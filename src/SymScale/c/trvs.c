/* trvs.c
 * Input file:  traversals.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "trvs.h"


DEFINE_VARIABLE_WITH_SYMBOL(Attributes_collector, Qattributes_collector);

DEFINE_VARIABLE_WITH_SYMBOL(Attributes_collector_tail, Qattributes_collector_tail);

Object Top_level_kb_elements_for_saving = UNBOUND;

static Object Kkb;                 /* :kb */

static Object Ksystem_frames;      /* :system-frames */

static Object Kdefinitions;        /* :definitions */

static Object Ktop_level_workspaces;  /* :top-level-workspaces */

static Object Ktransient_items_in_limbo;  /* :transient-items-in-limbo */

static Object Qprocedure_invocation;  /* procedure-invocation */

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* TRAVERSE-KB-FOR-SAVING */
Object traverse_kb_for_saving(tree)
    Object tree;
{
    x_note_fn_call(230,0);
    if (SYMBOLP(tree)) {
	if (EQ(tree,Kkb))
	    return copy_list_using_journal_conses_1(Top_level_kb_elements_for_saving);
	else if (EQ(tree,Ksystem_frames))
	    return traverse_system_frames_of_kb_for_saving();
	else if (EQ(tree,Kdefinitions))
	    return traverse_definitions_of_kb_for_saving();
	else if (EQ(tree,Ktop_level_workspaces))
	    return traverse_top_level_workspaces_of_kb_for_saving();
	else if (EQ(tree,Ktransient_items_in_limbo))
	    return traverse_transient_items_of_kb_for_saving();
	else if ( !EQ(tree,Qprocedure_invocation))
	    return traverse_transient_class_instances_of_kb_for_saving(tree);
	else
	    return VALUES_1(Nil);
    }
    else if (SIMPLE_VECTOR_P(tree) && EQ(ISVREF(tree,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	return VALUES_1(Nil);
    else
	return traverse_block_for_saving(tree);
}

static Object Qsystem_frame;       /* system-frame */

static Object list_constant;       /* # */

/* TRAVERSE-SYSTEM-FRAMES-OF-KB-FOR-SAVING */
Object traverse_system_frames_of_kb_for_saving()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4, block, module;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(230,1);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
      ab_loopvar_ = collect_subclasses(Qsystem_frame);
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
      if (ISVREF(Current_kb_save,(SI_Long)37L)) {
	  block = frame;
	  module = ISVREF(Current_kb_save,(SI_Long)37L);
	  temp = EQ(get_module_block_is_in(block),module);
      }
      else {
	  temp = TRUEP(system_table_installed_p(frame));
	  if (temp);
	  else
	      temp = TRUEP(ISVREF(frame,(SI_Long)21L));
      }
      if (temp ? TRUEP(has_slot_values_to_save_p(2,frame,list_constant)) : 
	      TRUEP(Nil)) {
	  ab_loopvar__4 = journal_cons_1(frame,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(ab_loopvar__2);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* WITHIN-MODULE-BEING-SAVED-P */
Object within_module_being_saved_p(block)
    Object block;
{
    Object temp, module;

    x_note_fn_call(230,2);
    temp =  !TRUEP(ISVREF(Current_kb_save,(SI_Long)37L)) ? T : Nil;
    if (temp);
    else {
	module = ISVREF(Current_kb_save,(SI_Long)37L);
	temp = EQ(get_module_block_is_in(block),module) ? T : Nil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Definitions_for_saving, Qdefinitions_for_saving);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* SAVABLE-DEFINITION-P */
Object savable_definition_p(definition)
    Object definition;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(230,3);
    if (SIMPLE_VECTOR_P(definition) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition)) > (SI_Long)2L &&  
	    !EQ(ISVREF(definition,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(definition,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = ((temp ? (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)4L)) 
	    & (SI_Long)1L) || ISVREF(Current_saving_context,(SI_Long)3L) 
	    && (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	    (SI_Long)262144L) : TRUEP(Nil)) ? 
	    TRUEP(within_module_being_saved_p(definition)) : TRUEP(Nil)) ? 
	    ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	    (SI_Long)32L)) ? T : Nil) : Nil;
    return VALUES_1(temp_1);
}

/* DEFINITION-IS-DEPENDENT-ON-UNCOLLECTED-DEFINITIONS-P */
Object definition_is_dependent_on_uncollected_definitions_p(definition)
    Object definition;
{
    Object class_of_definition, definition_for_class_of_definition, temp;
    Object superior, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp_1;

    x_note_fn_call(230,4);
    class_of_definition = ISVREF(ISVREF(definition,(SI_Long)1L),(SI_Long)1L);
    definition_for_class_of_definition = 
	    lookup_global_or_kb_specific_property_value(class_of_definition,
	    Class_definition_gkbprop);
    temp = savable_definition_p(definition_for_class_of_definition) ? 
	    journal_cons_1(definition_for_class_of_definition,Nil) : Qnil;
    if (instantiated_class_p(ISVREF(definition,(SI_Long)20L))) {
	superior = Nil;
	ab_loop_list_ = ISVREF(definition,(SI_Long)21L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (savable_definition_p(lookup_global_or_kb_specific_property_value(superior,
		Class_definition_gkbprop))) {
	    ab_loopvar__2 = 
		    journal_cons_1(lookup_global_or_kb_specific_property_value(superior,
		    Class_definition_gkbprop),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    temp_1 = nconc2(temp,temp_1);
    return VALUES_1(temp_1);
}

/* COLLECT-DEFINITION-FOR-SAVING */
Object collect_definition_for_saving(definition)
    Object definition;
{
    Object journal_consed_dependent_definitions_qm, dependent_definition;
    Object ab_loop_list_;
    SI_Long svref_new_value;

    x_note_fn_call(230,5);
    journal_consed_dependent_definitions_qm = 
	    definition_is_dependent_on_uncollected_definitions_p(definition);
    if (journal_consed_dependent_definitions_qm) {
	dependent_definition = Nil;
	ab_loop_list_ = journal_consed_dependent_definitions_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	dependent_definition = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	collect_definition_for_saving(dependent_definition);
	goto next_loop;
      end_loop:
	reclaim_journal_list_1(journal_consed_dependent_definitions_qm);
	svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) | (SI_Long)32L;
	ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	Definitions_for_saving = nconc2(Definitions_for_saving,
		journal_cons_1(definition,Nil));
	return VALUES_1(Qnil);
    }
    else {
	svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) | (SI_Long)32L;
	ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	Definitions_for_saving = nconc2(Definitions_for_saving,
		journal_cons_1(definition,Nil));
	return VALUES_1(Definitions_for_saving);
    }
}

static Object Qclass_definition;   /* class-definition */

static Object Qunits_of_measure_declaration;  /* units-of-measure-declaration */

static Object Qitem;               /* item */

static Object Qframe_flags;        /* frame-flags */

/* TRAVERSE-DEFINITIONS-OF-KB-FOR-SAVING */
Object traverse_definitions_of_kb_for_saving()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, definition, uomd, value;
    Object ab_loopvar__2, ab_loopvar__3, temp_1, temp_2, class_1;
    Object journal_consed_definition_list, ab_loop_list_, return_value, temp_3;
    Object x2, temp_4, ab_loopvar__4, result_1, noting_changes_to_kb_p;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(230,6);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qclass_definition);
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
      definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) &  ~(SI_Long)32L;
      ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    ab_loopvar_ = 
	    lookup_kb_specific_property_value(Qunits_of_measure_declaration,
	    Instances_specific_to_this_class_kbprop);
    uomd = Nil;
    value = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop_2;
    uomd = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    temp_1 = ISVREF(uomd,(SI_Long)16L);
    value = CAR(temp_1);
    if (((SI_Long)0L != (IFIX(ISVREF(uomd,(SI_Long)4L)) & (SI_Long)1L) || 
	    ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	    (IFIX(ISVREF(uomd,(SI_Long)5L)) & (SI_Long)262144L)) && 
	    within_module_being_saved_p(uomd) &&  !EQ(value,No_value) && 
		value) {
	ab_loopvar__3 = journal_cons_1(uomd,Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__3;
	else
	    ab_loopvar__1 = ab_loopvar__3;
	ab_loopvar__2 = ab_loopvar__3;
    }
    goto next_loop_2;
  end_loop_2:
    temp_2 = ab_loopvar__1;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qclass_definition;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      definition = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop_3:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop_3;
      temp_1 = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp_1;
      definition = lookup_global_or_kb_specific_property_value(class_1,
	      Class_definition_gkbprop);
      if (savable_definition_p(definition)) {
	  ab_loopvar__3 = journal_cons_1(definition,Nil);
	  if (ab_loopvar__2)
	      M_CDR(ab_loopvar__2) = ab_loopvar__3;
	  else
	      ab_loopvar__1 = ab_loopvar__3;
	  ab_loopvar__2 = ab_loopvar__3;
      }
      goto next_loop_3;
    end_loop_3:
      journal_consed_definition_list = ab_loopvar__1;
      goto end_2;
      journal_consed_definition_list = Qnil;
    end_2:;
    POP_SPECIAL();
    definition = Nil;
    ab_loop_list_ = journal_consed_definition_list;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    definition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	    (SI_Long)32L)))
	collect_definition_for_saving(definition);
    goto next_loop_4;
  end_loop_4:
    return_value = copy_list_using_journal_conses_1(Definitions_for_saving);
    reclaim_journal_list_1(journal_consed_definition_list);
    reclaim_journal_list_1(Definitions_for_saving);
    Definitions_for_saving = Nil;
    temp_3 = return_value;
    goto end_3;
    temp_3 = Qnil;
  end_3:;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = Qitem;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      definition = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop_5:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop_5;
      temp_1 = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp_1;
      definition = lookup_global_or_kb_specific_property_value(class_1,
	      Class_definition_gkbprop);
      if (SIMPLE_VECTOR_P(definition) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition)) > (SI_Long)2L && 
	       !EQ(ISVREF(definition,(SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(definition,(SI_Long)1L);
	  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp = TRUEP(Nil);
      if (((temp ? (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)4L)) & 
	      (SI_Long)1L) || ISVREF(Current_saving_context,(SI_Long)3L) 
	      && (SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	      (SI_Long)262144L) : TRUEP(Nil)) ? 
	      TRUEP(within_module_being_saved_p(definition)) : TRUEP(Nil)) 
	      ?  !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	      (SI_Long)32L)) : TRUEP(Nil)) {
	  svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) | 
		  (SI_Long)32L;
	  ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
	  ab_loopvar__3 = journal_cons_1(definition,Nil);
	  if (ab_loopvar__2)
	      M_CDR(ab_loopvar__2) = ab_loopvar__3;
	  else
	      ab_loopvar__1 = ab_loopvar__3;
	  ab_loopvar__2 = ab_loopvar__3;
      }
      goto next_loop_5;
    end_loop_5:
      temp_4 = ab_loopvar__1;
      goto end_4;
      temp_4 = Qnil;
    end_4:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
      ab_loopvar_ = collect_subclasses(Qclass_definition);
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
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_7;
      definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	      (SI_Long)32L)) && ((SI_Long)0L != (IFIX(ISVREF(definition,
	      (SI_Long)4L)) & (SI_Long)1L) || 
	      ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	      (IFIX(ISVREF(definition,(SI_Long)5L)) & (SI_Long)262144L)) 
	      && within_module_being_saved_p(definition)) {
	  ab_loopvar__4 = journal_cons_1(definition,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop_6;
    end_loop_7:
      temp_1 = ab_loopvar__2;
      goto end_5;
      temp_1 = Qnil;
    end_5:;
    POP_SPECIAL();
    result_1 = nconc2(temp_2,nconc2(temp_3,nconc2(temp_4,temp_1)));
    temp_1 = result_1;
    definition = Nil;
    ab_loop_list_ = result_1;
  next_loop_8:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_8;
    definition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    svref_new_value = IFIX(ISVREF(definition,(SI_Long)5L)) &  ~(SI_Long)32L;
    ISVREF(definition,(SI_Long)5L) = FIX(svref_new_value);
    if ( !((SI_Long)0L != (IFIX(ISVREF(definition,(SI_Long)5L)) & 
	    (SI_Long)262144L)) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(definition,(SI_Long)4L)) & (SI_Long)1L))) {
	noting_changes_to_kb_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
		0);
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(definition,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(definition,(SI_Long)4L)) | (SI_Long)1L;
	  ISVREF(definition,(SI_Long)4L) = FIX(svref_new_value);
	POP_SPECIAL();
    }
    goto next_loop_8;
  end_loop_8:;
    return VALUES_1(temp_1);
}

static Object Qkb_workspace;       /* kb-workspace */

/* TRAVERSE-TOP-LEVEL-WORKSPACES-OF-KB-FOR-SAVING */
Object traverse_top_level_workspaces_of_kb_for_saving()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace, ab_loopvar__2;
    Object ab_loopvar__3, ab_loopvar__4;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(230,7);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
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
      workspace = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !TRUEP(ISVREF(workspace,(SI_Long)18L)) && ((SI_Long)0L != 
	      (IFIX(ISVREF(workspace,(SI_Long)4L)) & (SI_Long)1L) || 
	      ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	      (IFIX(ISVREF(workspace,(SI_Long)5L)) & (SI_Long)262144L)) && 
	      within_module_being_saved_p(workspace)) {
	  ab_loopvar__4 = journal_cons_1(workspace,Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(ab_loopvar__2);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qloose_end;          /* loose-end */

/* TRAVERSE-TRANSIENT-ITEMS-OF-KB-FOR-SAVING */
Object traverse_transient_items_of_kb_for_saving()
{
    x_note_fn_call(230,8);
    if (ISVREF(Current_saving_context,(SI_Long)3L))
	return journal_cons_1(Qloose_end,journal_cons_1(Qitem,Nil));
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qparent_frame;       /* parent-frame */

/* TRAVERSE-TRANSIENT-CLASS-INSTANCES-OF-KB-FOR-SAVING */
Object traverse_transient_class_instances_of_kb_for_saving(class_1)
    Object class_1;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_1, temp_2, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object kb_workspace_subclass_p, ab_loopvar_, instance, ab_loopvar__1;
    Object ab_loopvar__2, ab_loopvar__3, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, frame_or_class;
    Object ab_loopvar__4, ab_loopvar__5, ab_less_than_branch_qm_, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(230,9);
    temp = 
	    copy_list_using_journal_conses_1(lookup_global_or_kb_specific_property_value(class_1,
	    Inferior_classes_gkbprop));
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
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
	gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
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
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	    kb_workspace_subclass_p = (SI_Long)0L < gensymed_symbol_3 ? T :
		     Nil;
	}
	else
	    kb_workspace_subclass_p = Nil;
    }
    else
	kb_workspace_subclass_p = Nil;
    ab_loopvar_ = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
    instance = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
  next_loop_12:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop_12;
    instance = ab_loopvar_;
    ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
    if ((SI_Long)0L != (IFIX(ISVREF(instance,(SI_Long)5L)) & 
		(SI_Long)262144L)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(instance,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp_3 =  !TRUEP(gensymed_symbol);
    }
    else
	temp_3 = TRUEP(Nil);
    if (((temp_3 ?  !TRUEP(get_lookup_slot_value_given_default(instance,
	    Qparent_frame,Nil)) : TRUEP(Nil)) ?  
	    !TRUEP(kb_workspace_subclass_p) ||  !TRUEP(ISVREF(instance,
	    (SI_Long)18L)) : TRUEP(Nil)) ? (SI_Long)0L != 
	    (IFIX(ISVREF(instance,(SI_Long)5L)) & (SI_Long)8L) : TRUEP(Nil)) {
	ab_loopvar__3 = journal_cons_1(instance,Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__3;
	else
	    ab_loopvar__1 = ab_loopvar__3;
	ab_loopvar__2 = ab_loopvar__3;
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(instance,(SI_Long)14L));
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
	  frame_or_class = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar__5 = Nil;
	  gensymed_symbol = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol)) {
	      temp_2 = M_CAR(gensymed_symbol);
	      temp_3 = SIMPLE_VECTOR_P(temp_2);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3) {
	      temp_2 = M_CDR(gensymed_symbol);
	      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_2) ? T : Nil;
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
	next_loop_13:
	next_loop_14:
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
		next_loop_15:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_13;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_15;
		end_loop_13:;
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
		  ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)2L),
		  instance))
	      goto end_5;
	  goto next_loop_14;
	end_loop_14:
	end_5:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_15;
	  connection = ab_connection_;
	  frame_or_class = ISVREF(connection,(SI_Long)1L);
	  ab_loopvar__5 = journal_cons_1(connection,Nil);
	  if (ab_loopvar__4)
	      M_CDR(ab_loopvar__4) = ab_loopvar__5;
	  else
	      ab_loopvar__3 = ab_loopvar__5;
	  ab_loopvar__4 = ab_loopvar__5;
	  if (SIMPLE_VECTOR_P(frame_or_class) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_class)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(frame_or_class,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(frame_or_class,(SI_Long)1L);
	      temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_3 = TRUEP(Nil);
	  if (temp_3 ? TRUEP(has_slot_values_to_save_p(1,frame_or_class)) :
		   TRUEP(Nil)) {
	      ab_loopvar__5 = journal_cons_1(frame_or_class,Nil);
	      if (ab_loopvar__4)
		  M_CDR(ab_loopvar__4) = ab_loopvar__5;
	      else
		  ab_loopvar__3 = ab_loopvar__5;
	      ab_loopvar__4 = ab_loopvar__5;
	  }
	  goto next_loop_13;
	end_loop_15:
	  goto end_6;
	  ab_loopvar__3 = Qnil;
	end_6:;
	POP_SPECIAL();
	if (ab_loopvar__3) {
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__3;
	    else
		ab_loopvar__1 = ab_loopvar__3;
	    ab_loopvar__2 = last(ab_loopvar__3,_);
	}
    }
    goto next_loop_12;
  end_loop_12:
    temp_2 = ab_loopvar__1;
    goto end_7;
    temp_2 = Qnil;
  end_7:;
    return VALUES_1(nconc2(temp,temp_2));
}

static Object Qcollect_attribute_if_savable;  /* collect-attribute-if-savable */

static Object Qimage_definition;   /* image-definition */

static Object Qimage_definition_media_bin;  /* image-definition-media-bin */

static Object Qsimulation_details;  /* simulation-details */

static Object Qg2_java_bean;       /* g2-java-bean */

static Object Qg2_java_bean_media_bin;  /* g2-java-bean-media-bin */

/* TRAVERSE-BLOCK-FOR-SAVING */
Object traverse_block_for_saving(tree)
    Object tree;
{
    Object connections, sub_class_bit_vector, kb_workspace_qm;
    Object gensymed_symbol_3, ab_queue_form_, ab_next_queue_element_, subblock;
    Object collectable_qm, subblocks, ab_loopvar_, ab_loopvar__1, temp, temp_1;
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object connection_frame_or_class, ab_loopvar__2, ab_loopvar__3;
    Object ab_less_than_branch_qm_, x2, attributes_collector;
    Object attributes_collector_tail, slot_description, class_description;
    Object ab_loop_list_, vector_slot_index_qm, slot_value;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm, gensymed_symbol_4, temp_3, subworkspace_qm;
    Object other_inferior_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, max_i, i, ab_loop_bind_;
    char temp_2;
    Declare_special(2);

    x_note_fn_call(230,10);
    if ((SI_Long)0L != (IFIX(ISVREF(tree,(SI_Long)4L)) & (SI_Long)1L) || 
	    ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	    (IFIX(ISVREF(tree,(SI_Long)5L)) & (SI_Long)262144L)) {
	connections = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(tree,(SI_Long)1L),(SI_Long)19L);
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
	    kb_workspace_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    kb_workspace_qm = Nil;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(tree,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol_3;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	collectable_qm = Nil;
	subblocks = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
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
	temp = (SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)4L)) & 
		(SI_Long)1L) ? T : Nil;
	if (temp);
	else
	    temp = ISVREF(Current_saving_context,(SI_Long)3L) ? 
		    ((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
		    (SI_Long)262144L) ? T : Nil) : Qnil;
	collectable_qm = temp;
	if (collectable_qm) {
	    ab_loopvar__1 = journal_cons_1(subblock,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		subblocks = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	if (collectable_qm && kb_workspace_qm) {
	    temp_1 = connections;
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	    ab_skip_list_form_ = gensymed_symbol_3;
	    ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_connection_ = Nil;
	    ab_connection_item_ = Nil;
	    connection = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      connection_frame_or_class = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__3 = Nil;
	      gensymed_symbol_3 = CDR(ab_skip_list_form_);
	      if (CONSP(gensymed_symbol_3)) {
		  temp = M_CAR(gensymed_symbol_3);
		  temp_2 = SIMPLE_VECTOR_P(temp);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  temp = M_CDR(gensymed_symbol_3);
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
		      ab_connection_item_ = ISVREF(ab_current_node_,
			      (SI_Long)3L);
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
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
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
	      if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		      ab_connection_ && EQ(ISVREF(ab_connection_,
		      (SI_Long)2L),subblock))
		  goto end_1;
	      goto next_loop_2;
	    end_loop_2:
	    end_1:
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_3;
	      connection = ab_connection_;
	      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	      if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) 
		      & (SI_Long)64L)) || ISVREF(Current_saving_context,
		      (SI_Long)3L)) {
		  ab_loopvar__3 = journal_cons_1(connection,Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__3;
		  else
		      ab_loopvar__1 = ab_loopvar__3;
		  ab_loopvar__2 = ab_loopvar__3;
	      }
	      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		      > (SI_Long)2L &&  
		      !EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		  temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ((temp_2 ? (SI_Long)0L != 
		      (IFIX(ISVREF(connection_frame_or_class,(SI_Long)4L)) 
		      & (SI_Long)1L) || ISVREF(Current_saving_context,
		      (SI_Long)3L) && (SI_Long)0L != 
		      (IFIX(ISVREF(connection_frame_or_class,(SI_Long)5L)) 
		      & (SI_Long)262144L) : TRUEP(Nil)) ? 
		      TRUEP(has_slot_values_to_save_p(1,
		      connection_frame_or_class)) : TRUEP(Nil)) {
		  ab_loopvar__3 = journal_cons_1(connection_frame_or_class,
			  Nil);
		  if (ab_loopvar__2)
		      M_CDR(ab_loopvar__2) = ab_loopvar__3;
		  else
		      ab_loopvar__1 = ab_loopvar__3;
		  ab_loopvar__2 = ab_loopvar__3;
	      }
	      goto next_loop_1;
	    end_loop_3:
	      temp = ab_loopvar__1;
	      goto end_2;
	      temp = Qnil;
	    end_2:;
	    POP_SPECIAL();
	    connections = nconc2(temp_1,temp);
	}
	goto next_loop;
      end_loop:
	temp_1 = nconc2(subblocks,connections);
	goto end_3;
	temp_1 = Qnil;
      end_3:;
	attributes_collector = Nil;
	attributes_collector_tail = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Attributes_collector_tail,Qattributes_collector_tail,attributes_collector_tail,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Attributes_collector,Qattributes_collector,attributes_collector,
		  0);
	    slot_description = Nil;
	    class_description = ISVREF(tree,(SI_Long)1L);
	    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
	  next_loop_4:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_4;
	    slot_description = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ISVREF(slot_description,(SI_Long)8L)) {
		vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
		if (vector_slot_index_qm)
		    slot_value = ISVREF(tree,IFIX(vector_slot_index_qm));
		else {
		    user_vector_slot_index_qm = ISVREF(slot_description,
			    (SI_Long)8L);
		    if (user_vector_slot_index_qm)
			slot_value = ISVREF(ISVREF(tree,(SI_Long)0L),
				IFIX(user_vector_slot_index_qm));
		    else {
			slot_name = ISVREF(slot_description,(SI_Long)1L);
			lookup_structure_qm = ISVREF(tree,(SI_Long)0L);
			if (lookup_structure_qm) {
			    max_i = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
			    max_i = max_i - (SI_Long)1L;
			    i = IFIX(ISVREF(ISVREF(tree,(SI_Long)1L),
				    (SI_Long)15L));
			    ab_loop_bind_ = max_i;
			  next_loop_5:
			    if (i >= ab_loop_bind_)
				goto end_loop_5;
			    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
				slot_index_qm = FIX(i + (SI_Long)1L);
				goto end_4;
			    }
			    i = i + (SI_Long)2L;
			    goto next_loop_5;
			  end_loop_5:
			    slot_index_qm = Qnil;
			  end_4:;
			    slot_value = slot_index_qm ? 
				    ISVREF(lookup_structure_qm,
				    IFIX(slot_index_qm)) : 
				    ISVREF(slot_description,(SI_Long)6L);
			}
			else
			    slot_value = ISVREF(slot_description,(SI_Long)6L);
		    }
		}
		if (SIMPLE_VECTOR_P(slot_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(slot_value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(slot_value,(SI_Long)1L);
		    gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && 
			    EQ(ISVREF(x2,(SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol_3 = Nil;
		if (gensymed_symbol_3 && ISVREF(gensymed_symbol_3,
			(SI_Long)16L)) {
		    gensymed_symbol_3 = 
			    SYMBOL_FUNCTION(Qcollect_attribute_if_savable);
		    gensymed_symbol_4 = slot_value;
		    inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4);
		}
	    }
	    goto next_loop_4;
	  end_loop_4:;
	    temp_3 = Attributes_collector;
	  POP_SPECIAL();
	POP_SPECIAL();
	sub_class_bit_vector = ISVREF(ISVREF(tree,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp = ISVREF(tree,(SI_Long)18L);
	    subworkspace_qm = CAR(temp);
	    temp = subworkspace_qm && ((SI_Long)0L != 
		    (IFIX(ISVREF(subworkspace_qm,(SI_Long)4L)) & 
		    (SI_Long)1L) || ISVREF(Current_saving_context,
		    (SI_Long)3L) && (SI_Long)0L != 
		    (IFIX(ISVREF(subworkspace_qm,(SI_Long)5L)) & 
		    (SI_Long)262144L)) ? journal_cons_1(subworkspace_qm,
		    Nil) : Nil;
	    gensymed_symbol_3 = ISVREF(tree,(SI_Long)1L);
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qimage_definition,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
		    temp_2 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		other_inferior_qm = 
			get_lookup_slot_value_given_default(tree,
			Qimage_definition_media_bin,Nil);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
		    temp_2 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    other_inferior_qm = get_lookup_slot_value(tree,
			    Qsimulation_details);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Generic_action_button_class_description,
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
			temp_2 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2)
			other_inferior_qm = ISVREF(tree,(SI_Long)22L);
		    else {
			gensymed_symbol_4 = 
				lookup_global_or_kb_specific_property_value(Qg2_java_bean,
				Class_description_gkbprop);
			if (gensymed_symbol_4) {
			    sub_class_bit_vector = 
				    ISVREF(gensymed_symbol_3,(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol_4,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp_2 = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp_2 = TRUEP(Nil);
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2)
			    other_inferior_qm = 
				    get_lookup_slot_value_given_default(tree,
				    Qg2_java_bean_media_bin,Nil);
			else {
			    sub_class_bit_vector = 
				    ISVREF(gensymed_symbol_3,(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(User_menu_choice_class_description,
				    (SI_Long)18L));
			    sub_class_vector_index = 
				    superior_class_bit_number >>  -  - 
				    (SI_Long)3L;
			    if (sub_class_vector_index < 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					{
				gensymed_symbol = 
					UBYTE_8_ISAREF_1(sub_class_bit_vector,
					sub_class_vector_index);
				gensymed_symbol_1 = (SI_Long)1L;
				gensymed_symbol_2 = 
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp_2 = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2)
				other_inferior_qm = ISVREF(tree,(SI_Long)24L);
			    else
				other_inferior_qm = Qnil;
			}
		    }
		}
	    }
	    temp = nconc2(temp,other_inferior_qm ? 
		    journal_cons_1(other_inferior_qm,Nil) : Nil);
	}
	else
	    temp = Nil;
	return VALUES_1(nconc2(temp_1,nconc2(temp_3,temp)));
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-ATTRIBUTE-IF-SAVABLE */
Object collect_attribute_if_savable(block)
    Object block;
{
    Object new_cons, cdr_arg, temp;

    x_note_fn_call(230,11);
    if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)1L) || 
	    ISVREF(Current_saving_context,(SI_Long)3L) && (SI_Long)0L != 
	    (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)262144L)) {
	if (has_slot_values_to_save_p(1,block)) {
	    new_cons = journal_cons_1(block,Nil);
	    if (Attributes_collector) {
		cdr_arg = Attributes_collector_tail;
		M_CDR(cdr_arg) = new_cons;
	    }
	    else
		Attributes_collector = new_cons;
	    Attributes_collector_tail = new_cons;
	    temp = Attributes_collector_tail;
	}
	else {
	    if (block_referenced_in_current_save_p(block) &&  
		    !TRUEP(block_written_in_current_save_p(block)))
		decrement_frame_reference_balance(block,
			Qcollect_attribute_if_savable);
	    temp = set_block_written_in_current_save(block,T);
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Kinferiors;          /* :inferiors */

static Object Ksuperior;           /* :superior */

/* ADD-AS-INFERIOR-BLOCK */
Object add_as_inferior_block(inferior,superior)
    Object inferior, superior;
{
    Object temp;

    x_note_fn_call(230,12);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(superior,Kinferiors);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(inferior,Ksuperior);
    temp =  !((SI_Long)0L != (IFIX(ISVREF(superior,(SI_Long)5L)) & 
	    (SI_Long)524288L)) ? add_as_inferior_block_1(inferior,
	    superior) : Nil;
    return VALUES_1(temp);
}

static Object Qpermanent;          /* permanent */

static Object Qtransient;          /* transient */

static Object Qneither_permanent_nor_transient;  /* neither-permanent-nor-transient */

/* PERMANENCE-OF-BLOCK-REPRESENTED */
Object permanence_of_block_represented(frame)
    Object frame;
{
    Object result_1, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object gensymed_symbol_5, ab_loop_list_, ab_loop_list__1;
    Object represented_frame;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(230,13);
    result_1 = Qpermanent;
    gensymed_symbol = frame;
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
		if ( !EQ(represented_frame,frame)) {
		    if ((SI_Long)0L != (IFIX(ISVREF(represented_frame,
			    (SI_Long)5L)) & (SI_Long)262144L))
			result_1 = Qtransient;
		    else if ( !((SI_Long)0L != 
			    (IFIX(ISVREF(represented_frame,(SI_Long)4L)) & 
			    (SI_Long)1L)))
			return VALUES_1(Qneither_permanent_nor_transient);
		}
	    }
	}
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(result_1);
}

static Object Qadd_as_inferior_block_1;  /* add-as-inferior-block-1 */

/* ADD-AS-INFERIOR-BLOCK-1 */
Object add_as_inferior_block_1(inferior,superior)
    Object inferior, superior;
{
    Object represented_block_permanence, temp;
    SI_Long svref_new_value;

    x_note_fn_call(230,14);
    if ( !((SI_Long)0L != (IFIX(ISVREF(inferior,(SI_Long)5L)) & 
	    (SI_Long)524288L))) {
	represented_block_permanence = 
		permanence_of_block_represented(inferior);
	if ((SI_Long)0L != (IFIX(ISVREF(superior,(SI_Long)5L)) & 
		(SI_Long)262144L)) {
	    if ( !EQ(represented_block_permanence,
		    Qneither_permanent_nor_transient)) {
		svref_new_value = IFIX(ISVREF(inferior,(SI_Long)5L)) | 
			(SI_Long)262144L;
		ISVREF(inferior,(SI_Long)5L) = FIX(svref_new_value);
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(inferior,Qframe_flags);
		svref_new_value = IFIX(ISVREF(inferior,(SI_Long)4L)) &  
			~(SI_Long)1L;
		ISVREF(inferior,(SI_Long)4L) = FIX(svref_new_value);
	    }
	}
	else if ( !((SI_Long)0L != (IFIX(ISVREF(inferior,(SI_Long)5L)) & 
		(SI_Long)262144L)) && (SI_Long)0L != (IFIX(ISVREF(superior,
		(SI_Long)4L)) & (SI_Long)1L)) {
	    if (EQ(represented_block_permanence,Qpermanent) || 
		    EQ(represented_block_permanence,Qnil)) {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(inferior,Qframe_flags);
		svref_new_value = IFIX(ISVREF(inferior,(SI_Long)4L)) | 
			(SI_Long)1L;
		ISVREF(inferior,(SI_Long)4L) = FIX(svref_new_value);
		if (Noting_changes_to_kb_p) {
		    svref_new_value = IFIX(ISVREF(inferior,(SI_Long)5L)) | 
			    (SI_Long)4L;
		    ISVREF(inferior,(SI_Long)5L) = FIX(svref_new_value);
		}
	    }
	    else if (EQ(represented_block_permanence,Qtransient)) {
		svref_new_value = IFIX(ISVREF(inferior,(SI_Long)5L)) | 
			(SI_Long)262144L;
		ISVREF(inferior,(SI_Long)5L) = FIX(svref_new_value);
	    }
	    else if (EQ(represented_block_permanence,
		    Qneither_permanent_nor_transient));
	}
	else if ( !((SI_Long)0L != (IFIX(ISVREF(superior,(SI_Long)5L)) & 
		(SI_Long)262144L)) &&  !((SI_Long)0L != 
		(IFIX(ISVREF(superior,(SI_Long)4L)) & (SI_Long)1L))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(inferior,Qframe_flags);
	    svref_new_value = IFIX(ISVREF(inferior,(SI_Long)4L)) &  
		    ~(SI_Long)1L;
	    ISVREF(inferior,(SI_Long)4L) = FIX(svref_new_value);
	    svref_new_value = IFIX(ISVREF(inferior,(SI_Long)5L)) &  
		    ~(SI_Long)262144L;
	    ISVREF(inferior,(SI_Long)5L) = FIX(svref_new_value);
	}
	temp = funcall_function_to_inferior_blocks(inferior,
		SYMBOL_FUNCTION(Qadd_as_inferior_block_1));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOVE-AS-INFERIOR-BLOCK */
Object remove_as_inferior_block(inferior,superior)
    Object inferior, superior;
{
    Object temp;

    x_note_fn_call(230,15);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(superior,Kinferiors);
    temp = remove_as_inferior_block_1(inferior,superior);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Remove_as_inferior_block_1, Qremove_as_inferior_block_1);

static Object Kmodule;             /* :module */

/* REMOVE-AS-INFERIOR-BLOCK-1 */
Object remove_as_inferior_block_1(inferior,superior)
    Object inferior, superior;
{
    Object temp;

    x_note_fn_call(230,16);
    funcall_function_to_inferior_blocks(inferior,Remove_as_inferior_block_1);
    temp = Noting_changes_to_kb_p ? note_change_to_block_1(inferior,
	    Kmodule) : Nil;
    return VALUES_1(temp);
}

/* REMOVE-BLOCK-FROM-MODULE */
Object remove_block_from_module(block)
    Object block;
{
    x_note_fn_call(230,17);
    if (Noting_changes_to_kb_p)
	return funcall_function_to_inferior_blocks(block,
		Remove_as_inferior_block_1);
    else
	return VALUES_1(Nil);
}

/* FUNCALL-FUNCTION-TO-INFERIOR-BLOCKS */
Object funcall_function_to_inferior_blocks(block,function)
    Object block, function;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object slot_description, class_description, ab_loop_list_;
    Object vector_slot_index_qm, slot_value, user_vector_slot_index_qm;
    Object slot_name, lookup_structure_qm, slot_index_qm, x2, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_skip_list_p_, ab_next_node_, ab_tail_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_connection_, ab_connection_item_, connection;
    Object temp, ab_less_than_branch_qm_, connection_frame_or_class;
    Object sub_class_bit_vector, subworkspace_qm, simulation_subtable_qm;
    Object embedded_rule_qm, gensymed_symbol_4, media_bin_qm;
    SI_Long max_i, i, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(230,18);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
    if ( !((SI_Long)0L != (IFIX(ISVREF(subblock,(SI_Long)5L)) & 
	    (SI_Long)524288L)))
	inline_funcall_2(function,subblock,block);
    goto next_loop;
  end_loop:;
    slot_description = Nil;
    class_description = ISVREF(block,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value = ISVREF(block,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value = ISVREF(ISVREF(block,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(block,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_2;
		  end_loop_2:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
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
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L))
	    inline_funcall_2(function,slot_value,block);
    }
    goto next_loop_1;
  end_loop_1:;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
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
    connection = Nil;
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
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)2L),block))
	  goto end_2;
      goto next_loop_4;
    end_loop_4:
    end_2:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_5;
      connection = ab_connection_;
      connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
      if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	      (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	      (SI_Long)1L),Qavailable_frame_vector)) {
	  x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		  Qg2_defstruct_structure_name_class_description_g2_struct) 
		  ? TRUEP(x2) : TRUEP(Qnil);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  inline_funcall_2(function,connection_frame_or_class,block);
      goto next_loop_3;
    end_loop_5:;
    POP_SPECIAL();
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
	    (SI_Long)18L));
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
	temp = ISVREF(block,(SI_Long)18L);
	subworkspace_qm = CAR(temp);
	if (subworkspace_qm)
	    inline_funcall_2(function,subworkspace_qm,block);
	gensymed_symbol = ISVREF(block,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	if (temp_1) {
	    simulation_subtable_qm = get_lookup_slot_value(block,
		    Qsimulation_details);
	    if (simulation_subtable_qm) {
		if (SIMPLE_VECTOR_P(simulation_subtable_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(simulation_subtable_qm)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(simulation_subtable_qm,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(simulation_subtable_qm,(SI_Long)1L);
		    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? x2 : Qnil;
		}
		else
		    gensymed_symbol = Nil;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Simulation_subtable_class_description,
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
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? inline_funcall_2(function,
		    simulation_subtable_qm,block) : Nil;
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_action_button_class_description,
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
	    if (temp_1) {
		embedded_rule_qm = ISVREF(block,(SI_Long)22L);
		temp = embedded_rule_qm ? inline_funcall_2(function,
			embedded_rule_qm,block) : Nil;
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(User_menu_choice_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    embedded_rule_qm = ISVREF(block,(SI_Long)24L);
		    temp = embedded_rule_qm ? inline_funcall_2(function,
			    embedded_rule_qm,block) : Nil;
		}
		else {
		    gensymed_symbol_4 = 
			    lookup_global_or_kb_specific_property_value(Qimage_definition,
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
			    temp_1 = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			media_bin_qm = 
				get_lookup_slot_value_given_default(block,
				Qimage_definition_media_bin,Nil);
			temp = media_bin_qm ? inline_funcall_2(function,
				media_bin_qm,block) : Nil;
		    }
		    else {
			gensymed_symbol_4 = 
				lookup_global_or_kb_specific_property_value(Qg2_java_bean,
				Class_description_gkbprop);
			if (gensymed_symbol_4) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(gensymed_symbol_4,
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
				temp_1 = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    media_bin_qm = 
				    get_lookup_slot_value_given_default(block,
				    Qg2_java_bean_media_bin,Nil);
			    temp = media_bin_qm ? 
				    inline_funcall_2(function,media_bin_qm,
				    block) : Nil;
			}
			else
			    temp = Qnil;
		    }
		}
	    }
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Blocks_with_specialized_method_qm, Qblocks_with_specialized_method_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Interesting_blocks_found_in_search, Qinteresting_blocks_found_in_search);

/* CHECK-FOR-SPECIALIZED-METHOD */
Object check_for_specialized_method(block,reference_method,method_name,
	    arg_count,add_instances_if_class_definition,include_connections_qm)
    Object block, reference_method, method_name, arg_count;
    Object add_instances_if_class_definition, include_connections_qm;
{
    Object class_description_qm, sub_class_bit_vector, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, an_item, slot_description;
    Object class_description, ab_loop_list_, slot_value_qm;
    Object vector_slot_index_qm, user_vector_slot_index_qm, slot_name;
    Object lookup_structure_qm, slot_index_qm, x2, gensymed_symbol_3;
    Object ab_queue_form_, ab_next_queue_element_, subblock, subworkspace;
    Object workspace_class_description_qm, ab_node_stack_, ab_current_node_;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, connection_frame_or_class, temp_1;
    Object ab_less_than_branch_qm_, other_inferior_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value, max_i, i;
    SI_Long ab_loop_bind_;
    char temp;
    Declare_special(1);

    x_note_fn_call(230,19);
    class_description_qm = Nil;
    if (add_instances_if_class_definition) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
    if (temp ?  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1048576L)) : TRUEP(Nil)) {
	svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | (SI_Long)1048576L;
	ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	Interesting_blocks_found_in_search = eval_cons_1(block,
		Interesting_blocks_found_in_search);
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(ISVREF(block,
		(SI_Long)20L),Class_description_gkbprop);
	if (class_description_qm) {
	    if ( !EQ(get_specific_method(method_name,class_description_qm,
		    arg_count,Nil,Nil,Nil),reference_method)) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		an_item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(ISVREF(block,(SI_Long)20L));
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
		  an_item = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  Blocks_with_specialized_method_qm = eval_cons_1(an_item,
			  Blocks_with_specialized_method_qm);
		  goto next_loop;
		end_loop_1:;
		POP_SPECIAL();
	    }
	    else {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		an_item = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(ISVREF(block,(SI_Long)20L));
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
		  an_item = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  check_for_specialized_method(an_item,reference_method,
			  method_name,arg_count,
			  add_instances_if_class_definition,
			  include_connections_qm);
		  goto next_loop_2;
		end_loop_3:;
		POP_SPECIAL();
	    }
	}
    }
    slot_description = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(block,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    slot_value_qm = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value_qm = ISVREF(block,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value_qm = ISVREF(ISVREF(block,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(block,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_5:
		    if (i >= ab_loop_bind_)
			goto end_loop_5;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_5;
		  end_loop_5:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value_qm = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value_qm = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if (SIMPLE_VECTOR_P(slot_value_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(slot_value_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(slot_value_qm,
		    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	    if (class_description_qm &&  
		    !EQ(get_specific_method(method_name,
		    class_description_qm,arg_count,Nil,Nil,Nil),
		    reference_method))
		Blocks_with_specialized_method_qm = 
			eval_cons_1(slot_value_qm,
			Blocks_with_specialized_method_qm);
	    else
		check_for_specialized_method(slot_value_qm,
			reference_method,method_name,arg_count,
			add_instances_if_class_definition,
			include_connections_qm);
	}
    }
    goto next_loop_4;
  end_loop_4:;
    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol_3 = gensymed_symbol_3 ? 
	    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol_3;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_6:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_6;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(subblock,
	    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
    if (class_description_qm) {
	if ( !EQ(get_specific_method(method_name,class_description_qm,
		arg_count,Nil,Nil,Nil),reference_method))
	    Blocks_with_specialized_method_qm = eval_cons_1(subblock,
		    Blocks_with_specialized_method_qm);
	else
	    check_for_specialized_method(subblock,reference_method,
		    method_name,arg_count,
		    add_instances_if_class_definition,include_connections_qm);
    }
    goto next_loop_6;
  end_loop_6:;
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	subworkspace = Nil;
	ab_loop_list_ = ISVREF(block,(SI_Long)18L);
	workspace_class_description_qm = Nil;
      next_loop_7:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_7;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	workspace_class_description_qm = 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(subworkspace,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	if (workspace_class_description_qm &&  
		!EQ(get_specific_method(method_name,
		workspace_class_description_qm,arg_count,Nil,Nil,Nil),
		reference_method))
	    Blocks_with_specialized_method_qm = eval_cons_1(subworkspace,
		    Blocks_with_specialized_method_qm);
	else {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(subworkspace,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol_3;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_8:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_8;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    class_description_qm = 
		    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(subblock,
		    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	    if (class_description_qm &&  
		    !EQ(get_specific_method(method_name,
		    class_description_qm,arg_count,Nil,Nil,Nil),
		    reference_method))
		Blocks_with_specialized_method_qm = eval_cons_1(subblock,
			Blocks_with_specialized_method_qm);
	    else
		check_for_specialized_method(subblock,reference_method,
			method_name,arg_count,
			add_instances_if_class_definition,
			include_connections_qm);
	    goto next_loop_8;
	  end_loop_8:;
	}
	goto next_loop_7;
      end_loop_7:;
    }
    if (include_connections_qm) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)6L)) : Nil;
	ab_skip_list_form_ = gensymed_symbol_3;
	ab_skip_list_p_ = Nil;
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_connection_ = Nil;
	ab_connection_item_ = Nil;
	connection = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  connection_frame_or_class = Nil;
	  gensymed_symbol_3 = CDR(ab_skip_list_form_);
	  if (CONSP(gensymed_symbol_3)) {
	      temp_1 = M_CAR(gensymed_symbol_3);
	      temp = SIMPLE_VECTOR_P(temp_1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      temp_1 = M_CDR(gensymed_symbol_3);
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
	next_loop_9:
	next_loop_10:
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
		next_loop_11:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_9;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_11;
		end_loop_9:;
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
	      goto end_2;
	  goto next_loop_10;
	end_loop_10:
	end_2:
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_11;
	  connection = ab_connection_;
	  connection_frame_or_class = SIMPLE_VECTOR_P(connection) && 
		  EQ(ISVREF(connection,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct) ? 
		  ISVREF(connection,(SI_Long)1L) : Nil;
	  if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		  > (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		  (SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ?  !((SI_Long)0L != 
		  (IFIX(ISVREF(connection_frame_or_class,(SI_Long)5L)) & 
		  (SI_Long)1048576L)) : TRUEP(Nil)) {
	      svref_new_value = IFIX(ISVREF(block,(SI_Long)5L)) | 
		      (SI_Long)1048576L;
	      ISVREF(block,(SI_Long)5L) = FIX(svref_new_value);
	      Interesting_blocks_found_in_search = eval_cons_1(block,
		      Interesting_blocks_found_in_search);
	      class_description_qm = 
		      lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(connection_frame_or_class,
		      (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	      if (class_description_qm &&  
		      !EQ(get_specific_method(method_name,
		      class_description_qm,arg_count,Nil,Nil,Nil),
		      reference_method))
		  Blocks_with_specialized_method_qm = 
			  eval_cons_1(connection_frame_or_class,
			  Blocks_with_specialized_method_qm);
	      else
		  check_for_specialized_method(connection_frame_or_class,
			  reference_method,method_name,arg_count,
			  add_instances_if_class_definition,Nil);
	  }
	  goto next_loop_9;
	end_loop_11:;
	POP_SPECIAL();
    }
    if (Nil) {
	gensymed_symbol_3 = ISVREF(block,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    other_inferior_qm = get_lookup_slot_value(block,
		    Qsimulation_details);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Generic_action_button_class_description,
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
		other_inferior_qm = ISVREF(block,(SI_Long)22L);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(User_menu_choice_class_description,
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
		    other_inferior_qm = ISVREF(block,(SI_Long)24L);
		else
		    other_inferior_qm = Qnil;
	    }
	}
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(other_inferior_qm,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	if (other_inferior_qm && class_description_qm) {
	    if ( !EQ(get_specific_method(method_name,class_description_qm,
		    arg_count,Nil,Nil,Nil),reference_method)) {
		Blocks_with_specialized_method_qm = 
			eval_cons_1(other_inferior_qm,
			Blocks_with_specialized_method_qm);
		return VALUES_1(Blocks_with_specialized_method_qm);
	    }
	    else
		return check_for_specialized_method(other_inferior_qm,
			reference_method,method_name,arg_count,
			add_instances_if_class_definition,
			include_connections_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

void traversals_INIT()
{
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qslot_group_for_block_qm, Qmodule_system_table_belongs_to_qm;
    Object Qthis_system_table_is_installed_qm, Qname_or_names_for_frame;
    Object list_constant_1, Qtop_level_kb_elements_for_saving;

    x_note_fn_call(230,20);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qtop_level_kb_elements_for_saving = 
	    STATIC_SYMBOL("TOP-LEVEL-KB-ELEMENTS-FOR-SAVING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtop_level_kb_elements_for_saving,
	    Top_level_kb_elements_for_saving);
    Ksystem_frames = STATIC_SYMBOL("SYSTEM-FRAMES",Pkeyword);
    Kdefinitions = STATIC_SYMBOL("DEFINITIONS",Pkeyword);
    Ktop_level_workspaces = STATIC_SYMBOL("TOP-LEVEL-WORKSPACES",Pkeyword);
    Ktransient_items_in_limbo = STATIC_SYMBOL("TRANSIENT-ITEMS-IN-LIMBO",
	    Pkeyword);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Ksystem_frames,Kdefinitions,
	    Ktop_level_workspaces,Ktransient_items_in_limbo);
    SET_SYMBOL_VALUE(Qtop_level_kb_elements_for_saving,list_constant_1);
    Kkb = STATIC_SYMBOL("KB",Pkeyword);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qthis_system_table_is_installed_qm = 
	    STATIC_SYMBOL("THIS-SYSTEM-TABLE-IS-INSTALLED\?",AB_package);
    Qmodule_system_table_belongs_to_qm = 
	    STATIC_SYMBOL("MODULE-SYSTEM-TABLE-BELONGS-TO\?",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qname_or_names_for_frame,
	    Qthis_system_table_is_installed_qm,
	    Qmodule_system_table_belongs_to_qm,Qslot_group_for_block_qm);
    if (Definitions_for_saving == UNBOUND)
	Definitions_for_saving = Nil;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qunits_of_measure_declaration = 
	    STATIC_SYMBOL("UNITS-OF-MEASURE-DECLARATION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qcollect_attribute_if_savable = 
	    STATIC_SYMBOL("COLLECT-ATTRIBUTE-IF-SAVABLE",AB_package);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qimage_definition_media_bin = 
	    STATIC_SYMBOL("IMAGE-DEFINITION-MEDIA-BIN",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qg2_java_bean = STATIC_SYMBOL("G2-JAVA-BEAN",AB_package);
    Qg2_java_bean_media_bin = STATIC_SYMBOL("G2-JAVA-BEAN-MEDIA-BIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcollect_attribute_if_savable,
	    STATIC_FUNCTION(collect_attribute_if_savable,NIL,FALSE,1,1));
    Kinferiors = STATIC_SYMBOL("INFERIORS",Pkeyword);
    Ksuperior = STATIC_SYMBOL("SUPERIOR",Pkeyword);
    Qpermanent = STATIC_SYMBOL("PERMANENT",AB_package);
    Qtransient = STATIC_SYMBOL("TRANSIENT",AB_package);
    Qneither_permanent_nor_transient = 
	    STATIC_SYMBOL("NEITHER-PERMANENT-NOR-TRANSIENT",AB_package);
    Qadd_as_inferior_block_1 = STATIC_SYMBOL("ADD-AS-INFERIOR-BLOCK-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_as_inferior_block_1,
	    STATIC_FUNCTION(add_as_inferior_block_1,NIL,FALSE,2,2));
    Kmodule = STATIC_SYMBOL("MODULE",Pkeyword);
    Qremove_as_inferior_block_1 = 
	    STATIC_SYMBOL("REMOVE-AS-INFERIOR-BLOCK-1",AB_package);
    SET_SYMBOL_FUNCTION(Qremove_as_inferior_block_1,
	    STATIC_FUNCTION(remove_as_inferior_block_1,NIL,FALSE,2,2));
    SET_SYMBOL_VALUE_LOCATION(Qremove_as_inferior_block_1,
	    Remove_as_inferior_block_1);
    Remove_as_inferior_block_1 = SYMBOL_FUNCTION(Qremove_as_inferior_block_1);
    if (Blocks_with_specialized_method_qm == UNBOUND)
	Blocks_with_specialized_method_qm = Nil;
    if (Interesting_blocks_found_in_search == UNBOUND)
	Interesting_blocks_found_in_search = Nil;
}
