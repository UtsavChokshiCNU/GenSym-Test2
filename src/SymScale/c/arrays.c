/* arrays.c
 * Input file:  arrays.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "arrays.h"


/* G2-ARRAY-LENGTH-FUNCTION */
Object g2_array_length_function(g2_array)
    Object g2_array;
{
    Object temp;

    x_note_fn_call(144,0);
    temp = ISVREF(g2_array,(SI_Long)20L);
    return VALUES_1(temp);
}

/* RECLAIM-MANAGED-G2-ARRAY-VALUE */
Object reclaim_managed_g2_array_value(managed_g2_array_qm,g2_array)
    Object managed_g2_array_qm, g2_array;
{
    Object thing, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(144,1);
    if (managed_g2_array_qm &&  !EQ(managed_g2_array_qm,
	    Initialization_inhibit)) {
	if (CONSP(managed_g2_array_qm)) {
	    thing = M_CAR(managed_g2_array_qm);
	    if ( !(SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		    Managed_array_unique_marker))) {
		reclaim_slot_value_tree_1(managed_g2_array_qm);
	      next_loop:
		gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
		gensymed_symbol_1 = Nil;
		if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol,
			gensymed_symbol_1))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    else {
		reclaim_managed_g2_array(M_CAR(managed_g2_array_qm),
			ISVREF(g2_array,(SI_Long)21L));
		M_CAR(managed_g2_array_qm) = Nil;
		reclaim_slot_value_cons_1(managed_g2_array_qm);
	    }
	}
	else
	    reclaim_managed_g2_array(managed_g2_array_qm,ISVREF(g2_array,
		    (SI_Long)21L));
    }
    return VALUES_1(Nil);
}

static Object Qg2_array_length_conflict;  /* g2-array-length-conflict */

/* PUT-G2-ARRAY-LENGTH */
Object put_g2_array_length(g2_array,new_length,initializing_qm)
    Object g2_array, new_length, initializing_qm;
{
    Object element_type, old_length, temp, gensymed_symbol, gensymed_symbol_1;
    Object new_array, managed_g2_array_qm;
    char temp_1;

    x_note_fn_call(144,2);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    old_length = ISVREF(g2_array,(SI_Long)20L);
    if (Reading_kb_p) {
	temp = ISVREF(g2_array,(SI_Long)23L);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
      next_loop:
	gensymed_symbol = ISVREF(g2_array,(SI_Long)20L);
	gensymed_symbol_1 = new_length;
	if (CAS_SVREF(g2_array,(SI_Long)20L,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:;
    }
    else {
	if (ISVREF(g2_array,(SI_Long)24L) &&  !TRUEP(initializing_qm) &&  
		!TRUEP(ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L)))) {
	    new_array = allocate_managed_g2_array(4,old_length,
		    element_type,Nil,Nil);
	    if (CAS_SVREF(g2_array,(SI_Long)23L,Nil,new_array))
		managed_g2_array_qm = new_array;
	    else {
		temp = ISVREF(g2_array,(SI_Long)23L);
		reclaim_managed_g2_array(new_array,element_type);
		managed_g2_array_qm = temp;
	    }
	}
	else
	    managed_g2_array_qm = ISVREF(g2_array,(SI_Long)23L);
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(g2_array);
      next_loop_1:
	gensymed_symbol = ISVREF(g2_array,(SI_Long)20L);
	gensymed_symbol_1 = new_length;
	if (CAS_SVREF(g2_array,(SI_Long)20L,gensymed_symbol,gensymed_symbol_1))
	    goto end_2;
	goto next_loop_1;
      end_loop_1:
      end_2:
	if (g2_array_length_and_initial_values_match_p(new_length,
		ISVREF(g2_array,(SI_Long)22L)))
	    delete_frame_note_if_any(Qg2_array_length_conflict,g2_array);
	else
	    add_frame_note(5,Qg2_array_length_conflict,g2_array,Nil,Nil,Nil);
	if ( !(initializing_qm ||  !TRUEP(managed_g2_array_qm) || 
		EQ(managed_g2_array_qm,Initialization_inhibit))) {
	    if (FIXNUM_LT(new_length,old_length) && (SI_Long)0L != 
		    (IFIX(ISVREF(g2_array,(SI_Long)5L)) & (SI_Long)1L))
		reclaim_managed_g2_array_elements_if_necessary(managed_g2_array_qm,
			element_type,new_length);
	  next_loop_2:
	    gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
	    gensymed_symbol_1 = adjust_managed_g2_array(3,
		    managed_g2_array_qm,new_length,element_type);
	    if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	    if (FIXNUM_GT(new_length,old_length) && (SI_Long)0L != 
		    (IFIX(ISVREF(g2_array,(SI_Long)5L)) & (SI_Long)1L))
		initialize_g2_array_at_position(g2_array,old_length);
	}
    }
    return VALUES_1(new_length);
}

/* PUT-ARRAY-IS-PERMANENT */
Object put_array_is_permanent(g2_array,value,gensymed_symbol)
    Object g2_array, value, gensymed_symbol;
{
    Object gensymed_symbol_1;

    x_note_fn_call(144,3);
  next_loop:
    gensymed_symbol = ISVREF(g2_array,(SI_Long)24L);
    gensymed_symbol_1 = value;
    if (CAS_SVREF(g2_array,(SI_Long)24L,gensymed_symbol,gensymed_symbol_1))
	return VALUES_1(gensymed_symbol);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qnone;               /* none */

static Object Qquantity;           /* quantity */

static Object Qdatum;              /* datum */

static Object Qtext;               /* text */

static Object Qtruth_value;        /* truth-value */

static Object Qitem;               /* item */

static Object Qitem_or_datum;      /* item-or-datum */

static Object string_constant;     /* "a default initial value of ~NC will be used because ~
				    *               there is more than one initial value and the array-length, ~d, ~
				    *               is not equal to the number of these values, ~d"
				    */

/* WRITE-G2-ARRAY-LENGTH-CONFLICT-NOTE */
Object write_g2_array_length_conflict_note(particulars,g2_array)
    Object particulars, g2_array;
{
    Object default_qm, array_type, temp, temp_1;

    x_note_fn_call(144,4);
    default_qm = g2_array_or_list_default_element_value(g2_array);
    array_type = ISVREF(g2_array,(SI_Long)21L);
    temp = default_qm;
    if (temp);
    else
	temp = Qnone;
    if (EQ(array_type,Qsymbol))
	temp_1 = Qsymbol;
    else if (EQ(array_type,Qquantity) || EQ(array_type,Qnumber) || 
	    EQ(array_type,Qfloat) || EQ(array_type,Qdatum))
	temp_1 = Qnumber;
    else if (EQ(array_type,Qtext))
	temp_1 = Qtext;
    else if (EQ(array_type,Qtruth_value))
	temp_1 = Qtruth_value;
    else if (EQ(array_type,Qitem) || EQ(array_type,Qitem_or_datum))
	temp_1 = Qsymbol;
    else
	temp_1 = array_type;
    GENSYM_RETURN_ONE(tformat(5,string_constant,temp,temp_1,
	    ISVREF(g2_array,(SI_Long)20L),length(ISVREF(g2_array,
	    (SI_Long)22L))));
    return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qg2_array_initial_values;  /* g2-array-initial-values */

/* PUT-G2-ARRAY-INITIAL-VALUES */
Object put_g2_array_initial_values(g2_array,new_initial_values,gensymed_symbol)
    Object g2_array, new_initial_values, gensymed_symbol;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(144,5);
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(g2_array,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = nconc2(stack_change_list_2(g2_array,
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
	M_CAR(gensymed_symbol_1) = g2_array;
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
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(g2_array,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_array,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = g2_array;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(g2_array,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(g2_array,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (g2_array_length_and_initial_values_match_p(ISVREF(g2_array,
	      (SI_Long)20L),new_initial_values))
	  delete_frame_note_if_any(Qg2_array_length_conflict,g2_array);
      else
	  add_frame_note(5,Qg2_array_length_conflict,g2_array,Nil,Nil,Nil);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(g2_array,Qg2_array_initial_values);
      SVREF(g2_array,FIX((SI_Long)22L)) = new_initial_values;
      result_1 = new_initial_values;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(g2_array,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(g2_array,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_array,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = g2_array;
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
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop;
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(g2_array,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(g2_array,slot_description,Nil,
		  Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(g2_array);
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
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(result_1);
}

/* PUT-G2-ARRAY-ELEMENT-TYPE */
Object put_g2_array_element_type(g2_array,new_element_type,initializing_qm)
    Object g2_array, new_element_type, initializing_qm;
{
    Object managed_g2_array_qm, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, frame_and_slot_or_atom;
    Object ab_loop_list_, ab_loop_it_, temp_2, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(144,6);
    if (EQ(new_element_type,Qquantity))
	new_element_type = Qnumber;
    if ( !(initializing_qm || Reading_kb_p)) {
	managed_g2_array_qm = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
	if (managed_g2_array_qm)
	    validate_and_fix_g2_item_array_elements(g2_array,new_element_type);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(g2_array,(SI_Long)1L),Nil);
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
	gensymed_symbol_1 = nconc2(stack_change_list_2(g2_array,
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
	M_CAR(gensymed_symbol_1) = g2_array;
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
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(g2_array,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_array,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = g2_array;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(g2_array,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(g2_array,(SI_Long)5L) = FIX(svref_new_value_1);
      }
    next_loop:
      gensymed_symbol = ISVREF(g2_array,(SI_Long)21L);
      gensymed_symbol_1 = new_element_type;
      if (CAS_SVREF(g2_array,(SI_Long)21L,gensymed_symbol,gensymed_symbol_1)) {
	  result_1 = gensymed_symbol;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      result_1 = Qnil;
    end_1:
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(g2_array,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(g2_array,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_array,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = g2_array;
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
	  ab_loop_it_ = temp_1 ? (EQ(g2_array,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_1 = TRUEP(Qnil);
	end_2:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(g2_array,slot_description,Nil,
		  Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(g2_array);
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
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_element_type);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-ARRAY */
Object activate_subclass_of_entity_for_g2_array(g2_array)
    Object g2_array;
{
    x_note_fn_call(144,7);
    if ( !EQ(ISVREF(g2_array,(SI_Long)23L),Initialization_inhibit))
	return note_item_needing_initialization_function(g2_array);
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-ARRAY */
Object deactivate_subclass_of_entity_for_g2_array(g2_array)
    Object g2_array;
{
    Object managed_g2_array_qm;

    x_note_fn_call(144,8);
    managed_g2_array_qm = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    if ( !( !TRUEP(managed_g2_array_qm) || Warmbooting_qm || 
	    EQ(managed_g2_array_qm,Initialization_inhibit) || 
	    ISVREF(g2_array,(SI_Long)24L)))
	return reclaim_managed_g2_array_elements_if_necessary(managed_g2_array_qm,
		ISVREF(g2_array,(SI_Long)21L),FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* ALLOCATE-MANAGED-G2-ARRAY */
Object allocate_managed_g2_array varargs_1(int, n)
{
    Object length_1, g2_array_element_type;
    Object dont_initialize, make_exactly;
    Declare_varargs_nonrelocating;

    x_note_fn_call(144,9);
    INIT_ARGS_nonrelocating();
    length_1 = REQUIRED_ARG_nonrelocating();
    g2_array_element_type = REQUIRED_ARG_nonrelocating();
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    make_exactly = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(g2_array_element_type,Qfloat))
	return allocate_managed_float_array(2,length_1,make_exactly);
    else if (g2_list_or_array_element_type_may_contain_item_p(g2_array_element_type))
	return allocate_managed_array(3,FIX((SI_Long)2L * IFIX(length_1)),
		dont_initialize,make_exactly);
    else
	return allocate_managed_array(3,length_1,dont_initialize,make_exactly);
}

static Object list_constant;       /* # */

/* RECLAIM-MANAGED-G2-ARRAY */
Object reclaim_managed_g2_array(managed_g2_array,g2_array_element_type)
    Object managed_g2_array, g2_array_element_type;
{
    x_note_fn_call(144,10);
    if (SIMPLE_VECTOR_P(managed_g2_array) && EQ(ISVREF(managed_g2_array,
	    (SI_Long)0L),Managed_float_array_unique_marker))
	return reclaim_managed_float_array(managed_g2_array);
    else {
	if ( !TRUEP(memq_function(g2_array_element_type,list_constant)))
	    reclaim_managed_g2_array_elements_if_necessary(managed_g2_array,
		    g2_array_element_type,FIX((SI_Long)0L));
	return reclaim_managed_array(managed_g2_array);
    }
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object list_constant_1;     /* # */

/* RECLAIM-MANAGED-G2-ARRAY-ELEMENTS-IF-NECESSARY */
Object reclaim_managed_g2_array_elements_if_necessary(managed_g2_array,
	    g2_array_element_type,starting_position_qm)
    Object managed_g2_array, g2_array_element_type, starting_position_qm;
{
    Object start_index, item_or_value_qm, thing, svref_arg_1, old, new_1;
    Object svref_new_value;
    SI_Long adjusted_start_index, i, ab_loop_bind_, temp_1;
    char temp;

    x_note_fn_call(144,11);
    start_index = starting_position_qm;
    if (start_index);
    else
	start_index = FIX((SI_Long)0L);
    if (EQ(g2_array_element_type,Qitem_or_datum)) {
	adjusted_start_index = IFIX(start_index) * (SI_Long)2L;
	i = adjusted_start_index;
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
	item_or_value_qm = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	item_or_value_qm = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_g2_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	if (item_or_value_qm) {
	    if (SIMPLE_VECTOR_P(item_or_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_qm)) > 
		    (SI_Long)2L) {
		temp = EQ(ISVREF(item_or_value_qm,(SI_Long)1L),
			Qavailable_frame_vector);
		if (temp);
		else {
		    thing = ISVREF(item_or_value_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    : TRUEP(Qnil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		item_or_value_qm = 
			reclaim_managed_number_or_value_function(item_or_value_qm);
	    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = i + IFIX(Managed_array_index_offset);
		ISVREF(managed_g2_array,temp_1) = Nil;
	    }
	    else {
		svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_1 = i & (SI_Long)1023L;
		ISVREF(svref_arg_1,temp_1) = Nil;
	    }
	    temp_1 = i + (SI_Long)1L;
	    old = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(managed_g2_array,
		    temp_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_g2_array,(temp_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),temp_1 & (SI_Long)1023L);
	    new_1 = Nil;
	    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = temp_1 + IFIX(Managed_array_index_offset);
		ISVREF(managed_g2_array,temp_1) = svref_new_value;
	    }
	    else {
		svref_arg_1 = ISVREF(managed_g2_array,(temp_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_1 = temp_1 & (SI_Long)1023L;
		ISVREF(svref_arg_1,temp_1) = svref_new_value;
	    }
	}
	i = i + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (memq_function(g2_array_element_type,list_constant_1)) {
	i = IFIX(start_index);
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
	item_or_value_qm = Nil;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	item_or_value_qm = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_g2_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	if (item_or_value_qm) {
	    item_or_value_qm = 
		    reclaim_managed_number_or_value_function(item_or_value_qm);
	    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = i + IFIX(Managed_array_index_offset);
		ISVREF(managed_g2_array,temp_1) = Nil;
	    }
	    else {
		svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_1 = i & (SI_Long)1023L;
		ISVREF(svref_arg_1,temp_1) = Nil;
	    }
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else if (g2_list_or_array_element_type_may_contain_item_p(g2_array_element_type)) 
		{
	adjusted_start_index = IFIX(start_index) * (SI_Long)2L;
	i = adjusted_start_index;
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	temp_1 = i + (SI_Long)1L;
	old = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_g2_array,
		temp_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_array,(temp_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),temp_1 & (SI_Long)1023L);
	new_1 = Nil;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = temp_1 + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_array,temp_1) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(managed_g2_array,(temp_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = svref_new_value;
	}
	i = i + (SI_Long)2L;
	goto next_loop_2;
      end_loop_2:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-MANAGED-VALUES-FROM-MANAGED-G2-ARRAY */
Object clear_managed_values_from_managed_g2_array(managed_g2_array,
	    g2_array_element_type)
    Object managed_g2_array, g2_array_element_type;
{
    Object item_or_value_qm, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(144,12);
    if ( !EQ(g2_array_element_type,Qfloat)) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
	item_or_value_qm = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	item_or_value_qm = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_g2_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	if (item_or_value_qm) {
	    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = i + IFIX(Managed_array_index_offset);
		ISVREF(managed_g2_array,svref_arg_2) = Nil;
	    }
	    else {
		svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = i & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* MANAGED-G2-ARRAY-AREF */
Object managed_g2_array_aref(managed_g2_array,index_1)
    Object managed_g2_array, index_1;
{
    Object temp;

    x_note_fn_call(144,13);
    temp = SIMPLE_VECTOR_P(managed_g2_array) && EQ(ISVREF(managed_g2_array,
	    (SI_Long)0L),Managed_float_array_unique_marker) ? 
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
	    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(index_1) & (SI_Long)1023L)) : 
	    FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_g2_array,
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
    return VALUES_1(temp);
}

/* ADJUST-MANAGED-G2-ARRAY */
Object adjust_managed_g2_array varargs_1(int, n)
{
    Object managed_g2_array, new_length, g2_array_element_type;
    Object dont_copy, dont_initialize;
    Declare_varargs_nonrelocating;

    x_note_fn_call(144,14);
    INIT_ARGS_nonrelocating();
    managed_g2_array = REQUIRED_ARG_nonrelocating();
    new_length = REQUIRED_ARG_nonrelocating();
    g2_array_element_type = REQUIRED_ARG_nonrelocating();
    dont_copy = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    dont_initialize = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(g2_array_element_type,Qfloat))
	return adjust_managed_float_array(3,managed_g2_array,new_length,
		dont_copy);
    else if (g2_list_or_array_element_type_may_contain_item_p(g2_array_element_type))
	return adjust_managed_array(4,managed_g2_array,FIX((SI_Long)2L * 
		IFIX(new_length)),dont_copy,dont_initialize);
    else
	return adjust_managed_array(4,managed_g2_array,new_length,
		dont_copy,dont_initialize);
}

static Object Qfloat_array;        /* float-array */

static Object Qiteration_state;    /* iteration-state */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* COPY-AND-BOX-ELEMENT-VALUE-IF-NECESSARY */
Object copy_and_box_element_value_if_necessary(value)
    Object value;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, car_1, cdr_1, temp_2, gensymed_symbol, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_4, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    double aref_new_value;
    Object result;

    x_note_fn_call(144,15);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L || 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L || 
	    FLOATP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	else
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (text_string_p(value))
	return copy_as_wide_string(value);
    else {
	if (CONSP(value)) {
	    car_1 = M_CAR(value);
	    cdr_1 = M_CDR(value);
	    if (CONSP(cdr_1)) {
		temp_2 = M_CAR(cdr_1);
		temp_3 = SYMBOLP(temp_2);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_3 = temp_3 ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_2 = CDR(value);
	    if (CONSP(temp_2) && EQ(CADR(value),Qtruth_value)) {
		gensymed_symbol = CAR(value);
		if (FIXNUM_EQ(gensymed_symbol,Truth))
		    return VALUES_1(Evaluation_true_value);
		else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		    return VALUES_1(Evaluation_false_value);
		else
		    return eval_cons_1(gensymed_symbol,Qtruth_value);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (SYMBOLP(value))
	    return VALUES_1(value);
	else if (FIXNUMP(value))
	    return VALUES_1(value);
	else {
	    gensymed_symbol = value;
	    temp_3 = FIXNUMP(gensymed_symbol);
	    if (temp_3);
	    else
		temp_3 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_3);
	    else
		temp_3 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_3);
	    else
		temp_3 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_3);
	    else
		temp_3 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_3);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_3 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_3);
		else
		    temp_3 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_3);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_4 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_4,temp_2);
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
		    temp_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		if (FIXNUMP(value) || value && SYMBOLP(value))
		    return VALUES_1(value);
		else
		    return copy_evaluation_value_1(value);
	    }
	    else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		return make_evaluation_value_from_temporary_constant(value);
	    else
		return VALUES_1(value);
	}
    }
}

static Object float_constant;      /* 0.0 */

/* FILL-MANAGED-G2-FLOAT-ARRAY */
Object fill_managed_g2_float_array(managed_float_array,float_or_fixnum)
    Object managed_float_array, float_or_fixnum;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,16);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(float_or_fixnum) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_or_fixnum)) == 
		(SI_Long)1L)
	    result = fill_managed_float_array_with_managed_float(managed_float_array,
		    float_or_fixnum);
	else if (FLOATP(float_or_fixnum))
	    result = fill_managed_float_array(managed_float_array,
		    float_or_fixnum);
	else if (FIXNUMP(float_or_fixnum))
	    result = fill_managed_float_array(managed_float_array,
		    lfloat(float_or_fixnum,float_constant));
	else
	    result = VALUES_1(Qt);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* FILL-MANAGED-G2-QUANTITY-ARRAY */
Object fill_managed_g2_quantity_array(managed_g2_quantity_array,quantity)
    Object managed_g2_quantity_array, quantity;
{
    x_note_fn_call(144,17);
    return fill_managed_g2_quantity_array_at_position(managed_g2_quantity_array,
	    quantity,FIX((SI_Long)0L));
}

/* FILL-MANAGED-G2-TEXT-ARRAY */
Object fill_managed_g2_text_array(managed_g2_text_array,text_string)
    Object managed_g2_text_array, text_string;
{
    x_note_fn_call(144,18);
    return fill_managed_g2_text_array_at_position(managed_g2_text_array,
	    text_string,FIX((SI_Long)0L));
}

/* FILL-MANAGED-G2-ITEM-ARRAY */
Object fill_managed_g2_item_array(managed_g2_item_array,item_qm)
    Object managed_g2_item_array, item_qm;
{
    x_note_fn_call(144,19);
    return fill_managed_g2_item_array_at_position(managed_g2_item_array,
	    item_qm,FIX((SI_Long)0L));
}

/* FILL-MANAGED-G2-VALUE-ARRAY */
Object fill_managed_g2_value_array(managed_g2_value_array,value)
    Object managed_g2_value_array, value;
{
    x_note_fn_call(144,20);
    return fill_managed_g2_value_array_at_position(managed_g2_value_array,
	    value,FIX((SI_Long)0L));
}

/* FILL-MANAGED-G2-ITEM-OR-VALUE-ARRAY */
Object fill_managed_g2_item_or_value_array(managed_g2_item_or_value_array,
	    item_or_value_qm)
    Object managed_g2_item_or_value_array, item_or_value_qm;
{
    x_note_fn_call(144,21);
    return fill_managed_g2_item_or_value_array_at_position(managed_g2_item_or_value_array,
	    item_or_value_qm,FIX((SI_Long)0L));
}

/* FILL-MANAGED-G2-ARRAY-WITH-UNMANAGED-VALUE */
Object fill_managed_g2_array_with_unmanaged_value(managed_g2_array,
	    unmanaged_value)
    Object managed_g2_array, unmanaged_value;
{
    x_note_fn_call(144,22);
    return fill_managed_array(managed_g2_array,unmanaged_value);
}

/* FILL-MANAGED-G2-ARRAY */
Object fill_managed_g2_array(managed_g2_array,item_or_value_qm,element_type)
    Object managed_g2_array, item_or_value_qm, element_type;
{
    x_note_fn_call(144,23);
    if (EQ(element_type,Qfloat))
	return fill_managed_g2_float_array(managed_g2_array,item_or_value_qm);
    else if (EQ(element_type,Qnumber) || EQ(element_type,Qquantity))
	return fill_managed_g2_quantity_array(managed_g2_array,
		item_or_value_qm);
    else if (EQ(element_type,Qtext))
	return fill_managed_g2_text_array(managed_g2_array,item_or_value_qm);
    else if (EQ(element_type,Qdatum))
	return fill_managed_g2_value_array(managed_g2_array,item_or_value_qm);
    else if (EQ(element_type,Qitem_or_datum))
	return fill_managed_g2_item_or_value_array(managed_g2_array,
		item_or_value_qm);
    else if (EQ(element_type,Qsymbol) || EQ(element_type,Qinteger) || 
	    EQ(element_type,Qtruth_value))
	return fill_managed_g2_array_with_unmanaged_value(managed_g2_array,
		item_or_value_qm);
    else
	return fill_managed_g2_item_array(managed_g2_array,item_or_value_qm);
}

/* FILL-MANAGED-G2-FLOAT-ARRAY-AT-POSITION */
Object fill_managed_g2_float_array_at_position(managed_non_text_g2_array,
	    float_or_fixnum,start_position)
    Object managed_non_text_g2_array, float_or_fixnum, start_position;
{
    Object new_value, aref_arg_1;
    SI_Long i, ab_loop_bind_, aref_arg_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,24);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_value = normalize_to_gensym_float(float_or_fixnum);
	i = IFIX(start_position);
	ab_loop_bind_ = IFIX(ISVREF(managed_non_text_g2_array,(SI_Long)1L));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	aref_arg_1 = ISVREF(managed_non_text_g2_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* FILL-MANAGED-G2-QUANTITY-ARRAY-AT-POSITION */
Object fill_managed_g2_quantity_array_at_position(managed_g2_quantity_array,
	    quantity,start_position)
    Object managed_g2_quantity_array, quantity, start_position;
{
    Object new_value, store_managed_number_arg, svref_new_value, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,25);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_value = quantity;
	i = IFIX(start_position);
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_quantity_array,(SI_Long)1L));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	store_managed_number_arg = FIXNUMP(new_value) || new_value && 
		SYMBOLP(new_value) ? new_value : 
		copy_evaluation_value_1(new_value);
	svref_new_value = 
		store_managed_number_function(FIXNUM_LE(ISVREF(managed_g2_quantity_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_g2_quantity_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_quantity_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L),
		store_managed_number_arg);
	if (FIXNUM_LE(ISVREF(managed_g2_quantity_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = i + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_quantity_array,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(managed_g2_quantity_array,(i >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = i & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* FILL-MANAGED-G2-TEXT-ARRAY-AT-POSITION */
Object fill_managed_g2_text_array_at_position(managed_g2_text_array,
	    text_string,start_position)
    Object managed_g2_text_array, text_string, start_position;
{
    Object copied_text_string, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(144,26);
    i = IFIX(start_position);
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_text_array,(SI_Long)1L));
    copied_text_string = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    copied_text_string = copy_text_string(text_string);
    if (FIXNUM_LE(ISVREF(managed_g2_text_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_text_array,svref_arg_2) = copied_text_string;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_text_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = copied_text_string;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-MANAGED-G2-ITEM-ARRAY-AT-POSITION */
Object fill_managed_g2_item_array_at_position(managed_g2_text_array,
	    item_qm,start_position)
    Object managed_g2_text_array, item_qm, start_position;
{
    Object length_1, frame_serial_number_qm, i, temp;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    SI_Long svref_arg_2;

    x_note_fn_call(144,27);
    length_1 = ISVREF(managed_g2_text_array,(SI_Long)1L);
    frame_serial_number_qm = item_qm ? ISVREF(item_qm,(SI_Long)3L) : Qnil;
    i = FIX(IFIX(start_position) * (SI_Long)2L);
  next_loop:
    if (FIXNUM_GE(i,length_1))
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_g2_text_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(i,Managed_array_index_offset);
	SVREF(managed_g2_text_array,temp) = item_qm;
    }
    else {
	temp = ISVREF(managed_g2_text_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(i) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = item_qm;
    }
    i = FIXNUM_ADD1(i);
    frame_serial_number_setf_arg = frame_serial_number_qm;
    old = FIXNUM_LE(ISVREF(managed_g2_text_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_g2_text_array,
	    IFIX(FIXNUM_ADD(i,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_g2_text_array,(IFIX(i) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    if (FIXNUM_LE(ISVREF(managed_g2_text_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(i,Managed_array_index_offset);
	SVREF(managed_g2_text_array,temp) = svref_new_value;
    }
    else {
	temp = ISVREF(managed_g2_text_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(i) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-MANAGED-G2-VALUE-ARRAY-AT-POSITION */
Object fill_managed_g2_value_array_at_position(managed_g2_value_array,
	    value,start_position)
    Object managed_g2_value_array, value, start_position;
{
    Object temp, svref_new_value;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(144,28);
    i = IFIX(start_position);
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_value_array,(SI_Long)1L));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_g2_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	temp = copy_and_box_element_value_if_necessary(value);
	ISVREF(managed_g2_value_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_g2_value_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = copy_and_box_element_value_if_necessary(value);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-MANAGED-G2-ITEM-OR-VALUE-ARRAY-AT-POSITION */
Object fill_managed_g2_item_or_value_array_at_position(managed_g2_item_or_value_array,
	    item_or_value,start_position)
    Object managed_g2_item_or_value_array, item_or_value, start_position;
{
    Object length_1, x2, frame_p_qm, frame_serial_number_qm, i, temp;
    Object svref_new_value, frame_serial_number_setf_arg, old, new_1;
    SI_Long svref_arg_2;

    x_note_fn_call(144,29);
    length_1 = ISVREF(managed_g2_item_or_value_array,(SI_Long)1L);
    if (item_or_value) {
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    frame_p_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    frame_p_qm = Nil;
    }
    else
	frame_p_qm = Nil;
    frame_serial_number_qm = frame_p_qm ? ISVREF(item_or_value,
	    (SI_Long)3L) : Qnil;
    i = FIX(IFIX(start_position) * (SI_Long)2L);
  next_loop:
    if (FIXNUM_GE(i,length_1))
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(i,Managed_array_index_offset);
	svref_new_value = frame_p_qm ? item_or_value : 
		copy_and_box_element_value_if_necessary(item_or_value);
	SVREF(managed_g2_item_or_value_array,temp) = svref_new_value;
    }
    else {
	temp = ISVREF(managed_g2_item_or_value_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(i) & (SI_Long)1023L;
	svref_new_value = frame_p_qm ? item_or_value : 
		copy_and_box_element_value_if_necessary(item_or_value);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = FIXNUM_ADD1(i);
    frame_serial_number_setf_arg = frame_serial_number_qm;
    old = FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? 
	    ISVREF(managed_g2_item_or_value_array,IFIX(FIXNUM_ADD(i,
	    Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_g2_item_or_value_array,(IFIX(i) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    if (FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(i,Managed_array_index_offset);
	SVREF(managed_g2_item_or_value_array,temp) = svref_new_value;
    }
    else {
	temp = ISVREF(managed_g2_item_or_value_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(i) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = FIXNUM_ADD1(i);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-MANAGED-G2-ARRAY-AT-POSITION-WITH-UNMANAGED-VALUE */
Object fill_managed_g2_array_at_position_with_unmanaged_value(managed_g2_array,
	    unmanaged_value,start_position)
    Object managed_g2_array, unmanaged_value, start_position;
{
    Object svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(144,30);
    i = IFIX(start_position);
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_array,svref_arg_2) = unmanaged_value;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = unmanaged_value;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-MANAGED-G2-ARRAY-AT-POSITION */
Object fill_managed_g2_array_at_position(managed_g2_array,item_or_value_qm,
	    start_position,element_type)
    Object managed_g2_array, item_or_value_qm, start_position, element_type;
{
    x_note_fn_call(144,31);
    if (EQ(element_type,Qfloat))
	return fill_managed_g2_float_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
    else if (EQ(element_type,Qnumber) || EQ(element_type,Qquantity))
	return fill_managed_g2_quantity_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
    else if (EQ(element_type,Qtext))
	return fill_managed_g2_text_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
    else if (EQ(element_type,Qdatum))
	return fill_managed_g2_value_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
    else if (EQ(element_type,Qitem_or_datum))
	return fill_managed_g2_item_or_value_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
    else if (EQ(element_type,Qsymbol) || EQ(element_type,Qinteger) || 
	    EQ(element_type,Qtruth_value))
	return fill_managed_g2_array_at_position_with_unmanaged_value(managed_g2_array,
		item_or_value_qm,start_position);
    else
	return fill_managed_g2_item_array_at_position(managed_g2_array,
		item_or_value_qm,start_position);
}

Object Symbol_initial_value_marker_symbol = UNBOUND;

Object Symbol_initial_value_marker = UNBOUND;

/* FILL-VALUES-INTO-MANAGED-G2-FLOAT-ARRAY */
Object fill_values_into_managed_g2_float_array(managed_float_array,
	    list_of_floats_qm,element_type,default_element_value)
    Object managed_float_array, list_of_floats_qm, element_type;
    Object default_element_value;
{
    Object value, ab_loop_list_, aref_arg_1;
    SI_Long i, ab_loop_bind_, aref_arg_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,32);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(managed_float_array,(SI_Long)1L));
    value = Nil;
    ab_loop_list_ = list_of_floats_qm;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    aref_arg_1 = ISVREF(managed_float_array,(i >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    aref_arg_2 = i & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else if (evaluation_value_of_type_p(value,element_type)) {
	aref_arg_1 = ISVREF(managed_float_array,(i >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    }
    else {
	aref_arg_1 = ISVREF(managed_float_array,(i >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(default_element_value);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-VALUES-INTO-MANAGED-G2-QUANTITY-ARRAY */
Object fill_values_into_managed_g2_quantity_array(managed_g2_quantity_array,
	    list_of_quantities,element_type,default_element_value)
    Object managed_g2_quantity_array, list_of_quantities, element_type;
    Object default_element_value;
{
    Object quantity, ab_loop_list_, new_value, ab_loop_iter_flag_;
    Object store_managed_number_arg, svref_new_value, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,33);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	quantity = Nil;
	ab_loop_list_ = list_of_quantities;
	new_value = Nil;
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_g2_quantity_array,(SI_Long)1L));
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	quantity = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(quantity) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(quantity)) == (SI_Long)1L)
	    new_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(quantity,
		    (SI_Long)0L));
	else if (evaluation_value_of_type_p(quantity,element_type))
	    new_value = quantity;
	else
	    new_value = default_element_value;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	if (i >= ab_loop_bind_)
	    goto end_loop;
	store_managed_number_arg = new_value;
	svref_new_value = 
		store_managed_number_function(FIXNUM_LE(ISVREF(managed_g2_quantity_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_g2_quantity_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_g2_quantity_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L),
		store_managed_number_arg);
	if (FIXNUM_LE(ISVREF(managed_g2_quantity_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = i + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_quantity_array,svref_arg_2) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(managed_g2_quantity_array,(i >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = i & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* FILL-VALUES-INTO-MANAGED-G2-TEXT-ARRAY */
Object fill_values_into_managed_g2_text_array(managed_g2_text_array,
	    list_of_text_strings_qm,element_type,default_element_value)
    Object managed_g2_text_array, list_of_text_strings_qm, element_type;
    Object default_element_value;
{
    Object value, ab_loop_list_, copied_text_string, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(144,34);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_text_array,(SI_Long)1L));
    value = Nil;
    ab_loop_list_ = list_of_text_strings_qm;
    copied_text_string = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    copied_text_string = evaluation_value_of_type_p(value,element_type) ? 
	    copy_text_string(value) : copy_text_string(default_element_value);
    if (FIXNUM_LE(ISVREF(managed_g2_text_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_text_array,svref_arg_2) = copied_text_string;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_text_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = copied_text_string;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-VALUES-INTO-MANAGED-G2-ITEM-ARRAY */
Object fill_values_into_managed_g2_item_array(managed_g2_array,
	    list_of_items_qm,default_element_value)
    Object managed_g2_array, list_of_items_qm, default_element_value;
{
    Object length_1, value, ab_loop_list_, new_value, frame_serial_number, x2;
    Object svref_arg_1, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value;
    SI_Long i, svref_arg_2;
    char temp;

    x_note_fn_call(144,35);
    length_1 = ISVREF(managed_g2_array,(SI_Long)1L);
    i = (SI_Long)0L;
    value = Nil;
    ab_loop_list_ = list_of_items_qm;
    new_value = Nil;
    frame_serial_number = Nil;
  next_loop:
    if (i >= IFIX(length_1))
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    new_value = (temp ? TRUEP(ISVREF(ISVREF(value,(SI_Long)1L),
	    (SI_Long)16L)) : TRUEP(Nil)) ? value : default_element_value;
    if (SIMPLE_VECTOR_P(new_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) > (SI_Long)2L &&  
	    !EQ(ISVREF(new_value,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(new_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    frame_serial_number = (temp ? TRUEP(ISVREF(ISVREF(new_value,
	    (SI_Long)1L),(SI_Long)16L)) : TRUEP(Nil)) ? ISVREF(new_value,
	    (SI_Long)3L) : Nil;
    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_array,svref_arg_2) = new_value;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = new_value;
    }
    i = i + (SI_Long)1L;
    frame_serial_number_setf_arg = frame_serial_number;
    old = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_g2_array,i + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),i & (SI_Long)1023L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_array,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-VALUES-INTO-MANAGED-G2-VALUE-ARRAY */
Object fill_values_into_managed_g2_value_array(managed_g2_value_array,
	    list_of_values,element_type,default_element_value)
    Object managed_g2_value_array, list_of_values, element_type;
    Object default_element_value;
{
    Object value, ab_loop_list_, new_value, car_1, cdr_1, temp_1, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    char temp;

    x_note_fn_call(144,36);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_value_array,(SI_Long)1L));
    value = Nil;
    ab_loop_list_ = list_of_values;
    new_value = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = TRUEP(evaluation_value_of_type_p(value,element_type));
    if (temp);
    else {
	if (CONSP(value)) {
	    car_1 = M_CAR(value);
	    cdr_1 = M_CDR(value);
	    if (CONSP(cdr_1)) {
		temp_1 = M_CAR(cdr_1);
		temp = SYMBOLP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = CDR(value);
	    temp = CONSP(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	temp = temp ? EQ(CADR(value),Qtruth_value) : TRUEP(Nil);
    }
    if (temp)
	new_value = copy_and_box_element_value_if_necessary(value);
    else {
	if (CONSP(value)) {
	    temp_1 = M_CAR(value);
	    temp = CONSP(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ?  !TRUEP(M_CDR(M_CAR(value))) : TRUEP(Nil)) ? 
		EQ(M_CAR(M_CAR(value)),Symbol_initial_value_marker_symbol) 
		: TRUEP(Nil))
	    new_value = 
		    copy_and_box_element_value_if_necessary(M_CAR(M_CDR(value)));
	else
	    new_value = 
		    copy_and_box_element_value_if_necessary(default_element_value);
    }
    if (FIXNUM_LE(ISVREF(managed_g2_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_value_array,svref_arg_2) = new_value;
    }
    else {
	svref_arg_1 = ISVREF(managed_g2_value_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = new_value;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-VALUES-INTO-MANAGED-G2-ITEM-OR-VALUE-ARRAY */
Object fill_values_into_managed_g2_item_or_value_array(managed_g2_item_or_value_array,
	    list_of_items_or_values)
    Object managed_g2_item_or_value_array, list_of_items_or_values;
{
    Object length_1, item_or_value, ab_loop_list_, x2, frame_p_qm;
    Object frame_serial_number_qm, temp, svref_new_value;
    Object frame_serial_number_setf_arg, old, new_1;
    SI_Long i, svref_arg_2;

    x_note_fn_call(144,37);
    length_1 = ISVREF(managed_g2_item_or_value_array,(SI_Long)1L);
    i = (SI_Long)0L;
    item_or_value = Nil;
    ab_loop_list_ = list_of_items_or_values;
    if (item_or_value) {
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    frame_p_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    frame_p_qm = Nil;
    }
    else
	frame_p_qm = Nil;
    frame_serial_number_qm = frame_p_qm ? ISVREF(item_or_value,
	    (SI_Long)3L) : Qnil;
  next_loop:
    if (i >= IFIX(length_1))
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item_or_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	temp = frame_p_qm ? item_or_value : 
		copy_and_box_element_value_if_necessary(item_or_value);
	ISVREF(managed_g2_item_or_value_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_g2_item_or_value_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	svref_new_value = frame_p_qm ? item_or_value : 
		copy_and_box_element_value_if_necessary(item_or_value);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    frame_serial_number_setf_arg = frame_serial_number_qm;
    old = FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? 
	    ISVREF(managed_g2_item_or_value_array,i + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_g2_item_or_value_array,(i >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    if (FIXNUM_LE(ISVREF(managed_g2_item_or_value_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	ISVREF(managed_g2_item_or_value_array,svref_arg_2) = svref_new_value;
    }
    else {
	temp = ISVREF(managed_g2_item_or_value_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-UNMANAGED-VALUES-INTO-MANAGED-G2-ARRAY */
Object fill_unmanaged_values_into_managed_g2_array(managed_g2_array,
	    list_of_non_text_datum,element_type,default_element_value)
    Object managed_g2_array, list_of_non_text_datum, element_type;
    Object default_element_value;
{
    Object datum, ab_loop_list_, temp, temp_1, svref_new_value;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    char temp_2;

    x_note_fn_call(144,38);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(managed_g2_array,(SI_Long)1L));
    datum = Nil;
    ab_loop_list_ = list_of_non_text_datum;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    datum = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = i + IFIX(Managed_array_index_offset);
	if (evaluation_value_of_type_p(datum,element_type) || 
		EQ(element_type,Qtruth_value) && FIXNUMP(datum) && 
		IFIX(datum) <= (SI_Long)1000L && IFIX(datum) >= 
		(SI_Long)-1000L)
	    temp = datum;
	else {
	    if (EQ(element_type,Qsymbol)) {
		if (CONSP(datum)) {
		    temp_1 = M_CAR(datum);
		    temp_2 = CONSP(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_2 = (temp_2 ?  !TRUEP(M_CDR(M_CAR(datum))) : 
			TRUEP(Nil)) ? EQ(M_CAR(M_CAR(datum)),
			Symbol_initial_value_marker_symbol) : TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		temp = M_CAR(M_CDR(datum));
	    else
		temp = default_element_value;
	}
	ISVREF(managed_g2_array,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_g2_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = i & (SI_Long)1023L;
	if (evaluation_value_of_type_p(datum,element_type) || 
		EQ(element_type,Qtruth_value) && FIXNUMP(datum) && 
		IFIX(datum) <= (SI_Long)1000L && IFIX(datum) >= 
		(SI_Long)-1000L)
	    svref_new_value = datum;
	else {
	    if (EQ(element_type,Qsymbol)) {
		if (CONSP(datum)) {
		    temp_1 = M_CAR(datum);
		    temp_2 = CONSP(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_2 = (temp_2 ?  !TRUEP(M_CDR(M_CAR(datum))) : 
			TRUEP(Nil)) ? EQ(M_CAR(M_CAR(datum)),
			Symbol_initial_value_marker_symbol) : TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		svref_new_value = M_CAR(M_CDR(datum));
	    else
		svref_new_value = default_element_value;
	}
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-VALUES-INTO-MANAGED-G2-ARRAY */
Object fill_values_into_managed_g2_array(managed_g2_array,
	    list_of_items_or_values,element_type,default_element_value)
    Object managed_g2_array, list_of_items_or_values, element_type;
    Object default_element_value;
{
    x_note_fn_call(144,39);
    if (EQ(element_type,Qfloat))
	return fill_values_into_managed_g2_float_array(managed_g2_array,
		list_of_items_or_values,element_type,default_element_value);
    else if (EQ(element_type,Qnumber) || EQ(element_type,Qquantity))
	return fill_values_into_managed_g2_quantity_array(managed_g2_array,
		list_of_items_or_values,element_type,default_element_value);
    else if (EQ(element_type,Qtext))
	return fill_values_into_managed_g2_text_array(managed_g2_array,
		list_of_items_or_values,element_type,default_element_value);
    else if (EQ(element_type,Qdatum))
	return fill_values_into_managed_g2_value_array(managed_g2_array,
		list_of_items_or_values,element_type,default_element_value);
    else if (EQ(element_type,Qitem_or_datum))
	return fill_values_into_managed_g2_item_or_value_array(managed_g2_array,
		list_of_items_or_values);
    else if (EQ(element_type,Qsymbol) || EQ(element_type,Qinteger) || 
	    EQ(element_type,Qtruth_value))
	return fill_unmanaged_values_into_managed_g2_array(managed_g2_array,
		list_of_items_or_values,element_type,default_element_value);
    else
	return fill_values_into_managed_g2_item_array(managed_g2_array,
		list_of_items_or_values,default_element_value);
}

static Object Qg2;                 /* g2 */

static Object array_constant;      /* # */

/* G2-ARRAY-OR-LIST-DEFAULT-ELEMENT-VALUE */
Object g2_array_or_list_default_element_value(g2_array_or_list)
    Object g2_array_or_list;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(144,40);
    sub_class_bit_vector = ISVREF(ISVREF(g2_array_or_list,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    temp_1 = temp ? ISVREF(g2_array_or_list,(SI_Long)21L) : 
	    ISVREF(g2_array_or_list,(SI_Long)21L);
    if (EQ(temp_1,Qquantity) || EQ(temp_1,Qnumber) || EQ(temp_1,Qfloat) || 
	    EQ(temp_1,Qdatum))
	return VALUES_1(float_constant);
    else if (EQ(temp_1,Qinteger))
	return VALUES_1(FIX((SI_Long)0L));
    else if (EQ(temp_1,Qsymbol))
	return VALUES_1(Qg2);
    else if (EQ(temp_1,Qtext))
	return VALUES_1(array_constant);
    else if (EQ(temp_1,Qtruth_value))
	return VALUES_1(Falsity);
    else
	return VALUES_1(Nil);
}

/* G2-ARRAY-LENGTH-AND-INITIAL-VALUES-MATCH-P */
Object g2_array_length_and_initial_values_match_p(array_length,initial_values)
    Object array_length, initial_values;
{
    Object initial_values_length, temp;

    x_note_fn_call(144,41);
    initial_values_length = length(initial_values);
    temp = IFIX(initial_values_length) <= (SI_Long)1L ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(FIXNUM_EQ(array_length,initial_values_length) ? T :
		 Nil);
}

/* G2-ARRAY-ASET */
Object g2_array_aset(g2_array,index_1,item_or_datum_qm)
    Object g2_array, index_1, item_or_datum_qm;
{
    Object element_type, managed_g2_array, store_managed_number_arg;
    Object svref_new_value, temp, old_text_element_qm, value;
    Object old_datum_element_qm, car_1, cdr_1, temp_2, managed_value;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_4, entry_hash, x2, frame_p_qm;
    Object frame_serial_number_qm, new_element, frame_serial_number_setf_arg;
    Object old, new_1;
    SI_Long temp_1, key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long adjusted_index;
    char temp_3;
    double aref_new_value;
    Object result;

    x_note_fn_call(144,42);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_array);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    managed_g2_array = ISVREF(g2_array,(SI_Long)23L);
    if (EQ(element_type,Qquantity) || EQ(element_type,Qnumber)) {
	store_managed_number_arg = item_or_datum_qm;
	svref_new_value = 
		store_managed_number_function(managed_g2_array_aref(managed_g2_array,
		index_1),store_managed_number_arg);
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(svref_new_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(svref_new_value)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(svref_new_value,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(svref_new_value);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_g2_array,temp) = svref_new_value;
	}
	else {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	return VALUES_1(svref_new_value);
    }
    else if (EQ(element_type,Qfloat) || EQ(element_type,Qinteger) || 
	    EQ(element_type,Qsymbol) || EQ(element_type,Qtruth_value)) {
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(item_or_datum_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(item_or_datum_qm,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(item_or_datum_qm);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_g2_array,temp) = item_or_datum_qm;
	}
	else {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = item_or_datum_qm;
	}
	return VALUES_1(item_or_datum_qm);
    }
    else if (EQ(element_type,Qtext)) {
	old_text_element_qm = managed_g2_array_aref(managed_g2_array,index_1);
	if (old_text_element_qm)
	    reclaim_text(old_text_element_qm);
	value = copy_text_string(item_or_datum_qm);
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_g2_array,temp) = value;
	}
	else {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = value;
	}
	return VALUES_1(value);
    }
    else if (EQ(element_type,Qdatum)) {
	old_datum_element_qm = managed_g2_array_aref(managed_g2_array,index_1);
	if (old_datum_element_qm) {
	    if ( !(FIXNUMP(old_datum_element_qm) || 
		    SYMBOLP(old_datum_element_qm) || 
		    SIMPLE_VECTOR_P(old_datum_element_qm)))
		reclaim_if_evaluation_value_1(old_datum_element_qm);
	}
	if (CONSP(item_or_datum_qm) && EQ(M_CDR(item_or_datum_qm),
		Qtruth_value))
	    value = FIXNUMP(item_or_datum_qm) || item_or_datum_qm && 
		    SYMBOLP(item_or_datum_qm) ? item_or_datum_qm : 
		    copy_evaluation_value_1(item_or_datum_qm);
	else {
	    if (CONSP(item_or_datum_qm)) {
		car_1 = M_CAR(item_or_datum_qm);
		cdr_1 = M_CDR(item_or_datum_qm);
		if (CONSP(cdr_1)) {
		    temp_2 = M_CAR(cdr_1);
		    temp_3 = SYMBOLP(temp_2);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 = temp_3 ? slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		managed_value = M_CAR(item_or_datum_qm);
		if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(item_or_datum_qm))),
			Qtruth_value)) {
		    if (FIXNUM_EQ(managed_value,Truth))
			value = Evaluation_true_value;
		    else if (FIXNUM_EQ(managed_value,Falsity))
			value = Evaluation_false_value;
		    else
			value = eval_cons_1(managed_value,Qtruth_value);
		}
		else
		    value = FIXNUMP(managed_value) || 
			    SYMBOLP(managed_value) ? managed_value : 
			    copy_evaluation_value_1(managed_value);
	    }
	    else {
		gensymed_symbol = item_or_datum_qm;
		temp_3 = FIXNUMP(gensymed_symbol);
		if (temp_3);
		else
		    temp_3 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_3);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_3 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_3);
		    else
			temp_3 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_3);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
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
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_2:
			if ( !TRUEP(marked))
			    goto end_loop_1;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_2);
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
			temp_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		if ( !temp_3)
		    value = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_or_datum_qm) 
			    != (SI_Long)0L ? 
			    copy_wide_string(item_or_datum_qm) : 
			    FIXNUMP(item_or_datum_qm) || 
			    SYMBOLP(item_or_datum_qm) ? item_or_datum_qm : 
			    copy_evaluation_value_1(item_or_datum_qm);
		else
		    value = FIXNUMP(item_or_datum_qm) || item_or_datum_qm 
			    && SYMBOLP(item_or_datum_qm) ? 
			    item_or_datum_qm : 
			    copy_evaluation_value_1(item_or_datum_qm);
	    }
	}
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_g2_array,temp) = value;
	}
	else {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = value;
	}
	return VALUES_1(value);
    }
    else if (EQ(element_type,Qitem_or_datum)) {
	adjusted_index = IFIX(index_1) * (SI_Long)2L;
	if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
	    frame_p_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    frame_p_qm = Nil;
	frame_serial_number_qm = item_or_datum_qm && frame_p_qm && 
		ISVREF(ISVREF(item_or_datum_qm,(SI_Long)1L),(SI_Long)16L) ?
		 ISVREF(item_or_datum_qm,(SI_Long)3L) : Nil;
	old_datum_element_qm = managed_g2_array_aref(managed_g2_array,
		FIX(adjusted_index));
	if (frame_p_qm)
	    new_element = item_or_datum_qm;
	else if (CONSP(item_or_datum_qm) && EQ(M_CDR(item_or_datum_qm),
		Qtruth_value))
	    new_element = FIXNUMP(item_or_datum_qm) || item_or_datum_qm && 
		    SYMBOLP(item_or_datum_qm) ? item_or_datum_qm : 
		    copy_evaluation_value_1(item_or_datum_qm);
	else {
	    if (CONSP(item_or_datum_qm)) {
		car_1 = M_CAR(item_or_datum_qm);
		cdr_1 = M_CDR(item_or_datum_qm);
		if (CONSP(cdr_1)) {
		    temp_2 = M_CAR(cdr_1);
		    temp_3 = SYMBOLP(temp_2);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 = temp_3 ? slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		managed_value = M_CAR(item_or_datum_qm);
		if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(item_or_datum_qm))),
			Qtruth_value)) {
		    if (FIXNUM_EQ(managed_value,Truth))
			new_element = Evaluation_true_value;
		    else if (FIXNUM_EQ(managed_value,Falsity))
			new_element = Evaluation_false_value;
		    else
			new_element = eval_cons_1(managed_value,Qtruth_value);
		}
		else
		    new_element = FIXNUMP(managed_value) || 
			    SYMBOLP(managed_value) ? managed_value : 
			    copy_evaluation_value_1(managed_value);
	    }
	    else {
		gensymed_symbol = item_or_datum_qm;
		temp_3 = FIXNUMP(gensymed_symbol);
		if (temp_3);
		else
		    temp_3 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_3);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_3 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_3);
		    else
			temp_3 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_3);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_4:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_5:
			if ( !TRUEP(marked))
			    goto end_loop_4;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_4 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_4,temp_2);
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
			temp_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		if ( !temp_3)
		    new_element = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_or_datum_qm) 
			    != (SI_Long)0L ? 
			    copy_wide_string(item_or_datum_qm) : 
			    FIXNUMP(item_or_datum_qm) || 
			    SYMBOLP(item_or_datum_qm) ? item_or_datum_qm : 
			    copy_evaluation_value_1(item_or_datum_qm);
		else
		    new_element = FIXNUMP(item_or_datum_qm) || 
			    item_or_datum_qm && SYMBOLP(item_or_datum_qm) ?
			     item_or_datum_qm : 
			    copy_evaluation_value_1(item_or_datum_qm);
	    }
	}
	if (old_datum_element_qm) {
	    if ( !(FIXNUMP(old_datum_element_qm) || 
		    SYMBOLP(old_datum_element_qm) || 
		    SIMPLE_VECTOR_P(old_datum_element_qm)))
		reclaim_if_evaluation_value_1(old_datum_element_qm);
	}
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(adjusted_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = adjusted_index & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_element) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_element)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(new_element,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_element);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = adjusted_index + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_array,temp_1) = new_element;
	}
	else {
	    temp = ISVREF(managed_g2_array,(adjusted_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = adjusted_index & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = new_element;
	}
	temp_1 = adjusted_index + (SI_Long)1L;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = managed_g2_array_aref(managed_g2_array,FIX(temp_1));
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(temp_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(svref_new_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(svref_new_value)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(svref_new_value,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(svref_new_value);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = temp_1 + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_array,temp_1) = svref_new_value;
	}
	else {
	    temp = ISVREF(managed_g2_array,(temp_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	return VALUES_1(svref_new_value);
    }
    else {
	adjusted_index = IFIX(index_1) * (SI_Long)2L;
	if (item_or_datum_qm) {
	    if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    temp_3 = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		    (SI_Long)16L)) : TRUEP(Qnil);
	}
	else
	    temp_3 = TRUEP(Nil);
	frame_serial_number_qm = temp_3 ? ISVREF(item_or_datum_qm,
		(SI_Long)3L) : Nil;
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(adjusted_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = adjusted_index & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(item_or_datum_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(item_or_datum_qm,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(item_or_datum_qm);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = adjusted_index + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_array,temp_1) = item_or_datum_qm;
	}
	else {
	    temp = ISVREF(managed_g2_array,(adjusted_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = adjusted_index & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = item_or_datum_qm;
	}
	temp_1 = adjusted_index + (SI_Long)1L;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = managed_g2_array_aref(managed_g2_array,FIX(temp_1));
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(temp_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(svref_new_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(svref_new_value)) == 
		    (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(svref_new_value,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(svref_new_value);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = temp_1 + IFIX(Managed_array_index_offset);
	    ISVREF(managed_g2_array,temp_1) = svref_new_value;
	}
	else {
	    temp = ISVREF(managed_g2_array,(temp_1 >>  -  - (SI_Long)10L) 
		    + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	return VALUES_1(svref_new_value);
    }
}

/* G2-ARRAY-AREF */
Object g2_array_aref(g2_array,index_1)
    Object g2_array, index_1;
{
    Object managed_g2_array_qm, item_or_value_qm, frame_serial_number_qm, x2;
    Object gensymed_symbol, gensymed_symbol_1, temp_1, datum;
    char temp;

    x_note_fn_call(144,43);
    managed_g2_array_qm = ISVREF(g2_array,(SI_Long)23L);
    if (managed_g2_array_qm) {
	if (g2_list_or_array_element_type_may_contain_item_p(ISVREF(g2_array,
		(SI_Long)21L))) {
	    item_or_value_qm = managed_g2_array_aref(managed_g2_array_qm,
		    FIX(IFIX(index_1) * (SI_Long)2L));
	    frame_serial_number_qm = 
		    managed_g2_array_aref(managed_g2_array_qm,
		    FIX(IFIX(index_1) * (SI_Long)2L + (SI_Long)1L));
	    if (item_or_value_qm) {
		if (SIMPLE_VECTOR_P(item_or_value_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_qm)) 
			> (SI_Long)2L &&  !EQ(ISVREF(item_or_value_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
		if (temp);
		else if ( !(SIMPLE_VECTOR_P(item_or_value_qm) && 
			EQ(ISVREF(item_or_value_qm,(SI_Long)1L),
			Qavailable_frame_vector))) {
		    gensymed_symbol = ISVREF(item_or_value_qm,(SI_Long)3L);
		    gensymed_symbol_1 = frame_serial_number_qm;
		    temp = FIXNUMP(gensymed_symbol) ? 
			    (FIXNUMP(gensymed_symbol_1) ? 
			    FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
			    TRUEP(Nil)) : FIXNUMP(gensymed_symbol_1) ? 
			    TRUEP(Nil) : FIXNUM_EQ(M_CAR(gensymed_symbol),
			    M_CAR(gensymed_symbol_1)) && 
			    FIXNUM_EQ(M_CDR(gensymed_symbol),
			    M_CDR(gensymed_symbol_1));
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    temp_1 = temp ? item_or_value_qm : Nil;
	}
	else {
	    datum = managed_g2_array_aref(managed_g2_array_qm,index_1);
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(datum) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum,
		    (SI_Long)0L)) : datum;
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qframe_denotation;   /* frame-denotation */

/* CONVERT-PERMANENT-ARRAY-STRUCTURE-FOR-SAVING */
Object convert_permanent_array_structure_for_saving(g2_array)
    Object g2_array;
{
    Object sub_class_bit_vector, current_module_being_saved_qm, array_length;
    Object real_array_length, array_element, array_element_to_save_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, x2;
    Object frame_denotation_to_save_qm, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(144,44);
    if (ISVREF(g2_array,(SI_Long)24L) || ISVREF(Current_kb_save,(SI_Long)3L)) {
	sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	temp =  !((temp ?  !TRUEP(zerop(ISVREF(g2_array,(SI_Long)20L))) : 
		TRUEP(Nil)) ?  !TRUEP(g2_array_aref(g2_array,
		FIX((SI_Long)0L))) : TRUEP(Nil));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	current_module_being_saved_qm = ISVREF(Current_kb_save,(SI_Long)37L);
	array_length = ISVREF(g2_array,(SI_Long)20L);
	real_array_length = ISVREF(ISVREF(g2_array,(SI_Long)23L),(SI_Long)1L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(FIXNUM_MIN(array_length,real_array_length));
	array_element = Nil;
	array_element_to_save_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	array_element = g2_array_aref(g2_array,FIX(index_1));
	if (SIMPLE_VECTOR_P(array_element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_element)) > 
		(SI_Long)2L &&  !EQ(ISVREF(array_element,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(array_element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if ((SI_Long)0L != (IFIX(ISVREF(array_element,(SI_Long)4L)) & 
		    (SI_Long)1L) || ISVREF(Current_saving_context,
		    (SI_Long)3L) && (SI_Long)0L != 
		    (IFIX(ISVREF(array_element,(SI_Long)5L)) & 
		    (SI_Long)262144L)) {
		if (EQ(get_module_block_is_in(array_element),
			current_module_being_saved_qm) ||  
			!TRUEP(current_module_being_saved_qm))
		    frame_denotation_to_save_qm = array_element;
		else {
		    frame_denotation_to_save_qm = 
			    copy_for_slot_value(get_primary_name_for_frame_if_any(array_element));
		    if (frame_denotation_to_save_qm);
		    else
			frame_denotation_to_save_qm = item_uuid(array_element);
		}
		if (SIMPLE_VECTOR_P(frame_denotation_to_save_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_denotation_to_save_qm)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(frame_denotation_to_save_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(frame_denotation_to_save_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    array_element_to_save_qm = frame_denotation_to_save_qm;
		else if (frame_denotation_to_save_qm)
		    array_element_to_save_qm = 
			    slot_value_list_2(Qframe_denotation,
			    frame_denotation_to_save_qm);
		else
		    array_element_to_save_qm = Nil;
	    }
	    else
		array_element_to_save_qm = Nil;
	}
	else
	    array_element_to_save_qm = SIMPLE_VECTOR_P(array_element) && 
		    EQ(ISVREF(array_element,(SI_Long)1L),
		    Qavailable_frame_vector) ? Nil : 
		    copy_for_slot_value(array_element);
	temp = TRUEP(array_element_to_save_qm);
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	    temp =  !temp;
	}
	if (temp) {
	    ab_loopvar__2 = slot_value_cons_1(array_element_to_save_qm,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qg2_array;           /* g2-array */

/* CONVERT-SAVED-ARRAY-VALUES-TO-G2-ARRAY-STRUCTURE */
Object convert_saved_array_values_to_g2_array_structure()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_array;
    Object saved_array_values, managed_g2_array, gensymed_symbol;
    Object gensymed_symbol_1, value, ab_loop_list_, value_to_set;
    Object ab_loop_iter_flag_, x2;
    SI_Long index_1, ab_loop_bind_;
    char temp;
    Declare_special(1);

    x_note_fn_call(144,45);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_array = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      saved_array_values = Nil;
      ab_loopvar_ = collect_subclasses(Qg2_array);
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
      g2_array = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      saved_array_values = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
      if (saved_array_values && CONSP(saved_array_values)) {
	  managed_g2_array = allocate_managed_g2_array(3,ISVREF(g2_array,
		  (SI_Long)20L),ISVREF(g2_array,(SI_Long)21L),Nil);
	next_loop_2:
	  gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
	  gensymed_symbol_1 = managed_g2_array;
	  if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol,
		  gensymed_symbol_1))
	      goto end_1;
	  goto next_loop_2;
	end_loop_2:
	end_1:
	  value = Nil;
	  ab_loop_list_ = saved_array_values;
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(ISVREF(g2_array,(SI_Long)20L));
	  value_to_set = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  value = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      index_1 = index_1 + (SI_Long)1L;
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop_3;
	  if (CONSP(value) && EQ(M_CAR(value),Qframe_denotation))
	      value_to_set = find_frame_for_denotation(2,SECOND(value),Qblock);
	  else {
	      if (SIMPLE_VECTOR_P(value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(value,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  value_to_set = value;
	      else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L 
		      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
		      (SI_Long)1L && SIMPLE_VECTOR_P(managed_g2_array) && 
		      EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		      Managed_float_array_unique_marker))
		  value_to_set = value;
	      else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
		      (SI_Long)1L),Qavailable_frame_vector))
		  value_to_set = Nil;
	      else
		  value_to_set = copy_for_slot_value(value);
	  }
	  g2_array_aset(g2_array,FIX(index_1),value_to_set);
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop_3;
	end_loop_3:
	  reclaim_slot_value(saved_array_values);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* G2-ARRAY-AREF-ITEM-OR-EVALUATION-VALUE */
Object g2_array_aref_item_or_evaluation_value(g2_array,index_1)
    Object g2_array, index_1;
{
    Object element_type, temp, gensymed_symbol, item_or_value_qm;
    Object frame_serial_number_qm, thing, gensymed_symbol_2, managed_array;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, value, text_element_qm, value_qm, datum_element_qm;
    SI_Long gensymed_symbol_1;
    char temp_1;
    double aref_new_value;

    x_note_fn_call(144,46);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    if ( !TRUEP(ISVREF(g2_array,(SI_Long)23L)))
	temp = Nil;
    else if (g2_list_or_array_element_type_may_contain_item_p(element_type)) {
	gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
	gensymed_symbol_1 = IFIX(index_1) * (SI_Long)2L;
	item_or_value_qm = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),gensymed_symbol_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
	gensymed_symbol_1 = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
	frame_serial_number_qm = FIXNUM_LE(ISVREF(ISVREF(g2_array,
		(SI_Long)23L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),gensymed_symbol_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & 
		(SI_Long)1023L);
	if ( !TRUEP(item_or_value_qm))
	    temp = Nil;
	else {
	    if (SIMPLE_VECTOR_P(item_or_value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_qm)) > 
		    (SI_Long)2L) {
		temp_1 = EQ(ISVREF(item_or_value_qm,(SI_Long)1L),
			Qavailable_frame_vector);
		if (temp_1);
		else {
		    thing = ISVREF(item_or_value_qm,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    : TRUEP(Qnil);
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1)
		temp = FIXNUMP(item_or_value_qm) || item_or_value_qm && 
			SYMBOLP(item_or_value_qm) ? item_or_value_qm : 
			copy_evaluation_value_1(item_or_value_qm);
	    else if (SIMPLE_VECTOR_P(item_or_value_qm) && 
		    EQ(ISVREF(item_or_value_qm,(SI_Long)1L),
		    Qavailable_frame_vector))
		temp = Nil;
	    else {
		gensymed_symbol = ISVREF(item_or_value_qm,(SI_Long)3L);
		gensymed_symbol_2 = frame_serial_number_qm;
		if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_2) 
			? FIXNUM_EQ(gensymed_symbol,gensymed_symbol_2) : 
			TRUEP(Nil)) : FIXNUMP(gensymed_symbol_2) ? 
			TRUEP(Nil) : FIXNUM_EQ(M_CAR(gensymed_symbol),
			M_CAR(gensymed_symbol_2)) && 
			FIXNUM_EQ(M_CDR(gensymed_symbol),
			M_CDR(gensymed_symbol_2)))
		    temp = item_or_value_qm;
		else
		    temp = Nil;
	    }
	}
    }
    else if (EQ(element_type,Qinteger))
	temp = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(ISVREF(g2_array,
		(SI_Long)23L),IFIX(FIXNUM_ADD(index_1,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
    else if (EQ(element_type,Qfloat)) {
	managed_array = ISVREF(g2_array,(SI_Long)23L);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array,
		(IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(index_1) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (EQ(element_type,Qquantity) || EQ(element_type,Qnumber)) {
	value = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L || 
		INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		(FIXNUMP(value) || value && SYMBOLP(value) ? value : 
		copy_evaluation_value_1(value)) : value;
    }
    else if (EQ(element_type,Qtext)) {
	text_element_qm = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
	temp = text_element_qm ? copy_wide_string(text_element_qm) : Nil;
    }
    else if (EQ(element_type,Qtruth_value)) {
	value_qm = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
	if (value_qm) {
	    if (FIXNUM_EQ(value_qm,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(value_qm,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(value_qm,Qtruth_value);
	}
	else
	    temp = Nil;
    }
    else if (EQ(element_type,Qdatum)) {
	datum_element_qm = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(g2_array,(SI_Long)23L),
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
	temp = datum_element_qm ? (FIXNUMP(datum_element_qm) || 
		datum_element_qm && SYMBOLP(datum_element_qm) ? 
		datum_element_qm : 
		copy_evaluation_value_1(datum_element_qm)) : Nil;
    }
    else
	temp = FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(ISVREF(g2_array,
		(SI_Long)23L),IFIX(FIXNUM_ADD(index_1,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
		(SI_Long)1023L);
    return VALUES_1(temp);
}

/* MUTATE-G2-ARRAY-RECLAIMING-EVALUATION-VALUES */
Object mutate_g2_array_reclaiming_evaluation_values(g2_array,index_1,
	    item_or_datum_qm)
    Object g2_array, index_1, item_or_datum_qm;
{
    x_note_fn_call(144,47);
    return mutate_g2_array(g2_array,index_1,item_or_datum_qm,T,T);
}

/* MUTATE-G2-ARRAY */
Object mutate_g2_array(g2_array,index_1,item_or_datum_qm,
	    reclaim_old_value_qm,reclaim_new_datum_when_necessary_qm)
    Object g2_array, index_1, item_or_datum_qm, reclaim_old_value_qm;
    Object reclaim_new_datum_when_necessary_qm;
{
    Object element_type, x2, gensymed_symbol, frame_serial_number_qm, temp_1;
    Object frame_serial_number_setf_arg, old, new_1, temp_3, managed_array;
    Object old_value_qm, old_text_element_qm, svref_new_value, old_element_qm;
    SI_Long adjusted_index, temp_2;
    char temp;
    double aref_new_value;

    x_note_fn_call(144,48);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(g2_array);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    if (g2_list_or_array_element_type_may_contain_item_p(element_type) &&  
	    !EQ(element_type,Qitem_or_datum)) {
	adjusted_index = IFIX(index_1) * (SI_Long)2L;
	if (item_or_datum_qm) {
	    if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    temp = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		    (SI_Long)16L)) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	frame_serial_number_qm = temp ? ISVREF(item_or_datum_qm,
		(SI_Long)3L) : Nil;
	if (FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = ISVREF(g2_array,(SI_Long)23L);
	    temp_2 = adjusted_index + IFIX(Managed_array_index_offset);
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
	else {
	    temp_1 = ISVREF(ISVREF(g2_array,(SI_Long)23L),(adjusted_index 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = adjusted_index & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
	temp_1 = ISVREF(g2_array,(SI_Long)23L);
	temp_2 = adjusted_index + (SI_Long)1L;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(temp_1,temp_2 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(temp_1,
		(temp_2 >>  -  - (SI_Long)10L) + (SI_Long)2L),temp_2 & 
		(SI_Long)1023L);
	new_1 = frame_serial_number_setf_arg;
	temp_3 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	if (FIXNUM_LE(ISVREF(temp_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
	    temp_2 = temp_2 + IFIX(Managed_array_index_offset);
	    ISVREF(temp_1,temp_2) = temp_3;
	}
	else {
	    temp_1 = ISVREF(temp_1,(temp_2 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_2 = temp_2 & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = temp_3;
	}
    }
    else if (EQ(element_type,Qfloat)) {
	temp_1 = ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) >>  - 
		 - (SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(index_1) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(item_or_datum_qm,(SI_Long)0L);
	DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	if (reclaim_new_datum_when_necessary_qm)
	    reclaim_managed_simple_float_array_of_length_1(item_or_datum_qm);
    }
    else if (EQ(element_type,Qquantity) || EQ(element_type,Qnumber) || 
	    EQ(element_type,Qdatum)) {
	managed_array = ISVREF(g2_array,(SI_Long)23L);
	old_value_qm = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	if (reclaim_old_value_qm && old_value_qm) {
	    if ( !(FIXNUMP(old_value_qm) || SYMBOLP(old_value_qm) || 
		    SIMPLE_VECTOR_P(old_value_qm)))
		reclaim_if_evaluation_value_1(old_value_qm);
	}
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_array,temp_1) = item_or_datum_qm;
	}
	else {
	    temp_1 = ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
    }
    else if (EQ(element_type,Qtext)) {
	managed_array = ISVREF(g2_array,(SI_Long)23L);
	old_text_element_qm = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	if (reclaim_old_value_qm && old_text_element_qm)
	    reclaim_text_string(old_text_element_qm);
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_array,temp_1) = item_or_datum_qm;
	}
	else {
	    temp_1 = ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
    }
    else if (EQ(element_type,Qtruth_value)) {
	if (FIXNUM_LE(ISVREF(ISVREF(g2_array,(SI_Long)23L),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = ISVREF(g2_array,(SI_Long)23L);
	    temp_3 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    svref_new_value = M_CAR(item_or_datum_qm);
	    SVREF(temp_1,temp_3) = svref_new_value;
	}
	else {
	    temp_1 = ISVREF(ISVREF(g2_array,(SI_Long)23L),(IFIX(index_1) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(index_1) & (SI_Long)1023L;
	    temp_3 = M_CAR(item_or_datum_qm);
	    ISVREF(temp_1,temp_2) = temp_3;
	}
	if (reclaim_new_datum_when_necessary_qm) {
	    if ( !(EQ(item_or_datum_qm,Evaluation_true_value) || 
		    EQ(item_or_datum_qm,Evaluation_false_value)))
		reclaim_eval_cons_1(item_or_datum_qm);
	}
    }
    else if (EQ(element_type,Qitem_or_datum)) {
	adjusted_index = IFIX(index_1) * (SI_Long)2L;
	if (item_or_datum_qm) {
	    if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_datum_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    temp = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		    (SI_Long)16L)) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	frame_serial_number_qm = temp ? ISVREF(item_or_datum_qm,
		(SI_Long)3L) : Nil;
	managed_array = ISVREF(g2_array,(SI_Long)23L);
	old_element_qm = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		adjusted_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(adjusted_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),adjusted_index & (SI_Long)1023L);
	if (old_element_qm && reclaim_old_value_qm) {
	    if ( !(FIXNUMP(old_element_qm) || SYMBOLP(old_element_qm) || 
		    SIMPLE_VECTOR_P(old_element_qm)))
		reclaim_if_evaluation_value_1(old_element_qm);
	}
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_2 = adjusted_index + IFIX(Managed_array_index_offset);
	    ISVREF(managed_array,temp_2) = item_or_datum_qm;
	}
	else {
	    temp_1 = ISVREF(managed_array,(adjusted_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = adjusted_index & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
	temp_2 = adjusted_index + (SI_Long)1L;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,temp_2 
		+ IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(temp_2 >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),temp_2 & (SI_Long)1023L);
	new_1 = frame_serial_number_setf_arg;
	temp_3 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_2 = temp_2 + IFIX(Managed_array_index_offset);
	    ISVREF(managed_array,temp_2) = temp_3;
	}
	else {
	    temp_1 = ISVREF(managed_array,(temp_2 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_2 = temp_2 & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = temp_3;
	}
    }
    else {
	managed_array = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
	if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_array,temp_1) = item_or_datum_qm;
	}
	else {
	    temp_1 = ISVREF(managed_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp_1,temp_2) = item_or_datum_qm;
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_initialize_g2_array_elements_p, Qdo_not_initialize_g2_array_elements_p);

/* INITIALIZE-G2-ARRAY */
Object initialize_g2_array(g2_array)
    Object g2_array;
{
    Object length_1, element_type, temp, sub_class_bit_vector;
    Object gensymed_symbol_3, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(144,49);
    length_1 = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)20L));
    element_type = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)21L));
    if (ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L))) {
	temp = ISVREF(g2_array,(SI_Long)23L);
	temp_1 = CONSP(temp);
	if (temp_1);
	else if (ISVREF(g2_array,(SI_Long)24L) && ISVREF(g2_array,
		(SI_Long)23L)) {
	    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	    temp_1 =  !temp_1;
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(zerop(length_1)) ? 
			TRUEP(g2_array_aref(g2_array,FIX((SI_Long)0L))) : 
			TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else
	    temp_1 = TRUEP(Warmbooting_qm);
	if ( !temp_1) {
	    if (ISVREF(g2_array,(SI_Long)23L) && IFIX(ISVREF(g2_array,
		    (SI_Long)20L)) > (SI_Long)0L) {
		if (finish_initialization_of_cloned_g2_array_p(g2_array))
		    finish_initialization_of_cloned_g2_array(g2_array);
		else if ( !TRUEP(Do_not_initialize_g2_array_elements_p)) {
		    if ( 
			    !TRUEP(fill_g2_array_with_initial_values_if_possible(g2_array)))
			fill_g2_array_with_default_values(g2_array);
		}
	    }
	}
    }
    else if (Warmbooting_qm ? TRUEP(zerop(length_1)) :  !(ISVREF(g2_array,
	    (SI_Long)24L) && zerop(length_1))) {
      next_loop:
	gensymed_symbol_3 = ISVREF(g2_array,(SI_Long)23L);
	gensymed_symbol_4 = allocate_managed_g2_array(4,length_1,
		element_type,Nil,Nil);
	if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol_3,
		gensymed_symbol_4))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
	if (ISVREF(g2_array,(SI_Long)23L) && IFIX(ISVREF(g2_array,
		(SI_Long)20L)) > (SI_Long)0L) {
	    if (finish_initialization_of_cloned_g2_array_p(g2_array))
		finish_initialization_of_cloned_g2_array(g2_array);
	    else if ( !TRUEP(Do_not_initialize_g2_array_elements_p)) {
		if ( 
			!TRUEP(fill_g2_array_with_initial_values_if_possible(g2_array)))
		    fill_g2_array_with_default_values(g2_array);
	    }
	}
    }
    barrier();
    return VALUES_1(Nil);
}

/* FINISH-INITIALIZATION-OF-CLONED-G2-ARRAY */
Object finish_initialization_of_cloned_g2_array(g2_array)
    Object g2_array;
{
    Object managed_g2_array_or_cons, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(144,50);
    managed_g2_array_or_cons = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    if (CONSP(managed_g2_array_or_cons)) {
      next_loop:
	gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
	gensymed_symbol_1 = M_CAR(managed_g2_array_or_cons);
	if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
	return reclaim_slot_value_cons_1(managed_g2_array_or_cons);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcloned_managed_array;  /* cloned-managed-array */

/* FINISH-INITIALIZATION-OF-CLONED-G2-ARRAY-P */
Object finish_initialization_of_cloned_g2_array_p(g2_array)
    Object g2_array;
{
    Object managed_g2_array_or_cons;

    x_note_fn_call(144,51);
    managed_g2_array_or_cons = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    if (CONSP(managed_g2_array_or_cons))
	return VALUES_1(EQ(M_CDR(managed_g2_array_or_cons),
		Qcloned_managed_array) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* FILL-G2-ARRAY-WITH-DEFAULT-VALUES */
Object fill_g2_array_with_default_values(g2_array)
    Object g2_array;
{
    Object temp, temp_1;

    x_note_fn_call(144,52);
    temp = ISVREF(g2_array,(SI_Long)23L);
    temp_1 = g2_array_or_list_default_element_value(g2_array);
    return fill_managed_g2_array(temp,temp_1,ISVREF(g2_array,(SI_Long)21L));
}

/* FILL-G2-ARRAY-WITH-INITIAL-VALUES-IF-POSSIBLE */
Object fill_g2_array_with_initial_values_if_possible(g2_array)
    Object g2_array;
{
    Object list_of_initial_values, managed_g2_array, element_type;
    Object default_element_value, initial_value, result_qm, car_1, cdr_1;
    Object temp_1;
    char temp;

    x_note_fn_call(144,53);
    list_of_initial_values = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)22L));
    managed_g2_array = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    element_type = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)21L));
    default_element_value = g2_array_or_list_default_element_value(g2_array);
    initial_value = Nil;
    result_qm = T;
    if ( !TRUEP(list_of_initial_values))
	result_qm = Nil;
    else if (g2_list_or_array_element_type_may_contain_item_p(element_type))
	fill_g2_item_array_or_g2_array_with_initial_values_if_possible(g2_array,
		list_of_initial_values);
    else if ( !TRUEP(CDR(list_of_initial_values))) {
	initial_value = FIRST(list_of_initial_values);
	temp = TRUEP(evaluation_value_of_type_p(initial_value,element_type));
	if (temp);
	else {
	    if (CONSP(initial_value)) {
		car_1 = M_CAR(initial_value);
		cdr_1 = M_CDR(initial_value);
		if (CONSP(cdr_1)) {
		    temp_1 = M_CAR(cdr_1);
		    temp = SYMBOLP(temp_1);
		}
		else
		    temp = TRUEP(Nil);
		temp = temp ? slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = CDR(initial_value);
		temp = CONSP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? EQ(CADR(initial_value),Qtruth_value) : TRUEP(Nil);
	}
	if (temp);
	else
	    temp = EQ(element_type,Qtruth_value) && FIXNUMP(initial_value) 
		    && IFIX(initial_value) <= (SI_Long)1000L ? 
		    IFIX(initial_value) >= (SI_Long)-1000L : TRUEP(Qnil);
	if (temp)
	    fill_managed_g2_array(managed_g2_array,initial_value,element_type);
	else
	    fill_managed_g2_array(managed_g2_array,default_element_value,
		    element_type);
    }
    else {
	temp_1 = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)20L));
	if (FIXNUM_EQ(temp_1,length(list_of_initial_values)))
	    fill_values_into_managed_g2_array(managed_g2_array,
		    list_of_initial_values,element_type,default_element_value);
	else
	    result_qm = Nil;
    }
    return VALUES_1(result_qm);
}

/* FILL-G2-ITEM-ARRAY-OR-G2-ARRAY-WITH-INITIAL-VALUES-IF-POSSIBLE */
Object fill_g2_item_array_or_g2_array_with_initial_values_if_possible(g2_array,
	    initial_value_list)
    Object g2_array, initial_value_list;
{
    x_note_fn_call(144,54);
    if ( !TRUEP(CDR(initial_value_list)))
	return fill_g2_item_array_or_g2_array_with_initial_value(g2_array,
		CAR(initial_value_list));
    else
	return fill_g2_item_array_or_g2_array_with_initial_value_list(g2_array,
		initial_value_list);
}

/* FILL-G2-ITEM-ARRAY-OR-G2-ARRAY-WITH-INITIAL-VALUE */
Object fill_g2_item_array_or_g2_array_with_initial_value(g2_array,
	    item_designation_or_value_qm)
    Object g2_array, item_designation_or_value_qm;
{
    Object managed_g2_array, designation_p_qm, current_computation_frame;
    Object item_or_temporary_constant_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector;
    Object valid_initial_item_or_value_qm, temp_1, result_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char item_or_value_array_p_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(144,55);
    item_or_value_array_p_qm = EQ(ISVREF(g2_array,(SI_Long)21L),
	    Qitem_or_datum);
    managed_g2_array = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    designation_p_qm = designation_p_function(item_designation_or_value_qm);
    current_computation_frame = g2_array;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      item_or_temporary_constant_qm = designation_p_qm ? 
	      evaluate_designation(item_designation_or_value_qm,Nil) : Qnil;
      if ( !item_or_value_array_p_qm) {
	  if (item_or_temporary_constant_qm &&  
		  !(SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
		      {
	      if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(item_or_temporary_constant_qm,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(ISVREF(g2_array,
			  (SI_Long)21L),Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
	  }
	  else
	      temp = TRUEP(Nil);
	  valid_initial_item_or_value_qm = temp ? 
		  item_or_temporary_constant_qm : Nil;
      }
      else if ( !TRUEP(item_or_temporary_constant_qm)) {
	  if (designation_p_qm)
	      valid_initial_item_or_value_qm = Nil;
	  else if ( !TRUEP(item_designation_or_value_qm))
	      valid_initial_item_or_value_qm = Nil;
	  else {
	      if (CONSP(item_designation_or_value_qm)) {
		  temp_1 = M_CAR(item_designation_or_value_qm);
		  temp = CONSP(temp_1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if ((temp ?  
		      !TRUEP(M_CDR(M_CAR(item_designation_or_value_qm))) : 
		      TRUEP(Nil)) ? 
		      EQ(M_CAR(M_CAR(item_designation_or_value_qm)),
		      Symbol_initial_value_marker_symbol) : TRUEP(Nil))
		  valid_initial_item_or_value_qm = 
			  M_CAR(M_CDR(item_designation_or_value_qm));
	      else
		  valid_initial_item_or_value_qm = 
			  item_designation_or_value_qm;
	  }
      }
      else if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
	      EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
	      Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	  valid_initial_item_or_value_qm = item_or_temporary_constant_qm;
      else {
	  if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
		  > (SI_Long)2L &&  
		  !EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
	      gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? x2 : Qnil;
	  }
	  else
	      gensymed_symbol = Nil;
	  if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
	      valid_initial_item_or_value_qm = item_or_temporary_constant_qm;
	  else
	      valid_initial_item_or_value_qm = Nil;
      }
      result_qm = T;
      if ( !TRUEP(valid_initial_item_or_value_qm)) {
	  if (item_or_temporary_constant_qm) {
	      if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		  reclaim_temporary_constant_1(item_or_temporary_constant_qm);
	  }
	  result_qm = Nil;
      }
      else if (item_or_value_array_p_qm) {
	  fill_managed_g2_item_or_value_array(managed_g2_array,
		  valid_initial_item_or_value_qm);
	  if (item_or_temporary_constant_qm) {
	      if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		  reclaim_temporary_constant_1(item_or_temporary_constant_qm);
	  }
      }
      else
	  fill_managed_g2_item_array(managed_g2_array,
		  valid_initial_item_or_value_qm);
      result = VALUES_1(result_qm);
    POP_SPECIAL();
    return result;
}

/* FILL-G2-ITEM-ARRAY-OR-G2-ARRAY-WITH-INITIAL-VALUE-LIST */
Object fill_g2_item_array_or_g2_array_with_initial_value_list(g2_array,
	    item_designation_or_value_list)
    Object g2_array, item_designation_or_value_list;
{
    Object current_computation_frame, result_qm, item_designation_or_value;
    Object ab_loop_list_, designation_p_qm, item_or_temporary_constant_qm;
    Object valid_initial_item_or_value_qm, ab_loop_iter_flag_, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector, temp_1;
    Object temporary_constant;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char item_or_value_array_p_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(144,56);
    current_computation_frame = g2_array;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      item_or_value_array_p_qm = EQ(ISVREF(g2_array,(SI_Long)21L),
	      Qitem_or_datum);
      result_qm = T;
      item_designation_or_value = Nil;
      ab_loop_list_ = item_designation_or_value_list;
      designation_p_qm = Nil;
      item_or_temporary_constant_qm = Nil;
      valid_initial_item_or_value_qm = Nil;
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(ISVREF(g2_array,(SI_Long)20L));
      ab_loop_iter_flag_ = T;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      item_designation_or_value = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      designation_p_qm = designation_p_function(item_designation_or_value);
      item_or_temporary_constant_qm = designation_p_qm ? 
	      evaluate_designation(item_designation_or_value,Nil) : Qnil;
      if ( !item_or_value_array_p_qm) {
	  if (item_or_temporary_constant_qm &&  
		  !(SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
		      {
	      if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(item_or_temporary_constant_qm,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(ISVREF(g2_array,
			  (SI_Long)21L),Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
	  }
	  else
	      temp = TRUEP(Nil);
	  valid_initial_item_or_value_qm = temp ? 
		  item_or_temporary_constant_qm : Nil;
      }
      else if ( !TRUEP(item_or_temporary_constant_qm)) {
	  if (designation_p_qm)
	      valid_initial_item_or_value_qm = Nil;
	  else if ( !TRUEP(item_designation_or_value))
	      valid_initial_item_or_value_qm = Nil;
	  else {
	      if (CONSP(item_designation_or_value)) {
		  temp_1 = CAR(item_designation_or_value);
		  temp = EQUAL(temp_1,Symbol_initial_value_marker);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  valid_initial_item_or_value_qm = 
			  CADR(item_designation_or_value);
	      else
		  valid_initial_item_or_value_qm = item_designation_or_value;
	  }
      }
      else if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
	      EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
	      Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	  temporary_constant = item_or_temporary_constant_qm;
	  item_or_temporary_constant_qm = Nil;
	  valid_initial_item_or_value_qm = 
		  transform_temporary_constant_into_evaluation_value(temporary_constant);
      }
      else {
	  if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
		  > (SI_Long)2L &&  
		  !EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
	      gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? x2 : Qnil;
	  }
	  else
	      gensymed_symbol = Nil;
	  if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
	      valid_initial_item_or_value_qm = item_or_temporary_constant_qm;
	  else
	      valid_initial_item_or_value_qm = Nil;
      }
      if ( !TRUEP(ab_loop_iter_flag_))
	  index_1 = index_1 + (SI_Long)1L;
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if ( !TRUEP(valid_initial_item_or_value_qm))
	  result_qm = Nil;
      if ( !TRUEP(valid_initial_item_or_value_qm))
	  g2_array_aset(g2_array,FIX(index_1),Nil);
      else
	  g2_array_aset(g2_array,FIX(index_1),valid_initial_item_or_value_qm);
      if (item_or_temporary_constant_qm) {
	  if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	      reclaim_temporary_constant_1(item_or_temporary_constant_qm);
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop;
    end_loop:;
      result = VALUES_1(result_qm);
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-G2-ARRAY-AT-POSITION */
Object initialize_g2_array_at_position(g2_array,starting_position)
    Object g2_array, starting_position;
{
    Object initial_values_qm, initial_value_qm, element_type, temp;
    Object designation_p_qm, current_computation_frame;
    Object item_or_temporary_constant_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector;
    Object valid_initial_item_or_value_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char item_or_value_array_p_qm, temp_1;
    Declare_special(1);

    x_note_fn_call(144,57);
    initial_values_qm = ISVREF(g2_array,(SI_Long)22L);
    initial_value_qm = FIRST(initial_values_qm);
    element_type = ISVREF(g2_array,(SI_Long)21L);
    if ( !(ISVREF(g2_array,(SI_Long)23L) && IFIX(ISVREF(g2_array,
	    (SI_Long)20L)) > (SI_Long)0L) ||  !TRUEP(initial_values_qm));
    else if (CDR(initial_values_qm)) {
	temp = FIX((SI_Long)0L);
	if (NUM_EQ(starting_position,temp) && 
		g2_array_length_and_initial_values_match_p(ISVREF(g2_array,
		(SI_Long)20L),initial_values_qm))
	    initialize_g2_array(g2_array);
	else if (g2_array_or_list_default_element_value(g2_array))
	    fill_g2_array_at_position(g2_array,
		    g2_array_or_list_default_element_value(g2_array),
		    starting_position);
    }
    else if ( 
	    !TRUEP(g2_list_or_array_element_type_may_contain_item_p(element_type)))
	fill_g2_array_at_position(g2_array,initial_value_qm,starting_position);
    else {
	item_or_value_array_p_qm = EQ(ISVREF(g2_array,(SI_Long)21L),
		Qitem_or_datum);
	designation_p_qm = designation_p_function(initial_value_qm);
	current_computation_frame = g2_array;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  item_or_temporary_constant_qm = designation_p_qm ? 
		  evaluate_designation(initial_value_qm,Nil) : Qnil;
	  if ( !item_or_value_array_p_qm) {
	      if (item_or_temporary_constant_qm &&  
		      !(SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct))) 
			  {
		  if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
			  > (SI_Long)2L &&  
			  !EQ(ISVREF(item_or_temporary_constant_qm,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
		      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
			      EQ(ISVREF(x2,(SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? x2 : Qnil;
		  }
		  else
		      gensymed_symbol = Nil;
		  if (gensymed_symbol) {
		      gensymed_symbol_1 = 
			      lookup_global_or_kb_specific_property_value(ISVREF(g2_array,
			      (SI_Long)21L),Class_description_gkbprop);
		      if (gensymed_symbol_1) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol_2 = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_3 = (SI_Long)1L;
			      gensymed_symbol_4 = 
				      superior_class_bit_number & (SI_Long)7L;
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
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      valid_initial_item_or_value_qm = temp_1 ? 
		      item_or_temporary_constant_qm : Nil;
	  }
	  else if ( !TRUEP(item_or_temporary_constant_qm)) {
	      if (designation_p_qm)
		  valid_initial_item_or_value_qm = Nil;
	      else if ( !TRUEP(initial_value_qm))
		  valid_initial_item_or_value_qm = Nil;
	      else {
		  if (CONSP(initial_value_qm)) {
		      temp = M_CAR(initial_value_qm);
		      temp_1 = CONSP(temp);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if ((temp_1 ?  !TRUEP(M_CDR(M_CAR(initial_value_qm))) : 
			  TRUEP(Nil)) ? EQ(M_CAR(M_CAR(initial_value_qm)),
			  Symbol_initial_value_marker_symbol) : TRUEP(Nil))
		      valid_initial_item_or_value_qm = 
			      M_CAR(M_CDR(initial_value_qm));
		  else
		      valid_initial_item_or_value_qm = initial_value_qm;
	      }
	  }
	  else if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		  EQ(ISVREF(item_or_temporary_constant_qm,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	      valid_initial_item_or_value_qm = item_or_temporary_constant_qm;
	  else {
	      if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_temporary_constant_qm)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(item_or_temporary_constant_qm,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_temporary_constant_qm,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
		  valid_initial_item_or_value_qm = 
			  item_or_temporary_constant_qm;
	      else
		  valid_initial_item_or_value_qm = Nil;
	  }
	  if ( !TRUEP(valid_initial_item_or_value_qm)) {
	      if (item_or_temporary_constant_qm) {
		  if (SIMPLE_VECTOR_P(item_or_temporary_constant_qm) && 
			  EQ(ISVREF(item_or_temporary_constant_qm,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		      reclaim_temporary_constant_1(item_or_temporary_constant_qm);
	      }
	  }
	  else {
	      fill_g2_array_at_position(g2_array,
		      valid_initial_item_or_value_qm,starting_position);
	      if (item_or_value_array_p_qm) {
		  if (SIMPLE_VECTOR_P(valid_initial_item_or_value_qm) && 
			  EQ(ISVREF(valid_initial_item_or_value_qm,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		      reclaim_temporary_constant_1(valid_initial_item_or_value_qm);
	      }
	  }
	POP_SPECIAL();
    }
    barrier();
    return VALUES_1(Nil);
}

/* FILL-G2-ARRAY-AT-POSITION */
Object fill_g2_array_at_position(g2_array,item_or_value_qm,starting_position)
    Object g2_array, item_or_value_qm, starting_position;
{
    Object temp;

    x_note_fn_call(144,58);
    temp = ACCESS_ONCE(ISVREF(g2_array,(SI_Long)23L));
    return fill_managed_g2_array_at_position(temp,item_or_value_qm,
	    starting_position,ISVREF(g2_array,(SI_Long)21L));
}

/* VALIDATE-AND-FIX-G2-ITEM-ARRAY-ELEMENTS */
Object validate_and_fix_g2_item_array_elements(g2_array,new_element_type)
    Object g2_array, new_element_type;
{
    Object ok_qm, item_qm, x2, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector;
    SI_Long i, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;
    char temp;

    x_note_fn_call(144,59);
    ok_qm = T;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(g2_array,(SI_Long)20L));
    item_qm = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    item_qm = g2_array_aref(g2_array,FIX(i));
    if (item_qm) {
	if (SIMPLE_VECTOR_P(item_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_qm)) > (SI_Long)2L &&  
		!EQ(ISVREF(item_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(item_qm,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(new_element_type,
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	ok_qm = Nil;
	g2_array_aset(g2_array,FIX(i),Nil);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(ok_qm);
}

static Object Qitem_array;         /* item-array */

/* VALIDATE-ALL-ITEM-ARRAYS */
Object validate_all_item_arrays(class_qm,old_class_qm)
    Object class_qm, old_class_qm;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item_array, element_type;
    Object gensymed_symbol;
    char temp;
    Declare_special(1);

    x_note_fn_call(144,60);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item_array = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      element_type = Nil;
      ab_loopvar_ = collect_subclasses(Qitem_array);
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
      item_array = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      element_type = ISVREF(item_array,(SI_Long)21L);
      if ( !EQ(element_type,Qitem)) {
	  temp =  !TRUEP(class_qm) ?  !TRUEP(old_class_qm) : TRUEP(Qnil);
	  if (temp);
	  else if (class_qm) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(element_type,
		      Class_description_gkbprop);
	      temp = gensymed_symbol ? TRUEP(memq_function(class_qm,
		      ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp);
	  else if (old_class_qm) {
	      temp = EQ(element_type,old_class_qm);
	      if (temp);
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(element_type,
			  Class_description_gkbprop);
		  temp = gensymed_symbol ? 
			  TRUEP(memq_function(old_class_qm,
			  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	      }
	  }
	  else
	      temp = TRUEP(Nil);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  validate_and_fix_g2_item_array_elements(item_array,element_type);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* WRITE-G2-ARRAY-DATA-FOR-KB */
Object write_g2_array_data_for_kb(g2_array)
    Object g2_array;
{
    Object array_length, element_type, array, element_type_1, items_possible_p;
    Object managed_g2_array, float_or_quantity_p, element_value_qm, elt_1;
    Object thing, gensymed_symbol, gensymed_symbol_2;
    SI_Long array_length_1, managed_step_size, managed_length, max_inner_index;
    SI_Long outer_index, inner_index, ab_loop_bind_, gensymed_symbol_1;
    SI_Long incff_1_arg;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,61);
    if ((SI_Long)0L != (IFIX(ISVREF(g2_array,(SI_Long)5L)) & (SI_Long)1L)) {
	array_length = ISVREF(g2_array,(SI_Long)20L);
	element_type = g2_list_or_array_element_type(g2_array);
	if (IFIX(array_length) > (SI_Long)0L) {
	    if ( !TRUEP(Left_braket_written_qm)) {
		write_char_for_kb(CHR('['));
		Left_braket_written_qm = T;
	    }
	    write_char_for_kb(CHR('A'));
	    write_fixnum_for_kb(array_length);
	    array = g2_array;
	    element_type_1 = ISVREF(array,(SI_Long)21L);
	    items_possible_p = 
		    g2_list_or_array_element_type_may_contain_item_p(element_type_1);
	    managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	    array_length_1 = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	    managed_length = array_length_1 * managed_step_size;
	    float_or_quantity_p = EQ(element_type_1,Qfloat) ? T : Nil;
	    if (float_or_quantity_p);
	    else
		float_or_quantity_p = EQ(element_type_1,Qquantity) ? T : Nil;
	    max_inner_index = float_or_quantity_p ? (SI_Long)100L : 
		    managed_length;
	    outer_index = (SI_Long)0L;
	    if ( !TRUEP(managed_g2_array))
		return VALUES_1(Nil);
	  next_loop:
	    if ( !(outer_index < managed_length))
		goto end_loop;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_index = (SI_Long)0L;
		ab_loop_bind_ = max_inner_index;
		element_value_qm = Nil;
	      next_loop_1:
		if (inner_index >= ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(element_type_1,Qfloat))
		    element_value_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			    (outer_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),outer_index & (SI_Long)1023L));
		else {
		    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,outer_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,(outer_index >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),outer_index 
			    & (SI_Long)1023L);
		    temp =  !TRUEP(items_possible_p);
		    if (temp);
		    else if (elt_1) {
			if (SIMPLE_VECTOR_P(elt_1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
				(SI_Long)2L) {
			    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp);
			    else {
				thing = ISVREF(elt_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol = ISVREF(elt_1,(SI_Long)3L);
			    gensymed_symbol_1 = outer_index + (SI_Long)1L;
			    gensymed_symbol_2 = 
				    FIXNUM_LE(ISVREF(managed_g2_array,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(managed_g2_array,
				    gensymed_symbol_1 + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(managed_g2_array,
				    (gensymed_symbol_1 >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol_1 & (SI_Long)1023L);
			    temp = (FIXNUMP(gensymed_symbol) ? 
				    (FIXNUMP(gensymed_symbol_2) ? 
				    FIXNUM_EQ(gensymed_symbol,
				    gensymed_symbol_2) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_2) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol),
				    M_CAR(gensymed_symbol_2)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol),
				    M_CDR(gensymed_symbol_2))) ? 
				    (SI_Long)0L != (IFIX(ISVREF(elt_1,
				    (SI_Long)5L)) & (SI_Long)1L) || 
				    ISVREF(array,(SI_Long)24L) : TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    element_value_qm = temp ? elt_1 : Nil;
		}
		write_g2_list_or_array_element_for_kb(element_value_qm,
			element_type);
		incff_1_arg = managed_step_size;
		outer_index = outer_index + incff_1_arg;
		if ( !(outer_index < managed_length))
		    goto end_loop_1;
		inner_index = inner_index + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* READ-ARRAY-DATA */
Object read_array_data(g2_array)
    Object g2_array;
{
    Object array_length, managed_g2_array, gensymed_symbol, gensymed_symbol_1;
    Object element_type, items_present_p, real_index, index_1, element;
    Object index_2, value, temp, x2, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value, temp_3;
    SI_Long temp_1, temp_4;
    char temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,62);
    array_length = read_element_for_kb(Nil);
    managed_g2_array = Nil;
    managed_g2_array = allocate_managed_g2_array(4,ISVREF(g2_array,
	    (SI_Long)20L),ISVREF(g2_array,(SI_Long)21L),Nil,Nil);
    reclaim_slot_value(ISVREF(g2_array,(SI_Long)23L));
  next_loop:
    gensymed_symbol = ISVREF(g2_array,(SI_Long)23L);
    gensymed_symbol_1 = managed_g2_array;
    if (CAS_SVREF(g2_array,(SI_Long)23L,gensymed_symbol,gensymed_symbol_1))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
    element_type = g2_list_or_array_element_type(g2_array);
    items_present_p = 
	    g2_list_or_array_element_type_may_contain_item_p(element_type);
    real_index = Nil;
    index_1 = FIX((SI_Long)0L);
  next_loop_1:
    if ( !FIXNUM_LT(index_1,array_length))
	goto end_loop_1;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	element = Nil;
      next_loop_2:
	element = read_g2_list_or_array_element_for_kb(element_type,T);
	if (items_present_p) {
	    real_index = FIX(IFIX(index_1) << (SI_Long)1L);
	    index_2 = real_index;
	    value = SIMPLE_VECTOR_P(element) && EQ(ISVREF(element,
		    (SI_Long)1L),Qavailable_frame_vector) ? Nil : element;
	    if (SIMPLE_VECTOR_P(managed_g2_array) && 
		    EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		    Managed_float_array_unique_marker)) {
		temp = ISVREF(managed_g2_array,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_1 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		else
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		SVREF(managed_g2_array,temp) = value;
	    }
	    else {
		temp = ISVREF(managed_g2_array,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_1 = IFIX(index_2) & (SI_Long)1023L;
		ISVREF(temp,temp_1) = value;
	    }
	    if (SIMPLE_VECTOR_P(element) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(element,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(element,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		temp = FIXNUM_ADD1(real_index);
		frame_serial_number_setf_arg = ISVREF(element,(SI_Long)3L);
		old = managed_g2_array_aref(managed_g2_array,temp);
		new_1 = frame_serial_number_setf_arg;
		svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
			(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
			frame_serial_number_setf_helper_1(old,new_1);
		if (SIMPLE_VECTOR_P(managed_g2_array) && 
			EQ(ISVREF(managed_g2_array,(SI_Long)0L),
			Managed_float_array_unique_marker)) {
		    temp_3 = ISVREF(managed_g2_array,(IFIX(temp) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_1 = IFIX(temp) & (SI_Long)1023L;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(svref_new_value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(svref_new_value)) 
			    == (SI_Long)1L)
			aref_new_value = DFLOAT_ISAREF_1(svref_new_value,
				(SI_Long)0L);
		    else
			aref_new_value = 
				DOUBLE_FLOAT_TO_DOUBLE(svref_new_value);
		    DFLOAT_ISASET_1(temp_3,temp_1,aref_new_value);
		}
		else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp = FIXNUM_ADD(temp,Managed_array_index_offset);
		    SVREF(managed_g2_array,temp) = svref_new_value;
		}
		else {
		    temp_3 = ISVREF(managed_g2_array,(IFIX(temp) >>  -  - 
			    (SI_Long)10L) + (SI_Long)2L);
		    temp_1 = IFIX(temp) & (SI_Long)1023L;
		    ISVREF(temp_3,temp_1) = svref_new_value;
		}
	    }
	}
	else if (EQ(element_type,Qfloat)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(element,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	    reclaim_managed_simple_float_array_of_length_1(element);
	}
	else if (SIMPLE_VECTOR_P(managed_g2_array) && 
		EQ(ISVREF(managed_g2_array,(SI_Long)0L),
		Managed_float_array_unique_marker)) {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L)
		aref_new_value = DFLOAT_ISAREF_1(element,(SI_Long)0L);
	    else
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element);
	    DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	}
	else if (FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(managed_g2_array,temp) = element;
	}
	else {
	    temp = ISVREF(managed_g2_array,(IFIX(index_1) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = element;
	}
	index_1 = FIXNUM_ADD1(index_1);
	if (FIXNUM_LT(index_1,array_length)) {
	    temp_4 = IFIX(index_1) % (SI_Long)500L;
	    temp_2 =  !(temp_4 == (SI_Long)0L);
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(managed_g2_array);
}

static Object Qg2_array_length;    /* g2-array-length */

/* CONVERT-G2-LIST-TO-G2-ARRAY */
Object convert_g2_list_to_g2_array(g2_list)
    Object g2_list;
{
    Object g2_list_element_type, g2_list_length_1, new_g2_array_class;
    Object new_g2_array;

    x_note_fn_call(144,63);
    g2_list_element_type = ISVREF(g2_list,(SI_Long)21L);
    g2_list_length_1 = g2_list_length(g2_list);
    new_g2_array_class = 
	    g2_list_or_array_class_for_element_type(g2_list_element_type,T);
    new_g2_array = make_transient_item(new_g2_array_class);
    change_slot_value(3,new_g2_array,Qg2_array_length,g2_list_length_1);
    move_g2_list_elements_to_g2_array(g2_list,new_g2_array,Nil);
    return VALUES_1(new_g2_array);
}

/* MOVE-G2-LIST-ELEMENTS-TO-G2-ARRAY */
Object move_g2_list_elements_to_g2_array(g2_list,g2_array,
	    count_of_elements_to_move_qm)
    Object g2_list, g2_array, count_of_elements_to_move_qm;
{
    Object g2_list_length_before_move, g2_array_length, item_or_value;
    SI_Long index_1;

    x_note_fn_call(144,64);
    g2_list_length_before_move = g2_list_length(g2_list);
    g2_array_length = ISVREF(g2_array,(SI_Long)20L);
    item_or_value = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if ( !(( !TRUEP(count_of_elements_to_move_qm) || index_1 < 
	    IFIX(count_of_elements_to_move_qm)) && index_1 < 
	    IFIX(g2_list_length_before_move) && index_1 < 
	    IFIX(g2_array_length)))
	goto end_loop;
    item_or_value = pop_g2_list(g2_list);
    mutate_g2_array(g2_array,FIX(index_1),item_or_value,T,T);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* MOVE-G2-ARRAY-ELEMENTS-TO-G2-LIST */
Object move_g2_array_elements_to_g2_list(g2_array,g2_list)
    Object g2_array, g2_list;
{
    Object sub_class_bit_vector, truth_value_array_p, float_value_array_p;
    Object array, element_type, items_possible_p, managed_g2_array;
    Object float_or_quantity_p, value, elt_1, thing, gensymed_symbol_3;
    Object gensymed_symbol_4, temp_1, amf_available_array_cons_qm, amf_array;
    Object temp_2, temp_3, amf_result, new_float;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, array_length;
    SI_Long managed_step_size, managed_length, max_inner_index, outer_index;
    SI_Long inner_index, ab_loop_bind_, incff_1_arg;
    char temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,65);
    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Truth_value_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	truth_value_array_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	truth_value_array_p = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Float_array_class_description,
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
	float_value_array_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	float_value_array_p = Nil;
    array = g2_array;
    element_type = ISVREF(array,(SI_Long)21L);
    items_possible_p = 
	    g2_list_or_array_element_type_may_contain_item_p(element_type);
    managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
    array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
    managed_length = array_length * managed_step_size;
    float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
    if (float_or_quantity_p);
    else
	float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
    max_inner_index = float_or_quantity_p ? (SI_Long)100L : managed_length;
    outer_index = (SI_Long)0L;
    if ( !TRUEP(managed_g2_array))
	goto end_1;
  next_loop:
    if ( !(outer_index < managed_length))
	goto end_loop;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	inner_index = (SI_Long)0L;
	ab_loop_bind_ = max_inner_index;
	value = Nil;
      next_loop_1:
	if (inner_index >= ab_loop_bind_)
	    goto end_loop_1;
	if (EQ(element_type,Qfloat))
	    value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
		    (outer_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    outer_index & (SI_Long)1023L));
	else {
	    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(managed_g2_array,
		    outer_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_g2_array,(outer_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),outer_index & (SI_Long)1023L);
	    temp =  !TRUEP(items_possible_p);
	    if (temp);
	    else if (elt_1) {
		if (SIMPLE_VECTOR_P(elt_1) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > (SI_Long)2L) {
		    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
			    Qavailable_frame_vector);
		    if (temp);
		    else {
			thing = ISVREF(elt_1,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				: TRUEP(Qnil);
		    }
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
		if (temp);
		else {
		    gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
		    gensymed_symbol = outer_index + (SI_Long)1L;
		    gensymed_symbol_4 = FIXNUM_LE(ISVREF(managed_g2_array,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,gensymed_symbol + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
		    temp = (FIXNUMP(gensymed_symbol_3) ? 
			    (FIXNUMP(gensymed_symbol_4) ? 
			    FIXNUM_EQ(gensymed_symbol_3,gensymed_symbol_4) 
			    : TRUEP(Nil)) : FIXNUMP(gensymed_symbol_4) ? 
			    TRUEP(Nil) : 
			    FIXNUM_EQ(M_CAR(gensymed_symbol_3),
			    M_CAR(gensymed_symbol_4)) && 
			    FIXNUM_EQ(M_CDR(gensymed_symbol_3),
			    M_CDR(gensymed_symbol_4))) ? (SI_Long)0L != 
			    (IFIX(ISVREF(elt_1,(SI_Long)5L)) & 
			    (SI_Long)1L) || ISVREF(array,(SI_Long)24L) : 
			    TRUEP(Nil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    value = temp ? elt_1 : Nil;
	}
	if (value) {
	    if (truth_value_array_p) {
		if (FIXNUM_EQ(value,Truth))
		    temp_1 = Evaluation_true_value;
		else if (FIXNUM_EQ(value,Falsity))
		    temp_1 = Evaluation_false_value;
		else
		    temp_1 = eval_cons_1(value,Qtruth_value);
	    }
	    else if (float_value_array_p) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		temp_1 = new_float;
	    }
	    else
		temp_1 = value;
	    g2_list_insert_at_end(2,temp_1,g2_list);
	}
	incff_1_arg = managed_step_size;
	outer_index = outer_index + incff_1_arg;
	if ( !(outer_index < managed_length))
	    goto end_loop_1;
	inner_index = inner_index + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    goto next_loop;
  end_loop:
    goto end_1;
  end_1:;
    clear_managed_values_from_managed_g2_array(ISVREF(g2_array,
	    (SI_Long)23L),ISVREF(g2_array,(SI_Long)21L));
    change_slot_value(3,g2_array,Qg2_array_length,FIX((SI_Long)0L));
    return VALUES_1(Nil);
}

Object Quicksort_verbose_p = UNBOUND;

Object Insertion_sort_array_size = UNBOUND;

/* INTEGER-INSERTION-SORT */
Object integer_insertion_sort(key_array,data_array_1,data_array_2_qm,
	    left_init,right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, element_b, element_b_2_qm, svref_arg_1, svref_new_value;
    SI_Long left, right, j, ab_loop_bind_, element_a, i, ab_loop_bind__1, temp;

    x_note_fn_call(144,66);
    left = IFIX(left_init);
    right = IFIX(right_init);
    a = ISVREF(key_array,(SI_Long)23L);
    b = data_array_1;
    j = left + (SI_Long)1L;
    ab_loop_bind_ = right;
    element_a = (SI_Long)0L;
    element_b = Nil;
    element_b_2_qm = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    element_a = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(a,j + 
	    IFIX(Managed_array_index_offset))) : IFIX(ISVREF(ISVREF(a,(j 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
    element_b = g2_array_aref_item_or_evaluation_value(b,FIX(j));
    element_b_2_qm = data_array_2_qm ? 
	    g2_array_aref_item_or_evaluation_value(data_array_2_qm,FIX(j)) 
	    : Nil;
    i = j - (SI_Long)1L;
    ab_loop_bind__1 = left;
  next_loop_1:
    if (i < ab_loop_bind__1)
	goto end_loop_1;
    if ((FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    IFIX(ISVREF(a,i + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(a,(i >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    i & (SI_Long)1023L))) >= element_a) {
	temp = i + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp = temp + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp) = FIX(element_a);
	}
	else {
	    svref_arg_1 = ISVREF(a,(temp >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp = temp & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp) = FIX(element_a);
	}
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + 
		(SI_Long)1L),element_b);
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(i + (SI_Long)1L),element_b_2_qm);
	goto end_1;
    }
    temp = i + (SI_Long)1L;
    svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp = temp + IFIX(Managed_array_index_offset);
	ISVREF(a,temp) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(a,(temp >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp = temp & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp) = svref_new_value;
    }
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + (SI_Long)1L),
	    g2_array_aref_item_or_evaluation_value(b,FIX(i)));
    if (data_array_2_qm)
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,FIX(i 
		+ (SI_Long)1L),
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(i)));
    i = i - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp = left + IFIX(Managed_array_index_offset);
	ISVREF(a,temp) = FIX(element_a);
    }
    else {
	svref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp = left & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp) = FIX(element_a);
    }
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),element_b);
    if (data_array_2_qm)
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(left),element_b_2_qm);
  end_1:;
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FLOAT-INSERTION-SORT */
Object float_insertion_sort(key_array,data_array_1,data_array_2_qm,
	    left_init,right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, element_b, element_b_2_qm, aref_arg_1;
    SI_Long left, right, j, ab_loop_bind_, i, ab_loop_bind__1, temp;
    double element_a, arg, arg_1, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,67);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = ISVREF(key_array,(SI_Long)23L);
	b = data_array_1;
	j = left + (SI_Long)1L;
	ab_loop_bind_ = right;
	element_a = 0.0;
	element_b = Nil;
	element_b_2_qm = Nil;
      next_loop:
	if (j > ab_loop_bind_)
	    goto end_loop;
	element_a = DFLOAT_ISAREF_1(ISVREF(a,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),j & (SI_Long)1023L);
	element_b = g2_array_aref_item_or_evaluation_value(b,FIX(j));
	element_b_2_qm = data_array_2_qm ? 
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(j)) : Nil;
	i = j - (SI_Long)1L;
	ab_loop_bind__1 = left;
      next_loop_1:
	if (i < ab_loop_bind__1)
	    goto end_loop_1;
	arg = DFLOAT_ISAREF_1(ISVREF(a,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	arg_1 = element_a;
	if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = i + (SI_Long)1L;
	    aref_arg_1 = ISVREF(a,(temp >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp = temp & (SI_Long)1023L;
	    DFLOAT_ISASET_1(aref_arg_1,temp,element_a);
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + 
		    (SI_Long)1L),element_b);
	    if (data_array_2_qm)
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(i + (SI_Long)1L),element_b_2_qm);
	    goto end_1;
	}
	temp = i + (SI_Long)1L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	aref_arg_1 = ISVREF(a,(temp >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp = temp & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp,aref_new_value);
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + 
		(SI_Long)1L),g2_array_aref_item_or_evaluation_value(b,FIX(i)));
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(i + (SI_Long)1L),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(i)));
	i = i - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	aref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp = left & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp,element_a);
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),element_b);
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left),element_b_2_qm);
      end_1:;
	j = j + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* QUANTITY-INSERTION-SORT */
Object quantity_insertion_sort(key_array,data_array_1,data_array_2_qm,
	    left_init,right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, element_a, element_b, element_b_2_qm, value, temp, array;
    Object old_value, temp_1, amf_available_array_cons_qm, amf_array, temp_2;
    Object amf_result, new_float, temp_3;
    SI_Long left, right, j, ab_loop_bind_, i, ab_loop_bind__1, index_1;
    SI_Long svref_arg_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,68);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = ISVREF(key_array,(SI_Long)23L);
	b = data_array_1;
	j = left + (SI_Long)1L;
	ab_loop_bind_ = right;
	element_a = FIX((SI_Long)0L);
	element_b = Nil;
	element_b_2_qm = Nil;
      next_loop:
	if (j > ab_loop_bind_)
	    goto end_loop;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,j + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(j >>  
		-  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	element_a = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	element_b = g2_array_aref_item_or_evaluation_value(b,FIX(j));
	element_b_2_qm = data_array_2_qm ? 
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(j)) : Nil;
	i = j - (SI_Long)1L;
	ab_loop_bind__1 = left;
      next_loop_1:
	if (i < ab_loop_bind__1)
	    goto end_loop_1;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,i + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_GE(temp,element_a)) {
	    array = a;
	    index_1 = i + (SI_Long)1L;
	    value = element_a;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + 
		    (SI_Long)1L),element_b);
	    if (data_array_2_qm)
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(i + (SI_Long)1L),element_b_2_qm);
	    goto end_1;
	}
	array = a;
	index_1 = i + (SI_Long)1L;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,i + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(i + 
		(SI_Long)1L),g2_array_aref_item_or_evaluation_value(b,FIX(i)));
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(i + (SI_Long)1L),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(i)));
	i = i - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	array = a;
	index_1 = left;
	value = element_a;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),element_b);
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left),element_b_2_qm);
      end_1:;
	j = j + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* INSERTION-SORT-PER-ARRAY-TYPE */
Object insertion_sort_per_array_type(key_array,data_array_1,
	    data_array_2_qm,left_init,right_init,array_type)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
    Object array_type;
{
    SI_Long left, right;

    x_note_fn_call(144,69);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (EQ(array_type,Qinteger))
	return integer_insertion_sort(key_array,data_array_1,
		data_array_2_qm,FIX(left),FIX(right));
    else if (EQ(array_type,Qfloat))
	return float_insertion_sort(key_array,data_array_1,data_array_2_qm,
		FIX(left),FIX(right));
    else
	return quantity_insertion_sort(key_array,data_array_1,
		data_array_2_qm,FIX(left),FIX(right));
}

/* INTEGER-PARTITION */
Object integer_partition(key_array,data_array_1,data_array_2_qm,left_init,
	    right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, pivot_b, pivot_b_2_qm, temp, svref_new_value, svref_arg_1;
    SI_Long left, right, k, pivot, left_index, right_index, temp_1, i;

    x_note_fn_call(144,70);
    left = IFIX(left_init);
    right = IFIX(right_init);
    a = ISVREF(key_array,(SI_Long)23L);
    b = data_array_1;
    k = (SI_Long)0L;
    pivot = (SI_Long)0L;
    pivot_b = Nil;
    pivot_b_2_qm = Nil;
    left_index = left + (SI_Long)1L;
    right_index = right;
    k = IFIX(chestnut_floorf_function(FIX(left + right),FIX((SI_Long)2L)));
    temp = FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(a,k + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(a,(k >>  -  - (SI_Long)10L) + (SI_Long)2L),k & 
	    (SI_Long)1023L);
    svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,left_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
	    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),left_index & 
	    (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = k + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(a,(k >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = k & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = left_index + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = temp;
    }
    else {
	svref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = left_index & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = temp;
    }
    temp = g2_array_aref_item_or_evaluation_value(b,FIX(k));
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(k),
	    g2_array_aref_item_or_evaluation_value(b,FIX(left_index)));
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),temp);
    if (data_array_2_qm) {
	temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,FIX(k));
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(k),
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(left_index)));
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(left_index),temp);
    }
    if (FIXNUM_LT(FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,left + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left >>  
	    -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L),
	    FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(a,right + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(a,(right >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    right & (SI_Long)1023L))) {
	temp = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
	svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(right 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = left + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = left & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = right + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = temp;
	}
	else {
	    svref_arg_1 = ISVREF(a,(right >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = right & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = temp;
	}
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(left));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),
		g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right),temp);
	}
    }
    if (FIXNUM_LT(FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,left_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
	    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),left_index & 
	    (SI_Long)1023L),FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,right + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(right >>  
	    -  - (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L))) {
	temp = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(right 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = left_index + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = left_index & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = right + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = temp;
	}
	else {
	    svref_arg_1 = ISVREF(a,(right >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = right & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = temp;
	}
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right),temp);
	}
    }
    if (FIXNUM_LT(FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,left + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left >>  
	    -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L),
	    FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(a,left_index + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),left_index & (SI_Long)1023L))) {
	temp = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = left_index + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = svref_new_value;
	}
	else {
	    svref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = left_index & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = left + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = temp;
	}
	else {
	    svref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = left & (SI_Long)1023L;
	    ISVREF(svref_arg_1,temp_1) = temp;
	}
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		g2_array_aref_item_or_evaluation_value(b,FIX(left)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left),temp);
	}
    }
    pivot = FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    IFIX(ISVREF(a,left_index + IFIX(Managed_array_index_offset))) :
	     IFIX(ISVREF(ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),left_index & (SI_Long)1023L));
    pivot_b = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
    pivot_b_2_qm = data_array_2_qm ? 
	    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
	    FIX(left_index)) : Nil;
  next_loop:
    i = left_index + (SI_Long)1L;
  next_loop_1:
    if ((FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    IFIX(ISVREF(a,i + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(a,(i >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    i & (SI_Long)1023L))) <= pivot) {
	left_index = i;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop:
    left_index = IFIX(Qnil);
  end_1:;
    i = right_index - (SI_Long)1L;
  next_loop_2:
    if ((FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    IFIX(ISVREF(a,i + IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(a,(i >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    i & (SI_Long)1023L))) >= pivot) {
	right_index = i;
	goto end_2;
    }
    i = i - (SI_Long)1L;
    goto next_loop_2;
  end_loop_1:
    right_index = IFIX(Qnil);
  end_2:;
    if (right_index < left_index)
	goto end_3;
    temp = FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(a,left_index + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),left_index & (SI_Long)1023L);
    svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,right_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
	    (right_index >>  -  - (SI_Long)10L) + (SI_Long)2L),right_index 
	    & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = left_index + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = left_index & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = right_index + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = temp;
    }
    else {
	svref_arg_1 = ISVREF(a,(right_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = right_index & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = temp;
    }
    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
	    g2_array_aref_item_or_evaluation_value(b,FIX(right_index)));
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),temp);
    if (data_array_2_qm) {
	temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(left_index));
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(left_index),
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(right_index)));
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(right_index),temp);
    }
    goto next_loop;
  end_loop_2:
  end_3:
    temp_1 = left + (SI_Long)1L;
    svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,right_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
	    (right_index >>  -  - (SI_Long)10L) + (SI_Long)2L),right_index 
	    & (SI_Long)1023L);
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = temp_1 + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = svref_new_value;
    }
    else {
	svref_arg_1 = ISVREF(a,(temp_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = temp_1 & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = svref_new_value;
    }
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left + (SI_Long)1L),
	    g2_array_aref_item_or_evaluation_value(b,FIX(right_index)));
    if (data_array_2_qm)
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(left + (SI_Long)1L),
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(right_index)));
    if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = right_index + IFIX(Managed_array_index_offset);
	ISVREF(a,temp_1) = FIX(pivot);
    }
    else {
	svref_arg_1 = ISVREF(a,(right_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = right_index & (SI_Long)1023L;
	ISVREF(svref_arg_1,temp_1) = FIX(pivot);
    }
    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),pivot_b);
    if (data_array_2_qm)
	mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		FIX(right_index),pivot_b_2_qm);
    return VALUES_1(FIX(right_index));
}

/* FLOAT-PARTITION */
Object float_partition(key_array,data_array_1,data_array_2_qm,left_init,
	    right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, pivot_b, pivot_b_2_qm, temp, aref_arg_1;
    SI_Long left, right, k, left_index, right_index, temp_1, i;
    double pivot, aref_new_value, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,71);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = ISVREF(key_array,(SI_Long)23L);
	b = data_array_1;
	k = (SI_Long)0L;
	pivot = 0.0;
	pivot_b = Nil;
	pivot_b_2_qm = Nil;
	left_index = left + (SI_Long)1L;
	right_index = right;
	k = IFIX(chestnut_floorf_function(FIX(left + right),FIX((SI_Long)2L)));
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(a,(k >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L));
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(left_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),left_index & (SI_Long)1023L);
	aref_arg_1 = ISVREF(a,(k >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = k & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	aref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = left_index & (SI_Long)1023L;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(k));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(k),
		g2_array_aref_item_or_evaluation_value(b,FIX(left_index)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(k));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(k),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),temp);
	}
	arg = DFLOAT_ISAREF_1(ISVREF(a,(left >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),left & (SI_Long)1023L);
	arg_1 = DFLOAT_ISAREF_1(ISVREF(a,(right >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),right & (SI_Long)1023L);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(a,(left 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),left & 
		    (SI_Long)1023L));
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(right >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	    aref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = left & (SI_Long)1023L;
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    aref_arg_1 = ISVREF(a,(right >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = right & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),
		    g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(right)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(right),temp);
	    }
	}
	arg = DFLOAT_ISAREF_1(ISVREF(a,(left_index >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),left_index & (SI_Long)1023L);
	arg_1 = DFLOAT_ISAREF_1(ISVREF(a,(right >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),right & (SI_Long)1023L);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(a,
		    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    left_index & (SI_Long)1023L));
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(right >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	    aref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = left_index & (SI_Long)1023L;
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    aref_arg_1 = ISVREF(a,(right >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = right & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left_index));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left_index),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(right)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(right),temp);
	    }
	}
	arg = DFLOAT_ISAREF_1(ISVREF(a,(left >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),left & (SI_Long)1023L);
	arg_1 = DFLOAT_ISAREF_1(ISVREF(a,(left_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),left_index & (SI_Long)1023L);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(a,
		    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    left_index & (SI_Long)1023L));
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(left >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
	    aref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = left_index & (SI_Long)1023L;
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    aref_arg_1 = ISVREF(a,(left >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = left & (SI_Long)1023L;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(b,FIX(left)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left_index));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left_index),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left),temp);
	    }
	}
	pivot = DFLOAT_ISAREF_1(ISVREF(a,(left_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),left_index & (SI_Long)1023L);
	pivot_b = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	pivot_b_2_qm = data_array_2_qm ? 
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(left_index)) : Nil;
      next_loop:
	i = left_index + (SI_Long)1L;
      next_loop_1:
	arg = DFLOAT_ISAREF_1(ISVREF(a,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	arg_1 = pivot;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    left_index = i;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:
	left_index = IFIX(Qnil);
      end_1:;
	i = right_index - (SI_Long)1L;
      next_loop_2:
	arg = DFLOAT_ISAREF_1(ISVREF(a,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),i & (SI_Long)1023L);
	arg_1 = pivot;
	if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    right_index = i;
	    goto end_2;
	}
	i = i - (SI_Long)1L;
	goto next_loop_2;
      end_loop_1:
	right_index = IFIX(Qnil);
      end_2:;
	if (right_index < left_index)
	    goto end_3;
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(a,(left_index 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),left_index & 
		(SI_Long)1023L));
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(right_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),right_index & (SI_Long)1023L);
	aref_arg_1 = ISVREF(a,(left_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = left_index & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	aref_arg_1 = ISVREF(a,(right_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = right_index & (SI_Long)1023L;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		g2_array_aref_item_or_evaluation_value(b,FIX(right_index)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right_index)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right_index),temp);
	}
	goto next_loop;
      end_loop_2:
      end_3:
	temp_1 = left + (SI_Long)1L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(a,(right_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),right_index & (SI_Long)1023L);
	aref_arg_1 = ISVREF(a,(temp_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = temp_1 & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left + 
		(SI_Long)1L),g2_array_aref_item_or_evaluation_value(b,
		FIX(right_index)));
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left + (SI_Long)1L),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right_index)));
	aref_arg_1 = ISVREF(a,(right_index >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_1 = right_index & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,temp_1,pivot);
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),
		pivot_b);
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right_index),pivot_b_2_qm);
	result = VALUES_1(FIX(right_index));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* QUANTITY-PARTITION */
Object quantity_partition(key_array,data_array_1,data_array_2_qm,left_init,
	    right_init)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
{
    Object a, b, pivot, pivot_b, pivot_b_2_qm, value, temp, array, old_value;
    Object temp_1, amf_available_array_cons_qm, amf_array, temp_2, amf_result;
    Object new_float, temp_3, temp_4, temp_5;
    SI_Long left, right, k, left_index, right_index, index_1, svref_arg_2, i;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,72);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = ISVREF(key_array,(SI_Long)23L);
	b = data_array_1;
	k = (SI_Long)0L;
	pivot = FIX((SI_Long)0L);
	pivot_b = Nil;
	pivot_b_2_qm = Nil;
	left_index = left + (SI_Long)1L;
	right_index = right;
	k = IFIX(chestnut_floorf_function(FIX(left + right),FIX((SI_Long)2L)));
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,k + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(k >>  
		-  - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	array = a;
	index_1 = k;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	array = a;
	index_1 = left_index;
	value = temp;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(k));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(k),
		g2_array_aref_item_or_evaluation_value(b,FIX(left_index)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(k));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(k),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),temp);
	}
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
	temp_4 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(right 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	temp_5 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_LT(temp_4,temp_5)) {
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,left + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (left >>  -  - (SI_Long)10L) + (SI_Long)2L),left & 
		    (SI_Long)1023L);
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    array = a;
	    index_1 = left;
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,right + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (right >>  -  - (SI_Long)10L) + (SI_Long)2L),right & 
		    (SI_Long)1023L);
	    value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    array = a;
	    index_1 = right;
	    value = temp;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),
		    g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(right)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(right),temp);
	    }
	}
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	temp_4 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(right 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),right & (SI_Long)1023L);
	temp_5 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_LT(temp_4,temp_5)) {
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    left_index & (SI_Long)1023L);
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    array = a;
	    index_1 = left_index;
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,right + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (right >>  -  - (SI_Long)10L) + (SI_Long)2L),right & 
		    (SI_Long)1023L);
	    value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    array = a;
	    index_1 = right;
	    value = temp;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(b,FIX(right)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(right),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left_index));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left_index),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(right)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(right),temp);
	    }
	}
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(left 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),left & (SI_Long)1023L);
	temp_4 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	temp_5 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_LT(temp_4,temp_5)) {
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    left_index & (SI_Long)1023L);
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    array = a;
	    index_1 = left_index;
	    value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(a,left + 
		    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		    (left >>  -  - (SI_Long)10L) + (SI_Long)2L),left & 
		    (SI_Long)1023L);
	    value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ?
		     DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		    (SI_Long)0L)) : value;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    array = a;
	    index_1 = left;
	    value = temp;
	    old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L),index_1 & (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == 
			(SI_Long)1L) {
		if (FLOATP(value)) {
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
		}
		else {
		    if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			    Maximum_in_place_array_size)) {
			svref_arg_2 = index_1 + 
				IFIX(Managed_array_index_offset);
			ISVREF(array,svref_arg_2) = value;
		    }
		    else {
			temp_1 = ISVREF(array,(index_1 >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			svref_arg_2 = index_1 & (SI_Long)1023L;
			ISVREF(temp_1,svref_arg_2) = value;
		    }
		    reclaim_managed_simple_float_array_of_length_1(old_value);
		}
	    }
	    else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(array,svref_arg_2) = new_float;
	    }
	    else {
		temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
			(SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		if (FLOATP(value)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		}
		else
		    new_float = value;
		ISVREF(temp_1,svref_arg_2) = new_float;
	    }
	    temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(b,FIX(left)));
	    mutate_g2_array_reclaiming_evaluation_values(b,FIX(left),temp);
	    if (data_array_2_qm) {
		temp = 
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left_index));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left_index),
			g2_array_aref_item_or_evaluation_value(data_array_2_qm,
			FIX(left)));
		mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
			FIX(left),temp);
	    }
	}
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	pivot = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	pivot_b = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	pivot_b_2_qm = data_array_2_qm ? 
		g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		FIX(left_index)) : Nil;
      next_loop:
	i = left_index + (SI_Long)1L;
      next_loop_1:
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,i + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	temp_4 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_LE(temp_4,pivot)) {
	    left_index = i;
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:
	left_index = IFIX(Qnil);
      end_1:;
	i = right_index - (SI_Long)1L;
      next_loop_2:
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,i + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	temp_4 = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	if (NUM_GE(temp_4,pivot)) {
	    right_index = i;
	    goto end_2;
	}
	i = i - (SI_Long)1L;
	goto next_loop_2;
      end_loop_1:
	right_index = IFIX(Qnil);
      end_2:;
	if (right_index < left_index)
	    goto end_3;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,left_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(left_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		left_index & (SI_Long)1023L);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	array = a;
	index_1 = left_index;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(right_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		right_index & (SI_Long)1023L);
	value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	array = a;
	index_1 = right_index;
	value = temp;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	temp = g2_array_aref_item_or_evaluation_value(b,FIX(left_index));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left_index),
		g2_array_aref_item_or_evaluation_value(b,FIX(right_index)));
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),temp);
	if (data_array_2_qm) {
	    temp = g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(left_index));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left_index),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right_index)));
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right_index),temp);
	}
	goto next_loop;
      end_loop_2:
      end_3:
	array = a;
	index_1 = left + (SI_Long)1L;
	value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,right_index + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(right_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		right_index & (SI_Long)1023L);
	value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L ? 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,(SI_Long)0L)) 
		: value;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(left + 
		(SI_Long)1L),g2_array_aref_item_or_evaluation_value(b,
		FIX(right_index)));
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(left + (SI_Long)1L),
		    g2_array_aref_item_or_evaluation_value(data_array_2_qm,
		    FIX(right_index)));
	array = a;
	index_1 = right_index;
	value = pivot;
	old_value = FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(array,index_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    if (FLOATP(value)) {
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    }
	    else {
		if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		    ISVREF(array,svref_arg_2) = value;
		}
		else {
		    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) 
			    + (SI_Long)2L);
		    svref_arg_2 = index_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = value;
		}
		reclaim_managed_simple_float_array_of_length_1(old_value);
	    }
	}
	else if (FIXNUM_LE(ISVREF(array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    if (FLOATP(value)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    }
	    else
		new_float = value;
	    ISVREF(array,svref_arg_2) = new_float;
	}
	else {
	    temp_1 = ISVREF(array,(index_1 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    if (FLOATP(value)) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_2 = Vector_of_simple_float_array_pools;
		    temp_3 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		    }
		    else {
			temp_2 = Available_float_array_conses_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			temp_2 = Available_float_array_conses_tail_vector;
			temp_3 = Current_thread_index;
			SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	    }
	    else
		new_float = value;
	    ISVREF(temp_1,svref_arg_2) = new_float;
	}
	mutate_g2_array_reclaiming_evaluation_values(b,FIX(right_index),
		pivot_b);
	if (data_array_2_qm)
	    mutate_g2_array_reclaiming_evaluation_values(data_array_2_qm,
		    FIX(right_index),pivot_b_2_qm);
	result = VALUES_1(FIX(right_index));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* PARTITION-PER-ARRAY-TYPE */
Object partition_per_array_type(key_array,data_array_1,data_array_2_qm,
	    left_init,right_init,array_type)
    Object key_array, data_array_1, data_array_2_qm, left_init, right_init;
    Object array_type;
{
    SI_Long left, right;

    x_note_fn_call(144,73);
    left = IFIX(left_init);
    right = IFIX(right_init);
    if (EQ(array_type,Qinteger))
	return integer_partition(key_array,data_array_1,data_array_2_qm,
		FIX(left),FIX(right));
    else if (EQ(array_type,Qfloat))
	return float_partition(key_array,data_array_1,data_array_2_qm,
		FIX(left),FIX(right));
    else
	return quantity_partition(key_array,data_array_1,data_array_2_qm,
		FIX(left),FIX(right));
}

static Object string_constant_1;   /* "Sorting a list or array containing NaNs with no ~
				    *                       comparison function is undefined."
				    */

/* QUICKSORT-1 */
Object quicksort_1(g2_key_value_array,g2_key_array,g2_aux_array,
	    left_stack_list,right_stack_list,state_list)
    Object g2_key_value_array, g2_key_array, g2_aux_array, left_stack_list;
    Object right_stack_list, state_list;
{
    Object current_left, current_right, stack_depth, key_array;
    Object key_value_array, aux_array_qm, array_type, stack_depth_source;
    Object current_right_source, current_left_source, time_of_start, x2;
    Object sub_class_bit_vector, array, element_type, items_possible_p;
    Object managed_g2_array, float_or_quantity_p, element, elt_1, thing;
    Object gensymed_symbol_3, gensymed_symbol_4, top_of_stack, message_1;
    Object quit_qm, partition_point, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, array_length;
    SI_Long managed_step_size, managed_length, max_inner_index, outer_index;
    SI_Long inner_index, ab_loop_bind_, incff_1_arg;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,74);
    current_left = Nil;
    current_right = Nil;
    stack_depth = Nil;
    key_array = g2_key_array;
    key_value_array = g2_key_value_array;
    aux_array_qm = Nil;
    array_type = ISVREF(g2_key_value_array,(SI_Long)21L);
    stack_depth_source = Nil;
    current_right_source = Nil;
    current_left_source = Nil;
    time_of_start = c_native_clock_ticks_or_cache(Nil,Nil);
    if (SIMPLE_VECTOR_P(g2_aux_array) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_aux_array)) > (SI_Long)2L && 
	     !EQ(ISVREF(g2_aux_array,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_aux_array,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(g2_aux_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp)
	aux_array_qm = g2_aux_array;
    if (IFIX(g2_list_length(left_stack_list)) == (SI_Long)0L) {
	if ( !EQ(array_type,Qinteger)) {
	    array = g2_key_value_array;
	    element_type = ISVREF(array,(SI_Long)21L);
	    items_possible_p = 
		    g2_list_or_array_element_type_may_contain_item_p(element_type);
	    managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	    array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	    managed_length = array_length * managed_step_size;
	    float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	    if (float_or_quantity_p);
	    else
		float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	    max_inner_index = float_or_quantity_p ? (SI_Long)100L : 
		    managed_length;
	    outer_index = (SI_Long)0L;
	    if ( !TRUEP(managed_g2_array))
		goto end_1;
	  next_loop:
	    if ( !(outer_index < managed_length))
		goto end_loop;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_index = (SI_Long)0L;
		ab_loop_bind_ = max_inner_index;
		element = Nil;
	      next_loop_1:
		if (inner_index >= ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(element_type,Qfloat))
		    element = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			    (outer_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),outer_index & (SI_Long)1023L));
		else {
		    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,outer_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,(outer_index >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),outer_index 
			    & (SI_Long)1023L);
		    temp =  !TRUEP(items_possible_p);
		    if (temp);
		    else if (elt_1) {
			if (SIMPLE_VECTOR_P(elt_1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
				(SI_Long)2L) {
			    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp);
			    else {
				thing = ISVREF(elt_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
			    gensymed_symbol = outer_index + (SI_Long)1L;
			    gensymed_symbol_4 = 
				    FIXNUM_LE(ISVREF(managed_g2_array,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(managed_g2_array,
				    gensymed_symbol + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(managed_g2_array,
				    (gensymed_symbol >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol & (SI_Long)1023L);
			    temp = (FIXNUMP(gensymed_symbol_3) ? 
				    (FIXNUMP(gensymed_symbol_4) ? 
				    FIXNUM_EQ(gensymed_symbol_3,
				    gensymed_symbol_4) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_4) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol_3),
				    M_CAR(gensymed_symbol_4)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol_3),
				    M_CDR(gensymed_symbol_4))) ? 
				    (SI_Long)0L != (IFIX(ISVREF(elt_1,
				    (SI_Long)5L)) & (SI_Long)1L) || 
				    ISVREF(array,(SI_Long)24L) : TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    element = temp ? elt_1 : Nil;
		}
		if (nanp(INLINE_DOUBLE_FLOAT_VECTOR_P(element) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == 
			(SI_Long)1L ? 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(element,
			(SI_Long)0L)) : element)) {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(1,
			    string_constant_1);
		    raw_stack_error_named_error(top_of_stack,message_1);
		}
		incff_1_arg = managed_step_size;
		outer_index = outer_index + incff_1_arg;
		if ( !(outer_index < managed_length))
		    goto end_loop_1;
		inner_index = inner_index + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    goto next_loop;
	  end_loop:
	    goto end_1;
	  end_1:;
	}
	current_left = FIX((SI_Long)0L);
	current_right = FIXNUM_SUB1(ISVREF(key_array,(SI_Long)20L));
	g2_list_insert_at_beginning(current_left,left_stack_list);
	g2_list_insert_at_beginning(current_right,right_stack_list);
	stack_depth = FIX((SI_Long)1L);
    }
    else {
	stack_depth_source = pop_g2_list(state_list);
	stack_depth = evaluation_value_value(stack_depth_source);
	current_left_source = pop_g2_list(state_list);
	current_left = evaluation_value_value(current_left_source);
	current_right_source = pop_g2_list(state_list);
	current_right = evaluation_value_value(current_right_source);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(key_value_array);
    quit_qm = Nil;
    partition_point = Nil;
  next_loop_2:
    if (IFIX(stack_depth) == (SI_Long)0L || quit_qm)
	goto end_loop_2;
    if (FIXNUM_GT(current_right,current_left) && 
	    FIXNUM_LT(FIXNUM_MINUS(current_right,current_left),
	    Insertion_sort_array_size)) {
	insertion_sort_per_array_type(key_value_array,key_array,
		aux_array_qm,current_left,current_right,array_type);
	current_right = current_left;
    }
    if (FIXNUM_GT(current_right,current_left)) {
	partition_point = partition_per_array_type(key_value_array,
		key_array,aux_array_qm,current_left,current_right,array_type);
	if (FIXNUM_GT(FIXNUM_MINUS(partition_point,current_left),
		FIXNUM_MINUS(current_right,partition_point))) {
	    g2_list_insert_at_beginning(current_left,left_stack_list);
	    g2_list_insert_at_beginning(FIXNUM_SUB1(partition_point),
		    right_stack_list);
	    current_left = FIXNUM_ADD1(partition_point);
	}
	else {
	    g2_list_insert_at_beginning(FIXNUM_ADD1(partition_point),
		    left_stack_list);
	    g2_list_insert_at_beginning(current_right,right_stack_list);
	    current_right = FIXNUM_SUB1(partition_point);
	}
	stack_depth = FIXNUM_ADD1(stack_depth);
    }
    else {
	stack_depth = FIXNUM_SUB1(stack_depth);
	if (current_right_source)
	    reclaim_evaluation_value(current_right_source);
	if (current_left_source)
	    reclaim_evaluation_value(current_left_source);
	current_right_source = pop_g2_list(right_stack_list);
	current_right = evaluation_value_value(current_right_source);
	current_left_source = pop_g2_list(left_stack_list);
	current_left = evaluation_value_value(current_left_source);
    }
    temp_1 = FIXNUM_MINUS(c_native_clock_ticks_or_cache(Nil,Nil),
	    time_of_start);
    if (FIXNUM_GT(temp_1,Maximum_time_slice_size))
	quit_qm = T;
    goto next_loop_2;
  end_loop_2:;
    g2_list_insert_at_beginning(current_right,state_list);
    g2_list_insert_at_beginning(current_left,state_list);
    g2_list_insert_at_beginning(stack_depth,state_list);
    if (current_right_source)
	reclaim_evaluation_value(current_right_source);
    if (current_left_source)
	reclaim_evaluation_value(current_left_source);
    if (stack_depth_source)
	reclaim_evaluation_value(stack_depth_source);
    return VALUES_3(left_stack_list,right_stack_list,state_list);
}

static Object Qab_slot_value;      /* slot-value */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_2;   /* "Cannot copy the array elements of ~NF into its initial-values attribute." */

static Object string_constant_3;   /* " A permanent array cannot be initialized." */

static Object string_constant_4;   /* "  An array element has no value." */

static Object string_constant_5;   /* "  An array element, ~NF, cannot be an initial value.  It must either ~
				    *                  have a name or be an attribute of a named item."
				    */

/* G2-COPY-ARRAY-ELEMENTS-TO-INITIAL-VALUES */
Object g2_copy_array_elements_to_initial_values(g2_array)
    Object g2_array;
{
    Object new_initial_values_list, all_equal_p, permanent_array_p;
    Object element_copy_no_value_error_qm, element_copy_error_in_frame_qm;
    Object tail_qm, previous_element_qm, element_type, items_possible_p;
    Object all_previous_elements_contain_no_value_qm, array, element_type_1;
    Object items_possible_p_1, managed_g2_array, float_or_quantity_p, element;
    Object elt_1, thing, gensymed_symbol, gensymed_symbol_2;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, x2, designation_qm, temp_3, svref_new_value, new_cons;
    Object gensymed_symbol_3, top_of_stack, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long array_length, managed_step_size, managed_length, max_inner_index;
    SI_Long outer_index, inner_index, ab_loop_bind_, gensymed_symbol_1;
    SI_Long incff_1_arg, bv16_length, aref_arg_2, aref_new_value_1, length_1;
    char temp;
    double aref_new_value, arg, arg_1;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,75);
    if (EQ(ISVREF(g2_array,(SI_Long)20L),FIX((SI_Long)0L))) {
	change_slot_value(3,g2_array,Qg2_array_initial_values,Nil);
	return VALUES_1(Nil);
    }
    new_initial_values_list = Nil;
    all_equal_p = T;
    permanent_array_p = Nil;
    element_copy_no_value_error_qm = Nil;
    element_copy_error_in_frame_qm = Nil;
    if (ISVREF(g2_array,(SI_Long)24L) && ISVREF(g2_array,(SI_Long)23L))
	permanent_array_p = T;
    else {
	tail_qm = Nil;
	previous_element_qm = Nil;
	element_type = ISVREF(g2_array,(SI_Long)21L);
	items_possible_p = 
		g2_list_or_array_element_type_may_contain_item_p(element_type);
	all_previous_elements_contain_no_value_qm = items_possible_p;
	array = g2_array;
	element_type_1 = ISVREF(array,(SI_Long)21L);
	items_possible_p_1 = 
		g2_list_or_array_element_type_may_contain_item_p(element_type_1);
	managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	managed_step_size = items_possible_p_1 ? (SI_Long)2L : (SI_Long)1L;
	managed_length = array_length * managed_step_size;
	float_or_quantity_p = EQ(element_type_1,Qfloat) ? T : Nil;
	if (float_or_quantity_p);
	else
	    float_or_quantity_p = EQ(element_type_1,Qquantity) ? T : Nil;
	max_inner_index = float_or_quantity_p ? (SI_Long)100L : managed_length;
	outer_index = (SI_Long)0L;
	if ( !TRUEP(managed_g2_array))
	    goto end_1;
      next_loop:
	if ( !(outer_index < managed_length))
	    goto end_loop;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    inner_index = (SI_Long)0L;
	    ab_loop_bind_ = max_inner_index;
	    element = Nil;
	  next_loop_1:
	    if (inner_index >= ab_loop_bind_)
		goto end_loop_1;
	    if (EQ(element_type_1,Qfloat))
		element = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			(outer_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
			outer_index & (SI_Long)1023L));
	    else {
		elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(managed_g2_array,outer_index + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(managed_g2_array,(outer_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L),outer_index & 
			(SI_Long)1023L);
		temp =  !TRUEP(items_possible_p_1);
		if (temp);
		else if (elt_1) {
		    if (SIMPLE_VECTOR_P(elt_1) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
			    (SI_Long)2L) {
			temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				Qavailable_frame_vector);
			if (temp);
			else {
			    thing = ISVREF(elt_1,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(thing) ? 
				    EQ(ISVREF(thing,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    : TRUEP(Qnil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    temp =  !temp;
		    if (temp);
		    else {
			gensymed_symbol = ISVREF(elt_1,(SI_Long)3L);
			gensymed_symbol_1 = outer_index + (SI_Long)1L;
			gensymed_symbol_2 = 
				FIXNUM_LE(ISVREF(managed_g2_array,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(managed_g2_array,gensymed_symbol_1 
				+ IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(managed_g2_array,
				(gensymed_symbol_1 >>  -  - (SI_Long)10L) 
				+ (SI_Long)2L),gensymed_symbol_1 & 
				(SI_Long)1023L);
			temp = (FIXNUMP(gensymed_symbol) ? 
				(FIXNUMP(gensymed_symbol_2) ? 
				FIXNUM_EQ(gensymed_symbol,
				gensymed_symbol_2) : TRUEP(Nil)) : 
				FIXNUMP(gensymed_symbol_2) ? TRUEP(Nil) : 
				FIXNUM_EQ(M_CAR(gensymed_symbol),
				M_CAR(gensymed_symbol_2)) && 
				FIXNUM_EQ(M_CDR(gensymed_symbol),
				M_CDR(gensymed_symbol_2))) ? (SI_Long)0L 
				!= (IFIX(ISVREF(elt_1,(SI_Long)5L)) & 
				(SI_Long)1L) || ISVREF(array,(SI_Long)24L) 
				: TRUEP(Nil);
		    }
		}
		else
		    temp = TRUEP(Nil);
		element = temp ? elt_1 : Nil;
	    }
	    if (EQ(element_type,Qfloat)) {
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
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		gensymed_symbol = new_float;
	    }
	    else if (EQ(element_type,Qinteger) || EQ(element_type,
		    Qtruth_value))
		gensymed_symbol = element;
	    else if (EQ(element_type,Qquantity)) {
		if (FIXNUMP(element))
		    gensymed_symbol = element;
		else if (INLINE_LONG_VECTOR_P(element) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == 
			(SI_Long)1L)
		    gensymed_symbol = copy_managed_long(element);
		else
		    gensymed_symbol = copy_managed_float(element);
	    }
	    else if (EQ(element_type,Qsymbol))
		gensymed_symbol = element;
	    else if (EQ(element_type,Qtext))
		gensymed_symbol = copy_wide_string(element);
	    else if (items_possible_p &&  !TRUEP(element)) {
		if ( !TRUEP(all_previous_elements_contain_no_value_qm))
		    element_copy_no_value_error_qm = T;
		gensymed_symbol = Nil;
	    }
	    else {
		if (items_possible_p)
		    all_previous_elements_contain_no_value_qm = Nil;
		if (items_possible_p) {
		    if (SIMPLE_VECTOR_P(element) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(element,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(element,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    designation_qm = generate_designation_for_block(element);
		    if (designation_qm) {
			temp_3 = 
				copy_tree_using_slot_value_conses_1(designation_qm);
			reclaim_eval_tree_1(designation_qm);
			gensymed_symbol = temp_3;
		    }
		    else {
			element_copy_error_in_frame_qm = element;
			gensymed_symbol = Nil;
		    }
		}
		else if (items_possible_p && element && SYMBOLP(element)) {
		    gensymed_symbol = Nil;
		  next_loop_2:
		    temp_3 = ISVREF(Available_slot_value_conses_vector,
			    IFIX(Current_thread_index));
		    gensymed_symbol = CDR(temp_3);
		    if (gensymed_symbol)
			goto end_loop_2;
		    replenish_slot_value_list_pool(FIX((SI_Long)1L));
		    goto next_loop_2;
		  end_loop_2:
		    if ( !((SI_Long)0L == inline_debugging_consing())) {
			gensymed_symbol_2 = 
				ISVREF(Available_slot_value_conses_vector,
				IFIX(Current_thread_index));
		      next_loop_3:
			inline_note_allocate_cons(gensymed_symbol_2,
				Qab_slot_value);
			if (EQ(gensymed_symbol_2,gensymed_symbol))
			    goto end_loop_3;
			gensymed_symbol_2 = CDR(gensymed_symbol_2);
			goto next_loop_3;
		      end_loop_3:;
		    }
		    temp_3 = ISVREF(Available_slot_value_conses_vector,
			    IFIX(Current_thread_index));
		    temp_1 = Available_slot_value_conses_vector;
		    temp_2 = Current_thread_index;
		    svref_new_value = CDR(gensymed_symbol);
		    SVREF(temp_1,temp_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_slot_value_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = Nil;
		    }
		    M_CDR(gensymed_symbol) = Nil;
		    gensymed_symbol = temp_3;
		    goto end_2;
		    gensymed_symbol = Qnil;
		  end_2:;
		    gensymed_symbol_2 = gensymed_symbol;
		    new_cons = ISVREF(Available_slot_value_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_slot_value_conses_vector;
			temp_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,temp_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_slot_value_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_slot_value_conses_tail_vector;
			    temp_2 = Current_thread_index;
			    SVREF(temp_1,temp_2) = Nil;
			}
			gensymed_symbol_3 = new_cons;
		    }
		    else
			gensymed_symbol_3 = Nil;
		    if ( !TRUEP(gensymed_symbol_3))
			gensymed_symbol_3 = replenish_slot_value_cons_pool();
		    M_CAR(gensymed_symbol_3) = 
			    Symbol_initial_value_marker_symbol;
		    M_CDR(gensymed_symbol_3) = Nil;
		    inline_note_allocate_cons(gensymed_symbol_3,
			    Qab_slot_value);
		    M_CAR(gensymed_symbol_2) = gensymed_symbol_3;
		    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
		    M_CAR(gensymed_symbol_2) = element;
		}
		else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value))
		    gensymed_symbol = make_slot_constant(M_CAR(element),
			    Qtruth_value,Nil);
		else
		    gensymed_symbol = FIXNUMP(element) || element && 
			    SYMBOLP(element) ? element : 
			    copy_evaluation_value_1(element);
	    }
	    new_cons = ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_slot_value_conses_vector;
		temp_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,temp_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_slot_value_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_slot_value_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol;
	    M_CDR(gensymed_symbol_2) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_2,Qab_slot_value);
	    if (new_initial_values_list) {
		if ( !TRUEP(tail_qm))
		    tail_qm = last(new_initial_values_list,_);
		temp_1 = gensymed_symbol_2;
		M_CDR(tail_qm) = temp_1;
	    }
	    else
		new_initial_values_list = gensymed_symbol_2;
	    tail_qm = gensymed_symbol_2;
	    if (all_equal_p && element) {
		if (previous_element_qm) {
		    if (EQ(element_type,Qfloat)) {
			arg = DOUBLE_FLOAT_TO_DOUBLE(element);
			arg_1 = DOUBLE_FLOAT_TO_DOUBLE(previous_element_qm);
			all_equal_p = arg == arg_1 &&  
				!inline_nanp_for_comparison(arg) ? ( 
				!inline_nanp_for_comparison(arg_1) ? T : 
				Nil) : Qnil;
		    }
		    else
			all_equal_p = item_or_value_eql(element,
				previous_element_qm);
		}
		previous_element_qm = element;
	    }
	    incff_1_arg = managed_step_size;
	    outer_index = outer_index + incff_1_arg;
	    if ( !(outer_index < managed_length))
		goto end_loop_1;
	    inner_index = inner_index + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	goto next_loop;
      end_loop:
	goto end_1;
      end_1:;
	if (all_previous_elements_contain_no_value_qm) {
	    reclaim_slot_value(new_initial_values_list);
	    new_initial_values_list = Nil;
	}
    }
    if (element_copy_no_value_error_qm || element_copy_error_in_frame_qm) {
	reclaim_slot_value(new_initial_values_list);
	new_initial_values_list = Nil;
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
	      aref_new_value_1 = (SI_Long)2048L & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_1);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value_1 = (SI_Long)57344L | (SI_Long)0L;
	      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value_1);
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
		      tformat(2,string_constant_2,g2_array);
		      if (permanent_array_p)
			  tformat(1,string_constant_3);
		      else if (element_copy_no_value_error_qm)
			  tformat(1,string_constant_4);
		      else {
			  if (element_copy_error_in_frame_qm) {
			      if (SIMPLE_VECTOR_P(element_copy_error_in_frame_qm) 
				      && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element_copy_error_in_frame_qm)) 
				      > (SI_Long)2L &&  
				      !EQ(ISVREF(element_copy_error_in_frame_qm,
				      (SI_Long)1L),Qavailable_frame_vector)) {
				  x2 = 
					  ISVREF(element_copy_error_in_frame_qm,
					  (SI_Long)1L);
				  temp = SIMPLE_VECTOR_P(x2) && 
					  EQ(ISVREF(x2,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  ? TRUEP(x2) : TRUEP(Qnil);
			      }
			      else
				  temp = TRUEP(Nil);
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp)
			      tformat(2,string_constant_5,
				      element_copy_error_in_frame_qm);
		      }
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
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	if (new_initial_values_list && all_equal_p) {
	    reclaim_slot_value(CDR(new_initial_values_list));
	    M_CDR(new_initial_values_list) = Nil;
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(g2_array);
	change_slot_value(3,g2_array,Qg2_array_initial_values,
		new_initial_values_list);
	remove_kb_state_variable_record(g2_array,Qg2_array_length);
    }
    return VALUES_1(Nil);
}

/* ITEM-OR-VALUE-EQL-P */
Object item_or_value_eql_p(element1,element2)
    Object element1, element2;
{
    Object x2;
    char temp;

    x_note_fn_call(144,76);
    if (SIMPLE_VECTOR_P(element1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element1)) > (SI_Long)2L &&  
	    !EQ(ISVREF(element1,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(element1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (SIMPLE_VECTOR_P(element2) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element2)) > (SI_Long)2L && 
		 !EQ(ISVREF(element2,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element2,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(EQ(element1,element2) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else {
	if (SIMPLE_VECTOR_P(element2) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element2)) > (SI_Long)2L && 
		 !EQ(ISVREF(element2,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element2,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    return evaluation_value_eql(2,element1,element2);
	else
	    return VALUES_1(Nil);
    }
}

/* G2-GET-POSITION-IN-LIST-OF-ELEMENT */
Object g2_get_position_in_list_of_element(element,g2_list)
    Object element, g2_list;
{
    Object ab_loopvar_, ab_loopvar__1, item_or_value, ii, ab_loop_iter_flag_;
    Object index_1;

    x_note_fn_call(144,77);
    ab_loopvar_ = ISVREF(g2_list,(SI_Long)20L);
    ab_loopvar__1 = Nil;
    item_or_value = Nil;
    ii = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
    ab_loopvar__1 = ab_loopvar_ ? 
	    g2_list_structure_next(ISVREF(ab_loopvar_,(SI_Long)2L),
	    ab_loopvar_) : Nil;
  next_loop:
    if ( !TRUEP(ab_loopvar__1))
	goto end_loop;
    item_or_value = ISVREF(ab_loopvar__1,(SI_Long)4L);
    ab_loopvar__1 = g2_list_structure_next(ab_loopvar__1,ab_loopvar_);
    if ( !TRUEP(ab_loop_iter_flag_))
	ii = FIXNUM_ADD1(ii);
    if (item_or_value_eql_p(item_or_value,element)) {
	index_1 = ii;
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    index_1 = Qnil;
  end_1:;
    if ( !(FIXNUMP(element) || SYMBOLP(element) || SIMPLE_VECTOR_P(element)))
	reclaim_if_evaluation_value_1(element);
    if (index_1)
	return VALUES_1(index_1);
    else
	return VALUES_1(FIX((SI_Long)-1L));
}

/* G2-GET-POSITION-IN-ARRAY-OF-ELEMENT */
Object g2_get_position_in_array_of_element(element,g2_array)
    Object element, g2_array;
{
    Object index_1, value_to_match, unmanaged_float_p, sub_class_bit_vector;
    Object array, element_type, items_possible_p, managed_g2_array;
    Object float_or_quantity_p, tag_temp, item_or_value_qm, elt_1, thing;
    Object gensymed_symbol_3, gensymed_symbol_4, temp_1, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, array_length;
    SI_Long managed_step_size, managed_length, max_inner_index, outer_index;
    SI_Long inner_index, ab_loop_bind_, incff_1_arg;
    char temp;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(144,78);
    index_1 = FIX((SI_Long)0L);
    value_to_match = element;
    unmanaged_float_p = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Float_array_class_description,
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
    if (temp) {
	value_to_match = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(element,
		(SI_Long)0L));
	unmanaged_float_p = T;
    }
    sub_class_bit_vector = ISVREF(ISVREF(g2_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Truth_value_array_class_description,(SI_Long)18L));
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
	value_to_match = M_CAR(element);
    if (unmanaged_float_p) {
	array = g2_array;
	element_type = ISVREF(array,(SI_Long)21L);
	items_possible_p = 
		g2_list_or_array_element_type_may_contain_item_p(element_type);
	managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	managed_length = array_length * managed_step_size;
	float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	if (float_or_quantity_p);
	else
	    float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	max_inner_index = float_or_quantity_p ? (SI_Long)100L : managed_length;
	outer_index = (SI_Long)0L;
	tag_temp = UNIQUE_TAG(Qnil);
	if (PUSH_CATCH(tag_temp,0)) {
	    if ( !TRUEP(managed_g2_array)) {
		result = VALUES_1(Nil);
		THROW(tag_temp,result);
	    }
	  next_loop:
	    if ( !(outer_index < managed_length))
		goto end_loop;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_index = (SI_Long)0L;
		ab_loop_bind_ = max_inner_index;
		item_or_value_qm = Nil;
	      next_loop_1:
		if (inner_index >= ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(element_type,Qfloat))
		    item_or_value_qm = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			    (outer_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),outer_index & (SI_Long)1023L));
		else {
		    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,outer_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,(outer_index >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),outer_index 
			    & (SI_Long)1023L);
		    temp =  !TRUEP(items_possible_p);
		    if (temp);
		    else if (elt_1) {
			if (SIMPLE_VECTOR_P(elt_1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
				(SI_Long)2L) {
			    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp);
			    else {
				thing = ISVREF(elt_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
			    gensymed_symbol = outer_index + (SI_Long)1L;
			    gensymed_symbol_4 = 
				    FIXNUM_LE(ISVREF(managed_g2_array,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(managed_g2_array,
				    gensymed_symbol + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(managed_g2_array,
				    (gensymed_symbol >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol & (SI_Long)1023L);
			    temp = (FIXNUMP(gensymed_symbol_3) ? 
				    (FIXNUMP(gensymed_symbol_4) ? 
				    FIXNUM_EQ(gensymed_symbol_3,
				    gensymed_symbol_4) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_4) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol_3),
				    M_CAR(gensymed_symbol_4)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol_3),
				    M_CDR(gensymed_symbol_4))) ? 
				    (SI_Long)0L != (IFIX(ISVREF(elt_1,
				    (SI_Long)5L)) & (SI_Long)1L) || 
				    ISVREF(array,(SI_Long)24L) : TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    item_or_value_qm = temp ? elt_1 : Nil;
		}
		if (EQL(item_or_value_qm,value_to_match)) {
		    result = VALUES_1(index_1);
		    THROW(tag_temp,result);
		}
		index_1 = FIXNUM_ADD1(index_1);
		incff_1_arg = managed_step_size;
		outer_index = outer_index + incff_1_arg;
		if ( !(outer_index < managed_length))
		    goto end_loop_1;
		inner_index = inner_index + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(FIX((SI_Long)-1L));
	    THROW(tag_temp,result);
	    temp_1 = Qnil;
	}
	else
	    temp_1 = CATCH_VALUES();
	POP_CATCH(0);
    }
    else {
	if (SIMPLE_VECTOR_P(value_to_match) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_to_match)) > 
		(SI_Long)2L &&  !EQ(ISVREF(value_to_match,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(value_to_match,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    array = g2_array;
	    element_type = ISVREF(array,(SI_Long)21L);
	    items_possible_p = 
		    g2_list_or_array_element_type_may_contain_item_p(element_type);
	    managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	    array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	    managed_length = array_length * managed_step_size;
	    float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	    if (float_or_quantity_p);
	    else
		float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	    max_inner_index = float_or_quantity_p ? (SI_Long)100L : 
		    managed_length;
	    outer_index = (SI_Long)0L;
	    tag_temp = UNIQUE_TAG(Qnil);
	    if (PUSH_CATCH(tag_temp,0)) {
		if ( !TRUEP(managed_g2_array)) {
		    result = VALUES_1(Nil);
		    THROW(tag_temp,result);
		}
	      next_loop_2:
		if ( !(outer_index < managed_length))
		    goto end_loop_2;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    inner_index = (SI_Long)0L;
		    ab_loop_bind_ = max_inner_index;
		    item_or_value_qm = Nil;
		  next_loop_3:
		    if (inner_index >= ab_loop_bind_)
			goto end_loop_3;
		    if (EQ(element_type,Qfloat))
			item_or_value_qm = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
				(outer_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),outer_index & (SI_Long)1023L));
		    else {
			elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(managed_g2_array,outer_index + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(managed_g2_array,
				(outer_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),outer_index & (SI_Long)1023L);
			temp =  !TRUEP(items_possible_p);
			if (temp);
			else if (elt_1) {
			    if (SIMPLE_VECTOR_P(elt_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) 
				    > (SI_Long)2L) {
				temp = EQ(ISVREF(elt_1,(SI_Long)1L),
					Qavailable_frame_vector);
				if (temp);
				else {
				    thing = ISVREF(elt_1,(SI_Long)1L);
				    temp = SIMPLE_VECTOR_P(thing) ? 
					    EQ(ISVREF(thing,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    : TRUEP(Qnil);
				}
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			    if (temp);
			    else {
				gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
				gensymed_symbol = outer_index + (SI_Long)1L;
				gensymed_symbol_4 = 
					FIXNUM_LE(ISVREF(managed_g2_array,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(managed_g2_array,
					gensymed_symbol + 
					IFIX(Managed_array_index_offset)) :
					 ISVREF(ISVREF(managed_g2_array,
					(gensymed_symbol >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					gensymed_symbol & (SI_Long)1023L);
				temp = (FIXNUMP(gensymed_symbol_3) ? 
					(FIXNUMP(gensymed_symbol_4) ? 
					FIXNUM_EQ(gensymed_symbol_3,
					gensymed_symbol_4) : TRUEP(Nil)) : 
					FIXNUMP(gensymed_symbol_4) ? 
					TRUEP(Nil) : 
					FIXNUM_EQ(M_CAR(gensymed_symbol_3),
					M_CAR(gensymed_symbol_4)) && 
					FIXNUM_EQ(M_CDR(gensymed_symbol_3),
					M_CDR(gensymed_symbol_4))) ? 
					(SI_Long)0L != (IFIX(ISVREF(elt_1,
					(SI_Long)5L)) & (SI_Long)1L) || 
					ISVREF(array,(SI_Long)24L) : 
					TRUEP(Nil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			item_or_value_qm = temp ? elt_1 : Nil;
		    }
		    if (EQ(item_or_value_qm,value_to_match)) {
			result = VALUES_1(index_1);
			THROW(tag_temp,result);
		    }
		    index_1 = FIXNUM_ADD1(index_1);
		    incff_1_arg = managed_step_size;
		    outer_index = outer_index + incff_1_arg;
		    if ( !(outer_index < managed_length))
			goto end_loop_3;
		    inner_index = inner_index + (SI_Long)1L;
		    goto next_loop_3;
		  end_loop_3:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		goto next_loop_2;
	      end_loop_2:
		result = VALUES_1(FIX((SI_Long)-1L));
		THROW(tag_temp,result);
		temp_1 = Qnil;
	    }
	    else
		temp_1 = CATCH_VALUES();
	    POP_CATCH(0);
	}
	else {
	    array = g2_array;
	    element_type = ISVREF(array,(SI_Long)21L);
	    items_possible_p = 
		    g2_list_or_array_element_type_may_contain_item_p(element_type);
	    managed_g2_array = ACCESS_ONCE(ISVREF(array,(SI_Long)23L));
	    array_length = IFIX(ACCESS_ONCE(ISVREF(array,(SI_Long)20L)));
	    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	    managed_length = array_length * managed_step_size;
	    float_or_quantity_p = EQ(element_type,Qfloat) ? T : Nil;
	    if (float_or_quantity_p);
	    else
		float_or_quantity_p = EQ(element_type,Qquantity) ? T : Nil;
	    max_inner_index = float_or_quantity_p ? (SI_Long)100L : 
		    managed_length;
	    outer_index = (SI_Long)0L;
	    tag_temp = UNIQUE_TAG(Qnil);
	    if (PUSH_CATCH(tag_temp,0)) {
		if ( !TRUEP(managed_g2_array)) {
		    result = VALUES_1(Nil);
		    THROW(tag_temp,result);
		}
	      next_loop_4:
		if ( !(outer_index < managed_length))
		    goto end_loop_4;
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    inner_index = (SI_Long)0L;
		    ab_loop_bind_ = max_inner_index;
		    item_or_value_qm = Nil;
		  next_loop_5:
		    if (inner_index >= ab_loop_bind_)
			goto end_loop_5;
		    if (EQ(element_type,Qfloat))
			item_or_value_qm = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
				(outer_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),outer_index & (SI_Long)1023L));
		    else {
			elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,
				(SI_Long)1L),Maximum_in_place_array_size) ?
				 ISVREF(managed_g2_array,outer_index + 
				IFIX(Managed_array_index_offset)) : 
				ISVREF(ISVREF(managed_g2_array,
				(outer_index >>  -  - (SI_Long)10L) + 
				(SI_Long)2L),outer_index & (SI_Long)1023L);
			temp =  !TRUEP(items_possible_p);
			if (temp);
			else if (elt_1) {
			    if (SIMPLE_VECTOR_P(elt_1) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) 
				    > (SI_Long)2L) {
				temp = EQ(ISVREF(elt_1,(SI_Long)1L),
					Qavailable_frame_vector);
				if (temp);
				else {
				    thing = ISVREF(elt_1,(SI_Long)1L);
				    temp = SIMPLE_VECTOR_P(thing) ? 
					    EQ(ISVREF(thing,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    : TRUEP(Qnil);
				}
			    }
			    else
				temp = TRUEP(Nil);
			    temp =  !temp;
			    if (temp);
			    else {
				gensymed_symbol_3 = ISVREF(elt_1,(SI_Long)3L);
				gensymed_symbol = outer_index + (SI_Long)1L;
				gensymed_symbol_4 = 
					FIXNUM_LE(ISVREF(managed_g2_array,
					(SI_Long)1L),
					Maximum_in_place_array_size) ? 
					ISVREF(managed_g2_array,
					gensymed_symbol + 
					IFIX(Managed_array_index_offset)) :
					 ISVREF(ISVREF(managed_g2_array,
					(gensymed_symbol >>  -  - 
					(SI_Long)10L) + (SI_Long)2L),
					gensymed_symbol & (SI_Long)1023L);
				temp = (FIXNUMP(gensymed_symbol_3) ? 
					(FIXNUMP(gensymed_symbol_4) ? 
					FIXNUM_EQ(gensymed_symbol_3,
					gensymed_symbol_4) : TRUEP(Nil)) : 
					FIXNUMP(gensymed_symbol_4) ? 
					TRUEP(Nil) : 
					FIXNUM_EQ(M_CAR(gensymed_symbol_3),
					M_CAR(gensymed_symbol_4)) && 
					FIXNUM_EQ(M_CDR(gensymed_symbol_3),
					M_CDR(gensymed_symbol_4))) ? 
					(SI_Long)0L != (IFIX(ISVREF(elt_1,
					(SI_Long)5L)) & (SI_Long)1L) || 
					ISVREF(array,(SI_Long)24L) : 
					TRUEP(Nil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			item_or_value_qm = temp ? elt_1 : Nil;
		    }
		    if (SIMPLE_VECTOR_P(item_or_value_qm) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_qm)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value_qm,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value_qm,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if ( !temp ? TRUEP(evaluation_value_eql(2,
			    item_or_value_qm,value_to_match)) : TRUEP(Nil)) {
			result = VALUES_1(index_1);
			THROW(tag_temp,result);
		    }
		    index_1 = FIXNUM_ADD1(index_1);
		    incff_1_arg = managed_step_size;
		    outer_index = outer_index + incff_1_arg;
		    if ( !(outer_index < managed_length))
			goto end_loop_5;
		    inner_index = inner_index + (SI_Long)1L;
		    goto next_loop_5;
		  end_loop_5:;
		}
		POP_LOCAL_ALLOCATION(0,0);
		goto next_loop_4;
	      end_loop_4:
		result = VALUES_1(FIX((SI_Long)-1L));
		THROW(tag_temp,result);
		temp_1 = Qnil;
	    }
	    else
		temp_1 = CATCH_VALUES();
	    POP_CATCH(0);
	}
    }
    if ( !(FIXNUMP(element) || SYMBOLP(element) || SIMPLE_VECTOR_P(element)))
	reclaim_if_evaluation_value_1(element);
    return VALUES_1(temp_1);
}

static Object float_constant_1;    /* -1.0 */

static Object float_constant_2;    /* 1.0 */

/* SIGMOIDAL-TRANSFER-FUNCTION */
Object sigmoidal_transfer_function(x)
    Object x;
{
    Object temp;
    double arg, arg_1, temp_1;

    x_note_fn_call(144,79);
    arg = DOUBLE_FLOAT_TO_DOUBLE(x);
    arg_1 = -40.0;
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	temp = float_constant_1;
    else {
	arg = 40.0;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(x);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    temp = float_constant_2;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x);
	    temp = DOUBLE_TO_DOUBLE_FLOAT(2.0 / (exp( - temp_1) + 1.0) - 1.0);
	}
    }
    return VALUES_1(temp);
}

static Object Qtransfer_fns;       /* transfer-fns */

static Object Qlayer_sizes;        /* layer-sizes */

static Object Qweight_array;       /* weight-array */

static Object string_constant_6;   /* "Invalid BPN, missing weights matrix at index ~a" */

/* G2-EVALUATE-BPN */
Object g2_evaluate_bpn(bpn,x,y)
    Object bpn, x, y;
{
    Object transfer_function_code_array, managed_transfer_function_code_array;
    Object layer_size_array, managed_layer_size_array, weights_array;
    Object managed_weights_array, number_of_layers, managed_x, length_x;
    Object ab_loopvar_, ab_loopvar__1, ab_loop_maxmin_fl_, temp1, temp2;
    Object managed_y, aref_arg_1, temp, gensymed_symbol_2, input_vector;
    Object output_vector, number_from, number_to, weights_matrix;
    Object current_layer_transfer_function_code, top_of_stack, message_1;
    Object managed_weights_matrix, weights_row, input_vector_element;
    SI_Long gensymed_symbol, i, ab_loop_bind_, gensymed_symbol_1;
    SI_Long max_nodes_in_layer, aref_arg_2, k, ab_loop_bind__1, j;
    SI_Long ab_loop_bind__2;
    double aref_new_value, temp_1, temp_2, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(144,80);
    transfer_function_code_array = get_slot_value_function(bpn,
	    Qtransfer_fns,Nil);
    managed_transfer_function_code_array = 
	    ISVREF(transfer_function_code_array,(SI_Long)23L);
    layer_size_array = get_slot_value_function(bpn,Qlayer_sizes,Nil);
    managed_layer_size_array = ISVREF(layer_size_array,(SI_Long)23L);
    weights_array = get_slot_value_function(bpn,Qweight_array,Nil);
    managed_weights_array = ISVREF(weights_array,(SI_Long)23L);
    number_of_layers = ISVREF(layer_size_array,(SI_Long)20L);
    managed_x = ISVREF(x,(SI_Long)23L);
    length_x = ISVREF(x,(SI_Long)20L);
    gensymed_symbol = (SI_Long)1L;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(number_of_layers);
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loopvar__1 = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ab_loopvar__1 = FIXNUM_LE(ISVREF(managed_layer_size_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_layer_size_array,
	    i + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_layer_size_array,(i >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
    if (ab_loop_maxmin_fl_) {
	ab_loop_maxmin_fl_ = Nil;
	ab_loopvar_ = ab_loopvar__1;
    }
    else
	ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(ab_loopvar_);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    max_nodes_in_layer = gensymed_symbol + gensymed_symbol_1;
    temp1 = allocate_managed_float_array(1,FIX(max_nodes_in_layer));
    temp2 = allocate_managed_float_array(1,FIX(max_nodes_in_layer));
    managed_y = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if ((FIXNUM_LE(ISVREF(managed_transfer_function_code_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		IFIX(ISVREF(managed_transfer_function_code_array,
		(SI_Long)0L + IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(managed_transfer_function_code_array,
		(SI_Long)2L),(SI_Long)0L))) == (SI_Long)1L) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(x,(SI_Long)20L));
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    aref_arg_1 = ISVREF(temp2,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    aref_arg_2 = i & (SI_Long)1023L;
	    temp = 
		    sigmoidal_transfer_function(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_x,
		    (i >>  -  - (SI_Long)10L) + (SI_Long)2L),i & 
		    (SI_Long)1023L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else
	    copy_managed_float_array_portion(managed_x,FIX((SI_Long)0L),
		    length_x,temp2,FIX((SI_Long)0L));
	gensymed_symbol_2 = FIXNUM_SUB1(number_of_layers);
	change_slot_value(3,y,Qg2_array_length,
		FIXNUM_LE(ISVREF(managed_layer_size_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(managed_layer_size_array,
		IFIX(FIXNUM_ADD(gensymed_symbol_2,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(managed_layer_size_array,
		(IFIX(gensymed_symbol_2) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(gensymed_symbol_2) & (SI_Long)1023L));
	managed_y = ISVREF(y,(SI_Long)23L);
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_layers);
	input_vector = temp2;
	output_vector = temp1;
	number_from = Nil;
	number_to = Nil;
	weights_matrix = Nil;
	current_layer_transfer_function_code = Nil;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	gensymed_symbol = i - (SI_Long)1L;
	number_from = FIXNUM_LE(ISVREF(managed_layer_size_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_layer_size_array,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_layer_size_array,(gensymed_symbol >> 
		 -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	number_to = FIXNUM_LE(ISVREF(managed_layer_size_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(managed_layer_size_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_layer_size_array,(i >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	gensymed_symbol = (i - (SI_Long)1L) * (SI_Long)2L;
	weights_matrix = FIXNUM_LE(ISVREF(managed_weights_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_weights_array,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_weights_array,(gensymed_symbol >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	current_layer_transfer_function_code = 
		FIXNUM_LE(ISVREF(managed_transfer_function_code_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_transfer_function_code_array,i + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_transfer_function_code_array,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	if ( !TRUEP(weights_matrix)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_6,FIX(i - (SI_Long)1L));
	    raw_stack_error_named_error(top_of_stack,message_1);
	    goto end_2;
	}
	aref_arg_1 = ISVREF(input_vector,(IFIX(number_from) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = IFIX(number_from) & (SI_Long)1023L;
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,1.0);
	fill_managed_float_array(output_vector,float_constant);
	k = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(number_from);
	managed_weights_matrix = ISVREF(weights_matrix,(SI_Long)23L);
	weights_row = Nil;
	input_vector_element = Nil;
      next_loop_3:
	if (k > ab_loop_bind__1)
	    goto end_loop_3;
	gensymed_symbol = k * (SI_Long)2L;
	weights_row = ISVREF(FIXNUM_LE(ISVREF(managed_weights_matrix,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_weights_matrix,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_weights_matrix,(gensymed_symbol >>  
		-  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L),(SI_Long)23L);
	input_vector_element = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(input_vector,
		(k >>  -  - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L));
	j = (SI_Long)0L;
	ab_loop_bind__2 = IFIX(FIXNUM_SUB1(number_to));
      next_loop_4:
	if (j > ab_loop_bind__2)
	    goto end_loop_4;
	aref_arg_1 = ISVREF(output_vector,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	aref_arg_2 = j & (SI_Long)1023L;
	temp_1 = DFLOAT_ISAREF_1(ISVREF(output_vector,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	temp_2 = DFLOAT_ISAREF_1(ISVREF(weights_row,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(input_vector_element);
	aref_new_value = temp_1 + temp_2 * temp_3;
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	k = k + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:
	if (IFIX(current_layer_transfer_function_code) == (SI_Long)1L) {
	    j = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(FIXNUM_SUB1(number_to));
	  next_loop_5:
	    if (j > ab_loop_bind__1)
		goto end_loop_5;
	    aref_arg_1 = ISVREF(output_vector,(j >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    aref_arg_2 = j & (SI_Long)1023L;
	    temp = 
		    sigmoidal_transfer_function(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(output_vector,
		    (j >>  -  - (SI_Long)10L) + (SI_Long)2L),j & 
		    (SI_Long)1023L)));
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	    j = j + (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:;
	}
	input_vector = output_vector;
	output_vector = i == IFIX(number_of_layers) - (SI_Long)2L ? 
		managed_y : EQ(output_vector,temp1) ? temp2 : temp1;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
      end_2:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    reclaim_managed_float_array(temp1);
    return reclaim_managed_float_array(temp2);
}

static Object Qweights;            /* weights */

static Object Qcenters;            /* centers */

static Object Qshapes;             /* shapes */

/* G2-EVALUATE-RBFN */
Object g2_evaluate_rbfn(rbfn,x,y)
    Object rbfn, x, y;
{
    Object weights, centers, shapes, managed_shapes, managed_centers;
    Object managed_weights, h, n_out, n_in, hx, hp, managed_diff, managed_ah;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, maximum_activation, current_activation, managed_x;
    Object managed_y, managed_difference, managed_array_2, sqdist;
    Object shape_factor, gensymed_symbol_1, managed_sum, managed_center_vector;
    Object s, f, shape_vector, managed_shape_vector, weight_vector;
    Object managed_weight_vector;
    SI_Long gensymed_symbol, i, ab_loop_bind_, j, ab_loop_bind__1, aref_arg_2;
    SI_Long k, ab_loop_bind__2;
    double aref_new_value, temp_2, temp_3, temp_4, arg, arg_1;

    x_note_fn_call(144,81);
    weights = get_slot_value_function(rbfn,Qweights,Nil);
    centers = get_slot_value_function(rbfn,Qcenters,Nil);
    shapes = get_slot_value_function(rbfn,Qshapes,Nil);
    managed_shapes = ISVREF(shapes,(SI_Long)23L);
    managed_centers = ISVREF(centers,(SI_Long)23L);
    managed_weights = ISVREF(weights,(SI_Long)23L);
    h = ISVREF(centers,(SI_Long)20L);
    n_out = ISVREF(weights,(SI_Long)20L);
    n_in = ISVREF(x,(SI_Long)20L);
    hx = ISVREF(shapes,(SI_Long)20L);
    gensymed_symbol = (SI_Long)0L * (SI_Long)2L;
    hp = ISVREF(FIXNUM_LE(ISVREF(managed_weights,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_weights,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_weights,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L),
	    (SI_Long)20L);
    managed_diff = allocate_managed_float_array(1,n_in);
    managed_ah = allocate_managed_float_array(1,hp);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    maximum_activation = new_float;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    current_activation = new_float;
    managed_x = ISVREF(x,(SI_Long)23L);
    managed_y = ISVREF(y,(SI_Long)23L);
    if (FIXNUM_EQ(hx,h)) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(h);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	managed_difference = new_float;
	managed_array_2 = Nil;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	sqdist = new_float;
	shape_factor = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol_1 = ISVREF(centers,(SI_Long)23L);
	gensymed_symbol = i * (SI_Long)2L;
	managed_array_2 = ISVREF(FIXNUM_LE(ISVREF(ISVREF(centers,
		(SI_Long)23L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(ISVREF(centers,(SI_Long)23L),gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_1,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L),(SI_Long)23L);
	gensymed_symbol = i * (SI_Long)2L;
	shape_factor = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(ISVREF(FIXNUM_LE(ISVREF(managed_shapes,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_shapes,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_shapes,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L),(SI_Long)23L),(SI_Long)2L),(SI_Long)0L));
	DFLOAT_ISASET_1(sqdist,(SI_Long)0L,0.0);
	j = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(n_in);
      next_loop_1:
	if (j >= ab_loop_bind__1)
	    goto end_loop_1;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_x,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L) - 
		DFLOAT_ISAREF_1(ISVREF(managed_array_2,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(managed_difference,(SI_Long)0L,aref_new_value);
	aref_new_value = DFLOAT_ISAREF_1(sqdist,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(managed_difference,(SI_Long)0L) * 
		DFLOAT_ISAREF_1(managed_difference,(SI_Long)0L);
	DFLOAT_ISASET_1(sqdist,(SI_Long)0L,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	temp_2 =  - DFLOAT_ISAREF_1(sqdist,(SI_Long)0L);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(shape_factor);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(shape_factor);
	aref_new_value = exp(temp_2 / (temp_3 * temp_4));
	DFLOAT_ISASET_1(current_activation,(SI_Long)0L,aref_new_value);
	temp = ISVREF(managed_ah,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,aref_arg_2,aref_new_value);
	arg = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(maximum_activation,(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_new_value = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	    DFLOAT_ISASET_1(maximum_activation,(SI_Long)0L,aref_new_value);
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reclaim_managed_simple_float_array_of_length_1(managed_difference);
	reclaim_managed_simple_float_array_of_length_1(sqdist);
    }
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(h);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	managed_sum = new_float;
	managed_center_vector = Nil;
	s = Nil;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_2;
	gensymed_symbol = i * (SI_Long)2L;
	managed_center_vector = ISVREF(FIXNUM_LE(ISVREF(managed_centers,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_centers,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_centers,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L),(SI_Long)23L);
	s = FIX(i * IFIX(n_in));
	j = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(n_in);
      next_loop_3:
	if (j >= ab_loop_bind__1)
	    goto end_loop_3;
	temp = ISVREF(managed_diff,(j >>  -  - (SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = j & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_x,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L) - 
		DFLOAT_ISAREF_1(ISVREF(managed_center_vector,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp,aref_arg_2,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	DFLOAT_ISASET_1(managed_sum,(SI_Long)0L,0.0);
	j = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(n_in);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	f = new_float;
	shape_vector = Nil;
	managed_shape_vector = Nil;
      next_loop_4:
	if (j >= ab_loop_bind__1)
	    goto end_loop_4;
	gensymed_symbol = (IFIX(s) + j) * (SI_Long)2L;
	shape_vector = FIXNUM_LE(ISVREF(managed_shapes,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_shapes,
		gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_shapes,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	managed_shape_vector = ISVREF(shape_vector,(SI_Long)23L);
	DFLOAT_ISASET_1(f,(SI_Long)0L,0.0);
	k = (SI_Long)0L;
	ab_loop_bind__2 = IFIX(n_in);
      next_loop_5:
	if (k >= ab_loop_bind__2)
	    goto end_loop_5;
	aref_new_value = DFLOAT_ISAREF_1(f,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(ISVREF(managed_shape_vector,(k >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L) * 
		DFLOAT_ISAREF_1(ISVREF(managed_diff,(k >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L);
	DFLOAT_ISASET_1(f,(SI_Long)0L,aref_new_value);
	k = k + (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:;
	aref_new_value = DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(f,(SI_Long)0L) * 
		DFLOAT_ISAREF_1(ISVREF(managed_diff,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(managed_sum,(SI_Long)0L,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	reclaim_managed_simple_float_array_of_length_1(f);
	aref_new_value = exp( - DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L));
	DFLOAT_ISASET_1(current_activation,(SI_Long)0L,aref_new_value);
	temp = ISVREF(managed_ah,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,aref_arg_2,aref_new_value);
	arg = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(maximum_activation,(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_new_value = DFLOAT_ISAREF_1(current_activation,(SI_Long)0L);
	    DFLOAT_ISASET_1(maximum_activation,(SI_Long)0L,aref_new_value);
	}
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	reclaim_managed_simple_float_array_of_length_1(managed_sum);
    }
    if (FIXNUM_EQ(hp,FIXNUM_ADD1(h))) {
	temp = ISVREF(managed_ah,(IFIX(h) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	aref_arg_2 = IFIX(h) & (SI_Long)1023L;
	DFLOAT_ISASET_1(temp,aref_arg_2,1.0);
    }
    change_slot_value(3,y,Qg2_array_length,n_out);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_out);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    managed_sum = new_float;
    weight_vector = Nil;
    managed_weight_vector = Nil;
  next_loop_6:
    if (i >= ab_loop_bind_)
	goto end_loop_6;
    gensymed_symbol = i * (SI_Long)2L;
    weight_vector = FIXNUM_LE(ISVREF(managed_weights,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_weights,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_weights,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    managed_weight_vector = ISVREF(weight_vector,(SI_Long)23L);
    DFLOAT_ISASET_1(managed_sum,(SI_Long)0L,0.0);
    j = (SI_Long)0L;
    ab_loop_bind__1 = IFIX(hp);
  next_loop_7:
    if (j >= ab_loop_bind__1)
	goto end_loop_7;
    aref_new_value = DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(ISVREF(managed_weight_vector,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L) * 
	    DFLOAT_ISAREF_1(ISVREF(managed_ah,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(managed_sum,(SI_Long)0L,aref_new_value);
    j = j + (SI_Long)1L;
    goto next_loop_7;
  end_loop_7:;
    temp = ISVREF(managed_y,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
    aref_arg_2 = i & (SI_Long)1023L;
    aref_new_value = DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,aref_arg_2,aref_new_value);
    i = i + (SI_Long)1L;
    goto next_loop_6;
  end_loop_6:
    reclaim_managed_simple_float_array_of_length_1(managed_sum);
    reclaim_managed_float_array(managed_diff);
    reclaim_managed_float_array(managed_ah);
    reclaim_managed_simple_float_array_of_length_1(current_activation);
    return VALUES_1(maximum_activation);
}

static Object string_constant_7;   /* "~a is not a defined class." */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* G2-CREATE-BY-CLONING-NO-RESTRICTIONS */
Object g2_create_by_cloning_no_restrictions(symbol,item_to_clone)
    Object symbol, item_to_clone;
{
    Object class_evaluation_symbol, class_1, class_description_qm;
    Object newly_cloned_item_qm, top_of_stack, message_1, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, text_string, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object sub_class_bit_vector, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5;
    char temp_2;
    Declare_special(7);
    Object result;

    x_note_fn_call(144,82);
    class_evaluation_symbol = symbol;
    class_1 = class_evaluation_symbol;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    newly_cloned_item_qm = Nil;
    if ( !TRUEP(class_description_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_7,
		class_1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if ( !TRUEP(class_can_be_transient_p(class_description_qm))) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L)) {
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    else if ( !TRUEP(class_can_be_transient_p(ISVREF(item_to_clone,
	    (SI_Long)1L)))) {
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
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_12:
	if (level < ab_loop_bind_)
	    goto end_loop_12;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_13:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_14:
	if ( !TRUEP(marked))
	    goto end_loop_13;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_14;
      end_loop_13:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_5;
	goto next_loop_13;
      end_loop_14:
      end_5:
	level = level - (SI_Long)1L;
	goto next_loop_12;
      end_loop_12:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
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
      next_loop_15:
	if (level < ab_loop_bind_)
	    goto end_loop_15;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_16:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_17:
	if ( !TRUEP(marked))
	    goto end_loop_16;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_17;
      end_loop_16:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_6;
	goto next_loop_16;
      end_loop_17:
      end_6:
	level = level - (SI_Long)1L;
	goto next_loop_15;
      end_loop_15:;
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
	  next_loop_18:
	    if (level < ab_loop_bind_)
		goto end_loop_18;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_19:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_20:
	    if ( !TRUEP(marked))
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_20;
	  end_loop_19:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_7;
	    goto next_loop_19;
	  end_loop_20:
	  end_7:
	    level = level - (SI_Long)1L;
	    goto next_loop_18;
	  end_loop_18:;
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
	  next_loop_21:
	    if (level < ab_loop_bind_)
		goto end_loop_21;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_22:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_23:
	    if ( !TRUEP(marked))
		goto end_loop_22;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_23;
	  end_loop_22:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_8;
	    goto next_loop_22;
	  end_loop_23:
	  end_8:
	    level = level - (SI_Long)1L;
	    goto next_loop_21;
	  end_loop_21:;
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
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	if (temp_2);
	else {
	    if (SIMPLE_VECTOR_P(item_to_clone) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_to_clone)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_to_clone,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_to_clone,(SI_Long)1L);
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
	}
	if (temp_2) {
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    newly_cloned_item_qm = clone_frame(1,item_to_clone);
	    if (newly_cloned_item_qm) {
		set_transient_and_propagate(newly_cloned_item_qm,Nil);
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(newly_cloned_item_qm,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
		gensymed_symbol_1 = newly_cloned_item_qm;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    else {
		top_of_stack = Cached_top_of_stack;
		text_string = Nil;
		snapshots = Nil;
		snapshots_of_related_blocks = Nil;
		note_blocks_in_tformat = 
			SYMBOL_FUNCTION(Qrecord_block_for_tformat);
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
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
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
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	}
    }
    return VALUES_1(newly_cloned_item_qm);
}

void arrays_INIT()
{
    Object temp, temp_1, write_g2_array_length_conflict_note_1, temp_2;
    Object gensymed_symbol;
    Object Qg2_create_by_cloning_no_restrictions, AB_package;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qg2_evaluate_rbfn;
    Object Qg2_evaluate_bpn, Qg2_get_position_in_array_of_element;
    Object Qg2_get_position_in_list_of_element;
    Object Qg2_copy_array_elements_to_initial_values, Qquicksort_1;
    Object Qmove_g2_array_elements_to_g2_list, Qconvert_g2_list_to_g2_array;
    Object Qconvert_saved_array_values_to_g2_array_structure, list_constant_6;
    Object Qsymbol_initial_value_marker, Qsymbolic_initial_values;
    Object Qsymbol_initial_value_marker_symbol;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qclasses_which_define;
    Object Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_g2_array;
    Object Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_g2_array, string_constant_53;
    Object list_constant_5, Qlong_array, string_constant_52;
    Object string_constant_49, Qinteger_array, string_constant_51;
    Object string_constant_50, string_constant_48, string_constant_47;
    Object array_constant_1, string_constant_46, Qquantity_array;
    Object string_constant_45, list_constant_4, string_constant_26;
    Object string_constant_44, string_constant_43, Qtruth_value_array;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, Qtext_array, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object Qsymbol_array, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, Qvalue_array;
    Object string_constant_30, list_constant_3, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_25;
    Object string_constant_24, Qslot_putter, Qput_g2_array_element_type;
    Object Qg2_array_element_type, Qput_g2_array_initial_values;
    Object Qframe_note_writer_1, Qput_array_is_permanent, Qarray_is_permanent;
    Object Qput_g2_array_length, Qslot_value_reclaimer;
    Object Qreclaim_managed_g2_array_value, Qmanaged_g2_array, Qinitial_values;
    Object Qelement_type, Qarray_length, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object list_constant_2, Qcreate_icon_description, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, Qobject;

    x_note_fn_call(144,83);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_2 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qg2_array,list_constant_2);
    string_constant_8 = 
	    STATIC_STRING("1n1m8v831Yy1l8t1m83-Cy532-yThe original parts document showed the following attributes for g2-array: reconcile.\n<ul>\n<LI>array l");
    string_constant_9 = 
	    STATIC_STRING("ength: integer, <!--from g2-array-length -->\n<LI>element type: symbol, <!--from g2-array-element-type -->\n<LI>initial values: (i");
    string_constant_10 = 
	    STATIC_STRING("tem-or-value *) <!--from g2-array-initial-values-->\n<LI>values (item-or-value *) ; A sequence of the values in the array. <!--fr");
    string_constant_11 = STATIC_STRING("om managed-g2-array-->\n</ul>");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_12 = 
	    STATIC_STRING("1q4z8r835Ey835Ey831Yy831Yy0k001o1l8o1m8p835Ey1l8l1l8z000004z8r83-vy83-vy831Yy831Yy083=Ky001o1l8o1m8p83-Xy1l8l1l83Fy000004z8r83-w");
    string_constant_13 = 
	    STATIC_STRING("y83-wy831Yy831Yy00001p1l8o1m8p839Ly1l8l1l8z1l83Cy000004z8r83Uhy83Uhy831Yy831Yy00001r1l8o1l8l1m8p835fy1l83Uy1l83Cy1l83Ny1l83Fy000");
    string_constant_14 = 
	    STATIC_STRING("004z8r837hy837hy831Yy831Yy00001o1l8o1l8l1l8z1m8p83Ky000004z8r8u8u831Yy831Yy01p8w9k3uy3uy1v1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1m");
    string_constant_15 = 
	    STATIC_STRING("zz1mz3fy1n83Oy1m3Lyz1m3Ly3fy1n83Oy1m3fyz1m3fy3fy1n83Oy1mzz1m3fyz1n83Oy1mz3Gy1m3fy3Gy1n83Oy1mz3Ly1m3fy3Ly1n83Oy1mz3Qy1m3fy3Qy1n83");
    string_constant_16 = 
	    STATIC_STRING("Oy1mz3Vy1m3fy3Vy1n83Oy1mz3ay1m3fy3ay1n83Oy1mz3fy1m3fy3fy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_17 = 
	    STATIC_STRING("1s8q1p831Yy1l83-Oy1m8v831Yy8t1m83-Cy532-yThe original parts document showed the following attributes for g2-array: reconcile.\n<u");
    string_constant_18 = 
	    STATIC_STRING("l>\n<LI>array length: integer, <!--from g2-array-length -->\n<LI>element type: symbol, <!--from g2-array-element-type -->\n<LI>init");
    string_constant_19 = 
	    STATIC_STRING("ial values: (item-or-value *) <!--from g2-array-initial-values-->\n<LI>values (item-or-value *) ; A sequence of the values in the");
    string_constant_20 = 
	    STATIC_STRING(" array. <!--from managed-g2-array-->\n</ul>1q835Eyk8o1m8p835Ey8l8z1q83-vy83=Ky8o1m8p83-Xy8l83Fy1r83-wy08o1m8p839Ly8l8z83Cy1t83Uhy");
    string_constant_21 = 
	    STATIC_STRING("08o8l1m8p835fy83Uy83Cy83Ny83Fy1q837hy08o8l8z1m8p83Ky1m8u1p8w9k3uy3uy1v1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mzz1mz3fy1n83Oy1m3Lyz");
    string_constant_22 = 
	    STATIC_STRING("1m3Ly3fy1n83Oy1m3fyz1m3fy3fy1n83Oy1mzz1m3fyz1n83Oy1mz3Gy1m3fy3Gy1n83Oy1mz3Ly1m3fy3Ly1n83Oy1mz3Qy1m3fy3Qy1n83Oy1mz3Vy1m3fy3Vy1n83");
    string_constant_23 = STATIC_STRING("Oy1mz3ay1m3fy3ay1n83Oy1mz3fy1m3fy3fy");
    temp = regenerate_optimized_constant(LIST_4(string_constant_8,
	    string_constant_9,string_constant_10,string_constant_11));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qg2_array,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,regenerate_optimized_constant(list(7,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23)),Nil);
    G2_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_array,
	    Class_description_gkbprop);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qarray_length = STATIC_SYMBOL("ARRAY-LENGTH",AB_package);
    alias_slot_name(3,Qg2_array_length,Qarray_length,Qg2_array);
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    alias_slot_name(3,Qg2_array_element_type,Qelement_type,Qg2_array);
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    Qinitial_values = STATIC_SYMBOL("INITIAL-VALUES",AB_package);
    alias_slot_name(3,Qg2_array_initial_values,Qinitial_values,Qg2_array);
    Qmanaged_g2_array = STATIC_SYMBOL("MANAGED-G2-ARRAY",AB_package);
    Qreclaim_managed_g2_array_value = 
	    STATIC_SYMBOL("RECLAIM-MANAGED-G2-ARRAY-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_managed_g2_array_value,
	    STATIC_FUNCTION(reclaim_managed_g2_array_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qmanaged_g2_array,
	    SYMBOL_FUNCTION(Qreclaim_managed_g2_array_value),
	    Qslot_value_reclaimer);
    Qg2_array_length_conflict = STATIC_SYMBOL("G2-ARRAY-LENGTH-CONFLICT",
	    AB_package);
    Qput_g2_array_length = STATIC_SYMBOL("PUT-G2-ARRAY-LENGTH",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_array_length,
	    STATIC_FUNCTION(put_g2_array_length,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qg2_array_length,
	    SYMBOL_FUNCTION(Qput_g2_array_length),Qslot_putter);
    Qarray_is_permanent = STATIC_SYMBOL("ARRAY-IS-PERMANENT",AB_package);
    Qput_array_is_permanent = STATIC_SYMBOL("PUT-ARRAY-IS-PERMANENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_array_is_permanent,
	    STATIC_FUNCTION(put_array_is_permanent,NIL,FALSE,3,3));
    mutate_global_property(Qarray_is_permanent,
	    SYMBOL_FUNCTION(Qput_array_is_permanent),Qslot_putter);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    string_constant = 
	    string_append2(STATIC_STRING("a default initial value of ~NC will be used because ~\n              there is more than one initial value and the array-length, ~d, ~\n              is not equal to the number o"),
	    STATIC_STRING("f these values, ~d"));
    write_g2_array_length_conflict_note_1 = 
	    STATIC_FUNCTION(write_g2_array_length_conflict_note,NIL,FALSE,2,2);
    mutate_global_property(Qg2_array_length_conflict,
	    write_g2_array_length_conflict_note_1,Qframe_note_writer_1);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qput_g2_array_initial_values = 
	    STATIC_SYMBOL("PUT-G2-ARRAY-INITIAL-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_array_initial_values,
	    STATIC_FUNCTION(put_g2_array_initial_values,NIL,FALSE,3,3));
    mutate_global_property(Qg2_array_initial_values,
	    SYMBOL_FUNCTION(Qput_g2_array_initial_values),Qslot_putter);
    Qput_g2_array_element_type = STATIC_SYMBOL("PUT-G2-ARRAY-ELEMENT-TYPE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_array_element_type,
	    STATIC_FUNCTION(put_g2_array_element_type,NIL,FALSE,3,3));
    mutate_global_property(Qg2_array_element_type,
	    SYMBOL_FUNCTION(Qput_g2_array_element_type),Qslot_putter);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    list_constant_3 = STATIC_CONS(Qg2_array,Qnil);
    check_if_superior_classes_are_defined(Qitem_array,list_constant_3);
    string_constant_24 = STATIC_STRING("1l1m8v834Fy");
    string_constant_25 = 
	    STATIC_STRING("1m4z8r83-vy83-vy834Fy834Fy083Ry001p1l8l1l83Fy1l8z1l8o1m8p83-Xy000004z8r83-wy83-wy834Fy834Fy00001p1l8l1m8p836jy1l8o1l8z1l83Cy0000");
    string_constant_26 = STATIC_STRING("0");
    string_constant_27 = 
	    STATIC_STRING("1o8q1n834Fy1l831Yy1m8v834Fy1o83-vy83Ry83Fy8z1n83-wy01m8p836jy");
    temp = regenerate_optimized_constant(string_constant_24);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_25,
	    string_constant_26));
    add_class_to_environment(9,Qitem_array,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_27),Nil);
    Item_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qitem_array,
	    Class_description_gkbprop);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qvalue_array,list_constant_3);
    string_constant_28 = STATIC_STRING("1l1m8v830vy");
    array_constant_1 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_1,(SI_Long)0L,0.0);
    string_constant_29 = 
	    STATIC_STRING("1m4z8r83-vy83-vy830vy830vy083=oy001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy830vy830vy01l9k001p1l8l1m8p839Ky1l8o1l8z1l83Cy0000");
    float_constant = STATIC_FLOAT(0.0);
    string_constant_30 = 
	    STATIC_STRING("1o8q1n830vy1l831Yy1m8v830vy1m83-vy83=oy1n83-wy1l9k1m8p839Ky");
    temp = regenerate_optimized_constant(string_constant_28);
    clear_optimized_constants();
    push_optimized_constant(array_constant_1);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_29,
	    string_constant_26));
    clear_optimized_constants();
    push_optimized_constant(float_constant);
    add_class_to_environment(9,Qvalue_array,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_30),Nil);
    Value_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qvalue_array,
	    Class_description_gkbprop);
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    list_constant_4 = STATIC_CONS(Qvalue_array,Qnil);
    check_if_superior_classes_are_defined(Qsymbol_array,list_constant_4);
    string_constant_31 = STATIC_STRING("1l1m8v834dy");
    string_constant_32 = 
	    STATIC_STRING("1m4z8r83-vy83-vy834dy834dy083-2y001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy834dy834dy01l830Jy001p1l8l1m8p831ky1l8o1l8z1l83Cy0");
    string_constant_33 = STATIC_STRING("0000");
    string_constant_34 = 
	    STATIC_STRING("1o8q1n834dy1l830vy1m8v834dy1m83-vy83-2y1n83-wy1l830Jy1m8p831ky");
    temp = regenerate_optimized_constant(string_constant_31);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_32,
	    string_constant_33));
    add_class_to_environment(9,Qsymbol_array,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_34),Nil);
    Symbol_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsymbol_array,
	    Class_description_gkbprop);
    Qtext_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qtext_array,list_constant_4);
    string_constant_35 = STATIC_STRING("1l1m8v834hy");
    string_constant_36 = 
	    STATIC_STRING("1m4z8r83-vy83-vy834hy834hy083Gy001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy834hy834hy01l+skkkkkkk3A++y001p1l8l1m8p837fy1l8o1l8");
    string_constant_37 = STATIC_STRING("z1l83Cy00000");
    string_constant_38 = 
	    STATIC_STRING("1o8q1n834hy1l830vy1m8v834hy1m83-vy83Gy1n83-wy1l5k1m8p837fy");
    temp = regenerate_optimized_constant(string_constant_35);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_36,
	    string_constant_37));
    add_class_to_environment(9,Qtext_array,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_38),Nil);
    Text_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtext_array,
	    Class_description_gkbprop);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qtruth_value_array,list_constant_4);
    string_constant_39 = STATIC_STRING("1l1m8v834ly");
    string_constant_40 = 
	    STATIC_STRING("1m4z8r83-vy83-vy834ly834ly083-hy001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy834ly834ly01l3Baz001p1l8l1m8p831my1l8o1l8z1l83Cy00");
    string_constant_41 = STATIC_STRING("000");
    string_constant_42 = 
	    STATIC_STRING("1o8q1n834ly1l830vy1m8v834ly1m83-vy83-hy1n83-wy1l3Baz1m8p831my");
    temp = regenerate_optimized_constant(string_constant_39);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_41));
    add_class_to_environment(9,Qtruth_value_array,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_42),Nil);
    Truth_value_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtruth_value_array,
	    Class_description_gkbprop);
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qquantity_array,list_constant_4);
    string_constant_43 = STATIC_STRING("1l1m8v8316y");
    string_constant_44 = 
	    STATIC_STRING("1m4z8r83-vy83-vy8316y8316y083-Hy001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy8316y8316y01l9k001p1l8l1m8p830Qy1l8o1l8z1l83Cy0000");
    string_constant_45 = 
	    STATIC_STRING("1o8q1n8316y1l830vy1m8v8316y1m83-vy83-Hy1n83-wy1l9k1m8p830Qy");
    temp = regenerate_optimized_constant(string_constant_43);
    clear_optimized_constants();
    push_optimized_constant(array_constant_1);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_44,
	    string_constant_26));
    clear_optimized_constants();
    push_optimized_constant(float_constant);
    add_class_to_environment(9,Qquantity_array,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_45),Nil);
    Quantity_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qquantity_array,
	    Class_description_gkbprop);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    list_constant_5 = STATIC_CONS(Qquantity_array,Qnil);
    check_if_superior_classes_are_defined(Qfloat_array,list_constant_5);
    string_constant_46 = STATIC_STRING("1l1m8v833wy");
    string_constant_47 = 
	    STATIC_STRING("1m4z8r83-vy83-vy833wy833wy09k001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy833wy833wy01l9l001p1l8l1m8p831Xy1l8o1l8z1l83Cy00000");
    string_constant_48 = 
	    STATIC_STRING("1o8q1n833wy1l8316y1m8v833wy1m83-vy9k1n83-wy1l9l1m8p831Xy");
    temp = regenerate_optimized_constant(string_constant_46);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(array_constant_1);
    temp_1 = regenerate_optimized_constant(string_constant_47);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(float_constant);
    add_class_to_environment(9,Qfloat_array,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_48),Nil);
    Float_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qfloat_array,
	    Class_description_gkbprop);
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qinteger_array,list_constant_5);
    string_constant_49 = STATIC_STRING("1l1m8v831cy");
    string_constant_50 = 
	    STATIC_STRING("1m4z8r83-vy83-vy831cy831cy083Sy001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy831cy831cy01lk001p1l8l1m8p831dy1l8o1l8z1l83Cy00000");
    string_constant_51 = 
	    STATIC_STRING("1o8q1n831cy1l8316y1m8v831cy1m83-vy83Sy1n83-wy1lk1m8p831dy");
    temp = regenerate_optimized_constant(string_constant_49);
    temp_1 = regenerate_optimized_constant(string_constant_50);
    add_class_to_environment(9,Qinteger_array,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_51),Nil);
    Integer_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinteger_array,
	    Class_description_gkbprop);
    Qlong_array = STATIC_SYMBOL("LONG-ARRAY",AB_package);
    check_if_superior_classes_are_defined(Qlong_array,list_constant_5);
    string_constant_52 = 
	    STATIC_STRING("1m4z8r83-vy83-vy83URy83URy083=By001o1l8l1l8o1m8p83-Xy1l83Fy000004z8r83-wy83-wy83URy83URy01lk001p1l8l1m8p83USy1l8o1l8z1l83Cy00000");
    string_constant_53 = 
	    STATIC_STRING("1o8q1n83URy1l8316y1m8v831cy1m83-vy83=By1n83-wy1lk1m8p83USy");
    temp = regenerate_optimized_constant(string_constant_49);
    temp_1 = regenerate_optimized_constant(string_constant_52);
    add_class_to_environment(9,Qlong_array,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_53),Nil);
    Qactivate_subclass_of_entity_for_g2_array = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_g2_array,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_g2_array,NIL,
	    FALSE,1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_g2_array);
    set_get(Qg2_array,Qactivate_subclass_of_entity,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_array,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_g2_array = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-G2-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_g2_array,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_g2_array,NIL,
	    FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_g2_array);
    set_get(Qg2_array,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_array,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    list_constant = STATIC_LIST((SI_Long)3L,Qsymbol,Qtruth_value,Qinteger);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qtext,Qnumber,Qquantity,Qdatum);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_initial_value_marker_symbol = 
	    STATIC_SYMBOL("SYMBOL-INITIAL-VALUE-MARKER-SYMBOL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsymbol_initial_value_marker_symbol,
	    Symbol_initial_value_marker_symbol);
    Qsymbolic_initial_values = STATIC_SYMBOL("SYMBOLIC-INITIAL-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE(Qsymbol_initial_value_marker_symbol,
	    Qsymbolic_initial_values);
    Qsymbol_initial_value_marker = 
	    STATIC_SYMBOL("SYMBOL-INITIAL-VALUE-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsymbol_initial_value_marker,
	    Symbol_initial_value_marker);
    SET_SYMBOL_VALUE(Qsymbol_initial_value_marker,
	    LIST_1(Symbol_initial_value_marker_symbol));
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_6,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qframe_denotation = STATIC_SYMBOL("FRAME-DENOTATION",AB_package);
    Qconvert_saved_array_values_to_g2_array_structure = 
	    STATIC_SYMBOL("CONVERT-SAVED-ARRAY-VALUES-TO-G2-ARRAY-STRUCTURE",
	    AB_package);
    temp_2 = adjoin(2,Qconvert_saved_array_values_to_g2_array_structure,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qconvert_saved_array_values_to_g2_array_structure,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qconvert_saved_array_values_to_g2_array_structure,
	    STATIC_FUNCTION(convert_saved_array_values_to_g2_array_structure,
	    NIL,FALSE,0,0));
    if (Do_not_initialize_g2_array_elements_p == UNBOUND)
	Do_not_initialize_g2_array_elements_p = Nil;
    Qcloned_managed_array = STATIC_SYMBOL("CLONED-MANAGED-ARRAY",AB_package);
    Qconvert_g2_list_to_g2_array = 
	    STATIC_SYMBOL("CONVERT-G2-LIST-TO-G2-ARRAY",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qconvert_g2_list_to_g2_array,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qconvert_g2_list_to_g2_array,
	    STATIC_FUNCTION(convert_g2_list_to_g2_array,NIL,FALSE,1,1));
    Qmove_g2_array_elements_to_g2_list = 
	    STATIC_SYMBOL("MOVE-G2-ARRAY-ELEMENTS-TO-G2-LIST",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qmove_g2_array_elements_to_g2_list,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qmove_g2_array_elements_to_g2_list,
	    STATIC_FUNCTION(move_g2_array_elements_to_g2_list,NIL,FALSE,2,2));
    Quicksort_verbose_p = Nil;
    Insertion_sort_array_size = FIX((SI_Long)7L);
    Qquicksort_1 = STATIC_SYMBOL("QUICKSORT-1",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qquicksort_1,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_1 = 
	    STATIC_STRING("Sorting a list or array containing NaNs with no ~\n                      comparison function is undefined.");
    SET_SYMBOL_FUNCTION(Qquicksort_1,STATIC_FUNCTION(quicksort_1,NIL,FALSE,
	    6,6));
    Qg2_copy_array_elements_to_initial_values = 
	    STATIC_SYMBOL("G2-COPY-ARRAY-ELEMENTS-TO-INITIAL-VALUES",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_copy_array_elements_to_initial_values,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_2 = 
	    STATIC_STRING("Cannot copy the array elements of ~NF into its initial-values attribute.");
    string_constant_3 = 
	    STATIC_STRING(" A permanent array cannot be initialized.");
    string_constant_4 = STATIC_STRING("  An array element has no value.");
    string_constant_5 = 
	    STATIC_STRING("  An array element, ~NF, cannot be an initial value.  It must either ~\n                 have a name or be an attribute of a named item.");
    SET_SYMBOL_FUNCTION(Qg2_copy_array_elements_to_initial_values,
	    STATIC_FUNCTION(g2_copy_array_elements_to_initial_values,NIL,
	    FALSE,1,1));
    Qg2_get_position_in_list_of_element = 
	    STATIC_SYMBOL("G2-GET-POSITION-IN-LIST-OF-ELEMENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_position_in_list_of_element,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_position_in_list_of_element,
	    STATIC_FUNCTION(g2_get_position_in_list_of_element,NIL,FALSE,2,2));
    Qg2_get_position_in_array_of_element = 
	    STATIC_SYMBOL("G2-GET-POSITION-IN-ARRAY-OF-ELEMENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_position_in_array_of_element,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_position_in_array_of_element,
	    STATIC_FUNCTION(g2_get_position_in_array_of_element,NIL,FALSE,
	    2,2));
    float_constant_1 = STATIC_FLOAT(-1.0);
    float_constant_2 = STATIC_FLOAT(1.0);
    Qg2_evaluate_bpn = STATIC_SYMBOL("G2-EVALUATE-BPN",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_evaluate_bpn,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qtransfer_fns = STATIC_SYMBOL("TRANSFER-FNS",AB_package);
    Qlayer_sizes = STATIC_SYMBOL("LAYER-SIZES",AB_package);
    Qweight_array = STATIC_SYMBOL("WEIGHT-ARRAY",AB_package);
    string_constant_6 = 
	    STATIC_STRING("Invalid BPN, missing weights matrix at index ~a");
    SET_SYMBOL_FUNCTION(Qg2_evaluate_bpn,STATIC_FUNCTION(g2_evaluate_bpn,
	    NIL,FALSE,3,3));
    Qg2_evaluate_rbfn = STATIC_SYMBOL("G2-EVALUATE-RBFN",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_evaluate_rbfn,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qweights = STATIC_SYMBOL("WEIGHTS",AB_package);
    Qcenters = STATIC_SYMBOL("CENTERS",AB_package);
    Qshapes = STATIC_SYMBOL("SHAPES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_evaluate_rbfn,STATIC_FUNCTION(g2_evaluate_rbfn,
	    NIL,FALSE,3,3));
    Qg2_create_by_cloning_no_restrictions = 
	    STATIC_SYMBOL("G2-CREATE-BY-CLONING-NO-RESTRICTIONS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_create_by_cloning_no_restrictions,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_7 = STATIC_STRING("~a is not a defined class.");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_create_by_cloning_no_restrictions,
	    STATIC_FUNCTION(g2_create_by_cloning_no_restrictions,NIL,FALSE,
	    2,2));
}
