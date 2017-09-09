/* evt.c
 * Input file:  events.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "evt.h"


Object Frame_type_offset = UNBOUND;

Object Frame_previous_offset = UNBOUND;

Object Frame_gesture_offset = UNBOUND;

Object Frame_pc_offset = UNBOUND;

Object Frame_header_size = UNBOUND;

Object Normal_frame = UNBOUND;

Object Catch_frame = UNBOUND;

Object Protected_frame = UNBOUND;

Object No_previous_frame = UNBOUND;

Object Per_call_stack_slop = UNBOUND;

/* GESTURE-VALUE-RUNTIME-SUBTYPE-P */
Object gesture_value_runtime_subtype_p(type,potential_subtype)
    Object type, potential_subtype;
{
    x_note_fn_call(247,0);
    return type_specification_subtype_in_kb_p(potential_subtype,type);
}

Object The_type_description_of_gesture_thread = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gesture_threads, Qchain_of_available_gesture_threads);

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_thread_count, Qgesture_thread_count);

Object Chain_of_available_gesture_threads_vector = UNBOUND;

/* GESTURE-THREAD-STRUCTURE-MEMORY-USAGE */
Object gesture_thread_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(247,1);
    temp = Gesture_thread_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GESTURE-THREAD-COUNT */
Object outstanding_gesture_thread_count()
{
    Object def_structure_gesture_thread_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(247,2);
    gensymed_symbol = IFIX(Gesture_thread_count);
    def_structure_gesture_thread_variable = Chain_of_available_gesture_threads;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gesture_thread_variable))
	goto end_loop;
    def_structure_gesture_thread_variable = 
	    ISVREF(def_structure_gesture_thread_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GESTURE-THREAD-1 */
Object reclaim_gesture_thread_1(gesture_thread)
    Object gesture_thread;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(247,3);
    inline_note_reclaim_cons(gesture_thread,Nil);
    structure_being_reclaimed = gesture_thread;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(gesture_thread,(SI_Long)5L));
      SVREF(gesture_thread,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_gesture_threads_vector,
	    IFIX(Current_thread_index));
    SVREF(gesture_thread,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gesture_threads_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gesture_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GESTURE-THREAD */
Object reclaim_structure_for_gesture_thread(gesture_thread)
    Object gesture_thread;
{
    x_note_fn_call(247,4);
    return reclaim_gesture_thread_1(gesture_thread);
}

static Object Qg2_defstruct_structure_name_gesture_thread_g2_struct;  /* g2-defstruct-structure-name::gesture-thread-g2-struct */

/* MAKE-PERMANENT-GESTURE-THREAD-STRUCTURE-INTERNAL */
Object make_permanent_gesture_thread_structure_internal()
{
    Object def_structure_gesture_thread_variable;
    Object defstruct_g2_gesture_thread_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(247,5);
    def_structure_gesture_thread_variable = Nil;
    atomic_incff_symval(Qgesture_thread_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gesture_thread_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_gesture_thread_variable = the_array;
	SVREF(defstruct_g2_gesture_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_thread_g2_struct;
	def_structure_gesture_thread_variable = 
		defstruct_g2_gesture_thread_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gesture_thread_variable);
}

/* MAKE-GESTURE-THREAD-1 */
Object make_gesture_thread_1()
{
    Object def_structure_gesture_thread_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(247,6);
    def_structure_gesture_thread_variable = 
	    ISVREF(Chain_of_available_gesture_threads_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gesture_thread_variable) {
	svref_arg_1 = Chain_of_available_gesture_threads_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gesture_thread_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gesture_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_thread_g2_struct;
    }
    else
	def_structure_gesture_thread_variable = 
		make_permanent_gesture_thread_structure_internal();
    inline_note_allocate_cons(def_structure_gesture_thread_variable,Nil);
    ISVREF(def_structure_gesture_thread_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_gesture_thread_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_gesture_thread_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_gesture_thread_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gesture_thread_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_gesture_thread_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gesture_thread_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_gesture_thread_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gesture_thread_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_gesture_thread_variable);
}

Object Gesture_function_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_source_recording_p, Qgesture_source_recording_p);

Object The_type_description_of_gesture_function = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gesture_functions, Qchain_of_available_gesture_functions);

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_function_count, Qgesture_function_count);

Object Chain_of_available_gesture_functions_vector = UNBOUND;

/* GESTURE-FUNCTION-STRUCTURE-MEMORY-USAGE */
Object gesture_function_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(247,7);
    temp = Gesture_function_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GESTURE-FUNCTION-COUNT */
Object outstanding_gesture_function_count()
{
    Object def_structure_gesture_function_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(247,8);
    gensymed_symbol = IFIX(Gesture_function_count);
    def_structure_gesture_function_variable = 
	    Chain_of_available_gesture_functions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gesture_function_variable))
	goto end_loop;
    def_structure_gesture_function_variable = 
	    ISVREF(def_structure_gesture_function_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GESTURE-FUNCTION-INTERNAL-1 */
Object reclaim_gesture_function_internal_1(gesture_function)
    Object gesture_function;
{
    Object temp, svref_arg_2;

    x_note_fn_call(247,9);
    inline_note_reclaim_cons(gesture_function,Nil);
    temp = ISVREF(Chain_of_available_gesture_functions_vector,
	    IFIX(Current_thread_index));
    SVREF(gesture_function,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gesture_functions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gesture_function;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GESTURE-FUNCTION */
Object reclaim_structure_for_gesture_function(gesture_function)
    Object gesture_function;
{
    x_note_fn_call(247,10);
    return reclaim_gesture_function_internal_1(gesture_function);
}

static Object Qg2_defstruct_structure_name_gesture_function_g2_struct;  /* g2-defstruct-structure-name::gesture-function-g2-struct */

/* MAKE-PERMANENT-GESTURE-FUNCTION-STRUCTURE-INTERNAL */
Object make_permanent_gesture_function_structure_internal()
{
    Object def_structure_gesture_function_variable;
    Object defstruct_g2_gesture_function_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(247,11);
    def_structure_gesture_function_variable = Nil;
    atomic_incff_symval(Qgesture_function_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gesture_function_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_gesture_function_variable = the_array;
	SVREF(defstruct_g2_gesture_function_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_function_g2_struct;
	def_structure_gesture_function_variable = 
		defstruct_g2_gesture_function_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gesture_function_variable);
}

/* MAKE-GESTURE-FUNCTION-1 */
Object make_gesture_function_1()
{
    Object def_structure_gesture_function_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(247,12);
    def_structure_gesture_function_variable = 
	    ISVREF(Chain_of_available_gesture_functions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gesture_function_variable) {
	svref_arg_1 = Chain_of_available_gesture_functions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gesture_function_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gesture_function_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_function_g2_struct;
    }
    else
	def_structure_gesture_function_variable = 
		make_permanent_gesture_function_structure_internal();
    inline_note_allocate_cons(def_structure_gesture_function_variable,Nil);
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_gesture_function_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_gesture_function_variable);
}

Object The_type_description_of_gesture_local = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_gesture_locals, Qchain_of_available_gesture_locals);

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_local_count, Qgesture_local_count);

Object Chain_of_available_gesture_locals_vector = UNBOUND;

/* GESTURE-LOCAL-STRUCTURE-MEMORY-USAGE */
Object gesture_local_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(247,13);
    temp = Gesture_local_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GESTURE-LOCAL-COUNT */
Object outstanding_gesture_local_count()
{
    Object def_structure_gesture_local_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(247,14);
    gensymed_symbol = IFIX(Gesture_local_count);
    def_structure_gesture_local_variable = Chain_of_available_gesture_locals;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gesture_local_variable))
	goto end_loop;
    def_structure_gesture_local_variable = 
	    ISVREF(def_structure_gesture_local_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GESTURE-LOCAL-1 */
Object reclaim_gesture_local_1(gesture_local)
    Object gesture_local;
{
    Object temp, svref_arg_2;

    x_note_fn_call(247,15);
    inline_note_reclaim_cons(gesture_local,Nil);
    temp = ISVREF(Chain_of_available_gesture_locals_vector,
	    IFIX(Current_thread_index));
    SVREF(gesture_local,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_gesture_locals_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = gesture_local;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GESTURE-LOCAL */
Object reclaim_structure_for_gesture_local(gesture_local)
    Object gesture_local;
{
    x_note_fn_call(247,16);
    return reclaim_gesture_local_1(gesture_local);
}

static Object Qg2_defstruct_structure_name_gesture_local_g2_struct;  /* g2-defstruct-structure-name::gesture-local-g2-struct */

/* MAKE-PERMANENT-GESTURE-LOCAL-STRUCTURE-INTERNAL */
Object make_permanent_gesture_local_structure_internal()
{
    Object def_structure_gesture_local_variable;
    Object defstruct_g2_gesture_local_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(247,17);
    def_structure_gesture_local_variable = Nil;
    atomic_incff_symval(Qgesture_local_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gesture_local_variable = Nil;
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
	defstruct_g2_gesture_local_variable = the_array;
	SVREF(defstruct_g2_gesture_local_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_local_g2_struct;
	def_structure_gesture_local_variable = 
		defstruct_g2_gesture_local_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gesture_local_variable);
}

/* MAKE-GESTURE-LOCAL-1 */
Object make_gesture_local_1(gesture_local_name,gesture_local_index,
	    gesture_local_type)
    Object gesture_local_name, gesture_local_index, gesture_local_type;
{
    Object def_structure_gesture_local_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(247,18);
    def_structure_gesture_local_variable = 
	    ISVREF(Chain_of_available_gesture_locals_vector,
	    IFIX(Current_thread_index));
    if (def_structure_gesture_local_variable) {
	svref_arg_1 = Chain_of_available_gesture_locals_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_gesture_local_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_gesture_local_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gesture_local_g2_struct;
    }
    else
	def_structure_gesture_local_variable = 
		make_permanent_gesture_local_structure_internal();
    inline_note_allocate_cons(def_structure_gesture_local_variable,Nil);
    SVREF(def_structure_gesture_local_variable,FIX((SI_Long)1L)) = 
	    gesture_local_name;
    SVREF(def_structure_gesture_local_variable,FIX((SI_Long)2L)) = 
	    gesture_local_index;
    SVREF(def_structure_gesture_local_variable,FIX((SI_Long)3L)) = 
	    gesture_local_type;
    return VALUES_1(def_structure_gesture_local_variable);
}

/* COPY-GESTURE-LOCAL */
Object copy_gesture_local(gesture_local)
    Object gesture_local;
{
    Object temp;

    x_note_fn_call(247,19);
    temp = make_gesture_local_1(ISVREF(gesture_local,(SI_Long)1L),
	    ISVREF(gesture_local,(SI_Long)2L),ISVREF(gesture_local,
	    (SI_Long)3L));
    return VALUES_1(temp);
}

/* TW-METHOD-IS-CONGRUENT-TO-DECLARATION-P */
Object tw_method_is_congruent_to_declaration_p(method_declaration,
	    specific_method)
    Object method_declaration, specific_method;
{
    Object temp, temp_1;
    char temp_2;

    x_note_fn_call(247,20);
    if (FIXNUM_EQ(ISVREF(method_declaration,(SI_Long)1L),
	    ISVREF(specific_method,(SI_Long)1L))) {
	temp = ISVREF(method_declaration,(SI_Long)2L);
	temp_1 = ISVREF(specific_method,(SI_Long)2L);
	temp_2 = TRUEP(gesture_locals_match_p(CDR(temp),CDR(temp_1)));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_EQ(ISVREF(method_declaration,(SI_Long)3L),
	    ISVREF(specific_method,(SI_Long)3L)) : TRUEP(Nil)) {
	temp = ISVREF(method_declaration,(SI_Long)4L);
	temp_1 = ISVREF(specific_method,(SI_Long)4L);
	temp_2 = TRUEP(gesture_locals_match_p(CDR(temp),CDR(temp_1)));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? FIXNUM_EQ(ISVREF(method_declaration,(SI_Long)5L),
	    ISVREF(specific_method,(SI_Long)5L)) : TRUEP(Nil)) {
	temp = ISVREF(method_declaration,(SI_Long)6L);
	temp_1 = ISVREF(specific_method,(SI_Long)6L);
	temp_2 = TRUEP(gesture_locals_match_p(CDR(temp),CDR(temp_1)));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp_1 = ISVREF(method_declaration,(SI_Long)9L);
	if (temp_1)
	    return VALUES_1(temp_1);
	else
	    return VALUES_1( !TRUEP(ISVREF(specific_method,(SI_Long)9L)) ? 
		    T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GESTURE-LOCALS-MATCH-P */
Object gesture_locals_match_p(local_list_1,local_list_2)
    Object local_list_1, local_list_2;
{
    Object local_1, ab_loop_list_, local_2, ab_loop_list__1, temp, temp_1;

    x_note_fn_call(247,21);
    if (EQ(length(local_list_1),length(local_list_2))) {
	local_1 = Nil;
	ab_loop_list_ = local_list_1;
	local_2 = Nil;
	ab_loop_list__1 = local_list_2;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	local_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	local_2 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = ISVREF(local_1,(SI_Long)3L);
	temp_1 = ISVREF(local_2,(SI_Long)3L);
	if ( !(EQUAL(temp,temp_1) && FIXNUM_EQ(ISVREF(local_1,(SI_Long)2L),
		ISVREF(local_2,(SI_Long)2L))))
	    return VALUES_1(Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-GESTURE-FUNCTION */
Object reclaim_gesture_function(gesture_function)
    Object gesture_function;
{
    Object local_spec, ab_loop_list_, name, gesture_method, temp;

    x_note_fn_call(247,22);
    local_spec = Nil;
    ab_loop_list_ = ISVREF(gesture_function,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gesture_local_1(local_spec);
    goto next_loop;
  end_loop:;
    local_spec = Nil;
    ab_loop_list_ = ISVREF(gesture_function,(SI_Long)4L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    local_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gesture_local_1(local_spec);
    goto next_loop_1;
  end_loop_1:;
    local_spec = Nil;
    ab_loop_list_ = ISVREF(gesture_function,(SI_Long)6L);
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    local_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gesture_local_1(local_spec);
    goto next_loop_2;
  end_loop_2:;
    if (ISVREF(gesture_function,(SI_Long)12L)) {
	name = Nil;
	gesture_method = Nil;
	ab_loop_list_ = ISVREF(gesture_function,(SI_Long)8L);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
      next_loop_3:
	name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	gesture_method = CAR(temp);
	reclaim_gesture_function(gesture_method);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	goto next_loop_3;
      end_loop_3:;
	reclaim_gensym_list_1(ISVREF(gesture_function,(SI_Long)8L));
    }
    reclaim_managed_simple_vector(ISVREF(gesture_function,(SI_Long)8L));
    return reclaim_gesture_function_internal_1(gesture_function);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tracing_in_events_modules_p, Qtracing_in_events_modules_p);

DEFINE_VARIABLE_WITH_SYMBOL(Tw_evaluate_trace_level, Qtw_evaluate_trace_level);

DEFINE_VARIABLE_WITH_SYMBOL(Tw_source_debug_p, Qtw_source_debug_p);

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_unbound_value, Qgesture_unbound_value);

Object Gesture_instruction_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(All_gesture_instruction_names, Qall_gesture_instruction_names);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_stack_pointer, Qcurrent_gesture_stack_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_frame_pointer, Qcurrent_gesture_frame_pointer);

/* GET-GESTURE-LOCAL-BY-INDEX */
Object get_gesture_local_by_index(gesture_function,index_1)
    Object gesture_function, index_1;
{
    Object local, ab_loop_list_, temp;

    x_note_fn_call(247,23);
    local = Nil;
    ab_loop_list_ = ISVREF(gesture_function,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(ISVREF(local,(SI_Long)2L),index_1)) {
	temp = local;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	local = Nil;
	ab_loop_list_ = ISVREF(gesture_function,(SI_Long)2L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	local = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (FIXNUM_EQ(ISVREF(local,(SI_Long)2L),index_1))
	    return VALUES_1(local);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Secret_return_value, Qsecret_return_value);

/* CALL-PRIMITIVE-GESTURE */
Object call_primitive_gesture(gesture_function,arg_count,arg_list)
    Object gesture_function, arg_count, arg_list;
{
    Object argument_list, gensymed_symbol, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10, temp_11;
    Object temp_12, temp_13, temp_14, temp_15, temp_16, ret_val_list;

    x_note_fn_call(247,24);
    if (IFIX(Tw_evaluate_trace_level) > (SI_Long)1L) {
	format((SI_Long)4L,T,"in call prim argc =~s argl=~s ~%",arg_count,
		arg_list);
	force_output(T);
    }
    argument_list = arg_list;
    gensymed_symbol = Secret_return_value;
    temp = arg_count;
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    gensymed_symbol = FUNCALL_0(gesture_function);
	    break;
	  case 1:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = FUNCALL_1(gesture_function,temp);
	    break;
	  case 2:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = FUNCALL_2(gesture_function,temp,temp_1);
	    break;
	  case 3:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = FUNCALL_3(gesture_function,temp,temp_1,temp_2);
	    break;
	  case 4:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = FUNCALL_4(gesture_function,temp,temp_1,
		    temp_2,temp_3);
	    break;
	  case 5:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = FUNCALL_5(gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4);
	    break;
	  case 6:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(7,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5);
	    break;
	  case 7:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(8,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6);
	    break;
	  case 8:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(9,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7);
	    break;
	  case 9:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(10,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8);
	    break;
	  case 10:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(11,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,temp_9);
	    break;
	  case 11:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(12,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10);
	    break;
	  case 12:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(13,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11);
	    break;
	  case 13:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_12 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(14,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11,temp_12);
	    break;
	  case 14:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_12 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_13 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(15,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11,temp_12,temp_13);
	    break;
	  case 15:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_12 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_13 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_14 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(16,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11,temp_12,temp_13,temp_14);
	    break;
	  case 16:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_12 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_13 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_14 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_15 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(17,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11,temp_12,temp_13,temp_14,temp_15);
	    break;
	  case 17:
	    temp = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_1 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_2 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_3 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_4 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_5 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_6 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_7 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_8 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_9 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_10 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_11 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_12 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_13 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_14 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_15 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    temp_16 = M_CAR(argument_list);
	    argument_list = M_CDR(argument_list);
	    gensymed_symbol = funcall(18,gesture_function,temp,temp_1,
		    temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,
		    temp_9,temp_10,temp_11,temp_12,temp_13,temp_14,temp_15,
		    temp_16);
	    break;
	  default:
	    break;
	}
    if (EQ(gensymed_symbol,Secret_return_value))
	error((SI_Long)1L,"too many args to call-primitive-gesture");
    ret_val_list = gensymed_symbol;
    if (IFIX(Tw_evaluate_trace_level) > (SI_Long)2L) {
	format((SI_Long)3L,T,"call prim gesture ret=~s~%",ret_val_list);
	force_output(T);
    }
    temp = nreverse(ret_val_list);
    reclaim_gensym_list_1(arg_list);
    return VALUES_1(temp);
}

/* COMPUTE-EFFECTIVE-GESTURE-METHOD */
Object compute_effective_gesture_method(gesture_method_declaration,frame,
	    next_p)
    Object gesture_method_declaration, frame, next_p;
{
    Object temp;

    x_note_fn_call(247,25);
    temp = 
	    compute_effective_gesture_method_of_class_description(gesture_method_declaration,
	    ISVREF(frame,(SI_Long)1L),next_p);
    return VALUES_1(temp);
}

/* COMPUTE-EFFECTIVE-GESTURE-METHOD-OF-CLASS-DESCRIPTION */
Object compute_effective_gesture_method_of_class_description(gesture_method_declaration,
	    class_description,next_p)
    Object gesture_method_declaration, class_description, next_p;
{
    Object inheritance_path, method_table, class_1, ab_loop_list_, method_qm;
    Object temp;

    x_note_fn_call(247,26);
    inheritance_path = ISVREF(class_description,(SI_Long)2L);
    if (next_p)
	inheritance_path = CDR(inheritance_path);
    method_table = ISVREF(gesture_method_declaration,(SI_Long)8L);
    class_1 = Nil;
    ab_loop_list_ = inheritance_path;
    method_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    method_qm = getf(method_table,class_1,_);
    if (method_qm) {
	temp = method_qm;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qnote_slot_changes;  /* note-slot-changes */

static Object Qparent_attribute_name;  /* parent-attribute-name */

static Object Qparent_frame;       /* parent-frame */

static Object Qab_slot_value;      /* slot-value */

/* TW-PUT-ATTRIBUTE-DESCRIPTION-VALUE */
Object tw_put_attribute_description_value(frame,slot_description,
	    new_attribute_value,initializing_qm)
    Object frame, slot_description, new_attribute_value, initializing_qm;
{
    Object old_attribute_value, x2, new_value_is_frame_p, slot_features;
    Object sub_class_bit_vector, parent_pretty_slot_name, class_description;
    Object temp_1, parent_slot_defining_class_qm, gensymed_symbol_3, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(247,27);
    old_attribute_value = get_slot_description_value(frame,slot_description);
    if (SIMPLE_VECTOR_P(new_attribute_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_attribute_value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(new_attribute_value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(new_attribute_value,(SI_Long)1L);
	new_value_is_frame_p = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	new_value_is_frame_p = Nil;
    if ( !TRUEP(initializing_qm)) {
	if (SIMPLE_VECTOR_P(old_attribute_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_attribute_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(old_attribute_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(old_attribute_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    error((SI_Long)1L,"we should not be in the sub-frame case");
    }
    if (Noting_changes_to_kb_p) {
	slot_features = ISVREF(slot_description,(SI_Long)9L);
	temp = assq_function(Qtype,slot_features) ?  
		!TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		TRUEP(assq_function(Qsave,slot_features));
	if (temp);
	else
	    temp = TRUEP(assq_function(Qnote_slot_changes,
		    ISVREF(slot_description,(SI_Long)9L)));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
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
	if (temp)
	    note_change_to_block_1(frame,ISVREF(slot_description,(SI_Long)2L));
	else
	    note_change_to_dependent_frame_1();
    }
    set_slot_description_value_without_noting(frame,slot_description,
	    new_attribute_value);
    if (new_value_is_frame_p) {
	parent_pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	class_description = ISVREF(frame,(SI_Long)1L);
	if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	    temp_1 = ISVREF(slot_description,(SI_Long)3L);
	    temp =  !EQ(temp_1,
		    ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		    (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	}
	else
	    temp = TRUEP(Nil);
	parent_slot_defining_class_qm = temp ? ISVREF(slot_description,
		(SI_Long)3L) : Nil;
	gensymed_symbol_3 = 
		get_lookup_slot_value_given_default(new_attribute_value,
		Qparent_attribute_name,Nil);
	set_non_savable_lookup_slot_value(new_attribute_value,
		Qparent_frame,frame);
	gensymed_symbol_3 = 
		get_lookup_slot_value_given_default(new_attribute_value,
		Qparent_attribute_name,Nil);
	if (parent_slot_defining_class_qm) {
	    new_cons = ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_slot_value_cons_pool();
	    M_CAR(gensymed_symbol_4) = parent_pretty_slot_name;
	    M_CDR(gensymed_symbol_4) = parent_slot_defining_class_qm;
	    inline_note_allocate_cons(gensymed_symbol_4,Qab_slot_value);
	    temp_1 = gensymed_symbol_4;
	}
	else
	    temp_1 = parent_pretty_slot_name;
	set_non_savable_lookup_slot_value(new_attribute_value,
		Qparent_attribute_name,temp_1);
	reclaim_slot_value(gensymed_symbol_3);
    }
    if ( !TRUEP(initializing_qm) && old_attribute_value) {
	if ( !EQ(old_attribute_value,ISVREF(slot_description,(SI_Long)6L)))
	    reclaim_slot_value(old_attribute_value);
    }
    return VALUES_1(new_attribute_value);
}

static Object Qslot_putter;        /* slot-putter */

static Object Qslot_category;      /* slot-category */

static Object Qput_attribute_value;  /* put-attribute-value */

/* TW-CHANGE-SLOT-DESCRIPTION-VALUE */
Object tw_change_slot_description_value(frame,slot_description,new_value,
	    pretty_slot_name,defining_class)
    Object frame, slot_description, new_value, pretty_slot_name;
    Object defining_class;
{
    Object old_value, do_not_reclaim_old_value_qm, slot_putter_qm, list_1;
    Object return_value, vector_slot_index_qm, user_vector_slot_index_qm;
    Object slot_name, lookup_structure_qm, slot_index_qm, gensymed_symbol;
    Object gensymed_symbol_1, slot_features, sub_class_bit_vector;
    SI_Long max_i, i, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;
    Object result;

    x_note_fn_call(247,28);
    old_value = Nil;
    do_not_reclaim_old_value_qm = Nil;
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	slot_putter_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
		Qslot_putter);
	if (slot_putter_qm);
	else {
	    list_1 = INLINE_SYMBOL_PLIST(pretty_slot_name);
	  next_loop:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qslot_category))
		goto end_loop;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop;
	  end_loop:;
	    slot_putter_qm =  !(list_1 ? TRUEP(M_CAR(M_CDR(list_1))) : 
		    TRUEP(Nil)) ? Qput_attribute_value : Nil;
	}
    }
    else
	slot_putter_qm = Qput_attribute_value;
    if (EQ(slot_putter_qm,Qput_attribute_value)) {
	do_not_reclaim_old_value_qm = T;
	return_value = tw_put_attribute_description_value(frame,
		slot_description,new_value,Nil);
    }
    else {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    old_value = ISVREF(frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		old_value = ISVREF(ISVREF(frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_1:
		    if (i >= ab_loop_bind_)
			goto end_loop_1;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_1;
		  end_loop_1:
		    slot_index_qm = Qnil;
		  end_1:;
		    old_value = slot_index_qm ? ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    old_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if (slot_putter_qm) {
	    result = inline_funcall_3(slot_putter_qm,frame,new_value,Nil);
	    MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	    do_not_reclaim_old_value_qm = gensymed_symbol_1;
	    return_value = gensymed_symbol;
	}
	else {
	    if (Noting_changes_to_kb_p) {
		slot_features = ISVREF(slot_description,(SI_Long)9L);
		temp = assq_function(Qtype,slot_features) ?  
			!TRUEP(assq_function(Qdo_not_save,slot_features)) :
			 TRUEP(assq_function(Qsave,slot_features));
		if (temp);
		else
		    temp = TRUEP(assq_function(Qnote_slot_changes,
			    ISVREF(slot_description,(SI_Long)9L)));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    note_change_to_block_1(frame,ISVREF(slot_description,
			    (SI_Long)2L));
		else
		    note_change_to_dependent_frame_1();
	    }
	    return_value = set_slot_description_value_without_noting(frame,
		    slot_description,new_value);
	}
    }
    if ( !TRUEP(do_not_reclaim_old_value_qm) && old_value &&  
	    !EQ(new_value,old_value) &&  !FIXNUMP(old_value) &&  
	    !EQ(old_value,ISVREF(slot_description,(SI_Long)6L)))
	reclaim_slot_value(old_value);
    return VALUES_1(return_value);
}

Object Tw_predefined_user_attributes = UNBOUND;

/* EVALUATION-SEQUENCE-WITHOUT-ELEMENTS */
Object evaluation_sequence_without_elements(sequence,evaluation_value,
	    first_only_p)
    Object sequence, evaluation_value, first_only_p;
{
    Object remove_p, eval_list, gensymed_symbol, held_vector, element, elt_1;
    Object validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(247,29);
    remove_p = T;
    eval_list = Qnil;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    element = Nil;
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
    element = validated_elt;
    if (remove_p && evaluation_value_eq(element,evaluation_value)) {
	if (first_only_p)
	    remove_p = Nil;
    }
    else {
	temp = FIXNUMP(element) || element && SYMBOLP(element) || 
		SIMPLE_VECTOR_P(element) ? element : 
		copy_if_evaluation_value_1(element);
	eval_list = eval_cons_1(temp,eval_list);
    }
    goto next_loop;
  end_loop:
    temp = eval_list;
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(nreverse(temp));
}

/* MAKE-GESTURE-VALUE-NODE */
Object make_gesture_value_node(type,op,args)
    Object type, op, args;
{
    x_note_fn_call(247,30);
    return phrase_cons(type,phrase_cons(op,args));
}

static Object Qsymbol_constant;    /* symbol-constant */

/* CONSTANT-SYMBOL-VALUE-NODE-OF-SYMBOL-P */
Object constant_symbol_value_node_of_symbol_p(node,symbol)
    Object node, symbol;
{
    Object temp;

    x_note_fn_call(247,31);
    if (EQ(CAR(node),Qsymbol) && EQ(CADR(node),Qsymbol_constant)) {
	temp = CDDR(node);
	temp = EQ(CAR(temp),symbol) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qab_class;           /* class */

static Object Qvalue2frame;        /* value2frame */

static Object Qab_structure;       /* structure */

static Object Qstruct;             /* struct */

static Object Qvalue2struct;       /* value2struct */

static Object Qvalue2sequence;     /* value2sequence */

static Object Qdatum;              /* datum */

static Object Qvalue2datum;        /* value2datum */

static Object Qvalue2symbol;       /* value2symbol */

static Object Qvalue2float;        /* value2float */

static Object Qvalue2quantity;     /* value2quantity */

static Object Qvalue2integer;      /* value2integer */

static Object Qtext;               /* text */

static Object Qvalue2text;         /* value2text */

static Object Qtruth_value;        /* truth-value */

static Object Qvalue2truth_value;  /* value2truth-value */

/* GET-CAST-OPERATOR */
Object get_cast_operator(source_type,target_type)
    Object source_type, target_type;
{
    Object temp;

    x_note_fn_call(247,32);
    if (CONSP(target_type)) {
	temp = CAR(target_type);
	if (EQ(temp,Qab_class))
	    return VALUES_2(Qvalue2frame,CADR(target_type));
	else if (EQ(temp,Qab_structure) || EQ(temp,Qstruct))
	    return VALUES_1(Qvalue2struct);
	else if (EQ(temp,Qsequence))
	    return VALUES_1(Qvalue2sequence);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(target_type,Qdatum))
	return VALUES_1(Qvalue2datum);
    else if (EQ(target_type,Qsymbol))
	return VALUES_1(Qvalue2symbol);
    else if (EQ(target_type,Qfloat))
	return VALUES_1(Qvalue2float);
    else if (EQ(target_type,Qnumber))
	return VALUES_1(Qvalue2quantity);
    else if (EQ(target_type,Qinteger))
	return VALUES_1(Qvalue2integer);
    else if (EQ(target_type,Qtext))
	return VALUES_1(Qvalue2text);
    else if (EQ(target_type,Qtruth_value))
	return VALUES_1(Qvalue2truth_value);
    else
	return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_code_sequences, Qcurrent_gesture_code_sequences);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_code_sequence, Qcurrent_gesture_code_sequence);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_sequence_index, Qcurrent_gesture_sequence_index);

DEFINE_VARIABLE_WITH_SYMBOL(Current_gesture_label_index, Qcurrent_gesture_label_index);

DEFINE_VARIABLE_WITH_SYMBOL(Gesture_source_stack, Qgesture_source_stack);

/* NEW-GESTURE-CODE-SEQUENCE */
Object new_gesture_code_sequence()
{
    Object current_gesture_sequence_index_new_value, new_gcs;

    x_note_fn_call(247,33);
    current_gesture_sequence_index_new_value = 
	    FIXNUM_ADD1(Current_gesture_sequence_index);
    Current_gesture_sequence_index = current_gesture_sequence_index_new_value;
    new_gcs = gensym_list_3(Current_gesture_sequence_index,Nil,Nil);
    Current_gesture_code_sequences = gensym_cons_1(new_gcs,
	    Current_gesture_code_sequences);
    return VALUES_1(new_gcs);
}

/* WRITE-GESTURE-CODE-INSTRUCTION */
Object write_gesture_code_instruction(gcs,instruction)
    Object gcs, instruction;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, temp;

    x_note_fn_call(247,34);
    gensym_push_modify_macro_arg = instruction;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = CADR(gcs);
    temp = gensym_cons_1(car_1,cdr_1);
    M_CADR(gcs) = temp;
    gensym_push_modify_macro_arg = CAR(Gesture_source_stack);
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = CADDR(gcs);
    temp = gensym_cons_1(car_1,cdr_1);
    return VALUES_1(M_CADDR(gcs) = temp);
}

/* EMIT-GESTURE-INSTRUCTION-WITH-CONSTANTS */
Object emit_gesture_instruction_with_constants(instruction,constants)
    Object instruction, constants;
{
    x_note_fn_call(247,35);
    return write_gesture_code_instruction(Current_gesture_code_sequence,
	    gensym_cons_1(instruction,constants));
}

/* NEW-GESTURE-LOCAL */
Object new_gesture_local(name,index_1,type)
    Object name, index_1, type;
{
    Object local;

    x_note_fn_call(247,36);
    local = make_gesture_local_1(name,index_1,type);
    return VALUES_1(local);
}

/* ADD-VARIABLE-DATA-TO-GESTURE */
Object add_variable_data_to_gesture(gesture,args,locals,returns)
    Object gesture, args, locals, returns;
{
    Object count_1, res, name, type, ab_loop_list_, ab_loop_iter_flag_;
    Object ab_loop_desetq_, temp, svref_new_value;
    SI_Long i;

    x_note_fn_call(247,37);
    count_1 = length(args);
    res = Qnil;
    name = Nil;
    type = Nil;
    ab_loop_list_ = args;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    temp = new_gesture_local(name,FIX(i - IFIX(count_1)),type);
    res = gensym_cons_1(temp,res);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    SVREF(gesture,FIX((SI_Long)1L)) = count_1;
    svref_new_value = nreverse(res);
    SVREF(gesture,FIX((SI_Long)2L)) = svref_new_value;
    count_1 = length(locals);
    res = Qnil;
    name = Nil;
    type = Nil;
    ab_loop_list_ = locals;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    temp = new_gesture_local(name,FIX(i + IFIX(Frame_header_size)),type);
    res = gensym_cons_1(temp,res);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    SVREF(gesture,FIX((SI_Long)3L)) = count_1;
    svref_new_value = nreverse(res);
    SVREF(gesture,FIX((SI_Long)4L)) = svref_new_value;
    count_1 = length(returns);
    res = Qnil;
    name = Nil;
    type = Nil;
    ab_loop_list_ = returns;
    i = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i + (SI_Long)1L;
    temp = new_gesture_local(name,FIX(i),type);
    res = gensym_cons_1(temp,res);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_2;
  end_loop_2:
    SVREF(gesture,FIX((SI_Long)5L)) = count_1;
    svref_new_value = nreverse(res);
    SVREF(gesture,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(Qnil);
}

/* EMIT-COMPILED-GESTURE */
Object emit_compiled_gesture(compiled_gesture)
    Object compiled_gesture;
{
    Object args, returns, locals, body, gesture;
    Object current_gesture_code_sequences, current_gesture_sequence_index;
    Object current_gesture_label_index, outer_code_sequence, temp;
    Object instruction_vector, source_vector_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(247,38);
    args = CADR(compiled_gesture);
    returns = CADDR(compiled_gesture);
    locals = CADDDR(compiled_gesture);
    body = FIFTH(compiled_gesture);
    gesture = make_gesture_function_1();
    current_gesture_code_sequences = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gesture_code_sequences,Qcurrent_gesture_code_sequences,current_gesture_code_sequences,
	    2);
      current_gesture_sequence_index = FIX((SI_Long)-1L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_gesture_sequence_index,Qcurrent_gesture_sequence_index,current_gesture_sequence_index,
	      1);
	current_gesture_label_index = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_gesture_label_index,Qcurrent_gesture_label_index,current_gesture_label_index,
		0);
	  outer_code_sequence = new_gesture_code_sequence();
	  Gesture_source_stack = Nil;
	  add_variable_data_to_gesture(gesture,args,locals,returns);
	  emit_compiled_gesture_statement(body,outer_code_sequence);
	  SVREF(gesture,FIX((SI_Long)8L)) = Nil;
	  temp = nreverse(CADR(outer_code_sequence));
	  M_CADR(outer_code_sequence) = temp;
	  temp = nreverse(CADDR(outer_code_sequence));
	  M_CADDR(outer_code_sequence) = temp;
	  result = assemble_gesture_code_sequence(outer_code_sequence,gesture);
	  MVS_2(result,instruction_vector,source_vector_qm);
	  SVREF(gesture,FIX((SI_Long)8L)) = instruction_vector;
	  SVREF(gesture,FIX((SI_Long)11L)) = source_vector_qm;
	  result = VALUES_1(gesture);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object Obsolete_gesture_instruction_map = UNBOUND;

static Object Qlabel;              /* label */

static Object Qab_gensym;          /* gensym */

static Object Qbranch_always;      /* branch-always */

static Object Qbranch_if_true;     /* branch-if-true */

static Object Qbranch_if_false;    /* branch-if-false */

static Object Qpush_thread_state;  /* push-thread-state */

static Object Qget_local;          /* get-local */

static Object Qget_local_or_no_item;  /* get-local-or-no-item */

static Object Qset_local;          /* set-local */

static Object Qset_local_from_return;  /* set-local-from-return */

static Object Qgesture_instruction;  /* gesture-instruction */

/* ASSEMBLE-GESTURE-CODE-SEQUENCE */
Object assemble_gesture_code_sequence(code_sequence,gesture)
    Object code_sequence, gesture;
{
    Object instruction_name, ignore, ab_loop_list_, ab_loop_desetq_;
    Object number_of_real_instructions, code_vector, source_vector;
    Object label_table, instruction_index, instruction_sources;
    Object instruction_source, instruction, replacement_instruction_name_qm;
    Object temp, gensym_pop_store, cons_1, next_cons, temp_1, svref_arg_2;
    Object mnemonic, gensymed_symbol;
    SI_Long ab_loopvar_, i, ab_loop_bind_, cadr_new_value;

    x_note_fn_call(247,39);
    instruction_name = Nil;
    ignore = Nil;
    ab_loop_list_ = CADR(code_sequence);
    ab_loopvar_ = (SI_Long)0L;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    instruction_name = CAR(ab_loop_desetq_);
    ignore = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(instruction_name,Qlabel))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    number_of_real_instructions = FIX(ab_loopvar_);
    goto end_1;
    number_of_real_instructions = Qnil;
  end_1:;
    code_vector = allocate_managed_simple_vector(number_of_real_instructions);
    source_vector = Tw_source_debug_p ? 
	    allocate_managed_simple_vector(number_of_real_instructions) : Qnil;
    label_table = Nil;
    instruction_index = FIX((SI_Long)0L);
    instruction_sources = CADDR(code_sequence);
    instruction_source = Nil;
    instruction = Nil;
    ab_loop_list_ = CADR(code_sequence);
    replacement_instruction_name_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    instruction = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = assq_function(CAR(instruction),Obsolete_gesture_instruction_map);
    replacement_instruction_name_qm = CDR(temp);
    if (replacement_instruction_name_qm)
	M_CAR(instruction) = replacement_instruction_name_qm;
    if (Tw_source_debug_p) {
	gensym_pop_store = Nil;
	cons_1 = instruction_sources;
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
	instruction_sources = next_cons;
	instruction_source = gensym_pop_store;
    }
    if (EQ(CAR(instruction),Qlabel))
	label_table = gensym_cons_1(gensym_cons_1(CADR(instruction),
		instruction_index),label_table);
    else {
	SVREF(code_vector,instruction_index) = instruction;
	if (Tw_source_debug_p)
	    SVREF(source_vector,instruction_index) = instruction_source;
	instruction_index = FIXNUM_ADD1(instruction_index);
    }
    goto next_loop_1;
  end_loop_1:;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_real_instructions);
    instruction = Nil;
    mnemonic = Nil;
  next_loop_2:
    if (i >= ab_loop_bind_)
	goto end_loop_2;
    instruction = ISVREF(code_vector,i);
    mnemonic = CAR(instruction);
    if (EQ(mnemonic,Qbranch_always) || EQ(mnemonic,Qbranch_if_true) || 
	    EQ(mnemonic,Qbranch_if_false) || EQ(mnemonic,Qpush_thread_state)) {
	temp = assq_function(CADR(instruction),label_table);
	cadr_new_value = IFIX(CDR(temp)) - i - (SI_Long)1L;
	M_CADR(instruction) = FIX(cadr_new_value);
    }
    else if (EQ(mnemonic,Qget_local) || EQ(mnemonic,Qget_local_or_no_item) 
	    || EQ(mnemonic,Qset_local) || EQ(mnemonic,
		Qset_local_from_return)) {
	temp_1 = resolve_gesture_local_variable(gesture,CADR(instruction));
	M_CADR(instruction) = temp_1;
    }
    gensymed_symbol = CAR(instruction);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qgesture_instruction);
    if (temp);
    else
	temp = error((SI_Long)2L,"Unknown instruction mnemonic ~s~%",
		CAR(instruction));
    temp_1 = CADR(temp);
    M_CAR(instruction) = temp_1;
    i = i + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    reclaim_gensym_tree_1(label_table);
    return VALUES_2(code_vector,source_vector);
}

/* RESOLVE-GESTURE-LOCAL-VARIABLE */
Object resolve_gesture_local_variable(gesture,var_name)
    Object gesture, var_name;
{
    Object local, ab_loop_list_, name, temp;

    x_note_fn_call(247,40);
    local = Nil;
    ab_loop_list_ = ISVREF(gesture,(SI_Long)2L);
    name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name = ISVREF(local,(SI_Long)1L);
    if (EQ(name,var_name)) {
	temp = ISVREF(local,(SI_Long)2L);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	local = Nil;
	ab_loop_list_ = ISVREF(gesture,(SI_Long)4L);
	name = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	local = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	name = ISVREF(local,(SI_Long)1L);
	if (EQ(name,var_name))
	    return VALUES_1(ISVREF(local,(SI_Long)2L));
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object Qlocal_assignment;   /* local-assignment */

static Object Qchange_slot;        /* change-slot */

static Object Qset_slot;           /* set-slot */

static Object Qchange_array_length;  /* change-array-length */

static Object Qab_if;              /* if */

static Object Qfor_loop_integer;   /* for-loop-integer */

static Object Qgreater_than_fixnum;  /* greater-than-fixnum */

static Object Qless_than_fixnum;   /* less-than-fixnum */

static Object Qpush_fixnum;        /* push-fixnum */

static Object Qadd_fixnum;         /* add-fixnum */

static Object Qgesture_call;       /* gesture-call */

static Object Qgesture_call_next_method;  /* gesture-call-next-method */

static Object Qcall_g2;            /* call-g2 */

static Object Qpush_gesture_def;   /* push-gesture-def */

static Object Qpush_next_method;   /* push-next-method */

static Object Qcheck_args;         /* check-args */

static Object Qprocedure_call;     /* procedure-call */

static Object Qcall_in_g2;         /* call-in-g2 */

static Object Qreturn_check;       /* return-check */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qprocedure_return;   /* procedure-return */

static Object Qrepeat;             /* repeat */

static Object Qexit_if;            /* exit-if */

static Object Qcompound_statement;  /* compound-statement */

static Object Qbegin;              /* begin */

static Object Qcompound_statement_with_error_handling;  /* compound-statement-with-error-handling */

static Object Qcompound_statement_with_unwind_protection;  /* compound-statement-with-unwind-protection */

static Object Qon_error;           /* on-error */

static Object Qon_exit;            /* on-exit */

/* EMIT-COMPILED-GESTURE-STATEMENT */
Object emit_compiled_gesture_statement(statement,code_sequence)
    Object statement, code_sequence;
{
    Object statement_type, statement_subforms, current_gesture_code_sequence;
    Object test_expression, then_clause, else_clause_qm, temp, end_label;
    Object else_label, iteration_var_name, limit_var_name;
    Object initial_value_expression, limit_value_expression, increment;
    Object increasing_p, loop_body, loop_top, loop_exit;
    Object assignment_variable_list, assignment_type_list, compiled_arg_list;
    Object assignment_count, compiled_arg, ab_loop_list_, assignment_var_name;
    Object assignment_var_type, ab_loop_list__1, cast_operator;
    Object additional_arg_qm, compiled_value_list, compiled_value, repeat_top;
    Object statement_list, protecting_statement_qm, on_error_var_and_type_qm;
    Object after_protect, cleanup_start, temp_1, var_and_type;
    Object gensym_pop_store, cons_1, next_cons, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(247,41);
    if (Tw_source_debug_p)
	Gesture_source_stack = gensym_cons_1(statement,Gesture_source_stack);
    statement_type = CAR(statement);
    statement_subforms = CDR(statement);
    current_gesture_code_sequence = code_sequence;
    PUSH_SPECIAL_WITH_SYMBOL(Current_gesture_code_sequence,Qcurrent_gesture_code_sequence,current_gesture_code_sequence,
	    0);
      if (EQ(statement_type,Qlocal_assignment)) {
	  emit_compiled_gesture_expression(THIRD(statement_subforms));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_local,FIRST(statement_subforms)));
      }
      else if (EQ(statement_type,Qchange_slot)) {
	  emit_compiled_gesture_expression(THIRD(statement_subforms));
	  emit_compiled_gesture_expression(SECOND(statement_subforms));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_slot,FIRST(statement_subforms)));
      }
      else if (EQ(statement_type,Qchange_array_length));
      else if (EQ(statement_type,Qab_if)) {
	  test_expression = FIRST(statement_subforms);
	  then_clause = SECOND(statement_subforms);
	  else_clause_qm = THIRD(statement_subforms);
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  end_label = Current_gesture_label_index;
	  if (else_clause_qm) {
	      temp = FIXNUM_ADD1(Current_gesture_label_index);
	      Current_gesture_label_index = temp;
	      else_label = Current_gesture_label_index;
	      emit_compiled_gesture_expression(test_expression);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qbranch_if_false,else_label));
	      emit_compiled_gesture_statement(then_clause,code_sequence);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qbranch_always,end_label));
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qlabel,else_label));
	      emit_compiled_gesture_statement(else_clause_qm,code_sequence);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qlabel,end_label));
	  }
	  else {
	      emit_compiled_gesture_expression(test_expression);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qbranch_if_false,end_label));
	      emit_compiled_gesture_statement(then_clause,code_sequence);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qlabel,end_label));
	  }
      }
      else if (EQ(statement_type,Qfor_loop_integer)) {
	  iteration_var_name = FIRST(statement_subforms);
	  limit_var_name = SECOND(statement_subforms);
	  initial_value_expression = THIRD(statement_subforms);
	  limit_value_expression = FOURTH(statement_subforms);
	  increment = FIFTH(statement_subforms);
	  increasing_p = SIXTH(statement_subforms);
	  loop_body = SEVENTH(statement_subforms);
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  loop_top = Current_gesture_label_index;
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  loop_exit = Current_gesture_label_index;
	  emit_compiled_gesture_expression(initial_value_expression);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_local,iteration_var_name));
	  emit_compiled_gesture_expression(limit_value_expression);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_local,limit_var_name));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qlabel,loop_top));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qget_local,iteration_var_name));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qget_local,limit_var_name));
	  if (increasing_p)
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_cons_1(Qgreater_than_fixnum,Nil));
	  else
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_cons_1(Qless_than_fixnum,Nil));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qbranch_if_true,loop_exit));
	  emit_compiled_gesture_statement(loop_body,code_sequence);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qpush_fixnum,increment));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qget_local,iteration_var_name));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_cons_1(Qadd_fixnum,Nil));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_local,iteration_var_name));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qbranch_always,loop_top));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qlabel,loop_exit));
      }
      else if (EQ(statement_type,Qgesture_call) || EQ(statement_type,
	      Qgesture_call_next_method) || EQ(statement_type,Qcall_g2)) {
	  assignment_variable_list = SECOND(statement_subforms);
	  assignment_type_list = THIRD(statement_subforms);
	  compiled_arg_list = FOURTH(statement_subforms);
	  assignment_count = length(assignment_variable_list);
	  compiled_arg = Nil;
	  ab_loop_list_ = compiled_arg_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  compiled_arg = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  emit_compiled_gesture_expression(compiled_arg);
	  goto next_loop;
	end_loop:;
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qpush_fixnum,length(compiled_arg_list)));
	  if (EQ(statement_type,Qgesture_call) || EQ(statement_type,Qcall_g2))
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qpush_gesture_def,
		      FIRST(statement_subforms)));
	  else if (EQ(statement_type,Qgesture_call_next_method))
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qpush_next_method,
		      FIRST(statement_subforms)));
	  else
	      error((SI_Long)2L,
		      "The value of STATEMENT-TYPE (~s), is not one of (GESTURE-CALL CALL-G2 GESTURE-CALL-NEXT-METHOD).",
		      statement_type);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_cons_1(Qcheck_args,Nil));
	  if (EQ(statement_type,Qgesture_call) || EQ(statement_type,
		  Qgesture_call_next_method))
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_cons_1(Qprocedure_call,Nil));
	  else if (EQ(statement_type,Qcall_g2))
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_cons_1(Qcall_in_g2,Nil));
	  else
	      error((SI_Long)2L,
		      "The value of STATEMENT-TYPE (~s), is not one of (GESTURE-CALL GESTURE-CALL-NEXT-METHOD CALL-G2).",
		      statement_type);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qreturn_check,assignment_count));
	  assignment_var_name = Nil;
	  ab_loop_list_ = assignment_variable_list;
	  assignment_var_type = Nil;
	  ab_loop_list__1 = assignment_type_list;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  assignment_var_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  assignment_var_type = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  result = get_cast_operator(Qitem_or_datum,assignment_var_type);
	  MVS_2(result,cast_operator,additional_arg_qm);
	  if (EQ(assignment_var_type,Qitem_or_datum));
	  else if (additional_arg_qm)
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(cast_operator,additional_arg_qm));
	  else
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_cons_1(cast_operator,Nil));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qset_local_from_return,assignment_var_name));
	  goto next_loop_1;
	end_loop_1:;
      }
      else if (EQ(statement_type,Qreturn)) {
	  compiled_value_list = FIRST(statement_subforms);
	  compiled_value = Nil;
	  ab_loop_list_ = compiled_value_list;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  compiled_value = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  emit_compiled_gesture_expression(compiled_value);
	  goto next_loop_2;
	end_loop_2:;
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qpush_fixnum,length(compiled_value_list)));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_cons_1(Qprocedure_return,Nil));
      }
      else if (EQ(statement_type,Qrepeat)) {
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  repeat_top = Current_gesture_label_index;
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qlabel,repeat_top));
	  emit_compiled_gesture_statement(FIRST(statement_subforms),
		  code_sequence);
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qbranch_always,repeat_top));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qlabel,SECOND(statement_subforms)));
      }
      else if (EQ(statement_type,Qexit_if)) {
	  emit_compiled_gesture_expression(FIRST(statement_subforms));
	  write_gesture_code_instruction(Current_gesture_code_sequence,
		  gensym_list_2(Qbranch_if_true,SECOND(statement_subforms)));
      }
      else if (EQ(statement_type,Qcompound_statement) || EQ(statement_type,
	      Qbegin) || EQ(statement_type,
	      Qcompound_statement_with_error_handling) || 
	      EQ(statement_type,Qcompound_statement_with_unwind_protection)) {
	  statement_list = FIRST(statement_subforms);
	  protecting_statement_qm = SECOND(statement_subforms);
	  on_error_var_and_type_qm = protecting_statement_qm ? 
		  CADR(protecting_statement_qm) : Qnil;
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  after_protect = Current_gesture_label_index;
	  temp = FIXNUM_ADD1(Current_gesture_label_index);
	  Current_gesture_label_index = temp;
	  cleanup_start = Current_gesture_label_index;
	  if (protecting_statement_qm)
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_3(Qpush_thread_state,cleanup_start,
		      EQ(statement_type,
		      Qcompound_statement_with_error_handling) ? 
		      M_CAR(M_CDR(CADR(on_error_var_and_type_qm))) : Qnil));
	  statement = Nil;
	  ab_loop_list_ = statement_list;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  statement = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  emit_compiled_gesture_statement(statement,code_sequence);
	  goto next_loop_3;
	end_loop_3:;
	  if (protecting_statement_qm) {
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qbranch_always,after_protect));
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qlabel,cleanup_start));
	      temp_1 = CAR(protecting_statement_qm);
	      if (EQ(temp_1,Qon_error)) {
		  var_and_type = SECOND(protecting_statement_qm);
		  write_gesture_code_instruction(Current_gesture_code_sequence,
			  gensym_list_2(Qset_local,CAR(var_and_type)));
		  emit_compiled_gesture_statement(THIRD(protecting_statement_qm),
			  code_sequence);
	      }
	      else if (EQ(temp_1,Qon_exit))
		  emit_compiled_gesture_statement(THIRD(protecting_statement_qm),
			  code_sequence);
	      write_gesture_code_instruction(Current_gesture_code_sequence,
		      gensym_list_2(Qlabel,after_protect));
	  }
      }
    POP_SPECIAL();
    if (Tw_source_debug_p) {
	gensym_pop_store = Nil;
	cons_1 = Gesture_source_stack;
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
	Gesture_source_stack = next_cons;
	return VALUES_1(gensym_pop_store);
    }
    else
	return VALUES_1(Nil);
}

static Object Qget_slot;           /* get-slot */

static Object Qget_slot_or_no_item;  /* get-slot-or-no-item */

static Object Qarray_length;       /* array-length */

static Object Qif_expression;      /* if-expression */

static Object Qtype_test;          /* type-test */

static Object Qvalue2type;         /* value2type */

static Object Qunevaluated_constant;  /* unevaluated-constant */

/* EMIT-COMPILED-GESTURE-EXPRESSION */
Object emit_compiled_gesture_expression(node)
    Object node;
{
    Object instruction_name, args, temp, gensymed_symbol, condition, then;
    Object else_1, temp_1, else_label, end_label, constants, arg;
    Object ab_loop_list_, gensym_pop_store, cons_1, next_cons, svref_arg_2;

    x_note_fn_call(247,42);
    if (Tw_source_debug_p)
	Gesture_source_stack = gensym_cons_1(node,Gesture_source_stack);
    if (primitive_gesture_value_node_p(node))
	emit_primitive_gesture_value_node(node);
    else {
	instruction_name = get_instruction_for_gesture_value_node(node);
	args = CDDR(node);
	if (EQ(instruction_name,Qget_slot) || EQ(instruction_name,
		Qget_slot_or_no_item)) {
	    temp = CDDR(node);
	    emit_compiled_gesture_expression(FIRST(temp));
	    temp = CDDR(node);
	    temp = SECOND(temp);
	    temp = CDDR(temp);
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_3(Qget_slot,FIRST(temp),
		    EQ(instruction_name,Qget_slot_or_no_item) ? T : Nil));
	}
	else if (EQ(instruction_name,Qarray_length));
	else if (EQ(instruction_name,Qif_expression)) {
	    gensymed_symbol = args;
	    condition = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    then = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    else_1 = CAR(gensymed_symbol);
	    temp_1 = FIXNUM_ADD1(Current_gesture_label_index);
	    Current_gesture_label_index = temp_1;
	    else_label = Current_gesture_label_index;
	    temp_1 = FIXNUM_ADD1(Current_gesture_label_index);
	    Current_gesture_label_index = temp_1;
	    end_label = Current_gesture_label_index;
	    emit_compiled_gesture_expression(condition);
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_2(Qbranch_if_false,else_label));
	    emit_compiled_gesture_expression(then);
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_2(Qbranch_always,end_label));
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_2(Qlabel,else_label));
	    emit_compiled_gesture_expression(else_1);
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_2(Qlabel,end_label));
	}
	else if (EQ(instruction_name,Qtype_test) || EQ(instruction_name,
		Qvalue2type) || EQ(instruction_name,Qvalue2frame)) {
	    emit_compiled_gesture_expression(CAR(args));
	    write_gesture_code_instruction(Current_gesture_code_sequence,
		    gensym_list_2(instruction_name,
		    copy_tree_using_gensym_conses_1(CADR(args))));
	}
	else {
	    constants = Nil;
	    arg = Nil;
	    ab_loop_list_ = args;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    arg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(CAR(arg),Qunevaluated_constant))
		constants = gensym_cons_1(CADR(arg),constants);
	    else
		emit_compiled_gesture_expression(arg);
	    goto next_loop;
	  end_loop:
	    constants = nreverse(constants);
	    emit_gesture_instruction_with_constants(instruction_name,
		    constants);
	}
    }
    if (Tw_source_debug_p) {
	gensym_pop_store = Nil;
	cons_1 = Gesture_source_stack;
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
	Gesture_source_stack = next_cons;
	return VALUES_1(gensym_pop_store);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* PRIMITIVE-GESTURE-VALUE-NODE-P */
Object primitive_gesture_value_node_p(node)
    Object node;
{
    x_note_fn_call(247,43);
    return memq_function(CADR(node),list_constant);
}

static Object Qfetch_local;        /* fetch-local */

static Object Qfetch_local_or_no_item;  /* fetch-local-or-no-item */

static Object Qinteger_constant;   /* integer-constant */

static Object Qfloat_constant;     /* float-constant */

static Object Qpush_float;         /* push-float */

static Object Qlong_constant;      /* long-constant */

static Object Qpush_long;          /* push-long */

static Object Qpush_symbol;        /* push-symbol */

static Object Qtext_constant;      /* text-constant */

static Object Qpush_text;          /* push-text */

static Object Qtruth_value_constant;  /* truth-value-constant */

static Object Qpush_truth_value;   /* push-truth-value */

static Object string_constant;     /* "The value of (CADR NODE) (~s), is not one of (FETCH-LOCAL FETCH-LOCAL-OR-NO-ITEM INTEGER-CONSTANT FLOAT-CONSTANT LONG-CONSTANT SYMBOL-CONSTANT TEXT-CONSTANT TRUTH-VALUE-CONSTANT)." */

/* EMIT-PRIMITIVE-GESTURE-VALUE-NODE */
Object emit_primitive_gesture_value_node(node)
    Object node;
{
    Object args, temp;

    x_note_fn_call(247,44);
    args = CDDR(node);
    temp = CADR(node);
    if (EQ(temp,Qfetch_local))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qget_local,CAR(args)));
    else if (EQ(temp,Qfetch_local_or_no_item))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qget_local_or_no_item,CAR(args)));
    else if (EQ(temp,Qinteger_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_fixnum,CAR(args)));
    else if (EQ(temp,Qfloat_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_float,CAR(args)));
    else if (EQ(temp,Qlong_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_long,CAR(args)));
    else if (EQ(temp,Qsymbol_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_symbol,CAR(args)));
    else if (EQ(temp,Qtext_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_text,CAR(args)));
    else if (EQ(temp,Qtruth_value_constant))
	return write_gesture_code_instruction(Current_gesture_code_sequence,
		gensym_list_2(Qpush_truth_value,CAR(args)));
    else
	return errorn(2,string_constant,CADR(node));
}

/* GET-INSTRUCTION-FOR-GESTURE-VALUE-NODE */
Object get_instruction_for_gesture_value_node(node)
    Object node;
{
    Object operation;

    x_note_fn_call(247,45);
    operation = CADR(node);
    return VALUES_1(operation);
}

void events_INIT()
{
    Object temp, reclaim_structure_for_gesture_thread_1;
    Object reclaim_structure_for_gesture_function_1;
    Object reclaim_structure_for_gesture_local_1;
    Object all_gesture_instruction_names_new_value;
    Object AB_package, list_constant_861, list_constant_860, list_constant_859;
    Object Qset_structure_slot, Qset_struct_slot, Qmake_structure;
    Object Qmake_struct, list_constant_379, Qdivide_float, list_constant_422;
    Object list_constant_417, Qremainder_float, Qquotient_float;
    Object list_constant_418, Qless_than_equal_float, list_constant_410;
    Object list_constant_396, Qgreater_than_equal_float, list_constant_406;
    Object Qless_than_float, list_constant_402, Qgreater_than_float;
    Object list_constant_397, Qnegate_float, list_constant_388, Qint2float;
    Object list_constant_858, list_constant_857, list_constant_91;
    Object Qgesture_push, Qequal_float, list_constant_377, Qmultiply_float;
    Object list_constant_372, Qsubtract_float, list_constant_369, Qadd_float;
    Object list_constant_366, list_constant_856, list_constant_20;
    Object list_constant_855, list_constant_567, list_constant_854;
    Object list_constant_853, list_constant_852, list_constant_572;
    Object list_constant_851, Qgesture_evaluation_error;
    Object Qvalue_is_not_a_structure, list_constant_561, list_constant_850;
    Object list_constant_31, Qevaluation_structure_p, list_constant_849;
    Object list_constant_848, list_constant_847, list_constant_846;
    Object list_constant_845, list_constant_844, Qvalue_is_not_a_sequence;
    Object list_constant_843, Qevaluation_sequence_p, Qab_make_sequence;
    Object list_constant_842, list_constant_841, list_constant_840;
    Object list_constant_839, list_constant_838, list_constant_827;
    Object list_constant_837, list_constant_836, list_constant_821;
    Object Qallocate_evaluation_sequence, string_constant_16, Qtw_trace;
    Object list_constant_835, list_constant_2, Qvalue, Qas, Qsequence_length;
    Object Qbelow, Qfrom, Qi, Qfor, Qab_loop, list_constant_824;
    Object list_constant_834, list_constant_833, list_constant_810;
    Object list_constant_38, list_constant_832, list_constant_831;
    Object list_constant_830, list_constant_829, list_constant_828;
    Object list_constant_826, list_constant_825;
    Object Qallocate_evaluation_structure, string_constant_15;
    Object list_constant_823, list_constant_822, Qstruct_length, Qeval_push;
    Object Qeval_list, list_constant_820, list_constant_819, list_constant_818;
    Object list_constant_817, Qwould_be_attribute_name;
    Object Qstructure_attribute_name_not_symbol, list_constant_816;
    Object list_constant_815, list_constant_814, list_constant_559;
    Object list_constant_813, list_constant_812, Qsl_eq_f, list_constant_811;
    Object Qlogandf, string_constant_14, list_constant_95, list_constant_809;
    Object list_constant_87, list_constant_808, list_constant_807;
    Object list_constant_806, list_constant_805, list_constant_804;
    Object list_constant_803, list_constant_802, list_constant_507;
    Object list_constant_800, list_constant_450, list_constant_521;
    Object list_constant_801, Qobtain_mutable_evaluation_structure_copy;
    Object Qattribute_name, list_constant_748, list_constant_513;
    Object list_constant_799, Qsequence_remove_element, list_constant_798;
    Object list_constant_797, list_constant_786, list_constant_796;
    Object list_constant_724, list_constant_795, list_constant_794;
    Object Qnew_sequence, list_constant_326, Qvalue_to_match;
    Object Qevaluation_sequence_without_elements, list_constant_793;
    Object list_constant_792, list_constant_722, list_constant_780;
    Object Qsequence_remove, list_constant_791, list_constant_790;
    Object list_constant_789, list_constant_788, list_constant_742;
    Object list_constant_787, list_constant_785, list_constant_784;
    Object list_constant_783, list_constant_731, list_constant_738;
    Object list_constant_750, Qsequence_remove_index_out_of_range;
    Object list_constant_782, list_constant_781;
    Object Qevaluation_sequence_remove_element_at_index, list_constant_747;
    Object list_constant_195, Qsequence_push, list_constant_779;
    Object list_constant_778, list_constant_777, list_constant_776;
    Object list_constant_775, list_constant_774, list_constant_773;
    Object list_constant_772, Qevaluation_sequence_insert_at_end;
    Object Qevaluation_sequence_insert_at_beginning, list_constant_771;
    Object list_constant_4, list_constant_429, Qset_nth_sequence_element;
    Object list_constant_770, list_constant_769, list_constant_768;
    Object list_constant_743, list_constant_767, list_constant_766;
    Object list_constant_741, list_constant_765, list_constant_764;
    Object list_constant_763, list_constant_734, list_constant_762;
    Object list_constant_761, list_constant_752, list_constant_760;
    Object Qnew_element_index, Qwith, list_constant_759, Qheld_vector;
    Object list_constant_758, list_constant_754, list_constant_757;
    Object list_constant_756, list_constant_755, Qcopy_if_evaluation_value;
    Object Qeq_f, list_constant_753, Qmanaged_svref, Qmanaged_array_length;
    Object Qindex, Qplus_f, Qevaluation_sequence_first_element_index;
    Object Qevaluation_sequence_value, list_constant_751;
    Object Qallocate_new_evaluation_sequence_copy, list_constant_749;
    Object Qregister_4, Qnew_value, Qnth_sequence_element, list_constant_746;
    Object list_constant_745, list_constant_744, list_constant_740;
    Object list_constant_739, list_constant_737, list_constant_736;
    Object Qlength_of_sequence, Qsequence_index_out_of_range;
    Object list_constant_735, list_constant_733, list_constant_732;
    Object Qevaluation_sequence_aref, Qlt_f, list_constant_730;
    Object list_constant_723, list_constant_729, list_constant_728;
    Object list_constant_727, list_constant_726, list_constant_725;
    Object Qevaluation_sequence_length, Qnew_class_instance, list_constant_721;
    Object list_constant_720, list_constant_719;
    Object Qnew_class_instance_is_not_yet_implemented, Qget_class;
    Object list_constant_718, list_constant_717, list_constant_716;
    Object Qclass_operator_is_not_yet_implemented, Qbitwise_and;
    Object list_constant_715, list_constant_714, list_constant_713;
    Object list_constant_363, Qbitwise_or, list_constant_712;
    Object list_constant_711, list_constant_710, Qlogiorf, list_constant_709;
    Object list_constant_687, list_constant_708, list_constant_685;
    Object list_constant_684, list_constant_707, list_constant_706;
    Object list_constant_705, list_constant_704, list_constant_703, Qthing;
    Object list_constant_702, list_constant_701, list_constant_700;
    Object string_constant_8, Qtformat_text_string, Qtype_specification;
    Object Qdesired_type, list_constant_659, Qtype_mismatch, list_constant_699;
    Object list_constant_680, Qclass_test, list_constant_698;
    Object list_constant_697, list_constant_696, list_constant_695;
    Object list_constant_694, list_constant_693, list_constant_683;
    Object list_constant_692, list_constant_691, list_constant_338;
    Object list_constant_690, list_constant_662, Qframe_of_class_p;
    Object list_constant_689, list_constant_678, list_constant_688;
    Object list_constant_686, list_constant_682, list_constant_681;
    Object list_constant_339, Qtype_specification_type_p, list_constant_15;
    Object list_constant_679, list_constant_677, list_constant_676, Qnew_pc;
    Object Qequal_datum, list_constant_675, list_constant_674;
    Object list_constant_673, list_constant_672;
    Object Qmake_evaluation_boolean_value, Qevaluation_value_eq;
    Object Qtw_format_form, list_constant_671, list_constant_670;
    Object list_constant_669, list_constant_668, list_constant_189;
    Object Qnew_text_string, list_constant_667, list_constant_666;
    Object Qtwith_output_to_text_string, list_constant_665, list_constant_664;
    Object Qarg_count, Qwrite_evaluation_value, list_constant_663;
    Object list_constant_661, list_constant_99, list_constant_660;
    Object Qcannot_get_text_of_item, Qframep, list_constant_658;
    Object list_constant_657, Qequal_text, list_constant_656;
    Object list_constant_655, list_constant_654, list_constant_374;
    Object list_constant_653, Qstring_equalw, list_constant_652;
    Object list_constant_651, list_constant_650, Qcopy_evaluation_text;
    Object Qequal_symbol, list_constant_358, Qinvert_truth_value;
    Object list_constant_649, list_constant_648, list_constant_647;
    Object list_constant_646, list_constant_645, list_constant_599;
    Object list_constant_337, list_constant_644, Qevaluation_true_value;
    Object list_constant_643, list_constant_642, list_constant_641;
    Object list_constant_640, list_constant_639, list_constant_638;
    Object list_constant_637, Qtrue, list_constant_636, list_constant_635;
    Object list_constant_634, list_constant_633, list_constant_632;
    Object list_constant_631, list_constant_630, Qvalue_does_not_exist;
    Object list_constant_629, list_constant_617, list_constant_628;
    Object list_constant_627, Qthing_that_is_not_a_value, Qnot_a_value;
    Object list_constant_626, list_constant_625, list_constant_624;
    Object list_constant_623, list_constant_622, list_constant_621;
    Object list_constant_620, list_constant_619, Qnot_tw_item;
    Object list_constant_618, list_constant_616, list_constant_615;
    Object list_constant_614, list_constant_613, list_constant_612;
    Object list_constant_611, Qdesired_class, Qnot_an_instance_of_class;
    Object list_constant_610, Qtarget_class, list_constant_609;
    Object list_constant_13, list_constant_608, list_constant_607;
    Object list_constant_606, list_constant_605, list_constant_604;
    Object list_constant_603, Qvalue_not_of_type_truth_value;
    Object list_constant_602, list_constant_601, list_constant_600, Qab_or;
    Object list_constant_598, list_constant_597, list_constant_596;
    Object list_constant_595, list_constant_594, list_constant_593;
    Object Qvalue_not_of_type_text, list_constant_592, Qtext_string_p;
    Object list_constant_591, list_constant_590, list_constant_589;
    Object list_constant_588, list_constant_587, list_constant_586;
    Object Qvalue_not_of_type_integer, list_constant_578, list_constant_585;
    Object list_constant_584, list_constant_583, list_constant_582;
    Object list_constant_581, list_constant_580, Qvalue_not_of_type_quantity;
    Object list_constant_579, list_constant_570, Qab_fixnump;
    Object list_constant_577, list_constant_576, list_constant_575;
    Object list_constant_574, list_constant_573, list_constant_571;
    Object list_constant_563, Qvalue_not_of_type_float, Qmanaged_float_p;
    Object list_constant_569, list_constant_568, list_constant_566;
    Object list_constant_565, list_constant_564, list_constant_562, Qthe_value;
    Object Qvalue_not_of_type_symbol, list_constant_560, list_constant_361;
    Object list_constant_558, list_constant_557, list_constant_556;
    Object list_constant_555, list_constant_554, list_constant_508;
    Object list_constant_553, list_constant_552, list_constant_551;
    Object list_constant_550, list_constant_549, list_constant_548;
    Object list_constant_547, Qab_let_star, list_constant_546;
    Object list_constant_545, list_constant_544, list_constant_543;
    Object list_constant_542, list_constant_538, list_constant_541;
    Object list_constant_540, list_constant_539;
    Object Qcast_slot_constant_into_evaluation_value, Qslot_constantp;
    Object Qslot_value_qm, list_constant_537, list_constant_536;
    Object list_constant_458, list_constant_535, list_constant_457;
    Object list_constant_517, list_constant_448, list_constant_447;
    Object list_constant_446, list_constant_445, list_constant_444;
    Object list_constant_534, list_constant_515, Qframe, list_constant_533;
    Object list_constant_532, list_constant_531, list_constant_530;
    Object list_constant_529, list_constant_528, list_constant_527;
    Object list_constant_526, list_constant_525;
    Object Qunknown_structure_attribute_reference, list_constant_520;
    Object Qallow_no_item_p, list_constant_524, list_constant_36;
    Object list_constant_523, list_constant_522, Qevaluation_structure_slot;
    Object list_constant_519, list_constant_518, list_constant_516;
    Object Qframe_or_structure, list_constant_514, list_constant_512;
    Object list_constant_511, list_constant_510, list_constant_509;
    Object list_constant_506, list_constant_505, list_constant_504;
    Object list_constant_503, list_constant_502, list_constant_501;
    Object list_constant_500, list_constant_499, list_constant_498;
    Object list_constant_497, list_constant_496, Qab_let, list_constant_495;
    Object list_constant_494, list_constant_493, list_constant_492;
    Object list_constant_491, Qattribute_type_mismatch, list_constant_490;
    Object list_constant_489, list_constant_488, list_constant_487;
    Object list_constant_486, list_constant_470, Qfloat_value;
    Object Qslot_description_qm, Qtw_change_slot_description_value;
    Object Qreclaim_evaluation_integer, list_constant_485, list_constant_484;
    Object list_constant_483, Qmake_evaluation_float, list_constant_482;
    Object Qcoerce_fixnum_to_gensym_float, Qevaluation_integer_value;
    Object list_constant_481, list_constant_480, list_constant_479;
    Object Qslot_type_specification, Qevaluation_integer_p, list_constant_478;
    Object list_constant_477, list_constant_476, list_constant_475;
    Object list_constant_474, list_constant_473, list_constant_472;
    Object list_constant_471, Qreclaim_evaluation_truth_value;
    Object list_constant_469, list_constant_432, list_constant_468;
    Object list_constant_467, Qslot_value_list, Qevaluation_truth_value_value;
    Object Qevaluation_truth_value_p, list_constant_466, list_constant_465;
    Object list_constant_434, list_constant_464, list_constant_463;
    Object list_constant_462, Qattempt_to_conclude_to_inaccessibe_system_slot;
    Object list_constant_461, list_constant_460;
    Object Qtw_predefined_user_attributes, Qassq_macro, list_constant_459;
    Object Quser_defined_slot_description_p, list_constant_456;
    Object Qunknown_attribute_reference, Qvisible_slot_qm, list_constant_455;
    Object Qslot_value_class_description_qm, list_constant_454;
    Object Qillegal_conclude_for_tw, list_constant_453, list_constant_452;
    Object list_constant_451, Qsub_items_not_yet_supported, list_constant_449;
    Object list_constant_443, list_constant_442, list_constant_441;
    Object Qget_slot_description_value, list_constant_440, list_constant_439;
    Object list_constant_438, list_constant_437;
    Object Qdo_not_put_slot_in_attribute_tables_p, list_constant_436;
    Object list_constant_435, Qfeature_assq_macro, Qslot_features;
    Object list_constant_433, Qclass_description;
    Object Qget_slot_description_of_class_description, Qclass_qualifier_qm;
    Object list_constant_431, Qclass_description_slot, list_constant_430;
    Object list_constant_428, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qremainder_quantity, Qquotient_quantity, Qless_than_equal_quantity;
    Object Qgreater_than_equal_quantity, Qless_than_quantity;
    Object Qgreater_than_quantity, Qnegate_quantity, Qpush_quantity;
    Object list_constant_427, list_constant_426, list_constant_378;
    Object list_constant_105, string_constant_13, Qab_format, Qequal_quantity;
    Object Qmultiply_quantity, Qsubtract_quantity, list_constant_425;
    Object list_constant_424, list_constant_394, list_constant_393;
    Object list_constant_423, list_constant_398, Q_f, Qadd_quantity;
    Object Qdivide_fixnum, Qremainder_fixnum, list_constant_421;
    Object list_constant_415, list_constant_414, list_constant_420;
    Object list_constant_419, Qrem_fixnums, Qdivisor, Qdividend;
    Object Qquotient_fixnum, list_constant_416, list_constant_413;
    Object Qtruncatef_first, list_constant_412, list_constant_411;
    Object Qless_than_equal_fixnum, list_constant_409, list_constant_408;
    Object list_constant_407, Qlt_eq_f, Qgreater_than_equal_fixnum;
    Object list_constant_405, list_constant_404, list_constant_403, Qgt_eq_f;
    Object list_constant_401, list_constant_400, list_constant_399;
    Object Qsecond_arg, Qfirst_arg, list_constant_395, list_constant_392;
    Object list_constant_391, Qgt_f, list_constant_390, list_constant_389;
    Object Qnegate_fixnum, list_constant_387, list_constant_386, Qdecrement;
    Object list_constant_385, list_constant_384, list_constant_383, Qdecff;
    Object Qincrement, list_constant_382, list_constant_381, list_constant_380;
    Object Qincff, Qequal_fixnum, list_constant_376, list_constant_375;
    Object list_constant_373, Qmultiply_fixnum, list_constant_371;
    Object list_constant_370, Qstar_f, Qsubtract_fixnum, list_constant_368;
    Object list_constant_367, list_constant_365, list_constant_364;
    Object list_constant_362, list_constant_360, list_constant_33;
    Object list_constant_359, list_constant_27, Qsamep, list_constant_357;
    Object list_constant_356, list_constant_355, list_constant_354;
    Object list_constant_353, list_constant_352, list_constant_351;
    Object list_constant_350, list_constant_47, list_constant_349;
    Object list_constant_348, list_constant_347, list_constant_346, Qname;
    Object Qundefined_procedure_or_method, list_constant_345;
    Object list_constant_344, list_constant_343, list_constant_54;
    Object list_constant_342, Qroutine, list_constant_312, list_constant_39;
    Object Qexists, list_constant_341, list_constant_340;
    Object Qevaluation_false_value, Qcompute_effective_gesture_method;
    Object list_constant_336, list_constant_335, list_constant_334;
    Object list_constant_333, list_constant_332, list_constant_331;
    Object list_constant_330, Qnext_method, list_constant_329;
    Object list_constant_320, list_constant_328, Qab_no_next_method;
    Object list_constant_327, list_constant_325, Qab_method, list_constant_324;
    Object Qgesture_stack_ref, list_constant_323, list_constant_14;
    Object list_constant_262, Qgesture_function_argument_count;
    Object list_constant_322, list_constant_321, list_constant_319;
    Object list_constant_318, list_constant_97, list_constant_313;
    Object Qgesture_function_name, Qundefined_method, list_constant_317;
    Object list_constant_316, list_constant_315, list_constant_314;
    Object Qgesture_function_method_p, Qgesture_function, list_constant_311;
    Object list_constant_310, Qfunction_return, list_constant_309;
    Object list_constant_308, list_constant_307, list_constant_306;
    Object list_constant_273, list_constant_305, list_constant_304;
    Object list_constant_303, list_constant_302, list_constant_301;
    Object list_constant_300, list_constant_299, Qdesired_return_count;
    Object list_constant_298, list_constant_291, Qgensym_pop;
    Object list_constant_297, Qreturn_count, list_constant_296;
    Object list_constant_295, list_constant_294, Qreclaim_if_evaluation_value;
    Object list_constant_293, list_constant_292, Qgensym_push, Qtemp;
    Object list_constant_284, list_constant_285, list_constant_290;
    Object list_constant_289, list_constant_246, list_constant_288;
    Object list_constant_287, list_constant_286, Qnumber_received;
    Object Qnumber_desired, Qunsufficient_number_of_return_values;
    Object list_constant_283, list_constant_282, list_constant_281;
    Object list_constant_21, list_constant_280, list_constant_279;
    Object list_constant_278, list_constant_277, list_constant_276;
    Object list_constant_275, list_constant_274, list_constant_272;
    Object list_constant_271, list_constant_270, list_constant_269;
    Object list_constant_268, list_constant_267, list_constant_266;
    Object list_constant_265, list_constant_3, list_constant_264;
    Object list_constant_154, Qprevious_frame, list_constant_263;
    Object list_constant_170, Qgesture_function_instructions, list_constant_22;
    Object list_constant_261, list_constant_260, list_constant_243;
    Object list_constant_259, list_constant_258, Qgesture_thread_done;
    Object Qno_previous_frame, list_constant_257, Qfinally, list_constant_256;
    Object list_constant_255, Qtarget_start, Qtarget_index, list_constant_41;
    Object list_constant_251, Qsource_index, list_constant_250;
    Object list_constant_254, list_constant_253, list_constant_252;
    Object list_constant_249, list_constant_248, list_constant_247;
    Object Qgesture_function_p, list_constant_165, list_constant_58;
    Object list_constant_245, list_constant_244, Qframe_gesture_offset;
    Object list_constant_242, list_constant_241, list_constant_240;
    Object Qframe_previous_offset, list_constant_239, list_constant_238;
    Object list_constant_237, Qstart_in_g2, list_constant_236;
    Object list_constant_224, list_constant_235, list_constant_219;
    Object list_constant_234, list_constant_188, list_constant_221;
    Object list_constant_233, list_constant_232, list_constant_217;
    Object list_constant_231, list_constant_230, list_constant_229;
    Object list_constant_227, list_constant_112, Qtw_start_rpc;
    Object list_constant_228, list_constant_137, list_constant_226;
    Object Qcall_primitive_gesture, Qarglist, list_constant_202;
    Object Qtw_rpc_start_name, string_constant_12, string_constant_11;
    Object list_constant_225, list_constant_223, list_constant_222;
    Object list_constant_220, list_constant_218, list_constant_128;
    Object list_constant_127, list_constant_126, list_constant_125;
    Object list_constant_124, list_constant_216, list_constant_215;
    Object list_constant_214, list_constant_213, list_constant_204;
    Object Qtw_call_rpc, list_constant_212, list_constant_211;
    Object list_constant_210, list_constant_209, list_constant_98;
    Object list_constant_143, Qnot_an_rpc, list_constant_144;
    Object list_constant_208, list_constant_207, list_constant_206;
    Object list_constant_205, Qgensym_cons, list_constant_107;
    Object list_constant_203, Q1_plus_f, Qtw_rpc_call_name, string_constant_10;
    Object list_constant_201, list_constant_115, list_constant_200;
    Object list_constant_113, string_constant_9, list_constant_199;
    Object list_constant_88, Qprocedure_start, list_constant_198;
    Object list_constant_197, list_constant_81, list_constant_80;
    Object list_constant_196, list_constant_40, Qargument_list, Qregister_3;
    Object Qfunction_call, list_constant_194, list_constant_193;
    Object list_constant_192, list_constant_191, list_constant_190;
    Object list_constant_187, list_constant_186, list_constant_185;
    Object list_constant_184, list_constant_183, list_constant_182;
    Object list_constant_181, list_constant_180, list_constant_179;
    Object list_constant_178, list_constant_177, list_constant_176;
    Object list_constant_175, list_constant_174, list_constant_173;
    Object list_constant_172, Qnew_stack_ptr, list_constant_171;
    Object list_constant_92, Qgesture_instruction_vector, list_constant_169;
    Object list_constant_168, Qstart, list_constant_167, list_constant_166;
    Object list_constant_146, list_constant_147, list_constant_164;
    Object list_constant_163, list_constant_162, list_constant_161;
    Object list_constant_106, list_constant_160, list_constant_159;
    Object Qnormal_frame, list_constant_158, list_constant_157;
    Object Qframe_type_offset, list_constant_119, list_constant_156;
    Object list_constant_155, Qframe_pc_offset, list_constant_153;
    Object list_constant_152, list_constant_151, Qstack_overflow;
    Object list_constant_150, list_constant_149, Qgesture_stack_size;
    Object Qper_call_stack_slop, list_constant_148, Qframe_header_size;
    Object Qgesture_function_locals_count, list_constant_145;
    Object list_constant_142, Qprocedure_name, Qprocedure_is_remote;
    Object Qremote_procedure_definition_p, list_constant_141;
    Object list_constant_140, list_constant_139, list_constant_138;
    Object list_constant_136, list_constant_135, list_constant_134;
    Object list_constant_133, list_constant_132, list_constant_131;
    Object list_constant_130, Qreturn_list, list_constant_129, Qin;
    Object Qreturn_value, list_constant_123, Qgesture_thread_pause;
    Object list_constant_122, list_constant_108, Qgesture_thread_function;
    Object list_constant_121, list_constant_120, Qgesture_thread_pc;
    Object list_constant_118, Qgesture_thread_fp, list_constant_117;
    Object Qgesture_thread_sp, Qgesture_function_can_wait_p, list_constant_116;
    Object list_constant_114, list_constant_111, Qusing, Qcollect;
    Object Qgesture_function_primitive_function, Qcurrent_gesture_thread;
    Object list_constant_110, list_constant_109, Qframe_serial_number_setf;
    Object Qab_current_frame_serial_number;
    Object Qgesture_thread_frame_serial_number, Qgesture_thread;
    Object Qgesture_function_primitive_p, list_constant_104, list_constant_103;
    Object list_constant_102, list_constant_101, Qprocedure, list_constant_100;
    Object list_constant_52, list_constant_94, Qitem_class, Qmethod_name;
    Object list_constant_96, list_constant_93, list_constant_90;
    Object list_constant_89, Qregister_2, list_constant_86, list_constant_85;
    Object list_constant_84, list_constant_83, list_constant_82;
    Object list_constant_79, list_constant_78, Qargument_index;
    Object list_constant_77, Qarg_spec, list_constant_76, Qargument_value;
    Object list_constant_75, Qto, list_constant_74, Qarg_index;
    Object list_constant_73, list_constant_72, list_constant_71;
    Object list_constant_70, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_65, Qargument_type;
    Object list_constant_64, Qgesture_local_name, Qargument_name;
    Object Qargument_type_mismatch, list_constant_66, Qcheck_gesture_argument;
    Object string_constant_7, Qgesture_local_type;
    Object Qgesture_function_argument_specs, list_constant_63;
    Object list_constant_44, Qargument_count, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_59;
    Object Qexpected_number_of_args, Qargument_count_mismatch;
    Object list_constant_57, list_constant_56, list_constant_55;
    Object list_constant_53, Qno_effective_method, list_constant_51;
    Object list_constant_50, list_constant_49, list_constant_48;
    Object list_constant_46, list_constant_45, list_constant_43;
    Object list_constant_42, Qgesture_sp, Qregister_1;
    Object Qget_gesture_local_by_index, list_constant_37, list_constant_35;
    Object list_constant_34, list_constant_32, list_constant_30;
    Object list_constant_26, list_constant_29, Qdoes_not_exist;
    Object list_constant_28, list_constant_25, list_constant_24;
    Object list_constant_23, Qgesture_func, Qlocal_variable;
    Object Qunbound_local_variable, list_constant_17, list_constant_19;
    Object list_constant_18, list_constant_16, Qgesture_fp, list_constant_12;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_5, list_constant_6, list_constant_8, list_constant_7;
    Object Qgesture_constant, Qgesture_pc, Qgesture_pop, list_constant_1;
    Object Qunbound, Qgesture_local, Qreclaim_structure;
    Object Qoutstanding_gesture_local_count;
    Object Qgesture_local_structure_memory_usage, Qutilities2;
    Object string_constant_6, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_5, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qoutstanding_gesture_function_count;
    Object Qgesture_function_structure_memory_usage, string_constant_4;
    Object string_constant_3, Qevents, Qoutstanding_gesture_thread_count;
    Object Qgesture_thread_structure_memory_usage, string_constant_2;
    Object string_constant_1;

    x_note_fn_call(247,46);
    SET_PACKAGE("AB");
    SET_PACKAGE("AB");
    Frame_type_offset = FIX((SI_Long)0L);
    Frame_previous_offset = FIX((SI_Long)1L);
    Frame_gesture_offset = FIX((SI_Long)2L);
    Frame_pc_offset = FIX((SI_Long)3L);
    Frame_header_size = FIX((SI_Long)4L);
    Normal_frame = FIX((SI_Long)0L);
    Catch_frame = FIX((SI_Long)1L);
    Protected_frame = FIX((SI_Long)2L);
    No_previous_frame = FIX((SI_Long)0L);
    Per_call_stack_slop = FIX((SI_Long)300L);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gesture_thread_g2_struct = 
	    STATIC_SYMBOL("GESTURE-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qgesture_thread = STATIC_SYMBOL("GESTURE-THREAD",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gesture_thread_g2_struct,
	    Qgesture_thread,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgesture_thread,
	    Qg2_defstruct_structure_name_gesture_thread_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gesture_thread == UNBOUND)
	The_type_description_of_gesture_thread = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8m83i=y1n83i=y8n8k1l8n0000000kuk0k0");
    temp = The_type_description_of_gesture_thread;
    The_type_description_of_gesture_thread = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_1));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gesture_thread_g2_struct,
	    The_type_description_of_gesture_thread,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgesture_thread,
	    The_type_description_of_gesture_thread,Qtype_description_of_type);
    Qoutstanding_gesture_thread_count = 
	    STATIC_SYMBOL("OUTSTANDING-GESTURE-THREAD-COUNT",AB_package);
    Qgesture_thread_structure_memory_usage = 
	    STATIC_SYMBOL("GESTURE-THREAD-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_2 = STATIC_STRING("1q83i=y8s83-WOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gesture_thread_count);
    push_optimized_constant(Qgesture_thread_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_2));
    Qchain_of_available_gesture_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GESTURE-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gesture_threads,
	    Chain_of_available_gesture_threads);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_gesture_threads,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgesture_thread_count = STATIC_SYMBOL("GESTURE-THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgesture_thread_count,Gesture_thread_count);
    record_system_variable(Qgesture_thread_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gesture_threads_vector == UNBOUND)
	Chain_of_available_gesture_threads_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgesture_thread_structure_memory_usage,
	    STATIC_FUNCTION(gesture_thread_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gesture_thread_count,
	    STATIC_FUNCTION(outstanding_gesture_thread_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gesture_thread_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gesture_thread,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qgesture_thread,
	    reclaim_structure_for_gesture_thread_1);
    Qgesture_function = STATIC_SYMBOL("GESTURE-FUNCTION",AB_package);
    Gesture_function_prop = Qgesture_function;
    Qgesture_source_recording_p = 
	    STATIC_SYMBOL("GESTURE-SOURCE-RECORDING-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgesture_source_recording_p,
	    Gesture_source_recording_p);
    Qevents = STATIC_SYMBOL("EVENTS",AB_package);
    record_system_variable(Qgesture_source_recording_p,Qevents,T,Qnil,Qnil,
	    Qnil,Qnil);
    Qg2_defstruct_structure_name_gesture_function_g2_struct = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_gesture_function_g2_struct,
	    Qgesture_function,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgesture_function,
	    Qg2_defstruct_structure_name_gesture_function_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gesture_function == UNBOUND)
	The_type_description_of_gesture_function = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8m83i-y1n83i-y8n8k1l8n0000001l1m83My83-AMykzk0k0");
    temp = The_type_description_of_gesture_function;
    The_type_description_of_gesture_function = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_3));
    mutate_global_property(Qg2_defstruct_structure_name_gesture_function_g2_struct,
	    The_type_description_of_gesture_function,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgesture_function,
	    The_type_description_of_gesture_function,
	    Qtype_description_of_type);
    Qoutstanding_gesture_function_count = 
	    STATIC_SYMBOL("OUTSTANDING-GESTURE-FUNCTION-COUNT",AB_package);
    Qgesture_function_structure_memory_usage = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_4 = STATIC_STRING("1q83i-y8s83-WMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gesture_function_count);
    push_optimized_constant(Qgesture_function_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    Qchain_of_available_gesture_functions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GESTURE-FUNCTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gesture_functions,
	    Chain_of_available_gesture_functions);
    record_system_variable(Qchain_of_available_gesture_functions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgesture_function_count = STATIC_SYMBOL("GESTURE-FUNCTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgesture_function_count,Gesture_function_count);
    record_system_variable(Qgesture_function_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gesture_functions_vector == UNBOUND)
	Chain_of_available_gesture_functions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgesture_function_structure_memory_usage,
	    STATIC_FUNCTION(gesture_function_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gesture_function_count,
	    STATIC_FUNCTION(outstanding_gesture_function_count,NIL,FALSE,0,0));
    reclaim_structure_for_gesture_function_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gesture_function,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgesture_function,
	    reclaim_structure_for_gesture_function_1);
    Qg2_defstruct_structure_name_gesture_local_g2_struct = 
	    STATIC_SYMBOL("GESTURE-LOCAL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgesture_local = STATIC_SYMBOL("GESTURE-LOCAL",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gesture_local_g2_struct,
	    Qgesture_local,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgesture_local,
	    Qg2_defstruct_structure_name_gesture_local_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gesture_local == UNBOUND)
	The_type_description_of_gesture_local = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83i*y1n83i*y8n8k1l8n0000001l1n8y83-40y1n83--*y83---y83--=ykok0k0");
    temp = The_type_description_of_gesture_local;
    The_type_description_of_gesture_local = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    mutate_global_property(Qg2_defstruct_structure_name_gesture_local_g2_struct,
	    The_type_description_of_gesture_local,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgesture_local,
	    The_type_description_of_gesture_local,Qtype_description_of_type);
    Qoutstanding_gesture_local_count = 
	    STATIC_SYMBOL("OUTSTANDING-GESTURE-LOCAL-COUNT",AB_package);
    Qgesture_local_structure_memory_usage = 
	    STATIC_SYMBOL("GESTURE-LOCAL-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_6 = STATIC_STRING("1q83i*y8s83-WNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gesture_local_count);
    push_optimized_constant(Qgesture_local_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_gesture_locals = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GESTURE-LOCALS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gesture_locals,
	    Chain_of_available_gesture_locals);
    record_system_variable(Qchain_of_available_gesture_locals,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgesture_local_count = STATIC_SYMBOL("GESTURE-LOCAL-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgesture_local_count,Gesture_local_count);
    record_system_variable(Qgesture_local_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_gesture_locals_vector == UNBOUND)
	Chain_of_available_gesture_locals_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qgesture_local_structure_memory_usage,
	    STATIC_FUNCTION(gesture_local_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gesture_local_count,
	    STATIC_FUNCTION(outstanding_gesture_local_count,NIL,FALSE,0,0));
    reclaim_structure_for_gesture_local_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gesture_local,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgesture_local,
	    reclaim_structure_for_gesture_local_1);
    if (Tracing_in_events_modules_p == UNBOUND)
	Tracing_in_events_modules_p = Nil;
    if (Tw_evaluate_trace_level == UNBOUND)
	Tw_evaluate_trace_level = FIX((SI_Long)0L);
    if (Tw_source_debug_p == UNBOUND)
	Tw_source_debug_p = T;
    Qunbound = STATIC_SYMBOL("UNBOUND",AB_package);
    list_constant_1 = STATIC_CONS(Qunbound,Qnil);
    if (Gesture_unbound_value == UNBOUND)
	Gesture_unbound_value = list_constant_1;
    Qgesture_instruction = STATIC_SYMBOL("GESTURE-INSTRUCTION",AB_package);
    Gesture_instruction_prop = Qgesture_instruction;
    if (All_gesture_instruction_names == UNBOUND)
	All_gesture_instruction_names = Nil;
    if (Current_gesture_stack_pointer == UNBOUND)
	Current_gesture_stack_pointer = Nil;
    if (Current_gesture_frame_pointer == UNBOUND)
	Current_gesture_frame_pointer = Nil;
    Qbranch_if_false = STATIC_SYMBOL("BRANCH-IF-FALSE",AB_package);
    Qgesture_pop = STATIC_SYMBOL("GESTURE-POP",AB_package);
    list_constant_2 = STATIC_CONS(Qgesture_pop,Qnil);
    Qevaluation_false_value = STATIC_SYMBOL("EVALUATION-FALSE-VALUE",
	    AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qeq,list_constant_2,
	    Qevaluation_false_value);
    Qincff = STATIC_SYMBOL("INCFF",AB_package);
    Qgesture_pc = STATIC_SYMBOL("GESTURE-PC",AB_package);
    list_constant_3 = STATIC_CONS(Qgesture_pc,Qnil);
    Qgesture_constant = STATIC_SYMBOL("GESTURE-CONSTANT",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qgesture_constant,
	    FIX((SI_Long)0L));
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qincff,list_constant_3,
	    list_constant_4);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_5,
	    list_constant_6);
    list_constant_8 = STATIC_CONS(list_constant_7,Qnil);
    mutate_global_property(Qbranch_if_false,LIST_3(Qnil,FIX((SI_Long)0L),
	    list_constant_8),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qbranch_if_false,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qbranch_always = STATIC_SYMBOL("BRANCH-ALWAYS",AB_package);
    list_constant_9 = STATIC_CONS(list_constant_6,Qnil);
    mutate_global_property(Qbranch_always,LIST_3(Qnil,FIX((SI_Long)1L),
	    list_constant_9),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qbranch_always,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qbranch_if_true = STATIC_SYMBOL("BRANCH-IF-TRUE",AB_package);
    list_constant_10 = STATIC_CONS(list_constant_5,list_constant_9);
    list_constant_11 = STATIC_CONS(Qunless,list_constant_10);
    list_constant_12 = STATIC_CONS(list_constant_11,Qnil);
    mutate_global_property(Qbranch_if_true,LIST_3(Qnil,FIX((SI_Long)2L),
	    list_constant_12),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qbranch_if_true,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qset_local = STATIC_SYMBOL("SET-LOCAL",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qregister_1 = STATIC_SYMBOL("REGISTER-1",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qvalue,Qregister_1);
    list_constant_20 = STATIC_CONS(list_constant_13,Qnil);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qsetq,Qvalue,list_constant_2);
    Qgesture_stack_ref = STATIC_SYMBOL("GESTURE-STACK-REF",AB_package);
    Qplus_f = STATIC_SYMBOL("+F",AB_package);
    Qgesture_fp = STATIC_SYMBOL("GESTURE-FP",AB_package);
    list_constant_14 = STATIC_CONS(Qgesture_fp,Qnil);
    list_constant_15 = STATIC_CONS(list_constant_4,Qnil);
    list_constant_16 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_14,list_constant_15);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_16);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_17,Qvalue);
    list_constant_21 = STATIC_LIST((SI_Long)2L,list_constant_18,
	    list_constant_19);
    mutate_global_property(Qset_local,LIST_3(list_constant_20,
	    FIX((SI_Long)3L),list_constant_21),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qset_local,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qget_local = STATIC_SYMBOL("GET-LOCAL",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)3L,Qsetq,Qvalue,list_constant_17);
    Qgesture_unbound_value = STATIC_SYMBOL("GESTURE-UNBOUND-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgesture_unbound_value,Gesture_unbound_value);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qeq,Qvalue,
	    Qgesture_unbound_value);
    Qgesture_evaluation_error = STATIC_SYMBOL("GESTURE-EVALUATION-ERROR",
	    AB_package);
    Qunbound_local_variable = STATIC_SYMBOL("UNBOUND-LOCAL-VARIABLE",
	    AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qunbound_local_variable);
    Qlocal_variable = STATIC_SYMBOL("LOCAL-VARIABLE",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qquote,Qlocal_variable);
    Qget_gesture_local_by_index = 
	    STATIC_SYMBOL("GET-GESTURE-LOCAL-BY-INDEX",AB_package);
    Qgesture_func = STATIC_SYMBOL("GESTURE-FUNC",AB_package);
    list_constant_22 = STATIC_CONS(Qgesture_func,Qnil);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,
	    Qget_gesture_local_by_index,list_constant_22,list_constant_15);
    list_constant_26 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_24);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_25,list_constant_26);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_27,
	    list_constant_28);
    Qdoes_not_exist = STATIC_SYMBOL("DOES-NOT-EXIST",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qquote,Qdoes_not_exist);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_29,list_constant_26);
    list_constant_35 = STATIC_LIST((SI_Long)3L,Qunless,Qvalue,
	    list_constant_30);
    Qgesture_push = STATIC_SYMBOL("GESTURE-PUSH",AB_package);
    Qcopy_if_evaluation_value = STATIC_SYMBOL("COPY-IF-EVALUATION-VALUE",
	    AB_package);
    list_constant_31 = STATIC_CONS(Qvalue,Qnil);
    list_constant_32 = STATIC_CONS(Qcopy_if_evaluation_value,list_constant_31);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qgesture_push,list_constant_32);
    list_constant_37 = STATIC_LIST((SI_Long)4L,list_constant_33,
	    list_constant_34,list_constant_35,list_constant_36);
    mutate_global_property(Qget_local,LIST_3(list_constant_20,
	    FIX((SI_Long)4L),list_constant_37),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qget_local,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    SET_SYMBOL_FUNCTION(Qget_gesture_local_by_index,
	    STATIC_FUNCTION(get_gesture_local_by_index,NIL,FALSE,2,2));
    Qcheck_args = STATIC_SYMBOL("CHECK-ARGS",AB_package);
    Qroutine = STATIC_SYMBOL("ROUTINE",AB_package);
    list_constant_38 = STATIC_CONS(Qregister_1,Qnil);
    list_constant_39 = STATIC_CONS(Qroutine,list_constant_38);
    Qargument_count = STATIC_SYMBOL("ARGUMENT-COUNT",AB_package);
    Qregister_2 = STATIC_SYMBOL("REGISTER-2",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qargument_count,Qregister_2);
    list_constant_85 = STATIC_LIST((SI_Long)2L,list_constant_39,
	    list_constant_40);
    Q_f = STATIC_SYMBOL("-F",AB_package);
    Qgesture_sp = STATIC_SYMBOL("GESTURE-SP",AB_package);
    list_constant_41 = STATIC_CONS(Qgesture_sp,Qnil);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_41,
	    FIX((SI_Long)1L));
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_42);
    list_constant_80 = STATIC_LIST((SI_Long)3L,Qsetf,Qroutine,
	    list_constant_43);
    list_constant_44 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)3L,Q_f,list_constant_41,
	    list_constant_44);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_45);
    list_constant_81 = STATIC_LIST((SI_Long)3L,Qsetf,Qargument_count,
	    list_constant_46);
    Qgesture_function_method_p = STATIC_SYMBOL("GESTURE-FUNCTION-METHOD-P",
	    AB_package);
    list_constant_47 = STATIC_CONS(Qroutine,Qnil);
    list_constant_54 = STATIC_CONS(Qgesture_function_method_p,
	    list_constant_47);
    Qcompute_effective_gesture_method = 
	    STATIC_SYMBOL("COMPUTE-EFFECTIVE-GESTURE-METHOD",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qplus_f,FIX((SI_Long)2L),
	    Qargument_count);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_41,
	    list_constant_48);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_49);
    list_constant_51 = STATIC_LIST((SI_Long)4L,
	    Qcompute_effective_gesture_method,Qroutine,list_constant_50,Qnil);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qsetf,Qroutine,
	    list_constant_51);
    Qno_effective_method = STATIC_SYMBOL("NO-EFFECTIVE-METHOD",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qquote,Qno_effective_method);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_52);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qunless,Qroutine,
	    list_constant_53);
    list_constant_82 = STATIC_LIST((SI_Long)4L,Qwhen,list_constant_54,
	    list_constant_55,list_constant_56);
    Qeq_f = STATIC_SYMBOL("=F",AB_package);
    Qgesture_function_argument_count = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-ARGUMENT-COUNT",AB_package);
    list_constant_57 = STATIC_CONS(Qgesture_function_argument_count,
	    list_constant_47);
    list_constant_58 = STATIC_CONS(list_constant_57,Qnil);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,Qeq_f,Qargument_count,
	    list_constant_58);
    Qargument_count_mismatch = STATIC_SYMBOL("ARGUMENT-COUNT-MISMATCH",
	    AB_package);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qargument_count_mismatch);
    Qexpected_number_of_args = STATIC_SYMBOL("EXPECTED-NUMBER-OF-ARGS",
	    AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qexpected_number_of_args);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)4L,
	    Qgesture_evaluation_error,list_constant_59,list_constant_60,
	    list_constant_58);
    list_constant_83 = STATIC_LIST((SI_Long)3L,Qunless,list_constant_61,
	    list_constant_62);
    Qab_loop = STATIC_SYMBOL("LOOP",AB_package);
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qarg_index = STATIC_SYMBOL("ARG-INDEX",AB_package);
    Qfrom = STATIC_SYMBOL("FROM",AB_package);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    Qargument_count,list_constant_44);
    list_constant_74 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_41,
	    list_constant_63);
    Qto = STATIC_SYMBOL("TO",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_41,
	    FIX((SI_Long)3L));
    Qas = STATIC_SYMBOL("AS",AB_package);
    Qargument_value = STATIC_SYMBOL("ARGUMENT-VALUE",AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,Qarg_index);
    Qarg_spec = STATIC_SYMBOL("ARG-SPEC",AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qgesture_function_argument_specs = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-ARGUMENT-SPECS",AB_package);
    list_constant_77 = STATIC_CONS(Qgesture_function_argument_specs,
	    list_constant_47);
    Qargument_index = STATIC_SYMBOL("ARGUMENT-INDEX",AB_package);
    Qtw_trace = STATIC_SYMBOL("TW-TRACE",AB_package);
    string_constant_7 = STATIC_STRING("arg-type =~s value=~s~%");
    Qgesture_local_type = STATIC_SYMBOL("GESTURE-LOCAL-TYPE",AB_package);
    list_constant_64 = STATIC_CONS(Qarg_spec,Qnil);
    list_constant_65 = STATIC_CONS(Qgesture_local_type,list_constant_64);
    list_constant_66 = STATIC_CONS(Qargument_value,Qnil);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)5L,Qtw_trace,
	    FIX((SI_Long)2L),string_constant_7,list_constant_65,
	    list_constant_66);
    Qcheck_gesture_argument = STATIC_SYMBOL("CHECK-GESTURE-ARGUMENT",
	    AB_package);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)3L,
	    Qcheck_gesture_argument,Qarg_spec,list_constant_66);
    Qargument_type_mismatch = STATIC_SYMBOL("ARGUMENT-TYPE-MISMATCH",
	    AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qquote,Qargument_type_mismatch);
    Qargument_name = STATIC_SYMBOL("ARGUMENT-NAME",AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qquote,Qargument_name);
    Qgesture_local_name = STATIC_SYMBOL("GESTURE-LOCAL-NAME",AB_package);
    list_constant_69 = STATIC_CONS(Qgesture_local_name,list_constant_64);
    Qargument_type = STATIC_SYMBOL("ARGUMENT-TYPE",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qquote,Qargument_type);
    Qtformat_text_string = STATIC_SYMBOL("TFORMAT-TEXT-STRING",AB_package);
    string_constant_8 = STATIC_STRING("~NT");
    list_constant_71 = STATIC_LIST((SI_Long)3L,Qtformat_text_string,
	    string_constant_8,list_constant_65);
    list_constant_73 = STATIC_LIST((SI_Long)6L,Qgesture_evaluation_error,
	    list_constant_67,list_constant_68,list_constant_69,
	    list_constant_70,list_constant_71);
    list_constant_79 = STATIC_LIST((SI_Long)3L,Qunless,list_constant_72,
	    list_constant_73);
    list_constant_84 = STATIC_LIST((SI_Long)22L,Qab_loop,Qfor,Qarg_index,
	    Qfrom,list_constant_74,Qto,list_constant_75,Qas,
	    Qargument_value,Qnum_eq,list_constant_76,Qas,Qarg_spec,Qin,
	    list_constant_77,Qas,Qargument_index,Qfrom,FIX((SI_Long)0L),
	    Qdo,list_constant_78,list_constant_79);
    list_constant_86 = STATIC_LIST((SI_Long)5L,list_constant_80,
	    list_constant_81,list_constant_82,list_constant_83,
	    list_constant_84);
    mutate_global_property(Qcheck_args,LIST_3(list_constant_85,
	    FIX((SI_Long)5L),list_constant_86),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qcheck_args,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_88 = STATIC_CONS(Qprocedure,list_constant_38);
    Qnew_stack_ptr = STATIC_SYMBOL("NEW-STACK-PTR",AB_package);
    list_constant_87 = STATIC_CONS(Qregister_2,Qnil);
    list_constant_89 = STATIC_CONS(Qnew_stack_ptr,list_constant_87);
    Qarg_count = STATIC_SYMBOL("ARG-COUNT",AB_package);
    Qregister_3 = STATIC_SYMBOL("REGISTER-3",AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qarg_count,Qregister_3);
    list_constant_192 = STATIC_LIST((SI_Long)3L,list_constant_88,
	    list_constant_89,list_constant_90);
    list_constant_91 = STATIC_CONS(list_constant_2,Qnil);
    list_constant_188 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qprocedure,
	    list_constant_91);
    list_constant_189 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qarg_count,
	    list_constant_91);
    list_constant_92 = STATIC_CONS(Qprocedure,Qnil);
    list_constant_102 = STATIC_CONS(Qgesture_function_method_p,
	    list_constant_92);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_41,
	    Qarg_count);
    list_constant_94 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_93);
    list_constant_95 = STATIC_CONS(Qnil,Qnil);
    list_constant_96 = STATIC_LIST_STAR((SI_Long)4L,
	    Qcompute_effective_gesture_method,Qprocedure,list_constant_94,
	    list_constant_95);
    list_constant_103 = STATIC_LIST((SI_Long)3L,Qsetf,Qprocedure,
	    list_constant_96);
    Qmethod_name = STATIC_SYMBOL("METHOD-NAME",AB_package);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qquote,Qmethod_name);
    Qgesture_function_name = STATIC_SYMBOL("GESTURE-FUNCTION-NAME",AB_package);
    list_constant_98 = STATIC_CONS(Qgesture_function_name,list_constant_92);
    Qitem_class = STATIC_SYMBOL("ITEM-CLASS",AB_package);
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qquote,Qitem_class);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qab_class,list_constant_94);
    list_constant_101 = STATIC_LIST((SI_Long)6L,Qgesture_evaluation_error,
	    list_constant_52,list_constant_97,list_constant_98,
	    list_constant_99,list_constant_100);
    list_constant_104 = STATIC_LIST((SI_Long)3L,Qunless,Qprocedure,
	    list_constant_101);
    list_constant_190 = STATIC_LIST((SI_Long)4L,Qwhen,list_constant_102,
	    list_constant_103,list_constant_104);
    Qgesture_function_primitive_p = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-PRIMITIVE-P",AB_package);
    list_constant_137 = STATIC_CONS(Qgesture_function_primitive_p,
	    list_constant_92);
    Qcurrent_gesture_stack_pointer = 
	    STATIC_SYMBOL("CURRENT-GESTURE-STACK-POINTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_gesture_stack_pointer,
	    Current_gesture_stack_pointer);
    list_constant_105 = STATIC_CONS(list_constant_41,Qnil);
    list_constant_138 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qcurrent_gesture_stack_pointer,list_constant_105);
    Qcurrent_gesture_frame_pointer = 
	    STATIC_SYMBOL("CURRENT-GESTURE-FRAME-POINTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_gesture_frame_pointer,
	    Current_gesture_frame_pointer);
    list_constant_106 = STATIC_CONS(list_constant_14,Qnil);
    list_constant_139 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qcurrent_gesture_frame_pointer,list_constant_106);
    Qframe_serial_number_setf = STATIC_SYMBOL("FRAME-SERIAL-NUMBER-SETF",
	    AB_package);
    Qgesture_thread_frame_serial_number = 
	    STATIC_SYMBOL("GESTURE-THREAD-FRAME-SERIAL-NUMBER",AB_package);
    list_constant_107 = STATIC_CONS(Qgesture_thread,Qnil);
    list_constant_108 = STATIC_CONS(list_constant_107,Qnil);
    list_constant_109 = STATIC_CONS(Qgesture_thread_frame_serial_number,
	    list_constant_108);
    Qab_current_frame_serial_number = 
	    STATIC_SYMBOL("CURRENT-FRAME-SERIAL-NUMBER",AB_package);
    list_constant_110 = STATIC_CONS(Qab_current_frame_serial_number,Qnil);
    list_constant_140 = STATIC_LIST((SI_Long)3L,Qframe_serial_number_setf,
	    list_constant_109,list_constant_110);
    Qab_let_star = STATIC_SYMBOL("LET*",AB_package);
    Qcurrent_gesture_thread = STATIC_SYMBOL("CURRENT-GESTURE-THREAD",
	    AB_package);
    list_constant_115 = STATIC_CONS(Qcurrent_gesture_thread,list_constant_108);
    Qreturn_list = STATIC_SYMBOL("RETURN-LIST",AB_package);
    Qcall_primitive_gesture = STATIC_SYMBOL("CALL-PRIMITIVE-GESTURE",
	    AB_package);
    Qgesture_function_primitive_function = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-PRIMITIVE-FUNCTION",AB_package);
    list_constant_112 = STATIC_CONS(Qgesture_function_primitive_function,
	    list_constant_92);
    Qi = STATIC_SYMBOL("I",AB_package);
    Qbelow = STATIC_SYMBOL("BELOW",AB_package);
    Qcollect = STATIC_SYMBOL("COLLECT",AB_package);
    Qusing = STATIC_SYMBOL("USING",AB_package);
    Qgensym_cons = STATIC_SYMBOL("GENSYM-CONS",AB_package);
    list_constant_111 = STATIC_LIST((SI_Long)11L,Qab_loop,Qfor,Qi,Qfrom,
	    FIX((SI_Long)0L),Qbelow,Qarg_count,Qcollect,list_constant_2,
	    Qusing,Qgensym_cons);
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qnreverse,list_constant_111);
    list_constant_114 = STATIC_LIST((SI_Long)4L,Qcall_primitive_gesture,
	    list_constant_112,Qarg_count,list_constant_113);
    list_constant_116 = STATIC_LIST((SI_Long)2L,Qreturn_list,
	    list_constant_114);
    list_constant_135 = STATIC_LIST((SI_Long)2L,list_constant_115,
	    list_constant_116);
    Qgesture_function_can_wait_p = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-CAN-WAIT-P",AB_package);
    list_constant_123 = STATIC_CONS(Qgesture_function_can_wait_p,
	    list_constant_92);
    Qgesture_thread_sp = STATIC_SYMBOL("GESTURE-THREAD-SP",AB_package);
    list_constant_117 = STATIC_CONS(Qgesture_thread_sp,list_constant_108);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_117,list_constant_105);
    Qgesture_thread_fp = STATIC_SYMBOL("GESTURE-THREAD-FP",AB_package);
    list_constant_118 = STATIC_CONS(Qgesture_thread_fp,list_constant_108);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_118,list_constant_106);
    Qgesture_thread_pc = STATIC_SYMBOL("GESTURE-THREAD-PC",AB_package);
    list_constant_120 = STATIC_CONS(Qgesture_thread_pc,list_constant_108);
    Q1_plus_f = STATIC_SYMBOL("1+F",AB_package);
    list_constant_119 = STATIC_CONS(list_constant_3,Qnil);
    list_constant_121 = STATIC_CONS(Q1_plus_f,list_constant_119);
    list_constant_126 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_120,
	    list_constant_121);
    Qgesture_thread_function = STATIC_SYMBOL("GESTURE-THREAD-FUNCTION",
	    AB_package);
    list_constant_122 = STATIC_CONS(Qgesture_thread_function,
	    list_constant_108);
    list_constant_127 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_122,
	    list_constant_22);
    Qgesture_thread_pause = STATIC_SYMBOL("GESTURE-THREAD-PAUSE",AB_package);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qgo,Qgesture_thread_pause);
    list_constant_133 = STATIC_LIST((SI_Long)6L,list_constant_123,
	    list_constant_124,list_constant_125,list_constant_126,
	    list_constant_127,list_constant_128);
    Qreturn_value = STATIC_SYMBOL("RETURN-VALUE",AB_package);
    list_constant_129 = STATIC_LIST((SI_Long)2L,Qgesture_push,Qreturn_value);
    list_constant_131 = STATIC_LIST((SI_Long)7L,Qab_loop,Qfor,
	    Qreturn_value,Qin,Qreturn_list,Qdo,list_constant_129);
    list_constant_130 = STATIC_LIST((SI_Long)2L,Qlength,Qreturn_list);
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_130);
    list_constant_134 = STATIC_LIST((SI_Long)3L,Qt,list_constant_131,
	    list_constant_132);
    list_constant_136 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_133,
	    list_constant_134);
    list_constant_141 = STATIC_LIST((SI_Long)3L,Qab_let_star,
	    list_constant_135,list_constant_136);
    list_constant_185 = STATIC_LIST((SI_Long)5L,list_constant_137,
	    list_constant_138,list_constant_139,list_constant_140,
	    list_constant_141);
    Qremote_procedure_definition_p = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DEFINITION-P",AB_package);
    list_constant_144 = STATIC_LIST((SI_Long)2L,
	    Qremote_procedure_definition_p,list_constant_112);
    Qprocedure_is_remote = STATIC_SYMBOL("PROCEDURE-IS-REMOTE",AB_package);
    list_constant_142 = STATIC_LIST((SI_Long)2L,Qquote,Qprocedure_is_remote);
    Qprocedure_name = STATIC_SYMBOL("PROCEDURE-NAME",AB_package);
    list_constant_143 = STATIC_LIST((SI_Long)2L,Qquote,Qprocedure_name);
    list_constant_145 = STATIC_LIST((SI_Long)4L,Qgesture_evaluation_error,
	    list_constant_142,list_constant_143,list_constant_98);
    list_constant_186 = STATIC_LIST((SI_Long)2L,list_constant_144,
	    list_constant_145);
    Qgesture_function_locals_count = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-LOCALS-COUNT",AB_package);
    list_constant_146 = STATIC_CONS(Qgesture_function_locals_count,
	    list_constant_92);
    Qframe_header_size = STATIC_SYMBOL("FRAME-HEADER-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_header_size,Frame_header_size);
    list_constant_147 = STATIC_CONS(Qframe_header_size,Qnil);
    list_constant_148 = STATIC_LIST_STAR((SI_Long)4L,Qplus_f,
	    list_constant_41,list_constant_146,list_constant_147);
    list_constant_172 = STATIC_LIST((SI_Long)3L,Qsetf,Qnew_stack_ptr,
	    list_constant_148);
    Qgt_f = STATIC_SYMBOL(">F",AB_package);
    Qper_call_stack_slop = STATIC_SYMBOL("PER-CALL-STACK-SLOP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qper_call_stack_slop,Per_call_stack_slop);
    list_constant_149 = STATIC_LIST((SI_Long)3L,Qplus_f,Qnew_stack_ptr,
	    Qper_call_stack_slop);
    Qgesture_stack_size = STATIC_SYMBOL("GESTURE-STACK-SIZE",AB_package);
    list_constant_150 = STATIC_CONS(Qgesture_stack_size,Qnil);
    list_constant_152 = STATIC_LIST((SI_Long)3L,Qgt_f,list_constant_149,
	    list_constant_150);
    Qstack_overflow = STATIC_SYMBOL("STACK-OVERFLOW",AB_package);
    list_constant_151 = STATIC_LIST((SI_Long)2L,Qquote,Qstack_overflow);
    list_constant_153 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_151);
    list_constant_173 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_152,
	    list_constant_153);
    Qframe_pc_offset = STATIC_SYMBOL("FRAME-PC-OFFSET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_pc_offset,Frame_pc_offset);
    list_constant_154 = STATIC_CONS(Qframe_pc_offset,Qnil);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_14,list_constant_154);
    list_constant_156 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_155);
    list_constant_174 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_156,list_constant_119);
    Qframe_type_offset = STATIC_SYMBOL("FRAME-TYPE-OFFSET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_type_offset,Frame_type_offset);
    list_constant_157 = STATIC_LIST((SI_Long)3L,Qplus_f,list_constant_41,
	    Qframe_type_offset);
    list_constant_158 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_157);
    Qnormal_frame = STATIC_SYMBOL("NORMAL-FRAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnormal_frame,Normal_frame);
    list_constant_175 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_158,
	    Qnormal_frame);
    Qframe_previous_offset = STATIC_SYMBOL("FRAME-PREVIOUS-OFFSET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_previous_offset,Frame_previous_offset);
    list_constant_159 = STATIC_LIST((SI_Long)3L,Qplus_f,list_constant_41,
	    Qframe_previous_offset);
    list_constant_160 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_159);
    list_constant_176 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_160,list_constant_106);
    Qframe_gesture_offset = STATIC_SYMBOL("FRAME-GESTURE-OFFSET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_gesture_offset,Frame_gesture_offset);
    list_constant_161 = STATIC_LIST((SI_Long)3L,Qplus_f,list_constant_41,
	    Qframe_gesture_offset);
    list_constant_162 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_161);
    list_constant_177 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_162,list_constant_92);
    list_constant_163 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_41,list_constant_154);
    list_constant_164 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_163);
    list_constant_178 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_164,
	    FIX((SI_Long)1234567L));
    Qwith = STATIC_SYMBOL("WITH",AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    list_constant_167 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_41,list_constant_147);
    list_constant_168 = STATIC_LIST((SI_Long)3L,Qplus_f,Qstart,
	    list_constant_146);
    list_constant_165 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,Qi);
    list_constant_166 = STATIC_CONS(Qgesture_unbound_value,Qnil);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_165,list_constant_166);
    list_constant_179 = STATIC_LIST((SI_Long)13L,Qab_loop,Qwith,Qstart,
	    Qnum_eq,list_constant_167,Qfor,Qi,Qfrom,Qstart,Qbelow,
	    list_constant_168,Qdo,list_constant_169);
    list_constant_180 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_14,list_constant_105);
    list_constant_181 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_22,list_constant_92);
    Qgesture_instruction_vector = 
	    STATIC_SYMBOL("GESTURE-INSTRUCTION-VECTOR",AB_package);
    list_constant_170 = STATIC_CONS(Qgesture_instruction_vector,Qnil);
    Qgesture_function_instructions = 
	    STATIC_SYMBOL("GESTURE-FUNCTION-INSTRUCTIONS",AB_package);
    list_constant_171 = STATIC_CONS(Qgesture_function_instructions,
	    list_constant_92);
    list_constant_182 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_170,
	    list_constant_171);
    list_constant_183 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_41,
	    Qnew_stack_ptr);
    list_constant_184 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_3,
	    FIX((SI_Long)-1L));
    list_constant_187 = STATIC_LIST((SI_Long)14L,Qt,list_constant_172,
	    list_constant_173,list_constant_174,list_constant_175,
	    list_constant_176,list_constant_177,list_constant_178,
	    list_constant_179,list_constant_180,list_constant_181,
	    list_constant_182,list_constant_183,list_constant_184);
    list_constant_191 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_185,
	    list_constant_186,list_constant_187);
    list_constant_193 = STATIC_LIST((SI_Long)4L,list_constant_188,
	    list_constant_189,list_constant_190,list_constant_191);
    mutate_global_property(Qprocedure_call,LIST_3(list_constant_192,
	    FIX((SI_Long)6L),list_constant_193),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qprocedure_call,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsecret_return_value = STATIC_SYMBOL("SECRET-RETURN-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsecret_return_value,Secret_return_value);
    list_constant_194 = STATIC_CONS(Qsecret_return_value,Qnil);
    if (Secret_return_value == UNBOUND)
	Secret_return_value = list_constant_194;
    SET_SYMBOL_FUNCTION(Qcall_primitive_gesture,
	    STATIC_FUNCTION(call_primitive_gesture,NIL,FALSE,3,3));
    Qfunction_call = STATIC_SYMBOL("FUNCTION-CALL",AB_package);
    mutate_global_property(Qfunction_call,LIST_3(Qnil,FIX((SI_Long)7L),
	    Qnil),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qfunction_call,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qprocedure_start = STATIC_SYMBOL("PROCEDURE-START",AB_package);
    Qargument_list = STATIC_SYMBOL("ARGUMENT-LIST",AB_package);
    list_constant_195 = STATIC_CONS(Qregister_3,Qnil);
    list_constant_196 = STATIC_CONS(Qargument_list,list_constant_195);
    list_constant_197 = STATIC_LIST((SI_Long)3L,list_constant_39,
	    list_constant_40,list_constant_196);
    list_constant_198 = STATIC_LIST((SI_Long)2L,list_constant_80,
	    list_constant_81);
    mutate_global_property(Qprocedure_start,LIST_3(list_constant_197,
	    FIX((SI_Long)8L),list_constant_198),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qprocedure_start,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qcall_in_g2 = STATIC_SYMBOL("CALL-IN-G2",AB_package);
    list_constant_199 = STATIC_CONS(Qarg_count,list_constant_87);
    list_constant_224 = STATIC_LIST((SI_Long)2L,list_constant_88,
	    list_constant_199);
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    string_constant_9 = 
	    STATIC_STRING("in call in g2 before much of anything~%");
    list_constant_222 = STATIC_LIST((SI_Long)3L,Qab_format,Qt,
	    string_constant_9);
    list_constant_219 = STATIC_LIST((SI_Long)2L,Qforce_output,Qt);
    Qarglist = STATIC_SYMBOL("ARGLIST",AB_package);
    list_constant_200 = STATIC_CONS(list_constant_113,Qnil);
    list_constant_201 = STATIC_CONS(Qarglist,list_constant_200);
    list_constant_217 = STATIC_LIST((SI_Long)2L,list_constant_115,
	    list_constant_201);
    string_constant_10 = STATIC_STRING("in call in g2 before prim call~%");
    list_constant_218 = STATIC_LIST((SI_Long)3L,Qab_format,Qt,
	    string_constant_10);
    Qtw_rpc_call_name = STATIC_SYMBOL("TW-RPC-CALL-NAME",AB_package);
    list_constant_202 = STATIC_CONS(list_constant_112,Qnil);
    list_constant_205 = STATIC_CONS(Qtw_rpc_call_name,list_constant_202);
    list_constant_203 = STATIC_CONS(Qarg_count,Qnil);
    list_constant_206 = STATIC_CONS(Q1_plus_f,list_constant_203);
    list_constant_204 = STATIC_LIST((SI_Long)2L,list_constant_107,Qarglist);
    list_constant_207 = STATIC_CONS(Qgensym_cons,list_constant_204);
    list_constant_208 = STATIC_LIST((SI_Long)4L,Qcall_primitive_gesture,
	    list_constant_205,list_constant_206,list_constant_207);
    list_constant_214 = STATIC_LIST((SI_Long)2L,list_constant_137,
	    list_constant_208);
    list_constant_211 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_144);
    Qnot_an_rpc = STATIC_SYMBOL("NOT-AN-RPC",AB_package);
    list_constant_209 = STATIC_LIST((SI_Long)2L,Qquote,Qnot_an_rpc);
    list_constant_210 = STATIC_LIST((SI_Long)2L,list_constant_143,
	    list_constant_98);
    list_constant_212 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_209,list_constant_210);
    list_constant_215 = STATIC_LIST((SI_Long)2L,list_constant_211,
	    list_constant_212);
    Qtw_call_rpc = STATIC_SYMBOL("TW-CALL-RPC",AB_package);
    list_constant_213 = STATIC_LIST_STAR((SI_Long)3L,Qtw_call_rpc,
	    list_constant_112,list_constant_204);
    list_constant_216 = STATIC_LIST((SI_Long)2L,Qt,list_constant_213);
    list_constant_220 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_214,
	    list_constant_215,list_constant_216);
    list_constant_221 = STATIC_LIST((SI_Long)5L,list_constant_124,
	    list_constant_125,list_constant_126,list_constant_127,
	    list_constant_128);
    list_constant_223 = STATIC_LIST_STAR((SI_Long)6L,Qab_let_star,
	    list_constant_217,list_constant_218,list_constant_219,
	    list_constant_220,list_constant_221);
    list_constant_225 = STATIC_LIST((SI_Long)5L,list_constant_188,
	    list_constant_189,list_constant_222,list_constant_219,
	    list_constant_223);
    mutate_global_property(Qcall_in_g2,LIST_3(list_constant_224,
	    FIX((SI_Long)9L),list_constant_225),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qcall_in_g2,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qstart_in_g2 = STATIC_SYMBOL("START-IN-G2",AB_package);
    string_constant_11 = 
	    STATIC_STRING("in start in g2 before much of anything~%");
    list_constant_234 = STATIC_LIST((SI_Long)3L,Qab_format,Qt,
	    string_constant_11);
    string_constant_12 = STATIC_STRING("in start in g2 before prim call~%");
    list_constant_232 = STATIC_LIST((SI_Long)3L,Qab_format,Qt,
	    string_constant_12);
    Qtw_rpc_start_name = STATIC_SYMBOL("TW-RPC-START-NAME",AB_package);
    list_constant_226 = STATIC_CONS(Qtw_rpc_start_name,list_constant_202);
    list_constant_227 = STATIC_CONS(Qarglist,Qnil);
    list_constant_228 = STATIC_LIST_STAR((SI_Long)4L,
	    Qcall_primitive_gesture,list_constant_226,Qarg_count,
	    list_constant_227);
    list_constant_230 = STATIC_LIST((SI_Long)2L,list_constant_137,
	    list_constant_228);
    Qtw_start_rpc = STATIC_SYMBOL("TW-START-RPC",AB_package);
    list_constant_229 = STATIC_LIST_STAR((SI_Long)3L,Qtw_start_rpc,
	    list_constant_112,list_constant_227);
    list_constant_231 = STATIC_LIST((SI_Long)2L,Qt,list_constant_229);
    list_constant_233 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_230,
	    list_constant_231);
    list_constant_235 = STATIC_LIST_STAR((SI_Long)6L,Qab_let_star,
	    list_constant_217,list_constant_232,list_constant_219,
	    list_constant_233,list_constant_221);
    list_constant_236 = STATIC_LIST((SI_Long)5L,list_constant_188,
	    list_constant_189,list_constant_234,list_constant_219,
	    list_constant_235);
    mutate_global_property(Qstart_in_g2,LIST_3(list_constant_224,
	    FIX((SI_Long)10L),list_constant_236),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qstart_in_g2,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qprocedure_return = STATIC_SYMBOL("PROCEDURE-RETURN",AB_package);
    Qprevious_frame = STATIC_SYMBOL("PREVIOUS-FRAME",AB_package);
    list_constant_237 = STATIC_CONS(Qprevious_frame,list_constant_38);
    Qreturn_count = STATIC_SYMBOL("RETURN-COUNT",AB_package);
    list_constant_238 = STATIC_CONS(Qreturn_count,list_constant_87);
    list_constant_239 = STATIC_CONS(Qroutine,list_constant_195);
    list_constant_279 = STATIC_LIST((SI_Long)3L,list_constant_237,
	    list_constant_238,list_constant_239);
    list_constant_240 = STATIC_CONS(Qframe_previous_offset,Qnil);
    list_constant_241 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_14,list_constant_240);
    list_constant_242 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_241);
    list_constant_272 = STATIC_LIST((SI_Long)3L,Qsetf,Qprevious_frame,
	    list_constant_242);
    list_constant_273 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qreturn_count,
	    list_constant_91);
    list_constant_243 = STATIC_CONS(Qframe_gesture_offset,Qnil);
    list_constant_244 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    list_constant_14,list_constant_243);
    list_constant_245 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_244);
    list_constant_274 = STATIC_LIST((SI_Long)3L,Qsetf,Qroutine,
	    list_constant_245);
    list_constant_250 = STATIC_LIST_STAR((SI_Long)3L,Q_f,list_constant_14,
	    list_constant_58);
    list_constant_246 = STATIC_CONS(Qreturn_count,Qnil);
    list_constant_251 = STATIC_LIST_STAR((SI_Long)3L,Q_f,list_constant_41,
	    list_constant_246);
    Qgesture_function_p = STATIC_SYMBOL("GESTURE-FUNCTION-P",AB_package);
    list_constant_247 = STATIC_CONS(list_constant_165,Qnil);
    list_constant_248 = STATIC_CONS(Qgesture_function_p,list_constant_247);
    Qreclaim_if_evaluation_value = 
	    STATIC_SYMBOL("RECLAIM-IF-EVALUATION-VALUE",AB_package);
    list_constant_249 = STATIC_CONS(Qreclaim_if_evaluation_value,
	    list_constant_247);
    list_constant_252 = STATIC_LIST((SI_Long)3L,Qunless,list_constant_248,
	    list_constant_249);
    list_constant_275 = STATIC_LIST((SI_Long)9L,Qab_loop,Qfor,Qi,Qfrom,
	    list_constant_250,Qbelow,list_constant_251,Qdo,list_constant_252);
    Qtarget_start = STATIC_SYMBOL("TARGET-START",AB_package);
    Qsource_index = STATIC_SYMBOL("SOURCE-INDEX",AB_package);
    Qtarget_index = STATIC_SYMBOL("TARGET-INDEX",AB_package);
    list_constant_255 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,Qtarget_start,
	    list_constant_246);
    list_constant_253 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    Qtarget_index);
    list_constant_254 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    Qsource_index);
    list_constant_256 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_253,
	    list_constant_254);
    Qfinally = STATIC_SYMBOL("FINALLY",AB_package);
    list_constant_257 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_41,
	    list_constant_255);
    list_constant_276 = STATIC_LIST((SI_Long)21L,Qab_loop,Qwith,
	    Qtarget_start,Qnum_eq,list_constant_250,Qfor,Qsource_index,
	    Qfrom,list_constant_251,Qbelow,list_constant_41,Qfor,
	    Qtarget_index,Qfrom,Qtarget_start,Qbelow,list_constant_255,Qdo,
	    list_constant_256,Qfinally,list_constant_257);
    list_constant_277 = STATIC_CONS(Qgesture_push,list_constant_246);
    Qno_previous_frame = STATIC_SYMBOL("NO-PREVIOUS-FRAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_previous_frame,No_previous_frame);
    list_constant_258 = STATIC_LIST((SI_Long)3L,Qeq,Qprevious_frame,
	    Qno_previous_frame);
    Qgesture_thread_done = STATIC_SYMBOL("GESTURE-THREAD-DONE",AB_package);
    list_constant_259 = STATIC_LIST((SI_Long)2L,Qgo,Qgesture_thread_done);
    list_constant_270 = STATIC_LIST((SI_Long)2L,list_constant_258,
	    list_constant_259);
    list_constant_266 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_14,
	    Qprevious_frame);
    list_constant_260 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    Qprevious_frame,list_constant_243);
    list_constant_261 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_260);
    list_constant_267 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_22,
	    list_constant_261);
    list_constant_262 = STATIC_CONS(list_constant_22,Qnil);
    list_constant_263 = STATIC_CONS(Qgesture_function_instructions,
	    list_constant_262);
    list_constant_268 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_170,
	    list_constant_263);
    list_constant_264 = STATIC_LIST_STAR((SI_Long)3L,Qplus_f,
	    Qprevious_frame,list_constant_154);
    list_constant_265 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_264);
    list_constant_269 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_3,
	    list_constant_265);
    list_constant_271 = STATIC_LIST((SI_Long)5L,Qt,list_constant_266,
	    list_constant_267,list_constant_268,list_constant_269);
    list_constant_278 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_270,
	    list_constant_271);
    list_constant_280 = STATIC_LIST((SI_Long)7L,list_constant_272,
	    list_constant_273,list_constant_274,list_constant_275,
	    list_constant_276,list_constant_277,list_constant_278);
    mutate_global_property(Qprocedure_return,LIST_3(list_constant_279,
	    FIX((SI_Long)11L),list_constant_280),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qprocedure_return,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qset_local_from_return = STATIC_SYMBOL("SET-LOCAL-FROM-RETURN",AB_package);
    mutate_global_property(Qset_local_from_return,LIST_3(list_constant_20,
	    FIX((SI_Long)17L),list_constant_21),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qset_local_from_return,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qreturn_check = STATIC_SYMBOL("RETURN-CHECK",AB_package);
    list_constant_281 = STATIC_CONS(Qreturn_count,list_constant_38);
    Qdesired_return_count = STATIC_SYMBOL("DESIRED-RETURN-COUNT",AB_package);
    list_constant_282 = STATIC_CONS(Qdesired_return_count,list_constant_87);
    Qtemp = STATIC_SYMBOL("TEMP",AB_package);
    list_constant_283 = STATIC_CONS(Qtemp,list_constant_195);
    list_constant_308 = STATIC_LIST((SI_Long)3L,list_constant_281,
	    list_constant_282,list_constant_283);
    list_constant_306 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qdesired_return_count,list_constant_15);
    Qlt_f = STATIC_SYMBOL("<F",AB_package);
    list_constant_284 = STATIC_CONS(Qdesired_return_count,Qnil);
    list_constant_285 = STATIC_CONS(Qreturn_count,list_constant_284);
    list_constant_289 = STATIC_CONS(Qlt_f,list_constant_285);
    Qunsufficient_number_of_return_values = 
	    STATIC_SYMBOL("UNSUFFICIENT-NUMBER-OF-RETURN-VALUES",AB_package);
    list_constant_286 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qunsufficient_number_of_return_values);
    Qnumber_desired = STATIC_SYMBOL("NUMBER-DESIRED",AB_package);
    list_constant_287 = STATIC_LIST((SI_Long)2L,Qquote,Qnumber_desired);
    Qnumber_received = STATIC_SYMBOL("NUMBER-RECEIVED",AB_package);
    list_constant_288 = STATIC_LIST((SI_Long)2L,Qquote,Qnumber_received);
    list_constant_290 = STATIC_LIST_STAR((SI_Long)6L,
	    Qgesture_evaluation_error,list_constant_286,list_constant_287,
	    Qdesired_return_count,list_constant_288,list_constant_246);
    list_constant_304 = STATIC_LIST((SI_Long)2L,list_constant_289,
	    list_constant_290);
    list_constant_300 = STATIC_CONS(Qgt_f,list_constant_285);
    list_constant_301 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qtemp,
	    list_constant_95);
    list_constant_292 = STATIC_LIST_STAR((SI_Long)3L,Qlt_f,Qi,
	    list_constant_284);
    Qgensym_push = STATIC_SYMBOL("GENSYM-PUSH",AB_package);
    list_constant_291 = STATIC_CONS(Qtemp,Qnil);
    list_constant_293 = STATIC_LIST_STAR((SI_Long)3L,Qgensym_push,
	    list_constant_2,list_constant_291);
    list_constant_295 = STATIC_LIST((SI_Long)2L,list_constant_292,
	    list_constant_293);
    list_constant_294 = STATIC_CONS(Qreclaim_if_evaluation_value,
	    list_constant_91);
    list_constant_296 = STATIC_LIST((SI_Long)2L,Qt,list_constant_294);
    list_constant_297 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_295,
	    list_constant_296);
    list_constant_302 = STATIC_LIST((SI_Long)9L,Qab_loop,Qfor,Qi,Qfrom,
	    FIX((SI_Long)0L),Qbelow,Qreturn_count,Qdo,list_constant_297);
    Qgensym_pop = STATIC_SYMBOL("GENSYM-POP",AB_package);
    list_constant_298 = STATIC_CONS(Qgensym_pop,list_constant_291);
    list_constant_299 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_298);
    list_constant_303 = STATIC_LIST((SI_Long)9L,Qab_loop,Qfor,Qi,Qfrom,
	    FIX((SI_Long)0L),Qbelow,Qdesired_return_count,Qdo,
	    list_constant_299);
    list_constant_305 = STATIC_LIST((SI_Long)4L,list_constant_300,
	    list_constant_301,list_constant_302,list_constant_303);
    list_constant_307 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_304,
	    list_constant_305);
    list_constant_309 = STATIC_LIST((SI_Long)3L,list_constant_273,
	    list_constant_306,list_constant_307);
    mutate_global_property(Qreturn_check,LIST_3(list_constant_308,
	    FIX((SI_Long)18L),list_constant_309),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qreturn_check,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qfunction_return = STATIC_SYMBOL("FUNCTION-RETURN",AB_package);
    mutate_global_property(Qfunction_return,LIST_3(Qnil,FIX((SI_Long)12L),
	    Qnil),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qfunction_return,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_next_method = STATIC_SYMBOL("PUSH-NEXT-METHOD",AB_package);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    list_constant_310 = STATIC_CONS(Qab_method,list_constant_38);
    Qnext_method = STATIC_SYMBOL("NEXT-METHOD",AB_package);
    list_constant_311 = STATIC_CONS(Qnext_method,list_constant_87);
    list_constant_335 = STATIC_LIST((SI_Long)2L,list_constant_310,
	    list_constant_311);
    list_constant_312 = STATIC_CONS(Qgesture_function,list_constant_15);
    list_constant_330 = STATIC_LIST((SI_Long)3L,Qsetf,Qab_method,
	    list_constant_312);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_313 = STATIC_CONS(Qab_method,Qnil);
    list_constant_316 = STATIC_CONS(Qnull,list_constant_313);
    list_constant_314 = STATIC_CONS(Qgesture_function_method_p,
	    list_constant_313);
    list_constant_315 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_314);
    list_constant_317 = STATIC_LIST((SI_Long)3L,Qand,list_constant_314,
	    list_constant_315);
    list_constant_321 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_316,
	    list_constant_317);
    Qundefined_method = STATIC_SYMBOL("UNDEFINED-METHOD",AB_package);
    list_constant_319 = STATIC_LIST((SI_Long)2L,Qquote,Qundefined_method);
    list_constant_318 = STATIC_CONS(Qgesture_function_name,list_constant_313);
    list_constant_320 = STATIC_LIST((SI_Long)2L,list_constant_97,
	    list_constant_318);
    list_constant_322 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_319,list_constant_320);
    list_constant_331 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_321,
	    list_constant_322);
    list_constant_323 = STATIC_CONS(Qgesture_function_argument_count,
	    list_constant_262);
    list_constant_324 = STATIC_LIST((SI_Long)3L,Q_f,list_constant_14,
	    list_constant_323);
    list_constant_325 = STATIC_LIST((SI_Long)2L,Qgesture_stack_ref,
	    list_constant_324);
    list_constant_326 = STATIC_CONS(Qt,Qnil);
    list_constant_327 = STATIC_LIST_STAR((SI_Long)4L,
	    Qcompute_effective_gesture_method,Qab_method,list_constant_325,
	    list_constant_326);
    list_constant_332 = STATIC_LIST((SI_Long)3L,Qsetf,Qnext_method,
	    list_constant_327);
    Qab_no_next_method = STATIC_SYMBOL("NO-NEXT-METHOD",AB_package);
    list_constant_328 = STATIC_LIST((SI_Long)2L,Qquote,Qab_no_next_method);
    list_constant_329 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_328,list_constant_320);
    list_constant_333 = STATIC_LIST((SI_Long)3L,Qunless,Qnext_method,
	    list_constant_329);
    list_constant_334 = STATIC_LIST((SI_Long)2L,Qgesture_push,Qnext_method);
    list_constant_336 = STATIC_LIST((SI_Long)5L,list_constant_330,
	    list_constant_331,list_constant_332,list_constant_333,
	    list_constant_334);
    mutate_global_property(Qpush_next_method,LIST_3(list_constant_335,
	    FIX((SI_Long)13L),list_constant_336),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_next_method,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    SET_SYMBOL_FUNCTION(Qcompute_effective_gesture_method,
	    STATIC_FUNCTION(compute_effective_gesture_method,NIL,FALSE,3,3));
    Qexists = STATIC_SYMBOL("EXISTS",AB_package);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qevaluation_true_value = STATIC_SYMBOL("EVALUATION-TRUE-VALUE",AB_package);
    list_constant_338 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    Qevaluation_true_value);
    list_constant_337 = STATIC_CONS(Qevaluation_false_value,Qnil);
    list_constant_339 = STATIC_CONS(Qgesture_push,list_constant_337);
    list_constant_340 = STATIC_LIST((SI_Long)4L,Qab_if,list_constant_2,
	    list_constant_338,list_constant_339);
    list_constant_341 = STATIC_CONS(list_constant_340,Qnil);
    mutate_global_property(Qexists,LIST_3(Qnil,FIX((SI_Long)14L),
	    list_constant_341),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qexists,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_gesture_def = STATIC_SYMBOL("PUSH-GESTURE-DEF",AB_package);
    list_constant_353 = STATIC_CONS(list_constant_39,Qnil);
    list_constant_342 = STATIC_CONS(list_constant_312,Qnil);
    list_constant_350 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qroutine,
	    list_constant_342);
    list_constant_344 = STATIC_CONS(Qnull,list_constant_47);
    list_constant_343 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_54);
    list_constant_345 = STATIC_LIST((SI_Long)3L,Qand,list_constant_54,
	    list_constant_343);
    list_constant_348 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_344,
	    list_constant_345);
    Qundefined_procedure_or_method = 
	    STATIC_SYMBOL("UNDEFINED-PROCEDURE-OR-METHOD",AB_package);
    list_constant_346 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qundefined_procedure_or_method);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    list_constant_347 = STATIC_LIST((SI_Long)2L,Qquote,Qname);
    list_constant_349 = STATIC_LIST_STAR((SI_Long)4L,
	    Qgesture_evaluation_error,list_constant_346,list_constant_347,
	    list_constant_15);
    list_constant_351 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_348,
	    list_constant_349);
    list_constant_352 = STATIC_CONS(Qgesture_push,list_constant_47);
    list_constant_354 = STATIC_LIST((SI_Long)3L,list_constant_350,
	    list_constant_351,list_constant_352);
    mutate_global_property(Qpush_gesture_def,LIST_3(list_constant_353,
	    FIX((SI_Long)15L),list_constant_354),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_gesture_def,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsamep = STATIC_SYMBOL("SAMEP",AB_package);
    list_constant_355 = STATIC_LIST_STAR((SI_Long)3L,Qeq,list_constant_2,
	    list_constant_91);
    list_constant_356 = STATIC_LIST_STAR((SI_Long)4L,Qab_if,
	    list_constant_355,Qevaluation_true_value,list_constant_337);
    list_constant_357 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_356);
    list_constant_358 = STATIC_CONS(list_constant_357,Qnil);
    mutate_global_property(Qsamep,LIST_3(Qnil,FIX((SI_Long)16L),
	    list_constant_358),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsamep,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qget_local_or_no_item = STATIC_SYMBOL("GET-LOCAL-OR-NO-ITEM",AB_package);
    list_constant_359 = STATIC_LIST_STAR((SI_Long)3L,Qsetq,Qvalue,
	    list_constant_95);
    list_constant_360 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_27,
	    list_constant_359);
    list_constant_361 = STATIC_CONS(Qgesture_push,list_constant_31);
    list_constant_362 = STATIC_LIST((SI_Long)3L,list_constant_33,
	    list_constant_360,list_constant_361);
    mutate_global_property(Qget_local_or_no_item,LIST_3(list_constant_20,
	    FIX((SI_Long)19L),list_constant_362),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qget_local_or_no_item,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qadd_fixnum = STATIC_SYMBOL("ADD-FIXNUM",AB_package);
    list_constant_363 = STATIC_CONS(list_constant_2,list_constant_91);
    list_constant_364 = STATIC_CONS(Qplus_f,list_constant_363);
    list_constant_365 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_364);
    list_constant_366 = STATIC_CONS(list_constant_365,Qnil);
    mutate_global_property(Qadd_fixnum,LIST_3(Qnil,FIX((SI_Long)20L),
	    list_constant_366),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qadd_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsubtract_fixnum = STATIC_SYMBOL("SUBTRACT-FIXNUM",AB_package);
    list_constant_367 = STATIC_CONS(Q_f,list_constant_363);
    list_constant_368 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_367);
    list_constant_369 = STATIC_CONS(list_constant_368,Qnil);
    mutate_global_property(Qsubtract_fixnum,LIST_3(Qnil,FIX((SI_Long)21L),
	    list_constant_369),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsubtract_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qmultiply_fixnum = STATIC_SYMBOL("MULTIPLY-FIXNUM",AB_package);
    Qstar_f = STATIC_SYMBOL("*F",AB_package);
    list_constant_370 = STATIC_CONS(Qstar_f,list_constant_363);
    list_constant_371 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_370);
    list_constant_372 = STATIC_CONS(list_constant_371,Qnil);
    mutate_global_property(Qmultiply_fixnum,LIST_3(Qnil,FIX((SI_Long)22L),
	    list_constant_372),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qmultiply_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_fixnum = STATIC_SYMBOL("EQUAL-FIXNUM",AB_package);
    list_constant_373 = STATIC_CONS(Qeq_f,list_constant_363);
    list_constant_374 = STATIC_CONS(Qevaluation_true_value,list_constant_337);
    list_constant_375 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_373,list_constant_374);
    list_constant_376 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_375);
    list_constant_377 = STATIC_CONS(list_constant_376,Qnil);
    mutate_global_property(Qequal_fixnum,LIST_3(Qnil,FIX((SI_Long)23L),
	    list_constant_377),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_fixnum = STATIC_SYMBOL("PUSH-FIXNUM",AB_package);
    list_constant_378 = STATIC_CONS(Qgesture_push,list_constant_15);
    list_constant_379 = STATIC_CONS(list_constant_378,Qnil);
    mutate_global_property(Qpush_fixnum,LIST_3(Qnil,FIX((SI_Long)24L),
	    list_constant_379),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qincrement = STATIC_SYMBOL("INCREMENT",AB_package);
    list_constant_380 = STATIC_CONS(Qincff,list_constant_91);
    list_constant_381 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_380);
    list_constant_382 = STATIC_CONS(list_constant_381,Qnil);
    mutate_global_property(Qincrement,LIST_3(Qnil,FIX((SI_Long)25L),
	    list_constant_382),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qincrement,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qdecrement = STATIC_SYMBOL("DECREMENT",AB_package);
    Qdecff = STATIC_SYMBOL("DECFF",AB_package);
    list_constant_383 = STATIC_CONS(Qdecff,list_constant_91);
    list_constant_384 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_383);
    list_constant_385 = STATIC_CONS(list_constant_384,Qnil);
    mutate_global_property(Qdecrement,LIST_3(Qnil,FIX((SI_Long)26L),
	    list_constant_385),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qdecrement,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qnegate_fixnum = STATIC_SYMBOL("NEGATE-FIXNUM",AB_package);
    list_constant_386 = STATIC_CONS(Q_f,list_constant_91);
    list_constant_387 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_386);
    list_constant_388 = STATIC_CONS(list_constant_387,Qnil);
    mutate_global_property(Qnegate_fixnum,LIST_3(Qnil,FIX((SI_Long)27L),
	    list_constant_388),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qnegate_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_fixnum = STATIC_SYMBOL("GREATER-THAN-FIXNUM",AB_package);
    Qfirst_arg = STATIC_SYMBOL("FIRST-ARG",AB_package);
    list_constant_389 = STATIC_CONS(Qfirst_arg,list_constant_38);
    Qsecond_arg = STATIC_SYMBOL("SECOND-ARG",AB_package);
    list_constant_390 = STATIC_CONS(Qsecond_arg,list_constant_87);
    list_constant_396 = STATIC_LIST((SI_Long)2L,list_constant_389,
	    list_constant_390);
    list_constant_393 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qsecond_arg,
	    list_constant_91);
    list_constant_394 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qfirst_arg,
	    list_constant_91);
    list_constant_391 = STATIC_LIST((SI_Long)3L,Qgt_f,Qfirst_arg,Qsecond_arg);
    list_constant_392 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_391,list_constant_374);
    list_constant_395 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_392);
    list_constant_397 = STATIC_LIST((SI_Long)3L,list_constant_393,
	    list_constant_394,list_constant_395);
    mutate_global_property(Qgreater_than_fixnum,LIST_3(list_constant_396,
	    FIX((SI_Long)28L),list_constant_397),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qgreater_than_fixnum,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_fixnum = STATIC_SYMBOL("LESS-THAN-FIXNUM",AB_package);
    list_constant_398 = STATIC_LIST((SI_Long)2L,Qfirst_arg,Qsecond_arg);
    list_constant_399 = STATIC_CONS(Qlt_f,list_constant_398);
    list_constant_400 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_399,list_constant_374);
    list_constant_401 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_400);
    list_constant_402 = STATIC_LIST((SI_Long)3L,list_constant_393,
	    list_constant_394,list_constant_401);
    mutate_global_property(Qless_than_fixnum,LIST_3(list_constant_396,
	    FIX((SI_Long)29L),list_constant_402),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qless_than_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_equal_fixnum = STATIC_SYMBOL("GREATER-THAN-EQUAL-FIXNUM",
	    AB_package);
    Qgt_eq_f = STATIC_SYMBOL(">=F",AB_package);
    list_constant_403 = STATIC_CONS(Qgt_eq_f,list_constant_398);
    list_constant_404 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_403,list_constant_374);
    list_constant_405 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_404);
    list_constant_406 = STATIC_LIST((SI_Long)3L,list_constant_393,
	    list_constant_394,list_constant_405);
    mutate_global_property(Qgreater_than_equal_fixnum,
	    LIST_3(list_constant_396,FIX((SI_Long)30L),list_constant_406),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qgreater_than_equal_fixnum,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_equal_fixnum = STATIC_SYMBOL("LESS-THAN-EQUAL-FIXNUM",
	    AB_package);
    Qlt_eq_f = STATIC_SYMBOL("<=F",AB_package);
    list_constant_407 = STATIC_CONS(Qlt_eq_f,list_constant_398);
    list_constant_408 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_407,list_constant_374);
    list_constant_409 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_408);
    list_constant_410 = STATIC_LIST((SI_Long)3L,list_constant_393,
	    list_constant_394,list_constant_409);
    mutate_global_property(Qless_than_equal_fixnum,
	    LIST_3(list_constant_396,FIX((SI_Long)31L),list_constant_410),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qless_than_equal_fixnum,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qquotient_fixnum = STATIC_SYMBOL("QUOTIENT-FIXNUM",AB_package);
    Qdividend = STATIC_SYMBOL("DIVIDEND",AB_package);
    list_constant_411 = STATIC_CONS(Qdividend,list_constant_38);
    Qdivisor = STATIC_SYMBOL("DIVISOR",AB_package);
    list_constant_412 = STATIC_CONS(Qdivisor,list_constant_87);
    list_constant_417 = STATIC_LIST((SI_Long)2L,list_constant_411,
	    list_constant_412);
    list_constant_414 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qdivisor,
	    list_constant_91);
    list_constant_415 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qdividend,
	    list_constant_91);
    Qtruncatef_first = STATIC_SYMBOL("TRUNCATEF-FIRST",AB_package);
    list_constant_413 = STATIC_LIST((SI_Long)3L,Qtruncatef_first,Qdividend,
	    Qdivisor);
    list_constant_416 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_413);
    list_constant_418 = STATIC_LIST((SI_Long)3L,list_constant_414,
	    list_constant_415,list_constant_416);
    mutate_global_property(Qquotient_fixnum,LIST_3(list_constant_417,
	    FIX((SI_Long)32L),list_constant_418),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qquotient_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qremainder_fixnum = STATIC_SYMBOL("REMAINDER-FIXNUM",AB_package);
    Qrem_fixnums = STATIC_SYMBOL("REM-FIXNUMS",AB_package);
    list_constant_419 = STATIC_LIST((SI_Long)2L,Qdividend,Qdivisor);
    list_constant_420 = STATIC_CONS(Qrem_fixnums,list_constant_419);
    list_constant_421 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_420);
    list_constant_422 = STATIC_LIST((SI_Long)3L,list_constant_414,
	    list_constant_415,list_constant_421);
    mutate_global_property(Qremainder_fixnum,LIST_3(list_constant_417,
	    FIX((SI_Long)33L),list_constant_422),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qremainder_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qdivide_fixnum = STATIC_SYMBOL("DIVIDE-FIXNUM",AB_package);
    mutate_global_property(Qdivide_fixnum,LIST_3(list_constant_417,
	    FIX((SI_Long)34L),list_constant_422),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qdivide_fixnum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qadd_quantity = STATIC_SYMBOL("ADD-QUANTITY",AB_package);
    mutate_global_property(Qadd_quantity,LIST_3(Qnil,FIX((SI_Long)40L),
	    list_constant_366),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qadd_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsubtract_quantity = STATIC_SYMBOL("SUBTRACT-QUANTITY",AB_package);
    list_constant_423 = STATIC_CONS(Q_f,list_constant_398);
    list_constant_424 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_423);
    list_constant_425 = STATIC_LIST((SI_Long)3L,list_constant_393,
	    list_constant_394,list_constant_424);
    mutate_global_property(Qsubtract_quantity,LIST_3(list_constant_396,
	    FIX((SI_Long)41L),list_constant_425),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsubtract_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qmultiply_quantity = STATIC_SYMBOL("MULTIPLY-QUANTITY",AB_package);
    mutate_global_property(Qmultiply_quantity,LIST_3(Qnil,
	    FIX((SI_Long)42L),list_constant_372),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qmultiply_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_quantity = STATIC_SYMBOL("EQUAL-QUANTITY",AB_package);
    mutate_global_property(Qequal_quantity,LIST_3(Qnil,FIX((SI_Long)43L),
	    list_constant_377),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_quantity = STATIC_SYMBOL("PUSH-QUANTITY",AB_package);
    string_constant_13 = STATIC_STRING("pre pushfix sp=~s~%");
    list_constant_426 = STATIC_LIST_STAR((SI_Long)4L,Qab_format,Qt,
	    string_constant_13,list_constant_105);
    list_constant_427 = STATIC_LIST((SI_Long)3L,list_constant_426,
	    list_constant_378,list_constant_426);
    mutate_global_property(Qpush_quantity,LIST_3(Qnil,FIX((SI_Long)44L),
	    list_constant_427),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qnegate_quantity = STATIC_SYMBOL("NEGATE-QUANTITY",AB_package);
    mutate_global_property(Qnegate_quantity,LIST_3(Qnil,FIX((SI_Long)47L),
	    list_constant_388),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qnegate_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_quantity = STATIC_SYMBOL("GREATER-THAN-QUANTITY",AB_package);
    mutate_global_property(Qgreater_than_quantity,LIST_3(list_constant_396,
	    FIX((SI_Long)48L),list_constant_397),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qgreater_than_quantity,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_quantity = STATIC_SYMBOL("LESS-THAN-QUANTITY",AB_package);
    mutate_global_property(Qless_than_quantity,LIST_3(list_constant_396,
	    FIX((SI_Long)49L),list_constant_402),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qless_than_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_equal_quantity = 
	    STATIC_SYMBOL("GREATER-THAN-EQUAL-QUANTITY",AB_package);
    mutate_global_property(Qgreater_than_equal_quantity,
	    LIST_3(list_constant_396,FIX((SI_Long)50L),list_constant_406),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qgreater_than_equal_quantity,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_equal_quantity = STATIC_SYMBOL("LESS-THAN-EQUAL-QUANTITY",
	    AB_package);
    mutate_global_property(Qless_than_equal_quantity,
	    LIST_3(list_constant_396,FIX((SI_Long)51L),list_constant_410),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qless_than_equal_quantity,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qquotient_quantity = STATIC_SYMBOL("QUOTIENT-QUANTITY",AB_package);
    mutate_global_property(Qquotient_quantity,LIST_3(list_constant_417,
	    FIX((SI_Long)52L),list_constant_418),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qquotient_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qremainder_quantity = STATIC_SYMBOL("REMAINDER-QUANTITY",AB_package);
    mutate_global_property(Qremainder_quantity,LIST_3(list_constant_417,
	    FIX((SI_Long)53L),list_constant_422),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qremainder_quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Qput_attribute_value = STATIC_SYMBOL("PUT-ATTRIBUTE-VALUE",AB_package);
    Tw_predefined_user_attributes = Nil;
    Qset_slot = STATIC_SYMBOL("SET-SLOT",AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    list_constant_428 = STATIC_CONS(Qframe,list_constant_38);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    list_constant_429 = STATIC_CONS(Qnew_value,list_constant_87);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    list_constant_430 = STATIC_CONS(Qattribute_name,list_constant_195);
    list_constant_510 = STATIC_LIST((SI_Long)3L,list_constant_428,
	    list_constant_429,list_constant_430);
    list_constant_506 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qframe,
	    list_constant_91);
    list_constant_507 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qnew_value,
	    list_constant_91);
    list_constant_508 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qattribute_name,
	    list_constant_15);
    Qclass_qualifier_qm = STATIC_SYMBOL("CLASS-QUALIFIER\?",AB_package);
    list_constant_444 = STATIC_CONS(Qclass_qualifier_qm,list_constant_95);
    Qclass_description = STATIC_SYMBOL("CLASS-DESCRIPTION",AB_package);
    Qclass_description_slot = STATIC_SYMBOL("CLASS-DESCRIPTION-SLOT",
	    AB_package);
    list_constant_431 = STATIC_LIST((SI_Long)2L,Qclass_description_slot,
	    Qframe);
    list_constant_445 = STATIC_LIST((SI_Long)2L,Qclass_description,
	    list_constant_431);
    Qslot_description_qm = STATIC_SYMBOL("SLOT-DESCRIPTION\?",AB_package);
    Qget_slot_description_of_class_description = 
	    STATIC_SYMBOL("GET-SLOT-DESCRIPTION-OF-CLASS-DESCRIPTION",
	    AB_package);
    list_constant_432 = STATIC_CONS(Qclass_qualifier_qm,Qnil);
    list_constant_433 = STATIC_LIST_STAR((SI_Long)4L,
	    Qget_slot_description_of_class_description,Qattribute_name,
	    Qclass_description,list_constant_432);
    list_constant_446 = STATIC_LIST((SI_Long)2L,Qslot_description_qm,
	    list_constant_433);
    Qvisible_slot_qm = STATIC_SYMBOL("VISIBLE-SLOT\?",AB_package);
    Qfeature_assq_macro = STATIC_SYMBOL("FEATURE-ASSQ-MACRO",AB_package);
    list_constant_435 = STATIC_LIST((SI_Long)2L,Qquote,Qtype);
    Qslot_features = STATIC_SYMBOL("SLOT-FEATURES",AB_package);
    list_constant_434 = STATIC_CONS(Qslot_description_qm,Qnil);
    list_constant_436 = STATIC_CONS(Qslot_features,list_constant_434);
    list_constant_438 = STATIC_LIST((SI_Long)3L,Qfeature_assq_macro,
	    list_constant_435,list_constant_436);
    Qdo_not_put_slot_in_attribute_tables_p = 
	    STATIC_SYMBOL("DO-NOT-PUT-SLOT-IN-ATTRIBUTE-TABLES-P",AB_package);
    SET_SYMBOL_FUNCTION(Qdo_not_put_slot_in_attribute_tables_p,
	    STATIC_FUNCTION(do_not_put_slot_in_attribute_tables_p,NIL,TRUE,
	    2,3));
    list_constant_437 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdo_not_put_slot_in_attribute_tables_p,Qslot_description_qm,
	    list_constant_326);
    list_constant_439 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_437);
    list_constant_440 = STATIC_LIST((SI_Long)4L,Qand,Qslot_description_qm,
	    list_constant_438,list_constant_439);
    list_constant_447 = STATIC_LIST((SI_Long)2L,Qvisible_slot_qm,
	    list_constant_440);
    Qslot_value_qm = STATIC_SYMBOL("SLOT-VALUE\?",AB_package);
    Qget_slot_description_value = 
	    STATIC_SYMBOL("GET-SLOT-DESCRIPTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_slot_description_value,
	    STATIC_FUNCTION(get_slot_description_value,NIL,FALSE,2,2));
    list_constant_441 = STATIC_LIST_STAR((SI_Long)3L,
	    Qget_slot_description_value,Qframe,list_constant_434);
    list_constant_442 = STATIC_LIST_STAR((SI_Long)4L,Qab_if,
	    Qvisible_slot_qm,list_constant_441,list_constant_95);
    list_constant_448 = STATIC_LIST((SI_Long)2L,Qslot_value_qm,
	    list_constant_442);
    Qslot_value_class_description_qm = 
	    STATIC_SYMBOL("SLOT-VALUE-CLASS-DESCRIPTION\?",AB_package);
    Qframep = STATIC_SYMBOL("FRAMEP",AB_package);
    list_constant_443 = STATIC_LIST((SI_Long)2L,Qframep,Qslot_value_qm);
    list_constant_449 = STATIC_LIST((SI_Long)2L,
	    Qslot_value_class_description_qm,list_constant_443);
    list_constant_504 = STATIC_LIST((SI_Long)6L,list_constant_444,
	    list_constant_445,list_constant_446,list_constant_447,
	    list_constant_448,list_constant_449);
    list_constant_450 = STATIC_CONS(Qnew_value,Qnil);
    list_constant_452 = STATIC_CONS(Qframep,list_constant_450);
    Qsub_items_not_yet_supported = 
	    STATIC_SYMBOL("SUB-ITEMS-NOT-YET-SUPPORTED",AB_package);
    list_constant_451 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qsub_items_not_yet_supported);
    list_constant_453 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_451);
    list_constant_499 = STATIC_LIST((SI_Long)2L,list_constant_452,
	    list_constant_453);
    Qillegal_conclude_for_tw = STATIC_SYMBOL("ILLEGAL-CONCLUDE-FOR-TW",
	    AB_package);
    list_constant_454 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qillegal_conclude_for_tw);
    list_constant_455 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_454);
    list_constant_500 = STATIC_LIST((SI_Long)2L,
	    Qslot_value_class_description_qm,list_constant_455);
    list_constant_457 = STATIC_LIST((SI_Long)2L,Qnull,Qvisible_slot_qm);
    Qunknown_attribute_reference = 
	    STATIC_SYMBOL("UNKNOWN-ATTRIBUTE-REFERENCE",AB_package);
    list_constant_456 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qunknown_attribute_reference);
    list_constant_458 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_456);
    list_constant_501 = STATIC_LIST((SI_Long)2L,list_constant_457,
	    list_constant_458);
    Quser_defined_slot_description_p = 
	    STATIC_SYMBOL("USER-DEFINED-SLOT-DESCRIPTION-P",AB_package);
    list_constant_459 = STATIC_CONS(Quser_defined_slot_description_p,
	    list_constant_434);
    list_constant_460 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_459);
    Qassq_macro = STATIC_SYMBOL("ASSQ-MACRO",AB_package);
    Qtw_predefined_user_attributes = 
	    STATIC_SYMBOL("TW-PREDEFINED-USER-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtw_predefined_user_attributes,
	    Tw_predefined_user_attributes);
    list_constant_461 = STATIC_LIST((SI_Long)3L,Qassq_macro,
	    Qattribute_name,Qtw_predefined_user_attributes);
    list_constant_463 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_460,
	    list_constant_461);
    Qattempt_to_conclude_to_inaccessibe_system_slot = 
	    STATIC_SYMBOL("ATTEMPT-TO-CONCLUDE-TO-INACCESSIBE-SYSTEM-SLOT",
	    AB_package);
    list_constant_462 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qattempt_to_conclude_to_inaccessibe_system_slot);
    list_constant_464 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_462);
    list_constant_502 = STATIC_LIST((SI_Long)2L,list_constant_463,
	    list_constant_464);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qslot_type_specification = STATIC_SYMBOL("SLOT-TYPE-SPECIFICATION",
	    AB_package);
    list_constant_465 = STATIC_CONS(Qslot_type_specification,
	    list_constant_434);
    list_constant_466 = STATIC_LIST((SI_Long)2L,Qslot_type_specification,
	    list_constant_465);
    list_constant_496 = STATIC_CONS(list_constant_466,Qnil);
    Qtype_specification_type_p = STATIC_SYMBOL("TYPE-SPECIFICATION-TYPE-P",
	    AB_package);
    list_constant_477 = STATIC_LIST((SI_Long)3L,Qtype_specification_type_p,
	    Qnew_value,Qslot_type_specification);
    Qevaluation_truth_value_p = STATIC_SYMBOL("EVALUATION-TRUTH-VALUE-P",
	    AB_package);
    list_constant_471 = STATIC_CONS(Qevaluation_truth_value_p,
	    list_constant_450);
    Qtw_change_slot_description_value = 
	    STATIC_SYMBOL("TW-CHANGE-SLOT-DESCRIPTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qtw_change_slot_description_value,
	    STATIC_FUNCTION(tw_change_slot_description_value,NIL,FALSE,5,5));
    Qslot_value_list = STATIC_SYMBOL("SLOT-VALUE-LIST",AB_package);
    Qevaluation_truth_value_value = 
	    STATIC_SYMBOL("EVALUATION-TRUTH-VALUE-VALUE",AB_package);
    list_constant_467 = STATIC_CONS(Qevaluation_truth_value_value,
	    list_constant_450);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_468 = STATIC_LIST((SI_Long)2L,Qquote,Qtruth_value);
    list_constant_469 = STATIC_LIST((SI_Long)3L,Qslot_value_list,
	    list_constant_467,list_constant_468);
    list_constant_470 = STATIC_CONS(Qattribute_name,list_constant_432);
    list_constant_472 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtw_change_slot_description_value,Qframe,Qslot_description_qm,
	    list_constant_469,list_constant_470);
    Qreclaim_evaluation_truth_value = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-TRUTH-VALUE",AB_package);
    list_constant_473 = STATIC_CONS(Qreclaim_evaluation_truth_value,
	    list_constant_450);
    list_constant_475 = STATIC_LIST((SI_Long)3L,list_constant_471,
	    list_constant_472,list_constant_473);
    list_constant_474 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtw_change_slot_description_value,Qframe,Qslot_description_qm,
	    Qnew_value,list_constant_470);
    list_constant_476 = STATIC_LIST((SI_Long)2L,Qt,list_constant_474);
    list_constant_478 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_475,
	    list_constant_476);
    list_constant_493 = STATIC_LIST((SI_Long)2L,list_constant_477,
	    list_constant_478);
    Qevaluation_integer_p = STATIC_SYMBOL("EVALUATION-INTEGER-P",AB_package);
    list_constant_480 = STATIC_CONS(Qevaluation_integer_p,list_constant_450);
    list_constant_479 = STATIC_LIST((SI_Long)2L,Qquote,Qfloat);
    list_constant_481 = STATIC_LIST((SI_Long)3L,Qeq,
	    Qslot_type_specification,list_constant_479);
    list_constant_489 = STATIC_LIST((SI_Long)3L,Qand,list_constant_480,
	    list_constant_481);
    Qfloat_value = STATIC_SYMBOL("FLOAT-VALUE",AB_package);
    Qmake_evaluation_float = STATIC_SYMBOL("MAKE-EVALUATION-FLOAT",AB_package);
    Qcoerce_fixnum_to_gensym_float = 
	    STATIC_SYMBOL("COERCE-FIXNUM-TO-GENSYM-FLOAT",AB_package);
    Qevaluation_integer_value = STATIC_SYMBOL("EVALUATION-INTEGER-VALUE",
	    AB_package);
    list_constant_482 = STATIC_CONS(Qevaluation_integer_value,
	    list_constant_450);
    list_constant_483 = STATIC_LIST((SI_Long)2L,
	    Qcoerce_fixnum_to_gensym_float,list_constant_482);
    list_constant_484 = STATIC_LIST((SI_Long)2L,Qmake_evaluation_float,
	    list_constant_483);
    list_constant_485 = STATIC_LIST((SI_Long)2L,Qfloat_value,
	    list_constant_484);
    list_constant_486 = STATIC_CONS(list_constant_485,Qnil);
    Qreclaim_evaluation_integer = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-INTEGER",AB_package);
    list_constant_487 = STATIC_CONS(Qreclaim_evaluation_integer,
	    list_constant_450);
    list_constant_488 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtw_change_slot_description_value,Qframe,Qslot_description_qm,
	    Qfloat_value,list_constant_470);
    list_constant_490 = STATIC_LIST((SI_Long)4L,Qab_let,list_constant_486,
	    list_constant_487,list_constant_488);
    list_constant_494 = STATIC_LIST((SI_Long)2L,list_constant_489,
	    list_constant_490);
    Qattribute_type_mismatch = STATIC_SYMBOL("ATTRIBUTE-TYPE-MISMATCH",
	    AB_package);
    list_constant_491 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qattribute_type_mismatch);
    list_constant_492 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_491);
    list_constant_495 = STATIC_LIST((SI_Long)2L,Qt,list_constant_492);
    list_constant_497 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_493,
	    list_constant_494,list_constant_495);
    list_constant_498 = STATIC_LIST((SI_Long)3L,Qab_let,list_constant_496,
	    list_constant_497);
    list_constant_503 = STATIC_LIST((SI_Long)2L,Qt,list_constant_498);
    list_constant_505 = STATIC_LIST((SI_Long)6L,Qcond,list_constant_499,
	    list_constant_500,list_constant_501,list_constant_502,
	    list_constant_503);
    list_constant_509 = STATIC_LIST((SI_Long)3L,Qab_let_star,
	    list_constant_504,list_constant_505);
    list_constant_511 = STATIC_LIST((SI_Long)4L,list_constant_506,
	    list_constant_507,list_constant_508,list_constant_509);
    mutate_global_property(Qset_slot,LIST_3(list_constant_510,
	    FIX((SI_Long)60L),list_constant_511),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qset_slot,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qget_slot = STATIC_SYMBOL("GET-SLOT",AB_package);
    Qframe_or_structure = STATIC_SYMBOL("FRAME-OR-STRUCTURE",AB_package);
    list_constant_512 = STATIC_CONS(Qframe_or_structure,list_constant_38);
    list_constant_513 = STATIC_CONS(Qattribute_name,list_constant_87);
    Qallow_no_item_p = STATIC_SYMBOL("ALLOW-NO-ITEM-P",AB_package);
    list_constant_514 = STATIC_CONS(Qallow_no_item_p,list_constant_195);
    list_constant_556 = STATIC_LIST((SI_Long)3L,list_constant_512,
	    list_constant_513,list_constant_514);
    list_constant_553 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qframe_or_structure,list_constant_91);
    list_constant_554 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qallow_no_item_p,list_constant_15);
    list_constant_515 = STATIC_CONS(Qframe_or_structure,Qnil);
    list_constant_516 = STATIC_CONS(Qnull,list_constant_515);
    list_constant_517 = STATIC_CONS(Qallow_no_item_p,Qnil);
    list_constant_519 = STATIC_LIST_STAR((SI_Long)3L,Qand,
	    list_constant_516,list_constant_517);
    list_constant_518 = STATIC_CONS(Qgesture_push,list_constant_95);
    list_constant_520 = STATIC_CONS(list_constant_518,Qnil);
    list_constant_550 = STATIC_CONS(list_constant_519,list_constant_520);
    Qevaluation_structure_p = STATIC_SYMBOL("EVALUATION-STRUCTURE-P",
	    AB_package);
    list_constant_532 = STATIC_CONS(Qevaluation_structure_p,list_constant_515);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_522 = STATIC_CONS(Qab_structure,list_constant_515);
    Qevaluation_structure_slot = STATIC_SYMBOL("EVALUATION-STRUCTURE-SLOT",
	    AB_package);
    list_constant_521 = STATIC_LIST((SI_Long)3L,Qevaluation_structure_slot,
	    Qab_structure,Qattribute_name);
    list_constant_523 = STATIC_LIST((SI_Long)2L,Qvalue,list_constant_521);
    list_constant_530 = STATIC_LIST((SI_Long)2L,list_constant_522,
	    list_constant_523);
    list_constant_524 = STATIC_CONS(list_constant_36,Qnil);
    list_constant_527 = STATIC_CONS(Qvalue,list_constant_524);
    list_constant_528 = STATIC_CONS(Qallow_no_item_p,list_constant_520);
    Qunknown_structure_attribute_reference = 
	    STATIC_SYMBOL("UNKNOWN-STRUCTURE-ATTRIBUTE-REFERENCE",AB_package);
    list_constant_525 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qunknown_structure_attribute_reference);
    list_constant_526 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_525);
    list_constant_529 = STATIC_LIST((SI_Long)2L,Qt,list_constant_526);
    list_constant_531 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_527,
	    list_constant_528,list_constant_529);
    list_constant_533 = STATIC_LIST((SI_Long)3L,Qab_let_star,
	    list_constant_530,list_constant_531);
    list_constant_551 = STATIC_LIST((SI_Long)2L,list_constant_532,
	    list_constant_533);
    list_constant_534 = STATIC_CONS(Qframe,list_constant_515);
    list_constant_547 = STATIC_LIST((SI_Long)6L,list_constant_534,
	    list_constant_444,list_constant_445,list_constant_446,
	    list_constant_447,list_constant_448);
    list_constant_535 = STATIC_CONS(Qnot,list_constant_517);
    list_constant_536 = STATIC_LIST((SI_Long)3L,Qand,list_constant_457,
	    list_constant_535);
    list_constant_537 = STATIC_CONS(list_constant_458,Qnil);
    list_constant_544 = STATIC_CONS(list_constant_536,list_constant_537);
    Qslot_constantp = STATIC_SYMBOL("SLOT-CONSTANTP",AB_package);
    list_constant_538 = STATIC_CONS(Qslot_value_qm,Qnil);
    list_constant_540 = STATIC_CONS(Qslot_constantp,list_constant_538);
    Qcast_slot_constant_into_evaluation_value = 
	    STATIC_SYMBOL("CAST-SLOT-CONSTANT-INTO-EVALUATION-VALUE",
	    AB_package);
    list_constant_539 = 
	    STATIC_CONS(Qcast_slot_constant_into_evaluation_value,
	    list_constant_538);
    list_constant_541 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_539);
    list_constant_545 = STATIC_LIST((SI_Long)2L,list_constant_540,
	    list_constant_541);
    list_constant_542 = STATIC_CONS(Qcopy_if_evaluation_value,
	    list_constant_538);
    list_constant_543 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_542);
    list_constant_546 = STATIC_LIST((SI_Long)2L,Qt,list_constant_543);
    list_constant_548 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_544,
	    list_constant_545,list_constant_546);
    list_constant_549 = STATIC_LIST((SI_Long)3L,Qab_let_star,
	    list_constant_547,list_constant_548);
    list_constant_552 = STATIC_LIST((SI_Long)2L,Qt,list_constant_549);
    list_constant_555 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_550,
	    list_constant_551,list_constant_552);
    list_constant_557 = STATIC_LIST((SI_Long)4L,list_constant_553,
	    list_constant_508,list_constant_554,list_constant_555);
    mutate_global_property(Qget_slot,LIST_3(list_constant_556,
	    FIX((SI_Long)61L),list_constant_557),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qget_slot,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2symbol = STATIC_SYMBOL("VALUE2SYMBOL",AB_package);
    list_constant_558 = STATIC_CONS(Qvalue,list_constant_91);
    list_constant_567 = STATIC_CONS(Qsetf,list_constant_558);
    list_constant_559 = STATIC_CONS(Qsymbolp,list_constant_31);
    list_constant_560 = STATIC_LIST((SI_Long)3L,Qand,Qvalue,list_constant_559);
    list_constant_561 = STATIC_CONS(list_constant_361,Qnil);
    list_constant_565 = STATIC_CONS(list_constant_560,list_constant_561);
    Qvalue_not_of_type_symbol = STATIC_SYMBOL("VALUE-NOT-OF-TYPE-SYMBOL",
	    AB_package);
    list_constant_562 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_symbol);
    Qthe_value = STATIC_SYMBOL("THE-VALUE",AB_package);
    list_constant_563 = STATIC_LIST((SI_Long)2L,Qquote,Qthe_value);
    list_constant_564 = STATIC_LIST_STAR((SI_Long)4L,
	    Qgesture_evaluation_error,list_constant_562,list_constant_563,
	    list_constant_31);
    list_constant_566 = STATIC_LIST((SI_Long)2L,Qt,list_constant_564);
    list_constant_568 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_565,
	    list_constant_566);
    list_constant_569 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_568);
    mutate_global_property(Qvalue2symbol,LIST_3(list_constant_20,
	    FIX((SI_Long)62L),list_constant_569),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2symbol,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2float = STATIC_SYMBOL("VALUE2FLOAT",AB_package);
    Qmanaged_float_p = STATIC_SYMBOL("MANAGED-FLOAT-P",AB_package);
    list_constant_570 = STATIC_CONS(Qmanaged_float_p,list_constant_31);
    list_constant_574 = STATIC_CONS(list_constant_570,list_constant_561);
    Qvalue_not_of_type_float = STATIC_SYMBOL("VALUE-NOT-OF-TYPE-FLOAT",
	    AB_package);
    list_constant_571 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_float);
    list_constant_572 = STATIC_CONS(list_constant_563,list_constant_31);
    list_constant_573 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_571,list_constant_572);
    list_constant_575 = STATIC_LIST((SI_Long)2L,Qt,list_constant_573);
    list_constant_576 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_574,
	    list_constant_575);
    list_constant_577 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_576);
    mutate_global_property(Qvalue2float,LIST_3(list_constant_20,
	    FIX((SI_Long)63L),list_constant_577),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2quantity = STATIC_SYMBOL("VALUE2QUANTITY",AB_package);
    Qab_fixnump = STATIC_SYMBOL("FIXNUMP",AB_package);
    list_constant_578 = STATIC_CONS(Qab_fixnump,list_constant_31);
    list_constant_579 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_570,
	    list_constant_578);
    list_constant_582 = STATIC_CONS(list_constant_579,list_constant_561);
    Qvalue_not_of_type_quantity = 
	    STATIC_SYMBOL("VALUE-NOT-OF-TYPE-QUANTITY",AB_package);
    list_constant_580 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_quantity);
    list_constant_581 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_580,list_constant_572);
    list_constant_583 = STATIC_LIST((SI_Long)2L,Qt,list_constant_581);
    list_constant_584 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_582,
	    list_constant_583);
    list_constant_585 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_584);
    mutate_global_property(Qvalue2quantity,LIST_3(list_constant_20,
	    FIX((SI_Long)64L),list_constant_585),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2quantity,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2integer = STATIC_SYMBOL("VALUE2INTEGER",AB_package);
    list_constant_588 = STATIC_CONS(list_constant_578,list_constant_561);
    Qvalue_not_of_type_integer = STATIC_SYMBOL("VALUE-NOT-OF-TYPE-INTEGER",
	    AB_package);
    list_constant_586 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_integer);
    list_constant_587 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_586,list_constant_572);
    list_constant_589 = STATIC_LIST((SI_Long)2L,Qt,list_constant_587);
    list_constant_590 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_588,
	    list_constant_589);
    list_constant_591 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_590);
    mutate_global_property(Qvalue2integer,LIST_3(list_constant_20,
	    FIX((SI_Long)65L),list_constant_591),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2integer,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2text = STATIC_SYMBOL("VALUE2TEXT",AB_package);
    Qtext_string_p = STATIC_SYMBOL("TEXT-STRING-P",AB_package);
    list_constant_592 = STATIC_CONS(Qtext_string_p,list_constant_31);
    list_constant_595 = STATIC_CONS(list_constant_592,list_constant_561);
    Qvalue_not_of_type_text = STATIC_SYMBOL("VALUE-NOT-OF-TYPE-TEXT",
	    AB_package);
    list_constant_593 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_text);
    list_constant_594 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_593,list_constant_572);
    list_constant_596 = STATIC_LIST((SI_Long)2L,Qt,list_constant_594);
    list_constant_597 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_595,
	    list_constant_596);
    list_constant_598 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_597);
    mutate_global_property(Qvalue2text,LIST_3(list_constant_20,
	    FIX((SI_Long)66L),list_constant_598),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2text,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2truth_value = STATIC_SYMBOL("VALUE2TRUTH-VALUE",AB_package);
    list_constant_599 = STATIC_CONS(Qevaluation_true_value,Qnil);
    list_constant_600 = STATIC_LIST_STAR((SI_Long)3L,Qeq,Qvalue,
	    list_constant_599);
    list_constant_601 = STATIC_LIST_STAR((SI_Long)3L,Qeq,Qvalue,
	    list_constant_337);
    list_constant_602 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_600,
	    list_constant_601);
    list_constant_605 = STATIC_CONS(list_constant_602,list_constant_561);
    Qvalue_not_of_type_truth_value = 
	    STATIC_SYMBOL("VALUE-NOT-OF-TYPE-TRUTH-VALUE",AB_package);
    list_constant_603 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_not_of_type_truth_value);
    list_constant_604 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_603,list_constant_572);
    list_constant_606 = STATIC_LIST((SI_Long)2L,Qt,list_constant_604);
    list_constant_607 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_605,
	    list_constant_606);
    list_constant_608 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_607);
    mutate_global_property(Qvalue2truth_value,LIST_3(list_constant_20,
	    FIX((SI_Long)67L),list_constant_608),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2truth_value,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2frame = STATIC_SYMBOL("VALUE2FRAME",AB_package);
    Qtarget_class = STATIC_SYMBOL("TARGET-CLASS",AB_package);
    list_constant_609 = STATIC_CONS(Qtarget_class,list_constant_87);
    list_constant_625 = STATIC_LIST((SI_Long)2L,list_constant_13,
	    list_constant_609);
    list_constant_623 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qtarget_class,
	    list_constant_15);
    list_constant_617 = STATIC_CONS(Qframep,list_constant_31);
    Qframe_of_class_p = STATIC_SYMBOL("FRAME-OF-CLASS-P",AB_package);
    list_constant_610 = STATIC_LIST((SI_Long)3L,Qframe_of_class_p,Qvalue,
	    Qtarget_class);
    list_constant_615 = STATIC_CONS(list_constant_610,list_constant_561);
    Qnot_an_instance_of_class = STATIC_SYMBOL("NOT-AN-INSTANCE-OF-CLASS",
	    AB_package);
    list_constant_611 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qnot_an_instance_of_class);
    list_constant_612 = STATIC_CONS(Qab_class,list_constant_31);
    Qdesired_class = STATIC_SYMBOL("DESIRED-CLASS",AB_package);
    list_constant_613 = STATIC_LIST((SI_Long)2L,Qquote,Qdesired_class);
    list_constant_614 = STATIC_LIST_STAR((SI_Long)6L,
	    Qgesture_evaluation_error,list_constant_611,list_constant_99,
	    list_constant_612,list_constant_613,list_constant_15);
    list_constant_616 = STATIC_LIST((SI_Long)2L,Qt,list_constant_614);
    list_constant_618 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_615,
	    list_constant_616);
    list_constant_621 = STATIC_LIST((SI_Long)2L,list_constant_617,
	    list_constant_618);
    Qnot_tw_item = STATIC_SYMBOL("NOT-TW-ITEM",AB_package);
    list_constant_619 = STATIC_LIST((SI_Long)2L,Qquote,Qnot_tw_item);
    list_constant_620 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_619,list_constant_572);
    list_constant_622 = STATIC_LIST((SI_Long)2L,Qt,list_constant_620);
    list_constant_624 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_621,
	    list_constant_622);
    list_constant_626 = STATIC_LIST((SI_Long)3L,list_constant_567,
	    list_constant_623,list_constant_624);
    mutate_global_property(Qvalue2frame,LIST_3(list_constant_625,
	    FIX((SI_Long)68L),list_constant_626),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2frame,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2datum = STATIC_SYMBOL("VALUE2DATUM",AB_package);
    Qnot_a_value = STATIC_SYMBOL("NOT-A-VALUE",AB_package);
    list_constant_627 = STATIC_LIST((SI_Long)2L,Qquote,Qnot_a_value);
    Qthing_that_is_not_a_value = STATIC_SYMBOL("THING-THAT-IS-NOT-A-VALUE",
	    AB_package);
    list_constant_628 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qthing_that_is_not_a_value);
    list_constant_629 = STATIC_LIST_STAR((SI_Long)4L,
	    Qgesture_evaluation_error,list_constant_627,list_constant_628,
	    list_constant_31);
    list_constant_632 = STATIC_LIST((SI_Long)2L,list_constant_617,
	    list_constant_629);
    list_constant_633 = STATIC_CONS(Qvalue,list_constant_561);
    Qvalue_does_not_exist = STATIC_SYMBOL("VALUE-DOES-NOT-EXIST",AB_package);
    list_constant_630 = STATIC_LIST((SI_Long)2L,Qquote,Qvalue_does_not_exist);
    list_constant_631 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_630);
    list_constant_634 = STATIC_LIST((SI_Long)2L,Qt,list_constant_631);
    list_constant_635 = STATIC_LIST((SI_Long)4L,Qcond,list_constant_632,
	    list_constant_633,list_constant_634);
    list_constant_636 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_635);
    mutate_global_property(Qvalue2datum,LIST_3(list_constant_20,
	    FIX((SI_Long)69L),list_constant_636),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2datum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_truth_value = STATIC_SYMBOL("PUSH-TRUTH-VALUE",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    list_constant_637 = STATIC_LIST((SI_Long)2L,Qquote,Qtrue);
    list_constant_638 = STATIC_LIST((SI_Long)3L,Qeq,list_constant_4,
	    list_constant_637);
    list_constant_639 = STATIC_CONS(list_constant_638,list_constant_599);
    list_constant_640 = STATIC_CONS(Qt,list_constant_337);
    list_constant_641 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_639,
	    list_constant_640);
    list_constant_642 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_641);
    list_constant_643 = STATIC_CONS(list_constant_642,Qnil);
    mutate_global_property(Qpush_truth_value,LIST_3(Qnil,FIX((SI_Long)70L),
	    list_constant_643),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_truth_value,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qinvert_truth_value = STATIC_SYMBOL("INVERT-TRUTH-VALUE",AB_package);
    list_constant_644 = STATIC_LIST_STAR((SI_Long)3L,Qeq,
	    Qevaluation_true_value,list_constant_91);
    list_constant_645 = STATIC_CONS(list_constant_644,list_constant_337);
    list_constant_646 = STATIC_CONS(Qt,list_constant_599);
    list_constant_647 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_645,
	    list_constant_646);
    list_constant_648 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_647);
    list_constant_649 = STATIC_CONS(list_constant_648,Qnil);
    mutate_global_property(Qinvert_truth_value,LIST_3(Qnil,
	    FIX((SI_Long)71L),list_constant_649),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qinvert_truth_value,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_symbol = STATIC_SYMBOL("PUSH-SYMBOL",AB_package);
    mutate_global_property(Qpush_symbol,LIST_3(Qnil,FIX((SI_Long)80L),
	    list_constant_379),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_symbol,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_symbol = STATIC_SYMBOL("EQUAL-SYMBOL",AB_package);
    mutate_global_property(Qequal_symbol,LIST_3(Qnil,FIX((SI_Long)81L),
	    list_constant_358),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_symbol,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_text = STATIC_SYMBOL("PUSH-TEXT",AB_package);
    Qcopy_evaluation_text = STATIC_SYMBOL("COPY-EVALUATION-TEXT",AB_package);
    list_constant_650 = STATIC_CONS(Qcopy_evaluation_text,list_constant_15);
    list_constant_651 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_650);
    list_constant_652 = STATIC_CONS(list_constant_651,Qnil);
    mutate_global_property(Qpush_text,LIST_3(Qnil,FIX((SI_Long)90L),
	    list_constant_652),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_text,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_text = STATIC_SYMBOL("EQUAL-TEXT",AB_package);
    Qstring_equalw = STATIC_SYMBOL("STRING-EQUALW",AB_package);
    list_constant_653 = STATIC_CONS(Qstring_equalw,list_constant_363);
    list_constant_654 = STATIC_LIST_STAR((SI_Long)3L,Qab_if,
	    list_constant_653,list_constant_374);
    list_constant_655 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_654);
    list_constant_656 = STATIC_CONS(list_constant_655,Qnil);
    mutate_global_property(Qequal_text,LIST_3(Qnil,FIX((SI_Long)91L),
	    list_constant_656),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_text,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qtw_format_form = STATIC_SYMBOL("TW-FORMAT-FORM",AB_package);
    list_constant_657 = STATIC_CONS(Qarg_count,list_constant_38);
    Qnew_text_string = STATIC_SYMBOL("NEW-TEXT-STRING",AB_package);
    list_constant_658 = STATIC_CONS(Qnew_text_string,list_constant_87);
    list_constant_670 = STATIC_LIST((SI_Long)2L,list_constant_657,
	    list_constant_658);
    Qtwith_output_to_text_string = 
	    STATIC_SYMBOL("TWITH-OUTPUT-TO-TEXT-STRING",AB_package);
    Qthing = STATIC_SYMBOL("THING",AB_package);
    list_constant_659 = STATIC_CONS(Qthing,Qnil);
    list_constant_662 = STATIC_CONS(Qframep,list_constant_659);
    Qcannot_get_text_of_item = STATIC_SYMBOL("CANNOT-GET-TEXT-OF-ITEM",
	    AB_package);
    list_constant_660 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qcannot_get_text_of_item);
    list_constant_661 = STATIC_CONS(Qab_class,list_constant_659);
    list_constant_663 = STATIC_LIST((SI_Long)4L,Qgesture_evaluation_error,
	    list_constant_660,list_constant_99,list_constant_661);
    list_constant_664 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_662,
	    list_constant_663);
    Qwrite_evaluation_value = STATIC_SYMBOL("WRITE-EVALUATION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_value,
	    STATIC_FUNCTION(write_evaluation_value,NIL,TRUE,1,2));
    list_constant_665 = STATIC_LIST_STAR((SI_Long)3L,
	    Qwrite_evaluation_value,Qthing,list_constant_326);
    list_constant_666 = STATIC_LIST((SI_Long)14L,Qab_loop,Qfor,Qi,Qfrom,
	    FIX((SI_Long)0L),Qbelow,Qarg_count,Qas,Qthing,Qnum_eq,
	    list_constant_2,Qdo,list_constant_664,list_constant_665);
    list_constant_667 = STATIC_LIST((SI_Long)2L,
	    Qtwith_output_to_text_string,list_constant_666);
    list_constant_668 = STATIC_LIST((SI_Long)3L,Qsetf,Qnew_text_string,
	    list_constant_667);
    list_constant_669 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    Qnew_text_string);
    list_constant_671 = STATIC_LIST((SI_Long)3L,list_constant_189,
	    list_constant_668,list_constant_669);
    mutate_global_property(Qtw_format_form,LIST_3(list_constant_670,
	    FIX((SI_Long)100L),list_constant_671),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qtw_format_form,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_datum = STATIC_SYMBOL("EQUAL-DATUM",AB_package);
    Qmake_evaluation_boolean_value = 
	    STATIC_SYMBOL("MAKE-EVALUATION-BOOLEAN-VALUE",AB_package);
    Qevaluation_value_eq = STATIC_SYMBOL("EVALUATION-VALUE-=",AB_package);
    list_constant_672 = STATIC_CONS(Qevaluation_value_eq,list_constant_363);
    list_constant_673 = STATIC_LIST((SI_Long)2L,
	    Qmake_evaluation_boolean_value,list_constant_672);
    list_constant_674 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_673);
    list_constant_675 = STATIC_CONS(list_constant_674,Qnil);
    mutate_global_property(Qequal_datum,LIST_3(Qnil,FIX((SI_Long)101L),
	    list_constant_675),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_datum,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_thread_state = STATIC_SYMBOL("PUSH-THREAD-STATE",AB_package);
    Qnew_pc = STATIC_SYMBOL("NEW-PC",AB_package);
    list_constant_676 = STATIC_CONS(Qnew_pc,list_constant_38);
    list_constant_677 = STATIC_CONS(list_constant_676,Qnil);
    mutate_global_property(Qpush_thread_state,LIST_3(list_constant_677,
	    FIX((SI_Long)102L),Qnil),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_thread_state,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qtype_test = STATIC_SYMBOL("TYPE-TEST",AB_package);
    list_constant_678 = STATIC_CONS(Qthing,list_constant_38);
    Qtype_specification = STATIC_SYMBOL("TYPE-SPECIFICATION",AB_package);
    list_constant_679 = STATIC_CONS(Qtype_specification,list_constant_87);
    list_constant_687 = STATIC_LIST((SI_Long)2L,list_constant_678,
	    list_constant_679);
    list_constant_684 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qthing,
	    list_constant_91);
    list_constant_685 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qtype_specification,list_constant_15);
    list_constant_680 = STATIC_LIST((SI_Long)3L,Qtype_specification_type_p,
	    Qthing,Qtype_specification);
    list_constant_682 = STATIC_LIST((SI_Long)2L,list_constant_680,
	    list_constant_338);
    list_constant_681 = STATIC_CONS(list_constant_339,Qnil);
    list_constant_683 = STATIC_CONS(Qt,list_constant_681);
    list_constant_686 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_682,
	    list_constant_683);
    list_constant_688 = STATIC_LIST((SI_Long)3L,list_constant_684,
	    list_constant_685,list_constant_686);
    mutate_global_property(Qtype_test,LIST_3(list_constant_687,
	    FIX((SI_Long)103L),list_constant_688),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qtype_test,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qclass_test = STATIC_SYMBOL("CLASS-TEST",AB_package);
    list_constant_689 = STATIC_CONS(Qab_class,list_constant_87);
    list_constant_697 = STATIC_LIST((SI_Long)2L,list_constant_678,
	    list_constant_689);
    list_constant_695 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qab_class,
	    list_constant_91);
    list_constant_690 = STATIC_LIST((SI_Long)3L,Qframe_of_class_p,Qthing,
	    Qab_class);
    list_constant_691 = STATIC_LIST((SI_Long)3L,Qand,list_constant_662,
	    list_constant_690);
    list_constant_692 = STATIC_CONS(list_constant_338,Qnil);
    list_constant_693 = STATIC_CONS(list_constant_691,list_constant_692);
    list_constant_694 = STATIC_CONS(list_constant_683,Qnil);
    list_constant_696 = STATIC_LIST_STAR((SI_Long)3L,Qcond,
	    list_constant_693,list_constant_694);
    list_constant_698 = STATIC_LIST((SI_Long)3L,list_constant_695,
	    list_constant_684,list_constant_696);
    mutate_global_property(Qclass_test,LIST_3(list_constant_697,
	    FIX((SI_Long)104L),list_constant_698),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qclass_test,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2type = STATIC_SYMBOL("VALUE2TYPE",AB_package);
    list_constant_699 = STATIC_CONS(Qgesture_push,list_constant_659);
    list_constant_706 = STATIC_LIST((SI_Long)2L,list_constant_680,
	    list_constant_699);
    Qtype_mismatch = STATIC_SYMBOL("TYPE-MISMATCH",AB_package);
    list_constant_701 = STATIC_LIST((SI_Long)2L,Qquote,Qtype_mismatch);
    list_constant_702 = STATIC_CONS(Qquote,list_constant_659);
    Qdesired_type = STATIC_SYMBOL("DESIRED-TYPE",AB_package);
    list_constant_703 = STATIC_LIST((SI_Long)2L,Qquote,Qdesired_type);
    list_constant_700 = STATIC_CONS(Qtype_specification,Qnil);
    list_constant_704 = STATIC_LIST_STAR((SI_Long)3L,Qtformat_text_string,
	    string_constant_8,list_constant_700);
    list_constant_705 = STATIC_LIST((SI_Long)6L,Qgesture_evaluation_error,
	    list_constant_701,list_constant_702,Qthing,list_constant_703,
	    list_constant_704);
    list_constant_707 = STATIC_LIST((SI_Long)2L,Qt,list_constant_705);
    list_constant_708 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_706,
	    list_constant_707);
    list_constant_709 = STATIC_LIST((SI_Long)3L,list_constant_684,
	    list_constant_685,list_constant_708);
    mutate_global_property(Qvalue2type,LIST_3(list_constant_687,
	    FIX((SI_Long)105L),list_constant_709),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2type,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qbitwise_or = STATIC_SYMBOL("BITWISE-OR",AB_package);
    Qlogiorf = STATIC_SYMBOL("LOGIORF",AB_package);
    list_constant_710 = STATIC_CONS(Qlogiorf,list_constant_363);
    list_constant_711 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_710);
    list_constant_712 = STATIC_CONS(list_constant_711,Qnil);
    mutate_global_property(Qbitwise_or,LIST_3(Qnil,FIX((SI_Long)106L),
	    list_constant_712),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qbitwise_or,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qbitwise_and = STATIC_SYMBOL("BITWISE-AND",AB_package);
    Qlogandf = STATIC_SYMBOL("LOGANDF",AB_package);
    list_constant_713 = STATIC_CONS(Qlogandf,list_constant_363);
    list_constant_714 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_713);
    list_constant_715 = STATIC_CONS(list_constant_714,Qnil);
    mutate_global_property(Qbitwise_and,LIST_3(Qnil,FIX((SI_Long)107L),
	    list_constant_715),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qbitwise_and,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qget_class = STATIC_SYMBOL("GET-CLASS",AB_package);
    Qclass_operator_is_not_yet_implemented = 
	    STATIC_SYMBOL("CLASS-OPERATOR-IS-NOT-YET-IMPLEMENTED",AB_package);
    list_constant_716 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qclass_operator_is_not_yet_implemented);
    list_constant_717 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_716);
    list_constant_718 = STATIC_CONS(list_constant_717,Qnil);
    mutate_global_property(Qget_class,LIST_3(Qnil,FIX((SI_Long)108L),
	    list_constant_718),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qget_class,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qnew_class_instance = STATIC_SYMBOL("NEW-CLASS-INSTANCE",AB_package);
    Qnew_class_instance_is_not_yet_implemented = 
	    STATIC_SYMBOL("NEW-CLASS-INSTANCE-IS-NOT-YET-IMPLEMENTED",
	    AB_package);
    list_constant_719 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qnew_class_instance_is_not_yet_implemented);
    list_constant_720 = STATIC_LIST((SI_Long)2L,Qgesture_evaluation_error,
	    list_constant_719);
    list_constant_721 = STATIC_CONS(list_constant_720,Qnil);
    mutate_global_property(Qnew_class_instance,LIST_3(Qnil,
	    FIX((SI_Long)109L),list_constant_721),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qnew_class_instance,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsequence_length = STATIC_SYMBOL("SEQUENCE-LENGTH",AB_package);
    list_constant_722 = STATIC_CONS(Qsequence,list_constant_38);
    list_constant_726 = STATIC_CONS(list_constant_722,Qnil);
    list_constant_724 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qsequence,
	    list_constant_91);
    Qevaluation_sequence_length = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-LENGTH",AB_package);
    list_constant_723 = STATIC_LIST((SI_Long)2L,
	    Qevaluation_sequence_length,Qsequence);
    list_constant_725 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_723);
    list_constant_727 = STATIC_LIST((SI_Long)2L,list_constant_724,
	    list_constant_725);
    mutate_global_property(Qsequence_length,LIST_3(list_constant_726,
	    FIX((SI_Long)110L),list_constant_727),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsequence_length,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qnth_sequence_element = STATIC_SYMBOL("NTH-SEQUENCE-ELEMENT",AB_package);
    list_constant_728 = STATIC_CONS(Qlength,list_constant_87);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    list_constant_729 = STATIC_CONS(Qindex,list_constant_195);
    list_constant_745 = STATIC_LIST((SI_Long)3L,list_constant_722,
	    list_constant_728,list_constant_729);
    list_constant_742 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qindex,
	    list_constant_91);
    list_constant_730 = STATIC_CONS(list_constant_723,Qnil);
    list_constant_743 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qlength,
	    list_constant_730);
    list_constant_734 = STATIC_LIST((SI_Long)4L,Qlt_f,FIX((SI_Long)-1L),
	    Qindex,Qlength);
    Qevaluation_sequence_aref = STATIC_SYMBOL("EVALUATION-SEQUENCE-AREF",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_aref,
	    STATIC_FUNCTION(evaluation_sequence_aref,NIL,FALSE,2,2));
    list_constant_731 = STATIC_CONS(Qindex,Qnil);
    list_constant_732 = STATIC_LIST_STAR((SI_Long)3L,
	    Qevaluation_sequence_aref,Qsequence,list_constant_731);
    list_constant_733 = STATIC_LIST((SI_Long)2L,Qcopy_if_evaluation_value,
	    list_constant_732);
    list_constant_735 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_733);
    list_constant_740 = STATIC_LIST((SI_Long)2L,list_constant_734,
	    list_constant_735);
    Qsequence_index_out_of_range = 
	    STATIC_SYMBOL("SEQUENCE-INDEX-OUT-OF-RANGE",AB_package);
    list_constant_736 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qsequence_index_out_of_range);
    Qlength_of_sequence = STATIC_SYMBOL("LENGTH-OF-SEQUENCE",AB_package);
    list_constant_737 = STATIC_LIST((SI_Long)2L,Qquote,Qlength_of_sequence);
    list_constant_738 = STATIC_CONS(Qquote,list_constant_731);
    list_constant_739 = STATIC_LIST_STAR((SI_Long)6L,
	    Qgesture_evaluation_error,list_constant_736,list_constant_737,
	    Qlength,list_constant_738,list_constant_731);
    list_constant_741 = STATIC_LIST((SI_Long)2L,Qt,list_constant_739);
    list_constant_744 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_740,
	    list_constant_741);
    list_constant_746 = STATIC_LIST((SI_Long)4L,list_constant_742,
	    list_constant_724,list_constant_743,list_constant_744);
    mutate_global_property(Qnth_sequence_element,LIST_3(list_constant_745,
	    FIX((SI_Long)111L),list_constant_746),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qnth_sequence_element,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qset_nth_sequence_element = STATIC_SYMBOL("SET-NTH-SEQUENCE-ELEMENT",
	    AB_package);
    list_constant_747 = STATIC_CONS(Qindex,list_constant_87);
    list_constant_748 = STATIC_CONS(Qnew_value,list_constant_195);
    Qregister_4 = STATIC_SYMBOL("REGISTER-4",AB_package);
    list_constant_749 = STATIC_LIST((SI_Long)2L,Qlength,Qregister_4);
    list_constant_769 = STATIC_LIST((SI_Long)4L,list_constant_722,
	    list_constant_747,list_constant_748,list_constant_749);
    Qallocate_new_evaluation_sequence_copy = 
	    STATIC_SYMBOL("ALLOCATE-NEW-EVALUATION-SEQUENCE-COPY",AB_package);
    list_constant_750 = STATIC_CONS(Qsequence,Qnil);
    list_constant_751 = STATIC_CONS(Qallocate_new_evaluation_sequence_copy,
	    list_constant_750);
    list_constant_763 = STATIC_LIST((SI_Long)3L,Qsetf,Qsequence,
	    list_constant_751);
    Qheld_vector = STATIC_SYMBOL("HELD-VECTOR",AB_package);
    Qevaluation_sequence_value = STATIC_SYMBOL("EVALUATION-SEQUENCE-VALUE",
	    AB_package);
    list_constant_759 = STATIC_CONS(Qevaluation_sequence_value,
	    list_constant_750);
    Qnew_element_index = STATIC_SYMBOL("NEW-ELEMENT-INDEX",AB_package);
    Qevaluation_sequence_first_element_index = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-FIRST-ELEMENT-INDEX",
	    AB_package);
    list_constant_752 = 
	    STATIC_CONS(Qevaluation_sequence_first_element_index,Qnil);
    list_constant_760 = STATIC_LIST((SI_Long)3L,Qplus_f,Qindex,
	    list_constant_752);
    Qmanaged_array_length = STATIC_SYMBOL("MANAGED-ARRAY-LENGTH",AB_package);
    list_constant_761 = STATIC_LIST((SI_Long)2L,Qmanaged_array_length,
	    Qheld_vector);
    Qmanaged_svref = STATIC_SYMBOL("MANAGED-SVREF",AB_package);
    list_constant_753 = STATIC_CONS(Qi,Qnil);
    list_constant_754 = STATIC_LIST_STAR((SI_Long)3L,Qmanaged_svref,
	    Qheld_vector,list_constant_753);
    list_constant_755 = STATIC_LIST((SI_Long)3L,Qeq_f,Qi,Qnew_element_index);
    list_constant_756 = STATIC_CONS(Qcopy_if_evaluation_value,
	    list_constant_450);
    list_constant_757 = STATIC_LIST((SI_Long)2L,Qcopy_if_evaluation_value,
	    list_constant_754);
    list_constant_758 = STATIC_LIST((SI_Long)4L,Qab_if,list_constant_755,
	    list_constant_756,list_constant_757);
    list_constant_762 = STATIC_LIST((SI_Long)3L,Qsetf,list_constant_754,
	    list_constant_758);
    list_constant_764 = STATIC_LIST((SI_Long)17L,Qab_loop,Qwith,
	    Qheld_vector,Qnum_eq,list_constant_759,Qwith,
	    Qnew_element_index,Qnum_eq,list_constant_760,Qfor,Qi,Qfrom,
	    list_constant_752,Qbelow,list_constant_761,Qdo,list_constant_762);
    list_constant_765 = STATIC_CONS(Qgesture_push,list_constant_750);
    list_constant_766 = STATIC_LIST((SI_Long)4L,list_constant_734,
	    list_constant_763,list_constant_764,list_constant_765);
    list_constant_767 = STATIC_CONS(list_constant_741,Qnil);
    list_constant_768 = STATIC_LIST_STAR((SI_Long)3L,Qcond,
	    list_constant_766,list_constant_767);
    list_constant_770 = STATIC_LIST((SI_Long)5L,list_constant_507,
	    list_constant_742,list_constant_724,list_constant_743,
	    list_constant_768);
    mutate_global_property(Qset_nth_sequence_element,
	    LIST_3(list_constant_769,FIX((SI_Long)112L),list_constant_770),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qset_nth_sequence_element,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsequence_push = STATIC_SYMBOL("SEQUENCE-PUSH",AB_package);
    list_constant_778 = STATIC_LIST((SI_Long)2L,list_constant_722,
	    list_constant_429);
    list_constant_771 = STATIC_LIST((SI_Long)2L,Qquote,Qfirst);
    list_constant_773 = STATIC_LIST((SI_Long)3L,Qeq,list_constant_4,
	    list_constant_771);
    Qevaluation_sequence_insert_at_beginning = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-INSERT-AT-BEGINNING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_insert_at_beginning,
	    STATIC_FUNCTION(evaluation_sequence_insert_at_beginning,NIL,
	    FALSE,2,2));
    list_constant_772 = STATIC_CONS(Qsequence,list_constant_450);
    list_constant_774 = 
	    STATIC_CONS(Qevaluation_sequence_insert_at_beginning,
	    list_constant_772);
    Qevaluation_sequence_insert_at_end = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-INSERT-AT-END",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_insert_at_end,
	    STATIC_FUNCTION(evaluation_sequence_insert_at_end,NIL,FALSE,2,2));
    list_constant_775 = STATIC_CONS(Qevaluation_sequence_insert_at_end,
	    list_constant_772);
    list_constant_776 = STATIC_LIST((SI_Long)4L,Qab_if,list_constant_773,
	    list_constant_774,list_constant_775);
    list_constant_777 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_776);
    list_constant_779 = STATIC_LIST((SI_Long)3L,list_constant_507,
	    list_constant_724,list_constant_777);
    mutate_global_property(Qsequence_push,LIST_3(list_constant_778,
	    FIX((SI_Long)113L),list_constant_779),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsequence_push,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsequence_remove = STATIC_SYMBOL("SEQUENCE-REMOVE",AB_package);
    Qnew_sequence = STATIC_SYMBOL("NEW-SEQUENCE",AB_package);
    list_constant_780 = STATIC_CONS(Qnew_sequence,list_constant_195);
    list_constant_790 = STATIC_LIST((SI_Long)3L,list_constant_722,
	    list_constant_747,list_constant_780);
    Qevaluation_sequence_remove_element_at_index = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-REMOVE-ELEMENT-AT-INDEX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_remove_element_at_index,
	    STATIC_FUNCTION(evaluation_sequence_remove_element_at_index,
	    NIL,FALSE,2,2));
    list_constant_781 = STATIC_CONS(Qsequence,list_constant_731);
    list_constant_782 = 
	    STATIC_CONS(Qevaluation_sequence_remove_element_at_index,
	    list_constant_781);
    list_constant_788 = STATIC_LIST((SI_Long)3L,Qsetf,Qnew_sequence,
	    list_constant_782);
    list_constant_786 = STATIC_LIST((SI_Long)2L,Qgesture_push,Qnew_sequence);
    Qsequence_remove_index_out_of_range = 
	    STATIC_SYMBOL("SEQUENCE-REMOVE-INDEX-OUT-OF-RANGE",AB_package);
    list_constant_783 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qsequence_remove_index_out_of_range);
    list_constant_784 = STATIC_CONS(Qquote,list_constant_750);
    list_constant_785 = STATIC_CONS(list_constant_738,list_constant_731);
    list_constant_787 = STATIC_LIST_STAR((SI_Long)5L,
	    Qgesture_evaluation_error,list_constant_783,list_constant_784,
	    Qsequence,list_constant_785);
    list_constant_789 = STATIC_LIST((SI_Long)4L,Qab_if,Qnew_sequence,
	    list_constant_786,list_constant_787);
    list_constant_791 = STATIC_LIST((SI_Long)4L,list_constant_742,
	    list_constant_724,list_constant_788,list_constant_789);
    mutate_global_property(Qsequence_remove,LIST_3(list_constant_790,
	    FIX((SI_Long)114L),list_constant_791),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsequence_remove,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsequence_remove_element = STATIC_SYMBOL("SEQUENCE-REMOVE-ELEMENT",
	    AB_package);
    Qvalue_to_match = STATIC_SYMBOL("VALUE-TO-MATCH",AB_package);
    list_constant_792 = STATIC_CONS(Qvalue_to_match,list_constant_87);
    list_constant_793 = STATIC_CONS(list_constant_780,Qnil);
    list_constant_797 = STATIC_LIST_STAR((SI_Long)3L,list_constant_722,
	    list_constant_792,list_constant_793);
    list_constant_795 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qvalue_to_match,
	    list_constant_91);
    Qevaluation_sequence_without_elements = 
	    STATIC_SYMBOL("EVALUATION-SEQUENCE-WITHOUT-ELEMENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_sequence_without_elements,
	    STATIC_FUNCTION(evaluation_sequence_without_elements,NIL,FALSE,
	    3,3));
    list_constant_794 = STATIC_LIST_STAR((SI_Long)4L,
	    Qevaluation_sequence_without_elements,Qsequence,
	    Qvalue_to_match,list_constant_326);
    list_constant_796 = STATIC_LIST((SI_Long)3L,Qsetf,Qnew_sequence,
	    list_constant_794);
    list_constant_798 = STATIC_LIST((SI_Long)4L,list_constant_795,
	    list_constant_724,list_constant_796,list_constant_786);
    mutate_global_property(Qsequence_remove_element,
	    LIST_3(list_constant_797,FIX((SI_Long)120L),list_constant_798),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qsequence_remove_element,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qset_structure_slot = STATIC_SYMBOL("SET-STRUCTURE-SLOT",AB_package);
    list_constant_799 = STATIC_CONS(Qab_structure,list_constant_38);
    list_constant_807 = STATIC_LIST((SI_Long)3L,list_constant_799,
	    list_constant_513,list_constant_748);
    list_constant_802 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qattribute_name,
	    list_constant_91);
    list_constant_803 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qab_structure,
	    list_constant_91);
    Qobtain_mutable_evaluation_structure_copy = 
	    STATIC_SYMBOL("OBTAIN-MUTABLE-EVALUATION-STRUCTURE-COPY",
	    AB_package);
    list_constant_800 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_801 = 
	    STATIC_CONS(Qobtain_mutable_evaluation_structure_copy,
	    list_constant_800);
    list_constant_804 = STATIC_LIST((SI_Long)3L,Qsetf,Qab_structure,
	    list_constant_801);
    list_constant_805 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    list_constant_521,list_constant_450);
    list_constant_806 = STATIC_CONS(Qgesture_push,list_constant_800);
    list_constant_808 = STATIC_LIST((SI_Long)6L,list_constant_507,
	    list_constant_802,list_constant_803,list_constant_804,
	    list_constant_805,list_constant_806);
    mutate_global_property(Qset_structure_slot,LIST_3(list_constant_807,
	    FIX((SI_Long)115L),list_constant_808),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qset_structure_slot,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qmake_structure = STATIC_SYMBOL("MAKE-STRUCTURE",AB_package);
    Qstruct_length = STATIC_SYMBOL("STRUCT-LENGTH",AB_package);
    list_constant_809 = STATIC_CONS(Qstruct_length,list_constant_38);
    Qeval_list = STATIC_SYMBOL("EVAL-LIST",AB_package);
    list_constant_810 = STATIC_CONS(Qeval_list,list_constant_87);
    list_constant_831 = STATIC_LIST((SI_Long)2L,list_constant_809,
	    list_constant_810);
    list_constant_826 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qstruct_length,
	    list_constant_91);
    list_constant_827 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,Qeval_list,
	    list_constant_95);
    string_constant_14 = STATIC_STRING("structure-val i=~s value=~s~%");
    list_constant_822 = STATIC_LIST_STAR((SI_Long)5L,Qtw_trace,
	    FIX((SI_Long)2L),string_constant_14,Qi,list_constant_31);
    Qsl_eq_f = STATIC_SYMBOL("/=F",AB_package);
    list_constant_811 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_812 = STATIC_LIST_STAR((SI_Long)3L,Qlogandf,Qi,
	    list_constant_811);
    list_constant_813 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_815 = STATIC_LIST_STAR((SI_Long)3L,Qsl_eq_f,
	    list_constant_812,list_constant_813);
    list_constant_814 = STATIC_CONS(list_constant_559,Qnil);
    list_constant_816 = STATIC_CONS(Qnot,list_constant_814);
    list_constant_819 = STATIC_LIST((SI_Long)3L,Qand,list_constant_815,
	    list_constant_816);
    Qstructure_attribute_name_not_symbol = 
	    STATIC_SYMBOL("STRUCTURE-ATTRIBUTE-NAME-NOT-SYMBOL",AB_package);
    list_constant_817 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qstructure_attribute_name_not_symbol);
    Qwould_be_attribute_name = STATIC_SYMBOL("WOULD-BE-ATTRIBUTE-NAME",
	    AB_package);
    list_constant_818 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qwould_be_attribute_name);
    list_constant_820 = STATIC_LIST_STAR((SI_Long)4L,
	    Qgesture_evaluation_error,list_constant_817,list_constant_818,
	    list_constant_31);
    list_constant_823 = STATIC_LIST((SI_Long)3L,Qwhen,list_constant_819,
	    list_constant_820);
    Qeval_push = STATIC_SYMBOL("EVAL-PUSH",AB_package);
    list_constant_821 = STATIC_CONS(Qeval_list,Qnil);
    list_constant_824 = STATIC_LIST_STAR((SI_Long)3L,Qeval_push,Qvalue,
	    list_constant_821);
    list_constant_828 = STATIC_LIST((SI_Long)15L,Qab_loop,Qfor,Qi,Qfrom,
	    FIX((SI_Long)0L),Qbelow,Qstruct_length,Qas,Qvalue,Qnum_eq,
	    list_constant_2,Qdo,list_constant_822,list_constant_823,
	    list_constant_824);
    string_constant_15 = STATIC_STRING("structure-args =~s~%");
    list_constant_829 = STATIC_LIST_STAR((SI_Long)4L,Qtw_trace,
	    FIX((SI_Long)2L),string_constant_15,list_constant_821);
    Qallocate_evaluation_structure = 
	    STATIC_SYMBOL("ALLOCATE-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_evaluation_structure,
	    STATIC_FUNCTION(allocate_evaluation_structure,NIL,FALSE,1,1));
    list_constant_825 = STATIC_CONS(Qallocate_evaluation_structure,
	    list_constant_821);
    list_constant_830 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_825);
    list_constant_832 = STATIC_LIST((SI_Long)5L,list_constant_826,
	    list_constant_827,list_constant_828,list_constant_829,
	    list_constant_830);
    mutate_global_property(Qmake_structure,LIST_3(list_constant_831,
	    FIX((SI_Long)116L),list_constant_832),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qmake_structure,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qab_make_sequence = STATIC_SYMBOL("MAKE-SEQUENCE",AB_package);
    list_constant_833 = STATIC_CONS(Qsequence_length,list_constant_38);
    list_constant_834 = STATIC_CONS(list_constant_810,Qnil);
    list_constant_841 = STATIC_CONS(list_constant_833,list_constant_834);
    list_constant_837 = STATIC_LIST_STAR((SI_Long)3L,Qsetf,
	    Qsequence_length,list_constant_91);
    list_constant_835 = STATIC_CONS(list_constant_824,Qnil);
    list_constant_838 = STATIC_LIST_STAR((SI_Long)13L,Qab_loop,Qfor,Qi,
	    Qfrom,FIX((SI_Long)0L),Qbelow,Qsequence_length,Qas,Qvalue,
	    Qnum_eq,list_constant_2,Qdo,list_constant_835);
    string_constant_16 = STATIC_STRING("seq-args=~s~%");
    list_constant_839 = STATIC_LIST_STAR((SI_Long)4L,Qtw_trace,
	    FIX((SI_Long)2L),string_constant_16,list_constant_821);
    Qallocate_evaluation_sequence = 
	    STATIC_SYMBOL("ALLOCATE-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qallocate_evaluation_sequence,
	    STATIC_FUNCTION(allocate_evaluation_sequence,NIL,FALSE,1,1));
    list_constant_836 = STATIC_CONS(Qallocate_evaluation_sequence,
	    list_constant_821);
    list_constant_840 = STATIC_LIST((SI_Long)2L,Qgesture_push,
	    list_constant_836);
    list_constant_842 = STATIC_LIST((SI_Long)5L,list_constant_837,
	    list_constant_827,list_constant_838,list_constant_839,
	    list_constant_840);
    mutate_global_property(Qab_make_sequence,LIST_3(list_constant_841,
	    FIX((SI_Long)117L),list_constant_842),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qab_make_sequence,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2sequence = STATIC_SYMBOL("VALUE2SEQUENCE",AB_package);
    Qevaluation_sequence_p = STATIC_SYMBOL("EVALUATION-SEQUENCE-P",AB_package);
    list_constant_843 = STATIC_CONS(Qevaluation_sequence_p,list_constant_31);
    list_constant_846 = STATIC_CONS(list_constant_843,list_constant_561);
    Qvalue_is_not_a_sequence = STATIC_SYMBOL("VALUE-IS-NOT-A-SEQUENCE",
	    AB_package);
    list_constant_844 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_is_not_a_sequence);
    list_constant_845 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_844,list_constant_572);
    list_constant_847 = STATIC_LIST((SI_Long)2L,Qt,list_constant_845);
    list_constant_848 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_846,
	    list_constant_847);
    list_constant_849 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_848);
    mutate_global_property(Qvalue2sequence,LIST_3(list_constant_20,
	    FIX((SI_Long)118L),list_constant_849),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2sequence,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qvalue2struct = STATIC_SYMBOL("VALUE2STRUCT",AB_package);
    list_constant_850 = STATIC_CONS(Qevaluation_structure_p,list_constant_31);
    list_constant_853 = STATIC_CONS(list_constant_850,list_constant_561);
    Qvalue_is_not_a_structure = STATIC_SYMBOL("VALUE-IS-NOT-A-STRUCTURE",
	    AB_package);
    list_constant_851 = STATIC_LIST((SI_Long)2L,Qquote,
	    Qvalue_is_not_a_structure);
    list_constant_852 = STATIC_LIST_STAR((SI_Long)3L,
	    Qgesture_evaluation_error,list_constant_851,list_constant_572);
    list_constant_854 = STATIC_LIST((SI_Long)2L,Qt,list_constant_852);
    list_constant_855 = STATIC_LIST((SI_Long)3L,Qcond,list_constant_853,
	    list_constant_854);
    list_constant_856 = STATIC_LIST((SI_Long)2L,list_constant_567,
	    list_constant_855);
    mutate_global_property(Qvalue2struct,LIST_3(list_constant_20,
	    FIX((SI_Long)119L),list_constant_856),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qvalue2struct,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qadd_float = STATIC_SYMBOL("ADD-FLOAT",AB_package);
    mutate_global_property(Qadd_float,LIST_3(Qnil,FIX((SI_Long)130L),
	    list_constant_366),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qadd_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsubtract_float = STATIC_SYMBOL("SUBTRACT-FLOAT",AB_package);
    mutate_global_property(Qsubtract_float,LIST_3(Qnil,FIX((SI_Long)131L),
	    list_constant_369),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qsubtract_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qmultiply_float = STATIC_SYMBOL("MULTIPLY-FLOAT",AB_package);
    mutate_global_property(Qmultiply_float,LIST_3(Qnil,FIX((SI_Long)132L),
	    list_constant_372),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qmultiply_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qequal_float = STATIC_SYMBOL("EQUAL-FLOAT",AB_package);
    mutate_global_property(Qequal_float,LIST_3(Qnil,FIX((SI_Long)133L),
	    list_constant_377),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qequal_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_float = STATIC_SYMBOL("PUSH-FLOAT",AB_package);
    mutate_global_property(Qpush_float,LIST_3(Qnil,FIX((SI_Long)134L),
	    list_constant_379),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qint2float = STATIC_SYMBOL("INT2FLOAT",AB_package);
    list_constant_857 = STATIC_CONS(Qgesture_push,list_constant_91);
    list_constant_858 = STATIC_CONS(list_constant_857,Qnil);
    mutate_global_property(Qint2float,LIST_3(Qnil,FIX((SI_Long)135L),
	    list_constant_858),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qint2float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qnegate_float = STATIC_SYMBOL("NEGATE-FLOAT",AB_package);
    mutate_global_property(Qnegate_float,LIST_3(Qnil,FIX((SI_Long)137L),
	    list_constant_388),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qnegate_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_float = STATIC_SYMBOL("GREATER-THAN-FLOAT",AB_package);
    mutate_global_property(Qgreater_than_float,LIST_3(list_constant_396,
	    FIX((SI_Long)138L),list_constant_397),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qgreater_than_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_float = STATIC_SYMBOL("LESS-THAN-FLOAT",AB_package);
    mutate_global_property(Qless_than_float,LIST_3(list_constant_396,
	    FIX((SI_Long)139L),list_constant_402),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qless_than_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qgreater_than_equal_float = STATIC_SYMBOL("GREATER-THAN-EQUAL-FLOAT",
	    AB_package);
    mutate_global_property(Qgreater_than_equal_float,
	    LIST_3(list_constant_396,FIX((SI_Long)140L),list_constant_406),
	    Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qgreater_than_equal_float,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qless_than_equal_float = STATIC_SYMBOL("LESS-THAN-EQUAL-FLOAT",AB_package);
    mutate_global_property(Qless_than_equal_float,LIST_3(list_constant_396,
	    FIX((SI_Long)141L),list_constant_410),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,
	    Qless_than_equal_float,All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qquotient_float = STATIC_SYMBOL("QUOTIENT-FLOAT",AB_package);
    mutate_global_property(Qquotient_float,LIST_3(list_constant_417,
	    FIX((SI_Long)142L),list_constant_418),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qquotient_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qremainder_float = STATIC_SYMBOL("REMAINDER-FLOAT",AB_package);
    mutate_global_property(Qremainder_float,LIST_3(list_constant_417,
	    FIX((SI_Long)143L),list_constant_422),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qremainder_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qdivide_float = STATIC_SYMBOL("DIVIDE-FLOAT",AB_package);
    mutate_global_property(Qdivide_float,LIST_3(list_constant_417,
	    FIX((SI_Long)144L),list_constant_422),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qdivide_float,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qpush_long = STATIC_SYMBOL("PUSH-LONG",AB_package);
    mutate_global_property(Qpush_long,LIST_3(Qnil,FIX((SI_Long)135L),
	    list_constant_379),Qgesture_instruction);
    all_gesture_instruction_names_new_value = adjoin(2,Qpush_long,
	    All_gesture_instruction_names);
    All_gesture_instruction_names = all_gesture_instruction_names_new_value;
    Qsymbol_constant = STATIC_SYMBOL("SYMBOL-CONSTANT",AB_package);
    Qstruct = STATIC_SYMBOL("STRUCT",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    if (Current_gesture_code_sequences == UNBOUND)
	Current_gesture_code_sequences = Nil;
    if (Current_gesture_code_sequence == UNBOUND)
	Current_gesture_code_sequence = Nil;
    if (Current_gesture_sequence_index == UNBOUND)
	Current_gesture_sequence_index = FIX((SI_Long)0L);
    if (Current_gesture_label_index == UNBOUND)
	Current_gesture_label_index = FIX((SI_Long)0L);
    if (Gesture_source_stack == UNBOUND)
	Gesture_source_stack = Nil;
    Qmake_struct = STATIC_SYMBOL("MAKE-STRUCT",AB_package);
    list_constant_859 = STATIC_CONS(Qmake_struct,Qmake_structure);
    Qset_struct_slot = STATIC_SYMBOL("SET-STRUCT-SLOT",AB_package);
    list_constant_860 = STATIC_CONS(Qset_struct_slot,Qset_structure_slot);
    list_constant_861 = STATIC_LIST((SI_Long)2L,list_constant_859,
	    list_constant_860);
    Obsolete_gesture_instruction_map = list_constant_861;
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qlocal_assignment = STATIC_SYMBOL("LOCAL-ASSIGNMENT",AB_package);
    Qchange_slot = STATIC_SYMBOL("CHANGE-SLOT",AB_package);
    Qchange_array_length = STATIC_SYMBOL("CHANGE-ARRAY-LENGTH",AB_package);
    Qfor_loop_integer = STATIC_SYMBOL("FOR-LOOP-INTEGER",AB_package);
    Qgesture_call = STATIC_SYMBOL("GESTURE-CALL",AB_package);
    Qgesture_call_next_method = STATIC_SYMBOL("GESTURE-CALL-NEXT-METHOD",
	    AB_package);
    Qcall_g2 = STATIC_SYMBOL("CALL-G2",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qrepeat = STATIC_SYMBOL("REPEAT",AB_package);
    Qexit_if = STATIC_SYMBOL("EXIT-IF",AB_package);
    Qcompound_statement = STATIC_SYMBOL("COMPOUND-STATEMENT",AB_package);
    Qbegin = STATIC_SYMBOL("BEGIN",AB_package);
    Qcompound_statement_with_error_handling = 
	    STATIC_SYMBOL("COMPOUND-STATEMENT-WITH-ERROR-HANDLING",AB_package);
    Qcompound_statement_with_unwind_protection = 
	    STATIC_SYMBOL("COMPOUND-STATEMENT-WITH-UNWIND-PROTECTION",
	    AB_package);
    Qon_error = STATIC_SYMBOL("ON-ERROR",AB_package);
    Qon_exit = STATIC_SYMBOL("ON-EXIT",AB_package);
    Qget_slot_or_no_item = STATIC_SYMBOL("GET-SLOT-OR-NO-ITEM",AB_package);
    Qarray_length = STATIC_SYMBOL("ARRAY-LENGTH",AB_package);
    Qif_expression = STATIC_SYMBOL("IF-EXPRESSION",AB_package);
    Qunevaluated_constant = STATIC_SYMBOL("UNEVALUATED-CONSTANT",AB_package);
    Qfetch_local = STATIC_SYMBOL("FETCH-LOCAL",AB_package);
    Qfetch_local_or_no_item = STATIC_SYMBOL("FETCH-LOCAL-OR-NO-ITEM",
	    AB_package);
    Qinteger_constant = STATIC_SYMBOL("INTEGER-CONSTANT",AB_package);
    Qtruth_value_constant = STATIC_SYMBOL("TRUTH-VALUE-CONSTANT",AB_package);
    Qtext_constant = STATIC_SYMBOL("TEXT-CONSTANT",AB_package);
    Qfloat_constant = STATIC_SYMBOL("FLOAT-CONSTANT",AB_package);
    Qlong_constant = STATIC_SYMBOL("LONG-CONSTANT",AB_package);
    list_constant = STATIC_LIST((SI_Long)8L,Qfetch_local,
	    Qfetch_local_or_no_item,Qinteger_constant,
	    Qtruth_value_constant,Qsymbol_constant,Qtext_constant,
	    Qfloat_constant,Qlong_constant);
    string_constant = 
	    string_append2(STATIC_STRING("The value of (CADR NODE) (~s), is not one of (FETCH-LOCAL FETCH-LOCAL-OR-NO-ITEM INTEGER-CONSTANT FLOAT-CONSTANT LONG-CONSTANT SYMBOL-CONSTANT TEXT-CONSTANT TRUTH-VALUE-CONSTA"),
	    STATIC_STRING("NT)."));
}
