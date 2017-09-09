/* menus.c
 * Input file:  menus.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "menus.h"


DEFINE_VARIABLE_WITH_SYMBOL(Short_menus_qm, Qshort_menus_qm);

Object Menu_string_prop = UNBOUND;

/* DISPLAY-TABLE-P */
Object display_table_p(table)
    Object table;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(117,0);
    sub_class_bit_vector = ISVREF(ISVREF(table,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(table,(SI_Long)1L),(SI_Long)19L);
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Directory_of_built_in_menu_choices, Qdirectory_of_built_in_menu_choices);

/* DEF-GRAMMAR-CHOICES-FOR-MENU-1 */
Object def_grammar_choices_for_menu_1(grammar_category_for_choice,
	    choice_symbols)
    Object grammar_category_for_choice, choice_symbols;
{
    Object choice_symbol, ab_loop_list_, grammar_rule, grammar_rules;
    Object ab_loopvar_, ab_loopvar__1, association_qm, temp, temp_1, push_arg;

    x_note_fn_call(117,1);
    choice_symbol = Nil;
    ab_loop_list_ = choice_symbols;
    grammar_rule = Nil;
    grammar_rules = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    grammar_rule = LIST_2(grammar_category_for_choice,LIST_2(Qquote,
	    choice_symbol));
    ab_loopvar__1 = LIST_1(grammar_rule);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	grammar_rules = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    if (grammar_rules)
	add_grammar_rules_function(grammar_rules);
    choice_symbol = Nil;
    ab_loop_list_ = choice_symbols;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    choice_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    association_qm = assq_function(grammar_category_for_choice,
	    Directory_of_built_in_menu_choices);
    if (association_qm) {
	if ( !TRUEP(memq_function(choice_symbol,CDR(association_qm)))) {
	    temp = nconc2(CDR(association_qm),LIST_1(choice_symbol));
	    M_CDR(association_qm) = temp;
	}
    }
    else {
	temp_1 = LIST_1(choice_symbol);
	push_arg = CONS(grammar_category_for_choice,temp_1);
	temp = CONS(push_arg,Directory_of_built_in_menu_choices);
	Directory_of_built_in_menu_choices = temp;
    }
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(grammar_category_for_choice);
}

/* BUILT-IN-MENU-CHOICE-P */
Object built_in_menu_choice_p varargs_1(int, n)
{
    Object choice_symbol;
    Object grammar_category_for_choice_qm, temp, choice_symbols, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(117,2);
    INIT_ARGS_nonrelocating();
    choice_symbol = REQUIRED_ARG_nonrelocating();
    grammar_category_for_choice_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (grammar_category_for_choice_qm) {
	temp = assq_function(grammar_category_for_choice_qm,
		Directory_of_built_in_menu_choices);
	return memq_function(choice_symbol,CDR(temp));
    }
    else {
	choice_symbols = Nil;
	ab_loop_list_ = Directory_of_built_in_menu_choices;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	choice_symbols = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = memq_function(choice_symbol,choice_symbols);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* RECLAIM-MENU-CHOICE-FUNCTION-VALUE */
Object reclaim_menu_choice_function_value(menu_choice_function,gensymed_symbol)
    Object menu_choice_function, gensymed_symbol;
{
    x_note_fn_call(117,3);
    return VALUES_1(Nil);
}

/* RECLAIM-MENU-CHOICE-ARGLIST-VALUE */
Object reclaim_menu_choice_arglist_value(menu_choice_arglist,gensymed_symbol)
    Object menu_choice_arglist, gensymed_symbol;
{
    x_note_fn_call(117,4);
    reclaim_slot_value_list_1(menu_choice_arglist);
    return VALUES_1(Nil);
}

static Object Qmenus_for_this;     /* menus-for-this */

/* RECLAIM-WHAT-THIS-IS-A-MENU-FOR?-VALUE */
Object reclaim_what_this_is_a_menu_for_qm_value(block_qm,menu_1)
    Object block_qm, menu_1;
{
    x_note_fn_call(117,5);
    if (block_qm)
	set_non_savable_lookup_slot_value(block_qm,Qmenus_for_this,
		delete_slot_value_element_1(menu_1,
		get_lookup_slot_value_given_default(block_qm,
		Qmenus_for_this,Nil)));
    return VALUES_1(Nil);
}

/* RECLAIM-MENU-CELL-CURRENTLY-HIGHLIGHTED?-VALUE */
Object reclaim_menu_cell_currently_highlighted_qm_value(cell,menu_1)
    Object cell, menu_1;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(117,6);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      ISVREF(menu_1,(SI_Long)26L) = Nil;
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-MENU-MOUSE-POINTER-VALUE */
Object reclaim_menu_mouse_pointer_value(mouse_pointer,gensymed_symbol)
    Object mouse_pointer, gensymed_symbol;
{
    x_note_fn_call(117,7);
    release_mouse_pointer_if_any(mouse_pointer);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Menu_parameters, Qmenu_parameters);

/* INITIALIZE-FOR-MENU-PARAMETERS */
Object initialize_for_menu_parameters(menu_parameters)
    Object menu_parameters;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(117,8);
    PUSH_SPECIAL_WITH_SYMBOL(Menu_parameters,Qmenu_parameters,menu_parameters,
	    0);
      frame = Menu_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qmenu_parameters)) {
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
      result = reset_walking_menus_if_needed(Menu_parameters);
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-AFTER-READING-FOR-MENU-PARAMETERS */
Object initialize_after_reading_for_menu_parameters(menu_parameters)
    Object menu_parameters;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(117,9);
    PUSH_SPECIAL_WITH_SYMBOL(Menu_parameters,Qmenu_parameters,menu_parameters,
	    0);
      frame = Menu_parameters;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)4L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qmenu_parameters)) {
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
      result = reset_walking_menus_if_needed(Menu_parameters);
    POP_SPECIAL();
    return result;
}

static Object Qwalking_menus;      /* walking-menus */

/* RESET-WALKING-MENUS-IF-NEEDED */
Object reset_walking_menus_if_needed(menu_parameters)
    Object menu_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(117,10);
    PUSH_SPECIAL_WITH_SYMBOL(Menu_parameters,Qmenu_parameters,menu_parameters,
	    0);
      if (Reading_kb_p && loading_version_3_or_earlier_kb_p()) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Menu_parameters,Qwalking_menus);
	  result = set_lookup_slot_value_1(Menu_parameters,Qwalking_menus,Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qif_different;       /* if-different */

static Object array_constant;      /* # */

/* WRITE-WHEN-TO-ALLOW-MULTIPLE-MENUS-FROM-SLOT */
Object write_when_to_allow_multiple_menus_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(117,11);
    if (EQ(value,Qif_different))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)24L));
    else
	return twrite_symbol(1,value);
}

static Object Qleft;               /* left */

static Object Qfat_left_aligned_menu_item_format;  /* fat-left-aligned-menu-item-format */

static Object Qcenter;             /* center */

static Object Qfat_center_aligned_menu_item_format;  /* fat-center-aligned-menu-item-format */

static Object Qright;              /* right */

static Object Qfat_right_aligned_menu_item_format;  /* fat-right-aligned-menu-item-format */

static Object Qleft_aligned_menu_item_format;  /* left-aligned-menu-item-format */

static Object Qcenter_aligned_menu_item_format;  /* center-aligned-menu-item-format */

static Object Qright_aligned_menu_item_format;  /* right-aligned-menu-item-format */

/* CHOOSE-MENU-ITEM-FORMAT-PER-MENU-PARAMETERS */
Object choose_menu_item_format_per_menu_parameters(fat_p)
    Object fat_p;
{
    Object temp;

    x_note_fn_call(117,12);
    if (fat_p) {
	temp = ISVREF(Menu_parameters,(SI_Long)22L);
	if (EQ(temp,Qleft))
	    return VALUES_1(Qfat_left_aligned_menu_item_format);
	else if (EQ(temp,Qcenter))
	    return VALUES_1(Qfat_center_aligned_menu_item_format);
	else if (EQ(temp,Qright))
	    return VALUES_1(Qfat_right_aligned_menu_item_format);
	else
	    return VALUES_1(Qnil);
    }
    else {
	temp = ISVREF(Menu_parameters,(SI_Long)22L);
	if (EQ(temp,Qleft))
	    return VALUES_1(Qleft_aligned_menu_item_format);
	else if (EQ(temp,Qcenter))
	    return VALUES_1(Qcenter_aligned_menu_item_format);
	else if (EQ(temp,Qright))
	    return VALUES_1(Qright_aligned_menu_item_format);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qleft_aligned_cascade_menu_item_format;  /* left-aligned-cascade-menu-item-format */

static Object Qcenter_aligned_cascade_menu_item_format;  /* center-aligned-cascade-menu-item-format */

static Object Qright_aligned_cascade_menu_item_format;  /* right-aligned-cascade-menu-item-format */

/* CHOOSE-CASCADE-MENU-ITEM-FORMAT-PER-MENU-PARAMETERS */
Object choose_cascade_menu_item_format_per_menu_parameters()
{
    Object temp;

    x_note_fn_call(117,13);
    temp = ISVREF(Menu_parameters,(SI_Long)22L);
    if (EQ(temp,Qleft))
	return VALUES_1(Qleft_aligned_cascade_menu_item_format);
    else if (EQ(temp,Qcenter))
	return VALUES_1(Qcenter_aligned_cascade_menu_item_format);
    else if (EQ(temp,Qright))
	return VALUES_1(Qright_aligned_cascade_menu_item_format);
    else
	return VALUES_1(Qnil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qleft_aligned_cascade_menu_item_format_new_large;  /* left-aligned-cascade-menu-item-format-new-large */

static Object Qnew_large_right;    /* new-large-right */

static Object Qleft_aligned_cascade_menu_item_format_new_small;  /* left-aligned-cascade-menu-item-format-new-small */

static Object Qnew_small_right;    /* new-small-right */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_large;  /* left-arrow-left-aligned-cascade-menu-item-format-new-large */

static Object Qnew_large_left;     /* new-large-left */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_small;  /* left-arrow-left-aligned-cascade-menu-item-format-new-small */

static Object Qnew_small_left;     /* new-small-left */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format;  /* left-arrow-left-aligned-cascade-menu-item-format */

static Object Qold_left;           /* old-left */

static Object Qold_right;          /* old-right */

static Object Qright_marker_for_cascading_menu;  /* right-marker-for-cascading-menu */

static Object Qleft_marker_for_cascading_menu;  /* left-marker-for-cascading-menu */

/* DRAW-CASCADING-MENU-MARKER */
Object draw_cascading_menu_marker(text_box_qm,color_change_case_qm,
	    highlight_or_new_background_color_qm,new_text_color_qm,
	    text_box_format,text_cell_plist,
	    unhighlighted_background_color_value,
	    cell_background_color_difference,left_edge_of_cell_in_window,
	    top_edge_of_cell_in_window,right_edge_of_cell_in_window,
	    bottom_edge_of_cell_in_window)
    Object text_box_qm, color_change_case_qm;
    Object highlight_or_new_background_color_qm, new_text_color_qm;
    Object text_box_format, text_cell_plist;
    Object unhighlighted_background_color_value;
    Object cell_background_color_difference, left_edge_of_cell_in_window;
    Object top_edge_of_cell_in_window, right_edge_of_cell_in_window;
    Object bottom_edge_of_cell_in_window;
{
    Object temp, position_type, old_position_format, scale;
    Object right_edge_in_workspace, left_edge_in_workspace, value_1;
    Object top_edge_in_workspace;
    SI_Long gensymed_symbol, gensymed_symbol_1, value, temp_1;

    x_note_fn_call(117,14);
    temp = get_lookup_slot_value_given_default(text_box_format,
	    Qname_or_names_for_frame,Nil);
    if (EQ(temp,Qleft_aligned_cascade_menu_item_format_new_large))
	position_type = Qnew_large_right;
    else if (EQ(temp,Qleft_aligned_cascade_menu_item_format_new_small))
	position_type = Qnew_small_right;
    else if (EQ(temp,
	    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large))
	position_type = Qnew_large_left;
    else if (EQ(temp,
	    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small))
	position_type = Qnew_small_left;
    else if (EQ(temp,Qleft_arrow_left_aligned_cascade_menu_item_format))
	position_type = Qold_left;
    else
	position_type = Qold_right;
    old_position_format = EQ(position_type,Qold_left) ? T : Nil;
    if (old_position_format);
    else
	old_position_format = EQ(position_type,Qold_right) ? T : Nil;
    scale = Current_image_x_scale;
    gensymed_symbol = old_position_format ? 
	    IFIX(right_edge_of_cell_in_window) : 
	    IFIX(ISVREF(Current_image_plane,(SI_Long)21L));
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    value = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	right_edge_in_workspace = FIX(value);
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	right_edge_in_workspace = inverse_scalef_function(scale,FIX(value));
    else if (value >= (SI_Long)0L) {
	temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	right_edge_in_workspace = temp;
    }
    else {
	temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	right_edge_in_workspace = temp;
    }
    scale = Current_image_x_scale;
    gensymed_symbol = old_position_format ? 
	    IFIX(left_edge_of_cell_in_window) : 
	    IFIX(ISVREF(Current_image_plane,(SI_Long)19L));
    gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
    value = gensymed_symbol - gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	left_edge_in_workspace = FIX(value);
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	left_edge_in_workspace = inverse_scalef_function(scale,FIX(value));
    else if (value >= (SI_Long)0L) {
	temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
	left_edge_in_workspace = temp;
    }
    else {
	temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	left_edge_in_workspace = temp;
    }
    scale = Current_image_y_scale;
    value_1 = FIXNUM_MINUS(top_edge_of_cell_in_window,
	    Current_y_origin_of_drawing);
    if (IFIX(scale) == (SI_Long)4096L)
	top_edge_in_workspace = value_1;
    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value_1) 
	    && FIXNUM_LT(value_1,Isqrt_of_most_positive_fixnum)))
	top_edge_in_workspace = inverse_scalef_function(scale,value_1);
    else if (IFIX(value_1) >= (SI_Long)0L) {
	temp = FIX(((IFIX(value_1) << (SI_Long)12L) + (IFIX(scale) >>  -  
		- (SI_Long)1L)) / IFIX(scale));
	top_edge_in_workspace = temp;
    }
    else {
	temp_1 = ((IFIX(FIXNUM_NEGATE(value_1)) << (SI_Long)12L) + 
		(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
	top_edge_in_workspace = temp;
    }
    if (EQ(position_type,Qnew_large_right))
	draw_rubber_stamp_widget(Qright_marker_for_cascading_menu,
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)12L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)7L),
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)5L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)17L));
    else if (EQ(position_type,Qnew_small_right))
	draw_rubber_stamp_widget(Qright_marker_for_cascading_menu,
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)12L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)5L),
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)5L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)14L));
    else if (EQ(position_type,Qnew_large_left))
	draw_rubber_stamp_widget(Qleft_marker_for_cascading_menu,
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)5L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)7L),
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)12L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)17L));
    else if (EQ(position_type,Qnew_small_left))
	draw_rubber_stamp_widget(Qleft_marker_for_cascading_menu,
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)5L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)5L),
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)12L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)14L));
    else if (EQ(position_type,Qold_right))
	draw_rubber_stamp_widget(Qright_marker_for_cascading_menu,
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)14L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)7L),
		FIX(IFIX(right_edge_in_workspace) - (SI_Long)4L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)17L));
    else if (EQ(position_type,Qold_left))
	draw_rubber_stamp_widget(Qleft_marker_for_cascading_menu,
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)4L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)7L),
		FIX(IFIX(left_edge_in_workspace) + (SI_Long)14L),
		FIX(IFIX(top_edge_in_workspace) + (SI_Long)17L));
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_menu_heading_format_names, Qall_menu_heading_format_names);

/* MENU-HEADING-TEXT-CELL-P */
Object menu_heading_text_cell_p(text_cell)
    Object text_cell;
{
    Object temp;

    x_note_fn_call(117,15);
    temp = get_lookup_slot_value_given_default(CAR(text_cell),
	    Qname_or_names_for_frame,Nil);
    return memq_function(temp,All_menu_heading_format_names);
}

static Object Qfat_left_aligned_menu_heading_format;  /* fat-left-aligned-menu-heading-format */

static Object Qfat_center_aligned_menu_heading_format;  /* fat-center-aligned-menu-heading-format */

static Object Qfat_right_aligned_menu_heading_format;  /* fat-right-aligned-menu-heading-format */

static Object Qleft_aligned_menu_heading_format;  /* left-aligned-menu-heading-format */

static Object Qcenter_aligned_menu_heading_format;  /* center-aligned-menu-heading-format */

static Object Qright_aligned_menu_heading_format;  /* right-aligned-menu-heading-format */

/* CHOOSE-MENU-HEADING-FORMAT-PER-MENU-PARAMETERS */
Object choose_menu_heading_format_per_menu_parameters varargs_1(int, n)
{
    Object fat_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(117,16);
    INIT_ARGS_nonrelocating();
    fat_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (fat_p) {
	temp = ISVREF(Menu_parameters,(SI_Long)22L);
	if (EQ(temp,Qleft))
	    return VALUES_1(Qfat_left_aligned_menu_heading_format);
	else if (EQ(temp,Qcenter))
	    return VALUES_1(Qfat_center_aligned_menu_heading_format);
	else if (EQ(temp,Qright))
	    return VALUES_1(Qfat_right_aligned_menu_heading_format);
	else
	    return VALUES_1(Qnil);
    }
    else {
	temp = ISVREF(Menu_parameters,(SI_Long)22L);
	if (EQ(temp,Qleft))
	    return VALUES_1(Qleft_aligned_menu_heading_format);
	else if (EQ(temp,Qcenter))
	    return VALUES_1(Qcenter_aligned_menu_heading_format);
	else if (EQ(temp,Qright))
	    return VALUES_1(Qright_aligned_menu_heading_format);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qleft_aligned_color_menu_item_format;  /* left-aligned-color-menu-item-format */

static Object Qcenter_aligned_color_menu_item_format;  /* center-aligned-color-menu-item-format */

static Object Qright_aligned_color_menu_item_format;  /* right-aligned-color-menu-item-format */

/* CHOOSE-COLOR-MENU-ITEM-FORMAT-PER-MENU-PARAMETERS */
Object choose_color_menu_item_format_per_menu_parameters()
{
    Object temp;

    x_note_fn_call(117,17);
    temp = ISVREF(Menu_parameters,(SI_Long)22L);
    if (EQ(temp,Qleft))
	return VALUES_1(Qleft_aligned_color_menu_item_format);
    else if (EQ(temp,Qcenter))
	return VALUES_1(Qcenter_aligned_color_menu_item_format);
    else if (EQ(temp,Qright))
	return VALUES_1(Qright_aligned_color_menu_item_format);
    else
	return VALUES_1(Qnil);
}

Object The_type_description_of_entire_menu_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_entire_menu_spots, Qchain_of_available_entire_menu_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Entire_menu_spot_count, Qentire_menu_spot_count);

Object Chain_of_available_entire_menu_spots_vector = UNBOUND;

/* ENTIRE-MENU-SPOT-STRUCTURE-MEMORY-USAGE */
Object entire_menu_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(117,18);
    temp = Entire_menu_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ENTIRE-MENU-SPOT-COUNT */
Object outstanding_entire_menu_spot_count()
{
    Object def_structure_entire_menu_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(117,19);
    gensymed_symbol = IFIX(Entire_menu_spot_count);
    def_structure_entire_menu_spot_variable = 
	    Chain_of_available_entire_menu_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_entire_menu_spot_variable))
	goto end_loop;
    def_structure_entire_menu_spot_variable = 
	    ISVREF(def_structure_entire_menu_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ENTIRE-MENU-SPOT-1 */
Object reclaim_entire_menu_spot_1(entire_menu_spot)
    Object entire_menu_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(117,20);
    inline_note_reclaim_cons(entire_menu_spot,Nil);
    structure_being_reclaimed = entire_menu_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(entire_menu_spot,(SI_Long)2L));
      SVREF(entire_menu_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_entire_menu_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(entire_menu_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_entire_menu_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = entire_menu_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ENTIRE-MENU-SPOT */
Object reclaim_structure_for_entire_menu_spot(entire_menu_spot)
    Object entire_menu_spot;
{
    x_note_fn_call(117,21);
    return reclaim_entire_menu_spot_1(entire_menu_spot);
}

static Object Qg2_defstruct_structure_name_entire_menu_spot_g2_struct;  /* g2-defstruct-structure-name::entire-menu-spot-g2-struct */

/* MAKE-PERMANENT-ENTIRE-MENU-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_entire_menu_spot_structure_internal()
{
    Object def_structure_entire_menu_spot_variable;
    Object defstruct_g2_entire_menu_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(117,22);
    def_structure_entire_menu_spot_variable = Nil;
    atomic_incff_symval(Qentire_menu_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_entire_menu_spot_variable = Nil;
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
	defstruct_g2_entire_menu_spot_variable = the_array;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_menu_spot_g2_struct;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_entire_menu_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_entire_menu_spot_variable = 
		defstruct_g2_entire_menu_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_entire_menu_spot_variable);
}

/* MAKE-ENTIRE-MENU-SPOT-1 */
Object make_entire_menu_spot_1()
{
    Object def_structure_entire_menu_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(117,23);
    def_structure_entire_menu_spot_variable = 
	    ISVREF(Chain_of_available_entire_menu_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_entire_menu_spot_variable) {
	svref_arg_1 = Chain_of_available_entire_menu_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_entire_menu_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_menu_spot_g2_struct;
    }
    else
	def_structure_entire_menu_spot_variable = 
		make_permanent_entire_menu_spot_structure_internal();
    inline_note_allocate_cons(def_structure_entire_menu_spot_variable,Nil);
    SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_entire_menu_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_entire_menu_spot_variable);
}

Object The_type_description_of_entire_focus_menu_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_entire_focus_menu_spots, Qchain_of_available_entire_focus_menu_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Entire_focus_menu_spot_count, Qentire_focus_menu_spot_count);

Object Chain_of_available_entire_focus_menu_spots_vector = UNBOUND;

/* ENTIRE-FOCUS-MENU-SPOT-STRUCTURE-MEMORY-USAGE */
Object entire_focus_menu_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(117,24);
    temp = Entire_focus_menu_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ENTIRE-FOCUS-MENU-SPOT-COUNT */
Object outstanding_entire_focus_menu_spot_count()
{
    Object def_structure_entire_focus_menu_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(117,25);
    gensymed_symbol = IFIX(Entire_focus_menu_spot_count);
    def_structure_entire_focus_menu_spot_variable = 
	    Chain_of_available_entire_focus_menu_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_entire_focus_menu_spot_variable))
	goto end_loop;
    def_structure_entire_focus_menu_spot_variable = 
	    ISVREF(def_structure_entire_focus_menu_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ENTIRE-FOCUS-MENU-SPOT-1 */
Object reclaim_entire_focus_menu_spot_1(entire_focus_menu_spot)
    Object entire_focus_menu_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(117,26);
    inline_note_reclaim_cons(entire_focus_menu_spot,Nil);
    structure_being_reclaimed = entire_focus_menu_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(entire_focus_menu_spot,(SI_Long)2L));
      SVREF(entire_focus_menu_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_entire_focus_menu_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(entire_focus_menu_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_entire_focus_menu_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = entire_focus_menu_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ENTIRE-FOCUS-MENU-SPOT */
Object reclaim_structure_for_entire_focus_menu_spot(entire_focus_menu_spot)
    Object entire_focus_menu_spot;
{
    x_note_fn_call(117,27);
    return reclaim_entire_focus_menu_spot_1(entire_focus_menu_spot);
}

static Object Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct;  /* g2-defstruct-structure-name::entire-focus-menu-spot-g2-struct */

/* MAKE-PERMANENT-ENTIRE-FOCUS-MENU-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_entire_focus_menu_spot_structure_internal()
{
    Object def_structure_entire_focus_menu_spot_variable;
    Object defstruct_g2_entire_focus_menu_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(117,28);
    def_structure_entire_focus_menu_spot_variable = Nil;
    atomic_incff_symval(Qentire_focus_menu_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_entire_focus_menu_spot_variable = Nil;
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
	defstruct_g2_entire_focus_menu_spot_variable = the_array;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_entire_focus_menu_spot_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_entire_focus_menu_spot_variable = 
		defstruct_g2_entire_focus_menu_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_entire_focus_menu_spot_variable);
}

/* MAKE-ENTIRE-FOCUS-MENU-SPOT-1 */
Object make_entire_focus_menu_spot_1()
{
    Object def_structure_entire_focus_menu_spot_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(117,29);
    def_structure_entire_focus_menu_spot_variable = 
	    ISVREF(Chain_of_available_entire_focus_menu_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_entire_focus_menu_spot_variable) {
	svref_arg_1 = Chain_of_available_entire_focus_menu_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_entire_focus_menu_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_entire_focus_menu_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct;
    }
    else
	def_structure_entire_focus_menu_spot_variable = 
		make_permanent_entire_focus_menu_spot_structure_internal();
    inline_note_allocate_cons(def_structure_entire_focus_menu_spot_variable,
	    Nil);
    SVREF(def_structure_entire_focus_menu_spot_variable,FIX((SI_Long)1L)) 
	    = Nil;
    SVREF(def_structure_entire_focus_menu_spot_variable,FIX((SI_Long)2L)) 
	    = Nil;
    SVREF(def_structure_entire_focus_menu_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_entire_focus_menu_spot_variable,FIX((SI_Long)4L)) 
	    = Nil;
    SVREF(def_structure_entire_focus_menu_spot_variable,FIX((SI_Long)5L)) 
	    = Nil;
    return VALUES_1(def_structure_entire_focus_menu_spot_variable);
}

/* GENERATE-SPOT-FOR-MENU-WORKSPACE */
Object generate_spot_for_menu_workspace(menu_workspace,mouse_pointer)
    Object menu_workspace, mouse_pointer;
{
    Object temp;

    x_note_fn_call(117,30);
    temp = generate_spot_if_in_workspace_frame(menu_workspace,mouse_pointer);
    if (temp)
	return VALUES_1(temp);
    else {
	temp = EQ(menu_workspace,ISVREF(Current_workstation,(SI_Long)8L)) ?
		 make_entire_focus_menu_spot_1() : make_entire_menu_spot_1();
	return push_more_detailed_spot(mouse_pointer,temp,
		first_subblock(menu_workspace));
    }
}

static Object Qalways;             /* always */

static Object Qreason_to_not_recycle_menu;  /* reason-to-not-recycle-menu */

static Object Qnever;              /* never */

static Object Qwhat_this_is_a_menu_for_qm;  /* what-this-is-a-menu-for? */

/* FIND-MENU-WORKSPACE-TO-DISMISS */
Object find_menu_workspace_to_dismiss(menu_workspace)
    Object menu_workspace;
{
    Object menu_1, when_to_allow_multiple_menus, image_plane, ab_loop_list_;
    Object workspace_qm, sub_class_bit_vector, other_menu, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(117,31);
    menu_1 = first_subblock(menu_workspace);
    when_to_allow_multiple_menus = ISVREF(Menu_parameters,(SI_Long)23L);
    if ( !EQ(when_to_allow_multiple_menus,Qalways)) {
	image_plane = Nil;
	ab_loop_list_ = ISVREF(Current_workstation_detail_pane,(SI_Long)5L);
	workspace_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	image_plane = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	workspace_qm = ISVREF(image_plane,(SI_Long)5L);
	if (workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Menu_workspace_class_description,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    other_menu = first_subblock(workspace_qm);
	    if ( !TRUEP(get_lookup_slot_value_given_default(other_menu,
		    Qreason_to_not_recycle_menu,Nil))) {
		temp = EQ(when_to_allow_multiple_menus,Qnever);
		if (temp);
		else {
		    temp_1 = get_lookup_slot_value_given_default(menu_1,
			    Qwhat_this_is_a_menu_for_qm,Nil);
		    temp = EQ(temp_1,
			    get_lookup_slot_value_given_default(other_menu,
			    Qwhat_this_is_a_menu_for_qm,Nil));
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return VALUES_2(workspace_qm,image_plane);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~a-~a-~a" */

static Object Qab_format;          /* format */

/* POST-MENU-WORKSPACE */
Object post_menu_workspace varargs_1(int, n)
{
    Object menu_workspace, x_in_window, y_in_window;
    Object allow_multiple_menus_qm, default_x_scale_qm, default_y_scale_qm;
    Object x_for_left_adjusting_qm, x_for_right_adjusting_qm;
    Object direction_for_adjusting_qm, other_menu_workspace_qm, image_plane_qm;
    Object current_draw_paper_p, adjustment, fsn, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, gensymed_symbol, gensymed_symbol_1, ab_loop_iter_flag_;
    Object gensymed_symbol_3, third_arg;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_repeat_;
    SI_Long gensymed_symbol_2, ab_loop_bind_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(6);
    Object result;

    x_note_fn_call(117,32);
    INIT_ARGS_nonrelocating();
    menu_workspace = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    allow_multiple_menus_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_x_scale_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_y_scale_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_for_left_adjusting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_for_right_adjusting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    direction_for_adjusting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(allow_multiple_menus_qm))
	result = find_menu_workspace_to_dismiss(menu_workspace);
    else
	result = VALUES_1(Nil);
    MVS_2(result,other_menu_workspace_qm,image_plane_qm);
    current_draw_paper_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
	    5);
      result = post_workspace_in_pane_function(menu_workspace,
	      Current_workstation_detail_pane,x_in_window,y_in_window,
	      image_plane_qm,default_x_scale_qm,default_y_scale_qm,
	      x_for_left_adjusting_qm,x_for_right_adjusting_qm,
	      direction_for_adjusting_qm);
      adjustment = NTH_VALUE((SI_Long)1L, result);
      if (other_menu_workspace_qm)
	  delete_menu(other_menu_workspace_qm);
      if ((EQ(direction_for_adjusting_qm,Qleft) || 
	      EQ(direction_for_adjusting_qm,Qright)) &&  !EQ(adjustment,
	      direction_for_adjusting_qm)) {
	  delete_menu(menu_workspace);
	  result = VALUES_2(Nil,adjustment);
	  POP_SPECIAL();
	  goto end_post_menu_workspace;
      }
      force_workspace_drawing(menu_workspace);
      fsn = ISVREF(menu_workspace,(SI_Long)3L);
      if (IFIX(mod(FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
	      M_CDR(fsn)),FIX((SI_Long)11L))) == (SI_Long)0L ? 
	      TRUEP(G2_has_been_started_qm) : TRUEP(Nil)) {
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(4,string_constant,Qab_format,
			    CAR(Format_redefinition_list),
			    SECOND(Format_redefinition_list));
		    temp = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensymed_symbol = SYMBOL_VALUE(intern_text_string(1,temp));
	  ab_loop_repeat_ = (SI_Long)15L;
	  gensymed_symbol_1 = gensymed_symbol;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !((SI_Long)0L < ab_loop_repeat_))
	      goto end_loop;
	  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	  if ( !TRUEP(ab_loop_iter_flag_))
	      gensymed_symbol_1 = CDR(gensymed_symbol_1);
	  if (ATOM(gensymed_symbol_1)) {
	      temp_1 = TRUEP(Nil);
	      goto end_1;
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(T);
	  goto end_1;
	  temp_1 = TRUEP(Qnil);
	end_1:;
	  if (temp_1) {
	      gensymed_symbol_1 = FOURTH(gensymed_symbol);
	      gensymed_symbol = SECOND(gensymed_symbol);
	      temp_1 =  !SIMPLE_VECTOR_P(gensymed_symbol_1);
	      if (temp_1);
	      else
		  temp_1 =  !(IFIX(length(gensymed_symbol_1)) >= (SI_Long)8L);
	      if (temp_1);
	      else {
		  gensymed_symbol_2 = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(length(gensymed_symbol_1));
		  gensymed_symbol_3 = Nil;
		next_loop_1:
		  if (gensymed_symbol_2 >= ab_loop_bind_)
		      goto end_loop_1;
		  gensymed_symbol_3 = ISVREF(gensymed_symbol_1,
			  gensymed_symbol_2);
		  if ( !(FIXNUMP(gensymed_symbol_3) && (SI_Long)0L <= 
			  IFIX(gensymed_symbol_3) && 
			  IFIX(gensymed_symbol_3) <= (SI_Long)255L)) {
		      temp_1 = TRUEP(Nil);
		      goto end_2;
		  }
		  gensymed_symbol_2 = gensymed_symbol_2 + (SI_Long)1L;
		  goto next_loop_1;
		end_loop_1:
		  temp_1 = TRUEP(T);
		  goto end_2;
		  temp_1 = TRUEP(Qnil);
		end_2:;
		  temp_1 =  !temp_1;
	      }
	      if (temp_1);
	      else
		  temp_1 =  
			  !TRUEP(match_machine_id_for_this_machine_online(gensymed_symbol,
			  gensymed_symbol_1));
	      temp = temp_1 ? Nil : T;
	      gensymed_symbol = Nil;
	      gensymed_symbol_1 = Nil;
	      gensymed_symbol = Nil;
	      temp_1 = TRUEP(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1) {
	      third_arg = Default_format_structure;
	      M_THIRD(third_arg) = T;
	  }
      }
      result = VALUES_2(menu_workspace,adjustment);
    POP_SPECIAL();
  end_post_menu_workspace:
    return result;
}

/* MAKE-TABLE-SPANNING-ROW */
Object make_table_spanning_row varargs_1(int, n)
{
    Object text_cell;
    Object number_of_columns, temp, list_1, sublist, car_arg;
    Declare_varargs_nonrelocating;

    x_note_fn_call(117,33);
    INIT_ARGS_nonrelocating();
    text_cell = REQUIRED_ARG_nonrelocating();
    number_of_columns = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = number_of_columns;
    if (temp);
    else
	temp = FIX((SI_Long)1L);
    list_1 = make_slot_value_list_1(temp);
    sublist = list_1;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    M_CAR(sublist) = Nil;
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:;
    car_arg = last(list_1,_);
    M_CAR(car_arg) = text_cell;
    return VALUES_1(list_1);
}

static Object array_constant_1;    /* # */

static Object Qformat_frame;       /* format-frame */

static Object Qmenu_spacer_format;  /* menu-spacer-format */

/* MAKE-TABLE-SPACER-CELLS */
Object make_table_spacer_cells varargs_1(int, n)
{
    Object count_1, number_of_columns, temp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1;
    SI_Long ab_loop_repeat_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(117,34);
    INIT_ARGS_nonrelocating();
    count_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    number_of_columns = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = count_1;
    if (temp);
    else
	temp = FIX((SI_Long)3L);
    ab_loop_repeat_ = IFIX(temp);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    temp_1 = 
	    slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_1,
	    FIX((SI_Long)0L)),Nil);
    temp = get_instance_with_name_if_any(Qformat_frame,Qmenu_spacer_format);
    if (temp);
    else
	temp = make_format_frame(Qmenu_spacer_format);
    ab_loopvar__2 = slot_value_cons_1(make_table_spanning_row(2,
	    make_text_cell(2,temp_1,temp),number_of_columns),Nil);
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

/* MENU-SPACER-CELL-P */
Object menu_spacer_cell_p(text_cell)
    Object text_cell;
{
    x_note_fn_call(117,35);
    if (CAR(text_cell))
	return VALUES_1(EQ(get_lookup_slot_value_given_default(CAR(text_cell),
		Qname_or_names_for_frame,Nil),Qmenu_spacer_format) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* DELETE-MENU */
Object delete_menu(menu_or_menu_workspace)
    Object menu_or_menu_workspace;
{
    Object gensymed_symbol;

    x_note_fn_call(117,36);
    gensymed_symbol = ACCESS_ONCE(ISVREF(menu_or_menu_workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    if (gensymed_symbol) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(menu_or_menu_workspace,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	return delete_frame(gensymed_symbol);
    }
    else
	return delete_frame(menu_or_menu_workspace);
}

static Object array_constant_2;    /* # */

/* TWRITE-MENU-BACKTRACE-INFO */
Object twrite_menu_backtrace_info()
{
    Object temp, index_of_top_of_backtrace_stack_new_value;

    x_note_fn_call(117,37);
    twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)10L));
    if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
	temp = Nil;
    else {
	temp = ISVREF(Backtrace_stack_for_internal_error,
		IFIX(Index_of_top_of_backtrace_stack));
	index_of_top_of_backtrace_stack_new_value = 
		FIXNUM_SUB1(Index_of_top_of_backtrace_stack);
	Index_of_top_of_backtrace_stack = 
		index_of_top_of_backtrace_stack_new_value;
    }
    return twrite_symbol(1,temp);
}

Object Highlight_selected_menu_items_qm = UNBOUND;

static Object Qtable;              /* table */

/* PICK-CELL-FROM-TABLE */
Object pick_cell_from_table varargs_1(int, n)
{
    Object table, image_plane, x_in_window, y_in_window;
    Object only_if_in_text_qm, find_nearest_cell_qm;
    Object consider_cell_visibility_qm, x_in_workspace, y_in_workspace;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, value, temp, image_x_scale;
    Object image_y_scale, table_format, gensymed_symbol, frame, symbol;
    Object sub_class_bit_vector, format_of_superblock_if_a_table_qm;
    Object left_border_width, x_in_workspace_1, top_border_width;
    Object y_in_workspace_1, right_border_width, bottom_edge_of_table;
    Object bottom_border_width, row_boundary_width, column_boundary_width;
    Object remaining_row_edges, nearest_cell_so_far_qm;
    Object nearest_cell_distance_so_far, row_index_of_nearest_cell;
    Object column_row_index_of_nearest_cell, left_edge_of_nearest_cell;
    Object top_edge_of_nearest_cell, right_edge_of_nearest_cell;
    Object bottom_edge_of_nearest_cell, row, ab_loop_list_, top_edge_of_cell;
    Object top_edge_of_cell_in_window, bottom_edge_of_cell;
    Object bottom_edge_of_cell_in_window, top_edge_of_next_cell_in_window;
    Object ab_loop_iter_flag_, remaining_row_edges_old_value;
    Object remaining_column_edges, remainder_of_row, column_index;
    Object left_edge_of_cell, left_edge_of_cell_in_window, cell;
    Object right_edge_of_cell, right_edge_of_cell_in_window;
    Object left_edge_of_next_cell_in_window, remaining_column_edges_old_value;
    Object ab_loop_it_, remainder_of_row_old_value, reasonable_distance;
    Object left_edge, top_edge, right_edge, bottom_edge;
    Object distance_if_in_range_qm, d1, d2, distance_if_reasonable_qm;
    SI_Long temp_1, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long unshifted_result, left_edge_of_table_in_window;
    SI_Long left_edge_of_table_interior_in_window, top_edge_of_table_in_window;
    SI_Long top_edge_of_table_interior_in_window;
    SI_Long right_edge_of_table_in_window;
    SI_Long right_edge_of_table_interior_in_window;
    SI_Long bottom_edge_of_table_in_window;
    SI_Long bottom_edge_of_table_interior_in_window;
    SI_Long row_boundary_width_in_window, column_boundary_width_in_window;
    SI_Long row_index;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(117,38);
    INIT_ARGS_nonrelocating();
    table = REQUIRED_ARG_nonrelocating();
    image_plane = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    only_if_in_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    find_nearest_cell_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    consider_cell_visibility_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    x_in_workspace = Nil;
    y_in_workspace = Nil;
    current_frame_transform_qm = Nil;
    current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
    current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
		    0);
	      scale = Current_image_x_scale;
	      value = FIXNUM_MINUS(x_in_window,Current_x_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  x_in_workspace = value;
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  x_in_workspace = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale));
		  x_in_workspace = temp;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp = FIXNUM_NEGATE(FIX(temp_1));
		  x_in_workspace = temp;
	      }
	      scale = Current_image_y_scale;
	      value = FIXNUM_MINUS(y_in_window,Current_y_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  y_in_workspace = value;
	      else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		      value) && FIXNUM_LT(value,
		      Isqrt_of_most_positive_fixnum)))
		  y_in_workspace = inverse_scalef_function(scale,value);
	      else if (IFIX(value) >= (SI_Long)0L) {
		  temp = FIX(((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			  >>  -  - (SI_Long)1L)) / IFIX(scale));
		  y_in_workspace = temp;
	      }
	      else {
		  temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			  (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		  temp = FIXNUM_NEGATE(FIX(temp_1));
		  y_in_workspace = temp;
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    table_format = ISVREF(table,(SI_Long)16L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(table,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    frame = gensymed_symbol;
    symbol = Qtable;
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
	    temp_2 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(table,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	format_of_superblock_if_a_table_qm = ISVREF(gensymed_symbol,
		(SI_Long)16L);
    }
    else
	format_of_superblock_if_a_table_qm = Nil;
    left_border_width = format_of_superblock_if_a_table_qm && 
	    IFIX(ISVREF(format_of_superblock_if_a_table_qm,(SI_Long)31L)) 
	    > (SI_Long)0L ? FIX((SI_Long)0L) : ISVREF(table_format,
	    (SI_Long)24L);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    x_in_workspace_1 = gensymed_symbol;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
    scale = ISVREF(image_plane,(SI_Long)11L);
    value = x_in_workspace_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    left_edge_of_table_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = left_edge_of_table_in_window;
    if (IFIX(left_border_width) == (SI_Long)0L)
	gensymed_symbol_2 = (SI_Long)0L;
    else {
	gensymed_symbol_2 = (SI_Long)1L;
	if (IFIX(image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(left_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_x_scale) && FIXNUM_LT(image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		left_border_width) && FIXNUM_LT(left_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_x_scale,
		    left_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(image_x_scale,
		    left_border_width));
	gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    }
    left_edge_of_table_interior_in_window = gensymed_symbol_1 + 
	    gensymed_symbol_2;
    top_border_width = format_of_superblock_if_a_table_qm && 
	    IFIX(ISVREF(format_of_superblock_if_a_table_qm,(SI_Long)29L)) 
	    > (SI_Long)0L ? FIX((SI_Long)0L) : ISVREF(table_format,
	    (SI_Long)25L);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    y_in_workspace_1 = gensymed_symbol;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
    scale = ISVREF(image_plane,(SI_Long)12L);
    value = y_in_workspace_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    top_edge_of_table_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = top_edge_of_table_in_window;
    if (IFIX(top_border_width) == (SI_Long)0L)
	gensymed_symbol_2 = (SI_Long)0L;
    else {
	gensymed_symbol_2 = (SI_Long)1L;
	if (IFIX(image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(top_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_y_scale) && FIXNUM_LT(image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		top_border_width) && FIXNUM_LT(top_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_y_scale,
		    top_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(image_y_scale,
		    top_border_width));
	gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    }
    top_edge_of_table_interior_in_window = gensymed_symbol_1 + 
	    gensymed_symbol_2;
    right_border_width = format_of_superblock_if_a_table_qm && 
	    IFIX(ISVREF(format_of_superblock_if_a_table_qm,(SI_Long)31L)) 
	    > (SI_Long)0L ? FIX((SI_Long)0L) : ISVREF(table_format,
	    (SI_Long)26L);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    x_in_workspace_1 = gensymed_symbol;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
    scale = ISVREF(image_plane,(SI_Long)11L);
    value = x_in_workspace_1;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    right_edge_of_table_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = right_edge_of_table_in_window;
    if (IFIX(right_border_width) == (SI_Long)0L)
	gensymed_symbol_2 = (SI_Long)0L;
    else {
	gensymed_symbol_2 = (SI_Long)1L;
	if (IFIX(image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(right_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_x_scale) && FIXNUM_LT(image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		right_border_width) && FIXNUM_LT(right_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_x_scale,
		    right_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(image_x_scale,
		    right_border_width));
	gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    }
    right_edge_of_table_interior_in_window = gensymed_symbol_1 - 
	    gensymed_symbol_2;
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    bottom_edge_of_table = gensymed_symbol;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
    scale = ISVREF(image_plane,(SI_Long)12L);
    value = bottom_edge_of_table;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = IFIX(value);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,value));
    bottom_edge_of_table_in_window = gensymed_symbol_1 + gensymed_symbol_2;
    bottom_border_width = format_of_superblock_if_a_table_qm && 
	    IFIX(ISVREF(format_of_superblock_if_a_table_qm,(SI_Long)29L)) 
	    > (SI_Long)0L ? FIX((SI_Long)0L) : ISVREF(table_format,
	    (SI_Long)27L);
    gensymed_symbol_1 = bottom_edge_of_table_in_window;
    if (IFIX(bottom_border_width) == (SI_Long)0L)
	gensymed_symbol_2 = (SI_Long)0L;
    else {
	gensymed_symbol_2 = (SI_Long)1L;
	if (IFIX(image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = IFIX(bottom_border_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_y_scale) && FIXNUM_LT(image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		bottom_border_width) && FIXNUM_LT(bottom_border_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_y_scale,
		    bottom_border_width)) + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(image_y_scale,
		    bottom_border_width));
	gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    }
    bottom_edge_of_table_interior_in_window = gensymed_symbol_1 - 
	    gensymed_symbol_2;
    row_boundary_width = ISVREF(table_format,(SI_Long)29L);
    if (IFIX(row_boundary_width) == (SI_Long)0L)
	row_boundary_width_in_window = (SI_Long)0L;
    else {
	gensymed_symbol_1 = (SI_Long)1L;
	if (IFIX(image_y_scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(row_boundary_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_y_scale) && FIXNUM_LT(image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		row_boundary_width) && FIXNUM_LT(row_boundary_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_y_scale,
		    row_boundary_width)) + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(image_y_scale,
		    row_boundary_width));
	row_boundary_width_in_window = MAX(gensymed_symbol_1,
		gensymed_symbol_2);
    }
    column_boundary_width = ISVREF(table_format,(SI_Long)31L);
    if (IFIX(column_boundary_width) == (SI_Long)0L)
	column_boundary_width_in_window = (SI_Long)0L;
    else {
	gensymed_symbol_1 = (SI_Long)1L;
	if (IFIX(image_x_scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(column_boundary_width);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		image_x_scale) && FIXNUM_LT(image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		column_boundary_width) && FIXNUM_LT(column_boundary_width,
		Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(image_x_scale,
		    column_boundary_width)) + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(image_x_scale,
		    column_boundary_width));
	column_boundary_width_in_window = MAX(gensymed_symbol_1,
		gensymed_symbol_2);
    }
    remaining_row_edges = ISVREF(table,(SI_Long)17L);
    nearest_cell_so_far_qm = Nil;
    nearest_cell_distance_so_far = Nil;
    row_index_of_nearest_cell = Nil;
    column_row_index_of_nearest_cell = Nil;
    left_edge_of_nearest_cell = Nil;
    top_edge_of_nearest_cell = Nil;
    right_edge_of_nearest_cell = Nil;
    bottom_edge_of_nearest_cell = Nil;
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,1);
      row_index = (SI_Long)0L;
      gensymed_symbol = ISVREF(table,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_1 = IFIX(gensymed_symbol);
      gensymed_symbol_2 = IFIX(top_border_width);
      top_edge_of_cell = FIX(gensymed_symbol_1 + gensymed_symbol_2);
      top_edge_of_cell_in_window = FIX(top_edge_of_table_interior_in_window);
      bottom_edge_of_cell = Nil;
      bottom_edge_of_cell_in_window = Nil;
      top_edge_of_next_cell_in_window = Nil;
      ab_loop_iter_flag_ = T;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_)) {
	  row_index = row_index + (SI_Long)1L;
	  remaining_row_edges_old_value = remaining_row_edges;
	  temp_1 = IFIX(FIRST(remaining_row_edges_old_value));
	  remaining_row_edges = REST(remaining_row_edges_old_value);
	  gensymed_symbol_1 = temp_1;
	  gensymed_symbol_2 = IFIX(row_boundary_width);
	  top_edge_of_cell = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  top_edge_of_cell_in_window = top_edge_of_next_cell_in_window;
      }
      temp = CAR(remaining_row_edges);
      if (temp);
      else
	  temp = FIXNUM_MINUS(bottom_edge_of_table,bottom_border_width);
      bottom_edge_of_cell = temp;
      if (remaining_row_edges) {
	  gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
	  scale = ISVREF(image_plane,(SI_Long)12L);
	  value = bottom_edge_of_cell;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) 
		  && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		      (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	  bottom_edge_of_cell_in_window = FIX(gensymed_symbol_1 + 
		  gensymed_symbol_2);
      }
      else
	  bottom_edge_of_cell_in_window = 
		  FIX(bottom_edge_of_table_interior_in_window);
      top_edge_of_next_cell_in_window = 
	      FIX(IFIX(bottom_edge_of_cell_in_window) + 
	      row_boundary_width_in_window);
      if ( !FIXNUM_LE(top_edge_of_next_cell_in_window,ISVREF(image_plane,
	      (SI_Long)7L))) {
	  remaining_column_edges = ISVREF(table,(SI_Long)18L);
	  remainder_of_row = Row;
	  column_index = FIX((SI_Long)-1L);
	  gensymed_symbol = ISVREF(table,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = IFIX(left_border_width);
	  left_edge_of_cell = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  left_edge_of_cell_in_window = 
		  FIX(left_edge_of_table_interior_in_window);
	  cell = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
	    right_edge_of_cell = Nil;
	    right_edge_of_cell_in_window = Nil;
	    left_edge_of_next_cell_in_window = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(remainder_of_row))
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		remaining_column_edges_old_value = remaining_column_edges;
		temp_1 = IFIX(FIRST(remaining_column_edges_old_value));
		remaining_column_edges = 
			REST(remaining_column_edges_old_value);
		gensymed_symbol_1 = temp_1;
		gensymed_symbol_2 = IFIX(column_boundary_width);
		left_edge_of_cell = FIX(gensymed_symbol_1 + gensymed_symbol_2);
		left_edge_of_cell_in_window = left_edge_of_next_cell_in_window;
	    }
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    column_index = FIXNUM_ADD1(column_index);
	    remainder_of_row_old_value = remainder_of_row;
	    temp = FIRST(remainder_of_row_old_value);
	    remainder_of_row = REST(remainder_of_row_old_value);
	    ab_loop_it_ = temp;
	    if (ab_loop_it_) {
		Cell = ab_loop_it_;
		goto end_1;
	    }
	    remaining_column_edges_old_value = remaining_column_edges;
	    remaining_column_edges = REST(remaining_column_edges_old_value);
	    goto next_loop_2;
	  end_loop_2:
	    Cell = Qnil;
	  end_1:;
	    temp = CAR(remaining_column_edges);
	    if (temp);
	    else {
		gensymed_symbol = ISVREF(table,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(right_border_width);
		temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    }
	    right_edge_of_cell = temp;
	    if (remaining_column_edges) {
		gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
		scale = ISVREF(image_plane,(SI_Long)11L);
		value = right_edge_of_cell;
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
		right_edge_of_cell_in_window = FIX(gensymed_symbol_1 + 
			gensymed_symbol_2);
	    }
	    else
		right_edge_of_cell_in_window = 
			FIX(right_edge_of_table_interior_in_window);
	    left_edge_of_next_cell_in_window = 
		    FIX(IFIX(right_edge_of_cell_in_window) + 
		    column_boundary_width_in_window);
	    if (FIXNUM_GE(x_in_window,left_edge_of_cell_in_window) && 
		    FIXNUM_GE(y_in_window,top_edge_of_cell_in_window) && 
		    FIXNUM_LE(x_in_window,right_edge_of_cell_in_window) && 
		    FIXNUM_LE(y_in_window,bottom_edge_of_cell_in_window)) {
		if (ATOM(Cell)) {
		    sub_class_bit_vector = ISVREF(ISVREF(Cell,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
			temp_2 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    result = pick_cell_from_table(5,Cell,image_plane,
			    x_in_window,y_in_window,only_if_in_text_qm);
		else if ( !TRUEP(only_if_in_text_qm) || ATOM(Cell) || 
			consider_cell_visibility_qm && 
			text_cell_visible_without_text_in_image_plane_p(Cell,
			image_plane) || find_position_in_text(11,Nil,Cell,
			left_edge_of_cell,top_edge_of_cell,Nil,
			x_in_workspace,y_in_workspace,Nil,Nil,Nil,
			only_if_in_text_qm) && ( 
			!TRUEP(consider_cell_visibility_qm) || 
			text_cell_text_visible_in_image_plane_p(Cell,
			image_plane)))
		    result = VALUES_8(Cell,table,FIX(row_index),
			    column_index,left_edge_of_cell,
			    top_edge_of_cell,right_edge_of_cell,
			    bottom_edge_of_cell);
		else
		    result = VALUES_1(Nil);
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_pick_cell_from_table;
	    }
	    if (find_nearest_cell_qm) {
		if (nearest_cell_so_far_qm)
		    reasonable_distance = nearest_cell_distance_so_far;
		else {
		    temp = FIXNUM_MAX(left_border_width,top_border_width);
		    temp = FIXNUM_MAX(temp,right_border_width);
		    temp = FIXNUM_MAX(temp,bottom_border_width);
		    reasonable_distance = FIXNUM_ADD(temp,
			    mouse_leeway_in_workspace(image_x_scale));
		}
		left_edge = left_edge_of_cell;
		top_edge = top_edge_of_cell;
		right_edge = right_edge_of_cell;
		bottom_edge = bottom_edge_of_cell;
		distance_if_in_range_qm = Nil;
		if (FIXNUM_LT(x_in_workspace,left_edge)) {
		    if (FIXNUM_LT(y_in_workspace,top_edge)) {
			temp = FIXNUM_MINUS(x_in_workspace,left_edge);
			d1 = FIXNUM_ABS(temp);
			temp = FIXNUM_MINUS(y_in_workspace,top_edge);
			d2 = FIXNUM_ABS(temp);
			distance_if_in_range_qm = FIXNUM_LE(d1,
				reasonable_distance) && FIXNUM_LE(d2,
				reasonable_distance) ? 
				isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
				FIXNUM_TIMES(d2,d2))) : Nil;
		    }
		    else if (FIXNUM_GT(y_in_workspace,bottom_edge)) {
			temp = FIXNUM_MINUS(x_in_workspace,left_edge);
			d1 = FIXNUM_ABS(temp);
			temp = FIXNUM_MINUS(y_in_workspace,bottom_edge);
			d2 = FIXNUM_ABS(temp);
			distance_if_in_range_qm = FIXNUM_LE(d1,
				reasonable_distance) && FIXNUM_LE(d2,
				reasonable_distance) ? 
				isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
				FIXNUM_TIMES(d2,d2))) : Nil;
		    }
		    else
			distance_if_in_range_qm = FIXNUM_MINUS(left_edge,
				x_in_workspace);
		}
		else if (FIXNUM_GT(x_in_workspace,right_edge)) {
		    if (FIXNUM_LT(y_in_workspace,top_edge)) {
			temp = FIXNUM_MINUS(x_in_workspace,right_edge);
			d1 = FIXNUM_ABS(temp);
			temp = FIXNUM_MINUS(y_in_workspace,top_edge);
			d2 = FIXNUM_ABS(temp);
			distance_if_in_range_qm = FIXNUM_LE(d1,
				reasonable_distance) && FIXNUM_LE(d2,
				reasonable_distance) ? 
				isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
				FIXNUM_TIMES(d2,d2))) : Nil;
		    }
		    else if (FIXNUM_GT(y_in_workspace,bottom_edge)) {
			temp = FIXNUM_MINUS(x_in_workspace,right_edge);
			d1 = FIXNUM_ABS(temp);
			temp = FIXNUM_MINUS(y_in_workspace,bottom_edge);
			d2 = FIXNUM_ABS(temp);
			distance_if_in_range_qm = FIXNUM_LE(d1,
				reasonable_distance) && FIXNUM_LE(d2,
				reasonable_distance) ? 
				isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
				FIXNUM_TIMES(d2,d2))) : Nil;
		    }
		    else
			distance_if_in_range_qm = 
				FIXNUM_MINUS(x_in_workspace,right_edge);
		}
		else if (FIXNUM_LT(y_in_workspace,top_edge))
		    distance_if_in_range_qm = FIXNUM_MINUS(top_edge,
			    y_in_workspace);
		else if (FIXNUM_GT(y_in_workspace,bottom_edge))
		    distance_if_in_range_qm = FIXNUM_MINUS(y_in_workspace,
			    bottom_edge);
		else
		    distance_if_in_range_qm = FIX((SI_Long)0L);
		distance_if_reasonable_qm = (distance_if_in_range_qm ? 
			FIXNUM_LT(distance_if_in_range_qm,
			reasonable_distance) : TRUEP(Nil)) ? 
			distance_if_in_range_qm : Nil;
		if (distance_if_reasonable_qm && ( 
			!TRUEP(nearest_cell_so_far_qm) || 
			FIXNUM_LT(distance_if_reasonable_qm,
			nearest_cell_distance_so_far))) {
		    nearest_cell_so_far_qm = Cell;
		    nearest_cell_distance_so_far = distance_if_reasonable_qm;
		    row_index_of_nearest_cell = FIX(row_index);
		    column_row_index_of_nearest_cell = column_index;
		    left_edge_of_nearest_cell = left_edge_of_cell;
		    top_edge_of_nearest_cell = top_edge_of_cell;
		    right_edge_of_nearest_cell = right_edge_of_cell;
		    bottom_edge_of_nearest_cell = bottom_edge_of_cell;
		}
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	  POP_SPECIAL();
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
      if (nearest_cell_so_far_qm)
	  result = VALUES_8(nearest_cell_so_far_qm,table,
		  row_index_of_nearest_cell,
		  column_row_index_of_nearest_cell,
		  left_edge_of_nearest_cell,top_edge_of_nearest_cell,
		  right_edge_of_nearest_cell,bottom_edge_of_nearest_cell);
      else
	  result = VALUES_1(Nil);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
  end_pick_cell_from_table:
    return result;
}

Object The_type_description_of_menu_item_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_menu_item_spots, Qchain_of_available_menu_item_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_item_spot_count, Qmenu_item_spot_count);

Object Chain_of_available_menu_item_spots_vector = UNBOUND;

/* MENU-ITEM-SPOT-STRUCTURE-MEMORY-USAGE */
Object menu_item_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(117,39);
    temp = Menu_item_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MENU-ITEM-SPOT-COUNT */
Object outstanding_menu_item_spot_count()
{
    Object def_structure_menu_item_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(117,40);
    gensymed_symbol = IFIX(Menu_item_spot_count);
    def_structure_menu_item_spot_variable = Chain_of_available_menu_item_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_menu_item_spot_variable))
	goto end_loop;
    def_structure_menu_item_spot_variable = 
	    ISVREF(def_structure_menu_item_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MENU-ITEM-SPOT-1 */
Object reclaim_menu_item_spot_1(menu_item_spot)
    Object menu_item_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(117,41);
    inline_note_reclaim_cons(menu_item_spot,Nil);
    structure_being_reclaimed = menu_item_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(menu_item_spot,(SI_Long)2L));
      SVREF(menu_item_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_menu_item_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(menu_item_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_menu_item_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = menu_item_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MENU-ITEM-SPOT */
Object reclaim_structure_for_menu_item_spot(menu_item_spot)
    Object menu_item_spot;
{
    x_note_fn_call(117,42);
    return reclaim_menu_item_spot_1(menu_item_spot);
}

static Object Qg2_defstruct_structure_name_menu_item_spot_g2_struct;  /* g2-defstruct-structure-name::menu-item-spot-g2-struct */

/* MAKE-PERMANENT-MENU-ITEM-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_menu_item_spot_structure_internal()
{
    Object def_structure_menu_item_spot_variable;
    Object defstruct_g2_menu_item_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(117,43);
    def_structure_menu_item_spot_variable = Nil;
    atomic_incff_symval(Qmenu_item_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_menu_item_spot_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_menu_item_spot_variable = the_array;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_menu_item_spot_g2_struct;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_menu_item_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_menu_item_spot_variable = 
		defstruct_g2_menu_item_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_menu_item_spot_variable);
}

/* MAKE-MENU-ITEM-SPOT-1 */
Object make_menu_item_spot_1()
{
    Object def_structure_menu_item_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(117,44);
    def_structure_menu_item_spot_variable = 
	    ISVREF(Chain_of_available_menu_item_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_menu_item_spot_variable) {
	svref_arg_1 = Chain_of_available_menu_item_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_menu_item_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_menu_item_spot_g2_struct;
    }
    else
	def_structure_menu_item_spot_variable = 
		make_permanent_menu_item_spot_structure_internal();
    inline_note_allocate_cons(def_structure_menu_item_spot_variable,Nil);
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_menu_item_spot_variable,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_menu_item_spot_variable);
}

Object The_type_description_of_menu_title_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_menu_title_spots, Qchain_of_available_menu_title_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_title_spot_count, Qmenu_title_spot_count);

Object Chain_of_available_menu_title_spots_vector = UNBOUND;

/* MENU-TITLE-SPOT-STRUCTURE-MEMORY-USAGE */
Object menu_title_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(117,45);
    temp = Menu_title_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MENU-TITLE-SPOT-COUNT */
Object outstanding_menu_title_spot_count()
{
    Object def_structure_menu_title_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(117,46);
    gensymed_symbol = IFIX(Menu_title_spot_count);
    def_structure_menu_title_spot_variable = 
	    Chain_of_available_menu_title_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_menu_title_spot_variable))
	goto end_loop;
    def_structure_menu_title_spot_variable = 
	    ISVREF(def_structure_menu_title_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MENU-TITLE-SPOT-1 */
Object reclaim_menu_title_spot_1(menu_title_spot)
    Object menu_title_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(117,47);
    inline_note_reclaim_cons(menu_title_spot,Nil);
    structure_being_reclaimed = menu_title_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(menu_title_spot,(SI_Long)2L));
      SVREF(menu_title_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_menu_title_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(menu_title_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_menu_title_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = menu_title_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MENU-TITLE-SPOT */
Object reclaim_structure_for_menu_title_spot(menu_title_spot)
    Object menu_title_spot;
{
    x_note_fn_call(117,48);
    return reclaim_menu_title_spot_1(menu_title_spot);
}

static Object Qg2_defstruct_structure_name_menu_title_spot_g2_struct;  /* g2-defstruct-structure-name::menu-title-spot-g2-struct */

/* MAKE-PERMANENT-MENU-TITLE-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_menu_title_spot_structure_internal()
{
    Object def_structure_menu_title_spot_variable;
    Object defstruct_g2_menu_title_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(117,49);
    def_structure_menu_title_spot_variable = Nil;
    atomic_incff_symval(Qmenu_title_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_menu_title_spot_variable = Nil;
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
	defstruct_g2_menu_title_spot_variable = the_array;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_menu_title_spot_g2_struct;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_menu_title_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_menu_title_spot_variable = 
		defstruct_g2_menu_title_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_menu_title_spot_variable);
}

/* MAKE-MENU-TITLE-SPOT-1 */
Object make_menu_title_spot_1()
{
    Object def_structure_menu_title_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(117,50);
    def_structure_menu_title_spot_variable = 
	    ISVREF(Chain_of_available_menu_title_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_menu_title_spot_variable) {
	svref_arg_1 = Chain_of_available_menu_title_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_menu_title_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_menu_title_spot_g2_struct;
    }
    else
	def_structure_menu_title_spot_variable = 
		make_permanent_menu_title_spot_structure_internal();
    inline_note_allocate_cons(def_structure_menu_title_spot_variable,Nil);
    SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_menu_title_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_menu_title_spot_variable);
}

/* GENERATE-SPOT-FOR-MENU */
Object generate_spot_for_menu(menu_1,mouse_pointer)
    Object menu_1, mouse_pointer;
{
    Object temp, cell_of_menu_qm, left_edge_of_nearest_cell;
    Object top_edge_of_nearest_cell, right_edge_of_nearest_cell;
    Object bottom_edge_of_nearest_cell, spot;
    char temp_1;
    Object result;

    x_note_fn_call(117,51);
    temp = image_plane_of_mouse_pointer(mouse_pointer);
    result = pick_cell_from_table(6,menu_1,temp,ISVREF(mouse_pointer,
	    (SI_Long)2L),ISVREF(mouse_pointer,(SI_Long)3L),Nil,T);
    MVS_8(result,cell_of_menu_qm,temp,temp,temp,left_edge_of_nearest_cell,
	    top_edge_of_nearest_cell,right_edge_of_nearest_cell,
	    bottom_edge_of_nearest_cell);
    spot = Nil;
    if ( !TRUEP(cell_of_menu_qm))
	spot = make_menu_title_spot_1();
    else {
	if ( !TRUEP(New_g2_classic_ui_p)) {
	    temp = ISVREF(menu_1,(SI_Long)19L);
	    temp = FIRST(temp);
	    temp = FIRST(temp);
	    temp_1 = EQL(temp,cell_of_menu_qm);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    spot = make_menu_title_spot_1();
	else {
	    spot = make_menu_item_spot_1();
	    SVREF(spot,FIX((SI_Long)6L)) = cell_of_menu_qm;
	    SVREF(spot,FIX((SI_Long)7L)) = left_edge_of_nearest_cell;
	    SVREF(spot,FIX((SI_Long)8L)) = top_edge_of_nearest_cell;
	    SVREF(spot,FIX((SI_Long)9L)) = right_edge_of_nearest_cell;
	    SVREF(spot,FIX((SI_Long)10L)) = bottom_edge_of_nearest_cell;
	}
    }
    SVREF(spot,FIX((SI_Long)3L)) = Nil;
    return push_more_detailed_spot(mouse_pointer,spot,Nil);
}

Object Class_choice_action_prop = UNBOUND;

static Object Qclass_choice_action;  /* class-choice-action */

/* CLASS-CHOICE-ACTION-FUNCTION */
Object class_choice_action_function(symbol)
    Object symbol;
{
    x_note_fn_call(117,52);
    return getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qclass_choice_action);
}

/* SET-CURSOR-POSITION-FOR-MENU-IF-APPROPRIATE */
Object set_cursor_position_for_menu_if_appropriate(x_in_window,y_in_window)
    Object x_in_window, y_in_window;
{
    x_note_fn_call(117,53);
    return VALUES_1(Nil);
}

static Object Quser_menu_choice;   /* user-menu-choice */

static Object Qframe_flags;        /* frame-flags */

/* NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-USER-MENU-CHOICE */
Object note_runs_while_inactive_change_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm, rule_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,54);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)18L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    rule_qm = ISVREF(user_menu_choice,(SI_Long)24L);
    if (rule_qm)
	return change_slot_value(3,rule_qm,Qframe_flags,(SI_Long)0L != 
		(IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
		(SI_Long)16777216L) ? FIXNUM_LOGIOR(ISVREF(rule_qm,
		(SI_Long)4L),Runs_while_inactive_flag) : 
		FIX(IFIX(ISVREF(rule_qm,(SI_Long)4L)) &  
		~IFIX(Runs_while_inactive_flag)));
    else
	return VALUES_1(Nil);
}

/* NOTE-MAY-REFER-TO-INACTIVE-ITEMS-CHANGE-FOR-USER-MENU-CHOICE */
Object note_may_refer_to_inactive_items_change_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm, rule_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,55);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)38L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    rule_qm = ISVREF(user_menu_choice,(SI_Long)24L);
    if (rule_qm)
	return change_slot_value(3,rule_qm,Qframe_flags,(SI_Long)0L != 
		(IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
		(SI_Long)33554432L) ? FIXNUM_LOGIOR(ISVREF(rule_qm,
		(SI_Long)4L),May_refer_to_inactive_items_flag) : 
		FIX(IFIX(ISVREF(rule_qm,(SI_Long)4L)) &  
		~IFIX(May_refer_to_inactive_items_flag)));
    else
	return VALUES_1(Nil);
}

static Object Qparent_attribute_name;  /* parent-attribute-name */

static Object Qparent_frame;       /* parent-frame */

static Object Qaction_for_user_menu_choice_qm;  /* action-for-user-menu-choice? */

static Object Qab_slot_value;      /* slot-value */

static Object Quser_menu_choice_priority;  /* user-menu-choice-priority */

static Object Qrule_priority;      /* rule-priority */

static Object Qbutton_or_user_menu_choice_not_compiled_up_to_date;  /* button-or-user-menu-choice-not-compiled-up-to-date */

static Object Quser_menu_choice_or_action_button_missing_action;  /* user-menu-choice-or-action-button-missing-action */

static Object Quser_menu_choice_missing_applicable_class;  /* user-menu-choice-missing-applicable-class */

static Object Quser_menu_choice_missing_label;  /* user-menu-choice-missing-label */

/* INITIALIZE-USER-MENU-CHOICE-ACTION */
Object initialize_user_menu_choice_action(user_menu_choice)
    Object user_menu_choice;
{
    Object embedded_rule_qm, gensymed_symbol, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, temp, thing;

    x_note_fn_call(117,56);
    embedded_rule_qm = ISVREF(user_menu_choice,(SI_Long)24L);
    if (embedded_rule_qm) {
	gensymed_symbol = 
		get_lookup_slot_value_given_default(embedded_rule_qm,
		Qparent_attribute_name,Nil);
	set_non_savable_lookup_slot_value(embedded_rule_qm,Qparent_frame,
		user_menu_choice);
	gensymed_symbol = 
		get_lookup_slot_value_given_default(embedded_rule_qm,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_slot_value_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qaction_for_user_menu_choice_qm;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_slot_value);
	    temp = gensymed_symbol_1;
	}
	else
	    temp = Qaction_for_user_menu_choice_qm;
	set_non_savable_lookup_slot_value(embedded_rule_qm,
		Qparent_attribute_name,temp);
	reclaim_slot_value(gensymed_symbol);
	if ( !TRUEP(Reading_kb_p))
	    add_as_inferior_block(embedded_rule_qm,user_menu_choice);
	thing = get_lookup_slot_value(user_menu_choice,
		Quser_menu_choice_priority);
	if (FIXNUMP(thing) && IFIX(thing) > (SI_Long)0L && FIXNUM_LE(thing,
		How_many_priorities_qm))
	    change_slot_value(3,embedded_rule_qm,Qrule_priority,
		    get_lookup_slot_value(user_menu_choice,
		    Quser_menu_choice_priority));
	propagate_runnable_item_options_to_embedded_rule(embedded_rule_qm,
		user_menu_choice);
	check_for_and_fix_up_cloned_embedded_rule(embedded_rule_qm);
    }
    if ( !TRUEP(compilations_up_to_date_p(user_menu_choice)) && 
	    ISVREF(user_menu_choice,(SI_Long)23L) && Loading_kb_p) {
	add_or_delete_button_frame_note(user_menu_choice,
		Qbutton_or_user_menu_choice_not_compiled_up_to_date,Nil);
	note_frame_with_compilation_removed(user_menu_choice);
    }
    add_or_delete_button_frame_note(user_menu_choice,
	    Quser_menu_choice_or_action_button_missing_action,
	    embedded_rule_qm);
    add_or_delete_button_frame_note(user_menu_choice,
	    Quser_menu_choice_missing_applicable_class,
	    ISVREF(user_menu_choice,(SI_Long)21L));
    return add_or_delete_button_frame_note(user_menu_choice,
	    Quser_menu_choice_missing_label,ISVREF(user_menu_choice,
	    (SI_Long)20L));
}

/* PROPAGATE-RUNNABLE-ITEM-OPTIONS-TO-EMBEDDED-RULE */
Object propagate_runnable_item_options_to_embedded_rule(embedded_rule,
	    parent_item)
    Object embedded_rule, parent_item;
{
    Object frame_flags;

    x_note_fn_call(117,57);
    if ( !EQ((SI_Long)0L != (IFIX(ISVREF(parent_item,(SI_Long)4L)) & 
	    (SI_Long)16777216L) ? T : Nil,(SI_Long)0L != 
	    (IFIX(ISVREF(embedded_rule,(SI_Long)4L)) & (SI_Long)16777216L) 
	    ? T : Nil) ||  !EQ((SI_Long)0L != (IFIX(ISVREF(parent_item,
	    (SI_Long)4L)) & (SI_Long)33554432L) ? T : Nil,(SI_Long)0L != 
	    (IFIX(ISVREF(embedded_rule,(SI_Long)4L)) & (SI_Long)33554432L) 
	    ? T : Nil)) {
	frame_flags = ISVREF(embedded_rule,(SI_Long)4L);
	frame_flags = (SI_Long)0L != (IFIX(ISVREF(parent_item,
		(SI_Long)4L)) & (SI_Long)16777216L) ? 
		FIXNUM_LOGIOR(frame_flags,Runs_while_inactive_flag) : 
		FIX(IFIX(frame_flags) &  ~IFIX(Runs_while_inactive_flag));
	frame_flags = (SI_Long)0L != (IFIX(ISVREF(parent_item,
		(SI_Long)4L)) & (SI_Long)33554432L) ? 
		FIXNUM_LOGIOR(frame_flags,
		May_refer_to_inactive_items_flag) : FIX(IFIX(frame_flags) 
		&  ~IFIX(Runs_while_inactive_flag));
	change_slot_value(3,embedded_rule,Qframe_flags,frame_flags);
    }
    return VALUES_1(Nil);
}

/* INITIALIZE-FOR-USER-MENU-CHOICE */
Object initialize_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,58);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    return initialize_user_menu_choice_slots(user_menu_choice);
}

/* INITIALIZE-AFTER-READING-FOR-USER-MENU-CHOICE */
Object initialize_after_reading_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,59);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    return initialize_user_menu_choice_slots(user_menu_choice);
}

/* INITIALIZE-USER-MENU-CHOICE-SLOTS */
Object initialize_user_menu_choice_slots(user_menu_choice)
    Object user_menu_choice;
{
    x_note_fn_call(117,60);
    initialize_user_menu_choice_action(user_menu_choice);
    initialize_user_menu_choice_symbol(user_menu_choice);
    initialize_class_for_user_menu_choice(user_menu_choice);
    return initialize_condition_for_using_user_menu_choice(user_menu_choice);
}

static Object Qcondition_for_using_user_menu_choice_qm;  /* condition-for-using-user-menu-choice? */

/* PUT-CONDITION-FOR-USING-USER-MENU-CHOICE? */
Object put_condition_for_using_user_menu_choice_qm(user_menu_choice,value,
	    initializing_qm)
    Object user_menu_choice, value, initializing_qm;
{
    Object temp;

    x_note_fn_call(117,61);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,
		Qcondition_for_using_user_menu_choice_qm);
    temp = SVREF(user_menu_choice,FIX((SI_Long)22L)) = value;
    if ( !TRUEP(initializing_qm))
	initialize_condition_for_using_user_menu_choice(user_menu_choice);
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

static Object Quser_menu_choice_condition_not_compiled_up_to_date;  /* user-menu-choice-condition-not-compiled-up-to-date */

/* INITIALIZE-CONDITION-FOR-USING-USER-MENU-CHOICE */
Object initialize_condition_for_using_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object condition_slot_value_and_text_qm, car_new_value;

    x_note_fn_call(117,62);
    condition_slot_value_and_text_qm = ISVREF(user_menu_choice,(SI_Long)22L);
    if (condition_slot_value_and_text_qm &&  
	    !TRUEP(compilations_up_to_date_p(user_menu_choice)) && 
	    Loading_kb_p) {
	if (EQUAL(condition_slot_value_and_text_qm,list_constant)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(user_menu_choice,
			Qcondition_for_using_user_menu_choice_qm);
	    SVREF(user_menu_choice,FIX((SI_Long)22L)) = Nil;
	    return reclaim_slot_value(condition_slot_value_and_text_qm);
	}
	else {
	    reclaim_slot_value(CAR(condition_slot_value_and_text_qm));
	    car_new_value = No_value;
	    M_CAR(condition_slot_value_and_text_qm) = car_new_value;
	    add_or_delete_button_frame_note(user_menu_choice,
		    Quser_menu_choice_condition_not_compiled_up_to_date,Nil);
	    return note_frame_with_compilation_removed(user_menu_choice);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object string_constant_1;   /* " of " */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-USER-MENU-CHOICE */
Object denote_cell_array_element_for_user_menu_choice(user_menu_choice,
	    element_index,include_block_denotation_qm)
    Object user_menu_choice, element_index, include_block_denotation_qm;
{
    x_note_fn_call(117,63);
    twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)13L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_1);
}

/* CLEANUP-FOR-USER-MENU-CHOICE */
Object cleanup_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,64);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    if (ISVREF(user_menu_choice,(SI_Long)21L))
	remove_as_user_menu_choice_for_class(user_menu_choice,
		ISVREF(user_menu_choice,(SI_Long)21L),
		ISVREF(user_menu_choice,(SI_Long)20L));
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(user_menu_choice,
	    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_1 = user_menu_choice;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = T;
    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3);
}

/* PUT-ACTION-FOR-USER-MENU-CHOICE? */
Object put_action_for_user_menu_choice_qm(user_menu_choice,action_text,
	    initializing_qm)
    Object user_menu_choice, action_text, initializing_qm;
{
    Object car_new_value;

    x_note_fn_call(117,65);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(user_menu_choice)) && 
	    Loading_kb_p) {
	reclaim_slot_value(CAR(action_text));
	car_new_value = No_value;
	M_CAR(action_text) = car_new_value;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,
		Qaction_for_user_menu_choice_qm);
    return VALUES_1(SVREF(user_menu_choice,FIX((SI_Long)23L)) = action_text);
}

static Object Qembedded_rule_in_user_menu_choice_qm;  /* embedded-rule-in-user-menu-choice? */

/* PUT-EMBEDDED-RULE-IN-USER-MENU-CHOICE? */
Object put_embedded_rule_in_user_menu_choice_qm(user_menu_choice,
	    embedded_rule_qm,initializing_qm)
    Object user_menu_choice, embedded_rule_qm, initializing_qm;
{
    Object temp;

    x_note_fn_call(117,66);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,
		Qembedded_rule_in_user_menu_choice_qm);
    temp = SVREF(user_menu_choice,FIX((SI_Long)24L)) = embedded_rule_qm;
    if ( !TRUEP(initializing_qm))
	initialize_user_menu_choice_action(user_menu_choice);
    return VALUES_1(temp);
}

/* PUT-USER-MENU-CHOICE-PRIORITY */
Object put_user_menu_choice_priority(user_menu_choice,value,initializing_qm)
    Object user_menu_choice, value, initializing_qm;
{
    Object temp;

    x_note_fn_call(117,67);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,Quser_menu_choice_priority);
    temp = set_lookup_slot_value_1(user_menu_choice,
	    Quser_menu_choice_priority,value);
    if ( !TRUEP(initializing_qm))
	initialize_user_menu_choice_action(user_menu_choice);
    return VALUES_1(temp);
}

static Object Quser_menu_choice_symbol_qm;  /* user-menu-choice-symbol? */

/* PUT-USER-MENU-CHOICE-SYMBOL? */
Object put_user_menu_choice_symbol_qm(user_menu_choice,value,initializing_qm)
    Object user_menu_choice, value, initializing_qm;
{
    Object old_label_qm, temp, class_qm;

    x_note_fn_call(117,68);
    old_label_qm = ISVREF(user_menu_choice,(SI_Long)20L);
    if (old_label_qm &&  !TRUEP(initializing_qm))
	delete_from_directory_of_names(old_label_qm,Quser_menu_choice);
    if (value)
	add_to_directory_of_names(value,Quser_menu_choice);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,Quser_menu_choice_symbol_qm);
    temp = SVREF(user_menu_choice,FIX((SI_Long)20L)) = value;
    if ( !TRUEP(initializing_qm)) {
	class_qm = ISVREF(user_menu_choice,(SI_Long)21L);
	if (class_qm)
	    remove_as_user_menu_choice_for_class(user_menu_choice,class_qm,
		    old_label_qm);
	initialize_user_menu_choice_symbol(user_menu_choice);
    }
    return VALUES_1(temp);
}

static Object Quser_menu_choices;  /* user-menu-choices */

/* INITIALIZE-USER-MENU-CHOICE-SYMBOL */
Object initialize_user_menu_choice_symbol(user_menu_choice)
    Object user_menu_choice;
{
    Object choice_symbol_qm, class_qm;

    x_note_fn_call(117,69);
    choice_symbol_qm = ISVREF(user_menu_choice,(SI_Long)20L);
    add_or_delete_button_frame_note(user_menu_choice,
	    Quser_menu_choice_missing_label,choice_symbol_qm);
    decache_dynamic_menus(1,Quser_menu_choices);
    class_qm = ISVREF(user_menu_choice,(SI_Long)21L);
    if (class_qm)
	return add_as_user_menu_choice_for_class(user_menu_choice,class_qm);
    else
	return VALUES_1(Nil);
}

static Object string_constant_2;   /* "~a conflicts with a built-in menu choice" */

static Object string_constant_3;   /* "the label conflicts with ~d other user menu choice~a" */

static Object string_constant_4;   /* "s" */

static Object string_constant_5;   /* "" */

/* WRITE-USER-MENU-CHOICE-LABEL-CONFLICT-NOTE */
Object write_user_menu_choice_label_conflict_note(particulars,user_menu_choice)
    Object particulars, user_menu_choice;
{
    Object write_symbols_in_lower_case_qm, temp;
    SI_Long count_of_other_labels;
    Declare_special(1);

    x_note_fn_call(117,70);
    if (SYMBOLP(particulars)) {
	write_symbols_in_lower_case_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		0);
	  temp = tformat(2,string_constant_2,particulars);
	POP_SPECIAL();
    }
    else {
	count_of_other_labels = IFIX(FIXNUM_SUB1(particulars));
	temp = tformat(3,string_constant_3,FIX(count_of_other_labels),
		count_of_other_labels > (SI_Long)1L ? string_constant_4 : 
		string_constant_5);
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

Object User_menu_choices_for_this_class_kbprop = UNBOUND;

static Object Qclass_for_user_menu_choice_qm;  /* class-for-user-menu-choice? */

/* PUT-CLASS-FOR-USER-MENU-CHOICE? */
Object put_class_for_user_menu_choice_qm(user_menu_choice,value,
	    initializing_qm)
    Object user_menu_choice, value, initializing_qm;
{
    Object old_class_qm, temp;

    x_note_fn_call(117,71);
    old_class_qm = ISVREF(user_menu_choice,(SI_Long)21L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(user_menu_choice,
		Qclass_for_user_menu_choice_qm);
    temp = SVREF(user_menu_choice,FIX((SI_Long)21L)) = value;
    if ( !TRUEP(initializing_qm)) {
	remove_as_user_menu_choice_for_class(user_menu_choice,old_class_qm,
		ISVREF(user_menu_choice,(SI_Long)20L));
	initialize_class_for_user_menu_choice(user_menu_choice);
    }
    return VALUES_1(temp);
}

static Object Quser_menu_choice_label_conflict;  /* user-menu-choice-label-conflict */

/* INITIALIZE-CLASS-FOR-USER-MENU-CHOICE */
Object initialize_class_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object class_qm;

    x_note_fn_call(117,72);
    class_qm = ISVREF(user_menu_choice,(SI_Long)21L);
    add_or_delete_button_frame_note(user_menu_choice,
	    Quser_menu_choice_missing_applicable_class,class_qm);
    if (class_qm)
	return add_as_user_menu_choice_for_class(user_menu_choice,class_qm);
    else
	return delete_frame_note_if_any(Quser_menu_choice_label_conflict,
		user_menu_choice);
}

/* ADD-AS-USER-MENU-CHOICE-FOR-CLASS */
Object add_as_user_menu_choice_for_class(user_menu_choice,class_1)
    Object user_menu_choice, class_1;
{
    Object kb_property_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_;
    Object user_menu_choices_for_this_class_new_value, label_qm;
    char temp;

    x_note_fn_call(117,73);
    kb_property_modify_macro_using_test_arg_1 = user_menu_choice;
    car_1 = kb_property_modify_macro_using_test_arg_1;
    cdr_1 = lookup_kb_specific_property_value(class_1,
	    User_menu_choices_for_this_class_kbprop);
    key_result = car_1;
    x_element = Nil;
    ab_loop_list_ = cdr_1;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    x_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    user_menu_choices_for_this_class_new_value = temp ? cdr_1 : 
	    kb_property_cons_1(car_1,cdr_1);
    mutate_kb_specific_property_value(class_1,
	    user_menu_choices_for_this_class_new_value,
	    User_menu_choices_for_this_class_kbprop);
    label_qm = ISVREF(user_menu_choice,(SI_Long)20L);
    if (label_qm)
	return update_menu_choice_label_conflict_frame_notes(user_menu_choice,
		class_1,label_qm);
    else
	return VALUES_1(Nil);
}

/* REMOVE-AS-USER-MENU-CHOICE-FOR-CLASS */
Object remove_as_user_menu_choice_for_class(user_menu_choice,class_1,label_qm)
    Object user_menu_choice, class_1, label_qm;
{
    Object temp;

    x_note_fn_call(117,74);
    temp = delete_kb_property_element_1(user_menu_choice,
	    lookup_kb_specific_property_value(class_1,
	    User_menu_choices_for_this_class_kbprop));
    mutate_kb_specific_property_value(class_1,temp,
	    User_menu_choices_for_this_class_kbprop);
    if (label_qm)
	return update_menu_choice_label_conflict_frame_notes(user_menu_choice,
		class_1,label_qm);
    else
	return VALUES_1(Nil);
}

/* UPDATE-MENU-CHOICE-LABEL-CONFLICT-FRAME-NOTES */
Object update_menu_choice_label_conflict_frame_notes(user_menu_choice,
	    class_1,label)
    Object user_menu_choice, class_1, label;
{
    Object particular_qm, umc, ab_loop_list_;
    SI_Long count_1;

    x_note_fn_call(117,75);
    if (built_in_menu_choice_p(1,label))
	particular_qm = label;
    else {
	umc = Nil;
	ab_loop_list_ = lookup_kb_specific_property_value(class_1,
		User_menu_choices_for_this_class_kbprop);
	count_1 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	umc = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(umc,user_menu_choice) || EQ(label,ISVREF(umc,(SI_Long)20L)))
	    count_1 = count_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (count_1 > (SI_Long)1L) {
	    particular_qm = FIX(count_1);
	    goto end_1;
	}
	particular_qm = Qnil;
      end_1:;
    }
    umc = Nil;
    ab_loop_list_ = lookup_kb_specific_property_value(class_1,
	    User_menu_choices_for_this_class_kbprop);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    umc = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(umc,user_menu_choice) || EQ(label,ISVREF(umc,(SI_Long)20L))) {
	delete_frame_note_if_any(Quser_menu_choice_label_conflict,umc);
	if (particular_qm)
	    add_frame_note(3,Quser_menu_choice_label_conflict,umc,
		    particular_qm);
    }
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* RECLAIM-USER-MENU-CHOICE-SYMBOL?-VALUE */
Object reclaim_user_menu_choice_symbol_qm_value(user_menu_choice_symbol_qm,
	    gensymed_symbol)
    Object user_menu_choice_symbol_qm, gensymed_symbol;
{
    x_note_fn_call(117,76);
    if (user_menu_choice_symbol_qm)
	delete_from_directory_of_names(user_menu_choice_symbol_qm,
		Quser_menu_choice);
    return VALUES_1(Nil);
}

/* RECLAIM-EMBEDDED-RULE-IN-USER-MENU-CHOICE?-VALUE */
Object reclaim_embedded_rule_in_user_menu_choice_qm_value(embedded_rule_in_user_menu_choice_qm,
	    gensymed_symbol)
    Object embedded_rule_in_user_menu_choice_qm, gensymed_symbol;
{
    x_note_fn_call(117,77);
    if (embedded_rule_in_user_menu_choice_qm)
	delete_frame(embedded_rule_in_user_menu_choice_qm);
    return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* USER-MENU-CHOICE-EVALUATION-SETTER */
Object user_menu_choice_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(117,78);
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
			      Qsymbol,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_menu_choice_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	result = VALUES_1(parse_result_or_bad_phrase);
  end_safe_category_setter_calling_block:
  end_user_menu_choice_evaluation_setter:
    return result;
}

/* USER-MENU-CHOICE-EVALUATION-GETTER */
Object user_menu_choice_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(117,79);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* MANUALLY-ENABLE-FOR-USER-MENU-CHOICE */
Object manually_enable_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm;
    Object embedded_rule_in_user_menu_choice_qm, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,80);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)48L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    embedded_rule_in_user_menu_choice_qm = ISVREF(user_menu_choice,
	    (SI_Long)24L);
    if (embedded_rule_in_user_menu_choice_qm) {
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(embedded_rule_in_user_menu_choice_qm,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)48L),(SI_Long)1L);
	gensymed_symbol_1 = embedded_rule_in_user_menu_choice_qm;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else
	return VALUES_1(Nil);
}

/* MANUALLY-DISABLE-FOR-USER-MENU-CHOICE */
Object manually_disable_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object frame, sub_vector_qm, method_function_qm;
    Object embedded_rule_in_user_menu_choice_qm, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(117,81);
    frame = user_menu_choice;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)47L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Quser_menu_choice)) {
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
    embedded_rule_in_user_menu_choice_qm = ISVREF(user_menu_choice,
	    (SI_Long)24L);
    if (embedded_rule_in_user_menu_choice_qm) {
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(embedded_rule_in_user_menu_choice_qm,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)47L),(SI_Long)1L);
	gensymed_symbol_1 = embedded_rule_in_user_menu_choice_qm;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else
	return VALUES_1(Nil);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-USER-MENU-CHOICE */
Object activate_subclass_of_entity_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object embedded_rule_in_user_menu_choice_qm, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(117,82);
    embedded_rule_in_user_menu_choice_qm = ISVREF(user_menu_choice,
	    (SI_Long)24L);
    if (embedded_rule_in_user_menu_choice_qm) {
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(embedded_rule_in_user_menu_choice_qm,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = embedded_rule_in_user_menu_choice_qm;
	return inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-USER-MENU-CHOICE */
Object deactivate_subclass_of_entity_for_user_menu_choice(user_menu_choice)
    Object user_menu_choice;
{
    Object embedded_rule_in_user_menu_choice_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(117,83);
    embedded_rule_in_user_menu_choice_qm = ISVREF(user_menu_choice,
	    (SI_Long)24L);
    if (embedded_rule_in_user_menu_choice_qm) {
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(ISVREF(embedded_rule_in_user_menu_choice_qm,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	gensymed_symbol_1 = embedded_rule_in_user_menu_choice_qm;
	gensymed_symbol_2 = Nil;
	return inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object Qreserved_word_p;    /* reserved-word-p */

static Object Qnone;               /* none */

/* USER-INSTANTIABLE-KB-CLASS?-EVALUATION-SETTER */
Object user_instantiable_kb_class_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(117,84);
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
			  list_constant_2))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_3,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_user_instantiable_kb_class_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(evaluation_value),
	    Qreserved_word_p))
	result = VALUES_1(Qnone);
    else
	result = VALUES_1(evaluation_value);
  end_user_instantiable_kb_class_qm_evaluation_setter:
    return result;
}

/* USER-INSTANTIABLE-KB-CLASS?-EVALUATION-GETTER */
Object user_instantiable_kb_class_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(117,85);
    GENSYM_RETURN_ONE(EQ(slot_value,Qnone) ? Nil : slot_value);
    return VALUES_1(Nil);
}

/* USER-MENU-CHOICE-RUNNABLE-P */
Object user_menu_choice_runnable_p(user_menu_choice,frame)
    Object user_menu_choice, frame;
{
    x_note_fn_call(117,86);
    if (runnable_p_function(user_menu_choice) && (System_is_running || 
	    (SI_Long)0L != (IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !TRUEP(Inside_breakpoint_p)) && 
	    ((SI_Long)0L != (IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
	    (SI_Long)33554432L) || (SI_Long)0L != (IFIX(ISVREF(frame,
	    (SI_Long)5L)) & (SI_Long)1L)))
	return evaluate_user_menu_choice_condition(user_menu_choice,frame);
    else
	return VALUES_1(Nil);
}

static Object Qtext_cell_of_table;  /* text-cell-of-table */

/* GET-USER-MENU-CHOICE-OR-CHOICE-SYMBOLS */
Object get_user_menu_choice_or_choice_symbols varargs_1(int, n)
{
    Object frame;
    Object choice_symbol_qm, class_1, resulting_user_menu_choices_so_far;
    Object resulting_user_menu_choice_qm, superior_class, class_description;
    Object ab_loop_list_, user_menu_choice, ab_loop_list__1;
    Object user_menu_choice_symbol_qm, user_menu_choice_1, ab_loop_list__2;
    Object resulting_user_menu_choice_symbols_so_far, ab_loopvar_;
    Object ab_loopvar__1;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(117,87);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    choice_symbol_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L)) {
	class_1 = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	resulting_user_menu_choices_so_far = Nil;
	resulting_user_menu_choice_qm = Nil;
	superior_class = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	user_menu_choice = Nil;
	ab_loop_list__1 = lookup_kb_specific_property_value(superior_class,
		User_menu_choices_for_this_class_kbprop);
	user_menu_choice_symbol_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	user_menu_choice = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	user_menu_choice_symbol_qm = ISVREF(user_menu_choice,(SI_Long)20L);
	if (user_menu_choice_symbol_qm) {
	    if (choice_symbol_qm)
		temp = EQ(user_menu_choice_symbol_qm,choice_symbol_qm);
	    else {
		user_menu_choice_1 = Nil;
		ab_loop_list__2 = resulting_user_menu_choices_so_far;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_2;
		user_menu_choice_1 = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if (EQ(user_menu_choice_symbol_qm,
			ISVREF(user_menu_choice_1,(SI_Long)20L))) {
		    temp = TRUEP(Nil);
		    goto end_1;
		}
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(T);
		goto end_1;
		temp = TRUEP(Qnil);
	      end_1:;
		temp = temp ? memq_function(Qtext_cell_of_table,
			lambda_list_of_ui_command_named(1,
			user_menu_choice_symbol_qm)) ||  
			!TRUEP(built_in_menu_choice_p(1,
			user_menu_choice_symbol_qm)) : TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (choice_symbol_qm)
		resulting_user_menu_choice_qm = user_menu_choice;
	    else
		resulting_user_menu_choices_so_far = 
			slot_value_cons_1(user_menu_choice,
			resulting_user_menu_choices_so_far);
	}
	goto next_loop_1;
      end_loop_1:;
	if (resulting_user_menu_choice_qm) {
	    if (user_menu_choice_runnable_p(resulting_user_menu_choice_qm,
		    frame))
		return VALUES_1(resulting_user_menu_choice_qm);
	    else
		return VALUES_1(Nil);
	}
	goto next_loop;
      end_loop:
	if ( !TRUEP(choice_symbol_qm) && resulting_user_menu_choices_so_far) {
	    user_menu_choice = Nil;
	    ab_loop_list_ = resulting_user_menu_choices_so_far;
	    resulting_user_menu_choice_symbols_so_far = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    user_menu_choice = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (runnable_p_function(user_menu_choice) && 
		    (System_is_running || (SI_Long)0L != 
		    (IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
		    (SI_Long)16777216L) &&  !TRUEP(Inside_breakpoint_p)) 
		    && ((SI_Long)0L != (IFIX(ISVREF(user_menu_choice,
		    (SI_Long)4L)) & (SI_Long)33554432L) || (SI_Long)0L != 
		    (IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)1L)) && 
		    evaluate_user_menu_choice_condition(user_menu_choice,
		    frame)) {
		ab_loopvar__1 = slot_value_cons_1(ISVREF(user_menu_choice,
			(SI_Long)20L),Nil);
		if (ab_loopvar_)
		    M_CDR(ab_loopvar_) = ab_loopvar__1;
		else
		    resulting_user_menu_choice_symbols_so_far = ab_loopvar__1;
		ab_loopvar_ = ab_loopvar__1;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    reclaim_slot_value_list_1(resulting_user_menu_choices_so_far);
	    return VALUES_1(resulting_user_menu_choice_symbols_so_far);
	    return VALUES_1(Qnil);
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-USER-MENU-CHOICES */
Object compute_user_menu_choices(frame)
    Object frame;
{
    x_note_fn_call(117,88);
    return get_user_menu_choice_or_choice_symbols(2,frame,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Window_instigating_this_rule_instance_qm, Qwindow_instigating_this_rule_instance_qm);

/* EXECUTE-USER-MENU-CHOICE-IF-POSSIBLE */
Object execute_user_menu_choice_if_possible(choice_symbol,frame)
    Object choice_symbol, frame;
{
    Object user_menu_choice_qm;

    x_note_fn_call(117,89);
    user_menu_choice_qm = get_user_menu_choice_or_choice_symbols(2,frame,
	    choice_symbol);
    if (user_menu_choice_qm && ISVREF(user_menu_choice_qm,(SI_Long)24L))
	return execute_user_menu_choice(user_menu_choice_qm,frame,
		Current_workstation_window);
    else
	return VALUES_1(Nil);
}

static Object Qitem;               /* item */

/* EXECUTE-USER-MENU-CHOICE */
Object execute_user_menu_choice(user_menu_choice,frame,window_or_ui_client)
    Object user_menu_choice, frame, window_or_ui_client;
{
    Object embedded_rule_qm, window_instigating_this_rule_instance_qm, temp;
    Declare_special(1);

    x_note_fn_call(117,90);
    embedded_rule_qm = ISVREF(user_menu_choice,(SI_Long)24L);
    if (embedded_rule_qm) {
	window_instigating_this_rule_instance_qm = window_or_ui_client;
	PUSH_SPECIAL_WITH_SYMBOL(Window_instigating_this_rule_instance_qm,Qwindow_instigating_this_rule_instance_qm,window_instigating_this_rule_instance_qm,
		0);
	  temp = generate_and_schedule_rule_instances(embedded_rule_qm,
		  Qitem,Nil,frame,Quser_menu_choice,Nil,Nil,Nil);
	POP_SPECIAL();
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

void menus_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_entire_menu_spot_1;
    Object type_description, reclaim_structure_for_entire_focus_menu_spot_1;
    Object reclaim_structure_for_menu_item_spot_1;
    Object reclaim_structure_for_menu_title_spot_1;
    Object write_user_menu_choice_label_conflict_note_1;
    Object user_menu_choice_evaluation_setter_1;
    Object user_menu_choice_evaluation_getter_1;
    Object user_instantiable_kb_class_qm_evaluation_setter_1;
    Object user_instantiable_kb_class_qm_evaluation_getter_1;
    Object Qnew_rules, AB_package, Qslot_value_writer, Qwrite_symbol_from_slot;
    Object Quser_instantiable_kb_class_qm, Qnamed;
    Object Qtype_specification_simple_expansion, list_constant_12, Qab_or;
    Object Qno_item, Qclasses_which_define, Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_user_menu_choice;
    Object Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_user_menu_choice;
    Object Qmanually_disable, Qmanually_disable_for_user_menu_choice;
    Object Qmanually_enable, Qmanually_enable_for_user_menu_choice;
    Object string_constant_80, string_constant_79, Qslot_value_reclaimer;
    Object Qreclaim_embedded_rule_in_user_menu_choice_qm_value;
    Object Qreclaim_user_menu_choice_symbol_qm_value, Qslot_putter;
    Object Qput_class_for_user_menu_choice_qm;
    Object Quser_menu_choices_for_this_class;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_kb_property_list_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qframe_note_writer_1, Qput_user_menu_choice_symbol_qm;
    Object Qput_user_menu_choice_priority;
    Object Qput_embedded_rule_in_user_menu_choice_qm;
    Object Qput_action_for_user_menu_choice_qm, Qcleanup;
    Object Qcleanup_for_user_menu_choice, Qdenote_cell_array_element;
    Object Qdenote_cell_array_element_for_user_menu_choice, list_constant_6;
    Object string_constant_78, list_constant_11, Qlost_spaces;
    Object Qput_condition_for_using_user_menu_choice_qm;
    Object Qwrite_expression_from_slot;
    Object Quser_menu_choice_expression_initialization;
    Object Quser_menu_choice_expression, Qaction_priority, Qaction;
    Object Qab_condition, Qapplicable_class, Qlabel, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_user_menu_choice, Qinitialize;
    Object Qinitialize_for_user_menu_choice;
    Object Qnote_may_refer_to_inactive_items_change;
    Object Qnote_may_refer_to_inactive_items_change_for_user_menu_choice;
    Object Qnote_runs_while_inactive_change;
    Object Qnote_runs_while_inactive_change_for_user_menu_choice;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object list_constant_10, Qcreate_icon_description, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, Qentity, Qformat_description;
    Object string_constant_60;
    Object Qleft_arrow_left_aligned_menu_item_format_new_large;
    Object string_constant_59, string_constant_58;
    Object Qleft_aligned_menu_item_format_new_large, string_constant_57;
    Object Qleft_arrow_left_aligned_menu_item_format_new_small;
    Object string_constant_56, string_constant_55;
    Object Qleft_aligned_menu_item_format_new_small, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object Qdefault_menu_item_format, string_constant_38, list_constant_9;
    Object Qmenu_item_format, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_19, Qtext_cell_format, string_constant_32;
    Object Qmenu_table_format_for_new_g2_classic_ui, string_constant_31;
    Object Qmenu_table_format, Qgenerate_spot, Qmenu, Qgenerate_spot_for_menu;
    Object Qtype_of_frame_represented, Qabstract_type, Qentire_menu_spot;
    Object Qenclosing_spot_type, Qinnermost_spot_p, Qtype_description_of_type;
    Object Qmenu_title_spot, Qreclaim_structure;
    Object Qoutstanding_menu_title_spot_count;
    Object Qmenu_title_spot_structure_memory_usage, Qutilities2;
    Object string_constant_30;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_29, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qmenu_item_spot;
    Object Qoutstanding_menu_item_spot_count;
    Object Qmenu_item_spot_structure_memory_usage, string_constant_28;
    Object string_constant_27, string_constant_26, Qmenu_workspace;
    Object Qgenerate_spot_for_menu_workspace, Qimage_plane_spot;
    Object Qentire_focus_menu_spot, Qoutstanding_entire_focus_menu_spot_count;
    Object Qentire_focus_menu_spot_structure_memory_usage, string_constant_25;
    Object string_constant_24, Qoutstanding_entire_menu_spot_count;
    Object Qentire_menu_spot_structure_memory_usage, string_constant_23;
    Object string_constant_22, string_constant_21, list_constant_8;
    Object string_constant_20, Qtemporary_workspace, list_constant_7;
    Object Qdraw_cascading_menu_marker, Qalignment;
    Object Qwrite_when_to_allow_multiple_menus_from_slot;
    Object Qwhen_to_allow_multiple_menus, string_constant_18;
    Object string_constant_17, Qinitialize_after_reading_for_menu_parameters;
    Object Qinitialize_for_menu_parameters, Qwalking_menus_qm, Ksystem_frame;
    Object Qformats, string_constant_16, string_constant_15, list_constant_5;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object Qsystem_table, Qreclaim_menu_mouse_pointer_value;
    Object Qmenu_mouse_pointer;
    Object Qreclaim_menu_cell_currently_highlighted_qm_value;
    Object Qmenu_cell_currently_highlighted_qm;
    Object Qreclaim_what_this_is_a_menu_for_qm_value;
    Object Qreclaim_menu_choice_arglist_value, Qmenu_choice_arglist;
    Object Qreclaim_menu_choice_function_value, Qmenu_choice_function;
    Object string_constant_11, string_constant_10, list_constant_4;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, Qmenu_string, Qmenus;

    x_note_fn_call(117,91);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qshort_menus_qm = STATIC_SYMBOL("SHORT-MENUS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qshort_menus_qm,Short_menus_qm);
    Qmenus = STATIC_SYMBOL("MENUS",AB_package);
    record_system_variable(Qshort_menus_qm,Qmenus,Nil,Qnil,Qnil,Qnil,Qnil);
    Qmenu_string = STATIC_SYMBOL("MENU-STRING",AB_package);
    Menu_string_prop = Qmenu_string;
    if (Directory_of_built_in_menu_choices == UNBOUND)
	Directory_of_built_in_menu_choices = Nil;
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    list_constant_4 = STATIC_CONS(Qtable,Qnil);
    check_if_superior_classes_are_defined(Qmenu,list_constant_4);
    string_constant_6 = STATIC_STRING("1l1l8t");
    string_constant_7 = 
	    STATIC_STRING("1u4z8r83VCy83VCy9k9k00001m1l8o1l8l000004z8r8325y8325y9k9k00001m1l8o1l8l000004z8r83VBy83VBy9k9k00001m1l8o1l8l000004z8r83efy83efy9");
    string_constant_8 = 
	    STATIC_STRING("k9k00001m1l8o1l8l000004z8r83eny83eny9k9k00001m1l8o1l8l000004z8r83HZy83HZy9k9k00001m1l8o1l8l000004z8r83VAy83VAy9k9k00001m1l8o1l8l");
    string_constant_9 = 
	    STATIC_STRING("000004z8r836Uy836Uy9k9k00001m1l83Ey1l8l000004z8r83VFy83VFy9k9k00001m1l83Ey1l8l000004z8r83Ydy83Ydy9k9k00001m1l83Ey1l8l00000");
    string_constant_10 = 
	    STATIC_STRING("1w8q1n9k1l83*Jy8t1o83VCy08o8l1o8325y08o8l1o83VBy08o8l1o83efy08o8l1o83eny08o8l1o83HZy08o8l1o83VAy08o8l1o836Uy083Ey8l1o83VFy083Ey8");
    string_constant_11 = STATIC_STRING("l1o83Ydy083Ey8l");
    temp = regenerate_optimized_constant(string_constant_6);
    clear_optimized_constants();
    push_optimized_constant(Qmenu);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_7,
	    string_constant_8,string_constant_9));
    clear_optimized_constants();
    push_optimized_constant(Qmenu);
    add_class_to_environment(9,Qmenu,list_constant_4,Nil,temp,Nil,temp_1,
	    list_constant_4,
	    regenerate_optimized_constant(LIST_2(string_constant_10,
	    string_constant_11)),Nil);
    Menu_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmenu,
	    Class_description_gkbprop);
    Qmenu_choice_function = STATIC_SYMBOL("MENU-CHOICE-FUNCTION",AB_package);
    Qreclaim_menu_choice_function_value = 
	    STATIC_SYMBOL("RECLAIM-MENU-CHOICE-FUNCTION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_menu_choice_function_value,
	    STATIC_FUNCTION(reclaim_menu_choice_function_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qmenu_choice_function,
	    SYMBOL_FUNCTION(Qreclaim_menu_choice_function_value),
	    Qslot_value_reclaimer);
    Qmenu_choice_arglist = STATIC_SYMBOL("MENU-CHOICE-ARGLIST",AB_package);
    Qreclaim_menu_choice_arglist_value = 
	    STATIC_SYMBOL("RECLAIM-MENU-CHOICE-ARGLIST-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_menu_choice_arglist_value,
	    STATIC_FUNCTION(reclaim_menu_choice_arglist_value,NIL,FALSE,2,2));
    mutate_global_property(Qmenu_choice_arglist,
	    SYMBOL_FUNCTION(Qreclaim_menu_choice_arglist_value),
	    Qslot_value_reclaimer);
    Qmenus_for_this = STATIC_SYMBOL("MENUS-FOR-THIS",AB_package);
    Qwhat_this_is_a_menu_for_qm = 
	    STATIC_SYMBOL("WHAT-THIS-IS-A-MENU-FOR\?",AB_package);
    Qreclaim_what_this_is_a_menu_for_qm_value = 
	    STATIC_SYMBOL("RECLAIM-WHAT-THIS-IS-A-MENU-FOR\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_what_this_is_a_menu_for_qm_value,
	    STATIC_FUNCTION(reclaim_what_this_is_a_menu_for_qm_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qwhat_this_is_a_menu_for_qm,
	    SYMBOL_FUNCTION(Qreclaim_what_this_is_a_menu_for_qm_value),
	    Qslot_value_reclaimer);
    Qmenu_cell_currently_highlighted_qm = 
	    STATIC_SYMBOL("MENU-CELL-CURRENTLY-HIGHLIGHTED\?",AB_package);
    Qreclaim_menu_cell_currently_highlighted_qm_value = 
	    STATIC_SYMBOL("RECLAIM-MENU-CELL-CURRENTLY-HIGHLIGHTED\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_menu_cell_currently_highlighted_qm_value,
	    STATIC_FUNCTION(reclaim_menu_cell_currently_highlighted_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qmenu_cell_currently_highlighted_qm,
	    SYMBOL_FUNCTION(Qreclaim_menu_cell_currently_highlighted_qm_value),
	    Qslot_value_reclaimer);
    Qmenu_mouse_pointer = STATIC_SYMBOL("MENU-MOUSE-POINTER",AB_package);
    Qreclaim_menu_mouse_pointer_value = 
	    STATIC_SYMBOL("RECLAIM-MENU-MOUSE-POINTER-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_menu_mouse_pointer_value,
	    STATIC_FUNCTION(reclaim_menu_mouse_pointer_value,NIL,FALSE,2,2));
    mutate_global_property(Qmenu_mouse_pointer,
	    SYMBOL_FUNCTION(Qreclaim_menu_mouse_pointer_value),
	    Qslot_value_reclaimer);
    Qmenu_parameters = STATIC_SYMBOL("MENU-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_5 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qmenu_parameters,list_constant_5);
    string_constant_12 = STATIC_STRING("1l1l83ey");
    string_constant_13 = 
	    STATIC_STRING("1o4z8r83GXy83GXy83VHy83VHy083*hy001n1l8l1l8o1m8p83Ady000004z8r83Fvy83Fvy83VHy83VHy08329y001n1l8l1l8o1m8p83Fvy000004z8r83e2y83e2y");
    string_constant_14 = 
	    STATIC_STRING("83VHy83VHy08k001n1l8l1l83Ey1m8p83Ky000004z8r83Asy83Asy83VHy83VHy01m830Py1n831iy834Wy836iy001n1l8l1l83Ey1m8p83Asy00000");
    string_constant_15 = 
	    STATIC_STRING("1q8q1n83VHy1l83-sy83ey1p83GXy83*hy8l8o1m8p83Ady1p83Fvy8329y8l8o1m8p83Fvy1p83e2y8k8l83Ey1m8p83Ky1p83Asy1m830Py1n831iy834Wy836iy8l");
    string_constant_16 = STATIC_STRING("83Ey1m8p83Asy");
    temp = regenerate_optimized_constant(string_constant_12);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_13,
	    string_constant_14));
    add_class_to_environment(9,Qmenu_parameters,list_constant_5,Nil,temp,
	    Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_15,
	    string_constant_16)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_parameters,Menu_parameters);
    Qformats = STATIC_SYMBOL("FORMATS",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qmenu_parameters,Qformats,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    Qwalking_menus = STATIC_SYMBOL("WALKING-MENUS",AB_package);
    Qwalking_menus_qm = STATIC_SYMBOL("WALKING-MENUS\?",AB_package);
    alias_slot_name(3,Qwalking_menus,Qwalking_menus_qm,Qmenu_parameters);
    Qinitialize_for_menu_parameters = 
	    STATIC_SYMBOL("INITIALIZE-FOR-MENU-PARAMETERS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_menu_parameters,
	    STATIC_FUNCTION(initialize_for_menu_parameters,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_menu_parameters);
    set_get(Qmenu_parameters,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmenu_parameters,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_menu_parameters = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-MENU-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_menu_parameters,
	    STATIC_FUNCTION(initialize_after_reading_for_menu_parameters,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_menu_parameters);
    set_get(Qmenu_parameters,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qmenu_parameters,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    string_constant_17 = 
	    STATIC_STRING("1n1m83Fvy1m9k8329y1m83Fvy1m9k83f4y1n83Fvy1n1m9k83=Iy1m9k83-RJy1m9k83-o6y83-Yxy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_17));
    string_constant_18 = 
	    STATIC_STRING("1n1m83Ady1m9k83*hy1m83Ady1m9k83-cy1m83Ady1m9k83-by");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_18));
    Qif_different = STATIC_SYMBOL("IF-DIFFERENT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qwhen_to_allow_multiple_menus = 
	    STATIC_SYMBOL("WHEN-TO-ALLOW-MULTIPLE-MENUS",AB_package);
    Qwrite_when_to_allow_multiple_menus_from_slot = 
	    STATIC_SYMBOL("WRITE-WHEN-TO-ALLOW-MULTIPLE-MENUS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_when_to_allow_multiple_menus_from_slot,
	    STATIC_FUNCTION(write_when_to_allow_multiple_menus_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qwhen_to_allow_multiple_menus,
	    SYMBOL_FUNCTION(Qwrite_when_to_allow_multiple_menus_from_slot),
	    Qslot_value_writer);
    Qalignment = STATIC_SYMBOL("ALIGNMENT",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qalignment,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qfat_left_aligned_menu_item_format = 
	    STATIC_SYMBOL("FAT-LEFT-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qfat_center_aligned_menu_item_format = 
	    STATIC_SYMBOL("FAT-CENTER-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qfat_right_aligned_menu_item_format = 
	    STATIC_SYMBOL("FAT-RIGHT-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qleft_aligned_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qcenter_aligned_menu_item_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qright_aligned_menu_item_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qleft_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",AB_package);
    Qcenter_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qright_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qnew_large_right = STATIC_SYMBOL("NEW-LARGE-RIGHT",AB_package);
    Qleft_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qnew_small_right = STATIC_SYMBOL("NEW-SMALL-RIGHT",AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qnew_large_left = STATIC_SYMBOL("NEW-LARGE-LEFT",AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qnew_small_left = STATIC_SYMBOL("NEW-SMALL-LEFT",AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qold_left = STATIC_SYMBOL("OLD-LEFT",AB_package);
    Qold_right = STATIC_SYMBOL("OLD-RIGHT",AB_package);
    Qright_marker_for_cascading_menu = 
	    STATIC_SYMBOL("RIGHT-MARKER-FOR-CASCADING-MENU",AB_package);
    Qleft_marker_for_cascading_menu = 
	    STATIC_SYMBOL("LEFT-MARKER-FOR-CASCADING-MENU",AB_package);
    Qdraw_cascading_menu_marker = 
	    STATIC_SYMBOL("DRAW-CASCADING-MENU-MARKER",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_cascading_menu_marker,
	    STATIC_FUNCTION(draw_cascading_menu_marker,NIL,FALSE,12,12));
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_aligned_cascade_menu_item_format,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_arrow_left_aligned_cascade_menu_item_format,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qcenter_aligned_cascade_menu_item_format,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qright_aligned_cascade_menu_item_format,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_aligned_cascade_menu_item_format_new_large,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large,
	    temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_aligned_cascade_menu_item_format_new_small,temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    temp_2 = SYMBOL_FUNCTION(Qdraw_cascading_menu_marker);
    temp_2 = set_getf(Post_draw_methods_for_text_box_formats,
	    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small,
	    temp_2);
    Post_draw_methods_for_text_box_formats = temp_2;
    Qfat_left_aligned_menu_heading_format = 
	    STATIC_SYMBOL("FAT-LEFT-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    Qfat_center_aligned_menu_heading_format = 
	    STATIC_SYMBOL("FAT-CENTER-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    Qfat_right_aligned_menu_heading_format = 
	    STATIC_SYMBOL("FAT-RIGHT-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    Qleft_aligned_menu_heading_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    Qcenter_aligned_menu_heading_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    Qright_aligned_menu_heading_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-MENU-HEADING-FORMAT",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)6L,
	    Qfat_left_aligned_menu_heading_format,
	    Qfat_center_aligned_menu_heading_format,
	    Qfat_right_aligned_menu_heading_format,
	    Qleft_aligned_menu_heading_format,
	    Qcenter_aligned_menu_heading_format,
	    Qright_aligned_menu_heading_format);
    if (All_menu_heading_format_names == UNBOUND)
	All_menu_heading_format_names = list_constant_7;
    Qleft_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    Qcenter_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    Qright_aligned_color_menu_item_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-COLOR-MENU-ITEM-FORMAT",AB_package);
    Qmenu_workspace = STATIC_SYMBOL("MENU-WORKSPACE",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    list_constant_8 = STATIC_CONS(Qtemporary_workspace,Qnil);
    check_if_superior_classes_are_defined(Qmenu_workspace,list_constant_8);
    string_constant_19 = STATIC_STRING("0");
    string_constant_20 = 
	    STATIC_STRING("1m4z8r83VJy83VJy83VIy83VIy00001m1l8o1l8l000004z8r836Hy836Hy83VIy83VIy08k001n1l8l1m8p83Ky1l83Ny00000");
    string_constant_21 = 
	    STATIC_STRING("1o8q1m83VIy1l8318y1o83VJy08o8l1m836Hy8k");
    temp = regenerate_optimized_constant(string_constant_19);
    temp_1 = regenerate_optimized_constant(string_constant_20);
    add_class_to_environment(9,Qmenu_workspace,list_constant_8,Nil,temp,
	    Nil,temp_1,list_constant_8,
	    regenerate_optimized_constant(string_constant_21),Nil);
    Menu_workspace_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmenu_workspace,
	    Class_description_gkbprop);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_entire_menu_spot_g2_struct = 
	    STATIC_SYMBOL("ENTIRE-MENU-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qentire_menu_spot = STATIC_SYMBOL("ENTIRE-MENU-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_entire_menu_spot_g2_struct,
	    Qentire_menu_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qentire_menu_spot,
	    Qg2_defstruct_structure_name_entire_menu_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_entire_menu_spot == UNBOUND)
	The_type_description_of_entire_menu_spot = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m838Fy1o838Fy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_entire_menu_spot;
    The_type_description_of_entire_menu_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_entire_menu_spot_g2_struct,
	    The_type_description_of_entire_menu_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qentire_menu_spot,
	    The_type_description_of_entire_menu_spot,
	    Qtype_description_of_type);
    Qoutstanding_entire_menu_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-ENTIRE-MENU-SPOT-COUNT",AB_package);
    Qentire_menu_spot_structure_memory_usage = 
	    STATIC_SYMBOL("ENTIRE-MENU-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_23 = STATIC_STRING("1q838Fy8s83-Sry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_entire_menu_spot_count);
    push_optimized_constant(Qentire_menu_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_entire_menu_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ENTIRE-MENU-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_entire_menu_spots,
	    Chain_of_available_entire_menu_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_entire_menu_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qentire_menu_spot_count = STATIC_SYMBOL("ENTIRE-MENU-SPOT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentire_menu_spot_count,Entire_menu_spot_count);
    record_system_variable(Qentire_menu_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_entire_menu_spots_vector == UNBOUND)
	Chain_of_available_entire_menu_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qentire_menu_spot_structure_memory_usage,
	    STATIC_FUNCTION(entire_menu_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_entire_menu_spot_count,
	    STATIC_FUNCTION(outstanding_entire_menu_spot_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_entire_menu_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_entire_menu_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qentire_menu_spot,
	    reclaim_structure_for_entire_menu_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qentire_menu_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qmenu),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct = 
	    STATIC_SYMBOL("ENTIRE-FOCUS-MENU-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qentire_focus_menu_spot = STATIC_SYMBOL("ENTIRE-FOCUS-MENU-SPOT",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct,
	    Qentire_focus_menu_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qentire_focus_menu_spot,
	    Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_entire_focus_menu_spot == UNBOUND)
	The_type_description_of_entire_focus_menu_spot = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83Kay1p83Kay838Fy83Qy8n8k1l838Fy0000001l1m8x838Fykqk0k0");
    temp = The_type_description_of_entire_focus_menu_spot;
    The_type_description_of_entire_focus_menu_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    mutate_global_property(Qg2_defstruct_structure_name_entire_focus_menu_spot_g2_struct,
	    The_type_description_of_entire_focus_menu_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qentire_focus_menu_spot,
	    The_type_description_of_entire_focus_menu_spot,
	    Qtype_description_of_type);
    Qoutstanding_entire_focus_menu_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-ENTIRE-FOCUS-MENU-SPOT-COUNT",
	    AB_package);
    Qentire_focus_menu_spot_structure_memory_usage = 
	    STATIC_SYMBOL("ENTIRE-FOCUS-MENU-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_25 = STATIC_STRING("1q83Kay8s83-Spy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_entire_focus_menu_spot_count);
    push_optimized_constant(Qentire_focus_menu_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_entire_focus_menu_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ENTIRE-FOCUS-MENU-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_entire_focus_menu_spots,
	    Chain_of_available_entire_focus_menu_spots);
    record_system_variable(Qchain_of_available_entire_focus_menu_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qentire_focus_menu_spot_count = 
	    STATIC_SYMBOL("ENTIRE-FOCUS-MENU-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qentire_focus_menu_spot_count,
	    Entire_focus_menu_spot_count);
    record_system_variable(Qentire_focus_menu_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_entire_focus_menu_spots_vector == UNBOUND)
	Chain_of_available_entire_focus_menu_spots_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qentire_focus_menu_spot_structure_memory_usage,
	    STATIC_FUNCTION(entire_focus_menu_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_entire_focus_menu_spot_count,
	    STATIC_FUNCTION(outstanding_entire_focus_menu_spot_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_entire_focus_menu_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_entire_focus_menu_spot,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qentire_focus_menu_spot,
	    reclaim_structure_for_entire_focus_menu_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qentire_focus_menu_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qnil),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qmenu),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qgenerate_spot_for_menu_workspace = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-MENU-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_menu_workspace,
	    STATIC_FUNCTION(generate_spot_for_menu_workspace,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_menu_workspace);
    set_get(Qmenu_workspace,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qmenu_workspace,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qalways = STATIC_SYMBOL("ALWAYS",AB_package);
    Qreason_to_not_recycle_menu = 
	    STATIC_SYMBOL("REASON-TO-NOT-RECYCLE-MENU",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~a-~a-~a");
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    Qmenu_spacer_format = STATIC_SYMBOL("MENU-SPACER-FORMAT",AB_package);
    string_constant_26 = 
	    STATIC_STRING("13Dy83-Qy83ny1l83-ry83tyk83uyk83syk83byk83ayk83Wyk83cyk");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qmenu_spacer_format,
	    regenerate_optimized_constant(string_constant_26),
	    Qformat_description);
    array_constant_1 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Highlight_selected_menu_items_qm = T;
    Qg2_defstruct_structure_name_menu_item_spot_g2_struct = 
	    STATIC_SYMBOL("MENU-ITEM-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmenu_item_spot = STATIC_SYMBOL("MENU-ITEM-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_menu_item_spot_g2_struct,
	    Qmenu_item_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmenu_item_spot,
	    Qg2_defstruct_structure_name_menu_item_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_menu_item_spot == UNBOUND)
	The_type_description_of_menu_item_spot = Nil;
    string_constant_27 = 
	    STATIC_STRING("43Dy8m83Ddy1o83Ddy83Qy8n8k1l83Qy0000001l1m8x83Qykvk0k0");
    temp = The_type_description_of_menu_item_spot;
    The_type_description_of_menu_item_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_27));
    mutate_global_property(Qg2_defstruct_structure_name_menu_item_spot_g2_struct,
	    The_type_description_of_menu_item_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmenu_item_spot,
	    The_type_description_of_menu_item_spot,Qtype_description_of_type);
    Qoutstanding_menu_item_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-MENU-ITEM-SPOT-COUNT",AB_package);
    Qmenu_item_spot_structure_memory_usage = 
	    STATIC_SYMBOL("MENU-ITEM-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_28 = STATIC_STRING("1q83Ddy8s83-eJy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_menu_item_spot_count);
    push_optimized_constant(Qmenu_item_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_28));
    Qchain_of_available_menu_item_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MENU-ITEM-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_menu_item_spots,
	    Chain_of_available_menu_item_spots);
    record_system_variable(Qchain_of_available_menu_item_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qmenu_item_spot_count = STATIC_SYMBOL("MENU-ITEM-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_item_spot_count,Menu_item_spot_count);
    record_system_variable(Qmenu_item_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_menu_item_spots_vector == UNBOUND)
	Chain_of_available_menu_item_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmenu_item_spot_structure_memory_usage,
	    STATIC_FUNCTION(menu_item_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_menu_item_spot_count,
	    STATIC_FUNCTION(outstanding_menu_item_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_menu_item_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_menu_item_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qmenu_item_spot,
	    reclaim_structure_for_menu_item_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_item_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qentire_menu_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qnull),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qg2_defstruct_structure_name_menu_title_spot_g2_struct = 
	    STATIC_SYMBOL("MENU-TITLE-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmenu_title_spot = STATIC_SYMBOL("MENU-TITLE-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_menu_title_spot_g2_struct,
	    Qmenu_title_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmenu_title_spot,
	    Qg2_defstruct_structure_name_menu_title_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_menu_title_spot == UNBOUND)
	The_type_description_of_menu_title_spot = Nil;
    string_constant_29 = 
	    STATIC_STRING("43Dy8m83Dfy1o83Dfy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_menu_title_spot;
    The_type_description_of_menu_title_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_29));
    mutate_global_property(Qg2_defstruct_structure_name_menu_title_spot_g2_struct,
	    The_type_description_of_menu_title_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmenu_title_spot,
	    The_type_description_of_menu_title_spot,Qtype_description_of_type);
    Qoutstanding_menu_title_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-MENU-TITLE-SPOT-COUNT",AB_package);
    Qmenu_title_spot_structure_memory_usage = 
	    STATIC_SYMBOL("MENU-TITLE-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_30 = STATIC_STRING("1q83Dfy8s83-eOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_menu_title_spot_count);
    push_optimized_constant(Qmenu_title_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_30));
    Qchain_of_available_menu_title_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MENU-TITLE-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_menu_title_spots,
	    Chain_of_available_menu_title_spots);
    record_system_variable(Qchain_of_available_menu_title_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qmenu_title_spot_count = STATIC_SYMBOL("MENU-TITLE-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_title_spot_count,Menu_title_spot_count);
    record_system_variable(Qmenu_title_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_menu_title_spots_vector == UNBOUND)
	Chain_of_available_menu_title_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmenu_title_spot_structure_memory_usage,
	    STATIC_FUNCTION(menu_title_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_menu_title_spot_count,
	    STATIC_FUNCTION(outstanding_menu_title_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_menu_title_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_menu_title_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmenu_title_spot,
	    reclaim_structure_for_menu_title_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmenu_title_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qentire_menu_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qnull),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qgenerate_spot_for_menu = STATIC_SYMBOL("GENERATE-SPOT-FOR-MENU",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_menu,
	    STATIC_FUNCTION(generate_spot_for_menu,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_menu);
    set_get(Qmenu,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qmenu,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qmenu_table_format = STATIC_SYMBOL("MENU-TABLE-FORMAT",AB_package);
    string_constant_31 = 
	    STATIC_STRING("13Dy83*ny83=wy83*2y832Py83fy8308ym830Aym8309ym8307ym83=Dyl83=Nyk");
    mutate_global_property(Qmenu_table_format,
	    regenerate_optimized_constant(string_constant_31),
	    Qformat_description);
    Qmenu_table_format_for_new_g2_classic_ui = 
	    STATIC_SYMBOL("MENU-TABLE-FORMAT-FOR-NEW-G2-CLASSIC-UI",
	    AB_package);
    string_constant_32 = 
	    STATIC_STRING("13Dy83*ny83=wy0832Py83fy8308yk830Ayk8309yk8307yk83=Dyk83=Nyk");
    mutate_global_property(Qmenu_table_format_for_new_g2_classic_ui,
	    regenerate_optimized_constant(string_constant_32),
	    Qformat_description);
    Qmenu_item_format = STATIC_SYMBOL("MENU-ITEM-FORMAT",AB_package);
    Qtext_cell_format = STATIC_SYMBOL("TEXT-CELL-FORMAT",AB_package);
    list_constant_9 = STATIC_CONS(Qtext_cell_format,Qnil);
    check_if_superior_classes_are_defined(Qmenu_item_format,list_constant_9);
    string_constant_33 = 
	    STATIC_STRING("1w4z8r83by83by83*by83*by0r001n1l8l1m8p83*4y1l8o000004z8r83ay83ay83*by83*by0n001n1l8l1m8p83*4y1l8o000004z8r83Wy83Wy83*by83*by0r00");
    string_constant_34 = 
	    STATIC_STRING("1n1l8l1m8p83*4y1l8o000004z8r83cy83cy83*by83*by0n001n1l8l1m8p83*4y1l8o000004z8r83ny83ny83*by83*by01l83-uy001n1l8l1m8p831wy1l8o000");
    string_constant_35 = 
	    STATIC_STRING("004z8r83ty83ty83*by83*by03Gy001n1l8l1m8p83*4y1l8o000004z8r83sy83sy83*by83*by0z001n1l8l1m8p83*4y1l8o000004z8r83uy83uy83*by83*by0k");
    string_constant_36 = 
	    STATIC_STRING("001n1l8l1m8p83*4y1l8o000004z8r83wy83wy83*by83*by00001n1l8l1m8p833Xy1l8o000004z8r83ky83ky83*by83*by0k001n1l8l1m8p83*4y1l8o000004z");
    string_constant_37 = 
	    STATIC_STRING("8r83-=y83-=y83*by83*by0k001n1l8l1m8p83*4y1l8o000004z8r83iy83iy83*by83*by03=4y001n1l8l1m8p83*4y1l8o00000");
    string_constant_38 = 
	    STATIC_STRING("1y8q1m83*by1l83-Qy1m83byr1m83ayn1m83Wyr1m83cyn1m83ny1l83-uy1m83ty3Gy1m83syz1m83uyk1m83wy01m83kyk1m83-=yk1m83iy3=4y");
    temp = regenerate_optimized_constant(string_constant_19);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37));
    add_class_to_environment(9,Qmenu_item_format,list_constant_9,Nil,temp,
	    Nil,temp_1,list_constant_9,
	    regenerate_optimized_constant(string_constant_38),Nil);
    Qdefault_menu_item_format = STATIC_SYMBOL("DEFAULT-MENU-ITEM-FORMAT",
	    AB_package);
    string_constant_39 = STATIC_STRING("1l83*by");
    mutate_global_property(Qdefault_menu_item_format,
	    regenerate_optimized_constant(string_constant_39),
	    Qformat_description);
    string_constant_40 = STATIC_STRING("1n83*by83wy0");
    mutate_global_property(Qleft_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_40),
	    Qformat_description);
    string_constant_41 = STATIC_STRING("1n83*by83wy83-cy");
    mutate_global_property(Qcenter_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_41),
	    Qformat_description);
    string_constant_42 = STATIC_STRING("1n83*by83wy83-by");
    mutate_global_property(Qright_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_42),
	    Qformat_description);
    string_constant_43 = STATIC_STRING("1p83*by83wy083Wy3Gy");
    mutate_global_property(Qfat_left_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_43),
	    Qformat_description);
    string_constant_44 = STATIC_STRING("1p83*by83wy83-cy83Wy3Gy");
    mutate_global_property(Qfat_center_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_44),
	    Qformat_description);
    string_constant_45 = STATIC_STRING("1p83*by83wy83-by83Wy3Gy");
    mutate_global_property(Qfat_right_aligned_menu_item_format,
	    regenerate_optimized_constant(string_constant_45),
	    Qformat_description);
    string_constant_46 = STATIC_STRING("1p83*by83wy083Wy3Hy");
    mutate_global_property(Qleft_aligned_cascade_menu_item_format,
	    regenerate_optimized_constant(string_constant_46),
	    Qformat_description);
    string_constant_47 = STATIC_STRING("1p83*by83wy83-cy83Wy3Hy");
    mutate_global_property(Qcenter_aligned_cascade_menu_item_format,
	    regenerate_optimized_constant(string_constant_47),
	    Qformat_description);
    string_constant_48 = STATIC_STRING("1p83*by83wy83-by83Wy3Hy");
    mutate_global_property(Qright_aligned_cascade_menu_item_format,
	    regenerate_optimized_constant(string_constant_48),
	    Qformat_description);
    string_constant_49 = STATIC_STRING("1r83*by83wy083*Ky83fy83-Ny83*2y");
    mutate_global_property(Qleft_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_49),
	    Qformat_description);
    string_constant_50 = STATIC_STRING("1r83*by83wy83-cy83*Ky83fy83-Ny83*2y");
    mutate_global_property(Qcenter_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_50),
	    Qformat_description);
    string_constant_51 = STATIC_STRING("1r83*by83wy83-by83*Ky83fy83-Ny83*2y");
    mutate_global_property(Qright_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_51),
	    Qformat_description);
    string_constant_52 = 
	    STATIC_STRING("1t83*by83Wy3Hy83wy083*Ky83fy83-Ny83*2y");
    mutate_global_property(Qfat_left_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_52),
	    Qformat_description);
    string_constant_53 = 
	    STATIC_STRING("1t83*by83Wy3Hy83wy83-cy83*Ky83fy83-Ny83*2y");
    mutate_global_property(Qfat_center_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_53),
	    Qformat_description);
    string_constant_54 = 
	    STATIC_STRING("1t83*by83Wy3Hy83wy83-by83*Ky83fy83-Ny83*2y");
    mutate_global_property(Qfat_right_aligned_menu_heading_format,
	    regenerate_optimized_constant(string_constant_54),
	    Qformat_description);
    Qleft_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    string_constant_55 = 
	    STATIC_STRING("13Ny83*by83wy083byo83aym83Wyo83cym83ny1l83-ry83ty3Cy83syx83uyk83wy083kyk83-=yk83iy3*my");
    mutate_global_property(Qleft_aligned_menu_item_format_new_small,
	    regenerate_optimized_constant(string_constant_55),
	    Qformat_description);
    string_constant_56 = 
	    STATIC_STRING("13Ny83*by83wy083byo83aym83Wy3Gy83cym83ny1l83-ry83ty3Cy83syx83uyk83wy083kyk83-=yk83iy3*my");
    mutate_global_property(Qleft_aligned_cascade_menu_item_format_new_small,
	    regenerate_optimized_constant(string_constant_56),
	    Qformat_description);
    Qleft_arrow_left_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    string_constant_57 = 
	    STATIC_STRING("13Ny83*by83wy083by3Gy83aym83Wyo83cym83ny1l83-ry83ty3Cy83syx83uyk83wy083kyk83-=yk83iy3*my");
    mutate_global_property(Qleft_arrow_left_aligned_menu_item_format_new_small,
	    regenerate_optimized_constant(string_constant_57),
	    Qformat_description);
    mutate_global_property(Qleft_arrow_left_aligned_cascade_menu_item_format_new_small,
	    regenerate_optimized_constant(string_constant_57),
	    Qformat_description);
    Qleft_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    string_constant_58 = 
	    STATIC_STRING("13Py83*by83wy083byo83ayn83Wyo83cyn83ny1l83-uy83ty3Fy83syz83uyk83wy083kyk83-=yk83iy3=4y83-7y3G+y");
    mutate_global_property(Qleft_aligned_menu_item_format_new_large,
	    regenerate_optimized_constant(string_constant_58),
	    Qformat_description);
    string_constant_59 = 
	    STATIC_STRING("13Py83*by83wy083byo83ayn83Wy3Oy83cyn83ny1l83-uy83ty3Fy83syz83uyk83wy083kyk83-=yk83iy3=4y83-7y3G+y");
    mutate_global_property(Qleft_aligned_cascade_menu_item_format_new_large,
	    regenerate_optimized_constant(string_constant_59),
	    Qformat_description);
    Qleft_arrow_left_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    string_constant_60 = 
	    STATIC_STRING("13Py83*by83wy083by3Oy83ayn83Wyo83cyn83ny1l83-uy83ty3Fy83syz83uyk83wy083kyk83-=yk83iy3=4y83-7y3G+y");
    mutate_global_property(Qleft_arrow_left_aligned_menu_item_format_new_large,
	    regenerate_optimized_constant(string_constant_60),
	    Qformat_description);
    mutate_global_property(Qleft_arrow_left_aligned_cascade_menu_item_format_new_large,
	    regenerate_optimized_constant(string_constant_60),
	    Qformat_description);
    Qclass_choice_action = STATIC_SYMBOL("CLASS-CHOICE-ACTION",AB_package);
    Class_choice_action_prop = Qclass_choice_action;
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Quser_menu_choice,list_constant_10);
    string_constant_61 = STATIC_STRING("1n1m8v834oy1m83*ey1m1l839Fy83*sy1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_62 = 
	    STATIC_STRING("1t4z8r83--y83--y834oy834oy00001p1l8l1m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date. ");
    string_constant_63 = 
	    STATIC_STRING("~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n1l83Ey1l83Uy00");
    string_constant_64 = 
	    STATIC_STRING("0004z8r83-0y83-0y834oy834oy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_65 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u834oy834oy01p8w9k3ay3uy1r1p83Jy1mkk1m3ayk1m3ay3uy1mk3uy1n83jy1mkk1m3ayu1n83Oy1mku1m3a");
    string_constant_66 = 
	    STATIC_STRING("yu1n83Oy1mk3Gy1m3ay3Gy1n83Oy1mk3Qy1m3ay3Qy1n83Oy1mk3ay1m3ay3ay1n83Oy1mk3ky1m3ay3ky001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTIT");
    string_constant_67 = 
	    STATIC_STRING("Y class definition000004z8r83dfy83dfy834oy834oy00001o1m8p834oy1l8l1l8o1l83Cy000004z8r83B9y83B9y834oy834oy00001p1m8p83AOy1l8l1l8z");
    string_constant_68 = 
	    STATIC_STRING("1l8o1l83Cy000004z8r83BMy83BMy834oy834oy00001r1n8p83APy83Gy1l8l1l8z1l8o1l83Cy1l83-5y1m83Dy53Pyexport a menu condition parse000004");
    string_constant_69 = 
	    STATIC_STRING("z8r83GRy83GRy834oy834oy00001p1n8p8333y83Gy1l8o1l8l1l83-5y1m83Dy53Fyexport action parse000004z8r83KQy83KQy834oy834oy00001o1l8o1l8");
    string_constant_70 = 
	    STATIC_STRING("l1l83Cy1m83Dy53Eyexport the uuid\?\?\?000004z8r83Fky83Fky834oy834oy0m001q1m8p83-Yy1l83Ey1l8l1l8z1l83Cy1m83Dy53Jyexport positive-int");
    string_constant_71 = STATIC_STRING("eger00000");
    string_constant_72 = 
	    STATIC_STRING("1v8q1p834oy1m83Ry83-+y1m8v834oy1m83*ey1m1l839Fy83*sy8t1o83--y01m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each auth");
    string_constant_73 = 
	    STATIC_STRING("or entry may have a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, wri");
    string_constant_74 = 
	    STATIC_STRING("table: true\n1n83-0y01m8p83-0y1m8u1p8w9k3ay3uy1r1p83Jy1mkk1m3ayk1m3ay3uy1mk3uy1n83jy1mkk1m3ayu1n83Oy1mku1m3ayu1n83Oy1mk3Gy1m3ay3G");
    string_constant_75 = 
	    STATIC_STRING("y1n83Oy1mk3Qy1m3ay3Qy1n83Oy1mk3ay1m3ay3ay1n83Oy1mk3ky1m3ay3ky1q83dfy01m8p834oy8l8o83Cy1r83B9y01m8p83AOy8l8z8o83Cy1t83BMy01n8p83A");
    string_constant_76 = 
	    STATIC_STRING("Py83Gy8l8z8o83Cy83-5y1m83Dy53Pyexport a menu condition parse1r83GRy01n8p8333y83Gy8o8l83-5y1m83Dy53Fyexport action parse1q83KQy08");
    string_constant_77 = 
	    STATIC_STRING("o8l83Cy1m83Dy53Eyexport the uuid\?\?\?1s83Fkym1m8p83-Yy83Ey8l8z83Cy1m83Dy53Jyexport positive-integer");
    temp = regenerate_optimized_constant(string_constant_61);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(10,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69,string_constant_70,string_constant_71));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Quser_menu_choice,list_constant_10,Nil,temp,
	    Nil,temp_1,list_constant_10,
	    regenerate_optimized_constant(list(6,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77)),Nil);
    User_menu_choice_class_description = 
	    lookup_global_or_kb_specific_property_value(Quser_menu_choice,
	    Class_description_gkbprop);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qnote_runs_while_inactive_change_for_user_menu_choice = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_user_menu_choice,
	    STATIC_FUNCTION(note_runs_while_inactive_change_for_user_menu_choice,
	    NIL,FALSE,1,1));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_user_menu_choice);
    set_get(Quser_menu_choice,Qnote_runs_while_inactive_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_runs_while_inactive_change),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qnote_runs_while_inactive_change,temp_2,
	    Qclasses_which_define);
    Qnote_may_refer_to_inactive_items_change_for_user_menu_choice = 
	    STATIC_SYMBOL("NOTE-MAY-REFER-TO-INACTIVE-ITEMS-CHANGE-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_may_refer_to_inactive_items_change_for_user_menu_choice,
	    STATIC_FUNCTION(note_may_refer_to_inactive_items_change_for_user_menu_choice,
	    NIL,FALSE,1,1));
    Qnote_may_refer_to_inactive_items_change = 
	    STATIC_SYMBOL("NOTE-MAY-REFER-TO-INACTIVE-ITEMS-CHANGE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qnote_may_refer_to_inactive_items_change_for_user_menu_choice);
    set_get(Quser_menu_choice,Qnote_may_refer_to_inactive_items_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_may_refer_to_inactive_items_change),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qnote_may_refer_to_inactive_items_change,temp_2,
	    Qclasses_which_define);
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qaction_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("ACTION-FOR-USER-MENU-CHOICE\?",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Quser_menu_choice_priority = STATIC_SYMBOL("USER-MENU-CHOICE-PRIORITY",
	    AB_package);
    Qrule_priority = STATIC_SYMBOL("RULE-PRIORITY",AB_package);
    Qbutton_or_user_menu_choice_not_compiled_up_to_date = 
	    STATIC_SYMBOL("BUTTON-OR-USER-MENU-CHOICE-NOT-COMPILED-UP-TO-DATE",
	    AB_package);
    Quser_menu_choice_or_action_button_missing_action = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-OR-ACTION-BUTTON-MISSING-ACTION",
	    AB_package);
    Quser_menu_choice_missing_applicable_class = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-MISSING-APPLICABLE-CLASS",
	    AB_package);
    Quser_menu_choice_missing_label = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-MISSING-LABEL",AB_package);
    Qinitialize_for_user_menu_choice = 
	    STATIC_SYMBOL("INITIALIZE-FOR-USER-MENU-CHOICE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_user_menu_choice,
	    STATIC_FUNCTION(initialize_for_user_menu_choice,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_user_menu_choice);
    set_get(Quser_menu_choice,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_user_menu_choice = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_user_menu_choice,
	    STATIC_FUNCTION(initialize_after_reading_for_user_menu_choice,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_user_menu_choice);
    set_get(Quser_menu_choice,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Quser_menu_choice_symbol_qm = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-SYMBOL\?",AB_package);
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    alias_slot_name(3,Quser_menu_choice_symbol_qm,Qlabel,Quser_menu_choice);
    Qclass_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("CLASS-FOR-USER-MENU-CHOICE\?",AB_package);
    Qapplicable_class = STATIC_SYMBOL("APPLICABLE-CLASS",AB_package);
    alias_slot_name(3,Qclass_for_user_menu_choice_qm,Qapplicable_class,
	    Quser_menu_choice);
    Qcondition_for_using_user_menu_choice_qm = 
	    STATIC_SYMBOL("CONDITION-FOR-USING-USER-MENU-CHOICE\?",AB_package);
    Qab_condition = STATIC_SYMBOL("CONDITION",AB_package);
    alias_slot_name(3,Qcondition_for_using_user_menu_choice_qm,
	    Qab_condition,Quser_menu_choice);
    Qaction = STATIC_SYMBOL("ACTION",AB_package);
    alias_slot_name(3,Qaction_for_user_menu_choice_qm,Qaction,
	    Quser_menu_choice);
    Qaction_priority = STATIC_SYMBOL("ACTION-PRIORITY",AB_package);
    alias_slot_name(3,Quser_menu_choice_priority,Qaction_priority,
	    Quser_menu_choice);
    Quser_menu_choice_expression = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION",AB_package);
    Qwrite_expression_from_slot = 
	    STATIC_SYMBOL("WRITE-EXPRESSION-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_expression_from_slot,
	    STATIC_FUNCTION(write_expression_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Quser_menu_choice_expression,
	    SYMBOL_FUNCTION(Qwrite_expression_from_slot),Qslot_value_writer);
    Quser_menu_choice_expression_initialization = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION-INITIALIZATION",
	    AB_package);
    mutate_global_property(Quser_menu_choice_expression_initialization,
	    SYMBOL_FUNCTION(Qwrite_expression_from_slot),Qslot_value_writer);
    Qput_condition_for_using_user_menu_choice_qm = 
	    STATIC_SYMBOL("PUT-CONDITION-FOR-USING-USER-MENU-CHOICE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_condition_for_using_user_menu_choice_qm,
	    STATIC_FUNCTION(put_condition_for_using_user_menu_choice_qm,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qcondition_for_using_user_menu_choice_qm,
	    SYMBOL_FUNCTION(Qput_condition_for_using_user_menu_choice_qm),
	    Qslot_putter);
    Qlost_spaces = STATIC_SYMBOL("LOST-SPACES",AB_package);
    list_constant_11 = STATIC_CONS(Qlost_spaces,FIX((SI_Long)0L));
    string_constant_78 = STATIC_STRING("none");
    list_constant = STATIC_LIST((SI_Long)3L,Qnil,list_constant_11,
	    string_constant_78);
    Quser_menu_choice_condition_not_compiled_up_to_date = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-CONDITION-NOT-COMPILED-UP-TO-DATE",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_1 = STATIC_STRING(" of ");
    Qdenote_cell_array_element_for_user_menu_choice = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_user_menu_choice,
	    STATIC_FUNCTION(denote_cell_array_element_for_user_menu_choice,
	    NIL,FALSE,3,3));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_user_menu_choice);
    set_get(Quser_menu_choice,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qcleanup_for_user_menu_choice = 
	    STATIC_SYMBOL("CLEANUP-FOR-USER-MENU-CHOICE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_user_menu_choice,
	    STATIC_FUNCTION(cleanup_for_user_menu_choice,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_user_menu_choice);
    set_get(Quser_menu_choice,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qput_action_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("PUT-ACTION-FOR-USER-MENU-CHOICE\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_action_for_user_menu_choice_qm,
	    STATIC_FUNCTION(put_action_for_user_menu_choice_qm,NIL,FALSE,3,3));
    mutate_global_property(Qaction_for_user_menu_choice_qm,
	    SYMBOL_FUNCTION(Qput_action_for_user_menu_choice_qm),Qslot_putter);
    Qembedded_rule_in_user_menu_choice_qm = 
	    STATIC_SYMBOL("EMBEDDED-RULE-IN-USER-MENU-CHOICE\?",AB_package);
    Qput_embedded_rule_in_user_menu_choice_qm = 
	    STATIC_SYMBOL("PUT-EMBEDDED-RULE-IN-USER-MENU-CHOICE\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_embedded_rule_in_user_menu_choice_qm,
	    STATIC_FUNCTION(put_embedded_rule_in_user_menu_choice_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qembedded_rule_in_user_menu_choice_qm,
	    SYMBOL_FUNCTION(Qput_embedded_rule_in_user_menu_choice_qm),
	    Qslot_putter);
    Qput_user_menu_choice_priority = 
	    STATIC_SYMBOL("PUT-USER-MENU-CHOICE-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_user_menu_choice_priority,
	    STATIC_FUNCTION(put_user_menu_choice_priority,NIL,FALSE,3,3));
    mutate_global_property(Quser_menu_choice_priority,
	    SYMBOL_FUNCTION(Qput_user_menu_choice_priority),Qslot_putter);
    Qput_user_menu_choice_symbol_qm = 
	    STATIC_SYMBOL("PUT-USER-MENU-CHOICE-SYMBOL\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_user_menu_choice_symbol_qm,
	    STATIC_FUNCTION(put_user_menu_choice_symbol_qm,NIL,FALSE,3,3));
    mutate_global_property(Quser_menu_choice_symbol_qm,
	    SYMBOL_FUNCTION(Qput_user_menu_choice_symbol_qm),Qslot_putter);
    Quser_menu_choices = STATIC_SYMBOL("USER-MENU-CHOICES",AB_package);
    Quser_menu_choice_label_conflict = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-LABEL-CONFLICT",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_2 = 
	    STATIC_STRING("~a conflicts with a built-in menu choice");
    string_constant_3 = 
	    STATIC_STRING("the label conflicts with ~d other user menu choice~a");
    string_constant_4 = STATIC_STRING("s");
    string_constant_5 = STATIC_STRING("");
    write_user_menu_choice_label_conflict_note_1 = 
	    STATIC_FUNCTION(write_user_menu_choice_label_conflict_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Quser_menu_choice_label_conflict,
	    write_user_menu_choice_label_conflict_note_1,Qframe_note_writer_1);
    Quser_menu_choices_for_this_class = 
	    STATIC_SYMBOL("USER-MENU-CHOICES-FOR-THIS-CLASS",AB_package);
    Kb_specific_property_names = CONS(Quser_menu_choices_for_this_class,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Quser_menu_choices_for_this_class,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_kb_property_list_function = 
	    STATIC_SYMBOL("RECLAIM-KB-PROPERTY-LIST-FUNCTION",AB_package);
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Quser_menu_choices_for_this_class,
	    Qreclaim_kb_property_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    User_menu_choices_for_this_class_kbprop = 
	    Quser_menu_choices_for_this_class;
    Qput_class_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("PUT-CLASS-FOR-USER-MENU-CHOICE\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_for_user_menu_choice_qm,
	    STATIC_FUNCTION(put_class_for_user_menu_choice_qm,NIL,FALSE,3,3));
    mutate_global_property(Qclass_for_user_menu_choice_qm,
	    SYMBOL_FUNCTION(Qput_class_for_user_menu_choice_qm),Qslot_putter);
    Qreclaim_user_menu_choice_symbol_qm_value = 
	    STATIC_SYMBOL("RECLAIM-USER-MENU-CHOICE-SYMBOL\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_user_menu_choice_symbol_qm_value,
	    STATIC_FUNCTION(reclaim_user_menu_choice_symbol_qm_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Quser_menu_choice_symbol_qm,
	    SYMBOL_FUNCTION(Qreclaim_user_menu_choice_symbol_qm_value),
	    Qslot_value_reclaimer);
    Qreclaim_embedded_rule_in_user_menu_choice_qm_value = 
	    STATIC_SYMBOL("RECLAIM-EMBEDDED-RULE-IN-USER-MENU-CHOICE\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_embedded_rule_in_user_menu_choice_qm_value,
	    STATIC_FUNCTION(reclaim_embedded_rule_in_user_menu_choice_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qembedded_rule_in_user_menu_choice_qm,
	    SYMBOL_FUNCTION(Qreclaim_embedded_rule_in_user_menu_choice_qm_value),
	    Qslot_value_reclaimer);
    string_constant_79 = STATIC_STRING("1m1m83-SYy8333y1m834oy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_79));
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Quser_menu_choice),
	    Qtype_specification_simple_expansion,Qsymbol);
    define_type_specification_explicit_complex_type(Quser_menu_choice,Qsymbol);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Quser_menu_choice);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    user_menu_choice_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_menu_choice_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_menu_choice,
	    user_menu_choice_evaluation_setter_1);
    user_menu_choice_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_menu_choice_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_menu_choice,
	    user_menu_choice_evaluation_getter_1);
    string_constant_80 = STATIC_STRING("1m1m83AOy83-Gy1n83AOy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_80));
    mutate_global_property(Quser_menu_choice,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qmanually_enable_for_user_menu_choice = 
	    STATIC_SYMBOL("MANUALLY-ENABLE-FOR-USER-MENU-CHOICE",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_enable_for_user_menu_choice,
	    STATIC_FUNCTION(manually_enable_for_user_menu_choice,NIL,FALSE,
	    1,1));
    Qmanually_enable = STATIC_SYMBOL("MANUALLY-ENABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qmanually_enable_for_user_menu_choice);
    set_get(Quser_menu_choice,Qmanually_enable,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_enable),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qmanually_enable,temp_2,Qclasses_which_define);
    Qmanually_disable_for_user_menu_choice = 
	    STATIC_SYMBOL("MANUALLY-DISABLE-FOR-USER-MENU-CHOICE",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_disable_for_user_menu_choice,
	    STATIC_FUNCTION(manually_disable_for_user_menu_choice,NIL,
	    FALSE,1,1));
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qmanually_disable_for_user_menu_choice);
    set_get(Quser_menu_choice,Qmanually_disable,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_disable),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qmanually_disable,temp_2,Qclasses_which_define);
    Qactivate_subclass_of_entity_for_user_menu_choice = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_user_menu_choice,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_user_menu_choice,
	    NIL,FALSE,1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_user_menu_choice);
    set_get(Quser_menu_choice,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_user_menu_choice = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-USER-MENU-CHOICE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_user_menu_choice,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_user_menu_choice,
	    NIL,FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_user_menu_choice);
    set_get(Quser_menu_choice,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Quser_menu_choice,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Quser_instantiable_kb_class_qm = 
	    STATIC_SYMBOL("USER-INSTANTIABLE-KB-CLASS\?",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_12 = STATIC_CONS(Qno_item,Qnil);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_12,Qsymbol);
    set_property_value_function(get_symbol_properties_function(Quser_instantiable_kb_class_qm),
	    Qtype_specification_simple_expansion,list_constant_3);
    define_type_specification_explicit_complex_type(Quser_instantiable_kb_class_qm,
	    list_constant_3);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Quser_instantiable_kb_class_qm);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    user_instantiable_kb_class_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(user_instantiable_kb_class_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Quser_instantiable_kb_class_qm,
	    user_instantiable_kb_class_qm_evaluation_setter_1);
    user_instantiable_kb_class_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_instantiable_kb_class_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Quser_instantiable_kb_class_qm,
	    user_instantiable_kb_class_qm_evaluation_getter_1);
    mutate_global_property(Quser_instantiable_kb_class_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qtext_cell_of_table = STATIC_SYMBOL("TEXT-CELL-OF-TABLE",AB_package);
    Qwindow_instigating_this_rule_instance_qm = 
	    STATIC_SYMBOL("WINDOW-INSTIGATING-THIS-RULE-INSTANCE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwindow_instigating_this_rule_instance_qm,
	    Window_instigating_this_rule_instance_qm);
    Qnew_rules = STATIC_SYMBOL("NEW-RULES",AB_package);
    record_system_variable(Qwindow_instigating_this_rule_instance_qm,
	    Qnew_rules,Nil,Qnil,Qnil,Qnil,Qnil);
}
