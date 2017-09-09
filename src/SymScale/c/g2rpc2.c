/* g2rpc2.c
 * Input file:  g2-rpc2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "g2rpc2.h"


Object The_type_description_of_resumable_circular_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_circular_nodes, Qchain_of_available_resumable_circular_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_circular_node_count, Qresumable_circular_node_count);

Object Chain_of_available_resumable_circular_nodes_vector = UNBOUND;

/* RESUMABLE-CIRCULAR-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_circular_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,0);
    temp = Resumable_circular_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-CIRCULAR-NODE-COUNT */
Object outstanding_resumable_circular_node_count()
{
    Object def_structure_resumable_circular_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,1);
    gensymed_symbol = IFIX(Resumable_circular_node_count);
    def_structure_resumable_circular_node_variable = 
	    Chain_of_available_resumable_circular_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_circular_node_variable))
	goto end_loop;
    def_structure_resumable_circular_node_variable = 
	    ISVREF(def_structure_resumable_circular_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-CIRCULAR-NODE-1 */
Object reclaim_resumable_circular_node_1(resumable_circular_node)
    Object resumable_circular_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,2);
    inline_note_reclaim_cons(resumable_circular_node,Nil);
    structure_being_reclaimed = resumable_circular_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_circular_node,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_circular_node,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_circular_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_circular_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_circular_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_circular_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-CIRCULAR-NODE */
Object reclaim_structure_for_resumable_circular_node(resumable_circular_node)
    Object resumable_circular_node;
{
    x_note_fn_call(167,3);
    return reclaim_resumable_circular_node_1(resumable_circular_node);
}

static Object Qg2_defstruct_structure_name_resumable_circular_node_g2_struct;  /* g2-defstruct-structure-name::resumable-circular-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-CIRCULAR-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_circular_node_structure_internal()
{
    Object def_structure_resumable_circular_node_variable;
    Object defstruct_g2_resumable_circular_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,4);
    def_structure_resumable_circular_node_variable = Nil;
    atomic_incff_symval(Qresumable_circular_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_circular_node_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_resumable_circular_node_variable = the_array;
	SVREF(defstruct_g2_resumable_circular_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_circular_node_g2_struct;
	SVREF(defstruct_g2_resumable_circular_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_circular_node_variable,
		FIX((SI_Long)2L)) = Nil;
	def_structure_resumable_circular_node_variable = 
		defstruct_g2_resumable_circular_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_circular_node_variable);
}

/* MAKE-RESUMABLE-CIRCULAR-NODE-1 */
Object make_resumable_circular_node_1(resumable_attribute_spec_qm,
	    resumable_circular_corresponding_icp_index,
	    resumable_node_parent_node_qm)
    Object resumable_attribute_spec_qm;
    Object resumable_circular_corresponding_icp_index;
    Object resumable_node_parent_node_qm;
{
    Object def_structure_resumable_circular_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,5);
    def_structure_resumable_circular_node_variable = 
	    ISVREF(Chain_of_available_resumable_circular_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_circular_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_circular_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_circular_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_circular_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_circular_node_g2_struct;
    }
    else
	def_structure_resumable_circular_node_variable = 
		make_permanent_resumable_circular_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_circular_node_variable,
	    Nil);
    SVREF(def_structure_resumable_circular_node_variable,FIX((SI_Long)2L)) 
	    = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_circular_node_variable,FIX((SI_Long)3L)) 
	    = resumable_circular_corresponding_icp_index;
    SVREF(def_structure_resumable_circular_node_variable,FIX((SI_Long)1L)) 
	    = resumable_node_parent_node_qm;
    return VALUES_1(def_structure_resumable_circular_node_variable);
}

/* RECLAIM-EVALUATION-VALUE-IF-ANY-FUNCTION */
Object reclaim_evaluation_value_if_any_function(evaluation_value_qm)
    Object evaluation_value_qm;
{
    x_note_fn_call(167,6);
    if (evaluation_value_qm)
	reclaim_evaluation_value(evaluation_value_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_resumable_value_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_value_nodes, Qchain_of_available_resumable_value_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_value_node_count, Qresumable_value_node_count);

Object Chain_of_available_resumable_value_nodes_vector = UNBOUND;

/* RESUMABLE-VALUE-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_value_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,7);
    temp = Resumable_value_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-VALUE-NODE-COUNT */
Object outstanding_resumable_value_node_count()
{
    Object def_structure_resumable_value_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,8);
    gensymed_symbol = IFIX(Resumable_value_node_count);
    def_structure_resumable_value_node_variable = 
	    Chain_of_available_resumable_value_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_value_node_variable))
	goto end_loop;
    def_structure_resumable_value_node_variable = 
	    ISVREF(def_structure_resumable_value_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-VALUE-NODE-1 */
Object reclaim_resumable_value_node_1(resumable_value_node)
    Object resumable_value_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm;
    Object evaluation_value_qm, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,9);
    inline_note_reclaim_cons(resumable_value_node,Nil);
    structure_being_reclaimed = resumable_value_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_value_node,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_value_node,FIX((SI_Long)2L)) = Nil;
      evaluation_value_qm = ISVREF(resumable_value_node,(SI_Long)3L);
      if (evaluation_value_qm)
	  reclaim_evaluation_value(evaluation_value_qm);
      SVREF(resumable_value_node,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_value_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_value_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_value_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_value_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-VALUE-NODE */
Object reclaim_structure_for_resumable_value_node(resumable_value_node)
    Object resumable_value_node;
{
    x_note_fn_call(167,10);
    return reclaim_resumable_value_node_1(resumable_value_node);
}

static Object Qg2_defstruct_structure_name_resumable_value_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-VALUE-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_value_node_structure_internal()
{
    Object def_structure_resumable_value_node_variable;
    Object defstruct_g2_resumable_value_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,11);
    def_structure_resumable_value_node_variable = Nil;
    atomic_incff_symval(Qresumable_value_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_value_node_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_resumable_value_node_variable = the_array;
	SVREF(defstruct_g2_resumable_value_node_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_resumable_value_node_g2_struct;
	SVREF(defstruct_g2_resumable_value_node_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_resumable_value_node_variable,FIX((SI_Long)2L)) 
		= Nil;
	def_structure_resumable_value_node_variable = 
		defstruct_g2_resumable_value_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_value_node_variable);
}

/* MAKE-RESUMABLE-VALUE-NODE-1 */
Object make_resumable_value_node_1(resumable_attribute_spec_qm,
	    resumable_attribute_value,resumable_node_parent_node_qm)
    Object resumable_attribute_spec_qm, resumable_attribute_value;
    Object resumable_node_parent_node_qm;
{
    Object def_structure_resumable_value_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,12);
    def_structure_resumable_value_node_variable = 
	    ISVREF(Chain_of_available_resumable_value_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_value_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_value_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_value_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_value_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_value_node_g2_struct;
    }
    else
	def_structure_resumable_value_node_variable = 
		make_permanent_resumable_value_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_value_node_variable,Nil);
    SVREF(def_structure_resumable_value_node_variable,FIX((SI_Long)2L)) = 
	    resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_value_node_variable,FIX((SI_Long)3L)) = 
	    resumable_attribute_value;
    SVREF(def_structure_resumable_value_node_variable,FIX((SI_Long)1L)) = 
	    resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_value_node_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_resumable_value_node_variable);
}

Object The_type_description_of_resumable_instance_or_complex_value_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_instance_or_complex_value_node_mixins, Qchain_of_available_resumable_instance_or_complex_value_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_instance_or_complex_value_node_mixin_count, Qresumable_instance_or_complex_value_node_mixin_count);

Object Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector = UNBOUND;

/* RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_instance_or_complex_value_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,13);
    temp = Resumable_instance_or_complex_value_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-COUNT */
Object outstanding_resumable_instance_or_complex_value_node_mixin_count()
{
    Object def_structure_resumable_instance_or_complex_value_node_mixin_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,14);
    gensymed_symbol = 
	    IFIX(Resumable_instance_or_complex_value_node_mixin_count);
    def_structure_resumable_instance_or_complex_value_node_mixin_variable 
	    = 
	    Chain_of_available_resumable_instance_or_complex_value_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_resumable_instance_or_complex_value_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_instance_or_complex_value_node_mixin_variable 
	    = 
	    ISVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-1 */
Object reclaim_resumable_instance_or_complex_value_node_mixin_1(resumable_instance_or_complex_value_node_mixin)
    Object resumable_instance_or_complex_value_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,15);
    inline_note_reclaim_cons(resumable_instance_or_complex_value_node_mixin,
	    Nil);
    structure_being_reclaimed = resumable_instance_or_complex_value_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = 
	      ISVREF(resumable_instance_or_complex_value_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_instance_or_complex_value_node_mixin,
	      FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_instance_or_complex_value_node_mixin,
	      (SI_Long)3L));
      SVREF(resumable_instance_or_complex_value_node_mixin,
	      FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_instance_or_complex_value_node_mixin,
	      (SI_Long)9L));
      SVREF(resumable_instance_or_complex_value_node_mixin,
	      FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_instance_or_complex_value_node_mixin,FIX((SI_Long)0L)) 
	    = temp;
    temp = 
	    Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_instance_or_complex_value_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN */
Object reclaim_structure_for_resumable_instance_or_complex_value_node_mixin(resumable_instance_or_complex_value_node_mixin)
    Object resumable_instance_or_complex_value_node_mixin;
{
    x_note_fn_call(167,16);
    return reclaim_resumable_instance_or_complex_value_node_mixin_1(resumable_instance_or_complex_value_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-instance-or-complex-value-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_instance_or_complex_value_node_mixin_structure_internal()
{
    Object def_structure_resumable_instance_or_complex_value_node_mixin_variable;
    Object defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,17);
    def_structure_resumable_instance_or_complex_value_node_mixin_variable 
	    = Nil;
    atomic_incff_symval(Qresumable_instance_or_complex_value_node_mixin_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable 
		= Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable 
		= the_array;
	SVREF(defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	def_structure_resumable_instance_or_complex_value_node_mixin_variable 
		= 
		defstruct_g2_resumable_instance_or_complex_value_node_mixin_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_instance_or_complex_value_node_mixin_variable);
}

/* MAKE-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-1 */
Object make_resumable_instance_or_complex_value_node_mixin_1()
{
    Object def_structure_resumable_instance_or_complex_value_node_mixin_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(167,18);
    def_structure_resumable_instance_or_complex_value_node_mixin_variable 
	    = 
	    ISVREF(Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_instance_or_complex_value_node_mixin_variable) 
		{
	svref_arg_1 = 
		Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_instance_or_complex_value_node_mixin_variable 
		= 
		make_permanent_resumable_instance_or_complex_value_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_instance_or_complex_value_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_resumable_instance_or_complex_value_node_mixin_variable);
}

Object The_type_description_of_resumable_instance_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_instance_node_mixins, Qchain_of_available_resumable_instance_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_instance_node_mixin_count, Qresumable_instance_node_mixin_count);

Object Chain_of_available_resumable_instance_node_mixins_vector = UNBOUND;

/* RESUMABLE-INSTANCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_instance_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,19);
    temp = Resumable_instance_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)18L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-INSTANCE-NODE-MIXIN-COUNT */
Object outstanding_resumable_instance_node_mixin_count()
{
    Object def_structure_resumable_instance_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,20);
    gensymed_symbol = IFIX(Resumable_instance_node_mixin_count);
    def_structure_resumable_instance_node_mixin_variable = 
	    Chain_of_available_resumable_instance_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_instance_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_instance_node_mixin_variable = 
	    ISVREF(def_structure_resumable_instance_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-INSTANCE-NODE-MIXIN-1 */
Object reclaim_resumable_instance_node_mixin_1(resumable_instance_node_mixin)
    Object resumable_instance_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,21);
    inline_note_reclaim_cons(resumable_instance_node_mixin,Nil);
    structure_being_reclaimed = resumable_instance_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_instance_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_instance_node_mixin,(SI_Long)3L));
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_instance_node_mixin,(SI_Long)9L));
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_instance_node_mixin,
	      (SI_Long)10L));
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_instance_node_mixin,
	      (SI_Long)13L));
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_instance_node_mixin,
	      (SI_Long)16L));
      SVREF(resumable_instance_node_mixin,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_instance_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_instance_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_instance_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_instance_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-INSTANCE-NODE-MIXIN */
Object reclaim_structure_for_resumable_instance_node_mixin(resumable_instance_node_mixin)
    Object resumable_instance_node_mixin;
{
    x_note_fn_call(167,22);
    return reclaim_resumable_instance_node_mixin_1(resumable_instance_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-instance-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-INSTANCE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_instance_node_mixin_structure_internal()
{
    Object def_structure_resumable_instance_node_mixin_variable;
    Object defstruct_g2_resumable_instance_node_mixin_variable, the_array;
    Object temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,23);
    def_structure_resumable_instance_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_instance_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_instance_node_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)18L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_instance_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_instance_node_mixin_variable,
		FIX((SI_Long)9L)) = Nil;
	def_structure_resumable_instance_node_mixin_variable = 
		defstruct_g2_resumable_instance_node_mixin_variable;
	SVREF(def_structure_resumable_instance_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_instance_node_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_instance_node_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_instance_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_instance_node_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_instance_node_mixin_variable);
}

/* MAKE-RESUMABLE-INSTANCE-NODE-MIXIN-1 */
Object make_resumable_instance_node_mixin_1()
{
    Object def_structure_resumable_instance_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,24);
    def_structure_resumable_instance_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_instance_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_instance_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_instance_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_instance_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_instance_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_instance_node_mixin_variable = 
		make_permanent_resumable_instance_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_instance_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_instance_node_mixin_variable,
	    FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_resumable_instance_node_mixin_variable);
}

Object The_type_description_of_resumable_object_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_object_nodes, Qchain_of_available_resumable_object_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_object_node_count, Qresumable_object_node_count);

Object Chain_of_available_resumable_object_nodes_vector = UNBOUND;

/* RESUMABLE-OBJECT-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_object_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,25);
    temp = Resumable_object_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)18L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-OBJECT-NODE-COUNT */
Object outstanding_resumable_object_node_count()
{
    Object def_structure_resumable_object_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,26);
    gensymed_symbol = IFIX(Resumable_object_node_count);
    def_structure_resumable_object_node_variable = 
	    Chain_of_available_resumable_object_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_object_node_variable))
	goto end_loop;
    def_structure_resumable_object_node_variable = 
	    ISVREF(def_structure_resumable_object_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-OBJECT-NODE-1 */
Object reclaim_resumable_object_node_1(resumable_object_node)
    Object resumable_object_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,27);
    inline_note_reclaim_cons(resumable_object_node,Nil);
    structure_being_reclaimed = resumable_object_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_object_node,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_object_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_object_node,(SI_Long)3L));
      SVREF(resumable_object_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_object_node,(SI_Long)9L));
      SVREF(resumable_object_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_object_node,(SI_Long)10L));
      SVREF(resumable_object_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_object_node,(SI_Long)13L));
      SVREF(resumable_object_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_object_node,
	      (SI_Long)16L));
      SVREF(resumable_object_node,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_object_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_object_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_object_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_object_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-OBJECT-NODE */
Object reclaim_structure_for_resumable_object_node(resumable_object_node)
    Object resumable_object_node;
{
    x_note_fn_call(167,28);
    return reclaim_resumable_object_node_1(resumable_object_node);
}

static Object Qg2_defstruct_structure_name_resumable_object_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-OBJECT-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_object_node_structure_internal()
{
    Object def_structure_resumable_object_node_variable;
    Object defstruct_g2_resumable_object_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,29);
    def_structure_resumable_object_node_variable = Nil;
    atomic_incff_symval(Qresumable_object_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_object_node_variable = Nil;
	gensymed_symbol = (SI_Long)18L;
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
	defstruct_g2_resumable_object_node_variable = the_array;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_node_g2_struct;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_object_node_variable,
		FIX((SI_Long)17L)) = Nil;
	def_structure_resumable_object_node_variable = 
		defstruct_g2_resumable_object_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_object_node_variable);
}

/* MAKE-RESUMABLE-OBJECT-NODE-1 */
Object make_resumable_object_node_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_object_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,30);
    def_structure_resumable_object_node_variable = 
	    ISVREF(Chain_of_available_resumable_object_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_object_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_object_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_object_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_object_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_node_g2_struct;
    }
    else
	def_structure_resumable_object_node_variable = 
		make_permanent_resumable_object_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_object_node_variable,
	    Nil);
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)4L)) = 
	    resumable_instance_current_object;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)10L)) 
	    = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)16L)) 
	    = current_attribute_names;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)17L)) 
	    = symbolic_attribute_count;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)2L)) = 
	    resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)11L)) 
	    = resumable_instance_class_name;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)1L)) = 
	    resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)12L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)13L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)14L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_node_variable,FIX((SI_Long)15L)) 
	    = Nil;
    return VALUES_1(def_structure_resumable_object_node_variable);
}

Object The_type_description_of_resumable_sequence_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_sequence_node_mixins, Qchain_of_available_resumable_sequence_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_sequence_node_mixin_count, Qresumable_sequence_node_mixin_count);

Object Chain_of_available_resumable_sequence_node_mixins_vector = UNBOUND;

/* RESUMABLE-SEQUENCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_sequence_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,31);
    temp = Resumable_sequence_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)20L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-SEQUENCE-NODE-MIXIN-COUNT */
Object outstanding_resumable_sequence_node_mixin_count()
{
    Object def_structure_resumable_sequence_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,32);
    gensymed_symbol = IFIX(Resumable_sequence_node_mixin_count);
    def_structure_resumable_sequence_node_mixin_variable = 
	    Chain_of_available_resumable_sequence_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_sequence_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_sequence_node_mixin_variable = 
	    ISVREF(def_structure_resumable_sequence_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-SEQUENCE-NODE-MIXIN-1 */
Object reclaim_resumable_sequence_node_mixin_1(resumable_sequence_node_mixin)
    Object resumable_sequence_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,33);
    inline_note_reclaim_cons(resumable_sequence_node_mixin,Nil);
    structure_being_reclaimed = resumable_sequence_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_sequence_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_sequence_node_mixin,(SI_Long)3L));
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_sequence_node_mixin,(SI_Long)9L));
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_sequence_node_mixin,
	      (SI_Long)10L));
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_sequence_node_mixin,
	      (SI_Long)13L));
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_sequence_node_mixin,
	      (SI_Long)16L));
      SVREF(resumable_sequence_node_mixin,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_sequence_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_sequence_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_sequence_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_sequence_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-SEQUENCE-NODE-MIXIN */
Object reclaim_structure_for_resumable_sequence_node_mixin(resumable_sequence_node_mixin)
    Object resumable_sequence_node_mixin;
{
    x_note_fn_call(167,34);
    return reclaim_resumable_sequence_node_mixin_1(resumable_sequence_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-sequence-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-SEQUENCE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_sequence_node_mixin_structure_internal()
{
    Object def_structure_resumable_sequence_node_mixin_variable;
    Object defstruct_g2_resumable_sequence_node_mixin_variable, the_array;
    Object temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,35);
    def_structure_resumable_sequence_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_sequence_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_sequence_node_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)20L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_sequence_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	def_structure_resumable_sequence_node_mixin_variable = 
		defstruct_g2_resumable_sequence_node_mixin_variable;
	SVREF(def_structure_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_sequence_node_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_sequence_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_sequence_node_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_sequence_node_mixin_variable);
}

/* MAKE-RESUMABLE-SEQUENCE-NODE-MIXIN-1 */
Object make_resumable_sequence_node_mixin_1()
{
    Object def_structure_resumable_sequence_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,36);
    def_structure_resumable_sequence_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_sequence_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_sequence_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_sequence_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_sequence_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_sequence_node_mixin_variable = 
		make_permanent_resumable_sequence_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_sequence_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_resumable_sequence_node_mixin_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_resumable_sequence_node_mixin_variable);
}

Object The_type_description_of_resumable_vector_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_vector_node_mixins, Qchain_of_available_resumable_vector_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_vector_node_mixin_count, Qresumable_vector_node_mixin_count);

Object Chain_of_available_resumable_vector_node_mixins_vector = UNBOUND;

/* RESUMABLE-VECTOR-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_vector_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,37);
    temp = Resumable_vector_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-VECTOR-NODE-MIXIN-COUNT */
Object outstanding_resumable_vector_node_mixin_count()
{
    Object def_structure_resumable_vector_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,38);
    gensymed_symbol = IFIX(Resumable_vector_node_mixin_count);
    def_structure_resumable_vector_node_mixin_variable = 
	    Chain_of_available_resumable_vector_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_vector_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_vector_node_mixin_variable = 
	    ISVREF(def_structure_resumable_vector_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-VECTOR-NODE-MIXIN-1 */
Object reclaim_resumable_vector_node_mixin_1(resumable_vector_node_mixin)
    Object resumable_vector_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,39);
    inline_note_reclaim_cons(resumable_vector_node_mixin,Nil);
    structure_being_reclaimed = resumable_vector_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_vector_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_vector_node_mixin,(SI_Long)3L));
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_vector_node_mixin,(SI_Long)9L));
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_vector_node_mixin,
	      (SI_Long)10L));
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_vector_node_mixin,
	      (SI_Long)13L));
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_vector_node_mixin,
	      (SI_Long)16L));
      SVREF(resumable_vector_node_mixin,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_vector_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_vector_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_vector_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_vector_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-VECTOR-NODE-MIXIN */
Object reclaim_structure_for_resumable_vector_node_mixin(resumable_vector_node_mixin)
    Object resumable_vector_node_mixin;
{
    x_note_fn_call(167,40);
    return reclaim_resumable_vector_node_mixin_1(resumable_vector_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-vector-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-VECTOR-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_vector_node_mixin_structure_internal()
{
    Object def_structure_resumable_vector_node_mixin_variable;
    Object defstruct_g2_resumable_vector_node_mixin_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,41);
    def_structure_resumable_vector_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_vector_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_vector_node_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)21L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_vector_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_vector_node_mixin_variable,
		FIX((SI_Long)19L)) = Nil;
	def_structure_resumable_vector_node_mixin_variable = 
		defstruct_g2_resumable_vector_node_mixin_variable;
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)18L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_vector_node_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_vector_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_vector_node_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_vector_node_mixin_variable);
}

/* MAKE-RESUMABLE-VECTOR-NODE-MIXIN-1 */
Object make_resumable_vector_node_mixin_1()
{
    Object def_structure_resumable_vector_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,42);
    def_structure_resumable_vector_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_vector_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_vector_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_vector_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_vector_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_vector_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_vector_node_mixin_variable = 
		make_permanent_resumable_vector_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_vector_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_resumable_vector_node_mixin_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_resumable_vector_node_mixin_variable);
}

Object The_type_description_of_resumable_object_vector_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_object_vector_nodes, Qchain_of_available_resumable_object_vector_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_object_vector_node_count, Qresumable_object_vector_node_count);

Object Chain_of_available_resumable_object_vector_nodes_vector = UNBOUND;

/* RESUMABLE-OBJECT-VECTOR-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_object_vector_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,43);
    temp = Resumable_object_vector_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)23L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-OBJECT-VECTOR-NODE-COUNT */
Object outstanding_resumable_object_vector_node_count()
{
    Object def_structure_resumable_object_vector_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,44);
    gensymed_symbol = IFIX(Resumable_object_vector_node_count);
    def_structure_resumable_object_vector_node_variable = 
	    Chain_of_available_resumable_object_vector_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_object_vector_node_variable))
	goto end_loop;
    def_structure_resumable_object_vector_node_variable = 
	    ISVREF(def_structure_resumable_object_vector_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-OBJECT-VECTOR-NODE-1 */
Object reclaim_resumable_object_vector_node_1(resumable_object_vector_node)
    Object resumable_object_vector_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,45);
    inline_note_reclaim_cons(resumable_object_vector_node,Nil);
    structure_being_reclaimed = resumable_object_vector_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_object_vector_node,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_object_vector_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_object_vector_node,(SI_Long)3L));
      SVREF(resumable_object_vector_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_object_vector_node,(SI_Long)9L));
      SVREF(resumable_object_vector_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_object_vector_node,
	      (SI_Long)10L));
      SVREF(resumable_object_vector_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_object_vector_node,
	      (SI_Long)13L));
      SVREF(resumable_object_vector_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_object_vector_node,
	      (SI_Long)16L));
      SVREF(resumable_object_vector_node,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_object_vector_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_object_vector_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_object_vector_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_object_vector_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-OBJECT-VECTOR-NODE */
Object reclaim_structure_for_resumable_object_vector_node(resumable_object_vector_node)
    Object resumable_object_vector_node;
{
    x_note_fn_call(167,46);
    return reclaim_resumable_object_vector_node_1(resumable_object_vector_node);
}

static Object Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-vector-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-OBJECT-VECTOR-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_object_vector_node_structure_internal()
{
    Object def_structure_resumable_object_vector_node_variable;
    Object defstruct_g2_resumable_object_vector_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,47);
    def_structure_resumable_object_vector_node_variable = Nil;
    atomic_incff_symval(Qresumable_object_vector_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_object_vector_node_variable = Nil;
	gensymed_symbol = (SI_Long)23L;
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
	defstruct_g2_resumable_object_vector_node_variable = the_array;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_resumable_object_vector_node_variable,
		FIX((SI_Long)20L)) = Nil;
	def_structure_resumable_object_vector_node_variable = 
		defstruct_g2_resumable_object_vector_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_object_vector_node_variable);
}

/* MAKE-RESUMABLE-OBJECT-VECTOR-NODE-INTERNAL-1 */
Object make_resumable_object_vector_node_internal_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    resumable_sequence_length,internal_vector_for_object_passing,
	    resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_sequence_length;
    Object internal_vector_for_object_passing, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_object_vector_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,48);
    def_structure_resumable_object_vector_node_variable = 
	    ISVREF(Chain_of_available_resumable_object_vector_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_object_vector_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_object_vector_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_object_vector_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_object_vector_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct;
    }
    else
	def_structure_resumable_object_vector_node_variable = 
		make_permanent_resumable_object_vector_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_object_vector_node_variable,
	    Nil);
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)10L)) = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)16L)) = current_attribute_names;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)17L)) = symbolic_attribute_count;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)2L)) = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)11L)) = resumable_instance_class_name;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)18L)) = resumable_sequence_length;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)20L)) = internal_vector_for_object_passing;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_object_vector_node_variable,
	    FIX((SI_Long)19L)) = Nil;
    ISVREF(def_structure_resumable_object_vector_node_variable,
	    (SI_Long)21L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_resumable_object_vector_node_variable);
}

Object The_type_description_of_resumable_value_vector_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_value_vector_nodes, Qchain_of_available_resumable_value_vector_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_value_vector_node_count, Qresumable_value_vector_node_count);

Object Chain_of_available_resumable_value_vector_nodes_vector = UNBOUND;

/* RESUMABLE-VALUE-VECTOR-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_value_vector_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,49);
    temp = Resumable_value_vector_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)22L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-VALUE-VECTOR-NODE-COUNT */
Object outstanding_resumable_value_vector_node_count()
{
    Object def_structure_resumable_value_vector_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,50);
    gensymed_symbol = IFIX(Resumable_value_vector_node_count);
    def_structure_resumable_value_vector_node_variable = 
	    Chain_of_available_resumable_value_vector_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_value_vector_node_variable))
	goto end_loop;
    def_structure_resumable_value_vector_node_variable = 
	    ISVREF(def_structure_resumable_value_vector_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-VALUE-VECTOR-NODE-1 */
Object reclaim_resumable_value_vector_node_1(resumable_value_vector_node)
    Object resumable_value_vector_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,51);
    inline_note_reclaim_cons(resumable_value_vector_node,Nil);
    structure_being_reclaimed = resumable_value_vector_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_value_vector_node,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_value_vector_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_value_vector_node,(SI_Long)3L));
      SVREF(resumable_value_vector_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_value_vector_node,(SI_Long)9L));
      SVREF(resumable_value_vector_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_value_vector_node,
	      (SI_Long)10L));
      SVREF(resumable_value_vector_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_value_vector_node,
	      (SI_Long)13L));
      SVREF(resumable_value_vector_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_value_vector_node,
	      (SI_Long)16L));
      SVREF(resumable_value_vector_node,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_value_vector_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_value_vector_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_value_vector_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_value_vector_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-VALUE-VECTOR-NODE */
Object reclaim_structure_for_resumable_value_vector_node(resumable_value_vector_node)
    Object resumable_value_vector_node;
{
    x_note_fn_call(167,52);
    return reclaim_resumable_value_vector_node_1(resumable_value_vector_node);
}

static Object Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-vector-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-VALUE-VECTOR-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_value_vector_node_structure_internal()
{
    Object def_structure_resumable_value_vector_node_variable;
    Object defstruct_g2_resumable_value_vector_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,53);
    def_structure_resumable_value_vector_node_variable = Nil;
    atomic_incff_symval(Qresumable_value_vector_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_value_vector_node_variable = Nil;
	gensymed_symbol = (SI_Long)22L;
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
	defstruct_g2_resumable_value_vector_node_variable = the_array;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_resumable_value_vector_node_variable,
		FIX((SI_Long)20L)) = Nil;
	def_structure_resumable_value_vector_node_variable = 
		defstruct_g2_resumable_value_vector_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_value_vector_node_variable);
}

/* MAKE-RESUMABLE-VALUE-VECTOR-NODE-INTERNAL-1 */
Object make_resumable_value_vector_node_internal_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    resumable_sequence_length,internal_vector_for_object_passing,
	    resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_sequence_length;
    Object internal_vector_for_object_passing, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_value_vector_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,54);
    def_structure_resumable_value_vector_node_variable = 
	    ISVREF(Chain_of_available_resumable_value_vector_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_value_vector_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_value_vector_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_value_vector_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_value_vector_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct;
    }
    else
	def_structure_resumable_value_vector_node_variable = 
		make_permanent_resumable_value_vector_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_value_vector_node_variable,
	    Nil);
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)10L)) = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)16L)) = current_attribute_names;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)17L)) = symbolic_attribute_count;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)2L)) = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)11L)) = resumable_instance_class_name;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)18L)) = resumable_sequence_length;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)20L)) = internal_vector_for_object_passing;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_value_vector_node_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_resumable_value_vector_node_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Size_of_cached_subsequence_for_resumable_history, Qsize_of_cached_subsequence_for_resumable_history);

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* RECLAIM-CACHED-HISTORY-SUBSEQUENCE */
Object reclaim_cached_history_subsequence(history_subsequence)
    Object history_subsequence;
{
    Object element_qm, gensymed_symbol, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_1, temp_2, entry_hash;
    SI_Long index_1, ab_loop_bind_, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind__1;
    char temp;
    Object result;

    x_note_fn_call(167,55);
    if (SIMPLE_VECTOR_P(history_subsequence) && 
	    EQ(ISVREF(history_subsequence,(SI_Long)0L),
	    Managed_float_array_unique_marker))
	reclaim_managed_float_array(history_subsequence);
    else if (SIMPLE_VECTOR_P(history_subsequence)) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(history_subsequence));
	element_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	element_qm = ISVREF(history_subsequence,index_1);
	gensymed_symbol = element_qm;
	temp = FIXNUMP(gensymed_symbol);
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp);
	else
	    temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value);
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state);
	    if (temp);
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
		ab_loop_bind__1 = bottom_level;
	      next_loop_1:
		if (level < ab_loop_bind__1)
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_3;
	      end_loop_2:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    goto end_loop;
	reclaim_evaluation_value(element_qm);
	ISVREF(history_subsequence,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reclaim_managed_simple_vector(history_subsequence);
    }
    else if ( !TRUEP(history_subsequence));
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-LIST-OF-EVALUATION-VALUES? */
Object reclaim_icp_list_of_evaluation_values_qm(icp_list)
    Object icp_list;
{
    Object element_qm, ab_loop_list_;

    x_note_fn_call(167,56);
    element_qm = Nil;
    ab_loop_list_ = icp_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element_qm = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (element_qm)
	reclaim_evaluation_value(element_qm);
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(icp_list);
    return VALUES_1(Nil);
}

Object The_type_description_of_resumable_history_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_history_nodes, Qchain_of_available_resumable_history_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_history_node_count, Qresumable_history_node_count);

Object Chain_of_available_resumable_history_nodes_vector = UNBOUND;

/* RESUMABLE-HISTORY-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_history_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,57);
    temp = Resumable_history_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)31L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-HISTORY-NODE-COUNT */
Object outstanding_resumable_history_node_count()
{
    Object def_structure_resumable_history_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,58);
    gensymed_symbol = IFIX(Resumable_history_node_count);
    def_structure_resumable_history_node_variable = 
	    Chain_of_available_resumable_history_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_history_node_variable))
	goto end_loop;
    def_structure_resumable_history_node_variable = 
	    ISVREF(def_structure_resumable_history_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-HISTORY-NODE-1 */
Object reclaim_resumable_history_node_1(resumable_history_node)
    Object resumable_history_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,59);
    inline_note_reclaim_cons(resumable_history_node,Nil);
    structure_being_reclaimed = resumable_history_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_history_node,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_history_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_history_node,(SI_Long)3L));
      SVREF(resumable_history_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_history_node,(SI_Long)9L));
      SVREF(resumable_history_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_history_node,(SI_Long)10L));
      SVREF(resumable_history_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_history_node,(SI_Long)13L));
      SVREF(resumable_history_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_history_node,
	      (SI_Long)16L));
      SVREF(resumable_history_node,FIX((SI_Long)16L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_history_node,(SI_Long)21L));
      SVREF(resumable_history_node,FIX((SI_Long)21L)) = Nil;
      reclaim_icp_list_of_evaluation_values_qm(ISVREF(resumable_history_node,
	      (SI_Long)22L));
      SVREF(resumable_history_node,FIX((SI_Long)22L)) = Nil;
      reclaim_cached_history_subsequence(ISVREF(resumable_history_node,
	      (SI_Long)29L));
      SVREF(resumable_history_node,FIX((SI_Long)29L)) = Nil;
      reclaim_cached_history_subsequence(ISVREF(resumable_history_node,
	      (SI_Long)30L));
      SVREF(resumable_history_node,FIX((SI_Long)30L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_history_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_history_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_history_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_history_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-HISTORY-NODE */
Object reclaim_structure_for_resumable_history_node(resumable_history_node)
    Object resumable_history_node;
{
    x_note_fn_call(167,60);
    return reclaim_resumable_history_node_1(resumable_history_node);
}

static Object Qg2_defstruct_structure_name_resumable_history_node_g2_struct;  /* g2-defstruct-structure-name::resumable-history-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-HISTORY-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_history_node_structure_internal()
{
    Object def_structure_resumable_history_node_variable;
    Object defstruct_g2_resumable_history_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,61);
    def_structure_resumable_history_node_variable = Nil;
    atomic_incff_symval(Qresumable_history_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_history_node_variable = Nil;
	gensymed_symbol = (SI_Long)31L;
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
	defstruct_g2_resumable_history_node_variable = the_array;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_history_node_g2_struct;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_history_node_variable,
		FIX((SI_Long)19L)) = Nil;
	def_structure_resumable_history_node_variable = 
		defstruct_g2_resumable_history_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_history_node_variable);
}

/* MAKE-RESUMABLE-HISTORY-NODE-1 */
Object make_resumable_history_node_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    resumable_sequence_length,resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_sequence_length;
    Object resumable_node_parent_node_qm;
{
    Object def_structure_resumable_history_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,62);
    def_structure_resumable_history_node_variable = 
	    ISVREF(Chain_of_available_resumable_history_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_history_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_history_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_history_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_history_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_history_node_g2_struct;
    }
    else
	def_structure_resumable_history_node_variable = 
		make_permanent_resumable_history_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_history_node_variable,
	    Nil);
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)4L)) 
	    = resumable_instance_current_object;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)10L)) 
	    = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)16L)) 
	    = current_attribute_names;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)17L)) 
	    = symbolic_attribute_count;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)2L)) 
	    = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)11L)) 
	    = resumable_instance_class_name;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)18L)) 
	    = resumable_sequence_length;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)1L)) 
	    = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)3L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)5L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)6L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)7L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)9L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)12L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)13L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)14L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)15L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)19L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)21L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)22L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)24L)) 
	    = Nil;
    ISVREF(def_structure_resumable_history_node_variable,(SI_Long)25L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)26L)) 
	    = Nil;
    ISVREF(def_structure_resumable_history_node_variable,(SI_Long)27L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)28L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)29L)) 
	    = Nil;
    SVREF(def_structure_resumable_history_node_variable,FIX((SI_Long)30L)) 
	    = Nil;
    return VALUES_1(def_structure_resumable_history_node_variable);
}

Object The_type_description_of_resumable_list_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_list_node_mixins, Qchain_of_available_resumable_list_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_list_node_mixin_count, Qresumable_list_node_mixin_count);

Object Chain_of_available_resumable_list_node_mixins_vector = UNBOUND;

/* RESUMABLE-LIST-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_list_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,63);
    temp = Resumable_list_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-LIST-NODE-MIXIN-COUNT */
Object outstanding_resumable_list_node_mixin_count()
{
    Object def_structure_resumable_list_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,64);
    gensymed_symbol = IFIX(Resumable_list_node_mixin_count);
    def_structure_resumable_list_node_mixin_variable = 
	    Chain_of_available_resumable_list_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_list_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_list_node_mixin_variable = 
	    ISVREF(def_structure_resumable_list_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-LIST-NODE-MIXIN-1 */
Object reclaim_resumable_list_node_mixin_1(resumable_list_node_mixin)
    Object resumable_list_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,65);
    inline_note_reclaim_cons(resumable_list_node_mixin,Nil);
    structure_being_reclaimed = resumable_list_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_list_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_list_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_list_node_mixin,(SI_Long)3L));
      SVREF(resumable_list_node_mixin,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_list_node_mixin,(SI_Long)9L));
      SVREF(resumable_list_node_mixin,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_list_node_mixin,
	      (SI_Long)10L));
      SVREF(resumable_list_node_mixin,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_list_node_mixin,
	      (SI_Long)13L));
      SVREF(resumable_list_node_mixin,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_list_node_mixin,
	      (SI_Long)16L));
      SVREF(resumable_list_node_mixin,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_list_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_list_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_list_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_list_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-LIST-NODE-MIXIN */
Object reclaim_structure_for_resumable_list_node_mixin(resumable_list_node_mixin)
    Object resumable_list_node_mixin;
{
    x_note_fn_call(167,66);
    return reclaim_resumable_list_node_mixin_1(resumable_list_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-list-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-LIST-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_list_node_mixin_structure_internal()
{
    Object def_structure_resumable_list_node_mixin_variable;
    Object defstruct_g2_resumable_list_node_mixin_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,67);
    def_structure_resumable_list_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_list_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_list_node_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)21L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_list_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_list_node_mixin_variable,
		FIX((SI_Long)19L)) = Nil;
	def_structure_resumable_list_node_mixin_variable = 
		defstruct_g2_resumable_list_node_mixin_variable;
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)18L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_resumable_list_node_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_list_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_list_node_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_list_node_mixin_variable);
}

/* MAKE-RESUMABLE-LIST-NODE-MIXIN-1 */
Object make_resumable_list_node_mixin_1()
{
    Object def_structure_resumable_list_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,68);
    def_structure_resumable_list_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_list_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_list_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_list_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_list_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_list_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_list_node_mixin_variable = 
		make_permanent_resumable_list_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_list_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_resumable_list_node_mixin_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_resumable_list_node_mixin_variable);
}

Object The_type_description_of_resumable_object_list_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_object_list_nodes, Qchain_of_available_resumable_object_list_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_object_list_node_count, Qresumable_object_list_node_count);

Object Chain_of_available_resumable_object_list_nodes_vector = UNBOUND;

/* RESUMABLE-OBJECT-LIST-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_object_list_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,69);
    temp = Resumable_object_list_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-OBJECT-LIST-NODE-COUNT */
Object outstanding_resumable_object_list_node_count()
{
    Object def_structure_resumable_object_list_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,70);
    gensymed_symbol = IFIX(Resumable_object_list_node_count);
    def_structure_resumable_object_list_node_variable = 
	    Chain_of_available_resumable_object_list_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_object_list_node_variable))
	goto end_loop;
    def_structure_resumable_object_list_node_variable = 
	    ISVREF(def_structure_resumable_object_list_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-OBJECT-LIST-NODE-1 */
Object reclaim_resumable_object_list_node_1(resumable_object_list_node)
    Object resumable_object_list_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,71);
    inline_note_reclaim_cons(resumable_object_list_node,Nil);
    structure_being_reclaimed = resumable_object_list_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_object_list_node,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_object_list_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_object_list_node,(SI_Long)3L));
      SVREF(resumable_object_list_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_object_list_node,(SI_Long)9L));
      SVREF(resumable_object_list_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_object_list_node,
	      (SI_Long)10L));
      SVREF(resumable_object_list_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_object_list_node,
	      (SI_Long)13L));
      SVREF(resumable_object_list_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_object_list_node,
	      (SI_Long)16L));
      SVREF(resumable_object_list_node,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_object_list_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_object_list_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_object_list_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_object_list_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-OBJECT-LIST-NODE */
Object reclaim_structure_for_resumable_object_list_node(resumable_object_list_node)
    Object resumable_object_list_node;
{
    x_note_fn_call(167,72);
    return reclaim_resumable_object_list_node_1(resumable_object_list_node);
}

static Object Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct;  /* g2-defstruct-structure-name::resumable-object-list-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-OBJECT-LIST-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_object_list_node_structure_internal()
{
    Object def_structure_resumable_object_list_node_variable;
    Object defstruct_g2_resumable_object_list_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,73);
    def_structure_resumable_object_list_node_variable = Nil;
    atomic_incff_symval(Qresumable_object_list_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_object_list_node_variable = Nil;
	gensymed_symbol = (SI_Long)21L;
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
	defstruct_g2_resumable_object_list_node_variable = the_array;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_resumable_object_list_node_variable,
		FIX((SI_Long)20L)) = Nil;
	def_structure_resumable_object_list_node_variable = 
		defstruct_g2_resumable_object_list_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_object_list_node_variable);
}

/* MAKE-RESUMABLE-OBJECT-LIST-NODE-1 */
Object make_resumable_object_list_node_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    internal_list_for_object_passing,resumable_sequence_length,
	    resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, internal_list_for_object_passing;
    Object resumable_sequence_length, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_object_list_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,74);
    def_structure_resumable_object_list_node_variable = 
	    ISVREF(Chain_of_available_resumable_object_list_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_object_list_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_object_list_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_object_list_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_object_list_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct;
    }
    else
	def_structure_resumable_object_list_node_variable = 
		make_permanent_resumable_object_list_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_object_list_node_variable,
	    Nil);
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)10L)) = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)16L)) = current_attribute_names;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)17L)) = symbolic_attribute_count;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)2L)) = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)11L)) = resumable_instance_class_name;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)20L)) = internal_list_for_object_passing;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)18L)) = resumable_sequence_length;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_object_list_node_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_resumable_object_list_node_variable);
}

Object The_type_description_of_resumable_value_list_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_value_list_nodes, Qchain_of_available_resumable_value_list_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_value_list_node_count, Qresumable_value_list_node_count);

Object Chain_of_available_resumable_value_list_nodes_vector = UNBOUND;

/* RESUMABLE-VALUE-LIST-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_value_list_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,75);
    temp = Resumable_value_list_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)22L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-VALUE-LIST-NODE-COUNT */
Object outstanding_resumable_value_list_node_count()
{
    Object def_structure_resumable_value_list_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,76);
    gensymed_symbol = IFIX(Resumable_value_list_node_count);
    def_structure_resumable_value_list_node_variable = 
	    Chain_of_available_resumable_value_list_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_value_list_node_variable))
	goto end_loop;
    def_structure_resumable_value_list_node_variable = 
	    ISVREF(def_structure_resumable_value_list_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-VALUE-LIST-NODE-1 */
Object reclaim_resumable_value_list_node_1(resumable_value_list_node)
    Object resumable_value_list_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,77);
    inline_note_reclaim_cons(resumable_value_list_node,Nil);
    structure_being_reclaimed = resumable_value_list_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_value_list_node,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_value_list_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_value_list_node,(SI_Long)3L));
      SVREF(resumable_value_list_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_value_list_node,(SI_Long)9L));
      SVREF(resumable_value_list_node,FIX((SI_Long)9L)) = Nil;
      reclaim_frame_serial_number(ISVREF(resumable_value_list_node,
	      (SI_Long)10L));
      SVREF(resumable_value_list_node,FIX((SI_Long)10L)) = Nil;
      reclaim_inferior_attributes(ISVREF(resumable_value_list_node,
	      (SI_Long)13L));
      SVREF(resumable_value_list_node,FIX((SI_Long)13L)) = Nil;
      reclaim_icp_list_of_resumable_attribute_specs(ISVREF(resumable_value_list_node,
	      (SI_Long)16L));
      SVREF(resumable_value_list_node,FIX((SI_Long)16L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_value_list_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_value_list_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_value_list_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_value_list_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-VALUE-LIST-NODE */
Object reclaim_structure_for_resumable_value_list_node(resumable_value_list_node)
    Object resumable_value_list_node;
{
    x_note_fn_call(167,78);
    return reclaim_resumable_value_list_node_1(resumable_value_list_node);
}

static Object Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct;  /* g2-defstruct-structure-name::resumable-value-list-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-VALUE-LIST-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_value_list_node_structure_internal()
{
    Object def_structure_resumable_value_list_node_variable;
    Object defstruct_g2_resumable_value_list_node_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,79);
    def_structure_resumable_value_list_node_variable = Nil;
    atomic_incff_symval(Qresumable_value_list_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_value_list_node_variable = Nil;
	gensymed_symbol = (SI_Long)22L;
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
	defstruct_g2_resumable_value_list_node_variable = the_array;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_resumable_value_list_node_variable,
		FIX((SI_Long)20L)) = Nil;
	def_structure_resumable_value_list_node_variable = 
		defstruct_g2_resumable_value_list_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_value_list_node_variable);
}

/* MAKE-RESUMABLE-VALUE-LIST-NODE-1 */
Object make_resumable_value_list_node_1(resumable_instance_current_object,
	    resumable_instance_reference_serial_number,
	    current_attribute_names,symbolic_attribute_count,
	    resumable_attribute_spec_qm,resumable_instance_class_name,
	    internal_list_for_object_passing,resumable_sequence_length,
	    resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, internal_list_for_object_passing;
    Object resumable_sequence_length, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_value_list_node_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,80);
    def_structure_resumable_value_list_node_variable = 
	    ISVREF(Chain_of_available_resumable_value_list_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_value_list_node_variable) {
	svref_arg_1 = Chain_of_available_resumable_value_list_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_value_list_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_value_list_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct;
    }
    else
	def_structure_resumable_value_list_node_variable = 
		make_permanent_resumable_value_list_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_value_list_node_variable,
	    Nil);
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)10L)) = resumable_instance_reference_serial_number;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)16L)) = current_attribute_names;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)17L)) = symbolic_attribute_count;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)2L)) = resumable_attribute_spec_qm;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)11L)) = resumable_instance_class_name;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)20L)) = internal_list_for_object_passing;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)18L)) = resumable_sequence_length;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_resumable_value_list_node_variable,
	    FIX((SI_Long)19L)) = Nil;
    ISVREF(def_structure_resumable_value_list_node_variable,(SI_Long)21L) 
	    = FIX((SI_Long)0L);
    return VALUES_1(def_structure_resumable_value_list_node_variable);
}

Object The_type_description_of_resumable_evaluation_sequence_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_evaluation_sequence_node_mixins, Qchain_of_available_resumable_evaluation_sequence_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_evaluation_sequence_node_mixin_count, Qresumable_evaluation_sequence_node_mixin_count);

Object Chain_of_available_resumable_evaluation_sequence_node_mixins_vector = UNBOUND;

/* RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_evaluation_sequence_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,81);
    temp = Resumable_evaluation_sequence_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-COUNT */
Object outstanding_resumable_evaluation_sequence_node_mixin_count()
{
    Object def_structure_resumable_evaluation_sequence_node_mixin_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,82);
    gensymed_symbol = IFIX(Resumable_evaluation_sequence_node_mixin_count);
    def_structure_resumable_evaluation_sequence_node_mixin_variable = 
	    Chain_of_available_resumable_evaluation_sequence_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_resumable_evaluation_sequence_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_evaluation_sequence_node_mixin_variable = 
	    ISVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-1 */
Object reclaim_resumable_evaluation_sequence_node_mixin_1(resumable_evaluation_sequence_node_mixin)
    Object resumable_evaluation_sequence_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,83);
    inline_note_reclaim_cons(resumable_evaluation_sequence_node_mixin,Nil);
    structure_being_reclaimed = resumable_evaluation_sequence_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = 
	      ISVREF(resumable_evaluation_sequence_node_mixin,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_evaluation_sequence_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_evaluation_sequence_node_mixin,
	      (SI_Long)3L));
      SVREF(resumable_evaluation_sequence_node_mixin,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_evaluation_sequence_node_mixin,
	      (SI_Long)9L));
      SVREF(resumable_evaluation_sequence_node_mixin,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_resumable_evaluation_sequence_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_evaluation_sequence_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_evaluation_sequence_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_evaluation_sequence_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN */
Object reclaim_structure_for_resumable_evaluation_sequence_node_mixin(resumable_evaluation_sequence_node_mixin)
    Object resumable_evaluation_sequence_node_mixin;
{
    x_note_fn_call(167,84);
    return reclaim_resumable_evaluation_sequence_node_mixin_1(resumable_evaluation_sequence_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-evaluation-sequence-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_evaluation_sequence_node_mixin_structure_internal()
{
    Object def_structure_resumable_evaluation_sequence_node_mixin_variable;
    Object defstruct_g2_resumable_evaluation_sequence_node_mixin_variable;
    Object the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,85);
    def_structure_resumable_evaluation_sequence_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_evaluation_sequence_node_mixin_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_evaluation_sequence_node_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)13L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_evaluation_sequence_node_mixin_variable = 
		the_array;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)9L)) = Nil;
	def_structure_resumable_evaluation_sequence_node_mixin_variable = 
		defstruct_g2_resumable_evaluation_sequence_node_mixin_variable;
	SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_evaluation_sequence_node_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = 
		Chain_of_available_resumable_evaluation_sequence_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_evaluation_sequence_node_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_evaluation_sequence_node_mixin_variable);
}

/* MAKE-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-1 */
Object make_resumable_evaluation_sequence_node_mixin_1()
{
    Object def_structure_resumable_evaluation_sequence_node_mixin_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(167,86);
    def_structure_resumable_evaluation_sequence_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_evaluation_sequence_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_evaluation_sequence_node_mixin_variable) {
	svref_arg_1 = 
		Chain_of_available_resumable_evaluation_sequence_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_evaluation_sequence_node_mixin_variable = 
		make_permanent_resumable_evaluation_sequence_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_resumable_evaluation_sequence_node_mixin_variable,
	    (SI_Long)11L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_resumable_evaluation_sequence_node_mixin_variable);
}

Object The_type_description_of_resumable_evaluation_sequence_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_evaluation_sequence_nodes, Qchain_of_available_resumable_evaluation_sequence_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_evaluation_sequence_node_count, Qresumable_evaluation_sequence_node_count);

Object Chain_of_available_resumable_evaluation_sequence_nodes_vector = UNBOUND;

/* RESUMABLE-EVALUATION-SEQUENCE-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_evaluation_sequence_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,87);
    temp = Resumable_evaluation_sequence_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-EVALUATION-SEQUENCE-NODE-COUNT */
Object outstanding_resumable_evaluation_sequence_node_count()
{
    Object def_structure_resumable_evaluation_sequence_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,88);
    gensymed_symbol = IFIX(Resumable_evaluation_sequence_node_count);
    def_structure_resumable_evaluation_sequence_node_variable = 
	    Chain_of_available_resumable_evaluation_sequence_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_evaluation_sequence_node_variable))
	goto end_loop;
    def_structure_resumable_evaluation_sequence_node_variable = 
	    ISVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-EVALUATION-SEQUENCE-NODE-1 */
Object reclaim_resumable_evaluation_sequence_node_1(resumable_evaluation_sequence_node)
    Object resumable_evaluation_sequence_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,89);
    inline_note_reclaim_cons(resumable_evaluation_sequence_node,Nil);
    structure_being_reclaimed = resumable_evaluation_sequence_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = 
	      ISVREF(resumable_evaluation_sequence_node,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_evaluation_sequence_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_evaluation_sequence_node,
	      (SI_Long)3L));
      SVREF(resumable_evaluation_sequence_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_evaluation_sequence_node,
	      (SI_Long)9L));
      SVREF(resumable_evaluation_sequence_node,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_resumable_evaluation_sequence_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_evaluation_sequence_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_evaluation_sequence_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_evaluation_sequence_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-EVALUATION-SEQUENCE-NODE */
Object reclaim_structure_for_resumable_evaluation_sequence_node(resumable_evaluation_sequence_node)
    Object resumable_evaluation_sequence_node;
{
    x_note_fn_call(167,90);
    return reclaim_resumable_evaluation_sequence_node_1(resumable_evaluation_sequence_node);
}

static Object Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct;  /* g2-defstruct-structure-name::resumable-evaluation-sequence-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-EVALUATION-SEQUENCE-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_evaluation_sequence_node_structure_internal()
{
    Object def_structure_resumable_evaluation_sequence_node_variable;
    Object defstruct_g2_resumable_evaluation_sequence_node_variable, the_array;
    Object temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,91);
    def_structure_resumable_evaluation_sequence_node_variable = Nil;
    atomic_incff_symval(Qresumable_evaluation_sequence_node_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_evaluation_sequence_node_variable = Nil;
	gensymed_symbol_1 = (SI_Long)13L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_evaluation_sequence_node_variable = the_array;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)12L)) = Nil;
	def_structure_resumable_evaluation_sequence_node_variable = 
		defstruct_g2_resumable_evaluation_sequence_node_variable;
	SVREF(def_structure_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)12L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_evaluation_sequence_nodes_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_evaluation_sequence_nodes_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_evaluation_sequence_node_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_evaluation_sequence_node_variable);
}

/* MAKE-RESUMABLE-EVALUATION-SEQUENCE-NODE-1 */
Object make_resumable_evaluation_sequence_node_1(resumable_instance_current_object,
	    resumable_evaluation_sequence_length,resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_evaluation_sequence_length, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_evaluation_sequence_node_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(167,92);
    def_structure_resumable_evaluation_sequence_node_variable = 
	    ISVREF(Chain_of_available_resumable_evaluation_sequence_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_evaluation_sequence_node_variable) {
	svref_arg_1 = 
		Chain_of_available_resumable_evaluation_sequence_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_evaluation_sequence_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_evaluation_sequence_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct;
    }
    else
	def_structure_resumable_evaluation_sequence_node_variable = 
		make_permanent_resumable_evaluation_sequence_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_evaluation_sequence_node_variable,
	    Nil);
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)10L)) = resumable_evaluation_sequence_length;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_resumable_evaluation_sequence_node_variable,
	    (SI_Long)11L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_resumable_evaluation_sequence_node_variable);
}

Object The_type_description_of_resumable_evaluation_structure_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_evaluation_structure_nodes, Qchain_of_available_resumable_evaluation_structure_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_evaluation_structure_node_count, Qresumable_evaluation_structure_node_count);

Object Chain_of_available_resumable_evaluation_structure_nodes_vector = UNBOUND;

/* RESUMABLE-EVALUATION-STRUCTURE-NODE-STRUCTURE-MEMORY-USAGE */
Object resumable_evaluation_structure_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,93);
    temp = Resumable_evaluation_structure_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)14L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-EVALUATION-STRUCTURE-NODE-COUNT */
Object outstanding_resumable_evaluation_structure_node_count()
{
    Object def_structure_resumable_evaluation_structure_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,94);
    gensymed_symbol = IFIX(Resumable_evaluation_structure_node_count);
    def_structure_resumable_evaluation_structure_node_variable = 
	    Chain_of_available_resumable_evaluation_structure_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_evaluation_structure_node_variable))
	goto end_loop;
    def_structure_resumable_evaluation_structure_node_variable = 
	    ISVREF(def_structure_resumable_evaluation_structure_node_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-EVALUATION-STRUCTURE-NODE-1 */
Object reclaim_resumable_evaluation_structure_node_1(resumable_evaluation_structure_node)
    Object resumable_evaluation_structure_node;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,95);
    inline_note_reclaim_cons(resumable_evaluation_structure_node,Nil);
    structure_being_reclaimed = resumable_evaluation_structure_node;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = 
	      ISVREF(resumable_evaluation_structure_node,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_evaluation_structure_node,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_evaluation_structure_node,
	      (SI_Long)3L));
      SVREF(resumable_evaluation_structure_node,FIX((SI_Long)3L)) = Nil;
      reclaim_icp_list_1(ISVREF(resumable_evaluation_structure_node,
	      (SI_Long)9L));
      SVREF(resumable_evaluation_structure_node,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_resumable_evaluation_structure_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_evaluation_structure_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_evaluation_structure_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_evaluation_structure_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-EVALUATION-STRUCTURE-NODE */
Object reclaim_structure_for_resumable_evaluation_structure_node(resumable_evaluation_structure_node)
    Object resumable_evaluation_structure_node;
{
    x_note_fn_call(167,96);
    return reclaim_resumable_evaluation_structure_node_1(resumable_evaluation_structure_node);
}

static Object Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct;  /* g2-defstruct-structure-name::resumable-evaluation-structure-node-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-EVALUATION-STRUCTURE-NODE-STRUCTURE-INTERNAL */
Object make_permanent_resumable_evaluation_structure_node_structure_internal()
{
    Object def_structure_resumable_evaluation_structure_node_variable;
    Object defstruct_g2_resumable_evaluation_structure_node_variable;
    Object the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,97);
    def_structure_resumable_evaluation_structure_node_variable = Nil;
    atomic_incff_symval(Qresumable_evaluation_structure_node_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_evaluation_structure_node_variable = Nil;
	gensymed_symbol_1 = (SI_Long)14L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_resumable_evaluation_structure_node_variable = the_array;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)12L)) = Nil;
	def_structure_resumable_evaluation_structure_node_variable = 
		defstruct_g2_resumable_evaluation_structure_node_variable;
	SVREF(def_structure_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)12L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_evaluation_structure_nodes_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_evaluation_structure_nodes_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_evaluation_structure_node_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_evaluation_structure_node_variable);
}

/* MAKE-RESUMABLE-EVALUATION-STRUCTURE-NODE-1 */
Object make_resumable_evaluation_structure_node_1(resumable_instance_current_object,
	    resumable_evaluation_sequence_length,resumable_node_parent_node_qm)
    Object resumable_instance_current_object;
    Object resumable_evaluation_sequence_length, resumable_node_parent_node_qm;
{
    Object def_structure_resumable_evaluation_structure_node_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(167,98);
    def_structure_resumable_evaluation_structure_node_variable = 
	    ISVREF(Chain_of_available_resumable_evaluation_structure_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_evaluation_structure_node_variable) {
	svref_arg_1 = 
		Chain_of_available_resumable_evaluation_structure_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_evaluation_structure_node_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_evaluation_structure_node_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct;
    }
    else
	def_structure_resumable_evaluation_structure_node_variable = 
		make_permanent_resumable_evaluation_structure_node_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_evaluation_structure_node_variable,
	    Nil);
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)4L)) = resumable_instance_current_object;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)10L)) = resumable_evaluation_sequence_length;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)1L)) = resumable_node_parent_node_qm;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)8L)) = T;
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_resumable_evaluation_structure_node_variable,
	    (SI_Long)11L) = FIX((SI_Long)0L);
    SVREF(def_structure_resumable_evaluation_structure_node_variable,
	    FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_resumable_evaluation_structure_node_variable);
}

/* RECLAIM-ICP-LIST-OF-RESUMABLE-ATTRIBUTE-SPECS */
Object reclaim_icp_list_of_resumable_attribute_specs(list_1)
    Object list_1;
{
    Object spec, ab_loop_list_;

    x_note_fn_call(167,99);
    spec = Nil;
    ab_loop_list_ = list_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(spec);
    goto next_loop;
  end_loop:
    reclaim_icp_list_1(list_1);
    return VALUES_1(Nil);
}

/* RECLAIM-RESUMABLE-NODE */
Object reclaim_resumable_node(resumable_node)
    Object resumable_node;
{
    x_note_fn_call(167,100);
    if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct))
	reclaim_resumable_circular_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_node_g2_struct))
	reclaim_resumable_value_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct))
	reclaim_resumable_object_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
	reclaim_resumable_object_vector_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct))
	reclaim_resumable_value_vector_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct))
	reclaim_resumable_history_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct))
	reclaim_resumable_object_list_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct))
	reclaim_resumable_value_list_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct))
	reclaim_resumable_evaluation_sequence_node_1(resumable_node);
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct))
	reclaim_resumable_evaluation_structure_node_1(resumable_node);
    return VALUES_1(Nil);
}

/* RECLAIM-INFERIOR-ATTRIBUTES */
Object reclaim_inferior_attributes(inferior_attributes)
    Object inferior_attributes;
{
    Object inferior_attribute, ab_loop_list_;

    x_note_fn_call(167,101);
    inferior_attribute = Nil;
    ab_loop_list_ = inferior_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    inferior_attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_resumable_node(inferior_attribute);
    goto next_loop;
  end_loop:;
    reclaim_icp_list_1(inferior_attributes);
    return VALUES_1(Nil);
}

/* RECLAIM-INTERNAL-VALUE-LIST */
Object reclaim_internal_value_list(internal_value_list)
    Object internal_value_list;
{
    Object internal_value, ab_loop_list_;

    x_note_fn_call(167,102);
    internal_value = Nil;
    ab_loop_list_ = internal_value_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    internal_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_evaluation_value(internal_value);
    goto next_loop;
  end_loop:;
    reclaim_icp_list_1(internal_value_list);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_object_circularity_hashtable_hash_vector_131_vectors, Qavailable_object_circularity_hashtable_hash_vector_131_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_object_circularity_hashtable_hash_vector_131_vectors, Qcount_of_object_circularity_hashtable_hash_vector_131_vectors);

Object Available_object_circularity_hashtable_hash_vector_131_vectors_vector = UNBOUND;

/* OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE */
Object object_circularity_hashtable_hash_vector_131_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(167,103);
    temp = Count_of_object_circularity_hashtable_hash_vector_131_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)131L)));
    return VALUES_1(temp);
}

/* OUT-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTORS */
Object out_object_circularity_hashtable_hash_vector_131_vectors()
{
    Object temp;

    x_note_fn_call(167,104);
    temp = 
	    FIXNUM_MINUS(Count_of_object_circularity_hashtable_hash_vector_131_vectors,
	    length(Available_object_circularity_hashtable_hash_vector_131_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTOR-INTERNAL */
Object make_permanent_object_circularity_hashtable_hash_vector_131_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(167,105);
    atomic_incff_symval(Qcount_of_object_circularity_hashtable_hash_vector_131_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)131L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR */
Object make_object_circularity_hashtable_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(167,106);
    if (ISVREF(Available_object_circularity_hashtable_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_object_circularity_hashtable_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_object_circularity_hashtable_hash_vector_131_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_object_circularity_hashtable_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_object_circularity_hashtable_hash_vector_131_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_object_circularity_hashtable_hash_vector_131_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR */
Object reclaim_object_circularity_hashtable_hash_vector(object_circularity_hashtable_hash_vector_131_vector)
    Object object_circularity_hashtable_hash_vector_131_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(167,107);
    svref_arg_1 = 
	    Available_object_circularity_hashtable_hash_vector_131_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = 
	    object_circularity_hashtable_hash_vector_131_vector;
    temp = 
	    ISVREF(Available_object_circularity_hashtable_hash_vector_131_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-OBJECT-CIRCULARITY-HASHTABLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_object_circularity_hashtable_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(167,108);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-OBJECT-CIRCULARITY-HASHTABLE-TREE-FOR-HASH-NODES */
Object reclaim_object_circularity_hashtable_tree_for_hash_nodes(object_circularity_hashtable_tree_for_hash_skip_list,
	    tail)
    Object object_circularity_hashtable_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(167,109);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(object_circularity_hashtable_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(object_circularity_hashtable_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(object_circularity_hashtable_tree_for_hash_skip_list,
	    (SI_Long)2L);
    entry = ISVREF(object_circularity_hashtable_tree_for_hash_skip_list,
	    (SI_Long)3L);
    reclaim_skip_list_element(object_circularity_hashtable_tree_for_hash_skip_list);
    object_circularity_hashtable_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-OBJECT-CIRCULARITY-HASHTABLE-TREE */
Object clear_object_circularity_hashtable_tree(object_circularity_hashtable_tree_for_hash_skip_list)
    Object object_circularity_hashtable_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(167,110);
    head = M_CAR(M_CDR(object_circularity_hashtable_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(object_circularity_hashtable_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_object_circularity_hashtable_tree_for_hash_nodes(element_qm,
		tail);
    return VALUES_1(object_circularity_hashtable_tree_for_hash_skip_list);
}

static Object Qobject_circularity_hashtable_tree_for_hash;  /* object-circularity-hashtable-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-OBJECT-CIRCULARITY-HASHTABLE */
Object make_object_circularity_hashtable()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(167,111);
    new_vector = make_object_circularity_hashtable_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    tail = 
	    make_object_circularity_hashtable_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_object_circularity_hashtable_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qobject_circularity_hashtable_tree_for_hash;
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
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-OBJECT-CIRCULARITY-HASHTABLE */
Object flatten_object_circularity_hashtable(object_circularity_hashtable_hash_table)
    Object object_circularity_hashtable_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(167,112);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    subtree = ISVREF(object_circularity_hashtable_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-OBJECT-CIRCULARITY-HASHTABLE */
Object clear_object_circularity_hashtable(object_circularity_hashtable_hash_table)
    Object object_circularity_hashtable_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(167,113);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    clear_object_circularity_hashtable_tree(ISVREF(object_circularity_hashtable_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-OBJECT-CIRCULARITY-HASHTABLE */
Object reclaim_object_circularity_hashtable(object_circularity_hashtable_hash_table)
    Object object_circularity_hashtable_hash_table;
{
    Object object_circularity_hashtable_tree_for_hash_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(167,114);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)131L)
	goto end_loop;
    object_circularity_hashtable_tree_for_hash_skip_list = 
	    ISVREF(object_circularity_hashtable_hash_table,index_1);
    head = M_CAR(M_CDR(object_circularity_hashtable_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(object_circularity_hashtable_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_object_circularity_hashtable_tree_for_hash_nodes(element_qm,
		tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(object_circularity_hashtable_tree_for_hash_skip_list) = Nil;
    M_CADR(object_circularity_hashtable_tree_for_hash_skip_list) = Nil;
    M_CAR(object_circularity_hashtable_tree_for_hash_skip_list) = Nil;
    if (object_circularity_hashtable_tree_for_hash_skip_list) {
	last_1 = object_circularity_hashtable_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_1:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_1;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_1;
      end_loop_1:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = object_circularity_hashtable_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    object_circularity_hashtable_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(object_circularity_hashtable_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_object_circularity_hashtable_hash_vector(object_circularity_hashtable_hash_table);
    return VALUES_1(temp_1);
}

Object The_type_description_of_sending_resumable_object = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sending_resumable_objects, Qchain_of_available_sending_resumable_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Sending_resumable_object_count, Qsending_resumable_object_count);

Object Chain_of_available_sending_resumable_objects_vector = UNBOUND;

/* SENDING-RESUMABLE-OBJECT-STRUCTURE-MEMORY-USAGE */
Object sending_resumable_object_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,115);
    temp = Sending_resumable_object_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)23L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SENDING-RESUMABLE-OBJECT-COUNT */
Object outstanding_sending_resumable_object_count()
{
    Object def_structure_sending_resumable_object_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,116);
    gensymed_symbol = IFIX(Sending_resumable_object_count);
    def_structure_sending_resumable_object_variable = 
	    Chain_of_available_sending_resumable_objects;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_sending_resumable_object_variable))
	goto end_loop;
    def_structure_sending_resumable_object_variable = 
	    ISVREF(def_structure_sending_resumable_object_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SENDING-RESUMABLE-OBJECT-INTERNAL-1 */
Object reclaim_sending_resumable_object_internal_1(sending_resumable_object)
    Object sending_resumable_object;
{
    Object structure_being_reclaimed, resumable_node_qm, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(167,117);
    inline_note_reclaim_cons(sending_resumable_object,Nil);
    structure_being_reclaimed = sending_resumable_object;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_list_1(ISVREF(sending_resumable_object,(SI_Long)7L));
      SVREF(sending_resumable_object,FIX((SI_Long)7L)) = Nil;
      resumable_node_qm = ISVREF(sending_resumable_object,(SI_Long)9L);
      if (resumable_node_qm)
	  reclaim_resumable_node(resumable_node_qm);
      SVREF(sending_resumable_object,FIX((SI_Long)9L)) = Nil;
      reclaim_object_circularity_hashtable(ISVREF(sending_resumable_object,
	      (SI_Long)18L));
      SVREF(sending_resumable_object,FIX((SI_Long)18L)) = Nil;
      arrange_to_cancel_task_in_sending_resumable_object(ISVREF(sending_resumable_object,
	      (SI_Long)19L));
      SVREF(sending_resumable_object,FIX((SI_Long)19L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_sending_resumable_objects_vector,
	    IFIX(Current_thread_index));
    SVREF(sending_resumable_object,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sending_resumable_objects_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = sending_resumable_object;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SENDING-RESUMABLE-OBJECT */
Object reclaim_structure_for_sending_resumable_object(sending_resumable_object)
    Object sending_resumable_object;
{
    x_note_fn_call(167,118);
    return reclaim_sending_resumable_object_internal_1(sending_resumable_object);
}

static Object Qg2_defstruct_structure_name_sending_resumable_object_g2_struct;  /* g2-defstruct-structure-name::sending-resumable-object-g2-struct */

/* MAKE-PERMANENT-SENDING-RESUMABLE-OBJECT-STRUCTURE-INTERNAL */
Object make_permanent_sending_resumable_object_structure_internal()
{
    Object def_structure_sending_resumable_object_variable;
    Object defstruct_g2_sending_resumable_object_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,119);
    def_structure_sending_resumable_object_variable = Nil;
    atomic_incff_symval(Qsending_resumable_object_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_sending_resumable_object_variable = Nil;
	gensymed_symbol = (SI_Long)23L;
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
	defstruct_g2_sending_resumable_object_variable = the_array;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sending_resumable_object_g2_struct;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_sending_resumable_object_variable,
		FIX((SI_Long)7L)) = Nil;
	def_structure_sending_resumable_object_variable = 
		defstruct_g2_sending_resumable_object_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_sending_resumable_object_variable);
}

/* MAKE-SENDING-RESUMABLE-OBJECT-INTERNAL-1 */
Object make_sending_resumable_object_internal_1(resumable_object_rpc_name_qm,
	    object_or_handle_to_be_passed,toplevel_resumable_node,
	    current_resumable_node,
	    resumable_object_reference_serial_number,
	    resumable_object_icp_socket,
	    resumable_object_icp_interface_frame_qm,
	    resumable_object_priority,
	    transmit_resumable_object_as_handle_p,
	    resumable_object_included_slots,
	    resumable_object_excluded_slots,
	    resumable_object_included_system_slots)
    Object resumable_object_rpc_name_qm, object_or_handle_to_be_passed;
    Object toplevel_resumable_node, current_resumable_node;
    Object resumable_object_reference_serial_number;
    Object resumable_object_icp_socket;
    Object resumable_object_icp_interface_frame_qm, resumable_object_priority;
    Object transmit_resumable_object_as_handle_p;
    Object resumable_object_included_slots, resumable_object_excluded_slots;
    Object resumable_object_included_system_slots;
{
    Object def_structure_sending_resumable_object_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(167,120);
    def_structure_sending_resumable_object_variable = 
	    ISVREF(Chain_of_available_sending_resumable_objects_vector,
	    IFIX(Current_thread_index));
    if (def_structure_sending_resumable_object_variable) {
	temp = Chain_of_available_sending_resumable_objects_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_sending_resumable_object_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_sending_resumable_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sending_resumable_object_g2_struct;
    }
    else
	def_structure_sending_resumable_object_variable = 
		make_permanent_sending_resumable_object_structure_internal();
    inline_note_allocate_cons(def_structure_sending_resumable_object_variable,
	    Nil);
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)1L)) = resumable_object_rpc_name_qm;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)8L)) = object_or_handle_to_be_passed;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)9L)) = toplevel_resumable_node;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)10L)) = current_resumable_node;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)6L)) = resumable_object_reference_serial_number;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)11L)) = resumable_object_icp_socket;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)13L)) = resumable_object_icp_interface_frame_qm;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)14L)) = resumable_object_priority;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)2L)) = transmit_resumable_object_as_handle_p;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)20L)) = resumable_object_included_slots;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)21L)) = resumable_object_excluded_slots;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)22L)) = resumable_object_included_system_slots;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)7L)) = Nil;
    ISVREF(def_structure_sending_resumable_object_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)17L)) = Nil;
    temp = make_object_circularity_hashtable();
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)18L)) = temp;
    SVREF(def_structure_sending_resumable_object_variable,
	    FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_sending_resumable_object_variable);
}

/* ARRANGE-TO-CANCEL-TASK-IN-SENDING-RESUMABLE-OBJECT */
Object arrange_to_cancel_task_in_sending_resumable_object(task_qm)
    Object task_qm;
{
    x_note_fn_call(167,121);
    if (task_qm)
	SVREF(task_qm,FIX((SI_Long)2L)) = T;
    return VALUES_1(Nil);
}

static Object Qtelewindows;        /* telewindows */

/* GET-INDEX-OF-CIRCULAR-RESUMABLE-NODE */
Object get_index_of_circular_resumable_node(object,resumable_object)
    Object object, resumable_object;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash, circular_resumable_node_qm, current_icp_socket;
    Object current_icp_port, icp_object_index_qm, new_index;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol_1, aref_arg_1;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    double gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    double gensymed_symbol_5, gensymed_symbol_6, aref_new_value;
    Declare_special(14);
    Object result;

    x_note_fn_call(167,122);
    gensymed_symbol = IFIX(frame_hash_function(object));
    temp = ISVREF(resumable_object,(SI_Long)18L);
    temp_1 = gensymed_symbol % (SI_Long)131L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = object;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
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
    circular_resumable_node_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
	    key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    if (circular_resumable_node_qm) {
	current_icp_socket = ISVREF(resumable_object,(SI_Long)11L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		13);
	  current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		  12);
	    icp_object_index_qm = 
		    get_icp_object_index_for_resumable_instance_node(circular_resumable_node_qm,
		    Current_icp_port);
	    temp = icp_object_index_qm;
	    if (temp)
		result = VALUES_1(temp);
	    else {
		new_index = Nil;
		current_icp_port = Current_icp_port;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp);
		    else
			temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
				Qtelewindows) ? T : Nil;
		    disable_resumability = temp;
		    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			    9);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      8);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				7);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				  6);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				    5);
			      number_of_icp_bytes_to_fill_buffer = 
				      FIX((SI_Long)0L);
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
					gensymed_symbol_1 = Nil;
					gensymed_symbol_2 = 0.0;
					gensymed_symbol_3 = 0.0;
					if (Profiling_enabled_qm) {
					    gensymed_symbol_1 = T;
					    gensymed_symbol_2 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    gensymed_symbol_3);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    new_index = 
						    establish_new_object_index_for_resumable_instance_node(2,
						    circular_resumable_node_qm,
						    Current_icp_port);
					    end_icp_message_group();
					}
					if (Profiling_enabled_qm) {
					    gensymed_symbol_4 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_5 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_6 = 
						    gensymed_symbol_4 - 
						    gensymed_symbol_5;
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_6 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    aref_new_value);
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol_1 ? 
						    gensymed_symbol_2 + 
						    gensymed_symbol_6 + 
						    (gensymed_symbol_5 - 
						    gensymed_symbol_3) : 
						    gensymed_symbol_4;
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
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
		result = VALUES_1(new_index);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* SET-INDEX-OF-CIRCULAR-RESUMABLE-NODE */
Object set_index_of_circular_resumable_node(object,resumable_object,
	    resumable_node)
    Object object, resumable_object, resumable_node;
{
    Object temp;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(167,123);
    gensymed_symbol = IFIX(frame_hash_function(object));
    temp = ISVREF(resumable_object,(SI_Long)18L);
    temp_1 = gensymed_symbol % (SI_Long)131L;
    return set_skip_list_entry(SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
	    Qeq,Nil,T,object,FIX(gensymed_symbol),resumable_node);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qresumable_object;   /* resumable-object */

static Object Qname_of_corresponding_icp_object_index_space;  /* name-of-corresponding-icp-object-index-space */

/* RECLAIM-SENDING-AND-RECEIVING-RESUMABLE-OBJECT */
Object reclaim_sending_and_receiving_resumable_object(sending_resumable_object)
    Object sending_resumable_object;
{
    Object icp_socket, reference_number, gensymed_symbol, x, xa, ya;
    Object index_space_name;
    char temp, need_to_reclaim_remote_side_p;

    x_note_fn_call(167,124);
    icp_socket = ISVREF(sending_resumable_object,(SI_Long)11L);
    reference_number = ISVREF(sending_resumable_object,(SI_Long)6L);
    gensymed_symbol = ISVREF(ISVREF(sending_resumable_object,(SI_Long)8L),
	    (SI_Long)3L);
    x = ISVREF(sending_resumable_object,(SI_Long)8L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(reference_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(reference_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(reference_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(reference_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    need_to_reclaim_remote_side_p =  !temp;
    index_space_name = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qresumable_object),
	    Qname_of_corresponding_icp_object_index_space);
    if (need_to_reclaim_remote_side_p)
	g2_reclaim_remote_side_for_deactivate_object_passing(sending_resumable_object,
		icp_socket,index_space_name);
    return g2_reclaim_sending_resumable_object(1,sending_resumable_object);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* G2-RECLAIM-SINGLE-RECEIVING-RESUMABLE-OBJECT */
Object g2_reclaim_single_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object object_being_built_qm, x2;
    char temp;

    x_note_fn_call(167,125);
    object_being_built_qm = ISVREF(receiving_resumable_object,(SI_Long)7L);
    if (SIMPLE_VECTOR_P(object_being_built_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object_being_built_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(object_being_built_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(object_being_built_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ?  
	    !TRUEP(rpc_object_handed_off_to_user_p(object_being_built_qm)) 
	    : TRUEP(Nil))
	delete_frame(object_being_built_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_object_passing_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_object_passing_infos, Qchain_of_available_object_passing_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Object_passing_info_count, Qobject_passing_info_count);

Object Chain_of_available_object_passing_infos_vector = UNBOUND;

/* OBJECT-PASSING-INFO-STRUCTURE-MEMORY-USAGE */
Object object_passing_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(167,126);
    temp = Object_passing_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-OBJECT-PASSING-INFO-COUNT */
Object outstanding_object_passing_info_count()
{
    Object def_structure_object_passing_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,127);
    gensymed_symbol = IFIX(Object_passing_info_count);
    def_structure_object_passing_info_variable = 
	    Chain_of_available_object_passing_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_object_passing_info_variable))
	goto end_loop;
    def_structure_object_passing_info_variable = 
	    ISVREF(def_structure_object_passing_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-OBJECT-PASSING-INFO-1 */
Object reclaim_object_passing_info_1(object_passing_info)
    Object object_passing_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(167,128);
    inline_note_reclaim_cons(object_passing_info,Nil);
    temp = ISVREF(Chain_of_available_object_passing_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(object_passing_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_object_passing_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = object_passing_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-OBJECT-PASSING-INFO */
Object reclaim_structure_for_object_passing_info(object_passing_info)
    Object object_passing_info;
{
    x_note_fn_call(167,129);
    return reclaim_object_passing_info_1(object_passing_info);
}

/* MAKE-PERMANENT-OBJECT-PASSING-INFO-STRUCTURE-INTERNAL */
Object make_permanent_object_passing_info_structure_internal()
{
    Object def_structure_object_passing_info_variable, the_array;
    Object defstruct_g2_object_passing_info_variable, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(167,130);
    def_structure_object_passing_info_variable = Nil;
    atomic_incff_symval(Qobject_passing_info_count,FIX((SI_Long)100L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)4L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_object_passing_info_variable = the_array;
	def_structure_object_passing_info_variable = 
		defstruct_g2_object_passing_info_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_object_passing_infos_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_object_passing_info_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_object_passing_infos_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_object_passing_info_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_object_passing_info_variable);
}

/* MAKE-OBJECT-PASSING-INFO-1 */
Object make_object_passing_info_1()
{
    Object def_structure_object_passing_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(167,131);
    def_structure_object_passing_info_variable = 
	    ISVREF(Chain_of_available_object_passing_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_object_passing_info_variable) {
	svref_arg_1 = Chain_of_available_object_passing_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_object_passing_info_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_object_passing_info_variable = 
		make_permanent_object_passing_info_structure_internal();
    inline_note_allocate_cons(def_structure_object_passing_info_variable,Nil);
    SVREF(def_structure_object_passing_info_variable,FIX((SI_Long)0L)) = Nil;
    SVREF(def_structure_object_passing_info_variable,FIX((SI_Long)1L)) = T;
    SVREF(def_structure_object_passing_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_object_passing_info_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_object_passing_info_variable);
}

static Object Qobject_passing_info_qm;  /* object-passing-info? */

/* G2-RPC-OBJECT-HANDED-OFF-TO-USER-P-FUNCTION */
Object g2_rpc_object_handed_off_to_user_p_function(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(167,132);
    gensymed_symbol = get_lookup_slot_value_given_default(block,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : T;
    return VALUES_1(gensymed_symbol);
}

/* ICP-OBJECT-MAP-FOR-REGISTERED-ITEM-FUNCTION */
Object icp_object_map_for_registered_item_function(block)
    Object block;
{
    Object gensymed_symbol;

    x_note_fn_call(167,133);
    gensymed_symbol = get_lookup_slot_value_given_default(block,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : Nil;
    return VALUES_1(gensymed_symbol);
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_to_g2_uses_references_p, Qg2_to_g2_uses_references_p);

static Object Qunknown;            /* unknown */

static Object Qg2;                 /* g2 */

static Object Qgsi;                /* gsi */

static Object Qgsi_references_in_use;  /* gsi-references-in-use */

/* ITEM-REFERENCES-ENABLED-P */
Object item_references_enabled_p(icp_socket)
    Object icp_socket;
{
    Object enabled_p, temp;

    x_note_fn_call(167,134);
    enabled_p = ISVREF(icp_socket,(SI_Long)50L);
    if (EQ(enabled_p,Qunknown)) {
	temp = ISVREF(icp_socket,(SI_Long)25L);
	if (EQ(temp,Qg2))
	    enabled_p = G2_to_g2_uses_references_p;
	else if (EQ(temp,Qgsi)) {
	    enabled_p = (SI_Long)1L == 
		    IFIX(get_remote_icp_version_info_value(icp_socket,
		    Qgsi_references_in_use,FIX((SI_Long)0L))) ? T : Nil;
	    if (enabled_p &&  !TRUEP(G2_to_g2_uses_references_p))
		enable_references_for_item_passing();
	}
	else
	    enabled_p = Nil;
	SVREF(icp_socket,FIX((SI_Long)50L)) = enabled_p;
    }
    return VALUES_1(enabled_p);
}

static Object Qgsi_interface_name;  /* gsi-interface-name */

static Object Qgsi_interface;      /* gsi-interface */

static Object Qgsi_collection_interval;  /* gsi-collection-interval */

/* INITIALIZE-GSI-DATA-SERVICE */
Object initialize_gsi_data_service(registered_item,interface_1)
    Object registered_item, interface_1;
{
    Object gsi_interface_name_qm, x2, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(167,135);
    gsi_interface_name_qm = get_slot_value_if_any_function(registered_item,
	    Qgsi_interface_name,Nil);
    if (gsi_interface_name_qm) {
	if (SIMPLE_VECTOR_P(interface_1) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interface_1)) > (SI_Long)2L 
		&&  !EQ(ISVREF(interface_1,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(interface_1,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qgsi_interface,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp ? EQ(gsi_interface_name_qm,
	    get_primary_name_for_frame_if_any(interface_1)) : TRUEP(Nil))
	get_or_make_gsi_sensor(registered_item,
		get_slot_value_if_any_function(registered_item,
		Qgsi_collection_interval,Nil));
    return VALUES_1(Nil);
}

static Object Qitem_index_space;   /* item-index-space */

static Object Qestablish_new_object_index_for_registered_item;  /* establish-new-object-index-for-registered-item */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-REGISTERED-ITEM */
Object establish_new_object_index_for_registered_item varargs_1(int, n)
{
    Object registered_item, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, gensymed_symbol, gensymed_symbol_1;
    Object slot_group_qm, svref_arg_1, resumable_icp_state_1, icp_suspend_1;
    Object top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(167,136);
    INIT_ARGS_nonrelocating();
    registered_item = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(registered_item,
		Qitem_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	gensymed_symbol = registered_item;
	gensymed_symbol_1 = Nil;
	slot_group_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	note_change_to_block_or_struct_or_seq(gensymed_symbol,
		Qobject_passing_info_qm);
	gensymed_symbol_1 = 
		get_lookup_slot_value_given_default(registered_item,
		Qobject_passing_info_qm,Nil);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : Nil;
	gensymed_symbol_1 = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		gensymed_symbol_1));
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,Qnil)) {
	    set_non_savable_lookup_slot_value(gensymed_symbol,
		    Qobject_passing_info_qm,make_object_passing_info_1());
	    svref_arg_1 = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
	}
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qestablish_new_object_index_for_registered_item,top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_registered_item,
			top,Nil);
	}
	registered_item = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : registered_item;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(registered_item,
		Qitem_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	gensymed_symbol = registered_item;
	gensymed_symbol_1 = Nil;
	slot_group_qm = 
		get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	note_change_to_block_or_struct_or_seq(gensymed_symbol,
		Qobject_passing_info_qm);
	gensymed_symbol_1 = 
		get_lookup_slot_value_given_default(registered_item,
		Qobject_passing_info_qm,Nil);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : Nil;
	gensymed_symbol_1 = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		gensymed_symbol_1));
	if (slot_group_qm)
	    SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	else if ( !EQ(gensymed_symbol_1,Qnil)) {
	    set_non_savable_lookup_slot_value(gensymed_symbol,
		    Qobject_passing_info_qm,make_object_passing_info_1());
	    svref_arg_1 = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
	}
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qgsi_data_service;   /* gsi-data-service */

static Object Qmake_corresponding_icp_registered_item;  /* make-corresponding-icp-registered-item */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* MAKE-CORRESPONDING-ICP-REGISTERED-ITEM */
Object make_corresponding_icp_registered_item(registered_item)
    Object registered_item;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, gensymed_symbol, gensymed_symbol_1;
    Object slot_group_qm, temp, svref_arg_1, interface_1, sub_class_bit_vector;
    Object sensor_p, corresponding_icp_object_index_for_item_reference;
    Object resumable_icp_state_1, icp_suspend_1, top, test, v1, v2, v3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(167,137);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  result = assign_corresponding_icp_object_index(registered_item,
		  Qitem_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  gensymed_symbol = registered_item;
	  gensymed_symbol_1 = Nil;
	  slot_group_qm = 
		  get_lookup_slot_value_given_default(gensymed_symbol,
		  Qobject_passing_info_qm,Nil);
	  note_change_to_block_or_struct_or_seq(gensymed_symbol,
		  Qobject_passing_info_qm);
	  temp = Current_icp_port;
	  gensymed_symbol_1 = 
		  get_lookup_slot_value_given_default(registered_item,
		  Qobject_passing_info_qm,Nil);
	  gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		  (SI_Long)3L) : Nil;
	  gensymed_symbol_1 = gensym_cons_1(temp,
		  gensym_cons_1(corresponding_icp_object_index,
		  gensymed_symbol_1));
	  if (slot_group_qm)
	      SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	  else if ( !EQ(gensymed_symbol_1,Qnil)) {
	      set_non_savable_lookup_slot_value(gensymed_symbol,
		      Qobject_passing_info_qm,make_object_passing_info_1());
	      svref_arg_1 = 
		      get_lookup_slot_value_given_default(gensymed_symbol,
		      Qobject_passing_info_qm,Nil);
	      SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
	  }
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      interface_1 = ISVREF(Current_icp_socket,(SI_Long)5L);
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(Qgsi_data_service,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  sub_class_bit_vector = ISVREF(ISVREF(registered_item,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		      gensymed_symbol_3 = gensymed_symbol_3 << 
			      gensymed_symbol_4;
		      gensymed_symbol_2 = gensymed_symbol_2 & 
			      gensymed_symbol_3;
		      sensor_p = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
		  }
		  else
		      sensor_p = Nil;
	      }
	      else
		  sensor_p = Nil;
	      corresponding_icp_object_index_for_item_reference = 
		      corresponding_icp_object_index;
	      PUSH_SPECIAL_WITH_SYMBOL(Corresponding_icp_object_index_for_item_reference,Qcorresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		if (sensor_p)
		    initialize_gsi_data_service(registered_item,interface_1);
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)12L ? 
			TRUEP(item_references_enabled_p(Current_icp_socket)) 
			: TRUEP(Nil))
		    send_icp_create_item_reference(registered_item);
		else if ( !EQ(Qg2,ISVREF(Current_icp_socket,(SI_Long)25L))) {
		    if (sensor_p)
			define_or_configure_gsi_sensor(registered_item,
				corresponding_icp_object_index,interface_1);
		    else if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)5L)
			gsi_register_item(registered_item,
				corresponding_icp_object_index,interface_1);
		}
	      POP_SPECIAL();
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_registered_item,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_registered_item,top,Nil);
	}
	registered_item = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : registered_item;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
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
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(registered_item,
		      Qitem_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      gensymed_symbol = registered_item;
	      gensymed_symbol_1 = Nil;
	      slot_group_qm = 
		      get_lookup_slot_value_given_default(gensymed_symbol,
		      Qobject_passing_info_qm,Nil);
	      note_change_to_block_or_struct_or_seq(gensymed_symbol,
		      Qobject_passing_info_qm);
	      temp = Current_icp_port;
	      gensymed_symbol_1 = 
		      get_lookup_slot_value_given_default(registered_item,
		      Qobject_passing_info_qm,Nil);
	      gensymed_symbol_1 = gensymed_symbol_1 ? 
		      ISVREF(gensymed_symbol_1,(SI_Long)3L) : Nil;
	      gensymed_symbol_1 = gensym_cons_1(temp,
		      gensym_cons_1(corresponding_icp_object_index,
		      gensymed_symbol_1));
	      if (slot_group_qm)
		  SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
	      else if ( !EQ(gensymed_symbol_1,Qnil)) {
		  set_non_savable_lookup_slot_value(gensymed_symbol,
			  Qobject_passing_info_qm,
			  make_object_passing_info_1());
		  svref_arg_1 = 
			  get_lookup_slot_value_given_default(gensymed_symbol,
			  Qobject_passing_info_qm,Nil);
		  SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
	      }
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      interface_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : ISVREF(Current_icp_socket,
		      (SI_Long)5L);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  sensor_p = resumable_icp_pop();
	      else {
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(Qgsi_data_service,
			  Class_description_gkbprop);
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(ISVREF(registered_item,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			  sensor_p = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
		      }
		      else
			  sensor_p = Nil;
		  }
		  else
		      sensor_p = Nil;
	      }
	      corresponding_icp_object_index_for_item_reference = 
		      (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : corresponding_icp_object_index;
	      PUSH_SPECIAL_WITH_SYMBOL(Corresponding_icp_object_index_for_item_reference,Qcorresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			 TRUEP(Nil))) {
		    if (sensor_p)
			initialize_gsi_data_service(registered_item,
				interface_1);
		}
		test = Nil;
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    test = resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qtrue) : 
			IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)12L ? 
			TRUEP(item_references_enabled_p(Current_icp_socket)) 
			: TRUEP(Nil)) {
		    if (EQ(icp_suspend_1,
			    send_icp_create_item_reference(registered_item))) {
			resumable_icp_push(Qtrue);
			resumable_icp_push(Corresponding_icp_object_index_for_item_reference);
			resumable_icp_push(sensor_p);
			resumable_icp_push(interface_1);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Writing_resumable_icp_messages_p);
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_block;
		    }
		}
		else if ((resumable_icp_state_1 ? 
			TRUEP(Resumable_icp_state) : TRUEP(Nil)) ||  
			!EQ(Qg2,ISVREF(Current_icp_socket,(SI_Long)25L))) {
		    test = Nil;
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			test = resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qtrue) : TRUEP(sensor_p)) {
			if (EQ(icp_suspend_1,
				define_or_configure_gsi_sensor(registered_item,
				corresponding_icp_object_index,interface_1))) {
			    resumable_icp_push(Qtrue);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Corresponding_icp_object_index_for_item_reference);
			    resumable_icp_push(sensor_p);
			    resumable_icp_push(interface_1);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Writing_resumable_icp_messages_p);
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_block;
			}
		    }
		    else if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) || 
			    IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)5L) {
			if (EQ(icp_suspend_1,
				gsi_register_item(registered_item,
				corresponding_icp_object_index,interface_1))) {
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Qfalse);
			    resumable_icp_push(Corresponding_icp_object_index_for_item_reference);
			    resumable_icp_push(sensor_p);
			    resumable_icp_push(interface_1);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Writing_resumable_icp_messages_p);
			    resumable_icp_push(FIX((SI_Long)2L));
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_block;
			}
		    }
		}
	      POP_SPECIAL();
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(registered_item);
	    resumable_icp_push(Qmake_corresponding_icp_registered_item);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-REGISTERED-ITEM */
Object get_icp_object_index_for_registered_item(registered_item,icp_port)
    Object registered_item, icp_port;
{
    Object gensymed_symbol;

    x_note_fn_call(167,138);
    gensymed_symbol = get_lookup_slot_value_given_default(registered_item,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : Nil;
    return getfq_function_no_default(gensymed_symbol,icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-REGISTERED-ITEM */
Object set_icp_object_index_for_registered_item(registered_item,
	    corresponding_icp_object_index,icp_port)
    Object registered_item, corresponding_icp_object_index, icp_port;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, svref_arg_1;

    x_note_fn_call(167,139);
    gensymed_symbol = registered_item;
    gensymed_symbol_1 = Nil;
    slot_group_qm = get_lookup_slot_value_given_default(gensymed_symbol,
	    Qobject_passing_info_qm,Nil);
    note_change_to_block_or_struct_or_seq(gensymed_symbol,
	    Qobject_passing_info_qm);
    gensymed_symbol_1 = 
	    get_lookup_slot_value_given_default(registered_item,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)3L) : Nil;
    gensymed_symbol_1 = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,gensymed_symbol_1));
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	set_non_savable_lookup_slot_value(gensymed_symbol,
		Qobject_passing_info_qm,make_object_passing_info_1());
	svref_arg_1 = get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
    }
    return VALUES_1(gensymed_symbol_1);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-REGISTERED-ITEM */
Object reclaim_icp_object_map_for_registered_item(registered_item)
    Object registered_item;
{
    Object gensymed_symbol, icp_object_map;

    x_note_fn_call(167,140);
    gensymed_symbol = get_lookup_slot_value_given_default(registered_item,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : Nil;
    icp_object_map = gensymed_symbol;
    if (icp_object_map)
	return reclaim_icp_object_map(registered_item,icp_object_map,
		Qitem_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_registered_item;  /* set-access-form-for-registered-item */

/* RECLAIM-ICP-PORT-ENTRY-FOR-REGISTERED-ITEM */
Object reclaim_icp_port_entry_for_registered_item(registered_item,icp_port)
    Object registered_item, icp_port;
{
    Object gensymed_symbol;

    x_note_fn_call(167,141);
    gensymed_symbol = get_lookup_slot_value_given_default(registered_item,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : Nil;
    return reclaim_icp_port_entry(icp_port,registered_item,gensymed_symbol,
	    Qset_access_form_for_registered_item);
}

/* SET-ACCESS-FORM-FOR-REGISTERED-ITEM */
Object set_access_form_for_registered_item(registered_item,new_value)
    Object registered_item, new_value;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, svref_arg_1;

    x_note_fn_call(167,142);
    gensymed_symbol = registered_item;
    gensymed_symbol_1 = Nil;
    slot_group_qm = get_lookup_slot_value_given_default(gensymed_symbol,
	    Qobject_passing_info_qm,Nil);
    note_change_to_block_or_struct_or_seq(gensymed_symbol,
	    Qobject_passing_info_qm);
    gensymed_symbol_1 = new_value;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	set_non_savable_lookup_slot_value(gensymed_symbol,
		Qobject_passing_info_qm,make_object_passing_info_1());
	svref_arg_1 = get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
    }
    return VALUES_1(gensymed_symbol_1);
}

static Object Qestablish_new_object_index_for_class_description;  /* establish-new-object-index-for-class-description */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-CLASS-DESCRIPTION */
Object establish_new_object_index_for_class_description varargs_1(int, n)
{
    Object class_description, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(167,143);
    INIT_ARGS_nonrelocating();
    class_description = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(class_description,
		Qitem_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(class_description,(SI_Long)22L)));
	SVREF(class_description,FIX((SI_Long)22L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qestablish_new_object_index_for_class_description,top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_class_description,
			top,Nil);
	}
	class_description = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : class_description;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(class_description,
		Qitem_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(class_description,(SI_Long)22L)));
	SVREF(class_description,FIX((SI_Long)22L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_class_description;  /* make-corresponding-icp-class-description */

/* MAKE-CORRESPONDING-ICP-CLASS-DESCRIPTION */
Object make_corresponding_icp_class_description(class_description)
    Object class_description;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object corresponding_icp_object_index_for_item_reference;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(2);
    Object result;

    x_note_fn_call(167,144);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  result = assign_corresponding_icp_object_index(class_description,
		  Qitem_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(class_description,(SI_Long)22L)));
	  SVREF(class_description,FIX((SI_Long)22L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      corresponding_icp_object_index_for_item_reference = 
		      corresponding_icp_object_index;
	      PUSH_SPECIAL_WITH_SYMBOL(Corresponding_icp_object_index_for_item_reference,Qcorresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		if (IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)12L ? 
			TRUEP(item_references_enabled_p(Current_icp_socket)) 
			: TRUEP(Nil))
		    send_icp_create_item_reference(class_description);
	      POP_SPECIAL();
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_class_description,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_class_description,top,Nil);
	}
	class_description = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : class_description;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
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
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		1);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(class_description,
		      Qitem_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(class_description,(SI_Long)22L)));
	      SVREF(class_description,FIX((SI_Long)22L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      corresponding_icp_object_index_for_item_reference = 
		      (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : corresponding_icp_object_index;
	      PUSH_SPECIAL_WITH_SYMBOL(Corresponding_icp_object_index_for_item_reference,Qcorresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		      0);
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) || (IFIX(ISVREF(Current_icp_socket,
			(SI_Long)22L)) >= (SI_Long)12L ? 
			TRUEP(item_references_enabled_p(Current_icp_socket)) 
			: TRUEP(Nil))) {
		    if (EQ(icp_suspend_1,
			    send_icp_create_item_reference(class_description))) 
				{
			resumable_icp_push(Corresponding_icp_object_index_for_item_reference);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Writing_resumable_icp_messages_p);
			resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_block;
		    }
		}
	      POP_SPECIAL();
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(class_description);
	    resumable_icp_push(Qmake_corresponding_icp_class_description);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-CLASS-DESCRIPTION */
Object get_icp_object_index_for_class_description(class_description,icp_port)
    Object class_description, icp_port;
{
    x_note_fn_call(167,145);
    return getfq_function_no_default(ISVREF(class_description,
	    (SI_Long)22L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-CLASS-DESCRIPTION */
Object set_icp_object_index_for_class_description(class_description,
	    corresponding_icp_object_index,icp_port)
    Object class_description, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(167,146);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(class_description,(SI_Long)22L)));
    return VALUES_1(SVREF(class_description,FIX((SI_Long)22L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-CLASS-DESCRIPTION */
Object reclaim_icp_object_map_for_class_description(class_description)
    Object class_description;
{
    Object icp_object_map;

    x_note_fn_call(167,147);
    icp_object_map = ISVREF(class_description,(SI_Long)22L);
    if (icp_object_map)
	return reclaim_icp_object_map(class_description,icp_object_map,
		Qitem_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_class_description;  /* set-access-form-for-class-description */

/* RECLAIM-ICP-PORT-ENTRY-FOR-CLASS-DESCRIPTION */
Object reclaim_icp_port_entry_for_class_description(class_description,icp_port)
    Object class_description, icp_port;
{
    x_note_fn_call(167,148);
    return reclaim_icp_port_entry(icp_port,class_description,
	    ISVREF(class_description,(SI_Long)22L),
	    Qset_access_form_for_class_description);
}

/* SET-ACCESS-FORM-FOR-CLASS-DESCRIPTION */
Object set_access_form_for_class_description(class_description,new_value)
    Object class_description, new_value;
{
    x_note_fn_call(167,149);
    return VALUES_1(SVREF(class_description,FIX((SI_Long)22L)) = new_value);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qoutput;             /* output */

static Object Qframe_serial_number;  /* frame-serial-number */

/* RECLAIM-INDEX-FOR-REGISTERED-ITEM */
Object reclaim_index_for_registered_item(index_1,output_port_p)
    Object index_1, output_port_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1, old_entry;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(167,150);
    port = Current_icp_port;
    if (EQ(Qitem_index_space,Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(Qitem_index_space,Qitem_index_space)) {
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
    else if (EQ(Qitem_index_space,Qframe_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	index_space_name = Qstandard_icp_object_index_space;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(Current_icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qitem_index_space))
	index_space = item_index_space(Current_icp_port);
    else if (EQ(index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(Current_icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	set_skip_list_entry(SVREF(index_space,FIX(temp_2)),
		FIX((SI_Long)31L),Qeq,
		Fp_mutate_frame_serial_number_to_item_table_tree_for_hash_skip_list_entry,
		T,index_1,FIX(gensymed_symbol),Nil);
    }
    else {
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    enlarge_index_space(index_space,index_1);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) 
		>>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    if (output_port_p) {
	if (EQ(index_space_name,Qframe_serial_number)) {
	    gensymed_symbol = IFIX(sxhashw(index_1));
	    temp_2 = gensymed_symbol % (SI_Long)67L;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),index_1,
		    SVREF(index_space,FIX(temp_2)),FIX((SI_Long)31L),
		    FIX(gensymed_symbol));
	    old_entry = NTH_VALUE((SI_Long)1L, result);
	    if (old_entry)
		note_item_deleted_from_frame_serial_number_table(old_entry);
	}
	else
	    deassign_index_in_index_space(index_1,index_space);
    }
    return VALUES_1(Nil);
}

/* SAVE-ICP-OBJECT-MAP-FOR-REGISTERED-ITEM */
Object save_icp_object_map_for_registered_item(frame)
    Object frame;
{
    Object gensymed_symbol, icp_object_map, icp_port, index_1, ab_loop_list_;
    Object temp, gensymed_symbol_1, slot_group_qm, svref_arg_1;

    x_note_fn_call(167,151);
    gensymed_symbol = get_lookup_slot_value_given_default(frame,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : Nil;
    icp_object_map = gensymed_symbol;
    icp_port = Nil;
    index_1 = Nil;
    ab_loop_list_ = icp_object_map;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    icp_port = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    index_1 = CAR(temp);
    set_in_icp_port(icp_port,index_1,Qitem_index_space,Nil);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    gensymed_symbol = frame;
    gensymed_symbol_1 = Nil;
    slot_group_qm = get_lookup_slot_value_given_default(gensymed_symbol,
	    Qobject_passing_info_qm,Nil);
    note_change_to_block_or_struct_or_seq(gensymed_symbol,
	    Qobject_passing_info_qm);
    gensymed_symbol_1 = Nil;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	set_non_savable_lookup_slot_value(gensymed_symbol,
		Qobject_passing_info_qm,make_object_passing_info_1());
	svref_arg_1 = get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
    }
    temp = icp_object_map;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* RESTORE-ICP-OBJECT-MAP-FOR-REGISTERED-ITEM */
Object restore_icp_object_map_for_registered_item(frame,icp_object_map)
    Object frame, icp_object_map;
{
    Object gensymed_symbol, gensymed_symbol_1, slot_group_qm, svref_arg_1;
    Object icp_port, index_1, ab_loop_list_, temp;

    x_note_fn_call(167,152);
    gensymed_symbol = frame;
    gensymed_symbol_1 = Nil;
    slot_group_qm = get_lookup_slot_value_given_default(gensymed_symbol,
	    Qobject_passing_info_qm,Nil);
    note_change_to_block_or_struct_or_seq(gensymed_symbol,
	    Qobject_passing_info_qm);
    gensymed_symbol_1 = icp_object_map;
    if (slot_group_qm)
	SVREF(slot_group_qm,FIX((SI_Long)3L)) = gensymed_symbol_1;
    else if ( !EQ(gensymed_symbol_1,Qnil)) {
	set_non_savable_lookup_slot_value(gensymed_symbol,
		Qobject_passing_info_qm,make_object_passing_info_1());
	svref_arg_1 = get_lookup_slot_value_given_default(gensymed_symbol,
		Qobject_passing_info_qm,Nil);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = gensymed_symbol_1;
    }
    icp_port = Nil;
    index_1 = Nil;
    ab_loop_list_ = icp_object_map;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    icp_port = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    index_1 = CAR(temp);
    set_in_icp_port(icp_port,index_1,Qitem_index_space,frame);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* GET-ITEM-FROM-LOCAL-HANDLE */
Object get_item_from_local_handle(handle,icp_socket)
    Object handle, icp_socket;
{
    Object temp;

    x_note_fn_call(167,153);
    temp = get_from_icp_port_if_any(ISVREF(icp_socket,(SI_Long)4L),handle,
	    Qitem_index_space);
    return VALUES_1(temp);
}

/* LOOKUP-ITEM-FROM-FRAME-SERIAL-NUMBER-TABLE-OF-PORT */
Object lookup_item_from_frame_serial_number_table_of_port(frame_serial_number,
	    icp_port)
    Object frame_serial_number, icp_port;
{
    Object temp, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(167,154);
    gensymed_symbol = IFIX(sxhashw(frame_serial_number));
    temp = frame_serial_number_to_item_table(icp_port);
    temp_1 = gensymed_symbol % (SI_Long)67L;
    temp = SVREF(temp,FIX(temp_1));
    skip_list = CDR(temp);
    key_value = frame_serial_number;
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
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp);
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
    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    return VALUES_1(temp);
}

/* REGISTER-ITEM-WITH-SOCKET */
Object register_item_with_socket(item,icp_socket,use_existing_message_group_p)
    Object item, icp_socket, use_existing_message_group_p;
{
    Object output_port, temp, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
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

    x_note_fn_call(167,155);
    output_port = ISVREF(icp_socket,(SI_Long)4L);
    temp = get_icp_object_index_for_registered_item(item,output_port);
    if (temp);
    else if (use_existing_message_group_p)
	temp = make_corresponding_icp_registered_item(item);
    else {
	current_icp_port = output_port;
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
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    temp = 
					    make_corresponding_icp_registered_item(item);
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
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
    }
    return VALUES_1(temp);
}

/* DEREGISTER-ITEM-WITH-SOCKET */
Object deregister_item_with_socket(item,icp_socket)
    Object item, icp_socket;
{
    Object deregister_corresponding_object_qm, input_port, output_port;
    Object gensymed_symbol, icp_object_map_tail, next_tail, icp_port, index_1;
    Object temp;
    Declare_special(1);

    x_note_fn_call(167,156);
    deregister_corresponding_object_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Deregister_corresponding_object_qm,Qderegister_corresponding_object_qm,deregister_corresponding_object_qm,
	    0);
      input_port = ISVREF(icp_socket,(SI_Long)3L);
      output_port = ISVREF(icp_socket,(SI_Long)4L);
      gensymed_symbol = get_lookup_slot_value_given_default(item,
	      Qobject_passing_info_qm,Nil);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)3L) : Nil;
      icp_object_map_tail = gensymed_symbol;
      next_tail = Nil;
      icp_port = Nil;
      index_1 = Nil;
    next_loop:
      if ( !TRUEP(icp_object_map_tail))
	  goto end_loop;
      next_tail = CDDR(icp_object_map_tail);
      icp_port = CAR(icp_object_map_tail);
      temp = CDR(icp_object_map_tail);
      index_1 = CAR(temp);
      if (EQ(icp_port,input_port) || EQ(icp_port,output_port))
	  reclaim_index_space_location_and_corresponding_objects(item,
		  icp_port,index_1,Qitem_index_space);
      icp_object_map_tail = next_tail;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* ENSURE-REGISTRATION-ON-NETWORK */
Object ensure_registration_on_network(item,icp_interface)
    Object item, icp_interface;
{
    Object icp_socket, temp;

    x_note_fn_call(167,157);
    icp_socket = icp_socket_of_interface_object(icp_interface);
    temp = icp_socket && icp_connection_open_p(icp_socket) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket)) ? 
	    register_item_with_socket(item,icp_socket,Nil) : Nil;
    return VALUES_1(temp);
}

/* DEREGISTER-ITEM-ON-NETWORK */
Object deregister_item_on_network(item,icp_interface)
    Object item, icp_interface;
{
    Object icp_socket;

    x_note_fn_call(167,158);
    icp_socket = icp_socket_of_interface_object(icp_interface);
    if (icp_socket && icp_connection_open_p(icp_socket) &&  
	    !TRUEP(icp_connection_being_shutdown_qm(icp_socket)))
	deregister_item_with_socket(item,icp_socket);
    return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-SYSTEM-ITEM */
Object deactivate_for_system_item(system_item)
    Object system_item;
{
    Object do_not_reclaim_runs_while_inactive_entries;
    Declare_special(1);
    Object result;

    x_note_fn_call(167,159);
    if ( !TRUEP(In_suspend_resume_p)) {
	do_not_reclaim_runs_while_inactive_entries = T;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_reclaim_runs_while_inactive_entries,Qdo_not_reclaim_runs_while_inactive_entries,do_not_reclaim_runs_while_inactive_entries,
		0);
	  result = reclaim_icp_object_map_for_registered_item(system_item);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-SYSTEM-ITEM */
Object cleanup_for_system_item(system_item)
    Object system_item;
{
    x_note_fn_call(167,160);
    return reclaim_icp_object_map_for_registered_item(system_item);
}

/* RECLAIM-OBJECT-PASSING-INFO?-VALUE */
Object reclaim_object_passing_info_qm_value(object_passing_info_qm,system_item)
    Object object_passing_info_qm, system_item;
{
    x_note_fn_call(167,161);
    if (object_passing_info_qm) {
	reclaim_icp_object_map_for_registered_item(system_item);
	reclaim_icp_tree_1(ISVREF(object_passing_info_qm,(SI_Long)2L));
	reclaim_object_passing_info_1(object_passing_info_qm);
	set_non_savable_lookup_slot_value(system_item,
		Qobject_passing_info_qm,Nil);
    }
    return VALUES_1(Nil);
}

/* RPC-OBJECT-HANDED-OFF-TO-USER-P */
Object rpc_object_handed_off_to_user_p(rpc_object)
    Object rpc_object;
{
    Object gensymed_symbol;

    x_note_fn_call(167,162);
    gensymed_symbol = get_lookup_slot_value_given_default(rpc_object,
	    Qobject_passing_info_qm,Nil);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : T;
    return VALUES_1(gensymed_symbol);
}

/* G2-RECLAIM-SENDING-RESUMABLE-OBJECT */
Object g2_reclaim_sending_resumable_object varargs_1(int, n)
{
    Object resumable_object;
    Object known_unclogged_p, icp_socket, head_contents_qm, tail_contents;
    Object this_resumable_object, first_1, last_1, next, gensymed_symbol;
    Object previous_cons, this_resumable_object_cons_qm, temp;
    Object rpc_identifier_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(167,163);
    INIT_ARGS_nonrelocating();
    resumable_object = REQUIRED_ARG_nonrelocating();
    known_unclogged_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(known_unclogged_p)) {
	icp_socket = ISVREF(resumable_object,(SI_Long)11L);
	head_contents_qm = ISVREF(icp_socket,(SI_Long)31L);
	if (head_contents_qm) {
	    tail_contents = ISVREF(icp_socket,(SI_Long)32L);
	    this_resumable_object = CAR(head_contents_qm);
	    if (EQ(resumable_object,this_resumable_object)) {
	      next_loop:
		first_1 = ISVREF(icp_socket,(SI_Long)31L);
		last_1 = ISVREF(icp_socket,(SI_Long)32L);
		next = CDR(first_1);
		if ( !TRUEP(first_1))
		    goto end_1;
		else if (EQ(first_1,ISVREF(icp_socket,(SI_Long)31L))) {
		    if (EQ(first_1,last_1))
			CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
		    else {
			gensymed_symbol = CAR(first_1);
			if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,next)) {
			    reclaim_icp_cons_1(first_1);
			    goto end_1;
			}
		    }
		}
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    else {
		previous_cons = ISVREF(icp_socket,(SI_Long)31L);
		this_resumable_object_cons_qm = Nil;
		this_resumable_object = Nil;
	      next_loop_1:
		if ( !TRUEP(previous_cons))
		    goto end_loop_1;
		this_resumable_object_cons_qm = CDR(previous_cons);
		if ( !TRUEP(this_resumable_object_cons_qm))
		    goto end_loop_1;
		this_resumable_object = CAR(this_resumable_object_cons_qm);
		if (EQ(resumable_object,this_resumable_object)) {
		    if (EQ(this_resumable_object_cons_qm,tail_contents))
			SVREF(icp_socket,FIX((SI_Long)32L)) = previous_cons;
		    temp = CDDR(previous_cons);
		    M_CDR(previous_cons) = temp;
		    reclaim_icp_cons_1(this_resumable_object_cons_qm);
		    goto end_2;
		}
		previous_cons = M_CDR(previous_cons);
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	}
    }
    rpc_identifier_qm = ISVREF(resumable_object,(SI_Long)5L);
    if (rpc_identifier_qm) {
	temp = delete_icp_element_1(resumable_object,
		ISVREF(rpc_identifier_qm,(SI_Long)5L));
	SVREF(rpc_identifier_qm,FIX((SI_Long)5L)) = temp;
    }
    return reclaim_sending_resumable_object_internal_1(resumable_object);
}

/* G2-RECLAIM-REMOTE-SIDE-FOR-DEACTIVATE-OBJECT-PASSING */
Object g2_reclaim_remote_side_for_deactivate_object_passing(resumable_object_structure,
	    icp_socket,index_space_name)
    Object resumable_object_structure, icp_socket, index_space_name;
{
    Object output_port, initial_resumable_var, resumable_object_structure_1;
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
    Object result;

    x_note_fn_call(167,164);
    output_port = ISVREF(icp_socket,(SI_Long)4L);
    initial_resumable_var = ISVREF(resumable_object_structure,(SI_Long)3L);
    resumable_object_structure_1 = initial_resumable_var;
  next_loop:
    if ( !TRUEP(resumable_object_structure_1))
	goto end_loop;
    current_icp_port = output_port;
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
				send_icp_delete_icp_object_for_process(get_icp_object_index_for_resumable_object(resumable_object_structure_1,
					output_port),index_space_name);
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
    resumable_object_structure_1 = ISVREF(resumable_object_structure_1,
	    (SI_Long)3L);
    goto next_loop;
  end_loop:;
    initial_resumable_var = ISVREF(resumable_object_structure,(SI_Long)4L);
    resumable_object_structure_1 = initial_resumable_var;
  next_loop_1:
    if ( !TRUEP(resumable_object_structure_1))
	goto end_loop_1;
    current_icp_port = output_port;
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
				send_icp_delete_icp_object_for_process(get_icp_object_index_for_resumable_object(resumable_object_structure_1,
					output_port),index_space_name);
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
    resumable_object_structure_1 = ISVREF(resumable_object_structure_1,
	    (SI_Long)4L);
    goto next_loop_1;
  end_loop_1:;
    current_icp_port = output_port;
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
				temp = 
					send_icp_delete_icp_object_for_process(get_icp_object_index_for_resumable_object(resumable_object_structure,
					output_port),index_space_name);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
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
			    result = VALUES_1(temp);
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
    return result;
}

static Object Qcall;               /* call */

static Object Qstart;              /* start */

static Object string_constant_1;   /* "An error occurred while attempting to register ~NF ~
				    *                       on the network: ~A"
				    */

static Object string_constant_2;   /* "An error occurred while attempting to register ~
				    *                       an argument on the network: ~A"
				    */

/* RECEIVE-OBJECT-PASSING-REMOTE-PROCEDURE-ERROR */
Object receive_object_passing_remote_procedure_error(resumable_object_structure,
	    name,error_string)
    Object resumable_object_structure, name, error_string;
{
    Object rpc_arglist_qm, continuation_tag_qm, bad_object, x2;
    Object error_string_with_prologue;
    char temp;

    x_note_fn_call(167,165);
    rpc_arglist_qm = ISVREF(resumable_object_structure,(SI_Long)9L);
    continuation_tag_qm = rpc_arglist_qm ? ISVREF(rpc_arglist_qm,
	    (SI_Long)2L) : Qnil;
    if (EQ(continuation_tag_qm,Qcall))
	return receive_remote_procedure_error_for_caller(ISVREF(rpc_arglist_qm,
		(SI_Long)4L),Nil,name,FIX((SI_Long)1L),error_string);
    else if (EQ(continuation_tag_qm,Qreturn))
	return remote_procedure_error(ISVREF(resumable_object_structure,
		(SI_Long)11L),name,error_string,ISVREF(rpc_arglist_qm,
		(SI_Long)5L));
    else if (EQ(continuation_tag_qm,Qstart))
	return receive_remote_procedure_error(ISVREF(resumable_object_structure,
		(SI_Long)11L),name,FIX((SI_Long)1L),error_string,Nil);
    else {
	bad_object = ISVREF(resumable_object_structure,(SI_Long)8L);
	if (SIMPLE_VECTOR_P(bad_object) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(bad_object)) > (SI_Long)2L 
		&&  !EQ(ISVREF(bad_object,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(bad_object,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	error_string_with_prologue = temp ? tformat_text_string(3,
		string_constant_1,bad_object,error_string) : 
		tformat_text_string(2,string_constant_2,error_string);
	receive_remote_procedure_error(ISVREF(resumable_object_structure,
		(SI_Long)11L),name,FIX((SI_Long)1L),
		error_string_with_prologue,Nil);
	return reclaim_text_string(error_string_with_prologue);
    }
}

/* G2-ATTACH-RESUMABLE-CHILD-NODE-TO-PARENT */
Object g2_attach_resumable_child_node_to_parent(child_node,parent_node)
    Object child_node, parent_node;
{
    Object new_tail, last_cons_qm, cdr_arg;

    x_note_fn_call(167,166);
    new_tail = icp_cons_1(child_node,Nil);
    last_cons_qm = ISVREF(parent_node,(SI_Long)15L);
    if (last_cons_qm) {
	cdr_arg = ISVREF(parent_node,(SI_Long)15L);
	M_CDR(cdr_arg) = new_tail;
    }
    else
	SVREF(parent_node,FIX((SI_Long)13L)) = new_tail;
    SVREF(parent_node,FIX((SI_Long)15L)) = new_tail;
    return VALUES_1(Nil);
}

static Object QFLOAT;              /* |float| */

static Object Qtext;               /* text */

static Object Qtruth;              /* truth */

/* G2-SET-RESUMABLE-NODE-HOMOGENEOUS-ELEMENT-TYPE */
Object g2_set_resumable_node_homogeneous_element_type(attribute_node,attribute)
    Object attribute_node, attribute;
{
    Object gensymed_symbol, sub_class_bit_vector, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,167);
    gensymed_symbol = ISVREF(attribute,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
	svref_new_value = Qinteger;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    svref_new_value = QFLOAT;
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Text_array_class_description,(SI_Long)18L));
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
		svref_new_value = Qtext;
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Truth_value_array_class_description,
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
		    svref_new_value = Qtruth;
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Symbol_array_class_description,
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
			svref_new_value = Qsymbol;
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Integer_list_class_description,
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
			if (temp)
			    svref_new_value = Qinteger;
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Float_list_class_description,
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
			    if (temp)
				svref_new_value = QFLOAT;
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Text_list_class_description,
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
				    svref_new_value = Qtext;
				else {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Truth_value_list_class_description,
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
					temp = (SI_Long)0L < gensymed_symbol_1;
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp)
					svref_new_value = Qtruth;
				    else {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(Symbol_list_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
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
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
					if (temp)
					    svref_new_value = Qsymbol;
					else {
					    sub_class_bit_vector = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)19L);
					    superior_class_bit_number = 
						    IFIX(ISVREF(Integer_parameter_class_description,
						    (SI_Long)18L));
					    sub_class_vector_index = 
						    superior_class_bit_number 
						    >>  -  - (SI_Long)3L;
					    if (sub_class_vector_index < 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							{
						gensymed_symbol_1 = 
							UBYTE_8_ISAREF_1(sub_class_bit_vector,
							sub_class_vector_index);
						gensymed_symbol_2 = 
							(SI_Long)1L;
						gensymed_symbol_3 = 
							superior_class_bit_number 
							& (SI_Long)7L;
						gensymed_symbol_2 = 
							gensymed_symbol_2 
							<< gensymed_symbol_3;
						gensymed_symbol_1 = 
							gensymed_symbol_1 
							& gensymed_symbol_2;
						temp = (SI_Long)0L < 
							gensymed_symbol_1;
					    }
					    else
						temp = TRUEP(Nil);
					    if (temp)
						svref_new_value = Qinteger;
					    else {
						sub_class_bit_vector = 
							ISVREF(gensymed_symbol,
							(SI_Long)19L);
						superior_class_bit_number 
							= 
							IFIX(ISVREF(Integer_variable_class_description,
							(SI_Long)18L));
						sub_class_vector_index = 
							superior_class_bit_number 
							>>  -  - (SI_Long)3L;
						if (sub_class_vector_index 
							< 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							    {
						    gensymed_symbol_1 = 
							    UBYTE_8_ISAREF_1(sub_class_bit_vector,
							    sub_class_vector_index);
						    gensymed_symbol_2 = 
							    (SI_Long)1L;
						    gensymed_symbol_3 = 
							    superior_class_bit_number 
							    & (SI_Long)7L;
						    gensymed_symbol_2 = 
							    gensymed_symbol_2 
							    << 
							    gensymed_symbol_3;
						    gensymed_symbol_1 = 
							    gensymed_symbol_1 
							    & 
							    gensymed_symbol_2;
						    temp = (SI_Long)0L < 
							    gensymed_symbol_1;
						}
						else
						    temp = TRUEP(Nil);
						if (temp)
						    svref_new_value = Qinteger;
						else {
						    sub_class_bit_vector = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)19L);
						    superior_class_bit_number 
							    = 
							    IFIX(ISVREF(Float_parameter_class_description,
							    (SI_Long)18L));
						    sub_class_vector_index 
							    = 
							    superior_class_bit_number 
							    >>  -  - 
							    (SI_Long)3L;
						    if (sub_class_vector_index 
							    < 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								{
							gensymed_symbol_1 
								= 
								UBYTE_8_ISAREF_1(sub_class_bit_vector,
								sub_class_vector_index);
							gensymed_symbol_2 
								= (SI_Long)1L;
							gensymed_symbol_3 
								= 
								superior_class_bit_number 
								& (SI_Long)7L;
							gensymed_symbol_2 
								= 
								gensymed_symbol_2 
								<< 
								gensymed_symbol_3;
							gensymed_symbol_1 
								= 
								gensymed_symbol_1 
								& 
								gensymed_symbol_2;
							temp = (SI_Long)0L 
								< 
								gensymed_symbol_1;
						    }
						    else
							temp = TRUEP(Nil);
						    if (temp)
							svref_new_value = 
								QFLOAT;
						    else {
							sub_class_bit_vector 
								= 
								ISVREF(gensymed_symbol,
								(SI_Long)19L);
							superior_class_bit_number 
								= 
								IFIX(ISVREF(Float_variable_class_description,
								(SI_Long)18L));
							sub_class_vector_index 
								= 
								superior_class_bit_number 
								>>  -  - 
								(SI_Long)3L;
							if (sub_class_vector_index 
								< 
								IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								    {
							    gensymed_symbol_1 
								    = 
								    UBYTE_8_ISAREF_1(sub_class_bit_vector,
								    sub_class_vector_index);
							    gensymed_symbol_2 
								    = 
								    (SI_Long)1L;
							    gensymed_symbol_3 
								    = 
								    superior_class_bit_number 
								    & 
								    (SI_Long)7L;
							    gensymed_symbol_2 
								    = 
								    gensymed_symbol_2 
								    << 
								    gensymed_symbol_3;
							    gensymed_symbol_1 
								    = 
								    gensymed_symbol_1 
								    & 
								    gensymed_symbol_2;
							    temp = 
								    (SI_Long)0L 
								    < 
								    gensymed_symbol_1;
							}
							else
							    temp = TRUEP(Nil);
							if (temp)
							    svref_new_value 
								    = QFLOAT;
							else {
							    sub_class_bit_vector 
								    = 
								    ISVREF(gensymed_symbol,
								    (SI_Long)19L);
							    superior_class_bit_number 
								    = 
								    IFIX(ISVREF(Text_parameter_class_description,
								    (SI_Long)18L));
							    sub_class_vector_index 
								    = 
								    superior_class_bit_number 
								    >>  -  
								    - 
								    (SI_Long)3L;
							    if (sub_class_vector_index 
								    < 
								    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
									{
								gensymed_symbol_1 
									= 
									UBYTE_8_ISAREF_1(sub_class_bit_vector,
									sub_class_vector_index);
								gensymed_symbol_2 
									= 
									(SI_Long)1L;
								gensymed_symbol_3 
									= 
									superior_class_bit_number 
									& 
									(SI_Long)7L;
								gensymed_symbol_2 
									= 
									gensymed_symbol_2 
									<< 
									gensymed_symbol_3;
								gensymed_symbol_1 
									= 
									gensymed_symbol_1 
									& 
									gensymed_symbol_2;
								temp = 
									(SI_Long)0L 
									< 
									gensymed_symbol_1;
							    }
							    else
								temp = 
									TRUEP(Nil);
							    if (temp)
								svref_new_value 
									= 
									Qtext;
							    else {
								sub_class_bit_vector 
									= 
									ISVREF(gensymed_symbol,
									(SI_Long)19L);
								superior_class_bit_number 
									= 
									IFIX(ISVREF(Text_variable_class_description,
									(SI_Long)18L));
								sub_class_vector_index 
									= 
									superior_class_bit_number 
									>> 
									 - 
									 - 
									(SI_Long)3L;
								if (sub_class_vector_index 
									< 
									IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
									    {
								    gensymed_symbol_1 
									    = 
									    UBYTE_8_ISAREF_1(sub_class_bit_vector,
									    sub_class_vector_index);
								    gensymed_symbol_2 
									    = 
									    (SI_Long)1L;
								    gensymed_symbol_3 
									    = 
									    superior_class_bit_number 
									    & 
									    (SI_Long)7L;
								    gensymed_symbol_2 
									    = 
									    gensymed_symbol_2 
									    << 
									    gensymed_symbol_3;
								    gensymed_symbol_1 
									    = 
									    gensymed_symbol_1 
									    & 
									    gensymed_symbol_2;
								    temp = 
									    (SI_Long)0L 
									    < 
									    gensymed_symbol_1;
								}
								else
								    temp = 
									    TRUEP(Nil);
								if (temp)
								    svref_new_value 
									    = 
									    Qtext;
								else {
								    sub_class_bit_vector 
									    = 
									    ISVREF(gensymed_symbol,
									    (SI_Long)19L);
								    superior_class_bit_number 
									    = 
									    IFIX(ISVREF(Logical_parameter_class_description,
									    (SI_Long)18L));
								    sub_class_vector_index 
									    = 
									    superior_class_bit_number 
									    >> 
									     
									    - 
									     
									    - 
									    (SI_Long)3L;
								    if (sub_class_vector_index 
									    < 
									    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
										{
									gensymed_symbol_1 
										= 
										UBYTE_8_ISAREF_1(sub_class_bit_vector,
										sub_class_vector_index);
									gensymed_symbol_2 
										= 
										(SI_Long)1L;
									gensymed_symbol_3 
										= 
										superior_class_bit_number 
										& 
										(SI_Long)7L;
									gensymed_symbol_2 
										= 
										gensymed_symbol_2 
										<< 
										gensymed_symbol_3;
									gensymed_symbol_1 
										= 
										gensymed_symbol_1 
										& 
										gensymed_symbol_2;
									temp 
										= 
										(SI_Long)0L 
										< 
										gensymed_symbol_1;
								    }
								    else
									temp 
										= 
										TRUEP(Nil);
								    if (temp)
									svref_new_value 
										= 
										Qtruth;
								    else {
									sub_class_bit_vector 
										= 
										ISVREF(gensymed_symbol,
										(SI_Long)19L);
									superior_class_bit_number 
										= 
										IFIX(ISVREF(Logical_variable_class_description,
										(SI_Long)18L));
									sub_class_vector_index 
										= 
										superior_class_bit_number 
										>> 
										 
										- 
										 
										- 
										(SI_Long)3L;
									if (sub_class_vector_index 
										< 
										IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
										    {
									    gensymed_symbol_1 
										    = 
										    UBYTE_8_ISAREF_1(sub_class_bit_vector,
										    sub_class_vector_index);
									    gensymed_symbol_2 
										    = 
										    (SI_Long)1L;
									    gensymed_symbol_3 
										    = 
										    superior_class_bit_number 
										    & 
										    (SI_Long)7L;
									    gensymed_symbol_2 
										    = 
										    gensymed_symbol_2 
										    << 
										    gensymed_symbol_3;
									    gensymed_symbol_1 
										    = 
										    gensymed_symbol_1 
										    & 
										    gensymed_symbol_2;
									    temp 
										    = 
										    (SI_Long)0L 
										    < 
										    gensymed_symbol_1;
									}
									else
									    temp 
										    = 
										    TRUEP(Nil);
									if (temp)
									    svref_new_value 
										    = 
										    Qtruth;
									else {
									    sub_class_bit_vector 
										    = 
										    ISVREF(gensymed_symbol,
										    (SI_Long)19L);
									    superior_class_bit_number 
										    = 
										    IFIX(ISVREF(Symbolic_parameter_class_description,
										    (SI_Long)18L));
									    sub_class_vector_index 
										    = 
										    superior_class_bit_number 
										    >> 
										     
										    - 
										     
										    - 
										    (SI_Long)3L;
									    if (sub_class_vector_index 
										    < 
										    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
											{
										gensymed_symbol_1 
											= 
											UBYTE_8_ISAREF_1(sub_class_bit_vector,
											sub_class_vector_index);
										gensymed_symbol_2 
											= 
											(SI_Long)1L;
										gensymed_symbol_3 
											= 
											superior_class_bit_number 
											& 
											(SI_Long)7L;
										gensymed_symbol_2 
											= 
											gensymed_symbol_2 
											<< 
											gensymed_symbol_3;
										gensymed_symbol_1 
											= 
											gensymed_symbol_1 
											& 
											gensymed_symbol_2;
										temp 
											= 
											(SI_Long)0L 
											< 
											gensymed_symbol_1;
									    }
									    else
										temp 
											= 
											TRUEP(Nil);
									    if (temp)
										svref_new_value 
											= 
											Qsymbol;
									    else {
										sub_class_bit_vector 
											= 
											ISVREF(gensymed_symbol,
											(SI_Long)19L);
										superior_class_bit_number 
											= 
											IFIX(ISVREF(Symbolic_variable_class_description,
											(SI_Long)18L));
										sub_class_vector_index 
											= 
											superior_class_bit_number 
											>> 
											 
											- 
											 
											- 
											(SI_Long)3L;
										if (sub_class_vector_index 
											< 
											IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
											    {
										    gensymed_symbol_1 
											    = 
											    UBYTE_8_ISAREF_1(sub_class_bit_vector,
											    sub_class_vector_index);
										    gensymed_symbol_2 
											    = 
											    (SI_Long)1L;
										    gensymed_symbol_3 
											    = 
											    superior_class_bit_number 
											    & 
											    (SI_Long)7L;
										    gensymed_symbol_2 
											    = 
											    gensymed_symbol_2 
											    << 
											    gensymed_symbol_3;
										    gensymed_symbol_1 
											    = 
											    gensymed_symbol_1 
											    & 
											    gensymed_symbol_2;
										    temp 
											    = 
											    (SI_Long)0L 
											    < 
											    gensymed_symbol_1;
										}
										else
										    temp 
											    = 
											    TRUEP(Nil);
										if (temp)
										    svref_new_value 
											    = 
											    Qsymbol;
										else
										    svref_new_value 
											    = 
											    Nil;
									    }
									}
								    }
								}
							    }
							}
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    SVREF(attribute_node,FIX((SI_Long)19L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qvector_element;     /* vector-element */

static Object Qattribute;          /* attribute */

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object list_constant;       /* # */

/* COUNT-OF-SYMBOLIC-ATTRIBUTES */
Object count_of_symbolic_attributes(attribute_specs)
    Object attribute_specs;
{
    Object attribute_spec, ab_loop_list_, temp, type;
    SI_Long ab_loopvar_;

    x_note_fn_call(167,168);
    attribute_spec = Nil;
    ab_loop_list_ = attribute_specs;
    ab_loopvar_ = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUMP(attribute_spec))
	temp = Qvector_element;
    else if (SYMBOLP(attribute_spec))
	temp = Qattribute;
    else if (CONSP(attribute_spec)) {
	type = M_CAR(attribute_spec);
	temp = EQ(type,Qclass_qualified_name) ? Qattribute : type;
    }
    else
	temp = Qnil;
    if (EQ(temp,Qattribute) ?  !TRUEP(memq_function(CONSP(attribute_spec) ?
	     THIRD(attribute_spec) : attribute_spec,list_constant)) : 
	    TRUEP(Nil))
	ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = FIX(ab_loopvar_);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qhistory;            /* history */

static Object Kabort_preflighting_resumable_object;  /* :abort-preflighting-resumable-object */

static Object Qsending_a_non_object_by_copy_to_a_pre_release_5_g2_or_gsi;  /* sending-a-non-object-by-copy-to-a-pre-release-5-g2-or-gsi */

static Object string_constant_3;   /* "~NF is not an object" */

/* GET-RESUMABLE-CHILD-NODE */
Object get_resumable_child_node(attribute_name,child_object_or_value,
	    current_node,resumable_object,last_attribute_p)
    Object attribute_name, child_object_or_value, current_node;
    Object resumable_object, last_attribute_p;
{
    Object x2, icp_object_index_qm, temp_1, serial_number, includes, excludes;
    Object system_includes, inferior_attribute_names_qm, class_of_attribute;
    Object grandparent, child_node, gensymed_symbol, sub_class_bit_vector;
    Object resumable_instance_current_object;
    Object resumable_instance_reference_serial_number, current_attribute_names;
    Object symbolic_attribute_count, resumable_attribute_spec_qm;
    Object resumable_instance_class_name, resumable_sequence_length;
    Object internal_vector_for_object_passing, resumable_node_parent_node_qm;
    Object value_vector_node, svref_new_value, internal_attribute_vector;
    Object object_vector_node, history_spec_qm, history_enclosure_qm;
    Object history_qm, temp_2, temp_3, old_list, new_list;
    Object exported_attribute_names;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,169);
    if (SIMPLE_VECTOR_P(child_object_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(child_object_or_value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(child_object_or_value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(child_object_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    icp_object_index_qm = temp ? 
	    get_index_of_circular_resumable_node(child_object_or_value,
	    resumable_object) : Nil;
    if (icp_object_index_qm)
	temp_1 = make_resumable_circular_node_1(attribute_name,
		icp_object_index_qm,current_node);
    else {
	if (SIMPLE_VECTOR_P(child_object_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(child_object_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(child_object_or_value,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(child_object_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    serial_number = ISVREF(child_object_or_value,(SI_Long)3L);
	    includes = ISVREF(resumable_object,(SI_Long)20L);
	    excludes = ISVREF(resumable_object,(SI_Long)21L);
	    system_includes = ISVREF(resumable_object,(SI_Long)22L);
	    inferior_attribute_names_qm = 
		    get_attribute_names_for_object_passing(child_object_or_value,
		    includes,excludes,system_includes);
	    class_of_attribute = ISVREF(ISVREF(child_object_or_value,
		    (SI_Long)1L),(SI_Long)1L);
	    grandparent = ISVREF(current_node,(SI_Long)1L);
	    child_node = Nil;
	    gensymed_symbol = ISVREF(child_object_or_value,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
		resumable_instance_current_object = child_object_or_value;
		resumable_instance_reference_serial_number = 
			copy_frame_serial_number(serial_number);
		current_attribute_names = inferior_attribute_names_qm;
		symbolic_attribute_count = 
			count_of_symbolic_attributes(inferior_attribute_names_qm);
		resumable_attribute_spec_qm = attribute_name;
		resumable_instance_class_name = class_of_attribute;
		resumable_sequence_length = ISVREF(child_object_or_value,
			(SI_Long)20L);
		if ( !TRUEP(ISVREF(child_object_or_value,(SI_Long)23L)))
		    initialize_g2_array(child_object_or_value);
		internal_vector_for_object_passing = 
			ISVREF(child_object_or_value,(SI_Long)23L);
		resumable_node_parent_node_qm = current_node;
		value_vector_node = 
			make_resumable_value_vector_node_internal_1(resumable_instance_current_object,
			resumable_instance_reference_serial_number,
			current_attribute_names,symbolic_attribute_count,
			resumable_attribute_spec_qm,
			resumable_instance_class_name,
			resumable_sequence_length,
			internal_vector_for_object_passing,
			resumable_node_parent_node_qm);
		svref_new_value = sub1(resumable_sequence_length);
		SVREF(value_vector_node,FIX((SI_Long)21L)) = svref_new_value;
		child_node = value_vector_node;
		g2_set_resumable_node_homogeneous_element_type(child_node,
			child_object_or_value);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Item_array_class_description,
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
		if (temp);
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(G2_array_class_description,
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
		}
		if (temp) {
		    if ( !TRUEP(ISVREF(child_object_or_value,(SI_Long)23L)))
			initialize_g2_array(child_object_or_value);
		    internal_attribute_vector = 
			    ISVREF(child_object_or_value,(SI_Long)23L);
		    resumable_instance_current_object = child_object_or_value;
		    resumable_instance_reference_serial_number = 
			    copy_frame_serial_number(serial_number);
		    current_attribute_names = inferior_attribute_names_qm;
		    symbolic_attribute_count = 
			    count_of_symbolic_attributes(inferior_attribute_names_qm);
		    resumable_attribute_spec_qm = attribute_name;
		    resumable_instance_class_name = class_of_attribute;
		    resumable_sequence_length = 
			    ISVREF(child_object_or_value,(SI_Long)20L);
		    internal_vector_for_object_passing = 
			    internal_attribute_vector;
		    resumable_node_parent_node_qm = current_node;
		    object_vector_node = 
			    make_resumable_object_vector_node_internal_1(resumable_instance_current_object,
			    resumable_instance_reference_serial_number,
			    current_attribute_names,
			    symbolic_attribute_count,
			    resumable_attribute_spec_qm,
			    resumable_instance_class_name,
			    resumable_sequence_length,
			    internal_vector_for_object_passing,
			    resumable_node_parent_node_qm);
		    svref_new_value = sub1(resumable_sequence_length);
		    SVREF(object_vector_node,FIX((SI_Long)22L)) = 
			    svref_new_value;
		    child_node = object_vector_node;
		}
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
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
		    if (temp) {
			history_spec_qm = ISVREF(child_object_or_value,
				(SI_Long)25L);
			if (history_spec_qm && memq_function(Qhistory,
				system_includes)) {
			    temp_1 = copy_frame_serial_number(serial_number);
			    child_node = 
				    make_resumable_history_node_1(child_object_or_value,
				    temp_1,inferior_attribute_names_qm,
				    count_of_symbolic_attributes(inferior_attribute_names_qm),
				    attribute_name,class_of_attribute,
				    FIX((SI_Long)0L),current_node);
			    history_enclosure_qm = 
				    ISVREF(child_object_or_value,(SI_Long)24L);
			    history_qm = 
				    get_history_ring_buffer_if_any(child_object_or_value,
				    Nil);
			    if (history_qm)
				copy_history_state_into_resumable_history_node(child_node,
					history_enclosure_qm,history_qm,
					history_spec_qm);
			    g2_set_resumable_node_homogeneous_element_type(child_node,
				    child_object_or_value);
			}
			else {
			    temp_1 = copy_frame_serial_number(serial_number);
			    child_node = 
				    make_resumable_object_node_1(child_object_or_value,
				    temp_1,inferior_attribute_names_qm,
				    count_of_symbolic_attributes(inferior_attribute_names_qm),
				    attribute_name,class_of_attribute,
				    current_node);
			}
		    }
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Value_list_class_description,
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
			if (temp) {
			    temp_2 = copy_frame_serial_number(serial_number);
			    temp_3 = 
				    count_of_symbolic_attributes(inferior_attribute_names_qm);
			    old_list = ISVREF(child_object_or_value,
				    (SI_Long)20L);
			    if ( !TRUEP(old_list)) {
				new_list = create_empty_g2_list_structure();
				if ( 
					!TRUEP(CAS_SVREF(child_object_or_value,
					(SI_Long)20L,old_list,new_list)))
				    reclaim_empty_g2_list_structure(new_list);
			    }
			    temp_1 = 
				    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ISVREF(child_object_or_value,
				    (SI_Long)20L),(SI_Long)2L),(SI_Long)2L));
			    child_node = 
				    make_resumable_value_list_node_1(child_object_or_value,
				    temp_2,inferior_attribute_names_qm,
				    temp_3,attribute_name,
				    class_of_attribute,temp_1,
				    g2_list_length(child_object_or_value),
				    current_node);
			    g2_set_resumable_node_homogeneous_element_type(child_node,
				    child_object_or_value);
			}
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Item_list_class_description,
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
			    if (temp);
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(G2_list_class_description,
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
			    if (temp) {
				temp_2 = 
					copy_frame_serial_number(serial_number);
				temp_3 = 
					count_of_symbolic_attributes(inferior_attribute_names_qm);
				old_list = ISVREF(child_object_or_value,
					(SI_Long)20L);
				if ( !TRUEP(old_list)) {
				    new_list = 
					    create_empty_g2_list_structure();
				    if ( 
					    !TRUEP(CAS_SVREF(child_object_or_value,
					    (SI_Long)20L,old_list,new_list)))
					reclaim_empty_g2_list_structure(new_list);
				}
				temp_1 = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(ISVREF(child_object_or_value,
					(SI_Long)20L),(SI_Long)2L),
					(SI_Long)2L));
				child_node = 
					make_resumable_object_list_node_1(child_object_or_value,
					temp_2,inferior_attribute_names_qm,
					temp_3,attribute_name,
					class_of_attribute,temp_1,
					g2_list_length(child_object_or_value),
					current_node);
			    }
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Object_class_description,
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
				if (temp) {
				    temp_1 = 
					    copy_frame_serial_number(serial_number);
				    child_node = 
					    make_resumable_object_node_1(child_object_or_value,
					    temp_1,
					    inferior_attribute_names_qm,
					    count_of_symbolic_attributes(inferior_attribute_names_qm),
					    attribute_name,
					    class_of_attribute,current_node);
				}
				else if (ISVREF(gensymed_symbol,
					    (SI_Long)16L)) {
				    temp_1 = ISVREF(Current_icp_socket,
					    (SI_Long)21L);
				    temp_3 = ISVREF(Current_icp_socket,
					    (SI_Long)22L);
				    if (IFIX(FIXNUM_MIN(temp_1,temp_3)) >= 
					    (SI_Long)8L) {
					exported_attribute_names = 
						get_exported_attribute_names_for_object_passing(child_object_or_value,
						includes,excludes,
						system_includes);
					temp_1 = 
						copy_frame_serial_number(serial_number);
					child_node = 
						make_resumable_object_node_1(child_object_or_value,
						temp_1,
						exported_attribute_names,
						length(exported_attribute_names),
						attribute_name,
						class_of_attribute,
						current_node);
				    }
				    else {
					Rpc_throw_tag = 
						Kabort_preflighting_resumable_object;
					return icp_list_2(Qsending_a_non_object_by_copy_to_a_pre_release_5_g2_or_gsi,
						tformat_text_string(2,
						string_constant_3,
						child_object_or_value));
				    }
				}
			    }
			}
		    }
		}
	    }
	    if (last_attribute_p) {
		svref_new_value = icp_cons_1(grandparent,ISVREF(child_node,
			(SI_Long)9L));
		SVREF(child_node,FIX((SI_Long)9L)) = svref_new_value;
		svref_new_value = ISVREF(current_node,(SI_Long)8L);
		SVREF(child_node,FIX((SI_Long)8L)) = svref_new_value;
	    }
	    else {
		svref_new_value = icp_cons_1(Nil,ISVREF(child_node,
			(SI_Long)9L));
		SVREF(child_node,FIX((SI_Long)9L)) = svref_new_value;
		SVREF(child_node,FIX((SI_Long)8L)) = Nil;
	    }
	    temp_1 = child_node;
	}
	else
	    temp_1 = make_resumable_value_node_1(attribute_name,
		    child_object_or_value,current_node);
    }
    return VALUES_1(temp_1);
}

static Object Kfinished_preflighting_resumable_object;  /* :finished-preflighting-resumable-object */

static Object Qicp;                /* icp */

/* SET-RESUMABLE-INSTANCE-ASCENSION */
Object set_resumable_instance_ascension(ascending_node)
    Object ascending_node;
{
    Object temp, final_attribute_qm, final_trailing_edge_object_p, parent_qm;
    Object superiors_qm, temp_1, superior_qm, ab_loop_list_, superior_cons_qm;
    Object highest_superior_qm, highest_superior_cons_qm, ab_loop_iter_flag_;
    Object icp_cons, svref_arg_2;
    SI_Long ascension_count;

    x_note_fn_call(167,170);
    temp = ISVREF(ascending_node,(SI_Long)15L);
    final_attribute_qm = CAR(temp);
    final_trailing_edge_object_p = ISVREF(ascending_node,(SI_Long)8L) ? ( 
	    !(SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(final_attribute_qm) && 
	    EQ(ISVREF(final_attribute_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
	    ? T : Nil) : Qnil;
    parent_qm = ISVREF(ascending_node,(SI_Long)1L);
    superiors_qm = ISVREF(ascending_node,(SI_Long)9L);
    temp_1 = ISVREF(ascending_node,(SI_Long)13L);
    SVREF(ascending_node,FIX((SI_Long)14L)) = temp_1;
    if (parent_qm) {
	temp_1 = ISVREF(parent_qm,(SI_Long)13L);
	SVREF(parent_qm,FIX((SI_Long)14L)) = temp_1;
    }
    SVREF(ascending_node,FIX((SI_Long)9L)) = Nil;
    if (SIMPLE_VECTOR_P(ascending_node) && EQ(ISVREF(ascending_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
	ISVREF(ascending_node,(SI_Long)21L) = FIX((SI_Long)0L);
    if (final_trailing_edge_object_p) {
	reclaim_icp_list_1(superiors_qm);
	if (parent_qm) {
	    superior_qm = ISVREF(parent_qm,(SI_Long)1L);
	  next_loop:
	    if ( !TRUEP(superior_qm))
		goto end_loop;
	    if (SIMPLE_VECTOR_P(superior_qm) && EQ(ISVREF(superior_qm,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
		ISVREF(superior_qm,(SI_Long)21L) = FIX((SI_Long)0L);
	    temp_1 = ISVREF(superior_qm,(SI_Long)13L);
	    SVREF(superior_qm,FIX((SI_Long)14L)) = temp_1;
	    SVREF(superior_qm,FIX((SI_Long)9L)) = Nil;
	    superior_qm = ISVREF(superior_qm,(SI_Long)1L);
	    goto next_loop;
	  end_loop:;
	}
	Rpc_throw_tag = Kfinished_preflighting_resumable_object;
	return VALUES_1(T);
    }
    else {
	superior_qm = Nil;
	ab_loop_list_ = superiors_qm;
	superior_cons_qm = superiors_qm;
	highest_superior_qm = Nil;
	highest_superior_cons_qm = Nil;
	ascension_count = (SI_Long)2L;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	superior_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    superior_cons_qm = M_CDR(superior_cons_qm);
	if ( !TRUEP(superior_cons_qm))
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_iter_flag_))
	    ascension_count = ascension_count + (SI_Long)1L;
	if ( !TRUEP(superior_qm))
	    goto end_loop_1;
	highest_superior_qm = superior_qm;
	highest_superior_cons_qm = superior_cons_qm;
	temp_1 = ISVREF(superior_qm,(SI_Long)13L);
	SVREF(superior_qm,FIX((SI_Long)14L)) = temp_1;
	if (CADR(superior_cons_qm) && SIMPLE_VECTOR_P(superior_qm) && 
		EQ(ISVREF(superior_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
	    ISVREF(superior_qm,(SI_Long)21L) = FIX((SI_Long)0L);
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:
	if (highest_superior_qm) {
	    SVREF(ascending_node,FIX((SI_Long)6L)) = highest_superior_qm;
	    ISVREF(ascending_node,(SI_Long)7L) = FIX(ascension_count);
	    M_CDR(highest_superior_cons_qm) = Nil;
	    if (parent_qm && SIMPLE_VECTOR_P(parent_qm) && 
		    EQ(ISVREF(parent_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct))
		ISVREF(parent_qm,(SI_Long)21L) = FIX((SI_Long)0L);
	    if (superiors_qm &&  !((SI_Long)0L == 
			inline_debugging_consing())) {
		icp_cons = superiors_qm;
	      next_loop_2:
		inline_note_reclaim_cons(icp_cons,Qicp);
		if (EQ(icp_cons,highest_superior_cons_qm))
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
		temp_1 = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = superiors_qm;
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = highest_superior_cons_qm;
	    }
	    else {
		temp_1 = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = superiors_qm;
		temp_1 = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = highest_superior_cons_qm;
	    }
	    M_CDR(highest_superior_cons_qm) = Nil;
	}
	else {
	    SVREF(ascending_node,FIX((SI_Long)6L)) = parent_qm;
	    ISVREF(ascending_node,(SI_Long)7L) = FIX((SI_Long)1L);
	    if (superiors_qm)
		reclaim_icp_cons_1(superiors_qm);
	}
	return VALUES_1(Qnil);
    }
}

static Object Ksuspend_preflighting_resumable_object;  /* :suspend-preflighting-resumable-object */

static Object Qlist_element;       /* list-element */

/* PREFLIGHT-RESUMABLE-OBJECT */
Object preflight_resumable_object(resumable_object,current_node)
    Object resumable_object, current_node;
{
    Object current_object, attribute_name, last_attribute_p, child;
    Object remaining_attribute_names_qm, icp_pop_store, cons_1, next_cons;
    Object temp, svref_arg_2, highest_index, current_index, contents;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, temp_3, entry_hash, internal_list, list_index;
    Object next_element_qm, possible_throw_value, child_node, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1, list_elements_remain_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(167,171);
    current_object = ISVREF(current_node,(SI_Long)4L);
    attribute_name = Nil;
    last_attribute_p = Nil;
    child = Nil;
  check_timeslice:
    if (time_slice_expired_p()) {
	Rpc_throw_tag = Ksuspend_preflighting_resumable_object;
	return VALUES_1(current_node);
    }
    if (SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct)) {
	remaining_attribute_names_qm = ISVREF(current_node,(SI_Long)16L);
	if (remaining_attribute_names_qm) {
	    attribute_name = CAR(remaining_attribute_names_qm);
	    last_attribute_p =  !TRUEP(CDR(remaining_attribute_names_qm)) ?
		     T : Nil;
	    child = g2_get_attribute_for_object_passing(current_object,
		    attribute_name);
	    icp_pop_store = Nil;
	    cons_1 = ISVREF(current_node,(SI_Long)16L);
	    if (cons_1) {
		icp_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    SVREF(current_node,FIX((SI_Long)16L)) = next_cons;
	    goto attach_child_node;
	}
	else
	    goto ascend_from_current_node;
    }
    else if (SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct)) 
		{
	highest_index = ISVREF(current_node,(SI_Long)22L);
	current_index = ISVREF(current_node,(SI_Long)21L);
	remaining_attribute_names_qm = ISVREF(current_node,(SI_Long)16L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,0);
	  if (FIXNUM_GT(Current_index,highest_index) &&  
		  !TRUEP(remaining_attribute_names_qm)) {
	      POP_SPECIAL();
	      goto ascend_from_current_node;
	  }
	  else if (FIXNUM_GT(Current_index,highest_index)) {
	      attribute_name = CAR(remaining_attribute_names_qm);
	      last_attribute_p =  
		      !TRUEP(CDR(remaining_attribute_names_qm)) ? T : Nil;
	      child = g2_get_attribute_for_object_passing(current_object,
		      attribute_name);
	      icp_pop_store = Nil;
	      cons_1 = ISVREF(current_node,(SI_Long)16L);
	      if (cons_1) {
		  icp_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qicp);
		  if (ISVREF(Available_icp_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = ISVREF(Available_icp_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_icp_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  else {
		      temp = Available_icp_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		      temp = Available_icp_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      SVREF(current_node,FIX((SI_Long)16L)) = next_cons;
	      POP_SPECIAL();
	      goto attach_child_node;
	  }
	  else {
	      attribute_name = gensym_list_2(Qvector_element,Current_index);
	      last_attribute_p = remaining_attribute_names_qm ? Nil : 
		      FIXNUM_EQ(Current_index,highest_index) ? T : Nil;
	      contents = managed_g2_array_aref(ISVREF(current_node,
		      (SI_Long)20L),FIX(IFIX(Current_index) * (SI_Long)2L));
	      gensymed_symbol = contents;
	      temp_1 = FIXNUMP(gensymed_symbol);
	      if (temp_1);
	      else
		  temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			  != (SI_Long)0L ? 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			  == (SI_Long)1L : TRUEP(Qnil);
	      if (temp_1);
	      else
		  temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			  (SI_Long)0L ? 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			  == (SI_Long)1L : TRUEP(Qnil);
	      if (temp_1);
	      else
		  temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			  TRUEP(Qnil);
	      if (temp_1);
	      else
		  temp_1 = 
			  INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			  != (SI_Long)0L;
	      if (temp_1);
	      else if (CONSP(gensymed_symbol)) {
		  gensymed_symbol = M_CDR(gensymed_symbol);
		  temp_1 = EQ(gensymed_symbol,Qtruth_value);
		  if (temp_1);
		  else
		      temp_1 = EQ(gensymed_symbol,Qiteration_state);
		  if (temp_1);
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
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_3 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_3);
		      MVS_2(result,succ,marked);
		    next_loop_2:
		      if ( !TRUEP(marked))
			  goto end_loop_1;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_2 = ATOMIC_REF_OBJECT(reference);
		      temp_3 = (SI_Long)355L == 
			      ATOMIC_REF_STAMP(reference) ? T : Nil;
		      result = VALUES_2(temp_2,temp_3);
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
		      temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			      (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      child = temp_1 ? (FIXNUMP(contents) || contents && 
		      SYMBOLP(contents) ? contents : 
		      copy_evaluation_value_1(contents)) : contents;
	      temp = FIXNUM_ADD1(ISVREF(current_node,(SI_Long)21L));
	      SVREF(current_node,FIX((SI_Long)21L)) = temp;
	      POP_SPECIAL();
	      goto attach_child_node;
	  }
	POP_SPECIAL();
    }
    else if (SIMPLE_VECTOR_P(current_node) && EQ(ISVREF(current_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct)) 
		{
	internal_list = ISVREF(current_node,(SI_Long)20L);
	list_elements_remain_p = EQ(ISVREF(internal_list,(SI_Long)5L),
		current_object);
	remaining_attribute_names_qm = ISVREF(current_node,(SI_Long)16L);
	if ( !list_elements_remain_p &&  !TRUEP(remaining_attribute_names_qm))
	    goto ascend_from_current_node;
	else if ( !list_elements_remain_p) {
	    attribute_name = CAR(remaining_attribute_names_qm);
	    last_attribute_p =  !TRUEP(CDR(remaining_attribute_names_qm)) ?
		     T : Nil;
	    child = g2_get_attribute_for_object_passing(current_object,
		    attribute_name);
	    icp_pop_store = Nil;
	    cons_1 = ISVREF(current_node,(SI_Long)16L);
	    if (cons_1) {
		icp_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    SVREF(current_node,FIX((SI_Long)16L)) = next_cons;
	    goto attach_child_node;
	}
	else {
	    list_index = ISVREF(current_node,(SI_Long)18L);
	    next_element_qm = ATOMIC_REF_OBJECT(ISVREF(internal_list,
		    (SI_Long)2L));
	    if ( !(SIMPLE_VECTOR_P(next_element_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(next_element_qm)) == 
		    (SI_Long)4L))
		goto ascend_from_current_node;
	    attribute_name = gensym_list_2(Qlist_element,list_index);
	    last_attribute_p = remaining_attribute_names_qm ? Nil :  
		    !EQ(ISVREF(next_element_qm,(SI_Long)5L),
		    current_object) ? T : Nil;
	    contents = ISVREF(internal_list,(SI_Long)4L);
	    gensymed_symbol = contents;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp_1);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp_1 = EQ(gensymed_symbol,Qtruth_value);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qiteration_state);
		if (temp_1);
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
		  next_loop_3:
		    if (level < ab_loop_bind_)
			goto end_loop_3;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_4:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
		    MVS_2(result,succ,marked);
		  next_loop_5:
		    if ( !TRUEP(marked))
			goto end_loop_4;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_2,temp_3);
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    child = temp_1 ? (FIXNUMP(contents) || contents && 
		    SYMBOLP(contents) ? contents : 
		    copy_evaluation_value_1(contents)) : contents;
	    SVREF(current_node,FIX((SI_Long)20L)) = next_element_qm;
	    temp = FIXNUM_ADD1(ISVREF(current_node,(SI_Long)18L));
	    SVREF(current_node,FIX((SI_Long)18L)) = temp;
	    goto attach_child_node;
	}
    }
  attach_child_node:
    possible_throw_value = get_resumable_child_node(attribute_name,child,
	    current_node,resumable_object,last_attribute_p);
    if (Rpc_throw_tag)
	return VALUES_1(possible_throw_value);
    child_node = possible_throw_value;
    g2_attach_resumable_child_node_to_parent(child_node,current_node);
    if (SIMPLE_VECTOR_P(child) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(child)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(child,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(child,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if ( !(SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_circular_node_g2_struct)))
	    set_index_of_circular_resumable_node(child,resumable_object,
		    child_node);
    }
    if (SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
	    || SIMPLE_VECTOR_P(child_node) && EQ(ISVREF(child_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
		{
	current_object = child;
	current_node = child_node;
    }
    goto check_timeslice;
  ascend_from_current_node:
    possible_throw_value = set_resumable_instance_ascension(current_node);
    if (Rpc_throw_tag)
	return VALUES_1(possible_throw_value);
    current_node = ISVREF(current_node,(SI_Long)6L);
    current_object = ISVREF(current_node,(SI_Long)4L);
    goto check_timeslice;
    return VALUES_1(Qnil);
}

static Object string_constant_4;   /* "The remote procedure call ~NF has been aborted ~
				    *                    while sending: ~A"
				    */

static Object string_constant_5;   /* "A remote procedure call has been aborted while sending: ~A" */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qtry_to_transmit_resumable_object;  /* try-to-transmit-resumable-object */

static Object Qtry_to_preflight_resumable_object;  /* try-to-preflight-resumable-object */

/* PREFLIGHT-RESUMABLE-OBJECT-WITH-CATCH-HANDLERS */
Object preflight_resumable_object_with_catch_handlers(resumable_object)
    Object resumable_object;
{
    Object rpc_throw_tag, possible_throw_value, gensymed_symbol, abort_info;
    Object rpc_name_qm, error_message, error_string, info, ab_loop_list_, temp;
    Object old, new_1, def_structure_schedule_task_variable, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    Object new_resumable_node;
    char g2_p;
    double aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(167,172);
    rpc_throw_tag = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Rpc_throw_tag,Qrpc_throw_tag,rpc_throw_tag,1);
      possible_throw_value = preflight_resumable_object(resumable_object,
	      ISVREF(resumable_object,(SI_Long)10L));
      if (Rpc_throw_tag) {
	  gensymed_symbol = possible_throw_value;
	  goto end_preflight_resumable_object_with_catch_handlers_body;
      }
      gensymed_symbol = possible_throw_value;
    end_preflight_resumable_object_with_catch_handlers_body:
      if (EQ(Rpc_throw_tag,Kabort_preflighting_resumable_object)) {
	  abort_info = gensymed_symbol;
	  rpc_name_qm = ISVREF(resumable_object,(SI_Long)1L);
	  error_message = SECOND(abort_info);
	  error_string = rpc_name_qm ? tformat_text_string(3,
		  string_constant_4,rpc_name_qm,error_message) : 
		  tformat_text_string(2,string_constant_5,error_message);
	  receive_object_passing_remote_procedure_error(resumable_object,
		  FIRST(abort_info),error_string);
	  info = Nil;
	  ab_loop_list_ = abort_info;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  info = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (text_string_p(info))
	      reclaim_text_string(info);
	  goto next_loop;
	end_loop:
	  reclaim_icp_list_1(abort_info);
	  reclaim_text_string(error_string);
	  result = reclaim_sending_and_receiving_resumable_object(resumable_object);
      }
      else if (EQ(Rpc_throw_tag,Kfinished_preflighting_resumable_object)) {
	  temp = ISVREF(resumable_object,(SI_Long)9L);
	  SVREF(resumable_object,FIX((SI_Long)10L)) = temp;
	  if (time_slice_expired_p()) {
	      old = Nil;
	      new_1 = Nil;
	    next_loop_1:
	      old = ISVREF(resumable_object,(SI_Long)19L);
	      def_structure_schedule_task_variable = 
		      ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      if (def_structure_schedule_task_variable) {
		  temp = Chain_of_available_schedule_tasks_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = 
			  ISVREF(def_structure_schedule_task_variable,
			  (SI_Long)0L);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  SVREF(def_structure_schedule_task_variable,
			  FIX((SI_Long)0L)) = 
			  Qg2_defstruct_structure_name_schedule_task_g2_struct;
	      }
	      else
		  def_structure_schedule_task_variable = 
			  make_permanent_schedule_task_structure_internal();
	      inline_note_allocate_cons(def_structure_schedule_task_variable,
		      Nil);
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) 
		      = Nil;
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) 
		      = Nil;
	      task = def_structure_schedule_task_variable;
	      temp = ISVREF(task,(SI_Long)1L);
	      aref_new_value = -1.0;
	      DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	      temp = ISVREF(resumable_object,(SI_Long)14L);
	      SVREF(task,FIX((SI_Long)4L)) = temp;
	      SVREF(task,FIX((SI_Long)5L)) = Nil;
	      SVREF(task,FIX((SI_Long)9L)) = Nil;
	      SVREF(task,FIX((SI_Long)10L)) = Nil;
	      g2_p =  !TRUEP(T);
	      SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	      temp = ISVREF(task,(SI_Long)1L);
	      aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		      Current_real_time,(SI_Long)0L);
	      DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      SVREF(task,FIX((SI_Long)7L)) = Qtry_to_transmit_resumable_object;
	      temp = SYMBOL_FUNCTION(Qtry_to_transmit_resumable_object);
	      SVREF(task,FIX((SI_Long)8L)) = temp;
	      ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	      SVREF(task,FIX((SI_Long)13L)) = resumable_object;
	      new_1 = task;
	      if (CAS_SVREF(resumable_object,(SI_Long)19L,old,new_1)) {
		  task = new_1;
		  ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		  if (ctask);
		  else
		      ctask = System_is_running;
		  p = ISVREF(task,(SI_Long)4L);
		  v = ctask ? Current_task_queue_vector : 
			  Deferred_task_queue_vector;
		  q = ISVREF(v,IFIX(p));
		  SVREF(task,FIX((SI_Long)11L)) = q;
		  temp = constant_queue_push_right(q,task);
		  SVREF(task,FIX((SI_Long)6L)) = temp;
		  if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		      Priority_of_next_task = p;
		  result = VALUES_1(task);
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
	      goto next_loop_1;
	    end_loop_1:
	      result = VALUES_1(Qnil);
	    end_1:;
	  }
	  else
	      result = try_to_transmit_resumable_object(resumable_object);
      }
      else if (EQ(Rpc_throw_tag,Ksuspend_preflighting_resumable_object)) {
	  new_resumable_node = gensymed_symbol;
	  SVREF(resumable_object,FIX((SI_Long)10L)) = new_resumable_node;
	  old = Nil;
	  new_1 = Nil;
	next_loop_2:
	  old = ISVREF(resumable_object,(SI_Long)19L);
	  def_structure_schedule_task_variable = 
		  ISVREF(Chain_of_available_schedule_tasks_vector,
		  IFIX(Current_thread_index));
	  if (def_structure_schedule_task_variable) {
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = 
		      ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	      SVREF(temp,svref_arg_2) = svref_new_value;
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) 
		      = Qg2_defstruct_structure_name_schedule_task_g2_struct;
	  }
	  else
	      def_structure_schedule_task_variable = 
		      make_permanent_schedule_task_structure_internal();
	  inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	  SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	  SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	  task = def_structure_schedule_task_variable;
	  temp = ISVREF(task,(SI_Long)1L);
	  aref_new_value = -1.0;
	  DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	  temp = ISVREF(resumable_object,(SI_Long)14L);
	  SVREF(task,FIX((SI_Long)4L)) = temp;
	  SVREF(task,FIX((SI_Long)5L)) = Nil;
	  SVREF(task,FIX((SI_Long)9L)) = Nil;
	  SVREF(task,FIX((SI_Long)10L)) = Nil;
	  g2_p =  !TRUEP(T);
	  SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	  temp = ISVREF(task,(SI_Long)1L);
	  aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		  Current_real_time,(SI_Long)0L);
	  DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	  SVREF(task,FIX((SI_Long)7L)) = Qtry_to_preflight_resumable_object;
	  temp = SYMBOL_FUNCTION(Qtry_to_preflight_resumable_object);
	  SVREF(task,FIX((SI_Long)8L)) = temp;
	  ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	  SVREF(task,FIX((SI_Long)13L)) = resumable_object;
	  new_1 = task;
	  if (CAS_SVREF(resumable_object,(SI_Long)19L,old,new_1)) {
	      task = new_1;
	      ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	      if (ctask);
	      else
		  ctask = System_is_running;
	      p = ISVREF(task,(SI_Long)4L);
	      v = ctask ? Current_task_queue_vector : 
		      Deferred_task_queue_vector;
	      q = ISVREF(v,IFIX(p));
	      SVREF(task,FIX((SI_Long)11L)) = q;
	      temp = constant_queue_push_right(q,task);
	      SVREF(task,FIX((SI_Long)6L)) = temp;
	      if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		  Priority_of_next_task = p;
	      result = VALUES_1(task);
	      goto end_2;
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
	  goto next_loop_2;
	end_loop_2:
	  result = VALUES_1(Qnil);
	end_2:;
      }
      else
	  result = VALUES_1(gensymed_symbol);
    POP_SPECIAL();
    return result;
}

/* TRY-TO-PREFLIGHT-RESUMABLE-OBJECT */
Object try_to_preflight_resumable_object(resumable_object)
    Object resumable_object;
{
    Object object, gensymed_symbol, x, y, xa, ya, current_icp_socket;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(167,173);
    object = ISVREF(resumable_object,(SI_Long)8L);
    temp = CONSP(object);
    if (temp);
    else {
	gensymed_symbol = ISVREF(object,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(object) ? EQ(ISVREF(object,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(resumable_object,(SI_Long)6L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    if ( !temp)
	return g2_reclaim_sending_resumable_object(1,resumable_object);
    else {
	current_icp_socket = ISVREF(resumable_object,(SI_Long)11L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		0);
	  result = preflight_resumable_object_with_catch_handlers(resumable_object);
	POP_SPECIAL();
	return result;
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Rpc_object_arguments_to_run_or_schedule_qm, Qrpc_object_arguments_to_run_or_schedule_qm);

/* SEND-DEFERRED-RPC-OBJECTS-IF-ANY */
Object send_deferred_rpc_objects_if_any()
{
    Object rpc_object, ab_loop_list_;

    x_note_fn_call(167,174);
    if (Rpc_object_arguments_to_run_or_schedule_qm) {
	rpc_object = Nil;
	ab_loop_list_ = Rpc_object_arguments_to_run_or_schedule_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	rpc_object = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	try_to_preflight_resumable_object(rpc_object);
	goto next_loop;
      end_loop:
	reclaim_icp_list_1(Rpc_object_arguments_to_run_or_schedule_qm);
	Rpc_object_arguments_to_run_or_schedule_qm = Nil;
    }
    return VALUES_1(Nil);
}

/* SEND-ICP-RPC-START-DEFERRING-OBJECTS */
Object send_icp_rpc_start_deferring_objects(icp_output_port,
	    remote_procedure_name,rpc_argument_list)
    Object icp_output_port, remote_procedure_name, rpc_argument_list;
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

    x_note_fn_call(167,175);
    current_icp_port = icp_output_port;
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
				send_icp_rpc_start(remote_procedure_name,
					rpc_argument_list);
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
    send_deferred_rpc_objects_if_any();
    return VALUES_1(Nil);
}

/* SEND-ICP-RPC-CALL-DEFERRING-OBJECTS */
Object send_icp_rpc_call_deferring_objects(icp_output_port,
	    remote_procedure_name,remote_procedure_identifier,
	    rpc_argument_list)
    Object icp_output_port, remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
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

    x_note_fn_call(167,176);
    current_icp_port = icp_output_port;
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
				send_icp_rpc_call(remote_procedure_name,
					remote_procedure_identifier,
					rpc_argument_list);
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
    send_deferred_rpc_objects_if_any();
    return VALUES_1(Nil);
}

/* SEND-ICP-RPC-RETURN-VALUES-DEFERRING-OBJECTS */
Object send_icp_rpc_return_values_deferring_objects(icp_output_port,
	    calling_procedure_index,return_values_list)
    Object icp_output_port, calling_procedure_index, return_values_list;
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

    x_note_fn_call(167,177);
    current_icp_port = icp_output_port;
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
				send_icp_rpc_return_values(calling_procedure_index,
					return_values_list);
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
    send_deferred_rpc_objects_if_any();
    return VALUES_1(Nil);
}

static Object Qreference;          /* reference */

/* G2-WRITE-ICP-RPC-VALUE-OR-OBJECT */
Object g2_write_icp_rpc_value_or_object(rpc_value_or_object)
    Object rpc_value_or_object;
{
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash, kind;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(167,178);
    gensymed_symbol = rpc_value_or_object;
    temp = FIXNUMP(gensymed_symbol);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L : TRUEP(Qnil);
    if (temp);
    else
	temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
    if (temp);
    else
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L;
    if (temp);
    else if (CONSP(gensymed_symbol)) {
	gensymed_symbol = M_CDR(gensymed_symbol);
	temp = EQ(gensymed_symbol,Qtruth_value);
	if (temp);
	else
	    temp = EQ(gensymed_symbol,Qiteration_state);
	if (temp);
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
	    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	write_icp_remote_value(rpc_value_or_object);
    else if ( !(SIMPLE_VECTOR_P(rpc_value_or_object) && 
	    EQ(ISVREF(rpc_value_or_object,(SI_Long)0L),
	    Qg2_defstruct_structure_name_sending_resumable_object_g2_struct)))
	write_icp_byte(Rpc_unknown_type_tag);
    else if (ISVREF(rpc_value_or_object,(SI_Long)2L)) {
	kind = ISVREF(rpc_value_or_object,(SI_Long)2L);
	if (EQ(Qreference,kind))
	    write_icp_remote_value(ISVREF(rpc_value_or_object,(SI_Long)8L));
	else {
	    write_icp_byte(Rpc_object_handle_type_tag);
	    write_icp_fixnum(ISVREF(rpc_value_or_object,(SI_Long)8L));
	}
	g2_reclaim_sending_resumable_object(1,rpc_value_or_object);
    }
    else {
	write_icp_byte(Rpc_object_type_tag);
	write_icp_unsigned_integer(ISVREF(rpc_value_or_object,(SI_Long)12L));
	Rpc_object_arguments_to_run_or_schedule_qm = 
		icp_cons_1(rpc_value_or_object,
		Rpc_object_arguments_to_run_or_schedule_qm);
    }
    return VALUES_1(Nil);
}

/* G2-RESUME-CLOGGED-RESUMABLE-OBJECT-TASKS */
Object g2_resume_clogged_resumable_object_tasks()
{
    Object icp_socket, temp, first_resumable_object_qm, temp_1, first_1;
    Object last_1, next, waiting_object_qm, gensymed_symbol, old, new_1;
    Object def_structure_schedule_task_variable, temp_3, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char temp_2, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(167,179);
    icp_socket = Current_icp_socket;
    temp = ISVREF(icp_socket,(SI_Long)31L);
    first_resumable_object_qm = CAR(temp);
    if (first_resumable_object_qm) {
	temp_1 = ISVREF(first_resumable_object_qm,(SI_Long)17L);
	temp = ISVREF(icp_socket,(SI_Long)30L);
	temp_2 = NUM_LE(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
      next_loop:
	first_1 = ISVREF(icp_socket,(SI_Long)31L);
	last_1 = ISVREF(icp_socket,(SI_Long)32L);
	next = CDR(first_1);
	if ( !TRUEP(first_1)) {
	    waiting_object_qm = Nil;
	    goto end_1;
	}
	else if (EQ(first_1,ISVREF(icp_socket,(SI_Long)31L))) {
	    if (EQ(first_1,last_1))
		CAS_SVREF(icp_socket,(SI_Long)32L,last_1,next);
	    else {
		gensymed_symbol = CAR(first_1);
		if (CAS_SVREF(icp_socket,(SI_Long)31L,first_1,next)) {
		    reclaim_icp_cons_1(first_1);
		    waiting_object_qm = gensymed_symbol;
		    goto end_1;
		}
	    }
	}
	goto next_loop;
      end_loop:
	waiting_object_qm = Qnil;
      end_1:;
    }
    else
	waiting_object_qm = Nil;
    if (waiting_object_qm) {
	SVREF(waiting_object_qm,FIX((SI_Long)17L)) = Nil;
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(waiting_object_qm,(SI_Long)19L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_3 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_3,svref_arg_2) = svref_new_value;
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
	temp_3 = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
	temp_3 = ISVREF(waiting_object_qm,(SI_Long)14L);
	SVREF(task,FIX((SI_Long)4L)) = temp_3;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp_3 = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qtry_to_transmit_resumable_object;
	temp_3 = SYMBOL_FUNCTION(Qtry_to_transmit_resumable_object);
	SVREF(task,FIX((SI_Long)8L)) = temp_3;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = waiting_object_qm;
	new_1 = task;
	if (CAS_SVREF(waiting_object_qm,(SI_Long)19L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp_3 = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp_3;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
	    goto end_2;
	}
	else {
	    inline_note_reclaim_cons(new_1,Nil);
	    structure_being_reclaimed = new_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
	      SVREF(new_1,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp_3 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
	    temp_3 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_3,svref_arg_2) = new_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_2:;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_most_recent_bandwidth_per_timeslice, Qdefault_most_recent_bandwidth_per_timeslice);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_bandwidth_per_timeslice, Qminimum_bandwidth_per_timeslice);

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_bandwidth_per_timeslice_qm, Qmost_recent_bandwidth_per_timeslice_qm);

/* BANDWIDTH-FOR-RESUMABLE-ATTRIBUTE-SPEC */
Object bandwidth_for_resumable_attribute_spec(attribute_spec_qm,icp_port)
    Object attribute_spec_qm, icp_port;
{
    Object temp, type, symbol, index_qm, symbol_name_1, bandwidth_of_base_name;
    Object index_of_base_name_qm, qualifier_qm, bandwidth_of_qualifier;
    Object index_of_qualifier_qm, fixnum;
    SI_Long length_1, gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(167,180);
    if (attribute_spec_qm) {
	if (FIXNUMP(attribute_spec_qm))
	    temp = Qvector_element;
	else if (SYMBOLP(attribute_spec_qm))
	    temp = Qattribute;
	else if (CONSP(attribute_spec_qm)) {
	    type = M_CAR(attribute_spec_qm);
	    temp = EQ(type,Qclass_qualified_name) ? Qattribute : type;
	}
	else
	    temp = Qnil;
	if (EQ(temp,Qattribute)) {
	    symbol = CONSP(attribute_spec_qm) ? THIRD(attribute_spec_qm) : 
		    attribute_spec_qm;
	    index_qm = get_icp_object_index_for_symbol(symbol,icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(symbol);
		length_1 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_1 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_1;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	    MVS_2(result,bandwidth_of_base_name,index_of_base_name_qm);
	    qualifier_qm = CONSP(attribute_spec_qm) ? 
		    SECOND(attribute_spec_qm) : Nil;
	    if (qualifier_qm) {
		index_qm = get_icp_object_index_for_symbol(qualifier_qm,
			icp_port);
		if (index_qm)
		    result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			    FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
		else {
		    symbol_name_1 = symbol_name_text_string(qualifier_qm);
		    length_1 = IFIX(text_string_length(symbol_name_1)) << 
			    (SI_Long)1L;
		    gensymed_symbol = length_1 > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L;
		    gensymed_symbol_1 = length_1;
		    result = VALUES_2(FIX(gensymed_symbol + 
			    gensymed_symbol_1),Nil);
		}
		MVS_2(result,bandwidth_of_qualifier,index_of_qualifier_qm);
		return VALUES_3(FIX((SI_Long)2L + 
			IFIX(bandwidth_of_base_name) + 
			IFIX(bandwidth_of_qualifier)),
			index_of_qualifier_qm,index_of_base_name_qm);
	    }
	    else
		return VALUES_3(FIX((SI_Long)2L + 
			IFIX(bandwidth_of_base_name)),Nil,
			index_of_base_name_qm);
	}
	else if (EQ(temp,Qvector_element) || EQ(temp,Qlist_element)) {
	    gensymed_symbol = (SI_Long)2L;
	    fixnum = FIXNUMP(attribute_spec_qm) ? attribute_spec_qm : 
		    SECOND(attribute_spec_qm);
	    gensymed_symbol_1 = IFIX(fixnum) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    return VALUES_3(FIX(gensymed_symbol + gensymed_symbol_1),Nil,Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_3(FIX((SI_Long)2L),Nil,Nil);
}

/* BANDWIDTH-FOR-RESUMABLE-NODE-CLASS-NAME */
Object bandwidth_for_resumable_node_class_name(resumable_node,icp_port)
    Object resumable_node, icp_port;
{
    Object symbol, index_qm, symbol_name_1;
    SI_Long length_1, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(167,181);
    symbol = ISVREF(resumable_node,(SI_Long)11L);
    index_qm = get_icp_object_index_for_symbol(symbol,icp_port);
    if (index_qm)
	return VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
		FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
    else {
	symbol_name_1 = symbol_name_text_string(symbol);
	length_1 = IFIX(text_string_length(symbol_name_1)) << (SI_Long)1L;
	gensymed_symbol = length_1 > (SI_Long)63000L ? (SI_Long)4L : 
		(SI_Long)2L;
	gensymed_symbol_1 = length_1;
	return VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),Nil);
    }
}

static Object Qab_structure;       /* structure */

/* BANDWIDTH-NEEDED-FOR-RESUMABLE-NODE */
Object bandwidth_needed_for_resumable_node(resumable_node,icp_port)
    Object resumable_node, icp_port;
{
    Object attribute_spec_qm, attribute_bandwidth, index_of_qualifier_qm;
    Object index_of_base_name_qm, evaluation_value_qm, evaluation_integer;
    Object evaluation_text, length_1, evaluation_truth_value;
    Object evaluation_symbol, index_qm, symbol_name_1, evaluation_sequence;
    Object evaluation_structure, bandwidth, corresponding_index_qm;
    Object value_bandwidth, fixnum, temp, class_bandwidth, ascension_count_qm;
    Object history_spec, datapoint_count_qm, datapoint_age_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    Object result;

    x_note_fn_call(167,182);
    attribute_spec_qm = ISVREF(resumable_node,(SI_Long)2L);
    result = bandwidth_for_resumable_attribute_spec(attribute_spec_qm,
	    icp_port);
    MVS_3(result,attribute_bandwidth,index_of_qualifier_qm,
	    index_of_base_name_qm);
    if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_value_node_g2_struct)) {
	evaluation_value_qm = ISVREF(resumable_node,(SI_Long)3L);
	if (FIXNUMP(evaluation_value_qm)) {
	    evaluation_integer = evaluation_value_qm;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value_qm)) == 
		(SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value_qm) != 
		(SI_Long)0L) {
	    evaluation_text = evaluation_value_qm;
	    length_1 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(evaluation_value_qm) && 
		EQ(M_CDR(evaluation_value_qm),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(evaluation_value_qm);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (evaluation_value_qm && SYMBOLP(evaluation_value_qm)) {
	    evaluation_symbol = evaluation_value_qm;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(evaluation_value_qm) && 
		EQ(M_CDR(evaluation_value_qm),Qsequence)) {
	    evaluation_sequence = evaluation_value_qm;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(evaluation_value_qm) && 
		EQ(M_CDR(evaluation_value_qm),Qab_structure)) {
	    evaluation_structure = evaluation_value_qm;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(evaluation_value_qm))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
		corresponding_index_qm);
	MVS_2(result,value_bandwidth,corresponding_index_qm);
	SVREF(resumable_node,FIX((SI_Long)4L)) = corresponding_index_qm;
	return VALUES_1(FIX((SI_Long)2L + IFIX(attribute_bandwidth) + 
		IFIX(value_bandwidth)));
    }
    else if (SIMPLE_VECTOR_P(resumable_node) && EQ(ISVREF(resumable_node,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct)) {
	gensymed_symbol = (SI_Long)2L;
	gensymed_symbol_1 = IFIX(attribute_bandwidth);
	fixnum = ISVREF(resumable_node,(SI_Long)3L);
	gensymed_symbol_2 = IFIX(fixnum) > (SI_Long)63000L ? (SI_Long)4L : 
		(SI_Long)2L;
	return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1 + 
		gensymed_symbol_2));
    }
    else {
	temp = SIMPLE_VECTOR_P(resumable_node) ? (EQ(ISVREF(resumable_node,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
		? T : Nil) : Qnil;
	if (temp);
	else
	    temp = SIMPLE_VECTOR_P(resumable_node) ? 
		    (EQ(ISVREF(resumable_node,(SI_Long)0L),
		    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct) 
		    ? T : Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if (SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_node_g2_struct) 
		|| SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
		|| SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
		|| SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
		|| SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
		|| SIMPLE_VECTOR_P(resumable_node) && 
		EQ(ISVREF(resumable_node,(SI_Long)0L),
		Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct)) 
		    {
	    if (ISVREF(resumable_node,(SI_Long)5L))
		return VALUES_1(FIX((SI_Long)0L));
	    else {
		result = bandwidth_for_resumable_node_class_name(resumable_node,
			icp_port);
		MVS_2(result,class_bandwidth,corresponding_index_qm);
		SVREF(resumable_node,FIX((SI_Long)12L)) = 
			corresponding_index_qm;
		gensymed_symbol = (SI_Long)2L;
		ascension_count_qm = ISVREF(resumable_node,(SI_Long)7L);
		gensymed_symbol_1 = ascension_count_qm ? 
			(IFIX(ascension_count_qm) > (SI_Long)63000L ? 
			(SI_Long)4L : (SI_Long)2L) : (SI_Long)0L;
		fixnum = ISVREF(resumable_node,(SI_Long)17L);
		gensymed_symbol_2 = IFIX(fixnum) > (SI_Long)63000L ? 
			(SI_Long)4L : (SI_Long)2L;
		gensymed_symbol_3 = SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct) 
			? (SI_Long)2L : (SI_Long)0L;
		if (SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_history_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct) 
			|| SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct)) 
			    {
		    fixnum = ISVREF(resumable_node,(SI_Long)18L);
		    gensymed_symbol_4 = IFIX(fixnum) > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L;
		}
		else
		    gensymed_symbol_4 = (SI_Long)0L;
		if (SIMPLE_VECTOR_P(resumable_node) && 
			EQ(ISVREF(resumable_node,(SI_Long)0L),
			Qg2_defstruct_structure_name_resumable_history_node_g2_struct)) 
			    {
		    history_spec = ISVREF(resumable_node,(SI_Long)21L);
		    datapoint_count_qm = SECOND(history_spec);
		    datapoint_age_qm = THIRD(history_spec);
		    gensymed_symbol_5 = datapoint_count_qm ? 
			    (IFIX(datapoint_count_qm) > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L) : (SI_Long)2L;
		    gensymed_symbol_6 = datapoint_age_qm ? 
			    (IFIX(datapoint_age_qm) > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L) : (SI_Long)2L;
		    gensymed_symbol_5 = gensymed_symbol_5 + 
			    gensymed_symbol_6 + (SI_Long)2L * (SI_Long)2L;
		}
		else
		    gensymed_symbol_5 = (SI_Long)0L;
		gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4 
			+ gensymed_symbol_5;
		gensymed_symbol_4 = IFIX(attribute_bandwidth);
		gensymed_symbol_5 = IFIX(class_bandwidth);
		return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1 + 
			gensymed_symbol_2 + gensymed_symbol_3 + 
			gensymed_symbol_4 + gensymed_symbol_5));
	    }
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* GET-AVAILABLE-OBJECT-PASSING-BANDWIDTH */
Object get_available_object_passing_bandwidth(resumable_object)
    Object resumable_object;
{
    Object network_bandwidth, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, timeslice_bandwidth;

    x_note_fn_call(167,183);
    if (ISVREF(resumable_object,(SI_Long)16L))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	network_bandwidth = ISVREF(ISVREF(resumable_object,(SI_Long)11L),
		(SI_Long)30L);
	temp = Most_recent_bandwidth_per_timeslice_qm;
	if (temp);
	else
	    temp = Default_most_recent_bandwidth_per_timeslice;
	gensymed_symbol = IFIX(temp);
	gensymed_symbol_1 = IFIX(ISVREF(resumable_object,(SI_Long)15L));
	timeslice_bandwidth = gensymed_symbol - gensymed_symbol_1;
	if (IFIX(network_bandwidth) < timeslice_bandwidth)
	    return VALUES_2(network_bandwidth,T);
	else {
	    SVREF(resumable_object,FIX((SI_Long)16L)) = T;
	    return VALUES_2(FIX(timeslice_bandwidth),Nil);
	}
    }
}

/* GET-VALUE-VECTOR-TRANSMISSION-INFO */
Object get_value_vector_transmission_info(resumable_value_vector_node,
	    element_type_qm,resumable_object,icp_port)
    Object resumable_value_vector_node, element_type_qm, resumable_object;
    Object icp_port;
{
    Object internal_vector, global_bandwidth, network_is_limiting_factor_p;
    Object temp, temp_1, number_of_elements, bandwidth_needed_1;
    Object bandwidth_available_1, interning_details, element, fixnum;
    Object text_string, length_1, symbol, index_qm, symbol_name_1;
    Object evaluation_integer, evaluation_text, evaluation_truth_value;
    Object evaluation_symbol, evaluation_sequence, evaluation_structure;
    Object bandwidth, corresponding_index_qm, new_bandwidth_available;
    Object incff_1_arg, temp_2;
    SI_Long bandwidth_available, bandwidth_needed, vector_index;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2;
    Object result;

    x_note_fn_call(167,184);
    internal_vector = ISVREF(resumable_value_vector_node,(SI_Long)20L);
    global_bandwidth = Nil;
    network_is_limiting_factor_p = Nil;
    result = get_available_object_passing_bandwidth(resumable_object);
    MVS_2(result,global_bandwidth,network_is_limiting_factor_p);
    if (SIMPLE_VECTOR_P(internal_vector) && EQ(ISVREF(internal_vector,
	    (SI_Long)0L),Managed_float_array_unique_marker)) {
	bandwidth_available = IFIX(global_bandwidth) - ((SI_Long)2L + 
		(SI_Long)2L);
	temp = chestnut_floorf_function(FIX(bandwidth_available),
		FIX((SI_Long)8L));
	temp_1 = FIXNUM_ADD1(ISVREF(resumable_value_vector_node,(SI_Long)21L));
	number_of_elements = FIXNUM_MIN(temp,temp_1);
	bandwidth_needed = IFIX(number_of_elements) * (SI_Long)8L;
	return VALUES_4(number_of_elements,FIX(bandwidth_needed),Nil,
		network_is_limiting_factor_p);
    }
    else {
	bandwidth_needed_1 = element_type_qm ? FIX((SI_Long)2L + 
		(SI_Long)2L) : FIX((SI_Long)2L);
	bandwidth_available_1 = FIXNUM_MINUS(global_bandwidth,
		bandwidth_needed_1);
	interning_details = Nil;
	vector_index = IFIX(ISVREF(resumable_value_vector_node,(SI_Long)21L));
	element = Nil;
	number_of_elements = FIX((SI_Long)0L);
      next_loop:
	if (vector_index < (SI_Long)0L)
	    goto end_loop;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	if (element_type_qm) {
	    if (EQ(element_type_qm,Qinteger)) {
		fixnum = element;
		if (IFIX(fixnum) > (SI_Long)63000L)
		    result = VALUES_1(FIX((SI_Long)4L));
		else
		    result = VALUES_1(FIX((SI_Long)2L));
	    }
	    else if (EQ(element_type_qm,QFLOAT))
		result = VALUES_1(FIX((SI_Long)8L));
	    else if (EQ(element_type_qm,Qtext)) {
		text_string = element;
		length_1 = length(text_string);
		gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
			(SI_Long)4L : (SI_Long)2L;
		gensymed_symbol_1 = IFIX(length_1);
		result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	    }
	    else if (EQ(element_type_qm,Qsymbol)) {
		symbol = element;
		index_qm = get_icp_object_index_for_symbol(symbol,icp_port);
		if (index_qm)
		    result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			    FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
		else {
		    symbol_name_1 = symbol_name_text_string(symbol);
		    length_2 = IFIX(text_string_length(symbol_name_1)) << 
			    (SI_Long)1L;
		    gensymed_symbol = length_2 > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L;
		    gensymed_symbol_1 = length_2;
		    result = VALUES_2(FIX(gensymed_symbol + 
			    gensymed_symbol_1),Nil);
		}
	    }
	    else if (EQ(element_type_qm,Qtruth)) {
		if (IFIX(element) > (SI_Long)63000L)
		    result = VALUES_1(FIX((SI_Long)4L));
		else
		    result = VALUES_1(FIX((SI_Long)2L));
	    }
	    else
		result = VALUES_1(Qnil);
	}
	else {
	    if (FIXNUMP(element)) {
		evaluation_integer = element;
		if (IFIX(evaluation_integer) > (SI_Long)63000L)
		    result = VALUES_1(FIX((SI_Long)4L));
		else
		    result = VALUES_1(FIX((SI_Long)2L));
	    }
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L)
		result = VALUES_1(FIX((SI_Long)8L));
	    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != 
			(SI_Long)0L) {
		evaluation_text = element;
		length_1 = length(evaluation_text);
		gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
			(SI_Long)4L : (SI_Long)2L;
		gensymed_symbol_1 = IFIX(length_1);
		result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	    }
	    else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value)) {
		evaluation_truth_value = M_CAR(element);
		if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		    result = VALUES_1(FIX((SI_Long)4L));
		else
		    result = VALUES_1(FIX((SI_Long)2L));
	    }
	    else if (element && SYMBOLP(element)) {
		evaluation_symbol = element;
		index_qm = 
			get_icp_object_index_for_symbol(evaluation_symbol,
			icp_port);
		if (index_qm)
		    result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			    FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
		else {
		    symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		    length_2 = IFIX(text_string_length(symbol_name_1)) << 
			    (SI_Long)1L;
		    gensymed_symbol = length_2 > (SI_Long)63000L ? 
			    (SI_Long)4L : (SI_Long)2L;
		    gensymed_symbol_1 = length_2;
		    result = VALUES_2(FIX(gensymed_symbol + 
			    gensymed_symbol_1),Nil);
		}
	    }
	    else if (CONSP(element) && EQ(M_CDR(element),Qsequence)) {
		evaluation_sequence = element;
		result = VALUES_2(FIX((SI_Long)0L),Nil);
	    }
	    else if (CONSP(element) && EQ(M_CDR(element),Qab_structure)) {
		evaluation_structure = element;
		result = VALUES_2(FIX((SI_Long)0L),Nil);
	    }
	    else if ( !TRUEP(element))
		result = VALUES_1(FIX((SI_Long)2L));
	    else
		result = VALUES_1(Qnil);
	    MVS_2(result,bandwidth,corresponding_index_qm);
	    result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
		    corresponding_index_qm);
	}
	MVS_2(result,bandwidth,corresponding_index_qm);
	new_bandwidth_available = FIXNUM_MINUS(bandwidth_available_1,
		bandwidth);
	if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	    incff_1_arg = bandwidth;
	    bandwidth_needed_1 = FIXNUM_ADD(bandwidth_needed_1,incff_1_arg);
	    bandwidth_available_1 = new_bandwidth_available;
	    number_of_elements = FIXNUM_ADD1(number_of_elements);
	    if (corresponding_index_qm)
		interning_details = 
			icp_cons_1(icp_cons_1(FIX(vector_index),
			corresponding_index_qm),interning_details);
	}
	else
	    goto end_loop;
	vector_index = vector_index - (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_2 = number_of_elements;
	temp = bandwidth_needed_1;
	temp_1 = nreverse(interning_details);
	return VALUES_4(temp_2,temp,temp_1,network_is_limiting_factor_p);
	return VALUES_1(Qnil);
    }
}

static Object Kabort_transmitting_resumable_object;  /* :abort-transmitting-resumable-object */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_6;   /* "The G2 value-list ~NF" */

static Object string_constant_7;   /* " at top level in the argument list" */

static Object string_constant_8;   /* ", being sent as a subobject of ~NF, " */

static Object string_constant_9;   /* "has had its length changed" */

static Object Qg2_value_list_length_changed;  /* g2-value-list-length-changed */

/* ABORT-OBJECT-PASSING-DUE-TO-LIST-LENGTH-CHANGE */
Object abort_object_passing_due_to_list_length_change(resumable_value_list_node,
	    resumable_object)
    Object resumable_value_list_node, resumable_object;
{
    Object current_object, toplevel_object, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(167,185);
    Rpc_throw_tag = Kabort_transmitting_resumable_object;
    current_object = ISVREF(resumable_value_list_node,(SI_Long)4L);
    toplevel_object = ISVREF(resumable_object,(SI_Long)8L);
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
	      tformat(2,string_constant_6,current_object);
	      if (EQ(current_object,toplevel_object))
		  tformat(1,string_constant_7);
	      else
		  tformat(2,string_constant_8,toplevel_object);
	      tformat(1,string_constant_9);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return icp_list_2(Qg2_value_list_length_changed,temp);
}

/* GET-VALUE-LIST-TRANSMISSION-INFO */
Object get_value_list_transmission_info(resumable_value_list_node,
	    element_type_qm,resumable_object,icp_port)
    Object resumable_value_list_node, element_type_qm, resumable_object;
    Object icp_port;
{
    Object global_bandwidth, network_is_limiting_factor_p, bandwidth_needed;
    Object bandwidth_available, interning_details, length_of_value_list;
    Object list_element, element, number_of_elements, fixnum, text_string;
    Object length_1, truth_value, symbol, index_qm, symbol_name_1;
    Object evaluation_integer, evaluation_text, evaluation_truth_value;
    Object evaluation_symbol, evaluation_sequence, evaluation_structure;
    Object bandwidth, corresponding_index_qm, new_bandwidth_available;
    Object incff_1_arg, svref_new_value, possible_throw_value, temp, temp_1;
    Object temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, length_2;
    char list_elements_remain_p;
    Object result;

    x_note_fn_call(167,186);
    global_bandwidth = Nil;
    network_is_limiting_factor_p = Nil;
    result = get_available_object_passing_bandwidth(resumable_object);
    MVS_2(result,global_bandwidth,network_is_limiting_factor_p);
    bandwidth_needed = element_type_qm ? FIX((SI_Long)2L + (SI_Long)2L) : 
	    FIX((SI_Long)2L);
    bandwidth_available = FIXNUM_MINUS(global_bandwidth,bandwidth_needed);
    interning_details = Nil;
    length_of_value_list = ISVREF(resumable_value_list_node,(SI_Long)18L);
    list_element = ISVREF(resumable_value_list_node,(SI_Long)20L);
    element = Nil;
    number_of_elements = FIX((SI_Long)0L);
  next_loop:
    if ( !(EQ(ISVREF(list_element,(SI_Long)5L),
	    ISVREF(resumable_value_list_node,(SI_Long)4L)) && 
	    FIXNUM_LT(ISVREF(resumable_value_list_node,(SI_Long)21L),
	    length_of_value_list)))
	goto end_loop;
    element = ISVREF(list_element,(SI_Long)4L);
    if (element_type_qm) {
	if (EQ(element_type_qm,Qinteger)) {
	    fixnum = element;
	    if (IFIX(fixnum) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (EQ(element_type_qm,QFLOAT))
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (EQ(element_type_qm,Qtext)) {
	    text_string = element;
	    length_1 = length(text_string);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (EQ(element_type_qm,Qtruth)) {
	    truth_value = M_CAR(element);
	    if (IFIX(truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (EQ(element_type_qm,Qsymbol)) {
	    symbol = element;
	    index_qm = get_icp_object_index_for_symbol(symbol,icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else
	    result = VALUES_1(Qnil);
    }
    else {
	if (FIXNUMP(element)) {
	    evaluation_integer = element;
	    if (IFIX(evaluation_integer) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L)
	    result = VALUES_1(FIX((SI_Long)8L));
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != (SI_Long)0L) {
	    evaluation_text = element;
	    length_1 = length(evaluation_text);
	    gensymed_symbol = IFIX(length_1) > (SI_Long)63000L ? 
		    (SI_Long)4L : (SI_Long)2L;
	    gensymed_symbol_1 = IFIX(length_1);
	    result = VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
	}
	else if (CONSP(element) && EQ(M_CDR(element),Qtruth_value)) {
	    evaluation_truth_value = M_CAR(element);
	    if (IFIX(evaluation_truth_value) > (SI_Long)63000L)
		result = VALUES_1(FIX((SI_Long)4L));
	    else
		result = VALUES_1(FIX((SI_Long)2L));
	}
	else if (element && SYMBOLP(element)) {
	    evaluation_symbol = element;
	    index_qm = get_icp_object_index_for_symbol(evaluation_symbol,
		    icp_port);
	    if (index_qm)
		result = VALUES_2(IFIX(index_qm) > (SI_Long)63000L ? 
			FIX((SI_Long)4L) : FIX((SI_Long)2L),index_qm);
	    else {
		symbol_name_1 = symbol_name_text_string(evaluation_symbol);
		length_2 = IFIX(text_string_length(symbol_name_1)) << 
			(SI_Long)1L;
		gensymed_symbol = length_2 > (SI_Long)63000L ? (SI_Long)4L 
			: (SI_Long)2L;
		gensymed_symbol_1 = length_2;
		result = VALUES_2(FIX(gensymed_symbol + gensymed_symbol_1),
			Nil);
	    }
	}
	else if (CONSP(element) && EQ(M_CDR(element),Qsequence)) {
	    evaluation_sequence = element;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if (CONSP(element) && EQ(M_CDR(element),Qab_structure)) {
	    evaluation_structure = element;
	    result = VALUES_2(FIX((SI_Long)0L),Nil);
	}
	else if ( !TRUEP(element))
	    result = VALUES_1(FIX((SI_Long)2L));
	else
	    result = VALUES_1(Qnil);
	MVS_2(result,bandwidth,corresponding_index_qm);
	result = VALUES_2(FIX(IFIX(bandwidth) + (SI_Long)2L),
		corresponding_index_qm);
    }
    MVS_2(result,bandwidth,corresponding_index_qm);
    new_bandwidth_available = FIXNUM_MINUS(bandwidth_available,bandwidth);
    if (IFIX(new_bandwidth_available) > (SI_Long)0L) {
	incff_1_arg = bandwidth;
	bandwidth_needed = FIXNUM_ADD(bandwidth_needed,incff_1_arg);
	bandwidth_available = new_bandwidth_available;
	number_of_elements = FIXNUM_ADD1(number_of_elements);
	svref_new_value = FIXNUM_ADD1(ISVREF(resumable_value_list_node,
		(SI_Long)21L));
	SVREF(resumable_value_list_node,FIX((SI_Long)21L)) = svref_new_value;
	if (corresponding_index_qm)
	    interning_details = icp_cons_1(icp_cons_1(number_of_elements,
		    corresponding_index_qm),interning_details);
    }
    else
	goto end_loop;
    list_element = ATOMIC_REF_OBJECT(ISVREF(list_element,(SI_Long)2L));
    goto next_loop;
  end_loop:
    list_elements_remain_p = EQ(ISVREF(list_element,(SI_Long)5L),
	    ISVREF(resumable_value_list_node,(SI_Long)4L));
    if ( !list_elements_remain_p && 
	    FIXNUM_LT(ISVREF(resumable_value_list_node,(SI_Long)21L),
	    length_of_value_list)) {
	possible_throw_value = 
		abort_object_passing_due_to_list_length_change(resumable_value_list_node,
		resumable_object);
	if (Rpc_throw_tag)
	    return VALUES_1(possible_throw_value);
    }
    temp = number_of_elements;
    temp_1 = bandwidth_needed;
    temp_2 = nreverse(interning_details);
    return VALUES_5(temp,temp_1,list_elements_remain_p ? T : Nil,temp_2,
	    network_is_limiting_factor_p);
    return VALUES_1(Qnil);
}

static Object Qsupplied;           /* supplied */

static Object Qvalidity_interval;  /* validity-interval */

static Object Qindefinite;         /* indefinite */

static Object Qcurrent_value_of_variable_or_parameter;  /* current-value-of-variable-or-parameter */

static Object string_constant_10;  /* "~A" */

static Object Qreclaim_text_string;  /* reclaim-text-string */

/* PUT-CURRENT-VALUE-FOR-OBJECT-PASSING */
Object put_current_value_for_object_passing(variable_or_parameter,
	    new_value,collection_time_qm,potential_problem_name)
    Object variable_or_parameter, new_value, collection_time_qm;
    Object potential_problem_name;
{
    Object restore_supplied_p, sub_class_bit_vector, validity_interval;
    Object problem_string_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(167,187);
    restore_supplied_p = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	validity_interval = ISVREF(variable_or_parameter,(SI_Long)27L);
	if (EQ(validity_interval,Qsupplied)) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(variable_or_parameter,
			Qvalidity_interval);
	    SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qindefinite;
	    restore_supplied_p = T;
	}
    }
    problem_string_qm = put_current_evaluation_value(variable_or_parameter,
	    new_value,Nil,collection_time_qm,Nil);
    if (problem_string_qm)
	record_object_building_problem_on_receiving_side_1(potential_problem_name,
		Nil,Qcurrent_value_of_variable_or_parameter,
		ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),
		(SI_Long)1L),string_constant_10,
		icp_cons_1(problem_string_qm,Nil),
		SYMBOL_FUNCTION(Qreclaim_text_string));
    if (restore_supplied_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(variable_or_parameter,Qvalidity_interval);
	SVREF(variable_or_parameter,FIX((SI_Long)27L)) = Qsupplied;
    }
    return VALUES_1(Nil);
}

/* GET-DEFAULT-COLLECTION-TIME-FOR-PUT-CURRENT-VALUE */
Object get_default_collection_time_for_put_current_value(variable_or_parameter)
    Object variable_or_parameter;
{
    Object collection_time_0_points_ago, temp;
    double temp_1;

    x_note_fn_call(167,188);
    collection_time_0_points_ago = 
	    get_collection_time_of_previous_datapoint(variable_or_parameter,
	    Nil,FIX((SI_Long)0L));
    if (collection_time_0_points_ago);
    else
	collection_time_0_points_ago = Some_time_ago;
    if (FIXNUMP(collection_time_0_points_ago))
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(FIXNUM_ADD(Gensym_time_at_start,
		collection_time_0_points_ago),Gensym_time_at_start)) + 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L));
    else {
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(collection_time_0_points_ago);
	temp = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L));
    }
    return VALUES_1(temp);
}

/* GET-CURRENT-VALUE-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object get_current_value_system_attribute_for_object_passing(variable_or_parameter)
    Object variable_or_parameter;
{
    Object current_computation_frame, current_computation_flags, temp;
    Declare_special(2);

    x_note_fn_call(167,189);
    current_computation_frame = variable_or_parameter;
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      0);
	Current_computation_flags = FIX(IFIX(Current_computation_flags) &  
		~(SI_Long)4L);
	Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
		(SI_Long)256L);
	temp = get_current_evaluation_value(variable_or_parameter,Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qcurrent_value;      /* current-value */

/* GET-CURRENT-VALUE-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING */
Object get_current_value_attribute_spec_structure_for_object_passing(variable_or_parameter,
	    system_includes)
    Object variable_or_parameter, system_includes;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(167,190);
    if (memq_function(Qcurrent_value,system_includes)) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
    temp_1 = temp ? gensym_list_3(Qattribute,Nil,Qcurrent_value) : Nil;
    return VALUES_1(temp_1);
}

static Object Qproblem_putting_current_value_into_history_keeper;  /* problem-putting-current-value-into-history-keeper */

static Object Qproblem_putting_current_value_into_variable_or_parameter;  /* problem-putting-current-value-into-variable-or-parameter */

static Object Qunable_to_set_current_value_because_item_is_not_a_variable_or_parameter;  /* unable-to-set-current-value-because-item-is-not-a-variable-or-parameter */

/* SET-CURRENT-VALUE-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object set_current_value_system_attribute_for_object_passing(variable_or_parameter,
	    new_value_qm)
    Object variable_or_parameter, new_value_qm;
{
    Object sub_class_bit_vector, current_computation_frame, temp_1;
    Object g2_time_at_start, collection_time_for_put_current_evaluation_value;
    Object previous_time_of_most_recent_value, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(167,191);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
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
	if (new_value_qm) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		current_computation_frame = variable_or_parameter;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			1);
		  if (ISVREF(variable_or_parameter,(SI_Long)24L)) {
		      temp_1 = ISVREF(Current_receiving_resumable_object,
			      (SI_Long)14L);
		      if (temp_1);
		      else
			  temp_1 = G2_time_at_start;
		      g2_time_at_start = temp_1;
		      PUSH_SPECIAL_WITH_SYMBOL(G2_time_at_start,Qg2_time_at_start,g2_time_at_start,
			      0);
			collection_time_for_put_current_evaluation_value = 
				get_default_collection_time_for_put_current_value(variable_or_parameter);
			previous_time_of_most_recent_value = 
				ISVREF(variable_or_parameter,(SI_Long)21L);
			reclaim_evaluation_value(previous_time_of_most_recent_value);
			svref_new_value = Some_time_ago;
			ISVREF(variable_or_parameter,(SI_Long)21L) = 
				svref_new_value;
			put_current_value_for_object_passing(variable_or_parameter,
				new_value_qm,
				collection_time_for_put_current_evaluation_value,
				Qproblem_putting_current_value_into_history_keeper);
		      POP_SPECIAL();
		  }
		  else
		      put_current_value_for_object_passing(variable_or_parameter,
			      new_value_qm,Nil,
			      Qproblem_putting_current_value_into_variable_or_parameter);
		POP_SPECIAL();
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
    }
    else
	record_object_building_problem_on_receiving_side_1(Qunable_to_set_current_value_because_item_is_not_a_variable_or_parameter,
		Nil,Qcurrent_value,ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* GET-NAME-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object get_name_system_attribute_for_object_passing(item)
    Object item;
{
    Object name_or_names, temp;

    x_note_fn_call(167,192);
    name_or_names = get_lookup_slot_value_given_default(item,
	    Qname_or_names_for_frame,Nil);
    if (CONSP(name_or_names))
	temp = CAR(name_or_names);
    else if (SYMBOLP(name_or_names))
	temp = name_or_names;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

static Object Qname;               /* name */

/* GET-NAME-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING */
Object get_name_attribute_spec_structure_for_object_passing(item,
	    system_includes)
    Object item, system_includes;
{
    Object temp;

    x_note_fn_call(167,193);
    temp = memq_function(Qname,system_includes) ? gensym_list_3(Qattribute,
	    Nil,Qname) : Nil;
    return VALUES_1(temp);
}

static Object Qinappropriate_item_for_system_attribute;  /* inappropriate-item-for-system-attribute */

/* SET-NAME-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object set_name_system_attribute_for_object_passing(item,new_name)
    Object item, new_name;
{
    x_note_fn_call(167,194);
    if (T)
	change_slot_value(3,item,Qname_or_names_for_frame,new_name);
    else
	record_object_building_problem_on_receiving_side_1(Qinappropriate_item_for_system_attribute,
		Nil,Qname,ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L),Nil,
		Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qaction;             /* action */

static Object Qedit_attribute;     /* edit-attribute */

/* SET-TEXT-OBJECT-PASSING-SYSTEM-ATTRIBUTE */
Object set_text_object_passing_system_attribute(item,new_text_qm)
    Object item, new_text_qm;
{
    Object gensymed_symbol, sub_class_bit_vector, text_slot_name_qm;
    Object slot_description_qm, type_of_slot_if_editable_qm, x2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,195);
    if (new_text_qm) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
	text_slot_name_qm = temp ? get_slot_name_for_alias_if_any(Qaction,
		item) : get_slot_name_for_alias_if_any(Qtext,item);
	if (text_slot_name_qm) {
	    slot_description_qm = 
		    get_slot_description_of_class_description_function(text_slot_name_qm,
		    ISVREF(item,(SI_Long)1L),Nil);
	    if (slot_description_qm) {
		type_of_slot_if_editable_qm = 
			type_slot_feature_assq_if_editable(ISVREF(slot_description_qm,
			(SI_Long)9L));
		if (type_of_slot_if_editable_qm) {
		    temp = 
			    TRUEP(attribute_operation_is_allowed_p(Qedit_attribute,
			    item,Qtext,ISVREF(slot_description_qm,
			    (SI_Long)3L)));
		    if (temp);
		    else {
			if (SIMPLE_VECTOR_P(item) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
				(SI_Long)2L &&  !EQ(ISVREF(item,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(item,(SI_Long)1L);
			    gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				    EQ(ISVREF(x2,(SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? x2 : Qnil;
			}
			else
			    gensymed_symbol = Nil;
			if (gensymed_symbol) {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Message_class_description,
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
		    }
		    if (temp) {
			if ( !TRUEP(parse_and_change_slot(item,
				slot_description_qm,new_text_qm,
				type_of_slot_if_editable_qm)))
			    reclaim_text_string(new_text_qm);
		    }
		}
	    }
	}
    }
    return VALUES_1(Nil);
}

static Object Qexternal_java_class;  /* external-java-class */

static Object Qcompilation_unit;   /* compilation-unit */

/* GET-TEXT-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object get_text_system_attribute_for_object_passing(item)
    Object item;
{
    Object gensymed_symbol, sub_class_bit_vector, text_qm, gensymed_symbol_4;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,196);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	text_qm = ISVREF(item,(SI_Long)16L);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	    text_qm = ISVREF(item,(SI_Long)27L);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
		text_qm = translation_and_text_of_embedded_rule_function(item);
	    else {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(Qexternal_java_class,
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
		if (temp)
		    text_qm = get_slot_value_if_any_function(item,
			    Qcompilation_unit,Nil);
		else
		    text_qm = Qnil;
	    }
	}
    }
    temp_1 = text_qm ? convert_text_to_text_string(1,text_qm) : Qnil;
    return VALUES_1(temp_1);
}

/* GET-TEXT-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING */
Object get_text_attribute_spec_structure_for_object_passing(item,
	    system_includes)
    Object item, system_includes;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,197);
    if (memq_function(Qtext,system_includes)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
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
		    IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
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
			IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
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
			IFIX(ISVREF(Action_button_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	}
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(Qexternal_java_class,
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? gensym_list_3(Qattribute,Nil,Qtext) : Nil;
    return VALUES_1(temp_1);
}

/* SET-TEXT-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object set_text_system_attribute_for_object_passing(item,new_text_qm)
    Object item, new_text_qm;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,198);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
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
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
    }
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
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
		    IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
    }
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qexternal_java_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    if (temp)
	set_text_object_passing_system_attribute(item,new_text_qm);
    else
	record_object_building_problem_on_receiving_side_1(Qinappropriate_item_for_system_attribute,
		Nil,Qtext,ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L),Nil,
		Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qpackage_declaration;  /* package-declaration */

/* GET-PACKAGE-DECLARATION-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object get_package_declaration_system_attribute_for_object_passing(item)
    Object item;
{
    Object text_qm, temp;

    x_note_fn_call(167,199);
    text_qm = get_slot_value_if_any_function(item,Qpackage_declaration,Nil);
    temp = text_qm ? convert_text_to_text_string(1,text_qm) : Qnil;
    return VALUES_1(temp);
}

/* GET-PACKAGE-DECLARATION-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING */
Object get_package_declaration_attribute_spec_structure_for_object_passing(item,
	    system_includes)
    Object item, system_includes;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(167,200);
    if (memq_function(Qpackage_declaration,system_includes)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qexternal_java_class,
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
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? gensym_list_3(Qattribute,Nil,Qpackage_declaration) : Nil;
    return VALUES_1(temp_1);
}

/* SET-PACKAGE-DECLARATION-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object set_package_declaration_system_attribute_for_object_passing(item,
	    new_text_qm)
    Object item, new_text_qm;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(167,201);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qexternal_java_class,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	set_text_object_passing_system_attribute(item,new_text_qm);
    else
	record_object_building_problem_on_receiving_side_1(Qinappropriate_item_for_system_attribute,
		Nil,Qpackage_declaration,ISVREF(ISVREF(item,(SI_Long)1L),
		(SI_Long)1L),Nil,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qimport_declarations;  /* import-declarations */

/* GET-IMPORT-DECLARATIONS-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object get_import_declarations_system_attribute_for_object_passing(item)
    Object item;
{
    Object text_qm, temp;

    x_note_fn_call(167,202);
    text_qm = get_slot_value_if_any_function(item,Qimport_declarations,Nil);
    temp = text_qm ? convert_text_to_text_string(1,text_qm) : Qnil;
    return VALUES_1(temp);
}

/* GET-IMPORT-DECLARATIONS-ATTRIBUTE-SPEC-STRUCTURE-FOR-OBJECT-PASSING */
Object get_import_declarations_attribute_spec_structure_for_object_passing(item,
	    system_includes)
    Object item, system_includes;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(167,203);
    if (memq_function(Qimport_declarations,system_includes)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qexternal_java_class,
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
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? gensym_list_3(Qattribute,Nil,Qimport_declarations) : Nil;
    return VALUES_1(temp_1);
}

/* SET-IMPORT-DECLARATIONS-SYSTEM-ATTRIBUTE-FOR-OBJECT-PASSING */
Object set_import_declarations_system_attribute_for_object_passing(item,
	    new_text_qm)
    Object item, new_text_qm;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(167,204);
    if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qexternal_java_class,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	set_text_object_passing_system_attribute(item,new_text_qm);
    else
	record_object_building_problem_on_receiving_side_1(Qinappropriate_item_for_system_attribute,
		Nil,Qimport_declarations,ISVREF(ISVREF(item,(SI_Long)1L),
		(SI_Long)1L),Nil,Nil,Nil);
    return VALUES_1(Nil);
}

/* G2-READ-ICP-ATTRIBUTE-FOR-LIST-OF-ATTRIBUTES */
Object g2_read_icp_attribute_for_list_of_attributes(tag)
    Object tag;
{
    Object temp, qualifier, base_name;

    x_note_fn_call(167,205);
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 13:
	    qualifier = read_icp_possibly_interned_symbol();
	    base_name = read_icp_possibly_interned_symbol();
	    temp = qualifier ? icp_cons_1(Qclass_qualified_name,
		    icp_cons_1(qualifier,icp_cons_1(base_name,Nil))) : 
		    base_name;
	    break;
	  case 12:
	    temp = read_icp_possibly_interned_symbol();
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

/* G2-WRITE-ICP-LIST-OF-ATTRIBUTES */
Object g2_write_icp_list_of_attributes(list_of_attributes)
    Object list_of_attributes;
{
    Object attribute, ab_loop_list_;

    x_note_fn_call(167,206);
    write_icp_fixnum(length(list_of_attributes));
    attribute = Nil;
    ab_loop_list_ = list_of_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(attribute) && EQ(M_CAR(attribute),Qclass_qualified_name)) {
	write_icp_byte(Qualified_symbolic_attribute_tag);
	write_icp_possibly_interned_symbol(CONSP(attribute) ? 
		M_CAR(M_CDR(attribute)) : Nil,Nil);
	write_icp_possibly_interned_symbol(CONSP(attribute) ? 
		M_CAR(M_CDR(M_CDR(attribute))) : attribute,Nil);
    }
    else {
	write_icp_byte(Unqualified_symbolic_attribute_tag);
	write_icp_possibly_interned_symbol(CONSP(attribute) ? 
		M_CAR(M_CDR(M_CDR(attribute))) : attribute,Nil);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CHANGE-SLOT-VALUE-FOR-OBJECT-PASSING */
Object change_slot_value_for_object_passing(current_subobject,
	    unique_slot_name,leaf)
    Object current_subobject, unique_slot_name, leaf;
{
    Object evaluation_truth_value, slot_constant;

    x_note_fn_call(167,207);
    if (CONSP(leaf) && EQ(M_CDR(leaf),Qtruth_value)) {
	evaluation_truth_value = M_CAR(leaf);
	slot_constant = slot_value_list_2(evaluation_truth_value,Qtruth_value);
	if ( !(EQ(leaf,Evaluation_true_value) || EQ(leaf,
		Evaluation_false_value)))
	    reclaim_eval_cons_1(leaf);
	return change_slot_value(3,current_subobject,unique_slot_name,
		slot_constant);
    }
    else
	return change_slot_value(3,current_subobject,unique_slot_name,leaf);
}

static Object Kstack_error;        /* :stack-error */

static Object Qab_slot_value;      /* slot-value */

/* CHANGE-EXPORTED-ATTRIBUTE-FOR-OBJECT-PASSING */
Object change_exported_attribute_for_object_passing(object,attribute_name,
	    attribute_qualifier_qm,new_value_qm)
    Object object, attribute_name, attribute_qualifier_qm, new_value_qm;
{
    Object component, error_message_qm, gensymed_symbol, slot_value_list;
    Object slot_value_list_tail, slot_value_cons, temp, svref_arg_2;
    Object error_text;
    Declare_catch(1);
    Object result;

    x_note_fn_call(167,208);
    if (PUSH_CATCH(Kstack_error,0)) {
	if ( !TRUEP(new_value_qm))
	    result = VALUES_1(T);
	else {
	    component = slot_value_list_4(Qattribute,attribute_name,Nil,
		    Qcurrent_computation_frame);
	    error_message_qm = conclude_into_attribute_component(6,object,
		    attribute_name,attribute_qualifier_qm,new_value_qm,Nil,
		    component);
	    gensymed_symbol = component;
	    slot_value_list = gensymed_symbol;
	    slot_value_list_tail = M_CDR(M_CDR(M_CDR(gensymed_symbol)));
	    if (slot_value_list &&  !((SI_Long)0L == 
		    inline_debugging_consing())) {
		slot_value_cons = slot_value_list;
	      next_loop:
		inline_note_reclaim_cons(slot_value_cons,Qab_slot_value);
		if (EQ(slot_value_cons,slot_value_list_tail))
		    goto end_1;
		else if ( !TRUEP(slot_value_cons))
		    goto end_1;
		else
		    slot_value_cons = CDR(slot_value_cons);
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = slot_value_list;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = slot_value_list_tail;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = slot_value_list;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = slot_value_list_tail;
	    }
	    M_CDR(slot_value_list_tail) = Nil;
	    if (error_message_qm) {
		reclaim_text_string(error_message_qm);
		result = VALUES_1(Nil);
	    }
	    else
		result = VALUES_1(T);
	}
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    error_text = NTH_VALUE((SI_Long)2L, result);
    reclaim_error_text(error_text);
    result = VALUES_1(T);
  end_gensymed_symbol:
    return result;
}

/* G2-LIST-INSERT-FOR-OBJECT-PASSING */
Object g2_list_insert_for_object_passing(thing_to_insert,g2_list)
    Object thing_to_insert, g2_list;
{
    x_note_fn_call(167,209);
    if (ISVREF(g2_list,(SI_Long)20L))
	g2_list_insert_at_end(2,thing_to_insert,g2_list);
    return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

static Object Qleaf_value_inappropriate_for_attribute;  /* leaf-value-inappropriate-for-attribute */

static Object Qleaf_attribute_name_inappropriate_for_class;  /* leaf-attribute-name-inappropriate-for-class */

static Object Qadd_g2_array_leaf_to_non_g2_array;  /* add-g2-array-leaf-to-non-g2-array */

static Object Qleaf_index_out_of_bounds_for_g2_array;  /* leaf-index-out-of-bounds-for-g2-array */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qincompatible_type_of_g2_array_leaf;  /* incompatible-type-of-g2-array-leaf */

static Object Qadd_g2_list_leaf_to_non_g2_list;  /* add-g2-list-leaf-to-non-g2-list */

static Object Qincompatible_type_of_g2_list_leaf;  /* incompatible-type-of-g2-list-leaf */

/* G2-ADD-LEAF-TO-REMOTE-OBJECT */
Object g2_add_leaf_to_remote_object(current_subobject,attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,leaf)
    Object current_subobject, attribute_type, attribute_qualifier_qm;
    Object attribute_name_or_index, leaf;
{
    Object class_of_current_subobject, x2, gensymed_symbol;
    Object sub_class_bit_vector, slot_description_qm;
    Object previous_attribute_contents_qm, unique_slot_name, item_or_datum_qm;
    Object element_type, temp_1, allow_no_value_p, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(167,210);
    if ( !TRUEP(ISVREF(Current_receiving_resumable_object,(SI_Long)10L))) {
	if (EQ(attribute_type,Qattribute)) {
	    if (memq_function(attribute_name_or_index,list_constant_1)) {
		if (EQ(attribute_name_or_index,Qimport_declarations))
		    return set_import_declarations_system_attribute_for_object_passing(current_subobject,
			    leaf);
		else if (EQ(attribute_name_or_index,Qpackage_declaration))
		    return set_package_declaration_system_attribute_for_object_passing(current_subobject,
			    leaf);
		else if (EQ(attribute_name_or_index,Qtext))
		    return set_text_system_attribute_for_object_passing(current_subobject,
			    leaf);
		else if (EQ(attribute_name_or_index,Qname))
		    return set_name_system_attribute_for_object_passing(current_subobject,
			    leaf);
		else if (EQ(attribute_name_or_index,Qcurrent_value))
		    return set_current_value_system_attribute_for_object_passing(current_subobject,
			    leaf);
		else
		    return VALUES_1(Qnil);
	    }
	    else {
		class_of_current_subobject = 
			ISVREF(ISVREF(current_subobject,(SI_Long)1L),
			(SI_Long)1L);
		if (SIMPLE_VECTOR_P(current_subobject) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject)) 
			> (SI_Long)2L &&  !EQ(ISVREF(current_subobject,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(current_subobject,(SI_Long)1L);
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
			    IFIX(ISVREF(Object_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		slot_description_qm = temp ? 
			get_slot_description_of_class_description_function(attribute_name_or_index,
			lookup_global_or_kb_specific_property_value(class_of_current_subobject,
			Class_description_gkbprop),attribute_qualifier_qm) 
			: Nil;
		if (slot_description_qm) {
		    if (type_specification_type_p(leaf,
			    ISVREF(slot_description_qm,(SI_Long)5L))) {
			previous_attribute_contents_qm = 
				get_slot_description_value(current_subobject,
				slot_description_qm);
			unique_slot_name = ISVREF(slot_description_qm,
				(SI_Long)1L);
			if (previous_attribute_contents_qm) {
			    if (SIMPLE_VECTOR_P(previous_attribute_contents_qm) 
				    && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_attribute_contents_qm)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(previous_attribute_contents_qm,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(previous_attribute_contents_qm,
					(SI_Long)1L);
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
			if (temp ? (SI_Long)0L != 
				(IFIX(ISVREF(previous_attribute_contents_qm,
				(SI_Long)5L)) & (SI_Long)262144L) : 
				    TRUEP(Nil)) {
			    delete_frame(previous_attribute_contents_qm);
			    set_slot_value_function(current_subobject,
				    unique_slot_name,Nil,Nil);
			}
			return change_slot_value_for_object_passing(current_subobject,
				unique_slot_name,leaf);
		    }
		    else
			return record_object_building_problem_on_receiving_side_1(Qleaf_value_inappropriate_for_attribute,
				attribute_qualifier_qm,
				attribute_name_or_index,
				class_of_current_subobject,Nil,Nil,Nil);
		}
		else if ( 
			!TRUEP(change_exported_attribute_for_object_passing(current_subobject,
			attribute_name_or_index,attribute_qualifier_qm,leaf)))
		    return record_object_building_problem_on_receiving_side_1(Qleaf_attribute_name_inappropriate_for_class,
			    attribute_qualifier_qm,attribute_name_or_index,
			    class_of_current_subobject,Nil,Nil,Nil);
		else
		    return VALUES_1(Nil);
	    }
	}
	else if (EQ(attribute_type,Qvector_element)) {
	    sub_class_bit_vector = ISVREF(ISVREF(current_subobject,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
		return record_object_building_problem_on_receiving_side_1(Qadd_g2_array_leaf_to_non_g2_array,
			Nil,attribute_name_or_index,
			ISVREF(ISVREF(current_subobject,(SI_Long)1L),
			(SI_Long)1L),Nil,Nil,Nil);
	    else if (FIXNUM_GE(attribute_name_or_index,
		    ISVREF(current_subobject,(SI_Long)20L)))
		return record_object_building_problem_on_receiving_side_1(Qleaf_index_out_of_bounds_for_g2_array,
			Nil,attribute_name_or_index,
			ISVREF(ISVREF(current_subobject,(SI_Long)1L),
			(SI_Long)1L),Nil,Nil,Nil);
	    else {
		item_or_datum_qm = leaf;
		element_type = ISVREF(current_subobject,(SI_Long)21L);
		temp_1 =  ! 
			!TRUEP(lookup_global_or_kb_specific_property_value(element_type,
			Class_description_gkbprop)) ? T : Nil;
		if (temp_1);
		else
		    temp_1 = EQ(element_type,Qitem_or_datum) ? T : Nil;
		allow_no_value_p = temp_1;
		PUSH_SPECIAL_WITH_SYMBOL(Allow_no_value_p,Qallow_no_value_p,allow_no_value_p,
			0);
		  if (Allow_no_value_p &&  !TRUEP(item_or_datum_qm))
		      result = g2_array_aset(current_subobject,
			      attribute_name_or_index,Nil);
		  else {
		      temp = 
			      TRUEP(type_specification_type_p(item_or_datum_qm,
			      element_type));
		      if (temp);
		      else {
			  if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) 
				  > (SI_Long)2L &&  
				  !EQ(ISVREF(item_or_datum_qm,(SI_Long)1L),
				  Qavailable_frame_vector)) {
			      x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
			      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				      EQ(ISVREF(x2,(SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? x2 : Qnil;
			  }
			  else
			      gensymed_symbol = Nil;
			  if (gensymed_symbol) {
			      gensymed_symbol_4 = 
				      lookup_global_or_kb_specific_property_value(element_type,
				      Class_description_gkbprop);
			      if (gensymed_symbol_4) {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(gensymed_symbol_4,
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
			  else
			      temp = TRUEP(Nil);
		      }
		      if ( !temp)
			  result = record_object_building_problem_on_receiving_side_1(Qincompatible_type_of_g2_array_leaf,
				  Nil,attribute_name_or_index,
				  ISVREF(ISVREF(current_subobject,
				  (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
		      else
			  result = g2_array_aset(current_subobject,
				  attribute_name_or_index,leaf);
		  }
		POP_SPECIAL();
		return result;
	    }
	}
	else if (EQ(attribute_type,Qlist_element)) {
	    sub_class_bit_vector = ISVREF(ISVREF(current_subobject,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		return record_object_building_problem_on_receiving_side_1(Qadd_g2_list_leaf_to_non_g2_list,
			Nil,attribute_name_or_index,
			ISVREF(ISVREF(current_subobject,(SI_Long)1L),
			(SI_Long)1L),Nil,Nil,Nil);
	    else {
		item_or_datum_qm = leaf;
		element_type = ISVREF(current_subobject,(SI_Long)21L);
		temp_1 =  ! 
			!TRUEP(lookup_global_or_kb_specific_property_value(element_type,
			Class_description_gkbprop)) ? T : Nil;
		if (temp_1);
		else
		    temp_1 = EQ(element_type,Qitem_or_datum) ? T : Nil;
		allow_no_value_p = temp_1;
		PUSH_SPECIAL_WITH_SYMBOL(Allow_no_value_p,Qallow_no_value_p,allow_no_value_p,
			0);
		  temp_1 = Allow_no_value_p ? ( !TRUEP(item_or_datum_qm) ? 
			  T : Nil) : Qnil;
		  if (temp_1)
		      result = VALUES_1(temp_1);
		  else {
		      temp = 
			      TRUEP(type_specification_type_p(item_or_datum_qm,
			      element_type));
		      if (temp);
		      else {
			  if (SIMPLE_VECTOR_P(item_or_datum_qm) && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_datum_qm)) 
				  > (SI_Long)2L &&  
				  !EQ(ISVREF(item_or_datum_qm,(SI_Long)1L),
				  Qavailable_frame_vector)) {
			      x2 = ISVREF(item_or_datum_qm,(SI_Long)1L);
			      gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				      EQ(ISVREF(x2,(SI_Long)0L),
				      Qg2_defstruct_structure_name_class_description_g2_struct) 
				      ? x2 : Qnil;
			  }
			  else
			      gensymed_symbol = Nil;
			  if (gensymed_symbol) {
			      gensymed_symbol_4 = 
				      lookup_global_or_kb_specific_property_value(element_type,
				      Class_description_gkbprop);
			      if (gensymed_symbol_4) {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(gensymed_symbol_4,
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
			  else
			      temp = TRUEP(Nil);
		      }
		      if ( !temp)
			  result = record_object_building_problem_on_receiving_side_1(Qincompatible_type_of_g2_list_leaf,
				  Nil,attribute_name_or_index,
				  ISVREF(ISVREF(current_subobject,
				  (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
		      else
			  result = g2_list_insert_for_object_passing(leaf,
				  current_subobject);
		  }
		POP_SPECIAL();
		return result;
	    }
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qnonexistent_class_for_object_passing;  /* nonexistent-class-for-object-passing */

/* PERMISSIBLE-TO-CREATE-OBJECT-PASSING-CLASS-P */
Object permissible_to_create_object_passing_class_p(class_name)
    Object class_name;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(167,211);
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
    if ( !temp_2)
	return VALUES_2(Nil,Qnonexistent_class_for_object_passing);
    else
	return VALUES_2(T,Nil);
}

/* G2-RESUMABLE-OBJECT-REPROCESSED-P */
Object g2_resumable_object_reprocessed_p(toplevel_object,resumable_object)
    Object toplevel_object, resumable_object;
{
    Object gensymed_symbol, temp, x, y, xa, ya;

    x_note_fn_call(167,212);
    gensymed_symbol = ISVREF(toplevel_object,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(toplevel_object) ? (EQ(ISVREF(toplevel_object,
	    (SI_Long)1L),Qavailable_frame_vector) ? T : Nil) : Qnil;
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? (IFIX(gensymed_symbol) == 
		(SI_Long)-1L ? T : Nil) : Nil;
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(resumable_object,(SI_Long)6L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? (FIXNUM_LT(y,x) ? T : Nil) : T;
	else if (FIXNUMP(x))
	    temp = Nil;
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya) ? T : Nil;
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? (FIXNUM_LT(M_CDR(y),M_CDR(x)) ? 
			T : Nil) : Qnil;
	}
    }
    return VALUES_1(temp);
}

static Object Qpremature_corresponding_index_transmission;  /* premature-corresponding-index-transmission */

/* G2-ADD-RESUMABLE-CIRCULARITY */
Object g2_add_resumable_circularity(corresponding_index)
    Object corresponding_index;
{
    Object current_subobject_qm, svref_arg_1, icp_push_modify_macro_arg, car_1;
    Object cdr_1, svref_new_value;

    x_note_fn_call(167,213);
    if ( !TRUEP(ISVREF(Current_receiving_resumable_object,(SI_Long)10L))) {
	current_subobject_qm = ISVREF(Current_receiving_resumable_object,
		(SI_Long)8L);
	if (current_subobject_qm) {
	    store_corresponding_icp_object(corresponding_index,
		    current_subobject_qm);
	    svref_arg_1 = Current_receiving_resumable_object;
	    icp_push_modify_macro_arg = corresponding_index;
	    car_1 = icp_push_modify_macro_arg;
	    cdr_1 = ISVREF(svref_arg_1,(SI_Long)12L);
	    svref_new_value = icp_cons_1(car_1,cdr_1);
	    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)12L)) = 
		    svref_new_value);
	}
	else
	    return record_object_building_problem_on_receiving_side_1(Qpremature_corresponding_index_transmission,
		    Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qattribute_name_inappropriate_for_class;  /* attribute-name-inappropriate-for-class */

static Object Qadd_g2_array_element_to_non_g2_array;  /* add-g2-array-element-to-non-g2-array */

static Object Qindex_out_of_bounds_for_g2_array;  /* index-out-of-bounds-for-g2-array */

static Object Qadd_g2_list_element_to_non_g2_list;  /* add-g2-list-element-to-non-g2-list */

/* ADD-TO-OR-TRAVERSE-REMOTE-OBJECT */
Object add_to_or_traverse_remote_object(current_subobject,attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name)
    Object current_subobject, attribute_type, attribute_qualifier_qm;
    Object attribute_name_or_index, class_name;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, slot_description_qm;
    Object attribute_contents_qm, gensymed_symbol_4, slot_group_qm, temp_1;
    Object new_object, icp_push_modify_macro_arg, car_1, cdr_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(167,214);
    if (EQ(attribute_type,Qattribute)) {
	if ( !TRUEP(memq_function(attribute_name_or_index,list_constant))) {
	    if (SIMPLE_VECTOR_P(current_subobject) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(current_subobject,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(current_subobject,(SI_Long)1L);
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
			IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
	    slot_description_qm = temp ? 
		    get_slot_description_of_class_description_function(attribute_name_or_index,
		    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(current_subobject,
		    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop),
		    attribute_qualifier_qm) : Nil;
	    if (slot_description_qm) {
		attribute_contents_qm = 
			get_slot_description_value(current_subobject,
			slot_description_qm);
		if ( !TRUEP(Nil)) {
		    attribute_contents_qm = (SI_Long)0L != 
			    (IFIX(ISVREF(current_subobject,(SI_Long)5L)) & 
			    (SI_Long)262144L) ? 
			    make_transient_item(class_name) : 
			    make_frame(class_name);
		    if ( 
			    !TRUEP(get_lookup_slot_value_given_default(attribute_contents_qm,
			    Qobject_passing_info_qm,Nil))) {
			set_non_savable_lookup_slot_value(attribute_contents_qm,
				Qobject_passing_info_qm,
				make_object_passing_info_1());
			gensymed_symbol = attribute_contents_qm;
			gensymed_symbol_4 = Nil;
			slot_group_qm = 
				get_lookup_slot_value_given_default(gensymed_symbol,
				Qobject_passing_info_qm,Nil);
			note_change_to_block_or_struct_or_seq(gensymed_symbol,
				Qobject_passing_info_qm);
			gensymed_symbol_4 = Nil;
			if (slot_group_qm)
			    SVREF(slot_group_qm,FIX((SI_Long)1L)) = 
				    gensymed_symbol_4;
			else if ( !EQ(gensymed_symbol_4,Qt)) {
			    set_non_savable_lookup_slot_value(gensymed_symbol,
				    Qobject_passing_info_qm,
				    make_object_passing_info_1());
			    temp_1 = 
				    get_lookup_slot_value_given_default(gensymed_symbol,
				    Qobject_passing_info_qm,Nil);
			    SVREF(temp_1,FIX((SI_Long)1L)) = gensymed_symbol_4;
			}
		    }
		    change_slot_value_for_object_passing(current_subobject,
			    ISVREF(slot_description_qm,(SI_Long)1L),
			    attribute_contents_qm);
		}
		temp_1 = Current_receiving_resumable_object;
		SVREF(temp_1,FIX((SI_Long)8L)) = attribute_contents_qm;
		return VALUES_1(attribute_contents_qm);
	    }
	    else {
		attribute_contents_qm = (SI_Long)0L != 
			(IFIX(ISVREF(current_subobject,(SI_Long)5L)) & 
			(SI_Long)262144L) ? 
			make_transient_item(class_name) : 
			make_frame(class_name);
		if (change_exported_attribute_for_object_passing(current_subobject,
			attribute_name_or_index,attribute_qualifier_qm,
			attribute_contents_qm)) {
		    if ( 
			    !TRUEP(get_lookup_slot_value_given_default(attribute_contents_qm,
			    Qobject_passing_info_qm,Nil))) {
			set_non_savable_lookup_slot_value(attribute_contents_qm,
				Qobject_passing_info_qm,
				make_object_passing_info_1());
			gensymed_symbol = attribute_contents_qm;
			gensymed_symbol_4 = Nil;
			slot_group_qm = 
				get_lookup_slot_value_given_default(gensymed_symbol,
				Qobject_passing_info_qm,Nil);
			note_change_to_block_or_struct_or_seq(gensymed_symbol,
				Qobject_passing_info_qm);
			gensymed_symbol_4 = Nil;
			if (slot_group_qm)
			    SVREF(slot_group_qm,FIX((SI_Long)1L)) = 
				    gensymed_symbol_4;
			else if ( !EQ(gensymed_symbol_4,Qt)) {
			    set_non_savable_lookup_slot_value(gensymed_symbol,
				    Qobject_passing_info_qm,
				    make_object_passing_info_1());
			    temp_1 = 
				    get_lookup_slot_value_given_default(gensymed_symbol,
				    Qobject_passing_info_qm,Nil);
			    SVREF(temp_1,FIX((SI_Long)1L)) = gensymed_symbol_4;
			}
		    }
		    return VALUES_1(attribute_contents_qm);
		}
		else {
		    if (attribute_contents_qm)
			delete_frame(attribute_contents_qm);
		    return record_object_building_problem_on_receiving_side_1(Qattribute_name_inappropriate_for_class,
			    attribute_qualifier_qm,attribute_name_or_index,
			    class_name,Nil,Nil,Nil);
		}
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(attribute_type,Qvector_element)) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	if ( !temp) {
	    record_object_building_problem_on_receiving_side_1(Qadd_g2_array_element_to_non_g2_array,
		    attribute_qualifier_qm,attribute_name_or_index,
		    class_name,Nil,Nil,Nil);
	    return VALUES_1(Nil);
	}
	else if (FIXNUM_GE(attribute_name_or_index,
		ISVREF(current_subobject,(SI_Long)20L))) {
	    record_object_building_problem_on_receiving_side_1(Qindex_out_of_bounds_for_g2_array,
		    attribute_qualifier_qm,attribute_name_or_index,
		    class_name,Nil,Nil,Nil);
	    return VALUES_1(Nil);
	}
	else {
	    new_object = make_transient_item(class_name);
	    if ( !TRUEP(get_lookup_slot_value_given_default(new_object,
		    Qobject_passing_info_qm,Nil))) {
		set_non_savable_lookup_slot_value(new_object,
			Qobject_passing_info_qm,make_object_passing_info_1());
		gensymed_symbol = new_object;
		gensymed_symbol_4 = Nil;
		slot_group_qm = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		note_change_to_block_or_struct_or_seq(gensymed_symbol,
			Qobject_passing_info_qm);
		gensymed_symbol_4 = Nil;
		if (slot_group_qm)
		    SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_4;
		else if ( !EQ(gensymed_symbol_4,Qt)) {
		    set_non_savable_lookup_slot_value(gensymed_symbol,
			    Qobject_passing_info_qm,
			    make_object_passing_info_1());
		    temp_1 = 
			    get_lookup_slot_value_given_default(gensymed_symbol,
			    Qobject_passing_info_qm,Nil);
		    SVREF(temp_1,FIX((SI_Long)1L)) = gensymed_symbol_4;
		}
	    }
	    g2_array_aset(current_subobject,attribute_name_or_index,
		    new_object);
	    icp_push_modify_macro_arg = 
		    icp_cons_1(Current_receiving_resumable_object,
		    current_subobject);
	    car_1 = icp_push_modify_macro_arg;
	    gensymed_symbol = 
		    get_lookup_slot_value_given_default(new_object,
		    Qobject_passing_info_qm,Nil);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : Nil;
	    cdr_1 = gensymed_symbol;
	    temp_1 = icp_cons_1(car_1,cdr_1);
	    gensymed_symbol = new_object;
	    gensymed_symbol_4 = Nil;
	    slot_group_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    note_change_to_block_or_struct_or_seq(gensymed_symbol,
		    Qobject_passing_info_qm);
	    gensymed_symbol_4 = temp_1;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_4;
	    else if ( !EQ(gensymed_symbol_4,Qnil)) {
		set_non_savable_lookup_slot_value(gensymed_symbol,
			Qobject_passing_info_qm,make_object_passing_info_1());
		temp_1 = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		SVREF(temp_1,FIX((SI_Long)2L)) = gensymed_symbol_4;
	    }
	    temp_1 = Current_receiving_resumable_object;
	    SVREF(temp_1,FIX((SI_Long)8L)) = new_object;
	    return VALUES_1(new_object);
	}
    }
    else if (EQ(attribute_type,Qlist_element)) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	if ( !temp) {
	    record_object_building_problem_on_receiving_side_1(Qadd_g2_list_element_to_non_g2_list,
		    attribute_qualifier_qm,attribute_name_or_index,
		    class_name,Nil,Nil,Nil);
	    return VALUES_1(Nil);
	}
	else {
	    new_object = make_transient_item(class_name);
	    if ( !TRUEP(get_lookup_slot_value_given_default(new_object,
		    Qobject_passing_info_qm,Nil))) {
		set_non_savable_lookup_slot_value(new_object,
			Qobject_passing_info_qm,make_object_passing_info_1());
		gensymed_symbol = new_object;
		gensymed_symbol_4 = Nil;
		slot_group_qm = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		note_change_to_block_or_struct_or_seq(gensymed_symbol,
			Qobject_passing_info_qm);
		gensymed_symbol_4 = Nil;
		if (slot_group_qm)
		    SVREF(slot_group_qm,FIX((SI_Long)1L)) = gensymed_symbol_4;
		else if ( !EQ(gensymed_symbol_4,Qt)) {
		    set_non_savable_lookup_slot_value(gensymed_symbol,
			    Qobject_passing_info_qm,
			    make_object_passing_info_1());
		    temp_1 = 
			    get_lookup_slot_value_given_default(gensymed_symbol,
			    Qobject_passing_info_qm,Nil);
		    SVREF(temp_1,FIX((SI_Long)1L)) = gensymed_symbol_4;
		}
	    }
	    g2_list_insert_for_object_passing(new_object,current_subobject);
	    icp_push_modify_macro_arg = 
		    icp_cons_1(Current_receiving_resumable_object,
		    current_subobject);
	    car_1 = icp_push_modify_macro_arg;
	    gensymed_symbol = 
		    get_lookup_slot_value_given_default(new_object,
		    Qobject_passing_info_qm,Nil);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : Nil;
	    cdr_1 = gensymed_symbol;
	    temp_1 = icp_cons_1(car_1,cdr_1);
	    gensymed_symbol = new_object;
	    gensymed_symbol_4 = Nil;
	    slot_group_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    note_change_to_block_or_struct_or_seq(gensymed_symbol,
		    Qobject_passing_info_qm);
	    gensymed_symbol_4 = temp_1;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_4;
	    else if ( !EQ(gensymed_symbol_4,Qnil)) {
		set_non_savable_lookup_slot_value(gensymed_symbol,
			Qobject_passing_info_qm,make_object_passing_info_1());
		temp_1 = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		SVREF(temp_1,FIX((SI_Long)2L)) = gensymed_symbol_4;
	    }
	    temp_1 = Current_receiving_resumable_object;
	    SVREF(temp_1,FIX((SI_Long)8L)) = new_object;
	    return VALUES_1(new_object);
	}
    }
    else
	return VALUES_1(Qnil);
}

/* G2-BUILD-REMOTE-OBJECT */
Object g2_build_remote_object(attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index,class_name)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name;
{
    Object permissible_p, problem, current_subobject_qm, subobject_qm;
    Object toplevel_object, svref_arg_1, frame_serial_number_setf_arg, old;
    Object new_1, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object slot_group_qm;
    Object result;

    x_note_fn_call(167,215);
    if ( !TRUEP(ISVREF(Current_receiving_resumable_object,(SI_Long)10L))) {
	result = permissible_to_create_object_passing_class_p(class_name);
	MVS_2(result,permissible_p,problem);
	if (permissible_p) {
	    current_subobject_qm = 
		    ISVREF(Current_receiving_resumable_object,(SI_Long)8L);
	    if (current_subobject_qm) {
		subobject_qm = 
			add_to_or_traverse_remote_object(current_subobject_qm,
			attribute_type,attribute_qualifier_qm,
			attribute_name_or_index,class_name);
		return VALUES_1(subobject_qm);
	    }
	    else {
		toplevel_object = make_transient_item(class_name);
		svref_arg_1 = Current_receiving_resumable_object;
		SVREF(svref_arg_1,FIX((SI_Long)7L)) = toplevel_object;
		svref_arg_1 = Current_receiving_resumable_object;
		frame_serial_number_setf_arg = ISVREF(toplevel_object,
			(SI_Long)3L);
		old = ISVREF(svref_arg_1,(SI_Long)6L);
		new_1 = frame_serial_number_setf_arg;
		svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
			(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
			frame_serial_number_setf_helper_1(old,new_1);
		SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
		svref_arg_1 = Current_receiving_resumable_object;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = toplevel_object;
		if ( 
			!TRUEP(get_lookup_slot_value_given_default(toplevel_object,
			Qobject_passing_info_qm,Nil))) {
		    set_non_savable_lookup_slot_value(toplevel_object,
			    Qobject_passing_info_qm,
			    make_object_passing_info_1());
		    gensymed_symbol = toplevel_object;
		    gensymed_symbol_1 = Nil;
		    slot_group_qm = 
			    get_lookup_slot_value_given_default(gensymed_symbol,
			    Qobject_passing_info_qm,Nil);
		    note_change_to_block_or_struct_or_seq(gensymed_symbol,
			    Qobject_passing_info_qm);
		    gensymed_symbol_1 = Nil;
		    if (slot_group_qm)
			SVREF(slot_group_qm,FIX((SI_Long)1L)) = 
				gensymed_symbol_1;
		    else if ( !EQ(gensymed_symbol_1,Qt)) {
			set_non_savable_lookup_slot_value(gensymed_symbol,
				Qobject_passing_info_qm,
				make_object_passing_info_1());
			svref_arg_1 = 
				get_lookup_slot_value_given_default(gensymed_symbol,
				Qobject_passing_info_qm,Nil);
			SVREF(svref_arg_1,FIX((SI_Long)1L)) = 
				gensymed_symbol_1;
		    }
		}
		return VALUES_1(toplevel_object);
	    }
	}
	else {
	    record_object_building_problem_on_receiving_side_1(problem,
		    attribute_qualifier_qm,attribute_name_or_index,
		    class_name,Nil,Nil,Nil);
	    return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qparent_frame;       /* parent-frame */

/* GET-OBJECT-PASSING-PARENT */
Object get_object_passing_parent(object)
    Object object;
{
    Object temp, gensymed_symbol, parent_item_lists_or_arrays;
    Object receiving_resumable_object_qm, parent_object, icp_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2, gensymed_symbol_1, slot_group_qm;
    Object trailing_cons, receiving_resumable_object, ab_loop_list_;
    Object ab_loop_desetq_, reclaimable_cons;

    x_note_fn_call(167,216);
    temp = get_lookup_slot_value_given_default(object,Qparent_frame,Nil);
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol = get_lookup_slot_value_given_default(object,
		Qobject_passing_info_qm,Nil);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : Nil;
	parent_item_lists_or_arrays = gensymed_symbol;
	gensymed_symbol = FIRST(parent_item_lists_or_arrays);
	receiving_resumable_object_qm = CAR(gensymed_symbol);
	parent_object = CDR(gensymed_symbol);
	if (receiving_resumable_object_qm && 
		EQ(receiving_resumable_object_qm,
		Current_receiving_resumable_object)) {
	    icp_pop_store = Nil;
	    gensymed_symbol = get_lookup_slot_value_given_default(object,
		    Qobject_passing_info_qm,Nil);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : Nil;
	    cons_1 = gensymed_symbol;
	    if (cons_1) {
		icp_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cons_1;
		    temp_1 = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		else {
		    temp_1 = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		    temp_1 = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    gensymed_symbol = object;
	    gensymed_symbol_1 = Nil;
	    slot_group_qm = 
		    get_lookup_slot_value_given_default(gensymed_symbol,
		    Qobject_passing_info_qm,Nil);
	    note_change_to_block_or_struct_or_seq(gensymed_symbol,
		    Qobject_passing_info_qm);
	    gensymed_symbol_1 = next_cons;
	    if (slot_group_qm)
		SVREF(slot_group_qm,FIX((SI_Long)2L)) = gensymed_symbol_1;
	    else if ( !EQ(gensymed_symbol_1,Qnil)) {
		set_non_savable_lookup_slot_value(gensymed_symbol,
			Qobject_passing_info_qm,make_object_passing_info_1());
		temp_1 = 
			get_lookup_slot_value_given_default(gensymed_symbol,
			Qobject_passing_info_qm,Nil);
		SVREF(temp_1,FIX((SI_Long)2L)) = gensymed_symbol_1;
	    }
	    reclaim_icp_cons_1(icp_pop_store);
	    return VALUES_1(parent_object);
	}
	else if (receiving_resumable_object_qm) {
	    trailing_cons = parent_item_lists_or_arrays;
	    receiving_resumable_object = Nil;
	    parent_object = Nil;
	    ab_loop_list_ = REST(parent_item_lists_or_arrays);
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(trailing_cons))
		goto end_loop;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    receiving_resumable_object = CAR(ab_loop_desetq_);
	    parent_object = CDR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(receiving_resumable_object,
		    Current_receiving_resumable_object)) {
		reclaimable_cons = CDR(trailing_cons);
		temp_1 = CDDR(trailing_cons);
		M_CDR(trailing_cons) = temp_1;
		reclaim_icp_cons_1(CAR(reclaimable_cons));
		reclaim_icp_cons_1(reclaimable_cons);
		return VALUES_1(parent_object);
	    }
	    trailing_cons = M_CDR(trailing_cons);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qattribute_hierarchy_not_isomorphous;  /* attribute-hierarchy-not-isomorphous */

static Object Qpremature_ascent_of_attribute_hierarchy;  /* premature-ascent-of-attribute-hierarchy */

/* G2-ASCEND-TO-PARENT */
Object g2_ascend_to_parent(ascension_count)
    Object ascension_count;
{
    Object current_subobject_qm, ancestor_qm, svref_arg_1;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(167,217);
    if ( !TRUEP(ISVREF(Current_receiving_resumable_object,(SI_Long)10L))) {
	current_subobject_qm = ISVREF(Current_receiving_resumable_object,
		(SI_Long)8L);
	if (current_subobject_qm) {
	    ab_loop_repeat_ = IFIX(ascension_count);
	    ancestor_qm = current_subobject_qm;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    ancestor_qm = get_object_passing_parent(ancestor_qm);
	    if ( !TRUEP(ancestor_qm)) {
		record_object_building_problem_on_receiving_side_1(Qattribute_hierarchy_not_isomorphous,
			Nil,Nil,Nil,Nil,Nil,Nil);
		goto end_loop;
	    }
	    goto next_loop;
	  end_loop:
	    if (ancestor_qm) {
		svref_arg_1 = Current_receiving_resumable_object;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = ancestor_qm;
	    }
	    return VALUES_1(Qnil);
	}
	else
	    return record_object_building_problem_on_receiving_side_1(Qpremature_ascent_of_attribute_hierarchy,
		    Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_array_length;    /* g2-array-length */

static Object Qitem_array_sent_to_non_item_array_attribute;  /* item-array-sent-to-non-item-array-attribute */

static Object Qitem_array_sent_to_non_item_array_class_definition;  /* item-array-sent-to-non-item-array-class-definition */

/* G2-RECEIVE-ADD-ATTRIBUTE-OBJECT-VECTOR */
Object g2_receive_add_attribute_object_vector(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,resumable_vector_length)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_vector_length;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object new_object_vector_qm, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(167,218);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
		IFIX(ISVREF(Item_array_class_description,(SI_Long)18L));
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
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_26;
	  end_loop_25:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_31:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_32;
	      end_loop_31:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_34:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_35;
	      end_loop_34:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_array_class_description,
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
	    temp_2 =  !temp_2;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    if (temp_2) {
	new_object_vector_qm = g2_build_remote_object(attribute_type,
		attribute_qualifier_qm,attribute_name_or_index,class_name);
	if (SIMPLE_VECTOR_P(new_object_vector_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_object_vector_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(new_object_vector_qm,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(new_object_vector_qm,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_object_vector_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Item_array_class_description,(SI_Long)18L));
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
	    if (temp_2);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(new_object_vector_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
		if (temp_2) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(new_object_vector_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Value_array_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
		    temp_2 =  !temp_2;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    change_slot_value_for_object_passing(new_object_vector_qm,
		    Qg2_array_length,resumable_vector_length);
	else
	    record_object_building_problem_on_receiving_side_1(Qitem_array_sent_to_non_item_array_attribute,
		    Nil,Nil,class_name,Nil,Nil,Nil);
    }
    else
	record_object_building_problem_on_receiving_side_1(Qitem_array_sent_to_non_item_array_class_definition,
		Nil,Nil,class_name,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qg2_array_element_type;  /* g2-array-element-type */

static Object Qdatum;              /* datum */

static Object Qvalue;              /* value */

static Object Qitem_or_value;      /* item-or-value */

static Object Qquantity;           /* quantity */

/* ARRAY-ELEMENT-TYPE-FOR-CLASS */
Object array_element_type_for_class(class_name)
    Object class_name;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, element_type;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(167,219);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
    element_type = 
	    ISVREF(get_slot_description_of_class_description_function(Qg2_array_element_type,
	    gensymed_symbol,Nil),(SI_Long)6L);
    if (EQ(element_type,Qdatum))
	temp_1 = Qvalue;
    else if (EQ(element_type,Qitem_or_datum))
	temp_1 = Qitem_or_value;
    else if (EQ(element_type,Qnumber))
	temp_1 = Qquantity;
    else
	temp_1 = element_type;
    return VALUES_1(temp_1);
}

static Object Qvalue_array_sent_to_non_value_array_attribute;  /* value-array-sent-to-non-value-array-attribute */

static Object Qvalue_array_sent_to_value_array_class_of_wrong_element_type;  /* value-array-sent-to-value-array-class-of-wrong-element-type */

static Object Qvalue_array_sent_to_non_value_array_class_definition;  /* value-array-sent-to-non-value-array-class-definition */

/* G2-RECEIVE-ADD-ATTRIBUTE-VALUE-VECTOR */
Object g2_receive_add_attribute_value_vector(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type,resumable_vector_length)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_vector_length;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object new_value_vector_qm, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(167,220);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
		IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	temp_1 = element_type;
	if (temp_1);
	else
	    temp_1 = Qvalue;
	if (array_or_list_element_type_suitable_p(temp_1,
		array_element_type_for_class(class_name))) {
	    new_value_vector_qm = g2_build_remote_object(attribute_type,
		    attribute_qualifier_qm,attribute_name_or_index,class_name);
	    if (SIMPLE_VECTOR_P(new_value_vector_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value_vector_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(new_value_vector_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(new_value_vector_qm,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		sub_class_bit_vector = ISVREF(ISVREF(new_value_vector_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_array_class_description,
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
	    if (temp_2)
		change_slot_value_for_object_passing(new_value_vector_qm,
			Qg2_array_length,resumable_vector_length);
	    else
		record_object_building_problem_on_receiving_side_1(Qvalue_array_sent_to_non_value_array_attribute,
			Nil,Nil,class_name,Nil,Nil,Nil);
	}
	else
	    record_object_building_problem_on_receiving_side_1(Qvalue_array_sent_to_value_array_class_of_wrong_element_type,
		    Nil,Nil,class_name,Nil,Nil,Nil);
    }
    else
	record_object_building_problem_on_receiving_side_1(Qvalue_array_sent_to_non_value_array_class_definition,
		Nil,Nil,class_name,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

/* OBJECT-PASSING-CLEARS-G2-LIST-P */
Object object_passing_clears_g2_list_p(g2_list)
    Object g2_list;
{
    x_note_fn_call(167,221);
    return VALUES_1(T);
}

static Object Qitem_list_sent_to_non_item_list_attribute;  /* item-list-sent-to-non-item-list-attribute */

static Object Qitem_list_sent_to_non_item_list_class_definition;  /* item-list-sent-to-non-item-list-class-definition */

/* G2-RECEIVE-ADD-ATTRIBUTE-OBJECT-LIST */
Object g2_receive_add_attribute_object_list(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,resumable_list_length)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_list_length;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object new_object_list_qm, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(167,222);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
		IFIX(ISVREF(Item_list_class_description,(SI_Long)18L));
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
		    IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_26;
	  end_loop_25:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_31:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_32;
	      end_loop_31:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_34:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_35;
	      end_loop_34:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_list_class_description,
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
	    temp_2 =  !temp_2;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    if (temp_2) {
	new_object_list_qm = g2_build_remote_object(attribute_type,
		attribute_qualifier_qm,attribute_name_or_index,class_name);
	if (SIMPLE_VECTOR_P(new_object_list_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_object_list_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(new_object_list_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(new_object_list_qm,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    sub_class_bit_vector = ISVREF(ISVREF(new_object_list_qm,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Item_list_class_description,(SI_Long)18L));
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
	    if (temp_2);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(new_object_list_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_list_class_description,(SI_Long)18L));
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
		if (temp_2) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(new_object_list_qm,(SI_Long)1L),
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Value_list_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
		    temp_2 =  !temp_2;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    if (object_passing_clears_g2_list_p(new_object_list_qm))
		clear_g2_list(new_object_list_qm);
	}
	else
	    record_object_building_problem_on_receiving_side_1(Qitem_list_sent_to_non_item_list_attribute,
		    Nil,Nil,class_name,Nil,Nil,Nil);
    }
    else
	record_object_building_problem_on_receiving_side_1(Qitem_list_sent_to_non_item_list_class_definition,
		Nil,Nil,class_name,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qlist_type;          /* list-type */

/* LIST-ELEMENT-TYPE-FOR-CLASS */
Object list_element_type_for_class(class_name)
    Object class_name;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, element_type;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(167,223);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
    element_type = 
	    ISVREF(get_slot_description_of_class_description_function(Qlist_type,
	    gensymed_symbol,Nil),(SI_Long)6L);
    if (EQ(element_type,Qdatum))
	temp_1 = Qvalue;
    else if (EQ(element_type,Qitem_or_datum))
	temp_1 = Qitem_or_value;
    else if (EQ(element_type,Qnumber))
	temp_1 = Qquantity;
    else
	temp_1 = element_type;
    return VALUES_1(temp_1);
}

static Object Qvalue_list_sent_to_non_value_list_attribute;  /* value-list-sent-to-non-value-list-attribute */

static Object Qvalue_list_sent_to_value_list_class_of_wrong_element_type;  /* value-list-sent-to-value-list-class-of-wrong-element-type */

static Object Qvalue_list_sent_to_non_value_list_class_definition;  /* value-list-sent-to-non-value-list-class-definition */

/* G2-RECEIVE-ADD-ATTRIBUTE-VALUE-LIST */
Object g2_receive_add_attribute_value_list(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type,resumable_list_length)
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_list_length;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object new_value_list_qm, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(167,224);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
		IFIX(ISVREF(Value_list_class_description,(SI_Long)18L));
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
	temp_1 = element_type;
	if (temp_1);
	else
	    temp_1 = Qvalue;
	if (array_or_list_element_type_suitable_p(temp_1,
		list_element_type_for_class(class_name))) {
	    new_value_list_qm = g2_build_remote_object(attribute_type,
		    attribute_qualifier_qm,attribute_name_or_index,class_name);
	    if (SIMPLE_VECTOR_P(new_value_list_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value_list_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(new_value_list_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(new_value_list_qm,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		sub_class_bit_vector = ISVREF(ISVREF(new_value_list_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Value_list_class_description,
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
	    if (temp_2) {
		if (object_passing_clears_g2_list_p(new_value_list_qm))
		    clear_g2_list(new_value_list_qm);
	    }
	    else
		record_object_building_problem_on_receiving_side_1(Qvalue_list_sent_to_non_value_list_attribute,
			Nil,Nil,class_name,Nil,Nil,Nil);
	}
	else
	    record_object_building_problem_on_receiving_side_1(Qvalue_list_sent_to_value_list_class_of_wrong_element_type,
		    Nil,Nil,class_name,Nil,Nil,Nil);
    }
    else
	record_object_building_problem_on_receiving_side_1(Qvalue_list_sent_to_non_value_list_class_definition,
		Nil,Nil,class_name,Nil,Nil,Nil);
    return VALUES_1(Nil);
}

/* G2-SEND-ADD-VALUE-VECTOR-RANGE */
Object g2_send_add_value_vector_range(number_of_elements,resumable_node,
	    interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    Object highest_index, internal_vector, element, corresponding_index_qm;
    Object next_interning_index_qm, ab_loop_iter_flag_, icp_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2;
    SI_Long ab_loop_repeat_, vector_index;

    x_note_fn_call(167,225);
    highest_index = ISVREF(resumable_node,(SI_Long)21L);
    write_icp_fixnum(number_of_elements);
    write_icp_fixnum(highest_index);
    if (interning_details_qm) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	corresponding_index_qm = Nil;
	next_interning_index_qm = CAAR(interning_details_qm);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	if (next_interning_index_qm && IFIX(next_interning_index_qm) == 
		vector_index) {
	    corresponding_index_qm = CDAR(interning_details_qm);
	    icp_pop_store = Nil;
	    cons_1 = interning_details_qm;
	    if (cons_1) {
		icp_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    interning_details_qm = next_cons;
	    reclaim_icp_cons_1(icp_pop_store);
	    next_interning_index_qm = CAAR(interning_details_qm);
	}
	else
	    corresponding_index_qm = Nil;
	write_icp_attribute_value(element,corresponding_index_qm);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    else {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	corresponding_index_qm = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	write_icp_attribute_value(element,corresponding_index_qm);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    if (interning_details_qm)
	reclaim_icp_tree_1(interning_details_qm);
    return VALUES_1(Nil);
}

static Object Qindex_out_of_bounds_for_g2_value_array;  /* index-out-of-bounds-for-g2-value-array */

static Object Qunexpected_non_value_array;  /* unexpected-non-value-array */

static Object Qpremature_access_to_toplevel_g2_value_array;  /* premature-access-to-toplevel-g2-value-array */

static Object Qg2_value_array_deleted_during_object_passing;  /* g2-value-array-deleted-during-object-passing */

static Object Qvalue_array_contains_an_element_inappropriate_for_receiving_array;  /* value-array-contains-an-element-inappropriate-for-receiving-array */

/* G2-RECEIVE-ADD-VALUE-VECTOR-RANGE */
Object g2_receive_add_value_vector_range(number_of_elements,highest_index)
    Object number_of_elements, highest_index;
{
    Object current_subobject_qm, x2, sub_class_bit_vector, value_array_p;
    Object internal_vector, ab_loop_iter_flag_, array_element_type_1;
    Object item_or_value_qm, new_value, thing, svref_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, ab_loop_repeat_, index_1;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(167,226);
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (SIMPLE_VECTOR_P(current_subobject_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(current_subobject_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(current_subobject_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject_qm,
		(SI_Long)1L),(SI_Long)19L);
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
	    value_array_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    value_array_p = Nil;
	if (value_array_p && FIXNUM_GE(highest_index,
		ISVREF(current_subobject_qm,(SI_Long)20L)))
	    record_object_building_problem_on_receiving_side_1(Qindex_out_of_bounds_for_g2_value_array,
		    Nil,highest_index,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
	else if (value_array_p);
	else
	    record_object_building_problem_on_receiving_side_1(Qunexpected_non_value_array,
		    Nil,Nil,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
    }
    else if ( !TRUEP(current_subobject_qm))
	record_object_building_problem_on_receiving_side_1(Qpremature_access_to_toplevel_g2_value_array,
		Nil,Nil,Nil,Nil,Nil,Nil);
    else
	record_object_building_problem_on_receiving_side_1(Qg2_value_array_deleted_during_object_passing,
		Nil,Nil,Nil,Nil,Nil,Nil);
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L))
	current_subobject_qm = Nil;
    if (current_subobject_qm) {
	if ( !TRUEP(ISVREF(current_subobject_qm,(SI_Long)23L)))
	    initialize_g2_array(current_subobject_qm);
	internal_vector = ISVREF(current_subobject_qm,(SI_Long)23L);
    }
    else
	internal_vector = Nil;
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	read_icp_attribute_value();
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    else {
	array_element_type_1 = ISVREF(current_subobject_qm,(SI_Long)21L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	item_or_value_qm = Nil;
	new_value = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	item_or_value_qm = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	new_value = read_icp_attribute_value();
	if (type_specification_type_p(new_value,array_element_type_1)) {
	    if (item_or_value_qm) {
		if (SIMPLE_VECTOR_P(item_or_value_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value_qm)) 
			> (SI_Long)2L) {
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
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		item_or_value_qm = 
			reclaim_managed_number_or_value_function(item_or_value_qm);
	    if (FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
		ISVREF(internal_vector,svref_arg_2) = new_value;
	    }
	    else {
		svref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = index_1 & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = new_value;
	    }
	}
	else {
	    new_value = reclaim_managed_number_or_value_function(new_value);
	    record_object_building_problem_on_receiving_side_1(Qvalue_array_contains_an_element_inappropriate_for_receiving_array,
		    Nil,Nil,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(Nil);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-FLOAT-VECTOR-RANGE */
Object write_icp_add_homogeneous_float_vector_range(resumable_node,
	    number_of_elements,highest_index)
    Object resumable_node, number_of_elements, highest_index;
{
    Object internal_vector, ab_loop_iter_flag_, svref_new_value;
    SI_Long ab_loop_repeat_, vector_index;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(167,227);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	write_icp_double_float_1(DFLOAT_ISAREF_1(ISVREF(internal_vector,
		(vector_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
		vector_index & (SI_Long)1023L));
	svref_new_value = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = svref_new_value;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-NON-FLOAT-VECTOR-RANGE */
Object write_icp_add_homogeneous_non_float_vector_range(resumable_node,
	    number_of_elements,highest_index,element_type,interning_details_qm)
    Object resumable_node, number_of_elements, highest_index, element_type;
    Object interning_details_qm;
{
    Object internal_vector, element, ab_loop_iter_flag_, temp;
    Object next_interning_index_qm, corresponding_index_qm, temp_1;
    Object icp_pop_store, cons_1, next_cons, svref_arg_2;
    SI_Long ab_loop_repeat_, vector_index;

    x_note_fn_call(167,228);
    if (EQ(element_type,Qinteger)) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	write_icp_fixnum(element);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    else if (EQ(element_type,Qtext)) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	write_icp_text_string(element);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (EQ(element_type,Qtruth)) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_2:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_2;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	write_icp_evaluation_truth_value(element);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_2;
      end_loop_2:;
    }
    else if (EQ(element_type,Qsymbol)) {
	internal_vector = ISVREF(resumable_node,(SI_Long)20L);
	ab_loop_repeat_ = IFIX(number_of_elements);
	vector_index = IFIX(highest_index);
	element = Nil;
	next_interning_index_qm = CAAR(interning_details_qm);
	corresponding_index_qm = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_3:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_3;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    vector_index = vector_index - (SI_Long)1L;
	element = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		vector_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(vector_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),vector_index & (SI_Long)1023L);
	if (next_interning_index_qm && IFIX(next_interning_index_qm) == 
		vector_index) {
	    temp_1 = CDAR(interning_details_qm);
	    icp_pop_store = Nil;
	    cons_1 = interning_details_qm;
	    if (cons_1) {
		icp_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qicp);
		if (ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_icp_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_icp_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_icp_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    interning_details_qm = next_cons;
	    reclaim_icp_cons_1(icp_pop_store);
	    next_interning_index_qm = CAAR(interning_details_qm);
	    corresponding_index_qm = temp_1;
	}
	else
	    corresponding_index_qm = Nil;
	write_icp_possibly_interned_symbol(element,corresponding_index_qm);
	temp = FIXNUM_SUB1(ISVREF(resumable_node,(SI_Long)21L));
	SVREF(resumable_node,FIX((SI_Long)21L)) = temp;
	ab_loop_iter_flag_ = Nil;
	goto next_loop_3;
      end_loop_3:;
    }
    if (interning_details_qm)
	reclaim_icp_tree_1(interning_details_qm);
    return VALUES_1(Nil);
}

/* READ-ICP-ADD-HOMOGENEOUS-FLOAT-VECTOR-RANGE */
Object read_icp_add_homogeneous_float_vector_range(number_of_elements,
	    highest_index,internal_vector)
    Object number_of_elements, highest_index, internal_vector;
{
    Object ab_loop_iter_flag_, aref_arg_1;
    SI_Long ab_loop_repeat_, index_1, aref_arg_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(167,229);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    read_icp_double_float_1();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:;
	}
	else {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    aref_new_value = read_icp_double_float_1();
	    aref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    aref_arg_2 = index_1 & (SI_Long)1023L;
	    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* READ-ICP-ADD-HOMOGENEOUS-NON-FLOAT-VECTOR-RANGE */
Object read_icp_add_homogeneous_non_float_vector_range(number_of_elements,
	    highest_index,internal_vector,element_type)
    Object number_of_elements, highest_index, internal_vector, element_type;
{
    Object ab_loop_iter_flag_, element, svref_arg_1, temp, thing;
    SI_Long ab_loop_repeat_, index_1, svref_arg_2;

    x_note_fn_call(167,230);
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L)) {
	if (EQ(element_type,Qinteger)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    read_icp_fixnum();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:;
	}
	else if (EQ(element_type,Qtext)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    reclaim_text_string(read_icp_text_string());
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else if (EQ(element_type,Qtruth)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    read_icp_integer();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_2;
	  end_loop_2:;
	}
	else if (EQ(element_type,Qsymbol)) {
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    read_icp_possibly_interned_symbol();
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:;
	}
    }
    else if (EQ(element_type,Qinteger)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_4:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_4;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	element = read_icp_fixnum();
	if (FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    ISVREF(internal_vector,svref_arg_2) = element;
	}
	else {
	    svref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = element;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_4;
      end_loop_4:;
    }
    else if (EQ(element_type,Qtext)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_5:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_5;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	temp = read_icp_text_string();
	thing = FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(internal_vector,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(internal_vector,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	    reclaim_wide_string(thing);
	element = temp;
	if (FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    ISVREF(internal_vector,svref_arg_2) = element;
	}
	else {
	    svref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = element;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_5;
      end_loop_5:;
    }
    else if (EQ(element_type,Qtruth)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_6:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_6;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	element = read_icp_integer();
	if (FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    ISVREF(internal_vector,svref_arg_2) = element;
	}
	else {
	    svref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = element;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_6;
      end_loop_6:;
    }
    else if (EQ(element_type,Qsymbol)) {
	ab_loop_repeat_ = IFIX(number_of_elements);
	index_1 = IFIX(highest_index);
	element = Nil;
	ab_loop_iter_flag_ = T;
      next_loop_7:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_7;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    index_1 = index_1 - (SI_Long)1L;
	element = read_icp_possibly_interned_symbol();
	if (FIXNUM_LE(ISVREF(internal_vector,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	    ISVREF(internal_vector,svref_arg_2) = element;
	}
	else {
	    svref_arg_1 = ISVREF(internal_vector,(index_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = index_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = element;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_7;
      end_loop_7:;
    }
    return VALUES_1(Nil);
}

/* G2-SEND-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object g2_send_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    Object highest_index;

    x_note_fn_call(167,231);
    highest_index = ISVREF(resumable_node,(SI_Long)21L);
    write_icp_fixnum(number_of_elements);
    write_icp_resumable_sequence_element_type(element_type);
    write_icp_fixnum(highest_index);
    if (EQ(element_type,QFLOAT))
	write_icp_add_homogeneous_float_vector_range(resumable_node,
		number_of_elements,highest_index);
    else
	write_icp_add_homogeneous_non_float_vector_range(resumable_node,
		number_of_elements,highest_index,element_type,
		interning_details_qm);
    return VALUES_1(Nil);
}

/* G2-RECEIVE-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object g2_receive_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,highest_index)
    Object number_of_elements, element_type, highest_index;
{
    Object current_subobject_qm, x2, sub_class_bit_vector, value_array_p;
    Object internal_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(167,232);
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (SIMPLE_VECTOR_P(current_subobject_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_subobject_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(current_subobject_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(current_subobject_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(current_subobject_qm,
		(SI_Long)1L),(SI_Long)19L);
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
	    value_array_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    value_array_p = Nil;
	if (value_array_p && FIXNUM_GE(highest_index,
		ISVREF(current_subobject_qm,(SI_Long)20L)))
	    record_object_building_problem_on_receiving_side_1(Qindex_out_of_bounds_for_g2_value_array,
		    Nil,highest_index,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
	else if (value_array_p);
	else
	    record_object_building_problem_on_receiving_side_1(Qunexpected_non_value_array,
		    Nil,Nil,ISVREF(ISVREF(current_subobject_qm,
		    (SI_Long)1L),(SI_Long)1L),Nil,Nil,Nil);
    }
    else if ( !TRUEP(current_subobject_qm))
	record_object_building_problem_on_receiving_side_1(Qpremature_access_to_toplevel_g2_value_array,
		Nil,Nil,Nil,Nil,Nil,Nil);
    else
	record_object_building_problem_on_receiving_side_1(Qg2_value_array_deleted_during_object_passing,
		Nil,Nil,Nil,Nil,Nil,Nil);
    if (ISVREF(Current_receiving_resumable_object,(SI_Long)10L))
	current_subobject_qm = Nil;
    if (current_subobject_qm) {
	if ( !TRUEP(ISVREF(current_subobject_qm,(SI_Long)23L)))
	    initialize_g2_array(current_subobject_qm);
	internal_vector = ISVREF(current_subobject_qm,(SI_Long)23L);
    }
    else
	internal_vector = Nil;
    if (EQ(element_type,QFLOAT))
	read_icp_add_homogeneous_float_vector_range(number_of_elements,
		highest_index,internal_vector);
    else
	read_icp_add_homogeneous_non_float_vector_range(number_of_elements,
		highest_index,internal_vector,element_type);
    return VALUES_1(Nil);
}

void g2_rpc2_INIT()
{
    Object temp, reclaim_structure_for_resumable_circular_node_1;
    Object reclaim_structure_for_resumable_value_node_1;
    Object reclaim_structure_for_resumable_instance_or_complex_value_node_mixin_1;
    Object reclaim_structure_for_resumable_instance_node_mixin_1;
    Object reclaim_structure_for_resumable_object_node_1;
    Object reclaim_structure_for_resumable_sequence_node_mixin_1;
    Object reclaim_structure_for_resumable_vector_node_mixin_1;
    Object reclaim_structure_for_resumable_object_vector_node_1;
    Object reclaim_structure_for_resumable_value_vector_node_1;
    Object reclaim_structure_for_resumable_history_node_1;
    Object reclaim_structure_for_resumable_list_node_mixin_1;
    Object reclaim_structure_for_resumable_object_list_node_1;
    Object reclaim_structure_for_resumable_value_list_node_1;
    Object reclaim_structure_for_resumable_evaluation_sequence_node_mixin_1;
    Object reclaim_structure_for_resumable_evaluation_sequence_node_1;
    Object reclaim_structure_for_resumable_evaluation_structure_node_1;
    Object reclaim_structure_for_sending_resumable_object_1;
    Object reclaim_structure_for_object_passing_info_1, temp_1;
    Object AB_package, string_constant_55, string_constant_54, Qrpc_common2;
    Object Qg2_rpc2, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qslot_value_reclaimer, Qreclaim_object_passing_info_qm_value;
    Object Qclasses_which_define, Qcleanup, Qsystem_item;
    Object Qcleanup_for_system_item, Qdeactivate, Qdeactivate_for_system_item;
    Object Qreclaim_icp_port_entry_for_class_description, Qclass_description;
    Object list_constant_3, Qicp_object_map_for_class_description;
    Object Qreclaim_icp_port_entry_for_registered_item, Qregistered_item;
    Object list_constant_2, Qicp_object_map_for_registered_item;
    Object Qobject_passing_info, Qreclaim_structure;
    Object Qoutstanding_object_passing_info_count;
    Object Qobject_passing_info_structure_memory_usage, Qutilities2;
    Object string_constant_53, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_object_passing_info_g2_struct;
    Object string_constant_52, Qsending_resumable_object;
    Object Qoutstanding_sending_resumable_object_count;
    Object Qsending_resumable_object_structure_memory_usage;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qout_object_circularity_hashtable_hash_vector_131_vectors;
    Object Qobject_circularity_hashtable_hash_vector_131_vector_memory_usage;
    Object string_constant_48, Qresumable_evaluation_structure_node;
    Object Qoutstanding_resumable_evaluation_structure_node_count;
    Object Qresumable_evaluation_structure_node_structure_memory_usage;
    Object string_constant_47, string_constant_46;
    Object Qresumable_evaluation_sequence_node;
    Object Qoutstanding_resumable_evaluation_sequence_node_count;
    Object Qresumable_evaluation_sequence_node_structure_memory_usage;
    Object string_constant_45, string_constant_44;
    Object Qresumable_evaluation_sequence_node_mixin;
    Object Qoutstanding_resumable_evaluation_sequence_node_mixin_count;
    Object Qresumable_evaluation_sequence_node_mixin_structure_memory_usage;
    Object string_constant_43, string_constant_42, Qresumable_value_list_node;
    Object Qoutstanding_resumable_value_list_node_count;
    Object Qresumable_value_list_node_structure_memory_usage;
    Object string_constant_41, string_constant_30, string_constant_40;
    Object Qresumable_object_list_node;
    Object Qoutstanding_resumable_object_list_node_count;
    Object Qresumable_object_list_node_structure_memory_usage;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object Qresumable_list_node_mixin;
    Object Qoutstanding_resumable_list_node_mixin_count;
    Object Qresumable_list_node_mixin_structure_memory_usage;
    Object string_constant_36, string_constant_35, Qresumable_history_node;
    Object Qoutstanding_resumable_history_node_count;
    Object Qresumable_history_node_structure_memory_usage, string_constant_34;
    Object string_constant_33, string_constant_32;
    Object Qresumable_value_vector_node;
    Object Qoutstanding_resumable_value_vector_node_count;
    Object Qresumable_value_vector_node_structure_memory_usage;
    Object string_constant_31, string_constant_29;
    Object Qresumable_object_vector_node;
    Object Qoutstanding_resumable_object_vector_node_count;
    Object Qresumable_object_vector_node_structure_memory_usage;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object Qresumable_vector_node_mixin;
    Object Qoutstanding_resumable_vector_node_mixin_count;
    Object Qresumable_vector_node_mixin_structure_memory_usage;
    Object string_constant_25, string_constant_24;
    Object Qresumable_sequence_node_mixin;
    Object Qoutstanding_resumable_sequence_node_mixin_count;
    Object Qresumable_sequence_node_mixin_structure_memory_usage;
    Object string_constant_23, string_constant_22, Qresumable_object_node;
    Object Qoutstanding_resumable_object_node_count;
    Object Qresumable_object_node_structure_memory_usage, string_constant_21;
    Object string_constant_20, string_constant_19;
    Object Qresumable_instance_node_mixin;
    Object Qoutstanding_resumable_instance_node_mixin_count;
    Object Qresumable_instance_node_mixin_structure_memory_usage;
    Object string_constant_18, string_constant_17;
    Object Qresumable_instance_or_complex_value_node_mixin;
    Object Qoutstanding_resumable_instance_or_complex_value_node_mixin_count;
    Object Qresumable_instance_or_complex_value_node_mixin_structure_memory_usage;
    Object string_constant_16, string_constant_15, Qresumable_value_node;
    Object Qoutstanding_resumable_value_node_count;
    Object Qresumable_value_node_structure_memory_usage, string_constant_14;
    Object string_constant_13, Qresumable_circular_node;
    Object Qoutstanding_resumable_circular_node_count;
    Object Qresumable_circular_node_structure_memory_usage, string_constant_12;
    Object string_constant_11;

    x_note_fn_call(167,233);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-CIRCULAR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qresumable_circular_node = STATIC_SYMBOL("RESUMABLE-CIRCULAR-NODE",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_circular_node_g2_struct,
	    Qresumable_circular_node,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qresumable_circular_node,
	    Qg2_defstruct_structure_name_resumable_circular_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_circular_node == UNBOUND)
	The_type_description_of_resumable_circular_node = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8m83mMy1o83mMy83*By8n8k1l83*By0000001m1m8x83*By1n8y83-5Sy1n830ny83-Bsy83=jykok0k0");
    temp = The_type_description_of_resumable_circular_node;
    The_type_description_of_resumable_circular_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_11));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_circular_node_g2_struct,
	    The_type_description_of_resumable_circular_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qresumable_circular_node,
	    The_type_description_of_resumable_circular_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_circular_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-CIRCULAR-NODE-COUNT",
	    AB_package);
    Qresumable_circular_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-CIRCULAR-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_12 = STATIC_STRING("1q83mMy8s83-mby09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_circular_node_count);
    push_optimized_constant(Qresumable_circular_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_12));
    Qchain_of_available_resumable_circular_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-CIRCULAR-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_circular_nodes,
	    Chain_of_available_resumable_circular_nodes);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_resumable_circular_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_circular_node_count = 
	    STATIC_SYMBOL("RESUMABLE-CIRCULAR-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_circular_node_count,
	    Resumable_circular_node_count);
    record_system_variable(Qresumable_circular_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_circular_nodes_vector == UNBOUND)
	Chain_of_available_resumable_circular_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_circular_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_circular_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_circular_node_count,
	    STATIC_FUNCTION(outstanding_resumable_circular_node_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_resumable_circular_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_circular_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_circular_node,
	    reclaim_structure_for_resumable_circular_node_1);
    Qg2_defstruct_structure_name_resumable_value_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_value_node = STATIC_SYMBOL("RESUMABLE-VALUE-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_node_g2_struct,
	    Qresumable_value_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_value_node,
	    Qg2_defstruct_structure_name_resumable_value_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_value_node == UNBOUND)
	The_type_description_of_resumable_value_node = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8m83mUy1o83mUy83*By8n8k1l83*By0000001m1m8x83*By1n8y83-5ay1n830ny83-Bry83=jykpk0k0");
    temp = The_type_description_of_resumable_value_node;
    The_type_description_of_resumable_value_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_13));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_node_g2_struct,
	    The_type_description_of_resumable_value_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_value_node,
	    The_type_description_of_resumable_value_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_value_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-VALUE-NODE-COUNT",AB_package);
    Qresumable_value_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_14 = STATIC_STRING("1q83mUy8s83-msy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_value_node_count);
    push_optimized_constant(Qresumable_value_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_14));
    Qchain_of_available_resumable_value_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-VALUE-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_value_nodes,
	    Chain_of_available_resumable_value_nodes);
    record_system_variable(Qchain_of_available_resumable_value_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_value_node_count = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_value_node_count,
	    Resumable_value_node_count);
    record_system_variable(Qresumable_value_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_value_nodes_vector == UNBOUND)
	Chain_of_available_resumable_value_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_value_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_value_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_value_node_count,
	    STATIC_FUNCTION(outstanding_resumable_value_node_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_resumable_value_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_value_node,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_value_node,
	    reclaim_structure_for_resumable_value_node_1);
    Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct 
	    = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_instance_or_complex_value_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct,
	    Qresumable_instance_or_complex_value_node_mixin,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_instance_or_complex_value_node_mixin,
	    Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_instance_or_complex_value_node_mixin 
	    == UNBOUND)
	The_type_description_of_resumable_instance_or_complex_value_node_mixin 
		= Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83*jy1p83*jy83*cy83*By8n8k1l83*cy0000001l1m8x83*cykuk0k0");
    temp = 
	    The_type_description_of_resumable_instance_or_complex_value_node_mixin;
    The_type_description_of_resumable_instance_or_complex_value_node_mixin 
	    = load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_instance_or_complex_value_node_mixin_g2_struct,
	    The_type_description_of_resumable_instance_or_complex_value_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_instance_or_complex_value_node_mixin,
	    The_type_description_of_resumable_instance_or_complex_value_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_instance_or_complex_value_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_instance_or_complex_value_node_mixin_structure_memory_usage 
	    = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_16 = STATIC_STRING("1q83*jy8s83-mjy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_instance_or_complex_value_node_mixin_count);
    push_optimized_constant(Qresumable_instance_or_complex_value_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_resumable_instance_or_complex_value_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_instance_or_complex_value_node_mixins,
	    Chain_of_available_resumable_instance_or_complex_value_node_mixins);
    record_system_variable(Qchain_of_available_resumable_instance_or_complex_value_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_instance_or_complex_value_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-OR-COMPLEX-VALUE-NODE-MIXIN-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_instance_or_complex_value_node_mixin_count,
	    Resumable_instance_or_complex_value_node_mixin_count);
    record_system_variable(Qresumable_instance_or_complex_value_node_mixin_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector 
	    == UNBOUND)
	Chain_of_available_resumable_instance_or_complex_value_node_mixins_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_instance_or_complex_value_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_instance_or_complex_value_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_instance_or_complex_value_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_instance_or_complex_value_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_instance_or_complex_value_node_mixin_1 
	    = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_instance_or_complex_value_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_instance_or_complex_value_node_mixin,
	    reclaim_structure_for_resumable_instance_or_complex_value_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_instance_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE-MIXIN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct,
	    Qresumable_instance_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_instance_node_mixin,
	    Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_instance_node_mixin == UNBOUND)
	The_type_description_of_resumable_instance_node_mixin = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m83=Wy1q83=Wy83*jy83*cy83*By8n8k1l83*jy0000001l1m8x83*jyk3Eyk0k0");
    temp = The_type_description_of_resumable_instance_node_mixin;
    The_type_description_of_resumable_instance_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_instance_node_mixin_g2_struct,
	    The_type_description_of_resumable_instance_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_instance_node_mixin,
	    The_type_description_of_resumable_instance_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_instance_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-INSTANCE-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_instance_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_18 = STATIC_STRING("1q83=Wy8s83-miy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_instance_node_mixin_count);
    push_optimized_constant(Qresumable_instance_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_resumable_instance_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-INSTANCE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_instance_node_mixins,
	    Chain_of_available_resumable_instance_node_mixins);
    record_system_variable(Qchain_of_available_resumable_instance_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_instance_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_instance_node_mixin_count,
	    Resumable_instance_node_mixin_count);
    record_system_variable(Qresumable_instance_node_mixin_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_instance_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_instance_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_instance_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_instance_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_instance_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_instance_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_instance_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_instance_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_instance_node_mixin,
	    reclaim_structure_for_resumable_instance_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_object_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_object_node = STATIC_SYMBOL("RESUMABLE-OBJECT-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_node_g2_struct,
	    Qresumable_object_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_object_node,
	    Qg2_defstruct_structure_name_resumable_object_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_object_node == UNBOUND)
	The_type_description_of_resumable_object_node = Nil;
    string_constant_19 = 
	    STATIC_STRING("43Dy8m83mRy1r83mRy83=Wy83*jy83*cy83*By8n8k1l83=Wy0000001n1m8x83=Wy1n8y83-5Xy1r830oy832Iy831qy832Oy830ny832Hy83=jy1m83My83-B-yk3E");
    string_constant_20 = STATIC_STRING("yk0k0");
    temp = The_type_description_of_resumable_object_node;
    The_type_description_of_resumable_object_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_19,
	    string_constant_20)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_node_g2_struct,
	    The_type_description_of_resumable_object_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_object_node,
	    The_type_description_of_resumable_object_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_object_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-OBJECT-NODE-COUNT",
	    AB_package);
    Qresumable_object_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_21 = STATIC_STRING("1q83mRy8s83-moy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_object_node_count);
    push_optimized_constant(Qresumable_object_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_resumable_object_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-OBJECT-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_object_nodes,
	    Chain_of_available_resumable_object_nodes);
    record_system_variable(Qchain_of_available_resumable_object_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_object_node_count = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_object_node_count,
	    Resumable_object_node_count);
    record_system_variable(Qresumable_object_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_object_nodes_vector == UNBOUND)
	Chain_of_available_resumable_object_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_object_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_object_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_object_node_count,
	    STATIC_FUNCTION(outstanding_resumable_object_node_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_resumable_object_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_object_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_object_node,
	    reclaim_structure_for_resumable_object_node_1);
    Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-SEQUENCE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_sequence_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-SEQUENCE-NODE-MIXIN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct,
	    Qresumable_sequence_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_sequence_node_mixin,
	    Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_sequence_node_mixin == UNBOUND)
	The_type_description_of_resumable_sequence_node_mixin = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m830Ry1r830Ry83=Wy83*jy83*cy83*By8n8k1l83=Wy0000001l1m8x83=Wyk3Gyk0k0");
    temp = The_type_description_of_resumable_sequence_node_mixin;
    The_type_description_of_resumable_sequence_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_sequence_node_mixin_g2_struct,
	    The_type_description_of_resumable_sequence_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_sequence_node_mixin,
	    The_type_description_of_resumable_sequence_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_sequence_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-SEQUENCE-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_sequence_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-SEQUENCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_23 = STATIC_STRING("1q830Ry8s83-mqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_sequence_node_mixin_count);
    push_optimized_constant(Qresumable_sequence_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_resumable_sequence_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-SEQUENCE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_sequence_node_mixins,
	    Chain_of_available_resumable_sequence_node_mixins);
    record_system_variable(Qchain_of_available_resumable_sequence_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_sequence_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-SEQUENCE-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_sequence_node_mixin_count,
	    Resumable_sequence_node_mixin_count);
    record_system_variable(Qresumable_sequence_node_mixin_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_sequence_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_sequence_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_sequence_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_sequence_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_sequence_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_sequence_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_sequence_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_sequence_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_sequence_node_mixin,
	    reclaim_structure_for_resumable_sequence_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VECTOR-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_vector_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-VECTOR-NODE-MIXIN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct,
	    Qresumable_vector_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_vector_node_mixin,
	    Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_vector_node_mixin == UNBOUND)
	The_type_description_of_resumable_vector_node_mixin = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m837Oy1s837Oy830Ry83=Wy83*jy83*cy83*By8n8k1l830Ry0000001l1m8x830Ryk3Hyk0k0");
    temp = The_type_description_of_resumable_vector_node_mixin;
    The_type_description_of_resumable_vector_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_vector_node_mixin_g2_struct,
	    The_type_description_of_resumable_vector_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_vector_node_mixin,
	    The_type_description_of_resumable_vector_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_vector_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-VECTOR-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_vector_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-VECTOR-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_25 = STATIC_STRING("1q837Oy8s83-muy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_vector_node_mixin_count);
    push_optimized_constant(Qresumable_vector_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_resumable_vector_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-VECTOR-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_vector_node_mixins,
	    Chain_of_available_resumable_vector_node_mixins);
    record_system_variable(Qchain_of_available_resumable_vector_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_vector_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-VECTOR-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_vector_node_mixin_count,
	    Resumable_vector_node_mixin_count);
    record_system_variable(Qresumable_vector_node_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_vector_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_vector_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_vector_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_vector_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_vector_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_vector_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_vector_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_vector_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_vector_node_mixin,
	    reclaim_structure_for_resumable_vector_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-VECTOR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_object_vector_node = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-VECTOR-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct,
	    Qresumable_object_vector_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_object_vector_node,
	    Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_object_vector_node == UNBOUND)
	The_type_description_of_resumable_object_vector_node = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8m83mSy1t83mSy837Oy830Ry83=Wy83*jy83*cy83*By8n8k1l837Oy0000001m1m8x837Oy1n8y83-5Yy1t830oy832Iy831qy832Oy830ny832Hy833Yy83Shy");
    string_constant_27 = STATIC_STRING("83=jyk3Jyk0k0");
    temp = The_type_description_of_resumable_object_vector_node;
    The_type_description_of_resumable_object_vector_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_26,
	    string_constant_27)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_vector_node_g2_struct,
	    The_type_description_of_resumable_object_vector_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_object_vector_node,
	    The_type_description_of_resumable_object_vector_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_object_vector_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-OBJECT-VECTOR-NODE-COUNT",
	    AB_package);
    Qresumable_object_vector_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-VECTOR-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_28 = STATIC_STRING("1q83mSy8s83-mpy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_object_vector_node_count);
    push_optimized_constant(Qresumable_object_vector_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_28));
    Qchain_of_available_resumable_object_vector_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-OBJECT-VECTOR-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_object_vector_nodes,
	    Chain_of_available_resumable_object_vector_nodes);
    record_system_variable(Qchain_of_available_resumable_object_vector_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_object_vector_node_count = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-VECTOR-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_object_vector_node_count,
	    Resumable_object_vector_node_count);
    record_system_variable(Qresumable_object_vector_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_object_vector_nodes_vector == UNBOUND)
	Chain_of_available_resumable_object_vector_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_object_vector_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_object_vector_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_object_vector_node_count,
	    STATIC_FUNCTION(outstanding_resumable_object_vector_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_object_vector_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_object_vector_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_object_vector_node,
	    reclaim_structure_for_resumable_object_vector_node_1);
    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-VECTOR-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_value_vector_node = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-VECTOR-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct,
	    Qresumable_value_vector_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_value_vector_node,
	    Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_value_vector_node == UNBOUND)
	The_type_description_of_resumable_value_vector_node = Nil;
    string_constant_29 = 
	    STATIC_STRING("43Dy8m83mVy1t83mVy837Oy830Ry83=Wy83*jy83*cy83*By8n8k1l837Oy0000001m1m8x837Oy1n8y83-5by1t830oy832Iy831qy832Oy830ny832Hy833Yy83Shy");
    string_constant_30 = STATIC_STRING("83=jyk3Iyk0k0");
    temp = The_type_description_of_resumable_value_vector_node;
    The_type_description_of_resumable_value_vector_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_29,
	    string_constant_30)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_vector_node_g2_struct,
	    The_type_description_of_resumable_value_vector_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_value_vector_node,
	    The_type_description_of_resumable_value_vector_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_value_vector_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-VALUE-VECTOR-NODE-COUNT",
	    AB_package);
    Qresumable_value_vector_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-VECTOR-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_31 = STATIC_STRING("1q83mVy8s83-mty09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_value_vector_node_count);
    push_optimized_constant(Qresumable_value_vector_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_resumable_value_vector_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-VALUE-VECTOR-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_value_vector_nodes,
	    Chain_of_available_resumable_value_vector_nodes);
    record_system_variable(Qchain_of_available_resumable_value_vector_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_value_vector_node_count = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-VECTOR-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_value_vector_node_count,
	    Resumable_value_vector_node_count);
    record_system_variable(Qresumable_value_vector_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_value_vector_nodes_vector == UNBOUND)
	Chain_of_available_resumable_value_vector_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_value_vector_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_value_vector_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_value_vector_node_count,
	    STATIC_FUNCTION(outstanding_resumable_value_vector_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_value_vector_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_value_vector_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_value_vector_node,
	    reclaim_structure_for_resumable_value_vector_node_1);
    if (Size_of_cached_subsequence_for_resumable_history == UNBOUND)
	Size_of_cached_subsequence_for_resumable_history = FIX((SI_Long)128L);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qg2_defstruct_structure_name_resumable_history_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-HISTORY-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_history_node = STATIC_SYMBOL("RESUMABLE-HISTORY-NODE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_history_node_g2_struct,
	    Qresumable_history_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_history_node,
	    Qg2_defstruct_structure_name_resumable_history_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_history_node == UNBOUND)
	The_type_description_of_resumable_history_node = Nil;
    string_constant_32 = 
	    STATIC_STRING("43Dy8m83mPy1s83mPy830Ry83=Wy83*jy83*cy83*By8n8k1l830Ry0000001m1m8x830Ry1n8y83-5Vy1s830oy832Iy831qy832Oy830ny832Hy833Yy83=jyk3Ryk");
    string_constant_33 = STATIC_STRING("0k0");
    temp = The_type_description_of_resumable_history_node;
    The_type_description_of_resumable_history_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_32,
	    string_constant_33)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_history_node_g2_struct,
	    The_type_description_of_resumable_history_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_history_node,
	    The_type_description_of_resumable_history_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_history_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-HISTORY-NODE-COUNT",
	    AB_package);
    Qresumable_history_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-HISTORY-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_34 = STATIC_STRING("1q83mPy8s83-mfy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_history_node_count);
    push_optimized_constant(Qresumable_history_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_34));
    Qchain_of_available_resumable_history_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-HISTORY-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_history_nodes,
	    Chain_of_available_resumable_history_nodes);
    record_system_variable(Qchain_of_available_resumable_history_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_history_node_count = 
	    STATIC_SYMBOL("RESUMABLE-HISTORY-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_history_node_count,
	    Resumable_history_node_count);
    record_system_variable(Qresumable_history_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_history_nodes_vector == UNBOUND)
	Chain_of_available_resumable_history_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_history_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_history_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_history_node_count,
	    STATIC_FUNCTION(outstanding_resumable_history_node_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_resumable_history_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_history_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_history_node,
	    reclaim_structure_for_resumable_history_node_1);
    Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-LIST-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_list_node_mixin = STATIC_SYMBOL("RESUMABLE-LIST-NODE-MIXIN",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct,
	    Qresumable_list_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_list_node_mixin,
	    Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_list_node_mixin == UNBOUND)
	The_type_description_of_resumable_list_node_mixin = Nil;
    string_constant_35 = 
	    STATIC_STRING("43Dy8m837Ny1s837Ny830Ry83=Wy83*jy83*cy83*By8n8k1l830Ry0000001l1m8x830Ryk3Hyk0k0");
    temp = The_type_description_of_resumable_list_node_mixin;
    The_type_description_of_resumable_list_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_35));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_list_node_mixin_g2_struct,
	    The_type_description_of_resumable_list_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_list_node_mixin,
	    The_type_description_of_resumable_list_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_list_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-LIST-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_list_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-LIST-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_36 = STATIC_STRING("1q837Ny8s83-mky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_list_node_mixin_count);
    push_optimized_constant(Qresumable_list_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_36));
    Qchain_of_available_resumable_list_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-LIST-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_list_node_mixins,
	    Chain_of_available_resumable_list_node_mixins);
    record_system_variable(Qchain_of_available_resumable_list_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_list_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-LIST-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_list_node_mixin_count,
	    Resumable_list_node_mixin_count);
    record_system_variable(Qresumable_list_node_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_list_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_list_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_list_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_list_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_list_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_list_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_list_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_list_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_list_node_mixin,
	    reclaim_structure_for_resumable_list_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-LIST-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_object_list_node = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-LIST-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct,
	    Qresumable_object_list_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_object_list_node,
	    Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_object_list_node == UNBOUND)
	The_type_description_of_resumable_object_list_node = Nil;
    string_constant_37 = 
	    STATIC_STRING("43Dy8m83mQy1t83mQy837Ny830Ry83=Wy83*jy83*cy83*By8n8k1l837Ny0000001m1m8x837Ny1n8y83-5Wy1t830oy832Iy831qy832Oy830ny832Hy83SXy833Yy");
    string_constant_38 = STATIC_STRING("83=jyk3Hyk0k0");
    temp = The_type_description_of_resumable_object_list_node;
    The_type_description_of_resumable_object_list_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_37,
	    string_constant_38)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_list_node_g2_struct,
	    The_type_description_of_resumable_object_list_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_object_list_node,
	    The_type_description_of_resumable_object_list_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_object_list_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-OBJECT-LIST-NODE-COUNT",
	    AB_package);
    Qresumable_object_list_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-LIST-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_39 = STATIC_STRING("1q83mQy8s83-mmy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_object_list_node_count);
    push_optimized_constant(Qresumable_object_list_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_39));
    Qchain_of_available_resumable_object_list_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-OBJECT-LIST-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_object_list_nodes,
	    Chain_of_available_resumable_object_list_nodes);
    record_system_variable(Qchain_of_available_resumable_object_list_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_object_list_node_count = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-LIST-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_object_list_node_count,
	    Resumable_object_list_node_count);
    record_system_variable(Qresumable_object_list_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_object_list_nodes_vector == UNBOUND)
	Chain_of_available_resumable_object_list_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_object_list_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_object_list_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_object_list_node_count,
	    STATIC_FUNCTION(outstanding_resumable_object_list_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_object_list_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_object_list_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_object_list_node,
	    reclaim_structure_for_resumable_object_list_node_1);
    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-LIST-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_value_list_node = STATIC_SYMBOL("RESUMABLE-VALUE-LIST-NODE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct,
	    Qresumable_value_list_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_value_list_node,
	    Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_value_list_node == UNBOUND)
	The_type_description_of_resumable_value_list_node = Nil;
    string_constant_40 = 
	    STATIC_STRING("43Dy8m83mTy1t83mTy837Ny830Ry83=Wy83*jy83*cy83*By8n8k1l837Ny0000001m1m8x837Ny1n8y83-5Zy1t830oy832Iy831qy832Oy830ny832Hy83SXy833Yy");
    temp = The_type_description_of_resumable_value_list_node;
    The_type_description_of_resumable_value_list_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_30)));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_value_list_node_g2_struct,
	    The_type_description_of_resumable_value_list_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_value_list_node,
	    The_type_description_of_resumable_value_list_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_value_list_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-VALUE-LIST-NODE-COUNT",
	    AB_package);
    Qresumable_value_list_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-LIST-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_41 = STATIC_STRING("1q83mTy8s83-mry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_value_list_node_count);
    push_optimized_constant(Qresumable_value_list_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_41));
    Qchain_of_available_resumable_value_list_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-VALUE-LIST-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_value_list_nodes,
	    Chain_of_available_resumable_value_list_nodes);
    record_system_variable(Qchain_of_available_resumable_value_list_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_value_list_node_count = 
	    STATIC_SYMBOL("RESUMABLE-VALUE-LIST-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_value_list_node_count,
	    Resumable_value_list_node_count);
    record_system_variable(Qresumable_value_list_node_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_value_list_nodes_vector == UNBOUND)
	Chain_of_available_resumable_value_list_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_value_list_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_value_list_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_value_list_node_count,
	    STATIC_FUNCTION(outstanding_resumable_value_list_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_value_list_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_value_list_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_value_list_node,
	    reclaim_structure_for_resumable_value_list_node_1);
    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct 
	    = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_evaluation_sequence_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct,
	    Qresumable_evaluation_sequence_node_mixin,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_evaluation_sequence_node_mixin,
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_evaluation_sequence_node_mixin 
	    == UNBOUND)
	The_type_description_of_resumable_evaluation_sequence_node_mixin = Nil;
    string_constant_42 = 
	    STATIC_STRING("43Dy8m837My1q837My83*jy83*cy83*By8n8k1l83*jy0000001l1m8x83*jykxk0k0");
    temp = The_type_description_of_resumable_evaluation_sequence_node_mixin;
    The_type_description_of_resumable_evaluation_sequence_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_42));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_mixin_g2_struct,
	    The_type_description_of_resumable_evaluation_sequence_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_evaluation_sequence_node_mixin,
	    The_type_description_of_resumable_evaluation_sequence_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_evaluation_sequence_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_evaluation_sequence_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_43 = STATIC_STRING("1q837My8s83-mdy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_evaluation_sequence_node_mixin_count);
    push_optimized_constant(Qresumable_evaluation_sequence_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_43));
    Qchain_of_available_resumable_evaluation_sequence_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_evaluation_sequence_node_mixins,
	    Chain_of_available_resumable_evaluation_sequence_node_mixins);
    record_system_variable(Qchain_of_available_resumable_evaluation_sequence_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_evaluation_sequence_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-MIXIN-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_evaluation_sequence_node_mixin_count,
	    Resumable_evaluation_sequence_node_mixin_count);
    record_system_variable(Qresumable_evaluation_sequence_node_mixin_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_evaluation_sequence_node_mixins_vector 
	    == UNBOUND)
	Chain_of_available_resumable_evaluation_sequence_node_mixins_vector 
		= make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_evaluation_sequence_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_evaluation_sequence_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_evaluation_sequence_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_evaluation_sequence_node_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_evaluation_sequence_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_evaluation_sequence_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_evaluation_sequence_node_mixin,
	    reclaim_structure_for_resumable_evaluation_sequence_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct 
	    = STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_evaluation_sequence_node = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct,
	    Qresumable_evaluation_sequence_node,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_evaluation_sequence_node,
	    Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_evaluation_sequence_node == UNBOUND)
	The_type_description_of_resumable_evaluation_sequence_node = Nil;
    string_constant_44 = 
	    STATIC_STRING("43Dy8m83mNy1r83mNy837My83*jy83*cy83*By8n8k1l837My0000001m1m8x837My1n8y83-5Ty1n830oy83Z3y83=jykxk0k0");
    temp = The_type_description_of_resumable_evaluation_sequence_node;
    The_type_description_of_resumable_evaluation_sequence_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_44));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_sequence_node_g2_struct,
	    The_type_description_of_resumable_evaluation_sequence_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_evaluation_sequence_node,
	    The_type_description_of_resumable_evaluation_sequence_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_evaluation_sequence_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-EVALUATION-SEQUENCE-NODE-COUNT",
	    AB_package);
    Qresumable_evaluation_sequence_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_45 = STATIC_STRING("1q83mNy8s83-mcy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_evaluation_sequence_node_count);
    push_optimized_constant(Qresumable_evaluation_sequence_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_45));
    Qchain_of_available_resumable_evaluation_sequence_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-EVALUATION-SEQUENCE-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_evaluation_sequence_nodes,
	    Chain_of_available_resumable_evaluation_sequence_nodes);
    record_system_variable(Qchain_of_available_resumable_evaluation_sequence_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_evaluation_sequence_node_count = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-SEQUENCE-NODE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_evaluation_sequence_node_count,
	    Resumable_evaluation_sequence_node_count);
    record_system_variable(Qresumable_evaluation_sequence_node_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_evaluation_sequence_nodes_vector == 
	    UNBOUND)
	Chain_of_available_resumable_evaluation_sequence_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_evaluation_sequence_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_evaluation_sequence_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_evaluation_sequence_node_count,
	    STATIC_FUNCTION(outstanding_resumable_evaluation_sequence_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_evaluation_sequence_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_evaluation_sequence_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_evaluation_sequence_node,
	    reclaim_structure_for_resumable_evaluation_sequence_node_1);
    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct 
	    = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-STRUCTURE-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_evaluation_structure_node = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-STRUCTURE-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct,
	    Qresumable_evaluation_structure_node,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_evaluation_structure_node,
	    Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_evaluation_structure_node == UNBOUND)
	The_type_description_of_resumable_evaluation_structure_node = Nil;
    string_constant_46 = 
	    STATIC_STRING("43Dy8m83mOy1r83mOy837My83*jy83*cy83*By8n8k1l837My0000001m1m8x837My1n8y83-5Uy1n830oy83Z3y83=jykyk0k0");
    temp = The_type_description_of_resumable_evaluation_structure_node;
    The_type_description_of_resumable_evaluation_structure_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_46));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_evaluation_structure_node_g2_struct,
	    The_type_description_of_resumable_evaluation_structure_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_evaluation_structure_node,
	    The_type_description_of_resumable_evaluation_structure_node,
	    Qtype_description_of_type);
    Qoutstanding_resumable_evaluation_structure_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-EVALUATION-STRUCTURE-NODE-COUNT",
	    AB_package);
    Qresumable_evaluation_structure_node_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-STRUCTURE-NODE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_47 = STATIC_STRING("1q83mOy8s83-mey09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_evaluation_structure_node_count);
    push_optimized_constant(Qresumable_evaluation_structure_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_47));
    Qchain_of_available_resumable_evaluation_structure_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-EVALUATION-STRUCTURE-NODES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_evaluation_structure_nodes,
	    Chain_of_available_resumable_evaluation_structure_nodes);
    record_system_variable(Qchain_of_available_resumable_evaluation_structure_nodes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_evaluation_structure_node_count = 
	    STATIC_SYMBOL("RESUMABLE-EVALUATION-STRUCTURE-NODE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_evaluation_structure_node_count,
	    Resumable_evaluation_structure_node_count);
    record_system_variable(Qresumable_evaluation_structure_node_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_evaluation_structure_nodes_vector == 
	    UNBOUND)
	Chain_of_available_resumable_evaluation_structure_nodes_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_evaluation_structure_node_structure_memory_usage,
	    STATIC_FUNCTION(resumable_evaluation_structure_node_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_evaluation_structure_node_count,
	    STATIC_FUNCTION(outstanding_resumable_evaluation_structure_node_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_evaluation_structure_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_evaluation_structure_node,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_evaluation_structure_node,
	    reclaim_structure_for_resumable_evaluation_structure_node_1);
    Qavailable_object_circularity_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("AVAILABLE-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_object_circularity_hashtable_hash_vector_131_vectors,
	    Available_object_circularity_hashtable_hash_vector_131_vectors);
    record_system_variable(Qavailable_object_circularity_hashtable_hash_vector_131_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_object_circularity_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("COUNT-OF-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_object_circularity_hashtable_hash_vector_131_vectors,
	    Count_of_object_circularity_hashtable_hash_vector_131_vectors);
    record_system_variable(Qcount_of_object_circularity_hashtable_hash_vector_131_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_object_circularity_hashtable_hash_vector_131_vectors_vector 
	    == UNBOUND)
	Available_object_circularity_hashtable_hash_vector_131_vectors_vector 
		= make_thread_array(Nil);
    Qout_object_circularity_hashtable_hash_vector_131_vectors = 
	    STATIC_SYMBOL("OUT-OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTORS",
	    AB_package);
    Qobject_circularity_hashtable_hash_vector_131_vector_memory_usage = 
	    STATIC_SYMBOL("OBJECT-CIRCULARITY-HASHTABLE-HASH-VECTOR-131-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_48 = STATIC_STRING("1q83-hIy83*9y83-P6y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_object_circularity_hashtable_hash_vector_131_vectors);
    push_optimized_constant(Qobject_circularity_hashtable_hash_vector_131_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_48));
    SET_SYMBOL_FUNCTION(Qobject_circularity_hashtable_hash_vector_131_vector_memory_usage,
	    STATIC_FUNCTION(object_circularity_hashtable_hash_vector_131_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_object_circularity_hashtable_hash_vector_131_vectors,
	    STATIC_FUNCTION(out_object_circularity_hashtable_hash_vector_131_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qobject_circularity_hashtable_tree_for_hash = 
	    STATIC_SYMBOL("OBJECT-CIRCULARITY-HASHTABLE-TREE-FOR-HASH",
	    AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qg2_defstruct_structure_name_sending_resumable_object_g2_struct = 
	    STATIC_SYMBOL("SENDING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsending_resumable_object = STATIC_SYMBOL("SENDING-RESUMABLE-OBJECT",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_sending_resumable_object_g2_struct,
	    Qsending_resumable_object,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsending_resumable_object,
	    Qg2_defstruct_structure_name_sending_resumable_object_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_sending_resumable_object == UNBOUND)
	The_type_description_of_sending_resumable_object = Nil;
    string_constant_49 = 
	    STATIC_STRING("43Dy8m83mjy1p83mjy83Emy834Xy8n8k1l83Emy0000001n1m8x83Emy1m83My83-B0y1n8y83-5ky1w83-C*y83-7wy83-F8y83tGy83-C-y83-Bvy83-Buy83-C+y8");
    string_constant_50 = STATIC_STRING("3-FFy83-Bwy83-Bty83-Bxyk3Jyk0k0");
    temp = The_type_description_of_sending_resumable_object;
    The_type_description_of_sending_resumable_object = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_49,
	    string_constant_50)));
    mutate_global_property(Qg2_defstruct_structure_name_sending_resumable_object_g2_struct,
	    The_type_description_of_sending_resumable_object,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsending_resumable_object,
	    The_type_description_of_sending_resumable_object,
	    Qtype_description_of_type);
    Qoutstanding_sending_resumable_object_count = 
	    STATIC_SYMBOL("OUTSTANDING-SENDING-RESUMABLE-OBJECT-COUNT",
	    AB_package);
    Qsending_resumable_object_structure_memory_usage = 
	    STATIC_SYMBOL("SENDING-RESUMABLE-OBJECT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_51 = STATIC_STRING("1q83mjy8s83-o9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sending_resumable_object_count);
    push_optimized_constant(Qsending_resumable_object_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_51));
    Qchain_of_available_sending_resumable_objects = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SENDING-RESUMABLE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sending_resumable_objects,
	    Chain_of_available_sending_resumable_objects);
    record_system_variable(Qchain_of_available_sending_resumable_objects,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsending_resumable_object_count = 
	    STATIC_SYMBOL("SENDING-RESUMABLE-OBJECT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsending_resumable_object_count,
	    Sending_resumable_object_count);
    record_system_variable(Qsending_resumable_object_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_sending_resumable_objects_vector == UNBOUND)
	Chain_of_available_sending_resumable_objects_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsending_resumable_object_structure_memory_usage,
	    STATIC_FUNCTION(sending_resumable_object_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_sending_resumable_object_count,
	    STATIC_FUNCTION(outstanding_sending_resumable_object_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_sending_resumable_object_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_sending_resumable_object,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsending_resumable_object,
	    reclaim_structure_for_sending_resumable_object_1);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qresumable_object = STATIC_SYMBOL("RESUMABLE-OBJECT",AB_package);
    Qname_of_corresponding_icp_object_index_space = 
	    STATIC_SYMBOL("NAME-OF-CORRESPONDING-ICP-OBJECT-INDEX-SPACE",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (The_type_description_of_object_passing_info == UNBOUND)
	The_type_description_of_object_passing_info = Nil;
    string_constant_52 = 
	    STATIC_STRING("43Dy8m83lBy1m83lBy8k1l8k0000001m1m83*gy9k1m83=ey3-Wykok0k0");
    temp = The_type_description_of_object_passing_info;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_object_passing_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_52));
    Qg2_defstruct_structure_name_object_passing_info_g2_struct = 
	    STATIC_SYMBOL("OBJECT-PASSING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_object_passing_info_g2_struct,
	    The_type_description_of_object_passing_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qobject_passing_info = STATIC_SYMBOL("OBJECT-PASSING-INFO",AB_package);
    mutate_global_property(Qobject_passing_info,
	    The_type_description_of_object_passing_info,
	    Qtype_description_of_type);
    Qoutstanding_object_passing_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-OBJECT-PASSING-INFO-COUNT",AB_package);
    Qobject_passing_info_structure_memory_usage = 
	    STATIC_SYMBOL("OBJECT-PASSING-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_53 = STATIC_STRING("1q83lBy8s83-hLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_object_passing_info_count);
    push_optimized_constant(Qobject_passing_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_53));
    Qchain_of_available_object_passing_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-OBJECT-PASSING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_object_passing_infos,
	    Chain_of_available_object_passing_infos);
    record_system_variable(Qchain_of_available_object_passing_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qobject_passing_info_count = STATIC_SYMBOL("OBJECT-PASSING-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qobject_passing_info_count,
	    Object_passing_info_count);
    record_system_variable(Qobject_passing_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_object_passing_infos_vector == UNBOUND)
	Chain_of_available_object_passing_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qobject_passing_info_structure_memory_usage,
	    STATIC_FUNCTION(object_passing_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_object_passing_info_count,
	    STATIC_FUNCTION(outstanding_object_passing_info_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_object_passing_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_object_passing_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qobject_passing_info,
	    reclaim_structure_for_object_passing_info_1);
    Qobject_passing_info_qm = STATIC_SYMBOL("OBJECT-PASSING-INFO\?",
	    AB_package);
    if (G2_to_g2_uses_references_p == UNBOUND)
	G2_to_g2_uses_references_p = Nil;
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qgsi_references_in_use = STATIC_SYMBOL("GSI-REFERENCES-IN-USE",AB_package);
    Qgsi_interface_name = STATIC_SYMBOL("GSI-INTERFACE-NAME",AB_package);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qgsi_collection_interval = STATIC_SYMBOL("GSI-COLLECTION-INTERVAL",
	    AB_package);
    Qitem_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_registered_item = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-REGISTERED-ITEM",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_registered_item,
	    STATIC_FUNCTION(establish_new_object_index_for_registered_item,
	    NIL,TRUE,2,3));
    Qgsi_data_service = STATIC_SYMBOL("GSI-DATA-SERVICE",AB_package);
    Qmake_corresponding_icp_registered_item = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-REGISTERED-ITEM",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_registered_item,
	    STATIC_FUNCTION(make_corresponding_icp_registered_item,NIL,
	    FALSE,1,1));
    Qset_access_form_for_registered_item = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-REGISTERED-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_registered_item,
	    STATIC_FUNCTION(set_access_form_for_registered_item,NIL,FALSE,
	    2,2));
    Qregistered_item = STATIC_SYMBOL("REGISTERED-ITEM",AB_package);
    Qicp_object_map_for_registered_item = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REGISTERED-ITEM",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_registered_item,Qregistered_item);
    initialize_icp_object_type_compile(Qregistered_item,Qitem_index_space,
	    list_constant_2);
    Qreclaim_icp_port_entry_for_registered_item = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-REGISTERED-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_registered_item,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_registered_item,NIL,
	    FALSE,2,2));
    initialize_icp_object_type(Qregistered_item,Qnil,Qnil,
	    Qreclaim_icp_port_entry_for_registered_item);
    Qestablish_new_object_index_for_class_description = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-CLASS-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_class_description,
	    STATIC_FUNCTION(establish_new_object_index_for_class_description,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_class_description = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-CLASS-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_class_description,
	    STATIC_FUNCTION(make_corresponding_icp_class_description,NIL,
	    FALSE,1,1));
    Qset_access_form_for_class_description = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-CLASS-DESCRIPTION",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_class_description,
	    STATIC_FUNCTION(set_access_form_for_class_description,NIL,
	    FALSE,2,2));
    Qclass_description = STATIC_SYMBOL("CLASS-DESCRIPTION",AB_package);
    Qicp_object_map_for_class_description = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-CLASS-DESCRIPTION",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_class_description,Qclass_description);
    initialize_icp_object_type_compile(Qclass_description,
	    Qitem_index_space,list_constant_3);
    Qreclaim_icp_port_entry_for_class_description = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-CLASS-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_class_description,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_class_description,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qclass_description,Qnil,Qnil,
	    Qreclaim_icp_port_entry_for_class_description);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qdeactivate_for_system_item = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-SYSTEM-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_system_item,
	    STATIC_FUNCTION(deactivate_for_system_item,NIL,FALSE,1,1));
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdeactivate_for_system_item);
    set_get(Qsystem_item,Qdeactivate,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_1 = CONS(Qsystem_item,temp);
    mutate_global_property(Qdeactivate,temp_1,Qclasses_which_define);
    Qcleanup_for_system_item = STATIC_SYMBOL("CLEANUP-FOR-SYSTEM-ITEM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_system_item,
	    STATIC_FUNCTION(cleanup_for_system_item,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcleanup_for_system_item);
    set_get(Qsystem_item,Qcleanup,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_1 = CONS(Qsystem_item,temp);
    mutate_global_property(Qcleanup,temp_1,Qclasses_which_define);
    Qreclaim_object_passing_info_qm_value = 
	    STATIC_SYMBOL("RECLAIM-OBJECT-PASSING-INFO\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_object_passing_info_qm_value,
	    STATIC_FUNCTION(reclaim_object_passing_info_qm_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qobject_passing_info_qm,
	    SYMBOL_FUNCTION(Qreclaim_object_passing_info_qm_value),
	    Qslot_value_reclaimer);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    string_constant_1 = 
	    STATIC_STRING("An error occurred while attempting to register ~NF ~\n                      on the network: ~A");
    string_constant_2 = 
	    STATIC_STRING("An error occurred while attempting to register ~\n                      an argument on the network: ~A");
    QFLOAT = STATIC_SYMBOL("float",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth = STATIC_SYMBOL("TRUTH",AB_package);
    Qvector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qname,Qvalue);
    Qhistory = STATIC_SYMBOL("HISTORY",AB_package);
    Kabort_preflighting_resumable_object = 
	    STATIC_SYMBOL("ABORT-PREFLIGHTING-RESUMABLE-OBJECT",Pkeyword);
    Qsending_a_non_object_by_copy_to_a_pre_release_5_g2_or_gsi = 
	    STATIC_SYMBOL("SENDING-A-NON-OBJECT-BY-COPY-TO-A-PRE-RELEASE-5-G2-OR-GSI",
	    AB_package);
    string_constant_3 = STATIC_STRING("~NF is not an object");
    Kfinished_preflighting_resumable_object = 
	    STATIC_SYMBOL("FINISHED-PREFLIGHTING-RESUMABLE-OBJECT",Pkeyword);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Ksuspend_preflighting_resumable_object = 
	    STATIC_SYMBOL("SUSPEND-PREFLIGHTING-RESUMABLE-OBJECT",Pkeyword);
    Qlist_element = STATIC_SYMBOL("LIST-ELEMENT",AB_package);
    string_constant_4 = 
	    STATIC_STRING("The remote procedure call ~NF has been aborted ~\n                   while sending: ~A");
    string_constant_5 = 
	    STATIC_STRING("A remote procedure call has been aborted while sending: ~A");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtry_to_transmit_resumable_object = 
	    STATIC_SYMBOL("TRY-TO-TRANSMIT-RESUMABLE-OBJECT",AB_package);
    Qtry_to_preflight_resumable_object = 
	    STATIC_SYMBOL("TRY-TO-PREFLIGHT-RESUMABLE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qtry_to_preflight_resumable_object,
	    STATIC_FUNCTION(try_to_preflight_resumable_object,NIL,FALSE,1,1));
    Qrpc_object_arguments_to_run_or_schedule_qm = 
	    STATIC_SYMBOL("RPC-OBJECT-ARGUMENTS-TO-RUN-OR-SCHEDULE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrpc_object_arguments_to_run_or_schedule_qm,
	    Rpc_object_arguments_to_run_or_schedule_qm);
    Qg2_rpc2 = STATIC_SYMBOL("G2-RPC2",AB_package);
    record_system_variable(Qrpc_object_arguments_to_run_or_schedule_qm,
	    Qg2_rpc2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qreference = STATIC_SYMBOL("REFERENCE",AB_package);
    if (Default_most_recent_bandwidth_per_timeslice == UNBOUND)
	Default_most_recent_bandwidth_per_timeslice = FIX((SI_Long)8192L);
    if (Minimum_bandwidth_per_timeslice == UNBOUND)
	Minimum_bandwidth_per_timeslice = FIX((SI_Long)4096L);
    Qmost_recent_bandwidth_per_timeslice_qm = 
	    STATIC_SYMBOL("MOST-RECENT-BANDWIDTH-PER-TIMESLICE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_recent_bandwidth_per_timeslice_qm,
	    Most_recent_bandwidth_per_timeslice_qm);
    Qrpc_common2 = STATIC_SYMBOL("RPC-COMMON2",AB_package);
    record_system_variable(Qmost_recent_bandwidth_per_timeslice_qm,
	    Qrpc_common2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Kabort_transmitting_resumable_object = 
	    STATIC_SYMBOL("ABORT-TRANSMITTING-RESUMABLE-OBJECT",Pkeyword);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_6 = STATIC_STRING("The G2 value-list ~NF");
    string_constant_7 = STATIC_STRING(" at top level in the argument list");
    string_constant_8 = STATIC_STRING(", being sent as a subobject of ~NF, ");
    string_constant_9 = STATIC_STRING("has had its length changed");
    Qg2_value_list_length_changed = 
	    STATIC_SYMBOL("G2-VALUE-LIST-LENGTH-CHANGED",AB_package);
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    Qindefinite = STATIC_SYMBOL("INDEFINITE",AB_package);
    Qcurrent_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("CURRENT-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    string_constant_10 = STATIC_STRING("~A");
    Qreclaim_text_string = STATIC_SYMBOL("RECLAIM-TEXT-STRING",AB_package);
    string_constant_54 = 
	    STATIC_STRING("1l1n83iuy1o1m9k831Sy1m9k83*ly1m9k83-Ty1m9k830Cy83gRy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_54));
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    Qproblem_putting_current_value_into_history_keeper = 
	    STATIC_SYMBOL("PROBLEM-PUTTING-CURRENT-VALUE-INTO-HISTORY-KEEPER",
	    AB_package);
    Qproblem_putting_current_value_into_variable_or_parameter = 
	    STATIC_SYMBOL("PROBLEM-PUTTING-CURRENT-VALUE-INTO-VARIABLE-OR-PARAMETER",
	    AB_package);
    Qunable_to_set_current_value_because_item_is_not_a_variable_or_parameter 
	    = 
	    STATIC_SYMBOL("UNABLE-TO-SET-CURRENT-VALUE-BECAUSE-ITEM-IS-NOT-A-VARIABLE-OR-PARAMETER",
	    AB_package);
    string_constant_55 = 
	    STATIC_STRING("1l1n83iuy1n1m9k83=hy1m9k83-Ty1m9k83Ry83=hy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_55));
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qinappropriate_item_for_system_attribute = 
	    STATIC_SYMBOL("INAPPROPRIATE-ITEM-FOR-SYSTEM-ATTRIBUTE",
	    AB_package);
    Qaction = STATIC_SYMBOL("ACTION",AB_package);
    Qedit_attribute = STATIC_SYMBOL("EDIT-ATTRIBUTE",AB_package);
    Qexternal_java_class = STATIC_SYMBOL("EXTERNAL-JAVA-CLASS",AB_package);
    Qcompilation_unit = STATIC_SYMBOL("COMPILATION-UNIT",AB_package);
    Qpackage_declaration = STATIC_SYMBOL("PACKAGE-DECLARATION",AB_package);
    Qimport_declarations = STATIC_SYMBOL("IMPORT-DECLARATIONS",AB_package);
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qimport_declarations,
	    Qpackage_declaration,Qtext,Qname,Qcurrent_value);
    Qleaf_value_inappropriate_for_attribute = 
	    STATIC_SYMBOL("LEAF-VALUE-INAPPROPRIATE-FOR-ATTRIBUTE",AB_package);
    Qleaf_attribute_name_inappropriate_for_class = 
	    STATIC_SYMBOL("LEAF-ATTRIBUTE-NAME-INAPPROPRIATE-FOR-CLASS",
	    AB_package);
    Qadd_g2_array_leaf_to_non_g2_array = 
	    STATIC_SYMBOL("ADD-G2-ARRAY-LEAF-TO-NON-G2-ARRAY",AB_package);
    Qleaf_index_out_of_bounds_for_g2_array = 
	    STATIC_SYMBOL("LEAF-INDEX-OUT-OF-BOUNDS-FOR-G2-ARRAY",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qincompatible_type_of_g2_array_leaf = 
	    STATIC_SYMBOL("INCOMPATIBLE-TYPE-OF-G2-ARRAY-LEAF",AB_package);
    Qadd_g2_list_leaf_to_non_g2_list = 
	    STATIC_SYMBOL("ADD-G2-LIST-LEAF-TO-NON-G2-LIST",AB_package);
    Qincompatible_type_of_g2_list_leaf = 
	    STATIC_SYMBOL("INCOMPATIBLE-TYPE-OF-G2-LIST-LEAF",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qnonexistent_class_for_object_passing = 
	    STATIC_SYMBOL("NONEXISTENT-CLASS-FOR-OBJECT-PASSING",AB_package);
    Qpremature_corresponding_index_transmission = 
	    STATIC_SYMBOL("PREMATURE-CORRESPONDING-INDEX-TRANSMISSION",
	    AB_package);
    Qattribute_name_inappropriate_for_class = 
	    STATIC_SYMBOL("ATTRIBUTE-NAME-INAPPROPRIATE-FOR-CLASS",AB_package);
    Qadd_g2_array_element_to_non_g2_array = 
	    STATIC_SYMBOL("ADD-G2-ARRAY-ELEMENT-TO-NON-G2-ARRAY",AB_package);
    Qindex_out_of_bounds_for_g2_array = 
	    STATIC_SYMBOL("INDEX-OUT-OF-BOUNDS-FOR-G2-ARRAY",AB_package);
    Qadd_g2_list_element_to_non_g2_list = 
	    STATIC_SYMBOL("ADD-G2-LIST-ELEMENT-TO-NON-G2-LIST",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qattribute_hierarchy_not_isomorphous = 
	    STATIC_SYMBOL("ATTRIBUTE-HIERARCHY-NOT-ISOMORPHOUS",AB_package);
    Qpremature_ascent_of_attribute_hierarchy = 
	    STATIC_SYMBOL("PREMATURE-ASCENT-OF-ATTRIBUTE-HIERARCHY",
	    AB_package);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qitem_array_sent_to_non_item_array_attribute = 
	    STATIC_SYMBOL("ITEM-ARRAY-SENT-TO-NON-ITEM-ARRAY-ATTRIBUTE",
	    AB_package);
    Qitem_array_sent_to_non_item_array_class_definition = 
	    STATIC_SYMBOL("ITEM-ARRAY-SENT-TO-NON-ITEM-ARRAY-CLASS-DEFINITION",
	    AB_package);
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qvalue_array_sent_to_non_value_array_attribute = 
	    STATIC_SYMBOL("VALUE-ARRAY-SENT-TO-NON-VALUE-ARRAY-ATTRIBUTE",
	    AB_package);
    Qvalue_array_sent_to_value_array_class_of_wrong_element_type = 
	    STATIC_SYMBOL("VALUE-ARRAY-SENT-TO-VALUE-ARRAY-CLASS-OF-WRONG-ELEMENT-TYPE",
	    AB_package);
    Qvalue_array_sent_to_non_value_array_class_definition = 
	    STATIC_SYMBOL("VALUE-ARRAY-SENT-TO-NON-VALUE-ARRAY-CLASS-DEFINITION",
	    AB_package);
    Qitem_list_sent_to_non_item_list_attribute = 
	    STATIC_SYMBOL("ITEM-LIST-SENT-TO-NON-ITEM-LIST-ATTRIBUTE",
	    AB_package);
    Qitem_list_sent_to_non_item_list_class_definition = 
	    STATIC_SYMBOL("ITEM-LIST-SENT-TO-NON-ITEM-LIST-CLASS-DEFINITION",
	    AB_package);
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    Qvalue_list_sent_to_non_value_list_attribute = 
	    STATIC_SYMBOL("VALUE-LIST-SENT-TO-NON-VALUE-LIST-ATTRIBUTE",
	    AB_package);
    Qvalue_list_sent_to_value_list_class_of_wrong_element_type = 
	    STATIC_SYMBOL("VALUE-LIST-SENT-TO-VALUE-LIST-CLASS-OF-WRONG-ELEMENT-TYPE",
	    AB_package);
    Qvalue_list_sent_to_non_value_list_class_definition = 
	    STATIC_SYMBOL("VALUE-LIST-SENT-TO-NON-VALUE-LIST-CLASS-DEFINITION",
	    AB_package);
    Qindex_out_of_bounds_for_g2_value_array = 
	    STATIC_SYMBOL("INDEX-OUT-OF-BOUNDS-FOR-G2-VALUE-ARRAY",AB_package);
    Qunexpected_non_value_array = 
	    STATIC_SYMBOL("UNEXPECTED-NON-VALUE-ARRAY",AB_package);
    Qpremature_access_to_toplevel_g2_value_array = 
	    STATIC_SYMBOL("PREMATURE-ACCESS-TO-TOPLEVEL-G2-VALUE-ARRAY",
	    AB_package);
    Qg2_value_array_deleted_during_object_passing = 
	    STATIC_SYMBOL("G2-VALUE-ARRAY-DELETED-DURING-OBJECT-PASSING",
	    AB_package);
    Qvalue_array_contains_an_element_inappropriate_for_receiving_array = 
	    STATIC_SYMBOL("VALUE-ARRAY-CONTAINS-AN-ELEMENT-INAPPROPRIATE-FOR-RECEIVING-ARRAY",
	    AB_package);
}
