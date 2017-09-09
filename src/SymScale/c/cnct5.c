/* cnct5.c
 * Input file:  connect5.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct5.h"


DEFINE_VARIABLE_WITH_SYMBOL(Transient_connection_error_qm, Qtransient_connection_error_qm);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qnot_same_workspace;  /* not-same-workspace */

static Object Qnot_on_workspace;   /* not-on-workspace */

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qif_does_not_exist;  /* if-does-not-exist */

static Object Qoutput;             /* output */

static Object Qinput;              /* input */

static Object array_constant;      /* # */

/* MAKE-TRANSIENT-CONNECTION */
Object make_transient_connection(class_1,input_end_object_qm,
	    make_new_input_stub_qm,input_end_side_qm,
	    input_end_position_on_side_qm,input_end_portname_qm,
	    output_end_object_qm,make_new_output_stub_qm,
	    output_end_side_qm,output_end_position_on_side_qm,
	    output_end_portname_qm,connection_directional_qm,
	    connection_style_qm,connection_vertices_qm,report_errors_qm)
    Object class_1, input_end_object_qm, make_new_input_stub_qm;
    Object input_end_side_qm, input_end_position_on_side_qm;
    Object input_end_portname_qm, output_end_object_qm;
    Object make_new_output_stub_qm, output_end_side_qm;
    Object output_end_position_on_side_qm, output_end_portname_qm;
    Object connection_directional_qm, connection_style_qm;
    Object connection_vertices_qm, report_errors_qm;
{
    Object gensymed_symbol, input_workspace_qm, output_workspace_qm, x2;
    Object sub_class_bit_vector, temp_1, x, current_drawing_priority;
    Object region_invalidation_is_preferred, stub_length_to_use_qm;
    Object replaced_stub_qm, input_end_object_connection_qm;
    Object output_end_object_connection_qm, final_connection_qm;
    Object input_end_loose_end, output_end_loose_end, workspace;
    Object eval_pop_store, cons_1, next_cons, temp_2, svref_arg_2, loose_end;
    Object temp_3, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(102,0);
    if (input_end_object_qm && output_end_object_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	input_workspace_qm = gensymed_symbol;
	gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	output_workspace_qm = gensymed_symbol;
	if (SIMPLE_VECTOR_P(input_workspace_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_workspace_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(input_workspace_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(input_workspace_qm,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (SIMPLE_VECTOR_P(output_workspace_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_workspace_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(output_workspace_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(output_workspace_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? EQ(input_workspace_qm,output_workspace_qm) : TRUEP(Nil))
	    temp_1 = T;
	else {
	    if (report_errors_qm)
		Transient_connection_error_qm = 
			gensym_list_3(Qnot_same_workspace,
			input_end_object_qm,output_end_object_qm);
	    temp_1 = Nil;
	}
    }
    else if (input_end_object_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(input_end_object_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	x = gensymed_symbol;
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    temp_1 = T;
	else {
	    if (report_errors_qm)
		Transient_connection_error_qm = 
			gensym_list_2(Qnot_on_workspace,input_end_object_qm);
	    temp_1 = Nil;
	}
    }
    else if (output_end_object_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(output_end_object_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	x = gensymed_symbol;
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    temp_1 = T;
	else {
	    if (report_errors_qm)
		Transient_connection_error_qm = 
			gensym_list_2(Qnot_on_workspace,output_end_object_qm);
	    temp_1 = Nil;
	}
    }
    else
	temp_1 = Qnil;
    if (temp_1) {
	current_drawing_priority = T ? Kdraw_as_late_as_possible : 
		Current_drawing_priority;
	region_invalidation_is_preferred = T ? T : 
		Region_invalidation_is_preferred;
	PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		  1);
	    stub_length_to_use_qm = connection_vertices_qm ? 
		    FIX((SI_Long)0L) : Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Stub_length_to_use_qm,Qstub_length_to_use_qm,stub_length_to_use_qm,
		    0);
	      if (input_end_object_qm) {
		  replaced_stub_qm = EQ(make_new_input_stub_qm,Qnil) || 
			  EQ(make_new_input_stub_qm,Qif_does_not_exist) ? 
			  make_transient_stub_to_replace_existing_one(class_1,
			  input_end_object_qm,connection_directional_qm ? 
			  Qoutput : Nil,input_end_portname_qm,
			  input_end_side_qm,input_end_position_on_side_qm,
			  connection_style_qm,report_errors_qm ? 
			  (EQ(make_new_input_stub_qm,Qnil) ? T : Nil) : 
			  Qnil) : Nil;
		  if (replaced_stub_qm)
		      input_end_object_connection_qm = replaced_stub_qm;
		  else if (make_new_input_stub_qm)
		      input_end_object_connection_qm = 
			      make_new_transient_stub(class_1,
			      input_end_object_qm,
			      connection_directional_qm ? Qoutput : Nil,
			      input_end_portname_qm,input_end_side_qm,
			      input_end_position_on_side_qm,
			      connection_style_qm);
		  else
		      input_end_object_connection_qm = Qnil;
	      }
	      else
		  input_end_object_connection_qm = Nil;
	      if (output_end_object_qm) {
		  replaced_stub_qm = EQ(make_new_output_stub_qm,Qnil) || 
			  EQ(make_new_output_stub_qm,Qif_does_not_exist) ? 
			  make_transient_stub_to_replace_existing_one(class_1,
			  output_end_object_qm,connection_directional_qm ? 
			  Qinput : Nil,output_end_portname_qm,
			  output_end_side_qm,
			  output_end_position_on_side_qm,
			  connection_style_qm,report_errors_qm ? 
			  (EQ(make_new_output_stub_qm,Qnil) ? T : Nil) : 
			  Qnil) : Nil;
		  if (replaced_stub_qm)
		      output_end_object_connection_qm = replaced_stub_qm;
		  else if (make_new_output_stub_qm)
		      output_end_object_connection_qm = 
			      make_new_transient_stub(class_1,
			      output_end_object_qm,
			      connection_directional_qm ? Qinput : Nil,
			      output_end_portname_qm,output_end_side_qm,
			      output_end_position_on_side_qm,
			      connection_style_qm);
		  else
		      output_end_object_connection_qm = Qnil;
	      }
	      else
		  output_end_object_connection_qm = Nil;
	      final_connection_qm = Nil;
	      if (input_end_object_qm && output_end_object_qm) {
		  if (input_end_object_connection_qm && 
			  output_end_object_connection_qm) {
		      input_end_loose_end = 
			      get_block_at_other_end_of_connection(input_end_object_connection_qm,
			      input_end_object_qm);
		      output_end_loose_end = 
			      get_block_at_other_end_of_connection(output_end_object_connection_qm,
			      output_end_object_qm);
		      gensymed_symbol = 
			      ACCESS_ONCE(ISVREF(input_end_loose_end,
			      (SI_Long)14L));
		      gensymed_symbol = gensymed_symbol ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol,
			      (SI_Long)5L)) : Nil;
		      workspace = gensymed_symbol;
		      if (connection_vertices_qm && 
			      Called_within_clear_text_loading) {
			  if (SIMPLE_VECTOR_P(input_end_object_qm) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_end_object_qm)) 
				  > (SI_Long)2L &&  
				  !EQ(ISVREF(input_end_object_qm,
				  (SI_Long)1L),Qavailable_frame_vector)) {
			      x2 = ISVREF(input_end_object_qm,(SI_Long)1L);
			      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				      EQ(ISVREF(x2,(SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? x2 : Qnil;
			  }
			  else
			      gensymed_symbol = Nil;
			  if (gensymed_symbol) {
			      sub_class_bit_vector = 
				      ISVREF(gensymed_symbol,(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(Loose_end_class_description,
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
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp);
			  else {
			      if (SIMPLE_VECTOR_P(output_end_object_qm) && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_end_object_qm)) 
				      > (SI_Long)2L &&  
				      !EQ(ISVREF(output_end_object_qm,
				      (SI_Long)1L),Qavailable_frame_vector)) {
				  x2 = ISVREF(output_end_object_qm,
					  (SI_Long)1L);
				  gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					  EQ(ISVREF(x2,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  ? x2 : Qnil;
			      }
			      else
				  gensymed_symbol = Nil;
			      if (gensymed_symbol) {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(Loose_end_class_description,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
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
				      gensymed_symbol_2 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_3;
				      gensymed_symbol_1 = 
					      gensymed_symbol_1 & 
					      gensymed_symbol_2;
				      temp = (SI_Long)0L < gensymed_symbol_1;
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
		      if (temp) {
			  connection_vertices_qm = 
				  nreverse(connection_vertices_qm);
			  eval_pop_store = Nil;
			  cons_1 = connection_vertices_qm;
			  if (cons_1) {
			      eval_pop_store = M_CAR(cons_1);
			      next_cons = M_CDR(cons_1);
			      inline_note_reclaim_cons(cons_1,Qeval);
			      if (ISVREF(Available_eval_conses_tail_vector,
				      IFIX(Current_thread_index))) {
				  temp_2 = 
					  ISVREF(Available_eval_conses_tail_vector,
					  IFIX(Current_thread_index));
				  M_CDR(temp_2) = cons_1;
				  temp_2 = Available_eval_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_2,svref_arg_2) = cons_1;
			      }
			      else {
				  temp_2 = Available_eval_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_2,svref_arg_2) = cons_1;
				  temp_2 = Available_eval_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp_2,svref_arg_2) = cons_1;
			      }
			      M_CDR(cons_1) = Nil;
			  }
			  else
			      next_cons = Nil;
			  connection_vertices_qm = next_cons;
			  connection_vertices_qm = 
				  nreverse(connection_vertices_qm);
		      }
		      if (connection_vertices_qm)
			  install_vertices_in_connection(input_end_object_connection_qm,
				  input_end_loose_end,
				  connection_vertices_qm,
				  ISVREF(array_constant,
				  IFIX(ISVREF(input_end_object_connection_qm,
				  (SI_Long)5L)) & (SI_Long)3L),workspace);
		      if (connection_is_straight_qm(input_end_object_connection_qm)) 
				  {
			  update_connection_images(T,workspace,
				  input_end_object_connection_qm);
			  toggle_side_for_loose_end(input_end_loose_end,
				  input_end_object_connection_qm);
			  update_connection_images(Nil,workspace,
				  input_end_object_connection_qm);
		      }
		      if (connection_vertices_qm) {
			  update_connection_images(T,workspace,
				  input_end_object_connection_qm);
			  add_bend_to_connection_1(input_end_object_connection_qm,
				  input_end_loose_end);
			  add_bend_to_connection_1(input_end_object_connection_qm,
				  input_end_loose_end);
			  update_connection_images(Nil,workspace,
				  input_end_object_connection_qm);
		      }
		      join_two_connections(input_end_loose_end,
			      output_end_loose_end);
		      final_connection_qm = input_end_object_connection_qm;
		  }
	      }
	      else if (input_end_object_qm) {
		  if (input_end_object_connection_qm) {
		      final_connection_qm = input_end_object_connection_qm;
		      if (connection_vertices_qm) {
			  loose_end = 
				  get_block_at_other_end_of_connection(input_end_object_connection_qm,
				  input_end_object_qm);
			  temp_1 = final_connection_qm;
			  temp_3 = connection_vertices_qm;
			  temp_4 = ISVREF(array_constant,
				  IFIX(ISVREF(input_end_object_connection_qm,
				  (SI_Long)5L)) & (SI_Long)3L);
			  gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  install_vertices_in_connection(temp_1,loose_end,
				  temp_3,temp_4,gensymed_symbol);
		      }
		  }
	      }
	      else if (output_end_object_qm) {
		  if (output_end_object_connection_qm) {
		      final_connection_qm = output_end_object_connection_qm;
		      if (connection_vertices_qm) {
			  loose_end = 
				  get_block_at_other_end_of_connection(output_end_object_connection_qm,
				  output_end_object_qm);
			  temp_1 = final_connection_qm;
			  temp_3 = connection_vertices_qm;
			  temp_4 = ISVREF(array_constant,
				  IFIX(ISVREF(output_end_object_connection_qm,
				  (SI_Long)4L)) & (SI_Long)3L);
			  gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  install_vertices_in_connection(temp_1,loose_end,
				  temp_3,temp_4,gensymed_symbol);
		      }
		  }
	      }
	      if (final_connection_qm) {
		  reclaim_eval_list_1(connection_vertices_qm);
		  if (output_end_object_qm)
		      add_subworkspace_connection_post_if_appropriate(final_connection_qm,
			      output_end_object_qm);
		  if (input_end_object_qm)
		      add_subworkspace_connection_post_if_appropriate(final_connection_qm,
			      input_end_object_qm);
		  result = VALUES_1(ISVREF(final_connection_qm,(SI_Long)1L));
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* INSTALL-VERTICES-IN-CONNECTION */
Object install_vertices_in_connection(connection,loose_end,
	    connection_vertices,starting_side,workspace)
    Object connection, loose_end, connection_vertices, starting_side;
    Object workspace;
{
    Object delta_x, delta_y, objects_to_drag, connections_to_drag, delta;
    Object ab_loop_list_, orientation_horizontal_p, first_time_qm;
    Object ab_loop_iter_flag_;
    Declare_special(1);

    x_note_fn_call(102,1);
    update_connection_images(T,workspace,connection);
    toggle_side_for_loose_end(loose_end,connection);
    update_connection_images(Nil,workspace,connection);
    delta_x = Nil;
    delta_y = Nil;
    objects_to_drag = gensym_cons_1(loose_end,Nil);
    connections_to_drag = gensym_cons_1(connection,Nil);
    delta = Nil;
    ab_loop_list_ = connection_vertices;
    orientation_horizontal_p = memq_function(starting_side,list_constant);
    PUSH_SPECIAL_WITH_SYMBOL(Orientation_horizontal_p,Qorientation_horizontal_p,orientation_horizontal_p,
	    0);
      first_time_qm = T;
      ab_loop_iter_flag_ = T;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      delta = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_)) {
	  Orientation_horizontal_p =  !TRUEP(Orientation_horizontal_p) ? T 
		  : Nil;
	  first_time_qm = Nil;
      }
      if (Orientation_horizontal_p) {
	  delta_x = delta;
	  delta_y = FIX((SI_Long)0L);
      }
      else {
	  delta_x = FIX((SI_Long)0L);
	  delta_y = FIXNUM_NEGATE(delta);
      }
      shift_blocks_with_their_external_connections(6,objects_to_drag,
	      connections_to_drag,Nil,workspace,delta_x,delta_y);
      if ( !TRUEP(first_time_qm)) {
	  update_connection_images(T,workspace,connection);
	  add_bend_to_connection_1(connection,loose_end);
	  update_connection_images(Nil,workspace,connection);
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:
      update_connection_images(T,workspace,connection);
      delete_last_bend_from_connection_1(connection,loose_end);
      update_connection_images(Nil,workspace,connection);
      if (G2_has_v5_mode_windows_p)
	  send_ws_representations_connection_moved(connection);
      reclaim_gensym_list_1(objects_to_drag);
      reclaim_gensym_list_1(connections_to_drag);
    POP_SPECIAL();
    return VALUES_1(ISVREF(connection,(SI_Long)6L));
}

/* MAKE-NEW-TRANSIENT-STUB */
Object make_new_transient_stub(class_1,end_object,direction_qm,
	    end_portname_qm,end_side,end_position_on_side,connection_style_qm)
    Object class_1, end_object, direction_qm, end_portname_qm, end_side;
    Object end_position_on_side, connection_style_qm;
{
    Object new_connection, gensymed_symbol;

    x_note_fn_call(102,2);
    new_connection = add_stub(8,end_object,end_portname_qm,class_1,
	    direction_qm,end_side,end_position_on_side,T,connection_style_qm);
    decache_roles_for_entities_related_to_this_connection(new_connection);
    gensymed_symbol = ACCESS_ONCE(ISVREF(end_object,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    update_connection_images(Nil,gensymed_symbol,new_connection);
    return VALUES_1(new_connection);
}

DEFINE_VARIABLE_WITH_SYMBOL(Permit_transfer_of_permanent_items_p, Qpermit_transfer_of_permanent_items_p);

static Object Qnot_transient;      /* not-transient */

static Object Qbad_designation;    /* bad-designation */

/* MAKE-TRANSIENT-STUB-TO-REPLACE-EXISTING-ONE */
Object make_transient_stub_to_replace_existing_one(class_1,end_object,
	    direction_qm,end_portname_qm,end_side_qm,
	    end_position_on_side_qm,connection_style_qm,report_errors_qm)
    Object class_1, end_object, direction_qm, end_portname_qm, end_side_qm;
    Object end_position_on_side_qm, connection_style_qm, report_errors_qm;
{
    Object designated_connection_qm, portname_of_designated_connection_qm;
    Object position_of_designated_connection, side_of_designated_connection;
    Object position_on_side_of_designated_connection, stub_designation;
    Object line_pattern_qm, connection_arrows_qm, new_connection;
    Object gensymed_symbol;
    char temp;

    x_note_fn_call(102,3);
    designated_connection_qm = Nil;
    portname_of_designated_connection_qm = Nil;
    position_of_designated_connection = Nil;
    side_of_designated_connection = Nil;
    position_on_side_of_designated_connection = Nil;
    if (end_side_qm) {
	stub_designation = gensym_list_2(end_side_qm,end_position_on_side_qm);
	designated_connection_qm = 
		get_connection_given_stub_designation(end_object,
		stub_designation);
	reclaim_gensym_list_1(stub_designation);
	if (designated_connection_qm) {
	    if (end_portname_qm &&  !EQ(end_portname_qm,
		    get_port_name_given_block_and_connection(2,end_object,
		    designated_connection_qm)))
		temp = TRUEP(Nil);
	    else {
		portname_of_designated_connection_qm = end_portname_qm;
		side_of_designated_connection = end_side_qm;
		position_on_side_of_designated_connection = 
			end_position_on_side_qm;
		temp = TRUEP(T);
	    }
	}
	else
	    temp = TRUEP(Nil);
    }
    else {
	designated_connection_qm = 
		get_connection_given_stub_designation(end_object,
		end_portname_qm);
	if (designated_connection_qm) {
	    portname_of_designated_connection_qm = end_portname_qm;
	    position_of_designated_connection = 
		    get_position_at_this_end_of_connection(designated_connection_qm,
		    end_object);
	    side_of_designated_connection = ISVREF(array_constant,
		    IFIX(position_of_designated_connection) & (SI_Long)3L);
	    position_on_side_of_designated_connection = 
		    FIX(IFIX(position_of_designated_connection) >>  -  - 
		    (SI_Long)2L);
	    temp = TRUEP(T);
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(designated_connection_qm,
		(SI_Long)7L)) & (SI_Long)64L)) &&  
		!TRUEP(Permit_transfer_of_permanent_items_p)) {
	    if (report_errors_qm)
		Transient_connection_error_qm = 
			gensym_list_2(Qnot_transient,end_object);
	    return VALUES_1(Nil);
	}
	else {
	    line_pattern_qm = 
		    copy_for_slot_value(connection_line_pattern(designated_connection_qm));
	    connection_arrows_qm = 
		    copy_for_slot_value(connection_arrows_of_connection(designated_connection_qm));
	    delete_connection(2,designated_connection_qm,Nil);
	    new_connection = add_stub(10,end_object,
		    portname_of_designated_connection_qm,class_1,
		    direction_qm,side_of_designated_connection,
		    position_on_side_of_designated_connection,T,
		    connection_style_qm,line_pattern_qm,connection_arrows_qm);
	    decache_roles_for_entities_related_to_this_connection(new_connection);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(end_object,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    update_connection_images(Nil,gensymed_symbol,new_connection);
	    reclaim_slot_value(line_pattern_qm);
	    reclaim_slot_value(connection_arrows_qm);
	    return VALUES_1(new_connection);
	}
    }
    else {
	if (report_errors_qm)
	    Transient_connection_error_qm = gensym_list_2(Qbad_designation,
		    end_object);
	return VALUES_1(Nil);
    }
}

/* DELETE-ITEM */
Object delete_item(item)
    Object item;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(102,4);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	return delete_connection_leaving_stubs_if_appropriate(ISVREF(item,
		(SI_Long)21L));
    else
	return delete_frame(item);
}

/* DELETE-CONNECTION-LEAVING-STUBS-IF-APPROPRIATE */
Object delete_connection_leaving_stubs_if_appropriate(connection)
    Object connection;
{
    x_note_fn_call(102,5);
    if (Delete_connections_without_leaving_stubs_qm)
	return delete_connection(1,connection);
    else
	return delete_connection_to_stub(connection);
}

/* RECLAIM-BAD-CONNECTIONS-OF-BLOCKS */
Object reclaim_bad_connections_of_blocks(blocks,reference_fsn)
    Object blocks, reference_fsn;
{
    Object count_1, loose_ends, block, ab_loop_list_, gensymed_symbol, xa, ya;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, conn;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;
    Object ab_less_than_branch_qm_, connections, ab_loop_list__1, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object connection_item, gensymed_symbol_1, old, svref_new_value;
    Object sub_class_bit_vector, loose_end;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long gensymed_symbol_2, new_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(102,6);
    count_1 = FIX((SI_Long)0L);
    loose_ends = Nil;
    block = Nil;
    ab_loop_list_ = blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference_fsn,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(reference_fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	conn = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
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
	next_loop_1:
	next_loop_2:
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
		next_loop_3:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_1;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_3;
		end_loop_1:;
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
	  goto next_loop_2;
	end_loop_2:
	end_1:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  conn = ab_connection_;
	  ab_loopvar__2 = gensym_cons_1(conn,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_1;
	end_loop_3:
	  connections = ab_loopvar_;
	  goto end_2;
	  connections = Qnil;
	end_2:;
	POP_SPECIAL();
	conn = Nil;
	ab_loop_list__1 = connections;
      next_loop_4:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_4;
	conn = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	gensymed_symbol = ISVREF(conn,(SI_Long)10L);
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(reference_fsn))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference_fsn,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(reference_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(reference_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if (temp);
	else {
	    temp =  !TRUEP(ISVREF(conn,(SI_Long)1L));
	    if (temp);
	    else
		temp =  !TRUEP(ISVREF(conn,(SI_Long)2L));
	    if (temp);
	    else
		temp =  !TRUEP(ISVREF(conn,(SI_Long)3L));
	}
	if (temp) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    skip_list = CDR(gensymed_symbol);
	    key_value = conn;
	    key_hash_value = SXHASH_SYMBOL_1(conn) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_5:
	    if (level < ab_loop_bind_)
		goto end_loop_5;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_6:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_7:
	    if ( !TRUEP(marked))
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_7;
	  end_loop_6:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_6;
	  end_loop_7:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	    connection_item = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    gensymed_symbol = conn;
	    gensymed_symbol_1 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_1,(SI_Long)6L)) : Nil;
	    temp_1 = gensymed_symbol_1;
	    set_skip_list_entry(temp_1,FIX((SI_Long)7L),Qeq,Nil,T,
		    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),Nil);
	    temp_1 = conn;
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	    temp_2 = gensymed_symbol;
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,temp_2,
		    FIX((SI_Long)7L),FIX(SXHASH_SYMBOL_1(conn) & 
		    IFIX(Most_positive_fixnum)));
	    reclaim_connection_item_1(connection_item);
	    gensymed_symbol = ISVREF(conn,(SI_Long)10L);
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(reference_fsn))
		temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference_fsn,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(reference_fsn);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(reference_fsn),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp) {
		temp_1 = ISVREF(conn,(SI_Long)6L);
		if (CONSP(temp_1))
		    reclaim_slot_value_list_1(ISVREF(conn,(SI_Long)6L));
		temp = TRUEP(Noting_changes_to_kb_p);
		if (temp);
		else {
		    gensymed_symbol_2 = IFIX(ISVREF(conn,(SI_Long)7L)) & 
			    (SI_Long)128L;
		    temp =  !((SI_Long)0L != gensymed_symbol_2) ?  
			    !TRUEP(Geometric_change_to_connection_is_temporary_p) 
			    : TRUEP(Nil);
		}
		if (temp)
		    note_change_to_connection_1(conn);
		SVREF(conn,FIX((SI_Long)6L)) = Nil;
		reclaim_slot_value(ISVREF(conn,(SI_Long)9L));
		old = ISVREF(conn,(SI_Long)10L);
		new_1 = (SI_Long)-1L;
		svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
			(FIXNUMP(FIX(new_1)) ||  !TRUEP(FIX(new_1))) ? 
			FIX(new_1) : frame_serial_number_setf_helper_1(old,
			FIX(new_1));
		SVREF(conn,FIX((SI_Long)10L)) = svref_new_value;
		reclaim_connection_1(conn);
		count_1 = FIXNUM_ADD1(count_1);
	    }
	}
	goto next_loop_4;
      end_loop_4:;
	reclaim_gensym_list_1(connections);
	gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
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
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    loose_ends = gensym_cons_1(block,loose_ends);
    }
    goto next_loop;
  end_loop:;
    loose_end = Nil;
    ab_loop_list_ = loose_ends;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    loose_end = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(loose_end,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(loose_end) ? EQ(ISVREF(loose_end,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference_fsn,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(reference_fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp)
	delete_frame(loose_end);
    goto next_loop_8;
  end_loop_8:;
    reclaim_gensym_list_1(loose_ends);
    return VALUES_1(count_1);
}

static Object string_constant;     /* "Cleared ~d unattached connection~a." */

static Object string_constant_1;   /* "" */

static Object string_constant_2;   /* "s" */

static Object Qtruth_value;        /* truth-value */

/* G2-CLEAR-FLOATING-CONNECTION-STRUCTURES */
Object g2_clear_floating_connection_structures()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, gensymed_symbol, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, conn, ab_loop_it_, temp_1;
    Object ab_less_than_branch_qm_, blocks, reference_fsn, count_1;
    Object evaluation_value;
    char temp;
    Declare_special(2);

    x_note_fn_call(102,7);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
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
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
      if (gensymed_symbol) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
	  conn = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loop_it_ = Nil;
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
	  next_loop_2:
	  next_loop_3:
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
		  next_loop_4:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_4;
		  end_loop_2:;
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
	    goto next_loop_3;
	  end_loop_3:
	  end_1:
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_4;
	    conn = ab_connection_;
	    temp_1 =  !TRUEP(ISVREF(conn,(SI_Long)1L)) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(ISVREF(conn,(SI_Long)2L)) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(ISVREF(conn,(SI_Long)3L)) ? T : Nil;
	    ab_loop_it_ = temp_1;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_4:
	    temp = TRUEP(Qnil);
	  end_2:;
	  POP_SPECIAL();
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  ab_loopvar__4 = gensym_cons_1(block,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      blocks = ab_loopvar__2;
      goto end_3;
      blocks = Qnil;
    end_3:;
    POP_SPECIAL();
    reference_fsn = copy_frame_serial_number(Current_frame_serial_number);
    count_1 = reclaim_bad_connections_of_blocks(blocks,reference_fsn);
    notify_user_at_console_and_on_logbook(3,string_constant,count_1,
	    IFIX(count_1) == (SI_Long)1L ? string_constant_1 : 
	    string_constant_2);
    reclaim_gensym_list_1(blocks);
    reclaim_frame_serial_number(reference_fsn);
    evaluation_value = IFIX(count_1) > (SI_Long)0L ? Evaluation_true_value 
	    : Evaluation_false_value;
    if (EQ(evaluation_value,Evaluation_true_value) || EQ(evaluation_value,
	    Evaluation_false_value))
	return VALUES_1(evaluation_value);
    else
	return eval_cons_1(M_CAR(evaluation_value),Qtruth_value);
}

static Object Qtop;                /* top */

static Object Qleft;               /* left */

static Object Qbottom;             /* bottom */

static Object list_constant_1;     /* # */

static Object Qloose_end;          /* loose-end */

static Object Qright;              /* right */

static Object Qdestination;        /* destination */

static Object Qorigin;             /* origin */

static Object Qabsolute;           /* absolute */

static Object list_constant_2;     /* # */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qlookup;             /* lookup */

static Object Qconnection_item_table;  /* connection-item-table */

/* CONNECT-LOOSE-END-TO-BLOCK */
Object connect_loose_end_to_block varargs_1(int, n)
{
    Object origin_loose_end, destination_block, side, position_1;
    Object bend_distance_qm, where_to_bend_qm, scope_conses, ab_node_stack_;
    Object ab_current_node_, gensymed_symbol, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, c, temp;
    Object ab_less_than_branch_qm_, connection, origin_block_end_position;
    Object origin_side, bend_distance, bend_distance_from_input_end, side_1;
    Object block, output_side, delta_or_deltas, gensymed_symbol_3;
    Object slot_group_qm, connection_item_table_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp_2, temp_3, connection_item_table;
    Object tail_1, head_1, new_cons, svref_new_value, gensymed_symbol_4;
    Object connection_item;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, end_position;
    char temp_1, loose_end_is_input_end;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(102,8);
    INIT_ARGS_nonrelocating();
    origin_loose_end = REQUIRED_ARG_nonrelocating();
    destination_block = REQUIRED_ARG_nonrelocating();
    side = REQUIRED_ARG_nonrelocating();
    position_1 = REQUIRED_ARG_nonrelocating();
    bend_distance_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    where_to_bend_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(origin_loose_end,(SI_Long)14L));
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
    c = Nil;
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
      c = ab_connection_;
      connection = c;
      goto end_2;
      goto next_loop;
    end_loop_2:
      connection = Qnil;
    end_2:;
    POP_SPECIAL();
    if (EQ(side,Qtop))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(side,Qleft))
	gensymed_symbol_1 = (SI_Long)1L;
    else if (EQ(side,Qbottom))
	gensymed_symbol_1 = (SI_Long)2L;
    else
	gensymed_symbol_1 = (SI_Long)3L;
    gensymed_symbol_2 = IFIX(position_1) << (SI_Long)2L;
    end_position = gensymed_symbol_1 + gensymed_symbol_2;
    loose_end_is_input_end = EQ(origin_loose_end,ISVREF(connection,
	    (SI_Long)3L));
    origin_block_end_position = loose_end_is_input_end ? ISVREF(connection,
	    (SI_Long)4L) : ISVREF(connection,(SI_Long)5L);
    origin_side = ISVREF(array_constant,IFIX(origin_block_end_position) & 
	    (SI_Long)3L);
    bend_distance = bend_distance_qm;
    if (bend_distance);
    else
	bend_distance = Default_stub_length;
    if (EQ(memq_function(origin_side,list_constant_1) ? T : Nil,
	    memq_function(side,list_constant_1) ? T : Nil)) {
	if (EQ(where_to_bend_qm,Qloose_end)) {
	    if (loose_end_is_input_end) {
		if (EQ(side,Qleft)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qtop)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qright)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		if (EQ(origin_side,Qleft)) {
		    gensymed_symbol = ISVREF(origin_loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(origin_side,Qtop)) {
		    gensymed_symbol = ISVREF(origin_loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(origin_side,Qright)) {
		    gensymed_symbol = ISVREF(origin_loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(origin_loose_end,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		bend_distance_from_input_end = FIX(ABS(gensymed_symbol_1));
	    }
	    else
		bend_distance_from_input_end = bend_distance;
	}
	else if (EQ(where_to_bend_qm,Qnil) || EQ(where_to_bend_qm,
		Qdestination)) {
	    if (loose_end_is_input_end)
		bend_distance_from_input_end = bend_distance;
	    else {
		if (EQ(side,Qleft)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qtop)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qright)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		side_1 = origin_side;
		block = get_block_at_other_end_of_connection(connection,
			origin_loose_end);
		if (EQ(side_1,Qleft)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(side_1,Qtop)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(side_1,Qright)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		gensymed_symbol_1 = ABS(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(bend_distance);
		bend_distance_from_input_end = FIX(gensymed_symbol_1 - 
			gensymed_symbol_2);
	    }
	}
	else if (EQ(where_to_bend_qm,Qorigin)) {
	    if (loose_end_is_input_end) {
		if (EQ(side,Qleft)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qtop)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else if (EQ(side,Qright)) {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(destination_block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		}
		side_1 = origin_side;
		block = get_block_at_other_end_of_connection(connection,
			origin_loose_end);
		if (EQ(side_1,Qleft)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(side_1,Qtop)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else if (EQ(side_1,Qright)) {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		else {
		    gensymed_symbol = ISVREF(block,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol);
		}
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		gensymed_symbol_1 = ABS(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(bend_distance);
		bend_distance_from_input_end = FIX(gensymed_symbol_1 - 
			gensymed_symbol_2);
	    }
	    else
		bend_distance_from_input_end = bend_distance;
	}
	else if (EQ(where_to_bend_qm,Qabsolute))
	    bend_distance_from_input_end = bend_distance;
	else
	    bend_distance_from_input_end = Qnil;
    }
    else
	bend_distance_from_input_end = Nil;
    output_side = loose_end_is_input_end ? origin_side : side;
    delta_or_deltas = memq_function(output_side,list_constant_2) ? 
	    bend_distance_from_input_end : bend_distance_from_input_end ? 
	    FIXNUM_NEGATE(bend_distance_from_input_end) : Nil;
    temp_1 = TRUEP(Noting_changes_to_kb_p);
    if (temp_1);
    else {
	gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp_1)
	note_change_to_connection_1(connection);
    temp = delta_or_deltas;
    reclaim_slot_value(ISVREF(connection,(SI_Long)6L));
    SVREF(connection,FIX((SI_Long)6L)) = temp;
    if (loose_end_is_input_end) {
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)3L)) = destination_block;
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	ISVREF(connection,(SI_Long)5L) = FIX(end_position);
    }
    else {
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)2L)) = destination_block;
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	ISVREF(connection,(SI_Long)4L) = FIX(end_position);
    }
    gensymed_symbol = origin_loose_end;
    gensymed_symbol_3 = Nil;
    slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
    temp = Nil;
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(origin_loose_end,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
    connection_item_table_skip_list = gensymed_symbol_3;
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
      next_loop_3:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_3;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_3;
      end_loop_3:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = connection_item_table_skip_list;
	    temp_2 = Available_lookup_conses_tail_vector;
	    temp_3 = Current_thread_index;
	    SVREF(temp_2,temp_3) = last_1;
	}
	else {
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    SVREF(temp_2,temp_3) = connection_item_table_skip_list;
	    temp_2 = Available_lookup_conses_tail_vector;
	    temp_3 = Current_thread_index;
	    SVREF(temp_2,temp_3) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    gensymed_symbol_3 = temp;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)6L)) = gensymed_symbol_3;
    else if ( !EQ(gensymed_symbol_3,Qnil)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	temp_2 = make_icon_slot_group_1();
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
	temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
	SVREF(temp_2,FIX((SI_Long)6L)) = gensymed_symbol_3;
    }
    delete_frame(origin_loose_end);
    gensymed_symbol = ACCESS_ONCE(ISVREF(destination_block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    connection_item_table = gensymed_symbol;
    if (connection_item_table);
    else {
	gensymed_symbol = destination_block;
	gensymed_symbol_3 = Nil;
	slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(gensymed_symbol,Qslot_group_for_block_qm);
	tail_1 = 
		make_connection_item_table_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head_1 = 
		make_connection_item_table_skip_list_sentinel(Most_negative_fixnum,
		tail_1);
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,temp_3) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
	    }
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_3) = Qconnection_item_table;
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_2,temp_3) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
	    }
	    gensymed_symbol_4 = new_cons;
	}
	else
	    gensymed_symbol_4 = Nil;
	if ( !TRUEP(gensymed_symbol_4))
	    gensymed_symbol_4 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_4) = head_1;
	M_CDR(gensymed_symbol_4) = tail_1;
	inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
	M_CDR(gensymed_symbol_3) = gensymed_symbol_4;
	inline_note_allocate_cons(gensymed_symbol_3,Qlookup);
	if (slot_group_qm) {
	    temp_2 = gensymed_symbol_3;
	    SVREF(slot_group_qm,FIX((SI_Long)6L)) = temp_2;
	}
	else if ( !EQ(gensymed_symbol_3,Qnil)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(gensymed_symbol,
			Qslot_group_for_block_qm);
	    temp_2 = make_icon_slot_group_1();
	    SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp_2;
	    temp_2 = ISVREF(gensymed_symbol,(SI_Long)14L);
	    temp_3 = gensymed_symbol_3;
	    SVREF(temp_2,FIX((SI_Long)6L)) = temp_3;
	}
	connection_item_table = gensymed_symbol_3;
    }
    connection_item = make_connection_item_1(connection);
    gensymed_symbol = connection;
    set_skip_list_entry(connection_item_table,FIX((SI_Long)7L),Qeq,Nil,T,
	    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),connection_item);
    return VALUES_1(connection);
}

void connect5_INIT()
{
    Object gensymed_symbol;
    Object AB_package, Qg2_clear_floating_connection_structures;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(102,9);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnot_same_workspace = STATIC_SYMBOL("NOT-SAME-WORKSPACE",AB_package);
    Qnot_on_workspace = STATIC_SYMBOL("NOT-ON-WORKSPACE",AB_package);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qif_does_not_exist = STATIC_SYMBOL("IF-DOES-NOT-EXIST",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
    list_constant = STATIC_LIST((SI_Long)2L,Qleft,Qright);
    Qnot_transient = STATIC_SYMBOL("NOT-TRANSIENT",AB_package);
    Qbad_designation = STATIC_SYMBOL("BAD-DESIGNATION",AB_package);
    Qg2_clear_floating_connection_structures = 
	    STATIC_SYMBOL("G2-CLEAR-FLOATING-CONNECTION-STRUCTURES",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_clear_floating_connection_structures,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant = STATIC_STRING("Cleared ~d unattached connection~a.");
    string_constant_1 = STATIC_STRING("");
    string_constant_2 = STATIC_STRING("s");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_clear_floating_connection_structures,
	    STATIC_FUNCTION(g2_clear_floating_connection_structures,NIL,
	    FALSE,0,0));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qbottom,Qtop);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qdestination = STATIC_SYMBOL("DESTINATION",AB_package);
    Qorigin = STATIC_SYMBOL("ORIGIN",AB_package);
    Qabsolute = STATIC_SYMBOL("ABSOLUTE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qtop,Qleft);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
}
