/* g2dsnp.c
 * Input file:  g2ds-nupec.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2dsnp.h"


Object Print_nupec_message_states = UNBOUND;

Object The_type_description_of_source_nupec_synchronization = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_source_nupec_synchronizations, Qchain_of_available_source_nupec_synchronizations);

DEFINE_VARIABLE_WITH_SYMBOL(Source_nupec_synchronization_count, Qsource_nupec_synchronization_count);

Object Chain_of_available_source_nupec_synchronizations_vector = UNBOUND;

/* SOURCE-NUPEC-SYNCHRONIZATION-STRUCTURE-MEMORY-USAGE */
Object source_nupec_synchronization_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(221,0);
    temp = Source_nupec_synchronization_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SOURCE-NUPEC-SYNCHRONIZATION-COUNT */
Object outstanding_source_nupec_synchronization_count()
{
    Object def_structure_source_nupec_synchronization_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(221,1);
    gensymed_symbol = IFIX(Source_nupec_synchronization_count);
    def_structure_source_nupec_synchronization_variable = 
	    Chain_of_available_source_nupec_synchronizations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_source_nupec_synchronization_variable))
	goto end_loop;
    def_structure_source_nupec_synchronization_variable = 
	    ISVREF(def_structure_source_nupec_synchronization_variable,
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

/* RECLAIM-SOURCE-NUPEC-SYNCHRONIZATION-1 */
Object reclaim_source_nupec_synchronization_1(source_nupec_synchronization)
    Object source_nupec_synchronization;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(221,2);
    inline_note_reclaim_cons(source_nupec_synchronization,Nil);
    structure_being_reclaimed = source_nupec_synchronization;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      delete_frame(ISVREF(source_nupec_synchronization,(SI_Long)11L));
      SVREF(source_nupec_synchronization,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_source_nupec_synchronizations_vector,
	    IFIX(Current_thread_index));
    SVREF(source_nupec_synchronization,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_source_nupec_synchronizations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = source_nupec_synchronization;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SOURCE-NUPEC-SYNCHRONIZATION */
Object reclaim_structure_for_source_nupec_synchronization(source_nupec_synchronization)
    Object source_nupec_synchronization;
{
    x_note_fn_call(221,3);
    return reclaim_source_nupec_synchronization_1(source_nupec_synchronization);
}

static Object Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct;  /* g2-defstruct-structure-name::source-nupec-synchronization-g2-struct */

/* MAKE-PERMANENT-SOURCE-NUPEC-SYNCHRONIZATION-STRUCTURE-INTERNAL */
Object make_permanent_source_nupec_synchronization_structure_internal()
{
    Object def_structure_source_nupec_synchronization_variable;
    Object defstruct_g2_source_nupec_synchronization_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(221,4);
    def_structure_source_nupec_synchronization_variable = Nil;
    atomic_incff_symval(Qsource_nupec_synchronization_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_source_nupec_synchronization_variable = Nil;
	gensymed_symbol = (SI_Long)14L;
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
	defstruct_g2_source_nupec_synchronization_variable = the_array;
	SVREF(defstruct_g2_source_nupec_synchronization_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct;
	def_structure_source_nupec_synchronization_variable = 
		defstruct_g2_source_nupec_synchronization_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_source_nupec_synchronization_variable);
}

static Object Qstart;              /* start */

/* MAKE-SOURCE-NUPEC-SYNCHRONIZATION-1 */
Object make_source_nupec_synchronization_1(source_nupec_synchronization_list,
	    source_nupec_synchronization_xface,
	    source_nupec_synchronization_icp_socket)
    Object source_nupec_synchronization_list;
    Object source_nupec_synchronization_xface;
    Object source_nupec_synchronization_icp_socket;
{
    Object def_structure_source_nupec_synchronization_variable, temp;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(221,5);
    def_structure_source_nupec_synchronization_variable = 
	    ISVREF(Chain_of_available_source_nupec_synchronizations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_source_nupec_synchronization_variable) {
	temp = Chain_of_available_source_nupec_synchronizations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_source_nupec_synchronization_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_source_nupec_synchronization_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct;
    }
    else
	def_structure_source_nupec_synchronization_variable = 
		make_permanent_source_nupec_synchronization_structure_internal();
    inline_note_allocate_cons(def_structure_source_nupec_synchronization_variable,
	    Nil);
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)1L)) = source_nupec_synchronization_list;
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)2L)) = source_nupec_synchronization_xface;
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)3L)) = source_nupec_synchronization_icp_socket;
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)4L)) = Qstart;
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_source_nupec_synchronization_variable,
	    (SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_source_nupec_synchronization_variable,
	    (SI_Long)7L) = FIX((SI_Long)0L);
    temp = c_native_clock_ticks_or_cache(Nil,Nil);
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)8L)) = temp;
    temp = c_native_clock_ticks_or_cache(Nil,Nil);
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)10L)) = Nil;
    temp = put_up_nupec_synchronization_progress_display();
    SVREF(def_structure_source_nupec_synchronization_variable,
	    FIX((SI_Long)11L)) = temp;
    ISVREF(def_structure_source_nupec_synchronization_variable,
	    (SI_Long)12L) = FIX((SI_Long)0L);
    ISVREF(def_structure_source_nupec_synchronization_variable,
	    (SI_Long)13L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_source_nupec_synchronization_variable);
}

Object The_type_description_of_target_nupec_synchronization = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_target_nupec_synchronizations, Qchain_of_available_target_nupec_synchronizations);

DEFINE_VARIABLE_WITH_SYMBOL(Target_nupec_synchronization_count, Qtarget_nupec_synchronization_count);

Object Chain_of_available_target_nupec_synchronizations_vector = UNBOUND;

/* TARGET-NUPEC-SYNCHRONIZATION-STRUCTURE-MEMORY-USAGE */
Object target_nupec_synchronization_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(221,6);
    temp = Target_nupec_synchronization_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TARGET-NUPEC-SYNCHRONIZATION-COUNT */
Object outstanding_target_nupec_synchronization_count()
{
    Object def_structure_target_nupec_synchronization_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(221,7);
    gensymed_symbol = IFIX(Target_nupec_synchronization_count);
    def_structure_target_nupec_synchronization_variable = 
	    Chain_of_available_target_nupec_synchronizations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_target_nupec_synchronization_variable))
	goto end_loop;
    def_structure_target_nupec_synchronization_variable = 
	    ISVREF(def_structure_target_nupec_synchronization_variable,
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

/* RECLAIM-TARGET-NUPEC-SYNCHRONIZATION-1 */
Object reclaim_target_nupec_synchronization_1(target_nupec_synchronization)
    Object target_nupec_synchronization;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(221,8);
    inline_note_reclaim_cons(target_nupec_synchronization,Nil);
    structure_being_reclaimed = target_nupec_synchronization;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(target_nupec_synchronization,(SI_Long)5L);
      if (CAS_SVREF(target_nupec_synchronization,(SI_Long)5L,
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
      SVREF(target_nupec_synchronization,FIX((SI_Long)5L)) = Nil;
      delete_frame(ISVREF(target_nupec_synchronization,(SI_Long)7L));
      SVREF(target_nupec_synchronization,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_target_nupec_synchronizations_vector,
	    IFIX(Current_thread_index));
    SVREF(target_nupec_synchronization,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_target_nupec_synchronizations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = target_nupec_synchronization;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TARGET-NUPEC-SYNCHRONIZATION */
Object reclaim_structure_for_target_nupec_synchronization(target_nupec_synchronization)
    Object target_nupec_synchronization;
{
    x_note_fn_call(221,9);
    return reclaim_target_nupec_synchronization_1(target_nupec_synchronization);
}

static Object Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct;  /* g2-defstruct-structure-name::target-nupec-synchronization-g2-struct */

/* MAKE-PERMANENT-TARGET-NUPEC-SYNCHRONIZATION-STRUCTURE-INTERNAL */
Object make_permanent_target_nupec_synchronization_structure_internal()
{
    Object def_structure_target_nupec_synchronization_variable;
    Object defstruct_g2_target_nupec_synchronization_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(221,10);
    def_structure_target_nupec_synchronization_variable = Nil;
    atomic_incff_symval(Qtarget_nupec_synchronization_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_target_nupec_synchronization_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
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
	defstruct_g2_target_nupec_synchronization_variable = the_array;
	SVREF(defstruct_g2_target_nupec_synchronization_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct;
	def_structure_target_nupec_synchronization_variable = 
		defstruct_g2_target_nupec_synchronization_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_target_nupec_synchronization_variable);
}

/* MAKE-TARGET-NUPEC-SYNCHRONIZATION-1 */
Object make_target_nupec_synchronization_1(target_nupec_synchronization_icp_socket,
	    target_nupec_synchronization_expected_variable_count,
	    target_nupec_synchronization_time_offset)
    Object target_nupec_synchronization_icp_socket;
    Object target_nupec_synchronization_expected_variable_count;
    Object target_nupec_synchronization_time_offset;
{
    Object def_structure_target_nupec_synchronization_variable, temp;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(221,11);
    def_structure_target_nupec_synchronization_variable = 
	    ISVREF(Chain_of_available_target_nupec_synchronizations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_target_nupec_synchronization_variable) {
	temp = Chain_of_available_target_nupec_synchronizations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_target_nupec_synchronization_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_target_nupec_synchronization_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct;
    }
    else
	def_structure_target_nupec_synchronization_variable = 
		make_permanent_target_nupec_synchronization_structure_internal();
    inline_note_allocate_cons(def_structure_target_nupec_synchronization_variable,
	    Nil);
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)1L)) = target_nupec_synchronization_icp_socket;
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)2L)) = 
	    target_nupec_synchronization_expected_variable_count;
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)3L)) = target_nupec_synchronization_time_offset;
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)5L)) = Nil;
    temp = c_native_clock_ticks_or_cache(Nil,Nil);
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)6L)) = temp;
    temp = put_up_nupec_synchronization_progress_display();
    SVREF(def_structure_target_nupec_synchronization_variable,
	    FIX((SI_Long)7L)) = temp;
    ISVREF(def_structure_target_nupec_synchronization_variable,
	    (SI_Long)8L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_target_nupec_synchronization_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_source_nupec_synchronization, Qcurrent_source_nupec_synchronization);

DEFINE_VARIABLE_WITH_SYMBOL(Current_target_nupec_synchronization, Qcurrent_target_nupec_synchronization);

Object The_type_description_of_nupec_synchronize_variable_or_parameter = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_nupec_synchronize_variable_or_parameters, Qchain_of_available_nupec_synchronize_variable_or_parameters);

DEFINE_VARIABLE_WITH_SYMBOL(Nupec_synchronize_variable_or_parameter_count, Qnupec_synchronize_variable_or_parameter_count);

Object Chain_of_available_nupec_synchronize_variable_or_parameters_vector = UNBOUND;

/* NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-STRUCTURE-MEMORY-USAGE */
Object nupec_synchronize_variable_or_parameter_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(221,12);
    temp = Nupec_synchronize_variable_or_parameter_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-COUNT */
Object outstanding_nupec_synchronize_variable_or_parameter_count()
{
    Object def_structure_nupec_synchronize_variable_or_parameter_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(221,13);
    gensymed_symbol = IFIX(Nupec_synchronize_variable_or_parameter_count);
    def_structure_nupec_synchronize_variable_or_parameter_variable = 
	    Chain_of_available_nupec_synchronize_variable_or_parameters;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_nupec_synchronize_variable_or_parameter_variable))
	goto end_loop;
    def_structure_nupec_synchronize_variable_or_parameter_variable = 
	    ISVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
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

/* RECLAIM-NUPEC-SYNCHRONIZE-INTERNAL-1 */
Object reclaim_nupec_synchronize_internal_1(nupec_synchronize_variable_or_parameter)
    Object nupec_synchronize_variable_or_parameter;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(221,14);
    inline_note_reclaim_cons(nupec_synchronize_variable_or_parameter,Nil);
    structure_being_reclaimed = nupec_synchronize_variable_or_parameter;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_tree_1(ISVREF(nupec_synchronize_variable_or_parameter,
	      (SI_Long)1L));
      SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)1L)) = Nil;
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(nupec_synchronize_variable_or_parameter,
	      (SI_Long)3L));
      SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)3L)) = temp;
      SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_nupec_synchronize_variable_or_parameters_vector,
	    IFIX(Current_thread_index));
    SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_nupec_synchronize_variable_or_parameters_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = nupec_synchronize_variable_or_parameter;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object reclaim_structure_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter)
    Object nupec_synchronize_variable_or_parameter;
{
    x_note_fn_call(221,15);
    return reclaim_nupec_synchronize_internal_1(nupec_synchronize_variable_or_parameter);
}

static Object Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct;  /* g2-defstruct-structure-name::nupec-synchronize-variable-or-parameter-g2-struct */

/* MAKE-PERMANENT-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-STRUCTURE-INTERNAL */
Object make_permanent_nupec_synchronize_variable_or_parameter_structure_internal()
{
    Object def_structure_nupec_synchronize_variable_or_parameter_variable;
    Object defstruct_g2_nupec_synchronize_variable_or_parameter_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(221,16);
    def_structure_nupec_synchronize_variable_or_parameter_variable = Nil;
    atomic_incff_symval(Qnupec_synchronize_variable_or_parameter_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_nupec_synchronize_variable_or_parameter_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
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
	defstruct_g2_nupec_synchronize_variable_or_parameter_variable = 
		the_array;
	SVREF(defstruct_g2_nupec_synchronize_variable_or_parameter_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct;
	def_structure_nupec_synchronize_variable_or_parameter_variable = 
		defstruct_g2_nupec_synchronize_variable_or_parameter_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_nupec_synchronize_variable_or_parameter_variable);
}

/* MAKE-NUPEC-VARIABLE-OR-PARAMETER-1 */
Object make_nupec_variable_or_parameter_1(nupec_synchronize_remote_designation,
	    nupec_synchronize_local_variable_or_parameter_qm,
	    nupec_synchronize_collection_time,nupec_synchronize_expiration,
	    nupec_synchronize_history_length)
    Object nupec_synchronize_remote_designation;
    Object nupec_synchronize_local_variable_or_parameter_qm;
    Object nupec_synchronize_collection_time, nupec_synchronize_expiration;
    Object nupec_synchronize_history_length;
{
    Object def_structure_nupec_synchronize_variable_or_parameter_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(221,17);
    def_structure_nupec_synchronize_variable_or_parameter_variable = 
	    ISVREF(Chain_of_available_nupec_synchronize_variable_or_parameters_vector,
	    IFIX(Current_thread_index));
    if (def_structure_nupec_synchronize_variable_or_parameter_variable) {
	svref_arg_1 = 
		Chain_of_available_nupec_synchronize_variable_or_parameters_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct;
    }
    else
	def_structure_nupec_synchronize_variable_or_parameter_variable = 
		make_permanent_nupec_synchronize_variable_or_parameter_structure_internal();
    inline_note_allocate_cons(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    Nil);
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)1L)) = nupec_synchronize_remote_designation;
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)2L)) = 
	    nupec_synchronize_local_variable_or_parameter_qm;
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)4L)) = nupec_synchronize_collection_time;
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)5L)) = nupec_synchronize_expiration;
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)6L)) = nupec_synchronize_history_length;
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    (SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_nupec_synchronize_variable_or_parameter_variable,
	    FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_nupec_synchronize_variable_or_parameter_variable);
}

/* RECLAIM-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object reclaim_nupec_synchronize_variable_or_parameter(structure)
    Object structure;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(221,18);
    inline_note_reclaim_cons(structure,Nil);
    structure_being_reclaimed = structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_tree_1(ISVREF(structure,(SI_Long)1L));
      SVREF(structure,FIX((SI_Long)1L)) = Nil;
      temp = reclaim_managed_number_or_value_function(ISVREF(structure,
	      (SI_Long)3L));
      SVREF(structure,FIX((SI_Long)3L)) = temp;
      SVREF(structure,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_nupec_synchronize_variable_or_parameters_vector,
	    IFIX(Current_thread_index));
    SVREF(structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_nupec_synchronize_variable_or_parameters_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = structure;
    return VALUES_1(Nil);
}

Object The_type_description_of_local_nupec_variable = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_local_nupec_variables, Qchain_of_available_local_nupec_variables);

DEFINE_VARIABLE_WITH_SYMBOL(Local_nupec_variable_count, Qlocal_nupec_variable_count);

Object Chain_of_available_local_nupec_variables_vector = UNBOUND;

/* LOCAL-NUPEC-VARIABLE-STRUCTURE-MEMORY-USAGE */
Object local_nupec_variable_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(221,19);
    temp = Local_nupec_variable_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LOCAL-NUPEC-VARIABLE-COUNT */
Object outstanding_local_nupec_variable_count()
{
    Object def_structure_local_nupec_variable_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(221,20);
    gensymed_symbol = IFIX(Local_nupec_variable_count);
    def_structure_local_nupec_variable_variable = 
	    Chain_of_available_local_nupec_variables;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_local_nupec_variable_variable))
	goto end_loop;
    def_structure_local_nupec_variable_variable = 
	    ISVREF(def_structure_local_nupec_variable_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LOCAL-NUPEC-VARIABLE-1 */
Object reclaim_local_nupec_variable_1(local_nupec_variable)
    Object local_nupec_variable;
{
    Object temp, svref_arg_2;

    x_note_fn_call(221,21);
    inline_note_reclaim_cons(local_nupec_variable,Nil);
    temp = ISVREF(Chain_of_available_local_nupec_variables_vector,
	    IFIX(Current_thread_index));
    SVREF(local_nupec_variable,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_local_nupec_variables_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = local_nupec_variable;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LOCAL-NUPEC-VARIABLE */
Object reclaim_structure_for_local_nupec_variable(local_nupec_variable)
    Object local_nupec_variable;
{
    x_note_fn_call(221,22);
    return reclaim_local_nupec_variable_1(local_nupec_variable);
}

static Object Qg2_defstruct_structure_name_local_nupec_variable_g2_struct;  /* g2-defstruct-structure-name::local-nupec-variable-g2-struct */

/* MAKE-PERMANENT-LOCAL-NUPEC-VARIABLE-STRUCTURE-INTERNAL */
Object make_permanent_local_nupec_variable_structure_internal()
{
    Object def_structure_local_nupec_variable_variable;
    Object defstruct_g2_local_nupec_variable_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(221,23);
    def_structure_local_nupec_variable_variable = Nil;
    atomic_incff_symval(Qlocal_nupec_variable_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_local_nupec_variable_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_local_nupec_variable_variable = the_array;
	SVREF(defstruct_g2_local_nupec_variable_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_local_nupec_variable_g2_struct;
	def_structure_local_nupec_variable_variable = 
		defstruct_g2_local_nupec_variable_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_local_nupec_variable_variable);
}

/* MAKE-LOCAL-NUPEC-VARIABLE-1 */
Object make_local_nupec_variable_1(local_nupec_variable_frame)
    Object local_nupec_variable_frame;
{
    Object def_structure_local_nupec_variable_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(221,24);
    def_structure_local_nupec_variable_variable = 
	    ISVREF(Chain_of_available_local_nupec_variables_vector,
	    IFIX(Current_thread_index));
    if (def_structure_local_nupec_variable_variable) {
	svref_arg_1 = Chain_of_available_local_nupec_variables_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_local_nupec_variable_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_local_nupec_variable_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_local_nupec_variable_g2_struct;
    }
    else
	def_structure_local_nupec_variable_variable = 
		make_permanent_local_nupec_variable_structure_internal();
    inline_note_allocate_cons(def_structure_local_nupec_variable_variable,Nil);
    SVREF(def_structure_local_nupec_variable_variable,FIX((SI_Long)1L)) = 
	    local_nupec_variable_frame;
    SVREF(def_structure_local_nupec_variable_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_local_nupec_variable_variable);
}

Object Nupec_allowable_message_groups_in_progress = UNBOUND;

Object Nupec_allowable_variables_per_message_group = UNBOUND;

Object Nupec_allowable_history_values_per_message_group = UNBOUND;

Object Nupec_fixnum_timeout_interval = UNBOUND;

static Object Qg2ds_interface_structure;  /* g2ds-interface-structure */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object string_constant;     /* "NUPEC synchronization failed because the interface status of ~NF is " */

static Object Qinterface_status;   /* interface-status */

static Object array_constant_1;    /* # */

/* NUPEC-SYNCHRONIZE */
Object nupec_synchronize(synchronization_list,g2_to_g2_interface_object)
    Object synchronization_list, g2_to_g2_interface_object;
{
    Object variable_cons, car_new_value, interface_structure_qm, socket_qm;
    Object sync_object, current_source_nupec_synchronization;
    Object maximum_time_slice_size, time_slice_start_time;
    Object scheduler_enabled_qm, failure_qm, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(10);
    Object result;

    x_note_fn_call(221,25);
    SAVE_STACK();
    variable_cons = synchronization_list;
  next_loop:
    if ( !TRUEP(variable_cons))
	goto end_loop;
    car_new_value = make_local_nupec_variable_1(CAR(variable_cons));
    M_CAR(variable_cons) = car_new_value;
    variable_cons = M_CDR(variable_cons);
    goto next_loop;
  end_loop:;
    interface_structure_qm = 
	    get_slot_value_function(g2_to_g2_interface_object,
	    Qg2ds_interface_structure,Nil);
    socket_qm = interface_structure_qm ? ISVREF(interface_structure_qm,
	    (SI_Long)1L) : Nil;
    sync_object = make_source_nupec_synchronization_1(synchronization_list,
	    g2_to_g2_interface_object,socket_qm);
    current_source_nupec_synchronization = sync_object;
    PUSH_SPECIAL_WITH_SYMBOL(Current_source_nupec_synchronization,Qcurrent_source_nupec_synchronization,current_source_nupec_synchronization,
	    9);
      maximum_time_slice_size = Icp_socket_processing_time_limit;
      PUSH_SPECIAL_WITH_SYMBOL(Maximum_time_slice_size,Qmaximum_time_slice_size,maximum_time_slice_size,
	      8);
	time_slice_start_time = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Time_slice_start_time,Qtime_slice_start_time,time_slice_start_time,
		7);
	  if (socket_qm) {
	    next_loop_1:
	      if ( !TRUEP(ISVREF(sync_object,(SI_Long)4L)))
		  goto end_loop_1;
	      ne_set_next_timer_event((SI_Long)5000L);
	      perform_work_on_nupec_synchronization(sync_object);
	      Time_slice_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	      display_events_were_enabled = (SI_Long)0L != 
		      ne_display_events_enabled();
	      ne_disable_display_events();
	      if (PUSH_UNWIND_PROTECT(0)) {
		  scheduler_enabled_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
			  0);
		    g2_event_cycle_handling_windows_quit();
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      if (display_events_were_enabled)
		  ne_enable_display_events();
	      CONTINUE_UNWINDING(0);
	      goto next_loop_1;
	    end_loop_1:
	      failure_qm = ISVREF(sync_object,(SI_Long)5L);
	      if (failure_qm) {
		  if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
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
				    write_warning_message_header(FIX((SI_Long)1L));
				    twrite_beginning_of_wide_string(array_constant,
					    FIX((SI_Long)56L));
				    twrite_general_string(failure_qm);
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
		  reclaim_text_string(failure_qm);
	      }
	  }
	  else if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
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
			    write_warning_message_header(FIX((SI_Long)1L));
			    tformat(2,string_constant,
				    g2_to_g2_interface_object);
			    write_symbol_from_slot(get_slot_value_function(g2_to_g2_interface_object,
				    Qinterface_status,Nil),Nil);
			    twrite_beginning_of_wide_string(array_constant_1,
				    FIX((SI_Long)1L));
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
	  result = reclaim_source_nupec_synchronization_1(sync_object);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qnupec_synchronize_datum;  /* nupec-synchronize-datum */

static Object string_constant_1;   /* "[value]" */

static Object Qvalue;              /* value */

static Object Qwrite_icp_nupec_synchronize_datum;  /* write-icp-nupec-synchronize-datum */

static Object string_constant_2;   /* "resumable icp synch error: ~S expected, ~S found" */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* WRITE-ICP-NUPEC-SYNCHRONIZE-DATUM */
Object write_icp_nupec_synchronize_datum(nupec_synchronize_datum)
    Object nupec_synchronize_datum;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Object test, value, v1, v2, v3;
    char temp_2;
    double temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(221,26);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_synchronize_datum,
			string_constant_1,Qvalue,T,nupec_synchronize_datum,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if ( !TRUEP(nupec_synchronize_datum))
		  result_of_write = 
			  write_icp_byte(Nupec_synchronize_datum_null_type);
	      else if (SYMBOLP(nupec_synchronize_datum)) {
		  write_icp_byte(Nupec_synchronize_datum_symbol_type);
		  result_of_write = 
			  write_icp_text_string(symbol_name_text_string(nupec_synchronize_datum));
	      }
	      else if (FIXNUMP(nupec_synchronize_datum)) {
		  write_icp_byte(Nupec_synchronize_datum_integer_type);
		  result_of_write = write_icp_integer(nupec_synchronize_datum);
	      }
	      else if (FLOATP(nupec_synchronize_datum)) {
		  write_icp_byte(Nupec_synchronize_datum_float_type);
		  temp = DOUBLE_FLOAT_TO_DOUBLE(nupec_synchronize_datum);
		  result_of_write = write_icp_double_float_1(temp);
	      }
	      else if (text_string_p(nupec_synchronize_datum)) {
		  write_icp_byte(Nupec_synchronize_datum_text_type);
		  result_of_write = 
			  write_icp_text_string(nupec_synchronize_datum);
	      }
	      else
		  result_of_write = 
			  write_icp_byte(Nupec_synchronize_datum_null_type);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_synchronize_datum,string_constant_1,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else if ( !TRUEP(nupec_synchronize_datum))
	    temp_1 = write_icp_byte(Nupec_synchronize_datum_null_type);
	else if (SYMBOLP(nupec_synchronize_datum)) {
	    write_icp_byte(Nupec_synchronize_datum_symbol_type);
	    temp_1 = 
		    write_icp_text_string(symbol_name_text_string(nupec_synchronize_datum));
	}
	else if (FIXNUMP(nupec_synchronize_datum)) {
	    write_icp_byte(Nupec_synchronize_datum_integer_type);
	    temp_1 = write_icp_integer(nupec_synchronize_datum);
	}
	else if (FLOATP(nupec_synchronize_datum)) {
	    write_icp_byte(Nupec_synchronize_datum_float_type);
	    temp = DOUBLE_FLOAT_TO_DOUBLE(nupec_synchronize_datum);
	    temp_1 = write_icp_double_float_1(temp);
	}
	else if (text_string_p(nupec_synchronize_datum)) {
	    write_icp_byte(Nupec_synchronize_datum_text_type);
	    temp_1 = write_icp_text_string(nupec_synchronize_datum);
	}
	else
	    temp_1 = write_icp_byte(Nupec_synchronize_datum_null_type);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_nupec_synchronize_datum,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qwrite_icp_nupec_synchronize_datum,top,Nil);
		goto end_write_icp_nupec_synchronize_datum;
	    }
	}
	nupec_synchronize_datum = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : nupec_synchronize_datum;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_synchronize_datum,
			string_constant_1,Qvalue,T,nupec_synchronize_datum,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_2 = TRUEP(test);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ? EQ(test,Qtrue) :  !TRUEP(nupec_synchronize_datum)) {
		  value = write_icp_byte(Nupec_synchronize_datum_null_type);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(nupec_synchronize_datum);
		      resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_nupec_synchronize_datum;
		  }
		  result_of_write = value;
	      }
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      test = resumable_icp_pop();
		      temp_2 = TRUEP(test);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2 ? EQ(test,Qtrue) : 
			  SYMBOLP(nupec_synchronize_datum)) {
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp_1 = resumable_icp_pop();
			  if (! !(FIXNUMP(temp_1) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				  FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			      switch (INTEGER_TO_CHAR(temp_1)) {
				case 1:
				  goto l1;
				  break;
				case 2:
				  goto l2;
				  break;
				default:
				  break;
			      }
		      }
		    l1:
		      if (EQ(icp_suspend_1,
			      write_icp_byte(Nupec_synchronize_datum_symbol_type))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l2:
		      value = 
			      write_icp_text_string(symbol_name_text_string(nupec_synchronize_datum));
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		      result = VALUES_1(value);
		      goto end_block;
		    end_block:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(Qtrue);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(nupec_synchronize_datum);
			  resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_write_icp_nupec_synchronize_datum;
		      }
		      temp_1 = v1;
		      result_of_write = temp_1;
		  }
		  else {
		      test = Nil;
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  test = resumable_icp_pop();
			  temp_2 = TRUEP(test);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		      if (temp_2 ? EQ(test,Qtrue) : 
			      FIXNUMP(nupec_synchronize_datum)) {
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp_1 = resumable_icp_pop();
			      if (! !(FIXNUMP(temp_1) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),
				      temp_1) && FIXNUM_LE(temp_1,
				      FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp_1)) {
				    case 1:
				      goto l1_1;
				      break;
				    case 2:
				      goto l2_1;
				      break;
				    default:
				      break;
				  }
			  }
			l1_1:
			  if (EQ(icp_suspend_1,
				  write_icp_byte(Nupec_synchronize_datum_integer_type))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			l2_1:
			  value = write_icp_integer(nupec_synchronize_datum);
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			  result = VALUES_1(value);
			  goto end_block_1;
			end_block_1:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(nupec_synchronize_datum);
			      resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_nupec_synchronize_datum;
			  }
			  temp_1 = v1;
			  result_of_write = temp_1;
		      }
		      else {
			  test = Nil;
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      test = resumable_icp_pop();
			      temp_2 = TRUEP(test);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2 ? EQ(test,Qtrue) : 
				  FLOATP(nupec_synchronize_datum)) {
			      if (resumable_icp_state_1 ? 
				      TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				  temp_1 = resumable_icp_pop();
				  if (! !(FIXNUMP(temp_1) && 
					  FIXNUM_LE(FIX((SI_Long)-128L),
					  temp_1) && FIXNUM_LE(temp_1,
					  FIX((SI_Long)127L))))
				      switch (INTEGER_TO_CHAR(temp_1)) {
					case 1:
					  goto l1_2;
					  break;
					case 2:
					  goto l2_2;
					  break;
					default:
					  break;
				      }
			      }
			    l1_2:
			      if (EQ(icp_suspend_1,
				      write_icp_byte(Nupec_synchronize_datum_float_type))) 
					  {
				  resumable_icp_push(FIX((SI_Long)1L));
				  result = VALUES_1(Icp_suspend);
				  goto end_block_2;
			      }
			    l2_2:
			      temp = 
				      DOUBLE_FLOAT_TO_DOUBLE(nupec_synchronize_datum);
			      value = write_icp_double_float_1(temp);
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(FIX((SI_Long)2L));
				  result = VALUES_1(Icp_suspend);
				  goto end_block_2;
			      }
			      result = VALUES_1(value);
			      goto end_block_2;
			    end_block_2:
			      MVS_3(result,v1,v2,v3);
			      if (EQ(icp_suspend_1,v1)) {
				  resumable_icp_push(Qtrue);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(nupec_synchronize_datum);
				  resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				  result = VALUES_1(Icp_suspend);
				  POP_SPECIAL();
				  goto end_write_icp_nupec_synchronize_datum;
			      }
			      temp_1 = v1;
			      result_of_write = temp_1;
			  }
			  else {
			      test = Nil;
			      if (resumable_icp_state_1 ? 
				      TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				  test = resumable_icp_pop();
				  temp_2 = TRUEP(test);
			      }
			      else
				  temp_2 = TRUEP(Nil);
			      if (temp_2 ? EQ(test,Qtrue) : 
				      TRUEP(text_string_p(nupec_synchronize_datum))) 
					  {
				  if (resumable_icp_state_1 ? 
					  TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				      temp_1 = resumable_icp_pop();
				      if (! !(FIXNUMP(temp_1) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_1) && FIXNUM_LE(temp_1,
					      FIX((SI_Long)127L))))
					  switch (INTEGER_TO_CHAR(temp_1)) {
					    case 1:
					      goto l1_3;
					      break;
					    case 2:
					      goto l2_3;
					      break;
					    default:
					      break;
					  }
				  }
				l1_3:
				  if (EQ(icp_suspend_1,
					  write_icp_byte(Nupec_synchronize_datum_text_type))) 
					      {
				      resumable_icp_push(FIX((SI_Long)1L));
				      result = VALUES_1(Icp_suspend);
				      goto end_block_3;
				  }
				l2_3:
				  value = 
					  write_icp_text_string(nupec_synchronize_datum);
				  if (EQ(icp_suspend_1,value)) {
				      resumable_icp_push(FIX((SI_Long)2L));
				      result = VALUES_1(Icp_suspend);
				      goto end_block_3;
				  }
				  result = VALUES_1(value);
				  goto end_block_3;
				end_block_3:
				  MVS_3(result,v1,v2,v3);
				  if (EQ(icp_suspend_1,v1)) {
				      resumable_icp_push(Qtrue);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(nupec_synchronize_datum);
				      resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				      result = VALUES_1(Icp_suspend);
				      POP_SPECIAL();
				      goto end_write_icp_nupec_synchronize_datum;
				  }
				  temp_1 = v1;
				  result_of_write = temp_1;
			      }
			      else if ((resumable_icp_state_1 ? 
				      TRUEP(Resumable_icp_state) : 
				      TRUEP(Nil)) || T) {
				  value = 
					  write_icp_byte(Nupec_synchronize_datum_null_type);
				  if (EQ(icp_suspend_1,value)) {
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(nupec_synchronize_datum);
				      resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				      result = VALUES_1(Icp_suspend);
				      POP_SPECIAL();
				      goto end_write_icp_nupec_synchronize_datum;
				  }
				  result_of_write = value;
			      }
			      else
				  result_of_write = Qnil;
			  }
		      }
		  }
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_synchronize_datum,string_constant_1,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_2 = TRUEP(test);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ? EQ(test,Qtrue) :  !TRUEP(nupec_synchronize_datum)) {
		value = write_icp_byte(Nupec_synchronize_datum_null_type);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(nupec_synchronize_datum);
		    resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_nupec_synchronize_datum;
		}
		temp_1 = value;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_2 = TRUEP(test);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2 ? EQ(test,Qtrue) : 
			    SYMBOLP(nupec_synchronize_datum)) {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_4;
				break;
			      case 2:
				goto l2_4;
				break;
			      default:
				break;
			    }
		    }
		  l1_4:
		    if (EQ(icp_suspend_1,
			    write_icp_byte(Nupec_synchronize_datum_symbol_type))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_4;
		    }
		  l2_4:
		    value = 
			    write_icp_text_string(symbol_name_text_string(nupec_synchronize_datum));
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			goto end_block_4;
		    }
		    result = VALUES_1(value);
		    goto end_block_4;
		  end_block_4:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(nupec_synchronize_datum);
			resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
			result = VALUES_1(Icp_suspend);
			goto end_write_icp_nupec_synchronize_datum;
		    }
		    temp_1 = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_2 = TRUEP(test);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2 ? EQ(test,Qtrue) : 
			    FIXNUMP(nupec_synchronize_datum)) {
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp_1 = resumable_icp_pop();
			    if (! !(FIXNUMP(temp_1) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) 
				    && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp_1)) {
				  case 1:
				    goto l1_5;
				    break;
				  case 2:
				    goto l2_5;
				    break;
				  default:
				    break;
				}
			}
		      l1_5:
			if (EQ(icp_suspend_1,
				write_icp_byte(Nupec_synchronize_datum_integer_type))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_5;
			}
		      l2_5:
			value = write_icp_integer(nupec_synchronize_datum);
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_5;
			}
			result = VALUES_1(value);
			goto end_block_5;
		      end_block_5:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(nupec_synchronize_datum);
			    resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_nupec_synchronize_datum;
			}
			temp_1 = v1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    test = resumable_icp_pop();
			    temp_2 = TRUEP(test);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2 ? EQ(test,Qtrue) : 
				FLOATP(nupec_synchronize_datum)) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				temp_1 = resumable_icp_pop();
				if (! !(FIXNUMP(temp_1) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp_1) && FIXNUM_LE(temp_1,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp_1)) {
				      case 1:
					goto l1_6;
					break;
				      case 2:
					goto l2_6;
					break;
				      default:
					break;
				    }
			    }
			  l1_6:
			    if (EQ(icp_suspend_1,
				    write_icp_byte(Nupec_synchronize_datum_float_type))) 
					{
				resumable_icp_push(FIX((SI_Long)1L));
				result = VALUES_1(Icp_suspend);
				goto end_block_6;
			    }
			  l2_6:
			    temp = 
				    DOUBLE_FLOAT_TO_DOUBLE(nupec_synchronize_datum);
			    value = write_icp_double_float_1(temp);
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(FIX((SI_Long)2L));
				result = VALUES_1(Icp_suspend);
				goto end_block_6;
			    }
			    result = VALUES_1(value);
			    goto end_block_6;
			  end_block_6:
			    MVS_3(result,v1,v2,v3);
			    if (EQ(icp_suspend_1,v1)) {
				resumable_icp_push(Qtrue);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(nupec_synchronize_datum);
				resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				result = VALUES_1(Icp_suspend);
				goto end_write_icp_nupec_synchronize_datum;
			    }
			    temp_1 = v1;
			}
			else {
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				test = resumable_icp_pop();
				temp_2 = TRUEP(test);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2 ? EQ(test,Qtrue) : 
				    TRUEP(text_string_p(nupec_synchronize_datum))) 
					{
				if (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) {
				    temp_1 = resumable_icp_pop();
				    if (! !(FIXNUMP(temp_1) && 
					    FIXNUM_LE(FIX((SI_Long)-128L),
					    temp_1) && FIXNUM_LE(temp_1,
					    FIX((SI_Long)127L))))
					switch (INTEGER_TO_CHAR(temp_1)) {
					  case 1:
					    goto l1_7;
					    break;
					  case 2:
					    goto l2_7;
					    break;
					  default:
					    break;
					}
				}
			      l1_7:
				if (EQ(icp_suspend_1,
					write_icp_byte(Nupec_synchronize_datum_text_type))) 
					    {
				    resumable_icp_push(FIX((SI_Long)1L));
				    result = VALUES_1(Icp_suspend);
				    goto end_block_7;
				}
			      l2_7:
				value = 
					write_icp_text_string(nupec_synchronize_datum);
				if (EQ(icp_suspend_1,value)) {
				    resumable_icp_push(FIX((SI_Long)2L));
				    result = VALUES_1(Icp_suspend);
				    goto end_block_7;
				}
				result = VALUES_1(value);
				goto end_block_7;
			      end_block_7:
				MVS_3(result,v1,v2,v3);
				if (EQ(icp_suspend_1,v1)) {
				    resumable_icp_push(Qtrue);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(nupec_synchronize_datum);
				    resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				    result = VALUES_1(Icp_suspend);
				    goto end_write_icp_nupec_synchronize_datum;
				}
				temp_1 = v1;
			    }
			    else if ((resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : 
				    TRUEP(Nil)) || T) {
				value = 
					write_icp_byte(Nupec_synchronize_datum_null_type);
				if (EQ(icp_suspend_1,value)) {
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(nupec_synchronize_datum);
				    resumable_icp_push(Qwrite_icp_nupec_synchronize_datum);
				    result = VALUES_1(Icp_suspend);
				    goto end_write_icp_nupec_synchronize_datum;
				}
				temp_1 = value;
			    }
			    else
				temp_1 = Qnil;
			}
		    }
		}
	    }
	}
    }
    result = VALUES_1(temp_1);
  end_write_icp_nupec_synchronize_datum:
    return result;
}

static Object Qread_icp_nupec_synchronize_datum;  /* read-icp-nupec-synchronize-datum */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* READ-ICP-NUPEC-SYNCHRONIZE-DATUM */
Object read_icp_nupec_synchronize_datum()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, result_1;
    Object temp, result_of_read, resumable_icp_state_1, icp_suspend_1, top;
    Object key, value, arg1;
    double value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(221,27);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_synchronize_datum,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_1 = Nil;
	      temp = read_icp_byte();
	      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		      FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      break;
		    case 1:
		      result_1 = intern_text_string(1,read_icp_text_string());
		      break;
		    case 2:
		      result_1 = read_icp_integer();
		      break;
		    case 3:
		      result_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		      break;
		    case 4:
		      result_1 = read_icp_text_string();
		      break;
		    default:
		      break;
		  }
	      result_of_read = result_1;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize_datum,string_constant_1,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    result_1 = Nil;
	    temp = read_icp_byte();
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    break;
		  case 1:
		    result_1 = intern_text_string(1,read_icp_text_string());
		    break;
		  case 2:
		    result_1 = read_icp_integer();
		    break;
		  case 3:
		    result_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    break;
		  case 4:
		    result_1 = read_icp_text_string();
		    break;
		  default:
		    break;
		}
	    temp = result_1;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_nupec_synchronize_datum,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qread_icp_nupec_synchronize_datum,top,Nil);
		goto end_read_icp_nupec_synchronize_datum;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_synchronize_datum,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  key = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(result_1);
		      resumable_icp_push(Qread_icp_nupec_synchronize_datum);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_nupec_synchronize_datum;
		  }
		  key = value;
	      }
	      temp = key;
	      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		      FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      break;
		    case 1:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_text_string();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(result_1);
			      resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_nupec_synchronize_datum;
			  }
			  arg1 = value;
		      }
		      result_1 = intern_text_string(1,arg1);
		      break;
		    case 2:
		      value = read_icp_integer();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(result_1);
			  resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_nupec_synchronize_datum;
		      }
		      result_1 = value;
		      break;
		    case 3:
		      value_1 = read_icp_double_float_1();
		      if (EQ(icp_suspend_1,DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			  resumable_icp_push(key);
			  resumable_icp_push(result_1);
			  resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_nupec_synchronize_datum;
		      }
		      result_1 = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		      break;
		    case 4:
		      value = read_icp_text_string();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(result_1);
			  resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_nupec_synchronize_datum;
		      }
		      result_1 = value;
		      break;
		    default:
		      break;
		  }
	      result_of_read = result_1;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize_datum,string_constant_1,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    result_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		    : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		key = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(result_1);
		    resumable_icp_push(Qread_icp_nupec_synchronize_datum);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_nupec_synchronize_datum;
		}
		key = value;
	    }
	    temp = key;
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    break;
		  case 1:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_text_string();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(result_1);
			    resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_nupec_synchronize_datum;
			}
			arg1 = value;
		    }
		    result_1 = intern_text_string(1,arg1);
		    break;
		  case 2:
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(result_1);
			resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_nupec_synchronize_datum;
		    }
		    result_1 = value;
		    break;
		  case 3:
		    value_1 = read_icp_double_float_1();
		    if (EQ(icp_suspend_1,DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			resumable_icp_push(key);
			resumable_icp_push(result_1);
			resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_nupec_synchronize_datum;
		    }
		    result_1 = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		    break;
		  case 4:
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(result_1);
			resumable_icp_push(Qread_icp_nupec_synchronize_datum);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_nupec_synchronize_datum;
		    }
		    result_1 = value;
		    break;
		  default:
		    break;
		}
	    temp = result_1;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_nupec_synchronize_datum:
    return result;
}

static Object Qnupec_designation;  /* nupec-designation */

static Object Qwrite_icp_nupec_designation;  /* write-icp-nupec-designation */

/* WRITE-ICP-NUPEC-DESIGNATION */
Object write_icp_nupec_designation(nupec_designation)
    Object nupec_designation;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object test, value, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(221,28);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_designation,
			string_constant_1,Qvalue,T,nupec_designation,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if ( !TRUEP(nupec_designation))
		  result_of_write = 
			  write_icp_byte(Nupec_designation_null_type_tag);
	      else if (CONSP(nupec_designation)) {
		  write_icp_byte(Nupec_designation_cons_type_tag);
		  write_icp_nupec_designation(CAR(nupec_designation));
		  result_of_write = 
			  write_icp_nupec_designation(CDR(nupec_designation));
	      }
	      else if (SYMBOLP(nupec_designation)) {
		  write_icp_byte(Nupec_designation_symbol_type_tag);
		  result_of_write = 
			  write_icp_text_string(symbol_name_text_string(nupec_designation));
	      }
	      else
		  result_of_write = 
			  write_icp_byte(Nupec_designation_null_type_tag);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_designation,string_constant_1,Qvalue,Nil,
			  Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ( !TRUEP(nupec_designation))
	    temp = write_icp_byte(Nupec_designation_null_type_tag);
	else if (CONSP(nupec_designation)) {
	    write_icp_byte(Nupec_designation_cons_type_tag);
	    write_icp_nupec_designation(CAR(nupec_designation));
	    temp = write_icp_nupec_designation(CDR(nupec_designation));
	}
	else if (SYMBOLP(nupec_designation)) {
	    write_icp_byte(Nupec_designation_symbol_type_tag);
	    temp = 
		    write_icp_text_string(symbol_name_text_string(nupec_designation));
	}
	else
	    temp = write_icp_byte(Nupec_designation_null_type_tag);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_nupec_designation,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qwrite_icp_nupec_designation,top,Nil);
		goto end_write_icp_nupec_designation;
	    }
	}
	nupec_designation = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : nupec_designation;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_designation,
			string_constant_1,Qvalue,T,nupec_designation,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) :  !TRUEP(nupec_designation)) {
		  value = write_icp_byte(Nupec_designation_null_type_tag);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(nupec_designation);
		      resumable_icp_push(Qwrite_icp_nupec_designation);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_nupec_designation;
		  }
		  result_of_write = value;
	      }
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      test = resumable_icp_pop();
		      temp_1 = TRUEP(test);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ? EQ(test,Qtrue) : CONSP(nupec_designation)) {
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp = resumable_icp_pop();
			  if (! !(FIXNUMP(temp) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
			      switch (INTEGER_TO_CHAR(temp)) {
				case 1:
				  goto l1;
				  break;
				case 2:
				  goto l2;
				  break;
				case 3:
				  goto l3;
				  break;
				default:
				  break;
			      }
		      }
		    l1:
		      if (EQ(icp_suspend_1,
			      write_icp_byte(Nupec_designation_cons_type_tag))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l2:
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_designation(CAR(nupec_designation)))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l3:
		      value = 
			      write_icp_nupec_designation(CDR(nupec_designation));
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		      result = VALUES_1(value);
		      goto end_block;
		    end_block:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(Qtrue);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(nupec_designation);
			  resumable_icp_push(Qwrite_icp_nupec_designation);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_write_icp_nupec_designation;
		      }
		      temp = v1;
		      result_of_write = temp;
		  }
		  else {
		      test = Nil;
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  test = resumable_icp_pop();
			  temp_1 = TRUEP(test);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1 ? EQ(test,Qtrue) : 
				  SYMBOLP(nupec_designation)) {
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp = resumable_icp_pop();
			      if (! !(FIXNUMP(temp) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),temp) 
				      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
				  switch (INTEGER_TO_CHAR(temp)) {
				    case 1:
				      goto l1_1;
				      break;
				    case 2:
				      goto l2_1;
				      break;
				    default:
				      break;
				  }
			  }
			l1_1:
			  if (EQ(icp_suspend_1,
				  write_icp_byte(Nupec_designation_symbol_type_tag))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			l2_1:
			  value = 
				  write_icp_text_string(symbol_name_text_string(nupec_designation));
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			  result = VALUES_1(value);
			  goto end_block_1;
			end_block_1:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(nupec_designation);
			      resumable_icp_push(Qwrite_icp_nupec_designation);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_nupec_designation;
			  }
			  temp = v1;
			  result_of_write = temp;
		      }
		      else if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) || T) {
			  value = 
				  write_icp_byte(Nupec_designation_null_type_tag);
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(nupec_designation);
			      resumable_icp_push(Qwrite_icp_nupec_designation);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_nupec_designation;
			  }
			  result_of_write = value;
		      }
		      else
			  result_of_write = Qnil;
		  }
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_designation,string_constant_1,Qvalue,Nil,
			  Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) :  !TRUEP(nupec_designation)) {
		value = write_icp_byte(Nupec_designation_null_type_tag);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(nupec_designation);
		    resumable_icp_push(Qwrite_icp_nupec_designation);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_nupec_designation;
		}
		temp = value;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : CONSP(nupec_designation)) {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_2;
				break;
			      case 2:
				goto l2_2;
				break;
			      case 3:
				goto l3_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_2:
		    if (EQ(icp_suspend_1,
			    write_icp_byte(Nupec_designation_cons_type_tag))) {
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_2;
		    }
		  l2_2:
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_designation(CAR(nupec_designation)))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			goto end_block_2;
		    }
		  l3_1:
		    value = 
			    write_icp_nupec_designation(CDR(nupec_designation));
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)3L));
			result = VALUES_1(Icp_suspend);
			goto end_block_2;
		    }
		    result = VALUES_1(value);
		    goto end_block_2;
		  end_block_2:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(nupec_designation);
			resumable_icp_push(Qwrite_icp_nupec_designation);
			result = VALUES_1(Icp_suspend);
			goto end_write_icp_nupec_designation;
		    }
		    temp = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qtrue) : SYMBOLP(nupec_designation)) {
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp = resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp)) {
				  case 1:
				    goto l1_3;
				    break;
				  case 2:
				    goto l2_3;
				    break;
				  default:
				    break;
				}
			}
		      l1_3:
			if (EQ(icp_suspend_1,
				write_icp_byte(Nupec_designation_symbol_type_tag))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_3;
			}
		      l2_3:
			value = 
				write_icp_text_string(symbol_name_text_string(nupec_designation));
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_3;
			}
			result = VALUES_1(value);
			goto end_block_3;
		      end_block_3:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(nupec_designation);
			    resumable_icp_push(Qwrite_icp_nupec_designation);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_nupec_designation;
			}
			temp = v1;
		    }
		    else if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) || T) {
			value = 
				write_icp_byte(Nupec_designation_null_type_tag);
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(nupec_designation);
			    resumable_icp_push(Qwrite_icp_nupec_designation);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_nupec_designation;
			}
			temp = value;
		    }
		    else
			temp = Qnil;
		}
	    }
	}
    }
    result = VALUES_1(temp);
  end_write_icp_nupec_designation:
    return result;
}

/* RECLAIM-NUPEC-DESIGNATION */
Object reclaim_nupec_designation(nupec_designation)
    Object nupec_designation;
{
    x_note_fn_call(221,29);
    if (CONSP(nupec_designation)) {
	reclaim_nupec_designation(CAR(nupec_designation));
	reclaim_nupec_designation(CDR(nupec_designation));
	reclaim_gensym_cons_1(nupec_designation);
    }
    else if (text_string_p(nupec_designation))
	reclaim_text_string(nupec_designation);
    return VALUES_1(Nil);
}

static Object Qread_icp_nupec_designation;  /* read-icp-nupec-designation */

/* READ-ICP-NUPEC-DESIGNATION */
Object read_icp_nupec_designation()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, result_1;
    Object temp, result_of_read, resumable_icp_state_1, icp_suspend_1, top;
    Object key, value, arg1, arg2;
    Declare_special(1);
    Object result;

    x_note_fn_call(221,30);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_designation,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_1 = Nil;
	      temp = read_icp_byte();
	      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		      FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      break;
		    case 1:
		      result_1 = intern_text_string(1,read_icp_text_string());
		      break;
		    case 2:
		      temp = read_icp_nupec_designation();
		      result_1 = gensym_cons_1(temp,
			      read_icp_nupec_designation());
		      break;
		    default:
		      break;
		  }
	      result_of_read = result_1;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_designation,string_constant_1,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    result_1 = Nil;
	    temp = read_icp_byte();
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    break;
		  case 1:
		    result_1 = intern_text_string(1,read_icp_text_string());
		    break;
		  case 2:
		    temp = read_icp_nupec_designation();
		    result_1 = gensym_cons_1(temp,
			    read_icp_nupec_designation());
		    break;
		  default:
		    break;
		}
	    temp = result_1;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_nupec_designation,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qread_icp_nupec_designation,top,Nil);
		goto end_read_icp_nupec_designation;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_designation,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  key = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(result_1);
		      resumable_icp_push(Qread_icp_nupec_designation);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_nupec_designation;
		  }
		  key = value;
	      }
	      temp = key;
	      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		      FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      break;
		    case 1:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_text_string();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(result_1);
			      resumable_icp_push(Qread_icp_nupec_designation);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_nupec_designation;
			  }
			  arg1 = value;
		      }
		      result_1 = intern_text_string(1,arg1);
		      break;
		    case 2:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_nupec_designation();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(result_1);
			      resumable_icp_push(Qread_icp_nupec_designation);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_nupec_designation;
			  }
			  arg1 = value;
		      }
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg2 = resumable_icp_pop();
		      else {
			  value = read_icp_nupec_designation();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(arg1);
			      resumable_icp_push(key);
			      resumable_icp_push(result_1);
			      resumable_icp_push(Qread_icp_nupec_designation);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_nupec_designation;
			  }
			  arg2 = value;
		      }
		      result_1 = gensym_cons_1(arg1,arg2);
		      break;
		    default:
		      break;
		  }
	      result_of_read = result_1;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_designation,string_constant_1,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    result_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		    : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		key = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(result_1);
		    resumable_icp_push(Qread_icp_nupec_designation);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_nupec_designation;
		}
		key = value;
	    }
	    temp = key;
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    break;
		  case 1:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_text_string();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(result_1);
			    resumable_icp_push(Qread_icp_nupec_designation);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_nupec_designation;
			}
			arg1 = value;
		    }
		    result_1 = intern_text_string(1,arg1);
		    break;
		  case 2:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_nupec_designation();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(result_1);
			    resumable_icp_push(Qread_icp_nupec_designation);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_nupec_designation;
			}
			arg1 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg2 = resumable_icp_pop();
		    else {
			value = read_icp_nupec_designation();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(arg1);
			    resumable_icp_push(key);
			    resumable_icp_push(result_1);
			    resumable_icp_push(Qread_icp_nupec_designation);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_nupec_designation;
			}
			arg2 = value;
		    }
		    result_1 = gensym_cons_1(arg1,arg2);
		    break;
		  default:
		    break;
		}
	    temp = result_1;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_nupec_designation:
    return result;
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_nupec_synchronize_variable_or_parameter;  /* establish-new-object-index-for-nupec-synchronize-variable-or-parameter */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object establish_new_object_index_for_nupec_synchronize_variable_or_parameter varargs_1(int, n)
{
    Object nupec_synchronize_variable_or_parameter, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(221,31);
    INIT_ARGS_nonrelocating();
    nupec_synchronize_variable_or_parameter = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(nupec_synchronize_variable_or_parameter,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(nupec_synchronize_variable_or_parameter,(SI_Long)2L)));
	SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)2L)) = 
		svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qestablish_new_object_index_for_nupec_synchronize_variable_or_parameter,
		    top))
		return icp_error_internal(Qerror,string_constant_2,
			Qestablish_new_object_index_for_nupec_synchronize_variable_or_parameter,
			top,Nil);
	}
	nupec_synchronize_variable_or_parameter = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : nupec_synchronize_variable_or_parameter;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(nupec_synchronize_variable_or_parameter,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(nupec_synchronize_variable_or_parameter,(SI_Long)2L)));
	SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)2L)) = 
		svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter;  /* make-corresponding-icp-nupec-synchronize-variable-or-parameter */

/* MAKE-CORRESPONDING-ICP-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object make_corresponding_icp_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter)
    Object nupec_synchronize_variable_or_parameter;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object variable_or_parameter, designation, history_qm, history_length;
    Object collection_gensym_time, managed_number_or_value, temp_2;
    Object sub_class_bit_vector, exp_qm, temp_3, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    double gensymed_symbol, arg, arg_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(221,32);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(nupec_synchronize_variable_or_parameter,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(nupec_synchronize_variable_or_parameter,
		  (SI_Long)2L)));
	  SVREF(nupec_synchronize_variable_or_parameter,FIX((SI_Long)2L)) 
		  = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      variable_or_parameter = 
		      ISVREF(nupec_synchronize_variable_or_parameter,
		      (SI_Long)1L);
	      designation = 
		      generate_designation_for_block(variable_or_parameter);
	      history_qm = ISVREF(variable_or_parameter,(SI_Long)24L);
	      history_length = history_qm ? 
		      get_total_cascaded_ring_buffer_length(history_qm) : 
		      FIX((SI_Long)0L);
	      collection_gensym_time = Nil;
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		  gensymed_symbol = 
			  DFLOAT_ISAREF_1(ISVREF(variable_or_parameter,
			  (SI_Long)21L),(SI_Long)0L) - 
			  DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
			  (double)IFIX(Gensym_time_at_start);
		  arg = gensymed_symbol;
		  arg_1 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		  temp_1 = arg > arg_1 &&  
			  !inline_nanp_for_comparison(arg) ?  
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  if (temp_1);
		  else {
		      arg = gensymed_symbol;
		      arg_1 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		      temp_1 = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  collection_gensym_time = temp_1 ? Most_negative_fixnum : 
			  LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      managed_number_or_value = ISVREF(variable_or_parameter,
		      (SI_Long)23L);
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
	      temp_2 = collection_gensym_time;
	      sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		  temp_1 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  exp_qm = ISVREF(variable_or_parameter,(SI_Long)26L);
		  temp_3 = FIXNUMP(exp_qm) && FIXNUM_EQ(exp_qm,
			  Some_time_ago) ? Qno_value : exp_qm;
	      }
	      else
		  temp_3 = FIX((SI_Long)0L);
	      send_icp_define_nupec_synchronize_variable_or_parameter(corresponding_icp_object_index,
		      designation,temp,temp_2,temp_3,history_length);
	      reclaim_eval_tree_1(designation);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter,
		    top))
		return icp_error_internal(Qerror,string_constant_2,
			Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter,
			top,Nil);
	}
	nupec_synchronize_variable_or_parameter = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : nupec_synchronize_variable_or_parameter;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(nupec_synchronize_variable_or_parameter,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(nupec_synchronize_variable_or_parameter,
		      (SI_Long)2L)));
	      SVREF(nupec_synchronize_variable_or_parameter,
		      FIX((SI_Long)2L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      variable_or_parameter = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      ISVREF(nupec_synchronize_variable_or_parameter,
		      (SI_Long)1L);
	      designation = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      generate_designation_for_block(variable_or_parameter);
	      history_qm = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : ISVREF(variable_or_parameter,
		      (SI_Long)24L);
	      history_length = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : history_qm ? 
		      get_total_cascaded_ring_buffer_length(history_qm) : 
		      FIX((SI_Long)0L);
	      collection_gensym_time = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))) {
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      gensymed_symbol = 
			      DFLOAT_ISAREF_1(ISVREF(variable_or_parameter,
			      (SI_Long)21L),(SI_Long)0L) - 
			      DFLOAT_ISAREF_1(G2_time_at_start,
			      (SI_Long)0L) + 
			      (double)IFIX(Gensym_time_at_start);
		      arg = gensymed_symbol;
		      arg_1 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		      temp_1 = arg > arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		      if (temp_1);
		      else {
			  arg = gensymed_symbol;
			  arg_1 = 
				  DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
			  temp_1 = arg < arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
		      }
		      collection_gensym_time = temp_1 ? 
			      Most_negative_fixnum : 
			      LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol));
		  }
		  POP_LOCAL_ALLOCATION(0,0);
	      }
	      managed_number_or_value = ISVREF(variable_or_parameter,
		      (SI_Long)23L);
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
	      temp_2 = collection_gensym_time;
	      sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		  temp_1 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  exp_qm = ISVREF(variable_or_parameter,(SI_Long)26L);
		  temp_3 = FIXNUMP(exp_qm) && FIXNUM_EQ(exp_qm,
			  Some_time_ago) ? Qno_value : exp_qm;
	      }
	      else
		  temp_3 = FIX((SI_Long)0L);
	      if (EQ(icp_suspend_1,
		      send_icp_define_nupec_synchronize_variable_or_parameter(corresponding_icp_object_index,
		      designation,temp,temp_2,temp_3,history_length))) {
		  resumable_icp_push(collection_gensym_time);
		  resumable_icp_push(history_length);
		  resumable_icp_push(history_qm);
		  resumable_icp_push(designation);
		  resumable_icp_push(variable_or_parameter);
		  resumable_icp_push(corresponding_icp_object_index);
		  resumable_icp_push(Writing_resumable_icp_messages_p);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	      reclaim_eval_tree_1(designation);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(nupec_synchronize_variable_or_parameter);
	    resumable_icp_push(Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object get_icp_object_index_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter,
	    icp_port)
    Object nupec_synchronize_variable_or_parameter, icp_port;
{
    x_note_fn_call(221,33);
    return getfq_function_no_default(ISVREF(nupec_synchronize_variable_or_parameter,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object set_icp_object_index_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter,
	    corresponding_icp_object_index,icp_port)
    Object nupec_synchronize_variable_or_parameter;
    Object corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(221,34);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(nupec_synchronize_variable_or_parameter,(SI_Long)2L)));
    return VALUES_1(SVREF(nupec_synchronize_variable_or_parameter,
	    FIX((SI_Long)2L)) = svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object reclaim_icp_object_map_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter)
    Object nupec_synchronize_variable_or_parameter;
{
    Object icp_object_map;

    x_note_fn_call(221,35);
    icp_object_map = ISVREF(nupec_synchronize_variable_or_parameter,
	    (SI_Long)2L);
    if (icp_object_map)
	return reclaim_icp_object_map(nupec_synchronize_variable_or_parameter,
		icp_object_map,Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_nupec_synchronize_variable_or_parameter;  /* set-access-form-for-nupec-synchronize-variable-or-parameter */

/* RECLAIM-ICP-PORT-ENTRY-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object reclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter,
	    icp_port)
    Object nupec_synchronize_variable_or_parameter, icp_port;
{
    x_note_fn_call(221,36);
    return reclaim_icp_port_entry(icp_port,
	    nupec_synchronize_variable_or_parameter,
	    ISVREF(nupec_synchronize_variable_or_parameter,(SI_Long)2L),
	    Qset_access_form_for_nupec_synchronize_variable_or_parameter);
}

/* SET-ACCESS-FORM-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object set_access_form_for_nupec_synchronize_variable_or_parameter(nupec_synchronize_variable_or_parameter,
	    new_value)
    Object nupec_synchronize_variable_or_parameter, new_value;
{
    x_note_fn_call(221,37);
    return VALUES_1(SVREF(nupec_synchronize_variable_or_parameter,
	    FIX((SI_Long)2L)) = new_value);
}

static Object Qsend_icp_define_nupec_synchronize_variable_or_parameter;  /* send-icp-define-nupec-synchronize-variable-or-parameter */

static Object Qdefine_nupec_synchronize_variable_or_parameter;  /* define-nupec-synchronize-variable-or-parameter */

static Object string_constant_3;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qcorresponding_icp_object_index;  /* corresponding-icp-object-index */

static Object string_constant_4;   /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qremote_designation;  /* remote-designation */

static Object Qcurrent_value;      /* current-value */

static Object Qcollection_time;    /* collection-time */

static Object Qexpiration;         /* expiration */

static Object Qhistory_length;     /* history-length */

/* SEND-ICP-DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object send_icp_define_nupec_synchronize_variable_or_parameter(corresponding_icp_object_index,
	    remote_designation,current_value,collection_time,expiration,
	    history_length)
    Object corresponding_icp_object_index, remote_designation, current_value;
    Object collection_time, expiration, history_length;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(221,38);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_nupec_synchronize_variable_or_parameter;
	  }
	  start_writing_icp_message(FIX((SI_Long)200L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_nupec_synchronize_variable_or_parameter,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qremote_designation,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_nupec_designation(remote_designation);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_designation,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_nupec_designation(remote_designation);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcurrent_value,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_nupec_synchronize_datum(current_value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcurrent_value,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_nupec_synchronize_datum(current_value);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcollection_time,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(collection_time);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcollection_time,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(collection_time);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qexpiration,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_nupec_synchronize_datum(expiration);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexpiration,string_constant_4,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_nupec_synchronize_datum(expiration);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhistory_length,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(history_length);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhistory_length,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(history_length);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_nupec_synchronize_variable_or_parameter,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qremote_designation,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_nupec_designation(remote_designation);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_designation,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_nupec_designation(remote_designation);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcurrent_value,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_nupec_synchronize_datum(current_value);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcurrent_value,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_nupec_synchronize_datum(current_value);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcollection_time,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(collection_time);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcollection_time,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(collection_time);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qexpiration,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_nupec_synchronize_datum(expiration);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qexpiration,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_nupec_synchronize_datum(expiration);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhistory_length,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(history_length);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhistory_length,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(history_length);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qsend_icp_define_nupec_synchronize_variable_or_parameter,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_define_nupec_synchronize_variable_or_parameter,
			top,Nil);
		goto end_send_icp_define_nupec_synchronize_variable_or_parameter;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	remote_designation = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_designation;
	current_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : current_value;
	collection_time = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : collection_time;
	expiration = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : expiration;
	history_length = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : history_length;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_nupec_synchronize_variable_or_parameter;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)200L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_nupec_synchronize_variable_or_parameter,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qremote_designation,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_designation(remote_designation))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_designation,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_nupec_designation(remote_designation))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcurrent_value,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_synchronize_datum(current_value))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcurrent_value,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_nupec_synchronize_datum(current_value))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcollection_time,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
				  write_icp_integer(collection_time))) {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcollection_time,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			    write_icp_integer(collection_time))) {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qexpiration,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_synchronize_datum(expiration))) {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexpiration,string_constant_4,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_nupec_synchronize_datum(expiration))) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhistory_length,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(history_length))) {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhistory_length,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(history_length))) {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_nupec_synchronize_variable_or_parameter,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qremote_designation,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_designation(remote_designation))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_designation,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_nupec_designation(remote_designation))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcurrent_value,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_synchronize_datum(current_value))) 
				{
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcurrent_value,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_nupec_synchronize_datum(current_value))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcollection_time,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_integer(collection_time))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcollection_time,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_integer(collection_time))) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qexpiration,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_synchronize_datum(expiration))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qexpiration,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_nupec_synchronize_datum(expiration))) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhistory_length,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(history_length))) {
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhistory_length,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(history_length))) {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(history_length);
	      resumable_icp_push(expiration);
	      resumable_icp_push(collection_time);
	      resumable_icp_push(current_value);
	      resumable_icp_push(remote_designation);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_define_nupec_synchronize_variable_or_parameter);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_nupec_synchronize_variable_or_parameter;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_nupec_synchronize_variable_or_parameter:
    return result;
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* HANDLE-ICP-DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER--BODY */
Object handle_icp_define_nupec_synchronize_variable_or_parameter__body(corresponding_icp_object_index,
	    remote_designation,current_value,collection_time,expiration,
	    history_length)
    Object corresponding_icp_object_index, remote_designation, current_value;
    Object collection_time, expiration, history_length;
{
    Object current_computation_frame, time_offset;
    Object local_variable_or_parameter_qm, temp, new_sync_object;
    Object sub_class_bit_vector, store_managed_number_or_value_arg;
    Object svref_new_value, spec_qm, history, ring_buffer_shell;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(221,39);
    current_computation_frame = Inference_engine_parameters;
    time_offset = ISVREF(Current_target_nupec_synchronization,(SI_Long)3L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      local_variable_or_parameter_qm = remote_designation ? 
	      evaluate_designation(remote_designation,Nil) : Nil;
      temp = FIXNUM_ADD(time_offset,collection_time);
      new_sync_object = 
	      make_nupec_variable_or_parameter_1(remote_designation,
	      local_variable_or_parameter_qm,temp,FIXNUMP(expiration) ? 
	      FIXNUM_ADD(time_offset,expiration) : EQ(expiration,
	      Qno_value) ? Some_time_ago : expiration,history_length);
      if (local_variable_or_parameter_qm) {
	  temp_1 = SIMPLE_VECTOR_P(local_variable_or_parameter_qm) ? 
		  EQ(ISVREF(local_variable_or_parameter_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct) 
		  : TRUEP(Qnil);
	  if (temp_1);
	  else {
	      sub_class_bit_vector = 
		      ISVREF(ISVREF(local_variable_or_parameter_qm,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Variable_or_parameter_class_description,
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
		  temp_1 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp_1 =  !temp_1;
	  }
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  SVREF(new_sync_object,FIX((SI_Long)2L)) = Nil;
	  if (SIMPLE_VECTOR_P(local_variable_or_parameter_qm) && 
		  EQ(ISVREF(local_variable_or_parameter_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	      reclaim_temporary_constant_1(local_variable_or_parameter_qm);
      }
      store_managed_number_or_value_arg = current_value;
      svref_new_value = 
	      store_managed_number_or_value_function(ISVREF(new_sync_object,
	      (SI_Long)3L),store_managed_number_or_value_arg);
      SVREF(new_sync_object,FIX((SI_Long)3L)) = svref_new_value;
      if (text_string_p(current_value))
	  reclaim_text_string(current_value);
      if (IFIX(history_length) != (SI_Long)0L) {
	  spec_qm = local_variable_or_parameter_qm ? 
		  ISVREF(local_variable_or_parameter_qm,(SI_Long)25L) : Nil;
	  if (spec_qm) {
	      history = make_or_reformat_cascaded_ring_buffer(Nil,
		      SECOND(spec_qm),THIRD(spec_qm),FOURTH(spec_qm));
	      ring_buffer_shell = make_history_ring_buffer_1();
	      svref_new_value = allocate_managed_float_array(1,
		      Smallest_ring_buffer_vector_size);
	      SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = svref_new_value;
	      svref_new_value = allocate_managed_float_array(1,
		      Smallest_ring_buffer_vector_size);
	      SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = svref_new_value;
	      svref_new_value = Smallest_ring_buffer_vector_size;
	      SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = svref_new_value;
	      svref_new_value = history_cons_1(ring_buffer_shell,Nil);
	      SVREF(history,FIX((SI_Long)4L)) = svref_new_value;
	      SVREF(new_sync_object,FIX((SI_Long)8L)) = history;
	  }
      }
      store_corresponding_icp_object(corresponding_icp_object_index,
	      new_sync_object);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_define_nupec_synchronize_variable_or_parameter;  /* handle-icp-define-nupec-synchronize-variable-or-parameter */

/* HANDLE-ICP-DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER */
Object handle_icp_define_nupec_synchronize_variable_or_parameter()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object remote_designation, current_value, collection_time, expiration;
    Object history_length, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(221,40);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_nupec_synchronize_variable_or_parameter,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qremote_designation,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_nupec_designation();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_designation,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_designation = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  remote_designation = read_icp_nupec_designation();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcurrent_value,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_nupec_synchronize_datum();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcurrent_value,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    current_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  current_value = read_icp_nupec_synchronize_datum();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcollection_time,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcollection_time,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    collection_time = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  collection_time = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qexpiration,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_nupec_synchronize_datum();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qexpiration,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    expiration = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  expiration = read_icp_nupec_synchronize_datum();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhistory_length,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhistory_length,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    history_length = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  history_length = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_nupec_synchronize_variable_or_parameter__body(corresponding_icp_object_index,
			remote_designation,current_value,collection_time,
			expiration,history_length);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_nupec_synchronize_variable_or_parameter,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qremote_designation,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_nupec_designation();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_designation,string_constant_4,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_designation = result_of_read;
		POP_SPECIAL();
	    }
	    else
		remote_designation = read_icp_nupec_designation();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcurrent_value,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_nupec_synchronize_datum();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcurrent_value,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  current_value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		current_value = read_icp_nupec_synchronize_datum();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcollection_time,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcollection_time,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  collection_time = result_of_read;
		POP_SPECIAL();
	    }
	    else
		collection_time = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qexpiration,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_nupec_synchronize_datum();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qexpiration,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  expiration = result_of_read;
		POP_SPECIAL();
	    }
	    else
		expiration = read_icp_nupec_synchronize_datum();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhistory_length,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qhistory_length,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  history_length = result_of_read;
		POP_SPECIAL();
	    }
	    else
		history_length = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_nupec_synchronize_variable_or_parameter__body(corresponding_icp_object_index,
		      remote_designation,current_value,collection_time,
		      expiration,history_length);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_define_nupec_synchronize_variable_or_parameter,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_define_nupec_synchronize_variable_or_parameter,
			top,Nil);
		goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdefine_nupec_synchronize_variable_or_parameter,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  remote_designation = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qremote_designation,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_nupec_designation();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_designation,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_designation = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_nupec_designation();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  remote_designation = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  current_value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcurrent_value,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_nupec_synchronize_datum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(remote_designation);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcurrent_value,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    current_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  current_value = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  collection_time = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcollection_time,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(current_value);
			resumable_icp_push(remote_designation);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcollection_time,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    collection_time = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  collection_time = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  expiration = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qexpiration,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_nupec_synchronize_datum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(collection_time);
			resumable_icp_push(current_value);
			resumable_icp_push(remote_designation);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qexpiration,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    expiration = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(collection_time);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  expiration = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  history_length = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhistory_length,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(expiration);
			resumable_icp_push(collection_time);
			resumable_icp_push(current_value);
			resumable_icp_push(remote_designation);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhistory_length,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    history_length = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(expiration);
		      resumable_icp_push(collection_time);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  history_length = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_nupec_synchronize_variable_or_parameter__body(corresponding_icp_object_index,
			remote_designation,current_value,collection_time,
			expiration,history_length);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_nupec_synchronize_variable_or_parameter,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_designation = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qremote_designation,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_nupec_designation();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_designation,string_constant_4,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_designation = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_nupec_designation();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		remote_designation = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		current_value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcurrent_value,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcurrent_value,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  current_value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_nupec_synchronize_datum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(remote_designation);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		current_value = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		collection_time = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcollection_time,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcollection_time,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  collection_time = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(current_value);
		    resumable_icp_push(remote_designation);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		collection_time = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		expiration = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qexpiration,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(collection_time);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qexpiration,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  expiration = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_nupec_synchronize_datum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(collection_time);
		    resumable_icp_push(current_value);
		    resumable_icp_push(remote_designation);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		expiration = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		history_length = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhistory_length,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(expiration);
		      resumable_icp_push(collection_time);
		      resumable_icp_push(current_value);
		      resumable_icp_push(remote_designation);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qhistory_length,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  history_length = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(expiration);
		    resumable_icp_push(collection_time);
		    resumable_icp_push(current_value);
		    resumable_icp_push(remote_designation);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_define_nupec_synchronize_variable_or_parameter);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_nupec_synchronize_variable_or_parameter;
		}
		history_length = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_nupec_synchronize_variable_or_parameter__body(corresponding_icp_object_index,
		      remote_designation,current_value,collection_time,
		      expiration,history_length);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_define_nupec_synchronize_variable_or_parameter:
    return result;
}

static Object Qtelewindows;        /* telewindows */

static Object Qstart_rejected;     /* start-rejected */

/* WRITE-MESSAGE-GROUP-FOR-NUPEC-SYNCHRONIZE */
Object write_message_group_for_nupec_synchronize(reject_reason_qm)
    Object reject_reason_qm;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,41);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_nupec_synchronize_control_message(Qstart_rejected,
					reject_reason_qm);
				temp = reclaim_text_string(reject_reason_qm);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qsend_icp_nupec_synchronize;  /* send-icp-nupec-synchronize */

static Object Qnupec_synchronize;  /* nupec-synchronize */

static Object Qvariable_count;     /* variable-count */

static Object Qyear;               /* year */

static Object Qmonth;              /* month */

static Object Qday;                /* day */

static Object Qhour;               /* hour */

static Object Qminute;             /* minute */

/* SEND-ICP-NUPEC-SYNCHRONIZE */
Object send_icp_nupec_synchronize(variable_count,year,month,day,hour,
	    minute,second_1)
    Object variable_count, year, month, day, hour, minute, second_1;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(221,42);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_nupec_synchronize;
	  }
	  start_writing_icp_message(FIX((SI_Long)203L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qnupec_synchronize,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qvariable_count,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(variable_count);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qvariable_count,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(variable_count);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qyear,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(year);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qyear,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(year);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmonth,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(month);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmonth,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(month);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qday,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(day);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qday,string_constant_4,Qargument,Nil,Nil,
				  Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(day);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhour,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(hour);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhour,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(hour);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qminute,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(minute);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qminute,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(minute);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qsecond,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_unsigned_integer(second_1);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qsecond,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_unsigned_integer(second_1);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnupec_synchronize,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qvariable_count,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(variable_count);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qvariable_count,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(variable_count);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qyear,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(year);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qyear,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(year);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qmonth,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(month);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qmonth,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(month);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qday,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(day);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),Qday,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(day);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhour,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(hour);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhour,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(hour);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qminute,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(minute);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qminute,string_constant_4,Qargument,Nil,
				Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(minute);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qsecond,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(second_1);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qsecond,string_constant_4,Qargument,Nil,
				Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(second_1);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_nupec_synchronize,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_nupec_synchronize,top,Nil);
		goto end_send_icp_nupec_synchronize;
	    }
	}
	variable_count = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : variable_count;
	year = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : year;
	month = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : month;
	day = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : day;
	hour = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : hour;
	minute = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : minute;
	second_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : second_1;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_nupec_synchronize;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)203L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qnupec_synchronize,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
			    break;
			  case 7:
			    goto l7;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qvariable_count,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(variable_count))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qvariable_count,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(variable_count))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qyear,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_unsigned_integer(year))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qyear,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_unsigned_integer(year))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmonth,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
				  write_icp_unsigned_integer(month))) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmonth,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_unsigned_integer(month))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qday,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_unsigned_integer(day))) {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qday,string_constant_4,Qargument,Nil,Nil,
				  Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_unsigned_integer(day))) {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhour,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_unsigned_integer(hour))) {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhour,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_unsigned_integer(hour))) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qminute,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
				  write_icp_unsigned_integer(minute))) {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qminute,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(minute))) {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l7:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qsecond,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(second_1))) {
			  resumable_icp_push(FIX((SI_Long)7L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qsecond,string_constant_4,Qargument,Nil,
				  Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(second_1))) {
		    resumable_icp_push(FIX((SI_Long)7L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnupec_synchronize,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_1;
			  break;
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
			  break;
			case 7:
			  goto l7_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qvariable_count,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(variable_count))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qvariable_count,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(variable_count))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qyear,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_unsigned_integer(year))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qyear,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_unsigned_integer(year))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qmonth,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_unsigned_integer(month))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qmonth,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_unsigned_integer(month))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qday,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_unsigned_integer(day))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),Qday,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_unsigned_integer(day))) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhour,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_unsigned_integer(hour))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhour,string_constant_4,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_unsigned_integer(hour))) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qminute,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_unsigned_integer(minute))) {
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qminute,string_constant_4,Qargument,Nil,
				Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_unsigned_integer(minute))) {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l7_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qsecond,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
				write_icp_unsigned_integer(second_1))) {
			resumable_icp_push(FIX((SI_Long)7L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qsecond,string_constant_4,Qargument,Nil,
				Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(second_1))) {
		  resumable_icp_push(FIX((SI_Long)7L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(second_1);
	      resumable_icp_push(minute);
	      resumable_icp_push(hour);
	      resumable_icp_push(day);
	      resumable_icp_push(month);
	      resumable_icp_push(year);
	      resumable_icp_push(variable_count);
	      resumable_icp_push(Qsend_icp_nupec_synchronize);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_nupec_synchronize;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_nupec_synchronize:
    return result;
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qreceive_nupec_synchronize_task;  /* receive-nupec-synchronize-task */

/* HANDLE-ICP-NUPEC-SYNCHRONIZE--BODY */
Object handle_icp_nupec_synchronize__body(variable_count,year,month,day,
	    hour,minute,second_1)
    Object variable_count, year, month, day, hour, minute, second_1;
{
    Object reject_reason_qm, offset_for_remote_gensym_time, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(221,43);
    if (Print_nupec_message_states)
	format((SI_Long)2L,T,"~%Starting Synchronization!");
    reject_reason_qm = reason_to_reject_nupec_synchronization_qm();
    offset_for_remote_gensym_time = encode_gensym_time(second_1,minute,
	    hour,day,month,year);
    if (reject_reason_qm)
	write_message_group_for_nupec_synchronize(reject_reason_qm);
    else {
	Current_target_nupec_synchronization = 
		make_target_nupec_synchronization_1(Current_icp_socket,
		variable_count,offset_for_remote_gensym_time);
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(Current_target_nupec_synchronization,(SI_Long)5L);
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qreceive_nupec_synchronize_task;
	temp = SYMBOL_FUNCTION(Qreceive_nupec_synchronize_task);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SVREF(Current_target_nupec_synchronization,(SI_Long)5L,old,
		new_1)) {
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

static Object Qhandle_icp_nupec_synchronize;  /* handle-icp-nupec-synchronize */

/* HANDLE-ICP-NUPEC-SYNCHRONIZE */
Object handle_icp_nupec_synchronize()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, variable_count, year, month;
    Object day, hour, minute, second_1, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(221,44);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_synchronize,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qvariable_count,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qvariable_count,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    variable_count = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  variable_count = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qyear,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qyear,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    year = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  year = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmonth,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmonth,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    month = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  month = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qday,string_constant_4,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),Qday,
				string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    day = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  day = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhour,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhour,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    hour = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  hour = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qminute,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qminute,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    minute = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  minute = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsecond,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsecond,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    second_1 = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  second_1 = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nupec_synchronize__body(variable_count,
			year,month,day,hour,minute,second_1);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qvariable_count,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qvariable_count,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  variable_count = result_of_read;
		POP_SPECIAL();
	    }
	    else
		variable_count = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qyear,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qyear,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  year = result_of_read;
		POP_SPECIAL();
	    }
	    else
		year = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmonth,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qmonth,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  month = result_of_read;
		POP_SPECIAL();
	    }
	    else
		month = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qday,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qday,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  day = result_of_read;
		POP_SPECIAL();
	    }
	    else
		day = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhour,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qhour,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  hour = result_of_read;
		POP_SPECIAL();
	    }
	    else
		hour = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qminute,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qminute,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  minute = result_of_read;
		POP_SPECIAL();
	    }
	    else
		minute = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsecond,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsecond,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  second_1 = result_of_read;
		POP_SPECIAL();
	    }
	    else
		second_1 = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nupec_synchronize__body(variable_count,year,month,
		      day,hour,minute,second_1);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_nupec_synchronize,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_nupec_synchronize,top,Nil);
		goto end_handle_icp_nupec_synchronize;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_synchronize,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  variable_count = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qvariable_count,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qvariable_count,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    variable_count = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  variable_count = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  year = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qyear,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qyear,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    year = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  year = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  month = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmonth,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(year);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmonth,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    month = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  month = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  day = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qday,string_constant_4,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(month);
			resumable_icp_push(year);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),Qday,
				string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    day = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  day = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  hour = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhour,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(day);
			resumable_icp_push(month);
			resumable_icp_push(year);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhour,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    hour = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  hour = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  minute = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qminute,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(hour);
			resumable_icp_push(day);
			resumable_icp_push(month);
			resumable_icp_push(year);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qminute,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    minute = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(hour);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  minute = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  second_1 = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsecond,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(minute);
			resumable_icp_push(hour);
			resumable_icp_push(day);
			resumable_icp_push(month);
			resumable_icp_push(year);
			resumable_icp_push(variable_count);
			resumable_icp_push(Qhandle_icp_nupec_synchronize);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsecond,string_constant_4,Qargument,T,
				result_of_read,Nil,Nil);
		    second_1 = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(minute);
		      resumable_icp_push(hour);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  second_1 = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nupec_synchronize__body(variable_count,
			year,month,day,hour,minute,second_1);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		variable_count = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qvariable_count,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qvariable_count,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  variable_count = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		variable_count = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		year = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qyear,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qyear,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  year = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		year = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		month = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmonth,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qmonth,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  month = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(year);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		month = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		day = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qday,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qday,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  day = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(month);
		    resumable_icp_push(year);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		day = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		hour = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhour,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qhour,
			      string_constant_4,Qargument,T,result_of_read,
			      Nil,Nil);
		  hour = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(day);
		    resumable_icp_push(month);
		    resumable_icp_push(year);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		hour = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		minute = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qminute,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(hour);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qminute,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  minute = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(hour);
		    resumable_icp_push(day);
		    resumable_icp_push(month);
		    resumable_icp_push(year);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		minute = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		second_1 = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsecond,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(minute);
		      resumable_icp_push(hour);
		      resumable_icp_push(day);
		      resumable_icp_push(month);
		      resumable_icp_push(year);
		      resumable_icp_push(variable_count);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsecond,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  second_1 = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(minute);
		    resumable_icp_push(hour);
		    resumable_icp_push(day);
		    resumable_icp_push(month);
		    resumable_icp_push(year);
		    resumable_icp_push(variable_count);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize;
		}
		second_1 = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nupec_synchronize__body(variable_count,year,month,
		      day,hour,minute,second_1);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_nupec_synchronize:
    return result;
}

/* RECEIVE-NUPEC-SYNCHRONIZE-TASK */
Object receive_nupec_synchronize_task()
{
    Object temp;

    x_note_fn_call(221,45);
    temp = receive_nupec_synchronize();
    return VALUES_1(temp);
}

static Object Qstart_accepted;     /* start-accepted */

/* RECEIVE-NUPEC-SYNCHRONIZE */
Object receive_nupec_synchronize()
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, time_slice_start_time;
    Object scheduler_enabled_qm;
    char display_events_were_enabled;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(221,46);
    SAVE_STACK();
    if (Current_target_nupec_synchronization) {
	system_pause(0);
	current_icp_port = 
		ISVREF(ISVREF(Current_target_nupec_synchronization,
		(SI_Long)1L),(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_nupec_synchronize_control_message(Qstart_accepted,
					    FIX((SI_Long)0L));
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
	time_slice_start_time = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Time_slice_start_time,Qtime_slice_start_time,time_slice_start_time,
		1);
	next_loop:
	  if ( !TRUEP(Current_target_nupec_synchronization))
	      goto end_loop;
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      check_for_target_nupec_timeout();
	      Time_slice_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	      ne_set_next_timer_event((SI_Long)5000L);
	      display_events_were_enabled = (SI_Long)0L != 
		      ne_display_events_enabled();
	      ne_disable_display_events();
	      if (PUSH_UNWIND_PROTECT(0)) {
		  scheduler_enabled_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
			  0);
		    g2_event_cycle_handling_windows_quit();
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      if (display_events_were_enabled)
		  ne_enable_display_events();
	      CONTINUE_UNWINDING(0);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object float_constant;      /* 0.0 */

static Object string_constant_5;   /* "Reception of NUPEC synchronization timed out after a delay ~
				    *                  of ~a seconds."
				    */

static Object Qabort_synchronize;  /* abort-synchronize */

/* CHECK-FOR-TARGET-NUPEC-TIMEOUT */
Object check_for_target_nupec_timeout()
{
    Object temp, message_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_2, aref_arg_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, wait_time;
    double temp_1, gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double gensymed_symbol_6, gensymed_symbol_7, aref_new_value;
    Declare_special(12);

    x_note_fn_call(221,47);
    gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
    gensymed_symbol_1 = IFIX(ISVREF(Current_target_nupec_synchronization,
	    (SI_Long)6L));
    if (gensymed_symbol >= gensymed_symbol_1)
	wait_time = gensymed_symbol - gensymed_symbol_1;
    else {
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	wait_time = gensymed_symbol + (SI_Long)1L;
    }
    if (wait_time >= IFIX(Nupec_fixnum_timeout_interval)) {
	temp = lfloat(Fixnum_time_units_per_second,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	message_1 = tformat_text_string(2,string_constant_5,
		DOUBLE_TO_DOUBLE_FLOAT((double)wait_time / temp_1));
	current_icp_port = 
		ISVREF(ISVREF(Current_target_nupec_synchronization,
		(SI_Long)1L),(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol_2 = Nil;
				gensymed_symbol_3 = 0.0;
				gensymed_symbol_4 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_2 = T;
				    gensymed_symbol_3 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_4 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_4);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_nupec_synchronize_control_message(Qabort_synchronize,
					    message_1);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_6 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_7 = gensymed_symbol_5 
					    - gensymed_symbol_6;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_7 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol_2 ? 
					    gensymed_symbol_3 + 
					    gensymed_symbol_7 + 
					    (gensymed_symbol_6 - 
					    gensymed_symbol_4) : 
					    gensymed_symbol_5;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
	abort_target_nupec_synchronization(message_1);
	return reclaim_text_string(message_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qgraph;              /* graph */

static Object string_constant_6;   /* "Reception of a NUPEC synchronization has been aborted for the following ~
				    *      reason: ~a"
				    */

/* ABORT-TARGET-NUPEC-SYNCHRONIZATION */
Object abort_target_nupec_synchronization(abort_reason)
    Object abort_reason;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, graph, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(221,48);
    reclaim_target_nupec_synchronization_1(Current_target_nupec_synchronization);
    Current_target_nupec_synchronization = Nil;
    system_resume();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    graph = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qgraph);
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
      graph = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & (SI_Long)1L)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(graph,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	  gensymed_symbol_1 = graph;
	  gensymed_symbol_2 = Nil;
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(graph,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	  gensymed_symbol_1 = graph;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(3,FIX((SI_Long)1L),string_constant_6,abort_reason);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

static Object Qgroup_received;     /* group-received */

/* WRITE-GROUP-SENT-FOR-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE */
Object write_group_sent_for_nupec_synchronize_control_message(extra_argument)
    Object extra_argument;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,49);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_nupec_synchronize_control_message(Qgroup_received,
					extra_argument);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qend_of_synchronization;  /* end-of-synchronization */

/* WRITE-END-OF-SYNCH-FOR-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE */
Object write_end_of_synch_for_nupec_synchronize_control_message()
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,50);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_nupec_synchronize_control_message(Qend_of_synchronization,
					FIX((SI_Long)0L));
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qend_of_synchronization_confirmed_thank_you;  /* end-of-synchronization-confirmed-thank-you */

/* WRITE-CONFIRMED-FOR-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE */
Object write_confirmed_for_nupec_synchronize_control_message()
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,51);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = 
					send_icp_nupec_synchronize_control_message(Qend_of_synchronization_confirmed_thank_you,
					FIX((SI_Long)0L));
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qsend_icp_nupec_synchronize_control_message;  /* send-icp-nupec-synchronize-control-message */

static Object Qcorresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qnupec_synchronize_control_message;  /* nupec-synchronize-control-message */

static Object Qcontrol_message;    /* control-message */

static Object string_constant_7;   /* "[object arg]" */

static Object Qextra_argument;     /* extra-argument */

/* SEND-ICP-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE */
Object send_icp_nupec_synchronize_control_message(control_message,
	    extra_argument)
    Object control_message, extra_argument;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(221,52);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_nupec_synchronize_control_message;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(control_message),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = make_corresponding_icp_symbol(control_message);
	  control_message = temp_1;
	  start_writing_icp_message(FIX((SI_Long)201L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnupec_synchronize_control_message,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcontrol_message,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(control_message);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcontrol_message,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(control_message);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qextra_argument,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_nupec_synchronize_datum(extra_argument);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qextra_argument,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_nupec_synchronize_datum(extra_argument);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnupec_synchronize_control_message,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcontrol_message,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(control_message);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcontrol_message,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(control_message);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qextra_argument,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_nupec_synchronize_datum(extra_argument);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qextra_argument,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_nupec_synchronize_datum(extra_argument);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_nupec_synchronize_control_message,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_nupec_synchronize_control_message,top,Nil);
		goto end_send_icp_nupec_synchronize_control_message;
	    }
	}
	control_message = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : control_message;
	extra_argument = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : extra_argument;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_nupec_synchronize_control_message;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(control_message),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      control_message = value;
	  else {
	      value_1 = make_corresponding_icp_symbol(control_message);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      control_message = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)201L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnupec_synchronize_control_message,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qcontrol_message,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(control_message))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcontrol_message,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(control_message))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qextra_argument,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_synchronize_datum(extra_argument))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qextra_argument,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_nupec_synchronize_datum(extra_argument))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnupec_synchronize_control_message,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qcontrol_message,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(control_message))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcontrol_message,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(control_message))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qextra_argument,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_synchronize_datum(extra_argument))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qextra_argument,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_nupec_synchronize_datum(extra_argument))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(extra_argument);
	      resumable_icp_push(control_message);
	      resumable_icp_push(Qsend_icp_nupec_synchronize_control_message);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_nupec_synchronize_control_message;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_nupec_synchronize_control_message:
    return result;
}

static Object Qsending;            /* sending */

static Object string_constant_8;   /* "Synchronization request was rejected by the remote G2.  ~
				    *                  The following reason was given:  ~a"
				    */

static Object Qgroup_sent;         /* group-sent */

static Object Qprogress_through_nupec_synchronization;  /* progress-through-nupec-synchronization */

static Object Qwait_for_final_acknowledgement;  /* wait-for-final-acknowledgement */

/* HANDLE-ICP-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE--BODY */
Object handle_icp_nupec_synchronize_control_message__body(control_message,
	    extra_argument)
    Object control_message, extra_argument;
{
    Object svref_arg_1, svref_new_value, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, scope_conses, ab_loopvar_, ab_loopvar__1, graph;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_3;
    double temp_1, temp_2;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(221,53);
    if (EQ(control_message,Qstart_accepted)) {
	svref_arg_1 = Current_source_nupec_synchronization;
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = Qsending;
	svref_arg_1 = Current_source_nupec_synchronization;
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
	if (Print_nupec_message_states)
	    format((SI_Long)2L,Terminal_io,"~%Sending...");
    }
    else if (EQ(control_message,Qstart_rejected)) {
	if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
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
			  write_warning_message_header(FIX((SI_Long)1L));
			  tformat(2,string_constant_8,extra_argument);
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
	reclaim_text_string(extra_argument);
	svref_arg_1 = Current_source_nupec_synchronization;
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	svref_arg_1 = Current_source_nupec_synchronization;
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
	if (Print_nupec_message_states)
	    format((SI_Long)2L,Terminal_io,"~%Rejected...");
    }
    else if (EQ(control_message,Qgroup_sent)) {
	write_group_sent_for_nupec_synchronize_control_message(extra_argument);
	svref_arg_1 = Current_target_nupec_synchronization;
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = lfloat(ISVREF(Current_target_nupec_synchronization,
		    (SI_Long)8L),float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    temp = lfloat(ISVREF(Current_target_nupec_synchronization,
		    (SI_Long)2L),float_constant);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    change_slot_value(3,
		    ISVREF(Current_target_nupec_synchronization,
		    (SI_Long)7L),Qprogress_through_nupec_synchronization,
		    lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp_1 / temp_2 * 
		    1000.0),_));
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (Print_nupec_message_states)
	    format((SI_Long)3L,Terminal_io,"~%Group ~a received...",
		    extra_argument);
    }
    else if (EQ(control_message,Qgroup_received)) {
	svref_arg_1 = Current_source_nupec_synchronization;
	SVREF(svref_arg_1,FIX((SI_Long)7L)) = extra_argument;
	if (Print_nupec_message_states)
	    format((SI_Long)3L,Terminal_io,"~%Group ~a received...",
		    extra_argument);
	if (FIXNUM_EQ(extra_argument,
		ISVREF(Current_source_nupec_synchronization,(SI_Long)6L)) 
		&&  !TRUEP(ISVREF(Current_source_nupec_synchronization,
		(SI_Long)1L))) {
	    svref_arg_1 = Current_source_nupec_synchronization;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = Nil;
	    svref_arg_1 = Current_source_nupec_synchronization;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = 
		    Qwait_for_final_acknowledgement;
	    write_end_of_synch_for_nupec_synchronize_control_message();
	    if (Print_nupec_message_states)
		format((SI_Long)2L,Terminal_io,"~%Waiting for final ack...");
	}
	svref_arg_1 = Current_source_nupec_synchronization;
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    }
    else if (EQ(control_message,Qend_of_synchronization)) {
	reclaim_target_nupec_synchronization_1(Current_target_nupec_synchronization);
	Current_target_nupec_synchronization = Nil;
	system_resume();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	graph = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qgraph);
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
	      temp_3 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3)
	      goto end_loop_1;
	  graph = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & (SI_Long)1L)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(graph,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	      gensymed_symbol_1 = graph;
	      gensymed_symbol_2 = Nil;
	      inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(graph,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	      gensymed_symbol_1 = graph;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	invoke_rules_for_nupec_synchronization_chaining();
	write_confirmed_for_nupec_synchronize_control_message();
	if (Print_nupec_message_states)
	    format((SI_Long)2L,Terminal_io,"~%End received.");
    }
    else if (EQ(control_message,Qend_of_synchronization_confirmed_thank_you)) {
	svref_arg_1 = Current_source_nupec_synchronization;
	SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	if (Print_nupec_message_states)
	    format((SI_Long)2L,Terminal_io,"~%End confirmed.");
    }
    else if (EQ(control_message,Qabort_synchronize)) {
	if (Current_target_nupec_synchronization) {
	    abort_target_nupec_synchronization(extra_argument);
	    reclaim_text_string(extra_argument);
	}
	else if (Current_source_nupec_synchronization) {
	    svref_arg_1 = Current_source_nupec_synchronization;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	    svref_arg_1 = Current_source_nupec_synchronization;
	    SVREF(svref_arg_1,FIX((SI_Long)5L)) = extra_argument;
	}
	else
	    reclaim_text_string(extra_argument);
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_nupec_synchronize_control_message;  /* handle-icp-nupec-synchronize-control-message */

/* HANDLE-ICP-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE */
Object handle_icp_nupec_synchronize_control_message()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object control_message, extra_argument, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(221,54);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qnupec_synchronize_control_message,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcontrol_message,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcontrol_message,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    control_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      control_message = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      control_message = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qextra_argument,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_nupec_synchronize_datum();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qextra_argument,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    extra_argument = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  extra_argument = read_icp_nupec_synchronize_datum();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nupec_synchronize_control_message__body(control_message,
			extra_argument);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize_control_message,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcontrol_message,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcontrol_message,string_constant_7,Qargument,
			      T,result_of_read,Nil,Nil);
		  control_message = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    control_message = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    control_message = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qextra_argument,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_nupec_synchronize_datum();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qextra_argument,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  extra_argument = result_of_read;
		POP_SPECIAL();
	    }
	    else
		extra_argument = read_icp_nupec_synchronize_datum();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nupec_synchronize_control_message__body(control_message,
		      extra_argument);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_nupec_synchronize_control_message,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_nupec_synchronize_control_message,top,Nil);
		goto end_handle_icp_nupec_synchronize_control_message;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qnupec_synchronize_control_message,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  control_message = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcontrol_message,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_nupec_synchronize_control_message;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcontrol_message,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    control_message = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_nupec_synchronize_control_message;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      control_message = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      control_message = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  extra_argument = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qextra_argument,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_nupec_synchronize_datum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(control_message);
			resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nupec_synchronize_control_message;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qextra_argument,string_constant_4,
				Qargument,T,result_of_read,Nil,Nil);
		    extra_argument = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(control_message);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize_control_message;
		  }
		  extra_argument = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nupec_synchronize_control_message__body(control_message,
			extra_argument);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_synchronize_control_message,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		control_message = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcontrol_message,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_nupec_synchronize_control_message;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcontrol_message,string_constant_7,Qargument,
			      T,result_of_read,Nil,Nil);
		  control_message = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_nupec_synchronize_control_message;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    control_message = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    control_message = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		extra_argument = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qextra_argument,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_nupec_synchronize_datum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(control_message);
		      resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nupec_synchronize_control_message;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qextra_argument,string_constant_4,Qargument,
			      T,result_of_read,Nil,Nil);
		  extra_argument = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_nupec_synchronize_datum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(control_message);
		    resumable_icp_push(Qhandle_icp_nupec_synchronize_control_message);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nupec_synchronize_control_message;
		}
		extra_argument = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nupec_synchronize_control_message__body(control_message,
		      extra_argument);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_nupec_synchronize_control_message:
    return result;
}

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* REASON-TO-REJECT-NUPEC-SYNCHRONIZATION? */
Object reason_to_reject_nupec_synchronization_qm()
{
    x_note_fn_call(221,55);
    if ( !TRUEP(System_is_running))
	return copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)34L));
    else if (Current_target_nupec_synchronization)
	return copy_constant_wide_string_given_length(array_constant_3,
		FIX((SI_Long)41L));
    else
	return VALUES_1(Nil);
}

static Object Qnupec_history_block;  /* nupec-history-block */

static Object Qwrite_icp_nupec_history_block;  /* write-icp-nupec-history-block */

static Object Qblock_1;            /* #:block */

/* WRITE-ICP-NUPEC-HISTORY-BLOCK */
Object write_icp_nupec_history_block(nupec_history_block)
    Object nupec_history_block;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object gensymed_symbol, values_to_send, element_index, history_buffer;
    Object history_g2_time, result_of_write, temp_2, resumable_icp_state_1;
    Object icp_suspend_1, top, tag_temp, history_gensym_time_1, temp_3, v1, v2;
    Object v3;
    SI_Long ab_loop_repeat_, history_gensym_time;
    char temp_1;
    double temp, gensymed_symbol_1, arg, arg_1;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(221,56);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_history_block,
			string_constant_1,Qvalue,T,nupec_history_block,Nil,
			Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      gensymed_symbol = nupec_history_block;
	      values_to_send = CAR(gensymed_symbol);
	      gensymed_symbol = CDR(gensymed_symbol);
	      element_index = CAR(gensymed_symbol);
	      gensymed_symbol = CDR(gensymed_symbol);
	      history_buffer = CAR(gensymed_symbol);
	      write_icp_unsigned_integer(values_to_send);
	      ab_loop_repeat_ = IFIX(values_to_send);
	    next_loop:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      write_icp_nupec_synchronize_datum(get_history_value_for_cascaded_ring_buffer(history_buffer,
		      element_index));
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		  history_g2_time = get_history_g2_time(2,history_buffer,
			  CDR(element_index));
		  temp = DOUBLE_FLOAT_TO_DOUBLE(history_g2_time);
		  gensymed_symbol_1 = temp - 
			  DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
			  (double)IFIX(Gensym_time_at_start);
		  arg = gensymed_symbol_1;
		  arg_1 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		  temp_1 = arg > arg_1 &&  
			  !inline_nanp_for_comparison(arg) ?  
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  if (temp_1);
		  else {
		      arg = gensymed_symbol_1;
		      arg_1 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		      temp_1 = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		  }
		  history_gensym_time = temp_1 ? 
			  IFIX(Most_negative_fixnum) : 
			  inline_floor_1(gensymed_symbol_1);
		  write_icp_integer(FIX(history_gensym_time));
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      increment_active_element_index_for_cascaded_ring_buffer(element_index,
		      history_buffer);
	      goto next_loop;
	    end_loop:
	      result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_history_block,string_constant_1,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp_2 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    gensymed_symbol = nupec_history_block;
	    values_to_send = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    element_index = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    history_buffer = CAR(gensymed_symbol);
	    write_icp_unsigned_integer(values_to_send);
	    ab_loop_repeat_ = IFIX(values_to_send);
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    write_icp_nupec_synchronize_datum(get_history_value_for_cascaded_ring_buffer(history_buffer,
		    element_index));
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		history_g2_time = get_history_g2_time(2,history_buffer,
			CDR(element_index));
		temp = DOUBLE_FLOAT_TO_DOUBLE(history_g2_time);
		gensymed_symbol_1 = temp - 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
			(double)IFIX(Gensym_time_at_start);
		arg = gensymed_symbol_1;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp_1);
		else {
		    arg = gensymed_symbol_1;
		    arg_1 = 
			    DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		history_gensym_time = temp_1 ? IFIX(Most_negative_fixnum) :
			 inline_floor_1(gensymed_symbol_1);
		write_icp_integer(FIX(history_gensym_time));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    increment_active_element_index_for_cascaded_ring_buffer(element_index,
		    history_buffer);
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = Qnil;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_nupec_history_block,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qwrite_icp_nupec_history_block,top,Nil);
		goto end_write_icp_nupec_history_block;
	    }
	}
	nupec_history_block = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : nupec_history_block;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qnupec_history_block,
			string_constant_1,Qvalue,T,nupec_history_block,Nil,
			Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      gensymed_symbol = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : nupec_history_block;
	      values_to_send = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : CAR(gensymed_symbol);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)))
		  gensymed_symbol = CDR(gensymed_symbol);
	      element_index = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : CAR(gensymed_symbol);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)))
		  gensymed_symbol = CDR(gensymed_symbol);
	      history_buffer = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : CAR(gensymed_symbol);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_2 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_2) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_2) && FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_2)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			default:
			  break;
		      }
	      }
	    l1:
	      if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(values_to_send))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      ab_loop_repeat_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : IFIX(values_to_send);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_2;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    resume:
	      tag_temp = UNIQUE_TAG(Qblock_1);
	      if (PUSH_CATCH(tag_temp,0)) {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_2 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_2) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			      FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_2)) {
			    case 1:
			      goto l1_1;
			      break;
			    case 2:
			      goto l2_1;
			      break;
			    default:
			      break;
			  }
		  }
		l1_1:
		  if (EQ(icp_suspend_1,
			  write_icp_nupec_synchronize_datum(get_history_value_for_cascaded_ring_buffer(history_buffer,
			  element_index)))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(Icp_suspend);
		      THROW(tag_temp,result);
		  }
		l2_1:
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      history_g2_time = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      get_history_g2_time(2,history_buffer,
			      CDR(element_index));
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  history_gensym_time_1 = resumable_icp_pop();
		      else {
			  temp = DOUBLE_FLOAT_TO_DOUBLE(history_g2_time);
			  gensymed_symbol_1 = temp - 
				  DFLOAT_ISAREF_1(G2_time_at_start,
				  (SI_Long)0L) + 
				  (double)IFIX(Gensym_time_at_start);
			  arg = gensymed_symbol_1;
			  arg_1 = 
				  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
			  temp_1 = arg > arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
			  if (temp_1);
			  else {
			      arg = gensymed_symbol_1;
			      arg_1 = 
				      DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
			      temp_1 = arg < arg_1 &&  
				      !inline_nanp_for_comparison(arg) ?  
				      !inline_nanp_for_comparison(arg_1) : 
				      TRUEP(Qnil);
			  }
			  history_gensym_time_1 = temp_1 ? 
				  Most_negative_fixnum : 
				  LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_1));
		      }
		      if (EQ(icp_suspend_1,
			      write_icp_integer(history_gensym_time_1))) {
			  resumable_icp_push(history_gensym_time_1);
			  resumable_icp_push(history_g2_time);
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  THROW(tag_temp,result);
		      }
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  result = increment_active_element_index_for_cascaded_ring_buffer(element_index,
			  history_buffer);
		  THROW(tag_temp,result);
	      }
	      else
		  temp_3 = CATCH_VALUES();
	      POP_CATCH(0);
	      if (EQ(icp_suspend_1,temp_3)) {
		  resumable_icp_push(FIX(ab_loop_repeat_));
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      result = VALUES_1(Qnil);
	      goto end_block;
	    end_block:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(history_buffer);
		  resumable_icp_push(element_index);
		  resumable_icp_push(values_to_send);
		  resumable_icp_push(gensymed_symbol);
		  resumable_icp_push(nupec_history_block);
		  resumable_icp_push(Qwrite_icp_nupec_history_block);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_nupec_history_block;
	      }
	      temp_2 = v1;
	      result_of_write = temp_2;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnupec_history_block,string_constant_1,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp_2 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    gensymed_symbol = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : nupec_history_block;
	    values_to_send = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : CAR(gensymed_symbol);
	    if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)))
		gensymed_symbol = CDR(gensymed_symbol);
	    element_index = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : CAR(gensymed_symbol);
	    if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)))
		gensymed_symbol = CDR(gensymed_symbol);
	    history_buffer = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : CAR(gensymed_symbol);
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		temp_2 = resumable_icp_pop();
		if (! !(FIXNUMP(temp_2) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp_2) && FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp_2)) {
		      case 1:
			goto l1_2;
			break;
		      case 2:
			goto l2_2;
			break;
		      default:
			break;
		    }
	    }
	  l1_2:
	    if (EQ(icp_suspend_1,write_icp_unsigned_integer(values_to_send))) {
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_2:
	    ab_loop_repeat_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : IFIX(values_to_send);
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	  resume_1:
	    tag_temp = UNIQUE_TAG(Qblock_1);
	    if (PUSH_CATCH(tag_temp,0)) {
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_2 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_2) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_2) && 
			    FIXNUM_LE(temp_2,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_2)) {
			  case 1:
			    goto l1_3;
			    break;
			  case 2:
			    goto l2_3;
			    break;
			  default:
			    break;
			}
		}
	      l1_3:
		if (EQ(icp_suspend_1,
			write_icp_nupec_synchronize_datum(get_history_value_for_cascaded_ring_buffer(history_buffer,
			element_index)))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(Icp_suspend);
		    THROW(tag_temp,result);
		}
	      l2_3:
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    history_g2_time = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : get_history_g2_time(2,
			    history_buffer,CDR(element_index));
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			history_gensym_time_1 = resumable_icp_pop();
		    else {
			temp = DOUBLE_FLOAT_TO_DOUBLE(history_g2_time);
			gensymed_symbol_1 = temp - 
				DFLOAT_ISAREF_1(G2_time_at_start,
				(SI_Long)0L) + 
				(double)IFIX(Gensym_time_at_start);
			arg = gensymed_symbol_1;
			arg_1 = 
				DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
			temp_1 = arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) ?  
				!inline_nanp_for_comparison(arg_1) : 
				TRUEP(Qnil);
			if (temp_1);
			else {
			    arg = gensymed_symbol_1;
			    arg_1 = 
				    DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
			    temp_1 = arg < arg_1 &&  
				    !inline_nanp_for_comparison(arg) ?  
				    !inline_nanp_for_comparison(arg_1) : 
				    TRUEP(Qnil);
			}
			history_gensym_time_1 = temp_1 ? 
				Most_negative_fixnum : 
				LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_1));
		    }
		    if (EQ(icp_suspend_1,
			    write_icp_integer(history_gensym_time_1))) {
			resumable_icp_push(history_gensym_time_1);
			resumable_icp_push(history_g2_time);
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			THROW(tag_temp,result);
		    }
		}
		POP_LOCAL_ALLOCATION(0,0);
		result = increment_active_element_index_for_cascaded_ring_buffer(element_index,
			history_buffer);
		THROW(tag_temp,result);
	    }
	    else
		temp_3 = CATCH_VALUES();
	    POP_CATCH(0);
	    if (EQ(icp_suspend_1,temp_3)) {
		resumable_icp_push(FIX(ab_loop_repeat_));
		resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    result = VALUES_1(Qnil);
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		resumable_icp_push(history_buffer);
		resumable_icp_push(element_index);
		resumable_icp_push(values_to_send);
		resumable_icp_push(gensymed_symbol);
		resumable_icp_push(nupec_history_block);
		resumable_icp_push(Qwrite_icp_nupec_history_block);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_nupec_history_block;
	    }
	    temp_2 = v1;
	}
    }
    result = VALUES_1(temp_2);
  end_write_icp_nupec_history_block:
    return result;
}

/* RECLAIM-NUPEC-HISTORY-BLOCK */
Object reclaim_nupec_history_block(nupec_history_block)
    Object nupec_history_block;
{
    x_note_fn_call(221,57);
    reclaim_if_managed_array(CDR(nupec_history_block));
    reclaim_gensym_cons_1(nupec_history_block);
    return VALUES_1(Nil);
}

static Object Qread_icp_nupec_history_block;  /* read-icp-nupec-history-block */

/* READ-ICP-NUPEC-HISTORY-BLOCK */
Object read_icp_nupec_history_block()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, array;
    Object temp, svref_new_value, result_of_read, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long history_length, array_size, value_index, ab_loop_bind_;
    SI_Long svref_arg_2, gensymed_symbol;
    Declare_special(1);
    Object result;

    x_note_fn_call(221,58);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_history_block,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      history_length = IFIX(read_icp_unsigned_integer());
	      array_size = history_length * (SI_Long)2L;
	      array = Nil;
	      if (history_length != (SI_Long)0L) {
		  array = allocate_managed_array(2,FIX(array_size),T);
		  value_index = (SI_Long)0L;
		  ab_loop_bind_ = array_size;
		next_loop:
		  if (value_index >= ab_loop_bind_)
		      goto end_loop;
		  if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = value_index + 
			      IFIX(Managed_array_index_offset);
		      temp = read_icp_nupec_synchronize_datum();
		      ISVREF(array,svref_arg_2) = temp;
		  }
		  else {
		      temp = ISVREF(array,(value_index >>  -  - 
			      (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2 = value_index & (SI_Long)1023L;
		      svref_new_value = read_icp_nupec_synchronize_datum();
		      ISVREF(temp,svref_arg_2) = svref_new_value;
		  }
		  gensymed_symbol = value_index + (SI_Long)1L;
		  if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = gensymed_symbol + 
			      IFIX(Managed_array_index_offset);
		      temp = read_icp_integer();
		      ISVREF(array,svref_arg_2) = temp;
		  }
		  else {
		      temp = ISVREF(array,(gensymed_symbol >>  -  - 
			      (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
		      svref_new_value = read_icp_integer();
		      ISVREF(temp,svref_arg_2) = svref_new_value;
		  }
		  value_index = value_index + (SI_Long)2L;
		  goto next_loop;
		end_loop:;
	      }
	      result_of_read = gensym_cons_1(FIX(history_length),array);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_history_block,string_constant_1,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp_1 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    history_length = IFIX(read_icp_unsigned_integer());
	    array_size = history_length * (SI_Long)2L;
	    array = Nil;
	    if (history_length != (SI_Long)0L) {
		array = allocate_managed_array(2,FIX(array_size),T);
		value_index = (SI_Long)0L;
		ab_loop_bind_ = array_size;
	      next_loop_1:
		if (value_index >= ab_loop_bind_)
		    goto end_loop_1;
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = value_index + 
			    IFIX(Managed_array_index_offset);
		    temp = read_icp_nupec_synchronize_datum();
		    ISVREF(array,svref_arg_2) = temp;
		}
		else {
		    temp = ISVREF(array,(value_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = value_index & (SI_Long)1023L;
		    svref_new_value = read_icp_nupec_synchronize_datum();
		    ISVREF(temp,svref_arg_2) = svref_new_value;
		}
		gensymed_symbol = value_index + (SI_Long)1L;
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol + 
			    IFIX(Managed_array_index_offset);
		    temp = read_icp_integer();
		    ISVREF(array,svref_arg_2) = temp;
		}
		else {
		    temp = ISVREF(array,(gensymed_symbol >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
		    svref_new_value = read_icp_integer();
		    ISVREF(temp,svref_arg_2) = svref_new_value;
		}
		value_index = value_index + (SI_Long)2L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    temp_1 = gensym_cons_1(FIX(history_length),array);
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_nupec_history_block,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qread_icp_nupec_history_block,top,Nil);
		goto end_read_icp_nupec_history_block;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnupec_history_block,
			string_constant_1,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  history_length = IFIX(resumable_icp_pop());
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_nupec_history_block);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_nupec_history_block;
		  }
		  history_length = IFIX(value);
	      }
	      array_size = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : history_length * (SI_Long)2L;
	      array = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) || history_length != (SI_Long)0L) {
		  if ( !(resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)))
		      array = allocate_managed_array(2,FIX(array_size),T);
		  value_index = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  IFIX(resumable_icp_pop()) : (SI_Long)0L;
		  ab_loop_bind_ = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  IFIX(resumable_icp_pop()) : array_size;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil))
		      goto resume;
		next_loop_2:
		  if (value_index >= ab_loop_bind_)
		      goto end_loop_2;
		resume:
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1;
			      break;
			    case 2:
			      goto l2;
			      break;
			    default:
			      break;
			  }
		  }
		l1:
		  if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = value_index + 
			      IFIX(Managed_array_index_offset);
		      value = read_icp_nupec_synchronize_datum();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  goto end_block;
		      }
		      ISVREF(array,svref_arg_2) = value;
		  }
		  else {
		      temp = ISVREF(array,(value_index >>  -  - 
			      (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2 = value_index & (SI_Long)1023L;
		      value = read_icp_nupec_synchronize_datum();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  goto end_block;
		      }
		      ISVREF(temp,svref_arg_2) = value;
		  }
		l2:
		  gensymed_symbol = value_index + (SI_Long)1L;
		  if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = gensymed_symbol + 
			      IFIX(Managed_array_index_offset);
		      value = read_icp_integer();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  goto end_block;
		      }
		      temp_1 = ISVREF(array,svref_arg_2) = value;
		  }
		  else {
		      temp = ISVREF(array,(gensymed_symbol >>  -  - 
			      (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
		      value = read_icp_integer();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  goto end_block;
		      }
		      temp_1 = ISVREF(temp,svref_arg_2) = value;
		  }
		  goto end_block;
		end_block:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(value_index));
		      resumable_icp_push(array);
		      resumable_icp_push(FIX(array_size));
		      resumable_icp_push(FIX(history_length));
		      resumable_icp_push(Qread_icp_nupec_history_block);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_nupec_history_block;
		  }
		  value_index = value_index + (SI_Long)2L;
		  goto next_loop_2;
		end_loop_2:;
	      }
	      result_of_read = gensym_cons_1(FIX(history_length),array);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnupec_history_block,string_constant_1,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp_1 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		history_length = IFIX(resumable_icp_pop());
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_nupec_history_block);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_nupec_history_block;
		}
		history_length = IFIX(value);
	    }
	    array_size = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : history_length * (SI_Long)2L;
	    array = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) || history_length != (SI_Long)0L) {
		if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			 TRUEP(Nil)))
		    array = allocate_managed_array(2,FIX(array_size),T);
		value_index = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			IFIX(resumable_icp_pop()) : (SI_Long)0L;
		ab_loop_bind_ = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			IFIX(resumable_icp_pop()) : array_size;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil))
		    goto resume_1;
	      next_loop_3:
		if (value_index >= ab_loop_bind_)
		    goto end_loop_3;
	      resume_1:
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = value_index + 
			    IFIX(Managed_array_index_offset);
		    value = read_icp_nupec_synchronize_datum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp = ISVREF(array,(value_index >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = value_index & (SI_Long)1023L;
		    value = read_icp_nupec_synchronize_datum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    ISVREF(temp,svref_arg_2) = value;
		}
	      l2_1:
		gensymed_symbol = value_index + (SI_Long)1L;
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol + 
			    IFIX(Managed_array_index_offset);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    temp_1 = ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp = ISVREF(array,(gensymed_symbol >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    temp_1 = ISVREF(temp,svref_arg_2) = value;
		}
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(value_index));
		    resumable_icp_push(array);
		    resumable_icp_push(FIX(array_size));
		    resumable_icp_push(FIX(history_length));
		    resumable_icp_push(Qread_icp_nupec_history_block);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_nupec_history_block;
		}
		value_index = value_index + (SI_Long)2L;
		goto next_loop_3;
	      end_loop_3:;
	    }
	    temp_1 = gensym_cons_1(FIX(history_length),array);
	}
    }
    result = VALUES_1(temp_1);
  end_read_icp_nupec_history_block:
    return result;
}

static Object Qsend_icp_receive_nupec_synchronize_history_block;  /* send-icp-receive-nupec-synchronize-history-block */

static Object Qreceive_nupec_synchronize_history_block;  /* receive-nupec-synchronize-history-block */

static Object Qv_or_p;             /* v-or-p */

static Object Qhistory_block;      /* history-block */

/* SEND-ICP-RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK */
Object send_icp_receive_nupec_synchronize_history_block(v_or_p,history_block)
    Object v_or_p, history_block;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(221,59);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_receive_nupec_synchronize_history_block;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(v_or_p,(SI_Long)2L),
		  Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_nupec_synchronize_variable_or_parameter(v_or_p);
	  v_or_p = temp_1;
	  start_writing_icp_message(FIX((SI_Long)202L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qreceive_nupec_synchronize_history_block,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qv_or_p,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(v_or_p);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qv_or_p,string_constant_7,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(v_or_p);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhistory_block,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_nupec_history_block(history_block);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhistory_block,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_nupec_history_block(history_block);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qreceive_nupec_synchronize_history_block,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qv_or_p,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(v_or_p);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qv_or_p,string_constant_7,Qargument,Nil,
				Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(v_or_p);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhistory_block,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_nupec_history_block(history_block);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhistory_block,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_nupec_history_block(history_block);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_receive_nupec_synchronize_history_block,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_receive_nupec_synchronize_history_block,
			top,Nil);
		goto end_send_icp_receive_nupec_synchronize_history_block;
	    }
	}
	v_or_p = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : v_or_p;
	history_block = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : history_block;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_receive_nupec_synchronize_history_block;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(v_or_p,(SI_Long)2L),
		  Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      v_or_p = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_nupec_synchronize_variable_or_parameter(v_or_p);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      v_or_p = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)202L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qreceive_nupec_synchronize_history_block,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qv_or_p,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(v_or_p))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qv_or_p,string_constant_7,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(v_or_p))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qhistory_block,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_nupec_history_block(history_block))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qhistory_block,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_nupec_history_block(history_block))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qreceive_nupec_synchronize_history_block,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qv_or_p,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(v_or_p))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qv_or_p,string_constant_7,Qargument,Nil,
				Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(v_or_p))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qhistory_block,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_nupec_history_block(history_block))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qhistory_block,string_constant_4,Qargument,
				Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_nupec_history_block(history_block))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(history_block);
	      resumable_icp_push(v_or_p);
	      resumable_icp_push(Qsend_icp_receive_nupec_synchronize_history_block);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_nupec_synchronize_history_block;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_nupec_synchronize_history_block:
    return result;
}

static Object Qfloat_array;        /* float-array */

static Object string_constant_9;   /* "Reception of a NUPEC Synchronize could find no local ~
				    *                  variable or parameter for the designation "
				    */

/* HANDLE-ICP-RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK--BODY */
Object handle_icp_receive_nupec_synchronize_history_block__body(v_or_p,
	    history_block)
    Object v_or_p, history_block;
{
    Object history_array_qm, history_qm, time_offset, temp, ring_buffer;
    Object history_base_time, value, history_gensym_time;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, index_2, vector_1, store_managed_number_or_value_arg;
    Object new_managed_array, element_index, temp_4, index_3;
    Object oldest_active_element_index_for_ring_buffer, frame_qm;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object managed_number_or_value, old_history_qm;
    SI_Long history_values, history_received, index_1, ab_loop_bind_;
    SI_Long gensymed_symbol;
    SI_Long elt_1_of_parallel_vector_values;
    SI_Long temp_3;
    SI_Long store_managed_number_or_value_arg_1;
    SI_Long incff_1_arg, bv16_length, aref_new_value_1, length_1;
    double aref_new_value;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(221,60);
    history_values = IFIX(CAR(history_block));
    history_array_qm = CDR(history_block);
    history_qm = ISVREF(v_or_p,(SI_Long)8L);
    history_received = IFIX(ISVREF(v_or_p,(SI_Long)7L));
    time_offset = ISVREF(Current_target_nupec_synchronization,(SI_Long)3L);
    if (history_array_qm) {
	if (history_qm) {
	    temp = ISVREF(history_qm,(SI_Long)4L);
	    ring_buffer = CAR(temp);
	}
	else
	    ring_buffer = Nil;
	history_base_time = Nil;
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = history_values * (SI_Long)2L;
	value = Nil;
	history_gensym_time = Nil;
	if (history_qm) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
		aref_new_value = 
			inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L));
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		history_base_time = new_float;
		SVREF(history_qm,FIX((SI_Long)10L)) = history_base_time;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value = FIXNUM_LE(ISVREF(history_array_qm,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(history_array_qm,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(history_array_qm,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	gensymed_symbol = index_1 + (SI_Long)1L;
	history_gensym_time = FIXNUM_LE(ISVREF(history_array_qm,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(history_array_qm,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(history_array_qm,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	if (history_qm) {
	    elt_1_of_parallel_vector_values = 
		    inline_floor_1((double)IFIX(FIXNUM_MINUS(FIXNUM_ADD(history_gensym_time,
		    time_offset),Gensym_time_at_start)) + 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) - 
		    DFLOAT_ISAREF_1(history_base_time,(SI_Long)0L));
	    if (ISVREF(ring_buffer,(SI_Long)3L)) {
		index_2 = ISVREF(ring_buffer,(SI_Long)1L);
		temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
		SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
		vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    store_managed_number_or_value_arg = value;
		    temp_2 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),store_managed_number_or_value_arg);
		    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(vector_1,temp_1) = temp_2;
		    }
		    else {
			temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_2;
		    }
		}
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else if (FLOATP(value)) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else {
		    new_managed_array = allocate_managed_array(1,
			    ISVREF(vector_1,(SI_Long)1L));
		    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
			element_index = ISVREF(ring_buffer,(SI_Long)2L);
		      next_loop_1:
			if (FIXNUM_LE(ISVREF(new_managed_array,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    temp_1 = FIXNUM_ADD(element_index,
				    Managed_array_index_offset);
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    SVREF(new_managed_array,temp_1) = new_float;
			}
			else {
			    temp_1 = ISVREF(new_managed_array,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    temp_3 = IFIX(element_index) & (SI_Long)1023L;
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    ISVREF(temp_1,temp_3) = new_float;
			}
			if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
				(SI_Long)1L)))
			    goto end_loop_1;
			element_index = FIXNUM_EQ(element_index,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? FIX((SI_Long)0L) : 
				FIXNUM_ADD1(element_index);
			goto next_loop_1;
		      end_loop_1:;
		    }
		    reclaim_managed_float_array(vector_1);
		    SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
		    temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    store_managed_number_or_value_arg = value;
		    temp_4 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),store_managed_number_or_value_arg);
		    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_2 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(temp_1,temp_2) = temp_4;
		    }
		    else {
			temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_4;
		    }
		}
		vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    store_managed_number_or_value_arg_1 = 
			    elt_1_of_parallel_vector_values;
		    temp_2 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),
			    LONG_TO_FIXNUM(store_managed_number_or_value_arg_1));
		    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(vector_1,temp_1) = temp_2;
		    }
		    else {
			temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_2;
		    }
		}
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values)) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values))) 
			== (SI_Long)1L) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values),
			    (SI_Long)0L);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else if (FLOATP(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values))) 
			    {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    temp = LONG_TO_FIXNUM(elt_1_of_parallel_vector_values);
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else {
		    new_managed_array = allocate_managed_array(1,
			    ISVREF(vector_1,(SI_Long)1L));
		    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
			element_index = ISVREF(ring_buffer,(SI_Long)2L);
		      next_loop_2:
			if (FIXNUM_LE(ISVREF(new_managed_array,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    temp_1 = FIXNUM_ADD(element_index,
				    Managed_array_index_offset);
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    SVREF(new_managed_array,temp_1) = new_float;
			}
			else {
			    temp_1 = ISVREF(new_managed_array,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    temp_3 = IFIX(element_index) & (SI_Long)1023L;
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    ISVREF(temp_1,temp_3) = new_float;
			}
			if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
				(SI_Long)1L)))
			    goto end_loop_2;
			element_index = FIXNUM_EQ(element_index,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? FIX((SI_Long)0L) : 
				FIXNUM_ADD1(element_index);
			goto next_loop_2;
		      end_loop_2:;
		    }
		    reclaim_managed_float_array(vector_1);
		    SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
		    temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
		    store_managed_number_or_value_arg_1 = 
			    elt_1_of_parallel_vector_values;
		    temp_4 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),
			    LONG_TO_FIXNUM(store_managed_number_or_value_arg_1));
		    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_2 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(temp_1,temp_2) = temp_4;
		    }
		    else {
			temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_4;
		    }
		}
		SVREF(ring_buffer,FIX((SI_Long)3L)) = Nil;
	    }
	    else {
		index_3 = ISVREF(ring_buffer,(SI_Long)1L);
		oldest_active_element_index_for_ring_buffer = 
			ISVREF(ring_buffer,(SI_Long)2L);
		if (FIXNUM_EQ(FIXNUM_GE(index_3,
			oldest_active_element_index_for_ring_buffer) ? 
			FIXNUM_ADD1(FIXNUM_MINUS(index_3,
			oldest_active_element_index_for_ring_buffer)) : 
			FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_3,
			ISVREF(ring_buffer,(SI_Long)4L)),
			oldest_active_element_index_for_ring_buffer)),
			ISVREF(ring_buffer,(SI_Long)4L)))
		    expand_history_ring_buffer(ring_buffer);
		index_3 = ISVREF(ring_buffer,(SI_Long)1L);
		temp_3 = FIXNUM_EQ(index_3,FIXNUM_SUB1(ISVREF(ring_buffer,
			(SI_Long)4L))) ? (SI_Long)0L : 
			IFIX(FIXNUM_ADD1(index_3));
		ISVREF(ring_buffer,(SI_Long)1L) = FIX(temp_3);
		index_2 = ISVREF(ring_buffer,(SI_Long)1L);
		temp_1 = FIXNUM_ADD1(ISVREF(ring_buffer,(SI_Long)5L));
		SVREF(ring_buffer,FIX((SI_Long)5L)) = temp_1;
		vector_1 = ISVREF(ring_buffer,(SI_Long)6L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    store_managed_number_or_value_arg = value;
		    temp_2 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),store_managed_number_or_value_arg);
		    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(vector_1,temp_1) = temp_2;
		    }
		    else {
			temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_2;
		    }
		}
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else if (FLOATP(value)) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else {
		    new_managed_array = allocate_managed_array(1,
			    ISVREF(vector_1,(SI_Long)1L));
		    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
			element_index = ISVREF(ring_buffer,(SI_Long)2L);
		      next_loop_3:
			if (FIXNUM_LE(ISVREF(new_managed_array,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    temp_1 = FIXNUM_ADD(element_index,
				    Managed_array_index_offset);
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    SVREF(new_managed_array,temp_1) = new_float;
			}
			else {
			    temp_1 = ISVREF(new_managed_array,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    temp_3 = IFIX(element_index) & (SI_Long)1023L;
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    ISVREF(temp_1,temp_3) = new_float;
			}
			if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
				(SI_Long)1L)))
			    goto end_loop_3;
			element_index = FIXNUM_EQ(element_index,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? FIX((SI_Long)0L) : 
				FIXNUM_ADD1(element_index);
			goto next_loop_3;
		      end_loop_3:;
		    }
		    reclaim_managed_float_array(vector_1);
		    SVREF(ring_buffer,FIX((SI_Long)6L)) = new_managed_array;
		    temp_1 = ISVREF(ring_buffer,(SI_Long)6L);
		    store_managed_number_or_value_arg = value;
		    temp_4 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),store_managed_number_or_value_arg);
		    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_2 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(temp_1,temp_2) = temp_4;
		    }
		    else {
			temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_4;
		    }
		}
		vector_1 = ISVREF(ring_buffer,(SI_Long)7L);
		if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,
			(SI_Long)0L),Managed_array_unique_marker)) {
		    store_managed_number_or_value_arg_1 = 
			    elt_1_of_parallel_vector_values;
		    temp_2 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(vector_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(vector_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),
			    LONG_TO_FIXNUM(store_managed_number_or_value_arg_1));
		    if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_1 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(vector_1,temp_1) = temp_2;
		    }
		    else {
			temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_2;
		    }
		}
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values)) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values))) 
			== (SI_Long)1L) {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values),
			    (SI_Long)0L);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else if (FLOATP(LONG_TO_FIXNUM(elt_1_of_parallel_vector_values))) 
			    {
		    temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_3 = IFIX(index_2) & (SI_Long)1023L;
		    temp = LONG_TO_FIXNUM(elt_1_of_parallel_vector_values);
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
		    DFLOAT_ISASET_1(temp_1,temp_3,aref_new_value);
		}
		else {
		    new_managed_array = allocate_managed_array(1,
			    ISVREF(vector_1,(SI_Long)1L));
		    if ( !TRUEP(ISVREF(ring_buffer,(SI_Long)3L))) {
			element_index = ISVREF(ring_buffer,(SI_Long)2L);
		      next_loop_4:
			if (FIXNUM_LE(ISVREF(new_managed_array,
				(SI_Long)1L),Maximum_in_place_array_size)) {
			    temp_1 = FIXNUM_ADD(element_index,
				    Managed_array_index_offset);
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    SVREF(new_managed_array,temp_1) = new_float;
			}
			else {
			    temp_1 = ISVREF(new_managed_array,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L);
			    temp_3 = IFIX(element_index) & (SI_Long)1023L;
			    amf_available_array_cons_qm = 
				    ISVREF(Vector_of_simple_float_array_pools,
				    (SI_Long)1L);
			    if (amf_available_array_cons_qm) {
				amf_array = M_CAR(amf_available_array_cons_qm);
				temp_2 = Vector_of_simple_float_array_pools;
				temp_4 = M_CDR(amf_available_array_cons_qm);
				SVREF(temp_2,FIX((SI_Long)1L)) = temp_4;
				inline_note_reclaim_cons(amf_available_array_cons_qm,
					Qfloat_array);
				if (ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_2 = 
					    ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_2) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				else {
				    temp_2 = 
					    Available_float_array_conses_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				    temp_2 = 
					    Available_float_array_conses_tail_vector;
				    temp_4 = Current_thread_index;
				    SVREF(temp_2,temp_4) = 
					    amf_available_array_cons_qm;
				}
				M_CDR(amf_available_array_cons_qm) = Nil;
				amf_result = amf_array;
			    }
			    else {
				atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					FIX((SI_Long)1L));
				atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				amf_result = 
					generate_float_vector(FIX((SI_Long)1L));
			    }
			    new_float = amf_result;
			    aref_new_value = 
				    DFLOAT_ISAREF_1(ISVREF(vector_1,
				    (IFIX(element_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(element_index) & (SI_Long)1023L);
			    DFLOAT_ISASET_1(new_float,(SI_Long)0L,
				    aref_new_value);
			    ISVREF(temp_1,temp_3) = new_float;
			}
			if (FIXNUM_EQ(element_index,ISVREF(ring_buffer,
				(SI_Long)1L)))
			    goto end_loop_4;
			element_index = FIXNUM_EQ(element_index,
				FIXNUM_SUB1(ISVREF(ring_buffer,
				(SI_Long)4L))) ? FIX((SI_Long)0L) : 
				FIXNUM_ADD1(element_index);
			goto next_loop_4;
		      end_loop_4:;
		    }
		    reclaim_managed_float_array(vector_1);
		    SVREF(ring_buffer,FIX((SI_Long)7L)) = new_managed_array;
		    temp_1 = ISVREF(ring_buffer,(SI_Long)7L);
		    store_managed_number_or_value_arg_1 = 
			    elt_1_of_parallel_vector_values;
		    temp_4 = 
			    store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(temp_1,IFIX(FIXNUM_ADD(index_2,
			    Managed_array_index_offset))) : 
			    ISVREF(ISVREF(temp_1,(IFIX(index_2) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
			    (SI_Long)1023L),
			    LONG_TO_FIXNUM(store_managed_number_or_value_arg_1));
		    if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			temp_2 = FIXNUM_ADD(index_2,
				Managed_array_index_offset);
			SVREF(temp_1,temp_2) = temp_4;
		    }
		    else {
			temp_1 = ISVREF(temp_1,(IFIX(index_2) >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			temp_3 = IFIX(index_2) & (SI_Long)1023L;
			ISVREF(temp_1,temp_3) = temp_4;
		    }
		}
	    }
	}
	if (text_string_p(value))
	    reclaim_text_string(value);
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:;
	incff_1_arg = history_values;
	history_received = history_received + incff_1_arg;
	ISVREF(v_or_p,(SI_Long)7L) = FIX(history_received);
	reclaim_managed_array(history_array_qm);
    }
    if (history_received == IFIX(ISVREF(v_or_p,(SI_Long)6L))) {
	frame_qm = ISVREF(v_or_p,(SI_Long)2L);
	if ( !TRUEP(frame_qm)) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
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
		      temp_3 = bv16_length - (SI_Long)2L;
		      aref_new_value_1 = (SI_Long)2048L & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,temp_3,
			      aref_new_value_1);
		      temp_3 = bv16_length - (SI_Long)1L;
		      aref_new_value_1 = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,temp_3,
			      aref_new_value_1);
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
			      tformat(1,string_constant_9);
			      print_designation(ISVREF(v_or_p,(SI_Long)1L));
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
	}
	else {
	    managed_number_or_value = ISVREF(v_or_p,(SI_Long)3L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		store_managed_number_or_value_arg = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		store_managed_number_or_value_arg = 
			aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else
		store_managed_number_or_value_arg = managed_number_or_value;
	    temp_1 = 
		    store_managed_number_or_value_function(ISVREF(frame_qm,
		    (SI_Long)23L),store_managed_number_or_value_arg);
	    ISVREF(frame_qm,(SI_Long)23L) = temp_1;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
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
		aref_new_value = (double)IFIX(FIXNUM_MINUS(ISVREF(v_or_p,
			(SI_Long)4L),Gensym_time_at_start)) + 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		ISVREF(frame_qm,(SI_Long)21L) = new_float;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    temp_1 = ISVREF(v_or_p,(SI_Long)5L);
	    ISVREF(frame_qm,(SI_Long)26L) = temp_1;
	    if (history_qm) {
		old_history_qm = ISVREF(frame_qm,(SI_Long)24L);
		if (old_history_qm)
		    reclaim_history_buffer(old_history_qm);
		ISVREF(frame_qm,(SI_Long)24L) = history_qm;
	    }
	}
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_receive_nupec_synchronize_history_block;  /* handle-icp-receive-nupec-synchronize-history-block */

/* HANDLE-ICP-RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK */
Object handle_icp_receive_nupec_synchronize_history_block()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read, v_or_p;
    Object history_block, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(221,61);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreceive_nupec_synchronize_history_block,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qv_or_p,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qv_or_p,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    v_or_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      v_or_p = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      v_or_p = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhistory_block,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_nupec_history_block();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhistory_block,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    history_block = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  history_block = read_icp_nupec_history_block();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_receive_nupec_synchronize_history_block__body(v_or_p,
			history_block);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreceive_nupec_synchronize_history_block,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qv_or_p,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qv_or_p,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  v_or_p = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    v_or_p = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    v_or_p = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhistory_block,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_nupec_history_block();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qhistory_block,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  history_block = result_of_read;
		POP_SPECIAL();
	    }
	    else
		history_block = read_icp_nupec_history_block();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_receive_nupec_synchronize_history_block__body(v_or_p,
		      history_block);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_receive_nupec_synchronize_history_block,
			top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_receive_nupec_synchronize_history_block,
			top,Nil);
		goto end_handle_icp_receive_nupec_synchronize_history_block;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreceive_nupec_synchronize_history_block,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  v_or_p = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qv_or_p,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_receive_nupec_synchronize_history_block;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qv_or_p,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    v_or_p = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_receive_nupec_synchronize_history_block;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      v_or_p = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      v_or_p = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  history_block = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qhistory_block,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_nupec_history_block();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(v_or_p);
			resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_receive_nupec_synchronize_history_block;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qhistory_block,string_constant_4,Qargument,
				T,result_of_read,Nil,Nil);
		    history_block = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_nupec_history_block();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(v_or_p);
		      resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_receive_nupec_synchronize_history_block;
		  }
		  history_block = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_receive_nupec_synchronize_history_block__body(v_or_p,
			history_block);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreceive_nupec_synchronize_history_block,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		v_or_p = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qv_or_p,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_receive_nupec_synchronize_history_block;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qv_or_p,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  v_or_p = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_receive_nupec_synchronize_history_block;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    v_or_p = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    v_or_p = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		history_block = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qhistory_block,
			    string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_nupec_history_block();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(v_or_p);
		      resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_receive_nupec_synchronize_history_block;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qhistory_block,string_constant_4,Qargument,T,
			      result_of_read,Nil,Nil);
		  history_block = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_nupec_history_block();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(v_or_p);
		    resumable_icp_push(Qhandle_icp_receive_nupec_synchronize_history_block);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_receive_nupec_synchronize_history_block;
		}
		history_block = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_receive_nupec_synchronize_history_block__body(v_or_p,
		      history_block);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_receive_nupec_synchronize_history_block:
    return result;
}

static Object string_constant_10;  /* "NUPEC synchronization source timed out after waiting ~a ~
				    *                  seconds without any response messages."
				    */

static Object Qwait_for_start_acknowledgement;  /* wait-for-start-acknowledgement */

static Object Qwait_for_send_acknowledgement;  /* wait-for-send-acknowledgement */

/* PERFORM-WORK-ON-NUPEC-SYNCHRONIZATION */
Object perform_work_on_nupec_synchronization(sync_object)
    Object sync_object;
{
    Object state_1, icp_socket, temp, message_1, current_icp_port;
    Object current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_2, aref_arg_1, second_1, minute, hour, day, month;
    Object year;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp_1;
    double temp_2, temp_3, gensymed_symbol_3, gensymed_symbol_4;
    double gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    double aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,62);
    state_1 = ISVREF(sync_object,(SI_Long)4L);
    icp_socket = ISVREF(sync_object,(SI_Long)3L);
    gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
    gensymed_symbol_1 = IFIX(ISVREF(sync_object,(SI_Long)8L));
    if (gensymed_symbol >= gensymed_symbol_1)
	temp = FIX(gensymed_symbol - gensymed_symbol_1);
    else {
	gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GT(temp,Nupec_fixnum_timeout_interval)) {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(ISVREF(sync_object,(SI_Long)8L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    temp_1 = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    temp_1 = gensymed_symbol + (SI_Long)1L;
	}
	temp_2 = (double)temp_1;
	temp = lfloat(Fixnum_time_units_per_second,float_constant);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	message_1 = tformat_text_string(2,string_constant_10,
		DOUBLE_TO_DOUBLE_FLOAT(temp_2 / temp_3));
	current_icp_port = ISVREF(ISVREF(sync_object,(SI_Long)3L),(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol_2 = Nil;
				gensymed_symbol_3 = 0.0;
				gensymed_symbol_4 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_2 = T;
				    gensymed_symbol_3 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_4 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_4);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_nupec_synchronize_control_message(Qabort_synchronize,
					    message_1);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_6 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_7 = gensymed_symbol_5 
					    - gensymed_symbol_6;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_7 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol_2 ? 
					    gensymed_symbol_3 + 
					    gensymed_symbol_7 + 
					    (gensymed_symbol_6 - 
					    gensymed_symbol_4) : 
					    gensymed_symbol_5;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
	SVREF(sync_object,FIX((SI_Long)5L)) = message_1;
	SVREF(sync_object,FIX((SI_Long)4L)) = Nil;
	return VALUES_1(Nil);
    }
    if (EQ(state_1,Qstart)) {
	result = decode_gensym_time(FIX((SI_Long)0L));
	MVS_6(result,second_1,minute,hour,day,month,year);
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol_2 = Nil;
				gensymed_symbol_3 = 0.0;
				gensymed_symbol_4 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_2 = T;
				    gensymed_symbol_3 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_4 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_4);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_nupec_synchronize(length(ISVREF(sync_object,
					    (SI_Long)1L)),year,month,day,
					    hour,minute,second_1);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_5 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_6 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_7 = gensymed_symbol_5 
					    - gensymed_symbol_6;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_7 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol_2 ? 
					    gensymed_symbol_3 + 
					    gensymed_symbol_7 + 
					    (gensymed_symbol_6 - 
					    gensymed_symbol_4) : 
					    gensymed_symbol_5;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
	SVREF(sync_object,FIX((SI_Long)4L)) = Qwait_for_start_acknowledgement;
	return VALUES_1(Nil);
    }
    else if (EQ(state_1,Qwait_for_start_acknowledgement))
	return VALUES_1(T);
    else if (EQ(state_1,Qsending)) {
	if (FIXNUM_GE(FIXNUM_MINUS(ISVREF(sync_object,(SI_Long)6L),
		ISVREF(sync_object,(SI_Long)7L)),
		Nupec_allowable_message_groups_in_progress))
	    return VALUES_1(T);
	else {
	    send_nupec_source_variables(sync_object,icp_socket);
	    if ( !TRUEP(ISVREF(sync_object,(SI_Long)1L)))
		SVREF(sync_object,FIX((SI_Long)4L)) = 
			Qwait_for_send_acknowledgement;
	    return VALUES_1(Nil);
	}
    }
    else if (EQ(state_1,Qwait_for_send_acknowledgement))
	return VALUES_1(T);
    else if (EQ(state_1,Qwait_for_final_acknowledgement))
	return VALUES_1(T);
    else
	return VALUES_1(Qnil);
}

/* SEND-NUPEC-SOURCE-VARIABLES */
Object send_nupec_source_variables(sync_object,icp_socket)
    Object sync_object, icp_socket;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, variable_count, history_count;
    Object variable_cons, local_nupec_variable, variable, history_block_spec;
    Object history_qm, history_length, temp_2, history_values_to_send;
    Object decff_1_arg, incff_1_arg, group_number;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(221,63);
    current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				variable_count = FIX((SI_Long)0L);
				history_count = FIX((SI_Long)0L);
				variable_cons = Nil;
				local_nupec_variable = Nil;
				variable = Nil;
				history_block_spec = Nil;
				history_qm = Nil;
			      next_loop:
				variable_cons = ISVREF(sync_object,
					(SI_Long)1L);
				if ( !TRUEP(variable_cons) || 
					FIXNUM_GE(variable_count,
					Nupec_allowable_variables_per_message_group) 
					|| FIXNUM_GE(history_count,
					Nupec_allowable_history_values_per_message_group))
				    goto end_loop;
				local_nupec_variable = CAR(variable_cons);
				variable = ISVREF(local_nupec_variable,
					(SI_Long)1L);
				history_block_spec = ISVREF(sync_object,
					(SI_Long)10L);
				history_qm = ISVREF(variable,(SI_Long)24L);
				if ( !TRUEP(history_block_spec)) {
				    history_length = history_qm ? 
					    get_total_cascaded_ring_buffer_length(history_qm) 
					    : FIX((SI_Long)0L);
				    if (IFIX(history_length) == (SI_Long)0L)
					history_block_spec = 
						eval_list_2(FIX((SI_Long)0L),
						FIX((SI_Long)0L));
				    else {
					temp = 
						get_oldest_active_element_index_for_cascaded_ring_buffer(history_qm);
					history_block_spec = 
						eval_list_4(history_length,
						FIX((SI_Long)0L),temp,
						history_qm);
				    }
				}
				temp_2 = CAR(history_block_spec);
				temp = 
					FIXNUM_MINUS(Nupec_allowable_history_values_per_message_group,
					history_count);
				history_values_to_send = FIXNUM_MIN(temp_2,
					temp);
				M_SECOND(history_block_spec) = 
					history_values_to_send;
				decff_1_arg = history_values_to_send;
				temp_1 = 
					FIXNUM_MINUS(FIRST(history_block_spec),
					decff_1_arg);
				M_FIRST(history_block_spec) = temp_1;
				incff_1_arg = history_values_to_send;
				history_count = FIXNUM_ADD(history_count,
					incff_1_arg);
				variable_count = FIXNUM_ADD1(variable_count);
				send_icp_receive_nupec_synchronize_history_block(local_nupec_variable,
					CDR(history_block_spec));
				if (IFIX(CAR(history_block_spec)) == 
					(SI_Long)0L) {
				    if (THIRD(history_block_spec))
					reclaim_history_cons_1(THIRD(history_block_spec));
				    reclaim_eval_list_1(history_block_spec);
				    history_block_spec = Nil;
				    temp_1 = CDR(variable_cons);
				    SVREF(sync_object,FIX((SI_Long)1L)) = 
					    temp_1;
				    reclaim_eval_cons_1(variable_cons);
				    reclaim_icp_object_map_for_nupec_synchronize_variable_or_parameter(local_nupec_variable);
				    reclaim_local_nupec_variable_1(local_nupec_variable);
				}
				SVREF(sync_object,FIX((SI_Long)10L)) = 
					history_block_spec;
				goto next_loop;
			      end_loop:;
				group_number = 
					FIXNUM_ADD1(ISVREF(sync_object,
					(SI_Long)6L));
				SVREF(sync_object,FIX((SI_Long)6L)) = 
					group_number;
				send_icp_nupec_synchronize_control_message(Qgroup_sent,
					group_number);
				temp = Print_nupec_message_states ? 
					format((SI_Long)3L,Terminal_io,
					"~%Group ~a sent...",group_number) 
					: Nil;
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					aref_new_value);
				temp_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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
    return result;
}

static Object string_constant_11;  /* "~A %" */

static Object float_constant_1;    /* 10.0 */

/* WRITE-NUPEC-SYNCHRONIZATION-PROGRESS-DISPLAY-VALUE-FROM-SLOT */
Object write_nupec_synchronization_progress_display_value_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(221,64);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = tformat(2,string_constant_11,divide(value,float_constant_1));
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qnupec_synchronization_progress;  /* nupec-synchronization-progress */

static Object Qlogged_in;          /* logged-in */

static Object list_constant;       /* # */

/* PUT-UP-NUPEC-SYNCHRONIZATION-PROGRESS-DISPLAY */
Object put_up_nupec_synchronization_progress_display()
{
    Object nupec_synchronization_progress, workstation, ab_loop_list_;
    Object current_workstation_1, current_workstation_window;
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

    x_note_fn_call(221,65);
    SAVE_STACK();
    nupec_synchronization_progress = make_entity(1,
	    Qnupec_synchronization_progress);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in)) {
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
				    put_up_attributes_table(4,
					    nupec_synchronization_progress,
					    FIX((SI_Long)230L),
					    FIX((SI_Long)100L),list_constant);
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
    RESTORE_STACK();
    return VALUES_1(nupec_synchronization_progress);
}

void g2ds_nupec_INIT()
{
    Object temp, reclaim_structure_for_source_nupec_synchronization_1;
    Object reclaim_structure_for_target_nupec_synchronization_1;
    Object reclaim_structure_for_nupec_synchronize_variable_or_parameter_1;
    Object reclaim_structure_for_local_nupec_variable_1, temp_1;
    Object AB_package, Qslot_value_writer;
    Object Qwrite_nupec_synchronization_progress_display_value_from_slot;
    Object Qnupec_synchronization_progress_display_value, string_constant_22;
    Object list_constant_3, string_constant_21, string_constant_20, Qentity;
    Object list_constant_1, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qreclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter;
    Object Qreclaim_nupec_synchronize_variable_or_parameter;
    Object Qnupec_synchronize_variable_or_parameter, list_constant_2;
    Object Qicp_object_map_for_local_nupec_variable, Qg2_ds;
    Object Qlocal_nupec_variable, Qreclaim_structure;
    Object Qoutstanding_local_nupec_variable_count;
    Object Qlocal_nupec_variable_structure_memory_usage, Qutilities2;
    Object string_constant_19, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_18, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qoutstanding_nupec_synchronize_variable_or_parameter_count;
    Object Qnupec_synchronize_variable_or_parameter_structure_memory_usage;
    Object string_constant_17, string_constant_16, Qint1;
    Object Qtarget_nupec_synchronization;
    Object Qoutstanding_target_nupec_synchronization_count;
    Object Qtarget_nupec_synchronization_structure_memory_usage;
    Object string_constant_15, string_constant_14;
    Object Qsource_nupec_synchronization;
    Object Qoutstanding_source_nupec_synchronization_count;
    Object Qsource_nupec_synchronization_structure_memory_usage;
    Object string_constant_13, string_constant_12;

    x_note_fn_call(221,66);
    SET_PACKAGE("AB");
    Print_nupec_message_states = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct = 
	    STATIC_SYMBOL("SOURCE-NUPEC-SYNCHRONIZATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qsource_nupec_synchronization = 
	    STATIC_SYMBOL("SOURCE-NUPEC-SYNCHRONIZATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct,
	    Qsource_nupec_synchronization,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qsource_nupec_synchronization,
	    Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_source_nupec_synchronization == UNBOUND)
	The_type_description_of_source_nupec_synchronization = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83nJy1n83nJy8n8k1l8n0000001l1n8y83-5vy1n83-DTy83-DUy83-DSykyk0k0");
    temp = The_type_description_of_source_nupec_synchronization;
    The_type_description_of_source_nupec_synchronization = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_source_nupec_synchronization_g2_struct,
	    The_type_description_of_source_nupec_synchronization,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qsource_nupec_synchronization,
	    The_type_description_of_source_nupec_synchronization,
	    Qtype_description_of_type);
    Qoutstanding_source_nupec_synchronization_count = 
	    STATIC_SYMBOL("OUTSTANDING-SOURCE-NUPEC-SYNCHRONIZATION-COUNT",
	    AB_package);
    Qsource_nupec_synchronization_structure_memory_usage = 
	    STATIC_SYMBOL("SOURCE-NUPEC-SYNCHRONIZATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83nJy8s83-qIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_source_nupec_synchronization_count);
    push_optimized_constant(Qsource_nupec_synchronization_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_source_nupec_synchronizations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SOURCE-NUPEC-SYNCHRONIZATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_source_nupec_synchronizations,
	    Chain_of_available_source_nupec_synchronizations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_source_nupec_synchronizations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsource_nupec_synchronization_count = 
	    STATIC_SYMBOL("SOURCE-NUPEC-SYNCHRONIZATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsource_nupec_synchronization_count,
	    Source_nupec_synchronization_count);
    record_system_variable(Qsource_nupec_synchronization_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_source_nupec_synchronizations_vector == UNBOUND)
	Chain_of_available_source_nupec_synchronizations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsource_nupec_synchronization_structure_memory_usage,
	    STATIC_FUNCTION(source_nupec_synchronization_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_source_nupec_synchronization_count,
	    STATIC_FUNCTION(outstanding_source_nupec_synchronization_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_source_nupec_synchronization_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_source_nupec_synchronization,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsource_nupec_synchronization,
	    reclaim_structure_for_source_nupec_synchronization_1);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct = 
	    STATIC_SYMBOL("TARGET-NUPEC-SYNCHRONIZATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtarget_nupec_synchronization = 
	    STATIC_SYMBOL("TARGET-NUPEC-SYNCHRONIZATION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct,
	    Qtarget_nupec_synchronization,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtarget_nupec_synchronization,
	    Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_target_nupec_synchronization == UNBOUND)
	The_type_description_of_target_nupec_synchronization = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83ngy1n83ngy8n8k1l8n0000001l1n8y83-63y1n83-ERy83-EQy83-ESyktk0k0");
    temp = The_type_description_of_target_nupec_synchronization;
    The_type_description_of_target_nupec_synchronization = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    mutate_global_property(Qg2_defstruct_structure_name_target_nupec_synchronization_g2_struct,
	    The_type_description_of_target_nupec_synchronization,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtarget_nupec_synchronization,
	    The_type_description_of_target_nupec_synchronization,
	    Qtype_description_of_type);
    Qoutstanding_target_nupec_synchronization_count = 
	    STATIC_SYMBOL("OUTSTANDING-TARGET-NUPEC-SYNCHRONIZATION-COUNT",
	    AB_package);
    Qtarget_nupec_synchronization_structure_memory_usage = 
	    STATIC_SYMBOL("TARGET-NUPEC-SYNCHRONIZATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_15 = STATIC_STRING("1q83ngy8s83-sGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_target_nupec_synchronization_count);
    push_optimized_constant(Qtarget_nupec_synchronization_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_target_nupec_synchronizations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TARGET-NUPEC-SYNCHRONIZATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_target_nupec_synchronizations,
	    Chain_of_available_target_nupec_synchronizations);
    record_system_variable(Qchain_of_available_target_nupec_synchronizations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtarget_nupec_synchronization_count = 
	    STATIC_SYMBOL("TARGET-NUPEC-SYNCHRONIZATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtarget_nupec_synchronization_count,
	    Target_nupec_synchronization_count);
    record_system_variable(Qtarget_nupec_synchronization_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_target_nupec_synchronizations_vector == UNBOUND)
	Chain_of_available_target_nupec_synchronizations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtarget_nupec_synchronization_structure_memory_usage,
	    STATIC_FUNCTION(target_nupec_synchronization_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_target_nupec_synchronization_count,
	    STATIC_FUNCTION(outstanding_target_nupec_synchronization_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_target_nupec_synchronization_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_target_nupec_synchronization,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qtarget_nupec_synchronization,
	    reclaim_structure_for_target_nupec_synchronization_1);
    if (Current_source_nupec_synchronization == UNBOUND)
	Current_source_nupec_synchronization = Nil;
    Qcurrent_target_nupec_synchronization = 
	    STATIC_SYMBOL("CURRENT-TARGET-NUPEC-SYNCHRONIZATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_target_nupec_synchronization,
	    Current_target_nupec_synchronization);
    Qint1 = STATIC_SYMBOL("INT1",AB_package);
    record_system_variable(Qcurrent_target_nupec_synchronization,Qint1,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct 
	    = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct,
	    Qnupec_synchronize_variable_or_parameter,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qnupec_synchronize_variable_or_parameter,
	    Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_nupec_synchronize_variable_or_parameter == 
	    UNBOUND)
	The_type_description_of_nupec_synchronize_variable_or_parameter = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83l9y1n83l9y8n8k1l8n0000001m1n8y83-5-y1p83-7my83-7ly83-7iy83-7jy83-7ky1m83My83-Ahyktk0k0");
    temp = The_type_description_of_nupec_synchronize_variable_or_parameter;
    The_type_description_of_nupec_synchronize_variable_or_parameter = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_nupec_synchronize_variable_or_parameter_g2_struct,
	    The_type_description_of_nupec_synchronize_variable_or_parameter,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qnupec_synchronize_variable_or_parameter,
	    The_type_description_of_nupec_synchronize_variable_or_parameter,
	    Qtype_description_of_type);
    Qoutstanding_nupec_synchronize_variable_or_parameter_count = 
	    STATIC_SYMBOL("OUTSTANDING-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-COUNT",
	    AB_package);
    Qnupec_synchronize_variable_or_parameter_structure_memory_usage = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83l9y8s83-hGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_nupec_synchronize_variable_or_parameter_count);
    push_optimized_constant(Qnupec_synchronize_variable_or_parameter_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_nupec_synchronize_variable_or_parameters = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_nupec_synchronize_variable_or_parameters,
	    Chain_of_available_nupec_synchronize_variable_or_parameters);
    record_system_variable(Qchain_of_available_nupec_synchronize_variable_or_parameters,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qnupec_synchronize_variable_or_parameter_count = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnupec_synchronize_variable_or_parameter_count,
	    Nupec_synchronize_variable_or_parameter_count);
    record_system_variable(Qnupec_synchronize_variable_or_parameter_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_nupec_synchronize_variable_or_parameters_vector 
	    == UNBOUND)
	Chain_of_available_nupec_synchronize_variable_or_parameters_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qnupec_synchronize_variable_or_parameter_structure_memory_usage,
	    STATIC_FUNCTION(nupec_synchronize_variable_or_parameter_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_nupec_synchronize_variable_or_parameter_count,
	    STATIC_FUNCTION(outstanding_nupec_synchronize_variable_or_parameter_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_nupec_synchronize_variable_or_parameter_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qnupec_synchronize_variable_or_parameter,
	    reclaim_structure_for_nupec_synchronize_variable_or_parameter_1);
    Qg2_defstruct_structure_name_local_nupec_variable_g2_struct = 
	    STATIC_SYMBOL("LOCAL-NUPEC-VARIABLE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlocal_nupec_variable = STATIC_SYMBOL("LOCAL-NUPEC-VARIABLE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_local_nupec_variable_g2_struct,
	    Qlocal_nupec_variable,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlocal_nupec_variable,
	    Qg2_defstruct_structure_name_local_nupec_variable_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_local_nupec_variable == UNBOUND)
	The_type_description_of_local_nupec_variable = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83kZy1n83kZy8n8k1l8n0000001l1n8y83-4ly1l83-2Qyknk0k0");
    temp = The_type_description_of_local_nupec_variable;
    The_type_description_of_local_nupec_variable = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_local_nupec_variable_g2_struct,
	    The_type_description_of_local_nupec_variable,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlocal_nupec_variable,
	    The_type_description_of_local_nupec_variable,
	    Qtype_description_of_type);
    Qoutstanding_local_nupec_variable_count = 
	    STATIC_SYMBOL("OUTSTANDING-LOCAL-NUPEC-VARIABLE-COUNT",AB_package);
    Qlocal_nupec_variable_structure_memory_usage = 
	    STATIC_SYMBOL("LOCAL-NUPEC-VARIABLE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83kZy8s83-d5y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_local_nupec_variable_count);
    push_optimized_constant(Qlocal_nupec_variable_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_local_nupec_variables = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LOCAL-NUPEC-VARIABLES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_local_nupec_variables,
	    Chain_of_available_local_nupec_variables);
    record_system_variable(Qchain_of_available_local_nupec_variables,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qlocal_nupec_variable_count = 
	    STATIC_SYMBOL("LOCAL-NUPEC-VARIABLE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlocal_nupec_variable_count,
	    Local_nupec_variable_count);
    record_system_variable(Qlocal_nupec_variable_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_local_nupec_variables_vector == UNBOUND)
	Chain_of_available_local_nupec_variables_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlocal_nupec_variable_structure_memory_usage,
	    STATIC_FUNCTION(local_nupec_variable_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_local_nupec_variable_count,
	    STATIC_FUNCTION(outstanding_local_nupec_variable_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_local_nupec_variable_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_local_nupec_variable,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qlocal_nupec_variable,
	    reclaim_structure_for_local_nupec_variable_1);
    Nupec_allowable_message_groups_in_progress = FIX((SI_Long)5L);
    Nupec_allowable_variables_per_message_group = FIX((SI_Long)10L);
    Nupec_allowable_history_values_per_message_group = FIX((SI_Long)100L);
    Nupec_fixnum_timeout_interval = fixnum_time_interval(FIX((SI_Long)30000L));
    Qg2ds_interface_structure = STATIC_SYMBOL("G2DS-INTERFACE-STRUCTURE",
	    AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)40L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)41L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)42L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)43L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)45L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)47L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)49L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)50L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)51L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)53L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)54L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)62L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)63L,(SI_Long)57344L);
    string_constant = 
	    STATIC_STRING("NUPEC synchronization failed because the interface status of ~NF is ");
    Qinterface_status = STATIC_SYMBOL("INTERFACE-STATUS",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qnupec_synchronize = STATIC_SYMBOL("NUPEC-SYNCHRONIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qnupec_synchronize,
	    STATIC_FUNCTION(nupec_synchronize,NIL,FALSE,2,2));
    Qdefine_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    Qg2_ds = STATIC_SYMBOL("G2-DS",AB_package);
    add_icp_message_type_code(Qdefine_nupec_synchronize_variable_or_parameter,
	    FIX((SI_Long)200L),Qg2_ds);
    Qnupec_synchronize_control_message = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZE-CONTROL-MESSAGE",AB_package);
    add_icp_message_type_code(Qnupec_synchronize_control_message,
	    FIX((SI_Long)201L),Qg2_ds);
    Qreceive_nupec_synchronize_history_block = 
	    STATIC_SYMBOL("RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK",
	    AB_package);
    add_icp_message_type_code(Qreceive_nupec_synchronize_history_block,
	    FIX((SI_Long)202L),Qg2_ds);
    add_icp_message_type_code(Qnupec_synchronize,FIX((SI_Long)203L),Qg2_ds);
    Qnupec_synchronize_datum = STATIC_SYMBOL("NUPEC-SYNCHRONIZE-DATUM",
	    AB_package);
    string_constant_1 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qwrite_icp_nupec_synchronize_datum = 
	    STATIC_SYMBOL("WRITE-ICP-NUPEC-SYNCHRONIZE-DATUM",AB_package);
    string_constant_2 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_nupec_synchronize_datum,
	    STATIC_FUNCTION(write_icp_nupec_synchronize_datum,NIL,FALSE,1,1));
    Qread_icp_nupec_synchronize_datum = 
	    STATIC_SYMBOL("READ-ICP-NUPEC-SYNCHRONIZE-DATUM",AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_nupec_synchronize_datum,
	    STATIC_FUNCTION(read_icp_nupec_synchronize_datum,NIL,FALSE,0,0));
    Qnupec_designation = STATIC_SYMBOL("NUPEC-DESIGNATION",AB_package);
    Qwrite_icp_nupec_designation = 
	    STATIC_SYMBOL("WRITE-ICP-NUPEC-DESIGNATION",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_nupec_designation,
	    STATIC_FUNCTION(write_icp_nupec_designation,NIL,FALSE,1,1));
    Qread_icp_nupec_designation = 
	    STATIC_SYMBOL("READ-ICP-NUPEC-DESIGNATION",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_nupec_designation,
	    STATIC_FUNCTION(read_icp_nupec_designation,NIL,FALSE,0,0));
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_nupec_synchronize_variable_or_parameter 
	    = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(establish_new_object_index_for_nupec_synchronize_variable_or_parameter,
	    NIL,TRUE,2,3));
    Qno_value = STATIC_SYMBOL("NO-VALUE",AB_package);
    Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(make_corresponding_icp_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,1,1));
    Qset_access_form_for_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(set_access_form_for_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,2,2));
    Qicp_object_map_for_local_nupec_variable = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-LOCAL-NUPEC-VARIABLE",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_local_nupec_variable,
	    Qnupec_synchronize_variable_or_parameter);
    initialize_icp_object_type_compile(Qnupec_synchronize_variable_or_parameter,
	    Qstandard_icp_object_index_space,list_constant_2);
    Qreclaim_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("RECLAIM-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(reclaim_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,1,1));
    Qreclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qnupec_synchronize_variable_or_parameter,
	    Qreclaim_nupec_synchronize_variable_or_parameter,Qnil,
	    Qreclaim_icp_port_entry_for_nupec_synchronize_variable_or_parameter);
    Qsend_icp_define_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    string_constant_3 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qcorresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    string_constant_4 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qremote_designation = STATIC_SYMBOL("REMOTE-DESIGNATION",AB_package);
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    Qcollection_time = STATIC_SYMBOL("COLLECTION-TIME",AB_package);
    Qexpiration = STATIC_SYMBOL("EXPIRATION",AB_package);
    Qhistory_length = STATIC_SYMBOL("HISTORY-LENGTH",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(send_icp_define_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,6,6));
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhandle_icp_define_nupec_synchronize_variable_or_parameter = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-NUPEC-SYNCHRONIZE-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_nupec_synchronize_variable_or_parameter,
	    STATIC_FUNCTION(handle_icp_define_nupec_synchronize_variable_or_parameter,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_nupec_synchronize_variable_or_parameter,
	    FIX((SI_Long)200L));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qstart_rejected = STATIC_SYMBOL("START-REJECTED",AB_package);
    Qsend_icp_nupec_synchronize = 
	    STATIC_SYMBOL("SEND-ICP-NUPEC-SYNCHRONIZE",AB_package);
    Qvariable_count = STATIC_SYMBOL("VARIABLE-COUNT",AB_package);
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    Qday = STATIC_SYMBOL("DAY",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_nupec_synchronize,
	    STATIC_FUNCTION(send_icp_nupec_synchronize,NIL,FALSE,7,7));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreceive_nupec_synchronize_task = 
	    STATIC_SYMBOL("RECEIVE-NUPEC-SYNCHRONIZE-TASK",AB_package);
    Qhandle_icp_nupec_synchronize = 
	    STATIC_SYMBOL("HANDLE-ICP-NUPEC-SYNCHRONIZE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_nupec_synchronize,
	    STATIC_FUNCTION(handle_icp_nupec_synchronize,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_nupec_synchronize,FIX((SI_Long)203L));
    SET_SYMBOL_FUNCTION(Qreceive_nupec_synchronize_task,
	    STATIC_FUNCTION(receive_nupec_synchronize_task,NIL,FALSE,0,0));
    Qstart_accepted = STATIC_SYMBOL("START-ACCEPTED",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    string_constant_5 = 
	    STATIC_STRING("Reception of NUPEC synchronization timed out after a delay ~\n                 of ~a seconds.");
    Qabort_synchronize = STATIC_SYMBOL("ABORT-SYNCHRONIZE",AB_package);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    string_constant_6 = 
	    STATIC_STRING("Reception of a NUPEC synchronization has been aborted for the following ~\n     reason: ~a");
    Qgroup_received = STATIC_SYMBOL("GROUP-RECEIVED",AB_package);
    Qend_of_synchronization = STATIC_SYMBOL("END-OF-SYNCHRONIZATION",
	    AB_package);
    Qend_of_synchronization_confirmed_thank_you = 
	    STATIC_SYMBOL("END-OF-SYNCHRONIZATION-CONFIRMED-THANK-YOU",
	    AB_package);
    Qsend_icp_nupec_synchronize_control_message = 
	    STATIC_SYMBOL("SEND-ICP-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE",
	    AB_package);
    Qcorresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    Qcontrol_message = STATIC_SYMBOL("CONTROL-MESSAGE",AB_package);
    string_constant_7 = STATIC_STRING("[object arg]");
    Qextra_argument = STATIC_SYMBOL("EXTRA-ARGUMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_nupec_synchronize_control_message,
	    STATIC_FUNCTION(send_icp_nupec_synchronize_control_message,NIL,
	    FALSE,2,2));
    Qsending = STATIC_SYMBOL("SENDING",AB_package);
    string_constant_8 = 
	    STATIC_STRING("Synchronization request was rejected by the remote G2.  ~\n                 The following reason was given:  ~a");
    Qgroup_sent = STATIC_SYMBOL("GROUP-SENT",AB_package);
    Qprogress_through_nupec_synchronization = 
	    STATIC_SYMBOL("PROGRESS-THROUGH-NUPEC-SYNCHRONIZATION",AB_package);
    Qwait_for_final_acknowledgement = 
	    STATIC_SYMBOL("WAIT-FOR-FINAL-ACKNOWLEDGEMENT",AB_package);
    Qhandle_icp_nupec_synchronize_control_message = 
	    STATIC_SYMBOL("HANDLE-ICP-NUPEC-SYNCHRONIZE-CONTROL-MESSAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_nupec_synchronize_control_message,
	    STATIC_FUNCTION(handle_icp_nupec_synchronize_control_message,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_nupec_synchronize_control_message,
	    FIX((SI_Long)201L));
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)57344L);
    Qnupec_history_block = STATIC_SYMBOL("NUPEC-HISTORY-BLOCK",AB_package);
    Qwrite_icp_nupec_history_block = 
	    STATIC_SYMBOL("WRITE-ICP-NUPEC-HISTORY-BLOCK",AB_package);
    Qblock_1 = STATIC_SYMBOL("BLOCK",Qnil);
    SET_SYMBOL_FUNCTION(Qwrite_icp_nupec_history_block,
	    STATIC_FUNCTION(write_icp_nupec_history_block,NIL,FALSE,1,1));
    Qread_icp_nupec_history_block = 
	    STATIC_SYMBOL("READ-ICP-NUPEC-HISTORY-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_nupec_history_block,
	    STATIC_FUNCTION(read_icp_nupec_history_block,NIL,FALSE,0,0));
    Qsend_icp_receive_nupec_synchronize_history_block = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK",
	    AB_package);
    Qv_or_p = STATIC_SYMBOL("V-OR-P",AB_package);
    Qhistory_block = STATIC_SYMBOL("HISTORY-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_receive_nupec_synchronize_history_block,
	    STATIC_FUNCTION(send_icp_receive_nupec_synchronize_history_block,
	    NIL,FALSE,2,2));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    string_constant_9 = 
	    STATIC_STRING("Reception of a NUPEC Synchronize could find no local ~\n                 variable or parameter for the designation ");
    Qhandle_icp_receive_nupec_synchronize_history_block = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-NUPEC-SYNCHRONIZE-HISTORY-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_receive_nupec_synchronize_history_block,
	    STATIC_FUNCTION(handle_icp_receive_nupec_synchronize_history_block,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_receive_nupec_synchronize_history_block,
	    FIX((SI_Long)202L));
    string_constant_10 = 
	    STATIC_STRING("NUPEC synchronization source timed out after waiting ~a ~\n                 seconds without any response messages.");
    Qwait_for_start_acknowledgement = 
	    STATIC_SYMBOL("WAIT-FOR-START-ACKNOWLEDGEMENT",AB_package);
    Qwait_for_send_acknowledgement = 
	    STATIC_SYMBOL("WAIT-FOR-SEND-ACKNOWLEDGEMENT",AB_package);
    Qnupec_synchronization_progress = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-PROGRESS",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_3 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qnupec_synchronization_progress,
	    list_constant_3);
    string_constant_20 = STATIC_STRING("0");
    string_constant_21 = 
	    STATIC_STRING("1l4z8r83YMy83YMy83X0y83X0y0k001p1l8l1l83Hy1l8o1l83Fy1m8p83X1y00000");
    string_constant_22 = 
	    STATIC_STRING("1n8q1m83X0y1l83-+y1r83YMyk8l83Hy8o83Fy1m8p83X1y");
    temp = regenerate_optimized_constant(string_constant_20);
    temp_1 = regenerate_optimized_constant(string_constant_21);
    add_class_to_environment(9,Qnupec_synchronization_progress,
	    list_constant_3,Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_22),Nil);
    string_constant_11 = STATIC_STRING("~A %");
    float_constant_1 = STATIC_FLOAT(10.0);
    Qnupec_synchronization_progress_display_value = 
	    STATIC_SYMBOL("NUPEC-SYNCHRONIZATION-PROGRESS-DISPLAY-VALUE",
	    AB_package);
    Qwrite_nupec_synchronization_progress_display_value_from_slot = 
	    STATIC_SYMBOL("WRITE-NUPEC-SYNCHRONIZATION-PROGRESS-DISPLAY-VALUE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_nupec_synchronization_progress_display_value_from_slot,
	    STATIC_FUNCTION(write_nupec_synchronization_progress_display_value_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qnupec_synchronization_progress_display_value,
	    SYMBOL_FUNCTION(Qwrite_nupec_synchronization_progress_display_value_from_slot),
	    Qslot_value_writer);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    list_constant = STATIC_CONS(Qprogress_through_nupec_synchronization,Qnil);
}
