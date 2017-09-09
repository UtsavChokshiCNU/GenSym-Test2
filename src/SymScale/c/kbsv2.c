/* kbsv2.c
 * Input file:  kb-save2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbsv2.h"


/* MAKE-PANE-DESCRIPTION */
Object make_pane_description(pane,include_transient_kb_workspaces_qm,
	    record_window_position_too_qm,module_qm)
    Object pane, include_transient_kb_workspaces_qm;
    Object record_window_position_too_qm, module_qm;
{
    Object image_plane, ab_loop_list_, workspace_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(134,0);
    image_plane = Nil;
    ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
    workspace_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
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
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
    if ((temp ? include_transient_kb_workspaces_qm || (SI_Long)0L != 
	    (IFIX(ISVREF(workspace_qm,(SI_Long)4L)) & (SI_Long)1L) : 
	    TRUEP(Nil)) ?  !TRUEP(module_qm) || 
	    EQ(get_module_block_is_in(workspace_qm),module_qm) : TRUEP(Nil)) {
	ab_loopvar__2 = 
		slot_value_cons_1(make_image_plane_description(image_plane,
		record_window_position_too_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* CREATE-PSEUDO-FRAME */
Object create_pseudo_frame(item)
    Object item;
{
    x_note_fn_call(134,1);
    return make_pseudo_frame_1(item,copy_frame_serial_number(ISVREF(item,
	    (SI_Long)3L)));
}

/* MODIFY-PANE-DESCRIPTION */
Object modify_pane_description(pane_description)
    Object pane_description;
{
    Object form, ab_loop_list_, first_new_value;

    x_note_fn_call(134,2);
    form = Nil;
    ab_loop_list_ = pane_description;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    first_new_value = create_pseudo_frame(FIRST(form));
    M_FIRST(form) = first_new_value;
    goto next_loop;
  end_loop:;
    return VALUES_1(pane_description);
}

/* RECLAIM-MODIFIED-PANE-DESCRIPTION */
Object reclaim_modified_pane_description(modified_pane_description)
    Object modified_pane_description;
{
    Object form, ab_loop_list_, temp;

    x_note_fn_call(134,3);
    form = Nil;
    ab_loop_list_ = modified_pane_description;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(form);
    M_CAR(form) = Nil;
    reclaim_pseudo_frame_1(temp);
    goto next_loop;
  end_loop:;
    return reclaim_slot_value(modified_pane_description);
}

static Object Qkb_workspace;       /* kb-workspace */

/* CHECK-PANE-DESCRIPTION-FOR-UNWRITTEN-WORKSPACES */
Object check_pane_description_for_unwritten_workspaces(modified_pane_description)
    Object modified_pane_description;
{
    Object form, ab_loop_list_, pf, fsn, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, workspace, gensymed_symbol, gensymed_symbol_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(134,4);
  next_loop:
    form = Nil;
    ab_loop_list_ = modified_pane_description;
    pf = Nil;
    fsn = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pf = FIRST(form);
    fsn = ISVREF(pf,(SI_Long)2L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qkb_workspace);
    next_loop_2:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_3:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_1;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_1;
	  goto next_loop_3;
	end_loop_1:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_2;
      workspace = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
      gensymed_symbol_1 = fsn;
      if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
	      FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : TRUEP(Nil)) : 
	      FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
	      FIXNUM_EQ(M_CAR(gensymed_symbol),M_CAR(gensymed_symbol_1)) 
	      && FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1))) {
	  temp = (SI_Long)0L != (IFIX(ISVREF(workspace,(SI_Long)5L)) & 
		  (SI_Long)2L) ? TRUEP(T) : TRUEP(Nil);
	  goto end_1;
      }
      goto next_loop_2;
    end_loop_2:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if ( !temp) {
	modified_pane_description = delete_eq(form,modified_pane_description);
	temp = TRUEP(T);
	goto end_2;
    }
    goto next_loop_1;
  end_loop:
    temp = TRUEP(Qnil);
  end_2:;
    if ( !temp)
	goto end_loop_3;
    goto next_loop;
  end_loop_3:
    return VALUES_1(modified_pane_description);
}

static Object Qdefault_x_scale;    /* default-x-scale */

static Object float_constant;      /* 0.0 */

static Object Qdefault_y_scale;    /* default-y-scale */

/* MAKE-IMAGE-PLANE-DESCRIPTION */
Object make_image_plane_description(image_plane,record_window_position_too_qm)
    Object image_plane, record_window_position_too_qm;
{
    Object gensym_window, x_in_workspace, y_in_workspace;
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, scale, temp, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value, numerator_1, denominator_1;
    SI_Long value, temp_1;
    double temp_2, temp_3;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(134,5);
    gensym_window = ISVREF(ISVREF(image_plane,(SI_Long)2L),(SI_Long)2L);
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
	      value = (IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),
		      ISVREF(image_plane,(SI_Long)8L))) >>  -  - 
		      (SI_Long)1L) - IFIX(Current_x_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  x_in_workspace = FIX(value);
	      else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value && value < IFIX(Isqrt_of_most_positive_fixnum)))
		  x_in_workspace = inverse_scalef_function(scale,FIX(value));
	      else if (value >= (SI_Long)0L) {
		  temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  - 
			   - (SI_Long)1L)) / IFIX(scale));
		  x_in_workspace = temp;
	      }
	      else {
		  temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  
			  -  - (SI_Long)1L)) / IFIX(scale);
		  temp = FIXNUM_NEGATE(FIX(temp_1));
		  x_in_workspace = temp;
	      }
	      scale = Current_image_y_scale;
	      value = (IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)7L),
		      ISVREF(image_plane,(SI_Long)9L))) >>  -  - 
		      (SI_Long)1L) - IFIX(Current_y_origin_of_drawing);
	      if (IFIX(scale) == (SI_Long)4096L)
		  y_in_workspace = FIX(value);
	      else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		      value && value < IFIX(Isqrt_of_most_positive_fixnum)))
		  y_in_workspace = inverse_scalef_function(scale,FIX(value));
	      else if (value >= (SI_Long)0L) {
		  temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  - 
			   - (SI_Long)1L)) / IFIX(scale));
		  y_in_workspace = temp;
	      }
	      else {
		  temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  
			  -  - (SI_Long)1L)) / IFIX(scale);
		  temp = FIXNUM_NEGATE(FIX(temp_1));
		  y_in_workspace = temp;
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = ISVREF(image_plane,(SI_Long)5L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = x_in_workspace;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = y_in_workspace;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    numerator_1 = ISVREF(image_plane,(SI_Long)11L);
    denominator_1 = get_gensym_window_parameter(gensym_window,
	    Qdefault_x_scale);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(numerator_1,float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(denominator_1,float_constant);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	car_new_value = 
		convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
		temp_3));
    }
    POP_LOCAL_ALLOCATION(0,0);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    numerator_1 = ISVREF(image_plane,(SI_Long)12L);
    denominator_1 = get_gensym_window_parameter(gensym_window,
	    Qdefault_y_scale);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(numerator_1,float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(denominator_1,float_constant);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	car_new_value = 
		convert_to_magnification(DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
		temp_3));
    }
    POP_LOCAL_ALLOCATION(0,0);
    M_CAR(gensymed_symbol_1) = car_new_value;
    return VALUES_1(nconc2(gensymed_symbol,record_window_position_too_qm ? 
	    slot_value_list_2(record_window_position_too_qm ? 
	    FIX(IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),
	    ISVREF(image_plane,(SI_Long)8L))) >>  -  - (SI_Long)1L) : Nil,
	    record_window_position_too_qm ? 
	    FIX(IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)7L),
	    ISVREF(image_plane,(SI_Long)9L))) >>  -  - (SI_Long)1L) : Nil) 
	    : Nil));
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* RESTORE-IMAGE-PLANES-TO-PANE */
Object restore_image_planes_to_pane varargs_1(int, n)
{
    Object pane, pane_description;
    Object frame_serial_number_qm, check_user_restrictions_qm;
    Object clear_image_planes_of_other_kb_workspaces_qm, specific_module_qm;
    Object image_plane, ab_loop_list_, workspace_qm, sub_class_bit_vector;
    Object frame_description_reference, workspace;
    Object workspace_x_at_center_of_pane, workspace_y_at_center_of_pane;
    Object magnification_of_default_x_scale, magnification_of_default_y_scale;
    Object x_in_window_qm, y_in_window_qm, ab_loop_desetq_, temp_1;
    Object gensymed_symbol_3, xa, ya, ab_loop_list__1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(134,6);
    INIT_ARGS_nonrelocating();
    pane = REQUIRED_ARG_nonrelocating();
    pane_description = REQUIRED_ARG_nonrelocating();
    frame_serial_number_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    check_user_restrictions_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    clear_image_planes_of_other_kb_workspaces_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    specific_module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (clear_image_planes_of_other_kb_workspaces_qm) {
      next_loop:
	image_plane = Nil;
	ab_loop_list_ = ISVREF(pane,(SI_Long)5L);
	workspace_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	image_plane = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	workspace_qm = ISVREF(image_plane,(SI_Long)5L);
	if (workspace_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	    delete_image_plane(image_plane);
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp)
	    goto end_loop_1;
	goto next_loop;
      end_loop_1:;
    }
    frame_description_reference = Nil;
    workspace = Nil;
    workspace_x_at_center_of_pane = Nil;
    workspace_y_at_center_of_pane = Nil;
    magnification_of_default_x_scale = Nil;
    magnification_of_default_y_scale = Nil;
    x_in_window_qm = Nil;
    y_in_window_qm = Nil;
    ab_loop_list_ = pane_description;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    workspace = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    workspace_x_at_center_of_pane = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    workspace_y_at_center_of_pane = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    magnification_of_default_x_scale = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    magnification_of_default_y_scale = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    x_in_window_qm = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    y_in_window_qm = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp =  !TRUEP(frame_serial_number_qm);
    if (temp);
    else {
	gensymed_symbol_3 = ISVREF(workspace,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol_3) ? IFIX(gensymed_symbol_3) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number_qm))
	    temp = FIXNUMP(gensymed_symbol_3) ? 
		    FIXNUM_LT(frame_serial_number_qm,gensymed_symbol_3) : 
		    TRUEP(T);
	else if (FIXNUMP(gensymed_symbol_3))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number_qm);
	    ya = M_CAR(gensymed_symbol_3);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number_qm),
			M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    if ((temp ?  !TRUEP(check_user_restrictions_qm) || 
	    workspaces_can_be_shown_at_this_kb_level_p(workspace,
	    Current_workstation) : TRUEP(Nil)) ?  
	    !TRUEP(specific_module_qm) || 
	    EQ(get_module_block_is_in(workspace),specific_module_qm) : 
	    TRUEP(Nil)) {
	image_plane = Nil;
	ab_loop_list__1 = ISVREF(workspace,(SI_Long)16L);
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	image_plane = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(pane,ISVREF(image_plane,(SI_Long)2L))) {
	    temp = TRUEP(Nil);
	    goto end_2;
	}
	goto next_loop_3;
      end_loop_3:
	temp = TRUEP(T);
	goto end_2;
	temp = TRUEP(Qnil);
      end_2:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	frame_description_reference = 
		lookup_frame_description_reference_of_block_qm(workspace);
	if (FLOATP(magnification_of_default_x_scale) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(magnification_of_default_x_scale) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_x_scale)) 
		== (SI_Long)1L) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(magnification_of_default_x_scale) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_x_scale)) 
		    == (SI_Long)1L)
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(magnification_of_default_x_scale,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(magnification_of_default_x_scale) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_x_scale)) 
		    == (SI_Long)1L)
		temp_1 = aref1(magnification_of_default_x_scale,
			FIX((SI_Long)0L));
	    else
		temp_1 = magnification_of_default_x_scale;
	    magnification_of_default_x_scale = 
		    convert_to_magnification(temp_1);
	}
	if (FLOATP(magnification_of_default_y_scale) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(magnification_of_default_y_scale) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_y_scale)) 
		== (SI_Long)1L) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(magnification_of_default_y_scale) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_y_scale)) 
		    == (SI_Long)1L)
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(magnification_of_default_y_scale,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(magnification_of_default_y_scale) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(magnification_of_default_y_scale)) 
		    == (SI_Long)1L)
		temp_1 = aref1(magnification_of_default_y_scale,
			FIX((SI_Long)0L));
	    else
		temp_1 = magnification_of_default_y_scale;
	    magnification_of_default_y_scale = 
		    convert_to_magnification(temp_1);
	}
	image_plane = get_available_image_plane(pane,
		frame_description_reference,T);
	temp_1 = workspace;
	temp_2 = get_gensym_window_parameter(ISVREF(pane,(SI_Long)2L),
		Qdefault_x_scale);
	temp_2 = FIX(IFIX(FIXNUM_TIMES(temp_2,
		magnification_of_default_x_scale)) + (SI_Long)128L >>  -  
		- (SI_Long)8L);
	temp_3 = get_gensym_window_parameter(ISVREF(pane,(SI_Long)2L),
		Qdefault_y_scale);
	put_image_on_image_plane(10,image_plane,temp_1,temp_2,
		FIX(IFIX(FIXNUM_TIMES(temp_3,
		magnification_of_default_y_scale)) + (SI_Long)128L >>  -  
		- (SI_Long)8L),Nil,Nil,workspace_x_at_center_of_pane,
		workspace_y_at_center_of_pane,x_in_window_qm,y_in_window_qm);
	require_that_image_plane_be_visible(1,image_plane);
    }
    goto next_loop_2;
  end_loop_2:
    return VALUES_1(Qnil);
}

static Object Qlogged_in;          /* logged-in */

/* RESTORE-IMAGE-PLANES-TO-PANE-NOW-OR-LATER */
Object restore_image_planes_to_pane_now_or_later varargs_1(int, n)
{
    Object pane_description;
    Object redisplay_logbook_qm, specific_module_qm, entry, ab_loop_list_;
    Object gensymed_symbol, x, xa, ya, frame_serial_number_setf_arg;
    Object reference_serial_number_for_saved_detail_pane_description_new_value;
    Object workstation, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(134,7);
    INIT_ARGS_nonrelocating();
    pane_description = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    redisplay_logbook_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    specific_module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
  next_loop:
    entry = Nil;
    ab_loop_list_ = Saved_detail_pane_description;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(CAR(entry),(SI_Long)3L);
    x = CAR(entry);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(Reference_serial_number_for_saved_detail_pane_description))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(Reference_serial_number_for_saved_detail_pane_description,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(Reference_serial_number_for_saved_detail_pane_description);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(Reference_serial_number_for_saved_detail_pane_description),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if (temp) {
	Saved_detail_pane_description = delete_slot_value_element_1(entry,
		Saved_detail_pane_description);
	reclaim_slot_value(entry);
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop_1;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp)
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    Saved_detail_pane_description = 
	    nconc2(copy_for_slot_value(pane_description),
	    Saved_detail_pane_description);
    frame_serial_number_setf_arg = Current_frame_serial_number;
    reference_serial_number_for_saved_detail_pane_description_new_value = 
	    (FIXNUMP(Reference_serial_number_for_saved_detail_pane_description) 
	    ||  
	    !TRUEP(Reference_serial_number_for_saved_detail_pane_description)) 
	    && (FIXNUMP(frame_serial_number_setf_arg) ||  
	    !TRUEP(frame_serial_number_setf_arg)) ? 
	    frame_serial_number_setf_arg : 
	    frame_serial_number_setf_helper_1(Reference_serial_number_for_saved_detail_pane_description,
	    frame_serial_number_setf_arg);
    Reference_serial_number_for_saved_detail_pane_description = 
	    reference_serial_number_for_saved_detail_pane_description_new_value;
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in)) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp_1);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    restore_current_workstation_detail_pane(3,
					    Backup_case_qm,
					    redisplay_logbook_qm,
					    specific_module_qm);
				    if (BOUNDP(Qmain_kb_being_read_qm) && 
					    Main_kb_being_read_qm)
					note_gensym_window_initialized(Current_workstation_window);
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
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
    }
    goto next_loop_2;
  end_loop_2:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* PUT-WORKSPACE-INTO-DETAIL-PANE-LAYOUT */
Object put_workspace_into_detail_pane_layout(workspace)
    Object workspace;
{
    Object image_plane_description, ab_loop_list_, stored_workspace;
    Object gensymed_symbol, xa, ya, temp_1, gensymed_symbol_1;
    Object gensymed_symbol_2, temp_2, frame_serial_number_setf_arg;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, car_new_value;
    char temp;

    x_note_fn_call(134,8);
  next_loop:
    image_plane_description = Nil;
    ab_loop_list_ = Saved_detail_pane_description;
    stored_workspace = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stored_workspace = FIRST(image_plane_description);
    temp = EQ(stored_workspace,workspace);
    if (temp);
    else {
	gensymed_symbol = ISVREF(stored_workspace,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(stored_workspace) ? 
		EQ(ISVREF(stored_workspace,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(Reference_serial_number_for_saved_detail_pane_description))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(Reference_serial_number_for_saved_detail_pane_description,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = 
		    M_CAR(Reference_serial_number_for_saved_detail_pane_description);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(Reference_serial_number_for_saved_detail_pane_description),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
    }
    if (temp) {
	Saved_detail_pane_description = 
		delete_slot_value_element_1(image_plane_description,
		Saved_detail_pane_description);
	reclaim_slot_value(image_plane_description);
	temp = TRUEP(T);
	goto end_1;
    }
    goto next_loop_1;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp)
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    temp_1 = Saved_detail_pane_description;
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = workspace;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
    gensymed_symbol_2 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    gensymed_symbol_4 = (SI_Long)1L;
    car_new_value = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    gensymed_symbol_2 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol_2);
    gensymed_symbol_2 = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol_2);
    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    gensymed_symbol_4 = (SI_Long)1L;
    car_new_value = gensymed_symbol_3 >>  -  - gensymed_symbol_4;
    M_CAR(gensymed_symbol_1) = FIX(car_new_value);
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp_2 = convert_to_magnification(FIX((SI_Long)1L));
    M_CAR(gensymed_symbol_1) = temp_2;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp_2 = convert_to_magnification(FIX((SI_Long)1L));
    M_CAR(gensymed_symbol_1) = temp_2;
    Saved_detail_pane_description = nconc2(temp_1,
	    slot_value_cons_1(gensymed_symbol,Nil));
    frame_serial_number_setf_arg = Current_frame_serial_number;
    temp_2 = 
	    (FIXNUMP(Reference_serial_number_for_saved_detail_pane_description) 
	    ||  
	    !TRUEP(Reference_serial_number_for_saved_detail_pane_description)) 
	    && (FIXNUMP(frame_serial_number_setf_arg) ||  
	    !TRUEP(frame_serial_number_setf_arg)) ? 
	    frame_serial_number_setf_arg : 
	    frame_serial_number_setf_helper_1(Reference_serial_number_for_saved_detail_pane_description,
	    frame_serial_number_setf_arg);
    Reference_serial_number_for_saved_detail_pane_description = temp_2;
    return VALUES_1(Reference_serial_number_for_saved_detail_pane_description);
}

static Object Qcenter;             /* center */

/* PUT-WORKSPACE-INTO-DETAIL-PANES */
Object put_workspace_into_detail_panes(workspace)
    Object workspace;
{
    Object workstation, ab_loop_list_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(134,9);
    SAVE_STACK();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(workstation,(SI_Long)28L),Qlogged_in)) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    put_workspace_on_pane_function(workspace,
					    Current_workstation_detail_pane,
					    Qcenter,Qcenter,Nil,
					    FIX((SI_Long)11L),Nil,Nil,Nil,
					    Nil,Nil,Nil,Nil);
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
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
    }
    goto next_loop;
  end_loop:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* PUT-WORKSPACE-ON-DETAIL-PANES-NOW-OR-LATER */
Object put_workspace_on_detail_panes_now_or_later(workspace)
    Object workspace;
{
    x_note_fn_call(134,10);
    put_workspace_into_detail_pane_layout(workspace);
    return put_workspace_into_detail_panes(workspace);
}

/* EMPTY-KB-P */
Object empty_kb_p()
{
    x_note_fn_call(134,11);
    return VALUES_1( 
	    !TRUEP(lookup_kb_specific_property_value(Qkb_workspace,
	    Instances_specific_to_this_class_kbprop)) ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Last_assigned_kb_serial_number, Qlast_assigned_kb_serial_number);

/* INITIALIZE-CURRENT-KB-SERIAL-NUMBER */
Object initialize_current_kb_serial_number()
{
    Object last_assigned_kb_serial_number_new_value;

    x_note_fn_call(134,12);
    last_assigned_kb_serial_number_new_value = 
	    FIXNUM_ADD1(Last_assigned_kb_serial_number);
    Last_assigned_kb_serial_number = last_assigned_kb_serial_number_new_value;
    return VALUES_1(Last_assigned_kb_serial_number);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object string_constant;     /* "~a" */

static Object Qkb;                 /* kb */

static Object Qattribute;          /* attribute */

static Object Qstatistics;         /* statistics */

/* CLEAR-BASE-NAME-FROM-DEFAULT-LOAD-PATHNAMES */
Object clear_base_name_from_default_load_pathnames()
{
    volatile Object user_name_string;
    volatile Object working_pathname;
    Object temp, new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(134,13);
    SAVE_STACK();
    if (Current_kb_pathname_qm) {
	user_name_string = Qunbound_in_protected_let;
	working_pathname = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    user_name_string = tformat_text_string(2,string_constant,
		    get_current_user_name());
	    temp = user_name_string;
	    working_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,temp,make_default_file_type(Qkb),Knewest,Nil);
	    new_value = gensym_merge_pathnames_function(working_pathname,
		    Current_kb_pathname_qm,Nil);
	    reclaim_pathname_or_string(Current_kb_pathname_qm);
	    if (text_string_p(new_value)) {
		temp = gensym_pathname(new_value);
		reclaim_text_string(new_value);
		Current_kb_pathname_qm = temp;
	    }
	    else
		Current_kb_pathname_qm = new_value;
	}
	POP_UNWIND_PROTECT(0);
	if (working_pathname) {
	    if ( !EQ(working_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(working_pathname);
	}
	if (user_name_string) {
	    if ( !EQ(user_name_string,Qunbound_in_protected_let))
		reclaim_text_string(user_name_string);
	}
	CONTINUE_UNWINDING(0);
    }
    if (Current_attribute_file_pathname_qm) {
	user_name_string = Qunbound_in_protected_let;
	working_pathname = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    user_name_string = tformat_text_string(2,string_constant,
		    get_current_user_name());
	    temp = user_name_string;
	    working_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,temp,make_default_file_type(Qattribute),Knewest,Nil);
	    new_value = gensym_merge_pathnames_function(working_pathname,
		    Current_attribute_file_pathname_qm,Nil);
	    reclaim_pathname_or_string(Current_attribute_file_pathname_qm);
	    if (text_string_p(new_value)) {
		temp = gensym_pathname(new_value);
		reclaim_text_string(new_value);
		Current_attribute_file_pathname_qm = temp;
	    }
	    else
		Current_attribute_file_pathname_qm = new_value;
	}
	POP_UNWIND_PROTECT(0);
	if (working_pathname) {
	    if ( !EQ(working_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(working_pathname);
	}
	if (user_name_string) {
	    if ( !EQ(user_name_string,Qunbound_in_protected_let))
		reclaim_text_string(user_name_string);
	}
	CONTINUE_UNWINDING(0);
    }
    if (Current_statistics_file_pathname_qm) {
	user_name_string = Qunbound_in_protected_let;
	working_pathname = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    user_name_string = tformat_text_string(2,string_constant,
		    get_current_user_name());
	    temp = user_name_string;
	    working_pathname = 
		    gensym_make_pathname_with_copied_components(Nil,Nil,
		    Nil,temp,make_default_file_type(Qstatistics),Knewest,Nil);
	    new_value = gensym_merge_pathnames_function(working_pathname,
		    Current_statistics_file_pathname_qm,Nil);
	    reclaim_pathname_or_string(Current_statistics_file_pathname_qm);
	    if (text_string_p(new_value)) {
		temp = gensym_pathname(new_value);
		reclaim_text_string(new_value);
		Current_statistics_file_pathname_qm = temp;
	    }
	    else
		Current_statistics_file_pathname_qm = new_value;
	    SAVE_VALUES(VALUES_1(Current_statistics_file_pathname_qm));
	}
	POP_UNWIND_PROTECT(0);
	if (working_pathname) {
	    if ( !EQ(working_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(working_pathname);
	}
	if (user_name_string) {
	    if ( !EQ(user_name_string,Qunbound_in_protected_let))
		reclaim_text_string(user_name_string);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Ui_client_interface_saved_icp_socket_list, Qui_client_interface_saved_icp_socket_list);

DEFINE_VARIABLE_WITH_SYMBOL(Ui_client_interface_saved_session_list, Qui_client_interface_saved_session_list);

static Object Qcallback_representation_callback_serial_number;  /* callback-representation-callback-serial-number */

static Object Qitem_representation_denotation;  /* item-representation-denotation */

static Object Qrepresentation_address;  /* representation-address */

/* MAKE-STORAGE-OF-REPRESENTATION-DATA */
Object make_storage_of_representation_data(representation)
    Object representation;
{
    Object slot_list, slot_name, ab_loop_list_, value, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, element, ab_loop_list__1;
    Object ab_loopvar__3, ab_loopvar__4, storage;

    x_note_fn_call(134,14);
    slot_list = 
	    get_slots_to_save_in_clear_kb_for_representation(representation);
    slot_name = Nil;
    ab_loop_list_ = slot_list;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    value = EQ(slot_name,Qcallback_representation_callback_serial_number) ?
	     (ISVREF(representation,(SI_Long)11L) ? 
	    frame_serial_number_0() : Nil) : 
	    get_slot_value_function(representation,slot_name,Nil);
    if (EQ(slot_name,Qcallback_representation_callback_serial_number))
	temp = copy_frame_serial_number(value);
    else if (EQ(slot_name,Qitem_representation_denotation))
	temp = copy_denotation(value);
    else if (EQ(slot_name,Qrepresentation_address)) {
	element = Nil;
	ab_loop_list__1 = value;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
	ab_loopvar__4 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loopvar__4 = slot_value_cons_1(element,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar__2;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = copy_for_slot_value(value);
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    storage = ab_loopvar_;
    goto end_2;
    storage = Qnil;
  end_2:;
    storage = gensym_cons_1(ISVREF(ISVREF(representation,(SI_Long)1L),
	    (SI_Long)1L),storage);
    return VALUES_1(storage);
}

DEFINE_VARIABLE_WITH_SYMBOL(Deleting_ui_client_interfaces_for_clear_kb, Qdeleting_ui_client_interfaces_for_clear_kb);

Object Ui_client_session_slots_to_save_for_clear_kb = UNBOUND;

static Object Qui_client_session;  /* ui-client-session */

static Object Qcallback_representation;  /* callback-representation */

static Object Qgsi_interface;      /* gsi-interface */

static Object Qgsi_interface_icp_socket;  /* gsi-interface-icp-socket */

static Object Qgsi_connection_configuration;  /* gsi-connection-configuration */

static Object Qremote_process_initialization_string;  /* remote-process-initialization-string */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qui_client_interface_callback_qm;  /* ui-client-interface-callback? */

static Object Qui_client_interface_callback_data;  /* ui-client-interface-callback-data */

static Object Qui_client_interface_module_information_callback_qm;  /* ui-client-interface-module-information-callback? */

static Object Qui_client_interface_module_information_callback_data;  /* ui-client-interface-module-information-callback-data */

static Object Qui_client_interface_progress_callback_qm;  /* ui-client-interface-progress-callback? */

static Object Qui_client_interface_progress_callback_data;  /* ui-client-interface-progress-callback-data */

static Object Qui_client_interface_dialog_callback_qm;  /* ui-client-interface-dialog-callback? */

static Object Qui_client_interface_dialog_callback_data;  /* ui-client-interface-dialog-callback-data */

static Object Qui_client_interface_dialog_list;  /* ui-client-interface-dialog-list */

static Object Qui_client_interface_sessions;  /* ui-client-interface-sessions */

/* SAVE-AND-DELETE-UI-CLIENT-INTERFACES */
Object save_and_delete_ui_client_interfaces()
{
    Object saved_ui_client_sessions, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object frame, temp_1, slot_name, ab_loop_list_, value, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, temp_2, representation_list;
    Object frame_representation, gensymed_symbol, sub_class_bit_vector, temp_3;
    Object icp_socket_qm, connection_configuration, gensymed_symbol_4;
    Object car_new_value, thing, session;
    Object deleting_ui_client_interfaces_for_clear_kb;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(2);

    x_note_fn_call(134,15);
    saved_ui_client_sessions = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qui_client_session);
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
      saved_ui_client_sessions = gensym_cons_1(frame,saved_ui_client_sessions);
      temp_1 = save_icp_object_map_for_registered_item(frame);
      slot_name = Nil;
      ab_loop_list_ = Ui_client_session_slots_to_save_for_clear_kb;
      value = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      slot_name = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      value = get_slot_value_function(frame,slot_name,Nil);
      ab_loopvar__4 = gensym_cons_1(copy_for_slot_value(value),Nil);
      if (ab_loopvar__3)
	  M_CDR(ab_loopvar__3) = ab_loopvar__4;
      else
	  ab_loopvar__2 = ab_loopvar__4;
      ab_loopvar__3 = ab_loopvar__4;
      goto next_loop_2;
    end_loop_2:
      temp_2 = ab_loopvar__2;
      goto end_1;
      temp_2 = Qnil;
    end_1:;
      representation_list = Nil;
      frame_representation = Nil;
      ab_loop_list_ = ISVREF(frame,(SI_Long)9L);
    next_loop_3:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_3;
      frame_representation = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensymed_symbol = 
	      lookup_global_or_kb_specific_property_value(Qcallback_representation,
	      Class_description_gkbprop);
      if (gensymed_symbol) {
	  sub_class_bit_vector = ISVREF(ISVREF(frame_representation,
		  (SI_Long)1L),(SI_Long)19L);
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
	  temp_3 = make_storage_of_representation_data(frame_representation);
	  representation_list = gensym_cons_1(temp_3,representation_list);
      }
      goto next_loop_3;
    end_loop_3:
      temp_3 = representation_list;
      goto end_2;
      temp_3 = Qnil;
    end_2:;
      Ui_client_interface_saved_session_list = 
	      gensym_cons_1(gensym_list_3(temp_1,temp_2,temp_3),
	      Ui_client_interface_saved_session_list);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      icp_socket_qm = Nil;
      connection_configuration = Nil;
      ab_loopvar_ = collect_subclasses(Qgsi_interface);
    next_loop_4:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_5:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_4;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_4;
	  goto next_loop_5;
	end_loop_4:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_5;
      frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      icp_socket_qm = get_slot_value_function(frame,
	      Qgsi_interface_icp_socket,Nil);
      temp_3 = get_slot_value_function(frame,Qgsi_connection_configuration,
	      Nil);
      connection_configuration = CAR(temp_3);
      if (icp_socket_qm && (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) 
	      & (SI_Long)16777216L)) {
	  gensymed_symbol = make_gensym_list_1(FIX((SI_Long)18L));
	  gensymed_symbol_4 = gensymed_symbol;
	  M_CAR(gensymed_symbol_4) = icp_socket_qm;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = CONSP(connection_configuration) ? 
		  CAR(connection_configuration) : Nil;
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  if (CONSP(connection_configuration)) {
	      thing = CADR(connection_configuration);
	      car_new_value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		      (SI_Long)0L ? copy_text_string(thing) : thing;
	  }
	  else
	      car_new_value = Nil;
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  if (CONSP(connection_configuration)) {
	      thing = CADDR(connection_configuration);
	      car_new_value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		      (SI_Long)0L ? copy_text_string(thing) : thing;
	  }
	  else
	      car_new_value = Nil;
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  thing = get_slot_value_function(frame,
		  Qremote_process_initialization_string,Nil);
	  car_new_value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		  (SI_Long)0L ? copy_text_string(thing) : thing;
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = get_slot_value_function(frame,
		  Qname_or_names_for_frame,Nil);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = get_slot_value_if_any_function(frame,
		  Qui_client_interface_callback_qm,Nil);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  thing = get_slot_value_if_any_function(frame,
		  Qui_client_interface_callback_data,Nil);
	  car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		  SIMPLE_VECTOR_P(thing) ? thing : 
		  copy_if_evaluation_value_1(thing);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = get_slot_value_if_any_function(frame,
		  Qui_client_interface_module_information_callback_qm,Nil);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  thing = get_slot_value_if_any_function(frame,
		  Qui_client_interface_module_information_callback_data,Nil);
	  car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		  SIMPLE_VECTOR_P(thing) ? thing : 
		  copy_if_evaluation_value_1(thing);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = get_slot_value_if_any_function(frame,
		  Qui_client_interface_progress_callback_qm,Nil);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  thing = get_slot_value_if_any_function(frame,
		  Qui_client_interface_progress_callback_data,Nil);
	  car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		  SIMPLE_VECTOR_P(thing) ? thing : 
		  copy_if_evaluation_value_1(thing);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = get_slot_value_if_any_function(frame,
		  Qui_client_interface_dialog_callback_qm,Nil);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  thing = get_slot_value_if_any_function(frame,
		  Qui_client_interface_dialog_callback_data,Nil);
	  car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		  SIMPLE_VECTOR_P(thing) ? thing : 
		  copy_if_evaluation_value_1(thing);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = 
		  copy_for_slot_value(get_slot_value_if_any_function(frame,
		  Qui_client_interface_dialog_list,Nil));
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  session = Nil;
	  ab_loop_list_ = get_slot_value_if_any_function(frame,
		  Qui_client_interface_sessions,Nil);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	next_loop_6:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_6;
	  session = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loopvar__4 = gensym_cons_1(position(2,session,
		  saved_ui_client_sessions),Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
	  goto next_loop_6;
	end_loop_6:
	  goto end_3;
	  ab_loopvar__2 = Qnil;
	end_3:;
	  M_CAR(gensymed_symbol_4) = ab_loopvar__2;
	  gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
	  car_new_value = save_icp_object_map_for_registered_item(frame);
	  M_CAR(gensymed_symbol_4) = car_new_value;
	  Ui_client_interface_saved_icp_socket_list = 
		  gensym_cons_1(gensymed_symbol,
		  Ui_client_interface_saved_icp_socket_list);
	  set_slot_value_function(frame,Qgsi_interface_icp_socket,Nil,Nil);
	  SVREF(icp_socket_qm,FIX((SI_Long)5L)) = Nil;
      }
      goto next_loop_4;
    end_loop_5:;
    POP_SPECIAL();
    deleting_ui_client_interfaces_for_clear_kb = T;
    PUSH_SPECIAL_WITH_SYMBOL(Deleting_ui_client_interfaces_for_clear_kb,Qdeleting_ui_client_interfaces_for_clear_kb,deleting_ui_client_interfaces_for_clear_kb,
	    1);
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      frame = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qgsi_interface);
      next_loop_7:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_8:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_7;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_7;
	    goto next_loop_8;
	  end_loop_7:
	    temp =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    goto end_loop_8;
	frame = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	delete_frame(frame);
	goto next_loop_7;
      end_loop_8:;
      POP_SPECIAL();
    POP_SPECIAL();
    return reclaim_gensym_list_1(saved_ui_client_sessions);
}

static Object Qframe_representations;  /* frame-representations */

/* RESTORE-UI-CLIENT-SESSION-ITEM-REPRESENTATIONS */
Object restore_ui_client_session_item_representations(frame,
	    representation_list)
    Object frame, representation_list;
{
    Object representation_data, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, representations;

    x_note_fn_call(134,16);
    representation_data = Nil;
    ab_loop_list_ = representation_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation_data = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    slot_value_cons_1(restore_ui_client_session_item_representation(representation_data,
	    frame),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    representations = ab_loopvar_;
    goto end_1;
    representations = Qnil;
  end_1:;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qframe_representations);
    return VALUES_1(SVREF(frame,FIX((SI_Long)9L)) = representations);
}

static Object Qsocket;             /* socket */

static Object Qitem_representation;  /* item-representation */

static Object Qg2_defstruct_structure_name_access_error_g2_struct;  /* g2-defstruct-structure-name::access-error-g2-struct */

static Object string_constant_1;   /* "Unable to restore ui-client-session ~NF properly" */

/* RESTORE-UI-CLIENT-SESSION-ITEM-REPRESENTATION */
Object restore_ui_client_session_item_representation(representation_data,frame)
    Object representation_data, frame;
{
    Object representation_class, representation, slot_name, ab_loop_list_;
    Object value, ab_loop_list__1, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value, address_qm, icp_socket_qm;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, denotation;
    Object definition_error_or_inner_item_index, class_description_qm, temp;
    Object result;

    x_note_fn_call(134,17);
    representation_class = CAR(representation_data);
    representation = make_frame(representation_class);
    slot_name = Nil;
    ab_loop_list_ = 
	    get_slots_to_save_in_clear_kb_for_representation(representation);
    value = Nil;
    ab_loop_list__1 = CDR(representation_data);
    ISVREF(representation,(SI_Long)9L) = frame;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    value = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(slot_name,Qcallback_representation_callback_serial_number)) {
	frame_serial_number_setf_arg = value;
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = svref_new_value;
    }
    else
	change_slot_value(3,representation,slot_name,value);
    goto next_loop;
  end_loop:
    address_qm = ISVREF(representation,(SI_Long)8L);
    icp_socket_qm = address_qm ? getf(address_qm,Qsocket,_) : Qnil;
    if (icp_socket_qm &&  !EQ(icp_socket_qm,Local_pseudo_socket)) {
	gensym_push_modify_macro_arg = representation;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(icp_socket_qm,(SI_Long)39L);
	svref_new_value = gensym_cons_1(car_1,cdr_1);
	SVREF(icp_socket_qm,FIX((SI_Long)39L)) = svref_new_value;
    }
    if (EQ(representation_class,Qitem_representation)) {
	denotation = ISVREF(representation,(SI_Long)13L);
	result = check_denotation_well_defined(frame,denotation);
	MVS_2(result,definition_error_or_inner_item_index,
		class_description_qm);
	if (SIMPLE_VECTOR_P(definition_error_or_inner_item_index) && 
		EQ(ISVREF(definition_error_or_inner_item_index,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_access_error_g2_struct)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_1,frame);
	    Suppress_warning_message_header_qm = Nil;
	}
	else
	    install_subscription(class_description_qm,representation,
		    denotation,definition_error_or_inner_item_index);
    }
    store_callback_representation(representation);
    reclaim_gensym_list_1(representation_data);
    temp = representation;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qab_gensym;          /* gensym */

static Object Qui_client_interface;  /* ui-client-interface */

static Object Qui_client_session_parent_interface;  /* ui-client-session-parent-interface */

/* RESTORE-UI-CLIENT-INTERFACES */
Object restore_ui_client_interfaces()
{
    Object frame_spec, icp_object_map, slot_value_list, representation_list;
    Object frame, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, gensym_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2, temp_1, slot_name;
    Object ab_loop_list_, value, ab_loop_list__1, sessions, current_icp_socket;
    Object network_type, host, port, remote_process_initialization_string;
    Object name_or_names_for_frame, class_1, callback_qm, callback_data;
    Object module_information_callback_qm, module_information_callback_data;
    Object progress_callback_qm, progress_callback_data, dialog_callback_qm;
    Object dialog_callback_data, dialog_list, session_position_list;
    Object ui_client_interface, gensymed_symbol, sub_class_bit_vector;
    Object position_1, session, scope_conses, module_info;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(2);

    x_note_fn_call(134,18);
    frame_spec = Nil;
    icp_object_map = Nil;
    slot_value_list = Nil;
    representation_list = Nil;
    frame = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(Ui_client_interface_saved_session_list))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = Ui_client_interface_saved_session_list;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Ui_client_interface_saved_session_list = next_cons;
    frame_spec = gensym_pop_store;
    icp_object_map = CAR(frame_spec);
    temp_1 = CDR(frame_spec);
    slot_value_list = CAR(temp_1);
    temp_1 = CDR(frame_spec);
    temp_1 = CDR(temp_1);
    representation_list = CAR(temp_1);
    frame = make_ui_client_session_internal();
    restore_icp_object_map_for_registered_item(frame,icp_object_map);
    slot_name = Nil;
    ab_loop_list_ = Ui_client_session_slots_to_save_for_clear_kb;
    value = Nil;
    ab_loop_list__1 = slot_value_list;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    slot_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    value = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    change_slot_value(3,frame,slot_name,value);
    goto next_loop_1;
  end_loop_1:;
    restore_ui_client_session_item_representations(frame,representation_list);
    reclaim_gensym_list_1(representation_list);
    reclaim_gensym_list_1(slot_value_list);
    reclaim_gensym_list_1(frame_spec);
    ab_loopvar__2 = gensym_cons_1(frame,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    sessions = ab_loopvar_;
    goto end_1;
    sessions = Qnil;
  end_1:;
    frame_spec = Nil;
    current_icp_socket = Nil;
    network_type = Nil;
    host = Nil;
    port = Nil;
    remote_process_initialization_string = Nil;
    name_or_names_for_frame = Nil;
    class_1 = Nil;
    callback_qm = Nil;
    callback_data = Nil;
    module_information_callback_qm = Nil;
    module_information_callback_data = Nil;
    progress_callback_qm = Nil;
    progress_callback_data = Nil;
    dialog_callback_qm = Nil;
    dialog_callback_data = Nil;
    dialog_list = Nil;
    session_position_list = Nil;
    icp_object_map = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	    1);
    next_loop_2:
      if ( !TRUEP(Ui_client_interface_saved_icp_socket_list))
	  goto end_loop_2;
      gensym_pop_store = Nil;
      cons_1 = Ui_client_interface_saved_icp_socket_list;
      if (cons_1) {
	  gensym_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qab_gensym);
	  if (ISVREF(Available_gensym_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_gensym_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_gensym_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_gensym_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Ui_client_interface_saved_icp_socket_list = next_cons;
      frame_spec = gensym_pop_store;
      Current_icp_socket = CAR(frame_spec);
      temp_1 = CDR(frame_spec);
      network_type = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      host = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      port = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      remote_process_initialization_string = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      name_or_names_for_frame = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      class_1 = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      callback_qm = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      callback_data = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      module_information_callback_qm = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      module_information_callback_data = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      progress_callback_qm = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      progress_callback_data = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      dialog_callback_qm = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      dialog_callback_data = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      dialog_list = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      session_position_list = CAR(temp_1);
      temp_1 = CDR(frame_spec);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      icp_object_map = CAR(temp_1);
      reclaim_gensym_list_1(frame_spec);
      ui_client_interface = 
	      g2_initialize_gsi_interface(name_or_names_for_frame,class_1,
	      T,network_type,host,port,remote_process_initialization_string,T);
      restore_icp_object_map_for_registered_item(ui_client_interface,
	      icp_object_map);
      gensymed_symbol = 
	      lookup_global_or_kb_specific_property_value(Qui_client_interface,
	      Class_description_gkbprop);
      if (gensymed_symbol) {
	  sub_class_bit_vector = ISVREF(ISVREF(ui_client_interface,
		  (SI_Long)1L),(SI_Long)19L);
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
	      temp_2 = (SI_Long)0L < gensymed_symbol_1;
	  }
	  else
	      temp_2 = TRUEP(Nil);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2) {
	  position_1 = Nil;
	  ab_loop_list_ = session_position_list;
	  session = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  position_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  session = nth(position_1,sessions);
	  change_slot_value(3,session,Qui_client_session_parent_interface,
		  ui_client_interface);
	  ab_loopvar__2 = slot_value_cons_1(session,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_3;
	end_loop_3:
	  temp_1 = ab_loopvar_;
	  goto end_2;
	  temp_1 = Qnil;
	end_2:;
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_sessions,temp_1);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_callback_qm,callback_qm);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_callback_data,callback_data);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_module_information_callback_qm,
		  module_information_callback_qm);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_module_information_callback_data,
		  module_information_callback_data);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_progress_callback_qm,
		  progress_callback_qm);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_progress_callback_data,
		  progress_callback_data);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_dialog_callback_qm,dialog_callback_qm);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_dialog_callback_data,
		  dialog_callback_data);
	  change_slot_value(3,ui_client_interface,
		  Qui_client_interface_dialog_list,dialog_list);
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  module_info = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qmodule_information);
	  next_loop_4:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_5:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_4;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_4;
		goto next_loop_5;
	      end_loop_4:
		temp_2 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		goto end_loop_5;
	    module_info = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    inform_ui_client_interface_of_module_creation(module_info,
		    ui_client_interface);
	    goto next_loop_4;
	  end_loop_5:;
	  POP_SPECIAL();
      }
      goto next_loop_2;
    end_loop_2:;
    POP_SPECIAL();
    reclaim_gensym_list_1(sessions);
    return VALUES_1(Nil);
}

static Object Qclear_kb_internal;  /* clear-kb-internal */

static Object Qclear_kb;           /* clear-kb */

static Object string_constant_2;   /* "new-kb" */

/* CLEAR-KB */
Object clear_kb varargs_1(int, n)
{
    Object reading_kb_qm, index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object old_kb_specific_property_list_property_name;
    Object do_not_note_permanent_changes_p, in_clear_kb_p, workstation;
    Object ab_loop_list_, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, gensym_window;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame;
    Object frame_serial_number_setf_arg, old, new_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(15);
    Object result;

    x_note_fn_call(134,19);
    INIT_ARGS_nonrelocating();
    SAVE_STACK();
    reading_kb_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    14);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qclear_kb_internal;
      }
      old_kb_specific_property_list_property_name = 
	      Current_kb_specific_property_list_property_name;
      do_not_note_permanent_changes_p = T;
      in_clear_kb_p = T;
      PUSH_SPECIAL_WITH_SYMBOL(In_clear_kb_p,Qin_clear_kb_p,in_clear_kb_p,13);
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		12);
	  workstation = Nil;
	  ab_loop_list_ = Workstations_in_service;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  workstation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !(Servicing_workstation_qm && EQ(Current_workstation,
		  workstation))) {
	      LOCK(For_workstation);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  current_workstation_1 = workstation;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			  11);
		    current_workstation_window = 
			    ISVREF(Current_workstation,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			    10);
		      current_g2_window_for_this_workstation_qm = 
			      ISVREF(Current_workstation,(SI_Long)25L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			      9);
			type_of_current_workstation_window = 
				ISVREF(Current_workstation_window,(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
				8);
			  current_workstation_native_window_qm = 
				  ISVREF(Current_workstation_window,
				  (SI_Long)17L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				  7);
			    temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			    current_workstation_context = CAR(temp_1);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				    6);
			      type_of_current_workstation_context = 
				      ISVREF(Current_workstation_context,
				      (SI_Long)1L);
			      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				      5);
				specific_structure_for_current_workstation_context 
					= 
					ISVREF(Current_workstation_context,
					(SI_Long)2L);
				PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
					4);
				  current_workstation_detail_pane = 
					  detail_pane(Current_workstation_window);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					  3);
				    current_g2_user_mode_qm = 
					    ISVREF(Current_workstation,
					    (SI_Long)19L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					    2);
				      new_g2_classic_ui_p = 
					      get_value_for_current_workstation_new_g2_classic_ui_p();
				      PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					      1);
					servicing_workstation_qm = T;
					PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
						0);
					  unwind_current_workstation_back_to_top_level();
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
	      UNLOCK(For_workstation);
	      CONTINUE_UNWINDING(0);
	  }
	  goto next_loop;
	end_loop:
	  if (Servicing_workstation_qm)
	      unwind_current_workstation_back_to_top_level();
	  clear_all_twng_disconnect_callbacks();
	  inform_ui_client_interfaces_of_clear_kb();
	  unedit_up_to_date_modules();
	  shut_down_g2ds_clients_for_clear_kb();
	  system_reset();
	  run_state_change_hook(Qclear_kb);
	  switch_to_new_empty_kb();
	  workstation = Nil;
	  ab_loop_list_ = Workstations_in_service;
	  gensym_window = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  workstation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensym_window = ISVREF(workstation,(SI_Long)1L);
	  set_window_title(gensym_window,Nil);
	  goto next_loop_1;
	end_loop_1:;
	  clear_inspect_command_history_list();
	  release_kb(old_kb_specific_property_list_property_name,T,Nil,Nil);
	  release_all_kb_write_locks();
	  make_or_clear_complete_kb_name(2,string_constant_2,T);
	  reset_current_frame_serial_number();
	  Use_current_time_for_next_uuid = T;
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop_2:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_3:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_2;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_2;
		goto next_loop_3;
	      end_loop_2:
		temp_2 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		goto end_loop_3;
	    frame = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    frame_serial_number_setf_arg = 
		    increment_current_frame_serial_number();
	    old = ISVREF(frame,(SI_Long)3L);
	    new_1 = frame_serial_number_setf_arg;
	    temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		    !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    ISVREF(frame,(SI_Long)3L) = temp;
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
	  Next_class_bit_number = FIXNUM_ADD1(Last_system_class_bit_number);
	  clear_base_name_from_default_load_pathnames();
	  if ( !TRUEP(reading_kb_qm))
	      restore_ui_client_interfaces();
	  if ( !TRUEP(reading_kb_qm))
	      result = display_credits(0);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant;      /* # */

static Object Qworkspace;          /* workspace */

static Object Qsystem_frame;       /* system-frame */

/* RELEASE-KB */
Object release_kb(kb_specific_property_list_property_name,
	    also_clear_windows_qm,keep_locations_entry_qm,
	    try_to_do_deferred_user_notifications_qm)
    Object kb_specific_property_list_property_name, also_clear_windows_qm;
    Object keep_locations_entry_qm, try_to_do_deferred_user_notifications_qm;
{
    Object releasing_kb_qm, old_kb_specific_property_list_property_name;
    Object gensymed_symbol, workstation, ab_loop_list_, gensym_window, pane;
    Object ab_loop_list__1, image_plane_to_delete_qm, image_plane;
    Object ab_loop_list__2, temp, gensymed_symbol_1, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, a_block, workspace, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, system_frame, temp_2, frame, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(134,20);
    SAVE_STACK();
    releasing_kb_qm = T;
    old_kb_specific_property_list_property_name = 
	    Current_kb_specific_property_list_property_name;
    PUSH_SPECIAL_WITH_SYMBOL(Releasing_kb_qm,Qreleasing_kb_qm,releasing_kb_qm,
	    1);
      gensymed_symbol = Current_kb_specific_property_list_property_name;
      switch_to_kb(kb_specific_property_list_property_name);
      if (PUSH_UNWIND_PROTECT(1)) {
	  if (also_clear_windows_qm) {
	      close_logbooks();
	      workstation = Nil;
	      ab_loop_list_ = Workstations_in_service;
	      gensym_window = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      workstation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensym_window = ISVREF(workstation,(SI_Long)1L);
	      pane = Nil;
	      ab_loop_list__1 = ISVREF(gensym_window,(SI_Long)3L);
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_1;
	      pane = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    next_loop_2:
	      image_plane_to_delete_qm = Nil;
	      image_plane = Nil;
	      ab_loop_list__2 = ISVREF(pane,(SI_Long)5L);
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list__2))
		  goto end_loop_2;
	      image_plane = M_CAR(ab_loop_list__2);
	      ab_loop_list__2 = M_CDR(ab_loop_list__2);
	      image_plane_to_delete_qm = image_plane;
	      goto next_loop_3;
	    end_loop_2:
	      if (image_plane_to_delete_qm) {
		  temp = ISVREF(pane,(SI_Long)5L);
		  if (EQ(CAR(temp),image_plane_to_delete_qm)) {
		      delete_image_plane(image_plane_to_delete_qm);
		      temp_1 = TRUEP(Nil);
		  }
		  else {
		      delete_image_plane(image_plane_to_delete_qm);
		      temp_1 = TRUEP(T);
		  }
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      goto end_1;
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	      if ( !temp_1)
		  goto end_loop_3;
	      goto next_loop_2;
	    end_loop_3:
	      goto next_loop_1;
	    end_loop_1:;
	      goto next_loop;
	    end_loop:;
	  }
	  if (try_to_do_deferred_user_notifications_qm) {
	      gensymed_symbol_1 = 
		      Current_kb_specific_property_list_property_name;
	      switch_to_kb(old_kb_specific_property_list_property_name);
	      if (PUSH_UNWIND_PROTECT(0))
		  try_to_do_deferred_user_notifications();
	      POP_UNWIND_PROTECT(0);
	      switch_to_kb(gensymed_symbol_1);
	      CONTINUE_UNWINDING(0);
	  }
	  note_progress(2,array_constant,FIX((SI_Long)0L));
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  a_block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop_4:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_5:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_4;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_4;
		goto next_loop_5;
	      end_loop_4:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_5;
	    a_block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    permanently_retract_consistency_analysis(a_block);
	    goto next_loop_4;
	  end_loop_5:;
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  workspace = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    ab_loopvar_ = collect_subclasses(Qworkspace);
	  next_loop_6:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_7:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_6;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_6;
		goto next_loop_7;
	      end_loop_6:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_7;
	    workspace = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    ab_loopvar__4 = gensym_cons_1(workspace,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_6;
	  end_loop_7:
	    temp = ab_loopvar__2;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  system_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    ab_loopvar_ = collect_subclasses(Qsystem_frame);
	  next_loop_8:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_9:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_8;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_8;
		goto next_loop_9;
	      end_loop_8:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_9;
	    system_frame = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    ab_loopvar__4 = gensym_cons_1(system_frame,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_8;
	  end_loop_9:
	    temp_2 = ab_loopvar__2;
	    goto end_3;
	    temp_2 = Qnil;
	  end_3:;
	  POP_SPECIAL();
	  delete_frame_list(nconc2(temp,temp_2));
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop_10:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_11:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_10;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_10;
		goto next_loop_11;
	      end_loop_10:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_11;
	    frame = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qui_client_interface,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qui_client_session,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
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
			temp_1 = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    if ( !temp_1) {
		ab_loopvar__4 = gensym_cons_1(frame,Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
	    }
	    goto next_loop_10;
	  end_loop_11:
	    temp = ab_loopvar__2;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	  POP_SPECIAL();
	  delete_frame_list(temp);
	  save_and_delete_ui_client_interfaces();
	  delete_classes_queued_by_delete_frame(Classes_to_delete_when_releasing_kb);
	  Classes_to_delete_when_releasing_kb = Nil;
	  reclaim_kb_specific_properties(keep_locations_entry_qm);
	  reclaim_values_of_kb_specific_variables(Current_system_name);
	  SAVE_VALUES(note_progress(0));
      }
      POP_UNWIND_PROTECT(1);
      switch_to_kb(gensymed_symbol);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* DELETE-FRAME-LIST */
Object delete_frame_list(frames_to_delete)
    Object frames_to_delete;
{
    Object ref, frame, ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(134,21);
    ref = copy_frame_serial_number(Current_frame_serial_number);
    frame = Nil;
    ab_loop_list_ = frames_to_delete;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(frame,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(ref))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(ref,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(ref);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(ref),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(frame);
    goto next_loop;
  end_loop:;
    reclaim_frame_serial_number(ref);
    reclaim_gensym_list_1(frames_to_delete);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ignore_kb_state_changes_p, Qignore_kb_state_changes_p);

static Object Qoriginal_kb_state_plist;  /* original-kb-state-plist */

static Object Qworkspace_frame;    /* workspace-frame */

static Object Qitem_position;      /* item-position */

static Object Qicon_position;      /* icon-position */

static Object Qicon_orientation;   /* icon-orientation */

static Object Qreflection_and_rotation;  /* reflection-and-rotation */

static Object Qicon_color;         /* icon-color */

static Object Qline_color;         /* line-color */

static Object Qicon_color_pattern;  /* icon-color-pattern */

static Object Qworkspace_color_pattern;  /* workspace-color-pattern */

static Object Qtext_box_color_pattern;  /* text-box-color-pattern */

static Object Qconnection_color_pattern;  /* connection-color-pattern */

static Object Qtext_color;         /* text-color */

static Object Qborder_color;       /* border-color */

static Object Qbackground_color;   /* background-color */

static Object Qforeground_color;   /* foreground-color */

static Object Qstripe_color;       /* stripe-color */

static Object Qtext;               /* text */

static Object Qg2_array_length;    /* g2-array-length */

static Object Qtext_box_font;      /* text-box-font */

/* NOTE-KB-STATE-CHANGE */
Object note_kb_state_change(frame,kb_state_variable)
    Object frame, kb_state_variable;
{
    Object original_kb_state_plist, indicator, ab_loop_list_, ab_loop_it_;
    Object gensymed_symbol, temp_1, temp_2, temp_3, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(134,22);
    original_kb_state_plist = get_lookup_slot_value_given_default(frame,
	    Qoriginal_kb_state_plist,Nil);
    temp = TRUEP(Ignore_kb_state_changes_p);
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)262144L);
    if (temp);
    else {
	indicator = Nil;
	ab_loop_list_ = original_kb_state_plist;
	ab_loop_it_ = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	indicator = M_CAR(ab_loop_list_);
	ab_loop_it_ = EQ(indicator,kb_state_variable) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
    }
    if ( !temp) {
	if ( !TRUEP(original_kb_state_plist))
	    note_as_frame_with_kb_state_changes(frame);
	if (EQ(kb_state_variable,Qworkspace_frame)) {
	    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_1 = gensymed_symbol;
	    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_2 = gensymed_symbol;
	    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    temp_3 = gensymed_symbol;
	    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    temp_3 = slot_value_list_4(temp_1,temp_2,temp_3,gensymed_symbol);
	}
	else if (EQ(kb_state_variable,Qitem_position) || 
		EQ(kb_state_variable,Qicon_position)) {
	    temp_3 = item_x_position(frame);
	    temp_3 = slot_value_cons_1(temp_3,item_y_position(frame));
	}
	else if (EQ(kb_state_variable,Qicon_orientation))
	    temp_3 = getf(ISVREF(frame,(SI_Long)17L),
		    Qreflection_and_rotation,_);
	else if (EQ(kb_state_variable,Qicon_color))
	    temp_3 = getf(ISVREF(frame,(SI_Long)17L),Qline_color,_);
	else if (EQ(kb_state_variable,Qicon_color_pattern))
	    temp_3 = get_icon_color_pattern(1,frame);
	else if (EQ(kb_state_variable,Qworkspace_color_pattern))
	    temp_3 = get_workspace_color_pattern(1,frame);
	else if (EQ(kb_state_variable,Qtext_box_color_pattern))
	    temp_3 = get_text_box_color_pattern(1,frame);
	else if (EQ(kb_state_variable,Qconnection_color_pattern))
	    temp_3 = get_connection_color_pattern(1,frame);
	else if (EQ(kb_state_variable,Qtext_color))
	    temp_3 = getf(ISVREF(frame,(SI_Long)18L),Qline_color,_);
	else if (EQ(kb_state_variable,Qborder_color))
	    temp_3 = getf(ISVREF(frame,(SI_Long)18L),Qborder_color,_);
	else if (EQ(kb_state_variable,Qbackground_color)) {
	    gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    temp_3 = temp ? ISVREF(frame,(SI_Long)21L) : getf(ISVREF(frame,
		    (SI_Long)18L),Qbackground_color,_);
	}
	else if (EQ(kb_state_variable,Qforeground_color))
	    temp_3 = ISVREF(frame,(SI_Long)22L);
	else if (EQ(kb_state_variable,Qstripe_color))
	    temp_3 = copy_tree_using_slot_value_conses_1(ISVREF(frame,
		    (SI_Long)20L));
	else if (EQ(kb_state_variable,Qtext)) {
	    temp_3 = ISVREF(frame,(SI_Long)16L);
	    temp_3 = copy_text(CDR(temp_3));
	}
	else if (EQ(kb_state_variable,Qg2_array_length))
	    temp_3 = g2_array_length_function(frame);
	else if (EQ(kb_state_variable,Qtext_box_font))
	    temp_3 = 
		    make_original_value_for_text_box_font_kb_state_change(frame);
	else
	    temp_3 = Qnil;
	return set_non_savable_lookup_slot_value(frame,
		Qoriginal_kb_state_plist,
		slot_value_cons_1(kb_state_variable,
		slot_value_cons_1(temp_3,original_kb_state_plist)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext_of_changed_slots;  /* text-of-changed-slots */

/* NOTE-KB-STATE-CHANGE-TO-SLOT-BY-SAVING-TEXT */
Object note_kb_state_change_to_slot_by_saving_text(frame,slot_description)
    Object frame, slot_description;
{
    Object plist_entry, temp, slot_denotation, name, value, ab_loop_list_;
    Object ab_loop_it_, second_new_value;
    char temp_1;

    x_note_fn_call(134,23);
    if ( !(Ignore_kb_state_changes_p || (SI_Long)0L != (IFIX(ISVREF(frame,
	    (SI_Long)5L)) & (SI_Long)262144L))) {
	if ( !TRUEP(get_lookup_slot_value_given_default(frame,
		Qoriginal_kb_state_plist,Nil)))
	    note_as_frame_with_kb_state_changes(frame);
	plist_entry = get_lookup_slot_value_given_default(frame,
		Qoriginal_kb_state_plist,Nil);
      next_loop:
	if ( !TRUEP(plist_entry))
	    goto end_loop;
	if (EQ(Qtext_of_changed_slots,FIRST(plist_entry)))
	    goto end_1;
	plist_entry = CDDR(plist_entry);
	goto next_loop;
      end_loop:
	plist_entry = Qnil;
      end_1:;
	if (plist_entry);
	else {
	    temp = slot_value_list_2(Qtext_of_changed_slots,Nil);
	    plist_entry = set_non_savable_lookup_slot_value(frame,
		    Qoriginal_kb_state_plist,nconc2(temp,
		    get_lookup_slot_value_given_default(frame,
		    Qoriginal_kb_state_plist,Nil)));
	}
	slot_denotation = 
		denote_slot_using_slot_value_conses(slot_description,
		ISVREF(frame,(SI_Long)1L));
	if (ATOM(slot_denotation))
	    temp_1 = TRUEP(getf(SECOND(plist_entry),slot_denotation,_));
	else {
	    name = Nil;
	    value = Nil;
	    ab_loop_list_ = SECOND(plist_entry);
	    ab_loop_it_ = Nil;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	  next_loop_1:
	    name = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    value = CAR(temp);
	    ab_loop_it_ = EQUAL(name,slot_denotation) ? T : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	}
	if ( !temp_1) {
	    temp = assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L));
	    if (memq_function(Qtext,CDDR(temp))) {
		temp = get_slot_description_value(frame,slot_description);
		temp = copy_text(CDR(temp));
	    }
	    else
		temp = 
			make_text_representation_for_slot_description_value(frame,
			slot_description);
	    second_new_value = slot_value_cons_1(slot_denotation,
		    slot_value_cons_1(temp,SECOND(plist_entry)));
	    return VALUES_1(M_SECOND(plist_entry) = second_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* NOTE-PERMANENT-CHANGE */
Object note_permanent_change(frame,slot_description)
    Object frame, slot_description;
{
    Object sub_class_bit_vector, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(134,24);
    if ( !TRUEP(Do_not_note_permanent_changes_p)) {
	if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L) &&  
		!((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)4L)) & (SI_Long)1L) && (SI_Long)0L != 
		(IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)16L)) {
	    temp = TRUEP(superior_frame(frame));
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qsystem_frame,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  
		!TRUEP(memq_function(reason_to_exclude_slot_description_for_compute_class_description_node_attributes(slot_description),
		list_constant)) : TRUEP(Nil))
	    note_permanent_changes(frame,slot_description);
    }
    return VALUES_1(Nil);
}

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

/* NOTE-PERMANENT-CHANGE-TO-SLOT-GROUP-FOR-BLOCK */
Object note_permanent_change_to_slot_group_for_block(frame)
    Object frame;
{
    Object sub_class_bit_vector, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(134,25);
    if ( !TRUEP(Do_not_note_permanent_changes_p)) {
	if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L) &&  
		!((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
		(SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(frame,
		(SI_Long)4L)) & (SI_Long)1L) && (SI_Long)0L != 
		(IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)16L)) {
	    temp = TRUEP(superior_frame(frame));
	    if (temp);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qsystem_frame,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return note_permanent_changes(frame,
		    get_slot_description_of_class_description_function(Qslot_group_for_block_qm,
		    ISVREF(frame,(SI_Long)1L),Nil));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-PERMANENT-CHANGE-TO-COMPONENT */
Object note_permanent_change_to_component(frame,slot_description,
	    slot_component_name_qm,slot_component_indicator_qm)
    Object frame, slot_description, slot_component_name_qm;
    Object slot_component_indicator_qm;
{
    x_note_fn_call(134,26);
    note_permanent_change(frame,slot_description);
    return VALUES_1(Nil);
}

static Object Qattributes_permamently_changed;  /* attributes-permamently-changed */

/* NOTE-PERMANENT-CHANGES */
Object note_permanent_changes(frame,slot_description_or_symbol_or_state_plist)
    Object frame, slot_description_or_symbol_or_state_plist;
{
    Object attributes_permamently_changed, name, value, ab_loop_list_;
    Object denotations, ab_loop_list__1, temp, slot_denotation;
    Object ab_loop_list__2;

    x_note_fn_call(134,27);
    attributes_permamently_changed = 
	    get_lookup_slot_value_given_default(frame,
	    Qattributes_permamently_changed,Nil);
    if (EQ(attributes_permamently_changed,T));
    else if (SYMBOLP(slot_description_or_symbol_or_state_plist))
	set_non_savable_lookup_slot_value(frame,
		Qattributes_permamently_changed,T);
    else if (CONSP(slot_description_or_symbol_or_state_plist)) {
	name = Nil;
	value = Nil;
	ab_loop_list_ = slot_description_or_symbol_or_state_plist;
	denotations = Nil;
	ab_loop_list__1 = 
		denotations_of_slots_given_state_change_name(name,frame);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop;
	denotations = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	slot_denotation = Nil;
	ab_loop_list__2 = denotations;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_1;
	slot_denotation = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if ( !TRUEP(memq_function(slot_denotation,
		attributes_permamently_changed)))
	    attributes_permamently_changed = 
		    slot_value_cons_1(slot_denotation,
		    attributes_permamently_changed);
	goto next_loop_1;
      end_loop_1:;
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:;
	set_non_savable_lookup_slot_value(frame,
		Qattributes_permamently_changed,
		attributes_permamently_changed);
    }
    else {
	slot_denotation = 
		denote_slot_using_slot_value_conses(slot_description_or_symbol_or_state_plist,
		ISVREF(frame,(SI_Long)1L));
	if ( !(ATOM(slot_denotation) ? TRUEP(memq_function(slot_denotation,
		attributes_permamently_changed)) : 
		TRUEP(ab_member_equal(slot_denotation,
		attributes_permamently_changed)))) {
	    attributes_permamently_changed = 
		    slot_value_cons_1(slot_denotation,
		    attributes_permamently_changed);
	    set_non_savable_lookup_slot_value(frame,
		    Qattributes_permamently_changed,
		    attributes_permamently_changed);
	}
    }
    return VALUES_1(Nil);
}

/* NOTE-SAVING-FRAME */
Object note_saving_frame(frame)
    Object frame;
{
    Object attributes_permamently_changed;
    SI_Long svref_new_value;

    x_note_fn_call(134,28);
    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) &  ~(SI_Long)4L;
    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
    svref_new_value = IFIX(ISVREF(frame,(SI_Long)5L)) | (SI_Long)16L;
    ISVREF(frame,(SI_Long)5L) = FIX(svref_new_value);
    attributes_permamently_changed = 
	    get_lookup_slot_value_given_default(frame,
	    Qattributes_permamently_changed,Nil);
    if (attributes_permamently_changed) {
	reclaim_slot_value(attributes_permamently_changed);
	return set_non_savable_lookup_slot_value(frame,
		Qattributes_permamently_changed,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SLOT-VALUE-IS-PERMANENT-P */
Object slot_value_is_permanent_p(frame,slot_description)
    Object frame, slot_description;
{
    Object sub_class_bit_vector, temp_1, slot_denotation, name, value;
    Object ab_loop_list_, name1, value1, ab_loop_list__1, ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(134,29);
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
    temp_1 =  !temp ? T : Nil;
    if (temp_1);
    else {
	slot_denotation = 
		denote_slot_using_slot_value_conses(slot_description,
		ISVREF(frame,(SI_Long)1L));
	name = Nil;
	value = Nil;
	ab_loop_list_ = get_lookup_slot_value_given_default(frame,
		Qoriginal_kb_state_plist,Nil);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	name = CAR(ab_loop_list_);
	temp_1 = CDR(ab_loop_list_);
	value = CAR(temp_1);
	if (EQ(Qtext_of_changed_slots,name)) {
	    if (ATOM(slot_denotation))
		temp = TRUEP(getf(value,slot_denotation,_));
	    else {
		name1 = Nil;
		value1 = Nil;
		ab_loop_list__1 = value;
		ab_loop_it_ = Nil;
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
	      next_loop_1:
		name1 = CAR(ab_loop_list__1);
		temp_1 = CDR(ab_loop_list__1);
		value1 = CAR(temp_1);
		ab_loop_it_ = EQUAL(name1,slot_denotation) ? T : Nil;
		if (ab_loop_it_) {
		    temp = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		ab_loop_list__1 = CDDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		goto next_loop_1;
	      end_loop_1:
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else
	    temp = TRUEP(memq_function(slot_denotation,
		    denotations_of_slots_given_state_change_name(name,frame)));
	if (temp) {
	    temp_1 = Nil;
	    goto end_2;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (CONSP(slot_denotation))
	    reclaim_slot_value(slot_denotation);
	temp_1 = T;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
    }
    return VALUES_1(temp_1);
}

static Object list_constant_1;     /* # */

static Object Qget_text_box_color_pattern;  /* get-text-box-color-pattern */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

/* DENOTATIONS-OF-SLOTS-GIVEN-STATE-CHANGE-NAME */
Object denotations_of_slots_given_state_change_name(name,frame)
    Object name, frame;
{
    Object temp, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(134,30);
    if (EQ(name,Qicon_orientation) || EQ(name,Qicon_color))
	temp = list_constant_1;
    else if (EQ(name,Qicon_color_pattern) || EQ(name,
	    Qworkspace_color_pattern) || EQ(name,Qtext_box_color_pattern) 
	    || EQ(name,Qget_text_box_color_pattern))
	temp = list_constant_1;
    else if (EQ(name,Qtext_color) || EQ(name,Qborder_color))
	temp = list_constant_2;
    else if (EQ(name,Qbackground_color)) {
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	temp = temp_1 ? list_constant_3 : list_constant_2;
    }
    else if (EQ(name,Qforeground_color))
	temp = list_constant_4;
    else if (EQ(name,Qtext))
	temp = list_constant_5;
    else if (EQ(name,Qtext_box_font))
	temp = list_constant_6;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object Qkb_state_changes_previous_cons_qm;  /* kb-state-changes-previous-cons? */

/* NOTE-AS-FRAME-WITH-KB-STATE-CHANGES */
Object note_as_frame_with_kb_state_changes(frame)
    Object frame;
{
    Object first_arg;

    x_note_fn_call(134,31);
    if ( !TRUEP(get_lookup_slot_value_given_default(frame,
	    Qkb_state_changes_previous_cons_qm,Nil))) {
	first_arg = Kb_state_changes;
	M_FIRST(first_arg) = frame;
	Kb_state_changes = kb_property_cons_1(Nil,Kb_state_changes);
	set_non_savable_lookup_slot_value(frame,
		Qkb_state_changes_previous_cons_qm,Kb_state_changes);
    }
    return VALUES_1(Nil);
}

/* REMOVE-AS-FRAME-WITH-KB-STATE-CHANGES */
Object remove_as_frame_with_kb_state_changes(frame)
    Object frame;
{
    Object previous_cons_qm, this_cons, next_cons_qm, next_frame_qm;

    x_note_fn_call(134,32);
    previous_cons_qm = get_lookup_slot_value_given_default(frame,
	    Qkb_state_changes_previous_cons_qm,Nil);
    if (previous_cons_qm) {
	this_cons = CDR(previous_cons_qm);
	next_cons_qm = CDR(this_cons);
	next_frame_qm = FIRST(next_cons_qm);
	set_non_savable_lookup_slot_value(frame,
		Qkb_state_changes_previous_cons_qm,Nil);
	M_CDR(this_cons) = Nil;
	reclaim_kb_property_cons_1(this_cons);
	M_CDR(previous_cons_qm) = next_cons_qm;
	if (next_frame_qm)
	    set_non_savable_lookup_slot_value(next_frame_qm,
		    Qkb_state_changes_previous_cons_qm,previous_cons_qm);
    }
    return VALUES_1(Nil);
}

/* UNDO-KB-STATE-CHANGES */
Object undo_kb_state_changes()
{
    Object list_1, cdr_arg, frame, ab_loop_list_;

    x_note_fn_call(134,33);
    if (CDR(Kb_state_changes)) {
	list_1 = CDR(Kb_state_changes);
	cdr_arg = Kb_state_changes;
	M_CDR(cdr_arg) = Nil;
	frame = Nil;
	ab_loop_list_ = list_1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	set_non_savable_lookup_slot_value(frame,
		Qkb_state_changes_previous_cons_qm,Nil);
	undo_kb_state_changes_for_frame(frame);
	goto next_loop;
      end_loop:;
	return reclaim_kb_property_list_1(list_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qreflected;          /* reflected */

static Object Qnormal;             /* normal */

static Object Qreflected_clockwise_90;  /* reflected-clockwise-90 */

static Object Qclockwise_90;       /* clockwise-90 */

static Object Qreflected_clockwise_180;  /* reflected-clockwise-180 */

static Object Qclockwise_180;      /* clockwise-180 */

static Object Qreflected_clockwise_270;  /* reflected-clockwise-270 */

static Object Qclockwise_270;      /* clockwise-270 */

static Object list_constant_7;     /* # */

static Object Kno_change;          /* :no-change */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object list_constant_8;     /* # */

/* UNDO-KB-STATE-CHANGES-FOR-FRAME */
Object undo_kb_state_changes_for_frame(frame)
    Object frame;
{
    Object plist, kb_state_variable, original_value, temp, gensymed_symbol;
    Object subblocks, extreme_left_edge, extreme_top_edge, extreme_right_edge;
    Object extreme_bottom_edge, workspace_margin, decff_1_arg, incff_1_arg;
    Object temp_1, temp_2, temp_3, new_x, new_y, reflection_and_rotation;
    Object sub_class_bit_vector, connection, workspace, plist_1;
    Object slot_denotation, text_or_text_string, slot_description_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, delta_x, delta_y;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3;
    char temp_4;
    Object result;

    x_note_fn_call(134,34);
    plist = get_lookup_slot_value_given_default(frame,
	    Qoriginal_kb_state_plist,Nil);
    kb_state_variable = Nil;
    original_value = Nil;
  next_loop:
    if ( !TRUEP(plist))
	goto end_loop;
    kb_state_variable = CAR(plist);
    temp = CDR(plist);
    original_value = CAR(temp);
    if (EQ(kb_state_variable,Qworkspace_frame)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(frame,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
		(SI_Long)2L),subblocks))) {
	    result = determine_extreme_edges_of_workspace_subblocks(frame);
	    MVS_4(result,extreme_left_edge,extreme_top_edge,
		    extreme_right_edge,extreme_bottom_edge);
	    workspace_margin = ISVREF(frame,(SI_Long)17L);
	    decff_1_arg = workspace_margin;
	    extreme_left_edge = FIXNUM_MINUS(extreme_left_edge,decff_1_arg);
	    decff_1_arg = workspace_margin;
	    extreme_top_edge = FIXNUM_MINUS(extreme_top_edge,decff_1_arg);
	    incff_1_arg = workspace_margin;
	    extreme_right_edge = FIXNUM_ADD(extreme_right_edge,incff_1_arg);
	    incff_1_arg = workspace_margin;
	    extreme_bottom_edge = FIXNUM_ADD(extreme_bottom_edge,incff_1_arg);
	    temp = FIRST(original_value);
	    temp_1 = SECOND(original_value);
	    temp_2 = THIRD(original_value);
	    temp_3 = FOURTH(original_value);
	    new_change_workspace_edges(frame,FIXNUM_MIN(extreme_left_edge,
		    temp),FIXNUM_MIN(extreme_top_edge,temp_1),
		    FIXNUM_MAX(extreme_right_edge,temp_2),
		    FIXNUM_MAX(extreme_bottom_edge,temp_3));
	}
	else
	    new_change_workspace_edges(frame,FIRST(original_value),
		    SECOND(original_value),THIRD(original_value),
		    FOURTH(original_value));
    }
    else if (EQ(kb_state_variable,Qitem_position)) {
	new_x = CAR(original_value);
	new_y = CDR(original_value);
	gensymed_symbol_1 = FIXNUMP(new_x) ? IFIX(new_x) : 
		IFIX(l_round(new_x,_));
	gensymed_symbol_2 = IFIX(item_x_position(frame));
	delta_x = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_1 = FIXNUMP(new_y) ? IFIX(new_y) : 
		IFIX(l_round(new_y,_));
	gensymed_symbol_2 = IFIX(item_y_position(frame));
	delta_y = gensymed_symbol_1 - gensymed_symbol_2;
	move_item_by(4,frame,FIX(delta_x),FIX(delta_y),Nil);
	if (G2_has_v5_mode_windows_p &&  
		!TRUEP(Ws_protocol_handle_moves_from_edge_change_p))
	    send_ws_representations_item_moved(frame,FIX(delta_x),
		    FIX(delta_y));
    }
    else if (EQ(kb_state_variable,Qicon_position))
	move_icon(frame,CAR(original_value),CDR(original_value));
    else if (EQ(kb_state_variable,Qicon_orientation)) {
	temp = 
		invert_reflection_and_rotation(getfq_function_no_default(ISVREF(frame,
		(SI_Long)17L),Qreflection_and_rotation));
	reflection_and_rotation = multiply_reflection_and_rotation(temp,
		original_value);
	if (EQ(reflection_and_rotation,Qreflected) || 
		EQ(reflection_and_rotation,Qnormal) || 
		EQ(reflection_and_rotation,Qnil))
	    temp = FIX((SI_Long)0L);
	else if (EQ(reflection_and_rotation,Qreflected_clockwise_90) || 
		EQ(reflection_and_rotation,Qclockwise_90))
	    temp = FIX((SI_Long)90L);
	else if (EQ(reflection_and_rotation,Qreflected_clockwise_180) || 
		EQ(reflection_and_rotation,Qclockwise_180))
	    temp = FIX((SI_Long)180L);
	else if (EQ(reflection_and_rotation,Qreflected_clockwise_270) || 
		EQ(reflection_and_rotation,Qclockwise_270))
	    temp = FIX((SI_Long)270L);
	else
	    temp = Qnil;
	rotate_and_reflect_icon(frame,temp,
		memq_function(reflection_and_rotation,list_constant_7),Nil,
		Nil,Nil);
    }
    else if (EQ(kb_state_variable,Qicon_color))
	change_color_of_icon(frame,Nil,original_value);
    else if (EQ(kb_state_variable,Qicon_color_pattern))
	change_color_pattern_of_icon(frame,Nil,original_value);
    else if (EQ(kb_state_variable,Qworkspace_color_pattern)) {
	temp = assq_function(Qbackground_color,original_value);
	temp_1 = assq_function(Qforeground_color,original_value);
	change_color_of_workspace(frame,Nil,CDR(temp),CDR(temp_1));
    }
    else if (EQ(kb_state_variable,Qtext_box_color_pattern)) {
	temp = assq_function(Qbackground_color,original_value);
	temp_1 = assq_function(Qborder_color,original_value);
	temp_2 = assq_function(Qtext_color,original_value);
	change_color_of_text_box(5,frame,Nil,CDR(temp),CDR(temp_1),
		CDR(temp_2));
    }
    else if (EQ(kb_state_variable,Qbackground_color)) {
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    temp_4 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_4 = TRUEP(Nil);
	if (temp_4)
	    change_color_of_workspace(frame,Nil,original_value,Kno_change);
	else
	    change_color_of_text_box(5,frame,Nil,original_value,Kno_change,
		    Kno_change);
    }
    else if (EQ(kb_state_variable,Qborder_color))
	change_color_of_text_box(5,frame,Nil,Kno_change,original_value,
		Kno_change);
    else if (EQ(kb_state_variable,Qforeground_color))
	change_color_of_workspace(frame,Nil,Kno_change,original_value);
    else if (EQ(kb_state_variable,Qtext_color))
	change_color_of_text_box(5,frame,Nil,Kno_change,Kno_change,
		original_value);
    else if (EQ(kb_state_variable,Qconnection_color_pattern))
	change_color_pattern_of_connection(frame,Nil,original_value);
    else if (EQ(kb_state_variable,Qstripe_color)) {
	connection = ISVREF(frame,(SI_Long)21L);
	gensymed_symbol = ACCESS_ONCE(ISVREF(ISVREF(connection,
		(SI_Long)2L),(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	workspace = gensymed_symbol;
	update_connection_images(T,workspace,connection);
	change_slot_value(3,frame,Qcross_section_pattern,original_value);
	M_CADR(plist) = Nil;
	update_connection_images(Nil,workspace,connection);
    }
    else if (EQ(kb_state_variable,Qtext_of_changed_slots)) {
	plist_1 = original_value;
	slot_denotation = Nil;
	text_or_text_string = Nil;
	slot_description_qm = Nil;
      next_loop_1:
	if ( !TRUEP(plist_1))
	    goto end_loop_1;
	slot_denotation = CAR(plist_1);
	temp = CDR(plist_1);
	text_or_text_string = CAR(temp);
	slot_description_qm = 
		get_slot_description_of_class_description_function(CONSP(slot_denotation) 
		? M_CAR(M_CDR(M_CDR(slot_denotation))) : slot_denotation,
		ISVREF(frame,(SI_Long)1L),CONSP(slot_denotation) ? 
		M_CAR(M_CDR(slot_denotation)) : Nil);
	if (slot_description_qm) {
	    temp = text_string_p(text_or_text_string) ? 
		    convert_text_string_to_text(text_or_text_string) : 
		    text_or_text_string;
	    parse_text_for_slot(4,temp,frame,
		    get_slot_description_of_class_description_function(CONSP(slot_denotation) 
		    ? M_CAR(M_CDR(M_CDR(slot_denotation))) : 
		    slot_denotation,ISVREF(frame,(SI_Long)1L),
		    CONSP(slot_denotation) ? M_CAR(M_CDR(slot_denotation)) 
		    : Nil),Nil);
	    M_CADR(plist_1) = Nil;
	}
	plist_1 = CDDR(plist_1);
	goto next_loop_1;
      end_loop_1:;
    }
    else if (EQ(kb_state_variable,Qtext)) {
	temp = ISVREF(frame,(SI_Long)16L);
	change_slot_value(3,frame,Qbox_translation_and_text,
		slot_value_cons_1(CAR(temp),original_value));
	M_CADR(plist) = Nil;
    }
    else if (EQ(kb_state_variable,Qg2_array_length))
	change_slot_value(3,frame,Qg2_array_length,original_value);
    else if (EQ(kb_state_variable,Qtext_box_font))
	restore_original_value_for_text_box_font_kb_state_change(frame,
		original_value);
    if (G2_has_v5_mode_windows_p) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	    temp_4 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_4 =  !temp_4;
    }
    else
	temp_4 = TRUEP(Nil);
    if (temp_4 ? TRUEP(memq_function(kb_state_variable,list_constant_8)) : 
	    TRUEP(Nil))
	send_ws_representations_item_color_pattern_change(frame,Nil,
		get_color_pattern_of_item(3,frame,Nil,T));
    plist = CDDR(plist);
    goto next_loop;
  end_loop:
    reclaim_slot_value(get_lookup_slot_value_given_default(frame,
	    Qoriginal_kb_state_plist,Nil));
    set_non_savable_lookup_slot_value(frame,Qoriginal_kb_state_plist,Nil);
    return VALUES_1(Qnil);
}

/* REMOVE-KB-STATE-VARIABLE-RECORD */
Object remove_kb_state_variable_record(frame,kb_state_variable)
    Object frame, kb_state_variable;
{
    Object l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(134,35);
    l_trailer_qm = Nil;
    l = get_lookup_slot_value_given_default(frame,Qoriginal_kb_state_plist,
	    Nil);
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (EQ(CAR(l),kb_state_variable)) {
	if (l_trailer_qm) {
	    cdr_new_value = CDDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	}
	else
	    set_non_savable_lookup_slot_value(frame,
		    Qoriginal_kb_state_plist,CDDR(l));
	M_CDDR(l) = Nil;
	reclaim_slot_value(l);
	goto end_1;
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop;
  end_loop:
  end_1:;
    if ( !TRUEP(get_lookup_slot_value_given_default(frame,
	    Qoriginal_kb_state_plist,Nil)))
	return remove_as_frame_with_kb_state_changes(frame);
    else
	return VALUES_1(Nil);
}

/* REMOVE-KB-STATE-CHANGES */
Object remove_kb_state_changes(frame)
    Object frame;
{
    x_note_fn_call(134,36);
    reclaim_slot_value(get_lookup_slot_value_given_default(frame,
	    Qoriginal_kb_state_plist,Nil));
    return set_non_savable_lookup_slot_value(frame,
	    Qoriginal_kb_state_plist,Nil);
}

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* INITIALIZE-DEFAULT-G2-INIT-PATHNAME */
Object initialize_default_g2_init_pathname()
{
    x_note_fn_call(134,37);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_1,array_constant_2,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2_init_pathname, Qdefault_g2_init_pathname);

static Object list_constant_9;     /* # */

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-INIT-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2_init_command_line()
{
    x_note_fn_call(134,38);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant_9,array_constant_3,array_constant_4,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_init_command_line, Qpathname_for_disabling_g2_init_command_line);

static Object array_constant_5;    /* # */

/* GET-OR-USE-G2-INIT-PATHNAME */
Object get_or_use_g2_init_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(134,39);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2_init_pathname,
	    Pathname_for_disabling_g2_init_command_line,array_constant_2,
	    array_constant_5,array_constant_2,provide_desired_namestring_p);
}

DEFINE_VARIABLE_WITH_SYMBOL(Command_line_qm, Qcommand_line_qm);

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

static Object Qinit_file_command_line;  /* init-file-command-line */

static Object list_constant_10;    /* # */

static Object Qinit_file_command;  /* init-file-command */

static Object string_constant_3;   /* "Executing the command line: ~a" */

static Object array_constant_8;    /* # */

static Object Qrequested;          /* requested */

static Object Qstart_g2;           /* start-g2 */

static Object string_constant_4;   /* "Cannot execute `Start G2' in the G2 Init file (\"~a\") ~
				    *                                     because G2 has already been started."
				    */

static Object string_constant_5;   /* "Error in G2 Init file (\"~a\") while executing the ~
				    *                             command line: ~a~
				    *                             ~%~a~%Aborting execution of the G2 Init file."
				    */

static Object Qautostart;          /* autostart */

static Object Qdo_not_autostart;   /* do-not-autostart */

static Object Qsystem_table;       /* system-table */

static Object string_constant_6;   /* "Ignoring commands following the \"Start G2\" command ~
				    *                            in the G2 Init file."
				    */

/* DO-G2-INIT-FILE */
Object do_g2_init_file()
{
    Object init_file_pathname_qm;
    volatile Object init_file_truename;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object init_file_stream_qm;
    Object doing_g2_init_file_p, start_on_load_p, start_happened_p;
    Object error_happened_p, init_file_command_qm;
    Object frame_serial_number_of_init_file_command_qm, command_line_qm, temp;
    Object temp_1, successp, reason_for_failure_qm, command_translation, frame;
    Object sub_vector_qm, function_qm, gensymed_symbol, gensymed_symbol_1;
    Object next_line_qm, residue_qm;
    SI_Long method_index, i, ab_loop_bind_;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(134,40);
    SAVE_STACK();
    force_process_drawing();
    init_file_pathname_qm = get_or_use_g2_init_pathname(0);
    if (init_file_pathname_qm) {
	init_file_truename = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    init_file_truename = gensym_namestring(1,init_file_pathname_qm);
	    pathname_used_p = Qunbound_in_protected_let;
	    namestring_1 = Qunbound_in_protected_let;
	    init_file_stream_qm = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		pathname_used_p = SIMPLE_VECTOR_P(init_file_truename) ? 
			(EQ(ISVREF(init_file_truename,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? T : Nil) : Qnil;
		namestring_1 = SIMPLE_VECTOR_P(init_file_truename) && 
			EQ(ISVREF(init_file_truename,(SI_Long)0L),
			Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
			? gensym_namestring(1,init_file_truename) : 
			init_file_truename;
		init_file_stream_qm = g2_stream_open_for_input(namestring_1);
		doing_g2_init_file_p = T;
		start_on_load_p = get_command_line_flag_argument(1,
			array_constant_6);
		if (start_on_load_p);
		else
		    start_on_load_p = 
			    get_gensym_environment_variable(array_constant_7);
		start_happened_p = Nil;
		error_happened_p = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Doing_g2_init_file_p,Qdoing_g2_init_file_p,doing_g2_init_file_p,
			1);
		  Autostart_after_doing_init_file_qm = Nil;
		  if (init_file_stream_qm) {
		      init_file_command_qm = Nil;
		      frame_serial_number_of_init_file_command_qm = Nil;
		      command_line_qm = 
			      g2_stream_read_line(init_file_stream_qm);
		      PUSH_SPECIAL_WITH_SYMBOL(Command_line_qm,Qcommand_line_qm,command_line_qm,
			      0);
		      next_loop:
			if ( !TRUEP(Command_line_qm))
			    goto end_loop;
			temp = import_text_string(2,Command_line_qm,
				Qinit_file_command_line);
			reclaim_text_string(Command_line_qm);
			Command_line_qm = temp;
			temp = text_string_trim(list_constant_10,
				Command_line_qm);
			reclaim_text_string(Command_line_qm);
			Command_line_qm = temp;
			if (IFIX(text_string_length(Command_line_qm)) == 
				(SI_Long)0L || 
				UBYTE_16_ISAREF_1(Command_line_qm,
				(SI_Long)0L) == (SI_Long)59L)
			    reclaim_text_string(Command_line_qm);
			else {
			    if ( !TRUEP(init_file_command_qm)) {
				init_file_command_qm = 
					make_command_frame(1,
					Qinit_file_command);
				frame_serial_number_of_init_file_command_qm 
					= 
					copy_frame_serial_number(ISVREF(init_file_command_qm,
					(SI_Long)3L));
			    }
			    notify_user(2,string_constant_3,Command_line_qm);
			    if (string_equalw(Command_line_qm,
				    array_constant_8))
				completely_shut_down_g2(1,Qrequested);
			    else {
				temp_1 = 
					convert_text_string_to_text(copy_text_string(Command_line_qm));
				temp = init_file_command_qm;
				result = parse_text_for_slot(8,temp_1,temp,
					get_slot_description_of_class_description_function(Qbox_translation_and_text,
					ISVREF(init_file_command_qm,
					(SI_Long)1L),Nil),Nil,Nil,Nil,Nil,T);
				MVS_2(result,successp,reason_for_failure_qm);
				if (successp) {
				    reclaim_text_string(Command_line_qm);
				    temp = ISVREF(init_file_command_qm,
					    (SI_Long)16L);
				    command_translation = CAR(temp);
				    if (EQ(command_translation,Qstart_g2)) {
					if (System_is_running || 
						System_has_paused)
					    notify_user(2,
						    string_constant_4,
						    init_file_truename);
					else {
					    start_happened_p = T;
					    system_start();
					    goto end_loop;
					}
				    }
				    else {
					method_index = (SI_Long)27L;
					frame = init_file_command_qm;
					sub_vector_qm = 
						ISVREF(ISVREF(ISVREF(frame,
						(SI_Long)1L),(SI_Long)11L),
						method_index);
					function_qm = sub_vector_qm ? 
						ISVREF(sub_vector_qm,
						(SI_Long)1L) : Nil;
					if (function_qm)
					    inline_funcall_1(function_qm,
						    frame);
					if (frame_serial_number_of_init_file_command_qm) 
						    {
					    gensymed_symbol = 
						    frame_serial_number_of_init_file_command_qm;
					    gensymed_symbol_1 = 
						    ISVREF(init_file_command_qm,
						    (SI_Long)3L);
					    temp_2 = 
						    FIXNUMP(gensymed_symbol) 
						    ? 
						    (FIXNUMP(gensymed_symbol_1) 
						    ? 
						    FIXNUM_EQ(gensymed_symbol,
						    gensymed_symbol_1) : 
						    TRUEP(Nil)) : 
						    FIXNUMP(gensymed_symbol_1) 
						    ? TRUEP(Nil) : 
						    FIXNUM_EQ(M_CAR(gensymed_symbol),
						    M_CAR(gensymed_symbol_1)) 
						    && 
						    FIXNUM_EQ(M_CDR(gensymed_symbol),
						    M_CDR(gensymed_symbol_1));
					}
					else
					    temp_2 = TRUEP(Nil);
					if ( !temp_2) {
					    init_file_command_qm = 
						    make_command_frame(1,
						    Qinit_file_command);
					    frame_serial_number_of_init_file_command_qm 
						    = 
						    copy_frame_serial_number(ISVREF(init_file_command_qm,
						    (SI_Long)3L));
					}
				    }
				}
				else {
				    notify_user(4,string_constant_5,
					    init_file_truename,
					    Command_line_qm,
					    reason_for_failure_qm);
				    reclaim_text_string(Command_line_qm);
				    error_happened_p = T;
				    goto end_loop;
				}
			    }
			}
			Command_line_qm = 
				g2_stream_read_line(init_file_stream_qm);
			goto next_loop;
		      end_loop:
			if ( !(start_happened_p || error_happened_p)) {
			    if (EQ(Autostart_after_doing_init_file_qm,
				    Qautostart)) {
				notify_user_of_autostart_and_reason(Autostart_reason_in_init_file_qm);
				system_start();
			    }
			    else if (EQ(Autostart_after_doing_init_file_qm,
				    Qdo_not_autostart));
			    else if (start_kb_after_load_from_system_table_qm()) 
					{
				notify_user_of_autostart_and_reason(Qsystem_table);
				system_start();
			    }
			    if (start_on_load_p)
				system_start();
			}
			if (start_happened_p) {
			    next_line_qm = 
				    g2_stream_read_line(init_file_stream_qm);
			    temp_2 =  !TRUEP(next_line_qm);
			    if (temp_2);
			    else {
				residue_qm = next_line_qm;
			      next_loop_1:
				if ( !TRUEP(residue_qm))
				    goto end_loop_1;
				i = (SI_Long)0L;
				ab_loop_bind_ = 
					IFIX(text_string_length(residue_qm));
			      next_loop_2:
				if (i >= ab_loop_bind_)
				    goto end_loop_2;
				if ( 
					!TRUEP(wide_character_member(FIX(UBYTE_16_ISAREF_1(residue_qm,
					i)),list_constant_10))) {
				    temp_2 = TRUEP(Nil);
				    goto end_1;
				}
				i = i + (SI_Long)1L;
				goto next_loop_2;
			      end_loop_2:
				temp_2 = TRUEP(T);
				goto end_1;
				temp_2 = TRUEP(Qnil);
			      end_1:;
				if ( !temp_2) {
				    temp_2 = TRUEP(Nil);
				    goto end_2;
				}
				reclaim_text_string(residue_qm);
				residue_qm = 
					g2_stream_read_line(init_file_stream_qm);
				goto next_loop_1;
			      end_loop_1:
				temp_2 = TRUEP(T);
				goto end_2;
				temp_2 = TRUEP(Qnil);
			      end_2:;
			    }
			    if ( !temp_2)
				notify_user(1,string_constant_6);
			}
			if (init_file_command_qm) {
			    gensymed_symbol = 
				    frame_serial_number_of_init_file_command_qm;
			    gensymed_symbol_1 = 
				    ISVREF(init_file_command_qm,(SI_Long)3L);
			    temp_2 = FIXNUMP(gensymed_symbol) ? 
				    (FIXNUMP(gensymed_symbol_1) ? 
				    FIXNUM_EQ(gensymed_symbol,
				    gensymed_symbol_1) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_1) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol),
				    M_CAR(gensymed_symbol_1)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol),
				    M_CDR(gensymed_symbol_1));
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2)
			    delete_frame(init_file_command_qm);
		      POP_SPECIAL();
		  }
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    if (init_file_stream_qm) {
		if ( !EQ(init_file_stream_qm,Qunbound_in_protected_let))
		    g2_stream_close(init_file_stream_qm);
	    }
	    if (namestring_1) {
		if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
		    if (pathname_used_p)
			reclaim_text_string(namestring_1);
		}
	    }
	    CONTINUE_UNWINDING(0);
	}
	POP_UNWIND_PROTECT(1);
	if (init_file_truename) {
	    if ( !EQ(init_file_truename,Qunbound_in_protected_let))
		reclaim_text_string(init_file_truename);
	}
	CONTINUE_UNWINDING(1);
	RESTORE_STACK();
	return VALUES_1(T);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2_kb_pathname, Qdefault_g2_kb_pathname);

static Object array_constant_9;    /* # */

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-KB-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2_kb_command_line()
{
    x_note_fn_call(134,41);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant_9,array_constant_3,array_constant_9,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_kb_command_line, Qpathname_for_disabling_g2_kb_command_line);

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

/* GET-OR-USE-G2-KB-PATHNAME */
Object get_or_use_g2_kb_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(134,42);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2_kb_pathname,
	    Pathname_for_disabling_g2_kb_command_line,array_constant_10,
	    array_constant_11,array_constant_10,provide_desired_namestring_p);
}

static Object array_constant_12;   /* # */

static Object Qdefault;            /* default */

static Object Qload_from_command_line;  /* load-from-command-line */

static Object Qcommand_line_argument;  /* command-line-argument */

static Object Kenvironment_variable;  /* :environment-variable */

static Object string_constant_7;   /* "G2 could not find the file \"~a\", ~
				    *                             which was specified as an environment variable ~
				    *                             when G2 was launched."
				    */

static Object Kcommand_line;       /* :command-line */

static Object string_constant_8;   /* "G2 could not find the file \"~a\", ~
				    *                             which was specified in the command line that launched G2."
				    */

/* DO-G2-KB-LOAD-AT-LAUNCH */
Object do_g2_kb_load_at_launch()
{
    Object init_file_pathname_qm, kb_file_pathname_qm;
    Object namestring_explicitly_specified_from_os_environment_qm;
    Object source_of_namestring_specification, doing_g2_init_kb_p;
    Object start_on_load_p, temp, readable_namestring;
    Declare_special(1);
    Object result;

    x_note_fn_call(134,43);
    force_process_drawing();
    init_file_pathname_qm = get_or_use_g2_init_pathname(0);
    if ( !TRUEP(Nil)) {
	result = get_or_use_g2_kb_pathname(1,T);
	MVS_3(result,kb_file_pathname_qm,
		namestring_explicitly_specified_from_os_environment_qm,
		source_of_namestring_specification);
	if (kb_file_pathname_qm) {
	    doing_g2_init_kb_p = T;
	    start_on_load_p = get_command_line_flag_argument(1,
		    array_constant_6);
	    if (start_on_load_p);
	    else
		start_on_load_p = 
			get_gensym_environment_variable(array_constant_7);
	    PUSH_SPECIAL_WITH_SYMBOL(Doing_g2_init_kb_p,Qdoing_g2_init_kb_p,doing_g2_init_kb_p,
		    0);
	      temp =  !TRUEP(get_command_line_flag_argument(1,
		      array_constant_12)) ? Qdefault : Nil;
	      read_kb_or_group_thereof(kb_file_pathname_qm,T,T,Nil,temp,
		      start_on_load_p &&  !TRUEP(init_file_pathname_qm) ? 
		      Qload_from_command_line : Nil,Nil,Nil);
	    POP_SPECIAL();
	}
	else if (namestring_explicitly_specified_from_os_environment_qm) {
	    readable_namestring = import_text_string(2,
		    namestring_explicitly_specified_from_os_environment_qm,
		    Qcommand_line_argument);
	    if (EQ(source_of_namestring_specification,Kenvironment_variable))
		notify_user(2,string_constant_7,readable_namestring);
	    else if (EQ(source_of_namestring_specification,Kcommand_line))
		notify_user(2,string_constant_8,readable_namestring);
	    reclaim_text_string(readable_namestring);
	}
	if (namestring_explicitly_specified_from_os_environment_qm)
	    reclaim_text_string(namestring_explicitly_specified_from_os_environment_qm);
    }
    if (init_file_pathname_qm)
	return do_g2_init_file();
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Transients_to_delete, Qtransients_to_delete);

DEFINE_VARIABLE_WITH_SYMBOL(Represented_frames_in_limbo, Qrepresented_frames_in_limbo);

/* KB-IS-SAVABLE-P */
Object kb_is_savable_p()
{
    Object represented_frames_in_limbo, entangled_representations;
    Object transients_to_delete, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object kb_workspace, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, block, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(134,44);
    represented_frames_in_limbo = Nil;
    entangled_representations = Nil;
    transients_to_delete = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Transients_to_delete,Qtransients_to_delete,transients_to_delete,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Represented_frames_in_limbo,Qrepresented_frames_in_limbo,represented_frames_in_limbo,
	      1);
	identify_all_savable_kb_workspaces();
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	kb_workspace = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qkb_workspace);
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
	  kb_workspace = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)4L)) & 
		  (SI_Long)2L)) {
	      gensymed_symbol = ACCESS_ONCE(ISVREF(kb_workspace,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	      ab_queue_form_ = gensymed_symbol;
	      ab_next_queue_element_ = Nil;
	      block = Nil;
	      if (ab_queue_form_)
		  ab_next_queue_element_ = 
			  constant_queue_next(ISVREF(ab_queue_form_,
			  (SI_Long)2L),ab_queue_form_);
	    next_loop_2:
	      if ( !TRUEP(ab_next_queue_element_))
		  goto end_loop_2;
	      block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	      ab_next_queue_element_ = 
		      constant_queue_next(ab_next_queue_element_,
		      ab_queue_form_);
	      sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
	      if (temp ? (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		      (SI_Long)1L) : TRUEP(Nil)) {
		  temp_1 = check_table_for_entanglement(block);
		  entangled_representations = nconc2(temp_1,
			  entangled_representations);
	      }
	      goto next_loop_2;
	    end_loop_2:;
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	if (Represented_frames_in_limbo) {
	    temp_1 = write_problems_saving_kb(Represented_frames_in_limbo,
		    entangled_representations,Transients_to_delete);
	    reclaim_gensym_list_1(Transients_to_delete);
	    Transients_to_delete = Nil;
	    result = VALUES_3(Nil,temp_1,Nil);
	}
	else if (entangled_representations) {
	    temp_1 = write_problems_saving_kb(Represented_frames_in_limbo,
		    entangled_representations,Transients_to_delete);
	    result = VALUES_3(T,temp_1,Transients_to_delete);
	}
	else
	    result = VALUES_3(T,Nil,Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CHECK-TABLE-FOR-ENTANGLEMENT */
Object check_table_for_entanglement(table)
    Object table;
{
    Object problem_qm, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, gensymed_symbol_5, ab_loop_list_;
    Object ab_loop_list__1, represented_frame, root_qm;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__2, ab_loop_it_, temp_1, temp_2;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(134,45);
    problem_qm = Nil;
    gensymed_symbol = table;
    gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol_1 = Nil;
	gensymed_symbol_5 = Nil;
	ab_loop_list_ = ISVREF(gensymed_symbol,(SI_Long)19L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol_5 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = Nil;
	ab_loop_list__1 = gensymed_symbol_5;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	gensymed_symbol = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (gensymed_symbol && CONSP(gensymed_symbol)) {
	    represented_frame = 
		    get_slot_represented_by_text_cell_if_any(gensymed_symbol);
	    if (represented_frame &&  !EQ(gensymed_symbol_1,
			represented_frame)) {
		gensymed_symbol_1 = represented_frame;
		if ( ! !((SI_Long)0L != (IFIX(ISVREF(represented_frame,
			(SI_Long)5L)) & (SI_Long)786432L))) {
		    root_qm = represented_frame;
		  next_loop_2:
		    if ( !TRUEP(root_qm) || (SI_Long)0L != 
			    (IFIX(ISVREF(root_qm,(SI_Long)5L)) & 
			    (SI_Long)262144L))
			goto end_loop_2;
		    root_qm = parent(root_qm);
		    goto next_loop_2;
		  end_loop_2:
		    if (root_qm) {
			gensym_modify_macro_using_test_arg_1 = root_qm;
			car_1 = gensym_modify_macro_using_test_arg_1;
			cdr_1 = Transients_to_delete;
			key_result = car_1;
			x_element = Nil;
			ab_loop_list__2 = cdr_1;
			ab_loop_it_ = Nil;
		      next_loop_3:
			if ( !TRUEP(ab_loop_list__2))
			    goto end_loop_3;
			x_element = M_CAR(ab_loop_list__2);
			ab_loop_list__2 = M_CDR(ab_loop_list__2);
			ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
			if (ab_loop_it_) {
			    temp = TRUEP(ab_loop_it_);
			    goto end_1;
			}
			goto next_loop_3;
		      end_loop_3:
			temp = TRUEP(Qnil);
		      end_1:;
			temp_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
			Transients_to_delete = temp_1;
		    }
		    else {
			gensym_modify_macro_using_test_arg_1 = 
				represented_frame;
			car_1 = gensym_modify_macro_using_test_arg_1;
			cdr_1 = Represented_frames_in_limbo;
			key_result = car_1;
			x_element = Nil;
			ab_loop_list__2 = cdr_1;
			ab_loop_it_ = Nil;
		      next_loop_4:
			if ( !TRUEP(ab_loop_list__2))
			    goto end_loop_4;
			x_element = M_CAR(ab_loop_list__2);
			ab_loop_list__2 = M_CDR(ab_loop_list__2);
			ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
			if (ab_loop_it_) {
			    temp = TRUEP(ab_loop_it_);
			    goto end_2;
			}
			goto next_loop_4;
		      end_loop_4:
			temp = TRUEP(Qnil);
		      end_2:;
			temp_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
			Represented_frames_in_limbo = temp_1;
		    }
		    problem_qm = T;
		}
	    }
	}
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    temp_2 = problem_qm ? gensym_cons_1(table,Nil) : Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(table,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_5:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_5;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
	temp = (SI_Long)0L < gensymed_symbol_2;
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
	    (SI_Long)786432L)) : TRUEP(Nil)) {
	ab_loopvar__2 = check_table_for_entanglement(subblock);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop_5;
  end_loop_5:
    temp_3 = ab_loopvar_;
    goto end_3;
    temp_3 = Qnil;
  end_3:;
    return VALUES_1(nconc2(temp_2,temp_3));
}

static Object Qparent_frame;       /* parent-frame */

/* PARENT */
Object parent(block)
    Object block;
{
    Object gensymed_symbol, temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(134,46);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    temp = gensymed_symbol;
    if (temp);
    else
	temp = get_lookup_slot_value_given_default(block,Qparent_frame,Nil);
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	temp = temp_1 ? ISVREF(block,(SI_Long)18L) : Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	temp = temp_1 ? ISVREF(ISVREF(block,(SI_Long)21L),(SI_Long)3L) : Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return parent_variable_function(block);
	else
	    return VALUES_1(Nil);
    }
}

static Object string_constant_9;   /* "and" */

/* WRITE-LIST-OF-FORCED-NAMES */
Object write_list_of_forced_names(list_of_frames)
    Object list_of_frames;
{
    Object block, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object list_of_names;

    x_note_fn_call(134,47);
    block = Nil;
    ab_loop_list_ = list_of_frames;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    gensym_cons_1(get_or_make_up_designation_for_block(block),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    list_of_names = ab_loopvar_;
    goto end_1;
    list_of_names = Qnil;
  end_1:;
    write_list_in_chicago_style(2,list_of_names,string_constant_9);
    return reclaim_gensym_list_1(list_of_names);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_10;  /* "~A, ~A ~A ~A" */

static Object string_constant_11;  /* "This KB cannot be saved because of certain problems.  Generally" */

static Object string_constant_12;  /* "such problems tend to go away if you reset G2 and/or delete" */

static Object string_constant_13;  /* "certain transient items.  Note that" */

static Object string_constant_14;  /* "resetting G2 deletes all transient items." */

static Object string_constant_15;  /* "~%~%The item~a " */

static Object string_constant_16;  /* "s" */

static Object string_constant_17;  /* "" */

static Object string_constant_18;  /* " cannot be saved, but ~a ~a represented by one or more tables that ~
				    *            must be saved.  Deleting such tables or deleting the above item~a ~
				    *            may make this KB savable."
				    */

static Object string_constant_19;  /* "they" */

static Object string_constant_20;  /* "it" */

static Object string_constant_21;  /* "are" */

static Object string_constant_22;  /* "is" */

static Object string_constant_23;  /* "~%~%Deleting the following transient item~a ~a make this KB savable: " */

static Object string_constant_24;  /* "will" */

static Object string_constant_25;  /* "may" */

/* WRITE-PROBLEMS-SAVING-KB */
Object write_problems_saving_kb(represented_frames_in_limbo,
	    entangled_representations,transients_to_delete)
    Object represented_frames_in_limbo, entangled_representations;
    Object transients_to_delete;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);
    Object result;

    x_note_fn_call(134,48);
    PUSH_SPECIAL_WITH_SYMBOL(Transients_to_delete,Qtransients_to_delete,transients_to_delete,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Represented_frames_in_limbo,Qrepresented_frames_in_limbo,represented_frames_in_limbo,
	      5);
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
		  if (Represented_frames_in_limbo || entangled_representations)
		      tformat(5,string_constant_10,string_constant_11,
			      string_constant_12,string_constant_13,
			      string_constant_14);
		  if (Represented_frames_in_limbo) {
		      tformat(2,string_constant_15,
			      CDR(Represented_frames_in_limbo) ? 
			      string_constant_16 : string_constant_17);
		      write_list_of_forced_names(Represented_frames_in_limbo);
		      tformat(4,string_constant_18,
			      CDR(Represented_frames_in_limbo) ? 
			      string_constant_19 : string_constant_20,
			      CDR(Represented_frames_in_limbo) ? 
			      string_constant_21 : string_constant_22,
			      CDR(Represented_frames_in_limbo) ? 
			      string_constant_16 : string_constant_17);
		  }
		  if (Transients_to_delete) {
		      tformat(3,string_constant_23,
			      CDR(Transients_to_delete) ? 
			      string_constant_16 : string_constant_17, 
			      !TRUEP(Represented_frames_in_limbo) ? 
			      string_constant_24 : string_constant_25);
		      write_list_of_forced_names(Transients_to_delete);
		  }
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	reclaim_gensym_list_1(Represented_frames_in_limbo);
	reclaim_gensym_list_1(entangled_representations);
	result = VALUES_1(temp);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qframe_flags;        /* frame-flags */

/* IDENTIFY-ALL-SAVABLE-KB-WORKSPACES */
Object identify_all_savable_kb_workspaces()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, kb_workspace;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(134,49);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    kb_workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qkb_workspace);
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
      kb_workspace = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(kb_workspace,Qframe_flags);
      svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)4L)) &  ~(SI_Long)2L;
      ISVREF(kb_workspace,(SI_Long)4L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    kb_workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qkb_workspace);
    next_loop_2:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_3:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_2;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_2;
	  goto next_loop_3;
	end_loop_2:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_3;
      kb_workspace = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(kb_workspace,(SI_Long)4L)) & 
	      (SI_Long)2L)))
	  mark_kb_workspace_if_savable(kb_workspace);
      goto next_loop_2;
    end_loop_3:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MARK-KB-WORKSPACE-IF-SAVABLE */
Object mark_kb_workspace_if_savable(kb_workspace)
    Object kb_workspace;
{
    Object parent_qm, gensymed_symbol, parent_of_parent_qm;
    Object sub_class_bit_vector;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(134,50);
    parent_qm = ISVREF(kb_workspace,(SI_Long)18L);
    if ( !TRUEP(parent_qm)) {
	if (orphan_workspace_p(kb_workspace) || (SI_Long)0L != 
		(IFIX(ISVREF(kb_workspace,(SI_Long)5L)) & (SI_Long)262144L))
	    return VALUES_1(Nil);
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(kb_workspace,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)4L)) | 
		    (SI_Long)2L;
	    ISVREF(kb_workspace,(SI_Long)4L) = FIX(svref_new_value);
	    return VALUES_1(T);
	}
    }
    else if ((SI_Long)0L != (IFIX(ISVREF(parent_qm,(SI_Long)5L)) & 
	    (SI_Long)786432L))
	return VALUES_1(Nil);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(parent_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	parent_of_parent_qm = gensymed_symbol;
	if (parent_of_parent_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(parent_of_parent_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	    if ( !temp)
		return VALUES_1(Nil);
	    else if ((SI_Long)0L != (IFIX(ISVREF(parent_of_parent_qm,
		    (SI_Long)4L)) & (SI_Long)2L)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(kb_workspace,Qframe_flags);
		svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)4L)) | 
			(SI_Long)2L;
		ISVREF(kb_workspace,(SI_Long)4L) = FIX(svref_new_value);
		return VALUES_1(T);
	    }
	    else if (mark_kb_workspace_if_savable(parent_of_parent_qm)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(kb_workspace,Qframe_flags);
		svref_new_value = IFIX(ISVREF(kb_workspace,(SI_Long)4L)) | 
			(SI_Long)2L;
		ISVREF(kb_workspace,(SI_Long)4L) = FIX(svref_new_value);
		return VALUES_1(T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qcomputation_style;  /* computation-style */

/* SAVABLE-BLOCK-P */
Object savable_block_p(block)
    Object block;
{
    Object parent_1, saved_block, gensymed_symbol, sub_class_bit_vector;
    Object gensymed_symbol_4, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(134,51);
    parent_1 = Nil;
    saved_block = Nil;
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)786432L))
	return VALUES_1(Nil);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(block,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	if (temp)
	    parent_1 = parent_variable_function(block);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		if (temp)
		    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block,
			    (SI_Long)4L)) & (SI_Long)2L) ? T : Nil);
		return VALUES_1(Nil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_class_description,
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
		if (temp)
		    parent_1 = ISVREF(ISVREF(block,(SI_Long)21L),(SI_Long)3L);
		else {
		    gensymed_symbol_4 = 
			    lookup_global_or_kb_specific_property_value(Qcomputation_style,
			    Class_description_gkbprop);
		    if (gensymed_symbol_4) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			return savable_computation_style_p(block);
		    else {
			gensymed_symbol = ACCESS_ONCE(ISVREF(block,
				(SI_Long)14L));
			gensymed_symbol = gensymed_symbol ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol,
				(SI_Long)5L)) : Nil;
			temp_1 = gensymed_symbol;
			if (temp_1);
			else
			    temp_1 = 
				    get_lookup_slot_value_given_default(block,
				    Qparent_frame,Nil);
			parent_1 = temp_1;
			if ( !TRUEP(parent_1)) {
			    sub_class_bit_vector = ISVREF(ISVREF(block,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Class_definition_class_description,
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
				temp_1 = (SI_Long)0L < gensymed_symbol_1 ? 
					T : Nil;
			    }
			    else
				temp_1 = Nil;
			    if (temp_1)
				return VALUES_1(temp_1);
			    else {
				gensymed_symbol = 
					lookup_global_or_kb_specific_property_value(Qsystem_frame,
					Class_description_gkbprop);
				if (gensymed_symbol) {
				    sub_class_bit_vector = 
					    ISVREF(ISVREF(block,
					    (SI_Long)1L),(SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(gensymed_symbol,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_1 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_2 = (SI_Long)1L;
					gensymed_symbol_3 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_2 = 
						gensymed_symbol_2 << 
						gensymed_symbol_3;
					gensymed_symbol_1 = 
						gensymed_symbol_1 & 
						gensymed_symbol_2;
					return VALUES_1((SI_Long)0L < 
						gensymed_symbol_1 ? T : Nil);
				    }
				    else
					return VALUES_1(Nil);
				}
				else
				    return VALUES_1(Nil);
			    }
			}
			else {
			    sub_class_bit_vector = ISVREF(ISVREF(parent_1,
				    (SI_Long)1L),(SI_Long)19L);
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
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(parent_1,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Kb_workspace_class_description,
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
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    return VALUES_1((SI_Long)0L != 
					    (IFIX(ISVREF(parent_1,
					    (SI_Long)4L)) & (SI_Long)2L) ? 
					    T : Nil);
				else
				    return VALUES_1(Nil);
			    }
			}
		    }
		}
	    }
	}
    }
  next_loop:
    if ((SI_Long)0L != (IFIX(ISVREF(parent_1,(SI_Long)5L)) & (SI_Long)786432L))
	return VALUES_1(Nil);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(parent_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    parent_1 = ISVREF(ISVREF(parent_1,(SI_Long)21L),(SI_Long)3L);
	else {
	    saved_block = parent_1;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(parent_1,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_1 = gensymed_symbol;
	    if (temp_1);
	    else
		temp_1 = get_lookup_slot_value_given_default(parent_1,
			Qparent_frame,Nil);
	    parent_1 = temp_1;
	    if ( !TRUEP(parent_1)) {
		sub_class_bit_vector = ISVREF(ISVREF(saved_block,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		}
		else
		    temp_1 = Nil;
		if (temp_1)
		    return VALUES_1(temp_1);
		else {
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(Qsystem_frame,
			    Class_description_gkbprop);
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(ISVREF(saved_block,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			    return VALUES_1((SI_Long)0L < 
				    gensymed_symbol_1 ? T : Nil);
			}
			else
			    return VALUES_1(Nil);
		    }
		    else
			return VALUES_1(Nil);
		}
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(parent_1,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(parent_1,
			    (SI_Long)1L),(SI_Long)19L);
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
		    if (temp)
			return VALUES_1((SI_Long)0L != 
				(IFIX(ISVREF(parent_1,(SI_Long)4L)) & 
				(SI_Long)2L) ? T : Nil);
		    else
			return VALUES_1(Nil);
		}
	    }
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_save_termination_reason_qm, Qkb_save_termination_reason_qm);

static Object string_constant_26;  /* "The modules in this KB are not consistent; you ~
				    *                         therefore cannot save individual modules.  ~
				    *                         NO PART OF THIS KB HAS BEEN SAVED!"
				    */

static Object Qkb_not_consistently_modularized;  /* kb-not-consistently-modularized */

/* REJECT-SAVE-KB-IF-SAVING-MODULES-WITHOUT-CONSISTENCY */
Object reject_save_kb_if_saving_modules_without_consistency()
{
    char temp;

    x_note_fn_call(134,52);
    if ( !TRUEP(Inhibit_modularity_consistency_checking_qm)) {
	if (check_savability_of_kb_in_terms_of_modularity(2,Nil,T)) {
	    notify_user(1,string_constant_26);
	    temp = TRUEP(T);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Kb_save_termination_reason_qm = Qkb_not_consistently_modularized;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qkb_not_savable;     /* kb-not-savable */

/* REJECT-SAVE-KB-IF-NOT-SAVABLE */
Object reject_save_kb_if_not_savable()
{
    Object temp, message_text_string_qm, transients_to_delete;
    Declare_special(1);
    Object result;

    x_note_fn_call(134,53);
    result = kb_is_savable_p();
    MVS_3(result,temp,message_text_string_qm,transients_to_delete);
    PUSH_SPECIAL_WITH_SYMBOL(Transients_to_delete,Qtransients_to_delete,transients_to_delete,
	    0);
      if (message_text_string_qm) {
	  notify_user(2,string_constant,message_text_string_qm);
	  reclaim_text_string(message_text_string_qm);
	  reclaim_gensym_list_1(Transients_to_delete);
	  Transients_to_delete = Nil;
	  Kb_save_termination_reason_qm = Qkb_not_savable;
	  result = VALUES_1(T);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_not_authorized;  /* g2-not-authorized */

/* REJECT-SAVE-KB-IF-NOT-AUTHORIZED */
Object reject_save_kb_if_not_authorized()
{
    x_note_fn_call(134,54);
    if ( ! !EQ(Unevaluated_expression,Within_side_limits)) {
	Kb_save_termination_reason_qm = Qg2_not_authorized;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_27;  /* "Save is already in progress." */

static Object Qin_progress;        /* in-progress */

/* REJECT-SAVE-KB-IF-SAVE-OR-BACKUP-IN-PROGRESS */
Object reject_save_kb_if_save_or_backup_in_progress()
{
    x_note_fn_call(134,55);
    if (Current_saving_context_qm) {
	notify_user(1,string_constant_27);
	Kb_save_termination_reason_qm = Qin_progress;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* REJECT-SAVE-KB-IF-RUN-TIME-ONLY */
Object reject_save_kb_if_run_time_only(type_of_kb_save)
    Object type_of_kb_save;
{
    x_note_fn_call(134,56);
    return VALUES_1(Nil);
}

static Object string_constant_28;  /* "WARNING: Saving did not complete. ~A" */

static Object Qwildcards_in_filename;  /* wildcards-in-filename */

/* REJECT-SAVE-KB-IF-FILENAME-PROBLEMS */
Object reject_save_kb_if_filename_problems(pathname_or_module_saving_schedule)
    Object pathname_or_module_saving_schedule;
{
    Object filename_string_qm;

    x_note_fn_call(134,57);
    filename_string_qm = 
	    any_wild_pathnames_p(pathname_or_module_saving_schedule);
    if (filename_string_qm) {
	notify_user(2,string_constant_28,
		get_error_string_for_illegal_wildcards_in_filename(filename_string_qm));
	reclaim_text_string(filename_string_qm);
	Kb_save_termination_reason_qm = Qwildcards_in_filename;
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* ANY-WILD-PATHNAMES-P */
Object any_wild_pathnames_p(pathname_or_module_saving_schedule)
    Object pathname_or_module_saving_schedule;
{
    Object temp;

    x_note_fn_call(134,58);
    if (CONSP(pathname_or_module_saving_schedule)) {
	temp = any_wild_pathnames_p(CAR(pathname_or_module_saving_schedule));
	if (temp)
	    return VALUES_1(temp);
	else
	    return any_wild_pathnames_p(REST(pathname_or_module_saving_schedule));
    }
    else if (SIMPLE_VECTOR_P(pathname_or_module_saving_schedule) && 
	    EQ(ISVREF(pathname_or_module_saving_schedule,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_pathname_g2_struct)) {
	if (gensym_wild_pathname_p(pathname_or_module_saving_schedule)) {
	    temp = ISVREF(pathname_or_module_saving_schedule,(SI_Long)10L);
	    return FUNCALL_1(temp,pathname_or_module_saving_schedule);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

void kb_save2_INIT()
{
    Object temp;
    Object AB_package, Qparent, list_constant_12, list_constant_15, Qpathnames;
    Object Qinitializer_for_pathname_for_disabling_g2_kb_command_line;
    Object Kfuncall, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qkb_save2;
    Object list_constant_14;
    Object Qinitializer_for_pathname_for_disabling_g2_init_command_line;
    Object Kabsolute, list_constant_13, Qinitialize_default_g2_init_pathname;
    Object Qtext_box_format, Qtext_cell_plist_for_text_box;
    Object Qworkspace_foreground_color_qm, Qworkspace_background_color_qm;
    Object Qicon_attributes_plist, Qnot_savable, Qdependant, Qdepreciated;
    Object Qrestore_ui_client_interfaces, Qinitialize_current_kb_serial_number;
    Object list_constant_11;

    x_note_fn_call(134,59);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qdefault_x_scale = STATIC_SYMBOL("DEFAULT-X-SCALE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qdefault_y_scale = STATIC_SYMBOL("DEFAULT-Y-SCALE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    Qmain_kb_being_read_qm = STATIC_SYMBOL("MAIN-KB-BEING-READ\?",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qcurrent_kb_serial_number = STATIC_SYMBOL("CURRENT-KB-SERIAL-NUMBER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_kb_serial_number,
	    Current_kb_serial_number);
    Qkb_save2 = STATIC_SYMBOL("KB-SAVE2",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_current_kb_serial_number = 
	    STATIC_SYMBOL("INITIALIZE-CURRENT-KB-SERIAL-NUMBER",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_current_kb_serial_number);
    record_system_variable(Qcurrent_kb_serial_number,Qkb_save2,
	    list_constant_11,Qnil,Qnil,Qnil,Qt);
    Qlast_assigned_kb_serial_number = 
	    STATIC_SYMBOL("LAST-ASSIGNED-KB-SERIAL-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_assigned_kb_serial_number,
	    Last_assigned_kb_serial_number);
    record_system_variable(Qlast_assigned_kb_serial_number,Qkb_save2,
	    FIX((SI_Long)-1L),Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_current_kb_serial_number,
	    STATIC_FUNCTION(initialize_current_kb_serial_number,NIL,FALSE,
	    0,0));
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    string_constant = STATIC_STRING("~a");
    Qkb = STATIC_SYMBOL("KB",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qstatistics = STATIC_SYMBOL("STATISTICS",AB_package);
    Qui_client_interface_saved_icp_socket_list = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-SAVED-ICP-SOCKET-LIST",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qui_client_interface_saved_icp_socket_list,
	    Ui_client_interface_saved_icp_socket_list);
    record_system_variable(Qui_client_interface_saved_icp_socket_list,
	    Qkb_save2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qui_client_interface_saved_session_list = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-SAVED-SESSION-LIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qui_client_interface_saved_session_list,
	    Ui_client_interface_saved_session_list);
    record_system_variable(Qui_client_interface_saved_session_list,
	    Qkb_save2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcallback_representation_callback_serial_number = 
	    STATIC_SYMBOL("CALLBACK-REPRESENTATION-CALLBACK-SERIAL-NUMBER",
	    AB_package);
    Qitem_representation_denotation = 
	    STATIC_SYMBOL("ITEM-REPRESENTATION-DENOTATION",AB_package);
    Qrepresentation_address = STATIC_SYMBOL("REPRESENTATION-ADDRESS",
	    AB_package);
    if (Deleting_ui_client_interfaces_for_clear_kb == UNBOUND)
	Deleting_ui_client_interfaces_for_clear_kb = Nil;
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    Qcallback_representation = STATIC_SYMBOL("CALLBACK-REPRESENTATION",
	    AB_package);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qgsi_interface_icp_socket = STATIC_SYMBOL("GSI-INTERFACE-ICP-SOCKET",
	    AB_package);
    Qgsi_connection_configuration = 
	    STATIC_SYMBOL("GSI-CONNECTION-CONFIGURATION",AB_package);
    Qremote_process_initialization_string = 
	    STATIC_SYMBOL("REMOTE-PROCESS-INITIALIZATION-STRING",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qui_client_interface_callback_qm = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-CALLBACK\?",AB_package);
    Qui_client_interface_callback_data = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-CALLBACK-DATA",AB_package);
    Qui_client_interface_module_information_callback_qm = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-MODULE-INFORMATION-CALLBACK\?",
	    AB_package);
    Qui_client_interface_module_information_callback_data = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-MODULE-INFORMATION-CALLBACK-DATA",
	    AB_package);
    Qui_client_interface_progress_callback_qm = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-PROGRESS-CALLBACK\?",
	    AB_package);
    Qui_client_interface_progress_callback_data = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-PROGRESS-CALLBACK-DATA",
	    AB_package);
    Qui_client_interface_dialog_callback_qm = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-DIALOG-CALLBACK\?",AB_package);
    Qui_client_interface_dialog_callback_data = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-DIALOG-CALLBACK-DATA",
	    AB_package);
    Qui_client_interface_dialog_list = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-DIALOG-LIST",AB_package);
    Qui_client_interface_sessions = 
	    STATIC_SYMBOL("UI-CLIENT-INTERFACE-SESSIONS",AB_package);
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qitem_representation = STATIC_SYMBOL("ITEM-REPRESENTATION",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_access_error_g2_struct = 
	    STATIC_SYMBOL("ACCESS-ERROR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_1 = 
	    STATIC_STRING("Unable to restore ui-client-session ~NF properly");
    Qrestore_ui_client_interfaces = 
	    STATIC_SYMBOL("RESTORE-UI-CLIENT-INTERFACES",AB_package);
    temp = adjoin(2,Qrestore_ui_client_interfaces,
	    List_of_module_pre_conflict_resolution_post_loading_functions);
    List_of_module_pre_conflict_resolution_post_loading_functions = temp;
    temp = adjoin(2,Qrestore_ui_client_interfaces,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp;
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    Qui_client_session_parent_interface = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-PARENT-INTERFACE",AB_package);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    SET_SYMBOL_FUNCTION(Qrestore_ui_client_interfaces,
	    STATIC_FUNCTION(restore_ui_client_interfaces,NIL,FALSE,0,0));
    if (In_clear_kb_p == UNBOUND)
	In_clear_kb_p = Nil;
    Qclear_kb_internal = STATIC_SYMBOL("CLEAR-KB-INTERNAL",AB_package);
    Qclear_kb = STATIC_SYMBOL("CLEAR-KB",AB_package);
    string_constant_2 = STATIC_STRING("new-kb");
    SET_SYMBOL_FUNCTION(Qclear_kb,STATIC_FUNCTION(clear_kb,NIL,TRUE,0,1));
    if (Releasing_kb_qm == UNBOUND)
	Releasing_kb_qm = Nil;
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    if (Ignore_kb_state_changes_p == UNBOUND)
	Ignore_kb_state_changes_p = Nil;
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qworkspace_frame = STATIC_SYMBOL("WORKSPACE-FRAME",AB_package);
    Qitem_position = STATIC_SYMBOL("ITEM-POSITION",AB_package);
    Qicon_position = STATIC_SYMBOL("ICON-POSITION",AB_package);
    Qicon_orientation = STATIC_SYMBOL("ICON-ORIENTATION",AB_package);
    Qreflection_and_rotation = STATIC_SYMBOL("REFLECTION-AND-ROTATION",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qicon_color_pattern = STATIC_SYMBOL("ICON-COLOR-PATTERN",AB_package);
    Qworkspace_color_pattern = STATIC_SYMBOL("WORKSPACE-COLOR-PATTERN",
	    AB_package);
    Qtext_box_color_pattern = STATIC_SYMBOL("TEXT-BOX-COLOR-PATTERN",
	    AB_package);
    Qconnection_color_pattern = STATIC_SYMBOL("CONNECTION-COLOR-PATTERN",
	    AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qtext_box_font = STATIC_SYMBOL("TEXT-BOX-FONT",AB_package);
    Qtext_of_changed_slots = STATIC_SYMBOL("TEXT-OF-CHANGED-SLOTS",AB_package);
    if (Do_not_note_permanent_changes_p == UNBOUND)
	Do_not_note_permanent_changes_p = Nil;
    Qdepreciated = STATIC_SYMBOL("DEPRECIATED",AB_package);
    Qdependant = STATIC_SYMBOL("DEPENDANT",AB_package);
    Qnot_savable = STATIC_SYMBOL("NOT-SAVABLE",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qdepreciated,Qdependant,
	    Qnot_savable);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qattributes_permamently_changed = 
	    STATIC_SYMBOL("ATTRIBUTES-PERMAMENTLY-CHANGED",AB_package);
    Qicon_attributes_plist = STATIC_SYMBOL("ICON-ATTRIBUTES-PLIST",AB_package);
    list_constant_1 = STATIC_CONS(Qicon_attributes_plist,Qnil);
    Qget_text_box_color_pattern = 
	    STATIC_SYMBOL("GET-TEXT-BOX-COLOR-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qget_text_box_color_pattern,
	    STATIC_FUNCTION(get_text_box_color_pattern,NIL,TRUE,1,5));
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    list_constant_2 = STATIC_CONS(Qtext_cell_plist_for_text_box,Qnil);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    list_constant_3 = STATIC_CONS(Qworkspace_background_color_qm,Qnil);
    Qworkspace_foreground_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR\?",AB_package);
    list_constant_4 = STATIC_CONS(Qworkspace_foreground_color_qm,Qnil);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    list_constant_5 = STATIC_CONS(Qbox_translation_and_text,Qnil);
    Qtext_box_format = STATIC_SYMBOL("TEXT-BOX-FORMAT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,
	    Qtext_cell_plist_for_text_box,Qtext_box_format);
    Qkb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("KB-STATE-CHANGES-PREVIOUS-CONS\?",AB_package);
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
    list_constant_7 = STATIC_LIST((SI_Long)4L,Qreflected,
	    Qreflected_clockwise_90,Qreflected_clockwise_180,
	    Qreflected_clockwise_270);
    Kno_change = STATIC_SYMBOL("NO-CHANGE",Pkeyword);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)8L,Qicon_color,
	    Qicon_color_pattern,Qtext_box_color_pattern,Qbackground_color,
	    Qborder_color,Qforeground_color,Qtext_color,
	    Qconnection_color_pattern);
    array_constant_1 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2_init_pathname = STATIC_SYMBOL("DEFAULT-G2-INIT-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2_init_pathname,
	    Default_g2_init_pathname);
    Qpathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Qinitialize_default_g2_init_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2-INIT-PATHNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2_init_pathname,
	    STATIC_FUNCTION(initialize_default_g2_init_pathname,NIL,FALSE,
	    0,0));
    list_constant_13 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2_init_pathname);
    record_system_variable(Qdefault_g2_init_pathname,Qpathnames,
	    list_constant_13,Qnil,Qnil,Qnil,Qnil);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    list_constant_9 = STATIC_CONS(Kabsolute,Qnil);
    array_constant_3 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qpathname_for_disabling_g2_init_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2-INIT-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2_init_command_line,
	    Pathname_for_disabling_g2_init_command_line);
    Qinitializer_for_pathname_for_disabling_g2_init_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-INIT-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2_init_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2_init_command_line,
	    NIL,FALSE,0,0));
    list_constant_14 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2_init_command_line);
    record_system_variable(Qpathname_for_disabling_g2_init_command_line,
	    Qpathnames,list_constant_14,Qnil,Qnil,Qnil,Qnil);
    array_constant_5 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qdoing_g2_init_file_p = STATIC_SYMBOL("DOING-G2-INIT-FILE-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdoing_g2_init_file_p,Doing_g2_init_file_p);
    record_system_variable(Qdoing_g2_init_file_p,Qkb_save2,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qdoing_g2_init_kb_p = STATIC_SYMBOL("DOING-G2-INIT-KB-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdoing_g2_init_kb_p,Doing_g2_init_kb_p);
    record_system_variable(Qdoing_g2_init_kb_p,Qkb_save2,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qautostart_after_doing_init_file_qm = 
	    STATIC_SYMBOL("AUTOSTART-AFTER-DOING-INIT-FILE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qautostart_after_doing_init_file_qm,
	    Autostart_after_doing_init_file_qm);
    record_system_variable(Qautostart_after_doing_init_file_qm,Qkb_save2,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qautostart_reason_in_init_file_qm = 
	    STATIC_SYMBOL("AUTOSTART-REASON-IN-INIT-FILE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qautostart_reason_in_init_file_qm,
	    Autostart_reason_in_init_file_qm);
    record_system_variable(Qautostart_reason_in_init_file_qm,Qkb_save2,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_6 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qinit_file_command_line = STATIC_SYMBOL("INIT-FILE-COMMAND-LINE",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)32L),
	    FIX((SI_Long)9L));
    Qinit_file_command = STATIC_SYMBOL("INIT-FILE-COMMAND",AB_package);
    string_constant_3 = STATIC_STRING("Executing the command line: ~a");
    array_constant_8 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    Qrequested = STATIC_SYMBOL("REQUESTED",AB_package);
    Qstart_g2 = STATIC_SYMBOL("START-G2",AB_package);
    string_constant_4 = 
	    STATIC_STRING("Cannot execute `Start G2\' in the G2 Init file (\"~a\") ~\n                                    because G2 has already been started.");
    string_constant_5 = 
	    STATIC_STRING("Error in G2 Init file (\"~a\") while executing the ~\n                            command line: ~a~\n                            ~%~a~%Aborting execution of the G2 Init file.");
    Qautostart = STATIC_SYMBOL("AUTOSTART",AB_package);
    Qdo_not_autostart = STATIC_SYMBOL("DO-NOT-AUTOSTART",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    string_constant_6 = 
	    STATIC_STRING("Ignoring commands following the \"Start G2\" command ~\n                           in the G2 Init file.");
    Qdefault_g2_kb_pathname = STATIC_SYMBOL("DEFAULT-G2-KB-PATHNAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2_kb_pathname,Default_g2_kb_pathname);
    record_system_variable(Qdefault_g2_kb_pathname,Qpathnames,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    array_constant_9 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Qpathname_for_disabling_g2_kb_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2-KB-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2_kb_command_line,
	    Pathname_for_disabling_g2_kb_command_line);
    Qinitializer_for_pathname_for_disabling_g2_kb_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-KB-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2_kb_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2_kb_command_line,
	    NIL,FALSE,0,0));
    list_constant_15 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2_kb_command_line);
    record_system_variable(Qpathname_for_disabling_g2_kb_command_line,
	    Qpathnames,list_constant_15,Qnil,Qnil,Qnil,Qnil);
    array_constant_10 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_12,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)57344L);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qload_from_command_line = STATIC_SYMBOL("LOAD-FROM-COMMAND-LINE",
	    AB_package);
    Qcommand_line_argument = STATIC_SYMBOL("COMMAND-LINE-ARGUMENT",AB_package);
    Kenvironment_variable = STATIC_SYMBOL("ENVIRONMENT-VARIABLE",Pkeyword);
    string_constant_7 = 
	    STATIC_STRING("G2 could not find the file \"~a\", ~\n                            which was specified as an environment variable ~\n                            when G2 was launched.");
    Kcommand_line = STATIC_SYMBOL("COMMAND-LINE",Pkeyword);
    string_constant_8 = 
	    STATIC_STRING("G2 could not find the file \"~a\", ~\n                            which was specified in the command line that launched G2.");
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qparent = STATIC_SYMBOL("PARENT",AB_package);
    SET_SYMBOL_FUNCTION(Qparent,STATIC_FUNCTION(parent,NIL,FALSE,1,1));
    string_constant_9 = STATIC_STRING("and");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_10 = STATIC_STRING("~A, ~A ~A ~A");
    string_constant_11 = 
	    STATIC_STRING("This KB cannot be saved because of certain problems.  Generally");
    string_constant_12 = 
	    STATIC_STRING("such problems tend to go away if you reset G2 and/or delete");
    string_constant_13 = STATIC_STRING("certain transient items.  Note that");
    string_constant_14 = 
	    STATIC_STRING("resetting G2 deletes all transient items.");
    string_constant_15 = STATIC_STRING("~%~%The item~a ");
    string_constant_16 = STATIC_STRING("s");
    string_constant_17 = STATIC_STRING("");
    string_constant_18 = 
	    string_append2(STATIC_STRING(" cannot be saved, but ~a ~a represented by one or more tables that ~\n           must be saved.  Deleting such tables or deleting the above item~a ~\n           may make this KB"),
	    STATIC_STRING(" savable."));
    string_constant_19 = STATIC_STRING("they");
    string_constant_20 = STATIC_STRING("it");
    string_constant_21 = STATIC_STRING("are");
    string_constant_22 = STATIC_STRING("is");
    string_constant_23 = 
	    STATIC_STRING("~%~%Deleting the following transient item~a ~a make this KB savable: ");
    string_constant_24 = STATIC_STRING("will");
    string_constant_25 = STATIC_STRING("may");
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qcomputation_style = STATIC_SYMBOL("COMPUTATION-STYLE",AB_package);
    string_constant_26 = 
	    string_append2(STATIC_STRING("The modules in this KB are not consistent; you ~\n                        therefore cannot save individual modules.  ~\n                        NO PART OF THIS KB HAS BEEN SAVED"),
	    STATIC_STRING("!"));
    Qkb_not_consistently_modularized = 
	    STATIC_SYMBOL("KB-NOT-CONSISTENTLY-MODULARIZED",AB_package);
    Qkb_not_savable = STATIC_SYMBOL("KB-NOT-SAVABLE",AB_package);
    Qg2_not_authorized = STATIC_SYMBOL("G2-NOT-AUTHORIZED",AB_package);
    string_constant_27 = STATIC_STRING("Save is already in progress.");
    Qin_progress = STATIC_SYMBOL("IN-PROGRESS",AB_package);
    string_constant_28 = STATIC_STRING("WARNING: Saving did not complete. ~A");
    Qwildcards_in_filename = STATIC_SYMBOL("WILDCARDS-IN-FILENAME",AB_package);
}
