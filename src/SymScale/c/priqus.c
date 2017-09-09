/* priqus.c
 * Input file:  priority-queues.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "priqus.h"


Object Priority_queue_initial_size = UNBOUND;

/* MAKE-PRIORITY-QUEUE-INITIAL-OBJECT-ARRAY */
Object make_priority_queue_initial_object_array()
{
    Object temp;

    x_note_fn_call(146,0);
    temp = allocate_managed_array(1,Priority_queue_initial_size);
    return VALUES_1(temp);
}

/* MAKE-PRIORITY-QUEUE-INITIAL-PRIORITY-ARRAY */
Object make_priority_queue_initial_priority_array()
{
    Object temp;

    x_note_fn_call(146,1);
    temp = allocate_managed_array(1,Priority_queue_initial_size);
    return VALUES_1(temp);
}

/* MAKE-PRIORITY-QUEUE-INITIAL-OBJECT-TABLE */
Object make_priority_queue_initial_object_table()
{
    Object temp;

    x_note_fn_call(146,2);
    temp = make_eq_hash_table(FIX((SI_Long)101L),Nil,Nil);
    return VALUES_1(temp);
}

static Object Qnot_found;          /* not-found */

/* PRIORITY-QUEUE-ADD */
Object priority_queue_add(queue,object,priority)
    Object queue, object, priority;
{
    Object objects, priorities, table, current_index, array_length, x, y, temp;
    Object svref_new_value;
    SI_Long parent_index, svref_arg_2;
    double arg, arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(146,3);
    objects = ISVREF(queue,(SI_Long)20L);
    priorities = ISVREF(queue,(SI_Long)21L);
    table = ISVREF(queue,(SI_Long)22L);
    current_index = ISVREF(queue,(SI_Long)23L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
      array_length = ISVREF(objects,(SI_Long)1L);
      if ( !EQ(eq_gethash(table,object,Qnot_found),Qnot_found)) {
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_priority_queue_add;
      }
      if (FIXNUM_GE(Current_index,array_length)) {
	  array_length = FIX(IFIX(array_length) << (SI_Long)1L);
	  objects = adjust_managed_array(2,objects,array_length);
	  ISVREF(queue,(SI_Long)20L) = objects;
	  priorities = adjust_managed_array(2,priorities,array_length);
	  ISVREF(queue,(SI_Long)21L) = priorities;
	  table = priority_queue_rehash(queue);
      }
    next_loop:
      if (IFIX(Current_index) == (SI_Long)0L)
	  goto end_1;
      parent_index = IFIX(FIXNUM_SUB1(Current_index)) >>  -  - (SI_Long)1L;
      x = priority;
      y = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(priorities,
	      parent_index + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(priorities,(parent_index >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),parent_index & (SI_Long)1023L);
      arg = DFLOAT_ISAREF_1(x,(SI_Long)0L);
      arg_1 = DFLOAT_ISAREF_1(y,(SI_Long)0L);
      if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	      !inline_nanp_for_comparison(arg_1))
	  goto end_1;
      if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),Maximum_in_place_array_size)) {
	  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	  svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(objects,
		  parent_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(objects,(parent_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),parent_index & (SI_Long)1023L);
	  SVREF(objects,temp) = svref_new_value;
      }
      else {
	  temp = ISVREF(objects,(IFIX(Current_index) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	  svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(objects,
		  parent_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(objects,(parent_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),parent_index & (SI_Long)1023L);
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
      if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	  svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(priorities,
		  parent_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(priorities,(parent_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),parent_index & (SI_Long)1023L);
	  SVREF(priorities,temp) = svref_new_value;
      }
      else {
	  temp = ISVREF(priorities,(IFIX(Current_index) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	  svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(priorities,
		  parent_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(priorities,(parent_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),parent_index & (SI_Long)1023L);
	  ISVREF(temp,svref_arg_2) = svref_new_value;
      }
      eq_puthash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(objects,parent_index + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(objects,
	      (parent_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
	      parent_index & (SI_Long)1023L),Current_index);
      Current_index = FIX(parent_index);
      goto next_loop;
    end_loop:
    end_1:
      if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),Maximum_in_place_array_size)) {
	  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	  SVREF(objects,temp) = object;
      }
      else {
	  temp = ISVREF(objects,(IFIX(Current_index) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	  ISVREF(temp,svref_arg_2) = object;
      }
      if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	  SVREF(priorities,temp) = priority;
      }
      else {
	  temp = ISVREF(priorities,(IFIX(Current_index) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	  ISVREF(temp,svref_arg_2) = priority;
      }
      eq_puthash(table,object,Current_index);
      temp = add1(ISVREF(queue,(SI_Long)23L));
      ISVREF(queue,(SI_Long)23L) = temp;
    POP_SPECIAL();
    result = VALUES_1(T);
  end_priority_queue_add:
    return result;
}

/* PRIORITY-QUEUE-REMOVE */
Object priority_queue_remove(queue,object)
    Object queue, object;
{
    Object index_1;

    x_note_fn_call(146,4);
    index_1 = eq_gethash(ISVREF(queue,(SI_Long)22L),object,Qnot_found);
    if ( !EQ(index_1,Qnot_found))
	return priority_queue_remove_by_index(queue,index_1);
    else
	return VALUES_1(Nil);
}

/* PRIORITY-QUEUE-REMOVE-BY-INDEX */
Object priority_queue_remove_by_index(queue,current_index)
    Object queue, current_index;
{
    Object objects, priorities, table, new_queue_size, priority;
    Object moving_object_priority, x, y, temp, svref_new_value, left_priority;
    Object right_priority;
    SI_Long left, right, svref_arg_2, new_index;
    char temp_1;
    double arg, arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(146,5);
    PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
      objects = ISVREF(queue,(SI_Long)20L);
      priorities = ISVREF(queue,(SI_Long)21L);
      table = ISVREF(queue,(SI_Long)22L);
      new_queue_size = FIXNUM_SUB1(ISVREF(queue,(SI_Long)23L));
      priority = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(priorities,
	      IFIX(FIXNUM_ADD(Current_index,Managed_array_index_offset))) :
	       ISVREF(ISVREF(priorities,(IFIX(Current_index) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(Current_index) & 
	      (SI_Long)1023L);
      moving_object_priority = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(priorities,
	      IFIX(FIXNUM_ADD(new_queue_size,Managed_array_index_offset))) 
	      : ISVREF(ISVREF(priorities,(IFIX(new_queue_size) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(new_queue_size) & 
	      (SI_Long)1023L);
      eq_remhash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(objects,
	      IFIX(FIXNUM_ADD(Current_index,Managed_array_index_offset))) :
	       ISVREF(ISVREF(objects,(IFIX(Current_index) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(Current_index) & 
	      (SI_Long)1023L));
    next_loop:
      left = (IFIX(Current_index) << (SI_Long)1L) + (SI_Long)1L;
      right = left + (SI_Long)1L;
      if (left >= IFIX(new_queue_size))
	  goto end_1;
      if (right >= IFIX(new_queue_size)) {
	  x = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(priorities,left + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(priorities,(left >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),left & (SI_Long)1023L);
	  y = moving_object_priority;
	  arg = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	  arg_1 = DFLOAT_ISAREF_1(y,(SI_Long)0L);
	  if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1)) {
	      if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
		  svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
			  Maximum_in_place_array_size) ? ISVREF(objects,
			  left + IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(objects,(left >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
		  SVREF(objects,temp) = svref_new_value;
	      }
	      else {
		  temp = ISVREF(objects,(IFIX(Current_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
		  svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
			  Maximum_in_place_array_size) ? ISVREF(objects,
			  left + IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(objects,(left >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
		  ISVREF(temp,svref_arg_2) = svref_new_value;
	      }
	      if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
		  svref_new_value = FIXNUM_LE(ISVREF(priorities,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(priorities,left + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(priorities,(left >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
		  SVREF(priorities,temp) = svref_new_value;
	      }
	      else {
		  temp = ISVREF(priorities,(IFIX(Current_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L);
		  svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
		  svref_new_value = FIXNUM_LE(ISVREF(priorities,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(priorities,left + 
			  IFIX(Managed_array_index_offset)) : 
			  ISVREF(ISVREF(priorities,(left >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
		  ISVREF(temp,svref_arg_2) = svref_new_value;
	      }
	      eq_puthash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(objects,left + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(objects,(left >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),left & (SI_Long)1023L),Current_index);
	      Current_index = FIX(left);
	  }
	  goto end_1;
      }
      else {
	  left_priority = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(priorities,left + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(priorities,(left >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),left & (SI_Long)1023L);
	  right_priority = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(priorities,right + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(priorities,(right >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),right & (SI_Long)1023L);
	  arg = DFLOAT_ISAREF_1(left_priority,(SI_Long)0L);
	  arg_1 = DFLOAT_ISAREF_1(moving_object_priority,(SI_Long)0L);
	  if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1)) {
	      arg = DFLOAT_ISAREF_1(right_priority,(SI_Long)0L);
	      arg_1 = DFLOAT_ISAREF_1(moving_object_priority,(SI_Long)0L);
	      temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_1;
	  arg = DFLOAT_ISAREF_1(left_priority,(SI_Long)0L);
	  arg_1 = DFLOAT_ISAREF_1(right_priority,(SI_Long)0L);
	  new_index = arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1) ? left : right;
	  if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	      svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(objects,
		      new_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(objects,(new_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),new_index & (SI_Long)1023L);
	      SVREF(objects,temp) = svref_new_value;
	  }
	  else {
	      temp = ISVREF(objects,(IFIX(Current_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	      svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(objects,
		      new_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(objects,(new_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),new_index & (SI_Long)1023L);
	      ISVREF(temp,svref_arg_2) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	      svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(priorities,
		      new_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(priorities,(new_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),new_index & (SI_Long)1023L);
	      SVREF(priorities,temp) = svref_new_value;
	  }
	  else {
	      temp = ISVREF(priorities,(IFIX(Current_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	      svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(priorities,
		      new_index + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(priorities,(new_index >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),new_index & (SI_Long)1023L);
	      ISVREF(temp,svref_arg_2) = svref_new_value;
	  }
	  eq_puthash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(objects,new_index 
		  + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(objects,(new_index >>  -  - (SI_Long)10L) 
		  + (SI_Long)2L),new_index & (SI_Long)1023L),Current_index);
	  Current_index = FIX(new_index);
      }
      goto next_loop;
    end_loop:
    end_1:
      if ( !FIXNUM_EQ(new_queue_size,Current_index)) {
	  if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	      svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(objects,
		      IFIX(FIXNUM_ADD(new_queue_size,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(objects,(IFIX(new_queue_size) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),IFIX(new_queue_size) & 
		      (SI_Long)1023L);
	      SVREF(objects,temp) = svref_new_value;
	  }
	  else {
	      temp = ISVREF(objects,(IFIX(Current_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	      svref_new_value = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(objects,
		      IFIX(FIXNUM_ADD(new_queue_size,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(objects,(IFIX(new_queue_size) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),IFIX(new_queue_size) & 
		      (SI_Long)1023L);
	      ISVREF(temp,svref_arg_2) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      temp = FIXNUM_ADD(Current_index,Managed_array_index_offset);
	      svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(priorities,
		      IFIX(FIXNUM_ADD(new_queue_size,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(priorities,(IFIX(new_queue_size) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),IFIX(new_queue_size) 
		      & (SI_Long)1023L);
	      SVREF(priorities,temp) = svref_new_value;
	  }
	  else {
	      temp = ISVREF(priorities,(IFIX(Current_index) >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = IFIX(Current_index) & (SI_Long)1023L;
	      svref_new_value = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(priorities,
		      IFIX(FIXNUM_ADD(new_queue_size,
		      Managed_array_index_offset))) : 
		      ISVREF(ISVREF(priorities,(IFIX(new_queue_size) >>  - 
		       - (SI_Long)10L) + (SI_Long)2L),IFIX(new_queue_size) 
		      & (SI_Long)1023L);
	      ISVREF(temp,svref_arg_2) = svref_new_value;
	  }
	  eq_puthash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(objects,
		  IFIX(FIXNUM_ADD(new_queue_size,
		  Managed_array_index_offset))) : ISVREF(ISVREF(objects,
		  (IFIX(new_queue_size) >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),IFIX(new_queue_size) & (SI_Long)1023L),
		  Current_index);
      }
      ISVREF(queue,(SI_Long)23L) = new_queue_size;
      result = VALUES_1(priority);
    POP_SPECIAL();
    return result;
}

/* PRIORITY-QUEUE-CHANGE-PRIORITY */
Object priority_queue_change_priority(queue,object,new_priority)
    Object queue, object, new_priority;
{
    Object old_priority;

    x_note_fn_call(146,6);
    old_priority = priority_queue_remove(queue,object);
    if (old_priority) {
	priority_queue_add(queue,object,new_priority);
	return VALUES_1(old_priority);
    }
    else
	return VALUES_1(Nil);
}

/* GET-HIGHEST-PRIORITY */
Object get_highest_priority(queue)
    Object queue;
{
    Object result_ref, result_1, objects, priorities, size, managed_float;
    Object temp, temp_1, temp_2;

    x_note_fn_call(146,7);
    result_ref = Nil;
    result_1 = Nil;
    objects = ISVREF(queue,(SI_Long)20L);
    priorities = ISVREF(queue,(SI_Long)21L);
    size = ISVREF(queue,(SI_Long)23L);
  next_loop:
    if (zerop(size)) {
	result_1 = Nil;
	goto end_1;
    }
    result_ref = FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(objects,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(objects,
	    (SI_Long)2L),(SI_Long)0L);
    result_1 = ISVREF(M_CAR(result_ref),(SI_Long)3L);
    if (result_1)
	goto end_1;
    size = sub1(size);
    managed_float = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(priorities,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(priorities,
	    (SI_Long)2L),(SI_Long)0L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    priority_queue_remove_by_index(queue,FIX((SI_Long)0L));
    reclaim_evaluation_item_reference(result_ref);
    goto next_loop;
  end_loop:
  end_1:
    if (result_1) {
	temp = result_1;
	temp_1 = result_ref;
	temp_2 = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(priorities,
		(SI_Long)0L + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(priorities,(SI_Long)2L),(SI_Long)0L);
	return VALUES_3(temp,temp_1,temp_2);
    }
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* GET-AND-REMOVE-HIGHEST-PRIORITY */
Object get_and_remove_highest_priority(queue)
    Object queue;
{
    Object object, object_ref, priority;
    Object result;

    x_note_fn_call(146,8);
    result = get_highest_priority(queue);
    MVS_3(result,object,object_ref,priority);
    if (priority) {
	priority_queue_remove(queue,object_ref);
	reclaim_evaluation_item_reference(object_ref);
    }
    return VALUES_2(object,priority);
}

/* CLEAR-PRIORITY-QUEUE */
Object clear_priority_queue(queue)
    Object queue;
{
    Object objects, priorities, table, size, array_length, temp, managed_float;
    SI_Long index_1, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(146,9);
    objects = ISVREF(queue,(SI_Long)20L);
    priorities = ISVREF(queue,(SI_Long)21L);
    table = ISVREF(queue,(SI_Long)22L);
    size = ISVREF(queue,(SI_Long)23L);
    array_length = ISVREF(objects,(SI_Long)1L);
    reclaim_eq_hash_table(table);
    temp = make_eq_hash_table(FIXNUM_ADD1(array_length),Nil,Nil);
    ISVREF(queue,(SI_Long)22L) = temp;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    managed_float = FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(priorities,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(priorities,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    if (FIXNUM_LE(ISVREF(priorities,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(priorities,svref_arg_2) = Nil;
    }
    else {
	temp = ISVREF(priorities,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = Nil;
    }
    reclaim_evaluation_item_reference(FIXNUM_LE(ISVREF(objects,
	    (SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(objects,
	    index_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(objects,(index_1 >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),index_1 & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(objects,(SI_Long)1L),Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(objects,svref_arg_2) = Nil;
    }
    else {
	temp = ISVREF(objects,(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = Nil;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(ISVREF(queue,(SI_Long)23L) = FIX((SI_Long)0L));
}

/* DEACTIVATE-FOR-PRIORITY-QUEUE */
Object deactivate_for_priority_queue(priority_queue)
    Object priority_queue;
{
    x_note_fn_call(146,10);
    return clear_priority_queue(priority_queue);
}

/* RECLAIM-PRIORITY-QUEUE-OBJECT-TABLE-VALUE */
Object reclaim_priority_queue_object_table_value(value,frame)
    Object value, frame;
{
    x_note_fn_call(146,11);
    reclaim_eq_hash_table(value);
    ISVREF(frame,(SI_Long)22L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PRIORITY-QUEUE-OBJECT-ARRAY-VALUE */
Object reclaim_priority_queue_object_array_value(value,frame)
    Object value, frame;
{
    Object svref_arg_1;
    SI_Long index_1, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(146,12);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(frame,(SI_Long)23L));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    reclaim_evaluation_item_reference(FIXNUM_LE(ISVREF(value,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(value,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(value,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(value,(SI_Long)1L),Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(value,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(value,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_managed_array(value);
    ISVREF(frame,(SI_Long)20L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-PRIORITY-QUEUE-PRIORITY-ARRAY-VALUE */
Object reclaim_priority_queue_priority_array_value(value,frame)
    Object value, frame;
{
    Object managed_float;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(146,13);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(frame,(SI_Long)23L));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    managed_float = FIXNUM_LE(ISVREF(value,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(value,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(value,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_managed_array(value);
    return VALUES_1(Nil);
}

/* G2-PRIORITY-QUEUE-PUSH */
Object g2_priority_queue_push(queue,object,priority)
    Object queue, object, priority;
{
    Object object_ref, result_1;

    x_note_fn_call(146,14);
    object_ref = get_reference_to_item(object);
    result_1 = priority_queue_add(queue,object_ref,priority);
    if ( !TRUEP(result_1)) {
	reclaim_managed_simple_float_array_of_length_1(priority);
	reclaim_evaluation_item_reference(object_ref);
    }
    if (result_1)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-PRIORITY-QUEUE-CHANGE-PRIORITY */
Object g2_priority_queue_change_priority(queue,object,new_priority)
    Object queue, object, new_priority;
{
    Object object_ref, old_priority_qm;
    char found_in_queue;

    x_note_fn_call(146,15);
    object_ref = get_reference_to_item(object);
    old_priority_qm = priority_queue_change_priority(queue,object_ref,
	    new_priority);
    reclaim_evaluation_item_reference(object_ref);
    found_in_queue =  ! !TRUEP(old_priority_qm);
    if (found_in_queue)
	reclaim_managed_simple_float_array_of_length_1(old_priority_qm);
    else
	reclaim_managed_simple_float_array_of_length_1(new_priority);
    if (found_in_queue)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-PRIORITY-QUEUE-REMOVE-ELEMENT */
Object g2_priority_queue_remove_element(queue,object)
    Object queue, object;
{
    Object object_ref, old_priority, result_1;

    x_note_fn_call(146,16);
    object_ref = get_reference_to_item(object);
    old_priority = priority_queue_remove(queue,object_ref);
    result_1 = old_priority ? Evaluation_true_value : Evaluation_false_value;
    reclaim_evaluation_item_reference(object_ref);
    if (old_priority) {
	reclaim_managed_simple_float_array_of_length_1(old_priority);
	reclaim_evaluation_item_reference(object_ref);
    }
    return VALUES_1(result_1);
}

/* G2-PRIORITY-QUEUE-TOP */
Object g2_priority_queue_top(queue)
    Object queue;
{
    Object result_1, temp, priority;
    Object result;

    x_note_fn_call(146,17);
    result = get_highest_priority(queue);
    MVS_3(result,result_1,temp,priority);
    if (result_1) {
	temp = copy_managed_float(priority);
	return VALUES_2(result_1,temp);
    }
    else
	return VALUES_2(Nil ? Evaluation_true_value : 
		Evaluation_false_value,Nil ? Evaluation_true_value : 
		Evaluation_false_value);
}

/* G2-PRIORITY-QUEUE-POP */
Object g2_priority_queue_pop(queue)
    Object queue;
{
    Object object, priority;
    Object result;

    x_note_fn_call(146,18);
    result = get_and_remove_highest_priority(queue);
    MVS_2(result,object,priority);
    if (object)
	return VALUES_2(object,priority);
    else
	return VALUES_2(Nil ? Evaluation_true_value : 
		Evaluation_false_value,Nil ? Evaluation_true_value : 
		Evaluation_false_value);
}

/* G2-PRIORITY-QUEUE-IS-EMPTY */
Object g2_priority_queue_is_empty(queue)
    Object queue;
{
    x_note_fn_call(146,19);
    if ( !TRUEP(get_highest_priority(queue)))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-PRIORITY-QUEUE-GET-PRIORITY */
Object g2_priority_queue_get_priority(queue,object)
    Object queue, object;
{
    Object object_ref, table, index_1, temp, temp_1;

    x_note_fn_call(146,20);
    object_ref = get_reference_to_item(object);
    table = ISVREF(queue,(SI_Long)22L);
    index_1 = eq_gethash(table,object_ref,Qnot_found);
    if (EQ(index_1,Qnot_found))
	return VALUES_2(Nil ? Evaluation_true_value : 
		Evaluation_false_value,Nil ? Evaluation_true_value : 
		Evaluation_false_value);
    else {
	temp = T ? Evaluation_true_value : Evaluation_false_value;
	temp_1 = copy_managed_float(FIXNUM_LE(ISVREF(ISVREF(queue,
		(SI_Long)21L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(queue,(SI_Long)21L),IFIX(FIXNUM_ADD(index_1,
		Managed_array_index_offset))) : ISVREF(ISVREF(ISVREF(queue,
		(SI_Long)21L),(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
	return VALUES_2(temp,temp_1);
    }
}

/* QUEUE-CONTENTS */
Object queue_contents(queue)
    Object queue;
{
    Object result_1, object, priority;
    Object result;

    x_note_fn_call(146,21);
    result_1 = Nil;
  next_loop:
    result = get_and_remove_highest_priority(queue);
    MVS_2(result,object,priority);
    if (object)
	result_1 = eval_cons_1(eval_cons_1(object,priority),result_1);
    else
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
    return nreverse(result_1);
}

/* REBUILD-PRIORITY-QUEUE */
Object rebuild_priority_queue(pairs,queue)
    Object pairs, queue;
{
    Object item, priority, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(146,22);
    item = Nil;
    priority = Nil;
    ab_loop_list_ = pairs;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    item = CAR(ab_loop_desetq_);
    priority = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = get_reference_to_item(item);
    priority_queue_add(queue,temp,priority);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* INITIAL-G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES */
Object initial_g2_priority_queue_number_of_entries(class_1)
    Object class_1;
{
    x_note_fn_call(146,23);
    return VALUES_1(FIX((SI_Long)0L));
}

/* GET-G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES */
Object get_g2_priority_queue_number_of_entries(priority_queue)
    Object priority_queue;
{
    Object queue_contents_1, result_1, pair, ab_loop_list_;

    x_note_fn_call(146,24);
    queue_contents_1 = queue_contents(priority_queue);
    result_1 = length(queue_contents_1);
    rebuild_priority_queue(queue_contents_1,priority_queue);
    pair = Nil;
    ab_loop_list_ = queue_contents_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_eval_cons_1(pair);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(queue_contents_1);
    return VALUES_1(result_1);
}

/* INITIAL-G2-PRIORITY-QUEUE-SEQUENCE */
Object initial_g2_priority_queue_sequence(class_1)
    Object class_1;
{
    x_note_fn_call(146,25);
    return VALUES_1(FIX((SI_Long)0L));
}

static Object Qentry;              /* entry */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qpriority;           /* priority */

static Object Qab_structure;       /* structure */

/* GET-G2-PRIORITY-QUEUE-SEQUENCE */
Object get_g2_priority_queue_sequence(priority_queue)
    Object priority_queue;
{
    Object queue_contents_1, pair, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value, structure_list, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(146,26);
    if ((SI_Long)0L != (IFIX(ISVREF(priority_queue,(SI_Long)5L)) & 
	    (SI_Long)1L)) {
	queue_contents_1 = queue_contents(priority_queue);
	pair = Nil;
	ab_loop_list_ = queue_contents_1;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qentry;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qentry;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = CAR(pair);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = CAR(pair);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qpriority;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qpriority;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = copy_managed_float(CDR(pair));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = copy_managed_float(CDR(pair));
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,
		Qab_structure),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	structure_list = ab_loopvar_;
	goto end_1;
	structure_list = Qnil;
      end_1:;
	rebuild_priority_queue(queue_contents_1,priority_queue);
	pair = Nil;
	ab_loop_list_ = queue_contents_1;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	pair = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_eval_cons_1(pair);
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_list_1(queue_contents_1);
	temp_2 = allocate_evaluation_sequence(structure_list);
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* G2-PRIORITY-QUEUE-LENGTH */
Object g2_priority_queue_length(queue)
    Object queue;
{
    x_note_fn_call(146,27);
    return VALUES_1(ISVREF(queue,(SI_Long)23L));
}

/* G2-PRIORITY-QUEUE-CLEAR */
Object g2_priority_queue_clear(queue)
    Object queue;
{
    x_note_fn_call(146,28);
    return clear_priority_queue(queue);
}

/* PRIORITY-QUEUE-REHASH */
Object priority_queue_rehash(queue)
    Object queue;
{
    Object queue_size, objects, old_table, table;
    SI_Long hash_size, index_1, ab_loop_bind_;

    x_note_fn_call(146,29);
    queue_size = ISVREF(queue,(SI_Long)23L);
    hash_size = (IFIX(queue_size) << (SI_Long)1L) + (SI_Long)1L;
    objects = ISVREF(queue,(SI_Long)20L);
    old_table = ISVREF(queue,(SI_Long)22L);
    table = make_eq_hash_table(FIX(hash_size),Nil,Nil);
    reclaim_eq_hash_table(old_table);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(queue_size);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    eq_puthash(table,FIXNUM_LE(ISVREF(objects,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(objects,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(objects,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L),FIX(index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(ISVREF(queue,(SI_Long)22L) = table);
}

void priority_queues_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qg2_priority_queue_clear;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_priority_queue_length, Qget_g2_priority_queue_sequence;
    Object Qinitial_g2_priority_queue_sequence, list_constant_2;
    Object list_constant_5, list_constant_1, Qg2_priority_queue_sequence;
    Object list_constant_4, list_constant_3, Qab_or, Qno_item;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qvirtual_attributes_local_to_class, Qpriority_queue;
    Object Qget_g2_priority_queue_number_of_entries;
    Object Qinitial_g2_priority_queue_number_of_entries;
    Object Qg2_priority_queue_number_of_entries;
    Object Qexclude_from_wildcard_denotation, Qab_class;
    Object Qg2_priority_queue_get_priority, Qg2_priority_queue_is_empty;
    Object Qg2_priority_queue_pop, Qg2_priority_queue_top;
    Object Qg2_priority_queue_remove_element;
    Object Qg2_priority_queue_change_priority, Qg2_priority_queue_push;
    Object Qslot_value_reclaimer, Qreclaim_priority_queue_priority_array_value;
    Object Qpriority_queue_priority_array;
    Object Qreclaim_priority_queue_object_array_value;
    Object Qpriority_queue_object_array;
    Object Qreclaim_priority_queue_object_table_value;
    Object Qpriority_queue_object_table, Qclasses_which_define, Qdeactivate;
    Object Qdeactivate_for_priority_queue;
    Object Qmake_priority_queue_initial_object_table;
    Object Qmake_priority_queue_initial_priority_array;
    Object Qmake_priority_queue_initial_object_array, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, list_constant, Qcreate_icon_description;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant, Qobject;

    x_note_fn_call(146,30);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qpriority_queue = STATIC_SYMBOL("PRIORITY-QUEUE",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qpriority_queue,list_constant);
    string_constant = 
	    STATIC_STRING("1n1m8v839ly1l8t1m83-Cy53*2ypriority queues allow insertion of items at priorities, and determination of and removal of top-prior");
    string_constant_1 = STATIC_STRING("ity item, all in logarithmic time");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qmake_priority_queue_initial_object_array = 
	    STATIC_SYMBOL("MAKE-PRIORITY-QUEUE-INITIAL-OBJECT-ARRAY",
	    AB_package);
    Qmake_priority_queue_initial_priority_array = 
	    STATIC_SYMBOL("MAKE-PRIORITY-QUEUE-INITIAL-PRIORITY-ARRAY",
	    AB_package);
    Qmake_priority_queue_initial_object_table = 
	    STATIC_SYMBOL("MAKE-PRIORITY-QUEUE-INITIAL-OBJECT-TABLE",
	    AB_package);
    string_constant_2 = 
	    STATIC_STRING("1p4z8r8u8u839ly839ly01v8w9k3ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1");
    string_constant_3 = 
	    STATIC_STRING("mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83");
    string_constant_4 = 
	    STATIC_STRING("Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3h");
    string_constant_5 = 
	    STATIC_STRING("y1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy83*Uy1o83Gy+s3-Cykkkkkl3A++");
    string_constant_6 = 
	    STATIC_STRING("y1ms3Hy83=Ay83*Uy1o83Gy+s3fykkkkkl3A++y1m3Hy3Sy83=Ay83*Uy1o83Gy+s3-Dykkkkkl3A++y1m3Qy3dy83=Ay000001q1p83*Ny3Ny3My3dy3cy1p83-Lykk");
    string_constant_7 = 
	    STATIC_STRING("3ky3ky1p83-nykk3ky3ky1p83-mykk3ky3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definiti");
    string_constant_8 = 
	    STATIC_STRING("on000004z8r83Y9y83Y9y839ly839ly01m83*Ay9l001m1l8o1l8l000004z8r83YBy83YBy839ly839ly01m83*Ay9m001m1l8o1l8l000004z8r83YAy83YAy839ly");
    string_constant_9 = 
	    STATIC_STRING("839ly01m83*Ay9n001m1l8o1l8l000004z8r83YCy83YCy839ly839ly0k001m1l8o1l8l00000");
    string_constant_10 = 
	    STATIC_STRING("1r8q1p839ly1l83-Oy1m8v839ly8t1m83-Cy53*2ypriority queues allow insertion of items at priorities, and determination of and remova");
    string_constant_11 = 
	    STATIC_STRING("l of top-priority item, all in logarithmic time1m8u1v8w9k3ky3ky13Gy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy");
    string_constant_12 = 
	    STATIC_STRING("83Ty1l83-iy1l83-jy83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk");
    string_constant_13 = 
	    STATIC_STRING("1m3hyn1mnn1n1mnn1mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1");
    string_constant_14 = 
	    STATIC_STRING("n1m3ky3ky1mk3ky1mn3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp");
    string_constant_15 = 
	    STATIC_STRING("3fy83*Uy1o83Gy+s3-Cykkkkkl3A++y1ms3Hy83=Ay83*Uy1o83Gy+s3fykkkkkl3A++y1m3Hy3Sy83=Ay83*Uy1o83Gy+s3-Dykkkkkl3A++y1m3Qy3dy83=Ay00000");
    string_constant_16 = 
	    STATIC_STRING("1q1p83*Ny3Ny3My3dy3cy1p83-Lykk3ky3ky1p83-nykk3ky3ky1p83-mykk3ky3ky1p83*Nykk3ky3ky1p83*Uysq3Gy3My1o83Y9y1m83*Ay9l8o8l1o83YBy1m83*");
    string_constant_17 = 
	    STATIC_STRING("Ay9m8o8l1o83YAy1m83*Ay9n8o8l1o83YCyk8o8l");
    temp = regenerate_optimized_constant(LIST_2(string_constant,
	    string_constant_1));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qmake_priority_queue_initial_object_array);
    push_optimized_constant(Qmake_priority_queue_initial_priority_array);
    push_optimized_constant(Qmake_priority_queue_initial_object_table);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_2,
	    string_constant_3,string_constant_4,string_constant_5,
	    string_constant_6,string_constant_7,string_constant_8,
	    string_constant_9));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qmake_priority_queue_initial_object_array);
    push_optimized_constant(Qmake_priority_queue_initial_priority_array);
    push_optimized_constant(Qmake_priority_queue_initial_object_table);
    add_class_to_environment(9,Qpriority_queue,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,regenerate_optimized_constant(list(8,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17)),Nil);
    Priority_queue_initial_size = FIX((SI_Long)100L);
    SET_SYMBOL_FUNCTION(Qmake_priority_queue_initial_object_array,
	    STATIC_FUNCTION(make_priority_queue_initial_object_array,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmake_priority_queue_initial_priority_array,
	    STATIC_FUNCTION(make_priority_queue_initial_priority_array,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qmake_priority_queue_initial_object_table,
	    STATIC_FUNCTION(make_priority_queue_initial_object_table,NIL,
	    FALSE,0,0));
    Qnot_found = STATIC_SYMBOL("NOT-FOUND",AB_package);
    Qdeactivate_for_priority_queue = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-PRIORITY-QUEUE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_priority_queue,
	    STATIC_FUNCTION(deactivate_for_priority_queue,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_priority_queue);
    set_get(Qpriority_queue,Qdeactivate,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qpriority_queue,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qpriority_queue_object_table = 
	    STATIC_SYMBOL("PRIORITY-QUEUE-OBJECT-TABLE",AB_package);
    Qreclaim_priority_queue_object_table_value = 
	    STATIC_SYMBOL("RECLAIM-PRIORITY-QUEUE-OBJECT-TABLE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_priority_queue_object_table_value,
	    STATIC_FUNCTION(reclaim_priority_queue_object_table_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qpriority_queue_object_table,
	    SYMBOL_FUNCTION(Qreclaim_priority_queue_object_table_value),
	    Qslot_value_reclaimer);
    Qpriority_queue_object_array = 
	    STATIC_SYMBOL("PRIORITY-QUEUE-OBJECT-ARRAY",AB_package);
    Qreclaim_priority_queue_object_array_value = 
	    STATIC_SYMBOL("RECLAIM-PRIORITY-QUEUE-OBJECT-ARRAY-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_priority_queue_object_array_value,
	    STATIC_FUNCTION(reclaim_priority_queue_object_array_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qpriority_queue_object_array,
	    SYMBOL_FUNCTION(Qreclaim_priority_queue_object_array_value),
	    Qslot_value_reclaimer);
    Qpriority_queue_priority_array = 
	    STATIC_SYMBOL("PRIORITY-QUEUE-PRIORITY-ARRAY",AB_package);
    Qreclaim_priority_queue_priority_array_value = 
	    STATIC_SYMBOL("RECLAIM-PRIORITY-QUEUE-PRIORITY-ARRAY-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_priority_queue_priority_array_value,
	    STATIC_FUNCTION(reclaim_priority_queue_priority_array_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpriority_queue_priority_array,
	    SYMBOL_FUNCTION(Qreclaim_priority_queue_priority_array_value),
	    Qslot_value_reclaimer);
    Qg2_priority_queue_push = STATIC_SYMBOL("G2-PRIORITY-QUEUE-PUSH",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_push,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_push,
	    STATIC_FUNCTION(g2_priority_queue_push,NIL,FALSE,3,3));
    Qg2_priority_queue_change_priority = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-CHANGE-PRIORITY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_change_priority,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_change_priority,
	    STATIC_FUNCTION(g2_priority_queue_change_priority,NIL,FALSE,3,3));
    Qg2_priority_queue_remove_element = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-REMOVE-ELEMENT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_remove_element,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_remove_element,
	    STATIC_FUNCTION(g2_priority_queue_remove_element,NIL,FALSE,2,2));
    Qg2_priority_queue_top = STATIC_SYMBOL("G2-PRIORITY-QUEUE-TOP",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_top,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_top,
	    STATIC_FUNCTION(g2_priority_queue_top,NIL,FALSE,1,1));
    Qg2_priority_queue_pop = STATIC_SYMBOL("G2-PRIORITY-QUEUE-POP",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_pop,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_pop,
	    STATIC_FUNCTION(g2_priority_queue_pop,NIL,FALSE,1,1));
    Qg2_priority_queue_is_empty = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-IS-EMPTY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_is_empty,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_is_empty,
	    STATIC_FUNCTION(g2_priority_queue_is_empty,NIL,FALSE,1,1));
    Qg2_priority_queue_get_priority = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-GET-PRIORITY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_get_priority,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_get_priority,
	    STATIC_FUNCTION(g2_priority_queue_get_priority,NIL,FALSE,2,2));
    Qg2_priority_queue_number_of_entries = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES",AB_package);
    temp_2 = CONS(Qg2_priority_queue_number_of_entries,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qpriority_queue),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qg2_priority_queue_number_of_entries,temp);
    set_property_value_function(get_symbol_properties_function(Qpriority_queue),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qab_class,Qpriority_queue);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qexclude_from_wildcard_denotation,Qt);
    Qinitial_g2_priority_queue_number_of_entries = 
	    STATIC_SYMBOL("INITIAL-G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_priority_queue_number_of_entries,
	    STATIC_FUNCTION(initial_g2_priority_queue_number_of_entries,
	    NIL,FALSE,1,1));
    Qget_g2_priority_queue_number_of_entries = 
	    STATIC_SYMBOL("GET-G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_priority_queue_number_of_entries,
	    STATIC_FUNCTION(get_g2_priority_queue_number_of_entries,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qg2_priority_queue_number_of_entries,
	    list_constant_1,Qinteger,list_constant_2,
	    SYMBOL_FUNCTION(Qinitial_g2_priority_queue_number_of_entries),
	    SYMBOL_FUNCTION(Qget_g2_priority_queue_number_of_entries),Nil);
    Qg2_priority_queue_sequence = 
	    STATIC_SYMBOL("G2-PRIORITY-QUEUE-SEQUENCE",AB_package);
    temp_2 = CONS(Qg2_priority_queue_sequence,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qpriority_queue),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qg2_priority_queue_sequence,temp);
    set_property_value_function(get_symbol_properties_function(Qpriority_queue),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qentry = STATIC_SYMBOL("ENTRY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_3 = STATIC_CONS(Qno_item,Qnil);
    list_constant_4 = STATIC_CONS(Qsequence,Qnil);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_3,
	    list_constant_4);
    Qinitial_g2_priority_queue_sequence = 
	    STATIC_SYMBOL("INITIAL-G2-PRIORITY-QUEUE-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_g2_priority_queue_sequence,
	    STATIC_FUNCTION(initial_g2_priority_queue_sequence,NIL,FALSE,1,1));
    Qget_g2_priority_queue_sequence = 
	    STATIC_SYMBOL("GET-G2-PRIORITY-QUEUE-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qget_g2_priority_queue_sequence,
	    STATIC_FUNCTION(get_g2_priority_queue_sequence,NIL,FALSE,1,1));
    add_virtual_attribute(Qg2_priority_queue_sequence,list_constant_1,
	    list_constant_5,list_constant_2,
	    SYMBOL_FUNCTION(Qinitial_g2_priority_queue_sequence),
	    SYMBOL_FUNCTION(Qget_g2_priority_queue_sequence),Nil);
    Qg2_priority_queue_length = STATIC_SYMBOL("G2-PRIORITY-QUEUE-LENGTH",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_length,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_length,
	    STATIC_FUNCTION(g2_priority_queue_length,NIL,FALSE,1,1));
    Qg2_priority_queue_clear = STATIC_SYMBOL("G2-PRIORITY-QUEUE-CLEAR",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_priority_queue_clear,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_priority_queue_clear,
	    STATIC_FUNCTION(g2_priority_queue_clear,NIL,FALSE,1,1));
}
