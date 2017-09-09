/* nwtbls.c
 * Input file:  new-tables.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "nwtbls.h"


DEFINE_VARIABLE_WITH_SYMBOL(Working_on_new_table, Qworking_on_new_table);

DEFINE_VARIABLE_WITH_SYMBOL(Editing_new_table, Qediting_new_table);

DEFINE_VARIABLE_WITH_SYMBOL(Current_new_table, Qcurrent_new_table);

DEFINE_VARIABLE_WITH_SYMBOL(Current_cell, Qcurrent_cell);

DEFINE_VARIABLE_WITH_SYMBOL(Current_row, Qcurrent_row);

DEFINE_VARIABLE_WITH_SYMBOL(Current_column, Qcurrent_column);

/* TABLE-DIMENSION-P */
Object table_dimension_p(x)
    Object x;
{
    x_note_fn_call(178,0);
    return num_ltn(3,FIX((SI_Long)0L),x,FIX((SI_Long)101L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Row_maximum, Qrow_maximum);

/* ENTER-PART-FEATURE-ROW-MAXIMUM */
Object enter_part_feature_row_maximum(new_value)
    Object new_value;
{
    x_note_fn_call(178,1);
    Part_feature_recall_stack = part_stack_cons_1(Row_maximum,
	    Part_feature_recall_stack);
    Row_maximum = new_value;
    return VALUES_1(Nil);
}

static Object Qpart_stack;         /* part-stack */

/* EXIT-PART-FEATURE-ROW-MAXIMUM */
Object exit_part_feature_row_maximum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,2);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Row_maximum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Column_maximum, Qcolumn_maximum);

/* ENTER-PART-FEATURE-COLUMN-MAXIMUM */
Object enter_part_feature_column_maximum(new_value)
    Object new_value;
{
    x_note_fn_call(178,3);
    Part_feature_recall_stack = part_stack_cons_1(Column_maximum,
	    Part_feature_recall_stack);
    Column_maximum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-COLUMN-MAXIMUM */
Object exit_part_feature_column_maximum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,4);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Column_maximum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cell_contents, Qcell_contents);

/* ENTER-PART-FEATURE-CELL-CONTENTS */
Object enter_part_feature_cell_contents(new_value)
    Object new_value;
{
    x_note_fn_call(178,5);
    Part_feature_recall_stack = part_stack_cons_1(Cell_contents,
	    Part_feature_recall_stack);
    Cell_contents = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CELL-CONTENTS */
Object exit_part_feature_cell_contents()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,6);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Cell_contents = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Text_value, Qtext_value);

/* ENTER-PART-FEATURE-TEXT-VALUE */
Object enter_part_feature_text_value(new_value)
    Object new_value;
{
    x_note_fn_call(178,7);
    Part_feature_recall_stack = part_stack_cons_1(Text_value,
	    Part_feature_recall_stack);
    Text_value = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-TEXT-VALUE */
Object exit_part_feature_text_value()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,8);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Text_value = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Column_width, Qcolumn_width);

/* ENTER-PART-FEATURE-COLUMN-WIDTH */
Object enter_part_feature_column_width(new_value)
    Object new_value;
{
    x_note_fn_call(178,9);
    Part_feature_recall_stack = part_stack_cons_1(Column_width,
	    Part_feature_recall_stack);
    Column_width = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-COLUMN-WIDTH */
Object exit_part_feature_column_width()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,10);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Column_width = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* ENTER-PART-FEATURE-ROW-HEIGHT */
Object enter_part_feature_row_height(new_value)
    Object new_value;
{
    x_note_fn_call(178,11);
    Part_feature_recall_stack = part_stack_cons_1(Row_height,
	    Part_feature_recall_stack);
    Row_height = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-ROW-HEIGHT */
Object exit_part_feature_row_height()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(178,12);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Row_height = part_stack_pop_store;
    return VALUES_1(Nil);
}

static Object Qwidth;              /* width */

static Object string_constant;     /* "The width of individual cells can not be modified but you can change the default for the entire table." */

static Object Qheight;             /* height */

static Object string_constant_1;   /* "The height of individual cells can not be modified but you can change the default for the entire table." */

/* SEMANTIC-CHECK-CELL-PART-TYPE */
Object semantic_check_cell_part_type(cell_description)
    Object cell_description;
{
    Object frame, symbol, gensymed_symbol, sub_class_bit_vector;
    Object this_is_the_table_wide_default_cell_description_p;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(178,13);
    frame = ISVREF(Current_edit_state,(SI_Long)3L);
    symbol = Qnew_table;
    gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
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
	    this_is_the_table_wide_default_cell_description_p = 
		    (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	}
	else
	    this_is_the_table_wide_default_cell_description_p = Nil;
    }
    else
	this_is_the_table_wide_default_cell_description_p = Nil;
    if ( !TRUEP(this_is_the_table_wide_default_cell_description_p) && 
	    part_has_feature_p(cell_description,Qwidth))
	return copy_text_string(string_constant);
    else if ( !TRUEP(this_is_the_table_wide_default_cell_description_p) && 
	    part_has_feature_p(cell_description,Qheight))
	return copy_text_string(string_constant_1);
    else
	return VALUES_1(Qnil);
}

/* CELL-ANNOTATIONS-FOR-CLASS */
Object cell_annotations_for_class(block)
    Object block;
{
    x_note_fn_call(178,14);
    return VALUES_1(ISVREF(block,(SI_Long)18L));
}

static Object Qdefault_cell_format;  /* default-cell-format */

static Object Qannotation;         /* annotation */

/* PUT-DEFAULT-CELL-FORMAT */
Object put_default_cell_format(new_table,cell_format_or_none,gensymed_symbol)
    Object new_table, cell_format_or_none, gensymed_symbol;
{
    Object current_annotated_frame, svref_arg_1, projection_focus_method;
    Object projection_focus_annotation, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(4);
    Object result;

    x_note_fn_call(178,15);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,3);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_annotated_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  2);
	    if (Loading_kb_p) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,Qdefault_cell_format);
		svref_arg_1 = New_table;
		SAVE_VALUES(VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)19L)) 
			= cell_format_or_none));
	    }
	    else {
		LOCK(Working_on_new_table);
		if (PUSH_UNWIND_PROTECT(0)) {
		    erase_part_of_block(New_table,ISVREF(New_table,
			    (SI_Long)19L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(New_table,Qdefault_cell_format);
		    svref_arg_1 = New_table;
		    SVREF(svref_arg_1,FIX((SI_Long)19L)) = cell_format_or_none;
		    update_new_table_size();
		    projection_focus_method = Qannotation;
		    projection_focus_annotation = cell_format_or_none;
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_annotation,Qprojection_focus_annotation,projection_focus_annotation,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
			      0);
			gensymed_symbol = 
				ISVREF(ISVREF(ISVREF(ISVREF(Current_annotated_frame,
				(SI_Long)1L),(SI_Long)11L),(SI_Long)46L),
				(SI_Long)1L);
			gensymed_symbol_1 = Current_annotated_frame;
			gensymed_symbol_2 = Qannotation;
			gensymed_symbol_3 = cell_format_or_none;
			inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
				gensymed_symbol_2,gensymed_symbol_3);
		      POP_SPECIAL();
		    POP_SPECIAL();
		    SAVE_VALUES(redraw_part_of_block(ISVREF(New_table,
			    (SI_Long)19L)));
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Working_on_new_table);
		CONTINUE_UNWINDING(0);
	    }
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qdefault_evaluation_setting;  /* default-evaluation-setting */

/* PUT-DEFAULT-EVALUATION-SETTING */
Object put_default_evaluation_setting(new_table,computation_style_or_none,
	    initializing_qm)
    Object new_table, computation_style_or_none, initializing_qm;
{
    Object svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,16);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(New_table,Qdefault_evaluation_setting);
      svref_arg_1 = New_table;
      SVREF(svref_arg_1,FIX((SI_Long)20L)) = computation_style_or_none;
      if ( !TRUEP(initializing_qm))
	  recompile_item(New_table);
      result = VALUES_1(computation_style_or_none);
    POP_SPECIAL();
    return result;
}

static Object list_constant;       /* # */

/* WRITE-TABLE-DIMENSIONS-FROM-SLOT */
Object write_table_dimensions_from_slot(cell_annotations,gensymed_symbol)
    Object cell_annotations, gensymed_symbol;
{
    x_note_fn_call(178,17);
    return write_part_description(2,cell_annotations,list_constant);
}

static Object Qtable_dimensions;   /* table-dimensions */

/* COMPILE-TABLE-DIMENSIONS-FOR-SLOT */
Object compile_table_dimensions_for_slot varargs_1(int, n)
{
    Object table_dimensions_parse, freeform_table, gensymed_symbol;
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_annotated_frame, current_computation_style;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(178,18);
    INIT_ARGS_nonrelocating();
    table_dimensions_parse = REQUIRED_ARG_nonrelocating();
    freeform_table = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    result_1 = Nil;
    error_message_qm = Nil;
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_annotated_frame = freeform_table;
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  0);
	    result = compile_part_description(table_dimensions_parse,
		    Qnew_table);
	    MVS_2(result,result_1,error_message_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(0);
    if (result_1)
	M_FIRST(result_1) = Qtable_dimensions;
    result = VALUES_2(result_1,error_message_qm);
    RESTORE_STACK();
    return result;
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qset_simple_part_feature;  /* set-simple-part-feature */

static Object Qcopy_for_slot_value;  /* copy-for-slot-value */

static Object Qnumber_of_rows;     /* number-of-rows */

static Object Qsc;                 /* \; */

static Object Qnumber_of_columns;  /* number-of-columns */

/* TABLE-DIMENSIONS-EVALUATION-SETTER */
Object table_dimensions_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(178,19);
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
			  list_constant_1))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_2,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_table_dimensions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = phrase_list_2(Qquote,Qrow_maximum);
    temp = phrase_list_4(Qset_simple_part_feature,
	    Qcurrent_part_description,temp_1,
	    phrase_list_2(Qcopy_for_slot_value,phrase_list_2(Qquote,
	    estructure_slot(gensymed_symbol,Qnumber_of_rows,Nil))));
    temp_1 = phrase_list_2(Qquote,Qcolumn_maximum);
    result = phrase_cons(Qsc,phrase_list_2(temp,
	    phrase_list_4(Qset_simple_part_feature,
	    Qcurrent_part_description,temp_1,
	    phrase_list_2(Qcopy_for_slot_value,phrase_list_2(Qquote,
	    estructure_slot(gensymed_symbol,Qnumber_of_columns,Nil))))));
  end_table_dimensions_evaluation_setter:
    return result;
}

/* TABLE-DIMENSIONS-EVALUATION-GETTER */
Object table_dimensions_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(178,20);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qnumber_of_columns,
	    get_simple_part_feature(slot_value,Qcolumn_maximum));
    set_evaluation_structure_slot(gensymed_symbol,Qnumber_of_rows,
	    get_simple_part_feature(slot_value,Qrow_maximum));
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qcell_annotations;   /* cell-annotations */

static Object Qadd_row;            /* add-row */

static Object Qdelete_row;         /* delete-row */

static Object Qadd_column;         /* add-column */

static Object Qdelete_column;      /* delete-column */

/* PUT-CELL-ANNOTATIONS */
Object put_cell_annotations(freeform_table,new_cell_annotations,
	    initializing_qm)
    Object freeform_table, new_cell_annotations, initializing_qm;
{
    Object current_annotated_frame, current_block_of_dependent_frame;
    Object new_row_maximum, new_column_maximum, old_cell_annotations;
    Object old_row_maximum, old_column_maximum, row_delta, column_delta;
    Object row_index, column_index, temp, edit_action, count_1, temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(178,21);
    SAVE_STACK();
    if ( !EQ(Qtable_dimensions,FIRST(new_cell_annotations))) {
	if ( !TRUEP(initializing_qm)) {
	    LOCK(Working_on_annotated_frame);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_annotated_frame = freeform_table;
		PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			0);
		  reclaim_part_description(ISVREF(freeform_table,
			  (SI_Long)18L));
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Working_on_annotated_frame);
	    CONTINUE_UNWINDING(0);
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(freeform_table,Qcell_annotations);
	result = VALUES_2(SVREF(freeform_table,FIX((SI_Long)18L)) = 
		new_cell_annotations,T);
	RESTORE_STACK();
	return result;
    }
    else {
	LOCK(Working_on_annotated_frame);
	if (PUSH_UNWIND_PROTECT(1)) {
	    current_annotated_frame = freeform_table;
	    current_block_of_dependent_frame = freeform_table;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		      0);
		LOCK(Working_on_new_table);
		if (PUSH_UNWIND_PROTECT(0)) {
		    new_row_maximum = 
			    get_simple_part_feature(new_cell_annotations,
			    Qrow_maximum);
		    new_column_maximum = 
			    get_simple_part_feature(new_cell_annotations,
			    Qcolumn_maximum);
		    old_cell_annotations = ISVREF(freeform_table,(SI_Long)18L);
		    old_row_maximum = 
			    get_simple_part_feature(old_cell_annotations,
			    Qrow_maximum);
		    old_column_maximum = 
			    get_simple_part_feature(old_cell_annotations,
			    Qcolumn_maximum);
		    row_delta = minus(new_row_maximum,old_row_maximum);
		    column_delta = minus(new_column_maximum,
			    old_column_maximum);
		    row_index = old_row_maximum;
		    column_index = old_column_maximum;
		    reclaim_slot_value(new_cell_annotations);
		    if ((SI_Long)0L < IFIX(row_delta))
			result = VALUES_3(Qadd_row,row_delta,FIX((SI_Long)0L));
		    else if ((SI_Long)0L > IFIX(row_delta)) {
			row_index = new_row_maximum;
			temp = FIXNUM_NEGATE(row_delta);
			result = VALUES_2(Qdelete_row,temp);
		    }
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,edit_action,count_1);
		    if (edit_action)
			table_block_insert_or_delete(freeform_table,
				row_index,column_index,edit_action,count_1);
		    if ((SI_Long)0L < IFIX(column_delta))
			result = VALUES_3(Qadd_column,column_delta,
				FIX((SI_Long)0L));
		    else if ((SI_Long)0L > IFIX(column_delta)) {
			column_index = new_column_maximum;
			temp_1 = FIXNUM_NEGATE(column_delta);
			temp = FIXNUM_NEGATE(column_delta);
			result = VALUES_3(Qdelete_column,temp_1,temp);
		    }
		    else
			result = VALUES_1(Qnil);
		    MVS_2(result,edit_action,count_1);
		    if (edit_action)
			table_block_insert_or_delete(freeform_table,
				row_index,column_index,edit_action,count_1);
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Working_on_new_table);
		CONTINUE_UNWINDING(0);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Working_on_annotated_frame);
	CONTINUE_UNWINDING(1);
	temp = ISVREF(freeform_table,(SI_Long)18L);
	result = VALUES_2(temp,T);
	RESTORE_STACK();
	return result;
    }
}

static Object Qfloat_array;        /* float-array */

static Object Qtruth_value;        /* truth-value */

/* MAKE-EVALUATION-VALUE-FOR-EXPRESSION-CELL-INDEX */
Object make_evaluation_value_for_expression_cell_index(wide_string)
    Object wide_string;
{
    Object length_1, value, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(178,22);
    length_1 = lengthw(wide_string);
    value = read_number_from_string(wide_string,FIX((SI_Long)0L),length_1);
    if (value);
    else
	value = read_symbol_from_string(wide_string,FIX((SI_Long)0L),length_1);
    if (value);
    else
	value = read_text_string_from_string(wide_string,FIX((SI_Long)0L),
		length_1);
    if (FIXNUMP(value))
	temp = value;
    else if ( !TRUEP(value))
	temp = Evaluation_false_value;
    else if (EQ(value,T))
	temp = Evaluation_true_value;
    else if (SYMBOLP(value))
	temp = value;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	temp = copy_managed_float(value);
    else if (FLOATP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	temp = copy_managed_long(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L)
	temp = make_evaluation_long(value);
    else if (text_string_p(value))
	temp = copy_as_wide_string(value);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	gensymed_symbol = M_CAR(value);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else
	temp = error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value));
    return VALUES_1(temp);
}

static Object Qcell_array;         /* cell-array */

static Object Qcurrent_value;      /* current-value */

static Object Qwarning_message_level_for_computation_style;  /* warning-message-level-for-computation-style */

static Object Qtrace_message_level_for_computation_style;  /* trace-message-level-for-computation-style */

static Object Qbreak_message_level_for_computation_style;  /* break-message-level-for-computation-style */

static Object Qexpression;         /* expression */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

/* MAKE-STRUCTURE-FOR-CELL-FORMAT */
Object make_structure_for_cell_format(feature_value,new_table)
    Object feature_value, new_table;
{
    Object eval_attrs_struct, tracing_substruct_qm, cell_array_qm;
    Object managed_array_qm, subfeature_name, subfeature_value, ab_loop_list_;
    Object eval_value, temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float, gensymed_symbol, expression_cell_qm;
    Object evaluation_value, wide_string_bv16, result_1, gensymed_symbol_2;
    SI_Long length_1, width, end_1, part_length, bv16_length, aref_arg_2;
    SI_Long aref_new_value_1, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char has_semi_p;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,23);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      if ( !TRUEP(simple_cell_expression_p(feature_value))) {
	  eval_attrs_struct = allocate_evaluation_structure(Nil);
	  tracing_substruct_qm = Nil;
	  cell_array_qm = get_lookup_slot_value_given_default(New_table,
		  Qcell_array,Nil);
	  managed_array_qm = cell_array_qm ? ISVREF(cell_array_qm,
		  (SI_Long)3L) : Qnil;
	  subfeature_name = Nil;
	  subfeature_value = Nil;
	  ab_loop_list_ = CDR(feature_value);
	  eval_value = Nil;
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	next_loop:
	  subfeature_name = CAR(ab_loop_list_);
	  temp = CDR(ab_loop_list_);
	  subfeature_value = CAR(temp);
	  if (FIXNUMP(subfeature_value))
	      eval_value = subfeature_value;
	  else if ( !TRUEP(subfeature_value))
	      eval_value = Evaluation_false_value;
	  else if (EQ(subfeature_value,T))
	      eval_value = Evaluation_true_value;
	  else if (SYMBOLP(subfeature_value))
	      eval_value = subfeature_value;
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(subfeature_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subfeature_value)) == 
		  (SI_Long)1L)
	      eval_value = copy_managed_float(subfeature_value);
	  else if (FLOATP(subfeature_value)) {
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
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(subfeature_value);
	      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	      eval_value = new_float;
	  }
	  else if (INLINE_LONG_VECTOR_P(subfeature_value) != (SI_Long)0L 
		  && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subfeature_value)) == 
		  (SI_Long)1L)
	      eval_value = copy_managed_long(subfeature_value);
	  else if (INLINE_LONG_P(subfeature_value) != (SI_Long)0L)
	      eval_value = make_evaluation_long(subfeature_value);
	  else if (text_string_p(subfeature_value))
	      eval_value = copy_as_wide_string(subfeature_value);
	  else if (CONSP(subfeature_value) && EQ(M_CDR(subfeature_value),
		  Qtruth_value)) {
	      gensymed_symbol = M_CAR(subfeature_value);
	      if (FIXNUM_EQ(gensymed_symbol,Truth))
		  eval_value = Evaluation_true_value;
	      else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		  eval_value = Evaluation_false_value;
	      else
		  eval_value = eval_cons_1(gensymed_symbol,Qtruth_value);
	  }
	  else
	      eval_value = error((SI_Long)2L,
		      "Bad type ~a for make-evaluation-value-based-on-type.",
		      type_of(subfeature_value));
	  if (EQ(subfeature_name,Qexpression_cell_index)) {
	      if (managed_array_qm) {
		  expression_cell_qm = FIXNUM_LE(ISVREF(managed_array_qm,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(managed_array_qm,
			  IFIX(FIXNUM_ADD(subfeature_value,
			  Managed_array_index_offset))) : 
			  ISVREF(ISVREF(managed_array_qm,
			  (IFIX(subfeature_value) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(subfeature_value) & 
			  (SI_Long)1023L);
		  if (expression_cell_qm && ISVREF(expression_cell_qm,
			  (SI_Long)6L)) {
		      temp = eval_attrs_struct;
		      evaluation_value = ISVREF(expression_cell_qm,
			      (SI_Long)6L);
		      set_evaluation_structure_slot(temp,Qcurrent_value,
			      FIXNUMP(evaluation_value) || 
			      evaluation_value && 
			      SYMBOLP(evaluation_value) ? evaluation_value 
			      : copy_evaluation_value_1(evaluation_value));
		  }
	      }
	  }
	  else if (EQ(subfeature_name,
		  Qwarning_message_level_for_computation_style)) {
	      if ( !TRUEP(tracing_substruct_qm))
		  tracing_substruct_qm = allocate_evaluation_structure(Nil);
	      set_evaluation_structure_slot(tracing_substruct_qm,
		      Qwarning_message_level,eval_value);
	  }
	  else if (EQ(subfeature_name,
		  Qtrace_message_level_for_computation_style)) {
	      if ( !TRUEP(tracing_substruct_qm))
		  tracing_substruct_qm = allocate_evaluation_structure(Nil);
	      set_evaluation_structure_slot(tracing_substruct_qm,
		      Qtracing_message_level,eval_value);
	  }
	  else if (EQ(subfeature_name,
		  Qbreak_message_level_for_computation_style)) {
	      if ( !TRUEP(tracing_substruct_qm))
		  tracing_substruct_qm = allocate_evaluation_structure(Nil);
	      set_evaluation_structure_slot(tracing_substruct_qm,
		      Qbreakpoint_level,eval_value);
	  }
	  else if (EQ(subfeature_name,Qexpression_source_text)) {
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subfeature_value));
	      width = UBYTE_16_ISAREF_1(subfeature_value,length_1 - 
		      (SI_Long)2L) + ((UBYTE_16_ISAREF_1(subfeature_value,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L);
	      has_semi_p = (SI_Long)59L == 
		      UBYTE_16_ISAREF_1(subfeature_value,width - (SI_Long)1L);
	      if (has_semi_p) {
		  temp = eval_attrs_struct;
		  end_1 = width - (SI_Long)1L;
		  part_length = end_1 - (SI_Long)0L;
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX(part_length + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value_1 = part_length & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value_1);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value_1 = (SI_Long)57344L | part_length >>  -  
			  - (SI_Long)16L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value_1);
		  UBYTE_16_ISASET_1(wide_string_bv16,part_length,(SI_Long)0L);
		  result_1 = wide_string_bv16;
		  gensymed_symbol = subfeature_value;
		  gensymed_symbol_1 = (SI_Long)0L;
		  gensymed_symbol_2 = result_1;
		  gensymed_symbol_3 = (SI_Long)0L;
		  gensymed_symbol_4 = part_length;
		  INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			  gensymed_symbol_1,
			  UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			  gensymed_symbol_3,gensymed_symbol_4);
		  set_evaluation_structure_slot(temp,Qexpression,result_1);
	      }
	      else {
		  temp = eval_attrs_struct;
		  set_evaluation_structure_slot(temp,Qexpression,
			  copy_wide_string(subfeature_value));
	      }
	  }
	  else
	      set_evaluation_structure_slot(eval_attrs_struct,
		      subfeature_name,eval_value);
	  ab_loop_list_ = CDDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  goto next_loop;
	end_loop:
	  if (tracing_substruct_qm)
	      set_evaluation_structure_slot(eval_attrs_struct,
		      Qtracing_and_breakpoints,tracing_substruct_qm);
	  if ((SI_Long)0L == 
		  IFIX(FIXNUM_SUB1(ISVREF(M_CAR(eval_attrs_struct),
		  (SI_Long)1L))) >>  -  - (SI_Long)1L) {
	      reclaim_evaluation_structure(eval_attrs_struct);
	      eval_attrs_struct = Nil;
	  }
	  temp = eval_attrs_struct;
	  goto end_2;
	  temp = Qnil;
	end_2:;
      }
      else
	  temp = Nil;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* MAKE-STRUCTURE-FOR-CELL-CONTENTS */
Object make_structure_for_cell_contents(feature_value)
    Object feature_value;
{
    Object eval_attrs_struct, tracing_substruct_qm, subfeature_name;
    Object subfeature_value, ab_loop_list_, eval_value, temp;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(178,24);
    if ( !TRUEP(simple_cell_expression_p(CAR(feature_value)))) {
	eval_attrs_struct = allocate_evaluation_structure(Nil);
	tracing_substruct_qm = Nil;
	subfeature_name = Nil;
	subfeature_value = Nil;
	ab_loop_list_ = CDAR(feature_value);
	eval_value = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	subfeature_name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	subfeature_value = CAR(temp);
	if (FIXNUMP(subfeature_value))
	    eval_value = subfeature_value;
	else if ( !TRUEP(subfeature_value))
	    eval_value = Evaluation_false_value;
	else if (EQ(subfeature_value,T))
	    eval_value = Evaluation_true_value;
	else if (SYMBOLP(subfeature_value))
	    eval_value = subfeature_value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(subfeature_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subfeature_value)) == 
		(SI_Long)1L)
	    eval_value = copy_managed_float(subfeature_value);
	else if (FLOATP(subfeature_value)) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(subfeature_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    eval_value = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(subfeature_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subfeature_value)) == 
		(SI_Long)1L)
	    eval_value = copy_managed_long(subfeature_value);
	else if (INLINE_LONG_P(subfeature_value) != (SI_Long)0L)
	    eval_value = make_evaluation_long(subfeature_value);
	else if (text_string_p(subfeature_value))
	    eval_value = copy_as_wide_string(subfeature_value);
	else if (CONSP(subfeature_value) && EQ(M_CDR(subfeature_value),
		Qtruth_value)) {
	    gensymed_symbol = M_CAR(subfeature_value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		eval_value = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		eval_value = Evaluation_false_value;
	    else
		eval_value = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    eval_value = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(subfeature_value));
	if (EQ(subfeature_name,Qexpression_cell_index));
	else if (EQ(subfeature_name,
		Qwarning_message_level_for_computation_style)) {
	    if ( !TRUEP(tracing_substruct_qm))
		tracing_substruct_qm = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(tracing_substruct_qm,
		    Qwarning_message_level,eval_value);
	}
	else if (EQ(subfeature_name,
		Qtrace_message_level_for_computation_style)) {
	    if ( !TRUEP(tracing_substruct_qm))
		tracing_substruct_qm = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(tracing_substruct_qm,
		    Qtracing_message_level,eval_value);
	}
	else if (EQ(subfeature_name,
		Qbreak_message_level_for_computation_style)) {
	    if ( !TRUEP(tracing_substruct_qm))
		tracing_substruct_qm = allocate_evaluation_structure(Nil);
	    set_evaluation_structure_slot(tracing_substruct_qm,
		    Qbreakpoint_level,eval_value);
	}
	else
	    set_evaluation_structure_slot(eval_attrs_struct,
		    subfeature_name,eval_value);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (tracing_substruct_qm)
	    set_evaluation_structure_slot(eval_attrs_struct,
		    Qtracing_and_breakpoints,tracing_substruct_qm);
	if ((SI_Long)0L == 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(eval_attrs_struct),
		(SI_Long)1L))) >>  -  - (SI_Long)1L) {
	    reclaim_evaluation_structure(eval_attrs_struct);
	    eval_attrs_struct = Nil;
	}
	temp = eval_attrs_struct;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qnone;               /* none */

static Object Qcell_evaluation_attributes;  /* cell-evaluation-attributes */

static Object Qcell_display_text;  /* cell-display-text */

static Object Qcell_display_value;  /* cell-display-value */

static Object Qhighlighted_qm;     /* highlighted? */

static Object Qcell_format;        /* cell-format */

/* MAKE-SEQUENCE-OF-FREEFORM-TABLE-ROW */
Object make_sequence_of_freeform_table_row(new_table,row_part)
    Object new_table, row_part;
{
    Object temp, cell_parts, cell_part, ab_loop_list_, column_eval_list;
    Object ab_loopvar_, ab_loopvar__1, cell_structure, format_structure_qm;
    Object feature_name, feature_value, ab_loop_list__1, expression_of_cell_qm;
    Object eval_attrs_struct_qm, wide_string_bv16, result_1, gensymed_symbol;
    Object gensymed_symbol_2, cell_array_qm, managed_array_qm, contents_qm;
    Object cell_qm, compiled_cell_qm, cell_index_qm, expression_cell_qm;
    Object evaluation_value, temp_1, temp_2;
    SI_Long length_1, width, end_1, part_length, bv16_length, aref_arg_2;
    SI_Long aref_new_value, gensymed_symbol_1, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char has_semi_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,25);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      temp = get_simple_part_feature(row_part,Qsubparts);
      cell_parts = CADR(temp);
      cell_part = Nil;
      ab_loop_list_ = cell_parts;
      column_eval_list = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      cell_part = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(CDR(cell_part)))
	  temp = Qnone;
      else {
	  cell_structure = allocate_evaluation_structure(Nil);
	  format_structure_qm = Nil;
	  feature_name = Nil;
	  feature_value = Nil;
	  ab_loop_list__1 = CDR(cell_part);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	next_loop_1:
	  feature_name = CAR(ab_loop_list__1);
	  temp = CDR(ab_loop_list__1);
	  feature_value = CAR(temp);
	  if (EQ(feature_name,Qcell_contents)) {
	      expression_of_cell_qm = CDR(feature_value);
	      eval_attrs_struct_qm = 
		      make_structure_for_cell_contents(feature_value);
	      if (expression_of_cell_qm) {
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expression_of_cell_qm));
		  width = UBYTE_16_ISAREF_1(expression_of_cell_qm,length_1 
			  - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(expression_of_cell_qm,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L);
		  has_semi_p = (SI_Long)59L == 
			  UBYTE_16_ISAREF_1(expression_of_cell_qm,width - 
			  (SI_Long)1L);
		  if (has_semi_p) {
		      end_1 = width - (SI_Long)1L;
		      part_length = end_1 - (SI_Long)0L;
		      wide_string_bv16 = 
			      allocate_byte_vector_16(FIX(part_length + 
			      (SI_Long)3L));
		      bv16_length = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = part_length & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | part_length >>  - 
			       - (SI_Long)16L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,part_length,
			      (SI_Long)0L);
		      result_1 = wide_string_bv16;
		      gensymed_symbol = expression_of_cell_qm;
		      gensymed_symbol_1 = (SI_Long)0L;
		      gensymed_symbol_2 = result_1;
		      gensymed_symbol_3 = (SI_Long)0L;
		      gensymed_symbol_4 = part_length;
		      INLINE_COPY_BYTE_VECTOR_16_PORTION(UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol),
			      gensymed_symbol_1,
			      UBYTE_16_SARRAY_TO_USHORT_PTR(gensymed_symbol_2),
			      gensymed_symbol_3,gensymed_symbol_4);
		      set_evaluation_structure_slot(cell_structure,
			      Qexpression,result_1);
		  }
		  else
		      set_evaluation_structure_slot(cell_structure,
			      Qexpression,
			      copy_wide_string(expression_of_cell_qm));
	      }
	      if (eval_attrs_struct_qm)
		  set_evaluation_structure_slot(cell_structure,
			  Qcell_evaluation_attributes,eval_attrs_struct_qm);
	  }
	  else if (EQ(feature_name,Qtext_value)) {
	      set_evaluation_structure_slot(cell_structure,
		      Qcell_display_text,convert_text_to_text_string(1,
		      feature_value));
	      cell_array_qm = 
		      get_lookup_slot_value_given_default(New_table,
		      Qcell_array,Nil);
	      managed_array_qm = cell_array_qm ? ISVREF(cell_array_qm,
		      (SI_Long)3L) : Qnil;
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
	      if (cell_index_qm && managed_array_qm) {
		  expression_cell_qm = FIXNUM_LE(ISVREF(managed_array_qm,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(managed_array_qm,
			  IFIX(FIXNUM_ADD(cell_index_qm,
			  Managed_array_index_offset))) : 
			  ISVREF(ISVREF(managed_array_qm,
			  (IFIX(cell_index_qm) >>  -  - (SI_Long)10L) + 
			  (SI_Long)2L),IFIX(cell_index_qm) & (SI_Long)1023L);
		  if (expression_cell_qm && ISVREF(expression_cell_qm,
			  (SI_Long)6L)) {
		      evaluation_value = ISVREF(expression_cell_qm,
			      (SI_Long)6L);
		      set_evaluation_structure_slot(cell_structure,
			      Qcell_display_value,
			      FIXNUMP(evaluation_value) || 
			      evaluation_value && 
			      SYMBOLP(evaluation_value) ? evaluation_value 
			      : copy_evaluation_value_1(evaluation_value));
		  }
	      }
	  }
	  else if (EQ(feature_name,Qhighlighted_qm));
	  else {
	      if ( !TRUEP(format_structure_qm)) {
		  format_structure_qm = allocate_evaluation_structure(Nil);
		  set_evaluation_structure_slot(cell_structure,
			  Qcell_format,format_structure_qm);
	      }
	      temp = format_structure_qm;
	      temp_1 = feature_name;
	      temp_2 = LISTP(feature_value) ? 
		      make_structure_for_cell_format(feature_value,
		      New_table) : Qnil;
	      if (temp_2);
	      else
		  temp_2 = feature_value;
	      set_evaluation_structure_slot(temp,temp_1,temp_2);
	  }
	  ab_loop_list__1 = CDDR(ab_loop_list__1);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  goto next_loop_1;
	end_loop_1:
	  temp = cell_structure;
	  goto end_2;
	  temp = Qnil;
	end_2:;
      }
      ab_loopvar__1 = eval_cons_1(temp,Nil);
      if (ab_loopvar_)
	  M_CDR(ab_loopvar_) = ab_loopvar__1;
      else
	  column_eval_list = ab_loopvar__1;
      ab_loopvar_ = ab_loopvar__1;
      goto next_loop;
    end_loop:
      temp = allocate_evaluation_sequence(column_eval_list);
      goto end_3;
      temp = Qnil;
    end_3:;
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

static Object Qcell_expression_parse;  /* cell-expression-parse */

static Object Qsource_position;    /* source-position */

static Object string_constant_2;   /* "~a;" */

static Object string_constant_3;   /* "~a" */

/* CREATE-COMPILED-CELL-EXPRESSION */
Object create_compiled_cell_expression(new_expression_value,new_eval_attrs,
	    expression_type)
    Object new_expression_value, new_eval_attrs, expression_type;
{
    Object new_expression, gensymed_symbol, held_vector, new_subfeature_name;
    Object attribute_value, new_subfeature_value, expression_p;
    Object tracing_substruct_p, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object held_vector_1, tracing_name, tracing_value, internal_tracing_name;
    Object ab_loopvar__3, ab_loopvar__4, temp, new_expression_description;
    Object new_cell_expression, gensymed_symbol_2, current_edit_state;
    Object svref_arg_1, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1, gensymed_symbol_1, next_index_1, length_2;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,26);
    SAVE_STACK();
    new_expression = evaluation_value_value(new_expression_value);
    if (new_eval_attrs) {
	gensymed_symbol = new_eval_attrs;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	new_subfeature_name = Nil;
	attribute_value = Nil;
	new_subfeature_value = Nil;
	expression_p = Nil;
	tracing_substruct_p = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	new_subfeature_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	gensymed_symbol_1 = next_index + (SI_Long)1L;
	attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	new_subfeature_value = 
		validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	next_index = next_index + (SI_Long)2L;
	expression_p = EQ(new_subfeature_name,Qexpression) ? T : Nil;
	tracing_substruct_p = EQ(new_subfeature_name,
		Qtracing_and_breakpoints) ? T : Nil;
	if ( !(expression_p || tracing_substruct_p)) {
	    ab_loopvar__2 = slot_value_cons_1(new_subfeature_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	if ( !(expression_p || tracing_substruct_p)) {
	    ab_loopvar__2 = slot_value_cons_1(CONSP(new_subfeature_value) 
		    && EQ(M_CDR(new_subfeature_value),Qtruth_value) ? 
		    evaluation_truth_value_is_true_p(new_subfeature_value) 
		    : FIXNUMP(new_subfeature_value) || 
		    new_subfeature_value && SYMBOLP(new_subfeature_value) 
		    || SIMPLE_VECTOR_P(new_subfeature_value) ? 
		    new_subfeature_value : 
		    copy_if_evaluation_value_1(new_subfeature_value),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	if (tracing_substruct_p) {
	    gensymed_symbol = new_subfeature_value;
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    tracing_name = Nil;
	    attribute_value = Nil;
	    tracing_value = Nil;
	    internal_tracing_name = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    held_vector_1 = M_CAR(gensymed_symbol);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	  next_loop_1:
	    if (next_index_1 >= length_2)
		goto end_loop_1;
	    tracing_name = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    gensymed_symbol_1 = next_index_1 + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector_1,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    tracing_value = 
		    validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index_1 = next_index_1 + (SI_Long)2L;
	    if (EQ(tracing_name,Qwarning_message_level))
		internal_tracing_name = 
			Qwarning_message_level_for_computation_style;
	    else if (EQ(tracing_name,Qtracing_message_level))
		internal_tracing_name = 
			Qtrace_message_level_for_computation_style;
	    else if (EQ(tracing_name,Qbreakpoint_level))
		internal_tracing_name = 
			Qbreak_message_level_for_computation_style;
	    else
		internal_tracing_name = Qnil;
	    ab_loopvar__4 = slot_value_cons_1(internal_tracing_name,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    ab_loopvar__4 = slot_value_cons_1(tracing_value,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_1;
	  end_loop_1:
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
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    new_expression_description = 
	    slot_value_cons_1(Qcompiled_cell_expression,temp);
    new_cell_expression = Nil;
    gensymed_symbol = Current_edit_state;
    if (Generate_source_annotation_info) {
	gensymed_symbol_2 = Current_edit_state ? 
		get_current_sexp_annotation_hash() : Nil;
	if (gensymed_symbol_2);
	else
	    gensymed_symbol_2 = make_sexp_annotation_hash();
    }
    else
	gensymed_symbol_2 = Nil;
    current_edit_state = make_edit_state_1();
    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
	    0);
      svref_arg_1 = Current_edit_state;
      SVREF(svref_arg_1,FIX((SI_Long)90L)) = gensymed_symbol_2;
      result = parse_text_string(2,new_expression,Qcell_expression_parse);
      MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
      if (EQ(parse_result_or_bad_phrase,Bad_phrase) ||  
	      !EQ(CAR(parse_result_or_bad_phrase),Qsource_position))
	  SAVE_VALUES(VALUES_2(Bad_phrase,error_string_qm));
      else {
	  temp = nconc2(new_expression_description,
		  slot_value_list_2(Qexpression_cell_index,
		  compile_a_compiled_cell_expression_from_expression_parse_and_style_description(CADR(parse_result_or_bad_phrase),
		  new_expression_description,expression_type)));
	  new_cell_expression = slot_value_cons_1(temp,new_eval_attrs ? 
		  tformat_text_string(2,string_constant_2,new_expression) :
		   tformat_text_string(2,string_constant_3,new_expression));
	  SAVE_VALUES(VALUES_1(new_cell_expression));
      }
      if (gensymed_symbol) {
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)90L)) = Nil;
      }
      reclaim_edit_state_1(Current_edit_state);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object list_constant_3;     /* # */

static Object Qcell_expression_and_text;  /* cell-expression-and-text */

/* HANDLE-CELL-EXPRESSION */
Object handle_cell_expression(current_annotated_frame,current_cell,
	    new_expression_value,new_eval_attrs)
    Object current_annotated_frame, current_cell, new_expression_value;
    Object new_eval_attrs;
{
    Object compiled_cell_expression_or_bad_phrase, error_string_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,27);
    PUSH_SPECIAL_WITH_SYMBOL(Current_cell,Qcurrent_cell,current_cell,1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
	      0);
	result = create_compiled_cell_expression(new_expression_value,
		new_eval_attrs,list_constant_3);
	MVS_2(result,compiled_cell_expression_or_bad_phrase,error_string_qm);
	if (EQ(compiled_cell_expression_or_bad_phrase,Bad_phrase))
	    result = VALUES_2(Bad_phrase,error_string_qm);
	else {
	    change_annotation(Current_annotated_frame,Current_cell,
		    Qcell_contents,Qcell_expression_and_text,Nil,
		    compiled_cell_expression_or_bad_phrase);
	    result = VALUES_1(Nil);
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_4;   /* "Error in the expression for cell (~a, ~a): ~s: ~a" */

static Object list_constant_4;     /* # */

static Object string_constant_5;   /* "Bad expression in ~S~%" */

static Object Qcell_expression;    /* cell-expression */

/* SET-THE-SPECIFIED-CELL-FEATURES */
Object set_the_specified_cell_features(new_value)
    Object new_value;
{
    Object current_cell_annotations, temp, current_rows, error_string_qm;
    Object gensymed_symbol, held_vector, new_row_element, current_row;
    Object ab_loop_iter_flag_, elt_1, validated_elt, held_vector_1;
    Object new_cell_element, current_cell, held_vector_2, new_feature_name;
    Object attribute_value, new_feature_value, new_expression_value;
    Object new_eval_attrs, new_formats, result_qm, local_error_string_qm;
    Object new_format_name, new_format_value, expression;
    Object adjusted_format_value_qm, value_for_expression_qm;
    Object compiled_cell_expression_or_bad_phrase, new_error_string_qm;
    SI_Long next_index, length_1, i, next_index_1, length_2, j, next_index_2;
    SI_Long length_3, gensymed_symbol_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,28);
    current_cell_annotations = ISVREF(Current_annotated_frame,(SI_Long)18L);
    temp = get_simple_part_feature(current_cell_annotations,Qsubparts);
    current_rows = CADR(temp);
    error_string_qm = Nil;
    gensymed_symbol = new_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    new_row_element = Nil;
    i = (SI_Long)0L;
    current_row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_row,Qcurrent_row,current_row,1);
      ab_loop_iter_flag_ = T;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop:
      if (next_index >= length_1)
	  goto end_loop;
      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	      Nil) : Nil;
      next_index = next_index + (SI_Long)1L;
      new_row_element = validated_elt;
      if ( !TRUEP(ab_loop_iter_flag_))
	  i = i + (SI_Long)1L;
      temp = get_simple_part_feature(nth(FIX(i),current_rows),Qsubparts);
      Current_row = CADR(temp);
      gensymed_symbol = new_row_element;
      held_vector_1 = Nil;
      next_index_1 = (SI_Long)1L;
      length_2 = (SI_Long)0L;
      new_cell_element = Nil;
      j = (SI_Long)0L;
      current_cell = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_cell,Qcurrent_cell,current_cell,0);
	ab_loop_iter_flag_ = T;
	held_vector_1 = M_CAR(gensymed_symbol);
	length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
      next_loop_1:
	if (next_index_1 >= length_2)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		next_index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index_1 = next_index_1 + (SI_Long)1L;
	new_cell_element = validated_elt;
	if ( !TRUEP(ab_loop_iter_flag_))
	    j = j + (SI_Long)1L;
	Current_cell = nth(FIX(j),Current_row);
	if ( !EQ(new_cell_element,Qnone)) {
	    gensymed_symbol = new_cell_element;
	    held_vector_2 = Nil;
	    next_index_2 = (SI_Long)1L;
	    length_3 = (SI_Long)0L;
	    new_feature_name = Nil;
	    attribute_value = Nil;
	    new_feature_value = Nil;
	    new_expression_value = Nil;
	    new_eval_attrs = Nil;
	    new_formats = Nil;
	    held_vector_2 = M_CAR(gensymed_symbol);
	    length_3 = IFIX(ISVREF(held_vector_2,(SI_Long)1L));
	  next_loop_2:
	    if (next_index_2 >= length_3)
		goto end_loop_2;
	    new_feature_name = FIXNUM_LE(ISVREF(held_vector_2,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_2,
		    next_index_2 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_2,(next_index_2 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_2 & 
		    (SI_Long)1023L);
	    gensymed_symbol_1 = next_index_2 + (SI_Long)1L;
	    attribute_value = FIXNUM_LE(ISVREF(held_vector_2,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_2,
		    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) :
		     ISVREF(ISVREF(held_vector_2,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		    (SI_Long)1023L);
	    new_feature_value = 
		    validate_item_or_evaluation_value(attribute_value,Nil,Nil);
	    next_index_2 = next_index_2 + (SI_Long)2L;
	    if (EQ(new_feature_name,Qexpression))
		new_expression_value = new_feature_value;
	    else if (EQ(new_feature_name,Qcell_evaluation_attributes))
		new_eval_attrs = new_feature_value;
	    else if (EQ(new_feature_name,Qcell_format))
		new_formats = new_feature_value;
	    else;
	    goto next_loop_2;
	  end_loop_2:
	    if (new_expression_value) {
		result_qm = handle_cell_expression(Current_annotated_frame,
			Current_cell,new_expression_value,new_eval_attrs);
		local_error_string_qm = result_qm ? tformat_text_string(5,
			string_constant_4,FIX(i),FIX(j),
			new_expression_value,result_qm) : Nil;
		if (local_error_string_qm)
		    error_string_qm = 
			    combine_and_reclaim_error_strings(error_string_qm,
			    local_error_string_qm);
	    }
	    if (new_formats) {
		gensymed_symbol = new_formats;
		held_vector_2 = Nil;
		next_index_2 = (SI_Long)1L;
		length_3 = (SI_Long)0L;
		new_format_name = Nil;
		attribute_value = Nil;
		new_format_value = Nil;
		held_vector_2 = M_CAR(gensymed_symbol);
		length_3 = IFIX(ISVREF(held_vector_2,(SI_Long)1L));
	      next_loop_3:
		if (next_index_2 >= length_3)
		    goto end_loop_3;
		new_format_name = FIXNUM_LE(ISVREF(held_vector_2,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_2,next_index_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_2,(next_index_2 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index_2 & 
			(SI_Long)1023L);
		gensymed_symbol_1 = next_index_2 + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector_2,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_2,gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_2,(gensymed_symbol_1 >>  
			-  - (SI_Long)10L) + (SI_Long)2L),
			gensymed_symbol_1 & (SI_Long)1023L);
		new_format_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index_2 = next_index_2 + (SI_Long)2L;
		if (SYMBOLP(new_format_value))
		    set_simple_part_feature(Current_cell,new_format_name,
			    new_format_value);
		else {
		    expression = estructure_slot(new_format_value,
			    Qexpression,Nil);
		    adjusted_format_value_qm = 
			    remove_evaluation_structure_attribute(new_format_value,
			    Qcurrent_value);
		    value_for_expression_qm = adjusted_format_value_qm;
		    if (value_for_expression_qm);
		    else
			value_for_expression_qm = new_format_value;
		    if (IFIX(FIXNUM_SUB1(ISVREF(M_CAR(value_for_expression_qm),
			    (SI_Long)1L))) >>  -  - (SI_Long)1L == (SI_Long)1L)
			value_for_expression_qm = Nil;
		    result = create_compiled_cell_expression(expression,
			    value_for_expression_qm,list_constant_4);
		    MVS_2(result,compiled_cell_expression_or_bad_phrase,
			    new_error_string_qm);
		    if (adjusted_format_value_qm)
			reclaim_evaluation_structure(adjusted_format_value_qm);
		    if (EQ(compiled_cell_expression_or_bad_phrase,
				Bad_phrase)) {
			temp = error_string_qm;
			error_string_qm = 
				combine_and_reclaim_error_strings(temp,
				new_error_string_qm ? new_error_string_qm :
				 tformat_text_string(2,string_constant_5,
				expression));
		    }
		    else {
			temp = 
				nconc2(CAR(compiled_cell_expression_or_bad_phrase),
				slot_value_list_2(Qexpression_source_text,
				CDR(compiled_cell_expression_or_bad_phrase)));
			reclaim_slot_value_cons_1(compiled_cell_expression_or_bad_phrase);
			compiled_cell_expression_or_bad_phrase = temp;
			change_annotation(Current_annotated_frame,
				Current_cell,new_format_name,
				Qcell_expression,Nil,
				compiled_cell_expression_or_bad_phrase);
		    }
		}
		goto next_loop_3;
	      end_loop_3:;
	    }
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
      POP_SPECIAL();
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
      result = VALUES_1(error_string_qm);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object string_constant_6;   /* "~a~%~a~%" */

/* COMBINE-AND-RECLAIM-ERROR-STRINGS */
Object combine_and_reclaim_error_strings(old_string_qm,new_string)
    Object old_string_qm, new_string;
{
    Object temp;

    x_note_fn_call(178,29);
    if (old_string_qm) {
	temp = tformat_text_string(3,string_constant_6,old_string_qm,
		new_string);
	reclaim_text_string(new_string);
	reclaim_text_string(old_string_qm);
    }
    else
	temp = new_string;
    return VALUES_1(temp);
}

/* INITIAL-TABLE-CELLS */
Object initial_table_cells(class_1)
    Object class_1;
{
    x_note_fn_call(178,30);
    return VALUES_1(Nil);
}

/* GET-TABLE-CELLS */
Object get_table_cells(freeform_table)
    Object freeform_table;
{
    Object table_part, temp, row_parts, row_part, ab_loop_list_, row_eval_list;
    Object ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(178,31);
    table_part = ISVREF(freeform_table,(SI_Long)18L);
    temp = get_simple_part_feature(table_part,Qsubparts);
    row_parts = CADR(temp);
    row_part = Nil;
    ab_loop_list_ = row_parts;
    row_eval_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    row_part = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = 
	    eval_cons_1(make_sequence_of_freeform_table_row(freeform_table,
	    row_part),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	row_eval_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(row_eval_list);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qrow_annotations;    /* row-annotations */

static Object Qcolumn_annotations;  /* column-annotations */

static Object string_constant_7;   /* "This value does not represent a rectangular grid of cells.  ~
				    *                Please make sure that all the row sequences are the same ~
				    *                length."
				    */

/* SET-TABLE-CELLS */
Object set_table_cells(freeform_table,new_value)
    Object freeform_table, new_value;
{
    Object length_of_first_row, gensymed_symbol, held_vector, row;
    Object length_of_nth_row, elt_1, validated_elt, rectangular_p;
    Object current_annotated_frame, current_block_of_dependent_frame;
    Object current_computation_frame, old_row_annotations;
    Object old_column_annotations, old_cell_annotations, new_row_maximum;
    Object new_column_maximum, svref_arg_1, svref_new_value, gensymed_symbol_1;
    Object temp;
    SI_Long next_index, length_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(3);
    Object result;

    x_note_fn_call(178,32);
    SAVE_STACK();
    length_of_first_row = 
	    FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence_aref(new_value,
	    FIX((SI_Long)0L))),(SI_Long)1L));
    gensymed_symbol = new_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      length_of_nth_row = Nil;
      held_vector = M_CAR(gensymed_symbol);
      length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    next_loop:
      if (next_index >= length_1)
	  goto end_loop;
      elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(held_vector,next_index 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(held_vector,(next_index >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),next_index & (SI_Long)1023L);
      validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	      Nil) : Nil;
      next_index = next_index + (SI_Long)1L;
      Row = validated_elt;
      length_of_nth_row = FIXNUM_SUB1(ISVREF(M_CAR(Row),(SI_Long)1L));
      if ( !EQ(length_of_first_row,length_of_nth_row)) {
	  rectangular_p = Nil;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      rectangular_p = T;
      goto end_1;
      rectangular_p = Qnil;
    end_1:;
    POP_SPECIAL();
    if (rectangular_p) {
	LOCK(Working_on_annotated_frame);
	if (PUSH_UNWIND_PROTECT(1)) {
	    current_annotated_frame = freeform_table;
	    current_block_of_dependent_frame = freeform_table;
	    current_computation_frame = freeform_table;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			0);
		  old_row_annotations = ISVREF(Current_annotated_frame,
			  (SI_Long)16L);
		  old_column_annotations = ISVREF(Current_annotated_frame,
			  (SI_Long)17L);
		  old_cell_annotations = ISVREF(Current_annotated_frame,
			  (SI_Long)18L);
		  new_row_maximum = FIXNUM_SUB1(ISVREF(M_CAR(new_value),
			  (SI_Long)1L));
		  new_column_maximum = 
			  FIXNUM_SUB1(ISVREF(M_CAR(evaluation_sequence_aref(new_value,
			  FIX((SI_Long)0L))),(SI_Long)1L));
		  erase_entire_annotated_block(Current_annotated_frame);
		  if (Noting_changes_to_kb_p)
		      note_change_to_block_1(Current_annotated_frame,
			      Qrow_annotations);
		  svref_arg_1 = Current_annotated_frame;
		  svref_new_value = make_table_annotation(Qrow,
			  new_row_maximum,FIX((SI_Long)1L));
		  SVREF(svref_arg_1,FIX((SI_Long)16L)) = svref_new_value;
		  if (Noting_changes_to_kb_p)
		      note_change_to_block_1(Current_annotated_frame,
			      Qcolumn_annotations);
		  svref_arg_1 = Current_annotated_frame;
		  svref_new_value = make_table_annotation(Qcolumn,
			  FIX((SI_Long)1L),new_column_maximum);
		  SVREF(svref_arg_1,FIX((SI_Long)17L)) = svref_new_value;
		  if (Noting_changes_to_kb_p)
		      note_change_to_block_1(Current_annotated_frame,
			      Qcell_annotations);
		  svref_arg_1 = Current_annotated_frame;
		  svref_new_value = make_table_annotation(Qcell,
			  new_row_maximum,new_column_maximum);
		  SVREF(svref_arg_1,FIX((SI_Long)18L)) = svref_new_value;
		  reclaim_part_description(old_row_annotations);
		  reclaim_part_description(old_column_annotations);
		  reclaim_part_description(old_cell_annotations);
		  update_representations_of_slot_value(2,
			  Current_annotated_frame,Qcell_annotations);
		  update_representations_of_slot_value(2,
			  Current_annotated_frame,Qrow_annotations);
		  update_representations_of_slot_value(2,
			  Current_annotated_frame,Qcolumn_annotations);
		  LOCK(Working_on_new_table);
		  if (PUSH_UNWIND_PROTECT(0))
		      update_new_table_size();
		  POP_UNWIND_PROTECT(0);
		  UNLOCK(Working_on_new_table);
		  CONTINUE_UNWINDING(0);
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(Current_annotated_frame,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)19L),
			  (SI_Long)1L);
		  gensymed_symbol_1 = Current_annotated_frame;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		  redraw_entire_annotated_block();
		  temp = set_the_specified_cell_features(new_value);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(VALUES_1(temp));
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Working_on_annotated_frame);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	temp = result;
    }
    else
	temp = tformat_text_string(1,string_constant_7);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object Qg2_cell_array;      /* g2-cell-array */

/* INITIALIZE-FOR-NEW-TABLE */
Object initialize_for_new_table(new_table)
    Object new_table;
{
    Object frame, sub_vector_qm, method_function_qm, temp, class_1;
    Object class_description, cell_annotations_for_class_1, row_maximum;
    Object column_maximum, current_annotated_frame, svref_arg_1;
    Object svref_new_value, new_value, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;
    char cloning_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(5);
    Object result;

    x_note_fn_call(178,33);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,4);
      frame = New_table;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qnew_table)) {
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
      temp = ISVREF(New_table,(SI_Long)16L);
      cloning_qm = CONSP(temp);
      if ( !cloning_qm) {
	  class_1 = ISVREF(ISVREF(New_table,(SI_Long)1L),(SI_Long)1L);
	  class_description = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  cell_annotations_for_class_1 = 
		  ISVREF(get_slot_description_of_class_description_function(Qcell_annotations,
		  class_description,Nil),(SI_Long)6L);
	  temp = get_simple_part_feature(cell_annotations_for_class_1,
		  Qrow_maximum);
	  if (temp);
	  else
	      temp = FIX((SI_Long)4L);
	  row_maximum = temp;
	  PUSH_SPECIAL_WITH_SYMBOL(Row_maximum,Qrow_maximum,row_maximum,3);
	    temp = get_simple_part_feature(cell_annotations_for_class_1,
		    Qcolumn_maximum);
	    if (temp);
	    else
		temp = FIX((SI_Long)3L);
	    column_maximum = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Column_maximum,Qcolumn_maximum,column_maximum,
		    2);
	      current_annotated_frame = New_table;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		      1);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,Qrow_annotations);
		svref_arg_1 = New_table;
		svref_new_value = make_table_annotation(Qrow,Row_maximum,
			FIX((SI_Long)1L));
		SVREF(svref_arg_1,FIX((SI_Long)16L)) = svref_new_value;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,Qcolumn_annotations);
		svref_arg_1 = New_table;
		svref_new_value = make_table_annotation(Qcolumn,
			FIX((SI_Long)1L),Column_maximum);
		SVREF(svref_arg_1,FIX((SI_Long)17L)) = svref_new_value;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,Qcell_annotations);
		svref_arg_1 = New_table;
		svref_new_value = make_table_annotation(Qcell,Row_maximum,
			Column_maximum);
		SVREF(svref_arg_1,FIX((SI_Long)18L)) = svref_new_value;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,Qdefault_cell_format);
		svref_arg_1 = New_table;
		svref_new_value = 
			ISVREF(get_slot_description_of_class_description_function(Qdefault_cell_format,
			class_description,Nil),(SI_Long)6L);
		SVREF(svref_arg_1,FIX((SI_Long)19L)) = svref_new_value;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(New_table,
			    Qdefault_evaluation_setting);
		svref_arg_1 = New_table;
		svref_new_value = 
			ISVREF(get_slot_description_of_class_description_function(Qdefault_evaluation_setting,
			class_description,Nil),(SI_Long)6L);
		SVREF(svref_arg_1,FIX((SI_Long)20L)) = svref_new_value;
		new_value = make_frame(Qg2_cell_array);
		temp = New_table;
		initialize_slot_description_value(temp,
			get_slot_description_of_class_description_function(Qcell_array,
			ISVREF(New_table,(SI_Long)1L),Nil),new_value);
		LOCK(Working_on_annotated_frame);
		if (PUSH_UNWIND_PROTECT(1)) {
		    current_annotated_frame = New_table;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			    0);
		      LOCK(Working_on_new_table);
		      if (PUSH_UNWIND_PROTECT(0))
			  update_new_table_size();
		      POP_UNWIND_PROTECT(0);
		      UNLOCK(Working_on_new_table);
		      CONTINUE_UNWINDING(0);
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(1);
		UNLOCK(Working_on_annotated_frame);
		CONTINUE_UNWINDING(1);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      method_index = (SI_Long)19L;
      frame = New_table;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),method_index);
      function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
      if (function_qm)
	  result = inline_funcall_1(function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qstandardize_text_size_feature_in_part_description;  /* standardize-text-size-feature-in-part-description */

/* INITIALIZE-AFTER-READING-FOR-NEW-TABLE */
Object initialize_after_reading_for_new_table(new_table)
    Object new_table;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,34);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      frame = New_table;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)4L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qnew_table)) {
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
      if ( !(IFIX(Kb_flags) >= (SI_Long)231L)) {
	  map_over_part_description(Qstandardize_text_size_feature_in_part_description,
		  ISVREF(New_table,(SI_Long)18L));
	  result = map_over_part_description(Qstandardize_text_size_feature_in_part_description,
		  ISVREF(New_table,(SI_Long)19L));
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

/* MAKE-TABLE-ANNOTATION */
Object make_table_annotation(which_kind,row_count,column_count)
    Object which_kind, row_count, column_count;
{
    Object rowwise_p, columnwise_p, row_maximum, column_maximum;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, prototype_cell, gensymed_symbol, gensymed_symbol_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, temp_2, result_1;
    Object fragment_with_default_for_all_cells;
    SI_Long row_index, ab_loop_bind_, column_index, ab_loop_bind__1;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,35);
    rowwise_p = memq_function(which_kind,list_constant_5);
    columnwise_p = memq_function(which_kind,list_constant_6);
    row_maximum = rowwise_p ? row_count : FIX((SI_Long)1L);
    PUSH_SPECIAL_WITH_SYMBOL(Row_maximum,Qrow_maximum,row_maximum,1);
      column_maximum = columnwise_p ? column_count : FIX((SI_Long)1L);
      PUSH_SPECIAL_WITH_SYMBOL(Column_maximum,Qcolumn_maximum,column_maximum,
	      0);
	if (EQ(which_kind,Qrow)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		}
		else {
		    temp = Available_float_array_conses_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,25.0);
	    prototype_cell = slot_value_list_3(Qcell,Qrow_height,new_float);
	}
	else if (EQ(which_kind,Qcolumn)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		}
		else {
		    temp = Available_float_array_conses_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_1 = Current_thread_index;
		    SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,70.0);
	    prototype_cell = slot_value_list_3(Qcell,Qcolumn_width,new_float);
	}
	else if (EQ(which_kind,Qcell))
	    prototype_cell = copy_for_slot_value(list_constant_7);
	else
	    prototype_cell = Qnil;
	gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qnew_table;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qrow_maximum;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = Row_maximum;
	M_CAR(gensymed_symbol_1) = temp;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcolumn_maximum;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = Column_maximum;
	M_CAR(gensymed_symbol_1) = temp;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qsubparts;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	row_index = (SI_Long)1L;
	ab_loop_bind_ = IFIX(Row_maximum);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (row_index > ab_loop_bind_)
	    goto end_loop;
	column_index = (SI_Long)1L;
	ab_loop_bind__1 = IFIX(Column_maximum);
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
      next_loop_1:
	if (column_index > ab_loop_bind__1)
	    goto end_loop_1;
	ab_loopvar__4 = 
		slot_value_cons_1(copy_for_slot_value(prototype_cell),Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	column_index = column_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_2 = ab_loopvar__2;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	ab_loopvar__2 = slot_value_cons_1(slot_value_list_3(Qrow,Qsubparts,
		slot_value_list_2(Qcell,temp_2)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	row_index = row_index + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_2;
	temp_2 = Qnil;
      end_2:;
	temp = slot_value_list_2(Qrow,temp_2);
	M_CAR(gensymed_symbol_1) = temp;
	result_1 = gensymed_symbol;
	if (EQ(which_kind,Qcell)) {
	    fragment_with_default_for_all_cells = 
		    copy_for_slot_value(list_constant_8);
	    temp = last(fragment_with_default_for_all_cells,_);
	    temp_1 = CDR(result_1);
	    M_CDR(temp) = temp_1;
	    M_CDR(result_1) = fragment_with_default_for_all_cells;
	}
	reclaim_slot_value(prototype_cell);
	result = VALUES_1(result_1);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UPDATE-FRAME-STATUS-AND-NOTES-FOR-NEW-TABLE */
Object update_frame_status_and_notes_for_new_table(new_table)
    Object new_table;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(178,36);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qbackground_color;   /* background-color */

/* EXPORT-CELL-ATTRIBUTE-NAME */
Object export_cell_attribute_name(cell_part_name)
    Object cell_part_name;
{
    Object temp;

    x_note_fn_call(178,37);
    if (EQ(cell_part_name,Qcell_contents))
	temp = Qcell_display_text;
    else if (EQ(cell_part_name,Qbackground_color))
	temp = Qbackground_color;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object Qiteration_state;    /* iteration-state */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qws_representation;  /* ws-representation */

static Object Qsocket;             /* socket */

static Object Qattribute_name;     /* attribute-name */

static Object Qtable_cells;        /* table-cells */

static Object Qrow_index;          /* row-index */

static Object Qcolumn_index;       /* column-index */

static Object Qcell_attribute_name;  /* cell-attribute-name */

static Object Qnew_value;          /* new-value */

static Object Qab_structure;       /* structure */

static Object Qitem_change;        /* item-change */

/* EXPRESSION-CELL-UPDATED-FOR-NEW-TABLE */
Object expression_cell_updated_for_new_table(new_table,g2_cell_array,
	    cell_index,old_value_qm,new_value_qm)
    Object new_table, g2_cell_array, cell_index, old_value_qm, new_value_qm;
{
    Object cell_updated_qm, cell_text_qm, cell_attribute_name, new_value;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, cell_x, cell_y, cell;
    Object cell_part, temp_3, item_or_value, svref_new_value, arg_lists;
    Object arg_list, ab_loop_list__1, arg_list_to_send;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(4);
    Object result;

    x_note_fn_call(178,38);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,3);
      cell_updated_qm = cell_updated(New_table,cell_index,old_value_qm,
	      new_value_qm);
      cell_text_qm = Nil;
      cell_attribute_name = Nil;
      new_value = Nil;
      if (G2_has_v5_mode_windows_p) {
	  gensymed_symbol = old_value_qm;
	  temp = FIXNUMP(gensymed_symbol);
	  if (temp);
	  else
	      temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		      (SI_Long)0L ? 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		      (SI_Long)1L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		       IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		      (SI_Long)1L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		      (SI_Long)0L;
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
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
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
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
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
		  temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			   (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			  TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			  TRUEP(Nil);
	      }
	      else
		  temp = TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      gensymed_symbol = new_value_qm;
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
		    next_loop_3:
		      if (level < ab_loop_bind_)
			  goto end_loop_3;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_4:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_1,temp_2);
		      MVS_2(result,succ,marked);
		    next_loop_5:
		      if ( !TRUEP(marked))
			  goto end_loop_4;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp_2 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
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
	  }
	  else
	      temp = TRUEP(Nil);
	  if ( !(temp ? TRUEP(evaluation_value_eql(2,old_value_qm,
		  new_value_qm)) : TRUEP(Nil))) {
	      LOCK(Javalink_notification_versions);
	      if (PUSH_UNWIND_PROTECT(1)) {
		  notification_data_version_map = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
			  2);
		    if (SIMPLE_VECTOR_P(New_table) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(New_table)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(New_table,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(New_table,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = ISVREF(ISVREF(New_table,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Connection_class_description,
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
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    connection_qm = ISVREF(New_table,(SI_Long)21L);
			    temp_2 = workspace_of_connection_qm(connection_qm);
			}
			else
			    temp_2 = get_workspace_if_any(New_table);
		    }
		    else if (SIMPLE_VECTOR_P(New_table) && 
			    EQ(ISVREF(New_table,(SI_Long)0L),
			    Qg2_defstruct_structure_name_connection_g2_struct))
			temp_2 = workspace_of_connection_qm(New_table);
		    else
			temp_2 = Qnil;
		    if (temp_2) {
			if (SIMPLE_VECTOR_P(New_table) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(New_table)) 
				> (SI_Long)2L &&  !EQ(ISVREF(New_table,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(New_table,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    sub_class_bit_vector = ISVREF(ISVREF(New_table,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Connection_class_description,
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
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				connection_qm = ISVREF(New_table,(SI_Long)21L);
				temp_2 = 
					workspace_of_connection_qm(connection_qm);
			    }
			    else
				temp_2 = get_workspace_if_any(New_table);
			}
			else if (SIMPLE_VECTOR_P(New_table) && 
				EQ(ISVREF(New_table,(SI_Long)0L),
				Qg2_defstruct_structure_name_connection_g2_struct))
			    temp_2 = workspace_of_connection_qm(New_table);
			else
			    temp_2 = Qnil;
			temp = TRUEP(v5_tw_item_like_p(temp_2));
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			any_body_evaluated_p = Nil;
			if (SIMPLE_VECTOR_P(New_table) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(New_table)) 
				> (SI_Long)2L &&  !EQ(ISVREF(New_table,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(New_table,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    sub_class_bit_vector = ISVREF(ISVREF(New_table,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Connection_class_description,
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
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				connection_qm = ISVREF(New_table,(SI_Long)21L);
				temp_2 = 
					workspace_of_connection_qm(connection_qm);
			    }
			    else
				temp_2 = get_workspace_if_any(New_table);
			}
			else if (SIMPLE_VECTOR_P(New_table) && 
				EQ(ISVREF(New_table,(SI_Long)0L),
				Qg2_defstruct_structure_name_connection_g2_struct))
			    temp_2 = workspace_of_connection_qm(New_table);
			else
			    temp_2 = Qnil;
			frame_list = ISVREF(temp_2,(SI_Long)9L);
			class_name = Qws_representation;
			new_list = Qnil;
			frame = Nil;
			ab_loop_list_ = frame_list;
		      next_loop_6:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_6;
			frame = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(class_name,
				Class_description_gkbprop);
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(ISVREF(frame,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    new_list = gensym_cons_1(frame,new_list);
			goto next_loop_6;
		      end_loop_6:
			representations = new_list;
			goto end_3;
			representations = Qnil;
		      end_3:;
			current_frame_serial_number_on_entry = 
				copy_frame_serial_number(Current_frame_serial_number);
			representation = Nil;
			ab_loop_list_ = representations;
		      next_loop_7:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_7;
			representation = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			gensymed_symbol = ISVREF(representation,(SI_Long)3L);
			temp = SIMPLE_VECTOR_P(representation) ? 
				EQ(ISVREF(representation,(SI_Long)1L),
				Qavailable_frame_vector) : TRUEP(Qnil);
			if (temp);
			else
			    temp = FIXNUMP(gensymed_symbol) ? 
				    IFIX(gensymed_symbol) == (SI_Long)-1L :
				     TRUEP(Nil);
			if (temp);
			else if (FIXNUMP(current_frame_serial_number_on_entry))
			    temp = FIXNUMP(gensymed_symbol) ? 
				    FIXNUM_LT(current_frame_serial_number_on_entry,
				    gensymed_symbol) : TRUEP(T);
			else if (FIXNUMP(gensymed_symbol))
			    temp = TRUEP(Nil);
			else {
			    xa = M_CAR(current_frame_serial_number_on_entry);
			    ya = M_CAR(gensymed_symbol);
			    temp = FIXNUM_LT(xa,ya);
			    if (temp);
			    else
				temp = FIXNUM_EQ(xa,ya) ? 
					FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
					M_CDR(gensymed_symbol)) : TRUEP(Qnil);
			}
			if ( !temp ? 
				TRUEP(representation_address_valid_p(representation)) 
				: TRUEP(Nil)) {
			    if ( !TRUEP(Notification_data_version_map))
				Notification_data_version_map = 
					gensym_cons_1(T,Nil);
			    version_for_current = Nil;
			    evaluatedp = Nil;
			    address = ISVREF(representation,(SI_Long)8L);
			    socket_1 = getf(address,Qsocket,_);
			    representation_version = 
				    remote_icp_protocol_version(socket_1);
			    subscription_handle = ISVREF(representation,
				    (SI_Long)12L);
			    current_list = Notification_data_version_map;
			    version_or_data = Nil;
			  next_loop_8:
			    version_or_data = CAR(current_list);
			    if ( !TRUEP(version_or_data))
				goto end_4;
			    version_for_current = 
				    javalink_versioned_call_data_get_version(version_or_data);
			    evaluatedp = 
				    javalink_versioned_call_data_evaluated_p(version_or_data);
			    if (EQ(version_for_current,T) || 
				    FIXNUM_GE(representation_version,
				    version_for_current)) {
				if ( !TRUEP(evaluatedp)) {
				    LOCK(Javalink_notification_versions);
				    if (PUSH_UNWIND_PROTECT(0)) {
					current_lookup_data = 
						make_javalink_versioned_data(version_or_data);
					PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
						1);
					  temp_2 = New_table;
					  result = expression_cell_index_to_cell_coordinates(3,
						  cell_index,New_table,T);
					  MVS_4(result,cell_x,cell_y,cell,
						  cell_part);
					  PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,
						  0);
					    if (cell_x && cell_y && Cell 
						    && cell_part) {
						cell_attribute_name = 
							export_cell_attribute_name(cell_part);
						if (EQ(cell_attribute_name,
							Qbackground_color))
						    new_value = new_value_qm;
						else if (EQ(cell_attribute_name,
							Qcell_display_text)) {
						    cell_text_qm = 
							    get_simple_part_feature(Cell,
							    Qtext_value);
						    new_value = 
							    cell_text_qm ? 
							    convert_text_to_text_string(1,
							    cell_text_qm) :
							     Nil;
						}
						else
						    new_value = Qnil;
						gensymed_symbol = 
							allocate_managed_array(1,
							FIX((SI_Long)10L + 
							(SI_Long)1L));
						gensymed_symbol_1 = 
							(SI_Long)0L;
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    svref_arg_2 = 
							    gensymed_symbol_1 
							    + 
							    IFIX(Managed_array_index_offset);
						    ISVREF(gensymed_symbol,
							    svref_arg_2) = 
							    FIX((SI_Long)1L);
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (gensymed_symbol_1 
							    >>  -  - 
							    (SI_Long)10L) 
							    + (SI_Long)2L);
						    svref_arg_2 = 
							    gensymed_symbol_1 
							    & (SI_Long)1023L;
						    ISVREF(temp_3,
							    svref_arg_2) = 
							    FIX((SI_Long)1L);
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size))
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)3L)) 
							    = Qattribute_name;
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    SVREF(temp_3,
							    FIX((SI_Long)1L)) 
							    = Qattribute_name;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    item_or_value = 
							    Qtable_cells;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    temp_3 = temp ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)4L)) 
							    = temp_3;
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    item_or_value = 
							    Qtable_cells;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    svref_new_value = temp 
							    ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(temp_3,
							    FIX((SI_Long)2L)) 
							    = svref_new_value;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size))
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)5L)) 
							    = Qrow_index;
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    SVREF(temp_3,
							    FIX((SI_Long)3L)) 
							    = Qrow_index;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    item_or_value = cell_x;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    temp_3 = temp ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)6L)) 
							    = temp_3;
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    item_or_value = cell_x;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    svref_new_value = temp 
							    ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(temp_3,
							    FIX((SI_Long)4L)) 
							    = svref_new_value;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size))
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)7L)) 
							    = Qcolumn_index;
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    SVREF(temp_3,
							    FIX((SI_Long)5L)) 
							    = Qcolumn_index;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    item_or_value = cell_y;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    temp_3 = temp ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)8L)) 
							    = temp_3;
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    item_or_value = cell_y;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    svref_new_value = temp 
							    ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(temp_3,
							    FIX((SI_Long)6L)) 
							    = svref_new_value;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size))
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)9L)) 
							    = 
							    Qcell_attribute_name;
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    SVREF(temp_3,
							    FIX((SI_Long)7L)) 
							    = 
							    Qcell_attribute_name;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    item_or_value = 
							    cell_attribute_name;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    temp_3 = temp ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)10L)) 
							    = temp_3;
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    item_or_value = 
							    cell_attribute_name;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    svref_new_value = temp 
							    ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(temp_3,
							    FIX((SI_Long)8L)) 
							    = svref_new_value;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size))
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)11L)) 
							    = Qnew_value;
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    SVREF(temp_3,
							    FIX((SI_Long)9L)) 
							    = Qnew_value;
						}
						if (FIXNUM_LE(ISVREF(gensymed_symbol,
							(SI_Long)1L),
							Maximum_in_place_array_size)) 
							    {
						    item_or_value = new_value;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    temp_3 = temp ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(gensymed_symbol,
							    FIX((SI_Long)12L)) 
							    = temp_3;
						}
						else {
						    temp_3 = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)2L);
						    item_or_value = new_value;
						    if (SIMPLE_VECTOR_P(item_or_value) 
							    && 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
							    > (SI_Long)2L 
							    &&  
							    !EQ(ISVREF(item_or_value,
							    (SI_Long)1L),
							    Qavailable_frame_vector)) 
								{
							x2 = 
								ISVREF(item_or_value,
								(SI_Long)1L);
							temp = 
								SIMPLE_VECTOR_P(x2) 
								&& 
								EQ(ISVREF(x2,
								(SI_Long)0L),
								Qg2_defstruct_structure_name_class_description_g2_struct) 
								? 
								TRUEP(x2) :
								 TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    svref_new_value = temp 
							    ? 
							    get_reference_to_item(item_or_value) 
							    : item_or_value;
						    SVREF(temp_3,
							    FIX((SI_Long)10L)) 
							    = svref_new_value;
						}
						temp_1 = 
							eval_cons_1(gensymed_symbol,
							Qab_structure);
					    }
					    else
						temp_1 = Nil;
					  POP_SPECIAL();
					  send_versioned_ws_notification_internal(Qitem_change,
						  temp_2,temp_1);
					  temp_2 = Current_lookup_data;
					POP_SPECIAL();
					SAVE_VALUES(VALUES_1(temp_2));
				    }
				    POP_UNWIND_PROTECT(0);
				    UNLOCK(Javalink_notification_versions);
				    CONTINUE_UNWINDING(0);
				    result = RESTORE_VALUES();
				    version_or_data = result;
				    M_CAR(current_list) = version_or_data;
				}
				if (javalink_versioned_call_data_sendp(version_or_data)) 
					    {
				    arg_lists = ISVREF(version_or_data,
					    (SI_Long)2L);
				    arg_list = Nil;
				    ab_loop_list__1 = arg_lists;
				    arg_list_to_send = Nil;
				  next_loop_9:
				    if ( !TRUEP(ab_loop_list__1))
					goto end_loop_8;
				    arg_list = M_CAR(ab_loop_list__1);
				    ab_loop_list__1 = M_CDR(ab_loop_list__1);
				    arg_list_to_send = 
					    javalink_versioning_make_arg_list_copy(arg_list,
					    subscription_handle);
				    callback_representation_fire_callback(representation,
					    socket_1,arg_list_to_send);
				    goto next_loop_9;
				  end_loop_8:;
				}
				goto end_4;
			    }
			    current_list = CDR(current_list);
			    goto next_loop_8;
			  end_loop_9:
			  end_4:;
			}
			goto next_loop_7;
		      end_loop_7:
			reclaim_gensym_list_1(representations);
			reclaim_frame_serial_number(current_frame_serial_number_on_entry);
			javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
			goto end_5;
		      end_5:;
		    }
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(1);
	      UNLOCK(Javalink_notification_versions);
	      CONTINUE_UNWINDING(1);
	  }
      }
      result = VALUES_1(cell_updated_qm);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* EXPRESSION-CELL-INDEX-TO-CELL-COORDINATES */
Object expression_cell_index_to_cell_coordinates varargs_1(int, n)
{
    Object index_1, new_table;
    Object cell_parts_too_qm, resulting_cell_qm, cell_part_name_qm;
    Object resulting_x, resulting_y, temp, row_parts, row_index, row_part;
    Object ab_loop_list_, cell_parts, column_index, cell_part, ab_loop_list__1;
    Object bg_color_qm, bg_color_expression_cell_index_qm, cell_contents_qm;
    Object compiled_cell_expression_qm, expression_cell_index_qm, is_bg_p;
    Object is_cell_contents_p;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,39);
    INIT_ARGS_nonrelocating();
    index_1 = REQUIRED_ARG_nonrelocating();
    new_table = REQUIRED_ARG_nonrelocating();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      cell_parts_too_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      END_ARGS_nonrelocating();
      resulting_cell_qm = Nil;
      cell_part_name_qm = Nil;
      resulting_x = Nil;
      resulting_y = Nil;
      temp = get_simple_part_feature(ISVREF(New_table,(SI_Long)18L),Qsubparts);
      row_parts = CADR(temp);
      row_index = FIX((SI_Long)0L);
      row_part = Nil;
      ab_loop_list_ = row_parts;
      cell_parts = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      row_part = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      temp = get_simple_part_feature(row_part,Qsubparts);
      cell_parts = CADR(temp);
      column_index = FIX((SI_Long)0L);
      cell_part = Nil;
      ab_loop_list__1 = cell_parts;
      bg_color_qm = Nil;
      bg_color_expression_cell_index_qm = Nil;
      cell_contents_qm = Nil;
      compiled_cell_expression_qm = Nil;
      expression_cell_index_qm = Nil;
      is_bg_p = Nil;
      is_cell_contents_p = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_part = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      bg_color_qm = get_simple_part_feature(cell_part,Qbackground_color);
      bg_color_expression_cell_index_qm = bg_color_qm && 
	      CONSP(bg_color_qm) ? get_simple_part_feature(bg_color_qm,
	      Qexpression_cell_index) : Qnil;
      cell_contents_qm = get_simple_part_feature(cell_part,Qcell_contents);
      compiled_cell_expression_qm = cell_contents_qm ? 
	      CAR(cell_contents_qm) : Qnil;
      expression_cell_index_qm = compiled_cell_expression_qm && 
	      EQ(CAR(compiled_cell_expression_qm),
	      Qcompiled_cell_expression) ? 
	      get_simple_part_feature(compiled_cell_expression_qm,
	      Qexpression_cell_index) : Qnil;
      is_bg_p = bg_color_expression_cell_index_qm ? 
	      (FIXNUM_EQ(bg_color_expression_cell_index_qm,index_1) ? T : 
	      Nil) : Qnil;
      is_cell_contents_p = expression_cell_index_qm ? 
	      (FIXNUM_EQ(expression_cell_index_qm,index_1) ? T : Nil) : Qnil;
      if (is_bg_p || is_cell_contents_p) {
	  resulting_x = row_index;
	  resulting_y = column_index;
	  if (cell_parts_too_qm) {
	      cell_part_name_qm = is_bg_p ? Qbackground_color : Qcell_contents;
	      resulting_cell_qm = cell_part;
	  }
	  goto end_1;
      }
      column_index = FIXNUM_ADD1(column_index);
      goto next_loop_1;
    end_loop_1:
    end_1:;
      if (resulting_x) {
	  result = VALUES_4(resulting_x,resulting_y,resulting_cell_qm,
		  cell_part_name_qm);
	  goto end_2;
      }
      row_index = FIXNUM_ADD1(row_index);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Postpone_cell_erase_until_redraw_p, Qpostpone_cell_erase_until_redraw_p);

DEFINE_VARIABLE_WITH_SYMBOL(Background_color_value_from_postponed_erase, Qbackground_color_value_from_postponed_erase);

DEFINE_VARIABLE_WITH_SYMBOL(Text_value_from_postponed_erase, Qtext_value_from_postponed_erase);

DEFINE_VARIABLE_WITH_SYMBOL(Reclaim_text_value_from_postponed_erase_p, Qreclaim_text_value_from_postponed_erase_p);

DEFINE_VARIABLE_WITH_SYMBOL(Updated_only_qm, Qupdated_only_qm);

/* COPY-TEXT-BOX-FORMAT */
Object copy_text_box_format(from,to)
    Object from, to;
{
    Object svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(178,40);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(array_dimension(from,FIX((SI_Long)0L)));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = ISVREF(from,i);
    ISVREF(to,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CELL-UPDATED */
Object cell_updated(new_table,cell_index,old_value_qm,new_value_qm)
    Object new_table, cell_index, old_value_qm, new_value_qm;
{
    Object projection_focus_method, projection_focus_cell_index;
    Object postpone_cell_erase_until_redraw_p;
    Object background_color_value_from_postponed_erase;
    Object text_value_from_postponed_erase;
    Object reclaim_text_value_from_postponed_erase_p, updated_only_qm, temp;
    Object expression_cell, projection_focus_cell_new_cached_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;
    Declare_special(9);
    Object result;

    x_note_fn_call(178,41);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,8);
      if (ISVREF(Drawing_parameters,(SI_Long)23L))
	  result = cell_updated_in_paint_mode(New_table,cell_index,
		  old_value_qm,new_value_qm);
      else {
	  projection_focus_method = Qcell;
	  projection_focus_cell_index = cell_index;
	  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_index,Qprojection_focus_cell_index,projection_focus_cell_index,
		  7);
	    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
		    6);
	      postpone_cell_erase_until_redraw_p =  ! !TRUEP(new_value_qm) 
		      ? T : Nil;
	      background_color_value_from_postponed_erase = Nil;
	      text_value_from_postponed_erase = Nil;
	      reclaim_text_value_from_postponed_erase_p = Nil;
	      updated_only_qm = T;
	      PUSH_SPECIAL_WITH_SYMBOL(Updated_only_qm,Qupdated_only_qm,updated_only_qm,
		      5);
		PUSH_SPECIAL_WITH_SYMBOL(Reclaim_text_value_from_postponed_erase_p,Qreclaim_text_value_from_postponed_erase_p,reclaim_text_value_from_postponed_erase_p,
			4);
		  PUSH_SPECIAL_WITH_SYMBOL(Text_value_from_postponed_erase,Qtext_value_from_postponed_erase,text_value_from_postponed_erase,
			  3);
		    PUSH_SPECIAL_WITH_SYMBOL(Background_color_value_from_postponed_erase,Qbackground_color_value_from_postponed_erase,background_color_value_from_postponed_erase,
			    2);
		      PUSH_SPECIAL_WITH_SYMBOL(Postpone_cell_erase_until_redraw_p,Qpostpone_cell_erase_until_redraw_p,postpone_cell_erase_until_redraw_p,
			      1);
			if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(New_table,
				Qcell_array,Nil),(SI_Long)3L),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    temp = 
				    ISVREF(get_lookup_slot_value_given_default(New_table,
				    Qcell_array,Nil),(SI_Long)3L);
			    expression_cell = ISVREF(temp,
				    IFIX(FIXNUM_ADD(cell_index,
				    Managed_array_index_offset)));
			}
			else {
			    temp = 
				    ISVREF(get_lookup_slot_value_given_default(New_table,
				    Qcell_array,Nil),(SI_Long)3L);
			    expression_cell = ISVREF(ISVREF(temp,
				    (IFIX(cell_index) >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    IFIX(cell_index) & (SI_Long)1023L);
			}
			ISVREF(expression_cell,(SI_Long)6L) = old_value_qm;
			erase_entire_annotated_block(New_table);
			ISVREF(expression_cell,(SI_Long)6L) = new_value_qm;
			projection_focus_cell_new_cached_value = new_value_qm;
			PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_new_cached_value,Qprojection_focus_cell_new_cached_value,projection_focus_cell_new_cached_value,
				0);
			  gensymed_symbol = 
				  ISVREF(ISVREF(ISVREF(ISVREF(New_table,
				  (SI_Long)1L),(SI_Long)11L),(SI_Long)46L),
				  (SI_Long)1L);
			  gensymed_symbol_1 = New_table;
			  gensymed_symbol_2 = Qcell;
			  gensymed_symbol_3 = cell_index;
			  inline_funcall_3(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2,
				  gensymed_symbol_3);
			POP_SPECIAL();
			redraw_entire_annotated_block();
			if (Reclaim_text_value_from_postponed_erase_p && 
				Text_value_from_postponed_erase)
			    reclaim_slot_value(Text_value_from_postponed_erase);
			if (Background_color_value_from_postponed_erase) {
			    reclaim_gensym_tree_1(Background_color_value_from_postponed_erase);
			    Background_color_value_from_postponed_erase = Nil;
			    result = VALUES_1(Background_color_value_from_postponed_erase);
			}
			else
			    result = VALUES_1(Nil);
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Off_window_color_map, Qoff_window_color_map);

/* INITIALIZE-OFF-WINDOW-COLOR-MAP */
Object initialize_off_window_color_map()
{
    x_note_fn_call(178,42);
    return make_color_map(FIX((SI_Long)8L),
	    make_monochrome_color_description_plist(FIX((SI_Long)1L),
	    FIX((SI_Long)0L)));
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qinvalidate_projection_mode;  /* invalidate-projection-mode */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* CELL-UPDATED-IN-PAINT-MODE */
Object cell_updated_in_paint_mode(new_table,cell_index,old_value_qm,
	    new_value_qm)
    Object new_table, cell_index, old_value_qm, new_value_qm;
{
    Object temp, expression_cell, projection_focus_method;
    Object projection_focus_cell_index, projection_focus_cell_new_cached_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, workspace_qm, current_drawing_priority;
    Object current_annotated_frame, projection_mode, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_background_color_value;
    Object current_foreground_color_value, current_color_map;
    Object current_kind_of_change, current_thing_changed;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(15);
    Object result;

    x_note_fn_call(178,43);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,14);
      if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(New_table,
	      Qcell_array,Nil),(SI_Long)3L),(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  temp = ISVREF(get_lookup_slot_value_given_default(New_table,
		  Qcell_array,Nil),(SI_Long)3L);
	  expression_cell = ISVREF(temp,IFIX(FIXNUM_ADD(cell_index,
		  Managed_array_index_offset)));
      }
      else {
	  temp = ISVREF(get_lookup_slot_value_given_default(New_table,
		  Qcell_array,Nil),(SI_Long)3L);
	  expression_cell = ISVREF(ISVREF(temp,(IFIX(cell_index) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),IFIX(cell_index) & 
		  (SI_Long)1023L);
      }
      ISVREF(expression_cell,(SI_Long)6L) = new_value_qm;
      projection_focus_method = Qcell;
      projection_focus_cell_index = cell_index;
      projection_focus_cell_new_cached_value = new_value_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_new_cached_value,Qprojection_focus_cell_new_cached_value,projection_focus_cell_new_cached_value,
	      2);
	PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_index,Qprojection_focus_cell_index,projection_focus_cell_index,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
		  0);
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(New_table,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)46L),(SI_Long)1L);
	    gensymed_symbol_1 = New_table;
	    gensymed_symbol_2 = Qcell;
	    gensymed_symbol_3 = cell_index;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      workspace_qm = get_workspace_if_any(New_table);
      if (workspace_qm) {
	  current_drawing_priority = Kdraw_as_late_as_possible;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		  13);
	    LOCK(Working_on_annotated_frame);
	    if (PUSH_UNWIND_PROTECT(1)) {
		current_annotated_frame = New_table;
		PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			12);
		  LOCK(Projection_drawing);
		  if (PUSH_UNWIND_PROTECT(0)) {
		      projection_mode = Qinvalidate_projection_mode;
		      PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			      11);
			current_image_x_scale = FIX((SI_Long)4096L);
			current_image_y_scale = FIX((SI_Long)4096L);
			current_x_origin_of_drawing = FIX((SI_Long)0L);
			current_y_origin_of_drawing = FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
				10);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				  9);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				    8);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				      7);
				current_background_color_value = 
					FIX((SI_Long)0L);
				current_foreground_color_value = 
					FIX((SI_Long)0L);
				current_color_map = Off_window_color_map;
				PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					6);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					  5);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					    4);
				      projection_focus_method = Qcell;
				      projection_focus_cell_index = cell_index;
				      current_kind_of_change = Qcell;
				      current_thing_changed = cell_index;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_thing_changed,Qcurrent_thing_changed,current_thing_changed,
					      3);
					PUSH_SPECIAL_WITH_SYMBOL(Current_kind_of_change,Qcurrent_kind_of_change,current_kind_of_change,
						2);
					  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_index,Qprojection_focus_cell_index,projection_focus_cell_index,
						  1);
					    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
						    0);
					      project_new_table();
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
		  UNLOCK(Projection_drawing);
		  CONTINUE_UNWINDING(0);
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(1);
	    UNLOCK(Working_on_annotated_frame);
	    CONTINUE_UNWINDING(1);
	  POP_SPECIAL();
	  if (EQ(Current_drawing_priority,Kdraw_as_soon_as_possible))
	      result = force_process_drawing();
	  else
	      result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qcompute_path_of_focus_projection_mode;  /* compute-path-of-focus-projection-mode */

/* PLACE-REFERENCE-OF-CELL-FOR-NEW-TABLE */
Object place_reference_of_cell_for_new_table(new_table,cell_index)
    Object new_table, cell_index;
{
    Object current_annotated_frame, projection_mode, projection_focus_method;
    Object projection_focus_cell_index, projection_focus_path;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_background_color_value, current_foreground_color_value;
    Object current_color_map, component_accessor;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(13);
    Object result;

    x_note_fn_call(178,44);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,12);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_annotated_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  11);
	    LOCK(Projection_computing_path_of_focus);
	    if (PUSH_UNWIND_PROTECT(0)) {
		projection_mode = Qcompute_path_of_focus_projection_mode;
		projection_focus_method = Qcell;
		projection_focus_cell_index = cell_index;
		projection_focus_path = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_path,Qprojection_focus_path,projection_focus_path,
			10);
		  PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_cell_index,Qprojection_focus_cell_index,projection_focus_cell_index,
			  9);
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
			    8);
		      PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			      7);
			current_image_x_scale = FIX((SI_Long)4096L);
			current_image_y_scale = FIX((SI_Long)4096L);
			current_x_origin_of_drawing = FIX((SI_Long)0L);
			current_y_origin_of_drawing = FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
				6);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				  5);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				    4);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				      3);
				current_background_color_value = 
					FIX((SI_Long)0L);
				current_foreground_color_value = 
					FIX((SI_Long)0L);
				current_color_map = Off_window_color_map;
				PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					2);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					  1);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					    0);
				      project_new_table();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			component_accessor = 
				convert_path_to_expression(Projection_focus_path,
				Qcurrent_computation_frame);
			SAVE_VALUES(make_evaluation_place_reference_to_place(component_accessor,
				New_table));
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Projection_computing_path_of_focus);
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant;      /* # */

static Object string_constant_8;   /* " of " */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-NEW-TABLE */
Object denote_cell_array_element_for_new_table(new_table,cell_index,
	    include_denotation_for_block)
    Object new_table, cell_index, include_denotation_for_block;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object place_reference, component_accessor;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,45);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      if (EQL(cell_index,Cell_index_currently_being_registered)) {
	  twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)29L));
	  result = denote_component_of_block_1(Qcurrent_computation_frame,
		  string_constant_8);
      }
      else {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(New_table,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)36L),(SI_Long)1L);
	  gensymed_symbol_1 = New_table;
	  gensymed_symbol_2 = cell_index;
	  place_reference = inline_funcall_2(gensymed_symbol,
		  gensymed_symbol_1,gensymed_symbol_2);
	  component_accessor = ISVREF(M_CAR(place_reference),(SI_Long)0L);
	  denote_component_of_block(2,include_denotation_for_block,
		  component_accessor);
	  result = reclaim_evaluation_place_reference(place_reference);
      }
    POP_SPECIAL();
    return result;
}

/* RECOMPILE-EXPRESSION-AT-COMPONENT-PARTICULARS-FOR-NEW-TABLE */
Object recompile_expression_at_component_particulars_for_new_table(new_table,
	    component_particulars)
    Object new_table, component_particulars;
{
    Object temp, gensymed_symbol, parent_component_particulars, part_feature;
    Object current_computation_frame, parent_part_description;
    Object current_annotated_frame, current_block_of_dependent_frame;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(5);
    Object result;

    x_note_fn_call(178,46);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,4);
      temp = THIRD(component_particulars);
      if (CONSP(temp)) {
	  gensymed_symbol = component_particulars;
	  gensymed_symbol = CDR(gensymed_symbol);
	  parent_component_particulars = CAR(gensymed_symbol);
	  gensymed_symbol = CDR(gensymed_symbol);
	  gensymed_symbol = CAR(gensymed_symbol);
	  gensymed_symbol = CDR(gensymed_symbol);
	  part_feature = CAR(gensymed_symbol);
	  current_computation_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  3);
	    parent_part_description = 
		    simple_eval(parent_component_particulars);
	    if (parent_part_description && 
		    get_simple_part_feature(parent_part_description,
		    part_feature)) {
		LOCK(Working_on_annotated_frame);
		if (PUSH_UNWIND_PROTECT(1)) {
		    current_annotated_frame = New_table;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
			    2);
		      current_block_of_dependent_frame = New_table;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
			      1);
			LOCK(Working_on_new_table);
			if (PUSH_UNWIND_PROTECT(0)) {
			    current_annotated_frame = New_table;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
				    0);
			      if (EQ(part_feature,Qcell_contents))
				  SAVE_VALUES(recompile_component_of_part_description(parent_part_description,
					  part_feature,
					  Qcell_expression_and_text));
			      else if (EQ(part_feature,Qbackground_color))
				  SAVE_VALUES(recompile_component_of_part_description(parent_part_description,
					  T,Qcell_format));
			      else
				  SAVE_VALUES(VALUES_1(Nil));
			    POP_SPECIAL();
			}
			POP_UNWIND_PROTECT(0);
			UNLOCK(Working_on_new_table);
			CONTINUE_UNWINDING(0);
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(1);
		UNLOCK(Working_on_annotated_frame);
		CONTINUE_UNWINDING(1);
		result = RESTORE_VALUES();
	    }
	    else
		result = VALUES_1(Qt);
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qit;                 /* it */

/* CONVERT-PATH-TO-EXPRESSION */
Object convert_path_to_expression(path,root)
    Object path, root;
{
    Object result_1, reversed_path, step, ab_loop_list_, p;

    x_note_fn_call(178,47);
    result_1 = root;
    reversed_path = nreverse(path);
    step = Nil;
    ab_loop_list_ = reversed_path;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    step = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    p = step;
  next_loop_1:
    if ( !TRUEP(p))
	goto end_loop_1;
    if (EQ(Qit,CAR(p)))
	M_CAR(p) = result_1;
    p = M_CDR(p);
    goto next_loop_1;
  end_loop_1:;
    result_1 = step;
    goto next_loop;
  end_loop:
    reclaim_slot_value_list_1(reversed_path);
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object Qdraw_projection_mode;  /* draw-projection-mode */

/* DRAW-FOR-NEW-TABLE */
Object draw_for_new_table(new_table)
    Object new_table;
{
    Object current_annotated_frame, projection_mode;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(3);
    Object result;

    x_note_fn_call(178,48);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,2);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_annotated_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  1);
	    LOCK(Projection_drawing);
	    if (PUSH_UNWIND_PROTECT(0)) {
		projection_mode = Qdraw_projection_mode;
		PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			0);
		  SAVE_VALUES(project_new_table());
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Projection_drawing);
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qtracking_projection_mode;  /* tracking-projection-mode */

/* TRACK-MOUSE-FOR-NEW-TABLE */
Object track_mouse_for_new_table(x_in_window,y_in_window,get_subpart_p)
    Object x_in_window, y_in_window, get_subpart_p;
{
    Object row, column;
    volatile Object subpart_description_qm;
    Object projection_mode, current_tracking_x_in_window;
    Object current_tracking_y_in_window, create_subpart_upon_tracking_p;
    Object current_tracking_subcomponent;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(178,49);
    SAVE_STACK();
    row = Nil;
    column = Nil;
    subpart_description_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,6);
      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,5);
	LOCK(Projection_tracking);
	if (PUSH_UNWIND_PROTECT(0)) {
	    projection_mode = Qtracking_projection_mode;
	    current_tracking_x_in_window = x_in_window;
	    current_tracking_y_in_window = y_in_window;
	    create_subpart_upon_tracking_p = get_subpart_p;
	    current_tracking_subcomponent = slot_value_list_3(Nil,Nil,Nil);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_tracking_subcomponent,Qcurrent_tracking_subcomponent,current_tracking_subcomponent,
		    4);
	      PUSH_SPECIAL_WITH_SYMBOL(Create_subpart_upon_tracking_p,Qcreate_subpart_upon_tracking_p,create_subpart_upon_tracking_p,
		      3);
		PUSH_SPECIAL_WITH_SYMBOL(Current_tracking_y_in_window,Qcurrent_tracking_y_in_window,current_tracking_y_in_window,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_tracking_x_in_window,Qcurrent_tracking_x_in_window,current_tracking_x_in_window,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			    0);
		      project_new_table();
		      Row = FIRST(Current_tracking_subcomponent);
		      Column = SECOND(Current_tracking_subcomponent);
		      subpart_description_qm = 
			      THIRD(Current_tracking_subcomponent);
		      reclaim_slot_value_list_1(Current_tracking_subcomponent);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Projection_tracking);
	CONTINUE_UNWINDING(0);
	result = VALUES_4(Current_annotated_frame,Row,Column,
		subpart_description_qm);
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

Object The_type_description_of_new_table_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_new_table_spots, Qchain_of_available_new_table_spots);

DEFINE_VARIABLE_WITH_SYMBOL(New_table_spot_count, Qnew_table_spot_count);

Object Chain_of_available_new_table_spots_vector = UNBOUND;

/* NEW-TABLE-SPOT-STRUCTURE-MEMORY-USAGE */
Object new_table_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(178,50);
    temp = New_table_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NEW-TABLE-SPOT-COUNT */
Object outstanding_new_table_spot_count()
{
    Object def_structure_new_table_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(178,51);
    gensymed_symbol = IFIX(New_table_spot_count);
    def_structure_new_table_spot_variable = Chain_of_available_new_table_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_new_table_spot_variable))
	goto end_loop;
    def_structure_new_table_spot_variable = 
	    ISVREF(def_structure_new_table_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-NEW-TABLE-SPOT-1 */
Object reclaim_new_table_spot_1(new_table_spot)
    Object new_table_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(178,52);
    inline_note_reclaim_cons(new_table_spot,Nil);
    structure_being_reclaimed = new_table_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(new_table_spot,(SI_Long)2L));
      SVREF(new_table_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_new_table_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(new_table_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_new_table_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = new_table_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NEW-TABLE-SPOT */
Object reclaim_structure_for_new_table_spot(new_table_spot)
    Object new_table_spot;
{
    x_note_fn_call(178,53);
    return reclaim_new_table_spot_1(new_table_spot);
}

static Object Qg2_defstruct_structure_name_new_table_spot_g2_struct;  /* g2-defstruct-structure-name::new-table-spot-g2-struct */

/* MAKE-PERMANENT-NEW-TABLE-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_new_table_spot_structure_internal()
{
    Object def_structure_new_table_spot_variable;
    Object defstruct_g2_new_table_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(178,54);
    def_structure_new_table_spot_variable = Nil;
    atomic_incff_symval(Qnew_table_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_new_table_spot_variable = Nil;
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
	defstruct_g2_new_table_spot_variable = the_array;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_new_table_spot_g2_struct;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_new_table_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_new_table_spot_variable = 
		defstruct_g2_new_table_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_new_table_spot_variable);
}

/* MAKE-NEW-TABLE-SPOT-1 */
Object make_new_table_spot_1()
{
    Object def_structure_new_table_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(178,55);
    def_structure_new_table_spot_variable = 
	    ISVREF(Chain_of_available_new_table_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_new_table_spot_variable) {
	svref_arg_1 = Chain_of_available_new_table_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_new_table_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_new_table_spot_g2_struct;
    }
    else
	def_structure_new_table_spot_variable = 
		make_permanent_new_table_spot_structure_internal();
    inline_note_allocate_cons(def_structure_new_table_spot_variable,Nil);
    SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_new_table_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_new_table_spot_variable);
}

Object The_type_description_of_new_table_cell_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_new_table_cell_spots, Qchain_of_available_new_table_cell_spots);

DEFINE_VARIABLE_WITH_SYMBOL(New_table_cell_spot_count, Qnew_table_cell_spot_count);

Object Chain_of_available_new_table_cell_spots_vector = UNBOUND;

/* NEW-TABLE-CELL-SPOT-STRUCTURE-MEMORY-USAGE */
Object new_table_cell_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(178,56);
    temp = New_table_cell_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NEW-TABLE-CELL-SPOT-COUNT */
Object outstanding_new_table_cell_spot_count()
{
    Object def_structure_new_table_cell_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(178,57);
    gensymed_symbol = IFIX(New_table_cell_spot_count);
    def_structure_new_table_cell_spot_variable = 
	    Chain_of_available_new_table_cell_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_new_table_cell_spot_variable))
	goto end_loop;
    def_structure_new_table_cell_spot_variable = 
	    ISVREF(def_structure_new_table_cell_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-NEW-TABLE-CELL-SPOT-1 */
Object reclaim_new_table_cell_spot_1(new_table_cell_spot)
    Object new_table_cell_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(178,58);
    inline_note_reclaim_cons(new_table_cell_spot,Nil);
    structure_being_reclaimed = new_table_cell_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(new_table_cell_spot,(SI_Long)2L));
      SVREF(new_table_cell_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_new_table_cell_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(new_table_cell_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_new_table_cell_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = new_table_cell_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NEW-TABLE-CELL-SPOT */
Object reclaim_structure_for_new_table_cell_spot(new_table_cell_spot)
    Object new_table_cell_spot;
{
    x_note_fn_call(178,59);
    return reclaim_new_table_cell_spot_1(new_table_cell_spot);
}

static Object Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct;  /* g2-defstruct-structure-name::new-table-cell-spot-g2-struct */

/* MAKE-PERMANENT-NEW-TABLE-CELL-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_new_table_cell_spot_structure_internal()
{
    Object def_structure_new_table_cell_spot_variable;
    Object defstruct_g2_new_table_cell_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(178,60);
    def_structure_new_table_cell_spot_variable = Nil;
    atomic_incff_symval(Qnew_table_cell_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_new_table_cell_spot_variable = Nil;
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
	defstruct_g2_new_table_cell_spot_variable = the_array;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_new_table_cell_spot_variable,FIX((SI_Long)5L)) 
		= Nil;
	def_structure_new_table_cell_spot_variable = 
		defstruct_g2_new_table_cell_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_new_table_cell_spot_variable);
}

/* MAKE-NEW-TABLE-CELL-SPOT-1 */
Object make_new_table_cell_spot_1()
{
    Object def_structure_new_table_cell_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(178,61);
    def_structure_new_table_cell_spot_variable = 
	    ISVREF(Chain_of_available_new_table_cell_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_new_table_cell_spot_variable) {
	svref_arg_1 = Chain_of_available_new_table_cell_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_new_table_cell_spot_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct;
    }
    else
	def_structure_new_table_cell_spot_variable = 
		make_permanent_new_table_cell_spot_structure_internal();
    inline_note_allocate_cons(def_structure_new_table_cell_spot_variable,Nil);
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_new_table_cell_spot_variable,FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_new_table_cell_spot_variable);
}

Object The_type_description_of_new_table_background_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_new_table_background_spots, Qchain_of_available_new_table_background_spots);

DEFINE_VARIABLE_WITH_SYMBOL(New_table_background_spot_count, Qnew_table_background_spot_count);

Object Chain_of_available_new_table_background_spots_vector = UNBOUND;

/* NEW-TABLE-BACKGROUND-SPOT-STRUCTURE-MEMORY-USAGE */
Object new_table_background_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(178,62);
    temp = New_table_background_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NEW-TABLE-BACKGROUND-SPOT-COUNT */
Object outstanding_new_table_background_spot_count()
{
    Object def_structure_new_table_background_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(178,63);
    gensymed_symbol = IFIX(New_table_background_spot_count);
    def_structure_new_table_background_spot_variable = 
	    Chain_of_available_new_table_background_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_new_table_background_spot_variable))
	goto end_loop;
    def_structure_new_table_background_spot_variable = 
	    ISVREF(def_structure_new_table_background_spot_variable,
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

/* RECLAIM-NEW-TABLE-BACKGROUND-SPOT-1 */
Object reclaim_new_table_background_spot_1(new_table_background_spot)
    Object new_table_background_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(178,64);
    inline_note_reclaim_cons(new_table_background_spot,Nil);
    structure_being_reclaimed = new_table_background_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(new_table_background_spot,(SI_Long)2L));
      SVREF(new_table_background_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_new_table_background_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(new_table_background_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_new_table_background_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = new_table_background_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NEW-TABLE-BACKGROUND-SPOT */
Object reclaim_structure_for_new_table_background_spot(new_table_background_spot)
    Object new_table_background_spot;
{
    x_note_fn_call(178,65);
    return reclaim_new_table_background_spot_1(new_table_background_spot);
}

static Object Qg2_defstruct_structure_name_new_table_background_spot_g2_struct;  /* g2-defstruct-structure-name::new-table-background-spot-g2-struct */

/* MAKE-PERMANENT-NEW-TABLE-BACKGROUND-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_new_table_background_spot_structure_internal()
{
    Object def_structure_new_table_background_spot_variable;
    Object defstruct_g2_new_table_background_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(178,66);
    def_structure_new_table_background_spot_variable = Nil;
    atomic_incff_symval(Qnew_table_background_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_new_table_background_spot_variable = Nil;
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
	defstruct_g2_new_table_background_spot_variable = the_array;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_new_table_background_spot_g2_struct;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_new_table_background_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_new_table_background_spot_variable = 
		defstruct_g2_new_table_background_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_new_table_background_spot_variable);
}

/* MAKE-NEW-TABLE-BACKGROUND-SPOT-1 */
Object make_new_table_background_spot_1()
{
    Object def_structure_new_table_background_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(178,67);
    def_structure_new_table_background_spot_variable = 
	    ISVREF(Chain_of_available_new_table_background_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_new_table_background_spot_variable) {
	svref_arg_1 = Chain_of_available_new_table_background_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_new_table_background_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_new_table_background_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_new_table_background_spot_g2_struct;
    }
    else
	def_structure_new_table_background_spot_variable = 
		make_permanent_new_table_background_spot_structure_internal();
    inline_note_allocate_cons(def_structure_new_table_background_spot_variable,
	    Nil);
    SVREF(def_structure_new_table_background_spot_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_new_table_background_spot_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_new_table_background_spot_variable,
	    FIX((SI_Long)3L)) = T;
    SVREF(def_structure_new_table_background_spot_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_new_table_background_spot_variable,
	    FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_new_table_background_spot_variable);
}

static Object Kxor;                /* :xor */

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

static Object Qtransparent;        /* transparent */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

/* GENERATE-SPOT-FOR-NEW-TABLE */
Object generate_spot_for_new_table(new_table,mouse_pointer)
    Object new_table, mouse_pointer;
{
    Object image_plane, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, temp;
    Object current_window_1, drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, current_annotated_frame, temp_1;
    Object row_qm, column_qm, subpart_description_qm, new_table_spot;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(27);
    Object result;

    x_note_fn_call(178,68);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,26);
      image_plane = image_plane_of_mouse_pointer(mouse_pointer);
      left_edge_of_draw_area = Left_edge_of_draw_area;
      top_edge_of_draw_area = Top_edge_of_draw_area;
      right_edge_of_draw_area = Right_edge_of_draw_area;
      bottom_edge_of_draw_area = Bottom_edge_of_draw_area;
      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
	      25);
	PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		24);
	  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		  23);
	    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		    22);
	      temp = left_edge_within_pane(ISVREF(image_plane,
		      (SI_Long)19L),image_plane);
	      Left_edge_of_draw_area = FIXNUM_MAX(temp,Left_edge_of_draw_area);
	      temp = top_edge_within_pane(ISVREF(image_plane,(SI_Long)20L),
		      image_plane);
	      Top_edge_of_draw_area = FIXNUM_MAX(temp,Top_edge_of_draw_area);
	      temp = right_edge_within_pane(ISVREF(image_plane,
		      (SI_Long)21L),image_plane);
	      Right_edge_of_draw_area = FIXNUM_MIN(temp,
		      Right_edge_of_draw_area);
	      temp = bottom_edge_within_pane(ISVREF(image_plane,
		      (SI_Long)22L),image_plane);
	      Bottom_edge_of_draw_area = FIXNUM_MIN(temp,
		      Bottom_edge_of_draw_area);
	      if (FIXNUM_LT(Left_edge_of_draw_area,
		      Right_edge_of_draw_area) && 
		      FIXNUM_LT(Top_edge_of_draw_area,
		      Bottom_edge_of_draw_area)) {
		  LOCK(On_window_without_drawing);
		  if (PUSH_UNWIND_PROTECT(3)) {
		      current_window_1 = ISVREF(ISVREF(image_plane,
			      (SI_Long)2L),(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
			      21);
			drawing_on_window = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				20);
			  current_drawing_transfer_mode = 
				  EQ(Current_drawing_transfer_mode,Kxor) ? 
				  Current_drawing_transfer_mode : 
				  ISVREF(Current_window,(SI_Long)30L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
				  19);
			    type_of_current_window = ISVREF(Current_window,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
				    18);
			      current_native_window_qm = 
				      ISVREF(Current_window,(SI_Long)17L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
				      17);
				current_color_map = ISVREF(Current_window,
					(SI_Long)20L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					16);
				  temp = ISVREF(Current_color_map,(SI_Long)5L);
				  if (temp);
				  else
				      temp = map_to_color_value_1(Qwhite);
				  current_background_color_value = temp;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					  15);
				    temp = ISVREF(Current_color_map,
					    (SI_Long)4L);
				    if (temp);
				    else
					temp = map_to_color_value_1(Qblack);
				    current_foreground_color_value = temp;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					    14);
				      current_frame_transform_qm = Nil;
				      current_image_x_scale = 
					      ISVREF(image_plane,(SI_Long)11L);
				      current_image_y_scale = 
					      ISVREF(image_plane,(SI_Long)12L);
				      current_x_origin_of_drawing = 
					      ISVREF(image_plane,(SI_Long)13L);
				      current_y_origin_of_drawing = 
					      ISVREF(image_plane,(SI_Long)14L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
					      13);
					PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
						12);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
						  11);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
						    10);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
						      9);
						LOCK(For_image_plane);
						if (PUSH_UNWIND_PROTECT(2)) {
						    current_pane = 
							    ISVREF(image_plane,
							    (SI_Long)2L);
						    current_image_plane = 
							    image_plane;
						    loose_left_edge_of_visible_workspace_area 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)23L);
						    loose_top_edge_of_visible_workspace_area 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)24L);
						    loose_right_edge_of_visible_workspace_area 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)25L);
						    loose_bottom_edge_of_visible_workspace_area 
							    = 
							    ISVREF(image_plane,
							    (SI_Long)26L);
						    color_or_metacolor = 
							    ISVREF(image_plane,
							    (SI_Long)5L) ? 
							    ISVREF(ISVREF(image_plane,
							    (SI_Long)5L),
							    (SI_Long)22L) :
							     Nil;
						    if (color_or_metacolor);
						    else
							color_or_metacolor 
								= Qblack;
						    if (EQ(color_or_metacolor,
							    Qtransparent) 
							    || 
							    EQ(color_or_metacolor,
							    Qbackground)) {
							background_color_or_metacolor 
								= 
								ISVREF(image_plane,
								(SI_Long)5L) 
								? 
								ISVREF(ISVREF(image_plane,
								(SI_Long)5L),
								(SI_Long)21L) 
								: Nil;
							if (background_color_or_metacolor);
							else
							    background_color_or_metacolor 
								    = Qwhite;
							if (EQ(background_color_or_metacolor,
								Qforeground) 
								|| 
								EQ(background_color_or_metacolor,
								Qworkspace_foreground)) 
								    {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)4L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qblack);
							    current_foreground_color_value 
								    = temp;
							}
							else if (EQ(background_color_or_metacolor,
								Qtransparent) 
								|| 
								EQ(background_color_or_metacolor,
								Qbackground)) {
							    temp = 
								    ISVREF(Current_color_map,
								    (SI_Long)5L);
							    if (temp);
							    else
								temp = 
									map_to_color_value_1(Qwhite);
							    current_foreground_color_value 
								    = temp;
							}
							else
							    current_foreground_color_value 
								    = 
								    EQ(background_color_or_metacolor,
								    ISVREF(Current_color_map,
								    (SI_Long)6L)) 
								    ? 
								    ISVREF(Current_color_map,
								    (SI_Long)7L) 
								    : 
								    map_to_color_value_1(background_color_or_metacolor);
						    }
						    else if (EQ(color_or_metacolor,
							    Qforeground) 
							    || 
							    EQ(color_or_metacolor,
							    Qworkspace_foreground)) 
								{
							temp = 
								ISVREF(Current_color_map,
								(SI_Long)4L);
							if (temp);
							else
							    temp = 
								    map_to_color_value_1(Qblack);
							current_foreground_color_value 
								= temp;
						    }
						    else
							current_foreground_color_value 
								= 
								EQ(color_or_metacolor,
								ISVREF(Current_color_map,
								(SI_Long)6L)) 
								? 
								ISVREF(Current_color_map,
								(SI_Long)7L) 
								: 
								map_to_color_value_1(color_or_metacolor);
						    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
							    8);
						      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
							      7);
							PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
								6);
							  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
								  5);
							    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
								    4);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
								      3);
								PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
									2);
								  color_or_metacolor 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)5L) 
									  ?
									   
									  ISVREF(ISVREF(image_plane,
									  (SI_Long)5L),
									  (SI_Long)21L) 
									  :
									   Nil;
								  if (color_or_metacolor);
								  else
								      color_or_metacolor 
									      = 
									      Qwhite;
								  if (EQ(color_or_metacolor,
									  Qtransparent) 
									  || 
									  EQ(color_or_metacolor,
									  Qbackground)) 
									      {
								      temp 
									      = 
									      ISVREF(Current_color_map,
									      (SI_Long)5L);
								      if (temp);
								      else
									  temp 
										  = 
										  map_to_color_value_1(Qwhite);
								      current_background_color_value 
									      = 
									      temp;
								  }
								  else if (EQ(color_or_metacolor,
									  Qforeground) 
									  || 
									  EQ(color_or_metacolor,
									  Qworkspace_foreground)) 
									      {
								      temp 
									      = 
									      ISVREF(image_plane,
									      (SI_Long)5L) 
									      ?
									       
									      ISVREF(ISVREF(image_plane,
									      (SI_Long)5L),
									      (SI_Long)22L) 
									      :
									       
									      Nil;
								      if (temp);
								      else
									  temp 
										  = 
										  Qblack;
								      color_or_metacolor 
									      = 
									      temp;
								      if (EQ(color_or_metacolor,
									      Qtransparent) 
									      || 
									      EQ(color_or_metacolor,
									      Qbackground)) 
										  {
									  background_color_or_metacolor 
										  = 
										  ISVREF(image_plane,
										  (SI_Long)5L) 
										  ?
										   
										  ISVREF(ISVREF(image_plane,
										  (SI_Long)5L),
										  (SI_Long)21L) 
										  :
										   
										  Nil;
									  if (background_color_or_metacolor);
									  else
									      background_color_or_metacolor 
										      = 
										      Qwhite;
									  if (EQ(background_color_or_metacolor,
										  Qforeground) 
										  || 
										  EQ(background_color_or_metacolor,
										  Qworkspace_foreground)) 
										      {
									      temp 
										      = 
										      ISVREF(Current_color_map,
										      (SI_Long)4L);
									      if (temp);
									      else
										  temp 
											  = 
											  map_to_color_value_1(Qblack);
									      current_background_color_value 
										      = 
										      temp;
									  }
									  else if (EQ(background_color_or_metacolor,
										  Qtransparent) 
										  || 
										  EQ(background_color_or_metacolor,
										  Qbackground)) 
										      {
									      temp 
										      = 
										      ISVREF(Current_color_map,
										      (SI_Long)5L);
									      if (temp);
									      else
										  temp 
											  = 
											  map_to_color_value_1(Qwhite);
									      current_background_color_value 
										      = 
										      temp;
									  }
									  else
									      current_background_color_value 
										      = 
										      EQ(background_color_or_metacolor,
										      ISVREF(Current_color_map,
										      (SI_Long)6L)) 
										      ?
										       
										      ISVREF(Current_color_map,
										      (SI_Long)7L) 
										      :
										       
										      map_to_color_value_1(background_color_or_metacolor);
								      }
								      else if (EQ(color_or_metacolor,
									      Qforeground) 
									      || 
									      EQ(color_or_metacolor,
									      Qworkspace_foreground)) 
										  {
									  temp 
										  = 
										  ISVREF(Current_color_map,
										  (SI_Long)4L);
									  if (temp);
									  else
									      temp 
										      = 
										      map_to_color_value_1(Qblack);
									  current_background_color_value 
										  = 
										  temp;
								      }
								      else
									  current_background_color_value 
										  = 
										  EQ(color_or_metacolor,
										  ISVREF(Current_color_map,
										  (SI_Long)6L)) 
										  ?
										   
										  ISVREF(Current_color_map,
										  (SI_Long)7L) 
										  :
										   
										  map_to_color_value_1(color_or_metacolor);
								  }
								  else
								      current_background_color_value 
									      = 
									      EQ(color_or_metacolor,
									      ISVREF(Current_color_map,
									      (SI_Long)6L)) 
									      ?
									       
									      ISVREF(Current_color_map,
									      (SI_Long)7L) 
									      :
									       
									      map_to_color_value_1(color_or_metacolor);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
									  1);
								    LOCK(Working_on_annotated_frame);
								    if (PUSH_UNWIND_PROTECT(1)) 
										{
									current_annotated_frame 
										= 
										New_table;
									PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
										0);
									  LOCK(Working_on_new_table);
									  if (PUSH_UNWIND_PROTECT(0)) 
										      {
									      result = track_mouse_for_new_table(ISVREF(mouse_pointer,
										      (SI_Long)2L),
										      ISVREF(mouse_pointer,
										      (SI_Long)3L),
										      T);
									      MVS_4(result,
										      temp,
										      row_qm,
										      column_qm,
										      subpart_description_qm);
									      if (row_qm 
										      && 
										      column_qm) 
											  {
										  new_table_spot 
											  = 
											  make_new_table_cell_spot_1();
										  SVREF(new_table_spot,
											  FIX((SI_Long)6L)) 
											  = 
											  row_qm;
										  SVREF(new_table_spot,
											  FIX((SI_Long)7L)) 
											  = 
											  column_qm;
										  SVREF(new_table_spot,
											  FIX((SI_Long)8L)) 
											  = 
											  subpart_description_qm;
										  temp 
											  = 
											  new_table_spot;
									      }
									      else
										  temp 
											  = 
											  make_new_table_background_spot_1();
									      SAVE_VALUES(push_last_spot(mouse_pointer,
										      temp,
										      New_table));
									  }
									  POP_UNWIND_PROTECT(0);
									  UNLOCK(Working_on_new_table);
									  CONTINUE_UNWINDING(0);
									POP_SPECIAL();
								    }
								    POP_UNWIND_PROTECT(1);
								    UNLOCK(Working_on_annotated_frame);
								    CONTINUE_UNWINDING(1);
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						    POP_SPECIAL();
						}
						POP_UNWIND_PROTECT(2);
						UNLOCK(For_image_plane);
						CONTINUE_UNWINDING(2);
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
		  }
		  POP_UNWIND_PROTECT(3);
		  UNLOCK(On_window_without_drawing);
		  CONTINUE_UNWINDING(3);
		  result = RESTORE_VALUES();
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qupdate_dependencies;  /* update-dependencies */

/* UPDATE-PART-DEPENDENCIES-FOR-NEW-TABLE */
Object update_part_dependencies_for_new_table(new_table,kind_of_change,
	    what_changed)
    Object new_table, kind_of_change, what_changed;
{
    Object current_annotated_frame, projection_mode, current_kind_of_change;
    Object current_thing_changed, current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_background_color_value, current_foreground_color_value;
    Object current_color_map;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(12);
    Object result;

    x_note_fn_call(178,69);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,11);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_annotated_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  10);
	    LOCK(Projection_update_dependencies);
	    if (PUSH_UNWIND_PROTECT(0)) {
		projection_mode = Qupdate_dependencies;
		current_kind_of_change = kind_of_change;
		current_thing_changed = what_changed;
		PUSH_SPECIAL_WITH_SYMBOL(Current_thing_changed,Qcurrent_thing_changed,current_thing_changed,
			9);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_kind_of_change,Qcurrent_kind_of_change,current_kind_of_change,
			  8);
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			    7);
		      current_image_x_scale = FIX((SI_Long)4096L);
		      current_image_y_scale = FIX((SI_Long)4096L);
		      current_x_origin_of_drawing = FIX((SI_Long)0L);
		      current_y_origin_of_drawing = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			      6);
			PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				5);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				  4);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				    3);
			      current_background_color_value = 
				      FIX((SI_Long)0L);
			      current_foreground_color_value = 
				      FIX((SI_Long)0L);
			      current_color_map = Off_window_color_map;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
				      2);
				PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					1);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					  0);
				    SAVE_VALUES(project_new_table());
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
	    UNLOCK(Projection_update_dependencies);
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Projection_of_new_table_accumulating_size, Qprojection_of_new_table_accumulating_size);

static Object Qsize;               /* size */

/* UPDATE-NEW-TABLE-SIZE */
Object update_new_table_size()
{
    Object maximum_width, maximum_height, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, new_right_edge_of_block;
    SI_Long new_bottom_edge_of_block;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,70);
    maximum_width = FIX((SI_Long)0L);
    maximum_height = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Maximum_height,Qmaximum_height,maximum_height,1);
      PUSH_SPECIAL_WITH_SYMBOL(Maximum_width,Qmaximum_width,maximum_width,0);
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(Current_annotated_frame,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)46L),(SI_Long)1L);
	gensymed_symbol_1 = Current_annotated_frame;
	gensymed_symbol_2 = Qsize;
	gensymed_symbol_3 = Nil;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
	gensymed_symbol = ISVREF(Current_annotated_frame,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_5 = IFIX(Maximum_width);
	new_right_edge_of_block = gensymed_symbol_4 + gensymed_symbol_5;
	gensymed_symbol = ISVREF(Current_annotated_frame,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_5 = IFIX(Maximum_height);
	new_bottom_edge_of_block = gensymed_symbol_4 + gensymed_symbol_5;
	gensymed_symbol = ISVREF(Current_annotated_frame,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	if (IFIX(gensymed_symbol) == new_right_edge_of_block) {
	    gensymed_symbol = ISVREF(Current_annotated_frame,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp = IFIX(gensymed_symbol) == new_bottom_edge_of_block;
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    change_edges_of_block(Current_annotated_frame,Nil,Nil,
		    FIX(new_right_edge_of_block),
		    FIX(new_bottom_edge_of_block));
	    result = enlarge_workspace_for_block_rectangle_if_necessary(Current_annotated_frame,
		    Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ACTIVATE-FOR-NEW-TABLE */
Object activate_for_new_table(new_table)
    Object new_table;
{
    Object current_block_of_dependent_frame, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,71);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,1);
      current_block_of_dependent_frame = New_table;
      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	      0);
	if ( !TRUEP(In_suspend_resume_p))
	    activate_g2_cell_array(get_lookup_slot_value_given_default(New_table,
		    Qcell_array,Nil));
	frame = New_table;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qnew_table)) {
	    method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	method_function_qm = Qnil;
      end_1:;
	if (method_function_qm)
	    result = inline_funcall_1(method_function_qm,frame);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DEACTIVATE-FOR-NEW-TABLE */
Object deactivate_for_new_table(new_table)
    Object new_table;
{
    Object current_block_of_dependent_frame, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,72);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,1);
      current_block_of_dependent_frame = New_table;
      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	      0);
	if ( !TRUEP(In_suspend_resume_p))
	    deactivate_g2_cell_array(get_lookup_slot_value_given_default(New_table,
		    Qcell_array,Nil));
	frame = New_table;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)7L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qnew_table)) {
	    method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	method_function_qm = Qnil;
      end_1:;
	if (method_function_qm)
	    result = inline_funcall_1(method_function_qm,frame);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qformat_frame;       /* format-frame */

static Object Qdynamic_text_cell_format;  /* dynamic-text-cell-format */

static Object Qmark;               /* mark */

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

static Object Qpart_description_of_frame;  /* part-description-of-frame */

static Object list_constant_9;     /* # */

static Object Qfuncall_on_focus_projection_mode;  /* funcall-on-focus-projection-mode */

static Object Qenter_focus;        /* enter-focus */

static Object Qdenote_projection_mode;  /* denote-projection-mode */

static Object Qcleanup_projection_mode;  /* cleanup-projection-mode */

static Object list_constant_10;    /* # */

static Object string_constant_9;   /* "the value of the cell in column ~D of row ~D" */

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object Qtext_cell_line_color_qm;  /* text-cell-line-color? */

static Object Qtext_cell_background_color_qm;  /* text-cell-background-color? */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Kno_bleeding;        /* :no-bleeding */

static Object Qab_slot_value;      /* slot-value */

/* PROJECT-NEW-TABLE */
Object project_new_table()
{
    Object current_computation_frame, current_computation_style;
    Object current_block_of_dependent_frame, temp, current_text_box_format;
    Object current_text_cell_plist, focus_just_happened_qm, cell_annotations;
    Object default_cell_format, part_feature_recall_stack;
    Object stack_of_current_part_descriptions;
    Object maintain_stack_of_current_part_descriptions_p;
    Object old_current_part_description, new_cons, temp_1, temp_2, temp_3;
    Object gensymed_symbol, old_current_part_description_1;
    Object old_current_part_description_2, old_current_part_description_3;
    Object block_background_color, block_background_color_value;
    Object block_background_color_value_color_difference;
    Object original_background_color_value, color_value, old_color_value;
    Object current_background_color_value, wrapup_scan_flag, focus_enabled_qm;
    Object right_edge_of_block, top_edge_of_block, left_edge_of_block;
    Object bottom_edge_of_block, suppress_details_qm, border_color;
    Object color_value_1, bottom_of_upper_row_border_in_window;
    Object ab_loop_destructure_, column_default_subpart_descriptions;
    Object row_annotations, top_edge_of_row, cell_subparts_of_this_row;
    Object ab_loop_list_, row_default_cell_subpart, ab_loop_list__1;
    Object ab_loop_desetq_, old_color_value_1, old_current_part_description_4;
    Object row_height_as_fixnum, bottom_edge_of_row, cell_subpart;
    Object ab_loop_list__2, cell_contents_qm, background_color_qm;
    Object computed_feature_qm, ab_loop_it_, left_edge_of_column;
    Object right_edge_of_column;
    Object right_edge_of_lefthand_column_border_in_window;
    Object column_default_cell_subpart, ab_loop_list__3;
    Object current_foreground_color_value, old_current_part_description_5;
    Object old_current_part_description_6, column_width_as_fixnum;
    Object focus_is_on_cell_contents, focus_matches_this_cell_p;
    Object background_color_feature_value, focus_enabled_qm_1, cell_expression;
    Object gensymed_symbol_3, new_text_value, svref_new_value;
    Object color_or_metacolor, text_cell_background_color_value;
    Object old_color_value_2, erase_instead_qm, supress_text_qm;
    Object x_magnification_qm, y_magnification_qm, magnified_x_scale;
    Object magnified_y_scale, scale, value, temp_5, new_background_color_value;
    Object changing_colors_of_graphic_elements_qm, color_value_2;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons, slot_value_pop_store;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long right_edge_of_block_in_window, top_edge_of_block_in_window;
    SI_Long left_edge_of_block_in_window, bottom_edge_of_block_in_window;
    SI_Long border_color_difference, row_border_height;
    SI_Long row_border_height_in_window, column_border_width;
    SI_Long column_border_width_in_window;
    SI_Long right_edge_of_first_column_border_in_window, row_index;
    SI_Long ab_loop_bind_, top_edge_of_row_in_window;
    SI_Long bottom_edge_of_row_in_window, temp_4;
    SI_Long bottom_of_lower_row_border_in_window, fifth_new_value;
    SI_Long column_index, ab_loop_bind__1, left_edge_of_column_in_window;
    SI_Long right_edge_of_column_in_window;
    SI_Long right_edge_of_righthand_column_border_in_window;
    char dragging_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(178,73);
    SAVE_STACK();
    current_computation_frame = Current_annotated_frame;
    current_computation_style = The_only_dynamic_computation_style;
    current_block_of_dependent_frame = Current_annotated_frame;
    temp = get_instance_with_name_if_any(Qformat_frame,
	    Qdynamic_text_cell_format);
    if (temp);
    else
	temp = make_format_frame(Qdynamic_text_cell_format);
    current_text_box_format = temp;
    current_text_cell_plist = Qnil;
    focus_just_happened_qm = Nil;
    cell_annotations = ISVREF(Current_annotated_frame,(SI_Long)18L);
    default_cell_format = ISVREF(Current_annotated_frame,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_text_cell_plist,Qcurrent_text_cell_plist,current_text_cell_plist,
	    13);
      PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
	      12);
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		11);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		  10);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		    9);
	      LOCK(Scanning_subparts_of_block);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  part_feature_recall_stack = Nil;
		  stack_of_current_part_descriptions = Nil;
		  maintain_stack_of_current_part_descriptions_p = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Maintain_stack_of_current_part_descriptions_p,Qmaintain_stack_of_current_part_descriptions_p,maintain_stack_of_current_part_descriptions_p,
			  8);
		    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_current_part_descriptions,Qstack_of_current_part_descriptions,stack_of_current_part_descriptions,
			    7);
		      PUSH_SPECIAL_WITH_SYMBOL(Part_feature_recall_stack,Qpart_feature_recall_stack,part_feature_recall_stack,
			      6);
			old_current_part_description = 
				Current_part_description;
			Current_part_description = 
				get_default_computation_style_of_class();
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				temp_3 = M_CDR(new_cons);
				SVREF(temp_1,temp_2) = temp_3;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    temp_2 = Current_thread_index;
			    temp_3 = M_CDR(new_cons);
			    SVREF(temp_1,temp_2) = temp_3;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			old_current_part_description_1 = 
				Current_part_description;
			Current_part_description = 
				get_default_formatted_part_of_class();
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				temp_3 = M_CDR(new_cons);
				SVREF(temp_1,temp_2) = temp_3;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    temp_2 = Current_thread_index;
			    temp_3 = M_CDR(new_cons);
			    SVREF(temp_1,temp_2) = temp_3;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			old_current_part_description_2 = 
				Current_part_description;
			Current_part_description = cell_annotations;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				temp_3 = M_CDR(new_cons);
				SVREF(temp_1,temp_2) = temp_3;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    temp_2 = Current_thread_index;
			    temp_3 = M_CDR(new_cons);
			    SVREF(temp_1,temp_2) = temp_3;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			old_current_part_description_3 = 
				Current_part_description;
			temp = default_cell_format;
			if (temp);
			else
			    temp = list_constant_7;
			Current_part_description = temp;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				temp_3 = M_CDR(new_cons);
				SVREF(temp_1,temp_2) = temp_3;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    temp_2 = Current_thread_index;
			    temp_3 = M_CDR(new_cons);
			    SVREF(temp_1,temp_2) = temp_3;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			dragging_qm = (SI_Long)0L != 
				(IFIX(ISVREF(Current_annotated_frame,
				(SI_Long)5L)) & (SI_Long)2048L);
			block_background_color = dragging_qm ? 
				Qtransparent : 
				ISVREF(Current_text_box_format,(SI_Long)24L);
			if (EQ(block_background_color,Qbackground))
			    block_background_color_value = 
				    Current_background_color_value;
			else if (EQ(block_background_color,Qforeground) || 
				EQ(block_background_color,
				Qworkspace_foreground))
			    block_background_color_value = 
				    Current_foreground_color_value;
			else if (EQ(block_background_color,Qtransparent))
			    block_background_color_value = 
				    Current_background_color_value;
			else
			    block_background_color_value = 
				    map_to_color_value(block_background_color);
			block_background_color_value_color_difference = 
				FIXNUM_LOGXOR(block_background_color_value,
				Current_background_color_value);
			original_background_color_value = 
				Current_background_color_value;
			color_value = EQ(Projection_mode,
				Qdraw_projection_mode) ? 
				block_background_color_value : 
				Current_background_color_value;
			old_color_value = Current_background_color_value;
			current_background_color_value = 
				Current_background_color_value;
			PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
				5);
			  set_current_background_color_value(color_value);
			  wrapup_scan_flag = Nil;
			  if (EQ(Projection_focus_method,Qnil))
			      focus_just_happened_qm = T;
			  else if (EQ(Projection_focus_method,Qcell))
			      focus_just_happened_qm = Nil;
			  else if (EQ(Projection_focus_method,Qannotation))
			      focus_just_happened_qm = 
				      EQ(Projection_focus_annotation,
				      default_cell_format) ? T : Nil;
			  else
			      focus_just_happened_qm = Qnil;
			  focus_enabled_qm = focus_just_happened_qm;
			  gensymed_symbol = ISVREF(Current_annotated_frame,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)2L) : 
				  FIX((SI_Long)0L);
			  right_edge_of_block = gensymed_symbol;
			  gensymed_symbol = ISVREF(Current_annotated_frame,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)1L) : 
				  FIX((SI_Long)0L);
			  top_edge_of_block = gensymed_symbol;
			  gensymed_symbol = ISVREF(Current_annotated_frame,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)0L) : 
				  FIX((SI_Long)0L);
			  left_edge_of_block = gensymed_symbol;
			  gensymed_symbol = ISVREF(Current_annotated_frame,
				  (SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)3L) : 
				  FIX((SI_Long)0L);
			  bottom_edge_of_block = gensymed_symbol;
			  gensymed_symbol_1 = 
				  IFIX(Current_x_origin_of_drawing);
			  if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(right_edge_of_block);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_x_scale) && 
				  FIXNUM_LT(Current_image_x_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  right_edge_of_block) && 
				  FIXNUM_LT(right_edge_of_block,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_x_scale,
				      right_edge_of_block)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_x_scale,
				      right_edge_of_block));
			  right_edge_of_block_in_window = 
				  gensymed_symbol_1 + gensymed_symbol_2;
			  gensymed_symbol_1 = 
				  IFIX(Current_y_origin_of_drawing);
			  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(top_edge_of_block);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_y_scale) && 
				  FIXNUM_LT(Current_image_y_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  top_edge_of_block) && 
				  FIXNUM_LT(top_edge_of_block,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_y_scale,
				      top_edge_of_block)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_y_scale,
				      top_edge_of_block));
			  top_edge_of_block_in_window = gensymed_symbol_1 
				  + gensymed_symbol_2;
			  gensymed_symbol_1 = 
				  IFIX(Current_x_origin_of_drawing);
			  if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(left_edge_of_block);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_x_scale) && 
				  FIXNUM_LT(Current_image_x_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  left_edge_of_block) && 
				  FIXNUM_LT(left_edge_of_block,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_x_scale,
				      left_edge_of_block)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_x_scale,
				      left_edge_of_block));
			  left_edge_of_block_in_window = gensymed_symbol_1 
				  + gensymed_symbol_2;
			  gensymed_symbol_1 = 
				  IFIX(Current_y_origin_of_drawing);
			  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(bottom_edge_of_block);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_y_scale) && 
				  FIXNUM_LT(Current_image_y_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  bottom_edge_of_block) && 
				  FIXNUM_LT(bottom_edge_of_block,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_y_scale,
				      bottom_edge_of_block)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_y_scale,
				      bottom_edge_of_block));
			  bottom_edge_of_block_in_window = 
				  gensymed_symbol_1 + gensymed_symbol_2;
			  suppress_details_qm = Nil;
			  if (suppress_details_qm);
			  else
			      suppress_details_qm = dragging_qm ? T : Nil;
			  if (suppress_details_qm) {
			      border_color = 
				      ISVREF(Current_text_box_format,
				      (SI_Long)23L);
			      if (border_color);
			      else
				  border_color = Qblack;
			  }
			  else
			      border_color = 
				      ISVREF(Current_text_box_format,
				      (SI_Long)48L);
			  if (EQ(border_color,Qbackground))
			      color_value_1 = Current_background_color_value;
			  else if (EQ(border_color,Qforeground) || 
				  EQ(border_color,Qworkspace_foreground))
			      color_value_1 = Current_foreground_color_value;
			  else if (EQ(border_color,Qtransparent))
			      color_value_1 = Current_background_color_value;
			  else
			      color_value_1 = map_to_color_value(border_color);
			  border_color_difference = 
				  IFIX(FIXNUM_LOGXOR(color_value_1,
				  Current_background_color_value));
			  row_border_height = (SI_Long)2L;
			  if (suppress_details_qm)
			      row_border_height_in_window = (SI_Long)1L;
			  else {
			      gensymed_symbol_1 = (SI_Long)1L;
			      if (IFIX(Current_image_y_scale) == 
				      (SI_Long)4096L)
				  gensymed_symbol_2 = row_border_height;
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_y_scale) && 
				      FIXNUM_LT(Current_image_y_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < row_border_height && 
				      row_border_height < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_y_scale) * 
					  row_border_height + (SI_Long)2048L;
				  gensymed_symbol_2 = unshifted_result >>  
					  -  - (SI_Long)12L;
			      }
			      else
				  gensymed_symbol_2 = 
					  IFIX(scalef_function(Current_image_y_scale,
					  FIX(row_border_height)));
			      row_border_height_in_window = 
				      MAX(gensymed_symbol_1,gensymed_symbol_2);
			  }
			  bottom_of_upper_row_border_in_window = 
				  FIX(top_edge_of_block_in_window + 
				  row_border_height_in_window);
			  column_border_width = (SI_Long)2L;
			  if (suppress_details_qm)
			      column_border_width_in_window = (SI_Long)1L;
			  else {
			      gensymed_symbol_1 = (SI_Long)1L;
			      if (IFIX(Current_image_x_scale) == 
				      (SI_Long)4096L)
				  gensymed_symbol_2 = column_border_width;
			      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				      Current_image_x_scale) && 
				      FIXNUM_LT(Current_image_x_scale,
				      Isqrt_of_most_positive_fixnum) && 
				      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				      < column_border_width && 
				      column_border_width < 
				      IFIX(Isqrt_of_most_positive_fixnum)) {
				  unshifted_result = 
					  IFIX(Current_image_x_scale) * 
					  column_border_width + (SI_Long)2048L;
				  gensymed_symbol_2 = unshifted_result >>  
					  -  - (SI_Long)12L;
			      }
			      else
				  gensymed_symbol_2 = 
					  IFIX(scalef_function(Current_image_x_scale,
					  FIX(column_border_width)));
			      column_border_width_in_window = 
				      MAX(gensymed_symbol_1,gensymed_symbol_2);
			  }
			  right_edge_of_first_column_border_in_window = 
				  left_edge_of_block_in_window + 
				  column_border_width_in_window;
			  ab_loop_destructure_ = 
				  get_subpart_collection(ISVREF(Current_annotated_frame,
				  (SI_Long)17L),Qsubparts,Qrow);
			  column_default_subpart_descriptions = Nil;
			  temp = CAR(ab_loop_destructure_);
			  temp = CDR(temp);
			  temp = CDR(temp);
			  temp = CAR(temp);
			  temp = CDR(temp);
			  column_default_subpart_descriptions = CAR(temp);
			  row_annotations = ISVREF(Current_annotated_frame,
				  (SI_Long)16L);
			  top_edge_of_row = FIX(IFIX(top_edge_of_block) + 
				  row_border_height);
			  row_index = (SI_Long)1L;
			  ab_loop_bind_ = IFIX(Row_maximum);
			  cell_subparts_of_this_row = Nil;
			  ab_loop_list_ = 
				  get_subpart_collection(cell_annotations,
				  Qsubparts,Qrow);
			  row_default_cell_subpart = Nil;
			  ab_loop_list__1 = 
				  get_subpart_collection(row_annotations,
				  Qsubparts,Qrow);
			  ab_loop_desetq_ = Nil;
			  if (EQ(Projection_mode,Qdraw_projection_mode)) {
			      if (focus_enabled_qm) {
				  if ( !EQ(Qtransparent,
					  block_background_color)) {
				      old_color_value_1 = 
					      Current_background_color_value;
				      current_background_color_value = 
					      Current_background_color_value;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					      0);
					set_current_background_color_value(original_background_color_value);
					draw_graphic_element(6,
						Qadd_solid_rectangle,
						FIX(left_edge_of_block_in_window),
						FIX(top_edge_of_block_in_window),
						FIX(right_edge_of_block_in_window),
						FIX(bottom_edge_of_block_in_window),
						block_background_color_value_color_difference);
					set_current_background_color_value(old_color_value_1);
				      POP_SPECIAL();
				  }
				  draw_graphic_element(6,
					  Qadd_solid_rectangle,
					  FIX(left_edge_of_block_in_window),
					  FIX(top_edge_of_block_in_window),
					  FIX(right_edge_of_block_in_window),
					  bottom_of_upper_row_border_in_window,
					  FIX(border_color_difference));
				  draw_graphic_element(6,
					  Qadd_solid_rectangle,
					  FIX(left_edge_of_block_in_window),
					  bottom_of_upper_row_border_in_window,
					  FIX(right_edge_of_first_column_border_in_window),
					  FIX(bottom_edge_of_block_in_window),
					  FIX(border_color_difference));
			      }
			  }
			  else if (EQ(Projection_mode,
				  Qcompute_path_of_focus_projection_mode)) {
			      Projection_focus_path = 
				      slot_value_cons_1(slot_value_list_3(Qpart_description_of_frame,
				      slot_value_list_2(Qquote,
				      Qcell_annotations),Qit),
				      Projection_focus_path);
			      Projection_focus_path = 
				      slot_value_cons_1(copy_for_slot_value(list_constant_9),
				      Projection_focus_path);
			  }
			  else if (EQ(Projection_mode,
				  Qfuncall_on_focus_projection_mode)) {
			      if (focus_just_happened_qm) {
				  focus_just_happened_qm = Nil;
				  FUNCALL_1(Current_projection_function_for_funcall,
					  Qenter_focus);
			      }
			  }
			next_loop:
			  if (row_index > ab_loop_bind_)
			      goto end_loop;
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  ab_loop_desetq_ = M_CAR(ab_loop_list_);
			  temp = CDR(ab_loop_desetq_);
			  temp = CDR(temp);
			  temp = CAR(temp);
			  temp = CDR(temp);
			  cell_subparts_of_this_row = CAR(temp);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop;
			  ab_loop_desetq_ = M_CAR(ab_loop_list__1);
			  temp = CDR(ab_loop_desetq_);
			  temp = CDR(temp);
			  temp = CAR(temp);
			  temp = CDR(temp);
			  temp = CAR(temp);
			  row_default_cell_subpart = CAR(temp);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if (wrapup_scan_flag)
			      goto end_loop;
			  old_current_part_description_4 = 
				  Current_part_description;
			  Current_part_description = row_default_cell_subpart;
			  if (Maintain_stack_of_current_part_descriptions_p) {
			      new_cons = 
				      ISVREF(Available_part_stack_conses_vector,
				      IFIX(Current_thread_index));
			      if (new_cons) {
				  temp_1 = Available_part_stack_conses_vector;
				  temp_2 = Current_thread_index;
				  temp_3 = M_CDR(new_cons);
				  SVREF(temp_1,temp_2) = temp_3;
				  if ( 
					  !TRUEP(ISVREF(Available_part_stack_conses_vector,
					  IFIX(Current_thread_index)))) {
				      temp_1 = 
					      Available_part_stack_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = Nil;
				  }
				  gensymed_symbol = new_cons;
			      }
			      else
				  gensymed_symbol = Nil;
			      if ( !TRUEP(gensymed_symbol))
				  gensymed_symbol = 
					  replenish_part_stack_cons_pool();
			      temp_1 = Current_part_description;
			      M_CAR(gensymed_symbol) = temp_1;
			      temp_1 = Stack_of_current_part_descriptions;
			      M_CDR(gensymed_symbol) = temp_1;
			      inline_note_allocate_cons(gensymed_symbol,
				      Qpart_stack);
			      Stack_of_current_part_descriptions = 
				      gensymed_symbol;
			  }
			  new_cons = 
				  ISVREF(Available_part_stack_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      temp_1 = Available_part_stack_conses_vector;
			      temp_2 = Current_thread_index;
			      temp_3 = M_CDR(new_cons);
			      SVREF(temp_1,temp_2) = temp_3;
			      if ( 
				      !TRUEP(ISVREF(Available_part_stack_conses_vector,
				      IFIX(Current_thread_index)))) {
				  temp_1 = 
					  Available_part_stack_conses_tail_vector;
				  temp_2 = Current_thread_index;
				  SVREF(temp_1,temp_2) = Nil;
			      }
			      gensymed_symbol = new_cons;
			  }
			  else
			      gensymed_symbol = Nil;
			  if ( !TRUEP(gensymed_symbol))
			      gensymed_symbol = 
				      replenish_part_stack_cons_pool();
			  M_CAR(gensymed_symbol) = Qmark;
			  temp_1 = Part_feature_recall_stack;
			  M_CDR(gensymed_symbol) = temp_1;
			  inline_note_allocate_cons(gensymed_symbol,
				  Qpart_stack);
			  Part_feature_recall_stack = gensymed_symbol;
			  enter_part_description(Current_part_description);
			  if (FIXNUMP(Current_height_of_formatted_part))
			      row_height_as_fixnum = 
				      Current_height_of_formatted_part;
			  else {
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Current_height_of_formatted_part) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_height_of_formatted_part)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_height_of_formatted_part,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(Current_height_of_formatted_part) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_height_of_formatted_part)) 
				      == (SI_Long)1L)
				  temp = 
					  aref1(Current_height_of_formatted_part,
					  FIX((SI_Long)0L));
			      else
				  temp = Current_height_of_formatted_part;
			      row_height_as_fixnum = ltruncate(temp,_);
			  }
			  bottom_edge_of_row = FIXNUM_ADD(top_edge_of_row,
				  row_height_as_fixnum);
			  gensymed_symbol_1 = 
				  IFIX(Current_y_origin_of_drawing);
			  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(top_edge_of_row);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_y_scale) && 
				  FIXNUM_LT(Current_image_y_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  top_edge_of_row) && 
				  FIXNUM_LT(top_edge_of_row,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_y_scale,
				      top_edge_of_row)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_y_scale,
				      top_edge_of_row));
			  top_edge_of_row_in_window = gensymed_symbol_1 + 
				  gensymed_symbol_2;
			  gensymed_symbol_1 = 
				  IFIX(Current_y_origin_of_drawing);
			  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			      gensymed_symbol_2 = IFIX(bottom_edge_of_row);
			  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  Current_image_y_scale) && 
				  FIXNUM_LT(Current_image_y_scale,
				  Isqrt_of_most_positive_fixnum) && 
				  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				  bottom_edge_of_row) && 
				  FIXNUM_LT(bottom_edge_of_row,
				  Isqrt_of_most_positive_fixnum)) {
			      unshifted_result = 
				      IFIX(FIXNUM_TIMES(Current_image_y_scale,
				      bottom_edge_of_row)) + (SI_Long)2048L;
			      gensymed_symbol_2 = unshifted_result >>  -  
				      - (SI_Long)12L;
			  }
			  else
			      gensymed_symbol_2 = 
				      IFIX(scalef_function(Current_image_y_scale,
				      bottom_edge_of_row));
			  bottom_edge_of_row_in_window = gensymed_symbol_1 
				  + gensymed_symbol_2;
			  temp_4 = bottom_edge_of_row_in_window + 
				  row_border_height_in_window;
			  bottom_of_lower_row_border_in_window = 
				  MIN(temp_4,bottom_edge_of_block_in_window);
			  if (EQ(Projection_mode,Qdraw_projection_mode) || 
				  EQ(Projection_mode,
				  Qdenote_projection_mode) || 
				  EQ(Projection_mode,
				  Qcompute_path_of_focus_projection_mode) 
				  || EQ(Projection_mode,
				  Qcleanup_projection_mode))
			      temp = T;
			  else if (EQ(Projection_mode,
				  Qtracking_projection_mode))
			      temp = top_edge_of_row_in_window < 
				      IFIX(Current_tracking_y_in_window) ? 
				      (IFIX(Current_tracking_y_in_window) 
				      < bottom_edge_of_row_in_window ? T : 
				      Nil) : Qnil;
			  else if (EQ(Projection_mode,
				  Qupdate_dependencies) || 
				  EQ(Projection_mode,
				  Qinvalidate_projection_mode)) {
			      if (EQ(Current_kind_of_change,Qsize))
				  temp = row_index == IFIX(Row_maximum) ? 
					  T : Nil;
			      else if (EQ(Current_kind_of_change,Qcell)) {
				  cell_subpart = Nil;
				  ab_loop_list__2 = cell_subparts_of_this_row;
				  cell_contents_qm = Nil;
				  background_color_qm = Nil;
				  computed_feature_qm = Nil;
				  ab_loop_it_ = Nil;
				next_loop_1:
				  if ( !TRUEP(ab_loop_list__2))
				      goto end_loop_1;
				  cell_subpart = M_CAR(ab_loop_list__2);
				  ab_loop_list__2 = M_CDR(ab_loop_list__2);
				  cell_contents_qm = 
					  get_simple_part_feature(cell_subpart,
					  Qcell_contents);
				  background_color_qm = 
					  get_simple_part_feature(cell_subpart,
					  Qbackground_color);
				  if (compiled_cell_expression_p(CAR(cell_contents_qm)))
				      computed_feature_qm = 
					      CAR(cell_contents_qm);
				  else if (evaluated_computed_part_feature_p(background_color_qm))
				      computed_feature_qm = 
					      background_color_qm;
				  else
				      computed_feature_qm = Nil;
				  if (computed_feature_qm) {
				      temp = Projection_focus_cell_index;
				      ab_loop_it_ = FIXNUM_EQ(temp,
					      get_simple_part_feature(computed_feature_qm,
					      Qexpression_cell_index)) ? T 
					      : Nil;
				  }
				  else
				      ab_loop_it_ = Nil;
				  if (ab_loop_it_) {
				      temp = ab_loop_it_;
				      goto end_1;
				  }
				  goto next_loop_1;
				end_loop_1:
				  temp = Qnil;
				end_1:;
			      }
			      else
				  temp = T;
			  }
			  else
			      temp = Qnil;
			  if (temp) {
			      if (EQ(Projection_mode,Qdraw_projection_mode)) {
				  if (focus_enabled_qm)
				      draw_graphic_element(6,
					      Qadd_solid_rectangle,
					      FIX(right_edge_of_first_column_border_in_window),
					      FIX(bottom_edge_of_row_in_window),
					      FIX(right_edge_of_block_in_window),
					      FIX(bottom_of_lower_row_border_in_window),
					      FIX(border_color_difference));
			      }
			      else if (EQ(Projection_mode,
				      Qcompute_path_of_focus_projection_mode)) 
					  {
				  temp_1 = FIRST(Projection_focus_path);
				  fifth_new_value = row_index - (SI_Long)1L;
				  M_FIFTH(temp_1) = FIX(fifth_new_value);
			      }
			      left_edge_of_column = 
				      FIX(IFIX(left_edge_of_block) + 
				      column_border_width);
			      right_edge_of_column = Nil;
			      right_edge_of_lefthand_column_border_in_window 
				      = 
				      FIX(right_edge_of_first_column_border_in_window);
			      column_index = (SI_Long)1L;
			      ab_loop_bind__1 = IFIX(Column_maximum);
			      column_default_cell_subpart = Nil;
			      ab_loop_list__2 = 
				      column_default_subpart_descriptions;
			      cell_subpart = Nil;
			      ab_loop_list__3 = cell_subparts_of_this_row;
			      if (EQ(Projection_mode,
				      Qcompute_path_of_focus_projection_mode))
				  Projection_focus_path = 
					  slot_value_cons_1(copy_for_slot_value(list_constant_10),
					  Projection_focus_path);
			    next_loop_2:
			      if (column_index > ab_loop_bind__1)
				  goto end_loop_2;
			      if ( !TRUEP(ab_loop_list__2))
				  goto end_loop_2;
			      column_default_cell_subpart = 
				      M_CAR(ab_loop_list__2);
			      ab_loop_list__2 = M_CDR(ab_loop_list__2);
			      if ( !TRUEP(ab_loop_list__3))
				  goto end_loop_2;
			      cell_subpart = M_CAR(ab_loop_list__3);
			      ab_loop_list__3 = M_CDR(ab_loop_list__3);
			      if (wrapup_scan_flag)
				  goto end_loop_2;
			      color_value = EQ(Projection_mode,
				      Qdraw_projection_mode) ? 
				      Current_background_color_value : 
				      Current_background_color_value;
			      old_color_value_1 = 
				      Current_background_color_value;
			      current_background_color_value = 
				      Current_background_color_value;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
				      4);
				set_current_background_color_value(color_value);
				current_foreground_color_value = 
					Current_foreground_color_value;
				PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					3);
				  old_current_part_description_5 = 
					  Current_part_description;
				  Current_part_description = 
					  column_default_cell_subpart;
				  if (Maintain_stack_of_current_part_descriptions_p) 
					      {
				      new_cons = 
					      ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp_1 = 
						  Available_part_stack_conses_vector;
					  temp_2 = Current_thread_index;
					  temp_3 = M_CDR(new_cons);
					  SVREF(temp_1,temp_2) = temp_3;
					  if ( 
						  !TRUEP(ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = Nil;
					  }
					  gensymed_symbol = new_cons;
				      }
				      else
					  gensymed_symbol = Nil;
				      if ( !TRUEP(gensymed_symbol))
					  gensymed_symbol = 
						  replenish_part_stack_cons_pool();
				      temp_1 = Current_part_description;
				      M_CAR(gensymed_symbol) = temp_1;
				      temp_1 = 
					      Stack_of_current_part_descriptions;
				      M_CDR(gensymed_symbol) = temp_1;
				      inline_note_allocate_cons(gensymed_symbol,
					      Qpart_stack);
				      Stack_of_current_part_descriptions = 
					      gensymed_symbol;
				  }
				  new_cons = 
					  ISVREF(Available_part_stack_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      temp_1 = 
					      Available_part_stack_conses_vector;
				      temp_2 = Current_thread_index;
				      temp_3 = M_CDR(new_cons);
				      SVREF(temp_1,temp_2) = temp_3;
				      if ( 
					      !TRUEP(ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index)))) {
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = Nil;
				      }
				      gensymed_symbol = new_cons;
				  }
				  else
				      gensymed_symbol = Nil;
				  if ( !TRUEP(gensymed_symbol))
				      gensymed_symbol = 
					      replenish_part_stack_cons_pool();
				  M_CAR(gensymed_symbol) = Qmark;
				  temp_1 = Part_feature_recall_stack;
				  M_CDR(gensymed_symbol) = temp_1;
				  inline_note_allocate_cons(gensymed_symbol,
					  Qpart_stack);
				  Part_feature_recall_stack = gensymed_symbol;
				  enter_part_description(Current_part_description);
				  old_current_part_description_6 = 
					  Current_part_description;
				  Current_part_description = cell_subpart;
				  if (Maintain_stack_of_current_part_descriptions_p) 
					      {
				      new_cons = 
					      ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp_1 = 
						  Available_part_stack_conses_vector;
					  temp_2 = Current_thread_index;
					  temp_3 = M_CDR(new_cons);
					  SVREF(temp_1,temp_2) = temp_3;
					  if ( 
						  !TRUEP(ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = Nil;
					  }
					  gensymed_symbol = new_cons;
				      }
				      else
					  gensymed_symbol = Nil;
				      if ( !TRUEP(gensymed_symbol))
					  gensymed_symbol = 
						  replenish_part_stack_cons_pool();
				      temp_1 = Current_part_description;
				      M_CAR(gensymed_symbol) = temp_1;
				      temp_1 = 
					      Stack_of_current_part_descriptions;
				      M_CDR(gensymed_symbol) = temp_1;
				      inline_note_allocate_cons(gensymed_symbol,
					      Qpart_stack);
				      Stack_of_current_part_descriptions = 
					      gensymed_symbol;
				  }
				  new_cons = 
					  ISVREF(Available_part_stack_conses_vector,
					  IFIX(Current_thread_index));
				  if (new_cons) {
				      temp_1 = 
					      Available_part_stack_conses_vector;
				      temp_2 = Current_thread_index;
				      temp_3 = M_CDR(new_cons);
				      SVREF(temp_1,temp_2) = temp_3;
				      if ( 
					      !TRUEP(ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index)))) {
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = Nil;
				      }
				      gensymed_symbol = new_cons;
				  }
				  else
				      gensymed_symbol = Nil;
				  if ( !TRUEP(gensymed_symbol))
				      gensymed_symbol = 
					      replenish_part_stack_cons_pool();
				  M_CAR(gensymed_symbol) = Qmark;
				  temp_1 = Part_feature_recall_stack;
				  M_CDR(gensymed_symbol) = temp_1;
				  inline_note_allocate_cons(gensymed_symbol,
					  Qpart_stack);
				  Part_feature_recall_stack = gensymed_symbol;
				  enter_part_description(Current_part_description);
				  if (FIXNUMP(Current_width_of_formatted_part))
				      column_width_as_fixnum = 
					      Current_width_of_formatted_part;
				  else {
				      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Current_width_of_formatted_part) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_width_of_formatted_part)) 
					      == (SI_Long)1L)
					  temp = 
						  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_width_of_formatted_part,
						  (SI_Long)0L));
				      else if (INLINE_LONG_VECTOR_P(Current_width_of_formatted_part) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_width_of_formatted_part)) 
					      == (SI_Long)1L)
					  temp = 
						  aref1(Current_width_of_formatted_part,
						  FIX((SI_Long)0L));
				      else
					  temp = 
						  Current_width_of_formatted_part;
				      column_width_as_fixnum = 
					      ltruncate(temp,_);
				  }
				  if (EQ(Projection_focus_method,Qcell)) {
				      if (part_has_feature_p(cell_subpart,
					      Qcell_contents) && 
					      compiled_cell_expression_p(CAR(Cell_contents))) 
						  {
					  temp = Projection_focus_cell_index;
					  focus_is_on_cell_contents = 
						  FIXNUM_EQ(temp,
						  get_simple_part_feature(CAR(Cell_contents),
						  Qexpression_cell_index)) 
						  ? T : Nil;
				      }
				      else
					  focus_is_on_cell_contents = Nil;
				  }
				  else if (EQ(Projection_focus_method,
					  Qannotation))
				      focus_is_on_cell_contents = 
					      EQ(Projection_focus_annotation,
					      cell_subpart) ? T : Nil;
				  else
				      focus_is_on_cell_contents = Qnil;
				  focus_matches_this_cell_p = focus_enabled_qm;
				  if (focus_matches_this_cell_p);
				  else if (EQ(Projection_focus_method,Qcell)) {
				      focus_matches_this_cell_p = 
					      focus_is_on_cell_contents;
				      if (focus_matches_this_cell_p);
				      else {
					  background_color_feature_value = 
						  part_has_feature_p(cell_subpart,
						  Qbackground_color);
					  if (background_color_feature_value 
						  && 
						  evaluated_computed_part_feature_p(background_color_feature_value)) 
						      {
					      temp = 
						      Projection_focus_cell_index;
					      focus_matches_this_cell_p = 
						      FIXNUM_EQ(temp,
						      get_simple_part_feature(background_color_feature_value,
						      Qexpression_cell_index)) 
						      ? T : Nil;
					  }
					  else
					      focus_matches_this_cell_p = Nil;
				      }
				  }
				  else if (EQ(Projection_focus_method,
					  Qannotation))
				      focus_matches_this_cell_p = 
					      focus_is_on_cell_contents;
				  else
				      focus_matches_this_cell_p = T;
				  temp = focus_enabled_qm;
				  if (temp);
				  else {
				      focus_just_happened_qm = 
					      focus_matches_this_cell_p;
				      temp = focus_just_happened_qm;
				  }
				  focus_enabled_qm_1 = temp;
				  right_edge_of_column = 
					  FIXNUM_ADD(left_edge_of_column,
					  column_width_as_fixnum);
				  gensymed_symbol_1 = 
					  IFIX(Current_x_origin_of_drawing);
				  if (IFIX(Current_image_x_scale) == 
					  (SI_Long)4096L)
				      gensymed_symbol_2 = 
					      IFIX(left_edge_of_column);
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_x_scale) && 
					  FIXNUM_LT(Current_image_x_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  left_edge_of_column) && 
					  FIXNUM_LT(left_edge_of_column,
					  Isqrt_of_most_positive_fixnum)) {
				      unshifted_result = 
					      IFIX(FIXNUM_TIMES(Current_image_x_scale,
					      left_edge_of_column)) + 
					      (SI_Long)2048L;
				      gensymed_symbol_2 = unshifted_result 
					      >>  -  - (SI_Long)12L;
				  }
				  else
				      gensymed_symbol_2 = 
					      IFIX(scalef_function(Current_image_x_scale,
					      left_edge_of_column));
				  left_edge_of_column_in_window = 
					  gensymed_symbol_1 + 
					  gensymed_symbol_2;
				  gensymed_symbol_1 = 
					  IFIX(Current_x_origin_of_drawing);
				  if (IFIX(Current_image_x_scale) == 
					  (SI_Long)4096L)
				      gensymed_symbol_2 = 
					      IFIX(right_edge_of_column);
				  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  Current_image_x_scale) && 
					  FIXNUM_LT(Current_image_x_scale,
					  Isqrt_of_most_positive_fixnum) 
					  && 
					  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					  right_edge_of_column) && 
					  FIXNUM_LT(right_edge_of_column,
					  Isqrt_of_most_positive_fixnum)) {
				      unshifted_result = 
					      IFIX(FIXNUM_TIMES(Current_image_x_scale,
					      right_edge_of_column)) + 
					      (SI_Long)2048L;
				      gensymed_symbol_2 = unshifted_result 
					      >>  -  - (SI_Long)12L;
				  }
				  else
				      gensymed_symbol_2 = 
					      IFIX(scalef_function(Current_image_x_scale,
					      right_edge_of_column));
				  right_edge_of_column_in_window = 
					  gensymed_symbol_1 + 
					  gensymed_symbol_2;
				  temp_4 = right_edge_of_column_in_window 
					  + column_border_width_in_window;
				  right_edge_of_righthand_column_border_in_window 
					  = MIN(temp_4,
					  right_edge_of_block_in_window);
				  if (focus_enabled_qm_1) {
				      if (EQ(Projection_mode,
					      Qdenote_projection_mode)) {
					  tformat(3,string_constant_9,
						  FIX(column_index),
						  FIX(row_index));
					  wrapup_scan_flag = T;
				      }
				      else if (EQ(Projection_mode,
					      Qcompute_path_of_focus_projection_mode)) 
						  {
					  temp_1 = 
						  FIRST(Projection_focus_path);
					  fifth_new_value = column_index - 
						  (SI_Long)1L;
					  M_FIFTH(temp_1) = 
						  FIX(fifth_new_value);
					  Projection_focus_path = 
						  slot_value_cons_1(copy_for_slot_value(focus_is_on_cell_contents 
						  ? list_constant_11 : 
						  list_constant_12),
						  Projection_focus_path);
					  wrapup_scan_flag = T;
				      }
				      else if (EQ(Projection_mode,
					      Qtracking_projection_mode)) {
					  if (left_edge_of_column_in_window 
						  < 
						  IFIX(Current_tracking_x_in_window) 
						  && 
						  IFIX(Current_tracking_x_in_window) 
						  < 
						  right_edge_of_column_in_window) 
						      {
					      temp_1 = 
						      Current_tracking_subcomponent;
					      M_FIRST(temp_1) = FIX(row_index);
					      temp_1 = 
						      Current_tracking_subcomponent;
					      M_SECOND(temp_1) = 
						      FIX(column_index);
					      temp_1 = 
						      Current_tracking_subcomponent;
					      temp_2 = 
						      Current_part_description;
					      M_THIRD(temp_1) = temp_2;
					      wrapup_scan_flag = T;
					  }
				      }
				      else if (EQ(Projection_mode,
					      Qupdate_dependencies)) {
					  if (memq_function(Current_kind_of_change,
						  list_constant_13) && 
						  (focus_is_on_cell_contents 
						  || 
						  EQ(Current_thing_changed,
						  default_cell_format))) {
					      if (part_has_feature_p(cell_subpart,
						      Qcell_contents)) {
						  cell_expression = 
							  CAR(Cell_contents);
						  if (EQ(Projection_focus_method,
							  Qcell))
						      temp = 
							      Projection_focus_cell_new_cached_value;
						  else if (simple_cell_expression_p(cell_expression))
						      temp = 
							      CAR(cell_expression);
						  else {
						      gensymed_symbol = 
							      ISVREF(get_lookup_slot_value_given_default(Current_annotated_frame,
							      Qcell_array,
							      Nil),
							      (SI_Long)3L);
						      gensymed_symbol_3 = 
							      get_simple_part_feature(cell_expression,
							      Qexpression_cell_index);
						      if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(Current_annotated_frame,
							      Qcell_array,
							      Nil),
							      (SI_Long)3L),
							      (SI_Long)1L),
							      Maximum_in_place_array_size)) 
								  {
							  temp = 
								  ISVREF(get_lookup_slot_value_given_default(Current_annotated_frame,
								  Qcell_array,
								  Nil),
								  (SI_Long)3L);
							  temp = 
								  ISVREF(temp,
								  IFIX(FIXNUM_ADD(gensymed_symbol_3,
								  Managed_array_index_offset)));
						      }
						      else
							  temp = 
								  ISVREF(ISVREF(gensymed_symbol,
								  (IFIX(gensymed_symbol_3) 
								  >>  -  - 
								  (SI_Long)10L) 
								  + 
								  (SI_Long)2L),
								  IFIX(gensymed_symbol_3) 
								  & 
								  (SI_Long)1023L);
						      temp = ISVREF(temp,
							      (SI_Long)6L);
						  }
						  new_text_value = 
							  make_text_for_datum(temp,
							  column_width_as_fixnum);
						  if (Postpone_cell_erase_until_redraw_p 
							  &&  
							  !TRUEP(Updated_only_qm)) 
							      {
						      set_simple_part_feature_without_reclaiming(cell_subpart,
							      Qtext_value,
							      new_text_value);
						      Reclaim_text_value_from_postponed_erase_p 
							      = T;
						  }
						  else
						      set_simple_part_feature(cell_subpart,
							      Qtext_value,
							      new_text_value);
					      }
					      else
						  remove_simple_part_feature(cell_subpart,
							  Qtext_value);
					  }
				      }
				      else if (EQ(Projection_mode,
					      Qdraw_projection_mode)) {
					  if ( !EQ(Projection_focus_method,
						  Qcell))
					      draw_graphic_element(6,
						      Qadd_solid_rectangle,
						      FIX(right_edge_of_column_in_window),
						      bottom_of_upper_row_border_in_window,
						      FIX(right_edge_of_righthand_column_border_in_window),
						      FIX(bottom_edge_of_row_in_window),
						      FIX(border_color_difference));
					  if (Formatted_part_highlight_flag) {
					      temp_1 = Current_text_box_format;
					      svref_new_value = 
						      ISVREF(temp_1,
						      (SI_Long)23L);
					      temp_3 = Current_text_box_format;
					      temp_2 = ISVREF(temp_3,
						      (SI_Long)24L);
					      if (Noting_changes_to_kb_p)
						  note_change_to_block_1(temp_1,
							  Qtext_cell_line_color_qm);
					      SVREF(temp_1,
						      FIX((SI_Long)23L)) = 
						      temp_2;
					      if (Noting_changes_to_kb_p)
						  note_change_to_block_1(temp_3,
							  Qtext_cell_background_color_qm);
					      SVREF(temp_3,
						      FIX((SI_Long)24L)) = 
						      svref_new_value;
					  }
					  color_or_metacolor = 
						  ISVREF(Current_text_box_format,
						  (SI_Long)24L);
					  if (EQ(color_or_metacolor,
						  Qbackground))
					      text_cell_background_color_value 
						      = 
						      Current_background_color_value;
					  else if (EQ(color_or_metacolor,
						  Qforeground) || 
						  EQ(color_or_metacolor,
						  Qworkspace_foreground))
					      text_cell_background_color_value 
						      = 
						      Current_foreground_color_value;
					  else if (EQ(color_or_metacolor,
						  Qtransparent))
					      text_cell_background_color_value 
						      = 
						      Current_background_color_value;
					  else
					      text_cell_background_color_value 
						      = 
						      map_to_color_value(color_or_metacolor);
					  if (ISVREF(Current_text_box_format,
						  (SI_Long)23L)) {
					      color_or_metacolor = 
						      ISVREF(Current_text_box_format,
						      (SI_Long)23L);
					      if (EQ(color_or_metacolor,
						      Qbackground))
						  current_foreground_color_value 
							  = 
							  Current_background_color_value;
					      else if (EQ(color_or_metacolor,
						      Qforeground) || 
						      EQ(color_or_metacolor,
						      Qworkspace_foreground))
						  current_foreground_color_value 
							  = 
							  Current_foreground_color_value;
					      else if (EQ(color_or_metacolor,
						      Qtransparent))
						  current_foreground_color_value 
							  = 
							  Current_background_color_value;
					      else
						  current_foreground_color_value 
							  = 
							  map_to_color_value(color_or_metacolor);
					  }
					  else
					      current_foreground_color_value 
						      = 
						      Current_foreground_color_value;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						  2);
					    if (Postpone_cell_erase_until_redraw_p 
						    &&  
						    !TRUEP(Erase_instead_qm) 
						    && 
						    Text_value_from_postponed_erase) 
							{
						if (Formatted_part_highlight_flag)
						    color_value = 
							    text_cell_background_color_value;
						else {
						    temp = 
							    assoc_eql(Current_window,
							    Background_color_value_from_postponed_erase);
						    color_value = CDR(temp);
						    if (color_value);
						    else
							color_value = 
								map_to_color_value(Qwhite);
						}
						old_color_value_2 = 
							Current_background_color_value;
						current_background_color_value 
							= 
							Current_background_color_value;
						PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
							1);
						  set_current_background_color_value(color_value);
						  erase_instead_qm = T;
						  PUSH_SPECIAL_WITH_SYMBOL(Erase_instead_qm,Qerase_instead_qm,erase_instead_qm,
							  0);
						    supress_text_qm = 
							    suppress_details_qm;
						    if (supress_text_qm);
						    else {
							x_magnification_qm 
								= Nil ? 
								getfq_function_no_default(Nil,
								Qx_magnification) 
								: Nil;
							if (x_magnification_qm);
							else
							    x_magnification_qm 
								    = 
								    ISVREF(Current_text_box_format,
								    (SI_Long)25L);
							y_magnification_qm 
								= Nil ? 
								getfq_function_no_default(Nil,
								Qy_magnification) 
								: Nil;
							if (y_magnification_qm);
							else
							    y_magnification_qm 
								    = 
								    ISVREF(Current_text_box_format,
								    (SI_Long)26L);
							magnified_x_scale 
								= 
								x_magnification_qm 
								? 
								FIX(IFIX(FIXNUM_TIMES(Current_image_x_scale,
								x_magnification_qm)) 
								+ 
								(SI_Long)128L 
								>>  -  - 
								(SI_Long)8L) 
								: 
								Current_image_x_scale;
							magnified_y_scale 
								= 
								y_magnification_qm 
								? 
								FIX(IFIX(FIXNUM_TIMES(Current_image_y_scale,
								y_magnification_qm)) 
								+ 
								(SI_Long)128L 
								>>  -  - 
								(SI_Long)8L) 
								: 
								Current_image_y_scale;
							scale = 
								FIXNUM_MIN(magnified_x_scale,
								magnified_y_scale);
							value = 
								ISVREF(Current_text_box_format,
								(SI_Long)31L);
							if (IFIX(scale) == 
								(SI_Long)4096L)
							    temp_5 = value;
							else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								scale) && 
								FIXNUM_LT(scale,
								Isqrt_of_most_positive_fixnum) 
								&& 
								FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
								value) && 
								FIXNUM_LT(value,
								Isqrt_of_most_positive_fixnum)) 
								    {
							    unshifted_result 
								    = 
								    IFIX(FIXNUM_TIMES(scale,
								    value)) 
								    + 
								    (SI_Long)2048L;
							    temp_5 = 
								    FIX(unshifted_result 
								    >>  -  
								    - 
								    (SI_Long)12L);
							}
							else
							    temp_5 = 
								    scalef_function(scale,
								    value);
							temp = 
								FIX((SI_Long)6L);
							supress_text_qm = 
								NUM_LT(temp_5,
								temp) ? T :
								 Nil;
						    }
						    if ( 
							    !TRUEP(supress_text_qm)) 
								{
							if (part_has_feature_p(cell_subpart,
								Qtext_value))
							    draw_text_segment_1(Text_value_from_postponed_erase,
								    Nil,
								    FIX((SI_Long)0L),
								    FIX(left_edge_of_column_in_window),
								    FIX(top_edge_of_row_in_window),
								    FIX(right_edge_of_column_in_window),
								    FIX(bottom_edge_of_row_in_window));
						    }
						  POP_SPECIAL();
						  set_current_background_color_value(old_color_value_2);
						POP_SPECIAL();
					    }
					    new_background_color_value = 
						    dragging_qm ? 
						    Current_background_color_value 
						    : 
						    text_cell_background_color_value;
					    if (Erase_instead_qm && 
						    Postpone_cell_erase_until_redraw_p) 
							{
						temp_5 = Current_window;
						if (Formatted_part_highlight_flag) 
							    {
						    color_or_metacolor = 
							    ISVREF(Current_text_box_format,
							    (SI_Long)23L);
						    if (EQ(color_or_metacolor,
							    Qbackground))
							temp = 
								Current_background_color_value;
						    else if (EQ(color_or_metacolor,
							    Qforeground) 
							    || 
							    EQ(color_or_metacolor,
							    Qworkspace_foreground))
							temp = 
								Current_foreground_color_value;
						    else if (EQ(color_or_metacolor,
							    Qtransparent))
							temp = 
								Current_background_color_value;
						    else
							temp = 
								map_to_color_value(color_or_metacolor);
						}
						else
						    temp = 
							    new_background_color_value;
						Background_color_value_from_postponed_erase 
							= 
							gensym_cons_1(gensym_cons_1(temp_5,
							temp),
							Background_color_value_from_postponed_erase);
					    }
					    else if ( 
						    !(Formatted_part_highlight_flag 
						    && 
						    Postpone_cell_erase_until_redraw_p)) 
							{
						changing_colors_of_graphic_elements_qm 
							= 
							Changing_colors_of_graphic_elements_qm;
						PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
							0);
						  if (Postpone_cell_erase_until_redraw_p)
						      Changing_colors_of_graphic_elements_qm 
							      = T;
						  if ( !(dragging_qm || 
							  EQ(Qtransparent,
							  ISVREF(Current_text_box_format,
							  (SI_Long)24L)))) {
						      temp = 
							      right_edge_of_lefthand_column_border_in_window;
						      if (Postpone_cell_erase_until_redraw_p) 
								  {
							  temp_5 = 
								  assoc_eql(Current_window,
								  Background_color_value_from_postponed_erase);
							  color_value_2 = 
								  CDR(temp_5);
							  if (color_value_2);
							  else
							      color_value_2 
								      = 
								      map_to_color_value(Qwhite);
						      }
						      else
							  color_value_2 = 
								  Current_background_color_value;
						      draw_graphic_element(6,
							      Qadd_solid_rectangle,
							      temp,
							      FIX(top_edge_of_row_in_window),
							      FIX(right_edge_of_column_in_window),
							      FIX(bottom_edge_of_row_in_window),
							      FIXNUM_LOGXOR(new_background_color_value,
							      color_value_2));
						  }
						POP_SPECIAL();
					    }
					    old_color_value_2 = 
						    Current_background_color_value;
					    current_background_color_value 
						    = 
						    Current_background_color_value;
					    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
						    0);
					      set_current_background_color_value(new_background_color_value);
					      if (Postpone_cell_erase_until_redraw_p 
						      && Erase_instead_qm) {
						  if ( 
							  !TRUEP(Text_value_from_postponed_erase))
						      Text_value_from_postponed_erase 
							      = 
							      get_simple_part_feature(cell_subpart,
							      Qtext_value);
						  Updated_only_qm = Nil;
					      }
					      else {
						  if (Formatted_part_highlight_flag 
							  && 
							  Background_color_value_from_postponed_erase) 
							      {
						      temp = 
							      assoc_eql(Current_window,
							      Background_color_value_from_postponed_erase);
						      temp = CDR(temp);
						      if (temp);
						      else
							  temp = 
								  map_to_color_value(Qwhite);
						      Current_foreground_color_value 
							      = temp;
						  }
						  supress_text_qm = 
							  suppress_details_qm;
						  if (supress_text_qm);
						  else {
						      x_magnification_qm = 
							      Nil ? 
							      getfq_function_no_default(Nil,
							      Qx_magnification) 
							      : Nil;
						      if (x_magnification_qm);
						      else
							  x_magnification_qm 
								  = 
								  ISVREF(Current_text_box_format,
								  (SI_Long)25L);
						      y_magnification_qm = 
							      Nil ? 
							      getfq_function_no_default(Nil,
							      Qy_magnification) 
							      : Nil;
						      if (y_magnification_qm);
						      else
							  y_magnification_qm 
								  = 
								  ISVREF(Current_text_box_format,
								  (SI_Long)26L);
						      magnified_x_scale = 
							      x_magnification_qm 
							      ? 
							      FIX(IFIX(FIXNUM_TIMES(Current_image_x_scale,
							      x_magnification_qm)) 
							      + 
							      (SI_Long)128L 
							      >>  -  - 
							      (SI_Long)8L) 
							      : 
							      Current_image_x_scale;
						      magnified_y_scale = 
							      y_magnification_qm 
							      ? 
							      FIX(IFIX(FIXNUM_TIMES(Current_image_y_scale,
							      y_magnification_qm)) 
							      + 
							      (SI_Long)128L 
							      >>  -  - 
							      (SI_Long)8L) 
							      : 
							      Current_image_y_scale;
						      scale = 
							      FIXNUM_MIN(magnified_x_scale,
							      magnified_y_scale);
						      value = 
							      ISVREF(Current_text_box_format,
							      (SI_Long)31L);
						      if (IFIX(scale) == 
							      (SI_Long)4096L)
							  temp_5 = value;
						      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
							      scale) && 
							      FIXNUM_LT(scale,
							      Isqrt_of_most_positive_fixnum) 
							      && 
							      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
							      value) && 
							      FIXNUM_LT(value,
							      Isqrt_of_most_positive_fixnum)) 
								  {
							  unshifted_result 
								  = 
								  IFIX(FIXNUM_TIMES(scale,
								  value)) 
								  + 
								  (SI_Long)2048L;
							  temp_5 = 
								  FIX(unshifted_result 
								  >>  -  - 
								  (SI_Long)12L);
						      }
						      else
							  temp_5 = 
								  scalef_function(scale,
								  value);
						      temp = FIX((SI_Long)6L);
						      supress_text_qm = 
							      NUM_LT(temp_5,
							      temp) ? T : Nil;
						  }
						  if ( 
							      !TRUEP(supress_text_qm)) {
						      if (part_has_feature_p(cell_subpart,
							      Qtext_value))
							  draw_text_segment_1(get_simple_part_feature(cell_subpart,
								  Qtext_value),
								  Nil,
								  FIX((SI_Long)0L),
								  FIX(left_edge_of_column_in_window),
								  FIX(top_edge_of_row_in_window),
								  FIX(right_edge_of_column_in_window),
								  FIX(bottom_edge_of_row_in_window));
						  }
					      }
					      set_current_background_color_value(old_color_value_2);
					    POP_SPECIAL();
					    if (Formatted_part_highlight_flag) 
							{
						temp_1 = 
							Current_text_box_format;
						svref_new_value = 
							ISVREF(temp_1,
							(SI_Long)23L);
						temp_3 = 
							Current_text_box_format;
						temp_2 = ISVREF(temp_3,
							(SI_Long)24L);
						if (Noting_changes_to_kb_p)
						    note_change_to_block_1(temp_1,
							    Qtext_cell_line_color_qm);
						SVREF(temp_1,
							FIX((SI_Long)23L)) 
							= temp_2;
						if (Noting_changes_to_kb_p)
						    note_change_to_block_1(temp_3,
							    Qtext_cell_background_color_qm);
						SVREF(temp_3,
							FIX((SI_Long)24L)) 
							= svref_new_value;
					    }
					  POP_SPECIAL();
				      }
				      else if (EQ(Projection_mode,
					      Qinvalidate_projection_mode)) {
					  temp = 
						  get_workspace_if_any(Current_annotated_frame);
					  invalidate_rectangle_of_workspace(temp,
						  Current_annotated_frame,
						  right_edge_of_lefthand_column_border_in_window,
						  FIX(top_edge_of_row_in_window),
						  FIX(right_edge_of_column_in_window),
						  FIX(bottom_edge_of_row_in_window),
						  Kno_bleeding);
				      }
				      else if (EQ(Projection_mode,
					      Qfuncall_on_focus_projection_mode)) 
						  {
					  if (focus_just_happened_qm) {
					      focus_just_happened_qm = Nil;
					      FUNCALL_1(Current_projection_function_for_funcall,
						      Qenter_focus);
					  }
				      }
				  }
				  left_edge_of_column = 
					  FIX(IFIX(right_edge_of_column) + 
					  column_border_width);
				  right_edge_of_lefthand_column_border_in_window 
					  = 
					  FIX(right_edge_of_righthand_column_border_in_window);
				  part_feature_index = Nil;
				  exit_feature_handler = Nil;
				next_loop_3:
				  part_stack_pop_store = Nil;
				  cons_1 = Part_feature_recall_stack;
				  if (cons_1) {
				      part_stack_pop_store = M_CAR(cons_1);
				      next_cons = M_CDR(cons_1);
				      inline_note_reclaim_cons(cons_1,
					      Qpart_stack);
				      if (ISVREF(Available_part_stack_conses_tail_vector,
					      IFIX(Current_thread_index))) {
					  temp_1 = 
						  ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index));
					  M_CDR(temp_1) = cons_1;
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      else {
					  temp_1 = 
						  Available_part_stack_conses_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      M_CDR(cons_1) = Nil;
				  }
				  else
				      next_cons = Nil;
				  Part_feature_recall_stack = next_cons;
				  part_feature_index = part_stack_pop_store;
				  if (EQ(part_feature_index,Qmark))
				      goto end_loop_3;
				  exit_feature_handler = 
					  ISVREF(Part_feature_exit_methods,
					  IFIX(part_feature_index));
				  inline_funcall_0(exit_feature_handler);
				  goto next_loop_3;
				end_loop_3:;
				  Current_part_description = 
					  old_current_part_description_6;
				  if (Maintain_stack_of_current_part_descriptions_p) 
					      {
				      part_stack_pop_store = Nil;
				      cons_1 = 
					      Stack_of_current_part_descriptions;
				      if (cons_1) {
					  part_stack_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qpart_stack);
					  if (ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp_1 = 
						      ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp_1) = cons_1;
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  else {
					      temp_1 = 
						      Available_part_stack_conses_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Stack_of_current_part_descriptions = 
					      next_cons;
				  }
				  part_feature_index = Nil;
				  exit_feature_handler = Nil;
				next_loop_4:
				  part_stack_pop_store = Nil;
				  cons_1 = Part_feature_recall_stack;
				  if (cons_1) {
				      part_stack_pop_store = M_CAR(cons_1);
				      next_cons = M_CDR(cons_1);
				      inline_note_reclaim_cons(cons_1,
					      Qpart_stack);
				      if (ISVREF(Available_part_stack_conses_tail_vector,
					      IFIX(Current_thread_index))) {
					  temp_1 = 
						  ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index));
					  M_CDR(temp_1) = cons_1;
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      else {
					  temp_1 = 
						  Available_part_stack_conses_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
					  temp_1 = 
						  Available_part_stack_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      M_CDR(cons_1) = Nil;
				  }
				  else
				      next_cons = Nil;
				  Part_feature_recall_stack = next_cons;
				  part_feature_index = part_stack_pop_store;
				  if (EQ(part_feature_index,Qmark))
				      goto end_loop_4;
				  exit_feature_handler = 
					  ISVREF(Part_feature_exit_methods,
					  IFIX(part_feature_index));
				  inline_funcall_0(exit_feature_handler);
				  goto next_loop_4;
				end_loop_4:;
				  Current_part_description = 
					  old_current_part_description_5;
				  if (Maintain_stack_of_current_part_descriptions_p) 
					      {
				      part_stack_pop_store = Nil;
				      cons_1 = 
					      Stack_of_current_part_descriptions;
				      if (cons_1) {
					  part_stack_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qpart_stack);
					  if (ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp_1 = 
						      ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp_1) = cons_1;
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  else {
					      temp_1 = 
						      Available_part_stack_conses_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					      temp_1 = 
						      Available_part_stack_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Stack_of_current_part_descriptions = 
					      next_cons;
				  }
				POP_SPECIAL();
				set_current_background_color_value(old_color_value_1);
			      POP_SPECIAL();
			      column_index = column_index + (SI_Long)1L;
			      goto next_loop_2;
			    end_loop_2:
			      if (EQ(Projection_mode,Qupdate_dependencies)) {
				  if (EQ(Current_kind_of_change,Qsize)) {
				      Maximum_width = 
					      FIX(column_border_width + 
					      IFIX(right_edge_of_column) - 
					      IFIX(left_edge_of_block));
				      Maximum_height = 
					      FIX(row_border_height + 
					      IFIX(bottom_edge_of_row) - 
					      IFIX(top_edge_of_block));
				  }
			      }
			      else if (EQ(Projection_mode,
				      Qcompute_path_of_focus_projection_mode)) 
					  {
				  if ( !TRUEP(wrapup_scan_flag)) {
				      slot_value_pop_store = Nil;
				      cons_1 = Projection_focus_path;
				      if (cons_1) {
					  slot_value_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qab_slot_value);
					  if (ISVREF(Available_slot_value_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp_1 = 
						      ISVREF(Available_slot_value_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp_1) = cons_1;
					      temp_1 = 
						      Available_slot_value_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  else {
					      temp_1 = 
						      Available_slot_value_conses_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					      temp_1 = 
						      Available_slot_value_conses_tail_vector;
					      temp_2 = Current_thread_index;
					      SVREF(temp_1,temp_2) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Projection_focus_path = next_cons;
				      reclaim_slot_value_tree_1(slot_value_pop_store);
				  }
			      }
			  }
			  top_edge_of_row = FIX(IFIX(bottom_edge_of_row) + 
				  row_border_height);
			  bottom_of_upper_row_border_in_window = 
				  FIX(bottom_of_lower_row_border_in_window);
			  part_feature_index = Nil;
			  exit_feature_handler = Nil;
			next_loop_5:
			  part_stack_pop_store = Nil;
			  cons_1 = Part_feature_recall_stack;
			  if (cons_1) {
			      part_stack_pop_store = M_CAR(cons_1);
			      next_cons = M_CDR(cons_1);
			      inline_note_reclaim_cons(cons_1,Qpart_stack);
			      if (ISVREF(Available_part_stack_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp_1 = 
					  ISVREF(Available_part_stack_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp_1) = cons_1;
				  temp_1 = 
					  Available_part_stack_conses_tail_vector;
				  temp_2 = Current_thread_index;
				  SVREF(temp_1,temp_2) = cons_1;
			      }
			      else {
				  temp_1 = Available_part_stack_conses_vector;
				  temp_2 = Current_thread_index;
				  SVREF(temp_1,temp_2) = cons_1;
				  temp_1 = 
					  Available_part_stack_conses_tail_vector;
				  temp_2 = Current_thread_index;
				  SVREF(temp_1,temp_2) = cons_1;
			      }
			      M_CDR(cons_1) = Nil;
			  }
			  else
			      next_cons = Nil;
			  Part_feature_recall_stack = next_cons;
			  part_feature_index = part_stack_pop_store;
			  if (EQ(part_feature_index,Qmark))
			      goto end_loop_5;
			  exit_feature_handler = 
				  ISVREF(Part_feature_exit_methods,
				  IFIX(part_feature_index));
			  inline_funcall_0(exit_feature_handler);
			  goto next_loop_5;
			end_loop_5:;
			  Current_part_description = 
				  old_current_part_description_4;
			  if (Maintain_stack_of_current_part_descriptions_p) {
			      part_stack_pop_store = Nil;
			      cons_1 = Stack_of_current_part_descriptions;
			      if (cons_1) {
				  part_stack_pop_store = M_CAR(cons_1);
				  next_cons = M_CDR(cons_1);
				  inline_note_reclaim_cons(cons_1,Qpart_stack);
				  if (ISVREF(Available_part_stack_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_part_stack_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = cons_1;
				      temp_1 = 
					      Available_part_stack_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = cons_1;
				  }
				  else {
				      temp_1 = 
					      Available_part_stack_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = cons_1;
				      temp_1 = 
					      Available_part_stack_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = cons_1;
				  }
				  M_CDR(cons_1) = Nil;
			      }
			      else
				  next_cons = Nil;
			      Stack_of_current_part_descriptions = next_cons;
			  }
			  row_index = row_index + (SI_Long)1L;
			  goto next_loop;
			end_loop:
			  if (EQ(Projection_mode,
				  Qcompute_path_of_focus_projection_mode)) {
			      if ( !TRUEP(wrapup_scan_flag)) {
				  slot_value_pop_store = Nil;
				  cons_1 = Projection_focus_path;
				  if (cons_1) {
				      slot_value_pop_store = M_CAR(cons_1);
				      next_cons = M_CDR(cons_1);
				      inline_note_reclaim_cons(cons_1,
					      Qab_slot_value);
				      if (ISVREF(Available_slot_value_conses_tail_vector,
					      IFIX(Current_thread_index))) {
					  temp_1 = 
						  ISVREF(Available_slot_value_conses_tail_vector,
						  IFIX(Current_thread_index));
					  M_CDR(temp_1) = cons_1;
					  temp_1 = 
						  Available_slot_value_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      else {
					  temp_1 = 
						  Available_slot_value_conses_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
					  temp_1 = 
						  Available_slot_value_conses_tail_vector;
					  temp_2 = Current_thread_index;
					  SVREF(temp_1,temp_2) = cons_1;
				      }
				      M_CDR(cons_1) = Nil;
				  }
				  else
				      next_cons = Nil;
				  Projection_focus_path = next_cons;
				  reclaim_slot_value_tree_1(slot_value_pop_store);
			      }
			  }
			  SAVE_VALUES(VALUES_1(Qnil));
			  set_current_background_color_value(old_color_value);
			POP_SPECIAL();
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_6:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_6;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_6;
		      end_loop_6:;
			Current_part_description = 
				old_current_part_description_3;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_7:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_7;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_7;
		      end_loop_7:;
			Current_part_description = 
				old_current_part_description_2;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_8:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_8;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_8;
		      end_loop_8:;
			Current_part_description = 
				old_current_part_description_1;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_9:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_9;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_9;
		      end_loop_9:;
			Current_part_description = 
				old_current_part_description;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    temp_2 = Current_thread_index;
				    SVREF(temp_1,temp_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Scanning_subparts_of_block);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_10;  /* "~A" */

static Object array_constant_1;    /* # */

/* MAKE-TEXT-FOR-DATUM */
Object make_text_for_datum(datum,width)
    Object datum, width;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(178,74);
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
	      if (text_string_p(datum))
		  tformat(2,string_constant_10,datum);
	      else if ( !TRUEP(datum))
		  twrite_beginning_of_wide_string(array_constant_1,
			  FIX((SI_Long)4L));
	      else {
		  gensymed_symbol = datum;
		  temp = FIXNUMP(gensymed_symbol);
		  if (temp);
		  else
		      temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L ? 
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
		      temp = 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
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
			  key_hash_value = 
				  SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp_2);
			  MVS_2(result,succ,marked);
			next_loop_2:
			  if ( !TRUEP(marked))
			      goto end_loop_1;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp_2 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
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
				  key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? 
				  TRUEP(ISVREF(curr,(SI_Long)3L)) : 
				  TRUEP(Nil)) : TRUEP(Nil);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      write_evaluation_value(1,datum);
	      }
	      temp_2 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_2 = convert_text_string_to_text(temp_2);
    return format_text(8,temp_2,Current_text_box_format,
	    Current_text_cell_plist,width,Nil,Nil,Nil,Nil);
}

/* COPY-AND-FORMAT-TEXT */
Object copy_and_format_text(text,width)
    Object text, width;
{
    x_note_fn_call(178,75);
    return format_text(8,copy_for_slot_value(text),Current_text_box_format,
	    Current_text_cell_plist,width,Nil,Nil,Nil,Nil);
}

/* SPLICE-LISTS */
Object splice_lists(destination_list,source_list,index_init)
    Object destination_list, source_list, index_init;
{
    Object cdr_arg, nthcdr_1, cdr_new_value;
    SI_Long index_1;

    x_note_fn_call(178,76);
    index_1 = IFIX(index_init);
    if (source_list) {
	if ((SI_Long)0L == index_1) {
	    cdr_arg = last(source_list,_);
	    M_CDR(cdr_arg) = destination_list;
	    return VALUES_1(source_list);
	}
	else {
	    nthcdr_1 = nthcdr(FIX(index_1 - (SI_Long)1L),destination_list);
	    cdr_arg = last(source_list,_);
	    cdr_new_value = CDR(nthcdr_1);
	    M_CDR(cdr_arg) = cdr_new_value;
	    M_CDR(nthcdr_1) = source_list;
	    return VALUES_1(destination_list);
	}
    }
    else
	return VALUES_1(Nil);
}

/* INSERT-SUBPART-DESCRIPTIONS */
Object insert_subpart_descriptions(destination_part_description,
	    source_part_description,subpart_type,index_to_insert_at)
    Object destination_part_description, source_part_description, subpart_type;
    Object index_to_insert_at;
{
    Object destination_subparts, source_subparts;

    x_note_fn_call(178,77);
    destination_subparts = 
	    get_subpart_collection(destination_part_description,Qsubparts,
	    subpart_type);
    source_subparts = get_subpart_collection(source_part_description,
	    Qsubparts,subpart_type);
    set_subpart_collection_without_reclaiming(source_part_description,
	    Qsubparts,subpart_type,Nil);
    destination_subparts = splice_lists(destination_subparts,
	    source_subparts,index_to_insert_at);
    set_subpart_collection_without_reclaiming(destination_part_description,
	    Qsubparts,subpart_type,destination_subparts);
    return VALUES_1(destination_part_description);
}

/* DELETE-SUBPART */
Object delete_subpart(part_description,subpart_type,
	    index_of_subpart_to_delete_init)
    Object part_description, subpart_type, index_of_subpart_to_delete_init;
{
    Object subparts, bit_to_reclaim, nthcdr_1, cdr_new_value;
    SI_Long index_of_subpart_to_delete;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,78);
    index_of_subpart_to_delete = IFIX(index_of_subpart_to_delete_init);
    subparts = get_subpart_collection(part_description,Qsubparts,subpart_type);
    PUSH_SPECIAL_WITH_SYMBOL(Subparts,Qsubparts,subparts,0);
      bit_to_reclaim = Nil;
      if ((SI_Long)0L == index_of_subpart_to_delete) {
	  bit_to_reclaim = Subparts;
	  Subparts = CDR(Subparts);
      }
      else {
	  nthcdr_1 = nthcdr(FIX(index_of_subpart_to_delete - (SI_Long)1L),
		  Subparts);
	  bit_to_reclaim = CDR(nthcdr_1);
	  cdr_new_value = CDR(bit_to_reclaim);
	  M_CDR(nthcdr_1) = cdr_new_value;
      }
      M_CDR(bit_to_reclaim) = Nil;
      reclaim_part_description(CAR(bit_to_reclaim));
      reclaim_slot_value_list_1(bit_to_reclaim);
      set_subpart_collection_without_reclaiming(part_description,Qsubparts,
	      subpart_type,Subparts);
      result = VALUES_1(part_description);
    POP_SPECIAL();
    return result;
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* TABLE-BLOCK-INSERT-OR-DELETE */
Object table_block_insert_or_delete(target_table,row_index,column_index,
	    edit_action,count_1)
    Object target_table, row_index, column_index, edit_action, count_1;
{
    Object target_cell_annotations, target_row_annotations;
    Object target_column_annotations, original_row_maximum;
    Object original_column_maximum, insert_cell_annotations;
    Object insert_row_annotations, insert_column_annotations;
    Object final_row_maximum, final_column_maximum, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object incff_1_arg, temp_1, temp_2, decff_1_arg;
    Object target_row_part_description, ab_loop_list_;
    Object insert_row_part_description, ab_loop_list__1, row_part_description;
    Object frame_and_slot_or_atom, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value_1, ab_loop_repeat_;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,79);
    target_cell_annotations = ISVREF(target_table,(SI_Long)18L);
    target_row_annotations = ISVREF(target_table,(SI_Long)16L);
    target_column_annotations = ISVREF(target_table,(SI_Long)17L);
    original_row_maximum = get_simple_part_feature(target_cell_annotations,
	    Qrow_maximum);
    original_column_maximum = 
	    get_simple_part_feature(target_cell_annotations,Qcolumn_maximum);
    insert_cell_annotations = Nil;
    insert_row_annotations = Nil;
    insert_column_annotations = Nil;
    final_row_maximum = original_row_maximum;
    final_column_maximum = original_column_maximum;
    erase_entire_annotated_block(Current_annotated_frame);
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(target_table,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = nconc2(stack_change_list_2(target_table,
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
	M_CAR(gensymed_symbol_1) = target_table;
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
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(target_table,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(target_table,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = target_table;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(target_table,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(target_table,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (EQ(edit_action,Qadd_row)) {
	  incff_1_arg = count_1;
	  final_row_maximum = FIXNUM_ADD(final_row_maximum,incff_1_arg);
	  temp_1 = make_table_annotation(Qrow,count_1,original_column_maximum);
	  temp_2 = make_table_annotation(Qcell,count_1,
		  original_column_maximum);
	  result = VALUES_3(temp_1,Nil,temp_2);
      }
      else if (EQ(edit_action,Qadd_column)) {
	  incff_1_arg = count_1;
	  final_column_maximum = FIXNUM_ADD(final_column_maximum,incff_1_arg);
	  temp_1 = make_table_annotation(Qcolumn,original_row_maximum,count_1);
	  temp_2 = make_table_annotation(Qcell,original_row_maximum,count_1);
	  result = VALUES_3(Nil,temp_1,temp_2);
      }
      else if (EQ(edit_action,Qdelete_row)) {
	  decff_1_arg = count_1;
	  final_row_maximum = FIXNUM_MINUS(final_row_maximum,decff_1_arg);
	  result = VALUES_3(Nil,Nil,Nil);
      }
      else if (EQ(edit_action,Qdelete_column)) {
	  decff_1_arg = count_1;
	  final_column_maximum = FIXNUM_MINUS(final_column_maximum,
		  decff_1_arg);
	  result = VALUES_3(Nil,Nil,Nil);
      }
      else
	  result = VALUES_1(Qnil);
      MVS_3(result,insert_row_annotations,insert_column_annotations,
	      insert_cell_annotations);
      if (EQ(edit_action,Qadd_row)) {
	  insert_subpart_descriptions(target_row_annotations,
		  insert_row_annotations,Qrow,row_index);
	  insert_subpart_descriptions(target_cell_annotations,
		  insert_cell_annotations,Qrow,row_index);
      }
      else if (EQ(edit_action,Qdelete_row)) {
	  ab_loop_repeat_ = IFIX(count_1);
	next_loop:
	  if ( !((SI_Long)0L < ab_loop_repeat_))
	      goto end_loop;
	  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	  delete_subpart(target_row_annotations,Qrow,row_index);
	  delete_subpart(target_cell_annotations,Qrow,row_index);
	  goto next_loop;
	end_loop:;
      }
      else if (EQ(edit_action,Qadd_column)) {
	  target_row_part_description = Nil;
	  ab_loop_list_ = get_subpart_collection(target_cell_annotations,
		  Qsubparts,Qrow);
	  insert_row_part_description = Nil;
	  ab_loop_list__1 = get_subpart_collection(insert_cell_annotations,
		  Qsubparts,Qrow);
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  target_row_part_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  insert_row_part_description = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  insert_subpart_descriptions(target_row_part_description,
		  insert_row_part_description,Qcell,column_index);
	  goto next_loop_1;
	end_loop_1:;
	  temp_2 = get_subpart_collection(target_column_annotations,
		  Qsubparts,Qrow);
	  temp_2 = FIRST(temp_2);
	  temp_1 = get_subpart_collection(insert_column_annotations,
		  Qsubparts,Qrow);
	  insert_subpart_descriptions(temp_2,FIRST(temp_1),Qcell,column_index);
      }
      else if (EQ(edit_action,Qdelete_column)) {
	  ab_loop_repeat_ = IFIX(count_1);
	next_loop_2:
	  if ( !((SI_Long)0L < ab_loop_repeat_))
	      goto end_loop_2;
	  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	  row_part_description = Nil;
	  ab_loop_list_ = get_subpart_collection(target_cell_annotations,
		  Qsubparts,Qrow);
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  row_part_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  delete_subpart(row_part_description,Qcell,column_index);
	  goto next_loop_3;
	end_loop_3:;
	  temp_2 = get_subpart_collection(target_column_annotations,
		  Qsubparts,Qrow);
	  delete_subpart(FIRST(temp_2),Qcell,column_index);
	  goto next_loop_2;
	end_loop_2:;
      }
      set_simple_part_feature(target_cell_annotations,Qrow_maximum,
	      final_row_maximum);
      set_simple_part_feature(target_cell_annotations,Qcolumn_maximum,
	      final_column_maximum);
      set_simple_part_feature(target_column_annotations,Qcolumn_maximum,
	      final_column_maximum);
      set_simple_part_feature(target_row_annotations,Qrow_maximum,
	      final_row_maximum);
      update_representations_of_slot_value(2,Current_annotated_frame,
	      Qcell_annotations);
      update_representations_of_slot_value(2,Current_annotated_frame,
	      Qrow_annotations);
      update_representations_of_slot_value(2,Current_annotated_frame,
	      Qcolumn_annotations);
      reclaim_slot_value(insert_row_annotations);
      reclaim_slot_value(insert_column_annotations);
      reclaim_slot_value(insert_cell_annotations);
      result_1 = update_new_table_size();
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(target_table,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(target_table,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(target_table,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = target_table;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_3 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_3);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_4:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_4;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_4;
	  temp_3 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_3);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_3 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_3 ? (EQ(target_table,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_3 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop_4;
	end_loop_4:
	  temp_3 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_3 = TRUEP(Nil);
      if ( !temp_3)
	  update_all_representations_of_slot(target_table,slot_description,
		  Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(target_table);
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
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_3 = ATOM(temp_2);
      }
      else
	  temp_3 = TRUEP(Nil);
      if (temp_3 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(target_table,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)19L),(SI_Long)1L);
    gensymed_symbol_1 = target_table;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    send_ws_representations_item_virtual_attribute_change(target_table,
	    get_property_value_function(3,
	    get_symbol_properties_function(Qtable_cells),
	    Qvirtual_attribute,Nil),Nil);
    return redraw_entire_annotated_block();
}

static Object Qedit_cell_expression;  /* edit-cell-expression */

static Object Qedit_cell_format;   /* edit-cell-format */

static Object list_constant_14;    /* # */

static Object list_constant_15;    /* # */

/* DO-NEW-TABLE-EDIT */
Object do_new_table_edit(new_table,edit_action,image_plane,x_in_window,
	    y_in_window)
    Object new_table, edit_action, image_plane, x_in_window, y_in_window;
{
    Object current_annotated_frame, current_block_of_dependent_frame;
    Object gensym_window, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, temp;
    Object current_frame_transform_qm, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map;
    Object current_background_color_value, current_foreground_color_value;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, cell_subpart, table, row_index;
    Object column_index;
    Declare_stack_pointer;
    Declare_catch(4);
    Declare_special(46);
    Object result;

    x_note_fn_call(178,80);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,45);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(3)) {
	  current_annotated_frame = New_table;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  44);
	    current_block_of_dependent_frame = New_table;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		    43);
	      gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),
		      (SI_Long)2L);
	      left_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)7L);
	      top_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)8L);
	      right_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)9L);
	      bottom_edge_of_draw_area = ISVREF(gensym_window,(SI_Long)10L);
	      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		      42);
		PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
			41);
		  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			  40);
		    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			    39);
		      current_image_x_scale = FIX((SI_Long)4096L);
		      current_image_y_scale = FIX((SI_Long)4096L);
		      current_x_origin_of_drawing = FIX((SI_Long)0L);
		      current_y_origin_of_drawing = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			      38);
			PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				37);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				  36);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				    35);
			      left_edge_of_draw_area = Left_edge_of_draw_area;
			      top_edge_of_draw_area = Top_edge_of_draw_area;
			      right_edge_of_draw_area = 
				      Right_edge_of_draw_area;
			      bottom_edge_of_draw_area = 
				      Bottom_edge_of_draw_area;
			      PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
				      34);
				PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
					33);
				  PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
					  32);
				    PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
					    31);
				      temp = ISVREF(image_plane,(SI_Long)6L);
				      Left_edge_of_draw_area = 
					      FIXNUM_MAX(temp,
					      Left_edge_of_draw_area);
				      temp = ISVREF(image_plane,(SI_Long)7L);
				      Top_edge_of_draw_area = 
					      FIXNUM_MAX(temp,
					      Top_edge_of_draw_area);
				      temp = ISVREF(image_plane,(SI_Long)8L);
				      Right_edge_of_draw_area = 
					      FIXNUM_MIN(temp,
					      Right_edge_of_draw_area);
				      temp = ISVREF(image_plane,(SI_Long)9L);
				      Bottom_edge_of_draw_area = 
					      FIXNUM_MIN(temp,
					      Bottom_edge_of_draw_area);
				      if (FIXNUM_LT(Left_edge_of_draw_area,
					      Right_edge_of_draw_area) && 
					      FIXNUM_LT(Top_edge_of_draw_area,
					      Bottom_edge_of_draw_area)) {
					  left_edge_of_draw_area = 
						  Left_edge_of_draw_area;
					  top_edge_of_draw_area = 
						  Top_edge_of_draw_area;
					  right_edge_of_draw_area = 
						  Right_edge_of_draw_area;
					  bottom_edge_of_draw_area = 
						  Bottom_edge_of_draw_area;
					  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
						  30);
					    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
						    29);
					      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
						      28);
						PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
							27);
						  temp = 
							  ISVREF(image_plane,
							  (SI_Long)19L);
						  Left_edge_of_draw_area = 
							  FIXNUM_MAX(temp,
							  Left_edge_of_draw_area);
						  temp = 
							  ISVREF(image_plane,
							  (SI_Long)20L);
						  Top_edge_of_draw_area = 
							  FIXNUM_MAX(temp,
							  Top_edge_of_draw_area);
						  temp = 
							  ISVREF(image_plane,
							  (SI_Long)21L);
						  Right_edge_of_draw_area 
							  = 
							  FIXNUM_MIN(temp,
							  Right_edge_of_draw_area);
						  temp = 
							  ISVREF(image_plane,
							  (SI_Long)22L);
						  Bottom_edge_of_draw_area 
							  = 
							  FIXNUM_MIN(temp,
							  Bottom_edge_of_draw_area);
						  if (FIXNUM_LT(Left_edge_of_draw_area,
							  Right_edge_of_draw_area) 
							  && 
							  FIXNUM_LT(Top_edge_of_draw_area,
							  Bottom_edge_of_draw_area)) 
							      {
						      current_frame_transform_qm 
							      = Nil;
						      current_image_x_scale 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)11L);
						      current_image_y_scale 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)12L);
						      current_x_origin_of_drawing 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)13L);
						      current_y_origin_of_drawing 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)14L);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
							      26);
							PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
								25);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
								  24);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
								    23);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
								      22);
								LOCK(On_window_without_drawing);
								if (PUSH_UNWIND_PROTECT(2)) 
									    {
								    current_window_1 
									    = 
									    ISVREF(ISVREF(image_plane,
									    (SI_Long)2L),
									    (SI_Long)2L);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
									    21);
								      drawing_on_window 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
									      20);
									current_drawing_transfer_mode 
										= 
										EQ(Current_drawing_transfer_mode,
										Kxor) 
										?
										 
										Current_drawing_transfer_mode 
										:
										 
										ISVREF(Current_window,
										(SI_Long)30L);
									PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
										19);
									  type_of_current_window 
										  = 
										  ISVREF(Current_window,
										  (SI_Long)1L);
									  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
										  18);
									    current_native_window_qm 
										    = 
										    ISVREF(Current_window,
										    (SI_Long)17L);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
										    17);
									      current_color_map 
										      = 
										      ISVREF(Current_window,
										      (SI_Long)20L);
									      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
										      16);
										temp 
											= 
											ISVREF(Current_color_map,
											(SI_Long)5L);
										if (temp);
										else
										    temp 
											    = 
											    map_to_color_value_1(Qwhite);
										current_background_color_value 
											= 
											temp;
										PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
											15);
										  temp 
											  = 
											  ISVREF(Current_color_map,
											  (SI_Long)4L);
										  if (temp);
										  else
										      temp 
											      = 
											      map_to_color_value_1(Qblack);
										  current_foreground_color_value 
											  = 
											  temp;
										  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
											  14);
										    current_frame_transform_qm 
											    = 
											    Nil;
										    current_image_x_scale 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)11L);
										    current_image_y_scale 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)12L);
										    current_x_origin_of_drawing 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)13L);
										    current_y_origin_of_drawing 
											    = 
											    ISVREF(image_plane,
											    (SI_Long)14L);
										    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
											    13);
										      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
											      12);
											PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
												11);
											  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
												  10);
											    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
												    9);
											      LOCK(For_image_plane);
											      if (PUSH_UNWIND_PROTECT(1)) 
													  {
												  current_pane 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)2L);
												  current_image_plane 
													  = 
													  image_plane;
												  loose_left_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)23L);
												  loose_top_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)24L);
												  loose_right_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)25L);
												  loose_bottom_edge_of_visible_workspace_area 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)26L);
												  color_or_metacolor 
													  = 
													  ISVREF(image_plane,
													  (SI_Long)5L) 
													  ?
													   
													  ISVREF(ISVREF(image_plane,
													  (SI_Long)5L),
													  (SI_Long)22L) 
													  :
													   
													  Nil;
												  if (color_or_metacolor);
												  else
												      color_or_metacolor 
													      = 
													      Qblack;
												  if (EQ(color_or_metacolor,
													  Qtransparent) 
													  || 
													  EQ(color_or_metacolor,
													  Qbackground)) 
													      {
												      background_color_or_metacolor 
													      = 
													      ISVREF(image_plane,
													      (SI_Long)5L) 
													      ?
													       
													      ISVREF(ISVREF(image_plane,
													      (SI_Long)5L),
													      (SI_Long)21L) 
													      :
													       
													      Nil;
												      if (background_color_or_metacolor);
												      else
													  background_color_or_metacolor 
														  = 
														  Qwhite;
												      if (EQ(background_color_or_metacolor,
													      Qforeground) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qworkspace_foreground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)4L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qblack);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else if (EQ(background_color_or_metacolor,
													      Qtransparent) 
													      || 
													      EQ(background_color_or_metacolor,
													      Qbackground)) 
														  {
													  temp 
														  = 
														  ISVREF(Current_color_map,
														  (SI_Long)5L);
													  if (temp);
													  else
													      temp 
														      = 
														      map_to_color_value_1(Qwhite);
													  current_foreground_color_value 
														  = 
														  temp;
												      }
												      else
													  current_foreground_color_value 
														  = 
														  EQ(background_color_or_metacolor,
														  ISVREF(Current_color_map,
														  (SI_Long)6L)) 
														  ?
														   
														  ISVREF(Current_color_map,
														  (SI_Long)7L) 
														  :
														   
														  map_to_color_value_1(background_color_or_metacolor);
												  }
												  else if (EQ(color_or_metacolor,
													  Qforeground) 
													  || 
													  EQ(color_or_metacolor,
													  Qworkspace_foreground)) 
													      {
												      temp 
													      = 
													      ISVREF(Current_color_map,
													      (SI_Long)4L);
												      if (temp);
												      else
													  temp 
														  = 
														  map_to_color_value_1(Qblack);
												      current_foreground_color_value 
													      = 
													      temp;
												  }
												  else
												      current_foreground_color_value 
													      = 
													      EQ(color_or_metacolor,
													      ISVREF(Current_color_map,
													      (SI_Long)6L)) 
													      ?
													       
													      ISVREF(Current_color_map,
													      (SI_Long)7L) 
													      :
													       
													      map_to_color_value_1(color_or_metacolor);
												  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
													  8);
												    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
													    7);
												      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
													      6);
													PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
														5);
													  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
														  4);
													    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
														    3);
													      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
														      2);
														color_or_metacolor 
															= 
															ISVREF(image_plane,
															(SI_Long)5L) 
															?
															 
															ISVREF(ISVREF(image_plane,
															(SI_Long)5L),
															(SI_Long)21L) 
															:
															 
															Nil;
														if (color_or_metacolor);
														else
														    color_or_metacolor 
															    = 
															    Qwhite;
														if (EQ(color_or_metacolor,
															Qtransparent) 
															|| 
															EQ(color_or_metacolor,
															Qbackground)) 
															    {
														    temp 
															    = 
															    ISVREF(Current_color_map,
															    (SI_Long)5L);
														    if (temp);
														    else
															temp 
																= 
																map_to_color_value_1(Qwhite);
														    current_background_color_value 
															    = 
															    temp;
														}
														else if (EQ(color_or_metacolor,
															Qforeground) 
															|| 
															EQ(color_or_metacolor,
															Qworkspace_foreground)) 
															    {
														    temp 
															    = 
															    ISVREF(image_plane,
															    (SI_Long)5L) 
															    ?
															     
															    ISVREF(ISVREF(image_plane,
															    (SI_Long)5L),
															    (SI_Long)22L) 
															    :
															     
															    Nil;
														    if (temp);
														    else
															temp 
																= 
																Qblack;
														    color_or_metacolor 
															    = 
															    temp;
														    if (EQ(color_or_metacolor,
															    Qtransparent) 
															    || 
															    EQ(color_or_metacolor,
															    Qbackground)) 
																{
															background_color_or_metacolor 
																= 
																ISVREF(image_plane,
																(SI_Long)5L) 
																?
																 
																ISVREF(ISVREF(image_plane,
																(SI_Long)5L),
																(SI_Long)21L) 
																:
																 
																Nil;
															if (background_color_or_metacolor);
															else
															    background_color_or_metacolor 
																    = 
																    Qwhite;
															if (EQ(background_color_or_metacolor,
																Qforeground) 
																|| 
																EQ(background_color_or_metacolor,
																Qworkspace_foreground)) 
																    {
															    temp 
																    = 
																    ISVREF(Current_color_map,
																    (SI_Long)4L);
															    if (temp);
															    else
																temp 
																	= 
																	map_to_color_value_1(Qblack);
															    current_background_color_value 
																    = 
																    temp;
															}
															else if (EQ(background_color_or_metacolor,
																Qtransparent) 
																|| 
																EQ(background_color_or_metacolor,
																Qbackground)) 
																    {
															    temp 
																    = 
																    ISVREF(Current_color_map,
																    (SI_Long)5L);
															    if (temp);
															    else
																temp 
																	= 
																	map_to_color_value_1(Qwhite);
															    current_background_color_value 
																    = 
																    temp;
															}
															else
															    current_background_color_value 
																    = 
																    EQ(background_color_or_metacolor,
																    ISVREF(Current_color_map,
																    (SI_Long)6L)) 
																    ?
																     
																    ISVREF(Current_color_map,
																    (SI_Long)7L) 
																    :
																     
																    map_to_color_value_1(background_color_or_metacolor);
														    }
														    else if (EQ(color_or_metacolor,
															    Qforeground) 
															    || 
															    EQ(color_or_metacolor,
															    Qworkspace_foreground)) 
																{
															temp 
																= 
																ISVREF(Current_color_map,
																(SI_Long)4L);
															if (temp);
															else
															    temp 
																    = 
																    map_to_color_value_1(Qblack);
															current_background_color_value 
																= 
																temp;
														    }
														    else
															current_background_color_value 
																= 
																EQ(color_or_metacolor,
																ISVREF(Current_color_map,
																(SI_Long)6L)) 
																?
																 
																ISVREF(Current_color_map,
																(SI_Long)7L) 
																:
																 
																map_to_color_value_1(color_or_metacolor);
														}
														else
														    current_background_color_value 
															    = 
															    EQ(color_or_metacolor,
															    ISVREF(Current_color_map,
															    (SI_Long)6L)) 
															    ?
															     
															    ISVREF(Current_color_map,
															    (SI_Long)7L) 
															    :
															     
															    map_to_color_value_1(color_or_metacolor);
														PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
															1);
														  LOCK(Editing_new_table);
														  if (PUSH_UNWIND_PROTECT(0)) 
															      {
														      current_annotated_frame 
															      = 
															      New_table;
														      PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
															      0);
															if (EQ(edit_action,
																Qedit_cell_expression) 
																|| 
																EQ(edit_action,
																Qedit_cell_format)) 
																    {
															    result = track_mouse_for_new_table(x_in_window,
																    y_in_window,
																    T);
															    cell_subpart 
																    = 
																    NTH_VALUE((SI_Long)3L,
																     
																    result);
															    SAVE_VALUES(start_edit_of_annotation_subexpression(4,
																    Current_annotated_frame,
																    cell_subpart,
																    getf(list_constant_14,
																    edit_action,
																    _),
																    getf(list_constant_15,
																    edit_action,
																    _)));
															}
															else if (EQ(edit_action,
																Qadd_row) 
																|| 
																EQ(edit_action,
																Qdelete_row) 
																|| 
																EQ(edit_action,
																Qadd_column) 
																|| 
																EQ(edit_action,
																Qdelete_column)) 
																    {
															    result = track_mouse_for_new_table(x_in_window,
																    y_in_window,
																    Nil);
															    MVS_3(result,
																    table,
																    row_index,
																    column_index);
															    SAVE_VALUES(table_block_insert_or_delete(table,
																    FIXNUM_SUB1(row_index),
																    FIXNUM_SUB1(column_index),
																    edit_action,
																    FIX((SI_Long)1L)));
															}
															else
															    SAVE_VALUES(VALUES_1(Qnil));
														      POP_SPECIAL();
														  }
														  POP_UNWIND_PROTECT(0);
														  UNLOCK(Editing_new_table);
														  CONTINUE_UNWINDING(0);
														POP_SPECIAL();
													      POP_SPECIAL();
													    POP_SPECIAL();
													  POP_SPECIAL();
													POP_SPECIAL();
												      POP_SPECIAL();
												    POP_SPECIAL();
												  POP_SPECIAL();
											      }
											      POP_UNWIND_PROTECT(1);
											      UNLOCK(For_image_plane);
											      CONTINUE_UNWINDING(1);
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
								}
								POP_UNWIND_PROTECT(2);
								UNLOCK(On_window_without_drawing);
								CONTINUE_UNWINDING(2);
							      POP_SPECIAL();
							    POP_SPECIAL();
							  POP_SPECIAL();
							POP_SPECIAL();
						      POP_SPECIAL();
						  }
						  else
						      SAVE_VALUES(VALUES_1(Nil));
						POP_SPECIAL();
					      POP_SPECIAL();
					    POP_SPECIAL();
					  POP_SPECIAL();
				      }
				      else
					  SAVE_VALUES(VALUES_1(Nil));
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
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(3);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(3);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* MOUSE-OVER-CELL-IN-NEW-TABLE-P */
Object mouse_over_cell_in_new_table_p(new_table)
    Object new_table;
{
    Object thing;
    Declare_special(1);
    Object result;

    x_note_fn_call(178,81);
    PUSH_SPECIAL_WITH_SYMBOL(New_table,Qnew_table,new_table,0);
      thing = ISVREF(ISVREF(Current_workstation,(SI_Long)11L),(SI_Long)5L);
      if (SIMPLE_VECTOR_P(thing))
	  result = VALUES_1(EQ(ISVREF(thing,(SI_Long)0L),
		  Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct) 
		  ? T : Nil);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* CHANGE-IN-FREEFORM-TABLE-DIMENSIONS-IS-OK-P */
Object change_in_freeform_table_dimensions_is_ok_p(freeform_table,
	    row_delta_init,column_delta_init)
    Object freeform_table, row_delta_init, column_delta_init;
{
    Object cell_annotations, row_maximum, column_maximum;
    SI_Long row_delta, column_delta;
    Declare_special(2);
    Object result;

    x_note_fn_call(178,82);
    row_delta = IFIX(row_delta_init);
    column_delta = IFIX(column_delta_init);
    cell_annotations = ISVREF(freeform_table,(SI_Long)18L);
    row_maximum = get_simple_part_feature(cell_annotations,Qrow_maximum);
    PUSH_SPECIAL_WITH_SYMBOL(Row_maximum,Qrow_maximum,row_maximum,1);
      column_maximum = get_simple_part_feature(cell_annotations,
	      Qcolumn_maximum);
      PUSH_SPECIAL_WITH_SYMBOL(Column_maximum,Qcolumn_maximum,column_maximum,
	      0);
	if (table_dimension_p(FIX(IFIX(Row_maximum) + row_delta)) && 
		table_dimension_p(FIX(IFIX(Column_maximum) + column_delta)))
	    result = item_is_either_not_permanent_or_from_an_editable_module_p(freeform_table);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qfreeform_table;     /* freeform-table */

/* ROW-AND-COLUMN-INDEX-AVAILABLE-P */
Object row_and_column_index_available_p(mouse_pointer)
    Object mouse_pointer;
{
    Object block, image_plane, original_x_in_window, original_y_in_window, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(178,83);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (block && image_plane && original_x_in_window && original_y_in_window) {
	if (SIMPLE_VECTOR_P(block) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L &&  
		!EQ(ISVREF(block,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qfreeform_table,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
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
	if (temp)
	    return change_in_freeform_table_is_meaningful_p(block,
		    FIX((SI_Long)0L),FIX((SI_Long)0L),image_plane,
		    original_x_in_window,original_y_in_window);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CHANGE-IN-FREEFORM-TABLE-IS-MEANINGFUL-P */
Object change_in_freeform_table_is_meaningful_p(freeform_table,
	    row_delta_init,column_delta_init,image_plane,
	    original_x_in_window,original_y_in_window)
    Object freeform_table, row_delta_init, column_delta_init, image_plane;
    Object original_x_in_window, original_y_in_window;
{
    Object current_annotated_frame, current_window_1, drawing_on_window;
    Object current_drawing_transfer_mode, type_of_current_window;
    Object current_native_window_qm, current_color_map, temp;
    Object current_background_color_value, current_foreground_color_value;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, temp_1, row_index, column_index;
    SI_Long row_delta, column_delta;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(22);
    Object result;

    x_note_fn_call(178,84);
    SAVE_STACK();
    row_delta = IFIX(row_delta_init);
    column_delta = IFIX(column_delta_init);
    if ( 
	    !TRUEP(item_is_either_not_permanent_or_from_an_editable_module_p(freeform_table))) 
		{
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(2)) {
	current_annotated_frame = freeform_table;
	PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		21);
	  LOCK(On_window_without_drawing);
	  if (PUSH_UNWIND_PROTECT(1)) {
	      current_window_1 = ISVREF(ISVREF(image_plane,(SI_Long)2L),
		      (SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
		      20);
		drawing_on_window = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
			19);
		  current_drawing_transfer_mode = 
			  EQ(Current_drawing_transfer_mode,Kxor) ? 
			  Current_drawing_transfer_mode : 
			  ISVREF(Current_window,(SI_Long)30L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
			  18);
		    type_of_current_window = ISVREF(Current_window,
			    (SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
			    17);
		      current_native_window_qm = ISVREF(Current_window,
			      (SI_Long)17L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
			      16);
			current_color_map = ISVREF(Current_window,
				(SI_Long)20L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
				15);
			  temp = ISVREF(Current_color_map,(SI_Long)5L);
			  if (temp);
			  else
			      temp = map_to_color_value_1(Qwhite);
			  current_background_color_value = temp;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
				  14);
			    temp = ISVREF(Current_color_map,(SI_Long)4L);
			    if (temp);
			    else
				temp = map_to_color_value_1(Qblack);
			    current_foreground_color_value = temp;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
				    13);
			      current_frame_transform_qm = Nil;
			      current_image_x_scale = ISVREF(image_plane,
				      (SI_Long)11L);
			      current_image_y_scale = ISVREF(image_plane,
				      (SI_Long)12L);
			      current_x_origin_of_drawing = 
				      ISVREF(image_plane,(SI_Long)13L);
			      current_y_origin_of_drawing = 
				      ISVREF(image_plane,(SI_Long)14L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
				      12);
				PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
					11);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
					  10);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
					    9);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
					      8);
					LOCK(For_image_plane);
					if (PUSH_UNWIND_PROTECT(0)) {
					    current_pane = 
						    ISVREF(image_plane,
						    (SI_Long)2L);
					    current_image_plane = image_plane;
					    loose_left_edge_of_visible_workspace_area 
						    = ISVREF(image_plane,
						    (SI_Long)23L);
					    loose_top_edge_of_visible_workspace_area 
						    = ISVREF(image_plane,
						    (SI_Long)24L);
					    loose_right_edge_of_visible_workspace_area 
						    = ISVREF(image_plane,
						    (SI_Long)25L);
					    loose_bottom_edge_of_visible_workspace_area 
						    = ISVREF(image_plane,
						    (SI_Long)26L);
					    color_or_metacolor = 
						    ISVREF(image_plane,
						    (SI_Long)5L) ? 
						    ISVREF(ISVREF(image_plane,
						    (SI_Long)5L),
						    (SI_Long)22L) : Nil;
					    if (color_or_metacolor);
					    else
						color_or_metacolor = Qblack;
					    if (EQ(color_or_metacolor,
						    Qtransparent) || 
						    EQ(color_or_metacolor,
						    Qbackground)) {
						background_color_or_metacolor 
							= 
							ISVREF(image_plane,
							(SI_Long)5L) ? 
							ISVREF(ISVREF(image_plane,
							(SI_Long)5L),
							(SI_Long)21L) : Nil;
						if (background_color_or_metacolor);
						else
						    background_color_or_metacolor 
							    = Qwhite;
						if (EQ(background_color_or_metacolor,
							Qforeground) || 
							EQ(background_color_or_metacolor,
							Qworkspace_foreground)) 
							    {
						    temp = 
							    ISVREF(Current_color_map,
							    (SI_Long)4L);
						    if (temp);
						    else
							temp = 
								map_to_color_value_1(Qblack);
						    current_foreground_color_value 
							    = temp;
						}
						else if (EQ(background_color_or_metacolor,
							Qtransparent) || 
							EQ(background_color_or_metacolor,
							Qbackground)) {
						    temp = 
							    ISVREF(Current_color_map,
							    (SI_Long)5L);
						    if (temp);
						    else
							temp = 
								map_to_color_value_1(Qwhite);
						    current_foreground_color_value 
							    = temp;
						}
						else
						    current_foreground_color_value 
							    = 
							    EQ(background_color_or_metacolor,
							    ISVREF(Current_color_map,
							    (SI_Long)6L)) ?
							     
							    ISVREF(Current_color_map,
							    (SI_Long)7L) : 
							    map_to_color_value_1(background_color_or_metacolor);
					    }
					    else if (EQ(color_or_metacolor,
						    Qforeground) || 
						    EQ(color_or_metacolor,
						    Qworkspace_foreground)) {
						temp = 
							ISVREF(Current_color_map,
							(SI_Long)4L);
						if (temp);
						else
						    temp = 
							    map_to_color_value_1(Qblack);
						current_foreground_color_value 
							= temp;
					    }
					    else
						current_foreground_color_value 
							= 
							EQ(color_or_metacolor,
							ISVREF(Current_color_map,
							(SI_Long)6L)) ? 
							ISVREF(Current_color_map,
							(SI_Long)7L) : 
							map_to_color_value_1(color_or_metacolor);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
						    7);
					      PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
						      6);
						PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
							5);
						  PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
							  4);
						    PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
							    3);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
							      2);
							PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
								1);
							  color_or_metacolor 
								  = 
								  ISVREF(image_plane,
								  (SI_Long)5L) 
								  ? 
								  ISVREF(ISVREF(image_plane,
								  (SI_Long)5L),
								  (SI_Long)21L) 
								  : Nil;
							  if (color_or_metacolor);
							  else
							      color_or_metacolor 
								      = Qwhite;
							  if (EQ(color_or_metacolor,
								  Qtransparent) 
								  || 
								  EQ(color_or_metacolor,
								  Qbackground)) 
								      {
							      temp = 
								      ISVREF(Current_color_map,
								      (SI_Long)5L);
							      if (temp);
							      else
								  temp = 
									  map_to_color_value_1(Qwhite);
							      current_background_color_value 
								      = temp;
							  }
							  else if (EQ(color_or_metacolor,
								  Qforeground) 
								  || 
								  EQ(color_or_metacolor,
								  Qworkspace_foreground)) 
								      {
							      temp = 
								      ISVREF(image_plane,
								      (SI_Long)5L) 
								      ? 
								      ISVREF(ISVREF(image_plane,
								      (SI_Long)5L),
								      (SI_Long)22L) 
								      : Nil;
							      if (temp);
							      else
								  temp = 
									  Qblack;
							      color_or_metacolor 
								      = temp;
							      if (EQ(color_or_metacolor,
								      Qtransparent) 
								      || 
								      EQ(color_or_metacolor,
								      Qbackground)) 
									  {
								  background_color_or_metacolor 
									  = 
									  ISVREF(image_plane,
									  (SI_Long)5L) 
									  ?
									   
									  ISVREF(ISVREF(image_plane,
									  (SI_Long)5L),
									  (SI_Long)21L) 
									  :
									   Nil;
								  if (background_color_or_metacolor);
								  else
								      background_color_or_metacolor 
									      = 
									      Qwhite;
								  if (EQ(background_color_or_metacolor,
									  Qforeground) 
									  || 
									  EQ(background_color_or_metacolor,
									  Qworkspace_foreground)) 
									      {
								      temp 
									      = 
									      ISVREF(Current_color_map,
									      (SI_Long)4L);
								      if (temp);
								      else
									  temp 
										  = 
										  map_to_color_value_1(Qblack);
								      current_background_color_value 
									      = 
									      temp;
								  }
								  else if (EQ(background_color_or_metacolor,
									  Qtransparent) 
									  || 
									  EQ(background_color_or_metacolor,
									  Qbackground)) 
									      {
								      temp 
									      = 
									      ISVREF(Current_color_map,
									      (SI_Long)5L);
								      if (temp);
								      else
									  temp 
										  = 
										  map_to_color_value_1(Qwhite);
								      current_background_color_value 
									      = 
									      temp;
								  }
								  else
								      current_background_color_value 
									      = 
									      EQ(background_color_or_metacolor,
									      ISVREF(Current_color_map,
									      (SI_Long)6L)) 
									      ?
									       
									      ISVREF(Current_color_map,
									      (SI_Long)7L) 
									      :
									       
									      map_to_color_value_1(background_color_or_metacolor);
							      }
							      else if (EQ(color_or_metacolor,
								      Qforeground) 
								      || 
								      EQ(color_or_metacolor,
								      Qworkspace_foreground)) 
									  {
								  temp = 
									  ISVREF(Current_color_map,
									  (SI_Long)4L);
								  if (temp);
								  else
								      temp 
									      = 
									      map_to_color_value_1(Qblack);
								  current_background_color_value 
									  = 
									  temp;
							      }
							      else
								  current_background_color_value 
									  = 
									  EQ(color_or_metacolor,
									  ISVREF(Current_color_map,
									  (SI_Long)6L)) 
									  ?
									   
									  ISVREF(Current_color_map,
									  (SI_Long)7L) 
									  :
									   
									  map_to_color_value_1(color_or_metacolor);
							  }
							  else
							      current_background_color_value 
								      = 
								      EQ(color_or_metacolor,
								      ISVREF(Current_color_map,
								      (SI_Long)6L)) 
								      ? 
								      ISVREF(Current_color_map,
								      (SI_Long)7L) 
								      : 
								      map_to_color_value_1(color_or_metacolor);
							  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
								  0);
							    result = track_mouse_for_new_table(original_x_in_window,
								    original_y_in_window,
								    T);
							    MVS_3(result,
								    temp,
								    row_index,
								    column_index);
							    if (row_index 
								    && 
								    column_index) 
									{
								temp = 
									row_delta 
									== 
									(SI_Long)0L 
									? 
									(column_delta 
									== 
									(SI_Long)0L 
									? 
									T :
									 
									Nil) 
									: Qnil;
								if (temp)
								    SAVE_VALUES(VALUES_1(temp));
								else
								    SAVE_VALUES(change_in_freeform_table_dimensions_is_ok_p(freeform_table,
									    FIX(row_delta),
									    FIX(column_delta)));
							    }
							    else
								SAVE_VALUES(VALUES_1(Nil));
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
					UNLOCK(For_image_plane);
					CONTINUE_UNWINDING(0);
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
	  }
	  POP_UNWIND_PROTECT(1);
	  UNLOCK(On_window_without_drawing);
	  CONTINUE_UNWINDING(1);
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(2);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(2);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Projecting_to_collect_description_for_new_table, Qprojecting_to_collect_description_for_new_table);

DEFINE_VARIABLE_WITH_SYMBOL(Current_description_of_new_table, Qcurrent_description_of_new_table);

static Object Qdescribe_new_table_from_inside_projection;  /* describe-new-table-from-inside-projection */

/* DESCRIBE-NEW-TABLE */
Object describe_new_table()
{
    Object current_annotated_frame, projection_mode;
    Object current_projection_function_for_funcall, projection_focus_method;
    Object current_description_of_new_table, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, current_background_color_value;
    Object current_foreground_color_value, current_color_map;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(12);
    Object result;

    x_note_fn_call(178,85);
    SAVE_STACK();
    LOCK(Working_on_annotated_frame);
    if (PUSH_UNWIND_PROTECT(1)) {
	current_annotated_frame = Current_computation_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		11);
	  LOCK(Projecting_to_collect_description_for_new_table);
	  if (PUSH_UNWIND_PROTECT(0)) {
	      projection_mode = Qfuncall_on_focus_projection_mode;
	      current_projection_function_for_funcall = 
		      SYMBOL_FUNCTION(Qdescribe_new_table_from_inside_projection);
	      projection_focus_method = Nil;
	      current_description_of_new_table = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_description_of_new_table,Qcurrent_description_of_new_table,current_description_of_new_table,
		      10);
		PUSH_SPECIAL_WITH_SYMBOL(Projection_focus_method,Qprojection_focus_method,projection_focus_method,
			9);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_projection_function_for_funcall,Qcurrent_projection_function_for_funcall,current_projection_function_for_funcall,
			  8);
		    PUSH_SPECIAL_WITH_SYMBOL(Projection_mode,Qprojection_mode,projection_mode,
			    7);
		      current_image_x_scale = FIX((SI_Long)4096L);
		      current_image_y_scale = FIX((SI_Long)4096L);
		      current_x_origin_of_drawing = FIX((SI_Long)0L);
		      current_y_origin_of_drawing = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
			      6);
			PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
				5);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
				  4);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
				    3);
			      current_background_color_value = 
				      FIX((SI_Long)0L);
			      current_foreground_color_value = 
				      FIX((SI_Long)0L);
			      current_color_map = Off_window_color_map;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
				      2);
				PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					1);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					  0);
				    project_new_table();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		      SAVE_VALUES(VALUES_1(Current_description_of_new_table));
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_UNWIND_PROTECT(0);
	  UNLOCK(Projecting_to_collect_description_for_new_table);
	  CONTINUE_UNWINDING(0);
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Working_on_annotated_frame);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_11;  /* "The formating attributes for a simple cell in the table are:" */

static Object string_constant_12;  /* "The evaluation attributes for a simple expression in the table are:" */

/* DESCRIBE-NEW-TABLE-FROM-INSIDE-PROJECTION */
Object describe_new_table_from_inside_projection(why_called)
    Object why_called;
{
    Object temp, temp_1, temp_2, temp_3;

    x_note_fn_call(178,86);
    temp = describe_part_from_current_extent(Qformatted_part);
    temp_1 = eval_cons_1(copy_text_string(string_constant_11),Nil);
    temp_2 = describe_part_from_current_extent(Qcomputation_style_description);
    temp_3 = eval_cons_1(copy_text_string(string_constant_12),Nil);
    Current_description_of_new_table = nconc2(temp,nconc2(temp_1,
	    nconc2(temp_2,nconc2(temp_3,Current_description_of_new_table))));
    return VALUES_1(T);
}

static Object Qpart_type_description;  /* part-type-description */

/* DESCRIBE-PART-FROM-CURRENT-EXTENT */
Object describe_part_from_current_extent(part_type)
    Object part_type;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object part_type_description, temp, hidden_features, part_features;
    Object part_feature_name, part_feature_user_visible_qm, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object outstanding_part_description, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4, ab_loop_iter_flag_, cummulative_part_description;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, level;
    Declare_special(5);

    x_note_fn_call(178,87);
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
	      part_type_description = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(part_type),
		      Qpart_type_description);
	      temp = CDDDDR(part_type_description);
	      hidden_features = CAR(temp);
	      temp = CDR(part_type_description);
	      part_features = CAR(temp);
	      part_feature_name = Nil;
	      part_feature_user_visible_qm = Nil;
	      ab_loop_list_ = part_features;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	    next_loop:
	      temp = CDR(ab_loop_list_);
	      temp = CAR(temp);
	      part_feature_name = CAR(temp);
	      temp = CDR(ab_loop_list_);
	      temp = CAR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      temp = CDR(temp);
	      part_feature_user_visible_qm = CAR(temp);
	      if (part_feature_user_visible_qm &&  
		      !TRUEP(memq_function(part_feature_name,
			  hidden_features))) {
		  outstanding_part_description = Nil;
		  ab_loop_list__1 = Stack_of_current_part_descriptions;
		  level = (SI_Long)1L;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__3 = Nil;
		  ab_loopvar__4 = Nil;
		  ab_loop_iter_flag_ = T;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_1;
		  outstanding_part_description = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  if ( !TRUEP(ab_loop_iter_flag_))
		      level = level + (SI_Long)1L;
		  if (part_has_feature_p(outstanding_part_description,
			  part_feature_name)) {
		      temp = part_feature_name;
		      ab_loopvar__4 = slot_value_list_2(temp,
			      get_simple_part_feature(outstanding_part_description,
			      part_feature_name));
		      if (ab_loopvar__4) {
			  if (ab_loopvar__3)
			      M_CDR(ab_loopvar__3) = ab_loopvar__4;
			  else
			      ab_loopvar__2 = ab_loopvar__4;
			  ab_loopvar__3 = last(ab_loopvar__4,_);
		      }
		  }
		  ab_loop_iter_flag_ = Nil;
		  goto next_loop_1;
		end_loop_1:
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
	      }
	      ab_loop_list_ = CDDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      goto next_loop;
	    end_loop:
	      temp = ab_loopvar_;
	      goto end_2;
	      temp = Qnil;
	    end_2:;
	      cummulative_part_description = slot_value_cons_1(part_type,temp);
	      write_part_description(4,cummulative_part_description,T,
		      FIX((SI_Long)5L),T);
	      reclaim_slot_value_list_1(cummulative_part_description);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return eval_cons_1(temp,Nil);
}

void new_tables_INIT()
{
    Object named_dynamic_extent_description, temp, temp_1, temp_2;
    Object table_dimensions_evaluation_setter_1;
    Object table_dimensions_evaluation_getter_1;
    Object reclaim_structure_for_new_table_spot_1, type_description;
    Object reclaim_structure_for_new_table_cell_spot_1;
    Object reclaim_structure_for_new_table_background_spot_1;
    Object AB_package, Qnamed_dynamic_extent_description, list_constant_136;
    Object Qnew_tables, string_constant_46, list_constant_126;
    Object list_constant_135, Qget_simple_part_feature, list_constant_134;
    Object list_constant_133, list_constant_131, list_constant_132;
    Object list_constant_129, Qget_subpart_of_collection, list_constant_130;
    Object list_constant_128, Qclasses_which_define, Qdeactivate;
    Object Qdeactivate_for_new_table, Qactivate, Qactivate_for_new_table;
    Object list_constant_127, string_constant_45, Qupdate_part_dependencies;
    Object Qupdate_part_dependencies_for_new_table, Qgenerate_spot;
    Object Qgenerate_spot_for_new_table, Qtype_of_frame_represented;
    Object Qabstract_type, Qimage_plane_spot, Qenclosing_spot_type;
    Object Qinnermost_spot_p, Qtype_description_of_type;
    Object Qnew_table_background_spot, Qreclaim_structure;
    Object Qoutstanding_new_table_background_spot_count;
    Object Qnew_table_background_spot_structure_memory_usage, Qutilities2;
    Object string_constant_44;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_43, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qnew_table_cell_spot;
    Object Qoutstanding_new_table_cell_spot_count;
    Object Qnew_table_cell_spot_structure_memory_usage, string_constant_42;
    Object string_constant_41, Qnew_table_spot;
    Object Qoutstanding_new_table_spot_count;
    Object Qnew_table_spot_structure_memory_usage, string_constant_40;
    Object string_constant_39, Qdraw, Qdraw_for_new_table;
    Object Qrecompile_expression_at_component_particulars;
    Object Qrecompile_expression_at_component_particulars_for_new_table;
    Object Qdenote_cell_array_element;
    Object Qdenote_cell_array_element_for_new_table, Qplace_reference_of_cell;
    Object Qplace_reference_of_cell_for_new_table;
    Object Qinitialize_off_window_color_map, list_constant_125, Kfuncall;
    Object Qexpression_cell_updated, Qexpression_cell_updated_for_new_table;
    Object Qupdate_frame_status_and_notes;
    Object Qupdate_frame_status_and_notes_for_new_table, list_constant_124;
    Object list_constant_123, list_constant_122, list_constant_121;
    Object Qborder_color, string_constant_38, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_new_table, Qinitialize;
    Object Qinitialize_for_new_table, Qset_table_cells, Qget_table_cells;
    Object Qinitial_table_cells, list_constant_120, list_constant_119;
    Object list_constant_117, list_constant_118, list_constant_116;
    Object list_constant_115, list_constant_114, Qab_or, list_constant_113;
    Object list_constant_112, list_constant_111, list_constant_110;
    Object list_constant_109, list_constant_108, list_constant_87;
    Object list_constant_107, list_constant_106, list_constant_105;
    Object Qmay_request_data_seeking, Qmay_request_event_updates;
    Object Qtime_out_when_requesting_data_seeking, Qupdate_only_when_shown;
    Object Qvalue_domain, Qinitial_scan_wait_interval, Qscan_interval;
    Object Qpriority, list_constant_90, list_constant_88, list_constant_104;
    Object list_constant_103, list_constant_102, Qtext_size, Qtext_alignment;
    Object Qtext_color, list_constant_101, list_constant_100, list_constant_99;
    Object list_constant_98, list_constant_97, list_constant_96, Qextra_large;
    Object Qlarge, Qsmall, list_constant_95, Qright, Qcenter, Qleft;
    Object list_constant_67, list_constant_94, list_constant_93;
    Object list_constant_92, list_constant_91, list_constant_89;
    Object list_constant_86, list_constant_85, list_constant_84;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object list_constant_80, list_constant_79, list_constant_70;
    Object list_constant_57, list_constant_78, list_constant_77;
    Object list_constant_76, list_constant_75, list_constant_74;
    Object list_constant_73, list_constant_72, list_constant_71;
    Object list_constant_69, Qg2_simulator, Qinference_engine;
    Object list_constant_68, list_constant_66, list_constant_65, Qdatum, Qtext;
    Object Qab_class, Qvirtual_attributes_local_to_class, list_constant_64;
    Object list_constant_63, list_constant_62, Qobsolete_datum, Qunknown_datum;
    Object Qslot_putter, Qput_cell_annotations, Qnamed, list_constant_61;
    Object list_constant_60, list_constant_59, list_constant_58;
    Object list_constant_56, Qtype_specification_simple_expansion;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_table_dimensions_for_slot;
    Object string_constant_37, string_constant_36, Qreduce_annotation;
    Object Qslot_value_writer, Qwrite_table_dimensions_from_slot;
    Object list_constant_55, Qtable_size, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, list_constant_54, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, Qitem;
    Object Qput_default_evaluation_setting, Qput_default_cell_format;
    Object string_constant_24, list_constant_53, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object Qsemantic_check_cell_part_type, list_constant_52;
    Object Qexit_part_feature_row_height, Qenter_part_feature_row_height;
    Object Qslot_value_number, Qspecial_variable;
    Object Qsymbol_standing_in_for_unbound, list_constant_51;
    Object Qexit_part_feature_column_width, Qenter_part_feature_column_width;
    Object Qsimple_type_specification, list_constant_50, Qslot_value_number_p;
    Object list_constant_49, Qexit_part_feature_text_value;
    Object Qenter_part_feature_text_value, Qsimple_formatted_text;
    Object list_constant_48, Qexit_part_feature_cell_contents;
    Object Qenter_part_feature_cell_contents, list_constant_47;
    Object Qexit_part_feature_column_maximum;
    Object Qenter_part_feature_column_maximum, Qtable_dimension;
    Object list_constant_46, Qexit_part_feature_row_maximum;
    Object Qenter_part_feature_row_maximum, Qtype_error_printer;
    Object string_constant_19, list_constant_45, Qtable_dimension_p;
    Object list_constant_32, Qexit_subpart_exceptions;
    Object Qenter_subpart_exceptions, list_constant_37, list_constant_29;
    Object Qexit_subpart_defaults, Qenter_subpart_defaults, list_constant_26;
    Object Qexit_part_feature_subparts, Qenter_part_feature_subparts;
    Object list_constant_44, list_constant_38, list_constant_40;
    Object list_constant_39, Qparts, string_constant_18, list_constant_43;
    Object Qsubparts_collection, list_constant_42, list_constant_41;
    Object Qchildren_part_types, Quser_spelling, Qincludes, list_constant_19;
    Object string_constant_17, list_constant_36, list_constant_33;
    Object list_constant_35, list_constant_34, Qline_color, Qhidden_features;
    Object string_constant_16, list_constant_25, list_constant_31;
    Object list_constant_30, Qcall_handlers, list_constant_28;
    Object list_constant_27, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object string_constant_15, list_constant_18, list_constant_17;
    Object string_constant_14, list_constant_16, string_constant_13;

    x_note_fn_call(178,88);
    SET_PACKAGE("AB");
    string_constant_13 = STATIC_STRING("WORKING-ON-NEW-TABLE");
    if (Working_on_new_table == UNBOUND)
	Working_on_new_table = make_recursive_lock(2,Kname,string_constant_13);
    AB_package = STATIC_PACKAGE("AB");
    Qworking_on_new_table = STATIC_SYMBOL("WORKING-ON-NEW-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworking_on_new_table,Working_on_new_table);
    Qnew_tables = STATIC_SYMBOL("NEW-TABLES",AB_package);
    Qworking_on_annotated_frame = 
	    STATIC_SYMBOL("WORKING-ON-ANNOTATED-FRAME",AB_package);
    list_constant_16 = STATIC_CONS(Qworking_on_annotated_frame,Qnil);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qworking_on_new_table,
	    Qnew_tables,Nil,list_constant_16,Qnil,Qnil,Nil);
    mutate_global_property(Qworking_on_new_table,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_14 = STATIC_STRING("EDITING-NEW-TABLE");
    if (Editing_new_table == UNBOUND)
	Editing_new_table = make_recursive_lock(2,Kname,string_constant_14);
    Qediting_new_table = STATIC_SYMBOL("EDITING-NEW-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qediting_new_table,Editing_new_table);
    Qfor_image_plane = STATIC_SYMBOL("FOR-IMAGE-PLANE",AB_package);
    list_constant_17 = STATIC_CONS(Qfor_image_plane,Qnil);
    list_constant_18 = STATIC_CONS(Qworking_on_new_table,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qediting_new_table,
	    Qnew_tables,Nil,list_constant_17,Qnil,list_constant_18,Nil);
    mutate_global_property(Qediting_new_table,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    string_constant_15 = STATIC_STRING("NEW-TABLE");
    if (New_table == UNBOUND)
	New_table = make_recursive_lock(2,Kname,string_constant_15);
    Qnew_table = STATIC_SYMBOL("NEW-TABLE",AB_package);
    Qparts = STATIC_SYMBOL("PARTS",AB_package);
    Qbasic_part = STATIC_SYMBOL("BASIC-PART",AB_package);
    list_constant_19 = STATIC_CONS(Qbasic_part,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qnew_table,Qparts,Nil,
	    Qnil,Qnil,list_constant_19,Nil);
    mutate_global_property(Qnew_table,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qsymbol_standing_in_for_unbound = 
	    STATIC_SYMBOL("SYMBOL-STANDING-IN-FOR-UNBOUND",AB_package);
    if (Current_new_table == UNBOUND)
	Current_new_table = Qsymbol_standing_in_for_unbound;
    Qchildren_part_types = STATIC_SYMBOL("CHILDREN-PART-TYPES",AB_package);
    Qrow = STATIC_SYMBOL("ROW",AB_package);
    Qcell = STATIC_SYMBOL("CELL",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qchildren_part_types,Qrow,
	    Qcell);
    list_constant_21 = STATIC_CONS(list_constant_20,Qnil);
    def_part_type_1(Qnew_table,list_constant_19,list_constant_21);
    Qsubparts = STATIC_SYMBOL("SUBPARTS",AB_package);
    Qsubparts_collection = STATIC_SYMBOL("SUBPARTS-COLLECTION",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qrow,Qcell);
    list_constant_25 = STATIC_CONS(Qsubparts_collection,list_constant_22);
    Qenter_part_feature_subparts = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-SUBPARTS",AB_package);
    Qexit_part_feature_subparts = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-SUBPARTS",AB_package);
    Qcall_handlers = STATIC_SYMBOL("CALL-HANDLERS",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_part_feature_subparts);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_part_feature_subparts);
    list_constant_26 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_23,list_constant_24);
    def_part_feature_1(Qnew_table,Qsubparts,list_constant_25,Qsubparts,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_26);
    Qsubpart_defaults = STATIC_SYMBOL("SUBPART-DEFAULTS",AB_package);
    Qenter_subpart_defaults = STATIC_SYMBOL("ENTER-SUBPART-DEFAULTS",
	    AB_package);
    Qexit_subpart_defaults = STATIC_SYMBOL("EXIT-SUBPART-DEFAULTS",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_defaults);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_defaults);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_27,list_constant_28);
    def_part_feature_1(Qnew_table,Qsubpart_defaults,list_constant_25,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_29);
    Qsubpart_exceptions = STATIC_SYMBOL("SUBPART-EXCEPTIONS",AB_package);
    Qenter_subpart_exceptions = STATIC_SYMBOL("ENTER-SUBPART-EXCEPTIONS",
	    AB_package);
    Qexit_subpart_exceptions = STATIC_SYMBOL("EXIT-SUBPART-EXCEPTIONS",
	    AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_exceptions);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_exceptions);
    list_constant_32 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_30,list_constant_31);
    def_part_feature_1(Qnew_table,Qsubpart_exceptions,list_constant_25,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_32);
    string_constant_16 = STATIC_STRING("CELL");
    if (Cell == UNBOUND)
	Cell = make_recursive_lock(2,Kname,string_constant_16);
    Qformatted_part = STATIC_SYMBOL("FORMATTED-PART",AB_package);
    list_constant_33 = STATIC_CONS(Qformatted_part,list_constant_19);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qcell,Qparts,Nil,Qnil,
	    Qnil,list_constant_33,Nil);
    mutate_global_property(Qcell,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_cell == UNBOUND)
	Current_cell = Qsymbol_standing_in_for_unbound;
    Qincludes = STATIC_SYMBOL("INCLUDES",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qincludes,Qformatted_part);
    Qhidden_features = STATIC_SYMBOL("HIDDEN-FEATURES",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qhidden_features,Qline_color);
    list_constant_36 = STATIC_LIST((SI_Long)2L,list_constant_34,
	    list_constant_35);
    def_part_type_1(Qcell,list_constant_33,list_constant_36);
    list_constant_37 = STATIC_CONS(Qsubparts_collection,Qnil);
    def_part_feature_1(Qcell,Qsubparts,list_constant_37,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_26);
    def_part_feature_1(Qcell,Qsubpart_defaults,list_constant_37,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_29);
    def_part_feature_1(Qcell,Qsubpart_exceptions,list_constant_37,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_32);
    string_constant_17 = STATIC_STRING("ROW");
    if (Row == UNBOUND)
	Row = make_recursive_lock(2,Kname,string_constant_17);
    list_constant_38 = STATIC_CONS(Qcell,list_constant_19);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qrow,Qparts,Nil,Qnil,
	    Qnil,list_constant_38,Nil);
    mutate_global_property(Qrow,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_row == UNBOUND)
	Current_row = Qsymbol_standing_in_for_unbound;
    list_constant_7 = STATIC_CONS(Qcell,Qnil);
    list_constant_39 = STATIC_CONS(Qincludes,list_constant_7);
    Quser_spelling = STATIC_SYMBOL("USER-SPELLING",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Quser_spelling,Qnil);
    list_constant_41 = STATIC_CONS(Qchildren_part_types,list_constant_7);
    list_constant_42 = STATIC_LIST((SI_Long)3L,list_constant_39,
	    list_constant_40,list_constant_41);
    def_part_type_1(Qrow,list_constant_38,list_constant_42);
    list_constant_43 = STATIC_CONS(Qsubparts_collection,list_constant_7);
    def_part_feature_1(Qrow,Qsubparts,list_constant_43,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_26);
    def_part_feature_1(Qrow,Qsubpart_defaults,list_constant_43,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_29);
    def_part_feature_1(Qrow,Qsubpart_exceptions,list_constant_43,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_32);
    string_constant_18 = STATIC_STRING("COLUMN");
    if (Column == UNBOUND)
	Column = make_recursive_lock(2,Kname,string_constant_18);
    Qcolumn = STATIC_SYMBOL("COLUMN",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qcolumn,Qparts,Nil,Qnil,
	    Qnil,list_constant_38,Nil);
    mutate_global_property(Qcolumn,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_column == UNBOUND)
	Current_column = Qsymbol_standing_in_for_unbound;
    list_constant_44 = STATIC_LIST((SI_Long)2L,list_constant_39,
	    list_constant_40);
    def_part_type_1(Qcolumn,list_constant_38,list_constant_44);
    def_part_feature_1(Qcolumn,Qsubparts,list_constant_37,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_26);
    def_part_feature_1(Qcolumn,Qsubpart_defaults,list_constant_37,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_29);
    def_part_feature_1(Qcolumn,Qsubpart_exceptions,list_constant_37,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_32);
    Qtable_dimension = STATIC_SYMBOL("TABLE-DIMENSION",AB_package);
    Qtable_dimension_p = STATIC_SYMBOL("TABLE-DIMENSION-P",AB_package);
    SET_SYMBOL_FUNCTION(Qtable_dimension_p,
	    STATIC_FUNCTION(table_dimension_p,NIL,FALSE,1,1));
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qtable_dimension_p);
    Qsimple_type_specification = STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",
	    AB_package);
    mutate_global_property(Qtable_dimension,list_constant_45,
	    Qsimple_type_specification);
    string_constant_19 = STATIC_STRING("is not in the range from 1 to 100");
    Qtype_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    mutate_global_property(Qtable_dimension,string_constant_19,
	    Qtype_error_printer);
    if (Row_maximum == UNBOUND)
	Row_maximum = Qsymbol_standing_in_for_unbound;
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qrow_maximum = STATIC_SYMBOL("ROW-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrow_maximum,Row_maximum);
    Qnumber_of_rows = STATIC_SYMBOL("NUMBER-OF-ROWS",AB_package);
    Qenter_part_feature_row_maximum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-ROW-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_row_maximum,
	    STATIC_FUNCTION(enter_part_feature_row_maximum,NIL,FALSE,1,1));
    Qexit_part_feature_row_maximum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-ROW-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_row_maximum,
	    STATIC_FUNCTION(exit_part_feature_row_maximum,NIL,FALSE,0,0));
    Qspecial_variable = STATIC_SYMBOL("SPECIAL-VARIABLE",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qrow_maximum);
    def_part_feature_1(Qnew_table,Qrow_maximum,Qtable_dimension,
	    Qnumber_of_rows,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_row_maximum),
	    SYMBOL_FUNCTION(Qexit_part_feature_row_maximum),list_constant_46);
    if (Column_maximum == UNBOUND)
	Column_maximum = Qsymbol_standing_in_for_unbound;
    Qcolumn_maximum = STATIC_SYMBOL("COLUMN-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolumn_maximum,Column_maximum);
    Qnumber_of_columns = STATIC_SYMBOL("NUMBER-OF-COLUMNS",AB_package);
    Qenter_part_feature_column_maximum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-COLUMN-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_column_maximum,
	    STATIC_FUNCTION(enter_part_feature_column_maximum,NIL,FALSE,1,1));
    Qexit_part_feature_column_maximum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-COLUMN-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_column_maximum,
	    STATIC_FUNCTION(exit_part_feature_column_maximum,NIL,FALSE,0,0));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qcolumn_maximum);
    def_part_feature_1(Qnew_table,Qcolumn_maximum,Qtable_dimension,
	    Qnumber_of_columns,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_column_maximum),
	    SYMBOL_FUNCTION(Qexit_part_feature_column_maximum),
	    list_constant_47);
    Qcell_contents = STATIC_SYMBOL("CELL-CONTENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcell_contents,Cell_contents);
    if (Cell_contents == UNBOUND)
	Cell_contents = Qsymbol_standing_in_for_unbound;
    Qcell_expression_and_text = STATIC_SYMBOL("CELL-EXPRESSION-AND-TEXT",
	    AB_package);
    Qenter_part_feature_cell_contents = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CELL-CONTENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_cell_contents,
	    STATIC_FUNCTION(enter_part_feature_cell_contents,NIL,FALSE,1,1));
    Qexit_part_feature_cell_contents = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CELL-CONTENTS",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_cell_contents,
	    STATIC_FUNCTION(exit_part_feature_cell_contents,NIL,FALSE,0,0));
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qcell_contents);
    def_part_feature_1(Qcell,Qcell_contents,Qcell_expression_and_text,
	    Qcell_contents,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_cell_contents),
	    SYMBOL_FUNCTION(Qexit_part_feature_cell_contents),
	    list_constant_48);
    Qsimple_formatted_text = STATIC_SYMBOL("SIMPLE-FORMATTED-TEXT",AB_package);
    mutate_global_property(Qsimple_formatted_text,Qcons,
	    Qsimple_type_specification);
    Qtext_value = STATIC_SYMBOL("TEXT-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtext_value,Text_value);
    if (Text_value == UNBOUND)
	Text_value = Qsymbol_standing_in_for_unbound;
    Qenter_part_feature_text_value = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-TEXT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_text_value,
	    STATIC_FUNCTION(enter_part_feature_text_value,NIL,FALSE,1,1));
    Qexit_part_feature_text_value = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-TEXT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_text_value,
	    STATIC_FUNCTION(exit_part_feature_text_value,NIL,FALSE,0,0));
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qtext_value);
    def_part_feature_1(Qcell,Qtext_value,Qsimple_formatted_text,
	    Qtext_value,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_text_value),
	    SYMBOL_FUNCTION(Qexit_part_feature_text_value),list_constant_49);
    Qslot_value_number = STATIC_SYMBOL("SLOT-VALUE-NUMBER",AB_package);
    Qslot_value_number_p = STATIC_SYMBOL("SLOT-VALUE-NUMBER-P",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_value_number_p,
	    STATIC_FUNCTION(slot_value_number_p,NIL,FALSE,1,1));
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qslot_value_number_p);
    mutate_global_property(Qslot_value_number,list_constant_50,
	    Qsimple_type_specification);
    Qcolumn_width = STATIC_SYMBOL("COLUMN-WIDTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcolumn_width,Column_width);
    if (Column_width == UNBOUND)
	Column_width = Qsymbol_standing_in_for_unbound;
    Qenter_part_feature_column_width = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-COLUMN-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_column_width,
	    STATIC_FUNCTION(enter_part_feature_column_width,NIL,FALSE,1,1));
    Qexit_part_feature_column_width = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-COLUMN-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_column_width,
	    STATIC_FUNCTION(exit_part_feature_column_width,NIL,FALSE,0,0));
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qcolumn_width);
    def_part_feature_1(Qcell,Qcolumn_width,Qslot_value_number,
	    Qcolumn_width,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_column_width),
	    SYMBOL_FUNCTION(Qexit_part_feature_column_width),list_constant_51);
    if (Row_height == UNBOUND)
	Row_height = Qsymbol_standing_in_for_unbound;
    Qrow_height = STATIC_SYMBOL("ROW-HEIGHT",AB_package);
    Qenter_part_feature_row_height = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-ROW-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_row_height,
	    STATIC_FUNCTION(enter_part_feature_row_height,NIL,FALSE,1,1));
    Qexit_part_feature_row_height = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-ROW-HEIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_row_height,
	    STATIC_FUNCTION(exit_part_feature_row_height,NIL,FALSE,0,0));
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qrow_height);
    def_part_feature_1(Qcell,Qrow_height,Qslot_value_number,Qrow_height,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_row_height),
	    SYMBOL_FUNCTION(Qexit_part_feature_row_height),list_constant_52);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    string_constant = 
	    STATIC_STRING("The width of individual cells can not be modified but you can change the default for the entire table.");
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    string_constant_1 = 
	    STATIC_STRING("The height of individual cells can not be modified but you can change the default for the entire table.");
    Qpart_type_description = STATIC_SYMBOL("PART-TYPE-DESCRIPTION",AB_package);
    Qsemantic_check_cell_part_type = 
	    STATIC_SYMBOL("SEMANTIC-CHECK-CELL-PART-TYPE",AB_package);
    SET_SYMBOL_FUNCTION(Qsemantic_check_cell_part_type,
	    STATIC_FUNCTION(semantic_check_cell_part_type,NIL,FALSE,1,1));
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcell),
	    Qpart_type_description);
    temp = CDDDDR(temp);
    temp_1 = CDDDR(temp);
    M_CAR(temp_1) = Qsemantic_check_cell_part_type;
    list_constant_53 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qnew_table,list_constant_53);
    string_constant_20 = STATIC_STRING("0");
    string_constant_21 = 
	    STATIC_STRING("1p4z8r83ZEy83ZEy839Uy839Uy00001n1l8o1l8l1l83Cy000004z8r83IFy83IFy839Uy839Uy00001n1l8o1l8l1l83Cy000004z8r833jy833jy839Uy839Uy0000");
    string_constant_22 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r833py833py839Uy839Uy00001o1l8o1l8l1l83Cy1m8p832vy000004z8r833qy833qy839Uy839Uy00001o1l8o1l8l1l83Cy1m8p8");
    string_constant_23 = STATIC_STRING("32wy00000");
    string_constant_24 = 
	    STATIC_STRING("1r8q1m839Uy1l9k1p83ZEy08o8l83Cy1p83IFy08o8l83Cy1p833jy08o8l83Cy1q833py08o8l83Cy1m8p832vy1q833qy08o8l83Cy1m8p832wy");
    temp = regenerate_optimized_constant(string_constant_20);
    temp_2 = regenerate_optimized_constant(LIST_3(string_constant_21,
	    string_constant_22,string_constant_23));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qnew_table,list_constant_53,Nil,temp,Nil,
	    temp_2,list_constant_53,
	    regenerate_optimized_constant(string_constant_24),Nil);
    Qdefault_cell_format = STATIC_SYMBOL("DEFAULT-CELL-FORMAT",AB_package);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    Qput_default_cell_format = STATIC_SYMBOL("PUT-DEFAULT-CELL-FORMAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_cell_format,
	    STATIC_FUNCTION(put_default_cell_format,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qdefault_cell_format,
	    SYMBOL_FUNCTION(Qput_default_cell_format),Qslot_putter);
    Qdefault_evaluation_setting = 
	    STATIC_SYMBOL("DEFAULT-EVALUATION-SETTING",AB_package);
    Qput_default_evaluation_setting = 
	    STATIC_SYMBOL("PUT-DEFAULT-EVALUATION-SETTING",AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_evaluation_setting,
	    STATIC_FUNCTION(put_default_evaluation_setting,NIL,FALSE,3,3));
    mutate_global_property(Qdefault_evaluation_setting,
	    SYMBOL_FUNCTION(Qput_default_evaluation_setting),Qslot_putter);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qitem,Qnew_table);
    check_if_superior_classes_are_defined(Qfreeform_table,list_constant_54);
    string_constant_25 = 
	    STATIC_STRING("1m1m8v836sy1m83-Cy533VyPossible exported slots and ~\n attribute mimics: <br><ul><LI>table-size: [number-of-rows: integer, ~\n num");
    string_constant_26 = 
	    STATIC_STRING("ber-of-columns:integer], ~\n <LI>default-cell-format: cell-format-part, ~\n <LI>default-evaluation-setting: computation-style-part");
    string_constant_27 = 
	    STATIC_STRING(", ~\n <li>row-annotations: \?\?\? ~\n <li>column-annotations: \?\?\?, ~\n <li>cell-annotations: \?\?\?, ~\n <li>cell-array: (named-structure ");
    string_constant_28 = 
	    STATIC_STRING("[cell-part, cell-expression: ~\n cell-expression-part, cell-format: cell-format-part, ~\n cell-value: item-or-value] *)</ul>");
    string_constant_29 = 
	    STATIC_STRING("1n4z8r833jy833jy836sy836sy00001p1m8p83A7y1l8l1l8z1l8o1l83Cy000004z8r833py833py836sy836sy00001p1l8o1l8l1l8z1l83Cy1m8p832vy000004z");
    string_constant_30 = 
	    STATIC_STRING("8r833qy833qy836sy836sy00001p1l8o1l8l1l8z1l83Cy1m8p832wy00000");
    string_constant_31 = 
	    STATIC_STRING("1p8q1o836sy1m83Ry839Uy1m8v836sy1m83-Cy533VyPossible exported slots and ~\n attribute mimics: <br><ul><LI>table-size: [number-of-r");
    string_constant_32 = 
	    STATIC_STRING("ows: integer, ~\n number-of-columns:integer], ~\n <LI>default-cell-format: cell-format-part, ~\n <LI>default-evaluation-setting: co");
    string_constant_33 = 
	    STATIC_STRING("mputation-style-part, ~\n <li>row-annotations: \?\?\? ~\n <li>column-annotations: \?\?\?, ~\n <li>cell-annotations: \?\?\?, ~\n <li>cell-arra");
    string_constant_34 = 
	    STATIC_STRING("y: (named-structure [cell-part, cell-expression: ~\n cell-expression-part, cell-format: cell-format-part, ~\n cell-value: item-or-");
    string_constant_35 = 
	    STATIC_STRING("value] *)</ul>1p833jy01m8p83A7y8l8z1r833py08o8l8z83Cy1m8p832vy1r833qy08o8l8z83Cy1m8p832wy");
    temp = regenerate_optimized_constant(LIST_4(string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28));
    temp_2 = regenerate_optimized_constant(LIST_2(string_constant_29,
	    string_constant_30));
    add_class_to_environment(9,Qfreeform_table,list_constant_54,Nil,temp,
	    Nil,temp_2,list_constant_54,
	    regenerate_optimized_constant(LIST_5(string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35)),Nil);
    Qcell_annotations = STATIC_SYMBOL("CELL-ANNOTATIONS",AB_package);
    Qtable_size = STATIC_SYMBOL("TABLE-SIZE",AB_package);
    alias_slot_name(3,Qcell_annotations,Qtable_size,Qfreeform_table);
    list_constant_55 = STATIC_CONS(Qcolumn_maximum,Qnil);
    list_constant = STATIC_CONS(Qrow_maximum,list_constant_55);
    Qtable_dimensions = STATIC_SYMBOL("TABLE-DIMENSIONS",AB_package);
    Qwrite_table_dimensions_from_slot = 
	    STATIC_SYMBOL("WRITE-TABLE-DIMENSIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_table_dimensions_from_slot,
	    STATIC_FUNCTION(write_table_dimensions_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qtable_dimensions,
	    SYMBOL_FUNCTION(Qwrite_table_dimensions_from_slot),
	    Qslot_value_writer);
    Qreduce_annotation = STATIC_SYMBOL("REDUCE-ANNOTATION",AB_package);
    string_constant_36 = 
	    STATIC_STRING("1o1n83A7y1n83-s2y1m9k83-Zy83-rvy1n83-Zyln1n83A7y1n83-rvy1m9k83-Zy83-s2y1n83-Zyln1o83-rvy1o1m9k9l1m9k83-hAy1m9k9m83Sy1n83BSymo9n1");
    string_constant_37 = 
	    STATIC_STRING("o83-s2y1o1m9k9l1m9k83-hBy1m9k9m83Sy1n83BSymo9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qreduce_annotation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_36,
	    string_constant_37)));
    Qcompile_table_dimensions_for_slot = 
	    STATIC_SYMBOL("COMPILE-TABLE-DIMENSIONS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_table_dimensions_for_slot,
	    STATIC_FUNCTION(compile_table_dimensions_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qtable_dimensions,
	    SYMBOL_FUNCTION(Qcompile_table_dimensions_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qtable_dimensions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_56 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qtable_dimensions),
	    Qtype_specification_simple_expansion,list_constant_56);
    list_constant_57 = STATIC_CONS(Qinteger,Qnil);
    list_constant_58 = STATIC_CONS(Qnumber_of_columns,list_constant_57);
    list_constant_59 = STATIC_CONS(Qnumber_of_rows,list_constant_57);
    list_constant_60 = STATIC_LIST((SI_Long)2L,list_constant_58,
	    list_constant_59);
    list_constant_61 = STATIC_LIST((SI_Long)3L,Qand,Qnumber_of_columns,
	    Qnumber_of_rows);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_60,list_constant_61);
    define_type_specification_explicit_complex_type(Qtable_dimensions,
	    list_constant_2);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Qtable_dimensions);
    Qset_simple_part_feature = STATIC_SYMBOL("SET-SIMPLE-PART-FEATURE",
	    AB_package);
    Qcurrent_part_description = STATIC_SYMBOL("CURRENT-PART-DESCRIPTION",
	    AB_package);
    Qcopy_for_slot_value = STATIC_SYMBOL("COPY-FOR-SLOT-VALUE",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    table_dimensions_evaluation_setter_1 = 
	    STATIC_FUNCTION(table_dimensions_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qtable_dimensions,
	    table_dimensions_evaluation_setter_1);
    table_dimensions_evaluation_getter_1 = 
	    STATIC_FUNCTION(table_dimensions_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtable_dimensions,
	    table_dimensions_evaluation_getter_1);
    Qadd_row = STATIC_SYMBOL("ADD-ROW",AB_package);
    Qdelete_row = STATIC_SYMBOL("DELETE-ROW",AB_package);
    Qadd_column = STATIC_SYMBOL("ADD-COLUMN",AB_package);
    Qdelete_column = STATIC_SYMBOL("DELETE-COLUMN",AB_package);
    Qput_cell_annotations = STATIC_SYMBOL("PUT-CELL-ANNOTATIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_cell_annotations,
	    STATIC_FUNCTION(put_cell_annotations,NIL,FALSE,3,3));
    mutate_global_property(Qcell_annotations,
	    SYMBOL_FUNCTION(Qput_cell_annotations),Qslot_putter);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qexpression_cell_index = STATIC_SYMBOL("EXPRESSION-CELL-INDEX",AB_package);
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    Qwarning_message_level_for_computation_style = 
	    STATIC_SYMBOL("WARNING-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qwarning_message_level = STATIC_SYMBOL("WARNING-MESSAGE-LEVEL",AB_package);
    Qtrace_message_level_for_computation_style = 
	    STATIC_SYMBOL("TRACE-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qtracing_message_level = STATIC_SYMBOL("TRACING-MESSAGE-LEVEL",AB_package);
    Qbreak_message_level_for_computation_style = 
	    STATIC_SYMBOL("BREAK-MESSAGE-LEVEL-FOR-COMPUTATION-STYLE",
	    AB_package);
    Qbreakpoint_level = STATIC_SYMBOL("BREAKPOINT-LEVEL",AB_package);
    Qexpression_source_text = STATIC_SYMBOL("EXPRESSION-SOURCE-TEXT",
	    AB_package);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qcell_evaluation_attributes = 
	    STATIC_SYMBOL("CELL-EVALUATION-ATTRIBUTES",AB_package);
    Qcell_display_text = STATIC_SYMBOL("CELL-DISPLAY-TEXT",AB_package);
    Qcell_display_value = STATIC_SYMBOL("CELL-DISPLAY-VALUE",AB_package);
    Qhighlighted_qm = STATIC_SYMBOL("HIGHLIGHTED\?",AB_package);
    Qcell_format = STATIC_SYMBOL("CELL-FORMAT",AB_package);
    Qcompiled_cell_expression = STATIC_SYMBOL("COMPILED-CELL-EXPRESSION",
	    AB_package);
    Qcell_expression_parse = STATIC_SYMBOL("CELL-EXPRESSION-PARSE",AB_package);
    Qsource_position = STATIC_SYMBOL("SOURCE-POSITION",AB_package);
    string_constant_2 = STATIC_STRING("~a;");
    string_constant_3 = STATIC_STRING("~a");
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_62 = STATIC_CONS(Qunknown_datum,Qnil);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    list_constant_63 = STATIC_CONS(Qobsolete_datum,Qnil);
    list_constant_3 = STATIC_LIST((SI_Long)4L,Qab_or,Qdatum,
	    list_constant_62,list_constant_63);
    string_constant_4 = 
	    STATIC_STRING("Error in the expression for cell (~a, ~a): ~s: ~a");
    list_constant_64 = STATIC_LIST((SI_Long)2L,list_constant_62,
	    list_constant_63);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_64);
    string_constant_5 = STATIC_STRING("Bad expression in ~S~%");
    Qcell_expression = STATIC_SYMBOL("CELL-EXPRESSION",AB_package);
    string_constant_6 = STATIC_STRING("~a~%~a~%");
    Qtable_cells = STATIC_SYMBOL("TABLE-CELLS",AB_package);
    temp_1 = CONS(Qtable_cells,All_virtual_attributes);
    All_virtual_attributes = temp_1;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qfreeform_table),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_1 = CONS(Qtable_cells,temp);
    set_property_value_function(get_symbol_properties_function(Qfreeform_table),
	    Qvirtual_attributes_local_to_class,temp_1);
    Qrow_annotations = STATIC_SYMBOL("ROW-ANNOTATIONS",AB_package);
    Qcolumn_annotations = STATIC_SYMBOL("COLUMN-ANNOTATIONS",AB_package);
    string_constant_7 = 
	    STATIC_STRING("This value does not represent a rectangular grid of cells.  ~\n               Please make sure that all the row sequences are the same ~\n               length.");
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_119 = STATIC_LIST((SI_Long)2L,Qab_class,Qfreeform_table);
    list_constant_114 = STATIC_LIST((SI_Long)2L,Qmember,Qnone);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_65 = STATIC_CONS(Qtext,Qnil);
    list_constant_87 = STATIC_CONS(Qexpression,list_constant_65);
    list_constant_108 = STATIC_LIST((SI_Long)2L,Qcell_display_value,Qdatum);
    list_constant_109 = STATIC_CONS(Qcell_display_text,list_constant_65);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)11L,Qmember,FIX((SI_Long)1L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),FIX((SI_Long)6L),FIX((SI_Long)7L),
	    FIX((SI_Long)8L),FIX((SI_Long)9L),FIX((SI_Long)10L));
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qpriority,list_constant_66);
    list_constant_67 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_89 = STATIC_CONS(Qcurrent_value,list_constant_67);
    Qscan_interval = STATIC_SYMBOL("SCAN-INTERVAL",AB_package);
    list_constant_68 = STATIC_CONS(Qnumber,Qnil);
    list_constant_79 = STATIC_CONS(Qscan_interval,list_constant_68);
    Qinitial_scan_wait_interval = 
	    STATIC_SYMBOL("INITIAL-SCAN-WAIT-INTERVAL",AB_package);
    list_constant_80 = STATIC_CONS(Qinitial_scan_wait_interval,
	    list_constant_68);
    Qvalue_domain = STATIC_SYMBOL("VALUE-DOMAIN",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qg2_simulator = STATIC_SYMBOL("G2-SIMULATOR",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qmember,Qinference_engine,
	    Qg2_simulator);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qvalue_domain,list_constant_69);
    Qupdate_only_when_shown = STATIC_SYMBOL("UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    list_constant_70 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_82 = STATIC_CONS(Qupdate_only_when_shown,list_constant_70);
    list_constant_71 = STATIC_LIST((SI_Long)5L,Qmember,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L),FIX((SI_Long)3L));
    list_constant_72 = STATIC_CONS(list_constant_71,Qnil);
    list_constant_73 = STATIC_CONS(Qwarning_message_level,list_constant_72);
    list_constant_74 = STATIC_CONS(Qtracing_message_level,list_constant_72);
    list_constant_75 = STATIC_CONS(Qbreakpoint_level,list_constant_72);
    list_constant_76 = STATIC_LIST((SI_Long)3L,list_constant_73,
	    list_constant_74,list_constant_75);
    list_constant_77 = STATIC_LIST((SI_Long)4L,Qab_or,
	    Qwarning_message_level,Qtracing_message_level,Qbreakpoint_level);
    list_constant_78 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_76,list_constant_77);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qtracing_and_breakpoints,
	    list_constant_78);
    Qtime_out_when_requesting_data_seeking = 
	    STATIC_SYMBOL("TIME-OUT-WHEN-REQUESTING-DATA-SEEKING",AB_package);
    list_constant_84 = STATIC_CONS(Qtime_out_when_requesting_data_seeking,
	    list_constant_57);
    Qmay_request_event_updates = STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    list_constant_85 = STATIC_CONS(Qmay_request_event_updates,
	    list_constant_70);
    Qmay_request_data_seeking = STATIC_SYMBOL("MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    list_constant_86 = STATIC_CONS(Qmay_request_data_seeking,list_constant_70);
    list_constant_90 = STATIC_LIST((SI_Long)8L,list_constant_79,
	    list_constant_80,list_constant_81,list_constant_82,
	    list_constant_83,list_constant_84,list_constant_85,
	    list_constant_86);
    list_constant_91 = STATIC_LIST_STAR((SI_Long)4L,list_constant_87,
	    list_constant_88,list_constant_89,list_constant_90);
    list_constant_92 = STATIC_LIST((SI_Long)2L,Qand,Qexpression);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_91,list_constant_92);
    list_constant_94 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_93);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qbackground_color,
	    list_constant_94);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    list_constant_98 = STATIC_CONS(Qborder_color,list_constant_67);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    list_constant_99 = STATIC_CONS(Qtext_color,list_constant_67);
    Qtext_alignment = STATIC_SYMBOL("TEXT-ALIGNMENT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    list_constant_95 = STATIC_LIST((SI_Long)4L,Qmember,Qleft,Qcenter,Qright);
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qtext_alignment,
	    list_constant_95);
    Qtext_size = STATIC_SYMBOL("TEXT-SIZE",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    list_constant_96 = STATIC_LIST((SI_Long)4L,Qmember,Qsmall,Qlarge,
	    Qextra_large);
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qtext_size,list_constant_96);
    list_constant_102 = STATIC_LIST((SI_Long)5L,list_constant_97,
	    list_constant_98,list_constant_99,list_constant_100,
	    list_constant_101);
    list_constant_103 = STATIC_LIST((SI_Long)6L,Qab_or,Qbackground_color,
	    Qborder_color,Qtext_color,Qtext_alignment,Qtext_size);
    list_constant_104 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_102,list_constant_103);
    list_constant_110 = STATIC_LIST((SI_Long)2L,Qcell_format,
	    list_constant_104);
    list_constant_105 = STATIC_CONS(list_constant_88,list_constant_90);
    list_constant_106 = STATIC_LIST((SI_Long)10L,Qab_or,Qpriority,
	    Qscan_interval,Qinitial_scan_wait_interval,Qvalue_domain,
	    Qupdate_only_when_shown,Qtracing_and_breakpoints,
	    Qtime_out_when_requesting_data_seeking,
	    Qmay_request_event_updates,Qmay_request_data_seeking);
    list_constant_107 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_105,list_constant_106);
    list_constant_111 = STATIC_LIST((SI_Long)2L,
	    Qcell_evaluation_attributes,list_constant_107);
    list_constant_112 = STATIC_LIST((SI_Long)5L,list_constant_87,
	    list_constant_108,list_constant_109,list_constant_110,
	    list_constant_111);
    list_constant_113 = STATIC_LIST((SI_Long)5L,Qab_or,Qexpression,
	    Qcell_display_value,Qcell_format,Qcell_evaluation_attributes);
    list_constant_115 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_112,list_constant_113);
    list_constant_116 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_114,
	    list_constant_115);
    list_constant_117 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_116,list_constant_117);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_118,list_constant_117);
    Qinitial_table_cells = STATIC_SYMBOL("INITIAL-TABLE-CELLS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_table_cells,
	    STATIC_FUNCTION(initial_table_cells,NIL,FALSE,1,1));
    Qget_table_cells = STATIC_SYMBOL("GET-TABLE-CELLS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_table_cells,STATIC_FUNCTION(get_table_cells,
	    NIL,FALSE,1,1));
    Qset_table_cells = STATIC_SYMBOL("SET-TABLE-CELLS",AB_package);
    SET_SYMBOL_FUNCTION(Qset_table_cells,STATIC_FUNCTION(set_table_cells,
	    NIL,FALSE,2,2));
    add_virtual_attribute(Qtable_cells,list_constant_119,list_constant_120,
	    Qnil,SYMBOL_FUNCTION(Qinitial_table_cells),
	    SYMBOL_FUNCTION(Qget_table_cells),
	    SYMBOL_FUNCTION(Qset_table_cells));
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qinitialize_for_new_table = STATIC_SYMBOL("INITIALIZE-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_new_table,
	    STATIC_FUNCTION(initialize_for_new_table,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_for_new_table);
    set_get(Qnew_table,Qinitialize,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qinitialize,temp_1,Qclasses_which_define);
    Qstandardize_text_size_feature_in_part_description = 
	    STATIC_SYMBOL("STANDARDIZE-TEXT-SIZE-FEATURE-IN-PART-DESCRIPTION",
	    AB_package);
    Qinitialize_after_reading_for_new_table = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_new_table,
	    STATIC_FUNCTION(initialize_after_reading_for_new_table,NIL,
	    FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_new_table);
    set_get(Qnew_table,Qinitialize_after_reading,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qinitialize_after_reading,temp_1,
	    Qclasses_which_define);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qcell,Qrow);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qcell,Qcolumn);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    string_constant_38 = STATIC_STRING("");
    list_constant_121 = STATIC_CONS(string_constant_38,Qnil);
    list_constant_122 = STATIC_LIST((SI_Long)13L,Qcell,Qbackground_color,
	    Qbackground,Qborder_color,Qforeground,Qtext_value,
	    list_constant_121,Qhighlighted_qm,Qnil,Qwidth,
	    FIX((SI_Long)70L),Qheight,FIX((SI_Long)25L));
    list_constant_123 = STATIC_CONS(list_constant_122,Qnil);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qcell,list_constant_123);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qsubpart_defaults,
	    list_constant_124);
    Qupdate_frame_status_and_notes_for_new_table = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_new_table,
	    STATIC_FUNCTION(update_frame_status_and_notes_for_new_table,
	    NIL,FALSE,1,1));
    Qupdate_frame_status_and_notes = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qupdate_frame_status_and_notes_for_new_table);
    set_get(Qnew_table,Qupdate_frame_status_and_notes,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_frame_status_and_notes),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qupdate_frame_status_and_notes,temp_1,
	    Qclasses_which_define);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qws_representation = STATIC_SYMBOL("WS-REPRESENTATION",AB_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qrow_index = STATIC_SYMBOL("ROW-INDEX",AB_package);
    Qcolumn_index = STATIC_SYMBOL("COLUMN-INDEX",AB_package);
    Qcell_attribute_name = STATIC_SYMBOL("CELL-ATTRIBUTE-NAME",AB_package);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    Qitem_change = STATIC_SYMBOL("ITEM-CHANGE",AB_package);
    Qexpression_cell_updated_for_new_table = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_new_table,
	    STATIC_FUNCTION(expression_cell_updated_for_new_table,NIL,
	    FALSE,5,5));
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_new_table);
    set_get(Qnew_table,Qexpression_cell_updated,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qexpression_cell_updated,temp_1,
	    Qclasses_which_define);
    if (Postpone_cell_erase_until_redraw_p == UNBOUND)
	Postpone_cell_erase_until_redraw_p = Nil;
    if (Background_color_value_from_postponed_erase == UNBOUND)
	Background_color_value_from_postponed_erase = Nil;
    if (Text_value_from_postponed_erase == UNBOUND)
	Text_value_from_postponed_erase = Nil;
    if (Reclaim_text_value_from_postponed_erase_p == UNBOUND)
	Reclaim_text_value_from_postponed_erase_p = Nil;
    if (Updated_only_qm == UNBOUND)
	Updated_only_qm = Nil;
    Qoff_window_color_map = STATIC_SYMBOL("OFF-WINDOW-COLOR-MAP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoff_window_color_map,Off_window_color_map);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_off_window_color_map = 
	    STATIC_SYMBOL("INITIALIZE-OFF-WINDOW-COLOR-MAP",AB_package);
    list_constant_125 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_off_window_color_map);
    record_system_variable(Qoff_window_color_map,Qnew_tables,
	    list_constant_125,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_off_window_color_map,
	    STATIC_FUNCTION(initialize_off_window_color_map,NIL,FALSE,0,0));
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qinvalidate_projection_mode = 
	    STATIC_SYMBOL("INVALIDATE-PROJECTION-MODE",AB_package);
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    Qcompute_path_of_focus_projection_mode = 
	    STATIC_SYMBOL("COMPUTE-PATH-OF-FOCUS-PROJECTION-MODE",AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    Qplace_reference_of_cell_for_new_table = 
	    STATIC_SYMBOL("PLACE-REFERENCE-OF-CELL-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qplace_reference_of_cell_for_new_table,
	    STATIC_FUNCTION(place_reference_of_cell_for_new_table,NIL,
	    FALSE,2,2));
    Qplace_reference_of_cell = STATIC_SYMBOL("PLACE-REFERENCE-OF-CELL",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qplace_reference_of_cell_for_new_table);
    set_get(Qnew_table,Qplace_reference_of_cell,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qplace_reference_of_cell),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qplace_reference_of_cell,temp_1,
	    Qclasses_which_define);
    list_constant_126 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_126,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING(" of ");
    Qdenote_cell_array_element_for_new_table = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_new_table,
	    STATIC_FUNCTION(denote_cell_array_element_for_new_table,NIL,
	    FALSE,3,3));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_new_table);
    set_get(Qnew_table,Qdenote_cell_array_element,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_1,
	    Qclasses_which_define);
    Qrecompile_expression_at_component_particulars_for_new_table = 
	    STATIC_SYMBOL("RECOMPILE-EXPRESSION-AT-COMPONENT-PARTICULARS-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrecompile_expression_at_component_particulars_for_new_table,
	    STATIC_FUNCTION(recompile_expression_at_component_particulars_for_new_table,
	    NIL,FALSE,2,2));
    Qrecompile_expression_at_component_particulars = 
	    STATIC_SYMBOL("RECOMPILE-EXPRESSION-AT-COMPONENT-PARTICULARS",
	    AB_package);
    temp_1 = 
	    SYMBOL_FUNCTION(Qrecompile_expression_at_component_particulars_for_new_table);
    set_get(Qnew_table,Qrecompile_expression_at_component_particulars,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qrecompile_expression_at_component_particulars),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qrecompile_expression_at_component_particulars,
	    temp_1,Qclasses_which_define);
    Qit = STATIC_SYMBOL("IT",AB_package);
    Qdraw_projection_mode = STATIC_SYMBOL("DRAW-PROJECTION-MODE",AB_package);
    Qdraw_for_new_table = STATIC_SYMBOL("DRAW-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_new_table,
	    STATIC_FUNCTION(draw_for_new_table,NIL,FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdraw_for_new_table);
    set_get(Qnew_table,Qdraw,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qdraw,temp_1,Qclasses_which_define);
    Qtracking_projection_mode = STATIC_SYMBOL("TRACKING-PROJECTION-MODE",
	    AB_package);
    Qg2_defstruct_structure_name_new_table_spot_g2_struct = 
	    STATIC_SYMBOL("NEW-TABLE-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnew_table_spot = STATIC_SYMBOL("NEW-TABLE-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_new_table_spot_g2_struct,
	    Qnew_table_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qnew_table_spot,
	    Qg2_defstruct_structure_name_new_table_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_new_table_spot == UNBOUND)
	The_type_description_of_new_table_spot = Nil;
    string_constant_39 = 
	    STATIC_STRING("43Dy8m837Ey1o837Ey83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_new_table_spot;
    The_type_description_of_new_table_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_39));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_new_table_spot_g2_struct,
	    The_type_description_of_new_table_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qnew_table_spot,
	    The_type_description_of_new_table_spot,Qtype_description_of_type);
    Qoutstanding_new_table_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-NEW-TABLE-SPOT-COUNT",AB_package);
    Qnew_table_spot_structure_memory_usage = 
	    STATIC_SYMBOL("NEW-TABLE-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_40 = STATIC_STRING("1q837Ey8s83-ggy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_new_table_spot_count);
    push_optimized_constant(Qnew_table_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_40));
    Qchain_of_available_new_table_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NEW-TABLE-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_new_table_spots,
	    Chain_of_available_new_table_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_new_table_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qnew_table_spot_count = STATIC_SYMBOL("NEW-TABLE-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_table_spot_count,New_table_spot_count);
    record_system_variable(Qnew_table_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_new_table_spots_vector == UNBOUND)
	Chain_of_available_new_table_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qnew_table_spot_structure_memory_usage,
	    STATIC_FUNCTION(new_table_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_new_table_spot_count,
	    STATIC_FUNCTION(outstanding_new_table_spot_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_new_table_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_new_table_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qnew_table_spot,
	    reclaim_structure_for_new_table_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnew_table_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qt),LIST_2(Qtype_of_frame_represented,
	    Qnew_table),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct = 
	    STATIC_SYMBOL("NEW-TABLE-CELL-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnew_table_cell_spot = STATIC_SYMBOL("NEW-TABLE-CELL-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct,
	    Qnew_table_cell_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qnew_table_cell_spot,
	    Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_new_table_cell_spot == UNBOUND)
	The_type_description_of_new_table_cell_spot = Nil;
    string_constant_41 = 
	    STATIC_STRING("43Dy8m83l1y1p83l1y837Ey83Qy8n8k1l837Ey0000001l1m8x837Eyktk0k0");
    temp = The_type_description_of_new_table_cell_spot;
    The_type_description_of_new_table_cell_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_41));
    mutate_global_property(Qg2_defstruct_structure_name_new_table_cell_spot_g2_struct,
	    The_type_description_of_new_table_cell_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qnew_table_cell_spot,
	    The_type_description_of_new_table_cell_spot,
	    Qtype_description_of_type);
    Qoutstanding_new_table_cell_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-NEW-TABLE-CELL-SPOT-COUNT",AB_package);
    Qnew_table_cell_spot_structure_memory_usage = 
	    STATIC_SYMBOL("NEW-TABLE-CELL-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_42 = STATIC_STRING("1q83l1y8s83-gfy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_new_table_cell_spot_count);
    push_optimized_constant(Qnew_table_cell_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_42));
    Qchain_of_available_new_table_cell_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NEW-TABLE-CELL-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_new_table_cell_spots,
	    Chain_of_available_new_table_cell_spots);
    record_system_variable(Qchain_of_available_new_table_cell_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qnew_table_cell_spot_count = STATIC_SYMBOL("NEW-TABLE-CELL-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_table_cell_spot_count,
	    New_table_cell_spot_count);
    record_system_variable(Qnew_table_cell_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_new_table_cell_spots_vector == UNBOUND)
	Chain_of_available_new_table_cell_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qnew_table_cell_spot_structure_memory_usage,
	    STATIC_FUNCTION(new_table_cell_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_new_table_cell_spot_count,
	    STATIC_FUNCTION(outstanding_new_table_cell_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_new_table_cell_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_new_table_cell_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qnew_table_cell_spot,
	    reclaim_structure_for_new_table_cell_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnew_table_cell_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qnew_table),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Qg2_defstruct_structure_name_new_table_background_spot_g2_struct = 
	    STATIC_SYMBOL("NEW-TABLE-BACKGROUND-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnew_table_background_spot = STATIC_SYMBOL("NEW-TABLE-BACKGROUND-SPOT",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_new_table_background_spot_g2_struct,
	    Qnew_table_background_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qnew_table_background_spot,
	    Qg2_defstruct_structure_name_new_table_background_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_new_table_background_spot == UNBOUND)
	The_type_description_of_new_table_background_spot = Nil;
    string_constant_43 = 
	    STATIC_STRING("43Dy8m83l0y1p83l0y837Ey83Qy8n8k1l837Ey0000001l1m8x837Eykqk0k0");
    temp = The_type_description_of_new_table_background_spot;
    The_type_description_of_new_table_background_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_43));
    mutate_global_property(Qg2_defstruct_structure_name_new_table_background_spot_g2_struct,
	    The_type_description_of_new_table_background_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qnew_table_background_spot,
	    The_type_description_of_new_table_background_spot,
	    Qtype_description_of_type);
    Qoutstanding_new_table_background_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-NEW-TABLE-BACKGROUND-SPOT-COUNT",
	    AB_package);
    Qnew_table_background_spot_structure_memory_usage = 
	    STATIC_SYMBOL("NEW-TABLE-BACKGROUND-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_44 = STATIC_STRING("1q83l0y8s83-gey09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_new_table_background_spot_count);
    push_optimized_constant(Qnew_table_background_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_44));
    Qchain_of_available_new_table_background_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NEW-TABLE-BACKGROUND-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_new_table_background_spots,
	    Chain_of_available_new_table_background_spots);
    record_system_variable(Qchain_of_available_new_table_background_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qnew_table_background_spot_count = 
	    STATIC_SYMBOL("NEW-TABLE-BACKGROUND-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_table_background_spot_count,
	    New_table_background_spot_count);
    record_system_variable(Qnew_table_background_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_new_table_background_spots_vector == UNBOUND)
	Chain_of_available_new_table_background_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qnew_table_background_spot_structure_memory_usage,
	    STATIC_FUNCTION(new_table_background_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_new_table_background_spot_count,
	    STATIC_FUNCTION(outstanding_new_table_background_spot_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_new_table_background_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_new_table_background_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qnew_table_background_spot,
	    reclaim_structure_for_new_table_background_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnew_table_background_spot),
	    Qtype_description_of_type);
    temp_1 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qnew_table),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_1;
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qgenerate_spot_for_new_table = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_new_table,
	    STATIC_FUNCTION(generate_spot_for_new_table,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_new_table);
    set_get(Qnew_table,Qgenerate_spot,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Qupdate_dependencies = STATIC_SYMBOL("UPDATE-DEPENDENCIES",AB_package);
    Qupdate_part_dependencies_for_new_table = 
	    STATIC_SYMBOL("UPDATE-PART-DEPENDENCIES-FOR-NEW-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_part_dependencies_for_new_table,
	    STATIC_FUNCTION(update_part_dependencies_for_new_table,NIL,
	    FALSE,3,3));
    Qupdate_part_dependencies = STATIC_SYMBOL("UPDATE-PART-DEPENDENCIES",
	    AB_package);
    temp_1 = SYMBOL_FUNCTION(Qupdate_part_dependencies_for_new_table);
    set_get(Qnew_table,Qupdate_part_dependencies,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_part_dependencies),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qupdate_part_dependencies,temp_1,
	    Qclasses_which_define);
    string_constant_45 = 
	    STATIC_STRING("PROJECTION-OF-NEW-TABLE-ACCUMULATING-SIZE");
    if (Projection_of_new_table_accumulating_size == UNBOUND)
	Projection_of_new_table_accumulating_size = make_recursive_lock(2,
		Kname,string_constant_45);
    Qprojection_of_new_table_accumulating_size = 
	    STATIC_SYMBOL("PROJECTION-OF-NEW-TABLE-ACCUMULATING-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojection_of_new_table_accumulating_size,
	    Projection_of_new_table_accumulating_size);
    Qprojection_update_dependencies = 
	    STATIC_SYMBOL("PROJECTION-UPDATE-DEPENDENCIES",AB_package);
    list_constant_127 = STATIC_CONS(Qprojection_update_dependencies,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojection_of_new_table_accumulating_size,
	    Qnew_tables,Nil,Qnil,Qnil,list_constant_127,Nil);
    mutate_global_property(Qprojection_of_new_table_accumulating_size,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qsize = STATIC_SYMBOL("SIZE",AB_package);
    Qactivate_for_new_table = STATIC_SYMBOL("ACTIVATE-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_new_table,
	    STATIC_FUNCTION(activate_for_new_table,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qactivate_for_new_table);
    set_get(Qnew_table,Qactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qactivate,temp_1,Qclasses_which_define);
    Qdeactivate_for_new_table = STATIC_SYMBOL("DEACTIVATE-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_new_table,
	    STATIC_FUNCTION(deactivate_for_new_table,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_new_table);
    set_get(Qnew_table,Qdeactivate,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qnew_table,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qdynamic_text_cell_format = STATIC_SYMBOL("DYNAMIC-TEXT-CELL-FORMAT",
	    AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    Qpart_description_of_frame = STATIC_SYMBOL("PART-DESCRIPTION-OF-FRAME",
	    AB_package);
    Qget_subpart_of_collection = STATIC_SYMBOL("GET-SUBPART-OF-COLLECTION",
	    AB_package);
    list_constant_129 = STATIC_LIST((SI_Long)2L,Qquote,Qsubparts);
    list_constant_128 = STATIC_CONS(Qrow,Qnil);
    list_constant_130 = STATIC_CONS(Qquote,list_constant_128);
    list_constant_131 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)5L,
	    Qget_subpart_of_collection,Qit,list_constant_129,
	    list_constant_130,list_constant_131);
    Qfuncall_on_focus_projection_mode = 
	    STATIC_SYMBOL("FUNCALL-ON-FOCUS-PROJECTION-MODE",AB_package);
    Qenter_focus = STATIC_SYMBOL("ENTER-FOCUS",AB_package);
    Qdenote_projection_mode = STATIC_SYMBOL("DENOTE-PROJECTION-MODE",
	    AB_package);
    Qcleanup_projection_mode = STATIC_SYMBOL("CLEANUP-PROJECTION-MODE",
	    AB_package);
    list_constant_132 = STATIC_CONS(Qquote,list_constant_7);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)5L,
	    Qget_subpart_of_collection,Qit,list_constant_129,
	    list_constant_132,list_constant_131);
    string_constant_9 = 
	    STATIC_STRING("the value of the cell in column ~D of row ~D");
    Qget_simple_part_feature = STATIC_SYMBOL("GET-SIMPLE-PART-FEATURE",
	    AB_package);
    list_constant_133 = STATIC_CONS(Qcell_contents,Qnil);
    list_constant_134 = STATIC_CONS(Qquote,list_constant_133);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qget_simple_part_feature,
	    Qit,list_constant_134);
    list_constant_135 = STATIC_LIST((SI_Long)2L,Qquote,Qbackground_color);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qget_simple_part_feature,
	    Qit,list_constant_135);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qcell,Qannotation);
    Qtext_cell_line_color_qm = STATIC_SYMBOL("TEXT-CELL-LINE-COLOR\?",
	    AB_package);
    Qtext_cell_background_color_qm = 
	    STATIC_SYMBOL("TEXT-CELL-BACKGROUND-COLOR\?",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Kno_bleeding = STATIC_SYMBOL("NO-BLEEDING",Pkeyword);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_10 = STATIC_STRING("~A");
    array_constant_1 = STATIC_ARRAY(list_constant_126,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qedit_cell_expression = STATIC_SYMBOL("EDIT-CELL-EXPRESSION",AB_package);
    Qedit_cell_format = STATIC_SYMBOL("EDIT-CELL-FORMAT",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)4L,Qedit_cell_expression,
	    Qcell_contents,Qedit_cell_format,Qt);
    list_constant_15 = STATIC_LIST((SI_Long)4L,Qedit_cell_expression,
	    Qcell_expression_and_text,Qedit_cell_format,Qcell_format);
    string_constant_46 = 
	    STATIC_STRING("PROJECTING-TO-COLLECT-DESCRIPTION-FOR-NEW-TABLE");
    if (Projecting_to_collect_description_for_new_table == UNBOUND)
	Projecting_to_collect_description_for_new_table = 
		make_recursive_lock(2,Kname,string_constant_46);
    Qprojecting_to_collect_description_for_new_table = 
	    STATIC_SYMBOL("PROJECTING-TO-COLLECT-DESCRIPTION-FOR-NEW-TABLE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprojecting_to_collect_description_for_new_table,
	    Projecting_to_collect_description_for_new_table);
    Qprojection_funcall_on_focus = 
	    STATIC_SYMBOL("PROJECTION-FUNCALL-ON-FOCUS",AB_package);
    list_constant_136 = STATIC_CONS(Qprojection_funcall_on_focus,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qprojecting_to_collect_description_for_new_table,
	    Qnew_tables,Nil,Qnil,Qnil,list_constant_136,Nil);
    mutate_global_property(Qprojecting_to_collect_description_for_new_table,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qdescribe_new_table_from_inside_projection = 
	    STATIC_SYMBOL("DESCRIBE-NEW-TABLE-FROM-INSIDE-PROJECTION",
	    AB_package);
    string_constant_11 = 
	    STATIC_STRING("The formating attributes for a simple cell in the table are:");
    Qcomputation_style_description = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-DESCRIPTION",AB_package);
    string_constant_12 = 
	    STATIC_STRING("The evaluation attributes for a simple expression in the table are:");
    SET_SYMBOL_FUNCTION(Qdescribe_new_table_from_inside_projection,
	    STATIC_FUNCTION(describe_new_table_from_inside_projection,NIL,
	    FALSE,1,1));
}
