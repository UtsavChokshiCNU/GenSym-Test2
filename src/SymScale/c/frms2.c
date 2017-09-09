/* frms2.c
 * Input file:  frames2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "frms2.h"


DEFINE_VARIABLE_WITH_SYMBOL(Last_system_class_bit_number, Qlast_system_class_bit_number);

DEFINE_VARIABLE_WITH_SYMBOL(Next_class_bit_number, Qnext_class_bit_number);

/* INITIALIZE-CLASSES-VISITED-BYTE-VECTOR */
Object initialize_classes_visited_byte_vector()
{
    SI_Long temp;

    x_note_fn_call(81,0);
    temp = (IFIX(Next_class_bit_number) + ((SI_Long)8L - (SI_Long)1L)) / 
	    (SI_Long)8L;
    return allocate_byte_vector(FIX(temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Classes_visited_byte_vector, Qclasses_visited_byte_vector);

static Object Qframe;              /* frame */

/* GET-NEXT-CLASS-BIT-NUMBER */
Object get_next_class_bit_number()
{
    Object frame_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;
    SI_Long temp_2, needed_length;

    x_note_fn_call(81,1);
    if (Class_bit_numbers_pool) {
	frame_pop_store = Nil;
	cons_1 = Class_bit_numbers_pool;
	if (cons_1) {
	    frame_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qframe);
	    if (ISVREF(Available_frame_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_frame_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_frame_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_frame_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Class_bit_numbers_pool = next_cons;
	return VALUES_1(frame_pop_store);
    }
    else {
	temp_1 = Next_class_bit_number;
	atomic_incff_symval(Qnext_class_bit_number,FIX((SI_Long)1L));
	temp_2 = (IFIX(Next_class_bit_number) + ((SI_Long)8L - 
		(SI_Long)1L)) / (SI_Long)8L;
	needed_length = temp_2;
	if (Classes_visited_byte_vector) {
	    if ( 
		    !(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Classes_visited_byte_vector)) 
		    >= needed_length)) {
		reclaim_byte_vector(Classes_visited_byte_vector);
		Classes_visited_byte_vector = Nil;
	    }
	}
	if ( !TRUEP(Classes_visited_byte_vector))
	    Classes_visited_byte_vector = 
		    allocate_byte_vector(FIX(needed_length));
	return VALUES_1(temp_1);
    }
}

static Object Qroot;               /* root */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* ASSIGN-CLASS-BIT-NUMBERS-AND-VECTORS-TO-SYSTEM-CLASSES */
Object assign_class_bit_numbers_and_vectors_to_system_classes()
{
    Object current_class_bit_number, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loopvar__3, class_1, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, ab_loopvar__4, current_classes_variable_set;
    Object sublist, class_to_add, superior, ab_loop_list_, ab_loop_it_;
    Object class_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(81,2);
    current_class_bit_number = FIX((SI_Long)0L);
    if (Class_bit_numbers_pool) {
	reclaim_frame_list_1(Class_bit_numbers_pool);
	Class_bit_numbers_pool = Nil;
    }
    scope_conses = Scope_conses;
    ab_loopvar_ = Qroot;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      if (SYMBOLP(ab_loopvar_)) {
	  skip_list = CDR(Symbol_properties_table);
	  key_value = ab_loopvar_;
	  key_hash_value = SXHASH_SYMBOL_1(ab_loopvar_) & 
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = ab_loopvar_;
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
	  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		  ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (kb_properties);
	  else
	      kb_properties = Nil;
	  if (kb_properties) {
	      skip_list = CDR(kb_properties);
	      key_value = Class_description_gkbprop;
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	  temp_3 = TRUEP(resulting_value);
      }
      else
	  temp_3 = TRUEP(Nil);
      ab_loopvar__3 = temp_3 ? scope_cons(ab_loopvar_,Nil) : Nil;
    next_loop_12:
      if ( !TRUEP(ab_loopvar__3))
	  goto end_loop_12;
      temp_1 = M_CAR(ab_loopvar__3);
      ab_loopvar__2 = scope_cons(M_CAR(ab_loopvar__3),ab_loopvar__2);
      ab_loopvar__4 = 
	      lookup_global_or_kb_specific_property_value(M_CAR(ab_loopvar__3),
	      Inferior_classes_gkbprop);
      if (ab_loopvar__4) {
	  temp = ab_loopvar__1;
	  ab_loopvar__1 = nconc2(temp,scope_cons(ab_loopvar__4,Nil));
      }
      ab_loopvar__3 = M_CDR(ab_loopvar__3);
      current_classes_variable_set = Nil;
    next_loop_13:
      if (current_classes_variable_set)
	  goto end_loop_13;
      sublist = ab_loopvar__3;
      class_to_add = Nil;
    next_loop_14:
      if ( !TRUEP(sublist))
	  goto end_loop_14;
      class_to_add = M_CAR(sublist);
      if ( !TRUEP(sublist))
	  goto end_loop_14;
      temp_3 = TRUEP(memq_function(M_CAR(sublist),ab_loopvar__2));
      if (temp_3);
      else {
	  superior = Nil;
	  ab_loop_list_ = 
		  lookup_global_or_kb_specific_property_value(class_to_add,
		  Direct_superior_classes_gkbprop);
	  ab_loop_it_ = Nil;
	next_loop_15:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_15;
	  superior = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(superior,
		  Class_description_gkbprop);
	  ab_loop_it_ = (gensymed_symbol ? TRUEP(memq_function(ab_loopvar_,
		  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? ( 
		  !TRUEP(memq_function(superior,ab_loopvar__2)) ? T : Nil) 
		  : Nil;
	  if (ab_loop_it_) {
	      temp_3 = TRUEP(ab_loop_it_);
	      goto end_5;
	  }
	  goto next_loop_15;
	end_loop_15:
	  temp_3 = TRUEP(Qnil);
	end_5:;
      }
      if ( !temp_3) {
	  ab_loopvar__3 = sublist;
	  current_classes_variable_set = T;
	  goto end_loop_14;
      }
      sublist = M_CDR(sublist);
      goto next_loop_14;
    end_loop_14:
      if ( !TRUEP(current_classes_variable_set)) {
	  ab_loopvar__3 = CAR(ab_loopvar__1);
	  if (ab_loopvar__1)
	      ab_loopvar__1 = M_CDR(ab_loopvar__1);
	  else
	      current_classes_variable_set = T;
      }
      goto next_loop_13;
    end_loop_13:;
      class_1 = temp_1;
      temp_2 = lookup_global_or_kb_specific_property_value(class_1,
	      Class_description_gkbprop);
      SVREF(temp_2,FIX((SI_Long)18L)) = current_class_bit_number;
      current_class_bit_number = FIXNUM_ADD1(current_class_bit_number);
      goto next_loop_12;
    end_loop_12:;
    POP_SPECIAL();
    Next_class_bit_number = current_class_bit_number;
    Last_system_class_bit_number = FIXNUM_SUB1(current_class_bit_number);
    scope_conses = Scope_conses;
    ab_loopvar_ = Qroot;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      class_description = Nil;
      if (SYMBOLP(ab_loopvar_)) {
	  skip_list = CDR(Symbol_properties_table);
	  key_value = ab_loopvar_;
	  key_hash_value = SXHASH_SYMBOL_1(ab_loopvar_) & 
		  IFIX(Most_positive_fixnum);
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
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = ab_loopvar_;
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
	next_loop_19:
	  if (level < ab_loop_bind_)
	      goto end_loop_19;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_20:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp,temp_1);
	  MVS_2(result,succ,marked);
	next_loop_21:
	  if ( !TRUEP(marked))
	      goto end_loop_20;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp,temp_1);
	  MVS_2(result,succ,marked);
	  goto next_loop_21;
	end_loop_20:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		  ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (kb_properties);
	  else
	      kb_properties = Nil;
	  if (kb_properties) {
	      skip_list = CDR(kb_properties);
	      key_value = Class_description_gkbprop;
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_23:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp,temp_1);
	      MVS_2(result,succ,marked);
	    next_loop_24:
	      if ( !TRUEP(marked))
		  goto end_loop_23;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp,temp_1);
	      MVS_2(result,succ,marked);
	      goto next_loop_24;
	    end_loop_23:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if (resulting_value);
	      else
		  resulting_value = Nil;
	  }
	  temp_3 = TRUEP(resulting_value);
      }
      else
	  temp_3 = TRUEP(Nil);
      ab_loopvar__3 = temp_3 ? scope_cons(ab_loopvar_,Nil) : Nil;
    next_loop_28:
      if ( !TRUEP(ab_loopvar__3))
	  goto end_loop_28;
      temp_1 = M_CAR(ab_loopvar__3);
      ab_loopvar__2 = scope_cons(M_CAR(ab_loopvar__3),ab_loopvar__2);
      ab_loopvar__4 = 
	      lookup_global_or_kb_specific_property_value(M_CAR(ab_loopvar__3),
	      Inferior_classes_gkbprop);
      if (ab_loopvar__4) {
	  temp = ab_loopvar__1;
	  ab_loopvar__1 = nconc2(temp,scope_cons(ab_loopvar__4,Nil));
      }
      ab_loopvar__3 = M_CDR(ab_loopvar__3);
      current_classes_variable_set = Nil;
    next_loop_29:
      if (current_classes_variable_set)
	  goto end_loop_29;
      sublist = ab_loopvar__3;
      class_to_add = Nil;
    next_loop_30:
      if ( !TRUEP(sublist))
	  goto end_loop_30;
      class_to_add = M_CAR(sublist);
      if ( !TRUEP(sublist))
	  goto end_loop_30;
      temp_3 = TRUEP(memq_function(M_CAR(sublist),ab_loopvar__2));
      if (temp_3);
      else {
	  superior = Nil;
	  ab_loop_list_ = 
		  lookup_global_or_kb_specific_property_value(class_to_add,
		  Direct_superior_classes_gkbprop);
	  ab_loop_it_ = Nil;
	next_loop_31:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_31;
	  superior = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(superior,
		  Class_description_gkbprop);
	  ab_loop_it_ = (gensymed_symbol ? TRUEP(memq_function(ab_loopvar_,
		  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? ( 
		  !TRUEP(memq_function(superior,ab_loopvar__2)) ? T : Nil) 
		  : Nil;
	  if (ab_loop_it_) {
	      temp_3 = TRUEP(ab_loop_it_);
	      goto end_10;
	  }
	  goto next_loop_31;
	end_loop_31:
	  temp_3 = TRUEP(Qnil);
	end_10:;
      }
      if ( !temp_3) {
	  ab_loopvar__3 = sublist;
	  current_classes_variable_set = T;
	  goto end_loop_30;
      }
      sublist = M_CDR(sublist);
      goto next_loop_30;
    end_loop_30:
      if ( !TRUEP(current_classes_variable_set)) {
	  ab_loopvar__3 = CAR(ab_loopvar__1);
	  if (ab_loopvar__1)
	      ab_loopvar__1 = M_CDR(ab_loopvar__1);
	  else
	      current_classes_variable_set = T;
      }
      goto next_loop_29;
    end_loop_29:;
      class_1 = temp_1;
      class_description = 
	      lookup_global_or_kb_specific_property_value(class_1,
	      Class_description_gkbprop);
      temp_2 = make_class_bit_vector(ISVREF(class_description,
	      (SI_Long)18L),ISVREF(class_description,(SI_Long)2L));
      SVREF(class_description,FIX((SI_Long)19L)) = temp_2;
      goto next_loop_28;
    end_loop_28:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* MAKE-CLASS-BIT-VECTOR */
Object make_class_bit_vector(class_bit_number,class_inheritance_path)
    Object class_bit_number, class_inheritance_path;
{
    Object superior_classes, number_of_bytes, superior_class, ab_loop_list_;
    Object length_needed_for_superior_bit, required_bytes_for_vector;
    Object class_bit_vector, superior_class_bit_number;
    Object vector_index_for_superior;
    SI_Long vector_index_for_class, index_1, gensymed_symbol;
    SI_Long gensymed_symbol_1, aref_new_value;

    x_note_fn_call(81,3);
    superior_classes = CDR(class_inheritance_path);
    vector_index_for_class = IFIX(class_bit_number) >>  -  - (SI_Long)3L;
    number_of_bytes = FIX(vector_index_for_class + (SI_Long)1L);
    superior_class = Nil;
    ab_loop_list_ = superior_classes;
    length_needed_for_superior_bit = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    length_needed_for_superior_bit = 
	    FIX((IFIX(ISVREF(lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop),(SI_Long)18L)) >>  -  - 
	    (SI_Long)3L) + (SI_Long)1L);
    number_of_bytes = FIXNUM_MAX(number_of_bytes,
	    length_needed_for_superior_bit);
    goto next_loop;
  end_loop:
    required_bytes_for_vector = number_of_bytes;
    goto end_1;
    required_bytes_for_vector = Qnil;
  end_1:;
    class_bit_vector = allocate_byte_vector(required_bytes_for_vector);
    index_1 = IFIX(FIXNUM_SUB1(SIMPLE_ARRAY_ANY_1_LENGTH(class_bit_vector)));
  next_loop_1:
    if (index_1 < (SI_Long)0L)
	goto end_loop_1;
    UBYTE_8_ISASET_1(class_bit_vector,index_1,(SI_Long)0L);
    index_1 = index_1 - (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    gensymed_symbol = (SI_Long)1L;
    gensymed_symbol_1 = IFIX(class_bit_number) & (SI_Long)7L;
    aref_new_value = UBYTE_8_ISAREF_1(class_bit_vector,
	    vector_index_for_class) | gensymed_symbol << gensymed_symbol_1;
    UBYTE_8_ISASET_1(class_bit_vector,vector_index_for_class,aref_new_value);
    superior_class = Nil;
    ab_loop_list_ = superior_classes;
    superior_class_bit_number = Nil;
    vector_index_for_superior = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    superior_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    superior_class_bit_number = 
	    ISVREF(lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop),(SI_Long)18L);
    vector_index_for_superior = FIX(IFIX(superior_class_bit_number) >>  -  
	    - (SI_Long)3L);
    gensymed_symbol = (SI_Long)1L;
    gensymed_symbol_1 = IFIX(superior_class_bit_number) & (SI_Long)7L;
    aref_new_value = UBYTE_8_ISAREF_1(class_bit_vector,
	    IFIX(vector_index_for_superior)) | gensymed_symbol << 
	    gensymed_symbol_1;
    UBYTE_8_ISASET_1(class_bit_vector,IFIX(vector_index_for_superior),
	    aref_new_value);
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(class_bit_vector);
}

/* COLLECT-SUBCLASSES */
Object collect_subclasses(subclasses_path_argument)
    Object subclasses_path_argument;
{
    Object class_description_qm, aref_arg_1, classes, classes_tail_pointer;
    Object class_bit_number, subclasses_traversal_pointer, superior_class;
    Object class_1, ab_loop_list_, superior, ab_loop_list__1, ab_loop_it_;
    Object gensymed_symbol_2, new_class_cons, temp_3;
    SI_Long index_1, temp, ab_loop_bind_, temp_1, gensymed_symbol;
    SI_Long gensymed_symbol_1, aref_new_value, class_byte_vector_index;
    SI_Long class_visited_byte, class_byte_mask, byte_vector_index;
    SI_Long visited_byte, byte_mask;
    char temp_2;

    x_note_fn_call(81,4);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(subclasses_path_argument,
	    Class_description_gkbprop);
    if (class_description_qm) {
	index_1 = (SI_Long)0L;
	temp = (IFIX(Next_class_bit_number) + ((SI_Long)8L - (SI_Long)1L)) 
		/ (SI_Long)8L;
	ab_loop_bind_ = temp;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	aref_arg_1 = Classes_visited_byte_vector;
	UBYTE_8_ISASET_1(aref_arg_1,index_1,(SI_Long)0L);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	classes = scope_cons(subclasses_path_argument,Nil);
	classes_tail_pointer = classes;
	class_bit_number = ISVREF(class_description_qm,(SI_Long)18L);
	aref_arg_1 = Classes_visited_byte_vector;
	temp_1 = IFIX(class_bit_number) >>  -  - (SI_Long)3L;
	gensymed_symbol = (SI_Long)1L;
	gensymed_symbol_1 = IFIX(class_bit_number) & (SI_Long)7L;
	aref_new_value = gensymed_symbol << gensymed_symbol_1;
	UBYTE_8_ISASET_1(aref_arg_1,temp_1,aref_new_value);
	subclasses_traversal_pointer = classes;
	superior_class = Nil;
      next_loop_1:
	if ( !TRUEP(subclasses_traversal_pointer))
	    goto end_loop_1;
	superior_class = M_CAR(subclasses_traversal_pointer);
	class_1 = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(superior_class,
		Inferior_classes_gkbprop);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	superior = Nil;
	ab_loop_list__1 = 
		lookup_global_or_kb_specific_property_value(class_1,
		Direct_superior_classes_gkbprop);
	ab_loop_it_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	superior = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	gensymed_symbol_2 = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (gensymed_symbol_2 ? 
		TRUEP(memq_function(subclasses_path_argument,
		ISVREF(gensymed_symbol_2,(SI_Long)2L))) : TRUEP(Nil)) {
	    class_bit_number = 
		    ISVREF(lookup_global_or_kb_specific_property_value(superior,
		    Class_description_gkbprop),(SI_Long)18L);
	    class_byte_vector_index = IFIX(class_bit_number) >>  -  - 
		    (SI_Long)3L;
	    class_visited_byte = 
		    UBYTE_8_ISAREF_1(Classes_visited_byte_vector,
		    class_byte_vector_index);
	    gensymed_symbol = (SI_Long)1L;
	    gensymed_symbol_1 = IFIX(class_bit_number) & (SI_Long)7L;
	    class_byte_mask = gensymed_symbol << gensymed_symbol_1;
	    ab_loop_it_ = (class_visited_byte & class_byte_mask) == 
		    (SI_Long)0L ? T : Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_3;
      end_loop_3:
	temp_2 = TRUEP(Qnil);
      end_1:;
	if ( !temp_2) {
	    class_bit_number = 
		    ISVREF(lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop),(SI_Long)18L);
	    byte_vector_index = IFIX(class_bit_number) >>  -  - (SI_Long)3L;
	    visited_byte = UBYTE_8_ISAREF_1(Classes_visited_byte_vector,
		    byte_vector_index);
	    gensymed_symbol = (SI_Long)1L;
	    gensymed_symbol_1 = IFIX(class_bit_number) & (SI_Long)7L;
	    byte_mask = gensymed_symbol << gensymed_symbol_1;
	    if ((visited_byte & byte_mask) == (SI_Long)0L) {
		aref_arg_1 = Classes_visited_byte_vector;
		temp_1 = visited_byte | byte_mask;
		UBYTE_8_ISASET_1(aref_arg_1,byte_vector_index,temp_1);
		new_class_cons = scope_cons(class_1,Nil);
		M_CDR(classes_tail_pointer) = new_class_cons;
		classes_tail_pointer = new_class_cons;
	    }
	}
	goto next_loop_2;
      end_loop_2:;
	subclasses_traversal_pointer = M_CDR(subclasses_traversal_pointer);
	goto next_loop_1;
      end_loop_1:;
	temp_3 = classes;
    }
    else
	temp_3 = Nil;
    return VALUES_1(temp_3);
}

/* COLLECT-SUPERCLASSES */
Object collect_superclasses(superclasses_path_argument)
    Object superclasses_path_argument;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, classes, classes_tail_pointer;
    Object classes_traversal_pointer, subclass, superior_class, ab_loop_list_;
    Object inferior, ab_loop_list__1, ab_loop_it_, class_bit_number;
    Object new_class_cons;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, index_1;
    SI_Long temp_4, class_byte_vector_index, class_visited_byte;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, class_byte_mask;
    SI_Long byte_vector_index, visited_byte, byte_mask, aref_new_value;
    char temp_3;
    Object result;

    x_note_fn_call(81,5);
    if (SYMBOLP(superclasses_path_argument)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = superclasses_path_argument;
	key_hash_value = SXHASH_SYMBOL_1(superclasses_path_argument) & 
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superclasses_path_argument;
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
	temp_3 = TRUEP(resulting_value);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	index_1 = (SI_Long)0L;
	temp_4 = (IFIX(Next_class_bit_number) + ((SI_Long)8L - 
		(SI_Long)1L)) / (SI_Long)8L;
	ab_loop_bind_ = temp_4;
      next_loop_12:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_12;
	temp_2 = Classes_visited_byte_vector;
	UBYTE_8_ISASET_1(temp_2,index_1,(SI_Long)0L);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_12;
      end_loop_12:;
	classes = frame_cons_1(superclasses_path_argument,Nil);
	classes_tail_pointer = classes;
	classes_traversal_pointer = classes;
	subclass = Nil;
      next_loop_13:
	if ( !TRUEP(classes_traversal_pointer))
	    goto end_loop_13;
	subclass = M_CAR(classes_traversal_pointer);
	superior_class = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(subclass,
		Direct_superior_classes_gkbprop);
      next_loop_14:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_14;
	superior_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	inferior = Nil;
	ab_loop_list__1 = 
		lookup_global_or_kb_specific_property_value(superior_class,
		Inferior_classes_gkbprop);
	ab_loop_it_ = Nil;
      next_loop_15:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_15;
	inferior = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !EQ(superclasses_path_argument,inferior)) {
	    class_bit_number = 
		    ISVREF(lookup_global_or_kb_specific_property_value(inferior,
		    Class_description_gkbprop),(SI_Long)18L);
	    class_byte_vector_index = IFIX(class_bit_number) >>  -  - 
		    (SI_Long)3L;
	    class_visited_byte = 
		    UBYTE_8_ISAREF_1(Classes_visited_byte_vector,
		    class_byte_vector_index);
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_4 = IFIX(class_bit_number) & (SI_Long)7L;
	    class_byte_mask = gensymed_symbol_3 << gensymed_symbol_4;
	    ab_loop_it_ = (class_visited_byte & class_byte_mask) == 
		    (SI_Long)0L ? T : Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp_3 = TRUEP(ab_loop_it_);
	    goto end_5;
	}
	goto next_loop_15;
      end_loop_15:
	temp_3 = TRUEP(Qnil);
      end_5:;
	if ( !temp_3) {
	    class_bit_number = 
		    ISVREF(lookup_global_or_kb_specific_property_value(superior_class,
		    Class_description_gkbprop),(SI_Long)18L);
	    byte_vector_index = IFIX(class_bit_number) >>  -  - (SI_Long)3L;
	    visited_byte = UBYTE_8_ISAREF_1(Classes_visited_byte_vector,
		    byte_vector_index);
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_4 = IFIX(class_bit_number) & (SI_Long)7L;
	    byte_mask = gensymed_symbol_3 << gensymed_symbol_4;
	    if ((visited_byte & byte_mask) == (SI_Long)0L) {
		temp_2 = Classes_visited_byte_vector;
		aref_new_value = visited_byte | byte_mask;
		UBYTE_8_ISASET_1(temp_2,byte_vector_index,aref_new_value);
		new_class_cons = scope_cons(superior_class,Nil);
		M_CDR(classes_tail_pointer) = new_class_cons;
		classes_tail_pointer = new_class_cons;
	    }
	}
	goto next_loop_14;
      end_loop_14:;
	classes_traversal_pointer = M_CDR(classes_traversal_pointer);
	goto next_loop_13;
      end_loop_13:
	temp_1 = classes;
	classes = CDR(classes);
	reclaim_frame_cons_1(temp_1);
	temp_1 = classes;
	goto end_6;
	temp_1 = Qnil;
      end_6:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qkb_frame;           /* kb-frame */

/* MAKE-SLOT-DESCRIPTIONS-HASH-TABLE */
Object make_slot_descriptions_hash_table(class_1,class_slot_descriptions,
	    class_inheritance_path,direct_superior_classes,
	    user_defined_class_qm)
    Object class_1, class_slot_descriptions, class_inheritance_path;
    Object direct_superior_classes, user_defined_class_qm;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, class_is_defined_qm, full_hash_table_class;
    Object upgraded_superiors_list, class_cons, superior_class;
    Object superior_class_description, superior_has_full_hash_table_qm;
    Object slot_hash_binary_tree, element_qm, superior, ab_loop_list_;
    Object scope_conses, ab_loopvar_, subclass, subclass_class_description;
    Object subclass_full_hash_table_class, subclass_inheritance_path;
    Object class_description, ab_loopvar__1, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, current_classes_variable_set, sublist, class_to_add;
    Object superior_1, ab_loop_list__1, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(81,6);
    if (SYMBOLP(class_1)) {
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
	class_is_defined_qm = resulting_value;
    }
    else
	class_is_defined_qm = Nil;
    if (EQ(class_1,Qroot) || EQ(class_1,Qblock)) {
	temp_1 = 
		make_full_slot_descriptions_hash_table(class_slot_descriptions,
		class_inheritance_path);
	return VALUES_2(temp_1,class_1);
    }
    else if (EQ(class_1,Qkb_frame)) {
	temp_1 = make_sparse_slot_descriptions_hash_table(class_1,
		class_slot_descriptions,class_inheritance_path);
	return VALUES_2(temp_1,Qroot);
    }
    else if (user_defined_class_qm && class_is_defined_qm && 
	    well_instantiated_or_subclassed_class_p(class_1)) {
	temp_1 = 
		make_full_slot_descriptions_hash_table(class_slot_descriptions,
		class_inheritance_path);
	return VALUES_2(temp_1,class_1);
    }
    else {
	full_hash_table_class = Nil;
	upgraded_superiors_list = Nil;
	class_cons = CDR(class_inheritance_path);
	superior_class = Nil;
	superior_class_description = Nil;
	superior_has_full_hash_table_qm = Nil;
      next_loop_12:
	if ( !TRUEP(class_cons))
	    goto end_loop_12;
	superior_class = M_CAR(class_cons);
	superior_class_description = 
		lookup_global_or_kb_specific_property_value(superior_class,
		Class_description_gkbprop);
	gensymed_symbol = superior_class_description;
	superior_has_full_hash_table_qm = EQ(ISVREF(gensymed_symbol,
		(SI_Long)17L),ISVREF(gensymed_symbol,(SI_Long)1L)) ? T : Nil;
	if (memq_function(superior_class,direct_superior_classes) &&  
		!TRUEP(superior_has_full_hash_table_qm) && 
		well_instantiated_or_subclassed_class_p(superior_class)) {
	    upgraded_superiors_list = frame_cons_1(superior_class,
		    upgraded_superiors_list);
	    slot_hash_binary_tree = ISVREF(superior_class_description,
		    (SI_Long)9L);
	    element_qm = M_CDR(slot_hash_binary_tree);
	    if (element_qm)
		reclaim_slot_hash_leaves(element_qm);
	    inline_note_reclaim_cons(slot_hash_binary_tree,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = slot_hash_binary_tree;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
	    }
	    else {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
	    }
	    M_CDR(slot_hash_binary_tree) = Nil;
	    temp_2 = 
		    make_full_slot_descriptions_hash_table(ISVREF(superior_class_description,
		    (SI_Long)6L),ISVREF(superior_class_description,
		    (SI_Long)2L));
	    SVREF(superior_class_description,FIX((SI_Long)9L)) = temp_2;
	    SVREF(superior_class_description,FIX((SI_Long)17L)) = 
		    superior_class;
	}
	temp_1 = ISVREF(superior_class_description,(SI_Long)2L);
	if (EQUAL(class_cons,temp_1)) {
	    if (superior_has_full_hash_table_qm) {
		full_hash_table_class = superior_class;
		goto end_loop_12;
	    }
	    else if (IFIX(position(2,superior_class,
		    class_inheritance_path)) > (SI_Long)1L) {
		upgraded_superiors_list = frame_cons_1(superior_class,
			upgraded_superiors_list);
		slot_hash_binary_tree = ISVREF(superior_class_description,
			(SI_Long)9L);
		element_qm = M_CDR(slot_hash_binary_tree);
		if (element_qm)
		    reclaim_slot_hash_leaves(element_qm);
		inline_note_reclaim_cons(slot_hash_binary_tree,Qlookup);
		if (ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = slot_hash_binary_tree;
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
		}
		else {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
		    temp_2 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = slot_hash_binary_tree;
		}
		M_CDR(slot_hash_binary_tree) = Nil;
		temp_2 = 
			make_full_slot_descriptions_hash_table(ISVREF(superior_class_description,
			(SI_Long)6L),ISVREF(superior_class_description,
			(SI_Long)2L));
		SVREF(superior_class_description,FIX((SI_Long)9L)) = temp_2;
		SVREF(superior_class_description,FIX((SI_Long)17L)) = 
			superior_class;
		full_hash_table_class = superior_class;
		goto end_loop_12;
	    }
	    else;
	}
	class_cons = M_CDR(class_cons);
	goto next_loop_12;
      end_loop_12:;
	superior = Nil;
	ab_loop_list_ = upgraded_superiors_list;
      next_loop_13:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_13;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (user_defined_class_qm) {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = superior;
	    subclass = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop_14:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_14;
	      temp_1 = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      subclass = temp_1;
	      subclass_class_description = 
		      lookup_global_or_kb_specific_property_value(subclass,
		      Class_description_gkbprop);
	      subclass_full_hash_table_class = 
		      ISVREF(subclass_class_description,(SI_Long)17L);
	      subclass_inheritance_path = 
		      ISVREF(subclass_class_description,(SI_Long)2L);
	      temp_1 = memq_function(superior,subclass_inheritance_path);
	      class_description = 
		      lookup_global_or_kb_specific_property_value(superior,
		      Class_description_gkbprop);
	      temp = ISVREF(class_description,(SI_Long)2L);
	      if (EQUAL(temp_1,temp)) {
		  temp_1 = position(2,superior,subclass_inheritance_path);
		  temp_3 = FIXNUM_LT(temp_1,position(2,
			  subclass_full_hash_table_class,
			  subclass_inheritance_path));
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3)
		  SVREF(subclass_class_description,FIX((SI_Long)17L)) = 
			  superior;
	      goto next_loop_14;
	    end_loop_14:;
	    POP_SPECIAL();
	}
	else {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = superior;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    subclass = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      if (SYMBOLP(ab_loopvar_)) {
		  skip_list = CDR(Symbol_properties_table);
		  key_value = ab_loopvar_;
		  key_hash_value = SXHASH_SYMBOL_1(ab_loopvar_) & 
			  IFIX(Most_positive_fixnum);
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
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_16:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_17:
		  if ( !TRUEP(marked))
		      goto end_loop_16;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_17;
		end_loop_16:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_5;
		  goto next_loop_16;
		end_loop_17:
		end_5:
		  level = level - (SI_Long)1L;
		  goto next_loop_15;
		end_loop_15:;
		  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if ( !TRUEP(gensymed_symbol)) {
		      gensymed_symbol = ab_loopvar_;
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
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
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
		      gensymed_symbol = set_skip_list_entry(temp,
			      FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			      temp_1,gensymed_symbol_1);
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
		next_loop_18:
		  if (level < ab_loop_bind_)
		      goto end_loop_18;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_19:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_20:
		  if ( !TRUEP(marked))
		      goto end_loop_19;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_20;
		end_loop_19:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_6;
		  goto next_loop_19;
		end_loop_20:
		end_6:
		  level = level - (SI_Long)1L;
		  goto next_loop_18;
		end_loop_18:;
		  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		    next_loop_21:
		      if (level < ab_loop_bind_)
			  goto end_loop_21;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_22:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_23:
		      if ( !TRUEP(marked))
			  goto end_loop_22;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_23;
		    end_loop_22:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_7;
		      goto next_loop_22;
		    end_loop_23:
		    end_7:
		      level = level - (SI_Long)1L;
		      goto next_loop_21;
		    end_loop_21:;
		      kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
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
		    next_loop_24:
		      if (level < ab_loop_bind_)
			  goto end_loop_24;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_25:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_26:
		      if ( !TRUEP(marked))
			  goto end_loop_25;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_26;
		    end_loop_25:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_8;
		      goto next_loop_25;
		    end_loop_26:
		    end_8:
		      level = level - (SI_Long)1L;
		      goto next_loop_24;
		    end_loop_24:;
		      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (resulting_value);
		      else
			  resulting_value = Nil;
		  }
		  temp_3 = TRUEP(resulting_value);
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      ab_loopvar__3 = temp_3 ? scope_cons(ab_loopvar_,Nil) : Nil;
	    next_loop_27:
	      if ( !TRUEP(ab_loopvar__3))
		  goto end_loop_27;
	      temp_1 = M_CAR(ab_loopvar__3);
	      ab_loopvar__2 = scope_cons(M_CAR(ab_loopvar__3),ab_loopvar__2);
	      ab_loopvar__4 = 
		      lookup_global_or_kb_specific_property_value(M_CAR(ab_loopvar__3),
		      Inferior_classes_gkbprop);
	      if (ab_loopvar__4) {
		  temp = ab_loopvar__1;
		  ab_loopvar__1 = nconc2(temp,scope_cons(ab_loopvar__4,Nil));
	      }
	      ab_loopvar__3 = M_CDR(ab_loopvar__3);
	      current_classes_variable_set = Nil;
	    next_loop_28:
	      if (current_classes_variable_set)
		  goto end_loop_28;
	      sublist = ab_loopvar__3;
	      class_to_add = Nil;
	    next_loop_29:
	      if ( !TRUEP(sublist))
		  goto end_loop_29;
	      class_to_add = M_CAR(sublist);
	      if ( !TRUEP(sublist))
		  goto end_loop_29;
	      temp_3 = TRUEP(memq_function(M_CAR(sublist),ab_loopvar__2));
	      if (temp_3);
	      else {
		  superior_1 = Nil;
		  ab_loop_list__1 = 
			  lookup_global_or_kb_specific_property_value(class_to_add,
			  Direct_superior_classes_gkbprop);
		  ab_loop_it_ = Nil;
		next_loop_30:
		  if ( !TRUEP(ab_loop_list__1))
		      goto end_loop_30;
		  superior_1 = M_CAR(ab_loop_list__1);
		  ab_loop_list__1 = M_CDR(ab_loop_list__1);
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(superior_1,
			  Class_description_gkbprop);
		  ab_loop_it_ = (gensymed_symbol ? 
			  TRUEP(memq_function(ab_loopvar_,
			  ISVREF(gensymed_symbol,(SI_Long)2L))) : 
			  TRUEP(Nil)) ? ( !TRUEP(memq_function(superior_1,
			  ab_loopvar__2)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp_3 = TRUEP(ab_loop_it_);
		      goto end_9;
		  }
		  goto next_loop_30;
		end_loop_30:
		  temp_3 = TRUEP(Qnil);
		end_9:;
	      }
	      if ( !temp_3) {
		  ab_loopvar__3 = sublist;
		  current_classes_variable_set = T;
		  goto end_loop_29;
	      }
	      sublist = M_CDR(sublist);
	      goto next_loop_29;
	    end_loop_29:
	      if ( !TRUEP(current_classes_variable_set)) {
		  ab_loopvar__3 = CAR(ab_loopvar__1);
		  if (ab_loopvar__1)
		      ab_loopvar__1 = M_CDR(ab_loopvar__1);
		  else
		      current_classes_variable_set = T;
	      }
	      goto next_loop_28;
	    end_loop_28:;
	      subclass = temp_1;
	      subclass_class_description = 
		      lookup_global_or_kb_specific_property_value(subclass,
		      Class_description_gkbprop);
	      subclass_full_hash_table_class = 
		      ISVREF(subclass_class_description,(SI_Long)17L);
	      subclass_inheritance_path = 
		      ISVREF(subclass_class_description,(SI_Long)2L);
	      temp_1 = memq_function(superior,subclass_inheritance_path);
	      class_description = 
		      lookup_global_or_kb_specific_property_value(superior,
		      Class_description_gkbprop);
	      temp = ISVREF(class_description,(SI_Long)2L);
	      if (EQUAL(temp_1,temp)) {
		  temp_1 = position(2,superior,subclass_inheritance_path);
		  temp_3 = FIXNUM_LT(temp_1,position(2,
			  subclass_full_hash_table_class,
			  subclass_inheritance_path));
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3)
		  SVREF(subclass_class_description,FIX((SI_Long)17L)) = 
			  superior;
	      goto next_loop_27;
	    end_loop_27:;
	    POP_SPECIAL();
	}
	goto next_loop_13;
      end_loop_13:;
	reclaim_frame_list_1(upgraded_superiors_list);
	temp_1 = make_sparse_slot_descriptions_hash_table(class_1,
		class_slot_descriptions,class_inheritance_path);
	return VALUES_2(temp_1,full_hash_table_class);
    }
}

/* MAKE-CLASS-INHERITANCE-PATH-FOR-SYSTEM-DEFINED-CLASS */
Object make_class_inheritance_path_for_system_defined_class(class_being_defined,
	    direct_superior_classes)
    Object class_being_defined, direct_superior_classes;
{
    Object class_description, path, merging_path, superior_class;
    Object ab_loop_list_, superior_path, class_1, ab_loop_list__1, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, list_of_common_ancestors;
    Object common_ancestor, temp, ab_loop_list__2, path_old_value, temp_1;
    Object superior_path_old_value, temp_2;

    x_note_fn_call(81,7);
    class_description = 
	    lookup_global_or_kb_specific_property_value(CAR(direct_superior_classes),
	    Class_description_gkbprop);
    path = copy_list(ISVREF(class_description,(SI_Long)2L));
    merging_path = Nil;
    superior_class = Nil;
    ab_loop_list_ = CDR(direct_superior_classes);
    superior_path = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop);
    superior_path = copy_list(ISVREF(class_description,(SI_Long)2L));
    class_1 = Nil;
    ab_loop_list__1 = superior_path;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (memq_function(class_1,path)) {
	ab_loopvar__2 = frame_cons_1(class_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    list_of_common_ancestors = ab_loopvar_;
    goto end_1;
    list_of_common_ancestors = Qnil;
  end_1:;
    common_ancestor = Nil;
    ab_loop_list__1 = list_of_common_ancestors;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    common_ancestor = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = merging_path;
    class_1 = Nil;
    ab_loop_list__2 = path;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__2))
	goto end_loop_3;
    class_1 = M_CAR(ab_loop_list__2);
    ab_loop_list__2 = M_CDR(ab_loop_list__2);
    if (EQ(class_1,common_ancestor))
	goto end_loop_3;
    ab_loopvar__2 = LIST_1(class_1);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    path_old_value = path;
    path = REST(path_old_value);
    goto next_loop_3;
  end_loop_3:
    temp_1 = ab_loopvar_;
    goto end_2;
    temp_1 = Qnil;
  end_2:;
    class_1 = Nil;
    ab_loop_list__2 = superior_path;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list__2))
	goto end_loop_4;
    class_1 = M_CAR(ab_loop_list__2);
    ab_loop_list__2 = M_CDR(ab_loop_list__2);
    if (EQ(class_1,common_ancestor))
	goto end_loop_4;
    ab_loopvar__2 = LIST_1(class_1);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    superior_path_old_value = superior_path;
    superior_path = REST(superior_path_old_value);
    goto next_loop_4;
  end_loop_4:
    temp_2 = ab_loopvar_;
    goto end_3;
    temp_2 = Qnil;
  end_3:;
    merging_path = nconc2(temp,nconc2(temp_1,nconc2(temp_2,
	    LIST_1(common_ancestor))));
    path_old_value = path;
    path = REST(path_old_value);
    superior_path_old_value = superior_path;
    superior_path = REST(superior_path_old_value);
    goto next_loop_2;
  end_loop_2:
    reclaim_frame_list_1(list_of_common_ancestors);
    path = Nil;
    path = merging_path;
    merging_path = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(CONS(class_being_defined,path));
    return VALUES_1(Qnil);
}

/* CLASSES-INTERSECT-P */
Object classes_intersect_p(symbol_1,symbol_2)
    Object symbol_1, symbol_2;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, symbol_1_subclasses;
    Object scope_conses, ab_loopvar_, symbol_2_subclass, ab_loopvar__1;
    Object class_1, ab_loopvar__2, ab_loopvar__3, ab_loopvar__4;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(81,8);
    if (SYMBOLP(symbol_1)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol_1;
	key_hash_value = SXHASH_SYMBOL_1(symbol_1) & 
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol_1;
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (SYMBOLP(symbol_2)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = symbol_2;
	    key_hash_value = SXHASH_SYMBOL_1(symbol_2) & 
		    IFIX(Most_positive_fixnum);
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = symbol_2;
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	      next_loop_18:
		if (level < ab_loop_bind_)
		    goto end_loop_18;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_19:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_20;
	      end_loop_19:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	      next_loop_21:
		if (level < ab_loop_bind_)
		    goto end_loop_21;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_22:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_23;
	      end_loop_22:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	symbol_1_subclasses = Nil;
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = symbol_2;
	symbol_2_subclass = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop_24:
	  scope_conses = Scope_conses;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__1 = symbol_1;
	  class_1 = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	    ab_loopvar__1 = collect_subclasses(ab_loopvar__1);
	  next_loop_25:
	    if ( !TRUEP(ab_loopvar__1))
		goto end_loop_24;
	    temp_1 = M_CAR(ab_loopvar__1);
	    ab_loopvar__1 = M_CDR(ab_loopvar__1);
	    class_1 = temp_1;
	    ab_loopvar__4 = frame_cons_1(class_1,Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_25;
	  end_loop_24:
	    symbol_1_subclasses = ab_loopvar__2;
	    goto end_9;
	    symbol_1_subclasses = Qnil;
	  end_9:;
	  POP_SPECIAL();
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_25;
	  temp_1 = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  symbol_2_subclass = temp_1;
	  if (memq_function(symbol_2_subclass,symbol_1_subclasses)) {
	      reclaim_frame_list_1(symbol_1_subclasses);
	      result = VALUES_1(T);
	      goto end_10;
	  }
	  goto next_loop_24;
	end_loop_25:
	  reclaim_frame_list_1(symbol_1_subclasses);
	  result = VALUES_1(Nil);
	  goto end_10;
	  result = VALUES_1(Qnil);
	end_10:;
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Noting_changes_to_kb_p, Qnoting_changes_to_kb_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_block_of_dependent_frame, Qcurrent_block_of_dependent_frame);

/* ERROR-MESSAGE-FOR-DEPENDENT-FRAME-SAVING */
Object error_message_for_dependent_frame_saving(frame)
    Object frame;
{
    x_note_fn_call(81,9);
    return VALUES_1(Nil);
}

/* SYSTEM-VECTOR-SLOTS-IN-CONFLICT */
Object system_vector_slots_in_conflict(direct_superior_classes)
    Object direct_superior_classes;
{
    Object slot_names_in_conflict_qm, class_description;
    Object longest_class_vector_length, class_with_longest_vector, superior;
    Object ab_loop_list_, maximum_slot_descriptions;
    Object comparison_class_description, slot_description, ab_loop_list__1;
    Object vector_slot_index_qm, comparison_slot_description_qm;
    Object slot_description_1, ab_loop_list__2;

    x_note_fn_call(81,10);
    if (IFIX(length(direct_superior_classes)) == (SI_Long)1L)
	return VALUES_1(Nil);
    else {
	slot_names_in_conflict_qm = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(FIRST(direct_superior_classes),
		Class_description_gkbprop);
	longest_class_vector_length = ISVREF(class_description,(SI_Long)14L);
	class_with_longest_vector = FIRST(direct_superior_classes);
	superior = Nil;
	ab_loop_list_ = CDR(direct_superior_classes);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if (FIXNUM_GT(ISVREF(class_description,(SI_Long)14L),
		longest_class_vector_length)) {
	    class_description = 
		    lookup_global_or_kb_specific_property_value(superior,
		    Class_description_gkbprop);
	    longest_class_vector_length = ISVREF(class_description,
		    (SI_Long)14L);
	    class_with_longest_vector = superior;
	}
	goto next_loop;
      end_loop:;
	class_description = 
		lookup_global_or_kb_specific_property_value(class_with_longest_vector,
		Class_description_gkbprop);
	maximum_slot_descriptions = ISVREF(class_description,(SI_Long)6L);
	superior = Nil;
	ab_loop_list_ = direct_superior_classes;
	comparison_class_description = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (slot_names_in_conflict_qm)
	    goto end_loop_1;
	comparison_class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if ( !EQ(class_with_longest_vector,superior)) {
	    slot_description = Nil;
	    ab_loop_list__1 = maximum_slot_descriptions;
	    vector_slot_index_qm = Nil;
	    comparison_slot_description_qm = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    slot_description = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	    if (vector_slot_index_qm) {
		slot_description_1 = Nil;
		ab_loop_list__2 = ISVREF(comparison_class_description,
			(SI_Long)6L);
	      next_loop_3:
		if ( !TRUEP(ab_loop_list__2))
		    goto end_loop_3;
		slot_description_1 = M_CAR(ab_loop_list__2);
		ab_loop_list__2 = M_CDR(ab_loop_list__2);
		if (EQ(ISVREF(slot_description_1,(SI_Long)7L),
			vector_slot_index_qm)) {
		    comparison_slot_description_qm = slot_description_1;
		    goto end_1;
		}
		goto next_loop_3;
	      end_loop_3:
		comparison_slot_description_qm = Qnil;
	      end_1:;
	    }
	    else
		comparison_slot_description_qm = Nil;
	    if (comparison_slot_description_qm &&  
		    !EQ(ISVREF(slot_description,(SI_Long)2L),
		    ISVREF(comparison_slot_description_qm,(SI_Long)2L))) {
		slot_names_in_conflict_qm = LIST_2(ISVREF(slot_description,
			(SI_Long)2L),ISVREF(comparison_slot_description_qm,
			(SI_Long)2L));
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	  end_2:;
	}
	goto next_loop_1;
      end_loop_1:;
	return VALUES_1(slot_names_in_conflict_qm);
    }
}

/* GET-MOST-SPECIFIC-DIRECT-SUPERIOR-FOR-CLASS */
Object get_most_specific_direct_superior_for_class(direct_superiors_for_class)
    Object direct_superiors_for_class;
{
    x_note_fn_call(81,11);
    return VALUES_1(FIRST(direct_superiors_for_class));
}

static Object Qfoundation_class;   /* foundation-class */

/* GET-FOUNDATION-CLASS-FOR-CLASS */
Object get_foundation_class_for_class(class_1)
    Object class_1;
{
    Object class_description, temp;

    x_note_fn_call(81,12);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    temp = assq_function(Qfoundation_class,ISVREF(class_description,
	    (SI_Long)12L));
    return VALUES_1(SECOND(temp));
}

/* MOST-REFINED-FOUNDATION-CLASS-OF-DIRECT-SUPERIORS */
Object most_refined_foundation_class_of_direct_superiors varargs_1(int, n)
{
    Object direct_superior_classes;
    Object unaliased_slot_name, most_refined_foundation_class, superior;
    Object ab_loop_list_, slot_description_qm, slot_defining_class_qm;
    Object superior_is_system_defined_p, superior_foundation_class;
    Object foundation_class_slot_description_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(81,13);
    INIT_ARGS_nonrelocating();
    direct_superior_classes = REQUIRED_ARG_nonrelocating();
    unaliased_slot_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    most_refined_foundation_class = Nil;
    superior = Nil;
    ab_loop_list_ = direct_superior_classes;
    slot_description_qm = Nil;
    slot_defining_class_qm = Nil;
    superior_is_system_defined_p = Nil;
    superior_foundation_class = Nil;
    foundation_class_slot_description_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (unaliased_slot_name) {
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
	slot_description_qm = 
		get_slot_description_of_class_description_function(unaliased_slot_name,
		gensymed_symbol,Nil);
    }
    else
	slot_description_qm = Nil;
    slot_defining_class_qm = slot_description_qm ? 
	    ISVREF(slot_description_qm,(SI_Long)3L) : Nil;
    if (lookup_global_or_kb_specific_property_value(superior,
	    Class_description_gkbprop)) {
	temp_1 = lookup_global_or_kb_specific_property_value(superior,
		Class_definition_gkbprop);
	superior_is_system_defined_p = CONSP(temp_1) ? T : Nil;
    }
    else
	superior_is_system_defined_p = Nil;
    superior_foundation_class = get_foundation_class_for_class(superior);
    if (unaliased_slot_name) {
	skip_list = CDR(Symbol_properties_table);
	key_value = superior_foundation_class;
	key_hash_value = SXHASH_SYMBOL_1(superior_foundation_class) & 
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior_foundation_class;
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  next_loop_19:
	    if (level < ab_loop_bind_)
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_20:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_21:
	    if ( !TRUEP(marked))
		goto end_loop_20;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_21;
	  end_loop_20:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_23:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_24:
	    if ( !TRUEP(marked))
		goto end_loop_23;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_24;
	  end_loop_23:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	foundation_class_slot_description_qm = 
		get_slot_description_of_class_description_function(unaliased_slot_name,
		gensymed_symbol,Nil);
    }
    else
	foundation_class_slot_description_qm = Nil;
    if ( !TRUEP(foundation_class_slot_description_qm)) {
	if (unaliased_slot_name)
	    superior_foundation_class = Nil;
	if (slot_defining_class_qm)
	    superior_foundation_class = slot_defining_class_qm;
    }
    if (superior_foundation_class) {
	temp_2 =  !TRUEP(most_refined_foundation_class);
	if (temp_2);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(superior_foundation_class,
		    Class_description_gkbprop);
	    temp_2 = gensymed_symbol ? 
		    TRUEP(memq_function(most_refined_foundation_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	}
	if (temp_2)
	    most_refined_foundation_class = superior_foundation_class;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(most_refined_foundation_class);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_class_method_tables_processed_qm, Qsystem_class_method_tables_processed_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Decache_attribute_description_lists_of_interned_lists_function, Qdecache_attribute_description_lists_of_interned_lists_function);

DEFINE_VARIABLE_WITH_SYMBOL(Class_change_timestamp, Qclass_change_timestamp);

/* DECACHE-CACHED-CLASS-DATA */
Object decache_cached_class_data(class_1)
    Object class_1;
{
    x_note_fn_call(81,14);
    if (Decache_attribute_description_lists_of_interned_lists_function)
	inline_funcall_1(Decache_attribute_description_lists_of_interned_lists_function,
		class_1);
    update_change_timestamps(class_1);
    return VALUES_1(Nil);
}

/* UPDATE-CHANGE-TIMESTAMPS */
Object update_change_timestamps(class_1)
    Object class_1;
{
    Object class_description_qm, new_timestamp, superclass_class_description;
    Object existing_class_description_path_arg, class_description_arg;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(81,15);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description_qm) {
	new_timestamp = atomic_incff_symval(Qclass_change_timestamp,
		FIX((SI_Long)1L));
	SVREF(class_description_qm,FIX((SI_Long)23L)) = new_timestamp;
	superclass_class_description = Nil;
	existing_class_description_path_arg = ISVREF(class_description_qm,
		(SI_Long)3L);
	class_description_arg = class_description_qm;
	if ( !TRUEP(existing_class_description_path_arg)) {
	    class_1 = Nil;
	    ab_loop_list_ = ISVREF(class_description_arg,(SI_Long)2L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    class_description_cons_1(lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    goto end_1;
	    ab_loopvar_ = Qnil;
	  end_1:;
	    ab_loop_list_ = SVREF(class_description_arg,FIX((SI_Long)3L)) 
		    = ab_loopvar_;
	}
	else
	    ab_loop_list_ = existing_class_description_path_arg;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	superclass_class_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	SVREF(superclass_class_description,FIX((SI_Long)24L)) = new_timestamp;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

static Object Qinferior_classes;   /* inferior-classes */

static Object Qport;               /* port */

static Object Qslot_category;      /* slot-category */

static Object Qobsolete;           /* obsolete */

static Object Qitem;               /* item */

/* ADD-CLASS-TO-ENVIRONMENT */
Object add_class_to_environment varargs_1(int, n)
{
    Object class_1, direct_superior_classes, class_inheritance_path;
    Object class_features, do_not_propagate_methods_qm;
    Object slot_descriptions_defined_for_class;
    Object previous_direct_superior_classes_qm, class_definition;
    Object user_defined_class_qm;
    Object slot_descriptions_for_overridden_slots_qm;
    Object superior_class_class_description, foundation_class;
    Object class_description, frame_vector_length, class_bit_number;
    Object class_bit_vector, slots_local_to_class;
    Object inherited_slots_this_class_overrides;
    Object all_slot_descriptions_for_class, class_user_vector_length;
    Object slot_descriptions_hash_table, full_hash_table_class;
    Object previous_superior, ab_loop_list_, temp, temp_1, superior;
    Object inferior_classes, slot_description, unique_slot_name;
    Object pretty_slot_name, slot_features, temp_2, class_vector_length;
    Object local_slots_for_class;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(81,16);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    direct_superior_classes = REQUIRED_ARG_nonrelocating();
    class_inheritance_path = REQUIRED_ARG_nonrelocating();
    class_features = REQUIRED_ARG_nonrelocating();
    do_not_propagate_methods_qm = REQUIRED_ARG_nonrelocating();
    slot_descriptions_defined_for_class = REQUIRED_ARG_nonrelocating();
    previous_direct_superior_classes_qm = REQUIRED_ARG_nonrelocating();
    class_definition = REQUIRED_ARG_nonrelocating();
    user_defined_class_qm = REQUIRED_ARG_nonrelocating();
    slot_descriptions_for_overridden_slots_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    slot_descriptions_defined_for_class = user_defined_class_qm ? 
	    slot_descriptions_defined_for_class : 
	    copy_slot_descriptions_evaluating_initialization_if_eval_once(slot_descriptions_defined_for_class);
    superior_class_class_description = 
	    lookup_global_or_kb_specific_property_value(CAR(direct_superior_classes),
	    Class_description_gkbprop);
    class_inheritance_path = user_defined_class_qm ? 
	    class_inheritance_path : 
	    make_class_inheritance_path_for_system_defined_class(class_1,
	    direct_superior_classes);
    foundation_class = user_defined_class_qm ? 
	    most_refined_foundation_class_of_direct_superiors(1,
	    direct_superior_classes) : Nil;
    if (user_defined_class_qm) {
	class_description = 
		lookup_global_or_kb_specific_property_value(foundation_class,
		Class_description_gkbprop);
	frame_vector_length = ISVREF(class_description,(SI_Long)14L);
    }
    else
	frame_vector_length = ISVREF(superior_class_class_description,
		(SI_Long)14L);
    class_bit_number = user_defined_class_qm ? get_next_class_bit_number() 
	    : Nil;
    class_bit_vector = user_defined_class_qm ? 
	    make_class_bit_vector(class_bit_number,class_inheritance_path) 
	    : Nil;
    slots_local_to_class = Nil;
    inherited_slots_this_class_overrides = Nil;
    if (user_defined_class_qm) {
	eval_slot_init_forms_of_slot_descriptions_defined_for_class(class_1,
		slot_descriptions_defined_for_class);
	result = merge_slot_descriptions_for_user_defined_class(class_1,
		class_inheritance_path,slot_descriptions_defined_for_class,
		slot_descriptions_for_overridden_slots_qm);
	MVS_2(result,all_slot_descriptions_for_class,class_user_vector_length);
	result = make_slot_descriptions_hash_table(class_1,
		all_slot_descriptions_for_class,class_inheritance_path,
		direct_superior_classes,T);
	MVS_2(result,slot_descriptions_hash_table,full_hash_table_class);
	mutate_global_or_kb_specific_property_value(class_1,
		class_definition,Class_definition_gkbprop);
	if (previous_direct_superior_classes_qm &&  
		!EQUAL(previous_direct_superior_classes_qm,
		direct_superior_classes)) {
	    previous_superior = Nil;
	    ab_loop_list_ = previous_direct_superior_classes_qm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    previous_superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(previous_superior,
		    direct_superior_classes))) {
		temp = previous_superior;
		temp_1 = delete_class_description_element_1(class_1,
			lookup_global_or_kb_specific_property_value(previous_superior,
			Inferior_classes_gkbprop));
		mutate_global_or_kb_specific_property_value(temp,temp_1,
			Inferior_classes_gkbprop);
	    }
	    goto next_loop;
	  end_loop:;
	    superior = Nil;
	    ab_loop_list_ = direct_superior_classes;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(class_1,
		    lookup_global_or_kb_specific_property_value(superior,
		    Inferior_classes_gkbprop)))) {
		copy_kb_specific_property_from_global_if_necessary(superior,
			Qinferior_classes);
		temp = superior;
		temp_1 = 
			nconc2(lookup_global_or_kb_specific_property_value(superior,
			Inferior_classes_gkbprop),
			class_description_cons_1(class_1,Nil));
		mutate_global_or_kb_specific_property_value(temp,temp_1,
			Inferior_classes_gkbprop);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	else {
	    superior = Nil;
	    ab_loop_list_ = direct_superior_classes;
	    inferior_classes = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    inferior_classes = 
		    lookup_global_or_kb_specific_property_value(superior,
		    Inferior_classes_gkbprop);
	    if ( !TRUEP(memq_function(class_1,inferior_classes))) {
		copy_kb_specific_property_from_global_if_necessary(superior,
			Qinferior_classes);
		temp = superior;
		temp_1 = 
			nconc2(lookup_global_or_kb_specific_property_value(superior,
			Inferior_classes_gkbprop),
			class_description_cons_1(class_1,Nil));
		mutate_global_or_kb_specific_property_value(temp,temp_1,
			Inferior_classes_gkbprop);
	    }
	    goto next_loop_2;
	  end_loop_2:;
	}
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions_defined_for_class;
	unique_slot_name = Nil;
	pretty_slot_name = Nil;
	slot_features = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
	pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	slot_features = ISVREF(slot_description,(SI_Long)9L);
	if (ISVREF(slot_description,(SI_Long)8L))
	    slots_local_to_class = nconc2(slots_local_to_class,
		    class_description_cons_1(unique_slot_name,Nil));
	else
	    inherited_slots_this_class_overrides = 
		    class_description_cons_1(unique_slot_name,
		    inherited_slots_this_class_overrides);
	if (assq_function(Qport,slot_features))
	    mutate_global_property(pretty_slot_name,Qport,Qslot_category);
	goto next_loop_3;
      end_loop_3:;
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions_for_overridden_slots_qm;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	inherited_slots_this_class_overrides = 
		class_description_cons_1(ISVREF(slot_description,
		(SI_Long)1L),inherited_slots_this_class_overrides);
	goto next_loop_4;
      end_loop_4:;
	reclaim_class_description_list_1(slot_descriptions_defined_for_class);
	reclaim_class_description_list_1(slot_descriptions_for_overridden_slots_qm);
	temp = slots_local_to_class;
	temp_1 = inherited_slots_this_class_overrides;
	temp_2 = initialize_or_update_method_table_for_user_class(class_1,
		class_inheritance_path,T);
	make_and_change_class_description(class_1,class_inheritance_path,
		frame_vector_length,class_features,
		all_slot_descriptions_for_class,T,class_user_vector_length,
		temp,temp_1,slot_descriptions_hash_table,
		full_hash_table_class,class_bit_number,class_bit_vector,
		temp_2, !TRUEP(user_defined_class_qm) ? T : Nil);
	mutate_global_or_kb_specific_property_value(class_1,
		user_defined_class_qm ? 
		copy_list_using_class_description_conses_1(direct_superior_classes) 
		: direct_superior_classes,Direct_superior_classes_gkbprop);
    }
    else {
	result = merge_slot_descriptions_for_system_defined_class(direct_superior_classes,
		class_inheritance_path,slot_descriptions_defined_for_class);
	MVS_3(result,all_slot_descriptions_for_class,class_vector_length,
		local_slots_for_class);
	result = make_slot_descriptions_hash_table(class_1,
		all_slot_descriptions_for_class,class_inheritance_path,
		direct_superior_classes,Nil);
	MVS_2(result,slot_descriptions_hash_table,full_hash_table_class);
	if (previous_direct_superior_classes_qm &&  
		!EQUAL(previous_direct_superior_classes_qm,
		direct_superior_classes)) {
	    superior = Nil;
	    ab_loop_list_ = previous_direct_superior_classes_qm;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(superior,direct_superior_classes))) {
		temp = superior;
		temp_1 = delete_eql(class_1,
			lookup_global_or_kb_specific_property_value(superior,
			Inferior_classes_gkbprop));
		mutate_global_or_kb_specific_property_value(temp,temp_1,
			Inferior_classes_gkbprop);
	    }
	    unpropagate_methods(2,superior,class_1);
	    goto next_loop_5;
	  end_loop_5:;
	}
	superior = Nil;
	ab_loop_list_ = direct_superior_classes;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(do_not_propagate_methods_qm) || 
		EQ(do_not_propagate_methods_qm,Qobsolete))
	    propagate_methods(2,superior,class_1);
	if ( !TRUEP(memq_function(class_1,
		lookup_global_or_kb_specific_property_value(superior,
		Inferior_classes_gkbprop)))) {
	    copy_kb_specific_property_from_global_if_necessary(superior,
		    Qinferior_classes);
	    temp = superior;
	    temp_1 = 
		    nconc2(lookup_global_or_kb_specific_property_value(superior,
		    Inferior_classes_gkbprop),
		    class_description_cons_1(class_1,Nil));
	    mutate_global_or_kb_specific_property_value(temp,temp_1,
		    Inferior_classes_gkbprop);
	}
	goto next_loop_6;
      end_loop_6:;
	mutate_global_or_kb_specific_property_value(class_1,
		class_definition,Class_definition_gkbprop);
	temp = memq_function(Qitem,class_inheritance_path) ? T : Nil;
	temp_1 = make_method_table_for_system_class();
	make_and_change_class_description(class_1,class_inheritance_path,
		class_vector_length,class_features,
		all_slot_descriptions_for_class,temp,FIX((SI_Long)0L),
		local_slots_for_class,Nil,slot_descriptions_hash_table,
		full_hash_table_class,class_bit_number,class_bit_vector,
		temp_1, !TRUEP(user_defined_class_qm) ? T : Nil);
	mutate_global_or_kb_specific_property_value(class_1,
		direct_superior_classes,Direct_superior_classes_gkbprop);
	if (System_class_method_tables_processed_qm)
	    initialize_or_update_method_tables_of_class_descriptions(class_1);
    }
    decache_cached_class_data(class_1);
    return VALUES_1(class_1);
}

/* GET-APPROPRIATE-SLOT-DESCRIPTIONS-CONS */
Object get_appropriate_slot_descriptions_cons(unique_slot_name,
	    slot_descriptions)
    Object unique_slot_name, slot_descriptions;
{
    Object sublist, car_of_slot_descriptions, temp;

    x_note_fn_call(81,17);
    if (slot_descriptions) {
	sublist = slot_descriptions;
	car_of_slot_descriptions = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	car_of_slot_descriptions = CAR(sublist);
	if (EQ(unique_slot_name,ISVREF(car_of_slot_descriptions,
		    (SI_Long)1L))) {
	    temp = sublist;
	    goto end_1;
	}
	sublist = M_CDR(sublist);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qvector_slot;        /* vector-slot */

static Object Qlookup_slot;        /* lookup-slot */

static Object Qsystem;             /* system */

/* MERGE-SLOT-DESCRIPTIONS-FOR-SYSTEM-DEFINED-CLASS */
Object merge_slot_descriptions_for_system_defined_class(direct_superior_classes,
	    class_inheritance_path,slot_descriptions_defined_for_class)
    Object direct_superior_classes, class_inheritance_path;
    Object slot_descriptions_defined_for_class;
{
    Object all_slot_descriptions_for_class, class_description;
    Object longest_vector_length, superior, ab_loop_list_;
    Object superior_vector_length, class_vector_length, slots_local_to_class;
    Object temp_class_list, slots_local_to_class_1, local_slot_name;
    Object ab_loop_list__1, slot_description, cons_holding_slot_description_qm;
    Object unique_slot_name, pretty_slot_name, car_new_value, slot_features;
    Object vector_slot_qm, current_slot_name_assignment_qm;
    Object future_slot_name_assignment;

    x_note_fn_call(81,18);
    all_slot_descriptions_for_class = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(FIRST(direct_superior_classes),
	    Class_description_gkbprop);
    longest_vector_length = ISVREF(class_description,(SI_Long)14L);
    superior = Nil;
    ab_loop_list_ = CDR(direct_superior_classes);
    superior_vector_length = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(superior,
	    Class_description_gkbprop);
    superior_vector_length = ISVREF(class_description,(SI_Long)14L);
    if (FIXNUM_GT(superior_vector_length,longest_vector_length))
	longest_vector_length = superior_vector_length;
    goto next_loop;
  end_loop:
    class_vector_length = longest_vector_length;
    goto end_1;
    class_vector_length = Qnil;
  end_1:;
    slots_local_to_class = Nil;
    temp_class_list = 
	    nreverse(copy_list_using_gensym_conses_1(CDR(class_inheritance_path)));
    superior = Nil;
    ab_loop_list_ = temp_class_list;
    class_description = Nil;
    slots_local_to_class_1 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(superior,
	    Class_description_gkbprop);
    slots_local_to_class_1 = ISVREF(class_description,(SI_Long)7L);
    local_slot_name = Nil;
    ab_loop_list__1 = slots_local_to_class_1;
    slot_description = Nil;
    cons_holding_slot_description_qm = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    local_slot_name = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    slot_description = 
	    get_slot_description_of_class_description_function(local_slot_name,
	    class_description,Nil);
    cons_holding_slot_description_qm = 
	    get_appropriate_slot_descriptions_cons(local_slot_name,
	    all_slot_descriptions_for_class);
    if (cons_holding_slot_description_qm)
	M_CAR(cons_holding_slot_description_qm) = slot_description;
    else
	all_slot_descriptions_for_class = 
		nconc2(all_slot_descriptions_for_class,
		LIST_1(slot_description));
    goto next_loop_2;
  end_loop_2:;
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(temp_class_list);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions_defined_for_class;
    unique_slot_name = Nil;
    pretty_slot_name = Nil;
    cons_holding_slot_description_qm = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
    cons_holding_slot_description_qm = 
	    get_appropriate_slot_descriptions_cons(unique_slot_name,
	    all_slot_descriptions_for_class);
    slots_local_to_class = nconc2(slots_local_to_class,
	    LIST_1(unique_slot_name));
    if (cons_holding_slot_description_qm) {
	car_new_value = 
		add_inherited_features_and_indexes_to_system_slot_description(slot_description,
		CAR(cons_holding_slot_description_qm),Nil);
	M_CAR(cons_holding_slot_description_qm) = car_new_value;
    }
    else {
	slot_features = ISVREF(slot_description,(SI_Long)9L);
	vector_slot_qm = assq_function(Qvector_slot,
		ISVREF(slot_description,(SI_Long)9L));
	current_slot_name_assignment_qm = 
		lookup_global_or_kb_specific_property_value(pretty_slot_name,
		Slot_name_assignment_gkbprop);
	future_slot_name_assignment = Nil;
	if (vector_slot_qm) {
	    SVREF(slot_description,FIX((SI_Long)7L)) = class_vector_length;
	    future_slot_name_assignment = class_vector_length;
	    class_vector_length = FIXNUM_ADD1(class_vector_length);
	}
	else
	    future_slot_name_assignment = Qlookup_slot;
	if (current_slot_name_assignment_qm && ( 
		!EQL(current_slot_name_assignment_qm,
		future_slot_name_assignment) || 
		lookup_global_or_kb_specific_property_value(pretty_slot_name,
		Old_slot_name_assignment_gkbprop)))
	    mutate_global_or_kb_specific_property_value(pretty_slot_name,
		    current_slot_name_assignment_qm,
		    Old_slot_name_assignment_gkbprop);
	mutate_global_or_kb_specific_property_value(pretty_slot_name,
		future_slot_name_assignment,Slot_name_assignment_gkbprop);
	if (assq_function(Qsystem,slot_features))
	    mutate_global_property(pretty_slot_name,Qsystem,Qslot_category);
	else if (assq_function(Qport,slot_features))
	    mutate_global_property(pretty_slot_name,Qport,Qslot_category);
	else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
		Qslot_category))
	    mutate_global_property(pretty_slot_name,Nil,Qslot_category);
	else;
	all_slot_descriptions_for_class = 
		nconc2(all_slot_descriptions_for_class,
		LIST_1(slot_description));
    }
    goto next_loop_3;
  end_loop_3:;
    return VALUES_3(all_slot_descriptions_for_class,class_vector_length,
	    slots_local_to_class);
}

/* COLLECT-USER-DEFINED-SLOT-DESCRIPTIONS-FOR-DEFINING-CLASS */
Object collect_user_defined_slot_descriptions_for_defining_class(defining_class,
	    slot_descriptions)
    Object defining_class, slot_descriptions;
{
    Object slot_description, ab_loop_list_, slot_description_defining_class;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(81,19);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_description_defining_class = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_description_defining_class = ISVREF(slot_description,(SI_Long)3L);
    if (EQ(slot_description_defining_class,defining_class) && 
	    ISVREF(slot_description,(SI_Long)8L)) {
	ab_loopvar__2 = frame_cons_1(slot_description,Nil);
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

/* GET-NEW-DEFAULT-SLOT-DESCRIPTION-WITH-PRETTY-NAME */
Object get_new_default_slot_description_with_pretty_name(slot_description_being_deleted,
	    class_description)
    Object slot_description_being_deleted, class_description;
{
    Object class_inheritance_path, pretty_slot_name;
    Object qualifying_slot_description_qm, slot_description, ab_loop_list_;
    Object temp_1;
    char temp;

    x_note_fn_call(81,20);
    class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
    pretty_slot_name = ISVREF(slot_description_being_deleted,(SI_Long)2L);
    qualifying_slot_description_qm = Nil;
    slot_description = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(slot_description,(SI_Long)2L),pretty_slot_name) &&  
	    !EQ(slot_description,slot_description_being_deleted)) {
	temp =  !TRUEP(qualifying_slot_description_qm);
	if (temp);
	else {
	    temp_1 = position(2,ISVREF(slot_description,(SI_Long)3L),
		    class_inheritance_path);
	    temp = FIXNUM_LT(temp_1,position(2,
		    ISVREF(qualifying_slot_description_qm,(SI_Long)3L),
		    class_inheritance_path));
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	qualifying_slot_description_qm = slot_description;
    goto next_loop;
  end_loop:
    return VALUES_1(qualifying_slot_description_qm);
    return VALUES_1(Qnil);
}

/* GET-SLOT-DESCRIPTION */
Object get_slot_description varargs_1(int, n)
{
    Object unique_or_pretty_slot_name, slot_descriptions;
    Object defining_class_qm, slot_description, ab_loop_list_;
    Object most_specific_default_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,21);
    INIT_ARGS_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    slot_descriptions = REQUIRED_ARG_nonrelocating();
    defining_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (defining_class_qm) {
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ((EQ(unique_or_pretty_slot_name,ISVREF(slot_description,
		(SI_Long)2L)) || EQ(unique_or_pretty_slot_name,
		ISVREF(slot_description,(SI_Long)1L))) && 
		EQ(defining_class_qm,ISVREF(slot_description,(SI_Long)3L)))
	    return VALUES_1(slot_description);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	most_specific_default_qm = Nil;
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(unique_or_pretty_slot_name,ISVREF(slot_description,
		(SI_Long)1L)))
	    return VALUES_1(slot_description);
	if (EQ(unique_or_pretty_slot_name,ISVREF(slot_description,
		(SI_Long)2L)))
	    most_specific_default_qm = slot_description;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(most_specific_default_qm);
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_user_overridable_system_slots, Qlist_of_user_overridable_system_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_variable_slots, Quser_overridable_variable_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_parameter_slots, Quser_overridable_parameter_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_g2_array_slots, Quser_overridable_g2_array_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_g2_list_slots, Quser_overridable_g2_list_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_object_slots, Quser_overridable_object_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_message_slots, Quser_overridable_message_slots);

DEFINE_VARIABLE_WITH_SYMBOL(User_overridable_connection_slots, Quser_overridable_connection_slots);

static Object Qcar_eq;             /* car-eq */

/* MAKE-LIST-OF-UNALIASED-USER-OVERRIDABLE-SYSTEM-SLOTS-FOR-CLASS */
Object make_list_of_unaliased_user_overridable_system_slots_for_class(class_inheritance_path)
    Object class_inheritance_path;
{
    Object list_to_return, class_1, ab_loop_list_, masked_slots_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp, slots_to_mask_qm;
    Object overridable_slots_for_class_qm, slot_name, ab_loop_list__1;
    char temp_1;

    x_note_fn_call(81,22);
    list_to_return = Nil;
    class_1 = Nil;
    ab_loop_list_ = class_inheritance_path;
    masked_slots_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = member(4,class_1,List_of_user_overridable_system_slots,
		Ktest,Qcar_eq);
	masked_slots_qm = FIFTH(CAR(temp));
    }
    else
	masked_slots_qm = Nil;
    ab_loopvar__2 = masked_slots_qm;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    slots_to_mask_qm = ab_loopvar_;
    goto end_1;
    slots_to_mask_qm = Qnil;
  end_1:;
    class_1 = Nil;
    ab_loop_list_ = class_inheritance_path;
    overridable_slots_for_class_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = member(4,class_1,List_of_user_overridable_system_slots,
		Ktest,Qcar_eq);
	temp = CAR(temp);
	overridable_slots_for_class_qm = FOURTH(temp);
    }
    else
	overridable_slots_for_class_qm = Nil;
    if (overridable_slots_for_class_qm) {
	slot_name = Nil;
	ab_loop_list__1 = overridable_slots_for_class_qm;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	slot_name = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(memq_function(slot_name,slots_to_mask_qm)))
	    list_to_return = frame_cons_1(slot_name,list_to_return);
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(list_to_return);
}

/* CAR-EQ */
Object car_eq(x,some_cons)
    Object x, some_cons;
{
    x_note_fn_call(81,23);
    return VALUES_1(EQ(x,CAR(some_cons)) ? T : Nil);
}

/* CAR-EQUAL */
Object car_equal(x,some_cons)
    Object x, some_cons;
{
    Object temp;

    x_note_fn_call(81,24);
    temp = CAR(some_cons);
    return VALUES_1(EQUAL(x,temp) ? T : Nil);
}

/* MERGE-SLOT-DESCRIPTIONS-FOR-USER-DEFINED-CLASS */
Object merge_slot_descriptions_for_user_defined_class(new_class,
	    new_class_inheritance_path,
	    new_class_specific_slot_descriptions,
	    slot_descriptions_for_overridden_slots_qm)
    Object new_class, new_class_inheritance_path;
    Object new_class_specific_slot_descriptions;
    Object slot_descriptions_for_overridden_slots_qm;
{
    Object class_cons, class_description, temp, superior_merging_point;
    Object merging_point_class_description, slot_descriptions_working_list;
    Object superior, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object superior_classes_below_merging_point_in_reverse_order_qm;
    Object class_description_qm, user_superior_classes_below_merging_point_qm;
    Object system_slots_overridden_by_most_refined_version;
    Object current_user_vector_slot_index;
    Object merging_point_class_inheritance_path, slot_description;
    Object unique_slot_name, new_class_slot_description_qm;
    Object most_specific_overriding_class, overriding_class_slot_description;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, inherited_user_vector_slot_index;
    Object slot_description_to_add, cons_holding_slot_description;
    Object user_slot_descriptions_to_add, last_system_defined_slot_description;
    Object ab_loop_list__1, local_slot_description;
    Object most_specific_slot_description, class_level_slot_description;
    Object working_list_slot_description_qm;
    Object preceding_slot_description_for_positioning;
    Object last_slot_description_in_list, sublist;
    Object slot_descriptions_cons_after_which_to_insert, symbol, property_name;
    Object temp_3, user_vector_slot_index_qm, superior_class_description;
    Object superior_slot_description_qm, working_list_slot_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(81,25);
    class_cons = CDR(new_class_inheritance_path);
  next_loop:
    if ( !TRUEP(class_cons))
	goto end_loop;
    class_description = 
	    lookup_global_or_kb_specific_property_value(CAR(class_cons),
	    Class_description_gkbprop);
    temp = ISVREF(class_description,(SI_Long)2L);
    if (EQUAL(class_cons,temp)) {
	superior_merging_point = CAR(class_cons);
	goto end_1;
    }
    class_cons = M_CDR(class_cons);
    goto next_loop;
  end_loop:
    superior_merging_point = Qnil;
  end_1:;
    merging_point_class_description = 
	    lookup_global_or_kb_specific_property_value(superior_merging_point,
	    Class_description_gkbprop);
    slot_descriptions_working_list = 
	    copy_list_using_class_description_conses_1(ISVREF(merging_point_class_description,
	    (SI_Long)6L));
    superior = Nil;
    ab_loop_list_ = CDR(new_class_inheritance_path);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(superior,superior_merging_point))
	goto end_loop_1;
    ab_loopvar__2 = frame_cons_1(superior,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    superior_classes_below_merging_point_in_reverse_order_qm = nreverse(temp);
    superior = Nil;
    ab_loop_list_ = CDR(new_class_inheritance_path);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(superior,superior_merging_point))
	goto end_loop_2;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(superior,
	    Class_description_gkbprop);
    if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L))) {
	ab_loopvar__2 = frame_cons_1(superior,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_2;
  end_loop_2:
    user_superior_classes_below_merging_point_qm = ab_loopvar_;
    goto end_3;
    user_superior_classes_below_merging_point_qm = Qnil;
  end_3:;
    system_slots_overridden_by_most_refined_version = Nil;
    current_user_vector_slot_index = 
	    ISVREF(merging_point_class_description,(SI_Long)15L);
    if ( !((zerop(current_user_vector_slot_index) ||  
	    !TRUEP(user_superior_classes_below_merging_point_qm)) &&  
	    !TRUEP(slot_descriptions_for_overridden_slots_qm))) {
	merging_point_class_inheritance_path = 
		ISVREF(merging_point_class_description,(SI_Long)2L);
	slot_description = Nil;
	ab_loop_list_ = slot_descriptions_working_list;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	slot_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ISVREF(slot_description,(SI_Long)8L)) {
	    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
	    new_class_slot_description_qm = get_slot_description(2,
		    unique_slot_name,
		    slot_descriptions_for_overridden_slots_qm);
	    most_specific_overriding_class = new_class_slot_description_qm 
		    ? new_class : 
		    most_specific_superior_that_refines_slot(new_class_inheritance_path,
		    slot_description);
	    if ( !TRUEP(memq_function(most_specific_overriding_class,
		    merging_point_class_inheritance_path))) {
		overriding_class_slot_description = 
			new_class_slot_description_qm;
		if (overriding_class_slot_description);
		else {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = most_specific_overriding_class;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(most_specific_overriding_class) 
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_5:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_6:
		    if ( !TRUEP(marked))
			goto end_loop_5;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_6;
		  end_loop_5:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_4;
		    goto next_loop_5;
		  end_loop_6:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_4;
		  end_loop_4:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = most_specific_overriding_class;
			temp_1 = Symbol_properties_table;
			temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_2 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_2,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			gensymed_symbol = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
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
		  next_loop_7:
		    if (level < ab_loop_bind_)
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_8:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_9:
		    if ( !TRUEP(marked))
			goto end_loop_8;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_9;
		  end_loop_8:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_5;
		    goto next_loop_8;
		  end_loop_9:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_7;
		  end_loop_7:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_11:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_12:
			if ( !TRUEP(marked))
			    goto end_loop_11;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_12;
		      end_loop_11:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_6;
			goto next_loop_11;
		      end_loop_12:
		      end_6:
			level = level - (SI_Long)1L;
			goto next_loop_10;
		      end_loop_10:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_14:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_15:
			if ( !TRUEP(marked))
			    goto end_loop_14;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_15;
		      end_loop_14:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_7;
			goto next_loop_14;
		      end_loop_15:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_13;
		      end_loop_13:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    overriding_class_slot_description = 
			    get_slot_description_of_class_description_function(unique_slot_name,
			    gensymed_symbol,Nil);
		}
		inherited_user_vector_slot_index = ISVREF(slot_description,
			(SI_Long)8L);
		temp = ISVREF(overriding_class_slot_description,(SI_Long)8L);
		slot_description_to_add = EQL(temp,
			inherited_user_vector_slot_index) ? 
			overriding_class_slot_description : 
			make_slot_description(8,
			ISVREF(overriding_class_slot_description,
			(SI_Long)2L),
			ISVREF(overriding_class_slot_description,
			(SI_Long)3L),new_class,
			ISVREF(overriding_class_slot_description,
			(SI_Long)5L),
			ISVREF(overriding_class_slot_description,
			(SI_Long)6L),Nil,inherited_user_vector_slot_index,
			ISVREF(overriding_class_slot_description,(SI_Long)9L));
		cons_holding_slot_description = 
			memq_function(slot_description,
			slot_descriptions_working_list);
		M_CAR(cons_holding_slot_description) = slot_description_to_add;
	    }
	}
	goto next_loop_3;
      end_loop_3:;
    }
    if (superior_classes_below_merging_point_in_reverse_order_qm) {
	user_slot_descriptions_to_add = Nil;
	last_system_defined_slot_description = Nil;
	superior = Nil;
	ab_loop_list_ = 
		superior_classes_below_merging_point_in_reverse_order_qm;
	class_description = Nil;
      next_loop_16:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_16;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	if ( !TRUEP(ISVREF(class_description,(SI_Long)20L))) {
	    unique_slot_name = Nil;
	    ab_loop_list__1 = ISVREF(class_description,(SI_Long)7L);
	    local_slot_description = Nil;
	    most_specific_slot_description = Nil;
	    slot_description_to_add = Nil;
	  next_loop_17:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_17;
	    unique_slot_name = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    local_slot_description = 
		    get_slot_description_of_class_description_function(unique_slot_name,
		    class_description,Nil);
	    temp = get_slot_description(2,unique_slot_name,
		    slot_descriptions_for_overridden_slots_qm);
	    if (temp);
	    else
		temp = 
			slot_description_of_most_specific_superior_refining_slot(new_class_inheritance_path,
			local_slot_description);
	    most_specific_slot_description = temp;
	    temp = ISVREF(most_specific_slot_description,(SI_Long)8L);
	    slot_description_to_add = EQL(temp,
		    current_user_vector_slot_index) ? 
		    most_specific_slot_description : 
		    make_slot_description(8,
		    ISVREF(most_specific_slot_description,(SI_Long)2L),
		    ISVREF(most_specific_slot_description,(SI_Long)3L),
		    new_class,ISVREF(most_specific_slot_description,
		    (SI_Long)5L),ISVREF(most_specific_slot_description,
		    (SI_Long)6L),Nil,current_user_vector_slot_index,
		    ISVREF(most_specific_slot_description,(SI_Long)9L));
	    user_slot_descriptions_to_add = 
		    class_description_cons_1(slot_description_to_add,
		    user_slot_descriptions_to_add);
	    current_user_vector_slot_index = 
		    FIXNUM_ADD1(current_user_vector_slot_index);
	    goto next_loop_17;
	  end_loop_17:;
	}
	else {
	    unique_slot_name = Nil;
	    ab_loop_list__1 = ISVREF(class_description,(SI_Long)7L);
	    class_level_slot_description = Nil;
	    working_list_slot_description_qm = Nil;
	  next_loop_18:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_18;
	    unique_slot_name = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    class_level_slot_description = 
		    get_slot_description_of_class_description_function(unique_slot_name,
		    class_description,Nil);
	    working_list_slot_description_qm = get_slot_description(2,
		    unique_slot_name,slot_descriptions_working_list);
	    if (working_list_slot_description_qm) {
		cons_holding_slot_description = 
			memq_function(working_list_slot_description_qm,
			slot_descriptions_working_list);
		if (EQ(CAR(cons_holding_slot_description),
			last_system_defined_slot_description))
		    last_system_defined_slot_description = 
			    class_level_slot_description;
		M_CAR(cons_holding_slot_description) = 
			class_level_slot_description;
	    }
	    else {
		if (last_system_defined_slot_description)
		    preceding_slot_description_for_positioning = 
			    last_system_defined_slot_description;
		else {
		    temp = last(slot_descriptions_working_list,_);
		    last_slot_description_in_list = CAR(temp);
		    if (ISVREF(last_slot_description_in_list,(SI_Long)8L)) {
			sublist = slot_descriptions_working_list;
		      next_loop_19:
			if ( !TRUEP(sublist))
			    goto end_loop_19;
			if (ISVREF(SECOND(sublist),(SI_Long)8L)) {
			    preceding_slot_description_for_positioning = 
				    FIRST(sublist);
			    goto end_8;
			}
			sublist = M_CDR(sublist);
			goto next_loop_19;
		      end_loop_19:
			preceding_slot_description_for_positioning = Qnil;
		      end_8:;
		    }
		    else
			preceding_slot_description_for_positioning = 
				last_slot_description_in_list;
		}
		slot_descriptions_cons_after_which_to_insert = 
			memq_function(preceding_slot_description_for_positioning,
			slot_descriptions_working_list);
		temp_2 = 
			class_description_cons_1(class_level_slot_description,
			CDR(slot_descriptions_cons_after_which_to_insert));
		M_CDR(slot_descriptions_cons_after_which_to_insert) = temp_2;
		last_system_defined_slot_description = 
			class_level_slot_description;
	    }
	    goto next_loop_18;
	  end_loop_18:;
	}
	goto next_loop_16;
      end_loop_16:
	temp = slot_descriptions_working_list;
	slot_descriptions_working_list = nconc2(temp,
		nreverse(user_slot_descriptions_to_add));
	reclaim_frame_list_1(superior_classes_below_merging_point_in_reverse_order_qm);
    }
    user_slot_descriptions_to_add = Nil;
    slot_description = Nil;
    ab_loop_list_ = new_class_specific_slot_descriptions;
  next_loop_20:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_20;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
	cons_holding_slot_description = 
		get_appropriate_slot_descriptions_cons(unique_slot_name,
		slot_descriptions_working_list);
	system_slots_overridden_by_most_refined_version = 
		frame_cons_1(unique_slot_name,
		system_slots_overridden_by_most_refined_version);
	temp = slot_description;
	symbol = ISVREF(slot_description,(SI_Long)3L);
	property_name = Class_description_gkbprop;
	skip_list = CDR(Symbol_properties_table);
	key_value = symbol;
	key_hash_value = SXHASH_SYMBOL_1(symbol) & IFIX(Most_positive_fixnum);
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
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
      next_loop_23:
	if ( !TRUEP(marked))
	    goto end_loop_22;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_23;
      end_loop_22:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_9;
	goto next_loop_22;
      end_loop_23:
      end_9:
	level = level - (SI_Long)1L;
	goto next_loop_21;
      end_loop_21:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = symbol;
	    temp_3 = Symbol_properties_table;
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
	    gensymed_symbol = set_skip_list_entry(temp_3,FIX((SI_Long)31L),
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
      next_loop_24:
	if (level < ab_loop_bind_)
	    goto end_loop_24;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_25:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
      next_loop_26:
	if ( !TRUEP(marked))
	    goto end_loop_25;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_26;
      end_loop_25:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_10;
	goto next_loop_25;
      end_loop_26:
      end_10:
	level = level - (SI_Long)1L;
	goto next_loop_24;
      end_loop_24:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = property_name;
	    key_hash_value = SXHASH_SYMBOL_1(property_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_29;
	  end_loop_28:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_11;
	    goto next_loop_28;
	  end_loop_29:
	  end_11:
	    level = level - (SI_Long)1L;
	    goto next_loop_27;
	  end_loop_27:;
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
	    key_value = property_name;
	    key_hash_value = SXHASH_SYMBOL_1(property_name) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_30:
	    if (level < ab_loop_bind_)
		goto end_loop_30;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_31:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_32:
	    if ( !TRUEP(marked))
		goto end_loop_31;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_32;
	  end_loop_31:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_12;
	    goto next_loop_31;
	  end_loop_32:
	  end_12:
	    level = level - (SI_Long)1L;
	    goto next_loop_30;
	  end_loop_30:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	temp_2 = 
		add_inherited_features_and_indexes_to_system_slot_description(temp,
		get_slot_description_of_class_description_function(unique_slot_name,
		gensymed_symbol,Nil),T);
	M_CAR(cons_holding_slot_description) = temp_2;
    }
    else {
	user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	if (FIXNUMP(user_vector_slot_index_qm))
	    slot_description_to_add = FIXNUM_EQ(user_vector_slot_index_qm,
		    current_user_vector_slot_index) ? slot_description : 
		    make_slot_description(8,ISVREF(slot_description,
		    (SI_Long)2L),new_class,new_class,
		    ISVREF(slot_description,(SI_Long)5L),
		    ISVREF(slot_description,(SI_Long)6L),Nil,
		    current_user_vector_slot_index,ISVREF(slot_description,
		    (SI_Long)9L));
	else {
	    SVREF(slot_description,FIX((SI_Long)8L)) = 
		    current_user_vector_slot_index;
	    slot_description_to_add = slot_description;
	}
	user_slot_descriptions_to_add = 
		class_description_cons_1(slot_description_to_add,
		user_slot_descriptions_to_add);
	current_user_vector_slot_index = 
		FIXNUM_ADD1(current_user_vector_slot_index);
    }
    goto next_loop_20;
  end_loop_20:
    temp = slot_descriptions_working_list;
    slot_descriptions_working_list = nconc2(temp,
	    nreverse(user_slot_descriptions_to_add));
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions_for_overridden_slots_qm;
  next_loop_33:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_33;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
	cons_holding_slot_description = 
		get_appropriate_slot_descriptions_cons(unique_slot_name,
		slot_descriptions_working_list);
	system_slots_overridden_by_most_refined_version = 
		frame_cons_1(unique_slot_name,
		system_slots_overridden_by_most_refined_version);
	M_CAR(cons_holding_slot_description) = slot_description;
    }
    goto next_loop_33;
  end_loop_33:;
    if (user_superior_classes_below_merging_point_qm) {
	superior = Nil;
	ab_loop_list_ = user_superior_classes_below_merging_point_qm;
	superior_class_description = Nil;
      next_loop_34:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_34;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	superior_class_description = 
		lookup_global_or_kb_specific_property_value(superior,
		Class_description_gkbprop);
	unique_slot_name = Nil;
	ab_loop_list__1 = ISVREF(superior_class_description,(SI_Long)8L);
	superior_slot_description_qm = Nil;
      next_loop_35:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_35;
	unique_slot_name = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	superior_slot_description_qm = 
		get_slot_description_of_class_description_function(unique_slot_name,
		superior_class_description,Nil);
	if (superior_slot_description_qm) {
	    if ( !TRUEP(memq_function(unique_slot_name,
		    system_slots_overridden_by_most_refined_version))) {
		working_list_slot_description = get_slot_description(2,
			unique_slot_name,slot_descriptions_working_list);
		if ( !TRUEP(ISVREF(working_list_slot_description,
			    (SI_Long)8L))) {
		    system_slots_overridden_by_most_refined_version = 
			    frame_cons_1(unique_slot_name,
			    system_slots_overridden_by_most_refined_version);
		    cons_holding_slot_description = 
			    memq_function(working_list_slot_description,
			    slot_descriptions_working_list);
		    temp_2 = 
			    get_slot_description_of_class_description_function(unique_slot_name,
			    superior_class_description,Nil);
		    M_CAR(cons_holding_slot_description) = temp_2;
		}
	    }
	}
	goto next_loop_35;
      end_loop_35:;
	goto next_loop_34;
      end_loop_34:
	reclaim_frame_list_1(user_superior_classes_below_merging_point_qm);
    }
    if (system_slots_overridden_by_most_refined_version)
	reclaim_frame_list_1(system_slots_overridden_by_most_refined_version);
    return VALUES_2(slot_descriptions_working_list,
	    current_user_vector_slot_index);
}

/* ADD-INHERITED-FEATURES-AND-INDEXES-TO-SYSTEM-SLOT-DESCRIPTION */
Object add_inherited_features_and_indexes_to_system_slot_description(slot_description,
	    superior_slot_description,user_defined_class_qm)
    Object slot_description, superior_slot_description, user_defined_class_qm;
{
    Object svref_new_value, slot_features, superior_slot_features;
    Object superior_feature, ab_loop_list_, temp, gensymed_symbol;

    x_note_fn_call(81,26);
    svref_new_value = ISVREF(superior_slot_description,(SI_Long)7L);
    SVREF(slot_description,FIX((SI_Long)7L)) = svref_new_value;
    slot_features = ISVREF(slot_description,(SI_Long)9L);
    superior_slot_features = ISVREF(superior_slot_description,(SI_Long)9L);
    superior_feature = Nil;
    ab_loop_list_ = superior_slot_features;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior_feature = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(assq_function(FIRST(superior_feature),slot_features))) {
	if (user_defined_class_qm)
	    svref_new_value = 
		    class_description_cons_1(copy_tree_using_class_description_conses_1(superior_feature),
		    ISVREF(slot_description,(SI_Long)9L));
	else {
	    temp = ISVREF(slot_description,(SI_Long)9L);
	    gensymed_symbol = make_permanent_list(FIX((SI_Long)1L));
	    M_CAR(gensymed_symbol) = superior_feature;
	    svref_new_value = nconc2(temp,gensymed_symbol);
	}
	SVREF(slot_description,FIX((SI_Long)9L)) = svref_new_value;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(slot_description);
}

static Object string_constant;     /* "The direct superior class, ~A, of class ~A is not defined.~
				    *             ~%It was defined when this class definition was initially ~
				    *             evaluated.~
				    *             ~%The user is advised to recompile/load the definition of ~
				    *             the superior class."
				    */

/* CHECK-IF-SUPERIOR-CLASSES-ARE-DEFINED */
Object check_if_superior_classes_are_defined(class_1,direct_superior_classes)
    Object class_1, direct_superior_classes;
{
    Object direct_superior, ab_loop_list_, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp, temp_1, entry_hash, gensymed_symbol;
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(81,27);
    direct_superior = Nil;
    ab_loop_list_ = direct_superior_classes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    direct_superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(direct_superior)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = direct_superior;
	key_hash_value = SXHASH_SYMBOL_1(direct_superior) & 
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
	    gensymed_symbol = direct_superior;
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	errorn(3,string_constant,direct_superior,class_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SYSTEM-CLASS-P */
Object system_class_p(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(81,28);
    temp = lookup_global_or_kb_specific_property_value(symbol,
	    Class_definition_gkbprop);
    return VALUES_1(CONSP(temp) ? T : Nil);
}

Object Aliases_for_slot_name_prop = UNBOUND;

Object Slot_names_for_alias_prop = UNBOUND;

static Object Qaliases_for_slot_name;  /* aliases-for-slot-name */

static Object Qslot_names_for_alias;  /* slot-names-for-alias */

/* ALIAS-SLOT-NAME */
Object alias_slot_name varargs_1(int, n)
{
    Object pretty_slot_name, alias;
    Object class_qm, association_qm, push_arg, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,29);
    INIT_ARGS_nonrelocating();
    pretty_slot_name = REQUIRED_ARG_nonrelocating();
    alias = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    association_qm = assq_function(class_qm,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
	    Qaliases_for_slot_name));
    if (association_qm)
	M_CDR(association_qm) = alias;
    else {
	push_arg = CONS(class_qm,alias);
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
		Qaliases_for_slot_name);
	temp_1 = CONS(push_arg,temp);
	mutate_global_property(pretty_slot_name,temp_1,Qaliases_for_slot_name);
    }
    association_qm = assq_function(class_qm,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(alias),
	    Qslot_names_for_alias));
    if (association_qm)
	return VALUES_1(M_CDR(association_qm) = pretty_slot_name);
    else {
	push_arg = CONS(class_qm,pretty_slot_name);
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(alias),
		Qslot_names_for_alias);
	temp_1 = CONS(push_arg,temp);
	return mutate_global_property(alias,temp_1,Qslot_names_for_alias);
    }
}

/* GET-ALIAS-FOR-SLOT-NAME-IF-ANY */
Object get_alias_for_slot_name_if_any(pretty_slot_name,class_or_frame)
    Object pretty_slot_name, class_or_frame;
{
    Object alist, temp, class_description, global_alias_qm, class_qm, alias;
    Object ab_loop_list_, ab_loop_desetq_, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(81,30);
    alist = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
	    Qaliases_for_slot_name);
    if (alist) {
	temp = M_CAR(alist);
	if ( !TRUEP(CAR(temp)) &&  !TRUEP(CDR(alist))) {
	    temp = FIRST(alist);
	    temp = CDR(temp);
	}
	else {
	    class_description = SYMBOLP(class_or_frame) ? 
		    lookup_global_or_kb_specific_property_value(class_or_frame,
		    Class_description_gkbprop) : ISVREF(class_or_frame,
		    (SI_Long)1L);
	    global_alias_qm = Nil;
	    class_qm = Nil;
	    alias = Nil;
	    ab_loop_list_ = alist;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    class_qm = CAR(ab_loop_desetq_);
	    alias = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(class_qm))
		global_alias_qm = alias;
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(class_description,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp = alias;
		    goto end_1;
		}
	    }
	    goto next_loop;
	  end_loop:
	    temp = global_alias_qm;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* GET-SLOT-NAME-FOR-ALIAS-IF-ANY */
Object get_slot_name_for_alias_if_any(alias,
	    class_or_frame_or_class_description)
    Object alias, class_or_frame_or_class_description;
{
    Object alist_qm, class_description_qm, temp, global_slot_name_qm, class_qm;
    Object pretty_slot_name, ab_loop_list_, ab_loop_desetq_, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(81,31);
    alist_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(alias),
	    Qslot_names_for_alias);
    if (SYMBOLP(class_or_frame_or_class_description))
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(class_or_frame_or_class_description,
		Class_description_gkbprop);
    else if (SIMPLE_VECTOR_P(class_or_frame_or_class_description) && 
	    EQ(ISVREF(class_or_frame_or_class_description,(SI_Long)0L),
	    Qg2_defstruct_structure_name_class_description_g2_struct))
	class_description_qm = class_or_frame_or_class_description;
    else
	class_description_qm = ISVREF(class_or_frame_or_class_description,
		(SI_Long)1L);
    if (alist_qm && class_description_qm) {
	temp = FIRST(alist_qm);
	if ( !TRUEP(CAR(temp)) &&  !TRUEP(CDR(alist_qm))) {
	    temp = FIRST(alist_qm);
	    temp = CDR(temp);
	}
	else {
	    global_slot_name_qm = Nil;
	    class_qm = Nil;
	    pretty_slot_name = Nil;
	    ab_loop_list_ = alist_qm;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    class_qm = CAR(ab_loop_desetq_);
	    pretty_slot_name = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(class_qm))
		global_slot_name_qm = pretty_slot_name;
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(class_description_qm,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp = pretty_slot_name;
		    goto end_1;
		}
	    }
	    goto next_loop;
	  end_loop:
	    temp = global_slot_name_qm;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* SET-OWNER-CLASS-OF-METHOD-TABLE */
Object set_owner_class_of_method_table(method_table,class_name)
    Object method_table, class_name;
{
    x_note_fn_call(81,32);
    return VALUES_1(SVREF(method_table,Maximum_number_of_generic_methods) 
	    = class_name);
}

/* MAKE-METHOD-TABLE-FOR-SYSTEM-CLASS */
Object make_method_table_for_system_class()
{
    x_note_fn_call(81,33);
    return make_array(3,add1(Maximum_number_of_generic_methods),
	    Kinitial_element,Nil);
}

/* RECLAIM-METHOD-TABLE-OF-CLASS-DESCRIPTION */
Object reclaim_method_table_of_class_description(method_table)
    Object method_table;
{
    Object method_table_sub_vector_qm, temp;
    SI_Long index_1;

    x_note_fn_call(81,34);
    index_1 = (SI_Long)0L;
    method_table_sub_vector_qm = Nil;
  next_loop:
    if (index_1 >= IFIX(Maximum_number_of_generic_methods))
	goto end_loop;
    method_table_sub_vector_qm = ISVREF(method_table,index_1);
    if (method_table_sub_vector_qm)
	reclaim_managed_simple_vector(method_table_sub_vector_qm);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_managed_simple_vector(method_table);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Table_to_map_generic_method_id_to_generic_method_name, Qtable_to_map_generic_method_id_to_generic_method_name);

/* INITIALIZE-METHOD-TABLE-OF-CLASS-DESCRIPTION */
Object initialize_method_table_of_class_description(method_table,
	    class_inheritance_path,user_defined_class_qm)
    Object method_table, class_inheritance_path, user_defined_class_qm;
{
    Object generic_method_name, class_specific_methods_with_name_on_path_qm;
    Object number_of_methods_on_path, sub_vector_qm, class_1, ab_loop_list_;
    Object class_specific_method_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object list_1, method_sub_list, svref_new_value, temp;
    SI_Long generic_method_id, index_1, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(81,35);
    generic_method_id = (SI_Long)0L;
    generic_method_name = Nil;
    class_specific_methods_with_name_on_path_qm = Nil;
    number_of_methods_on_path = Nil;
    sub_vector_qm = Nil;
  next_loop:
    if (generic_method_id >= IFIX(Maximum_number_of_generic_methods))
	goto end_loop;
    generic_method_name = 
	    ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
	    generic_method_id);
    class_1 = Nil;
    ab_loop_list_ = class_inheritance_path;
    class_specific_method_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    list_1 = INLINE_SYMBOL_PLIST(class_1);
  next_loop_2:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),generic_method_name))
	goto end_loop_2;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_2;
  end_loop_2:
    class_specific_method_qm = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (class_specific_method_qm) {
	ab_loopvar__2 = frame_cons_1(frame_list_2(class_1,
		class_specific_method_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    class_specific_methods_with_name_on_path_qm = ab_loopvar_;
    goto end_1;
    class_specific_methods_with_name_on_path_qm = Qnil;
  end_1:;
    number_of_methods_on_path = 
	    length(class_specific_methods_with_name_on_path_qm);
    sub_vector_qm = class_specific_methods_with_name_on_path_qm ? 
	    (user_defined_class_qm ? 
	    allocate_managed_simple_vector(FIX(IFIX(number_of_methods_on_path) 
	    * (SI_Long)2L)) : make_array(1,
	    FIX(IFIX(number_of_methods_on_path) * (SI_Long)2L))) : Nil;
    if (sub_vector_qm) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = 
		IFIX(FIXNUM_SUB1(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)));
	method_sub_list = Nil;
	ab_loop_list_ = class_specific_methods_with_name_on_path_qm;
      next_loop_3:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_3;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	method_sub_list = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	svref_new_value = M_CAR(method_sub_list);
	ISVREF(sub_vector_qm,index_1) = svref_new_value;
	svref_arg_2 = index_1 + (SI_Long)1L;
	svref_new_value = SECOND(method_sub_list);
	ISVREF(sub_vector_qm,svref_arg_2) = svref_new_value;
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop_3;
      end_loop_3:
	reclaim_frame_tree_1(class_specific_methods_with_name_on_path_qm);
	ISVREF(method_table,generic_method_id) = sub_vector_qm;
    }
    else
	ISVREF(method_table,generic_method_id) = Nil;
    generic_method_id = generic_method_id + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = set_owner_class_of_method_table(method_table,
	    CAR(class_inheritance_path));
    return VALUES_1(temp);
}

/* METHOD-TABLES-ARE-EQUIVALENT-P */
Object method_tables_are_equivalent_p(table1,table2)
    Object table1, table2;
{
    Object table1_sub_vector_for_index_qm, table1_sub_vector_length_qm;
    Object table2_sub_vector_for_index_qm, table2_sub_vector_length_qm;
    Object ab_loop_it_;
    SI_Long index_1, index_2, ab_loop_bind_;
    char temp;

    x_note_fn_call(81,36);
    index_1 = (SI_Long)0L;
    table1_sub_vector_for_index_qm = Nil;
    table1_sub_vector_length_qm = Nil;
    table2_sub_vector_for_index_qm = Nil;
    table2_sub_vector_length_qm = Nil;
  next_loop:
    if (index_1 >= IFIX(Maximum_number_of_generic_methods))
	goto end_loop;
    table1_sub_vector_for_index_qm = ISVREF(table1,index_1);
    table1_sub_vector_length_qm = table1_sub_vector_for_index_qm ? 
	    SIMPLE_ARRAY_ANY_1_LENGTH(table1_sub_vector_for_index_qm) : Nil;
    table2_sub_vector_for_index_qm = ISVREF(table2,index_1);
    table2_sub_vector_length_qm = table2_sub_vector_for_index_qm ? 
	    SIMPLE_ARRAY_ANY_1_LENGTH(table2_sub_vector_for_index_qm) : Nil;
    if ( !( !TRUEP(table1_sub_vector_for_index_qm) &&  
	    !TRUEP(table2_sub_vector_for_index_qm))) {
	temp = table1_sub_vector_for_index_qm ?  
		!TRUEP(table2_sub_vector_for_index_qm) : TRUEP(Qnil);
	if (temp);
	else
	    temp =  !TRUEP(table1_sub_vector_for_index_qm) ? 
		    TRUEP(table2_sub_vector_for_index_qm) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUM_NE(table1_sub_vector_length_qm,
		    table2_sub_vector_length_qm);
	if (temp);
	else {
	    index_2 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(table1_sub_vector_length_qm);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if (index_2 >= ab_loop_bind_)
		goto end_loop_1;
	    ab_loop_it_ =  !EQ(ISVREF(table1_sub_vector_for_index_qm,
		    index_2),ISVREF(table2_sub_vector_for_index_qm,
		    index_2)) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    index_2 = index_2 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	}
	if (temp)
	    return VALUES_1(Nil);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(table2);
    return VALUES_1(Qnil);
}

/* EQUIVALENT-METHOD-TABLE-ON-PATH-P */
Object equivalent_method_table_on_path_p(user_class_method_table,
	    class_inheritance_path)
    Object user_class_method_table, class_inheritance_path;
{
    Object superior_class, ab_loop_list_, superior_class_method_table_qm;
    Object equivalent_method_table_qm, class_description_qm, temp;

    x_note_fn_call(81,37);
    superior_class = Nil;
    ab_loop_list_ = M_CDR(class_inheritance_path);
    superior_class_method_table_qm = Nil;
    equivalent_method_table_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop);
    superior_class_method_table_qm = class_description_qm &&  
	    !TRUEP(ISVREF(class_description_qm,(SI_Long)20L)) ? 
	    ISVREF(lookup_global_or_kb_specific_property_value(superior_class,
	    Class_description_gkbprop),(SI_Long)11L) : Nil;
    equivalent_method_table_qm = superior_class_method_table_qm ? 
	    method_tables_are_equivalent_p(user_class_method_table,
	    superior_class_method_table_qm) : Qnil;
    if (equivalent_method_table_qm) {
	temp = equivalent_method_table_qm;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* INITIALIZE-OR-UPDATE-METHOD-TABLE-FOR-USER-CLASS */
Object initialize_or_update_method_table_for_user_class(user_class,
	    class_inheritance_path,new_class_qm)
    Object user_class, class_inheritance_path, new_class_qm;
{
    Object user_class_description, existing_user_class_method_table_qm;
    Object gensymed_symbol, pre_existing_method_table_from_class_hierarchy_qm;
    Object new_vector, new_method_table;
    Object new_table_equivalent_to_existing_table_qm;
    Object user_class_is_owner_of_pre_existing_obsolete_table_qm;
    Object equivalent_method_table_on_path_qm, usable_method_table;
    Object scope_conses, ab_loopvar_, class_1, subclass_description;
    Object subclass_method_table_qm, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(81,38);
    user_class_description = 
	    lookup_global_or_kb_specific_property_value(user_class,
	    Class_description_gkbprop);
    if ( !TRUEP(new_class_qm)) {
	existing_user_class_method_table_qm = 
		ISVREF(user_class_description,(SI_Long)11L);
	if (existing_user_class_method_table_qm) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(user_class,
		    Class_description_gkbprop);
	    temp = gensymed_symbol ? 
		    TRUEP(memq_function(ISVREF(existing_user_class_method_table_qm,
		    IFIX(Maximum_number_of_generic_methods)),
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	pre_existing_method_table_from_class_hierarchy_qm = temp ? 
		existing_user_class_method_table_qm : Nil;
    }
    else
	pre_existing_method_table_from_class_hierarchy_qm = Nil;
    new_vector = 
	    allocate_managed_simple_vector(add1(Maximum_number_of_generic_methods));
    initialize_method_table_of_class_description(new_vector,
	    class_inheritance_path,T);
    new_method_table = new_vector;
    new_table_equivalent_to_existing_table_qm = 
	    pre_existing_method_table_from_class_hierarchy_qm ? 
	    method_tables_are_equivalent_p(new_method_table,
	    pre_existing_method_table_from_class_hierarchy_qm) : Qnil;
    user_class_is_owner_of_pre_existing_obsolete_table_qm = 
	    pre_existing_method_table_from_class_hierarchy_qm ? ( 
	    !TRUEP(new_table_equivalent_to_existing_table_qm) ? 
	    (EQ(ISVREF(pre_existing_method_table_from_class_hierarchy_qm,
	    IFIX(Maximum_number_of_generic_methods)),user_class) ? T : 
	    Nil) : Nil) : Nil;
    equivalent_method_table_on_path_qm =  
	    !TRUEP(new_table_equivalent_to_existing_table_qm) ? 
	    equivalent_method_table_on_path_p(new_method_table,
	    class_inheritance_path) : Nil;
    if (new_class_qm) {
	if (equivalent_method_table_on_path_qm) {
	    reclaim_method_table_of_class_description(new_method_table);
	    return VALUES_1(equivalent_method_table_on_path_qm);
	}
	else
	    return VALUES_1(new_method_table);
    }
    else if (new_table_equivalent_to_existing_table_qm)
	return reclaim_method_table_of_class_description(new_method_table);
    else {
	if (user_class_is_owner_of_pre_existing_obsolete_table_qm) {
	    usable_method_table = equivalent_method_table_on_path_qm ? 
		    equivalent_method_table_on_path_qm : new_method_table;
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = user_class;
	    class_1 = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      subclass_description = Nil;
	      subclass_method_table_qm = Nil;
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      temp_1 = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      class_1 = temp_1;
	      subclass_description = 
		      lookup_global_or_kb_specific_property_value(class_1,
		      Class_description_gkbprop);
	      subclass_method_table_qm = ISVREF(subclass_description,
		      (SI_Long)11L);
	      if (subclass_method_table_qm && EQ(subclass_method_table_qm,
		      pre_existing_method_table_from_class_hierarchy_qm))
		  SVREF(subclass_description,FIX((SI_Long)11L)) = 
			  usable_method_table;
	      goto next_loop;
	    end_loop:;
	    POP_SPECIAL();
	    reclaim_method_table_of_class_description(pre_existing_method_table_from_class_hierarchy_qm);
	}
	if (equivalent_method_table_on_path_qm) {
	    reclaim_method_table_of_class_description(new_method_table);
	    return VALUES_1(SVREF(user_class_description,
		    FIX((SI_Long)11L)) = equivalent_method_table_on_path_qm);
	}
	else
	    return VALUES_1(SVREF(user_class_description,
		    FIX((SI_Long)11L)) = new_method_table);
    }
}

/* INITIALIZE-OR-UPDATE-METHOD-TABLES-OF-CLASS-DESCRIPTIONS */
Object initialize_or_update_method_tables_of_class_descriptions(node)
    Object node;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, subclass, subclass_description;
    Object subclass_inheritance_path, subclass_method_table, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, ab_loopvar__4, current_classes_variable_set;
    Object sublist, class_to_add, superior, ab_loop_list_, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(81,39);
    scope_conses = Scope_conses;
    ab_loopvar_ = node;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      subclass_description = Nil;
      subclass_inheritance_path = Nil;
      subclass_method_table = Nil;
      if (SYMBOLP(ab_loopvar_)) {
	  skip_list = CDR(Symbol_properties_table);
	  key_value = ab_loopvar_;
	  key_hash_value = SXHASH_SYMBOL_1(ab_loopvar_) & 
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = ab_loopvar_;
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
	  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		  ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (kb_properties);
	  else
	      kb_properties = Nil;
	  if (kb_properties) {
	      skip_list = CDR(kb_properties);
	      key_value = Class_description_gkbprop;
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		      & IFIX(Most_positive_fixnum);
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
	  temp_2 = TRUEP(resulting_value);
      }
      else
	  temp_2 = TRUEP(Nil);
      ab_loopvar__3 = temp_2 ? scope_cons(ab_loopvar_,Nil) : Nil;
    next_loop_12:
      if ( !TRUEP(ab_loopvar__3))
	  goto end_loop_12;
      temp_1 = M_CAR(ab_loopvar__3);
      ab_loopvar__2 = scope_cons(M_CAR(ab_loopvar__3),ab_loopvar__2);
      ab_loopvar__4 = 
	      lookup_global_or_kb_specific_property_value(M_CAR(ab_loopvar__3),
	      Inferior_classes_gkbprop);
      if (ab_loopvar__4) {
	  temp = ab_loopvar__1;
	  ab_loopvar__1 = nconc2(temp,scope_cons(ab_loopvar__4,Nil));
      }
      ab_loopvar__3 = M_CDR(ab_loopvar__3);
      current_classes_variable_set = Nil;
    next_loop_13:
      if (current_classes_variable_set)
	  goto end_loop_13;
      sublist = ab_loopvar__3;
      class_to_add = Nil;
    next_loop_14:
      if ( !TRUEP(sublist))
	  goto end_loop_14;
      class_to_add = M_CAR(sublist);
      if ( !TRUEP(sublist))
	  goto end_loop_14;
      temp_2 = TRUEP(memq_function(M_CAR(sublist),ab_loopvar__2));
      if (temp_2);
      else {
	  superior = Nil;
	  ab_loop_list_ = 
		  lookup_global_or_kb_specific_property_value(class_to_add,
		  Direct_superior_classes_gkbprop);
	  ab_loop_it_ = Nil;
	next_loop_15:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_15;
	  superior = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = 
		  lookup_global_or_kb_specific_property_value(superior,
		  Class_description_gkbprop);
	  ab_loop_it_ = (gensymed_symbol ? TRUEP(memq_function(ab_loopvar_,
		  ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? ( 
		  !TRUEP(memq_function(superior,ab_loopvar__2)) ? T : Nil) 
		  : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_5;
	  }
	  goto next_loop_15;
	end_loop_15:
	  temp_2 = TRUEP(Qnil);
	end_5:;
      }
      if ( !temp_2) {
	  ab_loopvar__3 = sublist;
	  current_classes_variable_set = T;
	  goto end_loop_14;
      }
      sublist = M_CDR(sublist);
      goto next_loop_14;
    end_loop_14:
      if ( !TRUEP(current_classes_variable_set)) {
	  ab_loopvar__3 = CAR(ab_loopvar__1);
	  if (ab_loopvar__1)
	      ab_loopvar__1 = M_CDR(ab_loopvar__1);
	  else
	      current_classes_variable_set = T;
      }
      goto next_loop_13;
    end_loop_13:;
      subclass = temp_1;
      subclass_description = 
	      lookup_global_or_kb_specific_property_value(subclass,
	      Class_description_gkbprop);
      subclass_inheritance_path = ISVREF(subclass_description,(SI_Long)2L);
      subclass_method_table = ISVREF(subclass_description,(SI_Long)11L);
      if (lookup_global_or_kb_specific_property_value(subclass,
	      Class_description_gkbprop)) {
	  temp_1 = lookup_global_or_kb_specific_property_value(subclass,
		  Class_definition_gkbprop);
	  temp_2 = CONSP(temp_1);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2)
	  initialize_method_table_of_class_description(subclass_method_table,
		  subclass_inheritance_path,Nil);
      else
	  initialize_or_update_method_table_for_user_class(subclass,
		  subclass_inheritance_path,Nil);
      goto next_loop_12;
    end_loop_12:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* INSTALL-GENERIC-METHOD-ID */
Object install_generic_method_id(generic_method_name,new_id)
    Object generic_method_name, new_id;
{
    Object old_name, svref_arg_1;

    x_note_fn_call(81,40);
    old_name = 
	    ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
	    IFIX(new_id));
    if ( !SYMBOLP(generic_method_name) ||  !FIXNUMP(new_id) ||  
	    !((SI_Long)-1L < IFIX(new_id) && FIXNUM_LT(new_id,
	    Maximum_number_of_generic_methods)))
	error((SI_Long)3L,
		"Bad generic-method-name symbol or id: name = ~a, id = ~a.",
		generic_method_name,new_id);
    else if (old_name &&  !EQ(old_name,generic_method_name))
	warn((SI_Long)4L,
		"Changing generic-method id number ~a from ~a to ~a.",
		new_id,old_name,generic_method_name);
    svref_arg_1 = Table_to_map_generic_method_id_to_generic_method_name;
    SVREF(svref_arg_1,new_id) = generic_method_name;
    return VALUES_1(generic_method_name);
}

Object Generic_method_lambda_list_prop = UNBOUND;

/* PROPAGATE-METHOD */
Object propagate_method varargs_1(int, n)
{
    Object method, method_definition, class_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,41);
    INIT_ARGS_nonrelocating();
    method = REQUIRED_ARG_nonrelocating();
    method_definition = REQUIRED_ARG_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* PROPAGATE-METHODS */
Object propagate_methods varargs_1(int, n)
{
    Object source_class, target_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,42);
    INIT_ARGS_nonrelocating();
    source_class = REQUIRED_ARG_nonrelocating();
    target_class = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    else
	INLINE_SYMBOL_PLIST(source_class);
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* UNPROPAGATE-METHODS */
Object unpropagate_methods varargs_1(int, n)
{
    Object source_class, target_class;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,43);
    INIT_ARGS_nonrelocating();
    source_class = REQUIRED_ARG_nonrelocating();
    target_class = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    else
	INLINE_SYMBOL_PLIST(source_class);
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

/* COPY-METHODS */
Object copy_methods(source_class,target_class)
    Object source_class, target_class;
{
    x_note_fn_call(81,44);
    return VALUES_1(Nil);
}

/* GET-SLOT-DESCRIPTION-VALUE */
Object get_slot_description_value(frame,slot_description)
    Object frame, slot_description;
{
    Object vector_slot_index_qm, temp, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,45);
    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
    if (vector_slot_index_qm)
	temp = ISVREF(frame,IFIX(vector_slot_index_qm));
    else {
	user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	if (user_vector_slot_index_qm)
	    temp = ISVREF(ISVREF(frame,(SI_Long)0L),
		    IFIX(user_vector_slot_index_qm));
	else {
	    slot_name = ISVREF(slot_description,(SI_Long)1L);
	    lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
	    if (lookup_structure_qm) {
		max_i = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		max_i = max_i - (SI_Long)1L;
		i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		ab_loop_bind_ = max_i;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
		    slot_index_qm = FIX(i + (SI_Long)1L);
		    goto end_1;
		}
		i = i + (SI_Long)2L;
		goto next_loop;
	      end_loop:
		slot_index_qm = Qnil;
	      end_1:;
		temp = slot_index_qm ? ISVREF(lookup_structure_qm,
			IFIX(slot_index_qm)) : ISVREF(slot_description,
			(SI_Long)6L);
	    }
	    else
		temp = ISVREF(slot_description,(SI_Long)6L);
	}
    }
    return VALUES_1(temp);
}

/* GET-LOOKUP-SLOT-VALUE-GIVEN-DEFAULT */
Object get_lookup_slot_value_given_default(frame,slot_name,default_value)
    Object frame, slot_name, default_value;
{
    Object temp, lookup_structure_qm, slot_index_qm;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,46);
    if ( !TRUEP(frame))
	temp = default_value;
    else {
	lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
	if (lookup_structure_qm) {
	    max_i = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
	    max_i = max_i - (SI_Long)1L;
	    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
	    ab_loop_bind_ = max_i;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
		slot_index_qm = FIX(i + (SI_Long)1L);
		goto end_1;
	    }
	    i = i + (SI_Long)2L;
	    goto next_loop;
	  end_loop:
	    slot_index_qm = Qnil;
	  end_1:;
	    temp = slot_index_qm ? ISVREF(lookup_structure_qm,
		    IFIX(slot_index_qm)) : default_value;
	}
	else
	    temp = default_value;
    }
    return VALUES_1(temp);
}

/* GET-LOOKUP-SLOT-VALUE */
Object get_lookup_slot_value(frame,slot_name)
    Object frame, slot_name;
{
    Object lookup_structure_qm, slot_index_qm, temp;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,47);
    lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
    if (lookup_structure_qm) {
	max_i = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
	max_i = max_i - (SI_Long)1L;
	i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
	ab_loop_bind_ = max_i;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
	    slot_index_qm = FIX(i + (SI_Long)1L);
	    goto end_1;
	}
	i = i + (SI_Long)2L;
	goto next_loop;
      end_loop:
	slot_index_qm = Qnil;
      end_1:;
	temp = slot_index_qm ? ISVREF(lookup_structure_qm,
		IFIX(slot_index_qm)) : 
		ISVREF(get_slot_description_of_class_description_function(slot_name,
		ISVREF(frame,(SI_Long)1L),Nil),(SI_Long)6L);
    }
    else
	temp = 
		ISVREF(get_slot_description_of_class_description_function(slot_name,
		ISVREF(frame,(SI_Long)1L),Nil),(SI_Long)6L);
    return VALUES_1(temp);
}

/* GET-SLOT-VALUE-FUNCTION */
Object get_slot_value_function(frame,unique_or_pretty_slot_name,
	    class_if_specific_qm)
    Object frame, unique_or_pretty_slot_name, class_if_specific_qm;
{
    Object slot_description_qm, vector_slot_index_qm, temp;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,48);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    if (slot_description_qm) {
	vector_slot_index_qm = ISVREF(slot_description_qm,(SI_Long)7L);
	if (vector_slot_index_qm)
	    temp = ISVREF(frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description_qm,
		    (SI_Long)8L);
	    if (user_vector_slot_index_qm)
		temp = ISVREF(ISVREF(frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description_qm,(SI_Long)1L);
		lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop:
		    if (i >= ab_loop_bind_)
			goto end_loop;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop;
		  end_loop:
		    slot_index_qm = Qnil;
		  end_1:;
		    temp = slot_index_qm ? ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : 
			    ISVREF(slot_description_qm,(SI_Long)6L);
		}
		else
		    temp = ISVREF(slot_description_qm,(SI_Long)6L);
	    }
	}
    }
    else
	temp = error((SI_Long)3L,"Frame ~S has no ~A slot",frame,
		unique_or_pretty_slot_name);
    return VALUES_1(temp);
}

/* GET-SLOT-VALUE-IF-ANY-FUNCTION */
Object get_slot_value_if_any_function(frame,unique_or_pretty_slot_name,
	    class_if_specific_qm)
    Object frame, unique_or_pretty_slot_name, class_if_specific_qm;
{
    Object slot_description_qm, vector_slot_index_qm, temp;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,49);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    if (slot_description_qm) {
	vector_slot_index_qm = ISVREF(slot_description_qm,(SI_Long)7L);
	if (vector_slot_index_qm)
	    temp = ISVREF(frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description_qm,
		    (SI_Long)8L);
	    if (user_vector_slot_index_qm)
		temp = ISVREF(ISVREF(frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description_qm,(SI_Long)1L);
		lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop:
		    if (i >= ab_loop_bind_)
			goto end_loop;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop;
		  end_loop:
		    slot_index_qm = Qnil;
		  end_1:;
		    temp = slot_index_qm ? ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : 
			    ISVREF(slot_description_qm,(SI_Long)6L);
		}
		else
		    temp = ISVREF(slot_description_qm,(SI_Long)6L);
	    }
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object No_slot = UNBOUND;

/* GET-SLOT-VALUE-OR-NO-SLOT-FUNCTION */
Object get_slot_value_or_no_slot_function(frame,unique_or_pretty_slot_name,
	    class_if_specific_qm)
    Object frame, unique_or_pretty_slot_name, class_if_specific_qm;
{
    Object slot_description_qm, vector_slot_index_qm, temp;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm;
    SI_Long max_i, i, ab_loop_bind_;

    x_note_fn_call(81,50);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    if (slot_description_qm) {
	vector_slot_index_qm = ISVREF(slot_description_qm,(SI_Long)7L);
	if (vector_slot_index_qm)
	    temp = ISVREF(frame,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description_qm,
		    (SI_Long)8L);
	    if (user_vector_slot_index_qm)
		temp = ISVREF(ISVREF(frame,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description_qm,(SI_Long)1L);
		lookup_structure_qm = ISVREF(frame,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop:
		    if (i >= ab_loop_bind_)
			goto end_loop;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop;
		  end_loop:
		    slot_index_qm = Qnil;
		  end_1:;
		    temp = slot_index_qm ? ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : 
			    ISVREF(slot_description_qm,(SI_Long)6L);
		}
		else
		    temp = ISVREF(slot_description_qm,(SI_Long)6L);
	    }
	}
    }
    else
	temp = No_slot;
    return VALUES_1(temp);
}

/* SET-LOOKUP-SLOT-VALUE-1 */
Object set_lookup_slot_value_1(frame,pretty_lookup_slot_name,value)
    Object frame, pretty_lookup_slot_name, value;
{
    Object slot_description_qm, temp;

    x_note_fn_call(81,51);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(pretty_lookup_slot_name,
	    ISVREF(frame,(SI_Long)1L),Nil);
    temp = slot_description_qm ? 
	    set_slot_description_value_without_noting(frame,
	    slot_description_qm,value) : Nil;
    return VALUES_1(temp);
}

/* SET-NON-SAVABLE-LOOKUP-SLOT-VALUE */
Object set_non_savable_lookup_slot_value(frame,pretty_lookup_slot_name,value)
    Object frame, pretty_lookup_slot_name, value;
{
    Object slot_description_qm, temp;

    x_note_fn_call(81,52);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(pretty_lookup_slot_name,
	    ISVREF(frame,(SI_Long)1L),Nil);
    temp = set_slot_description_value_without_noting(frame,
	    slot_description_qm,value);
    return VALUES_1(temp);
}

Object Frame_lookup_structure_vector_allocation_schemes = UNBOUND;

/* ALLOCATE-FRAME-LOOKUP-STRUCTURE-VECTOR */
Object allocate_frame_lookup_structure_vector(length_init,dont_initialize)
    Object length_init, dont_initialize;
{
    Object new_vector;
    SI_Long length_1, actual_length, index_1, ab_loop_bind_;

    x_note_fn_call(81,53);
    length_1 = IFIX(length_init);
    actual_length = IFIX(buffer_size_for_partial_buffer(FIX(length_1),
	    Frame_lookup_structure_vector_allocation_schemes));
    new_vector = allocate_managed_simple_vector(FIX(actual_length));
    if ( !TRUEP(dont_initialize)) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = actual_length;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(new_vector,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(new_vector);
}

/* SET-SLOT-DESCRIPTION-VALUE-WITHOUT-NOTING */
Object set_slot_description_value_without_noting(frame,slot_description,value)
    Object frame, slot_description, value;
{
    Object vector_slot_index_qm, user_vector_slot_index_qm, lookup_structure;
    Object unique_slot_name, first_available_location_qm;
    Object mission_accomplished_qm, lookup_slot_name, temp, entry_location;
    Object new_lookup_structure, gensymed_symbol, gensymed_symbol_3;
    SI_Long lookup_structure_length, class_user_vector_length, index_1;
    SI_Long svref_arg_2, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_4;

    x_note_fn_call(81,54);
    vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
    if (vector_slot_index_qm)
	SVREF(frame,vector_slot_index_qm) = value;
    else {
	user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	lookup_structure = ISVREF(frame,(SI_Long)0L);
	if (user_vector_slot_index_qm)
	    SVREF(lookup_structure,user_vector_slot_index_qm) = value;
	else {
	    lookup_structure_length = lookup_structure ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure)) : 
		    (SI_Long)0L;
	    unique_slot_name = ISVREF(slot_description,(SI_Long)1L);
	    class_user_vector_length = IFIX(ISVREF(ISVREF(frame,
		    (SI_Long)1L),(SI_Long)15L));
	    index_1 = class_user_vector_length;
	    first_available_location_qm = Nil;
	    mission_accomplished_qm = Nil;
	    if (EQ(value,ISVREF(slot_description,(SI_Long)6L))) {
		lookup_slot_name = Nil;
	      next_loop:
		if ( !(index_1 < lookup_structure_length))
		    goto end_loop;
		lookup_slot_name = ISVREF(lookup_structure,index_1);
		if (EQ(lookup_slot_name,unique_slot_name)) {
		    ISVREF(lookup_structure,index_1) = Nil;
		    svref_arg_2 = index_1 + (SI_Long)1L;
		    ISVREF(lookup_structure,svref_arg_2) = Nil;
		    mission_accomplished_qm = T;
		    goto end_loop;
		}
		else
		    index_1 = index_1 + (SI_Long)2L;
		goto next_loop;
	      end_loop:
		mission_accomplished_qm = T;
	    }
	    else {
		lookup_slot_name = Nil;
	      next_loop_1:
		if ( !(index_1 < lookup_structure_length))
		    goto end_loop_1;
		lookup_slot_name = ISVREF(lookup_structure,index_1);
		if (EQ(lookup_slot_name,unique_slot_name)) {
		    svref_arg_2 = index_1 + (SI_Long)1L;
		    ISVREF(lookup_structure,svref_arg_2) = value;
		    mission_accomplished_qm = T;
		    goto end_loop_1;
		}
		else if ( !TRUEP(lookup_slot_name) &&  
			!TRUEP(first_available_location_qm)) {
		    first_available_location_qm = FIX(index_1);
		    index_1 = index_1 + (SI_Long)2L;
		}
		else
		    index_1 = index_1 + (SI_Long)2L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    if ( !TRUEP(mission_accomplished_qm)) {
		if (first_available_location_qm && lookup_structure_length 
			> IFIX(FIXNUM_ADD1(first_available_location_qm))) {
		    SVREF(lookup_structure,first_available_location_qm) = 
			    unique_slot_name;
		    temp = FIXNUM_ADD1(first_available_location_qm);
		    SVREF(lookup_structure,temp) = value;
		}
		else {
		    entry_location = first_available_location_qm;
		    if (entry_location);
		    else
			entry_location = FIX(index_1);
		    new_lookup_structure = 
			    allocate_frame_lookup_structure_vector(FIX(IFIX(entry_location) 
			    + (SI_Long)2L),Nil);
		    if (lookup_structure) {
			gensymed_symbol = lookup_structure;
			gensymed_symbol_1 = (SI_Long)0L;
			gensymed_symbol_2 = gensymed_symbol_1 + 
				lookup_structure_length;
			gensymed_symbol_3 = new_lookup_structure;
			gensymed_symbol_4 = (SI_Long)0L;
		      next_loop_2:
			if ( !(gensymed_symbol_1 < gensymed_symbol_2))
			    goto end_loop_2;
			temp = ISVREF(gensymed_symbol,gensymed_symbol_1);
			ISVREF(gensymed_symbol_3,gensymed_symbol_4) = temp;
			gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
			gensymed_symbol_4 = gensymed_symbol_4 + (SI_Long)1L;
			goto next_loop_2;
		      end_loop_2:;
			reclaim_managed_simple_vector(lookup_structure);
		    }
		    SVREF(frame,FIX((SI_Long)0L)) = new_lookup_structure;
		    SVREF(new_lookup_structure,entry_location) = 
			    unique_slot_name;
		    temp = FIXNUM_ADD1(entry_location);
		    SVREF(new_lookup_structure,temp) = value;
		}
	    }
	}
    }
    return VALUES_1(value);
}

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qnote_slot_changes;  /* note-slot-changes */

/* SET-SLOT-VALUE-FUNCTION */
Object set_slot_value_function(frame,unique_or_pretty_slot_name,new_value,
	    class_if_specific_qm)
    Object frame, unique_or_pretty_slot_name, new_value, class_if_specific_qm;
{
    Object slot_description_qm, slot_features, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(81,55);
    slot_description_qm = 
	    get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    if (slot_description_qm) {
	if (Noting_changes_to_kb_p) {
	    slot_features = ISVREF(slot_description_qm,(SI_Long)9L);
	    temp = assq_function(Qtype,slot_features) ?  
		    !TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		    TRUEP(assq_function(Qsave,slot_features));
	    if (temp);
	    else
		temp = TRUEP(assq_function(Qnote_slot_changes,
			ISVREF(slot_description_qm,(SI_Long)9L)));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
	    if (temp)
		note_change_to_block_1(frame,ISVREF(slot_description_qm,
			(SI_Long)2L));
	    else
		note_change_to_dependent_frame_1();
	}
	temp_1 = set_slot_description_value_without_noting(frame,
		slot_description_qm,new_value);
    }
    else
	temp_1 = error((SI_Long)3L,"Frame ~S has no ~A slot",frame,
		unique_or_pretty_slot_name);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_note_permanent_changes_p, Qdo_not_note_permanent_changes_p);

static Object Qslot_putter;        /* slot-putter */

static Object Qput_attribute_value;  /* put-attribute-value */

/* INITIALIZE-SLOT-DESCRIPTION-VALUE */
Object initialize_slot_description_value(frame,slot_description,new_value)
    Object frame, slot_description, new_value;
{
    Object pretty_slot_name, slot_putter_qm, list_1;
    Object do_not_note_permanent_changes_p, temp;
    Declare_special(1);

    x_note_fn_call(81,56);
    if ( !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	slot_putter_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(pretty_slot_name),
		Qslot_putter);
	if (slot_putter_qm);
	else {
	    list_1 = INLINE_SYMBOL_PLIST(pretty_slot_name);
	  next_loop:
	    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qslot_category))
		goto end_loop;
	    list_1 = M_CDR(M_CDR(list_1));
	    goto next_loop;
	  end_loop:;
	    slot_putter_qm =  !(list_1 ? TRUEP(M_CAR(M_CDR(list_1))) : 
		    TRUEP(Nil)) ? Qput_attribute_value : Nil;
	}
    }
    else
	slot_putter_qm = Qput_attribute_value;
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      if ( !TRUEP(slot_putter_qm))
	  temp = set_slot_description_value_without_noting(frame,
		  slot_description,new_value);
      else if (EQ(slot_putter_qm,Qput_attribute_value))
	  temp = put_attribute_description_value(frame,slot_description,
		  new_value,T);
      else
	  temp = inline_funcall_3(slot_putter_qm,frame,new_value,T);
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* GET-SLOT-INIT-FORM */
Object get_slot_init_form varargs_1(int, n)
{
    Object class_1, unique_or_pretty_slot_name;
    Object class_if_specific_qm, class_description_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(81,57);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    unique_or_pretty_slot_name = REQUIRED_ARG_nonrelocating();
    class_if_specific_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    if (class_description_qm)
	return VALUES_1(ISVREF(get_slot_description_of_class_description_function(unique_or_pretty_slot_name,
		class_description_qm,class_if_specific_qm),(SI_Long)6L));
    else
	return VALUES_1(Nil);
}

/* CLASS-FUNCTION */
Object class_function(frame)
    Object frame;
{
    x_note_fn_call(81,58);
    return VALUES_1(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L));
}

/* SLOT-VALUE-FLOAT-P-FUNCTION */
Object slot_value_float_p_function(thing)
    Object thing;
{
    x_note_fn_call(81,59);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* SLOT-VALUE-LONG-P-FUNCTION */
Object slot_value_long_p_function(thing)
    Object thing;
{
    x_note_fn_call(81,60);
    if (INLINE_LONG_VECTOR_P(thing) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == 
		(SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* MAKE-SLOT-VALUE-FLOAT */
Object make_slot_value_float(gensym_float)
    Object gensym_float;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value;

    x_note_fn_call(81,61);
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
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(gensym_float);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* MAKE-SLOT-VALUE-LONG */
Object make_slot_value_long(gensym_long)
    Object gensym_long;
{
    Object new_long;
    SI_int64 aref_new_value;

    x_note_fn_call(81,62);
    new_long = allocate_managed_long_box();
    aref_new_value = INTEGER_TO_INT64(gensym_long);
    set_aref1(new_long,FIX((SI_Long)0L),INT64_TO_INTEGER(aref_new_value));
    return VALUES_1(new_long);
}

/* SLOT-VALUE-NUMBER-P */
Object slot_value_number_p(slot_value)
    Object slot_value;
{
    Object temp;

    x_note_fn_call(81,63);
    temp = FIXNUMP(slot_value) ? T : Nil;
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(slot_value) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(NUMBERP(slot_value) ? T : Nil);
}

/* ATOMIC-SLOT-VALUE-P */
Object atomic_slot_value_p(x)
    Object x;
{
    Object temp;

    x_note_fn_call(81,64);
    temp = ATOM(x) ? T : Nil;
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ? T : 
		Nil) : Qnil;
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(x) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ? T : 
		Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(x,No_value) ? T : Nil);
}

static Object float_constant;      /* 0.0 */

static Object Qab_structure;       /* structure */

/* SLOT-VALUE-EQUAL-P */
Object slot_value_equal_p(x,y)
    Object x, y;
{
    Object temp, float_x, float_y, gensymed_symbol, held_vector, x_value;
    Object gensymed_symbol_1, held_vector_1, y_value, elt_1, validated_elt;
    Object x_key, attribute_value, y_key, held_vector_2, y_key1, y_value1;
    SI_Long next_index, length_1, next_index_1, length_2, gensymed_symbol_2;
    SI_Long next_index_2, length_3;
    char temp_1;
    double arg, arg_1;

    x_note_fn_call(81,65);
    temp = EQ(x,y) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (FIXNUMP(x) && FIXNUMP(y))
	return VALUES_1(Nil);
    else if (slot_value_number_p(x) && slot_value_number_p(y)) {
	if (FIXNUMP(x))
	    float_x = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(x));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    float_x = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    float_x = lfloat(aref1(x,FIX((SI_Long)0L)),float_constant);
	else
	    float_x = x;
	if (FIXNUMP(y))
	    float_y = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(y));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
	    float_y = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(y,(SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
	    float_y = lfloat(aref1(y,FIX((SI_Long)0L)),float_constant);
	else
	    float_y = y;
	arg = DOUBLE_FLOAT_TO_DOUBLE(float_x);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(float_y);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg))
	    return VALUES_1( !inline_nanp_for_comparison(arg_1) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (text_string_p(x)) {
	if (text_string_p(y))
	    return string_eq_w(x,y);
	else
	    return VALUES_1(Nil);
    }
    else if (text_string_p(y)) {
	if (text_string_p(x))
	    return string_eq_w(x,y);
	else
	    return VALUES_1(Nil);
    }
    else if (ATOM(x)) {
	if ( !SYMBOLP(x))
	    return VALUES_1(EQUAL(x,y) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else if (ATOM(y))
	return VALUES_1(Nil);
    else if (CONSP(x) && EQ(M_CDR(x),Qsequence)) {
	if (CONSP(y) && EQ(M_CDR(y),Qsequence) && 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(x),(SI_Long)1L))) == 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(y),(SI_Long)1L)))) {
	    gensymed_symbol = x;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    x_value = Nil;
	    gensymed_symbol_1 = y;
	    held_vector_1 = Nil;
	    next_index_1 = (SI_Long)1L;
	    length_2 = (SI_Long)0L;
	    y_value = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	    held_vector_1 = M_CAR(gensymed_symbol_1);
	    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	  next_loop:
	    if (next_index >= length_1)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    x_value = validated_elt;
	    if (next_index_1 >= length_2)
		goto end_loop;
	    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
		    next_index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index_1 & 
		    (SI_Long)1023L);
	    validated_elt = elt_1 ? 
		    validate_item_or_evaluation_value(elt_1,Nil,Nil) : Nil;
	    next_index_1 = next_index_1 + (SI_Long)1L;
	    y_value = validated_elt;
	    if ( !TRUEP(slot_value_equal_p(x_value,y_value)))
		return VALUES_1(Nil);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(T);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(x) && EQ(M_CDR(x),Qab_structure)) {
	if (CONSP(y) && EQ(M_CDR(y),Qab_structure)) {
	    if (FIXNUM_EQ(ISVREF(M_CAR(x),(SI_Long)1L),ISVREF(M_CAR(y),
		    (SI_Long)1L))) {
		gensymed_symbol = x;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		x_key = Nil;
		attribute_value = Nil;
		x_value = Nil;
		gensymed_symbol_1 = y;
		held_vector_1 = Nil;
		next_index_1 = (SI_Long)1L;
		length_2 = (SI_Long)0L;
		y_key = Nil;
		attribute_value = Nil;
		y_value = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
		held_vector_1 = M_CAR(gensymed_symbol_1);
		length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
	      next_loop_1:
		if (next_index >= length_1)
		    goto end_loop_1;
		x_key = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(gensymed_symbol_2 >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 
			& (SI_Long)1023L);
		x_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index = next_index + (SI_Long)2L;
		if (next_index_1 >= length_2)
		    goto end_loop_1;
		y_key = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
			Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,next_index_1 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index_1 & 
			(SI_Long)1023L);
		gensymed_symbol_2 = next_index_1 + (SI_Long)1L;
		attribute_value = FIXNUM_LE(ISVREF(held_vector_1,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(held_vector_1,gensymed_symbol_2 + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector_1,(gensymed_symbol_2 >>  
			-  - (SI_Long)10L) + (SI_Long)2L),
			gensymed_symbol_2 & (SI_Long)1023L);
		y_value = 
			validate_item_or_evaluation_value(attribute_value,
			Nil,Nil);
		next_index_1 = next_index_1 + (SI_Long)2L;
		if (EQ(x_key,y_key))
		    temp_1 = TRUEP(slot_value_equal_p(x_value,y_value));
		else {
		    gensymed_symbol = y;
		    held_vector_2 = Nil;
		    next_index_2 = (SI_Long)1L;
		    length_3 = (SI_Long)0L;
		    y_key1 = Nil;
		    attribute_value = Nil;
		    y_value1 = Nil;
		    held_vector_2 = M_CAR(gensymed_symbol);
		    length_3 = IFIX(ISVREF(held_vector_2,(SI_Long)1L));
		  next_loop_2:
		    if (next_index_2 >= length_3)
			goto end_loop_2;
		    y_key1 = FIXNUM_LE(ISVREF(held_vector_2,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(held_vector_2,next_index_2 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector_2,(next_index_2 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L),next_index_2 
			    & (SI_Long)1023L);
		    gensymed_symbol_2 = next_index_2 + (SI_Long)1L;
		    attribute_value = FIXNUM_LE(ISVREF(held_vector_2,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    ISVREF(held_vector_2,gensymed_symbol_2 + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(held_vector_2,(gensymed_symbol_2 
			    >>  -  - (SI_Long)10L) + (SI_Long)2L),
			    gensymed_symbol_2 & (SI_Long)1023L);
		    y_value1 = 
			    validate_item_or_evaluation_value(attribute_value,
			    Nil,Nil);
		    next_index_2 = next_index_2 + (SI_Long)2L;
		    if (EQ(x_key,y_key1)) {
			temp_1 = TRUEP(slot_value_equal_p(x_value,y_value1));
			goto end_1;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp_1 = TRUEP(Qnil);
		  end_1:;
		}
		if ( !temp_1)
		    return VALUES_1(Nil);
		goto next_loop_1;
	      end_loop_1:
		return VALUES_1(T);
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (slot_value_equal_p(CAR(x),CAR(y)))
	return slot_value_equal_p(CDR(x),CDR(y));
    else
	return VALUES_1(Nil);
}

/* SLOT-VALUE-CONS-FUNCTION */
Object slot_value_cons_function(car_1,cdr_1)
    Object car_1, cdr_1;
{
    x_note_fn_call(81,66);
    return slot_value_cons_1(car_1,cdr_1);
}

/* RECLAIM-SLOT-VALUE-CONS-FUNCTION */
Object reclaim_slot_value_cons_function(cons_1)
    Object cons_1;
{
    x_note_fn_call(81,67);
    return reclaim_slot_value_cons_1(cons_1);
}

/* RECLAIM-SLOT-VALUE-TREE-FUNCTION */
Object reclaim_slot_value_tree_function(tree)
    Object tree;
{
    x_note_fn_call(81,68);
    return reclaim_slot_value_tree_1(tree);
}

static Object Qdefault_slot_constant;  /* default-slot-constant */

/* MAKE-SLOT-CONSTANT */
Object make_slot_constant(number_or_string,unit_qm,default_value_case_qm)
    Object number_or_string, unit_qm, default_value_case_qm;
{
    x_note_fn_call(81,69);
    if (default_value_case_qm)
	return slot_value_cons_1(number_or_string,
		slot_value_cons_1(unit_qm,Qdefault_slot_constant));
    else
	return slot_value_list_2(number_or_string,unit_qm);
}

/* RECLAIM-SLOT-CONSTANT */
Object reclaim_slot_constant(the_constant)
    Object the_constant;
{
    x_note_fn_call(81,70);
    return reclaim_slot_value_list_star_1(the_constant);
}

/* MAKE-SLOT-CONSTANT-USING-PHRASE-CONSES */
Object make_slot_constant_using_phrase_conses(number_or_string,unit_qm)
    Object number_or_string, unit_qm;
{
    x_note_fn_call(81,71);
    return phrase_cons(number_or_string,phrase_cons(unit_qm,Nil));
}

/* GET-SLOT-VALUE-NUMBER-VALUE-OR-STRING-FROM-SLOT-CONSTANT */
Object get_slot_value_number_value_or_string_from_slot_constant(slot_constant)
    Object slot_constant;
{
    Object value;

    x_note_fn_call(81,72);
    value = M_CAR(slot_constant);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value,
		(SI_Long)0L)));
    else
	return VALUES_1(value);
}

Object Slot_value_reclaimer_prop = UNBOUND;

/* RECLAIM-LOOKUP-STRUCTURE-VALUE */
Object reclaim_lookup_structure_value(vector_qm,gensymed_symbol)
    Object vector_qm, gensymed_symbol;
{
    x_note_fn_call(81,73);
    return VALUES_1(Nil);
}

/* RECLAIM-CLASS-DESCRIPTION-SLOT-VALUE */
Object reclaim_class_description_slot_value(class_description,gensymed_symbol)
    Object class_description, gensymed_symbol;
{
    x_note_fn_call(81,74);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Dependent_frame_class_description, Qdependent_frame_class_description);

static Object Qdefined_evaluation_type_reclaimer;  /* defined-evaluation-type-reclaimer */

static Object Qab_slot_value;      /* slot-value */

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* RECLAIM-INITIAL-SLOT-VALUE */
Object reclaim_initial_slot_value(slot_value)
    Object slot_value;
{
    Object slot_value_cdr, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol;
    Object gensymed_symbol_1, slot_cons, car_value, next_cdr, slot_value_cons;
    Object temp_3, svref_arg_2, x2, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, index_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_2;
    Object result;

    x_note_fn_call(81,75);
    if (SYMBOLP(slot_value) || FIXNUMP(slot_value) || EQ(slot_value,No_value))
	return VALUES_1(Nil);
    else if (CONSP(slot_value)) {
	slot_value_cdr = M_CDR(slot_value);
	if (SYMBOLP(slot_value_cdr)) {
	    skip_list = CDR(Defined_evaluation_value_types);
	    key_value = slot_value_cdr;
	    key_hash_value = SXHASH_SYMBOL_1(slot_value_cdr) & 
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    gensymed_symbol = get_property_value_function(3,
		    get_symbol_properties_function(slot_value_cdr),
		    Qdefined_evaluation_type_reclaimer,Nil);
	    gensymed_symbol_1 = slot_value;
	    return VALUES_1(inline_funcall_1(gensymed_symbol,
		    gensymed_symbol_1));
	}
	else {
	    slot_cons = slot_value;
	    car_value = Nil;
	    next_cdr = Nil;
	  next_loop_3:
	    car_value = CAR(slot_cons);
	    next_cdr = CDR(slot_cons);
	    if ( !( !TRUEP(car_value) || SYMBOLP(car_value) || 
		    FIXNUMP(car_value) || EQ(car_value,No_value)))
		reclaim_slot_value(car_value);
	    if ( !(CONSP(next_cdr) &&  !EQ(next_cdr,No_value)))
		goto end_loop_3;
	    slot_cons = next_cdr;
	    goto next_loop_3;
	  end_loop_3:
	    if ( !(SYMBOLP(next_cdr) || FIXNUMP(next_cdr)))
		reclaim_slot_value(next_cdr);
	    if (slot_value &&  !((SI_Long)0L == inline_debugging_consing())) {
		slot_value_cons = slot_value;
	      next_loop_4:
		inline_note_reclaim_cons(slot_value_cons,Qab_slot_value);
		if (EQ(slot_value_cons,slot_cons))
		    goto end_2;
		else if ( !TRUEP(slot_value_cons))
		    goto end_2;
		else
		    slot_value_cons = CDR(slot_value_cons);
		goto next_loop_4;
	      end_loop_4:
	      end_2:;
	    }
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_3 = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_3) = slot_value;
		temp_3 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = slot_cons;
	    }
	    else {
		temp_3 = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = slot_value;
		temp_3 = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_3,svref_arg_2) = slot_cons;
	    }
	    M_CDR(slot_cons) = Nil;
	    return VALUES_1(Qnil);
	}
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L) {
	reclaim_managed_simple_float_array_of_length_1(slot_value);
	return VALUES_1(Nil);
    }
    else if (text_string_p(slot_value))
	return reclaim_text_string(slot_value);
    else {
	temp_1 = STRINGP(slot_value) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
		(SI_Long)0L),Managed_array_unique_marker)) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(slot_value,(SI_Long)1L));
	  next_loop_5:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_5;
	    reclaim_slot_value(FIXNUM_LE(ISVREF(slot_value,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(slot_value,
		    index_1 + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(slot_value,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L));
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_5;
	  end_loop_5:
	    reclaim_managed_array(slot_value);
	    return VALUES_1(Qnil);
	}
	else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
		(SI_Long)0L),Managed_float_array_unique_marker))
	    return reclaim_managed_float_array(slot_value);
	else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_byte_code_body_g2_struct))
	    return reclaim_byte_code_body_1(slot_value);
	else {
	    if (SIMPLE_VECTOR_P(slot_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(slot_value,(SI_Long)1L);
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
			IFIX(ISVREF(Dependent_frame_class_description,
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
		    temp_2 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		return delete_frame(slot_value);
	    else
		return VALUES_1(Qnil);
	}
    }
}

static Object Qrelation_instance_tree;  /* relation-instance-tree */

static Object Qconnection_item_table;  /* connection-item-table */

/* RECLAIM-SLOT-VALUE */
Object reclaim_slot_value(slot_value)
    Object slot_value;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, slot_value_cdr, cdr_1;
    Object car_1, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, temp_2, entry_hash, thing, gensymed_symbol_4;
    Object cdr_of_next_cdr, slot_cons, car_value, next_cdr, slot_value_cons;
    Object temp_3, svref_arg_2;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, key_hash_value, bottom_level, level;
    char temp;
    Object result;

    x_note_fn_call(81,76);
    if (FIXNUMP(slot_value) ||  !TRUEP(slot_value) || EQ(slot_value,
	    No_value) || SYMBOLP(slot_value));
    else if (SIMPLE_VECTOR_P(slot_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)5L && 
	    EQ(ISVREF(slot_value,(SI_Long)4L),Constant_queue_marker));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(slot_value);
    else if (text_string_p(slot_value))
	reclaim_text_string(slot_value);
    else if (STRINGP(slot_value));
    else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
	    (SI_Long)0L),Managed_array_unique_marker)) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(slot_value,(SI_Long)1L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	reclaim_slot_value(FIXNUM_LE(ISVREF(slot_value,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(slot_value,index_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(slot_value,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),index_1 & (SI_Long)1023L));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reclaim_managed_array(slot_value);
    }
    else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
	    (SI_Long)0L),Managed_float_array_unique_marker))
	reclaim_managed_float_array(slot_value);
    else if (SIMPLE_VECTOR_P(slot_value) && EQ(ISVREF(slot_value,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_byte_code_body_g2_struct))
	reclaim_byte_code_body_1(slot_value);
    else {
	if (SIMPLE_VECTOR_P(slot_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value,(SI_Long)1L);
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
		    IFIX(ISVREF(Dependent_frame_class_description,
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
	if (temp)
	    delete_frame(slot_value);
	else if (compiled_resource_p_function(slot_value))
	    reclaim_compiled_resource_function(slot_value);
	else if (INLINE_LONG_VECTOR_P(slot_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) == (SI_Long)1L)
	    reclaim_managed_simple_long_array_of_length_1(slot_value);
	else if (CONSP(slot_value) && EQ(CAR(slot_value),
		Qrelation_instance_tree))
	    reclaim_relation_instances(slot_value);
	else if (CONSP(slot_value) && EQ(CAR(slot_value),
		Qconnection_item_table));
	else if (CONSP(slot_value)) {
	    slot_value_cdr = M_CDR(slot_value);
	    cdr_1 = M_CDR(slot_value);
	    if (CONSP(cdr_1) && EQ(M_CDR(cdr_1),Qdefault_slot_constant)) {
		car_1 = M_CAR(slot_value);
		temp = TRUEP(slot_value_number_p(car_1));
		if (temp);
		else
		    temp = TRUEP(text_string_p(car_1));
		if (temp);
		else
		    temp = STRINGP(car_1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp);
	    else {
		if (SYMBOLP(slot_value_cdr)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = slot_value_cdr;
		    key_hash_value = SXHASH_SYMBOL_1(slot_value_cdr) & 
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_2:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_3:
		    if ( !TRUEP(marked))
			goto end_loop_2;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_3;
		  end_loop_2:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp =  !(EQ(slot_value_cdr,Qsequence) || 
			    EQ(slot_value_cdr,Qab_structure));
		    if (temp);
		    else {
			thing = M_CAR(slot_value);
			temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,
				(SI_Long)0L),Managed_array_unique_marker) :
				 TRUEP(Qnil);
		    }
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    gensymed_symbol = get_property_value_function(3,
			    get_symbol_properties_function(slot_value_cdr),
			    Qdefined_evaluation_type_reclaimer,Nil);
		    gensymed_symbol_4 = slot_value;
		    inline_funcall_1(gensymed_symbol,gensymed_symbol_4);
		}
		else {
		    cdr_of_next_cdr = slot_value_cdr;
		    slot_cons = slot_value;
		    car_value = Nil;
		    next_cdr = Nil;
		  next_loop_4:
		    car_value = M_CAR(slot_cons);
		    next_cdr = cdr_of_next_cdr;
		    if ( !(SYMBOLP(car_value) || FIXNUMP(car_value) || 
			    EQ(car_value,No_value)))
			reclaim_slot_value(car_value);
		    if (CONSP(next_cdr) &&  !EQ(next_cdr,No_value)) {
			cdr_of_next_cdr = M_CDR(next_cdr);
			temp = TRUEP(cdr_of_next_cdr);
		    }
		    else
			temp = TRUEP(Nil);
		    if ( !temp)
			goto end_loop_4;
		    slot_cons = next_cdr;
		    goto next_loop_4;
		  end_loop_4:
		    if ( !(SYMBOLP(next_cdr) || FIXNUMP(next_cdr)))
			reclaim_slot_value(next_cdr);
		    if (slot_value &&  !((SI_Long)0L == 
			    inline_debugging_consing())) {
			slot_value_cons = slot_value;
		      next_loop_5:
			inline_note_reclaim_cons(slot_value_cons,
				Qab_slot_value);
			if (EQ(slot_value_cons,slot_cons))
			    goto end_2;
			else if ( !TRUEP(slot_value_cons))
			    goto end_2;
			else
			    slot_value_cons = CDR(slot_value_cons);
			goto next_loop_5;
		      end_loop_5:
		      end_2:;
		    }
		    if (ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_slot_value_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_3) = slot_value;
			temp_3 = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = slot_cons;
		    }
		    else {
			temp_3 = Available_slot_value_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = slot_value;
			temp_3 = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = slot_cons;
		    }
		    M_CDR(slot_cons) = Nil;
		}
	    }
	}
	else;
    }
    return VALUES_1(Nil);
}

static Object Qlookup_structure;   /* lookup-structure */

static Object Qclass_description_slot;  /* class-description-slot */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qab_class;           /* class */

static Object list_constant_3;     /* # */

static Object Qdefined;            /* defined */

/* DEFINE-ROOT-CLASS */
Object define_root_class()
{
    Object temp, slot_descriptions, class_inheritance_path;
    XDeclare_area(1);

    x_note_fn_call(81,77);
    mutate_global_or_kb_specific_property_value(Qlookup_structure,
	    FIX((SI_Long)0L),Slot_name_assignment_gkbprop);
    mutate_global_or_kb_specific_property_value(Qclass_description_slot,
	    FIX((SI_Long)1L),Slot_name_assignment_gkbprop);
    if (PUSH_AREA(Dynamic_area,0)) {
	temp = make_slot_description(9,Qlookup_structure,Qroot,Qroot,Nil,
		Nil,FIX((SI_Long)0L),Nil,list_constant,T);
	slot_descriptions = LIST_2(temp,make_slot_description(9,
		Qclass_description_slot,Qroot,Qroot,Nil,Nil,
		FIX((SI_Long)1L),Nil,list_constant,T));
    }
    POP_AREA(0);
    if (PUSH_AREA(Dynamic_area,0))
	class_inheritance_path = copy_tree(list_constant_1);
    POP_AREA(0);
    temp = make_full_slot_descriptions_hash_table(slot_descriptions,
	    class_inheritance_path);
    temp = make_class_description(Qroot,class_inheritance_path,
	    FIX((SI_Long)2L),Nil,slot_descriptions,Nil,FIX((SI_Long)0L),
	    list_constant_2,Nil,temp,Qroot,Nil,Nil,
	    make_method_table_for_system_class(),T);
    mutate_global_or_kb_specific_property_value(Qroot,temp,
	    Class_description_gkbprop);
    mutate_global_property(Qlookup_structure,Qsystem,Qslot_category);
    mutate_global_property(Qclass_description_slot,Qsystem,Qslot_category);
    mutate_global_property(Qab_class,Qsystem,Qslot_category);
    mutate_global_or_kb_specific_property_value(Qroot,list_constant_3,
	    Class_definition_gkbprop);
    mutate_global_or_kb_specific_property_value(Qroot,Qdefined,
	    Definition_state_gkbprop);
    return VALUES_1(Qroot);
}

/* CLEAR-ALL-EVALUATOR-SLOT-INFO */
Object clear_all_evaluator_slot_info()
{
    Object scope_conses, ab_loopvar_, class_1, class_description, temp;
    Object slot_description, ab_loop_list_, evaluator_slot_info_qm;
    Declare_special(1);

    x_note_fn_call(81,78);
    if (Any_cached_evaluator_slot_info_p) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar_ = Qroot;
	class_1 = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  class_description = Nil;
	  ab_loopvar_ = collect_subclasses(ab_loopvar_);
	next_loop:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  temp = M_CAR(ab_loopvar_);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  class_1 = temp;
	  class_description = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  slot_description = Nil;
	  ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	  evaluator_slot_info_qm = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  slot_description = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  evaluator_slot_info_qm = ISVREF(slot_description,(SI_Long)10L);
	  if (evaluator_slot_info_qm)
	      SVREF(slot_description,FIX((SI_Long)10L)) = Nil;
	  goto next_loop_1;
	end_loop_1:;
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
	Any_cached_evaluator_slot_info_p = Nil;
	return VALUES_1(Any_cached_evaluator_slot_info_p);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Item_class_description, Qitem_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(System_item_class_description, Qsystem_item_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_frame_class_description, Qkb_frame_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Temporary_workspace_class_description, Qtemporary_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Invisible_entity_class_description, Qinvisible_entity_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Message_definition_class_description, Qmessage_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Format_frame_class_description, Qformat_frame_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_class_description, Qmenu_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Language_translation_class_description, Qlanguage_translation_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(User_menu_choice_class_description, Quser_menu_choice_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Generic_formula_class_description, Qgeneric_formula_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Logical_variable_class_description, Qlogical_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Float_variable_class_description, Qfloat_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Integer_variable_class_description, Qinteger_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Symbolic_variable_class_description, Qsymbolic_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_variable_class_description, Qtext_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Logical_parameter_class_description, Qlogical_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Quantitative_parameter_class_description, Qquantitative_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Integer_parameter_class_description, Qinteger_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Float_parameter_class_description, Qfloat_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Symbolic_parameter_class_description, Qsymbolic_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_parameter_class_description, Qtext_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Forward_chaining_link_class_description, Qforward_chaining_link_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(True_value_update_recipient_class_description, Qtrue_value_update_recipient_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Backward_chaining_link_class_description, Qbackward_chaining_link_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Function_definition_class_description, Qfunction_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Units_of_measure_declaration_class_description, Qunits_of_measure_declaration_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Tabular_function_of_1_arg_class_description, Qtabular_function_of_1_arg_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_cell_array_class_description, Qg2_cell_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_cell_array_cell_class_description, Qg2_cell_array_cell_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_query_cell_class_description, Qg2_query_cell_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_designation_cell_class_description, Qg2_designation_cell_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_expression_cell_class_description, Qg2_expression_cell_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_declaration_class_description, Qremote_procedure_declaration_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Dial_class_description, Qdial_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Meter_class_description, Qmeter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Digital_clock_class_description, Qdigital_clock_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_grid_class_description, Qgraph_grid_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_class_description, Qplot_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Model_definition_class_description, Qmodel_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Foreign_function_declaration_class_description, Qforeign_function_declaration_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(External_simulation_definition_class_description, Qexternal_simulation_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Authorized_user_class_description, Qauthorized_user_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Statement_class_description, Qstatement_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Edit_box_class_description, Qedit_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_invocation_class_description, Qprocedure_invocation_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Logbook_page_class_description, Qlogbook_page_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Page_class_description, Qpage_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Menu_workspace_class_description, Qmenu_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Category_instance_menu_workspace_class_description, Qcategory_instance_menu_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Inspect_command_class_description, Qinspect_command_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_cell_class_description, Qicon_cell_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Explanation_table_class_description, Qexplanation_table_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_box_class_description, Qtext_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_login_class_description, Qg2_login_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Name_box_class_description, Qname_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Category_menu_class_description, Qcategory_menu_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Scrap_class_description, Qscrap_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_region_class_description, Qtext_region_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Kfep_conversion_choice_menu_class_description, Qkfep_conversion_choice_menu_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Subordinate_text_box_class_description, Qsubordinate_text_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Dialog_button_class_description, Qdialog_button_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_definition_class_description, Qconnection_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_name_box_class_description, Qworkspace_name_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Class_definition_class_description, Qclass_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Non_kb_workspace_class_description, Qnon_kb_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_post_class_description, Qconnection_post_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Message_board_class_description, Qmessage_board_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Action_button_class_description, Qaction_button_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_class_description, Qchart_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Default_junction_class_description, Qdefault_junction_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Ruling_for_dial_class_description, Qruling_for_dial_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Pointer_for_dial_class_description, Qpointer_for_dial_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Ruling_for_meter_class_description, Qruling_for_meter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Marker_for_meter_class_description, Qmarker_for_meter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Readout_table_class_description, Qreadout_table_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_class_description, Qgraph_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Ok_class_description, Qok_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Generic_simulation_formula_class_description, Qgeneric_simulation_formula_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Object_class_description, Qobject_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Method_declaration_class_description, Qmethod_declaration_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Method_class_description, Qmethod_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_class_description, Qprocedure_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Variable_or_parameter_class_description, Qvariable_or_parameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Relation_class_description, Qrelation_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_subtable_class_description, Qsimulation_subtable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_workspace_class_description, Qkb_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Table_class_description, Qtable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Message_class_description, Qmessage_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Loose_end_class_description, Qloose_end_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Parameter_class_description, Qparameter_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Variable_class_description, Qvariable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Quantitative_variable_class_description, Qquantitative_variable_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Slider_minimum_value_label_class_description, Qslider_minimum_value_label_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Rule_class_description, Qrule_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Question_mark_box_class_description, Qquestion_mark_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Slider_readout_class_description, Qslider_readout_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Button_label_class_description, Qbutton_label_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Slider_needle_class_description, Qslider_needle_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Type_in_text_box_class_description, Qtype_in_text_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Button_class_description, Qbutton_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Generic_action_button_class_description, Qgeneric_action_button_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Type_in_box_class_description, Qtype_in_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Arrow_button_class_description, Qarrow_button_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_window_class_description, Qg2_window_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Connection_class_description, Qconnection_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Entity_class_description, Qentity_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Workspace_class_description, Qworkspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_workspace_class_description, Qicon_editor_workspace_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Object_definition_class_description, Qobject_definition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Icon_editor_table_info_frame_class_description, Qicon_editor_table_info_frame_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Bounding_box_class_description, Qbounding_box_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Tabular_function_class_description, Qtabular_function_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_list_class_description, Qg2_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Item_list_class_description, Qitem_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Value_list_class_description, Qvalue_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Integer_list_class_description, Qinteger_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Float_list_class_description, Qfloat_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Quantity_list_class_description, Qquantity_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Symbol_list_class_description, Qsymbol_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_list_class_description, Qtext_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Truth_value_list_class_description, Qtruth_value_list_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(G2_array_class_description, Qg2_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Item_array_class_description, Qitem_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Value_array_class_description, Qvalue_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Integer_array_class_description, Qinteger_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Float_array_class_description, Qfloat_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Quantity_array_class_description, Qquantity_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Symbol_array_class_description, Qsymbol_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Text_array_class_description, Qtext_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Truth_value_array_class_description, Qtruth_value_array_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Definition_class_description, Qdefinition_class_description);

DEFINE_VARIABLE_WITH_SYMBOL(Long_variable_class_description, Qlong_variable_class_description);

void frames2_INIT()
{
    Object gensymed_symbol, the_array, temp, temp_1, temp_2, temp_3, temp_4;
    Object temp_5;
    SI_Long i, ab_loop_bind_;
    Object AB_package, Qdef_root_class, list_constant_185, list_constant_184;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_value_reclaimer;
    Object Qreclaim_class_description_slot_value;
    Object Qreclaim_lookup_structure_value, Qtype_error_printer;
    Object string_constant_1, Qslot_value_long, Qslot_value_float;
    Object Qsimple_type_specification, list_constant_183;
    Object Qslot_value_long_p_function, list_constant_182;
    Object Qslot_value_float_p_function, list_constant_181, Qno_slot;
    Object Qgeneric_method_lambda_list, Qon_frame_saved;
    Object Qprepare_to_saving_frame, Qnote_ancestor_manually_enabled;
    Object Qnote_ancestor_not_activatable, Qget_workspace_representation_type;
    Object Qrestore_history_buffer, Qchange_size_per_bounding_rectangle;
    Object Qhandle_change_or_deletion_fanout, Qmanually_enable;
    Object Qmanually_disable, Qupdate_part_dependencies;
    Object Qgenerate_designation_of_cell, Qdesignation_cell_updated;
    Object Qquery_cell_updated, Qadd_items_to_edit_workspace;
    Object Qhandle_end_operation, Qstrip_text, Qreconsider_formatting;
    Object Qnote_may_refer_to_inactive_items_change;
    Object Qrecompile_expression_at_component_particulars;
    Object Qplace_reference_of_cell, Qresize, Qretract_frame_notes;
    Object Qassert_frame_notes, Qshift, Qdeactivate_and_propagate;
    Object Qactivate_if_possible_and_propagate, Qupdate_cell_based_display;
    Object Qreformat_as_appropriate, Qexecute_command;
    Object Qcompute_minimum_bottom_edge, Qcompute_minimum_right_edge;
    Object Qscroll_block, Qclick, Qupdate_display, Qclear_display;
    Object Qfix_frame_with_substitute_class, Qupdate_frame_status_and_notes;
    Object Qnote_runs_while_inactive_change, Qcopy_frame;
    Object Qput_box_translation_and_text_slot_value, Qdescribe_frame;
    Object Qactivate_subclass_of_entity, Qdeactivate_subclass_of_entity;
    Object Qexpression_cell_updated, Qdenote_cell_array_element;
    Object Qnote_name_change, Qdeinstall_system_table, Qinstall_system_table;
    Object Qdeactivate, Qactivate, Qdraw, Qinitialize_after_reading;
    Object Qanalyze_for_consistency, Qinitialize, Qcleanup, Qgenerate_spot;
    Object list_constant_180, Qframes2, list_constant_179;
    Object Qjunction_block_class, Qstub_length, Qcross_section_pattern;
    Object list_constant_178, list_constant_177, Qminimum_height_of_text_box;
    Object Qminimum_width_of_text_box, Qtext_cell_plist_for_text_box;
    Object Qdefault_text_box_format_name, list_constant_176, list_constant_166;
    Object list_constant_175, list_constant_174, Qinsert_duplicate_elements_qm;
    Object Qlist_type, list_constant_173, list_constant_172;
    Object Qg2_array_initial_values, Qg2_array_length, Qg2_array_element_type;
    Object list_constant_171, list_constant_170, list_constant_169;
    Object Qvariable_or_parameter_history_specification_qm;
    Object Qinitial_value_of_variable_or_parameter;
    Object Qdata_type_of_variable_or_parameter, list_constant_168;
    Object list_constant_167;
    Object Qhistory_specification_for_simulation_subtables_qm, Qframe_flags;
    Object Qbackground_collection_interval_qm, Qdata_server_map;
    Object Qvalidity_interval, Qicon_description, list_constant_165;
    Object list_constant_164, list_constant_163, list_constant_162;
    Object list_constant_161, list_constant_160, list_constant_159;
    Object list_constant_158, list_constant_157, list_constant_156;
    Object list_constant_155, list_constant_154, list_constant_153;
    Object list_constant_152, list_constant_151, list_constant_150;
    Object list_constant_149, list_constant_148, list_constant_147;
    Object list_constant_146, list_constant_145, list_constant_144;
    Object list_constant_143, list_constant_142, list_constant_141;
    Object list_constant_140, list_constant_139, list_constant_138;
    Object list_constant_137, list_constant_136, list_constant_135;
    Object list_constant_134, list_constant_133, list_constant_132;
    Object list_constant_131, list_constant_130, list_constant_129;
    Object list_constant_128, list_constant_127, list_constant_126;
    Object list_constant_125, list_constant_124, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_119, list_constant_118, list_constant_117;
    Object list_constant_116, list_constant_115, list_constant_114;
    Object list_constant_113, list_constant_112, list_constant_111;
    Object list_constant_110, list_constant_109, list_constant_108;
    Object list_constant_107, list_constant_106, Qsimulation_subtable;
    Object Qtime_increment_for_update_qm, Qtracing_and_breakpoints;
    Object Qtime_increment_for_update, list_constant_7, list_constant_105;
    Object Qtype_in_box, Qhave_edit_option_buttons_for_type_in_qm;
    Object Qblank_for_type_in_qm, Qformat_for_type_in_box, list_constant_104;
    Object list_constant_103, Qslider, list_constant_9, Qwhen_to_show_value;
    Object Qset_value_while_sliding_qm, Qmaximum_value_for_slider;
    Object Qminimum_value_for_slider, list_constant_8, Qmaximum_value;
    Object Qminimum_value, list_constant_102, list_constant_101, Qradio_button;
    Object Qvalue_for_radio_button, Qon_value, list_constant_100;
    Object list_constant_99, Qcheck_box, Qoff_value_for_check_box;
    Object Qon_value_for_check_box, Qoff_value, list_constant_98;
    Object list_constant_97, Qnon_action_button;
    Object Qassociated_variable_designation_qm, Qvalue_on_activation_qm;
    Object Qvariable_or_parameter, Qvalue_on_activation, list_constant_96;
    Object list_constant_75, Qaction_button, Qaction_button_priority;
    Object list_constant_95, Qtext_inserter, Qborderless_free_text, Qfree_text;
    Object list_constant_94, list_constant_93, Qdefault_text_box_colors;
    Object list_constant_92, list_constant_91, Qexternal_simulation_definition;
    Object Qclass_of_object_computed_by_this, list_constant_90;
    Object list_constant_89, Qmodel_definition;
    Object Qsimulation_control_specifications;
    Object Qsend_all_values_at_beginning_of_cycle_for_model_qm;
    Object Qsimulation_procedure_for_model, Qintegration_algorithm_for_model;
    Object Qdefault_simulation_time_increment_for_model;
    Object Qsend_all_values_at_beginning_of_cycle, Qsimulation_procedure;
    Object Qintegration_algorithm, Qdefault_simulation_time_increment;
    Object list_constant_88, Qforeign_function_declaration, Qtimeout_interval;
    Object list_constant_87, Qgeneric_simulation_formula, list_constant_86;
    Object list_constant_85, Qrule, list_constant_84;
    Object Qbackward_chaining_precedence, Qrule_priority, Qrule_categories;
    Object Qfocal_objects, Qfocal_classes, Qrule_scan_interval;
    Object Qdepth_first_backward_chaining_precedence, Qcategories;
    Object Qscan_interval, Qtimeout_for_rule_completion, list_constant_83;
    Object list_constant_82, Qframe_style_definition, Qdescription_of_frame;
    Object list_constant_81, list_constant_80, Qrelation, list_constant_72;
    Object Qrelation_is_permanent, Qclass_of_object, Qclass_of_subject;
    Object Qsecond_class, Qfirst_class, list_constant_79, list_constant_78;
    Object Qtabular_function_of_1_arg, Qtabular_function_interpolation_qm;
    Object Qkeep_tabular_function_sorted_qm, Qinterpolate, Qkeep_sorted;
    Object list_constant_77, list_constant_76, Quser_menu_choice;
    Object Quser_menu_choice_priority;
    Object Qcondition_for_using_user_menu_choice_qm;
    Object Qclass_for_user_menu_choice_qm, Qab_condition, Qapplicable_class;
    Object Qaction_priority, list_constant_74, list_constant_73;
    Object Qimage_definition, Qdepth_of_image, Qheight_of_image;
    Object Qwidth_of_image, Qsave_image_data_with_kb, Qfile_name_of_image_qm;
    Object Qstubs_for_class, Qattribute_displays_for_class;
    Object Qfile_name_of_image, list_constant_71, list_constant_70;
    Object Qfreeform_table, list_constant_69, Qcell_annotations, Qtable_size;
    Object Qdefault_evaluation_setting, Qdefault_cell_format, list_constant_68;
    Object Qannotations, Qchart_style, list_constant_67, list_constant_66;
    Object Qgraph, list_constant_61, Qbackground_colors, Qextra_grid_lines_qm;
    Object Qinterval_between_horizontal_grid_lines_qm, Qshow_grid_lines_qm;
    Object Qpercentage_extra_space_to_leave, Qscroll_continuously_qm;
    Object Qdesired_range_for_vertical_axis_qm;
    Object Qdesired_range_for_horizontal_axis_qm, list_constant_59;
    Object Qdesired_range_for_vertical_axis;
    Object Qdesired_range_for_horizontal_axis, list_constant_65;
    Object list_constant_64, Qdigital_clock, list_constant_60;
    Object Qformat_for_readout_table, list_constant_58, Qdisplay_format;
    Object list_constant_63, list_constant_62, Qreadout_table;
    Object Qdisplay_update_priority, Qdisplay_wait_interval;
    Object Qdisplay_update_interval;
    Object Qdisplay_evaluation_should_use_simulated_values_qm;
    Object Qshow_simulated_values, list_constant_57, list_constant_56, Qmeter;
    Object list_constant_53, Qincrement_per_meter_ruling;
    Object Qlow_value_for_meter_ruling, list_constant_52, list_constant_55;
    Object list_constant_54, Qdial, Qincrement_per_dial_ruling;
    Object Qlow_value_for_dial_ruling, list_constant_51, list_constant_50;
    Object Qmethod_declaration, Quninterrupted_procedure_execution_limit_qm;
    Object Qdefault_procedure_priority, Qclass_of_procedure_invocation;
    Object Quninterrupted_procedure_execution_limit, list_constant_10;
    Object Qprocedure_invocation, list_constant_49, list_constant_48;
    Object Qprocedure, list_constant_47, list_constant_46, Qkb_workspace;
    Object Qmodule_this_is_part_of_qm, Qtitle_bar_text, Qframe_style;
    Object Qworkspace_margin, Qworkspace_background_color_qm;
    Object Qworkspace_foreground_color_qm, Qkb_workspace_initial_height;
    Object Qkb_workspace_initial_width, Qmodule_assignment, Qbackground_color;
    Object Qforeground_color, Qinitial_height, Qinitial_width;
    Object list_constant_45, list_constant_44, Qmessage;
    Object Qdefault_message_properties_for_class, Qdefault_message_properties;
    Object list_constant_43, list_constant_42, Qconnection;
    Object Qjunction_block_class_for_class, Qstub_length_for_class;
    Object Qcross_section_pattern_for_class, Qjunction_block, list_constant_41;
    Object list_constant_40, Qg2_list, list_constant_39;
    Object Qallow_duplicate_elements_for_g2_list, Qlist_is_permanent;
    Object list_constant_38, list_constant_36, Qitem_list, list_constant_37;
    Object Qitem_array, Qelement_type, list_constant_35, list_constant_34;
    Object Qg2_array, list_constant_33, Qinitial_values, Qarray_length;
    Object Qarray_is_permanent, list_constant_17, Qquantitative_parameter;
    Object list_constant_32, list_constant_31, Qparameter;
    Object Qoptions_for_parameter, Qg2_to_g2_data_interface, list_constant_30;
    Object Qgsi_interface, Qinterval_to_poll_external_system;
    Object Qremote_process_initialization_string, Qgrouping_specification;
    Object Qpoll_external_system_for_data, Qexternal_system_has_a_scheduler;
    Object list_constant_29, Qnetwork_interface;
    Object Qdisable_interleaving_of_large_messages;
    Object Qinterface_initialization_timeout_period, Qinterface_timeout_period;
    Object Qinterface_warning_message_level, Qidentifying_attributes;
    Object list_constant_28, list_constant_27, Qgfi_input_interface;
    Object list_constant_26, Qignore_gfi_input_base_time_qm;
    Object Qignore_gfi_input_base_time, Qgfi_input_file_pathname;
    Object Qgfi_input_file_format, Qgfi_input_time_stamp_format;
    Object Qgfi_input_variables_update_mode, list_constant_25;
    Object list_constant_24, Qgfi_output_interface, list_constant_23;
    Object Qrenamed_gfi_output_file_pathname_qm, Qgfi_output_file_format;
    Object Qgfi_output_time_stamp_format, Qgfi_output_file_update_frequency;
    Object Qmaximum_number_of_output_lines, Qrenamed_gfi_output_file_pathname;
    Object Qgfi_output_file_pathname, list_constant_22, Qg2_to_g2_data_service;
    Object Qg2_to_g2_interface_name, list_constant_21, Qgsi_data_service;
    Object Qgsi_interface_name, list_constant_20, Qgfi_data_service;
    Object Qgfi_input_interface_object, list_constant_19;
    Object Qg2_meter_data_service, Qg2_meter_name, list_constant_18;
    Object Qgsi_message_service, Qdata_server_for_messages;
    Object Qquantitative_variable, Qsensor, list_constant_16, list_constant_15;
    Object Qdata_type, list_constant_14, list_constant_13;
    Object Qhistory_keeping_spec_for_simulation_subtables_qm;
    Object Qsimulation_details, Qhistory_keeping_spec_for_simulation_subtable;
    Object Qoptions_for_variable, Qdefault_update_interval, Qdata_server;
    Object Qsupply_simulation_subtable, list_constant_12, list_constant_11;
    Object Qinitial_value, Qhistory_keeping_spec_for_variable_or_parameter;
    Object Qobject, Qstubs, Qattribute_displays, list_constant_6;
    Object list_constant_5, Qclass_definition, Qinclude_in_menus_qm;
    Object Qinstantiate_qm, Qinclude_in_menus, Qinstantiate;
    Object Qreclaim_byte_vector, list_constant_4;
    Object Qinitialize_classes_visited_byte_vector, Kfuncall;

    x_note_fn_call(81,79);
    SET_PACKAGE("AB");
    if (Last_system_class_bit_number == UNBOUND)
	Last_system_class_bit_number = FIX((SI_Long)0L);
    if (Next_class_bit_number == UNBOUND)
	Next_class_bit_number = FIX((SI_Long)0L);
    AB_package = STATIC_PACKAGE("AB");
    Qclasses_visited_byte_vector = 
	    STATIC_SYMBOL("CLASSES-VISITED-BYTE-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclasses_visited_byte_vector,
	    Classes_visited_byte_vector);
    Qframes2 = STATIC_SYMBOL("FRAMES2",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_classes_visited_byte_vector = 
	    STATIC_SYMBOL("INITIALIZE-CLASSES-VISITED-BYTE-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_classes_visited_byte_vector,
	    STATIC_FUNCTION(initialize_classes_visited_byte_vector,NIL,
	    FALSE,0,0));
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_classes_visited_byte_vector);
    Qreclaim_byte_vector = STATIC_SYMBOL("RECLAIM-BYTE-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_byte_vector,
	    STATIC_FUNCTION(reclaim_byte_vector,NIL,FALSE,1,1));
    record_system_variable(Qclasses_visited_byte_vector,Qframes2,
	    list_constant_4,Qnil,Qnil,Qreclaim_byte_vector,Qt);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qnext_class_bit_number = STATIC_SYMBOL("NEXT-CLASS-BIT-NUMBER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnext_class_bit_number,Next_class_bit_number);
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    Qnoting_changes_to_kb_p = STATIC_SYMBOL("NOTING-CHANGES-TO-KB-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnoting_changes_to_kb_p,Noting_changes_to_kb_p);
    record_system_variable(Qnoting_changes_to_kb_p,Qframes2,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qcurrent_block_of_dependent_frame = 
	    STATIC_SYMBOL("CURRENT-BLOCK-OF-DEPENDENT-FRAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_block_of_dependent_frame,
	    Current_block_of_dependent_frame);
    record_system_variable(Qcurrent_block_of_dependent_frame,Qframes2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qfoundation_class = STATIC_SYMBOL("FOUNDATION-CLASS",AB_package);
    if (System_class_method_tables_processed_qm == UNBOUND)
	System_class_method_tables_processed_qm = Nil;
    if (Decache_attribute_description_lists_of_interned_lists_function == 
	    UNBOUND)
	Decache_attribute_description_lists_of_interned_lists_function = Nil;
    if (Class_change_timestamp == UNBOUND)
	Class_change_timestamp = FIX((SI_Long)0L);
    Qclass_change_timestamp = STATIC_SYMBOL("CLASS-CHANGE-TIMESTAMP",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_change_timestamp,Class_change_timestamp);
    Qinferior_classes = STATIC_SYMBOL("INFERIOR-CLASSES",AB_package);
    Qport = STATIC_SYMBOL("PORT",AB_package);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Qobsolete = STATIC_SYMBOL("OBSOLETE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qvector_slot = STATIC_SYMBOL("VECTOR-SLOT",AB_package);
    Qlookup_slot = STATIC_SYMBOL("LOOKUP-SLOT",AB_package);
    Qsystem = STATIC_SYMBOL("SYSTEM",AB_package);
    Qlist_of_user_overridable_system_slots = 
	    STATIC_SYMBOL("LIST-OF-USER-OVERRIDABLE-SYSTEM-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_user_overridable_system_slots,
	    List_of_user_overridable_system_slots);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qinstantiate = STATIC_SYMBOL("INSTANTIATE",AB_package);
    Qinclude_in_menus = STATIC_SYMBOL("INCLUDE-IN-MENUS",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qinstantiate,Qinclude_in_menus);
    Qinstantiate_qm = STATIC_SYMBOL("INSTANTIATE\?",AB_package);
    Qinclude_in_menus_qm = STATIC_SYMBOL("INCLUDE-IN-MENUS\?",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qinstantiate_qm,
	    Qinclude_in_menus_qm);
    list_constant_7 = STATIC_CONS(Qnil,Qnil);
    list_constant_132 = STATIC_LIST_STAR((SI_Long)5L,Qclass_definition,
	    list_constant_5,Qnil,list_constant_6,list_constant_7);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qattribute_displays = STATIC_SYMBOL("ATTRIBUTE-DISPLAYS",AB_package);
    Qstubs = STATIC_SYMBOL("STUBS",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qattribute_displays,Qstubs);
    Qattribute_displays_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-FOR-CLASS",AB_package);
    Qstubs_for_class = STATIC_SYMBOL("STUBS-FOR-CLASS",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)3L,
	    Qattribute_displays_for_class,Qstubs_for_class,Qicon_description);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)4L,list_constant_8,Qnil,
	    list_constant_9,list_constant_7);
    list_constant_133 = STATIC_CONS(Qobject,list_constant_10);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qhistory_keeping_spec_for_variable_or_parameter = 
	    STATIC_SYMBOL("HISTORY-KEEPING-SPEC-FOR-VARIABLE-OR-PARAMETER",
	    AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qtracing_and_breakpoints,
	    Qhistory_keeping_spec_for_variable_or_parameter,Qinitial_value);
    Qvariable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qtracing_and_breakpoints,
	    Qvariable_or_parameter_history_specification_qm,
	    Qinitial_value_of_variable_or_parameter);
    list_constant_134 = STATIC_LIST_STAR((SI_Long)5L,
	    Qvariable_or_parameter,list_constant_11,Qnil,list_constant_12,
	    list_constant_7);
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    Qsupply_simulation_subtable = 
	    STATIC_SYMBOL("SUPPLY-SIMULATION-SUBTABLE",AB_package);
    Qdata_server = STATIC_SYMBOL("DATA-SERVER",AB_package);
    Qdefault_update_interval = STATIC_SYMBOL("DEFAULT-UPDATE-INTERVAL",
	    AB_package);
    Qoptions_for_variable = STATIC_SYMBOL("OPTIONS-FOR-VARIABLE",AB_package);
    Qhistory_keeping_spec_for_simulation_subtable = 
	    STATIC_SYMBOL("HISTORY-KEEPING-SPEC-FOR-SIMULATION-SUBTABLE",
	    AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)6L,Qvalidity_interval,
	    Qsupply_simulation_subtable,Qdata_server,
	    Qdefault_update_interval,Qoptions_for_variable,
	    Qhistory_keeping_spec_for_simulation_subtable);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    Qbackground_collection_interval_qm = 
	    STATIC_SYMBOL("BACKGROUND-COLLECTION-INTERVAL\?",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qhistory_keeping_spec_for_simulation_subtables_qm = 
	    STATIC_SYMBOL("HISTORY-KEEPING-SPEC-FOR-SIMULATION-SUBTABLES\?",
	    AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)6L,Qvalidity_interval,
	    Qsimulation_details,Qdata_server_map,
	    Qbackground_collection_interval_qm,Qframe_flags,
	    Qhistory_keeping_spec_for_simulation_subtables_qm);
    list_constant_135 = STATIC_LIST_STAR((SI_Long)5L,Qvariable,
	    list_constant_13,Qnil,list_constant_14,list_constant_7);
    Qsensor = STATIC_SYMBOL("SENSOR",AB_package);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    list_constant_15 = STATIC_CONS(Qdata_type,Qnil);
    Qdata_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    list_constant_16 = STATIC_CONS(Qdata_type_of_variable_or_parameter,Qnil);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)4L,list_constant_15,Qnil,
	    list_constant_16,list_constant_7);
    list_constant_136 = STATIC_CONS(Qsensor,list_constant_17);
    Qquantitative_variable = STATIC_SYMBOL("QUANTITATIVE-VARIABLE",AB_package);
    list_constant_137 = STATIC_CONS(Qquantitative_variable,list_constant_17);
    Qgsi_message_service = STATIC_SYMBOL("GSI-MESSAGE-SERVICE",AB_package);
    Qgsi_interface_name = STATIC_SYMBOL("GSI-INTERFACE-NAME",AB_package);
    Qdata_server_for_messages = STATIC_SYMBOL("DATA-SERVER-FOR-MESSAGES",
	    AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qgsi_interface_name,
	    Qdata_server_for_messages);
    list_constant_138 = STATIC_LIST_STAR((SI_Long)5L,Qgsi_message_service,
	    list_constant_18,Qnil,list_constant_18,list_constant_7);
    Qg2_meter_data_service = STATIC_SYMBOL("G2-METER-DATA-SERVICE",AB_package);
    Qg2_meter_name = STATIC_SYMBOL("G2-METER-NAME",AB_package);
    list_constant_19 = STATIC_CONS(Qg2_meter_name,Qnil);
    list_constant_139 = STATIC_LIST_STAR((SI_Long)5L,
	    Qg2_meter_data_service,list_constant_19,Qnil,list_constant_19,
	    list_constant_7);
    Qgfi_data_service = STATIC_SYMBOL("GFI-DATA-SERVICE",AB_package);
    Qgfi_input_interface_object = 
	    STATIC_SYMBOL("GFI-INPUT-INTERFACE-OBJECT",AB_package);
    list_constant_20 = STATIC_CONS(Qgfi_input_interface_object,Qnil);
    list_constant_140 = STATIC_LIST_STAR((SI_Long)5L,Qgfi_data_service,
	    list_constant_20,Qnil,list_constant_20,list_constant_7);
    Qgsi_data_service = STATIC_SYMBOL("GSI-DATA-SERVICE",AB_package);
    list_constant_21 = STATIC_CONS(Qgsi_interface_name,Qnil);
    list_constant_141 = STATIC_LIST_STAR((SI_Long)5L,Qgsi_data_service,
	    list_constant_21,Qnil,list_constant_21,list_constant_7);
    Qg2_to_g2_data_service = STATIC_SYMBOL("G2-TO-G2-DATA-SERVICE",AB_package);
    Qg2_to_g2_interface_name = STATIC_SYMBOL("G2-TO-G2-INTERFACE-NAME",
	    AB_package);
    list_constant_22 = STATIC_CONS(Qg2_to_g2_interface_name,Qnil);
    list_constant_142 = STATIC_LIST_STAR((SI_Long)5L,
	    Qg2_to_g2_data_service,list_constant_22,Qnil,list_constant_22,
	    list_constant_7);
    Qgfi_output_interface = STATIC_SYMBOL("GFI-OUTPUT-INTERFACE",AB_package);
    Qmaximum_number_of_output_lines = 
	    STATIC_SYMBOL("MAXIMUM-NUMBER-OF-OUTPUT-LINES",AB_package);
    Qgfi_output_file_update_frequency = 
	    STATIC_SYMBOL("GFI-OUTPUT-FILE-UPDATE-FREQUENCY",AB_package);
    Qgfi_output_time_stamp_format = 
	    STATIC_SYMBOL("GFI-OUTPUT-TIME-STAMP-FORMAT",AB_package);
    Qgfi_output_file_format = STATIC_SYMBOL("GFI-OUTPUT-FILE-FORMAT",
	    AB_package);
    Qrenamed_gfi_output_file_pathname = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME",AB_package);
    Qgfi_output_file_pathname = STATIC_SYMBOL("GFI-OUTPUT-FILE-PATHNAME",
	    AB_package);
    list_constant_23 = STATIC_CONS(Qgfi_output_file_pathname,Qnil);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)6L,
	    Qmaximum_number_of_output_lines,
	    Qgfi_output_file_update_frequency,
	    Qgfi_output_time_stamp_format,Qgfi_output_file_format,
	    Qrenamed_gfi_output_file_pathname,list_constant_23);
    Qrenamed_gfi_output_file_pathname_qm = 
	    STATIC_SYMBOL("RENAMED-GFI-OUTPUT-FILE-PATHNAME\?",AB_package);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)6L,
	    Qmaximum_number_of_output_lines,
	    Qgfi_output_file_update_frequency,
	    Qgfi_output_time_stamp_format,Qgfi_output_file_format,
	    Qrenamed_gfi_output_file_pathname_qm,list_constant_23);
    list_constant_143 = STATIC_LIST_STAR((SI_Long)5L,Qgfi_output_interface,
	    list_constant_24,Qnil,list_constant_25,list_constant_7);
    Qgfi_input_interface = STATIC_SYMBOL("GFI-INPUT-INTERFACE",AB_package);
    Qignore_gfi_input_base_time = 
	    STATIC_SYMBOL("IGNORE-GFI-INPUT-BASE-TIME",AB_package);
    Qgfi_input_variables_update_mode = 
	    STATIC_SYMBOL("GFI-INPUT-VARIABLES-UPDATE-MODE",AB_package);
    Qgfi_input_time_stamp_format = 
	    STATIC_SYMBOL("GFI-INPUT-TIME-STAMP-FORMAT",AB_package);
    Qgfi_input_file_format = STATIC_SYMBOL("GFI-INPUT-FILE-FORMAT",AB_package);
    Qgfi_input_file_pathname = STATIC_SYMBOL("GFI-INPUT-FILE-PATHNAME",
	    AB_package);
    list_constant_26 = STATIC_LIST((SI_Long)4L,
	    Qgfi_input_variables_update_mode,Qgfi_input_time_stamp_format,
	    Qgfi_input_file_format,Qgfi_input_file_pathname);
    list_constant_27 = STATIC_CONS(Qignore_gfi_input_base_time,
	    list_constant_26);
    Qignore_gfi_input_base_time_qm = 
	    STATIC_SYMBOL("IGNORE-GFI-INPUT-BASE-TIME\?",AB_package);
    list_constant_28 = STATIC_CONS(Qignore_gfi_input_base_time_qm,
	    list_constant_26);
    list_constant_144 = STATIC_LIST_STAR((SI_Long)5L,Qgfi_input_interface,
	    list_constant_27,Qnil,list_constant_28,list_constant_7);
    Qnetwork_interface = STATIC_SYMBOL("NETWORK-INTERFACE",AB_package);
    Qidentifying_attributes = STATIC_SYMBOL("IDENTIFYING-ATTRIBUTES",
	    AB_package);
    Qinterface_warning_message_level = 
	    STATIC_SYMBOL("INTERFACE-WARNING-MESSAGE-LEVEL",AB_package);
    Qinterface_timeout_period = STATIC_SYMBOL("INTERFACE-TIMEOUT-PERIOD",
	    AB_package);
    Qinterface_initialization_timeout_period = 
	    STATIC_SYMBOL("INTERFACE-INITIALIZATION-TIMEOUT-PERIOD",
	    AB_package);
    Qdisable_interleaving_of_large_messages = 
	    STATIC_SYMBOL("DISABLE-INTERLEAVING-OF-LARGE-MESSAGES",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)5L,Qidentifying_attributes,
	    Qinterface_warning_message_level,Qinterface_timeout_period,
	    Qinterface_initialization_timeout_period,
	    Qdisable_interleaving_of_large_messages);
    list_constant_145 = STATIC_LIST_STAR((SI_Long)5L,Qnetwork_interface,
	    list_constant_29,Qnil,list_constant_29,list_constant_7);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qexternal_system_has_a_scheduler = 
	    STATIC_SYMBOL("EXTERNAL-SYSTEM-HAS-A-SCHEDULER",AB_package);
    Qpoll_external_system_for_data = 
	    STATIC_SYMBOL("POLL-EXTERNAL-SYSTEM-FOR-DATA",AB_package);
    Qgrouping_specification = STATIC_SYMBOL("GROUPING-SPECIFICATION",
	    AB_package);
    Qremote_process_initialization_string = 
	    STATIC_SYMBOL("REMOTE-PROCESS-INITIALIZATION-STRING",AB_package);
    Qinterval_to_poll_external_system = 
	    STATIC_SYMBOL("INTERVAL-TO-POLL-EXTERNAL-SYSTEM",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)5L,
	    Qexternal_system_has_a_scheduler,
	    Qpoll_external_system_for_data,Qgrouping_specification,
	    Qremote_process_initialization_string,
	    Qinterval_to_poll_external_system);
    list_constant_146 = STATIC_LIST_STAR((SI_Long)5L,Qgsi_interface,
	    list_constant_30,Qnil,list_constant_30,list_constant_7);
    Qg2_to_g2_data_interface = STATIC_SYMBOL("G2-TO-G2-DATA-INTERFACE",
	    AB_package);
    list_constant_147 = STATIC_LIST_STAR((SI_Long)5L,
	    Qg2_to_g2_data_interface,Qnil,Qnil,Qnil,list_constant_7);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qoptions_for_parameter = STATIC_SYMBOL("OPTIONS-FOR-PARAMETER",AB_package);
    list_constant_31 = STATIC_CONS(Qoptions_for_parameter,Qnil);
    list_constant_32 = STATIC_CONS(Qframe_flags,Qnil);
    list_constant_148 = STATIC_LIST_STAR((SI_Long)5L,Qparameter,
	    list_constant_31,Qnil,list_constant_32,list_constant_7);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    list_constant_149 = STATIC_CONS(Qquantitative_parameter,list_constant_17);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qarray_length = STATIC_SYMBOL("ARRAY-LENGTH",AB_package);
    Qinitial_values = STATIC_SYMBOL("INITIAL-VALUES",AB_package);
    Qarray_is_permanent = STATIC_SYMBOL("ARRAY-IS-PERMANENT",AB_package);
    list_constant_33 = STATIC_CONS(Qarray_is_permanent,Qnil);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)3L,Qarray_length,
	    Qinitial_values,list_constant_33);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)3L,Qg2_array_length,
	    Qg2_array_initial_values,list_constant_33);
    list_constant_150 = STATIC_LIST_STAR((SI_Long)5L,Qg2_array,
	    list_constant_34,Qnil,list_constant_35,list_constant_7);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    list_constant_36 = STATIC_CONS(Qelement_type,Qnil);
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    list_constant_37 = STATIC_CONS(Qg2_array_element_type,Qnil);
    list_constant_151 = STATIC_LIST_STAR((SI_Long)5L,Qitem_array,
	    list_constant_36,Qnil,list_constant_37,list_constant_7);
    Qitem_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    list_constant_38 = STATIC_CONS(Qlist_type,Qnil);
    list_constant_152 = STATIC_LIST_STAR((SI_Long)5L,Qitem_list,
	    list_constant_36,Qnil,list_constant_38,list_constant_7);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qallow_duplicate_elements_for_g2_list = 
	    STATIC_SYMBOL("ALLOW-DUPLICATE-ELEMENTS-FOR-G2-LIST",AB_package);
    Qlist_is_permanent = STATIC_SYMBOL("LIST-IS-PERMANENT",AB_package);
    list_constant_39 = STATIC_CONS(Qlist_is_permanent,Qnil);
    list_constant_40 = STATIC_CONS(Qallow_duplicate_elements_for_g2_list,
	    list_constant_39);
    Qinsert_duplicate_elements_qm = 
	    STATIC_SYMBOL("INSERT-DUPLICATE-ELEMENTS\?",AB_package);
    list_constant_41 = STATIC_CONS(Qinsert_duplicate_elements_qm,
	    list_constant_39);
    list_constant_153 = STATIC_LIST_STAR((SI_Long)5L,Qg2_list,
	    list_constant_40,Qnil,list_constant_41,list_constant_7);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qjunction_block = STATIC_SYMBOL("JUNCTION-BLOCK",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qcross_section_pattern,
	    Qstub_length,Qjunction_block);
    Qcross_section_pattern_for_class = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CLASS",AB_package);
    Qstub_length_for_class = STATIC_SYMBOL("STUB-LENGTH-FOR-CLASS",AB_package);
    Qjunction_block_class = STATIC_SYMBOL("JUNCTION-BLOCK-CLASS",AB_package);
    Qjunction_block_class_for_class = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CLASS",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)6L,Qcross_section_pattern,
	    Qcross_section_pattern_for_class,Qstub_length,
	    Qstub_length_for_class,Qjunction_block_class,
	    Qjunction_block_class_for_class);
    list_constant_154 = STATIC_LIST_STAR((SI_Long)5L,Qconnection,
	    list_constant_42,Qnil,list_constant_43,list_constant_7);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    list_constant_44 = STATIC_CONS(Qdefault_message_properties,Qnil);
    Qdefault_message_properties_for_class = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES-FOR-CLASS",AB_package);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qtext_cell_plist_for_text_box = 
	    STATIC_SYMBOL("TEXT-CELL-PLIST-FOR-TEXT-BOX",AB_package);
    Qminimum_width_of_text_box = STATIC_SYMBOL("MINIMUM-WIDTH-OF-TEXT-BOX",
	    AB_package);
    Qminimum_height_of_text_box = 
	    STATIC_SYMBOL("MINIMUM-HEIGHT-OF-TEXT-BOX",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)5L,
	    Qdefault_message_properties_for_class,
	    Qdefault_text_box_format_name,Qtext_cell_plist_for_text_box,
	    Qminimum_width_of_text_box,Qminimum_height_of_text_box);
    list_constant_155 = STATIC_LIST_STAR((SI_Long)5L,Qmessage,
	    list_constant_44,Qnil,list_constant_45,list_constant_7);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qinitial_width = STATIC_SYMBOL("INITIAL-WIDTH",AB_package);
    Qinitial_height = STATIC_SYMBOL("INITIAL-HEIGHT",AB_package);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    Qframe_style = STATIC_SYMBOL("FRAME-STYLE",AB_package);
    Qtitle_bar_text = STATIC_SYMBOL("TITLE-BAR-TEXT",AB_package);
    Qmodule_assignment = STATIC_SYMBOL("MODULE-ASSIGNMENT",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)8L,Qinitial_width,
	    Qinitial_height,Qforeground_color,Qbackground_color,
	    Qworkspace_margin,Qframe_style,Qtitle_bar_text,Qmodule_assignment);
    Qkb_workspace_initial_width = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH",AB_package);
    Qkb_workspace_initial_height = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT",AB_package);
    Qworkspace_foreground_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-FOREGROUND-COLOR\?",AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)8L,Qkb_workspace_initial_width,
	    Qkb_workspace_initial_height,Qworkspace_foreground_color_qm,
	    Qworkspace_background_color_qm,Qworkspace_margin,Qframe_style,
	    Qtitle_bar_text,Qmodule_this_is_part_of_qm);
    list_constant_156 = STATIC_LIST_STAR((SI_Long)5L,Qkb_workspace,
	    list_constant_46,Qnil,list_constant_47,list_constant_7);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qclass_of_procedure_invocation = 
	    STATIC_SYMBOL("CLASS-OF-PROCEDURE-INVOCATION",AB_package);
    Qdefault_procedure_priority = 
	    STATIC_SYMBOL("DEFAULT-PROCEDURE-PRIORITY",AB_package);
    Quninterrupted_procedure_execution_limit = 
	    STATIC_SYMBOL("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT",
	    AB_package);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtracing_and_breakpoints,Qclass_of_procedure_invocation,
	    Qdefault_procedure_priority,
	    Quninterrupted_procedure_execution_limit,list_constant_8);
    Quninterrupted_procedure_execution_limit_qm = 
	    STATIC_SYMBOL("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT\?",
	    AB_package);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtracing_and_breakpoints,Qclass_of_procedure_invocation,
	    Qdefault_procedure_priority,
	    Quninterrupted_procedure_execution_limit_qm,list_constant_9);
    list_constant_157 = STATIC_LIST_STAR((SI_Long)5L,Qprocedure,
	    list_constant_48,Qnil,list_constant_49,list_constant_7);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    list_constant_158 = STATIC_CONS(Qprocedure_invocation,list_constant_10);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)4L,Qtracing_and_breakpoints,
	    Qclass_of_procedure_invocation,Qdefault_procedure_priority,
	    Quninterrupted_procedure_execution_limit);
    list_constant_51 = STATIC_LIST((SI_Long)4L,Qtracing_and_breakpoints,
	    Qclass_of_procedure_invocation,Qdefault_procedure_priority,
	    Quninterrupted_procedure_execution_limit_qm);
    list_constant_159 = STATIC_LIST((SI_Long)5L,Qmethod_declaration,Qnil,
	    list_constant_50,Qnil,list_constant_51);
    Qdial = STATIC_SYMBOL("DIAL",AB_package);
    Qlow_value_for_dial_ruling = STATIC_SYMBOL("LOW-VALUE-FOR-DIAL-RULING",
	    AB_package);
    Qincrement_per_dial_ruling = STATIC_SYMBOL("INCREMENT-PER-DIAL-RULING",
	    AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qshow_simulated_values = STATIC_SYMBOL("SHOW-SIMULATED-VALUES",AB_package);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)5L,
	    Qdisplay_update_interval,Qdisplay_wait_interval,
	    Qdisplay_update_priority,Qshow_simulated_values,list_constant_8);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)4L,
	    Qtracing_and_breakpoints,Qlow_value_for_dial_ruling,
	    Qincrement_per_dial_ruling,list_constant_52);
    Qdisplay_evaluation_should_use_simulated_values_qm = 
	    STATIC_SYMBOL("DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES\?",
	    AB_package);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)5L,
	    Qdisplay_update_interval,Qdisplay_wait_interval,
	    Qdisplay_update_priority,
	    Qdisplay_evaluation_should_use_simulated_values_qm,
	    list_constant_9);
    list_constant_55 = STATIC_LIST_STAR((SI_Long)4L,
	    Qtracing_and_breakpoints,Qlow_value_for_dial_ruling,
	    Qincrement_per_dial_ruling,list_constant_53);
    list_constant_160 = STATIC_LIST_STAR((SI_Long)5L,Qdial,
	    list_constant_54,Qnil,list_constant_55,list_constant_7);
    Qmeter = STATIC_SYMBOL("METER",AB_package);
    Qlow_value_for_meter_ruling = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-METER-RULING",AB_package);
    Qincrement_per_meter_ruling = 
	    STATIC_SYMBOL("INCREMENT-PER-METER-RULING",AB_package);
    list_constant_56 = STATIC_LIST_STAR((SI_Long)4L,
	    Qtracing_and_breakpoints,Qlow_value_for_meter_ruling,
	    Qincrement_per_meter_ruling,list_constant_52);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)4L,
	    Qtracing_and_breakpoints,Qlow_value_for_meter_ruling,
	    Qincrement_per_meter_ruling,list_constant_53);
    list_constant_161 = STATIC_LIST_STAR((SI_Long)5L,Qmeter,
	    list_constant_56,Qnil,list_constant_57,list_constant_7);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    Qdisplay_format = STATIC_SYMBOL("DISPLAY-FORMAT",AB_package);
    list_constant_58 = STATIC_CONS(Qshow_simulated_values,Qnil);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)4L,
	    Qdisplay_update_interval,Qdisplay_wait_interval,
	    Qdisplay_update_priority,list_constant_58);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtracing_and_breakpoints,Qdisplay_format,list_constant_59);
    Qformat_for_readout_table = STATIC_SYMBOL("FORMAT-FOR-READOUT-TABLE",
	    AB_package);
    list_constant_60 = 
	    STATIC_CONS(Qdisplay_evaluation_should_use_simulated_values_qm,
	    Qnil);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)4L,
	    Qdisplay_update_interval,Qdisplay_wait_interval,
	    Qdisplay_update_priority,list_constant_60);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtracing_and_breakpoints,Qformat_for_readout_table,
	    list_constant_61);
    list_constant_162 = STATIC_LIST_STAR((SI_Long)5L,Qreadout_table,
	    list_constant_62,Qnil,list_constant_63,list_constant_7);
    Qdigital_clock = STATIC_SYMBOL("DIGITAL-CLOCK",AB_package);
    list_constant_64 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtracing_and_breakpoints,Qdisplay_format,list_constant_58);
    list_constant_65 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtracing_and_breakpoints,Qformat_for_readout_table,
	    list_constant_60);
    list_constant_108 = STATIC_LIST((SI_Long)5L,Qdigital_clock,Qnil,
	    list_constant_64,Qnil,list_constant_65);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qdesired_range_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-HORIZONTAL-AXIS",AB_package);
    Qdesired_range_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-VERTICAL-AXIS",AB_package);
    Qscroll_continuously_qm = STATIC_SYMBOL("SCROLL-CONTINUOUSLY\?",
	    AB_package);
    Qpercentage_extra_space_to_leave = 
	    STATIC_SYMBOL("PERCENTAGE-EXTRA-SPACE-TO-LEAVE",AB_package);
    Qshow_grid_lines_qm = STATIC_SYMBOL("SHOW-GRID-LINES\?",AB_package);
    Qinterval_between_horizontal_grid_lines_qm = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES\?",
	    AB_package);
    Qextra_grid_lines_qm = STATIC_SYMBOL("EXTRA-GRID-LINES\?",AB_package);
    Qbackground_colors = STATIC_SYMBOL("BACKGROUND-COLORS",AB_package);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)9L,
	    Qdesired_range_for_horizontal_axis,
	    Qdesired_range_for_vertical_axis,Qscroll_continuously_qm,
	    Qpercentage_extra_space_to_leave,Qshow_grid_lines_qm,
	    Qinterval_between_horizontal_grid_lines_qm,
	    Qextra_grid_lines_qm,Qbackground_colors,list_constant_59);
    Qdesired_range_for_horizontal_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-HORIZONTAL-AXIS\?",AB_package);
    Qdesired_range_for_vertical_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-VERTICAL-AXIS\?",AB_package);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)9L,
	    Qdesired_range_for_horizontal_axis_qm,
	    Qdesired_range_for_vertical_axis_qm,Qscroll_continuously_qm,
	    Qpercentage_extra_space_to_leave,Qshow_grid_lines_qm,
	    Qinterval_between_horizontal_grid_lines_qm,
	    Qextra_grid_lines_qm,Qbackground_colors,list_constant_61);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)5L,Qgraph,
	    list_constant_66,Qnil,list_constant_67,list_constant_7);
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qchart_style = STATIC_SYMBOL("CHART-STYLE",AB_package);
    Qdata_series = STATIC_SYMBOL("DATA-SERIES",AB_package);
    Qannotations = STATIC_SYMBOL("ANNOTATIONS",AB_package);
    list_constant_68 = STATIC_LIST((SI_Long)3L,Qchart_style,Qdata_series,
	    Qannotations);
    list_constant_110 = STATIC_LIST_STAR((SI_Long)5L,Qchart,
	    list_constant_68,Qnil,list_constant_68,list_constant_7);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qtable_size = STATIC_SYMBOL("TABLE-SIZE",AB_package);
    Qdefault_cell_format = STATIC_SYMBOL("DEFAULT-CELL-FORMAT",AB_package);
    Qdefault_evaluation_setting = 
	    STATIC_SYMBOL("DEFAULT-EVALUATION-SETTING",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qdefault_cell_format,
	    Qdefault_evaluation_setting);
    list_constant_70 = STATIC_CONS(Qtable_size,list_constant_69);
    Qcell_annotations = STATIC_SYMBOL("CELL-ANNOTATIONS",AB_package);
    list_constant_71 = STATIC_CONS(Qcell_annotations,list_constant_69);
    list_constant_111 = STATIC_LIST_STAR((SI_Long)5L,Qfreeform_table,
	    list_constant_70,Qnil,list_constant_71,list_constant_7);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qfile_name_of_image = STATIC_SYMBOL("FILE-NAME-OF-IMAGE",AB_package);
    Qsave_image_data_with_kb = STATIC_SYMBOL("SAVE-IMAGE-DATA-WITH-KB",
	    AB_package);
    Qwidth_of_image = STATIC_SYMBOL("WIDTH-OF-IMAGE",AB_package);
    Qheight_of_image = STATIC_SYMBOL("HEIGHT-OF-IMAGE",AB_package);
    Qdepth_of_image = STATIC_SYMBOL("DEPTH-OF-IMAGE",AB_package);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)6L,Qfile_name_of_image,
	    Qsave_image_data_with_kb,Qwidth_of_image,Qheight_of_image,
	    Qdepth_of_image,list_constant_8);
    Qfile_name_of_image_qm = STATIC_SYMBOL("FILE-NAME-OF-IMAGE\?",AB_package);
    list_constant_72 = STATIC_LIST((SI_Long)2L,
	    Qattribute_displays_for_class,Qstubs_for_class);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)6L,Qfile_name_of_image_qm,
	    Qsave_image_data_with_kb,Qwidth_of_image,Qheight_of_image,
	    Qdepth_of_image,list_constant_72);
    list_constant_112 = STATIC_LIST_STAR((SI_Long)5L,Qimage_definition,
	    list_constant_73,Qnil,list_constant_74,list_constant_7);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    Qapplicable_class = STATIC_SYMBOL("APPLICABLE-CLASS",AB_package);
    Qab_condition = STATIC_SYMBOL("CONDITION",AB_package);
    Qaction_priority = STATIC_SYMBOL("ACTION-PRIORITY",AB_package);
    list_constant_75 = STATIC_CONS(Qaction_priority,list_constant_8);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)3L,Qapplicable_class,
	    Qab_condition,list_constant_75);
    Qclass_for_user_menu_choice_qm = 
	    STATIC_SYMBOL("CLASS-FOR-USER-MENU-CHOICE\?",AB_package);
    Qcondition_for_using_user_menu_choice_qm = 
	    STATIC_SYMBOL("CONDITION-FOR-USING-USER-MENU-CHOICE\?",AB_package);
    Quser_menu_choice_priority = STATIC_SYMBOL("USER-MENU-CHOICE-PRIORITY",
	    AB_package);
    list_constant_77 = STATIC_LIST_STAR((SI_Long)4L,
	    Qclass_for_user_menu_choice_qm,
	    Qcondition_for_using_user_menu_choice_qm,
	    Quser_menu_choice_priority,list_constant_9);
    list_constant_113 = STATIC_LIST_STAR((SI_Long)5L,Quser_menu_choice,
	    list_constant_76,Qnil,list_constant_77,list_constant_7);
    Qtabular_function_of_1_arg = STATIC_SYMBOL("TABULAR-FUNCTION-OF-1-ARG",
	    AB_package);
    Qkeep_sorted = STATIC_SYMBOL("KEEP-SORTED",AB_package);
    Qinterpolate = STATIC_SYMBOL("INTERPOLATE",AB_package);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qkeep_sorted,
	    Qinterpolate,list_constant_8);
    Qkeep_tabular_function_sorted_qm = 
	    STATIC_SYMBOL("KEEP-TABULAR-FUNCTION-SORTED\?",AB_package);
    Qtabular_function_interpolation_qm = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-INTERPOLATION\?",AB_package);
    list_constant_79 = STATIC_LIST_STAR((SI_Long)3L,
	    Qkeep_tabular_function_sorted_qm,
	    Qtabular_function_interpolation_qm,list_constant_9);
    list_constant_114 = STATIC_LIST_STAR((SI_Long)5L,
	    Qtabular_function_of_1_arg,list_constant_78,Qnil,
	    list_constant_79,list_constant_7);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qfirst_class = STATIC_SYMBOL("FIRST-CLASS",AB_package);
    Qsecond_class = STATIC_SYMBOL("SECOND-CLASS",AB_package);
    Qrelation_is_permanent = STATIC_SYMBOL("RELATION-IS-PERMANENT",AB_package);
    list_constant_80 = STATIC_LIST_STAR((SI_Long)4L,Qfirst_class,
	    Qsecond_class,Qrelation_is_permanent,list_constant_8);
    Qclass_of_subject = STATIC_SYMBOL("CLASS-OF-SUBJECT",AB_package);
    Qclass_of_object = STATIC_SYMBOL("CLASS-OF-OBJECT",AB_package);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)4L,Qclass_of_subject,
	    Qclass_of_object,Qrelation_is_permanent,list_constant_72);
    list_constant_115 = STATIC_LIST_STAR((SI_Long)5L,Qrelation,
	    list_constant_80,Qnil,list_constant_81,list_constant_7);
    Qframe_style_definition = STATIC_SYMBOL("FRAME-STYLE-DEFINITION",
	    AB_package);
    Qdescription_of_frame = STATIC_SYMBOL("DESCRIPTION-OF-FRAME",AB_package);
    list_constant_82 = STATIC_CONS(Qdescription_of_frame,list_constant_8);
    list_constant_83 = STATIC_CONS(Qdescription_of_frame,list_constant_9);
    list_constant_116 = STATIC_LIST_STAR((SI_Long)5L,
	    Qframe_style_definition,list_constant_82,Qnil,list_constant_83,
	    list_constant_7);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qscan_interval = STATIC_SYMBOL("SCAN-INTERVAL",AB_package);
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    Qfocal_objects = STATIC_SYMBOL("FOCAL-OBJECTS",AB_package);
    Qcategories = STATIC_SYMBOL("CATEGORIES",AB_package);
    Qrule_priority = STATIC_SYMBOL("RULE-PRIORITY",AB_package);
    Qdepth_first_backward_chaining_precedence = 
	    STATIC_SYMBOL("DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE",
	    AB_package);
    Qtimeout_for_rule_completion = 
	    STATIC_SYMBOL("TIMEOUT-FOR-RULE-COMPLETION",AB_package);
    list_constant_84 = STATIC_CONS(Qtimeout_for_rule_completion,Qnil);
    list_constant_85 = STATIC_LIST_STAR((SI_Long)8L,
	    Qtracing_and_breakpoints,Qscan_interval,Qfocal_classes,
	    Qfocal_objects,Qcategories,Qrule_priority,
	    Qdepth_first_backward_chaining_precedence,list_constant_84);
    Qrule_scan_interval = STATIC_SYMBOL("RULE-SCAN-INTERVAL",AB_package);
    Qrule_categories = STATIC_SYMBOL("RULE-CATEGORIES",AB_package);
    Qbackward_chaining_precedence = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-PRECEDENCE",AB_package);
    list_constant_86 = STATIC_LIST_STAR((SI_Long)8L,
	    Qtracing_and_breakpoints,Qrule_scan_interval,Qfocal_classes,
	    Qfocal_objects,Qrule_categories,Qrule_priority,
	    Qbackward_chaining_precedence,list_constant_84);
    list_constant_117 = STATIC_LIST_STAR((SI_Long)5L,Qrule,
	    list_constant_85,Qnil,list_constant_86,list_constant_7);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    list_constant_87 = STATIC_CONS(Qtracing_and_breakpoints,Qnil);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)5L,
	    Qgeneric_simulation_formula,list_constant_87,Qnil,
	    list_constant_87,list_constant_7);
    Qforeign_function_declaration = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-DECLARATION",AB_package);
    Qtimeout_interval = STATIC_SYMBOL("TIMEOUT-INTERVAL",AB_package);
    list_constant_88 = STATIC_CONS(Qtimeout_interval,Qnil);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)5L,
	    Qforeign_function_declaration,list_constant_88,Qnil,
	    list_constant_88,list_constant_7);
    Qmodel_definition = STATIC_SYMBOL("MODEL-DEFINITION",AB_package);
    Qdefault_simulation_time_increment = 
	    STATIC_SYMBOL("DEFAULT-SIMULATION-TIME-INCREMENT",AB_package);
    Qintegration_algorithm = STATIC_SYMBOL("INTEGRATION-ALGORITHM",AB_package);
    Qsimulation_procedure = STATIC_SYMBOL("SIMULATION-PROCEDURE",AB_package);
    Qsend_all_values_at_beginning_of_cycle = 
	    STATIC_SYMBOL("SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE",AB_package);
    Qsimulation_control_specifications = 
	    STATIC_SYMBOL("SIMULATION-CONTROL-SPECIFICATIONS",AB_package);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)6L,
	    Qdefault_simulation_time_increment,Qintegration_algorithm,
	    Qsimulation_procedure,Qsend_all_values_at_beginning_of_cycle,
	    Qsimulation_control_specifications,list_constant_8);
    Qdefault_simulation_time_increment_for_model = 
	    STATIC_SYMBOL("DEFAULT-SIMULATION-TIME-INCREMENT-FOR-MODEL",
	    AB_package);
    Qintegration_algorithm_for_model = 
	    STATIC_SYMBOL("INTEGRATION-ALGORITHM-FOR-MODEL",AB_package);
    Qsimulation_procedure_for_model = 
	    STATIC_SYMBOL("SIMULATION-PROCEDURE-FOR-MODEL",AB_package);
    Qsend_all_values_at_beginning_of_cycle_for_model_qm = 
	    STATIC_SYMBOL("SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE-FOR-MODEL\?",
	    AB_package);
    list_constant_90 = STATIC_LIST_STAR((SI_Long)6L,
	    Qdefault_simulation_time_increment_for_model,
	    Qintegration_algorithm_for_model,
	    Qsimulation_procedure_for_model,
	    Qsend_all_values_at_beginning_of_cycle_for_model_qm,
	    Qsimulation_control_specifications,list_constant_9);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)5L,Qmodel_definition,
	    list_constant_89,Qnil,list_constant_90,list_constant_7);
    Qexternal_simulation_definition = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION",AB_package);
    Qclass_of_object_computed_by_this = 
	    STATIC_SYMBOL("CLASS-OF-OBJECT-COMPUTED-BY-THIS",AB_package);
    list_constant_91 = STATIC_CONS(Qclass_of_object_computed_by_this,
	    list_constant_8);
    list_constant_92 = STATIC_CONS(Qclass_of_object_computed_by_this,
	    list_constant_9);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)5L,
	    Qexternal_simulation_definition,list_constant_91,Qnil,
	    list_constant_92,list_constant_7);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qdefault_text_box_colors = STATIC_SYMBOL("DEFAULT-TEXT-BOX-COLORS",
	    AB_package);
    list_constant_93 = STATIC_CONS(Qdefault_text_box_colors,Qnil);
    list_constant_94 = STATIC_CONS(Qtext_cell_plist_for_text_box,Qnil);
    list_constant_95 = STATIC_LIST_STAR((SI_Long)4L,list_constant_93,Qnil,
	    list_constant_94,list_constant_7);
    list_constant_122 = STATIC_CONS(Qfree_text,list_constant_95);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    list_constant_123 = STATIC_CONS(Qborderless_free_text,list_constant_95);
    Qtext_inserter = STATIC_SYMBOL("TEXT-INSERTER",AB_package);
    list_constant_124 = STATIC_CONS(Qtext_inserter,list_constant_95);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qaction_button_priority = STATIC_SYMBOL("ACTION-BUTTON-PRIORITY",
	    AB_package);
    list_constant_96 = STATIC_CONS(Qaction_button_priority,list_constant_9);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)5L,Qaction_button,
	    list_constant_75,Qnil,list_constant_96,list_constant_7);
    Qnon_action_button = STATIC_SYMBOL("NON-ACTION-BUTTON",AB_package);
    Qvalue_on_activation = STATIC_SYMBOL("VALUE-ON-ACTIVATION",AB_package);
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qvalue_on_activation,
	    Qvariable_or_parameter);
    Qvalue_on_activation_qm = STATIC_SYMBOL("VALUE-ON-ACTIVATION\?",
	    AB_package);
    Qassociated_variable_designation_qm = 
	    STATIC_SYMBOL("ASSOCIATED-VARIABLE-DESIGNATION\?",AB_package);
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qvalue_on_activation_qm,
	    Qassociated_variable_designation_qm);
    list_constant_126 = STATIC_LIST_STAR((SI_Long)5L,Qnon_action_button,
	    list_constant_97,Qnil,list_constant_98,list_constant_7);
    Qcheck_box = STATIC_SYMBOL("CHECK-BOX",AB_package);
    Qon_value = STATIC_SYMBOL("ON-VALUE",AB_package);
    Qoff_value = STATIC_SYMBOL("OFF-VALUE",AB_package);
    list_constant_99 = STATIC_LIST_STAR((SI_Long)3L,Qon_value,Qoff_value,
	    list_constant_8);
    Qon_value_for_check_box = STATIC_SYMBOL("ON-VALUE-FOR-CHECK-BOX",
	    AB_package);
    Qoff_value_for_check_box = STATIC_SYMBOL("OFF-VALUE-FOR-CHECK-BOX",
	    AB_package);
    list_constant_100 = STATIC_LIST_STAR((SI_Long)3L,
	    Qon_value_for_check_box,Qoff_value_for_check_box,list_constant_9);
    list_constant_127 = STATIC_LIST_STAR((SI_Long)5L,Qcheck_box,
	    list_constant_99,Qnil,list_constant_100,list_constant_7);
    Qradio_button = STATIC_SYMBOL("RADIO-BUTTON",AB_package);
    list_constant_101 = STATIC_CONS(Qon_value,list_constant_8);
    Qvalue_for_radio_button = STATIC_SYMBOL("VALUE-FOR-RADIO-BUTTON",
	    AB_package);
    list_constant_102 = STATIC_CONS(Qvalue_for_radio_button,list_constant_9);
    list_constant_128 = STATIC_LIST((SI_Long)4L,Qradio_button,
	    list_constant_101,Qnil,list_constant_102);
    Qslider = STATIC_SYMBOL("SLIDER",AB_package);
    Qminimum_value = STATIC_SYMBOL("MINIMUM-VALUE",AB_package);
    Qmaximum_value = STATIC_SYMBOL("MAXIMUM-VALUE",AB_package);
    Qset_value_while_sliding_qm = 
	    STATIC_SYMBOL("SET-VALUE-WHILE-SLIDING\?",AB_package);
    Qwhen_to_show_value = STATIC_SYMBOL("WHEN-TO-SHOW-VALUE",AB_package);
    list_constant_103 = STATIC_LIST_STAR((SI_Long)5L,Qminimum_value,
	    Qmaximum_value,Qset_value_while_sliding_qm,Qwhen_to_show_value,
	    list_constant_8);
    Qminimum_value_for_slider = STATIC_SYMBOL("MINIMUM-VALUE-FOR-SLIDER",
	    AB_package);
    Qmaximum_value_for_slider = STATIC_SYMBOL("MAXIMUM-VALUE-FOR-SLIDER",
	    AB_package);
    list_constant_104 = STATIC_LIST_STAR((SI_Long)5L,
	    Qminimum_value_for_slider,Qmaximum_value_for_slider,
	    Qset_value_while_sliding_qm,Qwhen_to_show_value,list_constant_9);
    list_constant_129 = STATIC_LIST_STAR((SI_Long)5L,Qslider,
	    list_constant_103,Qnil,list_constant_104,list_constant_7);
    Qtype_in_box = STATIC_SYMBOL("TYPE-IN-BOX",AB_package);
    Qformat_for_type_in_box = STATIC_SYMBOL("FORMAT-FOR-TYPE-IN-BOX",
	    AB_package);
    Qblank_for_type_in_qm = STATIC_SYMBOL("BLANK-FOR-TYPE-IN\?",AB_package);
    Qhave_edit_option_buttons_for_type_in_qm = 
	    STATIC_SYMBOL("HAVE-EDIT-OPTION-BUTTONS-FOR-TYPE-IN\?",AB_package);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qformat_for_type_in_box,
	    Qblank_for_type_in_qm,Qhave_edit_option_buttons_for_type_in_qm);
    list_constant_130 = STATIC_LIST_STAR((SI_Long)5L,Qtype_in_box,
	    list_constant_105,Qnil,list_constant_105,list_constant_7);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    Qtime_increment_for_update = STATIC_SYMBOL("TIME-INCREMENT-FOR-UPDATE",
	    AB_package);
    list_constant_106 = STATIC_LIST((SI_Long)2L,Qtracing_and_breakpoints,
	    Qtime_increment_for_update);
    Qtime_increment_for_update_qm = 
	    STATIC_SYMBOL("TIME-INCREMENT-FOR-UPDATE\?",AB_package);
    list_constant_107 = STATIC_LIST((SI_Long)2L,Qtracing_and_breakpoints,
	    Qtime_increment_for_update_qm);
    list_constant_131 = STATIC_LIST((SI_Long)4L,Qsimulation_subtable,
	    list_constant_106,Qnil,list_constant_107);
    list_constant_163 = STATIC_LIST((SI_Long)24L,list_constant_108,
	    list_constant_109,list_constant_110,list_constant_111,
	    list_constant_112,list_constant_113,list_constant_114,
	    list_constant_115,list_constant_116,list_constant_117,
	    list_constant_118,list_constant_119,list_constant_120,
	    list_constant_121,list_constant_122,list_constant_123,
	    list_constant_124,list_constant_125,list_constant_126,
	    list_constant_127,list_constant_128,list_constant_129,
	    list_constant_130,list_constant_131);
    list_constant_164 = STATIC_LIST_STAR((SI_Long)32L,list_constant_132,
	    list_constant_133,list_constant_134,list_constant_135,
	    list_constant_136,list_constant_137,list_constant_138,
	    list_constant_139,list_constant_140,list_constant_141,
	    list_constant_142,list_constant_143,list_constant_144,
	    list_constant_145,list_constant_146,list_constant_147,
	    list_constant_148,list_constant_149,list_constant_150,
	    list_constant_151,list_constant_152,list_constant_153,
	    list_constant_154,list_constant_155,list_constant_156,
	    list_constant_157,list_constant_158,list_constant_159,
	    list_constant_160,list_constant_161,list_constant_162,
	    list_constant_163);
    list_constant_165 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_164);
    record_system_variable(Qlist_of_user_overridable_system_slots,Qframes2,
	    list_constant_165,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_variable_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-VARIABLE-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_variable_slots,
	    User_overridable_variable_slots);
    Qhistory_specification_for_simulation_subtables_qm = 
	    STATIC_SYMBOL("HISTORY-SPECIFICATION-FOR-SIMULATION-SUBTABLES\?",
	    AB_package);
    list_constant_166 = STATIC_CONS(Qicon_description,Qnil);
    list_constant_167 = STATIC_LIST_STAR((SI_Long)9L,Qvalidity_interval,
	    Qdata_server_map,Qbackground_collection_interval_qm,
	    Qframe_flags,Qvariable_or_parameter_history_specification_qm,
	    Qhistory_specification_for_simulation_subtables_qm,
	    Qdata_type_of_variable_or_parameter,
	    Qinitial_value_of_variable_or_parameter,list_constant_166);
    list_constant_168 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_167);
    record_system_variable(Quser_overridable_variable_slots,Qframes2,
	    list_constant_168,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_parameter_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-PARAMETER-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_parameter_slots,
	    User_overridable_parameter_slots);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdata_type_of_variable_or_parameter,
	    Qinitial_value_of_variable_or_parameter,list_constant_166);
    list_constant_170 = 
	    STATIC_CONS(Qvariable_or_parameter_history_specification_qm,
	    list_constant_169);
    list_constant_171 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_170);
    record_system_variable(Quser_overridable_parameter_slots,Qframes2,
	    list_constant_171,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_g2_array_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-G2-ARRAY-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_g2_array_slots,
	    User_overridable_g2_array_slots);
    list_constant_172 = STATIC_LIST_STAR((SI_Long)4L,
	    Qg2_array_element_type,Qg2_array_length,
	    Qg2_array_initial_values,list_constant_166);
    list_constant_173 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_172);
    record_system_variable(Quser_overridable_g2_array_slots,Qframes2,
	    list_constant_173,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_g2_list_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-G2-LIST-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_g2_list_slots,
	    User_overridable_g2_list_slots);
    list_constant_174 = STATIC_LIST_STAR((SI_Long)3L,Qlist_type,
	    Qinsert_duplicate_elements_qm,list_constant_166);
    list_constant_175 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_174);
    record_system_variable(Quser_overridable_g2_list_slots,Qframes2,
	    list_constant_175,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_object_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-OBJECT-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_object_slots,
	    User_overridable_object_slots);
    list_constant_176 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_166);
    record_system_variable(Quser_overridable_object_slots,Qframes2,
	    list_constant_176,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_message_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-MESSAGE-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_message_slots,
	    User_overridable_message_slots);
    list_constant_177 = STATIC_LIST((SI_Long)4L,
	    Qdefault_text_box_format_name,Qtext_cell_plist_for_text_box,
	    Qminimum_width_of_text_box,Qminimum_height_of_text_box);
    list_constant_178 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_177);
    record_system_variable(Quser_overridable_message_slots,Qframes2,
	    list_constant_178,Qnil,Qnil,Qnil,Qnil);
    Quser_overridable_connection_slots = 
	    STATIC_SYMBOL("USER-OVERRIDABLE-CONNECTION-SLOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_overridable_connection_slots,
	    User_overridable_connection_slots);
    list_constant_179 = STATIC_LIST((SI_Long)3L,Qcross_section_pattern,
	    Qstub_length,Qjunction_block_class);
    list_constant_180 = STATIC_LIST((SI_Long)2L,Qquote,list_constant_179);
    record_system_variable(Quser_overridable_connection_slots,Qframes2,
	    list_constant_180,Qnil,Qnil,Qnil,Qnil);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    SET_SYMBOL_FUNCTION(Qcar_eq,STATIC_FUNCTION(car_eq,NIL,FALSE,2,2));
    string_constant = 
	    string_append2(STATIC_STRING("The direct superior class, ~A, of class ~A is not defined.~\n            ~%It was defined when this class definition was initially ~\n            evaluated.~\n            ~%The u"),
	    STATIC_STRING("ser is advised to recompile/load the definition of ~\n            the superior class."));
    Qaliases_for_slot_name = STATIC_SYMBOL("ALIASES-FOR-SLOT-NAME",AB_package);
    Aliases_for_slot_name_prop = Qaliases_for_slot_name;
    Qslot_names_for_alias = STATIC_SYMBOL("SLOT-NAMES-FOR-ALIAS",AB_package);
    Slot_names_for_alias_prop = Qslot_names_for_alias;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Table_to_map_generic_method_id_to_generic_method_name == UNBOUND) {
	gensymed_symbol = Maximum_number_of_generic_methods;
	the_array = make_array(1,gensymed_symbol);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(gensymed_symbol);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	Table_to_map_generic_method_id_to_generic_method_name = the_array;
    }
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    install_generic_method_id(Qgenerate_spot,FIX((SI_Long)0L));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    install_generic_method_id(Qcleanup,FIX((SI_Long)1L));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    install_generic_method_id(Qinitialize,FIX((SI_Long)2L));
    Qanalyze_for_consistency = STATIC_SYMBOL("ANALYZE-FOR-CONSISTENCY",
	    AB_package);
    install_generic_method_id(Qanalyze_for_consistency,FIX((SI_Long)3L));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    install_generic_method_id(Qinitialize_after_reading,FIX((SI_Long)4L));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    install_generic_method_id(Qdraw,FIX((SI_Long)5L));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    install_generic_method_id(Qactivate,FIX((SI_Long)6L));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    install_generic_method_id(Qdeactivate,FIX((SI_Long)7L));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    install_generic_method_id(Qinstall_system_table,FIX((SI_Long)8L));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    install_generic_method_id(Qdeinstall_system_table,FIX((SI_Long)9L));
    Qnote_name_change = STATIC_SYMBOL("NOTE-NAME-CHANGE",AB_package);
    install_generic_method_id(Qnote_name_change,FIX((SI_Long)10L));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    install_generic_method_id(Qdenote_cell_array_element,FIX((SI_Long)11L));
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    install_generic_method_id(Qexpression_cell_updated,FIX((SI_Long)12L));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    install_generic_method_id(Qdeactivate_subclass_of_entity,
	    FIX((SI_Long)13L));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    install_generic_method_id(Qactivate_subclass_of_entity,FIX((SI_Long)14L));
    Qdescribe_frame = STATIC_SYMBOL("DESCRIBE-FRAME",AB_package);
    install_generic_method_id(Qdescribe_frame,FIX((SI_Long)15L));
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    install_generic_method_id(Qput_box_translation_and_text_slot_value,
	    FIX((SI_Long)16L));
    Qcopy_frame = STATIC_SYMBOL("COPY-FRAME",AB_package);
    install_generic_method_id(Qcopy_frame,FIX((SI_Long)17L));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    install_generic_method_id(Qnote_runs_while_inactive_change,
	    FIX((SI_Long)18L));
    Qupdate_frame_status_and_notes = 
	    STATIC_SYMBOL("UPDATE-FRAME-STATUS-AND-NOTES",AB_package);
    install_generic_method_id(Qupdate_frame_status_and_notes,
	    FIX((SI_Long)19L));
    Qfix_frame_with_substitute_class = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS",AB_package);
    install_generic_method_id(Qfix_frame_with_substitute_class,
	    FIX((SI_Long)20L));
    Qclear_display = STATIC_SYMBOL("CLEAR-DISPLAY",AB_package);
    install_generic_method_id(Qclear_display,FIX((SI_Long)21L));
    Qupdate_display = STATIC_SYMBOL("UPDATE-DISPLAY",AB_package);
    install_generic_method_id(Qupdate_display,FIX((SI_Long)22L));
    Qclick = STATIC_SYMBOL("CLICK",AB_package);
    install_generic_method_id(Qclick,FIX((SI_Long)23L));
    Qscroll_block = STATIC_SYMBOL("SCROLL-BLOCK",AB_package);
    install_generic_method_id(Qscroll_block,FIX((SI_Long)24L));
    Qcompute_minimum_right_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-RIGHT-EDGE",AB_package);
    install_generic_method_id(Qcompute_minimum_right_edge,FIX((SI_Long)25L));
    Qcompute_minimum_bottom_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-BOTTOM-EDGE",AB_package);
    install_generic_method_id(Qcompute_minimum_bottom_edge,FIX((SI_Long)26L));
    Qexecute_command = STATIC_SYMBOL("EXECUTE-COMMAND",AB_package);
    install_generic_method_id(Qexecute_command,FIX((SI_Long)27L));
    Qreformat_as_appropriate = STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE",
	    AB_package);
    install_generic_method_id(Qreformat_as_appropriate,FIX((SI_Long)28L));
    Qupdate_cell_based_display = STATIC_SYMBOL("UPDATE-CELL-BASED-DISPLAY",
	    AB_package);
    install_generic_method_id(Qupdate_cell_based_display,FIX((SI_Long)29L));
    Qactivate_if_possible_and_propagate = 
	    STATIC_SYMBOL("ACTIVATE-IF-POSSIBLE-AND-PROPAGATE",AB_package);
    install_generic_method_id(Qactivate_if_possible_and_propagate,
	    FIX((SI_Long)30L));
    Qdeactivate_and_propagate = STATIC_SYMBOL("DEACTIVATE-AND-PROPAGATE",
	    AB_package);
    install_generic_method_id(Qdeactivate_and_propagate,FIX((SI_Long)31L));
    Qshift = STATIC_SYMBOL("SHIFT",AB_package);
    install_generic_method_id(Qshift,FIX((SI_Long)32L));
    Qassert_frame_notes = STATIC_SYMBOL("ASSERT-FRAME-NOTES",AB_package);
    install_generic_method_id(Qassert_frame_notes,FIX((SI_Long)33L));
    Qretract_frame_notes = STATIC_SYMBOL("RETRACT-FRAME-NOTES",AB_package);
    install_generic_method_id(Qretract_frame_notes,FIX((SI_Long)34L));
    Qresize = STATIC_SYMBOL("RESIZE",AB_package);
    install_generic_method_id(Qresize,FIX((SI_Long)35L));
    Qplace_reference_of_cell = STATIC_SYMBOL("PLACE-REFERENCE-OF-CELL",
	    AB_package);
    install_generic_method_id(Qplace_reference_of_cell,FIX((SI_Long)36L));
    Qrecompile_expression_at_component_particulars = 
	    STATIC_SYMBOL("RECOMPILE-EXPRESSION-AT-COMPONENT-PARTICULARS",
	    AB_package);
    install_generic_method_id(Qrecompile_expression_at_component_particulars,
	    FIX((SI_Long)37L));
    Qnote_may_refer_to_inactive_items_change = 
	    STATIC_SYMBOL("NOTE-MAY-REFER-TO-INACTIVE-ITEMS-CHANGE",
	    AB_package);
    install_generic_method_id(Qnote_may_refer_to_inactive_items_change,
	    FIX((SI_Long)38L));
    Qreconsider_formatting = STATIC_SYMBOL("RECONSIDER-FORMATTING",AB_package);
    install_generic_method_id(Qreconsider_formatting,FIX((SI_Long)39L));
    Qstrip_text = STATIC_SYMBOL("STRIP-TEXT",AB_package);
    install_generic_method_id(Qstrip_text,FIX((SI_Long)40L));
    Qhandle_end_operation = STATIC_SYMBOL("HANDLE-END-OPERATION",AB_package);
    install_generic_method_id(Qhandle_end_operation,FIX((SI_Long)41L));
    Qadd_items_to_edit_workspace = 
	    STATIC_SYMBOL("ADD-ITEMS-TO-EDIT-WORKSPACE",AB_package);
    install_generic_method_id(Qadd_items_to_edit_workspace,FIX((SI_Long)42L));
    Qquery_cell_updated = STATIC_SYMBOL("QUERY-CELL-UPDATED",AB_package);
    install_generic_method_id(Qquery_cell_updated,FIX((SI_Long)43L));
    Qdesignation_cell_updated = STATIC_SYMBOL("DESIGNATION-CELL-UPDATED",
	    AB_package);
    install_generic_method_id(Qdesignation_cell_updated,FIX((SI_Long)44L));
    Qgenerate_designation_of_cell = 
	    STATIC_SYMBOL("GENERATE-DESIGNATION-OF-CELL",AB_package);
    install_generic_method_id(Qgenerate_designation_of_cell,FIX((SI_Long)45L));
    Qupdate_part_dependencies = STATIC_SYMBOL("UPDATE-PART-DEPENDENCIES",
	    AB_package);
    install_generic_method_id(Qupdate_part_dependencies,FIX((SI_Long)46L));
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    install_generic_method_id(Qmanually_disable,FIX((SI_Long)47L));
    Qmanually_enable = STATIC_SYMBOL("MANUALLY-ENABLE",AB_package);
    install_generic_method_id(Qmanually_enable,FIX((SI_Long)48L));
    Qhandle_change_or_deletion_fanout = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT",AB_package);
    install_generic_method_id(Qhandle_change_or_deletion_fanout,
	    FIX((SI_Long)49L));
    Qchange_size_per_bounding_rectangle = 
	    STATIC_SYMBOL("CHANGE-SIZE-PER-BOUNDING-RECTANGLE",AB_package);
    install_generic_method_id(Qchange_size_per_bounding_rectangle,
	    FIX((SI_Long)50L));
    Qrestore_history_buffer = STATIC_SYMBOL("RESTORE-HISTORY-BUFFER",
	    AB_package);
    install_generic_method_id(Qrestore_history_buffer,FIX((SI_Long)51L));
    Qget_workspace_representation_type = 
	    STATIC_SYMBOL("GET-WORKSPACE-REPRESENTATION-TYPE",AB_package);
    install_generic_method_id(Qget_workspace_representation_type,
	    FIX((SI_Long)52L));
    Qnote_ancestor_not_activatable = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-NOT-ACTIVATABLE",AB_package);
    install_generic_method_id(Qnote_ancestor_not_activatable,
	    FIX((SI_Long)53L));
    Qnote_ancestor_manually_enabled = 
	    STATIC_SYMBOL("NOTE-ANCESTOR-MANUALLY-ENABLED",AB_package);
    install_generic_method_id(Qnote_ancestor_manually_enabled,
	    FIX((SI_Long)54L));
    Qprepare_to_saving_frame = STATIC_SYMBOL("PREPARE-TO-SAVING-FRAME",
	    AB_package);
    install_generic_method_id(Qprepare_to_saving_frame,FIX((SI_Long)55L));
    Qon_frame_saved = STATIC_SYMBOL("ON-FRAME-SAVED",AB_package);
    install_generic_method_id(Qon_frame_saved,FIX((SI_Long)56L));
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    Generic_method_lambda_list_prop = Qgeneric_method_lambda_list;
    Qno_slot = STATIC_SYMBOL("NO-SLOT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_slot,No_slot);
    list_constant_181 = STATIC_CONS(Qno_slot,Qnil);
    No_slot = list_constant_181;
    temp = make_partial_buffer_info(FIX((SI_Long)16L),FIX((SI_Long)1L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)32L),FIX((SI_Long)4L),
	    FIX((SI_Long)0L),FIX((SI_Long)2L));
    temp_2 = make_partial_buffer_info(FIX((SI_Long)64L),FIX((SI_Long)8L),
	    FIX((SI_Long)5L),FIX((SI_Long)3L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)128L),FIX((SI_Long)16L),
	    FIX((SI_Long)9L),FIX((SI_Long)4L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)256L),FIX((SI_Long)32L),
	    FIX((SI_Long)13L),FIX((SI_Long)5L));
    temp_5 = make_partial_buffer_info(FIX((SI_Long)512L),FIX((SI_Long)64L),
	    FIX((SI_Long)17L),FIX((SI_Long)6L));
    Frame_lookup_structure_vector_allocation_schemes = list(7,temp,temp_1,
	    temp_2,temp_3,temp_4,temp_5,
	    make_partial_buffer_info(FIX((SI_Long)1024L),
	    FIX((SI_Long)128L),FIX((SI_Long)21L),FIX((SI_Long)7L)));
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    Qput_attribute_value = STATIC_SYMBOL("PUT-ATTRIBUTE-VALUE",AB_package);
    Qslot_value_float = STATIC_SYMBOL("SLOT-VALUE-FLOAT",AB_package);
    Qslot_value_float_p_function = 
	    STATIC_SYMBOL("SLOT-VALUE-FLOAT-P-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_value_float_p_function,
	    STATIC_FUNCTION(slot_value_float_p_function,NIL,FALSE,1,1));
    list_constant_182 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qslot_value_float_p_function);
    Qsimple_type_specification = STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",
	    AB_package);
    mutate_global_property(Qslot_value_float,list_constant_182,
	    Qsimple_type_specification);
    Qslot_value_long = STATIC_SYMBOL("SLOT-VALUE-LONG",AB_package);
    Qslot_value_long_p_function = 
	    STATIC_SYMBOL("SLOT-VALUE-LONG-P-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_value_long_p_function,
	    STATIC_FUNCTION(slot_value_long_p_function,NIL,FALSE,1,1));
    list_constant_183 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qslot_value_long_p_function);
    mutate_global_property(Qslot_value_long,list_constant_183,
	    Qsimple_type_specification);
    string_constant_1 = STATIC_STRING("not a number");
    Qtype_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    mutate_global_property(Qslot_value_float,string_constant_1,
	    Qtype_error_printer);
    mutate_global_property(Qslot_value_long,string_constant_1,
	    Qtype_error_printer);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qdefault_slot_constant = STATIC_SYMBOL("DEFAULT-SLOT-CONSTANT",AB_package);
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    Slot_value_reclaimer_prop = Qslot_value_reclaimer;
    Qlookup_structure = STATIC_SYMBOL("LOOKUP-STRUCTURE",AB_package);
    Qreclaim_lookup_structure_value = 
	    STATIC_SYMBOL("RECLAIM-LOOKUP-STRUCTURE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_lookup_structure_value,
	    STATIC_FUNCTION(reclaim_lookup_structure_value,NIL,FALSE,2,2));
    mutate_global_property(Qlookup_structure,
	    SYMBOL_FUNCTION(Qreclaim_lookup_structure_value),
	    Qslot_value_reclaimer);
    Qclass_description_slot = STATIC_SYMBOL("CLASS-DESCRIPTION-SLOT",
	    AB_package);
    Qreclaim_class_description_slot_value = 
	    STATIC_SYMBOL("RECLAIM-CLASS-DESCRIPTION-SLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_class_description_slot_value,
	    STATIC_FUNCTION(reclaim_class_description_slot_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qclass_description_slot,
	    SYMBOL_FUNCTION(Qreclaim_class_description_slot_value),
	    Qslot_value_reclaimer);
    Qdefined_evaluation_type_reclaimer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-RECLAIMER",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qrelation_instance_tree = STATIC_SYMBOL("RELATION-INSTANCE-TREE",
	    AB_package);
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    list_constant_184 = STATIC_CONS(Qvector_slot,Qnil);
    list_constant_185 = STATIC_CONS(Qsystem,Qnil);
    list_constant = STATIC_LIST((SI_Long)2L,list_constant_184,
	    list_constant_185);
    list_constant_1 = STATIC_CONS(Qroot,Qnil);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qlookup_structure,
	    Qclass_description_slot);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qdef_root_class = STATIC_SYMBOL("DEF-ROOT-CLASS",AB_package);
    list_constant_3 = STATIC_CONS(Qdef_root_class,Qnil);
    Qdefined = STATIC_SYMBOL("DEFINED",AB_package);
    define_root_class();
}
