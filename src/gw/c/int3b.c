/* int3b.c
 * Input file:  int3b.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int3b.h"


/* HANDLER-FOR-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object g2int_handler_for_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    x_note_fn_call(43,0);
    return g2int_enlarge_index_space(ISVREF(G2int_current_icp_port,
	    (SI_Long)8L),FIXNUM_SUB1(new_index_limit_plus_one));
}

static Object Qg2int_send_icp_enlarge_corresponding_icp_object_index_space;  /* send-icp-enlarge-corresponding-icp-object-index-space */

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* SEND-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object g2int_send_icp_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,1);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_enlarge_corresponding_icp_object_index_space;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)15L));
	  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	  g2int_write_icp_unsigned_integer(new_index_limit_plus_one);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_enlarge_corresponding_icp_object_index_space,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_enlarge_corresponding_icp_object_index_space,
			top,Nil);
		goto end_send_icp_enlarge_corresponding_icp_object_index_space;
	    }
	}
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	new_index_limit_plus_one = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : new_index_limit_plus_one;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_enlarge_corresponding_icp_object_index_space;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)15L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(new_index_limit_plus_one))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(new_index_limit_plus_one);
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(Qg2int_send_icp_enlarge_corresponding_icp_object_index_space);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_enlarge_corresponding_icp_object_index_space;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_enlarge_corresponding_icp_object_index_space:
    return result;
}

/* HANDLE-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE--BODY */
Object g2int_handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    x_note_fn_call(43,2);
    g2int_handler_for_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space;  /* handle-icp-enlarge-corresponding-icp-object-index-space */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object g2int_handle_icp_enlarge_corresponding_icp_object_index_space()
{
    Object index_1, index_space, name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,3);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    name_of_corresponding_icp_object_index_space = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    name_of_corresponding_icp_object_index_space = Nil;
	new_index_limit_plus_one = g2int_read_icp_unsigned_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
		  new_index_limit_plus_one);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		name_of_corresponding_icp_object_index_space = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		name_of_corresponding_icp_object_index_space = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    new_index_limit_plus_one = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
		g2int_resumable_icp_push(Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space);
		return VALUES_1(G2int_icp_suspend);
	    }
	    new_index_limit_plus_one = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
		  new_index_limit_plus_one);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_icp_port_for_reclaim = UNBOUND;

Object G2int_deregister_and_register_item_p = UNBOUND;

Object G2int_deregister_but_do_not_remove_from_table_p = UNBOUND;

/* NOTE-NO-OBJECT-IN-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_note_no_object_in_deregister_corresponding_icp_object(icp_object,
	    index_1,original_index_space_name,icp_port,localp)
    Object icp_object, index_1, original_index_space_name, icp_port, localp;
{
    x_note_fn_call(43,4);
    return VALUES_1(Nil);
}

static Object Qg2int_output;       /* output */

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_item_index_space;  /* item-index-space */

static Object Qg2int_frame_serial_number;  /* frame-serial-number */

static Object Qg2int_gsi_instance;  /* gsi-instance */

static Object Qg2int_registered_item;  /* registered-item */

/* DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_deregister_corresponding_icp_object(icp_object_qm,index_1,
	    original_index_space_name,icp_port,localp)
    Object icp_object_qm, index_1, original_index_space_name, icp_port, localp;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object index_space_icp_object_qm, vector_1, icp_object_type_qm;
    Object icp_port_for_reclaim, old_entry, svref_arg_1;
    Object items_registered_with_handle, item, ab_loop_list_, icp_output_port;
    SI_Long gensymed_symbol, temp_2, gensymed_symbol_3, index_2, svref_arg_2;
    char outputp;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,5);
    outputp = EQ(Qg2int_output,ISVREF(icp_port,(SI_Long)3L));
    port = icp_port;
    if (EQ(original_index_space_name,Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(original_index_space_name,Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(original_index_space_name,Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	gensymed_symbol_1 = CDR(temp_1);
	gensymed_symbol_2 = index_1;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		index_space_icp_object_qm = M_CDR(M_CAR(gensymed_symbol_1));
		goto end;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    index_space_icp_object_qm = Qnil;
	  end:;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	index_space_icp_object_qm = Qnil;
      end_1:;
    }
    else {
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
	index_2 = IFIX(index_1) & (SI_Long)1023L;
	index_space_icp_object_qm = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
    }
    if (icp_object_qm &&  !EQ(icp_object_qm,index_space_icp_object_qm))
	g2int_note_no_object_in_deregister_corresponding_icp_object(icp_object_qm,
		index_1,original_index_space_name,icp_port,localp);
    if ( !TRUEP(icp_object_qm))
	icp_object_qm = index_space_icp_object_qm;
    if ( !TRUEP(icp_object_qm))
	return VALUES_1(Nil);
    icp_object_type_qm = 
	    g2int_icp_object_type_given_icp_object(icp_object_qm,
	    index_space_name);
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	icp_port_for_reclaim = icp_port;
	PUSH_SPECIAL(G2int_icp_port_for_reclaim,icp_port_for_reclaim,0);
	  if ( !TRUEP(G2int_deregister_but_do_not_remove_from_table_p)) {
	      gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	      temp_2 = gensymed_symbol % (SI_Long)67L;
	      result = g2int_delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		      index_1,SVREF(index_space,FIX(temp_2)),
		      FIX(gensymed_symbol));
	      old_entry = NTH_VALUE((SI_Long)1L, result);
	      g2int_note_item_deleted_from_frame_serial_number_table(old_entry);
	  }
	POP_SPECIAL();
    }
    else {
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    g2int_enlarge_index_space(index_space,index_1);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) 
		>>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
	g2int_remove_icp_port_entries_from_icp_object_1(icp_object_qm,
		icp_object_type_qm,icp_port,original_index_space_name,Nil);
	if (outputp &&  !TRUEP(localp))
	    g2int_deassign_index_in_index_space(index_1,index_space);
    }
    if ( !outputp) {
	if (EQ(Qg2int_gsi_instance,icp_object_type_qm) || 
		EQ(Qg2int_registered_item,icp_object_type_qm)) {
	    items_registered_with_handle = 
		    g2int_items_registered_with_handle_on_port(index_1,
		    icp_port);
	    if (items_registered_with_handle) {
		item = Nil;
		ab_loop_list_ = items_registered_with_handle;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		item = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		g2int_reclaim_icp_port_entry_for_gsi_instance(item,icp_port);
		goto next_loop_2;
	      end_loop_2:;
		g2int_reclaim_gensym_list_1(items_registered_with_handle);
		g2int_clear_items_registered_with_handle_on_port(index_1,
			icp_port);
	    }
	}
    }
    if ( !TRUEP(localp) &&  !outputp &&  
	    !TRUEP(G2int_deregister_and_register_item_p) && 
	    EQ(index_space_name,Qg2int_item_index_space)) {
	icp_output_port = ISVREF(ISVREF(icp_port,(SI_Long)2L),(SI_Long)4L);
	if (g2int_send_reclaim_index_space_message_p(icp_output_port,T,
		index_space_name))
	    g2int_enqueue_reclaim_index_space_message(icp_output_port,
		    index_1,original_index_space_name,T,T,Nil,Nil);
    }
    return VALUES_4(icp_object_qm,icp_object_type_qm,index_space_name,
	    outputp ? T : Nil);
}

static Object Qg2int_reclaimer_for_icp_object;  /* reclaimer-for-icp-object */

/* HANDLE-DELETE-CORRESPONDING-ICP-OBJECT */
Object g2int_handle_delete_corresponding_icp_object(index_1,
	    index_space_name,icp_port)
    Object index_1, index_space_name, icp_port;
{
    Object icp_object_qm, icp_object_type_qm, reclaimer_for_icp_object_qm;
    Object result;

    x_note_fn_call(43,6);
    result = g2int_deregister_corresponding_icp_object(Nil,index_1,
	    index_space_name,icp_port,Nil);
    MVS_2(result,icp_object_qm,icp_object_type_qm);
    if (icp_object_qm) {
	if (icp_object_type_qm) {
	    reclaimer_for_icp_object_qm = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type_qm),
		    Qg2int_reclaimer_for_icp_object);
	    if (reclaimer_for_icp_object_qm)
		inline_funcall_1(reclaimer_for_icp_object_qm,icp_object_qm);
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name;  /* write-icp-deregister-corresponding-icp-object-index-space-name */

/* WRITE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME */
Object g2int_write_icp_deregister_corresponding_icp_object_index_space_name(deregister_corresponding_icp_object_index_space_name)
    Object deregister_corresponding_icp_object_index_space_name;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,7);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)10L ? 
		g2int_write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name,
			top,Nil);
	}
	deregister_corresponding_icp_object_index_space_name = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		deregister_corresponding_icp_object_index_space_name;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)10L) {
	    value = 
		    g2int_write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(deregister_corresponding_icp_object_index_space_name);
		g2int_resumable_icp_push(Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name;  /* read-icp-deregister-corresponding-icp-object-index-space-name */

/* READ-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME */
Object g2int_read_icp_deregister_corresponding_icp_object_index_space_name()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,8);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)10L ? g2int_read_icp_symbol_as_value_type() : 
		Qg2int_standard_icp_object_index_space;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)10L) {
	    value = g2int_read_icp_symbol_as_value_type();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Qg2int_standard_icp_object_index_space;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_deregister_corresponding_icp_object;  /* send-icp-deregister-corresponding-icp-object */

/* SEND-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_send_icp_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,9);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_deregister_corresponding_icp_object;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)323L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_deregister_corresponding_icp_object,
			top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_deregister_corresponding_icp_object,
			top,Nil);
		goto end_send_icp_deregister_corresponding_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_deregister_corresponding_icp_object;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)323L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_deregister_corresponding_icp_object);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_deregister_corresponding_icp_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_deregister_corresponding_icp_object:
    return result;
}

/* HANDLE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT--BODY */
Object g2int_handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(43,10);
    g2int_deregister_corresponding_icp_object(Nil,
	    corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,
	    G2int_current_icp_port,Nil);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_deregister_corresponding_icp_object;  /* handle-icp-deregister-corresponding-icp-object */

/* HANDLE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_handle_icp_deregister_corresponding_icp_object()
{
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,11);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	name_of_corresponding_icp_object_index_space = 
		g2int_read_icp_deregister_corresponding_icp_object_index_space_name();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_deregister_corresponding_icp_object,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_deregister_corresponding_icp_object,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    value = 
		    g2int_read_icp_deregister_corresponding_icp_object_index_space_name();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    name_of_corresponding_icp_object_index_space = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_deregister_original_icp_object;  /* send-icp-deregister-original-icp-object */

/* SEND-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT */
Object g2int_send_icp_deregister_original_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,12);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_deregister_original_icp_object;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)324L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_deregister_original_icp_object,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_deregister_original_icp_object,top,
			Nil);
		goto end_send_icp_deregister_original_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_deregister_original_icp_object;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)324L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_deregister_original_icp_object);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_deregister_original_icp_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_deregister_original_icp_object:
    return result;
}

/* HANDLE-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT--BODY */
Object g2int_handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(43,13);
    g2int_deregister_corresponding_icp_object(Nil,
	    corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,
	    ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),(SI_Long)4L),
	    Nil);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_deregister_original_icp_object;  /* handle-icp-deregister-original-icp-object */

/* HANDLE-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT */
Object g2int_handle_icp_deregister_original_icp_object()
{
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,14);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	name_of_corresponding_icp_object_index_space = 
		g2int_read_icp_symbol_as_value_type();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_deregister_original_icp_object,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_deregister_original_icp_object,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_original_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_symbol_as_value_type();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_original_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    name_of_corresponding_icp_object_index_space = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_delete_icp_object_for_process;  /* send-icp-delete-icp-object-for-process */

/* SEND-ICP-DELETE-ICP-OBJECT-FOR-PROCESS */
Object g2int_send_icp_delete_icp_object_for_process(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,15);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_delete_icp_object_for_process;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)163L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_delete_icp_object_for_process,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_delete_icp_object_for_process,top,Nil);
		goto end_send_icp_delete_icp_object_for_process;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_delete_icp_object_for_process;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)163L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_delete_icp_object_for_process);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_delete_icp_object_for_process;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_delete_icp_object_for_process:
    return result;
}

/* HANDLE-ICP-DELETE-ICP-OBJECT-FOR-PROCESS--BODY */
Object g2int_handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(43,16);
    g2int_handle_delete_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,
	    G2int_current_icp_port);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_delete_icp_object_for_process;  /* handle-icp-delete-icp-object-for-process */

/* HANDLE-ICP-DELETE-ICP-OBJECT-FOR-PROCESS */
Object g2int_handle_icp_delete_icp_object_for_process()
{
    Object corresponding_icp_object_index, index_1, index_space;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,17);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    name_of_corresponding_icp_object_index_space = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    name_of_corresponding_icp_object_index_space = Nil;
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_delete_icp_object_for_process,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_delete_icp_object_for_process,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_delete_icp_object_for_process);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_delete_icp_object_for_process);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		name_of_corresponding_icp_object_index_space = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		name_of_corresponding_icp_object_index_space = Nil;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* HANDLE-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object icp_port, port, index_space_name, icp_socket, temp, temp_1;
    Object index_space;

    x_note_fn_call(43,18);
    icp_port = ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),(SI_Long)4L);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    g2int_deassign_index_in_index_space(corresponding_icp_object_index,
	    index_space);
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object;  /* send-icp-acknowledge-deregister-corresponding-icp-object */

/* SEND-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_send_icp_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,19);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)325L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object,
			top,Nil);
		goto end_send_icp_acknowledge_deregister_corresponding_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)325L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_acknowledge_deregister_corresponding_icp_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_acknowledge_deregister_corresponding_icp_object:
    return result;
}

/* HANDLE-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT--BODY */
Object g2int_handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(43,20);
    g2int_handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object;  /* handle-icp-acknowledge-deregister-corresponding-icp-object */

/* HANDLE-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_handle_icp_acknowledge_deregister_corresponding_icp_object()
{
    Object corresponding_icp_object_index, index_1, index_space;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,21);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    name_of_corresponding_icp_object_index_space = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    name_of_corresponding_icp_object_index_space = Nil;
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		name_of_corresponding_icp_object_index_space = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		name_of_corresponding_icp_object_index_space = Nil;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_deregister_corresponding_icp_object;  /* deregister-corresponding-icp-object */

static Object Qg2int_deregister_corresponding_icp_object_with_deassign;  /* deregister-corresponding-icp-object-with-deassign */

static Object Qg2int_deregister_original_icp_object;  /* deregister-original-icp-object */

static Object Qg2int_delete_icp_object_for_process;  /* delete-icp-object-for-process */

static Object Qg2int_delete_icp_object_for_process_with_deassign;  /* delete-icp-object-for-process-with-deassign */

static Object Qg2int_acknowledge_deregister_corresponding_icp_object;  /* acknowledge-deregister-corresponding-icp-object */

static Object Qg2int_deregister_and_register_corresponding_icp_object;  /* deregister-and-register-corresponding-icp-object */

static Object Qg2int_write_icp_deregister_icp_objects_operation;  /* write-icp-deregister-icp-objects-operation */

/* WRITE-ICP-DEREGISTER-ICP-OBJECTS-OPERATION */
Object g2int_write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation)
    Object deregister_icp_objects_operation;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,22);
    if (G2int_disable_resumability) {
	if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_corresponding_icp_object))
	    temp = FIX((SI_Long)0L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_corresponding_icp_object_with_deassign))
	    temp = FIX((SI_Long)0L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_original_icp_object))
	    temp = FIX((SI_Long)1L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_delete_icp_object_for_process))
	    temp = FIX((SI_Long)2L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_delete_icp_object_for_process_with_deassign))
	    temp = FIX((SI_Long)2L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_acknowledge_deregister_corresponding_icp_object))
	    temp = FIX((SI_Long)3L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_and_register_corresponding_icp_object))
	    temp = FIX((SI_Long)4L);
	else
	    temp = Qnil;
	temp = g2int_write_icp_byte(temp);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_deregister_icp_objects_operation,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_deregister_icp_objects_operation,
			top,Nil);
	}
	deregister_icp_objects_operation = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : deregister_icp_objects_operation;
	if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_corresponding_icp_object))
	    temp = FIX((SI_Long)0L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_corresponding_icp_object_with_deassign))
	    temp = FIX((SI_Long)0L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_original_icp_object))
	    temp = FIX((SI_Long)1L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_delete_icp_object_for_process))
	    temp = FIX((SI_Long)2L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_delete_icp_object_for_process_with_deassign))
	    temp = FIX((SI_Long)2L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_acknowledge_deregister_corresponding_icp_object))
	    temp = FIX((SI_Long)3L);
	else if (EQ(deregister_icp_objects_operation,
		Qg2int_deregister_and_register_corresponding_icp_object))
	    temp = FIX((SI_Long)4L);
	else
	    temp = Qnil;
	value = g2int_write_icp_byte(temp);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(deregister_icp_objects_operation);
	    g2int_resumable_icp_push(Qg2int_write_icp_deregister_icp_objects_operation);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_deregister_icp_objects_operation;  /* read-icp-deregister-icp-objects-operation */

/* READ-ICP-DEREGISTER-ICP-OBJECTS-OPERATION */
Object g2int_read_icp_deregister_icp_objects_operation()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, key, value;

    x_note_fn_call(43,23);
    if (G2int_disable_resumability) {
	temp = g2int_read_icp_byte();
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		temp = Qg2int_deregister_corresponding_icp_object;
		break;
	      case 1:
		temp = Qg2int_deregister_original_icp_object;
		break;
	      case 2:
		temp = Qg2int_delete_icp_object_for_process;
		break;
	      case 3:
		temp = Qg2int_acknowledge_deregister_corresponding_icp_object;
		break;
	      case 4:
		temp = Qg2int_deregister_and_register_corresponding_icp_object;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_deregister_icp_objects_operation,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_deregister_icp_objects_operation,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    key = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_deregister_icp_objects_operation);
		return VALUES_1(G2int_icp_suspend);
	    }
	    key = value;
	}
	if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		FIXNUM_LE(key,FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(key)) {
	      case 0:
		temp = Qg2int_deregister_corresponding_icp_object;
		break;
	      case 1:
		temp = Qg2int_deregister_original_icp_object;
		break;
	      case 2:
		temp = Qg2int_delete_icp_object_for_process;
		break;
	      case 3:
		temp = Qg2int_acknowledge_deregister_corresponding_icp_object;
		break;
	      case 4:
		temp = Qg2int_deregister_and_register_corresponding_icp_object;
		break;
	      default:
		temp = Nil;
		break;
	    }
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_corresponding_icp_object_index_list;  /* write-icp-corresponding-icp-object-index-list */

/* WRITE-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST */
Object g2int_write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list)
    Object corresponding_icp_object_index_list;
{
    Object index_1, ab_loop_list_, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, v1, v2, v3;
    Object result;

    x_note_fn_call(43,24);
    if (G2int_disable_resumability) {
	g2int_write_icp_byte(length(corresponding_icp_object_index_list));
	index_1 = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	index_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_unsigned_integer(index_1);
	goto next_loop;
      end_loop:
	temp = Qnil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_corresponding_icp_object_index_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_corresponding_icp_object_index_list,
			top,Nil);
	}
	corresponding_icp_object_index_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		corresponding_icp_object_index_list;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_byte(length(corresponding_icp_object_index_list)))) 
		    {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	index_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		corresponding_icp_object_index_list;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	index_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(index_1))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(index_1);
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(corresponding_icp_object_index_list);
	    g2int_resumable_icp_push(Qg2int_write_icp_corresponding_icp_object_index_list);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_corresponding_icp_object_index_list;  /* read-icp-corresponding-icp-object-index-list */

/* READ-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST */
Object g2int_read_icp_corresponding_icp_object_index_list()
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(43,25);
    if (G2int_disable_resumability) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(g2int_read_icp_byte());
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_read_icp_unsigned_integer(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end;
	temp = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_corresponding_icp_object_index_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_corresponding_icp_object_index_list,
			top,Nil);
	}
	i = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    ab_loop_bind_ = IFIX(g2int_resumable_icp_pop());
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(FIX(i));
		g2int_resumable_icp_push(Qg2int_read_icp_corresponding_icp_object_index_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    ab_loop_bind_ = IFIX(value);
	}
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(i));
		g2int_resumable_icp_push(Qg2int_read_icp_corresponding_icp_object_index_list);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg1 = value;
	}
	arg2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_deregister_icp_objects;  /* send-icp-deregister-icp-objects */

/* SEND-ICP-DEREGISTER-ICP-OBJECTS */
Object g2int_send_icp_deregister_icp_objects(name_of_corresponding_icp_object_index_space,
	    deregister_icp_objects_operation,
	    corresponding_icp_object_index_list)
    Object name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,26);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_deregister_icp_objects;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)326L));
	  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	  g2int_write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation);
	  g2int_write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_deregister_icp_objects,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_deregister_icp_objects,top,Nil);
		goto end_send_icp_deregister_icp_objects;
	    }
	}
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	deregister_icp_objects_operation = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : deregister_icp_objects_operation;
	corresponding_icp_object_index_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		corresponding_icp_object_index_list;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_deregister_icp_objects;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)326L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(corresponding_icp_object_index_list);
	      g2int_resumable_icp_push(deregister_icp_objects_operation);
	      g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      g2int_resumable_icp_push(Qg2int_send_icp_deregister_icp_objects);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_deregister_icp_objects;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_deregister_icp_objects:
    return result;
}

/* HANDLE-ICP-DEREGISTER-ICP-OBJECTS--BODY */
Object g2int_handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
	    deregister_icp_objects_operation,
	    corresponding_icp_object_index_list)
    Object name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list;
{
    Object corresponding_icp_object_index, ab_loop_list_;
    Object deregister_and_register_item_p;
    Declare_special(1);

    x_note_fn_call(43,27);
    if (EQ(deregister_icp_objects_operation,
	    Qg2int_deregister_corresponding_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_deregister_corresponding_icp_object(Nil,
		corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,
		G2int_current_icp_port,Nil);
	goto next_loop;
      end_loop:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qg2int_deregister_and_register_corresponding_icp_object)) {
	deregister_and_register_item_p = T;
	PUSH_SPECIAL(G2int_deregister_and_register_item_p,deregister_and_register_item_p,
		0);
	  corresponding_icp_object_index = Nil;
	  ab_loop_list_ = corresponding_icp_object_index_list;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  corresponding_icp_object_index = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  g2int_deregister_corresponding_icp_object(Nil,
		  corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space,
		  G2int_current_icp_port,Nil);
	  goto next_loop_1;
	end_loop_1:;
	POP_SPECIAL();
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qg2int_deregister_original_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_deregister_corresponding_icp_object(Nil,
		corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,
		ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),
		(SI_Long)4L),Nil);
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qg2int_delete_icp_object_for_process)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_handle_delete_corresponding_icp_object(corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,
		G2int_current_icp_port);
	goto next_loop_3;
      end_loop_3:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qg2int_acknowledge_deregister_corresponding_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space);
	goto next_loop_4;
      end_loop_4:;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_deregister_icp_objects;  /* handle-icp-deregister-icp-objects */

/* HANDLE-ICP-DEREGISTER-ICP-OBJECTS */
Object g2int_handle_icp_deregister_icp_objects()
{
    Object index_1, index_space, name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,28);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    name_of_corresponding_icp_object_index_space = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    name_of_corresponding_icp_object_index_space = Nil;
	deregister_icp_objects_operation = 
		g2int_read_icp_deregister_icp_objects_operation();
	corresponding_icp_object_index_list = 
		g2int_read_icp_corresponding_icp_object_index_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
		  deregister_icp_objects_operation,
		  corresponding_icp_object_index_list);
	POP_SPECIAL();
	g2int_reclaim_gensym_list_1(corresponding_icp_object_index_list);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_deregister_icp_objects,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_deregister_icp_objects,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_corresponding_icp_object_index_space = 
		    g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_deregister_icp_objects);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		name_of_corresponding_icp_object_index_space = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		name_of_corresponding_icp_object_index_space = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    deregister_icp_objects_operation = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_deregister_icp_objects_operation();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_icp_objects);
		return VALUES_1(G2int_icp_suspend);
	    }
	    deregister_icp_objects_operation = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_corresponding_icp_object_index_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(deregister_icp_objects_operation);
		g2int_resumable_icp_push(name_of_corresponding_icp_object_index_space);
		g2int_resumable_icp_push(Qg2int_handle_icp_deregister_icp_objects);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
		  deregister_icp_objects_operation,
		  corresponding_icp_object_index_list);
	POP_SPECIAL();
	g2int_reclaim_gensym_list_1(corresponding_icp_object_index_list);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_nop;  /* send-icp-nop */

/* SEND-ICP-NOP */
Object g2int_send_icp_nop(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,29);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_nop;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)16L));
	  g2int_write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_nop,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_nop,top,Nil);
		goto end_send_icp_nop;
	    }
	}
	number_of_icp_bytes_of_fill = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : number_of_icp_bytes_of_fill;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_nop;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)16L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(number_of_icp_bytes_of_fill);
	      g2int_resumable_icp_push(Qg2int_send_icp_nop);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_nop;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_nop:
    return result;
}

/* HANDLE-ICP-NOP--BODY */
Object g2int_handle_icp_nop__body(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    x_note_fn_call(43,30);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_nop;  /* handle-icp-nop */

/* HANDLE-ICP-NOP */
Object g2int_handle_icp_nop()
{
    Object number_of_icp_bytes_of_fill, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,31);
    if (G2int_disable_resumability) {
	number_of_icp_bytes_of_fill = 
		g2int_read_icp_number_of_icp_bytes_of_fill();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_nop__body(number_of_icp_bytes_of_fill);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_nop,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_nop,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    number_of_icp_bytes_of_fill = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_number_of_icp_bytes_of_fill();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_nop);
		return VALUES_1(G2int_icp_suspend);
	    }
	    number_of_icp_bytes_of_fill = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_nop__body(number_of_icp_bytes_of_fill);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_gsi_application_name = UNBOUND;

Object G2int_tcp_listener_port_number = UNBOUND;

Object G2int_name_for_local_home = UNBOUND;

Object G2int_icp_version_info_alist = UNBOUND;

Object G2int_icp_protocol_version = UNBOUND;

Object G2int_icp_acknowledge_version_info_alist = UNBOUND;

/* GET-ICP-VERSION-INFO-VALUE */
Object g2int_get_icp_version_info_value(info,symbol,default_1)
    Object info, symbol, default_1;
{
    Object temp;

    x_note_fn_call(43,32);
    temp = assoc_eql(symbol,info);
    temp = CDR(temp);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(default_1);
}

/* GET-REMOTE-ICP-VERSION-INFO-VALUE */
Object g2int_get_remote_icp_version_info_value(icp_socket,symbol,default_1)
    Object icp_socket, symbol, default_1;
{
    x_note_fn_call(43,33);
    return g2int_get_icp_version_info_value(ISVREF(icp_socket,
	    (SI_Long)19L),symbol,default_1);
}

/* RECONSTRUCT-G2-TIME-AT-START */
Object g2int_reconstruct_g2_time_at_start(text_string)
    Object text_string;
{
    x_note_fn_call(43,34);
    return g2int_reconstruct_managed_float(FIX(UBYTE_16_ISAREF_1(text_string,
	    (SI_Long)0L)),FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)1L)),
	    FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)2L)),
	    FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)3L)));
}

static Object Qg2int_g2_time_at_start;  /* g2-time-at-start */

static Object Qg2int_g2_time_at_start_as_text_string;  /* g2-time-at-start-as-text-string */

/* GET-REMOTE-G2-TIME-AT-START */
Object g2int_get_remote_g2_time_at_start(icp_socket)
    Object icp_socket;
{
    Object version_info, temp, text_string_qm, managed_float;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(43,35);
    version_info = ISVREF(icp_socket,(SI_Long)19L);
    temp = g2int_get_icp_version_info_value(version_info,
	    Qg2int_g2_time_at_start,Nil);
    if (temp)
	return VALUES_1(temp);
    else {
	text_string_qm = g2int_get_icp_version_info_value(version_info,
		Qg2int_g2_time_at_start_as_text_string,Nil);
	if (text_string_qm) {
	    managed_float = g2int_reconstruct_g2_time_at_start(text_string_qm);
	    gensym_push_modify_macro_arg = 
		    g2int_gensym_cons_1(Qg2int_g2_time_at_start,managed_float);
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = ISVREF(icp_socket,(SI_Long)19L);
	    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
	    return VALUES_1(managed_float);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qg2int_local_host_name;  /* local-host-name */

/* GET-REMOTE-HOST-NAME */
Object g2int_get_remote_host_name(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,36);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_local_host_name,Nil);
}

static Object Qg2int_tcp_listener_port_number;  /* tcp-listener-port-number */

/* GET-REMOTE-LISTENER-PORT */
Object g2int_get_remote_listener_port(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,37);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_tcp_listener_port_number,FIX((SI_Long)0L));
}

static Object Qg2int_name_for_local_home;  /* name-for-local-home */

/* GET-REMOTE-HOME-NAME */
Object g2int_get_remote_home_name(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,38);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_name_for_local_home,Nil);
}

Object G2int_cached_local_icp_version_info = UNBOUND;

static Object Qg2int_gensym_string;  /* gensym-string */

static Object Qg2int_wide_string;  /* wide-string */

/* COMPUTE-LOCAL-ICP-VERSION-INFO */
Object g2int_compute_local_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, systemp, value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Object temp_2;
    char temp_1;

    x_note_fn_call(43,39);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = G2int_icp_version_info_alist;
    systemp = Nil;
    value = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    systems = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp =  !TRUEP(systems) ? T : Nil;
    if (temp);
    else
	temp = g2int_memq_function(G2int_current_system_name,systems);
    systemp = temp;
    value = EQ(type,Qnull) ||  !TRUEP(systemp) ? Nil : SYMBOL_VALUE(symbol);
    if (symbol && systemp) {
	if (EQ(type,Qnull))
	    temp_1 = TRUEP(T);
	else if (EQ(type,Qfixnum))
	    temp_1 = FIXNUMP(value);
	else if (EQ(type,Qg2int_gensym_string) || EQ(type,
		    Qg2int_wide_string)) {
	    temp_1 = STRINGP(value);
	    if (temp_1);
	    else
		temp_1 = TRUEP(g2int_text_string_p(value));
	}
	else if (EQ(type,Qsymbol))
	    temp_1 = value ? SYMBOLP(value) : TRUEP(Qnil);
	else
	    temp_1 = TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = symbol;
	if (STRINGP(value)) {
	    if (EQ(type,Qg2int_gensym_string))
		temp_2 = g2int_copy_gensym_string(value);
	    else if (EQ(type,Qg2int_wide_string))
		temp_2 = g2int_wide_string_to_gensym_string(value);
	    else
		temp_2 = Qnil;
	}
	else if (g2int_text_string_p(value)) {
	    if (EQ(type,Qg2int_gensym_string))
		temp_2 = g2int_gensym_string_to_wide_string(value);
	    else if (EQ(type,Qg2int_wide_string))
		temp_2 = g2int_copy_text_string(value);
	    else
		temp_2 = Qnil;
	}
	else if (EQ(type,Qnull))
	    temp_2 = Nil;
	else
	    temp_2 = value;
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_gensym_cons_1(temp,
		temp_2),Nil);
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

/* LOCAL-ICP-VERSION-INFO */
Object g2int_local_icp_version_info()
{
    Object temp;

    x_note_fn_call(43,40);
    temp = G2int_cached_local_icp_version_info;
    if (temp)
	return VALUES_1(temp);
    else {
	G2int_cached_local_icp_version_info = 
		g2int_compute_local_icp_version_info();
	return VALUES_1(G2int_cached_local_icp_version_info);
    }
}

/* GET-LOCAL-ICP-VERSION-INFO-VALUE */
Object g2int_get_local_icp_version_info_value(symbol,default_1)
    Object symbol, default_1;
{
    x_note_fn_call(43,41);
    return g2int_get_icp_version_info_value(g2int_local_icp_version_info(),
	    symbol,default_1);
}

/* MIN-OF-LOCAL-AND-REMOTE-ICP-VERSION-INFO-VALUE */
Object g2int_min_of_local_and_remote_icp_version_info_value(icp_socket,symbol)
    Object icp_socket, symbol;
{
    Object temp, temp_1;

    x_note_fn_call(43,42);
    temp = g2int_get_remote_icp_version_info_value(icp_socket,symbol,
	    FIX((SI_Long)0L));
    temp_1 = g2int_get_local_icp_version_info_value(symbol,FIX((SI_Long)0L));
    return VALUES_1(FIXNUM_MIN(temp,temp_1));
}

static Object Qg2int_major_version_number_of_current_gensym_product_line;  /* major-version-number-of-current-gensym-product-line */

/* REMOTE-ICP-MAJOR-VERSION */
Object g2int_remote_icp_major_version(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,43);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_major_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
}

static Object Qg2int_minor_version_number_of_current_gensym_product_line;  /* minor-version-number-of-current-gensym-product-line */

/* REMOTE-ICP-MINOR-VERSION */
Object g2int_remote_icp_minor_version(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,44);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_minor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
}

static Object Qg2int_revision_number_of_current_gensym_product_line;  /* revision-number-of-current-gensym-product-line */

/* REMOTE-ICP-REVISION-NUMBER */
Object g2int_remote_icp_revision_number(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,45);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_revision_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
}

static Object Qg2int_build_identification_string;  /* build-identification-string */

/* REMOTE-ICP-BUILD-IDENTIFICATION-STRING? */
Object g2int_remote_icp_build_identification_stringqm(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(43,46);
    return g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_build_identification_string,Nil);
}

static Object Qg2int_icp_protocol_version;  /* icp-protocol-version */

/* REMOTE-ICP-PROTOCOL-VERSION */
Object g2int_remote_icp_protocol_version(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(43,47);
    temp = g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_icp_protocol_version,Nil);
    if (temp)
	return VALUES_1(temp);
    else
	return g2int_set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket);
}

/* SET-REMOTE-ICP-PROTOCOL-VERSION-FROM-MAJOR-AND-MINOR-VERSION */
Object g2int_set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket)
    Object icp_socket;
{
    Object temp, svref_new_value;
    SI_Long icp_version;

    x_note_fn_call(43,48);
    temp = g2int_remote_icp_major_version(icp_socket);
    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
	    FIXNUM_LE(temp,FIX((SI_Long)127L))))
	return VALUES_1(FIX((SI_Long)0L));
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	    icp_version = (SI_Long)1L;
	    break;
	  case 2:
	    icp_version = (SI_Long)2L;
	    break;
	  case 3:
	    icp_version = (SI_Long)4L;
	    break;
	  case 4:
	    icp_version = (SI_Long)5L;
	    break;
	  default:
	    return VALUES_1(FIX((SI_Long)0L));
	    break;
	}
    svref_new_value = 
	    g2int_gensym_cons_1(g2int_gensym_cons_1(Qg2int_icp_protocol_version,
	    FIX(icp_version)),ISVREF(icp_socket,(SI_Long)19L));
    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
    return VALUES_1(FIX(icp_version));
}

Object G2int_initial_icp_version_info_enabled_p = UNBOUND;

Object G2int_write_initial_icp_version_info_p = UNBOUND;

Object G2int_gsi_local_home = UNBOUND;

static Object Qg2int_initial;      /* initial */

static Object Qg2int_connect_side_info_sent_but_not_yet_acknowledged;  /* connect-side-info-sent-but-not-yet-acknowledged */

static Object Qg2int_acknowledge;  /* acknowledge */

static Object Qg2int_listen_side_info_sent_but_no_acknowledge_yet;  /* listen-side-info-sent-but-no-acknowledge-yet */

static Object Qg2int_send;         /* send */

static Object Qg2int_receive;      /* receive */

/* SEND-INITIAL-ICP-VERSION-INFO */
Object g2int_send_initial_icp_version_info(icp_socket,connect_p)
    Object icp_socket, connect_p;
{
    Object state_1, gsi_application_name, disable_resumability;
    Object name_for_local_home, current_icp_port, current_icp_socket, temp;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, write_initial_icp_version_info_p, new_state;
    char info_initial_p;
    double gensymed_symbol_1;
    Declare_special(16);
    Object result;

    x_note_fn_call(43,49);
    state_1 = ISVREF(icp_socket,(SI_Long)18L);
    gsi_application_name = ISVREF(icp_socket,(SI_Long)52L);
    PUSH_SPECIAL(G2int_gsi_application_name,gsi_application_name,15);
      disable_resumability =  ! !TRUEP(ISVREF(icp_socket,(SI_Long)53L)) ? 
	      T : Nil;
      PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,14);
	name_for_local_home = G2int_gsi_local_home ? 
		g2int_gsi_instance_value_function(G2int_gsi_local_home) : Nil;
	PUSH_SPECIAL(G2int_name_for_local_home,name_for_local_home,13);
	  info_initial_p = EQ(state_1,Qg2int_initial);
	  if ( !(SYMBOLP(G2int_name_for_local_home) || 
		  INLINE_UNSIGNED_BYTE_16_VECTOR_P(G2int_name_for_local_home) 
		  != (SI_Long)0L))
	      G2int_name_for_local_home = Nil;
	  if (G2int_initial_icp_version_info_enabled_p && (info_initial_p 
		  || EQ(state_1,
		  Qg2int_connect_side_info_sent_but_not_yet_acknowledged))) {
	      current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	      PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,12);
		current_icp_socket = ISVREF(G2int_current_icp_port,
			(SI_Long)2L);
		PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,11);
		  temp = IFIX(ISVREF(G2int_current_icp_socket,
			  (SI_Long)22L)) >= (SI_Long)17L ? 
			  ISVREF(G2int_current_icp_socket,(SI_Long)53L) : Nil;
		  if (temp);
		  else
		      temp = Nil;
		  disable_resumability = temp;
		  PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			  10);
		    number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		    PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			    9);
		      icp_buffers_for_message_group = Nil;
		      PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			      8);
			icp_buffer_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
				7);
			  icp_byte_position_of_start_of_message_series_qm 
				  = Nil;
			  PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				  6);
			    number_of_icp_bytes_to_fill_buffer = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				    5);
			      current_icp_buffer = Nil;
			      PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				      4);
				current_write_icp_byte_position = Nil;
				PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
					3);
				  number_of_icp_bytes_in_message_group = 
					  FIX((SI_Long)0L);
				  PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					  2);
				    writing_icp_message_group = 
					    FIXNUM_ADD1(G2int_writing_icp_message_group);
				    PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					    1);
				      gensymed_symbol = Nil;
				      gensymed_symbol_1 = 0.0;
				      gensymed_symbol_1 = 0.0;
				      if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					      &&  
					      !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						  {
					  write_initial_icp_version_info_p 
						  = info_initial_p ? 
						  Qg2int_initial : 
						  Qg2int_acknowledge;
					  PUSH_SPECIAL(G2int_write_initial_icp_version_info_p,write_initial_icp_version_info_p,
						  0);
					    g2int_send_icp_nop(info_initial_p 
						    ? 
						    g2int_initial_icp_version_info_length_in_icp_bytes() 
						    : 
						    g2int_acknowledge_icp_version_info_length_in_icp_bytes());
					  POP_SPECIAL();
					  g2int_end_icp_message_group();
				      }
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
	      new_state = EQ(state_1,Qg2int_initial) ? (connect_p ? 
		      Qg2int_connect_side_info_sent_but_not_yet_acknowledged 
		      : 
		      Qg2int_listen_side_info_sent_but_no_acknowledge_yet) 
		      : Qt;
	      SVREF(icp_socket,FIX((SI_Long)18L)) = new_state;
	      if (EQ(state_1,
		      Qg2int_connect_side_info_sent_but_not_yet_acknowledged) 
		      || EQ(new_state,
		      Qg2int_listen_side_info_sent_but_no_acknowledge_yet))
		  g2int_finalize_icp_version_info(icp_socket,Qg2int_send);
	      if (EQ(state_1,
		      Qg2int_connect_side_info_sent_but_not_yet_acknowledged))
		  result = g2int_finalize_icp_version_info(icp_socket,
			  Qg2int_receive);
	      else
		  result = VALUES_1(Nil);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_no_icp_version_info;  /* no-icp-version-info */

/* ENSURE-REMOTE-ICP-VERSION-INFO */
Object g2int_ensure_remote_icp_version_info(icp_socket,handler_name)
    Object icp_socket, handler_name;
{
    Object svref_new_value;

    x_note_fn_call(43,50);
    if (G2int_initial_icp_version_info_enabled_p) {
	if ( !TRUEP(ISVREF(icp_socket,(SI_Long)19L))) {
	    svref_new_value = 
		    g2int_gensym_cons_1(g2int_gensym_cons_1(Qg2int_no_icp_version_info,
		    Nil),Nil);
	    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
	}
    }
    return VALUES_1(Nil);
}

/* MAYBE-UPDATE-REMOTE-ICP-VERSION-INFO-FOR-VERSION */
Object g2int_maybe_update_remote_icp_version_info_for_version(icp_socket,
	    major_version,minor_version)
    Object icp_socket, major_version, minor_version;
{
    x_note_fn_call(43,51);
    g2int_maybe_update_remote_icp_version_info(icp_socket,major_version,
	    Qg2int_major_version_number_of_current_gensym_product_line);
    g2int_maybe_update_remote_icp_version_info(icp_socket,minor_version,
	    Qg2int_minor_version_number_of_current_gensym_product_line);
    if (g2int_assq_function(Qg2int_no_icp_version_info,ISVREF(icp_socket,
	    (SI_Long)19L))) {
	g2int_set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket);
	g2int_finalize_icp_version_info(icp_socket,Qg2int_send);
	return g2int_finalize_icp_version_info(icp_socket,Qg2int_receive);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-UPDATE-REMOTE-ICP-VERSION-INFO */
Object g2int_maybe_update_remote_icp_version_info(icp_socket,value,symbol)
    Object icp_socket, value, symbol;
{
    Object temp, temp_1, cdr_new_value;

    x_note_fn_call(43,52);
    if ( !TRUEP(ISVREF(icp_socket,(SI_Long)19L))) {
	temp = 
		g2int_gensym_cons_1(g2int_gensym_cons_1(Qg2int_no_icp_version_info,
		Nil),Nil);
	SVREF(icp_socket,FIX((SI_Long)19L)) = temp;
    }
    temp_1 = ISVREF(icp_socket,(SI_Long)19L);
    if (EQ(CAAR(temp_1),Qg2int_no_icp_version_info)) {
	temp = ISVREF(icp_socket,(SI_Long)19L);
	temp_1 = ISVREF(icp_socket,(SI_Long)19L);
	cdr_new_value = g2int_gensym_cons_1(g2int_gensym_cons_1(symbol,
		value),CDR(temp_1));
	return VALUES_1(M_CDR(temp) = cdr_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* FINALIZE-ICP-VERSION-INFO */
Object g2int_finalize_icp_version_info(icp_socket,direction)
    Object icp_socket, direction;
{
    Object svref_new_value;

    x_note_fn_call(43,53);
    if (EQ(direction,Qg2int_receive)) {
	svref_new_value = g2int_remote_icp_protocol_version(icp_socket);
	SVREF(icp_socket,FIX((SI_Long)21L)) = svref_new_value;
    }
    else if (EQ(direction,Qg2int_send)) {
	svref_new_value = g2int_remote_icp_protocol_version(icp_socket);
	SVREF(icp_socket,FIX((SI_Long)22L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* RECEIVE-INITIAL-MESSAGE */
Object g2int_receive_initial_message(local_system,remote_system)
    Object local_system, remote_system;
{
    x_note_fn_call(43,54);
    return VALUES_1(Nil);
}

static Object Qg2int_ab;           /* ab */

static Object Qg2int_g2;           /* g2 */

static Object string_constant_1;   /* "?" */

static Object string_constant_2;   /* "ICP connection: ~A, local: ~A, remote: ~A, version: ~A ~A ~A ~A ~A" */

/* DESCRIBE-ICP-CONNECTION */
Object g2int_describe_icp_connection(icp_socket)
    Object icp_socket;
{
    Object local_system_name, temp, temp_1, temp_2, temp_3, temp_4, temp_5;
    Object temp_6;

    x_note_fn_call(43,55);
    local_system_name = ISVREF(icp_socket,(SI_Long)49L);
    temp = ISVREF(icp_socket,(SI_Long)2L);
    temp_1 = EQ(local_system_name,Qg2int_ab) ? Qg2int_g2 : local_system_name;
    temp_2 = ISVREF(icp_socket,(SI_Long)25L);
    temp_3 = g2int_remote_icp_major_version(icp_socket);
    temp_4 = g2int_remote_icp_minor_version(icp_socket);
    temp_5 = g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_revision_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
    temp_6 = g2int_get_remote_icp_version_info_value(icp_socket,
	    Qg2int_build_identification_string,string_constant_1);
    return g2int_notify_user_at_console(9,string_constant_2,temp,temp_1,
	    temp_2,temp_3,temp_4,temp_5,temp_6,
	    g2int_remote_icp_protocol_version(icp_socket));
}

/* INITIAL-ICP-VERSION-INFO-LENGTH-IN-ICP-BYTES */
Object g2int_initial_icp_version_info_length_in_icp_bytes()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp, incff_1_arg;
    SI_Long size, gensymed_symbol;

    x_note_fn_call(43,56);
    size = (SI_Long)0L;
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = G2int_icp_version_info_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    systems = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    incff_1_arg = 
	    g2int_icp_version_info_element_length_in_icp_bytes(type_code,
	    symbol,type,systems);
    size = size + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    gensymed_symbol = size;
    goto end;
    gensymed_symbol = IFIX(Qnil);
  end:;
    return VALUES_1(FIX(gensymed_symbol + (SI_Long)1L));
}

/* ACKNOWLEDGE-ICP-VERSION-INFO-LENGTH-IN-ICP-BYTES */
Object g2int_acknowledge_icp_version_info_length_in_icp_bytes()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp, incff_1_arg;
    SI_Long size, gensymed_symbol;

    x_note_fn_call(43,57);
    size = (SI_Long)0L;
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = G2int_icp_acknowledge_version_info_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    systems = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    incff_1_arg = 
	    g2int_icp_version_info_element_length_in_icp_bytes(type_code,
	    symbol,type,systems);
    size = size + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    gensymed_symbol = size;
    goto end;
    gensymed_symbol = IFIX(Qnil);
  end:;
    return VALUES_1(FIX(gensymed_symbol + (SI_Long)1L));
}

/* WRITE-INITIAL-ICP-VERSION-INFO */
Object g2int_write_initial_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(43,58);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = G2int_icp_version_info_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    systems = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_write_icp_version_info_element(type_code,symbol,type,systems);
    goto next_loop;
  end_loop:;
    return g2int_write_icp_byte(FIX((SI_Long)0L));
}

/* WRITE-ACKNOWLEDGE-ICP-VERSION-INFO */
Object g2int_write_acknowledge_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(43,59);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = G2int_icp_acknowledge_version_info_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    type_code = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    symbol = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    systems = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_write_icp_version_info_element(type_code,symbol,type,systems);
    goto next_loop;
  end_loop:;
    return g2int_write_icp_byte(FIX((SI_Long)0L));
}

static Object Qg2int_disable_resumability;  /* disable-resumability */

/* ICP-VERSION-INFO-ELEMENT-VALUE */
Object g2int_icp_version_info_element_value(symbol,type,systems)
    Object symbol, type, systems;
{
    Object systemp, value;
    char temp;

    x_note_fn_call(43,60);
    systemp =  !TRUEP(systems) ? T : Nil;
    if (systemp);
    else
	systemp = g2int_memq_function(G2int_current_system_name,systems);
    value =  !(EQ(type,Qnull) ||  !TRUEP(systemp)) ? (EQ(symbol,
	    Qg2int_disable_resumability) ? ( ! 
	    !TRUEP(ISVREF(G2int_current_icp_socket,(SI_Long)53L)) ? T : 
	    Nil) : SYMBOL_VALUE(symbol)) : Nil;
    if (symbol && systemp) {
	if (EQ(type,Qnull))
	    temp = TRUEP(T);
	else if (EQ(type,Qfixnum))
	    temp = FIXNUMP(value);
	else if (EQ(type,Qg2int_gensym_string) || EQ(type,
		    Qg2int_wide_string)) {
	    temp = STRINGP(value);
	    if (temp);
	    else
		temp = TRUEP(g2int_text_string_p(value));
	}
	else if (EQ(type,Qsymbol))
	    temp = value ? SYMBOLP(value) : TRUEP(Qnil);
	else
	    temp = TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_2(value,T);
    else
	return VALUES_1(Nil);
}

/* WRITE-ICP-VERSION-INFO-ELEMENT */
Object g2int_write_icp_version_info_element(type_code,symbol,type,systems)
    Object type_code, symbol, type, systems;
{
    Object value, write_p, length_1, value_1, temp_string;
    Object result;

    x_note_fn_call(43,61);
    result = g2int_icp_version_info_element_value(symbol,type,systems);
    MVS_2(result,value,write_p);
    if (write_p) {
	result = g2int_icp_version_info_element_length_in_icp_bytes_1(type,
		value);
	MVS_3(result,length_1,value_1,temp_string);
	g2int_write_icp_byte(FIX((IFIX(type_code) << (SI_Long)10L) + 
		IFIX(length_1)));
	if (EQ(type,Qnull));
	else if (EQ(type,Qfixnum))
	    g2int_write_icp_fixnum(value_1);
	else if (EQ(type,Qg2int_gensym_string) || EQ(type,Qsymbol))
	    g2int_write_icp_gensym_string(value_1);
	else if (EQ(type,Qg2int_wide_string))
	    g2int_write_icp_wide_string(value_1);
	if (temp_string)
	    g2int_reclaim_text_or_gensym_string(temp_string);
	return VALUES_1(value);
    }
    else
	return VALUES_1(Nil);
}

/* ICP-VERSION-INFO-ELEMENT-LENGTH-IN-ICP-BYTES */
Object g2int_icp_version_info_element_length_in_icp_bytes(type_code,symbol,
	    type,systems)
    Object type_code, symbol, type, systems;
{
    Object value, write_p, temp, length_1, temp_1, temp_string;
    Object result;

    x_note_fn_call(43,62);
    result = g2int_icp_version_info_element_value(symbol,type,systems);
    MVS_2(result,value,write_p);
    if (write_p) {
	result = g2int_icp_version_info_element_length_in_icp_bytes_1(type,
		value);
	MVS_3(result,length_1,temp_1,temp_string);
	if (temp_string)
	    g2int_reclaim_text_or_gensym_string(temp_string);
	temp_1 = FIXNUM_ADD1(length_1);
    }
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(temp_1);
}

/* ICP-VERSION-INFO-ELEMENT-LENGTH-IN-ICP-BYTES-1 */
Object g2int_icp_version_info_element_length_in_icp_bytes_1(type,value)
    Object type, value;
{
    Object temp_string, length_1;

    x_note_fn_call(43,63);
    temp_string = Nil;
    if (EQ(type,Qnull))
	length_1 = FIX((SI_Long)0L);
    else if (EQ(type,Qfixnum))
	length_1 = g2int_fixnum_length_in_icp_bytes(value);
    else if (EQ(type,Qg2int_gensym_string) || EQ(type,Qsymbol)) {
	if (SYMBOLP(value))
	    value = SYMBOL_NAME(value);
	else if (STRINGP(value));
	else {
	    temp_string = g2int_wide_string_to_gensym_string(value);
	    value = temp_string;
	}
	length_1 = g2int_gensym_string_length_in_icp_bytes(value);
    }
    else if (EQ(type,Qg2int_wide_string)) {
	if (!g2int_text_string_p(value)) {
	    temp_string = g2int_gensym_string_to_wide_string(value);
	    value = temp_string;
	}
	length_1 = g2int_wide_string_length_in_icp_bytes(value);
    }
    else
	length_1 = Qnil;
    return VALUES_3(length_1,value,temp_string);
}

/* READ-INITIAL-ICP-VERSION-INFO */
Object g2int_read_initial_icp_version_info(total_number_of_bytes_init)
    Object total_number_of_bytes_init;
{
    Object alist, type_code, size, info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    SI_Long total_number_of_bytes, first_byte, type_plus_size;

    x_note_fn_call(43,64);
    total_number_of_bytes = IFIX(total_number_of_bytes_init);
    if ((SI_Long)0L < total_number_of_bytes) {
	first_byte = IFIX(g2int_read_icp_byte());
	if ((SI_Long)0L == first_byte)
	    return g2int_read_icp_version_info_skip(FIX(total_number_of_bytes));
	else {
	    alist = G2int_icp_version_info_alist;
	    type_plus_size = first_byte;
	    type_code = Nil;
	    size = Nil;
	    info = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ((SI_Long)0L == type_plus_size)
		goto end_loop;
	    type_code = FIX(type_plus_size >>  -  - (SI_Long)10L);
	    size = FIX(type_plus_size & (SI_Long)1023L);
	    info = g2int_read_icp_version_info_element(type_code,size,alist);
	    if (info) {
		ab_loopvar__2 = g2int_gensym_cons_1(info,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    type_plus_size = IFIX(g2int_read_icp_byte());
	    goto next_loop;
	  end_loop:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_acknowledge_version_info_receipt;  /* acknowledge-version-info-receipt */

/* READ-ACKNOWLEDGE-ICP-VERSION-INFO */
Object g2int_read_acknowledge_icp_version_info(total_number_of_bytes_init)
    Object total_number_of_bytes_init;
{
    Object alist, type_code, size, element, temp, svref_arg_1;
    SI_Long total_number_of_bytes, first_byte, type_plus_size;

    x_note_fn_call(43,65);
    total_number_of_bytes = IFIX(total_number_of_bytes_init);
    if ((SI_Long)0L < total_number_of_bytes) {
	first_byte = IFIX(g2int_read_icp_byte());
	if ((SI_Long)0L == first_byte)
	    return g2int_read_icp_version_info_skip(FIX(total_number_of_bytes));
	else {
	    alist = G2int_icp_acknowledge_version_info_alist;
	    type_plus_size = first_byte;
	    type_code = Nil;
	    size = Nil;
	    element = Nil;
	  next_loop:
	    if ((SI_Long)0L == type_plus_size)
		goto end_loop;
	    type_code = FIX(type_plus_size >>  -  - (SI_Long)10L);
	    size = FIX(type_plus_size & (SI_Long)1023L);
	    element = g2int_read_icp_version_info_element(type_code,size,
		    alist);
	    temp = CAR(element);
	    if (EQ(temp,Qg2int_acknowledge_version_info_receipt)) {
		svref_arg_1 = G2int_current_icp_socket;
		SVREF(svref_arg_1,FIX((SI_Long)18L)) = T;
		g2int_finalize_icp_version_info(G2int_current_icp_socket,
			Qg2int_receive);
	    }
	    g2int_reclaim_icp_version_info_element(element);
	    type_plus_size = IFIX(g2int_read_icp_byte());
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* READ-ICP-VERSION-INFO-SKIP */
Object g2int_read_icp_version_info_skip(total_number_of_bytes)
    Object total_number_of_bytes;
{
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(43,66);
    count_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(total_number_of_bytes);
  next_loop:
    if (count_1 >= ab_loop_bind_)
	goto end_loop;
    g2int_read_icp_byte();
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* READ-ICP-VERSION-INFO-ELEMENT */
Object g2int_read_icp_version_info_element(type_code,byte_count,alist)
    Object type_code, byte_count, alist;
{
    Object info, symbol, type, temp;

    x_note_fn_call(43,67);
    info = assoc_eql(type_code,alist);
    symbol = CADR(info);
    type = CADDR(info);
    if (EQ(type,Qnull))
	temp = g2int_gensym_cons_1(symbol,Nil);
    else if (EQ(type,Qfixnum))
	temp = g2int_gensym_cons_1(symbol,g2int_read_icp_fixnum());
    else if (EQ(type,Qg2int_gensym_string))
	temp = g2int_gensym_cons_1(symbol,g2int_read_icp_gensym_string());
    else if (EQ(type,Qg2int_wide_string))
	temp = g2int_gensym_cons_1(symbol,g2int_read_icp_wide_string());
    else if (EQ(type,Qsymbol))
	temp = g2int_gensym_cons_1(symbol,g2int_intern_gensym_string(1,
		g2int_read_icp_gensym_string()));
    else {
	g2int_read_icp_fill_bytes(byte_count);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* RECLAIM-ICP-VERSION-INFO-ELEMENT */
Object g2int_reclaim_icp_version_info_element(element)
    Object element;
{
    Object v;

    x_note_fn_call(43,68);
    v = CDR(element);
    if (STRINGP(v))
	g2int_reclaim_gensym_string(v);
    else if (g2int_text_string_p(v))
	g2int_reclaim_text_string(v);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(v) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(v)) == (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(v);
    g2int_reclaim_gensym_cons_1(element);
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-VERSION-INFO */
Object g2int_reclaim_icp_version_info(version_info)
    Object version_info;
{
    Object info, ab_loop_list_;

    x_note_fn_call(43,69);
    info = Nil;
    ab_loop_list_ = version_info;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_icp_version_info_element(info);
    goto next_loop;
  end_loop:;
    g2int_reclaim_gensym_list_1(version_info);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qg2int_do_not_use;   /* do-not-use */

/* MAYBE-SET-CONNECTION-NAME */
Object g2int_maybe_set_connection_name(icp_socket)
    Object icp_socket;
{
    Object name, accept_pos, remote_name, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object char_1, thing, temp, schar_arg_2, schar_new_value;
    Object new_connection_name;
    SI_Long limit1, length_1, name_length, bv16_length, aref_arg_2;
    SI_Long aref_new_value, i, ab_loop_bind_, thing_1;
    Declare_special(5);

    x_note_fn_call(43,70);
    name = g2int_stringw(ISVREF(icp_socket,(SI_Long)2L));
    limit1 = (SI_Long)8L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(name));
    name_length = UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    accept_pos = limit1 < name_length ? search(4,array_constant,name,Kend1,
	    FIX(limit1)) : Nil;
    remote_name = g2int_get_remote_host_name(G2int_current_icp_socket);
    if (accept_pos && remote_name) {
	current_wide_string_list = Qg2int_do_not_use;
	PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = 
		  g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	  PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
		      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		      (SI_Long)16L));
	      PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qg2int_wide_string;
		PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			0);
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(accept_pos);
		  char_1 = Nil;
		next_loop:
		  if (i >= ab_loop_bind_)
		      goto end_loop;
		  char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
		  if (EQ(G2int_current_twriting_output_type,
			  Qg2int_wide_string)) {
		      thing = char_1;
		      g2int_twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			      G2int_total_length_of_current_gensym_string))
			  g2int_extend_current_gensym_string(0);
		      temp = G2int_current_gensym_string;
		      schar_arg_2 = 
			      G2int_fill_pointer_for_current_gensym_string;
		      thing = char_1;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		      G2int_fill_pointer_for_current_gensym_string = temp;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  if (EQ(G2int_current_twriting_output_type,
			  Qg2int_wide_string)) {
		      thing_1 = (SI_Long)58L;
		      g2int_twrite_wide_character(CHARACTERP(FIX(thing_1)) 
			      ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			      G2int_total_length_of_current_gensym_string))
			  g2int_extend_current_gensym_string(0);
		      temp = G2int_current_gensym_string;
		      schar_arg_2 = 
			      G2int_fill_pointer_for_current_gensym_string;
		      thing_1 = (SI_Long)58L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) 
			      ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		      G2int_fill_pointer_for_current_gensym_string = temp;
		  }
		  g2int_twrite_general_string(remote_name);
		  new_connection_name = g2int_copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	g2int_reclaim_text_or_gensym_string(ISVREF(icp_socket,(SI_Long)2L));
	SVREF(icp_socket,FIX((SI_Long)2L)) = new_connection_name;
	g2int_c_set_connection_pathname(ISVREF(ISVREF(icp_socket,
		(SI_Long)3L),(SI_Long)1L),new_connection_name);
    }
    return VALUES_1(ISVREF(icp_socket,(SI_Long)2L));
}

static Object Qg2int_gsi_application_name;  /* gsi-application-name */

static Object Qg2int_default;      /* default */

static Object Qg2int_read_icp_number_of_icp_bytes_of_fill;  /* read-icp-number-of-icp-bytes-of-fill */

static Object Qg2int_true;         /* true */

static Object Qg2int_false;        /* false */

/* READ-ICP-NUMBER-OF-ICP-BYTES-OF-FILL */
Object g2int_read_icp_number_of_icp_bytes_of_fill()
{
    Object number_of_icp_bytes_of_fill, temp, svref_arg_1, svref_new_value;
    Object resumable_icp_state_1, icp_suspend_1, top, value, test, v1, v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(43,71);
    if (G2int_disable_resumability) {
	number_of_icp_bytes_of_fill = g2int_read_icp_byte();
	temp = ISVREF(G2int_current_icp_socket,(SI_Long)19L);
	if (EQ(CAAR(temp),Qg2int_no_icp_version_info))
	    temp = g2int_read_icp_fill_bytes(number_of_icp_bytes_of_fill);
	else if ( !TRUEP(ISVREF(G2int_current_icp_socket,(SI_Long)19L))) {
	    svref_arg_1 = G2int_current_icp_socket;
	    svref_new_value = 
		    g2int_read_initial_icp_version_info(number_of_icp_bytes_of_fill);
	    SVREF(svref_arg_1,FIX((SI_Long)19L)) = svref_new_value;
	    svref_arg_1 = G2int_current_icp_socket;
	    svref_new_value = 
		    g2int_get_remote_icp_version_info_value(G2int_current_icp_socket,
		    Qg2int_gsi_application_name,Qg2int_default);
	    SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
	    svref_arg_1 = G2int_current_icp_socket;
	    svref_new_value = 
		    g2int_get_remote_icp_version_info_value(G2int_current_icp_socket,
		    Qg2int_disable_resumability,Nil);
	    SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
	    if (ISVREF(G2int_current_icp_socket,(SI_Long)19L)) {
		g2int_send_initial_icp_version_info(G2int_current_icp_socket,
			Nil);
		temp = 
			g2int_maybe_set_connection_name(G2int_current_icp_socket);
	    }
	    else {
		svref_arg_1 = G2int_current_icp_socket;
		temp = 
			g2int_gensym_cons_1(g2int_gensym_cons_1(Qg2int_no_icp_version_info,
			Nil),Nil);
		SVREF(svref_arg_1,FIX((SI_Long)19L)) = temp;
	    }
	}
	else
	    temp = 
		    g2int_read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_number_of_icp_bytes_of_fill,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_number_of_icp_bytes_of_fill,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    number_of_icp_bytes_of_fill = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_number_of_icp_bytes_of_fill);
		return VALUES_1(G2int_icp_suspend);
	    }
	    number_of_icp_bytes_of_fill = value;
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp_1 = EQ(test,Qg2int_true);
	else {
	    temp = ISVREF(G2int_current_icp_socket,(SI_Long)19L);
	    temp_1 = EQ(CAAR(temp),Qg2int_no_icp_version_info);
	}
	if (temp_1) {
	    value = g2int_read_icp_fill_bytes(number_of_icp_bytes_of_fill);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(number_of_icp_bytes_of_fill);
		g2int_resumable_icp_push(Qg2int_read_icp_number_of_icp_bytes_of_fill);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) :  
		    !TRUEP(ISVREF(G2int_current_icp_socket,(SI_Long)19L))) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		svref_arg_1 = G2int_current_icp_socket;
		value = 
			g2int_read_initial_icp_version_info(number_of_icp_bytes_of_fill);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		SVREF(svref_arg_1,FIX((SI_Long)19L)) = value;
		svref_arg_1 = G2int_current_icp_socket;
		svref_new_value = 
			g2int_get_remote_icp_version_info_value(G2int_current_icp_socket,
			Qg2int_gsi_application_name,Qg2int_default);
		SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
		svref_arg_1 = G2int_current_icp_socket;
		svref_new_value = 
			g2int_get_remote_icp_version_info_value(G2int_current_icp_socket,
			Qg2int_disable_resumability,Nil);
		SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
	      l2:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) || ISVREF(G2int_current_icp_socket,
			(SI_Long)19L)) {
		    if (EQ(icp_suspend_1,
			    g2int_send_initial_icp_version_info(G2int_current_icp_socket,
			    Nil))) {
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		    result = g2int_maybe_set_connection_name(G2int_current_icp_socket);
		}
		else if (T) {
		    svref_arg_1 = G2int_current_icp_socket;
		    svref_new_value = 
			    g2int_gensym_cons_1(g2int_gensym_cons_1(Qg2int_no_icp_version_info,
			    Nil),Nil);
		    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)19L)) 
			    = svref_new_value);
		}
		else
		    result = VALUES_1(Nil);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(number_of_icp_bytes_of_fill);
		    g2int_resumable_icp_push(Qg2int_read_icp_number_of_icp_bytes_of_fill);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		value = 
			g2int_read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(number_of_icp_bytes_of_fill);
		    g2int_resumable_icp_push(Qg2int_read_icp_number_of_icp_bytes_of_fill);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

/* READ-ICP-FILL-BYTES */
Object g2int_read_icp_fill_bytes(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object number_of_icp_bytes_to_skip;

    x_note_fn_call(43,72);
    number_of_icp_bytes_to_skip = number_of_icp_bytes_of_fill;
  next_loop:
    if ( !(IFIX(number_of_icp_bytes_to_skip) > (SI_Long)0L))
	goto end_loop;
    g2int_read_icp_byte();
    number_of_icp_bytes_to_skip = FIXNUM_SUB1(number_of_icp_bytes_to_skip);
    goto next_loop;
  end_loop:;
    return VALUES_1(number_of_icp_bytes_of_fill);
}

/* WRITE-ICP-FILL-BYTES */
Object g2int_write_icp_fill_bytes(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    x_note_fn_call(43,73);
  next_loop:
    if ( !(IFIX(number_of_icp_bytes_of_fill) > (SI_Long)0L))
	goto end_loop;
    g2int_write_icp_byte(FIX((SI_Long)0L));
    number_of_icp_bytes_of_fill = FIXNUM_SUB1(number_of_icp_bytes_of_fill);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2int_write_icp_number_of_icp_bytes_of_fill;  /* write-icp-number-of-icp-bytes-of-fill */

/* WRITE-ICP-NUMBER-OF-ICP-BYTES-OF-FILL */
Object g2int_write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, key, value, v1, v2;
    Object v3;
    Object result;

    x_note_fn_call(43,74);
    if (G2int_disable_resumability) {
	g2int_write_icp_byte(number_of_icp_bytes_of_fill);
	if (EQ(G2int_write_initial_icp_version_info_p,Qg2int_initial))
	    temp = g2int_write_initial_icp_version_info();
	else if (EQ(G2int_write_initial_icp_version_info_p,Qg2int_acknowledge))
	    temp = g2int_write_acknowledge_icp_version_info();
	else
	    temp = g2int_write_icp_fill_bytes(number_of_icp_bytes_of_fill);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_number_of_icp_bytes_of_fill,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_number_of_icp_bytes_of_fill,top,Nil);
	}
	number_of_icp_bytes_of_fill = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : number_of_icp_bytes_of_fill;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_byte(number_of_icp_bytes_of_fill))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	key = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		G2int_write_initial_icp_version_info_p;
	if (EQ(key,Qg2int_initial)) {
	    value = g2int_write_initial_icp_version_info();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(key);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_1(value);
	}
	else if (EQ(key,Qg2int_acknowledge)) {
	    value = g2int_write_acknowledge_icp_version_info();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(key);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_1(value);
	}
	else {
	    value = g2int_write_icp_fill_bytes(number_of_icp_bytes_of_fill);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(key);
		g2int_resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(G2int_icp_suspend);
		goto end_block;
	    }
	    result = VALUES_1(value);
	}
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(number_of_icp_bytes_of_fill);
	    g2int_resumable_icp_push(Qg2int_write_icp_number_of_icp_bytes_of_fill);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_unsigned_integer_or_nil;  /* write-icp-unsigned-integer-or-nil */

/* WRITE-ICP-UNSIGNED-INTEGER-OR-NIL */
Object g2int_write_icp_unsigned_integer_or_nil(unsigned_integer_or_nil)
    Object unsigned_integer_or_nil;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_1;

    x_note_fn_call(43,75);
    if (G2int_disable_resumability)
	temp =  !TRUEP(unsigned_integer_or_nil) ? 
		g2int_write_icp_integer(FIX((SI_Long)-1L)) : 
		g2int_write_icp_integer(unsigned_integer_or_nil);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_unsigned_integer_or_nil,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_unsigned_integer_or_nil,top,Nil);
	}
	unsigned_integer_or_nil = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : unsigned_integer_or_nil;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) :  !TRUEP(unsigned_integer_or_nil)) {
	    value = g2int_write_icp_integer(FIX((SI_Long)-1L));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(unsigned_integer_or_nil);
		g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integer_or_nil);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    value = g2int_write_icp_integer(unsigned_integer_or_nil);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(unsigned_integer_or_nil);
		g2int_resumable_icp_push(Qg2int_write_icp_unsigned_integer_or_nil);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_unsigned_integer_or_nil;  /* read-icp-unsigned-integer-or-nil */

/* READ-ICP-UNSIGNED-INTEGER-OR-NIL */
Object g2int_read_icp_unsigned_integer_or_nil()
{
    Object value, temp, resumable_icp_state_1, icp_suspend_1, top, value_1;

    x_note_fn_call(43,76);
    if (G2int_disable_resumability) {
	value = g2int_read_icp_integer();
	temp = IFIX(value) > (SI_Long)-1L ? value : Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_unsigned_integer_or_nil,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_unsigned_integer_or_nil,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_unsigned_integer_or_nil);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value = value_1;
	}
	temp = IFIX(value) > (SI_Long)-1L ? value : Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_float;  /* write-icp-float */

/* WRITE-ICP-FLOAT */
Object g2int_write_icp_float(float_1)
    Object float_1;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,77);
    if (G2int_disable_resumability)
	temp = float_1;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_float,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_float,top,Nil);
	}
	float_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : float_1;
	temp = float_1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_float;  /* read-icp-float */

/* READ-ICP-FLOAT */
Object g2int_read_icp_float()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,78);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_float,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_float,top,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_double_float_using_function;  /* write-icp-double-float-using-function */

/* WRITE-ICP-DOUBLE-FLOAT-USING-FUNCTION */
Object g2int_write_icp_double_float_using_function(double_float)
    Object double_float;
{
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top, b0_1, b1_1, b2_1;
    Object b3_1, value, v1, v2, v3;
    SI_Long b0, b1, b2, b3;
    double temp;
    Object result;

    x_note_fn_call(43,79);
    if (G2int_disable_resumability) {
	temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	g2ext_foreign_partition_float(temp,
		UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
	g2int_write_icp_byte(FIX(b0));
	g2int_write_icp_byte(FIX(b1));
	g2int_write_icp_byte(FIX(b2));
	temp_1 = g2int_write_icp_byte(FIX(b3));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_double_float_using_function,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_double_float_using_function,top,Nil);
	}
	double_float = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : double_float;
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))) {
	    temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	    g2ext_foreign_partition_float(temp,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
	}
	b0_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
		(SI_Long)0L));
	b1_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
		(SI_Long)1L));
	b2_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
		(SI_Long)2L));
	b3_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
		(SI_Long)3L));
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		    temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp_1)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  case 3:
		    goto l3;
		    break;
		  case 4:
		    goto l4;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_byte(b0_1))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	if (EQ(icp_suspend_1,g2int_write_icp_byte(b1_1))) {
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l3:
	if (EQ(icp_suspend_1,g2int_write_icp_byte(b2_1))) {
	    g2int_resumable_icp_push(FIX((SI_Long)3L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l4:
	value = g2int_write_icp_byte(b3_1);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(FIX((SI_Long)4L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
	result = VALUES_1(value);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(b3_1);
	    g2int_resumable_icp_push(b2_1);
	    g2int_resumable_icp_push(b1_1);
	    g2int_resumable_icp_push(b0_1);
	    g2int_resumable_icp_push(double_float);
	    g2int_resumable_icp_push(Qg2int_write_icp_double_float_using_function);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp_1 = v1;
    }
    return VALUES_1(temp_1);
}

/* WRITE-ICP-DOUBLE-FLOAT-1 */
Object g2int_write_icp_double_float_1(value)
    double value;
{
    Object result_1;
    SI_Long b0, b1, b2, b3;

    x_note_fn_call(43,80);
    g2ext_foreign_partition_float(value,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
    b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)0L);
    b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)1L);
    b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)2L);
    b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,(SI_Long)3L);
    g2int_write_icp_byte(FIX(b0));
    g2int_write_icp_byte(FIX(b1));
    g2int_write_icp_byte(FIX(b2));
    g2int_write_icp_byte(FIX(b3));
    result_1 = Nil;
    return result_1;
}

static Object Qg2int_read_icp_double_float_using_function;  /* read-icp-double-float-using-function */

/* READ-ICP-DOUBLE-FLOAT-USING-FUNCTION */
Object g2int_read_icp_double_float_using_function()
{
    Object b0, b1, b2, b3, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object arg1, value, arg2, arg3, arg4;

    x_note_fn_call(43,81);
    if (G2int_disable_resumability) {
	b0 = g2int_read_icp_byte();
	b1 = g2int_read_icp_byte();
	b2 = g2int_read_icp_byte();
	b3 = g2int_read_icp_byte();
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(g2ext_foreign_reconstruct_float(IFIX(b0),
		IFIX(b1),IFIX(b2),IFIX(b3)));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_double_float_using_function,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_double_float_using_function,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_double_float_using_function);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg1 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg2 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(arg1);
		g2int_resumable_icp_push(Qg2int_read_icp_double_float_using_function);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg2 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg3 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(arg2);
		g2int_resumable_icp_push(arg1);
		g2int_resumable_icp_push(Qg2int_read_icp_double_float_using_function);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg3 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg4 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(arg3);
		g2int_resumable_icp_push(arg2);
		g2int_resumable_icp_push(arg1);
		g2int_resumable_icp_push(Qg2int_read_icp_double_float_using_function);
		return VALUES_1(G2int_icp_suspend);
	    }
	    arg4 = value;
	}
	b0 = arg1;
	b1 = arg2;
	b2 = arg3;
	b3 = arg4;
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(g2ext_foreign_reconstruct_float(IFIX(b0),
		IFIX(b1),IFIX(b2),IFIX(b3)));
    }
    return VALUES_1(temp);
}

/* READ-ICP-DOUBLE-FLOAT-1 */
double g2int_read_icp_double_float_1()
{
    Object b0, b1, b2, b3;
    double result_1;

    x_note_fn_call(43,82);
    b0 = g2int_read_icp_byte();
    b1 = g2int_read_icp_byte();
    b2 = g2int_read_icp_byte();
    b3 = g2int_read_icp_byte();
    result_1 = g2ext_foreign_reconstruct_float(IFIX(b0),IFIX(b1),IFIX(b2),
	    IFIX(b3));
    return result_1;
}

static Object Qg2int_read_icp_managed_double_float;  /* read-icp-managed-double-float */

static Object Qg2int_gensym;       /* gensym */

/* READ-ICP-MANAGED-DOUBLE-FLOAT */
Object g2int_read_icp_managed_double_float()
{
    Object tag_temp, amf_available_array_cons_qm, amf_array, temp;
    Object svref_new_value, amf_result, incff_1_arg, new_float, b0, b1, b2, b3;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top, arg1, value;
    Object arg2, arg3, arg4;
    double aref_new_value;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(43,83);
    tag_temp = UNIQUE_TAG(Qg2int_read_icp_managed_double_float);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		amf_available_array_cons_qm = 
			ISVREF(G2int_vector_of_simple_float_array_pools,
			(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp = G2int_vector_of_simple_float_array_pools;
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qg2int_gensym);
		    temp = G2int_available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp;
		    G2int_available_gensym_conses = 
			    amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp = 
			    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		    G2int_created_simple_float_array_pool_arrays = temp;
		    incff_1_arg = 
			    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp = 
			    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    G2int_simple_float_array_pool_memory_usage = temp;
		    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		b0 = g2int_read_icp_byte();
		b1 = g2int_read_icp_byte();
		b2 = g2int_read_icp_byte();
		b3 = g2int_read_icp_byte();
		aref_new_value = g2ext_foreign_reconstruct_float(IFIX(b0),
			IFIX(b1),IFIX(b2),IFIX(b3));
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_1 = new_float;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_read_icp_managed_double_float,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,
			    Qg2int_read_icp_managed_double_float,top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_double_float);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg1 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg2 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_double_float);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg2 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg3 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg2);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_double_float);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg3 = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg4 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(arg3);
			    g2int_resumable_icp_push(arg2);
			    g2int_resumable_icp_push(arg1);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_managed_double_float);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg4 = value;
		    }
		    b0 = arg1;
		    b1 = arg2;
		    b2 = arg3;
		    b3 = arg4;
		    arg1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(g2ext_foreign_reconstruct_float(IFIX(b0),
			    IFIX(b1),IFIX(b2),IFIX(b3)));
		}
		amf_available_array_cons_qm = 
			ISVREF(G2int_vector_of_simple_float_array_pools,
			(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp = G2int_vector_of_simple_float_array_pools;
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qg2int_gensym);
		    temp = G2int_available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp;
		    G2int_available_gensym_conses = 
			    amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp = 
			    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		    G2int_created_simple_float_array_pool_arrays = temp;
		    incff_1_arg = 
			    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp = 
			    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    G2int_simple_float_array_pool_memory_usage = temp;
		    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		temp_1 = new_float;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp_1);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_write_icp_managed_double_float;  /* write-icp-managed-double-float */

/* WRITE-ICP-MANAGED-DOUBLE-FLOAT */
Object g2int_write_icp_managed_double_float(managed_double_float)
    Object managed_double_float;
{
    Object tag_temp, temp, resumable_icp_state_1, icp_suspend_1, top, b0_1;
    Object b1_1, b2_1, b3_1, value, v1, v2, v3;
    SI_Long b0, b1, b2, b3;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(43,84);
    tag_temp = UNIQUE_TAG(Qg2int_write_icp_managed_double_float);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
			(SI_Long)0L),
			UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
		b0 = UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)0L);
		b1 = UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)1L);
		b2 = UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)2L);
		b3 = UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)3L);
		g2int_write_icp_byte(FIX(b0));
		g2int_write_icp_byte(FIX(b1));
		g2int_write_icp_byte(FIX(b2));
		temp = g2int_write_icp_byte(FIX(b3));
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_write_icp_managed_double_float,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,
			    Qg2int_write_icp_managed_double_float,top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    managed_double_float = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : managed_double_float;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if ( !(resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)))
		    g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
			    (SI_Long)0L),
			    UBYTE_16_SARRAY_TO_USHORT_PTR(G2int_partition_float_union));
		b0_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)0L));
		b1_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)1L));
		b2_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)2L));
		b3_1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(UBYTE_16_ISAREF_1(G2int_partition_float_union,
			(SI_Long)3L));
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
			  case 1:
			    goto l1;
			    break;
			  case 2:
			    goto l2;
			    break;
			  case 3:
			    goto l3;
			    break;
			  case 4:
			    goto l4;
			    break;
			  default:
			    break;
			}
		}
	      l1:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b0_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b1_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l3:
		if (EQ(icp_suspend_1,g2int_write_icp_byte(b2_1))) {
		    g2int_resumable_icp_push(FIX((SI_Long)3L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l4:
		value = g2int_write_icp_byte(b3_1);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)4L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(b3_1);
		    g2int_resumable_icp_push(b2_1);
		    g2int_resumable_icp_push(b1_1);
		    g2int_resumable_icp_push(b0_1);
		    g2int_resumable_icp_push(managed_double_float);
		    g2int_resumable_icp_push(Qg2int_write_icp_managed_double_float);
		    result = VALUES_1(G2int_icp_suspend);
		    THROW(tag_temp,result);
		}
		temp = v1;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_send_icp_end_message_block;  /* send-icp-end-message-block */

/* SEND-ICP-END-MESSAGE-BLOCK */
Object g2int_send_icp_end_message_block()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,85);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_end_message_block;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)17L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_end_message_block,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_end_message_block,top,Nil);
		goto end_send_icp_end_message_block;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_end_message_block;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)17L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_end_message_block);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_message_block;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_message_block:
    return result;
}

/* HANDLE-ICP-END-MESSAGE-BLOCK--BODY */
Object g2int_handle_icp_end_message_block__body()
{
    x_note_fn_call(43,86);
    G2int_at_end_of_icp_message_blockqm = T;
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_end_message_block;  /* handle-icp-end-message-block */

/* HANDLE-ICP-END-MESSAGE-BLOCK */
Object g2int_handle_icp_end_message_block()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,87);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_end_message_block__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_end_message_block,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_end_message_block,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_end_message_block__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* RECLAIM-S-EXPRESSION-FOR-REMOTE-EVAL */
Object g2int_reclaim_s_expression_for_remote_eval(s_expression)
    Object s_expression;
{
    x_note_fn_call(43,88);
    return VALUES_1(Nil);
}

Object G2int_sexp_null_type_tag = UNBOUND;

Object G2int_sexp_element_integer_type_tag = UNBOUND;

Object G2int_sexp_element_float_type_tag = UNBOUND;

Object G2int_sexp_element_symbol_type_tag = UNBOUND;

Object G2int_sexp_element_text_type_tag = UNBOUND;

Object G2int_sexp_element_list_type_tag = UNBOUND;

Object G2int_sexp_element_character_type_tag = UNBOUND;

static Object Qg2int_write_icp_sexp_element;  /* write-icp-sexp-element */

/* WRITE-ICP-SEXP-ELEMENT */
Object g2int_write_icp_sexp_element(sexp_element)
    Object sexp_element;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,89);
    if (G2int_disable_resumability)
	temp = sexp_element;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_sexp_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_sexp_element,top,Nil);
	}
	sexp_element = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : sexp_element;
	temp = sexp_element;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_sexp_element;  /* read-icp-sexp-element */

/* READ-ICP-SEXP-ELEMENT */
Object g2int_read_icp_sexp_element()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,90);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_sexp_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_sexp_element,top,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_s_expression_for_remote_eval;  /* write-icp-s-expression-for-remote-eval */

/* WRITE-ICP-S-EXPRESSION-FOR-REMOTE-EVAL */
Object g2int_write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval)
    Object s_expression_for_remote_eval;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,91);
    if (G2int_disable_resumability)
	temp = s_expression_for_remote_eval;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_s_expression_for_remote_eval,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_s_expression_for_remote_eval,top,Nil);
	}
	s_expression_for_remote_eval = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : s_expression_for_remote_eval;
	temp = s_expression_for_remote_eval;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_s_expression_for_remote_eval;  /* read-icp-s-expression-for-remote-eval */

/* READ-ICP-S-EXPRESSION-FOR-REMOTE-EVAL */
Object g2int_read_icp_s_expression_for_remote_eval()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,92);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_s_expression_for_remote_eval,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_s_expression_for_remote_eval,top,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_sending_i_am_aliveqm = UNBOUND;

Object G2int_i_am_alive_send_time_interval_in_seconds = UNBOUND;

Object G2int_i_am_alive_send_time_interval_in_seconds_as_float = UNBOUND;

Object G2int_i_am_alive_send_time_interval = UNBOUND;

/* SEND-I-AM-ALIVE-MESSAGE */
Object g2int_send_i_am_alive_message(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    x_note_fn_call(43,93);
    return VALUES_1(Nil);
}

static Object Qg2int_send_i_am_alive_message;  /* send-i-am-alive-message */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* SCHEDULE-SEND-I-AM-ALIVE-MESSAGE */
Object g2int_schedule_send_i_am_alive_message(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    Object schedule_task_qm, future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_11;
    Object future_task_schedule_modify_arg_12, old_structure_being_reclaimed;
    Object temp_1, def_structure_schedule_task_variable, task;
    char svref_new_value;
    double temp, future_task_schedule_modify_arg_3, aref_new_value;

    x_note_fn_call(43,94);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)51L);
    if ( !(schedule_task_qm && ISVREF(schedule_task_qm,(SI_Long)6L))) {
	temp = 
		DOUBLE_FLOAT_TO_DOUBLE(G2int_i_am_alive_send_time_interval_in_seconds_as_float);
	future_task_schedule_modify_arg_3 = 
		DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L) + temp;
	future_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_send_i_am_alive_message);
	future_task_schedule_modify_arg_11 = icp_socket;
	future_task_schedule_modify_arg_12 = i_am_alive_info;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)51L);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,G2int_current_schedule_task))
		G2int_current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = schedule_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    temp_1 = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_1;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	def_structure_schedule_task_variable = 
		G2int_chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    G2int_chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    g2int_make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp_1 = ISVREF(task,(SI_Long)1L);
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,future_task_schedule_modify_arg_3);
	temp_1 = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	svref_new_value =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_send_i_am_alive_message;
	SVREF(task,FIX((SI_Long)8L)) = future_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)11L)) = future_task_schedule_modify_arg_11;
	SVREF(task,FIX((SI_Long)12L)) = future_task_schedule_modify_arg_12;
	g2int_future_task_schedule_2(task);
	SVREF(icp_socket,FIX((SI_Long)51L)) = task;
    }
    return VALUES_1(Nil);
}

/* DUMP-ICP-BUFFER */
Object g2int_dump_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    Object j, icp_byte, array;
    SI_Long i, ab_loop_bind_, icp_position, position_1, temp;

    x_note_fn_call(43,95);
    format((SI_Long)3L,T,
	    "\n-------------\nICP Buffer ~a:\n-------------\n",icp_buffer);
    j = FIX((SI_Long)0L);
    i = (SI_Long)1L;
    ab_loop_bind_ = (IFIX(ISVREF(icp_buffer,(SI_Long)3L)) >>  -  - 
	    (SI_Long)1L) - (IFIX(ISVREF(icp_buffer,(SI_Long)2L)) >>  -  - 
	    (SI_Long)1L);
    icp_byte = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    array = ISVREF(icp_buffer,(SI_Long)4L);
    icp_position = i;
    position_1 = icp_position + icp_position;
    icp_byte = FIX((UBYTE_8_ISAREF_1(array,position_1) << (SI_Long)8L) + 
	    UBYTE_8_ISAREF_1(array,position_1 + (SI_Long)1L));
    if (IFIX(icp_byte) > (SI_Long)64000L && IFIX(icp_byte) < (SI_Long)64750L) {
	format((SI_Long)4L,T,"~%~a ~(~a~)~%",
		ISVREF(G2int_icp_message_handler_array,IFIX(icp_byte) - 
		(SI_Long)64000L),icp_byte);
	j = FIX((SI_Long)0L);
    }
    else {
	j = FIXNUM_ADD1(j);
	format((SI_Long)3L,T,"~a",icp_byte);
	temp = IFIX(j) % (SI_Long)8L;
	if (temp == (SI_Long)0L)
	    format((SI_Long)2L,T,"~%");
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_icp_message_out_of_synch_case_2_warning = UNBOUND;

/* ICP-CASE-2-ERROR */
Object g2int_icp_case_2_error(icp_input_port,message_series_byte_count,
	    index_of_icp_byte_position,icp_buffer_qm,next_icp_byte_qm,
	    number_of_icp_bytes_in_buffer,
	    number_of_icp_bytes_left_in_buffer,
	    contains_end_of_message_group_qm,icp_message_type_code_offset,
	    icp_message_handler_array_size)
    Object icp_input_port, message_series_byte_count;
    Object index_of_icp_byte_position, icp_buffer_qm, next_icp_byte_qm;
    Object number_of_icp_bytes_in_buffer, number_of_icp_bytes_left_in_buffer;
    Object contains_end_of_message_group_qm, icp_message_type_code_offset;
    Object icp_message_handler_array_size;
{
    x_note_fn_call(43,96);
    format((SI_Long)3L,T,
	    "~%~5T Next ICP byte, ~d, not a valid message type code!~%",
	    next_icp_byte_qm);
    format((SI_Long)2L,T,"~%ICP: Protocol out-of-synch (case 2)! ~%");
    format((SI_Long)3L,T,"~5T ICP Socket Type: ~a~%",
	    ISVREF(ISVREF(icp_input_port,(SI_Long)2L),(SI_Long)1L));
    format((SI_Long)3L,T,"~5T Remote Host Name: ~a~%",
	    ISVREF(ISVREF(icp_input_port,(SI_Long)2L),(SI_Long)2L));
    format((SI_Long)3L,T,"~5T message-series-byte-count: ~a~%",
	    message_series_byte_count);
    format((SI_Long)3L,T,"~5T index-of-icp-byte-position: ~a~%",
	    index_of_icp_byte_position);
    format((SI_Long)3L,T,"~5T icp-buffer\?: ~a~%",icp_buffer_qm);
    format((SI_Long)3L,T,"~5T next-icp-byte\?: ~a~%",next_icp_byte_qm);
    format((SI_Long)3L,T,"~5T contains-end-of-message-group\?: ~a~%",
	    contains_end_of_message_group_qm);
    format((SI_Long)3L,T,"~5T number-of-icp-bytes-in-buffer: ~a~%",
	    number_of_icp_bytes_in_buffer);
    format((SI_Long)3L,T,"~5T number-of-icp-bytes-left-in-buffer: ~a~%",
	    number_of_icp_bytes_left_in_buffer);
    format((SI_Long)3L,T,"~5T #.(icp-message-type-code-offset): ~a~%",
	    icp_message_type_code_offset);
    format((SI_Long)3L,T,
	    "~5T #.(+ (icp-message-type-code-offset)~%~5T      (icp-message-handler-array-size)): ~a~%",
	    FIXNUM_ADD(icp_message_type_code_offset,
	    icp_message_handler_array_size));
    g2int_dump_icp_buffer(icp_buffer_qm);
    return g2int_signal_gsi_icp_message_out_of_synch_case_2_error();
}

Object G2int_local_host_name = UNBOUND;

/* GET-LOCAL-HOST-NAME */
Object g2int_get_local_host_name()
{
    Object temp;

    x_note_fn_call(43,97);
    temp = G2int_local_host_name;
    if (temp)
	return VALUES_1(temp);
    else {
	G2int_local_host_name = g2int_get_unix_host_name();
	return VALUES_1(G2int_local_host_name);
    }
}

static Object Qg2int_unix_tcp_listener_port;  /* unix-tcp-listener-port */

/* GET-CURRENT-ICP-CONTACT-PORT-NUMBER-OR-NAME-IF-ANY */
Object g2int_get_current_icp_contact_port_number_or_name_if_any()
{
    Object symbol_qm;

    x_note_fn_call(43,98);
    symbol_qm = Qg2int_unix_tcp_listener_port;
    if (symbol_qm && BOUNDP(symbol_qm))
	return VALUES_1(SYMBOL_VALUE(symbol_qm));
    else
	return VALUES_1(Nil);
}

static Object Qg2int_send_icp_connection_denied;  /* send-icp-connection-denied */

/* SEND-ICP-CONNECTION-DENIED */
Object g2int_send_icp_connection_denied()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,99);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_connection_denied;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)305L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_connection_denied,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_connection_denied,top,Nil);
		goto end_send_icp_connection_denied;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_connection_denied;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)305L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_connection_denied);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_connection_denied;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_connection_denied:
    return result;
}

static Object Qg2int_gsi_initiate_connection;  /* gsi_initiate_connection */

/* HANDLE-ICP-CONNECTION-DENIED--BODY */
Object g2int_handle_icp_connection_denied__body()
{
    x_note_fn_call(43,100);
    g2int_gsi_connection_error(3,Qg2int_gsi_initiate_connection,
	    G2int_gsi_connection_denied,ISVREF(G2int_current_icp_socket,
	    (SI_Long)2L));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_connection_denied;  /* handle-icp-connection-denied */

/* HANDLE-ICP-CONNECTION-DENIED */
Object g2int_handle_icp_connection_denied()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,101);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_connection_denied__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_connection_denied,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_connection_denied,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_connection_denied__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_no_license;  /* send-icp-no-license */

/* SEND-ICP-NO-LICENSE */
Object g2int_send_icp_no_license()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,102);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_no_license;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)307L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_no_license,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_no_license,top,Nil);
		goto end_send_icp_no_license;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_no_license;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)307L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_no_license);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_no_license;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_no_license:
    return result;
}

/* HANDLE-ICP-NO-LICENSE--BODY */
Object g2int_handle_icp_no_license__body()
{
    x_note_fn_call(43,103);
    g2int_gsi_connection_error(3,Qg2int_gsi_initiate_connection,
	    G2int_gsi_no_license,ISVREF(G2int_current_icp_socket,(SI_Long)2L));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_no_license;  /* handle-icp-no-license */

/* HANDLE-ICP-NO-LICENSE */
Object g2int_handle_icp_no_license()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,104);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_no_license__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_no_license,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_no_license,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_no_license__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_connection_shutdown_imminent;  /* send-icp-connection-shutdown-imminent */

/* SEND-ICP-CONNECTION-SHUTDOWN-IMMINENT */
Object g2int_send_icp_connection_shutdown_imminent(time_until_shutdown)
    Object time_until_shutdown;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,105);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_connection_shutdown_imminent;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)306L));
	  g2int_write_icp_unsigned_integer(time_until_shutdown);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_connection_shutdown_imminent,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_connection_shutdown_imminent,top,Nil);
		goto end_send_icp_connection_shutdown_imminent;
	    }
	}
	time_until_shutdown = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : time_until_shutdown;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_connection_shutdown_imminent;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)306L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(time_until_shutdown))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(time_until_shutdown);
	      g2int_resumable_icp_push(Qg2int_send_icp_connection_shutdown_imminent);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_connection_shutdown_imminent;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_connection_shutdown_imminent:
    return result;
}

/* HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT--BODY */
Object g2int_handle_icp_connection_shutdown_imminent__body(time_until_shutdown)
    Object time_until_shutdown;
{
    x_note_fn_call(43,106);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_connection_shutdown_imminent;  /* handle-icp-connection-shutdown-imminent */

/* HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT */
Object g2int_handle_icp_connection_shutdown_imminent()
{
    Object time_until_shutdown, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,107);
    if (G2int_disable_resumability) {
	time_until_shutdown = g2int_read_icp_unsigned_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_connection_shutdown_imminent,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_connection_shutdown_imminent,top,
			Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    time_until_shutdown = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_connection_shutdown_imminent);
		return VALUES_1(G2int_icp_suspend);
	    }
	    time_until_shutdown = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* WARN-DISALLOWED-ICP-LISTENER-CONNECTIONS */
Object g2int_warn_disallowed_icp_listener_connections varargs_1(int, n)
{
    Object new_icp_listener_connections;
    Declare_varargs_nonrelocating;

    x_note_fn_call(43,108);
    INIT_ARGS_nonrelocating();
    new_icp_listener_connections = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

void int3b_INIT()
{
    Object AB_package, list_constant_48, Qg2int_int3b;
    Object Qg2int_get_unix_host_name, Kfuncall, string_constant_3;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, float_constant;
    Object Qg2int_handling_solitary_i_am_aliveqm, Qg2int_sending_i_am_aliveqm;
    Object list_constant_47, Qg2int_cached_local_icp_version_info;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_34, list_constant_33, list_constant_32;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_4, Qg2int_message_board_enabled;
    Object Qg2int_operator_logbook_enabled;
    Object Qg2int_supoorts_get_and_set_scroll_position_in_grid_view;
    Object Qg2int_supports_update_color_in_label;
    Object Qg2int_supports_update_color_in_list_box;
    Object Qg2int_supports_color_settings_in_toggle_button;
    Object Qg2int_supports_border_settings_in_label;
    Object Qg2int_supports_background_color_in_custom_dialogs;
    Object Qg2int_supports_update_color_in_push_button;
    Object Qg2int_supports_font_in_grid_view;
    Object Qg2int_supports_dialog_component_with_font, list_constant_10;
    Object Qg2int_g2_machine_type, Qg2int_g2_operating_system;
    Object Qg2int_supports_transparent_color_index, list_constant_8;
    Object list_constant_9, list_constant_7, list_constant;
    Object Qg2int_gsi_references_in_use, Qg2int_gsi, list_constant_5;
    Object list_constant_6, list_constant_2, list_constant_1;
    Object Qg2int_latest_icp_window_protocol_version, list_constant_3;
    Object Qg2int_telewindows, Qg2int_icp_value_reclaimer;
    Object Qg2int_reclaim_icp_list, Qg2int_corresponding_icp_object_index_list;
    Object Qg2int_icp_port_for_reclaim;

    x_note_fn_call(43,109);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_send_icp_enlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("SEND-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_enlarge_corresponding_icp_object_index_space,
	    STATIC_FUNCTION(g2int_send_icp_enlarge_corresponding_icp_object_index_space,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space,
	    STATIC_FUNCTION(g2int_handle_icp_enlarge_corresponding_icp_object_index_space,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_enlarge_corresponding_icp_object_index_space,
	    FIX((SI_Long)15L));
    Qg2int_icp_port_for_reclaim = STATIC_SYMBOL("ICP-PORT-FOR-RECLAIM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_port_for_reclaim,
	    G2int_icp_port_for_reclaim);
    Qg2int_int3b = STATIC_SYMBOL("INT3B",AB_package);
    g2int_record_system_variable(Qg2int_icp_port_for_reclaim,Qg2int_int3b,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_deregister_and_register_item_p == UNBOUND)
	G2int_deregister_and_register_item_p = Nil;
    if (G2int_deregister_but_do_not_remove_from_table_p == UNBOUND)
	G2int_deregister_but_do_not_remove_from_table_p = Nil;
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_frame_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",
	    AB_package);
    Qg2int_gsi_instance = STATIC_SYMBOL("GSI-INSTANCE",AB_package);
    Qg2int_registered_item = STATIC_SYMBOL("REGISTERED-ITEM",AB_package);
    Qg2int_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_deregister_corresponding_icp_object,NIL,
	    FALSE,5,5));
    Qg2int_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-OBJECT",AB_package);
    Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name 
	    = 
	    STATIC_SYMBOL("WRITE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_deregister_corresponding_icp_object_index_space_name,
	    STATIC_FUNCTION(g2int_write_icp_deregister_corresponding_icp_object_index_space_name,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name = 
	    STATIC_SYMBOL("READ-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_deregister_corresponding_icp_object_index_space_name,
	    STATIC_FUNCTION(g2int_read_icp_deregister_corresponding_icp_object_index_space_name,
	    NIL,FALSE,0,0));
    Qg2int_send_icp_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_send_icp_deregister_corresponding_icp_object,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_handle_icp_deregister_corresponding_icp_object,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_deregister_corresponding_icp_object,
	    FIX((SI_Long)323L));
    Qg2int_send_icp_deregister_original_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_deregister_original_icp_object,
	    STATIC_FUNCTION(g2int_send_icp_deregister_original_icp_object,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_deregister_original_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_deregister_original_icp_object,
	    STATIC_FUNCTION(g2int_handle_icp_deregister_original_icp_object,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_deregister_original_icp_object,
	    FIX((SI_Long)324L));
    Qg2int_send_icp_delete_icp_object_for_process = 
	    STATIC_SYMBOL("SEND-ICP-DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_delete_icp_object_for_process,
	    STATIC_FUNCTION(g2int_send_icp_delete_icp_object_for_process,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_delete_icp_object_for_process = 
	    STATIC_SYMBOL("HANDLE-ICP-DELETE-ICP-OBJECT-FOR-PROCESS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_delete_icp_object_for_process,
	    STATIC_FUNCTION(g2int_handle_icp_delete_icp_object_for_process,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_delete_icp_object_for_process,
	    FIX((SI_Long)163L));
    Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_acknowledge_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_send_icp_acknowledge_deregister_corresponding_icp_object,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_handle_icp_acknowledge_deregister_corresponding_icp_object,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_acknowledge_deregister_corresponding_icp_object,
	    FIX((SI_Long)325L));
    Qg2int_deregister_corresponding_icp_object_with_deassign = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-WITH-DEASSIGN",
	    AB_package);
    Qg2int_deregister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    Qg2int_delete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    Qg2int_delete_icp_object_for_process_with_deassign = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS-WITH-DEASSIGN",
	    AB_package);
    Qg2int_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qg2int_deregister_and_register_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-AND-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qg2int_write_icp_deregister_icp_objects_operation = 
	    STATIC_SYMBOL("WRITE-ICP-DEREGISTER-ICP-OBJECTS-OPERATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_deregister_icp_objects_operation,
	    STATIC_FUNCTION(g2int_write_icp_deregister_icp_objects_operation,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_deregister_icp_objects_operation = 
	    STATIC_SYMBOL("READ-ICP-DEREGISTER-ICP-OBJECTS-OPERATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_deregister_icp_objects_operation,
	    STATIC_FUNCTION(g2int_read_icp_deregister_icp_objects_operation,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_corresponding_icp_object_index_list = 
	    STATIC_SYMBOL("WRITE-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_corresponding_icp_object_index_list,
	    STATIC_FUNCTION(g2int_write_icp_corresponding_icp_object_index_list,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_corresponding_icp_object_index_list = 
	    STATIC_SYMBOL("READ-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_corresponding_icp_object_index_list,
	    STATIC_FUNCTION(g2int_read_icp_corresponding_icp_object_index_list,
	    NIL,FALSE,0,0));
    Qg2int_corresponding_icp_object_index_list = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX-LIST",AB_package);
    Qg2int_reclaim_icp_list = STATIC_SYMBOL("RECLAIM-ICP-LIST",AB_package);
    Qg2int_icp_value_reclaimer = STATIC_SYMBOL("ICP-VALUE-RECLAIMER",
	    AB_package);
    g2int_mutate_global_property(Qg2int_corresponding_icp_object_index_list,
	    Qg2int_reclaim_icp_list,Qg2int_icp_value_reclaimer);
    Qg2int_send_icp_deregister_icp_objects = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-ICP-OBJECTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_deregister_icp_objects,
	    STATIC_FUNCTION(g2int_send_icp_deregister_icp_objects,NIL,
	    FALSE,3,3));
    Qg2int_handle_icp_deregister_icp_objects = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-ICP-OBJECTS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_deregister_icp_objects,
	    STATIC_FUNCTION(g2int_handle_icp_deregister_icp_objects,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_deregister_icp_objects,
	    FIX((SI_Long)326L));
    Qg2int_send_icp_nop = STATIC_SYMBOL("SEND-ICP-NOP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_nop,
	    STATIC_FUNCTION(g2int_send_icp_nop,NIL,FALSE,1,1));
    Qg2int_handle_icp_nop = STATIC_SYMBOL("HANDLE-ICP-NOP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_nop,
	    STATIC_FUNCTION(g2int_handle_icp_nop,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_nop,FIX((SI_Long)16L));
    if (G2int_gsi_application_name == UNBOUND)
	G2int_gsi_application_name = Nil;
    Qg2int_tcp_listener_port_number = 
	    STATIC_SYMBOL("TCP-LISTENER-PORT-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_tcp_listener_port_number,
	    G2int_tcp_listener_port_number);
    g2int_record_system_variable(Qg2int_tcp_listener_port_number,
	    Qg2int_int3b,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (G2int_name_for_local_home == UNBOUND)
	G2int_name_for_local_home = Nil;
    Qg2int_major_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MAJOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant = STATIC_CONS(Qfixnum,Qnil);
    list_constant_1 = 
	    STATIC_CONS(Qg2int_major_version_number_of_current_gensym_product_line,
	    list_constant);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)1L),list_constant_1);
    Qg2int_minor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MINOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant_2 = 
	    STATIC_CONS(Qg2int_minor_version_number_of_current_gensym_product_line,
	    list_constant);
    list_constant_13 = STATIC_CONS(FIX((SI_Long)2L),list_constant_2);
    Qg2int_latest_icp_window_protocol_version = 
	    STATIC_SYMBOL("LATEST-ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qg2int_ab,Qg2int_telewindows);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qfixnum,list_constant_3);
    list_constant_5 = 
	    STATIC_CONS(Qg2int_latest_icp_window_protocol_version,
	    list_constant_4);
    list_constant_14 = STATIC_CONS(FIX((SI_Long)9L),list_constant_5);
    Qg2int_icp_protocol_version = STATIC_SYMBOL("ICP-PROTOCOL-VERSION",
	    AB_package);
    list_constant_6 = STATIC_CONS(Qg2int_icp_protocol_version,list_constant);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)10L),list_constant_6);
    list_constant_16 = STATIC_CONS(FIX((SI_Long)11L),list_constant_1);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)12L),list_constant_2);
    Qg2int_revision_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("REVISION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)13L),
	    Qg2int_revision_number_of_current_gensym_product_line,
	    list_constant);
    Qg2int_build_identification_string = 
	    STATIC_SYMBOL("BUILD-IDENTIFICATION-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_build_identification_string,
	    G2int_build_identification_string);
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)14L),
	    Qg2int_build_identification_string,Qg2int_gensym_string);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)15L),list_constant_6);
    list_constant_21 = STATIC_CONS(FIX((SI_Long)16L),list_constant_5);
    Qg2int_gsi_references_in_use = STATIC_SYMBOL("GSI-REFERENCES-IN-USE",
	    AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    list_constant_7 = STATIC_CONS(Qg2int_gsi,Qnil);
    list_constant_22 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)17L),
	    Qg2int_gsi_references_in_use,Qfixnum,list_constant_7);
    Qg2int_g2_time_at_start_as_text_string = 
	    STATIC_SYMBOL("G2-TIME-AT-START-AS-TEXT-STRING",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_8 = STATIC_CONS(Qg2int_wide_string,Qnil);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)18L),
	    Qg2int_g2_time_at_start_as_text_string,list_constant_8);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)19L),
	    Qg2int_tcp_listener_port_number,list_constant);
    Qg2int_local_host_name = STATIC_SYMBOL("LOCAL-HOST-NAME",AB_package);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)20L),
	    Qg2int_local_host_name,list_constant_8);
    Qg2int_gsi_application_name = STATIC_SYMBOL("GSI-APPLICATION-NAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_application_name,
	    G2int_gsi_application_name);
    list_constant_9 = STATIC_CONS(Qg2int_ab,list_constant_7);
    list_constant_26 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)21L),
	    Qg2int_gsi_application_name,Qsymbol,list_constant_9);
    Qg2int_disable_resumability = STATIC_SYMBOL("DISABLE-RESUMABILITY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_disable_resumability,
	    G2int_disable_resumability);
    list_constant_10 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)22L),
	    Qg2int_disable_resumability,list_constant_10);
    Qg2int_name_for_local_home = STATIC_SYMBOL("NAME-FOR-LOCAL-HOME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_name_for_local_home,
	    G2int_name_for_local_home);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)23L),
	    Qg2int_name_for_local_home,list_constant_10);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)24L),
	    Qg2int_name_for_local_home,list_constant_8);
    Qg2int_supports_transparent_color_index = 
	    STATIC_SYMBOL("SUPPORTS-TRANSPARENT-COLOR-INDEX",AB_package);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)25L),
	    Qg2int_supports_transparent_color_index,list_constant_4);
    Qg2int_g2_operating_system = STATIC_SYMBOL("G2-OPERATING-SYSTEM",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_operating_system,
	    G2int_g2_operating_system);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)26L),
	    Qg2int_g2_operating_system,list_constant_10);
    Qg2int_g2_machine_type = STATIC_SYMBOL("G2-MACHINE-TYPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_g2_machine_type,G2int_g2_machine_type);
    list_constant_32 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)27L),
	    Qg2int_g2_machine_type,list_constant_10);
    Qg2int_supports_dialog_component_with_font = 
	    STATIC_SYMBOL("SUPPORTS-DIALOG-COMPONENT-WITH-FONT",AB_package);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)28L),
	    Qg2int_supports_dialog_component_with_font,list_constant_4);
    Qg2int_supports_font_in_grid_view = 
	    STATIC_SYMBOL("SUPPORTS-FONT-IN-GRID-VIEW",AB_package);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)29L),
	    Qg2int_supports_font_in_grid_view,list_constant_4);
    Qg2int_supports_update_color_in_push_button = 
	    STATIC_SYMBOL("SUPPORTS-UPDATE-COLOR-IN-PUSH-BUTTON",AB_package);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)30L),
	    Qg2int_supports_update_color_in_push_button,list_constant_4);
    Qg2int_supports_background_color_in_custom_dialogs = 
	    STATIC_SYMBOL("SUPPORTS-BACKGROUND-COLOR-IN-CUSTOM-DIALOGS",
	    AB_package);
    list_constant_36 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)31L),
	    Qg2int_supports_background_color_in_custom_dialogs,
	    list_constant_4);
    Qg2int_supports_border_settings_in_label = 
	    STATIC_SYMBOL("SUPPORTS-BORDER-SETTINGS-IN-LABEL",AB_package);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)32L),
	    Qg2int_supports_border_settings_in_label,list_constant_4);
    Qg2int_supports_color_settings_in_toggle_button = 
	    STATIC_SYMBOL("SUPPORTS-COLOR-SETTINGS-IN-TOGGLE-BUTTON",
	    AB_package);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)33L),
	    Qg2int_supports_color_settings_in_toggle_button,list_constant_4);
    Qg2int_supports_update_color_in_list_box = 
	    STATIC_SYMBOL("SUPPORTS-UPDATE-COLOR-IN-LIST-BOX",AB_package);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)34L),
	    Qg2int_supports_update_color_in_list_box,list_constant_4);
    Qg2int_supports_update_color_in_label = 
	    STATIC_SYMBOL("SUPPORTS-UPDATE-COLOR-IN-LABEL",AB_package);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)35L),
	    Qg2int_supports_update_color_in_label,list_constant_4);
    Qg2int_supoorts_get_and_set_scroll_position_in_grid_view = 
	    STATIC_SYMBOL("SUPOORTS-GET-AND-SET-SCROLL-POSITION-IN-GRID-VIEW",
	    AB_package);
    list_constant_41 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)36L),
	    Qg2int_supoorts_get_and_set_scroll_position_in_grid_view,
	    list_constant_4);
    Qg2int_operator_logbook_enabled = 
	    STATIC_SYMBOL("OPERATOR-LOGBOOK-ENABLED",AB_package);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)37L),
	    Qg2int_operator_logbook_enabled,list_constant_4);
    Qg2int_message_board_enabled = STATIC_SYMBOL("MESSAGE-BOARD-ENABLED",
	    AB_package);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)38L),
	    Qg2int_message_board_enabled,list_constant_4);
    list_constant_43 = STATIC_CONS(list_constant_11,Qnil);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)32L,list_constant_12,
	    list_constant_13,list_constant_14,list_constant_15,
	    list_constant_16,list_constant_17,list_constant_18,
	    list_constant_19,list_constant_20,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25,list_constant_26,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30,
	    list_constant_31,list_constant_32,list_constant_33,
	    list_constant_34,list_constant_35,list_constant_36,
	    list_constant_37,list_constant_38,list_constant_39,
	    list_constant_40,list_constant_41,list_constant_42,
	    list_constant_43);
    G2int_icp_version_info_alist = list_constant_44;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_protocol_version,
	    G2int_icp_protocol_version);
    if (G2int_icp_protocol_version == UNBOUND)
	G2int_icp_protocol_version = G2int_newest_icp_version;
    Qg2int_acknowledge_version_info_receipt = 
	    STATIC_SYMBOL("ACKNOWLEDGE-VERSION-INFO-RECEIPT",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)63L),
	    Qg2int_acknowledge_version_info_receipt,Qnull);
    list_constant_46 = STATIC_CONS(list_constant_45,Qnil);
    G2int_icp_acknowledge_version_info_alist = list_constant_46;
    Qg2int_g2_time_at_start = STATIC_SYMBOL("G2-TIME-AT-START",AB_package);
    Qg2int_cached_local_icp_version_info = 
	    STATIC_SYMBOL("CACHED-LOCAL-ICP-VERSION-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_cached_local_icp_version_info,
	    G2int_cached_local_icp_version_info);
    g2int_record_system_variable(Qg2int_cached_local_icp_version_info,
	    Qg2int_int3b,Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_initial_icp_version_info_enabled_p == UNBOUND)
	G2int_initial_icp_version_info_enabled_p = T;
    if (G2int_write_initial_icp_version_info_p == UNBOUND)
	G2int_write_initial_icp_version_info_p = Nil;
    Qg2int_initial = STATIC_SYMBOL("INITIAL",AB_package);
    Qg2int_connect_side_info_sent_but_not_yet_acknowledged = 
	    STATIC_SYMBOL("CONNECT-SIDE-INFO-SENT-BUT-NOT-YET-ACKNOWLEDGED",
	    AB_package);
    Qg2int_acknowledge = STATIC_SYMBOL("ACKNOWLEDGE",AB_package);
    Qg2int_listen_side_info_sent_but_no_acknowledge_yet = 
	    STATIC_SYMBOL("LISTEN-SIDE-INFO-SENT-BUT-NO-ACKNOWLEDGE-YET",
	    AB_package);
    Qg2int_send = STATIC_SYMBOL("SEND",AB_package);
    Qg2int_receive = STATIC_SYMBOL("RECEIVE",AB_package);
    Qg2int_no_icp_version_info = STATIC_SYMBOL("NO-ICP-VERSION-INFO",
	    AB_package);
    Qg2int_g2 = STATIC_SYMBOL("G2",AB_package);
    string_constant_1 = STATIC_STRING("\?");
    string_constant_2 = 
	    STATIC_STRING("ICP connection: ~A, local: ~A, remote: ~A, version: ~A ~A ~A ~A ~A");
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_47,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_default = STATIC_SYMBOL("DEFAULT",AB_package);
    Qg2int_read_icp_number_of_icp_bytes_of_fill = 
	    STATIC_SYMBOL("READ-ICP-NUMBER-OF-ICP-BYTES-OF-FILL",AB_package);
    Qg2int_true = STATIC_SYMBOL("TRUE",AB_package);
    Qg2int_false = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_number_of_icp_bytes_of_fill,
	    STATIC_FUNCTION(g2int_read_icp_number_of_icp_bytes_of_fill,NIL,
	    FALSE,0,0));
    Qg2int_write_icp_number_of_icp_bytes_of_fill = 
	    STATIC_SYMBOL("WRITE-ICP-NUMBER-OF-ICP-BYTES-OF-FILL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_number_of_icp_bytes_of_fill,
	    STATIC_FUNCTION(g2int_write_icp_number_of_icp_bytes_of_fill,
	    NIL,FALSE,1,1));
    Qg2int_write_icp_unsigned_integer_or_nil = 
	    STATIC_SYMBOL("WRITE-ICP-UNSIGNED-INTEGER-OR-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_unsigned_integer_or_nil,
	    STATIC_FUNCTION(g2int_write_icp_unsigned_integer_or_nil,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_unsigned_integer_or_nil = 
	    STATIC_SYMBOL("READ-ICP-UNSIGNED-INTEGER-OR-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_unsigned_integer_or_nil,
	    STATIC_FUNCTION(g2int_read_icp_unsigned_integer_or_nil,NIL,
	    FALSE,0,0));
    Qg2int_write_icp_float = STATIC_SYMBOL("WRITE-ICP-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_float,
	    STATIC_FUNCTION(g2int_write_icp_float,NIL,FALSE,1,1));
    Qg2int_read_icp_float = STATIC_SYMBOL("READ-ICP-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_float,
	    STATIC_FUNCTION(g2int_read_icp_float,NIL,FALSE,0,0));
    Qg2int_write_icp_double_float_using_function = 
	    STATIC_SYMBOL("WRITE-ICP-DOUBLE-FLOAT-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_double_float_using_function,
	    STATIC_FUNCTION(g2int_write_icp_double_float_using_function,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_double_float_using_function = 
	    STATIC_SYMBOL("READ-ICP-DOUBLE-FLOAT-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_double_float_using_function,
	    STATIC_FUNCTION(g2int_read_icp_double_float_using_function,NIL,
	    FALSE,0,0));
    Qg2int_read_icp_managed_double_float = 
	    STATIC_SYMBOL("READ-ICP-MANAGED-DOUBLE-FLOAT",AB_package);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_managed_double_float,
	    STATIC_FUNCTION(g2int_read_icp_managed_double_float,NIL,FALSE,
	    0,0));
    Qg2int_write_icp_managed_double_float = 
	    STATIC_SYMBOL("WRITE-ICP-MANAGED-DOUBLE-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_managed_double_float,
	    STATIC_FUNCTION(g2int_write_icp_managed_double_float,NIL,FALSE,
	    1,1));
    Qg2int_send_icp_end_message_block = 
	    STATIC_SYMBOL("SEND-ICP-END-MESSAGE-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_end_message_block,
	    STATIC_FUNCTION(g2int_send_icp_end_message_block,NIL,FALSE,0,0));
    Qg2int_handle_icp_end_message_block = 
	    STATIC_SYMBOL("HANDLE-ICP-END-MESSAGE-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_end_message_block,
	    STATIC_FUNCTION(g2int_handle_icp_end_message_block,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_end_message_block,
	    FIX((SI_Long)17L));
    G2int_sexp_null_type_tag = FIX((SI_Long)0L);
    G2int_sexp_element_integer_type_tag = FIX((SI_Long)1L);
    G2int_sexp_element_float_type_tag = FIX((SI_Long)2L);
    G2int_sexp_element_symbol_type_tag = FIX((SI_Long)3L);
    G2int_sexp_element_text_type_tag = FIX((SI_Long)4L);
    G2int_sexp_element_list_type_tag = FIX((SI_Long)5L);
    G2int_sexp_element_character_type_tag = FIX((SI_Long)6L);
    Qg2int_write_icp_sexp_element = STATIC_SYMBOL("WRITE-ICP-SEXP-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_sexp_element,
	    STATIC_FUNCTION(g2int_write_icp_sexp_element,NIL,FALSE,1,1));
    Qg2int_read_icp_sexp_element = STATIC_SYMBOL("READ-ICP-SEXP-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_sexp_element,
	    STATIC_FUNCTION(g2int_read_icp_sexp_element,NIL,FALSE,0,0));
    Qg2int_write_icp_s_expression_for_remote_eval = 
	    STATIC_SYMBOL("WRITE-ICP-S-EXPRESSION-FOR-REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_s_expression_for_remote_eval,
	    STATIC_FUNCTION(g2int_write_icp_s_expression_for_remote_eval,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_s_expression_for_remote_eval = 
	    STATIC_SYMBOL("READ-ICP-S-EXPRESSION-FOR-REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_s_expression_for_remote_eval,
	    STATIC_FUNCTION(g2int_read_icp_s_expression_for_remote_eval,
	    NIL,FALSE,0,0));
    Qg2int_sending_i_am_aliveqm = STATIC_SYMBOL("SENDING-I-AM-ALIVE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_sending_i_am_aliveqm,
	    G2int_sending_i_am_aliveqm);
    g2int_record_system_variable(Qg2int_sending_i_am_aliveqm,Qg2int_int3b,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_handling_solitary_i_am_aliveqm = 
	    STATIC_SYMBOL("HANDLING-SOLITARY-I-AM-ALIVE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_handling_solitary_i_am_aliveqm,
	    G2int_handling_solitary_i_am_aliveqm);
    g2int_record_system_variable(Qg2int_handling_solitary_i_am_aliveqm,
	    Qg2int_int3b,Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_i_am_alive_send_time_interval_in_seconds == UNBOUND)
	G2int_i_am_alive_send_time_interval_in_seconds = FIX((SI_Long)30L);
    float_constant = STATIC_FLOAT(30.0);
    if (G2int_i_am_alive_send_time_interval_in_seconds_as_float == UNBOUND)
	G2int_i_am_alive_send_time_interval_in_seconds_as_float = 
		float_constant;
    if (G2int_i_am_alive_send_time_interval == UNBOUND)
	G2int_i_am_alive_send_time_interval = 
		FIXNUM_TIMES(G2int_i_am_alive_send_time_interval_in_seconds,
		G2int_fixnum_time_units_per_second);
    Qg2int_send_i_am_alive_message = 
	    STATIC_SYMBOL("SEND-I-AM-ALIVE-MESSAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_i_am_alive_message,
	    STATIC_FUNCTION(g2int_send_i_am_alive_message,NIL,FALSE,2,2));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_3 = STATIC_STRING("~5T Protocol out-of-synch (case 2)");
    G2int_icp_message_out_of_synch_case_2_warning = string_constant_3;
    SET_SYMBOL_VALUE_LOCATION(Qg2int_local_host_name,G2int_local_host_name);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_get_unix_host_name = STATIC_SYMBOL("GET-UNIX-HOST-NAME",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_get_unix_host_name);
    g2int_record_system_variable(Qg2int_local_host_name,Qg2int_int3b,
	    list_constant_48,Qnil,Qnil,Qnil,Qnil);
    Qg2int_unix_tcp_listener_port = STATIC_SYMBOL("UNIX-TCP-LISTENER-PORT",
	    AB_package);
    Qg2int_send_icp_connection_denied = 
	    STATIC_SYMBOL("SEND-ICP-CONNECTION-DENIED",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_connection_denied,
	    STATIC_FUNCTION(g2int_send_icp_connection_denied,NIL,FALSE,0,0));
    Qg2int_gsi_initiate_connection = 
	    STATIC_SYMBOL("GSI_INITIATE_CONNECTION",AB_package);
    Qg2int_handle_icp_connection_denied = 
	    STATIC_SYMBOL("HANDLE-ICP-CONNECTION-DENIED",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_connection_denied,
	    STATIC_FUNCTION(g2int_handle_icp_connection_denied,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_connection_denied,
	    FIX((SI_Long)305L));
    Qg2int_send_icp_no_license = STATIC_SYMBOL("SEND-ICP-NO-LICENSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_no_license,
	    STATIC_FUNCTION(g2int_send_icp_no_license,NIL,FALSE,0,0));
    Qg2int_handle_icp_no_license = STATIC_SYMBOL("HANDLE-ICP-NO-LICENSE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_no_license,
	    STATIC_FUNCTION(g2int_handle_icp_no_license,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_no_license,
	    FIX((SI_Long)307L));
    Qg2int_send_icp_connection_shutdown_imminent = 
	    STATIC_SYMBOL("SEND-ICP-CONNECTION-SHUTDOWN-IMMINENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_connection_shutdown_imminent,
	    STATIC_FUNCTION(g2int_send_icp_connection_shutdown_imminent,
	    NIL,FALSE,1,1));
    Qg2int_handle_icp_connection_shutdown_imminent = 
	    STATIC_SYMBOL("HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_connection_shutdown_imminent,
	    STATIC_FUNCTION(g2int_handle_icp_connection_shutdown_imminent,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_connection_shutdown_imminent,
	    FIX((SI_Long)306L));
}
