/* frms2a.c
 * Input file:  frames2a.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms2a.h"


/* UUID-FUNCTION */
Object uuid_function(item)
    Object item;
{
    x_note_fn_call(83,0);
    return VALUES_1(ISVREF(item,(SI_Long)2L));
}

/* RECLAIM-FRAME-SERIAL-NUMBER-VALUE */
Object reclaim_frame_serial_number_value(frame_serial_number,frame)
    Object frame_serial_number, frame;
{
    x_note_fn_call(83,1);
    return VALUES_1(Nil);
}

/* FRAME-HASH-FUNCTION */
Object frame_hash_function(block)
    Object block;
{
    Object fsn, temp;

    x_note_fn_call(83,2);
    fsn = ISVREF(block,(SI_Long)3L);
    temp = FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn));
    return VALUES_1(temp);
}

/* FRAME-SERIAL-NUMBER-FUNCTION */
Object frame_serial_number_function(block)
    Object block;
{
    Object temp;

    x_note_fn_call(83,3);
    temp = ISVREF(block,(SI_Long)3L);
    return VALUES_1(temp);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* FRAME-HAS-BEEN-REPROCESSED-P-FUNCTION */
Object frame_has_been_reprocessed_p_function(block,reference_serial_number)
    Object block, reference_serial_number;
{
    Object gensymed_symbol, temp, xa, ya;

    x_note_fn_call(83,4);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? (EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) ? T : Nil) : Qnil;
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? (IFIX(gensymed_symbol) == 
		(SI_Long)-1L ? T : Nil) : Nil;
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		(FIXNUM_LT(reference_serial_number,gensymed_symbol) ? T : 
		Nil) : T;
    else if (FIXNUMP(gensymed_symbol))
	temp = Nil;
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya) ? T : Nil;
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    (FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) ? T : Nil) : Qnil;
    }
    return VALUES_1(temp);
}

Object Instances_specific_to_this_class_kbprop = UNBOUND;

Object Instances_specific_to_this_class_tail_pointer_kbprop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Class_specific_instances_lock, Qclass_specific_instances_lock);

/* ADD-TO-INSTANCES-SPECIFIC-TO-THIS-CLASS */
Object add_to_instances_specific_to_this_class(class_1,frame)
    Object class_1, frame;
{
    Object first_instance_qm, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(83,5);
    SAVE_STACK();
    LOCK(Class_specific_instances_lock);
    if (PUSH_UNWIND_PROTECT(0)) {
	if (ISVREF(frame,(SI_Long)6L) || ISVREF(frame,(SI_Long)7L))
	    delete_from_instances_specific_to_this_class(class_1,frame);
	first_instance_qm = lookup_kb_specific_property_value(class_1,
		Instances_specific_to_this_class_kbprop);
	if (first_instance_qm) {
	    ISVREF(first_instance_qm,(SI_Long)7L) = frame;
	    ISVREF(frame,(SI_Long)6L) = first_instance_qm;
	    ISVREF(frame,(SI_Long)7L) = Nil;
	    temp = mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_kbprop);
	}
	else {
	    mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_kbprop);
	    mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_tail_pointer_kbprop);
	    ISVREF(frame,(SI_Long)6L) = Nil;
	    temp = ISVREF(frame,(SI_Long)7L) = Nil;
	}
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Class_specific_instances_lock);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    result = VALUES_1(result);
    RESTORE_STACK();
    return result;
}

/* ADD-TO-END-OF-INSTANCES-SPECIFIC-TO-THIS-CLASS */
Object add_to_end_of_instances_specific_to_this_class(class_1,frame)
    Object class_1, frame;
{
    Object last_instance_qm, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(83,6);
    SAVE_STACK();
    LOCK(Class_specific_instances_lock);
    if (PUSH_UNWIND_PROTECT(0)) {
	if (ISVREF(frame,(SI_Long)6L) || ISVREF(frame,(SI_Long)7L))
	    delete_from_instances_specific_to_this_class(class_1,frame);
	last_instance_qm = lookup_kb_specific_property_value(class_1,
		Instances_specific_to_this_class_tail_pointer_kbprop);
	if (last_instance_qm) {
	    ISVREF(last_instance_qm,(SI_Long)6L) = frame;
	    ISVREF(frame,(SI_Long)7L) = last_instance_qm;
	    ISVREF(frame,(SI_Long)6L) = Nil;
	    temp = mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_tail_pointer_kbprop);
	}
	else {
	    mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_kbprop);
	    mutate_kb_specific_property_value(class_1,frame,
		    Instances_specific_to_this_class_tail_pointer_kbprop);
	    ISVREF(frame,(SI_Long)6L) = Nil;
	    temp = ISVREF(frame,(SI_Long)7L) = Nil;
	}
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Class_specific_instances_lock);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    result = VALUES_1(result);
    RESTORE_STACK();
    return result;
}

/* DELETE-FROM-INSTANCES-SPECIFIC-TO-THIS-CLASS */
Object delete_from_instances_specific_to_this_class(class_1,frame)
    Object class_1, frame;
{
    Object next_qm, temp, previous_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(83,7);
    SAVE_STACK();
    LOCK(Class_specific_instances_lock);
    if (PUSH_UNWIND_PROTECT(0)) {
	if ( !TRUEP(ISVREF(frame,(SI_Long)7L))) {
	    next_qm = ISVREF(frame,(SI_Long)6L);
	    if (next_qm) {
		ISVREF(frame,(SI_Long)6L) = Nil;
		mutate_kb_specific_property_value(class_1,next_qm,
			Instances_specific_to_this_class_kbprop);
		temp = ISVREF(next_qm,(SI_Long)7L) = Nil;
	    }
	    else {
		mutate_kb_specific_property_value(class_1,Nil,
			Instances_specific_to_this_class_kbprop);
		temp = mutate_kb_specific_property_value(class_1,Nil,
			Instances_specific_to_this_class_tail_pointer_kbprop);
	    }
	}
	else if ( !TRUEP(ISVREF(frame,(SI_Long)6L))) {
	    previous_qm = ISVREF(frame,(SI_Long)7L);
	    ISVREF(frame,(SI_Long)7L) = Nil;
	    mutate_kb_specific_property_value(class_1,previous_qm,
		    Instances_specific_to_this_class_tail_pointer_kbprop);
	    temp = ISVREF(previous_qm,(SI_Long)6L) = Nil;
	}
	else {
	    next_qm = ISVREF(frame,(SI_Long)6L);
	    previous_qm = ISVREF(frame,(SI_Long)7L);
	    ISVREF(frame,(SI_Long)6L) = Nil;
	    ISVREF(frame,(SI_Long)7L) = Nil;
	    ISVREF(previous_qm,(SI_Long)6L) = next_qm;
	    temp = ISVREF(next_qm,(SI_Long)7L) = previous_qm;
	}
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Class_specific_instances_lock);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    result = VALUES_1(result);
    RESTORE_STACK();
    return result;
}

Object Largest_frame_vector_size = UNBOUND;

/* CREATE-FRAME-VECTOR-POOL-VECTOR */
Object create_frame_vector_pool_vector(initial_element)
    Object initial_element;
{
    x_note_fn_call(83,8);
    return make_array(3,Largest_frame_vector_size,Kinitial_element,
	    initial_element);
}

/* CREATE-FRAME-VECTOR-POOL-ARRAY */
Object create_frame_vector_pool_array(initial_element)
    Object initial_element;
{
    Object vector_1, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(83,9);
    vector_1 = make_thread_array(Nil);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(G2_max_threads);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = create_frame_vector_pool_vector(initial_element);
    ISVREF(vector_1,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(vector_1);
}

Object Frame_vector_pool_array = UNBOUND;

Object Frame_vector_pool_counts_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Frame_vector_count, Qframe_vector_count);

DEFINE_VARIABLE_WITH_SYMBOL(Outstanding_frame_vector_count, Qoutstanding_frame_vector_count);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_vector_memory_used, Qframe_vector_memory_used);

/* FRAME-VECTOR-MEMORY-USAGE */
Object frame_vector_memory_usage()
{
    x_note_fn_call(83,10);
    return VALUES_1(Frame_vector_memory_used);
}

Object Frame_vectors_to_make_at_a_time = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Frame_vector_pool_vector, Qframe_vector_pool_vector);

static Object Qframe;              /* frame */

/* CREATE-FRAME-VECTOR-AND-REPLENISH-POOL */
Object create_frame_vector_and_replenish_pool(size)
    Object size;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, size_list, vector_index, last_created_vector;
    Object vector_holder;
    SI_Long ab_loop_repeat_;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(83,11);
    temp = Frame_vectors_to_make_at_a_time;
    atomic_incff_symval(Qframe_vector_memory_used,FIXNUM_TIMES(temp,
	    bytes_per_simple_vector(size)));
    atomic_incff_symval(Qframe_vector_count,Frame_vectors_to_make_at_a_time);
    new_cons = ISVREF(Available_frame_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_frame_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_frame_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_frame_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_frame_cons_pool();
    M_CAR(gensymed_symbol) = size;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qframe);
    size_list = gensymed_symbol;
    vector_index = FIXNUM_SUB1(size);
    atomic_incff_svslot(Frame_vector_pool_counts_vector,vector_index,
	    Frame_vectors_to_make_at_a_time);
    if (PUSH_AREA(Dynamic_area,0)) {
	last_created_vector = Nil;
	vector_holder = Nil;
	ab_loop_repeat_ = IFIX(FIXNUM_SUB1(Frame_vectors_to_make_at_a_time));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	vector_holder = make_array(1,size_list);
	SVREF(vector_holder,FIX((SI_Long)0L)) = last_created_vector;
	last_created_vector = vector_holder;
	goto next_loop;
      end_loop:
	temp_1 = Frame_vector_pool_vector;
	SVREF(temp_1,vector_index) = last_created_vector;
	temp = make_array(3,size_list,Kinitial_element,Nil);
	inline_note_reclaim_cons(size_list,Qframe);
	if (ISVREF(Available_frame_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = size_list;
	    temp_1 = Available_frame_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = size_list;
	}
	else {
	    temp_1 = Available_frame_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = size_list;
	    temp_1 = Available_frame_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = size_list;
	}
	M_CDR(size_list) = Nil;
	result = VALUES_1(temp);
    }
    POP_AREA(0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_initialize_specializations, Qdo_not_initialize_specializations);

DEFINE_VARIABLE_WITH_SYMBOL(Uuid_for_next_frame_qm, Quuid_for_next_frame_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Class_description_for_next_frame_qm, Qclass_description_for_next_frame_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Tracking_items_p, Qtracking_items_p);

DEFINE_VARIABLE_WITH_SYMBOL(Reading_kb_p, Qreading_kb_p);

DEFINE_VARIABLE_WITH_SYMBOL(Called_within_clear_text_loading, Qcalled_within_clear_text_loading);

/* ALLOCATE-FRAME */
Object allocate_frame(class_description,frame_serial_number_qm,uuid_qm,
	    eval_slot_init_forms_p,class_known_to_be_system_item_p)
    Object class_description, frame_serial_number_qm, uuid_qm;
    Object eval_slot_init_forms_p, class_known_to_be_system_item_p;
{
    Object class_1, system_item_p, sub_class_bit_vector, gensymed_symbol_3;
    Object gensymed_symbol_4, frame_vector_pool_vector, gensymed_symbol_5;
    Object temp, svref_new_value, frame, lookup_structure, slot_description;
    Object ab_loop_list_, vector_slot_index_qm, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(1);

    x_note_fn_call(83,12);
    if ( !TRUEP(uuid_qm) && Uuid_for_next_frame_qm && 
	    EQ(Class_description_for_next_frame_qm,class_description)) {
	uuid_qm = Uuid_for_next_frame_qm;
	Uuid_for_next_frame_qm = Nil;
	Class_description_for_next_frame_qm = Nil;
    }
    class_1 = ISVREF(class_description,(SI_Long)1L);
    system_item_p = class_known_to_be_system_item_p;
    if (system_item_p);
    else {
	sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(System_item_class_description,(SI_Long)18L));
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
	    system_item_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    system_item_p = Nil;
    }
    if (system_item_p) {
	gensymed_symbol_3 = ISVREF(class_description,(SI_Long)14L);
	gensymed_symbol_4 = FIXNUM_SUB1(gensymed_symbol_3);
	frame_vector_pool_vector = ISVREF(Frame_vector_pool_array,
		IFIX(Current_thread_index));
	PUSH_SPECIAL_WITH_SYMBOL(Frame_vector_pool_vector,Qframe_vector_pool_vector,frame_vector_pool_vector,
		0);
	  if (FIXNUM_GT(gensymed_symbol_3,Largest_frame_vector_size))
	      error((SI_Long)2L,
		      "Tried to allocate a frame larger than largest-frame-vector-size,~%which is ~a.  Increase largest-frame-vector-size!",
		      Largest_frame_vector_size);
	  atomic_incff_symval(Qoutstanding_frame_vector_count,
		  FIX((SI_Long)1L));
	  gensymed_symbol_5 = ISVREF(Frame_vector_pool_vector,
		  IFIX(gensymed_symbol_4));
	  if (gensymed_symbol_5) {
	      temp = Frame_vector_pool_vector;
	      svref_new_value = ISVREF(gensymed_symbol_5,(SI_Long)0L);
	      SVREF(temp,gensymed_symbol_4) = svref_new_value;
	      gensymed_symbol_5;
	  }
	  else
	      gensymed_symbol_5 = 
		      create_frame_vector_and_replenish_pool(gensymed_symbol_3);
	  inline_note_allocate_cons(gensymed_symbol_5,Nil);
	  frame = gensymed_symbol_5;
	POP_SPECIAL();
    }
    else
	frame = allocate_managed_simple_vector(ISVREF(class_description,
		(SI_Long)14L));
    lookup_structure = IFIX(ISVREF(class_description,(SI_Long)15L)) > 
	    (SI_Long)0L ? 
	    allocate_frame_lookup_structure_vector(ISVREF(class_description,
	    (SI_Long)15L),Nil) : Nil;
    slot_description = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    vector_slot_index_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
    if (vector_slot_index_qm) {
	temp = ISVREF(slot_description,(SI_Long)6L);
	SVREF(frame,vector_slot_index_qm) = temp;
    }
    else if (ISVREF(slot_description,(SI_Long)8L)) {
	temp = ISVREF(slot_description,(SI_Long)8L);
	svref_new_value = ISVREF(slot_description,(SI_Long)6L);
	SVREF(lookup_structure,temp) = svref_new_value;
    }
    goto next_loop;
  end_loop:;
    SVREF(frame,FIX((SI_Long)1L)) = class_description;
    SVREF(frame,FIX((SI_Long)0L)) = lookup_structure;
    if (eval_slot_init_forms_p)
	initialize_slots_of_frame_needing_evaluation(frame);
    if (system_item_p) {
	temp_1 = frame_serial_number_qm;
	if (temp_1);
	else
	    temp_1 = increment_current_frame_serial_number();
	temp = copy_frame_serial_number(temp_1);
	ISVREF(frame,(SI_Long)3L) = temp;
	if (uuid_qm)
	    put_uuid(frame,uuid_qm,T);
	if ( !(uuid_qm && ISVREF(frame,(SI_Long)2L)))
	    put_new_uuid(frame);
	add_to_end_of_instances_specific_to_this_class(class_1,frame);
	if (Tracking_items_p)
	    note_tracked_item_creation(frame);
	if (Reading_kb_p || Called_within_clear_text_loading || In_clear_kb_p)
	    set_item_was_created_by_load_function(frame);
    }
    return VALUES_1(frame);
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_being_made, Qframe_being_made);

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

static Object Kfuncall;            /* :funcall */

/* INITIALIZE-SLOTS-OF-FRAME-NEEDING-EVALUATION */
Object initialize_slots_of_frame_needing_evaluation(frame)
    Object frame;
{
    Object noting_changes_to_kb_p, current_block_of_dependent_frame;
    Object frame_being_made, class_of_frame, slot_description;
    Object class_description, ab_loop_list_, slot_init_form, temp;
    Object vector_slot_index_qm, temp_1, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm, temp_3;
    SI_Long max_i, i, ab_loop_bind_;
    char temp_2;
    Declare_special(3);

    x_note_fn_call(83,13);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
	    2);
      current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	      1);
	frame_being_made = frame;
	PUSH_SPECIAL_WITH_SYMBOL(Frame_being_made,Qframe_being_made,frame_being_made,
		0);
	  class_of_frame = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	  slot_description = Nil;
	  class_description = ISVREF(frame,(SI_Long)1L);
	  ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	  slot_init_form = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  slot_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  slot_init_form = ISVREF(slot_description,(SI_Long)6L);
	  if (CONSP(slot_init_form) && EQ(M_CAR(slot_init_form),Kfuncall)) {
	      temp = slot_init_form;
	      vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	      if (vector_slot_index_qm)
		  temp_1 = ISVREF(frame,IFIX(vector_slot_index_qm));
	      else {
		  user_vector_slot_index_qm = ISVREF(slot_description,
			  (SI_Long)8L);
		  if (user_vector_slot_index_qm)
		      temp_1 = ISVREF(ISVREF(frame,(SI_Long)0L),
			      IFIX(user_vector_slot_index_qm));
		  else {
		      slot_name = ISVREF(slot_description,(SI_Long)1L);
		      lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		      if (lookup_structure_qm) {
			  max_i = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			  max_i = max_i - (SI_Long)1L;
			  i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),
				  (SI_Long)15L));
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
			  temp_1 = slot_index_qm ? 
				  ISVREF(lookup_structure_qm,
				  IFIX(slot_index_qm)) : 
				  ISVREF(slot_description,(SI_Long)6L);
		      }
		      else
			  temp_1 = ISVREF(slot_description,(SI_Long)6L);
		  }
	      }
	      temp_2 = EQ(temp,temp_1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      temp_1 = slot_description;
	      if (class_in_attribute_conforms_to_type_p(3,slot_description,
		      class_of_frame,T)) {
		  if (CONSP(slot_init_form) && EQ(M_CAR(slot_init_form),
			  Kfuncall)) {
		      temp_3 = M_CAR(M_CDR(slot_init_form));
		      temp = M_CDR(slot_init_form);
		      temp = APPLY_1(temp_3,CDR(temp));
		  }
		  else
		      temp = slot_init_form;
	      }
	      else
		  temp = Nil;
	      initialize_slot_description_value(frame,temp_1,temp);
	  }
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* WELL-INSTANTIATED-OR-SUBCLASSED-CLASS-P */
Object well_instantiated_or_subclassed_class_p(class_1)
    Object class_1;
{
    Object ab_loopvar_, instance, temp, temp_1, inferior_class, ab_loop_list_;
    SI_Long ab_loopvar__1;

    x_note_fn_call(83,14);
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    ab_loopvar__1 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    if (instance)
	ab_loopvar__1 = ab_loopvar__1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = FIX(ab_loopvar__1);
    goto end_1;
    temp = Qnil;
  end_1:;
    temp_1 = FIX((SI_Long)5L);
    temp_1 = NUM_GT(temp,temp_1) ? T : Nil;
    if (temp_1);
    else {
	inferior_class = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(class_1,
		Inferior_classes_gkbprop);
	ab_loopvar__1 = (SI_Long)0L;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	inferior_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = 
		lookup_global_or_kb_specific_property_value(inferior_class,
		Direct_superior_classes_gkbprop);
	if ( !TRUEP(CDR(temp_1))) {
	    if (class_1)
		ab_loopvar__1 = ab_loopvar__1 + (SI_Long)1L;
	}
	goto next_loop_1;
      end_loop_1:
	temp = FIX(ab_loopvar__1);
	goto end_2;
	temp = Qnil;
      end_2:;
	temp_1 = FIX((SI_Long)3L);
	temp_1 = NUM_GT(temp,temp_1) ? T : Nil;
    }
    return VALUES_1(temp_1);
}

static Object Quuid;               /* uuid */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qunique_identification;  /* unique-identification */

static Object Qpreviously_put_in_attribute_tables;  /* previously-put-in-attribute-tables */

static Object Qdo_not_put_in_attribute_tables;  /* do-not-put-in-attribute-tables */

static Object Qnot_ent;            /* not-ent */

static Object Qnupec;              /* nupec */

static Object Qnot_nupec;          /* not-nupec */

/* DO-NOT-PUT-SLOT-IN-ATTRIBUTE-TABLES-P */
Object do_not_put_slot_in_attribute_tables_p varargs_1(int, n)
{
    Object slot_description, formerly_visible_qm;
    Object frame_for_attribute_table_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, slot_features;
    Object ab_loop_list_, previously_put_in_qm;
    Object do_not_put_in_attribute_tables_feature_qm, temp_1, code;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(83,15);
    INIT_ARGS_nonrelocating();
    slot_description = REQUIRED_ARG_nonrelocating();
    formerly_visible_qm = REQUIRED_ARG_nonrelocating();
    frame_for_attribute_table_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L)) && 
	    EQ(ISVREF(slot_description,(SI_Long)2L),Quuid)) {
	temp =  !TRUEP(frame_for_attribute_table_qm);
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(frame_for_attribute_table_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_for_attribute_table_qm)) 
		    > (SI_Long)2L &&  
		    !EQ(ISVREF(frame_for_attribute_table_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(frame_for_attribute_table_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qunique_identification,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
	}
	if (temp);
	else
	    temp = TRUEP(show_uuids_in_attribute_tables_function());
	return VALUES_1( !temp ? T : Nil);
    }
    else {
	slot_features = ISVREF(slot_description,(SI_Long)9L);
	gensymed_symbol = Nil;
	ab_loop_list_ = slot_features;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qpreviously_put_in_attribute_tables)) {
	    previously_put_in_qm = gensymed_symbol;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	previously_put_in_qm = Qnil;
      end_1:;
	do_not_put_in_attribute_tables_feature_qm = previously_put_in_qm;
	if (do_not_put_in_attribute_tables_feature_qm);
	else {
	    gensymed_symbol = Nil;
	    ab_loop_list_ = slot_features;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		    Qdo_not_put_in_attribute_tables)) {
		do_not_put_in_attribute_tables_feature_qm = gensymed_symbol;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    do_not_put_in_attribute_tables_feature_qm = Qnil;
	  end_2:;
	}
	if (do_not_put_in_attribute_tables_feature_qm) {
	    temp =  !TRUEP(CDR(do_not_put_in_attribute_tables_feature_qm));
	    if (temp);
	    else {
		temp_1 = SECOND(do_not_put_in_attribute_tables_feature_qm);
		if (EQ(temp_1,Qnot_ent))
		    temp =  !TRUEP(g2_enterprise_p());
		else if (EQ(temp_1,Qnupec)) {
		    code = M_CAR(M_CDR(Journal_shutout_scan_p));
		    temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) 
			    != (SI_Long)0L ? 
			    TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) 
			    : TRUEP(Nil);
		}
		else if (EQ(temp_1,Qnot_nupec)) {
		    code = M_CAR(M_CDR(Journal_shutout_scan_p));
		    temp =  !(FIXNUMP(code) && (IFIX(code) & 
			    (SI_Long)256L) != (SI_Long)0L ? 
			    TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) 
			    : TRUEP(Nil));
		}
		else
		    temp = TRUEP(Qnil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1( !(formerly_visible_qm && 
		    previously_put_in_qm) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
}

Object Active_flag = UNBOUND;

Object Frame_being_deleted_flag = UNBOUND;

Object Permanent_block_flag = UNBOUND;

static Object Qparent_frame;       /* parent-frame */

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* GET-KB-PARENT-INFORMATION */
Object get_kb_parent_information(block)
    Object block;
{
    Object parent_attribute_name, temp;

    x_note_fn_call(83,16);
    if (get_lookup_slot_value_given_default(block,Qparent_frame,Nil)) {
	parent_attribute_name = get_lookup_slot_value_given_default(block,
		Qparent_attribute_name,Nil);
	if (CONSP(parent_attribute_name)) {
	    temp = get_lookup_slot_value_given_default(block,Qparent_frame,
		    Nil);
	    return VALUES_3(temp,M_CAR(parent_attribute_name),
		    M_CDR(parent_attribute_name));
	}
	else {
	    temp = get_lookup_slot_value_given_default(block,Qparent_frame,
		    Nil);
	    return VALUES_2(temp,parent_attribute_name);
	}
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PARENT-FRAME-VALUE */
Object reclaim_parent_frame_value(parent_frame_qm,frame)
    Object parent_frame_qm, frame;
{
    Object parent_attribute_name, pretty_slot_name, defining_class;
    Object parent_frame_slot_description_qm;

    x_note_fn_call(83,17);
    if (parent_frame_qm &&  !((SI_Long)0L != (IFIX(ISVREF(parent_frame_qm,
	    (SI_Long)5L)) & (SI_Long)512L))) {
	parent_attribute_name = get_lookup_slot_value_given_default(frame,
		Qparent_attribute_name,Nil);
	pretty_slot_name = CONSP(parent_attribute_name) ? 
		M_CAR(parent_attribute_name) : parent_attribute_name;
	defining_class = CONSP(parent_attribute_name) ? 
		M_CDR(parent_attribute_name) : Nil;
	parent_frame_slot_description_qm = 
		get_slot_description_of_class_description_function(pretty_slot_name,
		ISVREF(parent_frame_qm,(SI_Long)1L),defining_class);
	if (parent_frame_slot_description_qm)
	    change_slot_description_value_function(parent_frame_qm,
		    parent_frame_slot_description_qm,Nil,Nil,Nil);
    }
    return VALUES_1(Nil);
}

/* GET-PARENT-ATTRIBUTE-NAME-AS-SYMBOL */
Object get_parent_attribute_name_as_symbol(system_item)
    Object system_item;
{
    Object parent_attribute_name, temp;

    x_note_fn_call(83,18);
    parent_attribute_name = 
	    get_lookup_slot_value_given_default(system_item,
	    Qparent_attribute_name,Nil);
    temp = SYMBOLP(parent_attribute_name) ? parent_attribute_name : 
	    make_unique_slot_name_symbol(M_CDR(parent_attribute_name),
	    M_CAR(parent_attribute_name));
    return VALUES_1(temp);
}

/* INSTANTIATED-CLASS-P */
Object instantiated_class_p(class_1)
    Object class_1;
{
    Object scope_conses, ab_loopvar_, subclass, ab_loop_it_, temp;
    Object ab_loopvar__1, instance;
    Declare_special(1);
    Object result;

    x_note_fn_call(83,19);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = class_1;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      ab_loopvar__1 = lookup_kb_specific_property_value(subclass,
	      Instances_specific_to_this_class_kbprop);
      instance = Nil;
      ab_loop_it_ = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1))
	  goto end_loop_1;
      instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ =  !((SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)5L)) 
	      & (SI_Long)512L)) ? T : Nil;
      if (ab_loop_it_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
      ab_loop_it_ = Qnil;
    end_1:;
      if (ab_loop_it_) {
	  result = VALUES_1(ab_loop_it_);
	  goto end_2;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* ESSENTIALLY-INSTANTIATED-CLASS-P */
Object essentially_instantiated_class_p(class_1)
    Object class_1;
{
    Object ab_loopvar_, instance, ab_loop_it_, temp, subclass, ab_loop_list_;

    x_note_fn_call(83,20);
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    ab_loop_it_ = instance;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	subclass = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(class_1,
		Inferior_classes_gkbprop);
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	subclass = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = 
		invalidated_by_instantiation_without_superclass(subclass,
		class_1);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* INVALIDATED-BY-INSTANTIATION-WITHOUT-SUPERCLASS */
Object invalidated_by_instantiation_without_superclass(class_1,superclass)
    Object class_1, superclass;
{
    Object other_superclass, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, other_superclasses, temp;

    x_note_fn_call(83,21);
    other_superclass = Nil;
    ab_loop_list_ = lookup_global_or_kb_specific_property_value(class_1,
	    Direct_superior_classes_gkbprop);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    other_superclass = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(other_superclass,superclass)) {
	ab_loopvar__2 = gensym_cons_1(other_superclass,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    other_superclasses = ab_loopvar_;
    goto end_1;
    other_superclasses = Qnil;
  end_1:;
    temp =  !TRUEP(other_superclasses) || 
	    direct_superiors_preclude_instantiability_p(other_superclasses) 
	    ? essentially_instantiated_class_p(class_1) : Qnil;
    reclaim_gensym_list_1(other_superclasses);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Queue_of_classes_to_be_undefined, Qqueue_of_classes_to_be_undefined);

DEFINE_VARIABLE_WITH_SYMBOL(Within_delete_frame_scope_qm, Qwithin_delete_frame_scope_qm);

static Object Qdefault_slot_constant;  /* default-slot-constant */

/* RECLAIM-LIST-OF-SLOT-DESCRIPTIONS */
Object reclaim_list_of_slot_descriptions(slot_descriptions_to_reclaim)
    Object slot_descriptions_to_reclaim;
{
    Object class_1, slot_description, ab_loop_list_, ab_loop_desetq_;
    Object slot_init_form, temp, car_1, cdr_1, slot_value;
    char temp_1;

    x_note_fn_call(83,22);
    class_1 = Nil;
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions_to_reclaim;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    slot_description = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_init_form = ISVREF(slot_description,(SI_Long)6L);
    if (icon_description_slot_init_form_p(slot_init_form)) {
	temp = icon_owner_class_function(slot_init_form);
	if (EQ(temp,class_1)) {
	    Structure_being_reclaimed = slot_init_form;
	    reclaim_icon_description_of_slot_description(slot_init_form);
	}
    }
    else {
	if (CONSP(slot_init_form)) {
	    if ( !(INLINE_DOUBLE_FLOAT_VECTOR_P(slot_init_form) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_init_form)) == 
		    (SI_Long)1L)) {
		car_1 = M_CAR(slot_init_form);
		cdr_1 = M_CDR(slot_init_form);
		temp_1 = (slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1)) && 
			CONSP(cdr_1) ? EQ(M_CDR(cdr_1),
			Qdefault_slot_constant) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    slot_value = CAR(slot_init_form);
	    temp = slot_init_form;
	    slot_init_form = CDR(slot_init_form);
	    reclaim_slot_value_cons_1(temp);
	    reclaim_slot_value(slot_value);
	    reclaim_slot_value(slot_init_form);
	}
	else
	    reclaim_slot_value(slot_init_form);
    }
    SVREF(slot_description,FIX((SI_Long)6L)) = Nil;
    Structure_being_reclaimed = slot_description;
    reclaim_slot_description_1(slot_description);
    Structure_being_reclaimed = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qclass_description;  /* class-description */

/* RECLAIM-SLOT-DESCRIPTIONS-OF-CLASS-DESCRIPTION */
Object reclaim_slot_descriptions_of_class_description(class_description)
    Object class_description;
{
    Object slot_descriptions, class_1, slot_description, unique_slot_name;
    Object owner_class, class_description_pop_store, cons_1, next_cons, temp;
    Object svref_arg_2, scope_conses, ab_loopvar_, subclass;
    Object subclass_class_description_qm, subclass_slot_description_qm, temp_1;
    Object reclaim_argument;
    Declare_special(1);

    x_note_fn_call(83,23);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    class_1 = ISVREF(class_description,(SI_Long)1L);
    decache_cached_class_data(class_1);
    slot_description = Nil;
    unique_slot_name = Nil;
    owner_class = Nil;
  next_loop:
    if ( !TRUEP(slot_descriptions))
	goto end_loop;
    class_description_pop_store = Nil;
    cons_1 = slot_descriptions;
    if (cons_1) {
	class_description_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qclass_description);
	if (ISVREF(Available_class_description_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_class_description_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_class_description_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_class_description_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_class_description_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    slot_descriptions = next_cons;
    slot_description = class_description_pop_store;
    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
    owner_class = ISVREF(slot_description,(SI_Long)4L);
    if (EQ(owner_class,class_1)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = class_1;
	subclass = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  subclass_class_description_qm = Nil;
	  subclass_slot_description_qm = Nil;
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop_1:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_1;
	  temp_1 = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  subclass = temp_1;
	  subclass_class_description_qm = 
		  lookup_global_or_kb_specific_property_value(subclass,
		  Class_description_gkbprop);
	  subclass_slot_description_qm =  !EQ(subclass,class_1) ? 
		  (subclass_class_description_qm ? get_slot_description(2,
		  unique_slot_name,ISVREF(subclass_class_description_qm,
		  (SI_Long)6L)) : Nil) : Nil;
	  if (EQ(subclass_slot_description_qm,slot_description)) {
	      delete_class_description_element_from_slot_descriptions(subclass_slot_description_qm,
		      subclass_class_description_qm);
	      delete_slot_description_from_hash_table(subclass_slot_description_qm,
		      subclass_class_description_qm);
	  }
	  goto next_loop_1;
	end_loop_1:;
	POP_SPECIAL();
	reclaim_argument = frame_cons_1(frame_cons_1(class_1,
		slot_description),Nil);
	reclaim_list_of_slot_descriptions(reclaim_argument);
	reclaim_frame_tree_1(reclaim_argument);
    }
    goto next_loop;
  end_loop:;
    temp_1 = slot_descriptions_function(class_description,Nil);
    return VALUES_1(temp_1);
}

/* RECLAIM-CLASS-DESCRIPTION-OF-CLASS */
Object reclaim_class_description_of_class(class_1,class_description,
	    old_class_description_qm)
    Object class_1, class_description, old_class_description_qm;
{
    Object class_method_table_qm;

    x_note_fn_call(83,24);
    if (SIMPLE_VECTOR_P(class_description) && EQ(ISVREF(class_description,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct) &&  
	    !TRUEP(ISVREF(class_description,(SI_Long)20L))) {
	reclaim_icp_object_map_for_class_description(class_description);
	reclaim_slot_descriptions_of_class_description(class_description);
	class_method_table_qm = ISVREF(class_description,(SI_Long)11L);
	if (class_method_table_qm && EQ(ISVREF(class_method_table_qm,
		IFIX(Maximum_number_of_generic_methods)),class_1)) {
	    reclaim_method_table_of_class_description(class_method_table_qm);
	    SVREF(class_description,FIX((SI_Long)11L)) = Nil;
	}
	if ( !TRUEP(old_class_description_qm)) {
	    Class_bit_numbers_pool = frame_cons_1(ISVREF(class_description,
		    (SI_Long)18L),Class_bit_numbers_pool);
	    SVREF(class_description,FIX((SI_Long)18L)) = Nil;
	}
	reclaim_class_description_1(class_description);
	return mutate_global_or_kb_specific_property_value(class_1,Nil,
		Class_description_gkbprop);
    }
    else
	return VALUES_1(Nil);
}

/* RESET-WITHIN-DELETE-FRAME-SCOPE */
Object reset_within_delete_frame_scope()
{
    x_note_fn_call(83,25);
    Within_delete_frame_scope_qm = Nil;
    Queue_of_classes_to_be_undefined = Nil;
    return VALUES_1(Queue_of_classes_to_be_undefined);
}

Object Classes_to_delete_when_releasing_kb = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Releasing_kb_qm, Qreleasing_kb_qm);

/* PROCESS-CLASSES-QUEUED-BY-DELETE-FRAME */
Object process_classes_queued_by_delete_frame(class_list)
    Object class_list;
{
    x_note_fn_call(83,26);
    if (Releasing_kb_qm) {
	Classes_to_delete_when_releasing_kb = 
		nconc2(Classes_to_delete_when_releasing_kb,
		copy_list_using_frame_conses_1(class_list));
	return VALUES_1(Classes_to_delete_when_releasing_kb);
    }
    else
	return delete_classes_queued_by_delete_frame(class_list);
}

static Object Qitem;               /* item */

/* DELETE-CLASSES-QUEUED-BY-DELETE-FRAME */
Object delete_classes_queued_by_delete_frame(class_list)
    Object class_list;
{
    Object scope_conses, ab_loopvar_, subclass, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, temp, sorted_class_list;
    Declare_special(1);

    x_note_fn_call(83,27);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qitem;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      if (memq_function(subclass,class_list)) {
	  ab_loopvar__3 = frame_cons_1(subclass,Nil);
	  if (ab_loopvar__2)
	      M_CDR(ab_loopvar__2) = ab_loopvar__3;
	  else
	      ab_loopvar__1 = ab_loopvar__3;
	  ab_loopvar__2 = ab_loopvar__3;
      }
      goto next_loop;
    end_loop:
      temp = ab_loopvar__1;
      goto end_1;
      temp = Qnil;
    end_1:;
    POP_SPECIAL();
    sorted_class_list = nreverse(temp);
    reclaim_queued_class_descriptions(sorted_class_list);
    reclaim_frame_list_1(sorted_class_list);
    if (Releasing_kb_qm)
	return reclaim_frame_list_1(class_list);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-QUEUED-CLASS-DESCRIPTIONS */
Object reclaim_queued_class_descriptions(class_list)
    Object class_list;
{
    Object class_1, ab_loop_list_, class_description, class_method_table_qm;
    Object direct_superiors, superior, ab_loop_list__1, temp, temp_1;

    x_note_fn_call(83,28);
    class_1 = Nil;
    ab_loop_list_ = class_list;
    class_description = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    reclaim_icp_object_map_for_class_description(class_description);
    reclaim_slot_descriptions_of_class_description(class_description);
    class_method_table_qm = ISVREF(class_description,(SI_Long)11L);
    if (class_method_table_qm && EQ(ISVREF(class_method_table_qm,
	    IFIX(Maximum_number_of_generic_methods)),class_1)) {
	reclaim_method_table_of_class_description(class_method_table_qm);
	SVREF(class_description,FIX((SI_Long)11L)) = Nil;
    }
    goto next_loop;
  end_loop:;
    class_1 = Nil;
    ab_loop_list_ = class_list;
    class_description = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    Class_bit_numbers_pool = frame_cons_1(ISVREF(class_description,
	    (SI_Long)18L),Class_bit_numbers_pool);
    SVREF(class_description,FIX((SI_Long)18L)) = Nil;
    direct_superiors = lookup_global_or_kb_specific_property_value(class_1,
	    Direct_superior_classes_gkbprop);
    superior = Nil;
    ab_loop_list__1 = direct_superiors;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    superior = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = superior;
    temp_1 = delete_class_description_element_1(class_1,
	    lookup_global_or_kb_specific_property_value(superior,
	    Inferior_classes_gkbprop));
    mutate_global_or_kb_specific_property_value(temp,temp_1,
	    Inferior_classes_gkbprop);
    goto next_loop_2;
  end_loop_2:;
    reclaim_class_description_list_1(lookup_global_or_kb_specific_property_value(class_1,
	    Direct_superior_classes_gkbprop));
    mutate_global_or_kb_specific_property_value(class_1,Nil,
	    Direct_superior_classes_gkbprop);
    reclaim_class_description_list_1(lookup_global_or_kb_specific_property_value(class_1,
	    Inferior_classes_gkbprop));
    mutate_global_or_kb_specific_property_value(class_1,Nil,
	    Inferior_classes_gkbprop);
    reclaim_class_description_1(class_description);
    mutate_global_or_kb_specific_property_value(class_1,Nil,
	    Class_description_gkbprop);
    analyze_compiled_items_for_consistency(class_1);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_being_read_qm, Qframe_being_read_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Tracked_items_call_vector_table, Qtracked_items_call_vector_table);

DEFINE_VARIABLE_WITH_SYMBOL(Profiling_structure, Qprofiling_structure);

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qslot_value_reclaimer;  /* slot-value-reclaimer */

/* DELETE-FRAME */
Object delete_frame(frame)
    Object frame;
{
    Object sub_class_bit_vector, class_1;
    Object class_name_of_user_class_definition_frame_qm, class_description;
    Object slot_descriptions, frame_is_block_qm, frame_is_system_item_qm;
    Object already_within_delete_frame_qm, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_1, temp_2, entry_hash;
    Object gensymed_symbol_3, tail, head, new_cons, temp_3, svref_arg_2;
    Object svref_new_value_1, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, name_or_names, frame_1, sub_vector_qm, function_qm;
    Object current_block_of_dependent_frame, slot_description, ab_loop_list_;
    Object slot_value_qm, vector_slot_index_qm, user_vector_slot_index_qm;
    Object slot_name, lookup_structure_qm, slot_index_qm;
    Object slot_value_reclaimer_qm, lookup_structure, old;
    Object frame_vector_pool_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, method_index;
    SI_Long max_i, i, new_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(83,29);
    if (BOUNDP(Qframe_being_read_qm) && Frame_being_read_qm && 
	    ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L)) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    return delete_connection_after_reading_kb(frame);
	else
	    return delete_block_after_reading_kb(frame);
    }
    else {
	if (SIMPLE_VECTOR_P(frame) && EQ(ISVREF(frame,(SI_Long)1L),
		Qavailable_frame_vector))
	    return VALUES_1(Nil);
	class_1 = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	class_name_of_user_class_definition_frame_qm = temp ? 
		name_of_defined_class_function(frame) : Nil;
	class_description = ISVREF(frame,(SI_Long)1L);
	slot_descriptions = ISVREF(class_description,(SI_Long)6L);
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
	    frame_is_block_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    frame_is_block_qm = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(System_item_class_description,(SI_Long)18L));
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
	    frame_is_system_item_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    frame_is_system_item_qm = Nil;
	already_within_delete_frame_qm = Within_delete_frame_scope_qm;
	if (frame_is_system_item_qm) {
	    if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		    (SI_Long)512L))
		return VALUES_1(Nil);
	    else {
		svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | 
			(SI_Long)512L;
		ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
	    }
	    if (Tracked_items_call_vector_table)
		note_possibly_tracked_item_deletion(frame);
	    if (Profiling_structure)
		note_possibly_profiled_item_deletion(frame);
	}
	if ( !TRUEP(already_within_delete_frame_qm)) {
	    Within_delete_frame_scope_qm = T;
	    if (Queue_of_classes_to_be_undefined) {
		reclaim_frame_list_1(Queue_of_classes_to_be_undefined);
		Queue_of_classes_to_be_undefined = Nil;
	    }
	}
	if (class_name_of_user_class_definition_frame_qm) {
	    if (SYMBOLP(class_name_of_user_class_definition_frame_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_name_of_user_class_definition_frame_qm;
		key_hash_value = 
			SXHASH_SYMBOL_1(class_name_of_user_class_definition_frame_qm) 
			& IFIX(Most_positive_fixnum);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    gensymed_symbol_3 = 
			    class_name_of_user_class_definition_frame_qm;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			svref_new_value_1 = M_CDR(new_cons);
			SVREF(temp_3,svref_arg_2) = svref_new_value_1;
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
			svref_new_value_1 = M_CDR(new_cons);
			SVREF(temp_3,svref_arg_2) = svref_new_value_1;
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
		    gensymed_symbol_3 = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			    temp_2,gensymed_symbol_4);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp = TRUEP(resulting_value);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  
		!TRUEP(memq_function(class_name_of_user_class_definition_frame_qm,
		Queue_of_classes_to_be_undefined)) : TRUEP(Nil))
	    Queue_of_classes_to_be_undefined = 
		    nconc2(Queue_of_classes_to_be_undefined,
		    frame_cons_1(class_name_of_user_class_definition_frame_qm,
		    Nil));
	if (frame_is_block_qm) {
	    do_block_specific_deletion_stuff(frame);
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Object_definition_class_description,
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
		cleanup_for_stubs_for_class(frame);
	    name_or_names = get_slot_value_function(frame,
		    Qname_or_names_for_frame,Nil);
	    if (name_or_names)
		reclaim_name_or_names_for_frame_value(name_or_names,frame);
	}
	else {
	    method_index = (SI_Long)1L;
	    frame_1 = frame;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		    (SI_Long)11L),method_index);
	    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,
		    (SI_Long)1L) : Nil;
	    if (function_qm)
		inline_funcall_1(function_qm,frame_1);
	}
	send_notification_to_item_internal(frame,Qdelete);
	current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		0);
	  slot_description = Nil;
	  ab_loop_list_ = slot_descriptions;
	  slot_value_qm = Nil;
	next_loop_12:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_12;
	  slot_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	  if (vector_slot_index_qm)
	      slot_value_qm = ISVREF(frame,IFIX(vector_slot_index_qm));
	  else {
	      user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	      if (user_vector_slot_index_qm)
		  slot_value_qm = ISVREF(ISVREF(frame,(SI_Long)0L),
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
		    next_loop_13:
		      if (i >= ab_loop_bind_)
			  goto end_loop_13;
		      if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			  slot_index_qm = FIX(i + (SI_Long)1L);
			  goto end_5;
		      }
		      i = i + (SI_Long)2L;
		      goto next_loop_13;
		    end_loop_13:
		      slot_index_qm = Qnil;
		    end_5:;
		      slot_value_qm = slot_index_qm ? 
			      ISVREF(lookup_structure_qm,
			      IFIX(slot_index_qm)) : 
			      ISVREF(slot_description,(SI_Long)6L);
		  }
		  else
		      slot_value_qm = ISVREF(slot_description,(SI_Long)6L);
	      }
	  }
	  if ( !( !TRUEP(slot_value_qm) || FIXNUMP(slot_value_qm) || 
		  EQ(slot_value_qm,ISVREF(slot_description,(SI_Long)6L)) 
		  || frame_is_block_qm && EQ(ISVREF(slot_description,
		  (SI_Long)2L),Qname_or_names_for_frame))) {
	      slot_value_reclaimer_qm = ISVREF(slot_description,(SI_Long)11L);
	      if ( !TRUEP(slot_value_reclaimer_qm)) {
		  gensymed_symbol_3 = ISVREF(slot_description,(SI_Long)2L);
		  temp_2 = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_3),
			  Qslot_value_reclaimer);
		  if (temp_2);
		  else
		      temp_2 = FIX((SI_Long)0L);
		  slot_value_reclaimer_qm = temp_2;
		  SVREF(slot_description,FIX((SI_Long)11L)) = 
			  slot_value_reclaimer_qm;
	      }
	      if ( !EQ(slot_value_reclaimer_qm,FIX((SI_Long)0L)))
		  inline_funcall_2(slot_value_reclaimer_qm,slot_value_qm,
			  frame);
	      else if (ISVREF(slot_description,(SI_Long)8L))
		  reclaim_attribute_value(slot_value_qm,frame);
	      else if ( !SYMBOLP(slot_value_qm))
		  reclaim_slot_value(slot_value_qm);
	  }
	  goto next_loop_12;
	end_loop_12:;
	POP_SPECIAL();
	lookup_structure = ISVREF(frame,(SI_Long)0L);
	if (lookup_structure) {
	    reclaim_managed_simple_vector(lookup_structure);
	    SVREF(frame,FIX((SI_Long)0L)) = Nil;
	}
	if (frame_is_system_item_qm) {
	    old = ISVREF(frame,(SI_Long)3L);
	    new_1 = (SI_Long)-1L;
	    temp_3 = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(FIX(new_1)) ||  !TRUEP(FIX(new_1))) ? 
		    FIX(new_1) : frame_serial_number_setf_helper_1(old,
		    FIX(new_1));
	    ISVREF(frame,(SI_Long)3L) = temp_3;
	    reclaim_frame_serial_number(ISVREF(frame,(SI_Long)3L));
	    delete_from_instances_specific_to_this_class(class_1,frame);
	    gensymed_symbol_3 = frame;
	    gensymed_symbol = 
		    IFIX(FIXNUM_SUB1(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_3)));
	    frame_vector_pool_vector = ISVREF(Frame_vector_pool_array,
		    IFIX(Current_thread_index));
	    PUSH_SPECIAL_WITH_SYMBOL(Frame_vector_pool_vector,Qframe_vector_pool_vector,frame_vector_pool_vector,
		    0);
	      atomic_incff_symval(Qoutstanding_frame_vector_count,FIX( - 
		      (SI_Long)1L));
	      inline_note_reclaim_cons(gensymed_symbol_3,Nil);
	      SVREF(gensymed_symbol_3,FIX((SI_Long)1L)) = 
		      Qavailable_frame_vector;
	      temp_3 = ISVREF(Frame_vector_pool_vector,gensymed_symbol);
	      SVREF(gensymed_symbol_3,FIX((SI_Long)0L)) = temp_3;
	      temp_3 = Frame_vector_pool_vector;
	      ISVREF(temp_3,gensymed_symbol) = gensymed_symbol_3;
	    POP_SPECIAL();
	}
	else {
	    SVREF(frame,FIX((SI_Long)1L)) = Qavailable_frame_vector;
	    reclaim_managed_simple_vector(frame);
	}
	if (class_name_of_user_class_definition_frame_qm)
	    mutate_global_or_kb_specific_property_value(class_name_of_user_class_definition_frame_qm,
		    Nil,Class_definition_gkbprop);
	if ( !TRUEP(already_within_delete_frame_qm)) {
	    if (Queue_of_classes_to_be_undefined) {
		process_classes_queued_by_delete_frame(Queue_of_classes_to_be_undefined);
		reclaim_frame_list_1(Queue_of_classes_to_be_undefined);
		Queue_of_classes_to_be_undefined = Nil;
	    }
	    Within_delete_frame_scope_qm = Nil;
	    return VALUES_1(Within_delete_frame_scope_qm);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* DELETE-INSTANCES-SPECIFIC-TO-THIS-CLASS */
Object delete_instances_specific_to_this_class(class_1)
    Object class_1;
{
    Object reference_serial_number, ab_loopvar_, instance, ab_loopvar__1;
    Object ab_loopvar__2, ab_loopvar__3, instance_list, ab_loop_list_;
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(83,30);
    reference_serial_number = 
	    copy_frame_serial_number(Current_frame_serial_number);
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    ab_loopvar__3 = frame_cons_1(instance,Nil);
    if (ab_loopvar__2)
	M_CDR(ab_loopvar__2) = ab_loopvar__3;
    else
	ab_loopvar__1 = ab_loopvar__3;
    ab_loopvar__2 = ab_loopvar__3;
    goto next_loop;
  end_loop:
    instance_list = ab_loopvar__1;
    goto end_1;
    instance_list = Qnil;
  end_1:;
    instance = Nil;
    ab_loop_list_ = instance_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    instance = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(instance,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(instance) ? EQ(ISVREF(instance,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_serial_number,gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(instance);
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(reference_serial_number);
    reclaim_frame_list_1(instance_list);
    return VALUES_1(Qnil);
}

/* DELETE-CLASS-DESCRIPTION-ELEMENT-FROM-SLOT-DESCRIPTIONS */
Object delete_class_description_element_from_slot_descriptions(slot_description_being_deleted,
	    class_description)
    Object slot_description_being_deleted, class_description;
{
    Object slot_descriptions, first_slot_description, temp, sublist;
    Object slot_description, cdr_new_value;

    x_note_fn_call(83,31);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    first_slot_description = CAR(slot_descriptions);
    if (EQ(first_slot_description,slot_description_being_deleted)) {
	temp = slot_descriptions;
	slot_descriptions_function(class_description,CDR(slot_descriptions));
	return reclaim_class_description_cons_1(temp);
    }
    else {
	sublist = slot_descriptions;
	slot_description = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	slot_description = CADR(sublist);
	if (EQ(slot_description,slot_description_being_deleted)) {
	    temp = CDR(sublist);
	    cdr_new_value = CDDR(sublist);
	    M_CDR(sublist) = cdr_new_value;
	    reclaim_class_description_cons_1(temp);
	    goto end_loop;
	}
	sublist = M_CDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* DELETE-SLOT-DESCRIPTION-FROM-HASH-TABLE */
Object delete_slot_description_from_hash_table(slot_description,
	    class_description)
    Object slot_description, class_description;
{
    Object gensymed_symbol;

    x_note_fn_call(83,32);
    gensymed_symbol = class_description;
    if (EQ(ISVREF(gensymed_symbol,(SI_Long)17L),ISVREF(gensymed_symbol,
	    (SI_Long)1L)))
	delete_slot_description_from_full_hash_table(slot_description,
		class_description);
    else
	delete_slot_description_from_sparse_hash_table_if_present(slot_description,
		class_description);
    return VALUES_1(Nil);
}

/* DELETE-SLOT-DESCRIPTION-FROM-FULL-HASH-TABLE */
Object delete_slot_description_from_full_hash_table(slot_description,
	    class_description)
    Object slot_description, class_description;
{
    Object pretty_slot_name, slot_descriptions_hash_table;
    Object new_hash_table_value_for_pretty_slot_name_qm, gensymed_symbol;

    x_note_fn_call(83,33);
    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
    slot_descriptions_hash_table = ISVREF(class_description,(SI_Long)9L);
    new_hash_table_value_for_pretty_slot_name_qm = 
	    get_new_default_slot_description_with_pretty_name(slot_description,
	    class_description);
    gensymed_symbol = ISVREF(slot_description,(SI_Long)1L);
    delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),gensymed_symbol,
	    slot_descriptions_hash_table,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)));
    if (new_hash_table_value_for_pretty_slot_name_qm) {
	gensymed_symbol = pretty_slot_name;
	set_balanced_binary_tree_entry(slot_descriptions_hash_table,Qeq,
		Nil,T,gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
		& IFIX(Most_positive_fixnum)),
		new_hash_table_value_for_pretty_slot_name_qm);
    }
    else
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		pretty_slot_name,slot_descriptions_hash_table,
		FIX(SXHASH_SYMBOL_1(pretty_slot_name) & 
		IFIX(Most_positive_fixnum)));
    return VALUES_1(Nil);
}

/* DELETE-SLOT-DESCRIPTION-FROM-SPARSE-HASH-TABLE-IF-PRESENT */
Object delete_slot_description_from_sparse_hash_table_if_present(slot_description,
	    class_description)
    Object slot_description, class_description;
{
    Object pretty_slot_name, unique_slot_name, slot_descriptions_hash_table;
    Object new_hash_table_value_for_pretty_slot_name_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_4, temp;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(83,34);
    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
    slot_descriptions_hash_table = ISVREF(class_description,(SI_Long)9L);
    new_hash_table_value_for_pretty_slot_name_qm = 
	    get_new_default_slot_description_with_pretty_name(slot_description,
	    class_description);
    gensymed_symbol = CDR(slot_descriptions_hash_table);
    gensymed_symbol_1 = pretty_slot_name;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(pretty_slot_name) & 
	    IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    temp = M_CDR(M_CAR(gensymed_symbol));
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    if (EQ(temp,slot_description)) {
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		pretty_slot_name,slot_descriptions_hash_table,
		FIX(SXHASH_SYMBOL_1(pretty_slot_name) & 
		IFIX(Most_positive_fixnum)));
	if (new_hash_table_value_for_pretty_slot_name_qm) {
	    gensymed_symbol = pretty_slot_name;
	    set_balanced_binary_tree_entry(slot_descriptions_hash_table,
		    Qeq,Nil,T,gensymed_symbol,
		    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),
		    new_hash_table_value_for_pretty_slot_name_qm);
	}
    }
    gensymed_symbol = CDR(slot_descriptions_hash_table);
    gensymed_symbol_1 = unique_slot_name;
    gensymed_symbol_2 = SXHASH_SYMBOL_1(unique_slot_name) & 
	    IFIX(Most_positive_fixnum);
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop_2:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_2;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
    if (gensymed_symbol_2 < gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
    else if (gensymed_symbol_2 > gensymed_symbol_3)
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
    else {
	gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
	    temp = M_CDR(M_CAR(gensymed_symbol));
	    goto end_3;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop_3;
      end_loop_3:
	temp = Qnil;
      end_3:;
	goto end_4;
    }
    goto next_loop_2;
  end_loop_2:
    temp = Qnil;
  end_4:;
    if (EQ(temp,slot_description))
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		unique_slot_name,slot_descriptions_hash_table,
		FIX(SXHASH_SYMBOL_1(unique_slot_name) & 
		IFIX(Most_positive_fixnum)));
    return VALUES_1(Nil);
}

/* DETERMINE-POSSIBLE-PARENT-ATTRIBUTE-NAME-CHANGES */
Object determine_possible_parent_attribute_name_changes(user_class,
	    new_attribute_name)
    Object user_class, new_attribute_name;
{
    Object scope_conses, ab_loopvar_, subclass, temp, class_description;
    Object new_attribute_slot_description, ab_loopvar__1, instance, slot_value;
    Object x2, current_parent_attribute_name;
    Object new_attribute_name_needs_qualification_qm;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(83,35);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = user_class;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      if (instantiated_class_p(subclass)) {
	  class_description = 
		  lookup_global_or_kb_specific_property_value(subclass,
		  Class_description_gkbprop);
	  new_attribute_slot_description = 
		  get_slot_description_of_class_description_function(new_attribute_name,
		  class_description,user_class);
	  ab_loopvar__1 = lookup_kb_specific_property_value(subclass,
		  Instances_specific_to_this_class_kbprop);
	  instance = Nil;
	  slot_value = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loopvar__1))
	      goto end_loop_1;
	  instance = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  slot_value = get_slot_description_value(instance,
		  new_attribute_slot_description);
	  if (SIMPLE_VECTOR_P(slot_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(slot_value,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      current_parent_attribute_name = 
		      get_lookup_slot_value_given_default(slot_value,
		      Qparent_attribute_name,Nil);
	      if ( ! !TRUEP(ISVREF(new_attribute_slot_description,
		      (SI_Long)8L))) {
		  temp = ISVREF(new_attribute_slot_description,(SI_Long)3L);
		  new_attribute_name_needs_qualification_qm =  !EQ(temp,
			  ISVREF(get_slot_description_of_class_description_function(ISVREF(new_attribute_slot_description,
			  (SI_Long)2L),class_description,Nil),
			  (SI_Long)3L)) ? T : Nil;
	      }
	      else
		  new_attribute_name_needs_qualification_qm = Nil;
	      set_non_savable_lookup_slot_value(slot_value,
		      Qparent_attribute_name,
		      new_attribute_name_needs_qualification_qm ? 
		      slot_value_cons_1(new_attribute_name,user_class) : 
		      new_attribute_name);
	      reclaim_slot_value(current_parent_attribute_name);
	  }
	  goto next_loop_1;
	end_loop_1:;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qab_slot_value;      /* slot-value */

/* ADD-CLASS-QUALIFIER-TO-PARENT-ATTRIBUTE-NAMES-IF-NECESSARY */
Object add_class_qualifier_to_parent_attribute_names_if_necessary(user_class,
	    attribute_name)
    Object user_class, attribute_name;
{
    Object scope_conses, ab_loopvar_, subclass, existing_slot_description_qm;
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, class_description, class_inheritance_path;
    Object ab_loopvar__1, instance, slot_value, x2, class_inheritance_path_1;
    Object current_parent_attribute_name;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(83,36);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = user_class;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      existing_slot_description_qm = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      skip_list = CDR(Symbol_properties_table);
      key_value = subclass;
      key_hash_value = SXHASH_SYMBOL_1(subclass) & IFIX(Most_positive_fixnum);
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
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_2:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_3:
      if ( !TRUEP(marked))
	  goto end_loop_2;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_3;
    end_loop_2:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if ( !TRUEP(gensymed_symbol)) {
	  gensymed_symbol = subclass;
	  temp_1 = Symbol_properties_table;
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
	      temp_2 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp_2,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp_2 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = Nil;
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
	      temp_2 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp_2,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp_2 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = Nil;
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
	  gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		  Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
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
    next_loop_4:
      if (level < ab_loop_bind_)
	  goto end_loop_4;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_5:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_6:
      if ( !TRUEP(marked))
	  goto end_loop_5;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_6;
    end_loop_5:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if (kb_properties);
      else
	  kb_properties = Nil;
      if (kb_properties) {
	  skip_list = CDR(kb_properties);
	  key_value = Class_description_gkbprop;
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_7:
	  if (level < ab_loop_bind_)
	      goto end_loop_7;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_8:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_9:
	  if ( !TRUEP(marked))
	      goto end_loop_8;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_9;
	end_loop_8:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_3;
	  goto next_loop_8;
	end_loop_9:
	end_3:
	  level = level - (SI_Long)1L;
	  goto next_loop_7;
	end_loop_7:;
	  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_10:
	  if (level < ab_loop_bind_)
	      goto end_loop_10;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_11:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_12:
	  if ( !TRUEP(marked))
	      goto end_loop_11;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_12;
	end_loop_11:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_4;
	  goto next_loop_11;
	end_loop_12:
	end_4:
	  level = level - (SI_Long)1L;
	  goto next_loop_10;
	end_loop_10:;
	  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if (resulting_value);
	  else
	      resulting_value = Nil;
      }
      gensymed_symbol = resulting_value;
      existing_slot_description_qm = 
	      get_slot_description_of_class_description_function(attribute_name,
	      gensymed_symbol,Nil);
      if (existing_slot_description_qm) {
	  class_description = 
		  lookup_global_or_kb_specific_property_value(subclass,
		  Class_description_gkbprop);
	  class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
	  ab_loopvar__1 = lookup_kb_specific_property_value(subclass,
		  Instances_specific_to_this_class_kbprop);
	  instance = Nil;
	  slot_value = Nil;
	next_loop_13:
	  if ( !TRUEP(ab_loopvar__1))
	      goto end_loop_13;
	  instance = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  slot_value = get_slot_description_value(instance,
		  existing_slot_description_qm);
	  if (SIMPLE_VECTOR_P(slot_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(slot_value,(SI_Long)1L);
	      temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3) {
	      class_inheritance_path_1 = class_inheritance_path;
	      temp = position(2,user_class,class_inheritance_path_1);
	      temp_3 = FIXNUM_LT(temp,position(2,
		      ISVREF(existing_slot_description_qm,(SI_Long)3L),
		      class_inheritance_path_1));
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3) {
	      current_parent_attribute_name = 
		      get_lookup_slot_value_given_default(slot_value,
		      Qparent_attribute_name,Nil);
	      temp = slot_value;
	      new_cons = ISVREF(Available_slot_value_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp_2 = Available_slot_value_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp_2,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp_2 = Available_slot_value_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp_2,svref_arg_2) = Nil;
		  }
		  gensymed_symbol = new_cons;
	      }
	      else
		  gensymed_symbol = Nil;
	      if ( !TRUEP(gensymed_symbol))
		  gensymed_symbol = replenish_slot_value_cons_pool();
	      M_CAR(gensymed_symbol) = attribute_name;
	      temp_2 = ISVREF(existing_slot_description_qm,(SI_Long)3L);
	      M_CDR(gensymed_symbol) = temp_2;
	      inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	      set_non_savable_lookup_slot_value(temp,
		      Qparent_attribute_name,gensymed_symbol);
	      reclaim_slot_value(current_parent_attribute_name);
	  }
	  goto next_loop_13;
	end_loop_13:;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* REMOVE-CLASS-QUALIFIER-FROM-PARENT-ATTRIBUTE-NAMES-IF-NECESSARY */
Object remove_class_qualifier_from_parent_attribute_names_if_necessary(user_class,
	    attribute_name)
    Object user_class, attribute_name;
{
    Object scope_conses, ab_loopvar_, subclass, existing_slot_description_qm;
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, ab_loopvar__1, instance;
    Object slot_value, x2, current_parent_attribute_name;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(83,37);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = user_class;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      existing_slot_description_qm = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      skip_list = CDR(Symbol_properties_table);
      key_value = subclass;
      key_hash_value = SXHASH_SYMBOL_1(subclass) & IFIX(Most_positive_fixnum);
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
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_2:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_3:
      if ( !TRUEP(marked))
	  goto end_loop_2;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_3;
    end_loop_2:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if ( !TRUEP(gensymed_symbol)) {
	  gensymed_symbol = subclass;
	  temp_1 = Symbol_properties_table;
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
	  gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		  Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
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
    next_loop_4:
      if (level < ab_loop_bind_)
	  goto end_loop_4;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_5:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_6:
      if ( !TRUEP(marked))
	  goto end_loop_5;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_6;
    end_loop_5:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if (kb_properties);
      else
	  kb_properties = Nil;
      if (kb_properties) {
	  skip_list = CDR(kb_properties);
	  key_value = Class_description_gkbprop;
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_7:
	  if (level < ab_loop_bind_)
	      goto end_loop_7;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_8:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_9:
	  if ( !TRUEP(marked))
	      goto end_loop_8;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_9;
	end_loop_8:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_3;
	  goto next_loop_8;
	end_loop_9:
	end_3:
	  level = level - (SI_Long)1L;
	  goto next_loop_7;
	end_loop_7:;
	  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_10:
	  if (level < ab_loop_bind_)
	      goto end_loop_10;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_11:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_12:
	  if ( !TRUEP(marked))
	      goto end_loop_11;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_12;
	end_loop_11:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_4;
	  goto next_loop_11;
	end_loop_12:
	end_4:
	  level = level - (SI_Long)1L;
	  goto next_loop_10;
	end_loop_10:;
	  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if (resulting_value);
	  else
	      resulting_value = Nil;
      }
      gensymed_symbol = resulting_value;
      existing_slot_description_qm = 
	      get_slot_description_of_class_description_function(attribute_name,
	      gensymed_symbol,Nil);
      if (existing_slot_description_qm) {
	  ab_loopvar__1 = lookup_kb_specific_property_value(subclass,
		  Instances_specific_to_this_class_kbprop);
	  instance = Nil;
	  slot_value = Nil;
	next_loop_13:
	  if ( !TRUEP(ab_loopvar__1))
	      goto end_loop_13;
	  instance = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  slot_value = get_slot_description_value(instance,
		  existing_slot_description_qm);
	  if (SIMPLE_VECTOR_P(slot_value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(slot_value,(SI_Long)1L);
	      temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      current_parent_attribute_name = 
		      get_lookup_slot_value_given_default(slot_value,
		      Qparent_attribute_name,Nil);
	      set_non_savable_lookup_slot_value(slot_value,
		      Qparent_attribute_name,attribute_name);
	      reclaim_slot_value(current_parent_attribute_name);
	  }
	  goto next_loop_13;
	end_loop_13:;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-ATTRIBUTE-VALUE */
Object reclaim_attribute_value(attribute_value,frame)
    Object attribute_value, frame;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_4, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(83,38);
    if (SIMPLE_VECTOR_P(attribute_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(attribute_value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(attribute_value,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	remove_variable_from_simulation(attribute_value);
    if (SIMPLE_VECTOR_P(attribute_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(attribute_value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(attribute_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		get_lookup_slot_value_given_default(attribute_value,
		Qparent_attribute_name,Nil);
	set_non_savable_lookup_slot_value(attribute_value,Qparent_frame,Nil);
	gensymed_symbol = 
		get_lookup_slot_value_given_default(attribute_value,
		Qparent_attribute_name,Nil);
	if (Nil) {
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
	    M_CAR(gensymed_symbol_4) = Nil;
	    M_CDR(gensymed_symbol_4) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_4,Qab_slot_value);
	    temp_1 = gensymed_symbol_4;
	}
	else
	    temp_1 = Nil;
	set_non_savable_lookup_slot_value(attribute_value,
		Qparent_attribute_name,temp_1);
	reclaim_slot_value(gensymed_symbol);
	return delete_frame(attribute_value);
    }
    else
	return reclaim_slot_value(attribute_value);
}

static Object Qloose_end;          /* loose-end */

/* SERVE-ITEM-P */
Object serve_item_p(item)
    Object item;
{
    Object local_current_computation_flags, class_description, gensymed_symbol;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(83,39);
    local_current_computation_flags = Current_computation_flags;
    class_description = ISVREF(item,(SI_Long)1L);
    if (ISVREF(class_description,(SI_Long)16L) || 
	    (IFIX(Current_computation_flags) & (SI_Long)4096L) != 
	    (SI_Long)0L && EQ(ISVREF(class_description,(SI_Long)1L),
	    Qloose_end)) {
	temp = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & (SI_Long)1L);
	if (temp);
	else {
	    gensymed_symbol = ISVREF(item,(SI_Long)3L);
	    if ( !(FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil))) {
		temp = (IFIX(local_current_computation_flags) & 
			(SI_Long)16L) != (SI_Long)0L;
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Kb_workspace_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if ((temp ?  !((IFIX(local_current_computation_flags) & 
	    (SI_Long)2048L) != (SI_Long)0L) || (SI_Long)0L != 
	    (IFIX(ISVREF(item,(SI_Long)4L)) & (SI_Long)1L) : TRUEP(Nil)) ? 
	     !((IFIX(local_current_computation_flags) & (SI_Long)32L) != 
	    (SI_Long)0L) || item_remotely_modifiable_p(item) : TRUEP(Nil)) {
	temp_1 =  !((IFIX(local_current_computation_flags) & (SI_Long)64L) 
		!= (SI_Long)0L) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = item_remotely_visible_p(item);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qitem_reference;     /* item-reference */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qdefined_evaluation_type_validator;  /* defined-evaluation-type-validator */

/* VALIDATE-ITEM-OR-EVALUATION-VALUE */
Object validate_item_or_evaluation_value(value,frame_serial_number_qm,
	    type_spec_for_validation_qm)
    Object value, frame_serial_number_qm, type_spec_for_validation_qm;
{
    Object temp, thing, gensymed_symbol, xa, ya, possible_type_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object defined_evaluation_value_type_qm, validator_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(83,40);
    if (CONSP(value) && EQ(M_CDR(value),Qitem_reference))
	temp = ISVREF(M_CAR(value),(SI_Long)3L);
    else if ( !TRUEP(frame_serial_number_qm))
	temp = value;
    else {
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L) {
	    temp_1 = EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector);
	    if (temp_1);
	    else {
		thing = ISVREF(value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			: TRUEP(Qnil);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(value,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(value) ? EQ(ISVREF(value,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number_qm))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number_qm,gensymed_symbol) :
			 TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number_qm);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number_qm),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    temp = (( !temp_1 ? TRUEP(serve_item_p(value)) : TRUEP(Nil)) ? 
		     !TRUEP(type_spec_for_validation_qm) || 
		    (EQ(type_spec_for_validation_qm,Qitem_or_datum) || 
		    valid_class_type_specification_p(type_spec_for_validation_qm)) 
		    && type_specification_type_p(value,
		    type_spec_for_validation_qm) : TRUEP(Nil)) ? value : Nil;
	}
	else {
	    if (CONSP(value)) {
		possible_type_name = M_CDR(value);
		if (SYMBOLP(possible_type_name)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = possible_type_name;
		    key_hash_value = SXHASH_SYMBOL_1(possible_type_name) & 
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
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
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
		    defined_evaluation_value_type_qm = IFIX(ISVREF(curr,
			    (SI_Long)1L)) == key_hash_value ? 
			    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		}
		else
		    defined_evaluation_value_type_qm = Nil;
	    }
	    else
		defined_evaluation_value_type_qm = Nil;
	    validator_qm = defined_evaluation_value_type_qm ? 
		    get_property_value_function(3,
		    get_symbol_properties_function(M_CDR(value)),
		    Qdefined_evaluation_type_validator,Nil) : Qnil;
	    if (validator_qm)
		temp = inline_funcall_2(validator_qm,value,
			frame_serial_number_qm);
	    else if (type_spec_for_validation_qm)
		temp = (EQ(type_spec_for_validation_qm,Qitem_or_datum) || 
			valid_datum_type_specification_p(type_spec_for_validation_qm)) 
			&& type_specification_type_p(value,
			type_spec_for_validation_qm) ? value : Qnil;
	    else
		temp = value;
	}
    }
    return VALUES_1(temp);
}

void frames2a_INIT()
{
    Object temp, temp_1;
    Object AB_package, Qreset_within_delete_frame_scope, Qframes2a;
    Object Qgeneric_method_lambda_list, list_constant_5, Qcleanup, Qkb_frame;
    Object Qreclaim_parent_frame_value, string_constant_24, list_constant_4;
    Object string_constant_18, string_constant_23, string_constant_22;
    Object Qexported_system_item, string_constant_17, string_constant_21;
    Object Qui_client_item, string_constant_20, string_constant_19;
    Object list_constant_3, Qsystem_item, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object string_constant_16, Qframe_vector_memory_usage, list_constant_2;
    Object Qframe_vector_pool_counts_vector, Qcreate_frame_vector_pool_vector;
    Object list_constant_1, Qframe_vector_pool_array;
    Object Qcreate_frame_vector_pool_array;
    Object Qinstances_specific_to_this_class_tail_pointer;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qinstances_specific_to_this_class;
    Object Qreclaim_frame_serial_number_value, Qframe_serial_number;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object list_constant, Qframe_serial_number_recycled_function;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant, Qroot;

    x_note_fn_call(83,41);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    list_constant = STATIC_CONS(Qroot,Qnil);
    check_if_superior_classes_are_defined(Qsystem_item,list_constant);
    string_constant = STATIC_STRING("1l1l8t");
    Qframe_serial_number_recycled_function = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-RECYCLED-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_serial_number_recycled_function,
	    STATIC_FUNCTION(frame_serial_number_recycled_function,NIL,
	    FALSE,0,0));
    string_constant_1 = 
	    STATIC_STRING("1v4z8r83AQy83AQy833ay833ay00001p1m8p83AQy1l8o1l8l1l83Cy1l83Uy000004z8r83MDy83MDy833ay833ay01m83*Ay9k001n1l8o1l8l1m83Dy5sInternal");
    string_constant_2 = 
	    STATIC_STRING("000004z8r83-Ey83-Ey833ay833ay0k001q1l8l1l8o1m8p01l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I think i");
    string_constant_3 = 
	    STATIC_STRING("ndividual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be supported");
    string_constant_4 = 
	    STATIC_STRING(". This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83MBy83MBy833ay833ay0k001m1l8l1l8o0000");
    string_constant_5 = 
	    STATIC_STRING("04z8r83I+y83I+y833ay833ay00001n1l8o1l8l1m83Dy5sInternal000004z8r83I-y83I-y833ay833ay00001n1l8o1l8l1m83Dy5sInternal000004z8r83XZy");
    string_constant_6 = 
	    STATIC_STRING("83XZy833ay833ay00001m1l8l1m83Dy53-fyBackpointer to frame which holds this item. ~\n Depending on the type of frame this may be of");
    string_constant_7 = 
	    STATIC_STRING(" value to export.000004z8r839fy839fy833ay833ay00001m1l8l1m83Dy53-3yThe name of the attribute in the ~\n parent-frame which holds ");
    string_constant_8 = 
	    STATIC_STRING("this item.000004z8r83X5y83X5y833ay833ay00001n1l8l1l83Ey1l83Hy000004z8r83Gsy83Gsy833ay833ay00001n1l8l1l83Ey1l83Hy000004z8r83Suy83");
    string_constant_9 = 
	    STATIC_STRING("Suy833ay833ay00001n1l8l1l83Ey1l83Hy00000");
    string_constant_10 = 
	    STATIC_STRING("1x8q1n833ay1l83Epy8t1r83AQy01m8p83AQy8o8l83Cy83Uy1p83MDy1m83*Ay9k8o8l1m83Dy5sInternal1s83-Eyk8l8o1m8p083Hy83*8y1m83Dy5305yCurren");
    string_constant_11 = 
	    STATIC_STRING("tly frame-flags is aliased ~\nto options. I think individual attribute-mimics should be created for ~\nparticular flags, and I don");
    string_constant_12 = 
	    STATIC_STRING("\'t know if options should continue to be supported. This\ncomment should show up on options, despite it being placed on frame-fla");
    string_constant_13 = 
	    STATIC_STRING("gs.1o83MByk8l8o1p83I+y08o8l1m83Dy5sInternal1p83I-y08o8l1m83Dy5sInternal1o83XZy08l1m83Dy53-fyBackpointer to frame which holds thi");
    string_constant_14 = 
	    STATIC_STRING("s item. ~\n Depending on the type of frame this may be of value to export.1o839fy08l1m83Dy53-3yThe name of the attribute in the ~");
    string_constant_15 = 
	    STATIC_STRING("\n parent-frame which holds this item.1p83X5y08l83Ey83Hy1p83Gsy08l83Ey83Hy1p83Suy08l83Ey83Hy");
    temp = regenerate_optimized_constant(string_constant);
    clear_optimized_constants();
    push_optimized_constant(Qframe_serial_number_recycled_function);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_1,
	    string_constant_2,string_constant_3,string_constant_4,
	    string_constant_5,string_constant_6,string_constant_7,
	    string_constant_8,string_constant_9));
    clear_optimized_constants();
    push_optimized_constant(Qframe_serial_number_recycled_function);
    add_class_to_environment(9,Qsystem_item,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,regenerate_optimized_constant(list(6,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15)),Nil);
    System_item_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsystem_item,
	    Class_description_gkbprop);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qreclaim_frame_serial_number_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qframe_serial_number,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_value),
	    Qslot_value_reclaimer);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qinstances_specific_to_this_class = 
	    STATIC_SYMBOL("INSTANCES-SPECIFIC-TO-THIS-CLASS",AB_package);
    Kb_specific_property_names = CONS(Qinstances_specific_to_this_class,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qinstances_specific_to_this_class,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Instances_specific_to_this_class_kbprop = 
	    Qinstances_specific_to_this_class;
    Qinstances_specific_to_this_class_tail_pointer = 
	    STATIC_SYMBOL("INSTANCES-SPECIFIC-TO-THIS-CLASS-TAIL-POINTER",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qinstances_specific_to_this_class_tail_pointer,
	    Kb_specific_property_names);
    mutate_global_property(Qinstances_specific_to_this_class_tail_pointer,
	    T,Qdo_not_carry_global_property_value_into_kbs_qm);
    Instances_specific_to_this_class_tail_pointer_kbprop = 
	    Qinstances_specific_to_this_class_tail_pointer;
    if (Class_specific_instances_lock == UNBOUND)
	Class_specific_instances_lock = make_lock(0);
    Largest_frame_vector_size = FIX((SI_Long)100L);
    Qframe_vector_pool_array = STATIC_SYMBOL("FRAME-VECTOR-POOL-ARRAY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_vector_pool_array,
	    Frame_vector_pool_array);
    Qframes2a = STATIC_SYMBOL("FRAMES2A",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qcreate_frame_vector_pool_array = 
	    STATIC_SYMBOL("CREATE-FRAME-VECTOR-POOL-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_frame_vector_pool_array,
	    STATIC_FUNCTION(create_frame_vector_pool_array,NIL,FALSE,1,1));
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qcreate_frame_vector_pool_array,Qnil);
    record_system_variable(Qframe_vector_pool_array,Qframes2a,
	    list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qframe_vector_pool_counts_vector = 
	    STATIC_SYMBOL("FRAME-VECTOR-POOL-COUNTS-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_vector_pool_counts_vector,
	    Frame_vector_pool_counts_vector);
    Qcreate_frame_vector_pool_vector = 
	    STATIC_SYMBOL("CREATE-FRAME-VECTOR-POOL-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_frame_vector_pool_vector,
	    STATIC_FUNCTION(create_frame_vector_pool_vector,NIL,FALSE,1,1));
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qcreate_frame_vector_pool_vector,FIX((SI_Long)0L));
    record_system_variable(Qframe_vector_pool_counts_vector,Qframes2a,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qframe_vector_count = STATIC_SYMBOL("FRAME-VECTOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_vector_count,Frame_vector_count);
    record_system_variable(Qframe_vector_count,Qframes2a,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qoutstanding_frame_vector_count = 
	    STATIC_SYMBOL("OUTSTANDING-FRAME-VECTOR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutstanding_frame_vector_count,
	    Outstanding_frame_vector_count);
    record_system_variable(Qoutstanding_frame_vector_count,Qframes2a,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qframe_vector_memory_used = STATIC_SYMBOL("FRAME-VECTOR-MEMORY-USED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_vector_memory_used,
	    Frame_vector_memory_used);
    record_system_variable(Qframe_vector_memory_used,Qframes2a,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qframe_vector_memory_usage = STATIC_SYMBOL("FRAME-VECTOR-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qframe_vector_memory_usage,
	    STATIC_FUNCTION(frame_vector_memory_usage,NIL,FALSE,0,0));
    string_constant_16 = STATIC_STRING("1q83-V7y83*9y83-V6y83-i5y09k");
    clear_optimized_constants();
    push_optimized_constant(Qframe_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Frame_vectors_to_make_at_a_time = FIX((SI_Long)5L);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    if (Do_not_initialize_specializations == UNBOUND)
	Do_not_initialize_specializations = Nil;
    if (Uuid_for_next_frame_qm == UNBOUND)
	Uuid_for_next_frame_qm = Nil;
    if (Class_description_for_next_frame_qm == UNBOUND)
	Class_description_for_next_frame_qm = Nil;
    Qframe_being_made = STATIC_SYMBOL("FRAME-BEING-MADE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_being_made,Frame_being_made);
    record_system_variable(Qframe_being_made,Qframes2a,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunique_identification = STATIC_SYMBOL("UNIQUE-IDENTIFICATION",AB_package);
    Qpreviously_put_in_attribute_tables = 
	    STATIC_SYMBOL("PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qdo_not_put_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qnot_ent = STATIC_SYMBOL("NOT-ENT",AB_package);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    Qnot_nupec = STATIC_SYMBOL("NOT-NUPEC",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_3 = STATIC_CONS(Qsystem_item,Qnil);
    check_if_superior_classes_are_defined(Qitem,list_constant_3);
    string_constant_17 = STATIC_STRING("1o1m8v83Ry1l83Ly1l83-8y1l83Iy");
    string_constant_18 = STATIC_STRING("0");
    string_constant_19 = 
	    STATIC_STRING("1m8q1q83Ry1l833ay1m8v83Ry83Ly83-8y83Iy");
    temp = regenerate_optimized_constant(string_constant_17);
    temp_1 = regenerate_optimized_constant(string_constant_18);
    add_class_to_environment(9,Qitem,list_constant_3,Nil,temp,Nil,temp_1,
	    list_constant_3,
	    regenerate_optimized_constant(string_constant_19),Nil);
    Item_class_description = 
	    lookup_global_or_kb_specific_property_value(Qitem,
	    Class_description_gkbprop);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    list_constant_4 = STATIC_CONS(Qitem,Qnil);
    check_if_superior_classes_are_defined(Qui_client_item,list_constant_4);
    string_constant_20 = STATIC_STRING("1m1l83Ly1l83Iy");
    string_constant_21 = STATIC_STRING("1m8q1o836Py1l83Ry83Ly83Iy");
    temp = regenerate_optimized_constant(string_constant_20);
    temp_1 = regenerate_optimized_constant(string_constant_18);
    add_class_to_environment(9,Qui_client_item,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_21),Nil);
    Qexported_system_item = STATIC_SYMBOL("EXPORTED-SYSTEM-ITEM",AB_package);
    check_if_superior_classes_are_defined(Qexported_system_item,
	    list_constant_4);
    string_constant_22 = 
	    STATIC_STRING("1m8q1q838Iy1l83Ry1m8v83Ry83Ly83-8y83Iy");
    temp = regenerate_optimized_constant(string_constant_17);
    temp_1 = regenerate_optimized_constant(string_constant_18);
    add_class_to_environment(9,Qexported_system_item,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_22),Nil);
    check_if_superior_classes_are_defined(Qunique_identification,
	    list_constant_4);
    string_constant_23 = STATIC_STRING("1p1m8v83Ry1l8t1l83-8y1l83Ly1l83Iy");
    string_constant_24 = 
	    STATIC_STRING("1m8q1r83-Fcy1l83Ry1m8v83Ry8t83-8y83Ly83Iy");
    temp = regenerate_optimized_constant(string_constant_23);
    temp_1 = regenerate_optimized_constant(string_constant_18);
    add_class_to_environment(9,Qunique_identification,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_24),Nil);
    Active_flag = FIX((SI_Long)1L);
    Frame_being_deleted_flag = FIX((SI_Long)512L);
    Permanent_block_flag = FIX((SI_Long)1L);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qreclaim_parent_frame_value = 
	    STATIC_SYMBOL("RECLAIM-PARENT-FRAME-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_parent_frame_value,
	    STATIC_FUNCTION(reclaim_parent_frame_value,NIL,FALSE,2,2));
    mutate_global_property(Qparent_frame,
	    SYMBOL_FUNCTION(Qreclaim_parent_frame_value),
	    Qslot_value_reclaimer);
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    list_constant_5 = STATIC_CONS(Qkb_frame,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qcleanup,list_constant_5,
	    Qgeneric_method_lambda_list);
    Qqueue_of_classes_to_be_undefined = 
	    STATIC_SYMBOL("QUEUE-OF-CLASSES-TO-BE-UNDEFINED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_of_classes_to_be_undefined,
	    Queue_of_classes_to_be_undefined);
    record_system_variable(Qqueue_of_classes_to_be_undefined,Qframes2a,Nil,
	    Qnil,Qnil,Qnil,Qt);
    Qwithin_delete_frame_scope_qm = 
	    STATIC_SYMBOL("WITHIN-DELETE-FRAME-SCOPE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwithin_delete_frame_scope_qm,
	    Within_delete_frame_scope_qm);
    record_system_variable(Qwithin_delete_frame_scope_qm,Qframes2a,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qdefault_slot_constant = STATIC_SYMBOL("DEFAULT-SLOT-CONSTANT",AB_package);
    Qclass_description = STATIC_SYMBOL("CLASS-DESCRIPTION",AB_package);
    Qreset_within_delete_frame_scope = 
	    STATIC_SYMBOL("RESET-WITHIN-DELETE-FRAME-SCOPE",AB_package);
    SET_SYMBOL_FUNCTION(Qreset_within_delete_frame_scope,
	    STATIC_FUNCTION(reset_within_delete_frame_scope,NIL,FALSE,0,0));
    def_bombout_clean_up_function(Qreset_within_delete_frame_scope);
    Classes_to_delete_when_releasing_kb = Nil;
    Qframe_being_read_qm = STATIC_SYMBOL("FRAME-BEING-READ\?",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_being_read_qm,Frame_being_read_qm);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qdefined_evaluation_type_validator = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-VALIDATOR",AB_package);
}
