/* cnct3.c
 * Input file:  connect3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct3.h"


static Object array_constant;      /* # */

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

/* CHANGE-CONNECTION-DELTAS-FOR-INPUT-END-OBJECT-BEING-DRAGGED */
Object change_connection_deltas_for_input_end_object_being_dragged(connection,
	    block,delta_x_in_workspace,delta_y_in_workspace)
    Object connection, block, delta_x_in_workspace, delta_y_in_workspace;
{
    Object input_end_position, input_end_side;
    Object initial_orientation_horizontal_p, delta_or_deltas, link_1_delta;
    Object link_2_delta, temp_1, sub_class_bit_vector, temp_2;
    SI_Long gensymed_symbol, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp;
    Object result;

    x_note_fn_call(99,0);
    input_end_position = ISVREF(connection,(SI_Long)5L);
    input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	    (SI_Long)3L);
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    link_1_delta = Nil;
    link_2_delta = Nil;
    if ( !TRUEP(delta_or_deltas)) {
	result = compute_stretched_links_of_connection_being_dragged(connection,
		block);
	MVS_2(result,link_1_delta,link_2_delta);
	link_2_delta = FIXNUM_NEGATE(link_2_delta);
    }
    else if (ATOM(delta_or_deltas)) {
	link_2_delta = initial_orientation_horizontal_p ? 
		FIXNUM_MINUS(delta_or_deltas,delta_x_in_workspace) : 
		FIXNUM_MINUS(delta_or_deltas,delta_y_in_workspace);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = link_2_delta;
    }
    else {
	link_1_delta = initial_orientation_horizontal_p ? 
		FIXNUM_MINUS(CADR(delta_or_deltas),delta_y_in_workspace) : 
		FIXNUM_MINUS(CADR(delta_or_deltas),delta_x_in_workspace);
	link_2_delta = initial_orientation_horizontal_p ? 
		FIXNUM_MINUS(CAR(delta_or_deltas),delta_x_in_workspace) : 
		FIXNUM_MINUS(CAR(delta_or_deltas),delta_y_in_workspace);
	temp_1 = ISVREF(connection,(SI_Long)6L);
	M_CAR(temp_1) = link_2_delta;
	temp_1 = ISVREF(connection,(SI_Long)6L);
	M_CADR(temp_1) = link_1_delta;
    }
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	temp_2 = initial_orientation_horizontal_p ? ((SI_Long)0L > 
		IFIX(link_2_delta) ? Qleft : Qright) : (SI_Long)0L > 
		IFIX(link_2_delta) ? Qtop : Qbottom;
	if (EQ(temp_2,Qtop))
	    gensymed_symbol = (SI_Long)0L;
	else if (EQ(temp_2,Qleft))
	    gensymed_symbol = (SI_Long)1L;
	else if (EQ(temp_2,Qbottom))
	    gensymed_symbol = (SI_Long)2L;
	else
	    gensymed_symbol = (SI_Long)3L;
	gensymed_symbol_1 = (SI_Long)0L;
	svref_new_value = gensymed_symbol + gensymed_symbol_1;
	return VALUES_1(ISVREF(connection,(SI_Long)5L) = FIX(svref_new_value));
    }
    else
	return VALUES_1(Nil);
}

/* CHANGE-CONNECTION-DELTAS-FOR-OBJECT-BEING-DRAGGED */
Object change_connection_deltas_for_object_being_dragged(connection,block,
	    delta_x_in_workspace,delta_y_in_workspace)
    Object connection, block, delta_x_in_workspace, delta_y_in_workspace;
{
    x_note_fn_call(99,1);
    if (EQ(ISVREF(connection,(SI_Long)3L),block))
	return change_connection_deltas_for_input_end_object_being_dragged(connection,
		block,delta_x_in_workspace,delta_y_in_workspace);
    else if (EQ(ISVREF(connection,(SI_Long)2L),block))
	return VALUES_1(delta_y_in_workspace);
    else
	return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* SIDE-ORIENTATIONS-SAME-P */
Object side_orientations_same_p(side1,side2)
    Object side1, side2;
{
    Object temp;

    x_note_fn_call(99,2);
    temp = memq_function(side1,list_constant) ? memq_function(side2,
	    list_constant) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (memq_function(side1,list_constant_1))
	return memq_function(side2,list_constant_1);
    else
	return VALUES_1(Nil);
}

/* CONNECTION-IS-STRAIGHT? */
Object connection_is_straight_qm(connection)
    Object connection;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, output_end_object;
    Object output_end_position, output_end_side;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position;

    x_note_fn_call(99,3);
    gensymed_symbol = connection;
    input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
    input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
    input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	    (SI_Long)3L);
    input_end_position_on_side = IFIX(input_end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qright)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qbottom)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
    output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
    output_end_side = ISVREF(array_constant,IFIX(output_end_position) & 
	    (SI_Long)3L);
    output_end_position_on_side = IFIX(output_end_position) >>  -  - 
	    (SI_Long)2L;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qright)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    if ( !TRUEP(ISVREF(connection,(SI_Long)6L)) && 
	    side_orientations_same_p(input_end_side,output_end_side)) {
	if (input_end_x_position == output_end_x_position)
	    return VALUES_1(FIX(output_end_y_position - input_end_y_position));
	else if (input_end_y_position == output_end_y_position)
	    return VALUES_1(FIX(output_end_x_position - input_end_x_position));
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qconnection_style;   /* connection-style */

static Object Qdiagonal;           /* diagonal */

static Object Qloose_end;          /* loose-end */

/* PUT-KINK-INTO-CONNECTION-IF-STRAIGHT */
Object put_kink_into_connection_if_straight(connection,blocks)
    Object connection, blocks;
{
    Object plist, delta_qm, frame, symbol, gensymed_symbol;
    Object sub_class_bit_vector, workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(99,4);
    plist = ISVREF(connection,(SI_Long)9L);
    if ( !(plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal))) {
	delta_qm = connection_is_straight_qm(connection);
	if (delta_qm) {
	    frame = CAR(blocks);
	    symbol = Qloose_end;
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(connection,
		    (SI_Long)2L),(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    workspace_qm = gensymed_symbol;
	    update_connection_images(T,workspace_qm,connection);
	    put_kink_into_connection_if_straight_1(connection,delta_qm);
	    return update_connection_images(Nil,workspace_qm,connection);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qstub_length;        /* stub-length */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qconnection;         /* connection */

/* PUT-KINK-INTO-CONNECTION-IF-STRAIGHT-1 */
Object put_kink_into_connection_if_straight_1(connection,delta)
    Object connection, delta;
{
    Object connection_frame_or_class, x2, stub_length, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long gensymed_symbol_3, svref_new_value_1;
    char temp;
    Object result;

    x_note_fn_call(99,5);
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	stub_length = get_lookup_slot_value(connection_frame_or_class,
		Qstub_length);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		Class_description_gkbprop)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = connection_frame_or_class;
	    key_hash_value = SXHASH_SYMBOL_1(connection_frame_or_class) & 
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		    get_slot_description_of_class_description_function(Qstub_length,
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
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qstub_length,
		    gensymed_symbol,Nil);
	}
	stub_length = ISVREF(temp_2,(SI_Long)6L);
    }
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    if (IFIX(delta) > (SI_Long)0L)
	svref_new_value_1 = IFIX(FIXNUM_MIN(stub_length,delta));
    else {
	temp_2 = FIXNUM_NEGATE(delta);
	svref_new_value_1 = IFIX(FIXNUM_NEGATE(FIXNUM_MIN(stub_length,
		temp_2)));
    }
    return VALUES_1(ISVREF(connection,(SI_Long)6L) = FIX(svref_new_value_1));
}

static Object list_constant_2;     /* # */

/* COMPUTE-STRETCHED-LINKS-OF-CONNECTION-BEING-DRAGGED */
Object compute_stretched_links_of_connection_being_dragged(connection,block)
    Object connection, block;
{
    Object link_1_delta, link_2_delta, end_object, end_position;
    Object block_at_other_end, other_end_position, other_end_side;
    Object other_end_initial_orientation_horizontal_p, end_side;
    Object gensymed_symbol, initial_orientation_horizontal_p;
    Object connection_anchor_point_x, connection_anchor_point_y;
    SI_Long end_position_on_side, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, end_x_position, end_y_position;
    Object result;

    x_note_fn_call(99,6);
    link_1_delta = Nil;
    link_2_delta = Nil;
    end_object = Nil;
    end_position = Nil;
    if (EQ(ISVREF(connection,(SI_Long)2L),block)) {
	end_object = ISVREF(connection,(SI_Long)2L);
	end_position = ISVREF(connection,(SI_Long)4L);
    }
    else {
	end_object = ISVREF(connection,(SI_Long)3L);
	end_position = ISVREF(connection,(SI_Long)5L);
    }
    block_at_other_end = get_block_at_other_end_of_connection(connection,
	    block);
    other_end_position = get_position_at_this_end_of_connection(connection,
	    block_at_other_end);
    other_end_side = ISVREF(array_constant,IFIX(other_end_position) & 
	    (SI_Long)3L);
    other_end_initial_orientation_horizontal_p = 
	    memq_function(other_end_side,list_constant_2);
    end_side = ISVREF(array_constant,IFIX(end_position) & (SI_Long)3L);
    end_position_on_side = IFIX(end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(end_side,Qleft))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(end_side,Qright)) {
	gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = end_position_on_side;
    end_x_position = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    if (EQ(end_side,Qtop))
	gensymed_symbol_2 = (SI_Long)0L;
    else if (EQ(end_side,Qbottom)) {
	gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    }
    else
	gensymed_symbol_2 = end_position_on_side;
    end_y_position = gensymed_symbol_1 + gensymed_symbol_2;
    initial_orientation_horizontal_p = EQ(end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(end_side,Qright) ? T : Nil;
    result = compute_dragged_connection_anchor_point(connection,block);
    MVS_2(result,connection_anchor_point_x,connection_anchor_point_y);
    if (initial_orientation_horizontal_p) {
	link_1_delta = FIX(end_y_position - IFIX(connection_anchor_point_y));
	link_2_delta = FIX(end_x_position - IFIX(connection_anchor_point_x));
    }
    else {
	link_1_delta = FIX(end_x_position - IFIX(connection_anchor_point_x));
	link_2_delta = FIX(end_y_position - IFIX(connection_anchor_point_y));
    }
    return VALUES_3(link_1_delta,link_2_delta,
	    initial_orientation_horizontal_p);
}

/* EVEN-NUMBER-OF-DELTAS-IN-CONNECTION? */
Object even_number_of_deltas_in_connection_qm(connection)
    Object connection;
{
    Object delta_or_deltas_qm, temp;

    x_note_fn_call(99,7);
    delta_or_deltas_qm = ISVREF(connection,(SI_Long)6L);
    temp =  !TRUEP(delta_or_deltas_qm) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(delta_or_deltas_qm))
	return VALUES_1(FIXNUM_EVENP(length(delta_or_deltas_qm)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* ADD-BEND-TO-CONNECTION */
Object add_bend_to_connection(connection,loose_end)
    Object connection, loose_end;
{
    Object plist;

    x_note_fn_call(99,8);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal) ? 
	    TRUEP(even_number_of_deltas_in_connection_qm(connection)) : 
	    TRUEP(Nil)) {
	add_bend_to_connection_1(connection,loose_end);
	return add_bend_to_connection_1(connection,loose_end);
    }
    else
	return add_bend_to_connection_1(connection,loose_end);
}

/* ADD-BEND-TO-CONNECTION-1 */
Object add_bend_to_connection_1(connection,loose_end)
    Object connection, loose_end;
{
    Object link_1_delta, link_2_delta, delta_or_deltas, temp_1, rest_of_deltas;
    Object temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;
    char temp;
    Object result;

    x_note_fn_call(99,9);
    result = compute_stretched_links_of_connection_being_dragged(connection,
	    loose_end);
    MVS_2(result,link_1_delta,link_2_delta);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    if (EQ(ISVREF(connection,(SI_Long)2L),loose_end)) {
	if ( !TRUEP(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    SVREF(connection,FIX((SI_Long)6L)) = link_1_delta;
	}
	else if (ATOM(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = slot_value_list_2(delta_or_deltas,link_1_delta);
	    SVREF(connection,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    rest_of_deltas = delta_or_deltas;
	  next_loop:
	    if ( !TRUEP(rest_of_deltas))
		goto end_loop;
	    if ( !TRUEP(CDR(rest_of_deltas)))
		goto end_loop;
	    rest_of_deltas = M_CDR(rest_of_deltas);
	    goto next_loop;
	  end_loop:
	    temp_1 = slot_value_cons_1(link_1_delta,Nil);
	    M_CDR(rest_of_deltas) = temp_1;
	}
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	temp_2 = ISVREF(array_constant,IFIX(ISVREF(connection,
		(SI_Long)4L)) & (SI_Long)3L);
	temp_2 = EQ(temp_2,Qleft) || EQ(temp_2,Qright) ? Qtop : Qleft;
	if (EQ(temp_2,Qtop))
	    gensymed_symbol = (SI_Long)0L;
	else if (EQ(temp_2,Qleft))
	    gensymed_symbol = (SI_Long)1L;
	else if (EQ(temp_2,Qbottom))
	    gensymed_symbol = (SI_Long)2L;
	else
	    gensymed_symbol = (SI_Long)3L;
	gensymed_symbol_1 = (SI_Long)0L;
	svref_new_value = gensymed_symbol + gensymed_symbol_1;
	return VALUES_1(ISVREF(connection,(SI_Long)4L) = FIX(svref_new_value));
    }
    else {
	if ( !TRUEP(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    ISVREF(connection,(SI_Long)6L) = FIX((SI_Long)0L);
	}
	else if (ATOM(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = slot_value_list_2(FIX((SI_Long)0L),delta_or_deltas);
	    SVREF(connection,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = slot_value_cons_1(FIX((SI_Long)0L),ISVREF(connection,
		    (SI_Long)6L));
	    SVREF(connection,FIX((SI_Long)6L)) = temp_1;
	}
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	temp_2 = ISVREF(array_constant,IFIX(ISVREF(connection,
		(SI_Long)5L)) & (SI_Long)3L);
	temp_2 = EQ(temp_2,Qleft) || EQ(temp_2,Qright) ? Qtop : Qleft;
	if (EQ(temp_2,Qtop))
	    gensymed_symbol = (SI_Long)0L;
	else if (EQ(temp_2,Qleft))
	    gensymed_symbol = (SI_Long)1L;
	else if (EQ(temp_2,Qbottom))
	    gensymed_symbol = (SI_Long)2L;
	else
	    gensymed_symbol = (SI_Long)3L;
	gensymed_symbol_1 = (SI_Long)0L;
	svref_new_value = gensymed_symbol + gensymed_symbol_1;
	return VALUES_1(ISVREF(connection,(SI_Long)5L) = FIX(svref_new_value));
    }
}

/* REMOVE-KINK-AND-ADD-BEND */
Object remove_kink_and_add_bend(connection,loose_end,link_1_delta)
    Object connection, loose_end, link_1_delta;
{
    Object delta_or_deltas, temp_1, svref_new_value_1, rest_of_deltas;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;
    char temp;

    x_note_fn_call(99,10);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    if ( !TRUEP(delta_or_deltas))
	return add_bend_to_connection(connection,loose_end);
    else if (ATOM(delta_or_deltas)) {
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = Nil;
	if (EQ(ISVREF(connection,(SI_Long)2L),loose_end)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection,
		    (SI_Long)4L)) & (SI_Long)3L);
	    temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? Qtop : Qleft;
	    if (EQ(temp_1,Qtop))
		gensymed_symbol = (SI_Long)0L;
	    else if (EQ(temp_1,Qleft))
		gensymed_symbol = (SI_Long)1L;
	    else if (EQ(temp_1,Qbottom))
		gensymed_symbol = (SI_Long)2L;
	    else
		gensymed_symbol = (SI_Long)3L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    svref_new_value = gensymed_symbol + gensymed_symbol_1;
	    return VALUES_1(ISVREF(connection,(SI_Long)4L) = 
		    FIX(svref_new_value));
	}
	else {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection,
		    (SI_Long)5L)) & (SI_Long)3L);
	    temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? Qtop : Qleft;
	    if (EQ(temp_1,Qtop))
		gensymed_symbol = (SI_Long)0L;
	    else if (EQ(temp_1,Qleft))
		gensymed_symbol = (SI_Long)1L;
	    else if (EQ(temp_1,Qbottom))
		gensymed_symbol = (SI_Long)2L;
	    else
		gensymed_symbol = (SI_Long)3L;
	    gensymed_symbol_1 = (SI_Long)0L;
	    svref_new_value = gensymed_symbol + gensymed_symbol_1;
	    return VALUES_1(ISVREF(connection,(SI_Long)5L) = 
		    FIX(svref_new_value));
	}
    }
    else {
	if (EQ(ISVREF(connection,(SI_Long)2L),loose_end)) {
	    if ( !TRUEP(CDDR(delta_or_deltas))) {
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) 
			    & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		SVREF(connection,FIX((SI_Long)6L)) = Nil;
	    }
	    else if ( !TRUEP(CDDDR(delta_or_deltas))) {
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) 
			    & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		temp_1 = ISVREF(connection,(SI_Long)6L);
		svref_new_value_1 = CAR(temp_1);
		SVREF(connection,FIX((SI_Long)6L)) = svref_new_value_1;
	    }
	    else {
		rest_of_deltas = delta_or_deltas;
	      next_loop:
		if ( !TRUEP(rest_of_deltas))
		    goto end_loop;
		if ( !TRUEP(CDDDR(rest_of_deltas)))
		    goto end_loop;
		rest_of_deltas = M_CDR(rest_of_deltas);
		goto next_loop;
	      end_loop:
		M_CDR(rest_of_deltas) = Nil;
	    }
	}
	else if ( !TRUEP(CDDR(delta_or_deltas))) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    SVREF(connection,FIX((SI_Long)6L)) = Nil;
	}
	else if ( !TRUEP(CDDDR(delta_or_deltas))) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = ISVREF(connection,(SI_Long)6L);
	    svref_new_value_1 = CADDR(temp_1);
	    SVREF(connection,FIX((SI_Long)6L)) = svref_new_value_1;
	}
	else {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    temp_1 = ISVREF(connection,(SI_Long)6L);
	    svref_new_value_1 = CDDR(temp_1);
	    SVREF(connection,FIX((SI_Long)6L)) = svref_new_value_1;
	}
	return add_bend_to_connection(connection,loose_end);
    }
}

/* DELETE-LAST-BEND-FROM-CONNECTION */
Object delete_last_bend_from_connection(connection,loose_end)
    Object connection, loose_end;
{
    Object plist;

    x_note_fn_call(99,11);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal) ? 
	    TRUEP(even_number_of_deltas_in_connection_qm(connection)) : 
	    TRUEP(Nil)) {
	delete_last_bend_from_connection_1(connection,loose_end);
	return delete_last_bend_from_connection_1(connection,loose_end);
    }
    else
	return delete_last_bend_from_connection_1(connection,loose_end);
}

/* DELETE-LAST-BEND-FROM-CONNECTION-1 */
Object delete_last_bend_from_connection_1(connection,loose_end)
    Object connection, loose_end;
{
    Object delta_or_deltas, link_1_delta, link_2_delta;
    Object link_2_orientation_horizontal_p, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, svref_new_value, rest_of_deltas, temp_1;
    Object old_delta_or_deltas;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, svref_new_value_1;
    char temp;
    Object result;

    x_note_fn_call(99,12);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    if (EQ(ISVREF(connection,(SI_Long)2L),loose_end)) {
	if ( !TRUEP(delta_or_deltas)) {
	    result = compute_stretched_links_of_connection_being_dragged(connection,
		    loose_end);
	    MVS_3(result,link_1_delta,link_2_delta,
		    link_2_orientation_horizontal_p);
	    if (link_2_orientation_horizontal_p) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_1 = loose_end;
		gensymed_symbol_2 = FIXNUM_NEGATE(link_2_delta);
		gensymed_symbol_3 = (SI_Long)0L;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,FIX(gensymed_symbol_3));
	    }
	    else {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_1 = loose_end;
		gensymed_symbol_3 = (SI_Long)0L;
		gensymed_symbol_2 = FIXNUM_NEGATE(link_2_delta);
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			FIX(gensymed_symbol_3),gensymed_symbol_2);
	    }
	}
	else if (ATOM(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    SVREF(connection,FIX((SI_Long)6L)) = Nil;
	}
	else if ( !TRUEP(CDDR(delta_or_deltas))) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    svref_new_value = CAR(delta_or_deltas);
	    SVREF(connection,FIX((SI_Long)6L)) = svref_new_value;
	    reclaim_slot_value_list_1(delta_or_deltas);
	}
	else {
	    rest_of_deltas = ISVREF(connection,(SI_Long)6L);
	  next_loop:
	    if ( !TRUEP(rest_of_deltas))
		goto end_loop;
	    if ( !TRUEP(CDDR(rest_of_deltas)))
		goto end_loop;
	    rest_of_deltas = M_CDR(rest_of_deltas);
	    goto next_loop;
	  end_loop:
	    reclaim_slot_value_list_1(CDR(rest_of_deltas));
	    M_CDR(rest_of_deltas) = Nil;
	}
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection,
		(SI_Long)4L)) & (SI_Long)3L);
	temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? Qtop : Qleft;
	if (EQ(temp_1,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(temp_1,Qleft))
	    gensymed_symbol_3 = (SI_Long)1L;
	else if (EQ(temp_1,Qbottom))
	    gensymed_symbol_3 = (SI_Long)2L;
	else
	    gensymed_symbol_3 = (SI_Long)3L;
	gensymed_symbol_4 = (SI_Long)0L;
	svref_new_value_1 = gensymed_symbol_3 + gensymed_symbol_4;
	return VALUES_1(ISVREF(connection,(SI_Long)4L) = 
		FIX(svref_new_value_1));
    }
    else {
	result = compute_stretched_links_of_connection_being_dragged(connection,
		loose_end);
	MVS_3(result,link_1_delta,link_2_delta,
		link_2_orientation_horizontal_p);
	if ( !TRUEP(delta_or_deltas)) {
	    if (link_2_orientation_horizontal_p) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_1 = loose_end;
		gensymed_symbol_3 = EQ(ISVREF(array_constant,
			IFIX(ISVREF(connection,(SI_Long)5L)) & 
			(SI_Long)3L),Qleft) ? 
			IFIX(FIXNUM_NEGATE(link_2_delta)) : 
			IFIX(FIXNUM_ADD1(FIXNUM_NEGATE(link_2_delta)));
		gensymed_symbol_4 = (SI_Long)0L;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			FIX(gensymed_symbol_3),FIX(gensymed_symbol_4));
	    }
	    else {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_1 = loose_end;
		gensymed_symbol_3 = (SI_Long)0L;
		gensymed_symbol_4 = EQ(ISVREF(array_constant,
			IFIX(ISVREF(connection,(SI_Long)5L)) & 
			(SI_Long)3L),Qtop) ? 
			IFIX(FIXNUM_NEGATE(link_2_delta)) : 
			IFIX(FIXNUM_ADD1(FIXNUM_NEGATE(link_2_delta)));
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			FIX(gensymed_symbol_3),FIX(gensymed_symbol_4));
	    }
	}
	else if (ATOM(delta_or_deltas)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    SVREF(connection,FIX((SI_Long)6L)) = Nil;
	}
	else if ( !TRUEP(CDDR(delta_or_deltas))) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    svref_new_value = CADR(delta_or_deltas);
	    SVREF(connection,FIX((SI_Long)6L)) = svref_new_value;
	    reclaim_slot_value_list_1(delta_or_deltas);
	}
	else {
	    old_delta_or_deltas = ISVREF(connection,(SI_Long)6L);
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection);
	    svref_new_value = CDR(delta_or_deltas);
	    SVREF(connection,FIX((SI_Long)6L)) = svref_new_value;
	    reclaim_slot_value_cons_1(old_delta_or_deltas);
	}
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection,
		(SI_Long)5L)) & (SI_Long)3L);
	temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? ((SI_Long)0L > 
		IFIX(link_1_delta) ? Qbottom : Qtop) : (SI_Long)0L > 
		IFIX(link_1_delta) ? Qright : Qleft;
	if (EQ(temp_1,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(temp_1,Qleft))
	    gensymed_symbol_3 = (SI_Long)1L;
	else if (EQ(temp_1,Qbottom))
	    gensymed_symbol_3 = (SI_Long)2L;
	else
	    gensymed_symbol_3 = (SI_Long)3L;
	gensymed_symbol_4 = (SI_Long)0L;
	svref_new_value_1 = gensymed_symbol_3 + gensymed_symbol_4;
	return VALUES_1(ISVREF(connection,(SI_Long)5L) = 
		FIX(svref_new_value_1));
    }
}

static Object Qorthogonal;         /* orthogonal */

/* PLACE-CONNECTION-IF-ORTHOGONAL? */
Object place_connection_if_orthogonal_qm(connection_being_dragged,d1,d2,
	    maximum_mouse_leeway)
    Object connection_being_dragged, d1, d2, maximum_mouse_leeway;
{
    Object gensymed_symbol;

    x_note_fn_call(99,13);
    gensymed_symbol = 
	    getfq_function_no_default(ISVREF(connection_being_dragged,
	    (SI_Long)9L),Qconnection_style);
    if ( !TRUEP(gensymed_symbol) || EQ(gensymed_symbol,Qorthogonal) ?  
	    !TRUEP(loose_end_near_last_anchor_point_qm(d1,d2,
	    maximum_mouse_leeway)) : TRUEP(Nil))
	return VALUES_1(IFIX(d2) < IFIX(maximum_mouse_leeway) + 
		(SI_Long)4L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* LOOSE-END-NEAR-LAST-ANCHOR-POINT? */
Object loose_end_near_last_anchor_point_qm(d1,d2,maximum_mouse_leeway)
    Object d1, d2, maximum_mouse_leeway;
{
    x_note_fn_call(99,14);
    if (FIXNUM_LE(d1,maximum_mouse_leeway) && FIXNUM_LE(d2,
	    maximum_mouse_leeway))
	return VALUES_1(FIXNUM_LE(isqrt(FIXNUM_ADD(ltimes(d1,d1),ltimes(d2,
		d2))),maximum_mouse_leeway) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* HANDLE-CONNECTION-CLICK-NEAR-LAST-ANCHOR-POINT */
Object handle_connection_click_near_last_anchor_point(connection_being_dragged,
	    loose_end)
    Object connection_being_dragged, loose_end;
{
    Object plist;

    x_note_fn_call(99,15);
    if (ISVREF(connection_being_dragged,(SI_Long)6L)) {
	delete_last_bend_from_connection(connection_being_dragged,loose_end);
	plist = ISVREF(connection_being_dragged,(SI_Long)9L);
	if (plist)
	    return VALUES_1(EQ(getfq_function_no_default(plist,
		    Qconnection_style),Qdiagonal) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm, Qdelete_connections_without_leaving_stubs_qm);

static Object Qoutput;             /* output */

static Object Qinput;              /* input */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* RECLAIM-CONNECTIONS-VALUE */
Object reclaim_connections_value(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection_or_name, temp;
    Object ab_less_than_branch_qm_, connection_frame_or_class;
    Object connection_class, block_at_other_end_of_connection;
    Object position_of_block_at_other_end, side_of_block_at_other_end;
    Object position_on_side_of_block_at_other_end;
    Object new_connection_for_block_at_other_end, x2, proceed_with_delete_qm;
    Object connection_style_qm, line_pattern_qm, connection_arrows_qm;
    Object direction_qm, fsn, connection_frame_not_deleted, xa, ya;
    Object sub_class_bit_vector, connection, connections, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object connection_item_table_skip_list, head, tail, element_qm, last_1;
    Object next_qm, temp_3, svref_arg_2, gensymed_symbol_4, slot_group_qm;
    SI_Long gensymed_symbol_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1, block_at_other_end_input_object_p, connection_transient_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(99,16);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection_or_name = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
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
    next_loop:
    next_loop_1:
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
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection_or_name = ab_connection_;
      note_deletion_of_connection(connection_or_name);
      connection_frame_or_class = ISVREF(connection_or_name,(SI_Long)1L);
      connection_class = SYMBOLP(connection_frame_or_class) ? 
	      connection_frame_or_class : 
	      ISVREF(ISVREF(connection_frame_or_class,(SI_Long)1L),
	      (SI_Long)1L);
      block_at_other_end_of_connection = 
	      get_block_at_other_end_of_connection(connection_or_name,block);
      block_at_other_end_input_object_p = EQ(ISVREF(connection_or_name,
	      (SI_Long)3L),block_at_other_end_of_connection);
      position_of_block_at_other_end = Nil;
      side_of_block_at_other_end = Nil;
      position_on_side_of_block_at_other_end = Nil;
      new_connection_for_block_at_other_end = Nil;
      if (block_at_other_end_of_connection) {
	  if (SIMPLE_VECTOR_P(block_at_other_end_of_connection) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_at_other_end_of_connection)) 
		  > (SI_Long)2L &&  
		  !EQ(ISVREF(block_at_other_end_of_connection,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(block_at_other_end_of_connection,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
      }
      else
	  temp_1 = TRUEP(Nil);
      proceed_with_delete_qm = temp_1 ? ( !((SI_Long)0L != 
	      (IFIX(ISVREF(block_at_other_end_of_connection,(SI_Long)5L)) 
	      & (SI_Long)512L)) ? T : Nil) : Nil;
      connection_transient_p = (SI_Long)0L != 
	      (IFIX(ISVREF(connection_or_name,(SI_Long)7L)) & (SI_Long)64L);
      connection_style_qm = 
	      getfq_function_no_default(ISVREF(connection_or_name,
	      (SI_Long)9L),Qconnection_style);
      line_pattern_qm = 
	      copy_for_slot_value(connection_line_pattern(connection_or_name));
      connection_arrows_qm = 
	      copy_for_slot_value(connection_arrows_of_connection(connection_or_name));
      direction_qm = (SI_Long)0L != (IFIX(ISVREF(connection_or_name,
	      (SI_Long)7L)) & (SI_Long)1L) ? Nil : 
	      block_at_other_end_input_object_p ? Qoutput : Qinput;
      if (proceed_with_delete_qm) {
	  gensymed_symbol = 
		  ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
		  (SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  temp_1 = TRUEP(gensymed_symbol);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ? block_at_other_end_input_object_p : TRUEP(Nil)) {
	  gensymed_symbol = 
		  ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
		  (SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  update_connection_images(T,gensymed_symbol,connection_or_name);
      }
      temp_1 = TRUEP(Noting_changes_to_kb_p);
      if (temp_1);
      else {
	  gensymed_symbol_1 = IFIX(ISVREF(connection_or_name,(SI_Long)7L)) 
		  & (SI_Long)128L;
	  temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		  !TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		  TRUEP(Nil);
      }
      if (temp_1)
	  note_change_to_connection_1(connection_or_name);
      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp_1 = TRUEP(Nil);
      fsn = temp_1 ? 
	      copy_frame_serial_number(ISVREF(connection_frame_or_class,
	      (SI_Long)3L)) : Nil;
      connection_frame_not_deleted = Nil;
      if (fsn &&  !((SI_Long)0L != (IFIX(ISVREF(connection_frame_or_class,
	      (SI_Long)5L)) & (SI_Long)512L)))
	  delete_frame(connection_frame_or_class);
      if (fsn) {
	  gensymed_symbol = ISVREF(connection_frame_or_class,(SI_Long)3L);
	  temp_1 = SIMPLE_VECTOR_P(connection_frame_or_class) ? 
		  EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp_1);
	  else
	      temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp_1);
	  else if (FIXNUMP(fsn))
	      temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,
		      gensymed_symbol) : TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp_1 = TRUEP(Nil);
	  else {
	      xa = M_CAR(fsn);
	      ya = M_CAR(gensymed_symbol);
	      temp_1 = FIXNUM_LT(xa,ya);
	      if (temp_1);
	      else
		  temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  connection_frame_not_deleted =  !temp_1 ? T : Nil;
      }
      else
	  connection_frame_not_deleted = Nil;
      reclaim_frame_serial_number(fsn);
      SVREF(connection_or_name,FIX((SI_Long)1L)) = connection_class;
      if (proceed_with_delete_qm) {
	  sub_class_bit_vector = 
		  ISVREF(ISVREF(block_at_other_end_of_connection,
		  (SI_Long)1L),(SI_Long)19L);
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
	      delete_connection_in_block(block_at_other_end_of_connection,
		      connection_or_name,Nil);
	      if ( !TRUEP(connection_frame_not_deleted)) {
		  reclaim_connection_and_delta_or_deltas(connection_or_name,T);
		  delete_frame(block_at_other_end_of_connection);
	      }
	  }
	  else {
	      gensymed_symbol = 
		      ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  delete_connection_in_block(block_at_other_end_of_connection,
			  connection_or_name,Nil);
		  if ( !TRUEP(connection_frame_not_deleted))
		      reclaim_connection_and_delta_or_deltas(connection_or_name,
			      T);
	      }
	      else {
		  sub_class_bit_vector = 
			  ISVREF(ISVREF(block_at_other_end_of_connection,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Default_junction_class_description,
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
		      temp_1 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      delete_connection_in_block(block_at_other_end_of_connection,
			      connection_or_name,Nil);
		      if ( !TRUEP(connection_frame_not_deleted))
			  reclaim_connection_and_delta_or_deltas(connection_or_name,
				  T);
		      temp_1 = 
			      TRUEP(delete_junction_if_appropriate(block_at_other_end_of_connection));
		      if (temp_1);
		      else
			  temp_1 = 
				  TRUEP(Delete_connections_without_leaving_stubs_qm);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1);
		  else if (Delete_connections_without_leaving_stubs_qm) {
		      delete_connection_in_block(block_at_other_end_of_connection,
			      connection_or_name,Nil);
		      if ( !TRUEP(connection_frame_not_deleted))
			  reclaim_connection_and_delta_or_deltas(connection_or_name,
				  T);
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(block_at_other_end_of_connection,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_post_class_description,
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
			  temp_1 = (SI_Long)0L < gensymed_symbol_1;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      if (temp_1)
			  delete_subworkspace_connection_post_if_superfluous(block_at_other_end_of_connection);
		  }
		  else {
		      gensymed_symbol = 
			      ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
			      (SI_Long)14L));
		      gensymed_symbol = gensymed_symbol ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol,
			      (SI_Long)5L)) : Nil;
		      if (gensymed_symbol) {
			  if (block_at_other_end_input_object_p) {
			      position_of_block_at_other_end = 
				      ISVREF(connection_or_name,(SI_Long)5L);
			      side_of_block_at_other_end = 
				      ISVREF(array_constant,
				      IFIX(position_of_block_at_other_end) 
				      & (SI_Long)3L);
			      position_on_side_of_block_at_other_end = 
				      FIX(IFIX(position_of_block_at_other_end) 
				      >>  -  - (SI_Long)2L);
			  }
			  else {
			      position_of_block_at_other_end = 
				      ISVREF(connection_or_name,(SI_Long)4L);
			      side_of_block_at_other_end = 
				      ISVREF(array_constant,
				      IFIX(position_of_block_at_other_end) 
				      & (SI_Long)3L);
			      position_on_side_of_block_at_other_end = 
				      FIX(IFIX(position_of_block_at_other_end) 
				      >>  -  - (SI_Long)2L);
			  }
			  new_connection_for_block_at_other_end = 
				  make_stub(9,
				  block_at_other_end_of_connection,
				  connection_class,direction_qm,
				  side_of_block_at_other_end,
				  position_on_side_of_block_at_other_end,
				  connection_transient_p ? T : Nil,
				  connection_style_qm,line_pattern_qm,
				  connection_arrows_qm);
			  if (new_connection_for_block_at_other_end) {
			      connection = connection_or_name;
			      gensymed_symbol = 
				      ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
				      (SI_Long)14L));
			      gensymed_symbol = gensymed_symbol ? 
				      ACCESS_ONCE(ISVREF(gensymed_symbol,
				      (SI_Long)6L)) : Nil;
			      connections = gensymed_symbol;
			      if (connections) {
				  skip_list = CDR(connections);
				  key_value = connection;
				  key_hash_value = 
					  SXHASH_SYMBOL_1(connection) & 
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
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_4:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp);
				  MVS_2(result,succ,marked);
				next_loop_5:
				  if ( !TRUEP(marked))
				      goto end_loop_4;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_2 = ATOMIC_REF_OBJECT(reference);
				  temp = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_2,temp);
				  MVS_2(result,succ,marked);
				  goto next_loop_5;
				end_loop_4:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
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
				  temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) 
					  == key_hash_value ? 
					  (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? 
					  TRUEP(ISVREF(curr,(SI_Long)3L)) :
					   TRUEP(Nil)) : TRUEP(Nil);
			      }
			      else
				  temp_1 = TRUEP(Nil);
			      if (temp_1) {
				  replace_connection_in_block(block_at_other_end_of_connection,
					  connection_or_name,
					  new_connection_for_block_at_other_end);
				  if ( !TRUEP(connection_frame_not_deleted))
				      reclaim_connection_and_delta_or_deltas(connection_or_name,
					      T);
			      }
			      else
				  add_connection_in_block(block_at_other_end_of_connection,
					  new_connection_for_block_at_other_end);
			      temp = new_connection_for_block_at_other_end;
			      gensymed_symbol = 
				      ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
				      (SI_Long)14L));
			      gensymed_symbol = gensymed_symbol ? 
				      ACCESS_ONCE(ISVREF(gensymed_symbol,
				      (SI_Long)5L)) : Nil;
			      place_stub_loose_end_onto_workspace(block_at_other_end_of_connection,
				      temp,gensymed_symbol);
			      gensymed_symbol = 
				      ACCESS_ONCE(ISVREF(block_at_other_end_of_connection,
				      (SI_Long)14L));
			      gensymed_symbol = gensymed_symbol ? 
				      ACCESS_ONCE(ISVREF(gensymed_symbol,
				      (SI_Long)5L)) : Nil;
			      update_connection_images(Nil,gensymed_symbol,
				      new_connection_for_block_at_other_end);
			  }
		      }
		  }
	      }
	  }
      }
      if (line_pattern_qm)
	  reclaim_slot_value(line_pattern_qm);
      if (connection_arrows_qm)
	  reclaim_slot_value(connection_arrows_qm);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    if (gensymed_symbol) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	connection_item_table_skip_list = gensymed_symbol;
	head = M_CAR(M_CDR(connection_item_table_skip_list));
	tail = M_CDR(M_CDR(connection_item_table_skip_list));
	element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
		(SI_Long)0L));
	if ( !EQ(element_qm,tail))
	    reclaim_connection_item_table_nodes(element_qm,tail);
	reclaim_skip_list_element(head);
	reclaim_skip_list_element(tail);
	M_CDDR(connection_item_table_skip_list) = Nil;
	M_CADR(connection_item_table_skip_list) = Nil;
	M_CAR(connection_item_table_skip_list) = Nil;
	if (connection_item_table_skip_list) {
	    last_1 = connection_item_table_skip_list;
	    next_qm = Nil;
	  next_loop_6:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_6;
	    inline_note_reclaim_cons(last_1,Qlookup);
	    last_1 = next_qm;
	    goto next_loop_6;
	  end_loop_6:
	    inline_note_reclaim_cons(last_1,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_3 = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_3) = connection_item_table_skip_list;
		temp_3 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = last_1;
	    }
	    else {
		temp_3 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = connection_item_table_skip_list;
		temp_3 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    gensymed_symbol = block;
    gensymed_symbol_4 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_4 = Nil;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_4;
    else if ( !EQ(gensymed_symbol_4,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp_3 = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_3;
	temp_3 = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp_3,FIX((SI_Long)6L)) = gensymed_symbol_4;
    }
    return VALUES_1(gensymed_symbol_4);
}

/* CLEANUP-FOR-LOOSE-END */
Object cleanup_for_loose_end(loose_end)
    Object loose_end;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(99,17);
    frame = loose_end;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qloose_end)) {
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
    return remove_object_from_dragging_context(loose_end);
}

/* OK-TO-DELETE-CONNECTION-P */
Object ok_to_delete_connection_p(connection)
    Object connection;
{
    x_note_fn_call(99,18);
    return VALUES_1(T);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

/* DELETE-CONNECTION */
Object delete_connection varargs_1(int, n)
{
    Object connection;
    Object remove_subworkspace_connection_posts_if_appropriate_qm;
    Object preserved_loose_end_qm, input_end_object, output_end_object;
    Object connection_frame_or_class, connection_frame_not_deleted;
    Object current_drawing_priority, gensymed_symbol, x2, fsn, xa, ya;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(99,19);
    INIT_ARGS_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    remove_subworkspace_connection_posts_if_appropriate_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : T;
    preserved_loose_end_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    note_deletion_of_connection(connection);
    input_end_object = ISVREF(connection,(SI_Long)3L);
    output_end_object = ISVREF(connection,(SI_Long)2L);
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    connection_frame_not_deleted = Nil;
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    0);
      gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      update_connection_images(Qdelete,gensymed_symbol,connection);
      delete_connection_in_block(output_end_object,connection,
	      remove_subworkspace_connection_posts_if_appropriate_qm);
      delete_connection_in_block(input_end_object,connection,
	      remove_subworkspace_connection_posts_if_appropriate_qm);
      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      fsn = temp ? 
	      copy_frame_serial_number(ISVREF(connection_frame_or_class,
	      (SI_Long)3L)) : Nil;
      if (fsn)
	  delete_frame(connection_frame_or_class);
      if (fsn) {
	  gensymed_symbol = ISVREF(connection_frame_or_class,(SI_Long)3L);
	  temp = SIMPLE_VECTOR_P(connection_frame_or_class) ? 
		  EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp);
	  else if (FIXNUMP(fsn))
	      temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,
		      gensymed_symbol) : TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp = TRUEP(Nil);
	  else {
	      xa = M_CAR(fsn);
	      ya = M_CAR(gensymed_symbol);
	      temp = FIXNUM_LT(xa,ya);
	      if (temp);
	      else
		  temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  connection_frame_not_deleted =  !temp ? T : Nil;
      }
      else
	  connection_frame_not_deleted = Nil;
      reclaim_frame_serial_number(fsn);
      if ( !TRUEP(connection_frame_not_deleted)) {
	  sub_class_bit_vector = ISVREF(ISVREF(input_end_object,
		  (SI_Long)1L),(SI_Long)19L);
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
	      temp = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ?  !EQ(preserved_loose_end_qm,input_end_object) : 
		  TRUEP(Nil))
	      delete_frame(input_end_object);
	  else {
	      sub_class_bit_vector = ISVREF(ISVREF(output_end_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	      if (temp ?  !EQ(preserved_loose_end_qm,output_end_object) : 
		      TRUEP(Nil))
		  delete_frame(output_end_object);
	  }
      }
      if (remove_subworkspace_connection_posts_if_appropriate_qm) {
	  if (SIMPLE_VECTOR_P(output_end_object) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_end_object)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(output_end_object,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(output_end_object,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(output_end_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_post_class_description,
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ?  !EQ(preserved_loose_end_qm,output_end_object) : 
		  TRUEP(Nil))
	      delete_subworkspace_connection_post_if_superfluous(output_end_object);
	  if (SIMPLE_VECTOR_P(input_end_object) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_end_object)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(input_end_object,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(input_end_object,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(input_end_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_post_class_description,
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ?  !EQ(preserved_loose_end_qm,input_end_object) : 
		  TRUEP(Nil))
	      delete_subworkspace_connection_post_if_superfluous(input_end_object);
      }
      remove_object_from_dragging_context(connection);
      if ( !TRUEP(connection_frame_not_deleted))
	  result = reclaim_connection_and_delta_or_deltas(connection,T);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DELETE-CONNECTION-TO-STUB */
Object delete_connection_to_stub(connection)
    Object connection;
{
    Object connection_frame_or_class, connection_class, connection_style_qm;
    Object line_pattern_qm, connection_arrows_qm, input_end_object_to_delete;
    Object output_end_object_to_delete, current_drawing_priority;
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, new_input_end_connection, x2, sub_class_bit_vector;
    Object temp_1, connections, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, output_end_object;
    Object output_end_position, output_end_side, new_output_end_connection;
    Object fsn, xa, ya;
    SI_Long input_end_position_on_side, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, output_end_position_on_side;
    char connection_transient_p, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(99,20);
    note_deletion_of_connection(connection);
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    connection_class = SYMBOLP(connection_frame_or_class) ? 
	    connection_frame_or_class : 
	    ISVREF(ISVREF(connection_frame_or_class,(SI_Long)1L),(SI_Long)1L);
    connection_transient_p = (SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)64L);
    connection_style_qm = getfq_function_no_default(ISVREF(connection,
	    (SI_Long)9L),Qconnection_style);
    line_pattern_qm = copy_for_slot_value(connection_line_pattern(connection));
    connection_arrows_qm = 
	    copy_for_slot_value(connection_arrows_of_connection(connection));
    input_end_object_to_delete = Nil;
    output_end_object_to_delete = Nil;
    current_drawing_priority = Kdraw_as_late_as_possible;
    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
	    0);
      gensymed_symbol = connection;
      input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
      input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
      input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	      (SI_Long)3L);
      input_end_position_on_side = IFIX(input_end_position) >>  -  - 
	      (SI_Long)2L;
      gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(input_end_side,Qleft))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(input_end_side,Qright)) {
	  gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	  gensymed_symbol_2 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
      }
      else
	  gensymed_symbol_1 = input_end_position_on_side;
      gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(input_end_side,Qtop))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(input_end_side,Qbottom)) {
	  gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(input_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	  gensymed_symbol_2 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
      }
      else
	  gensymed_symbol_1 = input_end_position_on_side;
      new_input_end_connection = Nil;
      gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      update_connection_images(Qdelete,gensymed_symbol,connection);
      if (SIMPLE_VECTOR_P(input_end_object) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_end_object)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(input_end_object,(SI_Long)1L),
	      Qavailable_frame_vector)) {
	  x2 = ISVREF(input_end_object,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  sub_class_bit_vector = ISVREF(ISVREF(input_end_object,
		  (SI_Long)1L),(SI_Long)19L);
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
	      temp = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp = TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  delete_connection_in_block(input_end_object,connection,Nil);
	  input_end_object_to_delete = input_end_object;
      }
      else {
	  if (SIMPLE_VECTOR_P(input_end_object) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_end_object)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(input_end_object,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(input_end_object,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(input_end_object,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Default_junction_class_description,
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      delete_connection_in_block(input_end_object,connection,Nil);
	      temp =  !EQ(input_end_object,ISVREF(connection,(SI_Long)2L)) 
		      ? 
		      TRUEP(delete_junction_if_appropriate(input_end_object)) 
		      : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else {
	      new_input_end_connection = make_stub(9,input_end_object,
		      connection_class,(SI_Long)0L != 
		      (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)1L) 
		      ? Nil : Qoutput,input_end_side,
		      FIX(input_end_position_on_side),
		      connection_transient_p ? T : Nil,connection_style_qm,
		      line_pattern_qm,connection_arrows_qm);
	      temp_1 = new_input_end_connection;
	      gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      place_stub_loose_end_onto_workspace(input_end_object,temp_1,
		      gensymed_symbol);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object,
		      (SI_Long)14L));
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
		next_loop:
		  if (level < ab_loop_bind_)
		      goto end_loop;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_1:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_2:
		  if ( !TRUEP(marked))
		      goto end_loop_1;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
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
		  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			   (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			  TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			  TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  replace_connection_in_block(input_end_object,connection,
			  new_input_end_connection);
	      else
		  add_connection_in_block(input_end_object,
			  new_input_end_connection);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      update_connection_images(Nil,gensymed_symbol,
		      new_input_end_connection);
	  }
      }
      gensymed_symbol = connection;
      output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
      output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
      output_end_side = ISVREF(array_constant,IFIX(output_end_position) & 
	      (SI_Long)3L);
      output_end_position_on_side = IFIX(output_end_position) >>  -  - 
	      (SI_Long)2L;
      gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(output_end_side,Qleft))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(output_end_side,Qright)) {
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	  gensymed_symbol_2 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
      }
      else
	  gensymed_symbol_1 = output_end_position_on_side;
      gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      if (EQ(output_end_side,Qtop))
	  gensymed_symbol_1 = (SI_Long)0L;
      else if (EQ(output_end_side,Qbottom)) {
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	  gensymed_symbol_2 = Dont_include_offset_for_end_position_qm ? 
		  (SI_Long)0L : (SI_Long)1L;
	  gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
      }
      else
	  gensymed_symbol_1 = output_end_position_on_side;
      new_output_end_connection = Nil;
      sub_class_bit_vector = ISVREF(ISVREF(output_end_object,(SI_Long)1L),
	      (SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
      if (temp) {
	  delete_connection_in_block(output_end_object,connection,Nil);
	  output_end_object_to_delete = output_end_object;
      }
      else {
	  sub_class_bit_vector = ISVREF(ISVREF(output_end_object,
		  (SI_Long)1L),(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Default_junction_class_description,
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
	      delete_connection_in_block(output_end_object,connection,Nil);
	      temp =  !EQ(output_end_object,ISVREF(connection,
		      (SI_Long)3L)) ? 
		      TRUEP(delete_junction_if_appropriate(output_end_object)) 
		      : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else {
	      new_output_end_connection = make_stub(9,output_end_object,
		      connection_class,(SI_Long)0L != 
		      (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)1L) 
		      ? Nil : Qinput,output_end_side,
		      FIX(output_end_position_on_side),
		      connection_transient_p ? T : Nil,connection_style_qm,
		      line_pattern_qm,connection_arrows_qm);
	      temp_1 = new_output_end_connection;
	      gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      place_stub_loose_end_onto_workspace(output_end_object,temp_1,
		      gensymed_symbol);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object,
		      (SI_Long)14L));
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
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_4:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_5:
		  if ( !TRUEP(marked))
		      goto end_loop_4;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_2 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_2,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_5;
		end_loop_4:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			   (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			  TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			  TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  replace_connection_in_block(output_end_object,connection,
			  new_output_end_connection);
	      else
		  add_connection_in_block(output_end_object,
			  new_output_end_connection);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object,
		      (SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      update_connection_images(Nil,gensymed_symbol,
		      new_output_end_connection);
	  }
      }
      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      fsn = temp ? 
	      copy_frame_serial_number(ISVREF(connection_frame_or_class,
	      (SI_Long)3L)) : Nil;
      if (fsn)
	  delete_frame(connection_frame_or_class);
      if (fsn) {
	  gensymed_symbol = ISVREF(connection_frame_or_class,(SI_Long)3L);
	  temp = SIMPLE_VECTOR_P(connection_frame_or_class) ? 
		  EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp);
	  else if (FIXNUMP(fsn))
	      temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,
		      gensymed_symbol) : TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp = TRUEP(Nil);
	  else {
	      xa = M_CAR(fsn);
	      ya = M_CAR(gensymed_symbol);
	      temp = FIXNUM_LT(xa,ya);
	      if (temp);
	      else
		  temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  temp =  !temp;
      }
      else
	  temp = TRUEP(Nil);
      if ( !temp) {
	  if (input_end_object_to_delete)
	      delete_frame(input_end_object_to_delete);
	  if (output_end_object_to_delete)
	      delete_frame(output_end_object_to_delete);
	  reclaim_connection_and_delta_or_deltas(connection,Nil);
      }
      reclaim_frame_serial_number(fsn);
    POP_SPECIAL();
    if (line_pattern_qm)
	reclaim_slot_value(line_pattern_qm);
    if (connection_arrows_qm)
	return reclaim_slot_value(connection_arrows_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Junction_blocks_not_to_be_deleted, Qjunction_blocks_not_to_be_deleted);

static Object Qconnection_item_table;  /* connection-item-table */

static Object Qjunction_connection_1;  /* junction-connection-1 */

static Object Qjunction_connection_2;  /* junction-connection-2 */

/* DELETE-JUNCTION-IF-APPROPRIATE */
Object delete_junction_if_appropriate(junction_block)
    Object junction_block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, ab_less_than_branch_qm_, junction_connections;
    Object junction_connection_1, junction_connection_2;
    Object junction_connection_1_end_position_side;
    Object junction_connection_1_opposite_end_position_side;
    Object junction_connection_2_end_position_side, loose_end_1, loose_end_2;
    Object block_at_other_end_of_connection_1;
    Object block_at_other_end_of_connection_2, workspace_qm;
    Object sub_class_bit_vector, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, connection_table_1;
    Object connection_table_2, connection_item_1, connection_item_2;
    Object slot_group_qm, gensymed_symbol_5, temp_3;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, junction_block_half_width;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(99,21);
    if ( !TRUEP(memq_function(junction_block,
	    Junction_blocks_not_to_be_deleted))) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(junction_block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
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
	next_loop:
	next_loop_1:
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
		  ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_2:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_2;
		end_loop:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_connection_ = M_CAR(ab_entry_cons_);
		  ab_connection_item_ = M_CDR(ab_entry_cons_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	      goto end_1;
	  goto next_loop_1;
	end_loop_1:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_2;
	  connection = ab_connection_;
	  ab_loopvar__2 = gensym_cons_1(connection,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop_2:
	  junction_connections = ab_loopvar_;
	  goto end_2;
	  junction_connections = Qnil;
	end_2:;
	POP_SPECIAL();
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	junction_block_half_width = gensymed_symbol_1 >>  -  - 
		gensymed_symbol_2;
	if ( !TRUEP(junction_connections) ||  
		!TRUEP(CDR(junction_connections))) {
	    delete_frame(junction_block);
	    temp = T;
	}
	else if ( !TRUEP(CDDR(junction_connections))) {
	    junction_connection_1 = CAR(junction_connections);
	    junction_connection_2 = CADR(junction_connections);
	    junction_connection_1_end_position_side = Nil;
	    junction_connection_1_opposite_end_position_side = Nil;
	    junction_connection_2_end_position_side = Nil;
	    loose_end_1 = Nil;
	    loose_end_2 = Nil;
	    block_at_other_end_of_connection_1 = 
		    get_block_at_other_end_of_connection(junction_connection_1,
		    junction_block);
	    block_at_other_end_of_connection_2 = 
		    get_block_at_other_end_of_connection(junction_connection_2,
		    junction_block);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(junction_block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    workspace_qm = gensymed_symbol;
	    if (workspace_qm) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(block_at_other_end_of_connection_1,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
		if (temp_1) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(block_at_other_end_of_connection_2,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Loose_end_class_description,
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
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
	    if (((temp_1 ?  !((SI_Long)0L != 
		    (IFIX(ISVREF(block_at_other_end_of_connection_1,
		    (SI_Long)5L)) & (SI_Long)512L) || (SI_Long)0L != 
		    (IFIX(ISVREF(block_at_other_end_of_connection_2,
		    (SI_Long)5L)) & (SI_Long)512L)) : TRUEP(Nil)) ? 
		    TRUEP(connection_cross_section_patterns_compatible_qm(junction_connection_1,
		    junction_connection_2)) : TRUEP(Nil)) ? ((SI_Long)0L 
		    != (IFIX(ISVREF(junction_connection_1,(SI_Long)7L)) & 
		    (SI_Long)1L) ? (SI_Long)0L != 
		    (IFIX(ISVREF(junction_connection_2,(SI_Long)7L)) & 
		    (SI_Long)1L) :  !((SI_Long)0L != 
		    (IFIX(ISVREF(junction_connection_2,(SI_Long)7L)) & 
		    (SI_Long)1L)) &&  !(EQ(ISVREF(junction_connection_1,
		    (SI_Long)3L),junction_block) && 
		    EQ(ISVREF(junction_connection_2,(SI_Long)3L),
		    junction_block) || EQ(ISVREF(junction_connection_1,
		    (SI_Long)2L),junction_block) && 
		    EQ(ISVREF(junction_connection_2,(SI_Long)2L),
		    junction_block))) : TRUEP(Nil)) {
		update_connection_images(T,workspace_qm,junction_connection_1);
		update_connection_images(T,workspace_qm,junction_connection_2);
		loose_end_1 = make_frame(Qloose_end);
		loose_end_2 = make_frame(Qloose_end);
		add_subblock(loose_end_1,workspace_qm);
		add_subblock(loose_end_2,workspace_qm);
		delete_connection_in_block(junction_block,
			junction_connection_1,Nil);
		delete_connection_in_block(junction_block,
			junction_connection_2,Nil);
		tail = 
			make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol) = Qconnection_item_table;
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
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_4) = head;
		M_CDR(gensymed_symbol_4) = tail;
		inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		M_CDR(gensymed_symbol) = gensymed_symbol_4;
		inline_note_allocate_cons(gensymed_symbol,Qlookup);
		connection_table_1 = gensymed_symbol;
		tail = 
			make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol) = Qconnection_item_table;
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
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_4) = head;
		M_CDR(gensymed_symbol_4) = tail;
		inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		M_CDR(gensymed_symbol) = gensymed_symbol_4;
		inline_note_allocate_cons(gensymed_symbol,Qlookup);
		connection_table_2 = gensymed_symbol;
		connection_item_1 = 
			make_connection_item_1(junction_connection_1);
		connection_item_2 = 
			make_connection_item_1(junction_connection_2);
		temp = get_direction_of_connection(2,junction_connection_1,
			block_at_other_end_of_connection_1);
		if (EQ(temp,Qoutput)) {
		    temp_2 = slot_value_cons_1(Qjunction_connection_1,Nil);
		    SVREF(connection_item_1,FIX((SI_Long)2L)) = temp_2;
		}
		else {
		    temp_2 = slot_value_cons_1(Qjunction_connection_1,Nil);
		    SVREF(connection_item_1,FIX((SI_Long)1L)) = temp_2;
		}
		temp = get_direction_of_connection(2,junction_connection_2,
			block_at_other_end_of_connection_2);
		if (EQ(temp,Qoutput)) {
		    temp_2 = slot_value_cons_1(Qjunction_connection_2,Nil);
		    SVREF(connection_item_2,FIX((SI_Long)2L)) = temp_2;
		}
		else {
		    temp_2 = slot_value_cons_1(Qjunction_connection_2,Nil);
		    SVREF(connection_item_2,FIX((SI_Long)1L)) = temp_2;
		}
		gensymed_symbol = junction_connection_1;
		set_skip_list_entry(connection_table_1,FIX((SI_Long)7L),
			Qeq,Nil,T,gensymed_symbol,
			FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum)),connection_item_1);
		gensymed_symbol = junction_connection_2;
		set_skip_list_entry(connection_table_2,FIX((SI_Long)7L),
			Qeq,Nil,T,gensymed_symbol,
			FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum)),connection_item_2);
		gensymed_symbol = loose_end_1;
		gensymed_symbol_4 = Nil;
		slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		gensymed_symbol_4 = connection_table_1;
		if (slot_group_qm)
		    SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_4;
		else if ( !EQ(gensymed_symbol_4,Qnil)) {
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(gensymed_symbol,
				Qslot_group_for_block_qm);
		    temp_2 = make_icon_slot_group_1();
		    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
		    temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
		    SVREF(temp_2,FIX((SI_Long)6L)) = gensymed_symbol_4;
		}
		gensymed_symbol = loose_end_2;
		gensymed_symbol_4 = Nil;
		slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		gensymed_symbol_4 = connection_table_2;
		if (slot_group_qm)
		    SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_4;
		else if ( !EQ(gensymed_symbol_4,Qnil)) {
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(gensymed_symbol,
				Qslot_group_for_block_qm);
		    temp_2 = make_icon_slot_group_1();
		    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
		    temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
		    SVREF(temp_2,FIX((SI_Long)6L)) = gensymed_symbol_4;
		}
		if (EQ(ISVREF(junction_connection_1,(SI_Long)3L),
			junction_block)) {
		    junction_connection_1_end_position_side = 
			    ISVREF(array_constant,
			    IFIX(ISVREF(junction_connection_1,
			    (SI_Long)5L)) & (SI_Long)3L);
		    junction_connection_1_opposite_end_position_side = 
			    ISVREF(array_constant,
			    IFIX(ISVREF(junction_connection_1,
			    (SI_Long)4L)) & (SI_Long)3L);
		    if ( !TRUEP(ISVREF(junction_connection_1,(SI_Long)6L))) {
			if (EQ(junction_connection_1_end_position_side,
				    Qleft)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant_2))
				junction_connection_1_end_position_side = Qtop;
			}
			else if (EQ(junction_connection_1_end_position_side,
				Qright)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant_2))
				junction_connection_1_end_position_side = Qtop;
			}
			else if (EQ(junction_connection_1_end_position_side,
				Qtop)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant))
				junction_connection_1_end_position_side = 
					Qleft;
			}
			else if (memq_function(junction_connection_1_opposite_end_position_side,
				list_constant))
			    junction_connection_1_end_position_side = Qleft;
		    }
		    set_input_end_of_connection(junction_connection_1,
			    loose_end_1,
			    junction_connection_1_end_position_side,
			    FIX((SI_Long)0L));
		    if (EQ(ISVREF(junction_connection_2,(SI_Long)3L),
			    junction_block)) {
			junction_connection_2_end_position_side = 
				ISVREF(array_constant,
				IFIX(ISVREF(junction_connection_2,
				(SI_Long)5L)) & (SI_Long)3L);
			set_input_end_of_connection(junction_connection_2,
				loose_end_2,
				junction_connection_2_end_position_side,
				FIX((SI_Long)0L));
		    }
		    else {
			junction_connection_2_end_position_side = 
				ISVREF(array_constant,
				IFIX(ISVREF(junction_connection_2,
				(SI_Long)4L)) & (SI_Long)3L);
			set_output_end_of_connection(junction_connection_2,
				loose_end_2,
				junction_connection_2_end_position_side,
				FIX((SI_Long)0L));
		    }
		}
		else {
		    junction_connection_1_end_position_side = 
			    ISVREF(array_constant,
			    IFIX(ISVREF(junction_connection_1,
			    (SI_Long)4L)) & (SI_Long)3L);
		    junction_connection_1_opposite_end_position_side = 
			    ISVREF(array_constant,
			    IFIX(ISVREF(junction_connection_1,
			    (SI_Long)5L)) & (SI_Long)3L);
		    if ( !TRUEP(ISVREF(junction_connection_1,(SI_Long)6L))) {
			if (EQ(junction_connection_1_end_position_side,
				    Qleft)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant_2))
				junction_connection_1_end_position_side = Qtop;
			}
			else if (EQ(junction_connection_1_end_position_side,
				Qright)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant_2))
				junction_connection_1_end_position_side = Qtop;
			}
			else if (EQ(junction_connection_1_end_position_side,
				Qtop)) {
			    if (memq_function(junction_connection_1_opposite_end_position_side,
				    list_constant))
				junction_connection_1_end_position_side = 
					Qleft;
			}
			else if (memq_function(junction_connection_1_opposite_end_position_side,
				list_constant))
			    junction_connection_1_end_position_side = Qleft;
		    }
		    set_output_end_of_connection(junction_connection_1,
			    loose_end_1,
			    junction_connection_1_end_position_side,
			    FIX((SI_Long)0L));
		    if (EQ(ISVREF(junction_connection_2,(SI_Long)3L),
			    junction_block)) {
			junction_connection_2_end_position_side = 
				ISVREF(array_constant,
				IFIX(ISVREF(junction_connection_2,
				(SI_Long)5L)) & (SI_Long)3L);
			set_input_end_of_connection(junction_connection_2,
				loose_end_2,
				junction_connection_2_end_position_side,
				FIX((SI_Long)0L));
		    }
		    else {
			junction_connection_2_end_position_side = 
				ISVREF(array_constant,
				IFIX(ISVREF(junction_connection_2,
				(SI_Long)4L)) & (SI_Long)3L);
			set_output_end_of_connection(junction_connection_2,
				loose_end_2,
				junction_connection_2_end_position_side,
				FIX((SI_Long)0L));
		    }
		}
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end_1,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_4 = loose_end_1;
		if (EQ(junction_connection_1_end_position_side,Qleft)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		}
		else if (EQ(junction_connection_1_end_position_side,Qright)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		}
		else {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		    gensymed_symbol_2 = junction_block_half_width;
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		}
		gensymed_symbol_5 = ISVREF(loose_end_1,(SI_Long)14L);
		gensymed_symbol_5 = gensymed_symbol_5 ? 
			ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		if (EQ(junction_connection_1_end_position_side,Qtop)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		}
		else if (EQ(junction_connection_1_end_position_side,Qbottom)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		}
		else {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		    gensymed_symbol_3 = junction_block_half_width;
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		}
		gensymed_symbol_5 = ISVREF(loose_end_1,(SI_Long)14L);
		gensymed_symbol_5 = gensymed_symbol_5 ? 
			ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol_5);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
			FIX(gensymed_symbol_1),FIX(gensymed_symbol_2));
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end_2,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
		gensymed_symbol_4 = loose_end_2;
		if (EQ(junction_connection_2_end_position_side,Qleft)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		}
		else if (EQ(junction_connection_2_end_position_side,Qright)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		}
		else {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol_5);
		    gensymed_symbol_2 = junction_block_half_width;
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		}
		gensymed_symbol_5 = ISVREF(loose_end_2,(SI_Long)14L);
		gensymed_symbol_5 = gensymed_symbol_5 ? 
			ISVREF(gensymed_symbol_5,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		if (EQ(junction_connection_2_end_position_side,Qtop)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		}
		else if (EQ(junction_connection_2_end_position_side,Qbottom)) {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		}
		else {
		    gensymed_symbol_5 = ISVREF(junction_block,(SI_Long)14L);
		    gensymed_symbol_5 = gensymed_symbol_5 ? 
			    ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_5);
		    gensymed_symbol_3 = junction_block_half_width;
		    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
		}
		gensymed_symbol_5 = ISVREF(loose_end_2,(SI_Long)14L);
		gensymed_symbol_5 = gensymed_symbol_5 ? 
			ISVREF(gensymed_symbol_5,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol_5);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
			FIX(gensymed_symbol_1),FIX(gensymed_symbol_2));
		temp = loose_end_2;
		gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = junction_block_half_width;
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol = ISVREF(loose_end_2,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_3 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol = ISVREF(junction_block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = junction_block_half_width;
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol = ISVREF(loose_end_2,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		change_connection_deltas_for_object_being_dragged(junction_connection_2,
			temp,temp_3,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2));
		update_images_of_block(loose_end_1,Nil,Nil);
		update_images_of_block(loose_end_2,Nil,Nil);
		if (EQ(ISVREF(junction_connection_1,(SI_Long)2L),loose_end_1))
		    update_connection_images(Nil,workspace_qm,
			    junction_connection_1);
		if (EQ(ISVREF(junction_connection_2,(SI_Long)2L),loose_end_2))
		    update_connection_images(Nil,workspace_qm,
			    junction_connection_2);
		join_two_connections(loose_end_1,loose_end_2);
		delete_frame(junction_block);
		temp = T;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Qnil;
	reclaim_gensym_list_1(junction_connections);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-SUBWORKSPACE-CONNECTION-POST-IF-APPROPRIATE */
Object add_subworkspace_connection_post_if_appropriate(connection,object)
    Object connection, object;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, port_name_qm;
    Object subworkspace, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(99,22);
    if (SIMPLE_VECTOR_P(object) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(object,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(object,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Object_class_description,
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
    if (temp ? TRUEP(subworkspace_connection_posts_p(object)) : TRUEP(Nil)) {
	port_name_qm = get_port_name_given_block_and_connection(2,object,
		connection);
	subworkspace = Nil;
	ab_loop_list_ = ISVREF(object,(SI_Long)18L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_subworkspace_connection_post(connection,port_name_qm,object,
		subworkspace);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcross_section_pattern;  /* cross-section-pattern */

/* ADD-NEW-CONNECTION-TO-BLOCK */
Object add_new_connection_to_block varargs_1(int, n)
{
    Object loose_end, block;
    Object allow_multiple_connections_on_junction_side_qm, connection;
    Object connection_frame_or_class, x2, cross_section_pattern, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, temp_3;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, cross_section_stripe, width, ab_loop_list_;
    Object ab_loopvar_, ab_loop_desetq_, connection_overall_width;
    Object loose_end_delta_x_in_workspace, loose_end_delta_y_in_workspace;
    Object side, position_on_side, make_connection_qm;
    Object desired_position_on_side_qm, current_link_1_delta;
    Object current_link_2_delta, loose_end_initial_orientation_horizontal_p;
    Object sub_class_bit_vector, delta_qm, gensymed_symbol_6, plist;
    Object loose_end_side, temp1, slot_group_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long connection_half_width, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, svref_new_value_1;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(99,23);
    INIT_ARGS_nonrelocating();
    loose_end = REQUIRED_ARG_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    allow_multiple_connections_on_junction_side_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    connection = get_connection_for_loose_end(loose_end);
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	cross_section_pattern = ISVREF(connection_frame_or_class,(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		Class_description_gkbprop)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = connection_frame_or_class;
	    key_hash_value = SXHASH_SYMBOL_1(connection_frame_or_class) & 
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    temp_2 = CAAR(cross_section_pattern);
    cross_section_stripe = CONSP(temp_2) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    width = Nil;
    ab_loop_list_ = cross_section_stripe;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_24:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_24;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
    goto next_loop_24;
  end_loop_24:
    connection_overall_width = ab_loopvar_;
    goto end_9;
    connection_overall_width = Qnil;
  end_9:;
    connection_half_width = IFIX(connection_overall_width) >>  -  - 
	    (SI_Long)1L;
    loose_end_delta_x_in_workspace = FIX((SI_Long)0L);
    loose_end_delta_y_in_workspace = FIX((SI_Long)0L);
    side = Nil;
    position_on_side = Nil;
    make_connection_qm = Nil;
    desired_position_on_side_qm = Nil;
    if (EQ(get_block_at_other_end_of_connection(connection,loose_end),block)) {
	if (loose_end_within_block_p(block,loose_end)) {
	    delete_connection(1,connection);
	    return VALUES_2(T,T);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	result = compute_stretched_links_of_connection_being_dragged(connection,
		loose_end);
	MVS_3(result,current_link_1_delta,current_link_2_delta,
		loose_end_initial_orientation_horizontal_p);
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Default_junction_class_description,(SI_Long)18L));
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
	if (temp) {
	    if (loose_end_within_block_p(block,loose_end)) {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol);
		gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
		gensymed_symbol_4 = (SI_Long)1L;
		desired_position_on_side_qm = FIX(gensymed_symbol_3 >>  -  
			- gensymed_symbol_4);
		gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		update_connection_images(T,gensymed_symbol,connection);
		result = compute_side_of_exit(block,loose_end,connection,
			current_link_1_delta,current_link_2_delta,
			loose_end_initial_orientation_horizontal_p,
			desired_position_on_side_qm);
		MVS_4(result,side,position_on_side,
			loose_end_delta_x_in_workspace,
			loose_end_delta_y_in_workspace);
		if (side && ( 
			!TRUEP(side_of_junction_has_connection_p(block,
			side)) || 
			allow_multiple_connections_on_junction_side_qm)) {
		    make_connection_qm = T;
		    delta_qm = connection_is_straight_qm(connection);
		    if (delta_qm)
			put_kink_into_connection_if_straight_1(connection,
				delta_qm);
		}
		else {
		    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,
			    (SI_Long)14L));
		    gensymed_symbol = gensymed_symbol ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol,
			    (SI_Long)5L)) : Nil;
		    update_connection_images(Nil,gensymed_symbol,connection);
		}
	    }
	}
	else if (loose_end_within_block_and_border_p(block,loose_end,
		FIX(connection_half_width))) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    update_connection_images(T,gensymed_symbol,connection);
	    result = compute_side_of_exit(block,loose_end,connection,
		    current_link_1_delta,current_link_2_delta,
		    loose_end_initial_orientation_horizontal_p,Nil);
	    MVS_4(result,side,position_on_side,
		    loose_end_delta_x_in_workspace,
		    loose_end_delta_y_in_workspace);
	    if (side)
		make_connection_qm = T;
	    else {
		gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		update_connection_images(Nil,gensymed_symbol,connection);
	    }
	}
	if (make_connection_qm && side && position_on_side) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	    gensymed_symbol_1 = loose_end;
	    gensymed_symbol_2 = loose_end_delta_x_in_workspace;
	    gensymed_symbol_6 = loose_end_delta_y_in_workspace;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_6);
	    if (EQ(ISVREF(connection,(SI_Long)3L),loose_end)) {
		change_connection_deltas_for_input_end_object_being_dragged(connection,
			loose_end,loose_end_delta_x_in_workspace,
			loose_end_delta_y_in_workspace);
		plist = ISVREF(connection,(SI_Long)9L);
		if (plist && EQ(getfq_function_no_default(plist,
			Qconnection_style),Qdiagonal)) {
		    loose_end_side = ISVREF(array_constant,
			    IFIX(ISVREF(connection,(SI_Long)5L)) & 
			    (SI_Long)3L);
		    if ( !TRUEP(side_orientations_same_p(loose_end_side,
				side))) {
			add_missing_deltas_to_connection(connection);
			temp1 = 
				reverse_connection_delta_pairs(ISVREF(connection,
				(SI_Long)6L));
			reclaim_slot_value_list_1(ISVREF(connection,
				(SI_Long)6L));
			temp = TRUEP(Noting_changes_to_kb_p);
			if (temp);
			else {
			    gensymed_symbol_3 = IFIX(ISVREF(connection,
				    (SI_Long)7L)) & (SI_Long)128L;
			    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
				    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
				    : TRUEP(Nil);
			}
			if (temp)
			    note_change_to_connection_1(connection);
			SVREF(connection,FIX((SI_Long)6L)) = temp1;
			remove_redundant_deltas_from_connection(connection);
		    }
		}
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol_3 = IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		SVREF(connection,FIX((SI_Long)3L)) = block;
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol_3 = IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		if (EQ(side,Qtop))
		    gensymed_symbol_3 = (SI_Long)0L;
		else if (EQ(side,Qleft))
		    gensymed_symbol_3 = (SI_Long)1L;
		else if (EQ(side,Qbottom))
		    gensymed_symbol_3 = (SI_Long)2L;
		else
		    gensymed_symbol_3 = (SI_Long)3L;
		gensymed_symbol_4 = IFIX(position_on_side) << (SI_Long)2L;
		svref_new_value_1 = gensymed_symbol_3 + gensymed_symbol_4;
		ISVREF(connection,(SI_Long)5L) = FIX(svref_new_value_1);
	    }
	    else {
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol_3 = IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		SVREF(connection,FIX((SI_Long)2L)) = block;
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol_3 = IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(connection);
		if (EQ(side,Qtop))
		    gensymed_symbol_3 = (SI_Long)0L;
		else if (EQ(side,Qleft))
		    gensymed_symbol_3 = (SI_Long)1L;
		else if (EQ(side,Qbottom))
		    gensymed_symbol_3 = (SI_Long)2L;
		else
		    gensymed_symbol_3 = (SI_Long)3L;
		gensymed_symbol_4 = IFIX(position_on_side) << (SI_Long)2L;
		svref_new_value_1 = gensymed_symbol_3 + gensymed_symbol_4;
		ISVREF(connection,(SI_Long)4L) = FIX(svref_new_value_1);
	    }
	    add_connection_in_block(block,connection);
	    add_subworkspace_connection_post_if_appropriate(connection,block);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    update_connection_images(Nil,gensymed_symbol,connection);
	    if (EQ(block,ISVREF(connection,(SI_Long)3L))) {
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		temp = TRUEP(ws_has_ws_representation_p(gensymed_symbol));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_2 = 
			get_or_make_connection_frame_and_activate_if_appropriate(connection);
		gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		temp_1 = gensymed_symbol;
		send_ws_representations_item_layer_change(temp_2,temp_1,
			find_connection_or_block_below_this_connection(connection,
			block));
	    }
	    gensymed_symbol = loose_end;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    gensymed_symbol_1 = Nil;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp_3 = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_3;
		temp_3 = ISVREF(gensymed_symbol,(SI_Long)14L);
		SVREF(temp_3,FIX((SI_Long)6L)) = gensymed_symbol_1;
	    }
	    delete_frame(loose_end);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* FIND-CONNECTION-OR-BLOCK-BELOW-THIS-CONNECTION */
Object find_connection_or_block_below_this_connection(connection,block)
    Object connection, block;
{
    Object c1, scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, c2, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(99,24);
    c1 = Nil;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    c2 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
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
    next_loop:
    next_loop_1:
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
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      c2 = ab_connection_;
      if (EQ(c2,connection)) {
	  if ( !TRUEP(c1)) {
	      temp = block;
	      goto end_2;
	  }
	  else {
	      temp = 
		      get_or_make_connection_frame_and_activate_if_appropriate(c1);
	      goto end_2;
	  }
      }
      c1 = c2;
      goto next_loop;
    end_loop_2:
      temp = Qnil;
    end_2:;
    POP_SPECIAL();
    if (temp);
    else
	temp = block;
    return VALUES_1(temp);
}

/* COMPUTE-SIDE-OF-EXIT */
Object compute_side_of_exit(block,loose_end,connection,
	    current_link_1_delta,current_link_2_delta,
	    loose_end_initial_orientation_horizontal_p,
	    desired_position_on_side_qm)
    Object block, loose_end, connection, current_link_1_delta;
    Object current_link_2_delta, loose_end_initial_orientation_horizontal_p;
    Object desired_position_on_side_qm;
{
    Object side, position_on_side, loose_end_delta_x_in_workspace;
    Object loose_end_delta_y_in_workspace, x_position_of_last_bend;
    Object y_position_of_last_bend, x_position_of_next_to_last_bend;
    Object y_position_of_next_to_last_bend, last_chance_qm, temp, temp_1;
    Object temp_2, temp_3, plist;
    Object result;

    x_note_fn_call(99,25);
    side = Nil;
    position_on_side = Nil;
    loose_end_delta_x_in_workspace = Nil;
    loose_end_delta_y_in_workspace = Nil;
    x_position_of_last_bend = Nil;
    y_position_of_last_bend = Nil;
    x_position_of_next_to_last_bend = Nil;
    y_position_of_next_to_last_bend = Nil;
    if (connection_completely_inside_block_p(connection,loose_end,block)) {
	result = compute_info_for_connection_inside_block(loose_end,block,
		current_link_2_delta,
		loose_end_initial_orientation_horizontal_p);
	MVS_4(result,side,position_on_side,loose_end_delta_x_in_workspace,
		loose_end_delta_y_in_workspace);
    }
    else {
	result = compute_positions_of_last_bends(loose_end,
		current_link_1_delta,current_link_2_delta,
		loose_end_initial_orientation_horizontal_p);
	MVS_4(result,x_position_of_last_bend,y_position_of_last_bend,
		x_position_of_next_to_last_bend,
		y_position_of_next_to_last_bend);
	last_chance_qm = Nil;
      next_loop:
	temp = x_position_of_last_bend;
	temp_1 = y_position_of_last_bend;
	temp_2 = x_position_of_next_to_last_bend;
	temp_3 = y_position_of_next_to_last_bend;
	plist = ISVREF(connection,(SI_Long)9L);
	result = compute_side_of_exit_given_last_bend(block,loose_end,temp,
		temp_1,temp_2,temp_3,plist ? 
		(EQ(getfq_function_no_default(plist,Qconnection_style),
		Qdiagonal) ? T : Nil) : Qnil,desired_position_on_side_qm);
	MVS_4(result,side,loose_end_delta_x_in_workspace,
		loose_end_delta_y_in_workspace,position_on_side);
	if (side)
	    goto end_1;
	else if (last_chance_qm)
	    goto end_1;
	else {
	    delete_last_bend_from_connection(connection,loose_end);
	    result = compute_stretched_links_of_connection_being_dragged(connection,
		    loose_end);
	    MVS_3(result,current_link_1_delta,current_link_2_delta,
		    loose_end_initial_orientation_horizontal_p);
	    result = compute_positions_of_last_bends(loose_end,
		    current_link_1_delta,current_link_2_delta,
		    loose_end_initial_orientation_horizontal_p);
	    MVS_4(result,x_position_of_last_bend,y_position_of_last_bend,
		    x_position_of_next_to_last_bend,
		    y_position_of_next_to_last_bend);
	    loose_end_delta_x_in_workspace = FIX((SI_Long)0L);
	    loose_end_delta_y_in_workspace = FIX((SI_Long)0L);
	    last_chance_qm = T;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_4(side,position_on_side,loose_end_delta_x_in_workspace,
	    loose_end_delta_y_in_workspace);
}

/* COMPUTE-POSITIONS-OF-LAST-BENDS */
Object compute_positions_of_last_bends(loose_end,next_to_last_link_delta,
	    last_link_delta,loose_end_initial_orientation_horizontal_p)
    Object loose_end, next_to_last_link_delta, last_link_delta;
    Object loose_end_initial_orientation_horizontal_p;
{
    Object gensymed_symbol, y_position_of_last_bend, temp;
    Object x_position_of_last_bend_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, x_position_of_last_bend;
    SI_Long y_position_of_last_bend_1;

    x_note_fn_call(99,26);
    if (loose_end_initial_orientation_horizontal_p) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(last_link_delta);
	x_position_of_last_bend = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	y_position_of_last_bend = gensymed_symbol;
	temp = FIXNUM_MINUS(y_position_of_last_bend,next_to_last_link_delta);
	return VALUES_4(FIX(x_position_of_last_bend),
		y_position_of_last_bend,FIX(x_position_of_last_bend),temp);
    }
    else {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	x_position_of_last_bend_1 = gensymed_symbol;
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(last_link_delta);
	y_position_of_last_bend_1 = gensymed_symbol_1 - gensymed_symbol_2;
	temp = FIXNUM_MINUS(x_position_of_last_bend_1,next_to_last_link_delta);
	return VALUES_4(x_position_of_last_bend_1,
		FIX(y_position_of_last_bend_1),temp,
		FIX(y_position_of_last_bend_1));
    }
}

/* LOOSE-END-WITHIN-BLOCK-P */
Object loose_end_within_block_p(block,loose_end)
    Object block, loose_end;
{
    x_note_fn_call(99,27);
    return loose_end_within_block_and_border_p(block,loose_end,
	    FIX((SI_Long)0L));
}

/* LOOSE-END-WITHIN-BLOCK-AND-BORDER-P */
Object loose_end_within_block_and_border_p(block,loose_end,border)
    Object block, loose_end, border;
{
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(99,28);
    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(border);
    if (FIXNUM_GT(temp,FIX(gensymed_symbol_1 + gensymed_symbol_2))) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(border);
	temp_1 = FIXNUM_LT(temp,FIX(gensymed_symbol_1 - gensymed_symbol_2));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(border);
	temp_1 = FIXNUM_GT(temp,FIX(gensymed_symbol_1 + gensymed_symbol_2));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(border);
	return VALUES_1(FIXNUM_LT(temp,FIX(gensymed_symbol_1 - 
		gensymed_symbol_2)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-SIDE-OF-EXIT-GIVEN-LAST-BEND */
Object compute_side_of_exit_given_last_bend(block,loose_end,
	    x_position_of_last_bend,y_position_of_last_bend,
	    x_position_of_next_to_last_bend,
	    y_position_of_next_to_last_bend,connection_diagonal_p,
	    desired_position_on_side_qm)
    Object block, loose_end, x_position_of_last_bend, y_position_of_last_bend;
    Object x_position_of_next_to_last_bend, y_position_of_next_to_last_bend;
    Object connection_diagonal_p, desired_position_on_side_qm;
{
    x_note_fn_call(99,29);
    if (connection_diagonal_p)
	return compute_side_of_exit_for_diagonal_connection(block,
		loose_end,x_position_of_next_to_last_bend,
		y_position_of_next_to_last_bend);
    else
	return compute_side_of_exit_for_orthogonal_connection(block,
		loose_end,x_position_of_last_bend,y_position_of_last_bend,
		desired_position_on_side_qm);
}

/* COMPUTE-SIDE-OF-EXIT-FOR-DIAGONAL-CONNECTION */
Object compute_side_of_exit_for_diagonal_connection(block,loose_end,
	    x_position_of_next_to_last_bend,y_position_of_next_to_last_bend)
    Object block, loose_end, x_position_of_next_to_last_bend;
    Object y_position_of_next_to_last_bend;
{
    Object intercept_qm, gensymed_symbol, temp_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(99,30);
    intercept_qm = Nil;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    if (FIXNUM_GT(x_position_of_next_to_last_bend,gensymed_symbol)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	intercept_qm = 
		compute_intercept_with_vertical_side(gensymed_symbol,block,
		loose_end,x_position_of_next_to_last_bend,
		y_position_of_next_to_last_bend);
	temp = TRUEP(intercept_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(intercept_qm);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(intercept_qm);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	return VALUES_4(Qright,temp_1,temp_2,FIX(gensymed_symbol_1 - 
		gensymed_symbol_2));
    }
    else {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	if (FIXNUM_LT(x_position_of_next_to_last_bend,gensymed_symbol)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    intercept_qm = 
		    compute_intercept_with_vertical_side(gensymed_symbol,
		    block,loose_end,x_position_of_next_to_last_bend,
		    y_position_of_next_to_last_bend);
	    temp = TRUEP(intercept_qm);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(intercept_qm);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(intercept_qm);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    return VALUES_4(Qleft,temp_1,temp_2,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	}
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    if (FIXNUM_GT(y_position_of_next_to_last_bend,gensymed_symbol)) {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		intercept_qm = 
			compute_intercept_with_horizontal_side(gensymed_symbol,
			block,loose_end,x_position_of_next_to_last_bend,
			y_position_of_next_to_last_bend);
		temp = TRUEP(intercept_qm);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		gensymed_symbol_1 = IFIX(intercept_qm);
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol_1 = IFIX(intercept_qm);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		return VALUES_4(Qbottom,temp_1,temp_2,
			FIX(gensymed_symbol_1 - gensymed_symbol_2));
	    }
	    else {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		if (FIXNUM_LT(y_position_of_next_to_last_bend,
			    gensymed_symbol)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    intercept_qm = 
			    compute_intercept_with_horizontal_side(gensymed_symbol,
			    block,loose_end,
			    x_position_of_next_to_last_bend,
			    y_position_of_next_to_last_bend);
		    temp = TRUEP(intercept_qm);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol_1 = IFIX(intercept_qm);
		    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		    gensymed_symbol_1 = IFIX(intercept_qm);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    return VALUES_4(Qtop,temp_1,temp_2,
			    FIX(gensymed_symbol_1 - gensymed_symbol_2));
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

static Object float_constant;      /* 0.0 */

/* COMPUTE-INTERCEPT-WITH-VERTICAL-SIDE */
Object compute_intercept_with_vertical_side(side_x,block,loose_end,x1,y1_1)
    Object side_x, block, loose_end, x1, y1_1;
{
    Object fx1, fy1, gensymed_symbol, fx2, fy2, fside_x, intercept_qm, temp_2;
    char temp_3;
    double temp, temp_1, delta_x, delta_y, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(99,31);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	fx1 = lfloat(x1,float_constant);
	fy1 = lfloat(y1_1,float_constant);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	fx2 = lfloat(gensymed_symbol,float_constant);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	fy2 = lfloat(gensymed_symbol,float_constant);
	temp = DOUBLE_FLOAT_TO_DOUBLE(fx2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	delta_x = temp - temp_1;
	temp = DOUBLE_FLOAT_TO_DOUBLE(fy2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
	delta_y = temp - temp_1;
	fside_x = lfloat(side_x,float_constant);
	intercept_qm = Nil;
	arg = delta_x;
	arg_1 = 0.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1));
	else {
	    arg = delta_y;
	    arg_1 = 0.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		intercept_qm = y1_1;
	    else {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fside_x);
		temp = temp_1 * delta_y / delta_x;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		temp = temp +  - (temp_1 * delta_y / delta_x);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		intercept_qm = l_round(DOUBLE_TO_DOUBLE_FLOAT(temp + 
			temp_1),_);
	    }
	}
	if (intercept_qm) {
	    temp_2 = intercept_qm;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_3 = FIXNUM_GT(temp_2,gensymed_symbol);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_2 = intercept_qm;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp_3 = FIXNUM_LT(temp_2,gensymed_symbol);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3)
	    result = VALUES_1(intercept_qm);
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* COMPUTE-INTERCEPT-WITH-HORIZONTAL-SIDE */
Object compute_intercept_with_horizontal_side(side_y,block,loose_end,x1,y1_1)
    Object side_y, block, loose_end, x1, y1_1;
{
    Object fx1, fy1, gensymed_symbol, fx2, fy2, fside_y, intercept_qm, temp_2;
    char temp_3;
    double temp, temp_1, delta_x, delta_y, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(99,32);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	fx1 = lfloat(x1,float_constant);
	fy1 = lfloat(y1_1,float_constant);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	fx2 = lfloat(gensymed_symbol,float_constant);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	fy2 = lfloat(gensymed_symbol,float_constant);
	temp = DOUBLE_FLOAT_TO_DOUBLE(fx2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	delta_x = temp - temp_1;
	temp = DOUBLE_FLOAT_TO_DOUBLE(fy2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
	delta_y = temp - temp_1;
	fside_y = lfloat(side_y,float_constant);
	intercept_qm = Nil;
	arg = delta_x;
	arg_1 = 0.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    intercept_qm = x1;
	else {
	    arg = delta_y;
	    arg_1 = 0.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1));
	    else {
		temp = DOUBLE_FLOAT_TO_DOUBLE(fside_y);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		temp = temp * delta_x / delta_y + temp_1;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		intercept_qm = l_round(DOUBLE_TO_DOUBLE_FLOAT(temp +  - 
			(temp_1 * delta_x / delta_y)),_);
	    }
	}
	if (intercept_qm) {
	    temp_2 = intercept_qm;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_3 = FIXNUM_GT(temp_2,gensymed_symbol);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_2 = intercept_qm;
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_3 = FIXNUM_LT(temp_2,gensymed_symbol);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3)
	    result = VALUES_1(intercept_qm);
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* COMPUTE-SIDE-OF-EXIT-FOR-ORTHOGONAL-CONNECTION */
Object compute_side_of_exit_for_orthogonal_connection(block,loose_end,
	    x_position_of_last_bend,y_position_of_last_bend,
	    desired_position_on_side_qm)
    Object block, loose_end, x_position_of_last_bend, y_position_of_last_bend;
    Object desired_position_on_side_qm;
{
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(99,33);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    if (FIXNUM_GT(x_position_of_last_bend,gensymed_symbol)) {
	if (desired_position_on_side_qm) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(desired_position_on_side_qm);
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    return VALUES_4(Qright,temp,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2),desired_position_on_side_qm);
	}
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(y_position_of_last_bend);
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    return VALUES_4(Qright,temp,FIX((SI_Long)0L),
		    FIX(gensymed_symbol_1 - gensymed_symbol_2));
	}
    }
    else {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	if (FIXNUM_LT(x_position_of_last_bend,gensymed_symbol)) {
	    if (desired_position_on_side_qm) {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(desired_position_on_side_qm);
		gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		return VALUES_4(Qleft,temp,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2),desired_position_on_side_qm);
	    }
	    else {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol_1 = IFIX(y_position_of_last_bend);
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		return VALUES_4(Qleft,temp,FIX((SI_Long)0L),
			FIX(gensymed_symbol_1 - gensymed_symbol_2));
	    }
	}
	else {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    if (FIXNUM_GT(y_position_of_last_bend,gensymed_symbol)) {
		if (desired_position_on_side_qm) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = IFIX(desired_position_on_side_qm);
		    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
		    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    return VALUES_4(Qbottom,temp,FIX(gensymed_symbol_1 - 
			    gensymed_symbol_2),desired_position_on_side_qm);
		}
		else {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		    gensymed_symbol_1 = IFIX(x_position_of_last_bend);
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		    return VALUES_4(Qbottom,FIX((SI_Long)0L),temp,
			    FIX(gensymed_symbol_1 - gensymed_symbol_2));
		}
	    }
	    else {
		gensymed_symbol = ISVREF(block,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		if (FIXNUM_LT(y_position_of_last_bend,gensymed_symbol)) {
		    if (desired_position_on_side_qm) {
			gensymed_symbol = ISVREF(block,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)0L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_1 = IFIX(gensymed_symbol);
			gensymed_symbol_2 = IFIX(desired_position_on_side_qm);
			gensymed_symbol_1 = gensymed_symbol_1 + 
				gensymed_symbol_2;
			gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)0L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol);
			temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
			gensymed_symbol = ISVREF(block,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_1 = IFIX(gensymed_symbol);
			gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol);
			return VALUES_4(Qtop,temp,FIX(gensymed_symbol_1 - 
				gensymed_symbol_2),
				desired_position_on_side_qm);
		    }
		    else {
			gensymed_symbol = ISVREF(block,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_1 = IFIX(gensymed_symbol);
			gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)1L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol);
			temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
			gensymed_symbol_1 = IFIX(x_position_of_last_bend);
			gensymed_symbol = ISVREF(block,(SI_Long)14L);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)0L) : 
				FIX((SI_Long)0L);
			gensymed_symbol_2 = IFIX(gensymed_symbol);
			return VALUES_4(Qtop,FIX((SI_Long)0L),temp,
				FIX(gensymed_symbol_1 - gensymed_symbol_2));
		    }
		}
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
}

/* CONNECTION-COMPLETELY-INSIDE-BLOCK-P */
Object connection_completely_inside_block_p(connection,loose_end,block)
    Object connection, loose_end, block;
{
    Object anchor_x, anchor_y, gensymed_symbol;
    char temp;
    Object result;

    x_note_fn_call(99,34);
    if ( !TRUEP(ISVREF(connection,(SI_Long)6L))) {
	result = compute_dragged_connection_anchor_point(connection,loose_end);
	MVS_2(result,anchor_x,anchor_y);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	if (FIXNUM_GE(anchor_y,gensymed_symbol)) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp = FIXNUM_LE(anchor_y,gensymed_symbol);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = FIXNUM_GE(anchor_x,gensymed_symbol);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(block,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    return VALUES_1(FIXNUM_LE(anchor_x,gensymed_symbol) ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

/* COMPUTE-INFO-FOR-CONNECTION-INSIDE-BLOCK */
Object compute_info_for_connection_inside_block(loose_end,block,
	    current_link_2_delta,loose_end_initial_orientation_horizontal_p)
    Object loose_end, block, current_link_2_delta;
    Object loose_end_initial_orientation_horizontal_p;
{
    Object closest_side, gensymed_symbol, distance_to_closest_side;
    Object side_to_try, ab_loop_list_, distance_to_side;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(99,35);
    closest_side = Qleft;
    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    distance_to_closest_side = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    side_to_try = Nil;
    ab_loop_list_ = list_constant_3;
    distance_to_side = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    side_to_try = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(side_to_try,Qtop)) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	distance_to_side = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(side_to_try,Qright)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	distance_to_side = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else if (EQ(side_to_try,Qbottom)) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	distance_to_side = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    }
    else
	distance_to_side = Qnil;
    if (FIXNUM_LT(distance_to_side,distance_to_closest_side)) {
	distance_to_closest_side = distance_to_side;
	closest_side = side_to_try;
    }
    goto next_loop;
  end_loop:;
    if (EQ(closest_side,Qleft)) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 =  
		!TRUEP(loose_end_initial_orientation_horizontal_p) ? 
		IFIX(current_link_2_delta) : (SI_Long)0L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	return VALUES_4(Qleft,FIX(gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3),FIX((SI_Long)0L),FIX((SI_Long)0L));
    }
    else if (EQ(closest_side,Qtop)) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = loose_end_initial_orientation_horizontal_p ? 
		IFIX(current_link_2_delta) : (SI_Long)0L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	return VALUES_4(Qtop,FIX(gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3),FIX((SI_Long)0L),FIX((SI_Long)0L));
    }
    else if (EQ(closest_side,Qright)) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 =  
		!TRUEP(loose_end_initial_orientation_horizontal_p) ? 
		IFIX(current_link_2_delta) : (SI_Long)0L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	return VALUES_4(Qright,FIX(gensymed_symbol_1 - gensymed_symbol_2 - 
		gensymed_symbol_3),FIX((SI_Long)0L),FIX((SI_Long)0L));
    }
    else if (EQ(closest_side,Qbottom)) {
	gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = loose_end_initial_orientation_horizontal_p ? 
		IFIX(current_link_2_delta) : (SI_Long)0L;
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	return VALUES_4(Qbottom,FIX(gensymed_symbol_1 - gensymed_symbol_2 
		- gensymed_symbol_3),FIX((SI_Long)0L),FIX((SI_Long)0L));
    }
    else
	return VALUES_1(Qnil);
}

/* SIDE-OF-JUNCTION-HAS-CONNECTION-P */
Object side_of_junction_has_connection_p(junction,side)
    Object junction, side;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(99,36);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(junction,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
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
    next_loop:
    next_loop_1:
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
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if (EQ(ISVREF(connection,(SI_Long)3L),junction)) {
	  if (EQ(ISVREF(array_constant,IFIX(ISVREF(connection,
		  (SI_Long)5L)) & (SI_Long)3L),side)) {
	      result = VALUES_1(T);
	      goto end_2;
	  }
      }
      else if (EQ(ISVREF(array_constant,IFIX(ISVREF(connection,
	      (SI_Long)4L)) & (SI_Long)3L),side)) {
	  result = VALUES_1(T);
	  goto end_2;
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object string_constant;     /* "Can't join connections with incompatible cross sections" */

static Object string_constant_1;   /* "Can't join directed and non-directed connections!" */

static Object string_constant_2;   /* "Can't join directed connections with opposing directions!" */

/* JOIN-TWO-CONNECTIONS */
Object join_two_connections(loose_end_1,loose_end_2)
    Object loose_end_1, loose_end_2;
{
    Object connection_1, connection_1_fixed_end_block, connection_2;
    Object connection_2_fixed_end_block;
    Object directionality_or_cross_section_problem_p, gensymed_symbol_1;
    Object temp_1, temp_2, connection_item_table_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp_3, svref_arg_2, gensymed_symbol_2;
    Object slot_group_qm, connection_2_frame_or_class, fsn, xa, ya;
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(99,37);
    connection_1 = get_connection_for_loose_end(loose_end_1);
    connection_1_fixed_end_block = 
	    get_block_at_other_end_of_connection(connection_1,loose_end_1);
    connection_2 = get_connection_for_loose_end(loose_end_2);
    connection_2_fixed_end_block = 
	    get_block_at_other_end_of_connection(connection_2,loose_end_2);
    if ( 
	    !TRUEP(connection_cross_section_patterns_compatible_qm(connection_1,
	    connection_2))) {
	notify_user(1,string_constant);
	directionality_or_cross_section_problem_p = T;
    }
    else
	directionality_or_cross_section_problem_p = Nil;
    if (directionality_or_cross_section_problem_p);
    else if ((SI_Long)0L != (IFIX(ISVREF(connection_1,(SI_Long)7L)) & 
	    (SI_Long)1L) && (SI_Long)0L != (IFIX(ISVREF(connection_2,
	    (SI_Long)7L)) & (SI_Long)1L))
	directionality_or_cross_section_problem_p = Nil;
    else if ((SI_Long)0L != (IFIX(ISVREF(connection_1,(SI_Long)7L)) & 
	    (SI_Long)1L) || (SI_Long)0L != (IFIX(ISVREF(connection_2,
	    (SI_Long)7L)) & (SI_Long)1L)) {
	notify_user(1,string_constant_1);
	directionality_or_cross_section_problem_p = T;
    }
    else if (EQ(connection_1_fixed_end_block,ISVREF(connection_1,
	    (SI_Long)3L)) && EQ(connection_2_fixed_end_block,
	    ISVREF(connection_2,(SI_Long)3L)) || 
	    EQ(connection_1_fixed_end_block,ISVREF(connection_1,
	    (SI_Long)2L)) && EQ(connection_2_fixed_end_block,
	    ISVREF(connection_2,(SI_Long)2L))) {
	notify_user(1,string_constant_2);
	directionality_or_cross_section_problem_p = T;
    }
    else
	directionality_or_cross_section_problem_p = Qnil;
    if ( !TRUEP(directionality_or_cross_section_problem_p)) {
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection_1,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection_1);
	note_deletion_of_connection(connection_2);
	update_images_of_block(loose_end_1,T,Nil);
	update_images_of_block(loose_end_2,T,Nil);
	if (EQ(ISVREF(connection_1,(SI_Long)2L),loose_end_1)) {
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_1,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) : Nil;
	    update_connection_images(T,gensymed_symbol_1,connection_1);
	}
	if (EQ(ISVREF(connection_2,(SI_Long)2L),loose_end_2)) {
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_2,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) : Nil;
	    update_connection_images(T,gensymed_symbol_1,connection_2);
	}
	adjust_deltas_of_connections_to_be_joined(connection_1,loose_end_1,
		connection_2,loose_end_2);
	if (G2_has_v5_mode_windows_p)
	    send_ws_representations_connection_moved(connection_1);
	replace_connection_in_block(connection_2_fixed_end_block,
		connection_2,connection_1);
	if (G2_has_v5_mode_windows_p) {
	    temp_1 = 
		    get_or_make_connection_frame_and_activate_if_appropriate(connection_1);
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(ISVREF(connection_1,
		    (SI_Long)3L),(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) : Nil;
	    temp_2 = gensymed_symbol_1;
	    send_ws_representations_item_layer_change(temp_1,temp_2,
		    find_connection_or_block_below_this_connection(connection_1,
		    ISVREF(connection_1,(SI_Long)3L)));
	}
	gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_1,(SI_Long)14L));
	gensymed_symbol_1 = gensymed_symbol_1 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	if (gensymed_symbol_1) {
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_1,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	    connection_item_table_skip_list = gensymed_symbol_1;
	    head = M_CAR(M_CDR(connection_item_table_skip_list));
	    tail = M_CDR(M_CDR(connection_item_table_skip_list));
	    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
		    (SI_Long)0L));
	    if ( !EQ(element_qm,tail))
		reclaim_connection_item_table_nodes(element_qm,tail);
	    reclaim_skip_list_element(head);
	    reclaim_skip_list_element(tail);
	    M_CDDR(connection_item_table_skip_list) = Nil;
	    M_CADR(connection_item_table_skip_list) = Nil;
	    M_CAR(connection_item_table_skip_list) = Nil;
	    if (connection_item_table_skip_list) {
		last_1 = connection_item_table_skip_list;
		next_qm = Nil;
	      next_loop:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop;
		inline_note_reclaim_cons(last_1,Qlookup);
		last_1 = next_qm;
		goto next_loop;
	      end_loop:
		inline_note_reclaim_cons(last_1,Qlookup);
		if (ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_3 = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_3) = connection_item_table_skip_list;
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = last_1;
		}
		else {
		    temp_3 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = 
			    connection_item_table_skip_list;
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    gensymed_symbol_1 = loose_end_1;
	    gensymed_symbol_2 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol_1,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol_1,
			Qslot_group_for_block_qm);
	    gensymed_symbol_2 = Nil;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_2;
	    else if ( !EQ(gensymed_symbol_2,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol_1,
			    Qslot_group_for_block_qm);
		temp_3 = make_icon_slot_group_1();
		SVREF(gensymed_symbol_1,FIX((SI_Long)14L)) = temp_3;
		temp_3 = ISVREF(gensymed_symbol_1,(SI_Long)14L);
		SVREF(temp_3,FIX((SI_Long)6L)) = gensymed_symbol_2;
	    }
	}
	gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_2,(SI_Long)14L));
	gensymed_symbol_1 = gensymed_symbol_1 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	if (gensymed_symbol_1) {
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(loose_end_2,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	    connection_item_table_skip_list = gensymed_symbol_1;
	    head = M_CAR(M_CDR(connection_item_table_skip_list));
	    tail = M_CDR(M_CDR(connection_item_table_skip_list));
	    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
		    (SI_Long)0L));
	    if ( !EQ(element_qm,tail))
		reclaim_connection_item_table_nodes(element_qm,tail);
	    reclaim_skip_list_element(head);
	    reclaim_skip_list_element(tail);
	    M_CDDR(connection_item_table_skip_list) = Nil;
	    M_CADR(connection_item_table_skip_list) = Nil;
	    M_CAR(connection_item_table_skip_list) = Nil;
	    if (connection_item_table_skip_list) {
		last_1 = connection_item_table_skip_list;
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
		    temp_3 = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_3) = connection_item_table_skip_list;
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = last_1;
		}
		else {
		    temp_3 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = 
			    connection_item_table_skip_list;
		    temp_3 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    gensymed_symbol_1 = loose_end_2;
	    gensymed_symbol_2 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol_1,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol_1,
			Qslot_group_for_block_qm);
	    gensymed_symbol_2 = Nil;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_2;
	    else if ( !EQ(gensymed_symbol_2,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol_1,
			    Qslot_group_for_block_qm);
		temp_3 = make_icon_slot_group_1();
		SVREF(gensymed_symbol_1,FIX((SI_Long)14L)) = temp_3;
		temp_3 = ISVREF(gensymed_symbol_1,(SI_Long)14L);
		SVREF(temp_3,FIX((SI_Long)6L)) = gensymed_symbol_2;
	    }
	}
	connection_2_frame_or_class = ISVREF(connection_2,(SI_Long)1L);
	fsn =  !SYMBOLP(connection_2_frame_or_class) ? 
		copy_frame_serial_number(ISVREF(connection_2_frame_or_class,
		(SI_Long)3L)) : Nil;
	if (fsn)
	    delete_frame(connection_2_frame_or_class);
	if (fsn) {
	    gensymed_symbol_1 = ISVREF(connection_2_frame_or_class,
		    (SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(connection_2_frame_or_class) ? 
		    EQ(ISVREF(connection_2_frame_or_class,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol_1) ? 
			IFIX(gensymed_symbol_1) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(fsn))
		temp = FIXNUMP(gensymed_symbol_1) ? FIXNUM_LT(fsn,
			gensymed_symbol_1) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_1))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(fsn);
		ya = M_CAR(gensymed_symbol_1);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			    M_CDR(gensymed_symbol_1)) : TRUEP(Qnil);
	    }
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    reclaim_connection_and_delta_or_deltas(connection_2,Nil);
	    delete_frame(loose_end_2);
	}
	reclaim_frame_serial_number(fsn);
	delete_frame(loose_end_1);
	if ((SI_Long)0L != (IFIX(ISVREF(connection_2_fixed_end_block,
		(SI_Long)5L)) & (SI_Long)2048L))
	    recompute_external_connections_for_dragging_states(connection_2_fixed_end_block);
	gensymed_symbol_1 = 
		ACCESS_ONCE(ISVREF(connection_1_fixed_end_block,(SI_Long)14L));
	gensymed_symbol_1 = gensymed_symbol_1 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)5L)) : Nil;
	update_connection_images(Nil,gensymed_symbol_1,connection_1);
    }
    return VALUES_2( !TRUEP(directionality_or_cross_section_problem_p) ? T 
	    : Nil,connection_1);
}

/* RECLAIM-CONNECTION-AND-DELTA-OR-DELTAS */
Object reclaim_connection_and_delta_or_deltas(connection,
	    delete_dangling_connection_posts_qm)
    Object connection, delete_dangling_connection_posts_qm;
{
    Object delta_or_deltas, old, svref_new_value;
    SI_Long gensymed_symbol, new_1;
    char temp;

    x_note_fn_call(99,38);
    update_runtime_structures_according_to_edit(1,connection);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    if (CONSP(delta_or_deltas)) {
	reclaim_slot_value_list_1(delta_or_deltas);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = Nil;
    }
    flush_subworkspace_connection_posts(connection,Nil,
	    delete_dangling_connection_posts_qm);
    reclaim_slot_value(ISVREF(connection,(SI_Long)9L));
    old = ISVREF(connection,(SI_Long)10L);
    new_1 = (SI_Long)-1L;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
	    (FIXNUMP(FIX(new_1)) ||  !TRUEP(FIX(new_1))) ? FIX(new_1) : 
	    frame_serial_number_setf_helper_1(old,FIX(new_1));
    SVREF(connection,FIX((SI_Long)10L)) = svref_new_value;
    return reclaim_connection_1(connection);
}

/* CONNECTION-CROSS-SECTION-PATTERNS-COMPATIBLE? */
Object connection_cross_section_patterns_compatible_qm(connection_1,
	    connection_2)
    Object connection_1, connection_2;
{
    Object connection_1_connection_frame_or_class, x2;
    Object connection_1_cross_section_pattern, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, connection_2_connection_frame_or_class;
    Object connection_2_cross_section_pattern;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(99,39);
    connection_1_connection_frame_or_class = ISVREF(connection_1,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_1_connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_1_connection_frame_or_class)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(connection_1_connection_frame_or_class,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_1_connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	connection_1_cross_section_pattern = 
		ISVREF(connection_1_connection_frame_or_class,(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_1_connection_frame_or_class,
		Class_description_gkbprop)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = connection_1_connection_frame_or_class;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(connection_1_connection_frame_or_class) 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_1:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = connection_1_connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	connection_1_cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    connection_2_connection_frame_or_class = ISVREF(connection_2,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_2_connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_2_connection_frame_or_class)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(connection_2_connection_frame_or_class,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_2_connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	connection_2_cross_section_pattern = 
		ISVREF(connection_2_connection_frame_or_class,(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_2_connection_frame_or_class,
		Class_description_gkbprop)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = connection_2_connection_frame_or_class;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(connection_2_connection_frame_or_class) 
		    & IFIX(Most_positive_fixnum);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		gensymed_symbol = connection_2_connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
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
	    temp_2 = 
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
	  next_loop_36:
	    if (level < ab_loop_bind_)
		goto end_loop_36;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_37:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_38:
	    if ( !TRUEP(marked))
		goto end_loop_37;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_38;
	  end_loop_37:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_13;
	    goto next_loop_37;
	  end_loop_38:
	  end_13:
	    level = level - (SI_Long)1L;
	    goto next_loop_36;
	  end_loop_36:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	  next_loop_39:
	    if (level < ab_loop_bind_)
		goto end_loop_39;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_40:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_41:
	    if ( !TRUEP(marked))
		goto end_loop_40;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_41;
	  end_loop_40:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_14;
	    goto next_loop_40;
	  end_loop_41:
	  end_14:
	    level = level - (SI_Long)1L;
	    goto next_loop_39;
	  end_loop_39:;
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
	      next_loop_42:
		if (level < ab_loop_bind_)
		    goto end_loop_42;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_43:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_44:
		if ( !TRUEP(marked))
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_44;
	      end_loop_43:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_15;
		goto next_loop_43;
	      end_loop_44:
	      end_15:
		level = level - (SI_Long)1L;
		goto next_loop_42;
	      end_loop_42:;
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
	      next_loop_45:
		if (level < ab_loop_bind_)
		    goto end_loop_45;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_46:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_47:
		if ( !TRUEP(marked))
		    goto end_loop_46;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_47;
	      end_loop_46:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_16;
		goto next_loop_46;
	      end_loop_47:
	      end_16:
		level = level - (SI_Long)1L;
		goto next_loop_45;
	      end_loop_45:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	connection_2_cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    temp_2 = CAAR(connection_1_cross_section_pattern);
    temp_1 = CONSP(temp_2) ? CDR(connection_1_cross_section_pattern) : 
	    connection_1_cross_section_pattern;
    temp_2 = CAAR(connection_2_cross_section_pattern);
    temp_2 = CONSP(temp_2) ? CDR(connection_2_cross_section_pattern) : 
	    connection_2_cross_section_pattern;
    return VALUES_1(EQUAL(temp_1,temp_2) ? T : Nil);
}

/* SMALL-LINK-DELTA-P */
Object small_link_delta_p(delta)
    Object delta;
{
    x_note_fn_call(99,40);
    if (Called_within_clear_text_loading) {
	if ((SI_Long)-2L <= IFIX(delta))
	    return VALUES_1(IFIX(delta) <= (SI_Long)2L ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(IFIX(delta) == (SI_Long)0L ? T : Nil);
}

/* ADJUST-DELTAS-OF-CONNECTIONS-TO-BE-JOINED */
Object adjust_deltas_of_connections_to_be_joined(connection_1,loose_end_1,
	    connection_2,loose_end_2)
    Object connection_1, loose_end_1, connection_2, loose_end_2;
{
    Object connection_1_delta_or_deltas, connection_2_delta_or_deltas;
    Object connection_2_fixed_end_block, loose_end_orientations_same_p_1;
    Object plist, connection_being_dragged_diagonal_p;
    Object absorb_link_when_joining_qm_1;
    Object reverse_connection_delta_pairs_for_output_connection_qm_1;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, link_1_delta;
    Object link_2_delta, new_last_deltas, temp_1, rest_of_connection_1_deltas;
    Object deltas_to_be_added_to_connection_1, temp_2, temp1, rest_of_deltas;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long svref_new_value;
    char temp;
    Object result;

    x_note_fn_call(99,41);
    connection_1_delta_or_deltas = ISVREF(connection_1,(SI_Long)6L);
    connection_2_delta_or_deltas = ISVREF(connection_2,(SI_Long)6L);
    connection_2_fixed_end_block = 
	    get_block_at_other_end_of_connection(connection_2,loose_end_2);
    loose_end_orientations_same_p_1 = 
	    loose_end_orientations_same_p(connection_1,loose_end_1,
	    connection_2,loose_end_2);
    plist = ISVREF(connection_1,(SI_Long)9L);
    connection_being_dragged_diagonal_p = plist ? 
	    (EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal) ? T : Nil) : Qnil;
    absorb_link_when_joining_qm_1 = Nil;
    reverse_connection_delta_pairs_for_output_connection_qm_1 = Nil;
    connection_2_delta_or_deltas = 
	    add_missing_deltas_to_connection(connection_2);
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end_1,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
    gensymed_symbol_1 = loose_end_1;
    gensymed_symbol_2 = ISVREF(loose_end_2,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
    gensymed_symbol_2 = ISVREF(loose_end_1,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_2 = ISVREF(loose_end_2,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
    gensymed_symbol_2 = ISVREF(loose_end_1,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_5 = IFIX(gensymed_symbol_2);
    gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    FIX(gensymed_symbol_3),FIX(gensymed_symbol_4));
    result = compute_stretched_links_of_connection_being_dragged(connection_1,
	    loose_end_1);
    MVS_2(result,link_1_delta,link_2_delta);
    if (EQ(ISVREF(connection_1,(SI_Long)2L),loose_end_1)) {
	new_last_deltas = Nil;
	if (small_link_delta_p(link_2_delta)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection_1,(SI_Long)7L)) 
			& (SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection_1);
	    temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection_1,
		    (SI_Long)4L)) & (SI_Long)3L);
	    temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? Qtop : Qleft;
	    if (EQ(temp_1,Qtop))
		gensymed_symbol_3 = (SI_Long)0L;
	    else if (EQ(temp_1,Qleft))
		gensymed_symbol_3 = (SI_Long)1L;
	    else if (EQ(temp_1,Qbottom))
		gensymed_symbol_3 = (SI_Long)2L;
	    else
		gensymed_symbol_3 = (SI_Long)3L;
	    gensymed_symbol_4 = (SI_Long)0L;
	    svref_new_value = gensymed_symbol_3 + gensymed_symbol_4;
	    ISVREF(connection_1,(SI_Long)4L) = FIX(svref_new_value);
	    loose_end_orientations_same_p_1 = 
		    loose_end_orientations_same_p(connection_1,loose_end_1,
		    connection_2,loose_end_2);
	    new_last_deltas = slot_value_cons_1(link_1_delta,Nil);
	}
	else
	    new_last_deltas = slot_value_list_2(link_1_delta,link_2_delta);
	if ( !TRUEP(connection_1_delta_or_deltas))
	    connection_1_delta_or_deltas = new_last_deltas;
	else if (ATOM(connection_1_delta_or_deltas))
	    connection_1_delta_or_deltas = 
		    slot_value_cons_1(connection_1_delta_or_deltas,
		    new_last_deltas);
	else
	    connection_1_delta_or_deltas = 
		    nconc2(connection_1_delta_or_deltas,new_last_deltas);
	absorb_link_when_joining_qm_1 = 
		absorb_link_when_joining_qm(loose_end_orientations_same_p_1,
		connection_being_dragged_diagonal_p,
		FIXNUM_ODDP(length(connection_1_delta_or_deltas)) ? T : 
		Nil,IFIX(length(connection_2_delta_or_deltas)) == 
		(SI_Long)1L ? T : Nil);
	reverse_connection_delta_pairs_for_output_connection_qm_1 = 
		reverse_connection_delta_pairs_for_output_connection_qm(connection_being_dragged_diagonal_p,
		loose_end_orientations_same_p_1,absorb_link_when_joining_qm_1);
	rest_of_connection_1_deltas = connection_1_delta_or_deltas;
      next_loop:
	if ( !TRUEP(rest_of_connection_1_deltas))
	    goto end_loop;
	if ( !TRUEP(CDR(rest_of_connection_1_deltas)))
	    goto end_loop;
	rest_of_connection_1_deltas = M_CDR(rest_of_connection_1_deltas);
	goto next_loop;
      end_loop:
	deltas_to_be_added_to_connection_1 = EQ(ISVREF(connection_2,
		(SI_Long)3L),loose_end_2) ? 
		(reverse_connection_delta_pairs_for_output_connection_qm_1 
		? 
		reverse_connection_delta_pairs(connection_2_delta_or_deltas) 
		: 
		copy_list_using_slot_value_conses_1(connection_2_delta_or_deltas)) 
		: invert_connection_deltas(connection_2_delta_or_deltas,
		reverse_connection_delta_pairs_for_output_connection_qm_1);
	if (absorb_link_when_joining_qm_1) {
	    temp_2 = FIXNUM_ADD(CAR(rest_of_connection_1_deltas),
		    CAR(deltas_to_be_added_to_connection_1));
	    M_CAR(rest_of_connection_1_deltas) = temp_2;
	    temp_2 = CDR(deltas_to_be_added_to_connection_1);
	    M_CDR(rest_of_connection_1_deltas) = temp_2;
	    reclaim_slot_value_cons_1(deltas_to_be_added_to_connection_1);
	}
	else
	    M_CDR(rest_of_connection_1_deltas) = 
		    deltas_to_be_added_to_connection_1;
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_3 = IFIX(ISVREF(connection_1,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection_1);
	SVREF(connection_1,FIX((SI_Long)6L)) = connection_1_delta_or_deltas;
	set_output_end_of_connection_1(connection_1,
		connection_2_fixed_end_block,
		get_position_at_this_end_of_connection(connection_2,
		connection_2_fixed_end_block));
    }
    else {
	connection_1_delta_or_deltas = 
		add_missing_deltas_to_connection(connection_1);
	link_1_delta = FIXNUM_NEGATE(link_1_delta);
	link_2_delta = FIXNUM_NEGATE(link_2_delta);
	if (small_link_delta_p(link_2_delta)) {
	    temp = TRUEP(Noting_changes_to_kb_p);
	    if (temp);
	    else {
		gensymed_symbol_3 = IFIX(ISVREF(connection_1,(SI_Long)7L)) 
			& (SI_Long)128L;
		temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp)
		note_change_to_connection_1(connection_1);
	    temp_1 = ISVREF(array_constant,IFIX(ISVREF(connection_1,
		    (SI_Long)5L)) & (SI_Long)3L);
	    temp_1 = EQ(temp_1,Qleft) || EQ(temp_1,Qright) ? Qtop : Qleft;
	    if (EQ(temp_1,Qtop))
		gensymed_symbol_3 = (SI_Long)0L;
	    else if (EQ(temp_1,Qleft))
		gensymed_symbol_3 = (SI_Long)1L;
	    else if (EQ(temp_1,Qbottom))
		gensymed_symbol_3 = (SI_Long)2L;
	    else
		gensymed_symbol_3 = (SI_Long)3L;
	    gensymed_symbol_4 = (SI_Long)0L;
	    svref_new_value = gensymed_symbol_3 + gensymed_symbol_4;
	    ISVREF(connection_1,(SI_Long)5L) = FIX(svref_new_value);
	    loose_end_orientations_same_p_1 = 
		    loose_end_orientations_same_p(connection_1,loose_end_1,
		    connection_2,loose_end_2);
	    connection_1_delta_or_deltas = slot_value_cons_1(link_1_delta,
		    CDR(connection_1_delta_or_deltas) ? 
		    CDDR(connection_1_delta_or_deltas) : Nil);
	}
	else
	    connection_1_delta_or_deltas = slot_value_cons_1(link_2_delta,
		    slot_value_cons_1(link_1_delta,
		    CDR(connection_1_delta_or_deltas) ? 
		    CDDR(connection_1_delta_or_deltas) : Nil));
	absorb_link_when_joining_qm_1 = 
		absorb_link_when_joining_qm(loose_end_orientations_same_p_1,
		connection_being_dragged_diagonal_p,
		FIXNUM_ODDP(length(connection_2_delta_or_deltas)) ? T : 
		Nil,Nil);
	if (reverse_connection_delta_pairs_for_output_connection_qm(connection_being_dragged_diagonal_p,
		loose_end_orientations_same_p_1,
		    absorb_link_when_joining_qm_1)) {
	    temp1 = 
		    reverse_connection_delta_pairs(connection_1_delta_or_deltas);
	    reclaim_slot_value_list_1(connection_1_delta_or_deltas);
	    connection_1_delta_or_deltas = temp1;
	}
	deltas_to_be_added_to_connection_1 = EQ(ISVREF(connection_2,
		(SI_Long)3L),loose_end_2) ? 
		invert_connection_deltas(connection_2_delta_or_deltas,Nil) 
		: 
		copy_list_using_slot_value_conses_1(connection_2_delta_or_deltas);
	rest_of_deltas = deltas_to_be_added_to_connection_1;
      next_loop_1:
	if ( !TRUEP(rest_of_deltas))
	    goto end_loop_1;
	if ( !TRUEP(CDR(rest_of_deltas)))
	    goto end_loop_1;
	rest_of_deltas = M_CDR(rest_of_deltas);
	goto next_loop_1;
      end_loop_1:
	if (absorb_link_when_joining_qm_1) {
	    temp_2 = FIXNUM_ADD(CAR(rest_of_deltas),
		    CAR(connection_1_delta_or_deltas));
	    M_CAR(rest_of_deltas) = temp_2;
	    temp_2 = CDR(connection_1_delta_or_deltas);
	    M_CDR(rest_of_deltas) = temp_2;
	    reclaim_slot_value_cons_1(connection_1_delta_or_deltas);
	}
	else
	    M_CDR(rest_of_deltas) = connection_1_delta_or_deltas;
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_3 = IFIX(ISVREF(connection_1,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection_1);
	SVREF(connection_1,FIX((SI_Long)6L)) = 
		deltas_to_be_added_to_connection_1;
	set_input_end_of_connection_1(connection_1,
		connection_2_fixed_end_block,
		get_position_at_this_end_of_connection(connection_2,
		connection_2_fixed_end_block));
    }
    return remove_redundant_deltas_from_connection(connection_1);
}

/* LOOSE-END-ORIENTATIONS-SAME-P */
Object loose_end_orientations_same_p(connection_1,loose_end_1,connection_2,
	    loose_end_2)
    Object connection_1, loose_end_1, connection_2, loose_end_2;
{
    Object loose_end_1_end_position, loose_end_1_end_side;
    Object loose_end_1_initial_orientation_horizontal_p;
    Object loose_end_2_end_position, loose_end_2_end_side;
    Object loose_end_2_initial_orientation_horizontal_p, temp;

    x_note_fn_call(99,42);
    loose_end_1_end_position = 
	    get_position_at_this_end_of_connection(connection_1,loose_end_1);
    loose_end_1_end_side = ISVREF(array_constant,
	    IFIX(loose_end_1_end_position) & (SI_Long)3L);
    loose_end_1_initial_orientation_horizontal_p = 
	    memq_function(loose_end_1_end_side,list_constant_2);
    loose_end_2_end_position = 
	    get_position_at_this_end_of_connection(connection_2,loose_end_2);
    loose_end_2_end_side = ISVREF(array_constant,
	    IFIX(loose_end_2_end_position) & (SI_Long)3L);
    loose_end_2_initial_orientation_horizontal_p = 
	    memq_function(loose_end_2_end_side,list_constant_2);
    temp = loose_end_1_initial_orientation_horizontal_p ? 
	    loose_end_2_initial_orientation_horizontal_p : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if ( !TRUEP(loose_end_1_initial_orientation_horizontal_p))
	return VALUES_1( 
		!TRUEP(loose_end_2_initial_orientation_horizontal_p) ? T : 
		Nil);
    else
	return VALUES_1(Nil);
}

/* ABSORB-LINK-WHEN-JOINING? */
Object absorb_link_when_joining_qm(loose_end_orientations_same_p_1,
	    connection_being_dragged_diagonal_p,
	    input_connection_has_odd_number_of_deltas_p,
	    output_connection_is_stub_p)
    Object loose_end_orientations_same_p_1;
    Object connection_being_dragged_diagonal_p;
    Object input_connection_has_odd_number_of_deltas_p;
    Object output_connection_is_stub_p;
{
    Object temp;

    x_note_fn_call(99,43);
    if (connection_being_dragged_diagonal_p) {
	temp = input_connection_has_odd_number_of_deltas_p;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(output_connection_is_stub_p);
    }
    else
	return VALUES_1(loose_end_orientations_same_p_1);
}

/* REVERSE-CONNECTION-DELTA-PAIRS-FOR-OUTPUT-CONNECTION? */
Object reverse_connection_delta_pairs_for_output_connection_qm(connection_being_dragged_diagonal_p,
	    loose_end_orientations_same_p_1,absorb_link_when_joining_qm_1)
    Object connection_being_dragged_diagonal_p;
    Object loose_end_orientations_same_p_1, absorb_link_when_joining_qm_1;
{
    x_note_fn_call(99,44);
    if (connection_being_dragged_diagonal_p) {
	if (absorb_link_when_joining_qm_1)
	    return VALUES_1( !TRUEP(loose_end_orientations_same_p_1) ? T : 
		    Nil);
	else
	    return VALUES_1(loose_end_orientations_same_p_1);
    }
    else
	return VALUES_1(Nil);
}

/* INVERT-CONNECTION-DELTAS */
Object invert_connection_deltas(deltas,reverse_delta_pairs_qm)
    Object deltas, reverse_delta_pairs_qm;
{
    Object temp1, inverted_deltas;

    x_note_fn_call(99,45);
    if (reverse_delta_pairs_qm) {
	temp1 = reverse_connection_delta_pairs(deltas);
	inverted_deltas = invert_connection_deltas_1(temp1);
	reclaim_slot_value_list_1(temp1);
	return VALUES_1(inverted_deltas);
    }
    else
	return invert_connection_deltas_1(deltas);
}

/* INVERT-CONNECTION-DELTAS-1 */
Object invert_connection_deltas_1(deltas)
    Object deltas;
{
    Object processed_deltas, delta, ab_loop_list_;

    x_note_fn_call(99,46);
    processed_deltas = Nil;
    delta = Nil;
    ab_loop_list_ = deltas;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    delta = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    processed_deltas = slot_value_cons_1(FIXNUM_NEGATE(delta),
	    processed_deltas);
    goto next_loop;
  end_loop:
    return VALUES_1(processed_deltas);
    return VALUES_1(Qnil);
}

/* REVERSE-CONNECTION-DELTA-PAIRS */
Object reverse_connection_delta_pairs(deltas)
    Object deltas;
{
    Object processed_deltas, processed_deltas_tail, list_to_add, tail_of_list;
    Object rest_of_deltas, first_delta, second_delta;

    x_note_fn_call(99,47);
    processed_deltas = Nil;
    processed_deltas_tail = Nil;
    list_to_add = Nil;
    tail_of_list = Nil;
    rest_of_deltas = deltas;
    first_delta = Nil;
    second_delta = Nil;
  next_loop:
    first_delta = FIRST(rest_of_deltas);
    second_delta = SECOND(rest_of_deltas);
    if ( !TRUEP(rest_of_deltas))
	goto end_loop;
    if (second_delta) {
	list_to_add = slot_value_list_2(second_delta,first_delta);
	tail_of_list = CDR(list_to_add);
    }
    else {
	list_to_add = slot_value_cons_1(first_delta,Nil);
	tail_of_list = list_to_add;
    }
    if ( !TRUEP(processed_deltas))
	processed_deltas = list_to_add;
    else
	M_CDR(processed_deltas_tail) = list_to_add;
    processed_deltas_tail = tail_of_list;
    rest_of_deltas = CDDR(rest_of_deltas);
    goto next_loop;
  end_loop:
    return VALUES_1(processed_deltas);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_procedure_qm, Qconnection_handling_procedure_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_procedure_fsn_qm, Qconnection_handling_procedure_fsn_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_connection_queue, Qconnection_handling_connection_queue);

/* RECLAIM-SLOT-VALUE-FSN-QUEUE */
Object reclaim_slot_value_fsn_queue(queue)
    Object queue;
{
    Object fsn, ab_loop_list_;

    x_note_fn_call(99,48);
    fsn = Nil;
    ab_loop_list_ = queue;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    fsn = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(fsn);
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_list_1(queue);
}

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_fsn_queue, Qconnection_handling_fsn_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_window_queue, Qconnection_handling_window_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_connection_type_queue, Qconnection_handling_connection_type_queue);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_handling_block_queue, Qconnection_handling_block_queue);

/* G2-REGISTER-CONNECTION-HANDLING-PROCEDURE */
Object g2_register_connection_handling_procedure(procedure)
    Object procedure;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object frame_serial_number_setf_arg;
    Object connection_handling_procedure_fsn_qm_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(99,49);
    if (SIMPLE_VECTOR_P(procedure) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure)) > (SI_Long)2L &&  
	    !EQ(ISVREF(procedure,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(procedure,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
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
	    temp = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Connection_handling_procedure_qm = procedure;
	frame_serial_number_setf_arg = ISVREF(procedure,(SI_Long)3L);
	connection_handling_procedure_fsn_qm_new_value = 
		(FIXNUMP(Connection_handling_procedure_fsn_qm) ||  
		!TRUEP(Connection_handling_procedure_fsn_qm)) && 
		(FIXNUMP(frame_serial_number_setf_arg) ||  
		!TRUEP(frame_serial_number_setf_arg)) ? 
		frame_serial_number_setf_arg : 
		frame_serial_number_setf_helper_1(Connection_handling_procedure_fsn_qm,
		frame_serial_number_setf_arg);
	Connection_handling_procedure_fsn_qm = 
		connection_handling_procedure_fsn_qm_new_value;
	return make_evaluation_truth_value_function(Truth);
    }
    else {
	Connection_handling_procedure_qm = Nil;
	return make_evaluation_truth_value_function(Falsity);
    }
}

static Object Qab_slot_value;      /* slot-value */

/* G2-GET-CONNECTION-TO-HANDLE */
Object g2_get_connection_to_handle()
{
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2, frame;
    Object fsn, gensymed_symbol, xa, ya, temp_2, temp_3, temp_4, temp_5;
    char temp_1;

    x_note_fn_call(99,50);
    slot_value_pop_store = Nil;
    cons_1 = Connection_handling_connection_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Connection_handling_connection_queue = next_cons;
    frame = slot_value_pop_store;
    slot_value_pop_store = Nil;
    cons_1 = Connection_handling_fsn_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Connection_handling_fsn_queue = next_cons;
    fsn = slot_value_pop_store;
    if (frame) {
	gensymed_symbol = ISVREF(frame,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else if (FIXNUMP(fsn))
	    temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? TRUEP(serve_item_p(frame)) : TRUEP(Nil)) {
	reclaim_frame_serial_number(fsn);
	temp_2 = frame;
    }
    else {
	reclaim_frame_serial_number(fsn);
	temp_2 = make_evaluation_truth_value_function(Falsity);
    }
    slot_value_pop_store = Nil;
    cons_1 = Connection_handling_window_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Connection_handling_window_queue = next_cons;
    temp_3 = slot_value_pop_store;
    slot_value_pop_store = Nil;
    cons_1 = Connection_handling_connection_type_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Connection_handling_connection_type_queue = next_cons;
    temp_4 = slot_value_pop_store;
    slot_value_pop_store = Nil;
    cons_1 = Connection_handling_block_queue;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Connection_handling_block_queue = next_cons;
    temp_5 = slot_value_pop_store;
    if (temp_5);
    else
	temp_5 = make_evaluation_truth_value_function(Falsity);
    return VALUES_4(temp_2,temp_3,temp_4,temp_5);
}

/* G2-MORE-CONNECTIONS-TO-BE-HANDLED */
Object g2_more_connections_to_be_handled()
{
    x_note_fn_call(99,51);
    if (Connection_handling_connection_queue)
	return make_evaluation_truth_value_function(Truth);
    else
	return make_evaluation_truth_value_function(Falsity);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* INVOKE-CONNECTION-HANDLER-IF-ANY */
Object invoke_connection_handler_if_any(connection_or_block_qm,window,
	    connection_type,block_receiving_connection_if_any_qm)
    Object connection_or_block_qm, window, connection_type;
    Object block_receiving_connection_if_any_qm;
{
    Object gensymed_symbol, xa, ya, frame_to_queue_qm, temp_1;
    char temp;

    x_note_fn_call(99,52);
    if (Connection_handling_procedure_qm) {
	gensymed_symbol = ISVREF(Connection_handling_procedure_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(Connection_handling_procedure_qm) ? 
		EQ(ISVREF(Connection_handling_procedure_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(Connection_handling_procedure_fsn_qm))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(Connection_handling_procedure_fsn_qm,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(Connection_handling_procedure_fsn_qm);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(Connection_handling_procedure_fsn_qm),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	frame_to_queue_qm = connection_or_block_qm ? 
		(SIMPLE_VECTOR_P(connection_or_block_qm) && 
		EQ(ISVREF(connection_or_block_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct) ? 
		get_or_make_connection_frame_and_activate_if_appropriate(connection_or_block_qm) 
		: connection_or_block_qm) : Nil;
	if (frame_to_queue_qm) {
	    Connection_handling_connection_queue = 
		    nconc2(Connection_handling_connection_queue,
		    slot_value_cons_1(frame_to_queue_qm,Nil));
	    temp_1 = Connection_handling_fsn_queue;
	    Connection_handling_fsn_queue = nconc2(temp_1,
		    slot_value_cons_1(copy_frame_serial_number(ISVREF(frame_to_queue_qm,
		    (SI_Long)3L)),Nil));
	    Connection_handling_window_queue = 
		    nconc2(Connection_handling_window_queue,
		    slot_value_cons_1(window,Nil));
	    Connection_handling_connection_type_queue = 
		    nconc2(Connection_handling_connection_type_queue,
		    slot_value_cons_1(connection_type,Nil));
	    Connection_handling_block_queue = 
		    nconc2(Connection_handling_block_queue,
		    slot_value_cons_1(block_receiving_connection_if_any_qm,
		    Nil));
	}
	return start_procedure_invocation_in_place(Connection_handling_procedure_qm,
		Nil,Nil,Nil,FIX((SI_Long)0L),FIX((SI_Long)0L),Nil,Nil,Nil,
		Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-SET-CONNECTION-PORT-NAME */
Object g2_set_connection_port_name(block,connection_frame_1,name)
    Object block, connection_frame_1, name;
{
    Object connection, gensymed_symbol, connections, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object connection_item, svref_new_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(99,53);
    connection = ISVREF(connection_frame_1,(SI_Long)21L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    connections = gensymed_symbol;
    skip_list = CDR(connections);
    key_value = connection;
    key_hash_value = SXHASH_SYMBOL_1(connection) & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)7L;
    ab_loop_bind_ = bottom_level;
  next_loop:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (connection_item) {
	if (ISVREF(connection_item,(SI_Long)2L)) {
	    reclaim_slot_value_list_1(ISVREF(connection_item,(SI_Long)2L));
	    svref_new_value = slot_value_cons_1(name,Nil);
	    return VALUES_1(SVREF(connection_item,FIX((SI_Long)2L)) = 
		    svref_new_value);
	}
	else {
	    if (ISVREF(connection_item,(SI_Long)1L))
		reclaim_slot_value_list_1(ISVREF(connection_item,(SI_Long)1L));
	    svref_new_value = slot_value_cons_1(name,Nil);
	    return VALUES_1(SVREF(connection_item,FIX((SI_Long)1L)) = 
		    svref_new_value);
	}
    }
    else
	return VALUES_1(Nil);
}

/* G2-GET-CONNECTION-INPUT-AND-OUTPUT */
Object g2_get_connection_input_and_output(connection_frame_1)
    Object connection_frame_1;
{
    Object connection, in, out, sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(99,54);
    connection = ISVREF(connection_frame_1,(SI_Long)21L);
    in = ISVREF(connection,(SI_Long)3L);
    out = ISVREF(connection,(SI_Long)2L);
    temp =  !TRUEP(in);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(in,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    temp_1 = temp ? make_evaluation_truth_value_function(Falsity) : in;
    temp =  !TRUEP(out);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(out,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    temp_2 = temp ? make_evaluation_truth_value_function(Falsity) : out;
    return VALUES_2(temp_1,temp_2);
}

void connect3_INIT()
{
    Object temp, temp_1, gensymed_symbol;
    Object Qg2_get_connection_input_and_output;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_set_connection_port_name, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_more_connections_to_be_handled, Qg2_get_connection_to_handle;
    Object Qg2_register_connection_handling_procedure;
    Object Qreclaim_slot_value_list_function, Qconnect3;
    Object Qreclaim_slot_value_fsn_queue, Qreclaim_frame_serial_number;
    Object list_constant_4, Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_loose_end;

    x_note_fn_call(99,55);
    SET_PACKAGE("AB");
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    AB_package = STATIC_PACKAGE("AB");
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    list_constant = STATIC_LIST((SI_Long)2L,Qtop,Qbottom);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qright,Qleft);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qleft,Qright);
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    if (Delete_connections_without_leaving_stubs_qm == UNBOUND)
	Delete_connections_without_leaving_stubs_qm = Nil;
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qcleanup_for_loose_end = STATIC_SYMBOL("CLEANUP-FOR-LOOSE-END",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_loose_end,
	    STATIC_FUNCTION(cleanup_for_loose_end,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp = SYMBOL_FUNCTION(Qcleanup_for_loose_end);
    set_get(Qloose_end,Qcleanup,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp = CONS(Qloose_end,temp_1);
    mutate_global_property(Qcleanup,temp,Qclasses_which_define);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    if (Junction_blocks_not_to_be_deleted == UNBOUND)
	Junction_blocks_not_to_be_deleted = Nil;
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qjunction_connection_1 = STATIC_SYMBOL("JUNCTION-CONNECTION-1",AB_package);
    Qjunction_connection_2 = STATIC_SYMBOL("JUNCTION-CONNECTION-2",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    list_constant_4 = STATIC_CONS(Qbottom,Qnil);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,Qtop,Qright,
	    list_constant_4);
    string_constant = 
	    STATIC_STRING("Can\'t join connections with incompatible cross sections");
    string_constant_1 = 
	    STATIC_STRING("Can\'t join directed and non-directed connections!");
    string_constant_2 = 
	    STATIC_STRING("Can\'t join directed connections with opposing directions!");
    Qconnection_handling_procedure_qm = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-PROCEDURE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_procedure_qm,
	    Connection_handling_procedure_qm);
    Qconnect3 = STATIC_SYMBOL("CONNECT3",AB_package);
    record_system_variable(Qconnection_handling_procedure_qm,Qconnect3,Nil,
	    Qnil,Qnil,Qnil,Qt);
    Qconnection_handling_procedure_fsn_qm = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-PROCEDURE-FSN\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_procedure_fsn_qm,
	    Connection_handling_procedure_fsn_qm);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number,
	    STATIC_FUNCTION(reclaim_frame_serial_number,NIL,FALSE,1,1));
    record_system_variable(Qconnection_handling_procedure_fsn_qm,Qconnect3,
	    Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    Qconnection_handling_connection_queue = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-CONNECTION-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_connection_queue,
	    Connection_handling_connection_queue);
    Qreclaim_slot_value_list_function = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_slot_value_list_function,
	    STATIC_FUNCTION(reclaim_slot_value_list_function,NIL,FALSE,1,1));
    record_system_variable(Qconnection_handling_connection_queue,Qconnect3,
	    Nil,Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qconnection_handling_fsn_queue = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-FSN-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_fsn_queue,
	    Connection_handling_fsn_queue);
    Qreclaim_slot_value_fsn_queue = 
	    STATIC_SYMBOL("RECLAIM-SLOT-VALUE-FSN-QUEUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_slot_value_fsn_queue,
	    STATIC_FUNCTION(reclaim_slot_value_fsn_queue,NIL,FALSE,1,1));
    record_system_variable(Qconnection_handling_fsn_queue,Qconnect3,Nil,
	    Qnil,Qnil,Qreclaim_slot_value_fsn_queue,Qt);
    Qconnection_handling_window_queue = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-WINDOW-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_window_queue,
	    Connection_handling_window_queue);
    record_system_variable(Qconnection_handling_window_queue,Qconnect3,Nil,
	    Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qconnection_handling_connection_type_queue = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-CONNECTION-TYPE-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_connection_type_queue,
	    Connection_handling_connection_type_queue);
    record_system_variable(Qconnection_handling_connection_type_queue,
	    Qconnect3,Nil,Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qconnection_handling_block_queue = 
	    STATIC_SYMBOL("CONNECTION-HANDLING-BLOCK-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_handling_block_queue,
	    Connection_handling_block_queue);
    record_system_variable(Qconnection_handling_block_queue,Qconnect3,Nil,
	    Qnil,Qnil,Qreclaim_slot_value_list_function,Qt);
    Qg2_register_connection_handling_procedure = 
	    STATIC_SYMBOL("G2-REGISTER-CONNECTION-HANDLING-PROCEDURE",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_register_connection_handling_procedure,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_register_connection_handling_procedure,
	    STATIC_FUNCTION(g2_register_connection_handling_procedure,NIL,
	    FALSE,1,1));
    Qg2_get_connection_to_handle = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-TO-HANDLE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_connection_to_handle,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_connection_to_handle,
	    STATIC_FUNCTION(g2_get_connection_to_handle,NIL,FALSE,0,0));
    Qg2_more_connections_to_be_handled = 
	    STATIC_SYMBOL("G2-MORE-CONNECTIONS-TO-BE-HANDLED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_more_connections_to_be_handled,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_more_connections_to_be_handled,
	    STATIC_FUNCTION(g2_more_connections_to_be_handled,NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_set_connection_port_name = 
	    STATIC_SYMBOL("G2-SET-CONNECTION-PORT-NAME",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_connection_port_name,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_connection_port_name,
	    STATIC_FUNCTION(g2_set_connection_port_name,NIL,FALSE,3,3));
    Qg2_get_connection_input_and_output = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-INPUT-AND-OUTPUT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_connection_input_and_output,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_connection_input_and_output,
	    STATIC_FUNCTION(g2_get_connection_input_and_output,NIL,FALSE,1,1));
}
