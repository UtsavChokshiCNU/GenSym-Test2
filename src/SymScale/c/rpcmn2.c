/* rpcmn2.c
 * Input file:  rpc-common2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rpcmn2.h"


/* RECLAIM-RESUMABLE-ATTRIBUTE-SPEC-FUNCTION */
Object reclaim_resumable_attribute_spec_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(158,0);
    temp = CONSP(x) ? reclaim_gensym_list_1(x) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-RESUMABLE-ATTRIBUTE-SPEC-IF-ANY-FUNCTION */
Object reclaim_resumable_attribute_spec_if_any_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(158,1);
    temp = CONSP(x) ? reclaim_gensym_list_1(x) : Nil;
    return VALUES_1(temp);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

/* SET-RESUMABLE-ATTRIBUTE-TYPE */
Object set_resumable_attribute_type(resumable_attribute_spec,value)
    Object resumable_attribute_spec, value;
{
    x_note_fn_call(158,2);
    if (CONSP(resumable_attribute_spec) &&  
	    !EQ(M_CAR(resumable_attribute_spec),Qclass_qualified_name))
	return VALUES_1(M_CAR(resumable_attribute_spec) = value);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_resumable_object_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_object_mixins, Qchain_of_available_resumable_object_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_object_mixin_count, Qresumable_object_mixin_count);

Object Chain_of_available_resumable_object_mixins_vector = UNBOUND;

/* RESUMABLE-OBJECT-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_object_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,3);
    temp = Resumable_object_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-OBJECT-MIXIN-COUNT */
Object outstanding_resumable_object_mixin_count()
{
    Object def_structure_resumable_object_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,4);
    gensymed_symbol = IFIX(Resumable_object_mixin_count);
    def_structure_resumable_object_mixin_variable = 
	    Chain_of_available_resumable_object_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_object_mixin_variable))
	goto end_loop;
    def_structure_resumable_object_mixin_variable = 
	    ISVREF(def_structure_resumable_object_mixin_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-OBJECT-MIXIN-1 */
Object reclaim_resumable_object_mixin_1(resumable_object_mixin)
    Object resumable_object_mixin;
{
    Object temp, svref_arg_2;

    x_note_fn_call(158,5);
    inline_note_reclaim_cons(resumable_object_mixin,Nil);
    temp = ISVREF(Chain_of_available_resumable_object_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_object_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_object_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_object_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-OBJECT-MIXIN */
Object reclaim_structure_for_resumable_object_mixin(resumable_object_mixin)
    Object resumable_object_mixin;
{
    x_note_fn_call(158,6);
    return reclaim_resumable_object_mixin_1(resumable_object_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-object-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-OBJECT-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_object_mixin_structure_internal()
{
    Object def_structure_resumable_object_mixin_variable;
    Object defstruct_g2_resumable_object_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,7);
    def_structure_resumable_object_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_object_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_object_mixin_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_resumable_object_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct;
	def_structure_resumable_object_mixin_variable = 
		defstruct_g2_resumable_object_mixin_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_object_mixin_variable);
}

/* MAKE-RESUMABLE-OBJECT-MIXIN-1 */
Object make_resumable_object_mixin_1()
{
    Object def_structure_resumable_object_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,8);
    def_structure_resumable_object_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_object_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_object_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_object_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_object_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct;
    }
    else
	def_structure_resumable_object_mixin_variable = 
		make_permanent_resumable_object_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_object_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_object_mixin_variable,FIX((SI_Long)1L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_mixin_variable,FIX((SI_Long)3L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_mixin_variable,FIX((SI_Long)4L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_mixin_variable,FIX((SI_Long)5L)) 
	    = Nil;
    SVREF(def_structure_resumable_object_mixin_variable,FIX((SI_Long)6L)) 
	    = Nil;
    return VALUES_1(def_structure_resumable_object_mixin_variable);
}

Object The_type_description_of_resumable_icp_object_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_icp_object_mixins, Qchain_of_available_resumable_icp_object_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_icp_object_mixin_count, Qresumable_icp_object_mixin_count);

Object Chain_of_available_resumable_icp_object_mixins_vector = UNBOUND;

/* RESUMABLE-ICP-OBJECT-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_icp_object_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,9);
    temp = Resumable_icp_object_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-ICP-OBJECT-MIXIN-COUNT */
Object outstanding_resumable_icp_object_mixin_count()
{
    Object def_structure_resumable_icp_object_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,10);
    gensymed_symbol = IFIX(Resumable_icp_object_mixin_count);
    def_structure_resumable_icp_object_mixin_variable = 
	    Chain_of_available_resumable_icp_object_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_icp_object_mixin_variable))
	goto end_loop;
    def_structure_resumable_icp_object_mixin_variable = 
	    ISVREF(def_structure_resumable_icp_object_mixin_variable,
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

/* RECLAIM-RESUMABLE-ICP-OBJECT-MIXIN-1 */
Object reclaim_resumable_icp_object_mixin_1(resumable_icp_object_mixin)
    Object resumable_icp_object_mixin;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,11);
    inline_note_reclaim_cons(resumable_icp_object_mixin,Nil);
    structure_being_reclaimed = resumable_icp_object_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_list_1(ISVREF(resumable_icp_object_mixin,(SI_Long)7L));
      SVREF(resumable_icp_object_mixin,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_icp_object_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_icp_object_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_icp_object_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_icp_object_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-ICP-OBJECT-MIXIN */
Object reclaim_structure_for_resumable_icp_object_mixin(resumable_icp_object_mixin)
    Object resumable_icp_object_mixin;
{
    x_note_fn_call(158,12);
    return reclaim_resumable_icp_object_mixin_1(resumable_icp_object_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-icp-object-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-ICP-OBJECT-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_icp_object_mixin_structure_internal()
{
    Object def_structure_resumable_icp_object_mixin_variable;
    Object defstruct_g2_resumable_icp_object_mixin_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,13);
    def_structure_resumable_icp_object_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_icp_object_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_resumable_icp_object_mixin_variable = Nil;
	gensymed_symbol_1 = (SI_Long)8L;
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
	defstruct_g2_resumable_icp_object_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_object_mixin_variable,
		FIX((SI_Long)6L)) = Nil;
	def_structure_resumable_icp_object_mixin_variable = 
		defstruct_g2_resumable_icp_object_mixin_variable;
	SVREF(def_structure_resumable_icp_object_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_resumable_icp_object_mixins_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_resumable_icp_object_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_resumable_icp_object_mixins_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_resumable_icp_object_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_icp_object_mixin_variable);
}

/* MAKE-RESUMABLE-ICP-OBJECT-MIXIN-1 */
Object make_resumable_icp_object_mixin_1()
{
    Object def_structure_resumable_icp_object_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,14);
    def_structure_resumable_icp_object_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_icp_object_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_icp_object_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_icp_object_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_icp_object_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_icp_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct;
    }
    else
	def_structure_resumable_icp_object_mixin_variable = 
		make_permanent_resumable_icp_object_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_icp_object_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_resumable_icp_object_mixin_variable,
	    FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_resumable_icp_object_mixin_variable);
}

Object The_type_description_of_resumable_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_node_mixins, Qchain_of_available_resumable_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_node_mixin_count, Qresumable_node_mixin_count);

Object Chain_of_available_resumable_node_mixins_vector = UNBOUND;

/* RESUMABLE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,15);
    temp = Resumable_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-NODE-MIXIN-COUNT */
Object outstanding_resumable_node_mixin_count()
{
    Object def_structure_resumable_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,16);
    gensymed_symbol = IFIX(Resumable_node_mixin_count);
    def_structure_resumable_node_mixin_variable = 
	    Chain_of_available_resumable_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_node_mixin_variable = 
	    ISVREF(def_structure_resumable_node_mixin_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RESUMABLE-NODE-MIXIN-1 */
Object reclaim_resumable_node_mixin_1(resumable_node_mixin)
    Object resumable_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,17);
    inline_note_reclaim_cons(resumable_node_mixin,Nil);
    structure_being_reclaimed = resumable_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_node_mixin,(SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_node_mixin,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-NODE-MIXIN */
Object reclaim_structure_for_resumable_node_mixin(resumable_node_mixin)
    Object resumable_node_mixin;
{
    x_note_fn_call(158,18);
    return reclaim_resumable_node_mixin_1(resumable_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_node_mixin_structure_internal()
{
    Object def_structure_resumable_node_mixin_variable;
    Object defstruct_g2_resumable_node_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,19);
    def_structure_resumable_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_node_mixin_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_resumable_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_node_mixin_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct;
	def_structure_resumable_node_mixin_variable = 
		defstruct_g2_resumable_node_mixin_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_node_mixin_variable);
}

/* MAKE-RESUMABLE-NODE-MIXIN-1 */
Object make_resumable_node_mixin_1()
{
    Object def_structure_resumable_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,20);
    def_structure_resumable_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_node_mixin_variable = 
		make_permanent_resumable_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_node_mixin_variable,Nil);
    SVREF(def_structure_resumable_node_mixin_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_node_mixin_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_resumable_node_mixin_variable);
}

Object The_type_description_of_resumable_icp_node_mixin = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_resumable_icp_node_mixins, Qchain_of_available_resumable_icp_node_mixins);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_icp_node_mixin_count, Qresumable_icp_node_mixin_count);

Object Chain_of_available_resumable_icp_node_mixins_vector = UNBOUND;

/* RESUMABLE-ICP-NODE-MIXIN-STRUCTURE-MEMORY-USAGE */
Object resumable_icp_node_mixin_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,21);
    temp = Resumable_icp_node_mixin_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RESUMABLE-ICP-NODE-MIXIN-COUNT */
Object outstanding_resumable_icp_node_mixin_count()
{
    Object def_structure_resumable_icp_node_mixin_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,22);
    gensymed_symbol = IFIX(Resumable_icp_node_mixin_count);
    def_structure_resumable_icp_node_mixin_variable = 
	    Chain_of_available_resumable_icp_node_mixins;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_resumable_icp_node_mixin_variable))
	goto end_loop;
    def_structure_resumable_icp_node_mixin_variable = 
	    ISVREF(def_structure_resumable_icp_node_mixin_variable,
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

/* RECLAIM-RESUMABLE-ICP-NODE-MIXIN-1 */
Object reclaim_resumable_icp_node_mixin_1(resumable_icp_node_mixin)
    Object resumable_icp_node_mixin;
{
    Object structure_being_reclaimed, resumable_attribute_spec_qm, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,23);
    inline_note_reclaim_cons(resumable_icp_node_mixin,Nil);
    structure_being_reclaimed = resumable_icp_node_mixin;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      resumable_attribute_spec_qm = ISVREF(resumable_icp_node_mixin,
	      (SI_Long)2L);
      if (CONSP(resumable_attribute_spec_qm))
	  reclaim_gensym_list_1(resumable_attribute_spec_qm);
      SVREF(resumable_icp_node_mixin,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(resumable_icp_node_mixin,(SI_Long)3L));
      SVREF(resumable_icp_node_mixin,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_resumable_icp_node_mixins_vector,
	    IFIX(Current_thread_index));
    SVREF(resumable_icp_node_mixin,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_resumable_icp_node_mixins_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = resumable_icp_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-ICP-NODE-MIXIN */
Object reclaim_structure_for_resumable_icp_node_mixin(resumable_icp_node_mixin)
    Object resumable_icp_node_mixin;
{
    x_note_fn_call(158,24);
    return reclaim_resumable_icp_node_mixin_1(resumable_icp_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-icp-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-ICP-NODE-MIXIN-STRUCTURE-INTERNAL */
Object make_permanent_resumable_icp_node_mixin_structure_internal()
{
    Object def_structure_resumable_icp_node_mixin_variable;
    Object defstruct_g2_resumable_icp_node_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,25);
    def_structure_resumable_icp_node_mixin_variable = Nil;
    atomic_incff_symval(Qresumable_icp_node_mixin_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_resumable_icp_node_mixin_variable = Nil;
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
	defstruct_g2_resumable_icp_node_mixin_variable = the_array;
	SVREF(defstruct_g2_resumable_icp_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct;
	SVREF(defstruct_g2_resumable_icp_node_mixin_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_resumable_icp_node_mixin_variable,
		FIX((SI_Long)2L)) = Nil;
	def_structure_resumable_icp_node_mixin_variable = 
		defstruct_g2_resumable_icp_node_mixin_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_icp_node_mixin_variable);
}

/* MAKE-RESUMABLE-ICP-NODE-MIXIN-1 */
Object make_resumable_icp_node_mixin_1()
{
    Object def_structure_resumable_icp_node_mixin_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,26);
    def_structure_resumable_icp_node_mixin_variable = 
	    ISVREF(Chain_of_available_resumable_icp_node_mixins_vector,
	    IFIX(Current_thread_index));
    if (def_structure_resumable_icp_node_mixin_variable) {
	svref_arg_1 = Chain_of_available_resumable_icp_node_mixins_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_resumable_icp_node_mixin_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_resumable_icp_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_icp_node_mixin_variable = 
		make_permanent_resumable_icp_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_icp_node_mixin_variable,
	    Nil);
    SVREF(def_structure_resumable_icp_node_mixin_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_icp_node_mixin_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_resumable_icp_node_mixin_variable,
	    FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_resumable_icp_node_mixin_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_receiving_resumable_object, Qcurrent_receiving_resumable_object);

Object The_type_description_of_receiving_resumable_object = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_receiving_resumable_objects, Qchain_of_available_receiving_resumable_objects);

DEFINE_VARIABLE_WITH_SYMBOL(Receiving_resumable_object_count, Qreceiving_resumable_object_count);

Object Chain_of_available_receiving_resumable_objects_vector = UNBOUND;

/* RECEIVING-RESUMABLE-OBJECT-STRUCTURE-MEMORY-USAGE */
Object receiving_resumable_object_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,27);
    temp = Receiving_resumable_object_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RECEIVING-RESUMABLE-OBJECT-COUNT */
Object outstanding_receiving_resumable_object_count()
{
    Object def_structure_receiving_resumable_object_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,28);
    gensymed_symbol = IFIX(Receiving_resumable_object_count);
    def_structure_receiving_resumable_object_variable = 
	    Chain_of_available_receiving_resumable_objects;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_receiving_resumable_object_variable))
	goto end_loop;
    def_structure_receiving_resumable_object_variable = 
	    ISVREF(def_structure_receiving_resumable_object_variable,
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

/* RECLAIM-RECEIVING-RESUMABLE-OBJECT-INTERNAL-1 */
Object reclaim_receiving_resumable_object_internal_1(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,29);
    inline_note_reclaim_cons(receiving_resumable_object,Nil);
    structure_being_reclaimed = receiving_resumable_object;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_object_building_problem_if_any(ISVREF(receiving_resumable_object,
	      (SI_Long)10L));
      SVREF(receiving_resumable_object,FIX((SI_Long)10L)) = Nil;
      reclaim_icp_list_of_rpc_arglist_structures(ISVREF(receiving_resumable_object,
	      (SI_Long)13L));
      SVREF(receiving_resumable_object,FIX((SI_Long)13L)) = Nil;
      reclaim_evaluation_value_if_any_function(ISVREF(receiving_resumable_object,
	      (SI_Long)14L));
      SVREF(receiving_resumable_object,FIX((SI_Long)14L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_receiving_resumable_objects_vector,
	    IFIX(Current_thread_index));
    SVREF(receiving_resumable_object,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_receiving_resumable_objects_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = receiving_resumable_object;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RECEIVING-RESUMABLE-OBJECT */
Object reclaim_structure_for_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    x_note_fn_call(158,30);
    return reclaim_receiving_resumable_object_internal_1(receiving_resumable_object);
}

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

/* MAKE-PERMANENT-RECEIVING-RESUMABLE-OBJECT-STRUCTURE-INTERNAL */
Object make_permanent_receiving_resumable_object_structure_internal()
{
    Object def_structure_receiving_resumable_object_variable;
    Object defstruct_g2_receiving_resumable_object_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,31);
    def_structure_receiving_resumable_object_variable = Nil;
    atomic_incff_symval(Qreceiving_resumable_object_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_receiving_resumable_object_variable = Nil;
	gensymed_symbol_1 = (SI_Long)15L;
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
	defstruct_g2_receiving_resumable_object_variable = the_array;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_receiving_resumable_object_variable,
		FIX((SI_Long)6L)) = Nil;
	def_structure_receiving_resumable_object_variable = 
		defstruct_g2_receiving_resumable_object_variable;
	SVREF(def_structure_receiving_resumable_object_variable,
		FIX((SI_Long)2L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = 
		ISVREF(Chain_of_available_receiving_resumable_objects_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_receiving_resumable_object_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_receiving_resumable_objects_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_receiving_resumable_object_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_receiving_resumable_object_variable);
}

/* MAKE-RECEIVING-RESUMABLE-OBJECT-1 */
Object make_receiving_resumable_object_1()
{
    Object def_structure_receiving_resumable_object_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,32);
    def_structure_receiving_resumable_object_variable = 
	    ISVREF(Chain_of_available_receiving_resumable_objects_vector,
	    IFIX(Current_thread_index));
    if (def_structure_receiving_resumable_object_variable) {
	svref_arg_1 = Chain_of_available_receiving_resumable_objects_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_receiving_resumable_object_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_receiving_resumable_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;
    }
    else
	def_structure_receiving_resumable_object_variable = 
		make_permanent_receiving_resumable_object_structure_internal();
    inline_note_allocate_cons(def_structure_receiving_resumable_object_variable,
	    Nil);
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_receiving_resumable_object_variable,
	    FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_receiving_resumable_object_variable);
}

/* RECLAIM-TEXT-OR-GENSYM-STRING-IF-ANY */
Object reclaim_text_or_gensym_string_if_any(text_string_qm)
    Object text_string_qm;
{
    x_note_fn_call(158,33);
    if (text_string_qm)
	return reclaim_text_or_gensym_string(text_string_qm);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_object_building_problem = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_object_building_problems, Qchain_of_available_object_building_problems);

DEFINE_VARIABLE_WITH_SYMBOL(Object_building_problem_count, Qobject_building_problem_count);

Object Chain_of_available_object_building_problems_vector = UNBOUND;

/* OBJECT-BUILDING-PROBLEM-STRUCTURE-MEMORY-USAGE */
Object object_building_problem_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,34);
    temp = Object_building_problem_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-OBJECT-BUILDING-PROBLEM-COUNT */
Object outstanding_object_building_problem_count()
{
    Object def_structure_object_building_problem_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,35);
    gensymed_symbol = IFIX(Object_building_problem_count);
    def_structure_object_building_problem_variable = 
	    Chain_of_available_object_building_problems;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_object_building_problem_variable))
	goto end_loop;
    def_structure_object_building_problem_variable = 
	    ISVREF(def_structure_object_building_problem_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-OBJECT-BUILDING-PROBLEM-1 */
Object reclaim_object_building_problem_1(object_building_problem)
    Object object_building_problem;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,36);
    inline_note_reclaim_cons(object_building_problem,Nil);
    structure_being_reclaimed = object_building_problem;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_text_or_gensym_string_if_any(ISVREF(object_building_problem,
	      (SI_Long)2L));
      SVREF(object_building_problem,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_object_building_problems_vector,
	    IFIX(Current_thread_index));
    SVREF(object_building_problem,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_object_building_problems_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = object_building_problem;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-OBJECT-BUILDING-PROBLEM */
Object reclaim_structure_for_object_building_problem(object_building_problem)
    Object object_building_problem;
{
    x_note_fn_call(158,37);
    return reclaim_object_building_problem_1(object_building_problem);
}

static Object Qg2_defstruct_structure_name_object_building_problem_g2_struct;  /* g2-defstruct-structure-name::object-building-problem-g2-struct */

/* MAKE-PERMANENT-OBJECT-BUILDING-PROBLEM-STRUCTURE-INTERNAL */
Object make_permanent_object_building_problem_structure_internal()
{
    Object def_structure_object_building_problem_variable;
    Object defstruct_g2_object_building_problem_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,38);
    def_structure_object_building_problem_variable = Nil;
    atomic_incff_symval(Qobject_building_problem_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_object_building_problem_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_object_building_problem_variable = the_array;
	SVREF(defstruct_g2_object_building_problem_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_object_building_problem_g2_struct;
	def_structure_object_building_problem_variable = 
		defstruct_g2_object_building_problem_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_object_building_problem_variable);
}

/* MAKE-OBJECT-BUILDING-PROBLEM-1 */
Object make_object_building_problem_1(object_building_problem_name,
	    object_building_problem_attribute_qm,
	    object_building_problem_class_name_qm,
	    object_building_problem_extra_info_format_string_qm,
	    object_building_problem_extra_info_reclaimer_qm,
	    object_building_problem_extra_info)
    Object object_building_problem_name, object_building_problem_attribute_qm;
    Object object_building_problem_class_name_qm;
    Object object_building_problem_extra_info_format_string_qm;
    Object object_building_problem_extra_info_reclaimer_qm;
    Object object_building_problem_extra_info;
{
    Object def_structure_object_building_problem_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,39);
    def_structure_object_building_problem_variable = 
	    ISVREF(Chain_of_available_object_building_problems_vector,
	    IFIX(Current_thread_index));
    if (def_structure_object_building_problem_variable) {
	svref_arg_1 = Chain_of_available_object_building_problems_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_object_building_problem_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_object_building_problem_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_object_building_problem_g2_struct;
    }
    else
	def_structure_object_building_problem_variable = 
		make_permanent_object_building_problem_structure_internal();
    inline_note_allocate_cons(def_structure_object_building_problem_variable,
	    Nil);
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)1L)) 
	    = object_building_problem_name;
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)2L)) 
	    = object_building_problem_attribute_qm;
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)3L)) 
	    = object_building_problem_class_name_qm;
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)4L)) 
	    = object_building_problem_extra_info_format_string_qm;
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)6L)) 
	    = object_building_problem_extra_info_reclaimer_qm;
    SVREF(def_structure_object_building_problem_variable,FIX((SI_Long)5L)) 
	    = object_building_problem_extra_info;
    return VALUES_1(def_structure_object_building_problem_variable);
}

static Object string_constant;     /* "~(~A::~A~)" */

static Object string_constant_1;   /* "~(~A~)" */

static Object string_constant_2;   /* "top-level" */

/* RECORD-OBJECT-BUILDING-PROBLEM-ON-RECEIVING-SIDE-1 */
Object record_object_building_problem_on_receiving_side_1(problem_name,
	    attribute_qualifier_qm,attribute_name_or_index_qm,class_name,
	    info_format,info_args_qm,info_reclaimer_qm)
    Object problem_name, attribute_qualifier_qm, attribute_name_or_index_qm;
    Object class_name, info_format, info_args_qm, info_reclaimer_qm;
{
    Object old_problem_qm, info_arg, ab_loop_list_, svref_arg_1;
    Object attribute_text, svref_new_value;

    x_note_fn_call(158,40);
    old_problem_qm = ISVREF(Current_receiving_resumable_object,(SI_Long)10L);
    if (old_problem_qm) {
	if (info_args_qm) {
	    info_arg = Nil;
	    ab_loop_list_ = info_args_qm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    info_arg = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    FUNCALL_1(info_reclaimer_qm,info_arg);
	    goto next_loop;
	  end_loop:;
	}
    }
    else {
	svref_arg_1 = Current_receiving_resumable_object;
	if (attribute_qualifier_qm && attribute_name_or_index_qm)
	    attribute_text = tformat_text_string(3,string_constant,
		    attribute_qualifier_qm,attribute_name_or_index_qm);
	else if (attribute_name_or_index_qm)
	    attribute_text = tformat_text_string(2,string_constant_1,
		    attribute_name_or_index_qm);
	else
	    attribute_text = tformat_text_string(1,string_constant_2);
	svref_new_value = make_object_building_problem_1(problem_name,
		attribute_text,class_name,info_format,info_reclaimer_qm,
		info_args_qm);
	SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-OBJECT-BUILDING-PROBLEM-IF-ANY */
Object reclaim_object_building_problem_if_any(object_building_problem_qm)
    Object object_building_problem_qm;
{
    Object info_reclaimer_qm, extra_info_item, ab_loop_list_;

    x_note_fn_call(158,41);
    if (object_building_problem_qm) {
	info_reclaimer_qm = ISVREF(object_building_problem_qm,(SI_Long)6L);
	if (info_reclaimer_qm) {
	    extra_info_item = Nil;
	    ab_loop_list_ = ISVREF(object_building_problem_qm,(SI_Long)5L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    extra_info_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    FUNCALL_1(info_reclaimer_qm,extra_info_item);
	    goto next_loop;
	  end_loop:;
	}
	reclaim_object_building_problem_1(object_building_problem_qm);
    }
    return VALUES_1(Nil);
}

static Object Qoutput;             /* output */

static Object Qinput;              /* input */

/* RECLAIM-RESUMABLE-OBJECT */
Object reclaim_resumable_object(resumable_object,icp_port)
    Object resumable_object, icp_port;
{
    Object temp;

    x_note_fn_call(158,42);
    temp = ISVREF(icp_port,(SI_Long)3L);
    if (EQ(temp,Qoutput))
	return g2_reclaim_sending_resumable_object(1,resumable_object);
    else if (EQ(temp,Qinput))
	return reclaim_single_receiving_resumable_object(resumable_object);
    else
	return VALUES_1(Qnil);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-OBJECT */
Object establish_new_object_index_for_resumable_object varargs_1(int, n)
{
    Object resumable_object, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(158,43);
    INIT_ARGS_nonrelocating();
    resumable_object = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = assign_corresponding_icp_object_index(resumable_object,
	    Qstandard_icp_object_index_space,send_enlarge_message_p);
    MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_object,(SI_Long)7L)));
    SVREF(resumable_object,FIX((SI_Long)7L)) = svref_new_value;
    if (send_enlarge_message_p)
	return VALUES_1(corresponding_icp_object_index);
    else
	return VALUES_2(corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
}

/* MAKE-CORRESPONDING-ICP-RESUMABLE-OBJECT */
Object make_corresponding_icp_resumable_object(resumable_object)
    Object resumable_object;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,44);
    write_icp_maybe_suspend();
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      result = assign_corresponding_icp_object_index(resumable_object,
	      Qstandard_icp_object_index_space,T);
      MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
      svref_new_value = gensym_cons_1(Current_icp_port,
	      gensym_cons_1(corresponding_icp_object_index,
	      ISVREF(resumable_object,(SI_Long)7L)));
      SVREF(resumable_object,FIX((SI_Long)7L)) = svref_new_value;
      if (T);
      else {
	  temp = corresponding_icp_object_index;
	  corresponding_icp_object_index = temp;
      }
      result = VALUES_1(corresponding_icp_object_index);
    POP_SPECIAL();
    return result;
}

/* GET-ICP-OBJECT-INDEX-FOR-RESUMABLE-OBJECT */
Object get_icp_object_index_for_resumable_object(resumable_object,icp_port)
    Object resumable_object, icp_port;
{
    x_note_fn_call(158,45);
    return getfq_function_no_default(ISVREF(resumable_object,(SI_Long)7L),
	    icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-RESUMABLE-OBJECT */
Object set_icp_object_index_for_resumable_object(resumable_object,
	    corresponding_icp_object_index,icp_port)
    Object resumable_object, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(158,46);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_object,(SI_Long)7L)));
    return VALUES_1(SVREF(resumable_object,FIX((SI_Long)7L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-RESUMABLE-OBJECT */
Object reclaim_icp_object_map_for_resumable_object(resumable_object)
    Object resumable_object;
{
    Object icp_object_map;

    x_note_fn_call(158,47);
    icp_object_map = ISVREF(resumable_object,(SI_Long)7L);
    if (icp_object_map)
	return reclaim_icp_object_map(resumable_object,icp_object_map,
		Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_resumable_object;  /* set-access-form-for-resumable-object */

/* RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-OBJECT */
Object reclaim_icp_port_entry_for_resumable_object(resumable_object,icp_port)
    Object resumable_object, icp_port;
{
    x_note_fn_call(158,48);
    return reclaim_icp_port_entry(icp_port,resumable_object,
	    ISVREF(resumable_object,(SI_Long)7L),
	    Qset_access_form_for_resumable_object);
}

/* SET-ACCESS-FORM-FOR-RESUMABLE-OBJECT */
Object set_access_form_for_resumable_object(resumable_object,new_value)
    Object resumable_object, new_value;
{
    x_note_fn_call(158,49);
    return VALUES_1(SVREF(resumable_object,FIX((SI_Long)7L)) = new_value);
}

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object establish_new_object_index_for_resumable_instance_node varargs_1(int, n)
{
    Object resumable_instance_node, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(158,50);
    INIT_ARGS_nonrelocating();
    resumable_instance_node = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = assign_corresponding_icp_object_index(resumable_instance_node,
	    Qstandard_icp_object_index_space,send_enlarge_message_p);
    MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_instance_node,(SI_Long)3L)));
    SVREF(resumable_instance_node,FIX((SI_Long)3L)) = svref_new_value;
    if (send_enlarge_message_p)
	return VALUES_1(corresponding_icp_object_index);
    else
	return VALUES_2(corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
}

/* MAKE-CORRESPONDING-ICP-RESUMABLE-INSTANCE-NODE */
Object make_corresponding_icp_resumable_instance_node(resumable_instance_node)
    Object resumable_instance_node;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,51);
    write_icp_maybe_suspend();
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      result = assign_corresponding_icp_object_index(resumable_instance_node,
	      Qstandard_icp_object_index_space,T);
      MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
      svref_new_value = gensym_cons_1(Current_icp_port,
	      gensym_cons_1(corresponding_icp_object_index,
	      ISVREF(resumable_instance_node,(SI_Long)3L)));
      SVREF(resumable_instance_node,FIX((SI_Long)3L)) = svref_new_value;
      if (T);
      else {
	  temp = corresponding_icp_object_index;
	  corresponding_icp_object_index = temp;
      }
      result = VALUES_1(corresponding_icp_object_index);
    POP_SPECIAL();
    return result;
}

/* GET-ICP-OBJECT-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object get_icp_object_index_for_resumable_instance_node(resumable_instance_node,
	    icp_port)
    Object resumable_instance_node, icp_port;
{
    x_note_fn_call(158,52);
    return getfq_function_no_default(ISVREF(resumable_instance_node,
	    (SI_Long)3L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object set_icp_object_index_for_resumable_instance_node(resumable_instance_node,
	    corresponding_icp_object_index,icp_port)
    Object resumable_instance_node, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(158,53);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_instance_node,(SI_Long)3L)));
    return VALUES_1(SVREF(resumable_instance_node,FIX((SI_Long)3L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-RESUMABLE-INSTANCE-NODE */
Object reclaim_icp_object_map_for_resumable_instance_node(resumable_instance_node)
    Object resumable_instance_node;
{
    Object icp_object_map;

    x_note_fn_call(158,54);
    icp_object_map = ISVREF(resumable_instance_node,(SI_Long)3L);
    if (icp_object_map)
	return reclaim_icp_object_map(resumable_instance_node,
		icp_object_map,Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_resumable_instance_node;  /* set-access-form-for-resumable-instance-node */

/* RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-INSTANCE-NODE */
Object reclaim_icp_port_entry_for_resumable_instance_node(resumable_instance_node,
	    icp_port)
    Object resumable_instance_node, icp_port;
{
    x_note_fn_call(158,55);
    return reclaim_icp_port_entry(icp_port,resumable_instance_node,
	    ISVREF(resumable_instance_node,(SI_Long)3L),
	    Qset_access_form_for_resumable_instance_node);
}

/* SET-ACCESS-FORM-FOR-RESUMABLE-INSTANCE-NODE */
Object set_access_form_for_resumable_instance_node(resumable_instance_node,
	    new_value)
    Object resumable_instance_node, new_value;
{
    x_note_fn_call(158,56);
    return VALUES_1(SVREF(resumable_instance_node,FIX((SI_Long)3L)) = 
	    new_value);
}

Object The_type_description_of_receiving_rpc_arglist_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_receiving_rpc_arglist_structures, Qchain_of_available_receiving_rpc_arglist_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Receiving_rpc_arglist_structure_count, Qreceiving_rpc_arglist_structure_count);

Object Chain_of_available_receiving_rpc_arglist_structures_vector = UNBOUND;

/* RECEIVING-RPC-ARGLIST-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object receiving_rpc_arglist_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(158,57);
    temp = Receiving_rpc_arglist_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RECEIVING-RPC-ARGLIST-STRUCTURE-COUNT */
Object outstanding_receiving_rpc_arglist_structure_count()
{
    Object def_structure_receiving_rpc_arglist_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(158,58);
    gensymed_symbol = IFIX(Receiving_rpc_arglist_structure_count);
    def_structure_receiving_rpc_arglist_structure_variable = 
	    Chain_of_available_receiving_rpc_arglist_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_receiving_rpc_arglist_structure_variable))
	goto end_loop;
    def_structure_receiving_rpc_arglist_structure_variable = 
	    ISVREF(def_structure_receiving_rpc_arglist_structure_variable,
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

/* RECLAIM-RECEIVING-RPC-ARGLIST-STRUCTURE-1 */
Object reclaim_receiving_rpc_arglist_structure_1(receiving_rpc_arglist_structure)
    Object receiving_rpc_arglist_structure;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(158,59);
    inline_note_reclaim_cons(receiving_rpc_arglist_structure,Nil);
    structure_being_reclaimed = receiving_rpc_arglist_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_icp_list_with_some_resumable_objects(ISVREF(receiving_rpc_arglist_structure,
	      (SI_Long)1L));
      SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)1L)) = Nil;
      reclaim_icp_list_1(ISVREF(receiving_rpc_arglist_structure,(SI_Long)6L));
      SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)6L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_receiving_rpc_arglist_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_receiving_rpc_arglist_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = receiving_rpc_arglist_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RECEIVING-RPC-ARGLIST-STRUCTURE */
Object reclaim_structure_for_receiving_rpc_arglist_structure(receiving_rpc_arglist_structure)
    Object receiving_rpc_arglist_structure;
{
    x_note_fn_call(158,60);
    return reclaim_receiving_rpc_arglist_structure_1(receiving_rpc_arglist_structure);
}

static Object Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct;  /* g2-defstruct-structure-name::receiving-rpc-arglist-structure-g2-struct */

/* MAKE-PERMANENT-RECEIVING-RPC-ARGLIST-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_receiving_rpc_arglist_structure_structure_internal()
{
    Object def_structure_receiving_rpc_arglist_structure_variable;
    Object defstruct_g2_receiving_rpc_arglist_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(158,61);
    def_structure_receiving_rpc_arglist_structure_variable = Nil;
    atomic_incff_symval(Qreceiving_rpc_arglist_structure_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_receiving_rpc_arglist_structure_variable = Nil;
	gensymed_symbol = (SI_Long)9L;
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
	defstruct_g2_receiving_rpc_arglist_structure_variable = the_array;
	SVREF(defstruct_g2_receiving_rpc_arglist_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct;
	def_structure_receiving_rpc_arglist_structure_variable = 
		defstruct_g2_receiving_rpc_arglist_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_receiving_rpc_arglist_structure_variable);
}

/* MAKE-RECEIVING-RPC-ARGLIST-STRUCTURE-1 */
Object make_receiving_rpc_arglist_structure_1()
{
    Object def_structure_receiving_rpc_arglist_structure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(158,62);
    def_structure_receiving_rpc_arglist_structure_variable = 
	    ISVREF(Chain_of_available_receiving_rpc_arglist_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_receiving_rpc_arglist_structure_variable) {
	svref_arg_1 = 
		Chain_of_available_receiving_rpc_arglist_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_receiving_rpc_arglist_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_receiving_rpc_arglist_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct;
    }
    else
	def_structure_receiving_rpc_arglist_structure_variable = 
		make_permanent_receiving_rpc_arglist_structure_structure_internal();
    inline_note_allocate_cons(def_structure_receiving_rpc_arglist_structure_variable,
	    Nil);
    SVREF(def_structure_receiving_rpc_arglist_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_receiving_rpc_arglist_structure_variable,
	    FIX((SI_Long)2L)) = Qerror;
    SVREF(def_structure_receiving_rpc_arglist_structure_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_receiving_rpc_arglist_structure_variable,
	    FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_receiving_rpc_arglist_structure_variable);
}

/* RECLAIM-ICP-LIST-OF-RPC-ARGLIST-STRUCTURES */
Object reclaim_icp_list_of_rpc_arglist_structures(rpc_arglist_structures)
    Object rpc_arglist_structures;
{
    Object rpc_arglist_structure, ab_loop_list_;

    x_note_fn_call(158,63);
    rpc_arglist_structure = Nil;
    ab_loop_list_ = rpc_arglist_structures;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rpc_arglist_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_receiving_rpc_arglist_structure_1(rpc_arglist_structure);
    goto next_loop;
  end_loop:;
    return reclaim_icp_list_1(rpc_arglist_structures);
}

/* RECLAIM-ICP-LIST-WITH-SOME-RESUMABLE-OBJECTS */
Object reclaim_icp_list_with_some_resumable_objects(icp_list)
    Object icp_list;
{
    Object possible_resumable_object, ab_loop_list_;

    x_note_fn_call(158,64);
    possible_resumable_object = Nil;
    ab_loop_list_ = icp_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    possible_resumable_object = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(possible_resumable_object) && 
	    EQ(ISVREF(possible_resumable_object,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	SVREF(possible_resumable_object,FIX((SI_Long)9L)) = Nil;
	reclaim_single_receiving_resumable_object(possible_resumable_object);
    }
    goto next_loop;
  end_loop:;
    return reclaim_icp_list_1(icp_list);
}

/* RECLAIM-SINGLE-RECEIVING-RESUMABLE-OBJECT */
Object reclaim_single_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object rpc_identifier_qm, svref_new_value;

    x_note_fn_call(158,65);
    g2_reclaim_single_receiving_resumable_object(receiving_resumable_object);
    rpc_identifier_qm = ISVREF(receiving_resumable_object,(SI_Long)5L);
    if (rpc_identifier_qm) {
	svref_new_value = delete_icp_element_1(receiving_resumable_object,
		ISVREF(rpc_identifier_qm,(SI_Long)5L));
	SVREF(rpc_identifier_qm,FIX((SI_Long)5L)) = svref_new_value;
    }
    return reclaim_receiving_resumable_object_internal_1(receiving_resumable_object);
}

/* RECLAIM-RECEIVING-RESUMABLE-OBJECT */
Object reclaim_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object arglist_structure_qm, initial_resumable_var;
    Object receiving_resumable_object_1;

    x_note_fn_call(158,66);
    arglist_structure_qm = ISVREF(receiving_resumable_object,(SI_Long)9L);
    if (arglist_structure_qm)
	return reclaim_receiving_rpc_arglist_structure_1(arglist_structure_qm);
    else {
	initial_resumable_var = ISVREF(receiving_resumable_object,(SI_Long)3L);
	receiving_resumable_object_1 = initial_resumable_var;
      next_loop:
	if ( !TRUEP(receiving_resumable_object_1))
	    goto end_loop;
	reclaim_single_receiving_resumable_object(receiving_resumable_object_1);
	receiving_resumable_object_1 = ISVREF(receiving_resumable_object_1,
		(SI_Long)3L);
	goto next_loop;
      end_loop:;
	initial_resumable_var = ISVREF(receiving_resumable_object,(SI_Long)4L);
	receiving_resumable_object_1 = initial_resumable_var;
      next_loop_1:
	if ( !TRUEP(receiving_resumable_object_1))
	    goto end_loop_1;
	reclaim_single_receiving_resumable_object(receiving_resumable_object_1);
	receiving_resumable_object_1 = ISVREF(receiving_resumable_object_1,
		(SI_Long)4L);
	goto next_loop_1;
      end_loop_1:;
	return reclaim_single_receiving_resumable_object(receiving_resumable_object);
    }
}

static Object Qgsi_reference_flag;  /* gsi-reference-flag */

static Object list_constant;       /* # */

/* GSI-ITEM-IS-VALUE-P */
Object gsi_item_is_value_p(gsi_item)
    Object gsi_item;
{
    Object gsi_instance_extension;
    char temp;

    x_note_fn_call(158,67);
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    temp = gsi_instance_extension ? TRUEP(ISVREF(gsi_instance_extension,
	    (SI_Long)2L)) : TRUEP(Nil);
    if (temp);
    else
	temp = TRUEP(get_gsi_instance_plist_value(gsi_item,
		Qgsi_reference_flag));
    if (temp);
    else
	temp = ISVREF(gsi_item,(SI_Long)2L) ? 
		TRUEP(memq_function(FIX(IFIX(ISVREF(gsi_item,(SI_Long)1L)) 
		>>  -  - (SI_Long)3L),list_constant)) : TRUEP(Qnil);
    return VALUES_1( !temp ? T : Nil);
}

static Object Qinteger_array;      /* integer-array */

static Object Qsymbol_array;       /* symbol-array */

static Object Qtext_array;         /* text-array */

static Object Qtruth_value_array;  /* truth-value-array */

static Object Qfloat_array;        /* float-array */

static Object Qg2_array;           /* g2-array */

static Object Qquantity_array;     /* quantity-array */

static Object Qitem_array;         /* item-array */

static Object Qvalue_array;        /* value-array */

static Object Qinteger_list;       /* integer-list */

static Object Qsymbol_list;        /* symbol-list */

static Object Qtext_list;          /* text-list */

static Object Qtruth_value_list;   /* truth-value-list */

static Object Qfloat_list;         /* float-list */

static Object Qg2_list;            /* g2-list */

static Object Qquantity_list;      /* quantity-list */

static Object Qitem_list;          /* item-list */

static Object Qvalue_list;         /* value-list */

/* CLASS-FOR-GSI-ITEM */
Object class_for_gsi_item(gsi_item)
    Object gsi_item;
{
    Object gsi_instance_extension, temp, class_1;
    SI_Long temp_1;

    x_note_fn_call(158,68);
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    temp = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)2L) : Nil;
    if (temp);
    else if (ISVREF(gsi_item,(SI_Long)2L)) {
	temp_1 = IFIX(ISVREF(gsi_item,(SI_Long)1L)) >>  -  - (SI_Long)3L;
	if ( !((SI_Long)-128L <= temp_1 && temp_1 <= (SI_Long)127L))
	    class_1 = Nil;
	else
	    switch ((char)temp_1) {
	      case 17:
		class_1 = Qinteger_array;
		break;
	      case 19:
		class_1 = Qsymbol_array;
		break;
	      case 20:
		class_1 = Qtext_array;
		break;
	      case 21:
		class_1 = Qtruth_value_array;
		break;
	      case 22:
		class_1 = Qfloat_array;
		break;
	      case 25:
		class_1 = Qg2_array;
		break;
	      case 26:
		class_1 = Qquantity_array;
		break;
	      case 23:
		class_1 = Qitem_array;
		break;
	      case 24:
		class_1 = Qvalue_array;
		break;
	      case 33:
		class_1 = Qinteger_list;
		break;
	      case 35:
		class_1 = Qsymbol_list;
		break;
	      case 36:
		class_1 = Qtext_list;
		break;
	      case 37:
		class_1 = Qtruth_value_list;
		break;
	      case 38:
		class_1 = Qfloat_list;
		break;
	      case 41:
		class_1 = Qg2_list;
		break;
	      case 42:
		class_1 = Qquantity_list;
		break;
	      case 39:
		class_1 = Qitem_list;
		break;
	      case 40:
		class_1 = Qvalue_list;
		break;
	      default:
		class_1 = Nil;
		break;
	    }
	if (class_1) {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = make_gsi_instance_extension_1();
		SVREF(gsi_item,FIX((SI_Long)3L)) = gsi_instance_extension;
	    }
	    temp = SVREF(gsi_instance_extension,FIX((SI_Long)2L)) = class_1;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qrpc_value_or_object;  /* rpc-value-or-object */

static Object string_constant_3;   /* "[value]" */

static Object Qvalue;              /* value */

/* WRITE-ICP-RPC-VALUE-OR-OBJECT */
Object write_icp_rpc_value_or_object(rpc_value_or_object)
    Object rpc_value_or_object;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,69);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qrpc_value_or_object,
		    string_constant_3,Qvalue,T,rpc_value_or_object,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  result_of_write = 
		  g2_write_icp_rpc_value_or_object(rpc_value_or_object);
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qrpc_value_or_object,string_constant_3,Qvalue,Nil,
		      Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else
	return g2_write_icp_rpc_value_or_object(rpc_value_or_object);
}

/* READ-ICP-RPC-VALUE-OR-OBJECT */
Object read_icp_rpc_value_or_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, type_tag;
    Object remote_object_index, receiving_resumable_object, result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,70);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qrpc_value_or_object,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  type_tag = peek_icp_byte();
	  if (FIXNUM_EQ(type_tag,Rpc_object_type_tag)) {
	      read_icp_byte();
	      remote_object_index = read_icp_unsigned_integer();
	      receiving_resumable_object = make_receiving_resumable_object_1();
	      store_corresponding_icp_object(remote_object_index,
		      receiving_resumable_object);
	      SVREF(receiving_resumable_object,FIX((SI_Long)11L)) = 
		      remote_object_index;
	      result_of_read = receiving_resumable_object;
	  }
	  else if (FIXNUM_EQ(type_tag,Rpc_object_handle_type_tag)) {
	      read_icp_byte();
	      result_of_read = read_icp_fixnum();
	  }
	  else
	      result_of_read = read_icp_remote_value();
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qrpc_value_or_object,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	type_tag = peek_icp_byte();
	if (FIXNUM_EQ(type_tag,Rpc_object_type_tag)) {
	    read_icp_byte();
	    remote_object_index = read_icp_unsigned_integer();
	    receiving_resumable_object = make_receiving_resumable_object_1();
	    store_corresponding_icp_object(remote_object_index,
		    receiving_resumable_object);
	    SVREF(receiving_resumable_object,FIX((SI_Long)11L)) = 
		    remote_object_index;
	    return VALUES_1(receiving_resumable_object);
	}
	else if (FIXNUM_EQ(type_tag,Rpc_object_handle_type_tag)) {
	    read_icp_byte();
	    return read_icp_fixnum();
	}
	else
	    return read_icp_remote_value();
    }
}

static Object Qrpc_argument_list;  /* rpc-argument-list */

/* WRITE-ICP-RPC-ARGUMENT-LIST */
Object write_icp_rpc_argument_list(rpc_argument_list)
    Object rpc_argument_list;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object value_or_object, ab_loop_list_, result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,71);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
		    string_constant_3,Qvalue,T,rpc_argument_list,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  write_icp_unsigned_integer(length(rpc_argument_list));
	  value_or_object = Nil;
	  ab_loop_list_ = rpc_argument_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  value_or_object = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  write_icp_rpc_value_or_object(value_or_object);
	  goto next_loop;
	end_loop:
	  result_of_write = Qnil;
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qrpc_argument_list,string_constant_3,Qvalue,Nil,Nil,
		      Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else {
	write_icp_unsigned_integer(length(rpc_argument_list));
	value_or_object = Nil;
	ab_loop_list_ = rpc_argument_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	value_or_object = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_icp_rpc_value_or_object(value_or_object);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* RECLAIM-IGNORED-RPC-ARGUMENT-LIST */
Object reclaim_ignored_rpc_argument_list(rpc_argument_list)
    Object rpc_argument_list;
{
    Object argument, ab_loop_list_, object_argument_qm, rpc_arglist_structure;
    Object arg;

    x_note_fn_call(158,72);
    argument = Nil;
    ab_loop_list_ = rpc_argument_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	object_argument_qm = argument;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    object_argument_qm = Nil;
    goto end_1;
    object_argument_qm = Qnil;
  end_1:;
    if (object_argument_qm) {
	rpc_arglist_structure = ISVREF(object_argument_qm,(SI_Long)9L);
	arg = Nil;
	ab_loop_list_ = rpc_argument_list;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(FIXNUMP(arg) || SYMBOLP(arg) || SIMPLE_VECTOR_P(arg)))
	    reclaim_if_evaluation_value_1(arg);
	goto next_loop_1;
      end_loop_1:;
	reclaim_receiving_rpc_arglist_structure_1(rpc_arglist_structure);
    }
    else
	reclaim_unprocessed_rpc_argument_list(2,rpc_argument_list,
		frame_serial_number_0());
    return VALUES_1(Nil);
}

/* READ-ICP-RPC-ARGUMENT-LIST */
Object read_icp_rpc_argument_list()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, length_1;
    Object result_of_read, argument, argument_list_head_qm, argument_list_tail;
    Object enclosing_arglist_structure_qm;
    Object previous_receiving_resumable_object_qm, argument_cons;
    SI_Long ab_loop_repeat_;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,73);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  length_1 = read_icp_unsigned_integer();
	  if (IFIX(length_1) <= (SI_Long)0L)
	      result_of_read = Nil;
	  else {
	      ab_loop_repeat_ = IFIX(length_1);
	      argument = Nil;
	      argument_list_head_qm = Nil;
	      argument_list_tail = Nil;
	      enclosing_arglist_structure_qm = Nil;
	      previous_receiving_resumable_object_qm = Nil;
	    next_loop:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      argument = read_icp_rpc_value_or_object();
	      argument_cons = icp_cons_1(argument,Nil);
	      if (argument_list_head_qm)
		  M_CDR(argument_list_tail) = argument_cons;
	      else
		  argument_list_head_qm = argument_cons;
	      argument_list_tail = argument_cons;
	      if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
			  {
		  if ( !TRUEP(enclosing_arglist_structure_qm))
		      enclosing_arglist_structure_qm = 
			      make_receiving_rpc_arglist_structure_1();
		  SVREF(argument,FIX((SI_Long)9L)) = 
			  enclosing_arglist_structure_qm;
		  if (previous_receiving_resumable_object_qm)
		      SVREF(previous_receiving_resumable_object_qm,
			      FIX((SI_Long)3L)) = argument;
		  SVREF(argument,FIX((SI_Long)4L)) = 
			  previous_receiving_resumable_object_qm;
		  previous_receiving_resumable_object_qm = argument;
	      }
	      goto next_loop;
	    end_loop:
	      if (enclosing_arglist_structure_qm)
		  SVREF(enclosing_arglist_structure_qm,FIX((SI_Long)1L)) = 
			  argument_list_head_qm;
	      result_of_read = argument_list_head_qm;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	  }
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qrpc_argument_list,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	length_1 = read_icp_unsigned_integer();
	if (IFIX(length_1) <= (SI_Long)0L)
	    return VALUES_1(Nil);
	else {
	    ab_loop_repeat_ = IFIX(length_1);
	    argument = Nil;
	    argument_list_head_qm = Nil;
	    argument_list_tail = Nil;
	    enclosing_arglist_structure_qm = Nil;
	    previous_receiving_resumable_object_qm = Nil;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    argument = read_icp_rpc_value_or_object();
	    argument_cons = icp_cons_1(argument,Nil);
	    if (argument_list_head_qm)
		M_CDR(argument_list_tail) = argument_cons;
	    else
		argument_list_head_qm = argument_cons;
	    argument_list_tail = argument_cons;
	    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
			{
		if ( !TRUEP(enclosing_arglist_structure_qm))
		    enclosing_arglist_structure_qm = 
			    make_receiving_rpc_arglist_structure_1();
		SVREF(argument,FIX((SI_Long)9L)) = 
			enclosing_arglist_structure_qm;
		if (previous_receiving_resumable_object_qm)
		    SVREF(previous_receiving_resumable_object_qm,
			    FIX((SI_Long)3L)) = argument;
		SVREF(argument,FIX((SI_Long)4L)) = 
			previous_receiving_resumable_object_qm;
		previous_receiving_resumable_object_qm = argument;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    if (enclosing_arglist_structure_qm)
		SVREF(enclosing_arglist_structure_qm,FIX((SI_Long)1L)) = 
			argument_list_head_qm;
	    return VALUES_1(argument_list_head_qm);
	    return VALUES_1(Qnil);
	}
    }
}

/* GET-ITEM-FROM-ARGUMENTS */
Object get_item_from_arguments(rpc_arguments)
    Object rpc_arguments;
{
    x_note_fn_call(158,74);
    return VALUES_1(rpc_arguments);
}

DEFINE_VARIABLE_WITH_SYMBOL(Rpc_throw_tag, Qrpc_throw_tag);

Object Possibly_interned_symbol_tags = UNBOUND;

/* WRITE-ICP-POSSIBLY-INTERNED-SYMBOL */
Object write_icp_possibly_interned_symbol(possibly_interned_symbol,
	    corresponding_index_of_symbol_qm)
    Object possibly_interned_symbol, corresponding_index_of_symbol_qm;
{
    Object symbol_name_1, symbol_index, overflow_count_qm;
    Object result;

    x_note_fn_call(158,75);
    if ( !TRUEP(corresponding_index_of_symbol_qm))
	corresponding_index_of_symbol_qm = 
		get_icp_object_index_for_symbol(possibly_interned_symbol,
		Current_icp_port);
    if (corresponding_index_of_symbol_qm) {
	write_icp_byte(Possibly_interned_symbol_interned_tag);
	return write_icp_fixnum(corresponding_index_of_symbol_qm);
    }
    else {
	symbol_name_1 = symbol_name_text_string(possibly_interned_symbol);
	result = establish_new_object_index_for_symbol(3,
		possibly_interned_symbol,Current_icp_port,Nil);
	MVS_2(result,symbol_index,overflow_count_qm);
	if (overflow_count_qm) {
	    write_icp_byte(Possibly_interned_symbol_uninterned_overflow_tag);
	    write_icp_fixnum(overflow_count_qm);
	}
	else
	    write_icp_byte(Possibly_interned_symbol_uninterned_tag);
	write_icp_fixnum(symbol_index);
	return write_icp_text_string(symbol_name_1);
    }
}

/* READ-ICP-POSSIBLY-INTERNED-SYMBOL */
Object read_icp_possibly_interned_symbol()
{
    Object tag, symbol_index, symbol, symbol_name_1, new_index_limit_plus_one;

    x_note_fn_call(158,76);
    tag = read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 0:
	    symbol_index = read_icp_fixnum();
	    symbol = get_from_icp_port(Current_icp_port,symbol_index,
		    Qstandard_icp_object_index_space);
	    return VALUES_1(symbol);
	  case 1:
	    symbol_index = read_icp_fixnum();
	    symbol_name_1 = read_icp_text_string();
	    symbol = intern_text_string(1,symbol_name_1);
	    store_corresponding_icp_object(symbol_index,symbol);
	    return VALUES_1(symbol);
	  case 2:
	    new_index_limit_plus_one = read_icp_fixnum();
	    handler_for_enlarge_corresponding_icp_object_index_space(Qstandard_icp_object_index_space,
		    new_index_limit_plus_one);
	    symbol_index = read_icp_fixnum();
	    symbol_name_1 = read_icp_text_string();
	    symbol = intern_text_string(1,symbol_name_1);
	    store_corresponding_icp_object(symbol_index,symbol);
	    return VALUES_1(symbol);
	  default:
	    return VALUES_1(Nil);
	}
}

Object Attribute_spec_qm_tags = UNBOUND;

static Object Qvector_element;     /* vector-element */

static Object Qattribute;          /* attribute */

static Object list_constant_1;     /* # */

static Object Qlist_element;       /* list-element */

/* WRITE-ICP-ATTRIBUTE-SPEC? */
Object write_icp_attribute_spec_qm(attribute_spec_qm)
    Object attribute_spec_qm;
{
    Object attribute_type, type, class_qualifier_qm, base_name;

    x_note_fn_call(158,77);
    if (attribute_spec_qm) {
	if (FIXNUMP(attribute_spec_qm))
	    attribute_type = Qvector_element;
	else if (SYMBOLP(attribute_spec_qm))
	    attribute_type = Qattribute;
	else if (CONSP(attribute_spec_qm)) {
	    type = M_CAR(attribute_spec_qm);
	    attribute_type = EQ(type,Qclass_qualified_name) ? Qattribute : 
		    type;
	}
	else
	    attribute_type = Qnil;
	if (EQ(attribute_type,Qattribute)) {
	    if (memq_function(CONSP(attribute_spec_qm) ? 
		    THIRD(attribute_spec_qm) : attribute_spec_qm,
		    list_constant_1)) {
		class_qualifier_qm = CONSP(attribute_spec_qm) ? 
			SECOND(attribute_spec_qm) : Nil;
		base_name = CONSP(attribute_spec_qm) ? 
			THIRD(attribute_spec_qm) : attribute_spec_qm;
		if (class_qualifier_qm) {
		    write_icp_byte(Qualified_system_attribute_tag);
		    write_icp_possibly_interned_symbol(class_qualifier_qm,Nil);
		}
		else
		    write_icp_byte(Unqualified_system_attribute_tag);
		write_icp_possibly_interned_symbol(base_name,Nil);
	    }
	    else {
		class_qualifier_qm = CONSP(attribute_spec_qm) ? 
			SECOND(attribute_spec_qm) : Nil;
		base_name = CONSP(attribute_spec_qm) ? 
			THIRD(attribute_spec_qm) : attribute_spec_qm;
		if (class_qualifier_qm) {
		    write_icp_byte(Qualified_symbolic_attribute_tag);
		    write_icp_possibly_interned_symbol(class_qualifier_qm,Nil);
		}
		else
		    write_icp_byte(Unqualified_symbolic_attribute_tag);
		write_icp_possibly_interned_symbol(base_name,Nil);
	    }
	}
	else if (EQ(attribute_type,Qvector_element)) {
	    write_icp_byte(Vector_element_attribute_spec_tag);
	    write_icp_fixnum(FIXNUMP(attribute_spec_qm) ? 
		    attribute_spec_qm : SECOND(attribute_spec_qm));
	}
	else if (EQ(attribute_type,Qlist_element)) {
	    write_icp_byte(List_element_attribute_spec_tag);
	    write_icp_fixnum(FIXNUMP(attribute_spec_qm) ? 
		    attribute_spec_qm : SECOND(attribute_spec_qm));
	}
    }
    else
	write_icp_byte(Nameless_attribute_spec_tag);
    return VALUES_1(Nil);
}

/* READ-ICP-ATTRIBUTE-SPEC? */
Object read_icp_attribute_spec_qm()
{
    Object tag, base_name, qualifier, index_1;

    x_note_fn_call(158,78);
    tag = read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_3(Qattribute,Nil,Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 12:
	    base_name = read_icp_possibly_interned_symbol();
	    return VALUES_3(Qattribute,Nil,base_name);
	  case 13:
	    qualifier = read_icp_possibly_interned_symbol();
	    base_name = read_icp_possibly_interned_symbol();
	    return VALUES_3(Qattribute,qualifier,base_name);
	  case 14:
	    base_name = read_icp_possibly_interned_symbol();
	    return VALUES_3(Qattribute,Nil,base_name);
	  case 15:
	    qualifier = read_icp_possibly_interned_symbol();
	    base_name = read_icp_possibly_interned_symbol();
	    return VALUES_3(Qattribute,qualifier,base_name);
	  case 3:
	    index_1 = read_icp_fixnum();
	    return VALUES_3(Qvector_element,Nil,index_1);
	  case 4:
	    index_1 = read_icp_fixnum();
	    return VALUES_3(Qlist_element,Nil,index_1);
	  default:
	    return VALUES_3(Qattribute,Nil,Nil);
	}
}

static Object Qlist_of_attributes;  /* list-of-attributes */

static Object Qwrite_icp_list_of_attributes;  /* write-icp-list-of-attributes */

static Object string_constant_4;   /* "resumable icp synch error: ~S expected, ~S found" */

/* WRITE-ICP-LIST-OF-ATTRIBUTES */
Object write_icp_list_of_attributes(list_of_attributes)
    Object list_of_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,79);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_attributes,
			string_constant_3,Qvalue,T,list_of_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = 
		      g2_write_icp_list_of_attributes(list_of_attributes);
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_attributes,string_constant_3,Qvalue,Nil,
			  Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = g2_write_icp_list_of_attributes(list_of_attributes);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_list_of_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_attributes,top,Nil);
		goto end_write_icp_list_of_attributes;
	    }
	}
	list_of_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_attributes,
			string_constant_3,Qvalue,T,list_of_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      value = g2_write_icp_list_of_attributes(list_of_attributes);
	      if (EQ(icp_suspend_1,value)) {
		  resumable_icp_push(list_of_attributes);
		  resumable_icp_push(Qwrite_icp_list_of_attributes);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_list_of_attributes;
	      }
	      result_of_write = value;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_attributes,string_constant_3,Qvalue,Nil,
			  Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    value = g2_write_icp_list_of_attributes(list_of_attributes);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_attributes);
		resumable_icp_push(Qwrite_icp_list_of_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_attributes;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_attributes:
    return result;
}

static Object Qread_icp_list_of_attributes;  /* read-icp-list-of-attributes */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* READ-ICP-LIST-OF-ATTRIBUTES */
Object read_icp_list_of_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, length_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, tag, result_of_read;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long count_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,80);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      length_1 = read_icp_fixnum();
	      count_1 = (SI_Long)1L;
	      ab_loop_bind_ = IFIX(length_1);
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if (count_1 > ab_loop_bind_)
		  goto end_loop;
	      tag = read_icp_byte();
	      ab_loopvar__2 = 
		      icp_cons_1(g2_read_icp_attribute_for_list_of_attributes(tag),
		      Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      result_of_read = ab_loopvar_;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_attributes,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    length_1 = read_icp_fixnum();
	    count_1 = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(length_1);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (count_1 > ab_loop_bind_)
		goto end_loop_1;
	    tag = read_icp_byte();
	    ab_loopvar__2 = 
		    icp_cons_1(g2_read_icp_attribute_for_list_of_attributes(tag),
		    Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qread_icp_list_of_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_attributes,top,Nil);
		goto end_read_icp_list_of_attributes;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		  length_1 = resumable_icp_pop();
	      else {
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_list_of_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_attributes;
		  }
		  length_1 = value;
	      }
	      count_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	      if (count_1 > ab_loop_bind_)
		  goto end_loop_2;
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      tag = resumable_icp_pop();
		  else {
		      value = read_icp_byte();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(ab_loopvar__2);
			  resumable_icp_push(ab_loopvar__1);
			  resumable_icp_push(ab_loopvar_);
			  resumable_icp_push(FIX(ab_loop_bind_));
			  resumable_icp_push(FIX(count_1));
			  resumable_icp_push(length_1);
			  resumable_icp_push(Qread_icp_list_of_attributes);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_read_icp_list_of_attributes;
		      }
		      tag = value;
		  }
		  value = g2_read_icp_attribute_for_list_of_attributes(tag);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(tag);
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(count_1));
		      resumable_icp_push(length_1);
		      resumable_icp_push(Qread_icp_list_of_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_attributes;
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
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:
	      result_of_read = ab_loopvar_;
	      goto end_3;
	      result_of_read = Qnil;
	    end_3:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_attributes,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		length_1 = resumable_icp_pop();
	    else {
		value = read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_list_of_attributes);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_attributes;
		}
		length_1 = value;
	    }
	    count_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		     TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)1L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	    if (count_1 > ab_loop_bind_)
		goto end_loop_3;
	  resume_1:
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    tag = resumable_icp_pop();
		else {
		    value = read_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(ab_loopvar__2);
			resumable_icp_push(ab_loopvar__1);
			resumable_icp_push(ab_loopvar_);
			resumable_icp_push(FIX(ab_loop_bind_));
			resumable_icp_push(FIX(count_1));
			resumable_icp_push(length_1);
			resumable_icp_push(Qread_icp_list_of_attributes);
			result = VALUES_1(Icp_suspend);
			goto end_read_icp_list_of_attributes;
		    }
		    tag = value;
		}
		value = g2_read_icp_attribute_for_list_of_attributes(tag);
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(tag);
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(count_1));
		    resumable_icp_push(length_1);
		    resumable_icp_push(Qread_icp_list_of_attributes);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_attributes;
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
	    count_1 = count_1 + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_attributes:
    return result;
}

static Object Qlist_of_boolean;    /* list-of-boolean */

static Object Qread_icp_list_of_boolean;  /* read-icp-list-of-boolean */

/* READ-ICP-LIST-OF-BOOLEAN */
Object read_icp_list_of_boolean()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, length_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long count_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,81);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_boolean,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      length_1 = read_icp_fixnum();
	      count_1 = (SI_Long)1L;
	      ab_loop_bind_ = IFIX(length_1);
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if (count_1 > ab_loop_bind_)
		  goto end_loop;
	      ab_loopvar__2 = icp_cons_1(read_icp_boolean(),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      result_of_read = ab_loopvar_;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_boolean,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    length_1 = read_icp_fixnum();
	    count_1 = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(length_1);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (count_1 > ab_loop_bind_)
		goto end_loop_1;
	    ab_loopvar__2 = icp_cons_1(read_icp_boolean(),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qread_icp_list_of_boolean,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_boolean,top,Nil);
		goto end_read_icp_list_of_boolean;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_boolean,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		  length_1 = resumable_icp_pop();
	      else {
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_list_of_boolean);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_boolean;
		  }
		  length_1 = value;
	      }
	      count_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	      if (count_1 > ab_loop_bind_)
		  goto end_loop_2;
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(count_1));
		      resumable_icp_push(length_1);
		      resumable_icp_push(Qread_icp_list_of_boolean);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_boolean;
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
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:
	      result_of_read = ab_loopvar_;
	      goto end_3;
	      result_of_read = Qnil;
	    end_3:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_boolean,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		length_1 = resumable_icp_pop();
	    else {
		value = read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_list_of_boolean);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_boolean;
		}
		length_1 = value;
	    }
	    count_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		     TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)1L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	    if (count_1 > ab_loop_bind_)
		goto end_loop_3;
	  resume_1:
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		value = read_icp_boolean();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(count_1));
		    resumable_icp_push(length_1);
		    resumable_icp_push(Qread_icp_list_of_boolean);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_boolean;
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
	    count_1 = count_1 + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_boolean:
    return result;
}

static Object Qwrite_icp_list_of_boolean;  /* write-icp-list-of-boolean */

/* WRITE-ICP-LIST-OF-BOOLEAN */
Object write_icp_list_of_boolean(list_of_boolean)
    Object list_of_boolean;
{
    Object tracep, byte_count_before, current_icp_write_trace_level, value;
    Object ab_loop_list_, result_of_write, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,82);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_boolean,
			string_constant_3,Qvalue,T,list_of_boolean,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      write_icp_fixnum(length(list_of_boolean));
	      value = Nil;
	      ab_loop_list_ = list_of_boolean;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      value = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      write_icp_boolean(value);
	      goto next_loop;
	    end_loop:
	      result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_boolean,string_constant_3,Qvalue,Nil,
			  Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    write_icp_fixnum(length(list_of_boolean));
	    value = Nil;
	    ab_loop_list_ = list_of_boolean;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    value = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    write_icp_boolean(value);
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
	    if ( !EQ(Qwrite_icp_list_of_boolean,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_boolean,top,Nil);
		goto end_write_icp_list_of_boolean;
	    }
	}
	list_of_boolean = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_boolean;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_boolean,
			string_constant_3,Qvalue,T,list_of_boolean,Nil,Nil);
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
			  write_icp_fixnum(length(list_of_boolean)))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loop_list_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : list_of_boolean;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      value = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	    resume:
	      if (EQ(icp_suspend_1,write_icp_boolean(value))) {
		  resumable_icp_push(ab_loop_list_);
		  resumable_icp_push(value);
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
		  resumable_icp_push(list_of_boolean);
		  resumable_icp_push(Qwrite_icp_list_of_boolean);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_list_of_boolean;
	      }
	      temp = v1;
	      result_of_write = temp;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_boolean,string_constant_3,Qvalue,Nil,
			  Nil,Nil,Nil);
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
	    if (EQ(icp_suspend_1,write_icp_fixnum(length(list_of_boolean)))) {
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loop_list_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : list_of_boolean;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    value = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	  resume_1:
	    if (EQ(icp_suspend_1,write_icp_boolean(value))) {
		resumable_icp_push(ab_loop_list_);
		resumable_icp_push(value);
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
		resumable_icp_push(list_of_boolean);
		resumable_icp_push(Qwrite_icp_list_of_boolean);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_boolean;
	    }
	    temp = v1;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_boolean:
    return result;
}

static Object Qlist_of_lists_of_attributes;  /* list-of-lists-of-attributes */

static Object Qwrite_icp_list_of_lists_of_attributes;  /* write-icp-list-of-lists-of-attributes */

/* WRITE-ICP-LIST-OF-LISTS-OF-ATTRIBUTES */
Object write_icp_list_of_lists_of_attributes(list_of_lists_of_attributes)
    Object list_of_lists_of_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object list_of_attributes, ab_loop_list_, result_of_write, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,83);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_lists_of_attributes,string_constant_3,
			Qvalue,T,list_of_lists_of_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      write_icp_fixnum(length(list_of_lists_of_attributes));
	      list_of_attributes = Nil;
	      ab_loop_list_ = list_of_lists_of_attributes;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      list_of_attributes = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      write_icp_list_of_attributes(list_of_attributes);
	      goto next_loop;
	    end_loop:
	      result_of_write = Qnil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_lists_of_attributes,string_constant_3,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else {
	    write_icp_fixnum(length(list_of_lists_of_attributes));
	    list_of_attributes = Nil;
	    ab_loop_list_ = list_of_lists_of_attributes;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    list_of_attributes = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    write_icp_list_of_attributes(list_of_attributes);
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
	    if ( !EQ(Qwrite_icp_list_of_lists_of_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_lists_of_attributes,top,Nil);
		goto end_write_icp_list_of_lists_of_attributes;
	    }
	}
	list_of_lists_of_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_lists_of_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_lists_of_attributes,string_constant_3,
			Qvalue,T,list_of_lists_of_attributes,Nil,Nil);
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
		      write_icp_fixnum(length(list_of_lists_of_attributes)))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(Icp_suspend);
		  goto end_block;
	      }
	    l2:
	      list_of_attributes = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : Nil;
	      ab_loop_list_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : list_of_lists_of_attributes;
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil))
		  goto resume;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      list_of_attributes = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	    resume:
	      if (EQ(icp_suspend_1,
		      write_icp_list_of_attributes(list_of_attributes))) {
		  resumable_icp_push(ab_loop_list_);
		  resumable_icp_push(list_of_attributes);
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
		  resumable_icp_push(list_of_lists_of_attributes);
		  resumable_icp_push(Qwrite_icp_list_of_lists_of_attributes);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_write_icp_list_of_lists_of_attributes;
	      }
	      temp = v1;
	      result_of_write = temp;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_lists_of_attributes,string_constant_3,
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
		    write_icp_fixnum(length(list_of_lists_of_attributes)))) {
		resumable_icp_push(FIX((SI_Long)1L));
		result = VALUES_1(Icp_suspend);
		goto end_block_1;
	    }
	  l2_1:
	    list_of_attributes = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : Nil;
	    ab_loop_list_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : list_of_lists_of_attributes;
	    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil))
		goto resume_1;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    list_of_attributes = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	  resume_1:
	    if (EQ(icp_suspend_1,
		    write_icp_list_of_attributes(list_of_attributes))) {
		resumable_icp_push(ab_loop_list_);
		resumable_icp_push(list_of_attributes);
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
		resumable_icp_push(list_of_lists_of_attributes);
		resumable_icp_push(Qwrite_icp_list_of_lists_of_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_lists_of_attributes;
	    }
	    temp = v1;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_lists_of_attributes:
    return result;
}

static Object Qread_icp_list_of_lists_of_attributes;  /* read-icp-list-of-lists-of-attributes */

/* READ-ICP-LIST-OF-LISTS-OF-ATTRIBUTES */
Object read_icp_list_of_lists_of_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, length_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long count_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,84);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_lists_of_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      length_1 = read_icp_fixnum();
	      count_1 = (SI_Long)1L;
	      ab_loop_bind_ = IFIX(length_1);
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      ab_loopvar__2 = Nil;
	    next_loop:
	      if (count_1 > ab_loop_bind_)
		  goto end_loop;
	      ab_loopvar__2 = icp_cons_1(read_icp_list_of_attributes(),Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      result_of_read = ab_loopvar_;
	      goto end_1;
	      result_of_read = Qnil;
	    end_1:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_lists_of_attributes,string_constant_3,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    length_1 = read_icp_fixnum();
	    count_1 = (SI_Long)1L;
	    ab_loop_bind_ = IFIX(length_1);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if (count_1 > ab_loop_bind_)
		goto end_loop_1;
	    ab_loopvar__2 = icp_cons_1(read_icp_list_of_attributes(),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qread_icp_list_of_lists_of_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_lists_of_attributes,top,Nil);
		goto end_read_icp_list_of_lists_of_attributes;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_lists_of_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		  length_1 = resumable_icp_pop();
	      else {
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_list_of_lists_of_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_lists_of_attributes;
		  }
		  length_1 = value;
	      }
	      count_1 = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : (SI_Long)1L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	      if (count_1 > ab_loop_bind_)
		  goto end_loop_2;
	    resume:
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  arg1 = resumable_icp_pop();
	      else {
		  value = read_icp_list_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(ab_loopvar__2);
		      resumable_icp_push(ab_loopvar__1);
		      resumable_icp_push(ab_loopvar_);
		      resumable_icp_push(FIX(ab_loop_bind_));
		      resumable_icp_push(FIX(count_1));
		      resumable_icp_push(length_1);
		      resumable_icp_push(Qread_icp_list_of_lists_of_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_lists_of_attributes;
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
	      count_1 = count_1 + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:
	      result_of_read = ab_loopvar_;
	      goto end_3;
	      result_of_read = Qnil;
	    end_3:;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_lists_of_attributes,string_constant_3,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		length_1 = resumable_icp_pop();
	    else {
		value = read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_list_of_lists_of_attributes);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_lists_of_attributes;
		}
		length_1 = value;
	    }
	    count_1 = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		     TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : (SI_Long)1L;
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(resumable_icp_pop()) : IFIX(length_1);
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
	    if (count_1 > ab_loop_bind_)
		goto end_loop_3;
	  resume_1:
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		arg1 = resumable_icp_pop();
	    else {
		value = read_icp_list_of_attributes();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(ab_loopvar__2);
		    resumable_icp_push(ab_loopvar__1);
		    resumable_icp_push(ab_loopvar_);
		    resumable_icp_push(FIX(ab_loop_bind_));
		    resumable_icp_push(FIX(count_1));
		    resumable_icp_push(length_1);
		    resumable_icp_push(Qread_icp_list_of_lists_of_attributes);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_list_of_lists_of_attributes;
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
	    count_1 = count_1 + (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_lists_of_attributes:
    return result;
}

static Object Qlist_of_included_return_attributes;  /* list-of-included-return-attributes */

static Object Qwrite_icp_list_of_included_return_attributes;  /* write-icp-list-of-included-return-attributes */

/* WRITE-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES */
Object write_icp_list_of_included_return_attributes(list_of_included_return_attributes)
    Object list_of_included_return_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,85);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_included_return_attributes,
			string_constant_3,Qvalue,T,
			list_of_included_return_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)5L ? 
		      write_icp_list_of_lists_of_attributes(list_of_included_return_attributes) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_included_return_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)5L ? 
		    write_icp_list_of_lists_of_attributes(list_of_included_return_attributes) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_list_of_included_return_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_included_return_attributes,top,Nil);
		goto end_write_icp_list_of_included_return_attributes;
	    }
	}
	list_of_included_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_included_return_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_included_return_attributes,
			string_constant_3,Qvalue,T,
			list_of_included_return_attributes,Nil,Nil);
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
		      (SI_Long)22L)) >= (SI_Long)5L) {
		  value = 
			  write_icp_list_of_lists_of_attributes(list_of_included_return_attributes);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_included_return_attributes);
		      resumable_icp_push(Qwrite_icp_list_of_included_return_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_included_return_attributes;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_included_return_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)5L) {
	    value = 
		    write_icp_list_of_lists_of_attributes(list_of_included_return_attributes);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_included_return_attributes);
		resumable_icp_push(Qwrite_icp_list_of_included_return_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_included_return_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_included_return_attributes:
    return result;
}

static Object Qread_icp_list_of_included_return_attributes;  /* read-icp-list-of-included-return-attributes */

/* READ-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES */
Object read_icp_list_of_included_return_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,86);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qlist_of_included_return_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)5L ? 
		      read_icp_list_of_lists_of_attributes() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_included_return_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)5L ? read_icp_list_of_lists_of_attributes() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_list_of_included_return_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_included_return_attributes,top,Nil);
		goto end_read_icp_list_of_included_return_attributes;
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
			Qlist_of_included_return_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)5L) {
		  value = read_icp_list_of_lists_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_included_return_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_included_return_attributes;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_included_return_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)5L) {
	    value = read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_included_return_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_included_return_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_included_return_attributes:
    return result;
}

static Object Qlist_of_excluded_return_attributes;  /* list-of-excluded-return-attributes */

static Object Qwrite_icp_list_of_excluded_return_attributes;  /* write-icp-list-of-excluded-return-attributes */

/* WRITE-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES */
Object write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes)
    Object list_of_excluded_return_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,87);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_excluded_return_attributes,
			string_constant_3,Qvalue,T,
			list_of_excluded_return_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)5L ? 
		      write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_excluded_return_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)5L ? 
		    write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_list_of_excluded_return_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_excluded_return_attributes,top,Nil);
		goto end_write_icp_list_of_excluded_return_attributes;
	    }
	}
	list_of_excluded_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_excluded_return_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_excluded_return_attributes,
			string_constant_3,Qvalue,T,
			list_of_excluded_return_attributes,Nil,Nil);
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
		      (SI_Long)22L)) >= (SI_Long)5L) {
		  value = 
			  write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_excluded_return_attributes);
		      resumable_icp_push(Qwrite_icp_list_of_excluded_return_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_excluded_return_attributes;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_excluded_return_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)5L) {
	    value = 
		    write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_excluded_return_attributes);
		resumable_icp_push(Qwrite_icp_list_of_excluded_return_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_excluded_return_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_excluded_return_attributes:
    return result;
}

static Object Qread_icp_list_of_excluded_return_attributes;  /* read-icp-list-of-excluded-return-attributes */

/* READ-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES */
Object read_icp_list_of_excluded_return_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,88);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qlist_of_excluded_return_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)5L ? 
		      read_icp_list_of_lists_of_attributes() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_excluded_return_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)5L ? read_icp_list_of_lists_of_attributes() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_list_of_excluded_return_attributes,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_excluded_return_attributes,top,Nil);
		goto end_read_icp_list_of_excluded_return_attributes;
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
			Qlist_of_excluded_return_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)5L) {
		  value = read_icp_list_of_lists_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_excluded_return_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_excluded_return_attributes;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_excluded_return_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)5L) {
	    value = read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_excluded_return_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_excluded_return_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_excluded_return_attributes:
    return result;
}

static Object Qlist_of_included_return_system_attributes;  /* list-of-included-return-system-attributes */

static Object Qwrite_icp_list_of_included_return_system_attributes;  /* write-icp-list-of-included-return-system-attributes */

/* WRITE-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES */
Object write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes)
    Object list_of_included_return_system_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,89);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_included_return_system_attributes,
			string_constant_3,Qvalue,T,
			list_of_included_return_system_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)5L ? 
		      write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_included_return_system_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)5L ? 
		    write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_list_of_included_return_system_attributes,
			top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_included_return_system_attributes,
			top,Nil);
		goto end_write_icp_list_of_included_return_system_attributes;
	    }
	}
	list_of_included_return_system_attributes = (resumable_icp_state_1 
		? TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_included_return_system_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_included_return_system_attributes,
			string_constant_3,Qvalue,T,
			list_of_included_return_system_attributes,Nil,Nil);
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
		      (SI_Long)22L)) >= (SI_Long)5L) {
		  value = 
			  write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_included_return_system_attributes);
		      resumable_icp_push(Qwrite_icp_list_of_included_return_system_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_included_return_system_attributes;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_included_return_system_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)5L) {
	    value = 
		    write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_included_return_system_attributes);
		resumable_icp_push(Qwrite_icp_list_of_included_return_system_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_included_return_system_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_included_return_system_attributes:
    return result;
}

static Object Qread_icp_list_of_included_return_system_attributes;  /* read-icp-list-of-included-return-system-attributes */

/* READ-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES */
Object read_icp_list_of_included_return_system_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,90);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qlist_of_included_return_system_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)5L ? 
		      read_icp_list_of_lists_of_attributes() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_included_return_system_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)5L ? read_icp_list_of_lists_of_attributes() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_list_of_included_return_system_attributes,
			top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_included_return_system_attributes,
			top,Nil);
		goto end_read_icp_list_of_included_return_system_attributes;
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
			Qlist_of_included_return_system_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)5L) {
		  value = read_icp_list_of_lists_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_included_return_system_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_included_return_system_attributes;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_included_return_system_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)5L) {
	    value = read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_included_return_system_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_included_return_system_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_included_return_system_attributes:
    return result;
}

static Object Qlist_of_include_all_return_system_attributes;  /* list-of-include-all-return-system-attributes */

static Object Qwrite_icp_list_of_include_all_return_system_attributes;  /* write-icp-list-of-include-all-return-system-attributes */

/* WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES */
Object write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes)
    Object list_of_include_all_return_system_attributes;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,91);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes,
			string_constant_3,Qvalue,T,
			list_of_include_all_return_system_attributes,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)9L ? 
		      write_icp_list_of_boolean(list_of_include_all_return_system_attributes) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_include_all_return_system_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)9L ? 
		    write_icp_list_of_boolean(list_of_include_all_return_system_attributes) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qwrite_icp_list_of_include_all_return_system_attributes,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_include_all_return_system_attributes,
			top,Nil);
		goto end_write_icp_list_of_include_all_return_system_attributes;
	    }
	}
	list_of_include_all_return_system_attributes = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_include_all_return_system_attributes;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes,
			string_constant_3,Qvalue,T,
			list_of_include_all_return_system_attributes,Nil,Nil);
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
		      (SI_Long)22L)) >= (SI_Long)9L) {
		  value = 
			  write_icp_list_of_boolean(list_of_include_all_return_system_attributes);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_include_all_return_system_attributes);
		      resumable_icp_push(Qwrite_icp_list_of_include_all_return_system_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_include_all_return_system_attributes;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_include_all_return_system_attributes,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)9L) {
	    value = 
		    write_icp_list_of_boolean(list_of_include_all_return_system_attributes);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_include_all_return_system_attributes);
		resumable_icp_push(Qwrite_icp_list_of_include_all_return_system_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_include_all_return_system_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_include_all_return_system_attributes:
    return result;
}

static Object Qread_icp_list_of_include_all_return_system_attributes;  /* read-icp-list-of-include-all-return-system-attributes */

/* READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES */
Object read_icp_list_of_include_all_return_system_attributes()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,92);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)9L ? 
		      read_icp_list_of_boolean() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_include_all_return_system_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)9L ? read_icp_list_of_boolean() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qread_icp_list_of_include_all_return_system_attributes,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_include_all_return_system_attributes,
			top,Nil);
		goto end_read_icp_list_of_include_all_return_system_attributes;
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
			Qlist_of_include_all_return_system_attributes,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)9L) {
		  value = read_icp_list_of_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_include_all_return_system_attributes);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_include_all_return_system_attributes;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_include_all_return_system_attributes,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)9L) {
	    value = read_icp_list_of_boolean();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_include_all_return_system_attributes);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_include_all_return_system_attributes;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_include_all_return_system_attributes:
    return result;
}

static Object Qlist_of_include_all_return_system_attributes_except;  /* list-of-include-all-return-system-attributes-except */

static Object Qwrite_icp_list_of_include_all_return_system_attributes_except;  /* write-icp-list-of-include-all-return-system-attributes-except */

/* WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT */
Object write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except)
    Object list_of_include_all_return_system_attributes_except;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,93);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes_except,
			string_constant_3,Qvalue,T,
			list_of_include_all_return_system_attributes_except,
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
		      (SI_Long)22L)) >= (SI_Long)25L ? 
		      write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except) 
		      : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_include_all_return_system_attributes_except,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)25L ? 
		    write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except) 
		    : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qwrite_icp_list_of_include_all_return_system_attributes_except,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_include_all_return_system_attributes_except,
			top,Nil);
		goto end_write_icp_list_of_include_all_return_system_attributes_except;
	    }
	}
	list_of_include_all_return_system_attributes_except = 
		(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : 
		list_of_include_all_return_system_attributes_except;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes_except,
			string_constant_3,Qvalue,T,
			list_of_include_all_return_system_attributes_except,
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
		      (SI_Long)22L)) >= (SI_Long)25L) {
		  value = 
			  write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_include_all_return_system_attributes_except);
		      resumable_icp_push(Qwrite_icp_list_of_include_all_return_system_attributes_except);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_include_all_return_system_attributes_except;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_include_all_return_system_attributes_except,
			  string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)25L) {
	    value = 
		    write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_include_all_return_system_attributes_except);
		resumable_icp_push(Qwrite_icp_list_of_include_all_return_system_attributes_except);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_include_all_return_system_attributes_except;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_include_all_return_system_attributes_except:
    return result;
}

static Object Qread_icp_list_of_include_all_return_system_attributes_except;  /* read-icp-list-of-include-all-return-system-attributes-except */

/* READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT */
Object read_icp_list_of_include_all_return_system_attributes_except()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,94);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qlist_of_include_all_return_system_attributes_except,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)25L ? 
		      read_icp_list_of_lists_of_attributes() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_include_all_return_system_attributes_except,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)25L ? read_icp_list_of_lists_of_attributes() :
		     Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qread_icp_list_of_include_all_return_system_attributes_except,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_include_all_return_system_attributes_except,
			top,Nil);
		goto end_read_icp_list_of_include_all_return_system_attributes_except;
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
			Qlist_of_include_all_return_system_attributes_except,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)25L) {
		  value = read_icp_list_of_lists_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_include_all_return_system_attributes_except);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_include_all_return_system_attributes_except;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_include_all_return_system_attributes_except,
			  string_constant_3,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)25L) {
	    value = read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_include_all_return_system_attributes_except);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_include_all_return_system_attributes_except;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_include_all_return_system_attributes_except:
    return result;
}

static Object Qlist_of_return_kinds;  /* list-of-return-kinds */

static Object Qwrite_icp_list_of_return_kinds;  /* write-icp-list-of-return-kinds */

/* WRITE-ICP-LIST-OF-RETURN-KINDS */
Object write_icp_list_of_return_kinds(list_of_return_kinds)
    Object list_of_return_kinds;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,95);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_return_kinds,
			string_constant_3,Qvalue,T,list_of_return_kinds,
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
		      (SI_Long)22L)) >= (SI_Long)8L ? 
		      write_icp_list_of_attributes(list_of_return_kinds) : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_return_kinds,string_constant_3,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L ? 
		    write_icp_list_of_attributes(list_of_return_kinds) : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_list_of_return_kinds,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_list_of_return_kinds,top,Nil);
		goto end_write_icp_list_of_return_kinds;
	    }
	}
	list_of_return_kinds = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : list_of_return_kinds;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qlist_of_return_kinds,
			string_constant_3,Qvalue,T,list_of_return_kinds,
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
		      (SI_Long)22L)) >= (SI_Long)8L) {
		  value = write_icp_list_of_attributes(list_of_return_kinds);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(list_of_return_kinds);
		      resumable_icp_push(Qwrite_icp_list_of_return_kinds);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_list_of_return_kinds;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qlist_of_return_kinds,string_constant_3,Qvalue,
			  Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)8L) {
	    value = write_icp_list_of_attributes(list_of_return_kinds);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(list_of_return_kinds);
		resumable_icp_push(Qwrite_icp_list_of_return_kinds);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_list_of_return_kinds;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_list_of_return_kinds:
    return result;
}

static Object Qread_icp_list_of_return_kinds;  /* read-icp-list-of-return-kinds */

/* READ-ICP-LIST-OF-RETURN-KINDS */
Object read_icp_list_of_return_kinds()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,96);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)8L ? 
		      read_icp_list_of_attributes() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_return_kinds,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)8L ? read_icp_list_of_attributes() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_list_of_return_kinds,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_list_of_return_kinds,top,Nil);
		goto end_read_icp_list_of_return_kinds;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qlist_of_return_kinds,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)8L) {
		  value = read_icp_list_of_attributes();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_list_of_return_kinds);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_list_of_return_kinds;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qlist_of_return_kinds,string_constant_3,Qvalue,T,
			  result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)8L) {
	    value = read_icp_list_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_list_of_return_kinds);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_list_of_return_kinds;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_list_of_return_kinds:
    return result;
}

static Object Qremote_procedure_varargs_p;  /* remote-procedure-varargs-p */

static Object Qwrite_icp_remote_procedure_varargs_p;  /* write-icp-remote-procedure-varargs-p */

/* WRITE-ICP-REMOTE-PROCEDURE-VARARGS-P */
Object write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p)
    Object remote_procedure_varargs_p;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,97);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qremote_procedure_varargs_p,
			string_constant_3,Qvalue,T,
			remote_procedure_varargs_p,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)22L)) >= (SI_Long)9L ? 
		      write_icp_boolean(remote_procedure_varargs_p) : Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qremote_procedure_varargs_p,string_constant_3,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)9L ? 
		    write_icp_boolean(remote_procedure_varargs_p) : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_remote_procedure_varargs_p,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qwrite_icp_remote_procedure_varargs_p,top,Nil);
		goto end_write_icp_remote_procedure_varargs_p;
	    }
	}
	remote_procedure_varargs_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_varargs_p;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,Qremote_procedure_varargs_p,
			string_constant_3,Qvalue,T,
			remote_procedure_varargs_p,Nil,Nil);
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
		      (SI_Long)22L)) >= (SI_Long)9L) {
		  value = write_icp_boolean(remote_procedure_varargs_p);
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(remote_procedure_varargs_p);
		      resumable_icp_push(Qwrite_icp_remote_procedure_varargs_p);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_write_icp_remote_procedure_varargs_p;
		  }
		  result_of_write = value;
	      }
	      else
		  result_of_write = Nil;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qremote_procedure_varargs_p,string_constant_3,
			  Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)22L)) >= (SI_Long)9L) {
	    value = write_icp_boolean(remote_procedure_varargs_p);
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(remote_procedure_varargs_p);
		resumable_icp_push(Qwrite_icp_remote_procedure_varargs_p);
		result = VALUES_1(Icp_suspend);
		goto end_write_icp_remote_procedure_varargs_p;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_write_icp_remote_procedure_varargs_p:
    return result;
}

static Object Qread_icp_remote_procedure_varargs_p;  /* read-icp-remote-procedure-varargs-p */

/* READ-ICP-REMOTE-PROCEDURE-VARARGS-P */
Object read_icp_remote_procedure_varargs_p()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Object value;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,98);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_varargs_p,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = IFIX(ISVREF(Current_icp_socket,
		      (SI_Long)21L)) >= (SI_Long)9L ? read_icp_boolean() : Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_procedure_varargs_p,string_constant_3,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)9L ? read_icp_boolean() : Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_remote_procedure_varargs_p,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qread_icp_remote_procedure_varargs_p,top,Nil);
		goto end_read_icp_remote_procedure_varargs_p;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_varargs_p,
			string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
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
		      (SI_Long)21L)) >= (SI_Long)9L) {
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qread_icp_remote_procedure_varargs_p);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_remote_procedure_varargs_p;
		  }
		  result_of_read = value;
	      }
	      else
		  result_of_read = Nil;
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qremote_procedure_varargs_p,string_constant_3,
			  Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) || IFIX(ISVREF(Current_icp_socket,
		(SI_Long)21L)) >= (SI_Long)9L) {
	    value = read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		resumable_icp_push(Qread_icp_remote_procedure_varargs_p);
		result = VALUES_1(Icp_suspend);
		goto end_read_icp_remote_procedure_varargs_p;
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    result = VALUES_1(temp);
  end_read_icp_remote_procedure_varargs_p:
    return result;
}

Object Attribute_value_tags = UNBOUND;

static Object Qevaluation_truth_value;  /* evaluation-truth-value */

/* WRITE-ICP-EVALUATION-TRUTH-VALUE */
Object write_icp_evaluation_truth_value(evaluation_truth_value)
    Object evaluation_truth_value;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,99);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qevaluation_truth_value,
		    string_constant_3,Qvalue,T,evaluation_truth_value,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  result_of_write = write_icp_fixnum(evaluation_truth_value);
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qevaluation_truth_value,string_constant_3,Qvalue,Nil,
		      Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else
	return write_icp_fixnum(evaluation_truth_value);
}

/* RECLAIM-EVALUATION-TRUTH-VALUE-IF-APPROPRIATE */
Object reclaim_evaluation_truth_value_if_appropriate(maybe_evaluation_truth_value)
    Object maybe_evaluation_truth_value;
{
    x_note_fn_call(158,100);
    if ( !(EQ(maybe_evaluation_truth_value,Evaluation_true_value) || 
	    EQ(maybe_evaluation_truth_value,Evaluation_false_value)))
	reclaim_eval_cons_1(maybe_evaluation_truth_value);
    return VALUES_1(Nil);
}

/* READ-ICP-EVALUATION-TRUTH-VALUE */
Object read_icp_evaluation_truth_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,101);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qevaluation_truth_value,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  result_of_read = 
		  make_evaluation_truth_value_function(read_icp_fixnum());
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qevaluation_truth_value,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else
	return make_evaluation_truth_value_function(read_icp_fixnum());
}

/* WRITE-ICP-ATTRIBUTE-VALUE */
Object write_icp_attribute_value(simple_value,corresponding_index_qm)
    Object simple_value, corresponding_index_qm;
{
    x_note_fn_call(158,102);
    g2_write_icp_attribute_value(simple_value,corresponding_index_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-ATTRIBUTE-VALUE */
Object reclaim_icp_attribute_value(icp_attribute_value)
    Object icp_attribute_value;
{
    x_note_fn_call(158,103);
    if (text_string_p(icp_attribute_value))
	reclaim_text_or_gensym_string(icp_attribute_value);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(icp_attribute_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_attribute_value)) == 
	    (SI_Long)1L)
	reclaim_managed_simple_float_array_of_length_1(icp_attribute_value);
    return VALUES_1(Nil);
}

/* READ-ICP-ATTRIBUTE-VALUE */
Object read_icp_attribute_value()
{
    Object tag, symbol_qm, symbol_index, symbol, symbol_name_1;
    Object new_index_limit_plus_one, temp;

    x_note_fn_call(158,104);
    tag = read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	symbol_qm = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 0:
	    symbol_index = read_icp_fixnum();
	    symbol = get_from_icp_port(Current_icp_port,symbol_index,
		    Qstandard_icp_object_index_space);
	    symbol_qm = symbol;
	    break;
	  case 1:
	    symbol_index = read_icp_fixnum();
	    symbol_name_1 = read_icp_text_string();
	    symbol = intern_text_string(1,symbol_name_1);
	    store_corresponding_icp_object(symbol_index,symbol);
	    symbol_qm = symbol;
	    break;
	  case 2:
	    new_index_limit_plus_one = read_icp_fixnum();
	    handler_for_enlarge_corresponding_icp_object_index_space(Qstandard_icp_object_index_space,
		    new_index_limit_plus_one);
	    symbol_index = read_icp_fixnum();
	    symbol_name_1 = read_icp_text_string();
	    symbol = intern_text_string(1,symbol_name_1);
	    store_corresponding_icp_object(symbol_index,symbol);
	    symbol_qm = symbol;
	    break;
	  default:
	    symbol_qm = Nil;
	    break;
	}
    temp = symbol_qm;
    if (temp);
    else if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 5:
	    temp = read_icp_fixnum();
	    break;
	  case 16:
	    temp = read_icp_managed_long();
	    break;
	  case 6:
	    temp = read_icp_managed_double_float();
	    break;
	  case 8:
	    temp = read_icp_text_string();
	    break;
	  case 9:
	    temp = read_icp_evaluation_truth_value();
	    break;
	  case 14:
	    temp = read_icp_evaluation_sequence();
	    break;
	  case 15:
	    temp = read_icp_evaluation_structure();
	    break;
	  case 13:
	    temp = Nil;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_2(temp,tag);
}

static Object Qhistory_timestamp;  /* history-timestamp */

/* WRITE-ICP-HISTORY-TIMESTAMP */
Object write_icp_history_timestamp(history_timestamp)
    Object history_timestamp;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,105);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qhistory_timestamp,
		    string_constant_3,Qvalue,T,history_timestamp,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  result_of_write = g2_write_history_timestamp(history_timestamp);
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qhistory_timestamp,string_constant_3,Qvalue,Nil,Nil,
		      Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else
	return g2_write_history_timestamp(history_timestamp);
}

/* READ-ICP-HISTORY-TIMESTAMP */
Object read_icp_history_timestamp()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tag;
    Object result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,106);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qhistory_timestamp,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  tag = read_icp_byte();
	  if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
		  FIXNUM_LE(tag,FIX((SI_Long)127L))))
	      result_of_read = Nil;
	  else
	      switch (INTEGER_TO_CHAR(tag)) {
		case 5:
		  result_of_read = read_icp_fixnum();
		  break;
		case 6:
		  result_of_read = read_icp_managed_double_float();
		  break;
		default:
		  result_of_read = Nil;
		  break;
	      }
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qhistory_timestamp,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	tag = read_icp_byte();
	if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
		FIXNUM_LE(tag,FIX((SI_Long)127L))))
	    return VALUES_1(Nil);
	else
	    switch (INTEGER_TO_CHAR(tag)) {
	      case 5:
		return read_icp_fixnum();
	      case 6:
		return read_icp_managed_double_float();
	      default:
		return VALUES_1(Nil);
	    }
    }
}

/* WRITE-ICP-ADD-ATTRIBUTE-VALUE */
Object write_icp_add_attribute_value(attribute_spec_qm,attribute_value,
	    corresponding_index_of_attribute_value_qm)
    Object attribute_spec_qm, attribute_value;
    Object corresponding_index_of_attribute_value_qm;
{
    x_note_fn_call(158,107);
    write_icp_byte(Add_attribute_value_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    return write_icp_attribute_value(attribute_value,
	    corresponding_index_of_attribute_value_qm);
}

static Object Qpremature_attribute_value;  /* premature-attribute-value */

/* READ-ICP-ADD-ATTRIBUTE-VALUE */
Object read_icp_add_attribute_value()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object attribute_value, value_type, current_subobject_qm;
    Object result;

    x_note_fn_call(158,108);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    result = read_icp_attribute_value();
    MVS_2(result,attribute_value,value_type);
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (current_subobject_qm)
	return g2_add_leaf_to_remote_object(current_subobject_qm,
		attribute_type,attribute_qualifier_qm,
		attribute_name_or_index,attribute_value);
    else
	return record_object_building_problem_on_receiving_side_1(Qpremature_attribute_value,
		attribute_qualifier_qm,attribute_name_or_index,Nil,Nil,Nil,
		Nil);
}

/* WRITE-ICP-ADD-CIRCULAR-ATTRIBUTE */
Object write_icp_add_circular_attribute(attribute_spec_qm,corresponding_index)
    Object attribute_spec_qm, corresponding_index;
{
    x_note_fn_call(158,109);
    write_icp_byte(Add_circular_attribute_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    return write_icp_fixnum(corresponding_index);
}

static Object list_constant_2;     /* # */

static Object Qcircular_object_not_in_list_or_array;  /* circular-object-not-in-list-or-array */

static Object Qcannot_locate_network_registered_object;  /* cannot-locate-network-registered-object */

static Object Qpremature_circular_attribute;  /* premature-circular-attribute */

/* READ-ICP-ADD-CIRCULAR-ATTRIBUTE */
Object read_icp_add_circular_attribute()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object handle, current_subobject_qm, object_from_handle_qm;
    Object result;

    x_note_fn_call(158,110);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    handle = read_icp_fixnum();
    current_subobject_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)8L);
    if (current_subobject_qm) {
	object_from_handle_qm = get_from_icp_port(Current_icp_port,handle,
		Qstandard_icp_object_index_space);
	if (object_from_handle_qm) {
	    if (memq_function(attribute_type,list_constant_2))
		return g2_add_leaf_to_remote_object(current_subobject_qm,
			attribute_type,attribute_qualifier_qm,
			attribute_name_or_index,object_from_handle_qm);
	    else
		return record_object_building_problem_on_receiving_side_1(Qcircular_object_not_in_list_or_array,
			attribute_qualifier_qm,attribute_name_or_index,Nil,
			Nil,Nil,Nil);
	}
	else
	    return record_object_building_problem_on_receiving_side_1(Qcannot_locate_network_registered_object,
		    attribute_qualifier_qm,attribute_name_or_index,Nil,Nil,
		    Nil,Nil);
    }
    else
	return record_object_building_problem_on_receiving_side_1(Qpremature_circular_attribute,
		attribute_qualifier_qm,attribute_name_or_index,Nil,Nil,Nil,
		Nil);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT */
Object write_icp_add_attribute_object(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count;
{
    x_note_fn_call(158,111);
    write_icp_byte(Add_attribute_object_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    return write_icp_fixnum(symbolic_attribute_count);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT */
Object read_icp_add_attribute_object()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count;
    Object result;

    x_note_fn_call(158,112);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    return g2_build_remote_object(attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index,class_name);
}

/* WRITE-ICP-ADD-RESUMABLE-CIRCULARITY */
Object write_icp_add_resumable_circularity(corresponding_index)
    Object corresponding_index;
{
    x_note_fn_call(158,113);
    write_icp_byte(Add_resumable_circularity_for_resumable_object_portion);
    return write_icp_fixnum(corresponding_index);
}

/* READ-ICP-ADD-RESUMABLE-CIRCULARITY */
Object read_icp_add_resumable_circularity()
{
    Object corresponding_index;

    x_note_fn_call(158,114);
    corresponding_index = read_icp_fixnum();
    return g2_add_resumable_circularity(corresponding_index);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT-VECTOR */
Object write_icp_add_attribute_object_vector(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count,
	    resumable_vector_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, resumable_vector_length;
{
    x_note_fn_call(158,115);
    write_icp_byte(Add_attribute_object_vector_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    write_icp_fixnum(symbolic_attribute_count);
    return write_icp_fixnum(resumable_vector_length);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT-VECTOR */
Object read_icp_add_attribute_object_vector()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_vector_length;
    Object result;

    x_note_fn_call(158,116);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    resumable_vector_length = read_icp_fixnum();
    return g2_receive_add_attribute_object_vector(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,resumable_vector_length);
}

static Object Qlong;               /* long */

static Object QFLOAT;              /* |float| */

static Object Qtext;               /* text */

static Object Qtruth;              /* truth */

/* WRITE-ICP-RESUMABLE-SEQUENCE-ELEMENT-TYPE */
Object write_icp_resumable_sequence_element_type(element_type)
    Object element_type;
{
    Object temp;

    x_note_fn_call(158,117);
    if (EQ(element_type,Qinteger))
	temp = Attribute_value_integer_tag;
    else if (EQ(element_type,Qlong))
	temp = Attribute_value_long_tag;
    else if (EQ(element_type,QFLOAT))
	temp = Attribute_value_float_tag;
    else if (EQ(element_type,Qtext))
	temp = Attribute_value_text_tag;
    else if (EQ(element_type,Qtruth))
	temp = Attribute_value_truth_value_tag;
    else if (EQ(element_type,Qsymbol))
	temp = Attribute_value_symbol_tag;
    else
	temp = Unknown_value_vector_element_type_tag;
    write_icp_byte(temp);
    return VALUES_1(Nil);
}

/* READ-ICP-RESUMABLE-SEQUENCE-ELEMENT-TYPE */
Object read_icp_resumable_sequence_element_type()
{
    Object tag, temp;

    x_note_fn_call(158,118);
    tag = read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 5:
	    temp = Qinteger;
	    break;
	  case 16:
	    temp = Qlong;
	    break;
	  case 6:
	    temp = QFLOAT;
	    break;
	  case 8:
	    temp = Qtext;
	    break;
	  case 9:
	    temp = Qtruth;
	    break;
	  case 7:
	    temp = Qsymbol;
	    break;
	  case 11:
	    temp = Nil;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return VALUES_1(temp);
}

/* WRITE-ICP-ADD-ATTRIBUTE-VALUE-VECTOR */
Object write_icp_add_attribute_value_vector(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count,
	    element_type,resumable_vector_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type, resumable_vector_length;
{
    x_note_fn_call(158,119);
    write_icp_byte(Add_attribute_value_vector_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    write_icp_fixnum(symbolic_attribute_count);
    write_icp_resumable_sequence_element_type(element_type);
    return write_icp_fixnum(resumable_vector_length);
}

/* READ-ICP-ADD-ATTRIBUTE-VALUE-VECTOR */
Object read_icp_add_attribute_value_vector()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_vector_length;
    Object result;

    x_note_fn_call(158,120);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    element_type = read_icp_resumable_sequence_element_type();
    resumable_vector_length = read_icp_fixnum();
    return g2_receive_add_attribute_value_vector(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type,resumable_vector_length);
}

/* WRITE-ICP-HISTORY-SPEC */
Object write_icp_history_spec(history_spec)
    Object history_spec;
{
    Object gensymed_symbol, datapoint_count_qm, datapoint_age_qm;
    Object granularity_qm;

    x_note_fn_call(158,121);
    gensymed_symbol = history_spec;
    gensymed_symbol = CDR(gensymed_symbol);
    datapoint_count_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    datapoint_age_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    granularity_qm = CAR(gensymed_symbol);
    if (datapoint_count_qm)
	write_icp_fixnum(datapoint_count_qm);
    else
	write_icp_fixnum(No_history_spec_value);
    if (datapoint_age_qm)
	write_icp_fixnum(datapoint_age_qm);
    else
	write_icp_fixnum(No_history_spec_value);
    if (granularity_qm)
	return write_icp_fixnum(granularity_qm);
    else
	return write_icp_fixnum(No_history_spec_value);
}

/* READ-ICP-HISTORY-SPEC */
Object read_icp_history_spec()
{
    Object datapoint_count, datapoint_age, granularity;

    x_note_fn_call(158,122);
    datapoint_count = read_icp_fixnum();
    datapoint_age = read_icp_fixnum();
    granularity = read_icp_fixnum();
    return VALUES_3(FIXNUM_EQ(No_history_spec_value,datapoint_count) ? Nil 
	    : datapoint_count,FIXNUM_EQ(No_history_spec_value,
	    datapoint_age) ? Nil : datapoint_age,
	    FIXNUM_EQ(No_history_spec_value,granularity) ? Nil : granularity);
}

static Object Qevaluation_quantity_or_nil;  /* evaluation-quantity-or-nil */

/* WRITE-ICP-EVALUATION-QUANTITY-OR-NIL */
Object write_icp_evaluation_quantity_or_nil(evaluation_quantity_or_nil)
    Object evaluation_quantity_or_nil;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,123);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qevaluation_quantity_or_nil,
		    string_constant_3,Qvalue,T,evaluation_quantity_or_nil,
		    Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  if ( !TRUEP(evaluation_quantity_or_nil))
	      result_of_write = write_icp_byte(Attribute_value_null_tag);
	  else if (FIXNUMP(evaluation_quantity_or_nil)) {
	      write_icp_byte(Attribute_value_integer_tag);
	      result_of_write = write_icp_fixnum(evaluation_quantity_or_nil);
	  }
	  else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_or_nil) 
		  != (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) 
		  == (SI_Long)1L) {
	      write_icp_byte(Attribute_value_float_tag);
	      result_of_write = 
		      write_icp_managed_double_float(evaluation_quantity_or_nil);
	  }
	  else if (INLINE_LONG_VECTOR_P(evaluation_quantity_or_nil) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) 
		  == (SI_Long)1L) {
	      write_icp_byte(Attribute_value_long_tag);
	      result_of_write = 
		      write_icp_managed_long(evaluation_quantity_or_nil);
	  }
	  else
	      result_of_write = Qnil;
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qevaluation_quantity_or_nil,string_constant_3,Qvalue,
		      Nil,Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else if ( !TRUEP(evaluation_quantity_or_nil))
	return write_icp_byte(Attribute_value_null_tag);
    else if (FIXNUMP(evaluation_quantity_or_nil)) {
	write_icp_byte(Attribute_value_integer_tag);
	return write_icp_fixnum(evaluation_quantity_or_nil);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_or_nil) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) == 
	    (SI_Long)1L) {
	write_icp_byte(Attribute_value_float_tag);
	return write_icp_managed_double_float(evaluation_quantity_or_nil);
    }
    else if (INLINE_LONG_VECTOR_P(evaluation_quantity_or_nil) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) == 
	    (SI_Long)1L) {
	write_icp_byte(Attribute_value_long_tag);
	return write_icp_managed_long(evaluation_quantity_or_nil);
    }
    else
	return VALUES_1(Qnil);
}

/* READ-ICP-EVALUATION-QUANTITY-OR-NIL */
Object read_icp_evaluation_quantity_or_nil()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tag;
    Object result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,124);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qevaluation_quantity_or_nil,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  tag = read_icp_byte();
	  if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
		  FIXNUM_LE(tag,FIX((SI_Long)127L))))
	      result_of_read = Nil;
	  else
	      switch (INTEGER_TO_CHAR(tag)) {
		case 13:
		  result_of_read = Nil;
		  break;
		case 5:
		  result_of_read = read_icp_fixnum();
		  break;
		case 6:
		  result_of_read = read_icp_managed_double_float();
		  break;
		case 16:
		  result_of_read = read_icp_managed_long();
		  break;
		default:
		  result_of_read = Nil;
		  break;
	      }
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qevaluation_quantity_or_nil,string_constant_3,Qvalue,
		      T,result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	tag = read_icp_byte();
	if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
		FIXNUM_LE(tag,FIX((SI_Long)127L))))
	    return VALUES_1(Nil);
	else
	    switch (INTEGER_TO_CHAR(tag)) {
	      case 13:
		return VALUES_1(Nil);
	      case 5:
		return read_icp_fixnum();
	      case 6:
		return read_icp_managed_double_float();
	      case 16:
		return read_icp_managed_long();
	      default:
		return VALUES_1(Nil);
	    }
    }
}

/* WRITE-ICP-DYNAMIC-HISTORY-INFO */
Object write_icp_dynamic_history_info(dynamic_history_info)
    Object dynamic_history_info;
{
    Object gensymed_symbol, base_time_qm, lowest_ever_qm, highest_ever_qm;
    Object time_at_start_qm;

    x_note_fn_call(158,125);
    gensymed_symbol = dynamic_history_info;
    base_time_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lowest_ever_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    highest_ever_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    time_at_start_qm = CAR(gensymed_symbol);
    write_icp_evaluation_quantity_or_nil(base_time_qm);
    write_icp_evaluation_quantity_or_nil(lowest_ever_qm);
    write_icp_evaluation_quantity_or_nil(highest_ever_qm);
    return write_icp_evaluation_quantity_or_nil(time_at_start_qm);
}

/* READ-ICP-DYNAMIC-HISTORY-INFO */
Object read_icp_dynamic_history_info()
{
    Object base_time_qm, lowest_ever_qm, highest_ever_qm, time_at_start_qm;

    x_note_fn_call(158,126);
    base_time_qm = read_icp_evaluation_quantity_or_nil();
    lowest_ever_qm = read_icp_evaluation_quantity_or_nil();
    highest_ever_qm = read_icp_evaluation_quantity_or_nil();
    time_at_start_qm = read_icp_evaluation_quantity_or_nil();
    return VALUES_4(base_time_qm,lowest_ever_qm,highest_ever_qm,
	    time_at_start_qm);
}

/* WRITE-ICP-ADD-ATTRIBUTE-HISTORY-OBJECT */
Object write_icp_add_attribute_history_object(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count,
	    element_type_qm,resumable_history_length,
	    resumable_history_spec,dynamic_history_info,
	    timestamps_use_float_array_p,values_use_float_array_p)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type_qm, resumable_history_length;
    Object resumable_history_spec, dynamic_history_info;
    Object timestamps_use_float_array_p, values_use_float_array_p;
{
    x_note_fn_call(158,127);
    write_icp_byte(Add_attribute_history_object_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    write_icp_fixnum(symbolic_attribute_count);
    write_icp_resumable_sequence_element_type(element_type_qm);
    write_icp_fixnum(resumable_history_length);
    write_icp_boolean(timestamps_use_float_array_p);
    write_icp_boolean(values_use_float_array_p);
    write_icp_history_spec(resumable_history_spec);
    return write_icp_dynamic_history_info(dynamic_history_info);
}

/* READ-ICP-ADD-ATTRIBUTE-HISTORY-OBJECT */
Object read_icp_add_attribute_history_object()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type_qm;
    Object resumable_history_length, timestamps_use_float_array_p;
    Object values_use_float_array_p, datapoint_count, datapoint_age;
    Object granularity, base_time, lowest_ever_qm, highest_ever_qm;
    Object time_at_start_qm;
    Object result;

    x_note_fn_call(158,128);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    element_type_qm = read_icp_resumable_sequence_element_type();
    resumable_history_length = read_icp_fixnum();
    timestamps_use_float_array_p = read_icp_boolean();
    values_use_float_array_p = read_icp_boolean();
    result = read_icp_history_spec();
    MVS_3(result,datapoint_count,datapoint_age,granularity);
    result = read_icp_dynamic_history_info();
    MVS_4(result,base_time,lowest_ever_qm,highest_ever_qm,time_at_start_qm);
    return g2_receive_add_attribute_history_object(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type_qm,
	    resumable_history_length,timestamps_use_float_array_p,
	    values_use_float_array_p,datapoint_count,datapoint_age,
	    granularity,base_time,lowest_ever_qm,highest_ever_qm,
	    time_at_start_qm);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT-LIST */
Object write_icp_add_attribute_object_list(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count,
	    resumable_list_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, resumable_list_length;
{
    x_note_fn_call(158,129);
    write_icp_byte(Add_attribute_object_list_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    write_icp_fixnum(symbolic_attribute_count);
    return write_icp_fixnum(resumable_list_length);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT-LIST */
Object read_icp_add_attribute_object_list()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_list_length;
    Object result;

    x_note_fn_call(158,130);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    resumable_list_length = read_icp_fixnum();
    return g2_receive_add_attribute_object_list(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,resumable_list_length);
}

/* WRITE-ICP-ADD-ATTRIBUTE-VALUE-LIST */
Object write_icp_add_attribute_value_list(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count,
	    element_type,resumable_list_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type, resumable_list_length;
{
    x_note_fn_call(158,131);
    write_icp_byte(Add_attribute_value_list_for_resumable_object_portion);
    write_icp_attribute_spec_qm(attribute_spec_qm);
    write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    write_icp_fixnum(symbolic_attribute_count);
    write_icp_resumable_sequence_element_type(element_type);
    return write_icp_fixnum(resumable_list_length);
}

/* READ-ICP-ADD-ATTRIBUTE-VALUE-LIST */
Object read_icp_add_attribute_value_list()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_list_length;
    Object result;

    x_note_fn_call(158,132);
    result = read_icp_attribute_spec_qm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = read_icp_possibly_interned_symbol();
    symbolic_attribute_count = read_icp_fixnum();
    element_type = read_icp_resumable_sequence_element_type();
    resumable_list_length = read_icp_fixnum();
    return g2_receive_add_attribute_value_list(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    symbolic_attribute_count,element_type,resumable_list_length);
}

/* WRITE-ICP-ADD-VALUE-VECTOR-RANGE */
Object write_icp_add_value_vector_range(number_of_elements,resumable_node,
	    interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    x_note_fn_call(158,133);
    write_icp_byte(Add_value_vector_range_for_resumable_object_portion);
    return g2_send_add_value_vector_range(number_of_elements,
	    resumable_node,interning_details_qm);
}

/* READ-ICP-ADD-VALUE-VECTOR-RANGE */
Object read_icp_add_value_vector_range()
{
    Object number_of_elements, highest_index;

    x_note_fn_call(158,134);
    number_of_elements = read_icp_fixnum();
    highest_index = read_icp_fixnum();
    return g2_receive_add_value_vector_range(number_of_elements,highest_index);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object write_icp_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    x_note_fn_call(158,135);
    write_icp_byte(Add_homogeneous_value_vector_range_for_resumable_object_portion);
    return g2_send_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm);
}

/* READ-ICP-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object read_icp_add_homogeneous_value_vector_range()
{
    Object number_of_elements, element_type, highest_index;

    x_note_fn_call(158,136);
    number_of_elements = read_icp_fixnum();
    element_type = read_icp_resumable_sequence_element_type();
    highest_index = read_icp_fixnum();
    return g2_receive_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,highest_index);
}

/* WRITE-ICP-ADD-HISTORY-RANGE */
Object write_icp_add_history_range(resumable_node,
	    number_of_cached_elements,cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p,values_use_float_array_p)
    Object resumable_node, number_of_cached_elements;
    Object cached_interning_details_qm, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details_qm;
    Object timestamps_use_float_array_p, values_use_float_array_p;
{
    x_note_fn_call(158,137);
    write_icp_byte(Add_history_range_for_resumable_object_portion);
    write_icp_boolean(timestamps_use_float_array_p);
    write_icp_boolean(values_use_float_array_p);
    write_icp_fixnum(FIXNUM_ADD(number_of_cached_elements,
	    number_of_uncached_elements));
    return g2_transmit_add_history_range(resumable_node,
	    number_of_cached_elements,cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p,values_use_float_array_p);
}

/* READ-ICP-ADD-HISTORY-RANGE */
Object read_icp_add_history_range()
{
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object number_of_elements;

    x_note_fn_call(158,138);
    timestamps_use_float_array_p = read_icp_boolean();
    values_use_float_array_p = read_icp_boolean();
    number_of_elements = read_icp_fixnum();
    return g2_receive_add_history_range(timestamps_use_float_array_p,
	    values_use_float_array_p,number_of_elements);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object write_icp_add_homogeneous_history_range(resumable_node,
	    number_of_cached_elements,element_type,
	    cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p)
    Object resumable_node, number_of_cached_elements, element_type;
    Object cached_interning_details_qm, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details_qm;
    Object timestamps_use_float_array_p;
{
    x_note_fn_call(158,139);
    write_icp_byte(Add_homogeneous_history_range_for_resumable_object_portion);
    write_icp_boolean(timestamps_use_float_array_p);
    write_icp_resumable_sequence_element_type(element_type);
    write_icp_fixnum(FIXNUM_ADD(number_of_cached_elements,
	    number_of_uncached_elements));
    return g2_transmit_add_homogeneous_history_range(resumable_node,
	    element_type,number_of_cached_elements,
	    cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p);
}

/* READ-ICP-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object read_icp_add_homogeneous_history_range()
{
    Object timestamps_use_float_array_p, element_type, number_of_elements;

    x_note_fn_call(158,140);
    timestamps_use_float_array_p = read_icp_boolean();
    element_type = read_icp_resumable_sequence_element_type();
    number_of_elements = read_icp_fixnum();
    return g2_receive_add_homogeneous_history_range(timestamps_use_float_array_p,
	    element_type,number_of_elements);
}

/* WRITE-ICP-ADD-VALUE-LIST-RANGE */
Object write_icp_add_value_list_range(number_of_elements,resumable_node,
	    interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    x_note_fn_call(158,141);
    write_icp_byte(Add_value_list_range_for_resumable_object_portion);
    return g2_send_add_value_list_range(number_of_elements,resumable_node,
	    interning_details_qm);
}

/* READ-ICP-ADD-VALUE-LIST-RANGE */
Object read_icp_add_value_list_range()
{
    Object number_of_elements;

    x_note_fn_call(158,142);
    number_of_elements = read_icp_fixnum();
    return g2_receive_add_value_list_range(number_of_elements);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object write_icp_add_homogeneous_value_list_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    x_note_fn_call(158,143);
    write_icp_byte(Add_homogeneous_value_list_range_for_resumable_object_portion);
    return g2_send_add_homogeneous_value_list_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm);
}

/* READ-ICP-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object read_icp_add_homogeneous_value_list_range()
{
    Object number_of_elements, element_type;

    x_note_fn_call(158,144);
    number_of_elements = read_icp_fixnum();
    element_type = read_icp_resumable_sequence_element_type();
    return g2_receive_add_homogeneous_value_list_range(number_of_elements,
	    element_type);
}

/* WRITE-ICP-ASCEND-TO-PARENT */
Object write_icp_ascend_to_parent(ascension_count)
    Object ascension_count;
{
    x_note_fn_call(158,145);
    write_icp_byte(Ascend_to_parent_for_resumable_object_portion);
    return write_icp_fixnum(ascension_count);
}

/* READ-ICP-ASCEND-TO-PARENT */
Object read_icp_ascend_to_parent()
{
    Object ascension_count;

    x_note_fn_call(158,146);
    ascension_count = read_icp_fixnum();
    return g2_ascend_to_parent(ascension_count);
}

/* WRITE-ICP-SUSPEND-BUILDING-OBJECT */
Object write_icp_suspend_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(158,147);
    write_icp_byte(Suspend_building_object_for_resumable_object_portion);
    return write_icp_fixnum(bandwidth_consumed);
}

static Object Qtelewindows;        /* telewindows */

static Object Qexit_from_resumable_object_portion;  /* exit-from-resumable-object-portion */

/* READ-ICP-SUSPEND-BUILDING-OBJECT */
Object read_icp_suspend_building_object()
{
    Object bandwidth_consumed, current_icp_port, current_icp_socket, temp;
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

    x_note_fn_call(158,148);
    bandwidth_consumed = read_icp_fixnum();
    if (IFIX(bandwidth_consumed) > (SI_Long)0L) {
	current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
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
				    send_icp_update_object_passing_network_resources(bandwidth_consumed,
					    No_resumable_object_index,Nil);
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
    Rpc_throw_tag = Qexit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

/* WRITE-ICP-FINISH-BUILDING-OBJECT */
Object write_icp_finish_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(158,149);
    write_icp_byte(Finish_building_object_for_resumable_object_portion);
    return write_icp_fixnum(bandwidth_consumed);
}

/* READ-ICP-FINISH-BUILDING-OBJECT */
Object read_icp_finish_building_object()
{
    Object bandwidth_consumed;

    x_note_fn_call(158,150);
    bandwidth_consumed = read_icp_fixnum();
    return receive_finish_building_object(bandwidth_consumed);
}

/* WRITE-ICP-ABORT-BUILDING-OBJECT */
Object write_icp_abort_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(158,151);
    write_icp_byte(Abort_building_object_for_resumable_object_portion);
    return write_icp_fixnum(bandwidth_consumed);
}

/* READ-ICP-ABORT-BUILDING-OBJECT */
Object read_icp_abort_building_object()
{
    Object bandwidth_consumed, resumable_object_index;
    Object resumable_instance_node_indices, current_icp_port;
    Object current_icp_socket, temp, disable_resumability;
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

    x_note_fn_call(158,152);
    bandwidth_consumed = read_icp_fixnum();
    resumable_object_index = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)11L);
    resumable_instance_node_indices = 
	    ISVREF(Current_receiving_resumable_object,(SI_Long)12L);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
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
				send_icp_update_object_passing_network_resources(bandwidth_consumed,
					resumable_object_index,
					resumable_instance_node_indices);
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
    reclaim_receiving_resumable_object(Current_receiving_resumable_object);
    Rpc_throw_tag = Qexit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

static Object Qresumable_object_portion;  /* resumable-object-portion */

/* WRITE-ICP-RESUMABLE-OBJECT-PORTION */
Object write_icp_resumable_object_portion(resumable_object_portion)
    Object resumable_object_portion;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,153);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qresumable_object_portion,
		    string_constant_3,Qvalue,T,resumable_object_portion,
		    Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  result_of_write = 
		  write_icp_fixnum(get_icp_object_index_for_resumable_object(resumable_object_portion,
		  Current_icp_port));
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qresumable_object_portion,string_constant_3,Qvalue,
		      Nil,Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else
	return write_icp_fixnum(get_icp_object_index_for_resumable_object(resumable_object_portion,
		Current_icp_port));
}

/* READ-ICP-RESUMABLE-OBJECT-PORTION */
Object read_icp_resumable_object_portion()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,154);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qresumable_object_portion,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  result_of_read = read_icp_fixnum();
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qresumable_object_portion,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else
	return read_icp_fixnum();
}

static Object Qresumable_node_indices;  /* resumable-node-indices */

/* WRITE-ICP-RESUMABLE-NODE-INDICES */
Object write_icp_resumable_node_indices(resumable_node_indices)
    Object resumable_node_indices;
{
    Object tracep, byte_count_before, current_icp_write_trace_level, length_1;
    Object index_1, ab_loop_list_, result_of_write;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,155);
    if (Icp_write_trace_cutoff_level_qm) {
	tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)4L ?
		     T : Nil;
	if (tracep) {
	    emit_icp_write_trace(T,Nil,Nil,Qresumable_node_indices,
		    string_constant_3,Qvalue,T,resumable_node_indices,Nil,Nil);
	    byte_count_before = instantaneous_icp_writer_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_write_trace_level = 
		FIXNUM_ADD1(Current_icp_write_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		0);
	  length_1 = length(resumable_node_indices);
	  write_icp_fixnum(length_1);
	  index_1 = Nil;
	  ab_loop_list_ = resumable_node_indices;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  index_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  write_icp_fixnum(index_1);
	  goto next_loop;
	end_loop:
	  result_of_write = Qnil;
	  if (tracep)
	      emit_icp_write_trace(Nil,byte_count_before,
		      instantaneous_icp_writer_byte_count(),
		      Qresumable_node_indices,string_constant_3,Qvalue,Nil,
		      Nil,Nil,Nil);
	  result = VALUES_1(result_of_write);
	POP_SPECIAL();
	return result;
    }
    else {
	length_1 = length(resumable_node_indices);
	write_icp_fixnum(length_1);
	index_1 = Nil;
	ab_loop_list_ = resumable_node_indices;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	index_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_icp_fixnum(index_1);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* READ-ICP-RESUMABLE-NODE-INDICES */
Object read_icp_resumable_node_indices()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, length_1;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, result_of_read;
    SI_Long count_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(158,156);
    if (Icp_read_trace_cutoff_level_qm) {
	tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	if (tracep);
	else
	    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)4L ? 
		    T : Nil;
	if (tracep) {
	    emit_icp_read_trace(T,Nil,Nil,Qresumable_node_indices,
		    string_constant_3,Qvalue,Nil,Nil,Nil,Nil);
	    byte_count_before = instantaneous_icp_reader_byte_count();
	}
	else
	    byte_count_before = Nil;
	current_icp_read_trace_level = 
		FIXNUM_ADD1(Current_icp_read_trace_level);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		0);
	  length_1 = read_icp_fixnum();
	  count_1 = (SI_Long)1L;
	  ab_loop_bind_ = IFIX(length_1);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if (count_1 > ab_loop_bind_)
	      goto end_loop;
	  ab_loopvar__2 = icp_cons_1(read_icp_fixnum(),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  count_1 = count_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result_of_read = ab_loopvar_;
	  goto end_1;
	  result_of_read = Qnil;
	end_1:;
	  if (tracep)
	      emit_icp_read_trace(Nil,byte_count_before,
		      instantaneous_icp_reader_byte_count(),
		      Qresumable_node_indices,string_constant_3,Qvalue,T,
		      result_of_read,Nil,Nil);
	  result = VALUES_1(result_of_read);
	POP_SPECIAL();
	return result;
    }
    else {
	length_1 = read_icp_fixnum();
	count_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if (count_1 > ab_loop_bind_)
	    goto end_loop_1;
	ab_loopvar__2 = icp_cons_1(read_icp_fixnum(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

static Object Qitem_index_space;   /* item-index-space */

static Object Qg2;                 /* g2 */

static Object Qframe_serial_number;  /* frame-serial-number */

/* RECLAIM-INDEX-FOR-RESUMABLE-OBJECT */
Object reclaim_index_for_resumable_object(index_1,output_port_p)
    Object index_1, output_port_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1, old_entry;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(158,157);
    port = Current_icp_port;
    if (EQ(Qstandard_icp_object_index_space,Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(Qstandard_icp_object_index_space,Qitem_index_space)) {
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
    else if (EQ(Qstandard_icp_object_index_space,Qframe_serial_number))
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

/* RECLAIM-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object reclaim_index_for_resumable_instance_node(index_1,output_port_p)
    Object index_1, output_port_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1, old_entry;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(158,158);
    port = Current_icp_port;
    if (EQ(Qstandard_icp_object_index_space,Qstandard_icp_object_index_space))
	index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(Qstandard_icp_object_index_space,Qitem_index_space)) {
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
    else if (EQ(Qstandard_icp_object_index_space,Qframe_serial_number))
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

/* RECLAIM-INDICES-ASSOCIATED-WITH-RESUMABLE-OBJECT */
Object reclaim_indices_associated_with_resumable_object(resumable_object_index,
	    resumable_instance_node_indices,output_port_p)
    Object resumable_object_index, resumable_instance_node_indices;
    Object output_port_p;
{
    Object index_1, ab_loop_list_;

    x_note_fn_call(158,159);
    if (FIXNUM_NE(resumable_object_index,No_resumable_object_index))
	reclaim_index_for_resumable_object(resumable_object_index,
		output_port_p);
    index_1 = Nil;
    ab_loop_list_ = resumable_instance_node_indices;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    index_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_index_for_resumable_instance_node(index_1,output_port_p);
    goto next_loop;
  end_loop:;
    return reclaim_icp_list_1(resumable_instance_node_indices);
}

/* RECEIVE-FINISH-BUILDING-OBJECT */
Object receive_finish_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    Object resumable_object_index, resumable_instance_node_indices;
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, rpc_arglist_structure_qm;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(158,160);
    resumable_object_index = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)11L);
    resumable_instance_node_indices = 
	    ISVREF(Current_receiving_resumable_object,(SI_Long)12L);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
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
				send_icp_update_object_passing_network_resources(bandwidth_consumed,
					resumable_object_index,
					resumable_instance_node_indices);
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
    reclaim_indices_associated_with_resumable_object(resumable_object_index,
	    resumable_instance_node_indices,Nil);
    rpc_arglist_structure_qm = ISVREF(Current_receiving_resumable_object,
	    (SI_Long)9L);
    if (rpc_arglist_structure_qm)
	g2_maybe_continue_rpc_after_object_building(rpc_arglist_structure_qm);
    else;
    Rpc_throw_tag = Qexit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

static Object Qsend_icp_update_object_passing_network_resources;  /* send-icp-update-object-passing-network-resources */

static Object Qupdate_object_passing_network_resources;  /* update-object-passing-network-resources */

static Object string_constant_5;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qfreed;              /* freed */

static Object string_constant_6;   /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qresumable_object_index;  /* resumable-object-index */

/* SEND-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES */
Object send_icp_update_object_passing_network_resources(freed,
	    resumable_object_index,resumable_node_indices)
    Object freed, resumable_object_index, resumable_node_indices;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,161);
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
		      Qsend_icp_update_object_passing_network_resources;
	  }
	  start_writing_icp_message(FIX((SI_Long)321L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qupdate_object_passing_network_resources,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			emit_icp_write_trace(T,Nil,Nil,Qfreed,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_fixnum(freed);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qfreed,string_constant_6,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_fixnum(freed);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qresumable_object_index,string_constant_6,
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
			      write_icp_fixnum(resumable_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qresumable_object_index,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_fixnum(resumable_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qresumable_node_indices,string_constant_6,
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
			      write_icp_resumable_node_indices(resumable_node_indices);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qresumable_node_indices,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_resumable_node_indices(resumable_node_indices);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qupdate_object_passing_network_resources,
			    string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qfreed,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_fixnum(freed);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qfreed,string_constant_6,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_fixnum(freed);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qresumable_object_index,string_constant_6,
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
		    result_of_write = write_icp_fixnum(resumable_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qresumable_object_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_fixnum(resumable_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qresumable_node_indices,string_constant_6,
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
			    write_icp_resumable_node_indices(resumable_node_indices);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qresumable_node_indices,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_resumable_node_indices(resumable_node_indices);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_update_object_passing_network_resources,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_update_object_passing_network_resources,
			top,Nil);
		goto end_send_icp_update_object_passing_network_resources;
	    }
	}
	freed = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : freed;
	resumable_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : resumable_object_index;
	resumable_node_indices = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : resumable_node_indices;
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
		      Qsend_icp_update_object_passing_network_resources;
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
		      start_writing_icp_message(FIX((SI_Long)321L)))) {
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
			  Qupdate_object_passing_network_resources,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			    goto l3;
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
			emit_icp_write_trace(T,Nil,Nil,Qfreed,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_fixnum(freed))) {
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
				  Qfreed,string_constant_6,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_fixnum(freed))) {
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
				Qresumable_object_index,string_constant_6,
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
			      write_icp_fixnum(resumable_object_index))) {
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
				  Qresumable_object_index,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_fixnum(resumable_object_index))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qresumable_node_indices,string_constant_6,
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
			      write_icp_resumable_node_indices(resumable_node_indices))) 
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
				  Qresumable_node_indices,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_resumable_node_indices(resumable_node_indices))) 
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
			    Qupdate_object_passing_network_resources,
			    string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			  goto l3_1;
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
		      emit_icp_write_trace(T,Nil,Nil,Qfreed,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,write_icp_fixnum(freed))) {
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
				Qfreed,string_constant_6,Qargument,Nil,Nil,
				Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_fixnum(freed))) {
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
			      Qresumable_object_index,string_constant_6,
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
			    write_icp_fixnum(resumable_object_index))) {
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
				Qresumable_object_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_fixnum(resumable_object_index))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qresumable_node_indices,string_constant_6,
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
			    write_icp_resumable_node_indices(resumable_node_indices))) 
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
				Qresumable_node_indices,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_resumable_node_indices(resumable_node_indices))) 
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
	      resumable_icp_push(resumable_node_indices);
	      resumable_icp_push(resumable_object_index);
	      resumable_icp_push(freed);
	      resumable_icp_push(Qsend_icp_update_object_passing_network_resources);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_update_object_passing_network_resources;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_update_object_passing_network_resources:
    return result;
}

/* HANDLE-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES--BODY */
Object handle_icp_update_object_passing_network_resources__body(freed,
	    resumable_object_index,resumable_node_indices)
    Object freed, resumable_object_index, resumable_node_indices;
{
    Object current_icp_port, svref_arg_1, incff_1_arg, svref_new_value;
    Declare_special(1);

    x_note_fn_call(158,162);
    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    0);
      reclaim_indices_associated_with_resumable_object(resumable_object_index,
	      resumable_node_indices,T);
    POP_SPECIAL();
    svref_arg_1 = Current_icp_socket;
    incff_1_arg = freed;
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,(SI_Long)30L),incff_1_arg);
    SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
    g2_resume_clogged_resumable_object_tasks();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_update_object_passing_network_resources;  /* handle-icp-update-object-passing-network-resources */

/* HANDLE-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES */
Object handle_icp_update_object_passing_network_resources()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, freed, resumable_object_index;
    Object resumable_node_indices, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,163);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qupdate_object_passing_network_resources,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		      emit_icp_read_trace(T,Nil,Nil,Qfreed,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_fixnum();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qfreed,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    freed = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  freed = read_icp_fixnum();
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
			      Qresumable_object_index,string_constant_6,
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
		    result_of_read = read_icp_fixnum();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_object_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    resumable_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  resumable_object_index = read_icp_fixnum();
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
			      Qresumable_node_indices,string_constant_6,
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
		    result_of_read = read_icp_resumable_node_indices();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_node_indices,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    resumable_node_indices = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  resumable_node_indices = read_icp_resumable_node_indices();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_update_object_passing_network_resources__body(freed,
			resumable_object_index,resumable_node_indices);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_object_passing_network_resources,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qfreed,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_fixnum();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qfreed,
			      string_constant_6,Qargument,T,result_of_read,
			      Nil,Nil);
		  freed = result_of_read;
		POP_SPECIAL();
	    }
	    else
		freed = read_icp_fixnum();
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
		    emit_icp_read_trace(T,Nil,Nil,Qresumable_object_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_fixnum();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_object_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		resumable_object_index = read_icp_fixnum();
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
		    emit_icp_read_trace(T,Nil,Nil,Qresumable_node_indices,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_resumable_node_indices();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_node_indices,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_node_indices = result_of_read;
		POP_SPECIAL();
	    }
	    else
		resumable_node_indices = read_icp_resumable_node_indices();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_update_object_passing_network_resources__body(freed,
		      resumable_object_index,resumable_node_indices);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_update_object_passing_network_resources,
			top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_update_object_passing_network_resources,
			top,Nil);
		goto end_handle_icp_update_object_passing_network_resources;
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
			Qupdate_object_passing_network_resources,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		  freed = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qfreed,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_fixnum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_object_passing_network_resources;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qfreed,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    freed = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  freed = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  resumable_object_index = resumable_icp_pop();
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
			      Qresumable_object_index,string_constant_6,
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
		    value = read_icp_fixnum();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(freed);
			resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_object_passing_network_resources;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_object_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    resumable_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(freed);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  resumable_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  resumable_node_indices = resumable_icp_pop();
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
			      Qresumable_node_indices,string_constant_6,
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
		    value = read_icp_resumable_node_indices();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(resumable_object_index);
			resumable_icp_push(freed);
			resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_object_passing_network_resources;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_node_indices,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    resumable_node_indices = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_resumable_node_indices();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(resumable_object_index);
		      resumable_icp_push(freed);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  resumable_node_indices = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_update_object_passing_network_resources__body(freed,
			resumable_object_index,resumable_node_indices);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_object_passing_network_resources,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		freed = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qfreed,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qfreed,
			      string_constant_6,Qargument,T,result_of_read,
			      Nil,Nil);
		  freed = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_object_passing_network_resources;
		}
		freed = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		resumable_object_index = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qresumable_object_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_fixnum();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(freed);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_object_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_fixnum();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(freed);
		    resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_object_passing_network_resources;
		}
		resumable_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		resumable_node_indices = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qresumable_node_indices,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_resumable_node_indices();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(resumable_object_index);
		      resumable_icp_push(freed);
		      resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_object_passing_network_resources;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_node_indices,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_node_indices = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_resumable_node_indices();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(resumable_object_index);
		    resumable_icp_push(freed);
		    resumable_icp_push(Qhandle_icp_update_object_passing_network_resources);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_object_passing_network_resources;
		}
		resumable_node_indices = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_update_object_passing_network_resources__body(freed,
		      resumable_object_index,resumable_node_indices);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_update_object_passing_network_resources:
    return result;
}

static Object Qtoplevel_object_has_been_deleted_on_receiving_side;  /* toplevel-object-has-been-deleted-on-receiving-side */

static Object Qrpc_arg_list;       /* rpc-arg-list */

/* BODY-OF-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object body_of_continue_building_resumable_object(resumable_object_portion)
    Object resumable_object_portion;
{
    Object resumable_object_qm, current_receiving_resumable_object;
    Object do_not_initialize_g2_array_elements_p, toplevel_object_qm;
    Object rpc_throw_tag, gsi_reclaim_list_level, icp_tag;
    Declare_special(4);
    Object result;

    x_note_fn_call(158,164);
    resumable_object_qm = get_from_icp_port(Current_icp_port,
	    resumable_object_portion,Qstandard_icp_object_index_space);
    if (resumable_object_qm) {
	current_receiving_resumable_object = resumable_object_qm;
	do_not_initialize_g2_array_elements_p = T;
	toplevel_object_qm = ISVREF(resumable_object_qm,(SI_Long)7L);
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_initialize_g2_array_elements_p,Qdo_not_initialize_g2_array_elements_p,do_not_initialize_g2_array_elements_p,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_receiving_resumable_object,Qcurrent_receiving_resumable_object,current_receiving_resumable_object,
		  2);
	    if (toplevel_object_qm && 
		    g2_resumable_object_reprocessed_p(toplevel_object_qm,
		    resumable_object_qm))
		record_object_building_problem_on_receiving_side_1(Qtoplevel_object_has_been_deleted_on_receiving_side,
			Nil,Nil,Nil,Nil,Nil,Nil);
	    rpc_throw_tag = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Rpc_throw_tag,Qrpc_throw_tag,rpc_throw_tag,
		    1);
	    next_loop:
	      gsi_reclaim_list_level = Qrpc_arg_list;
	      icp_tag = read_icp_byte();
	      PUSH_SPECIAL_WITH_SYMBOL(Gsi_reclaim_list_level,Qgsi_reclaim_list_level,gsi_reclaim_list_level,
		      0);
		if (! !(FIXNUMP(icp_tag) && FIXNUM_LE(FIX((SI_Long)-128L),
			icp_tag) && FIXNUM_LE(icp_tag,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(icp_tag)) {
		      case 13:
			read_icp_abort_building_object();
			break;
		      case 12:
			read_icp_finish_building_object();
			break;
		      case 11:
			read_icp_suspend_building_object();
			break;
		      case 10:
			read_icp_ascend_to_parent();
			break;
		      case 15:
			read_icp_add_homogeneous_value_list_range();
			break;
		      case 9:
			read_icp_add_value_list_range();
			break;
		      case 19:
			read_icp_add_homogeneous_history_range();
			break;
		      case 18:
			read_icp_add_history_range();
			break;
		      case 14:
			read_icp_add_homogeneous_value_vector_range();
			break;
		      case 8:
			read_icp_add_value_vector_range();
			break;
		      case 7:
			read_icp_add_attribute_value_list();
			break;
		      case 6:
			read_icp_add_attribute_object_list();
			break;
		      case 17:
			read_icp_add_attribute_history_object();
			break;
		      case 5:
			read_icp_add_attribute_value_vector();
			break;
		      case 4:
			read_icp_add_attribute_object_vector();
			break;
		      case 16:
			read_icp_add_resumable_circularity();
			break;
		      case 3:
			read_icp_add_attribute_object();
			break;
		      case 2:
			read_icp_add_circular_attribute();
			break;
		      case 1:
			read_icp_add_attribute_value();
			break;
		      default:
			break;
		    }
	      POP_SPECIAL();
	      if (Rpc_throw_tag) {
		  result = VALUES_1(Nil);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      result = VALUES_1(Qnil);
	    end_1:;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qsend_icp_continue_building_resumable_object;  /* send-icp-continue-building-resumable-object */

static Object Qcontinue_building_resumable_object;  /* continue-building-resumable-object */

/* SEND-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object send_icp_continue_building_resumable_object(resumable_object_portion)
    Object resumable_object_portion;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,165);
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
		      Qsend_icp_continue_building_resumable_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)320L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qcontinue_building_resumable_object,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qresumable_object_portion,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_resumable_object_portion(resumable_object_portion);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qresumable_object_portion,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_resumable_object_portion(resumable_object_portion);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qcontinue_building_resumable_object,
			    string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qresumable_object_portion,
			  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_resumable_object_portion(resumable_object_portion);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qresumable_object_portion,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_resumable_object_portion(resumable_object_portion);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_continue_building_resumable_object,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_continue_building_resumable_object,top,Nil);
		goto end_send_icp_continue_building_resumable_object;
	    }
	}
	resumable_object_portion = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : resumable_object_portion;
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
		      Qsend_icp_continue_building_resumable_object;
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
		      start_writing_icp_message(FIX((SI_Long)320L)))) {
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
			  Qcontinue_building_resumable_object,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qresumable_object_portion,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_resumable_object_portion(resumable_object_portion))) 
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
				  Qresumable_object_portion,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_resumable_object_portion(resumable_object_portion))) 
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
			    Qcontinue_building_resumable_object,
			    string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
		  emit_icp_write_trace(T,Nil,Nil,Qresumable_object_portion,
			  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_resumable_object_portion(resumable_object_portion))) 
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
			    Qresumable_object_portion,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_resumable_object_portion(resumable_object_portion))) 
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
	      resumable_icp_push(resumable_object_portion);
	      resumable_icp_push(Qsend_icp_continue_building_resumable_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_continue_building_resumable_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_continue_building_resumable_object:
    return result;
}

/* HANDLE-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT--BODY */
Object handle_icp_continue_building_resumable_object__body(resumable_object_portion)
    Object resumable_object_portion;
{
    x_note_fn_call(158,166);
    body_of_continue_building_resumable_object(resumable_object_portion);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_continue_building_resumable_object;  /* handle-icp-continue-building-resumable-object */

/* HANDLE-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object handle_icp_continue_building_resumable_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, resumable_object_portion;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,167);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qcontinue_building_resumable_object,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
			      Qresumable_object_portion,string_constant_6,
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
		    result_of_read = read_icp_resumable_object_portion();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_object_portion,
				string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    resumable_object_portion = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  resumable_object_portion = 
			  read_icp_resumable_object_portion();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qcontinue_building_resumable_object,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
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
			    Qresumable_object_portion,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_resumable_object_portion();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_object_portion,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_object_portion = result_of_read;
		POP_SPECIAL();
	    }
	    else
		resumable_object_portion = read_icp_resumable_object_portion();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_continue_building_resumable_object,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_continue_building_resumable_object,top,
			Nil);
		goto end_handle_icp_continue_building_resumable_object;
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
			Qcontinue_building_resumable_object,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		  resumable_object_portion = resumable_icp_pop();
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
			      Qresumable_object_portion,string_constant_6,
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
		    value = read_icp_resumable_object_portion();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_continue_building_resumable_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_continue_building_resumable_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qresumable_object_portion,
				string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    resumable_object_portion = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_resumable_object_portion();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_continue_building_resumable_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_continue_building_resumable_object;
		  }
		  resumable_object_portion = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qcontinue_building_resumable_object,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		resumable_object_portion = resumable_icp_pop();
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
			    Qresumable_object_portion,string_constant_6,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_resumable_object_portion();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_continue_building_resumable_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_continue_building_resumable_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qresumable_object_portion,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  resumable_object_portion = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_resumable_object_portion();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_continue_building_resumable_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_continue_building_resumable_object;
		}
		resumable_object_portion = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_continue_building_resumable_object:
    return result;
}

/* GSI-RECORD-RPC-NAME-IN-ALL-RECEIVING-RESUMABLE-OBJECTS */
Object gsi_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
	    item)
    Object remote_procedure_name, item;
{
    Object my_item_qm, svref_new_value;

    x_note_fn_call(158,168);
    my_item_qm = Nil;
    my_item_qm = item;
  next_loop:
    if ( !TRUEP(my_item_qm))
	goto end_loop;
    svref_new_value = ISVREF(remote_procedure_name,(SI_Long)1L);
    SVREF(my_item_qm,FIX((SI_Long)1L)) = svref_new_value;
    my_item_qm = ISVREF(my_item_qm,(SI_Long)3L);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* G2-RECORD-RPC-NAME-IN-ALL-RECEIVING-RESUMABLE-OBJECTS */
Object g2_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
	    rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object argument, ab_loop_list_, typical_resumable_object_qm;
    Object initial_resumable_var, typical_resumable_object_qm_1;
    Object svref_new_value;

    x_note_fn_call(158,169);
    argument = Nil;
    ab_loop_list_ = rpc_argument_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	typical_resumable_object_qm = argument;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    typical_resumable_object_qm = Qnil;
  end_1:;
    if (typical_resumable_object_qm) {
	initial_resumable_var = ISVREF(typical_resumable_object_qm,
		(SI_Long)3L);
	typical_resumable_object_qm_1 = initial_resumable_var;
      next_loop_1:
	if ( !TRUEP(typical_resumable_object_qm_1))
	    goto end_loop_1;
	svref_new_value = ISVREF(remote_procedure_name,(SI_Long)1L);
	SVREF(typical_resumable_object_qm_1,FIX((SI_Long)1L)) = 
		svref_new_value;
	typical_resumable_object_qm_1 = 
		ISVREF(typical_resumable_object_qm_1,(SI_Long)3L);
	goto next_loop_1;
      end_loop_1:;
	initial_resumable_var = ISVREF(typical_resumable_object_qm,
		(SI_Long)4L);
	typical_resumable_object_qm_1 = initial_resumable_var;
      next_loop_2:
	if ( !TRUEP(typical_resumable_object_qm_1))
	    goto end_loop_2;
	svref_new_value = ISVREF(remote_procedure_name,(SI_Long)1L);
	SVREF(typical_resumable_object_qm_1,FIX((SI_Long)1L)) = 
		svref_new_value;
	typical_resumable_object_qm_1 = 
		ISVREF(typical_resumable_object_qm_1,(SI_Long)4L);
	goto next_loop_2;
      end_loop_2:;
	svref_new_value = ISVREF(remote_procedure_name,(SI_Long)1L);
	SVREF(typical_resumable_object_qm,FIX((SI_Long)1L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

/* TWRITE-GSI-RPC-BACKTRACE-INFO */
Object twrite_gsi_rpc_backtrace_info()
{
    Object temp, index_of_top_of_backtrace_stack_new_value;

    x_note_fn_call(158,170);
    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)7L));
    if (IFIX(Index_of_top_of_backtrace_stack) < (SI_Long)0L)
	temp = Nil;
    else {
	temp = ISVREF(Backtrace_stack_for_internal_error,
		IFIX(Index_of_top_of_backtrace_stack));
	index_of_top_of_backtrace_stack_new_value = 
		FIXNUM_SUB1(Index_of_top_of_backtrace_stack);
	Index_of_top_of_backtrace_stack = 
		index_of_top_of_backtrace_stack_new_value;
    }
    twrite(temp);
    return VALUES_1(Nil);
}

static Object Qsend_icp_rpc_start;  /* send-icp-rpc-start */

static Object Qrpc_start;          /* rpc-start */

static Object Qremote_procedure_name;  /* remote-procedure-name */

static Object string_constant_7;   /* "[object arg]" */

/* SEND-ICP-RPC-START */
Object send_icp_rpc_start(remote_procedure_name,rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,171);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_start;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  start_writing_icp_message(FIX((SI_Long)230L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_start,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
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
			      write_icp_corresponding_object_index(remote_procedure_name);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_name,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(remote_procedure_name);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(rpc_argument_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qrpc_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_rpc_argument_list(rpc_argument_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_start,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
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
			    write_icp_corresponding_object_index(remote_procedure_name);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_name,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(remote_procedure_name);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(rpc_argument_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_rpc_argument_list(rpc_argument_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_start,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_rpc_start,top,Nil);
		goto end_send_icp_rpc_start;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_name;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : rpc_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_start;
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
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)230L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_start,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
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
			      write_icp_corresponding_object_index(remote_procedure_name))) 
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
				  Qremote_procedure_name,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(remote_procedure_name))) 
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
			emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(rpc_argument_list))) 
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
				  Qrpc_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_rpc_argument_list(rpc_argument_list))) {
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
			    Qrpc_start,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
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
			    write_icp_corresponding_object_index(remote_procedure_name))) 
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
				Qremote_procedure_name,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(remote_procedure_name))) 
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
		      emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(rpc_argument_list))) {
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
				Qrpc_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_rpc_argument_list(rpc_argument_list))) {
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
	      resumable_icp_push(rpc_argument_list);
	      resumable_icp_push(remote_procedure_name);
	      resumable_icp_push(Qsend_icp_rpc_start);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_start;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_start:
    return result;
}

static Object Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-name-g2-struct */

static Object Qstart;              /* start */

/* HANDLE-ICP-RPC-START--BODY */
Object handle_icp_rpc_start__body(remote_procedure_name,rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object remote_procedure_name_symbol, rpc_argument_list_error, argument;
    Object ab_loop_list_, object_argument_qm, rpc_arglist_structure, temp;
    Object temp_1;
    Declare_special(1);

    x_note_fn_call(158,172);
    if ( !(SIMPLE_VECTOR_P(remote_procedure_name) && 
	    EQ(ISVREF(remote_procedure_name,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct)))
	reclaim_unprocessed_rpc_argument_list(2,rpc_argument_list,
		frame_serial_number_0());
    else {
	remote_procedure_name_symbol = ISVREF(remote_procedure_name,
		(SI_Long)1L);
	rpc_argument_list_error = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Rpc_argument_list_error,Qrpc_argument_list_error,rpc_argument_list_error,
		0);
	  argument = Nil;
	  ab_loop_list_ = rpc_argument_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  argument = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
		  Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		      {
	      object_argument_qm = argument;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  object_argument_qm = Nil;
	  goto end_1;
	  object_argument_qm = Qnil;
	end_1:;
	  if (object_argument_qm) {
	      rpc_arglist_structure = ISVREF(object_argument_qm,(SI_Long)9L);
	      if (plausible_remote_method_call_p(remote_procedure_name_symbol,
		      rpc_argument_list) || 
		      check_that_remote_procedure_can_be_started_or_called(Current_icp_socket,
		      remote_procedure_name_symbol,rpc_argument_list,Nil)) {
		  SVREF(rpc_arglist_structure,FIX((SI_Long)3L)) = 
			  remote_procedure_name;
		  SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qstart;
		  g2_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
			  rpc_argument_list);
	      }
	  }
	  else {
	      temp = Current_icp_socket;
	      temp_1 = frame_serial_number_0();
	      receive_start_or_call_remote_procedure(temp,
		      remote_procedure_name_symbol,icp_cons_1(temp_1,
		      icp_cons_1(Nil,rpc_argument_list)),Nil);
	  }
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_start;  /* handle-icp-rpc-start */

/* HANDLE-ICP-RPC-START */
Object handle_icp_rpc_start()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object remote_procedure_name, rpc_argument_list, abort_for_icp_catcher_qm;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,173);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_start,string_constant_5,
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_procedure_name = result_of_read;
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
		      remote_procedure_name = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name = Nil;
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
		      emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_rpc_argument_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    rpc_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  rpc_argument_list = read_icp_rpc_argument_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_start__body(remote_procedure_name,
			rpc_argument_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_start,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_procedure_name = result_of_read;
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
		    remote_procedure_name = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name = Nil;
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
		    emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_rpc_argument_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qrpc_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  rpc_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		rpc_argument_list = read_icp_rpc_argument_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_start__body(remote_procedure_name,
		      rpc_argument_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_start,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_rpc_start,top,Nil);
		goto end_handle_icp_rpc_start;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_start,string_constant_5,
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
		  remote_procedure_name = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_rpc_start);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_start;
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
				Qremote_procedure_name,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_procedure_name = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_rpc_start);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_start;
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
		      remote_procedure_name = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  rpc_argument_list = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_rpc_argument_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(remote_procedure_name);
			resumable_icp_push(Qhandle_icp_rpc_start);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_start;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    rpc_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_name);
		      resumable_icp_push(Qhandle_icp_rpc_start);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_start;
		  }
		  rpc_argument_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_start__body(remote_procedure_name,
			rpc_argument_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_start,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_name = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_rpc_start);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_start;
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
			      Qremote_procedure_name,string_constant_7,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_procedure_name = result_of_read;
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
			resumable_icp_push(Qhandle_icp_rpc_start);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_start;
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
		    remote_procedure_name = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		rpc_argument_list = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_name);
		      resumable_icp_push(Qhandle_icp_rpc_start);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_start;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qrpc_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  rpc_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_rpc_argument_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(remote_procedure_name);
		    resumable_icp_push(Qhandle_icp_rpc_start);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_start;
		}
		rpc_argument_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_start__body(remote_procedure_name,
		      rpc_argument_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_start:
    return result;
}

static Object Qsend_icp_rpc_call;  /* send-icp-rpc-call */

static Object Qrpc_call;           /* rpc-call */

static Object Qremote_procedure_identifier;  /* remote-procedure-identifier */

/* SEND-ICP-RPC-CALL */
Object send_icp_rpc_call(remote_procedure_name,remote_procedure_identifier,
	    rpc_argument_list)
    Object remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,174);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_call;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  temp_1 = 
		  getfq_function_no_default(ISVREF(remote_procedure_identifier,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier);
	  remote_procedure_identifier = temp_1;
	  start_writing_icp_message(FIX((SI_Long)231L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_call,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
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
			      write_icp_corresponding_object_index(remote_procedure_name);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_name,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(remote_procedure_name);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qremote_procedure_identifier,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(remote_procedure_identifier);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_procedure_identifier,
				  string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(remote_procedure_identifier);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(rpc_argument_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qrpc_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_rpc_argument_list(rpc_argument_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_call,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
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
			    write_icp_corresponding_object_index(remote_procedure_name);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_name,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(remote_procedure_name);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(remote_procedure_identifier);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_procedure_identifier,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(remote_procedure_identifier);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(rpc_argument_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_rpc_argument_list(rpc_argument_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_call,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_rpc_call,top,Nil);
		goto end_send_icp_rpc_call;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_name;
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_procedure_identifier;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : rpc_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_call;
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
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(remote_procedure_identifier,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      remote_procedure_identifier = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_identifier = value_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)231L)))) {
	      resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l4:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_call,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
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
			      write_icp_corresponding_object_index(remote_procedure_name))) 
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
				  Qremote_procedure_name,string_constant_7,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(remote_procedure_name))) 
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
				Qremote_procedure_identifier,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(remote_procedure_identifier))) 
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
				  Qremote_procedure_identifier,
				  string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(remote_procedure_identifier))) 
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
			emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(rpc_argument_list))) 
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
				  Qrpc_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_rpc_argument_list(rpc_argument_list))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_call,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
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
			    write_icp_corresponding_object_index(remote_procedure_name))) 
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
				Qremote_procedure_name,string_constant_7,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(remote_procedure_name))) 
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
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(remote_procedure_identifier))) 
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
				Qremote_procedure_identifier,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(remote_procedure_identifier))) 
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
		      emit_icp_write_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(rpc_argument_list))) {
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
				Qrpc_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_rpc_argument_list(rpc_argument_list))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(rpc_argument_list);
	      resumable_icp_push(remote_procedure_identifier);
	      resumable_icp_push(remote_procedure_name);
	      resumable_icp_push(Qsend_icp_rpc_call);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_call;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_call:
    return result;
}

static Object Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-identifier-g2-struct */

static Object Qcall;               /* call */

/* HANDLE-ICP-RPC-CALL--BODY */
Object handle_icp_rpc_call__body(remote_procedure_name,
	    remote_procedure_identifier,rpc_argument_list)
    Object remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object remote_procedure_name_symbol, rpc_argument_list_error, argument;
    Object ab_loop_list_, object_argument_qm, rpc_arglist_structure, arg;
    Object icp_push_modify_macro_arg, car_1, cdr_1, svref_new_value, temp;
    Object temp_1;
    Declare_special(1);

    x_note_fn_call(158,175);
    if (SIMPLE_VECTOR_P(remote_procedure_identifier) && 
	    EQ(ISVREF(remote_procedure_identifier,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct) 
	    && SIMPLE_VECTOR_P(remote_procedure_name) && 
	    EQ(ISVREF(remote_procedure_name,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct)) {
	remote_procedure_name_symbol = ISVREF(remote_procedure_name,
		(SI_Long)1L);
	rpc_argument_list_error = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Rpc_argument_list_error,Qrpc_argument_list_error,rpc_argument_list_error,
		0);
	  argument = Nil;
	  ab_loop_list_ = rpc_argument_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  argument = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
		  Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		      {
	      object_argument_qm = argument;
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  object_argument_qm = Nil;
	  goto end_1;
	  object_argument_qm = Qnil;
	end_1:;
	  if (object_argument_qm) {
	      rpc_arglist_structure = ISVREF(object_argument_qm,(SI_Long)9L);
	      if (plausible_remote_method_call_p(remote_procedure_name_symbol,
		      rpc_argument_list) || 
		      check_that_remote_procedure_can_be_started_or_called(Current_icp_socket,
		      remote_procedure_name_symbol,rpc_argument_list,
		      remote_procedure_identifier)) {
		  arg = Nil;
		  ab_loop_list_ = rpc_argument_list;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  arg = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (SIMPLE_VECTOR_P(arg) && EQ(ISVREF(arg,(SI_Long)0L),
			  Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct) 
			  &&  !TRUEP(ISVREF(arg,(SI_Long)2L))) {
		      icp_push_modify_macro_arg = arg;
		      car_1 = icp_push_modify_macro_arg;
		      cdr_1 = ISVREF(remote_procedure_identifier,(SI_Long)5L);
		      svref_new_value = icp_cons_1(car_1,cdr_1);
		      SVREF(remote_procedure_identifier,FIX((SI_Long)5L)) 
			      = svref_new_value;
		      SVREF(arg,FIX((SI_Long)5L)) = 
			      remote_procedure_identifier;
		  }
		  goto next_loop_1;
		end_loop_1:;
		  SVREF(rpc_arglist_structure,FIX((SI_Long)3L)) = 
			  remote_procedure_name;
		  SVREF(rpc_arglist_structure,FIX((SI_Long)4L)) = 
			  remote_procedure_identifier;
		  SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qcall;
		  g2_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
			  rpc_argument_list);
	      }
	  }
	  else {
	      temp = Current_icp_socket;
	      temp_1 = frame_serial_number_0();
	      receive_start_or_call_remote_procedure(temp,
		      remote_procedure_name_symbol,icp_cons_1(temp_1,
		      icp_cons_1(Nil,rpc_argument_list)),
		      remote_procedure_identifier);
	  }
	POP_SPECIAL();
    }
    else
	reclaim_unprocessed_rpc_argument_list(2,rpc_argument_list,
		frame_serial_number_0());
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_call;  /* handle-icp-rpc-call */

/* HANDLE-ICP-RPC-CALL */
Object handle_icp_rpc_call()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,176);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_call,string_constant_5,
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_name,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_procedure_name = result_of_read;
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
		      remote_procedure_name = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name = Nil;
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
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
				Qremote_procedure_identifier,
				string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_identifier = result_of_read;
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
		      remote_procedure_identifier = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_identifier = Nil;
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
		      emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_rpc_argument_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    rpc_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  rpc_argument_list = read_icp_rpc_argument_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_call__body(remote_procedure_name,
			remote_procedure_identifier,rpc_argument_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_call,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      Qremote_procedure_name,string_constant_7,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_procedure_name = result_of_read;
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
		    remote_procedure_name = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name = Nil;
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
			    Qremote_procedure_identifier,string_constant_7,
			    Qargument,Nil,Nil,Nil,Nil);
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
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_identifier = result_of_read;
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
		    remote_procedure_identifier = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_identifier = Nil;
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
		    emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_rpc_argument_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qrpc_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  rpc_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		rpc_argument_list = read_icp_rpc_argument_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_call__body(remote_procedure_name,
		      remote_procedure_identifier,rpc_argument_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_call,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_rpc_call,top,Nil);
		goto end_handle_icp_rpc_call;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_call,string_constant_5,
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
		  remote_procedure_name = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_rpc_call);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_call;
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
				Qremote_procedure_name,string_constant_7,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_procedure_name = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_rpc_call);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_call;
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
		      remote_procedure_name = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_name = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  remote_procedure_identifier = resumable_icp_pop();
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
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(remote_procedure_name);
			    resumable_icp_push(Qhandle_icp_rpc_call);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_call;
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
				Qremote_procedure_identifier,
				string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    remote_procedure_identifier = result_of_read;
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
			  resumable_icp_push(remote_procedure_name);
			  resumable_icp_push(Qhandle_icp_rpc_call);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_call;
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
		      remote_procedure_identifier = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      remote_procedure_identifier = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  rpc_argument_list = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_rpc_argument_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(remote_procedure_identifier);
			resumable_icp_push(remote_procedure_name);
			resumable_icp_push(Qhandle_icp_rpc_call);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_call;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qrpc_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    rpc_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_identifier);
		      resumable_icp_push(remote_procedure_name);
		      resumable_icp_push(Qhandle_icp_rpc_call);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_call;
		  }
		  rpc_argument_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_call__body(remote_procedure_name,
			remote_procedure_identifier,rpc_argument_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_call,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_name = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_procedure_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_rpc_call);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_call;
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
			      Qremote_procedure_name,string_constant_7,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_procedure_name = result_of_read;
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
			resumable_icp_push(Qhandle_icp_rpc_call);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_call;
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
		    remote_procedure_name = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_name = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_procedure_identifier = resumable_icp_pop();
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
			    Qremote_procedure_identifier,string_constant_7,
			    Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(remote_procedure_name);
			  resumable_icp_push(Qhandle_icp_rpc_call);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_call;
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
			      Qremote_procedure_identifier,
			      string_constant_7,Qargument,T,result_of_read,
			      Nil,Nil);
		  remote_procedure_identifier = result_of_read;
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
			resumable_icp_push(remote_procedure_name);
			resumable_icp_push(Qhandle_icp_rpc_call);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_call;
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
		    remote_procedure_identifier = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    remote_procedure_identifier = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		rpc_argument_list = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qrpc_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_procedure_identifier);
		      resumable_icp_push(remote_procedure_name);
		      resumable_icp_push(Qhandle_icp_rpc_call);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_call;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qrpc_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  rpc_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_rpc_argument_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(remote_procedure_identifier);
		    resumable_icp_push(remote_procedure_name);
		    resumable_icp_push(Qhandle_icp_rpc_call);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_call;
		}
		rpc_argument_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_call__body(remote_procedure_name,
		      remote_procedure_identifier,rpc_argument_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_call:
    return result;
}

static Object Qsend_icp_rpc_return_values;  /* send-icp-rpc-return-values */

static Object Qrpc_return_values;  /* rpc-return-values */

static Object Qcalling_procedure_index;  /* calling-procedure-index */

static Object Qreturn_values_list;  /* return-values-list */

/* SEND-ICP-RPC-RETURN-VALUES */
Object send_icp_rpc_return_values(calling_procedure_index,return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,177);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_return_values;
	  }
	  start_writing_icp_message(FIX((SI_Long)237L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_return_values,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qcalling_procedure_index,string_constant_6,
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
			      write_icp_unsigned_integer(calling_procedure_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcalling_procedure_index,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(calling_procedure_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qreturn_values_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(return_values_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qreturn_values_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_rpc_argument_list(return_values_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_return_values,string_constant_5,Qmessage,
			    Nil,Nil,Nil,Nil);
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
			      Qcalling_procedure_index,string_constant_6,
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
			    write_icp_unsigned_integer(calling_procedure_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcalling_procedure_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(calling_procedure_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qreturn_values_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(return_values_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qreturn_values_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_rpc_argument_list(return_values_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_return_values,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_rpc_return_values,top,Nil);
		goto end_send_icp_rpc_return_values;
	    }
	}
	calling_procedure_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : calling_procedure_index;
	return_values_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : return_values_list;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_return_values;
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
		      start_writing_icp_message(FIX((SI_Long)237L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_return_values,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qcalling_procedure_index,string_constant_6,
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
			      write_icp_unsigned_integer(calling_procedure_index))) 
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
				  Qcalling_procedure_index,
				  string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(calling_procedure_index))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qreturn_values_list,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_rpc_argument_list(return_values_list))) 
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
				  Qreturn_values_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_rpc_argument_list(return_values_list))) {
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
			    Qrpc_return_values,string_constant_5,Qmessage,
			    Nil,Nil,Nil,Nil);
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
			      Qcalling_procedure_index,string_constant_6,
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
			    write_icp_unsigned_integer(calling_procedure_index))) 
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
				Qcalling_procedure_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(calling_procedure_index))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qreturn_values_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(return_values_list))) {
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
				Qreturn_values_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_rpc_argument_list(return_values_list))) {
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
	      resumable_icp_push(return_values_list);
	      resumable_icp_push(calling_procedure_index);
	      resumable_icp_push(Qsend_icp_rpc_return_values);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_return_values;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_return_values:
    return result;
}

static Object Qoutstanding;        /* outstanding */

static Object Qreturned;           /* returned */

/* HANDLE-ICP-RPC-RETURN-VALUES--BODY */
Object handle_icp_rpc_return_values__body(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object argument, ab_loop_list_, object_argument_qm, rpc_arglist_structure;
    Object remote_procedure_identifier, rpc_argument_list_error, temp;
    Declare_special(1);

    x_note_fn_call(158,178);
    argument = Nil;
    ab_loop_list_ = return_values_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	object_argument_qm = argument;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    object_argument_qm = Nil;
    goto end_1;
    object_argument_qm = Qnil;
  end_1:;
    if (object_argument_qm) {
	rpc_arglist_structure = ISVREF(object_argument_qm,(SI_Long)9L);
	if (check_that_remote_procedure_can_receive_values(calling_procedure_index,
		return_values_list)) {
	    SVREF(rpc_arglist_structure,FIX((SI_Long)5L)) = 
		    calling_procedure_index;
	    SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qreturn;
	}
    }
    else {
	remote_procedure_identifier = 
		lookup_remote_procedure_identifier_from_index(calling_procedure_index);
	rpc_argument_list_error = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Rpc_argument_list_error,Qrpc_argument_list_error,rpc_argument_list_error,
		0);
	  if (remote_procedure_identifier && EQ(Qoutstanding,
		  ISVREF(remote_procedure_identifier,(SI_Long)6L)))
	      SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = Qreturned;
	  temp = frame_serial_number_0();
	  receive_remote_procedure_values(remote_procedure_identifier,
		  icp_cons_1(temp,icp_cons_1(Nil,return_values_list)));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_return_values;  /* handle-icp-rpc-return-values */

/* HANDLE-ICP-RPC-RETURN-VALUES */
Object handle_icp_rpc_return_values()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, calling_procedure_index;
    Object return_values_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,179);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_return_values,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
			      Qcalling_procedure_index,string_constant_6,
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
				Qcalling_procedure_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    calling_procedure_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  calling_procedure_index = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qreturn_values_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_rpc_argument_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qreturn_values_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    return_values_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  return_values_list = read_icp_rpc_argument_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_return_values__body(calling_procedure_index,
			return_values_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_return_values,string_constant_5,Qmessage,
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
		    emit_icp_read_trace(T,Nil,Nil,Qcalling_procedure_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      Qcalling_procedure_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  calling_procedure_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		calling_procedure_index = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qreturn_values_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_rpc_argument_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qreturn_values_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  return_values_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		return_values_list = read_icp_rpc_argument_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_return_values__body(calling_procedure_index,
		      return_values_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_return_values,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_rpc_return_values,top,Nil);
		goto end_handle_icp_rpc_return_values;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_return_values,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		  calling_procedure_index = resumable_icp_pop();
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
			      Qcalling_procedure_index,string_constant_6,
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
			resumable_icp_push(Qhandle_icp_rpc_return_values);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_return_values;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcalling_procedure_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    calling_procedure_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_rpc_return_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_return_values;
		  }
		  calling_procedure_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  return_values_list = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qreturn_values_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_rpc_argument_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(calling_procedure_index);
			resumable_icp_push(Qhandle_icp_rpc_return_values);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_return_values;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qreturn_values_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    return_values_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(calling_procedure_index);
		      resumable_icp_push(Qhandle_icp_rpc_return_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_return_values;
		  }
		  return_values_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_rpc_return_values__body(calling_procedure_index,
			return_values_list);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_return_values,string_constant_5,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		calling_procedure_index = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qcalling_procedure_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
		      resumable_icp_push(Qhandle_icp_rpc_return_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_return_values;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcalling_procedure_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  calling_procedure_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_rpc_return_values);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_return_values;
		}
		calling_procedure_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		return_values_list = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qreturn_values_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(calling_procedure_index);
		      resumable_icp_push(Qhandle_icp_rpc_return_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_return_values;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qreturn_values_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  return_values_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_rpc_argument_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(calling_procedure_index);
		    resumable_icp_push(Qhandle_icp_rpc_return_values);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_return_values;
		}
		return_values_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_return_values__body(calling_procedure_index,
		      return_values_list);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_return_values:
    return result;
}

static Object Qsend_icp_rpc_error;  /* send-icp-rpc-error */

static Object Qcorresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qrpc_error;          /* rpc-error */

static Object Qerror_name;         /* error-name */

static Object Qerror_level;        /* error-level */

static Object Qerror_description;  /* error-description */

static Object Qerror_argument_list;  /* error-argument-list */

/* SEND-ICP-RPC-ERROR */
Object send_icp_rpc_error(error_name,error_level,error_description,
	    error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,180);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_error;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  start_writing_icp_message(FIX((SI_Long)232L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_error,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			emit_icp_write_trace(T,Nil,Nil,Qerror_name,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(error_name);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_name,string_constant_7,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(error_name);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_level,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer(error_level);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_level,string_constant_6,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(error_level);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_description,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_text_string(error_description);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_description,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_text_string(error_description);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerror_argument_list,string_constant_6,
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
			      write_icp_rpc_argument_list(error_argument_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_rpc_argument_list(error_argument_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_error,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
		      emit_icp_write_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(error_name);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_name,string_constant_7,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(error_name);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(error_level);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_level,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(error_level);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_text_string(error_description);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(error_description);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(error_argument_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_rpc_argument_list(error_argument_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_error,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_rpc_error,top,Nil);
		goto end_send_icp_rpc_error;
	    }
	}
	error_name = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		 TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_error;
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
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      error_name = value;
	  else {
	      value_1 = make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)232L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_error,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			  case 4:
			    goto l4;
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
			emit_icp_write_trace(T,Nil,Nil,Qerror_name,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(error_name))) 
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
				  Qerror_name,string_constant_7,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(error_name))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qerror_level,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer(error_level))) {
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
				  Qerror_level,string_constant_6,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(error_level))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qerror_description,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_text_string(error_description))) {
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
				  Qerror_description,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(error_description))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerror_argument_list,string_constant_6,
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
			      write_icp_rpc_argument_list(error_argument_list))) 
				  {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_rpc_argument_list(error_argument_list))) {
		    resumable_icp_push(FIX((SI_Long)4L));
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
			    Qrpc_error,string_constant_5,Qmessage,Nil,Nil,
			    Nil,Nil);
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
			case 4:
			  goto l4_1;
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
		      emit_icp_write_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(error_name))) 
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
				Qerror_name,string_constant_7,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(error_name))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer(error_level))) {
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
				Qerror_level,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(error_level))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_text_string(error_description))) {
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
				Qerror_description,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(error_description))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(error_argument_list))) 
				{
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_rpc_argument_list(error_argument_list))) {
		  resumable_icp_push(FIX((SI_Long)4L));
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
	      resumable_icp_push(error_argument_list);
	      resumable_icp_push(error_description);
	      resumable_icp_push(error_level);
	      resumable_icp_push(error_name);
	      resumable_icp_push(Qsend_icp_rpc_error);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_error;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_error:
    return result;
}

/* HANDLE-ICP-RPC-ERROR--BODY */
Object handle_icp_rpc_error__body(error_name,error_level,error_description,
	    error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    x_note_fn_call(158,181);
    receive_remote_procedure_error(Current_icp_socket,error_name,
	    error_level,error_description,error_argument_list);
    reclaim_transformed_rpc_argument_list(error_argument_list,Nil);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_error;  /* handle-icp-rpc-error */

/* HANDLE-ICP-RPC-ERROR */
Object handle_icp_rpc_error()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object error_name, error_level, error_description, error_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,182);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_error,string_constant_5,
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
				Qerror_name,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    error_name = result_of_read;
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
		      error_name = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      error_name = Nil;
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
				Qerror_level,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    error_level = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_level = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_description = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_description = read_icp_text_string();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_rpc_argument_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_argument_list = read_icp_rpc_argument_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_rpc_error__body(error_name,error_level,
			error_description,error_argument_list);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(error_description);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_error,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      Qerror_name,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_name = result_of_read;
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
		    error_name = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    error_name = Nil;
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      Qerror_level,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_level = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_level = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_description,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_description = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_description = read_icp_text_string();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_rpc_argument_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_argument_list = read_icp_rpc_argument_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_error__body(error_name,error_level,
		      error_description,error_argument_list);
	    POP_SPECIAL();
	    reclaim_text_string(error_description);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_error,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_rpc_error,top,Nil);
		goto end_handle_icp_rpc_error;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_error,string_constant_5,
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
		  error_name = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(Qhandle_icp_rpc_error);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_error;
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
				Qerror_name,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    error_name = result_of_read;
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
			  resumable_icp_push(Qhandle_icp_rpc_error);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_error;
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
		      error_name = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      error_name = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_level = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			resumable_icp_push(error_name);
			resumable_icp_push(Qhandle_icp_rpc_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_level,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    error_level = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  error_level = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_description = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(error_level);
			resumable_icp_push(error_name);
			resumable_icp_push(Qhandle_icp_rpc_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_description = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  error_description = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_argument_list = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_rpc_argument_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(error_description);
			resumable_icp_push(error_level);
			resumable_icp_push(error_name);
			resumable_icp_push(Qhandle_icp_rpc_error);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_description);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  error_argument_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_rpc_error__body(error_name,error_level,
			error_description,error_argument_list);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(error_description);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),Qrpc_error,
			  string_constant_5,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_name = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(Qhandle_icp_rpc_error);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_error;
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
			      Qerror_name,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_name = result_of_read;
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
			resumable_icp_push(Qhandle_icp_rpc_error);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_error;
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
		    error_name = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    error_name = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_level = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_level,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_level = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_name);
		    resumable_icp_push(Qhandle_icp_rpc_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error;
		}
		error_level = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_description = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_description,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_description = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_level);
		    resumable_icp_push(error_name);
		    resumable_icp_push(Qhandle_icp_rpc_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error;
		}
		error_description = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_argument_list = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_description);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(Qhandle_icp_rpc_error);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_rpc_argument_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_description);
		    resumable_icp_push(error_level);
		    resumable_icp_push(error_name);
		    resumable_icp_push(Qhandle_icp_rpc_error);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error;
		}
		error_argument_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_error__body(error_name,error_level,
		      error_description,error_argument_list);
	    POP_SPECIAL();
	    reclaim_text_string(error_description);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_error:
    return result;
}

static Object Qsend_icp_rpc_error_to_caller;  /* send-icp-rpc-error-to-caller */

static Object Qrpc_error_to_caller;  /* rpc-error-to-caller */

static Object Qremote_caller_index;  /* remote-caller-index */

static Object Qsignaller_qm;       /* signaller? */

/* SEND-ICP-RPC-ERROR-TO-CALLER */
Object send_icp_rpc_error_to_caller(remote_caller_index,signaller_qm,
	    error_name,error_level,error_description,error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(158,183);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_error_to_caller;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  start_writing_icp_message(FIX((SI_Long)233L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_error_to_caller,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
				Qremote_caller_index,string_constant_6,
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
			      write_icp_unsigned_integer(remote_caller_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qremote_caller_index,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(remote_caller_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qsignaller_qm,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer_or_nil(signaller_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qsignaller_qm,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer_or_nil(signaller_qm);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_name,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(error_name);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_name,string_constant_7,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(error_name);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_level,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer(error_level);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_level,string_constant_6,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(error_level);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_description,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_text_string(error_description);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_description,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_text_string(error_description);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerror_argument_list,string_constant_6,
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
			      write_icp_rpc_argument_list(error_argument_list);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_rpc_argument_list(error_argument_list);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qrpc_error_to_caller,string_constant_5,
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
		      emit_icp_write_trace(T,Nil,Nil,Qremote_caller_index,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer(remote_caller_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qremote_caller_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(remote_caller_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qsignaller_qm,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer_or_nil(signaller_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qsignaller_qm,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer_or_nil(signaller_qm);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(error_name);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_name,string_constant_7,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(error_name);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_unsigned_integer(error_level);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_level,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(error_level);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_text_string(error_description);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(error_description);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(error_argument_list);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_rpc_argument_list(error_argument_list);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_rpc_error_to_caller,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qsend_icp_rpc_error_to_caller,top,Nil);
		goto end_send_icp_rpc_error_to_caller;
	    }
	}
	remote_caller_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : remote_caller_index;
	signaller_qm = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : signaller_qm;
	error_name = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		 TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : error_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_rpc_error_to_caller;
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
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      error_name = value;
	  else {
	      value_1 = make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)233L)))) {
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
		  emit_icp_write_trace(T,Nil,Nil,Qrpc_error_to_caller,
			  string_constant_5,Qmessage,Nil,Nil,Nil,Nil);
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
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
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
				Qremote_caller_index,string_constant_6,
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
			      write_icp_unsigned_integer(remote_caller_index))) 
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
				  Qremote_caller_index,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(remote_caller_index))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qsignaller_qm,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer_or_nil(signaller_qm))) 
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
				  Qsignaller_qm,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer_or_nil(signaller_qm))) {
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
			emit_icp_write_trace(T,Nil,Nil,Qerror_name,
				string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_corresponding_object_index(error_name))) 
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
				  Qerror_name,string_constant_7,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(error_name))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_level,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_unsigned_integer(error_level))) {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_level,string_constant_6,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(error_level))) {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qerror_description,
				string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      write_icp_text_string(error_description))) {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_description,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(error_description))) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qerror_argument_list,string_constant_6,
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
			      write_icp_rpc_argument_list(error_argument_list))) 
				  {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qerror_argument_list,string_constant_6,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_rpc_argument_list(error_argument_list))) {
		    resumable_icp_push(FIX((SI_Long)6L));
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
			    Qrpc_error_to_caller,string_constant_5,
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
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
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
		      emit_icp_write_trace(T,Nil,Nil,Qremote_caller_index,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer(remote_caller_index))) {
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
				Qremote_caller_index,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(remote_caller_index))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qsignaller_qm,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer_or_nil(signaller_qm))) {
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
				Qsignaller_qm,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer_or_nil(signaller_qm))) {
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
		      emit_icp_write_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_corresponding_object_index(error_name))) 
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
				Qerror_name,string_constant_7,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(error_name))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_unsigned_integer(error_level))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_level,string_constant_6,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(error_level))) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_text_string(error_description))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(error_description))) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			    write_icp_rpc_argument_list(error_argument_list))) 
				{
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_rpc_argument_list(error_argument_list))) {
		  resumable_icp_push(FIX((SI_Long)6L));
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
	      resumable_icp_push(error_argument_list);
	      resumable_icp_push(error_description);
	      resumable_icp_push(error_level);
	      resumable_icp_push(error_name);
	      resumable_icp_push(signaller_qm);
	      resumable_icp_push(remote_caller_index);
	      resumable_icp_push(Qsend_icp_rpc_error_to_caller);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_error_to_caller;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_error_to_caller:
    return result;
}

static Object Qsync_abort;         /* sync-abort */

/* HANDLE-ICP-RPC-ERROR-TO-CALLER--BODY */
Object handle_icp_rpc_error_to_caller__body(remote_caller_index,
	    signaller_qm,error_name,error_level,error_description,
	    error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object remote_procedure_identifier;

    x_note_fn_call(158,184);
    remote_procedure_identifier = (SI_Long)0L < IFIX(remote_caller_index) ?
	     
	    lookup_remote_procedure_identifier_from_index(remote_caller_index) 
	    : Nil;
    if (remote_procedure_identifier && EQ(Qoutstanding,
	    ISVREF(remote_procedure_identifier,(SI_Long)6L)))
	SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = Qsync_abort;
    receive_remote_procedure_error_for_caller(remote_procedure_identifier,
	    signaller_qm,error_name,error_level,error_description);
    reclaim_transformed_rpc_argument_list(error_argument_list,Nil);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_rpc_error_to_caller;  /* handle-icp-rpc-error-to-caller */

/* HANDLE-ICP-RPC-ERROR-TO-CALLER */
Object handle_icp_rpc_error_to_caller()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, remote_caller_index;
    Object signaller_qm, index_1, index_space, error_name, error_level;
    Object error_description, error_argument_list, abort_for_icp_catcher_qm;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(158,185);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_error_to_caller,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_caller_index,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
				Qremote_caller_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_caller_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  remote_caller_index = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qsignaller_qm,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer_or_nil();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsignaller_qm,string_constant_6,Qargument,
				T,result_of_read,Nil,Nil);
		    signaller_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  signaller_qm = read_icp_unsigned_integer_or_nil();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
				Qerror_name,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    error_name = result_of_read;
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
		      error_name = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      error_name = Nil;
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
				Qerror_level,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    error_level = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_level = read_icp_unsigned_integer();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_description = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_description = read_icp_text_string();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_rpc_argument_list();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  error_argument_list = read_icp_rpc_argument_list();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_rpc_error_to_caller__body(remote_caller_index,
			signaller_qm,error_name,error_level,
			error_description,error_argument_list);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(error_description);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_error_to_caller,string_constant_5,Qmessage,
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_caller_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      Qremote_caller_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_caller_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		remote_caller_index = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qsignaller_qm,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer_or_nil();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsignaller_qm,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  signaller_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else
		signaller_qm = read_icp_unsigned_integer_or_nil();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			      Qerror_name,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_name = result_of_read;
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
		    error_name = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    error_name = Nil;
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			      Qerror_level,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_level = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_level = read_icp_unsigned_integer();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_description,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_description = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_description = read_icp_text_string();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_rpc_argument_list();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else
		error_argument_list = read_icp_rpc_argument_list();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_error_to_caller__body(remote_caller_index,
		      signaller_qm,error_name,error_level,
		      error_description,error_argument_list);
	    POP_SPECIAL();
	    reclaim_text_string(error_description);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_rpc_error_to_caller,top)) {
		result = icp_error_internal(Qerror,string_constant_4,
			Qhandle_icp_rpc_error_to_caller,top,Nil);
		goto end_handle_icp_rpc_error_to_caller;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qrpc_error_to_caller,
			string_constant_5,Qmessage,Nil,Nil,Nil,T);
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
		  remote_caller_index = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qremote_caller_index,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error_to_caller;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qremote_caller_index,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    remote_caller_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  remote_caller_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  signaller_qm = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qsignaller_qm,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer_or_nil();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(remote_caller_index);
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error_to_caller;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsignaller_qm,string_constant_6,Qargument,
				T,result_of_read,Nil,Nil);
		    signaller_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer_or_nil();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  signaller_qm = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_name = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			      string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			    resumable_icp_push(signaller_qm);
			    resumable_icp_push(remote_caller_index);
			    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_rpc_error_to_caller;
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
				Qerror_name,string_constant_7,Qargument,T,
				result_of_read,Nil,Nil);
		    error_name = result_of_read;
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
			  resumable_icp_push(signaller_qm);
			  resumable_icp_push(remote_caller_index);
			  resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_error_to_caller;
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
		      error_name = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      error_name = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_level = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
			resumable_icp_push(error_name);
			resumable_icp_push(signaller_qm);
			resumable_icp_push(remote_caller_index);
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error_to_caller;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_level,string_constant_6,Qargument,T,
				result_of_read,Nil,Nil);
		    error_level = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  error_level = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_description = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(error_level);
			resumable_icp_push(error_name);
			resumable_icp_push(signaller_qm);
			resumable_icp_push(remote_caller_index);
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error_to_caller;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_description,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_description = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  error_description = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  error_argument_list = resumable_icp_pop();
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
		      emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			      string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_rpc_argument_list();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(error_description);
			resumable_icp_push(error_level);
			resumable_icp_push(error_name);
			resumable_icp_push(signaller_qm);
			resumable_icp_push(remote_caller_index);
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_rpc_error_to_caller;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerror_argument_list,string_constant_6,
				Qargument,T,result_of_read,Nil,Nil);
		    error_argument_list = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_description);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  error_argument_list = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_rpc_error_to_caller__body(remote_caller_index,
			signaller_qm,error_name,error_level,
			error_description,error_argument_list);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(error_description);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qrpc_error_to_caller,string_constant_5,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		remote_caller_index = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qremote_caller_index,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qremote_caller_index,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  remote_caller_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error_to_caller;
		}
		remote_caller_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		signaller_qm = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qsignaller_qm,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer_or_nil();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsignaller_qm,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  signaller_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer_or_nil();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(remote_caller_index);
		    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error_to_caller;
		}
		signaller_qm = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_name = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_name,
			    string_constant_7,Qargument,Nil,Nil,Nil,Nil);
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
			  resumable_icp_push(signaller_qm);
			  resumable_icp_push(remote_caller_index);
			  resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_rpc_error_to_caller;
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
			      Qerror_name,string_constant_7,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_name = result_of_read;
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
			resumable_icp_push(signaller_qm);
			resumable_icp_push(remote_caller_index);
			resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_rpc_error_to_caller;
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
		    error_name = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    error_name = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_level = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_level,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
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
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_level,string_constant_6,Qargument,T,
			      result_of_read,Nil,Nil);
		  error_level = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_name);
		    resumable_icp_push(signaller_qm);
		    resumable_icp_push(remote_caller_index);
		    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error_to_caller;
		}
		error_level = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_description = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_description,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_description,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_description = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_level);
		    resumable_icp_push(error_name);
		    resumable_icp_push(signaller_qm);
		    resumable_icp_push(remote_caller_index);
		    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error_to_caller;
		}
		error_description = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		error_argument_list = resumable_icp_pop();
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
		    emit_icp_read_trace(T,Nil,Nil,Qerror_argument_list,
			    string_constant_6,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_rpc_argument_list();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(error_description);
		      resumable_icp_push(error_level);
		      resumable_icp_push(error_name);
		      resumable_icp_push(signaller_qm);
		      resumable_icp_push(remote_caller_index);
		      resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_rpc_error_to_caller;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerror_argument_list,string_constant_6,
			      Qargument,T,result_of_read,Nil,Nil);
		  error_argument_list = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_rpc_argument_list();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(error_description);
		    resumable_icp_push(error_level);
		    resumable_icp_push(error_name);
		    resumable_icp_push(signaller_qm);
		    resumable_icp_push(remote_caller_index);
		    resumable_icp_push(Qhandle_icp_rpc_error_to_caller);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_rpc_error_to_caller;
		}
		error_argument_list = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_rpc_error_to_caller__body(remote_caller_index,
		      signaller_qm,error_name,error_level,
		      error_description,error_argument_list);
	    POP_SPECIAL();
	    reclaim_text_string(error_description);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_rpc_error_to_caller:
    return result;
}

void rpc_common2_INIT()
{
    Object temp, reclaim_structure_for_resumable_object_mixin_1;
    Object reclaim_structure_for_resumable_icp_object_mixin_1;
    Object reclaim_structure_for_resumable_node_mixin_1;
    Object reclaim_structure_for_resumable_icp_node_mixin_1;
    Object reclaim_structure_for_receiving_resumable_object_1;
    Object reclaim_structure_for_object_building_problem_1;
    Object reclaim_structure_for_receiving_rpc_arglist_structure_1;
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_9;
    Object list_constant_8;
    Object Qabort_building_object_for_resumable_object_portion;
    Object Qfinish_building_object_for_resumable_object_portion;
    Object Qsuspend_building_object_for_resumable_object_portion;
    Object Qascend_to_parent_for_resumable_object_portion;
    Object Qadd_homogeneous_value_list_range_for_resumable_object_portion;
    Object Qadd_value_list_range_for_resumable_object_portion;
    Object Qadd_homogeneous_history_range_for_resumable_object_portion;
    Object Qadd_history_range_for_resumable_object_portion;
    Object Qadd_homogeneous_value_vector_range_for_resumable_object_portion;
    Object Qadd_value_vector_range_for_resumable_object_portion;
    Object Qadd_attribute_value_list_for_resumable_object_portion;
    Object Qadd_attribute_object_list_for_resumable_object_portion;
    Object Qadd_attribute_history_object_for_resumable_object_portion;
    Object Qadd_attribute_value_vector_for_resumable_object_portion;
    Object Qadd_attribute_object_vector_for_resumable_object_portion;
    Object Qadd_resumable_circularity_for_resumable_object_portion;
    Object Qadd_attribute_object_for_resumable_object_portion;
    Object Qadd_circular_attribute_for_resumable_object_portion;
    Object Qadd_attribute_value_for_resumable_object_portion, list_constant_7;
    Object Qattribute_value_tags, Qattribute_value_long_tag;
    Object Qattribute_value_evaluation_structure_tag;
    Object Qattribute_value_evaluation_sequence_tag, Qattribute_value_null_tag;
    Object Qcircular_reference_tag, Qunknown_value_vector_element_type_tag;
    Object Qattribute_value_truth_value_tag, Qattribute_value_text_tag;
    Object Qattribute_value_symbol_tag, Qattribute_value_float_tag;
    Object Qattribute_value_integer_tag, Qcurrent_value, Qname;
    Object list_constant_6, Qattribute_spec_qm_tags;
    Object Qqualified_system_attribute_tag, Qunqualified_system_attribute_tag;
    Object Qqualified_symbolic_attribute_tag;
    Object Qunqualified_symbolic_attribute_tag;
    Object Qlist_element_attribute_spec_tag;
    Object Qvector_element_attribute_spec_tag, Qnameless_attribute_spec_tag;
    Object list_constant_5, Qpossibly_interned_symbol_tags;
    Object Qpossibly_interned_symbol_uninterned_overflow_tag;
    Object Qpossibly_interned_symbol_uninterned_tag;
    Object Qpossibly_interned_symbol_interned_tag;
    Object Qreceiving_rpc_arglist_structure, Qreclaim_structure;
    Object Qoutstanding_receiving_rpc_arglist_structure_count;
    Object Qreceiving_rpc_arglist_structure_structure_memory_usage;
    Object Qutilities2, string_constant_21, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_20, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qreclaim_icp_port_entry_for_resumable_instance_node;
    Object Qresumable_instance_node, list_constant_4;
    Object Qicp_object_map_for_resumable_instance_node;
    Object Qreclaim_icp_port_entry_for_resumable_object;
    Object Qreclaim_resumable_object, Qresumable_object, list_constant_3;
    Object Qicp_object_map_for_resumable_object, Qobject_building_problem;
    Object Qoutstanding_object_building_problem_count;
    Object Qobject_building_problem_structure_memory_usage, string_constant_19;
    Object string_constant_18, Qreceiving_resumable_object;
    Object Qoutstanding_receiving_resumable_object_count;
    Object Qreceiving_resumable_object_structure_memory_usage;
    Object string_constant_17, string_constant_16, Qresumable_icp_node_mixin;
    Object Qoutstanding_resumable_icp_node_mixin_count;
    Object Qresumable_icp_node_mixin_structure_memory_usage;
    Object string_constant_15, string_constant_14, Qresumable_node_mixin;
    Object Qoutstanding_resumable_node_mixin_count;
    Object Qresumable_node_mixin_structure_memory_usage, string_constant_13;
    Object string_constant_12, Qresumable_icp_object_mixin;
    Object Qoutstanding_resumable_icp_object_mixin_count;
    Object Qresumable_icp_object_mixin_structure_memory_usage;
    Object string_constant_11, string_constant_10, Qresumable_object_mixin;
    Object Qoutstanding_resumable_object_mixin_count;
    Object Qresumable_object_mixin_structure_memory_usage, string_constant_9;
    Object string_constant_8;

    x_note_fn_call(158,186);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_object_mixin = STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    Qresumable_object_mixin,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qresumable_object_mixin,
	    Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_object_mixin == UNBOUND)
	The_type_description_of_resumable_object_mixin = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m834Xy1n834Xy8n8k1l8n0000000krk0k0");
    temp = The_type_description_of_resumable_object_mixin;
    The_type_description_of_resumable_object_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    The_type_description_of_resumable_object_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qresumable_object_mixin,
	    The_type_description_of_resumable_object_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_object_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-OBJECT-MIXIN-COUNT",
	    AB_package);
    Qresumable_object_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q834Xy8s83-mny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_object_mixin_count);
    push_optimized_constant(Qresumable_object_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_resumable_object_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-OBJECT-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_object_mixins,
	    Chain_of_available_resumable_object_mixins);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_resumable_object_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_object_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_object_mixin_count,
	    Resumable_object_mixin_count);
    record_system_variable(Qresumable_object_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_object_mixins_vector == UNBOUND)
	Chain_of_available_resumable_object_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_object_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_object_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_object_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_object_mixin_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_resumable_object_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_object_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_object_mixin,
	    reclaim_structure_for_resumable_object_mixin_1);
    Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_icp_object_mixin = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    Qresumable_icp_object_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_icp_object_mixin,
	    Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_icp_object_mixin == UNBOUND)
	The_type_description_of_resumable_icp_object_mixin = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83Emy1o83Emy834Xy8n8k1l834Xy0000001l1m8x834Xyksk0k0");
    temp = The_type_description_of_resumable_icp_object_mixin;
    The_type_description_of_resumable_icp_object_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    The_type_description_of_resumable_icp_object_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_icp_object_mixin,
	    The_type_description_of_resumable_icp_object_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_icp_object_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-ICP-OBJECT-MIXIN-COUNT",
	    AB_package);
    Qresumable_icp_object_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83Emy8s83-mhy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_icp_object_mixin_count);
    push_optimized_constant(Qresumable_icp_object_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_resumable_icp_object_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-ICP-OBJECT-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_icp_object_mixins,
	    Chain_of_available_resumable_icp_object_mixins);
    record_system_variable(Qchain_of_available_resumable_icp_object_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_icp_object_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_icp_object_mixin_count,
	    Resumable_icp_object_mixin_count);
    record_system_variable(Qresumable_icp_object_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_icp_object_mixins_vector == UNBOUND)
	Chain_of_available_resumable_icp_object_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_icp_object_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_icp_object_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_icp_object_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_icp_object_mixin_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_resumable_icp_object_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_icp_object_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_icp_object_mixin,
	    reclaim_structure_for_resumable_icp_object_mixin_1);
    Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_node_mixin = STATIC_SYMBOL("RESUMABLE-NODE-MIXIN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    Qresumable_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_node_mixin,
	    Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_node_mixin == UNBOUND)
	The_type_description_of_resumable_node_mixin = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83*By1n83*By8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_resumable_node_mixin;
    The_type_description_of_resumable_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    The_type_description_of_resumable_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_node_mixin,
	    The_type_description_of_resumable_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-NODE-MIXIN-COUNT",AB_package);
    Qresumable_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83*By8s83-mly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_node_mixin_count);
    push_optimized_constant(Qresumable_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_resumable_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_node_mixins,
	    Chain_of_available_resumable_node_mixins);
    record_system_variable(Qchain_of_available_resumable_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_node_mixin_count,
	    Resumable_node_mixin_count);
    record_system_variable(Qresumable_node_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_node_mixin_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_resumable_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_node_mixin,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_node_mixin,
	    reclaim_structure_for_resumable_node_mixin_1);
    Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qresumable_icp_node_mixin = STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    Qresumable_icp_node_mixin,Qab_name_of_unique_structure_type);
    mutate_global_property(Qresumable_icp_node_mixin,
	    Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_resumable_icp_node_mixin == UNBOUND)
	The_type_description_of_resumable_icp_node_mixin = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83*cy1o83*cy83*By8n8k1l83*By0000001l1m8x83*Bykok0k0");
    temp = The_type_description_of_resumable_icp_node_mixin;
    The_type_description_of_resumable_icp_node_mixin = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    The_type_description_of_resumable_icp_node_mixin,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qresumable_icp_node_mixin,
	    The_type_description_of_resumable_icp_node_mixin,
	    Qtype_description_of_type);
    Qoutstanding_resumable_icp_node_mixin_count = 
	    STATIC_SYMBOL("OUTSTANDING-RESUMABLE-ICP-NODE-MIXIN-COUNT",
	    AB_package);
    Qresumable_icp_node_mixin_structure_memory_usage = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_15 = STATIC_STRING("1q83*cy8s83-mgy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_resumable_icp_node_mixin_count);
    push_optimized_constant(Qresumable_icp_node_mixin_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_resumable_icp_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-ICP-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_resumable_icp_node_mixins,
	    Chain_of_available_resumable_icp_node_mixins);
    record_system_variable(Qchain_of_available_resumable_icp_node_mixins,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qresumable_icp_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qresumable_icp_node_mixin_count,
	    Resumable_icp_node_mixin_count);
    record_system_variable(Qresumable_icp_node_mixin_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_resumable_icp_node_mixins_vector == UNBOUND)
	Chain_of_available_resumable_icp_node_mixins_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qresumable_icp_node_mixin_structure_memory_usage,
	    STATIC_FUNCTION(resumable_icp_node_mixin_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_resumable_icp_node_mixin_count,
	    STATIC_FUNCTION(outstanding_resumable_icp_node_mixin_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_resumable_icp_node_mixin_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_resumable_icp_node_mixin,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qresumable_icp_node_mixin,
	    reclaim_structure_for_resumable_icp_node_mixin_1);
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreceiving_resumable_object = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    Qreceiving_resumable_object,Qab_name_of_unique_structure_type);
    mutate_global_property(Qreceiving_resumable_object,
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_receiving_resumable_object == UNBOUND)
	The_type_description_of_receiving_resumable_object = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83m1y1o83m1y834Xy8n8k1l834Xy0000001n1m8x834Xy1n8y83-5Hy01m83My83-Aqykzk0k0");
    temp = The_type_description_of_receiving_resumable_object;
    The_type_description_of_receiving_resumable_object = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    The_type_description_of_receiving_resumable_object,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qreceiving_resumable_object,
	    The_type_description_of_receiving_resumable_object,
	    Qtype_description_of_type);
    Qoutstanding_receiving_resumable_object_count = 
	    STATIC_SYMBOL("OUTSTANDING-RECEIVING-RESUMABLE-OBJECT-COUNT",
	    AB_package);
    Qreceiving_resumable_object_structure_memory_usage = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83m1y8s83-lGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_receiving_resumable_object_count);
    push_optimized_constant(Qreceiving_resumable_object_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_receiving_resumable_objects = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RECEIVING-RESUMABLE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_receiving_resumable_objects,
	    Chain_of_available_receiving_resumable_objects);
    record_system_variable(Qchain_of_available_receiving_resumable_objects,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qreceiving_resumable_object_count = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreceiving_resumable_object_count,
	    Receiving_resumable_object_count);
    record_system_variable(Qreceiving_resumable_object_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_receiving_resumable_objects_vector == UNBOUND)
	Chain_of_available_receiving_resumable_objects_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qreceiving_resumable_object_structure_memory_usage,
	    STATIC_FUNCTION(receiving_resumable_object_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_receiving_resumable_object_count,
	    STATIC_FUNCTION(outstanding_receiving_resumable_object_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_receiving_resumable_object_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_receiving_resumable_object,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qreceiving_resumable_object,
	    reclaim_structure_for_receiving_resumable_object_1);
    Qg2_defstruct_structure_name_object_building_problem_g2_struct = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qobject_building_problem = STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    Qobject_building_problem,Qab_name_of_unique_structure_type);
    mutate_global_property(Qobject_building_problem,
	    Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_object_building_problem == UNBOUND)
	The_type_description_of_object_building_problem = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83lAy1n83lAy8n8k1l8n0000001l1n8y83-5*y1q83-7ty83-7oy83-7py83-7ry83-7sy83-7qykrk0k0");
    temp = The_type_description_of_object_building_problem;
    The_type_description_of_object_building_problem = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    The_type_description_of_object_building_problem,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qobject_building_problem,
	    The_type_description_of_object_building_problem,
	    Qtype_description_of_type);
    Qoutstanding_object_building_problem_count = 
	    STATIC_SYMBOL("OUTSTANDING-OBJECT-BUILDING-PROBLEM-COUNT",
	    AB_package);
    Qobject_building_problem_structure_memory_usage = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83lAy8s83-hHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_object_building_problem_count);
    push_optimized_constant(Qobject_building_problem_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_object_building_problems = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-OBJECT-BUILDING-PROBLEMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_object_building_problems,
	    Chain_of_available_object_building_problems);
    record_system_variable(Qchain_of_available_object_building_problems,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qobject_building_problem_count = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qobject_building_problem_count,
	    Object_building_problem_count);
    record_system_variable(Qobject_building_problem_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_object_building_problems_vector == UNBOUND)
	Chain_of_available_object_building_problems_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qobject_building_problem_structure_memory_usage,
	    STATIC_FUNCTION(object_building_problem_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_object_building_problem_count,
	    STATIC_FUNCTION(outstanding_object_building_problem_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_object_building_problem_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_object_building_problem,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qobject_building_problem,
	    reclaim_structure_for_object_building_problem_1);
    string_constant = STATIC_STRING("~(~A::~A~)");
    string_constant_1 = STATIC_STRING("~(~A~)");
    string_constant_2 = STATIC_STRING("top-level");
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qset_access_form_for_resumable_object = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-RESUMABLE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_resumable_object,
	    STATIC_FUNCTION(set_access_form_for_resumable_object,NIL,FALSE,
	    2,2));
    Qresumable_object = STATIC_SYMBOL("RESUMABLE-OBJECT",AB_package);
    Qicp_object_map_for_resumable_object = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-RESUMABLE-OBJECT",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_resumable_object,Qresumable_object);
    initialize_icp_object_type_compile(Qresumable_object,
	    Qstandard_icp_object_index_space,list_constant_3);
    Qreclaim_resumable_object = STATIC_SYMBOL("RECLAIM-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_resumable_object,
	    STATIC_FUNCTION(reclaim_resumable_object,NIL,FALSE,2,2));
    Qreclaim_icp_port_entry_for_resumable_object = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_resumable_object,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_resumable_object,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qresumable_object,Qreclaim_resumable_object,
	    Qnil,Qreclaim_icp_port_entry_for_resumable_object);
    Qset_access_form_for_resumable_instance_node = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_resumable_instance_node,
	    STATIC_FUNCTION(set_access_form_for_resumable_instance_node,
	    NIL,FALSE,2,2));
    Qresumable_instance_node = STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE",
	    AB_package);
    Qicp_object_map_for_resumable_instance_node = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,
	    Qicp_object_map_for_resumable_instance_node,
	    Qresumable_instance_node);
    initialize_icp_object_type_compile(Qresumable_instance_node,
	    Qstandard_icp_object_index_space,list_constant_4);
    Qreclaim_icp_port_entry_for_resumable_instance_node = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_resumable_instance_node,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_resumable_instance_node,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qresumable_instance_node,Qnil,Qnil,
	    Qreclaim_icp_port_entry_for_resumable_instance_node);
    Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct 
	    = STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreceiving_rpc_arglist_structure = 
	    STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    Qreceiving_rpc_arglist_structure,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qreceiving_rpc_arglist_structure,
	    Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_receiving_rpc_arglist_structure == UNBOUND)
	The_type_description_of_receiving_rpc_arglist_structure = Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8m83m2y1n83m2y8n8k1l8n0000000ktk0k0");
    temp = The_type_description_of_receiving_rpc_arglist_structure;
    The_type_description_of_receiving_rpc_arglist_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_20));
    mutate_global_property(Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    The_type_description_of_receiving_rpc_arglist_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qreceiving_rpc_arglist_structure,
	    The_type_description_of_receiving_rpc_arglist_structure,
	    Qtype_description_of_type);
    Qoutstanding_receiving_rpc_arglist_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-RECEIVING-RPC-ARGLIST-STRUCTURE-COUNT",
	    AB_package);
    Qreceiving_rpc_arglist_structure_structure_memory_usage = 
	    STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_21 = STATIC_STRING("1q83m2y8s83-lHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_receiving_rpc_arglist_structure_count);
    push_optimized_constant(Qreceiving_rpc_arglist_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_receiving_rpc_arglist_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RECEIVING-RPC-ARGLIST-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_receiving_rpc_arglist_structures,
	    Chain_of_available_receiving_rpc_arglist_structures);
    record_system_variable(Qchain_of_available_receiving_rpc_arglist_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qreceiving_rpc_arglist_structure_count = 
	    STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreceiving_rpc_arglist_structure_count,
	    Receiving_rpc_arglist_structure_count);
    record_system_variable(Qreceiving_rpc_arglist_structure_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_receiving_rpc_arglist_structures_vector == UNBOUND)
	Chain_of_available_receiving_rpc_arglist_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qreceiving_rpc_arglist_structure_structure_memory_usage,
	    STATIC_FUNCTION(receiving_rpc_arglist_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_receiving_rpc_arglist_structure_count,
	    STATIC_FUNCTION(outstanding_receiving_rpc_arglist_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_receiving_rpc_arglist_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_receiving_rpc_arglist_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qreceiving_rpc_arglist_structure,
	    reclaim_structure_for_receiving_rpc_arglist_structure_1);
    Qgsi_reference_flag = STATIC_SYMBOL("GSI-REFERENCE-FLAG",AB_package);
    list_constant = STATIC_LIST((SI_Long)18L,FIX((SI_Long)17L),
	    FIX((SI_Long)19L),FIX((SI_Long)20L),FIX((SI_Long)21L),
	    FIX((SI_Long)22L),FIX((SI_Long)25L),FIX((SI_Long)26L),
	    FIX((SI_Long)23L),FIX((SI_Long)24L),FIX((SI_Long)33L),
	    FIX((SI_Long)35L),FIX((SI_Long)36L),FIX((SI_Long)37L),
	    FIX((SI_Long)38L),FIX((SI_Long)41L),FIX((SI_Long)42L),
	    FIX((SI_Long)39L),FIX((SI_Long)40L));
    Qinteger_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    Qsymbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qtext_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    Qtruth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qquantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    Qitem_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qvalue_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    Qinteger_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    Qtext_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    Qtruth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    Qfloat_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    Qitem_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    Qvalue_list = STATIC_SYMBOL("VALUE-LIST",AB_package);
    Qrpc_value_or_object = STATIC_SYMBOL("RPC-VALUE-OR-OBJECT",AB_package);
    string_constant_3 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qrpc_argument_list = STATIC_SYMBOL("RPC-ARGUMENT-LIST",AB_package);
    if (Rpc_throw_tag == UNBOUND)
	Rpc_throw_tag = Nil;
    Qpossibly_interned_symbol_interned_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-INTERNED-TAG",AB_package);
    SET_SYMBOL_VALUE(Qpossibly_interned_symbol_interned_tag,FIX((SI_Long)0L));
    Qpossibly_interned_symbol_uninterned_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-UNINTERNED-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qpossibly_interned_symbol_uninterned_tag,
	    FIX((SI_Long)1L));
    Qpossibly_interned_symbol_uninterned_overflow_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-UNINTERNED-OVERFLOW-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qpossibly_interned_symbol_uninterned_overflow_tag,
	    FIX((SI_Long)2L));
    Qpossibly_interned_symbol_tags = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-TAGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpossibly_interned_symbol_tags,
	    Possibly_interned_symbol_tags);
    list_constant_5 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L));
    SET_SYMBOL_VALUE(Qpossibly_interned_symbol_tags,list_constant_5);
    Qnameless_attribute_spec_tag = 
	    STATIC_SYMBOL("NAMELESS-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qnameless_attribute_spec_tag,FIX((SI_Long)2L));
    Qvector_element_attribute_spec_tag = 
	    STATIC_SYMBOL("VECTOR-ELEMENT-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qvector_element_attribute_spec_tag,FIX((SI_Long)3L));
    Qlist_element_attribute_spec_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qlist_element_attribute_spec_tag,FIX((SI_Long)4L));
    Qunqualified_symbolic_attribute_tag = 
	    STATIC_SYMBOL("UNQUALIFIED-SYMBOLIC-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qunqualified_symbolic_attribute_tag,FIX((SI_Long)12L));
    Qqualified_symbolic_attribute_tag = 
	    STATIC_SYMBOL("QUALIFIED-SYMBOLIC-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qqualified_symbolic_attribute_tag,FIX((SI_Long)13L));
    Qunqualified_system_attribute_tag = 
	    STATIC_SYMBOL("UNQUALIFIED-SYSTEM-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qunqualified_system_attribute_tag,FIX((SI_Long)14L));
    Qqualified_system_attribute_tag = 
	    STATIC_SYMBOL("QUALIFIED-SYSTEM-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qqualified_system_attribute_tag,FIX((SI_Long)15L));
    Qattribute_spec_qm_tags = STATIC_SYMBOL("ATTRIBUTE-SPEC\?-TAGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_spec_qm_tags,Attribute_spec_qm_tags);
    list_constant_6 = STATIC_LIST((SI_Long)7L,FIX((SI_Long)2L),
	    FIX((SI_Long)3L),FIX((SI_Long)4L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)14L),FIX((SI_Long)15L));
    SET_SYMBOL_VALUE(Qattribute_spec_qm_tags,list_constant_6);
    Qvector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qname,Qcurrent_value);
    Qlist_element = STATIC_SYMBOL("LIST-ELEMENT",AB_package);
    Qlist_of_attributes = STATIC_SYMBOL("LIST-OF-ATTRIBUTES",AB_package);
    Qwrite_icp_list_of_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-ATTRIBUTES",AB_package);
    string_constant_4 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_attributes,
	    STATIC_FUNCTION(write_icp_list_of_attributes,NIL,FALSE,1,1));
    Qread_icp_list_of_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-ATTRIBUTES",AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_attributes,
	    STATIC_FUNCTION(read_icp_list_of_attributes,NIL,FALSE,0,0));
    Qlist_of_boolean = STATIC_SYMBOL("LIST-OF-BOOLEAN",AB_package);
    Qread_icp_list_of_boolean = STATIC_SYMBOL("READ-ICP-LIST-OF-BOOLEAN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_boolean,
	    STATIC_FUNCTION(read_icp_list_of_boolean,NIL,FALSE,0,0));
    Qwrite_icp_list_of_boolean = STATIC_SYMBOL("WRITE-ICP-LIST-OF-BOOLEAN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_boolean,
	    STATIC_FUNCTION(write_icp_list_of_boolean,NIL,FALSE,1,1));
    Qlist_of_lists_of_attributes = 
	    STATIC_SYMBOL("LIST-OF-LISTS-OF-ATTRIBUTES",AB_package);
    Qwrite_icp_list_of_lists_of_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-LISTS-OF-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_lists_of_attributes,
	    STATIC_FUNCTION(write_icp_list_of_lists_of_attributes,NIL,
	    FALSE,1,1));
    Qread_icp_list_of_lists_of_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-LISTS-OF-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_lists_of_attributes,
	    STATIC_FUNCTION(read_icp_list_of_lists_of_attributes,NIL,FALSE,
	    0,0));
    Qlist_of_included_return_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDED-RETURN-ATTRIBUTES",AB_package);
    Qwrite_icp_list_of_included_return_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_included_return_attributes,
	    STATIC_FUNCTION(write_icp_list_of_included_return_attributes,
	    NIL,FALSE,1,1));
    Qread_icp_list_of_included_return_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_included_return_attributes,
	    STATIC_FUNCTION(read_icp_list_of_included_return_attributes,
	    NIL,FALSE,0,0));
    Qlist_of_excluded_return_attributes = 
	    STATIC_SYMBOL("LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",AB_package);
    Qwrite_icp_list_of_excluded_return_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_excluded_return_attributes,
	    STATIC_FUNCTION(write_icp_list_of_excluded_return_attributes,
	    NIL,FALSE,1,1));
    Qread_icp_list_of_excluded_return_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_excluded_return_attributes,
	    STATIC_FUNCTION(read_icp_list_of_excluded_return_attributes,
	    NIL,FALSE,0,0));
    Qlist_of_included_return_system_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qwrite_icp_list_of_included_return_system_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_included_return_system_attributes,
	    STATIC_FUNCTION(write_icp_list_of_included_return_system_attributes,
	    NIL,FALSE,1,1));
    Qread_icp_list_of_included_return_system_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_included_return_system_attributes,
	    STATIC_FUNCTION(read_icp_list_of_included_return_system_attributes,
	    NIL,FALSE,0,0));
    Qlist_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    Qwrite_icp_list_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_include_all_return_system_attributes,
	    STATIC_FUNCTION(write_icp_list_of_include_all_return_system_attributes,
	    NIL,FALSE,1,1));
    Qread_icp_list_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_include_all_return_system_attributes,
	    STATIC_FUNCTION(read_icp_list_of_include_all_return_system_attributes,
	    NIL,FALSE,0,0));
    Qlist_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    Qwrite_icp_list_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_include_all_return_system_attributes_except,
	    STATIC_FUNCTION(write_icp_list_of_include_all_return_system_attributes_except,
	    NIL,FALSE,1,1));
    Qread_icp_list_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_include_all_return_system_attributes_except,
	    STATIC_FUNCTION(read_icp_list_of_include_all_return_system_attributes_except,
	    NIL,FALSE,0,0));
    Qlist_of_return_kinds = STATIC_SYMBOL("LIST-OF-RETURN-KINDS",AB_package);
    Qwrite_icp_list_of_return_kinds = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-RETURN-KINDS",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_list_of_return_kinds,
	    STATIC_FUNCTION(write_icp_list_of_return_kinds,NIL,FALSE,1,1));
    Qread_icp_list_of_return_kinds = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-RETURN-KINDS",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_list_of_return_kinds,
	    STATIC_FUNCTION(read_icp_list_of_return_kinds,NIL,FALSE,0,0));
    Qremote_procedure_varargs_p = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-VARARGS-P",AB_package);
    Qwrite_icp_remote_procedure_varargs_p = 
	    STATIC_SYMBOL("WRITE-ICP-REMOTE-PROCEDURE-VARARGS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_remote_procedure_varargs_p,
	    STATIC_FUNCTION(write_icp_remote_procedure_varargs_p,NIL,FALSE,
	    1,1));
    Qread_icp_remote_procedure_varargs_p = 
	    STATIC_SYMBOL("READ-ICP-REMOTE-PROCEDURE-VARARGS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_remote_procedure_varargs_p,
	    STATIC_FUNCTION(read_icp_remote_procedure_varargs_p,NIL,FALSE,
	    0,0));
    Qattribute_value_integer_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-INTEGER-TAG",AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_integer_tag,FIX((SI_Long)5L));
    Qattribute_value_float_tag = STATIC_SYMBOL("ATTRIBUTE-VALUE-FLOAT-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_float_tag,FIX((SI_Long)6L));
    Qattribute_value_symbol_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-SYMBOL-TAG",AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_symbol_tag,FIX((SI_Long)7L));
    Qattribute_value_text_tag = STATIC_SYMBOL("ATTRIBUTE-VALUE-TEXT-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_text_tag,FIX((SI_Long)8L));
    Qattribute_value_truth_value_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-TRUTH-VALUE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_truth_value_tag,FIX((SI_Long)9L));
    Qunknown_value_vector_element_type_tag = 
	    STATIC_SYMBOL("UNKNOWN-VALUE-VECTOR-ELEMENT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qunknown_value_vector_element_type_tag,FIX((SI_Long)11L));
    Qcircular_reference_tag = STATIC_SYMBOL("CIRCULAR-REFERENCE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qcircular_reference_tag,FIX((SI_Long)12L));
    Qattribute_value_null_tag = STATIC_SYMBOL("ATTRIBUTE-VALUE-NULL-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_null_tag,FIX((SI_Long)13L));
    Qattribute_value_evaluation_sequence_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-EVALUATION-SEQUENCE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_evaluation_sequence_tag,
	    FIX((SI_Long)14L));
    Qattribute_value_evaluation_structure_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-EVALUATION-STRUCTURE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_evaluation_structure_tag,
	    FIX((SI_Long)15L));
    Qattribute_value_long_tag = STATIC_SYMBOL("ATTRIBUTE-VALUE-LONG-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qattribute_value_long_tag,FIX((SI_Long)16L));
    Qattribute_value_tags = STATIC_SYMBOL("ATTRIBUTE-VALUE-TAGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_value_tags,Attribute_value_tags);
    list_constant_7 = STATIC_LIST((SI_Long)11L,FIX((SI_Long)5L),
	    FIX((SI_Long)6L),FIX((SI_Long)7L),FIX((SI_Long)8L),
	    FIX((SI_Long)9L),FIX((SI_Long)11L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)14L),FIX((SI_Long)15L),
	    FIX((SI_Long)16L));
    SET_SYMBOL_VALUE(Qattribute_value_tags,list_constant_7);
    Qevaluation_truth_value = STATIC_SYMBOL("EVALUATION-TRUTH-VALUE",
	    AB_package);
    Qhistory_timestamp = STATIC_SYMBOL("HISTORY-TIMESTAMP",AB_package);
    Qadd_attribute_value_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_value_for_resumable_object_portion,
	    FIX((SI_Long)1L));
    Qpremature_attribute_value = STATIC_SYMBOL("PREMATURE-ATTRIBUTE-VALUE",
	    AB_package);
    Qadd_circular_attribute_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-CIRCULAR-ATTRIBUTE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_circular_attribute_for_resumable_object_portion,
	    FIX((SI_Long)2L));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qvector_element,Qlist_element);
    Qcircular_object_not_in_list_or_array = 
	    STATIC_SYMBOL("CIRCULAR-OBJECT-NOT-IN-LIST-OR-ARRAY",AB_package);
    Qcannot_locate_network_registered_object = 
	    STATIC_SYMBOL("CANNOT-LOCATE-NETWORK-REGISTERED-OBJECT",
	    AB_package);
    Qpremature_circular_attribute = 
	    STATIC_SYMBOL("PREMATURE-CIRCULAR-ATTRIBUTE",AB_package);
    Qadd_attribute_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_object_for_resumable_object_portion,
	    FIX((SI_Long)3L));
    Qadd_resumable_circularity_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-RESUMABLE-CIRCULARITY-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_resumable_circularity_for_resumable_object_portion,
	    FIX((SI_Long)16L));
    Qadd_attribute_object_vector_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-VECTOR-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_object_vector_for_resumable_object_portion,
	    FIX((SI_Long)4L));
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    QFLOAT = STATIC_SYMBOL("float",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth = STATIC_SYMBOL("TRUTH",AB_package);
    Qadd_attribute_value_vector_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-VECTOR-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_value_vector_for_resumable_object_portion,
	    FIX((SI_Long)5L));
    Qevaluation_quantity_or_nil = 
	    STATIC_SYMBOL("EVALUATION-QUANTITY-OR-NIL",AB_package);
    Qadd_attribute_history_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-HISTORY-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_history_object_for_resumable_object_portion,
	    FIX((SI_Long)17L));
    Qadd_attribute_object_list_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-LIST-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_object_list_for_resumable_object_portion,
	    FIX((SI_Long)6L));
    Qadd_attribute_value_list_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-LIST-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_attribute_value_list_for_resumable_object_portion,
	    FIX((SI_Long)7L));
    Qadd_value_vector_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-VALUE-VECTOR-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_value_vector_range_for_resumable_object_portion,
	    FIX((SI_Long)8L));
    Qadd_homogeneous_value_vector_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_homogeneous_value_vector_range_for_resumable_object_portion,
	    FIX((SI_Long)14L));
    Qadd_history_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HISTORY-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_history_range_for_resumable_object_portion,
	    FIX((SI_Long)18L));
    Qadd_homogeneous_history_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-HISTORY-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_homogeneous_history_range_for_resumable_object_portion,
	    FIX((SI_Long)19L));
    Qadd_value_list_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-VALUE-LIST-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_value_list_range_for_resumable_object_portion,
	    FIX((SI_Long)9L));
    Qadd_homogeneous_value_list_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-VALUE-LIST-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qadd_homogeneous_value_list_range_for_resumable_object_portion,
	    FIX((SI_Long)15L));
    Qascend_to_parent_for_resumable_object_portion = 
	    STATIC_SYMBOL("ASCEND-TO-PARENT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qascend_to_parent_for_resumable_object_portion,
	    FIX((SI_Long)10L));
    Qsuspend_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("SUSPEND-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qsuspend_building_object_for_resumable_object_portion,
	    FIX((SI_Long)11L));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qexit_from_resumable_object_portion = 
	    STATIC_SYMBOL("EXIT-FROM-RESUMABLE-OBJECT-PORTION",AB_package);
    Qfinish_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("FINISH-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qfinish_building_object_for_resumable_object_portion,
	    FIX((SI_Long)12L));
    Qabort_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ABORT-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qabort_building_object_for_resumable_object_portion,
	    FIX((SI_Long)13L));
    Qresumable_object_portion = STATIC_SYMBOL("RESUMABLE-OBJECT-PORTION",
	    AB_package);
    Qresumable_node_indices = STATIC_SYMBOL("RESUMABLE-NODE-INDICES",
	    AB_package);
    Qitem_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qsend_icp_update_object_passing_network_resources = 
	    STATIC_SYMBOL("SEND-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    Qupdate_object_passing_network_resources = 
	    STATIC_SYMBOL("UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    string_constant_5 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qfreed = STATIC_SYMBOL("FREED",AB_package);
    string_constant_6 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qresumable_object_index = STATIC_SYMBOL("RESUMABLE-OBJECT-INDEX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_update_object_passing_network_resources,
	    STATIC_FUNCTION(send_icp_update_object_passing_network_resources,
	    NIL,FALSE,3,3));
    Qhandle_icp_update_object_passing_network_resources = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_update_object_passing_network_resources,
	    STATIC_FUNCTION(handle_icp_update_object_passing_network_resources,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_update_object_passing_network_resources,
	    FIX((SI_Long)321L));
    Qtoplevel_object_has_been_deleted_on_receiving_side = 
	    STATIC_SYMBOL("TOPLEVEL-OBJECT-HAS-BEEN-DELETED-ON-RECEIVING-SIDE",
	    AB_package);
    Qrpc_arg_list = STATIC_SYMBOL("RPC-ARG-LIST",AB_package);
    Qsend_icp_continue_building_resumable_object = 
	    STATIC_SYMBOL("SEND-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT",
	    AB_package);
    Qcontinue_building_resumable_object = 
	    STATIC_SYMBOL("CONTINUE-BUILDING-RESUMABLE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_continue_building_resumable_object,
	    STATIC_FUNCTION(send_icp_continue_building_resumable_object,
	    NIL,FALSE,1,1));
    Qhandle_icp_continue_building_resumable_object = 
	    STATIC_SYMBOL("HANDLE-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_continue_building_resumable_object,
	    STATIC_FUNCTION(handle_icp_continue_building_resumable_object,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_continue_building_resumable_object,
	    FIX((SI_Long)320L));
    list_constant_8 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_9 = STATIC_CONS(Qunsigned_byte,list_constant_8);
    array_constant = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qsend_icp_rpc_start = STATIC_SYMBOL("SEND-ICP-RPC-START",AB_package);
    Qrpc_start = STATIC_SYMBOL("RPC-START",AB_package);
    Qremote_procedure_name = STATIC_SYMBOL("REMOTE-PROCEDURE-NAME",AB_package);
    string_constant_7 = STATIC_STRING("[object arg]");
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_start,
	    STATIC_FUNCTION(send_icp_rpc_start,NIL,FALSE,2,2));
    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qhandle_icp_rpc_start = STATIC_SYMBOL("HANDLE-ICP-RPC-START",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_start,
	    STATIC_FUNCTION(handle_icp_rpc_start,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_start,FIX((SI_Long)230L));
    Qsend_icp_rpc_call = STATIC_SYMBOL("SEND-ICP-RPC-CALL",AB_package);
    Qrpc_call = STATIC_SYMBOL("RPC-CALL",AB_package);
    Qremote_procedure_identifier = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_call,
	    STATIC_FUNCTION(send_icp_rpc_call,NIL,FALSE,3,3));
    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    Qhandle_icp_rpc_call = STATIC_SYMBOL("HANDLE-ICP-RPC-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_call,
	    STATIC_FUNCTION(handle_icp_rpc_call,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_call,FIX((SI_Long)231L));
    Qsend_icp_rpc_return_values = 
	    STATIC_SYMBOL("SEND-ICP-RPC-RETURN-VALUES",AB_package);
    Qrpc_return_values = STATIC_SYMBOL("RPC-RETURN-VALUES",AB_package);
    Qcalling_procedure_index = STATIC_SYMBOL("CALLING-PROCEDURE-INDEX",
	    AB_package);
    Qreturn_values_list = STATIC_SYMBOL("RETURN-VALUES-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_return_values,
	    STATIC_FUNCTION(send_icp_rpc_return_values,NIL,FALSE,2,2));
    Qoutstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qreturned = STATIC_SYMBOL("RETURNED",AB_package);
    Qhandle_icp_rpc_return_values = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-RETURN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_return_values,
	    STATIC_FUNCTION(handle_icp_rpc_return_values,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_return_values,FIX((SI_Long)237L));
    Qsend_icp_rpc_error = STATIC_SYMBOL("SEND-ICP-RPC-ERROR",AB_package);
    Qcorresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    Qerror_name = STATIC_SYMBOL("ERROR-NAME",AB_package);
    Qerror_level = STATIC_SYMBOL("ERROR-LEVEL",AB_package);
    Qerror_description = STATIC_SYMBOL("ERROR-DESCRIPTION",AB_package);
    Qerror_argument_list = STATIC_SYMBOL("ERROR-ARGUMENT-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_error,
	    STATIC_FUNCTION(send_icp_rpc_error,NIL,FALSE,4,4));
    Qhandle_icp_rpc_error = STATIC_SYMBOL("HANDLE-ICP-RPC-ERROR",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_error,
	    STATIC_FUNCTION(handle_icp_rpc_error,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_error,FIX((SI_Long)232L));
    Qsend_icp_rpc_error_to_caller = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ERROR-TO-CALLER",AB_package);
    Qrpc_error_to_caller = STATIC_SYMBOL("RPC-ERROR-TO-CALLER",AB_package);
    Qremote_caller_index = STATIC_SYMBOL("REMOTE-CALLER-INDEX",AB_package);
    Qsignaller_qm = STATIC_SYMBOL("SIGNALLER\?",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_rpc_error_to_caller,
	    STATIC_FUNCTION(send_icp_rpc_error_to_caller,NIL,FALSE,6,6));
    Qsync_abort = STATIC_SYMBOL("SYNC-ABORT",AB_package);
    Qhandle_icp_rpc_error_to_caller = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ERROR-TO-CALLER",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_rpc_error_to_caller,
	    STATIC_FUNCTION(handle_icp_rpc_error_to_caller,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_rpc_error_to_caller,
	    FIX((SI_Long)233L));
}
