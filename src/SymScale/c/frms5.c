/* frms5.c
 * Input file:  frames5.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms5.h"


static Object Qframe_representations;  /* frame-representations */

/* ADD-FRAME-REPRESENTATION-IF-NECESSARY */
Object add_frame_representation_if_necessary(representation_frame,frame)
    Object representation_frame, frame;
{
    Object svref_new_value;

    x_note_fn_call(87,0);
    if ( !TRUEP(memq_function(representation_frame,ISVREF(frame,
		(SI_Long)9L)))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_representations);
	svref_new_value = slot_value_cons_1(representation_frame,
		ISVREF(frame,(SI_Long)9L));
	return VALUES_1(SVREF(frame,FIX((SI_Long)9L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-FROM-FRAME-REPRESENTATIONS-IF-PRESENT */
Object remove_from_frame_representations_if_present(representation_frame,frame)
    Object representation_frame, frame;
{
    Object svref_new_value;

    x_note_fn_call(87,1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qframe_representations);
    svref_new_value = delete_slot_value_element_1(representation_frame,
	    ISVREF(frame,(SI_Long)9L));
    return VALUES_1(SVREF(frame,FIX((SI_Long)9L)) = svref_new_value);
}

static Object Qrepresentation;     /* representation */

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* RECLAIM-FRAME-REPRESENTATIONS-VALUE */
Object reclaim_frame_representations_value(frame_representations,frame)
    Object frame_representations, frame;
{
    Object representation_frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, gensymed_symbol_4, serial_number, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(87,2);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qframe_representations);
    SVREF(frame,FIX((SI_Long)9L)) = Nil;
    representation_frame = Nil;
    ab_loop_list_ = frame_representations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation_frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !((SI_Long)0L != (IFIX(ISVREF(representation_frame,(SI_Long)5L)) 
	    & (SI_Long)512L))) {
	gensymed_symbol = ISVREF(representation_frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Explanation_table_class_description,(SI_Long)18L));
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
	    detach_table_from_frames_it_represents(representation_frame);
	else {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qrepresentation,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		serial_number = 
			copy_frame_serial_number(ISVREF(representation_frame,
			(SI_Long)3L));
		if ( !((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
			(SI_Long)512L)))
		    send_representation_deletion_notification(representation_frame);
		gensymed_symbol = ISVREF(representation_frame,(SI_Long)3L);
		temp = SIMPLE_VECTOR_P(representation_frame) ? 
			EQ(ISVREF(representation_frame,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else if (FIXNUMP(serial_number))
		    temp = FIXNUMP(gensymed_symbol) ? 
			    FIXNUM_LT(serial_number,gensymed_symbol) : 
			    TRUEP(T);
		else if (FIXNUMP(gensymed_symbol))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(serial_number);
		    ya = M_CAR(gensymed_symbol);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(serial_number),
				M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		}
		if ( !temp)
		    delete_representation(1,representation_frame);
		reclaim_frame_serial_number(serial_number);
	    }
	    else
		delete_frame(representation_frame);
	}
    }
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(frame_representations);
    return VALUES_1(Nil);
}

Object Namelike_slot_p_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Just_update_representations_of_slot_value, Qjust_update_representations_of_slot_value);

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm, Qsuppress_updating_of_slot_value_representations_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Available_stack_change_conses, Qavailable_stack_change_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_stack_change_conses_tail, Qavailable_stack_change_conses_tail);

Object Available_stack_change_conses_vector = UNBOUND;

Object Available_stack_change_conses_tail_vector = UNBOUND;

Object Stack_change_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Stack_change_cons_counter, Qstack_change_cons_counter);

/* OUTSTANDING-STACK-CHANGE-CONSES */
Object outstanding_stack_change_conses()
{
    Object temp;

    x_note_fn_call(87,3);
    temp = FIXNUM_MINUS(Stack_change_cons_counter,
	    length(Available_stack_change_conses));
    return VALUES_1(temp);
}

/* STACK-CHANGE-CONS-MEMORY-USAGE */
Object stack_change_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(87,4);
    temp = FIXNUM_TIMES(Stack_change_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-STACK-CHANGE-CONS-POOL */
Object replenish_stack_change_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(87,5);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qstack_change_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Stack_change_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qstack_change;       /* stack-change */

/* STACK-CHANGE-CONS-1 */
Object stack_change_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(87,6);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-STACK-CHANGE-LIST-POOL */
Object replenish_stack_change_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(87,7);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index))) {
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qstack_change_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-STACK-CHANGE-LIST-1 */
Object make_stack_change_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(87,8);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_stack_change_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* STACK-CHANGE-LIST-2 */
Object stack_change_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(87,9);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_change_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_change_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* STACK-CHANGE-LIST-3 */
Object stack_change_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(87,10);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_change_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_change_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* STACK-CHANGE-LIST-4 */
Object stack_change_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(87,11);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_stack_change_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_stack_change_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* STACK-CHANGE-LIST-TRACE-HOOK */
Object stack_change_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(87,12);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-STACK-CHANGE-CONSES-1 */
Object copy_tree_using_stack_change_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(87,13);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	temp_1 = copy_tree_using_stack_change_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	temp_1 = 
		copy_tree_using_stack_change_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-STACK-CHANGE-CONSES-1 */
Object copy_list_using_stack_change_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(87,14);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-STACK-CHANGE-CONS-1 */
Object reclaim_stack_change_cons_1(stack_change_cons)
    Object stack_change_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(87,15);
    inline_note_reclaim_cons(stack_change_cons,Qstack_change);
    if (ISVREF(Available_stack_change_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_stack_change_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = stack_change_cons;
	temp = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_change_cons;
    }
    else {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_change_cons;
	temp = Available_stack_change_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = stack_change_cons;
    }
    M_CDR(stack_change_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-STACK-CHANGE-LIST-1 */
Object reclaim_stack_change_list_1(stack_change_list)
    Object stack_change_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(87,16);
    if (stack_change_list) {
	last_1 = stack_change_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qstack_change);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qstack_change);
	if (ISVREF(Available_stack_change_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_stack_change_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = stack_change_list;
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = stack_change_list;
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-STACK-CHANGE-LIST*-1 */
Object reclaim_stack_change_list_star_1(stack_change_list)
    Object stack_change_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(87,17);
    if (CONSP(stack_change_list)) {
	temp = last(stack_change_list,_);
	M_CDR(temp) = Nil;
	if (stack_change_list) {
	    last_1 = stack_change_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qstack_change);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qstack_change);
	    if (ISVREF(Available_stack_change_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = stack_change_list;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = stack_change_list;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-STACK-CHANGE-TREE-1 */
Object reclaim_stack_change_tree_1(tree)
    Object tree;
{
    Object e, e2, stack_change_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(87,18);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_stack_change_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		stack_change_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(stack_change_cons,Qstack_change);
		if (EQ(stack_change_cons,e))
		    goto end_1;
		else if ( !TRUEP(stack_change_cons))
		    goto end_1;
		else
		    stack_change_cons = CDR(stack_change_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_stack_change_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-STACK-CHANGE-ELEMENT-1 */
Object delete_stack_change_element_1(element,stack_change_list)
    Object element, stack_change_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(87,19);
    if (stack_change_list) {
	if (EQ(element,M_CAR(stack_change_list))) {
	    temp = CDR(stack_change_list);
	    inline_note_reclaim_cons(stack_change_list,Qstack_change);
	    if (ISVREF(Available_stack_change_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = stack_change_list;
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_change_list;
	    }
	    else {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_change_list;
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = stack_change_list;
	    }
	    M_CDR(stack_change_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = stack_change_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qstack_change);
		if (ISVREF(Available_stack_change_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_stack_change_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = stack_change_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-STACK-CHANGE-CONS-1 */
Object delete_stack_change_cons_1(stack_change_cons,stack_change_list)
    Object stack_change_cons, stack_change_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(87,20);
    if (EQ(stack_change_cons,stack_change_list))
	temp = CDR(stack_change_list);
    else {
	l_trailer_qm = Nil;
	l = stack_change_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,stack_change_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = stack_change_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_stack_change_cons_1(stack_change_cons);
    return VALUES_1(temp);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

/* RECLAIM-FRAME-STATUS-AND-NOTES-VALUE */
Object reclaim_frame_status_and_notes_value(frame_status_and_notes,frame)
    Object frame_status_and_notes, frame;
{
    x_note_fn_call(87,21);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qframe_status_and_notes);
    SVREF(frame,FIX((SI_Long)8L)) = Nil;
    reclaim_slot_value(frame_status_and_notes);
    return VALUES_1(Nil);
}

static Object Qbad;                /* bad */

/* FRAME-NOT-BAD-P */
Object frame_not_bad_p(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(87,22);
    temp = ISVREF(frame,(SI_Long)8L);
    return VALUES_1( !EQ(CAR(temp),Qbad) ? T : Nil);
}

static Object Qincomplete;         /* incomplete */

/* FRAME-INCOMPLETE-P */
Object frame_incomplete_p(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(87,23);
    temp = ISVREF(frame,(SI_Long)8L);
    return VALUES_1(EQ(CAR(temp),Qincomplete) ? T : Nil);
}

static Object Qok;                 /* ok */

/* INITIAL-ITEM-STATUS */
Object initial_item_status(class_1)
    Object class_1;
{
    x_note_fn_call(87,24);
    return VALUES_1(Qok);
}

/* GET-ITEM-STATUS */
Object get_item_status(block)
    Object block;
{
    Object temp;

    x_note_fn_call(87,25);
    temp = ISVREF(block,(SI_Long)8L);
    temp = CAR(temp);
    if (temp);
    else
	temp = Qok;
    return VALUES_1(temp);
}

/* INITIAL-ITEM-ACTIVE */
Object initial_item_active(class_1)
    Object class_1;
{
    x_note_fn_call(87,26);
    return VALUES_1(Evaluation_false_value);
}

/* GET-ITEM-ACTIVE */
Object get_item_active(block)
    Object block;
{
    x_note_fn_call(87,27);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1L) ? Evaluation_true_value : Evaluation_false_value);
}

/* INITIAL-CONTAINING-MODULE */
Object initial_containing_module(class_1)
    Object class_1;
{
    x_note_fn_call(87,28);
    return VALUES_1(Nil);
}

/* GET-CONTAINING-MODULE */
Object get_containing_module(block)
    Object block;
{
    Object temp;

    x_note_fn_call(87,29);
    temp = get_module_block_is_in(block);
    return VALUES_1(temp);
}

/* FRAME-HAS-NOTE-P */
Object frame_has_note_p(frame,type_of_note)
    Object frame, type_of_note;
{
    Object temp, frame_note_plist, type_of_note_1, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(87,30);
    if (ISVREF(frame,(SI_Long)8L)) {
	temp = ISVREF(frame,(SI_Long)8L);
	frame_note_plist = CDR(temp);
	if (frame_note_plist) {
	    type_of_note_1 = Nil;
	    ab_loop_list_ = frame_note_plist;
	    ab_loop_it_ = Nil;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    type_of_note_1 = M_CAR(ab_loop_list_);
	    ab_loop_it_ = EQ(type_of_note_1,type_of_note) ? T : Nil;
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FRAME-STATUS-UNION */
Object frame_status_union(status_1,status_2)
    Object status_1, status_2;
{
    Object temp;

    x_note_fn_call(87,31);
    if (EQ(status_1,Qbad))
	temp = Qbad;
    else if (EQ(status_2,Qbad))
	temp = Qbad;
    else if (EQ(status_1,Qincomplete))
	temp = Qincomplete;
    else if (EQ(status_2,Qincomplete))
	temp = Qincomplete;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qactivatable_subworkspace;  /* activatable-subworkspace */

static Object Qitem_status;        /* item-status */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* UPDATE-FRAME-STATUS */
Object update_frame_status(frame,new_frame_status,
	    do_not_update_representations_qm)
    Object frame, new_frame_status, do_not_update_representations_qm;
{
    Object old_frame_status_and_notes, old_frame_status;
    Object reclaim_old_frame_status_and_notes_qm, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, superior_frame_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char gensymed_symbol_2, temp;

    x_note_fn_call(87,32);
    old_frame_status_and_notes = ISVREF(frame,(SI_Long)8L);
    old_frame_status = CAR(old_frame_status_and_notes);
    reclaim_old_frame_status_and_notes_qm = Nil;
    if ( !TRUEP(old_frame_status_and_notes)) {
	if ( ! !TRUEP(new_frame_status)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qframe_status_and_notes);
	    svref_new_value = slot_value_cons_1(new_frame_status,Nil);
	    SVREF(frame,FIX((SI_Long)8L)) = svref_new_value;
	}
    }
    else if ( !TRUEP(new_frame_status) &&  
	    !TRUEP(CDR(old_frame_status_and_notes))) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_status_and_notes);
	SVREF(frame,FIX((SI_Long)8L)) = Nil;
	reclaim_old_frame_status_and_notes_qm = T;
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_status_and_notes);
	M_CAR(old_frame_status_and_notes) = new_frame_status;
	SVREF(frame,FIX((SI_Long)8L)) = old_frame_status_and_notes;
    }
    if (EQ(new_frame_status,Qbad)) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_1 = frame;
	gensymed_symbol_2 = (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)5L)) & (SI_Long)256L);
	inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2 ? T : Nil);
    }
    if (old_frame_status &&  !TRUEP(new_frame_status)) {
	superior_frame_1 = superior_frame(frame);
	if (superior_frame_1)
	    temp = (SI_Long)0L != (IFIX(ISVREF(superior_frame_1,
		    (SI_Long)5L)) & (SI_Long)1L) ?  
		    !TRUEP(get_property_value_in_object_configuration(frame,
		    Qactivatable_subworkspace,Nil)) || (SI_Long)0L != 
		    (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)1L) : 
		    TRUEP(Qnil);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_4 = (SI_Long)1L;
		gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		temp = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) 
		    & (SI_Long)262144L) : TRUEP(Nil);
	}
	if (temp) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	    gensymed_symbol_1 = frame;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
	else {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	    gensymed_symbol_1 = frame;
	    gensymed_symbol_2 = (SI_Long)0L != (IFIX(ISVREF(frame,
		    (SI_Long)5L)) & (SI_Long)256L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2 ? T : Nil);
	}
    }
    if (reclaim_old_frame_status_and_notes_qm)
	reclaim_slot_value(old_frame_status_and_notes);
    if ( !TRUEP(do_not_update_representations_qm))
	update_representations_of_slot_value(2,frame,Qframe_status_and_notes);
    update_subscriptions_from_virtual_attribute_change(frame,
	    get_property_value_function(3,
	    get_symbol_properties_function(Qitem_status),
	    Qvirtual_attribute,Nil),Nil);
    check_for_frame_being_embedded(frame);
    return VALUES_1(frame);
}

static Object Qitem_notes;         /* item-notes */

/* UPDATE-REPRESENTATIONS-OF-FRAME-NOTES */
Object update_representations_of_frame_notes(frame)
    Object frame;
{
    x_note_fn_call(87,33);
    update_representations_of_slot_value(2,frame,Qframe_status_and_notes);
    update_subscriptions_from_virtual_attribute_change(frame,
	    get_property_value_function(3,
	    get_symbol_properties_function(Qitem_notes),Qvirtual_attribute,
	    Nil),Nil);
    return VALUES_1(Nil);
}

/* GET-PARTICULARS-OF-FRAME-NOTE-FROM-COMPONENT-PARTICULARS */
Object get_particulars_of_frame_note_from_component_particulars(type_of_note,
	    frame,component_particulars)
    Object type_of_note, frame, component_particulars;
{
    Object temp;

    x_note_fn_call(87,34);
    temp = get_entry_for_component_particulars(component_particulars,frame);
    temp = SECOND(temp);
    return getfq_function_no_default(CDR(temp),type_of_note);
}

static Object Qframe_notes_for_component_particulars;  /* frame-notes-for-component-particulars */

/* GET-PARTICULARS-OF-FRAME-NOTES-FOR-COMPONENT-PARTICULARS */
Object get_particulars_of_frame_notes_for_component_particulars(frame)
    Object frame;
{
    Object temp;

    x_note_fn_call(87,35);
    temp = ISVREF(frame,(SI_Long)8L);
    return getfq_function_no_default(CDR(temp),
	    Qframe_notes_for_component_particulars);
}

/* FRAME-NOTE-OF-TYPE-FOR-COMPONENT-PARTICULAR-P */
Object frame_note_of_type_for_component_particular_p(type_of_note,frame)
    Object type_of_note, frame;
{
    Object particulars_of_frame_notes, ab_loop_list_, component_particular;
    Object ab_loop_it_;

    x_note_fn_call(87,36);
    particulars_of_frame_notes = Nil;
    ab_loop_list_ = 
	    get_particulars_of_frame_notes_for_component_particulars(frame);
    component_particular = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    particulars_of_frame_notes = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    component_particular = FIRST(particulars_of_frame_notes);
    ab_loop_it_ = 
	    get_particulars_of_frame_note_from_component_particulars(type_of_note,
	    frame,component_particular);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object List_of_embedding_slots = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_component_particulars, Qcurrent_computation_component_particulars);

static Object Qembedded_rule_has_frame_notes;  /* embedded-rule-has-frame-notes */

/* UPDATE-FRAME-STATUS-OF-PARENT-OF-EMBEDDED-FRAME */
Object update_frame_status_of_parent_of_embedded_frame(parent_frame,
	    embedded_frame_has_notes,name_of_slot_holding_embedded_frame,
	    defining_class_for_slot_qm)
    Object parent_frame, embedded_frame_has_notes;
    Object name_of_slot_holding_embedded_frame, defining_class_for_slot_qm;
{
    Object embedded_frame, new_parent_status, temp_1;
    char temp;

    x_note_fn_call(87,37);
    embedded_frame = get_slot_value_function(parent_frame,
	    name_of_slot_holding_embedded_frame,Nil);
    new_parent_status = embedded_frame_parent_status(parent_frame,
	    embedded_frame);
    update_frame_status(parent_frame,new_parent_status,Nil);
    if (embedded_frame_has_notes) {
	if (Current_computation_component_particulars)
	    temp = 
		    TRUEP(get_particulars_of_frame_note_from_component_particulars(Qembedded_rule_has_frame_notes,
		    parent_frame,Current_computation_component_particulars));
	else {
	    temp_1 = ISVREF(parent_frame,(SI_Long)8L);
	    temp = TRUEP(getfq_function_no_default(CDR(temp_1),
		    Qembedded_rule_has_frame_notes));
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return add_frame_note(5,Qembedded_rule_has_frame_notes,
		parent_frame,name_of_slot_holding_embedded_frame,Nil,Nil);
    else if (embedded_frame_has_notes)
	return update_representations_of_frame_notes(parent_frame);
    else {
	if (Current_computation_component_particulars)
	    temp = 
		    TRUEP(get_particulars_of_frame_note_from_component_particulars(Qembedded_rule_has_frame_notes,
		    parent_frame,Current_computation_component_particulars));
	else {
	    temp_1 = ISVREF(parent_frame,(SI_Long)8L);
	    temp = TRUEP(getfq_function_no_default(CDR(temp_1),
		    Qembedded_rule_has_frame_notes));
	}
	if (temp)
	    return delete_frame_note_if_any(Qembedded_rule_has_frame_notes,
		    parent_frame);
	else
	    return VALUES_1(Qnil);
    }
}

/* CHECK-FOR-FRAME-BEING-EMBEDDED */
Object check_for_frame_being_embedded(frame)
    Object frame;
{
    Object sub_class_bit_vector, parent_frame_qm, parent_slot_name_qm;
    Object parent_slot_name_defining_class_qm, embedding_slot_name;
    Object embedding_slot_name_defining_class_qm, parent_embedding_slot_name;
    Object parent_embedding_defining_class_qm, ab_loop_list_, ab_loop_desetq_;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(87,38);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if (temp) {
	result = get_kb_parent_information(frame);
	MVS_3(result,parent_frame_qm,parent_slot_name_qm,
		parent_slot_name_defining_class_qm);
	if (parent_frame_qm) {
	    embedding_slot_name = Nil;
	    embedding_slot_name_defining_class_qm = Nil;
	    parent_embedding_slot_name = Nil;
	    parent_embedding_defining_class_qm = Nil;
	    ab_loop_list_ = List_of_embedding_slots;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    embedding_slot_name = CAR(ab_loop_desetq_);
	    temp_1 = CDR(ab_loop_desetq_);
	    embedding_slot_name_defining_class_qm = CAR(temp_1);
	    temp_1 = CDR(ab_loop_desetq_);
	    temp_1 = CDR(temp_1);
	    parent_embedding_slot_name = CAR(temp_1);
	    temp_1 = CDR(ab_loop_desetq_);
	    temp_1 = CDR(temp_1);
	    temp_1 = CDR(temp_1);
	    parent_embedding_defining_class_qm = CAR(temp_1);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(embedding_slot_name,parent_slot_name_qm) && 
		    EQ(embedding_slot_name_defining_class_qm,
		    parent_slot_name_defining_class_qm)) {
		temp_1 = ISVREF(frame,(SI_Long)8L);
		return update_frame_status_of_parent_of_embedded_frame(parent_frame_qm,
			CDR(temp_1),parent_embedding_slot_name,
			parent_embedding_defining_class_qm);
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

/* ADD-FRAME-NOTE */
Object add_frame_note varargs_1(int, n)
{
    Object type_of_note, frame;
    Object particulars, recycle_old_particulars_list_if_any_qm;
    Object do_not_update_representations_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,39);
    INIT_ARGS_nonrelocating();
    type_of_note = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    particulars = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    recycle_old_particulars_list_if_any_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    do_not_update_representations_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Current_computation_component_particulars)
	return add_frame_note_to_component_particulars(type_of_note,frame,
		Current_computation_component_particulars,particulars,
		recycle_old_particulars_list_if_any_qm,
		do_not_update_representations_qm);
    else
	return add_frame_note_1(type_of_note,frame,particulars,
		recycle_old_particulars_list_if_any_qm,
		do_not_update_representations_qm);
}

/* ADD-FRAME-NOTE-1 */
Object add_frame_note_1(type_of_note,frame,particulars,
	    recycle_old_particulars_list_if_any_qm,
	    do_not_update_representations_qm)
    Object type_of_note, frame, particulars;
    Object recycle_old_particulars_list_if_any_qm;
    Object do_not_update_representations_qm;
{
    Object frame_status_and_notes, old_particulars_or_no_value, temp, temp_1;

    x_note_fn_call(87,40);
    frame_status_and_notes = ISVREF(frame,(SI_Long)8L);
    old_particulars_or_no_value = 
	    getfq_function(CDR(frame_status_and_notes),type_of_note,No_value);
    if (EQ(old_particulars_or_no_value,No_value)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_status_and_notes);
	temp = frame_status_and_notes;
	if (temp);
	else
	    temp = slot_value_cons_1(Nil,Nil);
	temp_1 = nconc2(temp,slot_value_cons_1(type_of_note,
		slot_value_cons_1(particulars,Nil)));
	SVREF(frame,FIX((SI_Long)8L)) = temp_1;
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Qframe_status_and_notes);
	temp_1 = set_getf(CDR(frame_status_and_notes),type_of_note,
		particulars);
	M_CDR(frame_status_and_notes) = temp_1;
	temp_1 = ISVREF(frame,(SI_Long)8L);
	SVREF(frame,FIX((SI_Long)8L)) = temp_1;
	if (recycle_old_particulars_list_if_any_qm && 
		CONSP(old_particulars_or_no_value))
	    reclaim_slot_value(old_particulars_or_no_value);
    }
    if ( !TRUEP(do_not_update_representations_qm))
	update_representations_of_frame_notes(frame);
    check_for_frame_being_embedded(frame);
    return VALUES_1(frame);
}

/* DELETE-FRAME-NOTE-IF-ANY */
Object delete_frame_note_if_any(type_of_note,frame)
    Object type_of_note, frame;
{
    x_note_fn_call(87,41);
    if (Current_computation_component_particulars)
	return delete_frame_note_from_component_particulars(type_of_note,
		frame,Current_computation_component_particulars);
    else
	return delete_frame_note_if_any_1(type_of_note,frame);
}

static Object Qab_slot_value;      /* slot-value */

static Object Qparent_frame;       /* parent-frame */

/* DELETE-FRAME-NOTE-IF-ANY-1 */
Object delete_frame_note_if_any_1(type_of_note,frame)
    Object type_of_note, frame;
{
    Object frame_status_and_notes, l, plist_tail, temp, svref_arg_2, temp_1;

    x_note_fn_call(87,42);
    frame_status_and_notes = ISVREF(frame,(SI_Long)8L);
    if (CONSP(frame_status_and_notes)) {
	l = frame_status_and_notes;
	plist_tail = Nil;
      next_loop:
	plist_tail = M_CDR(l);
	if ( !TRUEP(plist_tail))
	    goto end_loop;
	if (EQ(M_CAR(plist_tail),type_of_note)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qframe_status_and_notes);
	    temp = CDDR(plist_tail);
	    M_CDR(l) = temp;
	    M_CDDR(plist_tail) = Nil;
	    reclaim_slot_value(plist_tail);
	    if ( !TRUEP(CAR(frame_status_and_notes)) &&  
		    !TRUEP(CDR(frame_status_and_notes))) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(frame,Qframe_status_and_notes);
		SVREF(frame,FIX((SI_Long)8L)) = Nil;
		inline_note_reclaim_cons(frame_status_and_notes,
			Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = frame_status_and_notes;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		}
		else {
		    temp = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		}
		M_CDR(frame_status_and_notes) = Nil;
	    }
	    update_representations_of_frame_notes(frame);
	    temp_1 = type_of_note;
	    goto end_1;
	}
	l = M_CDR(plist_tail);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    if (get_lookup_slot_value_given_default(frame,Qparent_frame,Nil))
	check_for_frame_being_embedded(frame);
    return VALUES_1(temp_1);
}

/* DELETE-MULTIPLE-FRAME-NOTES-IF-ANY */
Object delete_multiple_frame_notes_if_any(types_of_notes,frame)
    Object types_of_notes, frame;
{
    Object type_of_note, ab_loop_list_;

    x_note_fn_call(87,43);
    if (ISVREF(frame,(SI_Long)8L)) {
	type_of_note = Nil;
	ab_loop_list_ = types_of_notes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	type_of_note = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_frame_note_if_any(type_of_note,frame);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-TO-FRAME-NOTE-PARTICULARS-LIST-IF-NECESSARY */
Object add_to_frame_note_particulars_list_if_necessary(item,type_of_note,frame)
    Object item, type_of_note, frame;
{
    x_note_fn_call(87,44);
    if (Current_computation_component_particulars)
	return add_frame_note_particular_to_component_particulars(item,
		type_of_note,frame,Current_computation_component_particulars);
    else
	return add_to_frame_note_particulars_list_if_necessary_1(item,
		type_of_note,frame);
}

/* ADD-TO-FRAME-NOTE-PARTICULARS-LIST-IF-NECESSARY-1 */
Object add_to_frame_note_particulars_list_if_necessary_1(item,type_of_note,
	    frame)
    Object item, type_of_note, frame;
{
    Object existing_particulars, temp;

    x_note_fn_call(87,45);
    if (Current_computation_component_particulars)
	existing_particulars = 
		get_particulars_of_frame_note_from_component_particulars(type_of_note,
		frame,Current_computation_component_particulars);
    else {
	temp = ISVREF(frame,(SI_Long)8L);
	existing_particulars = getfq_function_no_default(CDR(temp),
		type_of_note);
    }
    if ( !TRUEP(member_equal(item,existing_particulars)))
	return add_frame_note_1(type_of_note,frame,
		nconc2(existing_particulars,slot_value_cons_1(item,Nil)),
		Nil,Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_frame, Qcurrent_computation_frame);

/* COMPONENT-PARTICULARS-WITH-FRAME-NOTES */
Object component_particulars_with_frame_notes()
{
    Object component_particulars, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_;

    x_note_fn_call(87,46);
    component_particulars = Nil;
    ab_loop_list_ = 
	    get_particulars_of_frame_notes_for_component_particulars(Current_computation_frame);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    component_particulars = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = slot_value_cons_1(component_particulars,Nil);
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

/* DELETE-FROM-FRAME-NOTE-PARTICULARS-LIST */
Object delete_from_frame_note_particulars_list(key_for_item,type_of_note,frame)
    Object key_for_item, type_of_note, frame;
{
    x_note_fn_call(87,47);
    if (Current_computation_component_particulars)
	return delete_frame_note_particular_from_component_particulars(key_for_item,
		type_of_note,frame,Current_computation_component_particulars);
    else
	return delete_from_frame_note_particulars_list_2(key_for_item,
		type_of_note,frame);
}

/* DELETE-FROM-FRAME-NOTE-PARTICULARS-LIST-2 */
Object delete_from_frame_note_particulars_list_2(key_for_item,type_of_note,
	    frame)
    Object key_for_item, type_of_note, frame;
{
    Object particulars, temp;

    x_note_fn_call(87,48);
    if (Current_computation_component_particulars)
	particulars = 
		get_particulars_of_frame_note_from_component_particulars(type_of_note,
		frame,Current_computation_component_particulars);
    else {
	temp = ISVREF(frame,(SI_Long)8L);
	particulars = getfq_function_no_default(CDR(temp),type_of_note);
    }
    if (memq_function(key_for_item,particulars)) {
	if ( !TRUEP(CDR(particulars)))
	    return delete_frame_note_if_any_1(type_of_note,frame);
	else
	    return add_frame_note_1(type_of_note,frame,
		    delete_from_frame_note_particulars_list_1(key_for_item,
		    particulars),Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-FRAME-NOTE-PARTICULARS-LIST-1 */
Object delete_from_frame_note_particulars_list_1(key_for_item,particulars)
    Object key_for_item, particulars;
{
    Object l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(87,49);
    l_trailer_qm = Nil;
    l = particulars;
  next_loop:
    if (EQ(key_for_item,CAR(l)))
	goto end_loop;
    l_trailer_qm = l;
    l = CDR(l);
    goto next_loop;
  end_loop:
    if (l_trailer_qm) {
	cdr_new_value = CDR(l);
	M_CDR(l_trailer_qm) = cdr_new_value;
    }
    else
	particulars = CDR(l);
    M_CDR(l) = Nil;
    reclaim_slot_value(l);
    return VALUES_1(particulars);
    return VALUES_1(Qnil);
}

Object Frame_note_writer_1_prop = UNBOUND;

Object Superior_frame_note_type_prop = UNBOUND;

Object Inferior_frame_note_types_prop = UNBOUND;

static Object Qsuperior_frame_note_type;  /* superior-frame-note-type */

/* FRAME-NOTE-SUBTYPE-P */
Object frame_note_subtype_p(frame_note_type,possible_superior_type)
    Object frame_note_type, possible_superior_type;
{
    Object type;

    x_note_fn_call(87,50);
    type = frame_note_type;
  next_loop:
    if ( !TRUEP(type))
	goto end_loop;
    if (EQ(type,possible_superior_type))
	return VALUES_1(T);
    type = getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
	    Qsuperior_frame_note_type);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WRITE-EMBEDDED-RULE-HAS-FRAME-NOTES-NOTE */
Object write_embedded_rule_has_frame_notes_note(particulars,
	    frame_with_embedded_rule)
    Object particulars, frame_with_embedded_rule;
{
    x_note_fn_call(87,51);
    GENSYM_RETURN_ONE(get_slot_value_function(frame_with_embedded_rule,
	    particulars,Nil) ? 
	    write_frame_notes_of_inferior_frame(get_slot_value_function(frame_with_embedded_rule,
	    particulars,Nil)) : Nil);
    return VALUES_1(Nil);
}

/* FRAME-STATUS-AND-NOTES-REFLECTS-FLAGS-OF-FRAME-P */
Object frame_status_and_notes_reflects_flags_of_frame_p(frame)
    Object frame;
{
    Object temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(87,52);
    temp = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
	    (SI_Long)8192L) ? T : Nil;
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)256L) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	if (System_is_running || System_has_paused) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Simulation_subtable_class_description,
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
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1( !((SI_Long)0L != (IFIX(ISVREF(frame,
		    (SI_Long)5L)) & (SI_Long)1L)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Frame_note_index_skip, Qframe_note_index_skip);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_note_index, Qframe_note_index);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_note_index_has_been_written_qm, Qframe_note_index_has_been_written_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Frame_note_count, Qframe_note_count);

/* INITIAL-ITEM-NOTES */
Object initial_item_notes(class_1)
    Object class_1;
{
    x_note_fn_call(87,53);
    return VALUES_1(Nil);
}

static Object Qframe_note_writer_1;  /* frame-note-writer-1 */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~S [frame note writer missing for type of note ~A]" */

/* GET-ITEM-NOTES */
Object get_item_notes(frame)
    Object frame;
{
    Object notes, frame_status_and_notes, frame_note_index_skip;
    Object frame_note_count, frame_note_index;
    Object frame_note_index_has_been_written_qm, ab_loop_destructure_;
    Object type_of_note, particulars, rest_of_plist, temp;
    Object frame_note_writer_qm, note, ab_loop_iter_flag_, gensymed_symbol;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long index_1, bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(9);

    x_note_fn_call(87,54);
    notes = Nil;
    frame_status_and_notes = ISVREF(frame,(SI_Long)8L);
    if (CDR(frame_status_and_notes)) {
	frame_note_index_skip = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_skip,Qframe_note_index_skip,frame_note_index_skip,
		8);
	  frame_note_count = FIX(IFIX(length(CDR(frame_status_and_notes))) 
		  >>  -  - (SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Frame_note_count,Qframe_note_count,frame_note_count,
		  7);
	    index_1 = (SI_Long)1L;
	    frame_note_index = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index,Qframe_note_index,frame_note_index,
		    6);
	      frame_note_index_has_been_written_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_has_been_written_qm,Qframe_note_index_has_been_written_qm,frame_note_index_has_been_written_qm,
		      5);
		ab_loop_destructure_ = CDR(frame_status_and_notes);
		type_of_note = Nil;
		particulars = Nil;
		rest_of_plist = Nil;
		type_of_note = CAR(ab_loop_destructure_);
		temp = CDR(ab_loop_destructure_);
		particulars = CAR(temp);
		temp = CDR(ab_loop_destructure_);
		rest_of_plist = CDR(temp);
		frame_note_writer_qm = Nil;
		note = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop:
		Frame_note_index = FIX(index_1 + IFIX(Frame_note_index_skip));
		temp = rest_of_plist;
		if (temp);
		else
		    temp = IFIX(Frame_note_index) > (SI_Long)1L ? T : Nil;
		Frame_note_index_has_been_written_qm = temp;
		if ( !TRUEP(ab_loop_iter_flag_)) {
		    type_of_note = CAR(rest_of_plist);
		    temp = CDR(rest_of_plist);
		    particulars = CAR(temp);
		    temp = CDR(rest_of_plist);
		    rest_of_plist = CDR(temp);
		}
		gensymed_symbol = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(type_of_note),
			Qframe_note_writer_1);
		frame_note_writer_qm = gensymed_symbol ? gensymed_symbol : Nil;
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
			  if (frame_note_writer_qm)
			      inline_funcall_2(frame_note_writer_qm,
				      particulars,frame);
			  else
			      tformat(3,string_constant,particulars,
				      type_of_note);
			  note = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notes = eval_cons_1(note,notes);
		note = Nil;
		if (note)
		    reclaim_wide_string(note);
		if ( !TRUEP(rest_of_plist))
		    goto end_loop;
		ab_loop_iter_flag_ = Nil;
		index_1 = index_1 + (SI_Long)1L;
		goto next_loop;
	      end_loop:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp = notes ? allocate_evaluation_sequence(nreverse(notes)) : Nil;
    return VALUES_1(temp);
}

static Object Qname_for_debugging;  /* name-for-debugging */

static Object string_constant_1;   /* "~A: " */

static Object string_constant_2;   /* "and" */

static Object string_constant_3;   /* "but" */

static Object string_constant_4;   /* "DISABLED, and some superior item is either DISABLED or not OK" */

static Object string_constant_5;   /* "DISABLED" */

static Object string_constant_6;   /* "some superior item is either DISABLED or not OK" */

static Object string_constant_7;   /* "this INITIALLY rule is no longer active, having completed or timed out" */

static Object string_constant_8;   /* "not active" */

static Object string_constant_9;   /* ", ~a ~a~a" */

static Object string_constant_10;  /* "" */

static Object string_constant_11;  /* "." */

static Object array_constant;      /* # */

/* WRITE-FRAME-STATUS-AND-NOTES-FROM-SLOT */
Object write_frame_status_and_notes_from_slot(frame_status_and_notes,frame)
    Object frame_status_and_notes, frame;
{
    Object sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(87,55);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
    if (temp ? TRUEP(get_lookup_slot_value_given_default(frame,
	    Qname_for_debugging,Nil)) : TRUEP(Nil))
	tformat(2,string_constant_1,get_cached_debugging_name(frame));
    temp_1 = CAR(frame_status_and_notes);
    if (temp_1);
    else
	temp_1 = Qok;
    twrite_symbol(2,temp_1,T);
    if (frame_status_and_notes_reflects_flags_of_frame_p(frame)) {
	temp_1 = CAR(frame_status_and_notes) ? string_constant_2 : 
		string_constant_3;
	if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
		(SI_Long)8192L) && (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)5L)) & (SI_Long)256L))
	    temp_2 = string_constant_4;
	else if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
		(SI_Long)8192L))
	    temp_2 = string_constant_5;
	else if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)256L))
	    temp_2 = string_constant_6;
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
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
	    if (temp ? (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & 
		    (SI_Long)2048L) : TRUEP(Nil))
		temp_2 = string_constant_7;
	    else
		temp_2 = string_constant_8;
	}
	tformat(4,string_constant_9,temp_1,temp_2,
		CDR(frame_status_and_notes) ? string_constant_10 : 
		string_constant_11);
    }
    if (CDR(frame_status_and_notes)) {
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)16L));
	return twrite_frame_notes(frame,Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Abbreviate_frame_notes_p, Qabbreviate_frame_notes_p);

static Object string_constant_12;  /* "~%(~D) " */

static Object array_constant_1;    /* # */

/* TWRITE-FRAME-NOTES */
Object twrite_frame_notes(frame,abbreviate_frame_notes_p)
    Object frame, abbreviate_frame_notes_p;
{
    Object frame_status_and_notes, frame_note_index_skip, frame_note_count;
    Object frame_note_index, frame_note_index_has_been_written_qm;
    Object ab_loop_destructure_, type_of_note, particulars, rest_of_plist;
    Object temp, frame_note_writer_qm, note, ab_loop_iter_flag_;
    Object gensymed_symbol, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long index_1, bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(10);
    Object result;

    x_note_fn_call(87,56);
    PUSH_SPECIAL_WITH_SYMBOL(Abbreviate_frame_notes_p,Qabbreviate_frame_notes_p,abbreviate_frame_notes_p,
	    9);
      frame_status_and_notes = ISVREF(frame,(SI_Long)8L);
      if (CDR(frame_status_and_notes)) {
	  frame_note_index_skip = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_skip,Qframe_note_index_skip,frame_note_index_skip,
		  8);
	    frame_note_count = 
		    FIX(IFIX(length(CDR(frame_status_and_notes))) >>  -  - 
		    (SI_Long)1L);
	    PUSH_SPECIAL_WITH_SYMBOL(Frame_note_count,Qframe_note_count,frame_note_count,
		    7);
	      index_1 = (SI_Long)1L;
	      frame_note_index = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index,Qframe_note_index,frame_note_index,
		      6);
		frame_note_index_has_been_written_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_has_been_written_qm,Qframe_note_index_has_been_written_qm,frame_note_index_has_been_written_qm,
			5);
		  ab_loop_destructure_ = CDR(frame_status_and_notes);
		  type_of_note = Nil;
		  particulars = Nil;
		  rest_of_plist = Nil;
		  type_of_note = CAR(ab_loop_destructure_);
		  temp = CDR(ab_loop_destructure_);
		  particulars = CAR(temp);
		  temp = CDR(ab_loop_destructure_);
		  rest_of_plist = CDR(temp);
		  frame_note_writer_qm = Nil;
		  note = Nil;
		  ab_loop_iter_flag_ = T;
		next_loop:
		  Frame_note_index = FIX(index_1 + 
			  IFIX(Frame_note_index_skip));
		  temp = rest_of_plist;
		  if (temp);
		  else
		      temp = IFIX(Frame_note_index) > (SI_Long)1L ? T : Nil;
		  Frame_note_index_has_been_written_qm = temp;
		  if ( !TRUEP(ab_loop_iter_flag_)) {
		      type_of_note = CAR(rest_of_plist);
		      temp = CDR(rest_of_plist);
		      particulars = CAR(temp);
		      temp = CDR(rest_of_plist);
		      rest_of_plist = CDR(temp);
		  }
		  gensymed_symbol = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(type_of_note),
			  Qframe_note_writer_1);
		  frame_note_writer_qm = gensymed_symbol ? gensymed_symbol 
			  : Nil;
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
			    if (frame_note_writer_qm)
				inline_funcall_2(frame_note_writer_qm,
					particulars,frame);
			    else
				tformat(3,string_constant,particulars,
					type_of_note);
			    note = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  if (Frame_note_index_has_been_written_qm)
		      tformat(2,string_constant_12,Frame_note_index);
		  twrite_general_string(note);
		  if ( !FIXNUM_GE(Frame_note_index,Frame_note_count))
		      twrite_beginning_of_wide_string(array_constant_1,
			      FIX((SI_Long)2L));
		  if (note)
		      reclaim_wide_string(note);
		  if ( !TRUEP(rest_of_plist))
		      goto end_loop;
		  ab_loop_iter_flag_ = Nil;
		  index_1 = index_1 + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_13;  /* "(~d) " */

/* WRITE-FRAME-NOTES-OF-INFERIOR-FRAME */
Object write_frame_notes_of_inferior_frame(inferior_frame)
    Object inferior_frame;
{
    Object temp, ab_loop_destructure_, type_of_note, particulars;
    Object rest_of_plist, frame_note_writer_qm, ab_loop_iter_flag_;
    Object gensymed_symbol;
    SI_Long index_1;

    x_note_fn_call(87,57);
    temp = ISVREF(inferior_frame,(SI_Long)8L);
    ab_loop_destructure_ = CDR(temp);
    type_of_note = Nil;
    particulars = Nil;
    rest_of_plist = Nil;
    type_of_note = CAR(ab_loop_destructure_);
    temp = CDR(ab_loop_destructure_);
    particulars = CAR(temp);
    temp = CDR(ab_loop_destructure_);
    rest_of_plist = CDR(temp);
    frame_note_writer_qm = Nil;
    index_1 = IFIX(Frame_note_index);
    ab_loop_iter_flag_ = T;
  next_loop:
    gensymed_symbol = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(type_of_note),
	    Qframe_note_writer_1);
    frame_note_writer_qm = gensymed_symbol ? gensymed_symbol : Nil;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if ( !((Frame_note_index_has_been_written_qm ||  
	    !TRUEP(rest_of_plist)) && index_1 == IFIX(Frame_note_index)))
	tformat(2,string_constant_13,FIX(index_1));
    if (frame_note_writer_qm)
	inline_funcall_2(frame_note_writer_qm,particulars,inferior_frame);
    else
	tformat(3,string_constant,particulars,type_of_note);
    if ( ! !TRUEP(rest_of_plist))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)2L));
    if ( !TRUEP(rest_of_plist))
	goto end_loop;
    ab_loop_iter_flag_ = Nil;
    type_of_note = CAR(rest_of_plist);
    temp = CDR(rest_of_plist);
    particulars = CAR(temp);
    temp = CDR(rest_of_plist);
    rest_of_plist = CDR(temp);
    goto next_loop;
  end_loop:
    Frame_note_index_skip = FIX(IFIX(Frame_note_index_skip) + (index_1 - 
	    IFIX(Frame_note_index)));
    return VALUES_1(Qnil);
}

static Object string_constant_14;  /* "~%for " */

static Object array_constant_2;    /* # */

/* WRITE-FRAME-NOTES-FOR-COMPONENT-PARTICULARS-NOTE */
Object write_frame_notes_for_component_particulars_note(frame_notes_for_component_particulars,
	    frame)
    Object frame_notes_for_component_particulars, frame;
{
    Object component_particulars, status, frame_notes, ab_loop_list_;
    Object ab_loop_desetq_, temp, frame_note_index_skip, ab_loop_destructure_;
    Object type_of_note, particulars, rest_of_plist, frame_note_writer_qm;
    Object frame_note_index, frame_note_index_has_been_written_qm;
    Object ab_loop_iter_flag_, gensymed_symbol;
    SI_Long index_1;
    Declare_special(3);

    x_note_fn_call(87,58);
    component_particulars = Nil;
    status = Nil;
    frame_notes = Nil;
    ab_loop_list_ = frame_notes_for_component_particulars;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    component_particulars = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    status = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CAR(temp);
    frame_notes = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(1,string_constant_14);
    denote_component_of_block(3,Nil,component_particulars,frame);
    write_status_of_component_particulars(component_particulars,status);
    if (frame_notes) {
	frame_note_index_skip = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_skip,Qframe_note_index_skip,frame_note_index_skip,
		2);
	  ab_loop_destructure_ = frame_notes;
	  type_of_note = Nil;
	  particulars = Nil;
	  rest_of_plist = Nil;
	  type_of_note = CAR(ab_loop_destructure_);
	  temp = CDR(ab_loop_destructure_);
	  particulars = CAR(temp);
	  temp = CDR(ab_loop_destructure_);
	  rest_of_plist = CDR(temp);
	  frame_note_writer_qm = Nil;
	  index_1 = (SI_Long)1L;
	  frame_note_index = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index,Qframe_note_index,frame_note_index,
		  1);
	    frame_note_index_has_been_written_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Frame_note_index_has_been_written_qm,Qframe_note_index_has_been_written_qm,frame_note_index_has_been_written_qm,
		    0);
	      ab_loop_iter_flag_ = T;
	      twrite_beginning_of_wide_string(array_constant_2,
		      FIX((SI_Long)2L));
	    next_loop_1:
	      gensymed_symbol = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(type_of_note),
		      Qframe_note_writer_1);
	      frame_note_writer_qm = gensymed_symbol ? gensymed_symbol : Nil;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  index_1 = index_1 + (SI_Long)1L;
	      Frame_note_index = FIX(index_1 + IFIX(Frame_note_index_skip));
	      temp = rest_of_plist;
	      if (temp);
	      else {
		  temp = FIX((SI_Long)1L);
		  temp = NUM_GT(Frame_note_index,temp) ? T : Nil;
	      }
	      Frame_note_index_has_been_written_qm = temp;
	      if (Frame_note_index_has_been_written_qm)
		  tformat(2,string_constant_12,Frame_note_index);
	      if (frame_note_writer_qm)
		  inline_funcall_2(frame_note_writer_qm,particulars,frame);
	      else
		  tformat(3,string_constant,particulars,type_of_note);
	      if ( !TRUEP(rest_of_plist))
		  goto end_1;
	      twrite_beginning_of_wide_string(array_constant_1,
		      FIX((SI_Long)2L));
	      ab_loop_iter_flag_ = Nil;
	      type_of_note = CAR(rest_of_plist);
	      temp = CDR(rest_of_plist);
	      particulars = CAR(temp);
	      temp = CDR(rest_of_plist);
	      rest_of_plist = CDR(temp);
	      goto next_loop_1;
	    end_loop_1:
	    end_1:;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* ADD-FRAME-NOTE-TO-COMPONENT-PARTICULARS */
Object add_frame_note_to_component_particulars(type_of_note,frame,
	    component_particulars,particulars,
	    recycle_old_particulars_list_if_any_qm,
	    do_not_update_representations_qm)
    Object type_of_note, frame, component_particulars, particulars;
    Object recycle_old_particulars_list_if_any_qm;
    Object do_not_update_representations_qm;
{
    x_note_fn_call(87,59);
    return add_frame_note_1(Qframe_notes_for_component_particulars,frame,
	    add_frame_note_to_component_particulars_1(type_of_note,frame,
	    component_particulars,particulars,
	    recycle_old_particulars_list_if_any_qm),Nil,
	    do_not_update_representations_qm);
}

/* ADD-FRAME-NOTE-TO-COMPONENT-PARTICULARS-1 */
Object add_frame_note_to_component_particulars_1(type_of_note,frame,
	    component_particulars,particulars,
	    recycle_old_particulars_list_if_any_qm)
    Object type_of_note, frame, component_particulars, particulars;
    Object recycle_old_particulars_list_if_any_qm;
{
    Object component_particulars_entry, frame_status_and_notes;
    Object old_particulars_or_no_value;
    Object particulars_of_frame_notes_for_component_particulars, temp, temp_1;
    Object result;

    x_note_fn_call(87,60);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qframe_status_and_notes);
    component_particulars_entry = Nil;
    frame_status_and_notes = Nil;
    old_particulars_or_no_value = Nil;
    particulars_of_frame_notes_for_component_particulars = Nil;
    result = get_or_make_entry_for_component_particulars(component_particulars,
	    frame);
    MVS_2(result,component_particulars_entry,
	    particulars_of_frame_notes_for_component_particulars);
    frame_status_and_notes = SECOND(component_particulars_entry);
    old_particulars_or_no_value = 
	    getfq_function(CDR(frame_status_and_notes),type_of_note,No_value);
    if (EQ(old_particulars_or_no_value,No_value)) {
	temp = frame_status_and_notes;
	if (temp);
	else
	    temp = slot_value_cons_1(Nil,Nil);
	temp_1 = nconc2(temp,slot_value_cons_1(type_of_note,
		slot_value_cons_1(particulars,Nil)));
	M_SECOND(component_particulars_entry) = temp_1;
    }
    else {
	temp_1 = set_getf(CDR(frame_status_and_notes),type_of_note,
		particulars);
	M_CDR(frame_status_and_notes) = temp_1;
	if (recycle_old_particulars_list_if_any_qm && 
		CONSP(old_particulars_or_no_value))
	    reclaim_slot_value(old_particulars_or_no_value);
    }
    return VALUES_1(particulars_of_frame_notes_for_component_particulars);
}

/* GET-OR-MAKE-ENTRY-FOR-COMPONENT-PARTICULARS */
Object get_or_make_entry_for_component_particulars(component_particulars,frame)
    Object component_particulars, frame;
{
    Object particulars_of_frame_notes_for_component_particulars;
    Object component_particulars_entry_qm, new_component_particulars_entry_qm;
    Object temp;

    x_note_fn_call(87,61);
    particulars_of_frame_notes_for_component_particulars = 
	    get_particulars_of_frame_notes_for_component_particulars(frame);
    component_particulars_entry_qm = assoc_equal(component_particulars,
	    particulars_of_frame_notes_for_component_particulars);
    if (component_particulars_entry_qm)
	return VALUES_2(component_particulars_entry_qm,
		particulars_of_frame_notes_for_component_particulars);
    else {
	new_component_particulars_entry_qm = 
		slot_value_list_2(copy_for_slot_value(component_particulars),
		Nil);
	temp = nconc2(particulars_of_frame_notes_for_component_particulars,
		slot_value_cons_1(new_component_particulars_entry_qm,Nil));
	return VALUES_2(new_component_particulars_entry_qm,temp);
    }
}

/* GET-ENTRY-FOR-COMPONENT-PARTICULARS */
Object get_entry_for_component_particulars(component_particulars,frame)
    Object component_particulars, frame;
{
    Object current_computation_component_particulars, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(87,62);
    current_computation_component_particulars = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	    0);
      if (Current_computation_component_particulars)
	  temp = 
		  get_particulars_of_frame_note_from_component_particulars(Qframe_notes_for_component_particulars,
		  frame,Current_computation_component_particulars);
      else {
	  temp = ISVREF(frame,(SI_Long)8L);
	  temp = getfq_function_no_default(CDR(temp),
		  Qframe_notes_for_component_particulars);
      }
      result = assoc_equal(component_particulars,temp);
    POP_SPECIAL();
    return result;
}

/* ADD-FRAME-NOTE-PARTICULAR-TO-COMPONENT-PARTICULARS */
Object add_frame_note_particular_to_component_particulars(particular,
	    type_of_note,frame,component_particulars)
    Object particular, type_of_note, frame, component_particulars;
{
    Object existing_particulars_qm;

    x_note_fn_call(87,63);
    existing_particulars_qm = 
	    get_particulars_of_frame_note_from_component_particulars(type_of_note,
	    frame,component_particulars);
    if ( !TRUEP(memq_function(particular,existing_particulars_qm)))
	return add_frame_note_to_component_particulars(type_of_note,frame,
		component_particulars,nconc2(existing_particulars_qm,
		slot_value_cons_1(particular,Nil)),Nil,Nil);
    else
	return VALUES_1(Nil);
}

/* DELETE-FRAME-NOTE-FROM-COMPONENT-PARTICULARS */
Object delete_frame_note_from_component_particulars(type_of_note,frame,
	    component_particulars)
    Object type_of_note, frame, component_particulars;
{
    Object component_particulars_entry_qm;

    x_note_fn_call(87,64);
    component_particulars_entry_qm = 
	    get_entry_for_component_particulars(component_particulars,frame);
    return delete_frame_note_from_component_particulars_1(type_of_note,
	    frame,component_particulars_entry_qm,
	    SECOND(component_particulars_entry_qm));
}

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_use_of_stack_of_slot_value_changes_p, Qsuppress_use_of_stack_of_slot_value_changes_p);

/* DELETE-FRAME-NOTE-FROM-COMPONENT-PARTICULARS-1 */
Object delete_frame_note_from_component_particulars_1(type_of_note_qm,
	    frame,component_particulars_entry_qm,frame_status_and_notes)
    Object type_of_note_qm, frame, component_particulars_entry_qm;
    Object frame_status_and_notes;
{
    Object l, plist_tail, temp, svref_arg_2, slot_description, new_cons;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes;
    Object current_computation_component_particulars, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_2, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(87,65);
    if (CONSP(frame_status_and_notes)) {
	l = frame_status_and_notes;
	plist_tail = Nil;
      next_loop:
	plist_tail = CDR(l);
	if ( !TRUEP(plist_tail))
	    goto end_loop;
	if ( !TRUEP(type_of_note_qm) || EQ(CAR(plist_tail),type_of_note_qm)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(frame,Qframe_status_and_notes);
	    temp = CDDR(plist_tail);
	    M_CDR(l) = temp;
	    M_CDDR(plist_tail) = Nil;
	    reclaim_slot_value(plist_tail);
	    if ( !TRUEP(CAR(frame_status_and_notes)) &&  
		    !TRUEP(CDR(frame_status_and_notes))) {
		M_SECOND(component_particulars_entry_qm) = Nil;
		inline_note_reclaim_cons(frame_status_and_notes,
			Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = frame_status_and_notes;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		}
		else {
		    temp = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = frame_status_and_notes;
		}
		M_CDR(frame_status_and_notes) = Nil;
		slot_description = 
			get_slot_description_of_class_description_function(Qframe_status_and_notes,
			ISVREF(frame,(SI_Long)1L),Nil);
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
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
		    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
			    slot_description),stack_change_cons_1(Nil,Nil));
		else {
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp = Available_stack_change_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
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
		    M_CAR(gensymed_symbol_1) = frame;
		    M_CDR(gensymed_symbol_1) = slot_description;
		    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
		}
		M_CAR(gensymed_symbol) = gensymed_symbol_1;
		temp = Stack_of_slot_value_changes;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		stack_of_slot_value_changes = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			1);
		  current_computation_component_particulars = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			  0);
		    delete_from_frame_note_particulars_list_2(component_particulars_entry_qm,
			    Qframe_notes_for_component_particulars,frame);
		  POP_SPECIAL();
		  temp_1 = 
			  TRUEP(Suppress_updating_of_slot_value_representations_qm);
		  if (temp_1);
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
		      temp_1 = EQ(slot_description,
			      M_CDR(frame_and_slot_or_atom));
		      if (temp_1);
		      else {
			  temp_2 = M_CDR(frame_and_slot_or_atom);
			  temp_1 = CONSP(temp_2) ? EQ(slot_description,
				  SECOND(frame_and_slot_or_atom)) && 
				  EQ(Nil,THIRD(frame_and_slot_or_atom)) && 
				  EQ(Nil,CDDDR(frame_and_slot_or_atom)) : 
				  TRUEP(Nil);
		      }
		      ab_loop_it_ = temp_1 ? (EQ(frame,
			      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
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
		  if ( !temp_1)
		      update_all_representations_of_slot(frame,
			      slot_description,Nil,Nil);
		  if (ISVREF(slot_description,(SI_Long)14L))
		      update_frame_name_references(frame);
		  stack_change_pop_store = Nil;
		  cons_1 = Stack_of_slot_value_changes;
		  if (cons_1) {
		      stack_change_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qstack_change);
		      if (ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = 
				  ISVREF(Available_stack_change_conses_tail_vector,
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
		      temp_2 = M_CAR(Stack_of_slot_value_changes);
		      temp_1 = ATOM(temp_2);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ?  
			  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			  : TRUEP(Nil))
		      do_deferred_updates_to_representations_in_tables();
		POP_SPECIAL();
	    }
	    update_representations_of_frame_notes(frame);
	    return VALUES_1(type_of_note_qm);
	}
	l = CDR(plist_tail);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-ALL-FRAME-NOTES-FOR-COMPONENT-PARTICULAR */
Object delete_all_frame_notes_for_component_particular(component_particulars,
	    frame)
    Object component_particulars, frame;
{
    Object component_particulars_entry_qm;

    x_note_fn_call(87,66);
    component_particulars_entry_qm = 
	    get_entry_for_component_particulars(component_particulars,frame);
    return delete_frame_note_from_component_particulars_1(Nil,frame,
	    component_particulars_entry_qm,
	    SECOND(component_particulars_entry_qm));
}

/* DELETE-FRAME-NOTE-PARTICULAR-FROM-COMPONENT-PARTICULARS */
Object delete_frame_note_particular_from_component_particulars(key_for_item,
	    type_of_note,frame,component_particulars)
    Object key_for_item, type_of_note, frame, component_particulars;
{
    Object particulars;

    x_note_fn_call(87,67);
    particulars = 
	    get_particulars_of_frame_note_from_component_particulars(type_of_note,
	    frame,component_particulars);
    if (memq_function(key_for_item,particulars)) {
	if ( !TRUEP(CDR(particulars)))
	    return delete_frame_note_from_component_particulars(type_of_note,
		    frame,component_particulars);
	else
	    return add_frame_note_to_component_particulars(type_of_note,
		    frame,component_particulars,
		    delete_from_frame_note_particulars_list_1(key_for_item,
		    particulars),Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FRAME-NOTE-FROM-ALL-COMPONENT-PARTICULARS-OF-FRAME */
Object delete_frame_note_from_all_component_particulars_of_frame(type_of_note,
	    frame)
    Object type_of_note, frame;
{
    Object component_particulars_entries, component_particulars_entry;
    Object ab_loop_list_;

    x_note_fn_call(87,68);
    component_particulars_entries = 
	    get_particulars_of_frame_notes_for_component_particulars(frame);
    component_particulars_entry = Nil;
    ab_loop_list_ = component_particulars_entries;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    component_particulars_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_frame_note_from_component_particulars_1(type_of_note,frame,
	    component_particulars_entry,SECOND(component_particulars_entry));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DELETE-FRAME-NOTES-OF-TYPES-IN-LIST */
Object delete_frame_notes_of_types_in_list(frame,frame_note_type_list,
	    delete_only_from_component_particulars_qm)
    Object frame, frame_note_type_list;
    Object delete_only_from_component_particulars_qm;
{
    Object temp, slot_description, new_cons, temp_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, frame_note_type, ab_loop_list_;
    Object frame_and_slot_or_atom, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(87,69);
    temp = ISVREF(frame,(SI_Long)8L);
    if (CDR(temp)) {
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(frame,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp_1 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  frame_note_type = Nil;
	  ab_loop_list_ = frame_note_type_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_note_type = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (delete_only_from_component_particulars_qm)
	      delete_frame_note_from_all_component_particulars_of_frame(frame_note_type,
		      frame);
	  else
	      delete_frame_note_if_any(frame_note_type,frame);
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
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(frame,
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
	      update_all_representations_of_slot(frame,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(frame);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Directory_nil, Qdirectory_nil);

/* RECLAIM-GRAMMAR-TREE-FUNCTION */
Object reclaim_grammar_tree_function(tree)
    Object tree;
{
    x_note_fn_call(87,70);
    return reclaim_grammar_tree_1(tree);
}

/* GET-DIRECTORY-CONTENTS */
Object get_directory_contents(category_symbol)
    Object category_symbol;
{
    Object temp;

    x_note_fn_call(87,71);
    temp = lookup_kb_specific_property_value(category_symbol,
	    Directory_of_names_kbprop);
    return VALUES_1(temp);
}

/* IN-DIRECTORY-OF-NAMES-P */
Object in_directory_of_names_p(symbol_or_string,category_symbol)
    Object symbol_or_string, category_symbol;
{
    Object directory_of_names, simple_string, directory_1, temp, temp_1;
    Object temp_2;

    x_note_fn_call(87,72);
    if ( !TRUEP(symbol_or_string))
	symbol_or_string = Directory_nil;
    directory_of_names = lookup_kb_specific_property_value(category_symbol,
	    Directory_of_names_kbprop);
    if (directory_of_names) {
	simple_string = copy_text_string(text_string_p(symbol_or_string) ? 
		symbol_or_string : symbol_name_text_string(symbol_or_string));
	directory_1 = directory_of_names;
      next_loop:
	if (ATOM(directory_1)) {
	    temp = text_string_p(directory_1) ? directory_1 : 
		    symbol_name_text_string(directory_1);
	    goto end_1;
	}
	directory_1 = FIRST(directory_1);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	if (CONSP(directory_of_names)) {
	    directory_1 = SECOND(directory_of_names);
	  next_loop_1:
	    if (ATOM(directory_1)) {
		temp_1 = text_string_p(directory_1) ? directory_1 : 
			symbol_name_text_string(directory_1);
		goto end_2;
	    }
	    directory_1 = FIRST(directory_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = Qnil;
	  end_2:;
	}
	else
	    temp_1 = Nil;
	temp_2 = symbol_or_string;
	temp_2 = in_directory_of_names_1(directory_of_names,temp,temp_1,
		FIX((SI_Long)0L),temp_2,simple_string,
		text_string_length(simple_string));
	reclaim_text_string(simple_string);
	return VALUES_1(temp_2);
    }
    else
	return VALUES_1(Nil);
}

/* IN-DIRECTORY-OF-NAMES-1 */
Object in_directory_of_names_1(non_empty_directory_of_names,
	    string_for_first_name_in_directory,
	    string_for_second_name_in_directory_qm,m,symbol_or_string,
	    simple_string,length_of_simple_string)
    Object non_empty_directory_of_names, string_for_first_name_in_directory;
    Object string_for_second_name_in_directory_qm, m, symbol_or_string;
    Object simple_string, length_of_simple_string;
{
    Object length_of_first_name_in_directory, character_1_qm, code, temp_1;
    Object temp_2, l, subdirectory, string_for_first_name_in_subdirectory;
    Object character_qm, ab_loop_iter_flag_, directory_1, temp_3;
    SI_Long character_1, code_1;
    char temp;

    x_note_fn_call(87,73);
    length_of_first_name_in_directory = 
	    text_string_length(string_for_first_name_in_directory);
    if (FIXNUM_EQ(m,length_of_simple_string))
	return VALUES_1(FIXNUM_EQ(length_of_first_name_in_directory,
		length_of_simple_string) ? T : Nil);
    else {
	character_1 = UBYTE_16_ISAREF_1(simple_string,IFIX(m));
	character_1_qm = FIXNUM_GT(length_of_first_name_in_directory,m) ? 
		FIX(UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		IFIX(m))) : Nil;
	temp =  !TRUEP(string_for_second_name_in_directory_qm);
	if (temp);
	else if (character_1_qm) {
	    code = character_1_qm;
	    if (IFIX(code) < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp_1 = unicode_lowercase_if_uppercase(code);
		if (temp_1);
		else
		    temp_1 = code;
	    }
	    code_1 = 
		    UBYTE_16_ISAREF_1(string_for_second_name_in_directory_qm,
		    IFIX(m));
	    if (code_1 < (SI_Long)127L)
		temp_2 = (SI_Long)65L <= code_1 && code_1 <= (SI_Long)90L ?
			 FIX(code_1 + (SI_Long)32L) : FIX(code_1);
	    else {
		temp_2 = unicode_lowercase_if_uppercase(FIX(code_1));
		if (temp_2);
		else
		    temp_2 = FIX(code_1);
	    }
	    temp = NUM_EQ(temp_1,temp_2);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (character_1_qm) {
		code = character_1_qm;
		if (IFIX(code) < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) :
			     code;
		else {
		    temp_1 = unicode_lowercase_if_uppercase(code);
		    if (temp_1);
		    else
			temp_1 = code;
		}
		code_1 = character_1;
		if (code_1 < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= code_1 && code_1 <= 
			    (SI_Long)90L ? FIX(code_1 + (SI_Long)32L) : 
			    FIX(code_1);
		else {
		    temp_2 = unicode_lowercase_if_uppercase(FIX(code_1));
		    if (temp_2);
		    else
			temp_2 = FIX(code_1);
		}
		temp = NUM_EQ(temp_1,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return in_directory_of_names_1(non_empty_directory_of_names,
			string_for_first_name_in_directory,
			string_for_second_name_in_directory_qm,
			FIXNUM_ADD1(m),symbol_or_string,simple_string,
			length_of_simple_string);
	    else
		return VALUES_1(Nil);
	}
	else {
	    l = non_empty_directory_of_names;
	    subdirectory = Nil;
	    string_for_first_name_in_subdirectory = 
		    string_for_first_name_in_directory;
	    character_qm = character_1_qm;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    subdirectory = CAR(l);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		directory_1 = subdirectory;
	      next_loop_1:
		if (ATOM(directory_1)) {
		    string_for_first_name_in_subdirectory = 
			    text_string_p(directory_1) ? directory_1 : 
			    symbol_name_text_string(directory_1);
		    goto end_1;
		}
		directory_1 = FIRST(directory_1);
		goto next_loop_1;
	      end_loop_1:
		string_for_first_name_in_subdirectory = Qnil;
	      end_1:;
		character_qm = character_qm || 
			FIXNUM_GT(text_string_length(string_for_first_name_in_subdirectory),
			m) ? 
			FIX(UBYTE_16_ISAREF_1(string_for_first_name_in_subdirectory,
			IFIX(m))) : Nil;
	    }
	    if (character_qm) {
		code = character_qm;
		if (IFIX(code) < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) :
			     code;
		else {
		    temp_1 = unicode_lowercase_if_uppercase(code);
		    if (temp_1);
		    else
			temp_1 = code;
		}
		code_1 = character_1;
		if (code_1 < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= code_1 && code_1 <= 
			    (SI_Long)90L ? FIX(code_1 + (SI_Long)32L) : 
			    FIX(code_1);
		else {
		    temp_2 = unicode_lowercase_if_uppercase(FIX(code_1));
		    if (temp_2);
		    else
			temp_2 = FIX(code_1);
		}
		temp =  !NUM_LT(temp_1,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		code = character_qm;
		if (IFIX(code) < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) :
			     code;
		else {
		    temp_1 = unicode_lowercase_if_uppercase(code);
		    if (temp_1);
		    else
			temp_1 = code;
		}
		code_1 = character_1;
		if (code_1 < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= code_1 && code_1 <= 
			    (SI_Long)90L ? FIX(code_1 + (SI_Long)32L) : 
			    FIX(code_1);
		else {
		    temp_2 = unicode_lowercase_if_uppercase(FIX(code_1));
		    if (temp_2);
		    else
			temp_2 = FIX(code_1);
		}
		if (NUM_EQ(temp_1,temp_2)) {
		    temp_3 = subdirectory;
		    temp_1 = string_for_first_name_in_subdirectory;
		    if (CONSP(subdirectory)) {
			directory_1 = SECOND(subdirectory);
		      next_loop_2:
			if (ATOM(directory_1)) {
			    temp_2 = text_string_p(directory_1) ? 
				    directory_1 : 
				    symbol_name_text_string(directory_1);
			    goto end_2;
			}
			directory_1 = FIRST(directory_1);
			goto next_loop_2;
		      end_loop_2:
			temp_2 = Qnil;
		      end_2:;
		    }
		    else
			temp_2 = Nil;
		    return in_directory_of_names_1(temp_3,temp_1,temp_2,
			    FIXNUM_ADD1(m),symbol_or_string,simple_string,
			    length_of_simple_string);
		}
		else
		    return VALUES_1(Nil);
	    }
	    ab_loop_iter_flag_ = Nil;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
}

/* ADD-TO-DIRECTORY-OF-NAMES */
Object add_to_directory_of_names(symbol_or_string,category_symbol)
    Object symbol_or_string, category_symbol;
{
    Object directory_of_names, temp, simple_string, directory_1, temp_1;
    Object temp_2;

    x_note_fn_call(87,74);
    if ( !TRUEP(symbol_or_string))
	symbol_or_string = Directory_nil;
    directory_of_names = lookup_kb_specific_property_value(category_symbol,
	    Directory_of_names_kbprop);
    if ( !TRUEP(directory_of_names))
	temp = symbol_or_string;
    else {
	simple_string = copy_text_string(text_string_p(symbol_or_string) ? 
		symbol_or_string : symbol_name_text_string(symbol_or_string));
	directory_1 = directory_of_names;
      next_loop:
	if (ATOM(directory_1)) {
	    temp_1 = text_string_p(directory_1) ? directory_1 : 
		    symbol_name_text_string(directory_1);
	    goto end_1;
	}
	directory_1 = FIRST(directory_1);
	goto next_loop;
      end_loop:
	temp_1 = Qnil;
      end_1:;
	if (CONSP(directory_of_names)) {
	    directory_1 = SECOND(directory_of_names);
	  next_loop_1:
	    if (ATOM(directory_1)) {
		temp_2 = text_string_p(directory_1) ? directory_1 : 
			symbol_name_text_string(directory_1);
		goto end_2;
	    }
	    directory_1 = FIRST(directory_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = Qnil;
	  end_2:;
	}
	else
	    temp_2 = Nil;
	temp = symbol_or_string;
	temp = add_to_directory_of_names_1(directory_of_names,temp_1,
		temp_2,FIX((SI_Long)0L),temp,simple_string,
		text_string_length(simple_string));
	reclaim_text_string(simple_string);
    }
    mutate_kb_specific_property_value(category_symbol,temp,
	    Directory_of_names_kbprop);
    return VALUES_1(Nil);
}

/* ADD-TO-DIRECTORY-OF-NAMES-1 */
Object add_to_directory_of_names_1(non_empty_directory_of_names,
	    string_for_first_name_in_directory,
	    string_for_second_name_in_directory_qm,m,symbol_or_string,
	    simple_string,length_of_simple_string)
    Object non_empty_directory_of_names, string_for_first_name_in_directory;
    Object string_for_second_name_in_directory_qm, m, symbol_or_string;
    Object simple_string, length_of_simple_string;
{
    Object temp_1, temp_2, character_1_qm, code_1, l_trailer_qm, l;
    Object subdirectory, string_for_first_name_in_subdirectory, character_qm;
    Object ab_loop_iter_flag_, directory_1, temp_3, temp_4;
    SI_Long code, character_1;
    char temp;

    x_note_fn_call(87,75);
    if (FIXNUM_EQ(m,length_of_simple_string)) {
	temp =  !TRUEP(string_for_second_name_in_directory_qm);
	if (temp);
	else if (FIXNUM_GT(text_string_length(string_for_first_name_in_directory),
		m)) {
	    code = UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    code = 
		    UBYTE_16_ISAREF_1(string_for_second_name_in_directory_qm,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_2 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_2 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_2);
		else
		    temp_2 = FIX(code);
	    }
	    temp = NUM_EQ(temp_1,temp_2);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return grammar_list_2(symbol_or_string,
		    non_empty_directory_of_names);
	else
	    return grammar_cons_1(symbol_or_string,
		    non_empty_directory_of_names);
    }
    else {
	character_1 = UBYTE_16_ISAREF_1(simple_string,IFIX(m));
	character_1_qm = 
		FIXNUM_GT(text_string_length(string_for_first_name_in_directory),
		m) ? 
		FIX(UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		IFIX(m))) : Nil;
	temp =  !TRUEP(string_for_second_name_in_directory_qm);
	if (temp);
	else if (character_1_qm) {
	    code_1 = character_1_qm;
	    if (IFIX(code_1) < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= IFIX(code_1) && IFIX(code_1) <= 
			(SI_Long)90L ? FIX(IFIX(code_1) + (SI_Long)32L) : 
			code_1;
	    else {
		temp_1 = unicode_lowercase_if_uppercase(code_1);
		if (temp_1);
		else
		    temp_1 = code_1;
	    }
	    code = 
		    UBYTE_16_ISAREF_1(string_for_second_name_in_directory_qm,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_2 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_2 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_2);
		else
		    temp_2 = FIX(code);
	    }
	    temp = NUM_EQ(temp_1,temp_2);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (character_1_qm) {
		code_1 = character_1_qm;
		if (IFIX(code_1) < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= IFIX(code_1) && IFIX(code_1) 
			    <= (SI_Long)90L ? FIX(IFIX(code_1) + 
			    (SI_Long)32L) : code_1;
		else {
		    temp_1 = unicode_lowercase_if_uppercase(code_1);
		    if (temp_1);
		    else
			temp_1 = code_1;
		}
		code = character_1;
		if (code < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_2 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_2);
		    else
			temp_2 = FIX(code);
		}
		temp =  !NUM_LT(temp_1,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		code_1 = character_1_qm;
		if (IFIX(code_1) < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= IFIX(code_1) && IFIX(code_1) 
			    <= (SI_Long)90L ? FIX(IFIX(code_1) + 
			    (SI_Long)32L) : code_1;
		else {
		    temp_2 = unicode_lowercase_if_uppercase(code_1);
		    if (temp_2);
		    else
			temp_2 = code_1;
		}
		code = character_1;
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		if (NUM_EQ(temp_2,temp_1))
		    return add_to_directory_of_names_1(non_empty_directory_of_names,
			    string_for_first_name_in_directory,
			    string_for_second_name_in_directory_qm,
			    FIXNUM_ADD1(m),symbol_or_string,simple_string,
			    length_of_simple_string);
		else
		    return grammar_list_2(symbol_or_string,
			    non_empty_directory_of_names);
	    }
	    else
		return grammar_list_2(non_empty_directory_of_names,
			symbol_or_string);
	}
	else {
	    l_trailer_qm = Nil;
	    l = non_empty_directory_of_names;
	    subdirectory = Nil;
	    string_for_first_name_in_subdirectory = 
		    string_for_first_name_in_directory;
	    character_qm = character_1_qm;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    subdirectory = CAR(l);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		directory_1 = subdirectory;
	      next_loop_1:
		if (ATOM(directory_1)) {
		    string_for_first_name_in_subdirectory = 
			    text_string_p(directory_1) ? directory_1 : 
			    symbol_name_text_string(directory_1);
		    goto end_1;
		}
		directory_1 = FIRST(directory_1);
		goto next_loop_1;
	      end_loop_1:
		string_for_first_name_in_subdirectory = Qnil;
	      end_1:;
		character_qm = character_qm || 
			FIXNUM_GT(text_string_length(string_for_first_name_in_subdirectory),
			m) ? 
			FIX(UBYTE_16_ISAREF_1(string_for_first_name_in_subdirectory,
			IFIX(m))) : Nil;
	    }
	    if (character_qm) {
		code_1 = character_qm;
		if (IFIX(code_1) < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= IFIX(code_1) && IFIX(code_1) 
			    <= (SI_Long)90L ? FIX(IFIX(code_1) + 
			    (SI_Long)32L) : code_1;
		else {
		    temp_1 = unicode_lowercase_if_uppercase(code_1);
		    if (temp_1);
		    else
			temp_1 = code_1;
		}
		code = character_1;
		if (code < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_2 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_2);
		    else
			temp_2 = FIX(code);
		}
		temp =  !NUM_LT(temp_1,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		code_1 = character_qm;
		if (IFIX(code_1) < (SI_Long)127L)
		    temp_2 = (SI_Long)65L <= IFIX(code_1) && IFIX(code_1) 
			    <= (SI_Long)90L ? FIX(IFIX(code_1) + 
			    (SI_Long)32L) : code_1;
		else {
		    temp_2 = unicode_lowercase_if_uppercase(code_1);
		    if (temp_2);
		    else
			temp_2 = code_1;
		}
		code = character_1;
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		if (NUM_EQ(temp_2,temp_1)) {
		    temp_3 = subdirectory;
		    temp_1 = string_for_first_name_in_subdirectory;
		    if (CONSP(subdirectory)) {
			directory_1 = SECOND(subdirectory);
		      next_loop_2:
			if (ATOM(directory_1)) {
			    temp_2 = text_string_p(directory_1) ? 
				    directory_1 : 
				    symbol_name_text_string(directory_1);
			    goto end_2;
			}
			directory_1 = FIRST(directory_1);
			goto next_loop_2;
		      end_loop_2:
			temp_2 = Qnil;
		      end_2:;
		    }
		    else
			temp_2 = Nil;
		    temp_4 = add_to_directory_of_names_1(temp_3,temp_1,
			    temp_2,FIXNUM_ADD1(m),symbol_or_string,
			    simple_string,length_of_simple_string);
		    M_CAR(l) = temp_4;
		}
		else if (l_trailer_qm) {
		    temp_4 = grammar_cons_1(symbol_or_string,l);
		    M_CDR(l_trailer_qm) = temp_4;
		}
		else
		    return grammar_cons_1(symbol_or_string,l);
		return VALUES_1(non_empty_directory_of_names);
	    }
	    ab_loop_iter_flag_ = Nil;
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp_4 = grammar_cons_1(symbol_or_string,Nil);
	    M_CDR(l_trailer_qm) = temp_4;
	    return VALUES_1(non_empty_directory_of_names);
	    return VALUES_1(Qnil);
	}
    }
}

/* DELETE-FROM-DIRECTORY-OF-NAMES */
Object delete_from_directory_of_names(symbol_or_string,category_symbol)
    Object symbol_or_string, category_symbol;
{
    Object directory_of_names, simple_string, directory_1, temp, temp_1;

    x_note_fn_call(87,76);
    if ( !TRUEP(Releasing_kb_qm)) {
	if ( !TRUEP(symbol_or_string))
	    symbol_or_string = Directory_nil;
	directory_of_names = 
		lookup_kb_specific_property_value(category_symbol,
		Directory_of_names_kbprop);
	if (directory_of_names) {
	    simple_string = 
		    copy_text_string(text_string_p(symbol_or_string) ? 
		    symbol_or_string : 
		    symbol_name_text_string(symbol_or_string));
	    directory_1 = directory_of_names;
	  next_loop:
	    if (ATOM(directory_1)) {
		temp = text_string_p(directory_1) ? directory_1 : 
			symbol_name_text_string(directory_1);
		goto end_1;
	    }
	    directory_1 = FIRST(directory_1);
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	    temp_1 = symbol_or_string;
	    temp_1 = delete_from_directory_of_names_1(directory_of_names,
		    temp,FIX((SI_Long)0L),temp_1,simple_string,
		    text_string_length(simple_string));
	    reclaim_text_string(simple_string);
	}
	else
	    temp_1 = Nil;
	return mutate_kb_specific_property_value(category_symbol,temp_1,
		Directory_of_names_kbprop);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-DIRECTORY-OF-NAMES-1 */
Object delete_from_directory_of_names_1(non_empty_directory_of_names,
	    string_for_first_name_in_directory,m,symbol_or_string,
	    simple_string,length_of_simple_string)
    Object non_empty_directory_of_names, string_for_first_name_in_directory, m;
    Object symbol_or_string, simple_string, length_of_simple_string;
{
    Object temp, temp_1, directory_1, string_1, i, l_trailer_qm, l;
    Object subdirectory, string_for_first_name_in_subdirectory;
    Object ab_loop_iter_flag_, modified_subdirectory, cdr_new_value;
    SI_Long code;
    char temp_2;

    x_note_fn_call(87,77);
    if (ATOM(non_empty_directory_of_names)) {
	if ( !EQ(non_empty_directory_of_names,symbol_or_string))
	    return VALUES_1(non_empty_directory_of_names);
	else
	    return VALUES_1(Nil);
    }
    else if (FIXNUM_EQ(m,length_of_simple_string)) {
	if (EQ(FIRST(non_empty_directory_of_names),symbol_or_string)) {
	    if (CDDR(non_empty_directory_of_names)) {
		temp = CDR(non_empty_directory_of_names);
		reclaim_grammar_cons_1(non_empty_directory_of_names);
		return VALUES_1(temp);
	    }
	    else {
		temp = SECOND(non_empty_directory_of_names);
		reclaim_grammar_list_1(non_empty_directory_of_names);
		return VALUES_1(temp);
	    }
	}
	else
	    return VALUES_1(non_empty_directory_of_names);
    }
    else {
	if (FIXNUM_GT(text_string_length(string_for_first_name_in_directory),
		m)) {
	    code = UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(simple_string,IFIX(m));
	    if (code < (SI_Long)127L)
		temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp = unicode_lowercase_if_uppercase(FIX(code));
		if (temp);
		else
		    temp = FIX(code);
	    }
	    temp_2 = NUM_EQ(temp_1,temp);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    directory_1 = SECOND(non_empty_directory_of_names);
	  next_loop:
	    if (ATOM(directory_1)) {
		string_1 = text_string_p(directory_1) ? directory_1 : 
			symbol_name_text_string(directory_1);
		goto end_1;
	    }
	    directory_1 = FIRST(directory_1);
	    goto next_loop;
	  end_loop:
	    string_1 = Qnil;
	  end_1:;
	    i = m;
	    if (FIXNUM_GT(text_string_length(string_1),i)) {
		code = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		code = UBYTE_16_ISAREF_1(simple_string,IFIX(i));
		if (code < (SI_Long)127L)
		    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			    FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp);
		    else
			temp = FIX(code);
		}
		temp_2 = NUM_EQ(temp_1,temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    return delete_from_directory_of_names_1(non_empty_directory_of_names,
		    string_for_first_name_in_directory,FIXNUM_ADD1(m),
		    symbol_or_string,simple_string,length_of_simple_string);
	else {
	    l_trailer_qm = Nil;
	    l = non_empty_directory_of_names;
	    subdirectory = Nil;
	    string_for_first_name_in_subdirectory = 
		    string_for_first_name_in_directory;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(l))
		goto end_loop_1;
	    subdirectory = CAR(l);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		directory_1 = subdirectory;
	      next_loop_2:
		if (ATOM(directory_1)) {
		    string_for_first_name_in_subdirectory = 
			    text_string_p(directory_1) ? directory_1 : 
			    symbol_name_text_string(directory_1);
		    goto end_2;
		}
		directory_1 = FIRST(directory_1);
		goto next_loop_2;
	      end_loop_2:
		string_for_first_name_in_subdirectory = Qnil;
	      end_2:;
	    }
	    if (FIXNUM_GT(text_string_length(string_for_first_name_in_subdirectory),
		    m)) {
		code = 
			UBYTE_16_ISAREF_1(string_for_first_name_in_subdirectory,
			IFIX(m));
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		code = UBYTE_16_ISAREF_1(simple_string,IFIX(m));
		if (code < (SI_Long)127L)
		    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			    FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp);
		    else
			temp = FIX(code);
		}
		temp_2 = NUM_EQ(temp_1,temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		modified_subdirectory = 
			delete_from_directory_of_names_1(subdirectory,
			string_for_first_name_in_subdirectory,
			FIXNUM_ADD1(m),symbol_or_string,simple_string,
			length_of_simple_string);
		if (modified_subdirectory)
		    M_CAR(l) = modified_subdirectory;
		else {
		    if (l_trailer_qm) {
			cdr_new_value = CDR(l);
			M_CDR(l_trailer_qm) = cdr_new_value;
		    }
		    else
			non_empty_directory_of_names = CDR(l);
		    reclaim_grammar_cons_1(l);
		}
		goto end_loop_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop_1;
	  end_loop_1:;
	    if (CDR(non_empty_directory_of_names))
		return VALUES_1(non_empty_directory_of_names);
	    else {
		temp = FIRST(non_empty_directory_of_names);
		reclaim_grammar_cons_1(non_empty_directory_of_names);
		return VALUES_1(temp);
	    }
	}
    }
}

/* MAKE-MENU-TREE-OF-NAMES-FROM-DIRECTORY */
Object make_menu_tree_of_names_from_directory(non_empty_directory_of_names,
	    string_for_first_name_in_directory,m,prefix_simple_string,
	    length_of_prefix)
    Object non_empty_directory_of_names, string_for_first_name_in_directory, m;
    Object prefix_simple_string, length_of_prefix;
{
    Object temp, temp_1, directory_1, string_1, simple_string, i, subdirectory;
    Object ab_loop_list_, string_for_first_name_in_subdirectory;
    Object ab_loop_iter_flag_;
    SI_Long code;
    char temp_2;

    x_note_fn_call(87,78);
    if (FIXNUM_EQ(m,length_of_prefix))
	temp = non_empty_directory_of_names;
    else if (ATOM(non_empty_directory_of_names)) {
	if (FIXNUM_GT(text_string_length(string_for_first_name_in_directory),
		m)) {
	    code = UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(prefix_simple_string,IFIX(m));
	    if (code < (SI_Long)127L)
		temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp = unicode_lowercase_if_uppercase(FIX(code));
		if (temp);
		else
		    temp = FIX(code);
	    }
	    temp_2 = NUM_EQ(temp_1,temp);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp = temp_2 ? 
		make_menu_tree_of_names_from_directory(non_empty_directory_of_names,
		string_for_first_name_in_directory,FIXNUM_ADD1(m),
		prefix_simple_string,length_of_prefix) : Nil;
    }
    else {
	if (FIXNUM_GT(text_string_length(string_for_first_name_in_directory),
		m)) {
	    code = UBYTE_16_ISAREF_1(string_for_first_name_in_directory,
		    IFIX(m));
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(prefix_simple_string,IFIX(m));
	    if (code < (SI_Long)127L)
		temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp = unicode_lowercase_if_uppercase(FIX(code));
		if (temp);
		else
		    temp = FIX(code);
	    }
	    temp_2 = NUM_EQ(temp_1,temp);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    directory_1 = SECOND(non_empty_directory_of_names);
	  next_loop:
	    if (ATOM(directory_1)) {
		string_1 = text_string_p(directory_1) ? directory_1 : 
			symbol_name_text_string(directory_1);
		goto end_1;
	    }
	    directory_1 = FIRST(directory_1);
	    goto next_loop;
	  end_loop:
	    string_1 = Qnil;
	  end_1:;
	    simple_string = prefix_simple_string;
	    i = m;
	    if (FIXNUM_GT(text_string_length(string_1),i)) {
		code = UBYTE_16_ISAREF_1(string_1,IFIX(i));
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		code = UBYTE_16_ISAREF_1(simple_string,IFIX(i));
		if (code < (SI_Long)127L)
		    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			    FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp);
		    else
			temp = FIX(code);
		}
		temp_2 = NUM_EQ(temp_1,temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    temp = 
		    make_menu_tree_of_names_from_directory(non_empty_directory_of_names,
		    string_for_first_name_in_directory,FIXNUM_ADD1(m),
		    prefix_simple_string,length_of_prefix);
	else {
	    subdirectory = Nil;
	    ab_loop_list_ = non_empty_directory_of_names;
	    string_for_first_name_in_subdirectory = 
		    string_for_first_name_in_directory;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    subdirectory = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		directory_1 = subdirectory;
	      next_loop_2:
		if (ATOM(directory_1)) {
		    string_for_first_name_in_subdirectory = 
			    text_string_p(directory_1) ? directory_1 : 
			    symbol_name_text_string(directory_1);
		    goto end_2;
		}
		directory_1 = FIRST(directory_1);
		goto next_loop_2;
	      end_loop_2:
		string_for_first_name_in_subdirectory = Qnil;
	      end_2:;
	    }
	    if (FIXNUM_GT(text_string_length(string_for_first_name_in_subdirectory),
		    m)) {
		code = 
			UBYTE_16_ISAREF_1(string_for_first_name_in_subdirectory,
			IFIX(m));
		if (code < (SI_Long)127L)
		    temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ?
			     FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp_1);
		    else
			temp_1 = FIX(code);
		}
		code = UBYTE_16_ISAREF_1(prefix_simple_string,IFIX(m));
		if (code < (SI_Long)127L)
		    temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			    FIX(code + (SI_Long)32L) : FIX(code);
		else {
		    temp = unicode_lowercase_if_uppercase(FIX(code));
		    if (temp);
		    else
			temp = FIX(code);
		}
		temp_2 = NUM_EQ(temp_1,temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = make_menu_tree_of_names_from_directory(subdirectory,
			string_for_first_name_in_subdirectory,
			FIXNUM_ADD1(m),prefix_simple_string,length_of_prefix);
		goto end_3;
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_3:;
	}
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Flattened_menu_reverse, Qflattened_menu_reverse);

DEFINE_VARIABLE_WITH_SYMBOL(Flattened_menu_maximum_remaining_elements, Qflattened_menu_maximum_remaining_elements);

/* FLATTEN-FIRST-N-DISTINCT-ELEMENTS-OF-MENU-TREE */
Object flatten_first_n_distinct_elements_of_menu_tree(directory_of_names)
    Object directory_of_names;
{
    Object dir, ab_loop_list_, temp;
    Object flattened_menu_maximum_remaining_elements_new_value;

    x_note_fn_call(87,79);
    if (LISTP(directory_of_names)) {
	dir = Nil;
	ab_loop_list_ = directory_of_names;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	dir = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(flatten_first_n_distinct_elements_of_menu_tree(dir))) {
	    temp = Nil;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else {
	temp = memq_function(directory_of_names,Flattened_menu_reverse);
	if (temp);
	else {
	    flattened_menu_maximum_remaining_elements_new_value = 
		    FIXNUM_SUB1(Flattened_menu_maximum_remaining_elements);
	    Flattened_menu_maximum_remaining_elements = 
		    flattened_menu_maximum_remaining_elements_new_value;
	    if ((SI_Long)0L <= 
			IFIX(Flattened_menu_maximum_remaining_elements)) {
		Flattened_menu_reverse = grammar_cons_1(directory_of_names,
			Flattened_menu_reverse);
		temp = T;
	    }
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* MAKE-MENU-OF-NAMES-UNLESS-TOO-MANY? */
Object make_menu_of_names_unless_too_many_qm(category_symbol,
	    prefix_simple_string_qm,maximum_length_of_menu,
	    return_partial_list_p)
    Object category_symbol, prefix_simple_string_qm, maximum_length_of_menu;
    Object return_partial_list_p;
{
    Object directory_of_names, directory_1, temp, directory_tree_of_names;
    Object flattened_menu_maximum_remaining_elements, flattened_menu_reverse;
    Object few_enough_choices_p;
    Declare_special(2);

    x_note_fn_call(87,80);
    directory_of_names = lookup_kb_specific_property_value(category_symbol,
	    Directory_of_names_kbprop);
    if (directory_of_names && prefix_simple_string_qm) {
	directory_1 = directory_of_names;
      next_loop:
	if (ATOM(directory_1)) {
	    temp = text_string_p(directory_1) ? directory_1 : 
		    symbol_name_text_string(directory_1);
	    goto end_1;
	}
	directory_1 = FIRST(directory_1);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	directory_tree_of_names = 
		make_menu_tree_of_names_from_directory(directory_of_names,
		temp,FIX((SI_Long)0L),prefix_simple_string_qm,
		text_string_length(prefix_simple_string_qm));
    }
    else
	directory_tree_of_names = directory_of_names;
    flattened_menu_maximum_remaining_elements = maximum_length_of_menu;
    PUSH_SPECIAL_WITH_SYMBOL(Flattened_menu_maximum_remaining_elements,Qflattened_menu_maximum_remaining_elements,flattened_menu_maximum_remaining_elements,
	    1);
      flattened_menu_reverse = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Flattened_menu_reverse,Qflattened_menu_reverse,flattened_menu_reverse,
	      0);
	few_enough_choices_p = 
		flatten_first_n_distinct_elements_of_menu_tree(directory_tree_of_names);
	if (few_enough_choices_p || return_partial_list_p)
	    temp = Flattened_menu_reverse;
	else {
	    reclaim_grammar_list_1(Flattened_menu_reverse);
	    temp = Menu_too_many_instances;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* MAKE-MENU-OF-NAMES-FROM-DIRECTORY-IF-FEW-ENOUGH */
Object make_menu_of_names_from_directory_if_few_enough(category_symbol,
	    prefix_simple_string_qm,maximum_length_of_menu)
    Object category_symbol, prefix_simple_string_qm, maximum_length_of_menu;
{
    Object temp;

    x_note_fn_call(87,81);
    temp = (SI_Long)0L >= IFIX(maximum_length_of_menu) ? 
	    Menu_too_many_instances : 
	    make_menu_of_names_unless_too_many_qm(category_symbol,
	    prefix_simple_string_qm,maximum_length_of_menu,Nil);
    return VALUES_1(temp);
}

/* MAKE-MENU-OF-NAMES-FROM-DIRECTORY */
Object make_menu_of_names_from_directory(category_symbol,
	    prefix_simple_string_qm)
    Object category_symbol, prefix_simple_string_qm;
{
    Object temp;

    x_note_fn_call(87,82);
    temp = nreverse(make_menu_of_names_unless_too_many_qm(category_symbol,
	    prefix_simple_string_qm,Maximum_length_of_menu_of_names,T));
    return VALUES_1(temp);
}

Object Frame_or_frames_with_this_name_kbprop = UNBOUND;

/* NAME-OR-NAMES-SAME-P */
Object name_or_names_same_p(set_a,set_b)
    Object set_a, set_b;
{
    Object name_b, ab_loop_list_, name_a;
    char temp;

    x_note_fn_call(87,83);
    if (set_a && ATOM(set_a)) {
	if (set_b && ATOM(set_b))
	    return VALUES_1(EQ(set_a,set_b) ? T : Nil);
	else if (set_b) {
	    name_b = Nil;
	    ab_loop_list_ = set_b;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name_b = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !EQ(name_b,set_a))
		return VALUES_1(Nil);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (set_b && ATOM(set_b)) {
	if (set_a) {
	    name_a = Nil;
	    ab_loop_list_ = set_a;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    name_a = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !EQ(name_a,set_b))
		return VALUES_1(Nil);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	name_a = Nil;
	ab_loop_list_ = set_a;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	name_a = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(name_a,set_b))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	if (temp) {
	    name_b = Nil;
	    ab_loop_list_ = set_b;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    name_b = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(name_b,set_a)))
		return VALUES_1(Nil);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* NAME-OR-NAMES-LIKE-P */
Object name_or_names_like_p(set_a,set_b)
    Object set_a, set_b;
{
    Object name_b, ab_loop_list_, ab_loop_it_, name_a;

    x_note_fn_call(87,84);
    if (set_a && ATOM(set_a)) {
	if (set_b && ATOM(set_b))
	    return VALUES_1(EQ(set_a,set_b) ? T : Nil);
	else if (set_b) {
	    name_b = Nil;
	    ab_loop_list_ = set_b;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name_b = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQ(name_b,set_a) ? T : Nil;
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (set_b && ATOM(set_b)) {
	if (set_a) {
	    name_a = Nil;
	    ab_loop_list_ = set_a;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    name_a = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQ(name_a,set_b) ? T : Nil;
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	name_a = Nil;
	ab_loop_list_ = set_a;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	name_a = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = memq_function(name_a,set_b);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* GET-PRIMARY-NAME-FOR-FRAME-IF-ANY */
Object get_primary_name_for_frame_if_any(namable_frame)
    Object namable_frame;
{
    Object name_or_names_for_frame;

    x_note_fn_call(87,85);
    name_or_names_for_frame = 
	    get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    if (ATOM(name_or_names_for_frame))
	return VALUES_1(name_or_names_for_frame);
    else
	return VALUES_1(CAR(name_or_names_for_frame));
}

/* GET-SECONDARY-NAME-FOR-FRAME-IF-ANY */
Object get_secondary_name_for_frame_if_any(namable_frame)
    Object namable_frame;
{
    Object name_or_names_for_frame;

    x_note_fn_call(87,86);
    name_or_names_for_frame = 
	    get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    if (CONSP(name_or_names_for_frame))
	return VALUES_1(SECOND(name_or_names_for_frame));
    else
	return VALUES_1(Nil);
}

/* GET-UNIQUE-NAME-FOR-FRAME-IF-ANY */
Object get_unique_name_for_frame_if_any(namable_frame)
    Object namable_frame;
{
    Object names_sic, name, list_1, frame_or_frames_with_this_name;

    x_note_fn_call(87,87);
    names_sic = get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    name = Nil;
  next_loop:
    name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
    if ( !TRUEP(name))
	goto end_loop;
    list_1 = INLINE_SYMBOL_PLIST(name);
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Frame_or_frames_with_this_name_kbprop))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    frame_or_frames_with_this_name = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (ATOM(frame_or_frames_with_this_name) ||  
	    !TRUEP(CDR(frame_or_frames_with_this_name)))
	return VALUES_1(name);
    names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qitem;               /* item */

/* GET-INSTANCE-WITH-NAME-IF-ANY */
Object get_instance_with_name_if_any(class_qm,name)
    Object class_qm, name;
{
    Object list_1, frame_or_frames_with_this_name, gensymed_symbol;
    Object sub_class_bit_vector, frame, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(87,88);
    list_1 = INLINE_SYMBOL_PLIST(name);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Frame_or_frames_with_this_name_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    frame_or_frames_with_this_name = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (frame_or_frames_with_this_name) {
	if (ATOM(frame_or_frames_with_this_name)) {
	    temp =  !TRUEP(class_qm);
	    if (temp);
	    else if (EQ(class_qm,Qitem))
		temp = TRUEP(ISVREF(ISVREF(frame_or_frames_with_this_name,
			(SI_Long)1L),(SI_Long)16L));
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(frame_or_frames_with_this_name,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp)
		return VALUES_1(frame_or_frames_with_this_name);
	    else
		return VALUES_1(Nil);
	}
	else {
	    frame = Nil;
	    ab_loop_list_ = frame_or_frames_with_this_name;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp =  !TRUEP(class_qm);
	    if (temp);
	    else if (EQ(class_qm,Qitem))
		temp = TRUEP(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L));
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp)
		return VALUES_1(frame);
	    goto next_loop_2;
	  end_loop_2:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qreclaim_slot_value_cons_function;  /* reclaim-slot-value-cons-function */

/* PUT-NAME-OR-NAMES-FOR-FRAME */
Object put_name_or_names_for_frame(namable_frame,name_or_names_for_frame,
	    initializing_qm)
    Object namable_frame, name_or_names_for_frame, initializing_qm;
{
    Object car_name, old_names, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(87,89);
    if (CONSP(name_or_names_for_frame)) {
	if ( !TRUEP(CDR(name_or_names_for_frame))) {
	    car_name = FIRST(name_or_names_for_frame);
	    reclaim_slot_value_list_1(name_or_names_for_frame);
	    name_or_names_for_frame = car_name;
	}
	else
	    name_or_names_for_frame = delete_duplicates_from_list(2,
		    name_or_names_for_frame,Qreclaim_slot_value_cons_function);
    }
    old_names = initializing_qm ? Qnil : 
	    get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(namable_frame,Qname_or_names_for_frame);
    set_lookup_slot_value_1(namable_frame,Qname_or_names_for_frame,
	    name_or_names_for_frame);
    if ( !TRUEP(name_or_names_same_p(old_names,name_or_names_for_frame))) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(namable_frame,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)10L),(SI_Long)1L);
	gensymed_symbol_1 = namable_frame;
	gensymed_symbol_2 = old_names;
	gensymed_symbol_3 = initializing_qm;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    return VALUES_1(name_or_names_for_frame);
}

/* NOTE-NAME-CHANGE-FOR-BLOCK */
Object note_name_change_for_block(block,old_names,initializing_p)
    Object block, old_names, initializing_p;
{
    x_note_fn_call(87,90);
    return update_as_frame_with_name(block,old_names,
	    get_lookup_slot_value_given_default(block,
	    Qname_or_names_for_frame,Nil));
}

/* UPDATE-AS-FRAME-WITH-NAME */
Object update_as_frame_with_name(namable_frame,old_names,new_names)
    Object namable_frame, old_names, new_names;
{
    Object name, ab_loop_list_, old_name;

    x_note_fn_call(87,91);
    if (old_names ? ATOM(old_names) : TRUEP(Nil)) {
	if (new_names ? ATOM(new_names) : TRUEP(Nil)) {
	    if ( !EQ(old_names,new_names)) {
		delete_as_frame_with_name(namable_frame,old_names);
		return add_as_frame_with_name(namable_frame,new_names);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    if ( !TRUEP(memq_function(old_names,new_names)))
		delete_as_frame_with_name(namable_frame,old_names);
	    name = Nil;
	    ab_loop_list_ = new_names;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !EQ(name,old_names))
		add_as_frame_with_name(namable_frame,name);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else if (new_names ? ATOM(new_names) : TRUEP(Nil)) {
	old_name = Nil;
	ab_loop_list_ = old_names;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	old_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(old_name,new_names))
	    delete_as_frame_with_name(namable_frame,old_name);
	goto next_loop_1;
      end_loop_1:;
	if ( !TRUEP(memq_function(new_names,old_names)))
	    return add_as_frame_with_name(namable_frame,new_names);
	else
	    return VALUES_1(Nil);
    }
    else {
	old_name = Nil;
	ab_loop_list_ = old_names;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	old_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(old_name,new_names)))
	    delete_as_frame_with_name(namable_frame,old_name);
	goto next_loop_2;
      end_loop_2:;
	name = Nil;
	ab_loop_list_ = new_names;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(name,old_names)))
	    add_as_frame_with_name(namable_frame,name);
	goto next_loop_3;
      end_loop_3:
	return VALUES_1(Qnil);
    }
}

/* CHANGE-PRIMARY-NAME-OF-FRAME */
Object change_primary_name_of_frame(namable_frame,new_name,initializing_qm)
    Object namable_frame, new_name, initializing_qm;
{
    Object names, new_value;

    x_note_fn_call(87,92);
    names = get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    new_value = Nil;
    if ( !TRUEP(new_name)) {
	if (SYMBOLP(names)) {
	    if (initializing_qm)
		return put_name_or_names_for_frame(namable_frame,
			CAR(names),initializing_qm);
	    else
		return change_slot_value(3,namable_frame,
			Qname_or_names_for_frame,Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(names) ? TRUEP(memq_function(new_name,names)) : 
	    EQ(new_name,names))
	return VALUES_1(names);
    else {
	new_value = ATOM(names) ? new_name : slot_value_cons_1(new_name,
		copy_list_using_slot_value_conses_1(CDR(names)));
	if (initializing_qm)
	    return put_name_or_names_for_frame(namable_frame,new_value,
		    initializing_qm);
	else
	    return change_slot_value(3,namable_frame,
		    Qname_or_names_for_frame,new_value);
    }
}

/* CHANGE-SECONDARY-NAME-OF-FRAME */
Object change_secondary_name_of_frame(namable_frame,new_name,initializing_qm)
    Object namable_frame, new_name, initializing_qm;
{
    Object names, new_value, temp;

    x_note_fn_call(87,93);
    names = get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    new_value = Nil;
    if ( !TRUEP(names))
	return VALUES_1(Nil);
    else {
	temp = CONSP(names) ? memq_function(new_name,names) : EQ(new_name,
		names) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if ( !TRUEP(new_name)) {
	    if (CONSP(names)) {
		if (initializing_qm)
		    return put_name_or_names_for_frame(namable_frame,
			    CAR(names),initializing_qm);
		else
		    return change_slot_value(3,namable_frame,
			    Qname_or_names_for_frame,CAR(names));
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    new_value = ATOM(names) ? slot_value_list_2(names,new_name) : 
		    slot_value_cons_1(CAR(names),
		    slot_value_cons_1(new_name,CDDR(names)));
	    if (initializing_qm)
		return put_name_or_names_for_frame(namable_frame,new_value,
			initializing_qm);
	    else
		return change_slot_value(3,namable_frame,
			Qname_or_names_for_frame,new_value);
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_flags, Qkb_flags);

static Object string_constant_15;  /* "~A~A~A" */

static Object string_constant_16;  /* "~A~A~A-~D" */

static Object Qsubstitute_class_and_kb_flags;  /* substitute-class-and-kb-flags */

/* MAKE-NEW-NAME-FOR-FRAME */
Object make_new_name_for_frame varargs_1(int, n)
{
    Object part_1;
    Object part_2, part_3, name, substitute_class_and_kb_flags_qm, temp;
    SI_Long i;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,94);
    INIT_ARGS_nonrelocating();
    part_1 = REQUIRED_ARG_nonrelocating();
    part_2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : string_constant_10;
    part_3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : string_constant_10;
    END_ARGS_nonrelocating();
    i = (SI_Long)0L;
    name = Nil;
  next_loop:
    name = intern_text_string(1,i == (SI_Long)0L ? tformat_text_string(4,
	    string_constant_15,part_1,part_2,part_3) : 
	    tformat_text_string(5,string_constant_16,part_1,part_2,part_3,
	    FIX(i)));
    if ( !TRUEP(lookup_kb_specific_property_value(name,
	    Frame_or_frames_with_this_name_kbprop)) &&  
	    !TRUEP(lookup_global_or_kb_specific_property_value(name,
	    Class_description_gkbprop))) {
	if (Loading_kb_p) {
	    substitute_class_and_kb_flags_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
		    Qsubstitute_class_and_kb_flags);
	    if (substitute_class_and_kb_flags_qm && FIXNUM_LT(Kb_flags,
		    M_CDR(substitute_class_and_kb_flags_qm))) {
		temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
			Qsubstitute_class_and_kb_flags);
		temp_1 = TRUEP(CAR(temp));
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(name);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SUBWORKSPACE-IS-NAMED-LIKE-ITS-PARENT-P */
Object subworkspace_is_named_like_its_parent_p(subworkspace)
    Object subworkspace;
{
    Object temp;

    x_note_fn_call(87,95);
    if (ISVREF(subworkspace,(SI_Long)18L)) {
	temp = get_primary_name_for_frame_if_any(ISVREF(subworkspace,
		(SI_Long)18L));
	return VALUES_1(EQ(temp,
		get_primary_name_for_frame_if_any(subworkspace)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qnon_unique_names;   /* non-unique-names */

static Object Qsystem_table;       /* system-table */

static Object Qlocal_name_or_names;  /* local-name-or-names */

/* ADD-AS-FRAME-WITH-NAME */
Object add_as_frame_with_name(namable_frame,name)
    Object namable_frame, name;
{
    Object old_frame_or_frames_with_this_name;
    Object new_frame_or_frames_with_this_name, sub_class_bit_vector, frame;
    Object ab_loop_list_, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(87,96);
    delete_from_frame_note_particulars_list(name,Qnon_unique_names,
	    namable_frame);
    old_frame_or_frames_with_this_name = 
	    lookup_kb_specific_property_value(name,
	    Frame_or_frames_with_this_name_kbprop);
    if ( !TRUEP(old_frame_or_frames_with_this_name))
	new_frame_or_frames_with_this_name = namable_frame;
    else if (ATOM(old_frame_or_frames_with_this_name))
	new_frame_or_frames_with_this_name = EQ(namable_frame,
		old_frame_or_frames_with_this_name) ? 
		old_frame_or_frames_with_this_name : 
		gensym_list_2(old_frame_or_frames_with_this_name,
		namable_frame);
    else
	new_frame_or_frames_with_this_name = memq_function(namable_frame,
		old_frame_or_frames_with_this_name) ? 
		old_frame_or_frames_with_this_name : 
		nconc2(old_frame_or_frames_with_this_name,
		gensym_cons_1(namable_frame,Nil));
    add_or_delete_class_or_name_for_frame(3,namable_frame,name,Nil);
    sub_class_bit_vector = ISVREF(ISVREF(namable_frame,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Authorized_user_class_description,(SI_Long)18L));
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
	maintain_authorized_user(namable_frame);
    mutate_kb_specific_property_value(name,
	    new_frame_or_frames_with_this_name,
	    Frame_or_frames_with_this_name_kbprop);
    if (CONSP(new_frame_or_frames_with_this_name) && 
	    CDR(new_frame_or_frames_with_this_name)) {
	frame = Nil;
	ab_loop_list_ = new_frame_or_frames_with_this_name;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_from_frame_note_particulars_list(name,Qnon_unique_names,frame);
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_post_class_description,(SI_Long)18L));
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
		    lookup_global_or_kb_specific_property_value(Qsystem_table,
		    Class_description_gkbprop);
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
	}
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
	if (temp);
	else
	    temp = TRUEP(get_slot_feature_if_any(3,ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)1L),Qname_or_names_for_frame,
		    Qlocal_name_or_names));
	if ( !temp)
	    add_to_frame_note_particulars_list_if_necessary(name,
		    Qnon_unique_names,frame);
	goto next_loop;
      end_loop:;
    }
    analyze_compiled_items_for_consistency(name);
    return install_item_in_model_if_models_used(namable_frame);
}

/* DELETE-AS-FRAME-WITH-NAME */
Object delete_as_frame_with_name(namable_frame,name)
    Object namable_frame, name;
{
    Object frame_or_frames_with_this_name, frame, ab_loop_list_, temp;
    Object sub_class_bit_vector, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(87,97);
    frame_or_frames_with_this_name = 
	    lookup_kb_specific_property_value(name,
	    Frame_or_frames_with_this_name_kbprop);
    add_or_delete_class_or_name_for_frame(3,namable_frame,name,T);
    if (EQ(frame_or_frames_with_this_name,namable_frame))
	frame_or_frames_with_this_name = Nil;
    else if (CONSP(frame_or_frames_with_this_name) && 
	    memq_function(namable_frame,frame_or_frames_with_this_name)) {
	frame = Nil;
	ab_loop_list_ = frame_or_frames_with_this_name;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	delete_from_frame_note_particulars_list(name,Qnon_unique_names,frame);
	goto next_loop;
      end_loop:;
	if ( !TRUEP(CDDR(frame_or_frames_with_this_name))) {
	    temp = EQ(FIRST(frame_or_frames_with_this_name),namable_frame) 
		    ? SECOND(frame_or_frames_with_this_name) : 
		    FIRST(frame_or_frames_with_this_name);
	    reclaim_gensym_list_1(frame_or_frames_with_this_name);
	    frame_or_frames_with_this_name = temp;
	}
	else {
	    frame_or_frames_with_this_name = 
		    delete_gensym_element_1(namable_frame,
		    frame_or_frames_with_this_name);
	    if (CDR(frame_or_frames_with_this_name)) {
		frame = Nil;
		ab_loop_list_ = frame_or_frames_with_this_name;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		frame = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_post_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1);
		else {
		    gensymed_symbol_3 = 
			    lookup_global_or_kb_specific_property_value(Qsystem_table,
			    Class_description_gkbprop);
		    if (gensymed_symbol_3) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp_1 = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		if (temp_1);
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Method_class_description,
			    (SI_Long)18L));
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
		if ( !temp_1)
		    add_to_frame_note_particulars_list_if_necessary(name,
			    Qnon_unique_names,frame);
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
    }
    mutate_kb_specific_property_value(name,frame_or_frames_with_this_name,
	    Frame_or_frames_with_this_name_kbprop);
    analyze_compiled_items_for_consistency(name);
    return install_item_in_model_if_models_used(namable_frame);
}

/* ENSURE-NAMED-FRAME-IS-FIRST-FETCHED */
Object ensure_named_frame_is_first_fetched(namable_frame)
    Object namable_frame;
{
    Object names_sic, name, frame_or_frames_with_this_name, l_trailer, l;
    Object cdr_new_value;

    x_note_fn_call(87,98);
    names_sic = get_lookup_slot_value_given_default(namable_frame,
	    Qname_or_names_for_frame,Nil);
    name = Nil;
  next_loop:
    name = CONSP(names_sic) ? CAR(names_sic) : names_sic;
    if ( !TRUEP(name))
	goto end_loop;
    frame_or_frames_with_this_name = 
	    lookup_kb_specific_property_value(name,
	    Frame_or_frames_with_this_name_kbprop);
    if ( !(ATOM(frame_or_frames_with_this_name) || 
	    EQ(CAR(frame_or_frames_with_this_name),namable_frame))) {
	l_trailer = frame_or_frames_with_this_name;
	l = CDR(frame_or_frames_with_this_name);
      next_loop_1:
	if ( !TRUEP(l))
	    goto end_loop_1;
	if (EQ(CAR(l),namable_frame)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer) = cdr_new_value;
	    M_CDR(l) = frame_or_frames_with_this_name;
	    mutate_kb_specific_property_value(name,l,
		    Frame_or_frames_with_this_name_kbprop);
	    goto end_1;
	}
	l_trailer = l;
	l = M_CDR(l);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-NAME-OR-NAMES-FOR-FRAME-VALUE */
Object reclaim_name_or_names_for_frame_value(name_or_names,frame)
    Object name_or_names, frame;
{
    x_note_fn_call(87,99);
    change_slot_value(3,frame,Qname_or_names_for_frame,Nil);
    return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* WRITE-NON-UNIQUE-NAMES-NOTE */
Object write_non_unique_names_note(non_unique_names,gensymed_symbol)
    Object non_unique_names, gensymed_symbol;
{
    Object ab_loop_destructure_, non_unique_name, rest_of_names, temp;

    x_note_fn_call(87,100);
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)15L));
    ab_loop_destructure_ = non_unique_names;
    non_unique_name = Nil;
    rest_of_names = Nil;
    non_unique_name = CAR(ab_loop_destructure_);
    rest_of_names = CDR(ab_loop_destructure_);
  next_loop:
    temp = lookup_kb_specific_property_value(non_unique_name,
	    Frame_or_frames_with_this_name_kbprop);
    if (ATOM(temp))
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)25L));
    else {
	twrite(length(lookup_kb_specific_property_value(non_unique_name,
		Frame_or_frames_with_this_name_kbprop)));
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)22L));
	twrite(non_unique_name);
    }
    if ( !TRUEP(rest_of_names)) {
	temp = Nil;
	goto end_1;
    }
    twrite_beginning_of_wide_string(array_constant_6,FIX((SI_Long)5L));
    non_unique_name = CAR(rest_of_names);
    rest_of_names = CDR(rest_of_names);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CHANGE-SLOT-VALUE */
Object change_slot_value varargs_1(int, n)
{
    Object frame, slot_name, new_value;
    Object class_if_specific_qm, slot_component_name_qm;
    Object slot_component_indicator_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,101);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    new_value = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return change_slot_description_value_function(frame,
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm),new_value,
	    slot_component_name_qm,slot_component_indicator_qm);
}

static Object Qslot_putter;        /* slot-putter */

static Object Qslot_category;      /* slot-category */

static Object Qput_attribute_value;  /* put-attribute-value */

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qnote_slot_changes;  /* note-slot-changes */

/* CHANGE-SLOT-DESCRIPTION-VALUE-FUNCTION */
Object change_slot_description_value_function(frame,slot_description,
	    new_value,slot_component_name_qm,slot_component_indicator_qm)
    Object frame, slot_description, new_value, slot_component_name_qm;
    Object slot_component_indicator_qm;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, stack_of_slot_value_changes, pretty_slot_name;
    Object defining_class, do_not_reclaim_old_value_override_qm, old_value;
    Object do_not_reclaim_old_value_qm, slot_component_putter_qm, value;
    Object dont_reclaim_qm, temp_1, slot_putter_qm, list_1;
    Object vector_slot_index_qm, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm, slot_features;
    Object sub_class_bit_vector, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, temp_3, stack_change_pop_store, cons_1, next_cons;
    SI_Long max_i, i, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(87,102);
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
    if (slot_component_name_qm)
	gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		slot_description),
		stack_change_cons_1(slot_component_name_qm,
		slot_component_indicator_qm));
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
	M_CAR(gensymed_symbol_1) = frame;
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
      if ( !EQ(new_value,Just_update_representations_of_slot_value)) {
	  pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	  defining_class = ISVREF(slot_description,(SI_Long)3L);
	  do_not_reclaim_old_value_override_qm = Nil;
	  old_value = Nil;
	  do_not_reclaim_old_value_qm = Nil;
	  if (slot_component_name_qm || slot_component_indicator_qm) {
	      result = get_slot_component_value(frame,pretty_slot_name,
		      defining_class,slot_component_name_qm,
		      slot_component_indicator_qm);
	      MVS_2(result,old_value,do_not_reclaim_old_value_qm);
	      if ( !(Do_not_note_permanent_changes_p || 
		      slot_value_equal_p(old_value,new_value)))
		  note_permanent_change_to_component(frame,
			  slot_description,slot_component_name_qm,
			  slot_component_indicator_qm);
	      slot_component_putter_qm = 
		      get_slot_component_putter_if_any(frame,
		      pretty_slot_name,defining_class,
		      slot_component_name_qm,slot_component_indicator_qm);
	      if (slot_component_putter_qm) {
		  result = inline_funcall_6(slot_component_putter_qm,frame,
			  pretty_slot_name,defining_class,
			  slot_component_indicator_qm,new_value,Nil);
		  MVS_2(result,value,dont_reclaim_qm);
		  if (dont_reclaim_qm)
		      do_not_reclaim_old_value_qm = T;
		  temp_1 = value;
	      }
	      else
		  temp_1 = set_slot_component_value(frame,pretty_slot_name,
			  defining_class,slot_component_name_qm,
			  slot_component_indicator_qm,new_value);
	  }
	  else {
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
		      slot_putter_qm =  !(list_1 ? 
			      TRUEP(M_CAR(M_CDR(list_1))) : TRUEP(Nil)) ? 
			      Qput_attribute_value : Nil;
		  }
	      }
	      else
		  slot_putter_qm = Qput_attribute_value;
	      if (EQ(slot_putter_qm,Qput_attribute_value)) {
		  do_not_reclaim_old_value_qm = T;
		  temp_1 = put_attribute_description_value(frame,
			  slot_description,new_value,
			  do_not_reclaim_old_value_override_qm);
	      }
	      else {
		  vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
		  if (vector_slot_index_qm)
		      old_value = ISVREF(frame,IFIX(vector_slot_index_qm));
		  else {
		      user_vector_slot_index_qm = ISVREF(slot_description,
			      (SI_Long)8L);
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
			      i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),
				      (SI_Long)15L));
			      ab_loop_bind_ = max_i;
			    next_loop_1:
			      if (i >= ab_loop_bind_)
				  goto end_loop_1;
			      if (EQ(ISVREF(lookup_structure_qm,i),
					  slot_name)) {
				  slot_index_qm = FIX(i + (SI_Long)1L);
				  goto end_1;
			      }
			      i = i + (SI_Long)2L;
			      goto next_loop_1;
			    end_loop_1:
			      slot_index_qm = Qnil;
			    end_1:;
			      old_value = slot_index_qm ? 
				      ISVREF(lookup_structure_qm,
				      IFIX(slot_index_qm)) : 
				      ISVREF(slot_description,(SI_Long)6L);
			  }
			  else
			      old_value = ISVREF(slot_description,(SI_Long)6L);
		      }
		  }
		  if ( !(Do_not_note_permanent_changes_p || 
			  slot_value_equal_p(old_value,new_value)))
		      note_permanent_change(frame,slot_description);
		  if (slot_putter_qm) {
		      result = inline_funcall_3(slot_putter_qm,frame,
			      new_value,Nil);
		      MVS_2(result,gensymed_symbol,gensymed_symbol_1);
		      do_not_reclaim_old_value_qm = gensymed_symbol_1;
		      temp_1 = gensymed_symbol;
		  }
		  else {
		      if (Noting_changes_to_kb_p) {
			  slot_features = ISVREF(slot_description,(SI_Long)9L);
			  temp_2 = assq_function(Qtype,slot_features) ?  
				  !TRUEP(assq_function(Qdo_not_save,
				  slot_features)) : 
				  TRUEP(assq_function(Qsave,slot_features));
			  if (temp_2);
			  else
			      temp_2 = 
				      TRUEP(assq_function(Qnote_slot_changes,
				      ISVREF(slot_description,(SI_Long)9L)));
		      }
		      else
			  temp_2 = TRUEP(Nil);
		      if (temp_2) {
			  sub_class_bit_vector = ISVREF(ISVREF(frame,
				  (SI_Long)1L),(SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Block_class_description,
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
			      temp_2 = (SI_Long)0L < gensymed_symbol_2;
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2)
			      note_change_to_block_1(frame,
				      ISVREF(slot_description,(SI_Long)2L));
			  else
			      note_change_to_dependent_frame_1();
		      }
		      temp_1 = 
			      set_slot_description_value_without_noting(frame,
			      slot_description,new_value);
		  }
	      }
	  }
	  if ( !TRUEP(do_not_reclaim_old_value_qm) &&  
		  !TRUEP(do_not_reclaim_old_value_override_qm) && 
		  old_value &&  !EQ(new_value,old_value) &&  
		  !FIXNUMP(old_value) && (slot_component_name_qm ||  
		  !EQ(old_value,ISVREF(slot_description,(SI_Long)6L))))
	      reclaim_slot_value(old_value);
      }
      else
	  temp_1 = Nil;
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_2;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && 
		      EQ(slot_component_name_qm,
		      THIRD(frame_and_slot_or_atom)) && 
		      EQ(slot_component_indicator_qm,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(frame,M_CAR(frame_and_slot_or_atom)) ?
		   T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_2;
	end_loop_2:
	  temp_2 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(frame,slot_description,
		  slot_component_name_qm,slot_component_indicator_qm);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(frame);
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
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pseudo_class_slot_description, Qpseudo_class_slot_description);

static Object Qab_class;           /* class */

/* UPDATE-REPRESENTATIONS-OF-SLOT-VALUE */
Object update_representations_of_slot_value varargs_1(int, n)
{
    Object frame, slot_name;
    Object defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,103);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    defining_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(frame,(SI_Long)9L) || EQ(slot_name,Qname_or_names_for_frame)) {
	temp = EQ(slot_name,Qab_class) ? Pseudo_class_slot_description : 
		get_slot_description_of_class_description_function(slot_name,
		ISVREF(frame,(SI_Long)1L),defining_class_qm);
	return change_slot_description_value_function(frame,temp,
		Just_update_representations_of_slot_value,
		slot_component_name_qm,slot_component_indicator_qm);
    }
    else
	return VALUES_1(Nil);
}

/* SET-SLOT-VALUE-AND-UPDATE-REPRESENTATIONS */
Object set_slot_value_and_update_representations varargs_1(int, n)
{
    Object frame, slot_name, new_value;
    Object defining_class_qm, slot_component_name_qm;
    Object slot_component_indicator_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, temp_1, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_3, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(87,104);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    new_value = REQUIRED_ARG_nonrelocating();
    defining_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_component_indicator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_description = 
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(frame,(SI_Long)1L),defining_class_qm);
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
    if (slot_component_name_qm)
	gensymed_symbol_1 = nconc2(stack_change_list_2(frame,
		slot_description),
		stack_change_cons_1(slot_component_name_qm,
		slot_component_indicator_qm));
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
	M_CAR(gensymed_symbol_1) = frame;
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
      temp_1 = set_slot_value_function(frame,slot_name,new_value,
	      defining_class_qm);
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_3 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_3) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && 
		      EQ(slot_component_name_qm,
		      THIRD(frame_and_slot_or_atom)) && 
		      EQ(slot_component_indicator_qm,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(frame,M_CAR(frame_and_slot_or_atom)) ?
		   T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_2 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(frame,slot_description,
		  slot_component_name_qm,slot_component_indicator_qm);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(frame);
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
	  temp_3 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_3);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
      result = VALUES_1(temp_1);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Items_deleted_since_load_or_save, Qitems_deleted_since_load_or_save);

DEFINE_VARIABLE_WITH_SYMBOL(Items_deleted_since_load_or_save_tail, Qitems_deleted_since_load_or_save_tail);

/* ADD-DELETED-ITEM-TO-LIST */
Object add_deleted_item_to_list(item,frame_qm)
    Object item, frame_qm;
{
    Object frame_serial_number, cdr_arg, cdr_new_value;

    x_note_fn_call(87,105);
    frame_serial_number = copy_frame_serial_number(frame_qm ? ISVREF(item,
	    (SI_Long)3L) : frame_serial_number_for_connection_function(item));
    if (Items_deleted_since_load_or_save) {
	cdr_arg = Items_deleted_since_load_or_save_tail;
	cdr_new_value = journal_cons_1(frame_serial_number,Nil);
	Items_deleted_since_load_or_save_tail = M_CDR(cdr_arg) = cdr_new_value;
	return VALUES_1(Items_deleted_since_load_or_save_tail);
    }
    else {
	Items_deleted_since_load_or_save_tail = 
		journal_cons_1(frame_serial_number,Nil);
	Items_deleted_since_load_or_save = 
		Items_deleted_since_load_or_save_tail;
	return VALUES_1(Items_deleted_since_load_or_save);
    }
}

/* RECLAIM-ITEMS-DELETED-SINCE-LOAD-OR-SAVE */
Object reclaim_items_deleted_since_load_or_save()
{
    Object frame_serial_number, ab_loop_list_;

    x_note_fn_call(87,106);
    frame_serial_number = Nil;
    ab_loop_list_ = Items_deleted_since_load_or_save_tail;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame_serial_number = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(frame_serial_number);
    goto next_loop;
  end_loop:;
    reclaim_journal_list_1(Items_deleted_since_load_or_save);
    Items_deleted_since_load_or_save = Nil;
    Items_deleted_since_load_or_save_tail = Nil;
    return VALUES_1(Items_deleted_since_load_or_save_tail);
}

/* NOTE-DELETION-OF-BLOCK-1 */
Object note_deletion_of_block_1(block)
    Object block;
{
    x_note_fn_call(87,107);
    note_deletion_of_block_2(block);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_with_relation_instances_from_kb_read, Qblocks_with_relation_instances_from_kb_read);

/* DO-BLOCK-SPECIFIC-DELETION-STUFF */
Object do_block_specific_deletion_stuff(frame)
    Object frame;
{
    Object sub_class_bit_vector, gensymed_symbol_3, frame_1, sub_vector_qm;
    Object function_qm, gensymed_symbol_4, old_tree, gensymed_symbol_5;
    Object gensymed_symbol_6, result_1, current_flag_state_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, method_index;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(87,108);
    if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)2048L)) {
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	remove_as_block_being_dragged(frame);
    remove_block_from_native_views(frame);
    note_deletion_of_block_for_selection(frame);
    if (Noting_changes_to_kb_p)
	note_deletion_of_block_1(frame);
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
    if (gensymed_symbol_3) {
	update_images_of_block(frame,Qdelete,Nil);
	remove_as_subblock_if_necessary(1,frame);
    }
    else {
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
	    remove_as_subblock_if_necessary(1,frame);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
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
	    if (temp)
		delete_image_planes_workspace_is_on(frame);
	}
    }
    if (ISVREF(frame,(SI_Long)13L))
	remove_element_from_all_g2_lists(frame,Nil);
    method_index = (SI_Long)31L;
    frame_1 = frame;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
	    (SI_Long)11L),method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    if (function_qm)
	inline_funcall_2(function_qm,frame_1,Nil);
    if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L) && ISVREF(frame,
	    (SI_Long)12L)) {
	if (Releasing_kb_qm) {
	  next_loop:
	    gensymed_symbol_3 = ISVREF(frame,(SI_Long)12L);
	    gensymed_symbol_4 = Nil;
	    if (CAS_SVREF(frame,(SI_Long)12L,gensymed_symbol_3,
		    gensymed_symbol_4)) {
		old_tree = gensymed_symbol_3;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    old_tree = Qnil;
	  end_1:
	    reclaim_relation_instances(old_tree);
	}
	else {
	    remove_transient_relation_instances(frame,Nil);
	    if (Reading_kb_p)
		Blocks_with_relation_instances_from_kb_read = 
			delete_gensym_element_1(frame,
			Blocks_with_relation_instances_from_kb_read);
	}
    }
    if ( !((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
	    (SI_Long)16777216L))) {
	gensymed_symbol_3 = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	gensymed_symbol_4 = frame;
	gensymed_symbol_5 = Nil;
	gensymed_symbol_6 = T;
	inline_funcall_3(gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5,gensymed_symbol_6);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(frame,
	    (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
    if ( !TRUEP(current_flag_state_qm)) {
	svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | (SI_Long)16777216L;
	ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
    }
    method_index = (SI_Long)1L;
    frame_1 = frame;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
	    (SI_Long)11L),method_index);
    function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
    result_1 = function_qm ? inline_funcall_1(function_qm,frame_1) : Nil;
    if ( !TRUEP(current_flag_state_qm)) {
	svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) &  
		~(SI_Long)16777216L;
	ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
    }
    return VALUES_1(result_1);
}

static Object Qunspecified;        /* unspecified */

/* COMPILE-MODULE-NAME?-FOR-SLOT */
Object compile_module_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,109);
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
    if (EQ(parse_result,Qunspecified))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* MODULE-NAME?-EVALUATION-SETTER */
Object module_name_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(87,110);
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
		      goto end_module_name_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_module_name_qm_evaluation_setter:
    return result;
}

/* MODULE-NAME?-EVALUATION-GETTER */
Object module_name_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(87,111);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

/* WRITE-MODULE-NAME?-FROM-SLOT */
Object write_module_name_qm_from_slot(module_name_qm,gensymed_symbol)
    Object module_name_qm, gensymed_symbol;
{
    x_note_fn_call(87,112);
    if ( !TRUEP(module_name_qm))
	return twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)11L));
    else
	return twrite_symbol(1,module_name_qm);
}

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* PUT-MODULE-THIS-IS-PART-OF? */
Object put_module_this_is_part_of_qm(kb_workspace,value,initializing_qm)
    Object kb_workspace, value, initializing_qm;
{
    Object old_module_qm;

    x_note_fn_call(87,113);
    if (EQ(value,No_value) && initializing_qm)
	value = Nil;
    old_module_qm =  !TRUEP(initializing_qm) ? 
	    get_lookup_slot_value(kb_workspace,Qmodule_this_is_part_of_qm) 
	    : Nil;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_workspace,Qmodule_this_is_part_of_qm);
    set_lookup_slot_value_1(kb_workspace,Qmodule_this_is_part_of_qm,value);
    if ( !TRUEP(initializing_qm))
	note_modification_of_module_for_clear_text(value,old_module_qm);
    if (old_module_qm)
	add_or_delete_as_workspace_belonging_to_module(kb_workspace,
		old_module_qm,T);
    if (value)
	add_or_delete_as_workspace_belonging_to_module(kb_workspace,value,Nil);
    if ( !(EQ(old_module_qm,value) || (SI_Long)0L != 
	    (IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & (SI_Long)512L))) {
	if (old_module_qm)
	    inform_ui_client_interfaces_of_top_level_workspace_assignment_change(kb_workspace,
		    Nil,old_module_qm);
	if (value)
	    inform_ui_client_interfaces_of_top_level_workspace_assignment_change(kb_workspace,
		    T,value);
    }
    if ( !TRUEP(initializing_qm))
	update_module_related_frame_notes_for_all_workspaces(2,
		kb_workspace,old_module_qm);
    return VALUES_1(value);
}

static Object Qkb_workspace;       /* kb-workspace */

/* INITIALIZE-FOR-KB-WORKSPACE */
Object initialize_for_kb_workspace(kb_workspace)
    Object kb_workspace;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(87,114);
    frame = kb_workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
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

DEFINE_VARIABLE_WITH_SYMBOL(Dynamic_menus_modification_tick, Qdynamic_menus_modification_tick);

static Object Qlanguage;           /* language */

static Object Quser_mode;          /* user-mode */

static Object Qlogged_in;          /* logged-in */

/* DECACHE-DYNAMIC-MENUS */
Object decache_dynamic_menus varargs_1(int, n)
{
    Object type;
    Object workstation_qm, svref_arg_1, workstation, ab_loop_list_;
    SI_Long svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(87,115);
    INIT_ARGS_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    workstation_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(type,Qlanguage) || EQ(type,Quser_mode)) {
	if (workstation_qm) {
	    svref_arg_1 = ISVREF(workstation_qm,(SI_Long)1L);
	    return VALUES_1(ISVREF(svref_arg_1,(SI_Long)56L) = 
		    FIX((SI_Long)-1L));
	}
	else {
	    workstation = Nil;
	    ab_loop_list_ = Workstations_in_service;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    workstation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in) &&  
		    !TRUEP(ISVREF(workstation,(SI_Long)27L)) && 
		    native_menu_bar_p(ISVREF(workstation,(SI_Long)1L))) {
		svref_arg_1 = ISVREF(workstation,(SI_Long)1L);
		ISVREF(svref_arg_1,(SI_Long)56L) = FIX((SI_Long)-1L);
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else if (workstation_qm) {
	svref_arg_1 = ISVREF(workstation_qm,(SI_Long)1L);
	svref_new_value = IFIX(FIXNUM_SUB1(ISVREF(ISVREF(workstation_qm,
		(SI_Long)1L),(SI_Long)56L))) & (SI_Long)16777215L;
	return VALUES_1(ISVREF(svref_arg_1,(SI_Long)56L) = 
		FIX(svref_new_value));
    }
    else {
	Dynamic_menus_modification_tick = 
		FIX(IFIX(FIXNUM_ADD1(Dynamic_menus_modification_tick)) & 
		(SI_Long)16777215L);
	return VALUES_1(Dynamic_menus_modification_tick);
    }
}

/* NATIVE-MENU-BAR-REALLY-NEEDS-UPDATING-P */
Object native_menu_bar_really_needs_updating_p(workstation)
    Object workstation;
{
    Object gensym_window;

    x_note_fn_call(87,116);
    if (workstation) {
	gensym_window = ISVREF(workstation,(SI_Long)1L);
	if (native_menu_bar_p(gensym_window))
	    return VALUES_1(IFIX(ISVREF(gensym_window,(SI_Long)56L)) == 
		    (SI_Long)-1L ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qnamed_workspaces;   /* named-workspaces */

/* NOTE-NAME-CHANGE-FOR-KB-WORKSPACE */
Object note_name_change_for_kb_workspace(kb_workspace,old_names,initializing_p)
    Object kb_workspace, old_names, initializing_p;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(87,117);
    frame = kb_workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)10L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_workspace)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_3(method_function_qm,frame,old_names,initializing_p);
    return decache_dynamic_menus(1,Qnamed_workspaces);
}

/* PUT-KB-NAME-WHERE-SLOT-IS-ABSENT */
Object put_kb_name_where_slot_is_absent(frame,name)
    Object frame, name;
{
    x_note_fn_call(87,118);
    return VALUES_1(Nil);
}

/* PUT-KB-NAME-FOR-WORKSPACE-WHERE-SLOT-IS-ABSENT */
Object put_kb_name_for_workspace_where_slot_is_absent(frame,name)
    Object frame, name;
{
    x_note_fn_call(87,119);
    return VALUES_1(Nil);
}

/* PUT-INITIALIZATION-INTERVAL-WHERE-SLOT-IS-ABSENT */
Object put_initialization_interval_where_slot_is_absent(kb_workspace,value)
    Object kb_workspace, value;
{
    x_note_fn_call(87,120);
    return VALUES_1(Nil);
}

/* ITEM-WORKSPACE-P */
Object item_workspace_p(frame)
    Object frame;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(87,121);
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
	return VALUES_1(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L));
    else
	return VALUES_1(Nil);
}

/* GET-REFERENCE-TO-ITEM-NO-COPY */
Object get_reference_to_item_no_copy(item)
    Object item;
{
    x_note_fn_call(87,122);
    return VALUES_1(ISVREF(item,(SI_Long)2L));
}

/* GET-REFERENCE-TO-ITEM */
Object get_reference_to_item(item)
    Object item;
{
    x_note_fn_call(87,123);
    return copy_evaluation_item_reference(ISVREF(item,(SI_Long)2L));
}

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

/* COMPILE-UUID-FOR-SLOT */
Object compile_uuid_for_slot varargs_1(int, n)
{
    Object parse_result, item, gensymed_symbol;
    Object temp, temp_1, uuid_qm, problem_report_qm, uuid, existing_item;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(87,124);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(text_string_p(parse_result))) {
	temp = Bad_phrase;
	temp_1 = copy_constant_wide_string_given_length(array_constant_8,
		FIX((SI_Long)34L));
	return VALUES_2(temp,temp_1);
    }
    else {
	result = convert_uuid_representation_to_internal(parse_result);
	MVS_2(result,uuid_qm,problem_report_qm);
	if ( !TRUEP(uuid_qm))
	    return VALUES_2(Bad_phrase,problem_report_qm);
	else {
	    uuid = uuid_qm;
	    existing_item = get_item_or_item_list_for_uuid(uuid);
	    if (existing_item && item &&  !EQ(item,existing_item)) {
		if (!Nil)
		    reclaim_text_string(uuid);
		temp = Bad_phrase;
		temp_1 = 
			copy_constant_wide_string_given_length(array_constant_9,
			FIX((SI_Long)39L));
		return VALUES_2(temp,temp_1);
	    }
	    else {
		if (Current_edit_state)
		    note_use_of_text_string_in_phrase(uuid);
		return VALUES_1(uuid);
	    }
	}
    }
}

/* WRITE-UUID-FROM-SLOT */
Object write_uuid_from_slot(uuid,gensymed_symbol)
    Object uuid, gensymed_symbol;
{
    x_note_fn_call(87,125);
    return twrite_uuid_printed_representation_as_string(uuid);
}

/* RECLAIM-UUID-VALUE */
Object reclaim_uuid_value(unique_reference,frame)
    Object unique_reference, frame;
{
    x_note_fn_call(87,126);
    put_uuid(frame,Nil,Nil);
    return VALUES_1(Nil);
}

/* ITEM-UUID */
Object item_uuid(system_item)
    Object system_item;
{
    Object item_reference_qm, temp;

    x_note_fn_call(87,127);
    item_reference_qm = ISVREF(system_item,(SI_Long)2L);
    temp = item_reference_qm ? 
	    evaluation_item_reference_uuid(item_reference_qm) : Nil;
    return VALUES_1(temp);
}

static Object Quuid;               /* uuid */

/* PUT-NEW-UUID */
Object put_new_uuid(frame)
    Object frame;
{
    Object new_item_reference, svref_arg_1;

    x_note_fn_call(87,128);
    new_item_reference = get_item_reference_for_new_uuid();
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Quuid);
    SVREF(frame,FIX((SI_Long)2L)) = new_item_reference;
    svref_arg_1 = M_CAR(new_item_reference);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = frame;
    return VALUES_1(Nil);
}

/* PUT-UUID */
Object put_uuid(frame,uuid_qm,initializing_qm)
    Object frame, uuid_qm, initializing_qm;
{
    Object old_item_reference, new_item_reference, svref_arg_1;
    SI_Long length_1;

    x_note_fn_call(87,129);
    old_item_reference = ISVREF(frame,(SI_Long)2L);
    if (uuid_qm) {
	if (valid_uuid_p(uuid_qm)) {
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(uuid_qm));
	    length_1 = UBYTE_16_ISAREF_1(uuid_qm,length_1 - (SI_Long)2L) + 
		    ((UBYTE_16_ISAREF_1(uuid_qm,length_1 - (SI_Long)1L) & 
		    (SI_Long)8191L) << (SI_Long)16L);
	    UBYTE_16_ISASET_1(uuid_qm,length_1,(SI_Long)1L);
	}
	new_item_reference = get_item_reference_for_uuid(uuid_qm,T,T);
    }
    else
	new_item_reference = Nil;
    if (EQ(old_item_reference,new_item_reference));
    else if (new_item_reference && ISVREF(M_CAR(new_item_reference),
	    (SI_Long)3L))
	reclaim_evaluation_item_reference(new_item_reference);
    else {
	if (old_item_reference) {
	    svref_arg_1 = M_CAR(old_item_reference);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
	    reclaim_evaluation_item_reference(old_item_reference);
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(frame,Quuid);
	SVREF(frame,FIX((SI_Long)2L)) = new_item_reference;
	if (new_item_reference) {
	    svref_arg_1 = M_CAR(new_item_reference);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = frame;
	}
    }
    if (uuid_qm)
	reclaim_text_string(uuid_qm);
    return VALUES_2(new_item_reference,T);
}

static Object Qg2_defstruct_structure_name_type_description_g2_struct;  /* g2-defstruct-structure-name::type-description-g2-struct */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* AB-SUBTYPEP-1 */
Object ab_subtypep_1(class_1,class_2)
    Object class_1, class_2;
{
    x_note_fn_call(87,130);
    if (SIMPLE_VECTOR_P(class_1) && EQ(ISVREF(class_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_type_description_g2_struct) && 
	    SIMPLE_VECTOR_P(class_2) && EQ(ISVREF(class_2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_type_description_g2_struct))
	return subtype_p_using_type_descriptions(class_1,class_2);
    else if (SIMPLE_VECTOR_P(class_1) && EQ(ISVREF(class_1,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct) && 
	    SIMPLE_VECTOR_P(class_2) && EQ(ISVREF(class_2,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	return memq_function(ISVREF(class_2,(SI_Long)1L),ISVREF(class_1,
		(SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtype_description_of_type;  /* type-description-of-type */

/* AB-SUBTYPEP */
Object ab_subtypep(type_1,type_2)
    Object type_1, type_2;
{
    Object class_1, class_2;

    x_note_fn_call(87,131);
    if (EQ(type_2,T))
	return VALUES_1(T);
    else if (EQ(type_1,T))
	return VALUES_1(Nil);
    else {
	class_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(type_1),
		Qtype_description_of_type);
	if (class_1);
	else
	    class_1 = lookup_global_or_kb_specific_property_value(type_1,
		    Class_description_gkbprop);
	class_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(type_2),
		Qtype_description_of_type);
	if (class_2);
	else
	    class_2 = lookup_global_or_kb_specific_property_value(type_2,
		    Class_description_gkbprop);
	return ab_subtypep_1(class_1,class_2);
    }
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* AB-TYPEP-FUNCTION */
Object ab_typep_function(thing,ab_type)
    Object thing, ab_type;
{
    Object x2, temp_1, possible_type_name_qm, temp_2;
    char temp;

    x_note_fn_call(87,132);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(thing,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    else {
	possible_type_name_qm = Nil;
	if (SIMPLE_VECTOR_P(thing) && FIXNUM_LE(FIX((SI_Long)1L),
		length(thing))) {
	    possible_type_name_qm = ISVREF(thing,(SI_Long)0L);
	    temp = TRUEP(possible_type_name_qm);
	}
	else
	    temp = TRUEP(Nil);
	temp_1 = (temp ? SYMBOLP(possible_type_name_qm) : TRUEP(Nil)) ? 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(possible_type_name_qm),
		Qtype_description_of_unique_type_name_of_gensym_structure) 
		: Nil;
	if (temp_1);
	else
	    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(T),
		    Qtype_description_of_type);
    }
    temp_2 = getfq_function_no_default(INLINE_SYMBOL_PLIST(ab_type),
	    Qtype_description_of_type);
    if (temp_2);
    else
	temp_2 = lookup_global_or_kb_specific_property_value(ab_type,
		Class_description_gkbprop);
    return ab_subtypep_1(temp_1,temp_2);
}

/* GET-ATTRIBUTE-DESCRIPTION-FROM-CLASS-DESCRIPTION */
Object get_attribute_description_from_class_description(class_description,
	    attribute_name,class_qualifier_qm)
    Object class_description, attribute_name, class_qualifier_qm;
{
    Object slot_description_qm, temp, va, aliased_slot_name;

    x_note_fn_call(87,133);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(attribute_name,
	    class_description,class_qualifier_qm);
    if (slot_description_qm && ISVREF(slot_description_qm,(SI_Long)8L))
	temp = slot_description_qm;
    else {
	va = get_property_value_function(3,
		get_symbol_properties_function(attribute_name),
		Qvirtual_attribute,Nil);
	temp = va && virtual_attribute_defined_for_class_qm(va,
		ISVREF(class_description,(SI_Long)1L)) ? va : Nil;
	if (temp);
	else {
	    aliased_slot_name = 
		    get_slot_name_for_alias_if_any(attribute_name,
		    ISVREF(class_description,(SI_Long)1L));
	    temp = aliased_slot_name ? 
		    get_slot_description_of_class_description_function(aliased_slot_name,
		    class_description,class_qualifier_qm) : 
		    slot_description_qm;
	}
    }
    return VALUES_1(temp);
}

static Object Qtext;               /* text */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qcategory_committer_function;  /* category-committer-function */

static Object Qdefault_category_slot_access_committer;  /* default-category-slot-access-committer */

static Object Qcategory_extracter_function;  /* category-extracter-function */

static Object Qdefault_category_slot_access_extracter;  /* default-category-slot-access-extracter */

/* CACHE-EVALUATOR-SLOT-INFO */
Object cache_evaluator_slot_info(slot_description)
    Object slot_description;
{
    Object slot_info, slot_type_qm, category_qm, text_slot_qm;
    Object category_evaluator_interface, category_setter, category_getter;
    Object category_committer, category_extracter, virtual_attribute;

    x_note_fn_call(87,134);
    slot_info = make_evaluator_slot_info_1();
    slot_type_qm = assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L));
    category_qm = slot_type_qm ? SECOND(slot_type_qm) : Nil;
    text_slot_qm = slot_type_qm ? memq_function(Qtext,CDDR(slot_type_qm)) :
	     Nil;
    if (category_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
		Qcategory_evaluator_interface);
	category_setter = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    }
    else
	category_setter = Nil;
    if (category_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
		Qcategory_evaluator_interface);
	category_getter = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    }
    else
	category_getter = Nil;
    category_committer = get_property_value_function(3,
	    get_symbol_properties_function(category_qm),
	    Qcategory_committer_function,Nil);
    if (category_committer);
    else
	category_committer = 
		SYMBOL_FUNCTION(Qdefault_category_slot_access_committer);
    category_extracter = get_property_value_function(3,
	    get_symbol_properties_function(category_qm),
	    Qcategory_extracter_function,Nil);
    if (category_extracter);
    else
	category_extracter = 
		SYMBOL_FUNCTION(Qdefault_category_slot_access_extracter);
    virtual_attribute = get_property_value_function(3,
	    get_symbol_properties_function(ISVREF(slot_description,
	    (SI_Long)2L)),Qvirtual_attribute,Nil);
    Any_cached_evaluator_slot_info_p = T;
    SVREF(slot_description,FIX((SI_Long)10L)) = slot_info;
    SVREF(slot_info,FIX((SI_Long)1L)) = category_qm;
    SVREF(slot_info,FIX((SI_Long)2L)) = category_setter;
    SVREF(slot_info,FIX((SI_Long)3L)) = category_getter;
    SVREF(slot_info,FIX((SI_Long)4L)) = category_committer;
    SVREF(slot_info,FIX((SI_Long)5L)) = category_extracter;
    SVREF(slot_info,FIX((SI_Long)6L)) = text_slot_qm;
    SVREF(slot_info,FIX((SI_Long)7L)) = virtual_attribute;
    return VALUES_1(slot_info);
}

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

static Object Qtruth_value;        /* truth-value */

/* GET-ATTRIBUTE-DESCRIPTION-EVALUATION-VALUE */
Object get_attribute_description_evaluation_value(frame,attribute_description)
    Object frame, attribute_description;
{
    Object value, car_1, cdr_1, temp, managed_value, x2, evaluator_info;
    Object category_getter_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, extracted_value, reclaim_p, gensymed_symbol_3;
    Object getter_qm;
    char temp_1;
    Object result;

    x_note_fn_call(87,135);
    if (EQ(ISVREF(attribute_description,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	if (ISVREF(attribute_description,(SI_Long)8L)) {
	    value = ISVREF(ISVREF(frame,(SI_Long)0L),
		    IFIX(ISVREF(attribute_description,(SI_Long)8L)));
	    if (CONSP(value)) {
		car_1 = M_CAR(value);
		cdr_1 = M_CDR(value);
		if (CONSP(cdr_1)) {
		    temp = M_CAR(cdr_1);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 = temp_1 ? slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		managed_value = M_CAR(value);
		if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(value))),
			Qtruth_value)) {
		    if (FIXNUM_EQ(managed_value,Truth))
			temp = Evaluation_true_value;
		    else if (FIXNUM_EQ(managed_value,Falsity))
			temp = Evaluation_false_value;
		    else
			temp = eval_cons_1(managed_value,Qtruth_value);
		}
		else
		    temp = FIXNUMP(managed_value) || 
			    SYMBOLP(managed_value) ? managed_value : 
			    copy_evaluation_value_1(managed_value);
	    }
	    else {
		if (SIMPLE_VECTOR_P(value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    temp = serve_item_p(value) ? value : Nil;
		else if (value)
		    temp = FIXNUMP(value) || value && SYMBOLP(value) ? 
			    value : copy_evaluation_value_1(value);
		else
		    temp = Nil;
	    }
	}
	else {
	    evaluator_info = ISVREF(attribute_description,(SI_Long)10L);
	    if (evaluator_info);
	    else
		evaluator_info = 
			cache_evaluator_slot_info(attribute_description);
	    category_getter_qm = ISVREF(evaluator_info,(SI_Long)3L);
	    if (category_getter_qm) {
		gensymed_symbol = ISVREF(evaluator_info,(SI_Long)5L);
		gensymed_symbol_1 = get_slot_description_value(frame,
			attribute_description);
		gensymed_symbol_2 = evaluator_info;
		result = inline_funcall_2(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2);
		MVS_2(result,extracted_value,reclaim_p);
		gensymed_symbol = category_getter_qm;
		gensymed_symbol_1 = extracted_value;
		gensymed_symbol_2 = frame;
		gensymed_symbol_3 = attribute_description;
		temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		if (reclaim_p)
		    reclaim_slot_value(extracted_value);
	    }
	    else
		temp = Nil;
	}
    }
    else if (type_specification_type_p(frame,ISVREF(attribute_description,
	    (SI_Long)2L))) {
	getter_qm = ISVREF(attribute_description,(SI_Long)6L);
	value = getter_qm ? inline_funcall_1(getter_qm,frame) : 
		No_component_value;
	temp = EQ(value,No_component_value) ? Nil : value;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CHANGE-ATTRIBUTE-DESCRIPTION-EVALUATION-VALUE */
Object change_attribute_description_evaluation_value(frame,
	    attribute_description,new_value)
    Object frame, attribute_description, new_value;
{
    Object pretty_name, unique_name, pretty_slot_name, class_or_frame_qm, temp;
    Object temp_1, slot_description, class_description;
    char temp_2;

    x_note_fn_call(87,136);
    if (SIMPLE_VECTOR_P(attribute_description) && 
	    EQ(ISVREF(attribute_description,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	pretty_name = ISVREF(attribute_description,(SI_Long)2L);
	unique_name = ISVREF(attribute_description,(SI_Long)1L);
	pretty_slot_name = ISVREF(attribute_description,(SI_Long)2L);
	class_or_frame_qm = frame;
	temp = get_alias_for_slot_name_if_any(pretty_slot_name,
		class_or_frame_qm);
	if (temp);
	else
	    temp = pretty_slot_name;
	if (EQ(pretty_name,unique_name))
	    temp_1 = Nil;
	else {
	    slot_description = attribute_description;
	    class_description = ISVREF(frame,(SI_Long)1L);
	    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		temp_1 = ISVREF(slot_description,(SI_Long)3L);
		temp_2 =  !EQ(temp_1,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			(SI_Long)2L),class_description,Nil),(SI_Long)3L));
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		temp_1 = ISVREF(attribute_description,(SI_Long)3L);
	    else
		temp_1 = Nil;
	}
	temp = conclude_into_attribute_component(7,frame,temp,temp_1,
		new_value,Nil,Nil,attribute_description);
    }
    else
	temp = conclude_into_attribute_component(7,frame,
		ISVREF(attribute_description,(SI_Long)1L),Nil,new_value,
		Nil,Nil,attribute_description);
    return VALUES_1(temp);
}

static Object Qslot_value_writer;  /* slot-value-writer */

/* DEFAULT-CATEGORY-SLOT-ACCESS-COMMITTER */
Object default_category_slot_access_committer(compiled_parse_result,
	    evaluation_value,evaluator_info)
    Object compiled_parse_result, evaluation_value, evaluator_info;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(87,137);
    if (ISVREF(evaluator_info,(SI_Long)6L)) {
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
		  gensymed_symbol = ISVREF(evaluator_info,(SI_Long)1L);
		  temp = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qslot_value_writer);
		  FUNCALL_2(temp,compiled_parse_result,compiled_parse_result);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return slot_value_cons_1(compiled_parse_result,
		convert_text_string_to_text(temp));
    }
    else
	return VALUES_1(compiled_parse_result);
}

/* DEFAULT-CATEGORY-SLOT-ACCESS-EXTRACTER */
Object default_category_slot_access_extracter(slot_value,evaluator_info)
    Object slot_value, evaluator_info;
{
    x_note_fn_call(87,138);
    if (ISVREF(evaluator_info,(SI_Long)6L))
	return VALUES_2(CAR(slot_value),Nil);
    else
	return VALUES_2(slot_value,Nil);
}

/* TEXT-CATEGORY-SLOT-ACCESS-COMMITTER */
Object text_category_slot_access_committer(compiled_parse_result,
	    evaluation_value,evaluator_info)
    Object compiled_parse_result, evaluation_value, evaluator_info;
{
    x_note_fn_call(87,139);
    if (ISVREF(evaluator_info,(SI_Long)6L)) {
	if (evaluation_value)
	    return slot_value_cons_1(compiled_parse_result,
		    convert_text_string_to_text(copy_text_string(evaluation_value)));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(compiled_parse_result);
}

/* TEXT-CATEGORY-SLOT-ACCESS-EXTRACTER */
Object text_category_slot_access_extracter(slot_value,evaluator_info)
    Object slot_value, evaluator_info;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(87,140);
    if (ISVREF(evaluator_info,(SI_Long)6L))
	return VALUES_2(CDR(slot_value),Nil);
    else {
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
		  gensymed_symbol = ISVREF(evaluator_info,(SI_Long)1L);
		  temp = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qslot_value_writer);
		  FUNCALL_2(temp,slot_value,slot_value);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = convert_text_string_to_text(temp);
	return VALUES_2(temp,T);
    }
}

static Object Qboth;               /* both */

/* USER-ATTRIBUTE-SLOT-DESCRIPTION-OR-VIRTUAL-ATTRIBUTE */
Object user_attribute_slot_description_or_virtual_attribute(item_or_class_description,
	    attribute,class_specific_attribute_class_qm,direction)
    Object item_or_class_description, attribute;
    Object class_specific_attribute_class_qm, direction;
{
    Object class_description_p, class_description, slot_description_qm;
    Object unaliased_name_qm, type_qm, virtual_attribute_qm, arg_type_qm;
    Object category_interface_qm, gensymed_symbol;
    char temp;

    x_note_fn_call(87,141);
    class_description_p = SIMPLE_VECTOR_P(item_or_class_description) ? 
	    (EQ(ISVREF(item_or_class_description,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct) ? T :
	     Nil) : Qnil;
    class_description = class_description_p ? item_or_class_description : 
	    ISVREF(item_or_class_description,(SI_Long)1L);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(attribute,
	    class_description,class_specific_attribute_class_qm);
    unaliased_name_qm = Nil;
    type_qm = Nil;
    virtual_attribute_qm = Nil;
    arg_type_qm = Nil;
    category_interface_qm = Nil;
    if (slot_description_qm && ISVREF(slot_description_qm,(SI_Long)8L))
	return VALUES_2(slot_description_qm,Nil);
    else {
	unaliased_name_qm = get_slot_name_for_alias_if_any(attribute,
		item_or_class_description);
	if (unaliased_name_qm) {
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(unaliased_name_qm,
		    class_description,class_specific_attribute_class_qm);
	    temp = TRUEP(slot_description_qm);
	}
	else
	    temp = TRUEP(slot_description_qm);
	if (temp) {
	    type_qm = assq_function(Qtype,ISVREF(slot_description_qm,
		    (SI_Long)9L));
	    temp = TRUEP(type_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = SECOND(type_qm);
	    category_interface_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qcategory_evaluator_interface);
	    temp = TRUEP(category_interface_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (EQ(direction,Qget))
		temp = TRUEP(ISVREF(category_interface_qm,(SI_Long)2L));
	    else if (EQ(direction,Qset))
		temp = TRUEP(ISVREF(category_interface_qm,(SI_Long)3L));
	    else if (EQ(direction,Qboth))
		temp = ISVREF(category_interface_qm,(SI_Long)2L) ? 
			TRUEP(ISVREF(category_interface_qm,(SI_Long)3L)) : 
			TRUEP(Qnil);
	    else
		temp = TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_2(slot_description_qm,category_interface_qm);
	else {
	    virtual_attribute_qm = get_property_value_function(3,
		    get_symbol_properties_function(attribute),
		    Qvirtual_attribute,Nil);
	    if (virtual_attribute_qm) {
		arg_type_qm = ISVREF(virtual_attribute_qm,(SI_Long)2L);
		temp = TRUEP(arg_type_qm);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? class_description_p || 
		    type_specification_type_p(item_or_class_description,
		    arg_type_qm) : TRUEP(Nil)) {
		if (EQ(direction,Qget))
		    temp = TRUEP(ISVREF(virtual_attribute_qm,(SI_Long)6L));
		else if (EQ(direction,Qset))
		    temp = TRUEP(ISVREF(virtual_attribute_qm,(SI_Long)7L));
		else if (EQ(direction,Qboth))
		    temp = ISVREF(virtual_attribute_qm,(SI_Long)6L) ? 
			    TRUEP(ISVREF(virtual_attribute_qm,
			    (SI_Long)7L)) : TRUEP(Qnil);
		else
		    temp = TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_2(Nil,virtual_attribute_qm);
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* GET-SLOT-EVALUATION-VALUE-1 */
Object get_slot_evaluation_value_1(item,slot_description_qm,
	    category_interface_or_virtual_attribute_qm)
    Object item, slot_description_qm;
    Object category_interface_or_virtual_attribute_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, value, car_1, cdr_1;
    Object managed_value, x2, evaluator_info, gensymed_symbol_2;
    Object extracted_value, reclaim_p, gensymed_symbol_3;
    char temp_1;
    Object result;

    x_note_fn_call(87,142);
    if ( !TRUEP(slot_description_qm)) {
	gensymed_symbol = 
		ISVREF(category_interface_or_virtual_attribute_qm,(SI_Long)6L);
	gensymed_symbol_1 = item;
	temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else if ( !TRUEP(category_interface_or_virtual_attribute_qm)) {
	value = get_slot_description_value(item,slot_description_qm);
	if (CONSP(value)) {
	    car_1 = M_CAR(value);
	    cdr_1 = M_CDR(value);
	    if (CONSP(cdr_1)) {
		temp = M_CAR(cdr_1);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    managed_value = M_CAR(value);
	    if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(value))),
		    Qtruth_value)) {
		if (FIXNUM_EQ(managed_value,Truth))
		    temp = Evaluation_true_value;
		else if (FIXNUM_EQ(managed_value,Falsity))
		    temp = Evaluation_false_value;
		else
		    temp = eval_cons_1(managed_value,Qtruth_value);
	    }
	    else
		temp = FIXNUMP(managed_value) || SYMBOLP(managed_value) ? 
			managed_value : copy_evaluation_value_1(managed_value);
	}
	else {
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp = serve_item_p(value) ? value : Nil;
	    else
		temp = value;
	}
    }
    else {
	evaluator_info = ISVREF(slot_description_qm,(SI_Long)10L);
	if (evaluator_info);
	else
	    evaluator_info = cache_evaluator_slot_info(slot_description_qm);
	gensymed_symbol = ISVREF(evaluator_info,(SI_Long)5L);
	gensymed_symbol_1 = get_slot_description_value(item,
		slot_description_qm);
	gensymed_symbol_2 = evaluator_info;
	result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2);
	MVS_2(result,extracted_value,reclaim_p);
	gensymed_symbol = ISVREF(evaluator_info,(SI_Long)3L);
	gensymed_symbol_1 = extracted_value;
	gensymed_symbol_2 = item;
	gensymed_symbol_3 = slot_description_qm;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
	if (reclaim_p)
	    reclaim_slot_value(extracted_value);
    }
    return VALUES_1(temp);
}

/* MALFORMED-SYMBOL-NAME-P */
Object malformed_symbol_name_p(symbol)
    Object symbol;
{
    Object symbol_string, symbol_length, temp;
    SI_Long stamp;

    x_note_fn_call(87,143);
    symbol_string = symbol_name_text_string(symbol);
    symbol_length = text_string_length(symbol_string);
    stamp = (SI_Long)38L;
    temp = UBYTE_16_ISAREF_1(symbol_string,(SI_Long)0L) == stamp ? 
	    (UBYTE_16_ISAREF_1(symbol_string,
	    IFIX(FIXNUM_SUB1(symbol_length))) == stamp ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

static Object string_constant_17;  /* "Fixed corrupted attribute name ~A with ~S, ~
				    *                                  please save your KB and notify Gensym Customer Support."
				    */

/* FIND-SIMILAR-SLOT-NAME */
Object find_similar_slot_name(slot_name,class_1)
    Object slot_name, class_1;
{
    Object slot_name_string, slot_name_length, sub1_1, current_class;
    Object class_description, ab_loop_list_, ab_loop_it_, candidate_slot_name;
    Object ab_loop_list__1, candidate_slot_name_string;
    Object candidate_slot_name_length, sub2, end1, end2, ab_loop_iter_flag_;
    Object temp;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp_1;

    x_note_fn_call(87,144);
    slot_name_string = symbol_name_text_string(slot_name);
    slot_name_length = text_string_length(slot_name_string);
    if (IFIX(slot_name_length) >= (SI_Long)5L) {
	sub1_1 = text_string_substring(slot_name_string,FIX((SI_Long)1L),
		FIXNUM_SUB1(slot_name_length));
	current_class = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	current_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	candidate_slot_name = Nil;
	ab_loop_list__1 = 
		ISVREF(lookup_global_or_kb_specific_property_value(current_class,
		Class_description_gkbprop),(SI_Long)7L);
	candidate_slot_name_string = Nil;
	candidate_slot_name_length = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	candidate_slot_name = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	candidate_slot_name_string = 
		symbol_name_text_string(candidate_slot_name);
	candidate_slot_name_length = 
		text_string_length(candidate_slot_name_string);
	if (FIXNUM_EQ(slot_name_length,candidate_slot_name_length)) {
	    sub2 = text_string_substring(candidate_slot_name_string,
		    FIX((SI_Long)1L),FIXNUM_SUB1(candidate_slot_name_length));
	    end1 = text_string_length(sub1_1);
	    end2 = text_string_length(sub2);
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
		if ( !(UBYTE_16_ISAREF_1(sub1_1,index1) == 
			UBYTE_16_ISAREF_1(sub2,index2))) {
		    temp = Nil;
		    goto end_1;
		}
		ab_loop_iter_flag_ = Nil;
		index1 = index1 + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:
		temp = T;
		goto end_1;
		temp = Qnil;
	      end_1:;
	    }
	    else
		temp = Nil;
	    reclaim_text_string(sub2);
	    temp_1 = TRUEP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    notify_user(3,string_constant_17,slot_name,candidate_slot_name);
	    slot_name = candidate_slot_name;
	    ab_loop_it_ = T;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	ab_loop_it_ = Nil;
	goto end_2;
	ab_loop_it_ = Qnil;
      end_2:;
	if (ab_loop_it_)
	    goto end_3;
	goto next_loop;
      end_loop:
	reclaim_text_string(sub1_1);
      end_3:;
    }
    return VALUES_1(slot_name);
}

static Object string_constant_18;  /* "Fixed corrupted class name ~A with ~S, ~
				    *                                please save your KB and notify Gensym Customer Support."
				    */

/* FIND-SIMILAR-CLASS-NAME */
Object find_similar_class_name(class_1)
    Object class_1;
{
    Object class_name_string, class_name_length, sub1_1, scope_conses;
    Object ab_loopvar_, candidate_class_name, candidate_class_name_string;
    Object candidate_class_name_length, temp, sub2, end1, end2;
    Object ab_loop_iter_flag_;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(87,145);
    class_name_string = symbol_name_text_string(class_1);
    class_name_length = text_string_length(class_name_string);
    if (IFIX(class_name_length) >= (SI_Long)5L) {
	sub1_1 = text_string_substring(class_name_string,FIX((SI_Long)1L),
		FIXNUM_SUB1(class_name_length));
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = Qblock;
	candidate_class_name = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  candidate_class_name_string = Nil;
	  candidate_class_name_length = Nil;
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  temp = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  candidate_class_name = temp;
	  candidate_class_name_string = 
		  symbol_name_text_string(candidate_class_name);
	  candidate_class_name_length = 
		  text_string_length(candidate_class_name_string);
	  if (FIXNUM_EQ(class_name_length,candidate_class_name_length)) {
	      sub2 = text_string_substring(candidate_class_name_string,
		      FIX((SI_Long)1L),
		      FIXNUM_SUB1(candidate_class_name_length));
	      end1 = text_string_length(sub1_1);
	      end2 = text_string_length(sub2);
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
		  if ( !(UBYTE_16_ISAREF_1(sub1_1,index1) == 
			  UBYTE_16_ISAREF_1(sub2,index2))) {
		      temp = Nil;
		      goto end_1;
		  }
		  ab_loop_iter_flag_ = Nil;
		  index1 = index1 + (SI_Long)1L;
		  goto next_loop_1;
		end_loop_1:
		  temp = T;
		  goto end_1;
		  temp = Qnil;
		end_1:;
	      }
	      else
		  temp = Nil;
	      reclaim_text_string(sub2);
	      temp_1 = TRUEP(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      notify_user(3,string_constant_18,class_1,candidate_class_name);
	      class_1 = candidate_class_name;
	      goto end_loop;
	  }
	  goto next_loop;
	end_loop:
	  reclaim_text_string(sub1_1);
	POP_SPECIAL();
    }
    return VALUES_1(class_1);
}

void frames5_INIT()
{
    Object temp, temp_1, write_embedded_rule_has_frame_notes_note_1;
    Object write_frame_notes_for_component_particulars_note_1;
    Object write_non_unique_names_note_1, temp_2;
    Object module_name_qm_evaluation_setter_1;
    Object module_name_qm_evaluation_getter_1;
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qput_uuid;
    Object Qslot_value_reclaimer, Qreclaim_uuid_value, Qwrite_uuid_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_uuid_for_slot, list_constant_14;
    Object Qabsent_slot_putter;
    Object Qput_initialization_interval_where_slot_is_absent;
    Object Qinitialization_interval, Qconcurrent_block;
    Object Qput_kb_name_for_workspace_where_slot_is_absent;
    Object Qkb_name_for_workspace, Qput_kb_name_where_slot_is_absent, Qkb_name;
    Object Qclasses_which_define, Qnote_name_change;
    Object Qnote_name_change_for_kb_workspace, Qframes5, Qmodule_assignment;
    Object Qinitialize, Qinitialize_for_kb_workspace;
    Object Qput_module_this_is_part_of_qm, Qwrite_module_name_qm_from_slot;
    Object Qmodule_name_qm, Qnamed, Qtype_specification_simple_expansion;
    Object list_constant_12, Qab_or, Qcompile_module_name_qm_for_slot;
    Object Qbackground_color, Qworkspace_background_color_qm;
    Object Qforeground_color, Qworkspace_foreground_color_qm, list_constant_17;
    Object string_constant_51, Qinitial_width, Qkb_workspace_initial_width;
    Object Qinitial_height, Qkb_workspace_initial_height, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object list_constant_16, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object Qworkspace, Qreclaim_name_or_names_for_frame_value;
    Object Qnote_name_change_for_block, Qgeneric_method_lambda_list;
    Object list_constant_15, Qinitializing_p, Qold_names;
    Object Qput_name_or_names_for_frame, Qframe_or_frames_with_this_name;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_gensym_list_if_list;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qreclaim_grammar_tree_function, string_constant_20;
    Object Qwrite_frame_status_and_notes_from_slot, Qget_item_notes;
    Object Qinitial_item_notes, list_constant_6, list_constant_13;
    Object list_constant_4, list_constant_11, Qno_item;
    Object Qvirtual_attributes_local_to_class, Qinferior_frame_note_types;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_7;
    Object Qembedded_rule_in_user_menu_choice_qm;
    Object Qaction_for_user_menu_choice_qm, Qembedded_rule_qm;
    Object Qtranslation_and_text_of_embedded_rule, Qget_containing_module;
    Object Qinitial_containing_module, Qcontaining_module, Qget_item_active;
    Object Qinitial_item_active, Qitem_active, Qget_item_status;
    Object Qinitial_item_status, list_constant_5, Kwithin_putter;
    Object Kevent_updates, Qreclaim_frame_status_and_notes_value;
    Object string_constant_19, Qstack_change_cons_memory_usage;
    Object Qoutstanding_stack_change_conses, Qutilities1, list_constant_3;
    Object Qstack_change_cons_counter_vector, Qmake_thread_array, Kfuncall;
    Object list_constant_2, Qavailable_stack_change_conses_tail_vector;
    Object Qavailable_stack_change_conses_vector;
    Object Qreclaim_slot_value_tree_function, Qnamelike_slot_p;
    Object Qreclaim_frame_representations_value;

    x_note_fn_call(87,146);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qrepresentation = STATIC_SYMBOL("REPRESENTATION",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qreclaim_frame_representations_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-REPRESENTATIONS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_representations_value,
	    STATIC_FUNCTION(reclaim_frame_representations_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qframe_representations,
	    SYMBOL_FUNCTION(Qreclaim_frame_representations_value),
	    Qslot_value_reclaimer);
    Qnamelike_slot_p = STATIC_SYMBOL("NAMELIKE-SLOT-P",AB_package);
    Namelike_slot_p_prop = Qnamelike_slot_p;
    Qstack_of_slot_value_changes = 
	    STATIC_SYMBOL("STACK-OF-SLOT-VALUE-CHANGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_of_slot_value_changes,
	    Stack_of_slot_value_changes);
    Qframes5 = STATIC_SYMBOL("FRAMES5",AB_package);
    Qreclaim_slot_value_tree_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-TREE-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_slot_value_tree_function,
	    STATIC_FUNCTION(reclaim_slot_value_tree_function,NIL,FALSE,1,1));
    record_system_variable(Qstack_of_slot_value_changes,Qframes5,Nil,Qnil,
	    Qnil,Qreclaim_slot_value_tree_function,Qnil);
    Qjust_update_representations_of_slot_value = 
	    STATIC_SYMBOL("JUST-UPDATE-REPRESENTATIONS-OF-SLOT-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qjust_update_representations_of_slot_value,
	    Just_update_representations_of_slot_value);
    if (Just_update_representations_of_slot_value == UNBOUND)
	Just_update_representations_of_slot_value = 
		LIST_1(Qjust_update_representations_of_slot_value);
    if (Suppress_updating_of_slot_value_representations_qm == UNBOUND)
	Suppress_updating_of_slot_value_representations_qm = Nil;
    Qavailable_stack_change_conses = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CHANGE-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_change_conses,
	    Available_stack_change_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_stack_change_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_stack_change_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CHANGE-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_change_conses_tail,
	    Available_stack_change_conses_tail);
    record_system_variable(Qavailable_stack_change_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_stack_change_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CHANGE-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_change_conses_vector,
	    Available_stack_change_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    Qnil);
    record_system_variable(Qavailable_stack_change_conses_vector,
	    Qutilities1,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qavailable_stack_change_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-STACK-CHANGE-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_stack_change_conses_tail_vector,
	    Available_stack_change_conses_tail_vector);
    record_system_variable(Qavailable_stack_change_conses_tail_vector,
	    Qutilities1,list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qstack_change_cons_counter_vector = 
	    STATIC_SYMBOL("STACK-CHANGE-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_change_cons_counter_vector,
	    Stack_change_cons_counter_vector);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qstack_change_cons_counter_vector,Qutilities1,
	    list_constant_3,Qnil,Qt,Qnil,Qnil);
    Qstack_change_cons_counter = STATIC_SYMBOL("STACK-CHANGE-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_change_cons_counter,
	    Stack_change_cons_counter);
    record_system_variable(Qstack_change_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_stack_change_conses = 
	    STATIC_SYMBOL("OUTSTANDING-STACK-CHANGE-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_stack_change_conses,
	    STATIC_FUNCTION(outstanding_stack_change_conses,NIL,FALSE,0,0));
    Qstack_change_cons_memory_usage = 
	    STATIC_SYMBOL("STACK-CHANGE-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qstack_change_cons_memory_usage,
	    STATIC_FUNCTION(stack_change_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_19 = STATIC_STRING("1q83-qYy9k83-qXy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_stack_change_conses);
    push_optimized_constant(Qstack_change_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qreclaim_frame_status_and_notes_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-STATUS-AND-NOTES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_status_and_notes_value,
	    STATIC_FUNCTION(reclaim_frame_status_and_notes_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qframe_status_and_notes,
	    SYMBOL_FUNCTION(Qreclaim_frame_status_and_notes_value),
	    Qslot_value_reclaimer);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qitem_status = STATIC_SYMBOL("ITEM-STATUS",AB_package);
    temp = CONS(Qitem_status,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qitem_status,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_class,Qblock);
    list_constant_5 = STATIC_LIST((SI_Long)4L,Qmember,Qok,Qincomplete,Qbad);
    Kevent_updates = STATIC_SYMBOL("EVENT-UPDATES",Pkeyword);
    Kwithin_putter = STATIC_SYMBOL("WITHIN-PUTTER",Pkeyword);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kevent_updates,Kwithin_putter);
    Qinitial_item_status = STATIC_SYMBOL("INITIAL-ITEM-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_status,
	    STATIC_FUNCTION(initial_item_status,NIL,FALSE,1,1));
    Qget_item_status = STATIC_SYMBOL("GET-ITEM-STATUS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_status,STATIC_FUNCTION(get_item_status,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qitem_status,list_constant_4,list_constant_5,
	    list_constant_6,SYMBOL_FUNCTION(Qinitial_item_status),
	    SYMBOL_FUNCTION(Qget_item_status),Nil);
    Qitem_active = STATIC_SYMBOL("ITEM-ACTIVE",AB_package);
    temp = CONS(Qitem_active,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qitem_active,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qinitial_item_active = STATIC_SYMBOL("INITIAL-ITEM-ACTIVE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_active,
	    STATIC_FUNCTION(initial_item_active,NIL,FALSE,1,1));
    Qget_item_active = STATIC_SYMBOL("GET-ITEM-ACTIVE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_active,STATIC_FUNCTION(get_item_active,
	    NIL,FALSE,1,1));
    add_virtual_attribute(Qitem_active,list_constant_4,Qtruth_value,
	    list_constant_6,SYMBOL_FUNCTION(Qinitial_item_active),
	    SYMBOL_FUNCTION(Qget_item_active),Nil);
    Qcontaining_module = STATIC_SYMBOL("CONTAINING-MODULE",AB_package);
    temp = CONS(Qcontaining_module,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qcontaining_module,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_containing_module = STATIC_SYMBOL("INITIAL-CONTAINING-MODULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_containing_module,
	    STATIC_FUNCTION(initial_containing_module,NIL,FALSE,1,1));
    Qget_containing_module = STATIC_SYMBOL("GET-CONTAINING-MODULE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_containing_module,
	    STATIC_FUNCTION(get_containing_module,NIL,FALSE,1,1));
    add_virtual_attribute(Qcontaining_module,list_constant_4,Qsymbol,Qnil,
	    SYMBOL_FUNCTION(Qinitial_containing_module),
	    SYMBOL_FUNCTION(Qget_containing_module),Nil);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qitem_notes = STATIC_SYMBOL("ITEM-NOTES",AB_package);
    Qframe_notes_for_component_particulars = 
	    STATIC_SYMBOL("FRAME-NOTES-FOR-COMPONENT-PARTICULARS",AB_package);
    Qtranslation_and_text_of_embedded_rule = 
	    STATIC_SYMBOL("TRANSLATION-AND-TEXT-OF-EMBEDDED-RULE",AB_package);
    Qembedded_rule_qm = STATIC_SYMBOL("EMBEDDED-RULE\?",AB_package);
    list_constant_7 = STATIC_CONS(Qnil,Qnil);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)4L,
	    Qtranslation_and_text_of_embedded_rule,Qnil,Qembedded_rule_qm,
	    list_constant_7);
    Qaction_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("ACTION-FOR-USER-MENU-CHOICE\?",AB_package);
    Qembedded_rule_in_user_menu_choice_qm = 
	    STATIC_SYMBOL("EMBEDDED-RULE-IN-USER-MENU-CHOICE\?",AB_package);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)4L,
	    Qaction_for_user_menu_choice_qm,Qnil,
	    Qembedded_rule_in_user_menu_choice_qm,list_constant_7);
    list_constant_10 = STATIC_LIST((SI_Long)2L,list_constant_8,
	    list_constant_9);
    List_of_embedding_slots = list_constant_10;
    Qembedded_rule_has_frame_notes = 
	    STATIC_SYMBOL("EMBEDDED-RULE-HAS-FRAME-NOTES",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_computation_frame,
	    Current_computation_frame);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    Frame_note_writer_1_prop = Qframe_note_writer_1;
    Qsuperior_frame_note_type = STATIC_SYMBOL("SUPERIOR-FRAME-NOTE-TYPE",
	    AB_package);
    Superior_frame_note_type_prop = Qsuperior_frame_note_type;
    Qinferior_frame_note_types = STATIC_SYMBOL("INFERIOR-FRAME-NOTE-TYPES",
	    AB_package);
    Inferior_frame_note_types_prop = Qinferior_frame_note_types;
    write_embedded_rule_has_frame_notes_note_1 = 
	    STATIC_FUNCTION(write_embedded_rule_has_frame_notes_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qembedded_rule_has_frame_notes,
	    write_embedded_rule_has_frame_notes_note_1,Qframe_note_writer_1);
    temp = CONS(Qitem_notes,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qitem_notes,temp_1);
    set_property_value_function(get_symbol_properties_function(Qblock),
	    Qvirtual_attributes_local_to_class,temp);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = 
	    STATIC_STRING("~S [frame note writer missing for type of note ~A]");
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qsequence,Qtext);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_12 = STATIC_CONS(Qno_item,Qnil);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_11,
	    list_constant_12);
    Qinitial_item_notes = STATIC_SYMBOL("INITIAL-ITEM-NOTES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_item_notes,
	    STATIC_FUNCTION(initial_item_notes,NIL,FALSE,1,1));
    Qget_item_notes = STATIC_SYMBOL("GET-ITEM-NOTES",AB_package);
    SET_SYMBOL_FUNCTION(Qget_item_notes,STATIC_FUNCTION(get_item_notes,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qitem_notes,list_constant_4,list_constant_13,
	    list_constant_6,SYMBOL_FUNCTION(Qinitial_item_notes),
	    SYMBOL_FUNCTION(Qget_item_notes),Nil);
    Qname_for_debugging = STATIC_SYMBOL("NAME-FOR-DEBUGGING",AB_package);
    string_constant_1 = STATIC_STRING("~A: ");
    string_constant_2 = STATIC_STRING("and");
    string_constant_3 = STATIC_STRING("but");
    string_constant_4 = 
	    STATIC_STRING("DISABLED, and some superior item is either DISABLED or not OK");
    string_constant_5 = STATIC_STRING("DISABLED");
    string_constant_6 = 
	    STATIC_STRING("some superior item is either DISABLED or not OK");
    string_constant_7 = 
	    STATIC_STRING("this INITIALLY rule is no longer active, having completed or timed out");
    string_constant_8 = STATIC_STRING("not active");
    string_constant_9 = STATIC_STRING(", ~a ~a~a");
    string_constant_10 = STATIC_STRING("");
    string_constant_11 = STATIC_STRING(".");
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qwrite_frame_status_and_notes_from_slot = 
	    STATIC_SYMBOL("WRITE-FRAME-STATUS-AND-NOTES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_frame_status_and_notes_from_slot,
	    STATIC_FUNCTION(write_frame_status_and_notes_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qframe_status_and_notes,
	    SYMBOL_FUNCTION(Qwrite_frame_status_and_notes_from_slot),
	    Qslot_value_writer);
    if (Abbreviate_frame_notes_p == UNBOUND)
	Abbreviate_frame_notes_p = Nil;
    string_constant_12 = STATIC_STRING("~%(~D) ");
    array_constant_1 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_13 = STATIC_STRING("(~d) ");
    string_constant_14 = STATIC_STRING("~%for ");
    array_constant_2 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    write_frame_notes_for_component_particulars_note_1 = 
	    STATIC_FUNCTION(write_frame_notes_for_component_particulars_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qframe_notes_for_component_particulars,
	    write_frame_notes_for_component_particulars_note_1,
	    Qframe_note_writer_1);
    string_constant_20 = STATIC_STRING("nil");
    if (Directory_nil == UNBOUND)
	Directory_nil = make_symbol(string_constant_20);
    Qreclaim_grammar_tree_function = 
	    STATIC_SYMBOL("RECLAIM-GRAMMAR-TREE-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_grammar_tree_function,
	    STATIC_FUNCTION(reclaim_grammar_tree_function,NIL,FALSE,1,1));
    if (Flattened_menu_reverse == UNBOUND)
	Flattened_menu_reverse = Nil;
    if (Flattened_menu_maximum_remaining_elements == UNBOUND)
	Flattened_menu_maximum_remaining_elements = FIX((SI_Long)0L);
    Qframe_or_frames_with_this_name = 
	    STATIC_SYMBOL("FRAME-OR-FRAMES-WITH-THIS-NAME",AB_package);
    Kb_specific_property_names = CONS(Qframe_or_frames_with_this_name,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qframe_or_frames_with_this_name,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_gensym_list_if_list = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-LIST-IF-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gensym_list_if_list,
	    STATIC_FUNCTION(reclaim_gensym_list_if_list,NIL,FALSE,1,1));
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qframe_or_frames_with_this_name,
	    Qreclaim_gensym_list_if_list,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Frame_or_frames_with_this_name_kbprop = Qframe_or_frames_with_this_name;
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qreclaim_slot_value_cons_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-CONS-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_slot_value_cons_function,
	    STATIC_FUNCTION(reclaim_slot_value_cons_function,NIL,FALSE,1,1));
    Qput_name_or_names_for_frame = 
	    STATIC_SYMBOL("PUT-NAME-OR-NAMES-FOR-FRAME",AB_package);
    SET_SYMBOL_FUNCTION(Qput_name_or_names_for_frame,
	    STATIC_FUNCTION(put_name_or_names_for_frame,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qname_or_names_for_frame,
	    SYMBOL_FUNCTION(Qput_name_or_names_for_frame),Qslot_putter);
    Qnote_name_change = STATIC_SYMBOL("NOTE-NAME-CHANGE",AB_package);
    Qold_names = STATIC_SYMBOL("OLD-NAMES",AB_package);
    Qinitializing_p = STATIC_SYMBOL("INITIALIZING-P",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qblock,Qold_names,
	    Qinitializing_p);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qnote_name_change,list_constant_15,
	    Qgeneric_method_lambda_list);
    Qnote_name_change_for_block = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_block,
	    STATIC_FUNCTION(note_name_change_for_block,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qnote_name_change_for_block);
    set_get(Qblock,Qnote_name_change,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qnote_name_change,temp,Qclasses_which_define);
    string_constant_15 = STATIC_STRING("~A~A~A");
    string_constant_16 = STATIC_STRING("~A~A~A-~D");
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    Qnon_unique_names = STATIC_SYMBOL("NON-UNIQUE-NAMES",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    Qlocal_name_or_names = STATIC_SYMBOL("LOCAL-NAME-OR-NAMES",AB_package);
    Qreclaim_name_or_names_for_frame_value = 
	    STATIC_SYMBOL("RECLAIM-NAME-OR-NAMES-FOR-FRAME-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_name_or_names_for_frame_value,
	    STATIC_FUNCTION(reclaim_name_or_names_for_frame_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qname_or_names_for_frame,
	    SYMBOL_FUNCTION(Qreclaim_name_or_names_for_frame_value),
	    Qslot_value_reclaimer);
    array_constant_3 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    write_non_unique_names_note_1 = 
	    STATIC_FUNCTION(write_non_unique_names_note,NIL,FALSE,2,2);
    mutate_global_property(Qnon_unique_names,write_non_unique_names_note_1,
	    Qframe_note_writer_1);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Qput_attribute_value = STATIC_SYMBOL("PUT-ATTRIBUTE-VALUE",AB_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qitems_deleted_since_load_or_save = 
	    STATIC_SYMBOL("ITEMS-DELETED-SINCE-LOAD-OR-SAVE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitems_deleted_since_load_or_save,
	    Items_deleted_since_load_or_save);
    record_system_variable(Qitems_deleted_since_load_or_save,Qframes5,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qitems_deleted_since_load_or_save_tail = 
	    STATIC_SYMBOL("ITEMS-DELETED-SINCE-LOAD-OR-SAVE-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qitems_deleted_since_load_or_save_tail,
	    Items_deleted_since_load_or_save_tail);
    record_system_variable(Qitems_deleted_since_load_or_save_tail,Qframes5,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qitem,Qworkspace);
    check_if_superior_classes_are_defined(Qkb_workspace,list_constant_16);
    string_constant_21 = STATIC_STRING("1m1m8v83=uy1l8t");
    string_constant_22 = 
	    STATIC_STRING("1x4z8r83K1y83K1y83=uy83=uy00001o1l8o1l8l1l83Cy1m83Dy53hyBogus name. Part of tamper mechanism. Internal.000004z8r83SCy83SCy83=uy8");
    string_constant_23 = 
	    STATIC_STRING("3=uy00001m1l8o1l8l000004z8r83Dxy83Dxy83=uy83=uy00001p1l83Ey1l8l1l8z1m8p8313y1m83Dy53-1yCurrently aliased to module-assignment. C");
    string_constant_24 = 
	    STATIC_STRING("hange alias to just module \?000004z8r83DMy83DMy83=uy83=uy036uy001r1l83Ey1l8l1l83Cy1m8p83-ey1l8z1l83Ny1m83Dy53-8yexport as initia");
    string_constant_25 = 
	    STATIC_STRING("l-workspace-width, (type positive-integer), writable = false000004z8r83DLy83DLy83=uy83=uy033my001r1l83Ey1l8l1l83Cy1l8z1m8p83-ey1");
    string_constant_26 = 
	    STATIC_STRING("l83Ny1m83Dy53-9yexport as initial-workspace-height, (type positive-integer), writable = false000004z8r834sy834sy83=uy83=uy083*2y");
    string_constant_27 = 
	    STATIC_STRING("001q1l8l1l8o1l8z1l83Cy1m8p832Yy1m83Dy53uyExport as background-color, with type (or none color-symbol)000004z8r834ty834ty83=uy83=");
    string_constant_28 = 
	    STATIC_STRING("uy083fy001q1l8l1l8z1l8o1l83Cy1m8p832Yy1m83Dy53uyExport as foreground-color, with type (or none color-symbol)000004z8r83*Ly83*Ly8");
    string_constant_29 = 
	    STATIC_STRING("3=uy83=uy03Qy001p1l8l1l8o1l8z1m8p83*7y1m83Dy5wExport as is000004z8r833gy833gy83=uy83=uy00001n1l8l1m8p833gy1m83Dy73-Dy3-Gy3-ry3-i");
    string_constant_30 = 
	    STATIC_STRING("y3-Xy3Sy3-Uy3-Xy3-Vy3-hy3-fy3-Xy3-ly3Sy3ay3Sy3-by3-fy3-Ty3-Zy3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-my3-by3-hy3-gy3Sy3cy3by3Sy3uy3vy3v");
    string_constant_31 = 
	    STATIC_STRING("y3wy3Sy3-wyutttt3ay3-hy3-ky3Sy3ay3-ly3-Xy3-jy3Sy3ay3-by3-fy3-Ty3-Zy3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-my3-by3-hy3-gy3by3by3Sy3-gy3");
    string_constant_32 = 
	    STATIC_STRING("-hy3-gy3-Xy3by3gy000004z8r8340y8340y83=uy83=uy00001o1l8l1l8z1m8p8337y1m83Dy73-wy3-1y3-qy3-iy3-hy3-ky3-my3sy3Sy3-Fy3-ay3-hy3-ny3-");
    string_constant_33 = 
	    STATIC_STRING("ey3-Wy3Sy3-my3-ry3-iy3-Xy3Sy3-Uy3-Xy3-Vy3-hy3-fy3-Xy3Sy3-Yy3-ky3-Ty3-fy3-Xy3fy3-ly3-my3-ry3-ey3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-m");
    string_constant_34 = 
	    STATIC_STRING("y3-by3-hy3-gy3Sy3ay3-Ty3-gy3Sy3-Xy3-fy3-Uy3-Xy3-Wy3-Wy3-Xy3-Wy3Sy3-ly3-my3-ky3-ny3-Vy3-my3by3ey3Sy3-hy3-ky3Sy3-wyu3Syt3-Ty3Sy3-l");
    string_constant_35 = 
	    STATIC_STRING("y3-ry3-fy3-Uy3-hy3-ey3Sy3-Ty3-ly3Sy3-by3-my3Sy3-Vy3-ny3-ky3-ky3-Xy3-gy3-my3-ey3-ry3Sy3-by3-ly3Sy3ay3-Yy3-ky3-Ty3-fy3-Xy3fy3-ly3-");
    string_constant_36 = 
	    STATIC_STRING("my3-ry3-ey3-Xy3fy3-gy3-Ty3-fy3-Xy3by3xy000004z8r834ky834ky83=uy83=uy00001n1l8l1l8z1m8p833cy000004z8r83K0y83K0y83=uy83=uy00001o1l");
    string_constant_37 = 
	    STATIC_STRING("8o1l8l1l83Cy1m83Dy53hyBogus name. Part of tamper mechanism. Internal.000004z8r83Tly83Tly83=uy83=uy00001m1l83Ey1l8l00000");
    string_constant_38 = 
	    STATIC_STRING("1z8q1o83=uy1m83Ry83*qy1m8v83=uy8t1q83K1y08o8l83Cy1m83Dy53hyBogus name. Part of tamper mechanism. Internal.1o83SCy08o8l1r83Dxy083");
    string_constant_39 = 
	    STATIC_STRING("Ey8l8z1m8p8313y1m83Dy53-1yCurrently aliased to module-assignment. Change alias to just module \?1t83DMy36uy83Ey8l83Cy1m8p83-ey8z8");
    string_constant_40 = 
	    STATIC_STRING("3Ny1m83Dy53-8yexport as initial-workspace-width, (type positive-integer), writable = false1t83DLy33my83Ey8l83Cy8z1m8p83-ey83Ny1m");
    string_constant_41 = 
	    STATIC_STRING("83Dy53-9yexport as initial-workspace-height, (type positive-integer), writable = false1s834sy83*2y8l8o8z83Cy1m8p832Yy1m83Dy53uyE");
    string_constant_42 = 
	    STATIC_STRING("xport as background-color, with type (or none color-symbol)1s834ty83fy8l8z8o83Cy1m8p832Yy1m83Dy53uyExport as foreground-color, w");
    string_constant_43 = 
	    STATIC_STRING("ith type (or none color-symbol)1r83*Ly3Qy8l8o8z1m8p83*7y1m83Dy5wExport as is1o833gy01m8p833gy1m83Dy73-Dy3-Gy3-ry3-iy3-Xy3Sy3-Uy3");
    string_constant_44 = 
	    STATIC_STRING("-Xy3-Vy3-hy3-fy3-Xy3-ly3Sy3ay3Sy3-by3-fy3-Ty3-Zy3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-my3-by3-hy3-gy3Sy3cy3by3Sy3uy3vy3vy3wy3Sy3-wyut");
    string_constant_45 = 
	    STATIC_STRING("ttt3ay3-hy3-ky3Sy3ay3-ly3-Xy3-jy3Sy3ay3-by3-fy3-Ty3-Zy3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-my3-by3-hy3-gy3by3by3Sy3-gy3-hy3-gy3-Xy3b");
    string_constant_46 = 
	    STATIC_STRING("y3gy1p8340y08z1m8p8337y1m83Dy73-wy3-1y3-qy3-iy3-hy3-ky3-my3sy3Sy3-Fy3-ay3-hy3-ny3-ey3-Wy3Sy3-my3-ry3-iy3-Xy3Sy3-Uy3-Xy3-Vy3-hy3-");
    string_constant_47 = 
	    STATIC_STRING("fy3-Xy3Sy3-Yy3-ky3-Ty3-fy3-Xy3fy3-ly3-my3-ry3-ey3-Xy3fy3-Wy3-Xy3-Yy3-by3-gy3-by3-my3-by3-hy3-gy3Sy3ay3-Ty3-gy3Sy3-Xy3-fy3-Uy3-Xy");
    string_constant_48 = 
	    STATIC_STRING("3-Wy3-Wy3-Xy3-Wy3Sy3-ly3-my3-ky3-ny3-Vy3-my3by3ey3Sy3-hy3-ky3Sy3-wyu3Syt3-Ty3Sy3-ly3-ry3-fy3-Uy3-hy3-ey3Sy3-Ty3-ly3Sy3-by3-my3Sy");
    string_constant_49 = 
	    STATIC_STRING("3-Vy3-ny3-ky3-ky3-Xy3-gy3-my3-ey3-ry3Sy3-by3-ly3Sy3ay3-Yy3-ky3-Ty3-fy3-Xy3fy3-ly3-my3-ry3-ey3-Xy3fy3-gy3-Ty3-fy3-Xy3by3xy1p834ky");
    string_constant_50 = 
	    STATIC_STRING("08l8z1m8p833cy1q83K0y08o8l83Cy1m83Dy53hyBogus name. Part of tamper mechanism. Internal.1o83Tly083Ey8l");
    temp_1 = regenerate_optimized_constant(string_constant_21);
    temp_2 = regenerate_optimized_constant(list(16,string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37));
    add_class_to_environment(9,Qkb_workspace,list_constant_16,Nil,temp_1,
	    Nil,temp_2,list_constant_16,
	    regenerate_optimized_constant(list(13,string_constant_38,
	    string_constant_39,string_constant_40,string_constant_41,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47,
	    string_constant_48,string_constant_49,string_constant_50)),Nil);
    Kb_workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qkb_workspace,
	    Class_description_gkbprop);
    Qkb_workspace_initial_height = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT",AB_package);
    Qinitial_height = STATIC_SYMBOL("INITIAL-HEIGHT",AB_package);
    alias_slot_name(3,Qkb_workspace_initial_height,Qinitial_height,
	    Qkb_workspace);
    Qkb_workspace_initial_width = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH",AB_package);
    Qinitial_width = STATIC_SYMBOL("INITIAL-WIDTH",AB_package);
    alias_slot_name(3,Qkb_workspace_initial_width,Qinitial_width,
	    Qkb_workspace);
    string_constant_51 = 
	    STATIC_STRING("1n1m83Duy83-6y1m8313y83Duy1m8313y1m9k83dVy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_51));
    Qunspecified = STATIC_SYMBOL("UNSPECIFIED",AB_package);
    list_constant_17 = STATIC_CONS(Qunspecified,Qnil);
    reserve_words(list_constant_17);
    Qworkspace_foreground_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR\?",AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    alias_slot_name(3,Qworkspace_foreground_color_qm,Qforeground_color,
	    Qkb_workspace);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    alias_slot_name(3,Qworkspace_background_color_qm,Qbackground_color,
	    Qkb_workspace);
    Qmodule_name_qm = STATIC_SYMBOL("MODULE-NAME\?",AB_package);
    Qcompile_module_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-MODULE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_module_name_qm_for_slot,
	    STATIC_FUNCTION(compile_module_name_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qmodule_name_qm,
	    SYMBOL_FUNCTION(Qcompile_module_name_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qmodule_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Qmodule_name_qm),
	    Qtype_specification_simple_expansion,list_constant_1);
    define_type_specification_explicit_complex_type(Qmodule_name_qm,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qmodule_name_qm);
    module_name_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(module_name_qm_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qmodule_name_qm,
	    module_name_qm_evaluation_setter_1);
    module_name_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(module_name_qm_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qmodule_name_qm,
	    module_name_qm_evaluation_getter_1);
    array_constant_7 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_module_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-MODULE-NAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_module_name_qm_from_slot,
	    STATIC_FUNCTION(write_module_name_qm_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmodule_name_qm,
	    SYMBOL_FUNCTION(Qwrite_module_name_qm_from_slot),
	    Qslot_value_writer);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qput_module_this_is_part_of_qm = 
	    STATIC_SYMBOL("PUT-MODULE-THIS-IS-PART-OF\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_module_this_is_part_of_qm,
	    STATIC_FUNCTION(put_module_this_is_part_of_qm,NIL,FALSE,3,3));
    mutate_global_property(Qmodule_this_is_part_of_qm,
	    SYMBOL_FUNCTION(Qput_module_this_is_part_of_qm),Qslot_putter);
    Qinitialize_for_kb_workspace = 
	    STATIC_SYMBOL("INITIALIZE-FOR-KB-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_kb_workspace,
	    STATIC_FUNCTION(initialize_for_kb_workspace,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_for_kb_workspace);
    set_get(Qkb_workspace,Qinitialize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qinitialize,temp,Qclasses_which_define);
    Qmodule_assignment = STATIC_SYMBOL("MODULE-ASSIGNMENT",AB_package);
    alias_slot_name(3,Qmodule_this_is_part_of_qm,Qmodule_assignment,Qnil);
    Qdynamic_menus_modification_tick = 
	    STATIC_SYMBOL("DYNAMIC-MENUS-MODIFICATION-TICK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_menus_modification_tick,
	    Dynamic_menus_modification_tick);
    record_system_variable(Qdynamic_menus_modification_tick,Qframes5,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qt);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    Qnamed_workspaces = STATIC_SYMBOL("NAMED-WORKSPACES",AB_package);
    Qnote_name_change_for_kb_workspace = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-KB-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_kb_workspace,
	    STATIC_FUNCTION(note_name_change_for_kb_workspace,NIL,FALSE,3,3));
    temp = SYMBOL_FUNCTION(Qnote_name_change_for_kb_workspace);
    set_get(Qkb_workspace,Qnote_name_change,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp = CONS(Qkb_workspace,temp_1);
    mutate_global_property(Qnote_name_change,temp,Qclasses_which_define);
    Qkb_name = STATIC_SYMBOL("KB-NAME",AB_package);
    Qput_kb_name_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-NAME-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_name_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_name_where_slot_is_absent,NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qkb_name,
	    SYMBOL_FUNCTION(Qput_kb_name_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qkb_name_for_workspace = STATIC_SYMBOL("KB-NAME-FOR-WORKSPACE",AB_package);
    Qput_kb_name_for_workspace_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-NAME-FOR-WORKSPACE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_name_for_workspace_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_name_for_workspace_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qkb_name_for_workspace,
	    SYMBOL_FUNCTION(Qput_kb_name_for_workspace_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qconcurrent_block = STATIC_SYMBOL("CONCURRENT-BLOCK",AB_package);
    temp_1 = FIX((SI_Long)199L);
    mutate_global_property(Qconcurrent_block,CONS(Qkb_workspace,temp_1),
	    Qsubstitute_class_and_kb_flags);
    Qinitialization_interval = STATIC_SYMBOL("INITIALIZATION-INTERVAL",
	    AB_package);
    Qput_initialization_interval_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-INITIALIZATION-INTERVAL-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_initialization_interval_where_slot_is_absent,
	    STATIC_FUNCTION(put_initialization_interval_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinitialization_interval,
	    SYMBOL_FUNCTION(Qput_initialization_interval_where_slot_is_absent),
	    Qabsent_slot_putter);
    array_constant_8 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qcompile_uuid_for_slot = STATIC_SYMBOL("COMPILE-UUID-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_uuid_for_slot,
	    STATIC_FUNCTION(compile_uuid_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Quuid,SYMBOL_FUNCTION(Qcompile_uuid_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Quuid,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_uuid_from_slot = STATIC_SYMBOL("WRITE-UUID-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_uuid_from_slot,
	    STATIC_FUNCTION(write_uuid_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Quuid,SYMBOL_FUNCTION(Qwrite_uuid_from_slot),
	    Qslot_value_writer);
    Qreclaim_uuid_value = STATIC_SYMBOL("RECLAIM-UUID-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_uuid_value,
	    STATIC_FUNCTION(reclaim_uuid_value,NIL,FALSE,2,2));
    mutate_global_property(Quuid,SYMBOL_FUNCTION(Qreclaim_uuid_value),
	    Qslot_value_reclaimer);
    Qput_uuid = STATIC_SYMBOL("PUT-UUID",AB_package);
    SET_SYMBOL_FUNCTION(Qput_uuid,STATIC_FUNCTION(put_uuid,NIL,FALSE,3,3));
    mutate_global_property(Quuid,SYMBOL_FUNCTION(Qput_uuid),Qslot_putter);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_type_description_g2_struct = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qcategory_committer_function = 
	    STATIC_SYMBOL("CATEGORY-COMMITTER-FUNCTION",AB_package);
    Qdefault_category_slot_access_committer = 
	    STATIC_SYMBOL("DEFAULT-CATEGORY-SLOT-ACCESS-COMMITTER",AB_package);
    Qcategory_extracter_function = 
	    STATIC_SYMBOL("CATEGORY-EXTRACTER-FUNCTION",AB_package);
    Qdefault_category_slot_access_extracter = 
	    STATIC_SYMBOL("DEFAULT-CATEGORY-SLOT-ACCESS-EXTRACTER",AB_package);
    Qg2_defstruct_structure_name_slot_description_g2_struct = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qdefault_category_slot_access_committer,
	    STATIC_FUNCTION(default_category_slot_access_committer,NIL,
	    FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qdefault_category_slot_access_extracter,
	    STATIC_FUNCTION(default_category_slot_access_extracter,NIL,
	    FALSE,2,2));
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    string_constant_17 = 
	    STATIC_STRING("Fixed corrupted attribute name ~A with ~S, ~\n                                 please save your KB and notify Gensym Customer Support.");
    string_constant_18 = 
	    STATIC_STRING("Fixed corrupted class name ~A with ~S, ~\n                               please save your KB and notify Gensym Customer Support.");
}
