/* kbmrge.c
 * Input file:  kb-merge.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbmrge.h"


DEFINE_VARIABLE_WITH_SYMBOL(Class_name_conflicts, Qclass_name_conflicts);

DEFINE_VARIABLE_WITH_SYMBOL(Deferred_class_definitions_alist, Qdeferred_class_definitions_alist);

DEFINE_VARIABLE_WITH_SYMBOL(Record_class_name_conflicts_qm, Qrecord_class_name_conflicts_qm);

static Object Qcombine_class_defintions;  /* combine-class-defintions */

static Object Qconnection;         /* connection */

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qjunction_block_class_for_class;  /* junction-block-class-for-class */

static Object Qmerge_definitions;  /* merge-definitions */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* COMBINE-CLASS-DEFINITIONS */
Object combine_class_definitions(class_definition_1,class_definition_2)
    Object class_definition_1, class_definition_2;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, class_1;
    Object class_2, instance_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, temp_2, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, junction_block_class_2;
    Object junction_block_class_1, change_command, junction_block_definition_2;
    Object x2, sub_class_bit_vector, inferior_class, ab_loop_list_;
    Object inferior_class_definition, inferior_class_definition_class;
    Object direct_superiors_of_defined_class;
    Object class_1_a_direct_superior_already_qm;
    Object new_direct_superiors_of_defined_class, new_direct_superiors;
    Object class_3, ab_loop_list__1, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object instance;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,0);
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
	  SVREF(temp,svref_arg_2) = Qcombine_class_defintions;
      }
      class_1 = ISVREF(class_definition_1,(SI_Long)20L);
      class_2 = ISVREF(class_definition_2,(SI_Long)20L);
      instance_qm = Nil;
    next_loop:
      instance_qm = lookup_kb_specific_property_value(class_2,
	      Instances_specific_to_this_class_kbprop);
      if ( !TRUEP(instance_qm))
	  goto end_loop;
      reclassify_frame(instance_qm,class_1);
      goto next_loop;
    end_loop:;
      if (memq_function(Qconnection,
	      get_lookup_slot_value_given_default(class_definition_1,
	      Qclass_inheritance_path_of_definition,Nil))) {
	  update_class_in_connections(class_2,class_1);
	  skip_list = CDR(Symbol_properties_table);
	  key_value = class_2;
	  key_hash_value = SXHASH_SYMBOL_1(class_2) & 
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
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_3:
	  if ( !TRUEP(marked))
	      goto end_loop_2;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = class_2;
	      temp_1 = Symbol_properties_table;
	      temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
		      FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	next_loop_4:
	  if (level < ab_loop_bind_)
	      goto end_loop_4;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_5:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_6:
	  if ( !TRUEP(marked))
	      goto end_loop_5;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
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
	    next_loop_7:
	      if (level < ab_loop_bind_)
		  goto end_loop_7;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_8:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_9:
	      if ( !TRUEP(marked))
		  goto end_loop_8;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_11:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_12:
	      if ( !TRUEP(marked))
		  goto end_loop_11;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
	  junction_block_class_2 = 
		  ISVREF(get_slot_description_of_class_description_function(Qjunction_block_class_for_class,
		  gensymed_symbol,Nil),(SI_Long)6L);
	  skip_list = CDR(Symbol_properties_table);
	  key_value = class_1;
	  key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_15:
	  if ( !TRUEP(marked))
	      goto end_loop_14;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = class_1;
	      temp_1 = Symbol_properties_table;
	      temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
		      FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_18:
	  if ( !TRUEP(marked))
	      goto end_loop_17;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
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
	    next_loop_19:
	      if (level < ab_loop_bind_)
		  goto end_loop_19;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_20:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_21:
	      if ( !TRUEP(marked))
		  goto end_loop_20;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_24:
	      if ( !TRUEP(marked))
		  goto end_loop_23;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
	  junction_block_class_1 = 
		  ISVREF(get_slot_description_of_class_description_function(Qjunction_block_class_for_class,
		  gensymed_symbol,Nil),(SI_Long)6L);
	  change_command = slot_value_list_2(Qmerge_definitions,
		  junction_block_class_1);
	  junction_block_definition_2 = 
		  lookup_global_or_kb_specific_property_value(junction_block_class_2,
		  Class_definition_gkbprop);
	  if (SIMPLE_VECTOR_P(junction_block_definition_2) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(junction_block_definition_2)) 
		  > (SI_Long)2L &&  !EQ(ISVREF(junction_block_definition_2,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(junction_block_definition_2,(SI_Long)1L);
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
		      IFIX(ISVREF(Class_definition_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_3 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
	  if (temp_3)
	      put_change(junction_block_definition_2,change_command,Nil);
      }
      inferior_class = Nil;
      ab_loop_list_ = lookup_global_or_kb_specific_property_value(class_2,
	      Inferior_classes_gkbprop);
      inferior_class_definition = Nil;
      inferior_class_definition_class = Nil;
      direct_superiors_of_defined_class = Nil;
      class_1_a_direct_superior_already_qm = Nil;
      new_direct_superiors_of_defined_class = Nil;
    next_loop_25:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_25;
      inferior_class = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      inferior_class_definition = 
	      lookup_global_or_kb_specific_property_value(inferior_class,
	      Class_definition_gkbprop);
      inferior_class_definition_class = 
	      ISVREF(ISVREF(inferior_class_definition,(SI_Long)1L),
	      (SI_Long)1L);
      direct_superiors_of_defined_class = ISVREF(inferior_class_definition,
	      (SI_Long)21L);
      class_1_a_direct_superior_already_qm = memq_function(class_1,
	      direct_superiors_of_defined_class);
      new_direct_superiors = Nil;
      class_3 = Nil;
      ab_loop_list__1 = direct_superiors_of_defined_class;
    next_loop_26:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_26;
      class_3 = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (EQ(class_3,class_2)) {
	  if ( !TRUEP(class_1_a_direct_superior_already_qm))
	      new_direct_superiors = nconc2(new_direct_superiors,
		      slot_value_cons_1(class_1,Nil));
      }
      else
	  new_direct_superiors = nconc2(new_direct_superiors,
		  slot_value_cons_1(class_3,Nil));
      goto next_loop_26;
    end_loop_26:;
      new_direct_superiors_of_defined_class = new_direct_superiors;
      clear_override_frame_notes_from_class_definitions(inferior_class);
      alter_inheritance_of_class_without_changing_foundation_class(inferior_class_definition,
	      new_direct_superiors_of_defined_class,class_2,class_1);
      process_default_overrides(inferior_class,T);
      goto next_loop_25;
    end_loop_25:;
      scope_conses = Scope_conses;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      instance = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(class_1);
      next_loop_27:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_28:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_27;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_27;
	    goto next_loop_28;
	  end_loop_27:
	    temp_3 =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3)
	    goto end_loop_28;
	instance = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	update_attribute_tables(1,instance);
	goto next_loop_27;
      end_loop_28:
	result = VALUES_1(Qnil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qdo_not_save;        /* do-not-save */

static Object Qsave;               /* save */

static Object Qnote_slot_changes;  /* note-slot-changes */

static Object Qab_class;           /* class */

/* RECLASSIFY-FRAME */
Object reclassify_frame(frame,new_class)
    Object frame, new_class;
{
    Object old_class, old_class_description, old_slot_descriptions;
    Object new_class_description, sub_class_bit_vector, frame_1, sub_vector_qm;
    Object function_qm, old_slot_description, ab_loop_list_, defining_class;
    Object new_slot_description, slot_description, new_value, slot_features;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, method_index;
    char frame_active_qm, temp;

    x_note_fn_call(130,1);
    old_class = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)1L);
    old_class_description = ISVREF(frame,(SI_Long)1L);
    old_slot_descriptions = ISVREF(old_class_description,(SI_Long)6L);
    new_class_description = 
	    lookup_global_or_kb_specific_property_value(new_class,
	    Class_description_gkbprop);
    frame_active_qm = (SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)5L)) & 
	    (SI_Long)1L);
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
    if (temp)
	update_images_of_block(frame,T,Nil);
    if (frame_active_qm) {
	method_index = (SI_Long)31L;
	frame_1 = frame;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    inline_funcall_2(function_qm,frame_1,Nil);
    }
    SVREF(frame,FIX((SI_Long)1L)) = new_class_description;
    old_slot_description = Nil;
    ab_loop_list_ = old_slot_descriptions;
    defining_class = Nil;
    new_slot_description = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    old_slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    defining_class = ISVREF(old_slot_description,(SI_Long)3L);
    new_slot_description = 
	    get_slot_description_of_class_description_function(ISVREF(old_slot_description,
	    (SI_Long)2L),new_class_description,EQ(defining_class,
	    old_class) ? new_class : defining_class);
    if (EQ(get_slot_description_value(frame,old_slot_description),
	    ISVREF(old_slot_description,(SI_Long)6L))) {
	slot_description = new_slot_description;
	new_value = ISVREF(new_slot_description,(SI_Long)6L);
	if (Noting_changes_to_kb_p) {
	    slot_features = ISVREF(slot_description,(SI_Long)9L);
	    temp = assq_function(Qtype,slot_features) ?  
		    !TRUEP(assq_function(Qdo_not_save,slot_features)) : 
		    TRUEP(assq_function(Qsave,slot_features));
	    if (temp);
	    else
		temp = TRUEP(assq_function(Qnote_slot_changes,
			ISVREF(slot_description,(SI_Long)9L)));
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
		note_change_to_block_1(frame,ISVREF(slot_description,
			(SI_Long)2L));
	    else
		note_change_to_dependent_frame_1();
	}
	set_slot_description_value_without_noting(frame,slot_description,
		new_value);
    }
    goto next_loop;
  end_loop:;
    delete_from_instances_specific_to_this_class(old_class,frame);
    add_to_end_of_instances_specific_to_this_class(new_class,frame);
    frame_serial_number_setf_arg = increment_current_frame_serial_number();
    old = ISVREF(frame,(SI_Long)3L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(frame,(SI_Long)3L) = svref_new_value;
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
    if (temp)
	update_images_of_block(frame,Nil,Nil);
    update_representations_of_slot_value(2,frame,Qab_class);
    if (frame_active_qm) {
	method_index = (SI_Long)30L;
	frame_1 = frame;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame_1,(SI_Long)1L),
		(SI_Long)11L),method_index);
	function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
	if (function_qm)
	    return inline_funcall_1(function_qm,frame_1);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INSTALL-DEFERRED-CLASS-DEFINITIONS */
Object install_deferred_class_definitions()
{
    Object name_for_class, class_definition_with_no_name, ab_loop_list_;
    Object ab_loop_desetq_;

    x_note_fn_call(130,2);
    name_for_class = Nil;
    class_definition_with_no_name = Nil;
    ab_loop_list_ = Deferred_class_definitions_alist;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name_for_class = CAR(ab_loop_desetq_);
    class_definition_with_no_name = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    install_class_definition(name_for_class,class_definition_with_no_name,
	    Nil,Nil,T);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_tree_1(Deferred_class_definitions_alist);
    Deferred_class_definitions_alist = Nil;
    return VALUES_1(Deferred_class_definitions_alist);
}

/* DEFER-CLASS-DEFINITION */
Object defer_class_definition(name_for_class,class_definition_with_no_name_yet)
    Object name_for_class, class_definition_with_no_name_yet;
{
    Object temp, superior_class_qm, pair, l, cdr_new_value;

    x_note_fn_call(130,3);
    temp = ISVREF(class_definition_with_no_name_yet,(SI_Long)21L);
    superior_class_qm = FIRST(temp);
    pair = slot_value_cons_1(name_for_class,class_definition_with_no_name_yet);
    l = Deferred_class_definitions_alist;
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    temp = CAR(l);
    if (EQ(CAR(temp),superior_class_qm)) {
	cdr_new_value = slot_value_cons_1(pair,CDR(l));
	return VALUES_1(M_CDR(l) = cdr_new_value);
    }
    l = M_CDR(l);
    goto next_loop;
  end_loop:
    Deferred_class_definitions_alist = slot_value_cons_1(pair,
	    Deferred_class_definitions_alist);
    return VALUES_1(Qnil);
}

/* ADJUST-DIRECT-SUPERIORS-PER-CLASS-CONFLICTS */
Object adjust_direct_superiors_per_class_conflicts(direct_superiors)
    Object direct_superiors;
{
    Object sublist, direct_superior, class_name_conflict, ab_loop_list_;
    Object car_new_value;

    x_note_fn_call(130,4);
    if (Class_name_conflicts) {
	sublist = direct_superiors;
	direct_superior = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	direct_superior = M_CAR(sublist);
	class_name_conflict = Nil;
	ab_loop_list_ = Class_name_conflicts;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	class_name_conflict = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(M_CAR(class_name_conflict),direct_superior) && 
		M_CAR(M_CDR(class_name_conflict))) {
	    car_new_value = M_CAR(M_CDR(class_name_conflict));
	    M_CAR(sublist) = car_new_value;
	}
	goto next_loop_1;
      end_loop_1:;
	sublist = M_CDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

static Object Qjunction_block_class_for_connection;  /* junction-block-class-for-connection */

static Object Qcross_section_pattern_for_class;  /* cross-section-pattern-for-class */

static Object Qcross_section_pattern;  /* cross-section-pattern */

/* DEAL-WITH-JUNCTION-BLOCK-CLASS-DIFFERENCES */
Object deal_with_junction_block_class_differences(new_definition,
	    old_definition,class_name)
    Object new_definition, old_definition, class_name;
{
    Object class_definition, x, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cross_section_pattern_qm, cross_section_pattern_slot_description;
    Object class_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(130,5);
    if ( !TRUEP(ISVREF(new_definition,(SI_Long)32L)) && 
	    ISVREF(old_definition,(SI_Long)32L)) {
	class_definition = 
		lookup_global_or_kb_specific_property_value(ISVREF(old_definition,
		(SI_Long)32L),Class_definition_gkbprop);
	if ( !((SI_Long)0L != (IFIX(ISVREF(class_definition,(SI_Long)5L)) 
		& (SI_Long)262144L))) {
	    x = ISVREF(class_definition,(SI_Long)20L);
	    if (SYMBOLP(x)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = x;
		key_hash_value = SXHASH_SYMBOL_1(x) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = x;
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
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		  next_loop_6:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
	    gensymed_symbol = ACCESS_ONCE(ISVREF(class_definition,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_2 =  !TRUEP(gensymed_symbol);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = ISVREF(class_definition,(SI_Long)21L);
	    temp_2 = EQUAL(temp_1,list_constant);
	}
	else
	    temp_2 = TRUEP(Nil);
	return VALUES_1( !temp_2 ? T : Nil);
    }
    else if ( !TRUEP(ISVREF(old_definition,(SI_Long)32L)) && 
	    ISVREF(new_definition,(SI_Long)32L)) {
	class_definition = 
		lookup_global_or_kb_specific_property_value(ISVREF(new_definition,
		(SI_Long)32L),Class_definition_gkbprop);
	if ( !((SI_Long)0L != (IFIX(ISVREF(class_definition,(SI_Long)5L)) 
		& (SI_Long)262144L))) {
	    x = ISVREF(class_definition,(SI_Long)20L);
	    if (SYMBOLP(x)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = x;
		key_hash_value = SXHASH_SYMBOL_1(x) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_14;
	      end_loop_13:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    gensymed_symbol = x;
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
	      next_loop_15:
		if (level < ab_loop_bind_)
		    goto end_loop_15;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_16:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_17;
	      end_loop_16:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
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
			goto end_7;
		    goto next_loop_19;
		  end_loop_20:
		  end_7:
		    level = level - (SI_Long)1L;
		    goto next_loop_18;
		  end_loop_18:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_22:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
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
			goto end_8;
		    goto next_loop_22;
		  end_loop_23:
		  end_8:
		    level = level - (SI_Long)1L;
		    goto next_loop_21;
		  end_loop_21:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
	    gensymed_symbol = ACCESS_ONCE(ISVREF(class_definition,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    temp_2 =  !TRUEP(gensymed_symbol);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = ISVREF(class_definition,(SI_Long)21L);
	    temp_2 = EQUAL(temp_1,list_constant);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    change_slot_value(3,old_definition,
		    Qjunction_block_class_for_connection,
		    ISVREF(new_definition,(SI_Long)32L));
	    if (SYMBOLP(class_name)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_name;
		key_hash_value = SXHASH_SYMBOL_1(class_name) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_25:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_26:
		if ( !TRUEP(marked))
		    goto end_loop_25;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_26;
	      end_loop_25:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_9;
		goto next_loop_25;
	      end_loop_26:
	      end_9:
		level = level - (SI_Long)1L;
		goto next_loop_24;
	      end_loop_24:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_name;
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
	      next_loop_27:
		if (level < ab_loop_bind_)
		    goto end_loop_27;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_28:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_29:
		if ( !TRUEP(marked))
		    goto end_loop_28;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_29;
	      end_loop_28:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_28;
	      end_loop_29:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_27;
	      end_loop_27:;
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
		  next_loop_30:
		    if (level < ab_loop_bind_)
			goto end_loop_30;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_31:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_32:
		    if ( !TRUEP(marked))
			goto end_loop_31;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_32;
		  end_loop_31:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_11;
		    goto next_loop_31;
		  end_loop_32:
		  end_11:
		    level = level - (SI_Long)1L;
		    goto next_loop_30;
		  end_loop_30:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_33:
		    if (level < ab_loop_bind_)
			goto end_loop_33;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_34:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_35:
		    if ( !TRUEP(marked))
			goto end_loop_34;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_35;
		  end_loop_34:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_12;
		    goto next_loop_34;
		  end_loop_35:
		  end_12:
		    level = level - (SI_Long)1L;
		    goto next_loop_33;
		  end_loop_33:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_name;
		key_hash_value = SXHASH_SYMBOL_1(class_name) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_36:
		if (level < ab_loop_bind_)
		    goto end_loop_36;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_37:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_38:
		if ( !TRUEP(marked))
		    goto end_loop_37;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_38;
	      end_loop_37:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_13;
		goto next_loop_37;
	      end_loop_38:
	      end_13:
		level = level - (SI_Long)1L;
		goto next_loop_36;
	      end_loop_36:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_name;
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
	      next_loop_39:
		if (level < ab_loop_bind_)
		    goto end_loop_39;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_40:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_41:
		if ( !TRUEP(marked))
		    goto end_loop_40;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_41;
	      end_loop_40:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_14;
		goto next_loop_40;
	      end_loop_41:
	      end_14:
		level = level - (SI_Long)1L;
		goto next_loop_39;
	      end_loop_39:;
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
		  next_loop_42:
		    if (level < ab_loop_bind_)
			goto end_loop_42;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_43:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_44:
		    if ( !TRUEP(marked))
			goto end_loop_43;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_44;
		  end_loop_43:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_15;
		    goto next_loop_43;
		  end_loop_44:
		  end_15:
		    level = level - (SI_Long)1L;
		    goto next_loop_42;
		  end_loop_42:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_45:
		    if (level < ab_loop_bind_)
			goto end_loop_45;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_46:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_47:
		    if ( !TRUEP(marked))
			goto end_loop_46;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_47;
		  end_loop_46:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_16;
		    goto next_loop_46;
		  end_loop_47:
		  end_16:
		    level = level - (SI_Long)1L;
		    goto next_loop_45;
		  end_loop_45:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		cross_section_pattern_qm = 
			ISVREF(get_slot_description_of_class_description_function(Qcross_section_pattern_for_class,
			gensymed_symbol,Nil),(SI_Long)6L);
		if (cross_section_pattern_qm);
		else {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = class_name;
		    key_hash_value = SXHASH_SYMBOL_1(class_name) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_48:
		    if (level < ab_loop_bind_)
			goto end_loop_48;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_49:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_50:
		    if ( !TRUEP(marked))
			goto end_loop_49;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_50;
		  end_loop_49:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_17;
		    goto next_loop_49;
		  end_loop_50:
		  end_17:
		    level = level - (SI_Long)1L;
		    goto next_loop_48;
		  end_loop_48:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = class_name;
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
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
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
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
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_1,gensymed_symbol_1);
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
		  next_loop_51:
		    if (level < ab_loop_bind_)
			goto end_loop_51;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_52:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_53:
		    if ( !TRUEP(marked))
			goto end_loop_52;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_53;
		  end_loop_52:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_18;
		    goto next_loop_52;
		  end_loop_53:
		  end_18:
		    level = level - (SI_Long)1L;
		    goto next_loop_51;
		  end_loop_51:;
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
		      next_loop_54:
			if (level < ab_loop_bind_)
			    goto end_loop_54;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_55:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_56:
			if ( !TRUEP(marked))
			    goto end_loop_55;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_56;
		      end_loop_55:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_19;
			goto next_loop_55;
		      end_loop_56:
		      end_19:
			level = level - (SI_Long)1L;
			goto next_loop_54;
		      end_loop_54:;
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
		      next_loop_57:
			if (level < ab_loop_bind_)
			    goto end_loop_57;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_58:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_59:
			if ( !TRUEP(marked))
			    goto end_loop_58;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_59;
		      end_loop_58:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_20;
			goto next_loop_58;
		      end_loop_59:
		      end_20:
			level = level - (SI_Long)1L;
			goto next_loop_57;
		      end_loop_57:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    cross_section_pattern_slot_description = 
			    get_slot_description_of_class_description_function(Qcross_section_pattern,
			    gensymed_symbol,Nil);
		    class_description = 
			    lookup_global_or_kb_specific_property_value(class_name,
			    Class_description_gkbprop);
		    cross_section_pattern_qm = 
			    ISVREF(slot_description_of_most_specific_superior_refining_slot(ISVREF(class_description,
			    (SI_Long)2L),
			    cross_section_pattern_slot_description),
			    (SI_Long)6L);
		}
		update_junction_block_for_connection(class_name,
			old_definition,cross_section_pattern_qm);
		update_connection_subrectangle_structures(class_name,
			cross_section_pattern_qm);
	    }
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_frame_serial_number_before_reading, Qcurrent_frame_serial_number_before_reading);

DEFINE_VARIABLE_WITH_SYMBOL(Reading_ghost_definitions_p, Qreading_ghost_definitions_p);

static Object Qsubstitute_class_and_kb_flags;  /* substitute-class-and-kb-flags */

static Object Qdirect_superiors_of_defined_class;  /* direct-superiors-of-defined-class */

/* INSTALL-CLASS-DEFINITION */
Object install_class_definition(name_for_class,
	    class_definition_with_no_name_yet,new_class_name_qm,
	    differing_slots_qm,class_inheritance_path_needs_refreshing_qm)
    Object name_for_class, class_definition_with_no_name_yet;
    Object new_class_name_qm, differing_slots_qm;
    Object class_inheritance_path_needs_refreshing_qm;
{
    Object sub_class_bit_vector, old_class_definition_qm;
    Object direct_superior_classes_qm, substitute_class_and_kb_flags_qm;
    Object temp_1, old_class_definition_is_frame_p;
    Object definition_classes_are_compatible_qm, current_differing_slots_qm;
    Object add_junction_block_class_to_slot_differences_qm;
    Object denotations_of_differing_slots, list_of_conflicts_for_subclasses_qm;
    Object new_name_qm, potential_definition, ab_loop_list_, gensymed_symbol_3;
    Object xa, ya, direct_superior_classes, superior, ab_loop_list__1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_direct_superiors;
    Object scope_conses, subclass, conflict_for_subclass_qm;
    Object new_class_definition_for_subclass, temp_2, ab_loopvar__3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(130,6);
    if ( !TRUEP(differing_slots_qm)) {
	if (old_format_for_default_overrides_p_function())
	    fix_up_default_overrides_for_5_0(class_definition_with_no_name_yet);
	if (need_to_normalize_message_properties_p_function()) {
	    sub_class_bit_vector = 
		    ISVREF(ISVREF(class_definition_with_no_name_yet,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_definition_class_description,
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
	    normalize_message_properties_for_message_definition(class_definition_with_no_name_yet);
    }
    old_class_definition_qm = 
	    lookup_global_or_kb_specific_property_value(name_for_class,
	    Class_definition_gkbprop);
    direct_superior_classes_qm = ISVREF(class_definition_with_no_name_yet,
	    (SI_Long)21L);
    if (class_inheritance_path_needs_refreshing_qm) {
	reclaim_slot_value(get_lookup_slot_value_given_default(class_definition_with_no_name_yet,
		Qclass_inheritance_path_of_definition,Nil));
	set_non_savable_lookup_slot_value(class_definition_with_no_name_yet,
		Qclass_inheritance_path_of_definition,
		direct_superiors_are_defined_p(direct_superior_classes_qm) 
		? make_class_inheritance_path_for_user_defined_class(Nil,
		direct_superior_classes_qm) : Nil);
    }
    if ( !TRUEP(old_class_definition_qm) &&  
	    !TRUEP(type_specification_for_user_type(name_for_class))) {
	if (Loading_kb_p) {
	    substitute_class_and_kb_flags_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(name_for_class),
		    Qsubstitute_class_and_kb_flags);
	    if (substitute_class_and_kb_flags_qm && FIXNUM_LT(Kb_flags,
		    M_CDR(substitute_class_and_kb_flags_qm))) {
		temp_1 = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(name_for_class),
			Qsubstitute_class_and_kb_flags);
		temp = TRUEP(CAR(temp_1));
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
    if (temp)
	put_name_of_defined_class(class_definition_with_no_name_yet,
		name_for_class,T);
    else {
	old_class_definition_is_frame_p = old_class_definition_qm ? 
		(ATOM(old_class_definition_qm) ? T : Nil) : Qnil;
	if (old_class_definition_is_frame_p) {
	    sub_class_bit_vector = ISVREF(ISVREF(old_class_definition_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Object_definition_class_description,
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
	    if (temp) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(class_definition_with_no_name_yet,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_definition_class_description,
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
		    definition_classes_are_compatible_qm = (SI_Long)0L < 
			    gensymed_symbol ? T : Nil;
		}
		else
		    definition_classes_are_compatible_qm = Nil;
	    }
	    else {
		sub_class_bit_vector = 
			ISVREF(ISVREF(old_class_definition_qm,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_definition_class_description,
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
		if (temp) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(class_definition_with_no_name_yet,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_definition_class_description,
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
			definition_classes_are_compatible_qm = (SI_Long)0L 
				< gensymed_symbol ? T : Nil;
		    }
		    else
			definition_classes_are_compatible_qm = Nil;
		}
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(old_class_definition_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Message_definition_class_description,
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(class_definition_with_no_name_yet,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Message_definition_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    definition_classes_are_compatible_qm = 
				    (SI_Long)0L < gensymed_symbol ? T : Nil;
			}
			else
			    definition_classes_are_compatible_qm = Nil;
		    }
		    else {
			sub_class_bit_vector = 
				ISVREF(ISVREF(old_class_definition_qm,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Class_definition_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    definition_classes_are_compatible_qm =  
				    !TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(class_definition_with_no_name_yet)) 
				    ? T : Nil;
			else
			    definition_classes_are_compatible_qm = Nil;
		    }
		}
	    }
	}
	else
	    definition_classes_are_compatible_qm = Nil;
	if (old_class_definition_is_frame_p) {
	    current_differing_slots_qm = differing_slots_qm;
	    if (current_differing_slots_qm);
	    else
		current_differing_slots_qm = 
			find_differences_in_frames_if_any(4,
			class_definition_with_no_name_yet,
			old_class_definition_qm,Nil,
			definition_classes_are_compatible_qm);
	    sub_class_bit_vector = ISVREF(ISVREF(old_class_definition_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_definition_class_description,
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
	    if (temp) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(class_definition_with_no_name_yet,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Connection_definition_class_description,
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
	    else
		temp = TRUEP(Nil);
	    if (temp ?  !EQ(ISVREF(old_class_definition_qm,(SI_Long)32L),
		    ISVREF(class_definition_with_no_name_yet,
		    (SI_Long)32L)) : TRUEP(Nil)) {
		add_junction_block_class_to_slot_differences_qm = 
			deal_with_junction_block_class_differences(class_definition_with_no_name_yet,
			old_class_definition_qm,name_for_class);
		if (add_junction_block_class_to_slot_differences_qm)
		    current_differing_slots_qm = 
			    nconc2(current_differing_slots_qm,
			    slot_value_cons_1(Qjunction_block_class_for_connection,
			    Nil));
	    }
	    denotations_of_differing_slots = current_differing_slots_qm;
	}
	else
	    denotations_of_differing_slots = Nil;
	list_of_conflicts_for_subclasses_qm = Nil;
	new_name_qm = new_class_name_qm;
	if (new_name_qm);
	else
	    new_name_qm =  !TRUEP(old_class_definition_qm) ||  
		    !TRUEP(old_class_definition_is_frame_p) || 
		    denotations_of_differing_slots ? 
		    name_class_with_variant_name(name_for_class,
		    class_definition_with_no_name_yet) : Nil;
	if (new_name_qm) {
	    potential_definition = Nil;
	    ab_loop_list_ = 
		    lookup_global_or_kb_specific_property_value(name_for_class,
		    Potential_inferior_class_definitions_gkbprop);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    potential_definition = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol_3 = ISVREF(potential_definition,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(potential_definition) ? 
		    EQ(ISVREF(potential_definition,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol_3) ? 
			IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(Current_frame_serial_number_before_reading))
		temp = FIXNUMP(gensymed_symbol_3) ? 
			FIXNUM_LT(Current_frame_serial_number_before_reading,
			gensymed_symbol_3) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_3))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(Current_frame_serial_number_before_reading);
		ya = M_CAR(gensymed_symbol_3);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(Current_frame_serial_number_before_reading),
			    M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	    }
	    if (temp) {
		direct_superior_classes = ISVREF(potential_definition,
			(SI_Long)21L);
		superior = Nil;
		ab_loop_list__1 = direct_superior_classes;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		superior = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		ab_loopvar__2 = slot_value_cons_1(EQ(superior,
			name_for_class) ? new_name_qm : superior,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_1;
	      end_loop_1:
		new_direct_superiors = ab_loopvar_;
		goto end_1;
		new_direct_superiors = Qnil;
	      end_1:;
		temp_1 = potential_definition;
		initialize_slot_description_value(temp_1,
			get_slot_description_of_class_description_function(Qdirect_superiors_of_defined_class,
			ISVREF(potential_definition,(SI_Long)1L),Nil),
			new_direct_superiors);
		reclaim_slot_value(direct_superior_classes);
	    }
	    goto next_loop;
	  end_loop:;
	    if (old_class_definition_qm) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar_ = name_for_class;
		subclass = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  conflict_for_subclass_qm = Nil;
		  ab_loopvar_ = collect_subclasses(ab_loopvar_);
		next_loop_2:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_2;
		  temp_1 = M_CAR(ab_loopvar_);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  subclass = temp_1;
		  conflict_for_subclass_qm = assq_function(subclass,
			  Class_name_conflicts);
		  if (conflict_for_subclass_qm) {
		      new_class_definition_for_subclass = 
			      FOURTH(conflict_for_subclass_qm);
		      direct_superior_classes = 
			      ISVREF(new_class_definition_for_subclass,
			      (SI_Long)21L);
		      if (THIRD(conflict_for_subclass_qm) &&  
			      !TRUEP(SECOND(conflict_for_subclass_qm))) {
			  temp_2 = name_class_with_variant_name(subclass,
				  new_class_definition_for_subclass);
			  M_SECOND(conflict_for_subclass_qm) = temp_2;
		      }
		      if (memq_function(name_for_class,
			      direct_superior_classes)) {
			  superior = Nil;
			  ab_loop_list_ = direct_superior_classes;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			  ab_loopvar__3 = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_3;
			  superior = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  ab_loopvar__3 = slot_value_cons_1(EQ(superior,
				  name_for_class) ? new_name_qm : superior,
				  Nil);
			  if (ab_loopvar__2)
			      M_CDR(ab_loopvar__2) = ab_loopvar__3;
			  else
			      ab_loopvar__1 = ab_loopvar__3;
			  ab_loopvar__2 = ab_loopvar__3;
			  goto next_loop_3;
			end_loop_3:
			  new_direct_superiors = ab_loopvar__1;
			  goto end_2;
			  new_direct_superiors = Qnil;
			end_2:;
			  initialize_slot_description_value(new_class_definition_for_subclass,
				  get_slot_description_of_class_description_function(Qdirect_superiors_of_defined_class,
				  ISVREF(new_class_definition_for_subclass,
				  (SI_Long)1L),Nil),new_direct_superiors);
			  reclaim_slot_value(direct_superior_classes);
		      }
		      if (THIRD(conflict_for_subclass_qm)) {
			  temp_2 = 
				  slot_value_cons_1(Qdirect_superiors_of_defined_class,
				  FIFTH(conflict_for_subclass_qm));
			  M_FIFTH(conflict_for_subclass_qm) = temp_2;
		      }
		      Class_name_conflicts = 
			      delete_slot_value_element_1(conflict_for_subclass_qm,
			      Class_name_conflicts);
		      list_of_conflicts_for_subclasses_qm = 
			      slot_value_cons_1(conflict_for_subclass_qm,
			      list_of_conflicts_for_subclasses_qm);
		  }
		  goto next_loop_2;
		end_loop_2:;
		POP_SPECIAL();
	    }
	}
	record_class_name_conflict(6,name_for_class,new_name_qm,
		old_class_definition_is_frame_p ? old_class_definition_qm :
		 Nil,class_definition_with_no_name_yet,
		denotations_of_differing_slots,Reading_ghost_definitions_p);
	Class_name_conflicts = nconc2(list_of_conflicts_for_subclasses_qm,
		Class_name_conflicts);
    }
    return update_indexed_attribute_properties(class_definition_with_no_name_yet,
	    Nil,Nil,Nil);
}

static Object string_constant;     /* "-FROM-" */

/* NAME-CLASS-WITH-VARIANT-NAME */
Object name_class_with_variant_name(intended_name,
	    class_definition_with_no_name_yet)
    Object intended_name, class_definition_with_no_name_yet;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(130,7);
    sub_class_bit_vector = ISVREF(ISVREF(class_definition_with_no_name_yet,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Connection_definition_class_description,(SI_Long)18L));
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
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(class_definition_with_no_name_yet,
		    Qjunction_block_class_for_connection);
	SVREF(class_definition_with_no_name_yet,FIX((SI_Long)32L)) = Nil;
    }
    return put_name_of_defined_class(class_definition_with_no_name_yet,
	    make_new_name_for_frame(3,intended_name,string_constant,
	    get_simple_name_of_kb_being_read()),T);
}

DEFINE_VARIABLE_WITH_SYMBOL(Name_of_kb_being_read, Qname_of_kb_being_read);

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* GET-SIMPLE-NAME-OF-KB-BEING-READ */
Object get_simple_name_of_kb_being_read()
{
    x_note_fn_call(130,8);
    if ( !TRUEP(string_eq_w(Name_of_kb_being_read,array_constant)))
	return VALUES_1(Name_of_kb_being_read);
    else
	return VALUES_1(array_constant_1);
}

static Object Qpreprocess_class_name_conflicts_with_move_attribute_facility;  /* preprocess-class-name-conflicts-with-move-attribute-facility */

static Object Qclass_specific_attributes;  /* class-specific-attributes */

static Object Qcar_eq;             /* car-eq */

static Object Qmove_attribute;     /* move-attribute */

static Object Qcadr_eq;            /* cadr-eq */

/* PREPROCESS-CLASS-NAME-CONFLICTS-WITH-MOVE-ATTRIBUTE-FACILITY */
Object preprocess_class_name_conflicts_with_move_attribute_facility()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object top_down_class_name_conflicts, basis_class, new_class;
    Object basis_definition, new_definition, differing_slots, ab_loop_list_;
    Object ab_loop_desetq_, temp_1, basis_class_attributes;
    Object new_class_attributes, new_class_attribute, ab_loop_list__1;
    Object attribute_name, scope_conses, ab_loopvar_, basis_subclass;
    Object basis_class_definition, cons_holding_attribute_description_qm;
    Object override_on_attribute_qm;
    Object cons_holding_basis_subclass_name_conflict_qm, new_subclass_qm;
    Object new_subclass_definition, basis_class_attribute, new_subclass;
    Object cons_holding_new_subclass_name_conflict_qm, basis_subclass_qm;
    Object basis_subclass_definition;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,9);
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
	  SVREF(temp,svref_arg_2) = 
		  Qpreprocess_class_name_conflicts_with_move_attribute_facility;
      }
      top_down_class_name_conflicts = 
	      nreverse(copy_list_using_slot_value_conses_1(Class_name_conflicts));
      basis_class = Nil;
      new_class = Nil;
      basis_definition = Nil;
      new_definition = Nil;
      differing_slots = Nil;
      ab_loop_list_ = top_down_class_name_conflicts;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      basis_class = CAR(ab_loop_desetq_);
      temp_1 = CDR(ab_loop_desetq_);
      new_class = CAR(temp_1);
      temp_1 = CDR(ab_loop_desetq_);
      temp_1 = CDR(temp_1);
      basis_definition = CAR(temp_1);
      temp_1 = CDR(ab_loop_desetq_);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      new_definition = CAR(temp_1);
      temp_1 = CDR(ab_loop_desetq_);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      differing_slots = CAR(temp_1);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (basis_class && new_class && basis_definition && new_definition 
	      && memq_function(Qclass_specific_attributes,differing_slots)) {
	  basis_class_attributes = ISVREF(basis_definition,(SI_Long)22L);
	  new_class_attributes = copy_for_slot_value(ISVREF(new_definition,
		  (SI_Long)22L));
	  new_class_attribute = Nil;
	  ab_loop_list__1 = new_class_attributes;
	  attribute_name = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  new_class_attribute = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  attribute_name = CAR(new_class_attribute);
	  if ( !(member(4,attribute_name,basis_class_attributes,Ktest,
		  Qcar_eq) || 
		  class_has_override_on_pretty_slot_name_p(basis_definition,
		  attribute_name))) {
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar_ = basis_class;
	      basis_subclass = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		basis_class_definition = Nil;
		cons_holding_attribute_description_qm = Nil;
		override_on_attribute_qm = Nil;
		ab_loopvar_ = collect_subclasses(ab_loopvar_);
	      next_loop_2:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_2;
		temp_1 = M_CAR(ab_loopvar_);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		basis_subclass = temp_1;
		basis_class_definition = 
			lookup_global_or_kb_specific_property_value(basis_subclass,
			Class_definition_gkbprop);
		cons_holding_attribute_description_qm =  
			!EQ(basis_subclass,basis_class) ? member(4,
			attribute_name,ISVREF(basis_class_definition,
			(SI_Long)22L),Ktest,Qcar_eq) : Nil;
		override_on_attribute_qm =  !EQ(basis_subclass,
			basis_class) ? 
			class_has_override_on_pretty_slot_name_p(basis_class_definition,
			attribute_name) : Nil;
		if (cons_holding_attribute_description_qm || 
			override_on_attribute_qm) {
		    if (cons_holding_attribute_description_qm &&  
			    !TRUEP(override_on_attribute_qm)) {
			temp_1 = M_CAR(cons_holding_attribute_description_qm);
			temp_2 = EQUAL(temp_1,new_class_attribute);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			cons_holding_basis_subclass_name_conflict_qm = 
				member(4,basis_subclass,
				top_down_class_name_conflicts,Ktest,Qcar_eq);
			if (cons_holding_basis_subclass_name_conflict_qm) {
			    temp_1 = 
				    M_CAR(cons_holding_basis_subclass_name_conflict_qm);
			    new_subclass_qm = SECOND(temp_1);
			}
			else
			    new_subclass_qm = Nil;
			if (new_subclass_qm) {
			    new_subclass_definition = 
				    lookup_global_or_kb_specific_property_value(new_subclass_qm,
				    Class_definition_gkbprop);
			    if ( !(member(4,attribute_name,
				    ISVREF(new_subclass_definition,
				    (SI_Long)22L),Ktest,Qcar_eq) || 
				    class_has_override_on_pretty_slot_name_p(new_subclass_definition,
				    attribute_name)))
				put_change(new_definition,
					slot_value_list_3(Qmove_attribute,
					attribute_name,new_subclass_qm),Nil);
			}
		    }
		    goto end_loop_2;
		}
		goto next_loop_2;
	      end_loop_2:;
	      POP_SPECIAL();
	  }
	  goto next_loop_1;
	end_loop_1:;
	  basis_class_attribute = Nil;
	  ab_loop_list__1 = basis_class_attributes;
	  attribute_name = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_3;
	  basis_class_attribute = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  attribute_name = CAR(basis_class_attribute);
	  if ( !(member(4,attribute_name,ISVREF(new_definition,
		  (SI_Long)22L),Ktest,Qcar_eq) || 
		  class_has_override_on_pretty_slot_name_p(new_definition,
		  attribute_name))) {
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar_ = new_class;
	      new_subclass = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		new_subclass_definition = Nil;
		cons_holding_attribute_description_qm = Nil;
		override_on_attribute_qm = Nil;
		ab_loopvar_ = collect_subclasses(ab_loopvar_);
	      next_loop_4:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_4;
		temp_1 = M_CAR(ab_loopvar_);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		new_subclass = temp_1;
		new_subclass_definition = 
			lookup_global_or_kb_specific_property_value(new_subclass,
			Class_definition_gkbprop);
		cons_holding_attribute_description_qm =  !EQ(new_subclass,
			new_class) ? member(4,attribute_name,
			ISVREF(new_subclass_definition,(SI_Long)22L),Ktest,
			Qcar_eq) : Nil;
		override_on_attribute_qm =  !EQ(new_subclass,new_class) ? 
			class_has_override_on_pretty_slot_name_p(new_subclass_definition,
			attribute_name) : Nil;
		if (cons_holding_attribute_description_qm || 
			override_on_attribute_qm) {
		    if (cons_holding_attribute_description_qm &&  
			    !TRUEP(override_on_attribute_qm)) {
			temp_1 = M_CAR(cons_holding_attribute_description_qm);
			temp_2 = EQUAL(temp_1,basis_class_attribute);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			cons_holding_new_subclass_name_conflict_qm = 
				member(4,new_subclass,
				top_down_class_name_conflicts,Ktest,Qcadr_eq);
			basis_subclass_qm = 
				cons_holding_new_subclass_name_conflict_qm 
				? 
				M_CAR(M_CAR(cons_holding_new_subclass_name_conflict_qm)) 
				: Nil;
			if (basis_subclass_qm) {
			    basis_subclass_definition = 
				    lookup_global_or_kb_specific_property_value(basis_subclass_qm,
				    Class_definition_gkbprop);
			    if ( !(member(4,attribute_name,
				    ISVREF(basis_subclass_definition,
				    (SI_Long)22L),Ktest,Qcar_eq) || 
				    class_has_override_on_pretty_slot_name_p(basis_subclass_definition,
				    attribute_name)))
				put_change(lookup_global_or_kb_specific_property_value(new_subclass,
					Class_definition_gkbprop),
					slot_value_list_3(Qmove_attribute,
					attribute_name,new_class),Nil);
			}
		    }
		    goto end_loop_4;
		}
		goto next_loop_4;
	      end_loop_4:;
	      POP_SPECIAL();
	  }
	  goto next_loop_3;
	end_loop_3:;
	  reclaim_slot_value(new_class_attributes);
      }
      goto next_loop;
    end_loop:;
      result = reclaim_slot_value_list_1(top_down_class_name_conflicts);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Name_text_string_for_kb_being_read, Qname_text_string_for_kb_being_read);

static Object Qdeal_with_class_name_conflicts;  /* deal-with-class-name-conflicts */

static Object Qname_of_defined_class;  /* name-of-defined-class */

static Object string_constant_1;   /* "The merged-in KB ~S contains ~D class definition(s) with subworkspaces ~
				    *                  that have been verified to be the same as established (existing) ~
				    *                  definitions with subworkspaces, except that the corresponding ~
				    *                  subworkspaces have not been verified to be equivalent.  These ~
				    *                  new definitions, with their subworkspaces, have been deleted."
				    */

/* DEAL-WITH-CLASS-NAME-CONFLICTS */
Object deal_with_class_name_conflicts(auto_merge_case_qm,new_algorithm_qm)
    Object auto_merge_case_qm, new_algorithm_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object number_of_conflicts, number_of_subworkspaces_deleted;
    Object ghost_definitions_to_restore, deferred_class_name_conflicts;
    Object workspace_coordinate_information, class_name_conflict;
    Object ab_loop_list_, class_1, new_name_qm, old_class_definition_qm;
    Object new_class_definition, denotations_of_differing_slots;
    Object ghost_definition_p, temp_1, gensymed_symbol, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_3, entry_hash, tail, head;
    Object new_cons, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector, scope_conses, ab_loopvar_;
    Object subclass, ab_loop_it_, x;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,10);
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
	  SVREF(temp,svref_arg_2) = Qdeal_with_class_name_conflicts;
      }
      if (auto_merge_case_qm)
	  preprocess_class_name_conflicts_with_move_attribute_facility();
      number_of_conflicts = FIX((SI_Long)0L);
      number_of_subworkspaces_deleted = FIX((SI_Long)0L);
      ghost_definitions_to_restore = Nil;
      deferred_class_name_conflicts = Nil;
      workspace_coordinate_information = Nil;
      class_name_conflict = Nil;
      ab_loop_list_ = Class_name_conflicts;
      class_1 = Nil;
      new_name_qm = Nil;
      old_class_definition_qm = Nil;
      new_class_definition = Nil;
      denotations_of_differing_slots = Nil;
      ghost_definition_p = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      class_name_conflict = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      class_1 = CAR(class_name_conflict);
      temp_1 = CDR(class_name_conflict);
      new_name_qm = CAR(temp_1);
      temp_1 = CDR(class_name_conflict);
      temp_1 = CDR(temp_1);
      old_class_definition_qm = CAR(temp_1);
      temp_1 = CDR(class_name_conflict);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      new_class_definition = CAR(temp_1);
      temp_1 = CDR(class_name_conflict);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      denotations_of_differing_slots = CAR(temp_1);
      temp_1 = CDR(class_name_conflict);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      temp_1 = CDR(temp_1);
      ghost_definition_p = CAR(temp_1);
      if (ghost_definition_p) {
	  gensymed_symbol = ACCESS_ONCE(ISVREF(new_class_definition,
		  (SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  temp_2 = TRUEP(gensymed_symbol);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2)
	  workspace_coordinate_information = 
		  fix_definitions_saved_as_ghost_definitions(new_class_definition,
		  workspace_coordinate_information,new_algorithm_qm);
      else if ( !TRUEP(new_name_qm) &&  !TRUEP(old_class_definition_qm) && 
	       !TRUEP(denotations_of_differing_slots) && ghost_definition_p) {
	  skip_list = CDR(Symbol_properties_table);
	  key_value = class_1;
	  key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	  temp_3 = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_3,temp_1);
	  MVS_2(result,succ,marked);
	next_loop_3:
	  if ( !TRUEP(marked))
	      goto end_loop_2;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_3 = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_3,temp_1);
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = class_1;
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
		  temp = Available_lookup_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_lookup_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
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
	      gensymed_symbol = set_skip_list_entry(temp_3,
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
	next_loop_4:
	  if (level < ab_loop_bind_)
	      goto end_loop_4;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_5:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_3 = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_3,temp_1);
	  MVS_2(result,succ,marked);
	next_loop_6:
	  if ( !TRUEP(marked))
	      goto end_loop_5;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_3 = ATOMIC_REF_OBJECT(reference);
	  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_3,temp_1);
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
	    next_loop_7:
	      if (level < ab_loop_bind_)
		  goto end_loop_7;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_8:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	    next_loop_9:
	      if ( !TRUEP(marked))
		  goto end_loop_8;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_11:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	    next_loop_12:
	      if ( !TRUEP(marked))
		  goto end_loop_11;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
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
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_3 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
	  temp_2 = temp_2 ? 
		  TRUEP(connection_class_is_instantiated_p(class_1)) : 
		  TRUEP(instantiated_class_p(class_1));
	  if (temp_2);
	  else {
	      scope_conses = Scope_conses;
	      ab_loopvar_ = Nil;
	      ab_loopvar_ = class_1;
	      subclass = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		      0);
		ab_loop_it_ = Nil;
		ab_loopvar_ = collect_subclasses(ab_loopvar_);
	      next_loop_13:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_13;
		temp_1 = M_CAR(ab_loopvar_);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		subclass = temp_1;
		gensymed_symbol = 
			ACCESS_ONCE(ISVREF(lookup_global_or_kb_specific_property_value(subclass,
			Class_definition_gkbprop),(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		ab_loop_it_ = gensymed_symbol;
		if (ab_loop_it_) {
		    temp_2 = TRUEP(ab_loop_it_);
		    goto end_5;
		}
		goto next_loop_13;
	      end_loop_13:
		temp_2 = TRUEP(Qnil);
	      end_5:;
	      POP_SPECIAL();
	  }
	  if (temp_2) {
	      if ( !((SI_Long)0L != (IFIX(ISVREF(new_class_definition,
		      (SI_Long)5L)) & (SI_Long)262144L))) {
		  x = ISVREF(new_class_definition,(SI_Long)20L);
		  if (SYMBOLP(x)) {
		      skip_list = CDR(Symbol_properties_table);
		      key_value = x;
		      key_hash_value = SXHASH_SYMBOL_1(x) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_14:
		      if (level < ab_loop_bind_)
			  goto end_loop_14;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_15:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_16:
		      if ( !TRUEP(marked))
			  goto end_loop_15;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_16;
		    end_loop_15:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_6;
		      goto next_loop_15;
		    end_loop_16:
		    end_6:
		      level = level - (SI_Long)1L;
		      goto next_loop_14;
		    end_loop_14:;
		      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol)) {
			  gensymed_symbol = x;
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
			      temp = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(temp,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  temp = Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp,svref_arg_2) = Nil;
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
			      temp = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(temp,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  temp = Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(temp,svref_arg_2) = Nil;
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
			  gensymed_symbol = set_skip_list_entry(temp_3,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol,temp_1,gensymed_symbol_1);
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
		    next_loop_17:
		      if (level < ab_loop_bind_)
			  goto end_loop_17;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_18:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_19:
		      if ( !TRUEP(marked))
			  goto end_loop_18;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_19;
		    end_loop_18:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_7;
		      goto next_loop_18;
		    end_loop_19:
		    end_7:
		      level = level - (SI_Long)1L;
		      goto next_loop_17;
		    end_loop_17:;
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
			next_loop_20:
			  if (level < ab_loop_bind_)
			      goto end_loop_20;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_21:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_22:
			  if ( !TRUEP(marked))
			      goto end_loop_21;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_22;
			end_loop_21:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_8;
			  goto next_loop_21;
			end_loop_22:
			end_8:
			  level = level - (SI_Long)1L;
			  goto next_loop_20;
			end_loop_20:;
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
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
			next_loop_23:
			  if (level < ab_loop_bind_)
			      goto end_loop_23;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_24:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_25:
			  if ( !TRUEP(marked))
			      goto end_loop_24;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_3 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_3,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_25;
			end_loop_24:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_9;
			  goto next_loop_24;
			end_loop_25:
			end_9:
			  level = level - (SI_Long)1L;
			  goto next_loop_23;
			end_loop_23:;
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
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
		  gensymed_symbol = 
			  ACCESS_ONCE(ISVREF(new_class_definition,
			  (SI_Long)14L));
		  gensymed_symbol = gensymed_symbol ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) 
			  : Nil;
		  temp_2 =  !TRUEP(gensymed_symbol);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  temp_1 = ISVREF(new_class_definition,(SI_Long)21L);
		  temp_2 = EQUAL(temp_1,list_constant);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ( !temp_2)
		  ghost_definitions_to_restore = 
			  gensym_cons_1(new_class_definition,
			  ghost_definitions_to_restore);
	  }
	  else
	      delete_frame(new_class_definition);
      }
      else {
	  if (ghost_definition_p && new_name_qm) {
	      if (SYMBOLP(new_name_qm)) {
		  skip_list = CDR(Symbol_properties_table);
		  key_value = new_name_qm;
		  key_hash_value = SXHASH_SYMBOL_1(new_name_qm) & 
			  IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)31L;
		  ab_loop_bind_ = bottom_level;
		next_loop_26:
		  if (level < ab_loop_bind_)
		      goto end_loop_26;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_27:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_28:
		  if ( !TRUEP(marked))
		      goto end_loop_27;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_28;
		end_loop_27:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_10;
		  goto next_loop_27;
		end_loop_28:
		end_10:
		  level = level - (SI_Long)1L;
		  goto next_loop_26;
		end_loop_26:;
		  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if ( !TRUEP(gensymed_symbol)) {
		      gensymed_symbol = new_name_qm;
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
			  temp = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
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
			  temp = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
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
		      gensymed_symbol = set_skip_list_entry(temp_3,
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
		next_loop_29:
		  if (level < ab_loop_bind_)
		      goto end_loop_29;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_30:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_31:
		  if ( !TRUEP(marked))
		      goto end_loop_30;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_31;
		end_loop_30:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_11;
		  goto next_loop_30;
		end_loop_31:
		end_11:
		  level = level - (SI_Long)1L;
		  goto next_loop_29;
		end_loop_29:;
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
		    next_loop_32:
		      if (level < ab_loop_bind_)
			  goto end_loop_32;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_33:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_34:
		      if ( !TRUEP(marked))
			  goto end_loop_33;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_34;
		    end_loop_33:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_12;
		      goto next_loop_33;
		    end_loop_34:
		    end_12:
		      level = level - (SI_Long)1L;
		      goto next_loop_32;
		    end_loop_32:;
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
		    next_loop_35:
		      if (level < ab_loop_bind_)
			  goto end_loop_35;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_36:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_37:
		      if ( !TRUEP(marked))
			  goto end_loop_36;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_37;
		    end_loop_36:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_13;
		      goto next_loop_36;
		    end_loop_37:
		    end_13:
		      level = level - (SI_Long)1L;
		      goto next_loop_35;
		    end_loop_35:;
		      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (resulting_value);
		      else
			  resulting_value = Nil;
		  }
		  temp_2 = TRUEP(resulting_value);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      temp_2 =  !temp_2;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      delete_frame(new_class_definition);
	  else {
	      skip_list = CDR(Symbol_properties_table);
	      key_value = class_1;
	      key_hash_value = SXHASH_SYMBOL_1(class_1) & 
		      IFIX(Most_positive_fixnum);
	      bottom_level = (SI_Long)0L;
	      marked = Nil;
	      pred = M_CAR(skip_list);
	      curr = Nil;
	      succ = Nil;
	      level = (SI_Long)31L;
	      ab_loop_bind_ = bottom_level;
	    next_loop_38:
	      if (level < ab_loop_bind_)
		  goto end_loop_38;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_39:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	    next_loop_40:
	      if ( !TRUEP(marked))
		  goto end_loop_39;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	      goto next_loop_40;
	    end_loop_39:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_14;
	      goto next_loop_39;
	    end_loop_40:
	    end_14:
	      level = level - (SI_Long)1L;
	      goto next_loop_38;
	    end_loop_38:;
	      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  gensymed_symbol = class_1;
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
		      temp = Available_lookup_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp = Available_lookup_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = Nil;
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
		      temp = Available_lookup_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp = Available_lookup_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = Nil;
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
		  gensymed_symbol = set_skip_list_entry(temp_3,
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
	    next_loop_41:
	      if (level < ab_loop_bind_)
		  goto end_loop_41;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_42:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	    next_loop_43:
	      if ( !TRUEP(marked))
		  goto end_loop_42;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_3 = ATOMIC_REF_OBJECT(reference);
	      temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_3,temp_1);
	      MVS_2(result,succ,marked);
	      goto next_loop_43;
	    end_loop_42:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_15;
	      goto next_loop_42;
	    end_loop_43:
	    end_15:
	      level = level - (SI_Long)1L;
	      goto next_loop_41;
	    end_loop_41:;
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
		next_loop_44:
		  if (level < ab_loop_bind_)
		      goto end_loop_44;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_45:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_46:
		  if ( !TRUEP(marked))
		      goto end_loop_45;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_46;
		end_loop_45:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_16;
		  goto next_loop_45;
		end_loop_46:
		end_16:
		  level = level - (SI_Long)1L;
		  goto next_loop_44;
		end_loop_44:;
		  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		next_loop_47:
		  if (level < ab_loop_bind_)
		      goto end_loop_47;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_48:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_49:
		  if ( !TRUEP(marked))
		      goto end_loop_48;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_49;
		end_loop_48:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_17;
		  goto next_loop_48;
		end_loop_49:
		end_17:
		  level = level - (SI_Long)1L;
		  goto next_loop_47;
		end_loop_47:;
		  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Default_junction_class_description,
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
		      gensymed_symbol_4 = gensymed_symbol_4 << 
			      gensymed_symbol_5;
		      gensymed_symbol_3 = gensymed_symbol_3 & 
			      gensymed_symbol_4;
		      temp_2 = (SI_Long)0L < gensymed_symbol_3;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  skip_list = CDR(Symbol_properties_table);
		  key_value = new_name_qm;
		  key_hash_value = SXHASH_SYMBOL_1(new_name_qm) & 
			  IFIX(Most_positive_fixnum);
		  bottom_level = (SI_Long)0L;
		  marked = Nil;
		  pred = M_CAR(skip_list);
		  curr = Nil;
		  succ = Nil;
		  level = (SI_Long)31L;
		  ab_loop_bind_ = bottom_level;
		next_loop_50:
		  if (level < ab_loop_bind_)
		      goto end_loop_50;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_51:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_52:
		  if ( !TRUEP(marked))
		      goto end_loop_51;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_52;
		end_loop_51:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_18;
		  goto next_loop_51;
		end_loop_52:
		end_18:
		  level = level - (SI_Long)1L;
		  goto next_loop_50;
		end_loop_50:;
		  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if ( !TRUEP(gensymed_symbol)) {
		      gensymed_symbol = new_name_qm;
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
			  temp = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
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
			  temp = Available_lookup_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_lookup_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
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
		      gensymed_symbol = set_skip_list_entry(temp_3,
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
		next_loop_53:
		  if (level < ab_loop_bind_)
		      goto end_loop_53;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_54:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		next_loop_55:
		  if ( !TRUEP(marked))
		      goto end_loop_54;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_3 = ATOMIC_REF_OBJECT(reference);
		  temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_3,temp_1);
		  MVS_2(result,succ,marked);
		  goto next_loop_55;
		end_loop_54:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
		      pred = curr;
		      curr = succ;
		  }
		  else
		      goto end_19;
		  goto next_loop_54;
		end_loop_55:
		end_19:
		  level = level - (SI_Long)1L;
		  goto next_loop_53;
		end_loop_53:;
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
		    next_loop_56:
		      if (level < ab_loop_bind_)
			  goto end_loop_56;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_57:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_58:
		      if ( !TRUEP(marked))
			  goto end_loop_57;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_58;
		    end_loop_57:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_20;
		      goto next_loop_57;
		    end_loop_58:
		    end_20:
		      level = level - (SI_Long)1L;
		      goto next_loop_56;
		    end_loop_56:;
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
		    next_loop_59:
		      if (level < ab_loop_bind_)
			  goto end_loop_59;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_60:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_61:
		      if ( !TRUEP(marked))
			  goto end_loop_60;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_3 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_3,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_61;
		    end_loop_60:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_21;
		      goto next_loop_60;
		    end_loop_61:
		    end_21:
		      level = level - (SI_Long)1L;
		      goto next_loop_59;
		    end_loop_59:;
		      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (resulting_value);
		      else
			  resulting_value = Nil;
		  }
		  gensymed_symbol = resulting_value;
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Default_junction_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol_3 = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_4 = (SI_Long)1L;
			  gensymed_symbol_5 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_4 = gensymed_symbol_4 << 
				  gensymed_symbol_5;
			  gensymed_symbol_3 = gensymed_symbol_3 & 
				  gensymed_symbol_4;
			  temp_2 = (SI_Long)0L < gensymed_symbol_3;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ((temp_2 ?  !TRUEP(instantiated_class_p(class_1)) : 
		      TRUEP(Nil)) ?  !((SI_Long)0L != 
		      (IFIX(ISVREF(old_class_definition_qm,(SI_Long)5L)) & 
		      (SI_Long)262144L)) : TRUEP(Nil)) {
		  gensymed_symbol = 
			  ACCESS_ONCE(ISVREF(old_class_definition_qm,
			  (SI_Long)14L));
		  gensymed_symbol = gensymed_symbol ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) 
			  : Nil;
		  temp_2 =  !TRUEP(gensymed_symbol);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  delete_frame(old_class_definition_qm);
		  change_slot_value(3,new_class_definition,
			  Qname_of_defined_class,class_1);
	      }
	      else {
		  temp_2 =  !TRUEP(new_name_qm);
		  if (temp_2);
		  else {
		      temp_1 = ISVREF(new_class_definition,(SI_Long)8L);
		      if (CAR(temp_1)) {
			  gensymed_symbol = 
				  ACCESS_ONCE(ISVREF(new_class_definition,
				  (SI_Long)14L));
			  gensymed_symbol = gensymed_symbol ? 
				  ACCESS_ONCE(ISVREF(gensymed_symbol,
				  (SI_Long)5L)) : Nil;
			  temp_2 =  !TRUEP(gensymed_symbol);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  if (temp_2) {
		      if (ISVREF(new_class_definition,(SI_Long)18L)) {
			  if ( !TRUEP(ISVREF(old_class_definition_qm,
				  (SI_Long)18L))) {
			      transfer_subworkspace_if_any(new_class_definition,
				      old_class_definition_qm);
			      delete_block_after_reading_kb(new_class_definition);
			  }
			  else {
			      delete_block_after_reading_kb(new_class_definition);
			      number_of_subworkspaces_deleted = 
				      FIXNUM_ADD1(number_of_subworkspaces_deleted);
			  }
		      }
		      else
			  delete_block_after_reading_kb(new_class_definition);
		  }
		  else {
		      if (ghost_definition_p) {
			  if ( !((SI_Long)0L != 
				  (IFIX(ISVREF(new_class_definition,
				  (SI_Long)5L)) & (SI_Long)262144L))) {
			      x = ISVREF(new_class_definition,(SI_Long)20L);
			      if (SYMBOLP(x)) {
				  skip_list = CDR(Symbol_properties_table);
				  key_value = x;
				  key_hash_value = SXHASH_SYMBOL_1(x) & 
					  IFIX(Most_positive_fixnum);
				  bottom_level = (SI_Long)0L;
				  marked = Nil;
				  pred = M_CAR(skip_list);
				  curr = Nil;
				  succ = Nil;
				  level = (SI_Long)31L;
				  ab_loop_bind_ = bottom_level;
				next_loop_62:
				  if (level < ab_loop_bind_)
				      goto end_loop_62;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_63:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_3 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_3,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_64:
				  if ( !TRUEP(marked))
				      goto end_loop_63;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_3 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_3,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_64;
				end_loop_63:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_22;
				  goto next_loop_63;
				end_loop_64:
				end_22:
				  level = level - (SI_Long)1L;
				  goto next_loop_62;
				end_loop_62:;
				  gensymed_symbol = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
				  if ( !TRUEP(gensymed_symbol)) {
				      gensymed_symbol = x;
				      temp_3 = Symbol_properties_table;
				      temp_1 = 
					      FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					      & IFIX(Most_positive_fixnum));
				      tail = 
					      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					      Nil);
				      head = 
					      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					      tail);
				      new_cons = 
					      ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp = 
						  Available_lookup_conses_vector;
					  svref_arg_2 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(temp,svref_arg_2) = 
						  svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp = 
						      Available_lookup_conses_tail_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      SVREF(temp,svref_arg_2) = Nil;
					  }
					  gensymed_symbol_1 = new_cons;
				      }
				      else
					  gensymed_symbol_1 = Nil;
				      if ( !TRUEP(gensymed_symbol_1))
					  gensymed_symbol_1 = 
						  replenish_lookup_cons_pool();
				      M_CAR(gensymed_symbol_1) = 
					      Qsymbol_properties_hash_table;
				      new_cons = 
					      ISVREF(Available_lookup_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp = 
						  Available_lookup_conses_vector;
					  svref_arg_2 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(temp,svref_arg_2) = 
						  svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_lookup_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp = 
						      Available_lookup_conses_tail_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      SVREF(temp,svref_arg_2) = Nil;
					  }
					  gensymed_symbol_2 = new_cons;
				      }
				      else
					  gensymed_symbol_2 = Nil;
				      if ( !TRUEP(gensymed_symbol_2))
					  gensymed_symbol_2 = 
						  replenish_lookup_cons_pool();
				      M_CAR(gensymed_symbol_2) = head;
				      M_CDR(gensymed_symbol_2) = tail;
				      inline_note_allocate_cons(gensymed_symbol_2,
					      Qlookup);
				      M_CDR(gensymed_symbol_1) = 
					      gensymed_symbol_2;
				      inline_note_allocate_cons(gensymed_symbol_1,
					      Qlookup);
				      gensymed_symbol = 
					      set_skip_list_entry(temp_3,
					      FIX((SI_Long)31L),Qeq,Nil,T,
					      gensymed_symbol,temp_1,
					      gensymed_symbol_1);
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
				next_loop_65:
				  if (level < ab_loop_bind_)
				      goto end_loop_65;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				next_loop_66:
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_3 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_3,temp_1);
				  MVS_2(result,succ,marked);
				next_loop_67:
				  if ( !TRUEP(marked))
				      goto end_loop_66;
				  curr = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					  (SI_Long)0L),level));
				  reference = ISVREF(ISVREF(curr,
					  (SI_Long)0L),level);
				  temp_3 = ATOMIC_REF_OBJECT(reference);
				  temp_1 = (SI_Long)355L == 
					  ATOMIC_REF_STAMP(reference) ? T :
					   Nil;
				  result = VALUES_2(temp_3,temp_1);
				  MVS_2(result,succ,marked);
				  goto next_loop_67;
				end_loop_66:
				  entry_hash = ISVREF(curr,(SI_Long)1L);
				  if (IFIX(entry_hash) < key_hash_value || 
					  IFIX(entry_hash) == 
					  key_hash_value &&  !EQ(key_value,
					  ISVREF(curr,(SI_Long)2L))) {
				      pred = curr;
				      curr = succ;
				  }
				  else
				      goto end_23;
				  goto next_loop_66;
				end_loop_67:
				end_23:
				  level = level - (SI_Long)1L;
				  goto next_loop_65;
				end_loop_65:;
				  kb_properties = IFIX(ISVREF(curr,
					  (SI_Long)1L)) == key_hash_value ?
					   (EQ(key_value,ISVREF(curr,
					  (SI_Long)2L)) ? ISVREF(curr,
					  (SI_Long)3L) : Nil) : Nil;
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
				    next_loop_68:
				      if (level < ab_loop_bind_)
					  goto end_loop_68;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_69:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_3 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_3,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_70:
				      if ( !TRUEP(marked))
					  goto end_loop_69;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_3 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_3,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_70;
				    end_loop_69:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_24;
				      goto next_loop_69;
				    end_loop_70:
				    end_24:
				      level = level - (SI_Long)1L;
				      goto next_loop_68;
				    end_loop_68:;
				      kb_specific_value = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
				      if (kb_specific_value);
				      else
					  kb_specific_value = 
						  No_specific_property_value;
				  }
				  else
				      kb_specific_value = 
					      No_specific_property_value;
				  if ( !EQ(kb_specific_value,
					  No_specific_property_value))
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
				    next_loop_71:
				      if (level < ab_loop_bind_)
					  goto end_loop_71;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				    next_loop_72:
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_3 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_3,temp_1);
				      MVS_2(result,succ,marked);
				    next_loop_73:
				      if ( !TRUEP(marked))
					  goto end_loop_72;
				      curr = 
					      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					      (SI_Long)0L),level));
				      reference = ISVREF(ISVREF(curr,
					      (SI_Long)0L),level);
				      temp_3 = ATOMIC_REF_OBJECT(reference);
				      temp_1 = (SI_Long)355L == 
					      ATOMIC_REF_STAMP(reference) ?
					       T : Nil;
				      result = VALUES_2(temp_3,temp_1);
				      MVS_2(result,succ,marked);
				      goto next_loop_73;
				    end_loop_72:
				      entry_hash = ISVREF(curr,(SI_Long)1L);
				      if (IFIX(entry_hash) < 
					      key_hash_value || 
					      IFIX(entry_hash) == 
					      key_hash_value &&  
					      !EQ(key_value,ISVREF(curr,
					      (SI_Long)2L))) {
					  pred = curr;
					  curr = succ;
				      }
				      else
					  goto end_25;
				      goto next_loop_72;
				    end_loop_73:
				    end_25:
				      level = level - (SI_Long)1L;
				      goto next_loop_71;
				    end_loop_71:;
				      resulting_value = IFIX(ISVREF(curr,
					      (SI_Long)1L)) == 
					      key_hash_value ? 
					      (EQ(key_value,ISVREF(curr,
					      (SI_Long)2L)) ? ISVREF(curr,
					      (SI_Long)3L) : Nil) : Nil;
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
			      gensymed_symbol = 
				      ACCESS_ONCE(ISVREF(new_class_definition,
				      (SI_Long)14L));
			      gensymed_symbol = gensymed_symbol ? 
				      ACCESS_ONCE(ISVREF(gensymed_symbol,
				      (SI_Long)5L)) : Nil;
			      temp_2 =  !TRUEP(gensymed_symbol);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if (temp_2) {
			      temp_1 = ISVREF(new_class_definition,
				      (SI_Long)21L);
			      temp_2 = EQUAL(temp_1,list_constant);
			  }
			  else
			      temp_2 = TRUEP(Nil);
			  if ( !temp_2)
			      ghost_definitions_to_restore = 
				      gensym_cons_1(new_class_definition,
				      ghost_definitions_to_restore);
		      }
		      if (Record_class_name_conflicts_qm && 
			      old_class_definition_qm && 
			      denotations_of_differing_slots)
			  deferred_class_name_conflicts = 
				  slot_value_cons_1(copy_tree_using_slot_value_conses_1(class_name_conflict),
				  deferred_class_name_conflicts);
		      else {
			  number_of_conflicts = 
				  FIXNUM_ADD1(number_of_conflicts);
			  create_class_definition_conflict_workspace(6,
				  class_1,new_name_qm,
				  old_class_definition_qm,
				  new_class_definition,
				  denotations_of_differing_slots, 
				  !TRUEP(new_algorithm_qm) ? T : Nil);
		      }
		  }
	      }
	  }
      }
      goto next_loop;
    end_loop:
      if (workspace_coordinate_information)
	  reclaim_frame_tree_1(workspace_coordinate_information);
      if (ghost_definitions_to_restore)
	  restore_ghost_definitions(ghost_definitions_to_restore,
		  new_algorithm_qm);
      if (Record_class_name_conflicts_qm)
	  record_class_name_conflicts(nreverse(deferred_class_name_conflicts));
      reclaim_slot_value_tree_1(Class_name_conflicts);
      Class_name_conflicts = Nil;
      if (IFIX(number_of_conflicts) > (SI_Long)0L)
	  notify_user_of_conflict_report_workspace_creation(number_of_conflicts);
      if (IFIX(number_of_subworkspaces_deleted) > (SI_Long)0L)
	  notify_user_of_conflicts(3,string_constant_1,
		  Name_text_string_for_kb_being_read,
		  number_of_subworkspaces_deleted);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_backup_definition_workspace_qm, Qcurrent_backup_definition_workspace_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_backup_definition_workspace_serial_number_qm, Qcurrent_backup_definition_workspace_serial_number_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_show_conflicts_during_kb_load_qm, Qdo_not_show_conflicts_during_kb_load_qm);

static Object string_constant_2;   /* "The class definitions on this workspace have been restored ~
				    *                 because they are no longer provided by the required modules.  ~
				    *                 After you have examined the class definitions ~
				    *                 and any subclasses and instances, you can move the definitions ~
				    *                 to other workspaces or delete them, and then delete ~
				    *                 this workspace."
				    */

static Object string_constant_3;   /* "BACKUP-DEFINITIONS-FROM-~a" */

static Object Qkb_workspace;       /* kb-workspace */

/* RESTORE-GHOST-DEFINITIONS */
Object restore_ghost_definitions(ghost_definitions_to_restore,new_algorithm_qm)
    Object ghost_definitions_to_restore, new_algorithm_qm;
{
    Object explanation, temp, workspace, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector, name_box;
    Object definition, ab_loop_list_, class_1, caption, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, list_of_layout_entries;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long spacing_between_columns, spacing_between_entries;
    SI_Long spacing_within_entries, inside_left_edge, inside_top_edge;
    SI_Long inside_bottom_edge, gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(130,11);
    explanation = make_free_text_box(1,tformat_text_string(1,
	    string_constant_2));
    temp = intern_text_string(1,tformat_text_string(2,string_constant_3,
	    get_simple_name_of_kb_being_read()));
    workspace = make_new_top_level_kb_workspace(7,Qkb_workspace,Nil,temp,
	    Nil,Nil,Nil,Reading_kb_p ? Name_of_module_being_read_qm : Nil);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
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
	    IFIX(ISVREF(Workspace_name_box_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp_1) {
	name_box = subblock;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    name_box = Qnil;
  end_1:;
    spacing_between_columns = (SI_Long)200L;
    spacing_between_entries = (SI_Long)50L;
    spacing_within_entries = (SI_Long)10L;
    inside_left_edge = IFIX(Most_negative_workspace_coordinate) + 
	    (SI_Long)500L;
    inside_top_edge = IFIX(Most_negative_workspace_coordinate) + (SI_Long)300L;
    inside_bottom_edge = IFIX(Most_positive_workspace_coordinate) - 
	    (SI_Long)100L - (SI_Long)500L;
    definition = Nil;
    ab_loop_list_ = ghost_definitions_to_restore;
    class_1 = Nil;
    caption = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    definition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_1 = ISVREF(definition,(SI_Long)20L);
    caption = make_caption_for_class_definition_table(class_1,definition);
    ab_loopvar__2 = gensym_cons_1(gensym_list_2(caption,definition),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    list_of_layout_entries = ab_loopvar_;
    goto end_2;
    list_of_layout_entries = Qnil;
  end_2:;
    add_to_workspace(4,explanation,workspace,FIX(inside_left_edge),
	    FIX(inside_top_edge));
    gensymed_symbol_1 = inside_left_edge;
    gensymed_symbol = ISVREF(name_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(explanation,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = spacing_between_entries;
    gensymed_symbol = ISVREF(name_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(name_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(name_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    shift_block(name_box,temp,FIX(gensymed_symbol_1 - gensymed_symbol_2));
    gensymed_symbol = ISVREF(explanation,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = spacing_between_entries;
    add_and_lay_out_blocks_on_workspace(list_of_layout_entries,workspace,
	    FIX(inside_left_edge),FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2),FIX(inside_bottom_edge),
	    FIX(spacing_between_columns),FIX(spacing_between_entries),
	    FIX(spacing_within_entries));
    shrink_wrap_workspace(workspace);
    reclaim_gensym_tree_1(list_of_layout_entries);
    normalize_kb_workspace(workspace,new_algorithm_qm);
    Current_backup_definition_workspace_serial_number_qm = 
	    copy_frame_serial_number(ISVREF(workspace,(SI_Long)3L));
    Current_backup_definition_workspace_qm = workspace;
    if ( !TRUEP(Do_not_show_conflicts_during_kb_load_qm))
	put_workspace_on_detail_panes_now_or_later(workspace);
    return VALUES_1(workspace);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* ADD-AND-LAY-OUT-BLOCKS-ON-WORKSPACE */
Object add_and_lay_out_blocks_on_workspace(list_of_layout_entries,
	    workspace,initial_left_edge,initial_top_edge,bottom_edge_limit,
	    spacing_between_columns,spacing_between_entries,
	    spacing_within_entries)
    Object list_of_layout_entries, workspace, initial_left_edge;
    Object initial_top_edge, bottom_edge_limit, spacing_between_columns;
    Object spacing_between_entries, spacing_within_entries;
{
    Object remaining_entries, max_right_edge, left_edge, max_bottom_edge;
    Object entry, top_edge, ab_loop_iter_flag_, remaining_entries_old_value;
    Object temp, block, ab_loop_list_, top_edge_now, temp_1;
    Object extreme_right_edge, extreme_bottom_edge, height, gensymed_symbol_3;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(130,12);
    remaining_entries = list_of_layout_entries;
    max_right_edge = initial_left_edge;
    left_edge = initial_left_edge;
  next_loop:
    if ( !TRUEP(remaining_entries))
	goto end_loop;
    max_bottom_edge = initial_top_edge;
    entry = Nil;
    top_edge = initial_top_edge;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    remaining_entries_old_value = remaining_entries;
    temp = FIRST(remaining_entries_old_value);
    remaining_entries = REST(remaining_entries_old_value);
    entry = temp;
    if ( !TRUEP(ab_loop_iter_flag_))
	top_edge = FIXNUM_ADD(max_bottom_edge,spacing_between_entries);
    block = Nil;
    ab_loop_list_ = entry;
    top_edge_now = top_edge;
    ab_loop_iter_flag_ = T;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	top_edge_now = FIXNUM_ADD(max_bottom_edge,spacing_within_entries);
    add_to_workspace(4,block,workspace,left_edge,top_edge_now);
    update_representations_of_slot_value(2,block,Qname_or_names_for_frame);
    result = determine_extreme_edges_of_block(block);
    MVS_4(result,temp,temp,extreme_right_edge,extreme_bottom_edge);
    max_right_edge = FIXNUM_MAX(max_right_edge,extreme_right_edge);
    max_bottom_edge = FIXNUM_MAX(max_bottom_edge,extreme_bottom_edge);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_2;
  end_loop_1:;
    if (remaining_entries) {
	gensymed_symbol = IFIX(max_bottom_edge);
	gensymed_symbol_1 = IFIX(spacing_between_entries);
	height = FIX((SI_Long)0L);
	block = Nil;
	ab_loop_list_ = FIRST(remaining_entries);
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_2 = IFIX(height);
	gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_3);
	gensymed_symbol_3 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_3 = gensymed_symbol_3 ? ISVREF(gensymed_symbol_3,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_5 = IFIX(gensymed_symbol_3);
	gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
	gensymed_symbol_5 = IFIX(height) == (SI_Long)0L ? (SI_Long)0L : 
		IFIX(spacing_within_entries);
	height = FIX(gensymed_symbol_2 + gensymed_symbol_4 + 
		gensymed_symbol_5);
	goto next_loop_3;
      end_loop_2:
	gensymed_symbol_2 = IFIX(height);
	goto end_1;
	gensymed_symbol_2 = IFIX(Qnil);
      end_1:;
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	temp_2 = FIXNUM_LT(FIX(gensymed_symbol + gensymed_symbol_1),
		bottom_edge_limit);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2)
	goto end_loop_3;
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_3:;
    left_edge = FIXNUM_ADD(max_right_edge,spacing_between_columns);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qfix_definitions_saved_as_ghost_definitions;  /* fix-definitions-saved-as-ghost-definitions */

/* FIX-DEFINITIONS-SAVED-AS-GHOST-DEFINITIONS */
Object fix_definitions_saved_as_ghost_definitions(new_class_definition,
	    workspace_coordinate_information,new_algorithm_qm)
    Object new_class_definition, workspace_coordinate_information;
    Object new_algorithm_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, gensymed_symbol;
    Object workspace, temp_1, coordinate_information_qm, left_edge, top_edge;
    SI_Long third_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,13);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
		  Qfix_definitions_saved_as_ghost_definitions;
      }
      gensymed_symbol = ACCESS_ONCE(ISVREF(new_class_definition,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      workspace = gensymed_symbol;
      temp_1 = member(4,workspace,workspace_coordinate_information,Ktest,
	      Qcar_eq);
      coordinate_information_qm = CAR(temp_1);
      left_edge = Nil;
      top_edge = Nil;
      if (coordinate_information_qm) {
	  top_edge = SECOND(coordinate_information_qm);
	  left_edge = THIRD(coordinate_information_qm);
	  third_new_value = IFIX(left_edge) + (SI_Long)60L;
	  M_THIRD(coordinate_information_qm) = FIX(third_new_value);
      }
      else {
	  gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  top_edge = gensymed_symbol;
	  gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  left_edge = gensymed_symbol;
	  workspace_coordinate_information = 
		  frame_cons_1(frame_list_3(workspace,top_edge,
		  FIX(IFIX(left_edge) + (SI_Long)80L)),
		  workspace_coordinate_information);
      }
      shift_block(new_class_definition,left_edge,top_edge);
      enlarge_workspace_for_block_and_subblocks_as_necessary(new_class_definition,
	      workspace);
      update_representations_of_slot_value(2,new_class_definition,
	      Qname_or_names_for_frame);
      gensymed_symbol = ACCESS_ONCE(ISVREF(new_class_definition,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      normalize_kb_workspace(gensymed_symbol,new_algorithm_qm);
      result = VALUES_1(workspace_coordinate_information);
    POP_SPECIAL();
    return result;
}

/* NOTIFY-USER-OF-CONFLICTS */
Object notify_user_of_conflicts varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,14);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Do_not_show_conflicts_during_kb_load_qm)) {
	if (EQ(arg1,No_arg))
	    return notify_user(1,notification_as_format_string);
	else if (EQ(arg2,No_arg))
	    return notify_user(2,notification_as_format_string,arg1);
	else if (EQ(arg3,No_arg))
	    return notify_user(3,notification_as_format_string,arg1,arg2);
	else if (EQ(arg4,No_arg))
	    return notify_user(4,notification_as_format_string,arg1,arg2,arg3);
	else if (EQ(arg5,No_arg))
	    return notify_user(5,notification_as_format_string,arg1,arg2,
		    arg3,arg4);
	else if (EQ(arg6,No_arg))
	    return notify_user(6,notification_as_format_string,arg1,arg2,
		    arg3,arg4,arg5);
	else if (EQ(arg7,No_arg))
	    return notify_user(7,notification_as_format_string,arg1,arg2,
		    arg3,arg4,arg5,arg6);
	else if (EQ(arg8,No_arg))
	    return notify_user(8,notification_as_format_string,arg1,arg2,
		    arg3,arg4,arg5,arg6,arg7);
	else if (EQ(arg9,No_arg))
	    return notify_user(9,notification_as_format_string,arg1,arg2,
		    arg3,arg4,arg5,arg6,arg7,arg8);
	else
	    return notify_user(10,notification_as_format_string,arg1,arg2,
		    arg3,arg4,arg5,arg6,arg7,arg8,arg9);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_4;   /* "The KB ~S contains a class definition that differs from an established ~
				    * ? (existing) definition.  A conflict report workspace has been created for this."
				    */

static Object string_constant_5;   /* "The KB ~S contains ~D class definitions that differ from established ~
				    * ? (existing) definitions.  For each of these, a conflict report workspace has ~
				    * ? been created."
				    */

/* NOTIFY-USER-OF-CONFLICT-REPORT-WORKSPACE-CREATION */
Object notify_user_of_conflict_report_workspace_creation(number_of_conflicts)
    Object number_of_conflicts;
{
    x_note_fn_call(130,15);
    return notify_user_of_conflicts(3,IFIX(number_of_conflicts) == 
	    (SI_Long)1L ? string_constant_4 : string_constant_5,
	    Name_text_string_for_kb_being_read,number_of_conflicts);
}

static Object string_constant_6;   /* "CONFLICT REPORT!  The merged-in KB ~S contained a definition for ~A ~
				    *                     that differed from an established (existing) definition.  The class ~
				    *                     from the merged-in KB has been renamed ~A.  (If you keep this new ~
				    *                     name, you should update rules, formulas, etc., appropriately.)"
				    */

static Object string_constant_7;   /* "CONFLICT REPORT!  When the KB ~S was saved out, it contained a ~
				    *                     definition for ~A, which has since become a built-in class or type.  Because ~
				    *                     of this, the class from the KB has been renamed ~A.  You should ~
				    *                     update rules, formulas, etc., appropriately.  (You may delete ~
				    *                     this workspace when you are done looking at it.)"
				    */

static Object Qborderless_free_text;  /* borderless-free-text */

static Object Qconflict_report_format;  /* conflict-report-format */

static Object string_constant_8;   /* "You may wish to edit one or both of the tables below.  Differences in ~
				    *                     the tables have been highlighted.  If the tables become identical ~
				    *                     except for the class names, you may merge one of them into the other ~
				    *                     by editing the CHANGE slot.  Type or select \"merge all instances and ~
				    *                     subclasses into definition for <other class>.\"  Be sure to read the ~
				    *                     logbook notes when you do this.  You should delete this workspace when ~
				    *                     you are done with it."
				    */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* CREATE-CLASS-DEFINITION-CONFLICT-WORKSPACE */
Object create_class_definition_conflict_workspace varargs_1(int, n)
{
    Object class_1, new_name_qm, old_class_definition_qm, new_class_definition;
    Object denotations_of_differing_slots;
    Object old_algorithm_qm, class_definition, paragraph_1, paragraph_2_qm;
    Object caption_for_class_definition_table, class_definition_table;
    Object caption_for_new_class_definition_table_qm;
    Object new_class_definition_table_qm, temp, workspace, gensymed_symbol;
    Object left_edge_for_class_definition_table, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, gensymed_symbol_5, temp_1;
    SI_Long left_edge_for_new_class_definition_table;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,16);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    new_name_qm = REQUIRED_ARG_nonrelocating();
    old_class_definition_qm = REQUIRED_ARG_nonrelocating();
    new_class_definition = REQUIRED_ARG_nonrelocating();
    denotations_of_differing_slots = REQUIRED_ARG_nonrelocating();
    old_algorithm_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_definition = old_class_definition_qm;
    if (class_definition);
    else
	class_definition = new_class_definition;
    paragraph_1 = make_free_text_box(3,tformat_text_string(4,
	    old_class_definition_qm ? string_constant_6 : 
	    string_constant_7,Name_text_string_for_kb_being_read,class_1,
	    new_name_qm),Qborderless_free_text,Qconflict_report_format);
    paragraph_2_qm = old_class_definition_qm ? make_free_text_box(3,
	    tformat_text_string(1,string_constant_8),Qborderless_free_text,
	    Qconflict_report_format) : Nil;
    caption_for_class_definition_table = 
	    make_caption_for_class_definition_table(get_lookup_slot_value_given_default(class_definition,
	    Qname_or_names_for_frame,Nil),class_definition);
    class_definition_table = make_attributes_table(1,class_definition);
    caption_for_new_class_definition_table_qm = old_class_definition_qm ? 
	    make_caption_for_class_definition_table(new_name_qm,
	    new_class_definition) : Nil;
    new_class_definition_table_qm = old_class_definition_qm ? 
	    make_attributes_table(1,new_class_definition) : Nil;
    temp = make_name_for_class_name_conflict_workspace(class_1);
    workspace = make_new_top_level_kb_workspace(7,Qkb_workspace,Nil,temp,
	    paragraph_1,Nil,Nil,Reading_kb_p ? 
	    Name_of_module_being_read_qm : Nil);
    gensymed_symbol = ISVREF(paragraph_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    left_edge_for_class_definition_table = gensymed_symbol;
    gensymed_symbol_1 = IFIX(left_edge_for_class_definition_table);
    gensymed_symbol = ISVREF(class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol = ISVREF(caption_for_class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(caption_for_class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol = ISVREF(paragraph_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(paragraph_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_5 = IFIX(gensymed_symbol);
    gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
    temp_1 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    gensymed_symbol_2 = MAX(temp_1,gensymed_symbol_4);
    gensymed_symbol_3 = (SI_Long)50L;
    left_edge_for_new_class_definition_table = gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_3;
    if (paragraph_2_qm) {
	gensymed_symbol = ISVREF(paragraph_1,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	add_to_workspace(4,paragraph_2_qm,workspace,
		FIX(left_edge_for_new_class_definition_table),gensymed_symbol);
    }
    gensymed_symbol_1 = IFIX(left_edge_for_class_definition_table);
    gensymed_symbol = ISVREF(class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol = ISVREF(caption_for_class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(caption_for_class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)1L;
    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)0L;
    gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(paragraph_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    temp_2 = paragraph_2_qm;
    if (temp_2);
    else
	temp_2 = paragraph_1;
    gensymed_symbol = ISVREF(temp_2,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
    gensymed_symbol_2 = (SI_Long)40L;
    add_to_workspace(4,caption_for_class_definition_table,workspace,temp,
	    FIX(gensymed_symbol_1 + gensymed_symbol_2));
    if (caption_for_new_class_definition_table_qm) {
	gensymed_symbol_1 = left_edge_for_new_class_definition_table;
	gensymed_symbol = ISVREF(new_class_definition_table_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(new_class_definition_table_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol = ISVREF(caption_for_new_class_definition_table_qm,
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(caption_for_new_class_definition_table_qm,
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)1L;
	gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	gensymed_symbol_3 = (SI_Long)0L;
	gensymed_symbol_2 = MAX(gensymed_symbol_2,gensymed_symbol_3);
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(caption_for_class_definition_table,
		(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	add_to_workspace(4,caption_for_new_class_definition_table_qm,
		workspace,temp,gensymed_symbol);
    }
    gensymed_symbol = ISVREF(caption_for_class_definition_table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ACCESS_ONCE(ISVREF(new_class_definition,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    temp = EQ(gensymed_symbol,workspace) ? new_class_definition : Nil;
    if (temp);
    else
	temp = caption_for_new_class_definition_table_qm;
    if (temp);
    else
	temp = caption_for_class_definition_table;
    gensymed_symbol = ISVREF(temp,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = MAX(gensymed_symbol_1,gensymed_symbol_2);
    gensymed_symbol_2 = (SI_Long)15L;
    gensymed_symbol = ACCESS_ONCE(ISVREF(new_class_definition,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    gensymed_symbol_3 = EQ(gensymed_symbol,workspace) ? (SI_Long)20L : 
	    (SI_Long)0L;
    add_to_workspace(4,class_definition_table,workspace,
	    left_edge_for_class_definition_table,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_3));
    if (old_class_definition_qm)
	highlight_differing_slots_in_definitions(class_definition,
		new_class_definition,denotations_of_differing_slots);
    if (new_class_definition_table_qm) {
	gensymed_symbol = ISVREF(class_definition_table,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	add_to_workspace(4,new_class_definition_table_qm,workspace,
		FIX(left_edge_for_new_class_definition_table),gensymed_symbol);
    }
    change_slot_value(3,new_class_definition,Qname_or_names_for_frame,
	    Just_update_representations_of_slot_value);
    if ( !TRUEP(Do_not_show_conflicts_during_kb_load_qm)) {
	if (Servicing_workstation_qm)
	    put_workspace_on_pane_function(workspace,
		    Current_workstation_detail_pane,Qleft,Qtop,Nil,
		    FIX((SI_Long)50L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    return normalize_kb_workspace(workspace, !TRUEP(old_algorithm_qm) ? T :
	     Nil);
}

static Object string_constant_9;   /* "~a-CLASS-NAME-CONFLICT" */

/* MAKE-NAME-FOR-CLASS-NAME-CONFLICT-WORKSPACE */
Object make_name_for_class_name_conflict_workspace(class_1)
    Object class_1;
{
    x_note_fn_call(130,17);
    return intern_text_string(1,tformat_text_string(2,string_constant_9,
	    class_1));
}

static Object string_constant_10;  /* " and ~D subclass~A" */

static Object string_constant_11;  /* "" */

static Object string_constant_12;  /* "es" */

static Object string_constant_13;  /* "Definition for ~A.  ~D instance~A~A~A." */

static Object string_constant_14;  /* "s" */

static Object string_constant_15;  /* " and a subworkspace" */

/* MAKE-CAPTION-FOR-CLASS-DEFINITION-TABLE */
Object make_caption_for_class_definition_table(class_1,class_definition)
    Object class_1, class_definition;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame;
    Object number_of_instances, temp_1, subclasses_phrase;
    SI_Long ab_loopvar__2, gensymed_symbol, gensymed_symbol_1;
    SI_Long number_of_subclasses;
    char temp;
    Declare_special(1);

    x_note_fn_call(130,18);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = (SI_Long)0L;
      ab_loopvar_ = collect_subclasses(class_1);
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
      if (frame)
	  ab_loopvar__2 = ab_loopvar__2 + (SI_Long)1L;
      goto next_loop;
    end_loop_1:
      number_of_instances = FIX(ab_loopvar__2);
      goto end_1;
      number_of_instances = Qnil;
    end_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = class_1;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = (SI_Long)0L;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop_2:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop_2;
      temp_1 = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      frame = temp_1;
      if (frame)
	  ab_loopvar__2 = ab_loopvar__2 + (SI_Long)1L;
      goto next_loop_2;
    end_loop_2:
      gensymed_symbol = ab_loopvar__2;
      goto end_2;
      gensymed_symbol = IFIX(Qnil);
    end_2:;
    POP_SPECIAL();
    gensymed_symbol_1 = (SI_Long)1L;
    number_of_subclasses = gensymed_symbol - gensymed_symbol_1;
    subclasses_phrase = number_of_subclasses > (SI_Long)0L ? 
	    tformat_text_string(3,string_constant_10,
	    FIX(number_of_subclasses),number_of_subclasses == (SI_Long)1L ?
	     string_constant_11 : string_constant_12) : string_constant_11;
    temp_1 = make_free_text_box(3,tformat_text_string(6,string_constant_13,
	    class_1,number_of_instances,IFIX(number_of_instances) == 
	    (SI_Long)1L ? string_constant_11 : string_constant_14,
	    subclasses_phrase,ISVREF(class_definition,(SI_Long)18L) ? 
	    string_constant_15 : string_constant_11),Qborderless_free_text,
	    Qconflict_report_format);
    if (number_of_subclasses > (SI_Long)0L)
	reclaim_text_string(subclasses_phrase);
    return VALUES_1(temp_1);
}

/* RECLAIM-CLASS-NAME-CONFLICTS */
Object reclaim_class_name_conflicts(conflicts)
    Object conflicts;
{
    x_note_fn_call(130,19);
    if (conflicts) {
	reclaim_slot_value(CDR(conflicts));
	reclaim_frame_serial_number(CAR(conflicts));
	return reclaim_slot_value_cons_1(conflicts);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Record_of_class_name_conflicts_qm, Qrecord_of_class_name_conflicts_qm);

/* RECORD-CLASS-NAME-CONFLICTS */
Object record_class_name_conflicts(class_name_conflicts)
    Object class_name_conflicts;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,20);
    PUSH_SPECIAL_WITH_SYMBOL(Class_name_conflicts,Qclass_name_conflicts,class_name_conflicts,
	    0);
      if (Record_of_class_name_conflicts_qm) {
	  temp = Record_of_class_name_conflicts_qm;
	  Record_of_class_name_conflicts_qm = Nil;
	  reclaim_class_name_conflicts(temp);
      }
      temp = copy_frame_serial_number(Current_frame_serial_number);
      Record_of_class_name_conflicts_qm = slot_value_cons_1(temp,
	      Class_name_conflicts);
      result = VALUES_1(Record_of_class_name_conflicts_qm);
    POP_SPECIAL();
    return result;
}

/* RECORD-CLASS-NAME-CONFLICT */
Object record_class_name_conflict varargs_1(int, n)
{
    Object class_1, new_name_qm, old_class_definition_qm, new_class_definition;
    Object denotations_of_differing_slots;
    Object ghost_definition_p, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,21);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    new_name_qm = REQUIRED_ARG_nonrelocating();
    old_class_definition_qm = REQUIRED_ARG_nonrelocating();
    new_class_definition = REQUIRED_ARG_nonrelocating();
    denotations_of_differing_slots = REQUIRED_ARG_nonrelocating();
    ghost_definition_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = class_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = new_name_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = old_class_definition_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = new_class_definition;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = denotations_of_differing_slots;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = ghost_definition_p;
    Class_name_conflicts = slot_value_cons_1(gensymed_symbol,
	    Class_name_conflicts);
    return VALUES_1(Class_name_conflicts);
}

static Object Qattribute_displays_spec_qm;  /* attribute-displays-spec? */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qdefault_overrides;  /* default-overrides */

static Object Qattribute_displays_for_class;  /* attribute-displays-for-class */

static Object Qstubs_for_class;    /* stubs-for-class */

static Object Qconnections_for_class_qm;  /* connections-for-class? */

static Object Qstub_length_for_class;  /* stub-length-for-class */

static Object Qcross_section_pattern_for_connection;  /* cross-section-pattern-for-connection */

static Object Qstub_length_for_connection;  /* stub-length-for-connection */

static Object Qdefault_message_properties_for_class;  /* default-message-properties-for-class */

static Object Qdefault_message_properties;  /* default-message-properties */

/* TRANSFER-VALUES-TO-INTERIM-CLASS-DEFINITION-FOR-MERGE */
Object transfer_values_to_interim_class_definition_for_merge(interim_class_definition,
	    current_definition)
    Object interim_class_definition, current_definition;
{
    Object current_definition_class, class_description;
    Object current_definition_slot_descriptions, class_name;
    Object interim_class_definition_class_description_slot;
    Object sub_class_bit_vector, current_attribute_displays_spec_qm;
    Object current_slot_description, ab_loop_list_, pretty_slot_name;
    Object interim_slot_description_qm, current_value;
    Object current_slot_group_for_block, new_current_slot_group_for_block;
    Object current_subblocks, temp_1, queue, next_queue_element, subblock;
    Object gensymed_symbol_3, gensymed_symbol_4, slot_group_qm;
    Object current_default_overrides_qm, stubs_qm, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, temp_3, entry_hash;
    Object tail, head, new_cons, svref_arg_2, svref_new_value;
    Object gensymed_symbol_5, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, cross_section_pattern_qm;
    Object stub_length_qm, junction_block_qm, default_message_properties_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(130,22);
    current_definition_class = ISVREF(ISVREF(current_definition,
	    (SI_Long)1L),(SI_Long)1L);
    class_description = ISVREF(current_definition,(SI_Long)1L);
    current_definition_slot_descriptions = ISVREF(class_description,
	    (SI_Long)6L);
    class_name = ISVREF(current_definition,(SI_Long)20L);
    interim_class_definition_class_description_slot = 
	    ISVREF(interim_class_definition,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(ISVREF(current_definition,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
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
    current_attribute_displays_spec_qm = temp ? 
	    get_lookup_slot_value_given_default(current_definition,
	    Qattribute_displays_spec_qm,Nil) : Nil;
    change_slot_value(3,interim_class_definition,Qframe_status_and_notes,Nil);
    current_slot_description = Nil;
    ab_loop_list_ = current_definition_slot_descriptions;
    pretty_slot_name = Nil;
    interim_slot_description_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    current_slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pretty_slot_name = ISVREF(current_slot_description,(SI_Long)2L);
    interim_slot_description_qm = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    interim_class_definition_class_description_slot,Nil);
    if (interim_slot_description_qm) {
	if (member_eql(pretty_slot_name,list_constant_1));
	else if (member_eql(pretty_slot_name,list_constant_2)) {
	    current_value = get_slot_description_value(current_definition,
		    current_slot_description);
	    set_slot_description_value_without_noting(interim_class_definition,
		    interim_slot_description_qm,current_value);
	    set_slot_description_value_without_noting(current_definition,
		    current_slot_description,
		    copy_for_slot_value(current_value));
	}
	else if (EQ(pretty_slot_name,Qslot_group_for_block_qm)) {
	    current_slot_group_for_block = ISVREF(current_definition,
		    (SI_Long)14L);
	    new_current_slot_group_for_block = make_icon_slot_group_1();
	    current_subblocks = ISVREF(current_slot_group_for_block,
		    (SI_Long)4L);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(interim_class_definition,
			Qslot_group_for_block_qm);
	    SVREF(interim_class_definition,FIX((SI_Long)14L)) = 
		    current_slot_group_for_block;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(current_definition,
			Qslot_group_for_block_qm);
	    SVREF(current_definition,FIX((SI_Long)14L)) = 
		    new_current_slot_group_for_block;
	    temp_1 = ISVREF(current_slot_group_for_block,(SI_Long)0L);
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = ISVREF(current_slot_group_for_block,(SI_Long)1L);
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)1L)) = temp_1;
	    temp_1 = ISVREF(current_slot_group_for_block,(SI_Long)2L);
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)2L)) = temp_1;
	    temp_1 = ISVREF(current_slot_group_for_block,(SI_Long)3L);
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)3L)) = temp_1;
	    temp_1 = ISVREF(current_slot_group_for_block,(SI_Long)5L);
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)5L)) = temp_1;
	    if (ISVREF(current_slot_group_for_block,(SI_Long)5L))
		add_subblock(interim_class_definition,
			ISVREF(current_slot_group_for_block,(SI_Long)5L));
	    if (current_subblocks) {
		queue = current_subblocks;
		next_queue_element = Nil;
		subblock = Nil;
		next_queue_element = constant_queue_next(ISVREF(queue,
			(SI_Long)2L),queue);
	      next_loop_1:
		if ( !TRUEP(next_queue_element))
		    goto end_loop_1;
		subblock = ISVREF(next_queue_element,(SI_Long)4L);
		next_queue_element = 
			constant_queue_next(next_queue_element,queue);
		gensymed_symbol_3 = subblock;
		gensymed_symbol_4 = Nil;
		slot_group_qm = ISVREF(gensymed_symbol_3,(SI_Long)14L);
		gensymed_symbol_4 = interim_class_definition;
		if (slot_group_qm)
		    SVREF(slot_group_qm,FIX((SI_Long)5L)) = gensymed_symbol_4;
		else if ( !EQ(gensymed_symbol_4,Qnil)) {
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(gensymed_symbol_3,
				Qslot_group_for_block_qm);
		    temp_1 = make_icon_slot_group_1();
		    SVREF(gensymed_symbol_3,FIX((SI_Long)14L)) = temp_1;
		    temp_1 = ISVREF(gensymed_symbol_3,(SI_Long)14L);
		    SVREF(temp_1,FIX((SI_Long)5L)) = gensymed_symbol_4;
		}
		goto next_loop_1;
	      end_loop_1:;
	    }
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)4L)) = Nil;
	    SVREF(new_current_slot_group_for_block,FIX((SI_Long)6L)) = Nil;
	}
	else if (EQ(pretty_slot_name,Qdefault_overrides)) {
	    current_default_overrides_qm = ISVREF(current_definition,
		    (SI_Long)27L);
	    sub_class_bit_vector = ISVREF(ISVREF(current_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Object_definition_class_description,
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
	    if (temp) {
		stubs_qm = ISVREF(current_definition,(SI_Long)30L);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(interim_class_definition,
			    Qdefault_overrides);
		temp_1 = current_attribute_displays_spec_qm || stubs_qm ? 
			nconc2(current_default_overrides_qm,
			nconc2(current_attribute_displays_spec_qm ? 
			slot_value_cons_1(slot_value_list_2(Qattribute_displays_for_class,
			current_attribute_displays_spec_qm),Nil) : Nil,
			stubs_qm ? 
			slot_value_cons_1(slot_value_list_2(Qstubs_for_class,
			stubs_qm),Nil) : Nil)) : current_default_overrides_qm;
		SVREF(interim_class_definition,FIX((SI_Long)27L)) = temp_1;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(current_definition,
			    Qconnections_for_class_qm);
		temp_1 = copy_for_slot_value(stubs_qm);
		SVREF(current_definition,FIX((SI_Long)30L)) = temp_1;
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(current_definition,
			    Qattribute_displays_spec_qm);
		set_lookup_slot_value_1(current_definition,
			Qattribute_displays_spec_qm,
			copy_for_slot_value(current_attribute_displays_spec_qm));
	    }
	    else {
		skip_list = CDR(Symbol_properties_table);
		key_value = current_definition_class;
		key_hash_value = SXHASH_SYMBOL_1(current_definition_class) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_2:
		if (level < ab_loop_bind_)
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_3:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_4:
		if ( !TRUEP(marked))
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
		goto next_loop_4;
	      end_loop_3:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_1;
		goto next_loop_3;
	      end_loop_4:
	      end_1:
		level = level - (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
		gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol_3)) {
		    gensymed_symbol_3 = current_definition_class;
		    temp_2 = Symbol_properties_table;
		    temp_3 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
			temp_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol_3 = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			    temp_3,gensymed_symbol_4);
		}
		global_properties = gensymed_symbol_3;
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
	      next_loop_5:
		if (level < ab_loop_bind_)
		    goto end_loop_5;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_6:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_7:
		if ( !TRUEP(marked))
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_3);
		MVS_2(result,succ,marked);
		goto next_loop_7;
	      end_loop_6:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_2;
		goto next_loop_6;
	      end_loop_7:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_5;
	      end_loop_5:;
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
		  next_loop_8:
		    if (level < ab_loop_bind_)
			goto end_loop_8;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_9:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_10:
		    if ( !TRUEP(marked))
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_10;
		  end_loop_9:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_3;
		    goto next_loop_9;
		  end_loop_10:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_8;
		  end_loop_8:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_11:
		    if (level < ab_loop_bind_)
			goto end_loop_11;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_12:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_13:
		    if ( !TRUEP(marked))
			goto end_loop_12;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		    goto next_loop_13;
		  end_loop_12:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_4;
		    goto next_loop_12;
		  end_loop_13:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_11;
		  end_loop_11:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol_3 = resulting_value;
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_definition_class_description,
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
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    cross_section_pattern_qm = ISVREF(current_definition,
			    (SI_Long)30L);
		    stub_length_qm = ISVREF(current_definition,(SI_Long)31L);
		    junction_block_qm = ISVREF(current_definition,
			    (SI_Long)32L);
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(interim_class_definition,
				Qdefault_overrides);
		    if (cross_section_pattern_qm || stub_length_qm || 
			    junction_block_qm) {
			temp_3 = cross_section_pattern_qm ? 
				slot_value_cons_1(slot_value_list_2(Qcross_section_pattern_for_class,
				cross_section_pattern_qm),Nil) : Nil;
			temp_1 = nconc2(current_default_overrides_qm,
				nconc2(temp_3,nconc2(stub_length_qm ? 
				slot_value_cons_1(slot_value_list_2(Qstub_length_for_class,
				stub_length_qm),Nil) : Nil,
				junction_block_qm ? 
				slot_value_cons_1(slot_value_list_2(Qjunction_block_class_for_class,
				junction_block_qm),Nil) : Nil)));
		    }
		    else
			temp_1 = current_default_overrides_qm;
		    SVREF(interim_class_definition,FIX((SI_Long)27L)) = temp_1;
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(current_definition,
				Qcross_section_pattern_for_connection);
		    temp_1 = copy_for_slot_value(cross_section_pattern_qm);
		    SVREF(current_definition,FIX((SI_Long)30L)) = temp_1;
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(current_definition,
				Qstub_length_for_connection);
		    temp_1 = copy_for_slot_value(stub_length_qm);
		    SVREF(current_definition,FIX((SI_Long)31L)) = temp_1;
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(current_definition,
				Qjunction_block_class_for_connection);
		    temp_1 = copy_for_slot_value(junction_block_qm);
		    SVREF(current_definition,FIX((SI_Long)32L)) = temp_1;
		}
		else {
		    default_message_properties_qm = 
			    ISVREF(current_definition,(SI_Long)30L);
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(interim_class_definition,
				Qdefault_overrides);
		    temp_1 = default_message_properties_qm ? 
			    nconc2(current_default_overrides_qm,
			    slot_value_cons_1(slot_value_list_2(Qdefault_message_properties_for_class,
			    default_message_properties_qm),Nil)) : 
			    current_default_overrides_qm;
		    SVREF(interim_class_definition,FIX((SI_Long)27L)) = temp_1;
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(current_definition,
				Qdefault_message_properties);
		    temp_1 = 
			    copy_for_slot_value(default_message_properties_qm);
		    SVREF(current_definition,FIX((SI_Long)30L)) = temp_1;
		}
	    }
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(current_definition,Qdefault_overrides);
	    temp_1 = copy_for_slot_value(current_default_overrides_qm);
	    SVREF(current_definition,FIX((SI_Long)27L)) = temp_1;
	}
	else {
	    current_value = get_slot_description_value(current_definition,
		    current_slot_description);
	    set_slot_description_value_without_noting(interim_class_definition,
		    interim_slot_description_qm,current_value);
	    if (Currently_automatically_resolving_class_name_conflicts_qm)
		set_slot_description_value_without_noting(current_definition,
			current_slot_description,
			ISVREF(current_slot_description,(SI_Long)6L));
	    else
		set_slot_description_value_without_noting(current_definition,
			current_slot_description,
			copy_for_slot_value(current_value));
	}
    }
    goto next_loop;
  end_loop:;
    return mutate_global_or_kb_specific_property_value(class_name,
	    interim_class_definition,Class_definition_gkbprop);
}

static Object Qab_gensym;          /* gensym */

/* REORDER-CLASS-NAME-CONFLICTS-WITH-REFERENCED-SLOTS-FIRST */
Object reorder_class_name_conflicts_with_referenced_slots_first(conflicts)
    Object conflicts;
{
    Object result_1, conflicts_with_predecessors;
    Object conflicts_ready_to_be_processed, conflicts_hash, fsn;
    Object number_of_conflicts, number_of_reordered_conflicts, conflict;
    Object ab_loop_list_, conflict_structure, gensymed_symbol, x, xa, ya;
    Object temp_1, definition, inheritance_path, class_1, ab_loop_list__1;
    Object follower_qm, temp_2, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object definition_1, x2, sub_class_bit_vector, attribute_descriptions;
    Object attribute_description, ab_loop_list__2, preceder_qm;
    Object gensym_pop_store, cons_1, next_cons, svref_arg_2, next, follower;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(130,23);
    result_1 = Nil;
    conflicts_with_predecessors = Nil;
    conflicts_ready_to_be_processed = Nil;
    conflicts_hash = make_eq_hash_table(length(conflicts),Nil,Nil);
    fsn = CAR(conflicts);
    number_of_conflicts = FIX((SI_Long)0L);
    number_of_reordered_conflicts = FIX((SI_Long)0L);
    conflict = Nil;
    ab_loop_list_ = CDR(conflicts);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    conflict = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    number_of_conflicts = FIXNUM_ADD1(number_of_conflicts);
    conflict_structure = gensym_list_2(conflict,FIX((SI_Long)0L));
    conflicts_with_predecessors = gensym_cons_1(conflict_structure,
	    conflicts_with_predecessors);
    gensymed_symbol = ISVREF(THIRD(conflict),(SI_Long)3L);
    x = THIRD(conflict);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	temp_1 = FIRST(conflict_structure);
	eq_puthash(conflicts_hash,FIRST(temp_1),conflict_structure);
    }
    goto next_loop;
  end_loop:;
    conflict_structure = Nil;
    ab_loop_list_ = conflicts_with_predecessors;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    conflict_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = FIRST(conflict_structure);
    definition = THIRD(temp_1);
    gensymed_symbol = ISVREF(definition,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(definition) ? EQ(ISVREF(definition,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(fsn))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(fsn,gensymed_symbol) : 
		TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(fsn);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(fsn),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	inheritance_path = get_lookup_slot_value_given_default(definition,
		Qclass_inheritance_path_of_definition,Nil);
	class_1 = Nil;
	ab_loop_list__1 = inheritance_path;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	class_1 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !EQ(class_1,ISVREF(definition,(SI_Long)20L))) {
	    follower_qm = eq_gethash(conflicts_hash,class_1,Nil);
	    if (follower_qm) {
		temp_2 = FIXNUM_ADD1(SECOND(follower_qm));
		M_SECOND(follower_qm) = temp_2;
		gensym_push_modify_macro_arg = follower_qm;
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = CDDR(conflict_structure);
		temp_2 = gensym_cons_1(car_1,cdr_1);
		M_CDDR(conflict_structure) = temp_2;
	    }
	}
	definition_1 = lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop);
	if (SIMPLE_VECTOR_P(definition_1) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition_1)) > 
		(SI_Long)2L &&  !EQ(ISVREF(definition_1,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(definition_1,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(definition_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Class_definition_class_description,
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
	attribute_descriptions = temp ? ISVREF(definition_1,(SI_Long)22L) :
		 Nil;
	attribute_description = Nil;
	ab_loop_list__2 = attribute_descriptions;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_3;
	attribute_description = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if (class_type_specification_p(attribute_type_specification(attribute_description))) 
		    {
	    preceder_qm = eq_gethash(conflicts_hash,
		    M_CAR(M_CDR(attribute_type_specification(attribute_description))),
		    Nil);
	    if (preceder_qm) {
		temp_2 = FIXNUM_ADD1(SECOND(conflict_structure));
		M_SECOND(conflict_structure) = temp_2;
		gensym_push_modify_macro_arg = conflict_structure;
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = CDDR(preceder_qm);
		temp_2 = gensym_cons_1(car_1,cdr_1);
		M_CDDR(preceder_qm) = temp_2;
	    }
	}
	goto next_loop_3;
      end_loop_3:;
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop_1;
  end_loop_1:;
    conflict_structure = Nil;
    ab_loop_list_ = conflicts_with_predecessors;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    conflict_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (IFIX(SECOND(conflict_structure)) == (SI_Long)0L)
	conflicts_ready_to_be_processed = gensym_cons_1(conflict_structure,
		conflicts_ready_to_be_processed);
    goto next_loop_4;
  end_loop_4:;
    conflicts_ready_to_be_processed = 
	    nreverse(conflicts_ready_to_be_processed);
    reclaim_eq_hash_table(conflicts_hash);
  next_loop_5:
    if ( !TRUEP(conflicts_ready_to_be_processed))
	goto end_loop_5;
    number_of_reordered_conflicts = FIXNUM_ADD1(number_of_reordered_conflicts);
    gensym_pop_store = Nil;
    cons_1 = conflicts_ready_to_be_processed;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = cons_1;
	    temp_2 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	else {
	    temp_2 = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	    temp_2 = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    conflicts_ready_to_be_processed = next_cons;
    next = gensym_pop_store;
    result_1 = slot_value_cons_1(CAR(next),result_1);
    follower = Nil;
    ab_loop_list_ = CDDR(next);
  next_loop_6:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_6;
    follower = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_2 = FIXNUM_SUB1(SECOND(follower));
    M_SECOND(follower) = temp_2;
    if (IFIX(SECOND(follower)) == (SI_Long)0L)
	conflicts_ready_to_be_processed = gensym_cons_1(follower,
		conflicts_ready_to_be_processed);
    goto next_loop_6;
  end_loop_6:;
    goto next_loop_5;
  end_loop_5:
    conflict_structure = Nil;
    ab_loop_list_ = conflicts_with_predecessors;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    conflict_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(conflict_structure);
    goto next_loop_7;
  end_loop_7:;
    reclaim_gensym_list_1(conflicts_with_predecessors);
    if (FIXNUM_EQ(number_of_conflicts,number_of_reordered_conflicts)) {
	temp_1 = CAR(conflicts);
	return slot_value_cons_1(temp_1,nreverse(result_1));
    }
    else {
	reclaim_slot_value_list_1(result_1);
	return VALUES_1(Nil);
    }
}

static Object Qclass_definition;   /* class-definition */

/* RESOLVE-CLASS-NAME-CONFLICTS */
Object resolve_class_name_conflicts()
{
    Object reordered_class_name_conflicts, do_not_note_permanent_changes_p;
    Object number_of_conflicts, ab_loop_destructure_;
    Object reference_frame_serial_number, class_name_conflicts;
    Object currently_automatically_resolving_class_name_conflicts_qm;
    Object class_name_conflict, ab_loop_list_, class_1, new_name;
    Object old_class_definition, new_class_definition;
    Object denotations_of_differing_slots, gensymed_symbol, xa, ya;
    Object interim_class_definition, successful_resolution_qm;
    Object slots_that_still_have_differences;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(130,24);
    if (Record_of_class_name_conflicts_qm) {
	reordered_class_name_conflicts = 
		reorder_class_name_conflicts_with_referenced_slots_first(Record_of_class_name_conflicts_qm);
	if (reordered_class_name_conflicts) {
	    reclaim_slot_value_list_1(Record_of_class_name_conflicts_qm);
	    Record_of_class_name_conflicts_qm = reordered_class_name_conflicts;
	}
	do_not_note_permanent_changes_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		2);
	  number_of_conflicts = FIX((SI_Long)0L);
	  ab_loop_destructure_ = Record_of_class_name_conflicts_qm;
	  reference_frame_serial_number = Nil;
	  class_name_conflicts = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Class_name_conflicts,Qclass_name_conflicts,class_name_conflicts,
		  1);
	    reference_frame_serial_number = CAR(ab_loop_destructure_);
	    Class_name_conflicts = CDR(ab_loop_destructure_);
	    currently_automatically_resolving_class_name_conflicts_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Currently_automatically_resolving_class_name_conflicts_qm,Qcurrently_automatically_resolving_class_name_conflicts_qm,currently_automatically_resolving_class_name_conflicts_qm,
		    0);
	      class_name_conflict = Nil;
	      ab_loop_list_ = Class_name_conflicts;
	      class_1 = Nil;
	      new_name = Nil;
	      old_class_definition = Nil;
	      new_class_definition = Nil;
	      denotations_of_differing_slots = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      class_name_conflict = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      class_1 = FIRST(class_name_conflict);
	      new_name = SECOND(class_name_conflict);
	      old_class_definition = THIRD(class_name_conflict);
	      new_class_definition = FOURTH(class_name_conflict);
	      denotations_of_differing_slots = FIFTH(class_name_conflict);
	      gensymed_symbol = ISVREF(old_class_definition,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(old_class_definition) ? 
		      EQ(ISVREF(old_class_definition,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			  == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(reference_frame_serial_number))
		  temp = FIXNUMP(gensymed_symbol) ? 
			  FIXNUM_LT(reference_frame_serial_number,
			  gensymed_symbol) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(reference_frame_serial_number);
		  ya = M_CAR(gensymed_symbol);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(reference_frame_serial_number),
			      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	      }
	      if (temp);
	      else {
		  gensymed_symbol = ISVREF(new_class_definition,(SI_Long)3L);
		  temp = SIMPLE_VECTOR_P(new_class_definition) ? 
			  EQ(ISVREF(new_class_definition,(SI_Long)1L),
			  Qavailable_frame_vector) : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = FIXNUMP(gensymed_symbol) ? 
			      IFIX(gensymed_symbol) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  if (temp);
		  else if (FIXNUMP(reference_frame_serial_number))
		      temp = FIXNUMP(gensymed_symbol) ? 
			      FIXNUM_LT(reference_frame_serial_number,
			      gensymed_symbol) : TRUEP(T);
		  else if (FIXNUMP(gensymed_symbol))
		      temp = TRUEP(Nil);
		  else {
		      xa = M_CAR(reference_frame_serial_number);
		      ya = M_CAR(gensymed_symbol);
		      temp = FIXNUM_LT(xa,ya);
		      if (temp);
		      else
			  temp = FIXNUM_EQ(xa,ya) ? 
				  FIXNUM_LT(M_CDR(reference_frame_serial_number),
				  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		  }
	      }
	      if ( !temp) {
		  if ( 
			  !TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(old_class_definition)) 
			  && 
			  definition_class_is_subclass_of_obj_conn_mess_definition_p(new_class_definition)) 
			      {
		      if (inheritance_for_merge_is_acceptable_p(new_class_definition,
			      old_class_definition)) {
			  interim_class_definition = 
				  make_frame(Qclass_definition);
			  transfer_values_to_interim_class_definition_for_merge(interim_class_definition,
				  new_class_definition);
			  M_FOURTH(class_name_conflict) = 
				  interim_class_definition;
			  delete_as_frame_with_name(new_class_definition,
				  new_name);
			  delete_frame(new_class_definition);
			  successful_resolution_qm = 
				  resolve_one_class_name_conflict(old_class_definition,
				  interim_class_definition);
			  if ( !TRUEP(successful_resolution_qm)) {
			      number_of_conflicts = 
				      FIXNUM_ADD1(number_of_conflicts);
			      create_class_definition_conflict_workspace(5,
				      class_1,new_name,
				      old_class_definition,
				      interim_class_definition,
				      slot_value_cons_1(Qdirect_superiors_of_defined_class,
				      Nil));
			  }
		      }
		      else {
			  number_of_conflicts = 
				  FIXNUM_ADD1(number_of_conflicts);
			  create_class_definition_conflict_workspace(5,
				  class_1,new_name,old_class_definition,
				  new_class_definition,
				  slot_value_cons_1(Qdirect_superiors_of_defined_class,
				  Nil));
		      }
		  }
		  else if ( 
			  !TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(new_class_definition)) 
			  && 
			  definition_class_is_subclass_of_obj_conn_mess_definition_p(old_class_definition)) 
			      {
		      number_of_conflicts = FIXNUM_ADD1(number_of_conflicts);
		      create_class_definition_conflict_workspace(5,class_1,
			      new_name,old_class_definition,
			      new_class_definition,
			      slot_value_cons_1(Qdirect_superiors_of_defined_class,
			      Nil));
		  }
		  else if ( 
			  !TRUEP(resolve_one_class_name_conflict(old_class_definition,
			  new_class_definition))) {
		      number_of_conflicts = FIXNUM_ADD1(number_of_conflicts);
		      slots_that_still_have_differences = 
			      find_differences_in_frames_if_any(4,
			      old_class_definition,new_class_definition,Nil,T);
		      create_class_definition_conflict_workspace(5,class_1,
			      new_name,old_class_definition,
			      new_class_definition,
			      slots_that_still_have_differences);
		      reclaim_slot_value_list_1(slots_that_still_have_differences);
		  }
	      }
	      goto next_loop;
	    end_loop:
	      if (IFIX(number_of_conflicts) > (SI_Long)0L)
		  notify_user_of_conflict_report_workspace_creation(number_of_conflicts);
	      record_class_name_conflicts(Nil);
	      Class_name_conflicts = Nil;
	      deal_with_backup_definition_workspace_after_automerge();
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_16;  /* "Automatically deleting the backup-definitions workspace ~NF; all ~
				    *          of its definitions were automatically deleted after conflicts ~
				    *          with existing definitions were successfully resolved."
				    */

/* DEAL-WITH-BACKUP-DEFINITION-WORKSPACE-AFTER-AUTOMERGE */
Object deal_with_backup_definition_workspace_after_automerge()
{
    Object gensymed_symbol, xa, ya, workspace_qm, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector;
    Object current_backup_definition_workspace_serial_number_qm_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(130,25);
    if (Current_backup_definition_workspace_qm) {
	gensymed_symbol = ISVREF(Current_backup_definition_workspace_qm,
		(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(Current_backup_definition_workspace_qm) ? 
		EQ(ISVREF(Current_backup_definition_workspace_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(Current_backup_definition_workspace_serial_number_qm))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(Current_backup_definition_workspace_serial_number_qm,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(Current_backup_definition_workspace_serial_number_qm);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(Current_backup_definition_workspace_serial_number_qm),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    workspace_qm = temp ? Current_backup_definition_workspace_qm : Nil;
    if (workspace_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	notify_user_of_conflicts(2,string_constant_16,workspace_qm);
	delete_frame(workspace_qm);
    }
    current_backup_definition_workspace_serial_number_qm_new_value = 
	    (FIXNUMP(Current_backup_definition_workspace_serial_number_qm) 
	    ||  
	    !TRUEP(Current_backup_definition_workspace_serial_number_qm)) 
	    && (Nil ||  !TRUEP(Nil)) ? Nil : 
	    frame_serial_number_setf_helper_1(Current_backup_definition_workspace_serial_number_qm,
	    Nil);
    Current_backup_definition_workspace_serial_number_qm = 
	    current_backup_definition_workspace_serial_number_qm_new_value;
    Current_backup_definition_workspace_qm = Nil;
    return VALUES_1(Current_backup_definition_workspace_qm);
}

/* FIND-DEFINITION-CONFLICT-WORKSPACE */
Object find_definition_conflict_workspace(definition_1,definition_2)
    Object definition_1, definition_2;
{
    Object frame_representation_1, ab_loop_list_, workspace_1_qm, ab_loop_it_;
    Object frame_representation_2, ab_loop_list__1, workspace_2_qm;

    x_note_fn_call(130,26);
    frame_representation_1 = Nil;
    ab_loop_list_ = ISVREF(definition_1,(SI_Long)9L);
    workspace_1_qm = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame_representation_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    workspace_1_qm = get_workspace_if_any(frame_representation_1);
    frame_representation_2 = Nil;
    ab_loop_list__1 = ISVREF(definition_2,(SI_Long)9L);
    workspace_2_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    frame_representation_2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    workspace_2_qm = get_workspace_if_any(frame_representation_2);
    if (EQ(workspace_1_qm,workspace_2_qm)) {
	ab_loop_it_ = workspace_1_qm;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qsuperiors_first_partial_ordering_of_slot_denotations_to_automerge;  /* superiors-first-partial-ordering-of-slot-denotations-to-automerge */

/* MERGE-DIFFERING-SLOTS-IN-DEFINITIONS */
Object merge_differing_slots_in_definitions(old_class_definition,
	    new_class_definition,differing_slots)
    Object old_class_definition, new_class_definition, differing_slots;
{
    Object slot_denotations, temp, remaining_differing_slots_qm;

    x_note_fn_call(130,27);
    slot_denotations = sort_list(copy_for_slot_value(differing_slots),
	    SYMBOL_FUNCTION(Qsuperiors_first_partial_ordering_of_slot_denotations_to_automerge),
	    Nil);
    temp = merge_differing_slots_in_definitions_1(old_class_definition,
	    new_class_definition,slot_denotations,Nil);
    reclaim_slot_value(slot_denotations);
    remaining_differing_slots_qm = temp;
    if (remaining_differing_slots_qm)
	return merge_differing_slots_in_definitions_1(old_class_definition,
		new_class_definition,remaining_differing_slots_qm,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_17;  /* "Unable to merge the ~NN attribute between definitions ~NF and ~NF." */

/* MERGE-DIFFERING-SLOTS-IN-DEFINITIONS-1 */
Object merge_differing_slots_in_definitions_1(old_class_definition,
	    new_class_definition,differing_slots,warn_p)
    Object old_class_definition, new_class_definition, differing_slots, warn_p;
{
    Object slot_denotation, ab_loop_list_, class_qualifier_qm, slot_name;
    Object text_representation_for_slot_value, slot_description;
    Object write_floats_accurately_p;
    Declare_special(1);

    x_note_fn_call(130,28);
    slot_denotation = Nil;
    ab_loop_list_ = differing_slots;
    class_qualifier_qm = Nil;
    slot_name = Nil;
    text_representation_for_slot_value = Nil;
    slot_description = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_denotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_qualifier_qm = CONSP(slot_denotation) ? 
	    M_CAR(M_CDR(slot_denotation)) : Nil;
    slot_name = CONSP(slot_denotation) ? 
	    M_CAR(M_CDR(M_CDR(slot_denotation))) : slot_denotation;
    write_floats_accurately_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_floats_accurately_p,Qwrite_floats_accurately_p,write_floats_accurately_p,
	    0);
      text_representation_for_slot_value = 
	      make_text_representation_for_slot_value(3,
	      old_class_definition,slot_name,class_qualifier_qm);
    POP_SPECIAL();
    slot_description = 
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(new_class_definition,(SI_Long)1L),class_qualifier_qm);
    if ( !TRUEP(parse_text_for_slot(3,text_representation_for_slot_value,
	    new_class_definition,slot_description))) {
	if (warn_p)
	    notify_user_of_conflicts(4,string_constant_17,slot_denotation,
		    old_class_definition,new_class_definition);
    }
    goto next_loop;
  end_loop:
    return find_differences_in_frames_if_any(4,old_class_definition,
	    new_class_definition,Nil,T);
    return VALUES_1(Qnil);
}

static Object list_constant_3;     /* # */

/* FIND-COMPLEX-DIFFERENCES-IN-ATTRIBUTE-SPECS-IF-ANY */
Object find_complex_differences_in_attribute_specs_if_any(old_class_definition,
	    new_class_definition)
    Object old_class_definition, new_class_definition;
{
    Object the_most_general_type, old_attribute_descriptions_for_class;
    Object new_attribute_description, ab_loop_list_;
    Object old_attribute_description_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_attribute_name, description, ab_loop_list__1;
    Object temp, temp_2;
    char temp_1;

    x_note_fn_call(130,29);
    the_most_general_type = list_constant_3;
    old_attribute_descriptions_for_class = ISVREF(old_class_definition,
	    (SI_Long)22L);
    new_attribute_description = Nil;
    ab_loop_list_ = ISVREF(new_class_definition,(SI_Long)22L);
    old_attribute_description_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    new_attribute_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_attribute_name = CAR(new_attribute_description);
    description = Nil;
    ab_loop_list__1 = old_attribute_descriptions_for_class;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    description = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(new_attribute_name,CAR(description))) {
	old_attribute_description_qm = description;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    old_attribute_description_qm = Qnil;
  end_1:;
    if (old_attribute_description_qm) {
	temp = attribute_type_specification(new_attribute_description);
	temp_1 = EQUAL(temp,the_most_general_type);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = attribute_type_specification(old_attribute_description_qm);
	temp_1 = EQUAL(temp,the_most_general_type);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = CDDR(old_attribute_description_qm);
	temp = CDDR(new_attribute_description);
	temp_1 =  !TRUEP(slot_value_equal_p(CAR(temp_2),CAR(temp)));
	if (temp_1);
	else {
	    temp_2 = CDDDDR(old_attribute_description_qm);
	    temp = CDDDDR(new_attribute_description);
	    temp_1 =  !EQUAL(temp_2,temp);
	}
	if (temp_1) {
	    temp = CDDDR(old_attribute_description_qm);
	    temp_1 =  !TRUEP(CAR(temp));
	    if (temp_1);
	    else {
		temp_2 = CDDDR(old_attribute_description_qm);
		temp = CDDDR(new_attribute_description);
		temp_1 =  !EQ(CAR(temp_2),CAR(temp));
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	ab_loopvar__2 = slot_value_cons_1(CAR(new_attribute_description),Nil);
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

Object Partial_ordering_of_slot_denotations_with_superiors_first = UNBOUND;

/* SUPERIORS-FIRST-PARTIAL-ORDERING-OF-SLOT-DENOTATIONS-TO-AUTOMERGE */
Object superiors_first_partial_ordering_of_slot_denotations_to_automerge(slot_denotation_1,
	    slot_denotation_2)
    Object slot_denotation_1, slot_denotation_2;
{
    Object slot_name_1, slot_denotation, ab_loop_list_, ab_loop_iter_flag_;
    Object temp, slot_name_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(130,30);
    slot_name_1 = CONSP(slot_denotation_1) ? 
	    M_CAR(M_CDR(M_CDR(slot_denotation_1))) : slot_denotation_1;
    slot_denotation = Nil;
    ab_loop_list_ = Partial_ordering_of_slot_denotations_with_superiors_first;
    index_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_denotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if (EQ(CONSP(slot_denotation) ? M_CAR(M_CDR(M_CDR(slot_denotation))) : 
	    slot_denotation,slot_name_1)) {
	temp = FIX(index_1);
	goto end_1;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    slot_name_2 = CONSP(slot_denotation_2) ? 
	    M_CAR(M_CDR(M_CDR(slot_denotation_2))) : slot_denotation_2;
    slot_denotation = Nil;
    ab_loop_list_ = Partial_ordering_of_slot_denotations_with_superiors_first;
    index_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    slot_denotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if (EQ(CONSP(slot_denotation) ? M_CAR(M_CDR(M_CDR(slot_denotation))) : 
	    slot_denotation,slot_name_2)) {
	temp_1 = FIX(index_1);
	goto end_2;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    temp_1 = Qnil;
  end_2:;
    if (temp_1);
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(NUM_LT(temp,temp_1) ? T : Nil);
}

/* GET-SLOT-VALUES-TO-SAVE-FOR-CONFLICT-RESOLUTION */
Object get_slot_values_to_save_for_conflict_resolution(old_class_definition,
	    new_class_definition)
    Object old_class_definition, new_class_definition;
{
    Object new_class, new_class_class_description, old_class;
    Object old_class_class_description, value_to_return_qm;
    Object new_slot_description, ab_loop_list_, temp, old_slot_description_qm;
    Object losing_slot_temporarily_qm, gaining_slot_temporarily_qm;
    Object defining_class_for_slot_description_to_set_qm, pretty_slot_name;
    Object defining_class, old_type_specification, scope_conses, ab_loopvar_;
    Object class_1, class_description, class_slot_description;
    Object new_slot_init_form, user_vector_slot_index_qm, ab_loopvar__1;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, instance;
    Object current_slot_value, ab_loopvar__5, ab_loopvar__6, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loop_it_;
    Object sub_class_bit_vector, attribute_table_display_qm, svref_arg_1;
    Object instances_and_slot_values_list_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(130,31);
    new_class = ISVREF(new_class_definition,(SI_Long)20L);
    new_class_class_description = 
	    lookup_global_or_kb_specific_property_value(new_class,
	    Class_description_gkbprop);
    old_class = ISVREF(old_class_definition,(SI_Long)20L);
    old_class_class_description = 
	    lookup_global_or_kb_specific_property_value(old_class,
	    Class_description_gkbprop);
    value_to_return_qm = Nil;
    new_slot_description = Nil;
    ab_loop_list_ = ISVREF(new_class_class_description,(SI_Long)6L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    new_slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(new_slot_description,(SI_Long)8L)) {
	if ( ! !TRUEP(ISVREF(new_slot_description,(SI_Long)8L))) {
	    temp = ISVREF(new_slot_description,(SI_Long)3L);
	    temp_1 =  !EQ(temp,
		    ISVREF(get_slot_description_of_class_description_function(ISVREF(new_slot_description,
		    (SI_Long)2L),new_class_class_description,Nil),
		    (SI_Long)3L));
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	old_slot_description_qm = 
		get_slot_description_of_class_description_function(ISVREF(new_slot_description,
		(SI_Long)2L),old_class_class_description,Nil);
	if (old_slot_description_qm) {
	    losing_slot_temporarily_qm = EQ(ISVREF(old_slot_description_qm,
		    (SI_Long)3L),old_class) ? ( 
		    !EQ(ISVREF(new_slot_description,(SI_Long)3L),
		    new_class) ? T : Nil) : Qnil;
	    gaining_slot_temporarily_qm = EQ(ISVREF(new_slot_description,
		    (SI_Long)3L),new_class) ? ( 
		    !EQ(ISVREF(old_slot_description_qm,(SI_Long)3L),
		    old_class) ? T : Nil) : Qnil;
	    defining_class_for_slot_description_to_set_qm = 
		    losing_slot_temporarily_qm ? old_class : 
		    gaining_slot_temporarily_qm ? 
		    ISVREF(old_slot_description_qm,(SI_Long)3L) : Nil;
	    if (defining_class_for_slot_description_to_set_qm) {
		pretty_slot_name = ISVREF(new_slot_description,(SI_Long)2L);
		defining_class = ISVREF(new_slot_description,(SI_Long)3L);
		old_type_specification = ISVREF(old_slot_description_qm,
			(SI_Long)5L);
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar_ = new_class;
		class_1 = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  class_description = Nil;
		  class_slot_description = Nil;
		  new_slot_init_form = Nil;
		  user_vector_slot_index_qm = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loopvar__2 = Nil;
		  ab_loopvar__3 = Nil;
		  ab_loopvar_ = collect_subclasses(ab_loopvar_);
		next_loop_1:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_1;
		  temp = M_CAR(ab_loopvar_);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  class_1 = temp;
		  class_description = 
			  lookup_global_or_kb_specific_property_value(class_1,
			  Class_description_gkbprop);
		  class_slot_description = EQ(class_1,new_class) ? 
			  new_slot_description : 
			  get_slot_description_of_class_description_function(pretty_slot_name,
			  class_description,defining_class);
		  new_slot_init_form = ISVREF(class_slot_description,
			  (SI_Long)6L);
		  user_vector_slot_index_qm = 
			  ISVREF(class_slot_description,(SI_Long)8L);
		  ab_loopvar__4 = 
			  lookup_kb_specific_property_value(class_1,
			  Instances_specific_to_this_class_kbprop);
		  instance = Nil;
		  current_slot_value = Nil;
		  ab_loopvar__3 = Nil;
		  ab_loopvar__5 = Nil;
		  ab_loopvar__6 = Nil;
		next_loop_2:
		  if ( !TRUEP(ab_loopvar__4))
		      goto end_loop_2;
		  instance = ab_loopvar__4;
		  ab_loopvar__4 = ISVREF(ab_loopvar__4,(SI_Long)6L);
		  current_slot_value = get_slot_description_value(instance,
			  class_slot_description);
		  if ( !EQ(current_slot_value,new_slot_init_form) && 
			  slot_value_conforms_to_type_specification_p(current_slot_value,
			  old_type_specification)) {
		      gensymed_symbol = ACCESS_ONCE(ISVREF(instance,
			      (SI_Long)14L));
		      gensymed_symbol = gensymed_symbol ? 
			      ACCESS_ONCE(ISVREF(gensymed_symbol,
			      (SI_Long)4L)) : Nil;
		      ab_queue_form_ = gensymed_symbol;
		      ab_next_queue_element_ = Nil;
		      subblock = Nil;
		      ab_loop_it_ = Nil;
		      if (ab_queue_form_)
			  ab_next_queue_element_ = 
				  constant_queue_next(ISVREF(ab_queue_form_,
				  (SI_Long)2L),ab_queue_form_);
		    next_loop_3:
		      if ( !TRUEP(ab_next_queue_element_))
			  goto end_loop_3;
		      subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
		      ab_next_queue_element_ = 
			      constant_queue_next(ab_next_queue_element_,
			      ab_queue_form_);
		      sub_class_bit_vector = ISVREF(ISVREF(subblock,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Table_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
		      ab_loop_it_ = (temp_1 ? 
			      TRUEP(attribute_display_p(subblock)) : 
			      TRUEP(Nil)) ? 
			      get_text_cell_representing_slot_if_any(4,
			      subblock,instance,pretty_slot_name,Nil) : Nil;
		      if (ab_loop_it_) {
			  attribute_table_display_qm = ab_loop_it_;
			  goto end_1;
		      }
		      goto next_loop_3;
		    end_loop_3:
		      attribute_table_display_qm = Qnil;
		    end_1:;
		      temp = frame_list_3(instance,current_slot_value,
			      attribute_table_display_qm);
		      svref_arg_1 = ISVREF(instance,(SI_Long)0L);
		      SVREF(svref_arg_1,user_vector_slot_index_qm) = Nil;
		      ab_loopvar__6 = frame_cons_1(temp,Nil);
		      if (ab_loopvar__5)
			  M_CDR(ab_loopvar__5) = ab_loopvar__6;
		      else
			  ab_loopvar__3 = ab_loopvar__6;
		      ab_loopvar__5 = ab_loopvar__6;
		  }
		  goto next_loop_2;
		end_loop_2:
		  goto end_2;
		  ab_loopvar__3 = Qnil;
		end_2:;
		  if (ab_loopvar__3) {
		      if (ab_loopvar__2)
			  M_CDR(ab_loopvar__2) = ab_loopvar__3;
		      else
			  ab_loopvar__1 = ab_loopvar__3;
		      ab_loopvar__2 = last(ab_loopvar__3,_);
		  }
		  goto next_loop_1;
		end_loop_1:
		  instances_and_slot_values_list_qm = ab_loopvar__1;
		  goto end_3;
		  instances_and_slot_values_list_qm = Qnil;
		end_3:;
		POP_SPECIAL();
	    }
	    else
		instances_and_slot_values_list_qm = Nil;
	    if (instances_and_slot_values_list_qm) {
		temp = value_to_return_qm;
		value_to_return_qm = nconc2(temp,
			frame_cons_1(nconc2(frame_list_2(ISVREF(new_slot_description,
			(SI_Long)2L),
			defining_class_for_slot_description_to_set_qm),
			frame_cons_1(instances_and_slot_values_list_qm,
			Nil)),Nil));
	    }
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(value_to_return_qm);
}

static Object Qframe;              /* frame */

/* REINSTATE-NON-DEFAULT-VALUES-AFTER-MERGE */
Object reinstate_non_default_values_after_merge(preserved_non_default_values)
    Object preserved_non_default_values;
{
    Object attribute_information, pretty_slot_name, defining_class;
    Object list_of_instances_and_values, frame_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2, instance_and_values, instance, slot_value;
    Object attribute_display_qm, class_description_slot, slot_description;
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object ab_loop_it_, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(130,32);
    attribute_information = Nil;
    pretty_slot_name = Nil;
    defining_class = Nil;
    list_of_instances_and_values = Nil;
  next_loop:
    if ( !TRUEP(preserved_non_default_values))
	goto end_loop;
    frame_pop_store = Nil;
    cons_1 = preserved_non_default_values;
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
    preserved_non_default_values = next_cons;
    attribute_information = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = attribute_information;
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
    attribute_information = next_cons;
    pretty_slot_name = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = attribute_information;
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
    attribute_information = next_cons;
    defining_class = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = attribute_information;
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
    attribute_information = next_cons;
    list_of_instances_and_values = frame_pop_store;
    instance_and_values = Nil;
    instance = Nil;
    slot_value = Nil;
    attribute_display_qm = Nil;
    class_description_slot = Nil;
    slot_description = Nil;
  next_loop_1:
    if ( !TRUEP(list_of_instances_and_values))
	goto end_loop_1;
    frame_pop_store = Nil;
    cons_1 = list_of_instances_and_values;
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
    list_of_instances_and_values = next_cons;
    instance_and_values = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = instance_and_values;
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
    instance_and_values = next_cons;
    instance = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = instance_and_values;
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
    instance_and_values = next_cons;
    slot_value = frame_pop_store;
    frame_pop_store = Nil;
    cons_1 = instance_and_values;
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
    instance_and_values = next_cons;
    attribute_display_qm = frame_pop_store;
    class_description_slot = ISVREF(instance,(SI_Long)1L);
    slot_description = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    class_description_slot,defining_class);
    change_slot_description_value_function(instance,slot_description,
	    slot_value,Nil,Nil);
    if (attribute_display_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(instance,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	ab_loop_it_ = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_2:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_2;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
	ab_loop_it_ = (temp_1 ? TRUEP(attribute_display_p(subblock)) : 
		TRUEP(Nil)) ? get_text_cell_representing_slot_if_any(4,
		subblock,instance,pretty_slot_name,Nil) : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(Qnil);
      end_1:;
	if ( !temp_1)
	    add_slot_representation_as_attribute_display(3,instance,
		    pretty_slot_name,defining_class);
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object list_constant_4;     /* # */

static Object string_constant_18;  /* "Warning: the attempt failed to automatically resolve ~
				    *                    the old and new definitions, ~NF and ~NF because they ~
				    *                    are not of compatible classes.  Neither definition will be deleted."
				    */

static Object string_constant_19;  /* "Warning: the attempt failed to automatically resolve ~
				    *                         the old and new definitions, ~NF and ~NF; they ~
				    *                         still differ in ~d slots!  So neither definition will be deleted."
				    */

static Object string_constant_20;  /* "Automatically deleting definition ~NF, whose instances, ~
				    *                                    if any, were merged into the class defined by ~NF."
				    */

static Object string_constant_21;  /* "Automatically deleting conflict workspace ~NF." */

static Object string_constant_22;  /* "Warning: Final attempt to merge ~NF with ~NF failed!" */

static Object string_constant_23;  /* "Automatically deleting the incomplete class-definition ~NF in favor of ~
				    *           the class-definition ~NF from a required module."
				    */

/* RESOLVE-ONE-CLASS-NAME-CONFLICT */
Object resolve_one_class_name_conflict(old_class_definition,
	    new_class_definition)
    Object old_class_definition, new_class_definition;
{
    Object sub_class_bit_vector, definition_classes_are_compatible_qm;
    Object old_definition_class_name, new_definition_class_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol_3, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, old_definition_defines_class_qm;
    Object new_definition_defines_class_qm, both_definitions_define_classes_qm;
    volatile Object denotations_of_differing_slots;
    Object preserved_non_default_values_qm;
    volatile Object irreconcilable_slots_qm;
    Object successful_resolution_qm, class_name_conflict_workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(130,33);
    SAVE_STACK();
    sub_class_bit_vector = ISVREF(ISVREF(old_class_definition,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
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
	sub_class_bit_vector = ISVREF(ISVREF(new_class_definition,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
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
	    definition_classes_are_compatible_qm = (SI_Long)0L < 
		    gensymed_symbol ? T : Nil;
	}
	else
	    definition_classes_are_compatible_qm = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(old_class_definition,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_definition_class_description,
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_class_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_definition_class_description,
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
		definition_classes_are_compatible_qm = (SI_Long)0L < 
			gensymed_symbol ? T : Nil;
	    }
	    else
		definition_classes_are_compatible_qm = Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(old_class_definition,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_definition_class_description,
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(new_class_definition,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Message_definition_class_description,
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
		    definition_classes_are_compatible_qm = (SI_Long)0L < 
			    gensymed_symbol ? T : Nil;
		}
		else
		    definition_classes_are_compatible_qm = Nil;
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(old_class_definition,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
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
		if (temp)
		    definition_classes_are_compatible_qm =  
			    !TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(new_class_definition)) 
			    ? T : Nil;
		else
		    definition_classes_are_compatible_qm = Nil;
	    }
	}
    }
    old_definition_class_name = ISVREF(old_class_definition,(SI_Long)20L);
    new_definition_class_name = ISVREF(new_class_definition,(SI_Long)20L);
    if (SYMBOLP(old_definition_class_name)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = old_definition_class_name;
	key_hash_value = SXHASH_SYMBOL_1(old_definition_class_name) & 
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol_3)) {
	    gensymed_symbol_3 = old_definition_class_name;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_5 = new_cons;
	    }
	    else
		gensymed_symbol_5 = Nil;
	    if ( !TRUEP(gensymed_symbol_5))
		gensymed_symbol_5 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_5) = head;
	    M_CDR(gensymed_symbol_5) = tail;
	    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
	    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
	    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
	    gensymed_symbol_3 = set_skip_list_entry(temp_1,
		    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,temp_2,
		    gensymed_symbol_4);
	}
	global_properties = gensymed_symbol_3;
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	old_definition_defines_class_qm = resulting_value;
    }
    else
	old_definition_defines_class_qm = Nil;
    if (SYMBOLP(new_definition_class_name)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = new_definition_class_name;
	key_hash_value = SXHASH_SYMBOL_1(new_definition_class_name) & 
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_14:
	if ( !TRUEP(marked))
	    goto end_loop_13;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol_3)) {
	    gensymed_symbol_3 = new_definition_class_name;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_5 = new_cons;
	    }
	    else
		gensymed_symbol_5 = Nil;
	    if ( !TRUEP(gensymed_symbol_5))
		gensymed_symbol_5 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_5) = head;
	    M_CDR(gensymed_symbol_5) = tail;
	    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
	    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
	    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
	    gensymed_symbol_3 = set_skip_list_entry(temp_1,
		    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,temp_2,
		    gensymed_symbol_4);
	}
	global_properties = gensymed_symbol_3;
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_17:
	if ( !TRUEP(marked))
	    goto end_loop_16;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_20:
	    if ( !TRUEP(marked))
		goto end_loop_19;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_23:
	    if ( !TRUEP(marked))
		goto end_loop_22;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
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
	new_definition_defines_class_qm = resulting_value;
    }
    else
	new_definition_defines_class_qm = Nil;
    both_definitions_define_classes_qm = old_definition_defines_class_qm ? 
	    new_definition_defines_class_qm : Qnil;
    if (both_definitions_define_classes_qm) {
	denotations_of_differing_slots = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(1)) {
	    denotations_of_differing_slots = 
		    find_differences_in_frames_if_any(4,
		    old_class_definition,new_class_definition,Nil,
		    definition_classes_are_compatible_qm);
	    if (EQUAL(denotations_of_differing_slots,list_constant_4)) {
		notify_user_of_conflicts(3,string_constant_18,
			old_class_definition,new_class_definition);
		SAVE_VALUES(VALUES_1(Nil));
	    }
	    else {
		preserved_non_default_values_qm = Qunbound_in_protected_let;
		irreconcilable_slots_qm = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    preserved_non_default_values_qm = 
			    memq_function(Qclass_specific_attributes,
			    denotations_of_differing_slots) && 
			    memq_function(Qdirect_superiors_of_defined_class,
			    denotations_of_differing_slots) ? 
			    get_slot_values_to_save_for_conflict_resolution(old_class_definition,
			    new_class_definition) : Nil;
		    irreconcilable_slots_qm = 
			    merge_differing_slots_in_definitions(old_class_definition,
			    new_class_definition,
			    denotations_of_differing_slots);
		    if (irreconcilable_slots_qm) {
			highlight_differing_slots_in_definitions(old_class_definition,
				new_class_definition,irreconcilable_slots_qm);
			notify_user_of_conflicts(4,string_constant_19,
				old_class_definition,new_class_definition,
				length(irreconcilable_slots_qm));
			SAVE_VALUES(VALUES_1(Nil));
		    }
		    else {
			successful_resolution_qm = 
				resolve_by_merging_all_instances(old_definition_class_name,
				new_class_definition,
				new_definition_class_name);
			if (successful_resolution_qm) {
			    class_name_conflict_workspace_qm = 
				    get_instance_with_name_if_any(Qkb_workspace,
				    make_name_for_class_name_conflict_workspace(old_definition_class_name));
			    notify_user_of_conflicts(3,string_constant_20,
				    new_class_definition,old_class_definition);
			    delete_frame(new_class_definition);
			    if (class_name_conflict_workspace_qm && 
				    EQ(class_name_conflict_workspace_qm,
				    find_definition_conflict_workspace(old_class_definition,
				    new_class_definition))) {
				notify_user_of_conflicts(2,
					string_constant_21,
					class_name_conflict_workspace_qm);
				delete_frame(class_name_conflict_workspace_qm);
			    }
			    if (preserved_non_default_values_qm)
				reinstate_non_default_values_after_merge(preserved_non_default_values_qm);
			    SAVE_VALUES(VALUES_1(T));
			}
			else {
			    notify_user_of_conflicts(3,string_constant_22,
				    old_class_definition,new_class_definition);
			    SAVE_VALUES(VALUES_1(Nil));
			}
		    }
		}
		POP_UNWIND_PROTECT(0);
		if (irreconcilable_slots_qm) {
		    if ( !EQ(irreconcilable_slots_qm,
			    Qunbound_in_protected_let))
			reclaim_slot_value(irreconcilable_slots_qm);
		}
		CONTINUE_UNWINDING(0);
	    }
	}
	POP_UNWIND_PROTECT(1);
	if (denotations_of_differing_slots) {
	    if ( !EQ(denotations_of_differing_slots,Qunbound_in_protected_let))
		reclaim_slot_value(denotations_of_differing_slots);
	}
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else if ( !TRUEP(new_definition_defines_class_qm)) {
	notify_user_of_conflicts(3,string_constant_23,new_class_definition,
		old_class_definition);
	delete_frame(new_class_definition);
	RESTORE_STACK();
	return VALUES_1(T);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object string_constant_24;  /* "merge all instances and subclasses into definition for ~a" */

static Object Qchange;             /* change */

/* RESOLVE-BY-MERGING-ALL-INSTANCES */
Object resolve_by_merging_all_instances(old_name,definition,new_name)
    Object old_name, definition, new_name;
{
    Object temp;

    x_note_fn_call(130,34);
    temp = convert_text_string_to_text(tformat_text_string(2,
	    string_constant_24,old_name));
    if (parse_text_for_slot(3,temp,definition,
	    get_slot_description_of_class_description_function(Qchange,
	    ISVREF(definition,(SI_Long)1L),Qclass_definition)))
	return VALUES_1( !TRUEP(instantiated_class_p(new_name)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* HIGHLIGHT-DIFFERING-SLOTS-IN-DEFINITIONS */
Object highlight_differing_slots_in_definitions(class_definition_1,
	    class_definition_2,differing_slots)
    Object class_definition_1, class_definition_2, differing_slots;
{
    Object slot_denotation, ab_loop_list_, class_qualifier_qm, slot_name;

    x_note_fn_call(130,35);
    slot_denotation = Nil;
    ab_loop_list_ = differing_slots;
    class_qualifier_qm = Nil;
    slot_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_denotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_qualifier_qm = CONSP(slot_denotation) ? 
	    M_CAR(M_CDR(slot_denotation)) : Nil;
    slot_name = CONSP(slot_denotation) ? 
	    M_CAR(M_CDR(M_CDR(slot_denotation))) : slot_denotation;
    highlight_or_unhighlight_for_slot(5,class_definition_1,slot_name,
	    class_qualifier_qm,Nil,Nil);
    highlight_or_unhighlight_for_slot(5,class_definition_2,slot_name,
	    class_qualifier_qm,Nil,Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object All_definitional_classes = UNBOUND;

/* DEFINITIONAL-CLASS-P */
Object definitional_class_p(class_1)
    Object class_1;
{
    Object definitional_class, ab_loop_list_, ab_loop_it_, gensymed_symbol;

    x_note_fn_call(130,36);
    definitional_class = Nil;
    ab_loop_list_ = All_definitional_classes;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    definitional_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    ab_loop_it_ = gensymed_symbol ? memq_function(definitional_class,
	    ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Record_of_definitional_name_conflicts_qm, Qrecord_of_definitional_name_conflicts_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Record_definitional_name_conflicts_qm, Qrecord_definitional_name_conflicts_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_load_case_qm, Qkb_load_case_qm);

static Object Qab_method;          /* method */

static Object list_constant_5;     /* # */

/* RECORD-NAME-CONFLICT-IF-NECESSARY */
Object record_name_conflict_if_necessary(frame,name_or_class_name_for_frame)
    Object frame, name_or_class_name_for_frame;
{
    Object gensymed_symbol, sub_class_bit_vector, name_qm, class_1, count_1;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, method, xa, ya;
    Object ab_loop_list_, definitional_class_for_frame, name_to_match;
    Object base_kb_instance_with_same_name_qm, temp_1;
    Object frame_or_frames_with_this_name, frame_with_same_name;
    Object ab_loop_list__1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,37);
    if (name_or_class_name_for_frame &&  !TRUEP(Kb_load_case_qm) && 
	    Record_definitional_name_conflicts_qm && 
	    definitional_class_p(ISVREF(ISVREF(frame,(SI_Long)1L),
	    (SI_Long)1L))) {
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Method_declaration_class_description,
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
		name_qm = Nil;
		class_1 = Nil;
		count_1 = Nil;
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		method = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(Qab_method);
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
		  method = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  temp = EQ(method,frame);
		  if (temp);
		  else {
		      gensymed_symbol = ISVREF(method,(SI_Long)3L);
		      temp = SIMPLE_VECTOR_P(method) ? EQ(ISVREF(method,
			      (SI_Long)1L),Qavailable_frame_vector) : 
			      TRUEP(Qnil);
		      if (temp);
		      else
			  temp = FIXNUMP(gensymed_symbol) ? 
				  IFIX(gensymed_symbol) == (SI_Long)-1L : 
				  TRUEP(Nil);
		      if (temp);
		      else if (FIXNUMP(Current_frame_serial_number_before_reading))
			  temp = FIXNUMP(gensymed_symbol) ? 
				  FIXNUM_LT(Current_frame_serial_number_before_reading,
				  gensymed_symbol) : TRUEP(T);
		      else if (FIXNUMP(gensymed_symbol))
			  temp = TRUEP(Nil);
		      else {
			  xa = 
				  M_CAR(Current_frame_serial_number_before_reading);
			  ya = M_CAR(gensymed_symbol);
			  temp = FIXNUM_LT(xa,ya);
			  if (temp);
			  else
			      temp = FIXNUM_EQ(xa,ya) ? 
				      FIXNUM_LT(M_CDR(Current_frame_serial_number_before_reading),
				      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		      }
		  }
		  if ( !temp) {
		      result = check_for_matching_methods(frame,
			      name_or_class_name_for_frame,method);
		      MVS_3(result,name_qm,class_1,count_1);
		      temp = TRUEP(name_qm);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      note_definitional_name_conflict(5,method,frame,
			      name_qm,class_1,count_1);
		      goto end_1;
		  }
		  goto next_loop;
		end_loop_1:
		end_1:;
		POP_SPECIAL();
	    }
	    else {
		class_1 = Nil;
		ab_loop_list_ = All_definitional_classes;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		class_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
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
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    definitional_class_for_frame = class_1;
		    goto end_2;
		}
		goto next_loop_2;
	      end_loop_2:
		definitional_class_for_frame = Qnil;
	      end_2:;
		name_qm = Nil;
		ab_loop_list_ = CONSP(name_or_class_name_for_frame) ? 
			name_or_class_name_for_frame : list_constant_5;
		name_to_match = Nil;
		base_kb_instance_with_same_name_qm = Nil;
	      next_loop_3:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_3;
		name_qm = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		temp_1 = name_qm;
		if (temp_1);
		else
		    temp_1 = name_or_class_name_for_frame;
		name_to_match = temp_1;
		frame_or_frames_with_this_name = 
			lookup_kb_specific_property_value(name_to_match,
			Frame_or_frames_with_this_name_kbprop);
		if (frame_or_frames_with_this_name) {
		    if (ATOM(frame_or_frames_with_this_name)) {
			gensymed_symbol = 
				ISVREF(frame_or_frames_with_this_name,
				(SI_Long)3L);
			temp = 
				SIMPLE_VECTOR_P(frame_or_frames_with_this_name) 
				? EQ(ISVREF(frame_or_frames_with_this_name,
				(SI_Long)1L),Qavailable_frame_vector) : 
				TRUEP(Qnil);
			if (temp);
			else
			    temp = FIXNUMP(gensymed_symbol) ? 
				    IFIX(gensymed_symbol) == (SI_Long)-1L :
				     TRUEP(Nil);
			if (temp);
			else if (FIXNUMP(Current_frame_serial_number_before_reading))
			    temp = FIXNUMP(gensymed_symbol) ? 
				    FIXNUM_LT(Current_frame_serial_number_before_reading,
				    gensymed_symbol) : TRUEP(T);
			else if (FIXNUMP(gensymed_symbol))
			    temp = TRUEP(Nil);
			else {
			    xa = 
				    M_CAR(Current_frame_serial_number_before_reading);
			    ya = M_CAR(gensymed_symbol);
			    temp = FIXNUM_LT(xa,ya);
			    if (temp);
			    else
				temp = FIXNUM_EQ(xa,ya) ? 
					FIXNUM_LT(M_CDR(Current_frame_serial_number_before_reading),
					M_CDR(gensymed_symbol)) : TRUEP(Qnil);
			}
			if ( !temp) {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(definitional_class_for_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(frame_or_frames_with_this_name,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol,
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
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			base_kb_instance_with_same_name_qm = temp ? 
				frame_or_frames_with_this_name : Nil;
		    }
		    else {
			frame_with_same_name = Nil;
			ab_loop_list__1 = frame_or_frames_with_this_name;
		      next_loop_4:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_4;
			frame_with_same_name = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			gensymed_symbol = ISVREF(frame_with_same_name,
				(SI_Long)3L);
			temp = SIMPLE_VECTOR_P(frame_with_same_name) ? 
				EQ(ISVREF(frame_with_same_name,
				(SI_Long)1L),Qavailable_frame_vector) : 
				TRUEP(Qnil);
			if (temp);
			else
			    temp = FIXNUMP(gensymed_symbol) ? 
				    IFIX(gensymed_symbol) == (SI_Long)-1L :
				     TRUEP(Nil);
			if (temp);
			else if (FIXNUMP(Current_frame_serial_number_before_reading))
			    temp = FIXNUMP(gensymed_symbol) ? 
				    FIXNUM_LT(Current_frame_serial_number_before_reading,
				    gensymed_symbol) : TRUEP(T);
			else if (FIXNUMP(gensymed_symbol))
			    temp = TRUEP(Nil);
			else {
			    xa = 
				    M_CAR(Current_frame_serial_number_before_reading);
			    ya = M_CAR(gensymed_symbol);
			    temp = FIXNUM_LT(xa,ya);
			    if (temp);
			    else
				temp = FIXNUM_EQ(xa,ya) ? 
					FIXNUM_LT(M_CDR(Current_frame_serial_number_before_reading),
					M_CDR(gensymed_symbol)) : TRUEP(Qnil);
			}
			if ( !temp) {
			    gensymed_symbol = 
				    lookup_global_or_kb_specific_property_value(definitional_class_for_frame,
				    Class_description_gkbprop);
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(ISVREF(frame_with_same_name,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol,
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
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    base_kb_instance_with_same_name_qm = 
				    frame_with_same_name;
			    goto end_3;
			}
			goto next_loop_4;
		      end_loop_4:
			base_kb_instance_with_same_name_qm = Qnil;
		      end_3:;
		    }
		}
		else
		    base_kb_instance_with_same_name_qm = Nil;
		if (base_kb_instance_with_same_name_qm) {
		    note_definitional_name_conflict(3,
			    base_kb_instance_with_same_name_qm,frame,
			    name_to_match);
		    goto end_4;
		}
		goto next_loop_3;
	      end_loop_3:
	      end_4:;
	    }
	}
    }
    return VALUES_1(Nil);
}

/* NOTE-DEFINITIONAL-NAME-CONFLICT */
Object note_definitional_name_conflict varargs_1(int, n)
{
    Object base_kb_instance_with_same_name, merge_kb_instance_with_same_name;
    Object name_in_common;
    Object class_in_common_in_method_case_qm;
    Object common_arglist_length_in_method_case_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,38);
    INIT_ARGS_nonrelocating();
    base_kb_instance_with_same_name = REQUIRED_ARG_nonrelocating();
    merge_kb_instance_with_same_name = REQUIRED_ARG_nonrelocating();
    name_in_common = REQUIRED_ARG_nonrelocating();
    class_in_common_in_method_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    common_arglist_length_in_method_case_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    temp = nconc2(slot_value_list_3(base_kb_instance_with_same_name,
	    merge_kb_instance_with_same_name,name_in_common),
	    class_in_common_in_method_case_qm ? 
	    slot_value_list_2(class_in_common_in_method_case_qm,
	    common_arglist_length_in_method_case_qm) : Nil);
    Record_of_definitional_name_conflicts_qm = slot_value_cons_1(temp,
	    Record_of_definitional_name_conflicts_qm);
    return VALUES_1(Record_of_definitional_name_conflicts_qm);
}

static Object Qrelation_instance_tree;  /* relation-instance-tree */

/* FIX-UP-RELATION-FRAME-REFERENCES-FOR-DEFINITION-CONFLICT */
Object fix_up_relation_frame_references_for_definition_conflict(base_kb_relation,
	    relation_to_be_deleted)
    Object base_kb_relation, relation_to_be_deleted;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, relation_instances;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, temp_1, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance, relation_frame_reference;
    Object ab_less_than_branch_qm_, ab_loop_list_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,39);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      relation_instances = Nil;
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
      relation_instances = ISVREF(block,(SI_Long)12L);
      if (CONSP(relation_instances) && EQ(M_CAR(relation_instances),
	      Qrelation_instance_tree)) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances;
	  ab_binary_tree_form_ = relation_instances;
	  gensymed_symbol = CDR(relation_instances);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    relation_frame_reference = Nil;
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
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
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
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
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    relation_instance = M_CDR(ab_entry_cons_);
	    relation_frame_reference = ISVREF(relation_instance,(SI_Long)1L);
	    if (EQ(relation_frame_reference,relation_to_be_deleted))
		SVREF(relation_instance,FIX((SI_Long)1L)) = base_kb_relation;
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
      }
      else {
	  relation_instance = Nil;
	  ab_loop_list_ = relation_instances;
	  relation_frame_reference = Nil;
	next_loop_4:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_4;
	  relation_instance = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  relation_frame_reference = M_CAR(M_CDR(relation_instance));
	  if (EQ(relation_frame_reference,relation_to_be_deleted))
	      M_SECOND(relation_instance) = base_kb_relation;
	  goto next_loop_4;
	end_loop_4:;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_25;  /* "Automatically deleting method ~A for ~
				    *                          class ~A because a previously-loaded method ~
				    *                          has the same name, is for the same class, and takes the same ~
				    *                          number of arguments (~d)."
				    */

static Object string_constant_26;  /* "Automatically deleting ~(~a~) ~a because a ~
				    *                          previously-loaded ~(~a~) has the same name."
				    */

static Object string_constant_27;  /* "WARNING: ~a ~a from the Basis KB no longer ~
				    *                           exists.  You probably have to start over, and ~
				    *                           resolve and merge and resolve conflicts by hand."
				    */

/* RESOLVE-DEFINITIONAL-NAME-CONFLICTS */
Object resolve_definitional_name_conflicts()
{
    Object resolving_definitional_name_conflicts_qm;
    Object reference_frame_serial_number, base_kb_instance_with_same_name;
    Object merge_kb_instance_with_same_name, name_in_common;
    Object class_in_common_in_method_case_qm;
    Object common_arglist_length_in_method_case_qm, ab_loop_list_;
    Object ab_loop_desetq_, temp, gensymed_symbol, xa, ya, class_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,40);
    if (Record_definitional_name_conflicts_qm) {
	resolving_definitional_name_conflicts_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Resolving_definitional_name_conflicts_qm,Qresolving_definitional_name_conflicts_qm,resolving_definitional_name_conflicts_qm,
		0);
	  reference_frame_serial_number = 
		  copy_frame_serial_number(Current_frame_serial_number);
	  base_kb_instance_with_same_name = Nil;
	  merge_kb_instance_with_same_name = Nil;
	  name_in_common = Nil;
	  class_in_common_in_method_case_qm = Nil;
	  common_arglist_length_in_method_case_qm = Nil;
	  ab_loop_list_ = Record_of_definitional_name_conflicts_qm;
	  ab_loop_desetq_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  base_kb_instance_with_same_name = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  merge_kb_instance_with_same_name = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  name_in_common = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  class_in_common_in_method_case_qm = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  common_arglist_length_in_method_case_qm = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = ISVREF(merge_kb_instance_with_same_name,
		  (SI_Long)3L);
	  temp_1 = SIMPLE_VECTOR_P(merge_kb_instance_with_same_name) ? 
		  EQ(ISVREF(merge_kb_instance_with_same_name,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp_1);
	  else
	      temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp_1);
	  else if (FIXNUMP(reference_frame_serial_number))
	      temp_1 = FIXNUMP(gensymed_symbol) ? 
		      FIXNUM_LT(reference_frame_serial_number,
		      gensymed_symbol) : TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp_1 = TRUEP(Nil);
	  else {
	      xa = M_CAR(reference_frame_serial_number);
	      ya = M_CAR(gensymed_symbol);
	      temp_1 = FIXNUM_LT(xa,ya);
	      if (temp_1);
	      else
		  temp_1 = FIXNUM_EQ(xa,ya) ? 
			  FIXNUM_LT(M_CDR(reference_frame_serial_number),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  if ( !temp_1) {
	      class_1 = ISVREF(ISVREF(merge_kb_instance_with_same_name,
		      (SI_Long)1L),(SI_Long)1L);
	      if (EQ(class_1,Qab_method))
		  notify_user_of_conflicts(4,string_constant_25,
			  name_in_common,class_in_common_in_method_case_qm,
			  common_arglist_length_in_method_case_qm);
	      else
		  notify_user_of_conflicts(4,string_constant_26,class_1,
			  name_in_common,class_1);
	      sub_class_bit_vector = 
		      ISVREF(ISVREF(merge_kb_instance_with_same_name,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Relation_class_description,(SI_Long)18L));
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
		  temp_1 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  fix_up_relation_frame_references_for_definition_conflict(base_kb_instance_with_same_name,
			  merge_kb_instance_with_same_name);
	      delete_frame(merge_kb_instance_with_same_name);
	  }
	  goto next_loop;
	end_loop:
	  base_kb_instance_with_same_name = Nil;
	  name_in_common = Nil;
	  ab_loop_list_ = Record_of_definitional_name_conflicts_qm;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  base_kb_instance_with_same_name = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  name_in_common = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = ISVREF(base_kb_instance_with_same_name,
		  (SI_Long)3L);
	  temp_1 = SIMPLE_VECTOR_P(base_kb_instance_with_same_name) ? 
		  EQ(ISVREF(base_kb_instance_with_same_name,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp_1);
	  else
	      temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp_1);
	  else if (FIXNUMP(reference_frame_serial_number))
	      temp_1 = FIXNUMP(gensymed_symbol) ? 
		      FIXNUM_LT(reference_frame_serial_number,
		      gensymed_symbol) : TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp_1 = TRUEP(Nil);
	  else {
	      xa = M_CAR(reference_frame_serial_number);
	      ya = M_CAR(gensymed_symbol);
	      temp_1 = FIXNUM_LT(xa,ya);
	      if (temp_1);
	      else
		  temp_1 = FIXNUM_EQ(xa,ya) ? 
			  FIXNUM_LT(M_CDR(reference_frame_serial_number),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  if (temp_1)
	      notify_user_of_conflicts(3,string_constant_27,
		      ISVREF(ISVREF(base_kb_instance_with_same_name,
		      (SI_Long)1L),(SI_Long)1L),name_in_common);
	  goto next_loop_1;
	end_loop_1:;
	  reclaim_frame_serial_number(reference_frame_serial_number);
	  reclaim_slot_value_tree_1(Record_of_definitional_name_conflicts_qm);
	  Record_of_definitional_name_conflicts_qm = Nil;
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_28;  /* "~(~a~)" */

static Object Qinput;              /* input */

static Object Qin;                 /* in */

static Object Qout;                /* out */

/* WRITE-DIRECTION-OF-FILE-PROGRESS-FROM-SLOT */
Object write_direction_of_file_progress_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(130,41);
    return tformat(2,string_constant_28,EQ(value,Qnil) || EQ(value,Qinput) 
	    ? Qin : Qout);
}

static Object Qunopened;           /* unopened */

static Object string_constant_29;  /* "unopened" */

static Object string_constant_30;  /* "writing" */

static Object Qclosing;            /* closing */

static Object string_constant_31;  /* "closing" */

static Object Qclosed;             /* closed */

static Object string_constant_32;  /* "closed" */

static Object Qaborted;            /* aborted */

static Object string_constant_33;  /* "ABORTED" */

/* WRITE-STATUS-OF-FILE-PROGRESS-FROM-SLOT */
Object write_status_of_file_progress_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(130,42);
    if (EQ(value,Qunopened))
	temp = string_constant_29;
    else if (EQ(value,Qopen) || EQ(value,Qnil))
	temp = string_constant_30;
    else if (EQ(value,Qclosing))
	temp = string_constant_31;
    else if (EQ(value,Qclosed))
	temp = string_constant_32;
    else if (EQ(value,Qaborted))
	temp = string_constant_33;
    else
	temp = value;
    return tformat(2,string_constant_28,temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_kb_characters_so_far_qm, Qnumber_of_kb_characters_so_far_qm);

static Object array_constant_2;    /* # */

/* WRITE-UNQUOTED-FILE-NAME?-FROM-SLOT */
Object write_unquoted_file_name_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(130,43);
    if (value)
	return twrite_general_string(value);
    else
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)4L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Total_items_in_file, Qtotal_items_in_file);

DEFINE_VARIABLE_WITH_SYMBOL(Write_xml_object_items_collected, Qwrite_xml_object_items_collected);

Object File_progress_finished_reading_states = UNBOUND;

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object list_constant_6;     /* # */

static Object array_constant_6;    /* # */

static Object string_constant_34;  /* "  [~(~a~)]" */

/* WRITE-PROGRESS-THROUGH-FILE-FROM-SLOT */
Object write_progress_through_file_from_slot(value,file_progress)
    Object value, file_progress;
{
    Object temp, finished_reading_status_qm, percentage_through_file;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(130,44);
    temp = memq_function(ISVREF(file_progress,(SI_Long)26L),
	    File_progress_finished_reading_states);
    finished_reading_status_qm = CAR(temp);
    if (Write_xml_object_items_collected) {
	twrite_positive_fixnum(value);
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)6L));
    }
    else if (Total_items_in_file) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    percentage_through_file = 
		    l_round(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(value) / 
		    (double)IFIX(Total_items_in_file) * 100.0),_);
	POP_LOCAL_ALLOCATION(0,0);
	twrite_positive_fixnum(percentage_through_file);
	twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)3L));
	twrite_positive_fixnum(value);
	return twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)6L));
    }
    else {
	if (Number_of_kb_characters_so_far_qm || finished_reading_status_qm) {
	    if (finished_reading_status_qm)
		percentage_through_file = FIX((SI_Long)100L);
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
		    percentage_through_file = 
			    l_round(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(Number_of_kb_characters_so_far_qm) 
			    / (double)IFIX(ISVREF(file_progress,
			    (SI_Long)23L)) * 100.0),_);
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    twrite_positive_fixnum(percentage_through_file);
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)3L));
	}
	twrite_positive_fixnum(value);
	twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)6L));
	if ( !( !EQ(Number_of_kb_characters_so_far_qm,FIX((SI_Long)0L)) || 
		memq_function(ISVREF(file_progress,(SI_Long)26L),
		list_constant_6)))
	    twrite_beginning_of_wide_string(array_constant_6,
		    FIX((SI_Long)11L));
	if (finished_reading_status_qm)
	    return tformat(2,string_constant_34,finished_reading_status_qm);
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_file_progress, Qkb_file_progress);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_kb_lines_so_far, Qnumber_of_kb_lines_so_far);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_update_file_progress_display_qm, Qdo_not_update_file_progress_display_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_restore_image_planes_qm, Qdo_not_restore_image_planes_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_notify_user_during_kb_load_qm, Qdo_not_notify_user_during_kb_load_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Do_not_allow_user_interactions_during_kb_load_qm, Qdo_not_allow_user_interactions_during_kb_load_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Selected_file_progress_attributes_to_show_subsets_plist, Qselected_file_progress_attributes_to_show_subsets_plist);

static Object Qnamestring_of_file_in_progress_qm;  /* namestring-of-file-in-progress? */

static Object Qmodule_of_file_in_progress_qm;  /* module-of-file-in-progress? */

static Object Qstatus_of_file_progress_qm;  /* status-of-file-progress? */

static Object list_constant_7;     /* # */

/* SELECT-SUBSET-OF-FILE-PROGRESS-ATTRIBUTES-TO-SHOW */
Object select_subset_of_file_progress_attributes_to_show varargs_1(int, n)
{
    Object include_namestring_of_file_in_progress_qm_p;
    Object include_module_of_file_in_progress_qm_p;
    Object include_status_of_file_progress_qm_p, temp, temp_1, pattern, temp_2;
    Object selected_subset;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);

    x_note_fn_call(130,45);
    INIT_ARGS_nonrelocating();
    include_namestring_of_file_in_progress_qm_p = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    include_module_of_file_in_progress_qm_p = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    include_status_of_file_progress_qm_p = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = include_namestring_of_file_in_progress_qm_p ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)1L;
    temp = FIX(gensymed_symbol << gensymed_symbol_1);
    gensymed_symbol = include_module_of_file_in_progress_qm_p ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)2L;
    temp_1 = FIX(gensymed_symbol << gensymed_symbol_1);
    gensymed_symbol = include_status_of_file_progress_qm_p ? (SI_Long)1L : 
	    (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)3L;
    pattern = logiorn(3,temp,temp_1,FIX(gensymed_symbol << gensymed_symbol_1));
    temp_1 = getf(Selected_file_progress_attributes_to_show_subsets_plist,
	    pattern,_);
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	if (include_namestring_of_file_in_progress_qm_p) {
	    if (PUSH_AREA(Dynamic_area,0))
		temp = LIST_1(Qnamestring_of_file_in_progress_qm);
	    POP_AREA(0);
	}
	else
	    temp = Nil;
	if (include_module_of_file_in_progress_qm_p) {
	    if (PUSH_AREA(Dynamic_area,0))
		temp_2 = LIST_1(Qmodule_of_file_in_progress_qm);
	    POP_AREA(0);
	}
	else
	    temp_2 = Nil;
	if (include_status_of_file_progress_qm_p) {
	    if (PUSH_AREA(Dynamic_area,0))
		temp_1 = LIST_1(Qstatus_of_file_progress_qm);
	    POP_AREA(0);
	}
	else
	    temp_1 = Nil;
	selected_subset = nconc2(temp,nconc2(temp_2,nconc2(temp_1,
		list_constant_7)));
	Selected_file_progress_attributes_to_show_subsets_plist = 
		nconc2(gensym_list_2(pattern,selected_subset),
		Selected_file_progress_attributes_to_show_subsets_plist);
	return VALUES_1(selected_subset);
    }
}

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qprogress_through_file;  /* progress-through-file */

static Object Qoutput;             /* output */

static Object Qdirection_of_file_progress_qm;  /* direction-of-file-progress? */

static Object Qdialog_workspace_frame_style;  /* dialog-workspace-frame-style */

static Object Qdefault_workspace_frame_style;  /* default-workspace-frame-style */

/* PUT-UP-FILE-PROGRESS-DISPLAY */
Object put_up_file_progress_display varargs_1(int, n)
{
    Object read_case_qm;
    Object file_length_qm, namestring_of_file_in_progress_qm, direction_qm;
    Object status_qm, offset_in_saving_context_qm;
    Object preexisting_file_progress_qm, module_of_file_in_progress_qm;
    Object file_progress, file_progress_attributes_table;
    Object number_of_kb_characters_so_far_qm, file_progress_workspace;
    Object workstation, ab_loop_list_, window;
    Object suppress_updating_of_slot_value_representations_qm, temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(2);

    x_note_fn_call(130,46);
    INIT_ARGS_nonrelocating();
    read_case_qm = REQUIRED_ARG_nonrelocating();
    file_length_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    namestring_of_file_in_progress_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    status_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    offset_in_saving_context_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    preexisting_file_progress_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    module_of_file_in_progress_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    file_progress = make_or_revise_file_progress(7,read_case_qm,
	    file_length_qm,namestring_of_file_in_progress_qm,direction_qm,
	    status_qm,module_of_file_in_progress_qm,
	    preexisting_file_progress_qm);
    if ( !(Do_not_update_file_progress_display_qm || 
	    preexisting_file_progress_qm)) {
	file_progress_attributes_table = make_attributes_table(6,
		file_progress,Nil,Nil,Nil,Nil,
		select_subset_of_file_progress_attributes_to_show(1,
		namestring_of_file_in_progress_qm));
	number_of_kb_characters_so_far_qm = ISVREF(file_progress,
		(SI_Long)23L) ? FIX((SI_Long)0L) : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Number_of_kb_characters_so_far_qm,Qnumber_of_kb_characters_so_far_qm,number_of_kb_characters_so_far_qm,
		1);
	  file_progress_workspace = make_workspace(4,Qtemporary_workspace,
		  Nil,file_progress_attributes_table,FIX((SI_Long)2L));
	  workstation = Nil;
	  ab_loop_list_ = Workstations_in_service;
	  window = Nil;
	  suppress_updating_of_slot_value_representations_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
		  0);
	    change_slot_value(3,file_progress,
		    Qmodule_of_file_in_progress_qm,
		    module_of_file_in_progress_qm);
	    temp = ISVREF(file_progress,(SI_Long)23L);
	    if (temp);
	    else
		temp = FIX((SI_Long)10000000L);
	    change_slot_value(3,file_progress,Qprogress_through_file,temp);
	    change_slot_value(3,file_progress,Qprogress_through_file,
		    FIX((SI_Long)0L));
	    change_slot_value(3,file_progress,
		    Qnumber_of_kb_characters_so_far_qm,FIX((SI_Long)0L));
	    temp = direction_qm;
	    if (temp);
	    else
		temp = read_case_qm ? Qinput : Qoutput;
	    change_slot_value(3,file_progress,
		    Qdirection_of_file_progress_qm,temp);
	    note_update_to_file_progress(1,file_progress);
	  POP_SPECIAL();
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  workstation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  window = ISVREF(workstation,(SI_Long)1L);
	  if ( !TRUEP(native_progress_bar_p(window))) {
	      temp = detail_pane(window);
	      temp_1 = add(FIX((SI_Long)11L),offset_in_saving_context_qm ? 
		      ltimes(FIX((SI_Long)100L),
		      offset_in_saving_context_qm) : FIX((SI_Long)0L));
	      put_workspace_on_pane_function(file_progress_workspace,temp,
		      Qleft,Qtop,T,temp_1,Nil,
		      lookup_frame_description_reference_of_frame_style(Qdialog_workspace_frame_style,
		      Qdefault_workspace_frame_style),Nil,Nil,Nil,Nil,Nil);
	  }
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
    }
    force_process_drawing();
    return VALUES_1(file_progress);
}

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_notification_for_kb_save_qm, Qsuppress_notification_for_kb_save_qm);

static Object Qfile_progress;      /* file-progress */

static Object Qlength_of_file_in_characters_qm;  /* length-of-file-in-characters? */

static Object Qfixnum_time_of_last_file_progress_display_update;  /* fixnum-time-of-last-file-progress-display-update */

/* MAKE-OR-REVISE-FILE-PROGRESS */
Object make_or_revise_file_progress varargs_1(int, n)
{
    Object read_case_qm;
    Object file_length_qm, namestring_of_file_in_progress_qm, direction_qm;
    Object status_qm, module_qm, preexisting_file_progress_qm;
    Object suppress_updating_of_slot_value_representations_qm, file_progress;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,47);
    INIT_ARGS_nonrelocating();
    read_case_qm = REQUIRED_ARG_nonrelocating();
    file_length_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    namestring_of_file_in_progress_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    direction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    status_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    preexisting_file_progress_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    suppress_updating_of_slot_value_representations_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Suppress_updating_of_slot_value_representations_qm,Qsuppress_updating_of_slot_value_representations_qm,suppress_updating_of_slot_value_representations_qm,
	    0);
      file_progress = preexisting_file_progress_qm;
      if (file_progress);
      else
	  file_progress = make_frame(Qfile_progress);
      change_slot_value(3,file_progress,Qdirection_of_file_progress_qm,
	      direction_qm);
      change_slot_value(3,file_progress,Qstatus_of_file_progress_qm,status_qm);
      change_slot_value(3,file_progress,Qnamestring_of_file_in_progress_qm,
	      namestring_of_file_in_progress_qm);
      change_slot_value(3,file_progress,Qmodule_of_file_in_progress_qm,
	      module_qm);
      if (read_case_qm)
	  change_slot_value(3,file_progress,
		  Qlength_of_file_in_characters_qm,file_length_qm && 
		  FIXNUMP(file_length_qm) && IFIX(file_length_qm) > 
		  (SI_Long)0L ? file_length_qm : Nil);
      change_slot_value(3,file_progress,
	      Qfixnum_time_of_last_file_progress_display_update,
	      c_native_clock_ticks_or_cache(Nil,Nil));
      change_slot_value(3,file_progress,Qprogress_through_file,
	      FIX((SI_Long)0L));
      change_slot_value(3,file_progress,Qnumber_of_kb_characters_so_far_qm,
	      FIX((SI_Long)0L));
      if ( !(Do_not_update_file_progress_display_qm || 
	      Suppress_notification_for_kb_save_qm))
	  note_update_to_file_progress(1,file_progress);
      result = VALUES_1(file_progress);
    POP_SPECIAL();
    return result;
}

static Object Qunits_for_progress_through_file;  /* units-for-progress-through-file */

static Object Qitems;              /* items */

static Object Qlines;              /* lines */

static Object Qtotal_number_of_items;  /* total-number-of-items */

/* UPDATE-FILE-PROGRESS-DISPLAY */
Object update_file_progress_display varargs_1(int, n)
{
    Object file_progress, new_integer_value;
    Object force_update_p, fixnum_time_now, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,48);
    INIT_ARGS_nonrelocating();
    file_progress = REQUIRED_ARG_nonrelocating();
    new_integer_value = REQUIRED_ARG_nonrelocating();
    force_update_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Do_not_update_file_progress_display_qm)) {
	fixnum_time_now = c_native_clock_ticks_or_cache(Nil,Nil);
	gensymed_symbol = IFIX(fixnum_time_now);
	gensymed_symbol_1 = IFIX(ISVREF(file_progress,(SI_Long)24L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    temp = FIX(gensymed_symbol - gensymed_symbol_1);
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    temp = FIX(gensymed_symbol + (SI_Long)1L);
	}
	temp_1 = FIXNUM_GE(temp,Fixnum_time_interval_for_one_second);
	if (temp_1);
	else
	    temp_1 = TRUEP(force_update_p);
	if (temp_1) {
	    ISVREF(file_progress,(SI_Long)24L) = fixnum_time_now;
	    change_slot_value(3,file_progress,Qprogress_through_file,
		    new_integer_value);
	    change_slot_value(3,file_progress,
		    Qunits_for_progress_through_file,
		    Write_xml_object_items_collected || 
		    Total_items_in_file ? Qitems : Qlines);
	    change_slot_value(3,file_progress,Qtotal_number_of_items,
		    Total_items_in_file);
	    change_slot_value(3,file_progress,
		    Qnumber_of_kb_characters_so_far_qm,
		    Number_of_kb_characters_so_far_qm);
	    note_update_to_file_progress(1,file_progress);
	    raise_file_progress_display_to_top(file_progress);
	    return force_process_drawing();
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-FILE-PROGRESS-DISPLAY-AFTER-READING */
Object update_file_progress_display_after_reading(file_progress,phase_1)
    Object file_progress, phase_1;
{
    Object svref_new_value;

    x_note_fn_call(130,49);
    if ( !TRUEP(Do_not_update_file_progress_display_qm)) {
	change_slot_value(3,file_progress,Qstatus_of_file_progress_qm,phase_1);
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	ISVREF(file_progress,(SI_Long)24L) = svref_new_value;
	change_slot_value(3,file_progress,
		Qnumber_of_kb_characters_so_far_qm,
		Number_of_kb_characters_so_far_qm);
	change_slot_value(3,file_progress,Qunits_for_progress_through_file,
		Write_xml_object_items_collected || Total_items_in_file ? 
		Qitems : Qlines);
	update_representations_of_slot_value(2,file_progress,
		Qprogress_through_file);
	note_update_to_file_progress(1,file_progress);
	return force_process_drawing();
    }
    else
	return VALUES_1(Nil);
}

/* FILE-PROGRESS-TABLE-P */
Object file_progress_table_p(table)
    Object table;
{
    Object row, ab_loop_list_, ab_loop_it_, cell_qm, ab_loop_list__1, frame_qm;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,50);
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      ab_loop_it_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      cell_qm = Nil;
      ab_loop_list__1 = Row;
      ab_loop_it_ = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      cell_qm = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (cell_qm && CONSP(cell_qm)) {
	  frame_qm = get_slot_represented_by_text_cell_if_any(cell_qm);
	  if (frame_qm) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qfile_progress,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame_qm,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		  }
		  else
		      ab_loop_it_ = Nil;
	      }
	      else
		  ab_loop_it_ = Nil;
	  }
	  else
	      ab_loop_it_ = Nil;
      }
      else
	  ab_loop_it_ = Nil;
      if (ab_loop_it_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
      ab_loop_it_ = Qnil;
    end_1:;
      if (ab_loop_it_) {
	  result = VALUES_1(ab_loop_it_);
	  goto end_2;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* RAISE-FILE-PROGRESS-DISPLAY-TO-TOP */
Object raise_file_progress_display_to_top(file_progress)
    Object file_progress;
{
    Object representation, ab_loop_list_, workspace_qm, sub_class_bit_vector;
    Object image_plane, ab_loop_list__1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(130,51);
    representation = Nil;
    ab_loop_list_ = ISVREF(file_progress,(SI_Long)9L);
    workspace_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
    workspace_qm = temp ? get_workspace_if_any(representation) : Nil;
    if (workspace_qm) {
	image_plane = Nil;
	ab_loop_list__1 = ISVREF(workspace_qm,(SI_Long)16L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	image_plane = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	raise_image_plane_to_top(1,image_plane);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(First_kb_in_group_read_in_yet_qm, Qfirst_kb_in_group_read_in_yet_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Level_of_group_kb_read, Qlevel_of_group_kb_read);

DEFINE_VARIABLE_WITH_SYMBOL(Modules_loaded_in_this_group, Qmodules_loaded_in_this_group);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_serial_number_before_loading_this_group, Qkb_serial_number_before_loading_this_group);

DEFINE_VARIABLE_WITH_SYMBOL(Current_system_rpc_icp_socket_qm, Qcurrent_system_rpc_icp_socket_qm);

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object string_constant_35;  /* "starting kb file '~a' loading (merging) on: ~a ~a ~a, ~a:~a:~a" */

static Object list_constant_8;     /* # */

static Object Qg2_defstruct_structure_name_workstation_g2_struct;  /* g2-defstruct-structure-name::workstation-g2-struct */

static Object Qui_client_interface;  /* ui-client-interface */

static Object Qgsi_interface_icp_socket;  /* gsi-interface-icp-socket */

static Object string_constant_36;  /* "ending kb file '~a' loading (merging) on: ~a ~a ~a, ~a:~a:~a" */

static Object string_constant_37;  /* "the time span for the kb '~a' loading (merging) is ~as" */

/* READ-KB-OR-GROUP-THEREOF */
Object read_kb_or_group_thereof(gensym_pathname_to_read,clear_kb_qm,
	    install_system_tables_qm,bring_formats_up_to_date_qm,
	    resolve_conflicts_automatically_qm,
	    what_to_do_after_loading_kb_qm,update_before_loading_qm,client_qm)
    Object gensym_pathname_to_read, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object what_to_do_after_loading_kb_qm, update_before_loading_qm, client_qm;
{
    Object time_before, time_after, measure_load_time_qm, second_1, minute;
    Object hour, date, month, year, temp, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, current_workstation_context;
    Object type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector;
    Object current_system_rpc_icp_socket_qm, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(12);
    Object result;

    x_note_fn_call(130,52);
    SAVE_STACK();
    time_before = Nil;
    time_after = Nil;
    measure_load_time_qm = string_eq_w(get_command_line_keyword_argument(1,
	    array_constant_7),array_constant_8);
    if (Do_not_allow_user_interactions_during_kb_load_qm)
	enable_ui_on_all_workstations(Nil);
    if (measure_load_time_qm) {
	time_before = DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float());
	result = gensym_decode_unix_time(time_before);
	MVS_6(result,second_1,minute,hour,date,month,year);
	temp = gensym_namestring(1,gensym_pathname_to_read);
	notify_user_at_console(8,string_constant_35,temp,date,
		nth(sub1(month),list_constant_8),year,hour,minute,second_1);
    }
    if (PUSH_UNWIND_PROTECT(1)) {
	if (SIMPLE_VECTOR_P(client_qm) && EQ(ISVREF(client_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_workstation_g2_struct)) {
	    if (Servicing_workstation_qm)
		temp = read_kb_or_group_thereof_1(gensym_pathname_to_read,
			clear_kb_qm,install_system_tables_qm,
			bring_formats_up_to_date_qm,
			resolve_conflicts_automatically_qm,
			what_to_do_after_loading_kb_qm,
			update_before_loading_qm);
	    else {
		LOCK(For_workstation);
		if (PUSH_UNWIND_PROTECT(0)) {
		    current_workstation_1 = client_qm;
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
				  ISVREF(Current_workstation_window,
				  (SI_Long)1L);
			  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
				  8);
			    current_workstation_native_window_qm = 
				    ISVREF(Current_workstation_window,
				    (SI_Long)17L);
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
					    temp = 
						    read_kb_or_group_thereof_1(gensym_pathname_to_read,
						    clear_kb_qm,
						    install_system_tables_qm,
						    bring_formats_up_to_date_qm,
						    resolve_conflicts_automatically_qm,
						    what_to_do_after_loading_kb_qm,
						    update_before_loading_qm);
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
		    SAVE_VALUES(VALUES_1(temp));
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(For_workstation);
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		temp = result;
	    }
	}
	else {
	    if (SIMPLE_VECTOR_P(client_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(client_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(client_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(client_qm,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qui_client_interface,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
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
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		current_system_rpc_icp_socket_qm = 
			get_slot_value_function(client_qm,
			Qgsi_interface_icp_socket,Nil);
		PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
			0);
		  temp = 
			  read_kb_or_group_thereof_1(gensym_pathname_to_read,
			  clear_kb_qm,install_system_tables_qm,
			  bring_formats_up_to_date_qm,
			  resolve_conflicts_automatically_qm,
			  what_to_do_after_loading_kb_qm,
			  update_before_loading_qm);
		POP_SPECIAL();
	    }
	    else
		temp = read_kb_or_group_thereof_1(gensym_pathname_to_read,
			clear_kb_qm,install_system_tables_qm,
			bring_formats_up_to_date_qm,
			resolve_conflicts_automatically_qm,
			what_to_do_after_loading_kb_qm,
			update_before_loading_qm);
	}
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(1);
    if (Do_not_allow_user_interactions_during_kb_load_qm)
	enable_ui_on_all_workstations(T);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    temp = result;
    if (measure_load_time_qm) {
	time_after = DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float());
	result = gensym_decode_unix_time(time_after);
	MVS_6(result,second_1,minute,hour,date,month,year);
	temp_2 = gensym_namestring(1,gensym_pathname_to_read);
	notify_user_at_console(8,string_constant_36,temp_2,date,
		nth(sub1(month),list_constant_8),year,hour,minute,second_1);
	temp_2 = gensym_namestring(1,gensym_pathname_to_read);
	notify_user_at_console(3,string_constant_37,temp_2,
		minus(time_after,time_before));
    }
    RESTORE_STACK();
    return VALUES_1(temp);
}

/* READ-KB-OR-GROUP-THEREOF-1 */
Object read_kb_or_group_thereof_1(gensym_pathname_to_read,clear_kb_qm,
	    install_system_tables_qm,bring_formats_up_to_date_qm,
	    resolve_conflicts_automatically_qm,
	    what_to_do_after_loading_kb_qm,update_before_loading_qm)
    Object gensym_pathname_to_read, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object what_to_do_after_loading_kb_qm, update_before_loading_qm;
{
    Object level_of_group_kb_read, first_kb_in_group_read_in_yet_qm;
    Object modules_loaded_in_this_group;
    Object kb_serial_number_before_loading_this_group;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(130,53);
    SAVE_STACK();
    level_of_group_kb_read = Qunbound_in_protected_let;
    first_kb_in_group_read_in_yet_qm = Qunbound_in_protected_let;
    modules_loaded_in_this_group = Qunbound_in_protected_let;
    kb_serial_number_before_loading_this_group = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Kb_serial_number_before_loading_this_group,Qkb_serial_number_before_loading_this_group,kb_serial_number_before_loading_this_group,
	    4);
      PUSH_SPECIAL_WITH_SYMBOL(Modules_loaded_in_this_group,Qmodules_loaded_in_this_group,modules_loaded_in_this_group,
	      3);
	PUSH_SPECIAL_WITH_SYMBOL(First_kb_in_group_read_in_yet_qm,Qfirst_kb_in_group_read_in_yet_qm,first_kb_in_group_read_in_yet_qm,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Level_of_group_kb_read,Qlevel_of_group_kb_read,level_of_group_kb_read,
		  1);
	    if (PUSH_UNWIND_PROTECT(0)) {
		Level_of_group_kb_read = FIX((SI_Long)0L);
		First_kb_in_group_read_in_yet_qm = Nil;
		Modules_loaded_in_this_group = Nil;
		Kb_serial_number_before_loading_this_group = 
			Current_kb_serial_number;
		inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
			= T;
		PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
			0);
		  temp = 
			  read_kb_or_group_thereof_2(gensym_pathname_to_read,
			  clear_kb_qm,install_system_tables_qm,
			  bring_formats_up_to_date_qm,
			  resolve_conflicts_automatically_qm,Nil,
			  what_to_do_after_loading_kb_qm,
			  update_before_loading_qm);
		POP_SPECIAL();
		SAVE_VALUES(VALUES_1(temp));
		if ( 
			!TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm))
		    update_module_related_frame_notes_for_all_workspaces(0);
	    }
	    POP_UNWIND_PROTECT(0);
	    if (Modules_loaded_in_this_group) {
		if ( !EQ(Modules_loaded_in_this_group,
			Qunbound_in_protected_let))
		    reclaim_gensym_list_1(Modules_loaded_in_this_group);
	    }
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Doing_g2_init_file_p, Qdoing_g2_init_file_p);

DEFINE_VARIABLE_WITH_SYMBOL(Doing_g2_init_kb_p, Qdoing_g2_init_kb_p);

static Object Qwarmboot_afterwards;  /* warmboot-afterwards */

static Object Qwarmboot_afterwards_with_catch_up;  /* warmboot-afterwards-with-catch-up */

static Object string_constant_38;  /* "Warmbooting can only be done when loading~A.  Cancelling the command!" */

static Object string_constant_39;  /* ", not when merging" */

static Object string_constant_40;  /* " a single KB file with no required modules" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_41;  /* "Replace existing KB with modules as shown?" */

static Object string_constant_42;  /* "Merge modules as shown into existing kb?" */

static Object string_constant_43;  /* "Replace existing KB with \"~a\"" */

static Object string_constant_44;  /* "Merge \"~a\" into existing KB" */

static Object string_constant_45;  /* "  (Note: See the logbook for source code control warnings.)" */

static Object Qloading;            /* loading */

static Object Qwarmboot_kb;        /* warmboot-kb */

static Object Qread_modules_of_kb_per_loading_schedule;  /* read-modules-of-kb-per-loading-schedule */

static Object Qreclaim_module_loading_schedule_and_representations_thereof;  /* reclaim-module-loading-schedule-and-representations-thereof */

/* READ-KB-OR-GROUP-THEREOF-2 */
Object read_kb_or_group_thereof_2(gensym_pathname_to_read,clear_kb_qm,
	    install_system_tables_qm,bring_formats_up_to_date_qm,
	    resolve_conflicts_automatically_qm,required_module_name_qm,
	    what_to_do_after_loading_kb_qm,update_before_loading_qm)
    Object gensym_pathname_to_read, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object required_module_name_qm, what_to_do_after_loading_kb_qm;
    Object update_before_loading_qm;
{
    Object warmboot_case_qm, defer_notifications_qm, module_loading_schedule;
    Object error_qm, ab_loop_list_, ab_loop_desetq_, temp;
    Object source_code_control_warnings_p, copy_of_module_loading_schedule;
    Object module, truename_qm, mapped_default_directory, requiring_module_qm;
    Object namestring_as_text_string, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(130,54);
    warmboot_case_qm = EQ(what_to_do_after_loading_kb_qm,
	    Qwarmboot_afterwards) ? T : Nil;
    if (warmboot_case_qm);
    else
	warmboot_case_qm = EQ(what_to_do_after_loading_kb_qm,
		Qwarmboot_afterwards_with_catch_up) ? T : Nil;
    defer_notifications_qm = clear_kb_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
	    5);
      module_loading_schedule = 
	      create_module_loading_schedule(gensym_pathname_to_read,
	      warmboot_case_qm,update_before_loading_qm,clear_kb_qm);
      error_qm = Nil;
      ab_loop_list_ = module_loading_schedule;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      temp = CDR(ab_loop_desetq_);
      temp = CDR(temp);
      temp = CDR(temp);
      temp = CDR(temp);
      error_qm = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (error_qm) {
	  source_code_control_warnings_p = T;
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      source_code_control_warnings_p = Qnil;
    end_1:;
      copy_of_module_loading_schedule = 
	      copy_tree_using_gensym_conses_1(module_loading_schedule);
      if ( !TRUEP(module_loading_schedule)) {
	  Defer_notifications_qm = Nil;
	  try_to_do_deferred_user_notifications();
	  temp = Nil;
      }
      else if (warmboot_case_qm && ( !TRUEP(clear_kb_qm) || 
	      CDR(module_loading_schedule))) {
	  notify_user(2,string_constant_38, !TRUEP(clear_kb_qm) ? 
		  string_constant_39 : string_constant_40);
	  Defer_notifications_qm = Nil;
	  try_to_do_deferred_user_notifications();
	  reclaim_module_loading_schedule(copy_of_module_loading_schedule);
	  temp = Nil;
      }
      else {
	  module = Nil;
	  truename_qm = Nil;
	  mapped_default_directory = Nil;
	  requiring_module_qm = Nil;
	  ab_loop_list_ = module_loading_schedule;
	  ab_loop_desetq_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  module = CAR(ab_loop_desetq_);
	  temp = CDR(ab_loop_desetq_);
	  truename_qm = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  mapped_default_directory = CAR(temp);
	  temp = CDR(ab_loop_desetq_);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  requiring_module_qm = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(module_exists_p(module)) &&  !TRUEP(truename_qm)) {
	      temp = last(module_loading_schedule,_);
	      temp = FIRST(temp);
	      give_module_not_found_warning(module,requiring_module_qm,
		      FIRST(temp),gensym_pathname_to_read);
	      temp_1 = TRUEP(T);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_1 = TRUEP(Nil);
	  goto end_2;
	  temp_1 = TRUEP(Qnil);
	end_2:;
	  if (temp_1) {
	      Defer_notifications_qm = Nil;
	      try_to_do_deferred_user_notifications();
	      temp = Nil;
	  }
	  else if (Servicing_workstation_qm &&  
		  !TRUEP(Doing_g2_init_file_p) &&  
		  !TRUEP(Doing_g2_init_kb_p) && ( !TRUEP(empty_kb_p()) || 
		  source_code_control_warnings_p)) {
	      Defer_notifications_qm = Nil;
	      try_to_do_deferred_user_notifications();
	      temp = FIRST(module_loading_schedule);
	      namestring_as_text_string = 
		      gensym_namestring_as_text_string(1,SECOND(temp));
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
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    1);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			tformat(2,CDR(module_loading_schedule) ? 
				(clear_kb_qm ? string_constant_41 : 
				string_constant_42) : clear_kb_qm ? 
				string_constant_43 : string_constant_44,
				namestring_as_text_string);
			if (clear_kb_qm)
			    twrite_changed_modules_note();
			if (source_code_control_warnings_p)
			    tformat(1,string_constant_45);
			temp_2 = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      reclaim_text_string(namestring_as_text_string);
	      if (warmboot_case_qm) {
		  temp = FIRST(module_loading_schedule);
		  temp = slot_value_list_2(SECOND(temp),
			  EQ(what_to_do_after_loading_kb_qm,
			  Qwarmboot_afterwards_with_catch_up) ? T : Nil);
	      }
	      else {
		  gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)6L));
		  gensymed_symbol_1 = gensymed_symbol;
		  M_CAR(gensymed_symbol_1) = copy_of_module_loading_schedule;
		  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		  M_CAR(gensymed_symbol_1) = clear_kb_qm;
		  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		  M_CAR(gensymed_symbol_1) = install_system_tables_qm;
		  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		  M_CAR(gensymed_symbol_1) = bring_formats_up_to_date_qm;
		  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		  M_CAR(gensymed_symbol_1) = 
			  resolve_conflicts_automatically_qm;
		  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		  M_CAR(gensymed_symbol_1) = what_to_do_after_loading_kb_qm;
		  temp = gensymed_symbol;
	      }
	      temp = post_module_schedule_dialog(Qloading,
		      module_loading_schedule,temp_2,warmboot_case_qm ? 
		      Qwarmboot_kb : 
		      Qread_modules_of_kb_per_loading_schedule,temp,
		      warmboot_case_qm ? Nil : 
		      Qreclaim_module_loading_schedule_and_representations_thereof,
		      warmboot_case_qm ? Nil : 
		      slot_value_cons_1(copy_of_module_loading_schedule,Nil));
	  }
	  else if (warmboot_case_qm) {
	      temp = FIRST(module_loading_schedule);
	      temp = warmboot_kb(2,SECOND(temp),
		      EQ(what_to_do_after_loading_kb_qm,
		      Qwarmboot_afterwards_with_catch_up) ? T : Nil);
	      Defer_notifications_qm = Nil;
	      try_to_do_deferred_user_notifications();
	  }
	  else {
	      temp = 
		      read_modules_of_kb_per_loading_schedule(copy_of_module_loading_schedule,
		      clear_kb_qm,install_system_tables_qm,
		      bring_formats_up_to_date_qm,
		      resolve_conflicts_automatically_qm,
		      what_to_do_after_loading_kb_qm);
	      Defer_notifications_qm = Nil;
	      try_to_do_deferred_user_notifications();
	  }
      }
      reclaim_module_loading_schedule(module_loading_schedule);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Some_module_is_clear_text_p, Qsome_module_is_clear_text_p);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_file_progress_is_currently_for_modules_p, Qkb_file_progress_is_currently_for_modules_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_kb_file_progress_for_modules_qm, Qcurrent_kb_file_progress_for_modules_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Post_loading_functions_will_be_executed_again_later_qm, Qpost_loading_functions_will_be_executed_again_later_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Launch_recompile_for_compilations_removed_in_this_kb_qm, Qlaunch_recompile_for_compilations_removed_in_this_kb_qm);

static Object string_constant_46;  /* "Skipping module ~a, since it is already present." */

static Object string_constant_47;  /* "Module ~a could not be found!" */

static Object Kerror_recovery;     /* :error-recovery */

static Object string_constant_48;  /* "WARNING!! This KB was not loaded successfully." */

static Object Qstart_afterwards;   /* start-afterwards */

static Object Qload_grammar;       /* load-grammar */

static Object Qmerge_grammar;      /* merge-grammar */

static Object Qload_from_command_line;  /* load-from-command-line */

static Object Qnever_start_afterwards;  /* never-start-afterwards */

static Object Qsystem_table;       /* system-table */

static Object string_constant_49;  /* "G2 cannot start automatically because this KB has not been ~
				    *                   compiled up-to-date and saved in the current version of G2.  ~
				    *                   Once you save the KB in this version of G2, it will be possible ~
				    * ?          for G2 to start automatically."
				    */

/* READ-MODULES-OF-KB-PER-LOADING-SCHEDULE */
Object read_modules_of_kb_per_loading_schedule(module_loading_schedule,
	    clear_kb_qm,install_system_tables_qm,
	    bring_formats_up_to_date_qm,resolve_conflicts_automatically_qm,
	    what_to_do_after_loading_kb_qm)
    Object module_loading_schedule, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object what_to_do_after_loading_kb_qm;
{
    Object defer_notifications_qm, current_kb_file_progress_for_modules_qm;
    Object kb_file_progress_is_currently_for_modules_p;
    Object remaining_modules_to_load, module, truename_qm;
    Object default_kb_directory, first_time_qm, last_time_qm;
    Object post_loading_functions_will_be_executed_again_later_qm;
    Object ab_loop_iter_flag_, temp, remaining_modules_to_load_old_value;
    Object autostart_reason_qm;
    Declare_special(4);
    Object result;

    x_note_fn_call(130,55);
    reclaim_any_module_schedule_displays();
    Some_module_is_clear_text_p = Nil;
    defer_notifications_qm = clear_kb_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
	    3);
      current_kb_file_progress_for_modules_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_kb_file_progress_for_modules_qm,Qcurrent_kb_file_progress_for_modules_qm,current_kb_file_progress_for_modules_qm,
	      2);
	kb_file_progress_is_currently_for_modules_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Kb_file_progress_is_currently_for_modules_p,Qkb_file_progress_is_currently_for_modules_p,kb_file_progress_is_currently_for_modules_p,
		1);
	  remaining_modules_to_load = module_loading_schedule;
	  module = Nil;
	  truename_qm = Nil;
	  default_kb_directory = Nil;
	  first_time_qm = T;
	  last_time_qm = Nil;
	  post_loading_functions_will_be_executed_again_later_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Post_loading_functions_will_be_executed_again_later_qm,Qpost_loading_functions_will_be_executed_again_later_qm,post_loading_functions_will_be_executed_again_later_qm,
		  0);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    temp = CAR(remaining_modules_to_load);
	    module = CAR(temp);
	    temp = CAR(remaining_modules_to_load);
	    temp = CDR(temp);
	    truename_qm = CAR(temp);
	    temp = CAR(remaining_modules_to_load);
	    temp = CDR(temp);
	    temp = CDR(temp);
	    default_kb_directory = CAR(temp);
	    if ( !TRUEP(ab_loop_iter_flag_))
		first_time_qm = Nil;
	    last_time_qm =  !TRUEP(CDR(remaining_modules_to_load)) ? T : Nil;
	    Post_loading_functions_will_be_executed_again_later_qm =  
		    !TRUEP(last_time_qm) ? T : Nil;
	    if (module_exists_p(module) &&  !TRUEP(last_time_qm) && ( 
		    !TRUEP(first_time_qm) ||  !TRUEP(clear_kb_qm))) {
		if ( !TRUEP(Do_not_notify_user_during_kb_load_qm))
		    notify_user(2,string_constant_46,module);
		temp = T;
	    }
	    else if ( !TRUEP(truename_qm)) {
		notify_user(2,string_constant_47,module);
		temp = Nil;
	    }
	    else
		temp = read_kb(module,truename_qm,clear_kb_qm ? 
			first_time_qm : Nil,install_system_tables_qm ? 
			last_time_qm : Nil,bring_formats_up_to_date_qm,
			resolve_conflicts_automatically_qm,
			default_kb_directory);
	    if ( !TRUEP(temp)) {
		do_post_loading_functions(Kerror_recovery);
		notify_user(1,string_constant_48);
		Defer_notifications_qm = Nil;
		try_to_do_deferred_user_notifications();
		result = VALUES_1(Nil);
		goto end_1;
	    }
	    remaining_modules_to_load_old_value = remaining_modules_to_load;
	    remaining_modules_to_load = 
		    REST(remaining_modules_to_load_old_value);
	    if ( !TRUEP(remaining_modules_to_load))
		goto end_loop;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    if (Current_kb_file_progress_for_modules_qm) {
		note_update_to_file_progress(2,
			Current_kb_file_progress_for_modules_qm,Qdelete);
		delete_frame(Current_kb_file_progress_for_modules_qm);
		force_process_drawing();
	    }
	    if ( !(Doing_g2_init_file_p || System_has_paused)) {
		if (EQ(what_to_do_after_loading_kb_qm,Qstart_afterwards))
		    autostart_reason_qm = clear_kb_qm ? Qload_grammar : 
			    Qmerge_grammar;
		else if (EQ(what_to_do_after_loading_kb_qm,
			Qload_from_command_line))
		    autostart_reason_qm = Qload_from_command_line;
		else if ( !EQ(what_to_do_after_loading_kb_qm,
			Qnever_start_afterwards) && 
			start_kb_after_load_from_system_table_qm())
		    autostart_reason_qm = Qsystem_table;
		else
		    autostart_reason_qm = Qnil;
		if (autostart_reason_qm) {
		    if (Launch_recompile_for_compilations_removed_in_this_kb_qm)
			notify_user(1,string_constant_49);
		    else {
			notify_user_of_autostart_and_reason(autostart_reason_qm);
			Need_call_system_start = T;
		    }
		}
	    }
	    Defer_notifications_qm = Nil;
	    try_to_do_deferred_user_notifications();
	    reclaim_pathnames_in_loading_schedule(module_loading_schedule);
	    reclaim_module_loading_schedule(module_loading_schedule);
	    result = VALUES_1(T);
	    goto end_1;
	    result = VALUES_1(Qnil);
	  end_1:;
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qmodule_load_request;  /* module-load-request */

/* MAKE-MODULE-LOAD-REQUEST */
Object make_module_load_request varargs_1(int, n)
{
    Object module, file_truename_qm;
    Object requiring_module_qm, required_modules, module_load_request;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,56);
    INIT_ARGS_nonrelocating();
    module = REQUIRED_ARG_nonrelocating();
    file_truename_qm = REQUIRED_ARG_nonrelocating();
    requiring_module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    required_modules = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    module_load_request = make_frame(Qmodule_load_request);
    ISVREF(module_load_request,(SI_Long)20L) = module;
    svref_new_value = file_truename_qm ? 
	    gensym_namestring_as_text_string(1,file_truename_qm) : Nil;
    ISVREF(module_load_request,(SI_Long)21L) = svref_new_value;
    ISVREF(module_load_request,(SI_Long)30L) = requiring_module_qm;
    ISVREF(module_load_request,(SI_Long)31L) = required_modules;
    note_update_to_file_progress(1,module_load_request);
    return VALUES_1(module_load_request);
}

/* CREATE-MODULE-LOAD-REQUESTS-PER-SCHEDULE */
Object create_module_load_requests_per_schedule(module_loading_schedule)
    Object module_loading_schedule;
{
    Object module, truename_qm, ab_loop_list_, module_load_request;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;

    x_note_fn_call(130,57);
    module = Nil;
    truename_qm = Nil;
    ab_loop_list_ = module_loading_schedule;
    module_load_request = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    truename_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    module_load_request = make_module_load_request(2,module,truename_qm);
    ab_loopvar__2 = gensym_cons_1(module_load_request,Nil);
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

DEFINE_VARIABLE_WITH_SYMBOL(Selected_module_load_request_attributes_to_show_subsets_plist, Qselected_module_load_request_attributes_to_show_subsets_plist);

static Object Qmodules_this_required;  /* modules-this-required */

static Object Qmodule_that_required_this_qm;  /* module-that-required-this? */

static Object list_constant_9;     /* # */

/* SELECT-SUBSET-OF-MODULE-LOAD-REQUEST-ATTRIBUTES-TO-SHOW */
Object select_subset_of_module_load_request_attributes_to_show varargs_1(int, n)
{
    Object include_modules_this_required_p;
    Object include_module_that_required_this_qm_p, temp, pattern, temp_1;
    Object selected_subset;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);

    x_note_fn_call(130,58);
    INIT_ARGS_nonrelocating();
    include_modules_this_required_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    include_module_that_required_this_qm_p = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = include_modules_this_required_p ? (SI_Long)1L : 
	    (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)1L;
    temp = FIX(gensymed_symbol << gensymed_symbol_1);
    gensymed_symbol = include_module_that_required_this_qm_p ? (SI_Long)1L 
	    : (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)2L;
    pattern = FIXNUM_LOGIOR(temp,FIX(gensymed_symbol << gensymed_symbol_1));
    temp = 
	    getf(Selected_module_load_request_attributes_to_show_subsets_plist,
	    pattern,_);
    if (temp)
	return VALUES_1(temp);
    else {
	if (include_modules_this_required_p) {
	    if (PUSH_AREA(Dynamic_area,0))
		temp_1 = LIST_1(Qmodules_this_required);
	    POP_AREA(0);
	}
	else
	    temp_1 = Nil;
	if (include_module_that_required_this_qm_p) {
	    if (PUSH_AREA(Dynamic_area,0))
		temp = LIST_1(Qmodule_that_required_this_qm);
	    POP_AREA(0);
	}
	else
	    temp = Nil;
	selected_subset = nconc2(temp_1,nconc2(temp,list_constant_9));
	Selected_module_load_request_attributes_to_show_subsets_plist = 
		nconc2(gensym_list_2(pattern,selected_subset),
		Selected_module_load_request_attributes_to_show_subsets_plist);
	return VALUES_1(selected_subset);
    }
}

static Object Qsmall_file_progress_display_value_format;  /* small-file-progress-display-value-format */

/* MAKE-MULTIFRAME-TABLE-PER-MODULE-LOAD-REQUESTS */
Object make_multiframe_table_per_module_load_requests(module_load_requests)
    Object module_load_requests;
{
    Object existing_table_rows, existing_slots, module_load_request;
    Object ab_loop_list_, temp, temp_1;
    Object result;

    x_note_fn_call(130,59);
    existing_table_rows = Nil;
    existing_slots = Nil;
    module_load_request = Nil;
    ab_loop_list_ = module_load_requests;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_load_request = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = module_load_request;
    temp_1 = select_subset_of_module_load_request_attributes_to_show(0);
    result = merge_frame_into_multiframe_table_rows(5,temp,temp_1,
	    existing_table_rows,existing_slots,
	    Qsmall_file_progress_display_value_format);
    MVS_2(result,existing_table_rows,existing_slots);
    goto next_loop;
  end_loop:
    reclaim_slot_value(existing_slots);
    return finish_making_multiframe_table(2,existing_table_rows,Nil);
    return VALUES_1(Qnil);
}

Object Module_schedule_title = UNBOUND;

static Object Qtitle_bar_text;     /* title-bar-text */

/* DISPLAY-MODULE-LOADING-SCHEDULE */
Object display_module_loading_schedule(module_loading_schedule)
    Object module_loading_schedule;
{
    Object module_load_requests, temp, table, workspace;

    x_note_fn_call(130,60);
    if (Servicing_workstation_qm) {
	module_load_requests = 
		create_module_load_requests_per_schedule(module_loading_schedule);
	temp = 
		make_multiframe_table_per_module_load_requests(module_load_requests);
	reclaim_gensym_list_1(module_load_requests);
	table = temp;
	workspace = make_workspace(3,Qtemporary_workspace,Nil,table);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qtitle_bar_text);
	set_lookup_slot_value_1(workspace,Qtitle_bar_text,
		copy_text_string(Module_schedule_title));
	return put_workspace_on_pane_function(workspace,
		Current_workstation_detail_pane,Qleft,Qtop,T,
		FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ANY-MODULE-SCHEDULE-DISPLAYS */
Object reclaim_any_module_schedule_displays()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, module_load_request;
    char temp;
    Declare_special(1);

    x_note_fn_call(130,61);
  next_loop:
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    module_load_request = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qmodule_load_request);
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_2;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      module_load_request = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      note_update_to_file_progress(2,module_load_request,Qdelete);
      delete_frame(module_load_request);
      temp = TRUEP(T);
      goto end_1;
      goto next_loop_1;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if ( !temp)
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* RECLAIM-MODULE-LOADING-SCHEDULE-AND-REPRESENTATIONS-THEREOF */
Object reclaim_module_loading_schedule_and_representations_thereof(module_loading_schedule)
    Object module_loading_schedule;
{
    x_note_fn_call(130,62);
    reclaim_any_module_schedule_displays();
    return reclaim_module_loading_schedule(module_loading_schedule);
}

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object Qicon;               /* icon */

static Object Qab_warning;         /* warning */

static Object Qquestion;           /* question */

static Object Qcheckable;          /* checkable */

static Object Qsaving;             /* saving */

static Object Qrow_count;          /* row-count */

static Object Qcolumns;            /* columns */

static Object list_constant_10;    /* # */

static Object Qrows;               /* rows */

/* POST-MODULE-SCHEDULE-DIALOG */
Object post_module_schedule_dialog(type,module_schedule,
	    dialog_message_text_string,ok_function_qm,
	    ok_function_arglist_qm,cancel_function_qm,
	    cancel_function_arglist_qm)
    Object type, module_schedule, dialog_message_text_string, ok_function_qm;
    Object ok_function_arglist_qm, cancel_function_qm;
    Object cancel_function_arglist_qm;
{
    Object native_dialog_p, display_schedule_p, warning_p;
    Object simple_dialog_title_qm, simple_dialog_fill_text_p, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value, module, truename_qm;
    Object ab_loop_list_, namestring_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp, simple_dialog_plist_qm;
    Declare_special(3);
    Object result;

    x_note_fn_call(130,63);
    native_dialog_p = native_simple_dialogs_p(Current_workstation_window) ?
	     (FIXNUM_LT(Icp_window_protocol_supports_simple_dialog_ex,
	    ISVREF(Current_workstation_window,(SI_Long)11L)) ? T : Nil) : Qnil;
    display_schedule_p = EQ(type,Qloading) ? ( ! 
	    !TRUEP(CDR(module_schedule)) ? T : Nil) :  ! 
	    !TRUEP(module_schedule) ? T : Nil;
    warning_p = gensym_search_simple(array_constant_9,
	    dialog_message_text_string);
    if (warning_p);
    else
	warning_p = gensym_search_simple(array_constant_10,
		dialog_message_text_string);
    simple_dialog_title_qm = native_dialog_p && display_schedule_p ? 
	    Module_schedule_title : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Simple_dialog_title_qm,Qsimple_dialog_title_qm,simple_dialog_title_qm,
	    2);
      simple_dialog_fill_text_p = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Simple_dialog_fill_text_p,Qsimple_dialog_fill_text_p,simple_dialog_fill_text_p,
	      1);
	if (native_dialog_p && display_schedule_p) {
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = Qicon;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = warning_p ? Qab_warning : Qquestion;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qcheckable;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = EQ(Qsaving,type) ? T : Nil;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qrow_count;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = EQ(Qsaving,type) ? length(module_schedule) : Nil;
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qcolumns;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    car_new_value = 
		    copy_gensym_tree_with_text_strings(list_constant_10);
	    M_CAR(gensymed_symbol_1) = car_new_value;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = Qrows;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    module = Nil;
	    truename_qm = Nil;
	    ab_loop_list_ = module_schedule;
	    namestring_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    module = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    truename_qm = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    namestring_1 = truename_qm ? gensym_namestring(1,truename_qm) :
		     copy_wide_string(array_constant);
	    ab_loopvar__2 = 
		    gensym_cons_1(copy_text_string(stringw(module)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    ab_loopvar__2 = gensym_cons_1(namestring_1,Nil);
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
	    M_CAR(gensymed_symbol_1) = ab_loopvar_;
	    simple_dialog_plist_qm = gensymed_symbol;
	}
	else
	    simple_dialog_plist_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Simple_dialog_plist_qm,Qsimple_dialog_plist_qm,simple_dialog_plist_qm,
		0);
	  if ( !TRUEP(native_dialog_p)) {
	      if (display_schedule_p)
		  display_module_loading_schedule(module_schedule);
	  }
	  enter_dialog(7,dialog_message_text_string,Nil,Nil,ok_function_qm,
		  ok_function_arglist_qm,cancel_function_qm,
		  cancel_function_arglist_qm);
	  if (Simple_dialog_plist_qm)
	      result = reclaim_gensym_tree_with_text_strings(Simple_dialog_plist_qm);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object Directory_cache_use_disabled_p = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(File_system_directory_search_cache_active_p, Qfile_system_directory_search_cache_active_p);

DEFINE_VARIABLE_WITH_SYMBOL(File_system_directory_search_cache, Qfile_system_directory_search_cache);

DEFINE_VARIABLE_WITH_SYMBOL(File_system_directory_search_cache_wildcard_string, Qfile_system_directory_search_cache_wildcard_string);

/* RECLAIM-FILE-SYSTEM-DIRECTORY-SEARCH-CACHE */
Object reclaim_file_system_directory_search_cache()
{
    Object temp;

    x_note_fn_call(130,64);
    temp = Nil;
    reclaim_directory_search_cache(File_system_directory_search_cache);
    File_system_directory_search_cache = temp;
    return VALUES_1(File_system_directory_search_cache);
}

/* COPY-FILE-SYSTEM-DIRECTORY-SEARCH-CACHE */
Object copy_file_system_directory_search_cache()
{
    x_note_fn_call(130,65);
    return copy_directory_search_cache(File_system_directory_search_cache);
}

/* SEIZE-FILE-SYSTEM-DIRECTORY-SEARCH-CACHE */
Object seize_file_system_directory_search_cache()
{
    Object temp;

    x_note_fn_call(130,66);
    temp = File_system_directory_search_cache;
    File_system_directory_search_cache = Nil;
    return VALUES_1(temp);
}

/* RECLAIM-DIRECTORY-SEARCH-CACHE */
Object reclaim_directory_search_cache(directory_search_cache)
    Object directory_search_cache;
{
    Object entry, ab_loop_list_, gensym_pathname_1, ab_loop_list__1;

    x_note_fn_call(130,67);
    entry = Nil;
    ab_loop_list_ = directory_search_cache;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_pathname_1 = Nil;
    ab_loop_list__1 = entry;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    gensym_pathname_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    reclaim_gensym_pathname(gensym_pathname_1);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    reclaim_gensym_tree_1(directory_search_cache);
    return VALUES_1(Qnil);
}

/* COPY-DIRECTORY-SEARCH-CACHE */
Object copy_directory_search_cache(directory_search_cache)
    Object directory_search_cache;
{
    Object entry, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object gensym_pathname_1, ab_loop_list__1, ab_loopvar__3, ab_loopvar__4;
    Object temp;

    x_note_fn_call(130,68);
    entry = Nil;
    ab_loop_list_ = directory_search_cache;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_pathname_1 = Nil;
    ab_loop_list__1 = entry;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    gensym_pathname_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__4 = gensym_cons_1(copy_gensym_pathname(gensym_pathname_1),Nil);
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
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
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

static Object string_constant_50;  /* "~a~a" */

static Object Qgensym_pathnames_equal_p;  /* gensym-pathnames-equal-p */

static Object string_constant_51;  /* "*.*" */

/* GENSYM-PROBE-FILE-USING-CACHE */
Object gensym_probe_file_using_cache(convertable_thing)
    Object convertable_thing;
{
    volatile Object gensym_pathname_1;
    volatile Object gensym_directory_and_above_namestring_1;
    volatile Object directory_pathname;
    volatile Object wildcarded_namestring;
    Object cached_directory_entry_qm, temp, candidate_gensym_pathname;
    Object ab_loop_list_, temp_1, file_system_directory_search_cache;
    Object file_system_directory_search_cache_active_p;
    Object file_system_directory_search_cache_wildcard_string;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(130,69);
    SAVE_STACK();
    if (Directory_cache_use_disabled_p) {
	result = gensym_probe_file(convertable_thing);
	RESTORE_STACK();
	return result;
    }
    if (File_system_directory_search_cache_active_p) {
	gensym_pathname_1 = Qunbound_in_protected_let;
	gensym_directory_and_above_namestring_1 = Qunbound_in_protected_let;
	directory_pathname = Qunbound_in_protected_let;
	wildcarded_namestring = Qunbound_in_protected_let;
	cached_directory_entry_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    gensym_pathname_1 = gensym_pathname(convertable_thing);
	    gensym_directory_and_above_namestring_1 = 
		    gensym_directory_and_above_namestring(1,gensym_pathname_1);
	    directory_pathname = 
		    gensym_pathname(gensym_directory_and_above_namestring_1);
	    wildcarded_namestring = tformat_text_string(3,
		    string_constant_50,
		    gensym_directory_and_above_namestring_1,
		    File_system_directory_search_cache_wildcard_string);
	    cached_directory_entry_qm = assoc(4,directory_pathname,
		    File_system_directory_search_cache,Ktest,
		    SYMBOL_FUNCTION(Qgensym_pathnames_equal_p));
	    if ( !TRUEP(cached_directory_entry_qm)) {
		temp = copy_gensym_pathname(directory_pathname);
		cached_directory_entry_qm = gensym_cons_1(temp,
			gensym_directory(2,wildcarded_namestring,Nil));
		File_system_directory_search_cache = 
			gensym_cons_1(cached_directory_entry_qm,
			File_system_directory_search_cache);
	    }
	    candidate_gensym_pathname = Nil;
	    ab_loop_list_ = CDR(cached_directory_entry_qm);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    candidate_gensym_pathname = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (string_equalw(ISVREF(gensym_pathname_1,(SI_Long)4L),
		    ISVREF(candidate_gensym_pathname,(SI_Long)4L)) && 
		    string_equalw(ISVREF(gensym_pathname_1,(SI_Long)5L),
		    ISVREF(candidate_gensym_pathname,(SI_Long)5L))) {
		temp_1 = ISVREF(gensym_pathname_1,(SI_Long)6L);
		temp = ISVREF(candidate_gensym_pathname,(SI_Long)6L);
		temp_2 = EQL(temp_1,temp);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		SAVE_VALUES(copy_gensym_pathname(candidate_gensym_pathname));
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    SAVE_VALUES(VALUES_1(Qnil));
	  end_1:;
	}
	POP_UNWIND_PROTECT(0);
	if (wildcarded_namestring) {
	    if ( !EQ(wildcarded_namestring,Qunbound_in_protected_let))
		reclaim_text_string(wildcarded_namestring);
	}
	if (directory_pathname) {
	    if ( !EQ(directory_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(directory_pathname);
	}
	if (gensym_directory_and_above_namestring_1) {
	    if ( !EQ(gensym_directory_and_above_namestring_1,
		    Qunbound_in_protected_let))
		reclaim_text_string(gensym_directory_and_above_namestring_1);
	}
	if (gensym_pathname_1) {
	    if ( !EQ(gensym_pathname_1,Qunbound_in_protected_let))
		reclaim_gensym_pathname(gensym_pathname_1);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	file_system_directory_search_cache = Nil;
	file_system_directory_search_cache_active_p = T;
	temp = Nil;
	if (temp);
	else
	    temp = string_constant_51;
	file_system_directory_search_cache_wildcard_string = temp;
	PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_wildcard_string,Qfile_system_directory_search_cache_wildcard_string,file_system_directory_search_cache_wildcard_string,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_active_p,Qfile_system_directory_search_cache_active_p,file_system_directory_search_cache_active_p,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache,Qfile_system_directory_search_cache,file_system_directory_search_cache,
		    0);
	      temp = gensym_probe_file_using_cache(convertable_thing);
	      reclaim_file_system_directory_search_cache();
	      result = VALUES_1(temp);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

/* GENSYM-DIRECTORY-USING-CACHE */
Object gensym_directory_using_cache varargs_1(int, n)
{
    Object convertable_thing;
    Object include_subdirectories_qm, temp;
    volatile Object directory_pathname;
    volatile Object path_list;
    Object file, ab_loop_list_, directory_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1;
    volatile Object gensym_pathname_1;
    volatile Object gensym_directory_and_above_namestring_1;
    volatile Object wildcarded_namestring;
    Object cached_directory_entry_qm, file_directory_if_needed;
    volatile Object subdirectory_directory_if_needed_1;
    Object subdirectory_directory_if_needed, result_1, list_1, l, d_qm, d1_qm;
    Object candidate_gensym_pathname, file_system_directory_search_cache;
    Object file_system_directory_search_cache_active_p;
    Object file_system_directory_search_cache_wildcard_string;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(130,70);
    INIT_ARGS_nonrelocating();
    convertable_thing = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    include_subdirectories_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Directory_cache_use_disabled_p) {
	temp = gensym_directory(2,convertable_thing,Nil);
	if (include_subdirectories_qm) {
	    directory_pathname = Qunbound_in_protected_let;
	    path_list = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(0)) {
		directory_pathname = 
			gensym_make_pathname_with_copied_components(ISVREF(convertable_thing,
			(SI_Long)1L),ISVREF(convertable_thing,(SI_Long)2L),
			ISVREF(convertable_thing,(SI_Long)3L),Kwild,Nil,
			Nil,Nil);
		path_list = gensym_subdirectories(2,directory_pathname,Nil);
		file = Nil;
		ab_loop_list_ = path_list;
		directory_qm = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		file = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		directory_qm = gensym_file_as_directory(file);
		if (directory_qm) {
		    ab_loopvar__2 = path_cons_1(directory_qm,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		}
		reclaim_gensym_pathname(file);
		goto next_loop;
	      end_loop:
		temp_1 = ab_loopvar_;
		goto end_1;
		temp_1 = Qnil;
	      end_1:;
		SAVE_VALUES(VALUES_1(temp_1));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (path_list) {
		if ( !EQ(path_list,Qunbound_in_protected_let))
		    reclaim_path_list_1(path_list);
	    }
	    if (directory_pathname) {
		if ( !EQ(directory_pathname,Qunbound_in_protected_let))
		    reclaim_gensym_pathname(directory_pathname);
	    }
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    temp_1 = result;
	}
	else
	    temp_1 = Nil;
	RESTORE_STACK();
	return VALUES_1(nconc2(temp,temp_1));
    }
    if (File_system_directory_search_cache_active_p) {
	gensym_pathname_1 = Qunbound_in_protected_let;
	gensym_directory_and_above_namestring_1 = Qunbound_in_protected_let;
	directory_pathname = Qunbound_in_protected_let;
	wildcarded_namestring = Qunbound_in_protected_let;
	cached_directory_entry_qm = Qunbound_in_protected_let;
	file_directory_if_needed = Qunbound_in_protected_let;
	subdirectory_directory_if_needed_1 = Qunbound_in_protected_let;
	subdirectory_directory_if_needed = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    gensym_pathname_1 = gensym_pathname(convertable_thing);
	    gensym_directory_and_above_namestring_1 = 
		    gensym_directory_and_above_namestring(1,gensym_pathname_1);
	    directory_pathname = 
		    gensym_pathname(gensym_directory_and_above_namestring_1);
	    wildcarded_namestring = tformat_text_string(3,
		    string_constant_50,
		    gensym_directory_and_above_namestring_1,
		    File_system_directory_search_cache_wildcard_string);
	    cached_directory_entry_qm = assoc(4,directory_pathname,
		    File_system_directory_search_cache,Ktest,
		    SYMBOL_FUNCTION(Qgensym_pathnames_equal_p));
	    file_directory_if_needed =  !TRUEP(cached_directory_entry_qm) ?
		     gensym_directory(2,wildcarded_namestring,Nil) : Nil;
	    subdirectory_directory_if_needed_1 = 
		    all_subdirectories_in_directory(directory_pathname);
	    if ( !TRUEP(cached_directory_entry_qm)) {
		result_1 = Nil;
		list_1 = subdirectory_directory_if_needed_1;
		l = list_1;
		d_qm = Nil;
		d1_qm = Nil;
	      next_loop_1:
		if ( !TRUEP(l))
		    goto end_loop_1;
		d_qm = string_eq_w(ISVREF(CAR(l),(SI_Long)4L),
			array_constant_11) || string_eq_w(ISVREF(CAR(l),
			(SI_Long)4L),array_constant_12) ? CAR(l) : 
			gensym_file_as_directory(CAR(l));
		if ( !TRUEP(d_qm))
		    d1_qm = CAR(l);
		else if (EQ(d_qm,CAR(l)))
		    d1_qm = CAR(l);
		else {
		    reclaim_gensym_pathname(CAR(l));
		    d1_qm = d_qm;
		}
		if (member(4,d1_qm,result_1,Ktest,
			SYMBOL_FUNCTION(Qgensym_pathnames_equal_p)) || 
			member(4,d1_qm,file_directory_if_needed,Ktest,
			SYMBOL_FUNCTION(Qgensym_pathnames_equal_p)))
		    reclaim_gensym_pathname(d1_qm);
		else
		    result_1 = path_cons_1(d1_qm,result_1);
		l = M_CDR(l);
		goto next_loop_1;
	      end_loop_1:
		subdirectory_directory_if_needed = result_1;
		goto end_2;
		subdirectory_directory_if_needed = Qnil;
	      end_2:;
	    }
	    else
		subdirectory_directory_if_needed = Nil;
	    if ( !TRUEP(cached_directory_entry_qm)) {
		temp_1 = copy_gensym_pathname(directory_pathname);
		cached_directory_entry_qm = gensym_cons_1(temp_1,
			nconc2(file_directory_if_needed,
			subdirectory_directory_if_needed));
		File_system_directory_search_cache = 
			gensym_cons_1(cached_directory_entry_qm,
			File_system_directory_search_cache);
	    }
	    candidate_gensym_pathname = Nil;
	    ab_loop_list_ = CDR(cached_directory_entry_qm);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    candidate_gensym_pathname = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ISVREF(candidate_gensym_pathname,(SI_Long)4L)) &&  
		    !TRUEP(ISVREF(candidate_gensym_pathname,(SI_Long)5L)) 
		    &&  !TRUEP(ISVREF(candidate_gensym_pathname,(SI_Long)6L)))
		temp_2 = TRUEP(include_subdirectories_qm);
	    else if ((EQ(ISVREF(gensym_pathname_1,(SI_Long)4L),Kwild) ? 
		    TRUEP(T) : 
		    TRUEP(string_equalw(ISVREF(gensym_pathname_1,
		    (SI_Long)4L),ISVREF(candidate_gensym_pathname,
		    (SI_Long)4L)))) && (EQ(ISVREF(gensym_pathname_1,
		    (SI_Long)5L),Kwild) ? TRUEP(T) : 
		    TRUEP(string_equalw(ISVREF(gensym_pathname_1,
		    (SI_Long)5L),ISVREF(candidate_gensym_pathname,
		    (SI_Long)5L))))) {
		if (EQ(ISVREF(gensym_pathname_1,(SI_Long)6L),Kwild))
		    temp_2 = TRUEP(T);
		else {
		    temp = ISVREF(gensym_pathname_1,(SI_Long)6L);
		    temp_1 = ISVREF(candidate_gensym_pathname,(SI_Long)6L);
		    temp_2 = EQL(temp,temp_1);
		}
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		ab_loopvar__2 = 
			path_cons_1(copy_gensym_pathname(candidate_gensym_pathname),
			Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    SAVE_VALUES(VALUES_1(ab_loopvar_));
	    goto end_3;
	    SAVE_VALUES(VALUES_1(Qnil));
	  end_3:;
	}
	POP_UNWIND_PROTECT(0);
	if (subdirectory_directory_if_needed_1) {
	    if ( !EQ(subdirectory_directory_if_needed_1,
		    Qunbound_in_protected_let))
		reclaim_path_list_1(subdirectory_directory_if_needed_1);
	}
	if (wildcarded_namestring) {
	    if ( !EQ(wildcarded_namestring,Qunbound_in_protected_let))
		reclaim_text_string(wildcarded_namestring);
	}
	if (directory_pathname) {
	    if ( !EQ(directory_pathname,Qunbound_in_protected_let))
		reclaim_gensym_pathname(directory_pathname);
	}
	if (gensym_directory_and_above_namestring_1) {
	    if ( !EQ(gensym_directory_and_above_namestring_1,
		    Qunbound_in_protected_let))
		reclaim_text_string(gensym_directory_and_above_namestring_1);
	}
	if (gensym_pathname_1) {
	    if ( !EQ(gensym_pathname_1,Qunbound_in_protected_let))
		reclaim_gensym_pathname(gensym_pathname_1);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	file_system_directory_search_cache = Nil;
	file_system_directory_search_cache_active_p = T;
	temp_1 = Nil;
	if (temp_1);
	else
	    temp_1 = string_constant_51;
	file_system_directory_search_cache_wildcard_string = temp_1;
	PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_wildcard_string,Qfile_system_directory_search_cache_wildcard_string,file_system_directory_search_cache_wildcard_string,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_active_p,Qfile_system_directory_search_cache_active_p,file_system_directory_search_cache_active_p,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache,Qfile_system_directory_search_cache,file_system_directory_search_cache,
		    0);
	      temp_1 = gensym_directory_using_cache(2,convertable_thing,
		      include_subdirectories_qm);
	      reclaim_file_system_directory_search_cache();
	      result = VALUES_1(temp_1);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* INITIALIZE-DEFAULT-G2-MODULE-MAP-PATHNAME */
Object initialize_default_g2_module_map_pathname()
{
    x_note_fn_call(130,71);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    array_constant_13,array_constant_14,Knewest,
	    Process_specific_system_pathname);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_g2_module_map_pathname, Qdefault_g2_module_map_pathname);

static Object list_constant_11;    /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

/* INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-MODULE-MAP-COMMAND-LINE */
Object initializer_for_pathname_for_disabling_g2_module_map_command_line()
{
    x_note_fn_call(130,72);
    return gensym_make_pathname_with_copied_components(Nil,Nil,
	    list_constant_11,array_constant_15,array_constant_16,Knewest,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_for_disabling_g2_module_map_command_line, Qpathname_for_disabling_g2_module_map_command_line);

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

/* GET-OR-USE-G2-MODULE-MAP-PATHNAME */
Object get_or_use_g2_module_map_pathname varargs_1(int, n)
{
    Object provide_desired_namestring_p;
    Declare_varargs_nonrelocating;

    x_note_fn_call(130,73);
    INIT_ARGS_nonrelocating();
    provide_desired_namestring_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return provide_pathname_for_launch_time_load(Default_g2_module_map_pathname,
	    Pathname_for_disabling_g2_module_map_command_line,
	    array_constant_17,array_constant_18,array_constant_14,
	    provide_desired_namestring_p);
}

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

/* UPDATE-G2-MODULE-FILE-NAME-MAP */
Object update_g2_module_file_name_map()
{
    Object module_map_pathname_qm, gensym_pathname_1, ab_loop_list_;
    Object ab_loop_desetq_, temp, reclaim_module_map_pathname_qm;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object g2_input_stream_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,74);
    SAVE_STACK();
    module_map_pathname_qm = get_or_use_g2_module_map_pathname(0);
    gensym_pathname_1 = Nil;
    ab_loop_list_ = G2_module_file_name_map;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    gensym_pathname_1 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( ! !EQ(module_map_pathname_qm,gensym_pathname_1)) {
	reclaim_module_map_pathname_qm = Nil;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    reclaim_module_map_pathname_qm = T;
    goto end_1;
    reclaim_module_map_pathname_qm = Qnil;
  end_1:;
    if (module_map_pathname_qm) {
	pathname_used_p = Qunbound_in_protected_let;
	namestring_1 = Qunbound_in_protected_let;
	g2_input_stream_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    pathname_used_p = SIMPLE_VECTOR_P(module_map_pathname_qm) ? 
		    (EQ(ISVREF(module_map_pathname_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		    ? T : Nil) : Qnil;
	    namestring_1 = SIMPLE_VECTOR_P(module_map_pathname_qm) && 
		    EQ(ISVREF(module_map_pathname_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		    ? gensym_namestring(1,module_map_pathname_qm) : 
		    module_map_pathname_qm;
	    g2_input_stream_qm = g2_stream_open_for_input(namestring_1);
	    temp = g2_input_stream_qm ? 
		    update_g2_module_file_name_map_from_map_file_stream(g2_input_stream_qm) 
		    : Nil;
	    SAVE_VALUES(VALUES_1(temp));
	}
	POP_UNWIND_PROTECT(0);
	if (g2_input_stream_qm) {
	    if ( !EQ(g2_input_stream_qm,Qunbound_in_protected_let))
		g2_stream_close(g2_input_stream_qm);
	}
	if (namestring_1) {
	    if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
		if (pathname_used_p)
		    reclaim_text_string(namestring_1);
	    }
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	temp = result;
	if (reclaim_module_map_pathname_qm)
	    reclaim_gensym_pathname(module_map_pathname_qm);
	RESTORE_STACK();
	return VALUES_1(temp);
    }
    else {
	G2_module_file_name_map = Nil;
	RESTORE_STACK();
	return VALUES_1(G2_module_file_name_map);
    }
}

/* UPDATE-G2-MODULE-FILE-NAME-MAP-FROM-MAP-FILE-STREAM */
Object update_g2_module_file_name_map_from_map_file_stream(g2_input_stream)
    Object g2_input_stream;
{
    Object temp;

    x_note_fn_call(130,75);
    temp = read_module_file_name_map_from_stream(g2_input_stream);
    reclaim_module_file_name_map(G2_module_file_name_map);
    G2_module_file_name_map = temp;
    return VALUES_1(G2_module_file_name_map);
}

/* RECLAIM-MODULE-FILE-NAME-MAP */
Object reclaim_module_file_name_map(module_file_name_map)
    Object module_file_name_map;
{
    Object gensym_pathname_1, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(130,76);
    gensym_pathname_1 = Nil;
    ab_loop_list_ = module_file_name_map;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    gensym_pathname_1 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_pathname(gensym_pathname_1);
    goto next_loop;
  end_loop:
    reclaim_gensym_tree_1(module_file_name_map);
    return VALUES_1(Qnil);
}

/* READ-MODULE-FILE-NAME-MAP-FROM-STREAM */
Object read_module_file_name_map_from_stream(input_g2_stream)
    Object input_g2_stream;
{
    Object input_line_qm, module_map_entry_qm, result_so_far, ab_loopvar_;
    Object ab_loopvar__1;

    x_note_fn_call(130,77);
    input_line_qm = Nil;
    module_map_entry_qm = Nil;
    result_so_far = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    input_line_qm = g2_stream_read_line(input_g2_stream);
    if ( !TRUEP(input_line_qm))
	goto end_loop;
    module_map_entry_qm = parse_module_map_line_into_parts(input_line_qm);
    if (module_map_entry_qm) {
	ab_loopvar__1 = gensym_cons_1(module_map_entry_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_so_far = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(result_so_far);
    return VALUES_1(Qnil);
}

/* FIND-MODULE-PATHNAME-MAPPING-IF-ANY */
Object find_module_pathname_mapping_if_any(module)
    Object module;
{
    Object temp, gensym_pathname_mapping_qm;

    x_note_fn_call(130,78);
    temp = assq_function(module,G2_module_file_name_map);
    gensym_pathname_mapping_qm = SECOND(temp);
    if (gensym_pathname_mapping_qm)
	return copy_gensym_pathname(gensym_pathname_mapping_qm);
    else
	return VALUES_1(Nil);
}

/* FIND-MODULE-SPECIFIC-SEARCH-PATH-IF-ANY */
Object find_module_specific_search_path_if_any(module)
    Object module;
{
    Object search_path_qm, p, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(130,79);
    search_path_qm = nthcdr(FIX((SI_Long)2L),assq_function(module,
	    G2_module_file_name_map));
    p = Nil;
    ab_loop_list_ = search_path_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    p = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(copy_gensym_pathname(p),Nil);
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

/* MODULE-NAME-AS-GENSYM-PATHNAME */
Object module_name_as_gensym_pathname(module)
    Object module;
{
    Object symbol_name_text_string_copy, temp;

    x_note_fn_call(130,80);
    symbol_name_text_string_copy = copy_symbol_name(2,module,Nil);
    temp = gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
	    symbol_name_text_string_copy,Nil,Nil,Nil);
    reclaim_text_string(symbol_name_text_string_copy);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Saved_directories_for_module_truename_search, Qsaved_directories_for_module_truename_search);

/* GET-OR-MAKE-DIRECTORY-FOR-MODULE-TRUENAME-SEARCH */
Object get_or_make_directory_for_module_truename_search(wild_name_pathname)
    Object wild_name_pathname;
{
    Object pathname_1, directory_1, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(130,81);
    pathname_1 = Nil;
    directory_1 = Nil;
    ab_loop_list_ = Saved_directories_for_module_truename_search;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    pathname_1 = CAR(ab_loop_desetq_);
    directory_1 = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (gensym_pathnames_equal_p(pathname_1,wild_name_pathname)) {
	temp = directory_1;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	pathname_1 = copy_gensym_pathname(wild_name_pathname);
	directory_1 = gensym_directory(2,pathname_1,Nil);
	Saved_directories_for_module_truename_search = 
		gensym_cons_1(gensym_cons_1(pathname_1,directory_1),
		Saved_directories_for_module_truename_search);
	return VALUES_1(directory_1);
    }
}

/* RECLAIM-SAVED-DIRECTORIES-FOR-MODULE-TRUENAME-SEARCH */
Object reclaim_saved_directories_for_module_truename_search(saved_directories)
    Object saved_directories;
{
    Object cons_1, ab_loop_list_, pathname_1, directory_1, ab_loop_list__1;

    x_note_fn_call(130,82);
    cons_1 = Nil;
    ab_loop_list_ = saved_directories;
    pathname_1 = Nil;
    directory_1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cons_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pathname_1 = CAR(cons_1);
    directory_1 = CDR(cons_1);
    reclaim_gensym_pathname(pathname_1);
    pathname_1 = Nil;
    ab_loop_list__1 = directory_1;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    pathname_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    reclaim_gensym_pathname(pathname_1);
    goto next_loop_1;
  end_loop_1:;
    reclaim_path_list_1(directory_1);
    reclaim_gensym_cons_1(cons_1);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(saved_directories);
    return VALUES_1(Nil);
}

static Object list_constant_12;    /* # */

/* SEARCH-FOR-MODULE-TRUENAME */
Object search_for_module_truename(module,overriding_pathname_qm,
	    current_kb_directory)
    Object module, overriding_pathname_qm, current_kb_directory;
{
    Object saved_directories_for_module_truename_search;
    volatile Object module_pathname_mapping_qm;
    volatile Object module_as_pathname;
    volatile Object series_of_pathnames_to_merge;
    volatile Object mapped_module_file_name;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(130,83);
    SAVE_STACK();
    saved_directories_for_module_truename_search = Qunbound_in_protected_let;
    module_pathname_mapping_qm = Qunbound_in_protected_let;
    module_as_pathname = Qunbound_in_protected_let;
    series_of_pathnames_to_merge = Qunbound_in_protected_let;
    mapped_module_file_name = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Saved_directories_for_module_truename_search,Qsaved_directories_for_module_truename_search,saved_directories_for_module_truename_search,
	    0);
      if (PUSH_UNWIND_PROTECT(0)) {
	  Saved_directories_for_module_truename_search = Nil;
	  module_pathname_mapping_qm = 
		  find_module_pathname_mapping_if_any(module);
	  module_as_pathname = module_name_as_gensym_pathname(module);
	  temp = overriding_pathname_qm ? 
		  gensym_cons_1(overriding_pathname_qm,Nil) : Nil;
	  series_of_pathnames_to_merge = nconc2(temp,
		  nconc2(module_pathname_mapping_qm ? 
		  gensym_cons_1(module_pathname_mapping_qm,Nil) : Nil,
		  gensym_cons_1(module_as_pathname,Nil)));
	  mapped_module_file_name = 
		  merge_series_of_pathnames(series_of_pathnames_to_merge);
	  SAVE_VALUES(search_for_module_truename_in_various_places(mapped_module_file_name,
		  current_kb_directory,list_constant_12));
      }
      POP_UNWIND_PROTECT(0);
      if (mapped_module_file_name) {
	  if ( !EQ(mapped_module_file_name,Qunbound_in_protected_let))
	      reclaim_gensym_pathname(mapped_module_file_name);
      }
      if (series_of_pathnames_to_merge) {
	  if ( !EQ(series_of_pathnames_to_merge,Qunbound_in_protected_let))
	      reclaim_gensym_list_1(series_of_pathnames_to_merge);
      }
      if (module_as_pathname) {
	  if ( !EQ(module_as_pathname,Qunbound_in_protected_let))
	      reclaim_gensym_pathname(module_as_pathname);
      }
      if (module_pathname_mapping_qm) {
	  if ( !EQ(module_pathname_mapping_qm,Qunbound_in_protected_let))
	      reclaim_gensym_pathname(module_pathname_mapping_qm);
      }
      if (Saved_directories_for_module_truename_search) {
	  if ( !EQ(Saved_directories_for_module_truename_search,
		  Qunbound_in_protected_let))
	      reclaim_saved_directories_for_module_truename_search(Saved_directories_for_module_truename_search);
      }
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* SEARCH-FOR-MODULE-TRUENAME-IN-VARIOUS-PLACES */
Object search_for_module_truename_in_various_places(mapped_module_file_name,
	    current_kb_directory,places)
    Object mapped_module_file_name, current_kb_directory, places;
{
    Object place, ab_loop_list_, ab_loop_it_, temp;

    x_note_fn_call(130,84);
    place = Nil;
    ab_loop_list_ = places;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    place = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = place;
    ab_loop_it_ = 
	    search_for_module_truename_with_various_file_types(mapped_module_file_name,
	    current_kb_directory,temp,file_types_for_module());
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qpath_directories;   /* path-directories */

static Object Qdefault_directory;  /* default-directory */

static Object Qlaunch_directory;   /* launch-directory */

/* SEARCH-FOR-MODULE-TRUENAME-WITH-VARIOUS-FILE-TYPES */
Object search_for_module_truename_with_various_file_types(mapped_module_file_name,
	    current_kb_directory,place,file_types)
    Object mapped_module_file_name, current_kb_directory, place, file_types;
{
    Object file_type, ab_loop_list_, ab_loop_it_, directory_file_name;
    Object ab_loop_list__1, directory_file_name_qm;

    x_note_fn_call(130,85);
    file_type = Nil;
    ab_loop_list_ = file_types;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    file_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(place,Qpath_directories)) {
	directory_file_name = Nil;
	ab_loop_list__1 = G2_module_search_path;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	directory_file_name = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = 
		search_for_module_truename_in_directory(mapped_module_file_name,
		file_type,directory_file_name);
	if (ab_loop_it_)
	    goto end_1;
	goto next_loop_1;
      end_loop_1:
	ab_loop_it_ = Qnil;
      end_1:;
    }
    else {
	if (EQ(place,Qdefault_directory))
	    directory_file_name_qm = current_kb_directory;
	else if (EQ(place,Qlaunch_directory))
	    directory_file_name_qm = Process_specific_system_pathname;
	else
	    directory_file_name_qm = Qnil;
	ab_loop_it_ = directory_file_name_qm ? 
		search_for_module_truename_in_directory(mapped_module_file_name,
		file_type,directory_file_name_qm) : Nil;
    }
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SEARCH-FOR-MODULE-TRUENAME-IN-DIRECTORY */
Object search_for_module_truename_in_directory(mapped_module_file_name,
	    file_type,directory_file_name)
    Object mapped_module_file_name, file_type, directory_file_name;
{
    volatile Object directory_pathname;
    volatile Object pathname_1;
    volatile Object pathname_with_type;
    volatile Object wild_name_pathname;
    Object directory_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,86);
    SAVE_STACK();
    directory_pathname = Qunbound_in_protected_let;
    pathname_1 = Qunbound_in_protected_let;
    pathname_with_type = Qunbound_in_protected_let;
    wild_name_pathname = Qunbound_in_protected_let;
    directory_1 = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	directory_pathname = gensym_pathname(directory_file_name);
	pathname_1 = 
		gensym_merge_pathnames_function(mapped_module_file_name,
		directory_pathname,Nil);
	pathname_with_type = 
		gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Nil,file_type,Nil,pathname_1);
	wild_name_pathname = 
		gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Kwild,Kwild,Nil,pathname_with_type);
	directory_1 = 
		get_or_make_directory_for_module_truename_search(wild_name_pathname);
	SAVE_VALUES(get_less_case_sensitive_gensym_pathname_given_directory(pathname_with_type,
		directory_1));
    }
    POP_UNWIND_PROTECT(0);
    if (wild_name_pathname) {
	if ( !EQ(wild_name_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(wild_name_pathname);
    }
    if (pathname_with_type) {
	if ( !EQ(pathname_with_type,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_with_type);
    }
    if (pathname_1) {
	if ( !EQ(pathname_1,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_1);
    }
    if (directory_pathname) {
	if ( !EQ(directory_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(directory_pathname);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_52;  /* "No KB file could be found for the module ~
				    *        named ~a~a~a; cancelling the loading of ~a from ~s."
				    */

static Object string_constant_53;  /* ", required by " */

/* GIVE-MODULE-NOT-FOUND-WARNING */
Object give_module_not_found_warning(sought_after_module,
	    requiring_module_qm,top_level_module,top_level_gensym_pathname)
    Object sought_after_module, requiring_module_qm, top_level_module;
    Object top_level_gensym_pathname;
{
    Object pathname_text_string, temp;

    x_note_fn_call(130,87);
    pathname_text_string = gensym_namestring_as_text_string(1,
	    top_level_gensym_pathname);
    temp = requiring_module_qm;
    if (temp);
    else
	temp = string_constant_11;
    notify_user(6,string_constant_52,sought_after_module,
	    requiring_module_qm ? string_constant_53 : string_constant_11,
	    temp,top_level_module,pathname_text_string);
    return reclaim_text_string(pathname_text_string);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_attribute_file_pathname_qm, Qcurrent_attribute_file_pathname_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_statistics_file_pathname_qm, Qcurrent_statistics_file_pathname_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_foreign_image_pathname_qm, Qcurrent_foreign_image_pathname_qm);

/* NON-RECLAIMABLE-PATHNAME */
Object non_reclaimable_pathname(a_pathname)
    Object a_pathname;
{
    Object temp;

    x_note_fn_call(130,88);
    temp = EQ(a_pathname,Current_kb_pathname_qm) ? T : Nil;
    if (temp);
    else
	temp = EQ(a_pathname,Log_file_default_pathname_qm) ? T : Nil;
    if (temp);
    else
	temp = EQ(a_pathname,Current_attribute_file_pathname_qm) ? T : Nil;
    if (temp);
    else
	temp = EQ(a_pathname,Current_statistics_file_pathname_qm) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(a_pathname,Current_foreign_image_pathname_qm) ? 
		T : Nil);
}

/* RECLAIM-PATHNAMES-IN-LOADING-SCHEDULE */
Object reclaim_pathnames_in_loading_schedule(module_loading_schedule)
    Object module_loading_schedule;
{
    Object list_qm, ab_loop_list_, text_string_qm, ab_loop_list__1;
    Object pathname_qm;

    x_note_fn_call(130,89);
    list_qm = Nil;
    ab_loop_list_ = module_loading_schedule;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    list_qm = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(list_qm)) {
	text_string_qm = Nil;
	ab_loop_list__1 = list_qm;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	text_string_qm = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (text_string_p(text_string_qm))
	    reclaim_text_string(text_string_qm);
	goto next_loop_1;
      end_loop_1:;
	pathname_qm = Nil;
	ab_loop_list__1 = list_qm;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	pathname_qm = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (SIMPLE_VECTOR_P(pathname_qm) && EQ(ISVREF(pathname_qm,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) && 
		 !TRUEP(non_reclaimable_pathname(pathname_qm)))
	    reclaim_gensym_pathname(pathname_qm);
	goto next_loop_2;
      end_loop_2:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-MODULE-LOADING-SCHEDULE */
Object reclaim_module_loading_schedule(module_loading_schedule)
    Object module_loading_schedule;
{
    x_note_fn_call(130,90);
    return reclaim_gensym_tree_1(module_loading_schedule);
}

DEFINE_VARIABLE_WITH_SYMBOL(Modules_scheduled_so_far_by_save_all_modules_of_kb, Qmodules_scheduled_so_far_by_save_all_modules_of_kb);

DEFINE_VARIABLE_WITH_SYMBOL(Kb_module_currently_to_save_qm, Qkb_module_currently_to_save_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_modularity_consistency_checking_qm, Qinhibit_modularity_consistency_checking_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_directory_binding_alist, Qcurrent_module_directory_binding_alist);

DEFINE_VARIABLE_WITH_SYMBOL(Current_module_pathname_override_binding_alist, Qcurrent_module_pathname_override_binding_alist);

DEFINE_VARIABLE_WITH_SYMBOL(Modules_scheduled_so_far, Qmodules_scheduled_so_far);

/* CREATE-MODULE-SAVING-SCHEDULE */
Object create_module_saving_schedule(module,current_default_pathname,
	    include_required_qm,override_pathname_qm,use_clear_text_qm,
	    only_changed_modules_qm)
    Object module, current_default_pathname, include_required_qm;
    Object override_pathname_qm, use_clear_text_qm, only_changed_modules_qm;
{
    Object current_module_pathname_override_binding_alist;
    Object current_module_directory_binding_alist, modules_scheduled_so_far;
    Object changed_modules, list_1, ab_loop_list_;
    Declare_special(3);
    Object result;

    x_note_fn_call(130,91);
    update_g2_module_file_name_map();
    current_module_pathname_override_binding_alist = override_pathname_qm ?
	     gensym_cons_1(gensym_list_2(module,override_pathname_qm),Nil) 
	    : Nil;
    current_module_directory_binding_alist = Nil;
    modules_scheduled_so_far = Nil;
    changed_modules = only_changed_modules_qm ? 
	    modules_with_unsaved_changes() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Modules_scheduled_so_far,Qmodules_scheduled_so_far,modules_scheduled_so_far,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_module_directory_binding_alist,Qcurrent_module_directory_binding_alist,current_module_directory_binding_alist,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Current_module_pathname_override_binding_alist,Qcurrent_module_pathname_override_binding_alist,current_module_pathname_override_binding_alist,
		0);
	  create_module_saving_schedule_1(module,current_default_pathname,
		  include_required_qm,use_clear_text_qm,T,changed_modules);
	  list_1 = Nil;
	  ab_loop_list_ = Current_module_pathname_override_binding_alist;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  list_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  reclaim_gensym_list_1(list_1);
	  goto next_loop;
	end_loop:;
	  reclaim_gensym_list_1(Current_module_pathname_override_binding_alist);
	  reclaim_gensym_list_1(changed_modules);
	  result = VALUES_1(Modules_scheduled_so_far);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CREATE-MODULE-SAVING-SCHEDULE-1 */
Object create_module_saving_schedule_1(module,current_default_pathname,
	    include_required_qm,use_clear_text_qm,top_module_qm,
	    changed_modules)
    Object module, current_default_pathname, include_required_qm;
    Object use_clear_text_qm, top_module_qm, changed_modules;
{
    Object module_information_instance_qm;

    x_note_fn_call(130,92);
    if ( !TRUEP(assq_function(module,Modules_scheduled_so_far))) {
	module_information_instance_qm = 
		lookup_kb_specific_property_value(module,
		Module_information_instance_for_module_qm_kbprop);
	if (module_information_instance_qm) {
	    if (module_hierarchy_contains_cyclic_dependency_p(module_information_instance_qm)) 
			{
		reclaim_gensym_tree_1(Modules_scheduled_so_far);
		Modules_scheduled_so_far = Qnil;
	    }
	    else
		create_module_saving_schedule_2(module,
			current_default_pathname,
			module_information_instance_qm,include_required_qm,
			use_clear_text_qm,top_module_qm,changed_modules);
	}
    }
    return VALUES_1(Nil);
}

/* GENSYM-PATHNAME-READ-ONLY-P */
Object gensym_pathname_read_only_p(convertible_thing)
    Object convertible_thing;
{
    volatile Object gensym_truename_qm;
    volatile Object truename_text_string_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,93);
    SAVE_STACK();
    gensym_truename_qm = Qunbound_in_protected_let;
    truename_text_string_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	gensym_truename_qm = gensym_probe_file(convertible_thing);
	truename_text_string_qm = gensym_truename_qm ? gensym_namestring(1,
		gensym_truename_qm) : Nil;
	if (truename_text_string_qm)
	    SAVE_VALUES(VALUES_1( 
		    !TRUEP(g2_stream_probe_file_for_write(truename_text_string_qm)) 
		    ? T : Nil));
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (truename_text_string_qm) {
	if ( !EQ(truename_text_string_qm,Qunbound_in_protected_let))
	    reclaim_text_string(truename_text_string_qm);
    }
    if (gensym_truename_qm) {
	if ( !EQ(gensym_truename_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(gensym_truename_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qsave_in_clear_text_by_default;  /* save-in-clear-text-by-default */

/* CREATE-MODULE-SAVING-SCHEDULE-2 */
Object create_module_saving_schedule_2(module,current_default_pathname,
	    module_information_instance,include_required_qm,
	    use_clear_text_qm,top_module_qm,changed_modules)
    Object module, current_default_pathname, module_information_instance;
    Object include_required_qm, use_clear_text_qm, top_module_qm;
    Object changed_modules;
{
    Object entry_qm, mapped_module_pathname_qm, required_module, ab_loop_list_;
    Object clear_text_requested_qm, clear_text_prohibited_qm, temp;
    Object gensym_pathname_1, read_only_qm, source_code_control_troubles_qm;
    Object gensymed_symbol, gensymed_symbol_1, gensym_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2, module_saving_schedule;

    x_note_fn_call(130,94);
    entry_qm = assq_function(module,
	    Current_module_pathname_override_binding_alist);
    mapped_module_pathname_qm = entry_qm ? 
	    copy_gensym_pathname(SECOND(entry_qm)) : Nil;
    if (mapped_module_pathname_qm);
    else
	mapped_module_pathname_qm = 
		find_module_pathname_mapping_if_any(module);
    if (mapped_module_pathname_qm)
	Current_module_directory_binding_alist = 
		gensym_cons_1(gensym_list_2(module,
		mapped_module_pathname_qm),
		Current_module_directory_binding_alist);
    if (include_required_qm) {
	required_module = Nil;
	ab_loop_list_ = ISVREF(module_information_instance,(SI_Long)24L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	required_module = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	create_module_saving_schedule_1(required_module,
		current_default_pathname,include_required_qm,
		use_clear_text_qm,Nil,changed_modules);
	goto next_loop;
      end_loop:;
    }
    if ( !TRUEP(changed_modules) || memq_function(module,changed_modules)) {
	clear_text_requested_qm = use_clear_text_qm;
	if (clear_text_requested_qm);
	else
	    clear_text_requested_qm =  !TRUEP(top_module_qm) ? 
		    get_slot_value_if_any_function(get_saving_parameters(module),
		    Qsave_in_clear_text_by_default,Nil) : Qnil;
	clear_text_prohibited_qm = clear_text_requested_qm ? ( ! 
		!TRUEP(module_contains_text_stripped_frames_p(module)) ? T 
		: Nil) : Nil;
	temp = FIRST(Current_module_directory_binding_alist);
	gensym_pathname_1 = make_module_pathname(4,
		module_information_instance,SECOND(temp),
		current_default_pathname,mapped_module_pathname_qm);
	read_only_qm = gensym_pathname_read_only_p(gensym_pathname_1);
	source_code_control_troubles_qm = 
		will_cause_source_code_control_problems_if_saved_p(gensym_pathname_1);
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = module;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = gensym_pathname_1;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = read_only_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = source_code_control_troubles_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = clear_text_prohibited_qm;
	Modules_scheduled_so_far = gensym_cons_1(gensymed_symbol,
		Modules_scheduled_so_far);
    }
    if (mapped_module_pathname_qm) {
	gensym_pop_store = Nil;
	cons_1 = Current_module_directory_binding_alist;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cons_1;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Current_module_directory_binding_alist = next_cons;
	module_saving_schedule = gensym_pop_store;
	reclaim_gensym_pathname(SECOND(module_saving_schedule));
	return reclaim_gensym_tree_1(module_saving_schedule);
    }
    else
	return VALUES_1(Nil);
}

/* CREATE-MODULE-LOADING-SCHEDULE */
Object create_module_loading_schedule(gensym_pathname_to_read,
	    warmboot_case_qm,update_before_loading_qm,clear_kb_qm)
    Object gensym_pathname_to_read, warmboot_case_qm, update_before_loading_qm;
    Object clear_kb_qm;
{
    x_note_fn_call(130,95);
    return create_module_loading_schedule_0(make_module_name_from_kb_pathname(gensym_pathname_to_read),
	    gensym_pathname_to_read,T,gensym_pathname_to_read,
	    warmboot_case_qm,update_before_loading_qm,clear_kb_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Modules_considered_in_loading_schedule_so_far, Qmodules_considered_in_loading_schedule_so_far);

Object Long_operation_posting_delay_for_module_loading_schedule_creation = UNBOUND;

static Object string_constant_54;  /* "~a~%Please wait . . . " */

static Object array_constant_19;   /* # */

/* CREATE-MODULE-LOADING-SCHEDULE-0 */
Object create_module_loading_schedule_0(module,current_kb_directory,
	    include_required_qm,known_module_truename_qm,warmboot_case_qm,
	    update_before_loading_qm,clear_kb_qm)
    Object module, current_kb_directory, include_required_qm;
    Object known_module_truename_qm, warmboot_case_qm;
    Object update_before_loading_qm, clear_kb_qm;
{
    Object temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm;
    Object file_system_directory_search_cache;
    Object file_system_directory_search_cache_active_p;
    Object file_system_directory_search_cache_wildcard_string;
    Object saved_directories_for_module_truename_search;
    Object modules_considered_in_loading_schedule_so_far;
    Object current_module_directory_binding_alist, modules_scheduled_so_far;
    Object gensymed_symbol_2, xa, ya;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(11);
    Object result;

    x_note_fn_call(130,96);
    SAVE_STACK();
    temp = make_message(1,tformat_text_string(2,string_constant_54,
	    array_constant_19));
    current_long_operation_notification_workspace = make_workspace(6,
	    Qtemporary_workspace,Nil,temp,Nil,
	    Width_for_prominent_notification_workspaces,
	    Height_for_prominent_notification_workspaces);
    PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
	    10);
      frame_serial_number = 
	      copy_frame_serial_number(Current_frame_serial_number);
      kb_serial_number = Current_kb_serial_number;
      fixnum_time_at_start_of_current_long_notification = 
	      c_native_clock_ticks_or_cache(Nil,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
	      9);
	if (PUSH_UNWIND_PROTECT(1)) {
	    doing_long_operation_with_notification_qm = T;
	    long_operation_notification_has_been_put_up_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
		    8);
	      PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
		      7);
		if ( !TRUEP(T)) {
		    if (Doing_long_operation_with_notification_qm &&  
			    !TRUEP(Long_operation_notification_has_been_put_up_qm)) 
				{
			gensymed_symbol = 
				IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
			gensymed_symbol_1 = 
				IFIX(Fixnum_time_at_start_of_current_long_notification);
			if (gensymed_symbol >= gensymed_symbol_1)
			    temp = FIX(gensymed_symbol - gensymed_symbol_1);
			else {
			    gensymed_symbol = gensymed_symbol - 
				    gensymed_symbol_1;
			    gensymed_symbol = gensymed_symbol + 
				    IFIX(Most_positive_fixnum);
			    temp = FIX(gensymed_symbol + (SI_Long)1L);
			}
			temp_1 = FIXNUM_GE(temp,
				fixnum_time_interval(FIX((SI_Long)0L)));
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			put_up_long_operation_notification_now();
		}
		file_system_directory_search_cache = Nil;
		file_system_directory_search_cache_active_p = T;
		temp = Nil;
		if (temp);
		else
		    temp = string_constant_51;
		file_system_directory_search_cache_wildcard_string = temp;
		PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_wildcard_string,Qfile_system_directory_search_cache_wildcard_string,file_system_directory_search_cache_wildcard_string,
			6);
		  PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache_active_p,Qfile_system_directory_search_cache_active_p,file_system_directory_search_cache_active_p,
			  5);
		    PUSH_SPECIAL_WITH_SYMBOL(File_system_directory_search_cache,Qfile_system_directory_search_cache,file_system_directory_search_cache,
			    4);
		      saved_directories_for_module_truename_search = 
			      Qunbound_in_protected_let;
		      modules_considered_in_loading_schedule_so_far = 
			      Qunbound_in_protected_let;
		      PUSH_SPECIAL_WITH_SYMBOL(Modules_considered_in_loading_schedule_so_far,Qmodules_considered_in_loading_schedule_so_far,modules_considered_in_loading_schedule_so_far,
			      3);
			PUSH_SPECIAL_WITH_SYMBOL(Saved_directories_for_module_truename_search,Qsaved_directories_for_module_truename_search,saved_directories_for_module_truename_search,
				2);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      Saved_directories_for_module_truename_search 
				      = Nil;
			      Modules_considered_in_loading_schedule_so_far 
				      = Nil;
			      update_g2_module_file_name_map();
			      current_module_directory_binding_alist = Nil;
			      modules_scheduled_so_far = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Modules_scheduled_so_far,Qmodules_scheduled_so_far,modules_scheduled_so_far,
				      1);
				PUSH_SPECIAL_WITH_SYMBOL(Current_module_directory_binding_alist,Qcurrent_module_directory_binding_alist,current_module_directory_binding_alist,
					0);
				  create_module_loading_schedule_1(module,
					  current_kb_directory,
					  include_required_qm,
					  known_module_truename_qm,Nil,
					  warmboot_case_qm,
					  update_before_loading_qm,
					  clear_kb_qm);
				  temp = 
					  nreverse_canonically(Modules_scheduled_so_far);
				POP_SPECIAL();
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp));
			  }
			  POP_UNWIND_PROTECT(0);
			  if (Modules_considered_in_loading_schedule_so_far) {
			      if ( 
				      !EQ(Modules_considered_in_loading_schedule_so_far,
				      Qunbound_in_protected_let))
				  reclaim_gensym_list_1(Modules_considered_in_loading_schedule_so_far);
			  }
			  if (Saved_directories_for_module_truename_search) {
			      if ( 
				      !EQ(Saved_directories_for_module_truename_search,
				      Qunbound_in_protected_let))
				  reclaim_saved_directories_for_module_truename_search(Saved_directories_for_module_truename_search);
			  }
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  temp = result;
			POP_SPECIAL();
		      POP_SPECIAL();
		      SAVE_VALUES(VALUES_1(temp));
		      reclaim_file_system_directory_search_cache();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
	    gensymed_symbol_2 = 
		    ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)3L);
	    temp_1 = 
		    SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
		    ? 
		    EQ(ISVREF(Current_long_operation_notification_workspace,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			IFIX(gensymed_symbol_2) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number))
		temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			FIXNUM_LT(frame_serial_number,gensymed_symbol_2) : 
			TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_2))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number);
		ya = M_CAR(gensymed_symbol_2);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number),
			    M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    delete_frame(Current_long_operation_notification_workspace);
	reclaim_frame_serial_number(frame_serial_number);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* CREATE-MODULE-LOADING-SCHEDULE-1 */
Object create_module_loading_schedule_1(module,current_kb_directory,
	    include_required_qm,known_module_truename_qm,
	    requiring_module_qm,warmboot_case_qm,update_before_loading_qm,
	    clear_kb_qm)
    Object module, current_kb_directory, include_required_qm;
    Object known_module_truename_qm, requiring_module_qm, warmboot_case_qm;
    Object update_before_loading_qm, clear_kb_qm;
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;

    x_note_fn_call(130,97);
    if (Doing_long_operation_with_notification_qm &&  
	    !TRUEP(Long_operation_notification_has_been_put_up_qm)) {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = 
		IFIX(Fixnum_time_at_start_of_current_long_notification);
	if (gensymed_symbol >= gensymed_symbol_1)
	    temp = FIX(gensymed_symbol - gensymed_symbol_1);
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    temp = FIX(gensymed_symbol + (SI_Long)1L);
	}
	temp_1 = FIXNUM_GE(temp,
		fixnum_time_interval(Long_operation_posting_delay_for_module_loading_schedule_creation));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	put_up_long_operation_notification_now();
    if ( !TRUEP(memq_function(module,
	    Modules_considered_in_loading_schedule_so_far)))
	return create_module_loading_schedule_2(module,
		current_kb_directory,include_required_qm,
		known_module_truename_qm,requiring_module_qm,
		warmboot_case_qm,update_before_loading_qm,clear_kb_qm);
    else
	return VALUES_1(Nil);
}

static Object Qrequired_modules;   /* required-modules */

/* CREATE-MODULE-LOADING-SCHEDULE-2 */
Object create_module_loading_schedule_2(module,current_kb_directory,
	    include_required_qm,known_module_truename_qm,
	    requiring_module_qm,warmboot_case_qm,update_before_loading_qm,
	    clear_kb_qm)
    Object module, current_kb_directory, include_required_qm;
    Object known_module_truename_qm, requiring_module_qm, warmboot_case_qm;
    Object update_before_loading_qm, clear_kb_qm;
{
    Object module_directory_binding_qm, mapped_default_directory_qm;
    Object module_truename_qm, temp, gensymed_symbol, gensymed_symbol_1;
    Object initial_kb_plist, module_scc_warning_qm, directly_required_modules;
    Object temp_1, required_module, ab_loop_list_, gensym_pop_store, cons_1;
    Object next_cons, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(130,98);
    module_directory_binding_qm = find_module_pathname_mapping_if_any(module);
    if (module_directory_binding_qm)
	Current_module_directory_binding_alist = 
		gensym_cons_1(gensym_list_2(module,
		module_directory_binding_qm),
		Current_module_directory_binding_alist);
    mapped_default_directory_qm = Nil;
    module_truename_qm = known_module_truename_qm ? 
	    copy_gensym_pathname(known_module_truename_qm) : Nil;
    if (module_truename_qm);
    else {
	temp = FIRST(Current_module_directory_binding_alist);
	result = find_module_truename(module,SECOND(temp),
		current_kb_directory,Nil);
	MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	mapped_default_directory_qm = gensymed_symbol_1;
	module_truename_qm = gensymed_symbol;
    }
    initial_kb_plist = Nil;
    module_scc_warning_qm = Nil;
    directly_required_modules = Nil;
    if (module_truename_qm) {
	temp_1 = module_truename_qm;
	temp =  !TRUEP(clear_kb_qm) ? T : Nil;
	if (temp);
	else
	    temp = requiring_module_qm;
	result = read_initial_plist(temp_1,update_before_loading_qm,temp);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,initial_kb_plist,module_scc_warning_qm);
    set_initial_plist_for_loaded_module(module,initial_kb_plist);
    directly_required_modules = getf(initial_kb_plist,Qrequired_modules,_);
    if ( !TRUEP(initial_kb_plist))
	module_truename_qm = Nil;
    Modules_considered_in_loading_schedule_so_far = gensym_cons_1(module,
	    Modules_considered_in_loading_schedule_so_far);
    if (include_required_qm) {
	required_module = Nil;
	ab_loop_list_ = directly_required_modules;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	required_module = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	create_module_loading_schedule_1(required_module,
		current_kb_directory,include_required_qm,Nil,module,
		warmboot_case_qm,update_before_loading_qm,clear_kb_qm);
	goto next_loop;
      end_loop:;
    }
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = module;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = module_truename_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = mapped_default_directory_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = requiring_module_qm;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = module_scc_warning_qm;
    Modules_scheduled_so_far = gensym_cons_1(gensymed_symbol,
	    Modules_scheduled_so_far);
    if (module_directory_binding_qm) {
	gensym_pop_store = Nil;
	cons_1 = Current_module_directory_binding_alist;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = cons_1;
		temp_2 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
	    }
	    else {
		temp_2 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
		temp_2 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Current_module_directory_binding_alist = next_cons;
	return reclaim_gensym_tree_1(gensym_pop_store);
    }
    else
	return VALUES_1(Nil);
}

/* FIND-MODULE-TRUENAME */
Object find_module_truename(module,relative_default_directory_qm,
	    current_kb_directory,overriding_pathname_qm)
    Object module, relative_default_directory_qm, current_kb_directory;
    Object overriding_pathname_qm;
{
    volatile Object module_pathname_mapping_qm;
    volatile Object module_as_pathname;
    volatile Object series_of_pathnames_to_merge;
    volatile Object mapped_module_file_name;
    volatile Object series_of_directories_to_merge;
    Object mapped_default_directory, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,99);
    SAVE_STACK();
    module_pathname_mapping_qm = Qunbound_in_protected_let;
    module_as_pathname = Qunbound_in_protected_let;
    series_of_pathnames_to_merge = Qunbound_in_protected_let;
    mapped_module_file_name = Qunbound_in_protected_let;
    series_of_directories_to_merge = Qunbound_in_protected_let;
    mapped_default_directory = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	module_pathname_mapping_qm = 
		find_module_pathname_mapping_if_any(module);
	module_as_pathname = module_name_as_gensym_pathname(module);
	temp = overriding_pathname_qm ? 
		gensym_cons_1(overriding_pathname_qm,Nil) : Nil;
	series_of_pathnames_to_merge = nconc2(temp,
		nconc2(module_pathname_mapping_qm ? 
		gensym_cons_1(module_pathname_mapping_qm,Nil) : Nil,
		gensym_cons_1(module_as_pathname,Nil)));
	mapped_module_file_name = 
		merge_series_of_pathnames(series_of_pathnames_to_merge);
	series_of_directories_to_merge = 
		nconc2(relative_default_directory_qm ? 
		gensym_cons_1(relative_default_directory_qm,Nil) : Nil,
		gensym_cons_1(current_kb_directory,Nil));
	mapped_default_directory = 
		merge_series_of_pathnames(series_of_directories_to_merge);
	temp = 
		search_for_module_truename_in_various_places(mapped_module_file_name,
		mapped_default_directory,list_constant_12);
	SAVE_VALUES(VALUES_2(temp,mapped_default_directory));
    }
    POP_UNWIND_PROTECT(0);
    if (series_of_directories_to_merge) {
	if ( !EQ(series_of_directories_to_merge,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(series_of_directories_to_merge);
    }
    if (mapped_module_file_name) {
	if ( !EQ(mapped_module_file_name,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(mapped_module_file_name);
    }
    if (series_of_pathnames_to_merge) {
	if ( !EQ(series_of_pathnames_to_merge,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(series_of_pathnames_to_merge);
    }
    if (module_as_pathname) {
	if ( !EQ(module_as_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(module_as_pathname);
    }
    if (module_pathname_mapping_qm) {
	if ( !EQ(module_pathname_mapping_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(module_pathname_mapping_qm);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Pathname_with_default_type_if_required_for_module_pathnames_qm, Qpathname_with_default_type_if_required_for_module_pathnames_qm);

static Object array_constant_20;   /* # */

/* MAKE-PATHNAME-WITH-DEFAULT-TYPE-FOR-MODULES */
Object make_pathname_with_default_type_for_modules()
{
    x_note_fn_call(130,100);
    return gensym_make_pathname_with_copied_components(Nil,Nil,Nil,Nil,
	    array_constant_20,Nil,Nil);
}

static Object Knone;               /* :none */

/* MAKE-MODULE-PATHNAME */
Object make_module_pathname varargs_1(int, n)
{
    Object module_information_instance, relative_default_directory_pathname_qm;
    Object current_default_pathname;
    Object override_pathname_qm, module;
    volatile Object module_as_pathname;
    Object kb_module_file_name_qm;
    volatile Object module_info_pathname_string_qm;
    volatile Object module_info_pathname_qm;
    volatile Object enough_pathname_of_module_loaded_qm;
    volatile Object series_of_default_pathnames;
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,101);
    INIT_ARGS_nonrelocating();
    module_information_instance = REQUIRED_ARG_nonrelocating();
    relative_default_directory_pathname_qm = REQUIRED_ARG_nonrelocating();
    current_default_pathname = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    override_pathname_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    module = Qunbound_in_protected_let;
    module_as_pathname = Qunbound_in_protected_let;
    kb_module_file_name_qm = Qunbound_in_protected_let;
    module_info_pathname_string_qm = Qunbound_in_protected_let;
    module_info_pathname_qm = Qunbound_in_protected_let;
    enough_pathname_of_module_loaded_qm = Qunbound_in_protected_let;
    series_of_default_pathnames = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	module = ISVREF(module_information_instance,(SI_Long)23L);
	module_as_pathname = module_name_as_gensym_pathname(module);
	kb_module_file_name_qm = ISVREF(module_information_instance,
		(SI_Long)22L);
	module_info_pathname_string_qm = kb_module_file_name_qm ? 
		(SYMBOLP(kb_module_file_name_qm) ? 
		copy_text_string_with_case_conversion(symbol_name_text_string(kb_module_file_name_qm),
		Knone) : copy_text_string(kb_module_file_name_qm)) : Nil;
	module_info_pathname_qm = module_info_pathname_string_qm ? 
		gensym_pathname(module_info_pathname_string_qm) : Nil;
	enough_pathname_of_module_loaded_qm = 
		get_enough_pathname_of_module_loaded_if_any(module);
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)7L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = override_pathname_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = module_info_pathname_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = module_as_pathname;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = relative_default_directory_pathname_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = enough_pathname_of_module_loaded_qm;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = current_default_pathname;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = 
		Pathname_with_default_type_if_required_for_module_pathnames_qm;
	M_CAR(gensymed_symbol_1) = car_new_value;
	series_of_default_pathnames = gensymed_symbol;
	SAVE_VALUES(merge_series_of_pathnames(series_of_default_pathnames));
    }
    POP_UNWIND_PROTECT(0);
    if (series_of_default_pathnames) {
	if ( !EQ(series_of_default_pathnames,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(series_of_default_pathnames);
    }
    if (enough_pathname_of_module_loaded_qm) {
	if ( !EQ(enough_pathname_of_module_loaded_qm,
		Qunbound_in_protected_let))
	    reclaim_gensym_pathname(enough_pathname_of_module_loaded_qm);
    }
    if (module_info_pathname_qm) {
	if ( !EQ(module_info_pathname_qm,Qunbound_in_protected_let)) {
	    if (module_info_pathname_qm)
		reclaim_gensym_pathname(module_info_pathname_qm);
	}
    }
    if (module_info_pathname_string_qm) {
	if ( !EQ(module_info_pathname_string_qm,Qunbound_in_protected_let))
	    reclaim_text_string(module_info_pathname_string_qm);
    }
    if (module_as_pathname) {
	if ( !EQ(module_as_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(module_as_pathname);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Modules_listed_so_far, Qmodules_listed_so_far);

/* LIST-REQUIRED-MODULES */
Object list_required_modules(module)
    Object module;
{
    Object modules_listed_so_far;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,102);
    modules_listed_so_far = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Modules_listed_so_far,Qmodules_listed_so_far,modules_listed_so_far,
	    0);
      list_required_modules_1(module);
      result = delete_gensym_element_1(module,Modules_listed_so_far);
    POP_SPECIAL();
    return result;
}

/* LIST-REQUIRED-MODULES-1 */
Object list_required_modules_1(module)
    Object module;
{
    Object temp, module_information_instance_qm, directly_required_module;
    Object ab_loop_list_;

    x_note_fn_call(130,103);
    temp = member_eql(module,Modules_listed_so_far) ? T : Qnil;
    if (temp)
	return VALUES_1(temp);
    else {
	module_information_instance_qm = 
		lookup_kb_specific_property_value(module,
		Module_information_instance_for_module_qm_kbprop);
	if (module_information_instance_qm) {
	    Modules_listed_so_far = gensym_cons_1(module,
		    Modules_listed_so_far);
	    directly_required_module = Nil;
	    ab_loop_list_ = ISVREF(module_information_instance_qm,
		    (SI_Long)24L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    directly_required_module = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    list_required_modules_1(directly_required_module);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Enable_loading_compiled_kbs_p, Qenable_loading_compiled_kbs_p);

/* ES-L-C */
Object es_l_c()
{
    x_note_fn_call(130,104);
    if ( !TRUEP(Enable_loading_compiled_kbs_p))
	Enable_loading_compiled_kbs_p = T;
    return VALUES_1(Evaluation_true_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Enable_saving_compiled_kbs_p, Qenable_saving_compiled_kbs_p);

DEFINE_VARIABLE_WITH_SYMBOL(Delete_compiled_kb_source_p, Qdelete_compiled_kb_source_p);

DEFINE_VARIABLE_WITH_SYMBOL(Loading_compiled_kb_p, Qloading_compiled_kb_p);

static Object string_constant_55;  /* "The modules in this KB are not consistent; you ~
				    *           therefore cannot save individual modules.  ~
				    *           NO PART OF THIS KB HAS BEEN SAVED!"
				    */

static Object Qsave_modules_of_kb_after_confirmation;  /* save-modules-of-kb-after-confirmation */

/* SAVE-MODULE-OF-KB */
Object save_module_of_kb varargs_1(int, n)
{
    Object default_pathname_qm, module;
    Object include_required_modules_qm, use_clear_text_qm, emit_c_code_qm;
    Object commit_after_saving_qm, only_changed_modules_qm;
    volatile Object default_series;
    volatile Object current_default_pathname;
    Object module_saving_schedule, temp, temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(130,105);
    INIT_ARGS_nonrelocating();
    default_pathname_qm = REQUIRED_ARG_nonrelocating();
    module = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    include_required_modules_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    use_clear_text_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    emit_c_code_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    commit_after_saving_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    only_changed_modules_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    default_series = Qunbound_in_protected_let;
    current_default_pathname = Qunbound_in_protected_let;
    module_saving_schedule = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	default_series = nconc2(default_pathname_qm ? 
		gensym_cons_1(default_pathname_qm,Nil) : Nil,
		gensym_cons_1(Current_kb_pathname_qm,Nil));
	current_default_pathname = merge_series_of_pathnames(default_series);
	module_saving_schedule = create_module_saving_schedule(module,
		current_default_pathname,include_required_modules_qm,
		default_pathname_qm,use_clear_text_qm,only_changed_modules_qm);
	if ( !TRUEP(module_saving_schedule))
	    SAVE_VALUES(notify_user(1,string_constant_55));
	else if (Servicing_workstation_qm &&  !TRUEP(Doing_g2_init_file_p)) {
	    temp = module_saving_schedule;
	    temp_1 = message_for_save_dialog(module_saving_schedule);
	    SAVE_VALUES(post_module_schedule_dialog(Qsaving,temp,temp_1,
		    Qsave_modules_of_kb_after_confirmation,
		    slot_value_list_3(module_saving_schedule,
		    emit_c_code_qm,commit_after_saving_qm),
		    Qreclaim_module_loading_schedule_and_representations_thereof,
		    slot_value_cons_1(module_saving_schedule,Nil)));
	}
	else
	    SAVE_VALUES(save_modules_of_kb_after_confirmation(module_saving_schedule,
		    emit_c_code_qm,commit_after_saving_qm));
    }
    POP_UNWIND_PROTECT(0);
    if (current_default_pathname) {
	if ( !EQ(current_default_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(current_default_pathname);
    }
    if (default_series) {
	if ( !EQ(default_series,Qunbound_in_protected_let))
	    reclaim_gensym_list_1(default_series);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_56;  /* "Save Modules as Shown?" */

static Object string_constant_57;  /* " (note " */

static Object string_constant_58;  /* "that the module~a ~L,& will not be saved, because ~a read-only" */

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

static Object array_constant_23;   /* # */

static Object string_constant_59;  /* ", and also " */

static Object string_constant_60;  /* "that the module~a ~L,& can not be committed, ~
				    *                                            because ~a already been committed by someone else"
				    */

static Object array_constant_24;   /* # */

static Object array_constant_25;   /* # */

static Object string_constant_61;  /* "that the module~a ~L,& will be not saved in clear text ~
				    *                                            because ~a proprietary or text-stripped items"
				    */

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

static Object string_constant_62;  /* ".)" */

/* MESSAGE-FOR-SAVE-DIALOG */
Object message_for_save_dialog(module_saving_schedule)
    Object module_saving_schedule;
{
    Object module, truename_qm, read_only_qm, scc_problems_qm;
    Object clear_text_problems_qm, ab_loop_list_, read_only_modules;
    Object ab_loopvar_, ab_loopvar__1, scc_problem_modules, ab_loopvar__2;
    Object clear_text_problem_modules, ab_loopvar__3, ab_loop_desetq_, temp;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char one_qm;
    Declare_special(5);

    x_note_fn_call(130,106);
    module = Nil;
    truename_qm = Nil;
    read_only_qm = Nil;
    scc_problems_qm = Nil;
    clear_text_problems_qm = Nil;
    ab_loop_list_ = module_saving_schedule;
    read_only_modules = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    scc_problem_modules = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    clear_text_problem_modules = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    truename_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    read_only_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    scc_problems_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    clear_text_problems_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (read_only_qm) {
	ab_loopvar__1 = gensym_cons_1(module,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    read_only_modules = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    if (scc_problems_qm) {
	ab_loopvar__1 = gensym_cons_1(module,Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__1;
	else
	    scc_problem_modules = ab_loopvar__1;
	ab_loopvar__2 = ab_loopvar__1;
    }
    if (clear_text_problems_qm) {
	ab_loopvar__1 = gensym_cons_1(module,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__1;
	else
	    clear_text_problem_modules = ab_loopvar__1;
	ab_loopvar__3 = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
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
	      tformat(1,string_constant_56);
	      if (read_only_modules || scc_problem_modules || 
		      clear_text_problem_modules) {
		  tformat(1,string_constant_57);
		  if (read_only_modules) {
		      one_qm =  !TRUEP(CDR(read_only_modules));
		      tformat(4,string_constant_58,one_qm ? array_constant 
			      : array_constant_21,read_only_modules,one_qm 
			      ? array_constant_22 : array_constant_23);
		  }
		  if (scc_problem_modules) {
		      if (read_only_modules)
			  tformat(1,string_constant_59);
		      one_qm =  !TRUEP(CDR(scc_problem_modules));
		      tformat(4,string_constant_60,one_qm ? array_constant 
			      : array_constant_21,scc_problem_modules,
			      one_qm ? array_constant_24 : array_constant_25);
		  }
		  if (clear_text_problem_modules) {
		      if (read_only_modules || read_only_modules)
			  tformat(1,string_constant_59);
		      one_qm =  !TRUEP(CDR(clear_text_problem_modules));
		      tformat(4,string_constant_61,one_qm ? array_constant 
			      : array_constant_21,
			      clear_text_problem_modules,one_qm ? 
			      array_constant_26 : array_constant_27);
		  }
		  tformat(1,string_constant_62);
	      }
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_gensym_list_1(read_only_modules);
    reclaim_gensym_list_1(scc_problem_modules);
    reclaim_gensym_list_1(clear_text_problem_modules);
    return VALUES_1(temp);
    return VALUES_1(Qnil);
}

static Object Qchecked_items;      /* checked-items */

static Object array_constant_28;   /* # */

static Object string_constant_63;  /* "There are no KB to save." */

/* SAVE-MODULES-OF-KB-AFTER-CONFIRMATION */
Object save_modules_of_kb_after_confirmation(module_saving_schedule,
	    emit_c_code_qm,commit_after_saving_qm)
    Object module_saving_schedule, emit_c_code_qm, commit_after_saving_qm;
{
    Object saving_schedule, need_to_reclaim_qm, plist, checkable_qm;
    Object checked_items_qm, num, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, pathname_1, ab_loop_desetq_, temp;

    x_note_fn_call(130,107);
    reclaim_any_module_schedule_displays();
    saving_schedule = module_saving_schedule;
    need_to_reclaim_qm = Nil;
    if (BOUNDP(Qcurrent_workstation_event) && Current_workstation_event) {
	plist = ISVREF(Current_workstation_event,(SI_Long)10L);
	checkable_qm = getf(plist,Qcheckable,_);
	checked_items_qm = getf(plist,Qchecked_items,_);
	if (checkable_qm) {
	    num = Nil;
	    ab_loop_list_ = checked_items_qm;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    num = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = gensym_cons_1(nth(num,module_saving_schedule),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    saving_schedule = ab_loopvar_;
	    goto end_1;
	    saving_schedule = Qnil;
	  end_1:;
	    need_to_reclaim_qm = T;
	}
    }
    if (saving_schedule) {
	save_kb(4,saving_schedule,Nil,emit_c_code_qm,commit_after_saving_qm);
	if (need_to_reclaim_qm)
	    reclaim_gensym_list_1(saving_schedule);
    }
    else {
	message(array_constant_28);
	notify_user(1,string_constant_63);
    }
    pathname_1 = Nil;
    ab_loop_list_ = module_saving_schedule;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    pathname_1 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_pathname(pathname_1);
    goto next_loop_1;
  end_loop_1:;
    return reclaim_module_saving_schedule(module_saving_schedule);
}

static Object Qkb_save;            /* kb-save */

/* SAVE-ONE-MODULE-OF-KB */
Object save_one_module_of_kb varargs_1(int, n)
{
    Object pathname_1, module;
    Object dont_check_consistency_qm, kb_module_currently_to_save_qm;
    Object inhibit_modularity_consistency_checking_qm;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,108);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    module = REQUIRED_ARG_nonrelocating();
    dont_check_consistency_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    kb_module_currently_to_save_qm = module;
    inhibit_modularity_consistency_checking_qm = dont_check_consistency_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_modularity_consistency_checking_qm,Qinhibit_modularity_consistency_checking_qm,inhibit_modularity_consistency_checking_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Kb_module_currently_to_save_qm,Qkb_module_currently_to_save_qm,kb_module_currently_to_save_qm,
	      0);
	result = save_kb(2,pathname_1,Qkb_save);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* RECLAIM-MODULE-SAVING-SCHEDULE */
Object reclaim_module_saving_schedule(module_saving_schedule)
    Object module_saving_schedule;
{
    x_note_fn_call(130,109);
    return reclaim_module_loading_schedule(module_saving_schedule);
}

static Object string_constant_64;  /* "The items below participate in permanent intermodule relationships ~
				    *                   defined by the relation that follows them, but the items do not ~
				    *                   reside in modules that require the relation module."
				    */

static Object string_constant_65;  /* "The item below participates in a permanent intermodule relationship ~
				    *                   defined by the relation that follows it, but the item does not ~
				    *                   reside in a module that requires the relation module."
				    */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_66;  /* "The items listed below participate in permanent intermodule ~
				    *                              relationships defined by the relation ~NF, but the items do not ~
				    *                              reside in modules that require the relation module ~(~a~): "
				    */

static Object string_constant_67;  /* ", " */

static Object string_constant_68;  /* "(module ~(~a~)) " */

static Object string_constant_69;  /* "~NF" */

/* PRINT-RELATIONS-WITH-RELATED-ITEMS-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM */
Object print_relations_with_related_items_in_modules_that_do_not_require_them(relation_and_related_items)
    Object relation_and_related_items;
{
    Object temp_1, header, results, relation_frame, modules_and_items;
    Object ab_loop_list_, ab_loop_desetq_, relate_item_module, related_items;
    Object ab_loop_list__1, related_item, ab_loop_list__2;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object first_module_p, first_p;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(130,110);
    if (Inspect_command_for_modularity_problems_qm) {
	temp = TRUEP(CDR(relation_and_related_items));
	if (temp);
	else {
	    temp_1 = CAR(relation_and_related_items);
	    temp = TRUEP(CDDR(temp_1));
	}
	if (temp);
	else {
	    temp_1 = CADAR(relation_and_related_items);
	    temp = TRUEP(CDDR(temp_1));
	}
	header = temp ? tformat_text_string(1,string_constant_64) : 
		tformat_text_string(1,string_constant_65);
	results = eval_cons_1(header,Nil);
	relation_frame = Nil;
	modules_and_items = Nil;
	ab_loop_list_ = relation_and_related_items;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	relation_frame = CAR(ab_loop_desetq_);
	modules_and_items = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	relate_item_module = Nil;
	related_items = Nil;
	ab_loop_list__1 = modules_and_items;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	relate_item_module = CAR(ab_loop_desetq_);
	related_items = CDR(ab_loop_desetq_);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	related_item = Nil;
	ab_loop_list__2 = related_items;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	related_item = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	results = eval_cons_1(related_item,results);
	goto next_loop_2;
      end_loop_2:;
	goto next_loop_1;
      end_loop_1:;
	results = eval_cons_1(relation_frame,results);
	goto next_loop;
      end_loop:
	temp_1 = nreverse(results);
	multiple_add_to_results_for_inspect_command(temp_1,
		Inspect_command_for_modularity_problems_qm);
	return VALUES_1(Qnil);
    }
    else {
	relation_frame = Nil;
	modules_and_items = Nil;
	ab_loop_list_ = relation_and_related_items;
	ab_loop_desetq_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	relation_frame = CAR(ab_loop_desetq_);
	modules_and_items = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
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
		      temp_1 = relation_frame;
		      tformat(3,string_constant_66,temp_1,
			      get_module_block_is_in(relation_frame));
		      first_module_p = T;
		      relate_item_module = Nil;
		      related_items = Nil;
		      ab_loop_list__1 = modules_and_items;
		      ab_loop_desetq_ = Nil;
		    next_loop_4:
		      if ( !TRUEP(ab_loop_list__1))
			  goto end_loop_4;
		      ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		      relate_item_module = CAR(ab_loop_desetq_);
		      related_items = CDR(ab_loop_desetq_);
		      ab_loop_list__1 = M_CDR(ab_loop_list__1);
		      if ( !TRUEP(first_module_p))
			  tformat(1,string_constant_67);
		      tformat(2,string_constant_68,relate_item_module);
		      first_p = T;
		      related_item = Nil;
		      ab_loop_list__2 = related_items;
		    next_loop_5:
		      if ( !TRUEP(ab_loop_list__2))
			  goto end_loop_5;
		      related_item = M_CAR(ab_loop_list__2);
		      ab_loop_list__2 = M_CDR(ab_loop_list__2);
		      if ( !TRUEP(first_p))
			  tformat(1,string_constant_67);
		      tformat(2,string_constant_69,related_item);
		      first_p = Nil;
		      goto next_loop_5;
		    end_loop_5:;
		      first_module_p = Nil;
		      goto next_loop_4;
		    end_loop_4:;
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user_1(temp_1);
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	goto next_loop_3;
      end_loop_3:
	return VALUES_1(Qnil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(A_list_of_relations_with_related_items_in_modules_that_do_not_require_them, Qa_list_of_relations_with_related_items_in_modules_that_do_not_require_them);

DEFINE_VARIABLE_WITH_SYMBOL(A_list_of_classes_with_instances_in_modules_that_do_not_require_them, Qa_list_of_classes_with_instances_in_modules_that_do_not_require_them);

DEFINE_VARIABLE_WITH_SYMBOL(Classes_whose_superiors_are_not_defined_in_required_modules, Qclasses_whose_superiors_are_not_defined_in_required_modules);

DEFINE_VARIABLE_WITH_SYMBOL(Classes_not_defined_in_any_module, Qclasses_not_defined_in_any_module);

static Object Qfatal;              /* fatal */

static Object list_constant_13;    /* # */

static Object Qclasses_with_instances_in_modules_that_do_not_require_them;  /* classes-with-instances-in-modules-that-do-not-require-them */

static Object Qrelations_with_related_items_in_modules_that_do_not_require_them;  /* relations-with-related-items-in-modules-that-do-not-require-them */

static Object Qtable;              /* table */

static Object Qtable_in_different_module_than_item_represented;  /* table-in-different-module-than-item-represented */

/* CHECK-SAVABILITY-OF-KB-IN-TERMS-OF-MODULARITY */
Object check_savability_of_kb_in_terms_of_modularity varargs_1(int, n)
{
    Object inspect_command_qm, for_save_qm, current_modularity_problems;
    Object inspect_command_for_modularity_problems_qm;
    Object current_modularity_problems_fatal_qm;
    Object classes_not_defined_in_any_module;
    Object classes_whose_superiors_are_not_defined_in_required_modules;
    Object a_list_of_classes_with_instances_in_modules_that_do_not_require_them;
    Object a_list_of_relations_with_related_items_in_modules_that_do_not_require_them;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, table, workspace_qm;
    Object sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, ab_loop_list_, ab_loop_list__1;
    Object represented_frame, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(130,111);
    INIT_ARGS_nonrelocating();
    SAVE_STACK();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    for_save_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (kb_has_modularity_information_p()) {
	LOCK(Modularity_checking);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_modularity_problems = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_modularity_problems,Qcurrent_modularity_problems,current_modularity_problems,
		    6);
	      inspect_command_for_modularity_problems_qm = inspect_command_qm;
	      PUSH_SPECIAL_WITH_SYMBOL(Inspect_command_for_modularity_problems_qm,Qinspect_command_for_modularity_problems_qm,inspect_command_for_modularity_problems_qm,
		      5);
		current_modularity_problems_fatal_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Current_modularity_problems_fatal_qm,Qcurrent_modularity_problems_fatal_qm,current_modularity_problems_fatal_qm,
			4);
		  check_frame_note_based_modularity_problems(Qfatal,
			  list_constant_13);
		  result = collect_bad_definitions_for_kb(1,for_save_qm);
		  MVS_4(result,classes_not_defined_in_any_module,
			  classes_whose_superiors_are_not_defined_in_required_modules,
			  a_list_of_classes_with_instances_in_modules_that_do_not_require_them,
			  a_list_of_relations_with_related_items_in_modules_that_do_not_require_them);
		  PUSH_SPECIAL_WITH_SYMBOL(A_list_of_relations_with_related_items_in_modules_that_do_not_require_them,Qa_list_of_relations_with_related_items_in_modules_that_do_not_require_them,a_list_of_relations_with_related_items_in_modules_that_do_not_require_them,
			  3);
		    PUSH_SPECIAL_WITH_SYMBOL(A_list_of_classes_with_instances_in_modules_that_do_not_require_them,Qa_list_of_classes_with_instances_in_modules_that_do_not_require_them,a_list_of_classes_with_instances_in_modules_that_do_not_require_them,
			    2);
		      PUSH_SPECIAL_WITH_SYMBOL(Classes_whose_superiors_are_not_defined_in_required_modules,Qclasses_whose_superiors_are_not_defined_in_required_modules,classes_whose_superiors_are_not_defined_in_required_modules,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Classes_not_defined_in_any_module,Qclasses_not_defined_in_any_module,classes_not_defined_in_any_module,
				0);
			  if (Classes_not_defined_in_any_module)
			      emit_kb_modularity_problem(3,Qfatal,
				      Qclasses_not_defined_in_any_module,
				      Classes_not_defined_in_any_module);
			  if (Classes_whose_superiors_are_not_defined_in_required_modules)
			      emit_kb_modularity_problem(3,Qfatal,
				      Qclasses_whose_superiors_are_not_defined_in_required_modules,
				      Classes_whose_superiors_are_not_defined_in_required_modules);
			  if (A_list_of_classes_with_instances_in_modules_that_do_not_require_them)
			      emit_kb_modularity_problem(3,Qfatal,
				      Qclasses_with_instances_in_modules_that_do_not_require_them,
				      A_list_of_classes_with_instances_in_modules_that_do_not_require_them);
			  if (A_list_of_relations_with_related_items_in_modules_that_do_not_require_them)
			      emit_kb_modularity_problem(3,Qfatal,
				      Qrelations_with_related_items_in_modules_that_do_not_require_them,
				      A_list_of_relations_with_related_items_in_modules_that_do_not_require_them);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  scope_conses = Scope_conses;
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  table = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			  0);
		    workspace_qm = Nil;
		    ab_loopvar_ = collect_subclasses(Qtable);
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
		    table = ab_loopvar__1;
		    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		    workspace_qm = get_workspace_if_any(table);
		    if (workspace_qm) {
			sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Kb_workspace_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			gensymed_symbol_3 = table;
			gensymed_symbol_4 = ISVREF(gensymed_symbol_3,
				(SI_Long)1L);
			sub_class_bit_vector = ISVREF(gensymed_symbol_4,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Table_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    gensymed_symbol_4 = Nil;
			    gensymed_symbol_5 = Nil;
			    ab_loop_list_ = ISVREF(gensymed_symbol_3,
				    (SI_Long)19L);
			  next_loop_2:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_2;
			    gensymed_symbol_5 = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    gensymed_symbol_3 = Nil;
			    ab_loop_list__1 = gensymed_symbol_5;
			  next_loop_3:
			    if ( !TRUEP(ab_loop_list__1))
				goto end_loop_3;
			    gensymed_symbol_3 = M_CAR(ab_loop_list__1);
			    ab_loop_list__1 = M_CDR(ab_loop_list__1);
			    if (gensymed_symbol_3 && 
					CONSP(gensymed_symbol_3)) {
				represented_frame = 
					get_slot_represented_by_text_cell_if_any(gensymed_symbol_3);
				if (represented_frame &&  
					!EQ(gensymed_symbol_4,
					represented_frame)) {
				    gensymed_symbol_4 = represented_frame;
				    temp_1 = 
					    get_module_block_is_in(represented_frame);
				    if ( !EQ(temp_1,
					    get_module_block_is_in(table))) {
					Current_modularity_problems_fatal_qm 
						= T;
					emit_kb_modularity_problem(3,
						Qfatal,
						Qtable_in_different_module_than_item_represented,
						gensym_list_2(represented_frame,
						workspace_qm));
				    }
				}
			    }
			    goto next_loop_3;
			  end_loop_3:;
			    goto next_loop_2;
			  end_loop_2:;
			}
		    }
		    goto next_loop;
		  end_loop_1:;
		  POP_SPECIAL();
		  SAVE_VALUES(VALUES_1(Current_modularity_problems_fatal_qm));
		  report_on_modularity_checking();
		  reclaim_modularity_problems();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Modularity_checking);
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

/* MAKE-NEW-TOP-LEVEL-KB-WORKSPACE */
Object make_new_top_level_kb_workspace varargs_1(int, n)
{
    Object class_1;
    Object transient_qm, name_qm, initial_subblock_qm, width_qm, height_qm;
    Object module_qm;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object new_kb_workspace;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,112);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    transient_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    initial_subblock_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    width_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    height_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (transient_qm &&  !TRUEP(name_qm) &&  !TRUEP(initial_subblock_qm) 
	    &&  !TRUEP(module_qm) &&  !TRUEP(ISVREF(Module_information,
	    (SI_Long)8L)) && EQ(ISVREF(Module_information,(SI_Long)23L),
	    ISVREF(Module_information,(SI_Long)21L))) {
	inhibit_updating_module_related_frame_notes_for_all_workspaces_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		0);
	  result = make_new_top_level_kb_workspace_1(class_1,transient_qm,
		  name_qm,initial_subblock_qm,width_qm,height_qm,module_qm);
	POP_SPECIAL();
	return result;
    }
    else {
	new_kb_workspace = make_new_top_level_kb_workspace_1(class_1,
		transient_qm,name_qm,initial_subblock_qm,width_qm,
		height_qm,module_qm);
	return VALUES_1(new_kb_workspace);
    }
}

static Object Qworkspace_margin;   /* workspace-margin */

static Object Qinitial_margin_for_workspaces;  /* initial-margin-for-workspaces */

static Object Qframe_flags;        /* frame-flags */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* MAKE-NEW-TOP-LEVEL-KB-WORKSPACE-1 */
Object make_new_top_level_kb_workspace_1(class_1,transient_qm,name_qm,
	    initial_subblock_qm,width_qm,height_qm,module_qm)
    Object class_1, transient_qm, name_qm, initial_subblock_qm, width_qm;
    Object height_qm, module_qm;
{
    Object do_not_note_permanent_changes_p, class_description_qm, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, default_workspace_margin;
    Object class_specific_workspace_margin, workspace_margin, kb_workspace;
    Object module_to_use_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long svref_new_value_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,113);
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    0);
      temp = TRUEP(Called_within_clear_text_loading);
      if (temp);
      else {
	  class_description_qm = 
		  lookup_global_or_kb_specific_property_value(class_1,
		  Class_description_gkbprop);
	  if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		  (SI_Long)20L))) {
	      skip_list = CDR(Symbol_properties_table);
	      key_value = Qkb_workspace;
	      key_hash_value = SXHASH_SYMBOL_1(Qkb_workspace) & 
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_2:
	      if ( !TRUEP(marked))
		  goto end_loop_1;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
	      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if ( !TRUEP(gensymed_symbol)) {
		  gensymed_symbol = Qkb_workspace;
		  temp_1 = Symbol_properties_table;
		  temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		  gensymed_symbol = set_skip_list_entry(temp_1,
			  FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			  temp_2,gensymed_symbol_1);
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_5:
	      if ( !TRUEP(marked))
		  goto end_loop_4;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	      goto next_loop_5;
	    end_loop_4:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
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
		next_loop_6:
		  if (level < ab_loop_bind_)
		      goto end_loop_6;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_7:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_8:
		  if ( !TRUEP(marked))
		      goto end_loop_7;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		  goto next_loop_8;
		end_loop_7:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		next_loop_9:
		  if (level < ab_loop_bind_)
		      goto end_loop_9;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		next_loop_10:
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_11:
		  if ( !TRUEP(marked))
		      goto end_loop_10;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		  goto next_loop_11;
		end_loop_10:
		  entry_hash = ISVREF(curr,(SI_Long)1L);
		  if (IFIX(entry_hash) < key_hash_value || 
			  IFIX(entry_hash) == key_hash_value &&  
			  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      default_workspace_margin = 
		      ISVREF(get_slot_description_of_class_description_function(Qworkspace_margin,
		      gensymed_symbol,Nil),(SI_Long)6L);
	      skip_list = CDR(Symbol_properties_table);
	      key_value = class_1;
	      key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_14:
	      if ( !TRUEP(marked))
		  goto end_loop_13;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
		  gensymed_symbol = class_1;
		  temp_1 = Symbol_properties_table;
		  temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		  gensymed_symbol = set_skip_list_entry(temp_1,
			  FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			  temp_2,gensymed_symbol_1);
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
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_17:
	      if ( !TRUEP(marked))
		  goto end_loop_16;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_20:
		  if ( !TRUEP(marked))
		      goto end_loop_19;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
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
		      goto end_7;
		  goto next_loop_19;
		end_loop_20:
		end_7:
		  level = level - (SI_Long)1L;
		  goto next_loop_18;
		end_loop_18:;
		  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
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
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
		  MVS_2(result,succ,marked);
		next_loop_23:
		  if ( !TRUEP(marked))
		      goto end_loop_22;
		  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			  level));
		  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		  temp_1 = ATOMIC_REF_OBJECT(reference);
		  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			  T : Nil;
		  result = VALUES_2(temp_1,temp_2);
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
		      goto end_8;
		  goto next_loop_22;
		end_loop_23:
		end_8:
		  level = level - (SI_Long)1L;
		  goto next_loop_21;
		end_loop_21:;
		  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			  key_hash_value ? (EQ(key_value,ISVREF(curr,
			  (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) :
			   Nil;
		  if (resulting_value);
		  else
		      resulting_value = Nil;
	      }
	      gensymed_symbol = resulting_value;
	      class_specific_workspace_margin = 
		      ISVREF(get_slot_description_of_class_description_function(Qworkspace_margin,
		      gensymed_symbol,Nil),(SI_Long)6L);
	      temp = FIXNUM_NE(default_workspace_margin,
		      class_specific_workspace_margin);
	  }
	  else
	      temp = TRUEP(Nil);
      }
      if (temp) {
	  skip_list = CDR(Symbol_properties_table);
	  key_value = class_1;
	  key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_25:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_26:
	  if ( !TRUEP(marked))
	      goto end_loop_25;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
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
	      goto end_9;
	  goto next_loop_25;
	end_loop_26:
	end_9:
	  level = level - (SI_Long)1L;
	  goto next_loop_24;
	end_loop_24:;
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = class_1;
	      temp_1 = Symbol_properties_table;
	      temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	      gensymed_symbol = set_skip_list_entry(temp_1,
		      FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
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
	next_loop_27:
	  if (level < ab_loop_bind_)
	      goto end_loop_27;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_28:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	next_loop_29:
	  if ( !TRUEP(marked))
	      goto end_loop_28;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp_2);
	  MVS_2(result,succ,marked);
	  goto next_loop_29;
	end_loop_28:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_10;
	  goto next_loop_28;
	end_loop_29:
	end_10:
	  level = level - (SI_Long)1L;
	  goto next_loop_27;
	end_loop_27:;
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
	    next_loop_30:
	      if (level < ab_loop_bind_)
		  goto end_loop_30;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_31:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_32:
	      if ( !TRUEP(marked))
		  goto end_loop_31;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
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
		  goto end_11;
	      goto next_loop_31;
	    end_loop_32:
	    end_11:
	      level = level - (SI_Long)1L;
	      goto next_loop_30;
	    end_loop_30:;
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
	    next_loop_33:
	      if (level < ab_loop_bind_)
		  goto end_loop_33;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    next_loop_34:
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	    next_loop_35:
	      if ( !TRUEP(marked))
		  goto end_loop_34;
	      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	      temp_1 = ATOMIC_REF_OBJECT(reference);
	      temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	      result = VALUES_2(temp_1,temp_2);
	      MVS_2(result,succ,marked);
	      goto next_loop_35;
	    end_loop_34:
	      entry_hash = ISVREF(curr,(SI_Long)1L);
	      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		      key_hash_value &&  !EQ(key_value,ISVREF(curr,
		      (SI_Long)2L))) {
		  pred = curr;
		  curr = succ;
	      }
	      else
		  goto end_12;
	      goto next_loop_34;
	    end_loop_35:
	    end_12:
	      level = level - (SI_Long)1L;
	      goto next_loop_33;
	    end_loop_33:;
	      resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		      key_hash_value ? (EQ(key_value,ISVREF(curr,
		      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	      if (resulting_value);
	      else
		  resulting_value = Nil;
	  }
	  gensymed_symbol = resulting_value;
	  workspace_margin = 
		  ISVREF(get_slot_description_of_class_description_function(Qworkspace_margin,
		  gensymed_symbol,Nil),(SI_Long)6L);
      }
      else
	  workspace_margin = 
		  get_slot_value_function(Miscellaneous_parameters,
		  Qinitial_margin_for_workspaces,Nil);
      temp_1 = width_qm;
      if (temp_1);
      else
	  temp_1 = FIX((SI_Long)700L);
      temp_2 = height_qm;
      if (temp_2);
      else
	  temp_2 = FIX((SI_Long)500L);
      kb_workspace = make_workspace(6,class_1,name_qm,initial_subblock_qm,
	      workspace_margin,temp_1,temp_2);
      module_to_use_qm = module_qm;
      if (module_to_use_qm);
      else
	  module_to_use_qm = ISVREF(Module_information,(SI_Long)23L);
      if ( !TRUEP(transient_qm) && module_to_use_qm && 
	      get_reason_module_is_not_editable(1,module_to_use_qm) &&  
	      !TRUEP(allow_unsavable_change_p(module_to_use_qm)))
	  module_to_use_qm = Nil;
      if (transient_qm)
	  set_transient_and_propagate(kb_workspace,Nil);
      else {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(kb_workspace,Qframe_flags);
	  svref_new_value_1 = IFIX(ISVREF(kb_workspace,(SI_Long)4L)) | 
		  (SI_Long)1L;
	  ISVREF(kb_workspace,(SI_Long)4L) = FIX(svref_new_value_1);
	  if (Noting_changes_to_kb_p) {
	      svref_new_value_1 = IFIX(ISVREF(kb_workspace,(SI_Long)5L)) | 
		      (SI_Long)4L;
	      ISVREF(kb_workspace,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
      }
      if (System_is_running || System_has_paused) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(kb_workspace,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	  gensymed_symbol_1 = kb_workspace;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      }
      if (module_to_use_qm)
	  change_slot_value(3,kb_workspace,Qmodule_this_is_part_of_qm,
		  module_to_use_qm);
      temp_2 = kb_workspace;
    POP_SPECIAL();
    return VALUES_1(temp_2);
}

/* GET-MODULE-BLOCK-IS-IN */
Object get_module_block_is_in(block)
    Object block;
{
    Object following_junction_class_definition_qm, superior;
    Object sub_class_bit_vector, temp_1, gensymed_symbol_3, class_defined_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, class_definition, x;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, symbol, property_name;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,114);
    following_junction_class_definition_qm = Nil;
    superior = block;
  next_loop:
    sub_class_bit_vector = ISVREF(ISVREF(superior,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
    if (temp ?  !TRUEP(ISVREF(superior,(SI_Long)18L)) : TRUEP(Nil)) {
	temp_1 = get_lookup_slot_value(superior,Qmodule_this_is_part_of_qm);
	goto end_1;
    }
    gensymed_symbol_3 = 
	    lookup_global_or_kb_specific_property_value(Qsystem_table,
	    Class_description_gkbprop);
    if (gensymed_symbol_3) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
	    temp = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = get_module_for_system_table(block);
	goto end_1;
    }
    temp_1 = superior_frame(superior);
    if (temp_1);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(superior,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(superior,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Class_definition_class_description,
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
	if (temp ?  !TRUEP(following_junction_class_definition_qm) : 
		TRUEP(Nil)) {
	    class_defined_qm = ISVREF(superior,(SI_Long)20L);
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    class_definition = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      if ( !TRUEP(class_defined_qm)) {
		  temp_1 = Nil;
		  goto end_2;
	      }
	      ab_loopvar_ = collect_subclasses(Qclass_definition);
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_2:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop;
		  goto next_loop_2;
		end_loop:
		  temp =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  goto end_loop_1;
	      class_definition = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      sub_class_bit_vector = ISVREF(ISVREF(class_definition,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_definition_class_description,
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
	      if (temp)
		  temp = EQ(ISVREF(class_definition,(SI_Long)32L),
			  class_defined_qm);
	      else {
		  if (memq_function(Qconnection,
			  get_lookup_slot_value_given_default(class_definition,
			  Qclass_inheritance_path_of_definition,Nil))) {
		      x = ISVREF(class_definition,(SI_Long)20L);
		      if (SYMBOLP(x)) {
			  skip_list = CDR(Symbol_properties_table);
			  key_value = x;
			  key_hash_value = SXHASH_SYMBOL_1(x) & 
				  IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_3:
			  if (level < ab_loop_bind_)
			      goto end_loop_2;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_4:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_5:
			  if ( !TRUEP(marked))
			      goto end_loop_3;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_5;
			end_loop_3:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_3;
			  goto next_loop_4;
			end_loop_4:
			end_3:
			  level = level - (SI_Long)1L;
			  goto next_loop_3;
			end_loop_2:;
			  gensymed_symbol_3 = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			  if ( !TRUEP(gensymed_symbol_3)) {
			      gensymed_symbol_3 = x;
			      temp_2 = Symbol_properties_table;
			      temp_1 = 
				      FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
				      & IFIX(Most_positive_fixnum));
			      tail = 
				      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				      Nil);
			      head = 
				      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				      tail);
			      new_cons = 
				      ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index));
			      if (new_cons) {
				  svref_arg_1 = Available_lookup_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  svref_new_value = M_CDR(new_cons);
				  SVREF(svref_arg_1,svref_arg_2) = 
					  svref_new_value;
				  if ( 
					  !TRUEP(ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index)))) {
				      svref_arg_1 = 
					      Available_lookup_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(svref_arg_1,svref_arg_2) = Nil;
				  }
				  gensymed_symbol_4 = new_cons;
			      }
			      else
				  gensymed_symbol_4 = Nil;
			      if ( !TRUEP(gensymed_symbol_4))
				  gensymed_symbol_4 = 
					  replenish_lookup_cons_pool();
			      M_CAR(gensymed_symbol_4) = 
				      Qsymbol_properties_hash_table;
			      new_cons = 
				      ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index));
			      if (new_cons) {
				  svref_arg_1 = Available_lookup_conses_vector;
				  svref_arg_2 = Current_thread_index;
				  svref_new_value = M_CDR(new_cons);
				  SVREF(svref_arg_1,svref_arg_2) = 
					  svref_new_value;
				  if ( 
					  !TRUEP(ISVREF(Available_lookup_conses_vector,
					  IFIX(Current_thread_index)))) {
				      svref_arg_1 = 
					      Available_lookup_conses_tail_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(svref_arg_1,svref_arg_2) = Nil;
				  }
				  gensymed_symbol_5 = new_cons;
			      }
			      else
				  gensymed_symbol_5 = Nil;
			      if ( !TRUEP(gensymed_symbol_5))
				  gensymed_symbol_5 = 
					  replenish_lookup_cons_pool();
			      M_CAR(gensymed_symbol_5) = head;
			      M_CDR(gensymed_symbol_5) = tail;
			      inline_note_allocate_cons(gensymed_symbol_5,
				      Qlookup);
			      M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			      inline_note_allocate_cons(gensymed_symbol_4,
				      Qlookup);
			      gensymed_symbol_3 = 
				      set_skip_list_entry(temp_2,
				      FIX((SI_Long)31L),Qeq,Nil,T,
				      gensymed_symbol_3,temp_1,
				      gensymed_symbol_4);
			  }
			  global_properties = gensymed_symbol_3;
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
			next_loop_6:
			  if (level < ab_loop_bind_)
			      goto end_loop_5;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_7:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_8:
			  if ( !TRUEP(marked))
			      goto end_loop_6;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_8;
			end_loop_6:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_4;
			  goto next_loop_7;
			end_loop_7:
			end_4:
			  level = level - (SI_Long)1L;
			  goto next_loop_6;
			end_loop_5:;
			  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
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
			    next_loop_9:
			      if (level < ab_loop_bind_)
				  goto end_loop_8;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_10:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_11:
			      if ( !TRUEP(marked))
				  goto end_loop_9;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_11;
			    end_loop_9:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_5;
			      goto next_loop_10;
			    end_loop_10:
			    end_5:
			      level = level - (SI_Long)1L;
			      goto next_loop_9;
			    end_loop_8:;
			      kb_specific_value = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (kb_specific_value);
			      else
				  kb_specific_value = 
					  No_specific_property_value;
			  }
			  else
			      kb_specific_value = No_specific_property_value;
			  if ( !EQ(kb_specific_value,
				  No_specific_property_value))
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
			    next_loop_12:
			      if (level < ab_loop_bind_)
				  goto end_loop_11;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			    next_loop_13:
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			    next_loop_14:
			      if ( !TRUEP(marked))
				  goto end_loop_12;
			      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				      (SI_Long)0L),level));
			      reference = ISVREF(ISVREF(curr,(SI_Long)0L),
				      level);
			      temp_2 = ATOMIC_REF_OBJECT(reference);
			      temp_1 = (SI_Long)355L == 
				      ATOMIC_REF_STAMP(reference) ? T : Nil;
			      result = VALUES_2(temp_2,temp_1);
			      MVS_2(result,succ,marked);
			      goto next_loop_14;
			    end_loop_12:
			      entry_hash = ISVREF(curr,(SI_Long)1L);
			      if (IFIX(entry_hash) < key_hash_value || 
				      IFIX(entry_hash) == key_hash_value 
				      &&  !EQ(key_value,ISVREF(curr,
				      (SI_Long)2L))) {
				  pred = curr;
				  curr = succ;
			      }
			      else
				  goto end_6;
			      goto next_loop_13;
			    end_loop_13:
			    end_6:
			      level = level - (SI_Long)1L;
			      goto next_loop_12;
			    end_loop_11:;
			      resulting_value = IFIX(ISVREF(curr,
				      (SI_Long)1L)) == key_hash_value ? 
				      (EQ(key_value,ISVREF(curr,
				      (SI_Long)2L)) ? ISVREF(curr,
				      (SI_Long)3L) : Nil) : Nil;
			      if (resulting_value);
			      else
				  resulting_value = Nil;
			  }
			  temp = TRUEP(resulting_value);
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      symbol = ISVREF(class_definition,(SI_Long)20L);
		      property_name = Class_description_gkbprop;
		      skip_list = CDR(Symbol_properties_table);
		      key_value = symbol;
		      key_hash_value = SXHASH_SYMBOL_1(symbol) & 
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
			  goto end_loop_14;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_16:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_17:
		      if ( !TRUEP(marked))
			  goto end_loop_15;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_17;
		    end_loop_15:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_7;
		      goto next_loop_16;
		    end_loop_16:
		    end_7:
		      level = level - (SI_Long)1L;
		      goto next_loop_15;
		    end_loop_14:;
		      gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol_3)) {
			  gensymed_symbol_3 = symbol;
			  temp_2 = Symbol_properties_table;
			  temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) 
				  & IFIX(Most_positive_fixnum));
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
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_4 = new_cons;
			  }
			  else
			      gensymed_symbol_4 = Nil;
			  if ( !TRUEP(gensymed_symbol_4))
			      gensymed_symbol_4 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_4) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_5 = new_cons;
			  }
			  else
			      gensymed_symbol_5 = Nil;
			  if ( !TRUEP(gensymed_symbol_5))
			      gensymed_symbol_5 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_5) = head;
			  M_CDR(gensymed_symbol_5) = tail;
			  inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			  inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			  gensymed_symbol_3 = set_skip_list_entry(temp_2,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol_3,temp_1,gensymed_symbol_4);
		      }
		      global_properties = gensymed_symbol_3;
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
		    next_loop_18:
		      if (level < ab_loop_bind_)
			  goto end_loop_17;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_19:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		    next_loop_20:
		      if ( !TRUEP(marked))
			  goto end_loop_18;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_1 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_1);
		      MVS_2(result,succ,marked);
		      goto next_loop_20;
		    end_loop_18:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_8;
		      goto next_loop_19;
		    end_loop_19:
		    end_8:
		      level = level - (SI_Long)1L;
		      goto next_loop_18;
		    end_loop_17:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = property_name;
			  key_hash_value = SXHASH_SYMBOL_1(property_name) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_21:
			  if (level < ab_loop_bind_)
			      goto end_loop_20;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_22:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_23:
			  if ( !TRUEP(marked))
			      goto end_loop_21;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_23;
			end_loop_21:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_9;
			  goto next_loop_22;
			end_loop_22:
			end_9:
			  level = level - (SI_Long)1L;
			  goto next_loop_21;
			end_loop_20:;
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
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
			  key_value = property_name;
			  key_hash_value = SXHASH_SYMBOL_1(property_name) 
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
			      goto end_loop_23;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_25:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			next_loop_26:
			  if ( !TRUEP(marked))
			      goto end_loop_24;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_2 = ATOMIC_REF_OBJECT(reference);
			  temp_1 = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_2,temp_1);
			  MVS_2(result,succ,marked);
			  goto next_loop_26;
			end_loop_24:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_10;
			  goto next_loop_25;
			end_loop_25:
			end_10:
			  level = level - (SI_Long)1L;
			  goto next_loop_24;
			end_loop_23:;
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
			  if (resulting_value);
			  else
			      resulting_value = Nil;
		      }
		      gensymed_symbol_3 = resulting_value;
		      temp = 
			      EQ(ISVREF(get_slot_description_of_class_description_function(Qjunction_block_class_for_class,
			      gensymed_symbol_3,Nil),(SI_Long)6L),
			      class_defined_qm);
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      if (temp) {
		  following_junction_class_definition_qm = T;
		  temp_1 = superior_frame(class_definition);
		  goto end_2;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      temp_1 = Qnil;
	    end_2:;
	    POP_SPECIAL();
	}
	else
	    temp_1 = Nil;
    }
    superior = temp_1;
    if ( !TRUEP(superior))
	goto end_loop_26;
    goto next_loop;
  end_loop_26:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

static Object string_constant_70;  /* "~NF-DEFINITION" */

static Object string_constant_71;  /* "The definition ~NF, which has one or more instances, has been ~
				    *        put on the newly created KB workspace ~a."
				    */

/* PUT-WACKO-DEFINITION-ON-KB-WORKSPACE */
Object put_wacko_definition_on_kb_workspace(wacko_definition)
    Object wacko_definition;
{
    Object name_for_new_workspace;

    x_note_fn_call(130,115);
    name_for_new_workspace = intern_text_string(1,tformat_text_string(2,
	    string_constant_70,wacko_definition));
    make_new_top_level_kb_workspace(6,Qkb_workspace,Nil,
	    name_for_new_workspace,wacko_definition,FIX((SI_Long)50L),
	    FIX((SI_Long)50L));
    return notify_user(3,string_constant_71,wacko_definition,
	    name_for_new_workspace);
}

DEFINE_VARIABLE_WITH_SYMBOL(Required_definitions, Qrequired_definitions);

/* WRITE-GHOST-DEFINITIONS */
Object write_ghost_definitions(module_being_saved)
    Object module_being_saved;
{
    Object noting_changes_to_kb_p, required_modules, required_definitions;
    Object definition, ab_loop_list_;
    Declare_special(2);
    Object result;

    x_note_fn_call(130,116);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
	    1);
      required_modules = list_required_modules(module_being_saved);
      required_definitions = collect_ghost_definitions(module_being_saved,
	      required_modules);
      PUSH_SPECIAL_WITH_SYMBOL(Required_definitions,Qrequired_definitions,required_definitions,
	      0);
	definition = Nil;
	ab_loop_list_ = Required_definitions;
	reclaim_gensym_list_1(required_modules);
	if (Required_definitions)
	    write_section_mark_for_kb(CHR('1'));
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	definition = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_frame_for_kb(3,definition,T,T);
	goto next_loop;
      end_loop:
	if (Required_definitions)
	    write_section_mark_for_kb(CHR('2'));
	reclaim_gensym_list_1(Required_definitions);
	result = VALUES_1(Qnil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* WRITE-SECTION-MARK-FOR-KB */
Object write_section_mark_for_kb(char_1)
    Object char_1;
{
    x_note_fn_call(130,117);
    start_new_kb_line();
    write_char_for_kb(CHR('*'));
    return write_char_for_kb(char_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Definitions_not_required, Qdefinitions_not_required);

DEFINE_VARIABLE_WITH_SYMBOL(Connections_in_modules_a_list, Qconnections_in_modules_a_list);

/* COLLECT-GHOST-DEFINITIONS */
Object collect_ghost_definitions(module_being_saved,required_modules)
    Object module_being_saved, required_modules;
{
    Object required_definitions, definitions_not_required;
    Object connections_in_modules_a_list, scope_conses, ab_loopvar_, subclass;
    Object temp, definition, ab_loop_list_;
    SI_Long svref_new_value;
    Declare_special(4);
    Object result;

    x_note_fn_call(130,118);
    required_definitions = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Required_definitions,Qrequired_definitions,required_definitions,
	    3);
      definitions_not_required = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Definitions_not_required,Qdefinitions_not_required,definitions_not_required,
	      2);
	connections_in_modules_a_list = get_connections_in_modules_a_list();
	PUSH_SPECIAL_WITH_SYMBOL(Connections_in_modules_a_list,Qconnections_in_modules_a_list,connections_in_modules_a_list,
		1);
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar_ = Qblock;
	  subclass = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(ab_loopvar_);
	  next_loop:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop;
	    temp = M_CAR(ab_loopvar_);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    subclass = temp;
	    collect_ghost_definition_qm(subclass,module_being_saved,
		    required_modules);
	    goto next_loop;
	  end_loop:;
	  POP_SPECIAL();
	  definition = Nil;
	  ab_loop_list_ = Definitions_not_required;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  definition = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) &  
		  ~(SI_Long)4096L;
	  ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	  goto next_loop_1;
	end_loop_1:;
	  reclaim_gensym_list_1(Definitions_not_required);
	  definition = Nil;
	  ab_loop_list_ = Required_definitions;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  definition = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) &  
		  ~(SI_Long)32L;
	  ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	  goto next_loop_2;
	end_loop_2:;
	  reclaim_gensym_tree_1(Connections_in_modules_a_list);
	  result = nreverse(Required_definitions);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COLLECT-GHOST-DEFINITION? */
Object collect_ghost_definition_qm(class_1,module_being_saved,required_modules)
    Object class_1, module_being_saved, required_modules;
{
    Object definition, class_description_qm, inherited_class, temp_1;
    Object ab_loop_list_, inherited_definition;
    SI_Long svref_new_value;
    char temp;

    x_note_fn_call(130,119);
    definition = lookup_global_or_kb_specific_property_value(class_1,
	    Class_definition_gkbprop);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    temp =  !(class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L)));
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
		(SI_Long)32L);
    if (temp);
    else
	temp = (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
		(SI_Long)4096L);
    if ( !temp) {
	if (EQ(get_module_block_is_in(definition),module_being_saved)) {
	    svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) | 
		    (SI_Long)4096L;
	    ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	    Definitions_not_required = gensym_cons_1(definition,
		    Definitions_not_required);
	    inherited_class = Nil;
	    temp_1 = get_lookup_slot_value_given_default(definition,
		    Qclass_inheritance_path_of_definition,Nil);
	    ab_loop_list_ = CDR(temp_1);
	    inherited_definition = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    inherited_class = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    inherited_definition = 
		    lookup_global_or_kb_specific_property_value(inherited_class,
		    Class_definition_gkbprop);
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(inherited_class,
		    Class_description_gkbprop);
	    if (class_description_qm &&  
		    !TRUEP(ISVREF(class_description_qm,(SI_Long)20L)) ?  
		    !EQ(get_module_block_is_in(inherited_definition),
		    module_being_saved) : TRUEP(Nil))
		collect_ghost_definition(inherited_class,
			module_being_saved,required_modules);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (within_modules_p(definition,required_modules) && 
		strict_instances_within_module_p(class_1,module_being_saved))
	    return collect_ghost_definition(class_1,module_being_saved,
		    required_modules);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-GHOST-DEFINITION */
Object collect_ghost_definition(class_1,module_being_saved,required_modules)
    Object class_1, module_being_saved, required_modules;
{
    Object definition, inherited_class, temp, ab_loop_list_;
    Object inherited_definition, class_description_qm, class_of_definition;
    Object defining_class, defining_class_definition;
    SI_Long svref_new_value;

    x_note_fn_call(130,120);
    definition = lookup_global_or_kb_specific_property_value(class_1,
	    Class_definition_gkbprop);
    if ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	    (SI_Long)32L))) {
	svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) | (SI_Long)32L;
	ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	inherited_class = Nil;
	temp = get_lookup_slot_value_given_default(definition,
		Qclass_inheritance_path_of_definition,Nil);
	ab_loop_list_ = CDR(temp);
	inherited_definition = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	inherited_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(inherited_class,
		Class_description_gkbprop);
	inherited_definition = class_description_qm &&  
		!TRUEP(ISVREF(class_description_qm,(SI_Long)20L)) ? 
		lookup_global_or_kb_specific_property_value(inherited_class,
		Class_definition_gkbprop) : Nil;
	if (inherited_definition &&  
		!EQ(get_module_block_is_in(inherited_definition),
		module_being_saved))
	    collect_ghost_definition(inherited_class,module_being_saved,
		    required_modules);
	goto next_loop;
      end_loop:;
	class_of_definition = 
		ISVREF(ISVREF(lookup_global_or_kb_specific_property_value(class_1,
		Class_definition_gkbprop),(SI_Long)1L),(SI_Long)1L);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(class_of_definition,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    defining_class = Nil;
	    ab_loop_list_ = 
		    get_lookup_slot_value_given_default(lookup_global_or_kb_specific_property_value(class_of_definition,
		    Class_definition_gkbprop),
		    Qclass_inheritance_path_of_definition,Nil);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    defining_class = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(defining_class,
		    Class_description_gkbprop);
	    if (class_description_qm &&  
		    !TRUEP(ISVREF(class_description_qm,(SI_Long)20L))) {
		defining_class_definition = 
			lookup_global_or_kb_specific_property_value(defining_class,
			Class_definition_gkbprop);
		if ( !((SI_Long)0L != 
			(IFIX(ISVREF(defining_class_definition,
			(SI_Long)5L)) & (SI_Long)4096L) || 
			EQ(get_module_block_is_in(defining_class_definition),
			module_being_saved)) && 
			within_modules_p(defining_class_definition,
			required_modules))
		    collect_ghost_definition(defining_class,
			    module_being_saved,required_modules);
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	Required_definitions = gensym_cons_1(definition,Required_definitions);
	return VALUES_1(Required_definitions);
    }
    else
	return VALUES_1(Nil);
}

/* GET-CONNECTIONS-IN-MODULES-A-LIST */
Object get_connections_in_modules_a_list()
{
    Object scope_conses, ab_loopvar_, class_1, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, temp, class_description_qm, a_list, b;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, c, connection_frame_or_class, entry_qm;
    Object ab_less_than_branch_qm_, gensym_modify_macro_using_test_arg_1;
    Object car_1, cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object cdr_new_value;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(130,121);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qconnection;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      class_description_qm = 
	      lookup_global_or_kb_specific_property_value(class_1,
	      Class_description_gkbprop);
      if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
	      (SI_Long)20L))) {
	  ab_loopvar__3 = gensym_cons_1(gensym_cons_1(class_1,Nil),Nil);
	  if (ab_loopvar__2)
	      M_CDR(ab_loopvar__2) = ab_loopvar__3;
	  else
	      ab_loopvar__1 = ab_loopvar__3;
	  ab_loopvar__2 = ab_loopvar__3;
      }
      goto next_loop;
    end_loop:
      a_list = ab_loopvar__1;
      goto end_1;
      a_list = Qnil;
    end_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    b = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qblock);
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_1;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_1;
	  goto next_loop_2;
	end_loop_1:
	  temp_1 =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  goto end_loop_2;
      b = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      scope_conses = Scope_conses;
      ab_node_stack_ = Nil;
      ab_current_node_ = Nil;
      gensymed_symbol = ACCESS_ONCE(ISVREF(b,(SI_Long)14L));
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
      c = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	connection_frame_or_class = Nil;
	class_1 = Nil;
	entry_qm = Nil;
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
      next_loop_3:
      next_loop_4:
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
	      next_loop_5:
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_3;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		ab_current_node_ = ab_less_than_branch_qm_;
		goto next_loop_5;
	      end_loop_3:;
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
		ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),b))
	    goto end_2;
	goto next_loop_4;
      end_loop_4:
      end_2:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_5;
	c = ab_connection_;
	connection_frame_or_class = ISVREF(c,(SI_Long)1L);
	class_1 = SYMBOLP(connection_frame_or_class) ? 
		connection_frame_or_class : 
		ISVREF(ISVREF(connection_frame_or_class,(SI_Long)1L),
		(SI_Long)1L);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	entry_qm = class_description_qm &&  
		!TRUEP(ISVREF(class_description_qm,(SI_Long)20L)) ? 
		assq_function(class_1,a_list) : Nil;
	if (entry_qm) {
	    gensym_modify_macro_using_test_arg_1 = 
		    get_module_connection_is_in(c);
	    car_1 = gensym_modify_macro_using_test_arg_1;
	    cdr_1 = CDR(entry_qm);
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list_ = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    x_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_3;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    temp_1 = TRUEP(Qnil);
	  end_3:;
	    cdr_new_value = temp_1 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	    M_CDR(entry_qm) = cdr_new_value;
	}
	goto next_loop_3;
      end_loop_5:;
      POP_SPECIAL();
      goto next_loop_1;
    end_loop_2:;
    POP_SPECIAL();
    return VALUES_1(a_list);
}

/* STRICT-INSTANCES-WITHIN-MODULE-P */
Object strict_instances_within_module_p(class_1,module)
    Object class_1, module;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object ab_loopvar_, instance, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(130,122);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
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
    if (temp_2) {
	temp_1 = assq_function(class_1,Connections_in_modules_a_list);
	return memq_function(module,CDR(temp_1));
    }
    else {
	ab_loopvar_ = lookup_kb_specific_property_value(class_1,
		Instances_specific_to_this_class_kbprop);
	instance = Nil;
	ab_loop_it_ = Nil;
      next_loop_12:
	if ( !TRUEP(ab_loopvar_))
	    goto end_loop_12;
	instance = ab_loopvar_;
	ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
	ab_loop_it_ = EQ(get_module_block_is_in(instance),module) ? T : Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_12;
      end_loop_12:
	return VALUES_1(Qnil);
    }
}

/* CONNECTION-CLASS-IS-INSTANTIATED-P */
Object connection_class_is_instantiated_p(connection_class)
    Object connection_class;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, block, ab_loop_it_;
    Object ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp_1, ab_less_than_branch_qm_;
    Object frame_or_class, x2;
    char temp;
    Declare_special(2);

    x_note_fn_call(130,123);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      ab_loop_it_ = Nil;
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
      connection = Nil;
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
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_2;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
		ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	    goto end_1;
	goto next_loop_3;
      end_loop_3:
      end_1:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_4;
	connection = ab_connection_;
	frame_or_class = ISVREF(connection,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_class)) > 
		(SI_Long)2L &&  !EQ(ISVREF(frame_or_class,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_or_class,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol = lookup_global_or_kb_specific_property_value(temp 
		? ISVREF(ISVREF(frame_or_class,(SI_Long)1L),(SI_Long)1L) : 
		frame_or_class,Class_description_gkbprop);
	ab_loop_it_ = gensymed_symbol ? memq_function(connection_class,
		ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
	if (ab_loop_it_)
	    goto end_2;
	goto next_loop_2;
      end_loop_4:
	ab_loop_it_ = Qnil;
      end_2:;
      POP_SPECIAL();
      if (ab_loop_it_) {
	  temp_1 = ab_loop_it_;
	  goto end_3;
      }
      goto next_loop;
    end_loop_1:
      temp_1 = Qnil;
    end_3:;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_linearized_kb_required_modules, Qcurrent_linearized_kb_required_modules);

Object Long_operation_posting_delay_for_kb_modularity_consistency_check = UNBOUND;

static Object array_constant_29;   /* # */

/* COLLECT-BAD-DEFINITIONS-FOR-KB */
Object collect_bad_definitions_for_kb varargs_1(int, n)
{
    Object secretly_qm, temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm, gensymed_symbol_2;
    Object xa, ya;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(130,124);
    INIT_ARGS_nonrelocating();
    SAVE_STACK();
    secretly_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (secretly_qm) {
	result = collect_bad_definitions_for_kb_1();
	RESTORE_STACK();
	return result;
    }
    else {
	temp = make_message(1,tformat_text_string(2,string_constant_54,
		array_constant_29));
	current_long_operation_notification_workspace = make_workspace(6,
		Qtemporary_workspace,Nil,temp,Nil,
		Width_for_prominent_notification_workspaces,
		Height_for_prominent_notification_workspaces);
	PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
		3);
	  frame_serial_number = 
		  copy_frame_serial_number(Current_frame_serial_number);
	  kb_serial_number = Current_kb_serial_number;
	  fixnum_time_at_start_of_current_long_notification = 
		  c_native_clock_ticks_or_cache(Nil,Nil);
	  PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
		  2);
	    if (PUSH_UNWIND_PROTECT(0)) {
		doing_long_operation_with_notification_qm = T;
		long_operation_notification_has_been_put_up_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
			  0);
		    if ( !TRUEP(T)) {
			if (Doing_long_operation_with_notification_qm &&  
				!TRUEP(Long_operation_notification_has_been_put_up_qm)) 
				    {
			    gensymed_symbol = 
				    IFIX(c_native_clock_ticks_or_cache(Nil,
				    Nil));
			    gensymed_symbol_1 = 
				    IFIX(Fixnum_time_at_start_of_current_long_notification);
			    if (gensymed_symbol >= gensymed_symbol_1)
				temp = FIX(gensymed_symbol - 
					gensymed_symbol_1);
			    else {
				gensymed_symbol = gensymed_symbol - 
					gensymed_symbol_1;
				gensymed_symbol = gensymed_symbol + 
					IFIX(Most_positive_fixnum);
				temp = FIX(gensymed_symbol + (SI_Long)1L);
			    }
			    temp_1 = FIXNUM_GE(temp,
				    fixnum_time_interval(FIX((SI_Long)0L)));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    put_up_long_operation_notification_now();
		    }
		    SAVE_VALUES(collect_bad_definitions_for_kb_1());
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
		gensymed_symbol_2 = 
			ISVREF(Current_long_operation_notification_workspace,
			(SI_Long)3L);
		temp_1 = 
			SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
			? 
			EQ(ISVREF(Current_long_operation_notification_workspace,
			(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp_1);
		else
		    temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			    IFIX(gensymed_symbol_2) == (SI_Long)-1L : 
			    TRUEP(Nil);
		if (temp_1);
		else if (FIXNUMP(frame_serial_number))
		    temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			    FIXNUM_LT(frame_serial_number,
			    gensymed_symbol_2) : TRUEP(T);
		else if (FIXNUMP(gensymed_symbol_2))
		    temp_1 = TRUEP(Nil);
		else {
		    xa = M_CAR(frame_serial_number);
		    ya = M_CAR(gensymed_symbol_2);
		    temp_1 = FIXNUM_LT(xa,ya);
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(xa,ya) ? 
				FIXNUM_LT(M_CDR(frame_serial_number),
				M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
		}
		temp_1 =  !temp_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		delete_frame(Current_long_operation_notification_workspace);
	    reclaim_frame_serial_number(frame_serial_number);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

/* COLLECT-BAD-DEFINITIONS-FOR-KB-1 */
Object collect_bad_definitions_for_kb_1()
{
    Object classes_not_defined_in_any_module;
    Object classes_whose_superiors_are_not_defined_in_required_modules;
    Object a_list_of_classes_with_instances_in_modules_that_do_not_require_them;
    Object connections_in_modules_a_list;
    Object a_list_of_relations_with_related_items_in_modules_that_do_not_require_them;
    Object module_required_by_relationships;
    Declare_special(6);
    Object result;

    x_note_fn_call(130,125);
    classes_not_defined_in_any_module = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Classes_not_defined_in_any_module,Qclasses_not_defined_in_any_module,classes_not_defined_in_any_module,
	    5);
      classes_whose_superiors_are_not_defined_in_required_modules = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Classes_whose_superiors_are_not_defined_in_required_modules,Qclasses_whose_superiors_are_not_defined_in_required_modules,classes_whose_superiors_are_not_defined_in_required_modules,
	      4);
	a_list_of_classes_with_instances_in_modules_that_do_not_require_them 
		= Nil;
	PUSH_SPECIAL_WITH_SYMBOL(A_list_of_classes_with_instances_in_modules_that_do_not_require_them,Qa_list_of_classes_with_instances_in_modules_that_do_not_require_them,a_list_of_classes_with_instances_in_modules_that_do_not_require_them,
		3);
	  connections_in_modules_a_list = get_connections_in_modules_a_list();
	  PUSH_SPECIAL_WITH_SYMBOL(Connections_in_modules_a_list,Qconnections_in_modules_a_list,connections_in_modules_a_list,
		  2);
	    a_list_of_relations_with_related_items_in_modules_that_do_not_require_them 
		    = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(A_list_of_relations_with_related_items_in_modules_that_do_not_require_them,Qa_list_of_relations_with_related_items_in_modules_that_do_not_require_them,a_list_of_relations_with_related_items_in_modules_that_do_not_require_them,
		    1);
	      propagate_modules_to_subworkspaces();
	      module_required_by_relationships = 
		      make_module_required_by_relationships();
	      PUSH_SPECIAL_WITH_SYMBOL(Module_required_by_relationships,Qmodule_required_by_relationships,module_required_by_relationships,
		      0);
		collect_bad_definitions();
		collect_potentially_unreloadable_permanent_relationships();
		reclaim_module_required_by_relationships(Module_required_by_relationships);
	      POP_SPECIAL();
	      unpropagate_modules_to_subworkspaces();
	      reclaim_gensym_tree_1(Connections_in_modules_a_list);
	      result = VALUES_4(Classes_not_defined_in_any_module,
		      Classes_whose_superiors_are_not_defined_in_required_modules,
		      A_list_of_classes_with_instances_in_modules_that_do_not_require_them,
		      A_list_of_relations_with_related_items_in_modules_that_do_not_require_them);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qmodule_relationship_key_equal;  /* module-relationship-key-equal */

static Object Qdependent;          /* dependent */

static Object Qnon_dependent;      /* non-dependent */

/* COLLECT-BAD-DEFINITIONS */
Object collect_bad_definitions()
{
    Object scope_conses, ab_loopvar_, class_1, class_definition, temp;
    Object module_for_definition_qm, gensym_modify_macro_using_test_arg_1;
    Object car_1, cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object temp_2, module, direct_superior, direct_superior_class_definition;
    Object module_for_superior_definition_qm, instance_qm, ab_loopvar__1;
    Object instance, workspace_of_instance, result_1, ab_loopvar__2;
    Object ab_loopvar__3, gensymed_symbol_2, module_for_instance_qm, key;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_4;
    Object entry_hash, hashed_relationship, relationship;
    SI_Long gensymed_symbol, gensymed_symbol_1, temp_3, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(130,126);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qblock;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      class_definition = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      class_definition = 
	      lookup_global_or_kb_specific_property_value(class_1,
	      Class_definition_gkbprop);
      if (Doing_long_operation_with_notification_qm &&  
	      !TRUEP(Long_operation_notification_has_been_put_up_qm)) {
	  gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	  gensymed_symbol_1 = 
		  IFIX(Fixnum_time_at_start_of_current_long_notification);
	  if (gensymed_symbol >= gensymed_symbol_1)
	      temp = FIX(gensymed_symbol - gensymed_symbol_1);
	  else {
	      gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	      gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	      temp = FIX(gensymed_symbol + (SI_Long)1L);
	  }
	  temp_1 = FIXNUM_GE(temp,
		  fixnum_time_interval(Long_operation_posting_delay_for_kb_modularity_consistency_check));
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  put_up_long_operation_notification_now();
      if (ATOM(class_definition)) {
	  module_for_definition_qm = 
		  efficient_get_module_block_is_in(class_definition);
	  if ( !TRUEP(module_for_definition_qm)) {
	      gensym_modify_macro_using_test_arg_1 = class_1;
	      car_1 = gensym_modify_macro_using_test_arg_1;
	      cdr_1 = Classes_not_defined_in_any_module;
	      key_result = car_1;
	      x_element = Nil;
	      ab_loop_list_ = cdr_1;
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      x_element = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	      temp_2 = temp_1 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	      Classes_not_defined_in_any_module = temp_2;
	  }
	  else {
	      module = module_for_definition_qm;
	      propagate_module_requires_module_p_to_all_modules(module);
	      direct_superior = Nil;
	      ab_loop_list_ = 
		      lookup_global_or_kb_specific_property_value(class_1,
		      Direct_superior_classes_gkbprop);
	      direct_superior_class_definition = Nil;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      direct_superior = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      direct_superior_class_definition = 
		      lookup_global_or_kb_specific_property_value(direct_superior,
		      Class_definition_gkbprop);
	      if (ATOM(direct_superior_class_definition)) {
		  module_for_superior_definition_qm = 
			  efficient_get_module_block_is_in(direct_superior_class_definition);
		  if (module_for_superior_definition_qm) {
		      temp_1 = EQ(module,module_for_superior_definition_qm);
		      if (temp_1);
		      else {
			  instance_qm = 
				  lookup_kb_specific_property_value(module_for_superior_definition_qm,
				  Module_information_instance_for_module_qm_kbprop);
			  temp_1 = instance_qm ? TRUEP(ISVREF(instance_qm,
				  (SI_Long)25L)) : TRUEP(Qnil);
		      }
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if ( !temp_1) {
		      gensym_modify_macro_using_test_arg_1 = class_1;
		      car_1 = gensym_modify_macro_using_test_arg_1;
		      cdr_1 = 
			      Classes_whose_superiors_are_not_defined_in_required_modules;
		      key_result = car_1;
		      x_element = Nil;
		      ab_loop_list_ = cdr_1;
		      ab_loop_it_ = Nil;
		    next_loop_3:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_3;
		      x_element = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
		      if (ab_loop_it_) {
			  temp_1 = TRUEP(ab_loop_it_);
			  goto end_2;
		      }
		      goto next_loop_3;
		    end_loop_3:
		      temp_1 = TRUEP(Qnil);
		    end_2:;
		      temp_2 = temp_1 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
		      Classes_whose_superiors_are_not_defined_in_required_modules 
			      = temp_2;
		      goto end_loop_2;
		  }
	      }
	      goto next_loop_2;
	    end_loop_2:;
	      ab_loopvar__1 = lookup_kb_specific_property_value(class_1,
		      Instances_specific_to_this_class_kbprop);
	      instance = Nil;
	      workspace_of_instance = Nil;
	      result_1 = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__3 = Nil;
	    next_loop_4:
	      if ( !TRUEP(ab_loopvar__1))
		  goto end_loop_4;
	      instance = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      workspace_of_instance = get_workspace_of_thing_if_any(instance);
	      gensymed_symbol_2 = ISVREF(instance,(SI_Long)3L);
	      if ( !(FIXNUMP(gensymed_symbol_2) ? IFIX(gensymed_symbol_2) 
		      == (SI_Long)-1L : TRUEP(Nil))) {
		  if (workspace_of_instance) {
		      gensymed_symbol_2 = ISVREF(workspace_of_instance,
			      (SI_Long)3L);
		      temp_1 = FIXNUMP(gensymed_symbol_2) ? 
			      IFIX(gensymed_symbol_2) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  temp_1 =  !temp_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  if ((SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)4L)) & 
			  (SI_Long)1L) &&  !((SI_Long)0L != 
			  (IFIX(ISVREF(instance,(SI_Long)5L)) & 
			  (SI_Long)524288L))) {
		      module_for_instance_qm = 
			      efficient_get_module_block_is_in(instance);
		      temp_1 = EQ(module_for_definition_qm,
			      module_for_instance_qm);
		      if (temp_1);
		      else {
			  key = gensym_cons_1(module_for_definition_qm,
				  module_for_instance_qm);
			  gensymed_symbol = IFIX(sxhashw(key));
			  temp = Module_required_by_relationships;
			  temp_3 = gensymed_symbol % (SI_Long)43L;
			  temp = SVREF(temp,FIX(temp_3));
			  skip_list = CDR(temp);
			  key_value = key;
			  key_hash_value = gensymed_symbol;
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_5:
			  if (level < ab_loop_bind_)
			      goto end_loop_5;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_6:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_4 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_4,temp);
			  MVS_2(result,succ,marked);
			next_loop_7:
			  if ( !TRUEP(marked))
			      goto end_loop_6;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_4 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_4,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_7;
			end_loop_6:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !TRUEP(module_relationship_key_equal(key_value,
				  ISVREF(curr,(SI_Long)2L)))) {
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
			  hashed_relationship = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (module_relationship_key_equal(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
			  relationship = hashed_relationship;
			  if (relationship);
			  else {
			      gensymed_symbol = IFIX(sxhashw(key));
			      temp = Module_required_by_relationships;
			      temp_3 = gensymed_symbol % (SI_Long)43L;
			      temp_4 = SVREF(temp,FIX(temp_3));
			      temp = 
				      Fp_mutate_module_required_by_relationships_tree_for_hash_skip_list_entry;
			      relationship = set_skip_list_entry(temp_4,
				      FIX((SI_Long)31L),
				      Qmodule_relationship_key_equal,temp,
				      T,key,FIX(gensymed_symbol),
				      module_requires_module_p(module_for_instance_qm,
				      module_for_definition_qm) ? 
				      Qdependent : Qnon_dependent);
			  }
			  if (hashed_relationship)
			      reclaim_gensym_cons_1(key);
			  temp_1 = EQ(relationship,Qdependent);
		      }
		      temp_1 =  !temp_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  ab_loopvar__3 = gensym_cons_1(instance,Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__3;
		  else
		      result_1 = ab_loopvar__3;
		  ab_loopvar__2 = ab_loopvar__3;
	      }
	      goto next_loop_4;
	    end_loop_4:
	      if (result_1)
		  A_list_of_classes_with_instances_in_modules_that_do_not_require_them 
			  = gensym_cons_1(gensym_cons_1(class_1,result_1),
			  A_list_of_classes_with_instances_in_modules_that_do_not_require_them);
	  }
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qrelation_is_permanent;  /* relation-is-permanent */

/* COLLECT-POTENTIALLY-UNRELOADABLE-PERMANENT-RELATIONSHIPS */
Object collect_potentially_unreloadable_permanent_relationships()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, subject_block;
    Object relation_instances, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_binary_tree_form_, gensymed_symbol, temp_1;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, relation_instance, relation_name, relation_frame;
    Object object_block_list, ab_less_than_branch_qm_, module_for_relation_qm;
    Object ab_node_stack__1, ab_current_node__1, ab_skip_list_p__1;
    Object ab_next_node__1, ab_tail_node__1, ab_current_alist__1;
    Object ab_entry_cons__1, object_block;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(130,127);
    propagate_kb_requires_module_p_to_all_modules();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    subject_block = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,2);
      relation_instances = Nil;
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
      subject_block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      relation_instances = ISVREF(subject_block,(SI_Long)12L);
      if (relation_instances) {
	  scope_conses = Scope_conses;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_skip_list_form_ = relation_instances;
	  ab_binary_tree_form_ = relation_instances;
	  gensymed_symbol = CDR(relation_instances);
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
	  ab_next_node_ = Nil;
	  ab_tail_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  relation_instance = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
	    relation_name = Nil;
	    relation_frame = Nil;
	    object_block_list = Nil;
	    if (ab_skip_list_p_) {
		ab_next_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L));
		ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
	    }
	    else
		ab_next_node_ = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
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
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
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
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
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
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_3;
	    relation_instance = M_CDR(ab_entry_cons_);
	    relation_name = ISVREF(relation_instance,(SI_Long)0L);
	    relation_frame = ISVREF(relation_instance,(SI_Long)1L);
	    object_block_list = ISVREF(relation_instance,(SI_Long)2L);
	    if (get_lookup_slot_value(relation_frame,
		    Qrelation_is_permanent) && (SI_Long)0L != 
		    (IFIX(ISVREF(relation_frame,(SI_Long)4L)) & 
		    (SI_Long)1L) && ISVREF(relation_frame,(SI_Long)22L)) {
		module_for_relation_qm = 
			efficient_get_module_block_is_in(relation_frame);
		note_item_used_by_relation(subject_block,relation_frame,
			module_for_relation_qm);
		scope_conses = Scope_conses;
		ab_node_stack__1 = Nil;
		ab_current_node__1 = Nil;
		ab_skip_list_form_ = object_block_list;
		ab_binary_tree_form_ = object_block_list;
		gensymed_symbol = CDR(object_block_list);
		if (CONSP(gensymed_symbol)) {
		    temp_1 = M_CAR(gensymed_symbol);
		    temp = SIMPLE_VECTOR_P(temp_1);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp_1 = M_CDR(gensymed_symbol);
		    ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		}
		else
		    ab_skip_list_p__1 = Nil;
		ab_next_node__1 = Nil;
		ab_tail_node__1 = Nil;
		ab_current_alist__1 = Nil;
		ab_entry_cons__1 = Nil;
		object_block = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  if (ab_skip_list_p__1) {
		      ab_next_node__1 = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			      (SI_Long)0L),(SI_Long)0L));
		      ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		      if (EQ(ab_next_node__1,ab_tail_node__1))
			  ab_next_node__1 = Nil;
		  }
		  else
		      ab_next_node__1 = M_CDR(ab_binary_tree_form_);
		next_loop_4:
		  if (ab_current_alist__1) {
		      ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		      ab_current_alist__1 = M_CDR(ab_current_alist__1);
		  }
		  else if (ab_skip_list_p__1) {
		      if (ab_next_node__1) {
			  ab_current_node__1 = ab_next_node__1;
			  ab_next_node__1 = 
				  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node__1,
				  (SI_Long)0L),(SI_Long)0L));
			  if (EQ(ab_next_node__1,ab_tail_node__1))
			      ab_next_node__1 = Nil;
			  ab_entry_cons__1 = 
				  scope_cons(ISVREF(ab_current_node__1,
				  (SI_Long)2L),ISVREF(ab_current_node__1,
				  (SI_Long)3L));
		      }
		      else
			  ab_current_node__1 = Nil;
		  }
		  else {
		      if (ab_next_node__1) {
			  ab_current_node__1 = ab_next_node__1;
			  ab_less_than_branch_qm_ = Nil;
			next_loop_5:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node__1,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_4;
			  ab_node_stack__1 = scope_cons(ab_current_node__1,
				  ab_node_stack__1);
			  ab_current_node__1 = ab_less_than_branch_qm_;
			  goto next_loop_5;
			end_loop_4:;
		      }
		      else if (ab_node_stack__1) {
			  ab_next_node__1 = ab_node_stack__1;
			  ab_current_node__1 = M_CAR(ab_node_stack__1);
			  ab_node_stack__1 = M_CDR(ab_node_stack__1);
		      }
		      else
			  ab_current_node__1 = Nil;
		      if (ab_current_node__1) {
			  ab_next_node__1 = ISVREF(ab_current_node__1,
				  (SI_Long)2L);
			  ab_current_alist__1 = ISVREF(ab_current_node__1,
				  (SI_Long)3L);
			  ab_entry_cons__1 = M_CAR(ab_current_alist__1);
			  ab_current_alist__1 = M_CDR(ab_current_alist__1);
		      }
		  }
		  if ( !TRUEP(ab_current_node__1))
		      goto end_loop_5;
		  object_block = M_CDR(ab_entry_cons__1);
		  if (object_block)
		      note_item_used_by_relation(object_block,
			      relation_frame,module_for_relation_qm);
		  goto next_loop_4;
		end_loop_5:;
		POP_SPECIAL();
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* NOTE-ITEM-USED-BY-RELATION */
Object note_item_used_by_relation(block,relation,module_for_relation_qm)
    Object block, relation, module_for_relation_qm;
{
    Object module_for_instance_qm, key, temp_1, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_3, entry_hash;
    Object hashed_relationship, relationship, a1, a2;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, cdr_new_value;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(130,128);
    if ( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L) 
	    &&  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)524288L))))
	return VALUES_1(Nil);
    module_for_instance_qm = efficient_get_module_block_is_in(block);
    temp = EQ(module_for_relation_qm,module_for_instance_qm);
    if (temp);
    else {
	key = gensym_cons_1(module_for_relation_qm,module_for_instance_qm);
	gensymed_symbol = IFIX(sxhashw(key));
	temp_1 = Module_required_by_relationships;
	temp_2 = gensymed_symbol % (SI_Long)43L;
	temp_1 = SVREF(temp_1,FIX(temp_2));
	skip_list = CDR(temp_1);
	key_value = key;
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
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_3 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_3,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  
		!TRUEP(module_relationship_key_equal(key_value,ISVREF(curr,
		(SI_Long)2L)))) {
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
	hashed_relationship = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (module_relationship_key_equal(key_value,
		ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
		Nil) : Nil;
	relationship = hashed_relationship;
	if (relationship);
	else {
	    gensymed_symbol = IFIX(sxhashw(key));
	    temp_1 = Module_required_by_relationships;
	    temp_2 = gensymed_symbol % (SI_Long)43L;
	    temp_3 = SVREF(temp_1,FIX(temp_2));
	    temp_1 = 
		    Fp_mutate_module_required_by_relationships_tree_for_hash_skip_list_entry;
	    relationship = set_skip_list_entry(temp_3,FIX((SI_Long)31L),
		    Qmodule_relationship_key_equal,temp_1,T,key,
		    FIX(gensymed_symbol),
		    module_requires_module_p(module_for_instance_qm,
		    module_for_relation_qm) ? Qdependent : Qnon_dependent);
	}
	if (hashed_relationship)
	    reclaim_gensym_cons_1(key);
	temp = EQ(relationship,Qdependent);
    }
    if ( !temp) {
	a1 = assq_function(relation,
		A_list_of_relations_with_related_items_in_modules_that_do_not_require_them);
	if ( !TRUEP(a1)) {
	    a1 = gensym_cons_1(relation,Nil);
	    A_list_of_relations_with_related_items_in_modules_that_do_not_require_them 
		    = gensym_cons_1(a1,
		    A_list_of_relations_with_related_items_in_modules_that_do_not_require_them);
	}
	a2 = assq_function(module_for_instance_qm,CDR(a1));
	if ( !TRUEP(a2)) {
	    a2 = gensym_cons_1(module_for_instance_qm,Nil);
	    gensym_push_modify_macro_arg = a2;
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = CDR(a1);
	    cdr_new_value = gensym_cons_1(car_1,cdr_1);
	    M_CDR(a1) = cdr_new_value;
	}
	if ( !TRUEP(memq_function(block,CDR(a2)))) {
	    gensym_push_modify_macro_arg = block;
	    car_1 = gensym_push_modify_macro_arg;
	    cdr_1 = CDR(a2);
	    cdr_new_value = gensym_cons_1(car_1,cdr_1);
	    M_CDR(a2) = cdr_new_value;
	}
	temp_1 = T;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

void kb_merge_INIT()
{
    Object temp, temp_1, gensymed_symbol;
    Object AB_package, list_constant_14, Qmodules_required_by_kb_do_not_exist;
    Object Qworkspaces_belong_to_unrequired_modules;
    Object Qworkspaces_belong_to_unspecified_module;
    Object Qmodules_that_exist_are_not_required;
    Object Qcircularity_in_module_hierarchy;
    Object Qparticulars_printer_for_kb_modularity_problem;
    Object Qprint_relations_with_related_items_in_modules_that_do_not_require_them;
    Object Qes_l_c, Qfunction_keeps_procedure_environment_valid_qm;
    Object Qmake_pathname_with_default_type_for_modules;
    Object Qreclaim_if_gensym_pathname, list_constant_23, Qkb_merge, Kfuncall;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_22, Qpathnames;
    Object Qinitializer_for_pathname_for_disabling_g2_module_map_command_line;
    Object Kabsolute, list_constant_21;
    Object Qinitialize_default_g2_module_map_pathname, array_constant_32;
    Object array_constant_31, array_constant_30, Qformat_description;
    Object string_constant_97, Qkb_load1, string_constant_96, list_constant_20;
    Object string_constant_95, string_constant_94, string_constant_74;
    Object string_constant_93, string_constant_92, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object Qslot_value_writer, Qwrite_progress_through_file_from_slot;
    Object list_constant_19, Qfinished, Qautomerge2, Qautomerge, Qreformat;
    Object Qrevert, Qpost_load2, Qpost_load, Qreinitialize;
    Object Qwrite_unquoted_file_name_qm_from_slot, Qunquoted_file_name_qm;
    Object Qwrite_status_of_file_progress_from_slot, Qstatus_of_file_progress;
    Object Qwrite_direction_of_file_progress_from_slot;
    Object Qdirection_of_file_progress, Qmodule, Qfile_name, Qstatus;
    Object Qdirection, string_constant_81, string_constant_80;
    Object list_constant_18, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75, Qentity;
    Object Qreclaim_slot_value, list_constant_17, Qall_definitional_classes;
    Object Qtext_conversion_style, Qtokenizer, Qframe_style_definition;
    Object Qimage_definition, Qlanguage_translation, Quser_menu_choice;
    Object Qgeneric_formula, Qgeneric_simulation_formula, Qrule;
    Object Qremote_procedure_declaration, Qforeign_function_declaration;
    Object Qexternal_simulation_definition, Qunits_of_measure_declaration;
    Object Qrelation, Qtabular_function, Qtabular_function_of_1_arg;
    Object Qfunction_definition, Qprocedure, list_constant_16;
    Object list_constant_15, Qitem_or_datum, Qab_or, Qno_item, Qframe_flags_2;
    Object Qinclude_in_menus_qm, Qinstantiate_qm, Qinstance_configuration;
    Object Qobject_configuration, Qsubworkspaces;
    Object Qkb_state_changes_previous_cons_qm;
    Object Qruntime_structures_affected_by_this_entity;
    Object Qchange_log_information, Qsquirreled_data, Qlayer_position_of_block;
    Object Qoverlapping_blocks_cache, Qunsaved_but_remembered_block_transforms;
    Object Qremembered_block_transform, Qframe_transforms_of_block;
    Object Qframe_representations, Qlookup_structure, Qoriginal_kb_state_plist;
    Object Qmenus_for_this, Qclass_description_slot, Qicon_attributes_plist;
    Object Qicon_description, Qclass_specific_instances_reverse_pointer;
    Object Qclass_specific_instances_forward_pointer, Qframe_serial_number;
    Object Qreclaim_class_name_conflicts, string_constant_73;
    Object string_constant_72, Qreclaim_frame_serial_number, Qdefault_junction;

    x_note_fn_call(130,129);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qcombine_class_defintions = STATIC_SYMBOL("COMBINE-CLASS-DEFINTIONS",
	    AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qjunction_block_class_for_class = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CLASS",AB_package);
    Qmerge_definitions = STATIC_SYMBOL("MERGE-DEFINITIONS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdo_not_save = STATIC_SYMBOL("DO-NOT-SAVE",AB_package);
    Qsave = STATIC_SYMBOL("SAVE",AB_package);
    Qnote_slot_changes = STATIC_SYMBOL("NOTE-SLOT-CHANGES",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    list_constant = STATIC_CONS(Qdefault_junction,Qnil);
    Qjunction_block_class_for_connection = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-FOR-CONNECTION",AB_package);
    Qcross_section_pattern_for_class = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CLASS",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    Qdirect_superiors_of_defined_class = 
	    STATIC_SYMBOL("DIRECT-SUPERIORS-OF-DEFINED-CLASS",AB_package);
    string_constant = STATIC_STRING("-FROM-");
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qpreprocess_class_name_conflicts_with_move_attribute_facility = 
	    STATIC_SYMBOL("PREPROCESS-CLASS-NAME-CONFLICTS-WITH-MOVE-ATTRIBUTE-FACILITY",
	    AB_package);
    Qclass_specific_attributes = STATIC_SYMBOL("CLASS-SPECIFIC-ATTRIBUTES",
	    AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    Qmove_attribute = STATIC_SYMBOL("MOVE-ATTRIBUTE",AB_package);
    Qcadr_eq = STATIC_SYMBOL("CADR-EQ",AB_package);
    SET_SYMBOL_FUNCTION(Qcadr_eq,STATIC_FUNCTION(cadr_eq,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qpreprocess_class_name_conflicts_with_move_attribute_facility,
	    STATIC_FUNCTION(preprocess_class_name_conflicts_with_move_attribute_facility,
	    NIL,FALSE,0,0));
    Qdeal_with_class_name_conflicts = 
	    STATIC_SYMBOL("DEAL-WITH-CLASS-NAME-CONFLICTS",AB_package);
    Qname_of_defined_class = STATIC_SYMBOL("NAME-OF-DEFINED-CLASS",AB_package);
    string_constant_1 = string_appendn(3,
	    STATIC_STRING("The merged-in KB ~S contains ~D class definition(s) with subworkspaces ~\n                 that have been verified to be the same as established (existing) ~\n                 d"),
	    STATIC_STRING("efinitions with subworkspaces, except that the corresponding ~\n                 subworkspaces have not been verified to be equivalent.  These ~\n                 new definition"),
	    STATIC_STRING("s, with their subworkspaces, have been deleted."));
    SET_SYMBOL_FUNCTION(Qdeal_with_class_name_conflicts,
	    STATIC_FUNCTION(deal_with_class_name_conflicts,NIL,FALSE,2,2));
    Qcurrent_backup_definition_workspace_qm = 
	    STATIC_SYMBOL("CURRENT-BACKUP-DEFINITION-WORKSPACE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_backup_definition_workspace_qm,
	    Current_backup_definition_workspace_qm);
    Qkb_merge = STATIC_SYMBOL("KB-MERGE",AB_package);
    record_system_variable(Qcurrent_backup_definition_workspace_qm,
	    Qkb_merge,Nil,Qnil,Qnil,Qnil,Qt);
    Qcurrent_backup_definition_workspace_serial_number_qm = 
	    STATIC_SYMBOL("CURRENT-BACKUP-DEFINITION-WORKSPACE-SERIAL-NUMBER\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_backup_definition_workspace_serial_number_qm,
	    Current_backup_definition_workspace_serial_number_qm);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    record_system_variable(Qcurrent_backup_definition_workspace_serial_number_qm,
	    Qkb_merge,Nil,Qnil,Qnil,Qreclaim_frame_serial_number,Qt);
    string_constant_2 = string_appendn(3,
	    STATIC_STRING("The class definitions on this workspace have been restored ~\n                because they are no longer provided by the required modules.  ~\n                After you have exa"),
	    STATIC_STRING("mined the class definitions ~\n                and any subclasses and instances, you can move the definitions ~\n                to other workspaces or delete them, and then del"),
	    STATIC_STRING("ete ~\n                this workspace."));
    string_constant_3 = STATIC_STRING("BACKUP-DEFINITIONS-FROM-~a");
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qfix_definitions_saved_as_ghost_definitions = 
	    STATIC_SYMBOL("FIX-DEFINITIONS-SAVED-AS-GHOST-DEFINITIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_definitions_saved_as_ghost_definitions,
	    STATIC_FUNCTION(fix_definitions_saved_as_ghost_definitions,NIL,
	    FALSE,3,3));
    string_constant_4 = 
	    STATIC_STRING("The KB ~S contains a class definition that differs from an established ~\n\t (existing) definition.  A conflict report workspace has been created for this.");
    string_constant_5 = 
	    STATIC_STRING("The KB ~S contains ~D class definitions that differ from established ~\n\t (existing) definitions.  For each of these, a conflict report workspace has ~\n\t been created.");
    string_constant_6 = 
	    string_append2(STATIC_STRING("CONFLICT REPORT!  The merged-in KB ~S contained a definition for ~A ~\n                    that differed from an established (existing) definition.  The class ~\n               "),
	    STATIC_STRING("     from the merged-in KB has been renamed ~A.  (If you keep this new ~\n                    name, you should update rules, formulas, etc., appropriately.)"));
    string_constant_7 = string_appendn(3,
	    STATIC_STRING("CONFLICT REPORT!  When the KB ~S was saved out, it contained a ~\n                    definition for ~A, which has since become a built-in class or type.  Because ~\n           "),
	    STATIC_STRING("         of this, the class from the KB has been renamed ~A.  You should ~\n                    update rules, formulas, etc., appropriately.  (You may delete ~\n                "),
	    STATIC_STRING("    this workspace when you are done looking at it.)"));
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    Qconflict_report_format = STATIC_SYMBOL("CONFLICT-REPORT-FORMAT",
	    AB_package);
    string_constant_8 = string_appendn(4,
	    STATIC_STRING("You may wish to edit one or both of the tables below.  Differences in ~\n                    the tables have been highlighted.  If the tables become identical ~\n               "),
	    STATIC_STRING("     except for the class names, you may merge one of them into the other ~\n                    by editing the CHANGE slot.  Type or select \"merge all instances and ~\n        "),
	    STATIC_STRING("            subclasses into definition for <other class>.\"  Be sure to read the ~\n                    logbook notes when you do this.  You should delete this workspace when ~\n"),
	    STATIC_STRING("                    you are done with it."));
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    string_constant_9 = STATIC_STRING("~a-CLASS-NAME-CONFLICT");
    string_constant_10 = STATIC_STRING(" and ~D subclass~A");
    string_constant_11 = STATIC_STRING("");
    string_constant_12 = STATIC_STRING("es");
    string_constant_13 = 
	    STATIC_STRING("Definition for ~A.  ~D instance~A~A~A.");
    string_constant_14 = STATIC_STRING("s");
    string_constant_15 = STATIC_STRING(" and a subworkspace");
    string_constant_72 = 
	    STATIC_STRING("13fy83-My83iy35Ay83*ay38Iy83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yk83-By083-Ny83fy83*ky83fy83byq83ayn83");
    string_constant_73 = STATIC_STRING("Wyq83cym83*=yk83*1yk83*0yk83**yk");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qconflict_report_format,
	    regenerate_optimized_constant(LIST_2(string_constant_72,
	    string_constant_73)),Qformat_description);
    Qrecord_of_class_name_conflicts_qm = 
	    STATIC_SYMBOL("RECORD-OF-CLASS-NAME-CONFLICTS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecord_of_class_name_conflicts_qm,
	    Record_of_class_name_conflicts_qm);
    Qreclaim_class_name_conflicts = 
	    STATIC_SYMBOL("RECLAIM-CLASS-NAME-CONFLICTS",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_class_name_conflicts,
	    STATIC_FUNCTION(reclaim_class_name_conflicts,NIL,FALSE,1,1));
    record_system_variable(Qrecord_of_class_name_conflicts_qm,Qkb_merge,
	    Nil,Qnil,Qnil,Qreclaim_class_name_conflicts,Qt);
    if (Currently_automatically_resolving_class_name_conflicts_qm == UNBOUND)
	Currently_automatically_resolving_class_name_conflicts_qm = Nil;
    Qattribute_displays_spec_qm = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-SPEC\?",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qclass_specific_instances_forward_pointer = 
	    STATIC_SYMBOL("CLASS-SPECIFIC-INSTANCES-FORWARD-POINTER",
	    AB_package);
    Qclass_specific_instances_reverse_pointer = 
	    STATIC_SYMBOL("CLASS-SPECIFIC-INSTANCES-REVERSE-POINTER",
	    AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    Qicon_attributes_plist = STATIC_SYMBOL("ICON-ATTRIBUTES-PLIST",AB_package);
    Qclass_description_slot = STATIC_SYMBOL("CLASS-DESCRIPTION-SLOT",
	    AB_package);
    Qmenus_for_this = STATIC_SYMBOL("MENUS-FOR-THIS",AB_package);
    Qoriginal_kb_state_plist = STATIC_SYMBOL("ORIGINAL-KB-STATE-PLIST",
	    AB_package);
    Qlookup_structure = STATIC_SYMBOL("LOOKUP-STRUCTURE",AB_package);
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    Qremembered_block_transform = 
	    STATIC_SYMBOL("REMEMBERED-BLOCK-TRANSFORM",AB_package);
    Qunsaved_but_remembered_block_transforms = 
	    STATIC_SYMBOL("UNSAVED-BUT-REMEMBERED-BLOCK-TRANSFORMS",
	    AB_package);
    Qoverlapping_blocks_cache = STATIC_SYMBOL("OVERLAPPING-BLOCKS-CACHE",
	    AB_package);
    Qlayer_position_of_block = STATIC_SYMBOL("LAYER-POSITION-OF-BLOCK",
	    AB_package);
    Qsquirreled_data = STATIC_SYMBOL("SQUIRRELED-DATA",AB_package);
    Qchange_log_information = STATIC_SYMBOL("CHANGE-LOG-INFORMATION",
	    AB_package);
    Qruntime_structures_affected_by_this_entity = 
	    STATIC_SYMBOL("RUNTIME-STRUCTURES-AFFECTED-BY-THIS-ENTITY",
	    AB_package);
    Qkb_state_changes_previous_cons_qm = 
	    STATIC_SYMBOL("KB-STATE-CHANGES-PREVIOUS-CONS\?",AB_package);
    Qsubworkspaces = STATIC_SYMBOL("SUBWORKSPACES",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)20L,Qframe_serial_number,
	    Qclass_specific_instances_forward_pointer,
	    Qclass_specific_instances_reverse_pointer,Qicon_description,
	    Qicon_attributes_plist,Qclass_description_slot,Qmenus_for_this,
	    Qoriginal_kb_state_plist,Qlookup_structure,
	    Qframe_representations,Qframe_transforms_of_block,
	    Qremembered_block_transform,
	    Qunsaved_but_remembered_block_transforms,
	    Qoverlapping_blocks_cache,Qlayer_position_of_block,
	    Qsquirreled_data,Qchange_log_information,
	    Qruntime_structures_affected_by_this_entity,
	    Qkb_state_changes_previous_cons_qm,Qsubworkspaces);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qinstance_configuration = STATIC_SYMBOL("INSTANCE-CONFIGURATION",
	    AB_package);
    Qinstantiate_qm = STATIC_SYMBOL("INSTANTIATE\?",AB_package);
    Qinclude_in_menus_qm = STATIC_SYMBOL("INCLUDE-IN-MENUS\?",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qframe_flags_2 = STATIC_SYMBOL("FRAME-FLAGS-2",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)8L,Qobject_configuration,
	    Qdirect_superiors_of_defined_class,Qclass_specific_attributes,
	    Qinstance_configuration,Qinstantiate_qm,Qinclude_in_menus_qm,
	    Qframe_flags,Qframe_flags_2);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qdefault_overrides = STATIC_SYMBOL("DEFAULT-OVERRIDES",AB_package);
    Qattribute_displays_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAYS-FOR-CLASS",AB_package);
    Qstubs_for_class = STATIC_SYMBOL("STUBS-FOR-CLASS",AB_package);
    Qconnections_for_class_qm = STATIC_SYMBOL("CONNECTIONS-FOR-CLASS\?",
	    AB_package);
    Qstub_length_for_class = STATIC_SYMBOL("STUB-LENGTH-FOR-CLASS",AB_package);
    Qcross_section_pattern_for_connection = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-FOR-CONNECTION",AB_package);
    Qstub_length_for_connection = 
	    STATIC_SYMBOL("STUB-LENGTH-FOR-CONNECTION",AB_package);
    Qdefault_message_properties_for_class = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES-FOR-CLASS",AB_package);
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    string_constant_16 = 
	    string_append2(STATIC_STRING("Automatically deleting the backup-definitions workspace ~NF; all ~\n         of its definitions were automatically deleted after conflicts ~\n         with existing definitions "),
	    STATIC_STRING("were successfully resolved."));
    Qsuperiors_first_partial_ordering_of_slot_denotations_to_automerge = 
	    STATIC_SYMBOL("SUPERIORS-FIRST-PARTIAL-ORDERING-OF-SLOT-DENOTATIONS-TO-AUTOMERGE",
	    AB_package);
    string_constant_17 = 
	    STATIC_STRING("Unable to merge the ~NN attribute between definitions ~NF and ~NF.");
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_15 = STATIC_CONS(Qno_item,Qnil);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_15);
    list_constant_16 = STATIC_LIST((SI_Long)2L,
	    Qdirect_superiors_of_defined_class,Qclass_specific_attributes);
    Partial_ordering_of_slot_denotations_with_superiors_first = 
	    list_constant_16;
    SET_SYMBOL_FUNCTION(Qsuperiors_first_partial_ordering_of_slot_denotations_to_automerge,
	    STATIC_FUNCTION(superiors_first_partial_ordering_of_slot_denotations_to_automerge,
	    NIL,FALSE,2,2));
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    list_constant_4 = STATIC_CONS(Qab_class,Qnil);
    string_constant_18 = 
	    string_append2(STATIC_STRING("Warning: the attempt failed to automatically resolve ~\n                   the old and new definitions, ~NF and ~NF because they ~\n                   are not of compatible clas"),
	    STATIC_STRING("ses.  Neither definition will be deleted."));
    string_constant_19 = 
	    string_append2(STATIC_STRING("Warning: the attempt failed to automatically resolve ~\n                        the old and new definitions, ~NF and ~NF; they ~\n                        still differ in ~d slot"),
	    STATIC_STRING("s!  So neither definition will be deleted."));
    string_constant_20 = 
	    STATIC_STRING("Automatically deleting definition ~NF, whose instances, ~\n                                   if any, were merged into the class defined by ~NF.");
    string_constant_21 = 
	    STATIC_STRING("Automatically deleting conflict workspace ~NF.");
    string_constant_22 = 
	    STATIC_STRING("Warning: Final attempt to merge ~NF with ~NF failed!");
    string_constant_23 = 
	    STATIC_STRING("Automatically deleting the incomplete class-definition ~NF in favor of ~\n          the class-definition ~NF from a required module.");
    string_constant_24 = 
	    STATIC_STRING("merge all instances and subclasses into definition for ~a");
    Qchange = STATIC_SYMBOL("CHANGE",AB_package);
    Qall_definitional_classes = STATIC_SYMBOL("ALL-DEFINITIONAL-CLASSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_definitional_classes,
	    All_definitional_classes);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    Qtabular_function_of_1_arg = STATIC_SYMBOL("TABULAR-FUNCTION-OF-1-ARG",
	    AB_package);
    Qtabular_function = STATIC_SYMBOL("TABULAR-FUNCTION",AB_package);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qunits_of_measure_declaration = 
	    STATIC_SYMBOL("UNITS-OF-MEASURE-DECLARATION",AB_package);
    Qexternal_simulation_definition = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION",AB_package);
    Qforeign_function_declaration = 
	    STATIC_SYMBOL("FOREIGN-FUNCTION-DECLARATION",AB_package);
    Qremote_procedure_declaration = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-DECLARATION",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    Qlanguage_translation = STATIC_SYMBOL("LANGUAGE-TRANSLATION",AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qframe_style_definition = STATIC_SYMBOL("FRAME-STYLE-DEFINITION",
	    AB_package);
    Qtokenizer = STATIC_SYMBOL("TOKENIZER",AB_package);
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)18L,Qprocedure,
	    Qfunction_definition,Qtabular_function_of_1_arg,
	    Qtabular_function,Qrelation,Qunits_of_measure_declaration,
	    Qexternal_simulation_definition,Qforeign_function_declaration,
	    Qremote_procedure_declaration,Qrule,
	    Qgeneric_simulation_formula,Qgeneric_formula,Quser_menu_choice,
	    Qlanguage_translation,Qimage_definition,
	    Qframe_style_definition,Qtokenizer,Qtext_conversion_style);
    SET_SYMBOL_VALUE(Qall_definitional_classes,list_constant_17);
    Qrecord_of_definitional_name_conflicts_qm = 
	    STATIC_SYMBOL("RECORD-OF-DEFINITIONAL-NAME-CONFLICTS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecord_of_definitional_name_conflicts_qm,
	    Record_of_definitional_name_conflicts_qm);
    Qreclaim_slot_value = STATIC_SYMBOL("RECLAIM-SLOT-VALUE",AB_package);
    record_system_variable(Qrecord_of_definitional_name_conflicts_qm,
	    Qkb_merge,Nil,Qnil,Qnil,Qreclaim_slot_value,Qt);
    if (Record_definitional_name_conflicts_qm == UNBOUND)
	Record_definitional_name_conflicts_qm = T;
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    list_constant_5 = STATIC_CONS(Qnil,Qnil);
    Qrelation_instance_tree = STATIC_SYMBOL("RELATION-INSTANCE-TREE",
	    AB_package);
    string_constant_25 = 
	    string_append2(STATIC_STRING("Automatically deleting method ~A for ~\n                         class ~A because a previously-loaded method ~\n                         has the same name, is for the same class"),
	    STATIC_STRING(", and takes the same ~\n                         number of arguments (~d)."));
    string_constant_26 = 
	    STATIC_STRING("Automatically deleting ~(~a~) ~a because a ~\n                         previously-loaded ~(~a~) has the same name.");
    string_constant_27 = 
	    string_append2(STATIC_STRING("WARNING: ~a ~a from the Basis KB no longer ~\n                          exists.  You probably have to start over, and ~\n                          resolve and merge and resolve "),
	    STATIC_STRING("conflicts by hand."));
    Qfile_progress = STATIC_SYMBOL("FILE-PROGRESS",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_18 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qfile_progress,list_constant_18);
    string_constant_74 = STATIC_STRING("0");
    string_constant_75 = 
	    STATIC_STRING("1u4z8r83Vvy83Vvy838Ly838Ly00001p1m8p8313y1l8l1l8o1l83Fy1l83Hy000004z8r83WHy83WHy838Ly838Ly00001q1m8p83dTy1l8l1l8o1l83Fy1l83Hy1l8");
    string_constant_76 = 
	    STATIC_STRING("3-3y000004z8r83YLy83YLy838Ly838Ly0k001p1m8p83YLy1l8l1l8o1l83Fy1l83Hy000004z8r83Tqy83Tqy838Ly838Ly00001p1m8p01l8l1l8o1l83Fy1l83Hy");
    string_constant_77 = 
	    STATIC_STRING("000004z8r83LXy83LXy838Ly838Ly0k001p1l8l1l8o1l83Fy1l83Hy1l83-3y000004z8r83Jty83Jty838Ly838Ly00001n1m8p83Jsy1l8l1l8o000004z8r83avy");
    string_constant_78 = 
	    STATIC_STRING("83avy838Ly838Ly00001n1m8p83auy1l8l1l8o000004z8r83Wky83Wky838Ly838Ly00001m1l8l1l8o000004z8r83cEy83cEy838Ly838Ly00001m1l8l1l8o0000");
    string_constant_79 = 
	    STATIC_STRING("04z8r83dRy83dRy838Ly838Ly00001m1l8l1l8o00000");
    string_constant_80 = 
	    STATIC_STRING("1w8q1m838Ly1l83-+y1r83Vvy01m8p8313y8l8o83Fy83Hy1s83WHy01m8p83dTy8l8o83Fy83Hy83-3y1r83YLyk1m8p83YLy8l8o83Fy83Hy1r83Tqy01m8p08l8o8");
    string_constant_81 = 
	    STATIC_STRING("3Fy83Hy1r83LXyk8l8o83Fy83Hy83-3y1p83Jty01m8p83Jsy8l8o1p83avy01m8p83auy8l8o1o83Wky08l8o1o83cEy08l8o1o83dRy08l8o");
    temp = regenerate_optimized_constant(string_constant_74);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79));
    add_class_to_environment(9,Qfile_progress,list_constant_18,Nil,temp,
	    Nil,temp_1,list_constant_18,
	    regenerate_optimized_constant(LIST_2(string_constant_80,
	    string_constant_81)),Nil);
    Qdirection_of_file_progress_qm = 
	    STATIC_SYMBOL("DIRECTION-OF-FILE-PROGRESS\?",AB_package);
    Qdirection = STATIC_SYMBOL("DIRECTION",AB_package);
    alias_slot_name(3,Qdirection_of_file_progress_qm,Qdirection,
	    Qfile_progress);
    Qstatus_of_file_progress_qm = 
	    STATIC_SYMBOL("STATUS-OF-FILE-PROGRESS\?",AB_package);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    alias_slot_name(3,Qstatus_of_file_progress_qm,Qstatus,Qfile_progress);
    Qnamestring_of_file_in_progress_qm = 
	    STATIC_SYMBOL("NAMESTRING-OF-FILE-IN-PROGRESS\?",AB_package);
    Qfile_name = STATIC_SYMBOL("FILE-NAME",AB_package);
    alias_slot_name(3,Qnamestring_of_file_in_progress_qm,Qfile_name,
	    Qfile_progress);
    Qmodule_of_file_in_progress_qm = 
	    STATIC_SYMBOL("MODULE-OF-FILE-IN-PROGRESS\?",AB_package);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    alias_slot_name(3,Qmodule_of_file_in_progress_qm,Qmodule,Qfile_progress);
    string_constant_28 = STATIC_STRING("~(~a~)");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qout = STATIC_SYMBOL("OUT",AB_package);
    Qdirection_of_file_progress = 
	    STATIC_SYMBOL("DIRECTION-OF-FILE-PROGRESS",AB_package);
    Qwrite_direction_of_file_progress_from_slot = 
	    STATIC_SYMBOL("WRITE-DIRECTION-OF-FILE-PROGRESS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_direction_of_file_progress_from_slot,
	    STATIC_FUNCTION(write_direction_of_file_progress_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qdirection_of_file_progress,
	    SYMBOL_FUNCTION(Qwrite_direction_of_file_progress_from_slot),
	    Qslot_value_writer);
    Qunopened = STATIC_SYMBOL("UNOPENED",AB_package);
    string_constant_29 = STATIC_STRING("unopened");
    string_constant_30 = STATIC_STRING("writing");
    Qclosing = STATIC_SYMBOL("CLOSING",AB_package);
    string_constant_31 = STATIC_STRING("closing");
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    string_constant_32 = STATIC_STRING("closed");
    Qaborted = STATIC_SYMBOL("ABORTED",AB_package);
    string_constant_33 = STATIC_STRING("ABORTED");
    Qstatus_of_file_progress = STATIC_SYMBOL("STATUS-OF-FILE-PROGRESS",
	    AB_package);
    Qwrite_status_of_file_progress_from_slot = 
	    STATIC_SYMBOL("WRITE-STATUS-OF-FILE-PROGRESS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_status_of_file_progress_from_slot,
	    STATIC_FUNCTION(write_status_of_file_progress_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qstatus_of_file_progress,
	    SYMBOL_FUNCTION(Qwrite_status_of_file_progress_from_slot),
	    Qslot_value_writer);
    if (Number_of_kb_characters_so_far_qm == UNBOUND)
	Number_of_kb_characters_so_far_qm = Nil;
    array_constant_2 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qunquoted_file_name_qm = STATIC_SYMBOL("UNQUOTED-FILE-NAME\?",AB_package);
    Qwrite_unquoted_file_name_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-UNQUOTED-FILE-NAME\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_unquoted_file_name_qm_from_slot,
	    STATIC_FUNCTION(write_unquoted_file_name_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qunquoted_file_name_qm,
	    SYMBOL_FUNCTION(Qwrite_unquoted_file_name_qm_from_slot),
	    Qslot_value_writer);
    if (Total_items_in_file == UNBOUND)
	Total_items_in_file = Nil;
    if (Write_xml_object_items_collected == UNBOUND)
	Write_xml_object_items_collected = Nil;
    Qreinitialize = STATIC_SYMBOL("REINITIALIZE",AB_package);
    Qpost_load = STATIC_SYMBOL("POST-LOAD",AB_package);
    Qpost_load2 = STATIC_SYMBOL("POST-LOAD2",AB_package);
    Qrevert = STATIC_SYMBOL("REVERT",AB_package);
    Qreformat = STATIC_SYMBOL("REFORMAT",AB_package);
    Qautomerge = STATIC_SYMBOL("AUTOMERGE",AB_package);
    Qautomerge2 = STATIC_SYMBOL("AUTOMERGE2",AB_package);
    Qfinished = STATIC_SYMBOL("FINISHED",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)8L,Qreinitialize,Qpost_load,
	    Qpost_load2,Qrevert,Qreformat,Qautomerge,Qautomerge2,Qfinished);
    File_progress_finished_reading_states = list_constant_19;
    array_constant_3 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)37L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    list_constant_6 = STATIC_CONS(Qopen,list_constant_5);
    array_constant_6 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    string_constant_34 = STATIC_STRING("  [~(~a~)]");
    Qprogress_through_file = STATIC_SYMBOL("PROGRESS-THROUGH-FILE",AB_package);
    Qwrite_progress_through_file_from_slot = 
	    STATIC_SYMBOL("WRITE-PROGRESS-THROUGH-FILE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_progress_through_file_from_slot,
	    STATIC_FUNCTION(write_progress_through_file_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qprogress_through_file,
	    SYMBOL_FUNCTION(Qwrite_progress_through_file_from_slot),
	    Qslot_value_writer);
    if (Kb_file_progress == UNBOUND)
	Kb_file_progress = Nil;
    if (Number_of_kb_lines_so_far == UNBOUND)
	Number_of_kb_lines_so_far = FIX((SI_Long)0L);
    if (Do_not_update_file_progress_display_qm == UNBOUND)
	Do_not_update_file_progress_display_qm = Nil;
    if (Do_not_restore_image_planes_qm == UNBOUND)
	Do_not_restore_image_planes_qm = Nil;
    if (Do_not_notify_user_during_kb_load_qm == UNBOUND)
	Do_not_notify_user_during_kb_load_qm = Nil;
    if (Do_not_show_conflicts_during_kb_load_qm == UNBOUND)
	Do_not_show_conflicts_during_kb_load_qm = Nil;
    if (Do_not_allow_user_interactions_during_kb_load_qm == UNBOUND)
	Do_not_allow_user_interactions_during_kb_load_qm = Nil;
    Qselected_file_progress_attributes_to_show_subsets_plist = 
	    STATIC_SYMBOL("SELECTED-FILE-PROGRESS-ATTRIBUTES-TO-SHOW-SUBSETS-PLIST",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qselected_file_progress_attributes_to_show_subsets_plist,
	    Selected_file_progress_attributes_to_show_subsets_plist);
    Qkb_load1 = STATIC_SYMBOL("KB-LOAD1",AB_package);
    record_system_variable(Qselected_file_progress_attributes_to_show_subsets_plist,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    list_constant_7 = STATIC_CONS(Qprogress_through_file,Qnil);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qnumber_of_kb_characters_so_far_qm = 
	    STATIC_SYMBOL("NUMBER-OF-KB-CHARACTERS-SO-FAR\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnumber_of_kb_characters_so_far_qm,
	    Number_of_kb_characters_so_far_qm);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qdialog_workspace_frame_style = 
	    STATIC_SYMBOL("DIALOG-WORKSPACE-FRAME-STYLE",AB_package);
    Qdefault_workspace_frame_style = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-FRAME-STYLE",AB_package);
    Qlength_of_file_in_characters_qm = 
	    STATIC_SYMBOL("LENGTH-OF-FILE-IN-CHARACTERS\?",AB_package);
    Qfixnum_time_of_last_file_progress_display_update = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-FILE-PROGRESS-DISPLAY-UPDATE",
	    AB_package);
    Qunits_for_progress_through_file = 
	    STATIC_SYMBOL("UNITS-FOR-PROGRESS-THROUGH-FILE",AB_package);
    Qitems = STATIC_SYMBOL("ITEMS",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qtotal_number_of_items = STATIC_SYMBOL("TOTAL-NUMBER-OF-ITEMS",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    string_constant_35 = 
	    STATIC_STRING("starting kb file \'~a\' loading (merging) on: ~a ~a ~a, ~a:~a:~a");
    string_constant_82 = STATIC_STRING("Jan");
    string_constant_83 = STATIC_STRING("Feb");
    string_constant_84 = STATIC_STRING("Mar");
    string_constant_85 = STATIC_STRING("Apr");
    string_constant_86 = STATIC_STRING("May");
    string_constant_87 = STATIC_STRING("Jun");
    string_constant_88 = STATIC_STRING("Jul");
    string_constant_89 = STATIC_STRING("Aug");
    string_constant_90 = STATIC_STRING("Sep");
    string_constant_91 = STATIC_STRING("Oct");
    string_constant_92 = STATIC_STRING("Nov");
    string_constant_93 = STATIC_STRING("Dec");
    list_constant_8 = STATIC_LIST((SI_Long)12L,string_constant_82,
	    string_constant_83,string_constant_84,string_constant_85,
	    string_constant_86,string_constant_87,string_constant_88,
	    string_constant_89,string_constant_90,string_constant_91,
	    string_constant_92,string_constant_93);
    Qg2_defstruct_structure_name_workstation_g2_struct = 
	    STATIC_SYMBOL("WORKSTATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    Qgsi_interface_icp_socket = STATIC_SYMBOL("GSI-INTERFACE-ICP-SOCKET",
	    AB_package);
    string_constant_36 = 
	    STATIC_STRING("ending kb file \'~a\' loading (merging) on: ~a ~a ~a, ~a:~a:~a");
    string_constant_37 = 
	    STATIC_STRING("the time span for the kb \'~a\' loading (merging) is ~as");
    Qwarmboot_afterwards = STATIC_SYMBOL("WARMBOOT-AFTERWARDS",AB_package);
    Qwarmboot_afterwards_with_catch_up = 
	    STATIC_SYMBOL("WARMBOOT-AFTERWARDS-WITH-CATCH-UP",AB_package);
    string_constant_38 = 
	    STATIC_STRING("Warmbooting can only be done when loading~A.  Cancelling the command!");
    string_constant_39 = STATIC_STRING(", not when merging");
    string_constant_40 = 
	    STATIC_STRING(" a single KB file with no required modules");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_41 = 
	    STATIC_STRING("Replace existing KB with modules as shown\?");
    string_constant_42 = 
	    STATIC_STRING("Merge modules as shown into existing kb\?");
    string_constant_43 = STATIC_STRING("Replace existing KB with \"~a\"");
    string_constant_44 = STATIC_STRING("Merge \"~a\" into existing KB");
    string_constant_45 = 
	    STATIC_STRING("  (Note: See the logbook for source code control warnings.)");
    Qloading = STATIC_SYMBOL("LOADING",AB_package);
    Qwarmboot_kb = STATIC_SYMBOL("WARMBOOT-KB",AB_package);
    Qread_modules_of_kb_per_loading_schedule = 
	    STATIC_SYMBOL("READ-MODULES-OF-KB-PER-LOADING-SCHEDULE",
	    AB_package);
    Qreclaim_module_loading_schedule_and_representations_thereof = 
	    STATIC_SYMBOL("RECLAIM-MODULE-LOADING-SCHEDULE-AND-REPRESENTATIONS-THEREOF",
	    AB_package);
    if (Some_module_is_clear_text_p == UNBOUND)
	Some_module_is_clear_text_p = Nil;
    if (Kb_file_progress_is_currently_for_modules_p == UNBOUND)
	Kb_file_progress_is_currently_for_modules_p = Nil;
    if (Current_kb_file_progress_for_modules_qm == UNBOUND)
	Current_kb_file_progress_for_modules_qm = Nil;
    Need_call_system_start = Nil;
    string_constant_46 = 
	    STATIC_STRING("Skipping module ~a, since it is already present.");
    string_constant_47 = STATIC_STRING("Module ~a could not be found!");
    Kerror_recovery = STATIC_SYMBOL("ERROR-RECOVERY",Pkeyword);
    string_constant_48 = 
	    STATIC_STRING("WARNING!! This KB was not loaded successfully.");
    Qstart_afterwards = STATIC_SYMBOL("START-AFTERWARDS",AB_package);
    Qload_grammar = STATIC_SYMBOL("LOAD-GRAMMAR",AB_package);
    Qmerge_grammar = STATIC_SYMBOL("MERGE-GRAMMAR",AB_package);
    Qload_from_command_line = STATIC_SYMBOL("LOAD-FROM-COMMAND-LINE",
	    AB_package);
    Qnever_start_afterwards = STATIC_SYMBOL("NEVER-START-AFTERWARDS",
	    AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    string_constant_49 = 
	    string_append2(STATIC_STRING("G2 cannot start automatically because this KB has not been ~\n                  compiled up-to-date and saved in the current version of G2.  ~\n                  Once you save t"),
	    STATIC_STRING("he KB in this version of G2, it will be possible ~\n\t          for G2 to start automatically."));
    SET_SYMBOL_FUNCTION(Qread_modules_of_kb_per_loading_schedule,
	    STATIC_FUNCTION(read_modules_of_kb_per_loading_schedule,NIL,
	    FALSE,6,6));
    Qmodule_load_request = STATIC_SYMBOL("MODULE-LOAD-REQUEST",AB_package);
    list_constant_20 = STATIC_CONS(Qfile_progress,Qnil);
    check_if_superior_classes_are_defined(Qmodule_load_request,
	    list_constant_20);
    string_constant_94 = 
	    STATIC_STRING("1m4z8r83Vxy83Vxy83Vuy83Vuy00001p1m8p8313y1l8l1l8o1l83Fy1l83Hy000004z8r83W0y83W0y83Vuy83Vuy00001p1m8p835ey1l8l1l8o1l83Fy1l83Hy000");
    string_constant_95 = STATIC_STRING("00");
    string_constant_96 = 
	    STATIC_STRING("1o8q1m83Vuy1l838Ly1r83Vxy01m8p8313y8l8o83Fy83Hy1r83W0y01m8p835ey8l8o83Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_74);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_94,
	    string_constant_95));
    add_class_to_environment(9,Qmodule_load_request,list_constant_20,Nil,
	    temp,Nil,temp_1,list_constant_20,
	    regenerate_optimized_constant(string_constant_96),Nil);
    Qselected_module_load_request_attributes_to_show_subsets_plist = 
	    STATIC_SYMBOL("SELECTED-MODULE-LOAD-REQUEST-ATTRIBUTES-TO-SHOW-SUBSETS-PLIST",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qselected_module_load_request_attributes_to_show_subsets_plist,
	    Selected_module_load_request_attributes_to_show_subsets_plist);
    record_system_variable(Qselected_module_load_request_attributes_to_show_subsets_plist,
	    Qkb_load1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qmodules_this_required = STATIC_SYMBOL("MODULES-THIS-REQUIRED",AB_package);
    Qmodule_that_required_this_qm = 
	    STATIC_SYMBOL("MODULE-THAT-REQUIRED-THIS\?",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,
	    Qmodule_of_file_in_progress_qm,Qnamestring_of_file_in_progress_qm);
    Qsmall_file_progress_display_value_format = 
	    STATIC_SYMBOL("SMALL-FILE-PROGRESS-DISPLAY-VALUE-FORMAT",
	    AB_package);
    string_constant_97 = 
	    STATIC_STRING("13Ny83-Qy83-By083bys83ayo83Wys83cyo83kyk83-=ys83ny1l83-ry83ty3Ey83syy83uyn83-7y3C+y83iy33my");
    mutate_global_property(Qsmall_file_progress_display_value_format,
	    regenerate_optimized_constant(string_constant_97),
	    Qformat_description);
    array_constant_30 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)12L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)17L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)19L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)31L,(SI_Long)57344L);
    Module_schedule_title = array_constant_30;
    Qtitle_bar_text = STATIC_SYMBOL("TITLE-BAR-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_module_loading_schedule_and_representations_thereof,
	    STATIC_FUNCTION(reclaim_module_loading_schedule_and_representations_thereof,
	    NIL,FALSE,1,1));
    array_constant_9 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qicon = STATIC_SYMBOL("ICON",AB_package);
    Qab_warning = STATIC_SYMBOL("WARNING",AB_package);
    Qquestion = STATIC_SYMBOL("QUESTION",AB_package);
    Qcheckable = STATIC_SYMBOL("CHECKABLE",AB_package);
    Qsaving = STATIC_SYMBOL("SAVING",AB_package);
    Qrow_count = STATIC_SYMBOL("ROW-COUNT",AB_package);
    Qcolumns = STATIC_SYMBOL("COLUMNS",AB_package);
    array_constant_31 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)57344L);
    array_constant_32 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)57344L);
    list_constant_10 = STATIC_LIST((SI_Long)2L,array_constant_31,
	    array_constant_32);
    Qrows = STATIC_SYMBOL("ROWS",AB_package);
    Directory_cache_use_disabled_p = T;
    if (File_system_directory_search_cache_active_p == UNBOUND)
	File_system_directory_search_cache_active_p = Nil;
    if (File_system_directory_search_cache_wildcard_string == UNBOUND)
	File_system_directory_search_cache_wildcard_string = Nil;
    string_constant_50 = STATIC_STRING("~a~a");
    Qgensym_pathnames_equal_p = STATIC_SYMBOL("GENSYM-PATHNAMES-EQUAL-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgensym_pathnames_equal_p,
	    STATIC_FUNCTION(gensym_pathnames_equal_p,NIL,FALSE,2,2));
    string_constant_51 = STATIC_STRING("*.*");
    array_constant_11 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    Qdefault_g2_module_map_pathname = 
	    STATIC_SYMBOL("DEFAULT-G2-MODULE-MAP-PATHNAME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_g2_module_map_pathname,
	    Default_g2_module_map_pathname);
    Qpathnames = STATIC_SYMBOL("PATHNAMES",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_default_g2_module_map_pathname = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-G2-MODULE-MAP-PATHNAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_g2_module_map_pathname,
	    STATIC_FUNCTION(initialize_default_g2_module_map_pathname,NIL,
	    FALSE,0,0));
    list_constant_21 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_default_g2_module_map_pathname);
    record_system_variable(Qdefault_g2_module_map_pathname,Qpathnames,
	    list_constant_21,Qnil,Qnil,Qnil,Qnil);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    list_constant_11 = STATIC_CONS(Kabsolute,Qnil);
    array_constant_15 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    Qpathname_for_disabling_g2_module_map_command_line = 
	    STATIC_SYMBOL("PATHNAME-FOR-DISABLING-G2-MODULE-MAP-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_for_disabling_g2_module_map_command_line,
	    Pathname_for_disabling_g2_module_map_command_line);
    Qinitializer_for_pathname_for_disabling_g2_module_map_command_line = 
	    STATIC_SYMBOL("INITIALIZER-FOR-PATHNAME-FOR-DISABLING-G2-MODULE-MAP-COMMAND-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitializer_for_pathname_for_disabling_g2_module_map_command_line,
	    STATIC_FUNCTION(initializer_for_pathname_for_disabling_g2_module_map_command_line,
	    NIL,FALSE,0,0));
    list_constant_22 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitializer_for_pathname_for_disabling_g2_module_map_command_line);
    record_system_variable(Qpathname_for_disabling_g2_module_map_command_line,
	    Qpathnames,list_constant_22,Qnil,Qnil,Qnil,Qnil);
    array_constant_17 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdefault_directory = STATIC_SYMBOL("DEFAULT-DIRECTORY",AB_package);
    Qpath_directories = STATIC_SYMBOL("PATH-DIRECTORIES",AB_package);
    Qlaunch_directory = STATIC_SYMBOL("LAUNCH-DIRECTORY",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qdefault_directory,
	    Qpath_directories,Qlaunch_directory);
    string_constant_52 = 
	    STATIC_STRING("No KB file could be found for the module ~\n       named ~a~a~a; cancelling the loading of ~a from ~s.");
    string_constant_53 = STATIC_STRING(", required by ");
    if (Kb_module_currently_to_save_qm == UNBOUND)
	Kb_module_currently_to_save_qm = Nil;
    if (Inhibit_modularity_consistency_checking_qm == UNBOUND)
	Inhibit_modularity_consistency_checking_qm = Nil;
    Qsave_in_clear_text_by_default = 
	    STATIC_SYMBOL("SAVE-IN-CLEAR-TEXT-BY-DEFAULT",AB_package);
    Long_operation_posting_delay_for_module_loading_schedule_creation = 
	    FIX((SI_Long)1000L);
    string_constant_54 = STATIC_STRING("~a~%Please wait . . . ");
    array_constant_19 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)33L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)39L,(SI_Long)57344L);
    Qrequired_modules = STATIC_SYMBOL("REQUIRED-MODULES",AB_package);
    Qpathname_with_default_type_if_required_for_module_pathnames_qm = 
	    STATIC_SYMBOL("PATHNAME-WITH-DEFAULT-TYPE-IF-REQUIRED-FOR-MODULE-PATHNAMES\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpathname_with_default_type_if_required_for_module_pathnames_qm,
	    Pathname_with_default_type_if_required_for_module_pathnames_qm);
    Qmake_pathname_with_default_type_for_modules = 
	    STATIC_SYMBOL("MAKE-PATHNAME-WITH-DEFAULT-TYPE-FOR-MODULES",
	    AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_pathname_with_default_type_for_modules);
    Qreclaim_if_gensym_pathname = 
	    STATIC_SYMBOL("RECLAIM-IF-GENSYM-PATHNAME",AB_package);
    record_system_variable(Qpathname_with_default_type_if_required_for_module_pathnames_qm,
	    Qkb_merge,list_constant_23,Qnil,Qnil,
	    Qreclaim_if_gensym_pathname,Qnil);
    array_constant_20 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qmake_pathname_with_default_type_for_modules,
	    STATIC_FUNCTION(make_pathname_with_default_type_for_modules,
	    NIL,FALSE,0,0));
    Knone = STATIC_SYMBOL("NONE",Pkeyword);
    if (Enable_loading_compiled_kbs_p == UNBOUND)
	Enable_loading_compiled_kbs_p = Nil;
    Qes_l_c = STATIC_SYMBOL("ES-L-C",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qes_l_c,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qes_l_c,STATIC_FUNCTION(es_l_c,NIL,FALSE,0,0));
    if (Enable_saving_compiled_kbs_p == UNBOUND)
	Enable_saving_compiled_kbs_p = Nil;
    if (Delete_compiled_kb_source_p == UNBOUND)
	Delete_compiled_kb_source_p = Nil;
    if (Loading_compiled_kb_p == UNBOUND)
	Loading_compiled_kb_p = Nil;
    string_constant_55 = 
	    STATIC_STRING("The modules in this KB are not consistent; you ~\n          therefore cannot save individual modules.  ~\n          NO PART OF THIS KB HAS BEEN SAVED!");
    Qsave_modules_of_kb_after_confirmation = 
	    STATIC_SYMBOL("SAVE-MODULES-OF-KB-AFTER-CONFIRMATION",AB_package);
    string_constant_56 = STATIC_STRING("Save Modules as Shown\?");
    string_constant_57 = STATIC_STRING(" (note ");
    string_constant_58 = 
	    STATIC_STRING("that the module~a ~L,& will not be saved, because ~a read-only");
    array_constant_21 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    string_constant_59 = STATIC_STRING(", and also ");
    string_constant_60 = 
	    STATIC_STRING("that the module~a ~L,& can not be committed, ~\n                                           because ~a already been committed by someone else");
    array_constant_24 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)57344L);
    string_constant_61 = 
	    STATIC_STRING("that the module~a ~L,& will be not saved in clear text ~\n                                           because ~a proprietary or text-stripped items");
    array_constant_26 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)57344L);
    string_constant_62 = STATIC_STRING(".)");
    Qcurrent_workstation_event = STATIC_SYMBOL("CURRENT-WORKSTATION-EVENT",
	    AB_package);
    Qchecked_items = STATIC_SYMBOL("CHECKED-ITEMS",AB_package);
    array_constant_28 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)21L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)31L,(SI_Long)57344L);
    string_constant_63 = STATIC_STRING("There are no KB to save.");
    SET_SYMBOL_FUNCTION(Qsave_modules_of_kb_after_confirmation,
	    STATIC_FUNCTION(save_modules_of_kb_after_confirmation,NIL,
	    FALSE,3,3));
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    string_constant_64 = 
	    string_append2(STATIC_STRING("The items below participate in permanent intermodule relationships ~\n                  defined by the relation that follows them, but the items do not ~\n                  resi"),
	    STATIC_STRING("de in modules that require the relation module."));
    string_constant_65 = 
	    string_append2(STATIC_STRING("The item below participates in a permanent intermodule relationship ~\n                  defined by the relation that follows it, but the item does not ~\n                  resi"),
	    STATIC_STRING("de in a module that requires the relation module."));
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_66 = 
	    string_append2(STATIC_STRING("The items listed below participate in permanent intermodule ~\n                             relationships defined by the relation ~NF, but the items do not ~\n                  "),
	    STATIC_STRING("           reside in modules that require the relation module ~(~a~): "));
    string_constant_67 = STATIC_STRING(", ");
    string_constant_68 = STATIC_STRING("(module ~(~a~)) ");
    string_constant_69 = STATIC_STRING("~NF");
    Qrelations_with_related_items_in_modules_that_do_not_require_them = 
	    STATIC_SYMBOL("RELATIONS-WITH-RELATED-ITEMS-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM",
	    AB_package);
    Qprint_relations_with_related_items_in_modules_that_do_not_require_them 
	    = 
	    STATIC_SYMBOL("PRINT-RELATIONS-WITH-RELATED-ITEMS-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qprint_relations_with_related_items_in_modules_that_do_not_require_them,
	    STATIC_FUNCTION(print_relations_with_related_items_in_modules_that_do_not_require_them,
	    NIL,FALSE,1,1));
    Qparticulars_printer_for_kb_modularity_problem = 
	    STATIC_SYMBOL("PARTICULARS-PRINTER-FOR-KB-MODULARITY-PROBLEM",
	    AB_package);
    mutate_global_property(Qrelations_with_related_items_in_modules_that_do_not_require_them,
	    Qprint_relations_with_related_items_in_modules_that_do_not_require_them,
	    Qparticulars_printer_for_kb_modularity_problem);
    Qfatal = STATIC_SYMBOL("FATAL",AB_package);
    Qcircularity_in_module_hierarchy = 
	    STATIC_SYMBOL("CIRCULARITY-IN-MODULE-HIERARCHY",AB_package);
    Qmodules_that_exist_are_not_required = 
	    STATIC_SYMBOL("MODULES-THAT-EXIST-ARE-NOT-REQUIRED",AB_package);
    Qworkspaces_belong_to_unspecified_module = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-UNSPECIFIED-MODULE",
	    AB_package);
    Qworkspaces_belong_to_unrequired_modules = 
	    STATIC_SYMBOL("WORKSPACES-BELONG-TO-UNREQUIRED-MODULES",
	    AB_package);
    Qmodules_required_by_kb_do_not_exist = 
	    STATIC_SYMBOL("MODULES-REQUIRED-BY-KB-DO-NOT-EXIST",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)5L,
	    Qcircularity_in_module_hierarchy,
	    Qmodules_that_exist_are_not_required,
	    Qworkspaces_belong_to_unspecified_module,
	    Qworkspaces_belong_to_unrequired_modules,
	    Qmodules_required_by_kb_do_not_exist);
    Qclasses_not_defined_in_any_module = 
	    STATIC_SYMBOL("CLASSES-NOT-DEFINED-IN-ANY-MODULE",AB_package);
    Qclasses_whose_superiors_are_not_defined_in_required_modules = 
	    STATIC_SYMBOL("CLASSES-WHOSE-SUPERIORS-ARE-NOT-DEFINED-IN-REQUIRED-MODULES",
	    AB_package);
    Qclasses_with_instances_in_modules_that_do_not_require_them = 
	    STATIC_SYMBOL("CLASSES-WITH-INSTANCES-IN-MODULES-THAT-DO-NOT-REQUIRE-THEM",
	    AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qtable_in_different_module_than_item_represented = 
	    STATIC_SYMBOL("TABLE-IN-DIFFERENT-MODULE-THAN-ITEM-REPRESENTED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclasses_whose_superiors_are_not_defined_in_required_modules,
	    Classes_whose_superiors_are_not_defined_in_required_modules);
    SET_SYMBOL_VALUE_LOCATION(Qclasses_not_defined_in_any_module,
	    Classes_not_defined_in_any_module);
    Qworkspace_margin = STATIC_SYMBOL("WORKSPACE-MARGIN",AB_package);
    Qinitial_margin_for_workspaces = 
	    STATIC_SYMBOL("INITIAL-MARGIN-FOR-WORKSPACES",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    string_constant_70 = STATIC_STRING("~NF-DEFINITION");
    string_constant_71 = 
	    STATIC_STRING("The definition ~NF, which has one or more instances, has been ~\n       put on the newly created KB workspace ~a.");
    Long_operation_posting_delay_for_kb_modularity_consistency_check = 
	    FIX((SI_Long)1000L);
    array_constant_29 = STATIC_ARRAY(list_constant_14,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)29L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)30L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)32L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)34L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)36L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)39L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)41L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)42L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)45L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)46L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)48L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)49L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)51L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)53L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)54L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)55L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)56L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)57L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)58L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)59L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)60L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)61L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)78L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)79L,(SI_Long)57344L);
    Qmodule_relationship_key_equal = 
	    STATIC_SYMBOL("MODULE-RELATIONSHIP-KEY-EQUAL",AB_package);
    Qdependent = STATIC_SYMBOL("DEPENDENT",AB_package);
    Qnon_dependent = STATIC_SYMBOL("NON-DEPENDENT",AB_package);
    Qrelation_is_permanent = STATIC_SYMBOL("RELATION-IS-PERMANENT",AB_package);
}
