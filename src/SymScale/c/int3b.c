/* int3b.c
 * Input file:  int3b.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int3b.h"


/* HANDLER-FOR-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object handler_for_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    x_note_fn_call(52,0);
    return enlarge_index_space(ISVREF(Current_icp_port,(SI_Long)8L),
	    FIXNUM_SUB1(new_index_limit_plus_one));
}

static Object Qsend_icp_enlarge_corresponding_icp_object_index_space;  /* send-icp-enlarge-corresponding-icp-object-index-space */

static Object Qcorresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qenlarge_corresponding_icp_object_index_space;  /* enlarge-corresponding-icp-object-index-space */

static Object string_constant;     /* "[message]" */

static Object Qmessage;            /* message */

static Object Qname_of_corresponding_icp_object_index_space;  /* name-of-corresponding-icp-object-index-space */

static Object string_constant_1;   /* "[object arg]" */

static Object Qargument;           /* argument */

static Object Qnew_index_limit_plus_one;  /* new-index-limit-plus-one */

static Object string_constant_2;   /* "[value arg]" */

static Object string_constant_3;   /* "resumable icp synch error: ~S expected, ~S found" */

/* SEND-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object send_icp_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,1);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_enlarge_corresponding_icp_object_index_space;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  start_writing_icp_message(FIX((SI_Long)15L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qenlarge_corresponding_icp_object_index_space,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(new_index_limit_plus_one);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnew_index_limit_plus_one,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(new_index_limit_plus_one);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qenlarge_corresponding_icp_object_index_space,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(new_index_limit_plus_one);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(new_index_limit_plus_one);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qsend_icp_enlarge_corresponding_icp_object_index_space,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_enlarge_corresponding_icp_object_index_space,
			top,Nil);
		goto end_send_icp_enlarge_corresponding_icp_object_index_space;
	    }
	}
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	new_index_limit_plus_one = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : new_index_limit_plus_one;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_enlarge_corresponding_icp_object_index_space;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)15L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qenlarge_corresponding_icp_object_index_space,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(new_index_limit_plus_one))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnew_index_limit_plus_one,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(new_index_limit_plus_one))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qenlarge_corresponding_icp_object_index_space,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(new_index_limit_plus_one))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(new_index_limit_plus_one))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(new_index_limit_plus_one);
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(Qsend_icp_enlarge_corresponding_icp_object_index_space);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one)
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one;
{
    x_note_fn_call(52,2);
    handler_for_enlarge_corresponding_icp_object_index_space(name_of_corresponding_icp_object_index_space,
	    new_index_limit_plus_one);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_enlarge_corresponding_icp_object_index_space;  /* handle-icp-enlarge-corresponding-icp-object-index-space */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE */
Object handle_icp_enlarge_corresponding_icp_object_index_space()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object name_of_corresponding_icp_object_index_space;
    Object new_index_limit_plus_one, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,3);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qenlarge_corresponding_icp_object_index_space,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    new_index_limit_plus_one = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  new_index_limit_plus_one = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
			new_index_limit_plus_one);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qenlarge_corresponding_icp_object_index_space,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnew_index_limit_plus_one,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  new_index_limit_plus_one = result_of_read;
		POP_SPECIAL();
	    }
	    else
		new_index_limit_plus_one = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
		      new_index_limit_plus_one);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_enlarge_corresponding_icp_object_index_space,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_enlarge_corresponding_icp_object_index_space,
			top,Nil);
		goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qenlarge_corresponding_icp_object_index_space,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  new_index_limit_plus_one = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(name_of_corresponding_icp_object_index_space);
			resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnew_index_limit_plus_one,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    new_index_limit_plus_one = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		  }
		  new_index_limit_plus_one = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
			new_index_limit_plus_one);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qenlarge_corresponding_icp_object_index_space,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		new_index_limit_plus_one = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnew_index_limit_plus_one,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnew_index_limit_plus_one,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  new_index_limit_plus_one = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(name_of_corresponding_icp_object_index_space);
		    resumable_icp_push(Qhandle_icp_enlarge_corresponding_icp_object_index_space);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_enlarge_corresponding_icp_object_index_space;
		}
		new_index_limit_plus_one = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_enlarge_corresponding_icp_object_index_space__body(name_of_corresponding_icp_object_index_space,
		      new_index_limit_plus_one);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_enlarge_corresponding_icp_object_index_space:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_port_for_reclaim, Qicp_port_for_reclaim);

DEFINE_VARIABLE_WITH_SYMBOL(Deregister_and_register_item_p, Qderegister_and_register_item_p);

DEFINE_VARIABLE_WITH_SYMBOL(Deregister_but_do_not_remove_from_table_p, Qderegister_but_do_not_remove_from_table_p);

/* NOTE-NO-OBJECT-IN-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object note_no_object_in_deregister_corresponding_icp_object(icp_object,
	    index_1,original_index_space_name,icp_port,localp)
    Object icp_object, index_1, original_index_space_name, icp_port, localp;
{
    x_note_fn_call(52,4);
    return VALUES_1(Nil);
}

static Object Qoutput;             /* output */

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qitem_index_space;   /* item-index-space */

static Object Qg2;                 /* g2 */

static Object Qframe_serial_number;  /* frame-serial-number */

static Object Qgsi_instance;       /* gsi-instance */

static Object Qregistered_item;    /* registered-item */

/* DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object deregister_corresponding_icp_object(icp_object_qm,index_1,
	    original_index_space_name,icp_port,localp)
    Object icp_object_qm, index_1, original_index_space_name, icp_port, localp;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object skip_list, key_value, marked, pred, curr, succ, reference;
    Object entry_hash, index_space_icp_object_qm, vector_1, icp_object_type_qm;
    Object icp_port_for_reclaim, old_entry, svref_arg_1;
    Object items_registered_with_handle, item, ab_loop_list_, icp_output_port;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, index_2, svref_arg_2;
    char outputp;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,5);
    outputp = EQ(Qoutput,ISVREF(icp_port,(SI_Long)3L));
    port = icp_port;
    if (EQ(original_index_space_name,Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(original_index_space_name,Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(original_index_space_name,Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	skip_list = CDR(temp_1);
	key_value = index_1;
	key_hash_value = gensymed_symbol;
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
	index_space_icp_object_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	note_no_object_in_deregister_corresponding_icp_object(icp_object_qm,
		index_1,original_index_space_name,icp_port,localp);
    if ( !TRUEP(icp_object_qm))
	icp_object_qm = index_space_icp_object_qm;
    if ( !TRUEP(icp_object_qm))
	return VALUES_1(Nil);
    icp_object_type_qm = icp_object_type_given_icp_object(icp_object_qm,
	    index_space_name);
    if (EQ(index_space_name,Qframe_serial_number)) {
	icp_port_for_reclaim = icp_port;
	PUSH_SPECIAL_WITH_SYMBOL(Icp_port_for_reclaim,Qicp_port_for_reclaim,icp_port_for_reclaim,
		0);
	  if ( !TRUEP(Deregister_but_do_not_remove_from_table_p)) {
	      gensymed_symbol = IFIX(sxhashw(index_1));
	      temp_2 = gensymed_symbol % (SI_Long)67L;
	      result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),index_1,
		      SVREF(index_space,FIX(temp_2)),FIX((SI_Long)31L),
		      FIX(gensymed_symbol));
	      old_entry = NTH_VALUE((SI_Long)1L, result);
	      if (old_entry)
		  note_item_deleted_from_frame_serial_number_table(old_entry);
	  }
	POP_SPECIAL();
    }
    else {
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,index_1);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) 
		>>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
	remove_icp_port_entries_from_icp_object_1(icp_object_qm,
		icp_object_type_qm,icp_port,original_index_space_name,Nil);
	if (outputp &&  !TRUEP(localp))
	    deassign_index_in_index_space(index_1,index_space);
    }
    if ( !outputp) {
	if (EQ(Qgsi_instance,icp_object_type_qm) || EQ(Qregistered_item,
		icp_object_type_qm)) {
	    items_registered_with_handle = 
		    items_registered_with_handle_on_port(index_1,icp_port);
	    if (items_registered_with_handle) {
		item = Nil;
		ab_loop_list_ = items_registered_with_handle;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		item = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		reclaim_icp_port_entry_for_registered_item(item,icp_port);
		goto next_loop_3;
	      end_loop_3:;
		reclaim_gensym_list_1(items_registered_with_handle);
		clear_items_registered_with_handle_on_port(index_1,icp_port);
	    }
	}
    }
    if ( !TRUEP(localp) &&  !outputp &&  
	    !TRUEP(Deregister_and_register_item_p) && EQ(index_space_name,
	    Qitem_index_space)) {
	icp_output_port = ISVREF(ISVREF(icp_port,(SI_Long)2L),(SI_Long)4L);
	if (send_reclaim_index_space_message_p(icp_output_port,T,
		index_space_name))
	    enqueue_reclaim_index_space_message(icp_output_port,index_1,
		    original_index_space_name,T,T,Nil,Nil);
    }
    return VALUES_4(icp_object_qm,icp_object_type_qm,index_space_name,
	    outputp ? T : Nil);
}

static Object Qreclaimer_for_icp_object;  /* reclaimer-for-icp-object */

/* HANDLE-DELETE-CORRESPONDING-ICP-OBJECT */
Object handle_delete_corresponding_icp_object(index_1,index_space_name,
	    icp_port)
    Object index_1, index_space_name, icp_port;
{
    Object icp_object_qm, icp_object_type_qm, reclaimer_for_icp_object_qm;
    Object result;

    x_note_fn_call(52,6);
    result = deregister_corresponding_icp_object(Nil,index_1,
	    index_space_name,icp_port,Nil);
    MVS_2(result,icp_object_qm,icp_object_type_qm);
    if (icp_object_qm) {
	if (icp_object_type_qm) {
	    reclaimer_for_icp_object_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type_qm),
		    Qreclaimer_for_icp_object);
	    if (reclaimer_for_icp_object_qm)
		inline_funcall_1(reclaimer_for_icp_object_qm,icp_object_qm);
	}
    }
    return VALUES_1(Nil);
}

static Object Qderegister_corresponding_icp_object_index_space_name;  /* deregister-corresponding-icp-object-index-space-name */

static Object string_constant_4;   /* "[value]" */

static Object Qvalue;              /* value */

static Object Qwrite_icp_deregister_corresponding_icp_object_index_space_name;  /* write-icp-deregister-corresponding-icp-object-index-space-name */

/* WRITE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME */
Object write_icp_deregister_corresponding_icp_object_index_space_name(deregister_corresponding_icp_object_index_space_name)
    Object deregister_corresponding_icp_object_index_space_name;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,7);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object_index_space_name,
			string_constant_4,Qvalue,T,
			deregister_corresponding_icp_object_index_space_name,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)10L ? 
		      write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qderegister_corresponding_icp_object_index_space_name,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)10L ? 
		    write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qwrite_icp_deregister_corresponding_icp_object_index_space_name,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_deregister_corresponding_icp_object_index_space_name,
			top,Nil);
		goto end_write_icp_deregister_corresponding_icp_object_index_space_name;
	    }
	}
	deregister_corresponding_icp_object_index_space_name = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		deregister_corresponding_icp_object_index_space_name;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object_index_space_name,
			string_constant_4,Qvalue,T,
			deregister_corresponding_icp_object_index_space_name,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)10L) {
		  value = 
			  write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(deregister_corresponding_icp_object_index_space_name);
		      resumable_icp_push(Qwrite_icp_deregister_corresponding_icp_object_index_space_name);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_deregister_corresponding_icp_object_index_space_name;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qderegister_corresponding_icp_object_index_space_name,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)10L) {
	    value = 
		    write_icp_symbol_as_value_type(deregister_corresponding_icp_object_index_space_name);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(deregister_corresponding_icp_object_index_space_name);
		resumable_icp_push(Qwrite_icp_deregister_corresponding_icp_object_index_space_name);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_deregister_corresponding_icp_object_index_space_name;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_deregister_corresponding_icp_object_index_space_name:
    return result;
}

static Object Qread_icp_deregister_corresponding_icp_object_index_space_name;  /* read-icp-deregister-corresponding-icp-object-index-space-name */

/* READ-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME */
Object read_icp_deregister_corresponding_icp_object_index_space_name()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,8);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object_index_space_name,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)10L ? 
		      read_icp_symbol_as_value_type() : 
		      Qstandard_icp_object_index_space;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_corresponding_icp_object_index_space_name,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)10L ? read_icp_symbol_as_value_type() : 
		    Qstandard_icp_object_index_space;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qread_icp_deregister_corresponding_icp_object_index_space_name,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_deregister_corresponding_icp_object_index_space_name,
			top,Nil);
		goto end_read_icp_deregister_corresponding_icp_object_index_space_name;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object_index_space_name,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)10L) {
		  value = read_icp_symbol_as_value_type();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_deregister_corresponding_icp_object_index_space_name);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_deregister_corresponding_icp_object_index_space_name;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Qstandard_icp_object_index_space;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_corresponding_icp_object_index_space_name,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)10L) {
	    value = read_icp_symbol_as_value_type();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_deregister_corresponding_icp_object_index_space_name);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_deregister_corresponding_icp_object_index_space_name;
	    }
	    temp = value;
	}
	else
	    temp = Qstandard_icp_object_index_space;
    }
    result = VALUES_1(temp);
  end_read_icp_deregister_corresponding_icp_object_index_space_name:
    return result;
}

static Object Qsend_icp_deregister_corresponding_icp_object;  /* send-icp-deregister-corresponding-icp-object */

static Object Qderegister_corresponding_icp_object;  /* deregister-corresponding-icp-object */

static Object Qcorresponding_icp_object_index;  /* corresponding-icp-object-index */

/* SEND-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object send_icp_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,9);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_deregister_corresponding_icp_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)323L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qderegister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_corresponding_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_deregister_corresponding_icp_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_deregister_corresponding_icp_object,top,Nil);
		goto end_send_icp_deregister_corresponding_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_deregister_corresponding_icp_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)323L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qderegister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_corresponding_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_deregister_corresponding_icp_object_index_space_name(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_deregister_corresponding_icp_object);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(52,10);
    deregister_corresponding_icp_object(Nil,corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,Current_icp_port,Nil);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_deregister_corresponding_icp_object;  /* handle-icp-deregister-corresponding-icp-object */

/* HANDLE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object handle_icp_deregister_corresponding_icp_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,11);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_deregister_corresponding_icp_object_index_space_name();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  name_of_corresponding_icp_object_index_space = 
			  read_icp_deregister_corresponding_icp_object_index_space_name();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_deregister_corresponding_icp_object_index_space_name();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else
		name_of_corresponding_icp_object_index_space = 
			read_icp_deregister_corresponding_icp_object_index_space_name();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_deregister_corresponding_icp_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_deregister_corresponding_icp_object,
			top,Nil);
		goto end_handle_icp_deregister_corresponding_icp_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_corresponding_icp_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_corresponding_icp_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_corresponding_icp_object;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = 
			    read_icp_deregister_corresponding_icp_object_index_space_name();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_corresponding_icp_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = 
			  read_icp_deregister_corresponding_icp_object_index_space_name();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_corresponding_icp_object;
		  }
		  name_of_corresponding_icp_object_index_space = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_corresponding_icp_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_corresponding_icp_object;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = 
			  read_icp_deregister_corresponding_icp_object_index_space_name();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_corresponding_icp_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = 
			read_icp_deregister_corresponding_icp_object_index_space_name();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_deregister_corresponding_icp_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_corresponding_icp_object;
		}
		name_of_corresponding_icp_object_index_space = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_deregister_corresponding_icp_object:
    return result;
}

static Object Qsend_icp_deregister_original_icp_object;  /* send-icp-deregister-original-icp-object */

static Object Qderegister_original_icp_object;  /* deregister-original-icp-object */

/* SEND-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT */
Object send_icp_deregister_original_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,12);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_deregister_original_icp_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)324L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qderegister_original_icp_object,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_original_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_deregister_original_icp_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_deregister_original_icp_object,top,Nil);
		goto end_send_icp_deregister_original_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_deregister_original_icp_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)324L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qderegister_original_icp_object,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_original_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_symbol_as_value_type(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_deregister_original_icp_object);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(52,13);
    deregister_corresponding_icp_object(Nil,corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,
	    ISVREF(ISVREF(Current_icp_port,(SI_Long)2L),(SI_Long)4L),Nil);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_deregister_original_icp_object;  /* handle-icp-deregister-original-icp-object */

/* HANDLE-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT */
Object handle_icp_deregister_original_icp_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,14);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_original_icp_object,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_symbol_as_value_type();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  name_of_corresponding_icp_object_index_space = 
			  read_icp_symbol_as_value_type();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_original_icp_object,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_symbol_as_value_type();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else
		name_of_corresponding_icp_object_index_space = 
			read_icp_symbol_as_value_type();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_deregister_original_icp_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_deregister_original_icp_object,top,Nil);
		goto end_handle_icp_deregister_original_icp_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_original_icp_object,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_original_icp_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_original_icp_object;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_symbol_as_value_type();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_original_icp_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_symbol_as_value_type();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_original_icp_object;
		  }
		  name_of_corresponding_icp_object_index_space = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_original_icp_object,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_original_icp_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_original_icp_object;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_symbol_as_value_type();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_original_icp_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_symbol_as_value_type();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_deregister_original_icp_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_original_icp_object;
		}
		name_of_corresponding_icp_object_index_space = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_original_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_deregister_original_icp_object:
    return result;
}

static Object Qsend_icp_delete_icp_object_for_process;  /* send-icp-delete-icp-object-for-process */

static Object Qdelete_icp_object_for_process;  /* delete-icp-object-for-process */

/* SEND-ICP-DELETE-ICP-OBJECT-FOR-PROCESS */
Object send_icp_delete_icp_object_for_process(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,15);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_delete_icp_object_for_process;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  start_writing_icp_message(FIX((SI_Long)163L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdelete_icp_object_for_process,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdelete_icp_object_for_process,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_delete_icp_object_for_process,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_delete_icp_object_for_process,top,Nil);
		goto end_send_icp_delete_icp_object_for_process;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_delete_icp_object_for_process;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)163L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdelete_icp_object_for_process,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdelete_icp_object_for_process,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_delete_icp_object_for_process);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(52,16);
    handle_delete_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space,Current_icp_port);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_delete_icp_object_for_process;  /* handle-icp-delete-icp-object-for-process */

/* HANDLE-ICP-DELETE-ICP-OBJECT-FOR-PROCESS */
Object handle_icp_delete_icp_object_for_process()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object index_1, index_space, name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,17);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdelete_icp_object_for_process,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdelete_icp_object_for_process,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_delete_icp_object_for_process,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_delete_icp_object_for_process,top,Nil);
		goto end_handle_icp_delete_icp_object_for_process;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qdelete_icp_object_for_process,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_delete_icp_object_for_process;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_delete_icp_object_for_process;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_delete_icp_object_for_process;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_delete_icp_object_for_process;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdelete_icp_object_for_process,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_delete_icp_object_for_process;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_delete_icp_object_for_process;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_delete_icp_object_for_process;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_delete_icp_object_for_process);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_delete_icp_object_for_process;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_delete_icp_object_for_process__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_delete_icp_object_for_process:
    return result;
}

/* HANDLE-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object icp_port, port, index_space_name, icp_socket, temp, temp_1;
    Object index_space;

    x_note_fn_call(52,18);
    icp_port = ISVREF(ISVREF(Current_icp_port,(SI_Long)2L),(SI_Long)4L);
    port = icp_port;
    if (EQ(name_of_corresponding_icp_object_index_space,
	    Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(name_of_corresponding_icp_object_index_space,
	    Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    deassign_index_in_index_space(corresponding_icp_object_index,index_space);
    return VALUES_1(Nil);
}

static Object Qsend_icp_acknowledge_deregister_corresponding_icp_object;  /* send-icp-acknowledge-deregister-corresponding-icp-object */

static Object Qacknowledge_deregister_corresponding_icp_object;  /* acknowledge-deregister-corresponding-icp-object */

/* SEND-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object send_icp_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,19);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_acknowledge_deregister_corresponding_icp_object;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  start_writing_icp_message(FIX((SI_Long)325L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qacknowledge_deregister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qacknowledge_deregister_corresponding_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qsend_icp_acknowledge_deregister_corresponding_icp_object,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_acknowledge_deregister_corresponding_icp_object,
			top,Nil);
		goto end_send_icp_acknowledge_deregister_corresponding_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_acknowledge_deregister_corresponding_icp_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)325L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qacknowledge_deregister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qacknowledge_deregister_corresponding_icp_object,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_acknowledge_deregister_corresponding_icp_object);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space)
    Object corresponding_icp_object_index;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(52,20);
    handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_corresponding_icp_object_index_space);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_acknowledge_deregister_corresponding_icp_object;  /* handle-icp-acknowledge-deregister-corresponding-icp-object */

/* HANDLE-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT */
Object handle_icp_acknowledge_deregister_corresponding_icp_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object index_1, index_space, name_of_corresponding_icp_object_index_space;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,21);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qacknowledge_deregister_corresponding_icp_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qacknowledge_deregister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_acknowledge_deregister_corresponding_icp_object,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_acknowledge_deregister_corresponding_icp_object,
			top,Nil);
		goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qacknowledge_deregister_corresponding_icp_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
			name_of_corresponding_icp_object_index_space);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qacknowledge_deregister_corresponding_icp_object,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_acknowledge_deregister_corresponding_icp_object);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_acknowledge_deregister_corresponding_icp_object;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_acknowledge_deregister_corresponding_icp_object__body(corresponding_icp_object_index,
		      name_of_corresponding_icp_object_index_space);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_acknowledge_deregister_corresponding_icp_object:
    return result;
}

static Object Qderegister_icp_objects_operation;  /* deregister-icp-objects-operation */

static Object Qderegister_corresponding_icp_object_with_deassign;  /* deregister-corresponding-icp-object-with-deassign */

static Object Qdelete_icp_object_for_process_with_deassign;  /* delete-icp-object-for-process-with-deassign */

static Object Qderegister_and_register_corresponding_icp_object;  /* deregister-and-register-corresponding-icp-object */

static Object Qwrite_icp_deregister_icp_objects_operation;  /* write-icp-deregister-icp-objects-operation */

/* WRITE-ICP-DEREGISTER-ICP-OBJECTS-OPERATION */
Object write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation)
    Object deregister_icp_objects_operation;
{
    Object tracep, byte_count_before, current_icp_write_trace_level, temp;
    Object result_of_write, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,22);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qderegister_icp_objects_operation,
			string_constant_4,Qvalue,T,
			deregister_icp_objects_operation,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (EQ(deregister_icp_objects_operation,
		      Qderegister_corresponding_icp_object))
		  temp = FIX((SI_Long)0L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_corresponding_icp_object_with_deassign))
		  temp = FIX((SI_Long)0L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_original_icp_object))
		  temp = FIX((SI_Long)1L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qdelete_icp_object_for_process))
		  temp = FIX((SI_Long)2L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qdelete_icp_object_for_process_with_deassign))
		  temp = FIX((SI_Long)2L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qacknowledge_deregister_corresponding_icp_object))
		  temp = FIX((SI_Long)3L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_and_register_corresponding_icp_object))
		  temp = FIX((SI_Long)4L);
	      else
		  temp = Qnil;
	      result_of_write = write_icp_byte(temp);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qderegister_icp_objects_operation,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if (EQ(deregister_icp_objects_operation,
		    Qderegister_corresponding_icp_object))
		temp = FIX((SI_Long)0L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_corresponding_icp_object_with_deassign))
		temp = FIX((SI_Long)0L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_original_icp_object))
		temp = FIX((SI_Long)1L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qdelete_icp_object_for_process))
		temp = FIX((SI_Long)2L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qdelete_icp_object_for_process_with_deassign))
		temp = FIX((SI_Long)2L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qacknowledge_deregister_corresponding_icp_object))
		temp = FIX((SI_Long)3L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_and_register_corresponding_icp_object))
		temp = FIX((SI_Long)4L);
	    else
		temp = Qnil;
	    temp = write_icp_byte(temp);
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_deregister_icp_objects_operation,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_deregister_icp_objects_operation,top,Nil);
		goto end_write_icp_deregister_icp_objects_operation;
	    }
	}
	deregister_icp_objects_operation = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : deregister_icp_objects_operation;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qderegister_icp_objects_operation,
			string_constant_4,Qvalue,T,
			deregister_icp_objects_operation,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (EQ(deregister_icp_objects_operation,
		      Qderegister_corresponding_icp_object))
		  temp = FIX((SI_Long)0L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_corresponding_icp_object_with_deassign))
		  temp = FIX((SI_Long)0L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_original_icp_object))
		  temp = FIX((SI_Long)1L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qdelete_icp_object_for_process))
		  temp = FIX((SI_Long)2L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qdelete_icp_object_for_process_with_deassign))
		  temp = FIX((SI_Long)2L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qacknowledge_deregister_corresponding_icp_object))
		  temp = FIX((SI_Long)3L);
	      else if (EQ(deregister_icp_objects_operation,
		      Qderegister_and_register_corresponding_icp_object))
		  temp = FIX((SI_Long)4L);
	      else
		  temp = Qnil;
	      value = write_icp_byte(temp);
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(deregister_icp_objects_operation);
		  resumable_icp_push(Qwrite_icp_deregister_icp_objects_operation);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_deregister_icp_objects_operation;
	      }
	      result_of_write = value;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qderegister_icp_objects_operation,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if (EQ(deregister_icp_objects_operation,
		    Qderegister_corresponding_icp_object))
		temp = FIX((SI_Long)0L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_corresponding_icp_object_with_deassign))
		temp = FIX((SI_Long)0L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_original_icp_object))
		temp = FIX((SI_Long)1L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qdelete_icp_object_for_process))
		temp = FIX((SI_Long)2L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qdelete_icp_object_for_process_with_deassign))
		temp = FIX((SI_Long)2L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qacknowledge_deregister_corresponding_icp_object))
		temp = FIX((SI_Long)3L);
	    else if (EQ(deregister_icp_objects_operation,
		    Qderegister_and_register_corresponding_icp_object))
		temp = FIX((SI_Long)4L);
	    else
		temp = Qnil;
	    value = write_icp_byte(temp);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(deregister_icp_objects_operation);
		resumable_icp_push(Qwrite_icp_deregister_icp_objects_operation);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_deregister_icp_objects_operation;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_deregister_icp_objects_operation:
    return result;
}

static Object Qread_icp_deregister_icp_objects_operation;  /* read-icp-deregister-icp-objects-operation */

/* READ-ICP-DEREGISTER-ICP-OBJECTS-OPERATION */
Object read_icp_deregister_icp_objects_operation()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, temp;
    Object result_of_read, resumable_icp_state_1, icp_suspend_1, top, key;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,23);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_icp_objects_operation,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      temp = read_icp_byte();
	      if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      result_of_read = Qderegister_corresponding_icp_object;
		      break;
		    case 1:
		      result_of_read = Qderegister_original_icp_object;
		      break;
		    case 2:
		      result_of_read = Qdelete_icp_object_for_process;
		      break;
		    case 3:
		      result_of_read = 
			      Qacknowledge_deregister_corresponding_icp_object;
		      break;
		    case 4:
		      result_of_read = 
			      Qderegister_and_register_corresponding_icp_object;
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_icp_objects_operation,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    temp = read_icp_byte();
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L))))
		temp = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = Qderegister_corresponding_icp_object;
		    break;
		  case 1:
		    temp = Qderegister_original_icp_object;
		    break;
		  case 2:
		    temp = Qdelete_icp_object_for_process;
		    break;
		  case 3:
		    temp = Qacknowledge_deregister_corresponding_icp_object;
		    break;
		  case 4:
		    temp = Qderegister_and_register_corresponding_icp_object;
		    break;
		  default:
		    temp = Nil;
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_deregister_icp_objects_operation,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_deregister_icp_objects_operation,top,Nil);
		goto end_read_icp_deregister_icp_objects_operation;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qderegister_icp_objects_operation,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  key = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_deregister_icp_objects_operation);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_deregister_icp_objects_operation;
		  }
		  key = value;
	      }
	      if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		      FIXNUM_LE(key,FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(key)) {
		    case 0:
		      result_of_read = Qderegister_corresponding_icp_object;
		      break;
		    case 1:
		      result_of_read = Qderegister_original_icp_object;
		      break;
		    case 2:
		      result_of_read = Qdelete_icp_object_for_process;
		      break;
		    case 3:
		      result_of_read = 
			      Qacknowledge_deregister_corresponding_icp_object;
		      break;
		    case 4:
		      result_of_read = 
			      Qderegister_and_register_corresponding_icp_object;
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_icp_objects_operation,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		key = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_deregister_icp_objects_operation);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_deregister_icp_objects_operation;
		}
		key = value;
	    }
	    if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		    FIXNUM_LE(key,FIX((SI_Long)127L))))
		temp = Nil;
	    else
		switch (INTEGER_TO_CHAR(key)) {
		  case 0:
		    temp = Qderegister_corresponding_icp_object;
		    break;
		  case 1:
		    temp = Qderegister_original_icp_object;
		    break;
		  case 2:
		    temp = Qdelete_icp_object_for_process;
		    break;
		  case 3:
		    temp = Qacknowledge_deregister_corresponding_icp_object;
		    break;
		  case 4:
		    temp = Qderegister_and_register_corresponding_icp_object;
		    break;
		  default:
		    temp = Nil;
		    break;
		}
	}
    }
    result = VALUES_1(temp);
  end_read_icp_deregister_icp_objects_operation:
    return result;
}

static Object Qcorresponding_icp_object_index_list;  /* corresponding-icp-object-index-list */

static Object Qwrite_icp_corresponding_icp_object_index_list;  /* write-icp-corresponding-icp-object-index-list */

/* WRITE-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST */
Object write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list)
    Object corresponding_icp_object_index_list;
{
    Object tracep, byte_count_before, current_icp_write_trace_level, index_1;
    Object ab_loop_list_, result_of_write, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,24);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qcorresponding_icp_object_index_list,
			string_constant_4,Qvalue,T,
			corresponding_icp_object_index_list,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      write_icp_byte(length(corresponding_icp_object_index_list));
	      index_1 = Nil;
	      ab_loop_list_ = corresponding_icp_object_index_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      index_1 = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      write_icp_unsigned_integer(index_1);
	      goto next_loop;
	    end_loop:
	      result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qcorresponding_icp_object_index_list,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    write_icp_byte(length(corresponding_icp_object_index_list));
	    index_1 = Nil;
	    ab_loop_list_ = corresponding_icp_object_index_list;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    index_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    write_icp_unsigned_integer(index_1);
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_corresponding_icp_object_index_list,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_corresponding_icp_object_index_list,top,
			Nil);
		goto end_write_icp_corresponding_icp_object_index_list;
	    }
	}
	corresponding_icp_object_index_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index_list;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qcorresponding_icp_object_index_list,
			string_constant_4,Qvalue,T,
			corresponding_icp_object_index_list,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp = resumable_icp_pop();
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
	      if (EQ(icp_suspend_1,
		      write_icp_byte(length(corresponding_icp_object_index_list)))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      index_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loop_list_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      corresponding_icp_object_index_list;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      index_1 = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	    resume:
	      if (EQ(icp_suspend_1,write_icp_unsigned_integer(index_1))) {
		  resumable_icp_push(ab_loop_list_);
		  resumable_icp_push(index_1);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      result = VALUES_1(Qnil);
	      goto end_block;
	    end_block:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(corresponding_icp_object_index_list);
		  resumable_icp_push(Qwrite_icp_corresponding_icp_object_index_list);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_corresponding_icp_object_index_list;
	      }
	      temp = v1;
	      result_of_write = temp;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qcorresponding_icp_object_index_list,
			  string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		temp = resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
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
		    write_icp_byte(length(corresponding_icp_object_index_list)))) 
			{
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    index_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		     TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loop_list_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : corresponding_icp_object_index_list;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    index_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	  resume_1:
	    if (EQ(icp_suspend_1,write_icp_unsigned_integer(index_1))) {
		resumable_icp_push(ab_loop_list_);
		resumable_icp_push(index_1);
		resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    result = VALUES_1(Qnil);
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		resumable_icp_push(corresponding_icp_object_index_list);
		resumable_icp_push(Qwrite_icp_corresponding_icp_object_index_list);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_corresponding_icp_object_index_list;
	    }
	    temp = v1;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_corresponding_icp_object_index_list:
    return result;
}

static Object Qread_icp_corresponding_icp_object_index_list;  /* read-icp-corresponding-icp-object-index-list */

/* READ-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST */
Object read_icp_corresponding_icp_object_index_list()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,25);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qcorresponding_icp_object_index_list,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(read_icp_byte());
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      ab_loopvar__2 = icp_cons_1(read_icp_unsigned_integer(),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      result_of_read = ab_loopvar_;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qcorresponding_icp_object_index_list,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(read_icp_byte());
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    ab_loopvar__2 = icp_cons_1(read_icp_unsigned_integer(),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar_;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_corresponding_icp_object_index_list,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_corresponding_icp_object_index_list,top,Nil);
		goto end_read_icp_corresponding_icp_object_index_list;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qcorresponding_icp_object_index_list,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      i = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)0L;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  ab_loop_bind_ = IFIX(resumable_icp_pop());
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(FIX(i));
		      resumable_icp_push(Qread_icp_corresponding_icp_object_index_list);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_corresponding_icp_object_index_list;
		  }
		  ab_loop_bind_ = IFIX(value);
	      }
	      ab_loopvar_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__2 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if (i >= ab_loop_bind_)
		  goto end_loop_2;
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(i));
		      resumable_icp_push(Qread_icp_corresponding_icp_object_index_list);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_corresponding_icp_object_index_list;
		  }
		  arg1 = value;
	      }
	      arg2 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__2 = icp_cons_1(arg1,arg2);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      i = i + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:
	      result_of_read = ab_loopvar_;
	      goto end_3;
	      result_of_read = Qnil;
	    end_3:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qcorresponding_icp_object_index_list,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    i = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)0L;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		ab_loop_bind_ = IFIX(resumable_icp_pop());
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(FIX(i));
		    resumable_icp_push(Qread_icp_corresponding_icp_object_index_list);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_corresponding_icp_object_index_list;
		}
		ab_loop_bind_ = IFIX(value);
	    }
	    ab_loopvar_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__1 = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__2 = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if (i >= ab_loop_bind_)
		goto end_loop_3;
	  resume_1:
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(i));
		    resumable_icp_push(Qread_icp_corresponding_icp_object_index_list);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_corresponding_icp_object_index_list;
		}
		arg1 = value;
	    }
	    arg2 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__2 = icp_cons_1(arg1,arg2);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    i = i + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_corresponding_icp_object_index_list:
    return result;
}

static Object Qsend_icp_deregister_icp_objects;  /* send-icp-deregister-icp-objects */

static Object Qderegister_icp_objects;  /* deregister-icp-objects */

/* SEND-ICP-DEREGISTER-ICP-OBJECTS */
Object send_icp_deregister_icp_objects(name_of_corresponding_icp_object_index_space,
	    deregister_icp_objects_operation,
	    corresponding_icp_object_index_list)
    Object name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,26);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_deregister_icp_objects;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	  name_of_corresponding_icp_object_index_space = temp_1;
	  start_writing_icp_message(FIX((SI_Long)326L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qderegister_icp_objects,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qderegister_icp_objects_operation,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index_list,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_icp_objects,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_deregister_icp_objects,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_deregister_icp_objects,top,Nil);
		goto end_send_icp_deregister_icp_objects;
	    }
	}
	name_of_corresponding_icp_object_index_space = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		name_of_corresponding_icp_object_index_space;
	deregister_icp_objects_operation = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : deregister_icp_objects_operation;
	corresponding_icp_object_index_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index_list;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_deregister_icp_objects;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_corresponding_icp_object_index_space),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      name_of_corresponding_icp_object_index_space = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(name_of_corresponding_icp_object_index_space);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      name_of_corresponding_icp_object_index_space = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)326L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qderegister_icp_objects,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qname_of_corresponding_icp_object_index_space,
				  string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qderegister_icp_objects_operation,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index_list,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qderegister_icp_objects,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(name_of_corresponding_icp_object_index_space))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_deregister_icp_objects_operation(deregister_icp_objects_operation))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list))) 
				{
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_icp_object_index_list(corresponding_icp_object_index_list))) 
			  {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(corresponding_icp_object_index_list);
	      resumable_icp_push(deregister_icp_objects_operation);
	      resumable_icp_push(name_of_corresponding_icp_object_index_space);
	      resumable_icp_push(Qsend_icp_deregister_icp_objects);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
	    deregister_icp_objects_operation,
	    corresponding_icp_object_index_list)
    Object name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list;
{
    Object corresponding_icp_object_index, ab_loop_list_;
    Object deregister_and_register_item_p;
    Declare_special(1);

    x_note_fn_call(52,27);
    if (EQ(deregister_icp_objects_operation,
	    Qderegister_corresponding_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	deregister_corresponding_icp_object(Nil,
		corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,
		Current_icp_port,Nil);
	goto next_loop;
      end_loop:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qderegister_and_register_corresponding_icp_object)) {
	deregister_and_register_item_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Deregister_and_register_item_p,Qderegister_and_register_item_p,deregister_and_register_item_p,
		0);
	  corresponding_icp_object_index = Nil;
	  ab_loop_list_ = corresponding_icp_object_index_list;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  corresponding_icp_object_index = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  deregister_corresponding_icp_object(Nil,
		  corresponding_icp_object_index,
		  name_of_corresponding_icp_object_index_space,
		  Current_icp_port,Nil);
	  goto next_loop_1;
	end_loop_1:;
	POP_SPECIAL();
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qderegister_original_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	deregister_corresponding_icp_object(Nil,
		corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,
		ISVREF(ISVREF(Current_icp_port,(SI_Long)2L),(SI_Long)4L),Nil);
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qdelete_icp_object_for_process)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	handle_delete_corresponding_icp_object(corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space,Current_icp_port);
	goto next_loop_3;
      end_loop_3:;
    }
    else if (EQ(deregister_icp_objects_operation,
	    Qacknowledge_deregister_corresponding_icp_object)) {
	corresponding_icp_object_index = Nil;
	ab_loop_list_ = corresponding_icp_object_index_list;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	corresponding_icp_object_index = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	handle_acknowledge_deregister_corresponding_icp_object(corresponding_icp_object_index,
		name_of_corresponding_icp_object_index_space);
	goto next_loop_4;
      end_loop_4:;
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_deregister_icp_objects;  /* handle-icp-deregister-icp-objects */

/* HANDLE-ICP-DEREGISTER-ICP-OBJECTS */
Object handle_icp_deregister_icp_objects()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object name_of_corresponding_icp_object_index_space;
    Object deregister_icp_objects_operation;
    Object corresponding_icp_object_index_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,28);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qderegister_icp_objects,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_deregister_icp_objects_operation();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    deregister_icp_objects_operation = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  deregister_icp_objects_operation = 
			  read_icp_deregister_icp_objects_operation();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_corresponding_icp_object_index_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index_list = 
			  read_icp_corresponding_icp_object_index_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
			deregister_icp_objects_operation,
			corresponding_icp_object_index_list);
	      POP_SPECIAL();
	      result_of_read = 
		      reclaim_icp_list_1(corresponding_icp_object_index_list);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_icp_objects,string_constant,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qderegister_icp_objects_operation,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_deregister_icp_objects_operation();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  deregister_icp_objects_operation = result_of_read;
		POP_SPECIAL();
	    }
	    else
		deregister_icp_objects_operation = 
			read_icp_deregister_icp_objects_operation();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index_list,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_corresponding_icp_object_index_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index_list = 
			read_icp_corresponding_icp_object_index_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
		      deregister_icp_objects_operation,
		      corresponding_icp_object_index_list);
	    POP_SPECIAL();
	    reclaim_icp_list_1(corresponding_icp_object_index_list);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_deregister_icp_objects,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_deregister_icp_objects,top,Nil);
		goto end_handle_icp_deregister_icp_objects;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qderegister_icp_objects,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  name_of_corresponding_icp_object_index_space = 
			  resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_deregister_icp_objects;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qname_of_corresponding_icp_object_index_space,
				string_constant_1,Qargument,T,
				result_of_read,Nil,Nil);
		    name_of_corresponding_icp_object_index_space = 
			    result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_deregister_icp_objects;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      name_of_corresponding_icp_object_index_space = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      name_of_corresponding_icp_object_index_space = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  deregister_icp_objects_operation = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_deregister_icp_objects_operation();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(name_of_corresponding_icp_object_index_space);
			resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_icp_objects;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qderegister_icp_objects_operation,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    deregister_icp_objects_operation = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_deregister_icp_objects_operation();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_icp_objects;
		  }
		  deregister_icp_objects_operation = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index_list = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_corresponding_icp_object_index_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(deregister_icp_objects_operation);
			resumable_icp_push(name_of_corresponding_icp_object_index_space);
			resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_deregister_icp_objects;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index_list,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_corresponding_icp_object_index_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(deregister_icp_objects_operation);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_icp_objects;
		  }
		  corresponding_icp_object_index_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
			deregister_icp_objects_operation,
			corresponding_icp_object_index_list);
	      POP_SPECIAL();
	      result_of_read = 
		      reclaim_icp_list_1(corresponding_icp_object_index_list);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qderegister_icp_objects,string_constant,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		name_of_corresponding_icp_object_index_space = 
			resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qname_of_corresponding_icp_object_index_space,
			    string_constant_1,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_deregister_icp_objects;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qname_of_corresponding_icp_object_index_space,
			      string_constant_1,Qargument,T,result_of_read,
			      Nil,Nil);
		  name_of_corresponding_icp_object_index_space = 
			  result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_deregister_icp_objects);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_deregister_icp_objects;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    name_of_corresponding_icp_object_index_space = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    name_of_corresponding_icp_object_index_space = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		deregister_icp_objects_operation = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qderegister_icp_objects_operation,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_deregister_icp_objects_operation();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_icp_objects;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qderegister_icp_objects_operation,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  deregister_icp_objects_operation = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_deregister_icp_objects_operation();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(name_of_corresponding_icp_object_index_space);
		    resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_icp_objects;
		}
		deregister_icp_objects_operation = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index_list = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index_list,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_corresponding_icp_object_index_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(deregister_icp_objects_operation);
		      resumable_icp_push(name_of_corresponding_icp_object_index_space);
		      resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_deregister_icp_objects;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index_list,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_corresponding_icp_object_index_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(deregister_icp_objects_operation);
		    resumable_icp_push(name_of_corresponding_icp_object_index_space);
		    resumable_icp_push(Qhandle_icp_deregister_icp_objects);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_deregister_icp_objects;
		}
		corresponding_icp_object_index_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_deregister_icp_objects__body(name_of_corresponding_icp_object_index_space,
		      deregister_icp_objects_operation,
		      corresponding_icp_object_index_list);
	    POP_SPECIAL();
	    reclaim_icp_list_1(corresponding_icp_object_index_list);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_deregister_icp_objects:
    return result;
}

static Object Qsend_icp_nop;       /* send-icp-nop */

static Object Qnop;                /* nop */

static Object Qnumber_of_icp_bytes_of_fill;  /* number-of-icp-bytes-of-fill */

/* SEND-ICP-NOP */
Object send_icp_nop(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,29);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_nop;
	  }
	  start_writing_icp_message(FIX((SI_Long)16L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qnop,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_icp_bytes_of_fill,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_icp_bytes_of_fill,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qnop,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnumber_of_icp_bytes_of_fill,string_constant_2,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnumber_of_icp_bytes_of_fill,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_nop,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_nop,top,Nil);
		goto end_send_icp_nop;
	    }
	}
	number_of_icp_bytes_of_fill = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : number_of_icp_bytes_of_fill;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_nop;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)16L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qnop,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_icp_bytes_of_fill,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_icp_bytes_of_fill,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qnop,
			    string_constant,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnumber_of_icp_bytes_of_fill,string_constant_2,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnumber_of_icp_bytes_of_fill,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill))) 
		      {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(number_of_icp_bytes_of_fill);
	      resumable_icp_push(Qsend_icp_nop);
	      result = VALUES_1(Icp_suspend);
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
Object handle_icp_nop__body(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    x_note_fn_call(52,30);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_nop;     /* handle-icp-nop */

/* HANDLE-ICP-NOP */
Object handle_icp_nop()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, number_of_icp_bytes_of_fill;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,31);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnop,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnumber_of_icp_bytes_of_fill,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_number_of_icp_bytes_of_fill();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_icp_bytes_of_fill,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    number_of_icp_bytes_of_fill = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  number_of_icp_bytes_of_fill = 
			  read_icp_number_of_icp_bytes_of_fill();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nop__body(number_of_icp_bytes_of_fill);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qnop,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnumber_of_icp_bytes_of_fill,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_number_of_icp_bytes_of_fill();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_icp_bytes_of_fill,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  number_of_icp_bytes_of_fill = result_of_read;
		POP_SPECIAL();
	    }
	    else
		number_of_icp_bytes_of_fill = 
			read_icp_number_of_icp_bytes_of_fill();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nop__body(number_of_icp_bytes_of_fill);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_nop,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_nop,top,Nil);
		goto end_handle_icp_nop;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnop,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  number_of_icp_bytes_of_fill = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnumber_of_icp_bytes_of_fill,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_number_of_icp_bytes_of_fill();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_nop);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_nop;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_icp_bytes_of_fill,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    number_of_icp_bytes_of_fill = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_number_of_icp_bytes_of_fill();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_nop);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nop;
		  }
		  number_of_icp_bytes_of_fill = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_nop__body(number_of_icp_bytes_of_fill);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qnop,
			  string_constant,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		number_of_icp_bytes_of_fill = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnumber_of_icp_bytes_of_fill,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_number_of_icp_bytes_of_fill();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_nop);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_nop;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_icp_bytes_of_fill,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  number_of_icp_bytes_of_fill = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_number_of_icp_bytes_of_fill();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_nop);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_nop;
		}
		number_of_icp_bytes_of_fill = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_nop__body(number_of_icp_bytes_of_fill);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_nop:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_application_name, Qgsi_application_name);

DEFINE_VARIABLE_WITH_SYMBOL(Tcp_listener_port_number, Qtcp_listener_port_number);

DEFINE_VARIABLE_WITH_SYMBOL(Name_for_local_home, Qname_for_local_home);

Object Icp_version_info_alist = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Icp_protocol_version, Qicp_protocol_version);

Object Icp_acknowledge_version_info_alist = UNBOUND;

/* GET-ICP-VERSION-INFO-VALUE */
Object get_icp_version_info_value(info,symbol,default_1)
    Object info, symbol, default_1;
{
    Object temp;

    x_note_fn_call(52,32);
    temp = assoc_eql(symbol,info);
    temp = CDR(temp);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(default_1);
}

/* GET-REMOTE-ICP-VERSION-INFO-VALUE */
Object get_remote_icp_version_info_value(icp_socket,symbol,default_1)
    Object icp_socket, symbol, default_1;
{
    x_note_fn_call(52,33);
    return get_icp_version_info_value(ISVREF(icp_socket,(SI_Long)19L),
	    symbol,default_1);
}

/* RECONSTRUCT-G2-TIME-AT-START */
Object reconstruct_g2_time_at_start(text_string)
    Object text_string;
{
    x_note_fn_call(52,34);
    return reconstruct_managed_float(FIX(UBYTE_16_ISAREF_1(text_string,
	    (SI_Long)0L)),FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)1L)),
	    FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)2L)),
	    FIX(UBYTE_16_ISAREF_1(text_string,(SI_Long)3L)));
}

/* GET-REMOTE-G2-TIME-AT-START */
Object get_remote_g2_time_at_start(icp_socket)
    Object icp_socket;
{
    Object version_info, temp, text_string_qm, managed_float;
    Object icp_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(52,35);
    version_info = ISVREF(icp_socket,(SI_Long)19L);
    temp = get_icp_version_info_value(version_info,Qg2_time_at_start,Nil);
    if (temp)
	return VALUES_1(temp);
    else {
	text_string_qm = get_icp_version_info_value(version_info,
		Qg2_time_at_start_as_text_string,Nil);
	if (text_string_qm) {
	    managed_float = reconstruct_g2_time_at_start(text_string_qm);
	    icp_push_modify_macro_arg = icp_cons_1(Qg2_time_at_start,
		    managed_float);
	    car_1 = icp_push_modify_macro_arg;
	    cdr_1 = ISVREF(icp_socket,(SI_Long)19L);
	    svref_new_value = icp_cons_1(car_1,cdr_1);
	    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
	    return VALUES_1(managed_float);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GET-REMOTE-HOST-NAME */
Object get_remote_host_name(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,36);
    return get_remote_icp_version_info_value(icp_socket,Qlocal_host_name,Nil);
}

/* GET-REMOTE-LISTENER-PORT */
Object get_remote_listener_port(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,37);
    return get_remote_icp_version_info_value(icp_socket,
	    Qtcp_listener_port_number,FIX((SI_Long)0L));
}

/* GET-REMOTE-HOME-NAME */
Object get_remote_home_name(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,38);
    return get_remote_icp_version_info_value(icp_socket,
	    Qname_for_local_home,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_local_icp_version_info, Qcached_local_icp_version_info);

static Object Qgensym_string;      /* gensym-string */

static Object Qwide_string;        /* wide-string */

/* COMPUTE-LOCAL-ICP-VERSION-INFO */
Object compute_local_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, systemp, value;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Object temp_2;
    char temp_1;

    x_note_fn_call(52,39);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = Icp_version_info_alist;
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
	temp = memq_function(Current_system_name,systems);
    systemp = temp;
    value = EQ(type,Qnull) ||  !TRUEP(systemp) ? Nil : SYMBOL_VALUE(symbol);
    if (symbol && systemp) {
	if (EQ(type,Qnull))
	    temp_1 = TRUEP(T);
	else if (EQ(type,Qfixnum))
	    temp_1 = FIXNUMP(value);
	else if (EQ(type,Qgensym_string) || EQ(type,Qwide_string)) {
	    temp_1 = STRINGP(value);
	    if (temp_1);
	    else
		temp_1 = TRUEP(text_string_p(value));
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
	    if (EQ(type,Qgensym_string))
		temp_2 = copy_gensym_string(value);
	    else if (EQ(type,Qwide_string))
		temp_2 = wide_string_to_gensym_string(value);
	    else
		temp_2 = Qnil;
	}
	else if (text_string_p(value)) {
	    if (EQ(type,Qgensym_string))
		temp_2 = gensym_string_to_wide_string(value);
	    else if (EQ(type,Qwide_string))
		temp_2 = copy_text_string(value);
	    else
		temp_2 = Qnil;
	}
	else if (EQ(type,Qnull))
	    temp_2 = Nil;
	else
	    temp_2 = value;
	ab_loopvar__2 = icp_cons_1(icp_cons_1(temp,temp_2),Nil);
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
Object local_icp_version_info()
{
    Object temp;

    x_note_fn_call(52,40);
    temp = Cached_local_icp_version_info;
    if (temp)
	return VALUES_1(temp);
    else {
	Cached_local_icp_version_info = compute_local_icp_version_info();
	return VALUES_1(Cached_local_icp_version_info);
    }
}

/* GET-LOCAL-ICP-VERSION-INFO-VALUE */
Object get_local_icp_version_info_value(symbol,default_1)
    Object symbol, default_1;
{
    x_note_fn_call(52,41);
    return get_icp_version_info_value(local_icp_version_info(),symbol,
	    default_1);
}

/* MIN-OF-LOCAL-AND-REMOTE-ICP-VERSION-INFO-VALUE */
Object min_of_local_and_remote_icp_version_info_value(icp_socket,symbol)
    Object icp_socket, symbol;
{
    Object temp, temp_1;

    x_note_fn_call(52,42);
    temp = get_remote_icp_version_info_value(icp_socket,symbol,
	    FIX((SI_Long)0L));
    temp_1 = get_local_icp_version_info_value(symbol,FIX((SI_Long)0L));
    return VALUES_1(FIXNUM_MIN(temp,temp_1));
}

static Object Qmajor_version_number_of_current_gensym_product_line;  /* major-version-number-of-current-gensym-product-line */

/* REMOTE-ICP-MAJOR-VERSION */
Object remote_icp_major_version(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,43);
    return get_remote_icp_version_info_value(icp_socket,
	    Qmajor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
}

static Object Qminor_version_number_of_current_gensym_product_line;  /* minor-version-number-of-current-gensym-product-line */

/* REMOTE-ICP-MINOR-VERSION */
Object remote_icp_minor_version(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,44);
    return get_remote_icp_version_info_value(icp_socket,
	    Qminor_version_number_of_current_gensym_product_line,
	    FIX((SI_Long)0L));
}

static Object Qrevision_number_of_current_gensym_product_line;  /* revision-number-of-current-gensym-product-line */

/* REMOTE-ICP-REVISION-NUMBER */
Object remote_icp_revision_number(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,45);
    return get_remote_icp_version_info_value(icp_socket,
	    Qrevision_number_of_current_gensym_product_line,FIX((SI_Long)0L));
}

static Object Qbuild_identification_string;  /* build-identification-string */

/* REMOTE-ICP-BUILD-IDENTIFICATION-STRING? */
Object remote_icp_build_identification_string_qm(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(52,46);
    return get_remote_icp_version_info_value(icp_socket,
	    Qbuild_identification_string,Nil);
}

/* REMOTE-ICP-PROTOCOL-VERSION */
Object remote_icp_protocol_version(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(52,47);
    temp = get_remote_icp_version_info_value(icp_socket,
	    Qicp_protocol_version,Nil);
    if (temp)
	return VALUES_1(temp);
    else
	return set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket);
}

/* SET-REMOTE-ICP-PROTOCOL-VERSION-FROM-MAJOR-AND-MINOR-VERSION */
Object set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket)
    Object icp_socket;
{
    Object temp, svref_new_value;
    SI_Long icp_version;

    x_note_fn_call(52,48);
    temp = remote_icp_major_version(icp_socket);
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
    svref_new_value = icp_cons_1(icp_cons_1(Qicp_protocol_version,
	    FIX(icp_version)),ISVREF(icp_socket,(SI_Long)19L));
    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
    return VALUES_1(FIX(icp_version));
}

DEFINE_VARIABLE_WITH_SYMBOL(Initial_icp_version_info_enabled_p, Qinitial_icp_version_info_enabled_p);

DEFINE_VARIABLE_WITH_SYMBOL(Write_initial_icp_version_info_p, Qwrite_initial_icp_version_info_p);

static Object Qinitial;            /* initial */

static Object Qconnect_side_info_sent_but_not_yet_acknowledged;  /* connect-side-info-sent-but-not-yet-acknowledged */

static Object Qtelewindows;        /* telewindows */

static Object Qacknowledge;        /* acknowledge */

static Object Qlisten_side_info_sent_but_no_acknowledge_yet;  /* listen-side-info-sent-but-no-acknowledge-yet */

static Object Qsend;               /* send */

static Object Qreceive;            /* receive */

/* SEND-INITIAL-ICP-VERSION-INFO */
Object send_initial_icp_version_info(icp_socket,connect_p)
    Object icp_socket, connect_p;
{
    Object state_1, gsi_application_name, disable_resumability;
    Object name_for_local_home_1, current_icp_port, current_icp_socket, temp;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, write_initial_icp_version_info_p;
    Object new_state;
    char info_initial_p;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(16);
    Object result;

    x_note_fn_call(52,49);
    state_1 = ISVREF(icp_socket,(SI_Long)18L);
    gsi_application_name = ISVREF(icp_socket,(SI_Long)52L);
    PUSH_SPECIAL_WITH_SYMBOL(Gsi_application_name,Qgsi_application_name,gsi_application_name,
	    15);
      disable_resumability =  ! !TRUEP(ISVREF(icp_socket,(SI_Long)53L)) ? 
	      T : Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
	      14);
	name_for_local_home_1 = name_for_local_home();
	PUSH_SPECIAL_WITH_SYMBOL(Name_for_local_home,Qname_for_local_home,name_for_local_home_1,
		13);
	  info_initial_p = EQ(state_1,Qinitial);
	  if ( !(SYMBOLP(Name_for_local_home) || 
		  INLINE_UNSIGNED_BYTE_16_VECTOR_P(Name_for_local_home) != 
		  (SI_Long)0L))
	      Name_for_local_home = Nil;
	  if (Initial_icp_version_info_enabled_p && (info_initial_p || 
		  EQ(state_1,
		  Qconnect_side_info_sent_but_not_yet_acknowledged))) {
	      current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      12);
		current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			11);
		  temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			  (SI_Long)17L ? ISVREF(Current_icp_socket,
			  (SI_Long)53L) : Nil;
		  if (temp);
		  else
		      temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			      Qtelewindows) ? T : Nil;
		  disable_resumability = temp;
		  PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			  10);
		    number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			    9);
		      icp_buffers_for_message_group = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			      8);
			icp_buffer_of_start_of_message_series_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				7);
			  icp_byte_position_of_start_of_message_series_qm 
				  = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				  6);
			    number_of_icp_bytes_to_fill_buffer = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				    5);
			      current_icp_buffer = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				      4);
				current_write_icp_byte_position = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
					3);
				  number_of_icp_bytes_in_message_group = 
					  FIX((SI_Long)0L);
				  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					  2);
				    writing_icp_message_group = 
					    FIXNUM_ADD1(Writing_icp_message_group);
				    PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					    1);
				      gensymed_symbol = Nil;
				      gensymed_symbol_1 = 0.0;
				      gensymed_symbol_2 = 0.0;
				      if (Profiling_enabled_qm) {
					  gensymed_symbol = T;
					  gensymed_symbol_1 = 
						  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L),(SI_Long)0L);
					  gensymed_symbol_2 = 
						  g2ext_unix_time_as_float();
					  aref_arg_1 = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L);
					  DFLOAT_ISASET_1(aref_arg_1,
						  (SI_Long)0L,
						  gensymed_symbol_2);
				      }
				      if (icp_connection_open_p(Current_icp_socket) 
					      &&  
					      !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						  {
					  write_initial_icp_version_info_p 
						  = info_initial_p ? 
						  Qinitial : Qacknowledge;
					  PUSH_SPECIAL_WITH_SYMBOL(Write_initial_icp_version_info_p,Qwrite_initial_icp_version_info_p,write_initial_icp_version_info_p,
						  0);
					    send_icp_nop(info_initial_p ? 
						    initial_icp_version_info_length_in_icp_bytes() 
						    : 
						    acknowledge_icp_version_info_length_in_icp_bytes());
					  POP_SPECIAL();
					  end_icp_message_group();
				      }
				      if (Profiling_enabled_qm) {
					  gensymed_symbol_3 = 
						  g2ext_unix_time_as_float();
					  gensymed_symbol_4 = 
						  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L),(SI_Long)0L);
					  gensymed_symbol_5 = 
						  gensymed_symbol_3 - 
						  gensymed_symbol_4;
					  aref_arg_1 = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)6L);
					  aref_new_value = 
						  gensymed_symbol_5 + 
						  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						  (SI_Long)6L),(SI_Long)0L);
					  DFLOAT_ISASET_1(aref_arg_1,
						  (SI_Long)0L,aref_new_value);
					  aref_arg_1 = 
						  ISVREF(Profiling_enabled_qm,
						  (SI_Long)2L);
					  aref_new_value = gensymed_symbol 
						  ? gensymed_symbol_1 + 
						  gensymed_symbol_5 + 
						  (gensymed_symbol_4 - 
						  gensymed_symbol_2) : 
						  gensymed_symbol_3;
					  DFLOAT_ISASET_1(aref_arg_1,
						  (SI_Long)0L,aref_new_value);
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
	      new_state = EQ(state_1,Qinitial) ? (connect_p ? 
		      Qconnect_side_info_sent_but_not_yet_acknowledged : 
		      Qlisten_side_info_sent_but_no_acknowledge_yet) : Qt;
	      SVREF(icp_socket,FIX((SI_Long)18L)) = new_state;
	      if (EQ(state_1,
		      Qconnect_side_info_sent_but_not_yet_acknowledged) || 
		      EQ(new_state,
		      Qlisten_side_info_sent_but_no_acknowledge_yet))
		  finalize_icp_version_info(icp_socket,Qsend);
	      if (EQ(state_1,Qconnect_side_info_sent_but_not_yet_acknowledged))
		  result = finalize_icp_version_info(icp_socket,Qreceive);
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

static Object Qno_icp_version_info;  /* no-icp-version-info */

/* ENSURE-REMOTE-ICP-VERSION-INFO */
Object ensure_remote_icp_version_info(icp_socket,handler_name)
    Object icp_socket, handler_name;
{
    Object svref_new_value;

    x_note_fn_call(52,50);
    if (Initial_icp_version_info_enabled_p) {
	if ( !TRUEP(ISVREF(icp_socket,(SI_Long)19L))) {
	    svref_new_value = icp_cons_1(icp_cons_1(Qno_icp_version_info,
		    Nil),Nil);
	    SVREF(icp_socket,FIX((SI_Long)19L)) = svref_new_value;
	}
    }
    return VALUES_1(Nil);
}

/* MAYBE-UPDATE-REMOTE-ICP-VERSION-INFO-FOR-VERSION */
Object maybe_update_remote_icp_version_info_for_version(icp_socket,
	    major_version,minor_version)
    Object icp_socket, major_version, minor_version;
{
    x_note_fn_call(52,51);
    maybe_update_remote_icp_version_info(icp_socket,major_version,
	    Qmajor_version_number_of_current_gensym_product_line);
    maybe_update_remote_icp_version_info(icp_socket,minor_version,
	    Qminor_version_number_of_current_gensym_product_line);
    if (assq_function(Qno_icp_version_info,ISVREF(icp_socket,(SI_Long)19L))) {
	set_remote_icp_protocol_version_from_major_and_minor_version(icp_socket);
	finalize_icp_version_info(icp_socket,Qsend);
	return finalize_icp_version_info(icp_socket,Qreceive);
    }
    else
	return VALUES_1(Nil);
}

/* MAYBE-UPDATE-REMOTE-ICP-VERSION-INFO */
Object maybe_update_remote_icp_version_info(icp_socket,value,symbol)
    Object icp_socket, value, symbol;
{
    Object temp, temp_1, cdr_new_value;

    x_note_fn_call(52,52);
    if ( !TRUEP(ISVREF(icp_socket,(SI_Long)19L))) {
	temp = icp_cons_1(icp_cons_1(Qno_icp_version_info,Nil),Nil);
	SVREF(icp_socket,FIX((SI_Long)19L)) = temp;
    }
    temp_1 = ISVREF(icp_socket,(SI_Long)19L);
    if (EQ(CAAR(temp_1),Qno_icp_version_info)) {
	temp = ISVREF(icp_socket,(SI_Long)19L);
	temp_1 = ISVREF(icp_socket,(SI_Long)19L);
	cdr_new_value = icp_cons_1(icp_cons_1(symbol,value),CDR(temp_1));
	return VALUES_1(M_CDR(temp) = cdr_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* FINALIZE-ICP-VERSION-INFO */
Object finalize_icp_version_info(icp_socket,direction)
    Object icp_socket, direction;
{
    Object svref_new_value;

    x_note_fn_call(52,53);
    if (EQ(direction,Qreceive)) {
	svref_new_value = remote_icp_protocol_version(icp_socket);
	SVREF(icp_socket,FIX((SI_Long)21L)) = svref_new_value;
    }
    else if (EQ(direction,Qsend)) {
	svref_new_value = remote_icp_protocol_version(icp_socket);
	SVREF(icp_socket,FIX((SI_Long)22L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* RECEIVE-INITIAL-MESSAGE */
Object receive_initial_message(local_system,remote_system)
    Object local_system, remote_system;
{
    x_note_fn_call(52,54);
    if (Send_logbook_messages_to_console_p)
	describe_icp_connection(Current_icp_socket);
    return VALUES_1(Nil);
}

static Object Qab;                 /* ab */

static Object string_constant_5;   /* "?" */

static Object string_constant_6;   /* "ICP connection: ~A, local: ~A, remote: ~A, version: ~A ~A ~A ~A ~A" */

/* DESCRIBE-ICP-CONNECTION */
Object describe_icp_connection(icp_socket)
    Object icp_socket;
{
    Object local_system_name, temp, temp_1, temp_2, temp_3, temp_4, temp_5;
    Object temp_6;

    x_note_fn_call(52,55);
    local_system_name = ISVREF(icp_socket,(SI_Long)49L);
    temp = ISVREF(icp_socket,(SI_Long)2L);
    temp_1 = EQ(local_system_name,Qab) ? Qg2 : local_system_name;
    temp_2 = ISVREF(icp_socket,(SI_Long)25L);
    temp_3 = remote_icp_major_version(icp_socket);
    temp_4 = remote_icp_minor_version(icp_socket);
    temp_5 = get_remote_icp_version_info_value(icp_socket,
	    Qrevision_number_of_current_gensym_product_line,FIX((SI_Long)0L));
    temp_6 = get_remote_icp_version_info_value(icp_socket,
	    Qbuild_identification_string,string_constant_5);
    return notify_user_at_console(9,string_constant_6,temp,temp_1,temp_2,
	    temp_3,temp_4,temp_5,temp_6,
	    remote_icp_protocol_version(icp_socket));
}

/* INITIAL-ICP-VERSION-INFO-LENGTH-IN-ICP-BYTES */
Object initial_icp_version_info_length_in_icp_bytes()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp, incff_1_arg;
    SI_Long size, gensymed_symbol;

    x_note_fn_call(52,56);
    size = (SI_Long)0L;
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = Icp_version_info_alist;
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
    incff_1_arg = icp_version_info_element_length_in_icp_bytes(type_code,
	    symbol,type,systems);
    size = size + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    gensymed_symbol = size;
    goto end_1;
    gensymed_symbol = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol + (SI_Long)1L));
}

/* ACKNOWLEDGE-ICP-VERSION-INFO-LENGTH-IN-ICP-BYTES */
Object acknowledge_icp_version_info_length_in_icp_bytes()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp, incff_1_arg;
    SI_Long size, gensymed_symbol;

    x_note_fn_call(52,57);
    size = (SI_Long)0L;
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = Icp_acknowledge_version_info_alist;
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
    incff_1_arg = icp_version_info_element_length_in_icp_bytes(type_code,
	    symbol,type,systems);
    size = size + IFIX(incff_1_arg);
    goto next_loop;
  end_loop:
    gensymed_symbol = size;
    goto end_1;
    gensymed_symbol = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol + (SI_Long)1L));
}

/* WRITE-INITIAL-ICP-VERSION-INFO */
Object write_initial_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(52,58);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = Icp_version_info_alist;
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
    write_icp_version_info_element(type_code,symbol,type,systems);
    goto next_loop;
  end_loop:;
    return write_icp_byte(FIX((SI_Long)0L));
}

/* WRITE-ACKNOWLEDGE-ICP-VERSION-INFO */
Object write_acknowledge_icp_version_info()
{
    Object type_code, symbol, type, systems, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(52,59);
    type_code = Nil;
    symbol = Nil;
    type = Nil;
    systems = Nil;
    ab_loop_list_ = Icp_acknowledge_version_info_alist;
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
    write_icp_version_info_element(type_code,symbol,type,systems);
    goto next_loop;
  end_loop:;
    return write_icp_byte(FIX((SI_Long)0L));
}

/* ICP-VERSION-INFO-ELEMENT-VALUE */
Object icp_version_info_element_value(symbol,type,systems)
    Object symbol, type, systems;
{
    Object systemp, value;
    char temp;

    x_note_fn_call(52,60);
    systemp =  !TRUEP(systems) ? T : Nil;
    if (systemp);
    else
	systemp = memq_function(Current_system_name,systems);
    value =  !(EQ(type,Qnull) ||  !TRUEP(systemp)) ? (EQ(symbol,
	    Qdisable_resumability) ? ( ! !TRUEP(ISVREF(Current_icp_socket,
	    (SI_Long)53L)) ? T : Nil) : SYMBOL_VALUE(symbol)) : Nil;
    if (symbol && systemp) {
	if (EQ(type,Qnull))
	    temp = TRUEP(T);
	else if (EQ(type,Qfixnum))
	    temp = FIXNUMP(value);
	else if (EQ(type,Qgensym_string) || EQ(type,Qwide_string)) {
	    temp = STRINGP(value);
	    if (temp);
	    else
		temp = TRUEP(text_string_p(value));
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
Object write_icp_version_info_element(type_code,symbol,type,systems)
    Object type_code, symbol, type, systems;
{
    Object value, write_p, length_1, value_1, temp_string;
    Object result;

    x_note_fn_call(52,61);
    result = icp_version_info_element_value(symbol,type,systems);
    MVS_2(result,value,write_p);
    if (write_p) {
	result = icp_version_info_element_length_in_icp_bytes_1(type,value);
	MVS_3(result,length_1,value_1,temp_string);
	write_icp_byte(FIX((IFIX(type_code) << (SI_Long)10L) + 
		IFIX(length_1)));
	if (EQ(type,Qnull));
	else if (EQ(type,Qfixnum))
	    write_icp_fixnum(value_1);
	else if (EQ(type,Qgensym_string) || EQ(type,Qsymbol))
	    write_icp_gensym_string(value_1);
	else if (EQ(type,Qwide_string))
	    write_icp_wide_string(value_1);
	if (temp_string)
	    reclaim_text_or_gensym_string(temp_string);
	return VALUES_1(value);
    }
    else
	return VALUES_1(Nil);
}

/* ICP-VERSION-INFO-ELEMENT-LENGTH-IN-ICP-BYTES */
Object icp_version_info_element_length_in_icp_bytes(type_code,symbol,type,
	    systems)
    Object type_code, symbol, type, systems;
{
    Object value, write_p, temp, length_1, temp_1, temp_string;
    Object result;

    x_note_fn_call(52,62);
    result = icp_version_info_element_value(symbol,type,systems);
    MVS_2(result,value,write_p);
    if (write_p) {
	result = icp_version_info_element_length_in_icp_bytes_1(type,value);
	MVS_3(result,length_1,temp_1,temp_string);
	if (temp_string)
	    reclaim_text_or_gensym_string(temp_string);
	temp_1 = FIXNUM_ADD1(length_1);
    }
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(temp_1);
}

/* ICP-VERSION-INFO-ELEMENT-LENGTH-IN-ICP-BYTES-1 */
Object icp_version_info_element_length_in_icp_bytes_1(type,value)
    Object type, value;
{
    Object temp_string, length_1;

    x_note_fn_call(52,63);
    temp_string = Nil;
    if (EQ(type,Qnull))
	length_1 = FIX((SI_Long)0L);
    else if (EQ(type,Qfixnum))
	length_1 = fixnum_length_in_icp_bytes(value);
    else if (EQ(type,Qgensym_string) || EQ(type,Qsymbol)) {
	if (SYMBOLP(value))
	    value = SYMBOL_NAME(value);
	else if (STRINGP(value));
	else {
	    temp_string = wide_string_to_gensym_string(value);
	    value = temp_string;
	}
	length_1 = gensym_string_length_in_icp_bytes(value);
    }
    else if (EQ(type,Qwide_string)) {
	if (!text_string_p(value)) {
	    temp_string = gensym_string_to_wide_string(value);
	    value = temp_string;
	}
	length_1 = wide_string_length_in_icp_bytes(value);
    }
    else
	length_1 = Qnil;
    return VALUES_3(length_1,value,temp_string);
}

/* READ-INITIAL-ICP-VERSION-INFO */
Object read_initial_icp_version_info(total_number_of_bytes_init)
    Object total_number_of_bytes_init;
{
    Object alist, type_code, size, info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    SI_Long total_number_of_bytes, first_byte, type_plus_size;

    x_note_fn_call(52,64);
    total_number_of_bytes = IFIX(total_number_of_bytes_init);
    if ((SI_Long)0L < total_number_of_bytes) {
	first_byte = IFIX(read_icp_byte());
	if ((SI_Long)0L == first_byte)
	    return read_icp_version_info_skip(FIX(total_number_of_bytes));
	else {
	    alist = Icp_version_info_alist;
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
	    info = read_icp_version_info_element(type_code,size,alist);
	    if (info) {
		ab_loopvar__2 = icp_cons_1(info,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    type_plus_size = IFIX(read_icp_byte());
	    goto next_loop;
	  end_loop:
	    return VALUES_1(ab_loopvar_);
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qacknowledge_version_info_receipt;  /* acknowledge-version-info-receipt */

/* READ-ACKNOWLEDGE-ICP-VERSION-INFO */
Object read_acknowledge_icp_version_info(total_number_of_bytes_init)
    Object total_number_of_bytes_init;
{
    Object alist, type_code, size, element, temp, svref_arg_1;
    SI_Long total_number_of_bytes, first_byte, type_plus_size;

    x_note_fn_call(52,65);
    total_number_of_bytes = IFIX(total_number_of_bytes_init);
    if ((SI_Long)0L < total_number_of_bytes) {
	first_byte = IFIX(read_icp_byte());
	if ((SI_Long)0L == first_byte)
	    return read_icp_version_info_skip(FIX(total_number_of_bytes));
	else {
	    alist = Icp_acknowledge_version_info_alist;
	    type_plus_size = first_byte;
	    type_code = Nil;
	    size = Nil;
	    element = Nil;
	  next_loop:
	    if ((SI_Long)0L == type_plus_size)
		goto end_loop;
	    type_code = FIX(type_plus_size >>  -  - (SI_Long)10L);
	    size = FIX(type_plus_size & (SI_Long)1023L);
	    element = read_icp_version_info_element(type_code,size,alist);
	    temp = CAR(element);
	    if (EQ(temp,Qacknowledge_version_info_receipt)) {
		svref_arg_1 = Current_icp_socket;
		SVREF(svref_arg_1,FIX((SI_Long)18L)) = T;
		finalize_icp_version_info(Current_icp_socket,Qreceive);
	    }
	    reclaim_icp_version_info_element(element);
	    type_plus_size = IFIX(read_icp_byte());
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* READ-ICP-VERSION-INFO-SKIP */
Object read_icp_version_info_skip(total_number_of_bytes)
    Object total_number_of_bytes;
{
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(52,66);
    count_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(total_number_of_bytes);
  next_loop:
    if (count_1 >= ab_loop_bind_)
	goto end_loop;
    read_icp_byte();
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* READ-ICP-VERSION-INFO-ELEMENT */
Object read_icp_version_info_element(type_code,byte_count,alist)
    Object type_code, byte_count, alist;
{
    Object info, symbol, type, temp;

    x_note_fn_call(52,67);
    info = assoc_eql(type_code,alist);
    symbol = CADR(info);
    type = CADDR(info);
    if (EQ(type,Qnull))
	temp = icp_cons_1(symbol,Nil);
    else if (EQ(type,Qfixnum))
	temp = icp_cons_1(symbol,read_icp_fixnum());
    else if (EQ(type,Qgensym_string))
	temp = icp_cons_1(symbol,read_icp_gensym_string());
    else if (EQ(type,Qwide_string))
	temp = icp_cons_1(symbol,read_icp_wide_string());
    else if (EQ(type,Qsymbol))
	temp = icp_cons_1(symbol,intern_gensym_string(1,
		read_icp_gensym_string()));
    else {
	read_icp_fill_bytes(byte_count);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* RECLAIM-ICP-VERSION-INFO-ELEMENT */
Object reclaim_icp_version_info_element(element)
    Object element;
{
    Object v;

    x_note_fn_call(52,68);
    v = CDR(element);
    if (STRINGP(v))
	reclaim_gensym_string(v);
    else if (text_string_p(v))
	reclaim_text_string(v);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(v) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(v)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(v);
    reclaim_icp_cons_1(element);
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-VERSION-INFO */
Object reclaim_icp_version_info(version_info)
    Object version_info;
{
    Object info, ab_loop_list_;

    x_note_fn_call(52,69);
    info = Nil;
    ab_loop_list_ = version_info;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_icp_version_info_element(info);
    goto next_loop;
  end_loop:;
    reclaim_icp_list_1(version_info);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qdo_not_use;         /* do-not-use */

/* MAYBE-SET-CONNECTION-NAME */
Object maybe_set_connection_name(icp_socket)
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

    x_note_fn_call(52,70);
    name = stringw(ISVREF(icp_socket,(SI_Long)2L));
    limit1 = (SI_Long)8L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(name));
    name_length = UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(name,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    accept_pos = limit1 < name_length ? search(4,array_constant,name,Kend1,
	    FIX(limit1)) : Nil;
    remote_name = get_remote_host_name(Current_icp_socket);
    if (accept_pos && remote_name) {
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
		  i = (SI_Long)0L;
		  ab_loop_bind_ = IFIX(accept_pos);
		  char_1 = Nil;
		next_loop:
		  if (i >= ab_loop_bind_)
		      goto end_loop;
		  char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = char_1;
		      twrite_wide_character(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = char_1;
		      schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			      CHAR_CODE(thing) : thing);
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop;
		end_loop:;
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing_1 = (SI_Long)58L;
		      twrite_wide_character(CHARACTERP(FIX(thing_1)) ? 
			      CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing_1 = (SI_Long)58L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing_1)) 
			      ? CHAR_CODE(FIX(thing_1)) : FIX(thing_1));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  twrite_general_string(remote_name);
		  new_connection_name = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	reclaim_text_or_gensym_string(ISVREF(icp_socket,(SI_Long)2L));
	SVREF(icp_socket,FIX((SI_Long)2L)) = new_connection_name;
	c_set_connection_pathname(ISVREF(ISVREF(icp_socket,(SI_Long)3L),
		(SI_Long)1L),new_connection_name);
    }
    return VALUES_1(ISVREF(icp_socket,(SI_Long)2L));
}

static Object Qdefault;            /* default */

static Object Qread_icp_number_of_icp_bytes_of_fill;  /* read-icp-number-of-icp-bytes-of-fill */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* READ-ICP-NUMBER-OF-ICP-BYTES-OF-FILL */
Object read_icp_number_of_icp_bytes_of_fill()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object number_of_icp_bytes_of_fill, temp, result_of_read, svref_arg_1;
    Object svref_new_value, resumable_icp_state_1, icp_suspend_1, top, value;
    Object test, v1, v2, v3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,71);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes_of_fill,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      number_of_icp_bytes_of_fill = read_icp_byte();
	      temp = ISVREF(Current_icp_socket,(SI_Long)19L);
	      if (EQ(CAAR(temp),Qno_icp_version_info))
		  result_of_read = 
			  read_icp_fill_bytes(number_of_icp_bytes_of_fill);
	      else if ( !TRUEP(ISVREF(Current_icp_socket,(SI_Long)19L))) {
		  svref_arg_1 = Current_icp_socket;
		  svref_new_value = 
			  read_initial_icp_version_info(number_of_icp_bytes_of_fill);
		  SVREF(svref_arg_1,FIX((SI_Long)19L)) = svref_new_value;
		  svref_arg_1 = Current_icp_socket;
		  svref_new_value = 
			  get_remote_icp_version_info_value(Current_icp_socket,
			  Qgsi_application_name,Qdefault);
		  SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
		  svref_arg_1 = Current_icp_socket;
		  svref_new_value = 
			  get_remote_icp_version_info_value(Current_icp_socket,
			  Qdisable_resumability,Nil);
		  SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
		  if (ISVREF(Current_icp_socket,(SI_Long)19L)) {
		      send_initial_icp_version_info(Current_icp_socket,Nil);
		      result_of_read = 
			      maybe_set_connection_name(Current_icp_socket);
		  }
		  else {
		      svref_arg_1 = Current_icp_socket;
		      result_of_read = 
			      icp_cons_1(icp_cons_1(Qno_icp_version_info,
			      Nil),Nil);
		      SVREF(svref_arg_1,FIX((SI_Long)19L)) = result_of_read;
		  }
	      }
	      else
		  result_of_read = 
			  read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnumber_of_icp_bytes_of_fill,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    number_of_icp_bytes_of_fill = read_icp_byte();
	    temp = ISVREF(Current_icp_socket,(SI_Long)19L);
	    if (EQ(CAAR(temp),Qno_icp_version_info))
		temp = read_icp_fill_bytes(number_of_icp_bytes_of_fill);
	    else if ( !TRUEP(ISVREF(Current_icp_socket,(SI_Long)19L))) {
		svref_arg_1 = Current_icp_socket;
		svref_new_value = 
			read_initial_icp_version_info(number_of_icp_bytes_of_fill);
		SVREF(svref_arg_1,FIX((SI_Long)19L)) = svref_new_value;
		svref_arg_1 = Current_icp_socket;
		svref_new_value = 
			get_remote_icp_version_info_value(Current_icp_socket,
			Qgsi_application_name,Qdefault);
		SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
		svref_arg_1 = Current_icp_socket;
		svref_new_value = 
			get_remote_icp_version_info_value(Current_icp_socket,
			Qdisable_resumability,Nil);
		SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
		if (ISVREF(Current_icp_socket,(SI_Long)19L)) {
		    send_initial_icp_version_info(Current_icp_socket,Nil);
		    temp = maybe_set_connection_name(Current_icp_socket);
		}
		else {
		    svref_arg_1 = Current_icp_socket;
		    temp = icp_cons_1(icp_cons_1(Qno_icp_version_info,Nil),
			    Nil);
		    SVREF(svref_arg_1,FIX((SI_Long)19L)) = temp;
		}
	    }
	    else
		temp = 
			read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_number_of_icp_bytes_of_fill,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_number_of_icp_bytes_of_fill,top,Nil);
		goto end_read_icp_number_of_icp_bytes_of_fill;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes_of_fill,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  number_of_icp_bytes_of_fill = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_number_of_icp_bytes_of_fill;
		  }
		  number_of_icp_bytes_of_fill = value;
	      }
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  temp_1 = EQ(test,Qtrue);
	      else {
		  temp = ISVREF(Current_icp_socket,(SI_Long)19L);
		  temp_1 = EQ(CAAR(temp),Qno_icp_version_info);
	      }
	      if (temp_1) {
		  value = read_icp_fill_bytes(number_of_icp_bytes_of_fill);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(number_of_icp_bytes_of_fill);
		      resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_number_of_icp_bytes_of_fill;
		  }
		  result_of_read = value;
	      }
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      test = resumable_icp_pop();
		      temp_1 = TRUEP(test);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1 ? EQ(test,Qtrue) :  
			  !TRUEP(ISVREF(Current_icp_socket,(SI_Long)19L))) {
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp = resumable_icp_pop();
			  if (! !(FIXNUMP(temp) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		      svref_arg_1 = Current_icp_socket;
		      value = 
			      read_initial_icp_version_info(number_of_icp_bytes_of_fill);
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		      SVREF(svref_arg_1,FIX((SI_Long)19L)) = value;
		      svref_arg_1 = Current_icp_socket;
		      svref_new_value = 
			      get_remote_icp_version_info_value(Current_icp_socket,
			      Qgsi_application_name,Qdefault);
		      SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
		      svref_arg_1 = Current_icp_socket;
		      svref_new_value = 
			      get_remote_icp_version_info_value(Current_icp_socket,
			      Qdisable_resumability,Nil);
		      SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
		    l2:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) || 
			      ISVREF(Current_icp_socket,(SI_Long)19L)) {
			  if (EQ(icp_suspend_1,
				  send_initial_icp_version_info(Current_icp_socket,
				  Nil))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block;
			  }
			  result = maybe_set_connection_name(Current_icp_socket);
		      }
		      else if (T) {
			  svref_arg_1 = Current_icp_socket;
			  svref_new_value = 
				  icp_cons_1(icp_cons_1(Qno_icp_version_info,
				  Nil),Nil);
			  result = VALUES_1(SVREF(svref_arg_1,
				  FIX((SI_Long)19L)) = svref_new_value);
		      }
		      else
			  result = VALUES_1(Nil);
		      goto end_block;
		    end_block:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(Qtrue);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(number_of_icp_bytes_of_fill);
			  resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_number_of_icp_bytes_of_fill;
		      }
		      temp = v1;
		      result_of_read = temp;
		  }
		  else if ((resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) || T) {
		      value = 
			      read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(number_of_icp_bytes_of_fill);
			  resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_number_of_icp_bytes_of_fill;
		      }
		      result_of_read = value;
		  }
		  else
		      result_of_read = Qnil;
	      }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qnumber_of_icp_bytes_of_fill,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		number_of_icp_bytes_of_fill = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_number_of_icp_bytes_of_fill;
		}
		number_of_icp_bytes_of_fill = value;
	    }
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		temp_1 = EQ(test,Qtrue);
	    else {
		temp = ISVREF(Current_icp_socket,(SI_Long)19L);
		temp_1 = EQ(CAAR(temp),Qno_icp_version_info);
	    }
	    if (temp_1) {
		value = read_icp_fill_bytes(number_of_icp_bytes_of_fill);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(number_of_icp_bytes_of_fill);
		    resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_number_of_icp_bytes_of_fill;
		}
		temp = value;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) :  
			!TRUEP(ISVREF(Current_icp_socket,(SI_Long)19L))) {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
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
		    svref_arg_1 = Current_icp_socket;
		    value = 
			    read_initial_icp_version_info(number_of_icp_bytes_of_fill);
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		    SVREF(svref_arg_1,FIX((SI_Long)19L)) = value;
		    svref_arg_1 = Current_icp_socket;
		    svref_new_value = 
			    get_remote_icp_version_info_value(Current_icp_socket,
			    Qgsi_application_name,Qdefault);
		    SVREF(svref_arg_1,FIX((SI_Long)52L)) = svref_new_value;
		    svref_arg_1 = Current_icp_socket;
		    svref_new_value = 
			    get_remote_icp_version_info_value(Current_icp_socket,
			    Qdisable_resumability,Nil);
		    SVREF(svref_arg_1,FIX((SI_Long)53L)) = svref_new_value;
		  l2_1:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) || 
			    ISVREF(Current_icp_socket,(SI_Long)19L)) {
			if (EQ(icp_suspend_1,
				send_initial_icp_version_info(Current_icp_socket,
				Nil))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_1;
			}
			result = maybe_set_connection_name(Current_icp_socket);
		    }
		    else if (T) {
			svref_arg_1 = Current_icp_socket;
			svref_new_value = 
				icp_cons_1(icp_cons_1(Qno_icp_version_info,
				Nil),Nil);
			result = VALUES_1(SVREF(svref_arg_1,
				FIX((SI_Long)19L)) = svref_new_value);
		    }
		    else
			result = VALUES_1(Nil);
		    goto end_block_1;
		  end_block_1:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(number_of_icp_bytes_of_fill);
			resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_number_of_icp_bytes_of_fill;
		    }
		    temp = v1;
		}
		else if ((resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) || T) {
		    value = 
			    read_acknowledge_icp_version_info(number_of_icp_bytes_of_fill);
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qfalse);
			resumable_icp_push(Qfalse);
			resumable_icp_push(number_of_icp_bytes_of_fill);
			resumable_icp_push(Qread_icp_number_of_icp_bytes_of_fill);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_number_of_icp_bytes_of_fill;
		    }
		    temp = value;
		}
		else
		    temp = Qnil;
	    }
	}
    }
    result = VALUES_1(temp);
  end_read_icp_number_of_icp_bytes_of_fill:
    return result;
}

/* READ-ICP-FILL-BYTES */
Object read_icp_fill_bytes(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object number_of_icp_bytes_to_skip;

    x_note_fn_call(52,72);
    number_of_icp_bytes_to_skip = number_of_icp_bytes_of_fill;
  next_loop:
    if ( !(IFIX(number_of_icp_bytes_to_skip) > (SI_Long)0L))
	goto end_loop;
    read_icp_byte();
    number_of_icp_bytes_to_skip = FIXNUM_SUB1(number_of_icp_bytes_to_skip);
    goto next_loop;
  end_loop:;
    return VALUES_1(number_of_icp_bytes_of_fill);
}

/* WRITE-ICP-FILL-BYTES */
Object write_icp_fill_bytes(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    x_note_fn_call(52,73);
  next_loop:
    if ( !(IFIX(number_of_icp_bytes_of_fill) > (SI_Long)0L))
	goto end_loop;
    write_icp_byte(FIX((SI_Long)0L));
    number_of_icp_bytes_of_fill = FIXNUM_SUB1(number_of_icp_bytes_of_fill);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qwrite_icp_number_of_icp_bytes_of_fill;  /* write-icp-number-of-icp-bytes-of-fill */

/* WRITE-ICP-NUMBER-OF-ICP-BYTES-OF-FILL */
Object write_icp_number_of_icp_bytes_of_fill(number_of_icp_bytes_of_fill)
    Object number_of_icp_bytes_of_fill;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object key, value, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,74);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qnumber_of_icp_bytes_of_fill,string_constant_4,
			Qvalue,T,number_of_icp_bytes_of_fill,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      write_icp_byte(number_of_icp_bytes_of_fill);
	      if (EQ(Write_initial_icp_version_info_p,Qinitial))
		  result_of_write = write_initial_icp_version_info();
	      else if (EQ(Write_initial_icp_version_info_p,Qacknowledge))
		  result_of_write = write_acknowledge_icp_version_info();
	      else
		  result_of_write = 
			  write_icp_fill_bytes(number_of_icp_bytes_of_fill);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnumber_of_icp_bytes_of_fill,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    write_icp_byte(number_of_icp_bytes_of_fill);
	    if (EQ(Write_initial_icp_version_info_p,Qinitial))
		temp = write_initial_icp_version_info();
	    else if (EQ(Write_initial_icp_version_info_p,Qacknowledge))
		temp = write_acknowledge_icp_version_info();
	    else
		temp = write_icp_fill_bytes(number_of_icp_bytes_of_fill);
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_number_of_icp_bytes_of_fill,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_number_of_icp_bytes_of_fill,top,Nil);
		goto end_write_icp_number_of_icp_bytes_of_fill;
	    }
	}
	number_of_icp_bytes_of_fill = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : number_of_icp_bytes_of_fill;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qnumber_of_icp_bytes_of_fill,string_constant_4,
			Qvalue,T,number_of_icp_bytes_of_fill,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp = resumable_icp_pop();
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
	      if (EQ(icp_suspend_1,
		      write_icp_byte(number_of_icp_bytes_of_fill))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Write_initial_icp_version_info_p;
	      if (EQ(key,Qinitial)) {
		  value = write_initial_icp_version_info();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(key);
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		  result = VALUES_1(value);
	      }
	      else if (EQ(key,Qacknowledge)) {
		  value = write_acknowledge_icp_version_info();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(key);
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		  result = VALUES_1(value);
	      }
	      else {
		  value = write_icp_fill_bytes(number_of_icp_bytes_of_fill);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(key);
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		  result = VALUES_1(value);
	      }
	      goto end_block;
	    end_block:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(number_of_icp_bytes_of_fill);
		  resumable_icp_push(Qwrite_icp_number_of_icp_bytes_of_fill);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_number_of_icp_bytes_of_fill;
	      }
	      temp = v1;
	      result_of_write = temp;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qnumber_of_icp_bytes_of_fill,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		temp = resumable_icp_pop();
		if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(temp)) {
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
			write_icp_byte(number_of_icp_bytes_of_fill))) {
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Write_initial_icp_version_info_p;
	    if (EQ(key,Qinitial)) {
		value = write_initial_icp_version_info();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(key);
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
		result = VALUES_1(value);
	    }
	    else if (EQ(key,Qacknowledge)) {
		value = write_acknowledge_icp_version_info();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(key);
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
		result = VALUES_1(value);
	    }
	    else {
		value = write_icp_fill_bytes(number_of_icp_bytes_of_fill);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(key);
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
		result = VALUES_1(value);
	    }
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		resumable_icp_push(number_of_icp_bytes_of_fill);
		resumable_icp_push(Qwrite_icp_number_of_icp_bytes_of_fill);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_number_of_icp_bytes_of_fill;
	    }
	    temp = v1;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_number_of_icp_bytes_of_fill:
    return result;
}

static Object Qunsigned_integer_or_nil;  /* unsigned-integer-or-nil */

static Object Qwrite_icp_unsigned_integer_or_nil;  /* write-icp-unsigned-integer-or-nil */

/* WRITE-ICP-UNSIGNED-INTEGER-OR-NIL */
Object write_icp_unsigned_integer_or_nil(unsigned_integer_or_nil)
    Object unsigned_integer_or_nil;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object test, value;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,75);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qunsigned_integer_or_nil,
			string_constant_4,Qvalue,T,unsigned_integer_or_nil,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write =  !TRUEP(unsigned_integer_or_nil) ? 
		      write_icp_integer(FIX((SI_Long)-1L)) : 
		      write_icp_integer(unsigned_integer_or_nil);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qunsigned_integer_or_nil,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp =  !TRUEP(unsigned_integer_or_nil) ? 
		    write_icp_integer(FIX((SI_Long)-1L)) : 
		    write_icp_integer(unsigned_integer_or_nil);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_unsigned_integer_or_nil,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_unsigned_integer_or_nil,top,Nil);
		goto end_write_icp_unsigned_integer_or_nil;
	    }
	}
	unsigned_integer_or_nil = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : unsigned_integer_or_nil;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qunsigned_integer_or_nil,
			string_constant_4,Qvalue,T,unsigned_integer_or_nil,
			Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) :  !TRUEP(unsigned_integer_or_nil)) {
		  value = write_icp_integer(FIX((SI_Long)-1L));
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(unsigned_integer_or_nil);
		      resumable_icp_push(Qwrite_icp_unsigned_integer_or_nil);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_unsigned_integer_or_nil;
		  }
		  result_of_write = value;
	      }
	      else {
		  value = write_icp_integer(unsigned_integer_or_nil);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qfalse);
		      resumable_icp_push(unsigned_integer_or_nil);
		      resumable_icp_push(Qwrite_icp_unsigned_integer_or_nil);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_unsigned_integer_or_nil;
		  }
		  result_of_write = value;
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qunsigned_integer_or_nil,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) :  !TRUEP(unsigned_integer_or_nil)) {
		value = write_icp_integer(FIX((SI_Long)-1L));
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(unsigned_integer_or_nil);
		    resumable_icp_push(Qwrite_icp_unsigned_integer_or_nil);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_unsigned_integer_or_nil;
		}
		temp = value;
	    }
	    else {
		value = write_icp_integer(unsigned_integer_or_nil);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qfalse);
		    resumable_icp_push(unsigned_integer_or_nil);
		    resumable_icp_push(Qwrite_icp_unsigned_integer_or_nil);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_unsigned_integer_or_nil;
		}
		temp = value;
	    }
	}
    }
    result = VALUES_1(temp);
  end_write_icp_unsigned_integer_or_nil:
    return result;
}

static Object Qread_icp_unsigned_integer_or_nil;  /* read-icp-unsigned-integer-or-nil */

/* READ-ICP-UNSIGNED-INTEGER-OR-NIL */
Object read_icp_unsigned_integer_or_nil()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, value;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,76);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qunsigned_integer_or_nil,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      value = read_icp_integer();
	      result_of_read = IFIX(value) > (SI_Long)-1L ? value : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qunsigned_integer_or_nil,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    value = read_icp_integer();
	    temp = IFIX(value) > (SI_Long)-1L ? value : Nil;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_unsigned_integer_or_nil,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_unsigned_integer_or_nil,top,Nil);
		goto end_read_icp_unsigned_integer_or_nil;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qunsigned_integer_or_nil,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  value = resumable_icp_pop();
	      else {
		  value_1 = read_icp_integer();
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_unsigned_integer_or_nil);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_unsigned_integer_or_nil;
		  }
		  value = value_1;
	      }
	      result_of_read = IFIX(value) > (SI_Long)-1L ? value : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qunsigned_integer_or_nil,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		value = resumable_icp_pop();
	    else {
		value_1 = read_icp_integer();
		if (EQ(icp_suspend_1,value_1)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_unsigned_integer_or_nil);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_unsigned_integer_or_nil;
		}
		value = value_1;
	    }
	    temp = IFIX(value) > (SI_Long)-1L ? value : Nil;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_unsigned_integer_or_nil:
    return result;
}

static Object Qwrite_icp_float;    /* write-icp-float */

/* WRITE-ICP-FLOAT */
Object write_icp_float(float_1)
    Object float_1;
{
    Object tag_temp, tracep, byte_count_before, current_icp_write_trace_level;
    Object temp_1, signif, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, temp_3, value, v1, v2, v3;
    SI_Long expon, sign, signif_int;
    double float_2, arg, arg_1, temp, temp_2;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(52,77);
    tag_temp = UNIQUE_TAG(Qwrite_icp_float);
    if (PUSH_CATCH(tag_temp,0)) {
	if (Disable_resumability) {
	    if (Icp_write_trace_cutoff_level_qm) {
		tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_write_trace(T,Nil,Nil,Qfloat,
			    string_constant_4,Qvalue,T,float_1,Nil,Nil);
		    byte_count_before = instantaneous_icp_writer_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_write_trace_level = 
			FIXNUM_ADD1(Current_icp_write_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
		      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			  if (INLINE_DOUBLE_FLOAT_VECTOR_P(float_1) != 
				  (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_1)) 
				  == (SI_Long)1L)
			      float_2 = DFLOAT_ISAREF_1(float_1,(SI_Long)0L);
			  else
			      float_2 = DOUBLE_FLOAT_TO_DOUBLE(float_1);
			  arg = float_2;
			  arg_1 = 0.0;
			  temp = arg == arg_1 &&  
				  !inline_nanp_for_comparison(arg) &&  
				  !inline_nanp_for_comparison(arg_1) ? 
				  1.0E-37 : float_2;
			  result = ceiling(llog(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp)),
				  FIX((SI_Long)10L)),_);
			  MVS_2(result,temp_1,signif);
			  expon = IFIX(temp_1);
			  arg = float_2;
			  arg_1 = 0.0;
			  sign = arg > arg_1 &&  
				  !inline_nanp_for_comparison(arg) &&  
				  !inline_nanp_for_comparison(arg_1) ? 
				  (SI_Long)1L : (SI_Long)0L;
			  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(signif);
			  temp = 
				  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
			  signif_int = 
				  IFIX(ltruncate(DOUBLE_TO_DOUBLE_FLOAT(temp_2 
				  * temp),_));
			  write_icp_integer(FIX(signif_int));
			  write_icp_integer(FIX(expon));
			  result_of_write = write_icp_byte(FIX(sign));
		      }
		      POP_LOCAL_ALLOCATION(0,0);
		  }
		  POP_LOCAL_ALLOCATION(1,1);
		  if (tracep)
		      emit_icp_write_trace(Nil,byte_count_before,
			      instantaneous_icp_writer_byte_count(),Qfloat,
			      string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		  temp_1 = result_of_write;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(float_1) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_1)) 
				== (SI_Long)1L)
			    float_2 = DFLOAT_ISAREF_1(float_1,(SI_Long)0L);
			else
			    float_2 = DOUBLE_FLOAT_TO_DOUBLE(float_1);
			arg = float_2;
			arg_1 = 0.0;
			temp = arg == arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1) ? 
				1.0E-37 : float_2;
			result = ceiling(llog(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp)),
				FIX((SI_Long)10L)),_);
			MVS_2(result,temp_1,signif);
			expon = IFIX(temp_1);
			arg = float_2;
			arg_1 = 0.0;
			sign = arg > arg_1 &&  
				!inline_nanp_for_comparison(arg) &&  
				!inline_nanp_for_comparison(arg_1) ? 
				(SI_Long)1L : (SI_Long)0L;
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(signif);
			temp = 
				DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
			signif_int = 
				IFIX(ltruncate(DOUBLE_TO_DOUBLE_FLOAT(temp_2 
				* temp),_));
			write_icp_integer(FIX(signif_int));
			write_icp_integer(FIX(expon));
			temp_1 = write_icp_byte(FIX(sign));
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
		POP_LOCAL_ALLOCATION(1,1);
	    }
	}
	else {
	    resumable_icp_state_1 = Resumable_icp_state;
	    icp_suspend_1 = Icp_suspend;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		top = resumable_icp_pop();
		if ( !EQ(Qwrite_icp_float,top)) {
		    result = icp_error_internal(Qerror,string_constant_3,
			    Qwrite_icp_float,top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    float_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		     TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : float_1;
	    if (Icp_write_trace_cutoff_level_qm) {
		tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_write_trace(T,Nil,Nil,Qfloat,
			    string_constant_4,Qvalue,T,float_1,Nil,Nil);
		    byte_count_before = instantaneous_icp_writer_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_write_trace_level = 
			FIXNUM_ADD1(Current_icp_write_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
		      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker())) 
				      {
			      temp_1 = resumable_icp_pop();
			      float_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			  }
			  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(float_1) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_1)) 
				  == (SI_Long)1L)
			      float_2 = DFLOAT_ISAREF_1(float_1,(SI_Long)0L);
			  else
			      float_2 = DOUBLE_FLOAT_TO_DOUBLE(float_1);
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp_3 = resumable_icp_pop();
			      temp_1 = resumable_icp_pop();
			      result = VALUES_2(temp_3,temp_1);
			  }
			  else {
			      arg = float_2;
			      arg_1 = 0.0;
			      temp = arg == arg_1 &&  
				      !inline_nanp_for_comparison(arg) &&  
				      !inline_nanp_for_comparison(arg_1) ? 
				      1.0E-37 : float_2;
			      result = ceiling(llog(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp)),
				      FIX((SI_Long)10L)),_);
			  }
			  MVS_2(result,temp_1,signif);
			  expon = IFIX(temp_1);
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      sign = IFIX(resumable_icp_pop());
			  else {
			      arg = float_2;
			      arg_1 = 0.0;
			      sign = arg > arg_1 &&  
				      !inline_nanp_for_comparison(arg) &&  
				      !inline_nanp_for_comparison(arg_1) ? 
				      (SI_Long)1L : (SI_Long)0L;
			  }
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      signif_int = IFIX(resumable_icp_pop());
			  else {
			      temp_2 = DOUBLE_FLOAT_TO_DOUBLE(signif);
			      temp = 
				      DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
			      signif_int = 
				      IFIX(ltruncate(DOUBLE_TO_DOUBLE_FLOAT(temp_2 
				      * temp),_));
			  }
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp_1 = resumable_icp_pop();
			      if (! !(FIXNUMP(temp_1) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),
				      temp_1) && FIXNUM_LE(temp_1,
				      FIX((SI_Long)127L))))
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
			  if (EQ(icp_suspend_1,
				  write_icp_integer(FIX(signif_int)))) {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block;
			  }
			l2:
			  if (EQ(icp_suspend_1,
				      write_icp_integer(FIX(expon)))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block;
			  }
			l3:
			  value = write_icp_byte(FIX(sign));
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)3L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block;
			  }
			  result = VALUES_1(value);
			  goto end_block;
			end_block:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(FIX(signif_int));
			      resumable_icp_push(FIX(sign));
			      resumable_icp_push(signif);
			      resumable_icp_push(FIX(expon));
			      resumable_icp_push(DOUBLE_TO_DOUBLE_FLOAT(float_2));
			      resumable_icp_push(DOUBLE_TO_DOUBLE_FLOAT(float_2));
			      resumable_icp_push(Qwrite_icp_float);
			      result = VALUES_1(Icp_suspend);
			      THROW(tag_temp,result);
			  }
			  temp_1 = v1;
			  result_of_write = temp_1;
		      }
		      POP_LOCAL_ALLOCATION(0,0);
		  }
		  POP_LOCAL_ALLOCATION(1,1);
		  if (tracep)
		      emit_icp_write_trace(Nil,byte_count_before,
			      instantaneous_icp_writer_byte_count(),Qfloat,
			      string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		  temp_1 = result_of_write;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker())) 
				    {
			    temp_1 = resumable_icp_pop();
			    float_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			}
			else if (INLINE_DOUBLE_FLOAT_VECTOR_P(float_1) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_1)) 
				== (SI_Long)1L)
			    float_2 = DFLOAT_ISAREF_1(float_1,(SI_Long)0L);
			else
			    float_2 = DOUBLE_FLOAT_TO_DOUBLE(float_1);
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp_3 = resumable_icp_pop();
			    temp_1 = resumable_icp_pop();
			    result = VALUES_2(temp_3,temp_1);
			}
			else {
			    arg = float_2;
			    arg_1 = 0.0;
			    temp = arg == arg_1 &&  
				    !inline_nanp_for_comparison(arg) &&  
				    !inline_nanp_for_comparison(arg_1) ? 
				    1.0E-37 : float_2;
			    result = ceiling(llog(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp)),
				    FIX((SI_Long)10L)),_);
			}
			MVS_2(result,temp_1,signif);
			expon = IFIX(temp_1);
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    sign = IFIX(resumable_icp_pop());
			else {
			    arg = float_2;
			    arg_1 = 0.0;
			    sign = arg > arg_1 &&  
				    !inline_nanp_for_comparison(arg) &&  
				    !inline_nanp_for_comparison(arg_1) ? 
				    (SI_Long)1L : (SI_Long)0L;
			}
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    signif_int = IFIX(resumable_icp_pop());
			else {
			    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(signif);
			    temp = 
				    DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
			    signif_int = 
				    IFIX(ltruncate(DOUBLE_TO_DOUBLE_FLOAT(temp_2 
				    * temp),_));
			}
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp_1 = resumable_icp_pop();
			    if (! !(FIXNUMP(temp_1) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) 
				    && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
				write_icp_integer(FIX(signif_int)))) {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_1;
			}
		      l2_1:
			if (EQ(icp_suspend_1,write_icp_integer(FIX(expon)))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_1;
			}
		      l3_1:
			value = write_icp_byte(FIX(sign));
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)3L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_1;
			}
			result = VALUES_1(value);
			goto end_block_1;
		      end_block_1:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(FIX(signif_int));
			    resumable_icp_push(FIX(sign));
			    resumable_icp_push(signif);
			    resumable_icp_push(FIX(expon));
			    resumable_icp_push(DOUBLE_TO_DOUBLE_FLOAT(float_2));
			    resumable_icp_push(DOUBLE_TO_DOUBLE_FLOAT(float_2));
			    resumable_icp_push(Qwrite_icp_float);
			    result = VALUES_1(Icp_suspend);
			    THROW(tag_temp,result);
			}
			temp_1 = v1;
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
		POP_LOCAL_ALLOCATION(1,1);
	    }
	}
	result = VALUES_1(temp_1);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object float_constant;      /* 0.0 */

static Object Qfloat_array;        /* float-array */

static Object Qread_icp_float;     /* read-icp-float */

/* READ-ICP-FLOAT */
Object read_icp_float()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, signif;
    Object expon, sign, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float, temp_5, result_of_read;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    double temp_2, temp_3, temp_4, aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,78);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qfloat,string_constant_4,
			Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      signif = read_icp_integer();
	      expon = read_icp_integer();
	      sign = read_icp_byte();
	      signif = lfloat(signif,float_constant);
	      expon = lfloat(expon,float_constant);
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
		      temp = 
			      ISVREF(Available_float_array_conses_tail_vector,
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
	      if (IFIX(sign) == (SI_Long)0L) {
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		  temp_4 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		  temp_5 = expt(FIX((SI_Long)10L),
			  DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		  temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
		  aref_new_value =  - temp_4;
	      }
	      else {
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		  temp_4 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		  temp_5 = expt(FIX((SI_Long)10L),
			  DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
	      }
	      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	      result_of_read = new_float;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qfloat,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp_5 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    signif = read_icp_integer();
	    expon = read_icp_integer();
	    sign = read_icp_byte();
	    signif = lfloat(signif,float_constant);
	    expon = lfloat(expon,float_constant);
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
	    if (IFIX(sign) == (SI_Long)0L) {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		temp_4 = 
			DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		temp_5 = expt(FIX((SI_Long)10L),
			DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
		aref_new_value =  - temp_4;
	    }
	    else {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		temp_4 = 
			DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		temp_5 = expt(FIX((SI_Long)10L),
			DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
	    }
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_5 = new_float;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_float,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_float,top,Nil);
		goto end_read_icp_float;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qfloat,string_constant_4,
			Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  signif = resumable_icp_pop();
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_float);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_float;
		  }
		  signif = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  expon = resumable_icp_pop();
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(signif);
		      resumable_icp_push(Qread_icp_float);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_float;
		  }
		  expon = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  sign = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(expon);
		      resumable_icp_push(signif);
		      resumable_icp_push(Qread_icp_float);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_float;
		  }
		  sign = value;
	      }
	      signif = lfloat(signif,float_constant);
	      expon = lfloat(expon,float_constant);
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
		      temp = 
			      ISVREF(Available_float_array_conses_tail_vector,
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
	      if (IFIX(sign) == (SI_Long)0L) {
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		  temp_4 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		  temp_5 = expt(FIX((SI_Long)10L),
			  DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		  temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
		  aref_new_value =  - temp_4;
	      }
	      else {
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		  temp_4 = 
			  DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		  temp_5 = expt(FIX((SI_Long)10L),
			  DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
	      }
	      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	      result_of_read = new_float;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qfloat,
			  string_constant_4,Qvalue,T,result_of_read,Nil,Nil);
	      temp_5 = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		signif = resumable_icp_pop();
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_float);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_float;
		}
		signif = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		expon = resumable_icp_pop();
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(signif);
		    resumable_icp_push(Qread_icp_float);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_float;
		}
		expon = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		sign = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(expon);
		    resumable_icp_push(signif);
		    resumable_icp_push(Qread_icp_float);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_float;
		}
		sign = value;
	    }
	    signif = lfloat(signif,float_constant);
	    expon = lfloat(expon,float_constant);
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
	    if (IFIX(sign) == (SI_Long)0L) {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		temp_4 = 
			DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		temp_5 = expt(FIX((SI_Long)10L),
			DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
		aref_new_value =  - temp_4;
	    }
	    else {
		temp_2 = DOUBLE_FLOAT_TO_DOUBLE(expon);
		temp_3 = DOUBLE_FLOAT_TO_DOUBLE(signif);
		temp_4 = 
			DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum32_plus_one_as_float);
		temp_5 = expt(FIX((SI_Long)10L),
			DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3 / temp_4));
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_5);
	    }
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_5 = new_float;
	}
    }
    result = VALUES_1(temp_5);
  end_read_icp_float:
    return result;
}

static Object Qwrite_icp_double_float_using_function;  /* write-icp-double-float-using-function */

/* WRITE-ICP-DOUBLE-FLOAT-USING-FUNCTION */
Object write_icp_double_float_using_function(double_float)
    Object double_float;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Object b0_1, b1_1, b2_1, b3_1, value, v1, v2, v3;
    SI_Long b0, b1, b2, b3;
    double temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,79);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qdouble_float,
			string_constant_4,Qvalue,T,double_float,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	      g2ext_foreign_partition_float(temp,
		      UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	      b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	      b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	      b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	      b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	      write_icp_byte(FIX(b0));
	      write_icp_byte(FIX(b1));
	      write_icp_byte(FIX(b2));
	      result_of_write = write_icp_byte(FIX(b3));
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qdouble_float,string_constant_4,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
	    g2ext_foreign_partition_float(temp,
		    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	    write_icp_byte(FIX(b0));
	    write_icp_byte(FIX(b1));
	    write_icp_byte(FIX(b2));
	    temp_1 = write_icp_byte(FIX(b3));
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_double_float_using_function,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_double_float_using_function,top,Nil);
		goto end_write_icp_double_float_using_function;
	    }
	}
	double_float = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : double_float;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qdouble_float,
			string_constant_4,Qvalue,T,double_float,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))) {
		  temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
		  g2ext_foreign_partition_float(temp,
			  UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	      }
	      b0_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
		      (SI_Long)0L));
	      b1_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
		      (SI_Long)1L));
	      b2_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
		      (SI_Long)2L));
	      b3_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
		      (SI_Long)3L));
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
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
	      if (EQ(icp_suspend_1,write_icp_byte(b0_1))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      if (EQ(icp_suspend_1,write_icp_byte(b1_1))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l3:
	      if (EQ(icp_suspend_1,write_icp_byte(b2_1))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l4:
	      value = write_icp_byte(b3_1);
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	      result = VALUES_1(value);
	      goto end_block;
	    end_block:
	      MVS_3(result,v1,v2,v3);
	      if (EQ(icp_suspend_1,v1)) {
		  resumable_icp_push(b3_1);
		  resumable_icp_push(b2_1);
		  resumable_icp_push(b1_1);
		  resumable_icp_push(b0_1);
		  resumable_icp_push(double_float);
		  resumable_icp_push(Qwrite_icp_double_float_using_function);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_double_float_using_function;
	      }
	      temp_1 = v1;
	      result_of_write = temp_1;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qdouble_float,string_constant_4,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))) {
		temp = DOUBLE_FLOAT_TO_DOUBLE(double_float);
		g2ext_foreign_partition_float(temp,
			UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	    }
	    b0_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : 
		    FIX(UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L));
	    b1_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : 
		    FIX(UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L));
	    b2_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : 
		    FIX(UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L));
	    b3_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : 
		    FIX(UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L));
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		temp_1 = resumable_icp_pop();
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
		      case 4:
			goto l4_1;
			break;
		      default:
			break;
		    }
	    }
	  l1_1:
	    if (EQ(icp_suspend_1,write_icp_byte(b0_1))) {
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    if (EQ(icp_suspend_1,write_icp_byte(b1_1))) {
		resumable_icp_push(FIX((SI_Long)2L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l3_1:
	    if (EQ(icp_suspend_1,write_icp_byte(b2_1))) {
		resumable_icp_push(FIX((SI_Long)3L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l4_1:
	    value = write_icp_byte(b3_1);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(FIX((SI_Long)4L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	    result = VALUES_1(value);
	    goto end_block_1;
	  end_block_1:
	    MVS_3(result,v1,v2,v3);
	    if (EQ(icp_suspend_1,v1)) {
		resumable_icp_push(b3_1);
		resumable_icp_push(b2_1);
		resumable_icp_push(b1_1);
		resumable_icp_push(b0_1);
		resumable_icp_push(double_float);
		resumable_icp_push(Qwrite_icp_double_float_using_function);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_double_float_using_function;
	    }
	    temp_1 = v1;
	}
    }
    result = VALUES_1(temp_1);
  end_write_icp_double_float_using_function:
    return result;
}

/* WRITE-ICP-DOUBLE-FLOAT-1 */
Object write_icp_double_float_1(value)
    double value;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, result_1;
    SI_Long b0, b1, b2, b3;
    Declare_special(1);

    x_note_fn_call(52,80);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qvalue,string_constant_4,Qvalue,
		    T,DOUBLE_TO_DOUBLE_FLOAT(value),Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  g2ext_foreign_partition_float(value,
		  UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	  b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	  b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	  b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	  b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	  write_icp_byte(FIX(b0));
	  write_icp_byte(FIX(b1));
	  write_icp_byte(FIX(b2));
	  result_of_write = write_icp_byte(FIX(b3));
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),Qvalue,
		      string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
	POP_SPECIAL();
    }
    else {
	g2ext_foreign_partition_float(value,
		UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
	b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
	b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
	b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
	b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
	write_icp_byte(FIX(b0));
	write_icp_byte(FIX(b1));
	write_icp_byte(FIX(b2));
	write_icp_byte(FIX(b3));
    }
    result_1 = Nil;
    return result_1;
}

static Object Qread_icp_double_float_using_function;  /* read-icp-double-float-using-function */

/* READ-ICP-DOUBLE-FLOAT-USING-FUNCTION */
Object read_icp_double_float_using_function()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, b0, b1, b2;
    Object b3, temp, resumable_icp_state_1, icp_suspend_1, top, arg1, value;
    Object arg2, arg3, arg4;
    double result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,81);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdouble_float,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      b0 = read_icp_byte();
	      b1 = read_icp_byte();
	      b2 = read_icp_byte();
	      b3 = read_icp_byte();
	      result_of_read = g2ext_foreign_reconstruct_float(IFIX(b0),
		      IFIX(b1),IFIX(b2),IFIX(b3));
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdouble_float,string_constant_4,Qvalue,T,
			  DOUBLE_TO_DOUBLE_FLOAT(result_of_read),Nil,Nil);
	      temp = DOUBLE_TO_DOUBLE_FLOAT(result_of_read);
	    POP_SPECIAL();
	}
	else {
	    b0 = read_icp_byte();
	    b1 = read_icp_byte();
	    b2 = read_icp_byte();
	    b3 = read_icp_byte();
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(g2ext_foreign_reconstruct_float(IFIX(b0),
		    IFIX(b1),IFIX(b2),IFIX(b3)));
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_double_float_using_function,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_double_float_using_function,top,Nil);
		goto end_read_icp_double_float_using_function;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdouble_float,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_double_float_using_function);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_double_float_using_function;
		  }
		  arg1 = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg2 = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(arg1);
		      resumable_icp_push(Qread_icp_double_float_using_function);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_double_float_using_function;
		  }
		  arg2 = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg3 = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(arg2);
		      resumable_icp_push(arg1);
		      resumable_icp_push(Qread_icp_double_float_using_function);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_double_float_using_function;
		  }
		  arg3 = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg4 = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(arg3);
		      resumable_icp_push(arg2);
		      resumable_icp_push(arg1);
		      resumable_icp_push(Qread_icp_double_float_using_function);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_double_float_using_function;
		  }
		  arg4 = value;
	      }
	      b0 = arg1;
	      b1 = arg2;
	      b2 = arg3;
	      b3 = arg4;
	      result_of_read = g2ext_foreign_reconstruct_float(IFIX(b0),
		      IFIX(b1),IFIX(b2),IFIX(b3));
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdouble_float,string_constant_4,Qvalue,T,
			  DOUBLE_TO_DOUBLE_FLOAT(result_of_read),Nil,Nil);
	      temp = DOUBLE_TO_DOUBLE_FLOAT(result_of_read);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_double_float_using_function);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_double_float_using_function;
		}
		arg1 = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg2 = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(arg1);
		    resumable_icp_push(Qread_icp_double_float_using_function);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_double_float_using_function;
		}
		arg2 = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg3 = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(arg2);
		    resumable_icp_push(arg1);
		    resumable_icp_push(Qread_icp_double_float_using_function);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_double_float_using_function;
		}
		arg3 = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg4 = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(arg3);
		    resumable_icp_push(arg2);
		    resumable_icp_push(arg1);
		    resumable_icp_push(Qread_icp_double_float_using_function);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_double_float_using_function;
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
    }
    result = VALUES_1(temp);
  end_read_icp_double_float_using_function:
    return result;
}

/* READ-ICP-DOUBLE-FLOAT-1 */
double read_icp_double_float_1()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, b0, b1, b2;
    Object b3;
    double result_of_read, result_1;
    Declare_special(1);

    x_note_fn_call(52,82);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qdouble_float,string_constant_4,
		    Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  b0 = read_icp_byte();
	  b1 = read_icp_byte();
	  b2 = read_icp_byte();
	  b3 = read_icp_byte();
	  result_of_read = g2ext_foreign_reconstruct_float(IFIX(b0),
		  IFIX(b1),IFIX(b2),IFIX(b3));
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),Qdouble_float,
		      string_constant_4,Qvalue,T,
		      DOUBLE_TO_DOUBLE_FLOAT(result_of_read),Nil,Nil);
	  result_1 = result_of_read;
	POP_SPECIAL();
    }
    else {
	b0 = read_icp_byte();
	b1 = read_icp_byte();
	b2 = read_icp_byte();
	b3 = read_icp_byte();
	result_1 = g2ext_foreign_reconstruct_float(IFIX(b0),IFIX(b1),
		IFIX(b2),IFIX(b3));
    }
    return result_1;
}

static Object Qread_icp_managed_double_float;  /* read-icp-managed-double-float */

static Object Qmanaged_double_float;  /* managed-double-float */

/* READ-ICP-MANAGED-DOUBLE-FLOAT */
Object read_icp_managed_double_float()
{
    Object tag_temp, tracep, byte_count_before, current_icp_read_trace_level;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, b0, b1, b2, b3, result_of_read, temp_2;
    Object resumable_icp_state_1, icp_suspend_1, top, arg1, value, arg2, arg3;
    Object arg4;
    double aref_new_value;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(52,83);
    tag_temp = UNIQUE_TAG(Qread_icp_managed_double_float);
    if (PUSH_CATCH(tag_temp,0)) {
	if (Disable_resumability) {
	    if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmanaged_double_float,
			    string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      amf_available_array_cons_qm = 
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp = Vector_of_simple_float_array_pools;
			  temp_1 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_float_array_conses_tail_vector,
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
		      b0 = read_icp_byte();
		      b1 = read_icp_byte();
		      b2 = read_icp_byte();
		      b3 = read_icp_byte();
		      aref_new_value = 
			      g2ext_foreign_reconstruct_float(IFIX(b0),
			      IFIX(b1),IFIX(b2),IFIX(b3));
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      result_of_read = new_float;
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmanaged_double_float,string_constant_4,
			      Qvalue,T,result_of_read,Nil,Nil);
		  temp_2 = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    b0 = read_icp_byte();
		    b1 = read_icp_byte();
		    b2 = read_icp_byte();
		    b3 = read_icp_byte();
		    aref_new_value = 
			    g2ext_foreign_reconstruct_float(IFIX(b0),
			    IFIX(b1),IFIX(b2),IFIX(b3));
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_2 = new_float;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	else {
	    resumable_icp_state_1 = Resumable_icp_state;
	    icp_suspend_1 = Icp_suspend;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		top = resumable_icp_pop();
		if ( !EQ(Qread_icp_managed_double_float,top)) {
		    result = icp_error_internal(Qerror,string_constant_3,
			    Qread_icp_managed_double_float,top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmanaged_double_float,
			    string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      arg1 = resumable_icp_pop();
			  else {
			      value = read_icp_byte();
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qread_icp_managed_double_float);
				  result = VALUES_1(Icp_suspend);
				  THROW(tag_temp,result);
			      }
			      arg1 = value;
			  }
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      arg2 = resumable_icp_pop();
			  else {
			      value = read_icp_byte();
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(arg1);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qread_icp_managed_double_float);
				  result = VALUES_1(Icp_suspend);
				  THROW(tag_temp,result);
			      }
			      arg2 = value;
			  }
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      arg3 = resumable_icp_pop();
			  else {
			      value = read_icp_byte();
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(arg2);
				  resumable_icp_push(arg1);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qread_icp_managed_double_float);
				  result = VALUES_1(Icp_suspend);
				  THROW(tag_temp,result);
			      }
			      arg3 = value;
			  }
			  if ((resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				  &&  
				  !TRUEP(resumable_icp_pop_list_if_end_marker()))
			      arg4 = resumable_icp_pop();
			  else {
			      value = read_icp_byte();
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(arg3);
				  resumable_icp_push(arg2);
				  resumable_icp_push(arg1);
				  resumable_icp_push(Qresumable_icp_list_end);
				  resumable_icp_push(Qread_icp_managed_double_float);
				  result = VALUES_1(Icp_suspend);
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
			      ISVREF(Vector_of_simple_float_array_pools,
			      (SI_Long)1L);
		      if (amf_available_array_cons_qm) {
			  amf_array = M_CAR(amf_available_array_cons_qm);
			  temp = Vector_of_simple_float_array_pools;
			  temp_1 = M_CDR(amf_available_array_cons_qm);
			  SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			  inline_note_reclaim_cons(amf_available_array_cons_qm,
				  Qfloat_array);
			  if (ISVREF(Available_float_array_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_float_array_conses_tail_vector,
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
		      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		      DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		      result_of_read = new_float;
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmanaged_double_float,string_constant_4,
			      Qvalue,T,result_of_read,Nil,Nil);
		  temp_2 = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    arg1 = resumable_icp_pop();
			else {
			    value = read_icp_byte();
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qread_icp_managed_double_float);
				result = VALUES_1(Icp_suspend);
				THROW(tag_temp,result);
			    }
			    arg1 = value;
			}
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    arg2 = resumable_icp_pop();
			else {
			    value = read_icp_byte();
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(arg1);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qread_icp_managed_double_float);
				result = VALUES_1(Icp_suspend);
				THROW(tag_temp,result);
			    }
			    arg2 = value;
			}
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    arg3 = resumable_icp_pop();
			else {
			    value = read_icp_byte();
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(arg2);
				resumable_icp_push(arg1);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qread_icp_managed_double_float);
				result = VALUES_1(Icp_suspend);
				THROW(tag_temp,result);
			    }
			    arg3 = value;
			}
			if ((resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) 
				&&  
				!TRUEP(resumable_icp_pop_list_if_end_marker()))
			    arg4 = resumable_icp_pop();
			else {
			    value = read_icp_byte();
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(arg3);
				resumable_icp_push(arg2);
				resumable_icp_push(arg1);
				resumable_icp_push(Qresumable_icp_list_end);
				resumable_icp_push(Qread_icp_managed_double_float);
				result = VALUES_1(Icp_suspend);
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
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = Vector_of_simple_float_array_pools;
			temp_1 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = temp_1;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_float_array_conses_tail_vector,
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_2 = new_float;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	result = VALUES_1(temp_2);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qwrite_icp_managed_double_float;  /* write-icp-managed-double-float */

/* WRITE-ICP-MANAGED-DOUBLE-FLOAT */
Object write_icp_managed_double_float(managed_double_float)
    Object managed_double_float;
{
    Object tag_temp, tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object b0_1, b1_1, b2_1, b3_1, value, v1, v2, v3;
    SI_Long b0, b1, b2, b3;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(52,84);
    tag_temp = UNIQUE_TAG(Qwrite_icp_managed_double_float);
    if (PUSH_CATCH(tag_temp,0)) {
	if (Disable_resumability) {
	    if (Icp_write_trace_cutoff_level_qm) {
		tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_write_trace(T,Nil,Nil,Qmanaged_double_float,
			    string_constant_4,Qvalue,T,
			    managed_double_float,Nil,Nil);
		    byte_count_before = instantaneous_icp_writer_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_write_trace_level = 
			FIXNUM_ADD1(Current_icp_write_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
			      (SI_Long)0L),
			      UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
		      b0 = UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)0L);
		      b1 = UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)1L);
		      b2 = UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)2L);
		      b3 = UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)3L);
		      write_icp_byte(FIX(b0));
		      write_icp_byte(FIX(b1));
		      write_icp_byte(FIX(b2));
		      result_of_write = write_icp_byte(FIX(b3));
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  if (tracep)
		      emit_icp_write_trace(Nil,byte_count_before,
			      instantaneous_icp_writer_byte_count(),
			      Qmanaged_double_float,string_constant_4,
			      Qvalue,Nil,Nil,Nil,Nil);
		  temp = result_of_write;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
			    (SI_Long)0L),
			    UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
		    b0 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)0L);
		    b1 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)1L);
		    b2 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)2L);
		    b3 = UBYTE_16_ISAREF_1(Partition_float_union,(SI_Long)3L);
		    write_icp_byte(FIX(b0));
		    write_icp_byte(FIX(b1));
		    write_icp_byte(FIX(b2));
		    temp = write_icp_byte(FIX(b3));
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	else {
	    resumable_icp_state_1 = Resumable_icp_state;
	    icp_suspend_1 = Icp_suspend;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		top = resumable_icp_pop();
		if ( !EQ(Qwrite_icp_managed_double_float,top)) {
		    result = icp_error_internal(Qerror,string_constant_3,
			    Qwrite_icp_managed_double_float,top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    managed_double_float = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : managed_double_float;
	    if (Icp_write_trace_cutoff_level_qm) {
		tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_write_trace(T,Nil,Nil,Qmanaged_double_float,
			    string_constant_4,Qvalue,T,
			    managed_double_float,Nil,Nil);
		    byte_count_before = instantaneous_icp_writer_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_write_trace_level = 
			FIXNUM_ADD1(Current_icp_write_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			0);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      if ( !(resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)))
			  g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
				  (SI_Long)0L),
				  UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
		      b0_1 = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)0L));
		      b1_1 = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)1L));
		      b2_1 = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)2L));
		      b3_1 = (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			      ? resumable_icp_pop() : 
			      FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			      (SI_Long)3L));
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp = resumable_icp_pop();
			  if (! !(FIXNUMP(temp) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		      if (EQ(icp_suspend_1,write_icp_byte(b0_1))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l2:
		      if (EQ(icp_suspend_1,write_icp_byte(b1_1))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l3:
		      if (EQ(icp_suspend_1,write_icp_byte(b2_1))) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l4:
		      value = write_icp_byte(b3_1);
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)4L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		      result = VALUES_1(value);
		      goto end_block;
		    end_block:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(b3_1);
			  resumable_icp_push(b2_1);
			  resumable_icp_push(b1_1);
			  resumable_icp_push(b0_1);
			  resumable_icp_push(managed_double_float);
			  resumable_icp_push(Qwrite_icp_managed_double_float);
			  result = VALUES_1(Icp_suspend);
			  THROW(tag_temp,result);
		      }
		      temp = v1;
		      result_of_write = temp;
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  if (tracep)
		      emit_icp_write_trace(Nil,byte_count_before,
			      instantaneous_icp_writer_byte_count(),
			      Qmanaged_double_float,string_constant_4,
			      Qvalue,Nil,Nil,Nil,Nil);
		  temp = result_of_write;
		POP_SPECIAL();
	    }
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)))
			g2ext_foreign_partition_float(DFLOAT_ISAREF_1(managed_double_float,
				(SI_Long)0L),
				UBYTE_16_SARRAY_TO_USHORT_PTR(Partition_float_union));
		    b0_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : 
			    FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			    (SI_Long)0L));
		    b1_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : 
			    FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			    (SI_Long)1L));
		    b2_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : 
			    FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			    (SI_Long)2L));
		    b3_1 = (resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()) 
			    ? resumable_icp_pop() : 
			    FIX(UBYTE_16_ISAREF_1(Partition_float_union,
			    (SI_Long)3L));
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp = resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      case 3:
				goto l3_1;
				break;
			      case 4:
				goto l4_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (EQ(icp_suspend_1,write_icp_byte(b0_1))) {
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		  l2_1:
		    if (EQ(icp_suspend_1,write_icp_byte(b1_1))) {
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		  l3_1:
		    if (EQ(icp_suspend_1,write_icp_byte(b2_1))) {
			resumable_icp_push(FIX((SI_Long)3L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		  l4_1:
		    value = write_icp_byte(b3_1);
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)4L));
			result = VALUES_1(Icp_suspend);
			goto end_block_1;
		    }
		    result = VALUES_1(value);
		    goto end_block_1;
		  end_block_1:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(b3_1);
			resumable_icp_push(b2_1);
			resumable_icp_push(b1_1);
			resumable_icp_push(b0_1);
			resumable_icp_push(managed_double_float);
			resumable_icp_push(Qwrite_icp_managed_double_float);
			result = VALUES_1(Icp_suspend);
			THROW(tag_temp,result);
		    }
		    temp = v1;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	result = VALUES_1(temp);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qsend_icp_define_dummy_object;  /* send-icp-define-dummy-object */

static Object Qdefine_dummy_object;  /* define-dummy-object */

/* SEND-ICP-DEFINE-DUMMY-OBJECT */
Object send_icp_define_dummy_object(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,85);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_dummy_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)18L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qdefine_dummy_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_dummy_object,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qcorresponding_icp_object_index,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_unsigned_integer(corresponding_icp_object_index);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_unsigned_integer(corresponding_icp_object_index);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_define_dummy_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_define_dummy_object,top,Nil);
		goto end_send_icp_define_dummy_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_define_dummy_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)18L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qdefine_dummy_object,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_dummy_object,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qcorresponding_icp_object_index,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_define_dummy_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_dummy_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_dummy_object:
    return result;
}

/* HANDLE-ICP-DEFINE-DUMMY-OBJECT--BODY */
Object handle_icp_define_dummy_object__body(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(52,86);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_define_dummy_object;  /* handle-icp-define-dummy-object */

/* HANDLE-ICP-DEFINE-DUMMY-OBJECT */
Object handle_icp_define_dummy_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,87);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdefine_dummy_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_dummy_object__body(corresponding_icp_object_index);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_dummy_object,string_constant,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_dummy_object__body(corresponding_icp_object_index);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_define_dummy_object,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_define_dummy_object,top,Nil);
		goto end_handle_icp_define_dummy_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qdefine_dummy_object,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_define_dummy_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_define_dummy_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_dummy_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_dummy_object;
		  }
		  corresponding_icp_object_index = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_define_dummy_object__body(corresponding_icp_object_index);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qdefine_dummy_object,string_constant,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_define_dummy_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_define_dummy_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_define_dummy_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_define_dummy_object;
		}
		corresponding_icp_object_index = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_define_dummy_object__body(corresponding_icp_object_index);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_define_dummy_object:
    return result;
}

static Object Qsend_icp_end_message_block;  /* send-icp-end-message-block */

static Object Qend_message_block;  /* end-message-block */

/* SEND-ICP-END-MESSAGE-BLOCK */
Object send_icp_end_message_block()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,88);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_end_message_block;
	  }
	  start_writing_icp_message(FIX((SI_Long)17L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qend_message_block,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qend_message_block,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_end_message_block,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_end_message_block,top,Nil);
		goto end_send_icp_end_message_block;
	    }
	}
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_end_message_block;
	  }
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)17L)))) {
	      resumable_icp_push(Qsend_icp_end_message_block);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_message_block;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qend_message_block,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qend_message_block,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_message_block:
    return result;
}

/* HANDLE-ICP-END-MESSAGE-BLOCK--BODY */
Object handle_icp_end_message_block__body()
{
    x_note_fn_call(52,89);
    At_end_of_icp_message_block_qm = T;
    return VALUES_1(Nil);
}

static Object Qhandle_icp_end_message_block;  /* handle-icp-end-message-block */

/* HANDLE-ICP-END-MESSAGE-BLOCK */
Object handle_icp_end_message_block()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(52,90);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qend_message_block,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_end_message_block__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_message_block,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_message_block__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_end_message_block,top))
		return icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_end_message_block,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qend_message_block,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_end_message_block__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_message_block,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_message_block__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* RECLAIM-S-EXPRESSION-FOR-REMOTE-EVAL */
Object reclaim_s_expression_for_remote_eval(s_expression)
    Object s_expression;
{
    Object l, x, cdr_arg;

    x_note_fn_call(52,91);
    if ( !TRUEP(s_expression) || SYMBOLP(s_expression) || 
	    INTEGERP(s_expression))
	return VALUES_1(Nil);
    else if (CONSP(s_expression)) {
	l = s_expression;
	x = Nil;
      next_loop:
	x = CAR(l);
	if ( !SYMBOLP(x) &&  !NUMBERP(x))
	    reclaim_s_expression_for_remote_eval(x);
	l = CDR(l);
	if (ATOM(l))
	    goto end_loop;
	goto next_loop;
      end_loop:
	if (l) {
	    reclaim_s_expression_for_remote_eval(l);
	    cdr_arg = last(s_expression,_);
	    M_CDR(cdr_arg) = Nil;
	}
	reclaim_icp_list_1(s_expression);
	return VALUES_1(Qnil);
    }
    else if (text_string_p(s_expression))
	return reclaim_text_string(s_expression);
    else
	return VALUES_1(Nil);
}

Object Sexp_null_type_tag = UNBOUND;

Object Sexp_element_integer_type_tag = UNBOUND;

Object Sexp_element_float_type_tag = UNBOUND;

Object Sexp_element_symbol_type_tag = UNBOUND;

Object Sexp_element_text_type_tag = UNBOUND;

Object Sexp_element_list_type_tag = UNBOUND;

Object Sexp_element_character_type_tag = UNBOUND;

static Object Qsexp_element;       /* sexp-element */

static Object Qwrite_icp_sexp_element;  /* write-icp-sexp-element */

/* WRITE-ICP-SEXP-ELEMENT */
Object write_icp_sexp_element(sexp_element)
    Object sexp_element;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Object test, value, v1, v2, v3;
    char temp_2;
    double temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,92);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qsexp_element,
			string_constant_4,Qvalue,T,sexp_element,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if ( !TRUEP(sexp_element))
		  result_of_write = write_icp_byte(Sexp_null_type_tag);
	      else if (CHARACTERP(sexp_element)) {
		  write_icp_byte(Sexp_element_character_type_tag);
		  result_of_write = write_icp_character(sexp_element);
	      }
	      else if (INTEGERP(sexp_element)) {
		  write_icp_byte(Sexp_element_integer_type_tag);
		  result_of_write = write_icp_integer(sexp_element);
	      }
	      else if (FLOATP(sexp_element)) {
		  write_icp_byte(Sexp_element_float_type_tag);
		  temp = DOUBLE_FLOAT_TO_DOUBLE(sexp_element);
		  result_of_write = write_icp_double_float_1(temp);
	      }
	      else if (SYMBOLP(sexp_element)) {
		  write_icp_byte(Sexp_element_symbol_type_tag);
		  result_of_write = 
			  write_icp_text_string(symbol_name_text_string(sexp_element));
	      }
	      else if (text_string_p(sexp_element)) {
		  write_icp_byte(Sexp_element_text_type_tag);
		  result_of_write = write_icp_text_string(sexp_element);
	      }
	      else if (CONSP(sexp_element)) {
		  write_icp_byte(Sexp_element_list_type_tag);
		  result_of_write = 
			  write_icp_s_expression_for_remote_eval(sexp_element);
	      }
	      else
		  result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qsexp_element,string_constant_4,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else if ( !TRUEP(sexp_element))
	    temp_1 = write_icp_byte(Sexp_null_type_tag);
	else if (CHARACTERP(sexp_element)) {
	    write_icp_byte(Sexp_element_character_type_tag);
	    temp_1 = write_icp_character(sexp_element);
	}
	else if (INTEGERP(sexp_element)) {
	    write_icp_byte(Sexp_element_integer_type_tag);
	    temp_1 = write_icp_integer(sexp_element);
	}
	else if (FLOATP(sexp_element)) {
	    write_icp_byte(Sexp_element_float_type_tag);
	    temp = DOUBLE_FLOAT_TO_DOUBLE(sexp_element);
	    temp_1 = write_icp_double_float_1(temp);
	}
	else if (SYMBOLP(sexp_element)) {
	    write_icp_byte(Sexp_element_symbol_type_tag);
	    temp_1 = 
		    write_icp_text_string(symbol_name_text_string(sexp_element));
	}
	else if (text_string_p(sexp_element)) {
	    write_icp_byte(Sexp_element_text_type_tag);
	    temp_1 = write_icp_text_string(sexp_element);
	}
	else if (CONSP(sexp_element)) {
	    write_icp_byte(Sexp_element_list_type_tag);
	    temp_1 = write_icp_s_expression_for_remote_eval(sexp_element);
	}
	else
	    temp_1 = Qnil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_sexp_element,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_sexp_element,top,Nil);
		goto end_write_icp_sexp_element;
	    }
	}
	sexp_element = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : sexp_element;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qsexp_element,
			string_constant_4,Qvalue,T,sexp_element,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_2 = TRUEP(test);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ? EQ(test,Qtrue) :  !TRUEP(sexp_element)) {
		  value = write_icp_byte(Sexp_null_type_tag);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(sexp_element);
		      resumable_icp_push(Qwrite_icp_sexp_element);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_sexp_element;
		  }
		  result_of_write = value;
	      }
	      else {
		  test = Nil;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      test = resumable_icp_pop();
		      temp_2 = TRUEP(test);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2 ? EQ(test,Qtrue) : CHARACTERP(sexp_element)) {
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  temp_1 = resumable_icp_pop();
			  if (! !(FIXNUMP(temp_1) && 
				  FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				  FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
			      write_icp_byte(Sexp_element_character_type_tag))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		    l2:
		      value = write_icp_character(sexp_element);
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  result = VALUES_1(Icp_suspend);
			  goto end_block;
		      }
		      result = VALUES_1(value);
		      goto end_block;
		    end_block:
		      MVS_3(result,v1,v2,v3);
		      if (EQ(icp_suspend_1,v1)) {
			  resumable_icp_push(Qtrue);
			  resumable_icp_push(Qfalse);
			  resumable_icp_push(sexp_element);
			  resumable_icp_push(Qwrite_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_write_icp_sexp_element;
		      }
		      temp_1 = v1;
		      result_of_write = temp_1;
		  }
		  else {
		      test = Nil;
		      if (resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			  test = resumable_icp_pop();
			  temp_2 = TRUEP(test);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		      if (temp_2 ? EQ(test,Qtrue) : INTEGERP(sexp_element)) {
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      temp_1 = resumable_icp_pop();
			      if (! !(FIXNUMP(temp_1) && 
				      FIXNUM_LE(FIX((SI_Long)-128L),
				      temp_1) && FIXNUM_LE(temp_1,
				      FIX((SI_Long)127L))))
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
				  write_icp_byte(Sexp_element_integer_type_tag))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			l2_1:
			  value = write_icp_integer(sexp_element);
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      result = VALUES_1(Icp_suspend);
			      goto end_block_1;
			  }
			  result = VALUES_1(value);
			  goto end_block_1;
			end_block_1:
			  MVS_3(result,v1,v2,v3);
			  if (EQ(icp_suspend_1,v1)) {
			      resumable_icp_push(Qtrue);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(Qfalse);
			      resumable_icp_push(sexp_element);
			      resumable_icp_push(Qwrite_icp_sexp_element);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_write_icp_sexp_element;
			  }
			  temp_1 = v1;
			  result_of_write = temp_1;
		      }
		      else {
			  test = Nil;
			  if (resumable_icp_state_1 ? 
				  TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			      test = resumable_icp_pop();
			      temp_2 = TRUEP(test);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2 ? EQ(test,Qtrue) : FLOATP(sexp_element)) {
			      if (resumable_icp_state_1 ? 
				      TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				  temp_1 = resumable_icp_pop();
				  if (! !(FIXNUMP(temp_1) && 
					  FIXNUM_LE(FIX((SI_Long)-128L),
					  temp_1) && FIXNUM_LE(temp_1,
					  FIX((SI_Long)127L))))
				      switch (INTEGER_TO_CHAR(temp_1)) {
					case 1:
					  goto l1_2;
					  break;
					case 2:
					  goto l2_2;
					  break;
					default:
					  break;
				      }
			      }
			    l1_2:
			      if (EQ(icp_suspend_1,
				      write_icp_byte(Sexp_element_float_type_tag))) 
					  {
				  resumable_icp_push(FIX((SI_Long)1L));
				  result = VALUES_1(Icp_suspend);
				  goto end_block_2;
			      }
			    l2_2:
			      temp = DOUBLE_FLOAT_TO_DOUBLE(sexp_element);
			      value = write_icp_double_float_1(temp);
			      if (EQ(icp_suspend_1,value)) {
				  resumable_icp_push(FIX((SI_Long)2L));
				  result = VALUES_1(Icp_suspend);
				  goto end_block_2;
			      }
			      result = VALUES_1(value);
			      goto end_block_2;
			    end_block_2:
			      MVS_3(result,v1,v2,v3);
			      if (EQ(icp_suspend_1,v1)) {
				  resumable_icp_push(Qtrue);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(Qfalse);
				  resumable_icp_push(sexp_element);
				  resumable_icp_push(Qwrite_icp_sexp_element);
				  result = VALUES_1(Icp_suspend);
				  POP_SPECIAL();
				  goto end_write_icp_sexp_element;
			      }
			      temp_1 = v1;
			      result_of_write = temp_1;
			  }
			  else {
			      test = Nil;
			      if (resumable_icp_state_1 ? 
				      TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				  test = resumable_icp_pop();
				  temp_2 = TRUEP(test);
			      }
			      else
				  temp_2 = TRUEP(Nil);
			      if (temp_2 ? EQ(test,Qtrue) : 
				      SYMBOLP(sexp_element)) {
				  if (resumable_icp_state_1 ? 
					  TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				      temp_1 = resumable_icp_pop();
				      if (! !(FIXNUMP(temp_1) && 
					      FIXNUM_LE(FIX((SI_Long)-128L),
					      temp_1) && FIXNUM_LE(temp_1,
					      FIX((SI_Long)127L))))
					  switch (INTEGER_TO_CHAR(temp_1)) {
					    case 1:
					      goto l1_3;
					      break;
					    case 2:
					      goto l2_3;
					      break;
					    default:
					      break;
					  }
				  }
				l1_3:
				  if (EQ(icp_suspend_1,
					  write_icp_byte(Sexp_element_symbol_type_tag))) 
					      {
				      resumable_icp_push(FIX((SI_Long)1L));
				      result = VALUES_1(Icp_suspend);
				      goto end_block_3;
				  }
				l2_3:
				  value = 
					  write_icp_text_string(symbol_name_text_string(sexp_element));
				  if (EQ(icp_suspend_1,value)) {
				      resumable_icp_push(FIX((SI_Long)2L));
				      result = VALUES_1(Icp_suspend);
				      goto end_block_3;
				  }
				  result = VALUES_1(value);
				  goto end_block_3;
				end_block_3:
				  MVS_3(result,v1,v2,v3);
				  if (EQ(icp_suspend_1,v1)) {
				      resumable_icp_push(Qtrue);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(Qfalse);
				      resumable_icp_push(sexp_element);
				      resumable_icp_push(Qwrite_icp_sexp_element);
				      result = VALUES_1(Icp_suspend);
				      POP_SPECIAL();
				      goto end_write_icp_sexp_element;
				  }
				  temp_1 = v1;
				  result_of_write = temp_1;
			      }
			      else {
				  test = Nil;
				  if (resumable_icp_state_1 ? 
					  TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) {
				      test = resumable_icp_pop();
				      temp_2 = TRUEP(test);
				  }
				  else
				      temp_2 = TRUEP(Nil);
				  if (temp_2 ? EQ(test,Qtrue) : 
					  TRUEP(text_string_p(sexp_element))) {
				      if (resumable_icp_state_1 ? 
					      TRUEP(Resumable_icp_state) : 
					      TRUEP(Nil)) {
					  temp_1 = resumable_icp_pop();
					  if (! !(FIXNUMP(temp_1) && 
						  FIXNUM_LE(FIX((SI_Long)-128L),
						  temp_1) && 
						  FIXNUM_LE(temp_1,
						  FIX((SI_Long)127L))))
					      switch (INTEGER_TO_CHAR(temp_1)) 
							  {
						case 1:
						  goto l1_4;
						  break;
						case 2:
						  goto l2_4;
						  break;
						default:
						  break;
					      }
				      }
				    l1_4:
				      if (EQ(icp_suspend_1,
					      write_icp_byte(Sexp_element_text_type_tag))) 
						  {
					  resumable_icp_push(FIX((SI_Long)1L));
					  result = VALUES_1(Icp_suspend);
					  goto end_block_4;
				      }
				    l2_4:
				      value = 
					      write_icp_text_string(sexp_element);
				      if (EQ(icp_suspend_1,value)) {
					  resumable_icp_push(FIX((SI_Long)2L));
					  result = VALUES_1(Icp_suspend);
					  goto end_block_4;
				      }
				      result = VALUES_1(value);
				      goto end_block_4;
				    end_block_4:
				      MVS_3(result,v1,v2,v3);
				      if (EQ(icp_suspend_1,v1)) {
					  resumable_icp_push(Qtrue);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(sexp_element);
					  resumable_icp_push(Qwrite_icp_sexp_element);
					  result = VALUES_1(Icp_suspend);
					  POP_SPECIAL();
					  goto end_write_icp_sexp_element;
				      }
				      temp_1 = v1;
				      result_of_write = temp_1;
				  }
				  else if ((resumable_icp_state_1 ? 
					  TRUEP(Resumable_icp_state) : 
					  TRUEP(Nil)) || CONSP(sexp_element)) {
				      if (resumable_icp_state_1 ? 
					      TRUEP(Resumable_icp_state) : 
					      TRUEP(Nil)) {
					  temp_1 = resumable_icp_pop();
					  if (! !(FIXNUMP(temp_1) && 
						  FIXNUM_LE(FIX((SI_Long)-128L),
						  temp_1) && 
						  FIXNUM_LE(temp_1,
						  FIX((SI_Long)127L))))
					      switch (INTEGER_TO_CHAR(temp_1)) 
							  {
						case 1:
						  goto l1_5;
						  break;
						case 2:
						  goto l2_5;
						  break;
						default:
						  break;
					      }
				      }
				    l1_5:
				      if (EQ(icp_suspend_1,
					      write_icp_byte(Sexp_element_list_type_tag))) 
						  {
					  resumable_icp_push(FIX((SI_Long)1L));
					  result = VALUES_1(Icp_suspend);
					  goto end_block_5;
				      }
				    l2_5:
				      value = 
					      write_icp_s_expression_for_remote_eval(sexp_element);
				      if (EQ(icp_suspend_1,value)) {
					  resumable_icp_push(FIX((SI_Long)2L));
					  result = VALUES_1(Icp_suspend);
					  goto end_block_5;
				      }
				      result = VALUES_1(value);
				      goto end_block_5;
				    end_block_5:
				      MVS_3(result,v1,v2,v3);
				      if (EQ(icp_suspend_1,v1)) {
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(Qfalse);
					  resumable_icp_push(sexp_element);
					  resumable_icp_push(Qwrite_icp_sexp_element);
					  result = VALUES_1(Icp_suspend);
					  POP_SPECIAL();
					  goto end_write_icp_sexp_element;
				      }
				      temp_1 = v1;
				      result_of_write = temp_1;
				  }
				  else
				      result_of_write = Qnil;
			      }
			  }
		      }
		  }
	      }
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qsexp_element,string_constant_4,Qvalue,Nil,Nil,
			  Nil,Nil);
	      temp_1 = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_2 = TRUEP(test);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ? EQ(test,Qtrue) :  !TRUEP(sexp_element)) {
		value = write_icp_byte(Sexp_null_type_tag);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(sexp_element);
		    resumable_icp_push(Qwrite_icp_sexp_element);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_sexp_element;
		}
		temp_1 = value;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_2 = TRUEP(test);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2 ? EQ(test,Qtrue) : CHARACTERP(sexp_element)) {
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_6;
				break;
			      case 2:
				goto l2_6;
				break;
			      default:
				break;
			    }
		    }
		  l1_6:
		    if (EQ(icp_suspend_1,
			    write_icp_byte(Sexp_element_character_type_tag))) {
			resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(Icp_suspend);
			goto end_block_6;
		    }
		  l2_6:
		    value = write_icp_character(sexp_element);
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			goto end_block_6;
		    }
		    result = VALUES_1(value);
		    goto end_block_6;
		  end_block_6:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(Qfalse);
			resumable_icp_push(sexp_element);
			resumable_icp_push(Qwrite_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_write_icp_sexp_element;
		    }
		    temp_1 = v1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_2 = TRUEP(test);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2 ? EQ(test,Qtrue) : INTEGERP(sexp_element)) {
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    temp_1 = resumable_icp_pop();
			    if (! !(FIXNUMP(temp_1) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) 
				    && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp_1)) {
				  case 1:
				    goto l1_7;
				    break;
				  case 2:
				    goto l2_7;
				    break;
				  default:
				    break;
				}
			}
		      l1_7:
			if (EQ(icp_suspend_1,
				write_icp_byte(Sexp_element_integer_type_tag))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_7;
			}
		      l2_7:
			value = write_icp_integer(sexp_element);
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    goto end_block_7;
			}
			result = VALUES_1(value);
			goto end_block_7;
		      end_block_7:
			MVS_3(result,v1,v2,v3);
			if (EQ(icp_suspend_1,v1)) {
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(sexp_element);
			    resumable_icp_push(Qwrite_icp_sexp_element);
			    result = VALUES_1(Icp_suspend);
			    goto end_write_icp_sexp_element;
			}
			temp_1 = v1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
			    test = resumable_icp_pop();
			    temp_2 = TRUEP(test);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2 ? EQ(test,Qtrue) : FLOATP(sexp_element)) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				temp_1 = resumable_icp_pop();
				if (! !(FIXNUMP(temp_1) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp_1) && FIXNUM_LE(temp_1,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp_1)) {
				      case 1:
					goto l1_8;
					break;
				      case 2:
					goto l2_8;
					break;
				      default:
					break;
				    }
			    }
			  l1_8:
			    if (EQ(icp_suspend_1,
				    write_icp_byte(Sexp_element_float_type_tag))) 
					{
				resumable_icp_push(FIX((SI_Long)1L));
				result = VALUES_1(Icp_suspend);
				goto end_block_8;
			    }
			  l2_8:
			    temp = DOUBLE_FLOAT_TO_DOUBLE(sexp_element);
			    value = write_icp_double_float_1(temp);
			    if (EQ(icp_suspend_1,value)) {
				resumable_icp_push(FIX((SI_Long)2L));
				result = VALUES_1(Icp_suspend);
				goto end_block_8;
			    }
			    result = VALUES_1(value);
			    goto end_block_8;
			  end_block_8:
			    MVS_3(result,v1,v2,v3);
			    if (EQ(icp_suspend_1,v1)) {
				resumable_icp_push(Qtrue);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(Qfalse);
				resumable_icp_push(sexp_element);
				resumable_icp_push(Qwrite_icp_sexp_element);
				result = VALUES_1(Icp_suspend);
				goto end_write_icp_sexp_element;
			    }
			    temp_1 = v1;
			}
			else {
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
				test = resumable_icp_pop();
				temp_2 = TRUEP(test);
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2 ? EQ(test,Qtrue) : 
				    SYMBOLP(sexp_element)) {
				if (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) {
				    temp_1 = resumable_icp_pop();
				    if (! !(FIXNUMP(temp_1) && 
					    FIXNUM_LE(FIX((SI_Long)-128L),
					    temp_1) && FIXNUM_LE(temp_1,
					    FIX((SI_Long)127L))))
					switch (INTEGER_TO_CHAR(temp_1)) {
					  case 1:
					    goto l1_9;
					    break;
					  case 2:
					    goto l2_9;
					    break;
					  default:
					    break;
					}
				}
			      l1_9:
				if (EQ(icp_suspend_1,
					write_icp_byte(Sexp_element_symbol_type_tag))) 
					    {
				    resumable_icp_push(FIX((SI_Long)1L));
				    result = VALUES_1(Icp_suspend);
				    goto end_block_9;
				}
			      l2_9:
				value = 
					write_icp_text_string(symbol_name_text_string(sexp_element));
				if (EQ(icp_suspend_1,value)) {
				    resumable_icp_push(FIX((SI_Long)2L));
				    result = VALUES_1(Icp_suspend);
				    goto end_block_9;
				}
				result = VALUES_1(value);
				goto end_block_9;
			      end_block_9:
				MVS_3(result,v1,v2,v3);
				if (EQ(icp_suspend_1,v1)) {
				    resumable_icp_push(Qtrue);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(Qfalse);
				    resumable_icp_push(sexp_element);
				    resumable_icp_push(Qwrite_icp_sexp_element);
				    result = VALUES_1(Icp_suspend);
				    goto end_write_icp_sexp_element;
				}
				temp_1 = v1;
			    }
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) {
				    test = resumable_icp_pop();
				    temp_2 = TRUEP(test);
				}
				else
				    temp_2 = TRUEP(Nil);
				if (temp_2 ? EQ(test,Qtrue) : 
					TRUEP(text_string_p(sexp_element))) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					temp_1 = resumable_icp_pop();
					if (! !(FIXNUMP(temp_1) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp_1) && 
						FIXNUM_LE(temp_1,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp_1)) {
					      case 1:
						goto l1_10;
						break;
					      case 2:
						goto l2_10;
						break;
					      default:
						break;
					    }
				    }
				  l1_10:
				    if (EQ(icp_suspend_1,
					    write_icp_byte(Sexp_element_text_type_tag))) 
						{
					resumable_icp_push(FIX((SI_Long)1L));
					result = VALUES_1(Icp_suspend);
					goto end_block_10;
				    }
				  l2_10:
				    value = 
					    write_icp_text_string(sexp_element);
				    if (EQ(icp_suspend_1,value)) {
					resumable_icp_push(FIX((SI_Long)2L));
					result = VALUES_1(Icp_suspend);
					goto end_block_10;
				    }
				    result = VALUES_1(value);
				    goto end_block_10;
				  end_block_10:
				    MVS_3(result,v1,v2,v3);
				    if (EQ(icp_suspend_1,v1)) {
					resumable_icp_push(Qtrue);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(sexp_element);
					resumable_icp_push(Qwrite_icp_sexp_element);
					result = VALUES_1(Icp_suspend);
					goto end_write_icp_sexp_element;
				    }
				    temp_1 = v1;
				}
				else if ((resumable_icp_state_1 ? 
					TRUEP(Resumable_icp_state) : 
					TRUEP(Nil)) || CONSP(sexp_element)) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(Resumable_icp_state) : 
					    TRUEP(Nil)) {
					temp_1 = resumable_icp_pop();
					if (! !(FIXNUMP(temp_1) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp_1) && 
						FIXNUM_LE(temp_1,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp_1)) {
					      case 1:
						goto l1_11;
						break;
					      case 2:
						goto l2_11;
						break;
					      default:
						break;
					    }
				    }
				  l1_11:
				    if (EQ(icp_suspend_1,
					    write_icp_byte(Sexp_element_list_type_tag))) 
						{
					resumable_icp_push(FIX((SI_Long)1L));
					result = VALUES_1(Icp_suspend);
					goto end_block_11;
				    }
				  l2_11:
				    value = 
					    write_icp_s_expression_for_remote_eval(sexp_element);
				    if (EQ(icp_suspend_1,value)) {
					resumable_icp_push(FIX((SI_Long)2L));
					result = VALUES_1(Icp_suspend);
					goto end_block_11;
				    }
				    result = VALUES_1(value);
				    goto end_block_11;
				  end_block_11:
				    MVS_3(result,v1,v2,v3);
				    if (EQ(icp_suspend_1,v1)) {
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(Qfalse);
					resumable_icp_push(sexp_element);
					resumable_icp_push(Qwrite_icp_sexp_element);
					result = VALUES_1(Icp_suspend);
					goto end_write_icp_sexp_element;
				    }
				    temp_1 = v1;
				}
				else
				    temp_1 = Qnil;
			    }
			}
		    }
		}
	    }
	}
    }
    result = VALUES_1(temp_1);
  end_write_icp_sexp_element:
    return result;
}

static Object Qread_icp_sexp_element;  /* read-icp-sexp-element */

/* READ-ICP-SEXP-ELEMENT */
Object read_icp_sexp_element()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, temp;
    Object result_of_read, resumable_icp_state_1, icp_suspend_1, top, key;
    Object value, arg1;
    double value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,93);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qsexp_element,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      temp = read_icp_byte();
	      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		      FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      result_of_read = Nil;
		      break;
		    case 6:
		      result_of_read = read_icp_character();
		      break;
		    case 1:
		      result_of_read = read_icp_integer();
		      break;
		    case 2:
		      result_of_read = 
			      DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		      break;
		    case 3:
		      result_of_read = intern_text_string(1,
			      read_icp_text_string());
		      break;
		    case 4:
		      result_of_read = read_icp_text_string();
		      break;
		    case 5:
		      result_of_read = read_icp_s_expression_for_remote_eval();
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsexp_element,string_constant_4,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    temp = read_icp_byte();
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		temp = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = Nil;
		    break;
		  case 6:
		    temp = read_icp_character();
		    break;
		  case 1:
		    temp = read_icp_integer();
		    break;
		  case 2:
		    temp = DOUBLE_TO_DOUBLE_FLOAT(read_icp_double_float_1());
		    break;
		  case 3:
		    temp = intern_text_string(1,read_icp_text_string());
		    break;
		  case 4:
		    temp = read_icp_text_string();
		    break;
		  case 5:
		    temp = read_icp_s_expression_for_remote_eval();
		    break;
		  default:
		    temp = Nil;
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_sexp_element,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_sexp_element,top,Nil);
		goto end_read_icp_sexp_element;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qsexp_element,
			string_constant_4,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  key = resumable_icp_pop();
	      else {
		  value = read_icp_byte();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_sexp_element);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_sexp_element;
		  }
		  key = value;
	      }
	      temp = key;
	      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		      FIX((SI_Long)127L))))
		  result_of_read = Nil;
	      else
		  switch (INTEGER_TO_CHAR(temp)) {
		    case 0:
		      result_of_read = Nil;
		      break;
		    case 6:
		      value = read_icp_character();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(Qread_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_sexp_element;
		      }
		      result_of_read = value;
		      break;
		    case 1:
		      value = read_icp_integer();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(Qread_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_sexp_element;
		      }
		      result_of_read = value;
		      break;
		    case 2:
		      value_1 = read_icp_double_float_1();
		      if (EQ(icp_suspend_1,DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			  resumable_icp_push(key);
			  resumable_icp_push(Qread_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_sexp_element;
		      }
		      result_of_read = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		      break;
		    case 3:
		      if ((resumable_icp_state_1 ? 
			      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			      !TRUEP(resumable_icp_pop_list_if_end_marker()))
			  arg1 = resumable_icp_pop();
		      else {
			  value = read_icp_text_string();
			  if (EQ(icp_suspend_1,value)) {
			      resumable_icp_push(Qresumable_icp_list_end);
			      resumable_icp_push(key);
			      resumable_icp_push(Qread_icp_sexp_element);
			      result = VALUES_1(Icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_sexp_element;
			  }
			  arg1 = value;
		      }
		      result_of_read = intern_text_string(1,arg1);
		      break;
		    case 4:
		      value = read_icp_text_string();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(Qread_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_sexp_element;
		      }
		      result_of_read = value;
		      break;
		    case 5:
		      value = read_icp_s_expression_for_remote_eval();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(key);
			  resumable_icp_push(Qread_icp_sexp_element);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_sexp_element;
		      }
		      result_of_read = value;
		      break;
		    default:
		      result_of_read = Nil;
		      break;
		  }
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsexp_element,string_constant_4,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		key = resumable_icp_pop();
	    else {
		value = read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_sexp_element);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_sexp_element;
		}
		key = value;
	    }
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		temp = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = Nil;
		    break;
		  case 6:
		    value = read_icp_character();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(Qread_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_sexp_element;
		    }
		    temp = value;
		    break;
		  case 1:
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(Qread_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_sexp_element;
		    }
		    temp = value;
		    break;
		  case 2:
		    value_1 = read_icp_double_float_1();
		    if (EQ(icp_suspend_1,DOUBLE_TO_DOUBLE_FLOAT(value_1))) {
			resumable_icp_push(key);
			resumable_icp_push(Qread_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_sexp_element;
		    }
		    temp = DOUBLE_TO_DOUBLE_FLOAT(value_1);
		    break;
		  case 3:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			arg1 = resumable_icp_pop();
		    else {
			value = read_icp_text_string();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(key);
			    resumable_icp_push(Qread_icp_sexp_element);
			    result = VALUES_1(Icp_suspend);
			    goto end_read_icp_sexp_element;
			}
			arg1 = value;
		    }
		    temp = intern_text_string(1,arg1);
		    break;
		  case 4:
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(Qread_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_sexp_element;
		    }
		    temp = value;
		    break;
		  case 5:
		    value = read_icp_s_expression_for_remote_eval();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(key);
			resumable_icp_push(Qread_icp_sexp_element);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_sexp_element;
		    }
		    temp = value;
		    break;
		  default:
		    temp = Nil;
		    break;
		}
	}
    }
    result = VALUES_1(temp);
  end_read_icp_sexp_element:
    return result;
}

static Object Qs_expression_for_remote_eval;  /* s-expression-for-remote-eval */

static Object Qwrite_icp_s_expression_for_remote_eval;  /* write-icp-s-expression-for-remote-eval */

/* WRITE-ICP-S-EXPRESSION-FOR-REMOTE-EVAL */
Object write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval)
    Object s_expression_for_remote_eval;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object sexp_element, ab_loop_list_, result_of_write, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, v1, v2, v3, value;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,94);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qs_expression_for_remote_eval,string_constant_4,
			Qvalue,T,s_expression_for_remote_eval,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      if (CONSP(s_expression_for_remote_eval)) {
		  write_icp_unsigned_integer(length(s_expression_for_remote_eval));
		  sexp_element = Nil;
		  ab_loop_list_ = s_expression_for_remote_eval;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  sexp_element = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  write_icp_sexp_element(sexp_element);
		  goto next_loop;
		end_loop:
		  result_of_write = Qnil;
	      }
	      else
		  result_of_write = 
			  write_icp_sexp_element(s_expression_for_remote_eval);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qs_expression_for_remote_eval,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if (CONSP(s_expression_for_remote_eval)) {
	    write_icp_unsigned_integer(length(s_expression_for_remote_eval));
	    sexp_element = Nil;
	    ab_loop_list_ = s_expression_for_remote_eval;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    sexp_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    write_icp_sexp_element(sexp_element);
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
	else
	    temp = write_icp_sexp_element(s_expression_for_remote_eval);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_s_expression_for_remote_eval,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qwrite_icp_s_expression_for_remote_eval,top,Nil);
		goto end_write_icp_s_expression_for_remote_eval;
	    }
	}
	s_expression_for_remote_eval = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : s_expression_for_remote_eval;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qs_expression_for_remote_eval,string_constant_4,
			Qvalue,T,s_expression_for_remote_eval,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      test = Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  test = resumable_icp_pop();
		  temp_1 = TRUEP(test);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1 ? EQ(test,Qtrue) : 
		      CONSP(s_expression_for_remote_eval)) {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp = resumable_icp_pop();
		      if (! !(FIXNUMP(temp) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			      FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
			  write_icp_unsigned_integer(length(s_expression_for_remote_eval)))) 
			      {
		      resumable_icp_push(FIX((SI_Long)1L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		l2:
		  sexp_element = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : Nil;
		  ab_loop_list_ = (resumable_icp_state_1 ? 
			  TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			  resumable_icp_pop() : s_expression_for_remote_eval;
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil))
		      goto resume;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  sexp_element = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		resume:
		  if (EQ(icp_suspend_1,write_icp_sexp_element(sexp_element))) {
		      resumable_icp_push(ab_loop_list_);
		      resumable_icp_push(sexp_element);
		      resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(Icp_suspend);
		      goto end_block;
		  }
		  goto next_loop_2;
		end_loop_2:
		  result = VALUES_1(Qnil);
		  goto end_block;
		end_block:
		  MVS_3(result,v1,v2,v3);
		  if (EQ(icp_suspend_1,v1)) {
		      resumable_icp_push(Qtrue);
		      resumable_icp_push(s_expression_for_remote_eval);
		      resumable_icp_push(Qwrite_icp_s_expression_for_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_s_expression_for_remote_eval;
		  }
		  temp = v1;
		  result_of_write = temp;
	      }
	      else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		      : TRUEP(Nil)) || T) {
		  value = write_icp_sexp_element(s_expression_for_remote_eval);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qfalse);
		      resumable_icp_push(s_expression_for_remote_eval);
		      resumable_icp_push(Qwrite_icp_s_expression_for_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_s_expression_for_remote_eval;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qs_expression_for_remote_eval,string_constant_4,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) {
		test = resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qtrue) : 
			CONSP(s_expression_for_remote_eval)) {
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp = resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp)) {
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
			write_icp_unsigned_integer(length(s_expression_for_remote_eval)))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
	      l2_1:
		sexp_element = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : Nil;
		ab_loop_list_ = (resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
			resumable_icp_pop() : s_expression_for_remote_eval;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil))
		    goto resume_1;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		sexp_element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
	      resume_1:
		if (EQ(icp_suspend_1,write_icp_sexp_element(sexp_element))) {
		    resumable_icp_push(ab_loop_list_);
		    resumable_icp_push(sexp_element);
		    resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(Icp_suspend);
		    goto end_block_1;
		}
		goto next_loop_3;
	      end_loop_3:
		result = VALUES_1(Qnil);
		goto end_block_1;
	      end_block_1:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    resumable_icp_push(Qtrue);
		    resumable_icp_push(s_expression_for_remote_eval);
		    resumable_icp_push(Qwrite_icp_s_expression_for_remote_eval);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_s_expression_for_remote_eval;
		}
		temp = v1;
	    }
	    else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) || T) {
		value = write_icp_sexp_element(s_expression_for_remote_eval);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qfalse);
		    resumable_icp_push(s_expression_for_remote_eval);
		    resumable_icp_push(Qwrite_icp_s_expression_for_remote_eval);
		    result = VALUES_1(Icp_suspend);
		    goto end_write_icp_s_expression_for_remote_eval;
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_s_expression_for_remote_eval:
    return result;
}

static Object Qread_icp_s_expression_for_remote_eval;  /* read-icp-s-expression-for-remote-eval */

/* READ-ICP-S-EXPRESSION-FOR-REMOTE-EVAL */
Object read_icp_s_expression_for_remote_eval()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long item_count, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(52,95);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qs_expression_for_remote_eval,string_constant_4,
			Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      item_count = (SI_Long)1L;
	      ab_loop_bind_ = IFIX(read_icp_unsigned_integer());
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if (item_count > ab_loop_bind_)
		  goto end_loop;
	      ab_loopvar__2 = icp_cons_1(read_icp_sexp_element(),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      item_count = item_count + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      result_of_read = ab_loopvar_;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qs_expression_for_remote_eval,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    item_count = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(read_icp_unsigned_integer());
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (item_count > ab_loop_bind_)
		goto end_loop_1;
	    ab_loopvar__2 = icp_cons_1(read_icp_sexp_element(),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    item_count = item_count + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar_;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_s_expression_for_remote_eval,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qread_icp_s_expression_for_remote_eval,top,Nil);
		goto end_read_icp_s_expression_for_remote_eval;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qs_expression_for_remote_eval,string_constant_4,
			Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      item_count = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  ab_loop_bind_ = IFIX(resumable_icp_pop());
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(FIX(item_count));
		      resumable_icp_push(Qread_icp_s_expression_for_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_s_expression_for_remote_eval;
		  }
		  ab_loop_bind_ = IFIX(value);
	      }
	      ab_loopvar_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__2 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if (item_count > ab_loop_bind_)
		  goto end_loop_2;
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  value = read_icp_sexp_element();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(item_count));
		      resumable_icp_push(Qread_icp_s_expression_for_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_s_expression_for_remote_eval;
		  }
		  arg1 = value;
	      }
	      arg2 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loopvar__2 = icp_cons_1(arg1,arg2);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      item_count = item_count + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:
	      result_of_read = ab_loopvar_;
	      goto end_3;
	      result_of_read = Qnil;
	    end_3:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qs_expression_for_remote_eval,string_constant_4,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    item_count = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)1L;
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		ab_loop_bind_ = IFIX(resumable_icp_pop());
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(FIX(item_count));
		    resumable_icp_push(Qread_icp_s_expression_for_remote_eval);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_s_expression_for_remote_eval;
		}
		ab_loop_bind_ = IFIX(value);
	    }
	    ab_loopvar_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__1 = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__2 = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if (item_count > ab_loop_bind_)
		goto end_loop_3;
	  resume_1:
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		value = read_icp_sexp_element();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(item_count));
		    resumable_icp_push(Qread_icp_s_expression_for_remote_eval);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_s_expression_for_remote_eval;
		}
		arg1 = value;
	    }
	    arg2 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loopvar__2 = icp_cons_1(arg1,arg2);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    item_count = item_count + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_s_expression_for_remote_eval:
    return result;
}

static Object Qsend_icp_remote_eval;  /* send-icp-remote-eval */

static Object Qremote_eval;        /* remote-eval */

/* SEND-ICP-REMOTE-EVAL */
Object send_icp_remote_eval(s_expression_for_remote_eval)
    Object s_expression_for_remote_eval;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,96);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_remote_eval;
	  }
	  start_writing_icp_message(FIX((SI_Long)300L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qremote_eval,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qs_expression_for_remote_eval,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qs_expression_for_remote_eval,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qremote_eval,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qs_expression_for_remote_eval,string_constant_2,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qs_expression_for_remote_eval,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_remote_eval,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_remote_eval,top,Nil);
		goto end_send_icp_remote_eval;
	    }
	}
	s_expression_for_remote_eval = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : s_expression_for_remote_eval;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_remote_eval;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)300L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qremote_eval,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qs_expression_for_remote_eval,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qs_expression_for_remote_eval,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qremote_eval,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qs_expression_for_remote_eval,string_constant_2,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qs_expression_for_remote_eval,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_s_expression_for_remote_eval(s_expression_for_remote_eval))) 
		      {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(s_expression_for_remote_eval);
	      resumable_icp_push(Qsend_icp_remote_eval);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_remote_eval;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_remote_eval:
    return result;
}

/* HANDLE-ICP-REMOTE-EVAL--BODY */
Object handle_icp_remote_eval__body(s_expression_for_remote_eval)
    Object s_expression_for_remote_eval;
{
    x_note_fn_call(52,97);
    simple_eval(s_expression_for_remote_eval);
    reclaim_s_expression_for_remote_eval(s_expression_for_remote_eval);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_remote_eval;  /* handle-icp-remote-eval */

/* HANDLE-ICP-REMOTE-EVAL */
Object handle_icp_remote_eval()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, s_expression_for_remote_eval;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,98);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_eval,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qs_expression_for_remote_eval,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_s_expression_for_remote_eval();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qs_expression_for_remote_eval,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    s_expression_for_remote_eval = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  s_expression_for_remote_eval = 
			  read_icp_s_expression_for_remote_eval();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_remote_eval__body(s_expression_for_remote_eval);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_eval,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qs_expression_for_remote_eval,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_s_expression_for_remote_eval();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qs_expression_for_remote_eval,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  s_expression_for_remote_eval = result_of_read;
		POP_SPECIAL();
	    }
	    else
		s_expression_for_remote_eval = 
			read_icp_s_expression_for_remote_eval();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_remote_eval__body(s_expression_for_remote_eval);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_remote_eval,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_remote_eval,top,Nil);
		goto end_handle_icp_remote_eval;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_eval,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  s_expression_for_remote_eval = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qs_expression_for_remote_eval,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_s_expression_for_remote_eval();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_remote_eval);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_remote_eval;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qs_expression_for_remote_eval,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    s_expression_for_remote_eval = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_s_expression_for_remote_eval();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_remote_eval;
		  }
		  s_expression_for_remote_eval = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_remote_eval__body(s_expression_for_remote_eval);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_eval,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		s_expression_for_remote_eval = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qs_expression_for_remote_eval,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_s_expression_for_remote_eval();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_remote_eval);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_remote_eval;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qs_expression_for_remote_eval,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  s_expression_for_remote_eval = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_s_expression_for_remote_eval();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_remote_eval);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_remote_eval;
		}
		s_expression_for_remote_eval = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_remote_eval__body(s_expression_for_remote_eval);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_remote_eval:
    return result;
}

/* INITIALIZE-I-AM-ALIVE-INFO */
Object initialize_i_am_alive_info(icp_socket,
	    function_to_determine_if_icp_connection_clogged_qm)
    Object icp_socket, function_to_determine_if_icp_connection_clogged_qm;
{
    Object i_am_alive_info, fixnum_time;

    x_note_fn_call(52,99);
    i_am_alive_info = make_i_am_alive_info_1();
    fixnum_time = c_native_clock_ticks_or_cache(Nil,Nil);
    SVREF(i_am_alive_info,FIX((SI_Long)10L)) = 
	    function_to_determine_if_icp_connection_clogged_qm;
    SVREF(i_am_alive_info,FIX((SI_Long)3L)) = fixnum_time;
    SVREF(i_am_alive_info,FIX((SI_Long)4L)) = fixnum_time;
    ISVREF(i_am_alive_info,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(i_am_alive_info,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(i_am_alive_info,(SI_Long)7L) = FIX((SI_Long)0L);
    ISVREF(i_am_alive_info,(SI_Long)8L) = FIX((SI_Long)0L);
    ISVREF(i_am_alive_info,(SI_Long)9L) = FIX((SI_Long)0L);
    ISVREF(i_am_alive_info,(SI_Long)14L) = FIX((SI_Long)0L);
    return VALUES_1(SVREF(icp_socket,FIX((SI_Long)24L)) = i_am_alive_info);
}

DEFINE_VARIABLE_WITH_SYMBOL(Deadman_switch_time_interval, Qdeadman_switch_time_interval);

/* DO-I-AM-ALIVE-PROCESSING */
Object do_i_am_alive_processing(icp_socket)
    Object icp_socket;
{
    Object i_am_alive_info, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(52,100);
    i_am_alive_info = ISVREF(icp_socket,(SI_Long)24L);
    if (i_am_alive_info) {
	handle_unclogged_connection_if_necessary(i_am_alive_info);
	send_i_am_alive_if_necessary(icp_socket,i_am_alive_info);
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(ISVREF(i_am_alive_info,(SI_Long)4L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    temp = FIX(gensymed_symbol - gensymed_symbol_1);
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    temp = FIX(gensymed_symbol + (SI_Long)1L);
	}
	if (FIXNUM_GT(temp,Deadman_switch_time_interval))
	    return VALUES_1(SVREF(i_am_alive_info,FIX((SI_Long)1L)) = Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Sending_i_am_alive_qm, Qsending_i_am_alive_qm);

DEFINE_VARIABLE_WITH_SYMBOL(I_am_alive_send_time_interval_in_seconds, Qi_am_alive_send_time_interval_in_seconds);

DEFINE_VARIABLE_WITH_SYMBOL(I_am_alive_send_time_interval_in_seconds_as_float, Qi_am_alive_send_time_interval_in_seconds_as_float);

DEFINE_VARIABLE_WITH_SYMBOL(I_am_alive_send_time_interval, Qi_am_alive_send_time_interval);

/* SEND-I-AM-ALIVE-IF-NECESSARY */
Object send_i_am_alive_if_necessary(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    Object system_1, temp, temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(52,101);
    system_1 = ISVREF(icp_socket,(SI_Long)25L);
    if (system_1);
    else
	system_1 = Qg2;
    if (EQ(system_1,Qg2) || EQ(system_1,Qtelewindows)) {
	if (Sending_i_am_alive_qm || Handling_solitary_i_am_alive_qm)
	    return schedule_send_i_am_alive_message(icp_socket,
		    i_am_alive_info);
	else {
	    gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	    gensymed_symbol_1 = IFIX(ISVREF(i_am_alive_info,(SI_Long)3L));
	    if (gensymed_symbol >= gensymed_symbol_1)
		temp = FIX(gensymed_symbol - gensymed_symbol_1);
	    else {
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    temp_1 = FIXNUM_GT(temp,I_am_alive_send_time_interval);
	    if (temp_1);
	    else {
		temp = ISVREF(i_am_alive_info,(SI_Long)5L);
		if (EQ(system_1,Qg2))
		    temp_2 = FIX((SI_Long)5L);
		else if (EQ(system_1,Qtelewindows))
		    temp_2 = FIX((SI_Long)1L);
		else
		    temp_2 = FIX((SI_Long)0L);
		temp_1 = NUM_GT(temp,temp_2);
	    }
	    if (temp_1);
	    else
		temp_1 = IFIX(ISVREF(i_am_alive_info,(SI_Long)6L)) > 
			(SI_Long)30000L;
	    if (temp_1)
		return send_i_am_alive_message(icp_socket,i_am_alive_info);
	    else
		return schedule_send_i_am_alive_message(icp_socket,
			i_am_alive_info);
	}
    }
    else
	return VALUES_1(Nil);
}

/* SEND-I-AM-ALIVE-MESSAGE */
Object send_i_am_alive_message(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object sending_i_am_alive_qm, current_icp_port, current_icp_socket, temp_1;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(13);

    x_note_fn_call(52,102);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)51L);
    if (CAS_SVREF(icp_socket,(SI_Long)51L,gensymed_symbol,Nil)) {
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
    if ((SI_Long)2L == IFIX(ISVREF(icp_socket,(SI_Long)15L)) &&  
	    !TRUEP(ISVREF(ISVREF(icp_socket,(SI_Long)4L),(SI_Long)4L))) {
	sending_i_am_alive_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Sending_i_am_alive_qm,Qsending_i_am_alive_qm,sending_i_am_alive_qm,
		12);
	  current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		  11);
	    current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		    10);
	      temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		      (SI_Long)17L ? ISVREF(Current_icp_socket,
		      (SI_Long)53L) : Nil;
	      if (temp_1);
	      else
		  temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			  Qtelewindows) ? T : Nil;
	      disable_resumability = temp_1;
	      PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		      9);
		number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			8);
		  icp_buffers_for_message_group = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			  7);
		    icp_buffer_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			    6);
		      icp_byte_position_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			      5);
			number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				4);
			  current_icp_buffer = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				  3);
			    current_write_icp_byte_position = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				    2);
			      number_of_icp_bytes_in_message_group = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				      1);
				writing_icp_message_group = 
					FIXNUM_ADD1(Writing_icp_message_group);
				PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					0);
				  gensymed_symbol = Nil;
				  gensymed_symbol_1 = 0.0;
				  gensymed_symbol_2 = 0.0;
				  if (Profiling_enabled_qm) {
				      gensymed_symbol = T;
				      gensymed_symbol_1 = 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L),(SI_Long)0L);
				      gensymed_symbol_2 = 
					      g2ext_unix_time_as_float();
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L);
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      gensymed_symbol_2);
				  }
				  if (icp_connection_open_p(Current_icp_socket) 
					  &&  
					  !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					      {
				      send_icp_i_am_alive(ISVREF(i_am_alive_info,
					      (SI_Long)8L));
				      end_icp_message_group();
				  }
				  if (Profiling_enabled_qm) {
				      gensymed_symbol_3 = 
					      g2ext_unix_time_as_float();
				      gensymed_symbol_4 = 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L),(SI_Long)0L);
				      gensymed_symbol_5 = 
					      gensymed_symbol_3 - 
					      gensymed_symbol_4;
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L);
				      aref_new_value = gensymed_symbol_5 + 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L),(SI_Long)0L);
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      aref_new_value);
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L);
				      aref_new_value = gensymed_symbol ? 
					      gensymed_symbol_1 + 
					      gensymed_symbol_5 + 
					      (gensymed_symbol_4 - 
					      gensymed_symbol_2) : 
					      gensymed_symbol_3;
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      aref_new_value);
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
	POP_SPECIAL();
	temp = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(i_am_alive_info,FIX((SI_Long)3L)) = temp;
	ISVREF(i_am_alive_info,(SI_Long)5L) = FIX((SI_Long)0L);
	ISVREF(i_am_alive_info,(SI_Long)6L) = FIX((SI_Long)0L);
    }
    return schedule_send_i_am_alive_message(icp_socket,i_am_alive_info);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qsend_i_am_alive_message;  /* send-i-am-alive-message */

/* SCHEDULE-SEND-I-AM-ALIVE-MESSAGE */
Object schedule_send_i_am_alive_message(icp_socket,i_am_alive_info)
    Object icp_socket, i_am_alive_info;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double temp_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(52,103);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)51L);
    if ( !(schedule_task_qm && ISVREF(schedule_task_qm,(SI_Long)6L))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)51L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	temp_1 = 
		DOUBLE_FLOAT_TO_DOUBLE(I_am_alive_send_time_interval_in_seconds_as_float);
	aref_new_value = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
		temp_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qsend_i_am_alive_message;
	temp = SYMBOL_FUNCTION(Qsend_i_am_alive_message);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	SVREF(task,FIX((SI_Long)14L)) = i_am_alive_info;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)51L,old,new_1)) {
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
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old;
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
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(Nil);
}

/* UPDATE-ICP-BYTES-PER-SECOND-IF-POSSIBLE */
Object update_icp_bytes_per_second_if_possible(i_am_alive_info,
	    outstanding_icp_bytes_originally)
    Object i_am_alive_info, outstanding_icp_bytes_originally;
{
    Object icp_bytes_sent_and_handled;
    SI_Long gensymed_symbol, gensymed_symbol_1, processing_interval, temp;
    SI_Long new_bytes_per_second;

    x_note_fn_call(52,104);
    icp_bytes_sent_and_handled = 
	    FIXNUM_MINUS(outstanding_icp_bytes_originally,
	    ISVREF(i_am_alive_info,(SI_Long)14L));
    if (IFIX(icp_bytes_sent_and_handled) > (SI_Long)2048L) {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(ISVREF(i_am_alive_info,(SI_Long)3L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    processing_interval = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    processing_interval = gensymed_symbol + (SI_Long)1L;
	}
	if (processing_interval > (SI_Long)10L) {
	    temp = IFIX(FIXNUM_TIMES(icp_bytes_sent_and_handled,
		    Fixnum_time_units_per_second)) / processing_interval;
	    new_bytes_per_second = temp;
	    ISVREF(i_am_alive_info,(SI_Long)16L) = FIX(new_bytes_per_second);
	}
    }
    return VALUES_1(Nil);
}

static Object Qsend_icp_i_am_alive;  /* send-icp-i-am-alive */

static Object Qi_am_alive;         /* i-am-alive */

static Object Qmessage_group_id;   /* message-group-id */

/* SEND-ICP-I-AM-ALIVE */
Object send_icp_i_am_alive(message_group_id)
    Object message_group_id;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,105);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_i_am_alive;
	  }
	  start_writing_icp_message(FIX((SI_Long)14L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
	      }
	      else
		  tracep = Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qi_am_alive,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(message_group_id);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmessage_group_id,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(message_group_id);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qi_am_alive,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_unsigned_integer(message_group_id);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qmessage_group_id,string_constant_2,Qargument,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_unsigned_integer(message_group_id);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_i_am_alive,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_i_am_alive,top,Nil);
		goto end_send_icp_i_am_alive;
	    }
	}
	message_group_id = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : message_group_id;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_i_am_alive;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)14L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
	      }
	      else
		  tracep = Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qi_am_alive,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(message_group_id))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmessage_group_id,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(message_group_id))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qi_am_alive,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(message_group_id))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qmessage_group_id,string_constant_2,Qargument,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_unsigned_integer(message_group_id))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(message_group_id);
	      resumable_icp_push(Qsend_icp_i_am_alive);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_i_am_alive;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_i_am_alive:
    return result;
}

static Object Qicp;                /* icp */

/* HANDLE-ICP-I-AM-ALIVE--BODY */
Object handle_icp_i_am_alive__body(message_group_id)
    Object message_group_id;
{
    Object i_am_alive_info_qm, temp, message_group_ids_and_byte_counts_qm;
    Object outstanding_icp_bytes_originally, trailing_entry_cons;
    Object entry_cons_qm, delta_of_outstanding_icp_bytes, entry, ab_loop_list_;
    Object incff_1_arg, decff_1_arg, icp_cons, svref_arg_2;

    x_note_fn_call(52,106);
    i_am_alive_info_qm = ISVREF(Current_icp_socket,(SI_Long)24L);
    if (i_am_alive_info_qm) {
	temp = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(i_am_alive_info_qm,FIX((SI_Long)4L)) = temp;
	SVREF(i_am_alive_info_qm,FIX((SI_Long)9L)) = message_group_id;
	message_group_ids_and_byte_counts_qm = ISVREF(i_am_alive_info_qm,
		(SI_Long)12L);
	if (message_group_ids_and_byte_counts_qm) {
	    outstanding_icp_bytes_originally = ISVREF(i_am_alive_info_qm,
		    (SI_Long)14L);
	    trailing_entry_cons = message_group_ids_and_byte_counts_qm;
	    entry_cons_qm = Nil;
	  next_loop:
	    entry_cons_qm = CDR(trailing_entry_cons);
	    if ( !TRUEP(entry_cons_qm))
		goto end_loop;
	    if (FIXNUM_EQ(M_CAR(M_CAR(entry_cons_qm)),message_group_id)) {
		SVREF(i_am_alive_info_qm,FIX((SI_Long)12L)) = entry_cons_qm;
		M_CDR(trailing_entry_cons) = Nil;
		delta_of_outstanding_icp_bytes = FIX((SI_Long)0L);
		entry = Nil;
		ab_loop_list_ = message_group_ids_and_byte_counts_qm;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		entry = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		incff_1_arg = CDR(entry);
		delta_of_outstanding_icp_bytes = 
			FIXNUM_ADD(delta_of_outstanding_icp_bytes,incff_1_arg);
		reclaim_icp_cons_1(entry);
		goto next_loop_1;
	      end_loop_1:
		decff_1_arg = delta_of_outstanding_icp_bytes;
		temp = FIXNUM_MINUS(ISVREF(i_am_alive_info_qm,
			(SI_Long)14L),decff_1_arg);
		SVREF(i_am_alive_info_qm,FIX((SI_Long)14L)) = temp;
		if (message_group_ids_and_byte_counts_qm &&  !((SI_Long)0L 
			== inline_debugging_consing())) {
		    icp_cons = message_group_ids_and_byte_counts_qm;
		  next_loop_2:
		    inline_note_reclaim_cons(icp_cons,Qicp);
		    if (EQ(icp_cons,trailing_entry_cons))
			goto end_1;
		    else if ( !TRUEP(icp_cons))
			goto end_1;
		    else
			icp_cons = CDR(icp_cons);
		    goto next_loop_2;
		  end_loop_2:
		  end_1:;
		}
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = message_group_ids_and_byte_counts_qm;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = trailing_entry_cons;
		}
		else {
		    temp = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = 
			    message_group_ids_and_byte_counts_qm;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = trailing_entry_cons;
		}
		M_CDR(trailing_entry_cons) = Nil;
		goto end_loop;
	    }
	    trailing_entry_cons = entry_cons_qm;
	    goto next_loop;
	  end_loop:;
	    update_icp_bytes_per_second_if_possible(i_am_alive_info_qm,
		    outstanding_icp_bytes_originally);
	}
	update_icp_connection_clogged_p(i_am_alive_info_qm,Nil);
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_i_am_alive;  /* handle-icp-i-am-alive */

/* HANDLE-ICP-I-AM-ALIVE */
Object handle_icp_i_am_alive()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, message_group_id;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,107);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)2L ? T : Nil;
	    }
	    else
		tracep = Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qi_am_alive,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    message_group_id = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  message_group_id = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_i_am_alive__body(message_group_id);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qi_am_alive,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmessage_group_id,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  message_group_id = result_of_read;
		POP_SPECIAL();
	    }
	    else
		message_group_id = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_i_am_alive__body(message_group_id);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_i_am_alive,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_i_am_alive,top,Nil);
		goto end_handle_icp_i_am_alive;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)2L ? T : Nil;
	    }
	    else
		tracep = Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qi_am_alive,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  message_group_id = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_i_am_alive);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_i_am_alive;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    message_group_id = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_i_am_alive);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_i_am_alive;
		  }
		  message_group_id = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_i_am_alive__body(message_group_id);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qi_am_alive,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		message_group_id = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_i_am_alive);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_i_am_alive;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmessage_group_id,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  message_group_id = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_i_am_alive);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_i_am_alive;
		}
		message_group_id = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_i_am_alive__body(message_group_id);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_i_am_alive:
    return result;
}

static Object Qsend_icp_message_group_id;  /* send-icp-message-group-id */

static Object Qnumber_of_icp_bytes;  /* number-of-icp-bytes */

/* SEND-ICP-MESSAGE-GROUP-ID */
Object send_icp_message_group_id(message_group_id,number_of_icp_bytes)
    Object message_group_id, number_of_icp_bytes;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,108);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_message_group_id;
	  }
	  start_writing_icp_message(FIX((SI_Long)181L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
	      }
	      else
		  tracep = Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(message_group_id);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmessage_group_id,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(message_group_id);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(number_of_icp_bytes);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_icp_bytes,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(number_of_icp_bytes);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qmessage_group_id,string_constant,Qmessage,Nil,
			    Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(message_group_id);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(message_group_id);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(number_of_icp_bytes);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(number_of_icp_bytes);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_message_group_id,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_message_group_id,top,Nil);
		goto end_send_icp_message_group_id;
	    }
	}
	message_group_id = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : message_group_id;
	number_of_icp_bytes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : number_of_icp_bytes;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_message_group_id;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)181L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
	      }
	      else
		  tracep = Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(message_group_id))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qmessage_group_id,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(message_group_id))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(number_of_icp_bytes))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_icp_bytes,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(number_of_icp_bytes))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qmessage_group_id,string_constant,Qmessage,Nil,
			    Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(message_group_id))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(message_group_id))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(number_of_icp_bytes))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(number_of_icp_bytes))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(number_of_icp_bytes);
	      resumable_icp_push(message_group_id);
	      resumable_icp_push(Qsend_icp_message_group_id);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_message_group_id;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_message_group_id:
    return result;
}

/* HANDLE-ICP-MESSAGE-GROUP-ID--BODY */
Object handle_icp_message_group_id__body(message_group_id,number_of_icp_bytes)
    Object message_group_id, number_of_icp_bytes;
{
    Object i_am_alive_info_qm, svref_new_value;

    x_note_fn_call(52,109);
    i_am_alive_info_qm = ISVREF(Current_icp_socket,(SI_Long)24L);
    if (i_am_alive_info_qm) {
	SVREF(i_am_alive_info_qm,FIX((SI_Long)8L)) = message_group_id;
	svref_new_value = FIXNUM_ADD1(ISVREF(i_am_alive_info_qm,(SI_Long)5L));
	SVREF(i_am_alive_info_qm,FIX((SI_Long)5L)) = svref_new_value;
	send_i_am_alive_if_necessary(Current_icp_socket,i_am_alive_info_qm);
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_message_group_id;  /* handle-icp-message-group-id */

/* HANDLE-ICP-MESSAGE-GROUP-ID */
Object handle_icp_message_group_id()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, message_group_id;
    Object number_of_icp_bytes, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,110);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)2L ? T : Nil;
	    }
	    else
		tracep = Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    message_group_id = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  message_group_id = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    number_of_icp_bytes = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  number_of_icp_bytes = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_message_group_id__body(message_group_id,
			number_of_icp_bytes);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qmessage_group_id,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmessage_group_id,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  message_group_id = result_of_read;
		POP_SPECIAL();
	    }
	    else
		message_group_id = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_icp_bytes,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  number_of_icp_bytes = result_of_read;
		POP_SPECIAL();
	    }
	    else
		number_of_icp_bytes = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_message_group_id__body(message_group_id,
		      number_of_icp_bytes);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_message_group_id,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_message_group_id,top,Nil);
		goto end_handle_icp_message_group_id;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    if ( !TRUEP(Trace_skip_data_service_i_am_alive_messages_p)) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)2L ? T : Nil;
	    }
	    else
		tracep = Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  message_group_id = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_message_group_id);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_message_group_id;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qmessage_group_id,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    message_group_id = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_message_group_id);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_message_group_id;
		  }
		  message_group_id = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  number_of_icp_bytes = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(message_group_id);
			resumable_icp_push(Qhandle_icp_message_group_id);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_message_group_id;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_icp_bytes,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    number_of_icp_bytes = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(message_group_id);
		      resumable_icp_push(Qhandle_icp_message_group_id);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_message_group_id;
		  }
		  number_of_icp_bytes = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_message_group_id__body(message_group_id,
			number_of_icp_bytes);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qmessage_group_id,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		message_group_id = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qmessage_group_id,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_message_group_id);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_message_group_id;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qmessage_group_id,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  message_group_id = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_message_group_id);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_message_group_id;
		}
		message_group_id = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		number_of_icp_bytes = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qnumber_of_icp_bytes,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(message_group_id);
		      resumable_icp_push(Qhandle_icp_message_group_id);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_message_group_id;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_icp_bytes,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  number_of_icp_bytes = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(message_group_id);
		    resumable_icp_push(Qhandle_icp_message_group_id);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_message_group_id;
		}
		number_of_icp_bytes = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_message_group_id__body(message_group_id,
		      number_of_icp_bytes);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_message_group_id:
    return result;
}

/* NUMBER-OF-OUTSTANDING-MESSAGE-GROUPS */
Object number_of_outstanding_message_groups(i_am_alive_info)
    Object i_am_alive_info;
{
    Object message_group_id_1, message_group_id_2;

    x_note_fn_call(52,111);
    message_group_id_1 = ISVREF(i_am_alive_info,(SI_Long)7L);
    message_group_id_2 = ISVREF(i_am_alive_info,(SI_Long)9L);
    if (FIXNUM_GE(message_group_id_1,message_group_id_2))
	return VALUES_1(FIXNUM_MINUS(message_group_id_1,message_group_id_2));
    else
	return VALUES_1(FIXNUM_ADD1(FIXNUM_ADD(message_group_id_1,
		FIXNUM_MINUS(Most_positive_fixnum,message_group_id_2))));
}

/* BYTE-ALLOTMENT-FOR-ICP-OUTPUT-PORT */
Object byte_allotment_for_icp_output_port(icp_output_port,
	    interval_as_fixnum_time)
    Object icp_output_port, interval_as_fixnum_time;
{
    Object i_am_alive_info_qm;
    SI_Long channel_transmission_rate, maximum_channel_buffer_size;
    SI_Long current_amount_enqueued_in_channel_buffer;
    SI_Long prefered_channel_loading, maximum_bytes_to_avoid_clogging, temp;
    SI_Long bytes_to_achieve_full_loading;

    x_note_fn_call(52,112);
    i_am_alive_info_qm = ISVREF(icp_output_port,(SI_Long)2L);
    channel_transmission_rate = (SI_Long)100000L;
    maximum_channel_buffer_size = (SI_Long)100000L;
    current_amount_enqueued_in_channel_buffer = i_am_alive_info_qm ? 
	    IFIX(ISVREF(i_am_alive_info_qm,(SI_Long)14L)) << (SI_Long)1L : 
	    (SI_Long)0L;
    prefered_channel_loading = (SI_Long)1L;
    maximum_bytes_to_avoid_clogging = maximum_channel_buffer_size - 
	    current_amount_enqueued_in_channel_buffer;
    temp = IFIX(FIXNUM_TIMES(l_round(FIX(channel_transmission_rate),
	    Fixnum_time_units_per_second),interval_as_fixnum_time)) * 
	    prefered_channel_loading;
    bytes_to_achieve_full_loading = MAX(maximum_bytes_to_avoid_clogging,temp);
    return VALUES_2(FIX(bytes_to_achieve_full_loading),
	    FIX(maximum_bytes_to_avoid_clogging));
}

/* DUMP-ICP-BUFFER */
Object dump_icp_buffer(icp_buffer)
    Object icp_buffer;
{
    Object j, icp_byte, array;
    SI_Long i, ab_loop_bind_, icp_position, position_1, temp;

    x_note_fn_call(52,113);
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
		ISVREF(Icp_message_handler_array,IFIX(icp_byte) - 
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

Object Icp_message_out_of_synch_case_2_warning = UNBOUND;

static Object string_constant_7;   /* "~5T Protocol out-of-synch (case 2)" */

/* ICP-CASE-2-ERROR */
Object icp_case_2_error(icp_input_port,message_series_byte_count,
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
    x_note_fn_call(52,114);
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
    dump_icp_buffer(icp_buffer_qm);
    icp_error_internal(Qerror,string_constant_7,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_host_name, Qlocal_host_name);

/* GET-LOCAL-HOST-NAME */
Object get_local_host_name()
{
    Object temp;

    x_note_fn_call(52,115);
    temp = Local_host_name;
    if (temp)
	return VALUES_1(temp);
    else {
	Local_host_name = get_unix_host_name();
	return VALUES_1(Local_host_name);
    }
}

static Object Qunix_tcp_listener_port;  /* unix-tcp-listener-port */

/* GET-CURRENT-ICP-CONTACT-PORT-NUMBER-OR-NAME-IF-ANY */
Object get_current_icp_contact_port_number_or_name_if_any()
{
    Object symbol_qm;

    x_note_fn_call(52,116);
    symbol_qm = Qunix_tcp_listener_port;
    if (symbol_qm && BOUNDP(symbol_qm))
	return VALUES_1(SYMBOL_VALUE(symbol_qm));
    else
	return VALUES_1(Nil);
}

static Object Qsend_icp_connection_denied;  /* send-icp-connection-denied */

static Object Qconnection_denied;  /* connection-denied */

/* SEND-ICP-CONNECTION-DENIED */
Object send_icp_connection_denied()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,117);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_denied;
	  }
	  start_writing_icp_message(FIX((SI_Long)305L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qconnection_denied,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_denied,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_connection_denied,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_connection_denied,top,Nil);
		goto end_send_icp_connection_denied;
	    }
	}
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_denied;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)305L)))) {
	      resumable_icp_push(Qsend_icp_connection_denied);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_connection_denied;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qconnection_denied,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_denied,string_constant,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_connection_denied:
    return result;
}

static Object string_constant_8;   /* "ICP connection \"~a\" is closed to remote users.~%" */

/* HANDLE-ICP-CONNECTION-DENIED--BODY */
Object handle_icp_connection_denied__body()
{
    x_note_fn_call(52,118);
    notify_user(2,string_constant_8,ISVREF(Current_icp_socket,(SI_Long)2L));
    return VALUES_1(Nil);
}

static Object Qhandle_icp_connection_denied;  /* handle-icp-connection-denied */

/* HANDLE-ICP-CONNECTION-DENIED */
Object handle_icp_connection_denied()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(52,119);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qconnection_denied,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_connection_denied__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qconnection_denied,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_connection_denied__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_connection_denied,top))
		return icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_connection_denied,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qconnection_denied,
			string_constant,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_connection_denied__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qconnection_denied,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_connection_denied__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_no_license;  /* send-icp-no-license */

static Object Qno_license;         /* no-license */

/* SEND-ICP-NO-LICENSE */
Object send_icp_no_license()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,120);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_no_license;
	  }
	  start_writing_icp_message(FIX((SI_Long)307L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qno_license,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qno_license,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_no_license,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_no_license,top,Nil);
		goto end_send_icp_no_license;
	    }
	}
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_no_license;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)307L)))) {
	      resumable_icp_push(Qsend_icp_no_license);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_no_license;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qno_license,
			  string_constant,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qno_license,string_constant,Qmessage,Nil,Nil,
			    Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_no_license:
    return result;
}

static Object string_constant_9;   /* "No license is available for a connection over \"~a\".~%" */

/* HANDLE-ICP-NO-LICENSE--BODY */
Object handle_icp_no_license__body()
{
    x_note_fn_call(52,121);
    notify_user(2,string_constant_9,ISVREF(Current_icp_socket,(SI_Long)2L));
    return VALUES_1(Nil);
}

static Object Qhandle_icp_no_license;  /* handle-icp-no-license */

/* HANDLE-ICP-NO-LICENSE */
Object handle_icp_no_license()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(52,122);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qno_license,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_no_license__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qno_license,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_no_license__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_no_license,top))
		return icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_no_license,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qno_license,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_no_license__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qno_license,string_constant,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_no_license__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_connection_shutdown_imminent;  /* send-icp-connection-shutdown-imminent */

static Object Qconnection_shutdown_imminent;  /* connection-shutdown-imminent */

static Object Qtime_until_shutdown;  /* time-until-shutdown */

/* SEND-ICP-CONNECTION-SHUTDOWN-IMMINENT */
Object send_icp_connection_shutdown_imminent(time_until_shutdown)
    Object time_until_shutdown;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(52,123);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_shutdown_imminent;
	  }
	  start_writing_icp_message(FIX((SI_Long)306L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qconnection_shutdown_imminent,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qtime_until_shutdown,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(time_until_shutdown);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qtime_until_shutdown,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(time_until_shutdown);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_shutdown_imminent,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qtime_until_shutdown,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_unsigned_integer(time_until_shutdown);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qtime_until_shutdown,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_unsigned_integer(time_until_shutdown);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_connection_shutdown_imminent,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qsend_icp_connection_shutdown_imminent,top,Nil);
		goto end_send_icp_connection_shutdown_imminent;
	    }
	}
	time_until_shutdown = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : time_until_shutdown;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_shutdown_imminent;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)306L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qconnection_shutdown_imminent,string_constant,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qtime_until_shutdown,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(time_until_shutdown))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qtime_until_shutdown,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(time_until_shutdown))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_shutdown_imminent,string_constant,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qtime_until_shutdown,
			  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(time_until_shutdown))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qtime_until_shutdown,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_unsigned_integer(time_until_shutdown))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(time_until_shutdown);
	      resumable_icp_push(Qsend_icp_connection_shutdown_imminent);
	      result = VALUES_1(Icp_suspend);
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

static Object string_constant_10;  /* "ICP connection \"~a\" will be shut down within ~a seconds.~%~
				    *      That process has disallowed remote connections.~%"
				    */

/* HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT--BODY */
Object handle_icp_connection_shutdown_imminent__body(time_until_shutdown)
    Object time_until_shutdown;
{
    x_note_fn_call(52,124);
    notify_user(3,string_constant_10,ISVREF(Current_icp_socket,
	    (SI_Long)2L),time_until_shutdown);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_connection_shutdown_imminent;  /* handle-icp-connection-shutdown-imminent */

/* HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT */
Object handle_icp_connection_shutdown_imminent()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, time_until_shutdown;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(52,125);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qconnection_shutdown_imminent,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtime_until_shutdown,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtime_until_shutdown,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    time_until_shutdown = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  time_until_shutdown = read_icp_unsigned_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qconnection_shutdown_imminent,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtime_until_shutdown,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtime_until_shutdown,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  time_until_shutdown = result_of_read;
		POP_SPECIAL();
	    }
	    else
		time_until_shutdown = read_icp_unsigned_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_connection_shutdown_imminent,top)) {
		result = icp_error_internal(Qerror,string_constant_3,
			Qhandle_icp_connection_shutdown_imminent,top,Nil);
		goto end_handle_icp_connection_shutdown_imminent;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qconnection_shutdown_imminent,string_constant,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  time_until_shutdown = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtime_until_shutdown,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_connection_shutdown_imminent);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_connection_shutdown_imminent;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtime_until_shutdown,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    time_until_shutdown = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_connection_shutdown_imminent);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_connection_shutdown_imminent;
		  }
		  time_until_shutdown = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qconnection_shutdown_imminent,string_constant,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		time_until_shutdown = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtime_until_shutdown,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_connection_shutdown_imminent);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_connection_shutdown_imminent;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtime_until_shutdown,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  time_until_shutdown = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_connection_shutdown_imminent);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_connection_shutdown_imminent;
		}
		time_until_shutdown = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_connection_shutdown_imminent__body(time_until_shutdown);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_connection_shutdown_imminent:
    return result;
}

/* DISALLOW-NEW-ICP-LISTENER-CONNECTION */
Object disallow_new_icp_listener_connection(new_icp_socket)
    Object new_icp_socket;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(52,126);
    current_icp_port = ISVREF(new_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_connection_denied();
				end_icp_message_group();
			    }
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
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
    return flush_and_shutdown_icp_socket(new_icp_socket);
}

/* NO-LICENSE-FOR-NEW-ICP-LISTENER-CONNECTION */
Object no_license_for_new_icp_listener_connection(new_icp_socket)
    Object new_icp_socket;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(52,127);
    current_icp_port = ISVREF(new_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
		    Qtelewindows) ? T : Nil;
	disable_resumability = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(Writing_icp_message_group);
			  PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_2 = 0.0;
			    if (Profiling_enabled_qm) {
				gensymed_symbol = T;
				gensymed_symbol_1 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_no_license();
				end_icp_message_group();
			    }
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
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
    return flush_and_shutdown_icp_socket(new_icp_socket);
}

/* WARN-DISALLOWED-ICP-LISTENER-CONNECTIONS */
Object warn_disallowed_icp_listener_connections varargs_1(int, n)
{
    Object new_icp_listener_connections;
    Object specific_clients_qm, new_icp_socket, ab_loop_list_, list_1;
    Object icp_socket, next_list, listener_client_qm, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_varargs_nonrelocating;
    Declare_special(12);

    x_note_fn_call(52,128);
    INIT_ARGS_nonrelocating();
    new_icp_listener_connections = REQUIRED_ARG_nonrelocating();
    specific_clients_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(specific_clients_qm)) {
	new_icp_socket = Nil;
	ab_loop_list_ = new_icp_listener_connections;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	new_icp_socket = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	disallow_new_icp_listener_connection(new_icp_socket);
	goto next_loop;
      end_loop:;
    }
    list_1 = Active_icp_sockets;
    icp_socket = Nil;
    next_list = Nil;
  next_loop_1:
    icp_socket = CAR(list_1);
    next_list = CDR(list_1);
    if ( !TRUEP(list_1))
	goto end_loop_1;
    listener_client_qm = ISVREF(icp_socket,(SI_Long)25L);
    if (listener_client_qm && ISVREF(icp_socket,(SI_Long)33L) &&  
	    !TRUEP(ISVREF(icp_socket,(SI_Long)26L)) && 
	    (specific_clients_qm ? TRUEP(memq_function(listener_client_qm,
	    specific_clients_qm)) : TRUEP(T))) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_connection_shutdown_imminent(Shutdown_interval_for_disallowed_icp_connection_in_seconds);
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
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
	temp_1 = c_native_clock_ticks_or_cache(Nil,Nil);
	SVREF(icp_socket,FIX((SI_Long)27L)) = temp_1;
	SVREF(icp_socket,FIX((SI_Long)26L)) = T;
	Refused_icp_listener_connections = icp_cons_1(icp_socket,
		Refused_icp_listener_connections);
    }
    list_1 = next_list;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

void int3b_INIT()
{
    Object AB_package, list_constant_38, Qint3b, Qget_unix_host_name, Kfuncall;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, float_constant_1;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_34, list_constant_33, list_constant_32;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_22, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, list_constant_17;
    Object list_constant_16, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, list_constant_11;
    Object list_constant_4, list_constant_10, list_constant_8, list_constant_9;
    Object list_constant_7, list_constant, Qgsi_references_in_use, Qgsi;
    Object list_constant_5, list_constant_6, list_constant_2, list_constant_1;
    Object Qlatest_icp_window_protocol_version, list_constant_3;
    Object Qicp_value_reclaimer, Qreclaim_icp_list;

    x_note_fn_call(52,129);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsend_icp_enlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("SEND-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Qcorresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    Qenlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    string_constant = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qname_of_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("NAME-OF-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    string_constant_1 = STATIC_STRING("[object arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qnew_index_limit_plus_one = STATIC_SYMBOL("NEW-INDEX-LIMIT-PLUS-ONE",
	    AB_package);
    string_constant_2 = STATIC_STRING("[value arg]");
    string_constant_3 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qsend_icp_enlarge_corresponding_icp_object_index_space,
	    STATIC_FUNCTION(send_icp_enlarge_corresponding_icp_object_index_space,
	    NIL,FALSE,2,2));
    Qhandle_icp_enlarge_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-ENLARGE-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_enlarge_corresponding_icp_object_index_space,
	    STATIC_FUNCTION(handle_icp_enlarge_corresponding_icp_object_index_space,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_enlarge_corresponding_icp_object_index_space,
	    FIX((SI_Long)15L));
    Qicp_port_for_reclaim = STATIC_SYMBOL("ICP-PORT-FOR-RECLAIM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_port_for_reclaim,Icp_port_for_reclaim);
    Qint3b = STATIC_SYMBOL("INT3B",AB_package);
    record_system_variable(Qicp_port_for_reclaim,Qint3b,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    if (Deregister_and_register_item_p == UNBOUND)
	Deregister_and_register_item_p = Nil;
    if (Deregister_but_do_not_remove_from_table_p == UNBOUND)
	Deregister_but_do_not_remove_from_table_p = Nil;
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qitem_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qgsi_instance = STATIC_SYMBOL("GSI-INSTANCE",AB_package);
    Qregistered_item = STATIC_SYMBOL("REGISTERED-ITEM",AB_package);
    Qderegister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qderegister_corresponding_icp_object,
	    STATIC_FUNCTION(deregister_corresponding_icp_object,NIL,FALSE,
	    5,5));
    Qreclaimer_for_icp_object = STATIC_SYMBOL("RECLAIMER-FOR-ICP-OBJECT",
	    AB_package);
    Qderegister_corresponding_icp_object_index_space_name = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME",
	    AB_package);
    string_constant_4 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qwrite_icp_deregister_corresponding_icp_object_index_space_name = 
	    STATIC_SYMBOL("WRITE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_deregister_corresponding_icp_object_index_space_name,
	    STATIC_FUNCTION(write_icp_deregister_corresponding_icp_object_index_space_name,
	    NIL,FALSE,1,1));
    Qread_icp_deregister_corresponding_icp_object_index_space_name = 
	    STATIC_SYMBOL("READ-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT-INDEX-SPACE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_deregister_corresponding_icp_object_index_space_name,
	    STATIC_FUNCTION(read_icp_deregister_corresponding_icp_object_index_space_name,
	    NIL,FALSE,0,0));
    Qsend_icp_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qcorresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(send_icp_deregister_corresponding_icp_object,
	    NIL,FALSE,2,2));
    Qhandle_icp_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(handle_icp_deregister_corresponding_icp_object,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_deregister_corresponding_icp_object,
	    FIX((SI_Long)323L));
    Qsend_icp_deregister_original_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT",
	    AB_package);
    Qderegister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_deregister_original_icp_object,
	    STATIC_FUNCTION(send_icp_deregister_original_icp_object,NIL,
	    FALSE,2,2));
    Qhandle_icp_deregister_original_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-ORIGINAL-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_deregister_original_icp_object,
	    STATIC_FUNCTION(handle_icp_deregister_original_icp_object,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_deregister_original_icp_object,
	    FIX((SI_Long)324L));
    Qsend_icp_delete_icp_object_for_process = 
	    STATIC_SYMBOL("SEND-ICP-DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    Qdelete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_delete_icp_object_for_process,
	    STATIC_FUNCTION(send_icp_delete_icp_object_for_process,NIL,
	    FALSE,2,2));
    Qhandle_icp_delete_icp_object_for_process = 
	    STATIC_SYMBOL("HANDLE-ICP-DELETE-ICP-OBJECT-FOR-PROCESS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_delete_icp_object_for_process,
	    STATIC_FUNCTION(handle_icp_delete_icp_object_for_process,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_delete_icp_object_for_process,
	    FIX((SI_Long)163L));
    Qsend_icp_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qacknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_acknowledge_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(send_icp_acknowledge_deregister_corresponding_icp_object,
	    NIL,FALSE,2,2));
    Qhandle_icp_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_acknowledge_deregister_corresponding_icp_object,
	    STATIC_FUNCTION(handle_icp_acknowledge_deregister_corresponding_icp_object,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_acknowledge_deregister_corresponding_icp_object,
	    FIX((SI_Long)325L));
    Qderegister_icp_objects_operation = 
	    STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS-OPERATION",AB_package);
    Qderegister_corresponding_icp_object_with_deassign = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-WITH-DEASSIGN",
	    AB_package);
    Qdelete_icp_object_for_process_with_deassign = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS-WITH-DEASSIGN",
	    AB_package);
    Qderegister_and_register_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-AND-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qwrite_icp_deregister_icp_objects_operation = 
	    STATIC_SYMBOL("WRITE-ICP-DEREGISTER-ICP-OBJECTS-OPERATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_deregister_icp_objects_operation,
	    STATIC_FUNCTION(write_icp_deregister_icp_objects_operation,NIL,
	    FALSE,1,1));
    Qread_icp_deregister_icp_objects_operation = 
	    STATIC_SYMBOL("READ-ICP-DEREGISTER-ICP-OBJECTS-OPERATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_deregister_icp_objects_operation,
	    STATIC_FUNCTION(read_icp_deregister_icp_objects_operation,NIL,
	    FALSE,0,0));
    Qcorresponding_icp_object_index_list = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX-LIST",AB_package);
    Qwrite_icp_corresponding_icp_object_index_list = 
	    STATIC_SYMBOL("WRITE-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_corresponding_icp_object_index_list,
	    STATIC_FUNCTION(write_icp_corresponding_icp_object_index_list,
	    NIL,FALSE,1,1));
    Qread_icp_corresponding_icp_object_index_list = 
	    STATIC_SYMBOL("READ-ICP-CORRESPONDING-ICP-OBJECT-INDEX-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_corresponding_icp_object_index_list,
	    STATIC_FUNCTION(read_icp_corresponding_icp_object_index_list,
	    NIL,FALSE,0,0));
    Qreclaim_icp_list = STATIC_SYMBOL("RECLAIM-ICP-LIST",AB_package);
    Qicp_value_reclaimer = STATIC_SYMBOL("ICP-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qcorresponding_icp_object_index_list,
	    Qreclaim_icp_list,Qicp_value_reclaimer);
    Qsend_icp_deregister_icp_objects = 
	    STATIC_SYMBOL("SEND-ICP-DEREGISTER-ICP-OBJECTS",AB_package);
    Qderegister_icp_objects = STATIC_SYMBOL("DEREGISTER-ICP-OBJECTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_deregister_icp_objects,
	    STATIC_FUNCTION(send_icp_deregister_icp_objects,NIL,FALSE,3,3));
    Qhandle_icp_deregister_icp_objects = 
	    STATIC_SYMBOL("HANDLE-ICP-DEREGISTER-ICP-OBJECTS",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_deregister_icp_objects,
	    STATIC_FUNCTION(handle_icp_deregister_icp_objects,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_deregister_icp_objects,
	    FIX((SI_Long)326L));
    Qsend_icp_nop = STATIC_SYMBOL("SEND-ICP-NOP",AB_package);
    Qnop = STATIC_SYMBOL("NOP",AB_package);
    Qnumber_of_icp_bytes_of_fill = 
	    STATIC_SYMBOL("NUMBER-OF-ICP-BYTES-OF-FILL",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_nop,STATIC_FUNCTION(send_icp_nop,NIL,
	    FALSE,1,1));
    Qhandle_icp_nop = STATIC_SYMBOL("HANDLE-ICP-NOP",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_nop,STATIC_FUNCTION(handle_icp_nop,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_nop,FIX((SI_Long)16L));
    if (Gsi_application_name == UNBOUND)
	Gsi_application_name = Nil;
    Qtcp_listener_port_number = STATIC_SYMBOL("TCP-LISTENER-PORT-NUMBER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtcp_listener_port_number,
	    Tcp_listener_port_number);
    record_system_variable(Qtcp_listener_port_number,Qint3b,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    if (Name_for_local_home == UNBOUND)
	Name_for_local_home = Nil;
    Qmajor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MAJOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant = STATIC_CONS(Qfixnum,Qnil);
    list_constant_1 = 
	    STATIC_CONS(Qmajor_version_number_of_current_gensym_product_line,
	    list_constant);
    list_constant_11 = STATIC_CONS(FIX((SI_Long)1L),list_constant_1);
    Qminor_version_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("MINOR-VERSION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant_2 = 
	    STATIC_CONS(Qminor_version_number_of_current_gensym_product_line,
	    list_constant);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)2L),list_constant_2);
    Qlatest_icp_window_protocol_version = 
	    STATIC_SYMBOL("LATEST-ICP-WINDOW-PROTOCOL-VERSION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlatest_icp_window_protocol_version,
	    Latest_icp_window_protocol_version);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qab,Qtelewindows);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qfixnum,list_constant_3);
    list_constant_5 = STATIC_CONS(Qlatest_icp_window_protocol_version,
	    list_constant_4);
    list_constant_13 = STATIC_CONS(FIX((SI_Long)9L),list_constant_5);
    Qicp_protocol_version = STATIC_SYMBOL("ICP-PROTOCOL-VERSION",AB_package);
    list_constant_6 = STATIC_CONS(Qicp_protocol_version,list_constant);
    list_constant_14 = STATIC_CONS(FIX((SI_Long)10L),list_constant_6);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)11L),list_constant_1);
    list_constant_16 = STATIC_CONS(FIX((SI_Long)12L),list_constant_2);
    Qrevision_number_of_current_gensym_product_line = 
	    STATIC_SYMBOL("REVISION-NUMBER-OF-CURRENT-GENSYM-PRODUCT-LINE",
	    AB_package);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)13L),
	    Qrevision_number_of_current_gensym_product_line,list_constant);
    Qbuild_identification_string = 
	    STATIC_SYMBOL("BUILD-IDENTIFICATION-STRING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbuild_identification_string,
	    Build_identification_string);
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)14L),
	    Qbuild_identification_string,Qgensym_string);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)15L),list_constant_6);
    list_constant_20 = STATIC_CONS(FIX((SI_Long)16L),list_constant_5);
    Qgsi_references_in_use = STATIC_SYMBOL("GSI-REFERENCES-IN-USE",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    list_constant_7 = STATIC_CONS(Qgsi,Qnil);
    list_constant_21 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)17L),
	    Qgsi_references_in_use,Qfixnum,list_constant_7);
    Qg2_time_at_start_as_text_string = 
	    STATIC_SYMBOL("G2-TIME-AT-START-AS-TEXT-STRING",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_8 = STATIC_CONS(Qwide_string,Qnil);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)18L),
	    Qg2_time_at_start_as_text_string,list_constant_8);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)19L),
	    Qtcp_listener_port_number,list_constant);
    Qlocal_host_name = STATIC_SYMBOL("LOCAL-HOST-NAME",AB_package);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)20L),
	    Qlocal_host_name,list_constant_8);
    Qgsi_application_name = STATIC_SYMBOL("GSI-APPLICATION-NAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgsi_application_name,Gsi_application_name);
    list_constant_9 = STATIC_CONS(Qab,list_constant_7);
    list_constant_25 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)21L),
	    Qgsi_application_name,Qsymbol,list_constant_9);
    Qdisable_resumability = STATIC_SYMBOL("DISABLE-RESUMABILITY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdisable_resumability,Disable_resumability);
    list_constant_10 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)22L),
	    Qdisable_resumability,list_constant_10);
    Qname_for_local_home = STATIC_SYMBOL("NAME-FOR-LOCAL-HOME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qname_for_local_home,Name_for_local_home);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)23L),
	    Qname_for_local_home,list_constant_10);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)24L),
	    Qname_for_local_home,list_constant_8);
    Qsupports_transparent_color_index = 
	    STATIC_SYMBOL("SUPPORTS-TRANSPARENT-COLOR-INDEX",AB_package);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)25L),
	    Qsupports_transparent_color_index,list_constant_4);
    Qg2_operating_system = STATIC_SYMBOL("G2-OPERATING-SYSTEM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_operating_system,G2_operating_system);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)26L),
	    Qg2_operating_system,list_constant_10);
    Qg2_machine_type = STATIC_SYMBOL("G2-MACHINE-TYPE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_machine_type,G2_machine_type);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)27L),
	    Qg2_machine_type,list_constant_10);
    Qsupports_dialog_component_with_font = 
	    STATIC_SYMBOL("SUPPORTS-DIALOG-COMPONENT-WITH-FONT",AB_package);
    list_constant_32 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)28L),
	    Qsupports_dialog_component_with_font,list_constant_4);
    Qsupports_font_in_grid_view = 
	    STATIC_SYMBOL("SUPPORTS-FONT-IN-GRID-VIEW",AB_package);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)29L),
	    Qsupports_font_in_grid_view,list_constant_4);
    list_constant_34 = STATIC_LIST((SI_Long)23L,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17,
	    list_constant_18,list_constant_19,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24,list_constant_25,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_33);
    Icp_version_info_alist = list_constant_34;
    SET_SYMBOL_VALUE_LOCATION(Qicp_protocol_version,Icp_protocol_version);
    if (Icp_protocol_version == UNBOUND)
	Icp_protocol_version = Newest_icp_version;
    Qacknowledge_version_info_receipt = 
	    STATIC_SYMBOL("ACKNOWLEDGE-VERSION-INFO-RECEIPT",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)63L),
	    Qacknowledge_version_info_receipt,Qnull);
    list_constant_36 = STATIC_CONS(list_constant_35,Qnil);
    Icp_acknowledge_version_info_alist = list_constant_36;
    Qg2_time_at_start = STATIC_SYMBOL("G2-TIME-AT-START",AB_package);
    Qcached_local_icp_version_info = 
	    STATIC_SYMBOL("CACHED-LOCAL-ICP-VERSION-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_local_icp_version_info,
	    Cached_local_icp_version_info);
    record_system_variable(Qcached_local_icp_version_info,Qint3b,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    if (Initial_icp_version_info_enabled_p == UNBOUND)
	Initial_icp_version_info_enabled_p = T;
    if (Write_initial_icp_version_info_p == UNBOUND)
	Write_initial_icp_version_info_p = Nil;
    Qinitial = STATIC_SYMBOL("INITIAL",AB_package);
    Qconnect_side_info_sent_but_not_yet_acknowledged = 
	    STATIC_SYMBOL("CONNECT-SIDE-INFO-SENT-BUT-NOT-YET-ACKNOWLEDGED",
	    AB_package);
    Qacknowledge = STATIC_SYMBOL("ACKNOWLEDGE",AB_package);
    Qlisten_side_info_sent_but_no_acknowledge_yet = 
	    STATIC_SYMBOL("LISTEN-SIDE-INFO-SENT-BUT-NO-ACKNOWLEDGE-YET",
	    AB_package);
    Qsend = STATIC_SYMBOL("SEND",AB_package);
    Qreceive = STATIC_SYMBOL("RECEIVE",AB_package);
    Qno_icp_version_info = STATIC_SYMBOL("NO-ICP-VERSION-INFO",AB_package);
    string_constant_5 = STATIC_STRING("\?");
    string_constant_6 = 
	    STATIC_STRING("ICP connection: ~A, local: ~A, remote: ~A, version: ~A ~A ~A ~A ~A");
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_37,(SI_Long)1L,
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
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qread_icp_number_of_icp_bytes_of_fill = 
	    STATIC_SYMBOL("READ-ICP-NUMBER-OF-ICP-BYTES-OF-FILL",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_number_of_icp_bytes_of_fill,
	    STATIC_FUNCTION(read_icp_number_of_icp_bytes_of_fill,NIL,FALSE,
	    0,0));
    Qwrite_icp_number_of_icp_bytes_of_fill = 
	    STATIC_SYMBOL("WRITE-ICP-NUMBER-OF-ICP-BYTES-OF-FILL",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_number_of_icp_bytes_of_fill,
	    STATIC_FUNCTION(write_icp_number_of_icp_bytes_of_fill,NIL,
	    FALSE,1,1));
    Qunsigned_integer_or_nil = STATIC_SYMBOL("UNSIGNED-INTEGER-OR-NIL",
	    AB_package);
    Qwrite_icp_unsigned_integer_or_nil = 
	    STATIC_SYMBOL("WRITE-ICP-UNSIGNED-INTEGER-OR-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_unsigned_integer_or_nil,
	    STATIC_FUNCTION(write_icp_unsigned_integer_or_nil,NIL,FALSE,1,1));
    Qread_icp_unsigned_integer_or_nil = 
	    STATIC_SYMBOL("READ-ICP-UNSIGNED-INTEGER-OR-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_unsigned_integer_or_nil,
	    STATIC_FUNCTION(read_icp_unsigned_integer_or_nil,NIL,FALSE,0,0));
    Qwrite_icp_float = STATIC_SYMBOL("WRITE-ICP-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_float,STATIC_FUNCTION(write_icp_float,
	    NIL,FALSE,1,1));
    float_constant = STATIC_FLOAT(0.0);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qread_icp_float = STATIC_SYMBOL("READ-ICP-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_float,STATIC_FUNCTION(read_icp_float,NIL,
	    FALSE,0,0));
    Qwrite_icp_double_float_using_function = 
	    STATIC_SYMBOL("WRITE-ICP-DOUBLE-FLOAT-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_double_float_using_function,
	    STATIC_FUNCTION(write_icp_double_float_using_function,NIL,
	    FALSE,1,1));
    Qread_icp_double_float_using_function = 
	    STATIC_SYMBOL("READ-ICP-DOUBLE-FLOAT-USING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_double_float_using_function,
	    STATIC_FUNCTION(read_icp_double_float_using_function,NIL,FALSE,
	    0,0));
    Qread_icp_managed_double_float = 
	    STATIC_SYMBOL("READ-ICP-MANAGED-DOUBLE-FLOAT",AB_package);
    Qmanaged_double_float = STATIC_SYMBOL("MANAGED-DOUBLE-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_managed_double_float,
	    STATIC_FUNCTION(read_icp_managed_double_float,NIL,FALSE,0,0));
    Qwrite_icp_managed_double_float = 
	    STATIC_SYMBOL("WRITE-ICP-MANAGED-DOUBLE-FLOAT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_managed_double_float,
	    STATIC_FUNCTION(write_icp_managed_double_float,NIL,FALSE,1,1));
    Qsend_icp_define_dummy_object = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-DUMMY-OBJECT",AB_package);
    Qdefine_dummy_object = STATIC_SYMBOL("DEFINE-DUMMY-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_dummy_object,
	    STATIC_FUNCTION(send_icp_define_dummy_object,NIL,FALSE,1,1));
    Qhandle_icp_define_dummy_object = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-DUMMY-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_define_dummy_object,
	    STATIC_FUNCTION(handle_icp_define_dummy_object,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_define_dummy_object,FIX((SI_Long)18L));
    Qsend_icp_end_message_block = 
	    STATIC_SYMBOL("SEND-ICP-END-MESSAGE-BLOCK",AB_package);
    Qend_message_block = STATIC_SYMBOL("END-MESSAGE-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_message_block,
	    STATIC_FUNCTION(send_icp_end_message_block,NIL,FALSE,0,0));
    Qhandle_icp_end_message_block = 
	    STATIC_SYMBOL("HANDLE-ICP-END-MESSAGE-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_end_message_block,
	    STATIC_FUNCTION(handle_icp_end_message_block,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_end_message_block,FIX((SI_Long)17L));
    Sexp_null_type_tag = FIX((SI_Long)0L);
    Sexp_element_integer_type_tag = FIX((SI_Long)1L);
    Sexp_element_float_type_tag = FIX((SI_Long)2L);
    Sexp_element_symbol_type_tag = FIX((SI_Long)3L);
    Sexp_element_text_type_tag = FIX((SI_Long)4L);
    Sexp_element_list_type_tag = FIX((SI_Long)5L);
    Sexp_element_character_type_tag = FIX((SI_Long)6L);
    Qsexp_element = STATIC_SYMBOL("SEXP-ELEMENT",AB_package);
    Qwrite_icp_sexp_element = STATIC_SYMBOL("WRITE-ICP-SEXP-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_sexp_element,
	    STATIC_FUNCTION(write_icp_sexp_element,NIL,FALSE,1,1));
    Qread_icp_sexp_element = STATIC_SYMBOL("READ-ICP-SEXP-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_sexp_element,
	    STATIC_FUNCTION(read_icp_sexp_element,NIL,FALSE,0,0));
    Qs_expression_for_remote_eval = 
	    STATIC_SYMBOL("S-EXPRESSION-FOR-REMOTE-EVAL",AB_package);
    Qwrite_icp_s_expression_for_remote_eval = 
	    STATIC_SYMBOL("WRITE-ICP-S-EXPRESSION-FOR-REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_s_expression_for_remote_eval,
	    STATIC_FUNCTION(write_icp_s_expression_for_remote_eval,NIL,
	    FALSE,1,1));
    Qread_icp_s_expression_for_remote_eval = 
	    STATIC_SYMBOL("READ-ICP-S-EXPRESSION-FOR-REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_s_expression_for_remote_eval,
	    STATIC_FUNCTION(read_icp_s_expression_for_remote_eval,NIL,
	    FALSE,0,0));
    Qsend_icp_remote_eval = STATIC_SYMBOL("SEND-ICP-REMOTE-EVAL",AB_package);
    Qremote_eval = STATIC_SYMBOL("REMOTE-EVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_remote_eval,
	    STATIC_FUNCTION(send_icp_remote_eval,NIL,FALSE,1,1));
    Qhandle_icp_remote_eval = STATIC_SYMBOL("HANDLE-ICP-REMOTE-EVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_remote_eval,
	    STATIC_FUNCTION(handle_icp_remote_eval,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_remote_eval,FIX((SI_Long)300L));
    if (Deadman_switch_time_interval == UNBOUND)
	Deadman_switch_time_interval = FIX((SI_Long)200L * 
		IFIX(Fixnum_time_units_per_second));
    Qsending_i_am_alive_qm = STATIC_SYMBOL("SENDING-I-AM-ALIVE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsending_i_am_alive_qm,Sending_i_am_alive_qm);
    record_system_variable(Qsending_i_am_alive_qm,Qint3b,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qhandling_solitary_i_am_alive_qm = 
	    STATIC_SYMBOL("HANDLING-SOLITARY-I-AM-ALIVE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhandling_solitary_i_am_alive_qm,
	    Handling_solitary_i_am_alive_qm);
    record_system_variable(Qhandling_solitary_i_am_alive_qm,Qint3b,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    if (I_am_alive_send_time_interval_in_seconds == UNBOUND)
	I_am_alive_send_time_interval_in_seconds = FIX((SI_Long)30L);
    float_constant_1 = STATIC_FLOAT(30.0);
    if (I_am_alive_send_time_interval_in_seconds_as_float == UNBOUND)
	I_am_alive_send_time_interval_in_seconds_as_float = float_constant_1;
    if (I_am_alive_send_time_interval == UNBOUND)
	I_am_alive_send_time_interval = 
		FIXNUM_TIMES(I_am_alive_send_time_interval_in_seconds,
		Fixnum_time_units_per_second);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsend_i_am_alive_message = STATIC_SYMBOL("SEND-I-AM-ALIVE-MESSAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_i_am_alive_message,
	    STATIC_FUNCTION(send_i_am_alive_message,NIL,FALSE,2,2));
    Qsend_icp_i_am_alive = STATIC_SYMBOL("SEND-ICP-I-AM-ALIVE",AB_package);
    Qi_am_alive = STATIC_SYMBOL("I-AM-ALIVE",AB_package);
    Qmessage_group_id = STATIC_SYMBOL("MESSAGE-GROUP-ID",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_i_am_alive,
	    STATIC_FUNCTION(send_icp_i_am_alive,NIL,FALSE,1,1));
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qhandle_icp_i_am_alive = STATIC_SYMBOL("HANDLE-ICP-I-AM-ALIVE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_i_am_alive,
	    STATIC_FUNCTION(handle_icp_i_am_alive,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_i_am_alive,FIX((SI_Long)14L));
    Qsend_icp_message_group_id = STATIC_SYMBOL("SEND-ICP-MESSAGE-GROUP-ID",
	    AB_package);
    Qnumber_of_icp_bytes = STATIC_SYMBOL("NUMBER-OF-ICP-BYTES",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_message_group_id,
	    STATIC_FUNCTION(send_icp_message_group_id,NIL,FALSE,2,2));
    Qhandle_icp_message_group_id = 
	    STATIC_SYMBOL("HANDLE-ICP-MESSAGE-GROUP-ID",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_message_group_id,
	    STATIC_FUNCTION(handle_icp_message_group_id,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_message_group_id,FIX((SI_Long)181L));
    string_constant_7 = STATIC_STRING("~5T Protocol out-of-synch (case 2)");
    Icp_message_out_of_synch_case_2_warning = string_constant_7;
    SET_SYMBOL_VALUE_LOCATION(Qlocal_host_name,Local_host_name);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qget_unix_host_name = STATIC_SYMBOL("GET-UNIX-HOST-NAME",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Kfuncall,Qget_unix_host_name);
    record_system_variable(Qlocal_host_name,Qint3b,list_constant_38,Qnil,
	    Qnil,Qnil,Qnil);
    Qunix_tcp_listener_port = STATIC_SYMBOL("UNIX-TCP-LISTENER-PORT",
	    AB_package);
    Qsend_icp_connection_denied = 
	    STATIC_SYMBOL("SEND-ICP-CONNECTION-DENIED",AB_package);
    Qconnection_denied = STATIC_SYMBOL("CONNECTION-DENIED",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_connection_denied,
	    STATIC_FUNCTION(send_icp_connection_denied,NIL,FALSE,0,0));
    string_constant_8 = 
	    STATIC_STRING("ICP connection \"~a\" is closed to remote users.~%");
    Qhandle_icp_connection_denied = 
	    STATIC_SYMBOL("HANDLE-ICP-CONNECTION-DENIED",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_connection_denied,
	    STATIC_FUNCTION(handle_icp_connection_denied,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_connection_denied,FIX((SI_Long)305L));
    Qsend_icp_no_license = STATIC_SYMBOL("SEND-ICP-NO-LICENSE",AB_package);
    Qno_license = STATIC_SYMBOL("NO-LICENSE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_no_license,
	    STATIC_FUNCTION(send_icp_no_license,NIL,FALSE,0,0));
    string_constant_9 = 
	    STATIC_STRING("No license is available for a connection over \"~a\".~%");
    Qhandle_icp_no_license = STATIC_SYMBOL("HANDLE-ICP-NO-LICENSE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_no_license,
	    STATIC_FUNCTION(handle_icp_no_license,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_no_license,FIX((SI_Long)307L));
    Qsend_icp_connection_shutdown_imminent = 
	    STATIC_SYMBOL("SEND-ICP-CONNECTION-SHUTDOWN-IMMINENT",AB_package);
    Qconnection_shutdown_imminent = 
	    STATIC_SYMBOL("CONNECTION-SHUTDOWN-IMMINENT",AB_package);
    Qtime_until_shutdown = STATIC_SYMBOL("TIME-UNTIL-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_connection_shutdown_imminent,
	    STATIC_FUNCTION(send_icp_connection_shutdown_imminent,NIL,
	    FALSE,1,1));
    string_constant_10 = 
	    STATIC_STRING("ICP connection \"~a\" will be shut down within ~a seconds.~%~\n     That process has disallowed remote connections.~%");
    Qhandle_icp_connection_shutdown_imminent = 
	    STATIC_SYMBOL("HANDLE-ICP-CONNECTION-SHUTDOWN-IMMINENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_connection_shutdown_imminent,
	    STATIC_FUNCTION(handle_icp_connection_shutdown_imminent,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_connection_shutdown_imminent,
	    FIX((SI_Long)306L));
}
