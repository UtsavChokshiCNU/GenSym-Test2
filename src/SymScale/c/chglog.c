/* chglog.c
 * Input file:  change-log.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chglog.h"


/* MAKE-CHANGE-LOGGING-KB-VERSION */
Object make_change_logging_kb_version(change_logging_kb_version_number,
	    change_logging_kb_version_timestamp,change_logging_kb_version_uuid)
    Object change_logging_kb_version_number;
    Object change_logging_kb_version_timestamp, change_logging_kb_version_uuid;
{
    x_note_fn_call(163,0);
    return slot_value_cons_1(change_logging_kb_version_number,
	    slot_value_cons_1(change_logging_kb_version_timestamp,
	    slot_value_cons_1(change_logging_kb_version_uuid,Nil)));
}

/* MAKE-VERSION-INFORMATION-ENTRY-FOR-CHANGE-LOGGING */
Object make_version_information_entry_for_change_logging(version_number)
    Object version_number;
{
    Object temp;

    x_note_fn_call(163,1);
    temp = get_current_frame_edit_timestamp();
    return make_change_logging_kb_version(version_number,temp,make_uuid());
}

/* MAKE-INITIAL-VERSION-INFORMATION-FOR-CHANGE-LOGGING */
Object make_initial_version_information_for_change_logging()
{
    x_note_fn_call(163,2);
    return slot_value_cons_1(make_version_information_entry_for_change_logging(FIX((SI_Long)1L)),
	    Nil);
}

static Object Qkb_version_information_for_change_logging;  /* kb-version-information-for-change-logging */

static Object Qenable_kb_change_logging_qm;  /* enable-kb-change-logging? */

/* PUT-ENABLE-KB-CHANGE-LOGGING? */
Object put_enable_kb_change_logging_qm(saving_parameters,value,initializing_qm)
    Object saving_parameters, value, initializing_qm;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,3);
    PUSH_SPECIAL_WITH_SYMBOL(Saving_parameters,Qsaving_parameters,saving_parameters,
	    0);
      if ( !(initializing_qm || Loading_kb_p)) {
	  if (value &&  
		  !TRUEP(get_lookup_slot_value_given_default(Saving_parameters,
		  Qkb_version_information_for_change_logging,Nil))) {
	      temp = Saving_parameters;
	      change_slot_value(4,temp,
		      Qkb_version_information_for_change_logging,
		      make_initial_version_information_for_change_logging(),
		      Nil);
	  }
	  propagate_enable_kb_change_logging_to_new_system_table(value,
		  Saving_parameters);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Saving_parameters,
		  Qenable_kb_change_logging_qm);
      result = set_lookup_slot_value_1(Saving_parameters,
	      Qenable_kb_change_logging_qm,value);
    POP_SPECIAL();
    return result;
}

static Object string_constant;     /* "none" */

static Object string_constant_1;   /* ";~%" */

static Object string_constant_2;   /* "Version ~d (" */

static Object string_constant_3;   /* ")" */

/* WRITE-KB-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-SLOT */
Object write_kb_version_information_for_change_logging_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object change_logging_kb_version, ab_loop_list_, first_time_qm;
    Object ab_loop_iter_flag_, temp;

    x_note_fn_call(163,4);
    if ( !TRUEP(value))
	return tformat(1,string_constant);
    else {
	change_logging_kb_version = Nil;
	ab_loop_list_ = value;
	first_time_qm = T;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	change_logging_kb_version = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    first_time_qm = Nil;
	if ( !TRUEP(first_time_qm))
	    tformat(1,string_constant_1);
	tformat(2,string_constant_2,CAR(change_logging_kb_version));
	temp = CDR(change_logging_kb_version);
	twrite_frame_edit_timestamp(CAR(temp));
	tformat(1,string_constant_3);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE-NOW */
Object flush_version_information_for_change_logging_from_table_now(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(163,5);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp ? TRUEP(get_lookup_slot_value_given_default(item,
	    Qkb_version_information_for_change_logging,Nil)) : TRUEP(Nil))
	return change_slot_value(3,item,
		Qkb_version_information_for_change_logging,
		get_lookup_slot_value_given_default(item,
		Qenable_kb_change_logging_qm,Nil) ? 
		make_initial_version_information_for_change_logging() : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

static Object string_constant_4;   /* "Flush all version information for this KB?  Once flushed, this information ~
				    *         cannot be recovered."
				    */

static Object Qflush_version_information_for_change_logging_from_table_now;  /* flush-version-information-for-change-logging-from-table-now */

/* COM-FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE */
Object com_flush_version_information_for_change_logging_from_table(slot_name,
	    item,original_x_in_window,original_y_in_window)
    Object slot_name, item, original_x_in_window, original_y_in_window;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(163,6);
    if (slot_name && of_class_p_function(item,Qitem) && 
	    original_x_in_window && original_y_in_window) {
	if (Package_preparation_mode && EQ(slot_name,
		Qkb_version_information_for_change_logging)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qkb_version_information_for_change_logging,Nil)) : 
		    TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = tformat_text_string(1,string_constant_4);
	return confirm_or_cancel(3,temp_1,
		Qflush_version_information_for_change_logging_from_table_now,
		slot_value_cons_1(item,Nil));
    }
    else
	return VALUES_1(Nil);
}

static Object Qslot_name;          /* slot-name */

static Object Qoriginal_x_in_window;  /* original-x-in-window */

static Object Qoriginal_y_in_window;  /* original-y-in-window */

/* FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE-COMMAND-PURSUER */
Object flush_version_information_for_change_logging_from_table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, slot_name, item, original_x_in_window;
    Object original_y_in_window;

    x_note_fn_call(163,7);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    slot_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    slot_name = command_argument_value(slot_name);
    item = command_argument_value(item);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(slot_name,Plus_missing_argument_plus))
	return VALUES_3(Qslot_name,Qslot_name,FIX((SI_Long)0L));
    else if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)1L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)2L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)3L));
    else
	return VALUES_1(Qnil);
}

static Object Qflush_version_information_for_change_logging_from_table;  /* flush-version-information-for-change-logging-from-table */

/* FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE-COMMAND-TRANSLATOR */
Object flush_version_information_for_change_logging_from_table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object slot_name, item, original_x_in_window, original_y_in_window;
    Object gensymed_symbol, sub_class_bit_vector, temp_1, temp_2, temp_3;
    Object temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(163,8);
    slot_name = slot_name_blackboard_function(mouse_pointer);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (slot_name && item && original_x_in_window && original_y_in_window) {
	if (Package_preparation_mode && EQ(slot_name,
		Qkb_version_information_for_change_logging)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qkb_version_information_for_change_logging,Nil)) : 
		    TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = slot_name;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = item;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_4 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qflush_version_information_for_change_logging_from_table,
		    slot_value_list_4(temp_2,temp_3,temp_4,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_5;   /* "~NA must be an instance of saving-parameters." */

/* G2-FLUSH-VERSION-INFORMATION */
Object g2_flush_version_information(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(163,9);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	return flush_version_information_for_change_logging_from_table_now(item);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_5,item);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object string_constant_6;   /* "~NA does not have any KB version information." */

static Object string_constant_7;   /* "~NA is an invalid entry-number for KB version information." */

static Object string_constant_8;   /* "~NA is a the current KB version; it cannot be deleted except by flushing the entire attribute." */

static Object string_constant_9;   /* "~NA does not exist in the KB version information of ~NA." */

static Object Qstack_change;       /* stack-change */

/* G2-DELETE-VERSION-INFORMATION-ENTRY */
Object g2_delete_version_information_entry(sav_params,entry_number)
    Object sav_params, entry_number;
{
    Object gensymed_symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object temp_1, rest_1, slot_description, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, stack_of_slot_value_changes;
    Object entry_to_delete, frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(163,10);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(sav_params,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_5,
		sav_params);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if ( !TRUEP(get_lookup_slot_value_given_default(sav_params,
	    Qkb_version_information_for_change_logging,Nil))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_6,
		sav_params);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (IFIX(entry_number) < (SI_Long)1L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_7,
		entry_number);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	temp_1 = get_lookup_slot_value_given_default(sav_params,
		Qkb_version_information_for_change_logging,Nil);
	if (FIXNUM_EQ(entry_number,CAAR(temp_1))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_8,entry_number);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    rest_1 = get_lookup_slot_value_given_default(sav_params,
		    Qkb_version_information_for_change_logging,Nil);
	  next_loop:
	    if ( !TRUEP(rest_1))
		goto end_loop;
	    if (FIXNUM_GT(entry_number,CAAR(rest_1))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_9,entry_number,sav_params);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    if (FIXNUM_EQ(entry_number,CAADR(rest_1))) {
		slot_description = 
			get_slot_description_of_class_description_function(Qkb_version_information_for_change_logging,
			lookup_global_or_kb_specific_property_value(Qsaving_parameters,
			Class_description_gkbprop),Nil);
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_stack_change_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_stack_change_cons_pool();
		if (Nil)
		    gensymed_symbol_4 = 
			    nconc2(stack_change_list_2(sav_params,
			    slot_description),stack_change_cons_1(Nil,Nil));
		else {
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_stack_change_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_stack_change_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_stack_change_cons_pool();
		    M_CAR(gensymed_symbol_4) = sav_params;
		    M_CDR(gensymed_symbol_4) = slot_description;
		    inline_note_allocate_cons(gensymed_symbol_4,Qstack_change);
		}
		M_CAR(gensymed_symbol) = gensymed_symbol_4;
		temp_2 = Stack_of_slot_value_changes;
		M_CDR(gensymed_symbol) = temp_2;
		inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		stack_of_slot_value_changes = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			0);
		  entry_to_delete = CADR(rest_1);
		  temp_2 = CDDR(rest_1);
		  M_CDR(rest_1) = temp_2;
		  temp_1 = CDDR(entry_to_delete);
		  reclaim_wide_string(CAR(temp_1));
		  temp_2 = CDDR(entry_to_delete);
		  M_CAR(temp_2) = Nil;
		  reclaim_slot_value_list_1(entry_to_delete);
		  temp = 
			  TRUEP(Suppress_updating_of_slot_value_representations_qm);
		  if (temp);
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
		      temp = EQ(slot_description,
			      M_CDR(frame_and_slot_or_atom));
		      if (temp);
		      else {
			  temp_1 = M_CDR(frame_and_slot_or_atom);
			  temp = CONSP(temp_1) ? EQ(slot_description,
				  SECOND(frame_and_slot_or_atom)) && 
				  EQ(Nil,THIRD(frame_and_slot_or_atom)) && 
				  EQ(Nil,CDDDR(frame_and_slot_or_atom)) : 
				  TRUEP(Nil);
		      }
		      ab_loop_it_ = temp ? (EQ(sav_params,
			      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		      if (ab_loop_it_) {
			  temp = TRUEP(ab_loop_it_);
			  goto end_1;
		      }
		      goto next_loop_1;
		    end_loop_1:
		      temp = TRUEP(Qnil);
		    end_1:;
		  }
		  else
		      temp = TRUEP(Nil);
		  if ( !temp)
		      update_all_representations_of_slot(sav_params,
			      slot_description,Nil,Nil);
		  if (ISVREF(slot_description,(SI_Long)14L))
		      update_frame_name_references(sav_params);
		  stack_change_pop_store = Nil;
		  cons_1 = Stack_of_slot_value_changes;
		  if (cons_1) {
		      stack_change_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qstack_change);
		      if (ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_2 = 
				  ISVREF(Available_stack_change_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp_2) = cons_1;
			  temp_2 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_2,svref_arg_2) = cons_1;
		      }
		      else {
			  temp_2 = Available_stack_change_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_2,svref_arg_2) = cons_1;
			  temp_2 = Available_stack_change_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp_2,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Stack_of_slot_value_changes = next_cons;
		  reclaim_stack_change_tree_1(stack_change_pop_store);
		  if (Stack_of_slot_value_changes) {
		      temp_1 = M_CAR(Stack_of_slot_value_changes);
		      temp = ATOM(temp_1);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp ?  
			  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			  : TRUEP(Nil))
		      do_deferred_updates_to_representations_in_tables();
		POP_SPECIAL();
		return VALUES_1(T);
	    }
	    rest_1 = M_CDR(rest_1);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
}

/* INCREMENT-VERSION-FOR-CHANGE-LOGGING-IF-APPROPRIATE */
Object increment_version_for_change_logging_if_appropriate(saving_parameters_instance)
    Object saving_parameters_instance;
{
    Object instance, temp;

    x_note_fn_call(163,11);
    instance = saving_parameters_instance;
    if (get_lookup_slot_value_given_default(instance,
	    Qkb_version_information_for_change_logging,Nil)) {
	temp = get_lookup_slot_value_given_default(instance,
		Qkb_version_information_for_change_logging,Nil);
	temp = FIRST(temp);
	temp = 
		make_version_information_entry_for_change_logging(FIXNUM_ADD1(CAR(temp)));
	return change_slot_value(3,saving_parameters_instance,
		Qkb_version_information_for_change_logging,
		slot_value_cons_1(temp,
		copy_for_slot_value(get_lookup_slot_value_given_default(instance,
		Qkb_version_information_for_change_logging,Nil))));
    }
    else
	return VALUES_1(Nil);
}

static Object Qtop_level_kb_module_qm;  /* top-level-kb-module? */

/* GET-SAVING-PARAMETERS-FOR-FRAME */
Object get_saving_parameters_for_frame(frame)
    Object frame;
{
    Object sub_class_bit_vector, module_qm, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,12);
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
    module_qm = temp ? get_module_block_is_in(frame) : Nil;
    if (module_qm);
    else
	module_qm = get_slot_value_function(Module_information,
		Qtop_level_kb_module_qm,Nil);
    temp_1 = module_qm ? 
	    get_system_table_of_class_for_module_or_nil(module_qm,
	    Qsaving_parameters) : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(Saving_parameters);
}

/* MODULE-UUID-FOR-FRAME-IF-LOGGING? */
Object module_uuid_for_frame_if_logging_qm(frame)
    Object frame;
{
    Object saving_parameters_instance, temp;

    x_note_fn_call(163,13);
    saving_parameters_instance = get_saving_parameters_for_frame(frame);
    if (get_slot_value_function(saving_parameters_instance,
	    Qenable_kb_change_logging_qm,Nil)) {
	temp = 
		get_lookup_slot_value_given_default(saving_parameters_instance,
		Qkb_version_information_for_change_logging,Nil);
	temp = FIRST(temp);
	temp = CDDR(temp);
	return VALUES_1(CAR(temp));
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Version_control_parameters, Qversion_control_parameters);

static Object Qenable_kb_change_logging;  /* enable-kb-change-logging */

/* PUT-ENABLE-KB-CHANGE-LOGGING */
Object put_enable_kb_change_logging(version_control_parameters,value,
	    initializing_qm)
    Object version_control_parameters, value, initializing_qm;
{
    Object saving_parameters_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,14);
    PUSH_SPECIAL_WITH_SYMBOL(Version_control_parameters,Qversion_control_parameters,version_control_parameters,
	    0);
      saving_parameters_qm = 
	      get_saving_parameters_for_frame(Version_control_parameters);
      if (saving_parameters_qm)
	  change_slot_value(3,Saving_parameters,
		  Qenable_kb_change_logging_qm,value);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Version_control_parameters,
		  Qenable_kb_change_logging);
      result = set_lookup_slot_value_1(Version_control_parameters,
	      Qenable_kb_change_logging,value);
    POP_SPECIAL();
    return result;
}

/* PROPAGATE-ENABLE-KB-CHANGE-LOGGING-TO-NEW-SYSTEM-TABLE */
Object propagate_enable_kb_change_logging_to_new_system_table(value,
	    sp_system_frame)
    Object value, sp_system_frame;
{
    Object vc_parameters_qm, buddy_slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, temp_1, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_3, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(163,15);
    vc_parameters_qm = 
	    get_system_table_of_class_for_module_or_nil(get_module_block_is_in(sp_system_frame),
	    Qversion_control_parameters);
    buddy_slot_description = 
	    get_slot_description_of_class_description_function(Qenable_kb_change_logging,
	    lookup_global_or_kb_specific_property_value(Qversion_control_parameters,
	    Class_description_gkbprop),Nil);
    if (vc_parameters_qm) {
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
	    gensymed_symbol_1 = 
		    nconc2(stack_change_list_2(vc_parameters_qm,
		    buddy_slot_description),stack_change_cons_1(Nil,Nil));
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
	    M_CAR(gensymed_symbol_1) = vc_parameters_qm;
	    M_CDR(gensymed_symbol_1) = buddy_slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(vc_parameters_qm,
		      Qenable_kb_change_logging);
	  temp_1 = set_lookup_slot_value_1(vc_parameters_qm,
		  Qenable_kb_change_logging,value);
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
	      temp_2 = EQ(buddy_slot_description,
		      M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp_3 = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp_3) ? EQ(buddy_slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(vc_parameters_qm,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
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
	      update_all_representations_of_slot(vc_parameters_qm,
		      buddy_slot_description,Nil,Nil);
	  if (ISVREF(buddy_slot_description,(SI_Long)14L))
	      update_frame_name_references(vc_parameters_qm);
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
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

Object Default_unix_diff_program = UNBOUND;

Object Default_unix_diff_options = UNBOUND;

Object Default_windows_diff_program = UNBOUND;

Object Default_windows_diff_options = UNBOUND;

static Object Qunix;               /* unix */

/* GET-DEFAULT-DIFF-PROGRAM? */
Object get_default_diff_program_qm()
{
    x_note_fn_call(163,16);
    return copy_text_string(EQ(Qunix,Local_file_system) ? 
	    Default_unix_diff_program : Default_windows_diff_program);
}

/* GET-DEFAULT-DIFF-OPTIONS? */
Object get_default_diff_options_qm()
{
    x_note_fn_call(163,17);
    return copy_text_string(EQ(Qunix,Local_file_system) ? 
	    Default_unix_diff_options : Default_windows_diff_options);
}

DEFINE_VARIABLE_WITH_SYMBOL(External_diff_program_qm, Qexternal_diff_program_qm);

DEFINE_VARIABLE_WITH_SYMBOL(External_diff_options_qm, Qexternal_diff_options_qm);

static Object Qab_pathname;        /* pathname */

static Object Qcommand_line_options;  /* command-line-options */

static Object string_constant_10;  /* "diff pathname must be text" */

static Object string_constant_11;  /* "diff options must be text" */

/* G2-SET-UP-EXTERNAL-DIFF */
Object g2_set_up_external_diff(value)
    Object value;
{
    Object diff_program_qm, diff_options_qm, top_of_stack, message_1;
    Object requested_diff_program;

    x_note_fn_call(163,18);
    diff_program_qm = estructure_slot(value,Qab_pathname,Nil);
    diff_options_qm = estructure_slot(value,Qcommand_line_options,Nil);
    if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(diff_program_qm) != (SI_Long)0L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (diff_options_qm &&  
	    !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(diff_options_qm) != 
	    (SI_Long)0L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_11);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	if (External_diff_program_qm) {
	    reclaim_text_string(External_diff_program_qm);
	    External_diff_program_qm = Nil;
	}
	if (External_diff_options_qm) {
	    reclaim_text_string(External_diff_options_qm);
	    External_diff_options_qm = Nil;
	}
	requested_diff_program = diff_program_qm;
	External_diff_program_qm = copy_text_string(requested_diff_program);
	if (diff_options_qm)
	    External_diff_options_qm = copy_text_string(diff_options_qm);
	return VALUES_1(Evaluation_true_value);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Delete_files_after_external_diff_p, Qdelete_files_after_external_diff_p);

static Object Qtruth_value;        /* truth-value */

/* G2-DELETE-FILES-AFTER-EXTERNAL-DIFF */
Object g2_delete_files_after_external_diff(value)
    Object value;
{
    x_note_fn_call(163,19);
    Delete_files_after_external_diff_p = CONSP(value) && EQ(M_CDR(value),
	    Qtruth_value) ? evaluation_truth_value_is_true_p(value) : Qnil;
    return VALUES_1(Delete_files_after_external_diff_p);
}

static Object string_constant_12;  /* "~A ~A ~A ~A > ~A 2> ~A" */

static Object array_constant;      /* # */

static Object Qtemp_file_1;        /* temp-file-1 */

static Object Qtemp_file_2;        /* temp-file-2 */

static Object Qoutput_filename;    /* output-filename */

static Object Qcommand_line;       /* command-line */

static Object Qerror_filename;     /* error-filename */

/* SET-VERSION-CONTROL-DIFF-COMMAND-LINE-IF-POSSIBLE */
Object set_version_control_diff_command_line_if_possible()
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6;

    x_note_fn_call(163,20);
    temp = Version_control_parameters;
    temp_1 = EQ(Local_file_system,Qunix) ? string_constant_12 : 
	    string_constant_12;
    temp_2 = External_diff_program_qm;
    temp_3 = External_diff_options_qm;
    if (temp_3);
    else
	temp_3 = array_constant;
    temp_4 = 
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_1,Nil);
    temp_5 = 
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_2,Nil);
    temp_6 = 
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qoutput_filename,Nil);
    return set_non_savable_lookup_slot_value(temp,Qcommand_line,
	    tformat_text_string(7,temp_1,temp_2,temp_3,temp_4,temp_5,
	    temp_6,
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qerror_filename,Nil)));
}

static Object string_constant_13;  /* "fo" */

static Object string_constant_14;  /* "ft" */

static Object string_constant_15;  /* "output" */

static Object string_constant_16;  /* "error" */

/* SET-VERSION-CONTROL-DIFF-FILENAMES */
Object set_version_control_diff_filenames(need_temp_files_p)
    Object need_temp_files_p;
{
    Object temp;

    x_note_fn_call(163,21);
    if (need_temp_files_p) {
	temp = Version_control_parameters;
	set_non_savable_lookup_slot_value(temp,Qtemp_file_1,
		make_unique_file_name(string_constant_13));
	temp = Version_control_parameters;
	set_non_savable_lookup_slot_value(temp,Qtemp_file_2,
		make_unique_file_name(string_constant_14));
    }
    temp = Version_control_parameters;
    set_non_savable_lookup_slot_value(temp,Qoutput_filename,
	    make_unique_file_name(string_constant_15));
    temp = Version_control_parameters;
    set_non_savable_lookup_slot_value(temp,Qerror_filename,
	    make_unique_file_name(string_constant_16));
    if (get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_1,Nil) && 
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_2,Nil) && 
	    get_lookup_slot_value_given_default(Version_control_parameters,
	    Qoutput_filename,Nil))
	return get_lookup_slot_value_given_default(Version_control_parameters,
		Qerror_filename,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qno_diff_found;      /* no-diff-found */

static Object Qcan_not_execute;    /* can-not-execute */

static Object Qcan_not_make_generate_temp_filenames;  /* can-not-make-generate-temp-filenames */

static Object Qcan_not_generate_command_line;  /* can-not-generate-command-line */

/* VERIFY-EXTERNAL-DIFFING */
Object verify_external_diffing(need_temp_files_p)
    Object need_temp_files_p;
{
    x_note_fn_call(163,22);
    if ( !TRUEP(External_diff_program_qm))
	return VALUES_1(Qno_diff_found);
    else if ( !TRUEP(verify_executable(External_diff_program_qm)))
	return VALUES_1(Qcan_not_execute);
    else if ( !TRUEP(set_version_control_diff_filenames(need_temp_files_p)))
	return VALUES_1(Qcan_not_make_generate_temp_filenames);
    else if ( !TRUEP(set_version_control_diff_command_line_if_possible()))
	return VALUES_1(Qcan_not_generate_command_line);
    else
	return VALUES_1(Nil);
}

static Object Qdiff_output;        /* diff-output */

static Object Qdiff_error;         /* diff-error */

/* EXTERNAL-DIFF-FILES */
Object external_diff_files()
{
    Object pid, result_qm, temp_1;
    double temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(163,23);
    pid = FIX((SI_Long)-1L);
    result_qm = Nil;
    g2ext_set_inherit_stdio_handles((SI_Long)0L);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	pid = 
		c_spawn_command_line_process(get_lookup_slot_value_given_default(Version_control_parameters,
		Qcommand_line,Nil));
    POP_LOCAL_ALLOCATION(0,0);
    g2ext_set_inherit_stdio_handles((SI_Long)1L);
    reclaim_text_string(get_lookup_slot_value_given_default(Version_control_parameters,
	    Qcommand_line,Nil));
    set_non_savable_lookup_slot_value(Version_control_parameters,
	    Qcommand_line,Nil);
  next_loop:
    temp = DOUBLE_FLOAT_TO_DOUBLE(pid);
    if ( !((SI_Long)0L != g2ext_process_exists(temp)))
	goto end_loop;
    lsleep(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    temp_1 = 
	    read_text_file_into_wide_string(get_lookup_slot_value_given_default(Version_control_parameters,
	    Qoutput_filename,Nil));
    result_qm = allocate_evaluation_structure(eval_list_4(Qdiff_output,
	    temp_1,Qdiff_error,
	    read_text_file_into_wide_string(get_lookup_slot_value_given_default(Version_control_parameters,
	    Qerror_filename,Nil))));
    if (Delete_files_after_external_diff_p) {
	g2_stream_delete_file(get_lookup_slot_value_given_default(Version_control_parameters,
		Qoutput_filename,Nil));
	g2_stream_delete_file(get_lookup_slot_value_given_default(Version_control_parameters,
		Qerror_filename,Nil));
    }
    return VALUES_1(result_qm);
}

/* EXTERNAL-DIFF-TEXT-STRINGS */
Object external_diff_text_strings(t1,t2)
    Object t1, t2;
{
    Object f1, f2, success_p, result_qm;

    x_note_fn_call(163,24);
    f1 = get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_1,Nil);
    f2 = get_lookup_slot_value_given_default(Version_control_parameters,
	    Qtemp_file_2,Nil);
    success_p = write_wide_string_into_text_file(t1,f1);
    result_qm = Nil;
    if (success_p) {
	success_p = write_wide_string_into_text_file(t2,f2);
	if (success_p) {
	    result_qm = external_diff_files();
	    if (Delete_files_after_external_diff_p) {
		g2_stream_delete_file(f1);
		g2_stream_delete_file(f2);
	    }
	}
	else
	    g2_stream_delete_file(f1);
    }
    return VALUES_1(result_qm);
}

static Object string_constant_17;  /* "Unable to execute external diff: ~s" */

/* G2-DIFF-TEXTS */
Object g2_diff_texts(text1,text2)
    Object text1, text2;
{
    Object error_symbol_qm, top_of_stack, message_1;

    x_note_fn_call(163,25);
    error_symbol_qm = verify_external_diffing(T);
    if (error_symbol_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_17,
		error_symbol_qm);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return external_diff_text_strings(text1,text2);
}

/* G2-TEXT-FILE-CONTENTS */
Object g2_text_file_contents(eval_filename)
    Object eval_filename;
{
    Object filename, the_text, result_1;

    x_note_fn_call(163,26);
    filename = eval_filename;
    the_text = read_text_file_into_wide_string(filename);
    result_1 = copy_as_wide_string(the_text);
    reclaim_text_string(the_text);
    return VALUES_1(result_1);
}

/* MAKE-CHANGE-LOG-ENTRY-FOR-SLOT */
Object make_change_log_entry_for_slot(change_log_entry_slot_name,
	    change_log_entry_class_qualifier_qm,change_log_entry_edit_type,
	    change_log_entry_timestamp,change_log_entry_author,
	    change_log_entry_revision,change_log_entry_tags_qm,
	    change_log_entry_type_of_text_stored,
	    change_log_entry_slot_value_text,change_log_entry_log_qm,
	    change_log_entry_uuid_of_save)
    Object change_log_entry_slot_name, change_log_entry_class_qualifier_qm;
    Object change_log_entry_edit_type, change_log_entry_timestamp;
    Object change_log_entry_author, change_log_entry_revision;
    Object change_log_entry_tags_qm, change_log_entry_type_of_text_stored;
    Object change_log_entry_slot_value_text, change_log_entry_log_qm;
    Object change_log_entry_uuid_of_save;
{
    x_note_fn_call(163,27);
    return slot_value_cons_1(change_log_entry_slot_name,
	    slot_value_cons_1(change_log_entry_class_qualifier_qm,
	    slot_value_cons_1(change_log_entry_edit_type,
	    slot_value_cons_1(change_log_entry_timestamp,
	    slot_value_cons_1(change_log_entry_author,
	    slot_value_cons_1(change_log_entry_revision,
	    slot_value_cons_1(change_log_entry_tags_qm,
	    slot_value_cons_1(change_log_entry_type_of_text_stored,
	    slot_value_cons_1(change_log_entry_slot_value_text,
	    slot_value_cons_1(change_log_entry_log_qm,
	    slot_value_cons_1(change_log_entry_uuid_of_save,Nil)))))))))));
}

/* CHANGE-LOG-INFORMATION-ENTRY */
Object change_log_information_entry(slot_name,class_qualifier_qm,
	    revision_number)
    Object slot_name, class_qualifier_qm, revision_number;
{
    x_note_fn_call(163,28);
    return slot_value_list_2(class_qualifier_qm ? 
	    slot_value_cons_1(slot_name,class_qualifier_qm) : slot_name,
	    revision_number);
}

static Object Qframe_change_log;   /* frame-change-log */

static Object Qchange_log_information;  /* change-log-information */

/* BUILD-CHANGE-LOG-INFORMATION */
Object build_change_log_information(frame)
    Object frame;
{
    Object revision_list, entry, ab_loop_list_, slot_name, class_qualifier_qm;
    Object temp, slot_denot, ab_loop_list__1, ab_loop_it_, ab_loop_desetq_;
    char temp_1;

    x_note_fn_call(163,29);
    revision_list = Qnil;
    entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(frame,
	    Qframe_change_log,Nil);
    slot_name = Nil;
    class_qualifier_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = CAR(entry);
    temp = CDR(entry);
    class_qualifier_qm = CAR(temp);
    slot_denot = Nil;
    ab_loop_list__1 = revision_list;
    ab_loop_it_ = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    slot_denot = CAR(ab_loop_desetq_);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp =  !TRUEP(class_qualifier_qm) ? (EQ(slot_denot,slot_name) ? T : 
	    Nil) : Qnil;
    if (temp);
    else
	temp = LISTP(slot_denot) && EQ(CAR(slot_denot),slot_name) ? 
		(EQ(CDR(slot_denot),class_qualifier_qm) ? T : Nil) : Qnil;
    ab_loop_it_ = temp;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if ( !temp_1) {
	temp = CDDDDR(entry);
	temp = CDR(temp);
	temp = change_log_information_entry(slot_name,class_qualifier_qm,
		CAR(temp));
	revision_list = slot_value_cons_1(temp,revision_list);
    }
    goto next_loop;
  end_loop:
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qchange_log_information);
    set_lookup_slot_value_1(frame,Qchange_log_information,
	    slot_value_cons_1(T,revision_list));
    return VALUES_1(Qnil);
}

/* ENSURE-FRAME-CHANGE-LOG-INFORMATION */
Object ensure_frame_change_log_information(frame)
    Object frame;
{
    x_note_fn_call(163,30);
    if ( !TRUEP(get_lookup_slot_value_given_default(frame,
	    Qchange_log_information,Nil)))
	return build_change_log_information(frame);
    else
	return VALUES_1(Nil);
}

/* ADD-CHANGE-LOG-INFORMATION-TO-83B0-KBS */
Object add_change_log_information_to_83b0_kbs()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame;
    char temp;
    Declare_special(1);

    x_note_fn_call(163,31);
    if (IFIX(Kb_flags_from_last_kb_read) == (SI_Long)281L) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	frame = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qblock);
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
	  frame = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (get_lookup_slot_value_given_default(frame,Qframe_change_log,Nil))
	      ensure_frame_change_log_information(frame);
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qpermanent;          /* permanent */

static Object Qfull_text;          /* full-text */

static Object Qpost_load;          /* post-load */

/* CONVERT-FRAME-CHANGE-LOG-TO-NEW-FORM */
Object convert_frame_change_log_to_new_form(frame_change_entries,frame)
    Object frame_change_entries, frame;
{
    Object revision_list, new_frame_change_log, current_module_uuid_qm;
    Object uuid_and_entry_list, ab_loop_list_, module_uuid, entries, entry;
    Object ab_loop_list__1, slot_name, slot_value_text, timestamp, author;
    Object tag_qm, slot_status_qm, revision, replacement_entry, cadr_new_value;
    Object slot_revision, ab_loop_desetq_, temp, temp_1, temp_2, temp_3;
    Object temp_4;

    x_note_fn_call(163,32);
    revision_list = Qnil;
    new_frame_change_log = Qnil;
    current_module_uuid_qm = module_uuid_for_frame_if_logging_qm(frame);
    uuid_and_entry_list = Nil;
    ab_loop_list_ = frame_change_entries;
    module_uuid = Nil;
    entries = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    uuid_and_entry_list = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_uuid = CAR(uuid_and_entry_list);
    entries = CDR(uuid_and_entry_list);
    entry = Nil;
    ab_loop_list__1 = entries;
    slot_name = Nil;
    slot_value_text = Nil;
    timestamp = Nil;
    author = Nil;
    tag_qm = Nil;
    slot_status_qm = Nil;
    revision = Nil;
    replacement_entry = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    entry = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    slot_name = FIRST(entry);
    slot_value_text = SECOND(entry);
    timestamp = THIRD(entry);
    author = FOURTH(entry);
    tag_qm = FIFTH(entry);
    slot_status_qm = assq_function(slot_name,revision_list);
    if ( !TRUEP(slot_status_qm)) {
	slot_status_qm = slot_value_list_2(slot_name,
		Initial_change_log_revision_number);
	revision_list = slot_value_cons_1(slot_status_qm,revision_list);
    }
    revision = CADR(slot_status_qm);
    replacement_entry = make_change_log_entry_for_slot(slot_name,Nil,
	    Qpermanent,timestamp,author,revision,tag_qm ? 
	    slot_value_cons_1(tag_qm,Nil) : Nil,Qfull_text,slot_value_text,
	    Nil,copy_for_slot_value(module_uuid));
    new_frame_change_log = slot_value_cons_1(replacement_entry,
	    new_frame_change_log);
    cadr_new_value = FIXNUM_ADD1(CADR(slot_status_qm));
    M_CADR(slot_status_qm) = cadr_new_value;
    reclaim_slot_value_list_1(entry);
    goto next_loop_1;
  end_loop_1:;
    reclaim_slot_value_list_1(entries);
    reclaim_wide_string(module_uuid);
    goto next_loop;
  end_loop:
    if (current_module_uuid_qm) {
	slot_name = Nil;
	slot_revision = Nil;
	ab_loop_list_ = revision_list;
	ab_loop_desetq_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	slot_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	slot_revision = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (get_slot_description_of_class_description_function(slot_name,
		ISVREF(frame,(SI_Long)1L),Nil)) {
	    temp_1 = slot_name;
	    temp_2 = get_current_frame_edit_timestamp();
	    temp_3 = slot_value_cons_1(Qpost_load,Nil);
	    temp_4 = slot_revision;
	    temp = make_text_representation_for_slot_value(2,frame,slot_name);
	    temp = make_change_log_entry_for_slot(temp_1,Nil,Qpermanent,
		    temp_2,temp_3,temp_4,Qnil,Qfull_text,temp,Nil,
		    copy_for_slot_value(current_module_uuid_qm));
	    new_frame_change_log = slot_value_cons_1(temp,
		    new_frame_change_log);
	}
	goto next_loop_2;
      end_loop_2:;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qchange_log_information);
    set_lookup_slot_value_1(frame,Qchange_log_information,
	    slot_value_cons_1(T,revision_list));
    set_non_savable_lookup_slot_value(frame,Qframe_change_log,
	    new_frame_change_log);
    return VALUES_1(Qnil);
}

/* CONVERT-OLD-CHANGE-LOGS-TO-NEW-FORM */
Object convert_old_change_logs_to_new_form()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame, the_change_log_qm;
    Object temp_1, system_table_a_list, ab_loop_list_, vc_params, sv_params;
    Object system_frame, ab_loop_list__1, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);

    x_note_fn_call(163,33);
    if ( !(IFIX(Kb_flags_from_last_kb_read) >= (SI_Long)281L)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	frame = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  the_change_log_qm = Nil;
	  ab_loopvar_ = collect_subclasses(Qblock);
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
	  frame = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  the_change_log_qm = get_lookup_slot_value_given_default(frame,
		  Qframe_change_log,Nil);
	  if (text_string_p(CAAR(the_change_log_qm))) {
	      set_non_savable_lookup_slot_value(frame,Qframe_change_log,Nil);
	      temp_1 = nreverse(the_change_log_qm);
	      convert_frame_change_log_to_new_form(temp_1,frame);
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	system_table_a_list = Nil;
	ab_loop_list_ = Modules_and_system_tables_a_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	system_table_a_list = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	vc_params = Nil;
	sv_params = Nil;
	system_frame = Nil;
	ab_loop_list__1 = system_table_a_list;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	system_frame = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qversion_control_parameters,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(system_frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	    vc_params = system_frame;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qsaving_parameters,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(system_frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	    sv_params = system_frame;
	goto next_loop_3;
      end_loop_3:
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(vc_params,Qenable_kb_change_logging);
	temp_1 = vc_params;
	set_lookup_slot_value_1(temp_1,Qenable_kb_change_logging,
		get_lookup_slot_value_given_default(sv_params,
		Qenable_kb_change_logging_qm,Nil));
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object string_constant_18;  /* "~d~a~a" */

static Object array_constant_3;    /* # */

/* WRITE-FRAME-CHANGE-LOG-FROM-SLOT */
Object write_frame_change_log_from_slot(value,frame)
    Object value, frame;
{
    Object n_1, temp, temp_1;

    x_note_fn_call(163,34);
    n_1 = length(value);
    temp = IFIX(n_1) == (SI_Long)1L ? array_constant_1 : array_constant_2;
    temp_1 = get_lookup_slot_value_given_default(frame,
	    Qchange_log_information,Nil);
    return tformat(4,string_constant_18,n_1,temp,CAR(temp_1) ? 
	    array_constant : array_constant_3);
}

/* GET-CHANGE-LOGGING-REVISION-FOR-SLOT-ON-FRAME */
Object get_change_logging_revision_for_slot_on_frame(frame,slot_name,
	    class_qualifier_qm)
    Object frame, slot_name, class_qualifier_qm;
{
    Object revision_entry, temp, ab_loop_list_, temp_2, initial_revision;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;
    char temp_1;

    x_note_fn_call(163,35);
    ensure_frame_change_log_information(frame);
    revision_entry = Nil;
    temp = get_lookup_slot_value_given_default(frame,
	    Qchange_log_information,Nil);
    ab_loop_list_ = CDR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    revision_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 =  !TRUEP(class_qualifier_qm) ? EQ(slot_name,
	    CAR(revision_entry)) : TRUEP(Qnil);
    if (temp_1);
    else {
	temp = CAR(revision_entry);
	temp_1 = LISTP(temp) && EQ(slot_name,CAAR(revision_entry)) ? 
		EQ(class_qualifier_qm,CDAR(revision_entry)) : TRUEP(Nil);
    }
    if (temp_1) {
	temp_2 = FIXNUM_ADD1(CADR(revision_entry));
	return VALUES_1(M_CADR(revision_entry) = temp_2);
    }
    goto next_loop;
  end_loop:;
    initial_revision = Initial_change_log_revision_number;
    temp_2 = get_lookup_slot_value_given_default(frame,
	    Qchange_log_information,Nil);
    slot_value_push_modify_macro_arg = 
	    change_log_information_entry(slot_name,class_qualifier_qm,
	    initial_revision);
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = CDR(temp_2);
    cdr_new_value = slot_value_cons_1(car_1,cdr_1);
    M_CDR(temp_2) = cdr_new_value;
    return VALUES_1(initial_revision);
}

/* LOG-KB-CHANGE */
Object log_kb_change(frame,slot_name,qualifier_qm,new_text,module_uuid)
    Object frame, slot_name, qualifier_qm, new_text, module_uuid;
{
    Object new_frame_change_log, temp, temp_1, temp_2, new_entry_for_slot;

    x_note_fn_call(163,36);
    new_frame_change_log = get_lookup_slot_value_given_default(frame,
	    Qframe_change_log,Nil);
    temp = get_current_frame_edit_timestamp();
    temp_1 = Servicing_workstation_qm ? ISVREF(Current_workstation,
	    (SI_Long)20L) : Nil;
    if (temp_1);
    else
	temp_1 = get_current_user_name_if_any_case_insensitive();
    if (temp_1);
    else
	temp_1 = get_current_user_name();
    temp_2 = get_change_logging_revision_for_slot_on_frame(frame,slot_name,
	    qualifier_qm);
    new_entry_for_slot = make_change_log_entry_for_slot(slot_name,
	    qualifier_qm,Qpermanent,temp,temp_1,temp_2,Qnil,Qfull_text,
	    new_text,Nil,copy_for_slot_value(module_uuid));
    set_non_savable_lookup_slot_value(frame,Qframe_change_log,Nil);
    new_frame_change_log = slot_value_cons_1(new_entry_for_slot,
	    new_frame_change_log);
    return change_slot_value(3,frame,Qframe_change_log,new_frame_change_log);
}

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

/* UPDATE-CHANGE-LOG-ATTRIBUTE */
Object update_change_log_attribute(frame,slot_description,runtime_change_p)
    Object frame, slot_description, runtime_change_p;
{
    Object uuid_if_logging_qm, temp, pretty_slot_name, class_description;
    Object class_qualifier_qm, entry, ab_loop_list_;
    Object most_recent_change_log_entry_text_qm, newly_installed_text;
    Object log_change_p;
    char temp_1;

    x_note_fn_call(163,37);
    ensure_frame_change_log_information(frame);
    uuid_if_logging_qm = module_uuid_for_frame_if_logging_qm(frame);
    if ( !TRUEP(uuid_if_logging_qm))
	return VALUES_1(Nil);
    else {
	temp = get_lookup_slot_value_given_default(frame,
		Qchange_log_information,Nil);
	if ( !TRUEP(CAR(temp)))
	    return VALUES_1(Nil);
	else if ( !TRUEP(type_of_slot_if_editable(2,ISVREF(ISVREF(frame,
		(SI_Long)1L),(SI_Long)1L),Qframe_author_or_authors)))
	    return VALUES_1(Nil);
	else if (runtime_change_p)
	    return VALUES_1(Nil);
	else {
	    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	    class_description = ISVREF(frame,(SI_Long)1L);
	    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		temp = ISVREF(slot_description,(SI_Long)3L);
		temp_1 =  !EQ(temp,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			(SI_Long)2L),class_description,Nil),(SI_Long)3L));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    class_qualifier_qm = temp_1 ? ISVREF(slot_description,
		    (SI_Long)3L) : Nil;
	    entry = Nil;
	    ab_loop_list_ = get_lookup_slot_value_given_default(frame,
		    Qframe_change_log,Nil);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    entry = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(pretty_slot_name,CAR(entry))) {
		temp = CDR(entry);
		temp_1 = EQ(class_qualifier_qm,CAR(temp));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		temp = entry;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	    temp = CDDDDR(temp);
	    temp = CDDDDR(temp);
	    most_recent_change_log_entry_text_qm = CAR(temp);
	    newly_installed_text = 
		    make_text_representation_for_slot_value(2,frame,
		    ISVREF(slot_description,(SI_Long)1L));
	    log_change_p =  !TRUEP(most_recent_change_log_entry_text_qm) ? 
		    T : Nil;
	    if (log_change_p);
	    else
		log_change_p =  
			!TRUEP(texts_equal_p(most_recent_change_log_entry_text_qm,
			newly_installed_text)) ? T : Nil;
	    if (log_change_p)
		return log_kb_change(frame,pretty_slot_name,
			class_qualifier_qm,newly_installed_text,
			uuid_if_logging_qm);
	    else
		return reclaim_text(newly_installed_text);
	}
    }
}

static Object string_constant_19;  /* "Attribute" */

static Object string_constant_20;  /* "Revision" */

static Object string_constant_21;  /* "Value" */

static Object string_constant_22;  /* "Module Version" */

static Object string_constant_23;  /* "Timestamp" */

static Object string_constant_24;  /* "Author" */

static Object string_constant_25;  /* "Tags" */

/* MAKE-FRAME-CHANGE-LOG-TABLE-STUB-ROWS */
Object make_frame_change_log_table_stub_rows()
{
    Object gensymed_symbol, gensymed_symbol_1, temp, car_new_value;

    x_note_fn_call(163,38);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)7L));
    gensymed_symbol_1 = gensymed_symbol;
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_19));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_description_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_20));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_21));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_22));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_23));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_24));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(1,
	    string_constant_25));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    return slot_value_cons_1(gensymed_symbol,Nil);
}

static Object string_constant_26;  /* "~d" */

static Object string_constant_27;  /* "(unknown)" */

static Object string_constant_28;  /* "~a" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_29;  /* "~(~a~)" */

static Object string_constant_30;  /* "~L,&" */

/* MAKE-FRAME-CHANGE-LOG-TABLE-ROWS-FROM-DATA */
Object make_frame_change_log_table_rows_from_data(frame,row_content_data)
    Object frame, row_content_data;
{
    Object saving_parameters_instance_qm, slot_name, class_qualifier_qm;
    Object revision, text, module_uuid_qm, timestamp, author, tags_qm;
    Object ab_loop_list_, associated_version_qm, version_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp, version;
    Object ab_loop_list__1, version_uuid, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,39);
    saving_parameters_instance_qm = get_saving_parameters_for_frame(frame);
    slot_name = Nil;
    class_qualifier_qm = Nil;
    revision = Nil;
    text = Nil;
    module_uuid_qm = Nil;
    timestamp = Nil;
    author = Nil;
    tags_qm = Nil;
    ab_loop_list_ = row_content_data;
    associated_version_qm = Nil;
    version_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    slot_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    class_qualifier_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    revision = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    text = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    module_uuid_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    timestamp = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    author = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    tags_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (saving_parameters_instance_qm) {
	version = Nil;
	ab_loop_list__1 = 
		get_lookup_slot_value_given_default(saving_parameters_instance_qm,
		Qkb_version_information_for_change_logging,Nil);
	version_uuid = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	version = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = CDDR(version);
	version_uuid = CAR(temp);
	if (uuid_eq(module_uuid_qm,version_uuid)) {
	    associated_version_qm = version;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	associated_version_qm = Qnil;
      end_1:;
    }
    else
	associated_version_qm = Nil;
    version_qm = CAR(associated_version_qm);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)7L));
    gensymed_symbol_1 = gensymed_symbol;
    temp = make_text_for_cell_identifying_attribute_in_table(frame,
	    slot_name,class_qualifier_qm,Nil);
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_description_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(2,
	    string_constant_26,revision));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = copy_text(text);
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = version_qm;
    if (temp);
    else
	temp = string_constant_27;
    temp = convert_text_string_to_text(tformat_text_string(2,
	    string_constant_28,temp));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
	      twrite_frame_edit_timestamp(timestamp);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = convert_text_string_to_text(temp);
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(2,
	    string_constant_29,author && SYMBOLP(author) ? author : 
	    string_constant_27));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = convert_text_string_to_text(tformat_text_string(2,
	    string_constant_30,tags_qm));
    car_new_value = make_text_cell(2,temp,
	    parameterized_attribute_value_format());
    M_CAR(gensymed_symbol_1) = car_new_value;
    ab_loopvar__2 = slot_value_cons_1(gensymed_symbol,Nil);
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

/* MAKE-FRAME-CHANGE-LOG-ROW-CONTENT-DATA */
Object make_frame_change_log_row_content_data(frame)
    Object frame;
{
    Object change_log, entry, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, gensymed_symbol_1, car_new_value;
    Object temp, evaluation_value;

    x_note_fn_call(163,40);
    change_log = get_lookup_slot_value_given_default(frame,
	    Qframe_change_log,Nil);
    entry = Nil;
    ab_loop_list_ = change_log;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)8L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = CAR(entry);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDR(entry);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDDR(entry);
    temp = CDR(temp);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDDR(entry);
    temp = CDDDDR(temp);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDDR(entry);
    temp = CDDDDR(temp);
    temp = CDDR(temp);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDR(entry);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDDR(entry);
    evaluation_value = CAR(temp);
    if (evaluation_value && SYMBOLP(evaluation_value)) {
	temp = CDDDDR(entry);
	car_new_value = CAR(temp);
    }
    else
	car_new_value = Nil;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDDR(entry);
    temp = CDDR(temp);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    ab_loopvar__2 = slot_value_cons_1(gensymed_symbol,Nil);
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

/* MAKE-FRAME-CHANGE-LOG-TABLE-ROWS */
Object make_frame_change_log_table_rows(frame)
    Object frame;
{
    Object row_content_data, temp;

    x_note_fn_call(163,41);
    row_content_data = make_frame_change_log_row_content_data(frame);
    temp = make_frame_change_log_table_stub_rows();
    return VALUES_1(nconc2(temp,
	    make_frame_change_log_table_rows_from_data(frame,
	    row_content_data)));
}

static Object Qnone;               /* none */

static Object list_constant;       /* # */

static Object Qtable_rows;         /* table-rows */

/* MAKE-CHANGE-LOG-TABLE */
Object make_change_log_table(frame)
    Object frame;
{
    Object temp, basic_table, additional_rows, temp_1, car_new_value;

    x_note_fn_call(163,42);
    temp = parameterized_attribute_table_header_format();
    basic_table = make_attributes_table(6,frame,Nil,temp,Nil,Nil,
	    New_g2_classic_ui_p ? Qnone : list_constant);
    additional_rows = make_frame_change_log_table_rows(frame);
    if (New_g2_classic_ui_p) {
	temp = ISVREF(basic_table,(SI_Long)19L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(basic_table,Qtable_rows);
	SVREF(basic_table,FIX((SI_Long)19L)) = Nil;
	reclaim_slot_value(temp);
    }
    else {
	temp_1 = ISVREF(basic_table,(SI_Long)19L);
	temp = ISVREF(basic_table,(SI_Long)19L);
	car_new_value = nconc2(slot_value_list_3(Nil,Nil,Nil),CAR(temp));
	M_CAR(temp_1) = car_new_value;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(basic_table,Qtable_rows);
    temp_1 = nconc2(ISVREF(basic_table,(SI_Long)19L),additional_rows);
    SVREF(basic_table,FIX((SI_Long)19L)) = temp_1;
    reformat_table_in_place(1,basic_table);
    return VALUES_1(basic_table);
}

/* PUT-UP-CHANGE-LOG-TABLE */
Object put_up_change_log_table(frame,x_in_window,y_in_window)
    Object frame, x_in_window, y_in_window;
{
    Object table;

    x_note_fn_call(163,43);
    table = make_change_log_table(frame);
    put_table_on_workspace_in_pane(3,table,x_in_window,y_in_window);
    return VALUES_1(table);
}

/* COM-VIEW-CHANGE-LOG */
Object com_view_change_log(item,original_x_in_window,original_y_in_window)
    Object item, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,44);
    if (of_class_p_function(item,Qitem) && original_x_in_window && 
	    original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
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
	temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		Qframe_change_log,Nil)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_change_log_table(item,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* VIEW-CHANGE-LOG-COMMAND-PURSUER */
Object view_change_log_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item, original_x_in_window, original_y_in_window;

    x_note_fn_call(163,45);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    item = command_argument_value(item);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qview_change_log;    /* view-change-log */

/* VIEW-CHANGE-LOG-COMMAND-TRANSLATOR */
Object view_change_log_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,46);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (item && original_x_in_window && original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
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
	if (temp ? TRUEP(get_lookup_slot_value_given_default(item,
		Qframe_change_log,Nil)) : TRUEP(Nil)) {
	    temp_1 = item;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qview_change_log,
		    slot_value_list_3(temp_2,temp_3,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-VIEW-CHANGE-LOG-FROM-TABLE */
Object com_view_change_log_from_table(slot_name,item,original_x_in_window,
	    original_y_in_window)
    Object slot_name, item, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,47);
    if (slot_name && of_class_p_function(item,Qitem) && 
	    original_x_in_window && original_y_in_window) {
	if (EQ(slot_name,Qframe_change_log)) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qframe_change_log,Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_change_log_table(item,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* VIEW-CHANGE-LOG-FROM-TABLE-COMMAND-PURSUER */
Object view_change_log_from_table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, slot_name, item, original_x_in_window;
    Object original_y_in_window;

    x_note_fn_call(163,48);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    slot_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    slot_name = command_argument_value(slot_name);
    item = command_argument_value(item);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(slot_name,Plus_missing_argument_plus))
	return VALUES_3(Qslot_name,Qslot_name,FIX((SI_Long)0L));
    else if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)1L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)2L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)3L));
    else
	return VALUES_1(Qnil);
}

static Object Qview_change_log_from_table;  /* view-change-log-from-table */

/* VIEW-CHANGE-LOG-FROM-TABLE-COMMAND-TRANSLATOR */
Object view_change_log_from_table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object slot_name, item, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,49);
    slot_name = slot_name_blackboard_function(mouse_pointer);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (slot_name && item && original_x_in_window && original_y_in_window) {
	if (EQ(slot_name,Qframe_change_log)) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qframe_change_log,Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = slot_name;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = item;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_4 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qview_change_log_from_table,
		    slot_value_list_4(temp_2,temp_3,temp_4,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FLUSH-CHANGE-LOG-FOR-ITEM-NOW */
Object flush_change_log_for_item_now(item)
    Object item;
{
    x_note_fn_call(163,50);
    change_slot_value(3,item,Qframe_change_log,Nil);
    return change_slot_value(3,item,Qchange_log_information,Nil);
}

static Object string_constant_31;  /* "Flush the change log for this item?" */

static Object Qflush_change_log_for_item_now;  /* flush-change-log-for-item-now */

/* COM-FLUSH-CHANGE-LOG-FROM-TABLE */
Object com_flush_change_log_from_table(slot_name,item,original_x_in_window,
	    original_y_in_window)
    Object slot_name, item, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,51);
    if (slot_name && of_class_p_function(item,Qitem) && 
	    original_x_in_window && original_y_in_window) {
	if (EQ(slot_name,Qframe_change_log) && Package_preparation_mode) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qframe_change_log,Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = copy_text_string(string_constant_31);
	return confirm_or_cancel(3,temp_1,Qflush_change_log_for_item_now,
		slot_value_cons_1(item,Nil));
    }
    else
	return VALUES_1(Nil);
}

/* FLUSH-CHANGE-LOG-FROM-TABLE-COMMAND-PURSUER */
Object flush_change_log_from_table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, slot_name, item, original_x_in_window;
    Object original_y_in_window;

    x_note_fn_call(163,52);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    slot_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    item = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    slot_name = command_argument_value(slot_name);
    item = command_argument_value(item);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(slot_name,Plus_missing_argument_plus))
	return VALUES_3(Qslot_name,Qslot_name,FIX((SI_Long)0L));
    else if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)1L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)2L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)3L));
    else
	return VALUES_1(Qnil);
}

static Object Qflush_change_log_from_table;  /* flush-change-log-from-table */

/* FLUSH-CHANGE-LOG-FROM-TABLE-COMMAND-TRANSLATOR */
Object flush_change_log_from_table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object slot_name, item, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(163,53);
    slot_name = slot_name_blackboard_function(mouse_pointer);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (slot_name && item && original_x_in_window && original_y_in_window) {
	if (EQ(slot_name,Qframe_change_log) && Package_preparation_mode) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    temp = temp ? TRUEP(get_lookup_slot_value_given_default(item,
		    Qframe_change_log,Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = slot_name;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = item;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_4 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qflush_change_log_from_table,
		    slot_value_list_4(temp_2,temp_3,temp_4,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-FLUSH-CHANGE-LOG-FOR-ITEM */
Object g2_flush_change_log_for_item(item)
    Object item;
{
    x_note_fn_call(163,54);
    return flush_change_log_for_item_now(item);
}

/* FLUSH-CHANGE-LOG-FOR-ENTIRE-KB-NOW */
Object flush_change_log_for_entire_kb_now()
{
    Object scope_conses, ab_loopvar_, class_1, temp, ab_loopvar__1, instance;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,55);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qblock;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      ab_loopvar__1 = lookup_kb_specific_property_value(class_1,
	      Instances_specific_to_this_class_kbprop);
      instance = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1))
	  goto end_loop_1;
      instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      flush_change_log_for_item_now(instance);
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_32;  /* "Flush the change log for the entire KB?" */

static Object Qflush_change_log_for_entire_kb_now;  /* flush-change-log-for-entire-kb-now */

/* COM-FLUSH-CHANGE-LOG-FOR-ENTIRE-KB */
Object com_flush_change_log_for_entire_kb()
{
    x_note_fn_call(163,56);
    if (Package_preparation_mode)
	return confirm_or_cancel(2,copy_text_string(string_constant_32),
		Qflush_change_log_for_entire_kb_now);
    else
	return VALUES_1(Nil);
}

static Object Qflush_change_log_for_entire_kb;  /* flush-change-log-for-entire-kb */

/* FLUSH-CHANGE-LOG-FOR-ENTIRE-KB-COMMAND-TRANSLATOR */
Object flush_change_log_for_entire_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(163,57);
    if (Package_preparation_mode)
	return make_partial_command(Qflush_change_log_for_entire_kb,Nil);
    else
	return VALUES_1(Nil);
}

/* G2-FLUSH-CHANGE-LOG-FOR-ENTIRE-KB */
Object g2_flush_change_log_for_entire_kb()
{
    x_note_fn_call(163,58);
    return flush_change_log_for_entire_kb_now();
}

/* ITEM-HAS-CHANGES-LOGGED-P */
Object item_has_changes_logged_p(item,before,after,author)
    Object item, before, after, author;
{
    Object entry, ab_loop_list_, entry_date, entry_author, ab_loop_it_, temp;

    x_note_fn_call(163,59);
    entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(item,
	    Qframe_change_log,Nil);
    entry_date = Nil;
    entry_author = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDDDR(entry);
    entry_date = CAR(temp);
    temp = CDDDDR(entry);
    entry_author = CAR(temp);
    if (( !FIXNUMP(before) || FIXNUM_LT(entry_date,before)) && ( 
	    !FIXNUMP(after) || FIXNUM_LT(after,entry_date))) {
	temp =  !(author && SYMBOLP(author)) ? T : Nil;
	if (temp);
	else
	    temp = EQ(author,entry_author) ? T : Nil;
	ab_loop_it_ = temp;
    }
    else
	ab_loop_it_ = Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Change_log_type = UNBOUND;

static Object string_constant_33;  /* "" */

/* GET-COMMENT-ON-CHANGE-LOG-ENTRY */
Object get_comment_on_change_log_entry(entry)
    Object entry;
{
    Object temp, log_qm;

    x_note_fn_call(163,60);
    temp = CDDDDR(entry);
    temp = CDDDDR(temp);
    temp = CDR(temp);
    log_qm = CAR(temp);
    if (log_qm)
	return copy_wide_string(log_qm);
    else
	return copy_as_wide_string(string_constant_33);
}

static Object Qattribute;          /* attribute */

static Object string_constant_34;  /* "~A::~A" */

static Object Qrevision;           /* revision */

static Object Qcomment;            /* comment */

static Object Qtags;               /* tags */

static Object Qmodule_version;     /* module-version */

static Object Qtimestamp;          /* timestamp */

static Object Qauthor;             /* author */

/* MAKE-CHANGE-LOG-ENTRY-EVAL-STRUCT */
Object make_change_log_entry_eval_struct(entry_qm,item)
    Object entry_qm, item;
{
    Object saving_parameters_qm, temp, change_log_entry_author_qm;
    Object gensymed_symbol, gensymed_symbol_1, defining_class;
    Object pretty_slot_name, text_string, car_new_value, class_or_frame_qm;
    Object version, ab_loop_list_, temp_1;

    x_note_fn_call(163,61);
    if ( !TRUEP(entry_qm))
	return allocate_evaluation_structure(Nil);
    else {
	saving_parameters_qm = get_saving_parameters_for_frame(item);
	temp = CDDDDR(entry_qm);
	change_log_entry_author_qm = CAR(temp);
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)16L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qattribute;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = CDR(entry_qm);
	if (CAR(temp)) {
	    temp = CDR(entry_qm);
	    defining_class = CAR(temp);
	    pretty_slot_name = CAR(entry_qm);
	    text_string = tformat_text_string(3,string_constant_34,
		    defining_class,pretty_slot_name);
	    car_new_value = intern_text_string(2,text_string,
		    Keyword_package_1);
	}
	else {
	    pretty_slot_name = CAR(entry_qm);
	    class_or_frame_qm = item;
	    car_new_value = 
		    get_alias_for_slot_name_if_any(pretty_slot_name,
		    class_or_frame_qm);
	    if (car_new_value);
	    else
		car_new_value = pretty_slot_name;
	}
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qrevision;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = CDDDDR(entry_qm);
	temp = CDR(temp);
	car_new_value = CAR(temp);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcomment;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = get_comment_on_change_log_entry(entry_qm);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtags;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = CDDDDR(entry_qm);
	temp = CDDR(temp);
	car_new_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(CAR(temp)));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtext_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = CDDDDR(entry_qm);
	temp = CDDDDR(temp);
	car_new_value = convert_text_to_text_string(1,CAR(temp));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qmodule_version;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	if (saving_parameters_qm) {
	    version = Nil;
	    ab_loop_list_ = 
		    get_lookup_slot_value_given_default(saving_parameters_qm,
		    Qkb_version_information_for_change_logging,Nil);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    version = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = CDDDDR(entry_qm);
	    temp = CDDDDR(temp);
	    temp = CDDR(temp);
	    temp_1 = CDDR(version);
	    if (uuid_eq(CAR(temp),CAR(temp_1))) {
		car_new_value = CAR(version);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    car_new_value = Qnil;
	  end_1:;
	}
	else
	    car_new_value = FIX((SI_Long)0L);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qtimestamp;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = CDDDR(entry_qm);
	car_new_value = 
		evaluation_structure_for_frame_edit_timestamp(CAR(temp));
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qauthor;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = change_log_entry_author_qm && 
		SYMBOLP(change_log_entry_author_qm) ? 
		change_log_entry_author_qm : Nil;
	M_CAR(gensymed_symbol_1) = car_new_value;
	return allocate_evaluation_structure(gensymed_symbol);
    }
}

/* FRAME-CHANGE-LOG-AS-SEQUENCE-OF-STRUCTURES */
Object frame_change_log_as_sequence_of_structures(frame_change_log,item)
    Object frame_change_log, item;
{
    Object entry, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(163,62);
    entry = Nil;
    ab_loop_list_ = frame_change_log;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(make_change_log_entry_eval_struct(entry,
	    item),Nil);
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
    return allocate_evaluation_sequence(temp);
}

/* FRAME-CHANGE-LOG-EVALUATION-GETTER */
Object frame_change_log_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(163,63);
    GENSYM_RETURN_ONE(frame_change_log_as_sequence_of_structures(slot_value,
	    frame));
    return VALUES_1(Nil);
}

/* MAKE-DEFAULT-CHANGE-LOGGING-IDENTIFIER */
Object make_default_change_logging_identifier()
{
    x_note_fn_call(163,64);
    return gensym_list_2(Qtimestamp,get_current_frame_edit_timestamp());
}

/* CHANGE-LOG-ENTRY-BY-REVISION? */
Object change_log_entry_by_revision_qm(item,slot_name,revision)
    Object item, slot_name, revision;
{
    Object entry, ab_loop_list_, entry_slot_name, entry_revision;
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(163,65);
    entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(item,
	    Qframe_change_log,Nil);
    entry_slot_name = Nil;
    entry_revision = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pretty_slot_name = CAR(entry);
    class_or_frame_qm = item;
    temp = get_alias_for_slot_name_if_any(pretty_slot_name,class_or_frame_qm);
    if (temp);
    else
	temp = pretty_slot_name;
    entry_slot_name = temp;
    temp = CDDDDR(entry);
    temp = CDR(temp);
    entry_revision = CAR(temp);
    if (EQ(entry_slot_name,slot_name) && EQL(entry_revision,revision))
	return VALUES_1(entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHANGE-LOG-ENTRY-BY-TAG? */
Object change_log_entry_by_tag_qm(item,slot_name,tag)
    Object item, slot_name, tag;
{
    Object entry, ab_loop_list_, entry_slot_name, entry_tags_qm;
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(163,66);
    entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(item,
	    Qframe_change_log,Nil);
    entry_slot_name = Nil;
    entry_tags_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pretty_slot_name = CAR(entry);
    class_or_frame_qm = item;
    temp = get_alias_for_slot_name_if_any(pretty_slot_name,class_or_frame_qm);
    if (temp);
    else
	temp = pretty_slot_name;
    entry_slot_name = temp;
    temp = CDDDDR(entry);
    temp = CDDR(temp);
    entry_tags_qm = CAR(temp);
    if (EQ(entry_slot_name,slot_name) && memq_function(tag,entry_tags_qm))
	return VALUES_1(entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHANGE-LOG-ENTRY-BY-DATE? */
Object change_log_entry_by_date_qm(item,slot_name,encoded_timestamp)
    Object item, slot_name, encoded_timestamp;
{
    Object entry, ab_loop_list_, entry_slot_name, entry_timestamp_qm;
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(163,67);
    entry = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(item,
	    Qframe_change_log,Nil);
    entry_slot_name = Nil;
    entry_timestamp_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pretty_slot_name = CAR(entry);
    class_or_frame_qm = item;
    temp = get_alias_for_slot_name_if_any(pretty_slot_name,class_or_frame_qm);
    if (temp);
    else
	temp = pretty_slot_name;
    entry_slot_name = temp;
    temp = CDDDR(entry);
    entry_timestamp_qm = CAR(temp);
    if (EQ(slot_name,entry_slot_name) && FIXNUM_LE(entry_timestamp_qm,
	    encoded_timestamp))
	return VALUES_1(entry);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DELETE-CHANGE-LOG-ENTRY */
Object delete_change_log_entry(frame,entry)
    Object frame, entry;
{
    Object new_frame_change_log, rest_1, cdr_new_value;

    x_note_fn_call(163,68);
    new_frame_change_log = get_lookup_slot_value_given_default(frame,
	    Qframe_change_log,Nil);
    set_non_savable_lookup_slot_value(frame,Qframe_change_log,Nil);
    if (EQ(entry,CAR(new_frame_change_log))) {
	new_frame_change_log = CDR(new_frame_change_log);
	reclaim_slot_value_list_1(entry);
    }
    else {
	rest_1 = new_frame_change_log;
      next_loop:
	if ( !TRUEP(rest_1))
	    goto end_loop;
	if (EQ(entry,CADR(rest_1))) {
	    cdr_new_value = CDDR(rest_1);
	    M_CDR(rest_1) = cdr_new_value;
	}
	rest_1 = M_CDR(rest_1);
	goto next_loop;
      end_loop:;
	reclaim_slot_value_list_1(entry);
    }
    return change_slot_value(3,frame,Qframe_change_log,new_frame_change_log);
}

/* SET-COMMENT-ON-CHANGE-LOG-ENTRY */
Object set_comment_on_change_log_entry(entry,comment)
    Object entry, comment;
{
    Object temp, thing, car_arg;

    x_note_fn_call(163,69);
    temp = CDDDDR(entry);
    temp = CDDDDR(temp);
    temp = CDR(temp);
    thing = CAR(temp);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L) {
	temp = CDDDDR(entry);
	temp = CDDDDR(temp);
	temp = CDR(temp);
	reclaim_text_string(CAR(temp));
    }
    temp = CDDDDR(entry);
    temp = CDDDDR(temp);
    car_arg = CDR(temp);
    return VALUES_1(M_CAR(car_arg) = comment);
}

static Object Qtag;                /* tag */

/* GET-CHANGE-LOG-ENTRY */
Object get_change_log_entry(item,slot_name,specification)
    Object item, slot_name, specification;
{
    Object temp, revision_qm, tag_qm, timestamp_qm;

    x_note_fn_call(163,70);
    temp = memq_function(Qrevision,specification);
    revision_qm = CADR(temp);
    temp = memq_function(Qtag,specification);
    tag_qm = CADR(temp);
    temp = memq_function(Qtimestamp,specification);
    timestamp_qm = CADR(temp);
    if (revision_qm)
	return change_log_entry_by_revision_qm(item,slot_name,revision_qm);
    else if (tag_qm)
	return change_log_entry_by_tag_qm(item,slot_name,tag_qm);
    else if (timestamp_qm)
	return change_log_entry_by_date_qm(item,slot_name,timestamp_qm);
    else
	return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

/* ILLEGAL-CHANGE-LOGGING-TAG-P */
Object illegal_change_logging_tag_p(new_tag)
    Object new_tag;
{
    x_note_fn_call(163,71);
    return memq_function(new_tag,list_constant_1);
}

static Object Qillegal_tag;        /* illegal-tag */

static Object Qno_such_entry;      /* no-such-entry */

static Object Qtag_already_used;   /* tag-already-used */

/* TAG-CHANGE-LOG-ENTRY */
Object tag_change_log_entry(item,slot_name,identifier,new_tag)
    Object item, slot_name, identifier, new_tag;
{
    Object found_entry_qm, temp, car_arg, car_new_value;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1;

    x_note_fn_call(163,72);
    if (illegal_change_logging_tag_p(new_tag))
	return VALUES_1(Qillegal_tag);
    else {
	found_entry_qm = get_change_log_entry(item,slot_name,identifier);
	if ( !TRUEP(found_entry_qm))
	    return VALUES_1(Qno_such_entry);
	else {
	    temp = CDDDDR(found_entry_qm);
	    temp = CDDR(temp);
	    if (memq_function(new_tag,CAR(temp)))
		return VALUES_1(found_entry_qm);
	    else if (change_log_entry_by_tag_qm(item,slot_name,new_tag))
		return VALUES_1(Qtag_already_used);
	    else {
		temp = CDDDDR(found_entry_qm);
		temp = CDDR(temp);
		if ( !TRUEP(CAR(temp))) {
		    temp = CDDDDR(found_entry_qm);
		    car_arg = CDDR(temp);
		    car_new_value = slot_value_cons_1(new_tag,Nil);
		    M_CAR(car_arg) = car_new_value;
		    return VALUES_1(found_entry_qm);
		}
		else {
		    temp = CDDDDR(found_entry_qm);
		    car_arg = CDDR(temp);
		    slot_value_push_modify_macro_arg = new_tag;
		    car_1 = slot_value_push_modify_macro_arg;
		    cdr_1 = CAR(car_arg);
		    car_new_value = slot_value_cons_1(car_1,cdr_1);
		    M_CAR(car_arg) = car_new_value;
		    return VALUES_1(found_entry_qm);
		}
	    }
	}
    }
}

/* TAG-ITEM-CHANGE-LOG */
Object tag_item_change_log(item,id_as_list,new_tag)
    Object item, id_as_list, new_tag;
{
    Object entry, temp, ab_loop_list_, slot_name;

    x_note_fn_call(163,73);
    entry = Nil;
    temp = get_lookup_slot_value_given_default(item,
	    Qchange_log_information,Nil);
    ab_loop_list_ = CDR(temp);
    slot_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = CAR(entry);
    if (SYMBOLP(slot_name)) {
	temp = get_alias_for_slot_name_if_any(slot_name,item);
	if (temp);
	else
	    temp = slot_name;
	tag_change_log_entry(item,temp,id_as_list,new_tag);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TAG-ALL-FRAMES-IN-MODULE */
Object tag_all_frames_in_module(module_name,new_tag,id_as_list)
    Object module_name, new_tag, id_as_list;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,74);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qblock);
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
      if (EQ(module_name,get_module_block_is_in(item)))
	  tag_item_change_log(item,id_as_list,new_tag);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* DELETE-CHANGE-LOG-TAG-1 */
Object delete_change_log_tag_1(found_entry_qm,new_tag)
    Object found_entry_qm, new_tag;
{
    Object temp, car_arg, cons_to_delete, car_new_value;

    x_note_fn_call(163,75);
    if ( !TRUEP(found_entry_qm));
    else {
	temp = CDDDDR(found_entry_qm);
	temp = CDDR(temp);
	temp = CAR(temp);
	if ( !TRUEP(CDR(temp))) {
	    temp = CDDDDR(found_entry_qm);
	    temp = CDDR(temp);
	    reclaim_slot_value_list_1(CAR(temp));
	    temp = CDDDDR(found_entry_qm);
	    car_arg = CDDR(temp);
	    M_CAR(car_arg) = Nil;
	}
	else {
	    temp = CDDDDR(found_entry_qm);
	    temp = CDDR(temp);
	    temp = CAR(temp);
	    if (EQ(new_tag,CAR(temp))) {
		temp = CDDDDR(found_entry_qm);
		temp = CDDR(temp);
		cons_to_delete = CAR(temp);
		temp = CDDDDR(found_entry_qm);
		car_arg = CDDR(temp);
		temp = CDDDDR(found_entry_qm);
		temp = CDDR(temp);
		temp = CAR(temp);
		car_new_value = CDR(temp);
		M_CAR(car_arg) = car_new_value;
		reclaim_slot_value_cons_1(cons_to_delete);
	    }
	    else {
		temp = CDDDDR(found_entry_qm);
		temp = CDDR(temp);
		delete_slot_value_element_1(new_tag,CAR(temp));
	    }
	}
    }
    return VALUES_1(found_entry_qm);
}

/* DELETE-CHANGE-LOG-TAG */
Object delete_change_log_tag(item,slot_name,new_tag,error_on_unfound_p)
    Object item, slot_name, new_tag, error_on_unfound_p;
{
    Object found_entry_qm;

    x_note_fn_call(163,76);
    found_entry_qm = change_log_entry_by_tag_qm(item,slot_name,new_tag);
    if (error_on_unfound_p &&  !TRUEP(found_entry_qm))
	return VALUES_1(Qno_such_entry);
    else
	return delete_change_log_tag_1(found_entry_qm,new_tag);
}

/* REVERT-CHANGE-LOG-ENTRY */
Object revert_change_log_entry(item,slot_name,identifier)
    Object item, slot_name, identifier;
{
    Object found_entry_qm, temp, temp_1;

    x_note_fn_call(163,77);
    found_entry_qm = get_change_log_entry(item,slot_name,identifier);
    if (found_entry_qm) {
	temp = CAR(found_entry_qm);
	temp_1 = CDDDDR(found_entry_qm);
	temp_1 = CDDDDR(temp_1);
	change_the_text_of(3,item,temp,convert_text_to_text_string(1,
		CAR(temp_1)));
    }
    return VALUES_1(found_entry_qm);
}

/* REVERT-ITEM-PER-CHANGE-LOG */
Object revert_item_per_change_log(item,id_as_list)
    Object item, id_as_list;
{
    Object class_description, entry, temp, ab_loop_list_, slot_name;
    Object slot_description_qm;

    x_note_fn_call(163,78);
    class_description = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(item,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    entry = Nil;
    temp = get_lookup_slot_value_given_default(item,
	    Qchange_log_information,Nil);
    ab_loop_list_ = CDR(temp);
    slot_name = Nil;
    slot_description_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = CAR(entry);
    slot_description_qm = SYMBOLP(slot_name) ? get_slot_description(2,
	    slot_name,ISVREF(class_description,(SI_Long)6L)) : Qnil;
    if (slot_description_qm) {
	temp = get_alias_for_slot_name_if_any(slot_name,item);
	if (temp);
	else
	    temp = slot_name;
	revert_change_log_entry(item,temp,id_as_list);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REVERT-ALL-FRAMES-IN-MODULE */
Object revert_all_frames_in_module(module_name,id_as_list)
    Object module_name, id_as_list;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,79);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qblock);
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
      if (EQ(module_name,get_module_block_is_in(item)))
	  revert_item_per_change_log(item,id_as_list);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SET-CHANGE-LOGGING-P-ON-ITEM */
Object set_change_logging_p_on_item(frame,log_p)
    Object frame, log_p;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object temp_1, frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_3;
    Object stack_change_pop_store, cons_1, next_cons;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(163,80);
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_change_log,
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(frame,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop),Nil);
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
      ensure_frame_change_log_information(frame);
      temp = get_lookup_slot_value_given_default(frame,
	      Qchange_log_information,Nil);
      temp_1 = M_CAR(temp) = log_p;
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
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
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
	  update_all_representations_of_slot(frame,slot_description,Nil,Nil);
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

/* ENCODE-DATE-INTO-EDIT-TIMESTAMP */
Object encode_date_into_edit_timestamp(seconds,minutes,hours,date,month,year)
    Object seconds, minutes, hours, date, month, year;
{
    Object temp, delta, converted_to_minutes;
    double unix_time, arg, arg_1, gensymed_symbol, gensymed_symbol_1;
    double raw_encoded_ts;

    x_note_fn_call(163,81);
    unix_time = g2ext_get_encoded_unix_time(IFIX(seconds),IFIX(minutes),
	    IFIX(hours),IFIX(date),IFIX(month),IFIX(year));
    arg = unix_time;
    arg_1 = -1.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	temp = encode_unix_time_after_failure(seconds,minutes,hours,date,
		month,year);
	gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
    }
    else
	gensymed_symbol = unix_time;
    gensymed_symbol_1 = (double)((SI_Long)60L * 
	    IFIX(Global_daylight_saving_time_adjustment));
    raw_encoded_ts = gensymed_symbol - gensymed_symbol_1;
    delta = minus(DOUBLE_TO_DOUBLE_FLOAT(raw_encoded_ts),
	    Time_of_frame_edit_base_time);
    converted_to_minutes = divide(delta,FIX((SI_Long)60L));
    return l_round(converted_to_minutes,_);
}

static Object Qab_structure;       /* structure */

static Object string_constant_35;  /* "Timestamp must be structure." */

static Object Qminutes;            /* minutes */

static Object Qhours;              /* hours */

static Object Qdate;               /* date */

static Object Qmonth;              /* month */

static Object Qyear;               /* year */

static Object string_constant_36;  /* "Minutes must be integer between 0 and 59, inclusive." */

static Object string_constant_37;  /* "Hours must be integer between 0 and 23, inclusive." */

static Object string_constant_38;  /* "Month must be integer between 1 and 12, inclusive." */

static Object string_constant_39;  /* "Year must be integer between 1970 and 2038, inclusive." */

static Object string_constant_40;  /* "Date must make sense for given month and year." */

/* EDIT-TIMESTAMP-OR-STACK-ERROR? */
Object edit_timestamp_or_stack_error_qm(timestamp_qm)
    Object timestamp_qm;
{
    Object top_of_stack, message_1, minutes, hours, date_qm, month_qm, year_qm;

    x_note_fn_call(163,82);
    if (timestamp_qm &&  !(CONSP(timestamp_qm) && EQ(M_CDR(timestamp_qm),
	    Qab_structure))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_35);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (timestamp_qm) {
	minutes = estructure_slot(timestamp_qm,Qminutes,FIX((SI_Long)0L));
	hours = estructure_slot(timestamp_qm,Qhours,FIX((SI_Long)0L));
	date_qm = estructure_slot(timestamp_qm,Qdate,Nil);
	month_qm = estructure_slot(timestamp_qm,Qmonth,Nil);
	year_qm = estructure_slot(timestamp_qm,Qyear,Nil);
	if ( !(FIXNUMP(minutes) && num_len(3,FIX((SI_Long)0L),minutes,
		FIX((SI_Long)59L)))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_36);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if ( !(FIXNUMP(hours) && num_len(3,FIX((SI_Long)0L),hours,
		FIX((SI_Long)23L)))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_37);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if ( !(FIXNUMP(month_qm) && num_len(3,FIX((SI_Long)1L),month_qm,
		FIX((SI_Long)12L)))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_38);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if ( !(FIXNUMP(year_qm) && num_len(3,FIX((SI_Long)1970L),year_qm,
		FIX((SI_Long)2038L)))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_39);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if ( !(FIXNUMP(date_qm) && valid_date_for_month_p(date_qm,month_qm,
		year_qm))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_40);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	return encode_date_into_edit_timestamp(FIX((SI_Long)0L),minutes,
		hours,date_qm,month_qm,year_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_41;  /* "Must supply revision, tag, or timestamp." */

static Object string_constant_42;  /* "Cannot supply both revision and tag." */

static Object string_constant_43;  /* "Cannot supply both revision and timestamp." */

static Object string_constant_44;  /* "Cannot supply both tag and timestamp." */

static Object string_constant_45;  /* "Revision must be integer." */

static Object string_constant_46;  /* "Tag must be symbol." */

static Object string_constant_47;  /* "Cannot parse timestamp." */

/* CONVERT-CHANGE-LOG-IDENTIFIER-STRUCTURE-TO-LIST */
Object convert_change_log_identifier_structure_to_list(identifier,
	    allow_empty_p)
    Object identifier, allow_empty_p;
{
    Object revision_qm, tag_qm, timestamp_qm, top_of_stack, message_1;
    Object evaluated_timestamp_qm;

    x_note_fn_call(163,83);
    revision_qm = estructure_slot(identifier,Qrevision,Nil);
    tag_qm = estructure_slot(identifier,Qtag,Nil);
    timestamp_qm = estructure_slot(identifier,Qtimestamp,Nil);
    if ( !(allow_empty_p || revision_qm || tag_qm || timestamp_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_41);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (revision_qm && tag_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_42);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (revision_qm && timestamp_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_43);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (tag_qm && timestamp_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_44);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (revision_qm &&  !FIXNUMP(revision_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_45);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (tag_qm &&  !(tag_qm && SYMBOLP(tag_qm))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_46);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (revision_qm)
	return gensym_list_2(Qrevision,revision_qm);
    else if (tag_qm)
	return gensym_list_2(Qtag,tag_qm);
    else if (timestamp_qm) {
	evaluated_timestamp_qm = 
		edit_timestamp_or_stack_error_qm(timestamp_qm);
	if (evaluated_timestamp_qm)
	    return gensym_list_2(Qtimestamp,evaluated_timestamp_qm);
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_47);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    else
	return make_default_change_logging_identifier();
}

/* G2-GET-CHANGE-LOG-ENTRY */
Object g2_get_change_log_entry(item,slot_name,id_structure)
    Object item, slot_name, id_structure;
{
    Object specification_as_list, found_entry_qm;

    x_note_fn_call(163,84);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(id_structure,T);
    found_entry_qm = get_change_log_entry(item,slot_name,
	    specification_as_list);
    reclaim_gensym_list_1(specification_as_list);
    return make_change_log_entry_eval_struct(found_entry_qm,item);
}

static Object string_constant_48;  /* "No change-log entry found for ~NA." */

/* G2-DIFF-CHANGE-LOG-ENTRIES */
Object g2_diff_change_log_entries(item,slot_name,id_struct1,id_struct2)
    Object item, slot_name, id_struct1, id_struct2;
{
    Object spec1, spec2, entry1_qm, entry2_qm, error_symbol_qm, top_of_stack;
    Object message_1, temp, string1, string2, result_1;

    x_note_fn_call(163,85);
    spec1 = convert_change_log_identifier_structure_to_list(id_struct1,T);
    spec2 = convert_change_log_identifier_structure_to_list(id_struct2,T);
    entry1_qm = get_change_log_entry(item,slot_name,spec1);
    entry2_qm = get_change_log_entry(item,slot_name,spec2);
    error_symbol_qm = verify_external_diffing(T);
    reclaim_gensym_list_1(spec1);
    reclaim_gensym_list_1(spec2);
    if (error_symbol_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_17,
		error_symbol_qm);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if ( !TRUEP(entry1_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_48,
		id_struct1);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if ( !TRUEP(entry2_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_48,
		id_struct2);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	temp = CDDDDR(entry1_qm);
	temp = CDDDDR(temp);
	string1 = convert_text_to_text_string(1,CAR(temp));
	temp = CDDDDR(entry2_qm);
	temp = CDDDDR(temp);
	string2 = convert_text_to_text_string(1,CAR(temp));
	result_1 = external_diff_text_strings(string1,string2);
	reclaim_text_string(string1);
	reclaim_text_string(string2);
	return VALUES_1(result_1);
    }
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object array_constant_4;    /* # */

static Object string_constant_49;  /* "Tag ~s is already in use on ~NF." */

/* G2-TAG-CHANGE-LOG-ENTRY */
Object g2_tag_change_log_entry(item,slot_name,identifier,new_tag)
    Object item, slot_name, identifier, new_tag;
{
    Object specification_as_list, modified_entry_or_error, top_of_stack;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(163,86);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(identifier,T);
    modified_entry_or_error = tag_change_log_entry(item,slot_name,
	    specification_as_list,new_tag);
    reclaim_gensym_list_1(specification_as_list);
    if (EQ(modified_entry_or_error,Qillegal_tag)) {
	top_of_stack = Cached_top_of_stack;
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
		      twrite_symbol(2,new_tag,T);
		      twrite_beginning_of_wide_string(array_constant_4,
			      FIX((SI_Long)38L));
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
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (EQ(modified_entry_or_error,Qno_such_entry)) {
	top_of_stack = Cached_top_of_stack;
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
		      tformat(2,string_constant_48,identifier);
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
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (EQ(modified_entry_or_error,Qtag_already_used)) {
	top_of_stack = Cached_top_of_stack;
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
		      tformat(3,string_constant_49,new_tag,item);
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
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return make_change_log_entry_eval_struct(modified_entry_or_error,item);
}

static Object string_constant_50;  /* "No change-log entry found with tag ~NA." */

/* G2-DELETE-CHANGE-LOG-TAG */
Object g2_delete_change_log_tag(item,slot_name,tag_to_delete)
    Object item, slot_name, tag_to_delete;
{
    Object modified_entry_or_error, top_of_stack, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(163,87);
    modified_entry_or_error = delete_change_log_tag(item,slot_name,
	    tag_to_delete,T);
    if (EQ(modified_entry_or_error,Qno_such_entry)) {
	top_of_stack = Cached_top_of_stack;
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
		      tformat(2,string_constant_50,tag_to_delete);
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
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return make_change_log_entry_eval_struct(modified_entry_or_error,item);
}

/* G2-DELETE-CHANGE-LOG-ENTRY */
Object g2_delete_change_log_entry(item,slot_name,id_structure)
    Object item, slot_name, id_structure;
{
    Object specification_as_list, found_entry_qm;

    x_note_fn_call(163,88);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(id_structure,Nil);
    found_entry_qm = get_change_log_entry(item,slot_name,
	    specification_as_list);
    reclaim_gensym_list_1(specification_as_list);
    if ( !TRUEP(found_entry_qm))
	return VALUES_1(Evaluation_false_value);
    else {
	delete_change_log_entry(item,found_entry_qm);
	return VALUES_1(Evaluation_true_value);
    }
}

static Object string_constant_51;  /* "No change-log entry found." */

/* G2-SET-CHANGE-LOG-ENTRY-COMMENT */
Object g2_set_change_log_entry_comment(item,slot_name,id_structure,comment)
    Object item, slot_name, id_structure, comment;
{
    Object specification_as_list, found_entry_qm, top_of_stack, message_1;

    x_note_fn_call(163,89);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(id_structure,Nil);
    found_entry_qm = get_change_log_entry(item,slot_name,
	    specification_as_list);
    reclaim_gensym_list_1(specification_as_list);
    if ( !TRUEP(found_entry_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_51);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	set_comment_on_change_log_entry(found_entry_qm,comment);
	return VALUES_1(Nil);
    }
}

/* G2-GET-CHANGE-LOG-ENTRY-COMMENT */
Object g2_get_change_log_entry_comment(item,slot_name,id_structure)
    Object item, slot_name, id_structure;
{
    Object specification_as_list, found_entry_qm;

    x_note_fn_call(163,90);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(id_structure,Nil);
    found_entry_qm = get_change_log_entry(item,slot_name,
	    specification_as_list);
    reclaim_gensym_list_1(specification_as_list);
    if ( !TRUEP(found_entry_qm))
	return copy_as_wide_string(string_constant_33);
    else
	return get_comment_on_change_log_entry(found_entry_qm);
}

static Object string_constant_52;  /* "No matching change-log entry found." */

/* G2-REVERT-CHANGE-LOG-ENTRY */
Object g2_revert_change_log_entry(item,slot_name,id_structure)
    Object item, slot_name, id_structure;
{
    Object specification_as_list, found_entry_qm, top_of_stack, message_1;

    x_note_fn_call(163,91);
    specification_as_list = 
	    convert_change_log_identifier_structure_to_list(id_structure,Nil);
    found_entry_qm = revert_change_log_entry(item,slot_name,
	    specification_as_list);
    reclaim_gensym_list_1(specification_as_list);
    if ( !TRUEP(found_entry_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_52);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return make_change_log_entry_eval_struct(found_entry_qm,item);
}

/* G2-TAG-MODULE */
Object g2_tag_module(module_name,id_structure,new_tag)
    Object module_name, id_structure, new_tag;
{
    Object specification_as_list;

    x_note_fn_call(163,92);
    if ( !TRUEP(module_exists_p(module_name)))
	return VALUES_1(Evaluation_false_value);
    else {
	specification_as_list = 
		convert_change_log_identifier_structure_to_list(id_structure,
		T);
	tag_all_frames_in_module(module_name,new_tag,specification_as_list);
	reclaim_gensym_list_1(specification_as_list);
	return VALUES_1(Evaluation_true_value);
    }
}

/* G2-REVERT-MODULE */
Object g2_revert_module(module_name,id_structure)
    Object module_name, id_structure;
{
    Object specification_as_list;

    x_note_fn_call(163,93);
    if ( !TRUEP(module_exists_p(module_name)))
	return VALUES_1(Evaluation_false_value);
    else {
	specification_as_list = 
		convert_change_log_identifier_structure_to_list(id_structure,
		Nil);
	revert_all_frames_in_module(module_name,specification_as_list);
	reclaim_gensym_list_1(specification_as_list);
	return VALUES_1(Evaluation_true_value);
    }
}

/* G2-DISABLE-CHANGE-LOGGING-ON-ITEM */
Object g2_disable_change_logging_on_item(frame)
    Object frame;
{
    x_note_fn_call(163,94);
    return set_change_logging_p_on_item(frame,Nil);
}

/* G2-ENABLE-CHANGE-LOGGING-ON-ITEM */
Object g2_enable_change_logging_on_item(frame)
    Object frame;
{
    x_note_fn_call(163,95);
    return set_change_logging_p_on_item(frame,T);
}

/* G2-IS-GPU-ENABLED */
Object g2_is_gpu_enabled()
{
    x_note_fn_call(163,96);
    return VALUES_1(Evaluation_false_value);
}

static Object string_constant_53;  /* "~NA" */

/* TWRITE-CHANGE-LOG-ENTRY-AS-STRUCT */
Object twrite_change_log_entry_as_struct(entry,item)
    Object entry, item;
{
    Object eval_struct, temp;

    x_note_fn_call(163,97);
    eval_struct = make_change_log_entry_eval_struct(entry,item);
    temp = tformat(2,string_constant_53,eval_struct);
    reclaim_evaluation_structure(eval_struct);
    return VALUES_1(temp);
}

static Object string_constant_54;  /* "No item named ~s exists." */

static Object string_constant_55;  /* "~s has no change-log." */

/* QUERY-SHOW-LOGGED-CHANGES */
Object query_show_logged_changes(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object item_name, item_qm, change_log_qm, list_of_strings, gensymed_symbol;
    Object held_vector, struct_1, string_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(163,98);
    item_name = SECOND(query);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
    change_log_qm = item_qm ? 
	    frame_change_log_as_sequence_of_structures(get_lookup_slot_value_given_default(item_qm,
	    Qframe_change_log,Nil),item_qm) : Qnil;
    if (run_invisibly_p)
	list_of_strings = Nil;
    else if ( !TRUEP(item_qm))
	list_of_strings = gensym_cons_1(tformat_text_string(2,
		string_constant_54,item_name),Nil);
    else if ((SI_Long)0L == IFIX(FIXNUM_SUB1(ISVREF(M_CAR(change_log_qm),
	    (SI_Long)1L))))
	list_of_strings = gensym_cons_1(tformat_text_string(2,
		string_constant_55,item_name),Nil);
    else {
	gensymed_symbol = change_log_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	struct_1 = Nil;
	string_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	struct_1 = validated_elt;
	string_1 = tformat_text_string(2,string_constant_53,struct_1);
	ab_loopvar__2 = gensym_cons_1(string_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	list_of_strings = ab_loopvar_;
	goto end_1;
	list_of_strings = Qnil;
      end_1:;
    }
    if (change_log_qm)
	reclaim_evaluation_sequence(change_log_qm);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(list_of_strings,
		inspect_command);
    else
	return VALUES_1(Nil);
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* QUERY-SHOW-DIFFS-ON-A-WORKSPACE */
Object query_show_diffs_on_a_workspace(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object diff_error_qm, spec_1, spec_2, temp, slot_name_1, item_name_1;
    Object item_1_qm, vc_spec_1, type_of_spec_1, identifier_1;
    Object actual_change_log_entry_1_qm, string_1_qm, slot_name_2, item_name_2;
    Object item_2_qm, vc_spec_2, type_of_spec_2, identifier_2;
    Object actual_change_log_entry_2_qm, string_2_qm, result_1, output_text_qm;
    Object error_text_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_string, items_to_display;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,99);
    diff_error_qm = verify_external_diffing(T);
    spec_1 = CADR(query);
    spec_2 = CADDR(query);
    temp = CADAR(spec_1);
    slot_name_1 = CAR(temp);
    temp = CADAR(spec_1);
    item_name_1 = CADR(temp);
    item_1_qm = get_instance_with_name_if_any(Qblock,item_name_1);
    vc_spec_1 = CADR(spec_1);
    type_of_spec_1 = CAR(vc_spec_1);
    identifier_1 = CADR(vc_spec_1);
    if (item_1_qm) {
	if (EQ(type_of_spec_1,Qrevision))
	    actual_change_log_entry_1_qm = 
		    change_log_entry_by_revision_qm(item_1_qm,slot_name_1,
		    identifier_1);
	else if (EQ(type_of_spec_1,Qtag))
	    actual_change_log_entry_1_qm = 
		    change_log_entry_by_tag_qm(item_1_qm,slot_name_1,
		    identifier_1);
	else if (EQ(type_of_spec_1,Qtimestamp))
	    actual_change_log_entry_1_qm = 
		    change_log_entry_by_date_qm(item_1_qm,slot_name_1,
		    identifier_1);
	else
	    actual_change_log_entry_1_qm = Qnil;
    }
    else
	actual_change_log_entry_1_qm = Nil;
    if (actual_change_log_entry_1_qm) {
	temp = CDDDDR(actual_change_log_entry_1_qm);
	temp = CDDDDR(temp);
	string_1_qm = convert_text_to_text_string(1,CAR(temp));
    }
    else
	string_1_qm = Nil;
    temp = CADAR(spec_2);
    slot_name_2 = CAR(temp);
    temp = CADAR(spec_2);
    item_name_2 = CADR(temp);
    item_2_qm = get_instance_with_name_if_any(Qblock,item_name_2);
    vc_spec_2 = CADR(spec_2);
    type_of_spec_2 = CAR(vc_spec_2);
    identifier_2 = CADR(vc_spec_2);
    if (item_2_qm) {
	if (EQ(type_of_spec_2,Qrevision))
	    actual_change_log_entry_2_qm = 
		    change_log_entry_by_revision_qm(item_2_qm,slot_name_2,
		    identifier_2);
	else if (EQ(type_of_spec_2,Qtag))
	    actual_change_log_entry_2_qm = 
		    change_log_entry_by_tag_qm(item_2_qm,slot_name_2,
		    identifier_2);
	else if (EQ(type_of_spec_2,Qtimestamp))
	    actual_change_log_entry_2_qm = 
		    change_log_entry_by_date_qm(item_2_qm,slot_name_2,
		    identifier_2);
	else
	    actual_change_log_entry_2_qm = Qnil;
    }
    else
	actual_change_log_entry_2_qm = Nil;
    if (actual_change_log_entry_2_qm) {
	temp = CDDDDR(actual_change_log_entry_2_qm);
	temp = CDDDDR(temp);
	string_2_qm = convert_text_to_text_string(1,CAR(temp));
    }
    else
	string_2_qm = Nil;
    result_1 = string_1_qm && string_2_qm &&  !TRUEP(diff_error_qm) ? 
	    external_diff_text_strings(string_1_qm,string_2_qm) : 
	    allocate_evaluation_structure(Nil);
    output_text_qm = estructure_slot(result_1,Qdiff_output,Nil);
    error_text_qm = estructure_slot(result_1,Qdiff_error,Nil);
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
	      if (run_invisibly_p);
	      else if (diff_error_qm)
		  tformat(2,string_constant_17,diff_error_qm);
	      else if ( !TRUEP(item_1_qm))
		  tformat(2,string_constant_54,item_name_1);
	      else if ( !TRUEP(actual_change_log_entry_1_qm)) {
		  twrite_symbol(1,item_name_1);
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)29L));
		  twrite_symbol(1,slot_name_1);
		  if (EQ(type_of_spec_1,Qrevision)) {
		      twrite_beginning_of_wide_string(array_constant_6,
			      FIX((SI_Long)15L));
		      twrite_fixnum(identifier_1);
		  }
		  else if (EQ(type_of_spec_1,Qtag)) {
		      twrite_beginning_of_wide_string(array_constant_7,
			      FIX((SI_Long)10L));
		      twrite_symbol(1,identifier_1);
		  }
		  else if (EQ(type_of_spec_1,Qtimestamp)) {
		      twrite_beginning_of_wide_string(array_constant_8,
			      FIX((SI_Long)7L));
		      twrite_frame_edit_timestamp(identifier_1);
		  }
	      }
	      else if ( !TRUEP(item_2_qm))
		  tformat(2,string_constant_54,item_name_2);
	      else if ( !TRUEP(actual_change_log_entry_2_qm)) {
		  twrite_symbol(1,item_name_2);
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)29L));
		  twrite_symbol(1,slot_name_2);
		  if (EQ(type_of_spec_2,Qrevision)) {
		      twrite_beginning_of_wide_string(array_constant_6,
			      FIX((SI_Long)15L));
		      twrite_fixnum(identifier_2);
		  }
		  else if (EQ(type_of_spec_2,Qtag)) {
		      twrite_beginning_of_wide_string(array_constant_7,
			      FIX((SI_Long)10L));
		      twrite_symbol(1,identifier_2);
		  }
		  else if (EQ(type_of_spec_2,Qtimestamp)) {
		      twrite_beginning_of_wide_string(array_constant_8,
			      FIX((SI_Long)7L));
		      twrite_frame_edit_timestamp(identifier_2);
		  }
	      }
	      else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(error_text_qm) != 
		      (SI_Long)0L)
		  twrite_general_string(error_text_qm);
	      error_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    items_to_display = INLINE_UNSIGNED_BYTE_16_VECTOR_P(output_text_qm) != 
	    (SI_Long)0L ? ((SI_Long)0L == 
	    IFIX(text_string_length(error_string)) ? 
	    gensym_cons_1(output_text_qm,Nil) : 
	    gensym_list_2(output_text_qm,error_string)) : 
	    gensym_cons_1(error_string,Nil);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(items_to_display,
		inspect_command);
    else
	return VALUES_1(Nil);
}

/* QUERY-SHOW-CHANGE-LOG-ENTRY */
Object query_show_change_log_entry(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, slot_name, item_name, item_qm, vc_spec, type_of_spec;
    Object identifier, actual_change_log_entry_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object whipped_up_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,100);
    temp = SECOND(query);
    slot_name = CAR(temp);
    temp = SECOND(query);
    item_name = CADR(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
    vc_spec = THIRD(query);
    type_of_spec = CAR(vc_spec);
    identifier = CADR(vc_spec);
    if (item_qm) {
	if (EQ(type_of_spec,Qrevision))
	    actual_change_log_entry_qm = 
		    change_log_entry_by_revision_qm(item_qm,slot_name,
		    identifier);
	else if (EQ(type_of_spec,Qtag))
	    actual_change_log_entry_qm = 
		    change_log_entry_by_tag_qm(item_qm,slot_name,identifier);
	else if (EQ(type_of_spec,Qtimestamp))
	    actual_change_log_entry_qm = 
		    change_log_entry_by_date_qm(item_qm,slot_name,identifier);
	else
	    actual_change_log_entry_qm = Qnil;
    }
    else
	actual_change_log_entry_qm = Nil;
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else if ( !TRUEP(actual_change_log_entry_qm)) {
		  twrite_symbol(1,item_name);
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)29L));
		  twrite_symbol(1,slot_name);
		  if (EQ(type_of_spec,Qrevision)) {
		      twrite_beginning_of_wide_string(array_constant_6,
			      FIX((SI_Long)15L));
		      twrite_fixnum(identifier);
		  }
		  else if (EQ(type_of_spec,Qtag)) {
		      twrite_beginning_of_wide_string(array_constant_7,
			      FIX((SI_Long)10L));
		      twrite_symbol(1,identifier);
		  }
		  else if (EQ(type_of_spec,Qtimestamp)) {
		      twrite_beginning_of_wide_string(array_constant_8,
			      FIX((SI_Long)7L));
		      twrite_frame_edit_timestamp(identifier);
		  }
	      }
	      else
		  twrite_change_log_entry_as_struct(actual_change_log_entry_qm,
			  item_qm);
	      whipped_up_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(whipped_up_string,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object Qno_such_item;       /* no-such-item */

/* QUERY-TAG-CHANGE-LOG-ENTRY */
Object query_tag_change_log_entry(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, slot_name, item_name, item_qm, vc_spec, new_tag;
    Object modified_entry_or_error, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,101);
    temp = CAR(query);
    temp = THIRD(temp);
    slot_name = CAADR(temp);
    temp = CAR(query);
    temp = THIRD(temp);
    item_name = CADADR(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
    vc_spec = fifth(CAR(query));
    if (vc_spec);
    else
	vc_spec = make_default_change_logging_identifier();
    temp = CAR(query);
    temp = FOURTH(temp);
    new_tag = SECOND(temp);
    modified_entry_or_error = item_qm ? tag_change_log_entry(item_qm,
	    slot_name,vc_spec,new_tag) : Qno_such_item;
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else if (EQ(modified_entry_or_error,Qillegal_tag)) {
		  twrite_symbol(2,new_tag,T);
		  twrite_beginning_of_wide_string(array_constant_4,
			  FIX((SI_Long)38L));
	      }
	      else if (EQ(modified_entry_or_error,Qno_such_entry))
		  tformat(2,string_constant_48,vc_spec);
	      else if (EQ(modified_entry_or_error,Qtag_already_used))
		  tformat(3,string_constant_49,new_tag,item_qm);
	      else
		  twrite_change_log_entry_as_struct(modified_entry_or_error,
			  item_qm);
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if ( !TRUEP(FIFTH(CAR(query))))
	reclaim_gensym_list_1(vc_spec);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object array_constant_9;    /* # */

/* QUERY-REVERT-CHANGE-LOG-ENTRY */
Object query_revert_change_log_entry(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, slot_name, item_name, vc_spec, item_qm, found_entry_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,102);
    temp = CAR(query);
    temp = THIRD(temp);
    slot_name = CAR(temp);
    temp = CAR(query);
    temp = THIRD(temp);
    item_name = CADR(temp);
    temp = CAR(query);
    vc_spec = FOURTH(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
    found_entry_qm = item_qm ? revert_change_log_entry(item_qm,slot_name,
	    vc_spec) : Qnil;
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else if ( !TRUEP(found_entry_qm))
		  twrite_beginning_of_wide_string(array_constant_9,
			  FIX((SI_Long)35L));
	      else
		  twrite_change_log_entry_as_struct(found_entry_qm,item_qm);
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

/* QUERY-DELETE-CHANGE-LOG-ENTRY */
Object query_delete_change_log_entry(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, slot_name, item_name, vc_spec, item_qm, found_entry_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,103);
    temp = CAR(query);
    temp = THIRD(temp);
    slot_name = CAADAR(temp);
    temp = CAR(query);
    temp = THIRD(temp);
    temp = CDADAR(temp);
    item_name = CAR(temp);
    temp = CAR(query);
    temp = THIRD(temp);
    vc_spec = CADR(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
    found_entry_qm = item_qm ? get_change_log_entry(item_qm,slot_name,
	    vc_spec) : Qnil;
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else if ( !TRUEP(found_entry_qm))
		  twrite_beginning_of_wide_string(array_constant_9,
			  FIX((SI_Long)35L));
	      else
		  twrite_change_log_entry_as_struct(found_entry_qm,item_qm);
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (found_entry_qm)
	delete_change_log_entry(item_qm,found_entry_qm);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object string_constant_56;  /* "No module named ~s exists." */

static Object array_constant_10;   /* # */

/* QUERY-TAG-ALL-CHANGE-LOG-ENTRIES */
Object query_tag_all_change_log_entries(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, new_tag, vc_spec, module_name, module_exists_p_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,104);
    temp = CAR(query);
    temp = THIRD(temp);
    new_tag = SECOND(temp);
    vc_spec = FIFTH(CAR(query));
    temp = CAR(query);
    temp = FOURTH(temp);
    module_name = SECOND(temp);
    module_exists_p_1 = module_exists_p(module_name);
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(module_exists_p_1))
		  tformat(2,string_constant_56,module_name);
	      else
		  twrite_beginning_of_wide_string(array_constant_10,
			  FIX((SI_Long)14L));
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if ( !TRUEP(FIFTH(CAR(query))))
	vc_spec = make_default_change_logging_identifier();
    tag_all_frames_in_module(module_name,new_tag,vc_spec);
    if ( !TRUEP(FIFTH(CAR(query))))
	reclaim_gensym_list_1(vc_spec);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

/* QUERY-REVERT-ALL-CHANGE-LOG-ENTRIES */
Object query_revert_all_change_log_entries(query,run_invisibly_p,
	    inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, vc_spec, module_name, module_exists_p_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,105);
    temp = CAR(query);
    vc_spec = THIRD(temp);
    temp = CAR(query);
    temp = FOURTH(temp);
    module_name = SECOND(temp);
    module_exists_p_1 = module_exists_p(module_name);
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(module_exists_p_1))
		  tformat(2,string_constant_56,module_name);
	      else
		  twrite_beginning_of_wide_string(array_constant_11,
			  FIX((SI_Long)16L));
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = CAR(query);
    if ( !TRUEP(THIRD(temp)))
	vc_spec = make_default_change_logging_identifier();
    revert_all_frames_in_module(module_name,vc_spec);
    temp = CAR(query);
    if ( !TRUEP(THIRD(temp)))
	reclaim_gensym_list_1(vc_spec);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object string_constant_57;  /* "Enabled change logging on ~s." */

/* QUERY-ENABLE-CHANGE-LOGGING */
Object query_enable_change_logging(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, item_name, item_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,106);
    temp = CAR(query);
    item_name = THIRD(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else
		  tformat(2,string_constant_57,item_name);
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (item_qm)
	set_change_logging_p_on_item(item_qm,T);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object string_constant_58;  /* "Disabled change logging on ~s." */

/* QUERY-DISABLE-CHANGE-LOGGING */
Object query_disable_change_logging(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp, item_name, item_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_for_workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(163,107);
    temp = CAR(query);
    item_name = THIRD(temp);
    item_qm = get_instance_with_name_if_any(Qblock,item_name);
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
	      if (run_invisibly_p);
	      else if ( !TRUEP(item_qm))
		  tformat(2,string_constant_54,item_name);
	      else
		  tformat(2,string_constant_58,item_name);
	      text_for_workspace = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (item_qm)
	set_change_logging_p_on_item(item_qm,Nil);
    if ( !TRUEP(run_invisibly_p))
	return put_up_verson_control_inspect_workspace(gensym_cons_1(text_for_workspace,
		Nil),inspect_command);
    else
	return VALUES_1(Nil);
}

static Object Qshow_logged_changes_on_a_workspace;  /* show-logged-changes-on-a-workspace */

static Object Qshow_change_log_entry_on_a_workspace;  /* show-change-log-entry-on-a-workspace */

static Object Qshow_diffs_on_a_workspace;  /* show-diffs-on-a-workspace */

static Object Qtag_entry;          /* tag-entry */

static Object Qrevert_entry;       /* revert-entry */

static Object Qdelete_entry;       /* delete-entry */

static Object Qtag_every_attribute;  /* tag-every-attribute */

static Object Qrevert_every_attribute;  /* revert-every-attribute */

static Object Qenable_change_logging;  /* enable-change-logging */

static Object Qdisable_change_logging;  /* disable-change-logging */

/* EXECUTE-VERSION-CONTROL-QUERY */
Object execute_version_control_query(query,run_invisibly_p,inspect_command)
    Object query, run_invisibly_p, inspect_command;
{
    Object temp;

    x_note_fn_call(163,108);
    temp = CADAR(query);
    if (EQ(temp,Qshow_logged_changes_on_a_workspace))
	return query_show_logged_changes(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qshow_change_log_entry_on_a_workspace))
	return query_show_change_log_entry(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qshow_diffs_on_a_workspace))
	return query_show_diffs_on_a_workspace(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qtag_entry))
	return query_tag_change_log_entry(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qrevert_entry))
	return query_revert_change_log_entry(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qdelete_entry))
	return query_delete_change_log_entry(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qtag_every_attribute))
	return query_tag_all_change_log_entries(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qrevert_every_attribute))
	return query_revert_all_change_log_entries(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qenable_change_logging))
	return query_enable_change_logging(query,run_invisibly_p,
		inspect_command);
    else if (EQ(temp,Qdisable_change_logging))
	return query_disable_change_logging(query,run_invisibly_p,
		inspect_command);
    else
	return VALUES_1(Nil);
}

/* VERSION-CONTROL-QUERY */
Object version_control_query(inspect_command,run_invisibly_p)
    Object inspect_command, run_invisibly_p;
{
    Object temp;

    x_note_fn_call(163,109);
    temp = ISVREF(inspect_command,(SI_Long)16L);
    return execute_version_control_query(CDAR(temp),run_invisibly_p,
	    inspect_command);
}

void change_log_INIT()
{
    Object com_flush_version_information_for_change_logging_from_table_1;
    Object flush_version_information_for_change_logging_from_table_command_pursuer_1;
    Object flush_version_information_for_change_logging_from_table_command_translator_1;
    Object gensymed_symbol, temp, temp_1, temp_2, com_view_change_log_1;
    Object view_change_log_command_pursuer_1;
    Object view_change_log_command_translator_1;
    Object com_view_change_log_from_table_1;
    Object view_change_log_from_table_command_pursuer_1;
    Object view_change_log_from_table_command_translator_1;
    Object com_flush_change_log_from_table_1;
    Object flush_change_log_from_table_command_pursuer_1;
    Object flush_change_log_from_table_command_translator_1;
    Object com_flush_change_log_for_entire_kb_1;
    Object flush_change_log_for_entire_kb_command_translator_1;
    Object frame_change_log_evaluation_getter_1;
    Object AB_package, list_constant_4, Qg2_is_gpu_enabled;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_enable_change_logging_on_item;
    Object Qg2_disable_change_logging_on_item, Qg2_revert_module;
    Object Qg2_tag_module, Qg2_revert_change_log_entry;
    Object Qg2_get_change_log_entry_comment, Qg2_set_change_log_entry_comment;
    Object Qg2_delete_change_log_entry, Qg2_delete_change_log_tag;
    Object Qg2_tag_change_log_entry, Qg2_diff_change_log_entries;
    Object Qg2_get_change_log_entry, list_constant_29;
    Object Qtype_specification_simple_expansion, list_constant_28;
    Object list_constant_9, Qab_or, Qno_item, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_19, list_constant_18;
    Object list_constant_17, list_constant_6, list_constant_16;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_12, list_constant_11, list_constant_10;
    Object list_constant_7, list_constant_8, Qtext;
    Object Qg2_flush_change_log_for_entire_kb, Qempty_command_pursuer;
    Object string_constant_68, Qg2_flush_change_log_for_item;
    Object Qflush_change_log, string_constant_59, list_constant_2;
    Object string_constant_67, list_constant_5, Qab_class, Qslot_value_writer;
    Object Qwrite_frame_change_log_from_slot;
    Object Qconvert_old_change_logs_to_new_form;
    Object Qadd_change_log_information_to_83b0_kbs, Qg2_text_file_contents;
    Object Qg2_diff_texts, Qg2_delete_files_after_external_diff;
    Object Qg2_set_up_external_diff, Qdefault_windows_diff_options;
    Object array_constant_14, Qdefault_windows_diff_program, array_constant_13;
    Object Qdefault_unix_diff_options, array_constant_12;
    Object Qdefault_unix_diff_program, Qslot_putter;
    Object Qput_enable_kb_change_logging, Ksystem_frame, Qchange_log;
    Object string_constant_66, string_constant_65, list_constant_3;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, Qsystem_table;
    Object Qg2_delete_version_information_entry, Qg2_flush_version_information;
    Object Qflush_version_information;
    Object Qwrite_kb_version_information_for_change_logging_from_slot;
    Object Qput_enable_kb_change_logging_qm;

    x_note_fn_call(163,110);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qenable_kb_change_logging_qm = 
	    STATIC_SYMBOL("ENABLE-KB-CHANGE-LOGGING\?",AB_package);
    Qenable_kb_change_logging = STATIC_SYMBOL("ENABLE-KB-CHANGE-LOGGING",
	    AB_package);
    Qsaving_parameters = STATIC_SYMBOL("SAVING-PARAMETERS",AB_package);
    alias_slot_name(3,Qenable_kb_change_logging_qm,
	    Qenable_kb_change_logging,Qsaving_parameters);
    Qkb_version_information_for_change_logging = 
	    STATIC_SYMBOL("KB-VERSION-INFORMATION-FOR-CHANGE-LOGGING",
	    AB_package);
    Qput_enable_kb_change_logging_qm = 
	    STATIC_SYMBOL("PUT-ENABLE-KB-CHANGE-LOGGING\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_enable_kb_change_logging_qm,
	    STATIC_FUNCTION(put_enable_kb_change_logging_qm,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qenable_kb_change_logging_qm,
	    SYMBOL_FUNCTION(Qput_enable_kb_change_logging_qm),Qslot_putter);
    string_constant = STATIC_STRING("none");
    string_constant_1 = STATIC_STRING(";~%");
    string_constant_2 = STATIC_STRING("Version ~d (");
    string_constant_3 = STATIC_STRING(")");
    Qwrite_kb_version_information_for_change_logging_from_slot = 
	    STATIC_SYMBOL("WRITE-KB-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_kb_version_information_for_change_logging_from_slot,
	    STATIC_FUNCTION(write_kb_version_information_for_change_logging_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qkb_version_information_for_change_logging,
	    SYMBOL_FUNCTION(Qwrite_kb_version_information_for_change_logging_from_slot),
	    Qslot_value_writer);
    Qflush_version_information_for_change_logging_from_table = 
	    STATIC_SYMBOL("FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE",
	    AB_package);
    Qslot_name = STATIC_SYMBOL("SLOT-NAME",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qoriginal_x_in_window = STATIC_SYMBOL("ORIGINAL-X-IN-WINDOW",AB_package);
    Qoriginal_y_in_window = STATIC_SYMBOL("ORIGINAL-Y-IN-WINDOW",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)4L,Qslot_name,Qitem,
	    Qoriginal_x_in_window,Qoriginal_y_in_window);
    string_constant_59 = STATIC_STRING("Flush the change log for this item");
    Qflush_version_information = STATIC_SYMBOL("FLUSH-VERSION-INFORMATION",
	    AB_package);
    make_ui_command(5,
	    Qflush_version_information_for_change_logging_from_table,
	    list_constant_2,string_constant_59,Qflush_version_information,
	    Qnil);
    string_constant_4 = 
	    STATIC_STRING("Flush all version information for this KB\?  Once flushed, this information ~\n        cannot be recovered.");
    Qflush_version_information_for_change_logging_from_table_now = 
	    STATIC_SYMBOL("FLUSH-VERSION-INFORMATION-FOR-CHANGE-LOGGING-FROM-TABLE-NOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qflush_version_information_for_change_logging_from_table_now,
	    STATIC_FUNCTION(flush_version_information_for_change_logging_from_table_now,
	    NIL,FALSE,1,1));
    com_flush_version_information_for_change_logging_from_table_1 = 
	    STATIC_FUNCTION(com_flush_version_information_for_change_logging_from_table,
	    NIL,FALSE,4,4);
    set_ui_command_function(Qflush_version_information_for_change_logging_from_table,
	    com_flush_version_information_for_change_logging_from_table_1);
    flush_version_information_for_change_logging_from_table_command_pursuer_1 
	    = 
	    STATIC_FUNCTION(flush_version_information_for_change_logging_from_table_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qflush_version_information_for_change_logging_from_table,
	    flush_version_information_for_change_logging_from_table_command_pursuer_1);
    flush_version_information_for_change_logging_from_table_command_translator_1 
	    = 
	    STATIC_FUNCTION(flush_version_information_for_change_logging_from_table_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qflush_version_information_for_change_logging_from_table,
	    flush_version_information_for_change_logging_from_table_command_translator_1);
    Qg2_flush_version_information = 
	    STATIC_SYMBOL("G2-FLUSH-VERSION-INFORMATION",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_flush_version_information,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_5 = 
	    STATIC_STRING("~NA must be an instance of saving-parameters.");
    SET_SYMBOL_FUNCTION(Qg2_flush_version_information,
	    STATIC_FUNCTION(g2_flush_version_information,NIL,FALSE,1,1));
    Qg2_delete_version_information_entry = 
	    STATIC_SYMBOL("G2-DELETE-VERSION-INFORMATION-ENTRY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_version_information_entry,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_6 = 
	    STATIC_STRING("~NA does not have any KB version information.");
    string_constant_7 = 
	    STATIC_STRING("~NA is an invalid entry-number for KB version information.");
    string_constant_8 = 
	    STATIC_STRING("~NA is a the current KB version; it cannot be deleted except by flushing the entire attribute.");
    string_constant_9 = 
	    STATIC_STRING("~NA does not exist in the KB version information of ~NA.");
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_delete_version_information_entry,
	    STATIC_FUNCTION(g2_delete_version_information_entry,NIL,FALSE,
	    2,2));
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    Qversion_control_parameters = 
	    STATIC_SYMBOL("VERSION-CONTROL-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_3 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qversion_control_parameters,
	    list_constant_3);
    string_constant_60 = STATIC_STRING("1l1l83ey");
    string_constant_61 = 
	    STATIC_STRING("1q4z8r83KUy83KUy83dvy83dvy00001n1l83Ey1l8l1m8p83Ky000004z8r83bZy83bZy83dvy83dvy00001q1l8l1l83Ey1m8p01l83Uy1l83Hy1l83Ny000004z8r8");
    string_constant_62 = 
	    STATIC_STRING("3bay83bay83dvy83dvy00001q1l8l1l83Ey1m8p01l83Uy1l83Hy1l83Ny000004z8r83XPy83XPy83dvy83dvy00001q1l8l1l83Ey1m8p01l83Uy1l83Hy1l83Ny00");
    string_constant_63 = 
	    STATIC_STRING("0004z8r83Key83Key83dvy83dvy00001q1l8l1l83Ey1m8p01l83Uy1l83Hy1l83Ny000004z8r83IKy83IKy83dvy83dvy00001q1l8l1l83Ey1m8p01l83Uy1l83Hy");
    string_constant_64 = STATIC_STRING("1l83Ny00000");
    string_constant_65 = 
	    STATIC_STRING("1s8q1n83dvy1l83-sy83ey1p83KUy083Ey8l1m8p83Ky1s83bZy08l83Ey1m8p083Uy83Hy83Ny1s83bay08l83Ey1m8p083Uy83Hy83Ny1s83XPy08l83Ey1m8p083U");
    string_constant_66 = 
	    STATIC_STRING("y83Hy83Ny1s83Key08l83Ey1m8p083Uy83Hy83Ny1s83IKy08l83Ey1m8p083Uy83Hy83Ny");
    temp = regenerate_optimized_constant(string_constant_60);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64));
    add_class_to_environment(9,Qversion_control_parameters,list_constant_3,
	    Nil,temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(LIST_2(string_constant_65,
	    string_constant_66)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qversion_control_parameters,
	    Version_control_parameters);
    Qchange_log = STATIC_SYMBOL("CHANGE-LOG",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qversion_control_parameters,Qchange_log,
	    Ksystem_frame,Qnil,Qnil,Qnil,Qt);
    Qput_enable_kb_change_logging = 
	    STATIC_SYMBOL("PUT-ENABLE-KB-CHANGE-LOGGING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_enable_kb_change_logging,
	    STATIC_FUNCTION(put_enable_kb_change_logging,NIL,FALSE,3,3));
    mutate_global_property(Qenable_kb_change_logging,
	    SYMBOL_FUNCTION(Qput_enable_kb_change_logging),Qslot_putter);
    Qdefault_unix_diff_program = STATIC_SYMBOL("DEFAULT-UNIX-DIFF-PROGRAM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_unix_diff_program,
	    Default_unix_diff_program);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_12 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdefault_unix_diff_program,array_constant_12);
    Qdefault_unix_diff_options = STATIC_SYMBOL("DEFAULT-UNIX-DIFF-OPTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_unix_diff_options,
	    Default_unix_diff_options);
    array_constant_13 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdefault_unix_diff_options,array_constant_13);
    Qdefault_windows_diff_program = 
	    STATIC_SYMBOL("DEFAULT-WINDOWS-DIFF-PROGRAM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_windows_diff_program,
	    Default_windows_diff_program);
    array_constant_14 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)92L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)24L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdefault_windows_diff_program,array_constant_14);
    Qdefault_windows_diff_options = 
	    STATIC_SYMBOL("DEFAULT-WINDOWS-DIFF-OPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_windows_diff_options,
	    Default_windows_diff_options);
    array_constant = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_VALUE(Qdefault_windows_diff_options,array_constant);
    Qunix = STATIC_SYMBOL("UNIX",AB_package);
    if (External_diff_program_qm == UNBOUND)
	External_diff_program_qm = get_default_diff_program_qm();
    if (External_diff_options_qm == UNBOUND)
	External_diff_options_qm = get_default_diff_options_qm();
    Qg2_set_up_external_diff = STATIC_SYMBOL("G2-SET-UP-EXTERNAL-DIFF",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_up_external_diff,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qab_pathname = STATIC_SYMBOL("PATHNAME",AB_package);
    Qcommand_line_options = STATIC_SYMBOL("COMMAND-LINE-OPTIONS",AB_package);
    string_constant_10 = STATIC_STRING("diff pathname must be text");
    string_constant_11 = STATIC_STRING("diff options must be text");
    SET_SYMBOL_FUNCTION(Qg2_set_up_external_diff,
	    STATIC_FUNCTION(g2_set_up_external_diff,NIL,FALSE,1,1));
    if (Delete_files_after_external_diff_p == UNBOUND)
	Delete_files_after_external_diff_p = T;
    Qg2_delete_files_after_external_diff = 
	    STATIC_SYMBOL("G2-DELETE-FILES-AFTER-EXTERNAL-DIFF",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_files_after_external_diff,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_delete_files_after_external_diff,
	    STATIC_FUNCTION(g2_delete_files_after_external_diff,NIL,FALSE,
	    1,1));
    string_constant_12 = STATIC_STRING("~A ~A ~A ~A > ~A 2> ~A");
    Qtemp_file_1 = STATIC_SYMBOL("TEMP-FILE-1",AB_package);
    Qtemp_file_2 = STATIC_SYMBOL("TEMP-FILE-2",AB_package);
    Qoutput_filename = STATIC_SYMBOL("OUTPUT-FILENAME",AB_package);
    Qcommand_line = STATIC_SYMBOL("COMMAND-LINE",AB_package);
    Qerror_filename = STATIC_SYMBOL("ERROR-FILENAME",AB_package);
    string_constant_13 = STATIC_STRING("fo");
    string_constant_14 = STATIC_STRING("ft");
    string_constant_15 = STATIC_STRING("output");
    string_constant_16 = STATIC_STRING("error");
    Qno_diff_found = STATIC_SYMBOL("NO-DIFF-FOUND",AB_package);
    Qcan_not_execute = STATIC_SYMBOL("CAN-NOT-EXECUTE",AB_package);
    Qcan_not_make_generate_temp_filenames = 
	    STATIC_SYMBOL("CAN-NOT-MAKE-GENERATE-TEMP-FILENAMES",AB_package);
    Qcan_not_generate_command_line = 
	    STATIC_SYMBOL("CAN-NOT-GENERATE-COMMAND-LINE",AB_package);
    Qdiff_output = STATIC_SYMBOL("DIFF-OUTPUT",AB_package);
    Qdiff_error = STATIC_SYMBOL("DIFF-ERROR",AB_package);
    Qg2_diff_texts = STATIC_SYMBOL("G2-DIFF-TEXTS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_diff_texts,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_17 = STATIC_STRING("Unable to execute external diff: ~s");
    SET_SYMBOL_FUNCTION(Qg2_diff_texts,STATIC_FUNCTION(g2_diff_texts,NIL,
	    FALSE,2,2));
    Qg2_text_file_contents = STATIC_SYMBOL("G2-TEXT-FILE-CONTENTS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_text_file_contents,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_text_file_contents,
	    STATIC_FUNCTION(g2_text_file_contents,NIL,FALSE,1,1));
    Qframe_change_log = STATIC_SYMBOL("FRAME-CHANGE-LOG",AB_package);
    Qchange_log_information = STATIC_SYMBOL("CHANGE-LOG-INFORMATION",
	    AB_package);
    Qadd_change_log_information_to_83b0_kbs = 
	    STATIC_SYMBOL("ADD-CHANGE-LOG-INFORMATION-TO-83B0-KBS",AB_package);
    temp_2 = adjoin(2,Qadd_change_log_information_to_83b0_kbs,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qadd_change_log_information_to_83b0_kbs,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qadd_change_log_information_to_83b0_kbs,
	    STATIC_FUNCTION(add_change_log_information_to_83b0_kbs,NIL,
	    FALSE,0,0));
    Qpermanent = STATIC_SYMBOL("PERMANENT",AB_package);
    Qfull_text = STATIC_SYMBOL("FULL-TEXT",AB_package);
    Qpost_load = STATIC_SYMBOL("POST-LOAD",AB_package);
    Qconvert_old_change_logs_to_new_form = 
	    STATIC_SYMBOL("CONVERT-OLD-CHANGE-LOGS-TO-NEW-FORM",AB_package);
    temp_2 = adjoin(2,Qconvert_old_change_logs_to_new_form,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qconvert_old_change_logs_to_new_form,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qconvert_old_change_logs_to_new_form,
	    STATIC_FUNCTION(convert_old_change_logs_to_new_form,NIL,FALSE,
	    0,0));
    array_constant_1 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    string_constant_18 = STATIC_STRING("~d~a~a");
    array_constant_3 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qwrite_frame_change_log_from_slot = 
	    STATIC_SYMBOL("WRITE-FRAME-CHANGE-LOG-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_frame_change_log_from_slot,
	    STATIC_FUNCTION(write_frame_change_log_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qframe_change_log,
	    SYMBOL_FUNCTION(Qwrite_frame_change_log_from_slot),
	    Qslot_value_writer);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    string_constant_19 = STATIC_STRING("Attribute");
    string_constant_20 = STATIC_STRING("Revision");
    string_constant_21 = STATIC_STRING("Value");
    string_constant_22 = STATIC_STRING("Module Version");
    string_constant_23 = STATIC_STRING("Timestamp");
    string_constant_24 = STATIC_STRING("Author");
    string_constant_25 = STATIC_STRING("Tags");
    string_constant_26 = STATIC_STRING("~d");
    string_constant_27 = STATIC_STRING("(unknown)");
    string_constant_28 = STATIC_STRING("~a");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_29 = STATIC_STRING("~(~a~)");
    string_constant_30 = STATIC_STRING("~L,&");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant = STATIC_CONS(Qab_class,Qnil);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qview_change_log = STATIC_SYMBOL("VIEW-CHANGE-LOG",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qitem,Qoriginal_x_in_window,
	    Qoriginal_y_in_window);
    string_constant_67 = STATIC_STRING("View the change log for this item");
    make_ui_command(5,Qview_change_log,list_constant_5,string_constant_67,
	    Qview_change_log,Qnil);
    com_view_change_log_1 = STATIC_FUNCTION(com_view_change_log,NIL,FALSE,3,3);
    set_ui_command_function(Qview_change_log,com_view_change_log_1);
    view_change_log_command_pursuer_1 = 
	    STATIC_FUNCTION(view_change_log_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qview_change_log,view_change_log_command_pursuer_1);
    view_change_log_command_translator_1 = 
	    STATIC_FUNCTION(view_change_log_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qview_change_log,
	    view_change_log_command_translator_1);
    Qview_change_log_from_table = 
	    STATIC_SYMBOL("VIEW-CHANGE-LOG-FROM-TABLE",AB_package);
    make_ui_command(5,Qview_change_log_from_table,list_constant_2,
	    string_constant_67,Qview_change_log,Qnil);
    com_view_change_log_from_table_1 = 
	    STATIC_FUNCTION(com_view_change_log_from_table,NIL,FALSE,4,4);
    set_ui_command_function(Qview_change_log_from_table,
	    com_view_change_log_from_table_1);
    view_change_log_from_table_command_pursuer_1 = 
	    STATIC_FUNCTION(view_change_log_from_table_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qview_change_log_from_table,
	    view_change_log_from_table_command_pursuer_1);
    view_change_log_from_table_command_translator_1 = 
	    STATIC_FUNCTION(view_change_log_from_table_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qview_change_log_from_table,
	    view_change_log_from_table_command_translator_1);
    Qflush_change_log_from_table = 
	    STATIC_SYMBOL("FLUSH-CHANGE-LOG-FROM-TABLE",AB_package);
    Qflush_change_log = STATIC_SYMBOL("FLUSH-CHANGE-LOG",AB_package);
    make_ui_command(5,Qflush_change_log_from_table,list_constant_2,
	    string_constant_59,Qflush_change_log,Qnil);
    string_constant_31 = STATIC_STRING("Flush the change log for this item\?");
    Qflush_change_log_for_item_now = 
	    STATIC_SYMBOL("FLUSH-CHANGE-LOG-FOR-ITEM-NOW",AB_package);
    SET_SYMBOL_FUNCTION(Qflush_change_log_for_item_now,
	    STATIC_FUNCTION(flush_change_log_for_item_now,NIL,FALSE,1,1));
    com_flush_change_log_from_table_1 = 
	    STATIC_FUNCTION(com_flush_change_log_from_table,NIL,FALSE,4,4);
    set_ui_command_function(Qflush_change_log_from_table,
	    com_flush_change_log_from_table_1);
    flush_change_log_from_table_command_pursuer_1 = 
	    STATIC_FUNCTION(flush_change_log_from_table_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qflush_change_log_from_table,
	    flush_change_log_from_table_command_pursuer_1);
    flush_change_log_from_table_command_translator_1 = 
	    STATIC_FUNCTION(flush_change_log_from_table_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qflush_change_log_from_table,
	    flush_change_log_from_table_command_translator_1);
    Qg2_flush_change_log_for_item = 
	    STATIC_SYMBOL("G2-FLUSH-CHANGE-LOG-FOR-ITEM",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_flush_change_log_for_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_flush_change_log_for_item,
	    STATIC_FUNCTION(g2_flush_change_log_for_item,NIL,FALSE,1,1));
    Qflush_change_log_for_entire_kb = 
	    STATIC_SYMBOL("FLUSH-CHANGE-LOG-FOR-ENTIRE-KB",AB_package);
    string_constant_68 = 
	    STATIC_STRING("Flush the change log for every item in the KB (includes all modules).");
    make_ui_command(5,Qflush_change_log_for_entire_kb,Qnil,
	    string_constant_68,Qflush_change_log_for_entire_kb,Qnil);
    string_constant_32 = 
	    STATIC_STRING("Flush the change log for the entire KB\?");
    Qflush_change_log_for_entire_kb_now = 
	    STATIC_SYMBOL("FLUSH-CHANGE-LOG-FOR-ENTIRE-KB-NOW",AB_package);
    SET_SYMBOL_FUNCTION(Qflush_change_log_for_entire_kb_now,
	    STATIC_FUNCTION(flush_change_log_for_entire_kb_now,NIL,FALSE,0,0));
    com_flush_change_log_for_entire_kb_1 = 
	    STATIC_FUNCTION(com_flush_change_log_for_entire_kb,NIL,FALSE,0,0);
    set_ui_command_function(Qflush_change_log_for_entire_kb,
	    com_flush_change_log_for_entire_kb_1);
    Qempty_command_pursuer = STATIC_SYMBOL("EMPTY-COMMAND-PURSUER",AB_package);
    SET_SYMBOL_FUNCTION(Qempty_command_pursuer,
	    STATIC_FUNCTION(empty_command_pursuer,NIL,FALSE,1,1));
    set_ui_command_pursuer(Qflush_change_log_for_entire_kb,
	    Qempty_command_pursuer);
    flush_change_log_for_entire_kb_command_translator_1 = 
	    STATIC_FUNCTION(flush_change_log_for_entire_kb_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qflush_change_log_for_entire_kb,
	    flush_change_log_for_entire_kb_command_translator_1);
    Qg2_flush_change_log_for_entire_kb = 
	    STATIC_SYMBOL("G2-FLUSH-CHANGE-LOG-FOR-ENTIRE-KB",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_flush_change_log_for_entire_kb,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_flush_change_log_for_entire_kb,
	    STATIC_FUNCTION(g2_flush_change_log_for_entire_kb,NIL,FALSE,0,0));
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_6 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_17 = STATIC_CONS(Qattribute,list_constant_6);
    Qrevision = STATIC_SYMBOL("REVISION",AB_package);
    list_constant_7 = STATIC_CONS(Qinteger,Qnil);
    list_constant_18 = STATIC_CONS(Qrevision,list_constant_7);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_8 = STATIC_CONS(Qtext,Qnil);
    list_constant_19 = STATIC_CONS(Qcomment,list_constant_8);
    Qtags = STATIC_SYMBOL("TAGS",AB_package);
    list_constant_9 = STATIC_CONS(Qsequence,Qnil);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qtags,list_constant_9);
    Qtext_value = STATIC_SYMBOL("TEXT-VALUE",AB_package);
    list_constant_21 = STATIC_CONS(Qtext_value,list_constant_8);
    Qmodule_version = STATIC_SYMBOL("MODULE-VERSION",AB_package);
    list_constant_22 = STATIC_CONS(Qmodule_version,list_constant_7);
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qyear = STATIC_SYMBOL("YEAR",AB_package);
    list_constant_10 = STATIC_CONS(Qyear,list_constant_7);
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    list_constant_11 = STATIC_CONS(Qmonth,list_constant_7);
    Qdate = STATIC_SYMBOL("DATE",AB_package);
    list_constant_12 = STATIC_CONS(Qdate,list_constant_7);
    Qhours = STATIC_SYMBOL("HOURS",AB_package);
    list_constant_13 = STATIC_CONS(Qhours,list_constant_7);
    Qminutes = STATIC_SYMBOL("MINUTES",AB_package);
    list_constant_14 = STATIC_CONS(Qminutes,list_constant_7);
    list_constant_15 = STATIC_LIST((SI_Long)5L,list_constant_10,
	    list_constant_11,list_constant_12,list_constant_13,
	    list_constant_14);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_15);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qtimestamp,list_constant_16);
    Qauthor = STATIC_SYMBOL("AUTHOR",AB_package);
    list_constant_24 = STATIC_CONS(Qauthor,list_constant_6);
    list_constant_25 = STATIC_LIST((SI_Long)8L,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_25);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_26);
    Change_log_type = list_constant_27;
    string_constant_33 = STATIC_STRING("");
    string_constant_34 = STATIC_STRING("~A::~A");
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_28 = STATIC_CONS(Qno_item,Qnil);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_9,
	    list_constant_28);
    set_property_value_function(get_symbol_properties_function(Qframe_change_log),
	    Qtype_specification_simple_expansion,list_constant_29);
    define_type_specification_explicit_complex_type(Qframe_change_log,
	    list_constant_29);
    frame_change_log_evaluation_getter_1 = 
	    STATIC_FUNCTION(frame_change_log_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qframe_change_log,
	    frame_change_log_evaluation_getter_1);
    Qtag = STATIC_SYMBOL("TAG",AB_package);
    list_constant_1 = STATIC_CONS(Qnone,Qnil);
    Qillegal_tag = STATIC_SYMBOL("ILLEGAL-TAG",AB_package);
    Qno_such_entry = STATIC_SYMBOL("NO-SUCH-ENTRY",AB_package);
    Qtag_already_used = STATIC_SYMBOL("TAG-ALREADY-USED",AB_package);
    string_constant_35 = STATIC_STRING("Timestamp must be structure.");
    string_constant_36 = 
	    STATIC_STRING("Minutes must be integer between 0 and 59, inclusive.");
    string_constant_37 = 
	    STATIC_STRING("Hours must be integer between 0 and 23, inclusive.");
    string_constant_38 = 
	    STATIC_STRING("Month must be integer between 1 and 12, inclusive.");
    string_constant_39 = 
	    STATIC_STRING("Year must be integer between 1970 and 2038, inclusive.");
    string_constant_40 = 
	    STATIC_STRING("Date must make sense for given month and year.");
    string_constant_41 = 
	    STATIC_STRING("Must supply revision, tag, or timestamp.");
    string_constant_42 = STATIC_STRING("Cannot supply both revision and tag.");
    string_constant_43 = 
	    STATIC_STRING("Cannot supply both revision and timestamp.");
    string_constant_44 = 
	    STATIC_STRING("Cannot supply both tag and timestamp.");
    string_constant_45 = STATIC_STRING("Revision must be integer.");
    string_constant_46 = STATIC_STRING("Tag must be symbol.");
    string_constant_47 = STATIC_STRING("Cannot parse timestamp.");
    Qg2_get_change_log_entry = STATIC_SYMBOL("G2-GET-CHANGE-LOG-ENTRY",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_change_log_entry,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_change_log_entry,
	    STATIC_FUNCTION(g2_get_change_log_entry,NIL,FALSE,3,3));
    Qg2_diff_change_log_entries = 
	    STATIC_SYMBOL("G2-DIFF-CHANGE-LOG-ENTRIES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_diff_change_log_entries,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_48 = STATIC_STRING("No change-log entry found for ~NA.");
    SET_SYMBOL_FUNCTION(Qg2_diff_change_log_entries,
	    STATIC_FUNCTION(g2_diff_change_log_entries,NIL,FALSE,4,4));
    Qg2_tag_change_log_entry = STATIC_SYMBOL("G2-TAG-CHANGE-LOG-ENTRY",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tag_change_log_entry,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)57344L);
    string_constant_49 = STATIC_STRING("Tag ~s is already in use on ~NF.");
    SET_SYMBOL_FUNCTION(Qg2_tag_change_log_entry,
	    STATIC_FUNCTION(g2_tag_change_log_entry,NIL,FALSE,4,4));
    Qg2_delete_change_log_tag = STATIC_SYMBOL("G2-DELETE-CHANGE-LOG-TAG",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_change_log_tag,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_50 = 
	    STATIC_STRING("No change-log entry found with tag ~NA.");
    SET_SYMBOL_FUNCTION(Qg2_delete_change_log_tag,
	    STATIC_FUNCTION(g2_delete_change_log_tag,NIL,FALSE,3,3));
    Qg2_delete_change_log_entry = 
	    STATIC_SYMBOL("G2-DELETE-CHANGE-LOG-ENTRY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_change_log_entry,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_delete_change_log_entry,
	    STATIC_FUNCTION(g2_delete_change_log_entry,NIL,FALSE,3,3));
    Qg2_set_change_log_entry_comment = 
	    STATIC_SYMBOL("G2-SET-CHANGE-LOG-ENTRY-COMMENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_change_log_entry_comment,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_51 = STATIC_STRING("No change-log entry found.");
    SET_SYMBOL_FUNCTION(Qg2_set_change_log_entry_comment,
	    STATIC_FUNCTION(g2_set_change_log_entry_comment,NIL,FALSE,4,4));
    Qg2_get_change_log_entry_comment = 
	    STATIC_SYMBOL("G2-GET-CHANGE-LOG-ENTRY-COMMENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_change_log_entry_comment,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_change_log_entry_comment,
	    STATIC_FUNCTION(g2_get_change_log_entry_comment,NIL,FALSE,3,3));
    Qg2_revert_change_log_entry = 
	    STATIC_SYMBOL("G2-REVERT-CHANGE-LOG-ENTRY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_revert_change_log_entry,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_52 = STATIC_STRING("No matching change-log entry found.");
    SET_SYMBOL_FUNCTION(Qg2_revert_change_log_entry,
	    STATIC_FUNCTION(g2_revert_change_log_entry,NIL,FALSE,3,3));
    Qg2_tag_module = STATIC_SYMBOL("G2-TAG-MODULE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tag_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_tag_module,STATIC_FUNCTION(g2_tag_module,NIL,
	    FALSE,3,3));
    Qg2_revert_module = STATIC_SYMBOL("G2-REVERT-MODULE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_revert_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_revert_module,STATIC_FUNCTION(g2_revert_module,
	    NIL,FALSE,2,2));
    Qg2_disable_change_logging_on_item = 
	    STATIC_SYMBOL("G2-DISABLE-CHANGE-LOGGING-ON-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_disable_change_logging_on_item,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_disable_change_logging_on_item,
	    STATIC_FUNCTION(g2_disable_change_logging_on_item,NIL,FALSE,1,1));
    Qg2_enable_change_logging_on_item = 
	    STATIC_SYMBOL("G2-ENABLE-CHANGE-LOGGING-ON-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_enable_change_logging_on_item,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_enable_change_logging_on_item,
	    STATIC_FUNCTION(g2_enable_change_logging_on_item,NIL,FALSE,1,1));
    Qg2_is_gpu_enabled = STATIC_SYMBOL("G2-IS-GPU-ENABLED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_is_gpu_enabled,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_is_gpu_enabled,
	    STATIC_FUNCTION(g2_is_gpu_enabled,NIL,FALSE,0,0));
    string_constant_53 = STATIC_STRING("~NA");
    string_constant_54 = STATIC_STRING("No item named ~s exists.");
    string_constant_55 = STATIC_STRING("~s has no change-log.");
    array_constant_5 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qno_such_item = STATIC_SYMBOL("NO-SUCH-ITEM",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)39L,(SI_Long)57344L);
    string_constant_56 = STATIC_STRING("No module named ~s exists.");
    array_constant_10 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_4,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)57344L);
    string_constant_57 = STATIC_STRING("Enabled change logging on ~s.");
    string_constant_58 = STATIC_STRING("Disabled change logging on ~s.");
    Qshow_logged_changes_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-LOGGED-CHANGES-ON-A-WORKSPACE",AB_package);
    Qshow_change_log_entry_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-CHANGE-LOG-ENTRY-ON-A-WORKSPACE",AB_package);
    Qshow_diffs_on_a_workspace = STATIC_SYMBOL("SHOW-DIFFS-ON-A-WORKSPACE",
	    AB_package);
    Qtag_entry = STATIC_SYMBOL("TAG-ENTRY",AB_package);
    Qrevert_entry = STATIC_SYMBOL("REVERT-ENTRY",AB_package);
    Qdelete_entry = STATIC_SYMBOL("DELETE-ENTRY",AB_package);
    Qtag_every_attribute = STATIC_SYMBOL("TAG-EVERY-ATTRIBUTE",AB_package);
    Qrevert_every_attribute = STATIC_SYMBOL("REVERT-EVERY-ATTRIBUTE",
	    AB_package);
    Qenable_change_logging = STATIC_SYMBOL("ENABLE-CHANGE-LOGGING",AB_package);
    Qdisable_change_logging = STATIC_SYMBOL("DISABLE-CHANGE-LOGGING",
	    AB_package);
}
