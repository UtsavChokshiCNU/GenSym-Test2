/* icons4.c
 * Input file:  icons4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "icons4.h"


/* RECOMPUTE-VIEW-PAD-SIZE */
Object recompute_view_pad_size(icon_editor)
    Object icon_editor;
{
    Object view_pad, workspace, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;

    x_note_fn_call(235,0);
    view_pad = ISVREF(icon_editor,(SI_Long)12L);
    workspace = ISVREF(icon_editor,(SI_Long)4L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)5L));
    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
    ISVREF(view_pad,(SI_Long)7L) = FIX(svref_new_value);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = IFIX(ISVREF(view_pad,(SI_Long)6L));
    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
    return VALUES_1(ISVREF(view_pad,(SI_Long)8L) = FIX(svref_new_value));
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "The maximum icon width in the icon editor is ~a." */

static Object string_constant_1;   /* "The maximum icon height in the icon editor is ~a." */

/* CHANGE-SIZE-OF-ICON-IN-ICON-EDITOR */
Object change_size_of_icon_in_icon_editor(icon_editor,width,height)
    Object icon_editor, width, height;
{
    Object engine, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, new_width, new_height;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(235,1);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    if (IFIX(width) > (SI_Long)500L || IFIX(height) > (SI_Long)500L) {
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
		  if (IFIX(width) > (SI_Long)500L)
		      tformat(2,string_constant,FIX((SI_Long)500L));
		  else
		      tformat(2,string_constant_1,FIX((SI_Long)500L));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),temp,Nil);
	new_width = IFIX(width) > (SI_Long)500L ? FIX((SI_Long)500L) : width;
	new_height = IFIX(height) > (SI_Long)500L ? FIX((SI_Long)500L) : 
		height;
	enqueue_icon_editor_translator_event(icon_editor,FIX((SI_Long)20L),
		new_width,new_height);
	SVREF(engine,FIX((SI_Long)1L)) = new_width;
	return VALUES_1(SVREF(engine,FIX((SI_Long)2L)) = new_height);
    }
    else {
	SVREF(engine,FIX((SI_Long)1L)) = width;
	return VALUES_1(SVREF(engine,FIX((SI_Long)2L)) = height);
    }
}

/* SET-MAIN-COLOR-IN-ICON-EDITOR */
Object set_main_color_in_icon_editor(icon_editor,new_color)
    Object icon_editor, new_color;
{
    Object engine, current_region_qm, first_arg, temp;

    x_note_fn_call(235,2);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    current_region_qm = ISVREF(engine,(SI_Long)10L);
    if ( !TRUEP(current_region_qm)) {
	first_arg = ISVREF(engine,(SI_Long)6L);
	M_FIRST(first_arg) = new_color;
    }
    set_color_of_region_in_icon_editor(icon_editor,ISVREF(engine,
	    (SI_Long)11L),Nil);
    temp = current_region_qm;
    if (temp);
    else
	temp = new_color;
    set_color_of_region_in_icon_editor(icon_editor,temp,new_color);
    temp = ISVREF(engine,(SI_Long)6L);
    temp = CDDR(temp);
    if (CAR(temp))
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)26L),
		current_region_qm,new_color);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)31L),
	    ISVREF(engine,(SI_Long)10L),new_color);
    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)7L),new_color,
	    Nil);
    return VALUES_1(SVREF(engine,FIX((SI_Long)11L)) = new_color);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object string_constant_2;   /* "Note that there is currently no image named ~a" */

static Object string_constant_3;   /* "Note that the image ~a is currently incomplete" */

static Object Qvariables;          /* variables */

static Object Qimage;              /* image */

/* SET-MAIN-IMAGE-IN-ICON-EDITOR */
Object set_main_image_in_icon_editor(icon_editor,new_image)
    Object icon_editor, new_image;
{
    Object engine, workspace, changed_qm, new_image_name_qm;
    Object new_image_definition_qm, temp, variables, fixed_variables;
    Object fixed_element, new_variables, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, temp_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object layer, sublist, drawing_element, old_image_place, old_image;
    Object icon_editor_engine, new_drawing_element, drawing_elements;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long temp_3, bv16_length, aref_new_value, length_1;
    char temp_4;
    Declare_special(6);
    Object result;

    x_note_fn_call(235,3);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    workspace = ISVREF(icon_editor,(SI_Long)4L);
    changed_qm = Nil;
    new_image_name_qm = new_image ? SECOND(new_image) : Qnil;
    new_image_definition_qm = new_image_name_qm ? 
	    find_image_named(new_image_name_qm) : Qnil;
    temp = ISVREF(icon_editor,(SI_Long)7L);
    variables = CDR(temp);
    fixed_variables = Nil;
    fixed_element = Nil;
    new_variables = Nil;
    result = fix_up_drawing_element_for_icon_editor(new_image,variables);
    MVS_3(result,fixed_element,fixed_variables,new_variables);
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(workspace,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_stack_change_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_stack_change_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(workspace,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    temp_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,temp_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = workspace;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp_1 = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp_1;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    5);
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(workspace,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  temp_3 = IFIX(ISVREF(workspace,(SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(temp_3);
      }
      if (new_image_name_qm &&  !TRUEP(new_image_definition_qm)) {
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    temp_3 = bv16_length - (SI_Long)2L;
	    aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_3,aref_new_value);
	    temp_3 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_3,aref_new_value);
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(2,string_constant_2,new_image_name_qm);
		    temp = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		  temp,Nil);
      }
      else if (new_image_definition_qm && 
	      frame_incomplete_p(new_image_definition_qm)) {
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    temp_3 = bv16_length - (SI_Long)2L;
	    aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_3,aref_new_value);
	    temp_3 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,temp_3,aref_new_value);
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(2,string_constant_3,new_image_name_qm);
		    temp = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		  temp,Nil);
      }
      else
	  handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		  ISVREF(ISVREF(icon_editor,(SI_Long)10L),(SI_Long)1L),Nil);
      if ( !EQ(fixed_variables,Qerror)) {
	  if (new_variables) {
	      fixed_variables = icon_editor_cons_1(Qvariables,fixed_variables);
	      SVREF(icon_editor,FIX((SI_Long)7L)) = fixed_variables;
	      inform_user_of_new_variables_for_icon_editor(icon_editor,
		      new_variables);
	      reclaim_gensym_tree_1(new_variables);
	      reclaim_gensym_tree_1(variables);
	  }
	  layer = ISVREF(engine,(SI_Long)6L);
	  temp = CDDR(layer);
	  sublist = CAR(temp);
	next_loop:
	  if ( !TRUEP(sublist))
	      goto end_loop;
	  drawing_element = CAR(sublist);
	  if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qimage)) {
	      old_image_place = sublist;
	      goto end_1;
	  }
	  sublist = M_CDR(sublist);
	  goto next_loop;
	end_loop:
	  old_image_place = Qnil;
	end_1:;
	  old_image = CAR(old_image_place);
	  if (EQUAL(old_image,new_image))
	      changed_qm = Nil;
	  else if ( !TRUEP(old_image)) {
	      icon_editor_engine = engine;
	      new_drawing_element = 
		      copy_tree_using_icon_editor_conses_1(new_image);
	      layer = ISVREF(icon_editor_engine,(SI_Long)6L);
	      temp = CDDR(layer);
	      drawing_elements = CAR(temp);
	      reclaim_icon_editor_slot_value(SECOND(layer));
	      M_SECOND(layer) = Nil;
	      gensymed_symbol = new_drawing_element;
	      gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	      if (drawing_elements) {
		  temp = CDDDR(layer);
		  if ( !TRUEP(CAR(temp))) {
		      temp_1 = CDDDR(layer);
		      temp_2 = last(drawing_elements,_);
		      M_CAR(temp_1) = temp_2;
		  }
		  temp = CDDDR(layer);
		  temp_1 = CAR(temp);
		  M_CDR(temp_1) = gensymed_symbol;
	      }
	      else
		  drawing_elements = gensymed_symbol;
	      temp_1 = CDDDR(layer);
	      M_CAR(temp_1) = gensymed_symbol;
	      temp_1 = CDDR(layer);
	      M_CAR(temp_1) = drawing_elements;
	      changed_qm = T;
	  }
	  else if (new_image) {
	      changed_qm = copy_tree_using_icon_editor_conses_1(new_image);
	      M_CAR(old_image_place) = changed_qm;
	  }
	  else {
	      temp_1 = CDDR(layer);
	      temp = CDDR(layer);
	      temp_2 = delete_icon_editor_element_1(old_image,CAR(temp));
	      M_CAR(temp_1) = temp_2;
	      temp_1 = CDDDR(layer);
	      temp = CDDR(layer);
	      temp_2 = last(CAR(temp),_);
	      M_CAR(temp_1) = temp_2;
	      changed_qm = T;
	  }
	  if (Nil)
	      reclaim_icon_editor_slot_value(ISVREF(engine,(SI_Long)14L));
	  temp_1 = copy_tree_using_icon_editor_conses_1(new_image);
	  SVREF(engine,FIX((SI_Long)14L)) = temp_1;
      }
      result_1 = changed_qm;
      if ( !TRUEP(current_flag_state_qm)) {
	  temp_3 = IFIX(ISVREF(workspace,(SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(temp_3);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_4 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_4);
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
	  temp_4 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_4);
	  else {
	      temp = M_CDR(frame_and_slot_or_atom);
	      temp_4 = CONSP(temp) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_4 ? (EQ(workspace,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_4 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_4 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_4 = TRUEP(Nil);
      if ( !temp_4)
	  update_all_representations_of_slot(workspace,slot_description,
		  Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(workspace);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_1 = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp_1) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	  }
	  else {
	      temp_1 = Available_stack_change_conses_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp = M_CAR(Stack_of_slot_value_changes);
	  temp_4 = ATOM(temp);
      }
      else
	  temp_4 = TRUEP(Nil);
      if (temp_4 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(result_1);
}

static Object Qtext;               /* text */

static Object string_constant_4;   /* "undefined-text" */

static Object Qlarge;              /* large */

/* DEFAULT-VALUE-FOR-VARIABLE */
Object default_value_for_variable(variable_name,drawing_element)
    Object variable_name, drawing_element;
{
    x_note_fn_call(235,4);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qtext)) {
	if (EQ(variable_name,CADR(drawing_element)))
	    return stringw(string_constant_4);
	else if (EQ(variable_name,FOURTH(drawing_element)))
	    return VALUES_1(Qlarge);
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
    else if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qimage))
	return VALUES_1(FIX((SI_Long)0L));
    else
	return VALUES_1(Qnil);
}

static Object array_constant;      /* # */

/* FIX-UP-DRAWING-ELEMENT-FOR-ICON-EDITOR */
Object fix_up_drawing_element_for_icon_editor(drawing_element,variables)
    Object drawing_element, variables;
{
    Object new_variables, current_variables, current_error, bad_variable_name;
    Object bad_variable_reason_qm, default_value;

    x_note_fn_call(235,5);
    new_variables = Nil;
    current_variables = 
	    copy_tree_including_leaves_using_gensym_conses(variables);
    current_error = Nil;
    bad_variable_name = Nil;
    bad_variable_reason_qm = Nil;
  next_loop:
    current_error = element_contains_bad_variable_qm(drawing_element,
	    current_variables);
    bad_variable_name = SECOND(current_error);
    bad_variable_reason_qm = CAR(current_error);
    if ( !TRUEP(current_error))
	goto end_loop;
    if (string_eq_w(bad_variable_reason_qm,array_constant) &&  
	    !TRUEP(memq_function(bad_variable_name,
	    Reserved_icon_variable_names))) {
	default_value = default_value_for_variable(bad_variable_name,
		drawing_element);
	current_variables = gensym_cons_1(default_value,current_variables);
	current_variables = gensym_cons_1(bad_variable_name,current_variables);
	new_variables = gensym_cons_1(copy_for_slot_value(default_value),
		new_variables);
	new_variables = gensym_cons_1(bad_variable_name,new_variables);
    }
    else
	return VALUES_2(drawing_element,Qerror);
    goto next_loop;
  end_loop:
    return VALUES_3(drawing_element,current_variables,new_variables);
    return VALUES_1(Qnil);
}

static Object array_constant_1;    /* # */

static Object string_constant_5;   /* "s:  " */

static Object string_constant_6;   /* ":  " */

static Object array_constant_2;    /* # */

/* INFORM-USER-OF-NEW-VARIABLES-FOR-ICON-EDITOR */
Object inform_user_of_new_variables_for_icon_editor(icon_editor,new_variables)
    Object icon_editor, new_variables;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object name, value, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(235,6);
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
	      twrite_beginning_of_wide_string(array_constant_1,
		      FIX((SI_Long)22L));
	      twrite_general_string(IFIX(length(new_variables)) > 
		      (SI_Long)2L ? string_constant_5 : string_constant_6);
	      name = Nil;
	      value = Nil;
	      ab_loop_list_ = new_variables;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	    next_loop:
	      name = CAR(ab_loop_list_);
	      temp = CDR(ab_loop_list_);
	      value = CAR(temp);
	      write_variable_name_and_value(name,value);
	      twrite_beginning_of_wide_string(array_constant_2,
		      FIX((SI_Long)2L));
	      ab_loop_list_ = CDDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      goto next_loop;
	    end_loop:;
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
	    temp,Nil);
}

static Object Qicon_editor_table_info_frame_icon_editor;  /* icon-editor-table-info-frame-icon-editor */

/* REJECT-BAD-VARIABLES */
Object reject_bad_variables(parse_result,table_info_frame)
    Object parse_result, table_info_frame;
{
    Object icon_editor, temp, variables, bad_variable, reason_for_rejection;
    Object reject_undefined_variables, variable_name, variable_value_qm;

    x_note_fn_call(235,7);
    icon_editor = get_lookup_slot_value_given_default(table_info_frame,
	    Qicon_editor_table_info_frame_icon_editor,Nil);
    temp = ISVREF(icon_editor,(SI_Long)7L);
    variables = CDR(temp);
    bad_variable = element_contains_bad_variable_qm(parse_result,variables);
    reason_for_rejection = FIRST(bad_variable);
    reject_undefined_variables = Nil;
    if (bad_variable && reason_for_rejection && 
	    (reject_undefined_variables ||  
	    !TRUEP(string_eq_w(reason_for_rejection,array_constant)))) {
	variable_name = SECOND(bad_variable);
	variable_value_qm = getfq_function_no_default(variables,variable_name);
	return bad_variable_in_element_message(parse_result,variable_name,
		variable_value_qm,reason_for_rejection);
    }
    else if (memq_function(SECOND(bad_variable),Reserved_icon_variable_names))
	return reserved_icon_variable_message(SECOND(bad_variable));
    else
	return VALUES_1(parse_result);
}

static Object Qpolychrome;         /* polychrome */

/* CHECK-ICON-DESCRIPTION-FOR-IMAGES-NAMED */
Object check_icon_description_for_images_named(names,icon_description)
    Object names, icon_description;
{
    Object line_drawing_description, first_element, polychrome_header_qm;
    Object variable_header_qm, background_header_qm, stipple_qm, header_count;
    Object description_elements, description_element, ab_loop_list_;
    Object ab_loop_it_;

    x_note_fn_call(235,8);
    line_drawing_description = CDDR(icon_description);
    first_element = CAR(line_drawing_description);
    polychrome_header_qm = CONSP(first_element) && EQ(CAR(first_element),
	    Qpolychrome) ? first_element : Nil;
    variable_header_qm = 
	    get_variable_specification_if_any(line_drawing_description);
    background_header_qm = 
	    get_icon_background_layer_if_any(line_drawing_description);
    stipple_qm = get_icon_stipple_if_any(line_drawing_description);
    header_count = FIX((SI_Long)0L);
    if (polychrome_header_qm)
	header_count = FIXNUM_ADD1(header_count);
    if (variable_header_qm)
	header_count = FIXNUM_ADD1(header_count);
    if (background_header_qm)
	header_count = FIXNUM_ADD1(header_count);
    if (stipple_qm)
	header_count = FIXNUM_ADD1(header_count);
    description_elements = nthcdr(header_count,line_drawing_description);
    description_element = Nil;
    ab_loop_list_ = description_elements;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = CONSP(description_element) && 
	    EQ(FIRST(description_element),Qimage) && 
	    memq_function(SECOND(description_element),names) ? 
	    description_element : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* POINT-EXPRESSION-VARIABLES */
Object point_expression_variables(point_expression)
    Object point_expression;
{
    Object point_list_1, point_list_2;

    x_note_fn_call(235,9);
    if (INTEGERP(point_expression))
	return VALUES_1(Nil);
    else if (EQ(point_expression,Qplus) || EQ(point_expression,Qminus))
	return VALUES_1(Nil);
    else if ( !TRUEP(point_expression))
	return VALUES_1(Nil);
    else if (SYMBOLP(point_expression))
	return gensym_cons_1(point_expression,Nil);
    else if (CONSP(point_expression)) {
	point_list_1 = point_expression_variables(CAR(point_expression));
	point_list_2 = point_expression_variables(CDR(point_expression));
	if ( !TRUEP(point_list_1))
	    return VALUES_1(point_list_2);
	else if ( !TRUEP(point_list_2))
	    return VALUES_1(point_list_1);
	else
	    return VALUES_1(nconc2(point_list_1,point_list_2));
    }
    else
	return VALUES_1(Qnil);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* COMPILE-IMAGE-SPECIFICATION?-FOR-SLOT */
Object compile_image_specification_qm_for_slot varargs_1(int, n)
{
    Object parse_result, table_info_frame, gensymed_symbol;
    Object point, temp, variable_names, icon_editor, icon_description_qm;
    Object conflicting_image_drawing_element_qm, error_string_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(235,10);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    table_info_frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    point = THIRD(parse_result);
    if (point) {
	temp = point_expression_variables(CAR(point));
	variable_names = nconc2(temp,point_expression_variables(CADR(point)));
    }
    else
	variable_names = Nil;
    if (variable_names) {
	icon_editor = get_lookup_slot_value_given_default(table_info_frame,
		Qicon_editor_table_info_frame_icon_editor,Nil);
	icon_description_qm = 
		extract_icon_description_from_icon_editor(icon_editor);
	conflicting_image_drawing_element_qm = icon_description_qm ? 
		check_icon_description_for_images_named(variable_names,
		icon_description_qm) : Qnil;
	error_string_qm = conflicting_image_drawing_element_qm ? 
		bad_variable_in_element_message_string(conflicting_image_drawing_element_qm,
		array_constant_3,
		SECOND(conflicting_image_drawing_element_qm),
		FIX((SI_Long)0L),array_constant_4) : Qnil;
	if (icon_description_qm)
	    reclaim_slot_value(icon_description_qm);
	reclaim_gensym_list_1(variable_names);
	if (error_string_qm)
	    return VALUES_2(Bad_phrase,error_string_qm);
    }
    return reject_bad_variables(parse_result,table_info_frame);
}

static Object array_constant_5;    /* # */

/* COMPILE-TEXT-SPECIFICATION?-FOR-SLOT */
Object compile_text_specification_qm_for_slot varargs_1(int, n)
{
    Object parse_result, table_info_frame, gensymed_symbol;
    Object label, point, x, y, temp, variable_names, icon_editor;
    Object icon_description_qm, conflicting_image_drawing_element_qm;
    Object image_name_qm, new_variable_value_qm, error_string_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(235,11);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    table_info_frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    label = CADR(parse_result);
    point = THIRD(parse_result);
    x = CAR(point);
    y = CADR(point);
    temp = point_expression_variables(x);
    variable_names = nconc2(temp,point_expression_variables(y));
    if (SYMBOLP(label))
	variable_names = gensym_cons_1(label,variable_names);
    if (variable_names) {
	icon_editor = get_lookup_slot_value_given_default(table_info_frame,
		Qicon_editor_table_info_frame_icon_editor,Nil);
	icon_description_qm = 
		extract_icon_description_from_icon_editor(icon_editor);
	conflicting_image_drawing_element_qm = 
		check_icon_description_for_images_named(variable_names,
		icon_description_qm);
	image_name_qm = conflicting_image_drawing_element_qm ? 
		SECOND(conflicting_image_drawing_element_qm) : Qnil;
	new_variable_value_qm = conflicting_image_drawing_element_qm ? 
		(EQ(label,image_name_qm) ? array_constant_5 : 
		FIX((SI_Long)0L)) : Qnil;
	error_string_qm = conflicting_image_drawing_element_qm ? 
		bad_variable_in_element_message_string(conflicting_image_drawing_element_qm,
		array_constant_3,image_name_qm,new_variable_value_qm,
		array_constant_4) : Qnil;
	if (icon_description_qm)
	    reclaim_slot_value(icon_description_qm);
	reclaim_gensym_list_1(variable_names);
	if (error_string_qm)
	    return VALUES_2(Bad_phrase,error_string_qm);
    }
    return reject_bad_variables(parse_result,table_info_frame);
}

/* SET-TEXT-IN-ICON-EDITOR */
Object set_text_in_icon_editor(icon_editor,text)
    Object icon_editor, text;
{
    Object engine, workspace, changed_qm, temp, variables, fixed_variables;
    Object fixed_element, new_variables, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, temp_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, layer, sublist;
    Object drawing_element, old_text_place, old_text, icon_editor_engine;
    Object new_drawing_element, drawing_elements, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value_1;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(235,12);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    workspace = ISVREF(icon_editor,(SI_Long)4L);
    changed_qm = Nil;
    temp = ISVREF(icon_editor,(SI_Long)7L);
    variables = CDR(temp);
    fixed_variables = Nil;
    fixed_element = Nil;
    new_variables = Nil;
    result = fix_up_drawing_element_for_icon_editor(text,variables);
    MVS_3(result,fixed_element,fixed_variables,new_variables);
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(workspace,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_stack_change_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_stack_change_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(workspace,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    temp_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,temp_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = workspace;
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
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(workspace,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (T)
	  handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		  ISVREF(ISVREF(icon_editor,(SI_Long)10L),(SI_Long)1L),Nil);
      if ( !EQ(fixed_variables,Qerror)) {
	  if (new_variables) {
	      fixed_variables = icon_editor_cons_1(Qvariables,fixed_variables);
	      SVREF(icon_editor,FIX((SI_Long)7L)) = fixed_variables;
	      inform_user_of_new_variables_for_icon_editor(icon_editor,
		      new_variables);
	      reclaim_gensym_tree_1(new_variables);
	      reclaim_gensym_tree_1(variables);
	  }
	  layer = ISVREF(engine,(SI_Long)6L);
	  temp = CDDR(layer);
	  sublist = CAR(temp);
	next_loop:
	  if ( !TRUEP(sublist))
	      goto end_loop;
	  drawing_element = CAR(sublist);
	  if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qtext)) {
	      old_text_place = sublist;
	      goto end_1;
	  }
	  sublist = M_CDR(sublist);
	  goto next_loop;
	end_loop:
	  old_text_place = Qnil;
	end_1:;
	  old_text = CAR(old_text_place);
	  if (EQUAL(old_text,text))
	      changed_qm = Nil;
	  else if ( !TRUEP(old_text)) {
	      icon_editor_engine = engine;
	      new_drawing_element = 
		      copy_drawing_element_with_icon_editor_conses(text,
		      Nil,Nil);
	      layer = ISVREF(icon_editor_engine,(SI_Long)6L);
	      temp = CDDR(layer);
	      drawing_elements = CAR(temp);
	      reclaim_icon_editor_slot_value(SECOND(layer));
	      M_SECOND(layer) = Nil;
	      gensymed_symbol = new_drawing_element;
	      gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
	      if (drawing_elements) {
		  temp = CDDDR(layer);
		  if ( !TRUEP(CAR(temp))) {
		      temp_1 = CDDDR(layer);
		      temp_2 = last(drawing_elements,_);
		      M_CAR(temp_1) = temp_2;
		  }
		  temp = CDDDR(layer);
		  temp_1 = CAR(temp);
		  M_CDR(temp_1) = gensymed_symbol;
	      }
	      else
		  drawing_elements = gensymed_symbol;
	      temp_1 = CDDDR(layer);
	      M_CAR(temp_1) = gensymed_symbol;
	      temp_1 = CDDR(layer);
	      M_CAR(temp_1) = drawing_elements;
	      changed_qm = T;
	  }
	  else if (text) {
	      temp_1 = copy_drawing_element_with_icon_editor_conses(text,
		      Nil,Nil);
	      M_CAR(old_text_place) = temp_1;
	      reclaim_icon_editor_slot_value(old_text);
	      changed_qm = T;
	  }
	  else {
	      temp_1 = CDDR(layer);
	      temp = CDDR(layer);
	      temp_2 = delete_icon_editor_element_1(old_text,CAR(temp));
	      M_CAR(temp_1) = temp_2;
	      temp_1 = CDDDR(layer);
	      temp = CDDR(layer);
	      temp_2 = last(CAR(temp),_);
	      M_CAR(temp_1) = temp_2;
	      changed_qm = T;
	  }
	  if (ISVREF(engine,(SI_Long)15L))
	      reclaim_icon_editor_slot_value(ISVREF(engine,(SI_Long)15L));
	  temp_1 = copy_drawing_element_with_icon_editor_conses(text,Nil,Nil);
	  SVREF(engine,FIX((SI_Long)15L)) = temp_1;
      }
      result_1 = changed_qm;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = workspace;
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
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_1;
	  temp_3 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_3);
	  else {
	      temp = M_CDR(frame_and_slot_or_atom);
	      temp_3 = CONSP(temp) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_3 ? (EQ(workspace,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_3 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_3 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_3 = TRUEP(Nil);
      if ( !temp_3)
	  update_all_representations_of_slot(workspace,slot_description,
		  Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(workspace);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_1 = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp_1) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	  }
	  else {
	      temp_1 = Available_stack_change_conses_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      temp_2 = Current_thread_index;
	      SVREF(temp_1,temp_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp = M_CAR(Stack_of_slot_value_changes);
	  temp_3 = ATOM(temp);
      }
      else
	  temp_3 = TRUEP(Nil);
      if (temp_3 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(result_1);
}

static Object Qlight_stipple;      /* light-stipple */

static Object Qmedium_stipple;     /* medium-stipple */

static Object Qdark_stipple;       /* dark-stipple */

static Object Qlight_texture;      /* light-texture */

static Object Qmedium_texture;     /* medium-texture */

static Object Qdark_texture;       /* dark-texture */

/* SET-STIPPLE-IN-ICON-EDITOR */
Object set_stipple_in_icon_editor varargs_1(int, n)
{
    Object icon_editor, stipple_spec;
    Object global_p, temp, engine, workspace, changed_qm, temp_1, variables;
    Object fixed_variables, fixed_element, new_variables, result_1;
    Object current_flag_state_qm, slot_description, new_cons, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(235,13);
    INIT_ARGS_nonrelocating();
    icon_editor = REQUIRED_ARG_nonrelocating();
    stipple_spec = REQUIRED_ARG_nonrelocating();
    global_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (global_p) {
	if (EQ(stipple_spec,Qnil) || EQ(stipple_spec,Qlight_stipple) || 
		EQ(stipple_spec,Qmedium_stipple) || EQ(stipple_spec,
		Qdark_stipple) || EQ(stipple_spec,Qlight_texture) || 
		EQ(stipple_spec,Qmedium_texture) || EQ(stipple_spec,
		Qdark_texture)) {
	    temp = ISVREF(icon_editor,(SI_Long)11L);
	    SVREF(temp,FIX((SI_Long)17L)) = stipple_spec;
	}
	return VALUES_1(SVREF(icon_editor,FIX((SI_Long)9L)) = stipple_spec);
    }
    else {
	engine = ISVREF(icon_editor,(SI_Long)11L);
	workspace = ISVREF(icon_editor,(SI_Long)4L);
	changed_qm = Nil;
	temp_1 = ISVREF(icon_editor,(SI_Long)7L);
	variables = CDR(temp_1);
	fixed_variables = Nil;
	fixed_element = Nil;
	new_variables = Nil;
	result = fix_up_drawing_element_for_icon_editor(stipple_spec,
		variables);
	MVS_3(result,fixed_element,fixed_variables,new_variables);
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(workspace,(SI_Long)1L),Nil);
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
	    gensymed_symbol_1 = nconc2(stack_change_list_2(workspace,
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
	    M_CAR(gensymed_symbol_1) = workspace;
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
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(workspace,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = workspace;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (T)
	      handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		      ISVREF(ISVREF(icon_editor,(SI_Long)10L),(SI_Long)1L),
		      Nil);
	  if ( !EQ(fixed_variables,Qerror)) {
	      if (new_variables) {
		  fixed_variables = icon_editor_cons_1(Qvariables,
			  fixed_variables);
		  SVREF(icon_editor,FIX((SI_Long)7L)) = fixed_variables;
		  inform_user_of_new_variables_for_icon_editor(icon_editor,
			  new_variables);
		  reclaim_gensym_tree_1(new_variables);
		  reclaim_gensym_tree_1(variables);
	      }
	      changed_qm = change_stipple_of_current_layer(engine,
		      stipple_spec);
	      if (ISVREF(engine,(SI_Long)16L))
		  reclaim_icon_editor_slot_value(ISVREF(engine,(SI_Long)16L));
	      temp = 
		      copy_drawing_element_with_icon_editor_conses(stipple_spec,
		      Nil,Nil);
	      SVREF(engine,FIX((SI_Long)16L)) = temp;
	  }
	  result_1 = changed_qm;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(workspace,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(workspace,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(workspace,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = workspace;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
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
		  temp_1 = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp_1) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(workspace,
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
	      update_all_representations_of_slot(workspace,
		      slot_description,Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(workspace);
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
	      temp_1 = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp_1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_1(result_1);
    }
}

/* SET-GLOBAL-STIPPLE-IN-ICON-EDITOR */
Object set_global_stipple_in_icon_editor(icon_editor,stipple_spec)
    Object icon_editor, stipple_spec;
{
    x_note_fn_call(235,14);
    return set_stipple_in_icon_editor(3,icon_editor,stipple_spec,T);
}

/* UPDATE-ICON-EDITOR-STATUS */
Object update_icon_editor_status(icon_editor)
    Object icon_editor;
{
    Object engine, layer, drawing_element, temp, ab_loop_list_, image_name_qm;
    Object image_definition_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(235,15);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    layer = ISVREF(engine,(SI_Long)6L);
    drawing_element = Nil;
    temp = CDDR(layer);
    ab_loop_list_ = CAR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(drawing_element) && EQ(FIRST(drawing_element),Qimage)) {
	image_name_qm = SECOND(drawing_element);
	image_definition_qm = image_name_qm ? 
		find_image_named(image_name_qm) : Qnil;
	if (image_name_qm &&  !TRUEP(image_definition_qm)) {
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
		      tformat(2,string_constant_2,image_name_qm);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    temp,Nil);
	}
	else if (image_definition_qm && 
		frame_incomplete_p(image_definition_qm)) {
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
		      tformat(2,string_constant_3,image_name_qm);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    temp,Nil);
	}
	else
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		    ISVREF(ISVREF(icon_editor,(SI_Long)10L),(SI_Long)1L),Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* EXTRACT-ICON-DESCRIPTION-FROM-ICON-EDITOR */
Object extract_icon_description_from_icon_editor(icon_editor)
    Object icon_editor;
{
    Object class_definition, serial_number, gensymed_symbol, xa, ya, engine;
    Object layer, ab_loop_list_, ab_loop_it_, temp_1;
    Object drawing_elements_present_qm, stipple_spec, icon_description_qm;
    char temp;

    x_note_fn_call(235,16);
    class_definition = ISVREF(icon_editor,(SI_Long)3L);
    serial_number = ISVREF(icon_editor,(SI_Long)5L);
    gensymed_symbol = ISVREF(class_definition,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(class_definition) ? EQ(ISVREF(class_definition,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	engine = ISVREF(icon_editor,(SI_Long)11L);
	layer = Nil;
	ab_loop_list_ = ISVREF(engine,(SI_Long)3L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	layer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = CDDR(layer);
	ab_loop_it_ = CAR(temp_1);
	if (ab_loop_it_) {
	    drawing_elements_present_qm = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	drawing_elements_present_qm = Qnil;
      end_1:;
	stipple_spec = ISVREF(icon_editor,(SI_Long)9L);
	icon_description_qm = drawing_elements_present_qm ? 
		convert_list_of_layers_to_line_drawing_description(ISVREF(engine,
		(SI_Long)3L),ISVREF(icon_editor,(SI_Long)6L),
		ISVREF(icon_editor,(SI_Long)7L),ISVREF(icon_editor,
		(SI_Long)8L),ISVREF(engine,(SI_Long)1L),ISVREF(engine,
		(SI_Long)2L),FIX((SI_Long)4096L),FIX((SI_Long)4096L),Nil,
		Nil,stipple_spec) : Nil;
	return VALUES_1(icon_description_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qicon_description;   /* icon-description */

static Object Qicon_description_for_class_qm;  /* icon-description-for-class? */

static Object string_constant_7;   /* "Error: Could not accept edit for ~NF. The value of the direct-superior-classes attribute on the ~
				    *           class-definition does not indicate that the class has a changeable icon-description."
				    */

/* UPDATE-CLASS-DEFINITION-FOR-ICON-EDITOR */
Object update_class_definition_for_icon_editor(icon_editor)
    Object icon_editor;
{
    Object class_definition, superior, ab_loop_list_, ab_loop_it_, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(235,17);
    class_definition = ISVREF(icon_editor,(SI_Long)3L);
    if (get_lookup_slot_value_given_default(class_definition,
	    Qclass_inheritance_path_of_definition,Nil)) {
	superior = Nil;
	ab_loop_list_ = ISVREF(class_definition,(SI_Long)21L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = superior;
	key_hash_value = SXHASH_SYMBOL_1(superior) & 
		IFIX(Most_positive_fixnum);
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
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
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		temp_2 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
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
	      next_loop_19:
		if (level < ab_loop_bind_)
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_20:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_21:
		if ( !TRUEP(marked))
		    goto end_loop_20;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_21;
	      end_loop_20:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_20;
	      end_loop_21:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_19;
	      end_loop_19:;
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
	      next_loop_22:
		if (level < ab_loop_bind_)
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_23:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_24:
		if ( !TRUEP(marked))
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_24;
	      end_loop_23:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_23;
	      end_loop_24:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_22;
	      end_loop_22:;
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
			IFIX(ISVREF(Connection_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_2 =  !temp_2;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_25:
	    if (level < ab_loop_bind_)
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_26:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_27:
	    if ( !TRUEP(marked))
		goto end_loop_26;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_27;
	  end_loop_26:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_26;
	  end_loop_27:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_25;
	  end_loop_25:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
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
	  next_loop_28:
	    if (level < ab_loop_bind_)
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_29:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_30:
	    if ( !TRUEP(marked))
		goto end_loop_29;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_30;
	  end_loop_29:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_10;
	    goto next_loop_29;
	  end_loop_30:
	  end_10:
	    level = level - (SI_Long)1L;
	    goto next_loop_28;
	  end_loop_28:;
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
	      next_loop_31:
		if (level < ab_loop_bind_)
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_32:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_33:
		if ( !TRUEP(marked))
		    goto end_loop_32;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_33;
	      end_loop_32:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_32;
	      end_loop_33:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_31;
	      end_loop_31:;
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
	      next_loop_34:
		if (level < ab_loop_bind_)
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_35:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_36:
		if ( !TRUEP(marked))
		    goto end_loop_35;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_36;
	      end_loop_35:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_12;
		goto next_loop_35;
	      end_loop_36:
	      end_12:
		level = level - (SI_Long)1L;
		goto next_loop_34;
	      end_loop_34:;
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
			IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_2 =  !temp_2;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_37:
	    if (level < ab_loop_bind_)
		goto end_loop_37;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_38:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_39:
	    if ( !TRUEP(marked))
		goto end_loop_38;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_39;
	  end_loop_38:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_13;
	    goto next_loop_38;
	  end_loop_39:
	  end_13:
	    level = level - (SI_Long)1L;
	    goto next_loop_37;
	  end_loop_37:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
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
	  next_loop_40:
	    if (level < ab_loop_bind_)
		goto end_loop_40;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_41:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_42:
	    if ( !TRUEP(marked))
		goto end_loop_41;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_42;
	  end_loop_41:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_14;
	    goto next_loop_41;
	  end_loop_42:
	  end_14:
	    level = level - (SI_Long)1L;
	    goto next_loop_40;
	  end_loop_40:;
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
	      next_loop_43:
		if (level < ab_loop_bind_)
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_44:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_45:
		if ( !TRUEP(marked))
		    goto end_loop_44;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_45;
	      end_loop_44:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_15;
		goto next_loop_44;
	      end_loop_45:
	      end_15:
		level = level - (SI_Long)1L;
		goto next_loop_43;
	      end_loop_43:;
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
	      next_loop_46:
		if (level < ab_loop_bind_)
		    goto end_loop_46;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_47:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_48:
		if ( !TRUEP(marked))
		    goto end_loop_47;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_48;
	      end_loop_47:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_16;
		goto next_loop_47;
	      end_loop_48:
	      end_16:
		level = level - (SI_Long)1L;
		goto next_loop_46;
	      end_loop_46:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    ab_loop_it_ = 
		    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
		    gensymed_symbol,Nil),(SI_Long)6L);
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_17;
	}
	goto next_loop;
      end_loop:
	temp_2 = TRUEP(Qnil);
      end_17:;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return change_slot_value(3,class_definition,
		Qicon_description_for_class_qm,
		extract_icon_description_from_icon_editor(icon_editor));
    else
	return notify_user(2,string_constant_7,class_definition);
}

/* CONVERT-LIST-OF-DOTTED-PAIRS-TO-LIST-OF-LISTS */
Object convert_list_of_dotted_pairs_to_list_of_lists(list_of_dotted_pairs)
    Object list_of_dotted_pairs;
{
    Object dotted_pair, ab_loop_list_, cdr_new_value;

    x_note_fn_call(235,18);
    dotted_pair = Nil;
    ab_loop_list_ = list_of_dotted_pairs;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dotted_pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    cdr_new_value = icon_editor_cons_1(CDR(dotted_pair),Nil);
    M_CDR(dotted_pair) = cdr_new_value;
    goto next_loop;
  end_loop:;
    return VALUES_1(list_of_dotted_pairs);
}

/* HANDLE-NEW-LAYER-CREATION-IN-ENGINE */
Object handle_new_layer_creation_in_engine(icon_editor,new_layer_index,
	    region_qm,color,new_layer_drawing_elements_qm)
    Object icon_editor, new_layer_index, region_qm, color;
    Object new_layer_drawing_elements_qm;
{
    Object engine, temp, temp_1, temp_2;

    x_note_fn_call(235,19);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    temp = region_qm;
    if (temp);
    else
	temp = color;
    set_color_of_region_in_icon_editor(icon_editor,temp,color);
    temp = region_qm;
    if (temp);
    else
	temp = color;
    new_icon_layer(temp,new_layer_drawing_elements_qm,new_layer_index,engine);
    reset_current_layer(engine,new_layer_index);
    temp = ISVREF(engine,(SI_Long)6L);
    temp = FIRST(temp);
    temp_1 = image_of_layer_qm(ISVREF(engine,(SI_Long)6L));
    temp_2 = text_of_layer_qm(ISVREF(engine,(SI_Long)6L));
    enqueue_icon_editor_engine_event(icon_editor,FIX((SI_Long)21L),temp,
	    temp_1,temp_2,stipple_of_layer_qm(ISVREF(engine,(SI_Long)6L)));
    return handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)36L),
	    Nil,Nil);
}

static Object string_constant_8;   /* "No more drawing elements to pop." */

static Object string_constant_9;   /* "No more layers to delete." */

/* HANDLE-DELETE-CURRENT-LAYER-FOR-ENGINE */
Object handle_delete_current_layer_for_engine(icon_editor,
	    deleting_drawing_element_p_qm)
    Object icon_editor, deleting_drawing_element_p_qm;
{
    Object engine, number_of_layers, temp_1, old_label, layer_index_to_delete;
    Object layer_to_delete, temp_2, temp_4, temp_5;
    SI_Long temp_3;
    char temp, layer_to_delete_is_empty_p;

    x_note_fn_call(235,20);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    number_of_layers = ISVREF(engine,(SI_Long)5L);
    temp = IFIX(number_of_layers) == (SI_Long)0L;
    if (temp);
    else if (IFIX(number_of_layers) == (SI_Long)1L) {
	temp_1 = ISVREF(engine,(SI_Long)6L);
	temp_1 = CDDR(temp_1);
	temp =  !TRUEP(CAR(temp_1));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)3L),
		copy_text_string(deleting_drawing_element_p_qm ? 
		string_constant_8 : string_constant_9),Nil);
	return VALUES_1(Nil);
    }
    else {
	temp_1 = ISVREF(engine,(SI_Long)6L);
	old_label = FIRST(temp_1);
	layer_index_to_delete = ISVREF(engine,(SI_Long)7L);
	layer_to_delete = delete_specific_layer(layer_index_to_delete,engine);
	temp_1 = CDDR(layer_to_delete);
	layer_to_delete_is_empty_p =  !TRUEP(CAR(temp_1));
	temp_2 = CDDDR(layer_to_delete);
	M_CAR(temp_2) = Nil;
	reclaim_icon_editor_slot_value(layer_to_delete);
	layer_to_delete = Nil;
	if (IFIX(ISVREF(engine,(SI_Long)7L)) > (SI_Long)0L) {
	    temp_2 = FIXNUM_SUB1(ISVREF(engine,(SI_Long)7L));
	    SVREF(engine,FIX((SI_Long)7L)) = temp_2;
	    temp_3 = IFIX(FIXNUM_SUB1(layer_index_to_delete));
	    reset_current_layer(engine,FIX(MAX(temp_3,(SI_Long)0L)));
	}
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)29L),
		layer_index_to_delete,Nil);
	if (IFIX(ISVREF(engine,(SI_Long)5L)) == (SI_Long)0L) {
	    engine = ISVREF(icon_editor,(SI_Long)11L);
	    handle_new_layer_creation_in_engine(icon_editor,
		    FIX((SI_Long)0L),Nil,ISVREF(engine,(SI_Long)11L),Nil);
	}
	else {
	    set_color_of_region_in_icon_editor(icon_editor,old_label,Nil);
	    inform_user_of_current_regions(icon_editor);
	    temp_1 = ISVREF(engine,(SI_Long)6L);
	    temp_1 = FIRST(temp_1);
	    temp_4 = image_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	    temp_5 = text_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	    enqueue_icon_editor_engine_event(icon_editor,FIX((SI_Long)21L),
		    temp_1,temp_4,temp_5,stipple_of_layer_qm(ISVREF(engine,
		    (SI_Long)6L)));
	}
	if ( !layer_to_delete_is_empty_p)
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)21L),
		    Nil,Nil);
	return VALUES_1(T);
    }
}

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* HANDLE-CHANGING-CURRENT-LAYER-IN-ENGINE */
Object handle_changing_current_layer_in_engine(icon_editor,new_layer_index)
    Object icon_editor, new_layer_index;
{
    Object engine, number_of_layers, svref_new_value, temp, current_label;
    Object current_image, current_text, current_stipple;
    SI_Long old_layer_index;

    x_note_fn_call(235,21);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    number_of_layers = ISVREF(engine,(SI_Long)5L);
    if (IFIX(new_layer_index) < (SI_Long)0L)
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)3L),
		copy_constant_wide_string_given_length(array_constant_6,
		FIX((SI_Long)33L)),Nil);
    else if (FIXNUM_GE(new_layer_index,number_of_layers))
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)3L),
		copy_constant_wide_string_given_length(array_constant_7,
		FIX((SI_Long)33L)),Nil);
    else {
	old_layer_index = IFIX(ISVREF(engine,(SI_Long)7L));
	SVREF(engine,FIX((SI_Long)7L)) = new_layer_index;
	svref_new_value = nth(new_layer_index,ISVREF(engine,(SI_Long)3L));
	SVREF(engine,FIX((SI_Long)6L)) = svref_new_value;
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)34L),
		FIX(old_layer_index),new_layer_index);
	temp = ISVREF(engine,(SI_Long)6L);
	current_label = FIRST(temp);
	current_image = image_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	current_text = text_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	current_stipple = stipple_of_layer_qm(ISVREF(engine,(SI_Long)6L));
	return enqueue_icon_editor_engine_event(icon_editor,
		FIX((SI_Long)21L),current_label,current_image,current_text,
		current_stipple);
    }
}

/* HANDLE-MOVE-LAYER-ALONG-Z-AXIS-IN-ENGINE */
Object handle_move_layer_along_z_axis_in_engine(icon_editor,
	    old_layer_index,new_layer_index)
    Object icon_editor, old_layer_index, new_layer_index;
{
    Object index_after_new_layer_index, engine;

    x_note_fn_call(235,22);
    index_after_new_layer_index = FIXNUM_ADD1(new_layer_index);
    engine = ISVREF(icon_editor,(SI_Long)11L);
    move_icon_layer(old_layer_index,index_after_new_layer_index,engine);
    reset_current_layer(engine,FIX(MAX(IFIX(new_layer_index),(SI_Long)0L)));
    return VALUES_1(T);
}

static Object Qstippled_area;      /* stippled-area */

/* HANDLE-MOVE-LAYER-IN-XY-PLANE-IN-ENGINE */
Object handle_move_layer_in_xy_plane_in_engine(icon_editor,engine,x_offset,
	    y_offset)
    Object icon_editor, engine, x_offset, y_offset;
{
    Object layer, temp, drawing_elements, drawing_element, ab_loop_list_;
    Object image_qm, text_qm, stipple_qm;

    x_note_fn_call(235,23);
    layer = ISVREF(engine,(SI_Long)6L);
    temp = CDDR(layer);
    drawing_elements = CAR(temp);
    if (drawing_elements) {
	shift_drawing_elements_in_place(drawing_elements,x_offset,y_offset);
	reclaim_icon_editor_slot_value(SECOND(layer));
	drawing_element = Nil;
	ab_loop_list_ = drawing_elements;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	drawing_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(drawing_element),Qimage)) {
	    image_qm = drawing_element;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	image_qm = Qnil;
      end_1:;
	drawing_element = Nil;
	ab_loop_list_ = drawing_elements;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	drawing_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(drawing_element),Qtext)) {
	    text_qm = drawing_element;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	text_qm = Qnil;
      end_2:;
	drawing_element = Nil;
	ab_loop_list_ = drawing_elements;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	drawing_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(drawing_element),Qstippled_area)) {
	    stipple_qm = drawing_element;
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
	stipple_qm = Qnil;
      end_3:;
	if (image_qm)
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)49L),
		    image_qm,Nil);
	if (text_qm)
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)50L),
		    text_qm,Nil);
	if (stipple_qm)
	    handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)51L),
		    stipple_qm,Nil);
	M_SECOND(layer) = Nil;
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)21L),Nil,Nil);
	return handle_icon_editor_visual_event(icon_editor,
		FIX((SI_Long)35L),Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qicon_editor;        /* icon-editor */

static Object array_constant_8;    /* # */

static Object Knil;                /* :nil */

static Object Qnone;               /* none */

static Object string_constant_10;  /* "There is no layer below the current layer to group." */

static Object array_constant_9;    /* # */

static Object Qpoint;              /* point */

static Object Qlines;              /* lines */

static Object Qarc;                /* arc */

static Object Qoutline;            /* outline */

static Object Qcircle;             /* circle */

static Object Qsolid_rectangle;    /* solid-rectangle */

static Object Qfilled_polygon;     /* filled-polygon */

static Object string_constant_11;  /* "The polygon was rejected because it was not a simple polygon." */

static Object Qfilled_circle;      /* filled-circle */

static Object array_constant_10;   /* # */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object array_constant_11;   /* # */

static Object string_constant_12;  /* "for ~a." */

static Object string_constant_13;  /* "Nothing in the current layer needs to be filled." */

static Object string_constant_14;  /* "Nothing in the current layer needs to be outlined." */

static Object string_constant_15;  /* "Can't fill an empty layer." */

static Object string_constant_16;  /* "Can't outline an empty layer." */

/* ENQUEUE-ICON-EDITOR-ENGINE-EVENT */
Object enqueue_icon_editor_engine_event(icon_editor,engine_event_init,
	    arg_1_qm,arg_2_qm,arg_3_qm,arg_4_qm)
    Object icon_editor, engine_event_init, arg_1_qm, arg_2_qm, arg_3_qm;
    Object arg_4_qm;
{
    Object current_layer_changed_p, redraw_view_pad_p, drawing_failed_p;
    Object gensymed_symbol, x, y, xa, ya, engine, scale, value, temp_2;
    Object icon_editor_engine, old_main_region_qm, temp_3, temp_4;
    Object new_color_qm, current_region_qm, old_color_qm, new_layer_index;
    Object engine_1, current_layer_index, layer_index_1, layer_index_2, layers;
    Object layer_1, drawing_elements_1, layer_2, label_2, element;
    Object ab_loop_list_, car_new_value, current_layer, temp_5, layer_index;
    Object layer, label, elements, new_current_layer_qm;
    Object group_points_into_one_layer_qm, new_list_of_elements;
    Object list_of_point_elements, ab_loopvar_, ab_loopvar__1, current_label;
    Object current_image, current_text, current_stipple, new_drawing_element;
    Object drawing_elements, x_value, y_value, ab_loop_desetq_;
    Object gensymed_symbol_1, decomposed_polygon_qm, new_color, new_region_qm;
    Object new_image_qm, new_text_qm, new_stipple_qm;
    Object number_of_drawing_elements, clear_info_box_p, rest_of_elements;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object name_or_names, icon_width, icon_height, current_drawing_elements_qm;
    Object variable_spec_list, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, new_drawing_elements_qm;
    SI_Long engine_event, temp_1, unshifted_result, current_width;
    SI_Long current_height, width_extent, height_extent, number_of_elements;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp, fill_qm;
    Declare_special(5);

    x_note_fn_call(235,24);
    engine_event = IFIX(engine_event_init);
    current_layer_changed_p = Nil;
    redraw_view_pad_p = Nil;
    drawing_failed_p = Nil;
    gensymed_symbol = ISVREF(ISVREF(icon_editor,(SI_Long)4L),(SI_Long)3L);
    x = ISVREF(icon_editor,(SI_Long)4L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(icon_editor,(SI_Long)5L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if (temp) {
	reclaim_icon_editor_tree_1(arg_1_qm);
	reclaim_icon_editor_tree_1(arg_2_qm);
	reclaim_icon_editor_tree_1(arg_3_qm);
	reclaim_icon_editor_tree_1(arg_4_qm);
	abort_current_workstation_context(Qicon_editor);
    }
    else {
	engine = ISVREF(icon_editor,(SI_Long)11L);
	temp_1 = engine_event;
	if (! !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
	    switch ((char)temp_1) {
	      case 20:
		change_size_of_icon_in_icon_editor(icon_editor,arg_1_qm,
			arg_2_qm);
		break;
	      case 23:
		change_size_of_icon_in_icon_editor(icon_editor,arg_1_qm,
			ISVREF(ISVREF(icon_editor,(SI_Long)11L),(SI_Long)2L));
		break;
	      case 24:
		change_size_of_icon_in_icon_editor(icon_editor,
			ISVREF(ISVREF(icon_editor,(SI_Long)11L),
			(SI_Long)1L),arg_1_qm);
		break;
	      case 22:
		scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),(SI_Long)10L);
		value = ISVREF(engine,(SI_Long)1L);
		if (IFIX(scale) == (SI_Long)4096L)
		    temp_2 = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_2 = scalef_function(scale,value);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)11L),temp_2,Nil);
		scale = ISVREF(ISVREF(icon_editor,(SI_Long)12L),(SI_Long)11L);
		value = ISVREF(engine,(SI_Long)2L);
		if (IFIX(scale) == (SI_Long)4096L)
		    temp_2 = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp_2 = scalef_function(scale,value);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)12L),temp_2,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)21L),Nil,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)38L),Nil,Nil);
		break;
	      case 52:
		icon_editor_engine = ISVREF(icon_editor,(SI_Long)11L);
		current_width = IFIX(ISVREF(icon_editor_engine,(SI_Long)1L));
		current_height = IFIX(ISVREF(icon_editor_engine,(SI_Long)2L));
		width_extent = IFIX(ISVREF(icon_editor_engine,(SI_Long)8L));
		height_extent = IFIX(ISVREF(icon_editor_engine,(SI_Long)9L));
		change_size_of_icon_in_icon_editor(icon_editor,
			current_width > width_extent ? FIX(width_extent) : 
			FIX(current_width),current_height > height_extent ?
			 FIX(height_extent) : FIX(current_height));
		break;
	      case 18:
		set_main_color_in_icon_editor(icon_editor,arg_1_qm);
		break;
	      case 17:
		if (illegal_region_name_p(arg_1_qm))
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),
			    copy_constant_wide_string_given_length(array_constant_8,
			    FIX((SI_Long)36L)),Nil);
		else {
		    if (EQ(arg_1_qm,Knil) || EQ(arg_1_qm,Qnone))
			arg_1_qm = Nil;
		    engine = ISVREF(icon_editor,(SI_Long)11L);
		    old_main_region_qm = ISVREF(engine,(SI_Long)10L);
		    if ( !EQ(old_main_region_qm,arg_1_qm)) {
			temp_2 = ISVREF(engine,(SI_Long)7L);
			temp_3 = ISVREF(engine,(SI_Long)10L);
			if (temp_3);
			else
			    temp_3 = ISVREF(engine,(SI_Long)11L);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)33L),temp_2,temp_3);
			SVREF(engine,FIX((SI_Long)10L)) = arg_1_qm;
			temp_4 = ISVREF(ISVREF(icon_editor,(SI_Long)11L),
				(SI_Long)6L);
			M_FIRST(temp_4) = arg_1_qm;
			new_color_qm = 
				get_color_of_region_in_icon_editor(icon_editor,
				arg_1_qm);
			set_main_color_in_icon_editor(icon_editor,
				new_color_qm ? new_color_qm : 
				ISVREF(engine,(SI_Long)11L));
			set_color_of_region_in_icon_editor(icon_editor,
				old_main_region_qm,Nil);
		    }
		}
		inform_user_of_current_regions(icon_editor);
		break;
	      case 64:
		current_layer_changed_p = 
			set_main_image_in_icon_editor(icon_editor,arg_1_qm);
		break;
	      case 65:
		current_layer_changed_p = 
			set_text_in_icon_editor(icon_editor,arg_1_qm);
		break;
	      case 66:
		current_layer_changed_p = set_stipple_in_icon_editor(2,
			icon_editor,arg_1_qm);
		break;
	      case 67:
		current_layer_changed_p = 
			set_global_stipple_in_icon_editor(icon_editor,
			arg_1_qm);
		break;
	      case 46:
		icon_editor_engine = ISVREF(icon_editor,(SI_Long)11L);
		current_region_qm = ISVREF(icon_editor_engine,(SI_Long)12L);
		old_color_qm = 
			get_color_of_region_in_icon_editor(icon_editor,
			current_region_qm);
		if (old_color_qm)
		    set_color_of_region_in_icon_editor(icon_editor,
			    old_color_qm,Nil);
		if ( !EQ(old_color_qm,arg_1_qm))
		    SVREF(icon_editor_engine,FIX((SI_Long)13L)) = arg_1_qm;
		break;
	      case 47:
		temp_4 = ISVREF(icon_editor,(SI_Long)11L);
		SVREF(temp_4,FIX((SI_Long)12L)) = arg_1_qm;
		break;
	      case 8:
		new_layer_index = FIXNUM_ADD1(ISVREF(engine,(SI_Long)7L));
		engine = ISVREF(icon_editor,(SI_Long)11L);
		handle_new_layer_creation_in_engine(icon_editor,
			new_layer_index,Nil,ISVREF(engine,(SI_Long)11L),Nil);
		break;
	      case 5:
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)0L),Nil,Nil);
		break;
	      case 6:
		update_class_definition_for_icon_editor(icon_editor);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)0L),Nil,Nil);
		break;
	      case 10:
		engine_1 = ISVREF(icon_editor,(SI_Long)11L);
		current_layer_index = ISVREF(engine_1,(SI_Long)7L);
		if (IFIX(current_layer_index) <= (SI_Long)0L) {
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),
			    copy_text_string(string_constant_10),Nil);
		    redraw_view_pad_p = Nil;
		}
		else {
		    layer_index_1 = current_layer_index;
		    layer_index_2 = FIXNUM_SUB1(current_layer_index);
		    icon_editor_engine = ISVREF(icon_editor,(SI_Long)11L);
		    layers = ISVREF(icon_editor_engine,(SI_Long)3L);
		    layer_1 = FIXNUM_EQ(layer_index_1,
			    ISVREF(icon_editor_engine,(SI_Long)7L)) ? 
			    ISVREF(icon_editor_engine,(SI_Long)6L) : 
			    nth(layer_index_1,layers);
		    temp_2 = CDDR(layer_1);
		    drawing_elements_1 = CAR(temp_2);
		    layer_2 = delete_specific_layer(layer_index_2,
			    icon_editor_engine);
		    label_2 = FIRST(layer_2);
		    element = Nil;
		    temp_2 = CDDR(layer_2);
		    ab_loop_list_ = CAR(temp_2);
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    element = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    drawing_elements_1 = icon_editor_cons_1(element,
			    drawing_elements_1);
		    goto next_loop;
		  end_loop:;
		    temp_4 = CDDR(layer_1);
		    M_CAR(temp_4) = drawing_elements_1;
		    temp_4 = CDDDR(layer_1);
		    car_new_value = last(drawing_elements_1,_);
		    M_CAR(temp_4) = car_new_value;
		    reclaim_icon_editor_slot_value(SECOND(layer_1));
		    M_SECOND(layer_1) = Nil;
		    reclaim_icon_editor_slot_value(SECOND(layer_2));
		    reclaim_icon_editor_list_1(layer_2);
		    temp_1 = IFIX(FIXNUM_SUB1(layer_index_1));
		    reset_current_layer(icon_editor_engine,FIX(MAX(temp_1,
			    (SI_Long)0L)));
		    set_color_of_region_in_icon_editor(icon_editor,label_2,
			    Nil);
		    inform_user_of_current_regions(icon_editor);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)36L),Nil,Nil);
		    redraw_view_pad_p = T;
		}
		current_layer = ISVREF(engine,(SI_Long)6L);
		if (current_layer) {
		    temp_2 = FIRST(current_layer);
		    temp_3 = image_of_layer_qm(current_layer);
		    temp_5 = text_of_layer_qm(current_layer);
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)21L),temp_2,temp_3,temp_5,
			    stipple_of_layer_qm(current_layer));
		}
		break;
	      case 11:
		current_layer = ISVREF(engine,(SI_Long)6L);
		temp_2 = CDDR(current_layer);
		number_of_elements = IFIX(length(CAR(temp_2)));
		if (number_of_elements < (SI_Long)2L)
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),
			    copy_constant_wide_string_given_length(array_constant_9,
			    FIX((SI_Long)38L)),Nil);
		else {
		    layer_index = ISVREF(engine,(SI_Long)7L);
		    engine_1 = ISVREF(icon_editor,(SI_Long)11L);
		    layer = delete_specific_layer(layer_index,engine_1);
		    label = FIRST(layer);
		    temp_2 = CDDR(layer);
		    elements = CAR(temp_2);
		    new_current_layer_qm = Nil;
		    group_points_into_one_layer_qm = Nil;
		    element = Nil;
		    ab_loop_list_ = elements;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    element = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if ( !EQ(FIRST(element),Qpoint))
			goto end_loop_1;
		    goto next_loop_1;
		  end_loop_1:
		    if ( !EQ(FIRST(element),Qpoint))
			group_points_into_one_layer_qm = T;
		    new_list_of_elements = Nil;
		    element = Nil;
		    ab_loop_list_ = elements;
		    list_of_point_elements = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    element = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (EQ(FIRST(element),Qpoint) && 
			    group_points_into_one_layer_qm) {
			ab_loopvar__1 = icon_editor_cons_1(element,Nil);
			if (ab_loopvar_)
			    M_CDR(ab_loopvar_) = ab_loopvar__1;
			else
			    list_of_point_elements = ab_loopvar__1;
			ab_loopvar_ = ab_loopvar__1;
		    }
		    if ( !(EQ(FIRST(element),Qpoint) && 
			    group_points_into_one_layer_qm)) {
			new_list_of_elements = icon_editor_cons_1(element,Nil);
			new_current_layer_qm = icon_editor_list_4(label,
				Nil,new_list_of_elements,new_list_of_elements);
			put_layer_before_specific_layer(new_current_layer_qm,
				layer_index,engine_1);
			layer_index = FIXNUM_ADD1(layer_index);
		    }
		    goto next_loop_2;
		  end_loop_2:
		    if (list_of_point_elements) {
			new_current_layer_qm = icon_editor_list_4(label,
				Nil,list_of_point_elements,
				list_of_point_elements);
			put_layer_before_specific_layer(new_current_layer_qm,
				layer_index,engine_1);
			layer_index = FIXNUM_ADD1(layer_index);
		    }
		    reclaim_icon_editor_list_1(elements);
		    SVREF(engine_1,FIX((SI_Long)6L)) = new_current_layer_qm;
		    temp_4 = FIXNUM_SUB1(layer_index);
		    SVREF(engine_1,FIX((SI_Long)7L)) = temp_4;
		    temp_4 = CDDR(layer);
		    M_CAR(temp_4) = Nil;
		    temp_4 = CDDDR(layer);
		    M_CAR(temp_4) = Nil;
		    reclaim_icon_editor_slot_value(layer);
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)36L),Nil,Nil);
		    current_layer = ISVREF(engine,(SI_Long)6L);
		    if (current_layer) {
			current_label = FIRST(current_layer);
			current_image = image_of_layer_qm(current_layer);
			current_text = text_of_layer_qm(current_layer);
			current_stipple = stipple_of_layer_qm(current_layer);
			enqueue_icon_editor_engine_event(icon_editor,
				FIX((SI_Long)21L),current_label,
				current_image,current_text,current_stipple);
		    }
		    redraw_view_pad_p = T;
		}
		break;
	      case 9:
		handle_delete_current_layer_for_engine(icon_editor,Nil);
		break;
	      case 32:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_2(Qpoint,
			icon_editor_list_2(arg_1_qm,arg_2_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 33:
		x_value = Nil;
		y_value = Nil;
		ab_loop_list_ = arg_1_qm;
		ab_loop_desetq_ = Nil;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		ab_loop_desetq_ = M_CAR(ab_loop_list_);
		x_value = CAR(ab_loop_desetq_);
		y_value = CDR(ab_loop_desetq_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_2(Qpoint,
			icon_editor_list_2(x_value,y_value));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		goto next_loop_3;
	      end_loop_3:;
		reclaim_icon_editor_tree_1(arg_1_qm);
		current_layer_changed_p = T;
		break;
	      case 34:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_3(Qlines,
			icon_editor_list_2(arg_1_qm,arg_2_qm),
			icon_editor_list_2(arg_3_qm,arg_4_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 35:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_cons_1(Qlines,
			convert_list_of_dotted_pairs_to_list_of_lists(arg_1_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 36:
		icon_editor_engine = engine;
		temp_4 = icon_editor_cons_1(CDR(arg_1_qm),Nil);
		M_CDR(arg_1_qm) = temp_4;
		temp_3 = arg_1_qm;
		temp_4 = icon_editor_cons_1(CDR(arg_2_qm),Nil);
		M_CDR(arg_2_qm) = temp_4;
		temp_2 = icon_editor_list_2(Qarc,arg_2_qm);
		temp_4 = icon_editor_cons_1(CDR(arg_3_qm),Nil);
		M_CDR(arg_3_qm) = temp_4;
		new_drawing_element = icon_editor_list_4(Qlines,temp_3,
			temp_2,arg_3_qm);
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 37:
		icon_editor_engine = engine;
		gensymed_symbol = make_icon_editor_list_1(FIX((SI_Long)5L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = Qoutline;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_4 = icon_editor_list_2(arg_1_qm,arg_2_qm);
		M_CAR(gensymed_symbol_1) = temp_4;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_4 = icon_editor_list_2(arg_1_qm,arg_4_qm);
		M_CAR(gensymed_symbol_1) = temp_4;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_4 = icon_editor_list_2(arg_3_qm,arg_4_qm);
		M_CAR(gensymed_symbol_1) = temp_4;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_4 = icon_editor_list_2(arg_3_qm,arg_2_qm);
		M_CAR(gensymed_symbol_1) = temp_4;
		new_drawing_element = gensymed_symbol;
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 38:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_cons_1(Qoutline,
			convert_list_of_dotted_pairs_to_list_of_lists(arg_1_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 39:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_4(Qcircle,
			icon_editor_list_2(FIXNUM_MINUS(arg_1_qm,arg_3_qm),
			arg_2_qm),icon_editor_list_2(arg_1_qm,
			FIXNUM_MINUS(arg_2_qm,arg_3_qm)),
			icon_editor_list_2(FIXNUM_ADD(arg_1_qm,arg_3_qm),
			arg_2_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 40:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_3(Qsolid_rectangle,
			icon_editor_list_2(arg_1_qm,arg_2_qm),
			icon_editor_list_2(arg_3_qm,arg_4_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 41:
		convert_list_of_dotted_pairs_to_list_of_lists(arg_1_qm);
		if ( !TRUEP(clockwise_polygon_p(arg_1_qm)))
		    arg_1_qm = nreverse(arg_1_qm);
		decomposed_polygon_qm = 
			decompose_polygon_using_icon_editor_conses(arg_1_qm);
		if (decomposed_polygon_qm) {
		    icon_editor_engine = engine;
		    new_drawing_element = 
			    icon_editor_cons_1(Qfilled_polygon,
			    icon_editor_cons_1(arg_1_qm,
			    decomposed_polygon_qm));
		    layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		    temp_2 = CDDR(layer);
		    drawing_elements = CAR(temp_2);
		    reclaim_icon_editor_slot_value(SECOND(layer));
		    M_SECOND(layer) = Nil;
		    gensymed_symbol = new_drawing_element;
		    gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		    if (drawing_elements) {
			temp_2 = CDDDR(layer);
			if ( !TRUEP(CAR(temp_2))) {
			    temp_4 = CDDDR(layer);
			    car_new_value = last(drawing_elements,_);
			    M_CAR(temp_4) = car_new_value;
			}
			temp_2 = CDDDR(layer);
			temp_4 = CAR(temp_2);
			M_CDR(temp_4) = gensymed_symbol;
		    }
		    else
			drawing_elements = gensymed_symbol;
		    temp_4 = CDDDR(layer);
		    M_CAR(temp_4) = gensymed_symbol;
		    temp_4 = CDDR(layer);
		    M_CAR(temp_4) = drawing_elements;
		    current_layer_changed_p = T;
		}
		else {
		    drawing_failed_p = T;
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),
			    copy_text_string(string_constant_11),Nil);
		}
		break;
	      case 42:
		icon_editor_engine = engine;
		new_drawing_element = icon_editor_list_4(Qfilled_circle,
			icon_editor_list_2(FIXNUM_MINUS(arg_1_qm,arg_3_qm),
			arg_2_qm),icon_editor_list_2(arg_1_qm,
			FIXNUM_MINUS(arg_2_qm,arg_3_qm)),
			icon_editor_list_2(FIXNUM_ADD(arg_1_qm,arg_3_qm),
			arg_2_qm));
		layer = ISVREF(icon_editor_engine,(SI_Long)6L);
		temp_2 = CDDR(layer);
		drawing_elements = CAR(temp_2);
		reclaim_icon_editor_slot_value(SECOND(layer));
		M_SECOND(layer) = Nil;
		gensymed_symbol = new_drawing_element;
		gensymed_symbol = icon_editor_cons_1(gensymed_symbol,Nil);
		if (drawing_elements) {
		    temp_2 = CDDDR(layer);
		    if ( !TRUEP(CAR(temp_2))) {
			temp_4 = CDDDR(layer);
			car_new_value = last(drawing_elements,_);
			M_CAR(temp_4) = car_new_value;
		    }
		    temp_2 = CDDDR(layer);
		    temp_4 = CAR(temp_2);
		    M_CDR(temp_4) = gensymed_symbol;
		}
		else
		    drawing_elements = gensymed_symbol;
		temp_4 = CDDDR(layer);
		M_CAR(temp_4) = gensymed_symbol;
		temp_4 = CDDR(layer);
		M_CAR(temp_4) = drawing_elements;
		current_layer_changed_p = T;
		break;
	      case 43:
		break;
	      case 44:
		break;
	      case 45:
		break;
	      case 12:
		handle_changing_current_layer_in_engine(icon_editor,
			FIXNUM_ADD1(ISVREF(engine,(SI_Long)7L)));
		break;
	      case 13:
		handle_changing_current_layer_in_engine(icon_editor,
			FIXNUM_SUB1(ISVREF(engine,(SI_Long)7L)));
		break;
	      case 14:
		handle_changing_current_layer_in_engine(icon_editor,arg_1_qm);
		break;
	      case 21:
		new_color = get_color_of_region_in_icon_editor(icon_editor,
			arg_1_qm);
		if (new_color);
		else
		    new_color = arg_1_qm;
		new_region_qm = illegal_region_name_p(arg_1_qm) ? Nil : 
			arg_1_qm;
		new_image_qm = arg_2_qm;
		new_text_qm = arg_3_qm;
		new_stipple_qm = arg_4_qm;
		if (ISVREF(engine,(SI_Long)15L))
		    reclaim_icon_editor_slot_value(ISVREF(engine,
			    (SI_Long)15L));
		SVREF(engine,FIX((SI_Long)10L)) = new_region_qm;
		SVREF(engine,FIX((SI_Long)11L)) = new_color;
		temp_4 = copy_tree_using_slot_value_conses_1(new_image_qm);
		SVREF(engine,FIX((SI_Long)14L)) = temp_4;
		temp_4 = 
			copy_drawing_element_with_icon_editor_conses(new_text_qm,
			Nil,Nil);
		SVREF(engine,FIX((SI_Long)15L)) = temp_4;
		temp_4 = 
			copy_drawing_element_with_icon_editor_conses(new_stipple_qm,
			Nil,Nil);
		SVREF(engine,FIX((SI_Long)16L)) = temp_4;
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)6L),new_region_qm,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)7L),new_color,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)49L),new_image_qm,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)50L),new_text_qm,Nil);
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)51L),new_stipple_qm,Nil);
		break;
	      case 31:
		current_layer = ISVREF(engine,(SI_Long)6L);
		temp_2 = CDDR(current_layer);
		drawing_elements = CAR(temp_2);
		number_of_drawing_elements = length(drawing_elements);
		clear_info_box_p = Nil;
		if (IFIX(number_of_drawing_elements) <= (SI_Long)0L)
		    clear_info_box_p = 
			    handle_delete_current_layer_for_engine(icon_editor,
			    T);
		else {
		    layer = ISVREF(engine,(SI_Long)6L);
		    temp_2 = CDDR(layer);
		    drawing_elements = CAR(temp_2);
		    if ( !TRUEP(CDR(drawing_elements))) {
			temp_4 = CDDR(layer);
			M_CAR(temp_4) = Nil;
			temp_4 = CDDDR(layer);
			M_CAR(temp_4) = Nil;
		    }
		    else {
			rest_of_elements = drawing_elements;
		      next_loop_4:
			if ( !TRUEP(rest_of_elements))
			    goto end_loop_4;
			if ( !TRUEP(CDDR(rest_of_elements))) {
			    reclaim_icon_editor_slot_value(CDR(rest_of_elements));
			    M_CDR(rest_of_elements) = Nil;
			    temp_4 = CDDDR(layer);
			    M_CAR(temp_4) = rest_of_elements;
			    goto end_1;
			}
			rest_of_elements = M_CDR(rest_of_elements);
			goto next_loop_4;
		      end_loop_4:
		      end_1:;
		    }
		    current_layer_changed_p = T;
		}
		current_layer = ISVREF(engine,(SI_Long)6L);
		if (current_layer) {
		    current_label = FIRST(current_layer);
		    current_image = image_of_layer_qm(current_layer);
		    current_text = text_of_layer_qm(current_layer);
		    current_stipple = stipple_of_layer_qm(current_layer);
		    enqueue_icon_editor_engine_event(icon_editor,
			    FIX((SI_Long)21L),current_label,current_image,
			    current_text,current_stipple);
		}
		if (clear_info_box_p)
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),FIX((SI_Long)0L),Nil);
		break;
	      case 7:
		update_class_definition_for_icon_editor(icon_editor);
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
			  twrite_beginning_of_wide_string(array_constant_10,
				  FIX((SI_Long)25L));
			  name_or_names = 
				  get_lookup_slot_value_given_default(ISVREF(icon_editor,
				  (SI_Long)3L),Qname_or_names_for_frame,Nil);
			  if ( !TRUEP(name_or_names))
			      twrite_beginning_of_wide_string(array_constant_11,
				      FIX((SI_Long)24L));
			  else
			      tformat(2,string_constant_12,
				      LISTP(name_or_names) ? 
				      CAR(name_or_names) : name_or_names);
			  temp_2 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)3L),temp_2,Nil);
		break;
	      case 55:
		handle_move_layer_along_z_axis_in_engine(icon_editor,
			arg_1_qm,arg_2_qm);
		redraw_view_pad_p = T;
		handle_icon_editor_visual_event(icon_editor,
			FIX((SI_Long)27L),Nil,Nil);
		break;
	      case 56:
		handle_move_layer_in_xy_plane_in_engine(icon_editor,engine,
			arg_1_qm,arg_2_qm);
		break;
	      case 57:
		temp_2 = ISVREF(engine,(SI_Long)7L);
		temp_3 = ISVREF(engine,(SI_Long)11L);
		temp_5 = ISVREF(engine,(SI_Long)6L);
		temp_5 = CDDR(temp_5);
		handle_new_layer_creation_in_engine(icon_editor,temp_2,Nil,
			temp_3,
			copy_tree_including_leaves_using_icon_editor_conses(CAR(temp_5)));
		break;
	      case 58:
	      case 59:
		fill_qm = engine_event == (SI_Long)58L;
		icon_width = ISVREF(ISVREF(icon_editor,(SI_Long)11L),
			(SI_Long)1L);
		icon_height = ISVREF(ISVREF(icon_editor,(SI_Long)11L),
			(SI_Long)2L);
		current_layer = ISVREF(engine,(SI_Long)6L);
		temp_2 = CDDR(current_layer);
		current_drawing_elements_qm = CAR(temp_2);
		if (current_drawing_elements_qm) {
		    temp_2 = ISVREF(icon_editor,(SI_Long)7L);
		    variable_spec_list = CDR(temp_2);
		    current_icon_untransformed_width = icon_width;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
			    3);
		      current_icon_untransformed_height = icon_height;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
			      2);
			current_icon_variables_plist = variable_spec_list;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
				1);
			  current_icon_variables_override_plist = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
				  0);
			    new_drawing_elements_qm = fill_qm ? 
				    convert_to_filled_drawing_elements(current_drawing_elements_qm) 
				    : 
				    convert_to_outlined_drawing_elements(current_drawing_elements_qm);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    if (new_drawing_elements_qm) {
			temp_4 = CDDDR(current_layer);
			car_new_value = last(new_drawing_elements_qm,_);
			M_CAR(temp_4) = car_new_value;
			temp_4 = CDDR(current_layer);
			M_CAR(temp_4) = new_drawing_elements_qm;
			reclaim_icon_editor_slot_value(SECOND(current_layer));
			M_SECOND(current_layer) = Nil;
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)35L),Nil,Nil);
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)21L),Nil,Nil);
		    }
		    else
			handle_icon_editor_visual_event(icon_editor,
				FIX((SI_Long)3L),copy_text_string(fill_qm ?
				 string_constant_13 : string_constant_14),Nil);
		}
		else
		    handle_icon_editor_visual_event(icon_editor,
			    FIX((SI_Long)3L),copy_text_string(fill_qm ? 
			    string_constant_15 : string_constant_16),Nil);
		break;
	      default:
		break;
	    }
    }
    if (current_layer_changed_p)
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)35L),Nil,Nil);
    if (redraw_view_pad_p || current_layer_changed_p)
	handle_icon_editor_visual_event(icon_editor,FIX((SI_Long)21L),Nil,Nil);
    return VALUES_1(drawing_failed_p);
}

/* ICON-EDITOR-FOR-ICON-EDITOR-WORKSPACE */
Object icon_editor_for_icon_editor_workspace(workspace)
    Object workspace;
{
    Object temp, image_plane_qm, pane_qm, window_qm, workstation_qm;
    Object context_stack, context, ab_loop_list_, icon_editor_qm;

    x_note_fn_call(235,25);
    temp = ISVREF(workspace,(SI_Long)16L);
    image_plane_qm = FIRST(temp);
    pane_qm = image_plane_qm ? ISVREF(image_plane_qm,(SI_Long)2L) : Qnil;
    window_qm = pane_qm ? ISVREF(pane_qm,(SI_Long)2L) : Qnil;
    workstation_qm = window_qm ? ISVREF(window_qm,(SI_Long)2L) : Qnil;
    context_stack = workstation_qm ? ISVREF(workstation_qm,(SI_Long)17L) : 
	    Qnil;
    context = Nil;
    ab_loop_list_ = context_stack;
    icon_editor_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    context = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    icon_editor_qm = EQ(ISVREF(context,(SI_Long)1L),Qicon_editor) ? 
	    ISVREF(context,(SI_Long)2L) : Qnil;
    if (icon_editor_qm && EQ(ISVREF(icon_editor_qm,(SI_Long)4L),workspace))
	return VALUES_1(icon_editor_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qobject_configuration;  /* object-configuration */

static Object Qcheck_undefined_instances_of_class;  /* check-undefined-instances-of-class */

static Object Qimage_definition;   /* image-definition */

/* ANALYZE-FOR-CONSISTENCY-FOR-ICON-EDITOR-WORKSPACE */
Object analyze_for_consistency_for_icon_editor_workspace(icon_editor_workspace,
	    add_as_item_referring_to_name_qm,
	    delete_as_item_referring_to_name_qm)
    Object icon_editor_workspace, add_as_item_referring_to_name_qm;
    Object delete_as_item_referring_to_name_qm;
{
    Object icon_editor_qm, engine_qm, layers, compiled_item_being_analyzed;
    Object any_qm, object_configuration_qm, layer, ab_loop_list_;
    Object drawing_element, temp, ab_loop_list__1, image_name_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(235,26);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Delete_as_item_referring_to_name_qm,Qdelete_as_item_referring_to_name_qm,delete_as_item_referring_to_name_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Add_as_item_referring_to_name_qm,Qadd_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
	      1);
	if (Defer_consistency_analysis_qm &&  
		!TRUEP(Add_as_item_referring_to_name_qm) &&  
		!TRUEP(Delete_as_item_referring_to_name_qm))
	    result = defer_consistency_analysis_of_item(icon_editor_workspace);
	else {
	    LOCK(Analyze_for_consistency_in_progress);
	    if (PUSH_UNWIND_PROTECT(0)) {
		if ( !TRUEP(Loading_kb_p)) {
		    delete_all_consistency_analysis_frame_notes(1,
			    icon_editor_workspace);
		    icon_editor_qm = 
			    icon_editor_for_icon_editor_workspace(icon_editor_workspace);
		    engine_qm = icon_editor_qm ? ISVREF(icon_editor_qm,
			    (SI_Long)11L) : Qnil;
		    layers = engine_qm ? ISVREF(engine_qm,(SI_Long)3L) : Qnil;
		    if (layers) {
			compiled_item_being_analyzed = icon_editor_workspace;
			any_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Compiled_item_being_analyzed,Qcompiled_item_being_analyzed,compiled_item_being_analyzed,
				0);
			  object_configuration_qm = 
				  get_lookup_slot_value(icon_editor_workspace,
				  Qobject_configuration);
			  if (object_configuration_qm)
			      map_over_external_names_in_object_configuration(SYMBOL_FUNCTION(Qcheck_undefined_instances_of_class),
				      object_configuration_qm);
			  layer = Nil;
			  ab_loop_list_ = layers;
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  layer = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  drawing_element = Nil;
			  temp = CDDR(layer);
			  ab_loop_list__1 = CAR(temp);
			next_loop_1:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_1;
			  drawing_element = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  if (CONSP(drawing_element) && 
				  EQ(FIRST(drawing_element),Qimage)) {
			      image_name_qm = SECOND(drawing_element);
			      if (image_name_qm) {
				  check_undefined_instances_of_class(image_name_qm,
					  Qimage_definition);
				  any_qm = T;
			      }
			  }
			  goto next_loop_1;
			end_loop_1:;
			  goto next_loop;
			end_loop:;
			  if (any_qm &&  
				  !TRUEP(Add_as_item_referring_to_name_qm) 
				  &&  
				  !TRUEP(Delete_as_item_referring_to_name_qm)) 
				      {
			      update_icon_editor_status(icon_editor_qm);
			      handle_icon_editor_visual_event(icon_editor_qm,
				      FIX((SI_Long)38L),Nil,Nil);
			      SAVE_VALUES(handle_icon_editor_visual_event(icon_editor_qm,
				      FIX((SI_Long)21L),Nil,Nil));
			  }
			  else
			      SAVE_VALUES(VALUES_1(Nil));
			POP_SPECIAL();
		    }
		    else
			SAVE_VALUES(VALUES_1(Nil));
		}
		else
		    SAVE_VALUES(VALUES_1(Nil));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Analyze_for_consistency_in_progress);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

void icons4_INIT()
{
    Object temp, temp_1;
    Object Qclasses_which_define, Qanalyze_for_consistency;
    Object Qicon_editor_workspace, AB_package;
    Object Qanalyze_for_consistency_for_icon_editor_workspace, list_constant;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qtext_specification_qm, Qslot_value_compiler;
    Object Qcompile_text_specification_qm_for_slot, Qimage_specification_qm;
    Object Qcompile_image_specification_qm_for_slot;

    x_note_fn_call(235,27);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = 
	    STATIC_STRING("The maximum icon width in the icon editor is ~a.");
    string_constant_1 = 
	    STATIC_STRING("The maximum icon height in the icon editor is ~a.");
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    string_constant_2 = 
	    STATIC_STRING("Note that there is currently no image named ~a");
    string_constant_3 = 
	    STATIC_STRING("Note that the image ~a is currently incomplete");
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_4 = STATIC_STRING("undefined-text");
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    string_constant_5 = STATIC_STRING("s:  ");
    string_constant_6 = STATIC_STRING(":  ");
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qicon_editor_table_info_frame_icon_editor = 
	    STATIC_SYMBOL("ICON-EDITOR-TABLE-INFO-FRAME-ICON-EDITOR",
	    AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)32L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)33L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)36L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)41L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)42L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)43L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)44L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)46L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)48L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)49L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)50L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)53L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)62L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)63L,(SI_Long)57344L);
    Qimage_specification_qm = STATIC_SYMBOL("IMAGE-SPECIFICATION\?",
	    AB_package);
    Qcompile_image_specification_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-IMAGE-SPECIFICATION\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_image_specification_qm_for_slot,
	    STATIC_FUNCTION(compile_image_specification_qm_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qimage_specification_qm,
	    SYMBOL_FUNCTION(Qcompile_image_specification_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qimage_specification_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_5 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)57344L);
    Qtext_specification_qm = STATIC_SYMBOL("TEXT-SPECIFICATION\?",AB_package);
    Qcompile_text_specification_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-TEXT-SPECIFICATION\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_text_specification_qm_for_slot,
	    STATIC_FUNCTION(compile_text_specification_qm_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qtext_specification_qm,
	    SYMBOL_FUNCTION(Qcompile_text_specification_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtext_specification_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qlight_stipple = STATIC_SYMBOL("LIGHT-STIPPLE",AB_package);
    Qmedium_stipple = STATIC_SYMBOL("MEDIUM-STIPPLE",AB_package);
    Qdark_stipple = STATIC_SYMBOL("DARK-STIPPLE",AB_package);
    Qlight_texture = STATIC_SYMBOL("LIGHT-TEXTURE",AB_package);
    Qmedium_texture = STATIC_SYMBOL("MEDIUM-TEXTURE",AB_package);
    Qdark_texture = STATIC_SYMBOL("DARK-TEXTURE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qicon_description_for_class_qm = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-FOR-CLASS\?",AB_package);
    string_constant_7 = 
	    string_append2(STATIC_STRING("Error: Could not accept edit for ~NF. The value of the direct-superior-classes attribute on the ~\n          class-definition does not indicate that the class has a changeable "),
	    STATIC_STRING("icon-description."));
    string_constant_8 = STATIC_STRING("No more drawing elements to pop.");
    string_constant_9 = STATIC_STRING("No more layers to delete.");
    array_constant_6 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)29L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)32L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)39L,(SI_Long)57344L);
    Qstippled_area = STATIC_SYMBOL("STIPPLED-AREA",AB_package);
    Qicon_editor = STATIC_SYMBOL("ICON-EDITOR",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)29L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)34L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)35L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)39L,(SI_Long)57344L);
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    string_constant_10 = 
	    STATIC_STRING("There is no layer below the current layer to group.");
    array_constant_9 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)22L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)32L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)36L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)37L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)46L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)47L,(SI_Long)57344L);
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    string_constant_11 = 
	    STATIC_STRING("The polygon was rejected because it was not a simple polygon.");
    Qfilled_circle = STATIC_SYMBOL("FILLED-CIRCLE",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)57344L);
    string_constant_12 = STATIC_STRING("for ~a.");
    string_constant_13 = 
	    STATIC_STRING("Nothing in the current layer needs to be filled.");
    string_constant_14 = 
	    STATIC_STRING("Nothing in the current layer needs to be outlined.");
    string_constant_15 = STATIC_STRING("Can\'t fill an empty layer.");
    string_constant_16 = STATIC_STRING("Can\'t outline an empty layer.");
    Qicon_editor_workspace = STATIC_SYMBOL("ICON-EDITOR-WORKSPACE",AB_package);
    temp = adjoin(2,Qicon_editor_workspace,List_of_types_to_be_analyzed);
    List_of_types_to_be_analyzed = temp;
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qcheck_undefined_instances_of_class = 
	    STATIC_SYMBOL("CHECK-UNDEFINED-INSTANCES-OF-CLASS",AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qanalyze_for_consistency_for_icon_editor_workspace = 
	    STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY-FOR-ICON-EDITOR-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qanalyze_for_consistency_for_icon_editor_workspace,
	    STATIC_FUNCTION(analyze_for_consistency_for_icon_editor_workspace,
	    NIL,FALSE,3,3));
    Qanalyze_for_consistency = STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qanalyze_for_consistency_for_icon_editor_workspace);
    set_get(Qicon_editor_workspace,Qanalyze_for_consistency,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qanalyze_for_consistency),
	    Qclasses_which_define);
    temp = CONS(Qicon_editor_workspace,temp_1);
    mutate_global_property(Qanalyze_for_consistency,temp,
	    Qclasses_which_define);
}
