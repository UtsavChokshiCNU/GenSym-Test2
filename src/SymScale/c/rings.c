/* rings.c
 * Input file:  rings.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rings.h"


Object Smallest_ring_buffer_vector_size = UNBOUND;

Object Largest_ring_buffer_vector_size = UNBOUND;

/* RECLAIM-RING-BUFFER-VECTOR */
Object reclaim_ring_buffer_vector(ring_buffer_vector)
    Object ring_buffer_vector;
{
    Object svref_new_value, svref_arg_1;
    SI_Long vector_index, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(127,0);
    if (SIMPLE_VECTOR_P(ring_buffer_vector) && 
	    EQ(ISVREF(ring_buffer_vector,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	vector_index = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(ring_buffer_vector,(SI_Long)1L));
      next_loop:
	if (vector_index >= ab_loop_bind_)
	    goto end_loop;
	svref_new_value = 
		reclaim_managed_number_or_value_function(FIXNUM_LE(ISVREF(ring_buffer_vector,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ring_buffer_vector,vector_index + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(ring_buffer_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L));
	if (FIXNUM_LE(ISVREF(ring_buffer_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = vector_index + IFIX(Managed_array_index_offset);
	    ISVREF(ring_buffer_vector,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(ring_buffer_vector,(vector_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = vector_index & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	vector_index = vector_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	return reclaim_managed_array(ring_buffer_vector);
    }
    else
	return reclaim_managed_float_array(ring_buffer_vector);
}

/* COMPUTE-NEXT-LARGER-SIZE-FOR-RING-BUFFER-VECTORS */
Object compute_next_larger_size_for_ring_buffer_vectors(current_size)
    Object current_size;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(127,1);
    gensymed_symbol = IFIX(Largest_ring_buffer_vector_size);
    gensymed_symbol_1 = IFIX(current_size) < (SI_Long)1000L ? 
	    IFIX(current_size) * (SI_Long)2L : IFIX(current_size) + 
	    (SI_Long)1024L;
    return VALUES_1(FIX(MIN(gensymed_symbol,gensymed_symbol_1)));
}

Object The_type_description_of_ring_buffer_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_ring_buffer_states, Qchain_of_available_ring_buffer_states);

DEFINE_VARIABLE_WITH_SYMBOL(Ring_buffer_state_count, Qring_buffer_state_count);

Object Chain_of_available_ring_buffer_states_vector = UNBOUND;

/* RING-BUFFER-STATE-STRUCTURE-MEMORY-USAGE */
Object ring_buffer_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(127,2);
    temp = Ring_buffer_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RING-BUFFER-STATE-COUNT */
Object outstanding_ring_buffer_state_count()
{
    Object def_structure_ring_buffer_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(127,3);
    gensymed_symbol = IFIX(Ring_buffer_state_count);
    def_structure_ring_buffer_state_variable = 
	    Chain_of_available_ring_buffer_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_ring_buffer_state_variable))
	goto end_loop;
    def_structure_ring_buffer_state_variable = 
	    ISVREF(def_structure_ring_buffer_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RING-BUFFER-STATE-1 */
Object reclaim_ring_buffer_state_1(ring_buffer_state)
    Object ring_buffer_state;
{
    Object temp, svref_arg_2;

    x_note_fn_call(127,4);
    inline_note_reclaim_cons(ring_buffer_state,Nil);
    temp = ISVREF(Chain_of_available_ring_buffer_states_vector,
	    IFIX(Current_thread_index));
    SVREF(ring_buffer_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_ring_buffer_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = ring_buffer_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RING-BUFFER-STATE */
Object reclaim_structure_for_ring_buffer_state(ring_buffer_state)
    Object ring_buffer_state;
{
    x_note_fn_call(127,5);
    return reclaim_ring_buffer_state_1(ring_buffer_state);
}

static Object Qg2_defstruct_structure_name_ring_buffer_state_g2_struct;  /* g2-defstruct-structure-name::ring-buffer-state-g2-struct */

/* MAKE-PERMANENT-RING-BUFFER-STATE-STRUCTURE-INTERNAL */
Object make_permanent_ring_buffer_state_structure_internal()
{
    Object def_structure_ring_buffer_state_variable;
    Object defstruct_g2_ring_buffer_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(127,6);
    def_structure_ring_buffer_state_variable = Nil;
    atomic_incff_symval(Qring_buffer_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_ring_buffer_state_variable = Nil;
	gensymed_symbol = (SI_Long)6L;
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
	defstruct_g2_ring_buffer_state_variable = the_array;
	SVREF(defstruct_g2_ring_buffer_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ring_buffer_state_g2_struct;
	def_structure_ring_buffer_state_variable = 
		defstruct_g2_ring_buffer_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_ring_buffer_state_variable);
}

/* MAKE-RING-BUFFER-STATE-1 */
Object make_ring_buffer_state_1()
{
    Object def_structure_ring_buffer_state_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(127,7);
    def_structure_ring_buffer_state_variable = 
	    ISVREF(Chain_of_available_ring_buffer_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_ring_buffer_state_variable) {
	svref_arg_1 = Chain_of_available_ring_buffer_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_ring_buffer_state_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_ring_buffer_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ring_buffer_state_g2_struct;
    }
    else
	def_structure_ring_buffer_state_variable = 
		make_permanent_ring_buffer_state_structure_internal();
    inline_note_allocate_cons(def_structure_ring_buffer_state_variable,Nil);
    ISVREF(def_structure_ring_buffer_state_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_ring_buffer_state_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_ring_buffer_state_variable,FIX((SI_Long)3L)) = T;
    ISVREF(def_structure_ring_buffer_state_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_ring_buffer_state_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_ring_buffer_state_variable);
}

/* COPY-RING-BUFFER-SHELL-SLOTS */
Object copy_ring_buffer_shell_slots(ring_buffer,new_shell)
    Object ring_buffer, new_shell;
{
    Object svref_new_value;

    x_note_fn_call(127,8);
    svref_new_value = ISVREF(ring_buffer,(SI_Long)1L);
    SVREF(new_shell,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = ISVREF(ring_buffer,(SI_Long)2L);
    SVREF(new_shell,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(ring_buffer,(SI_Long)3L);
    SVREF(new_shell,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = ISVREF(ring_buffer,(SI_Long)4L);
    return VALUES_1(SVREF(new_shell,FIX((SI_Long)4L)) = svref_new_value);
}

/* COPY-RING-BUFFER-VECTOR */
Object copy_ring_buffer_vector(vector_1)
    Object vector_1;
{
    Object length_1, new_vector, value_to_copy, temp, svref_new_value;
    SI_Long index_1, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(127,9);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_float_array_unique_marker))
	return copy_managed_float_array(vector_1);
    else {
	length_1 = ISVREF(vector_1,(SI_Long)1L);
	new_vector = allocate_managed_array(1,length_1);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length_1);
	value_to_copy = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value_to_copy = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(vector_1,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(new_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value_to_copy) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_copy)) == 
		    (SI_Long)1L ? copy_managed_float(value_to_copy) : 
		    value_to_copy;
	    ISVREF(new_vector,svref_arg_2) = temp;
	}
	else {
	    temp = ISVREF(new_vector,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    svref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value_to_copy) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_copy)) == 
		    (SI_Long)1L ? copy_managed_float(value_to_copy) : 
		    value_to_copy;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(new_vector);
	return VALUES_1(Qnil);
    }
}

Object Thrashing_ratio_ring_buffer_length = UNBOUND;

Object The_type_description_of_thrashing_ratio_ring_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_thrashing_ratio_ring_buffers, Qchain_of_available_thrashing_ratio_ring_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Thrashing_ratio_ring_buffer_count, Qthrashing_ratio_ring_buffer_count);

Object Chain_of_available_thrashing_ratio_ring_buffers_vector = UNBOUND;

/* THRASHING-RATIO-RING-BUFFER-STRUCTURE-MEMORY-USAGE */
Object thrashing_ratio_ring_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(127,10);
    temp = Thrashing_ratio_ring_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-THRASHING-RATIO-RING-BUFFER-COUNT */
Object outstanding_thrashing_ratio_ring_buffer_count()
{
    Object def_structure_thrashing_ratio_ring_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(127,11);
    gensymed_symbol = IFIX(Thrashing_ratio_ring_buffer_count);
    def_structure_thrashing_ratio_ring_buffer_variable = 
	    Chain_of_available_thrashing_ratio_ring_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_thrashing_ratio_ring_buffer_variable))
	goto end_loop;
    def_structure_thrashing_ratio_ring_buffer_variable = 
	    ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,
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

/* RECLAIM-THRASHING-RATIO-RING-BUFFER-1 */
Object reclaim_thrashing_ratio_ring_buffer_1(thrashing_ratio_ring_buffer)
    Object thrashing_ratio_ring_buffer;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(127,12);
    inline_note_reclaim_cons(thrashing_ratio_ring_buffer,Nil);
    structure_being_reclaimed = thrashing_ratio_ring_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_ring_buffer_vector(ISVREF(thrashing_ratio_ring_buffer,
	      (SI_Long)6L));
      SVREF(thrashing_ratio_ring_buffer,FIX((SI_Long)6L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_thrashing_ratio_ring_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(thrashing_ratio_ring_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_thrashing_ratio_ring_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = thrashing_ratio_ring_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-THRASHING-RATIO-RING-BUFFER */
Object reclaim_structure_for_thrashing_ratio_ring_buffer(thrashing_ratio_ring_buffer)
    Object thrashing_ratio_ring_buffer;
{
    x_note_fn_call(127,13);
    return reclaim_thrashing_ratio_ring_buffer_1(thrashing_ratio_ring_buffer);
}

static Object Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct;  /* g2-defstruct-structure-name::thrashing-ratio-ring-buffer-g2-struct */

/* MAKE-PERMANENT-THRASHING-RATIO-RING-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_thrashing_ratio_ring_buffer_structure_internal()
{
    Object def_structure_thrashing_ratio_ring_buffer_variable;
    Object defstruct_g2_thrashing_ratio_ring_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(127,14);
    def_structure_thrashing_ratio_ring_buffer_variable = Nil;
    atomic_incff_symval(Qthrashing_ratio_ring_buffer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_thrashing_ratio_ring_buffer_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_thrashing_ratio_ring_buffer_variable = the_array;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_thrashing_ratio_ring_buffer_variable = 
		defstruct_g2_thrashing_ratio_ring_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_thrashing_ratio_ring_buffer_variable);
}

/* MAKE-THRASHING-RATIO-RING-BUFFER-1 */
Object make_thrashing_ratio_ring_buffer_1()
{
    Object def_structure_thrashing_ratio_ring_buffer_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(127,15);
    def_structure_thrashing_ratio_ring_buffer_variable = 
	    ISVREF(Chain_of_available_thrashing_ratio_ring_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_thrashing_ratio_ring_buffer_variable) {
	svref_arg_1 = Chain_of_available_thrashing_ratio_ring_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_thrashing_ratio_ring_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct;
    }
    else
	def_structure_thrashing_ratio_ring_buffer_variable = 
		make_permanent_thrashing_ratio_ring_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_thrashing_ratio_ring_buffer_variable,
	    Nil);
    ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,(SI_Long)1L) 
	    = FIX((SI_Long)0L);
    ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,(SI_Long)2L) 
	    = FIX((SI_Long)0L);
    SVREF(def_structure_thrashing_ratio_ring_buffer_variable,
	    FIX((SI_Long)3L)) = T;
    ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,(SI_Long)4L) 
	    = FIX((SI_Long)0L);
    ISVREF(def_structure_thrashing_ratio_ring_buffer_variable,(SI_Long)5L) 
	    = FIX((SI_Long)0L);
    SVREF(def_structure_thrashing_ratio_ring_buffer_variable,
	    FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_thrashing_ratio_ring_buffer_variable);
}

/* COPY-THRASHING-RATIO-RING-BUFFER */
Object copy_thrashing_ratio_ring_buffer varargs_1(int, n)
{
    Object ring_buffer;
    Object new_shell, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(127,16);
    INIT_ARGS_nonrelocating();
    ring_buffer = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    new_shell = make_thrashing_ratio_ring_buffer_1();
    copy_ring_buffer_shell_slots(ring_buffer,new_shell);
    svref_new_value = copy_ring_buffer_vector(ISVREF(ring_buffer,(SI_Long)6L));
    SVREF(new_shell,FIX((SI_Long)6L)) = svref_new_value;
    return VALUES_1(new_shell);
}

Object Fixnum_time_normalization_factor = UNBOUND;

static Object float_constant;      /* 0.0 */

/* COMPUTE-NEWEST-THRASHING-RATIO */
Object compute_newest_thrashing_ratio(limit_info,time_since_last_update)
    Object limit_info, time_since_last_update;
{
    Object thrashing_cost_float, temp, normalized_time_since_last_update;
    Object newest_thrashing_ratio, filtered_thrashing_ratio, ring_buffer_shell;
    Object temp_3, thrashing_ratio_ring_buffer, index_1;
    Object store_managed_number_or_value_arg, svref_new_value, svref_arg_2;
    Object ring_buffer, index_2, oldest_active_element_index_for_ring_buffer;
    SI_Long temp_4;
    double temp_1, temp_2;

    x_note_fn_call(127,17);
    thrashing_cost_float = lfloat(ISVREF(limit_info,(SI_Long)3L),
	    float_constant);
    if (time_since_last_update) {
	temp = lfloat(time_since_last_update,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(Fixnum_time_normalization_factor);
	normalized_time_since_last_update = DOUBLE_TO_DOUBLE_FLOAT(temp_1 
		/ temp_2);
    }
    else
	normalized_time_since_last_update = Nil;
    newest_thrashing_ratio = l_round(normalized_time_since_last_update ? 
	    divide(thrashing_cost_float,normalized_time_since_last_update) 
	    : thrashing_cost_float,_);
    filtered_thrashing_ratio = Nil;
    ISVREF(limit_info,(SI_Long)3L) = FIX((SI_Long)0L);
    if ( !TRUEP(ISVREF(limit_info,(SI_Long)6L))) {
	ring_buffer_shell = make_thrashing_ratio_ring_buffer_1();
	temp_3 = allocate_managed_array(1,Smallest_ring_buffer_vector_size);
	SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = temp_3;
	temp_3 = Smallest_ring_buffer_vector_size;
	SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = temp_3;
	SVREF(limit_info,FIX((SI_Long)6L)) = ring_buffer_shell;
    }
    thrashing_ratio_ring_buffer = ISVREF(limit_info,(SI_Long)6L);
    if (ISVREF(thrashing_ratio_ring_buffer,(SI_Long)3L)) {
	index_1 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	temp_3 = FIXNUM_ADD1(ISVREF(thrashing_ratio_ring_buffer,(SI_Long)5L));
	SVREF(thrashing_ratio_ring_buffer,FIX((SI_Long)5L)) = temp_3;
	temp_3 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)6L);
	store_managed_number_or_value_arg = newest_thrashing_ratio;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_3,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp_3,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp_3,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp_3,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(temp_3,svref_arg_2) = svref_new_value;
	}
	else {
	    temp_3 = ISVREF(temp_3,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_4 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp_3,temp_4) = svref_new_value;
	}
	SVREF(thrashing_ratio_ring_buffer,FIX((SI_Long)3L)) = Nil;
    }
    else {
	ring_buffer = thrashing_ratio_ring_buffer;
	index_2 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_EQ(FIXNUM_GE(index_2,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)),
		ISVREF(thrashing_ratio_ring_buffer,(SI_Long)4L)))
	    FUNCALL_SYMBOL_1(Nil,thrashing_ratio_ring_buffer);
	index_2 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	ring_buffer = thrashing_ratio_ring_buffer;
	temp_4 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L) = FIX(temp_4);
	index_1 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	temp_3 = FIXNUM_ADD1(ISVREF(thrashing_ratio_ring_buffer,(SI_Long)5L));
	SVREF(thrashing_ratio_ring_buffer,FIX((SI_Long)5L)) = temp_3;
	temp_3 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)6L);
	store_managed_number_or_value_arg = newest_thrashing_ratio;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp_3,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp_3,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp_3,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp_3,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(temp_3,svref_arg_2) = svref_new_value;
	}
	else {
	    temp_3 = ISVREF(temp_3,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_4 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp_3,temp_4) = svref_new_value;
	}
    }
    ring_buffer = thrashing_ratio_ring_buffer;
    index_2 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
    oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
	    (SI_Long)2L);
    if (FIXNUM_GT(FIXNUM_GE(index_2,
	    oldest_active_element_index_for_ring_buffer) ? 
	    FIXNUM_ADD1(FIXNUM_MINUS(index_2,
	    oldest_active_element_index_for_ring_buffer)) : 
	    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,ISVREF(ring_buffer,
	    (SI_Long)4L)),oldest_active_element_index_for_ring_buffer)),
	    Thrashing_ratio_ring_buffer_length)) {
	index_2 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)2L);
	ring_buffer = thrashing_ratio_ring_buffer;
	temp_4 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	ISVREF(thrashing_ratio_ring_buffer,(SI_Long)2L) = FIX(temp_4);
    }
    filtered_thrashing_ratio = 
	    l_round(compute_filtered_thrashing_ratio(thrashing_ratio_ring_buffer),
	    _);
    SVREF(limit_info,FIX((SI_Long)4L)) = newest_thrashing_ratio;
    SVREF(limit_info,FIX((SI_Long)5L)) = filtered_thrashing_ratio;
    return VALUES_2(newest_thrashing_ratio,filtered_thrashing_ratio);
}

Object Base_for_exponential_weighting = UNBOUND;

/* COMPUTE-WEIGHTING-FACTORS-FOR-THRASHING-FILTER */
Object compute_weighting_factors_for_thrashing_filter()
{
    x_note_fn_call(127,18);
    return compute_exponential_weighting_factors(Base_for_exponential_weighting);
}

/* COMPUTE-EXPONENTIAL-WEIGHTING-FACTORS */
Object compute_exponential_weighting_factors(exponent_base)
    Object exponent_base;
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long exponent, ab_loop_bind_;

    x_note_fn_call(127,19);
    exponent = (SI_Long)1L;
    ab_loop_bind_ = IFIX(Thrashing_ratio_ring_buffer_length);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (exponent > ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = LIST_1(expt(exponent_base,FIX(exponent)));
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    exponent = exponent + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Weighting_factors_for_thrashing_ratio_ring_buffers, Qweighting_factors_for_thrashing_ratio_ring_buffers);

/* COMPUTE-FILTERED-THRASHING-RATIO */
Object compute_filtered_thrashing_ratio(thrashing_ratio_ring_buffer)
    Object thrashing_ratio_ring_buffer;
{
    Object index_1, count_1, weighting_factor, ab_loop_list_, ab_loopvar_;
    Object temp, managed_number_or_value, temp_1, ring_buffer, index_2;
    Object oldest_active_element_index_for_ring_buffer;

    x_note_fn_call(127,20);
    if ( !TRUEP(ISVREF(thrashing_ratio_ring_buffer,(SI_Long)3L))) {
	index_1 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	count_1 = FIX((SI_Long)1L);
	weighting_factor = Nil;
	ab_loop_list_ = Weighting_factors_for_thrashing_ratio_ring_buffers;
	ab_loopvar_ = FIX((SI_Long)0L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	weighting_factor = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = weighting_factor;
	managed_number_or_value = 
		FIXNUM_LE(ISVREF(ISVREF(thrashing_ratio_ring_buffer,
		(SI_Long)6L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(thrashing_ratio_ring_buffer,(SI_Long)6L),
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(thrashing_ratio_ring_buffer,
		(SI_Long)6L),(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp_1 = copy_text_string(managed_number_or_value);
	else
	    temp_1 = managed_number_or_value;
	ab_loopvar_ = add(ltimes(temp,temp_1),ab_loopvar_);
	temp = count_1;
	ring_buffer = thrashing_ratio_ring_buffer;
	index_2 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_GE(temp,FIXNUM_GE(index_2,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)))) {
	    count_1 = FIX((SI_Long)1L);
	    index_1 = ISVREF(thrashing_ratio_ring_buffer,(SI_Long)1L);
	}
	else {
	    count_1 = FIXNUM_ADD1(count_1);
	    index_1 = IFIX(index_1) == (SI_Long)0L ? 
		    FIXNUM_SUB1(ISVREF(thrashing_ratio_ring_buffer,
		    (SI_Long)4L)) : FIXNUM_SUB1(index_1);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(FIX((SI_Long)0L));
}

void rings_INIT()
{
    Object temp_1, reclaim_structure_for_ring_buffer_state_1;
    Object reclaim_structure_for_thrashing_ratio_ring_buffer_1;
    SI_Long temp;
    Object float_constant_1, Qthrashing_ratio_ring_buffer, Qreclaim_structure;
    Object Qoutstanding_thrashing_ratio_ring_buffer_count;
    Object Qthrashing_ratio_ring_buffer_structure_memory_usage, Qutilities2;
    Object AB_package, string_constant_3, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_2, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qring_buffer_state;
    Object Qoutstanding_ring_buffer_state_count;
    Object Qring_buffer_state_structure_memory_usage, string_constant_1;
    Object string_constant;

    x_note_fn_call(127,21);
    SET_PACKAGE("AB");
    temp = IFIX(Maximum_managed_array_size);
    Smallest_ring_buffer_vector_size = FIX(MIN((SI_Long)16L,temp));
    Largest_ring_buffer_vector_size = ltimes(Maximum_managed_array_size,
	    FIX((SI_Long)16L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_ring_buffer_state_g2_struct = 
	    STATIC_SYMBOL("RING-BUFFER-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qring_buffer_state = STATIC_SYMBOL("RING-BUFFER-STATE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ring_buffer_state_g2_struct,
	    Qring_buffer_state,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qring_buffer_state,
	    Qg2_defstruct_structure_name_ring_buffer_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_ring_buffer_state == UNBOUND)
	The_type_description_of_ring_buffer_state = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m834Yy1n834Yy8n8k1l8n0000001l1m8y83-5cykqk0k0");
    temp_1 = The_type_description_of_ring_buffer_state;
    The_type_description_of_ring_buffer_state = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ring_buffer_state_g2_struct,
	    The_type_description_of_ring_buffer_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qring_buffer_state,
	    The_type_description_of_ring_buffer_state,
	    Qtype_description_of_type);
    Qoutstanding_ring_buffer_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-RING-BUFFER-STATE-COUNT",AB_package);
    Qring_buffer_state_structure_memory_usage = 
	    STATIC_SYMBOL("RING-BUFFER-STATE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q834Yy8s83-n6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_ring_buffer_state_count);
    push_optimized_constant(Qring_buffer_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_ring_buffer_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RING-BUFFER-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_ring_buffer_states,
	    Chain_of_available_ring_buffer_states);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_ring_buffer_states,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qring_buffer_state_count = STATIC_SYMBOL("RING-BUFFER-STATE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qring_buffer_state_count,
	    Ring_buffer_state_count);
    record_system_variable(Qring_buffer_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_ring_buffer_states_vector == UNBOUND)
	Chain_of_available_ring_buffer_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qring_buffer_state_structure_memory_usage,
	    STATIC_FUNCTION(ring_buffer_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_ring_buffer_state_count,
	    STATIC_FUNCTION(outstanding_ring_buffer_state_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_ring_buffer_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_ring_buffer_state,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qring_buffer_state,
	    reclaim_structure_for_ring_buffer_state_1);
    Thrashing_ratio_ring_buffer_length = FIX((SI_Long)10L);
    Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct = 
	    STATIC_SYMBOL("THRASHING-RATIO-RING-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qthrashing_ratio_ring_buffer = 
	    STATIC_SYMBOL("THRASHING-RATIO-RING-BUFFER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct,
	    Qthrashing_ratio_ring_buffer,Qab_name_of_unique_structure_type);
    mutate_global_property(Qthrashing_ratio_ring_buffer,
	    Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_thrashing_ratio_ring_buffer == UNBOUND)
	The_type_description_of_thrashing_ratio_ring_buffer = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83npy1o83npy834Yy8n8k1l834Yy0000001m1m8x834Yy1m8y83-67ykrk0k0");
    temp_1 = The_type_description_of_thrashing_ratio_ring_buffer;
    The_type_description_of_thrashing_ratio_ring_buffer = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_2));
    mutate_global_property(Qg2_defstruct_structure_name_thrashing_ratio_ring_buffer_g2_struct,
	    The_type_description_of_thrashing_ratio_ring_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qthrashing_ratio_ring_buffer,
	    The_type_description_of_thrashing_ratio_ring_buffer,
	    Qtype_description_of_type);
    Qoutstanding_thrashing_ratio_ring_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-THRASHING-RATIO-RING-BUFFER-COUNT",
	    AB_package);
    Qthrashing_ratio_ring_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("THRASHING-RATIO-RING-BUFFER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_3 = STATIC_STRING("1q83npy8s83-sqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_thrashing_ratio_ring_buffer_count);
    push_optimized_constant(Qthrashing_ratio_ring_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_thrashing_ratio_ring_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-THRASHING-RATIO-RING-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_thrashing_ratio_ring_buffers,
	    Chain_of_available_thrashing_ratio_ring_buffers);
    record_system_variable(Qchain_of_available_thrashing_ratio_ring_buffers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qthrashing_ratio_ring_buffer_count = 
	    STATIC_SYMBOL("THRASHING-RATIO-RING-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthrashing_ratio_ring_buffer_count,
	    Thrashing_ratio_ring_buffer_count);
    record_system_variable(Qthrashing_ratio_ring_buffer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_thrashing_ratio_ring_buffers_vector == UNBOUND)
	Chain_of_available_thrashing_ratio_ring_buffers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qthrashing_ratio_ring_buffer_structure_memory_usage,
	    STATIC_FUNCTION(thrashing_ratio_ring_buffer_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_thrashing_ratio_ring_buffer_count,
	    STATIC_FUNCTION(outstanding_thrashing_ratio_ring_buffer_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_thrashing_ratio_ring_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_thrashing_ratio_ring_buffer,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qthrashing_ratio_ring_buffer,
	    reclaim_structure_for_thrashing_ratio_ring_buffer_1);
    float_constant = STATIC_FLOAT(0.0);
    Fixnum_time_normalization_factor = 
	    lfloat(fixnum_time_interval(FIX((SI_Long)1000L)),float_constant);
    float_constant_1 = STATIC_FLOAT(0.5);
    Base_for_exponential_weighting = float_constant_1;
    if (Weighting_factors_for_thrashing_ratio_ring_buffers == UNBOUND)
	Weighting_factors_for_thrashing_ratio_ring_buffers = 
		compute_weighting_factors_for_thrashing_filter();
}
