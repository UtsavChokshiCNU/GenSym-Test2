/* cnct2.c
 * Input file:  connect2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct2.h"


static Object Qconnection_item_table;  /* connection-item-table */

static Object Qlookup;             /* lookup */

static Object Qinput;              /* input */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* MAKE-STUBS */
Object make_stubs varargs_1(int, n)
{
    Object block, stub_specs;
    Object transient_qm, tail, head, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object connection_item_table, connection_name_or_names, connection_type;
    Object direction_qm, side, position_1, style_qm, pattern_qm;
    Object connection_arrows_qm, ab_loop_list_, new_stub_qm, ab_loop_desetq_;
    Object temp_1, connection_item, names, slot_group_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(98,0);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    stub_specs = REQUIRED_ARG_nonrelocating();
    transient_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tail = 
	    make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
	    tail);
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
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
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
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
    connection_item_table = gensymed_symbol;
    connection_name_or_names = Nil;
    connection_type = Nil;
    direction_qm = Nil;
    side = Nil;
    position_1 = Nil;
    style_qm = Nil;
    pattern_qm = Nil;
    connection_arrows_qm = Nil;
    ab_loop_list_ = stub_specs;
    new_stub_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    connection_name_or_names = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    connection_type = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    direction_qm = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    side = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    position_1 = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    style_qm = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    pattern_qm = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    connection_arrows_qm = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_stub_qm = make_stub(9,block,connection_type,direction_qm,side,
	    position_1,transient_qm,style_qm,pattern_qm,connection_arrows_qm);
    if (new_stub_qm) {
	connection_item = make_connection_item_1(new_stub_qm);
	names = connection_name_or_names ? 
		(CONSP(connection_name_or_names) ? 
		copy_list_using_slot_value_conses_1(connection_name_or_names) 
		: slot_value_cons_1(connection_name_or_names,Nil)) : Nil;
	if (EQ(direction_qm,Qinput))
	    SVREF(connection_item,FIX((SI_Long)2L)) = names;
	else
	    SVREF(connection_item,FIX((SI_Long)1L)) = names;
	gensymed_symbol = new_stub_qm;
	set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,Nil,
		T,gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),connection_item);
    }
    goto next_loop;
  end_loop:;
    gensymed_symbol = block;
    gensymed_symbol_1 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    gensymed_symbol_1 = connection_item_table;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	temp = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp,FIX((SI_Long)6L)) = gensymed_symbol_1;
    }
    return VALUES_1(gensymed_symbol_1);
}

/* ADD-STUB-GIVEN-SPEC */
Object add_stub_given_spec(block,stub_info)
    Object block, stub_info;
{
    Object gensymed_symbol, connection_name_or_names, connection_type;
    Object direction_qm, side, position_1, connection_style_qm;
    Object line_pattern_qm;

    x_note_fn_call(98,1);
    gensymed_symbol = stub_info;
    connection_name_or_names = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    connection_type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    direction_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    side = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    position_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    connection_style_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    line_pattern_qm = CAR(gensymed_symbol);
    return add_stub(9,block,connection_name_or_names,connection_type,
	    direction_qm,side,position_1,Nil,connection_style_qm,
	    line_pattern_qm);
}

/* ADD-STUB */
Object add_stub varargs_1(int, n)
{
    Object block, connection_name_or_names, connection_type, direction_qm;
    Object side, position_1;
    Object transient_qm, connection_style_qm, line_pattern_qm;
    Object connection_arrows_qm, new_stub_qm, gensymed_symbol;
    Object gensymed_symbol_1, slot_group_qm, tail, head, new_cons, temp;
    Object temp_1, svref_new_value, gensymed_symbol_2, connection_item, names;
    Object temp_2, this_block, superblock_qm, sub_class_bit_vector;
    Object workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(98,2);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    connection_name_or_names = REQUIRED_ARG_nonrelocating();
    connection_type = REQUIRED_ARG_nonrelocating();
    direction_qm = REQUIRED_ARG_nonrelocating();
    side = REQUIRED_ARG_nonrelocating();
    position_1 = REQUIRED_ARG_nonrelocating();
    transient_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_style_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_pattern_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_arrows_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    new_stub_qm = make_stub(9,block,connection_type,direction_qm,side,
	    position_1,transient_qm,connection_style_qm,line_pattern_qm,
	    connection_arrows_qm);
    if (new_stub_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = block;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    tail = 
		    make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_lookup_conses_vector;
		temp_1 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,temp_1) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_lookup_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qconnection_item_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_lookup_conses_vector;
		temp_1 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,temp_1) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_lookup_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = Nil;
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
	    if (slot_group_qm) {
		temp = gensymed_symbol_1;
		SVREF(slot_group_qm,FIX((SI_Long)6L)) = temp;
	    }
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(gensymed_symbol,
			    Qslot_group_for_block_qm);
		temp = make_icon_slot_group_1();
		SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
		temp = ISVREF(gensymed_symbol,(SI_Long)14L);
		temp_1 = gensymed_symbol_1;
		SVREF(temp,FIX((SI_Long)6L)) = temp_1;
	    }
	}
	connection_item = make_connection_item_1(new_stub_qm);
	names = connection_name_or_names ? 
		(CONSP(connection_name_or_names) ? 
		copy_list_using_slot_value_conses_1(connection_name_or_names) 
		: slot_value_cons_1(connection_name_or_names,Nil)) : Nil;
	if (EQ(direction_qm,Qinput))
	    SVREF(connection_item,FIX((SI_Long)2L)) = names;
	else
	    SVREF(connection_item,FIX((SI_Long)1L)) = names;
	gensymed_symbol = new_stub_qm;
	gensymed_symbol_1 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_1 = gensymed_symbol_1 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	temp_2 = gensymed_symbol_1;
	set_skip_list_entry(temp_2,FIX((SI_Long)7L),Qeq,Nil,T,
		gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),connection_item);
	this_block = block;
	superblock_qm = Nil;
      next_loop:
	gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	superblock_qm = gensymed_symbol;
	if ( !TRUEP(superblock_qm)) {
	    sub_class_bit_vector = ISVREF(ISVREF(this_block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		temp_3 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_3 = TRUEP(Nil);
	    workspace_qm = temp_3 ? this_block : Nil;
	    goto end_1;
	}
	this_block = superblock_qm;
	goto next_loop;
      end_loop:
	workspace_qm = Qnil;
      end_1:;
	if (workspace_qm) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    place_stub_loose_end_onto_workspace(block,new_stub_qm,
		    gensymed_symbol);
	    determine_subworkspace_connection_posts_for_object(new_stub_qm,
		    block);
	    return VALUES_1(new_stub_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Stub_length_to_use_qm, Qstub_length_to_use_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Default_stub_length, Qdefault_stub_length);

static Object Qoutput;             /* output */

/* MAKE-STUB */
Object make_stub varargs_1(int, n)
{
    Object block, connection_frame_or_class, direction_qm, side, position_1;
    Object transient_qm, connection_style_qm, line_pattern_qm;
    Object connection_arrows_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(98,3);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    connection_frame_or_class = REQUIRED_ARG_nonrelocating();
    direction_qm = REQUIRED_ARG_nonrelocating();
    side = REQUIRED_ARG_nonrelocating();
    position_1 = REQUIRED_ARG_nonrelocating();
    transient_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_style_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_pattern_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_arrows_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return make_stub_new(10,block,connection_frame_or_class, ! 
	    !TRUEP(direction_qm) ? T : Nil,EQ(direction_qm,Qinput) ? 
	    Qinput : Qoutput,side,position_1,transient_qm,
	    connection_style_qm,line_pattern_qm,connection_arrows_qm);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qconnection_style;   /* connection-style */

static Object Qconnection_arrows;  /* connection-arrows */

static Object Qline_pattern;       /* line-pattern */

static Object Qstub_length;        /* stub-length */

static Object Qconnection;         /* connection */

static Object Qloose_end;          /* loose-end */

static Object Qright;              /* right */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

static Object Qstub_connection;    /* stub-connection */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "Attempting to make a connection of class ~A. ~%" */

static Object string_constant_1;   /* "This class is not defined as a connection class." */

/* MAKE-STUB-NEW */
Object make_stub_new varargs_1(int, n)
{
    Object block, connection_frame_or_class, directed_qm, direction, side;
    Object position_1;
    Object transient_qm, connection_style_qm, line_pattern_qm;
    Object connection_arrows_qm, x2, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, temp_2, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, temp_3, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object sub_class_bit_vector, connection, make_transient_qm;
    Object noting_changes_to_kb_p, stub_length, stub_loose_end;
    Object stub_x_position, stub_y_position, connection_table, connection_item;
    Object slot_group_qm, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5, temp_4;
    SI_Long bv16_length, aref_new_value, length_1;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(7);
    Object result;

    x_note_fn_call(98,4);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    connection_frame_or_class = REQUIRED_ARG_nonrelocating();
    directed_qm = REQUIRED_ARG_nonrelocating();
    direction = REQUIRED_ARG_nonrelocating();
    side = REQUIRED_ARG_nonrelocating();
    position_1 = REQUIRED_ARG_nonrelocating();
    transient_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_style_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    line_pattern_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connection_arrows_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
    if (temp);
    else {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
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
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp) {
	connection = make_connection_1();
	make_transient_qm = transient_qm;
	if (make_transient_qm);
	else
	    make_transient_qm = (SI_Long)0L != (IFIX(ISVREF(block,
		    (SI_Long)5L)) & (SI_Long)262144L) ? T : Nil;
	noting_changes_to_kb_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
		0);
	  if ( !TRUEP(make_transient_qm)) {
	      temp_4 = IFIX(ISVREF(connection,(SI_Long)7L)) | (SI_Long)2L;
	      ISVREF(connection,(SI_Long)7L) = FIX(temp_4);
	  }
	  temp_3 = 
		  copy_frame_serial_number(increment_current_frame_serial_number());
	  SVREF(connection,FIX((SI_Long)10L)) = temp_3;
	  change_connection_attribute(connection,Qconnection_style,
		  connection_style_qm);
	  change_connection_attribute(connection,Qconnection_arrows,
		  copy_for_slot_value(connection_arrows_qm));
	  change_connection_attribute(connection,Qline_pattern,
		  copy_for_slot_value(line_pattern_qm));
	  stub_length = Stub_length_to_use_qm;
	  if (stub_length);
	  else {
	      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  stub_length = 
			  get_lookup_slot_value(connection_frame_or_class,
			  Qstub_length);
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
		    next_loop_12:
		      if (level < ab_loop_bind_)
			  goto end_loop_12;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_13:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_14:
		      if ( !TRUEP(marked))
			  goto end_loop_13;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
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
			  goto end_5;
		      goto next_loop_13;
		    end_loop_14:
		    end_5:
		      level = level - (SI_Long)1L;
		      goto next_loop_12;
		    end_loop_12:;
		      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
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
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			  M_CAR(gensymed_symbol_1) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      temp_3 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(temp_3,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
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
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol,temp_2,gensymed_symbol_1);
		      }
		      global_properties = gensymed_symbol;
		      skip_list = CDR(global_properties);
		      key_value = 
			      Current_kb_specific_property_list_property_name;
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
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_16:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_17:
		      if ( !TRUEP(marked))
			  goto end_loop_16;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
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
			  goto end_6;
		      goto next_loop_16;
		    end_loop_17:
		    end_6:
		      level = level - (SI_Long)1L;
		      goto next_loop_15;
		    end_loop_15:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
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
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_19:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_20:
			  if ( !TRUEP(marked))
			      goto end_loop_19;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_20;
			end_loop_19:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_22:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_23:
			  if ( !TRUEP(marked))
			      goto end_loop_22;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_23;
			end_loop_22:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
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
		    next_loop_24:
		      if (level < ab_loop_bind_)
			  goto end_loop_24;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_25:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_26:
		      if ( !TRUEP(marked))
			  goto end_loop_25;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
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
			  goto end_9;
		      goto next_loop_25;
		    end_loop_26:
		    end_9:
		      level = level - (SI_Long)1L;
		      goto next_loop_24;
		    end_loop_24:;
		      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
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
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			  M_CAR(gensymed_symbol_1) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      temp_3 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(temp_3,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
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
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol,temp_2,gensymed_symbol_1);
		      }
		      global_properties = gensymed_symbol;
		      skip_list = CDR(global_properties);
		      key_value = 
			      Current_kb_specific_property_list_property_name;
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
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_28:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_29:
		      if ( !TRUEP(marked))
			  goto end_loop_28;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
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
			  goto end_10;
		      goto next_loop_28;
		    end_loop_29:
		    end_10:
		      level = level - (SI_Long)1L;
		      goto next_loop_27;
		    end_loop_27:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
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
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_31:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_32:
			  if ( !TRUEP(marked))
			      goto end_loop_31;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_32;
			end_loop_31:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
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
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_34:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_35:
			  if ( !TRUEP(marked))
			      goto end_loop_34;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			  goto next_loop_35;
			end_loop_34:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
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
	  }
	  if (stub_length);
	  else
	      stub_length = Default_stub_length;
	  stub_loose_end = make_frame(Qloose_end);
	  if (EQ(side,Qright)) {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = (SI_Long)1L;
	      gensymed_symbol_5 = IFIX(stub_length);
	      stub_x_position = FIX(gensymed_symbol_3 + gensymed_symbol_4 
		      + gensymed_symbol_5);
	  }
	  else if (EQ(side,Qleft)) {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = IFIX(stub_length);
	      stub_x_position = FIX(gensymed_symbol_3 - gensymed_symbol_4);
	  }
	  else {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = IFIX(position_1);
	      stub_x_position = FIX(gensymed_symbol_3 + gensymed_symbol_4);
	  }
	  if (EQ(side,Qtop)) {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = IFIX(stub_length);
	      stub_y_position = FIX(gensymed_symbol_3 - gensymed_symbol_4);
	  }
	  else if (EQ(side,Qbottom)) {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)3L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = (SI_Long)1L;
	      gensymed_symbol_5 = IFIX(stub_length);
	      stub_y_position = FIX(gensymed_symbol_3 + gensymed_symbol_4 
		      + gensymed_symbol_5);
	  }
	  else {
	      gensymed_symbol = ISVREF(block,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_3 = IFIX(gensymed_symbol);
	      gensymed_symbol_4 = IFIX(position_1);
	      stub_y_position = FIX(gensymed_symbol_3 + gensymed_symbol_4);
	  }
	  if (make_transient_qm) {
	      temp_4 = IFIX(ISVREF(stub_loose_end,(SI_Long)5L)) | 
		      (SI_Long)262144L;
	      ISVREF(stub_loose_end,(SI_Long)5L) = FIX(temp_4);
	  }
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(stub_loose_end,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	  gensymed_symbol_1 = stub_loose_end;
	  gensymed_symbol_2 = ISVREF(stub_loose_end,(SI_Long)14L);
	  gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	  gensymed_symbol_3 =  - gensymed_symbol_3;
	  gensymed_symbol_4 = IFIX(stub_x_position);
	  gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	  gensymed_symbol_2 = ISVREF(stub_loose_end,(SI_Long)14L);
	  gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	  gensymed_symbol_4 =  - gensymed_symbol_4;
	  gensymed_symbol_5 = IFIX(stub_y_position);
	  gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  FIX(gensymed_symbol_3),FIX(gensymed_symbol_4));
	  if (directed_qm) {
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      temp_4 = IFIX(ISVREF(connection,(SI_Long)7L)) &  ~(SI_Long)1L;
	      ISVREF(connection,(SI_Long)7L) = FIX(temp_4);
	  }
	  else {
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      temp_4 = IFIX(ISVREF(connection,(SI_Long)7L)) | (SI_Long)1L;
	      ISVREF(connection,(SI_Long)7L) = FIX(temp_4);
	  }
	  tail = 
		  make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
		  Nil);
	  head = 
		  make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
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
	  M_CAR(gensymed_symbol_1) = head;
	  M_CDR(gensymed_symbol_1) = tail;
	  inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	  M_CDR(gensymed_symbol) = gensymed_symbol_1;
	  inline_note_allocate_cons(gensymed_symbol,Qlookup);
	  connection_table = gensymed_symbol;
	  connection_item = make_connection_item_1(connection);
	  if (EQ(direction,Qinput)) {
	      temp_3 = slot_value_cons_1(Qstub_connection,Nil);
	      SVREF(connection_item,FIX((SI_Long)1L)) = temp_3;
	  }
	  else {
	      temp_3 = slot_value_cons_1(Qstub_connection,Nil);
	      SVREF(connection_item,FIX((SI_Long)2L)) = temp_3;
	  }
	  gensymed_symbol = connection;
	  set_skip_list_entry(connection_table,FIX((SI_Long)7L),Qeq,Nil,T,
		  gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		  IFIX(Most_positive_fixnum)),connection_item);
	  gensymed_symbol = stub_loose_end;
	  gensymed_symbol_1 = Nil;
	  slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	  gensymed_symbol_1 = connection_table;
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
	  if (EQ(direction,Qinput)) {
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
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
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
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
	      gensymed_symbol_4 = EQ(side,Qleft) || EQ(side,Qright) ? 
		      IFIX(position_1) : IFIX(position_1);
	      gensymed_symbol_5 = (SI_Long)2L;
	      gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	      temp_4 = gensymed_symbol_3 + gensymed_symbol_4;
	      ISVREF(connection,(SI_Long)4L) = FIX(temp_4);
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      SVREF(connection,FIX((SI_Long)3L)) = stub_loose_end;
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      if (EQ(side,Qleft))
		  temp_2 = Qright;
	      else if (EQ(side,Qright))
		  temp_2 = Qleft;
	      else if (EQ(side,Qtop))
		  temp_2 = Qbottom;
	      else
		  temp_2 = Qtop;
	      if (EQ(temp_2,Qtop))
		  gensymed_symbol_3 = (SI_Long)0L;
	      else if (EQ(temp_2,Qleft))
		  gensymed_symbol_3 = (SI_Long)1L;
	      else if (EQ(temp_2,Qbottom))
		  gensymed_symbol_3 = (SI_Long)2L;
	      else
		  gensymed_symbol_3 = (SI_Long)3L;
	      gensymed_symbol_4 = (SI_Long)0L;
	      temp_4 = gensymed_symbol_3 + gensymed_symbol_4;
	      ISVREF(connection,(SI_Long)5L) = FIX(temp_4);
	  }
	  else {
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
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
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
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
	      gensymed_symbol_4 = EQ(side,Qleft) || EQ(side,Qright) ? 
		      IFIX(position_1) : IFIX(position_1);
	      gensymed_symbol_5 = (SI_Long)2L;
	      gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	      temp_4 = gensymed_symbol_3 + gensymed_symbol_4;
	      ISVREF(connection,(SI_Long)5L) = FIX(temp_4);
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      SVREF(connection,FIX((SI_Long)2L)) = stub_loose_end;
	      temp = TRUEP(Noting_changes_to_kb_p);
	      if (temp);
	      else {
		  gensymed_symbol_3 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp =  !((SI_Long)0L != gensymed_symbol_3) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp)
		  note_change_to_connection_1(connection);
	      if (EQ(side,Qleft))
		  temp_2 = Qright;
	      else if (EQ(side,Qright))
		  temp_2 = Qleft;
	      else if (EQ(side,Qtop))
		  temp_2 = Qbottom;
	      else
		  temp_2 = Qtop;
	      if (EQ(temp_2,Qtop))
		  gensymed_symbol_3 = (SI_Long)0L;
	      else if (EQ(temp_2,Qleft))
		  gensymed_symbol_3 = (SI_Long)1L;
	      else if (EQ(temp_2,Qbottom))
		  gensymed_symbol_3 = (SI_Long)2L;
	      else
		  gensymed_symbol_3 = (SI_Long)3L;
	      gensymed_symbol_4 = (SI_Long)0L;
	      temp_4 = gensymed_symbol_3 + gensymed_symbol_4;
	      ISVREF(connection,(SI_Long)4L) = FIX(temp_4);
	  }
	  if (make_transient_qm) {
	      temp_4 = IFIX(ISVREF(connection,(SI_Long)7L)) | (SI_Long)64L;
	      ISVREF(connection,(SI_Long)7L) = FIX(temp_4);
	  }
	  if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		  > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if ( !temp ? make_transient_qm || 
		  always_instantiate_connection_frame_for_this_class_qm(connection_frame_or_class) 
		  : TRUEP(Nil))
	      connection_frame_or_class = 
		      make_new_connection_frame_for_connection(connection,
		      connection_frame_or_class);
	  else {
	      SVREF(connection,FIX((SI_Long)1L)) = connection_frame_or_class;
	      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp ? TRUEP(make_transient_qm) : TRUEP(Nil))
		  set_transient_and_propagate(connection_frame_or_class,Nil);
	  }
	  if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		  > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      ISVREF(connection_frame_or_class,(SI_Long)21L) = connection;
	      update_runtime_structures_according_to_edit(1,
		      connection_frame_or_class);
	  }
	  result = VALUES_1(connection);
	POP_SPECIAL();
	return result;
    }
    else {
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
		  temp_4 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp_4,aref_new_value);
		  temp_4 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,temp_4,aref_new_value);
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
			  tformat(2,string_constant,connection_frame_or_class);
			  tformat(1,string_constant_1);
			  temp_2 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		notify_user_1(temp_2);
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	return VALUES_1(Nil);
    }
}

/* GET-CONNECTION-FOR-LOOSE-END */
Object get_connection_for_loose_end(loose_end)
    Object loose_end;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,5);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
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
      result = VALUES_1(connection);
      goto end_2;
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* ALWAYS-INSTANTIATE-CONNECTION-FRAME-FOR-THIS-CLASS? */
Object always_instantiate_connection_frame_for_this_class_qm(connection_class)
    Object connection_class;
{
    Object slot_description, class_description, ab_loop_list_, slot_init_form;
    Object ab_loop_it_;

    x_note_fn_call(98,6);
    if ( !TRUEP(Releasing_kb_qm)) {
	slot_description = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(connection_class,
		Class_description_gkbprop);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	slot_init_form = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	slot_init_form = ISVREF(slot_description,(SI_Long)6L);
	ab_loop_it_ = slot_init_form_needs_evaluation_qm(slot_init_form);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* PLACE-STUB-LOOSE-END-ONTO-WORKSPACE */
Object place_stub_loose_end_onto_workspace(block,stub_connection,workspace)
    Object block, stub_connection, workspace;
{
    Object loose_end, connection_frame_or_class, x2;
    char temp;

    x_note_fn_call(98,7);
    if (workspace) {
	loose_end = get_block_at_other_end_of_connection(stub_connection,
		block);
	connection_frame_or_class = ISVREF(stub_connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    activate_connection_frame_if_appropriate(connection_frame_or_class,
		    workspace);
	add_subblock(loose_end,workspace);
    }
    if (G2_has_v5_mode_windows_p) {
	send_ws_representations_item_insert_as_subblock(stub_connection,
		block,
		find_connection_or_block_below_this_connection(stub_connection,
		ISVREF(stub_connection,(SI_Long)3L)));
	send_ws_representations_connection_moved(stub_connection);
    }
    return VALUES_1(Nil);
}

/* GET-OR-MAKE-CONNECTION-FRAME-AND-ACTIVATE-IF-APPROPRIATE */
Object get_or_make_connection_frame_and_activate_if_appropriate(connection)
    Object connection;
{
    Object connection_frame_or_class, x2, connection_frame_for_connection;
    Object superblock_qm;
    char temp;

    x_note_fn_call(98,8);
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
    connection_frame_for_connection = temp ? connection_frame_or_class : 
	    make_and_install_new_connection_frame(connection,
	    connection_frame_or_class);
    superblock_qm = get_superblock_of_connection(connection);
    activate_connection_frame_if_appropriate(connection_frame_for_connection,
	    superblock_qm);
    return VALUES_1(connection_frame_for_connection);
}

/* ACTIVATE-CONNECTION-FRAME-IF-APPROPRIATE */
Object activate_connection_frame_if_appropriate(connection_frame_1,
	    superblock_qm)
    Object connection_frame_1, superblock_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,9);
    if ( !((SI_Long)0L != (IFIX(ISVREF(connection_frame_1,(SI_Long)5L)) & 
	    (SI_Long)1L)) && superblock_qm && (SI_Long)0L != 
	    (IFIX(ISVREF(superblock_qm,(SI_Long)5L)) & (SI_Long)1L)) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(connection_frame_1,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = connection_frame_1;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-NEW-SUBBLOCK-CONNECTIONS-ACTIVATION-AND-PROPAGATE */
Object update_new_subblock_connections_activation_and_propagate(block,
	    superblock)
    Object block, superblock;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_, x;
    Object x2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,10);
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
      x = ISVREF(connection,(SI_Long)1L);
      if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
	      Qavailable_frame_vector)) {
	  x2 = ISVREF(x,(SI_Long)1L);
	  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  update_new_subblock_activation_and_propagate(ISVREF(connection,
		  (SI_Long)1L),superblock);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* UPDATE-REMOVED-SUBBLOCK-CONNECTIONS-ACTIVATION-AND-PROPAGATE */
Object update_removed_subblock_connections_activation_and_propagate(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_, x;
    Object x2, frame, sub_vector_qm, function_qm;
    SI_Long method_index;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,11);
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
      x = ISVREF(connection,(SI_Long)1L);
      if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
	      Qavailable_frame_vector)) {
	  x2 = ISVREF(x,(SI_Long)1L);
	  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  method_index = (SI_Long)31L;
	  frame = ISVREF(connection,(SI_Long)1L);
	  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),method_index);
	  function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) :
		   Nil;
	  if (function_qm)
	      inline_funcall_2(function_qm,frame,Nil);
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* GET-SUPERBLOCK-OF-CONNECTION-FRAME */
Object get_superblock_of_connection_frame(connection_frame_1)
    Object connection_frame_1;
{
    x_note_fn_call(98,12);
    return get_superblock_of_connection(ISVREF(connection_frame_1,
	    (SI_Long)21L));
}

/* GET-SUPERBLOCK-OF-CONNECTION */
Object get_superblock_of_connection(connection)
    Object connection;
{
    Object gensymed_symbol;

    x_note_fn_call(98,13);
    gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(connection,(SI_Long)3L),
	    (SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    return VALUES_1(gensymed_symbol);
}

/* MAKE-AND-INSTALL-NEW-CONNECTION-FRAME */
Object make_and_install_new_connection_frame(connection,connection_class)
    Object connection, connection_class;
{
    Object new_connection_frame;

    x_note_fn_call(98,14);
    new_connection_frame = 
	    make_new_connection_frame_for_connection(connection,
	    connection_class);
    update_runtime_structures_according_to_edit(1,connection_class);
    return VALUES_1(new_connection_frame);
}

static Object Qorthogonal;         /* orthogonal */

static Object Qlayer_position_of_block;  /* layer-position-of-block */

/* MAKE-NEW-CONNECTION-FRAME-FOR-CONNECTION */
Object make_new_connection_frame_for_connection(connection,connection_class)
    Object connection, connection_class;
{
    Object new_connection_frame, temp_1;
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(98,15);
    new_connection_frame = make_entity(1,connection_class);
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    ISVREF(new_connection_frame,(SI_Long)21L) = connection;
    SVREF(connection,FIX((SI_Long)1L)) = new_connection_frame;
    if ((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)64L))
	set_transient_and_propagate(new_connection_frame,Nil);
    add_as_inferior_block(new_connection_frame,ISVREF(connection,(SI_Long)2L));
    temp_1 = getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
	    Qconnection_style);
    if (temp_1);
    else
	temp_1 = Qorthogonal;
    set_non_savable_lookup_slot_value(new_connection_frame,
	    Qconnection_style,temp_1);
    set_non_savable_lookup_slot_value(new_connection_frame,
	    Qconnection_arrows,
	    copy_for_slot_value(connection_arrows_of_connection(connection)));
    set_non_savable_lookup_slot_value(new_connection_frame,Qline_pattern,
	    copy_for_slot_value(connection_line_pattern(connection)));
    set_non_savable_lookup_slot_value(new_connection_frame,
	    Qlayer_position_of_block,ISVREF(connection,(SI_Long)11L));
    return VALUES_1(new_connection_frame);
}

/* CLEANUP-FOR-CONNECTION */
Object cleanup_for_connection(connection)
    Object connection;
{
    Object frame, sub_vector_qm, method_function_qm, connection_structure_qm;
    Object svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(98,16);
    frame = connection;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection)) {
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
    connection_structure_qm = ISVREF(connection,(SI_Long)21L);
    if (connection_structure_qm) {
	svref_new_value = ISVREF(ISVREF(connection,(SI_Long)1L),(SI_Long)1L);
	return VALUES_1(SVREF(connection_structure_qm,FIX((SI_Long)1L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-UNSAVED-SLOTS-FROM-CONNECTION-TO-CONNECTION-FRAME */
Object copy_unsaved_slots_from_connection_to_connection_frame(connection,
	    connection_frame_1)
    Object connection, connection_frame_1;
{
    Object temp;

    x_note_fn_call(98,17);
    temp = getfq_function_no_default(ISVREF(connection,(SI_Long)9L),
	    Qconnection_style);
    if (temp);
    else
	temp = Qorthogonal;
    change_slot_value(3,connection_frame_1,Qconnection_style,temp);
    change_slot_value(3,connection_frame_1,Qconnection_arrows,
	    copy_for_slot_value(connection_arrows_of_connection(connection)));
    return change_slot_value(3,connection_frame_1,Qline_pattern,
	    copy_for_slot_value(connection_line_pattern(connection)));
}

static Object array_constant;      /* # */

/* CLONE-STUB-FOR-CONNECTION */
Object clone_stub_for_connection(previous_connection_qm,
	    connection_being_cloned,frame_being_cloned,new_frame)
    Object previous_connection_qm, connection_being_cloned, frame_being_cloned;
    Object new_frame;
{
    Object old_connection_frame_or_class, x2, new_connection_frame_or_class;
    Object output_qm, new_end_position, new_end_side, new_stub;
    SI_Long new_end_position_on_side;
    char temp;

    x_note_fn_call(98,18);
    old_connection_frame_or_class = ISVREF(connection_being_cloned,
	    (SI_Long)1L);
    if (SIMPLE_VECTOR_P(old_connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_connection_frame_or_class)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(old_connection_frame_or_class,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(old_connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    new_connection_frame_or_class = temp ? clone_frame(1,
	    old_connection_frame_or_class) : old_connection_frame_or_class;
    output_qm =  !EQ(connection_being_cloned,previous_connection_qm) ? 
	    (EQ(ISVREF(connection_being_cloned,(SI_Long)3L),
	    frame_being_cloned) ? T : Nil) : Qnil;
    new_end_position = output_qm ? ISVREF(connection_being_cloned,
	    (SI_Long)5L) : ISVREF(connection_being_cloned,(SI_Long)4L);
    new_end_side = ISVREF(array_constant,IFIX(new_end_position) & (SI_Long)3L);
    new_end_position_on_side = IFIX(new_end_position) >>  -  - (SI_Long)2L;
    new_stub = make_stub_new(6,new_frame,new_connection_frame_or_class, 
	    !((SI_Long)0L != (IFIX(ISVREF(connection_being_cloned,
	    (SI_Long)7L)) & (SI_Long)1L)) ? T : Nil,output_qm ? Qoutput : 
	    Qinput,new_end_side,FIX(new_end_position_on_side));
    clone_connection_attributes_plist(connection_being_cloned,new_stub);
    return VALUES_1(new_stub);
}

/* CLONE-CONNECTION-ATTRIBUTES-PLIST */
Object clone_connection_attributes_plist(old_connection,new_connection)
    Object old_connection, new_connection;
{
    x_note_fn_call(98,19);
    change_connection_attribute(new_connection,Qconnection_style,
	    getfq_function_no_default(ISVREF(old_connection,(SI_Long)9L),
	    Qconnection_style));
    change_connection_attribute(new_connection,Qconnection_arrows,
	    copy_for_slot_value(connection_arrows_of_connection(old_connection)));
    return change_connection_attribute(new_connection,Qline_pattern,
	    copy_for_slot_value(connection_line_pattern(old_connection)));
}

static Object Qframe_flags;        /* frame-flags */

/* SET-CONNECTIONS-OF-TRANSIENT-BLOCK-TRANSIENT */
Object set_connections_of_transient_block_transient(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class;
    Object loose_end_maybe, temp, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,20);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      connection_frame_or_class = Nil;
      loose_end_maybe = Nil;
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
      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
      loose_end_maybe = get_block_at_other_end_of_connection(connection,block);
      make_connection_transient(connection);
      sub_class_bit_vector = ISVREF(ISVREF(loose_end_maybe,(SI_Long)1L),
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  svref_new_value = IFIX(ISVREF(loose_end_maybe,(SI_Long)5L)) | 
		  (SI_Long)262144L;
	  ISVREF(loose_end_maybe,(SI_Long)5L) = FIX(svref_new_value);
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(loose_end_maybe,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(loose_end_maybe,(SI_Long)4L)) &  
		  ~(SI_Long)1L;
	  ISVREF(loose_end_maybe,(SI_Long)4L) = FIX(svref_new_value);
      }
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
      if (temp_1)
	  set_transient_and_propagate(connection_frame_or_class,Nil);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SET-CONNECTIONS-OF-PERMANENT-BLOCK-PERMANENT */
Object set_connections_of_permanent_block_permanent(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class;
    Object block_at_other_end, temp, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,21);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      connection_frame_or_class = Nil;
      block_at_other_end = Nil;
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
      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
      block_at_other_end = get_block_at_other_end_of_connection(connection,
	      block);
      sub_class_bit_vector = ISVREF(ISVREF(block_at_other_end,(SI_Long)1L),
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(block_at_other_end,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(block_at_other_end,(SI_Long)4L)) | 
		  (SI_Long)1L;
	  ISVREF(block_at_other_end,(SI_Long)4L) = FIX(svref_new_value);
	  svref_new_value = IFIX(ISVREF(block_at_other_end,(SI_Long)5L)) & 
		   ~(SI_Long)262144L;
	  ISVREF(block_at_other_end,(SI_Long)5L) = FIX(svref_new_value);
	  make_connection_permanent(connection);
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
	      set_permanent_and_propagate(connection_frame_or_class,Nil);
      }
      else if ((SI_Long)0L != (IFIX(ISVREF(block_at_other_end,
	      (SI_Long)4L)) & (SI_Long)1L)) {
	  make_connection_permanent(connection);
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
	      set_permanent_and_propagate(connection_frame_or_class,Nil);
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SET-CONNECTIONS-OF-NEITHER-PERMANENT-NOR-TRANSIENT-BLOCK-NEITHER-PERMANENT-NOR-TRANSIENT */
Object set_connections_of_neither_permanent_nor_transient_block_neither_permanent_nor_transient(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class;
    Object loose_end_maybe, temp, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,22);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      connection_frame_or_class = Nil;
      loose_end_maybe = Nil;
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
      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
      loose_end_maybe = get_block_at_other_end_of_connection(connection,block);
      make_connection_neither_permanent_nor_transient(connection);
      sub_class_bit_vector = ISVREF(ISVREF(loose_end_maybe,(SI_Long)1L),
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  svref_new_value = IFIX(ISVREF(loose_end_maybe,(SI_Long)5L)) &  
		  ~(SI_Long)262144L;
	  ISVREF(loose_end_maybe,(SI_Long)5L) = FIX(svref_new_value);
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(loose_end_maybe,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(loose_end_maybe,(SI_Long)4L)) &  
		  ~(SI_Long)1L;
	  ISVREF(loose_end_maybe,(SI_Long)4L) = FIX(svref_new_value);
      }
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
      if (temp_1)
	  set_neither_permanent_nor_transient_and_propagate(connection_frame_or_class,
		  Nil);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MAKE-CONNECTION-TRANSIENT */
Object make_connection_transient(connection)
    Object connection;
{
    Object connection_frame_1, output_end_object, input_end_object, x2;
    Object sub_class_bit_vector;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(98,23);
    note_change_or_deletion(connection,T);
    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) | (SI_Long)64L;
    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
    connection_frame_1 = ISVREF(connection,(SI_Long)1L);
    output_end_object = ISVREF(connection,(SI_Long)2L);
    input_end_object = ISVREF(connection,(SI_Long)3L);
    if (SIMPLE_VECTOR_P(connection_frame_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)5L)) | 
		(SI_Long)262144L;
	ISVREF(connection_frame_1,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(connection_frame_1,Qframe_flags);
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)4L)) &  
		~(SI_Long)1L;
	ISVREF(connection_frame_1,(SI_Long)4L) = FIX(svref_new_value);
    }
    sub_class_bit_vector = ISVREF(ISVREF(output_end_object,(SI_Long)1L),
	    (SI_Long)19L);
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
	svref_new_value = IFIX(ISVREF(output_end_object,(SI_Long)5L)) | 
		(SI_Long)262144L;
	ISVREF(output_end_object,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(output_end_object,Qframe_flags);
	svref_new_value = IFIX(ISVREF(output_end_object,(SI_Long)4L)) &  
		~(SI_Long)1L;
	ISVREF(output_end_object,(SI_Long)4L) = FIX(svref_new_value);
    }
    sub_class_bit_vector = ISVREF(ISVREF(input_end_object,(SI_Long)1L),
	    (SI_Long)19L);
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
	svref_new_value = IFIX(ISVREF(input_end_object,(SI_Long)5L)) | 
		(SI_Long)262144L;
	ISVREF(input_end_object,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(input_end_object,Qframe_flags);
	svref_new_value = IFIX(ISVREF(input_end_object,(SI_Long)4L)) &  
		~(SI_Long)1L;
	return VALUES_1(ISVREF(input_end_object,(SI_Long)4L) = 
		FIX(svref_new_value));
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-CONNECTION-PERMANENT */
Object make_connection_permanent(connection)
    Object connection;
{
    Object connection_frame_1, output_end_object, input_end_object, x2;
    Object sub_class_bit_vector;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(98,24);
    note_change_or_deletion(connection,T);
    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  ~(SI_Long)64L;
    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
    connection_frame_1 = ISVREF(connection,(SI_Long)1L);
    output_end_object = ISVREF(connection,(SI_Long)2L);
    input_end_object = ISVREF(connection,(SI_Long)3L);
    if (SIMPLE_VECTOR_P(connection_frame_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)5L)) &  
		~(SI_Long)262144L;
	ISVREF(connection_frame_1,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(connection_frame_1,Qframe_flags);
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)4L)) | 
		(SI_Long)1L;
	ISVREF(connection_frame_1,(SI_Long)4L) = FIX(svref_new_value);
    }
    sub_class_bit_vector = ISVREF(ISVREF(output_end_object,(SI_Long)1L),
	    (SI_Long)19L);
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
	svref_new_value = IFIX(ISVREF(output_end_object,(SI_Long)5L)) &  
		~(SI_Long)262144L;
	ISVREF(output_end_object,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(output_end_object,Qframe_flags);
	svref_new_value = IFIX(ISVREF(output_end_object,(SI_Long)4L)) | 
		(SI_Long)1L;
	ISVREF(output_end_object,(SI_Long)4L) = FIX(svref_new_value);
    }
    sub_class_bit_vector = ISVREF(ISVREF(input_end_object,(SI_Long)1L),
	    (SI_Long)19L);
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
	svref_new_value = IFIX(ISVREF(input_end_object,(SI_Long)5L)) &  
		~(SI_Long)262144L;
	ISVREF(input_end_object,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(input_end_object,Qframe_flags);
	svref_new_value = IFIX(ISVREF(input_end_object,(SI_Long)4L)) | 
		(SI_Long)1L;
	return VALUES_1(ISVREF(input_end_object,(SI_Long)4L) = 
		FIX(svref_new_value));
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-CONNECTION-NEITHER-PERMANENT-NOR-TRANSIENT */
Object make_connection_neither_permanent_nor_transient(connection)
    Object connection;
{
    Object connection_frame_1, x2;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(98,25);
    note_change_or_deletion(connection,T);
    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  ~(SI_Long)64L;
    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
    connection_frame_1 = ISVREF(connection,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_frame_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)5L)) &  
		~(SI_Long)262144L;
	ISVREF(connection_frame_1,(SI_Long)5L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(connection_frame_1,Qframe_flags);
	svref_new_value = IFIX(ISVREF(connection_frame_1,(SI_Long)4L)) &  
		~(SI_Long)1L;
	return VALUES_1(ISVREF(connection_frame_1,(SI_Long)4L) = 
		FIX(svref_new_value));
    }
    else
	return VALUES_1(Nil);
}

static Object Qconnections;        /* connections */

static Object Qstubs;              /* stubs */

static Object Qnone;               /* none */

/* REPLACE-CONNECTION-IN-BLOCK */
Object replace_connection_in_block(block,connection_to_be_replaced,
	    new_connection)
    Object block, connection_to_be_replaced, new_connection;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash;
    Object connection_to_be_replaced_duplicated_qm, side, position_1;
    Object position_on_side, class_description, raw_stub_specs_qm;
    Object connection_replaced_via_stub_spec_qm, stub_specs_qm;
    Object connection_item_table, connection_item, input_names, output_names;
    Object new_connection_item, spec, ab_loop_list_, spec_found_qm;
    Object svref_new_value, connection, connections, output_port_connection;
    Object input_port_connection, old_single_item, gensymed_symbol_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(98,26);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qconnections);
    decache_roles_for_entities_related_to_this_connection(connection_to_be_replaced);
    decache_roles_for_entities_related_to_this_connection(new_connection);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    skip_list = CDR(gensymed_symbol);
    key_value = connection_to_be_replaced;
    key_hash_value = SXHASH_SYMBOL_1(connection_to_be_replaced) & 
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
    connection_to_be_replaced_duplicated_qm = ISVREF(IFIX(ISVREF(curr,
	    (SI_Long)1L)) == key_hash_value ? (EQ(key_value,ISVREF(curr,
	    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil,(SI_Long)3L);
    side = Nil;
    position_1 = Nil;
    position_on_side = Nil;
    class_description = ISVREF(block,(SI_Long)1L);
    raw_stub_specs_qm = assq_function(Qstubs,ISVREF(class_description,
	    (SI_Long)12L));
    connection_replaced_via_stub_spec_qm = Nil;
    stub_specs_qm = raw_stub_specs_qm && EQ(CAR(raw_stub_specs_qm),Qstubs) 
	    &&  !EQ(CDR(raw_stub_specs_qm),Qnone) ? CDR(raw_stub_specs_qm) 
	    : Nil;
    if (stub_specs_qm && connection_to_be_replaced_duplicated_qm) {
	if (EQ(block,ISVREF(new_connection,(SI_Long)3L)))
	    position_1 = ISVREF(new_connection,(SI_Long)5L);
	else
	    position_1 = ISVREF(new_connection,(SI_Long)4L);
	side = ISVREF(array_constant,IFIX(position_1) & (SI_Long)3L);
	position_on_side = FIX(IFIX(position_1) >>  -  - (SI_Long)2L);
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	connection_item_table = gensymed_symbol;
	skip_list = CDR(connection_item_table);
	key_value = connection_to_be_replaced;
	key_hash_value = SXHASH_SYMBOL_1(connection_to_be_replaced) & 
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	input_names = ISVREF(connection_item,(SI_Long)2L);
	output_names = ISVREF(connection_item,(SI_Long)1L);
	new_connection_item = make_connection_item_1(new_connection);
	SVREF(connection_item,FIX((SI_Long)3L)) = Nil;
	if (input_names || output_names) {
	    spec = Nil;
	    ab_loop_list_ = stub_specs_qm;
	    spec_found_qm = Nil;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    spec = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (spec_found_qm)
		goto end_loop_6;
	    if (memq_function(CAR(spec),input_names)) {
		spec_found_qm = T;
		temp_1 = CDDDR(spec);
		if (EQ(side,CAR(temp_1))) {
		    temp_1 = CDDDDR(spec);
		    temp_2 = FIXNUM_EQ(position_on_side,CAR(temp_1));
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    svref_new_value = 
			    copy_list_using_slot_value_conses_1(input_names);
		    SVREF(new_connection_item,FIX((SI_Long)2L)) = 
			    svref_new_value;
		}
	    }
	    else if (memq_function(CAR(spec),output_names)) {
		spec_found_qm = T;
		temp_1 = CDDDR(spec);
		if (EQ(side,CAR(temp_1))) {
		    temp_1 = CDDDDR(spec);
		    temp_2 = FIXNUM_EQ(position_on_side,CAR(temp_1));
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    svref_new_value = 
			    copy_list_using_slot_value_conses_1(output_names);
		    SVREF(new_connection_item,FIX((SI_Long)2L)) = 
			    svref_new_value;
		}
	    }
	    goto next_loop_6;
	  end_loop_6:;
	}
	gensymed_symbol = new_connection;
	set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,Nil,
		T,gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum)),new_connection_item);
    }
    if (connection_replaced_via_stub_spec_qm);
    else {
	connection = new_connection;
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    output_port_connection = EQ(ISVREF(connection_to_be_replaced,
		    (SI_Long)3L),block) ? connection_to_be_replaced : 
		    new_connection;
	    input_port_connection = EQ(output_port_connection,
		    connection_to_be_replaced) ? new_connection : 
		    connection_to_be_replaced;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    skip_list = CDR(gensymed_symbol);
	    key_value = connection_to_be_replaced;
	    key_hash_value = SXHASH_SYMBOL_1(connection_to_be_replaced) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_10:
	    if (level < ab_loop_bind_)
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    skip_list = CDR(gensymed_symbol);
	    key_value = new_connection;
	    key_hash_value = SXHASH_SYMBOL_1(new_connection) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_13:
	    if (level < ab_loop_bind_)
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_14:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_15:
	    if ( !TRUEP(marked))
		goto end_loop_14;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_15;
	  end_loop_14:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_14;
	  end_loop_15:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_13;
	  end_loop_13:;
	    old_single_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    SVREF(old_single_item,FIX((SI_Long)3L)) = T;
	    if (EQ(input_port_connection,new_connection)) {
		svref_new_value = ISVREF(connection_item,(SI_Long)1L);
		SVREF(old_single_item,FIX((SI_Long)1L)) = svref_new_value;
	    }
	    else {
		svref_new_value = ISVREF(connection_item,(SI_Long)2L);
		SVREF(old_single_item,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    gensymed_symbol = connection_to_be_replaced;
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	    temp_1 = gensymed_symbol_1;
	    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),Nil);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    temp_1 = gensymed_symbol;
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
		    connection_to_be_replaced,temp_1,FIX((SI_Long)7L),
		    FIX(SXHASH_SYMBOL_1(connection_to_be_replaced) & 
		    IFIX(Most_positive_fixnum)));
	    reclaim_connection_item_1(connection_item);
	}
	else {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    connection_item_table = gensymed_symbol;
	    skip_list = CDR(connection_item_table);
	    key_value = connection_to_be_replaced;
	    key_hash_value = SXHASH_SYMBOL_1(connection_to_be_replaced) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_16:
	    if (level < ab_loop_bind_)
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_17:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_18:
	    if ( !TRUEP(marked))
		goto end_loop_17;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_18;
	  end_loop_17:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_17;
	  end_loop_18:
	  end_6:
	    level = level - (SI_Long)1L;
	    goto next_loop_16;
	  end_loop_16:;
	    connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    gensymed_symbol = connection_to_be_replaced;
	    set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,
		    Nil,T,gensymed_symbol,
		    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),Nil);
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
		    connection_to_be_replaced,connection_item_table,
		    FIX((SI_Long)7L),
		    FIX(SXHASH_SYMBOL_1(connection_to_be_replaced) & 
		    IFIX(Most_positive_fixnum)));
	    SVREF(connection_item,FIX((SI_Long)0L)) = new_connection;
	    gensymed_symbol = new_connection;
	    set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,
		    Nil,T,gensymed_symbol,
		    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),connection_item);
	}
    }
    update_runtime_structures_according_to_edit(1,block);
    update_runtime_structures_according_to_edit(1,connection_to_be_replaced);
    update_runtime_structures_according_to_edit(1,new_connection);
    flush_subworkspace_connection_posts_for_object(connection_to_be_replaced,
	    block,Nil);
    return determine_subworkspace_connection_posts_for_object(new_connection,
	    block);
}

/* GET-PORT-NAME-GIVEN-BLOCK-AND-CONNECTION */
Object get_port_name_given_block_and_connection varargs_1(int, n)
{
    Object block, connection;
    Object input_or_output, gensymed_symbol, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object connection_item, names;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(98,27);
    INIT_ARGS_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    input_or_output = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    skip_list = CDR(gensymed_symbol);
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
    if (EQ(input_or_output,Qinput))
	names = ISVREF(connection_item,(SI_Long)2L);
    else if (EQ(input_or_output,Qoutput))
	names = ISVREF(connection_item,(SI_Long)1L);
    else {
	names = ISVREF(connection_item,(SI_Long)1L);
	if (names);
	else
	    names = ISVREF(connection_item,(SI_Long)2L);
    }
    return VALUES_1(FIRST(names));
}

/* ADD-CONNECTION-IN-BLOCK */
Object add_connection_in_block(block,connection_to_be_added)
    Object block, connection_to_be_added;
{
    Object connection, gensymed_symbol, connections, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object connection_item, gensymed_symbol_1, slot_group_qm, tail, head;
    Object new_cons, temp_3, svref_arg_2, svref_new_value, gensymed_symbol_2;
    Object connection_table, workspace_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(98,28);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qconnections);
    decache_roles_for_entities_related_to_this_connection(connection_to_be_added);
    connection = connection_to_be_added;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
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
	temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	skip_list = CDR(gensymed_symbol);
	key_value = connection_to_be_added;
	key_hash_value = SXHASH_SYMBOL_1(connection_to_be_added) & 
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	SVREF(connection_item,FIX((SI_Long)3L)) = T;
    }
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	if (gensymed_symbol) {
	    gensymed_symbol = connection_to_be_added;
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	    temp_1 = gensymed_symbol_1;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,temp,
		    make_connection_item_1(connection_to_be_added));
	}
	else {
	    gensymed_symbol = block;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    tail = 
		    make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
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
	    M_CAR(gensymed_symbol_1) = Qconnection_item_table;
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
	    connection_table = gensymed_symbol_1;
	    connection_item = make_connection_item_1(connection_to_be_added);
	    gensymed_symbol_1 = connection_to_be_added;
	    set_skip_list_entry(connection_table,FIX((SI_Long)7L),Qeq,Nil,
		    T,gensymed_symbol_1,
		    FIX(SXHASH_SYMBOL_1(gensymed_symbol_1) & 
		    IFIX(Most_positive_fixnum)),connection_item);
	    gensymed_symbol_1 = connection_table;
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
	}
    }
    workspace_qm = get_workspace_if_any(block);
    if (workspace_qm)
	invalidate_layer_positions(workspace_qm);
    update_runtime_structures_according_to_edit(1,block);
    update_runtime_structures_according_to_edit(1,connection_to_be_added);
    return determine_subworkspace_connection_posts_for_object(connection_to_be_added,
	    block);
}

/* DELETE-CONNECTION-IN-BLOCK */
Object delete_connection_in_block(block,connection_to_be_deleted,
	    remove_subworkspace_connection_posts_if_appropriate_qm)
    Object block, connection_to_be_deleted;
    Object remove_subworkspace_connection_posts_if_appropriate_qm;
{
    Object gensymed_symbol, connection_item_table, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object connection_item;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(98,29);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qconnections);
    decache_roles_for_entities_related_to_this_connection(connection_to_be_deleted);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    connection_item_table = gensymed_symbol;
    if (connection_item_table) {
	skip_list = CDR(connection_item_table);
	key_value = connection_to_be_deleted;
	key_hash_value = SXHASH_SYMBOL_1(connection_to_be_deleted) & 
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
	connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (connection_item) {
	    gensymed_symbol = connection_to_be_deleted;
	    set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,
		    Nil,T,gensymed_symbol,
		    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),Nil);
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
		    connection_to_be_deleted,connection_item_table,
		    FIX((SI_Long)7L),
		    FIX(SXHASH_SYMBOL_1(connection_to_be_deleted) & 
		    IFIX(Most_positive_fixnum)));
	    reclaim_connection_item_1(connection_item);
	}
    }
    update_runtime_structures_according_to_edit(1,block);
    update_runtime_structures_according_to_edit(1,connection_to_be_deleted);
    return flush_subworkspace_connection_posts_for_object(connection_to_be_deleted,
	    block,remove_subworkspace_connection_posts_if_appropriate_qm);
}

/* LOWER-CONNECTION-FRAME-TO-BOTTOM */
Object lower_connection_frame_to_bottom(connection_frame_1)
    Object connection_frame_1;
{
    x_note_fn_call(98,30);
    return VALUES_1(Nil);
}

/* GET-BLOCK-AT-OTHER-END-OF-CONNECTION */
Object get_block_at_other_end_of_connection(connection,block)
    Object connection, block;
{
    x_note_fn_call(98,31);
    if (EQ(ISVREF(connection,(SI_Long)3L),block))
	return VALUES_1(ISVREF(connection,(SI_Long)2L));
    else
	return VALUES_1(ISVREF(connection,(SI_Long)3L));
}

/* CONNECTION-CONNECTED-TO-BLOCK-P */
Object connection_connected_to_block_p(connection,block)
    Object connection, block;
{
    Object temp;

    x_note_fn_call(98,32);
    temp = EQ(block,ISVREF(connection,(SI_Long)3L)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(block,ISVREF(connection,(SI_Long)2L)) ? T : Nil);
}

/* GET-DIRECTION-OF-CONNECTION */
Object get_direction_of_connection varargs_1(int, n)
{
    Object connection, block;
    Object even_if_not_directed_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(98,33);
    INIT_ARGS_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    block = REQUIRED_ARG_nonrelocating();
    even_if_not_directed_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
	    (SI_Long)1L)) || even_if_not_directed_qm) {
	if (EQ(ISVREF(connection,(SI_Long)3L),block))
	    return VALUES_1(Qoutput);
	else
	    return VALUES_1(Qinput);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdiagonal;           /* diagonal */

/* GET-STYLE-OF-CONNECTION */
Object get_style_of_connection(connection)
    Object connection;
{
    Object plist;

    x_note_fn_call(98,34);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal))
	return VALUES_1(Qdiagonal);
    else
	return VALUES_1(Qorthogonal);
}

/* GET-POSITION-AT-THIS-END-OF-CONNECTION */
Object get_position_at_this_end_of_connection(connection,block)
    Object connection, block;
{
    x_note_fn_call(98,35);
    if (EQ(ISVREF(connection,(SI_Long)2L),block))
	return VALUES_1(ISVREF(connection,(SI_Long)4L));
    else
	return VALUES_1(ISVREF(connection,(SI_Long)5L));
}

/* SET-INPUT-END-OF-CONNECTION */
Object set_input_end_of_connection(connection,block,side,position_on_side)
    Object connection, block, side, position_on_side;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,36);
    if (EQ(side,Qtop))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(side,Qleft))
	gensymed_symbol = (SI_Long)1L;
    else if (EQ(side,Qbottom))
	gensymed_symbol = (SI_Long)2L;
    else
	gensymed_symbol = (SI_Long)3L;
    gensymed_symbol_1 = IFIX(position_on_side) << (SI_Long)2L;
    return set_input_end_of_connection_1(connection,block,
	    FIX(gensymed_symbol + gensymed_symbol_1));
}

/* SET-INPUT-END-OF-CONNECTION-1 */
Object set_input_end_of_connection_1(connection,block,end_position)
    Object connection, block, end_position;
{
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(98,37);
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    SVREF(connection,FIX((SI_Long)3L)) = block;
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    SVREF(connection,FIX((SI_Long)5L)) = end_position;
    return set_or_clear_connection_transient_if_necessary(connection,block,
	    ISVREF(connection,(SI_Long)2L));
}

/* SET-OUTPUT-END-OF-CONNECTION */
Object set_output_end_of_connection(connection,block,side,position_on_side)
    Object connection, block, side, position_on_side;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,38);
    if (EQ(side,Qtop))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(side,Qleft))
	gensymed_symbol = (SI_Long)1L;
    else if (EQ(side,Qbottom))
	gensymed_symbol = (SI_Long)2L;
    else
	gensymed_symbol = (SI_Long)3L;
    gensymed_symbol_1 = IFIX(position_on_side) << (SI_Long)2L;
    return set_output_end_of_connection_1(connection,block,
	    FIX(gensymed_symbol + gensymed_symbol_1));
}

/* SET-OUTPUT-END-OF-CONNECTION-1 */
Object set_output_end_of_connection_1(connection,block,end_position)
    Object connection, block, end_position;
{
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(98,39);
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    SVREF(connection,FIX((SI_Long)2L)) = block;
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    SVREF(connection,FIX((SI_Long)4L)) = end_position;
    return set_or_clear_connection_transient_if_necessary(connection,block,
	    ISVREF(connection,(SI_Long)3L));
}

/* SET-OR-CLEAR-CONNECTION-TRANSIENT-IF-NECESSARY */
Object set_or_clear_connection_transient_if_necessary(connection,block1,block2)
    Object connection, block1, block2;
{
    Object x2;
    char temp;

    x_note_fn_call(98,40);
    if (SIMPLE_VECTOR_P(block1) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block1)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(block1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(block1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (SIMPLE_VECTOR_P(block2) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block2)) > (SI_Long)2L &&  
		!EQ(ISVREF(block2,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block2,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	set_or_clear_connection_transient_if_necessary_1(block1,block2);
	set_or_clear_connection_transient_if_necessary_1(block2,block1);
    }
    return VALUES_1(connection);
}

/* SET-OR-CLEAR-CONNECTION-TRANSIENT-IF-NECESSARY-1 */
Object set_or_clear_connection_transient_if_necessary_1(block_to_check,
	    block_at_other_end)
    Object block_to_check, block_at_other_end;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp;

    x_note_fn_call(98,41);
    sub_class_bit_vector = ISVREF(ISVREF(block_at_other_end,(SI_Long)1L),
	    (SI_Long)19L);
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
	if ((SI_Long)0L != (IFIX(ISVREF(block_to_check,(SI_Long)5L)) & 
		(SI_Long)262144L)) {
	    svref_new_value = IFIX(ISVREF(block_at_other_end,(SI_Long)5L)) 
		    | (SI_Long)262144L;
	    return VALUES_1(ISVREF(block_at_other_end,(SI_Long)5L) = 
		    FIX(svref_new_value));
	}
	else {
	    svref_new_value = IFIX(ISVREF(block_at_other_end,(SI_Long)5L)) 
		    &  ~(SI_Long)262144L;
	    return VALUES_1(ISVREF(block_at_other_end,(SI_Long)5L) = 
		    FIX(svref_new_value));
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qtransparent;        /* transparent */

static Object Kpaint_infered_from_xor;  /* :paint-infered-from-xor */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qconnection_color_pattern;  /* connection-color-pattern */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Kxor;                /* :xor */

static Object Qdraw_connection;    /* draw-connection */

/* CHANGE-COLOR-PATTERN-OF-CONNECTION */
Object change_color_pattern_of_connection(connection_frame_1,
	    note_as_kb_state_change_qm,connection_color_change_pattern)
    Object connection_frame_1, note_as_kb_state_change_qm;
    Object connection_color_change_pattern;
{
    Object cross_section_pattern, temp, old_color_pattern, new_color_pattern;
    Object cross_section_stripes, any_changes_noticed_qm, region;
    Object color_or_listed_color, ab_loop_list_, color;
    Object new_region_and_color_qm, ab_loop_desetq_, connection;
    Object gensymed_symbol, workspace_qm, becoming_transparent_qm, element;
    Object ab_loop_it_, do_not_note_permanent_changes_p, x2, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, changed_regions;
    Object frame_transform_block, sub_class_bit_vector;
    Object changing_colors_of_graphic_elements_qm;
    Object current_drawing_transfer_mode, this_block, superblock_qm, left, top;
    Object right, bottom;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long edge_overflow_if_any;
    char temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(98,42);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    3);
      cross_section_pattern = ISVREF(connection_frame_1,(SI_Long)20L);
      temp = CAAR(cross_section_pattern);
      old_color_pattern = CONSP(temp) ? CAR(cross_section_pattern) : Nil;
      new_color_pattern = 
	      copy_tree_using_slot_value_conses_1(old_color_pattern);
      cross_section_pattern = ISVREF(connection_frame_1,(SI_Long)20L);
      temp = CAAR(cross_section_pattern);
      cross_section_stripes = 
	      copy_tree_using_slot_value_conses_1(CONSP(temp) ? 
	      CDR(cross_section_pattern) : cross_section_pattern);
      any_changes_noticed_qm = Nil;
      region = Nil;
      color_or_listed_color = Nil;
      ab_loop_list_ = connection_color_change_pattern;
      color = Nil;
      new_region_and_color_qm = Nil;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      region = CAR(ab_loop_desetq_);
      color_or_listed_color = CDR(ab_loop_desetq_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      color = ATOM(color_or_listed_color) ? color_or_listed_color : 
	      CAR(color_or_listed_color);
      new_region_and_color_qm = assq_function(region,new_color_pattern);
      if ( !TRUEP(new_region_and_color_qm))
	  warn_of_missing_color_region(connection_frame_1,region);
      else if (EQ(CAR(new_region_and_color_qm),CDR(new_region_and_color_qm)))
	  warn_of_unnamed_color_region(connection_frame_1,region);
      else {
	  if ( !EQ(color,CDR(new_region_and_color_qm)))
	      any_changes_noticed_qm = T;
	  M_CDR(new_region_and_color_qm) = color;
      }
      goto next_loop;
    end_loop:
      connection = ISVREF(connection_frame_1,(SI_Long)21L);
      gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(connection,(SI_Long)2L),
	      (SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      workspace_qm = gensymed_symbol;
      if (ATOM(new_color_pattern))
	  becoming_transparent_qm = EQ(new_color_pattern,Qtransparent) ? T 
		  : Nil;
      else {
	  element = Nil;
	  ab_loop_list_ = new_color_pattern;
	  color = Nil;
	  ab_loop_it_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  element = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  color = ATOM(element) ? element : CDR(element);
	  ab_loop_it_ = EQ(color,Qtransparent) ? T : Nil;
	  if (ab_loop_it_) {
	      becoming_transparent_qm = ab_loop_it_;
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  becoming_transparent_qm = Qnil;
	end_1:;
      }
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      2);
	if ( !TRUEP(any_changes_noticed_qm)) {
	    reclaim_slot_value_tree_1(new_color_pattern);
	    reclaim_slot_value_tree_1(cross_section_stripes);
	}
	else {
	    if (EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) 
		    && EQ(Current_drawing_priority,
		    Kdraw_as_late_as_possible) &&  
		    !TRUEP(becoming_transparent_qm)) {
		if (SIMPLE_VECTOR_P(connection) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			(SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(connection,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 =  !(temp_1 ? (SI_Long)0L != 
			(IFIX(ISVREF(connection,(SI_Long)5L)) & 
			(SI_Long)1024L) : 
			TRUEP(render_connection_in_xor_overlay_p_function(connection)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(connection_frame_1,
			    Qconnection_color_pattern);
		change_slot_value(3,connection_frame_1,
			Qcross_section_pattern,new_color_pattern ? 
			slot_value_cons_1(new_color_pattern,
			cross_section_stripes) : cross_section_stripes);
		if (workspace_qm) {
		    region = Nil;
		    color = Nil;
		    ab_loop_list_ = connection_color_change_pattern;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    ab_loop_desetq_ = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    ab_loop_desetq_ = M_CAR(ab_loop_list_);
		    region = CAR(ab_loop_desetq_);
		    color = CDR(ab_loop_desetq_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    ab_loopvar__2 = gensym_cons_1(region,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    changed_regions = ab_loopvar_;
		    goto end_2;
		    changed_regions = Qnil;
		  end_2:;
		    invalidate_color_of_block(workspace_qm,
			    connection_frame_1,changed_regions);
		    reclaim_gensym_list_1(changed_regions);
		}
	    }
	    else {
		frame_transform_block = ISVREF(connection,(SI_Long)2L);
		if (EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) && becoming_transparent_qm) {
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			redraw_transfer_representations_of_block(connection,T);
		    if (Note_as_kb_state_change_qm)
			note_kb_state_change(connection_frame_1,
				Qconnection_color_pattern);
		    change_slot_value(3,connection_frame_1,
			    Qcross_section_pattern,new_color_pattern ? 
			    slot_value_cons_1(new_color_pattern,
			    cross_section_stripes) : cross_section_stripes);
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			redraw_transfer_representations_of_block(connection,
				Nil);
		    invalidate_region_for_block_or_connection(connection);
		}
		else {
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			sub_class_bit_vector = ISVREF(ISVREF(connection,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Entity_class_description,
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
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
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
		    edge_overflow_if_any = temp_1 ? (SI_Long)1L : (SI_Long)0L;
		    changing_colors_of_graphic_elements_qm = T;
		    current_drawing_transfer_mode = 
			    Current_drawing_transfer_mode;
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			this_block = connection;
			superblock_qm = Nil;
		      next_loop_3:
			gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,
				(SI_Long)14L));
			gensymed_symbol = gensymed_symbol ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol,
				(SI_Long)5L)) : Nil;
			superblock_qm = gensymed_symbol;
			if ( !TRUEP(superblock_qm)) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(this_block,(SI_Long)1L),
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Workspace_class_description,
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
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp_1 = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp_1 = TRUEP(Nil);
			    workspace_qm = temp_1 ? this_block : Nil;
			    goto end_3;
			}
			this_block = superblock_qm;
			goto next_loop_3;
		      end_loop_3:
			workspace_qm = Qnil;
		      end_3:;
		    }
		    else
			workspace_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
			      0);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? (SI_Long)0L != 
				(IFIX(ISVREF(connection,(SI_Long)5L)) & 
				(SI_Long)1024L) : 
				TRUEP(render_connection_in_xor_overlay_p_function(connection)))
			    Current_drawing_transfer_mode = Kxor;
			result = local_edges_of_block_or_connection(connection);
			MVS_4(result,left,top,right,bottom);
			update_images(11,Nil,connection,
				frame_transform_block,left,top,
				FIX(IFIX(right) + edge_overflow_if_any),
				FIX(IFIX(bottom) + edge_overflow_if_any),
				Nil,Qdraw_connection,connection,
				new_color_pattern);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    redraw_transfer_representations_of_block(connection,
				    T);
			if (Note_as_kb_state_change_qm)
			    note_kb_state_change(connection_frame_1,
				    Qconnection_color_pattern);
			change_slot_value(3,connection_frame_1,
				Qcross_section_pattern,new_color_pattern ? 
				slot_value_cons_1(new_color_pattern,
				cross_section_stripes) : 
				cross_section_stripes);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    redraw_transfer_representations_of_block(connection,
				    Nil);
			if ( !EQ(Current_drawing_transfer_mode,
				Kpaint_infered_from_xor)) {
			    if (SIMPLE_VECTOR_P(connection) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(connection,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(connection,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(connection,(SI_Long)1L),
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Meter_class_description,
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
					superior_class_bit_number & 
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
			if (temp_1 ? TRUEP(workspace_qm) : TRUEP(Nil)) {
			    region = 
				    bounding_region_of_block_or_connection(get_ruling_for_meter(connection));
			    invalidate_region_of_workspace(2,workspace_qm,
				    region);
			    reclaim_region(region);
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
	    }
	}
      POP_SPECIAL();
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qstripe_color;       /* stripe-color */

/* CHANGE-COLOR-OF-CONNECTION */
Object change_color_of_connection(connection_frame_1,
	    note_as_kb_state_change_qm,new_color)
    Object connection_frame_1, note_as_kb_state_change_qm, new_color;
{
    Object cross_section_pattern, temp, new_cross_section_regions;
    Object new_cross_section_stripes, any_changes_noticed_qm;
    Object region_color_pair, ab_loop_list_, color, region_width_pair;
    Object region_or_color, connection, gensymed_symbol, workspace_qm;
    Object do_not_note_permanent_changes_p, x2, changed_regions;
    Object frame_transform_block, sub_class_bit_vector;
    Object changing_colors_of_graphic_elements_qm;
    Object current_drawing_transfer_mode, this_block, superblock_qm, left, top;
    Object right, bottom, region;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long edge_overflow_if_any;
    char becoming_transparent_qm, temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(98,43);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    3);
      cross_section_pattern = ISVREF(connection_frame_1,(SI_Long)20L);
      temp = CAAR(cross_section_pattern);
      new_cross_section_regions = 
	      copy_tree_using_slot_value_conses_1(CONSP(temp) ? 
	      CAR(cross_section_pattern) : Nil);
      cross_section_pattern = ISVREF(connection_frame_1,(SI_Long)20L);
      temp = CAAR(cross_section_pattern);
      new_cross_section_stripes = 
	      copy_tree_using_slot_value_conses_1(CONSP(temp) ? 
	      CDR(cross_section_pattern) : cross_section_pattern);
      any_changes_noticed_qm = Nil;
      region_color_pair = Nil;
      ab_loop_list_ = new_cross_section_regions;
      color = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      region_color_pair = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      color = CDR(region_color_pair);
      if ( !EQ(color,new_color)) {
	  any_changes_noticed_qm = T;
	  M_CDR(region_color_pair) = new_color;
      }
      goto next_loop;
    end_loop:;
      region_width_pair = Nil;
      ab_loop_list_ = new_cross_section_stripes;
      region_or_color = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      region_width_pair = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      region_or_color = CAR(region_width_pair);
      if ( !TRUEP(assq_function(region_or_color,
	      new_cross_section_regions)) &&  !EQ(region_or_color,new_color)) {
	  any_changes_noticed_qm = T;
	  M_CAR(region_width_pair) = new_color;
      }
      goto next_loop_1;
    end_loop_1:;
      connection = ISVREF(connection_frame_1,(SI_Long)21L);
      gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(connection,(SI_Long)2L),
	      (SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      workspace_qm = gensymed_symbol;
      becoming_transparent_qm = EQ(new_color,Qtransparent);
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      2);
	if ( !TRUEP(any_changes_noticed_qm)) {
	    reclaim_slot_value_tree_1(new_cross_section_regions);
	    result = reclaim_slot_value_tree_1(new_cross_section_stripes);
	}
	else {
	    if (EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) 
		    && EQ(Current_drawing_priority,
		    Kdraw_as_late_as_possible) &&  !becoming_transparent_qm) {
		if (SIMPLE_VECTOR_P(connection) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			(SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(connection,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 =  !(temp_1 ? (SI_Long)0L != 
			(IFIX(ISVREF(connection,(SI_Long)5L)) & 
			(SI_Long)1024L) : 
			TRUEP(render_connection_in_xor_overlay_p_function(connection)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		if (Note_as_kb_state_change_qm)
		    note_kb_state_change(connection_frame_1,Qstripe_color);
		change_slot_value(3,connection_frame_1,
			Qcross_section_pattern,new_cross_section_regions ? 
			slot_value_cons_1(new_cross_section_regions,
			new_cross_section_stripes) : 
			new_cross_section_stripes);
		if (workspace_qm) {
		    changed_regions = gensym_cons_1(Qstripe_color,Nil);
		    invalidate_color_of_block(workspace_qm,
			    connection_frame_1,changed_regions);
		    result = reclaim_gensym_list_1(changed_regions);
		}
		else
		    result = VALUES_1(Nil);
	    }
	    else {
		frame_transform_block = ISVREF(connection,(SI_Long)2L);
		if (EQ(Current_drawing_transfer_mode,
			Kpaint_infered_from_xor) && becoming_transparent_qm) {
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			redraw_transfer_representations_of_block(connection,T);
		    if (Note_as_kb_state_change_qm)
			note_kb_state_change(connection_frame_1,Qstripe_color);
		    temp = change_slot_value(3,connection_frame_1,
			    Qcross_section_pattern,
			    new_cross_section_regions ? 
			    slot_value_cons_1(new_cross_section_regions,
			    new_cross_section_stripes) : 
			    new_cross_section_stripes);
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			redraw_transfer_representations_of_block(connection,
				Nil);
		    invalidate_region_for_block_or_connection(connection);
		    result = VALUES_1(temp);
		}
		else {
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			sub_class_bit_vector = ISVREF(ISVREF(connection,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Entity_class_description,
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
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
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
		    edge_overflow_if_any = temp_1 ? (SI_Long)1L : (SI_Long)0L;
		    changing_colors_of_graphic_elements_qm = T;
		    current_drawing_transfer_mode = 
			    Current_drawing_transfer_mode;
		    if (SIMPLE_VECTOR_P(connection) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(connection,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			this_block = connection;
			superblock_qm = Nil;
		      next_loop_2:
			gensymed_symbol = ACCESS_ONCE(ISVREF(this_block,
				(SI_Long)14L));
			gensymed_symbol = gensymed_symbol ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol,
				(SI_Long)5L)) : Nil;
			superblock_qm = gensymed_symbol;
			if ( !TRUEP(superblock_qm)) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(this_block,(SI_Long)1L),
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Workspace_class_description,
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
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp_1 = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp_1 = TRUEP(Nil);
			    workspace_qm = temp_1 ? this_block : Nil;
			    goto end_1;
			}
			this_block = superblock_qm;
			goto next_loop_2;
		      end_loop_2:
			workspace_qm = Qnil;
		      end_1:;
		    }
		    else
			workspace_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
			      0);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? (SI_Long)0L != 
				(IFIX(ISVREF(connection,(SI_Long)5L)) & 
				(SI_Long)1024L) : 
				TRUEP(render_connection_in_xor_overlay_p_function(connection)))
			    Current_drawing_transfer_mode = Kxor;
			result = local_edges_of_block_or_connection(connection);
			MVS_4(result,left,top,right,bottom);
			update_images(11,Nil,connection,
				frame_transform_block,left,top,
				FIX(IFIX(right) + edge_overflow_if_any),
				FIX(IFIX(bottom) + edge_overflow_if_any),
				Nil,Qdraw_connection,connection,new_color);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    redraw_transfer_representations_of_block(connection,
				    T);
			if (Note_as_kb_state_change_qm)
			    note_kb_state_change(connection_frame_1,
				    Qstripe_color);
			change_slot_value(3,connection_frame_1,
				Qcross_section_pattern,
				new_cross_section_regions ? 
				slot_value_cons_1(new_cross_section_regions,
				new_cross_section_stripes) : 
				new_cross_section_stripes);
			if (SIMPLE_VECTOR_P(connection) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				> (SI_Long)2L &&  !EQ(ISVREF(connection,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(connection,(SI_Long)1L);
			    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    redraw_transfer_representations_of_block(connection,
				    Nil);
			if ( !EQ(Current_drawing_transfer_mode,
				Kpaint_infered_from_xor)) {
			    if (SIMPLE_VECTOR_P(connection) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(connection,(SI_Long)1L),
				    Qavailable_frame_vector)) {
				x2 = ISVREF(connection,(SI_Long)1L);
				temp_1 = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? TRUEP(x2) : TRUEP(Qnil);
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(connection,(SI_Long)1L),
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Meter_class_description,
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
					superior_class_bit_number & 
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
			if (temp_1 ? TRUEP(workspace_qm) : TRUEP(Nil)) {
			    region = 
				    bounding_region_of_block_or_connection(get_ruling_for_meter(connection));
			    invalidate_region_of_workspace(2,workspace_qm,
				    region);
			    result = reclaim_region(region);
			}
			else
			    result = VALUES_1(Nil);
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-CONNECTION-LAYER-POSITION */
Object get_connection_layer_position(connection)
    Object connection;
{
    Object block_for_connection_qm, workspace_qm;

    x_note_fn_call(98,44);
    block_for_connection_qm = ISVREF(connection,(SI_Long)3L);
    if (block_for_connection_qm) {
	workspace_qm = get_workspace_if_any(block_for_connection_qm);
	if (workspace_qm) {
	    ensure_layer_positions(workspace_qm);
	    return VALUES_1(ISVREF(connection,(SI_Long)11L));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-CONNECTIONS-FOR-BLOCK */
Object draw_connections_for_block(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,45);
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      draw_connection(connection,Nil);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* UPDATE-CONNECTION-IMAGES */
Object update_connection_images(erase_qm,workspace_qm,connection)
    Object erase_qm, workspace_qm, connection;
{
    x_note_fn_call(98,46);
    if (workspace_qm)
	update_connection_images_1(erase_qm,workspace_qm,connection);
    if ( !TRUEP(erase_qm))
	return recompute_selection_highlights(connection);
    else
	return VALUES_1(Nil);
}

static Object Kconnection_bleeding;  /* :connection-bleeding */

/* UPDATE-CONNECTION-IMAGES-1 */
Object update_connection_images_1(erase_qm,workspace,connection)
    Object erase_qm, workspace, connection;
{
    Object gensymed_symbol, extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Object bleeding_hack;
    Declare_special(4);
    Object result;

    x_note_fn_call(98,47);
    if (ISVREF(workspace,(SI_Long)16L)) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	extreme_left_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	extreme_top_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	extreme_right_edge_so_far = gensymed_symbol;
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	extreme_bottom_edge_so_far = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Extreme_bottom_edge_so_far,Qextreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Extreme_right_edge_so_far,Qextreme_right_edge_so_far,extreme_right_edge_so_far,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Extreme_top_edge_so_far,Qextreme_top_edge_so_far,extreme_top_edge_so_far,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Extreme_left_edge_so_far,Qextreme_left_edge_so_far,extreme_left_edge_so_far,
		      0);
		update_extreme_edges_from_connection(connection);
		bleeding_hack = Kconnection_bleeding;
		result = update_images(11,erase_qm,connection,workspace,
			Extreme_left_edge_so_far,Extreme_top_edge_so_far,
			Extreme_right_edge_so_far,
			Extreme_bottom_edge_so_far,bleeding_hack,
			Qdraw_connection,connection,Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_connection_subrectangle_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_connection_subrectangle_structures, Qchain_of_available_connection_subrectangle_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_subrectangle_structure_count, Qconnection_subrectangle_structure_count);

Object Chain_of_available_connection_subrectangle_structures_vector = UNBOUND;

/* CONNECTION-SUBRECTANGLE-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object connection_subrectangle_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(98,48);
    temp = Connection_subrectangle_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CONNECTION-SUBRECTANGLE-STRUCTURE-COUNT */
Object outstanding_connection_subrectangle_structure_count()
{
    Object def_structure_connection_subrectangle_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,49);
    gensymed_symbol = IFIX(Connection_subrectangle_structure_count);
    def_structure_connection_subrectangle_structure_variable = 
	    Chain_of_available_connection_subrectangle_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_connection_subrectangle_structure_variable))
	goto end_loop;
    def_structure_connection_subrectangle_structure_variable = 
	    ISVREF(def_structure_connection_subrectangle_structure_variable,
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

/* RECLAIM-CONNECTION-SUBRECTANGLE-STRUCTURE-1 */
Object reclaim_connection_subrectangle_structure_1(connection_subrectangle_structure)
    Object connection_subrectangle_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(98,50);
    inline_note_reclaim_cons(connection_subrectangle_structure,Nil);
    temp = 
	    ISVREF(Chain_of_available_connection_subrectangle_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(connection_subrectangle_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_connection_subrectangle_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = connection_subrectangle_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CONNECTION-SUBRECTANGLE-STRUCTURE */
Object reclaim_structure_for_connection_subrectangle_structure(connection_subrectangle_structure)
    Object connection_subrectangle_structure;
{
    x_note_fn_call(98,51);
    return reclaim_connection_subrectangle_structure_1(connection_subrectangle_structure);
}

static Object Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct;  /* g2-defstruct-structure-name::connection-subrectangle-structure-g2-struct */

/* MAKE-PERMANENT-CONNECTION-SUBRECTANGLE-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_connection_subrectangle_structure_structure_internal()
{
    Object def_structure_connection_subrectangle_structure_variable;
    Object defstruct_g2_connection_subrectangle_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(98,52);
    def_structure_connection_subrectangle_structure_variable = Nil;
    atomic_incff_symval(Qconnection_subrectangle_structure_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_connection_subrectangle_structure_variable = Nil;
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
	defstruct_g2_connection_subrectangle_structure_variable = the_array;
	SVREF(defstruct_g2_connection_subrectangle_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct;
	def_structure_connection_subrectangle_structure_variable = 
		defstruct_g2_connection_subrectangle_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_connection_subrectangle_structure_variable);
}

/* MAKE-CONNECTION-SUBRECTANGLE-STRUCTURE-1 */
Object make_connection_subrectangle_structure_1(subrectangle_width)
    Object subrectangle_width;
{
    Object def_structure_connection_subrectangle_structure_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(98,53);
    def_structure_connection_subrectangle_structure_variable = 
	    ISVREF(Chain_of_available_connection_subrectangle_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_connection_subrectangle_structure_variable) {
	svref_arg_1 = 
		Chain_of_available_connection_subrectangle_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_connection_subrectangle_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_connection_subrectangle_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct;
    }
    else
	def_structure_connection_subrectangle_structure_variable = 
		make_permanent_connection_subrectangle_structure_structure_internal();
    inline_note_allocate_cons(def_structure_connection_subrectangle_structure_variable,
	    Nil);
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)3L)) = subrectangle_width;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_connection_subrectangle_structure_variable,
	    FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_connection_subrectangle_structure_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_distance_between_fins, Qminimum_distance_between_fins);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_distance_between_fins, Qdesired_distance_between_fins);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_distance_between_fins_on_link, Qdesired_distance_between_fins_on_link);

DEFINE_VARIABLE_WITH_SYMBOL(Default_fin_length, Qdefault_fin_length);

/* CONNECTION-FIN-LENGTH */
Object connection_fin_length varargs_1(int, n)
{
    Object connection;
    Object total_width_qm, total_width, connection_frame_or_class, x2;
    Object cross_section_pattern, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, temp_2, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cross_section_stripe, width, ab_loop_list_, ab_loopvar_;
    Object ab_loop_desetq_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, fin_length;
    SI_Long temp_3;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(98,54);
    INIT_ARGS_nonrelocating();
    connection = REQUIRED_ARG_nonrelocating();
    total_width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (connection_has_arrows_p(connection)) {
	total_width = total_width_qm;
	if (total_width);
	else {
	    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
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
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
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
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_2,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_8:
			if ( !TRUEP(marked))
			    goto end_loop_7;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
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
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_10:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_11:
			if ( !TRUEP(marked))
			    goto end_loop_10;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
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
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_5;
		    goto next_loop_13;
		  end_loop_14:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
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
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_2,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_16:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_17:
		    if ( !TRUEP(marked))
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
			goto end_6;
		    goto next_loop_16;
		  end_loop_17:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_15;
		  end_loop_15:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_19:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_20:
			if ( !TRUEP(marked))
			    goto end_loop_19;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_20;
		      end_loop_19:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_22:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_23:
			if ( !TRUEP(marked))
			    goto end_loop_22;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_23;
		      end_loop_22:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
	    cross_section_stripe = CONSP(temp_2) ? 
		    CDR(cross_section_pattern) : cross_section_pattern;
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
	    total_width = ab_loopvar_;
	    goto end_9;
	    total_width = Qnil;
	  end_9:;
	}
	fin_length = (SI_Long)3L * IFIX(total_width);
	temp_3 = IFIX(Default_fin_length);
	return VALUES_1(FIX(MAX(fin_length,temp_3)));
    }
    else
	return VALUES_1(Default_fin_length);
}

/* CONNECTION-TOTAL-WIDTH */
Object connection_total_width(connection)
    Object connection;
{
    Object connection_frame_or_class, x2, cross_section_pattern, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, cross_section_stripes, color, width, ab_loop_list_;
    Object ab_loopvar_, ab_loop_desetq_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(98,55);
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
	cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    temp_2 = CAAR(cross_section_pattern);
    cross_section_stripes = CONSP(temp_2) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    color = Nil;
    width = Nil;
    ab_loop_list_ = cross_section_stripes;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop_24:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_24;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
    goto next_loop_24;
  end_loop_24:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Orientation_horizontal_p, Qorientation_horizontal_p);

DEFINE_VARIABLE_WITH_SYMBOL(Init_orientation_horizontal_p, Qinit_orientation_horizontal_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_delta, Qcurrent_delta);

DEFINE_VARIABLE_WITH_SYMBOL(Cumulative_x_scaled_connection_stripe_width, Qcumulative_x_scaled_connection_stripe_width);

DEFINE_VARIABLE_WITH_SYMBOL(Cumulative_y_scaled_connection_stripe_width, Qcumulative_y_scaled_connection_stripe_width);

DEFINE_VARIABLE_WITH_SYMBOL(Cumulative_x_scaled_connection_stripe_half_width, Qcumulative_x_scaled_connection_stripe_half_width);

DEFINE_VARIABLE_WITH_SYMBOL(Cumulative_y_scaled_connection_stripe_half_width, Qcumulative_y_scaled_connection_stripe_half_width);

/* INITIALIZE-CUMULATIVE-SCALED-WIDTHS */
Object initialize_cumulative_scaled_widths(cross_section_stripes)
    Object cross_section_stripes;
{
    Object width, ab_loop_list_, cumulative_x, cumulative_y, ab_loop_desetq_;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;

    x_note_fn_call(98,56);
    width = Nil;
    ab_loop_list_ = cross_section_stripes;
    cumulative_x = FIX((SI_Long)0L);
    cumulative_y = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = (SI_Long)1L;
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(width);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
	    FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,width)) 
		+ (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,width));
    cumulative_x = add(FIX(MAX(gensymed_symbol,gensymed_symbol_1)),
	    cumulative_x);
    gensymed_symbol = (SI_Long)1L;
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(width);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
	    FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,width)) 
		+ (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,width));
    cumulative_y = add(FIX(MAX(gensymed_symbol,gensymed_symbol_1)),
	    cumulative_y);
    goto next_loop;
  end_loop:
    Cumulative_x_scaled_connection_stripe_width = cumulative_x;
    Cumulative_y_scaled_connection_stripe_width = cumulative_y;
    Cumulative_x_scaled_connection_stripe_half_width = 
	    FIX(IFIX(Cumulative_x_scaled_connection_stripe_width) >>  -  - 
	    (SI_Long)1L);
    Cumulative_y_scaled_connection_stripe_half_width = 
	    FIX(IFIX(Cumulative_y_scaled_connection_stripe_width) >>  -  - 
	    (SI_Long)1L);
    return VALUES_1(Cumulative_y_scaled_connection_stripe_half_width);
}

Object Connection_subrectangle_structures_for_drawing_kbprop = UNBOUND;

/* GENERATE-CONNECTION-SUBRECTANGLE-STRUCTURES */
Object generate_connection_subrectangle_structures(cross_section_pattern)
    Object cross_section_pattern;
{
    Object width, temp, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, forward_list, reversed_list;
    Object subrectangle_structure, reverse_list;

    x_note_fn_call(98,57);
    width = Nil;
    temp = CAAR(cross_section_pattern);
    ab_loop_list_ = CONSP(temp) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    connection_cons_1(make_connection_subrectangle_structure_1(width),
	    Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    forward_list = ab_loopvar_;
    goto end_1;
    forward_list = Qnil;
  end_1:;
    reversed_list = Nil;
    subrectangle_structure = Nil;
    ab_loop_list_ = forward_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    subrectangle_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reversed_list = connection_cons_1(subrectangle_structure,reversed_list);
    goto next_loop_1;
  end_loop_1:
    reverse_list = reversed_list;
    goto end_2;
    reverse_list = Qnil;
  end_2:;
    return connection_cons_1(forward_list,reverse_list);
}

/* RECLAIM-CONNECTION-SUBRECTANGLE-STRUCTURES */
Object reclaim_connection_subrectangle_structures(connection_subrectangle_structures)
    Object connection_subrectangle_structures;
{
    Object forward_list, connection_subrectangle_structure, ab_loop_list_;

    x_note_fn_call(98,58);
    if (connection_subrectangle_structures) {
	forward_list = CAR(connection_subrectangle_structures);
	connection_subrectangle_structure = Nil;
	ab_loop_list_ = forward_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection_subrectangle_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_connection_subrectangle_structure_1(connection_subrectangle_structure);
	goto next_loop;
      end_loop:;
	reclaim_connection_list_1(forward_list);
	reclaim_connection_list_1(CDR(connection_subrectangle_structures));
	return reclaim_connection_cons_1(connection_subrectangle_structures);
    }
    else
	return VALUES_1(Nil);
}

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

/* INITIALIZE-CONNECTION-SUBRECTANGLE-STRUCTURES */
Object initialize_connection_subrectangle_structures(cross_section_regions,
	    cross_section_stripes,connection_subrectangle_structures,
	    input_end_x_position,input_end_y_position,input_end_side,
	    initial_delta,change_to_this_color_or_color_pattern_qm)
    Object cross_section_regions, cross_section_stripes;
    Object connection_subrectangle_structures, input_end_x_position;
    Object input_end_y_position, input_end_side, initial_delta;
    Object change_to_this_color_or_color_pattern_qm;
{
    Object subrectangle_stable_axis_position;
    Object connection_subrectangle_structure, ab_loop_list_, region_or_color;
    Object ab_loop_list__1, width, recorded_color, desired_color;
    Object color_difference, ab_loop_desetq_, temp, color_value_1;
    Object color_value_2, svref_new_value, scaled_subrectangle_width;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long input_end_x_position_in_window, input_end_y_position_in_window;
    SI_Long subrectangle_variable_axis_begin_position, svref_new_value_1;

    x_note_fn_call(98,59);
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(input_end_x_position);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    input_end_x_position) && FIXNUM_LT(input_end_x_position,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		input_end_x_position)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		input_end_x_position));
    input_end_x_position_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(input_end_y_position);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    input_end_y_position) && FIXNUM_LT(input_end_y_position,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		input_end_y_position)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		input_end_y_position));
    input_end_y_position_in_window = gensymed_symbol + gensymed_symbol_1;
    if (EQ(input_end_side,Qright))
	subrectangle_stable_axis_position = IFIX(initial_delta) > 
		(SI_Long)0L ? FIX(input_end_y_position_in_window - 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width)) : 
		oddp(Cumulative_y_scaled_connection_stripe_width) ? 
		FIX(input_end_y_position_in_window + 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width) + 
		(SI_Long)1L) : FIX(input_end_y_position_in_window + 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width));
    else if (EQ(input_end_side,Qleft))
	subrectangle_stable_axis_position = IFIX(initial_delta) < 
		(SI_Long)0L ? 
		(oddp(Cumulative_y_scaled_connection_stripe_width) ? 
		FIX(input_end_y_position_in_window + 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width) + 
		(SI_Long)1L) : FIX(input_end_y_position_in_window + 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width))) : 
		FIX(input_end_y_position_in_window - 
		IFIX(Cumulative_y_scaled_connection_stripe_half_width));
    else if (EQ(input_end_side,Qtop))
	subrectangle_stable_axis_position = IFIX(initial_delta) < 
		(SI_Long)0L ? FIX(input_end_x_position_in_window - 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width)) : 
		oddp(Cumulative_y_scaled_connection_stripe_width) ? 
		FIX(input_end_x_position_in_window + 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width) + 
		(SI_Long)1L) : FIX(input_end_x_position_in_window + 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width));
    else
	subrectangle_stable_axis_position = IFIX(initial_delta) > 
		(SI_Long)0L ? 
		(oddp(Cumulative_x_scaled_connection_stripe_width) ? 
		FIX(input_end_x_position_in_window + 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width) + 
		(SI_Long)1L) : FIX(input_end_x_position_in_window + 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width))) : 
		FIX(input_end_x_position_in_window - 
		IFIX(Cumulative_x_scaled_connection_stripe_half_width));
    subrectangle_variable_axis_begin_position = EQ(input_end_side,Qright) 
	    || EQ(input_end_side,Qleft) ? input_end_x_position_in_window : 
	    input_end_y_position_in_window;
    connection_subrectangle_structure = Nil;
    ab_loop_list_ = connection_subrectangle_structures;
    region_or_color = Nil;
    ab_loop_list__1 = cross_section_stripes;
    width = Nil;
    recorded_color = Nil;
    desired_color = Nil;
    color_difference = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection_subrectangle_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    region_or_color = CAR(ab_loop_desetq_);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    width = ISVREF(connection_subrectangle_structure,(SI_Long)3L);
    if (change_to_this_color_or_color_pattern_qm) {
	temp = assq_function(region_or_color,cross_section_regions);
	temp = CDR(temp);
	if (temp);
	else
	    temp = region_or_color;
	recorded_color = temp;
    }
    else
	recorded_color = Qbackground;
    if ( !TRUEP(change_to_this_color_or_color_pattern_qm)) {
	temp = assq_function(region_or_color,cross_section_regions);
	temp = CDR(temp);
	if (temp);
	else
	    temp = region_or_color;
	desired_color = temp;
    }
    else if (SYMBOLP(change_to_this_color_or_color_pattern_qm))
	desired_color = change_to_this_color_or_color_pattern_qm;
    else {
	temp = assq_function(region_or_color,
		change_to_this_color_or_color_pattern_qm);
	temp = CDR(temp);
	if (temp);
	else
	    temp = region_or_color;
	desired_color = temp;
    }
    if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	if (EQ(recorded_color,Qbackground))
	    color_value_2 = Current_background_color_value;
	else if (EQ(recorded_color,Qforeground) || EQ(recorded_color,
		Qworkspace_foreground))
	    color_value_2 = Current_foreground_color_value;
	else if (EQ(recorded_color,Qtransparent))
	    color_value_2 = Current_background_color_value;
	else
	    color_value_2 = map_to_color_value(recorded_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,color_value_2);
    }
    else if (EQ(desired_color,recorded_color))
	color_difference = EQ(Current_drawing_transfer_mode,
		Kpaint_infered_from_xor) ? Transparent_color_value : 
		FIX((SI_Long)0L);
    else if (EQ(desired_color,Qtransparent))
	color_difference = EQ(Current_drawing_transfer_mode,
		Kpaint_infered_from_xor) ? Transparent_color_value : 
		FIX((SI_Long)0L);
    else if (EQ(recorded_color,Qtransparent)) {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,
		Current_background_color_value);
    }
    else {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	if (EQ(recorded_color,Qbackground))
	    color_value_2 = Current_background_color_value;
	else if (EQ(recorded_color,Qforeground) || EQ(recorded_color,
		Qworkspace_foreground))
	    color_value_2 = Current_foreground_color_value;
	else if (EQ(recorded_color,Qtransparent))
	    color_value_2 = Current_background_color_value;
	else
	    color_value_2 = map_to_color_value(recorded_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,color_value_2);
    }
    SVREF(connection_subrectangle_structure,FIX((SI_Long)1L)) = 
	    color_difference;
    if (EQ(recorded_color,Qbackground))
	svref_new_value = Current_background_color_value;
    else if (EQ(recorded_color,Qforeground) || EQ(recorded_color,
	    Qworkspace_foreground))
	svref_new_value = Current_foreground_color_value;
    else if (EQ(recorded_color,Qtransparent))
	svref_new_value = Current_background_color_value;
    else
	svref_new_value = map_to_color_value(recorded_color);
    SVREF(connection_subrectangle_structure,FIX((SI_Long)2L)) = 
	    svref_new_value;
    SVREF(connection_subrectangle_structure,FIX((SI_Long)8L)) = 
	    subrectangle_stable_axis_position;
    ISVREF(connection_subrectangle_structure,(SI_Long)6L) = 
	    FIX(subrectangle_variable_axis_begin_position);
    gensymed_symbol = (SI_Long)1L;
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(width);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
	    FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,width)) 
		+ (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,width));
    svref_new_value_1 = MAX(gensymed_symbol,gensymed_symbol_1);
    ISVREF(connection_subrectangle_structure,(SI_Long)4L) = 
	    FIX(svref_new_value_1);
    gensymed_symbol = (SI_Long)1L;
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(width);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
	    FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,width)) 
		+ (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,width));
    svref_new_value_1 = MAX(gensymed_symbol,gensymed_symbol_1);
    ISVREF(connection_subrectangle_structure,(SI_Long)5L) = 
	    FIX(svref_new_value_1);
    scaled_subrectangle_width = Orientation_horizontal_p ? 
	    ISVREF(connection_subrectangle_structure,(SI_Long)5L) : 
	    ISVREF(connection_subrectangle_structure,(SI_Long)4L);
    gensymed_symbol = IFIX(subrectangle_stable_axis_position);
    gensymed_symbol_1 = ((SI_Long)0L > IFIX(Current_delta) ? 
	    TRUEP(Orientation_horizontal_p) :  
	    !TRUEP(Orientation_horizontal_p)) ? 
	    IFIX(FIXNUM_NEGATE(scaled_subrectangle_width)) : 
	    IFIX(scaled_subrectangle_width);
    subrectangle_stable_axis_position = FIX(gensymed_symbol + 
	    gensymed_symbol_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qlink_2_delta;       /* link-2-delta */

/* SERVE-FIRST-CONNECTION-DELTA */
Object serve_first_connection_delta(connection,input_end_x,input_end_y,
	    output_end_x,output_end_y,initial_orientation_horizontal_p)
    Object connection, input_end_x, input_end_y, output_end_x, output_end_y;
    Object initial_orientation_horizontal_p;
{
    Object delta_or_deltas_qm, current_delta, next_delta, delta_continuation;
    Object stable_axis_position, variable_axis_begin_position;
    Object variable_axis_end_position, last_delta, orientation_horizontal_p;
    Object cumulative_scaled_width;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long output_end_x_in_window, input_end_x_in_window;
    SI_Long output_end_y_in_window, input_end_y_in_window, delta;
    Declare_special(2);
    Object result;

    x_note_fn_call(98,60);
    delta_or_deltas_qm = ISVREF(connection,(SI_Long)6L);
    current_delta = Nil;
    next_delta = Nil;
    delta_continuation = Nil;
    stable_axis_position = Nil;
    variable_axis_begin_position = Nil;
    variable_axis_end_position = Nil;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(output_end_x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,output_end_x) 
	    && FIXNUM_LT(output_end_x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		output_end_x)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		output_end_x));
    output_end_x_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(input_end_x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,input_end_x) 
	    && FIXNUM_LT(input_end_x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		input_end_x)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		input_end_x));
    input_end_x_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(output_end_y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,output_end_y) 
	    && FIXNUM_LT(output_end_y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		output_end_y)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		output_end_y));
    output_end_y_in_window = gensymed_symbol + gensymed_symbol_1;
    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_1 = IFIX(input_end_y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,input_end_y) 
	    && FIXNUM_LT(input_end_y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		input_end_y)) + (SI_Long)2048L;
	gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		input_end_y));
    input_end_y_in_window = gensymed_symbol + gensymed_symbol_1;
    PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,1);
      if (initial_orientation_horizontal_p) {
	  stable_axis_position = FIX(input_end_y_in_window);
	  variable_axis_begin_position = FIX(input_end_x_in_window);
      }
      else {
	  stable_axis_position = FIX(input_end_x_in_window);
	  variable_axis_begin_position = FIX(input_end_y_in_window);
      }
      if ( !TRUEP(delta_or_deltas_qm)) {
	  if (initial_orientation_horizontal_p) {
	      next_delta = FIX(output_end_y_in_window - input_end_y_in_window);
	      delta = output_end_x_in_window - input_end_x_in_window;
	      last_delta = next_delta;
	      orientation_horizontal_p = initial_orientation_horizontal_p;
	      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
		      0);
		cumulative_scaled_width = Orientation_horizontal_p ? 
			Cumulative_x_scaled_connection_stripe_width : 
			Cumulative_y_scaled_connection_stripe_width;
		Current_delta = initial_orientation_horizontal_p && 
			Orientation_horizontal_p ||  
			!TRUEP(initial_orientation_horizontal_p) &&  
			!TRUEP(Orientation_horizontal_p) ? 
			(oddp(cumulative_scaled_width) ? (delta > 
			(SI_Long)0L ? FIX(delta + (SI_Long)1L) : 
			FIX(delta)) : Orientation_horizontal_p ? 
			(IFIX(last_delta) < (SI_Long)0L ? (delta > 
			(SI_Long)0L ? FIX(delta) : FIX(delta - 
			(SI_Long)1L)) : delta > (SI_Long)0L ? FIX(delta + 
			(SI_Long)1L) : FIX(delta)) : IFIX(last_delta) > 
			(SI_Long)0L ? (delta > (SI_Long)0L ? FIX(delta) : 
			FIX(delta - (SI_Long)1L)) : delta > (SI_Long)0L ? 
			FIX(delta + (SI_Long)1L) : FIX(delta)) : FIX(delta);
	      POP_SPECIAL();
	  }
	  else {
	      next_delta = FIX(output_end_x_in_window - input_end_x_in_window);
	      delta = output_end_y_in_window - input_end_y_in_window;
	      last_delta = next_delta;
	      orientation_horizontal_p = initial_orientation_horizontal_p;
	      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
		      0);
		cumulative_scaled_width = Orientation_horizontal_p ? 
			Cumulative_x_scaled_connection_stripe_width : 
			Cumulative_y_scaled_connection_stripe_width;
		Current_delta = initial_orientation_horizontal_p && 
			Orientation_horizontal_p ||  
			!TRUEP(initial_orientation_horizontal_p) &&  
			!TRUEP(Orientation_horizontal_p) ? 
			(oddp(cumulative_scaled_width) ? (delta > 
			(SI_Long)0L ? FIX(delta + (SI_Long)1L) : 
			FIX(delta)) : Orientation_horizontal_p ? 
			(IFIX(last_delta) < (SI_Long)0L ? (delta > 
			(SI_Long)0L ? FIX(delta) : FIX(delta - 
			(SI_Long)1L)) : delta > (SI_Long)0L ? FIX(delta + 
			(SI_Long)1L) : FIX(delta)) : IFIX(last_delta) > 
			(SI_Long)0L ? (delta > (SI_Long)0L ? FIX(delta) : 
			FIX(delta - (SI_Long)1L)) : delta > (SI_Long)0L ? 
			FIX(delta + (SI_Long)1L) : FIX(delta)) : FIX(delta);
	      POP_SPECIAL();
	  }
	  if (IFIX(next_delta) == (SI_Long)0L)
	      next_delta = Nil;
	  delta_continuation = Qlink_2_delta;
	  variable_axis_end_position = 
		  FIXNUM_ADD(variable_axis_begin_position,Current_delta);
      }
      else {
	  result = compute_next_delta(connection,delta_or_deltas_qm, 
		  !TRUEP(initial_orientation_horizontal_p) ? T : Nil,
		  variable_axis_begin_position,FIX((SI_Long)0L),
		  stable_axis_position,FIX(output_end_x_in_window),
		  FIX(output_end_y_in_window));
	  MVS_2(result,Current_delta,delta_continuation);
	  if ( !TRUEP(Current_delta))
	      Current_delta = FIX((SI_Long)0L);
	  variable_axis_end_position = 
		  FIXNUM_ADD(variable_axis_begin_position,Current_delta);
	  result = compute_next_delta(connection,delta_continuation,
		  initial_orientation_horizontal_p,stable_axis_position,
		  variable_axis_begin_position,variable_axis_end_position,
		  FIX(output_end_x_in_window),FIX(output_end_y_in_window));
	  MVS_2(result,next_delta,delta_continuation);
      }
      result = VALUES_6(Current_delta,next_delta,stable_axis_position,
	      variable_axis_begin_position,variable_axis_end_position,
	      delta_continuation);
    POP_SPECIAL();
    return result;
}

/* SERVE-NEXT-CONNECTION-DELTA */
Object serve_next_connection_delta(connection,output_end_x,output_end_y,
	    stable_axis_position,variable_axis_end_position,
	    delta_continuation,old_next_delta)
    Object connection, output_end_x, output_end_y, stable_axis_position;
    Object variable_axis_end_position, delta_continuation, old_next_delta;
{
    Object current_delta, next_delta, next_delta_continuation;
    Object next_stable_axis_position, next_variable_axis_begin_position;
    Object next_variable_axis_end_position;
    SI_Long gensymed_symbol, gensymed_symbol_1, unshifted_result;
    SI_Long output_end_x_in_window, output_end_y_in_window;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,61);
    current_delta = old_next_delta;
    PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,0);
      next_delta = Nil;
      next_delta_continuation = Nil;
      next_stable_axis_position = variable_axis_end_position;
      next_variable_axis_begin_position = stable_axis_position;
      next_variable_axis_end_position = 
	      FIXNUM_ADD(next_variable_axis_begin_position,Current_delta);
      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
      if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	  gensymed_symbol_1 = IFIX(output_end_x);
      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	      Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	      Isqrt_of_most_positive_fixnum) && 
	      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	      output_end_x) && FIXNUM_LT(output_end_x,
	      Isqrt_of_most_positive_fixnum)) {
	  unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		  output_end_x)) + (SI_Long)2048L;
	  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
      }
      else
	  gensymed_symbol_1 = IFIX(scalef_function(Current_image_x_scale,
		  output_end_x));
      output_end_x_in_window = gensymed_symbol + gensymed_symbol_1;
      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	  gensymed_symbol_1 = IFIX(output_end_y);
      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	      Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	      Isqrt_of_most_positive_fixnum) && 
	      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	      output_end_y) && FIXNUM_LT(output_end_y,
	      Isqrt_of_most_positive_fixnum)) {
	  unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		  output_end_y)) + (SI_Long)2048L;
	  gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
      }
      else
	  gensymed_symbol_1 = IFIX(scalef_function(Current_image_y_scale,
		  output_end_y));
      output_end_y_in_window = gensymed_symbol + gensymed_symbol_1;
      result = compute_next_delta(connection,delta_continuation,
	      Orientation_horizontal_p,next_stable_axis_position,
	      next_variable_axis_begin_position,
	      next_variable_axis_end_position,FIX(output_end_x_in_window),
	      FIX(output_end_y_in_window));
      MVS_2(result,next_delta,next_delta_continuation);
      result = VALUES_6(Current_delta,next_delta,next_stable_axis_position,
	      next_variable_axis_begin_position,
	      next_variable_axis_end_position,next_delta_continuation);
    POP_SPECIAL();
    return result;
}

/* COMPUTE-NEXT-DELTA */
Object compute_next_delta(connection,delta_continuation,
	    orientation_horizontal_p_arg,next_stable_axis_position,
	    next_variable_axis_begin_position,
	    next_variable_axis_end_position,output_end_x_in_window,
	    output_end_y_in_window)
    Object connection, delta_continuation, orientation_horizontal_p_arg;
    Object next_stable_axis_position, next_variable_axis_begin_position;
    Object next_variable_axis_end_position, output_end_x_in_window;
    Object output_end_y_in_window;
{
    Object next_delta, next_delta_continuation, gensymed_symbol;
    Object possible_next_delta, possible_next_delta_continuation;
    Object number_of_zeros_swallowed;
    Object result;

    x_note_fn_call(98,62);
    result = compute_next_delta_1(delta_continuation,
	    orientation_horizontal_p_arg,next_stable_axis_position,
	    next_variable_axis_end_position,output_end_x_in_window,
	    output_end_y_in_window);
    MVS_2(result,next_delta,next_delta_continuation);
    gensymed_symbol = getfq_function_no_default(ISVREF(connection,
	    (SI_Long)9L),Qconnection_style);
    if ( !TRUEP(gensymed_symbol) || EQ(gensymed_symbol,Qorthogonal) ? 
	    TRUEP(next_delta_continuation) : TRUEP(Nil)) {
	result = compute_next_delta_swallowing_zeros(delta_continuation,
		orientation_horizontal_p_arg,next_stable_axis_position,
		next_variable_axis_begin_position,
		next_variable_axis_end_position,output_end_x_in_window,
		output_end_y_in_window);
	MVS_3(result,possible_next_delta,possible_next_delta_continuation,
		number_of_zeros_swallowed);
	if (IFIX(number_of_zeros_swallowed) != (SI_Long)0L) {
	    if (evenp(number_of_zeros_swallowed)) {
		next_delta = possible_next_delta;
		next_delta_continuation = possible_next_delta_continuation;
	    }
	}
    }
    return VALUES_2(next_delta,next_delta_continuation);
}

static Object Qlink_1_delta;       /* link-1-delta */

static Object Qlink_0_delta;       /* link-0-delta */

/* COMPUTE-NEXT-DELTA-1 */
Object compute_next_delta_1(delta_continuation,
	    orientation_horizontal_p_arg,next_stable_axis_position,
	    next_variable_axis_end_position,output_end_x_in_window,
	    output_end_y_in_window)
    Object delta_continuation, orientation_horizontal_p_arg;
    Object next_stable_axis_position, next_variable_axis_end_position;
    Object output_end_x_in_window, output_end_y_in_window;
{
    Object next_delta, next_delta_continuation, delta_in_workspace;
    Object orientation_horizontal_p, temp;
    SI_Long unshifted_result;
    Declare_special(1);

    x_note_fn_call(98,63);
    next_delta = Nil;
    next_delta_continuation = Nil;
    if (EQ(delta_continuation,Qlink_2_delta)) {
	next_delta = Nil;
	next_delta_continuation = Nil;
    }
    else if (EQ(delta_continuation,Qlink_1_delta)) {
	next_delta = 
		compute_delta_from_end_position(orientation_horizontal_p_arg,
		next_stable_axis_position,output_end_x_in_window,
		output_end_y_in_window);
	if (IFIX(next_delta) == (SI_Long)0L)
	    next_delta = Nil;
	next_delta_continuation = Qlink_2_delta;
    }
    else if (EQ(delta_continuation,Qlink_0_delta)) {
	next_delta = 
		compute_delta_from_end_position_link_1(orientation_horizontal_p_arg,
		next_stable_axis_position,next_variable_axis_end_position,
		output_end_x_in_window,output_end_y_in_window);
	next_delta_continuation = Qlink_1_delta;
    }
    else if (ATOM(delta_continuation)) {
	if (orientation_horizontal_p_arg) {
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		next_delta = delta_continuation;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    delta_continuation) && FIXNUM_LT(delta_continuation,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			delta_continuation)) + (SI_Long)2048L;
		next_delta = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		next_delta = scalef_function(Current_image_y_scale,
			delta_continuation);
	}
	else if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    next_delta = delta_continuation;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		delta_continuation) && FIXNUM_LT(delta_continuation,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    delta_continuation)) + (SI_Long)2048L;
	    next_delta = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    next_delta = scalef_function(Current_image_x_scale,
		    delta_continuation);
	next_delta_continuation = Qlink_0_delta;
    }
    else {
	delta_in_workspace = CAR(delta_continuation);
	orientation_horizontal_p = orientation_horizontal_p_arg;
	PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
		0);
	  if (Orientation_horizontal_p) {
	      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		  next_delta = delta_in_workspace;
	      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      Current_image_y_scale) && 
		      FIXNUM_LT(Current_image_y_scale,
		      Isqrt_of_most_positive_fixnum) && 
		      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      delta_in_workspace) && FIXNUM_LT(delta_in_workspace,
		      Isqrt_of_most_positive_fixnum)) {
		  unshifted_result = 
			  IFIX(FIXNUM_TIMES(Current_image_y_scale,
			  delta_in_workspace)) + (SI_Long)2048L;
		  next_delta = FIX(unshifted_result >>  -  - (SI_Long)12L);
	      }
	      else
		  next_delta = scalef_function(Current_image_y_scale,
			  delta_in_workspace);
	  }
	  else if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	      next_delta = delta_in_workspace;
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  Current_image_x_scale) && 
		  FIXNUM_LT(Current_image_x_scale,
		  Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  delta_in_workspace) && FIXNUM_LT(delta_in_workspace,
		  Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		      delta_in_workspace)) + (SI_Long)2048L;
	      next_delta = FIX(unshifted_result >>  -  - (SI_Long)12L);
	  }
	  else
	      next_delta = scalef_function(Current_image_x_scale,
		      delta_in_workspace);
	POP_SPECIAL();
	temp = CDR(delta_continuation);
	if (temp);
	else
	    temp = Qlink_0_delta;
	next_delta_continuation = temp;
    }
    return VALUES_2(next_delta,next_delta_continuation);
}

/* COMPUTE-NEXT-DELTA-SWALLOWING-ZEROS */
Object compute_next_delta_swallowing_zeros(next_delta_continuation,
	    orientation_horizontal_p_arg,next_stable_axis_position,
	    next_variable_axis_begin_position,
	    next_variable_axis_end_position,output_end_x_in_window,
	    output_end_y_in_window)
    Object next_delta_continuation, orientation_horizontal_p_arg;
    Object next_stable_axis_position, next_variable_axis_begin_position;
    Object next_variable_axis_end_position, output_end_x_in_window;
    Object output_end_y_in_window;
{
    Object zeros_to_swallow_qm, next_delta;
    SI_Long number_of_zeros_swallowed;
    Object result;

    x_note_fn_call(98,64);
    zeros_to_swallow_qm = T;
    next_delta = Nil;
    number_of_zeros_swallowed = (SI_Long)0L;
  next_loop:
    result = compute_next_delta_1(next_delta_continuation,
	    orientation_horizontal_p_arg,next_stable_axis_position,
	    next_variable_axis_end_position,output_end_x_in_window,
	    output_end_y_in_window);
    MVS_2(result,next_delta,next_delta_continuation);
    if ( !(next_delta && IFIX(next_delta) == (SI_Long)0L))
	zeros_to_swallow_qm = Nil;
    if ( !(next_delta_continuation && zeros_to_swallow_qm))
	goto end_loop;
    next_variable_axis_begin_position = next_stable_axis_position;
    next_stable_axis_position = next_variable_axis_end_position;
    next_variable_axis_end_position = next_variable_axis_begin_position;
    orientation_horizontal_p_arg =  !TRUEP(orientation_horizontal_p_arg) ? 
	    T : Nil;
    number_of_zeros_swallowed = number_of_zeros_swallowed + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_3(next_delta,next_delta_continuation,
	    FIX(number_of_zeros_swallowed));
    return VALUES_1(Qnil);
}

/* COMPUTE-DELTA-FROM-END-POSITION */
Object compute_delta_from_end_position(orientation_horizontal_p_arg,
	    next_stable_axis_position,output_end_x_in_window,
	    output_end_y_in_window)
    Object orientation_horizontal_p_arg, next_stable_axis_position;
    Object output_end_x_in_window, output_end_y_in_window;
{
    x_note_fn_call(98,65);
    if (orientation_horizontal_p_arg)
	return VALUES_1(FIXNUM_MINUS(output_end_y_in_window,
		next_stable_axis_position));
    else
	return VALUES_1(FIXNUM_MINUS(output_end_x_in_window,
		next_stable_axis_position));
}

/* COMPUTE-DELTA-FROM-END-POSITION-LINK-1 */
Object compute_delta_from_end_position_link_1(orientation_horizontal_p_arg,
	    next_stable_axis_position,next_variable_axis_end_position,
	    output_end_x_in_window,output_end_y_in_window)
    Object orientation_horizontal_p_arg, next_stable_axis_position;
    Object next_variable_axis_end_position, output_end_x_in_window;
    Object output_end_y_in_window;
{
    Object delta, next_delta, last_delta, orientation_horizontal_p;
    Object initial_orientation_horizontal_p, cumulative_scaled_width;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,66);
    delta = Nil;
    next_delta = Nil;
    if (orientation_horizontal_p_arg) {
	delta = FIXNUM_MINUS(output_end_y_in_window,next_stable_axis_position);
	next_delta = FIXNUM_MINUS(output_end_x_in_window,
		next_variable_axis_end_position);
    }
    else {
	delta = FIXNUM_MINUS(output_end_x_in_window,next_stable_axis_position);
	next_delta = FIXNUM_MINUS(output_end_y_in_window,
		next_variable_axis_end_position);
    }
    last_delta = next_delta;
    orientation_horizontal_p =  !TRUEP(orientation_horizontal_p_arg) ? T : Nil;
    initial_orientation_horizontal_p = Init_orientation_horizontal_p;
    PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	    0);
      cumulative_scaled_width = Orientation_horizontal_p ? 
	      Cumulative_x_scaled_connection_stripe_width : 
	      Cumulative_y_scaled_connection_stripe_width;
      if (initial_orientation_horizontal_p && Orientation_horizontal_p ||  
	      !TRUEP(initial_orientation_horizontal_p) &&  
	      !TRUEP(Orientation_horizontal_p)) {
	  if (oddp(cumulative_scaled_width)) {
	      if (IFIX(delta) > (SI_Long)0L)
		  result = VALUES_1(FIXNUM_ADD1(delta));
	      else
		  result = VALUES_1(delta);
	  }
	  else if (Orientation_horizontal_p) {
	      if (IFIX(last_delta) < (SI_Long)0L) {
		  if (IFIX(delta) > (SI_Long)0L)
		      result = VALUES_1(delta);
		  else
		      result = VALUES_1(FIXNUM_SUB1(delta));
	      }
	      else if (IFIX(delta) > (SI_Long)0L)
		  result = VALUES_1(FIXNUM_ADD1(delta));
	      else
		  result = VALUES_1(delta);
	  }
	  else if (IFIX(last_delta) > (SI_Long)0L) {
	      if (IFIX(delta) > (SI_Long)0L)
		  result = VALUES_1(delta);
	      else
		  result = VALUES_1(FIXNUM_SUB1(delta));
	  }
	  else if (IFIX(delta) > (SI_Long)0L)
	      result = VALUES_1(FIXNUM_ADD1(delta));
	  else
	      result = VALUES_1(delta);
      }
      else
	  result = VALUES_1(delta);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_draw_diagonally_qm, Qglobal_draw_diagonally_qm);

static Object Qdraw_connection_frame_in_xor;  /* draw-connection-frame-in-xor */

static Object Qdraw_connection_structure_in_xor;  /* draw-connection-structure-in-xor */

/* DRAW-CONNECTION */
Object draw_connection(connection,change_to_this_color_or_color_pattern_qm)
    Object connection, change_to_this_color_or_color_pattern_qm;
{
    Object connection_frame_or_class, x2, block, compiled_function;
    Object block_or_connection, fun, blk, ab_loop_list_, ab_loop_it_;
    Object ab_loop_desetq_, temp_1, svref_arg_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object current_drawing_transfer_mode;
    char temp, already_in_synch;
    Declare_special(1);

    x_note_fn_call(98,67);
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
    if (temp);
    else
	temp = 
		TRUEP(lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		Class_description_gkbprop));
    if (temp) {
	block = ISVREF(connection,(SI_Long)3L);
	temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)1024L);
	if (temp);
	else {
	    block = ISVREF(connection,(SI_Long)2L);
	    temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		    (SI_Long)1024L);
	}
	if (temp) {
	    if (SIMPLE_VECTOR_P(connection) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(connection,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (Currently_working_on_drawing_workspace) {
		    compiled_function = 
			    SYMBOL_FUNCTION(Qdraw_connection_frame_in_xor);
		    block_or_connection = connection;
		    fun = Nil;
		    blk = Nil;
		    ab_loop_list_ = ISVREF(Current_image_plane,(SI_Long)31L);
		    ab_loop_it_ = Nil;
		    ab_loop_desetq_ = Nil;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    ab_loop_desetq_ = M_CAR(ab_loop_list_);
		    fun = CAR(ab_loop_desetq_);
		    temp_1 = CDR(ab_loop_desetq_);
		    blk = CAR(temp_1);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    ab_loop_it_ = EQ(fun,compiled_function) ? (EQ(blk,
			    block_or_connection) ? T : Nil) : Qnil;
		    if (ab_loop_it_) {
			temp = TRUEP(ab_loop_it_);
			goto end_1;
		    }
		    goto next_loop;
		  end_loop:
		    temp = TRUEP(Qnil);
		  end_1:;
		    if ( !temp) {
			svref_arg_1 = Current_image_plane;
			slot_value_push_modify_macro_arg = 
				slot_value_list_4(SYMBOL_FUNCTION(Qdraw_connection_frame_in_xor),
				connection,
				copy_frame_serial_number(ISVREF(connection,
				(SI_Long)3L)),
				change_to_this_color_or_color_pattern_qm);
			car_1 = slot_value_push_modify_macro_arg;
			cdr_1 = ISVREF(svref_arg_1,(SI_Long)31L);
			svref_new_value = slot_value_cons_1(car_1,cdr_1);
			SVREF(svref_arg_1,FIX((SI_Long)31L)) = svref_new_value;
		    }
		}
		else {
		    already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
		    current_drawing_transfer_mode = 
			    Current_drawing_transfer_mode;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			    0);
		      if ( !already_in_synch) {
			  Current_drawing_transfer_mode = Kxor;
			  synchronize_transfer_mode();
		      }
		      draw_connection_frame_in_xor(connection,
			      ISVREF(connection,(SI_Long)3L),
			      change_to_this_color_or_color_pattern_qm);
		    POP_SPECIAL();
		    if ( !already_in_synch)
			synchronize_transfer_mode();
		}
	    }
	    else if (Currently_working_on_drawing_workspace) {
		compiled_function = 
			SYMBOL_FUNCTION(Qdraw_connection_structure_in_xor);
		block_or_connection = connection;
		fun = Nil;
		blk = Nil;
		ab_loop_list_ = ISVREF(Current_image_plane,(SI_Long)31L);
		ab_loop_it_ = Nil;
		ab_loop_desetq_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		fun = CAR(ab_loop_desetq_);
		temp_1 = CDR(ab_loop_desetq_);
		blk = CAR(temp_1);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_it_ = EQ(fun,compiled_function) ? (EQ(blk,
			block_or_connection) ? T : Nil) : Qnil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_2;
		}
		goto next_loop_1;
	      end_loop_1:
		temp = TRUEP(Qnil);
	      end_2:;
		if ( !temp) {
		    svref_arg_1 = Current_image_plane;
		    slot_value_push_modify_macro_arg = 
			    slot_value_list_4(SYMBOL_FUNCTION(Qdraw_connection_structure_in_xor),
			    connection,
			    copy_frame_serial_number(ISVREF(connection,
			    (SI_Long)10L)),
			    change_to_this_color_or_color_pattern_qm);
		    car_1 = slot_value_push_modify_macro_arg;
		    cdr_1 = ISVREF(svref_arg_1,(SI_Long)31L);
		    svref_new_value = slot_value_cons_1(car_1,cdr_1);
		    SVREF(svref_arg_1,FIX((SI_Long)31L)) = svref_new_value;
		}
	    }
	    else {
		already_in_synch = EQ(Current_drawing_transfer_mode,Kxor);
		current_drawing_transfer_mode = Current_drawing_transfer_mode;
		PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			0);
		  if ( !already_in_synch) {
		      Current_drawing_transfer_mode = Kxor;
		      synchronize_transfer_mode();
		  }
		  draw_connection_structure_in_xor(connection,
			  ISVREF(connection,(SI_Long)10L),
			  change_to_this_color_or_color_pattern_qm);
		POP_SPECIAL();
		if ( !already_in_synch)
		    synchronize_transfer_mode();
	    }
	}
	else
	    draw_connection_1(connection,
		    change_to_this_color_or_color_pattern_qm);
    }
    return VALUES_1(connection);
}

/* DRAW-CONNECTION-STRUCTURE-IN-XOR */
Object draw_connection_structure_in_xor(connection,
	    reference_frame_serial_number,
	    change_to_this_color_or_color_pattern_qm)
    Object connection, reference_frame_serial_number;
    Object change_to_this_color_or_color_pattern_qm;
{
    Object gensymed_symbol, xa, ya, temp_1;
    char temp;

    x_note_fn_call(98,68);
    gensymed_symbol = ISVREF(connection,(SI_Long)10L);
    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
	    (SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_frame_serial_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    temp_1 =  !temp ? draw_connection_1(connection,
	    change_to_this_color_or_color_pattern_qm) : Nil;
    return VALUES_1(temp_1);
}

/* DRAW-CONNECTION-FRAME-IN-XOR */
Object draw_connection_frame_in_xor(connection,
	    reference_frame_serial_number,
	    change_to_this_color_or_color_pattern_qm)
    Object connection, reference_frame_serial_number;
    Object change_to_this_color_or_color_pattern_qm;
{
    Object gensymed_symbol, xa, ya, temp_1;
    char temp;

    x_note_fn_call(98,69);
    gensymed_symbol = ISVREF(connection,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(connection) ? EQ(ISVREF(connection,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(reference_frame_serial_number,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(reference_frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    temp_1 =  !temp ? draw_connection_1(connection,
	    change_to_this_color_or_color_pattern_qm) : Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Buggy_polyline_p, Qbuggy_polyline_p);

static Object Qpending;            /* pending */

static Object array_constant_1;    /* # */

/* BUGGY-POLYLINE-P */
Object buggy_polyline_p()
{
    x_note_fn_call(98,70);
    if (EQ(Buggy_polyline_p,Qpending))
	Buggy_polyline_p = get_gensym_environment_variable(array_constant_1);
    return VALUES_1(Buggy_polyline_p);
}

/* DRAW-CONNECTION-1 */
Object draw_connection_1(connection,change_to_this_color_or_color_pattern_qm)
    Object connection, change_to_this_color_or_color_pattern_qm;
{
    Object plist;
    char temp;

    x_note_fn_call(98,71);
    if (printing_window_p(Current_window) || 
	    FIXNUM_LT(Icp_window_protocol_supports_wide_polyline,
	    ISVREF(Current_window,(SI_Long)11L))) {
	plist = ISVREF(connection,(SI_Long)9L);
	temp = plist ? EQ(getfq_function_no_default(plist,
		Qconnection_style),Qdiagonal) : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(connection_line_pattern(connection));
	if (temp);
	else
	    temp = TRUEP(connection_has_arrows_p(connection));
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !TRUEP(buggy_polyline_p()) : TRUEP(Nil))
	return new_draw_connection_wrapper(connection,
		change_to_this_color_or_color_pattern_qm);
    else
	return old_draw_connection(connection,
		change_to_this_color_or_color_pattern_qm);
}

/* OLD-DRAW-CONNECTION */
Object old_draw_connection(connection,change_to_this_color_or_color_pattern_qm)
    Object connection, change_to_this_color_or_color_pattern_qm;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, initial_orientation_horizontal_p;
    Object output_end_object, output_end_position, output_end_side;
    Object connection_frame_or_class, x2, cross_section_pattern, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cross_section_regions, cross_section_stripes, draw_diagonally_qm;
    Object plist, fin_length, cumulative_x_scaled_connection_stripe_width;
    Object cumulative_y_scaled_connection_stripe_width;
    Object cumulative_x_scaled_connection_stripe_half_width;
    Object cumulative_y_scaled_connection_stripe_half_width;
    Object init_orientation_horizontal_p, stable_axis_position;
    Object variable_axis_begin_position, variable_axis_end_position;
    Object delta_continuation, current_delta, next_delta, right_turn_qm;
    Object orientation_horizontal_p, previous_turn_qm, distance_from_last_fin;
    Object any_fins_drawn_qm, connection_class;
    Object forward_and_reverse_subrectangle_structures;
    Object connection_subrectangle_structures;
    Object reverse_connection_subrectangle_structures;
    Object left_most_subrectangle_structure, draw_fins_qm, vertex_x, vertex_y;
    Object initial_delta_p, next_x_and_y_vertex_available_qm;
    Object cumulative_scaled_half_width, stable_axis_position_offset;
    Object subrectangle_stable_axis_position;
    Object connection_subrectangle_structure, ab_loop_list_;
    Object next_stable_axis_position;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, unshifted_result;
    char temp;
    Declare_special(8);
    Object result;

    x_note_fn_call(98,72);
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
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
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
		    gensymed_symbol_5 = new_cons;
		}
		else
		    gensymed_symbol_5 = Nil;
		if ( !TRUEP(gensymed_symbol_5))
		    gensymed_symbol_5 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_5) = head;
		M_CDR(gensymed_symbol_5) = tail;
		inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_5;
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
		    gensymed_symbol_5 = new_cons;
		}
		else
		    gensymed_symbol_5 = Nil;
		if ( !TRUEP(gensymed_symbol_5))
		    gensymed_symbol_5 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_5) = head;
		M_CDR(gensymed_symbol_5) = tail;
		inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_5;
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
    cross_section_regions = CONSP(temp_2) ? CAR(cross_section_pattern) : Nil;
    temp_2 = CAAR(cross_section_pattern);
    cross_section_stripes = CONSP(temp_2) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    draw_diagonally_qm = Global_draw_diagonally_qm;
    if (draw_diagonally_qm);
    else {
	plist = ISVREF(connection,(SI_Long)9L);
	draw_diagonally_qm = plist ? (EQ(getfq_function_no_default(plist,
		Qconnection_style),Qdiagonal) ? T : Nil) : Qnil;
    }
    fin_length = connection_fin_length(1,connection);
    cumulative_x_scaled_connection_stripe_width = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Cumulative_x_scaled_connection_stripe_width,Qcumulative_x_scaled_connection_stripe_width,cumulative_x_scaled_connection_stripe_width,
	    7);
      cumulative_y_scaled_connection_stripe_width = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Cumulative_y_scaled_connection_stripe_width,Qcumulative_y_scaled_connection_stripe_width,cumulative_y_scaled_connection_stripe_width,
	      6);
	cumulative_x_scaled_connection_stripe_half_width = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Cumulative_x_scaled_connection_stripe_half_width,Qcumulative_x_scaled_connection_stripe_half_width,cumulative_x_scaled_connection_stripe_half_width,
		5);
	  cumulative_y_scaled_connection_stripe_half_width = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Cumulative_y_scaled_connection_stripe_half_width,Qcumulative_y_scaled_connection_stripe_half_width,cumulative_y_scaled_connection_stripe_half_width,
		  4);
	    init_orientation_horizontal_p = initial_orientation_horizontal_p;
	    PUSH_SPECIAL_WITH_SYMBOL(Init_orientation_horizontal_p,Qinit_orientation_horizontal_p,init_orientation_horizontal_p,
		    3);
	      stable_axis_position = Nil;
	      variable_axis_begin_position = Nil;
	      variable_axis_end_position = Nil;
	      delta_continuation = Nil;
	      current_delta = Nil;
	      next_delta = Nil;
	      right_turn_qm = Nil;
	      orientation_horizontal_p = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
		      2);
		PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,
			1);
		  previous_turn_qm = Nil;
		  distance_from_last_fin = FIX((SI_Long)0L);
		  any_fins_drawn_qm = Nil;
		  connection_class = SYMBOLP(connection_frame_or_class) ? 
			  connection_frame_or_class : 
			  ISVREF(ISVREF(connection_frame_or_class,
			  (SI_Long)1L),(SI_Long)1L);
		  forward_and_reverse_subrectangle_structures = 
			  lookup_kb_specific_property_value(connection_class,
			  Connection_subrectangle_structures_for_drawing_kbprop);
		  if (forward_and_reverse_subrectangle_structures);
		  else {
		      temp_2 = 
			      generate_connection_subrectangle_structures(cross_section_pattern);
		      forward_and_reverse_subrectangle_structures = 
			      mutate_kb_specific_property_value(connection_class,
			      temp_2,
			      Connection_subrectangle_structures_for_drawing_kbprop);
		  }
		  connection_subrectangle_structures = 
			  CAR(forward_and_reverse_subrectangle_structures);
		  reverse_connection_subrectangle_structures = 
			  CDR(forward_and_reverse_subrectangle_structures);
		  left_most_subrectangle_structure = 
			  CAR(connection_subrectangle_structures);
		  draw_fins_qm = connection_has_classic_fins_p(connection);
		  vertex_x = Nil;
		  vertex_y = Nil;
		  initial_delta_p = T;
		  next_x_and_y_vertex_available_qm = T;
		  initialize_cumulative_scaled_widths(cross_section_stripes);
		  result = serve_first_connection_delta(connection,
			  FIX(input_end_x_position),
			  FIX(input_end_y_position),
			  FIX(output_end_x_position),
			  FIX(output_end_y_position),
			  initial_orientation_horizontal_p);
		  MVS_6(result,Current_delta,next_delta,
			  stable_axis_position,
			  variable_axis_begin_position,
			  variable_axis_end_position,delta_continuation);
		  Orientation_horizontal_p = initial_orientation_horizontal_p;
		  initialize_connection_subrectangle_structures(cross_section_regions,
			  cross_section_stripes,
			  connection_subrectangle_structures,
			  FIX(input_end_x_position),
			  FIX(input_end_y_position),input_end_side,
			  Current_delta,
			  change_to_this_color_or_color_pattern_qm);
		  if (draw_diagonally_qm) {
		      gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
		      if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			  gensymed_symbol_3 = input_end_x_position;
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      Current_image_x_scale) && 
			      FIXNUM_LT(Current_image_x_scale,
			      Isqrt_of_most_positive_fixnum) && 
			      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
			      < input_end_x_position && 
			      input_end_x_position < 
			      IFIX(Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(Current_image_x_scale) * 
				  input_end_x_position + (SI_Long)2048L;
			  gensymed_symbol_3 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_3 = 
				  IFIX(scalef_function(Current_image_x_scale,
				  FIX(input_end_x_position)));
		      vertex_x = FIX(gensymed_symbol_2 + gensymed_symbol_3);
		      gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
		      if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			  gensymed_symbol_3 = input_end_y_position;
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      Current_image_y_scale) && 
			      FIXNUM_LT(Current_image_y_scale,
			      Isqrt_of_most_positive_fixnum) && 
			      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
			      < input_end_y_position && 
			      input_end_y_position < 
			      IFIX(Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(Current_image_y_scale) * 
				  input_end_y_position + (SI_Long)2048L;
			  gensymed_symbol_3 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_3 = 
				  IFIX(scalef_function(Current_image_y_scale,
				  FIX(input_end_y_position)));
		      vertex_y = FIX(gensymed_symbol_2 + gensymed_symbol_3);
		  }
		next_loop_24:
		  if ( !TRUEP(next_delta))
		      goto end_loop_24;
		  right_turn_qm = ((SI_Long)0L > IFIX(Current_delta) ? 
			  TRUEP(Orientation_horizontal_p) :  
			  !TRUEP(Orientation_horizontal_p)) ? ((SI_Long)0L 
			  > IFIX(next_delta) ? T : Nil) :  !((SI_Long)0L > 
			  IFIX(next_delta)) ? T : Nil;
		  distance_from_last_fin = 
			  FIXNUM_ADD(distance_from_last_fin,
			  FIXNUM_ABS(Current_delta));
		  if (draw_diagonally_qm) {
		      if (next_x_and_y_vertex_available_qm) {
			  result = compute_new_vertex_and_draw_diagonal_link(vertex_x,
				  vertex_y,Orientation_horizontal_p,
				  Current_delta,next_delta,
				  connection_subrectangle_structures,
				  draw_fins_qm,fin_length);
			  MVS_2(result,vertex_x,vertex_y);
		      }
		  }
		  else if ( !(IFIX(Current_delta) == (SI_Long)0L)) {
		      if (draw_fins_qm) {
			  temp_2 = distance_from_last_fin;
			  if (Orientation_horizontal_p) {
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  temp_1 = Desired_distance_between_fins;
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Desired_distance_between_fins) && 
				      FIXNUM_LT(Desired_distance_between_fins,
				      Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(FIXNUM_TIMES(Current_image_y_scale,
					  Desired_distance_between_fins)) 
					  + (SI_Long)2048L;
				  temp_1 = FIX(unshifted_result >>  -  - 
					  (SI_Long)12L);
			      }
			      else
				  temp_1 = 
					  scalef_function(Current_image_y_scale,
					  Desired_distance_between_fins);
			  }
			  else if (IFIX(Current_image_x_scale) == 
				  (SI_Long)4096L)
			      temp_1 = Desired_distance_between_fins;
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_x_scale) && 
				  FIXNUM_LT(Current_image_x_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Desired_distance_between_fins) && 
				  FIXNUM_LT(Desired_distance_between_fins,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_x_scale,
				      Desired_distance_between_fins)) + 
				      (SI_Long)2048L;
			      temp_1 = FIX(unshifted_result >>  -  - 
				      (SI_Long)12L);
			  }
			  else
			      temp_1 = 
				      scalef_function(Current_image_x_scale,
				      Desired_distance_between_fins);
			  if (NUM_GT(temp_2,temp_1)) {
			      distance_from_last_fin = 
				      draw_fins_for_connection_component(Current_delta,
				      Orientation_horizontal_p,
				      left_most_subrectangle_structure,
				      variable_axis_begin_position,
				      Orientation_horizontal_p ? 
				      Cumulative_y_scaled_connection_stripe_width 
				      : 
				      Cumulative_x_scaled_connection_stripe_width,
				      fin_length);
			      any_fins_drawn_qm = T;
			  }
		      }
		      draw_connection_subrectangles(right_turn_qm ? 
			      connection_subrectangle_structures : 
			      reverse_connection_subrectangle_structures,
			      right_turn_qm,previous_turn_qm,Nil,
			      next_delta,initial_delta_p,
			      variable_axis_end_position);
		  }
		  else if (initial_delta_p) {
		      cumulative_scaled_half_width = 
			      initial_orientation_horizontal_p ? 
			      Cumulative_y_scaled_connection_stripe_half_width 
			      : 
			      Cumulative_x_scaled_connection_stripe_half_width;
		      stable_axis_position_offset = 
			      oddp(initial_orientation_horizontal_p ? 
			      Cumulative_y_scaled_connection_stripe_width :
			       
			      Cumulative_x_scaled_connection_stripe_width) 
			      ? cumulative_scaled_half_width : 
			      FIXNUM_SUB1(cumulative_scaled_half_width);
		      orientation_horizontal_p = 
			      initial_orientation_horizontal_p;
		      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
			      0);
			gensymed_symbol_2 = IFIX(variable_axis_begin_position);
			gensymed_symbol_3 = 
				initial_orientation_horizontal_p ? 
				(IFIX(next_delta) > (SI_Long)1L ? 
				IFIX(stable_axis_position_offset) : 
				IFIX(FIXNUM_NEGATE(stable_axis_position_offset))) 
				: IFIX(next_delta) > (SI_Long)1L ? 
				IFIX(FIXNUM_NEGATE(stable_axis_position_offset)) 
				: IFIX(stable_axis_position_offset);
			subrectangle_stable_axis_position = 
				FIX(gensymed_symbol_2 + gensymed_symbol_3);
		      POP_SPECIAL();
		      connection_subrectangle_structure = Nil;
		      ab_loop_list_ = connection_subrectangle_structures;
		      next_stable_axis_position = Nil;
		    next_loop_25:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_25;
		      connection_subrectangle_structure = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (initial_orientation_horizontal_p) {
			  if (IFIX(next_delta) > (SI_Long)1L) {
			      gensymed_symbol_2 = 
				      IFIX(subrectangle_stable_axis_position);
			      gensymed_symbol_3 = Orientation_horizontal_p 
				      ? 
				      IFIX(ISVREF(connection_subrectangle_structure,
				      (SI_Long)5L)) : 
				      IFIX(ISVREF(connection_subrectangle_structure,
				      (SI_Long)4L));
			      next_stable_axis_position = 
				      FIX(gensymed_symbol_2 - 
				      gensymed_symbol_3);
			  }
			  else {
			      gensymed_symbol_2 = 
				      IFIX(subrectangle_stable_axis_position);
			      gensymed_symbol_3 = Orientation_horizontal_p 
				      ? 
				      IFIX(ISVREF(connection_subrectangle_structure,
				      (SI_Long)5L)) : 
				      IFIX(ISVREF(connection_subrectangle_structure,
				      (SI_Long)4L));
			      next_stable_axis_position = 
				      FIX(gensymed_symbol_2 + 
				      gensymed_symbol_3);
			  }
		      }
		      else if (IFIX(next_delta) > (SI_Long)1L) {
			  gensymed_symbol_2 = 
				  IFIX(subrectangle_stable_axis_position);
			  gensymed_symbol_3 = Orientation_horizontal_p ? 
				  IFIX(ISVREF(connection_subrectangle_structure,
				  (SI_Long)5L)) : 
				  IFIX(ISVREF(connection_subrectangle_structure,
				  (SI_Long)4L));
			  next_stable_axis_position = 
				  FIX(gensymed_symbol_2 + gensymed_symbol_3);
		      }
		      else {
			  gensymed_symbol_2 = 
				  IFIX(subrectangle_stable_axis_position);
			  gensymed_symbol_3 = Orientation_horizontal_p ? 
				  IFIX(ISVREF(connection_subrectangle_structure,
				  (SI_Long)5L)) : 
				  IFIX(ISVREF(connection_subrectangle_structure,
				  (SI_Long)4L));
			  next_stable_axis_position = 
				  FIX(gensymed_symbol_2 - gensymed_symbol_3);
		      }
		      SVREF(connection_subrectangle_structure,
			      FIX((SI_Long)8L)) = 
			      subrectangle_stable_axis_position;
		      SVREF(connection_subrectangle_structure,
			      FIX((SI_Long)6L)) = stable_axis_position;
		      subrectangle_stable_axis_position = 
			      next_stable_axis_position;
		      goto next_loop_25;
		    end_loop_25:;
		  }
		  previous_turn_qm = IFIX(Current_delta) == (SI_Long)0L ? 
			  Nil : right_turn_qm ? Qright : Qleft;
		  Orientation_horizontal_p =  
			  !TRUEP(Orientation_horizontal_p) ? T : Nil;
		  result = serve_next_connection_delta(connection,
			  FIX(output_end_x_position),
			  FIX(output_end_y_position),stable_axis_position,
			  variable_axis_end_position,delta_continuation,
			  next_delta);
		  MVS_6(result,Current_delta,next_delta,
			  stable_axis_position,
			  variable_axis_begin_position,
			  variable_axis_end_position,delta_continuation);
		  initial_delta_p = Nil;
		  next_x_and_y_vertex_available_qm =  
			  !TRUEP(next_x_and_y_vertex_available_qm) ? T : Nil;
		  goto next_loop_24;
		end_loop_24:
		  if (draw_diagonally_qm) {
		      if (next_x_and_y_vertex_available_qm)
			  compute_new_vertex_and_draw_diagonal_link(vertex_x,
				  vertex_y,Orientation_horizontal_p,
				  Current_delta,FIX((SI_Long)0L),
				  connection_subrectangle_structures,
				  draw_fins_qm,fin_length);
		  }
		  else {
		      if ( !(IFIX(Current_delta) == (SI_Long)0L))
			  draw_connection_subrectangles(connection_subrectangle_structures,
				  right_turn_qm,previous_turn_qm,T,
				  next_delta,initial_delta_p,
				  variable_axis_end_position);
		      distance_from_last_fin = 
			      FIXNUM_ADD(distance_from_last_fin,
			      FIXNUM_ABS(Current_delta));
		      if (draw_fins_qm) {
			  if ( !TRUEP(any_fins_drawn_qm)) {
			      temp_1 = distance_from_last_fin;
			      if (Orientation_horizontal_p) {
				  if (IFIX(Current_image_y_scale) == 
					  (SI_Long)4096L)
				      temp_2 = Minimum_distance_between_fins;
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_y_scale) && 
					  FIXNUM_LT(Current_image_y_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Minimum_distance_between_fins) 
					  && 
					  FIXNUM_LT(Minimum_distance_between_fins,
					  Isqrt_of_most_positive_fixnum)) {
				      unshifted_result = 
					      IFIX(FIXNUM_TIMES(Current_image_y_scale,
					      Minimum_distance_between_fins)) 
					      + (SI_Long)2048L;
				      temp_2 = FIX(unshifted_result >>  -  
					      - (SI_Long)12L);
				  }
				  else
				      temp_2 = 
					      scalef_function(Current_image_y_scale,
					      Minimum_distance_between_fins);
			      }
			      else if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  temp_2 = Minimum_distance_between_fins;
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Minimum_distance_between_fins) && 
				      FIXNUM_LT(Minimum_distance_between_fins,
				      Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(FIXNUM_TIMES(Current_image_x_scale,
					  Minimum_distance_between_fins)) 
					  + (SI_Long)2048L;
				  temp_2 = FIX(unshifted_result >>  -  - 
					  (SI_Long)12L);
			      }
			      else
				  temp_2 = 
					  scalef_function(Current_image_x_scale,
					  Minimum_distance_between_fins);
			      temp = NUM_GT(temp_1,temp_2);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp);
			  else {
			      temp_1 = distance_from_last_fin;
			      if (Orientation_horizontal_p) {
				  if (IFIX(Current_image_y_scale) == 
					  (SI_Long)4096L)
				      temp_2 = Desired_distance_between_fins;
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_y_scale) && 
					  FIXNUM_LT(Current_image_y_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Desired_distance_between_fins) 
					  && 
					  FIXNUM_LT(Desired_distance_between_fins,
					  Isqrt_of_most_positive_fixnum)) {
				      unshifted_result = 
					      IFIX(FIXNUM_TIMES(Current_image_y_scale,
					      Desired_distance_between_fins)) 
					      + (SI_Long)2048L;
				      temp_2 = FIX(unshifted_result >>  -  
					      - (SI_Long)12L);
				  }
				  else
				      temp_2 = 
					      scalef_function(Current_image_y_scale,
					      Desired_distance_between_fins);
			      }
			      else if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  temp_2 = Desired_distance_between_fins;
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Desired_distance_between_fins) && 
				      FIXNUM_LT(Desired_distance_between_fins,
				      Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(FIXNUM_TIMES(Current_image_x_scale,
					  Desired_distance_between_fins)) 
					  + (SI_Long)2048L;
				  temp_2 = FIX(unshifted_result >>  -  - 
					  (SI_Long)12L);
			      }
			      else
				  temp_2 = 
					  scalef_function(Current_image_x_scale,
					  Desired_distance_between_fins);
			      temp = NUM_GT(temp_1,temp_2);
			  }
			  if (temp)
			      distance_from_last_fin = 
				      draw_fins_for_connection_component(Current_delta,
				      Orientation_horizontal_p,
				      left_most_subrectangle_structure,
				      variable_axis_begin_position,
				      Orientation_horizontal_p ? 
				      Cumulative_y_scaled_connection_stripe_width 
				      : 
				      Cumulative_x_scaled_connection_stripe_width,
				      fin_length);
		      }
		  }
		  result = VALUES_1(Qnil);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CONNECTION-HAS-CLASSIC-FINS-P */
Object connection_has_classic_fins_p(connection)
    Object connection;
{
    x_note_fn_call(98,73);
    if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
	    (SI_Long)1L)))
	return VALUES_1( 
		!TRUEP(connection_arrows_of_connection(connection)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* CONNECTION-HAS-ARROWS-P */
Object connection_has_arrows_p(connection)
    Object connection;
{
    Object arrows;

    x_note_fn_call(98,74);
    arrows = connection_arrows_of_connection(connection);
    if ( ! !TRUEP(arrows))
	return VALUES_1( !EQ(arrows,Qnone) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* NEW-DRAW-CONNECTION-WRAPPER */
Object new_draw_connection_wrapper(connection,
	    change_to_this_color_or_color_pattern_qm)
    Object connection, change_to_this_color_or_color_pattern_qm;
{
    Object gensymed_symbol, temp;
    char temp_1;

    x_note_fn_call(98,75);
    gensymed_symbol = ISVREF(ISVREF(connection,(SI_Long)3L),(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(ISVREF(connection,(SI_Long)2L),(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    if (FIXNUM_EQ(temp,gensymed_symbol)) {
	gensymed_symbol = ISVREF(ISVREF(connection,(SI_Long)3L),(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp = gensymed_symbol;
	gensymed_symbol = ISVREF(ISVREF(connection,(SI_Long)2L),(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	temp_1 = FIXNUM_EQ(temp,gensymed_symbol);
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	return new_draw_connection(connection,
		change_to_this_color_or_color_pattern_qm);
    else
	return VALUES_1(Nil);
}

static Object Qrounded;            /* rounded */

static Object Qmiter;              /* miter */

/* NEW-DRAW-CONNECTION */
Object new_draw_connection(connection,change_to_this_color_or_color_pattern_qm)
    Object connection, change_to_this_color_or_color_pattern_qm;
{
    Object connection_frame_or_class, x2, cross_section_pattern, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, cross_section_regions, cross_section_stripes;
    Object vertices, total_width, scale, line_pattern, stripes, nstripes;
    Object scaled_line_pattern, connection_has_fins_p;
    Object connection_has_arrows_p_1, fin_length, index_1, color_difference;
    Object ab_loop_list_, ab_loop_desetq_, fin_color_difference, arrows;
    Object arrow_size, arrow_line_thickness, plist, line_style;
    Object stripe_width_in_window, fdist, points;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long unshifted_result;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(98,76);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_2,gensymed_symbol_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_14;
	      end_loop_13:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_2,gensymed_symbol_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_16:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_17;
	      end_loop_16:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_19:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_20:
		    if ( !TRUEP(marked))
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_20;
		  end_loop_19:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		  next_loop_21:
		    if (level < ab_loop_bind_)
			goto end_loop_21;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_22:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_23;
		  end_loop_22:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
	cross_section_regions = CONSP(temp_2) ? CAR(cross_section_pattern) 
		: Nil;
	temp_2 = CAAR(cross_section_pattern);
	cross_section_stripes = CONSP(temp_2) ? CDR(cross_section_pattern) 
		: cross_section_pattern;
	vertices = compute_connection_vertices(connection);
	total_width = connection_total_width(connection);
	scale = FIXNUM_MIN(Current_image_x_scale,Current_image_y_scale);
	line_pattern = connection_line_pattern(connection);
	stripes = sort_stripes(compute_stripes(cross_section_regions,
		cross_section_stripes,
		change_to_this_color_or_color_pattern_qm,scale,
		EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ?
		 ( !TRUEP(line_pattern) ? T : Nil) : Qnil));
	nstripes = length(stripes);
	scaled_line_pattern = compute_scaled_line_pattern(line_pattern,
		scale,total_width);
	connection_has_fins_p = connection_has_classic_fins_p(connection);
	connection_has_arrows_p_1 = connection_has_arrows_p(connection);
	fin_length = connection_fin_length(2,connection,total_width);
	index_1 = Nil;
	color_difference = Nil;
	ab_loop_list_ = stripes;
	ab_loop_desetq_ = Nil;
      next_loop_24:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_24;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	index_1 = CAR(ab_loop_desetq_);
	temp_2 = CDR(ab_loop_desetq_);
	color_difference = CAR(temp_2);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (IFIX(index_1) == (SI_Long)0L) {
	    fin_color_difference = color_difference;
	    goto end_9;
	}
	goto next_loop_24;
      end_loop_24:
	fin_color_difference = Qnil;
      end_9:;
	arrows = connection_arrows_of_connection(connection);
	if (IFIX(fin_length) == (SI_Long)4096L)
	    arrow_size = scale;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		fin_length) && FIXNUM_LT(fin_length,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
		FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(fin_length,scale)) + 
		    (SI_Long)2048L;
	    arrow_size = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    arrow_size = scalef_function(fin_length,scale);
	if (IFIX(total_width) == (SI_Long)4096L)
	    arrow_line_thickness = scale;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		total_width) && FIXNUM_LT(total_width,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
		FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(total_width,scale)) + 
		    (SI_Long)2048L;
	    arrow_line_thickness = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    arrow_line_thickness = scalef_function(total_width,scale);
	plist = ISVREF(connection,(SI_Long)9L);
	line_style = (plist && EQ(getfq_function_no_default(plist,
		Qconnection_style),Qdiagonal) ? IFIX(nstripes) == 
		(SI_Long)1L : TRUEP(Nil)) ? Qrounded : Qmiter;
	index_1 = Nil;
	color_difference = Nil;
	stripe_width_in_window = Nil;
	fdist = Nil;
	ab_loop_list_ = stripes;
	points = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_25:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_25;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	index_1 = CAR(ab_loop_desetq_);
	temp_2 = CDR(ab_loop_desetq_);
	color_difference = CAR(temp_2);
	temp_2 = CDR(ab_loop_desetq_);
	temp_2 = CDR(temp_2);
	stripe_width_in_window = CAR(temp_2);
	temp_2 = CDR(ab_loop_desetq_);
	temp_2 = CDR(temp_2);
	temp_2 = CDR(temp_2);
	fdist = CAR(temp_2);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	points = compute_miter_points(fdist,vertices);
	if (connection_has_arrows_p_1)
	    adjust_points_for_connection_arrows(connection,arrows,points,
		    arrow_size,arrow_line_thickness);
	draw_wide_polyline(points,color_difference,stripe_width_in_window,
		scaled_line_pattern,line_style);
	reclaim_gensym_list_1(points);
	goto next_loop_25;
      end_loop_25:;
	if (connection_has_fins_p)
	    draw_connection_fins(vertices,total_width,fin_length,
		    fin_color_difference);
	if (connection_has_arrows_p_1)
	    draw_connection_arrows(connection,arrows,vertices,arrow_size,
		    arrow_line_thickness,fin_color_difference);
	if (CONSP(scaled_line_pattern))
	    reclaim_gensym_list_1(scaled_line_pattern);
	reclaim_gensym_tree_1(stripes);
	result = reclaim_gensym_list_1(vertices);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object float_constant;      /* 0.0 */

/* COMPUTE-STRIPES */
Object compute_stripes(cross_section_regions,cross_section_stripes,
	    color_qm,scale,fudge)
    Object cross_section_regions, cross_section_stripes, color_qm, scale;
    Object fudge;
{
    Object color, width, ab_loop_list_, ab_loopvar_, ab_loop_desetq_;
    Object total_width, temp, nstripes, region_or_color, stripe_width;
    Object sum_width, fw, fw2, fdist, stripe_width_in_window;
    Object fudged_width_in_window, stripe_color, recorded_color, desired_color;
    Object color_difference, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object color_value_1, color_value_2;
    SI_Long index_1, unshifted_result;
    double temp_1, fwidth2, temp_2;

    x_note_fn_call(98,77);
    color = Nil;
    width = Nil;
    ab_loop_list_ = cross_section_stripes;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    color = CAR(ab_loop_desetq_);
    width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
    goto next_loop;
  end_loop:
    total_width = ab_loopvar_;
    goto end_1;
    total_width = Qnil;
  end_1:;
    temp = float_delta_x_in_window(total_width,scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    fwidth2 = temp_1 / 2.0;
    nstripes = length(cross_section_stripes);
    region_or_color = Nil;
    stripe_width = Nil;
    ab_loop_list_ = cross_section_stripes;
    sum_width = float_constant;
    fw = Nil;
    fw2 = Nil;
    fdist = Nil;
    index_1 = (SI_Long)0L;
    stripe_width_in_window = Nil;
    fudged_width_in_window = Nil;
    stripe_color = Nil;
    recorded_color = Nil;
    desired_color = Nil;
    color_difference = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region_or_color = CAR(ab_loop_desetq_);
    stripe_width = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_)) {
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(sum_width);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fw);
	sum_width = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_1);
    }
    fw = float_delta_x_in_window(stripe_width,scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fw);
    fw2 = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 2.0);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(sum_width);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fw2);
    fdist = DOUBLE_TO_DOUBLE_FLOAT(fwidth2 - temp_2 - temp_1);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if (IFIX(scale) == (SI_Long)4096L)
	stripe_width_in_window = stripe_width;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,stripe_width) 
	    && FIXNUM_LT(stripe_width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,stripe_width)) + 
		(SI_Long)2048L;
	stripe_width_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	stripe_width_in_window = scalef_function(scale,stripe_width);
    fudged_width_in_window =  !TRUEP(fudge) || index_1 == (SI_Long)0L || 
	    index_1 == IFIX(FIXNUM_SUB1(nstripes)) ? 
	    stripe_width_in_window : FIX(IFIX(stripe_width_in_window) + 
	    (SI_Long)2L);
    temp = assq_function(region_or_color,cross_section_regions);
    temp = CDR(temp);
    if (temp);
    else
	temp = region_or_color;
    stripe_color = temp;
    recorded_color = color_qm ? stripe_color : Qbackground;
    if ( !TRUEP(color_qm))
	desired_color = stripe_color;
    else if (SYMBOLP(color_qm))
	desired_color = color_qm;
    else {
	temp = assq_function(region_or_color,color_qm);
	temp = CDR(temp);
	if (temp);
	else
	    temp = region_or_color;
	desired_color = temp;
    }
    if ( !EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor)) {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	if (EQ(recorded_color,Qbackground))
	    color_value_2 = Current_background_color_value;
	else if (EQ(recorded_color,Qforeground) || EQ(recorded_color,
		Qworkspace_foreground))
	    color_value_2 = Current_foreground_color_value;
	else if (EQ(recorded_color,Qtransparent))
	    color_value_2 = Current_background_color_value;
	else
	    color_value_2 = map_to_color_value(recorded_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,color_value_2);
    }
    else if (EQ(desired_color,recorded_color))
	color_difference = EQ(Current_drawing_transfer_mode,
		Kpaint_infered_from_xor) ? Transparent_color_value : 
		FIX((SI_Long)0L);
    else if (EQ(desired_color,Qtransparent))
	color_difference = EQ(Current_drawing_transfer_mode,
		Kpaint_infered_from_xor) ? Transparent_color_value : 
		FIX((SI_Long)0L);
    else if (EQ(recorded_color,Qtransparent)) {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,
		Current_background_color_value);
    }
    else {
	if (EQ(desired_color,Qbackground))
	    color_value_1 = Current_background_color_value;
	else if (EQ(desired_color,Qforeground) || EQ(desired_color,
		Qworkspace_foreground))
	    color_value_1 = Current_foreground_color_value;
	else if (EQ(desired_color,Qtransparent))
	    color_value_1 = Current_background_color_value;
	else
	    color_value_1 = map_to_color_value(desired_color);
	if (EQ(recorded_color,Qbackground))
	    color_value_2 = Current_background_color_value;
	else if (EQ(recorded_color,Qforeground) || EQ(recorded_color,
		Qworkspace_foreground))
	    color_value_2 = Current_foreground_color_value;
	else if (EQ(recorded_color,Qtransparent))
	    color_value_2 = Current_background_color_value;
	else
	    color_value_2 = map_to_color_value(recorded_color);
	color_difference = FIXNUM_LOGXOR(color_value_1,color_value_2);
    }
    ab_loopvar__2 = gensym_cons_1(gensym_list_4(FIX(index_1),
	    color_difference,fudged_width_in_window,fdist),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* SORT-STRIPES */
Object sort_stripes(stripes)
    Object stripes;
{
    Object next, last_two, cdr_new_value;

    x_note_fn_call(98,78);
    if (IFIX(length(stripes)) <= (SI_Long)2L || 
	    EQ(Current_drawing_transfer_mode,Kxor))
	return VALUES_1(stripes);
    else {
	next = CDR(stripes);
	last_two = lastn(stripes,FIX((SI_Long)2L));
	cdr_new_value = last(stripes,_);
	M_CDR(stripes) = cdr_new_value;
	M_CDR(last_two) = stripes;
	return VALUES_1(next);
    }
}

/* LASTN */
Object lastn(list_1,n_1)
    Object list_1, n_1;
{
    Object result_1, marker, ab_loop_iter_flag_;

    x_note_fn_call(98,79);
    result_1 = list_1;
    marker = nthcdr(n_1,list_1);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(result_1))
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	marker = M_CDR(marker);
    if ( !TRUEP(marker))
	goto end_loop;
    if ( !TRUEP(marker))
	goto end_loop;
    ab_loop_iter_flag_ = Nil;
    result_1 = M_CDR(result_1);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object float_constant_1;    /* 0.1 */

/* COMPUTE-MITER-POINTS */
Object compute_miter_points(fdist,vertices)
    Object fdist, vertices;
{
    Object points, pdx, pdy, pdxn, pdyn, x1, y1_1, x2, y2, rest_qm;
    Object ab_loop_list_, first_1, dx, dy, dn, dxn, dyn, perpx, perpy;
    Object ab_loop_iter_flag_, temp, cross, un, uxn, uyn, sinth2;
    SI_Long temp_3, x, y;
    double arg, arg_1, temp_1, temp_2, ux, uy, signum_1, length_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(98,80);
    arg = DOUBLE_FLOAT_TO_DOUBLE(fdist);
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return copy_list_using_gensym_conses_1(vertices);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    points = Nil;
	    pdx = float_constant;
	    pdy = float_constant;
	    pdxn = float_constant;
	    pdyn = float_constant;
	    x1 = Nil;
	    y1_1 = Nil;
	    x2 = Nil;
	    y2 = Nil;
	    rest_qm = Nil;
	    ab_loop_list_ = vertices;
	    first_1 = T;
	    dx = Nil;
	    dy = Nil;
	    dn = Nil;
	    dxn = Nil;
	    dyn = Nil;
	    perpx = Nil;
	    perpy = Nil;
	    ab_loop_iter_flag_ = T;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    x1 = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    y1_1 = CAR(temp);
	    temp = CDR(ab_loop_list_);
	    temp = CDR(temp);
	    x2 = CAR(temp);
	    temp = CDR(ab_loop_list_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    y2 = CAR(temp);
	    temp = CDR(ab_loop_list_);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    rest_qm = CDR(temp);
	    if ( !TRUEP(x2))
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		first_1 = Nil;
	    dx = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(x2,x1)));
	    dy = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(y2,y1_1)));
	    dn = float_length(dx,dy);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(dx);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(dn);
	    dxn = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / temp_2);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(dy);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(dn);
	    dyn = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / temp_2);
	    perpx = dyn;
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(dxn);
	    perpy = DOUBLE_TO_DOUBLE_FLOAT( - temp_2);
	    if (first_1) {
		temp_3 = IFIX(x1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fdist);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(perpx);
		x = temp_3 + inline_ceiling_1(temp_1 * temp_2);
		temp_3 = IFIX(y1_1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fdist);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(perpy);
		y = temp_3 + inline_ceiling_1(temp_1 * temp_2);
		points = gensym_cons_1(FIX(y),gensym_cons_1(FIX(x),points));
	    }
	    else {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(dxn);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(pdxn);
		ux = temp_1 - temp_2;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(dyn);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(pdyn);
		uy = temp_1 - temp_2;
		cross = float_cross(pdxn,pdyn,dxn,dyn);
		arg = DOUBLE_FLOAT_TO_DOUBLE(cross);
		arg_1 = 0.0;
		signum_1 = arg > arg_1 &&  
			!inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1) ? -1.0 : 1.0;
		un = float_length(DOUBLE_TO_DOUBLE_FLOAT(ux),
			DOUBLE_TO_DOUBLE_FLOAT(uy));
		arg = DOUBLE_FLOAT_TO_DOUBLE(un);
		arg_1 = 0.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    uxn = perpx;
		else {
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(un);
		    uxn = DOUBLE_TO_DOUBLE_FLOAT(signum_1 * (ux / temp_2));
		}
		arg = DOUBLE_FLOAT_TO_DOUBLE(un);
		arg_1 = 0.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    uyn = perpy;
		else {
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(un);
		    uyn = DOUBLE_TO_DOUBLE_FLOAT(signum_1 * (uy / temp_2));
		}
		sinth2 = float_cross(uxn,uyn,pdxn,pdyn);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fdist);
		temp = DOUBLE_FLOAT_MAX(sinth2,float_constant_1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		length_1 = temp_1 / temp_2;
		temp_3 = IFIX(x1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(uxn);
		x = temp_3 + inline_ceiling_1(length_1 * temp_2);
		temp_3 = IFIX(y1_1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(uyn);
		y = temp_3 + inline_ceiling_1(length_1 * temp_2);
		points = gensym_cons_1(FIX(y),gensym_cons_1(FIX(x),points));
	    }
	    if ( !TRUEP(rest_qm)) {
		temp_3 = IFIX(x2);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fdist);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(perpx);
		x = temp_3 + inline_ceiling_1(temp_1 * temp_2);
		temp_3 = IFIX(y2);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fdist);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(perpy);
		y = temp_3 + inline_ceiling_1(temp_1 * temp_2);
		points = gensym_cons_1(FIX(y),gensym_cons_1(FIX(x),points));
	    }
	    pdx = dx;
	    pdy = dy;
	    pdxn = dxn;
	    pdyn = dyn;
	    ab_loop_iter_flag_ = Nil;
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:
	    result = nreverse(points);
	    goto end_1;
	    result = VALUES_1(Qnil);
	  end_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* COMPUTE-CONNECTION-VERTICES */
Object compute_connection_vertices(connection)
    Object connection;
{
    Object plist;

    x_note_fn_call(98,81);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal))
	return compute_diagonal_connection_vertices(connection);
    else
	return compute_orthogonal_connection_vertices(connection);
}

/* COMPUTE-ORTHOGONAL-CONNECTION-VERTICES */
Object compute_orthogonal_connection_vertices(connection)
    Object connection;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, initial_orientation_horizontal_p;
    Object output_end_object, output_end_position, output_end_side;
    Object delta_or_deltas_qm, horizontal, x, y, xw, yw, result_1, names_sic;
    Object delta;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, unshifted_result;

    x_note_fn_call(98,82);
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
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
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
    delta_or_deltas_qm = ISVREF(connection,(SI_Long)6L);
    horizontal = initial_orientation_horizontal_p;
    x = Nil;
    y = Nil;
    xw = FIX((SI_Long)0L);
    yw = FIX((SI_Long)0L);
    result_1 = Nil;
    x = FIX(input_end_x_position);
    y = FIX(input_end_y_position);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
	    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
	    CADR(result_1)))) {
	result_1 = gensym_cons_1(xw,result_1);
	result_1 = gensym_cons_1(yw,result_1);
    }
    names_sic = delta_or_deltas_qm;
    delta = Nil;
  next_loop:
    delta = CONSP(names_sic) ? CAR(names_sic) : names_sic;
    if ( !TRUEP(delta))
	goto end_loop;
    if (horizontal) {
	x = FIXNUM_ADD(x,delta);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    else {
	y = FIXNUM_ADD(y,delta);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    horizontal =  !TRUEP(horizontal) ? T : Nil;
    names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
    goto next_loop;
  end_loop:;
    if (horizontal) {
	x = FIX(output_end_x_position);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    else {
	y = FIX(output_end_y_position);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    x = FIX(output_end_x_position);
    y = FIX(output_end_y_position);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
	    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
	    CADR(result_1)))) {
	result_1 = gensym_cons_1(xw,result_1);
	result_1 = gensym_cons_1(yw,result_1);
    }
    return nreverse(result_1);
}

/* COMPUTE-DIAGONAL-CONNECTION-VERTICES */
Object compute_diagonal_connection_vertices(connection)
    Object connection;
{
    Object gensymed_symbol, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, initial_orientation_horizontal_p;
    Object output_end_object, output_end_position, output_end_side;
    Object delta_or_deltas_qm, horizontal, x, y, xw, yw, ready, result_1;
    Object names_sic, delta;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, unshifted_result;

    x_note_fn_call(98,83);
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
    initial_orientation_horizontal_p = EQ(input_end_side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(input_end_side,Qright) ? T : Nil;
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
    delta_or_deltas_qm = ISVREF(connection,(SI_Long)6L);
    horizontal = initial_orientation_horizontal_p;
    x = Nil;
    y = Nil;
    xw = FIX((SI_Long)0L);
    yw = FIX((SI_Long)0L);
    ready = Nil;
    result_1 = Nil;
    x = FIX(input_end_x_position);
    y = FIX(input_end_y_position);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
	    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    if (T) {
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    names_sic = delta_or_deltas_qm;
    delta = Nil;
  next_loop:
    delta = CONSP(names_sic) ? CAR(names_sic) : names_sic;
    if ( !TRUEP(delta))
	goto end_loop;
    if (horizontal) {
	x = FIXNUM_ADD(x,delta);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if (ready) {
	    if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		    CADR(result_1)))) {
		result_1 = gensym_cons_1(xw,result_1);
		result_1 = gensym_cons_1(yw,result_1);
	    }
	}
    }
    else {
	y = FIXNUM_ADD(y,delta);
	gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(x);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
	xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(y);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) 
		    + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
	yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	if (ready) {
	    if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		    CADR(result_1)))) {
		result_1 = gensym_cons_1(xw,result_1);
		result_1 = gensym_cons_1(yw,result_1);
	    }
	}
    }
    horizontal =  !TRUEP(horizontal) ? T : Nil;
    ready =  !TRUEP(ready) ? T : Nil;
    names_sic = CONSP(names_sic) ? CDR(names_sic) : Nil;
    goto next_loop;
  end_loop:;
    if (ready) {
	if (horizontal) {
	    x = FIX(output_end_x_position);
	    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(x);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			x)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_x_scale,x));
	    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(y);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			y)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_y_scale,y));
	    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	    if (T) {
		if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && 
			FIXNUM_EQ(xw,CADR(result_1)))) {
		    result_1 = gensym_cons_1(xw,result_1);
		    result_1 = gensym_cons_1(yw,result_1);
		}
	    }
	}
	else {
	    y = FIX(output_end_y_position);
	    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(x);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			x)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_x_scale,x));
	    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_3 = IFIX(y);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			y)) + (SI_Long)2048L;
		gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_3 = 
			IFIX(scalef_function(Current_image_y_scale,y));
	    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	    if (T) {
		if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && 
			FIXNUM_EQ(xw,CADR(result_1)))) {
		    result_1 = gensym_cons_1(xw,result_1);
		    result_1 = gensym_cons_1(yw,result_1);
		}
	    }
	}
    }
    x = FIX(output_end_x_position);
    y = FIX(output_end_y_position);
    gensymed_symbol_2 = IFIX(Current_x_origin_of_drawing);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(x);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
	    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,x)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_x_scale,x));
    xw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    gensymed_symbol_2 = IFIX(Current_y_origin_of_drawing);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	gensymed_symbol_3 = IFIX(y);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,y)) + 
		(SI_Long)2048L;
	gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_3 = IFIX(scalef_function(Current_image_y_scale,y));
    yw = FIX(gensymed_symbol_2 + gensymed_symbol_3);
    if (T) {
	if ( !(result_1 && FIXNUM_EQ(yw,CAR(result_1)) && FIXNUM_EQ(xw,
		CADR(result_1)))) {
	    result_1 = gensym_cons_1(xw,result_1);
	    result_1 = gensym_cons_1(yw,result_1);
	}
    }
    return nreverse(result_1);
}

/* DRAW-FINS-FOR-CONNECTION-COMPONENT */
Object draw_fins_for_connection_component(current_delta,
	    orientation_horizontal_p,subrectangle_structure,
	    connection_component_variable_axis_begin_position,
	    connection_overall_width,fin_length)
    Object current_delta, orientation_horizontal_p, subrectangle_structure;
    Object connection_component_variable_axis_begin_position;
    Object connection_overall_width, fin_length;
{
    Object subrectangle_stable_axis_position, temp, temp_1;
    Object spacing_between_fins_on_link, fin_color_difference;
    Object x_scaled_fin_length, y_scaled_fin_length, color_value;
    Object old_color_value, current_background_color_value;
    Object left_fin_inner_point_x, left_fin_inner_point_y;
    Object left_fin_outer_point_x, left_fin_outer_point_y;
    Object right_fin_inner_point_x, right_fin_inner_point_y;
    Object right_fin_outer_point_x, right_fin_outer_point_y;
    Object position_along_link;
    SI_Long unshifted_result, temp_2, number_of_fins, fin_number;
    SI_Long ab_loop_bind_;
    Declare_stack_pointer;
    Declare_special(3);
    Object result;

    x_note_fn_call(98,84);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,1);
	subrectangle_stable_axis_position = ISVREF(subrectangle_structure,
		(SI_Long)8L);
	temp = FIXNUM_ABS(Current_delta);
	if (Orientation_horizontal_p) {
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		temp_1 = Desired_distance_between_fins_on_link;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Desired_distance_between_fins_on_link) && 
		    FIXNUM_LT(Desired_distance_between_fins_on_link,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			Desired_distance_between_fins_on_link)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(Current_image_y_scale,
			Desired_distance_between_fins_on_link);
	}
	else if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    temp_1 = Desired_distance_between_fins_on_link;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Desired_distance_between_fins_on_link) && 
		FIXNUM_LT(Desired_distance_between_fins_on_link,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    Desired_distance_between_fins_on_link)) + (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(Current_image_x_scale,
		    Desired_distance_between_fins_on_link);
	temp_2 = IFIX(lfloor(temp,temp_1));
	number_of_fins = MAX((SI_Long)1L,temp_2);
	spacing_between_fins_on_link = l_round(Current_delta,
		FIX(number_of_fins + (SI_Long)1L));
	fin_color_difference = ISVREF(subrectangle_structure,(SI_Long)1L);
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    x_scaled_fin_length = fin_length;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		fin_length) && FIXNUM_LT(fin_length,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		    fin_length)) + (SI_Long)2048L;
	    x_scaled_fin_length = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    x_scaled_fin_length = scalef_function(Current_image_x_scale,
		    fin_length);
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    y_scaled_fin_length = fin_length;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		fin_length) && FIXNUM_LT(fin_length,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		    fin_length)) + (SI_Long)2048L;
	    y_scaled_fin_length = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    y_scaled_fin_length = scalef_function(Current_image_y_scale,
		    fin_length);
	color_value = ISVREF(subrectangle_structure,(SI_Long)2L);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(color_value);
	  left_fin_inner_point_x = Nil;
	  left_fin_inner_point_y = Nil;
	  left_fin_outer_point_x = Nil;
	  left_fin_outer_point_y = Nil;
	  right_fin_inner_point_x = Nil;
	  right_fin_inner_point_y = Nil;
	  right_fin_outer_point_x = Nil;
	  right_fin_outer_point_y = Nil;
	  fin_number = (SI_Long)1L;
	  ab_loop_bind_ = number_of_fins;
	  position_along_link = Nil;
	next_loop:
	  if (fin_number > ab_loop_bind_)
	      goto end_loop;
	  position_along_link = ltimes(FIX(fin_number),
		  spacing_between_fins_on_link);
	  if (Orientation_horizontal_p) {
	      left_fin_inner_point_x = 
		      FIXNUM_ADD(connection_component_variable_axis_begin_position,
		      position_along_link);
	      right_fin_inner_point_x = left_fin_inner_point_x;
	      if (IFIX(Current_delta) > (SI_Long)1L) {
		  left_fin_inner_point_y = 
			  FIX(IFIX(subrectangle_stable_axis_position) - 
			  (SI_Long)2L);
		  left_fin_outer_point_x = 
			  FIXNUM_MINUS(left_fin_inner_point_x,
			  x_scaled_fin_length);
		  left_fin_outer_point_y = 
			  FIXNUM_MINUS(left_fin_inner_point_y,
			  y_scaled_fin_length);
		  right_fin_inner_point_y = 
			  FIXNUM_ADD(subrectangle_stable_axis_position,
			  connection_overall_width);
		  right_fin_outer_point_y = 
			  FIXNUM_ADD(right_fin_inner_point_y,
			  y_scaled_fin_length);
	      }
	      else {
		  left_fin_inner_point_y = subrectangle_stable_axis_position;
		  left_fin_outer_point_x = 
			  FIXNUM_ADD(left_fin_inner_point_x,
			  x_scaled_fin_length);
		  left_fin_outer_point_y = 
			  FIXNUM_ADD(left_fin_inner_point_y,
			  y_scaled_fin_length);
		  right_fin_inner_point_y = 
			  FIX(IFIX(FIXNUM_MINUS(subrectangle_stable_axis_position,
			  connection_overall_width)) - (SI_Long)2L);
		  right_fin_outer_point_y = 
			  FIXNUM_MINUS(right_fin_inner_point_y,
			  y_scaled_fin_length);
	      }
	      right_fin_outer_point_x = left_fin_outer_point_x;
	  }
	  else {
	      left_fin_inner_point_y = 
		      FIXNUM_ADD(connection_component_variable_axis_begin_position,
		      position_along_link);
	      right_fin_inner_point_y = left_fin_inner_point_y;
	      if (IFIX(Current_delta) > (SI_Long)1L) {
		  left_fin_inner_point_x = subrectangle_stable_axis_position;
		  left_fin_outer_point_x = 
			  FIXNUM_ADD(left_fin_inner_point_x,
			  x_scaled_fin_length);
		  left_fin_outer_point_y = 
			  FIXNUM_MINUS(left_fin_inner_point_y,
			  y_scaled_fin_length);
		  right_fin_inner_point_x = 
			  FIX(IFIX(FIXNUM_MINUS(subrectangle_stable_axis_position,
			  connection_overall_width)) - (SI_Long)2L);
		  right_fin_outer_point_x = 
			  FIXNUM_MINUS(right_fin_inner_point_x,
			  x_scaled_fin_length);
	      }
	      else {
		  left_fin_inner_point_x = 
			  FIX(IFIX(subrectangle_stable_axis_position) - 
			  (SI_Long)2L);
		  left_fin_outer_point_x = 
			  FIXNUM_MINUS(left_fin_inner_point_x,
			  x_scaled_fin_length);
		  left_fin_outer_point_y = 
			  FIXNUM_ADD(left_fin_inner_point_y,
			  y_scaled_fin_length);
		  right_fin_inner_point_x = 
			  FIXNUM_ADD(subrectangle_stable_axis_position,
			  connection_overall_width);
		  right_fin_outer_point_x = 
			  FIXNUM_ADD(right_fin_inner_point_x,
			  x_scaled_fin_length);
	      }
	      right_fin_outer_point_y = left_fin_outer_point_y;
	  }
	  draw_line(left_fin_inner_point_x,left_fin_inner_point_y,
		  left_fin_outer_point_x,left_fin_outer_point_y,
		  fin_color_difference);
	  draw_line(right_fin_inner_point_x,right_fin_inner_point_y,
		  right_fin_outer_point_x,right_fin_outer_point_y,
		  fin_color_difference);
	  fin_number = fin_number + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
	  SAVE_VALUES(VALUES_1(FIXNUM_ABS(spacing_between_fins_on_link)));
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* FLOAT-SQUARE */
Object float_square(x)
    Object x;
{
    double temp, temp_1;

    x_note_fn_call(98,85);
    temp = DOUBLE_FLOAT_TO_DOUBLE(x);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp * temp_1));
}

/* FLOAT-DOT */
Object float_dot(x1,y1_1,x2,y2)
    Object x1, y1_1, x2, y2;
{
    double temp, temp_1, temp_2, temp_3;

    x_note_fn_call(98,86);
    temp = DOUBLE_FLOAT_TO_DOUBLE(x1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x2);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(y1_1);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y2);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp * temp_1 + temp_2 * temp_3));
}

/* FLOAT-CROSS */
Object float_cross(x1,y1_1,x2,y2)
    Object x1, y1_1, x2, y2;
{
    double temp, temp_1, temp_2, temp_3;

    x_note_fn_call(98,87);
    temp = DOUBLE_FLOAT_TO_DOUBLE(x1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(y2);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(x2);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y1_1);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp * temp_1 - temp_2 * temp_3));
}

/* FLOAT-LENGTH */
Object float_length(delta_x,delta_y)
    Object delta_x, delta_y;
{
    Object temp_4;
    double temp, temp_1, temp_2, temp_3;

    x_note_fn_call(98,88);
    temp = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
    temp_4 = DOUBLE_TO_DOUBLE_FLOAT(sqrt(temp * temp_1 + temp_2 * temp_3));
    return VALUES_1(temp_4);
}

/* FLOAT-DISTANCE */
Object float_distance(delta_x,delta_y)
    Object delta_x, delta_y;
{
    Object temp_4;
    double temp, temp_1, temp_2, temp_3;

    x_note_fn_call(98,89);
    temp = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(delta_x);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(delta_y);
    temp_4 = DOUBLE_TO_DOUBLE_FLOAT(sqrt(temp * temp_1 + temp_2 * temp_3));
    return VALUES_1(temp_4);
}

Object Basic_arrow_shapes = UNBOUND;

/* DRAW-CONNECTION-ARROWS */
Object draw_connection_arrows(connection,arrows,vertices,size,line_width,
	    color_difference)
    Object connection, arrows, vertices, size, line_width, color_difference;
{
    Object spec, ab_loop_list_;

    x_note_fn_call(98,90);
    if (ATOM(arrows))
	return draw_connection_arrow_1(connection,arrows,vertices,size,
		line_width,color_difference);
    else {
	spec = Nil;
	ab_loop_list_ = arrows;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	spec = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	draw_connection_arrow_1(connection,spec,vertices,size,line_width,
		color_difference);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qboth;               /* both */

/* DRAW-CONNECTION-ARROW-1 */
Object draw_connection_arrow_1(connection,spec,vertices,size,line_width,
	    color_difference)
    Object connection, spec, vertices, size, line_width, color_difference;
{
    Object shape, end_1, thickness, width, height, filled_qm, gensymed_symbol;
    Object xp, yp, xn, yn_1, x0, y0_1, x1, y1_1;
    Object result;

    x_note_fn_call(98,91);
    result = decode_arrow_spec(connection,spec,size,line_width);
    MVS_6(result,shape,end_1,thickness,width,height,filled_qm);
    gensymed_symbol = lastn(vertices,FIX((SI_Long)4L));
    xp = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    yp = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    xn = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    yn_1 = CAR(gensymed_symbol);
    gensymed_symbol = vertices;
    x0 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y0_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y1_1 = CAR(gensymed_symbol);
    if (yn_1 && (EQ(end_1,Qoutput) || EQ(end_1,Qboth)))
	draw_connection_arrow(shape,xp,yp,xn,yn_1,width,height,thickness,
		color_difference,filled_qm);
    if (y1_1 && (EQ(end_1,Qinput) || EQ(end_1,Qboth)))
	return draw_connection_arrow(shape,x1,y1_1,x0,y0_1,width,height,
		thickness,color_difference,filled_qm);
    else
	return VALUES_1(Nil);
}

static Object Qcircle;             /* circle */

/* DRAW-CONNECTION-ARROW */
Object draw_connection_arrow(shape,x0,y0_1,x1,y1_1,width,height,thickness,
	    color_difference,filled_qm)
    Object shape, x0, y0_1, x1, y1_1, width, height, thickness;
    Object color_difference, filled_qm;
{
    Object points;

    x_note_fn_call(98,92);
    points = compute_arrow_points(shape,x0,y0_1,x1,y1_1,width,height,
	    thickness);
    if (EQ(shape,Qcircle))
	draw_circle(4,points,color_difference,thickness,filled_qm);
    else
	draw_polygon(4,points,color_difference,thickness,filled_qm);
    return reclaim_gensym_list_1(points);
}

static Object Qarrow;              /* arrow */

static Object Qsimple_arrow;       /* simple-arrow */

static Object Qtriangle;           /* triangle */

static Object Qdiamond;            /* diamond */

/* COMPUTE-ARROW-POINTS */
Object compute_arrow_points(shape,x0,y0_1,x1,y1_1,width,height,thickness)
    Object shape, x0, y0_1, x1, y1_1, width, height, thickness;
{
    Object l, xt, yt, x2, y2, x3, y3, x4, y4, gensymed_symbol;
    Object gensymed_symbol_1, xc, yc;
    SI_Long radius;
    double w, h, dx, dy, temp, c, s, x1f, y1f, t2, xb, yb, d;

    x_note_fn_call(98,93);
    if ( !(FIXNUM_EQ(x0,x1) && FIXNUM_EQ(y0_1,y1_1))) {
	w = (double)IFIX(width);
	h = (double)IFIX(height);
	dx = (double)IFIX(FIXNUM_MINUS(x1,x0));
	dy = (double)IFIX(FIXNUM_MINUS(y1_1,y0_1));
	l = float_length(DOUBLE_TO_DOUBLE_FLOAT(dx),
		DOUBLE_TO_DOUBLE_FLOAT(dy));
	temp = DOUBLE_FLOAT_TO_DOUBLE(l);
	c = dx / temp;
	temp = DOUBLE_FLOAT_TO_DOUBLE(l);
	s = dy / temp;
	x1f = (double)IFIX(x1);
	y1f = (double)IFIX(y1_1);
	t2 = IFIX(thickness) == (SI_Long)1L ? 0.0 : 
		(double)IFIX(thickness) / 2.0;
	xb = x1f - (t2 + w) * c;
	yb = y1f - (t2 + w) * s;
	xt = l_round(DOUBLE_TO_DOUBLE_FLOAT(x1f - t2 * c),_);
	yt = l_round(DOUBLE_TO_DOUBLE_FLOAT(y1f - t2 * s),_);
	x2 = l_round(DOUBLE_TO_DOUBLE_FLOAT(xb - h * 0.5 * s),_);
	y2 = l_round(DOUBLE_TO_DOUBLE_FLOAT(yb + h * 0.5 * c),_);
	x3 = l_round(DOUBLE_TO_DOUBLE_FLOAT(xb + h * 0.5 * s),_);
	y3 = l_round(DOUBLE_TO_DOUBLE_FLOAT(yb - h * 0.5 * c),_);
	x4 = l_round(DOUBLE_TO_DOUBLE_FLOAT(xb - w * c),_);
	y4 = l_round(DOUBLE_TO_DOUBLE_FLOAT(yb - w * s),_);
	if (EQ(shape,Qarrow) || EQ(shape,Qsimple_arrow)) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = x2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = xt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = yt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x3;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y3;
	    return VALUES_1(gensymed_symbol);
	}
	else if (EQ(shape,Qtriangle)) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = x2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = xt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = yt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x3;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y3;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y2;
	    return VALUES_1(gensymed_symbol);
	}
	else if (EQ(shape,Qdiamond)) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = x2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = xt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = yt;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x3;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y3;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x4;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y4;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = x2;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = y2;
	    return VALUES_1(gensymed_symbol);
	}
	else if (EQ(shape,Qcircle)) {
	    d = t2 + w / 2.0;
	    xc = l_round(DOUBLE_TO_DOUBLE_FLOAT(x1f - d * c),_);
	    yc = l_round(DOUBLE_TO_DOUBLE_FLOAT(y1f - d * s),_);
	    radius = IFIX(width) >>  -  - (SI_Long)1L;
	    return gensym_list_3(xc,yc,FIX(radius));
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* MAP-OVER-CONNECTION-ARROWS */
Object map_over_connection_arrows(connection,vertices,function,answer)
    Object connection, vertices, function, answer;
{
    Object arrows, thickness, size, spec, ab_loop_list_;

    x_note_fn_call(98,94);
    if (connection_has_arrows_p(connection)) {
	arrows = connection_arrows_of_connection(connection);
	thickness = connection_total_width(connection);
	size = connection_fin_length(2,connection,thickness);
	if (ATOM(arrows))
	    answer = map_over_connection_arrows_1(function,answer,
		    connection,arrows,vertices,size,thickness);
	else {
	    spec = Nil;
	    ab_loop_list_ = arrows;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    spec = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    answer = map_over_connection_arrows_1(function,answer,
		    connection,spec,vertices,size,thickness);
	    goto next_loop;
	  end_loop:;
	}
    }
    return VALUES_1(answer);
}

/* MAP-OVER-CONNECTION-ARROWS-1 */
Object map_over_connection_arrows_1(function,answer,connection,spec,
	    vertices,size,line_width)
    Object function, answer, connection, spec, vertices, size, line_width;
{
    Object shape, end_1, thickness, width, height, gensymed_symbol, xp, yp, xn;
    Object yn_1, x0, y0_1, x1, y1_1;
    Object result;

    x_note_fn_call(98,95);
    result = decode_arrow_spec(connection,spec,size,line_width);
    MVS_5(result,shape,end_1,thickness,width,height);
    gensymed_symbol = lastn(vertices,FIX((SI_Long)4L));
    xp = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    yp = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    xn = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    yn_1 = CAR(gensymed_symbol);
    gensymed_symbol = vertices;
    x0 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y0_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y1_1 = CAR(gensymed_symbol);
    if (yn_1 && (EQ(end_1,Qoutput) || EQ(end_1,Qboth)))
	answer = map_over_connection_arrows_2(function,answer,shape,xp,yp,
		xn,yn_1,width,height,thickness);
    if (y1_1 && (EQ(end_1,Qinput) || EQ(end_1,Qboth)))
	answer = map_over_connection_arrows_2(function,answer,shape,x1,
		y1_1,x0,y0_1,width,height,thickness);
    return VALUES_1(answer);
}

/* MAP-OVER-CONNECTION-ARROWS-2 */
Object map_over_connection_arrows_2(function,answer,shape,x0,y0_1,x1,y1_1,
	    width,height,thickness)
    Object function, answer, shape, x0, y0_1, x1, y1_1, width, height;
    Object thickness;
{
    Object points, t2, gensymed_symbol, xc, yc, radius, left, top, right;
    Object bottom, x, y, ab_loop_list_, ab_loopvar_, ab_loop_maxmin_fl_;
    Object ab_loop_maxmin_fl__1, ab_loop_maxmin_fl__2, ab_loop_maxmin_fl__3;
    Object temp;

    x_note_fn_call(98,96);
    points = compute_arrow_points(shape,x0,y0_1,x1,y1_1,width,height,
	    thickness);
    t2 = FIXNUM_ADD1(ltruncate(thickness,FIX((SI_Long)2L)));
    if (EQ(shape,Qcircle)) {
	gensymed_symbol = points;
	xc = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	yc = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	radius = CAR(gensymed_symbol);
	left = FIXNUM_MINUS(FIXNUM_MINUS(xc,radius),t2);
	top = FIXNUM_MINUS(FIXNUM_MINUS(yc,radius),t2);
	right = FIXNUM_ADD(FIXNUM_ADD(xc,radius),t2);
	bottom = FIXNUM_ADD(FIXNUM_ADD(yc,radius),t2);
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    else {
	x = Nil;
	y = Nil;
	ab_loop_list_ = points;
	left = FIX((SI_Long)0L);
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
	top = FIX((SI_Long)0L);
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__1 = T;
	right = FIX((SI_Long)0L);
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__2 = T;
	bottom = FIX((SI_Long)0L);
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__3 = T;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	x = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	y = CAR(temp);
	if ( !TRUEP(y))
	    goto end_loop;
	ab_loopvar_ = FIXNUM_MINUS(x,t2);
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    left = ab_loopvar_;
	}
	else
	    left = lmin(left,ab_loopvar_);
	ab_loopvar_ = FIXNUM_MINUS(y,t2);
	if (ab_loop_maxmin_fl__1) {
	    ab_loop_maxmin_fl__1 = Nil;
	    top = ab_loopvar_;
	}
	else
	    top = lmin(top,ab_loopvar_);
	ab_loopvar_ = FIXNUM_ADD(x,t2);
	if (ab_loop_maxmin_fl__2) {
	    ab_loop_maxmin_fl__2 = Nil;
	    right = ab_loopvar_;
	}
	else
	    right = lmax(right,ab_loopvar_);
	ab_loopvar_ = FIXNUM_ADD(y,t2);
	if (ab_loop_maxmin_fl__3) {
	    ab_loop_maxmin_fl__3 = Nil;
	    bottom = ab_loopvar_;
	}
	else
	    bottom = lmax(bottom,ab_loopvar_);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	answer = inline_funcall_5(function,left,top,right,bottom,answer);
    }
    reclaim_gensym_list_1(points);
    return VALUES_1(answer);
}

/* DECODE-ARROW-SPEC */
Object decode_arrow_spec(connection,spec,size,line)
    Object connection, spec, size, line;
{
    Object shape, placement, thick, width, height, filled, temp, temp_1;
    Object temp_2, temp_3;
    Object result;

    x_note_fn_call(98,97);
    result = decode_arrow_spec_1(spec);
    MVS_6(result,shape,placement,thick,width,height,filled);
    temp = default_placement_of_connection_arrow(connection,placement);
    temp_1 = ash(line,thick);
    temp_2 = ash(size,width);
    temp_3 = ash(size,height);
    return VALUES_6(shape,temp,temp_1,temp_2,temp_3,filled);
}

static Object Qfilled;             /* filled */

static Object Qlarge;              /* large */

static Object Qsmall;              /* small */

static Object Qwide;               /* wide */

static Object Qnarrow;             /* narrow */

static Object Qthick;              /* thick */

static Object Qthin;               /* thin */

static Object Qvery;               /* very */

static Object Qdefault;            /* default */

/* DECODE-ARROW-SPEC-1 */
Object decode_arrow_spec_1(spec)
    Object spec;
{
    Object filled, thick, width, height, delta, adjective, ab_loop_list_;
    Object incff_1_arg, decff_1_arg, temp, temp_1, temp_2, temp_3, temp_4;
    Object temp_5;

    x_note_fn_call(98,98);
    filled = FIX((SI_Long)0L);
    thick = FIX((SI_Long)0L);
    width = FIX((SI_Long)0L);
    height = FIX((SI_Long)0L);
    delta = FIX((SI_Long)1L);
    if (CONSP(spec)) {
	adjective = Nil;
	ab_loop_list_ = CDDR(spec);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	adjective = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(adjective,Qfilled)) {
	    incff_1_arg = delta;
	    filled = FIXNUM_ADD(filled,incff_1_arg);
	}
	else if (EQ(adjective,Qopen)) {
	    decff_1_arg = delta;
	    filled = FIXNUM_MINUS(filled,decff_1_arg);
	}
	else if (EQ(adjective,Qlarge)) {
	    incff_1_arg = delta;
	    width = FIXNUM_ADD(width,incff_1_arg);
	    incff_1_arg = delta;
	    height = FIXNUM_ADD(height,incff_1_arg);
	}
	else if (EQ(adjective,Qsmall)) {
	    decff_1_arg = delta;
	    width = FIXNUM_MINUS(width,decff_1_arg);
	    decff_1_arg = delta;
	    height = FIXNUM_MINUS(height,decff_1_arg);
	}
	else if (EQ(adjective,Qwide)) {
	    incff_1_arg = delta;
	    height = FIXNUM_ADD(height,incff_1_arg);
	}
	else if (EQ(adjective,Qnarrow)) {
	    decff_1_arg = delta;
	    height = FIXNUM_MINUS(height,decff_1_arg);
	}
	else if (EQ(adjective,Qthick)) {
	    incff_1_arg = delta;
	    thick = FIXNUM_ADD(thick,incff_1_arg);
	}
	else if (EQ(adjective,Qthin)) {
	    decff_1_arg = delta;
	    thick = FIXNUM_MINUS(thick,decff_1_arg);
	}
	if (EQ(adjective,Qvery))
	    delta = FIX((SI_Long)2L);
	else
	    delta = FIX((SI_Long)1L);
	goto next_loop;
      end_loop:;
    }
    temp = ATOM(spec) ? spec : CADR(spec);
    temp_1 = ATOM(spec) ? Qdefault : CAR(spec);
    temp_2 = thick;
    temp_3 = width;
    temp_4 = height;
    temp_5 = FIX((SI_Long)0L);
    temp_5 = NUM_GT(filled,temp_5) ? T : Nil;
    return VALUES_6(temp,temp_1,temp_2,temp_3,temp_4,temp_5);
}

/* CONNECTION-ARROW-HEIGHT-1 */
Object connection_arrow_height_1(arrow,size)
    Object arrow, size;
{
    Object height, delta, adjective, ab_loop_list_, incff_1_arg, decff_1_arg;

    x_note_fn_call(98,99);
    height = FIX((SI_Long)0L);
    delta = FIX((SI_Long)1L);
    if (CONSP(arrow)) {
	adjective = Nil;
	ab_loop_list_ = CDDR(arrow);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	adjective = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(adjective,Qwide) || EQ(adjective,Qlarge)) {
	    incff_1_arg = delta;
	    height = FIXNUM_ADD(height,incff_1_arg);
	}
	else if (EQ(adjective,Qnarrow) || EQ(adjective,Qsmall)) {
	    decff_1_arg = delta;
	    height = FIXNUM_MINUS(height,decff_1_arg);
	}
	if (EQ(adjective,Qvery))
	    delta = FIX((SI_Long)2L);
	else
	    delta = FIX((SI_Long)1L);
	goto next_loop;
      end_loop:;
    }
    return ash(size,height);
}

/* DEFAULT-PLACEMENT-OF-CONNECTION-ARROW */
Object default_placement_of_connection_arrow(connection,placement)
    Object connection, placement;
{
    x_note_fn_call(98,100);
    if (EQ(placement,Qdefault)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)1L)))
	    return VALUES_1(Qoutput);
	else
	    return VALUES_1(Qboth);
    }
    else
	return VALUES_1(placement);
}

/* CONNECTION-ARROW-WIDTH */
Object connection_arrow_width(connection)
    Object connection;
{
    Object connection_frame_or_class, x2, cross_section_pattern, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, cross_section_stripe, width, ab_loop_list_;
    Object ab_loopvar_, ab_loop_desetq_, size, arrows, arrow, ab_loopvar__1;
    Object ab_loop_maxmin_fl_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Object result;

    x_note_fn_call(98,101);
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
    width = ab_loopvar_;
    goto end_9;
    width = Qnil;
  end_9:;
    size = connection_fin_length(2,connection,width);
    arrows = connection_arrows_of_connection(connection);
    gensymed_symbol_3 = IFIX(width);
    if (EQ(arrows,Qnone))
	gensymed_symbol_4 = IFIX(width);
    else if ( !TRUEP(arrows) &&  !((SI_Long)0L != (IFIX(ISVREF(connection,
	    (SI_Long)7L)) & (SI_Long)1L)))
	gensymed_symbol_4 = IFIX(width) + IFIX(size) * (SI_Long)2L;
    else if (ATOM(arrows))
	gensymed_symbol_4 = IFIX(size);
    else {
	arrow = Nil;
	ab_loop_list_ = arrows;
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loopvar__1 = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
      next_loop_25:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_25;
	arrow = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = connection_arrow_height_1(arrow,size);
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    ab_loopvar_ = ab_loopvar__1;
	}
	else
	    ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
	goto next_loop_25;
      end_loop_25:
	gensymed_symbol_4 = IFIX(ab_loopvar_);
	goto end_10;
	gensymed_symbol_4 = IFIX(Qnil);
      end_10:;
    }
    return VALUES_1(FIX(MAX(gensymed_symbol_3,gensymed_symbol_4)));
}

/* LENGTH-OF-ARROW-SHAPE */
Object length_of_arrow_shape(shape,size,thickness)
    Object shape, size, thickness;
{
    x_note_fn_call(98,102);
    if (EQ(shape,Qarrow) || EQ(shape,Qsimple_arrow))
	return VALUES_1(thickness);
    else if (EQ(shape,Qtriangle))
	return VALUES_1(size);
    else if (EQ(shape,Qdiamond))
	return VALUES_1(FIX((SI_Long)2L * IFIX(size)));
    else if (EQ(shape,Qcircle))
	return VALUES_1(size);
    else
	return VALUES_1(size);
}

/* ADJUST-POINTS-FOR-CONNECTION-ARROWS */
Object adjust_points_for_connection_arrows(connection,arrows,points,size,line)
    Object connection, arrows, points, size, line;
{
    Object shape, ends, thickness, width, length_1, arrow, ab_loop_list_;
    Object len_1, len_2, length_at_input_end, ab_loop_maxmin_fl_;
    Object length_at_output_end, ab_loop_maxmin_fl__1;
    Object result;

    x_note_fn_call(98,103);
    if (ATOM(arrows)) {
	result = decode_arrow_spec(connection,arrows,size,line);
	MVS_4(result,shape,ends,thickness,width);
	length_1 = length_of_arrow_shape(shape,width,thickness);
	if (EQ(ends,Qinput))
	    return pull_in_endpoint(points,length_1,Nil);
	else if (EQ(ends,Qoutput))
	    return pull_in_endpoint(points,length_1,T);
	else if (EQ(ends,Qboth)) {
	    pull_in_endpoint(points,length_1,Nil);
	    return pull_in_endpoint(points,length_1,T);
	}
	else
	    return VALUES_1(Qnil);
    }
    else {
	arrow = Nil;
	ab_loop_list_ = arrows;
	len_1 = Nil;
	len_2 = Nil;
	length_at_input_end = FIX((SI_Long)0L);
	ab_loop_maxmin_fl_ = T;
	length_at_output_end = FIX((SI_Long)0L);
	ab_loop_maxmin_fl__1 = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arrow = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	len_1 = FIX((SI_Long)0L);
	len_2 = FIX((SI_Long)0L);
	result = decode_arrow_spec(connection,arrow,size,line);
	MVS_4(result,shape,ends,thickness,width);
	length_1 = length_of_arrow_shape(shape,width,thickness);
	if (EQ(ends,Qinput))
	    len_1 = length_1;
	else if (EQ(ends,Qoutput))
	    len_2 = length_1;
	else if (EQ(ends,Qboth)) {
	    len_1 = length_1;
	    len_2 = length_1;
	}
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    length_at_input_end = len_1;
	}
	else
	    length_at_input_end = lmax(length_at_input_end,len_1);
	if (ab_loop_maxmin_fl__1) {
	    ab_loop_maxmin_fl__1 = Nil;
	    length_at_output_end = len_2;
	}
	else
	    length_at_output_end = lmax(length_at_output_end,len_2);
	goto next_loop;
      end_loop:
	if (IFIX(length_at_input_end) > (SI_Long)0L)
	    pull_in_endpoint(points,length_at_input_end,Nil);
	if (IFIX(length_at_output_end) > (SI_Long)0L)
	    pull_in_endpoint(points,length_at_output_end,T);
	return VALUES_1(Qnil);
    }
}

/* PULL-IN-ENDPOINT */
Object pull_in_endpoint(points,distance,tail_p)
    Object points, distance, tail_p;
{
    Object vector_1, gensymed_symbol, x0, y0_1, x1, y1_1, l, temp_1;
    double dx, dy, temp, c, s, x0f, y0f, x1f, y1f, dist;

    x_note_fn_call(98,104);
    vector_1 = tail_p ? lastn(points,FIX((SI_Long)4L)) : points;
    gensymed_symbol = vector_1;
    x0 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y0_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y1_1 = CAR(gensymed_symbol);
    if (y1_1 && (FIXNUM_NE(x0,x1) || FIXNUM_NE(y0_1,y1_1))) {
	dx = (double)IFIX(FIXNUM_MINUS(x1,x0));
	dy = (double)IFIX(FIXNUM_MINUS(y1_1,y0_1));
	l = float_length(DOUBLE_TO_DOUBLE_FLOAT(dx),
		DOUBLE_TO_DOUBLE_FLOAT(dy));
	temp = DOUBLE_FLOAT_TO_DOUBLE(l);
	c = dx / temp;
	temp = DOUBLE_FLOAT_TO_DOUBLE(l);
	s = dy / temp;
	x0f = (double)IFIX(x0);
	y0f = (double)IFIX(y0_1);
	x1f = (double)IFIX(x1);
	y1f = (double)IFIX(y1_1);
	dist = (double)IFIX(distance);
	if (tail_p) {
	    temp_1 = l_round(DOUBLE_TO_DOUBLE_FLOAT(x1f - dist * c),_);
	    M_THIRD(vector_1) = temp_1;
	    temp_1 = l_round(DOUBLE_TO_DOUBLE_FLOAT(y1f - dist * s),_);
	    return VALUES_1(M_FOURTH(vector_1) = temp_1);
	}
	else {
	    temp_1 = l_round(DOUBLE_TO_DOUBLE_FLOAT(x0f + dist * c),_);
	    M_FIRST(vector_1) = temp_1;
	    temp_1 = l_round(DOUBLE_TO_DOUBLE_FLOAT(y0f + dist * s),_);
	    return VALUES_1(M_SECOND(vector_1) = temp_1);
	}
    }
    else
	return VALUES_1(Nil);
}

/* DRAW-CONNECTION-FINS */
Object draw_connection_fins(vertices,thickness,fin_length,color_difference)
    Object vertices, thickness, fin_length, color_difference;
{
    Object x1, y1_1, x2, y2, ab_loop_list_, temp;

    x_note_fn_call(98,105);
    x1 = Nil;
    y1_1 = Nil;
    x2 = Nil;
    y2 = Nil;
    ab_loop_list_ = vertices;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    x1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    y1_1 = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    x2 = CAR(temp);
    temp = CDR(ab_loop_list_);
    temp = CDR(temp);
    temp = CDR(temp);
    y2 = CAR(temp);
    if (x2)
	draw_fins_for_diagonal_connection_component(x1,y1_1,x2,y2,
		thickness,fin_length,color_difference);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DRAW-FINS-FOR-DIAGONAL-CONNECTION-COMPONENT */
Object draw_fins_for_diagonal_connection_component(x1,y1_1,x2,y2,
	    connection_width,fin_length,color_difference)
    Object x1, y1_1, x2, y2, connection_width, fin_length, color_difference;
{
    x_note_fn_call(98,106);
    return draw_fins_for_diagonal_connection_component_1(x1,y1_1,x2,y2,
	    connection_width,fin_length,color_difference,T);
}

/* BOUNDING-REGION-OF-FINS-FOR-DIAGONAL-CONNECTION-COMPONENT */
Object bounding_region_of_fins_for_diagonal_connection_component(x1,y1_1,
	    x2,y2,connection_width,fin_length)
    Object x1, y1_1, x2, y2, connection_width, fin_length;
{
    x_note_fn_call(98,107);
    return draw_fins_for_diagonal_connection_component_1(x1,y1_1,x2,y2,
	    connection_width,fin_length,FIX((SI_Long)0L),Nil);
}

/* DRAW-FINS-FOR-DIAGONAL-CONNECTION-COMPONENT-1 */
Object draw_fins_for_diagonal_connection_component_1(x1,y1_1,x2,y2,
	    connection_width,fin_length,color_difference,draw_qm)
    Object x1, y1_1, x2, y2, connection_width, fin_length, color_difference;
    Object draw_qm;
{
    Object region, fx1, fy1, fx2, fy2, scale, temp, link_length;
    Object number_of_fins, spacing_between_fins_on_link, scaled_fin_length;
    Object float_fin_length, fin_1_inner_point_x, fin_1_inner_point_y;
    Object fin_2_inner_point_x, fin_2_inner_point_y, fin_1_base_point_x;
    Object fin_1_base_point_y, fin_2_base_point_x, fin_2_base_point_y;
    Object fin_1_outer_point_x, fin_1_outer_point_y, fin_2_outer_point_x;
    Object fin_2_outer_point_y, position_along_link, temp_4, temp_5, temp_6;
    SI_Long unshifted_result, fin_number, ab_loop_bind_;
    double temp_1, fw2, temp_2, delta_x, delta_y, base_length, arg, arg_1, ux;
    double uy, perpx, perpy, dx, dy, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(98,108);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	region =  !TRUEP(draw_qm) ? make_empty_region() : Nil;
	fx1 = lfloat(x1,float_constant);
	fy1 = lfloat(y1_1,float_constant);
	fx2 = lfloat(x2,float_constant);
	fy2 = lfloat(y2,float_constant);
	scale = FIXNUM_MIN(Current_image_x_scale,Current_image_y_scale);
	temp = float_delta_x_in_window(connection_width,scale);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	fw2 = temp_1 / 2.0;
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fx2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	delta_x = temp_2 - temp_1;
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fy2);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
	delta_y = temp_2 - temp_1;
	link_length = float_distance(DOUBLE_TO_DOUBLE_FLOAT(delta_x),
		DOUBLE_TO_DOUBLE_FLOAT(delta_y));
	number_of_fins = lmax(FIX((SI_Long)1L),lfloor(link_length,
		Desired_distance_between_fins_on_link));
	spacing_between_fins_on_link = l_round(link_length,
		add1(number_of_fins));
	if (IFIX(scale) == (SI_Long)4096L)
	    scaled_fin_length = fin_length;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		fin_length) && FIXNUM_LT(fin_length,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,fin_length)) + 
		    (SI_Long)2048L;
	    scaled_fin_length = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    scaled_fin_length = scalef_function(scale,fin_length);
	float_fin_length = lfloat(scaled_fin_length,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
	base_length =  - temp_1;
	fin_1_inner_point_x = Nil;
	fin_1_inner_point_y = Nil;
	fin_2_inner_point_x = Nil;
	fin_2_inner_point_y = Nil;
	fin_1_base_point_x = Nil;
	fin_1_base_point_y = Nil;
	fin_2_base_point_x = Nil;
	fin_2_base_point_y = Nil;
	fin_1_outer_point_x = Nil;
	fin_1_outer_point_y = Nil;
	fin_2_outer_point_x = Nil;
	fin_2_outer_point_y = Nil;
	fin_number = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_fins);
	position_along_link = Nil;
      next_loop:
	if (fin_number > ab_loop_bind_)
	    goto end_loop;
	position_along_link = lfloat(ltimes(FIX(fin_number),
		spacing_between_fins_on_link),float_constant);
	temp = FIX((SI_Long)0L);
	if (NUM_EQ(DOUBLE_TO_DOUBLE_FLOAT(delta_x),temp)) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	    fin_1_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + fw2);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
	    fin_2_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_1 - fw2);
	    arg = delta_y;
	    arg_1 = 0.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_1_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_1);
	    }
	    else {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_1_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - temp_1);
	    }
	    fin_2_inner_point_y = fin_1_inner_point_y;
	    arg = delta_y;
	    arg_1 = 0.0;
	    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_y);
		fin_1_base_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 
			base_length);
	    }
	    else {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_y);
		fin_1_base_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_1 - 
			base_length);
	    }
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
	    fin_1_outer_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_1);
	    fin_1_outer_point_y = fin_1_base_point_y;
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_inner_point_x);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
	    fin_2_outer_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - temp_1);
	    fin_2_outer_point_y = fin_1_base_point_y;
	}
	else {
	    temp = FIX((SI_Long)0L);
	    if (NUM_EQ(DOUBLE_TO_DOUBLE_FLOAT(delta_y),temp)) {
		arg = delta_x;
		arg_1 = 0.0;
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		    fin_1_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			    temp_1);
		}
		else {
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		    fin_1_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - 
			    temp_1);
		}
		fin_2_inner_point_x = fin_1_inner_point_x;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		fin_1_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + fw2);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		fin_2_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_1 - fw2);
		arg = delta_x;
		arg_1 = 0.0;
		if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_x);
		    fin_1_base_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 
			    base_length);
		}
		else {
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_x);
		    fin_1_base_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_1 - 
			    base_length);
		}
		fin_1_outer_point_x = fin_1_base_point_x;
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_y);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		fin_1_outer_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_1);
		fin_2_outer_point_x = fin_1_base_point_x;
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_inner_point_y);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		fin_2_outer_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - temp_1);
	    }
	    else {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		ux = delta_x / temp_1;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		uy = delta_y / temp_1;
		perpx = uy;
		perpy =  - ux;
		dx = fw2 * perpx;
		dy = fw2 * perpy;
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_1_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			temp_1 * ux + dx);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fx1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_2_inner_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			temp_1 * ux +  - dx);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_1_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			temp_1 * uy + dy);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fy1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(position_along_link);
		fin_2_inner_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			temp_1 * uy +  - dy);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_x);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_1_base_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			delta_x * base_length / temp_1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_inner_point_y);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_1_base_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			delta_y * base_length / temp_1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_inner_point_x);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_2_base_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			delta_x * base_length / temp_1);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_inner_point_y);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_2_base_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + 
			delta_y * base_length / temp_1);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_base_point_x);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_1_outer_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + 
			delta_y * temp_2 / temp_1);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(fin_1_base_point_y);
		temp_2 =  - delta_x;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		temp_2 = temp_2 * temp_1;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_1_outer_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + 
			temp_2 / temp_1);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_base_point_x);
		temp_2 =  - delta_y;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		temp_2 = temp_2 * temp_1;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_2_outer_point_x = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + 
			temp_2 / temp_1);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(fin_2_base_point_y);
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(float_fin_length);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(link_length);
		fin_2_outer_point_y = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + 
			delta_x * temp_2 / temp_1);
	    }
	}
	if (fin_1_inner_point_x) {
	    fin_1_inner_point_x = l_round(fin_1_inner_point_x,_);
	    fin_1_inner_point_y = l_round(fin_1_inner_point_y,_);
	    fin_2_inner_point_x = l_round(fin_2_inner_point_x,_);
	    fin_2_inner_point_y = l_round(fin_2_inner_point_y,_);
	    fin_1_outer_point_x = l_round(fin_1_outer_point_x,_);
	    fin_1_outer_point_y = l_round(fin_1_outer_point_y,_);
	    fin_2_outer_point_x = l_round(fin_2_outer_point_x,_);
	    fin_2_outer_point_y = l_round(fin_2_outer_point_y,_);
	    if (draw_qm) {
		new_draw_line(fin_1_inner_point_x,fin_1_inner_point_y,
			fin_1_outer_point_x,fin_1_outer_point_y,
			color_difference);
		new_draw_line(fin_2_inner_point_x,fin_2_inner_point_y,
			fin_2_outer_point_x,fin_2_outer_point_y,
			color_difference);
	    }
	    else {
		temp = FIXNUM_MIN(fin_1_inner_point_x,fin_2_inner_point_x);
		temp_4 = FIXNUM_MIN(temp,fin_1_outer_point_x);
		temp = FIXNUM_MIN(fin_1_inner_point_y,fin_2_inner_point_y);
		temp_5 = FIXNUM_MIN(temp,fin_1_outer_point_y);
		temp = FIXNUM_MAX(fin_1_inner_point_x,fin_2_inner_point_x);
		temp_6 = FIXNUM_MAX(temp,fin_1_outer_point_x);
		temp = FIXNUM_MAX(fin_1_inner_point_y,fin_2_inner_point_y);
		temp = FIXNUM_MAX(temp,fin_1_outer_point_y);
		region = add_rectangle_to_region(FIXNUM_MIN(temp_4,
			fin_2_outer_point_x),FIXNUM_MIN(temp_5,
			fin_2_outer_point_y),FIXNUM_ADD1(FIXNUM_MAX(temp_6,
			fin_2_outer_point_x)),FIXNUM_ADD1(FIXNUM_MAX(temp,
			fin_2_outer_point_y)),region);
	    }
	}
	fin_number = fin_number + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (draw_qm)
	    result = VALUES_1(spacing_between_fins_on_link);
	else
	    result = VALUES_1(region);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DRAW-CONNECTION-SUBRECTANGLES */
Object draw_connection_subrectangles(connection_subrectangle_structures_to_use,
	    right_turn_qm,previous_turn_qm,last_link_qm,next_delta,
	    initial_delta_p,variable_axis_end_position)
    Object connection_subrectangle_structures_to_use, right_turn_qm;
    Object previous_turn_qm, last_link_qm, next_delta, initial_delta_p;
    Object variable_axis_end_position;
{
    Object connection_subrectangle_structure, ab_loop_list_;
    Object subrectangle_width, first_subrectangle_structure;
    Object subrectangle_scaled_width, cumulative_scaled_width;
    Object cumulative_scaled_half_width;
    Object subrectangle_variable_axis_end_position;
    Object subrectangle_stable_axis_position;
    Object next_subrectangle_stable_axis_position;
    Object next_subrectangle_variable_axis_begin_position;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(98,109);
    if (last_link_qm) {
	connection_subrectangle_structure = Nil;
	ab_loop_list_ = connection_subrectangle_structures_to_use;
	subrectangle_width = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	connection_subrectangle_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	subrectangle_width = Orientation_horizontal_p ? 
		ISVREF(connection_subrectangle_structure,(SI_Long)5L) : 
		ISVREF(connection_subrectangle_structure,(SI_Long)4L);
	SVREF(connection_subrectangle_structure,FIX((SI_Long)7L)) = 
		variable_axis_end_position;
	draw_subrectangle_for_connection(connection_subrectangle_structure,
		subrectangle_width);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	first_subrectangle_structure = 
		CAR(connection_subrectangle_structures_to_use);
	if (Orientation_horizontal_p) {
	    subrectangle_scaled_width = 
		    ISVREF(first_subrectangle_structure,(SI_Long)5L);
	    cumulative_scaled_width = 
		    Cumulative_y_scaled_connection_stripe_width;
	    cumulative_scaled_half_width = 
		    Cumulative_y_scaled_connection_stripe_half_width;
	    if (IFIX(next_delta) == (SI_Long)0L)
		subrectangle_variable_axis_end_position = 
			variable_axis_end_position;
	    else if (initial_delta_p ||  !TRUEP(previous_turn_qm))
		subrectangle_variable_axis_end_position = 
			IFIX(Current_delta) > (SI_Long)1L ? 
			(oddp(cumulative_scaled_width) ||  
			!TRUEP(right_turn_qm) ? 
			FIXNUM_ADD(variable_axis_end_position,
			cumulative_scaled_half_width) : 
			FIX(IFIX(FIXNUM_ADD(variable_axis_end_position,
			cumulative_scaled_half_width)) +  - (SI_Long)1L)) :
			 oddp(cumulative_scaled_width) ||  
			!TRUEP(right_turn_qm) ? 
			FIXNUM_MINUS(variable_axis_end_position,
			cumulative_scaled_half_width) : 
			FIX(IFIX(FIXNUM_MINUS(variable_axis_end_position,
			cumulative_scaled_half_width)) -  - (SI_Long)1L);
	    else if (right_turn_qm ?  !EQ(previous_turn_qm,Qright) :  
		    !EQ(previous_turn_qm,Qleft))
		subrectangle_variable_axis_end_position = 
			FIXNUM_ADD(ISVREF(first_subrectangle_structure,
			(SI_Long)6L),Current_delta);
	    else if (oddp(cumulative_scaled_width) ||  !TRUEP(right_turn_qm)) {
		gensymed_symbol = IFIX(ISVREF(first_subrectangle_structure,
			(SI_Long)6L));
		gensymed_symbol_1 = IFIX(Current_delta);
		gensymed_symbol_2 = IFIX(Current_delta) > (SI_Long)1L ? 
			IFIX(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))) : 
			IFIX(FIXNUM_NEGATE(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))));
		subrectangle_variable_axis_end_position = 
			FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	    else {
		gensymed_symbol = IFIX(ISVREF(first_subrectangle_structure,
			(SI_Long)6L));
		gensymed_symbol_1 = IFIX(Current_delta);
		gensymed_symbol_2 = IFIX(Current_delta) > (SI_Long)1L ? 
			IFIX(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))) : 
			IFIX(FIXNUM_NEGATE(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))));
		subrectangle_variable_axis_end_position = 
			FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	}
	else {
	    subrectangle_scaled_width = 
		    ISVREF(first_subrectangle_structure,(SI_Long)4L);
	    cumulative_scaled_width = 
		    Cumulative_x_scaled_connection_stripe_width;
	    cumulative_scaled_half_width = 
		    Cumulative_x_scaled_connection_stripe_half_width;
	    if (IFIX(next_delta) == (SI_Long)0L)
		subrectangle_variable_axis_end_position = 
			variable_axis_end_position;
	    else if (initial_delta_p ||  !TRUEP(previous_turn_qm))
		subrectangle_variable_axis_end_position = 
			IFIX(Current_delta) > (SI_Long)1L ? 
			(oddp(cumulative_scaled_width) ||  
			!TRUEP(right_turn_qm) ? 
			FIXNUM_ADD(variable_axis_end_position,
			cumulative_scaled_half_width) : 
			FIX(IFIX(FIXNUM_ADD(variable_axis_end_position,
			cumulative_scaled_half_width)) +  - (SI_Long)1L)) :
			 oddp(cumulative_scaled_width) ||  
			!TRUEP(right_turn_qm) ? 
			FIXNUM_MINUS(variable_axis_end_position,
			cumulative_scaled_half_width) : 
			FIX(IFIX(FIXNUM_MINUS(variable_axis_end_position,
			cumulative_scaled_half_width)) -  - (SI_Long)1L);
	    else if (right_turn_qm ?  !EQ(previous_turn_qm,Qright) :  
		    !EQ(previous_turn_qm,Qleft))
		subrectangle_variable_axis_end_position = 
			FIXNUM_ADD(ISVREF(first_subrectangle_structure,
			(SI_Long)6L),Current_delta);
	    else if (oddp(cumulative_scaled_width) ||  !TRUEP(right_turn_qm)) {
		gensymed_symbol = IFIX(ISVREF(first_subrectangle_structure,
			(SI_Long)6L));
		gensymed_symbol_1 = IFIX(Current_delta);
		gensymed_symbol_2 = IFIX(Current_delta) > (SI_Long)1L ? 
			IFIX(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))) : 
			IFIX(FIXNUM_NEGATE(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))));
		subrectangle_variable_axis_end_position = 
			FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	    else {
		gensymed_symbol = IFIX(ISVREF(first_subrectangle_structure,
			(SI_Long)6L));
		gensymed_symbol_1 = IFIX(Current_delta);
		gensymed_symbol_2 = IFIX(Current_delta) > (SI_Long)1L ? 
			IFIX(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))) : 
			IFIX(FIXNUM_NEGATE(FIXNUM_ADD(cumulative_scaled_width,
			FIXNUM_NEGATE(subrectangle_scaled_width))));
		subrectangle_variable_axis_end_position = 
			FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	}
	connection_subrectangle_structure = Nil;
	ab_loop_list_ = connection_subrectangle_structures_to_use;
	subrectangle_width = Nil;
	subrectangle_stable_axis_position = Nil;
	next_subrectangle_stable_axis_position = Nil;
	next_subrectangle_variable_axis_begin_position = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	connection_subrectangle_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	subrectangle_width = Orientation_horizontal_p ? 
		ISVREF(connection_subrectangle_structure,(SI_Long)5L) : 
		ISVREF(connection_subrectangle_structure,(SI_Long)4L);
	subrectangle_stable_axis_position = 
		ISVREF(connection_subrectangle_structure,(SI_Long)8L);
	next_subrectangle_stable_axis_position = IFIX(next_delta) == 
		(SI_Long)0L ? subrectangle_stable_axis_position : 
		right_turn_qm ? subrectangle_variable_axis_end_position : 
		(SI_Long)0L > IFIX(Current_delta) ? 
		FIXNUM_ADD(subrectangle_variable_axis_end_position,
		subrectangle_width) : 
		FIXNUM_MINUS(subrectangle_variable_axis_end_position,
		subrectangle_width);
	if (IFIX(next_delta) == (SI_Long)0L)
	    next_subrectangle_variable_axis_begin_position = 
		    subrectangle_variable_axis_end_position;
	else if ( !TRUEP(right_turn_qm))
	    next_subrectangle_variable_axis_begin_position = 
		    subrectangle_stable_axis_position;
	else {
	    gensymed_symbol = IFIX(subrectangle_stable_axis_position);
	    gensymed_symbol_1 = ((SI_Long)0L > IFIX(Current_delta) ? 
		    TRUEP(Orientation_horizontal_p) :  
		    !TRUEP(Orientation_horizontal_p)) ? 
		    IFIX(FIXNUM_NEGATE(subrectangle_width)) : 
		    IFIX(subrectangle_width);
	    next_subrectangle_variable_axis_begin_position = 
		    FIX(gensymed_symbol + gensymed_symbol_1);
	}
	SVREF(connection_subrectangle_structure,FIX((SI_Long)7L)) = 
		subrectangle_variable_axis_end_position;
	draw_subrectangle_for_connection(connection_subrectangle_structure,
		subrectangle_width);
	subrectangle_variable_axis_end_position = IFIX(next_delta) == 
		(SI_Long)0L ? subrectangle_variable_axis_end_position : 
		(SI_Long)0L > IFIX(Current_delta) ? 
		FIXNUM_ADD(subrectangle_variable_axis_end_position,
		subrectangle_width) : 
		FIXNUM_MINUS(subrectangle_variable_axis_end_position,
		subrectangle_width);
	SVREF(connection_subrectangle_structure,FIX((SI_Long)6L)) = 
		next_subrectangle_variable_axis_begin_position;
	SVREF(connection_subrectangle_structure,FIX((SI_Long)8L)) = 
		next_subrectangle_stable_axis_position;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

/* DRAW-SUBRECTANGLE-FOR-CONNECTION */
Object draw_subrectangle_for_connection(connection_subrectangle_structure,
	    subrectangle_width)
    Object connection_subrectangle_structure, subrectangle_width;
{
    Object color_value, old_color_value, current_background_color_value;
    Object subrectangle_color_difference;
    Object subrectangle_variable_axis_begin_position;
    Object subrectangle_variable_axis_end_position;
    Object subrectangle_stable_axis_position;
    Object top_edge_of_subrectangle_in_window;
    Object left_edge_of_subrectangle_in_window;
    Object bottom_edge_of_subrectangle_in_window;
    Object right_edge_of_subrectangle_in_window;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,110);
    SAVE_STACK();
    color_value = ISVREF(connection_subrectangle_structure,(SI_Long)2L);
    old_color_value = Current_background_color_value;
    current_background_color_value = Current_background_color_value;
    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
	    0);
      set_current_background_color_value(color_value);
      subrectangle_color_difference = 
	      ISVREF(connection_subrectangle_structure,(SI_Long)1L);
      subrectangle_variable_axis_begin_position = 
	      ISVREF(connection_subrectangle_structure,(SI_Long)6L);
      subrectangle_variable_axis_end_position = 
	      ISVREF(connection_subrectangle_structure,(SI_Long)7L);
      subrectangle_stable_axis_position = 
	      ISVREF(connection_subrectangle_structure,(SI_Long)8L);
      top_edge_of_subrectangle_in_window = Nil;
      left_edge_of_subrectangle_in_window = Nil;
      bottom_edge_of_subrectangle_in_window = Nil;
      right_edge_of_subrectangle_in_window = Nil;
      if ( !(EQ(Current_drawing_transfer_mode,Kpaint_infered_from_xor) ? 
	      FIXNUM_EQ(subrectangle_color_difference,
	      Transparent_color_value) : 
	      IFIX(subrectangle_color_difference) == (SI_Long)0L || 
	      FIXNUM_EQ(subrectangle_color_difference,
	      Transparent_color_value))) {
	  if (Orientation_horizontal_p) {
	      if ((SI_Long)0L > IFIX(Current_delta)) {
		  top_edge_of_subrectangle_in_window = 
			  FIXNUM_MINUS(subrectangle_stable_axis_position,
			  subrectangle_width);
		  left_edge_of_subrectangle_in_window = 
			  subrectangle_variable_axis_end_position;
		  bottom_edge_of_subrectangle_in_window = 
			  subrectangle_stable_axis_position;
		  right_edge_of_subrectangle_in_window = 
			  subrectangle_variable_axis_begin_position;
	      }
	      else {
		  top_edge_of_subrectangle_in_window = 
			  subrectangle_stable_axis_position;
		  left_edge_of_subrectangle_in_window = 
			  subrectangle_variable_axis_begin_position;
		  bottom_edge_of_subrectangle_in_window = 
			  FIXNUM_ADD(subrectangle_stable_axis_position,
			  subrectangle_width);
		  right_edge_of_subrectangle_in_window = 
			  subrectangle_variable_axis_end_position;
	      }
	  }
	  else if ((SI_Long)0L > IFIX(Current_delta)) {
	      top_edge_of_subrectangle_in_window = 
		      subrectangle_variable_axis_end_position;
	      left_edge_of_subrectangle_in_window = 
		      subrectangle_stable_axis_position;
	      bottom_edge_of_subrectangle_in_window = 
		      subrectangle_variable_axis_begin_position;
	      right_edge_of_subrectangle_in_window = 
		      FIXNUM_ADD(subrectangle_stable_axis_position,
		      subrectangle_width);
	  }
	  else {
	      top_edge_of_subrectangle_in_window = 
		      subrectangle_variable_axis_begin_position;
	      left_edge_of_subrectangle_in_window = 
		      FIXNUM_MINUS(subrectangle_stable_axis_position,
		      subrectangle_width);
	      bottom_edge_of_subrectangle_in_window = 
		      subrectangle_variable_axis_end_position;
	      right_edge_of_subrectangle_in_window = 
		      subrectangle_stable_axis_position;
	  }
	  SAVE_VALUES(draw_graphic_element(6,Qadd_solid_rectangle,
		  left_edge_of_subrectangle_in_window,
		  top_edge_of_subrectangle_in_window,
		  right_edge_of_subrectangle_in_window,
		  bottom_edge_of_subrectangle_in_window,
		  subrectangle_color_difference));
      }
      else
	  SAVE_VALUES(VALUES_1(Nil));
      set_current_background_color_value(old_color_value);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* COMPUTE-NEW-VERTEX-AND-DRAW-DIAGONAL-LINK */
Object compute_new_vertex_and_draw_diagonal_link(vertex_x,vertex_y,
	    orientation_horizontal_p,current_delta,next_delta,
	    connection_subrectangle_structures,draw_fins_qm,fin_length)
    Object vertex_x, vertex_y, orientation_horizontal_p, current_delta;
    Object next_delta, connection_subrectangle_structures, draw_fins_qm;
    Object fin_length;
{
    Object new_vertex_x, new_vertex_y;
    Declare_special(2);
    Object result;

    x_note_fn_call(98,111);
    PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,1);
      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	      0);
	result = compute_new_vertex(vertex_x,vertex_y,
		Orientation_horizontal_p,Current_delta,next_delta,T);
	MVS_2(result,new_vertex_x,new_vertex_y);
	draw_diagonal_link(connection_subrectangle_structures,vertex_x,
		vertex_y,new_vertex_x,new_vertex_y);
	if (draw_fins_qm)
	    draw_fins_for_diagonal_connection_component(vertex_x,vertex_y,
		    new_vertex_x,new_vertex_y,FIX((SI_Long)1L),fin_length,
		    ISVREF(CAR(connection_subrectangle_structures),
		    (SI_Long)1L));
	result = VALUES_2(new_vertex_x,new_vertex_y);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPUTE-NEW-VERTEX */
Object compute_new_vertex(vertex_x,vertex_y,orientation_horizontal_p,
	    current_delta,next_delta,compute_in_image_units_qm)
    Object vertex_x, vertex_y, orientation_horizontal_p, current_delta;
    Object next_delta, compute_in_image_units_qm;
{
    Object delta_x, delta_y, new_vertex_x, new_vertex_y;
    Declare_special(2);
    Object result;

    x_note_fn_call(98,112);
    PUSH_SPECIAL_WITH_SYMBOL(Current_delta,Qcurrent_delta,current_delta,1);
      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	      0);
	delta_x = Nil;
	delta_y = Nil;
	new_vertex_x = Nil;
	new_vertex_y = Nil;
	if (Orientation_horizontal_p) {
	    delta_x = Current_delta;
	    delta_y = next_delta;
	}
	else {
	    delta_y = Current_delta;
	    delta_x = next_delta;
	}
	if (compute_in_image_units_qm) {
	    new_vertex_x = FIXNUM_ADD(vertex_x,delta_x);
	    new_vertex_y = FIXNUM_ADD(vertex_y,delta_y);
	}
	else {
	    new_vertex_x = FIXNUM_ADD(vertex_x,delta_x);
	    new_vertex_y = FIXNUM_ADD(vertex_y,delta_y);
	}
	result = VALUES_2(new_vertex_x,new_vertex_y);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DRAW-DIAGONAL-LINK */
Object draw_diagonal_link(connection_subrectangle_structures_to_use,
	    old_vertex_x,old_vertex_y,vertex_x,vertex_y)
    Object connection_subrectangle_structures_to_use, old_vertex_x;
    Object old_vertex_y, vertex_x, vertex_y;
{
    Object color_difference;

    x_note_fn_call(98,113);
    color_difference = 
	    ISVREF(CAR(connection_subrectangle_structures_to_use),(SI_Long)1L);
    return draw_line(old_vertex_x,old_vertex_y,vertex_x,vertex_y,
	    color_difference);
}

/* ADD-LOOSE-ENDS-AS-SUBBLOCKS-AND-SHIFT */
Object add_loose_ends_as_subblocks_and_shift(block,superblock,delta_x,delta_y)
    Object block, superblock, delta_x, delta_y;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, loose_end, temp;
    Object ab_less_than_branch_qm_, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,114);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      loose_end = Nil;
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
      loose_end = EQ(ISVREF(connection,(SI_Long)3L),block) ? 
	      ISVREF(connection,(SI_Long)2L) : ISVREF(connection,(SI_Long)3L);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(loose_end,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
      gensymed_symbol_1 = loose_end;
      gensymed_symbol_2 = delta_x;
      gensymed_symbol_3 = delta_y;
      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	      gensymed_symbol_3);
      add_subblock(loose_end,superblock);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* ADJUST-CONNECTIONS-ACCORDING-TO-NEW-EDGE */
Object adjust_connections_according_to_new_edge(block,straight_connections,
	    side_to_shift,delta_width,delta_height)
    Object block, straight_connections, side_to_shift, delta_width;
    Object delta_height;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,115);
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
      adjust_connection_according_to_new_edge(connection,block,
	      straight_connections,side_to_shift,delta_width,delta_height,
	      EQ(ISVREF(connection,(SI_Long)3L),block) ? T : Nil);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* ADJUST-CONNECTION-ACCORDING-TO-NEW-EDGE */
Object adjust_connection_according_to_new_edge(connection,block,
	    straight_connections,side_to_shift,delta_width,delta_height,
	    output_connection_qm)
    Object connection, block, straight_connections, side_to_shift, delta_width;
    Object delta_height, output_connection_qm;
{
    Object side;

    x_note_fn_call(98,116);
    side = output_connection_qm ? ISVREF(array_constant,
	    IFIX(ISVREF(connection,(SI_Long)5L)) & (SI_Long)3L) : 
	    ISVREF(array_constant,IFIX(ISVREF(connection,(SI_Long)4L)) & 
	    (SI_Long)3L);
    if (EQ(side,side_to_shift))
	shift_connection(connection,block,straight_connections,
		output_connection_qm,memq_function(side,list_constant) ? 
		delta_width : FIX((SI_Long)0L),memq_function(side,
		list_constant_1) ? delta_height : FIX((SI_Long)0L));
    if (memq_function(side,list_constant_1)) {
	if (EQ(side_to_shift,Qleft))
	    return shift_end_position_of_connection(block,connection,
		    straight_connections,output_connection_qm,side,
		    FIXNUM_NEGATE(delta_width));
	else if (EQ(side_to_shift,Qright))
	    return shift_end_position_of_connection(block,connection,
		    straight_connections,output_connection_qm,side,
		    FIX((SI_Long)0L));
	else
	    return VALUES_1(Qnil);
    }
    else if (memq_function(side,list_constant)) {
	if (EQ(side_to_shift,Qtop))
	    return shift_end_position_of_connection(block,connection,
		    straight_connections,output_connection_qm,side,
		    FIXNUM_NEGATE(delta_height));
	else if (EQ(side_to_shift,Qbottom))
	    return shift_end_position_of_connection(block,connection,
		    straight_connections,output_connection_qm,side,
		    FIX((SI_Long)0L));
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* SHIFT-END-POSITION-OF-CONNECTION */
Object shift_end_position_of_connection(block,connection,
	    straight_connections,output_connection_qm,side,shift)
    Object block, connection, straight_connections, output_connection_qm, side;
    Object shift;
{
    Object end_position, left_or_right_side_qm, gensymed_symbol;
    Object actual_position, shift_difference_qm, new_end_position;
    SI_Long desired_position, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long maximum_position;
    char temp;

    x_note_fn_call(98,117);
    end_position = output_connection_qm ? ISVREF(connection,(SI_Long)5L) : 
	    ISVREF(connection,(SI_Long)4L);
    desired_position = (IFIX(end_position) >>  -  - (SI_Long)2L) + IFIX(shift);
    left_or_right_side_qm = memq_function(side,list_constant);
    if (left_or_right_side_qm) {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    }
    else {
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(block,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    }
    gensymed_symbol_2 = (SI_Long)1L;
    maximum_position = gensymed_symbol_1 - gensymed_symbol_2;
    actual_position = Nil;
    shift_difference_qm = Nil;
    new_end_position = Nil;
    if (desired_position < (SI_Long)0L) {
	actual_position = FIX((SI_Long)0L);
	shift_difference_qm = FIX(IFIX(actual_position) - desired_position);
    }
    else if (desired_position > maximum_position) {
	actual_position = FIX(maximum_position);
	shift_difference_qm = FIX(IFIX(actual_position) - desired_position);
    }
    else
	actual_position = FIX(desired_position);
    if (EQ(side,Qtop))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(side,Qleft))
	gensymed_symbol_1 = (SI_Long)1L;
    else if (EQ(side,Qbottom))
	gensymed_symbol_1 = (SI_Long)2L;
    else
	gensymed_symbol_1 = (SI_Long)3L;
    gensymed_symbol_2 = IFIX(actual_position) << (SI_Long)2L;
    new_end_position = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    if (shift_difference_qm) {
	if (left_or_right_side_qm)
	    shift_connection(connection,block,straight_connections,
		    output_connection_qm,FIX((SI_Long)0L),shift_difference_qm);
	else
	    shift_connection(connection,block,straight_connections,
		    output_connection_qm,shift_difference_qm,FIX((SI_Long)0L));
    }
    if (output_connection_qm) {
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	return VALUES_1(SVREF(connection,FIX((SI_Long)5L)) = new_end_position);
    }
    else {
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	return VALUES_1(SVREF(connection,FIX((SI_Long)4L)) = new_end_position);
    }
}

/* SHIFT-CONNECTION */
Object shift_connection(connection,block,straight_connections,
	    output_connection_qm,delta_x,delta_y)
    Object connection, block, straight_connections, output_connection_qm;
    Object delta_x, delta_y;
{
    Object temp, delta_for_straight_connection_qm, object_at_other_end;
    Object sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(98,118);
    temp = assq_function(connection,straight_connections);
    delta_for_straight_connection_qm = CDR(temp);
    object_at_other_end = output_connection_qm ? ISVREF(connection,
	    (SI_Long)2L) : ISVREF(connection,(SI_Long)3L);
    if (delta_for_straight_connection_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(object_at_other_end,
		(SI_Long)1L),(SI_Long)19L);
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol_3 = 
		    ISVREF(ISVREF(ISVREF(ISVREF(object_at_other_end,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	    gensymed_symbol_4 = object_at_other_end;
	    gensymed_symbol_5 = delta_x;
	    gensymed_symbol_6 = delta_y;
	    return inline_funcall_3(gensymed_symbol_3,gensymed_symbol_4,
		    gensymed_symbol_5,gensymed_symbol_6);
	}
	else {
	    put_kink_into_connection_if_straight_1(connection,
		    delta_for_straight_connection_qm);
	    if (output_connection_qm)
		return change_connection_deltas_for_object_being_dragged(connection,
			block,delta_x,delta_y);
	    else
		return VALUES_1(Nil);
	}
    }
    else if (output_connection_qm)
	return change_connection_deltas_for_object_being_dragged(connection,
		block,delta_x,delta_y);
    else
	return VALUES_1(Nil);
}

/* UPDATE-INPUT-CONNECTIONS-OF-ENTITY */
Object update_input_connections_of_entity varargs_1(int, n)
{
    Object entity, erase_qm;
    Object icon_description_for_inhibiting_qm, workspace_qm, scope_conses;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,119);
    INIT_ARGS_nonrelocating();
    entity = REQUIRED_ARG_nonrelocating();
    erase_qm = REQUIRED_ARG_nonrelocating();
    icon_description_for_inhibiting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workspace_qm = get_workspace_if_any(entity);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)2L),entity))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      if ( !EQ(ISVREF(connection,(SI_Long)3L),entity) && ( 
	      !TRUEP(icon_description_for_inhibiting_qm) ||  
	      !EQ(icon_description_for_instance(ISVREF(connection,
	      (SI_Long)3L)),icon_description_for_inhibiting_qm)))
	  update_connection_images(erase_qm,workspace_qm,connection);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

/* MAGNIFY-ICON */
Object magnify_icon(entity,x_magnification_for_current_rotation_qm,
	    y_magnification_for_current_rotation_qm,new_left_edge_qm,
	    new_top_edge_qm,note_as_kb_state_change_qm)
    Object entity, x_magnification_for_current_rotation_qm;
    Object y_magnification_for_current_rotation_qm, new_left_edge_qm;
    Object new_top_edge_qm, note_as_kb_state_change_qm;
{
    Object workspace_qm, icon_attributes_plist, icon_description;
    Object x_magnification_for_current_rotation;
    Object y_magnification_for_current_rotation;
    Object old_x_magnification_with_no_rotation_qm;
    Object old_y_magnification_with_no_rotation_qm, gensymed_symbol_1;
    Object x_magnification_with_no_rotation_qm;
    Object y_magnification_with_no_rotation_qm;
    Object old_x_magnification_for_current_rotation_qm;
    Object old_y_magnification_for_current_rotation_qm;
    Object unmagnified_block_width, unmagnified_block_height;
    Object reflection_and_rotation_qm, delta_right_edge, delta_bottom_edge;
    Object old_x_magnification_for_current_rotation_qm_temp;
    Object x_magnification_with_no_rotation_qm_temp;
    Object unmagnified_block_height_temp, temp, gensymed_symbol_3;
    SI_Long gensymed_symbol, gensymed_symbol_2, delta_left_edge;
    SI_Long delta_top_edge;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,120);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      workspace_qm = get_workspace_if_any(entity);
      icon_attributes_plist = ISVREF(entity,(SI_Long)17L);
      icon_description = ISVREF(entity,(SI_Long)16L);
      x_magnification_for_current_rotation = 
	      x_magnification_for_current_rotation_qm;
      if (x_magnification_for_current_rotation);
      else
	  x_magnification_for_current_rotation = ISVREF(icon_description,
		  (SI_Long)6L);
      if (x_magnification_for_current_rotation);
      else
	  x_magnification_for_current_rotation = 
		  convert_to_magnification(FIX((SI_Long)1L));
      y_magnification_for_current_rotation = 
	      y_magnification_for_current_rotation_qm;
      if (y_magnification_for_current_rotation);
      else
	  y_magnification_for_current_rotation = ISVREF(icon_description,
		  (SI_Long)7L);
      if (y_magnification_for_current_rotation);
      else
	  y_magnification_for_current_rotation = 
		  convert_to_magnification(FIX((SI_Long)1L));
      old_x_magnification_with_no_rotation_qm = getf(icon_attributes_plist,
	      Qx_magnification,_);
      if (old_x_magnification_with_no_rotation_qm);
      else
	  old_x_magnification_with_no_rotation_qm = 
		  ISVREF(icon_description,(SI_Long)6L);
      old_y_magnification_with_no_rotation_qm = getf(icon_attributes_plist,
	      Qy_magnification,_);
      if (old_y_magnification_with_no_rotation_qm);
      else
	  old_y_magnification_with_no_rotation_qm = 
		  ISVREF(icon_description,(SI_Long)7L);
      if (new_left_edge_qm) {
	  gensymed_symbol = IFIX(new_left_edge_qm);
	  gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	  delta_left_edge = gensymed_symbol - gensymed_symbol_2;
      }
      else
	  delta_left_edge = (SI_Long)0L;
      if (new_top_edge_qm) {
	  gensymed_symbol = IFIX(new_top_edge_qm);
	  gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	  delta_top_edge = gensymed_symbol - gensymed_symbol_2;
      }
      else
	  delta_top_edge = (SI_Long)0L;
      x_magnification_with_no_rotation_qm = 
	      x_magnification_for_current_rotation_qm;
      y_magnification_with_no_rotation_qm = 
	      y_magnification_for_current_rotation_qm;
      old_x_magnification_for_current_rotation_qm = 
	      old_x_magnification_with_no_rotation_qm;
      old_y_magnification_for_current_rotation_qm = 
	      old_y_magnification_with_no_rotation_qm;
      unmagnified_block_width = 
	      getfq_function_no_default(icon_attributes_plist,Qwidth);
      if (unmagnified_block_width);
      else
	  unmagnified_block_width = ISVREF(icon_description,(SI_Long)1L);
      unmagnified_block_height = 
	      getfq_function_no_default(icon_attributes_plist,Qheight);
      if (unmagnified_block_height);
      else
	  unmagnified_block_height = ISVREF(icon_description,(SI_Long)2L);
      reflection_and_rotation_qm = getfq_function_no_default(ISVREF(entity,
	      (SI_Long)17L),Qreflection_and_rotation);
      delta_right_edge = Nil;
      delta_bottom_edge = Nil;
      if (rotated_by_90_p(reflection_and_rotation_qm)) {
	  old_x_magnification_for_current_rotation_qm_temp = 
		  old_y_magnification_for_current_rotation_qm;
	  x_magnification_with_no_rotation_qm_temp = 
		  y_magnification_with_no_rotation_qm;
	  unmagnified_block_height_temp = unmagnified_block_width;
	  old_y_magnification_for_current_rotation_qm = 
		  old_x_magnification_for_current_rotation_qm;
	  old_x_magnification_for_current_rotation_qm = 
		  old_x_magnification_for_current_rotation_qm_temp;
	  y_magnification_with_no_rotation_qm = 
		  x_magnification_with_no_rotation_qm;
	  x_magnification_with_no_rotation_qm = 
		  x_magnification_with_no_rotation_qm_temp;
	  unmagnified_block_width = unmagnified_block_height;
	  unmagnified_block_height = unmagnified_block_height_temp;
      }
      gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol = IFIX(gensymed_symbol_1);
      gensymed_symbol_2 = IFIX(FIXNUM_TIMES(unmagnified_block_width,
	      x_magnification_for_current_rotation)) + (SI_Long)128L >>  - 
	       - (SI_Long)8L;
      gensymed_symbol = gensymed_symbol + gensymed_symbol_2;
      gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)2L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      delta_right_edge = FIX(gensymed_symbol - gensymed_symbol_2);
      gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol = IFIX(gensymed_symbol_1);
      gensymed_symbol_2 = IFIX(FIXNUM_TIMES(unmagnified_block_height,
	      y_magnification_for_current_rotation)) + (SI_Long)128L >>  - 
	       - (SI_Long)8L;
      gensymed_symbol = gensymed_symbol + gensymed_symbol_2;
      gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)3L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      delta_bottom_edge = FIX(gensymed_symbol - gensymed_symbol_2);
      if (workspace_qm) {
	  update_images_of_block(entity,T,Nil);
	  update_input_connections_of_entity(2,entity,T);
	  magnify_connections_on_block_in_workspace(entity,
		  x_magnification_for_current_rotation,
		  y_magnification_for_current_rotation,
		  old_x_magnification_for_current_rotation_qm,
		  old_y_magnification_for_current_rotation_qm,
		  FIX(delta_left_edge),FIX(delta_top_edge),
		  delta_right_edge,delta_bottom_edge);
	  change_icon_attribute(entity,Qx_magnification,
		  x_magnification_with_no_rotation_qm);
	  change_icon_attribute(entity,Qy_magnification,
		  y_magnification_with_no_rotation_qm);
	  gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol = IFIX(gensymed_symbol_1);
	  gensymed_symbol_2 = IFIX(delta_right_edge);
	  temp = FIX(gensymed_symbol + gensymed_symbol_2);
	  gensymed_symbol_1 = ISVREF(entity,(SI_Long)14L);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol = IFIX(gensymed_symbol_1);
	  gensymed_symbol_2 = IFIX(delta_bottom_edge);
	  change_edges_of_block(entity,Nil,Nil,temp,FIX(gensymed_symbol + 
		  gensymed_symbol_2));
	  if (new_left_edge_qm) {
	      gensymed_symbol_1 = ISVREF(ISVREF(ISVREF(ISVREF(entity,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	      gensymed_symbol_3 = entity;
	      gensymed_symbol = delta_left_edge;
	      gensymed_symbol_2 = delta_top_edge;
	      inline_funcall_3(gensymed_symbol_1,gensymed_symbol_3,
		      FIX(gensymed_symbol),FIX(gensymed_symbol_2));
	      if (G2_has_v5_mode_windows_p &&  
		      !TRUEP(Ws_protocol_handle_moves_from_edge_change_p))
		  send_ws_representations_item_moved(entity,
			  FIX(delta_left_edge),FIX(delta_top_edge));
	  }
	  enlarge_workspace_for_block_and_subblocks_as_necessary(entity,Nil);
	  update_images_of_block(entity,Nil,Nil);
	  result = update_input_connections_of_entity(2,entity,Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* MAGNIFY-CONNECTIONS-ON-BLOCK-IN-WORKSPACE */
Object magnify_connections_on_block_in_workspace(block,x_magnification,
	    y_magnification,old_x_magnification_qm,old_y_magnification_qm,
	    delta_left_edge,delta_top_edge,delta_right_edge,delta_bottom_edge)
    Object block, x_magnification, y_magnification, old_x_magnification_qm;
    Object old_y_magnification_qm, delta_left_edge, delta_top_edge;
    Object delta_right_edge, delta_bottom_edge;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, input_end_object;
    Object output_end_object, connection_is_straight_qm_1;
    Object object_at_other_end_is_loose_end_qm, temp, ab_less_than_branch_qm_;
    Object sub_class_bit_vector, new_end_position, delta_x, delta_y;
    Object gensymed_symbol_4, gensymed_symbol_5, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,121);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      input_end_object = Nil;
      output_end_object = Nil;
      connection_is_straight_qm_1 = Nil;
      object_at_other_end_is_loose_end_qm = Nil;
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
      input_end_object = ISVREF(connection,(SI_Long)3L);
      output_end_object = ISVREF(connection,(SI_Long)2L);
      connection_is_straight_qm_1 = connection_is_straight_qm(connection);
      object_at_other_end_is_loose_end_qm = Nil;
      if (EQ(input_end_object,block)) {
	  sub_class_bit_vector = ISVREF(ISVREF(output_end_object,
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
	      object_at_other_end_is_loose_end_qm = (SI_Long)0L < 
		      gensymed_symbol_1 ? T : Nil;
	  }
	  else
	      object_at_other_end_is_loose_end_qm = Nil;
	  if (connection_is_straight_qm_1 &&  
		  !TRUEP(object_at_other_end_is_loose_end_qm))
	      put_kink_into_connection_if_straight_1(connection,
		      connection_is_straight_qm_1);
	  result = magnify_end_position(ISVREF(connection,(SI_Long)5L),
		  x_magnification,y_magnification,block,
		  old_x_magnification_qm,old_y_magnification_qm,
		  delta_left_edge,delta_top_edge,delta_right_edge,
		  delta_bottom_edge);
	  MVS_3(result,new_end_position,delta_x,delta_y);
	  temp_1 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_1);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_1)
	      note_change_to_connection_1(connection);
	  SVREF(connection,FIX((SI_Long)5L)) = new_end_position;
	  if (connection_is_straight_qm_1 && 
		  object_at_other_end_is_loose_end_qm) {
	      gensymed_symbol = 
		      ISVREF(ISVREF(ISVREF(ISVREF(output_end_object,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	      gensymed_symbol_4 = output_end_object;
	      gensymed_symbol_5 = delta_x;
	      gensymed_symbol_6 = delta_y;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6);
	  }
	  else
	      change_connection_deltas_for_object_being_dragged(connection,
		      block,delta_x,delta_y);
      }
      else {
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
	      object_at_other_end_is_loose_end_qm = (SI_Long)0L < 
		      gensymed_symbol_1 ? T : Nil;
	  }
	  else
	      object_at_other_end_is_loose_end_qm = Nil;
	  if (connection_is_straight_qm_1 &&  
		  !TRUEP(object_at_other_end_is_loose_end_qm))
	      put_kink_into_connection_if_straight_1(connection,
		      connection_is_straight_qm_1);
	  result = magnify_end_position(ISVREF(connection,(SI_Long)4L),
		  x_magnification,y_magnification,block,
		  old_x_magnification_qm,old_y_magnification_qm,
		  delta_left_edge,delta_top_edge,delta_right_edge,
		  delta_bottom_edge);
	  MVS_3(result,new_end_position,delta_x,delta_y);
	  temp_1 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_1);
	  else {
	      gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_1)
	      note_change_to_connection_1(connection);
	  SVREF(connection,FIX((SI_Long)4L)) = new_end_position;
	  if (connection_is_straight_qm_1 && 
		  object_at_other_end_is_loose_end_qm) {
	      gensymed_symbol = 
		      ISVREF(ISVREF(ISVREF(ISVREF(input_end_object,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	      gensymed_symbol_4 = input_end_object;
	      gensymed_symbol_5 = delta_x;
	      gensymed_symbol_6 = delta_y;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6);
	  }
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MAGNIFY-END-POSITION */
Object magnify_end_position(end_position,x_magnification,y_magnification,
	    block,old_x_magnification_qm,old_y_magnification_qm,
	    delta_left_edge,delta_top_edge,delta_right_edge,delta_bottom_edge)
    Object end_position, x_magnification, y_magnification, block;
    Object old_x_magnification_qm, old_y_magnification_qm, delta_left_edge;
    Object delta_top_edge, delta_right_edge, delta_bottom_edge;
{
    Object side, shift_in_y_direction_qm, delta_x, delta_y;
    SI_Long position_on_side, temp, new_position_on_side, delta;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,122);
    side = ISVREF(array_constant,IFIX(end_position) & (SI_Long)3L);
    position_on_side = IFIX(end_position) >>  -  - (SI_Long)2L;
    shift_in_y_direction_qm = memq_function(side,list_constant);
    if (shift_in_y_direction_qm) {
	if (old_y_magnification_qm) {
	    temp = IFIX(FIXNUM_TIMES(inverse_magnify(FIX(position_on_side),
		    old_y_magnification_qm),y_magnification)) + (SI_Long)128L;
	    new_position_on_side = temp >>  -  - (SI_Long)8L;
	}
	else
	    new_position_on_side = position_on_side * 
		    IFIX(y_magnification) + (SI_Long)128L >>  -  - (SI_Long)8L;
    }
    else if (old_x_magnification_qm) {
	temp = IFIX(FIXNUM_TIMES(inverse_magnify(FIX(position_on_side),
		old_x_magnification_qm),x_magnification)) + (SI_Long)128L;
	new_position_on_side = temp >>  -  - (SI_Long)8L;
    }
    else
	new_position_on_side = position_on_side * IFIX(x_magnification) + 
		(SI_Long)128L >>  -  - (SI_Long)8L;
    delta = new_position_on_side - position_on_side;
    delta_x = Nil;
    delta_y = Nil;
    if (EQ(side,Qleft)) {
	delta_x = delta_left_edge;
	delta_y = FIX(delta + IFIX(delta_top_edge));
    }
    else if (EQ(side,Qtop)) {
	delta_x = FIX(delta + IFIX(delta_left_edge));
	delta_y = delta_top_edge;
    }
    else if (EQ(side,Qright)) {
	delta_x = FIXNUM_ADD(delta_left_edge,delta_right_edge);
	delta_y = FIX(delta + IFIX(delta_top_edge));
    }
    else if (EQ(side,Qbottom)) {
	delta_x = FIX(delta + IFIX(delta_left_edge));
	delta_y = FIXNUM_ADD(delta_top_edge,delta_bottom_edge);
    }
    if (EQ(side,Qtop))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(side,Qleft))
	gensymed_symbol = (SI_Long)1L;
    else if (EQ(side,Qbottom))
	gensymed_symbol = (SI_Long)2L;
    else
	gensymed_symbol = (SI_Long)3L;
    gensymed_symbol_1 = new_position_on_side << (SI_Long)2L;
    return VALUES_3(FIX(gensymed_symbol + gensymed_symbol_1),delta_x,delta_y);
}

static Object Qreflected;          /* reflected */

static Object Qnormal;             /* normal */

static Object Qreflected_clockwise_90;  /* reflected-clockwise-90 */

static Object Qclockwise_90;       /* clockwise-90 */

static Object Qreflected_clockwise_180;  /* reflected-clockwise-180 */

static Object Qclockwise_180;      /* clockwise-180 */

static Object Qreflected_clockwise_270;  /* reflected-clockwise-270 */

static Object Qclockwise_270;      /* clockwise-270 */

/* ROTATE-AND-REFLECT-ICON */
Object rotate_and_reflect_icon(entity,
	    clockwise_angle_of_rotation_in_degrees,
	    reflect_about_x_center_qm,
	    x_center_of_rotation_sl_reflection_qm,y_center_of_rotation_qm,
	    note_as_kb_state_change_qm)
    Object entity, clockwise_angle_of_rotation_in_degrees;
    Object reflect_about_x_center_qm, x_center_of_rotation_sl_reflection_qm;
    Object y_center_of_rotation_qm, note_as_kb_state_change_qm;
{
    Object delta_rotation_and_reflection;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,123);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    0);
      clockwise_angle_of_rotation_in_degrees = ltimes(FIX((SI_Long)90L),
	      mod(l_round(clockwise_angle_of_rotation_in_degrees,
	      FIX((SI_Long)90L)),FIX((SI_Long)4L)));
      if ( !(FIXNUMP(clockwise_angle_of_rotation_in_degrees) && 
	      FIXNUM_LE(FIX((SI_Long)-32768L),
	      clockwise_angle_of_rotation_in_degrees) && 
	      FIXNUM_LE(clockwise_angle_of_rotation_in_degrees,
	      FIX((SI_Long)32767L))))
	  delta_rotation_and_reflection = Nil;
      else
	  switch (INTEGER_TO_SHORT(clockwise_angle_of_rotation_in_degrees)) {
	    case 0:
	      delta_rotation_and_reflection = reflect_about_x_center_qm ? 
		      Qreflected : Qnormal;
	      break;
	    case 90:
	      delta_rotation_and_reflection = reflect_about_x_center_qm ? 
		      Qreflected_clockwise_90 : Qclockwise_90;
	      break;
	    case 180:
	      delta_rotation_and_reflection = reflect_about_x_center_qm ? 
		      Qreflected_clockwise_180 : Qclockwise_180;
	      break;
	    case 270:
	      delta_rotation_and_reflection = reflect_about_x_center_qm ? 
		      Qreflected_clockwise_270 : Qclockwise_270;
	      break;
	    default:
	      delta_rotation_and_reflection = Nil;
	      break;
	  }
      rotate_and_reflect_icon_symbolically(entity,
	      delta_rotation_and_reflection,
	      x_center_of_rotation_sl_reflection_qm,
	      y_center_of_rotation_qm,Note_as_kb_state_change_qm);
      if (G2_has_v5_mode_windows_p)
	  result = send_ws_representations_item_rotated(entity,
		  getfq_function_no_default(ISVREF(entity,(SI_Long)17L),
		  Qreflection_and_rotation));
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qicon_position;      /* icon-position */

static Object Qicon_orientation;   /* icon-orientation */

/* ROTATE-AND-REFLECT-ICON-SYMBOLICALLY */
Object rotate_and_reflect_icon_symbolically(entity,
	    delta_rotation_and_reflection,
	    x_center_of_rotation_sl_reflection_qm,y_center_of_rotation_qm,
	    note_as_kb_state_change_qm)
    Object entity, delta_rotation_and_reflection;
    Object x_center_of_rotation_sl_reflection_qm, y_center_of_rotation_qm;
    Object note_as_kb_state_change_qm;
{
    Object do_not_note_permanent_changes_p, workspace_qm, x2;
    Object extreme_left_edge, extreme_top_edge, extreme_right_edge;
    Object extreme_bottom_edge, scope_conses, ab_node_stack_, ab_current_node_;
    Object gensymed_symbol, ab_skip_list_form_, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, input_end_object, loose_end_maybe;
    Object temp_1, ab_less_than_branch_qm_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(98,124);
    PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	    2);
      do_not_note_permanent_changes_p = Note_as_kb_state_change_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	      1);
	if (Note_as_kb_state_change_qm) {
	    note_kb_state_change(entity,Qicon_position);
	    note_kb_state_change(entity,Qicon_orientation);
	}
	if ( !TRUEP(x_center_of_rotation_sl_reflection_qm))
	    x_center_of_rotation_sl_reflection_qm = item_x_position(entity);
	if ( !TRUEP(y_center_of_rotation_qm))
	    y_center_of_rotation_qm = FIXNUM_NEGATE(item_y_position(entity));
	workspace_qm = get_workspace_if_any(entity);
	if (workspace_qm &&  !EQ(delta_rotation_and_reflection,Qnormal)) {
	    if (SIMPLE_VECTOR_P(entity) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(entity,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(entity,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		redraw_transfer_representations_of_block(entity,T);
	    result = determine_extreme_edges_of_block(entity);
	    MVS_4(result,extreme_left_edge,extreme_top_edge,
		    extreme_right_edge,extreme_bottom_edge);
	    update_images_of_rectangle_of_block(entity,T,extreme_left_edge,
		    extreme_top_edge,extreme_right_edge,extreme_bottom_edge);
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(entity,(SI_Long)14L));
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
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      input_end_object = Nil;
	      loose_end_maybe = Nil;
	      gensymed_symbol = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol)) {
		  temp_1 = M_CAR(gensymed_symbol);
		  temp = SIMPLE_VECTOR_P(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  temp_1 = M_CDR(gensymed_symbol);
		  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
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
		    next_loop_2:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
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
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_)
		  goto end_1;
	      goto next_loop_1;
	    end_loop_1:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_2;
	      connection = ab_connection_;
	      input_end_object = ISVREF(connection,(SI_Long)3L);
	      loose_end_maybe = EQ(input_end_object,entity) ? 
		      ISVREF(connection,(SI_Long)2L) : input_end_object;
	      sub_class_bit_vector = ISVREF(ISVREF(loose_end_maybe,
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
	      if (temp) {
		  update_images_of_block(loose_end_maybe,T,Nil);
		  reflect_and_rotate_block_in_workspace(loose_end_maybe,
			  delta_rotation_and_reflection,
			  x_center_of_rotation_sl_reflection_qm,
			  y_center_of_rotation_qm);
	      }
	      else if ( !EQ(input_end_object,entity))
		  update_connection_images(T,workspace_qm,connection);
	      goto next_loop;
	    end_loop_2:;
	    POP_SPECIAL();
	    reflect_and_rotate_block_in_workspace(entity,
		    delta_rotation_and_reflection,
		    x_center_of_rotation_sl_reflection_qm,
		    y_center_of_rotation_qm);
	    result = determine_extreme_edges_of_block(entity);
	    MVS_4(result,extreme_left_edge,extreme_top_edge,
		    extreme_right_edge,extreme_bottom_edge);
	    if ( !TRUEP(Note_as_kb_state_change_qm))
		enlarge_workspace_if_necessary(5,workspace_qm,
			extreme_left_edge,extreme_top_edge,
			extreme_right_edge,extreme_bottom_edge);
	    update_images_of_rectangle_of_block(entity,Nil,
		    extreme_left_edge,extreme_top_edge,extreme_right_edge,
		    extreme_bottom_edge);
	    update_input_connections_of_entity(2,entity,Nil);
	    temp_1 = extreme_left_edge;
	    gensymed_symbol = ISVREF(workspace_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(ISVREF(workspace_qm,(SI_Long)17L));
	    temp = FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2));
	    if (temp);
	    else {
		temp_1 = extreme_top_edge;
		gensymed_symbol = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(ISVREF(workspace_qm,(SI_Long)17L));
		temp = FIXNUM_LT(temp_1,FIX(gensymed_symbol_1 + 
			gensymed_symbol_2));
	    }
	    if (temp);
	    else {
		temp_1 = extreme_right_edge;
		gensymed_symbol = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(ISVREF(workspace_qm,(SI_Long)17L));
		temp = FIXNUM_GT(temp_1,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2));
	    }
	    if (temp);
	    else {
		temp_1 = extreme_bottom_edge;
		gensymed_symbol = ISVREF(workspace_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(ISVREF(workspace_qm,(SI_Long)17L));
		temp = FIXNUM_GT(temp_1,FIX(gensymed_symbol_1 - 
			gensymed_symbol_2));
	    }
	    if (temp) {
		if (Note_as_kb_state_change_qm) {
		    temp_1 = 
			    invert_reflection_and_rotation(delta_rotation_and_reflection);
		    rotate_and_reflect_icon_symbolically(entity,temp_1,
			    x_center_of_rotation_sl_reflection_qm,
			    y_center_of_rotation_qm,Nil);
		}
	    }
	    if (SIMPLE_VECTOR_P(entity) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(entity)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(entity,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(entity,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		redraw_transfer_representations_of_block(entity,Nil);
	    if ((SI_Long)0L != (IFIX(ISVREF(entity,(SI_Long)5L)) & 
		    (SI_Long)2097152L))
		result = update_icon_views(entity);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* REFLECT-AND-ROTATE-LOOSE-ENDS-OF-BLOCK-IN-WORKSPACE */
Object reflect_and_rotate_loose_ends_of_block_in_workspace(block,
	    reflection_and_rotation_qm,x_center_of_block,y_center_of_block)
    Object block, reflection_and_rotation_qm, x_center_of_block;
    Object y_center_of_block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, loose_end_maybe, temp;
    Object ab_less_than_branch_qm_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,125);
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      loose_end_maybe = Nil;
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
      loose_end_maybe = EQ(ISVREF(connection,(SI_Long)3L),block) ? 
	      ISVREF(connection,(SI_Long)2L) : ISVREF(connection,(SI_Long)3L);
      sub_class_bit_vector = ISVREF(ISVREF(loose_end_maybe,(SI_Long)1L),
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
	  temp_1 = (SI_Long)0L < gensymed_symbol_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  reflect_and_rotate_block_in_workspace(loose_end_maybe,
		  reflection_and_rotation_qm,x_center_of_block,
		  y_center_of_block);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* REFLECT-AND-ROTATE-CONNECTIONS-ON-BLOCK-IN-WORKSPACE */
Object reflect_and_rotate_connections_on_block_in_workspace(block,
	    reflection_and_rotation)
    Object block, reflection_and_rotation;
{
    Object rotated_initial_orientation_horizontal_p, scope_conses;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, delta_or_deltas_qm, temp;
    Object ab_less_than_branch_qm_, input_end_object, input_end_position;
    Object input_end_side, gensymed_symbol_1, output_end_object;
    Object output_end_position, output_end_side, svref_new_value;
    Object sub_class_bit_vector, frame, symbol, delta_x_multiplier;
    Object delta_y_multiplier, side, delta, ab_loop_list_;
    Object orientation_horizontal_p, new_deltas, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_iter_flag_;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, superior_class_bit_number;
    SI_Long sub_class_vector_index;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(98,126);
    rotated_initial_orientation_horizontal_p = Nil;
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
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      delta_or_deltas_qm = Nil;
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
      delta_or_deltas_qm = ISVREF(connection,(SI_Long)6L);
      gensymed_symbol = connection;
      input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
      input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
      input_end_side = ISVREF(array_constant,IFIX(input_end_position) & 
	      (SI_Long)3L);
      input_end_position_on_side = IFIX(input_end_position) >>  -  - 
	      (SI_Long)2L;
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
      if (EQ(input_end_object,block)) {
	  temp_1 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_1);
	  else {
	      gensymed_symbol_2 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp_1 =  !((SI_Long)0L != gensymed_symbol_2) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_1)
	      note_change_to_connection_1(connection);
	  svref_new_value = 
		  reflect_and_rotate_end_position(input_end_position,
		  reflection_and_rotation,block);
	  SVREF(connection,FIX((SI_Long)5L)) = svref_new_value;
      }
      if (EQ(output_end_object,block)) {
	  temp_1 = TRUEP(Noting_changes_to_kb_p);
	  if (temp_1);
	  else {
	      gensymed_symbol_2 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		      (SI_Long)128L;
	      temp_1 =  !((SI_Long)0L != gensymed_symbol_2) ?  
		      !TRUEP(Geometric_change_to_connection_is_temporary_p) 
		      : TRUEP(Nil);
	  }
	  if (temp_1)
	      note_change_to_connection_1(connection);
	  svref_new_value = 
		  reflect_and_rotate_end_position(output_end_position,
		  reflection_and_rotation,block);
	  SVREF(connection,FIX((SI_Long)4L)) = svref_new_value;
      }
      if (delta_or_deltas_qm) {
	  sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	  temp_1 =  !temp_1;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  frame = get_block_at_other_end_of_connection(connection,block);
	  symbol = Qloose_end;
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(symbol,
		  Class_description_gkbprop);
	  if (gensymed_symbol) {
	      sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		  temp_1 = (SI_Long)0L < gensymed_symbol_2;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  result = reflect_and_rotate_point_in_workspace(FIX((SI_Long)1L),
		  FIX((SI_Long)1L),reflection_and_rotation,
		  FIX((SI_Long)0L),FIX((SI_Long)0L));
	  MVS_2(result,delta_x_multiplier,delta_y_multiplier);
	  side = ISVREF(array_constant,IFIX(ISVREF(connection,
		  (SI_Long)5L)) & (SI_Long)3L);
	  temp = EQ(side,Qleft) ? T : Nil;
	  if (temp);
	  else
	      temp = EQ(side,Qright) ? T : Nil;
	  rotated_initial_orientation_horizontal_p = temp;
	  if (NUMBERP(delta_or_deltas_qm)) {
	      temp_1 = TRUEP(Noting_changes_to_kb_p);
	      if (temp_1);
	      else {
		  gensymed_symbol_2 = IFIX(ISVREF(connection,(SI_Long)7L)) 
			  & (SI_Long)128L;
		  temp_1 =  !((SI_Long)0L != gensymed_symbol_2) ?  
			  !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			  : TRUEP(Nil);
	      }
	      if (temp_1)
		  note_change_to_connection_1(connection);
	      svref_new_value = 
		      adjust_delta_according_to_new_orientation(delta_or_deltas_qm,
		      rotated_initial_orientation_horizontal_p,
		      delta_x_multiplier,delta_y_multiplier);
	      SVREF(connection,FIX((SI_Long)6L)) = svref_new_value;
	  }
	  else {
	      delta = Nil;
	      ab_loop_list_ = delta_or_deltas_qm;
	      orientation_horizontal_p = 
		      rotated_initial_orientation_horizontal_p;
	      PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
		      0);
		new_deltas = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		delta = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    Orientation_horizontal_p =  
			    !TRUEP(Orientation_horizontal_p) ? T : Nil;
		ab_loopvar__1 = 
			slot_value_cons_1(adjust_delta_according_to_new_orientation(delta,
			Orientation_horizontal_p,delta_x_multiplier,
			delta_y_multiplier),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    new_deltas = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_3;
	      end_loop_3:
		reclaim_slot_value_list_1(delta_or_deltas_qm);
		temp_1 = TRUEP(Noting_changes_to_kb_p);
		if (temp_1);
		else {
		    gensymed_symbol_2 = IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)128L;
		    temp_1 =  !((SI_Long)0L != gensymed_symbol_2) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp_1)
		    note_change_to_connection_1(connection);
		SVREF(connection,FIX((SI_Long)6L)) = new_deltas;
	      POP_SPECIAL();
	  }
      }
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* ADJUST-DELTA-ACCORDING-TO-NEW-ORIENTATION */
Object adjust_delta_according_to_new_orientation(delta,
	    orientation_horizontal_p,x_multiplier,y_multiplier)
    Object delta, orientation_horizontal_p, x_multiplier, y_multiplier;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,127);
    PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	    0);
      gensymed_symbol = IFIX(delta);
      gensymed_symbol_1 = Orientation_horizontal_p ? IFIX(x_multiplier) : 
	      IFIX(y_multiplier);
      result = VALUES_1(FIX(gensymed_symbol * gensymed_symbol_1));
    POP_SPECIAL();
    return result;
}

/* REFLECT-AND-ROTATE-END-POSITION */
Object reflect_and_rotate_end_position(end_position,
	    reflection_and_rotation,block)
    Object end_position, reflection_and_rotation, block;
{
    Object gensymed_symbol, side, new_side, temp, temp_1, x, y;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, block_width, block_height;
    SI_Long position_on_side, gensymed_symbol_3;
    Object result;

    x_note_fn_call(98,128);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    block_width = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    block_height = gensymed_symbol_1 - gensymed_symbol_2;
    side = ISVREF(array_constant,IFIX(end_position) & (SI_Long)3L);
    new_side = reflect_and_rotate_side(side,reflection_and_rotation);
    position_on_side = IFIX(end_position) >>  -  - (SI_Long)2L;
    if (EQ(side,Qleft))
	temp = FIX((SI_Long)0L);
    else if (EQ(side,Qright))
	temp = FIX(block_width);
    else
	temp = FIX(position_on_side);
    if (EQ(side,Qtop))
	temp_1 = FIX((SI_Long)0L);
    else if (EQ(side,Qbottom))
	temp_1 = FIX(block_height);
    else
	temp_1 = FIX(position_on_side);
    result = rotate_point_in_line_drawing_description(reflection_and_rotation,
	    FIX(block_width),FIX(block_height),temp,temp_1);
    MVS_2(result,x,y);
    if (EQ(new_side,Qtop))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(new_side,Qleft))
	gensymed_symbol_1 = (SI_Long)1L;
    else if (EQ(new_side,Qbottom))
	gensymed_symbol_1 = (SI_Long)2L;
    else
	gensymed_symbol_1 = (SI_Long)3L;
    gensymed_symbol_2 = memq_function(new_side,list_constant) ? IFIX(y) : 
	    IFIX(x);
    gensymed_symbol_3 = (SI_Long)2L;
    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
    return VALUES_1(FIX(gensymed_symbol_1 + gensymed_symbol_2));
}

/* REFLECT-AND-ROTATE-SIDE */
Object reflect_and_rotate_side(side,reflection_and_rotation)
    Object side, reflection_and_rotation;
{
    x_note_fn_call(98,129);
    if (EQ(reflection_and_rotation,Qnormal))
	return VALUES_1(side);
    else if (EQ(side,Qleft)) {
	if (EQ(reflection_and_rotation,Qclockwise_90) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_270))
	    return VALUES_1(Qtop);
	else if (EQ(reflection_and_rotation,Qclockwise_180) || 
		EQ(reflection_and_rotation,Qreflected))
	    return VALUES_1(Qright);
	else if (EQ(reflection_and_rotation,Qclockwise_270) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_90))
	    return VALUES_1(Qbottom);
	else if (EQ(reflection_and_rotation,Qreflected_clockwise_180))
	    return VALUES_1(Qleft);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(side,Qright)) {
	if (EQ(reflection_and_rotation,Qclockwise_90) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_270))
	    return VALUES_1(Qbottom);
	else if (EQ(reflection_and_rotation,Qclockwise_180) || 
		EQ(reflection_and_rotation,Qreflected))
	    return VALUES_1(Qleft);
	else if (EQ(reflection_and_rotation,Qclockwise_270) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_90))
	    return VALUES_1(Qtop);
	else if (EQ(reflection_and_rotation,Qreflected_clockwise_180))
	    return VALUES_1(Qright);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(side,Qtop)) {
	if (EQ(reflection_and_rotation,Qclockwise_90) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_90))
	    return VALUES_1(Qright);
	else if (EQ(reflection_and_rotation,Qreflected))
	    return VALUES_1(Qtop);
	else if (EQ(reflection_and_rotation,Qclockwise_270) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_270))
	    return VALUES_1(Qleft);
	else if (EQ(reflection_and_rotation,Qclockwise_180) || 
		EQ(reflection_and_rotation,Qreflected_clockwise_180))
	    return VALUES_1(Qbottom);
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(reflection_and_rotation,Qclockwise_90) || 
	    EQ(reflection_and_rotation,Qreflected_clockwise_90))
	return VALUES_1(Qleft);
    else if (EQ(reflection_and_rotation,Qreflected))
	return VALUES_1(Qbottom);
    else if (EQ(reflection_and_rotation,Qclockwise_270) || 
	    EQ(reflection_and_rotation,Qreflected_clockwise_270))
	return VALUES_1(Qright);
    else if (EQ(reflection_and_rotation,Qclockwise_180) || 
	    EQ(reflection_and_rotation,Qreflected_clockwise_180))
	return VALUES_1(Qtop);
    else
	return VALUES_1(Qnil);
}

/* TOGGLE-SIDE-FOR-LOOSE-END */
Object toggle_side_for_loose_end(loose_end,connection)
    Object loose_end, connection;
{
    Object output_end_object, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, end_position;
    char temp_1;

    x_note_fn_call(98,130);
    output_end_object = ISVREF(connection,(SI_Long)2L);
    gensymed_symbol = EQ(output_end_object,loose_end) ? 
	    IFIX(ISVREF(connection,(SI_Long)4L)) : IFIX(ISVREF(connection,
	    (SI_Long)5L));
    gensymed_symbol_1 = (SI_Long)3L;
    temp = SVREF(array_constant,FIX(gensymed_symbol & gensymed_symbol_1));
    temp = EQ(temp,Qleft) || EQ(temp,Qright) ? Qtop : Qleft;
    if (EQ(temp,Qtop))
	gensymed_symbol = (SI_Long)0L;
    else if (EQ(temp,Qleft))
	gensymed_symbol = (SI_Long)1L;
    else if (EQ(temp,Qbottom))
	gensymed_symbol = (SI_Long)2L;
    else
	gensymed_symbol = (SI_Long)3L;
    gensymed_symbol_1 = (SI_Long)0L;
    end_position = gensymed_symbol + gensymed_symbol_1;
    if (EQ(output_end_object,loose_end)) {
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	return VALUES_1(ISVREF(connection,(SI_Long)4L) = FIX(end_position));
    }
    else {
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	return VALUES_1(ISVREF(connection,(SI_Long)5L) = FIX(end_position));
    }
}

void connect2_INIT()
{
    Object temp, temp_1;
    Object reclaim_structure_for_connection_subrectangle_structure_1;
    Object AB_package, list_constant_3, list_constant_2, Qconnect3;
    Object Qreclaim_connection_subrectangle_structures;
    Object Qconnection_subrectangle_structures_for_drawing;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qdo_not_carry_global_property_value_into_kbs_qm, Qconnect2;
    Object Qconnection_subrectangle_structure, Qreclaim_structure;
    Object Qoutstanding_connection_subrectangle_structure_count;
    Object Qconnection_subrectangle_structure_structure_memory_usage;
    Object Qutilities2, string_constant_3, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_2, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qclasses_which_define;
    Object Qcleanup, Qcleanup_for_connection;

    x_note_fn_call(98,131);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qstub_length_to_use_qm = STATIC_SYMBOL("STUB-LENGTH-TO-USE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstub_length_to_use_qm,Stub_length_to_use_qm);
    Qconnect2 = STATIC_SYMBOL("CONNECT2",AB_package);
    record_system_variable(Qstub_length_to_use_qm,Qconnect2,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qdefault_stub_length = STATIC_SYMBOL("DEFAULT-STUB-LENGTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_stub_length,Default_stub_length);
    record_system_variable(Qdefault_stub_length,Qconnect2,
	    FIX((SI_Long)20L),Qnil,Qnil,Qnil,Qnil);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qstub_connection = STATIC_SYMBOL("STUB-CONNECTION",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = 
	    STATIC_STRING("Attempting to make a connection of class ~A. ~%");
    string_constant_1 = 
	    STATIC_STRING("This class is not defined as a connection class.");
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    Qlayer_position_of_block = STATIC_SYMBOL("LAYER-POSITION-OF-BLOCK",
	    AB_package);
    Qcleanup_for_connection = STATIC_SYMBOL("CLEANUP-FOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_connection,
	    STATIC_FUNCTION(cleanup_for_connection,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp = SYMBOL_FUNCTION(Qcleanup_for_connection);
    set_get(Qconnection,Qcleanup,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp = CONS(Qconnection,temp_1);
    mutate_global_property(Qcleanup,temp,Qclasses_which_define);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qconnections = STATIC_SYMBOL("CONNECTIONS",AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Kpaint_infered_from_xor = STATIC_SYMBOL("PAINT-INFERED-FROM-XOR",Pkeyword);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qconnection_color_pattern = STATIC_SYMBOL("CONNECTION-COLOR-PATTERN",
	    AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qdraw_connection = STATIC_SYMBOL("DRAW-CONNECTION",AB_package);
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Kconnection_bleeding = STATIC_SYMBOL("CONNECTION-BLEEDING",Pkeyword);
    Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct 
	    = STATIC_SYMBOL("CONNECTION-SUBRECTANGLE-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qconnection_subrectangle_structure = 
	    STATIC_SYMBOL("CONNECTION-SUBRECTANGLE-STRUCTURE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct,
	    Qconnection_subrectangle_structure,
	    Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qconnection_subrectangle_structure,
	    Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_connection_subrectangle_structure == UNBOUND)
	The_type_description_of_connection_subrectangle_structure = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83gEy1n83gEy8n8k1l8n0000001l1n8y83-3Ly1l83-E+yktk0k0");
    temp_1 = The_type_description_of_connection_subrectangle_structure;
    The_type_description_of_connection_subrectangle_structure = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_2));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_subrectangle_structure_g2_struct,
	    The_type_description_of_connection_subrectangle_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qconnection_subrectangle_structure,
	    The_type_description_of_connection_subrectangle_structure,
	    Qtype_description_of_type);
    Qoutstanding_connection_subrectangle_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-CONNECTION-SUBRECTANGLE-STRUCTURE-COUNT",
	    AB_package);
    Qconnection_subrectangle_structure_structure_memory_usage = 
	    STATIC_SYMBOL("CONNECTION-SUBRECTANGLE-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_3 = STATIC_STRING("1q83gEy8s83-O7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_connection_subrectangle_structure_count);
    push_optimized_constant(Qconnection_subrectangle_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_connection_subrectangle_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CONNECTION-SUBRECTANGLE-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_connection_subrectangle_structures,
	    Chain_of_available_connection_subrectangle_structures);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_connection_subrectangle_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qconnection_subrectangle_structure_count = 
	    STATIC_SYMBOL("CONNECTION-SUBRECTANGLE-STRUCTURE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_subrectangle_structure_count,
	    Connection_subrectangle_structure_count);
    record_system_variable(Qconnection_subrectangle_structure_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_connection_subrectangle_structures_vector == 
	    UNBOUND)
	Chain_of_available_connection_subrectangle_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qconnection_subrectangle_structure_structure_memory_usage,
	    STATIC_FUNCTION(connection_subrectangle_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_connection_subrectangle_structure_count,
	    STATIC_FUNCTION(outstanding_connection_subrectangle_structure_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_connection_subrectangle_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_connection_subrectangle_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qconnection_subrectangle_structure,
	    reclaim_structure_for_connection_subrectangle_structure_1);
    Qminimum_distance_between_fins = 
	    STATIC_SYMBOL("MINIMUM-DISTANCE-BETWEEN-FINS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_distance_between_fins,
	    Minimum_distance_between_fins);
    record_system_variable(Qminimum_distance_between_fins,Qconnect2,
	    FIX((SI_Long)50L),Qnil,Qnil,Qnil,Qnil);
    Qdesired_distance_between_fins = 
	    STATIC_SYMBOL("DESIRED-DISTANCE-BETWEEN-FINS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_distance_between_fins,
	    Desired_distance_between_fins);
    record_system_variable(Qdesired_distance_between_fins,Qconnect2,
	    FIX((SI_Long)100L),Qnil,Qnil,Qnil,Qnil);
    Qdesired_distance_between_fins_on_link = 
	    STATIC_SYMBOL("DESIRED-DISTANCE-BETWEEN-FINS-ON-LINK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_distance_between_fins_on_link,
	    Desired_distance_between_fins_on_link);
    record_system_variable(Qdesired_distance_between_fins_on_link,
	    Qconnect2,FIX((SI_Long)300L),Qnil,Qnil,Qnil,Qnil);
    Qdefault_fin_length = STATIC_SYMBOL("DEFAULT-FIN-LENGTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_fin_length,Default_fin_length);
    record_system_variable(Qdefault_fin_length,Qconnect2,FIX((SI_Long)10L),
	    Qnil,Qnil,Qnil,Qnil);
    Qconnection_subrectangle_structures_for_drawing = 
	    STATIC_SYMBOL("CONNECTION-SUBRECTANGLE-STRUCTURES-FOR-DRAWING",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qconnection_subrectangle_structures_for_drawing,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qconnection_subrectangle_structures_for_drawing,
	    T,Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_connection_subrectangle_structures = 
	    STATIC_SYMBOL("RECLAIM-CONNECTION-SUBRECTANGLE-STRUCTURES",
	    AB_package);
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qconnection_subrectangle_structures_for_drawing,
	    Qreclaim_connection_subrectangle_structures,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Connection_subrectangle_structures_for_drawing_kbprop = 
	    Qconnection_subrectangle_structures_for_drawing;
    SET_SYMBOL_FUNCTION(Qreclaim_connection_subrectangle_structures,
	    STATIC_FUNCTION(reclaim_connection_subrectangle_structures,NIL,
	    FALSE,1,1));
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qlink_2_delta = STATIC_SYMBOL("LINK-2-DELTA",AB_package);
    Qlink_1_delta = STATIC_SYMBOL("LINK-1-DELTA",AB_package);
    Qlink_0_delta = STATIC_SYMBOL("LINK-0-DELTA",AB_package);
    Qglobal_draw_diagonally_qm = STATIC_SYMBOL("GLOBAL-DRAW-DIAGONALLY\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_draw_diagonally_qm,
	    Global_draw_diagonally_qm);
    Qconnect3 = STATIC_SYMBOL("CONNECT3",AB_package);
    record_system_variable(Qglobal_draw_diagonally_qm,Qconnect3,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qdraw_connection_frame_in_xor = 
	    STATIC_SYMBOL("DRAW-CONNECTION-FRAME-IN-XOR",AB_package);
    Qdraw_connection_structure_in_xor = 
	    STATIC_SYMBOL("DRAW-CONNECTION-STRUCTURE-IN-XOR",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_connection,STATIC_FUNCTION(draw_connection,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qdraw_connection_structure_in_xor,
	    STATIC_FUNCTION(draw_connection_structure_in_xor,NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qdraw_connection_frame_in_xor,
	    STATIC_FUNCTION(draw_connection_frame_in_xor,NIL,FALSE,3,3));
    Qpending = STATIC_SYMBOL("PENDING",AB_package);
    if (Buggy_polyline_p == UNBOUND)
	Buggy_polyline_p = Qpending;
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_1 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qrounded = STATIC_SYMBOL("ROUNDED",AB_package);
    Qmiter = STATIC_SYMBOL("MITER",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    float_constant_1 = STATIC_FLOAT(0.1);
    Qarrow = STATIC_SYMBOL("ARROW",AB_package);
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    Qdiamond = STATIC_SYMBOL("DIAMOND",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)4L,Qarrow,Qtriangle,Qdiamond,
	    Qcircle);
    Basic_arrow_shapes = list_constant_3;
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    Qsimple_arrow = STATIC_SYMBOL("SIMPLE-ARROW",AB_package);
    Qfilled = STATIC_SYMBOL("FILLED",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qwide = STATIC_SYMBOL("WIDE",AB_package);
    Qnarrow = STATIC_SYMBOL("NARROW",AB_package);
    Qthick = STATIC_SYMBOL("THICK",AB_package);
    Qthin = STATIC_SYMBOL("THIN",AB_package);
    Qvery = STATIC_SYMBOL("VERY",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qleft,Qright);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qtop,Qbottom);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    Qreflected = STATIC_SYMBOL("REFLECTED",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qreflected_clockwise_90 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-90",
	    AB_package);
    Qclockwise_90 = STATIC_SYMBOL("CLOCKWISE-90",AB_package);
    Qreflected_clockwise_180 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-180",
	    AB_package);
    Qclockwise_180 = STATIC_SYMBOL("CLOCKWISE-180",AB_package);
    Qreflected_clockwise_270 = STATIC_SYMBOL("REFLECTED-CLOCKWISE-270",
	    AB_package);
    Qclockwise_270 = STATIC_SYMBOL("CLOCKWISE-270",AB_package);
    Qicon_position = STATIC_SYMBOL("ICON-POSITION",AB_package);
    Qicon_orientation = STATIC_SYMBOL("ICON-ORIENTATION",AB_package);
}
