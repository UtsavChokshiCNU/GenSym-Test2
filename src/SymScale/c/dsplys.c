/* dsplys.c
 * Input file:  displays.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "dsplys.h"


/* PUT-PARENT-METER-FOR-MARKER-WHERE-SLOT-IS-ABSENT */
Object put_parent_meter_for_marker_where_slot_is_absent(marker_for_meter,
	    slot_value)
    Object marker_for_meter, slot_value;
{
    x_note_fn_call(171,0);
    return VALUES_1(Nil);
}

/* PUT-PARENT-METER-FOR-RULING-WHERE-SLOT-IS-ABSENT */
Object put_parent_meter_for_ruling_where_slot_is_absent(ruling_for_meter,
	    slot_value)
    Object ruling_for_meter, slot_value;
{
    x_note_fn_call(171,1);
    return VALUES_1(Nil);
}

/* PUT-PARENT-DIAL-FOR-POINTER-WHERE-SLOT-IS-ABSENT */
Object put_parent_dial_for_pointer_where_slot_is_absent(pointer_for_dial,
	    slot_value)
    Object pointer_for_dial, slot_value;
{
    x_note_fn_call(171,2);
    return VALUES_1(Nil);
}

/* PUT-PARENT-DIAL-FOR-RULING-WHERE-SLOT-IS-ABSENT */
Object put_parent_dial_for_ruling_where_slot_is_absent(ruling_for_dial,
	    slot_value)
    Object ruling_for_dial, slot_value;
{
    x_note_fn_call(171,3);
    return VALUES_1(Nil);
}

static Object Qcell_array;         /* cell-array */

/* GET-CACHED-VALUE-FOR-CELL-BASED-DISPLAY */
Object get_cached_value_for_cell_based_display(display_frame)
    Object display_frame;
{
    Object cell_array_qm;

    x_note_fn_call(171,4);
    cell_array_qm = get_lookup_slot_value_given_default(display_frame,
	    Qcell_array,Nil);
    if (cell_array_qm)
	return VALUES_1(ISVREF(FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,
		(SI_Long)3L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),(SI_Long)0L + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		(SI_Long)2L),(SI_Long)0L),(SI_Long)6L));
    else
	return VALUES_1(Nil);
}

static Object Qlow_value_for_dial_ruling;  /* low-value-for-dial-ruling */

/* RECLAIM-LOW-VALUE-FOR-DIAL-RULING-VALUE */
Object reclaim_low_value_for_dial_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,5);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)31L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qlow_value_for_dial_ruling);
    SVREF(frame,FIX((SI_Long)31L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-DIAL-RULING-VALUE */
Object reclaim_high_value_for_dial_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,6);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)32L));
    ISVREF(frame,(SI_Long)32L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qincrement_per_dial_ruling;  /* increment-per-dial-ruling */

/* RECLAIM-INCREMENT-PER-DIAL-RULING-VALUE */
Object reclaim_increment_per_dial_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,7);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)33L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qincrement_per_dial_ruling);
    SVREF(frame,FIX((SI_Long)33L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-LOW-VALUE-FOR-DIAL-RULING-VALUE */
Object reclaim_desired_low_value_for_dial_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,8);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)34L));
    ISVREF(frame,(SI_Long)34L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-HIGH-VALUE-FOR-DIAL-RULING-VALUE */
Object reclaim_desired_high_value_for_dial_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,9);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)35L));
    ISVREF(frame,(SI_Long)35L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qpointer_for_dial;   /* pointer-for-dial */

/* INITIALIZE-FOR-POINTER-FOR-DIAL */
Object initialize_for_pointer_for_dial(pointer_for_dial)
    Object pointer_for_dial;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(171,10);
    frame = pointer_for_dial;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qpointer_for_dial)) {
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
    svref_new_value = IFIX(ISVREF(pointer_for_dial,(SI_Long)5L)) | 
	    (SI_Long)1024L;
    return VALUES_1(ISVREF(pointer_for_dial,(SI_Long)5L) = 
	    FIX(svref_new_value));
}

static Object Qdial;               /* dial */

/* INITIALIZE-AFTER-READING-FOR-DIAL */
Object initialize_after_reading_for_dial(dial)
    Object dial;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,11);
    frame = dial;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qdial)) {
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
    make_or_reformat_ruling_for_dial(get_ruling_for_dial(dial),dial);
    return eliminate_extra_rulings_for_dial(dial);
}

/* INITIALIZE-AFTER-READING-FOR-POINTER-FOR-DIAL */
Object initialize_after_reading_for_pointer_for_dial(pointer_for_dial)
    Object pointer_for_dial;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(171,12);
    frame = pointer_for_dial;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qpointer_for_dial)) {
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
    svref_new_value = IFIX(ISVREF(pointer_for_dial,(SI_Long)5L)) | 
	    (SI_Long)1024L;
    return VALUES_1(ISVREF(pointer_for_dial,(SI_Long)5L) = 
	    FIX(svref_new_value));
}

/* RECLAIM-RULING-LOW-VALUE-ANGLE-IN-RADIANS-VALUE */
Object reclaim_ruling_low_value_angle_in_radians_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,13);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)16L));
    ISVREF(frame,(SI_Long)16L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-RULING-HIGH-VALUE-ANGLE-IN-RADIANS-VALUE */
Object reclaim_ruling_high_value_angle_in_radians_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,14);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)17L));
    ISVREF(frame,(SI_Long)17L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-ANGLE-BETWEEN-MARKINGS-IN-RADIANS-VALUE */
Object reclaim_angle_between_markings_in_radians_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,15);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)18L));
    ISVREF(frame,(SI_Long)18L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-POINTER-POSITION-IN-RADIANS?-VALUE */
Object reclaim_pointer_position_in_radians_qm_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,16);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)16L));
    ISVREF(frame,(SI_Long)16L) = svref_new_value;
    return VALUES_1(Nil);
}

/* MAKE-DIAL */
Object make_dial(dial_type)
    Object dial_type;
{
    Object new_dial;

    x_note_fn_call(171,17);
    new_dial = make_entity(1,dial_type);
    make_or_reformat_ruling_for_dial(Nil,new_dial);
    return VALUES_1(new_dial);
}

/* GENERATE-SPOT-FOR-DIAL */
Object generate_spot_for_dial(dial,mouse_pointer)
    Object dial, mouse_pointer;
{
    x_note_fn_call(171,18);
    return push_last_spot(mouse_pointer,make_dial_spot_1(),dial);
}

/* GENERATE-SPOT-FOR-POINTER-FOR-DIAL */
Object generate_spot_for_pointer_for_dial(pointer_for_dial,mouse_pointer)
    Object pointer_for_dial, mouse_pointer;
{
    x_note_fn_call(171,19);
    return generate_spot_for_aggregate(pointer_for_dial,mouse_pointer);
}

/* GENERATE-SPOT-FOR-RULING-FOR-DIAL */
Object generate_spot_for_ruling_for_dial(ruling_for_dial,mouse_pointer)
    Object ruling_for_dial, mouse_pointer;
{
    x_note_fn_call(171,20);
    return generate_spot_for_aggregate(ruling_for_dial,mouse_pointer);
}

static Object Qruling_for_meter;   /* ruling-for-meter */

static Object Qg2_icon_background;  /* g2-icon-background */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

static Object Qdial_marking_label;  /* dial-marking-label */

/* DRAW-FOR-DIAL-MARKING-LABEL */
Object draw_for_dial_marking_label(dial_marking_label)
    Object dial_marking_label;
{
    Object gensymed_symbol, frame, symbol, sub_class_bit_vector;
    Object color_or_metacolor, color_value, old_color_value;
    Object current_background_color_value, frame_1, sub_vector_qm;
    Object method_function_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, index_1;
    SI_Long ab_loop_bind_;
    char temp;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(171,21);
    SAVE_STACK();
    if ( !((SI_Long)0L != (IFIX(ISVREF(dial_marking_label,(SI_Long)5L)) & 
	    (SI_Long)2048L))) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(dial_marking_label,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	frame = gensymed_symbol;
	symbol = Qruling_for_meter;
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
	    gensymed_symbol = ACCESS_ONCE(ISVREF(dial_marking_label,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(gensymed_symbol,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    color_or_metacolor = item_color(gensymed_symbol,
		    Qg2_icon_background);
	    if (EQ(color_or_metacolor,Qbackground))
		color_value = Current_background_color_value;
	    else if (EQ(color_or_metacolor,Qforeground) || 
		    EQ(color_or_metacolor,Qworkspace_foreground))
		color_value = Current_foreground_color_value;
	    else if (EQ(color_or_metacolor,Qtransparent))
		color_value = Current_background_color_value;
	    else
		color_value = map_to_color_value(color_or_metacolor);
	    old_color_value = Current_background_color_value;
	    current_background_color_value = Current_background_color_value;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		    0);
	      set_current_background_color_value(color_value);
	      frame_1 = dial_marking_label;
	      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		      (SI_Long)11L),(SI_Long)5L);
	      index_1 = (SI_Long)0L;
	      ab_loop_bind_ = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		      (SI_Long)3L;
	    next_loop:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop;
	      if (EQ(ISVREF(sub_vector_qm,index_1),Qdial_marking_label)) {
		  method_function_qm = ISVREF(sub_vector_qm,index_1 + 
			  (SI_Long)3L);
		  goto end_1;
	      }
	      index_1 = index_1 + (SI_Long)2L;
	      goto next_loop;
	    end_loop:
	      method_function_qm = Qnil;
	    end_1:;
	      if (method_function_qm)
		  SAVE_VALUES(inline_funcall_1(method_function_qm,frame_1));
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	      set_current_background_color_value(old_color_value);
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    frame_1 = dial_marking_label;
	    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		    (SI_Long)11L),(SI_Long)5L);
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) 
		    - (SI_Long)3L;
	  next_loop_1:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_1;
	    if (EQ(ISVREF(sub_vector_qm,index_1),Qdial_marking_label)) {
		method_function_qm = ISVREF(sub_vector_qm,index_1 + 
			(SI_Long)3L);
		goto end_2;
	    }
	    index_1 = index_1 + (SI_Long)2L;
	    goto next_loop_1;
	  end_loop_1:
	    method_function_qm = Qnil;
	  end_2:;
	    if (method_function_qm) {
		result = inline_funcall_1(method_function_qm,frame_1);
		RESTORE_STACK();
		return result;
	    }
	    else {
		RESTORE_STACK();
		return VALUES_1(Nil);
	    }
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qmarking_label_format;  /* marking-label-format */

/* MAKE-MARKING-LABEL */
Object make_marking_label(number,left_field_size,right_field_size)
    Object number, left_field_size, right_field_size;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(171,22);
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
	      write_floating_point_number(5,number,left_field_size,
		      right_field_size,FIX((SI_Long)6L),T);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return make_free_text_box(3,temp,Qdial_marking_label,
	    Qmarking_label_format);
}

/* GENERATE-SPOT-FOR-DIAL-MARKING-LABEL */
Object generate_spot_for_dial_marking_label(dial_marking_label,mouse_pointer)
    Object dial_marking_label, mouse_pointer;
{
    x_note_fn_call(171,23);
    return generate_spot_for_aggregate(dial_marking_label,mouse_pointer);
}

static Object Qruling_for_dial;    /* ruling-for-dial */

static Object float_constant;      /* 3.141592653589793 */

/* MAKE-OR-REFORMAT-RULING-FOR-DIAL */
Object make_or_reformat_ruling_for_dial(ruling_for_dial_qm,dial)
    Object ruling_for_dial_qm, dial;
{
    Object ruling_for_dial, short_pi, ruling_low_value_angle_in_radians;
    Object ruling_high_value_angle_in_radians, managed_number_or_value;
    Object low_value_for_dial_ruling, high_value_for_dial_ruling;
    Object increment_per_dial_ruling, number_of_marks_for_dial;
    Object distance_from_mark_to_label_center, dial_radius;
    Object length_of_ruling_markers, gensymed_symbol, x_center_of_dial;
    Object y_center_of_dial, temp_1, temp_2, temp_3;
    Object store_managed_number_or_value_arg, svref_new_value, low, high;
    Object increment, ab_queue_form_, ab_next_queue_element_;
    Object dial_marking_label, mark_angle, label_x_center, label_y_center;
    Object label_value, new_dial_marking_label, gensymed_symbol_1;
    Object gensymed_symbol_3;
    SI_Long mark_number, ab_loop_bind_, gensymed_symbol_2, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, gensymed_symbol_6;
    double temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,24);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	ruling_for_dial = ruling_for_dial_qm;
	if (ruling_for_dial);
	else
	    ruling_for_dial = make_frame(Qruling_for_dial);
	short_pi = float_constant;
	temp = DOUBLE_FLOAT_TO_DOUBLE(short_pi);
	ruling_low_value_angle_in_radians = ltimes(ISVREF(dial,
		(SI_Long)23L),DOUBLE_TO_DOUBLE_FLOAT(temp / 180.0));
	temp = DOUBLE_FLOAT_TO_DOUBLE(short_pi);
	ruling_high_value_angle_in_radians = ltimes(ISVREF(dial,
		(SI_Long)24L),DOUBLE_TO_DOUBLE_FLOAT(temp / 180.0));
	managed_number_or_value = ISVREF(dial,(SI_Long)31L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_dial_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_dial_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    low_value_for_dial_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    low_value_for_dial_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(dial,(SI_Long)32L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_dial_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_dial_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    high_value_for_dial_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    high_value_for_dial_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(dial,(SI_Long)33L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    increment_per_dial_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    increment_per_dial_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    increment_per_dial_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    increment_per_dial_ruling = managed_number_or_value;
	number_of_marks_for_dial = ISVREF(dial,(SI_Long)25L);
	distance_from_mark_to_label_center = ISVREF(dial,(SI_Long)38L);
	dial_radius = ISVREF(dial,(SI_Long)26L);
	length_of_ruling_markers = ISVREF(dial,(SI_Long)30L);
	gensymed_symbol = ISVREF(ruling_for_dial,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	x_center_of_dial = add(gensymed_symbol,ISVREF(dial,(SI_Long)27L));
	gensymed_symbol = ISVREF(ruling_for_dial,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	y_center_of_dial = add(gensymed_symbol,ISVREF(dial,(SI_Long)28L));
	if ( !TRUEP(ruling_for_dial_qm)) {
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_2 = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_3 = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    set_edges_of_block(ruling_for_dial,temp_1,temp_2,temp_3,
		    gensymed_symbol);
	    add_subblock(ruling_for_dial,dial);
	}
	store_managed_number_or_value_arg = ruling_low_value_angle_in_radians;
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(ruling_for_dial,
		(SI_Long)16L),store_managed_number_or_value_arg);
	ISVREF(ruling_for_dial,(SI_Long)16L) = svref_new_value;
	store_managed_number_or_value_arg = ruling_high_value_angle_in_radians;
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(ruling_for_dial,
		(SI_Long)17L),store_managed_number_or_value_arg);
	ISVREF(ruling_for_dial,(SI_Long)17L) = svref_new_value;
	store_managed_number_or_value_arg = 
		divide(minus(ruling_low_value_angle_in_radians,
		ruling_high_value_angle_in_radians),sub1(ISVREF(dial,
		(SI_Long)25L)));
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(ruling_for_dial,
		(SI_Long)18L),store_managed_number_or_value_arg);
	ISVREF(ruling_for_dial,(SI_Long)18L) = svref_new_value;
	if (low_value_for_dial_ruling && increment_per_dial_ruling) {
	    store_managed_number_or_value_arg = 
		    add(low_value_for_dial_ruling,
		    ltimes(increment_per_dial_ruling,
		    sub1(number_of_marks_for_dial)));
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(dial,
		    (SI_Long)32L),store_managed_number_or_value_arg);
	    ISVREF(dial,(SI_Long)32L) = svref_new_value;
	}
	else if (low_value_for_dial_ruling && high_value_for_dial_ruling) {
	    store_managed_number_or_value_arg = 
		    divide(minus(high_value_for_dial_ruling,
		    low_value_for_dial_ruling),sub1(number_of_marks_for_dial));
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(dial,
		    (SI_Long)33L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(dial,Qincrement_per_dial_ruling);
	    SVREF(dial,FIX((SI_Long)33L)) = svref_new_value;
	}
	else {
	    temp_1 = SYMBOL_FUNCTION(ISVREF(dial,(SI_Long)36L));
	    managed_number_or_value = ISVREF(dial,(SI_Long)34L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_2 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp_2 = copy_text_string(managed_number_or_value);
	    else
		temp_2 = managed_number_or_value;
	    managed_number_or_value = ISVREF(dial,(SI_Long)35L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_3 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_3 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp_3 = copy_text_string(managed_number_or_value);
	    else
		temp_3 = managed_number_or_value;
	    result = FUNCALL_3(temp_1,temp_2,temp_3,number_of_marks_for_dial);
	    MVS_3(result,low,high,increment);
	    store_managed_number_or_value_arg = low;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(dial,
		    (SI_Long)31L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(dial,Qlow_value_for_dial_ruling);
	    SVREF(dial,FIX((SI_Long)31L)) = svref_new_value;
	    store_managed_number_or_value_arg = high;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(dial,
		    (SI_Long)32L),store_managed_number_or_value_arg);
	    ISVREF(dial,(SI_Long)32L) = svref_new_value;
	    store_managed_number_or_value_arg = increment;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(dial,
		    (SI_Long)33L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(dial,Qincrement_per_dial_ruling);
	    SVREF(dial,FIX((SI_Long)33L)) = svref_new_value;
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(ruling_for_dial,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	dial_marking_label = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	dial_marking_label = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	remove_as_subblock_if_necessary(1,dial_marking_label);
	delete_frame(dial_marking_label);
	goto next_loop;
      end_loop:;
	mark_number = (SI_Long)0L;
	ab_loop_bind_ = IFIX(sub1(number_of_marks_for_dial));
	mark_angle = Nil;
	label_x_center = Nil;
	label_y_center = Nil;
	label_value = Nil;
	new_dial_marking_label = Nil;
      next_loop_1:
	if (mark_number > ab_loop_bind_)
	    goto end_loop_1;
	temp_1 = FIX(mark_number);
	managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)18L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_2 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp_2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp_2 = copy_text_string(managed_number_or_value);
	else
	    temp_2 = managed_number_or_value;
	mark_angle = minus(ruling_low_value_angle_in_radians,ltimes(temp_1,
		temp_2));
	label_x_center = l_round(add(ltimes(minusn(3,dial_radius,
		length_of_ruling_markers,
		distance_from_mark_to_label_center),lcos(mark_angle)),
		x_center_of_dial),_);
	label_y_center = l_round(minus(y_center_of_dial,ltimes(minusn(3,
		dial_radius,length_of_ruling_markers,
		distance_from_mark_to_label_center),lsin(mark_angle))),_);
	label_value = add(low_value_for_dial_ruling,
		ltimes(FIX(mark_number),increment_per_dial_ruling));
	new_dial_marking_label = make_marking_label(label_value,
		FIX((SI_Long)3L),FIX((SI_Long)2L));
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(new_dial_marking_label,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	gensymed_symbol_1 = new_dial_marking_label;
	gensymed_symbol_2 = IFIX(label_x_center);
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_3);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_4;
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_3);
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_3);
	gensymed_symbol_4 = IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT( - 
		((double)(gensymed_symbol_4 - gensymed_symbol_5) / 2.0)),_));
	gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_4;
	gensymed_symbol_4 = IFIX(label_y_center);
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_3);
	gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_3);
	gensymed_symbol_3 = ISVREF(new_dial_marking_label,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_6 = IFIX(gensymed_symbol_3);
	gensymed_symbol_5 = IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT( - 
		((double)(gensymed_symbol_5 - gensymed_symbol_6) / 2.0)),_));
	gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2),FIX(gensymed_symbol_4));
	add_subblock(new_dial_marking_label,ruling_for_dial);
	mark_number = mark_number + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	result = VALUES_1(ruling_for_dial);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object float_constant_1;    /* 0.0 */

/* DETERMINE-STANDARD-DIAL-RULING */
Object determine_standard_dial_ruling(desired_low_value,desired_high_value,
	    number_of_markings)
    Object desired_low_value, desired_high_value, number_of_markings;
{
    Object desired_increment_per_ruling;

    x_note_fn_call(171,25);
    desired_increment_per_ruling = divide(lfloat(minus(desired_high_value,
	    desired_low_value),float_constant_1),number_of_markings);
    return VALUES_1(desired_increment_per_ruling);
}

/* GET-POINTER-FOR-DIAL-IF-ANY */
Object get_pointer_for_dial_if_any(dial)
    Object dial;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(171,26);
    gensymed_symbol = ACCESS_ONCE(ISVREF(dial,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Pointer_for_dial_class_description,(SI_Long)18L));
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
    if (temp)
	return VALUES_1(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-RULING-FOR-DIAL */
Object get_ruling_for_dial(dial)
    Object dial;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(171,27);
    gensymed_symbol = ACCESS_ONCE(ISVREF(dial,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Ruling_for_dial_class_description,(SI_Long)18L));
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
    if (temp)
	return VALUES_1(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_update_simulated_value_qm, Qdo_not_update_simulated_value_qm);

/* EXPRESSION-CELL-UPDATED-FOR-DIAL */
Object expression_cell_updated_for_dial(dial,g2_cell_array,index_1,
	    old_cache_qm,new_cache_qm)
    Object dial, g2_cell_array, index_1, old_cache_qm, new_cache_qm;
{
    x_note_fn_call(171,28);
    return update_cell_based_display_for_dial(dial,old_cache_qm,
	    new_cache_qm,Nil);
}

/* UPDATE-DISPLAY-FOR-DIAL */
Object update_display_for_dial(dial,update_even_if_value_unchanged_qm,
	    wake_up_qm,update_even_if_not_showing_qm)
    Object dial, update_even_if_value_unchanged_qm, wake_up_qm;
    Object update_even_if_not_showing_qm;
{
    Object cached_value_qm;

    x_note_fn_call(171,29);
    cached_value_qm = get_cached_value_for_cell_based_display(dial);
    return update_cell_based_display_for_dial(dial,cached_value_qm,
	    cached_value_qm,update_even_if_value_unchanged_qm);
}

static Object Qobsolete_datum;     /* obsolete-datum */

static Object Qvalue_to_display;   /* value-to-display */

static Object Qvirtual_attribute;  /* virtual-attribute */

/* UPDATE-CELL-BASED-DISPLAY-FOR-DIAL */
Object update_cell_based_display_for_dial(dial,old_cache_qm,new_cache_qm,
	    update_even_if_value_unchanged_qm)
    Object dial, old_cache_qm, new_cache_qm, update_even_if_value_unchanged_qm;
{
    Object dial_pointer_qm, new_display_value_qm, old_display_value_qm;
    Object new_dial_pointer_qm, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,30);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	dial_pointer_qm = get_pointer_for_dial_if_any(dial);
	new_display_value_qm = CONSP(new_cache_qm) && 
		EQ(M_CDR(new_cache_qm),Qobsolete_datum) ? 
		M_CAR(new_cache_qm) : new_cache_qm;
	old_display_value_qm = CONSP(old_cache_qm) && 
		EQ(M_CDR(old_cache_qm),Qobsolete_datum) ? 
		M_CAR(old_cache_qm) : old_cache_qm;
	if (new_display_value_qm) {
	    if ( !( !TRUEP(update_even_if_value_unchanged_qm) && 
		    dial_pointer_qm && old_display_value_qm && 
		    evaluation_value_eql(2,new_display_value_qm,
		    old_display_value_qm))) {
		if (dial_pointer_qm)
		    update_images_of_block(dial_pointer_qm,T,T);
		make_or_reformat_pointer_for_dial(dial_pointer_qm,dial,
			evaluation_value_value(new_display_value_qm));
		new_dial_pointer_qm = dial_pointer_qm;
		if (new_dial_pointer_qm);
		else
		    new_dial_pointer_qm = get_pointer_for_dial_if_any(dial);
		if (new_dial_pointer_qm)
		    update_images_of_block(new_dial_pointer_qm,Nil,T);
		result = send_ws_representations_item_virtual_attribute_change(dial,
			get_property_value_function(3,
			get_symbol_properties_function(Qvalue_to_display),
			Qvirtual_attribute,Nil),Nil);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(dial,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)21L),(SI_Long)1L);
	    gensymed_symbol_1 = dial;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    result = send_ws_representations_item_virtual_attribute_change(dial,
		    get_property_value_function(3,
		    get_symbol_properties_function(Qvalue_to_display),
		    Qvirtual_attribute,Nil),Nil);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* INITIALIZE-FOR-DIAL */
Object initialize_for_dial(dial)
    Object dial;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,31);
    frame = dial;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qdial)) {
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

/* ELIMINATE-EXTRA-RULINGS-FOR-DIAL */
Object eliminate_extra_rulings_for_dial(dial)
    Object dial;
{
    Object ruling_seen_p, gensymed_symbol, constant_queue, head, queue_element;
    Object next_queue_element, subblock, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(171,32);
    ruling_seen_p = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(dial,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    constant_queue = gensymed_symbol;
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = constant_queue_next(head,constant_queue);
    next_queue_element = Nil;
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    next_queue_element = constant_queue_next(queue_element,constant_queue);
    subblock = ISVREF(queue_element,(SI_Long)4L);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Ruling_for_dial_class_description,(SI_Long)18L));
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
	if (ruling_seen_p) {
	    constant_queue_delete(2,queue_element,constant_queue);
	    delete_frame(subblock);
	}
	else
	    ruling_seen_p = T;
    }
    queue_element = next_queue_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object string_constant;     /* "Attempting to display non-numeric values on a dial." */

/* MAKE-OR-REFORMAT-POINTER-FOR-DIAL */
Object make_or_reformat_pointer_for_dial(pointer_for_dial_qm,dial,
	    new_data_value_for_pointer)
    Object pointer_for_dial_qm, dial, new_data_value_for_pointer;
{
    Object managed_number_or_value, high_value_for_dial_ruling;
    Object ruling_for_dial_qm, ruling_for_dial, the_ruling_for_dial;
    Object pointer_for_dial, low_value_for_dial_ruling;
    Object ruling_low_value_angle_in_radians;
    Object ruling_high_value_angle_in_radians, gensymed_symbol, temp, temp_1;
    Object temp_2, svref_new_value, store_managed_number_or_value_arg;

    x_note_fn_call(171,33);
    if ( !TRUEP(new_data_value_for_pointer) || 
	    FIXNUMP(new_data_value_for_pointer) || 
	    FLOATP(new_data_value_for_pointer)) {
	managed_number_or_value = ISVREF(dial,(SI_Long)32L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_dial_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_dial_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    high_value_for_dial_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    high_value_for_dial_ruling = managed_number_or_value;
	ruling_for_dial_qm = get_ruling_for_dial(dial);
	if ( !TRUEP(ruling_for_dial_qm))
	    ruling_for_dial = make_or_reformat_ruling_for_dial(Nil,dial);
	else if ( !TRUEP(high_value_for_dial_ruling)) {
	    the_ruling_for_dial = 
		    make_or_reformat_ruling_for_dial(ruling_for_dial_qm,dial);
	    managed_number_or_value = ISVREF(dial,(SI_Long)32L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		high_value_for_dial_ruling = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		high_value_for_dial_ruling = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		high_value_for_dial_ruling = 
			copy_text_string(managed_number_or_value);
	    else
		high_value_for_dial_ruling = managed_number_or_value;
	    ruling_for_dial = the_ruling_for_dial;
	}
	else
	    ruling_for_dial = ruling_for_dial_qm;
	pointer_for_dial = pointer_for_dial_qm;
	if (pointer_for_dial);
	else
	    pointer_for_dial = make_frame(Qpointer_for_dial);
	managed_number_or_value = ISVREF(dial,(SI_Long)31L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_dial_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_dial_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    low_value_for_dial_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    low_value_for_dial_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)16L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    ruling_low_value_angle_in_radians = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    ruling_low_value_angle_in_radians = 
		    aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    ruling_low_value_angle_in_radians = 
		    copy_text_string(managed_number_or_value);
	else
	    ruling_low_value_angle_in_radians = managed_number_or_value;
	managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)17L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    ruling_high_value_angle_in_radians = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    ruling_high_value_angle_in_radians = 
		    aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    ruling_high_value_angle_in_radians = 
		    copy_text_string(managed_number_or_value);
	else
	    ruling_high_value_angle_in_radians = managed_number_or_value;
	if ( !TRUEP(pointer_for_dial_qm)) {
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_2 = gensymed_symbol;
	    gensymed_symbol = ISVREF(dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    set_edges_of_block(pointer_for_dial,temp,temp_1,temp_2,
		    gensymed_symbol);
	    add_subblock(pointer_for_dial,dial);
	}
	if ( !TRUEP(new_data_value_for_pointer)) {
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(pointer_for_dial,
		    (SI_Long)16L),Nil);
	    ISVREF(pointer_for_dial,(SI_Long)16L) = svref_new_value;
	}
	else if (NUM_LE(new_data_value_for_pointer,
		    low_value_for_dial_ruling)) {
	    store_managed_number_or_value_arg = 
		    ruling_low_value_angle_in_radians;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(pointer_for_dial,
		    (SI_Long)16L),store_managed_number_or_value_arg);
	    ISVREF(pointer_for_dial,(SI_Long)16L) = svref_new_value;
	}
	else if (NUM_GE(new_data_value_for_pointer,
		    high_value_for_dial_ruling)) {
	    store_managed_number_or_value_arg = 
		    ruling_high_value_angle_in_radians;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(pointer_for_dial,
		    (SI_Long)16L),store_managed_number_or_value_arg);
	    ISVREF(pointer_for_dial,(SI_Long)16L) = svref_new_value;
	}
	else {
	    store_managed_number_or_value_arg = 
		    add(ruling_low_value_angle_in_radians,
		    ltimes(divide(minus(lfloat(new_data_value_for_pointer,
		    float_constant_1),low_value_for_dial_ruling),
		    minus(high_value_for_dial_ruling,
		    low_value_for_dial_ruling)),
		    minus(ruling_high_value_angle_in_radians,
		    ruling_low_value_angle_in_radians)));
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(pointer_for_dial,
		    (SI_Long)16L),store_managed_number_or_value_arg);
	    ISVREF(pointer_for_dial,(SI_Long)16L) = svref_new_value;
	}
	return VALUES_1(pointer_for_dial);
    }
    else if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(2,FIX((SI_Long)1L),string_constant);
    else
	return VALUES_1(Nil);
}

static Object Qadd_solid_rectangle;  /* add-solid-rectangle */

/* DRAW-FOR-RULING-FOR-DIAL */
Object draw_for_ruling_for_dial(ruling_for_dial)
    Object ruling_for_dial;
{
    Object gensymed_symbol, parent_dial_for_ruling, managed_number_or_value;
    Object temp, x_center_of_dial, y_center_of_dial, dial_radius;
    Object ruling_low_value_angle_in_radians;
    Object ruling_high_value_angle_in_radians;
    Object angle_between_markings_in_radians, ruling_marker_color_difference;
    Object length_of_ruling_markers, mark_angle, mark_x_position_in_window;
    Object mark_y_position_in_window, scale, value, temp_1, temp_2, temp_3;
    Object temp_4;
    SI_Long mark_number, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long unshifted_result;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,34);
    if ( !((SI_Long)0L != (IFIX(ISVREF(ruling_for_dial,(SI_Long)5L)) & 
	    (SI_Long)2048L))) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(ruling_for_dial,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	parent_dial_for_ruling = gensymed_symbol;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)16L);
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
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	    if ( !TRUEP(temp))
		make_or_reformat_ruling_for_dial(ruling_for_dial,
			parent_dial_for_ruling);
	    gensymed_symbol = ISVREF(ruling_for_dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    x_center_of_dial = add(gensymed_symbol,
		    ISVREF(parent_dial_for_ruling,(SI_Long)27L));
	    gensymed_symbol = ISVREF(ruling_for_dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    y_center_of_dial = add(gensymed_symbol,
		    ISVREF(parent_dial_for_ruling,(SI_Long)28L));
	    dial_radius = ISVREF(parent_dial_for_ruling,(SI_Long)26L);
	    managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)16L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		ruling_low_value_angle_in_radians = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		ruling_low_value_angle_in_radians = 
			aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		ruling_low_value_angle_in_radians = 
			copy_text_string(managed_number_or_value);
	    else
		ruling_low_value_angle_in_radians = managed_number_or_value;
	    managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)17L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		ruling_high_value_angle_in_radians = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		ruling_high_value_angle_in_radians = 
			aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		ruling_high_value_angle_in_radians = 
			copy_text_string(managed_number_or_value);
	    else
		ruling_high_value_angle_in_radians = managed_number_or_value;
	    managed_number_or_value = ISVREF(ruling_for_dial,(SI_Long)18L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		angle_between_markings_in_radians = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		angle_between_markings_in_radians = 
			aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		angle_between_markings_in_radians = 
			copy_text_string(managed_number_or_value);
	    else
		angle_between_markings_in_radians = managed_number_or_value;
	    ruling_marker_color_difference = 
		    FIXNUM_LOGXOR(Current_foreground_color_value,
		    Current_background_color_value);
	    length_of_ruling_markers = ISVREF(parent_dial_for_ruling,
		    (SI_Long)30L);
	    mark_number = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(sub1(ISVREF(parent_dial_for_ruling,
		    (SI_Long)25L)));
	    mark_angle = Nil;
	    mark_x_position_in_window = Nil;
	    mark_y_position_in_window = Nil;
	  next_loop:
	    if (mark_number > ab_loop_bind_)
		goto end_loop;
	    mark_angle = minus(ruling_low_value_angle_in_radians,
		    ltimes(FIX(mark_number),
		    angle_between_markings_in_radians));
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    value = l_round(add(ltimes(minus(dial_radius,
		    length_of_ruling_markers),lcos(mark_angle)),
		    x_center_of_dial),_);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    mark_x_position_in_window = FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    value = l_round(minus(y_center_of_dial,
		    ltimes(minus(dial_radius,length_of_ruling_markers),
		    lsin(mark_angle))),_);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    mark_y_position_in_window = FIX(gensymed_symbol_1 + 
		    gensymed_symbol_2);
	    temp = mark_x_position_in_window;
	    temp_1 = mark_y_position_in_window;
	    temp_2 = mark_x_position_in_window;
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		temp_3 = FIX((SI_Long)3L);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		    (SI_Long)3L && (SI_Long)3L < 
		    IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(Current_image_x_scale) * 
			(SI_Long)3L + (SI_Long)2048L;
		temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_3 = scalef_function(Current_image_x_scale,
			FIX((SI_Long)3L));
	    temp_2 = add(temp_2,temp_3);
	    temp_3 = mark_y_position_in_window;
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		temp_4 = FIX((SI_Long)3L);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		    (SI_Long)3L && (SI_Long)3L < 
		    IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(Current_image_y_scale) * 
			(SI_Long)3L + (SI_Long)2048L;
		temp_4 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_4 = scalef_function(Current_image_y_scale,
			FIX((SI_Long)3L));
	    draw_graphic_element(6,Qadd_solid_rectangle,temp,temp_1,temp_2,
		    add(temp_3,temp_4),ruling_marker_color_difference);
	    mark_number = mark_number + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qwhite;              /* white */

/* DRAW-FOR-POINTER-FOR-DIAL */
Object draw_for_pointer_for_dial(pointer_for_dial)
    Object pointer_for_dial;
{
    Object pointer_position_in_radians_qm, gensymed_symbol, parent_dial;
    Object parent_dial_for_pointer, x_center_of_dial, y_center_of_dial;
    Object length_of_dial_pointer, temp, pointer_position_in_radians;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, scale, value;
    Object list_of_points_for_pointer, point_width_in_window;
    Object point_height_in_window, color_value_2, pointer_arrowhead_size;
    Object point, ab_loop_list_, arrowhead_base_x, arrowhead_base_y, temp_2;
    SI_Long number_of_points_for_pointer, point_number, ab_loop_bind_;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    SI_Long x_center_of_dial_in_window, y_center_of_dial_in_window, point_size;
    SI_Long point_color_difference, arrowhead_right_x_in_window;
    SI_Long arrowhead_left_x_in_window, arrowhead_right_y_in_window;
    SI_Long arrowhead_left_y_in_window, arrowhead_base_x_in_window;
    SI_Long arrowhead_base_y_in_window;
    double temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,35);
    pointer_position_in_radians_qm = ISVREF(pointer_for_dial,(SI_Long)16L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(pointer_for_dial,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    parent_dial = gensymed_symbol;
    if (pointer_position_in_radians_qm &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(parent_dial,(SI_Long)5L)) & (SI_Long)2048L))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(pointer_for_dial,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    parent_dial_for_pointer = gensymed_symbol;
	    gensymed_symbol = ISVREF(pointer_for_dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    x_center_of_dial = add(gensymed_symbol,
		    ISVREF(parent_dial_for_pointer,(SI_Long)27L));
	    gensymed_symbol = ISVREF(pointer_for_dial,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    y_center_of_dial = add(gensymed_symbol,
		    ISVREF(parent_dial_for_pointer,(SI_Long)28L));
	    length_of_dial_pointer = ISVREF(parent_dial_for_pointer,
		    (SI_Long)29L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(pointer_position_in_radians_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(pointer_position_in_radians_qm)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(pointer_position_in_radians_qm,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(pointer_position_in_radians_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(pointer_position_in_radians_qm)) 
		    == (SI_Long)1L)
		temp = aref1(pointer_position_in_radians_qm,FIX((SI_Long)0L));
	    else if (text_string_p(pointer_position_in_radians_qm))
		temp = copy_text_string(pointer_position_in_radians_qm);
	    else
		temp = pointer_position_in_radians_qm;
	    pointer_position_in_radians = lfloat(temp,float_constant_1);
	    number_of_points_for_pointer = (SI_Long)20L;
	    point_number = (SI_Long)1L;
	    ab_loop_bind_ = number_of_points_for_pointer;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (point_number > ab_loop_bind_)
		goto end_loop;
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
	    value = l_round(add(x_center_of_dial,
		    ltimes(ltimes(length_of_dial_pointer,
		    DOUBLE_TO_DOUBLE_FLOAT((double)((float)point_number) / 
		    (double)number_of_points_for_pointer)),
		    DOUBLE_TO_DOUBLE_FLOAT(cos(temp_1)))),_);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
	    value = l_round(minus(y_center_of_dial,
		    ltimes(ltimes(length_of_dial_pointer,
		    DOUBLE_TO_DOUBLE_FLOAT((double)((float)point_number) / 
		    (double)number_of_points_for_pointer)),
		    DOUBLE_TO_DOUBLE_FLOAT(sin(temp_1)))),_);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
		    FIX(gensymed_symbol_1 + gensymed_symbol_2)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    point_number = point_number + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    list_of_points_for_pointer = ab_loopvar_;
	    goto end_1;
	    list_of_points_for_pointer = Qnil;
	  end_1:;
	    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(x_center_of_dial);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_center_of_dial) && FIXNUM_LT(x_center_of_dial,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
			x_center_of_dial)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_x_scale,
			x_center_of_dial));
	    x_center_of_dial_in_window = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		gensymed_symbol_2 = IFIX(y_center_of_dial);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_center_of_dial) && FIXNUM_LT(y_center_of_dial,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
			y_center_of_dial)) + (SI_Long)2048L;
		gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_2 = 
			IFIX(scalef_function(Current_image_y_scale,
			y_center_of_dial));
	    y_center_of_dial_in_window = gensymed_symbol_1 + gensymed_symbol_2;
	    point_size = (SI_Long)2L;
	    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		point_width_in_window = FIX(point_size);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_x_scale) && 
		    FIXNUM_LT(Current_image_x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		    point_size && point_size < 
		    IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(Current_image_x_scale) * 
			point_size + (SI_Long)2048L;
		point_width_in_window = FIX(unshifted_result >>  -  - 
			(SI_Long)12L);
	    }
	    else
		point_width_in_window = 
			scalef_function(Current_image_x_scale,FIX(point_size));
	    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		point_height_in_window = FIX(point_size);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    Current_image_y_scale) && 
		    FIXNUM_LT(Current_image_y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		    point_size && point_size < 
		    IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(Current_image_y_scale) * 
			point_size + (SI_Long)2048L;
		point_height_in_window = FIX(unshifted_result >>  -  - 
			(SI_Long)12L);
	    }
	    else
		point_height_in_window = 
			scalef_function(Current_image_y_scale,FIX(point_size));
	    color_value_2 = printing_window_p(Current_window) ? 
		    Current_background_color_value : 
		    map_to_color_value(Qwhite);
	    point_color_difference = 
		    IFIX(FIXNUM_LOGXOR(Current_foreground_color_value,
		    color_value_2));
	    pointer_arrowhead_size = ISVREF(parent_dial_for_pointer,
		    (SI_Long)37L);
	    draw_graphic_element(6,Qadd_solid_rectangle,
		    FIX(x_center_of_dial_in_window),
		    FIX(y_center_of_dial_in_window),
		    add(FIX(x_center_of_dial_in_window),
		    point_width_in_window),
		    add(FIX(y_center_of_dial_in_window),
		    point_height_in_window),FIX(point_color_difference));
	    point = Nil;
	    ab_loop_list_ = list_of_points_for_pointer;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    point = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    draw_graphic_element(6,Qadd_solid_rectangle,CAR(point),
		    CDR(point),add(CAR(point),point_width_in_window),
		    add(CDR(point),point_height_in_window),
		    FIX(point_color_difference));
	    goto next_loop_1;
	  end_loop_1:;
	    if (pointer_arrowhead_size) {
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		arrowhead_base_x = add(x_center_of_dial,
			ltimes(minus(length_of_dial_pointer,
			pointer_arrowhead_size),
			DOUBLE_TO_DOUBLE_FLOAT(cos(temp_1))));
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		arrowhead_base_y = minus(y_center_of_dial,
			ltimes(minus(length_of_dial_pointer,
			pointer_arrowhead_size),
			DOUBLE_TO_DOUBLE_FLOAT(sin(temp_1))));
		gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		scale = Current_image_x_scale;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		value = l_round(add(arrowhead_base_x,
			ltimes(pointer_arrowhead_size,
			DOUBLE_TO_DOUBLE_FLOAT(sin(temp_1)))),_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_right_x_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		scale = Current_image_x_scale;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		value = l_round(minus(arrowhead_base_x,
			ltimes(pointer_arrowhead_size,
			DOUBLE_TO_DOUBLE_FLOAT(sin(temp_1)))),_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_left_x_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		scale = Current_image_y_scale;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		value = l_round(add(arrowhead_base_y,
			ltimes(pointer_arrowhead_size,
			DOUBLE_TO_DOUBLE_FLOAT(cos(temp_1)))),_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_right_y_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		scale = Current_image_y_scale;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(pointer_position_in_radians);
		value = l_round(minus(arrowhead_base_y,
			ltimes(pointer_arrowhead_size,
			DOUBLE_TO_DOUBLE_FLOAT(cos(temp_1)))),_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_left_y_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
		scale = Current_image_x_scale;
		value = l_round(arrowhead_base_x,_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_base_x_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
		scale = Current_image_y_scale;
		value = l_round(arrowhead_base_y,_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_2 = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
		arrowhead_base_y_in_window = gensymed_symbol_1 + 
			gensymed_symbol_2;
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		    temp = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_x_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(Current_image_x_scale,
			    FIX((SI_Long)3L));
		temp = add(FIX(arrowhead_base_x_in_window),temp);
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		    temp_2 = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_y_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_2 = scalef_function(Current_image_y_scale,
			    FIX((SI_Long)3L));
		draw_graphic_element(6,Qadd_solid_rectangle,
			FIX(arrowhead_base_x_in_window),
			FIX(arrowhead_base_y_in_window),temp,
			add(FIX(arrowhead_base_y_in_window),temp_2),
			FIX(point_color_difference));
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		    temp = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_x_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(Current_image_x_scale,
			    FIX((SI_Long)3L));
		temp = add(FIX(arrowhead_right_x_in_window),temp);
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		    temp_2 = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_y_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_2 = scalef_function(Current_image_y_scale,
			    FIX((SI_Long)3L));
		draw_graphic_element(6,Qadd_solid_rectangle,
			FIX(arrowhead_right_x_in_window),
			FIX(arrowhead_right_y_in_window),temp,
			add(FIX(arrowhead_right_y_in_window),temp_2),
			FIX(point_color_difference));
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
		    temp = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_x_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(Current_image_x_scale,
			    FIX((SI_Long)3L));
		temp = add(FIX(arrowhead_left_x_in_window),temp);
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
		    temp_2 = FIX((SI_Long)3L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
			(SI_Long)3L && (SI_Long)3L < 
			IFIX(Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(Current_image_y_scale) * 
			    (SI_Long)3L + (SI_Long)2048L;
		    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_2 = scalef_function(Current_image_y_scale,
			    FIX((SI_Long)3L));
		draw_graphic_element(6,Qadd_solid_rectangle,
			FIX(arrowhead_left_x_in_window),
			FIX(arrowhead_left_y_in_window),temp,
			add(FIX(arrowhead_left_y_in_window),temp_2),
			FIX(point_color_difference));
	    }
	    result = reclaim_eval_tree_1(list_of_points_for_pointer);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-DISPLAY-FOR-DIAL */
Object clear_display_for_dial(dial)
    Object dial;
{
    Object dial_pointer_qm;

    x_note_fn_call(171,36);
    dial_pointer_qm = get_pointer_for_dial_if_any(dial);
    if (dial_pointer_qm) {
	update_images_of_block(dial_pointer_qm,T,T);
	remove_as_subblock_if_necessary(1,dial_pointer_qm);
	return delete_frame(dial_pointer_qm);
    }
    else
	return VALUES_1(Nil);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-DIAL */
Object activate_subclass_of_entity_for_dial(dial)
    Object dial;
{
    Object cell_array_qm;

    x_note_fn_call(171,37);
    cell_array_qm = get_lookup_slot_value_given_default(dial,Qcell_array,Nil);
    if (cell_array_qm)
	return activate_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-DIAL */
Object deactivate_subclass_of_entity_for_dial(dial)
    Object dial;
{
    Object cell_array_qm;

    x_note_fn_call(171,38);
    cell_array_qm = get_lookup_slot_value_given_default(dial,Qcell_array,Nil);
    if (cell_array_qm)
	return deactivate_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

static Object Qlow_value_for_meter_ruling;  /* low-value-for-meter-ruling */

/* RECLAIM-LOW-VALUE-FOR-METER-RULING-VALUE */
Object reclaim_low_value_for_meter_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,39);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)29L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qlow_value_for_meter_ruling);
    SVREF(frame,FIX((SI_Long)29L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-METER-RULING-VALUE */
Object reclaim_high_value_for_meter_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,40);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)30L));
    ISVREF(frame,(SI_Long)30L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qincrement_per_meter_ruling;  /* increment-per-meter-ruling */

/* RECLAIM-INCREMENT-PER-METER-RULING-VALUE */
Object reclaim_increment_per_meter_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,41);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)31L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qincrement_per_meter_ruling);
    SVREF(frame,FIX((SI_Long)31L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-LOW-VALUE-FOR-METER-RULING-VALUE */
Object reclaim_desired_low_value_for_meter_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,42);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)32L));
    ISVREF(frame,(SI_Long)32L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-HIGH-VALUE-FOR-METER-RULING-VALUE */
Object reclaim_desired_high_value_for_meter_ruling_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,43);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)33L));
    ISVREF(frame,(SI_Long)33L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qmarker_for_meter;   /* marker-for-meter */

/* INITIALIZE-FOR-MARKER-FOR-METER */
Object initialize_for_marker_for_meter(marker_for_meter)
    Object marker_for_meter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(171,44);
    frame = marker_for_meter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmarker_for_meter)) {
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
    svref_new_value = IFIX(ISVREF(marker_for_meter,(SI_Long)5L)) | 
	    (SI_Long)1024L;
    return VALUES_1(ISVREF(marker_for_meter,(SI_Long)5L) = 
	    FIX(svref_new_value));
}

/* INITIALIZE-AFTER-READING-FOR-MARKER-FOR-METER */
Object initialize_after_reading_for_marker_for_meter(marker_for_meter)
    Object marker_for_meter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_, svref_new_value;

    x_note_fn_call(171,45);
    frame = marker_for_meter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmarker_for_meter)) {
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
    svref_new_value = IFIX(ISVREF(marker_for_meter,(SI_Long)5L)) | 
	    (SI_Long)1024L;
    return VALUES_1(ISVREF(marker_for_meter,(SI_Long)5L) = 
	    FIX(svref_new_value));
}

/* RECLAIM-DISTANCE-BETWEEN-MARKINGS-FOR-METER-VALUE */
Object reclaim_distance_between_markings_for_meter_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(171,46);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)16L));
    ISVREF(frame,(SI_Long)16L) = svref_new_value;
    return VALUES_1(Nil);
}

/* GENERATE-SPOT-FOR-METER */
Object generate_spot_for_meter(meter,mouse_pointer)
    Object meter, mouse_pointer;
{
    x_note_fn_call(171,47);
    return push_last_spot(mouse_pointer,make_meter_spot_1(),meter);
}

/* GENERATE-SPOT-FOR-RULING-FOR-METER */
Object generate_spot_for_ruling_for_meter(ruling_for_meter,mouse_pointer)
    Object ruling_for_meter, mouse_pointer;
{
    x_note_fn_call(171,48);
    return generate_spot_for_aggregate(ruling_for_meter,mouse_pointer);
}

/* GENERATE-SPOT-FOR-MARKER-FOR-METER */
Object generate_spot_for_marker_for_meter(marker_for_meter,mouse_pointer)
    Object marker_for_meter, mouse_pointer;
{
    x_note_fn_call(171,49);
    return generate_spot_for_aggregate(marker_for_meter,mouse_pointer);
}

/* MAKE-METER */
Object make_meter(meter_type)
    Object meter_type;
{
    Object new_meter;

    x_note_fn_call(171,50);
    new_meter = make_entity(1,meter_type);
    make_or_reformat_ruling_for_meter(Nil,new_meter);
    return VALUES_1(new_meter);
}

static Object Qmeter;              /* meter */

/* INITIALIZE-AFTER-READING-FOR-METER */
Object initialize_after_reading_for_meter(meter)
    Object meter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,51);
    frame = meter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmeter)) {
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
    return make_or_reformat_ruling_for_meter(Nil,meter);
}

/* MAKE-OR-REFORMAT-RULING-FOR-METER */
Object make_or_reformat_ruling_for_meter(ruling_for_meter_qm,meter)
    Object ruling_for_meter_qm, meter;
{
    Object ruling_for_meter, ruling_low_value_position;
    Object ruling_high_value_position, managed_number_or_value;
    Object low_value_for_meter_ruling, high_value_for_meter_ruling;
    Object increment_per_meter_ruling, number_of_marks_for_meter;
    Object gensymed_symbol, temp, temp_1, temp_2;
    Object store_managed_number_or_value_arg, svref_new_value, low, high;
    Object increment, ab_queue_form_, ab_next_queue_element_;
    Object meter_marking_label, mark_position_in_meter, label_left_edge;
    Object label_bottom_edge, label_value, new_meter_marking_label;
    Object gensymed_symbol_4, gensymed_symbol_5;
    SI_Long mark_number, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,52);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	ruling_for_meter = ruling_for_meter_qm;
	if (ruling_for_meter);
	else
	    ruling_for_meter = make_frame(Qruling_for_meter);
	ruling_low_value_position = ISVREF(meter,(SI_Long)22L);
	ruling_high_value_position = ISVREF(meter,(SI_Long)23L);
	managed_number_or_value = ISVREF(meter,(SI_Long)29L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_meter_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_meter_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    low_value_for_meter_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    low_value_for_meter_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(meter,(SI_Long)30L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_meter_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_meter_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    high_value_for_meter_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    high_value_for_meter_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(meter,(SI_Long)31L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    increment_per_meter_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    increment_per_meter_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    increment_per_meter_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    increment_per_meter_ruling = managed_number_or_value;
	number_of_marks_for_meter = ISVREF(meter,(SI_Long)24L);
	if ( !TRUEP(ruling_for_meter_qm)) {
	    gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp = gensymed_symbol;
	    gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	    gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_2 = gensymed_symbol;
	    gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    set_edges_of_block(ruling_for_meter,temp,temp_1,temp_2,
		    gensymed_symbol);
	    add_subblock(ruling_for_meter,meter);
	}
	store_managed_number_or_value_arg = 
		divide(lfloat(minus(ruling_high_value_position,
		ruling_low_value_position),float_constant_1),
		sub1(ISVREF(meter,(SI_Long)24L)));
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(ruling_for_meter,
		(SI_Long)16L),store_managed_number_or_value_arg);
	ISVREF(ruling_for_meter,(SI_Long)16L) = svref_new_value;
	if (low_value_for_meter_ruling && increment_per_meter_ruling) {
	    store_managed_number_or_value_arg = 
		    add(low_value_for_meter_ruling,
		    ltimes(increment_per_meter_ruling,
		    sub1(number_of_marks_for_meter)));
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(meter,
		    (SI_Long)30L),store_managed_number_or_value_arg);
	    ISVREF(meter,(SI_Long)30L) = svref_new_value;
	}
	else if (low_value_for_meter_ruling && high_value_for_meter_ruling) {
	    store_managed_number_or_value_arg = 
		    divide(minus(high_value_for_meter_ruling,
		    low_value_for_meter_ruling),
		    sub1(number_of_marks_for_meter));
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(meter,
		    (SI_Long)31L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(meter,Qincrement_per_meter_ruling);
	    SVREF(meter,FIX((SI_Long)31L)) = svref_new_value;
	}
	else {
	    temp = SYMBOL_FUNCTION(ISVREF(meter,(SI_Long)34L));
	    managed_number_or_value = ISVREF(meter,(SI_Long)32L);
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
	    managed_number_or_value = ISVREF(meter,(SI_Long)33L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_2 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp_2 = copy_text_string(managed_number_or_value);
	    else
		temp_2 = managed_number_or_value;
	    result = FUNCALL_3(temp,temp_1,temp_2,number_of_marks_for_meter);
	    MVS_3(result,low,high,increment);
	    store_managed_number_or_value_arg = low;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(meter,
		    (SI_Long)29L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(meter,Qlow_value_for_meter_ruling);
	    SVREF(meter,FIX((SI_Long)29L)) = svref_new_value;
	    store_managed_number_or_value_arg = high;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(meter,
		    (SI_Long)30L),store_managed_number_or_value_arg);
	    ISVREF(meter,(SI_Long)30L) = svref_new_value;
	    store_managed_number_or_value_arg = increment;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(meter,
		    (SI_Long)31L),store_managed_number_or_value_arg);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(meter,Qincrement_per_meter_ruling);
	    SVREF(meter,FIX((SI_Long)31L)) = svref_new_value;
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(ruling_for_meter,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	meter_marking_label = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	meter_marking_label = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	remove_as_subblock_if_necessary(1,meter_marking_label);
	delete_frame(meter_marking_label);
	goto next_loop;
      end_loop:;
	mark_number = (SI_Long)0L;
	ab_loop_bind_ = IFIX(sub1(number_of_marks_for_meter));
	mark_position_in_meter = Nil;
	label_left_edge = Nil;
	label_bottom_edge = Nil;
	label_value = Nil;
	new_meter_marking_label = Nil;
      next_loop_1:
	if (mark_number > ab_loop_bind_)
	    goto end_loop_1;
	temp = FIX(mark_number);
	managed_number_or_value = ISVREF(ruling_for_meter,(SI_Long)16L);
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
	mark_position_in_meter = add(ruling_low_value_position,
		l_round(ltimes(temp,temp_1),_));
	gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	label_left_edge = gensymed_symbol;
	gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = IFIX(mark_position_in_meter);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	label_bottom_edge = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	label_value = add(low_value_for_meter_ruling,
		ltimes(FIX(mark_number),increment_per_meter_ruling));
	new_meter_marking_label = make_marking_label(label_value,
		FIX((SI_Long)4L),FIX((SI_Long)3L));
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(new_meter_marking_label,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	gensymed_symbol_4 = new_meter_marking_label;
	gensymed_symbol_1 = IFIX(label_left_edge);
	gensymed_symbol_5 = ISVREF(new_meter_marking_label,(SI_Long)14L);
	gensymed_symbol_5 = gensymed_symbol_5 ? ISVREF(gensymed_symbol_5,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_5);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = IFIX(label_bottom_edge);
	gensymed_symbol_5 = ISVREF(new_meter_marking_label,(SI_Long)14L);
	gensymed_symbol_5 = gensymed_symbol_5 ? ISVREF(gensymed_symbol_5,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_5);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		FIX(gensymed_symbol_1),FIX(gensymed_symbol_2));
	add_subblock(new_meter_marking_label,ruling_for_meter);
	mark_number = mark_number + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	result = VALUES_1(ruling_for_meter);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DETERMINE-STANDARD-METER-RULING */
Object determine_standard_meter_ruling(desired_low_value,
	    desired_high_value,number_of_markings)
    Object desired_low_value, desired_high_value, number_of_markings;
{
    Object desired_increment_per_ruling;

    x_note_fn_call(171,53);
    desired_increment_per_ruling = divide(lfloat(minus(desired_high_value,
	    desired_low_value),float_constant_1),number_of_markings);
    return VALUES_1(desired_increment_per_ruling);
}

/* CLEAR-DISPLAY-FOR-METER */
Object clear_display_for_meter(meter)
    Object meter;
{
    Object meter_marker_qm;

    x_note_fn_call(171,54);
    meter_marker_qm = get_marker_for_meter_if_any(meter);
    if (meter_marker_qm) {
	update_images_of_block(meter_marker_qm,T,T);
	remove_as_subblock_if_necessary(1,meter_marker_qm);
	return delete_frame(meter_marker_qm);
    }
    else
	return VALUES_1(Nil);
}

/* GET-MARKER-FOR-METER-IF-ANY */
Object get_marker_for_meter_if_any(meter)
    Object meter;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(171,55);
    gensymed_symbol = ACCESS_ONCE(ISVREF(meter,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Marker_for_meter_class_description,(SI_Long)18L));
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
    if (temp)
	return VALUES_1(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-RULING-FOR-METER */
Object get_ruling_for_meter(meter)
    Object meter;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(171,56);
    gensymed_symbol = ACCESS_ONCE(ISVREF(meter,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Ruling_for_meter_class_description,(SI_Long)18L));
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
    if (temp)
	return VALUES_1(subblock);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* EXPRESSION-CELL-UPDATED-FOR-METER */
Object expression_cell_updated_for_meter(meter,g2_cell_array,index_1,
	    old_cache_qm,new_cache_qm)
    Object meter, g2_cell_array, index_1, old_cache_qm, new_cache_qm;
{
    x_note_fn_call(171,57);
    return update_cell_based_display_for_meter(meter,old_cache_qm,
	    new_cache_qm,Nil);
}

/* UPDATE-DISPLAY-FOR-METER */
Object update_display_for_meter(meter,update_even_if_value_unchanged_qm,
	    wake_up_qm,update_even_if_not_showing_qm)
    Object meter, update_even_if_value_unchanged_qm, wake_up_qm;
    Object update_even_if_not_showing_qm;
{
    Object cached_value_qm;

    x_note_fn_call(171,58);
    cached_value_qm = get_cached_value_for_cell_based_display(meter);
    return update_cell_based_display_for_meter(meter,cached_value_qm,
	    cached_value_qm,update_even_if_value_unchanged_qm);
}

/* UPDATE-CELL-BASED-DISPLAY-FOR-METER */
Object update_cell_based_display_for_meter(meter,old_cache_qm,new_cache_qm,
	    update_even_if_value_unchanged_qm)
    Object meter, old_cache_qm, new_cache_qm;
    Object update_even_if_value_unchanged_qm;
{
    Object meter_marker_qm, new_display_value_qm, old_display_value_qm;
    Object new_meter_marker_qm, gensymed_symbol, gensymed_symbol_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,59);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	meter_marker_qm = get_marker_for_meter_if_any(meter);
	new_display_value_qm = CONSP(new_cache_qm) && 
		EQ(M_CDR(new_cache_qm),Qobsolete_datum) ? 
		M_CAR(new_cache_qm) : new_cache_qm;
	old_display_value_qm = CONSP(old_cache_qm) && 
		EQ(M_CDR(old_cache_qm),Qobsolete_datum) ? 
		M_CAR(old_cache_qm) : old_cache_qm;
	if (new_display_value_qm) {
	    if ( !( !TRUEP(update_even_if_value_unchanged_qm) && 
		    meter_marker_qm && old_display_value_qm && 
		    evaluation_value_eql(2,new_display_value_qm,
		    old_display_value_qm))) {
		if (meter_marker_qm)
		    update_images_of_block(meter_marker_qm,T,T);
		make_or_reformat_marker_for_meter(meter_marker_qm,meter,
			evaluation_value_value(new_display_value_qm));
		new_meter_marker_qm = meter_marker_qm;
		if (new_meter_marker_qm);
		else
		    new_meter_marker_qm = get_marker_for_meter_if_any(meter);
		if (new_meter_marker_qm)
		    update_images_of_block(new_meter_marker_qm,Nil,T);
		result = send_ws_representations_item_virtual_attribute_change(meter,
			get_property_value_function(3,
			get_symbol_properties_function(Qvalue_to_display),
			Qvirtual_attribute,Nil),Nil);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(meter,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)21L),(SI_Long)1L);
	    gensymed_symbol_1 = meter;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    result = send_ws_representations_item_virtual_attribute_change(meter,
		    get_property_value_function(3,
		    get_symbol_properties_function(Qvalue_to_display),
		    Qvirtual_attribute,Nil),Nil);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* INITIALIZE-FOR-METER */
Object initialize_for_meter(meter)
    Object meter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,60);
    frame = meter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmeter)) {
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

static Object string_constant_1;   /* "Attempting to display non-numeric values on a meter." */

/* MAKE-OR-REFORMAT-MARKER-FOR-METER */
Object make_or_reformat_marker_for_meter(marker_for_meter_qm,meter,
	    new_data_value_for_marker)
    Object marker_for_meter_qm, meter, new_data_value_for_marker;
{
    Object marker_for_meter, managed_number_or_value;
    Object low_value_for_meter_ruling, high_value_for_meter_ruling;
    Object ruling_low_value_position, ruling_high_value_position;
    Object marker_position_for_shift, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;
    SI_Long svref_new_value, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;

    x_note_fn_call(171,61);
    if ( !TRUEP(new_data_value_for_marker) || 
	    FIXNUMP(new_data_value_for_marker) || 
	    FLOATP(new_data_value_for_marker)) {
	marker_for_meter = marker_for_meter_qm;
	if (marker_for_meter);
	else
	    marker_for_meter = make_entity(1,Qmarker_for_meter);
	managed_number_or_value = ISVREF(meter,(SI_Long)29L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_meter_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_meter_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    low_value_for_meter_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    low_value_for_meter_ruling = managed_number_or_value;
	managed_number_or_value = ISVREF(meter,(SI_Long)30L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_meter_ruling = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    high_value_for_meter_ruling = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    high_value_for_meter_ruling = 
		    copy_text_string(managed_number_or_value);
	else
	    high_value_for_meter_ruling = managed_number_or_value;
	ruling_low_value_position = ISVREF(meter,(SI_Long)22L);
	ruling_high_value_position = ISVREF(meter,(SI_Long)23L);
	marker_position_for_shift = Nil;
	if ( !TRUEP(marker_for_meter_qm))
	    add_subblock(marker_for_meter,meter);
	if ( !((SI_Long)0L != (IFIX(ISVREF(meter,(SI_Long)5L)) & 
		(SI_Long)2048L) || (SI_Long)0L != (IFIX(ISVREF(meter,
		(SI_Long)5L)) & (SI_Long)1024L))) {
	    svref_new_value = IFIX(ISVREF(marker_for_meter,(SI_Long)5L)) & 
		     ~(SI_Long)1024L;
	    ISVREF(marker_for_meter,(SI_Long)5L) = FIX(svref_new_value);
	}
	if ( !TRUEP(new_data_value_for_marker)) {
	    ISVREF(marker_for_meter,(SI_Long)20L) = Nil;
	    marker_position_for_shift = low_value_for_meter_ruling;
	}
	else if (NUM_LE(new_data_value_for_marker,
		    low_value_for_meter_ruling)) {
	    marker_position_for_shift = ruling_low_value_position;
	    ISVREF(marker_for_meter,(SI_Long)20L) = marker_position_for_shift;
	}
	else if (NUM_GE(new_data_value_for_marker,
		    high_value_for_meter_ruling)) {
	    marker_position_for_shift = ruling_high_value_position;
	    ISVREF(marker_for_meter,(SI_Long)20L) = marker_position_for_shift;
	}
	else {
	    marker_position_for_shift = 
		    l_round(add(ruling_low_value_position,
		    ltimes(divide(minus(lfloat(new_data_value_for_marker,
		    float_constant_1),low_value_for_meter_ruling),
		    minus(high_value_for_meter_ruling,
		    low_value_for_meter_ruling)),
		    minus(ruling_high_value_position,
		    ruling_low_value_position))),_);
	    ISVREF(marker_for_meter,(SI_Long)20L) = marker_position_for_shift;
	}
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(marker_for_meter,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	gensymed_symbol_1 = marker_for_meter;
	gensymed_symbol_2 = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_2);
	gensymed_symbol_4 = IFIX(ISVREF(meter,(SI_Long)28L));
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	gensymed_symbol_2 = ISVREF(marker_for_meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_2 = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_2);
	gensymed_symbol_2 = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_2);
	gensymed_symbol_2 = ISVREF(meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_6 = IFIX(gensymed_symbol_2);
	gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6;
	gensymed_symbol_6 = IFIX(marker_position_for_shift);
	gensymed_symbol_5 = gensymed_symbol_5 - gensymed_symbol_6;
	gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
	gensymed_symbol_2 = ISVREF(marker_for_meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_2);
	gensymed_symbol_2 = ISVREF(marker_for_meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_6 = IFIX(gensymed_symbol_2);
	gensymed_symbol_2 = ISVREF(marker_for_meter,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_7 = IFIX(gensymed_symbol_2);
	gensymed_symbol_6 = 
		IFIX(l_round(DOUBLE_TO_DOUBLE_FLOAT((double)
		(gensymed_symbol_6 - gensymed_symbol_7) / 2.0),_));
	gensymed_symbol_5 = gensymed_symbol_5 + gensymed_symbol_6;
	gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_3),FIX(gensymed_symbol_4));
	return VALUES_1(marker_for_meter);
    }
    else if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(2,FIX((SI_Long)1L),string_constant_1);
    else
	return VALUES_1(Nil);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-METER */
Object activate_subclass_of_entity_for_meter(meter)
    Object meter;
{
    Object cell_array_qm;

    x_note_fn_call(171,62);
    cell_array_qm = get_lookup_slot_value_given_default(meter,Qcell_array,Nil);
    if (cell_array_qm)
	return activate_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-METER */
Object deactivate_subclass_of_entity_for_meter(meter)
    Object meter;
{
    Object cell_array_qm;

    x_note_fn_call(171,63);
    cell_array_qm = get_lookup_slot_value_given_default(meter,Qcell_array,Nil);
    if (cell_array_qm)
	return deactivate_g2_cell_array(cell_array_qm);
    else
	return VALUES_1(Nil);
}

/* DRAW-FOR-RULING-FOR-METER */
Object draw_for_ruling_for_meter(ruling_for_meter)
    Object ruling_for_meter;
{
    Object gensymed_symbol, color_or_metacolor, color_value, old_color_value;
    Object current_background_color_value, parent_meter_for_ruling;
    Object managed_number_or_value, temp, ruling_low_value_position;
    Object ruling_high_value_position, distance_between_markings_for_meter;
    Object ruling_marker_color_difference, length_of_ruling_markers_for_meter;
    Object width_of_ruling_markers_for_meter;
    Object space_for_ruling_labels_for_meter, mark_position_in_meter;
    Object mark_position, mark_x_position_in_window, mark_y_position_in_window;
    Object scale, temp_1, temp_2, temp_3, temp_4;
    SI_Long mark_number, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, value, unshifted_result;
    Declare_stack_pointer;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,64);
    SAVE_STACK();
    gensymed_symbol = ACCESS_ONCE(ISVREF(ruling_for_meter,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    color_or_metacolor = item_color(gensymed_symbol,Qg2_icon_background);
    if (EQ(color_or_metacolor,Qbackground))
	color_value = Current_background_color_value;
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	color_value = Current_foreground_color_value;
    else if (EQ(color_or_metacolor,Qtransparent))
	color_value = Current_background_color_value;
    else
	color_value = map_to_color_value(color_or_metacolor);
    old_color_value = Current_background_color_value;
    current_background_color_value = Current_background_color_value;
    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
	    0);
      set_current_background_color_value(color_value);
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(ruling_for_meter,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  parent_meter_for_ruling = gensymed_symbol;
	  managed_number_or_value = ISVREF(ruling_for_meter,(SI_Long)16L);
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
	  else if (text_string_p(managed_number_or_value))
	      temp = copy_text_string(managed_number_or_value);
	  else
	      temp = managed_number_or_value;
	  if ( !TRUEP(temp))
	      make_or_reformat_ruling_for_meter(ruling_for_meter,
		      parent_meter_for_ruling);
	  ruling_low_value_position = ISVREF(parent_meter_for_ruling,
		  (SI_Long)22L);
	  ruling_high_value_position = ISVREF(parent_meter_for_ruling,
		  (SI_Long)23L);
	  managed_number_or_value = ISVREF(ruling_for_meter,(SI_Long)16L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      distance_between_markings_for_meter = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      distance_between_markings_for_meter = 
		      aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      distance_between_markings_for_meter = 
		      copy_text_string(managed_number_or_value);
	  else
	      distance_between_markings_for_meter = managed_number_or_value;
	  ruling_marker_color_difference = 
		  FIXNUM_LOGXOR(Current_foreground_color_value,
		  Current_background_color_value);
	  length_of_ruling_markers_for_meter = 
		  ISVREF(parent_meter_for_ruling,(SI_Long)25L);
	  width_of_ruling_markers_for_meter = 
		  ISVREF(parent_meter_for_ruling,(SI_Long)26L);
	  space_for_ruling_labels_for_meter = 
		  ISVREF(parent_meter_for_ruling,(SI_Long)27L);
	  mark_number = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(sub1(ISVREF(parent_meter_for_ruling,
		  (SI_Long)24L)));
	  mark_position_in_meter = Nil;
	  mark_position = Nil;
	  mark_x_position_in_window = Nil;
	  mark_y_position_in_window = Nil;
	next_loop:
	  if (mark_number > ab_loop_bind_)
	      goto end_loop;
	  mark_position_in_meter = add(ruling_low_value_position,
		  l_round(ltimes(FIX(mark_number),
		  distance_between_markings_for_meter),_));
	  gensymed_symbol = ISVREF(parent_meter_for_ruling,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(parent_meter_for_ruling,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(parent_meter_for_ruling,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  gensymed_symbol_3 = IFIX(mark_position_in_meter);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  mark_position = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	  scale = Current_image_x_scale;
	  gensymed_symbol = ISVREF(parent_meter_for_ruling,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol_3 = IFIX(space_for_ruling_labels_for_meter);
	  value = gensymed_symbol_2 + gensymed_symbol_3;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = value;
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		  value < IFIX(Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
	  mark_x_position_in_window = FIX(gensymed_symbol_1 + 
		  gensymed_symbol_2);
	  gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(mark_position);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  Current_image_y_scale) && 
		  FIXNUM_LT(Current_image_y_scale,
		  Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  mark_position) && FIXNUM_LT(mark_position,
		  Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		      mark_position)) + (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = 
		      IFIX(scalef_function(Current_image_y_scale,
		      mark_position));
	  mark_y_position_in_window = FIX(gensymed_symbol_1 + 
		  gensymed_symbol_2);
	  temp = mark_x_position_in_window;
	  temp_1 = mark_y_position_in_window;
	  temp_2 = mark_x_position_in_window;
	  if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	      temp_3 = length_of_ruling_markers_for_meter;
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  Current_image_x_scale) && 
		  FIXNUM_LT(Current_image_x_scale,
		  Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  length_of_ruling_markers_for_meter) && 
		  FIXNUM_LT(length_of_ruling_markers_for_meter,
		  Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,
		      length_of_ruling_markers_for_meter)) + (SI_Long)2048L;
	      temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	  }
	  else
	      temp_3 = scalef_function(Current_image_x_scale,
		      length_of_ruling_markers_for_meter);
	  temp_2 = add(temp_2,temp_3);
	  temp_3 = mark_y_position_in_window;
	  if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	      temp_4 = width_of_ruling_markers_for_meter;
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  Current_image_y_scale) && 
		  FIXNUM_LT(Current_image_y_scale,
		  Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		  width_of_ruling_markers_for_meter) && 
		  FIXNUM_LT(width_of_ruling_markers_for_meter,
		  Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		      width_of_ruling_markers_for_meter)) + (SI_Long)2048L;
	      temp_4 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	  }
	  else
	      temp_4 = scalef_function(Current_image_y_scale,
		      width_of_ruling_markers_for_meter);
	  draw_graphic_element(6,Qadd_solid_rectangle,temp,temp_1,temp_2,
		  add(temp_3,temp_4),ruling_marker_color_difference);
	  mark_number = mark_number + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
      }
      POP_LOCAL_ALLOCATION(0,0);
      SAVE_VALUES(result);
      set_current_background_color_value(old_color_value);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* DRAW-FOR-MARKER-FOR-METER */
Object draw_for_marker_for_meter(marker_for_meter)
    Object marker_for_meter;
{
    Object gensymed_symbol, meter, color_or_metacolor, color_value;
    Object old_color_value, current_background_color_value;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(171,65);
    SAVE_STACK();
    gensymed_symbol = ACCESS_ONCE(ISVREF(marker_for_meter,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    meter = gensymed_symbol;
    if ( !((SI_Long)0L != (IFIX(ISVREF(meter,(SI_Long)5L)) & 
	    (SI_Long)2048L)) && ISVREF(marker_for_meter,(SI_Long)20L)) {
	color_or_metacolor = item_color(meter,Qg2_icon_background);
	if (EQ(color_or_metacolor,Qbackground))
	    color_value = Current_background_color_value;
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground))
	    color_value = Current_foreground_color_value;
	else if (EQ(color_or_metacolor,Qtransparent))
	    color_value = Current_background_color_value;
	else
	    color_value = map_to_color_value(color_or_metacolor);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(color_value);
	  SAVE_VALUES(draw_icon_for_entity(marker_for_meter));
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* SPOT-GENERATOR-FOR-READOUT-TABLE-FORMAT */
Object spot_generator_for_readout_table_format(readout_table,mouse_pointer)
    Object readout_table, mouse_pointer;
{
    x_note_fn_call(171,66);
    generate_spot_for_input_table(readout_table,mouse_pointer,
	    make_readout_table_spot_1());
    return VALUES_1(Nil);
}

static Object Qdefault_readout_table_format_name;  /* default-readout-table-format-name */

static Object Qformat_frame;       /* format-frame */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qtable_rows;         /* table-rows */

/* MAKE-READOUT-TABLE */
Object make_readout_table(readout_table_class)
    Object readout_table_class;
{
    Object readout_table, format_name, readout_table_format, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Object result;

    x_note_fn_call(171,67);
    readout_table = make_frame(readout_table_class);
    format_name = 
	    ISVREF(get_slot_description_of_class_description_function(Qdefault_readout_table_format_name,
	    lookup_global_or_kb_specific_property_value(readout_table_class,
	    Class_description_gkbprop),Nil),(SI_Long)6L);
    readout_table_format = get_instance_with_name_if_any(Qformat_frame,
	    format_name);
    if (readout_table_format);
    else
	readout_table_format = make_format_frame(format_name);
    skip_list = CDR(Symbol_properties_table);
    key_value = readout_table_class;
    key_hash_value = SXHASH_SYMBOL_1(readout_table_class) & 
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = readout_table_class;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Digital_clock_class_description,(SI_Long)18L));
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
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(readout_table,Qtable_rows);
	temp_2 = slot_value_cons_1(slot_value_list_2(Nil,
		make_initial_readout_table_value_text(readout_table)),Nil);
	SVREF(readout_table,FIX((SI_Long)19L)) = temp_2;
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(readout_table,Qtable_rows);
	temp_1 = make_initial_readout_table_expression_text(readout_table);
	temp_2 = slot_value_cons_1(slot_value_list_2(temp_1,
		make_initial_readout_table_value_text(readout_table)),Nil);
	SVREF(readout_table,FIX((SI_Long)19L)) = temp_2;
    }
    make_or_reformat_table(3,readout_table,readout_table_format,Nil);
    add_frame_representation_if_necessary(readout_table,readout_table);
    return VALUES_1(readout_table);
}

static Object Qexpressions_to_display;  /* expressions-to-display */

/* MAKE-INITIAL-READOUT-TABLE-EXPRESSION-TEXT */
Object make_initial_readout_table_expression_text(readout_table)
    Object readout_table;
{
    x_note_fn_call(171,68);
    return make_readout_table_expression_text(readout_table,
	    Qexpressions_to_display,Nil);
}

static Object Qreadout_table_text_cell_format;  /* readout-table-text-cell-format */

/* MAKE-READOUT-TABLE-EXPRESSION-TEXT */
Object make_readout_table_expression_text(readout_table,slot_name,
	    class_qualifier_qm)
    Object readout_table, slot_name, class_qualifier_qm;
{
    Object temp, temp_1;

    x_note_fn_call(171,69);
    temp = get_type_of_slot_if_any(3,readout_table,slot_name,
	    class_qualifier_qm);
    temp_1 = get_instance_with_name_if_any(Qformat_frame,
	    Qreadout_table_text_cell_format);
    if (temp_1);
    else
	temp_1 = make_format_frame(Qreadout_table_text_cell_format);
    return make_text_cell_for_slot(5,readout_table,slot_name,
	    class_qualifier_qm,temp,temp_1);
}

static Object Qreadout_table_display_value;  /* readout-table-display-value */

/* MAKE-INITIAL-READOUT-TABLE-VALUE-TEXT */
Object make_initial_readout_table_value_text(readout_table)
    Object readout_table;
{
    Object temp, temp_1;

    x_note_fn_call(171,70);
    temp = get_type_of_slot_if_any(3,readout_table,
	    Qreadout_table_display_value,Nil);
    temp_1 = get_instance_with_name_if_any(Qformat_frame,
	    Qreadout_table_text_cell_format);
    if (temp_1);
    else
	temp_1 = make_format_frame(Qreadout_table_text_cell_format);
    return make_text_cell_for_slot(5,readout_table,
	    Qreadout_table_display_value,Nil,temp,temp_1);
}

/* EXPRESSION-CELL-UPDATED-FOR-READOUT-TABLE */
Object expression_cell_updated_for_readout_table(readout_table,
	    g2_cell_array,index_1,old_cache_qm,new_cache_qm)
    Object readout_table, g2_cell_array, index_1, old_cache_qm, new_cache_qm;
{
    x_note_fn_call(171,71);
    return update_cell_based_display_for_readout_table(readout_table,
	    old_cache_qm,new_cache_qm,Nil);
}

/* UPDATE-DISPLAY-FOR-READOUT-TABLE */
Object update_display_for_readout_table(readout_table,
	    update_even_if_value_unchanged_qm,wake_up_qm,
	    update_even_if_not_showing_qm)
    Object readout_table, update_even_if_value_unchanged_qm, wake_up_qm;
    Object update_even_if_not_showing_qm;
{
    Object cached_value_qm;

    x_note_fn_call(171,72);
    cached_value_qm = get_cached_value_for_cell_based_display(readout_table);
    return update_cell_based_display_for_readout_table(readout_table,
	    cached_value_qm,cached_value_qm,update_even_if_value_unchanged_qm);
}

/* UPDATE-CELL-BASED-DISPLAY-FOR-READOUT-TABLE */
Object update_cell_based_display_for_readout_table(readout_table,
	    old_cache_qm,new_cache_qm,update_even_if_value_unchanged_qm)
    Object readout_table, old_cache_qm, new_cache_qm;
    Object update_even_if_value_unchanged_qm;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,73);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (update_even_if_value_unchanged_qm || new_cache_qm &&  
		!TRUEP(old_cache_qm) || old_cache_qm &&  
		!TRUEP(new_cache_qm) || new_cache_qm && old_cache_qm &&  
		!TRUEP(evaluation_value_eql(2,new_cache_qm,old_cache_qm)))
	    result = change_slot_value(3,readout_table,
		    Qreadout_table_display_value,Nil);
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qreadout_table;      /* readout-table */

/* INITIALIZE-FOR-READOUT-TABLE */
Object initialize_for_readout_table(readout_table)
    Object readout_table;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,74);
    frame = readout_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qreadout_table)) {
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

/* CLEAR-DISPLAY-FOR-READOUT-TABLE */
Object clear_display_for_readout_table(readout_table)
    Object readout_table;
{
    x_note_fn_call(171,75);
    return change_slot_value(3,readout_table,Qreadout_table_display_value,Nil);
}

/* ACTIVATE-FOR-READOUT-TABLE */
Object activate_for_readout_table(readout_table)
    Object readout_table;
{
    Object cell_array_qm, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,76);
    cell_array_qm = get_lookup_slot_value_given_default(readout_table,
	    Qcell_array,Nil);
    if (cell_array_qm)
	activate_g2_cell_array(cell_array_qm);
    frame = readout_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qreadout_table)) {
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

/* DEACTIVATE-FOR-READOUT-TABLE */
Object deactivate_for_readout_table(readout_table)
    Object readout_table;
{
    Object cell_array_qm, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,77);
    cell_array_qm = get_lookup_slot_value_given_default(readout_table,
	    Qcell_array,Nil);
    if (cell_array_qm)
	deactivate_g2_cell_array(cell_array_qm);
    frame = readout_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qreadout_table)) {
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

/* INITIALIZE-AFTER-READING-FOR-READOUT-TABLE */
Object initialize_after_reading_for_readout_table(readout_table)
    Object readout_table;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(171,78);
    frame = readout_table;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qreadout_table)) {
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
    return update_representations_of_slot_value(2,readout_table,
	    Qreadout_table_display_value);
}

static Object Qdisplay_up_to_date_qm;  /* display-up-to-date? */

/* UPDATE-DISPLAY-FOR-DIGITAL-CLOCK */
Object update_display_for_digital_clock(digital_clock,
	    update_even_if_value_unchanged_qm,wake_up_qm,
	    update_even_if_not_showing_qm)
    Object digital_clock, update_even_if_value_unchanged_qm, wake_up_qm;
    Object update_even_if_not_showing_qm;
{
    Object old_display_value, new_display_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(171,79);
    if (((SI_Long)0L != (IFIX(ISVREF(digital_clock,(SI_Long)5L)) & 
	    (SI_Long)1L) || (SI_Long)0L != (IFIX(ISVREF(digital_clock,
	    (SI_Long)4L)) & (SI_Long)16777216L)) && 
	    (update_even_if_not_showing_qm || 
	    rectangle_visible_p(digital_clock))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(digital_clock,(SI_Long)5L)) 
		    & (SI_Long)2048L))) {
		old_display_value = 
			get_lookup_slot_value_given_default(digital_clock,
			Qreadout_table_display_value,Nil);
		new_display_value = FIXNUM_MINUS(Gensym_time,
			Gensym_time_at_start);
		if ( !TRUEP(old_display_value) || 
			FIXNUM_NE(old_display_value,new_display_value)) {
		    change_slot_value(3,digital_clock,
			    Qreadout_table_display_value,new_display_value);
		    result = set_non_savable_lookup_slot_value(digital_clock,
			    Qdisplay_up_to_date_qm,T);
		}
		else
		    result = VALUES_1(Nil);
	    }
	    else
		result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qdisplay_wait_interval;  /* display-wait-interval */

static Object Qdisplay_update_interval;  /* display-update-interval */

static Object float_constant_2;    /* -1.0 */

static Object Qdisplay_update_priority;  /* display-update-priority */

static Object Qupdate_display_for_digital_clock;  /* update-display-for-digital-clock */

static Object Qdigital_clock;      /* digital-clock */

/* ACTIVATE-FOR-DIGITAL-CLOCK */
Object activate_for_digital_clock(digital_clock)
    Object digital_clock;
{
    Object old, new_1, def_structure_schedule_task_variable, temp, temp_1;
    Object svref_new_value, task, thing, structure_being_reclaimed, frame;
    Object sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    char svref_new_value_1;
    double gensymed_symbol, gensymed_symbol_1, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(171,80);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(digital_clock,(SI_Long)20L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,temp_1) = svref_new_value;
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
	gensymed_symbol = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	gensymed_symbol_1 = FIXNUMP(get_lookup_slot_value(digital_clock,
		Qdisplay_wait_interval)) ? 
		(double)IFIX(get_lookup_slot_value(digital_clock,
		Qdisplay_wait_interval)) : 
		DFLOAT_ISAREF_1(get_lookup_slot_value(digital_clock,
		Qdisplay_wait_interval),(SI_Long)0L);
	aref_new_value = gensymed_symbol + gensymed_symbol_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp_1 = ISVREF(task,(SI_Long)1L);
	if (FIXNUMP(get_lookup_slot_value(digital_clock,
		Qdisplay_update_interval)))
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(get_lookup_slot_value(digital_clock,
		    Qdisplay_update_interval)));
	else {
	    thing = get_lookup_slot_value(digital_clock,
		    Qdisplay_update_interval);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(get_lookup_slot_value(digital_clock,
			Qdisplay_update_interval),(SI_Long)0L));
	    else
		temp = float_constant_2;
	}
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	temp = get_lookup_slot_value(digital_clock,Qdisplay_update_priority);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qupdate_display_for_digital_clock;
	temp = SYMBOL_FUNCTION(Qupdate_display_for_digital_clock);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)4L);
	SVREF(task,FIX((SI_Long)13L)) = digital_clock;
	SVREF(task,FIX((SI_Long)14L)) = Nil;
	SVREF(task,FIX((SI_Long)15L)) = Nil;
	SVREF(task,FIX((SI_Long)16L)) = Nil;
	new_1 = task;
	if (CAS_SVREF(digital_clock,(SI_Long)20L,old,new_1)) {
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
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = old;
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
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    frame = digital_clock;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qdigital_clock)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_2;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_1;
  end_loop_1:
    method_function_qm = Qnil;
  end_2:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qthings_this_display_is_interested_in;  /* things-this-display-is-interested-in */

/* DEACTIVATE-FOR-DIGITAL-CLOCK */
Object deactivate_for_digital_clock(digital_clock)
    Object digital_clock;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object gensymed_symbol_1, variable, ab_loop_list_, pruned_interest_list;
    Object eval_list, last_1, next_qm, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(171,81);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(digital_clock,(SI_Long)20L);
    if (CAS_SVREF(digital_clock,(SI_Long)20L,gensymed_symbol,Nil)) {
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
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = ISVREF(digital_clock,(SI_Long)21L);
    if (CAS_SVREF(digital_clock,(SI_Long)21L,gensymed_symbol,Nil)) {
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
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(digital_clock,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)21L),(SI_Long)1L);
    gensymed_symbol_1 = digital_clock;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    set_non_savable_lookup_slot_value(digital_clock,Qdisplay_up_to_date_qm,
	    Nil);
    variable = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(digital_clock,
	    Qthings_this_display_is_interested_in,Nil);
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pruned_interest_list = delete_eval_element_1(digital_clock,
	    ISVREF(variable,(SI_Long)36L));
    ISVREF(variable,(SI_Long)36L) = pruned_interest_list;
    if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable,
	    (SI_Long)38L)))
	withdraw_backward_chaining(variable);
    goto next_loop_2;
  end_loop_2:;
    eval_list = get_lookup_slot_value_given_default(digital_clock,
	    Qthings_this_display_is_interested_in,Nil);
    if (eval_list) {
	last_1 = eval_list;
	next_qm = Nil;
      next_loop_3:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_3;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_3;
      end_loop_3:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    set_non_savable_lookup_slot_value(digital_clock,
	    Qthings_this_display_is_interested_in,Nil);
    frame = digital_clock;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_4:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_4;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qdigital_clock)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_3;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_4;
  end_loop_4:
    method_function_qm = Qnil;
  end_3:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* CLEAR-DISPLAY-FOR-DIGITAL-CLOCK */
Object clear_display_for_digital_clock(digital_clock)
    Object digital_clock;
{
    x_note_fn_call(171,82);
    return change_slot_value(3,digital_clock,Qreadout_table_display_value,Nil);
}

static Object array_constant;      /* # */

static Object string_constant_2;   /* " of " */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-DIAL */
Object denote_cell_array_element_for_dial(dial,component_particulars,
	    include_block_denotation_qm)
    Object dial, component_particulars, include_block_denotation_qm;
{
    x_note_fn_call(171,83);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)25L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_2);
}

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-METER */
Object denote_cell_array_element_for_meter(meter,component_particulars,
	    include_block_denotation_qm)
    Object meter, component_particulars, include_block_denotation_qm;
{
    x_note_fn_call(171,84);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)25L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_2);
}

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-READOUT-TABLE */
Object denote_cell_array_element_for_readout_table(readout_table,
	    component_particulars,include_block_denotation_qm)
    Object readout_table, component_particulars, include_block_denotation_qm;
{
    x_note_fn_call(171,85);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)25L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_2);
}

static Object Qcomputation_style_scan_interval;  /* computation-style-scan-interval */

static Object Qcomputation_style_initial_scan_wait_interval;  /* computation-style-initial-scan-wait-interval */

static Object Qcomputation_style_priority;  /* computation-style-priority */

static Object Qcomputation_style_value_domain;  /* computation-style-value-domain */

static Object Qdisplay_evaluation_should_use_simulated_values_qm;  /* display-evaluation-should-use-simulated-values? */

static Object Qsimulator;          /* simulator */

static Object Qinference_engine;   /* inference-engine */

static Object Qcomputation_style_tracing_and_breakpoints;  /* computation-style-tracing-and-breakpoints */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

/* UPDATE-COMPUTATION-STYLE-WITH-DISPLAY-SETTINGS */
Object update_computation_style_with_display_settings(computation_style,
	    display_frame)
    Object computation_style, display_frame;
{
    Object svref_new_value;

    x_note_fn_call(171,86);
    reclaim_slot_value(ISVREF(computation_style,(SI_Long)19L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(computation_style,
		Qcomputation_style_scan_interval);
    svref_new_value = 
	    copy_for_slot_value(get_lookup_slot_value(display_frame,
	    Qdisplay_update_interval));
    SVREF(computation_style,FIX((SI_Long)19L)) = svref_new_value;
    reclaim_slot_value(ISVREF(computation_style,(SI_Long)20L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(computation_style,
		Qcomputation_style_initial_scan_wait_interval);
    svref_new_value = 
	    copy_for_slot_value(get_lookup_slot_value(display_frame,
	    Qdisplay_wait_interval));
    SVREF(computation_style,FIX((SI_Long)20L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(computation_style,Qcomputation_style_priority);
    svref_new_value = get_lookup_slot_value(display_frame,
	    Qdisplay_update_priority);
    SVREF(computation_style,FIX((SI_Long)18L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(computation_style,
		Qcomputation_style_value_domain);
    svref_new_value = get_lookup_slot_value(display_frame,
	    Qdisplay_evaluation_should_use_simulated_values_qm) ? 
	    Qsimulator : Qinference_engine;
    SVREF(computation_style,FIX((SI_Long)27L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(computation_style,
		Qcomputation_style_tracing_and_breakpoints);
    svref_new_value = get_lookup_slot_value(display_frame,
	    Qtracing_and_breakpoints);
    return VALUES_1(SVREF(computation_style,FIX((SI_Long)22L)) = 
	    svref_new_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_slot_component_group, Qcurrent_computation_slot_component_group);

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qpart_stack;         /* part-stack */

static Object Qmark;               /* mark */

static Object Qtrend_chart;        /* trend-chart */

/* UPDATE-CELL-BASED-DISPLAY-COMPUTATION-STYLE */
Object update_cell_based_display_computation_style varargs_1(int, n)
{
    Object display_frame;
    Object cell_index, cell_array_qm, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_style, current_block_of_dependent_frame;
    Object current_edit_state, old_current_part_description;
    Object sub_class_bit_vector, temp_2, part_feature_index;
    Object exit_feature_handler, part_stack_pop_store, cons_1, next_cons;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store;
    SI_Long svref_new_value_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(6);

    x_note_fn_call(171,87);
    INIT_ARGS_nonrelocating();
    display_frame = REQUIRED_ARG_nonrelocating();
    cell_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    END_ARGS_nonrelocating();
    cell_array_qm = get_lookup_slot_value_given_default(display_frame,
	    Qcell_array,Nil);
    if (cell_array_qm) {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(display_frame,(SI_Long)1L),Nil);
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
	    gensymed_symbol_1 = nconc2(stack_change_list_2(display_frame,
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
	    M_CAR(gensymed_symbol_1) = display_frame;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		5);
	  current_flag_state_qm = (SI_Long)0L != 
		  (IFIX(ISVREF(display_frame,(SI_Long)5L)) & 
		  (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = display_frame;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(display_frame,(SI_Long)5L)) 
		      | (SI_Long)16777216L;
	      ISVREF(display_frame,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  current_computation_frame = display_frame;
	  current_computation_component_particulars = Nil;
	  current_computation_style = The_only_dynamic_computation_style;
	  current_block_of_dependent_frame = display_frame;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		  4);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		    3);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		      2);
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			1);
		  gensymed_symbol = Current_edit_state;
		  if (Generate_source_annotation_info) {
		      gensymed_symbol_1 = Current_edit_state ? 
			      get_current_sexp_annotation_hash() : Nil;
		      if (gensymed_symbol_1);
		      else
			  gensymed_symbol_1 = make_sexp_annotation_hash();
		  }
		  else
		      gensymed_symbol_1 = Nil;
		  current_edit_state = make_edit_state_1();
		  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			  0);
		    temp = Current_edit_state;
		    SVREF(temp,FIX((SI_Long)90L)) = gensymed_symbol_1;
		    old_current_part_description = Current_part_description;
		    Current_part_description = 
			    get_default_computation_style_of_class();
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp = Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = 
				    replenish_part_stack_cons_pool();
			temp = Current_part_description;
			M_CAR(gensymed_symbol_1) = temp;
			temp = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol_1) = temp;
			inline_note_allocate_cons(gensymed_symbol_1,
				Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol_1;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qmark;
		    temp = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol_1) = temp;
		    inline_note_allocate_cons(gensymed_symbol_1,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol_1;
		    enter_part_description(Current_part_description);
		    gensymed_symbol_1 = 
			    lookup_global_or_kb_specific_property_value(Qtrend_chart,
			    Class_description_gkbprop);
		    if (gensymed_symbol_1) {
			sub_class_bit_vector = ISVREF(ISVREF(display_frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_4 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_5 = (SI_Long)1L;
			    gensymed_symbol_6 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_5 = gensymed_symbol_5 << 
				    gensymed_symbol_6;
			    gensymed_symbol_4 = gensymed_symbol_4 & 
				    gensymed_symbol_5;
			    temp_1 = (SI_Long)0L < gensymed_symbol_4;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			update_computation_style_for_trend_chart(Current_computation_style,
				Current_computation_slot_component_group);
		    else
			update_computation_style_with_display_settings(Current_computation_style,
				display_frame);
		    temp_2 = register_expression_cell_during_compilation(3,
			    cell_array_qm,cell_index,T);
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_part_stack_conses_tail_vector,
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
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop;
		  end_loop:;
		    Current_part_description = old_current_part_description;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp = 
					ISVREF(Available_part_stack_conses_tail_vector,
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
			Stack_of_current_part_descriptions = next_cons;
		    }
		    if (gensymed_symbol) {
			temp = Current_edit_state;
			SVREF(temp,FIX((SI_Long)90L)) = Nil;
		    }
		    reclaim_edit_state_1(Current_edit_state);
		    result_1 = temp_2;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(display_frame,(SI_Long)5L)) 
		      &  ~(SI_Long)16777216L;
	      ISVREF(display_frame,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(display_frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = display_frame;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
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
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp_2 = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp_2) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(display_frame,
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
	      update_all_representations_of_slot(display_frame,
		      slot_description,Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(display_frame);
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
	      temp_1 = ATOM(temp_2);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return register_expression_cell_during_slot_putter(cell_array_qm,
		cell_index,T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* UPDATE-DISPLAY-IF-NOT-REPROCESSED */
Object update_display_if_not_reprocessed(reference_serial_number,display)
    Object reference_serial_number, display;
{
    Object gensymed_symbol, xa, ya, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, temp_1;
    char temp;

    x_note_fn_call(171,88);
    gensymed_symbol = ISVREF(display,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(display) ? EQ(ISVREF(display,(SI_Long)1L),
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
    if ( !temp) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(display,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)22L),(SI_Long)1L);
	gensymed_symbol_1 = display;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = T;
	gensymed_symbol_4 = Nil;
	temp_1 = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* KIND-OF-DISPLAY-P */
Object kind_of_display_p(frame)
    Object frame;
{
    Object sub_class_bit_vector, temp, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(171,89);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Dial_class_description,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Meter_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Readout_table_class_description,(SI_Long)18L));
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
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Digital_clock_class_description,(SI_Long)18L));
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
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qtrend_chart,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
		return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* KIND-OF-CELL-BASED-DISPLAY-P */
Object kind_of_cell_based_display_p(frame)
    Object frame;
{
    Object sub_class_bit_vector, temp, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(171,90);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Dial_class_description,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Meter_class_description,
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
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Readout_table_class_description,(SI_Long)18L));
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
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Digital_clock_class_description,(SI_Long)18L));
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
	    temp =  !temp_1 ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qtrend_chart,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
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
		return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_inference_background_collection_g2_struct;  /* g2-defstruct-structure-name::inference-background-collection-g2-struct */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qreclaim_frame_serial_number;  /* reclaim-frame-serial-number */

static Object Qupdate_display_if_not_reprocessed;  /* update-display-if-not-reprocessed */

static Object string_constant_3;   /* "G2 INTERNAL BUG, a wake up sent to ~a from ~NF.  Please inform ~
				    *           Gensym Software Support of this G2 wake up bug!"
				    */

/* VARIABLE-HAS-RECEIVED-A-VALUE */
Object variable_has_received_a_value(thing,variable)
    Object thing, variable;
{
    Object temp, type_name, x2, sub_class_bit_vector, schedule_task_qm, old;
    Object new_1, def_structure_schedule_task_variable, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(171,91);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	temp = delete_eval_element_1(variable,ISVREF(thing,(SI_Long)17L));
	SVREF(thing,FIX((SI_Long)17L)) = temp;
	schedule_computation_instance_execution(thing,ISVREF(thing,
		(SI_Long)14L),ISVREF(thing,(SI_Long)8L));
	if (Backward_chaining_displays)
	    return update_backward_chaining_displays_function(thing);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (SIMPLE_VECTOR_P(thing)) {
	    type_name = ISVREF(thing,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = delete_eval_element_1(variable,ISVREF(thing,(SI_Long)14L));
	    SVREF(thing,FIX((SI_Long)14L)) = temp;
	    return wake_up_code_body_invocation(thing);
	}
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct)) 
		    {
	    temp = delete_eval_element_1(variable,ISVREF(thing,(SI_Long)4L));
	    SVREF(thing,FIX((SI_Long)4L)) = temp;
	    return wake_up_inference_background_collection(thing);
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		if (temp_1) {
		    temp = delete_eval_element_1(variable,ISVREF(thing,
			    (SI_Long)35L));
		    ISVREF(thing,(SI_Long)35L) = temp;
		    wake_up_variable(thing);
		    if (Backward_chaining_displays)
			return update_backward_chaining_displays_function(thing);
		    else
			return VALUES_1(Nil);
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(thing,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(G2_expression_cell_class_description,
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
		    if (temp_1)
			return schedule_expression_cell_execution_given_cell(thing,
				ISVREF(ISVREF(thing,(SI_Long)4L),
				(SI_Long)2L),Nil);
		    else if (kind_of_display_p(thing)) {
			set_non_savable_lookup_slot_value(thing,
				Qthings_this_display_is_interested_in,
				delete_eval_element_1(variable,
				get_lookup_slot_value_given_default(thing,
				Qthings_this_display_is_interested_in,Nil)));
			schedule_task_qm = ISVREF(thing,(SI_Long)21L);
			if ( !(schedule_task_qm && 
				(ISVREF(schedule_task_qm,(SI_Long)6L) || 
				EQ(schedule_task_qm,Current_schedule_task)))) {
			    old = Nil;
			    new_1 = Nil;
			  next_loop:
			    old = ISVREF(thing,(SI_Long)21L);
			    def_structure_schedule_task_variable = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    if (def_structure_schedule_task_variable) {
				temp = 
					Chain_of_available_schedule_tasks_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = 
					ISVREF(def_structure_schedule_task_variable,
					(SI_Long)0L);
				SVREF(temp,svref_arg_2) = svref_new_value;
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
			    temp = ISVREF(task,(SI_Long)1L);
			    aref_new_value = -1.0;
			    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
			    temp = get_lookup_slot_value(thing,
				    Qdisplay_update_priority);
			    SVREF(task,FIX((SI_Long)4L)) = temp;
			    SVREF(task,FIX((SI_Long)5L)) = Nil;
			    temp = 
				    gensym_cons_1(Qreclaim_frame_serial_number,
				    Nil);
			    SVREF(task,FIX((SI_Long)9L)) = temp;
			    SVREF(task,FIX((SI_Long)10L)) = Nil;
			    g2_p =  !TRUEP(Nil);
			    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
			    temp = ISVREF(task,(SI_Long)1L);
			    aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
				    Current_g2_time : Current_real_time,
				    (SI_Long)0L);
			    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
			    SVREF(task,FIX((SI_Long)7L)) = 
				    Qupdate_display_if_not_reprocessed;
			    temp = 
				    SYMBOL_FUNCTION(Qupdate_display_if_not_reprocessed);
			    SVREF(task,FIX((SI_Long)8L)) = temp;
			    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
			    temp = copy_frame_serial_number(ISVREF(thing,
				    (SI_Long)3L));
			    SVREF(task,FIX((SI_Long)13L)) = temp;
			    SVREF(task,FIX((SI_Long)14L)) = thing;
			    new_1 = task;
			    if (CAS_SVREF(thing,(SI_Long)21L,old,new_1)) {
				task = new_1;
				ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ?
					 T : Nil;
				if (ctask);
				else
				    ctask = System_is_running;
				p = ISVREF(task,(SI_Long)4L);
				v = ctask ? Current_task_queue_vector : 
					Deferred_task_queue_vector;
				q = ISVREF(v,IFIX(p));
				SVREF(task,FIX((SI_Long)11L)) = q;
				temp = constant_queue_push_right(q,task);
				SVREF(task,FIX((SI_Long)6L)) = temp;
				if (ctask && FIXNUM_LT(p,
					Priority_of_next_task))
				    Priority_of_next_task = p;
				return VALUES_1(task);
			    }
			    else {
				inline_note_reclaim_cons(new_1,Nil);
				structure_being_reclaimed = new_1;
				PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
					0);
				  reclaim_schedule_task_args(ISVREF(new_1,
					  (SI_Long)9L));
				  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
				POP_SPECIAL();
				temp = 
					ISVREF(Chain_of_available_schedule_tasks_vector,
					IFIX(Current_thread_index));
				SVREF(new_1,FIX((SI_Long)0L)) = temp;
				temp = 
					Chain_of_available_schedule_tasks_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp,svref_arg_2) = new_1;
			    }
			    goto next_loop;
			  end_loop:
			    return VALUES_1(Qnil);
			}
			else
			    return VALUES_1(Nil);
		    }
		    else
			return VALUES_1(Qnil);
		}
	    }
	    else {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)1L),string_constant_3,
			    thing,variable);
		Suppress_warning_message_header_qm = Nil;
		return VALUES_1(Suppress_warning_message_header_qm);
	    }
	}
    }
}

/* VARIABLE-IS-NO-LONGER-AVAILABLE */
Object variable_is_no_longer_available(thing,variable)
    Object thing, variable;
{
    Object svref_new_value, temp, type_name, x2, sub_class_bit_vector;
    Object current_block_of_dependent_frame;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(171,92);
    if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	svref_new_value = delete_eval_element_1(variable,ISVREF(thing,
		(SI_Long)17L));
	SVREF(thing,FIX((SI_Long)17L)) = svref_new_value;
	temp = Backward_chaining_displays ? 
		update_backward_chaining_displays_function(thing) : Nil;
    }
    else {
	if (SIMPLE_VECTOR_P(thing)) {
	    type_name = ISVREF(thing,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = delete_eval_element_1(variable,ISVREF(thing,(SI_Long)14L));
	    SVREF(thing,FIX((SI_Long)14L)) = temp;
	}
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct)) 
		    {
	    svref_new_value = delete_eval_element_1(variable,ISVREF(thing,
		    (SI_Long)4L));
	    SVREF(thing,FIX((SI_Long)4L)) = svref_new_value;
	    temp = Nil;
	}
	else {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		if (temp_1) {
		    svref_new_value = delete_eval_element_1(variable,
			    ISVREF(thing,(SI_Long)35L));
		    ISVREF(thing,(SI_Long)35L) = svref_new_value;
		    temp = Backward_chaining_displays ? 
			    update_backward_chaining_displays_function(thing) 
			    : Nil;
		}
		else if (kind_of_display_p(thing))
		    temp = set_non_savable_lookup_slot_value(thing,
			    Qthings_this_display_is_interested_in,
			    delete_eval_element_1(variable,
			    get_lookup_slot_value_given_default(thing,
			    Qthings_this_display_is_interested_in,Nil)));
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(thing,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(G2_expression_cell_class_description,
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
		    if (temp_1) {
			current_block_of_dependent_frame = 
				ISVREF(ISVREF(thing,(SI_Long)4L),(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
				0);
			  temp = delete_eval_element_1(variable,
				  ISVREF(thing,(SI_Long)8L));
			  ISVREF(thing,(SI_Long)8L) = temp;
			POP_SPECIAL();
		    }
		    else
			temp = Qnil;
		}
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

/* INSTALL-EVENT-DETECTOR */
Object install_event_detector(block,event_type,event_consumer,extra_info)
    Object block, event_type, event_consumer, extra_info;
{
    Object new_event_detector, new_value, old_value;

    x_note_fn_call(171,93);
    new_event_detector = make_event_detector_1(event_type,block,
	    event_consumer,extra_info);
    new_value = eval_cons_1(new_event_detector,Nil);
    old_value = Nil;
  next_loop:
    old_value = ISVREF(block,(SI_Long)15L);
    M_CDR(new_value) = old_value;
    if (CAS_SVREF(block,(SI_Long)15L,old_value,new_value))
	goto end_loop;
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    new_value = eval_cons_1(new_event_detector,Nil);
    old_value = Nil;
  next_loop_1:
    old_value = ISVREF(event_consumer,(SI_Long)16L);
    M_CDR(new_value) = old_value;
    if (CAS_SVREF(event_consumer,(SI_Long)16L,old_value,new_value))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    return VALUES_1(Nil);
}

/* CLEAR-EVENT-DETECTORS */
Object clear_event_detectors(event_consumer)
    Object event_consumer;
{
    Object old, event_list, event, ab_loop_list_, block, svref_new_value;

    x_note_fn_call(171,94);
    old = Nil;
  next_loop:
    old = ISVREF(event_consumer,(SI_Long)16L);
    if (CAS_SVREF(event_consumer,(SI_Long)16L,old,Nil)) {
	event_list = old;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    event_list = Qnil;
  end_1:;
    event = Nil;
    ab_loop_list_ = event_list;
    block = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    event = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    block = ISVREF(event,(SI_Long)2L);
    svref_new_value = delete_eval_element_1(event,ISVREF(block,(SI_Long)15L));
    ISVREF(block,(SI_Long)15L) = svref_new_value;
    reclaim_event_detector_1(event);
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(event_list);
    return VALUES_1(Nil);
}

/* TRIGGER-EVENT-DETECTOR */
Object trigger_event_detector(event_detector)
    Object event_detector;
{
    Object consumer, monitored_block, temp, svref_arg_2;

    x_note_fn_call(171,95);
    consumer = ISVREF(event_detector,(SI_Long)3L);
    monitored_block = ISVREF(event_detector,(SI_Long)2L);
    temp = delete_eval_element_1(event_detector,ISVREF(consumer,(SI_Long)16L));
    SVREF(consumer,FIX((SI_Long)16L)) = temp;
    temp = delete_eval_element_1(event_detector,ISVREF(monitored_block,
	    (SI_Long)15L));
    ISVREF(monitored_block,(SI_Long)15L) = temp;
    inline_note_reclaim_cons(event_detector,Nil);
    temp = ISVREF(Chain_of_available_event_detectors_vector,
	    IFIX(Current_thread_index));
    SVREF(event_detector,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_event_detectors_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = event_detector;
    wake_up_code_body_invocation(consumer);
    return VALUES_1(Nil);
}

/* TRIGGER-AND-CLEAR-EVENT-DETECTORS */
Object trigger_and_clear_event_detectors(monitored_block)
    Object monitored_block;
{
    Object event_detectors;

    x_note_fn_call(171,96);
    event_detectors = Nil;
  next_loop:
    event_detectors = ISVREF(monitored_block,(SI_Long)15L);
    if ( !TRUEP(event_detectors))
	goto end_loop;
    trigger_event_detector(M_CAR(event_detectors));
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

void displays_INIT()
{
    Object temp, temp_1, temp_2;
    Object Qclear_event_detectors, AB_package, Qinstall_event_detector;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qclasses_which_define;
    Object Qdenote_cell_array_element;
    Object Qdenote_cell_array_element_for_readout_table;
    Object Qdenote_cell_array_element_for_meter;
    Object Qdenote_cell_array_element_for_dial, list_constant_9;
    Object Qclear_display, Qclear_display_for_digital_clock, Qdeactivate;
    Object Qdeactivate_for_digital_clock, Qactivate;
    Object Qactivate_for_digital_clock, Qupdate_display, string_constant_93;
    Object string_constant_92, list_constant_8, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_readout_table;
    Object Qdeactivate_for_readout_table, Qactivate_for_readout_table;
    Object Qclear_display_for_readout_table, Qinitialize;
    Object Qinitialize_for_readout_table, Qupdate_cell_based_display;
    Object Qupdate_cell_based_display_for_readout_table;
    Object Qupdate_display_for_readout_table, Qexpression_cell_updated;
    Object Qexpression_cell_updated_for_readout_table, Qformat_description;
    Object string_constant_84, Qspot_generator_for_readout_table_format;
    Object Qtable_format_spot_generator, Qreadout_table_format;
    Object string_constant_83, Qdisplay_format, Qformat_for_readout_table;
    Object Qexpression_to_display, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object list_constant_7, string_constant_74, string_constant_73;
    Object string_constant_72, string_constant_71, string_constant_70;
    Object string_constant_69, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61, Qtable;
    Object Qitem, Qdraw, Qdraw_for_marker_for_meter;
    Object Qdraw_for_ruling_for_meter, Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_meter;
    Object Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_meter, Qinitialize_for_meter;
    Object Qupdate_cell_based_display_for_meter, Qupdate_display_for_meter;
    Object Qexpression_cell_updated_for_meter, Qclear_display_for_meter;
    Object Qdetermine_standard_meter_ruling;
    Object Qinitialize_after_reading_for_meter, Qgenerate_spot;
    Object Qgenerate_spot_for_marker_for_meter;
    Object Qgenerate_spot_for_ruling_for_meter, Qgenerate_spot_for_meter;
    Object Qslot_value_reclaimer;
    Object Qreclaim_distance_between_markings_for_meter_value;
    Object Qdistance_between_markings_for_meter;
    Object Qinitialize_after_reading_for_marker_for_meter;
    Object Qinitialize_for_marker_for_meter, string_constant_60;
    Object list_constant_6, Qcreate_icon_description, string_constant_59;
    Object string_constant_58, string_constant_26, Qentity, string_constant_57;
    Object list_constant_4, string_constant_56;
    Object Qreclaim_desired_high_value_for_meter_ruling_value;
    Object Qdesired_high_value_for_meter_ruling;
    Object Qreclaim_desired_low_value_for_meter_ruling_value;
    Object Qdesired_low_value_for_meter_ruling;
    Object Qreclaim_increment_per_meter_ruling_value;
    Object Qreclaim_high_value_for_meter_ruling_value;
    Object Qhigh_value_for_meter_ruling;
    Object Qreclaim_low_value_for_meter_ruling_value, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, list_constant_3;
    Object float_constant_4, float_constant_3, string_constant_49;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, array_constant_3, array_constant_1;
    Object array_constant_2, string_constant_35;
    Object Qdeactivate_subclass_of_entity_for_dial;
    Object Qactivate_subclass_of_entity_for_dial, Qclear_display_for_dial;
    Object Qdraw_for_pointer_for_dial, Qdraw_for_ruling_for_dial;
    Object Qinitialize_for_dial, Qupdate_cell_based_display_for_dial;
    Object Qupdate_display_for_dial, Qexpression_cell_updated_for_dial;
    Object Qdisplays, Qdetermine_standard_dial_ruling, string_constant_34;
    Object Qgenerate_spot_for_dial_marking_label, Qdraw_for_dial_marking_label;
    Object string_constant_33, list_constant_5, string_constant_32, Qtext_box;
    Object Qgenerate_spot_for_ruling_for_dial;
    Object Qgenerate_spot_for_pointer_for_dial, Qgenerate_spot_for_dial;
    Object Qreclaim_pointer_position_in_radians_qm_value;
    Object Qpointer_position_in_radians_qm;
    Object Qreclaim_angle_between_markings_in_radians_value;
    Object Qangle_between_markings_in_radians;
    Object Qreclaim_ruling_high_value_angle_in_radians_value;
    Object Qruling_high_value_angle_in_radians;
    Object Qreclaim_ruling_low_value_angle_in_radians_value;
    Object Qruling_low_value_angle_in_radians;
    Object Qinitialize_after_reading_for_pointer_for_dial;
    Object Qinitialize_after_reading_for_dial;
    Object Qinitialize_for_pointer_for_dial, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27;
    Object Qreclaim_desired_high_value_for_dial_ruling_value;
    Object Qdesired_high_value_for_dial_ruling;
    Object Qreclaim_desired_low_value_for_dial_ruling_value;
    Object Qdesired_low_value_for_dial_ruling;
    Object Qreclaim_increment_per_dial_ruling_value;
    Object Qreclaim_high_value_for_dial_ruling_value;
    Object Qhigh_value_for_dial_ruling;
    Object Qreclaim_low_value_for_dial_ruling_value, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4, Qgraph;
    Object Qshow_simulated_values, Qgeneric_method_lambda_list;
    Object list_constant_2, list_constant_1;
    Object Qupdate_even_if_value_unchanged_qm, Qnew_cache_qm, Qold_cache_qm;
    Object Qdisplay_class, list_constant, Qupdate_even_if_not_showing_qm;
    Object Qwake_up_qm, Qabsent_slot_putter;
    Object Qput_parent_dial_for_ruling_where_slot_is_absent;
    Object Qparent_dial_for_ruling;
    Object Qput_parent_dial_for_pointer_where_slot_is_absent;
    Object Qparent_dial_for_pointer;
    Object Qput_parent_meter_for_ruling_where_slot_is_absent;
    Object Qparent_meter_for_ruling;
    Object Qput_parent_meter_for_marker_where_slot_is_absent;
    Object Qparent_meter_for_marker;

    x_note_fn_call(171,97);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qparent_meter_for_marker = STATIC_SYMBOL("PARENT-METER-FOR-MARKER",
	    AB_package);
    Qput_parent_meter_for_marker_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PARENT-METER-FOR-MARKER-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_parent_meter_for_marker_where_slot_is_absent,
	    STATIC_FUNCTION(put_parent_meter_for_marker_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qparent_meter_for_marker,
	    SYMBOL_FUNCTION(Qput_parent_meter_for_marker_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qparent_meter_for_ruling = STATIC_SYMBOL("PARENT-METER-FOR-RULING",
	    AB_package);
    Qput_parent_meter_for_ruling_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PARENT-METER-FOR-RULING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_parent_meter_for_ruling_where_slot_is_absent,
	    STATIC_FUNCTION(put_parent_meter_for_ruling_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qparent_meter_for_ruling,
	    SYMBOL_FUNCTION(Qput_parent_meter_for_ruling_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qparent_dial_for_pointer = STATIC_SYMBOL("PARENT-DIAL-FOR-POINTER",
	    AB_package);
    Qput_parent_dial_for_pointer_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PARENT-DIAL-FOR-POINTER-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_parent_dial_for_pointer_where_slot_is_absent,
	    STATIC_FUNCTION(put_parent_dial_for_pointer_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qparent_dial_for_pointer,
	    SYMBOL_FUNCTION(Qput_parent_dial_for_pointer_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qparent_dial_for_ruling = STATIC_SYMBOL("PARENT-DIAL-FOR-RULING",
	    AB_package);
    Qput_parent_dial_for_ruling_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PARENT-DIAL-FOR-RULING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_parent_dial_for_ruling_where_slot_is_absent,
	    STATIC_FUNCTION(put_parent_dial_for_ruling_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qparent_dial_for_ruling,
	    SYMBOL_FUNCTION(Qput_parent_dial_for_ruling_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qupdate_display = STATIC_SYMBOL("UPDATE-DISPLAY",AB_package);
    Qdisplay_class = STATIC_SYMBOL("DISPLAY-CLASS",AB_package);
    Qupdate_even_if_value_unchanged_qm = 
	    STATIC_SYMBOL("UPDATE-EVEN-IF-VALUE-UNCHANGED\?",AB_package);
    Qwake_up_qm = STATIC_SYMBOL("WAKE-UP\?",AB_package);
    Qupdate_even_if_not_showing_qm = 
	    STATIC_SYMBOL("UPDATE-EVEN-IF-NOT-SHOWING\?",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qdisplay_class,
	    Qupdate_even_if_value_unchanged_qm,Qwake_up_qm,
	    Qupdate_even_if_not_showing_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qupdate_display,list_constant,
	    Qgeneric_method_lambda_list);
    Qupdate_cell_based_display = STATIC_SYMBOL("UPDATE-CELL-BASED-DISPLAY",
	    AB_package);
    Qold_cache_qm = STATIC_SYMBOL("OLD-CACHE\?",AB_package);
    Qnew_cache_qm = STATIC_SYMBOL("NEW-CACHE\?",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qdisplay_class,Qold_cache_qm,
	    Qnew_cache_qm,Qupdate_even_if_value_unchanged_qm);
    mutate_global_property(Qupdate_cell_based_display,list_constant_1,
	    Qgeneric_method_lambda_list);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qclear_display = STATIC_SYMBOL("CLEAR-DISPLAY",AB_package);
    list_constant_2 = STATIC_CONS(Qclear_display,Qnil);
    mutate_global_property(Qclear_display,list_constant_2,
	    Qgeneric_method_lambda_list);
    Qdisplay_evaluation_should_use_simulated_values_qm = 
	    STATIC_SYMBOL("DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES\?",
	    AB_package);
    Qshow_simulated_values = STATIC_SYMBOL("SHOW-SIMULATED-VALUES",AB_package);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    alias_slot_name(3,Qdisplay_evaluation_should_use_simulated_values_qm,
	    Qshow_simulated_values,Qreadout_table);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    alias_slot_name(3,Qdisplay_evaluation_should_use_simulated_values_qm,
	    Qshow_simulated_values,Qdial);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    alias_slot_name(3,Qdisplay_evaluation_should_use_simulated_values_qm,
	    Qshow_simulated_values,Qmeter);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    alias_slot_name(3,Qdisplay_evaluation_should_use_simulated_values_qm,
	    Qshow_simulated_values,Qgraph);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qdial,list_constant_3);
    string_constant_4 = 
	    STATIC_STRING("1n1m8v836ky1l8t1m83-Cy53QyShares some slot names w/Meter");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    array_constant_1 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_1,(SI_Long)0L,0.0);
    array_constant_2 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_2,(SI_Long)0L,0.25);
    array_constant_3 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_3,(SI_Long)0L,1.0);
    Qdetermine_standard_dial_ruling = 
	    STATIC_SYMBOL("DETERMINE-STANDARD-DIAL-RULING",AB_package);
    string_constant_5 = 
	    STATIC_STRING("13Qy4z8r8u8u836ky836ky01p8w9k3-qy3-qy1q1n83jy1mkk1m3-qyl1n83jy1mkl1ml3-py1n83jy1m3-pyl1m3-qy3-py1n83jy1mk3-py1m3-qy3-qy1o83*fy1m");
    string_constant_6 = 
	    STATIC_STRING("p3uy1m3uyp1m3-ly3uy1o83*fy1mq3uy1m3uyq1m3-ky3uy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r830dy830");
    string_constant_7 = 
	    STATIC_STRING("dy836ky836ky00001n1l8o1l8l1l83Hy000004z8r830ry830ry836ky836ky00001n1l8o1l8l1l83Hy000004z8r83J4y83J4y836ky836ky00001m1l8o1l8l0000");
    string_constant_8 = 
	    STATIC_STRING("04z8r83ZUy83ZUy836ky836ky03*my001m1l8o1l8l000004z8r83ZRy83ZRy836ky836ky0k001m1l8o1l8l000004z8r83Wny83Wny836ky836ky0p001m1l8o1l8l");
    string_constant_9 = 
	    STATIC_STRING("000004z8r83Jgy83Jgy836ky836ky03uy001m1l8o1l8l000004z8r83Jhy83Jhy836ky836ky03uy001m1l8o1l8l000004z8r83Jiy83Jiy836ky836ky03uy001m1");
    string_constant_10 = 
	    STATIC_STRING("l8o1l8l000004z8r83Tpy83Tpy836ky836ky03ay001m1l8o1l8l000004z8r83Try83Try836ky836ky0u001m1l8o1l8l000004z8r83DYy83DYy836ky836ky09l0");
    string_constant_11 = 
	    STATIC_STRING("01o1m8p8388y1l8o1l8l1l8z000004z8r83RMy83RMy836ky836ky00001m1l8o1l8l000004z8r83Cty83Cty836ky836ky09m001o1m8p8388y1l8o1l8l1l8z0000");
    string_constant_12 = 
	    STATIC_STRING("04z8r83Jcy83Jcy836ky836ky09n001m1l8o1l8l000004z8r83JYy83JYy836ky836ky09o001m1l8o1l8l000004z8r83MUy83MUy836ky836ky09p001m1l8o1l8l");
    string_constant_13 = 
	    STATIC_STRING("000004z8r83Xqy83Xqy836ky836ky0p001m1l8o1l8l000004z8r83K3y83K3y836ky836ky0w001m1l8o1l8l000004z8r83=gy83=gy836ky836ky00001o1n8p831");
    string_constant_14 = 
	    STATIC_STRING("*y83Gy1l83Ey1l8l1l83-5y000004z8r830wy830wy836ky836ky00001n1l83Ey1l83Cy1l8l000004z8r830cy830cy836ky836ky00001m1l83Ey1l8l000004z8r");
    string_constant_15 = 
	    STATIC_STRING("8300y8300y836ky836ky0p001o1m8p83=Qy1l83Ey1l8l1l8z000004z8r830Hy830Hy836ky836ky0m001o1m8p83=Qy1l83Ey1l8l1l8z000004z8r830Gy830Gy83");
    string_constant_16 = 
	    STATIC_STRING("6ky836ky0m001o1m8p83-Yy1l83Ey1l8l1l8z000004z8r83=Py83=Py836ky836ky00001o1m8p83Ky1l83Ey1l8l1l8z000004z8r830xy830xy836ky836ky00001");
    string_constant_17 = 
	    STATIC_STRING("m1l83Ey1l8l000004z8r830sy830sy836ky836ky00001m1l83Ey1l8l000004z8r83-py83-py836ky836ky00001q1l8l1l8z1l83Ey1l83Cy1m8p83-py1m83Dy53");
    string_constant_18 = 
	    STATIC_STRING("*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;), ~\nbreakpoint-lev");
    string_constant_19 = 
	    STATIC_STRING("el: (or default &lt;integer&gt;)]00000");
    float_constant_1 = STATIC_FLOAT(0.0);
    float_constant_3 = STATIC_FLOAT(0.25);
    float_constant_4 = STATIC_FLOAT(1.0);
    string_constant_20 = 
	    STATIC_STRING("13Sy8q1p836ky1m83Ry83-+y1m8v836ky8t1m83-Cy53QyShares some slot names w/Meter1m8u1p8w9k3-qy3-qy1q1n83jy1mkk1m3-qyl1n83jy1mkl1ml3-");
    string_constant_21 = 
	    STATIC_STRING("py1n83jy1m3-pyl1m3-qy3-py1n83jy1mk3-py1m3-qy3-qy1o83*fy1mp3uy1m3uyp1m3-ly3uy1o83*fy1mq3uy1m3uyq1m3-ky3uy1p830dy08o8l83Hy1p830ry0");
    string_constant_22 = 
	    STATIC_STRING("8o8l83Hy1o83J4y08o8l1o83ZUy3*my8o8l1o83ZRyk8o8l1o83Wnyp8o8l1o83Jgy3uy8o8l1o83Jhy3uy8o8l1o83Jiy3uy8o8l1o83Tpy3ay8o8l1o83Tryu8o8l1");
    string_constant_23 = 
	    STATIC_STRING("q83DYy9l1m8p8388y8o8l8z1o83RMy08o8l1q83Cty9m1m8p8388y8o8l8z1o83Jcy9l8o8l1o83JYy9n8o8l1o83MUy9o8o8l1o83Xqyp8o8l1o83K3yw8o8l1q83=g");
    string_constant_24 = 
	    STATIC_STRING("y01n8p831*y83Gy83Ey8l83-5y1p830wy083Ey83Cy8l1o830cy083Ey8l1q8300yp1m8p83=Qy83Ey8l8z1q830Hym1m8p83=Qy83Ey8l8z1q830Gym1m8p83-Yy83E");
    string_constant_25 = 
	    STATIC_STRING("y8l8z1q83=Py01m8p83Ky83Ey8l8z1o830xy083Ey8l1o830sy083Ey8l1r83-py08l8z83Ey83Cy1m8p83-py");
    temp = regenerate_optimized_constant(string_constant_4);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(array_constant_1);
    push_optimized_constant(array_constant_2);
    push_optimized_constant(array_constant_1);
    push_optimized_constant(array_constant_3);
    push_optimized_constant(Qdetermine_standard_dial_ruling);
    temp_1 = regenerate_optimized_constant(list(15,string_constant_5,
	    string_constant_6,string_constant_7,string_constant_8,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12,string_constant_13,string_constant_14,
	    string_constant_15,string_constant_16,string_constant_17,
	    string_constant_18,string_constant_19));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(float_constant_1);
    push_optimized_constant(float_constant_3);
    push_optimized_constant(float_constant_4);
    push_optimized_constant(Qdetermine_standard_dial_ruling);
    add_class_to_environment(9,Qdial,list_constant_3,Nil,temp,Nil,temp_1,
	    list_constant_3,regenerate_optimized_constant(list(6,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25)),Nil);
    Dial_class_description = 
	    lookup_global_or_kb_specific_property_value(Qdial,
	    Class_description_gkbprop);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    Qexpression_to_display = STATIC_SYMBOL("EXPRESSION-TO-DISPLAY",AB_package);
    alias_slot_name(3,Qexpressions_to_display,Qexpression_to_display,Qdial);
    Qlow_value_for_dial_ruling = STATIC_SYMBOL("LOW-VALUE-FOR-DIAL-RULING",
	    AB_package);
    Qreclaim_low_value_for_dial_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-DIAL-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_dial_ruling_value,
	    STATIC_FUNCTION(reclaim_low_value_for_dial_ruling_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qlow_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_dial_ruling_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_dial_ruling = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-DIAL-RULING",AB_package);
    Qreclaim_high_value_for_dial_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-DIAL-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_dial_ruling_value,
	    STATIC_FUNCTION(reclaim_high_value_for_dial_ruling_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qhigh_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_dial_ruling_value),
	    Qslot_value_reclaimer);
    Qincrement_per_dial_ruling = STATIC_SYMBOL("INCREMENT-PER-DIAL-RULING",
	    AB_package);
    Qreclaim_increment_per_dial_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-INCREMENT-PER-DIAL-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_increment_per_dial_ruling_value,
	    STATIC_FUNCTION(reclaim_increment_per_dial_ruling_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qincrement_per_dial_ruling,
	    SYMBOL_FUNCTION(Qreclaim_increment_per_dial_ruling_value),
	    Qslot_value_reclaimer);
    Qdesired_low_value_for_dial_ruling = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-DIAL-RULING",AB_package);
    Qreclaim_desired_low_value_for_dial_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-LOW-VALUE-FOR-DIAL-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_dial_ruling_value,
	    STATIC_FUNCTION(reclaim_desired_low_value_for_dial_ruling_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_low_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_dial_ruling_value),
	    Qslot_value_reclaimer);
    Qdesired_high_value_for_dial_ruling = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-DIAL-RULING",AB_package);
    Qreclaim_desired_high_value_for_dial_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-HIGH-VALUE-FOR-DIAL-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_dial_ruling_value,
	    STATIC_FUNCTION(reclaim_desired_high_value_for_dial_ruling_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_high_value_for_dial_ruling,
	    SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_dial_ruling_value),
	    Qslot_value_reclaimer);
    Qruling_for_dial = STATIC_SYMBOL("RULING-FOR-DIAL",AB_package);
    list_constant_4 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qruling_for_dial,list_constant_4);
    string_constant_26 = STATIC_STRING("1l1l8t");
    string_constant_27 = 
	    STATIC_STRING("1n4z8r83ZVy83ZVy83ZPy83ZPy00001m1l8o1l8l000004z8r83ZSy83ZSy83ZPy83ZPy00001m1l8o1l8l000004z8r83Gby83Gby83ZPy83ZPy00001m1l8o1l8l00");
    string_constant_28 = STATIC_STRING("000");
    string_constant_29 = 
	    STATIC_STRING("1p8q1n83ZPy1l9k8t1o83ZVy08o8l1o83ZSy08o8l1o83Gby08o8l");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_27,
	    string_constant_28));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qruling_for_dial,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_29),Nil);
    Ruling_for_dial_class_description = 
	    lookup_global_or_kb_specific_property_value(Qruling_for_dial,
	    Class_description_gkbprop);
    Qpointer_for_dial = STATIC_SYMBOL("POINTER-FOR-DIAL",AB_package);
    check_if_superior_classes_are_defined(Qpointer_for_dial,list_constant_4);
    string_constant_30 = 
	    STATIC_STRING("1l4z8r83Xsy83Xsy83Xry83Xry00001m1l8o1l8l00000");
    string_constant_31 = STATIC_STRING("1n8q1n83Xry1l9k8t1o83Xsy08o8l");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(string_constant_30);
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qpointer_for_dial,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_31),Nil);
    Pointer_for_dial_class_description = 
	    lookup_global_or_kb_specific_property_value(Qpointer_for_dial,
	    Class_description_gkbprop);
    Qinitialize_for_pointer_for_dial = 
	    STATIC_SYMBOL("INITIALIZE-FOR-POINTER-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_pointer_for_dial,
	    STATIC_FUNCTION(initialize_for_pointer_for_dial,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_pointer_for_dial);
    set_get(Qpointer_for_dial,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qpointer_for_dial,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_dial = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_dial,
	    STATIC_FUNCTION(initialize_after_reading_for_dial,NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_dial);
    set_get(Qdial,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qinitialize_after_reading_for_pointer_for_dial = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-POINTER-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_pointer_for_dial,
	    STATIC_FUNCTION(initialize_after_reading_for_pointer_for_dial,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_pointer_for_dial);
    set_get(Qpointer_for_dial,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qpointer_for_dial,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qruling_low_value_angle_in_radians = 
	    STATIC_SYMBOL("RULING-LOW-VALUE-ANGLE-IN-RADIANS",AB_package);
    Qreclaim_ruling_low_value_angle_in_radians_value = 
	    STATIC_SYMBOL("RECLAIM-RULING-LOW-VALUE-ANGLE-IN-RADIANS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_ruling_low_value_angle_in_radians_value,
	    STATIC_FUNCTION(reclaim_ruling_low_value_angle_in_radians_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qruling_low_value_angle_in_radians,
	    SYMBOL_FUNCTION(Qreclaim_ruling_low_value_angle_in_radians_value),
	    Qslot_value_reclaimer);
    Qruling_high_value_angle_in_radians = 
	    STATIC_SYMBOL("RULING-HIGH-VALUE-ANGLE-IN-RADIANS",AB_package);
    Qreclaim_ruling_high_value_angle_in_radians_value = 
	    STATIC_SYMBOL("RECLAIM-RULING-HIGH-VALUE-ANGLE-IN-RADIANS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_ruling_high_value_angle_in_radians_value,
	    STATIC_FUNCTION(reclaim_ruling_high_value_angle_in_radians_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qruling_high_value_angle_in_radians,
	    SYMBOL_FUNCTION(Qreclaim_ruling_high_value_angle_in_radians_value),
	    Qslot_value_reclaimer);
    Qangle_between_markings_in_radians = 
	    STATIC_SYMBOL("ANGLE-BETWEEN-MARKINGS-IN-RADIANS",AB_package);
    Qreclaim_angle_between_markings_in_radians_value = 
	    STATIC_SYMBOL("RECLAIM-ANGLE-BETWEEN-MARKINGS-IN-RADIANS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_angle_between_markings_in_radians_value,
	    STATIC_FUNCTION(reclaim_angle_between_markings_in_radians_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qangle_between_markings_in_radians,
	    SYMBOL_FUNCTION(Qreclaim_angle_between_markings_in_radians_value),
	    Qslot_value_reclaimer);
    Qpointer_position_in_radians_qm = 
	    STATIC_SYMBOL("POINTER-POSITION-IN-RADIANS\?",AB_package);
    Qreclaim_pointer_position_in_radians_qm_value = 
	    STATIC_SYMBOL("RECLAIM-POINTER-POSITION-IN-RADIANS\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_pointer_position_in_radians_qm_value,
	    STATIC_FUNCTION(reclaim_pointer_position_in_radians_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpointer_position_in_radians_qm,
	    SYMBOL_FUNCTION(Qreclaim_pointer_position_in_radians_qm_value),
	    Qslot_value_reclaimer);
    Qgenerate_spot_for_dial = STATIC_SYMBOL("GENERATE-SPOT-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_dial,
	    STATIC_FUNCTION(generate_spot_for_dial,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_dial);
    set_get(Qdial,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qgenerate_spot_for_pointer_for_dial = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-POINTER-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_pointer_for_dial,
	    STATIC_FUNCTION(generate_spot_for_pointer_for_dial,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_pointer_for_dial);
    set_get(Qpointer_for_dial,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qpointer_for_dial,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qgenerate_spot_for_ruling_for_dial = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-RULING-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_ruling_for_dial,
	    STATIC_FUNCTION(generate_spot_for_ruling_for_dial,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_ruling_for_dial);
    set_get(Qruling_for_dial,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qruling_for_dial,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qdial_marking_label = STATIC_SYMBOL("DIAL-MARKING-LABEL",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_5 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qdial_marking_label,list_constant_5);
    string_constant_32 = STATIC_STRING("0");
    string_constant_33 = STATIC_STRING("1m8q1m83v0y1l83-ly");
    temp = regenerate_optimized_constant(string_constant_32);
    temp_1 = regenerate_optimized_constant(string_constant_32);
    add_class_to_environment(9,Qdial_marking_label,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_33),Nil);
    Qruling_for_meter = STATIC_SYMBOL("RULING-FOR-METER",AB_package);
    Qg2_icon_background = STATIC_SYMBOL("G2-ICON-BACKGROUND",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qdraw_for_dial_marking_label = 
	    STATIC_SYMBOL("DRAW-FOR-DIAL-MARKING-LABEL",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_dial_marking_label,
	    STATIC_FUNCTION(draw_for_dial_marking_label,NIL,FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_dial_marking_label);
    set_get(Qdial_marking_label,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial_marking_label,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qmarking_label_format = STATIC_SYMBOL("MARKING-LABEL-FORMAT",AB_package);
    Qgenerate_spot_for_dial_marking_label = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-DIAL-MARKING-LABEL",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_dial_marking_label,
	    STATIC_FUNCTION(generate_spot_for_dial_marking_label,NIL,FALSE,
	    2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_dial_marking_label);
    set_get(Qdial_marking_label,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial_marking_label,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    float_constant = STATIC_FLOAT(3.141592653589793);
    string_constant_34 = 
	    STATIC_STRING("13Ly83-My837Wy3=+y837Xy3=+y83kyk83-=y3Ky83bys83ayq83Wys83cyp83*=yk83*1yk83*0yk83**yk");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qmarking_label_format,
	    regenerate_optimized_constant(string_constant_34),
	    Qformat_description);
    SET_SYMBOL_FUNCTION(Qdetermine_standard_dial_ruling,
	    STATIC_FUNCTION(determine_standard_dial_ruling,NIL,FALSE,3,3));
    Qdo_not_update_simulated_value_qm = 
	    STATIC_SYMBOL("DO-NOT-UPDATE-SIMULATED-VALUE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdo_not_update_simulated_value_qm,
	    Do_not_update_simulated_value_qm);
    Qdisplays = STATIC_SYMBOL("DISPLAYS",AB_package);
    record_system_variable(Qdo_not_update_simulated_value_qm,Qdisplays,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qexpression_cell_updated_for_dial = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_dial,
	    STATIC_FUNCTION(expression_cell_updated_for_dial,NIL,FALSE,5,5));
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_dial);
    set_get(Qdial,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    Qupdate_display_for_dial = STATIC_SYMBOL("UPDATE-DISPLAY-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_for_dial,
	    STATIC_FUNCTION(update_display_for_dial,NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_display_for_dial);
    set_get(Qdial,Qupdate_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qupdate_display,temp_2,Qclasses_which_define);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    Qvalue_to_display = STATIC_SYMBOL("VALUE-TO-DISPLAY",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qupdate_cell_based_display_for_dial = 
	    STATIC_SYMBOL("UPDATE-CELL-BASED-DISPLAY-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_cell_based_display_for_dial,
	    STATIC_FUNCTION(update_cell_based_display_for_dial,NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_cell_based_display_for_dial);
    set_get(Qdial,Qupdate_cell_based_display,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_cell_based_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qupdate_cell_based_display,temp_2,
	    Qclasses_which_define);
    Qinitialize_for_dial = STATIC_SYMBOL("INITIALIZE-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_dial,
	    STATIC_FUNCTION(initialize_for_dial,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_dial);
    set_get(Qdial,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    string_constant = 
	    STATIC_STRING("Attempting to display non-numeric values on a dial.");
    Qadd_solid_rectangle = STATIC_SYMBOL("ADD-SOLID-RECTANGLE",AB_package);
    Qdraw_for_ruling_for_dial = STATIC_SYMBOL("DRAW-FOR-RULING-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_ruling_for_dial,
	    STATIC_FUNCTION(draw_for_ruling_for_dial,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_ruling_for_dial);
    set_get(Qruling_for_dial,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qruling_for_dial,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qdraw_for_pointer_for_dial = STATIC_SYMBOL("DRAW-FOR-POINTER-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_pointer_for_dial,
	    STATIC_FUNCTION(draw_for_pointer_for_dial,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_pointer_for_dial);
    set_get(Qpointer_for_dial,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qpointer_for_dial,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qclear_display_for_dial = STATIC_SYMBOL("CLEAR-DISPLAY-FOR-DIAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qclear_display_for_dial,
	    STATIC_FUNCTION(clear_display_for_dial,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qclear_display_for_dial);
    set_get(Qdial,Qclear_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclear_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qclear_display,temp_2,Qclasses_which_define);
    Qactivate_subclass_of_entity_for_dial = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_dial,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_dial,NIL,FALSE,
	    1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_dial);
    set_get(Qdial,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_dial = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_dial,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_dial,NIL,
	    FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_dial);
    set_get(Qdial,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    check_if_superior_classes_are_defined(Qmeter,list_constant_3);
    string_constant_35 = 
	    STATIC_STRING("1n1m8v835my1l8t1m83-Cy53PyShares some slot names w/Dial");
    Qdetermine_standard_meter_ruling = 
	    STATIC_SYMBOL("DETERMINE-STANDARD-METER-RULING",AB_package);
    string_constant_36 = 
	    STATIC_STRING("13Ny4z8r8u8u835my835my01p8w9k3-Cy30ey1o1n83jy1mkk1m3-Cyl1n83jy1mkl1ml30dy1n83jy1m3-Byl1m3-Cy30dy1n83jy1mk30dy1m3-Cy30ey001o1l8l1");
    string_constant_37 = 
	    STATIC_STRING("l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r830dy830dy835my835my00001o1l83-4y1l8o1l8l1l83Hy000004z8r830ry830");
    string_constant_38 = 
	    STATIC_STRING("ry835my835my00001o1l83-4y1l8o1l8l1l83Hy000004z8r83ZWy83ZWy835my835my03Ly001m1l8o1l8l000004z8r83ZTy83ZTy835my835my030Fy001m1l8o1l");
    string_constant_39 = 
	    STATIC_STRING("8l000004z8r83Woy83Woy835my835my0p001m1l8o1l8l000004z8r83Tsy83Tsy835my835my0z001m1l8o1l8l000004z8r83eRy83eRy835my835my0n001m1l8o1");
    string_constant_40 = 
	    STATIC_STRING("l8l000004z8r83aay83aay835my835my03Qy001m1l8o1l8l000004z8r83VTy83VTy835my835my03fy001m1l8o1l8l000004z8r83DZy83DZy835my835my09l001");
    string_constant_41 = 
	    STATIC_STRING("o1m8p839Ry1l8o1l8l1l8z000004z8r83RPy83RPy835my835my00001m1l8o1l8l000004z8r83Cuy83Cuy835my835my09m001o1m8p839Ry1l8o1l8l1l8z000004");
    string_constant_42 = 
	    STATIC_STRING("z8r83Jey83Jey835my835my09n001m1l8o1l8l000004z8r83Jay83Jay835my835my09o001m1l8o1l8l000004z8r83MVy83MVy835my835my09p001m1l8o1l8l00");
    string_constant_43 = 
	    STATIC_STRING("0004z8r83K4y83K4y835my835my03Gy001m1l8o1l8l000004z8r83=gy83=gy835my835my00001p1n8p831*y83Gy1l83-4y1l83Ey1l8l1l83-5y000004z8r830w");
    string_constant_44 = 
	    STATIC_STRING("y830wy835my835my00001n1l83-4y1l83Ey1l8l000004z8r830cy830cy835my835my00001n1l83-4y1l83Ey1l8l000004z8r8300y8300y835my835my0p001p1m");
    string_constant_45 = 
	    STATIC_STRING("8p83=Qy1l83-4y1l83Ey1l8l1l8z000004z8r830Hy830Hy835my835my0m001p1m8p83=Qy1l83-4y1l83Ey1l8l1l8z000004z8r830Gy830Gy835my835my0m001p");
    string_constant_46 = 
	    STATIC_STRING("1m8p83-Yy1l83-4y1l83Ey1l8l1l8z000004z8r83=Py83=Py835my835my00001p1m8p83Ky1l83-4y1l83Ey1l8l1l8z000004z8r830xy830xy835my835my00001");
    string_constant_47 = 
	    STATIC_STRING("n1l83-4y1l83Ey1l8l000004z8r830sy830sy835my835my00001n1l83-4y1l83Ey1l8l000004z8r83-py83-py835my835my00001q1l8l1l8z1l83Ey1l83Cy1m8");
    string_constant_48 = 
	    STATIC_STRING("p83-py1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;), ~\n");
    string_constant_49 = 
	    STATIC_STRING("breakpoint-level: (or default &lt;integer&gt;)]00000");
    string_constant_50 = 
	    STATIC_STRING("13Py8q1p835my1m83Ry83-+y1m8v835my8t1m83-Cy53PyShares some slot names w/Dial1m8u1p8w9k3-Cy30ey1o1n83jy1mkk1m3-Cyl1n83jy1mkl1ml30d");
    string_constant_51 = 
	    STATIC_STRING("y1n83jy1m3-Byl1m3-Cy30dy1n83jy1mk30dy1m3-Cy30ey1q830dy083-4y8o8l83Hy1q830ry083-4y8o8l83Hy1o83ZWy3Ly8o8l1o83ZTy30Fy8o8l1o83Woyp8o");
    string_constant_52 = 
	    STATIC_STRING("8l1o83Tsyz8o8l1o83eRyn8o8l1o83aay3Qy8o8l1o83VTy3fy8o8l1q83DZy9l1m8p839Ry8o8l8z1o83RPy08o8l1q83Cuy9m1m8p839Ry8o8l8z1o83Jey9l8o8l1");
    string_constant_53 = 
	    STATIC_STRING("o83Jay9n8o8l1o83MVy9o8o8l1o83K4y3Gy8o8l1r83=gy01n8p831*y83Gy83-4y83Ey8l83-5y1p830wy083-4y83Ey8l1p830cy083-4y83Ey8l1r8300yp1m8p83");
    string_constant_54 = 
	    STATIC_STRING("=Qy83-4y83Ey8l8z1r830Hym1m8p83=Qy83-4y83Ey8l8z1r830Gym1m8p83-Yy83-4y83Ey8l8z1r83=Py01m8p83Ky83-4y83Ey8l8z1p830xy083-4y83Ey8l1p83");
    string_constant_55 = 
	    STATIC_STRING("0sy083-4y83Ey8l1r83-py08l8z83Ey83Cy1m8p83-py");
    temp = regenerate_optimized_constant(string_constant_35);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(array_constant_1);
    push_optimized_constant(array_constant_2);
    push_optimized_constant(array_constant_1);
    push_optimized_constant(array_constant_3);
    push_optimized_constant(Qdetermine_standard_meter_ruling);
    temp_1 = regenerate_optimized_constant(list(14,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(float_constant_1);
    push_optimized_constant(float_constant_3);
    push_optimized_constant(float_constant_4);
    push_optimized_constant(Qdetermine_standard_meter_ruling);
    add_class_to_environment(9,Qmeter,list_constant_3,Nil,temp,Nil,temp_1,
	    list_constant_3,regenerate_optimized_constant(list(6,
	    string_constant_50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55)),Nil);
    Meter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmeter,
	    Class_description_gkbprop);
    alias_slot_name(3,Qexpressions_to_display,Qexpression_to_display,Qmeter);
    Qlow_value_for_meter_ruling = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-METER-RULING",AB_package);
    Qreclaim_low_value_for_meter_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-METER-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_meter_ruling_value,
	    STATIC_FUNCTION(reclaim_low_value_for_meter_ruling_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlow_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_meter_ruling_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_meter_ruling = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-METER-RULING",AB_package);
    Qreclaim_high_value_for_meter_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-METER-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_meter_ruling_value,
	    STATIC_FUNCTION(reclaim_high_value_for_meter_ruling_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qhigh_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_meter_ruling_value),
	    Qslot_value_reclaimer);
    Qincrement_per_meter_ruling = 
	    STATIC_SYMBOL("INCREMENT-PER-METER-RULING",AB_package);
    Qreclaim_increment_per_meter_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-INCREMENT-PER-METER-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_increment_per_meter_ruling_value,
	    STATIC_FUNCTION(reclaim_increment_per_meter_ruling_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qincrement_per_meter_ruling,
	    SYMBOL_FUNCTION(Qreclaim_increment_per_meter_ruling_value),
	    Qslot_value_reclaimer);
    Qdesired_low_value_for_meter_ruling = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-METER-RULING",AB_package);
    Qreclaim_desired_low_value_for_meter_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-LOW-VALUE-FOR-METER-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_meter_ruling_value,
	    STATIC_FUNCTION(reclaim_desired_low_value_for_meter_ruling_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_low_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_meter_ruling_value),
	    Qslot_value_reclaimer);
    Qdesired_high_value_for_meter_ruling = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-METER-RULING",AB_package);
    Qreclaim_desired_high_value_for_meter_ruling_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-HIGH-VALUE-FOR-METER-RULING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_meter_ruling_value,
	    STATIC_FUNCTION(reclaim_desired_high_value_for_meter_ruling_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_high_value_for_meter_ruling,
	    SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_meter_ruling_value),
	    Qslot_value_reclaimer);
    check_if_superior_classes_are_defined(Qruling_for_meter,list_constant_4);
    string_constant_56 = 
	    STATIC_STRING("1l4z8r83K2y83K2y83ZQy83ZQy00001m1l8o1l8l00000");
    string_constant_57 = STATIC_STRING("1n8q1n83ZQy1l9k8t1o83K2y08o8l");
    temp = regenerate_optimized_constant(string_constant_26);
    temp_1 = regenerate_optimized_constant(string_constant_56);
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qruling_for_meter,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_57),Nil);
    Ruling_for_meter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qruling_for_meter,
	    Class_description_gkbprop);
    Qmarker_for_meter = STATIC_SYMBOL("MARKER-FOR-METER",AB_package);
    list_constant_6 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qmarker_for_meter,list_constant_6);
    string_constant_58 = 
	    STATIC_STRING("1m4z8r8u8u83Ujy83Ujy01p8w9k3Gy3ay1m1n83qy1n1mk3Gy1muu1mu3Qy1n1mk3Gy1muu1mu3Qy1n83jy1muk1m3Gy3ay001o1l8l1l8o1l8z1m83Dy53YySee com");
    string_constant_59 = 
	    STATIC_STRING("ment on ENTITY class definition000004z8r83Uky83Uky83Ujy83Ujy00001m1l8o1l8l00000");
    string_constant_60 = 
	    STATIC_STRING("1o8q1n83Ujy1l83-+y8t1m8u1p8w9k3Gy3ay1m1n83qy1n1mk3Gy1muu1mu3Qy1n1mk3Gy1muu1mu3Qy1n83jy1muk1m3Gy3ay1o83Uky08o8l");
    temp = regenerate_optimized_constant(string_constant_26);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_58,
	    string_constant_59));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qmarker_for_meter,list_constant_6,Nil,temp,
	    Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(string_constant_60),Nil);
    Marker_for_meter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmarker_for_meter,
	    Class_description_gkbprop);
    Qinitialize_for_marker_for_meter = 
	    STATIC_SYMBOL("INITIALIZE-FOR-MARKER-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_marker_for_meter,
	    STATIC_FUNCTION(initialize_for_marker_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_marker_for_meter);
    set_get(Qmarker_for_meter,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmarker_for_meter,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_marker_for_meter = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-MARKER-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_marker_for_meter,
	    STATIC_FUNCTION(initialize_after_reading_for_marker_for_meter,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_marker_for_meter);
    set_get(Qmarker_for_meter,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qmarker_for_meter,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qdistance_between_markings_for_meter = 
	    STATIC_SYMBOL("DISTANCE-BETWEEN-MARKINGS-FOR-METER",AB_package);
    Qreclaim_distance_between_markings_for_meter_value = 
	    STATIC_SYMBOL("RECLAIM-DISTANCE-BETWEEN-MARKINGS-FOR-METER-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_distance_between_markings_for_meter_value,
	    STATIC_FUNCTION(reclaim_distance_between_markings_for_meter_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdistance_between_markings_for_meter,
	    SYMBOL_FUNCTION(Qreclaim_distance_between_markings_for_meter_value),
	    Qslot_value_reclaimer);
    Qgenerate_spot_for_meter = STATIC_SYMBOL("GENERATE-SPOT-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_meter,
	    STATIC_FUNCTION(generate_spot_for_meter,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_meter);
    set_get(Qmeter,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qgenerate_spot_for_ruling_for_meter = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-RULING-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_ruling_for_meter,
	    STATIC_FUNCTION(generate_spot_for_ruling_for_meter,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_ruling_for_meter);
    set_get(Qruling_for_meter,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qruling_for_meter,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qgenerate_spot_for_marker_for_meter = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-MARKER-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_marker_for_meter,
	    STATIC_FUNCTION(generate_spot_for_marker_for_meter,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_marker_for_meter);
    set_get(Qmarker_for_meter,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qmarker_for_meter,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_meter = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_meter,
	    STATIC_FUNCTION(initialize_after_reading_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_meter);
    set_get(Qmeter,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    SET_SYMBOL_FUNCTION(Qdetermine_standard_meter_ruling,
	    STATIC_FUNCTION(determine_standard_meter_ruling,NIL,FALSE,3,3));
    Qclear_display_for_meter = STATIC_SYMBOL("CLEAR-DISPLAY-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qclear_display_for_meter,
	    STATIC_FUNCTION(clear_display_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qclear_display_for_meter);
    set_get(Qmeter,Qclear_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclear_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qclear_display,temp_2,Qclasses_which_define);
    Qexpression_cell_updated_for_meter = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_meter,
	    STATIC_FUNCTION(expression_cell_updated_for_meter,NIL,FALSE,5,5));
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_meter);
    set_get(Qmeter,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    Qupdate_display_for_meter = STATIC_SYMBOL("UPDATE-DISPLAY-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_for_meter,
	    STATIC_FUNCTION(update_display_for_meter,NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_display_for_meter);
    set_get(Qmeter,Qupdate_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qupdate_display,temp_2,Qclasses_which_define);
    Qupdate_cell_based_display_for_meter = 
	    STATIC_SYMBOL("UPDATE-CELL-BASED-DISPLAY-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_cell_based_display_for_meter,
	    STATIC_FUNCTION(update_cell_based_display_for_meter,NIL,FALSE,
	    4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_cell_based_display_for_meter);
    set_get(Qmeter,Qupdate_cell_based_display,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_cell_based_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qupdate_cell_based_display,temp_2,
	    Qclasses_which_define);
    Qinitialize_for_meter = STATIC_SYMBOL("INITIALIZE-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_meter,
	    STATIC_FUNCTION(initialize_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_meter);
    set_get(Qmeter,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    string_constant_1 = 
	    STATIC_STRING("Attempting to display non-numeric values on a meter.");
    Qactivate_subclass_of_entity_for_meter = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_meter,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_meter,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_meter);
    set_get(Qmeter,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_meter = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_meter,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_meter,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_meter);
    set_get(Qmeter,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdraw_for_ruling_for_meter = STATIC_SYMBOL("DRAW-FOR-RULING-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_ruling_for_meter,
	    STATIC_FUNCTION(draw_for_ruling_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_ruling_for_meter);
    set_get(Qruling_for_meter,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qruling_for_meter,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qdraw_for_marker_for_meter = STATIC_SYMBOL("DRAW-FOR-MARKER-FOR-METER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_marker_for_meter,
	    STATIC_FUNCTION(draw_for_marker_for_meter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_marker_for_meter);
    set_get(Qmarker_for_meter,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qmarker_for_meter,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qitem,Qtable);
    check_if_superior_classes_are_defined(Qreadout_table,list_constant_7);
    string_constant_61 = STATIC_STRING("1m1m8v834Ty1l8t");
    string_constant_62 = 
	    STATIC_STRING("13Dy4z8r830dy830dy834Ty834Ty00001o1l83-4y1l8o1l8l1l83Hy000004z8r830ry830ry834Ty834Ty00001o1l83-4y1l8o1l8l1l83Hy000004z8r83=gy83=");
    string_constant_63 = 
	    STATIC_STRING("gy834Ty834Ty00001q1n8p831*y83Gy1l83-4y1l83Ey1l8l1l83-5y1m83Dy53UyExport numerical-expression-parse\?000004z8r835cy835cy834Ty834Ty");
    string_constant_64 = 
	    STATIC_STRING("00001o1n8p83-dy83Gy1l83Ey1l8l1m83Dy5zExport: string.000004z8r834*y834*y834Ty834Ty00001p1l8l1l8z1l83Ey1m8p83*Wy1m83Dy53JyExport t");
    string_constant_65 = 
	    STATIC_STRING("ext-format-name000004z8r830wy830wy834Ty834Ty00001o1l83-4y1l83Ey1l83Cy1l8l000004z8r830cy830cy834Ty834Ty00001n1l83-4y1l83Ey1l8l000");
    string_constant_66 = 
	    STATIC_STRING("004z8r8300y8300y834Ty834Ty0p001q1m8p83=Qy1l83-4y1l83Ey1l8l1l8z1m83Dy53Lyexport time interval part000004z8r830Hy830Hy834Ty834Ty0m");
    string_constant_67 = 
	    STATIC_STRING("001q1m8p83=Qy1l83-4y1l83Ey1l8l1l8z1m83Dy53Lyexport time interval part000004z8r830Gy830Gy834Ty834Ty0m001p1m8p83-Yy1l83-4y1l83Ey1l");
    string_constant_68 = 
	    STATIC_STRING("8l1l8z000004z8r83=Py83=Py834Ty834Ty00001q1m8p83Ky1l83-4y1l83Ey1l8l1l8z1m83Dy53eyExport and alias to show-simulated-values\? \?0000");
    string_constant_69 = 
	    STATIC_STRING("04z8r83Zty83Zty834Ty834Ty08k001o1m8p01l83-4y1l83Ey1l8l000004z8r830xy830xy834Ty834Ty00001n1l83-4y1l83Ey1l8l000004z8r830sy830sy834");
    string_constant_70 = 
	    STATIC_STRING("Ty834Ty00001o1l83-4y1l83Ey1l8l1m83Dy53*JyAssociated with callback and registration\? ~\n This and several other slots are repeated");
    string_constant_71 = 
	    STATIC_STRING(" in related classes. Should be in\n a multiple-inheritance mixin.000004z8r83JHy83JHy834Ty834Ty083Yay001l1l8l000004z8r8366y8366y83");
    string_constant_72 = 
	    STATIC_STRING("4Ty834Ty00001q1l83Fy1l83Hy1m8p83dmy1l83Ey1l8l1m83Dy53vyExport: currently in attribute tables. Not showing up in doc\?000004z8r83-");
    string_constant_73 = 
	    STATIC_STRING("py83-py834Ty834Ty00001q1l8l1l8z1l83Ey1l83Cy1m8p83-py1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-m");
    string_constant_74 = 
	    STATIC_STRING("essage-level: (or default &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]00000");
    string_constant_75 = 
	    STATIC_STRING("13Fy8q1o834Ty1m83Ry83*Jy1m8v834Ty8t1q830dy083-4y8o8l83Hy1q830ry083-4y8o8l83Hy1s83=gy01n8p831*y83Gy83-4y83Ey8l83-5y1m83Dy53UyExpo");
    string_constant_76 = 
	    STATIC_STRING("rt numerical-expression-parse\?1q835cy01n8p83-dy83Gy83Ey8l1m83Dy5zExport: string.1r834*y08l8z83Ey1m8p83*Wy1m83Dy53JyExport text-f");
    string_constant_77 = 
	    STATIC_STRING("ormat-name1q830wy083-4y83Ey83Cy8l1p830cy083-4y83Ey8l1s8300yp1m8p83=Qy83-4y83Ey8l8z1m83Dy53Lyexport time interval part1s830Hym1m8");
    string_constant_78 = 
	    STATIC_STRING("p83=Qy83-4y83Ey8l8z1m83Dy53Lyexport time interval part1r830Gym1m8p83-Yy83-4y83Ey8l8z1s83=Py01m8p83Ky83-4y83Ey8l8z1m83Dy53eyExpor");
    string_constant_79 = 
	    STATIC_STRING("t and alias to show-simulated-values\? \?1q83Zty8k1m8p083-4y83Ey8l1p830xy083-4y83Ey8l1q830sy083-4y83Ey8l1m83Dy53*JyAssociated with");
    string_constant_80 = 
	    STATIC_STRING(" callback and registration\? ~\n This and several other slots are repeated in related classes. Should be in\n a multiple-inheritanc");
    string_constant_81 = 
	    STATIC_STRING("e mixin.1m83JHy83Yay1s8366y083Fy83Hy1m8p83dmy83Ey8l1m83Dy53vyExport: currently in attribute tables. Not showing up in doc\?1r83-p");
    string_constant_82 = STATIC_STRING("y08l8z83Ey83Cy1m8p83-py");
    temp = regenerate_optimized_constant(string_constant_61);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69,string_constant_70,string_constant_71,
	    string_constant_72,string_constant_73,string_constant_74));
    add_class_to_environment(9,Qreadout_table,list_constant_7,Nil,temp,Nil,
	    temp_1,list_constant_7,regenerate_optimized_constant(list(8,
	    string_constant_75,string_constant_76,string_constant_77,
	    string_constant_78,string_constant_79,string_constant_80,
	    string_constant_81,string_constant_82)),Nil);
    Readout_table_class_description = 
	    lookup_global_or_kb_specific_property_value(Qreadout_table,
	    Class_description_gkbprop);
    alias_slot_name(3,Qexpressions_to_display,Qexpression_to_display,
	    Qreadout_table);
    Qformat_for_readout_table = STATIC_SYMBOL("FORMAT-FOR-READOUT-TABLE",
	    AB_package);
    Qdisplay_format = STATIC_SYMBOL("DISPLAY-FORMAT",AB_package);
    alias_slot_name(3,Qformat_for_readout_table,Qdisplay_format,
	    Qreadout_table);
    Qreadout_table_format = STATIC_SYMBOL("READOUT-TABLE-FORMAT",AB_package);
    string_constant_83 = 
	    STATIC_STRING("1x83*ny8308yl830Ayl8309yl8307yl83=Dyl83=Nyl");
    mutate_global_property(Qreadout_table_format,
	    regenerate_optimized_constant(string_constant_83),
	    Qformat_description);
    Qspot_generator_for_readout_table_format = 
	    STATIC_SYMBOL("SPOT-GENERATOR-FOR-READOUT-TABLE-FORMAT",
	    AB_package);
    Qtable_format_spot_generator = 
	    STATIC_SYMBOL("TABLE-FORMAT-SPOT-GENERATOR",AB_package);
    mutate_global_property(Qreadout_table_format,
	    Qspot_generator_for_readout_table_format,
	    Qtable_format_spot_generator);
    SET_SYMBOL_FUNCTION(Qspot_generator_for_readout_table_format,
	    STATIC_FUNCTION(spot_generator_for_readout_table_format,NIL,
	    FALSE,2,2));
    Qreadout_table_text_cell_format = 
	    STATIC_SYMBOL("READOUT-TABLE-TEXT-CELL-FORMAT",AB_package);
    string_constant_84 = 
	    STATIC_STRING("1z83-Qy83kyk83-=y3Ey83iy30ey83byq83ayo83Wyq83cyo");
    mutate_global_property(Qreadout_table_text_cell_format,
	    regenerate_optimized_constant(string_constant_84),
	    Qformat_description);
    Qdefault_readout_table_format_name = 
	    STATIC_SYMBOL("DEFAULT-READOUT-TABLE-FORMAT-NAME",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qreadout_table_display_value = 
	    STATIC_SYMBOL("READOUT-TABLE-DISPLAY-VALUE",AB_package);
    Qexpression_cell_updated_for_readout_table = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_readout_table,
	    STATIC_FUNCTION(expression_cell_updated_for_readout_table,NIL,
	    FALSE,5,5));
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_readout_table);
    set_get(Qreadout_table,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    Qupdate_display_for_readout_table = 
	    STATIC_SYMBOL("UPDATE-DISPLAY-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_for_readout_table,
	    STATIC_FUNCTION(update_display_for_readout_table,NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_display_for_readout_table);
    set_get(Qreadout_table,Qupdate_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qupdate_display,temp_2,Qclasses_which_define);
    Qupdate_cell_based_display_for_readout_table = 
	    STATIC_SYMBOL("UPDATE-CELL-BASED-DISPLAY-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_cell_based_display_for_readout_table,
	    STATIC_FUNCTION(update_cell_based_display_for_readout_table,
	    NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_cell_based_display_for_readout_table);
    set_get(Qreadout_table,Qupdate_cell_based_display,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_cell_based_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qupdate_cell_based_display,temp_2,
	    Qclasses_which_define);
    Qinitialize_for_readout_table = 
	    STATIC_SYMBOL("INITIALIZE-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_readout_table,
	    STATIC_FUNCTION(initialize_for_readout_table,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_readout_table);
    set_get(Qreadout_table,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qclear_display_for_readout_table = 
	    STATIC_SYMBOL("CLEAR-DISPLAY-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_display_for_readout_table,
	    STATIC_FUNCTION(clear_display_for_readout_table,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qclear_display_for_readout_table);
    set_get(Qreadout_table,Qclear_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclear_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qclear_display,temp_2,Qclasses_which_define);
    Qactivate_for_readout_table = 
	    STATIC_SYMBOL("ACTIVATE-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_readout_table,
	    STATIC_FUNCTION(activate_for_readout_table,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_readout_table);
    set_get(Qreadout_table,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qdeactivate_for_readout_table = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-READOUT-TABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_readout_table,
	    STATIC_FUNCTION(deactivate_for_readout_table,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_readout_table);
    set_get(Qreadout_table,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_readout_table = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_readout_table,
	    STATIC_FUNCTION(initialize_after_reading_for_readout_table,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_readout_table);
    set_get(Qreadout_table,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qdigital_clock = STATIC_SYMBOL("DIGITAL-CLOCK",AB_package);
    list_constant_8 = STATIC_CONS(Qreadout_table,Qnil);
    check_if_superior_classes_are_defined(Qdigital_clock,list_constant_8);
    string_constant_85 = STATIC_STRING("1m1m8v836ly1l8t");
    string_constant_86 = 
	    STATIC_STRING("1p4z8r83=gy83=gy836ly836ly00001r1l83Ny1l83Ey1l8l1n8p831*y83Gy1l83-4y1l83-5y1m83Dy53UyExport numerical-expression-parse\?000004z8r");
    string_constant_87 = 
	    STATIC_STRING("834*y834*y836ly836ly02lno001q1l83Ny1l8l1l83Ey1l8z1m8p83*Wy1m83Dy53JyExport text-format-name000004z8r83=Py83=Py836ly836ly00001r1l");
    string_constant_88 = 
	    STATIC_STRING("83Ny1l83-4y1l83Ey1l8l1l8z1m8p83Ky1m83Dy53eyExport and alias to show-simulated-values\? \?000004z8r8366y8366y836ly836ly00001q1l83Fy");
    string_constant_89 = 
	    STATIC_STRING("1l83Hy1m8p83dly1l83Ey1l8l1m83Dy53vyExport: currently in attribute tables. Not showing up in doc\?000004z8r83-py83-py836ly836ly000");
    string_constant_90 = 
	    STATIC_STRING("01r1l8l1l83Ey1l8z1l83Ny1l83Cy1m8p83-py1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: ");
    string_constant_91 = 
	    STATIC_STRING("(or default &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]00000");
    string_constant_92 = 
	    STATIC_STRING("1r8q1o836ly1l834Ty1m8v836ly8t1p83=gy083Ny83Ey8l1q834*y2lno83Ny8l83Ey8z1r83=Py083Ny83-4y83Ey8l8z1r8366y083Fy83Hy1m8p83dly83Ey8l1q");
    string_constant_93 = STATIC_STRING("83-py08l83Ey8z83Ny");
    temp = regenerate_optimized_constant(string_constant_85);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_86,
	    string_constant_87,string_constant_88,string_constant_89,
	    string_constant_90,string_constant_91));
    add_class_to_environment(9,Qdigital_clock,list_constant_8,Nil,temp,Nil,
	    temp_1,list_constant_8,
	    regenerate_optimized_constant(LIST_2(string_constant_92,
	    string_constant_93)),Nil);
    Digital_clock_class_description = 
	    lookup_global_or_kb_specific_property_value(Qdigital_clock,
	    Class_description_gkbprop);
    Qdisplay_up_to_date_qm = STATIC_SYMBOL("DISPLAY-UP-TO-DATE\?",AB_package);
    Qupdate_display_for_digital_clock = 
	    STATIC_SYMBOL("UPDATE-DISPLAY-FOR-DIGITAL-CLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_for_digital_clock,
	    STATIC_FUNCTION(update_display_for_digital_clock,NIL,FALSE,4,4));
    temp_2 = SYMBOL_FUNCTION(Qupdate_display_for_digital_clock);
    set_get(Qdigital_clock,Qupdate_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qdigital_clock,temp);
    mutate_global_property(Qupdate_display,temp_2,Qclasses_which_define);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    float_constant_2 = STATIC_FLOAT(-1.0);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qactivate_for_digital_clock = 
	    STATIC_SYMBOL("ACTIVATE-FOR-DIGITAL-CLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_digital_clock,
	    STATIC_FUNCTION(activate_for_digital_clock,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_digital_clock);
    set_get(Qdigital_clock,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qdigital_clock,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qthings_this_display_is_interested_in = 
	    STATIC_SYMBOL("THINGS-THIS-DISPLAY-IS-INTERESTED-IN",AB_package);
    Qdeactivate_for_digital_clock = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-DIGITAL-CLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_digital_clock,
	    STATIC_FUNCTION(deactivate_for_digital_clock,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_digital_clock);
    set_get(Qdigital_clock,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qdigital_clock,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qclear_display_for_digital_clock = 
	    STATIC_SYMBOL("CLEAR-DISPLAY-FOR-DIGITAL-CLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_display_for_digital_clock,
	    STATIC_FUNCTION(clear_display_for_digital_clock,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qclear_display_for_digital_clock);
    set_get(Qdigital_clock,Qclear_display,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclear_display),
	    Qclasses_which_define);
    temp_2 = CONS(Qdigital_clock,temp);
    mutate_global_property(Qclear_display,temp_2,Qclasses_which_define);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
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
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_2 = STATIC_STRING(" of ");
    Qdenote_cell_array_element_for_dial = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-DIAL",AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_dial,
	    STATIC_FUNCTION(denote_cell_array_element_for_dial,NIL,FALSE,3,3));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_dial);
    set_get(Qdial,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qdial,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qdenote_cell_array_element_for_meter = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-METER",AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_meter,
	    STATIC_FUNCTION(denote_cell_array_element_for_meter,NIL,FALSE,
	    3,3));
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_meter);
    set_get(Qmeter,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qmeter,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qdenote_cell_array_element_for_readout_table = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-READOUT-TABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_readout_table,
	    STATIC_FUNCTION(denote_cell_array_element_for_readout_table,
	    NIL,FALSE,3,3));
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_readout_table);
    set_get(Qreadout_table,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qreadout_table,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qcomputation_style_scan_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-SCAN-INTERVAL",AB_package);
    Qcomputation_style_initial_scan_wait_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-INITIAL-SCAN-WAIT-INTERVAL",
	    AB_package);
    Qcomputation_style_priority = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-PRIORITY",AB_package);
    Qcomputation_style_value_domain = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-VALUE-DOMAIN",AB_package);
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qcomputation_style_tracing_and_breakpoints = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qupdate_display_if_not_reprocessed = 
	    STATIC_SYMBOL("UPDATE-DISPLAY-IF-NOT-REPROCESSED",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_if_not_reprocessed,
	    STATIC_FUNCTION(update_display_if_not_reprocessed,NIL,FALSE,2,2));
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_inference_background_collection_g2_struct 
	    = STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    string_constant_3 = 
	    STATIC_STRING("G2 INTERNAL BUG, a wake up sent to ~a from ~NF.  Please inform ~\n          Gensym Software Support of this G2 wake up bug!");
    Qinstall_event_detector = STATIC_SYMBOL("INSTALL-EVENT-DETECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_event_detector,
	    STATIC_FUNCTION(install_event_detector,NIL,FALSE,4,4));
    Qclear_event_detectors = STATIC_SYMBOL("CLEAR-EVENT-DETECTORS",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_event_detectors,
	    STATIC_FUNCTION(clear_event_detectors,NIL,FALSE,1,1));
}
