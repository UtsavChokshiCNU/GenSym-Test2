/* rpcmn2.c
 * Input file:  rpc-common2.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rpcmn2.h"


/* RECLAIM-RESUMABLE-ATTRIBUTE-SPEC-FUNCTION */
Object g2int_reclaim_resumable_attribute_spec_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(47,0);
    temp = CONSP(x) ? g2int_reclaim_gensym_list_1(x) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-RESUMABLE-ATTRIBUTE-SPEC-IF-ANY-FUNCTION */
Object g2int_reclaim_resumable_attribute_spec_if_any_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(47,1);
    temp = CONSP(x) ? g2int_reclaim_gensym_list_1(x) : Nil;
    return VALUES_1(temp);
}

static Object Qg2int_class_qualified_name;  /* class-qualified-name */

/* SET-RESUMABLE-ATTRIBUTE-TYPE */
Object g2int_set_resumable_attribute_type(resumable_attribute_spec,value)
    Object resumable_attribute_spec, value;
{
    x_note_fn_call(47,2);
    if (CONSP(resumable_attribute_spec) &&  
	    !EQ(M_CAR(resumable_attribute_spec),Qg2int_class_qualified_name))
	return VALUES_1(M_CAR(resumable_attribute_spec) = value);
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_resumable_object_mixin = UNBOUND;

Object G2int_chain_of_available_resumable_object_mixins = UNBOUND;

Object G2int_resumable_object_mixin_count = UNBOUND;

/* RECLAIM-RESUMABLE-OBJECT-MIXIN-1 */
Object g2int_reclaim_resumable_object_mixin_1(resumable_object_mixin)
    Object resumable_object_mixin;
{
    Object svref_new_value;

    x_note_fn_call(47,3);
    inline_note_reclaim_cons(resumable_object_mixin,Nil);
    svref_new_value = G2int_chain_of_available_resumable_object_mixins;
    SVREF(resumable_object_mixin,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_resumable_object_mixins = resumable_object_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-OBJECT-MIXIN */
Object g2int_reclaim_structure_for_resumable_object_mixin(resumable_object_mixin)
    Object resumable_object_mixin;
{
    x_note_fn_call(47,4);
    return g2int_reclaim_resumable_object_mixin_1(resumable_object_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-object-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-OBJECT-MIXIN-STRUCTURE-INTERNAL */
Object g2int_make_permanent_resumable_object_mixin_structure_internal()
{
    Object def_structure_resumable_object_mixin_variable;
    Object resumable_object_mixin_count_new_value;
    Object defstruct_g2_resumable_object_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,5);
    def_structure_resumable_object_mixin_variable = Nil;
    resumable_object_mixin_count_new_value = 
	    FIXNUM_ADD1(G2int_resumable_object_mixin_count);
    G2int_resumable_object_mixin_count = 
	    resumable_object_mixin_count_new_value;
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
Object g2int_make_resumable_object_mixin_1()
{
    Object def_structure_resumable_object_mixin_variable;

    x_note_fn_call(47,6);
    def_structure_resumable_object_mixin_variable = 
	    G2int_chain_of_available_resumable_object_mixins;
    if (def_structure_resumable_object_mixin_variable) {
	G2int_chain_of_available_resumable_object_mixins = 
		ISVREF(def_structure_resumable_object_mixin_variable,
		(SI_Long)0L);
	SVREF(def_structure_resumable_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct;
    }
    else
	def_structure_resumable_object_mixin_variable = 
		g2int_make_permanent_resumable_object_mixin_structure_internal();
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

Object G2int_the_type_description_of_resumable_icp_object_mixin = UNBOUND;

Object G2int_chain_of_available_resumable_icp_object_mixins = UNBOUND;

Object G2int_resumable_icp_object_mixin_count = UNBOUND;

/* RECLAIM-RESUMABLE-ICP-OBJECT-MIXIN-1 */
Object g2int_reclaim_resumable_icp_object_mixin_1(resumable_icp_object_mixin)
    Object resumable_icp_object_mixin;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(47,7);
    inline_note_reclaim_cons(resumable_icp_object_mixin,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = resumable_icp_object_mixin;
    g2int_reclaim_gensym_list_1(ISVREF(resumable_icp_object_mixin,
	    (SI_Long)7L));
    SVREF(resumable_icp_object_mixin,FIX((SI_Long)7L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_resumable_icp_object_mixins;
    SVREF(resumable_icp_object_mixin,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_resumable_icp_object_mixins = 
	    resumable_icp_object_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-ICP-OBJECT-MIXIN */
Object g2int_reclaim_structure_for_resumable_icp_object_mixin(resumable_icp_object_mixin)
    Object resumable_icp_object_mixin;
{
    x_note_fn_call(47,8);
    return g2int_reclaim_resumable_icp_object_mixin_1(resumable_icp_object_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-icp-object-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-ICP-OBJECT-MIXIN-STRUCTURE-INTERNAL */
Object g2int_make_permanent_resumable_icp_object_mixin_structure_internal()
{
    Object def_structure_resumable_icp_object_mixin_variable, temp;
    Object defstruct_g2_resumable_icp_object_mixin_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,9);
    def_structure_resumable_icp_object_mixin_variable = Nil;
    temp = FIXNUM_ADD1(G2int_resumable_icp_object_mixin_count);
    G2int_resumable_icp_object_mixin_count = temp;
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
	temp = G2int_chain_of_available_resumable_icp_object_mixins;
	SVREF(def_structure_resumable_icp_object_mixin_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_resumable_icp_object_mixins = 
		def_structure_resumable_icp_object_mixin_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_resumable_icp_object_mixin_variable);
}

/* MAKE-RESUMABLE-ICP-OBJECT-MIXIN-1 */
Object g2int_make_resumable_icp_object_mixin_1()
{
    Object def_structure_resumable_icp_object_mixin_variable;

    x_note_fn_call(47,10);
    def_structure_resumable_icp_object_mixin_variable = 
	    G2int_chain_of_available_resumable_icp_object_mixins;
    if (def_structure_resumable_icp_object_mixin_variable) {
	G2int_chain_of_available_resumable_icp_object_mixins = 
		ISVREF(def_structure_resumable_icp_object_mixin_variable,
		(SI_Long)0L);
	SVREF(def_structure_resumable_icp_object_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct;
    }
    else
	def_structure_resumable_icp_object_mixin_variable = 
		g2int_make_permanent_resumable_icp_object_mixin_structure_internal();
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

Object G2int_the_type_description_of_resumable_node_mixin = UNBOUND;

Object G2int_chain_of_available_resumable_node_mixins = UNBOUND;

Object G2int_resumable_node_mixin_count = UNBOUND;

/* RECLAIM-RESUMABLE-NODE-MIXIN-1 */
Object g2int_reclaim_resumable_node_mixin_1(resumable_node_mixin)
    Object resumable_node_mixin;
{
    Object old_structure_being_reclaimed, resumable_attribute_spec_qm;
    Object svref_new_value;

    x_note_fn_call(47,11);
    inline_note_reclaim_cons(resumable_node_mixin,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = resumable_node_mixin;
    resumable_attribute_spec_qm = ISVREF(resumable_node_mixin,(SI_Long)2L);
    if (CONSP(resumable_attribute_spec_qm))
	g2int_reclaim_gensym_list_1(resumable_attribute_spec_qm);
    SVREF(resumable_node_mixin,FIX((SI_Long)2L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_resumable_node_mixins;
    SVREF(resumable_node_mixin,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_resumable_node_mixins = resumable_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-NODE-MIXIN */
Object g2int_reclaim_structure_for_resumable_node_mixin(resumable_node_mixin)
    Object resumable_node_mixin;
{
    x_note_fn_call(47,12);
    return g2int_reclaim_resumable_node_mixin_1(resumable_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-NODE-MIXIN-STRUCTURE-INTERNAL */
Object g2int_make_permanent_resumable_node_mixin_structure_internal()
{
    Object def_structure_resumable_node_mixin_variable;
    Object resumable_node_mixin_count_new_value;
    Object defstruct_g2_resumable_node_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,13);
    def_structure_resumable_node_mixin_variable = Nil;
    resumable_node_mixin_count_new_value = 
	    FIXNUM_ADD1(G2int_resumable_node_mixin_count);
    G2int_resumable_node_mixin_count = resumable_node_mixin_count_new_value;
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
Object g2int_make_resumable_node_mixin_1()
{
    Object def_structure_resumable_node_mixin_variable;

    x_note_fn_call(47,14);
    def_structure_resumable_node_mixin_variable = 
	    G2int_chain_of_available_resumable_node_mixins;
    if (def_structure_resumable_node_mixin_variable) {
	G2int_chain_of_available_resumable_node_mixins = 
		ISVREF(def_structure_resumable_node_mixin_variable,
		(SI_Long)0L);
	SVREF(def_structure_resumable_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_node_mixin_variable = 
		g2int_make_permanent_resumable_node_mixin_structure_internal();
    inline_note_allocate_cons(def_structure_resumable_node_mixin_variable,Nil);
    SVREF(def_structure_resumable_node_mixin_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_resumable_node_mixin_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_resumable_node_mixin_variable);
}

Object G2int_the_type_description_of_resumable_icp_node_mixin = UNBOUND;

Object G2int_chain_of_available_resumable_icp_node_mixins = UNBOUND;

Object G2int_resumable_icp_node_mixin_count = UNBOUND;

/* RECLAIM-RESUMABLE-ICP-NODE-MIXIN-1 */
Object g2int_reclaim_resumable_icp_node_mixin_1(resumable_icp_node_mixin)
    Object resumable_icp_node_mixin;
{
    Object old_structure_being_reclaimed, resumable_attribute_spec_qm;
    Object svref_new_value;

    x_note_fn_call(47,15);
    inline_note_reclaim_cons(resumable_icp_node_mixin,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = resumable_icp_node_mixin;
    resumable_attribute_spec_qm = ISVREF(resumable_icp_node_mixin,(SI_Long)2L);
    if (CONSP(resumable_attribute_spec_qm))
	g2int_reclaim_gensym_list_1(resumable_attribute_spec_qm);
    SVREF(resumable_icp_node_mixin,FIX((SI_Long)2L)) = Nil;
    g2int_reclaim_gensym_list_1(ISVREF(resumable_icp_node_mixin,(SI_Long)3L));
    SVREF(resumable_icp_node_mixin,FIX((SI_Long)3L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_resumable_icp_node_mixins;
    SVREF(resumable_icp_node_mixin,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_resumable_icp_node_mixins = 
	    resumable_icp_node_mixin;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RESUMABLE-ICP-NODE-MIXIN */
Object g2int_reclaim_structure_for_resumable_icp_node_mixin(resumable_icp_node_mixin)
    Object resumable_icp_node_mixin;
{
    x_note_fn_call(47,16);
    return g2int_reclaim_resumable_icp_node_mixin_1(resumable_icp_node_mixin);
}

static Object Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct;  /* g2-defstruct-structure-name::resumable-icp-node-mixin-g2-struct */

/* MAKE-PERMANENT-RESUMABLE-ICP-NODE-MIXIN-STRUCTURE-INTERNAL */
Object g2int_make_permanent_resumable_icp_node_mixin_structure_internal()
{
    Object def_structure_resumable_icp_node_mixin_variable;
    Object resumable_icp_node_mixin_count_new_value;
    Object defstruct_g2_resumable_icp_node_mixin_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,17);
    def_structure_resumable_icp_node_mixin_variable = Nil;
    resumable_icp_node_mixin_count_new_value = 
	    FIXNUM_ADD1(G2int_resumable_icp_node_mixin_count);
    G2int_resumable_icp_node_mixin_count = 
	    resumable_icp_node_mixin_count_new_value;
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
Object g2int_make_resumable_icp_node_mixin_1()
{
    Object def_structure_resumable_icp_node_mixin_variable;

    x_note_fn_call(47,18);
    def_structure_resumable_icp_node_mixin_variable = 
	    G2int_chain_of_available_resumable_icp_node_mixins;
    if (def_structure_resumable_icp_node_mixin_variable) {
	G2int_chain_of_available_resumable_icp_node_mixins = 
		ISVREF(def_structure_resumable_icp_node_mixin_variable,
		(SI_Long)0L);
	SVREF(def_structure_resumable_icp_node_mixin_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct;
    }
    else
	def_structure_resumable_icp_node_mixin_variable = 
		g2int_make_permanent_resumable_icp_node_mixin_structure_internal();
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

Object G2int_current_receiving_resumable_object = UNBOUND;

Object G2int_the_type_description_of_receiving_resumable_object = UNBOUND;

Object G2int_chain_of_available_receiving_resumable_objects = UNBOUND;

Object G2int_receiving_resumable_object_count = UNBOUND;

/* RECLAIM-RECEIVING-RESUMABLE-OBJECT-INTERNAL-1 */
Object g2int_reclaim_receiving_resumable_object_internal_1(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(47,19);
    inline_note_reclaim_cons(receiving_resumable_object,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = receiving_resumable_object;
    g2int_reclaim_object_building_problem_if_any(ISVREF(receiving_resumable_object,
	    (SI_Long)10L));
    SVREF(receiving_resumable_object,FIX((SI_Long)10L)) = Nil;
    g2int_reclaim_icp_list_of_rpc_arglist_structures(ISVREF(receiving_resumable_object,
	    (SI_Long)13L));
    SVREF(receiving_resumable_object,FIX((SI_Long)13L)) = Nil;
    g2int_reclaim_evaluation_value_if_any_function(ISVREF(receiving_resumable_object,
	    (SI_Long)14L));
    SVREF(receiving_resumable_object,FIX((SI_Long)14L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_receiving_resumable_objects;
    SVREF(receiving_resumable_object,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_receiving_resumable_objects = 
	    receiving_resumable_object;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RECEIVING-RESUMABLE-OBJECT */
Object g2int_reclaim_structure_for_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    x_note_fn_call(47,20);
    return g2int_reclaim_receiving_resumable_object_internal_1(receiving_resumable_object);
}

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

/* MAKE-PERMANENT-RECEIVING-RESUMABLE-OBJECT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_receiving_resumable_object_structure_internal()
{
    Object def_structure_receiving_resumable_object_variable, temp;
    Object defstruct_g2_receiving_resumable_object_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,21);
    def_structure_receiving_resumable_object_variable = Nil;
    temp = FIXNUM_ADD1(G2int_receiving_resumable_object_count);
    G2int_receiving_resumable_object_count = temp;
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
	temp = G2int_chain_of_available_receiving_resumable_objects;
	SVREF(def_structure_receiving_resumable_object_variable,
		FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_receiving_resumable_objects = 
		def_structure_receiving_resumable_object_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_receiving_resumable_object_variable);
}

/* MAKE-RECEIVING-RESUMABLE-OBJECT-1 */
Object g2int_make_receiving_resumable_object_1()
{
    Object def_structure_receiving_resumable_object_variable;

    x_note_fn_call(47,22);
    def_structure_receiving_resumable_object_variable = 
	    G2int_chain_of_available_receiving_resumable_objects;
    if (def_structure_receiving_resumable_object_variable) {
	G2int_chain_of_available_receiving_resumable_objects = 
		ISVREF(def_structure_receiving_resumable_object_variable,
		(SI_Long)0L);
	SVREF(def_structure_receiving_resumable_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;
    }
    else
	def_structure_receiving_resumable_object_variable = 
		g2int_make_permanent_receiving_resumable_object_structure_internal();
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
Object g2int_reclaim_text_or_gensym_string_if_any(text_string_qm)
    Object text_string_qm;
{
    x_note_fn_call(47,23);
    if (text_string_qm)
	return g2int_reclaim_text_or_gensym_string(text_string_qm);
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_object_building_problem = UNBOUND;

Object G2int_chain_of_available_object_building_problems = UNBOUND;

Object G2int_object_building_problem_count = UNBOUND;

/* RECLAIM-OBJECT-BUILDING-PROBLEM-1 */
Object g2int_reclaim_object_building_problem_1(object_building_problem)
    Object object_building_problem;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(47,24);
    inline_note_reclaim_cons(object_building_problem,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = object_building_problem;
    g2int_reclaim_text_or_gensym_string_if_any(ISVREF(object_building_problem,
	    (SI_Long)2L));
    SVREF(object_building_problem,FIX((SI_Long)2L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_object_building_problems;
    SVREF(object_building_problem,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_object_building_problems = 
	    object_building_problem;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-OBJECT-BUILDING-PROBLEM */
Object g2int_reclaim_structure_for_object_building_problem(object_building_problem)
    Object object_building_problem;
{
    x_note_fn_call(47,25);
    return g2int_reclaim_object_building_problem_1(object_building_problem);
}

static Object Qg2_defstruct_structure_name_object_building_problem_g2_struct;  /* g2-defstruct-structure-name::object-building-problem-g2-struct */

/* MAKE-PERMANENT-OBJECT-BUILDING-PROBLEM-STRUCTURE-INTERNAL */
Object g2int_make_permanent_object_building_problem_structure_internal()
{
    Object def_structure_object_building_problem_variable;
    Object object_building_problem_count_new_value;
    Object defstruct_g2_object_building_problem_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,26);
    def_structure_object_building_problem_variable = Nil;
    object_building_problem_count_new_value = 
	    FIXNUM_ADD1(G2int_object_building_problem_count);
    G2int_object_building_problem_count = 
	    object_building_problem_count_new_value;
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
Object g2int_make_object_building_problem_1(object_building_problem_name,
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
    Object def_structure_object_building_problem_variable;

    x_note_fn_call(47,27);
    def_structure_object_building_problem_variable = 
	    G2int_chain_of_available_object_building_problems;
    if (def_structure_object_building_problem_variable) {
	G2int_chain_of_available_object_building_problems = 
		ISVREF(def_structure_object_building_problem_variable,
		(SI_Long)0L);
	SVREF(def_structure_object_building_problem_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_object_building_problem_g2_struct;
    }
    else
	def_structure_object_building_problem_variable = 
		g2int_make_permanent_object_building_problem_structure_internal();
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
Object g2int_record_object_building_problem_on_receiving_side_1(problem_name,
	    attribute_qualifier_qm,attribute_name_or_index_qm,class_name,
	    info_format,info_args_qm,info_reclaimer_qm)
    Object problem_name, attribute_qualifier_qm, attribute_name_or_index_qm;
    Object class_name, info_format, info_args_qm, info_reclaimer_qm;
{
    Object old_problem_qm, info_arg, ab_loop_list_, svref_arg_1;
    Object attribute_text, svref_new_value;

    x_note_fn_call(47,28);
    old_problem_qm = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)10L);
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
	svref_arg_1 = G2int_current_receiving_resumable_object;
	if (attribute_qualifier_qm && attribute_name_or_index_qm)
	    attribute_text = g2int_tformat_text_string(3,string_constant,
		    attribute_qualifier_qm,attribute_name_or_index_qm);
	else if (attribute_name_or_index_qm)
	    attribute_text = g2int_tformat_text_string(2,string_constant_1,
		    attribute_name_or_index_qm);
	else
	    attribute_text = g2int_tformat_text_string(1,string_constant_2);
	svref_new_value = 
		g2int_make_object_building_problem_1(problem_name,
		attribute_text,class_name,info_format,info_reclaimer_qm,
		info_args_qm);
	SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-OBJECT-BUILDING-PROBLEM-IF-ANY */
Object g2int_reclaim_object_building_problem_if_any(object_building_problem_qm)
    Object object_building_problem_qm;
{
    Object info_reclaimer_qm, extra_info_item, ab_loop_list_;

    x_note_fn_call(47,29);
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
	g2int_reclaim_object_building_problem_1(object_building_problem_qm);
    }
    return VALUES_1(Nil);
}

static Object Qg2int_output;       /* output */

static Object Qg2int_input;        /* input */

/* RECLAIM-RESUMABLE-OBJECT */
Object g2int_reclaim_resumable_object(resumable_object,icp_port)
    Object resumable_object, icp_port;
{
    Object temp;

    x_note_fn_call(47,30);
    temp = ISVREF(icp_port,(SI_Long)3L);
    if (EQ(temp,Qg2int_output))
	return g2int_g2_reclaim_sending_resumable_object(resumable_object);
    else if (EQ(temp,Qg2int_input))
	return g2int_reclaim_single_receiving_resumable_object(resumable_object);
    else
	return VALUES_1(Qnil);
}

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-OBJECT */
Object g2int_establish_new_object_index_for_resumable_object varargs_1(int, n)
{
    Object resumable_object, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(47,31);
    INIT_ARGS_nonrelocating();
    resumable_object = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = g2int_assign_corresponding_icp_object_index(resumable_object,
	    Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
    MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_object,(SI_Long)7L)));
    SVREF(resumable_object,FIX((SI_Long)7L)) = svref_new_value;
    if (send_enlarge_message_p)
	return VALUES_1(corresponding_icp_object_index);
    else
	return VALUES_2(corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
}

/* MAKE-CORRESPONDING-ICP-RESUMABLE-OBJECT */
Object g2int_make_corresponding_icp_resumable_object(resumable_object)
    Object resumable_object;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,32);
    g2int_write_icp_maybe_suspend();
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      result = g2int_assign_corresponding_icp_object_index(resumable_object,
	      Qg2int_standard_icp_object_index_space,T);
      MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
      svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
	      g2int_gensym_cons_1(corresponding_icp_object_index,
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
Object g2int_get_icp_object_index_for_resumable_object(resumable_object,
	    icp_port)
    Object resumable_object, icp_port;
{
    x_note_fn_call(47,33);
    return g2int_getfq_function_no_default(ISVREF(resumable_object,
	    (SI_Long)7L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-RESUMABLE-OBJECT */
Object g2int_set_icp_object_index_for_resumable_object(resumable_object,
	    corresponding_icp_object_index,icp_port)
    Object resumable_object, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(47,34);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_object,(SI_Long)7L)));
    return VALUES_1(SVREF(resumable_object,FIX((SI_Long)7L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-RESUMABLE-OBJECT */
Object g2int_reclaim_icp_object_map_for_resumable_object(resumable_object)
    Object resumable_object;
{
    Object icp_object_map;

    x_note_fn_call(47,35);
    icp_object_map = ISVREF(resumable_object,(SI_Long)7L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(resumable_object,
		icp_object_map,Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_resumable_object;  /* set-access-form-for-resumable-object */

/* RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-OBJECT */
Object g2int_reclaim_icp_port_entry_for_resumable_object(resumable_object,
	    icp_port)
    Object resumable_object, icp_port;
{
    x_note_fn_call(47,36);
    return g2int_reclaim_icp_port_entry(icp_port,resumable_object,
	    ISVREF(resumable_object,(SI_Long)7L),
	    Qg2int_set_access_form_for_resumable_object);
}

/* SET-ACCESS-FORM-FOR-RESUMABLE-OBJECT */
Object g2int_set_access_form_for_resumable_object(resumable_object,new_value)
    Object resumable_object, new_value;
{
    x_note_fn_call(47,37);
    return VALUES_1(SVREF(resumable_object,FIX((SI_Long)7L)) = new_value);
}

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_establish_new_object_index_for_resumable_instance_node varargs_1(int, n)
{
    Object resumable_instance_node, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(47,38);
    INIT_ARGS_nonrelocating();
    resumable_instance_node = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = g2int_assign_corresponding_icp_object_index(resumable_instance_node,
	    Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
    MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_instance_node,(SI_Long)3L)));
    SVREF(resumable_instance_node,FIX((SI_Long)3L)) = svref_new_value;
    if (send_enlarge_message_p)
	return VALUES_1(corresponding_icp_object_index);
    else
	return VALUES_2(corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
}

/* MAKE-CORRESPONDING-ICP-RESUMABLE-INSTANCE-NODE */
Object g2int_make_corresponding_icp_resumable_instance_node(resumable_instance_node)
    Object resumable_instance_node;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,39);
    g2int_write_icp_maybe_suspend();
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      result = g2int_assign_corresponding_icp_object_index(resumable_instance_node,
	      Qg2int_standard_icp_object_index_space,T);
      MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
      svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
	      g2int_gensym_cons_1(corresponding_icp_object_index,
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
Object g2int_get_icp_object_index_for_resumable_instance_node(resumable_instance_node,
	    icp_port)
    Object resumable_instance_node, icp_port;
{
    x_note_fn_call(47,40);
    return g2int_getfq_function_no_default(ISVREF(resumable_instance_node,
	    (SI_Long)3L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_set_icp_object_index_for_resumable_instance_node(resumable_instance_node,
	    corresponding_icp_object_index,icp_port)
    Object resumable_instance_node, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(47,41);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(resumable_instance_node,(SI_Long)3L)));
    return VALUES_1(SVREF(resumable_instance_node,FIX((SI_Long)3L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_reclaim_icp_object_map_for_resumable_instance_node(resumable_instance_node)
    Object resumable_instance_node;
{
    Object icp_object_map;

    x_note_fn_call(47,42);
    icp_object_map = ISVREF(resumable_instance_node,(SI_Long)3L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(resumable_instance_node,
		icp_object_map,Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_resumable_instance_node;  /* set-access-form-for-resumable-instance-node */

/* RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_reclaim_icp_port_entry_for_resumable_instance_node(resumable_instance_node,
	    icp_port)
    Object resumable_instance_node, icp_port;
{
    x_note_fn_call(47,43);
    return g2int_reclaim_icp_port_entry(icp_port,resumable_instance_node,
	    ISVREF(resumable_instance_node,(SI_Long)3L),
	    Qg2int_set_access_form_for_resumable_instance_node);
}

/* SET-ACCESS-FORM-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_set_access_form_for_resumable_instance_node(resumable_instance_node,
	    new_value)
    Object resumable_instance_node, new_value;
{
    x_note_fn_call(47,44);
    return VALUES_1(SVREF(resumable_instance_node,FIX((SI_Long)3L)) = 
	    new_value);
}

Object G2int_the_type_description_of_receiving_rpc_arglist_structure = UNBOUND;

Object G2int_chain_of_available_receiving_rpc_arglist_structures = UNBOUND;

Object G2int_receiving_rpc_arglist_structure_count = UNBOUND;

/* RECLAIM-RECEIVING-RPC-ARGLIST-STRUCTURE-1 */
Object g2int_reclaim_receiving_rpc_arglist_structure_1(receiving_rpc_arglist_structure)
    Object receiving_rpc_arglist_structure;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(47,45);
    inline_note_reclaim_cons(receiving_rpc_arglist_structure,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = receiving_rpc_arglist_structure;
    g2int_reclaim_icp_list_with_some_resumable_objects(ISVREF(receiving_rpc_arglist_structure,
	    (SI_Long)1L));
    SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)1L)) = Nil;
    g2int_reclaim_gensym_list_1(ISVREF(receiving_rpc_arglist_structure,
	    (SI_Long)6L));
    SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)6L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = 
	    G2int_chain_of_available_receiving_rpc_arglist_structures;
    SVREF(receiving_rpc_arglist_structure,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_receiving_rpc_arglist_structures = 
	    receiving_rpc_arglist_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RECEIVING-RPC-ARGLIST-STRUCTURE */
Object g2int_reclaim_structure_for_receiving_rpc_arglist_structure(receiving_rpc_arglist_structure)
    Object receiving_rpc_arglist_structure;
{
    x_note_fn_call(47,46);
    return g2int_reclaim_receiving_rpc_arglist_structure_1(receiving_rpc_arglist_structure);
}

static Object Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct;  /* g2-defstruct-structure-name::receiving-rpc-arglist-structure-g2-struct */

/* MAKE-PERMANENT-RECEIVING-RPC-ARGLIST-STRUCTURE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_receiving_rpc_arglist_structure_structure_internal()
{
    Object def_structure_receiving_rpc_arglist_structure_variable;
    Object receiving_rpc_arglist_structure_count_new_value;
    Object defstruct_g2_receiving_rpc_arglist_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(47,47);
    def_structure_receiving_rpc_arglist_structure_variable = Nil;
    receiving_rpc_arglist_structure_count_new_value = 
	    FIXNUM_ADD1(G2int_receiving_rpc_arglist_structure_count);
    G2int_receiving_rpc_arglist_structure_count = 
	    receiving_rpc_arglist_structure_count_new_value;
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
Object g2int_make_receiving_rpc_arglist_structure_1()
{
    Object def_structure_receiving_rpc_arglist_structure_variable;

    x_note_fn_call(47,48);
    def_structure_receiving_rpc_arglist_structure_variable = 
	    G2int_chain_of_available_receiving_rpc_arglist_structures;
    if (def_structure_receiving_rpc_arglist_structure_variable) {
	G2int_chain_of_available_receiving_rpc_arglist_structures = 
		ISVREF(def_structure_receiving_rpc_arglist_structure_variable,
		(SI_Long)0L);
	SVREF(def_structure_receiving_rpc_arglist_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct;
    }
    else
	def_structure_receiving_rpc_arglist_structure_variable = 
		g2int_make_permanent_receiving_rpc_arglist_structure_structure_internal();
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
Object g2int_reclaim_icp_list_of_rpc_arglist_structures(rpc_arglist_structures)
    Object rpc_arglist_structures;
{
    Object rpc_arglist_structure, ab_loop_list_;

    x_note_fn_call(47,49);
    rpc_arglist_structure = Nil;
    ab_loop_list_ = rpc_arglist_structures;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rpc_arglist_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_receiving_rpc_arglist_structure_1(rpc_arglist_structure);
    goto next_loop;
  end_loop:;
    return g2int_reclaim_gensym_list_1(rpc_arglist_structures);
}

/* RECLAIM-ICP-LIST-WITH-SOME-RESUMABLE-OBJECTS */
Object g2int_reclaim_icp_list_with_some_resumable_objects(icp_list)
    Object icp_list;
{
    Object possible_resumable_object, ab_loop_list_;

    x_note_fn_call(47,50);
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
	g2int_reclaim_single_receiving_resumable_object(possible_resumable_object);
    }
    goto next_loop;
  end_loop:;
    return g2int_reclaim_gensym_list_1(icp_list);
}

/* RECLAIM-SINGLE-RECEIVING-RESUMABLE-OBJECT */
Object g2int_reclaim_single_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object rpc_identifier_qm, svref_new_value;

    x_note_fn_call(47,51);
    rpc_identifier_qm = ISVREF(receiving_resumable_object,(SI_Long)5L);
    if (rpc_identifier_qm) {
	svref_new_value = 
		g2int_delete_gensym_element_1(receiving_resumable_object,
		ISVREF(rpc_identifier_qm,(SI_Long)5L));
	SVREF(rpc_identifier_qm,FIX((SI_Long)5L)) = svref_new_value;
    }
    return g2int_reclaim_receiving_resumable_object_internal_1(receiving_resumable_object);
}

/* RECLAIM-RECEIVING-RESUMABLE-OBJECT */
Object g2int_reclaim_receiving_resumable_object(receiving_resumable_object)
    Object receiving_resumable_object;
{
    Object arglist_structure_qm, initial_resumable_var;
    Object receiving_resumable_object_1;

    x_note_fn_call(47,52);
    arglist_structure_qm = ISVREF(receiving_resumable_object,(SI_Long)9L);
    if (arglist_structure_qm)
	return g2int_reclaim_receiving_rpc_arglist_structure_1(arglist_structure_qm);
    else {
	initial_resumable_var = ISVREF(receiving_resumable_object,(SI_Long)3L);
	receiving_resumable_object_1 = initial_resumable_var;
      next_loop:
	if ( !TRUEP(receiving_resumable_object_1))
	    goto end_loop;
	g2int_reclaim_single_receiving_resumable_object(receiving_resumable_object_1);
	receiving_resumable_object_1 = ISVREF(receiving_resumable_object_1,
		(SI_Long)3L);
	goto next_loop;
      end_loop:;
	initial_resumable_var = ISVREF(receiving_resumable_object,(SI_Long)4L);
	receiving_resumable_object_1 = initial_resumable_var;
      next_loop_1:
	if ( !TRUEP(receiving_resumable_object_1))
	    goto end_loop_1;
	g2int_reclaim_single_receiving_resumable_object(receiving_resumable_object_1);
	receiving_resumable_object_1 = ISVREF(receiving_resumable_object_1,
		(SI_Long)4L);
	goto next_loop_1;
      end_loop_1:;
	return g2int_reclaim_single_receiving_resumable_object(receiving_resumable_object);
    }
}

static Object Qg2int_gsi_reference_flag;  /* gsi-reference-flag */

static Object list_constant;       /* # */

/* GSI-ITEM-IS-VALUE-P */
Object g2int_gsi_item_is_value_p(gsi_item)
    Object gsi_item;
{
    Object gsi_instance_extension;
    char temp;

    x_note_fn_call(47,53);
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    temp = gsi_instance_extension ? TRUEP(ISVREF(gsi_instance_extension,
	    (SI_Long)2L)) : TRUEP(Nil);
    if (temp);
    else
	temp = TRUEP(g2int_get_gsi_instance_plist_value(gsi_item,
		Qg2int_gsi_reference_flag));
    if (temp);
    else
	temp = ISVREF(gsi_item,(SI_Long)2L) ? 
		TRUEP(g2int_memq_function(FIX(IFIX(ISVREF(gsi_item,
		(SI_Long)1L)) >>  -  - (SI_Long)3L),list_constant)) : 
		TRUEP(Qnil);
    return VALUES_1( !temp ? T : Nil);
}

static Object Qg2int_integer_array;  /* integer-array */

static Object Qg2int_symbol_array;  /* symbol-array */

static Object Qg2int_text_array;   /* text-array */

static Object Qg2int_truth_value_array;  /* truth-value-array */

static Object Qg2int_float_array;  /* float-array */

static Object Qg2int_g2_array;     /* g2-array */

static Object Qg2int_quantity_array;  /* quantity-array */

static Object Qg2int_item_array;   /* item-array */

static Object Qg2int_value_array;  /* value-array */

static Object Qg2int_integer_list;  /* integer-list */

static Object Qg2int_symbol_list;  /* symbol-list */

static Object Qg2int_text_list;    /* text-list */

static Object Qg2int_truth_value_list;  /* truth-value-list */

static Object Qg2int_float_list;   /* float-list */

static Object Qg2int_g2_list;      /* g2-list */

static Object Qg2int_quantity_list;  /* quantity-list */

static Object Qg2int_item_list;    /* item-list */

static Object Qg2int_value_list;   /* value-list */

/* CLASS-FOR-GSI-ITEM */
Object g2int_class_for_gsi_item(gsi_item)
    Object gsi_item;
{
    Object gsi_instance_extension, temp, class_1;
    SI_Long temp_1;

    x_note_fn_call(47,54);
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
		class_1 = Qg2int_integer_array;
		break;
	      case 19:
		class_1 = Qg2int_symbol_array;
		break;
	      case 20:
		class_1 = Qg2int_text_array;
		break;
	      case 21:
		class_1 = Qg2int_truth_value_array;
		break;
	      case 22:
		class_1 = Qg2int_float_array;
		break;
	      case 25:
		class_1 = Qg2int_g2_array;
		break;
	      case 26:
		class_1 = Qg2int_quantity_array;
		break;
	      case 23:
		class_1 = Qg2int_item_array;
		break;
	      case 24:
		class_1 = Qg2int_value_array;
		break;
	      case 33:
		class_1 = Qg2int_integer_list;
		break;
	      case 35:
		class_1 = Qg2int_symbol_list;
		break;
	      case 36:
		class_1 = Qg2int_text_list;
		break;
	      case 37:
		class_1 = Qg2int_truth_value_list;
		break;
	      case 38:
		class_1 = Qg2int_float_list;
		break;
	      case 41:
		class_1 = Qg2int_g2_list;
		break;
	      case 42:
		class_1 = Qg2int_quantity_list;
		break;
	      case 39:
		class_1 = Qg2int_item_list;
		break;
	      case 40:
		class_1 = Qg2int_value_list;
		break;
	      default:
		class_1 = Nil;
		break;
	    }
	if (class_1) {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    if ( !TRUEP(gsi_instance_extension)) {
		gsi_instance_extension = g2int_make_gsi_instance_extension_1();
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

static Object Qg2_defstruct_structure_name_gsi_instance_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-g2-struct */

static Object Qg2int_write_rpc_argument;  /* write_rpc_argument */

static Object Qg2int_gsi_instance_squirrelled_index;  /* gsi-instance-squirrelled-index */

/* WRITE-ICP-RPC-VALUE-OR-OBJECT */
Object g2int_write_icp_rpc_value_or_object(rpc_value_or_object)
    Object rpc_value_or_object;
{
    Object value_type, gsi_instance_index, gsi_extension_data_qm;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value, value;
    char copy_string_value_p;

    x_note_fn_call(47,55);
    if ( !(SIMPLE_VECTOR_P(rpc_value_or_object) && 
	    EQ(ISVREF(rpc_value_or_object,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_instance_g2_struct)))
	g2int_gsi_connection_error(2,Qg2int_write_rpc_argument,
		G2int_gsi_incompatible_structure);
    value_type = FIX(IFIX(ISVREF(rpc_value_or_object,(SI_Long)1L)) >>  -  
	    - (SI_Long)3L);
    if (g2int_gsi_item_is_value_p(rpc_value_or_object)) {
	gsi_instance_index = 
		g2int_get_gsi_instance_plist_value(rpc_value_or_object,
		Qg2int_gsi_instance_squirrelled_index);
	gsi_extension_data_qm = ISVREF(G2int_current_icp_socket,(SI_Long)29L);
	g2int_write_icp_byte(G2int_rpc_object_type_tag);
	g2int_write_icp_unsigned_integer(gsi_instance_index);
	gensym_push_modify_macro_arg = rpc_value_or_object;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(gsi_extension_data_qm,(SI_Long)5L);
	svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	return VALUES_1(SVREF(gsi_extension_data_qm,FIX((SI_Long)5L)) = 
		svref_new_value);
    }
    else {
	value = ISVREF(rpc_value_or_object,(SI_Long)2L);
	if ( !TRUEP(value))
	    value_type = FIX((SI_Long)0L);
	if ( !(FIXNUMP(value_type) && FIXNUM_LE(FIX((SI_Long)-128L),
		value_type) && FIXNUM_LE(value_type,FIX((SI_Long)127L))))
	    return g2int_write_icp_byte(G2int_gsi_null_type_tag);
	else
	    switch (INTEGER_TO_CHAR(value_type)) {
	      case 0:
		return g2int_write_icp_byte(G2int_gsi_null_type_tag);
	      case 1:
		g2int_write_icp_byte(G2int_gsi_integer_type_tag);
		return g2int_write_icp_integer(value);
	      case 5:
		g2int_write_icp_byte(G2int_gsi_logical_type_tag);
		return g2int_write_icp_integer(value);
	      case 3:
		g2int_write_icp_byte(G2int_gsi_symbol_type_tag);
		return g2int_write_icp_text_string(g2int_symbol_name_text_string(value));
	      case 4:
	      case 11:
		g2int_write_icp_byte(G2int_gsi_string_type_tag);
		copy_string_value_p = STRINGP(value);
		if (copy_string_value_p)
		    value = g2int_gensym_string_to_wide_string_for_gsi(value);
		g2int_write_icp_text_string(value);
		if (copy_string_value_p)
		    return g2int_reclaim_wide_string(value);
		else
		    return VALUES_1(Nil);
	      case 6:
		g2int_write_icp_byte(G2int_gsi_64bit_float_type_tag);
		return g2int_write_icp_managed_double_float(value);
	      case 9:
		g2int_write_icp_byte(G2int_rpc_object_handle_type_tag);
		return g2int_write_icp_fixnum(value);
	      default:
		return g2int_write_icp_byte(G2int_gsi_null_type_tag);
	    }
    }
}

/* READ-ICP-RPC-VALUE-OR-OBJECT */
Object g2int_read_icp_rpc_value_or_object()
{
    Object type_tag, remote_object_index, receiving_resumable_object;

    x_note_fn_call(47,56);
    type_tag = g2int_peek_icp_byte();
    if (FIXNUM_EQ(type_tag,G2int_rpc_object_type_tag)) {
	g2int_read_icp_byte();
	remote_object_index = g2int_read_icp_unsigned_integer();
	receiving_resumable_object = g2int_make_receiving_resumable_object_1();
	g2int_store_corresponding_icp_object(remote_object_index,
		receiving_resumable_object);
	SVREF(receiving_resumable_object,FIX((SI_Long)11L)) = 
		remote_object_index;
	return VALUES_1(receiving_resumable_object);
    }
    else if (FIXNUM_EQ(type_tag,G2int_rpc_object_handle_type_tag)) {
	g2int_read_icp_byte();
	return g2int_make_gsi_instance(2,G2int_gsi_item_handle_type_tag,
		g2int_read_icp_fixnum());
    }
    else
	return g2int_read_icp_remote_value();
}

/* WRITE-ICP-RPC-ARGUMENT-LIST */
Object g2int_write_icp_rpc_argument_list(rpc_argument_list)
    Object rpc_argument_list;
{
    Object actual_size, value_or_object;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(47,57);
    actual_size = G2int_rpc_argument_count_overrideqm;
    if (actual_size);
    else
	actual_size = rpc_argument_list ? 
		FIXNUM_SUB1(g2int_gsi_managed_array_length(rpc_argument_list)) 
		: FIX((SI_Long)0L);
    g2int_write_icp_unsigned_integer(actual_size);
    i = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(actual_size);
    value_or_object = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    value_or_object = ISVREF(rpc_argument_list,i);
    g2int_write_icp_rpc_value_or_object(value_or_object);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-IGNORED-RPC-ARGUMENT-LIST */
Object g2int_reclaim_ignored_rpc_argument_list(rpc_argument_list)
    Object rpc_argument_list;
{
    Object item_among_arguments_qm, rpc_arglist_structure, temp;

    x_note_fn_call(47,58);
    item_among_arguments_qm = g2int_get_item_from_arguments(rpc_argument_list);
    if (item_among_arguments_qm) {
	rpc_arglist_structure = ISVREF(item_among_arguments_qm,(SI_Long)9L);
	temp = ISVREF(rpc_arglist_structure,(SI_Long)7L);
	g2int_gsi_reclaim_contents(temp,g2int_default_owner_for_gsi_objects());
	SVREF(rpc_arglist_structure,FIX((SI_Long)7L)) = Nil;
	g2int_reclaim_rpc_argument_list(rpc_argument_list,Nil);
	SVREF(rpc_arglist_structure,FIX((SI_Long)1L)) = Nil;
	g2int_reclaim_receiving_rpc_arglist_structure_1(rpc_arglist_structure);
    }
    else {
	temp = G2int_gsi_reclaim_listqm;
	g2int_gsi_reclaim_contents(temp,g2int_default_owner_for_gsi_objects());
	G2int_gsi_reclaim_listqm = Nil;
	g2int_reclaim_rpc_argument_list(rpc_argument_list,Nil);
    }
    return VALUES_1(Nil);
}

/* READ-ICP-RPC-ARGUMENT-LIST */
Object g2int_read_icp_rpc_argument_list()
{
    Object length_1, actual_size, arg_array, svref_new_value, argument;
    Object enclosing_arglist_structure_qm;
    Object previous_receiving_resumable_object_qm;
    SI_Long item_count, ab_loop_bind_;

    x_note_fn_call(47,59);
    length_1 = g2int_read_icp_unsigned_integer();
    actual_size = FIXNUM_ADD1(length_1);
    arg_array = g2int_gsi_allocate_managed_array(actual_size);
    svref_new_value = G2int_gsi_magic_number;
    SVREF(arg_array,FIX((SI_Long)0L)) = svref_new_value;
    item_count = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(actual_size);
    argument = Nil;
    enclosing_arglist_structure_qm = Nil;
    previous_receiving_resumable_object_qm = Nil;
  next_loop:
    if (item_count >= ab_loop_bind_)
	goto end_loop;
    argument = g2int_read_icp_rpc_value_or_object();
    ISVREF(arg_array,item_count) = argument;
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	if ( !TRUEP(enclosing_arglist_structure_qm))
	    enclosing_arglist_structure_qm = 
		    g2int_make_receiving_rpc_arglist_structure_1();
	SVREF(argument,FIX((SI_Long)9L)) = enclosing_arglist_structure_qm;
	if (previous_receiving_resumable_object_qm)
	    SVREF(previous_receiving_resumable_object_qm,FIX((SI_Long)3L)) 
		    = argument;
	SVREF(argument,FIX((SI_Long)4L)) = 
		previous_receiving_resumable_object_qm;
	previous_receiving_resumable_object_qm = argument;
    }
    item_count = item_count + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (enclosing_arglist_structure_qm)
	SVREF(enclosing_arglist_structure_qm,FIX((SI_Long)1L)) = arg_array;
    return VALUES_1(arg_array);
    return VALUES_1(Qnil);
}

/* GET-ITEM-FROM-ARGUMENTS */
Object g2int_get_item_from_arguments(rpc_arguments)
    Object rpc_arguments;
{
    Object argument, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(47,60);
    i = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(g2int_gsi_managed_array_length(rpc_arguments));
    argument = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    argument = ISVREF(rpc_arguments,i);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct)) 
		{
	temp = argument;
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
  nil:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

Object G2int_rpc_throw_tag = UNBOUND;

Object G2int_possibly_interned_symbol_tags = UNBOUND;

/* WRITE-ICP-POSSIBLY-INTERNED-SYMBOL */
Object g2int_write_icp_possibly_interned_symbol(possibly_interned_symbol,
	    corresponding_index_of_symbol_qm)
    Object possibly_interned_symbol, corresponding_index_of_symbol_qm;
{
    Object symbol_name_1, symbol_index, overflow_count_qm;
    Object result;

    x_note_fn_call(47,61);
    if ( !TRUEP(corresponding_index_of_symbol_qm))
	corresponding_index_of_symbol_qm = 
		g2int_get_icp_object_index_for_symbol(possibly_interned_symbol,
		G2int_current_icp_port);
    if (corresponding_index_of_symbol_qm) {
	g2int_write_icp_byte(G2int_possibly_interned_symbol_interned_tag);
	return g2int_write_icp_fixnum(corresponding_index_of_symbol_qm);
    }
    else {
	symbol_name_1 = 
		g2int_symbol_name_text_string(possibly_interned_symbol);
	result = g2int_establish_new_object_index_for_symbol(3,
		possibly_interned_symbol,G2int_current_icp_port,Nil);
	MVS_2(result,symbol_index,overflow_count_qm);
	if (overflow_count_qm) {
	    g2int_write_icp_byte(G2int_possibly_interned_symbol_uninterned_overflow_tag);
	    g2int_write_icp_fixnum(overflow_count_qm);
	}
	else
	    g2int_write_icp_byte(G2int_possibly_interned_symbol_uninterned_tag);
	g2int_write_icp_fixnum(symbol_index);
	return g2int_write_icp_text_string(symbol_name_1);
    }
}

/* READ-ICP-POSSIBLY-INTERNED-SYMBOL */
Object g2int_read_icp_possibly_interned_symbol()
{
    Object tag, symbol_index, symbol, symbol_name_1, new_index_limit_plus_one;

    x_note_fn_call(47,62);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 0:
	    symbol_index = g2int_read_icp_fixnum();
	    symbol = g2int_get_from_icp_port(G2int_current_icp_port,
		    symbol_index,Qg2int_standard_icp_object_index_space);
	    return VALUES_1(symbol);
	  case 1:
	    symbol_index = g2int_read_icp_fixnum();
	    symbol_name_1 = g2int_read_icp_text_string();
	    symbol = g2int_intern_text_string(1,symbol_name_1);
	    g2int_store_corresponding_icp_object(symbol_index,symbol);
	    return VALUES_1(symbol);
	  case 2:
	    new_index_limit_plus_one = g2int_read_icp_fixnum();
	    g2int_handler_for_enlarge_corresponding_icp_object_index_space(Qg2int_standard_icp_object_index_space,
		    new_index_limit_plus_one);
	    symbol_index = g2int_read_icp_fixnum();
	    symbol_name_1 = g2int_read_icp_text_string();
	    symbol = g2int_intern_text_string(1,symbol_name_1);
	    g2int_store_corresponding_icp_object(symbol_index,symbol);
	    return VALUES_1(symbol);
	  default:
	    return VALUES_1(Nil);
	}
}

Object G2int_attribute_specqm_tags = UNBOUND;

static Object Qg2int_vector_element;  /* vector-element */

static Object Qg2int_attribute;    /* attribute */

static Object list_constant_1;     /* # */

static Object Qg2int_list_element;  /* list-element */

/* WRITE-ICP-ATTRIBUTE-SPEC? */
Object g2int_write_icp_attribute_specqm(attribute_spec_qm)
    Object attribute_spec_qm;
{
    Object attribute_type, type, class_qualifier_qm, base_name;

    x_note_fn_call(47,63);
    if (attribute_spec_qm) {
	if (FIXNUMP(attribute_spec_qm))
	    attribute_type = Qg2int_vector_element;
	else if (SYMBOLP(attribute_spec_qm))
	    attribute_type = Qg2int_attribute;
	else if (CONSP(attribute_spec_qm)) {
	    type = M_CAR(attribute_spec_qm);
	    attribute_type = EQ(type,Qg2int_class_qualified_name) ? 
		    Qg2int_attribute : type;
	}
	else
	    attribute_type = Qnil;
	if (EQ(attribute_type,Qg2int_attribute)) {
	    if (g2int_memq_function(CONSP(attribute_spec_qm) ? 
		    THIRD(attribute_spec_qm) : attribute_spec_qm,
		    list_constant_1)) {
		class_qualifier_qm = CONSP(attribute_spec_qm) ? 
			SECOND(attribute_spec_qm) : Nil;
		base_name = CONSP(attribute_spec_qm) ? 
			THIRD(attribute_spec_qm) : attribute_spec_qm;
		if (class_qualifier_qm) {
		    g2int_write_icp_byte(G2int_qualified_system_attribute_tag);
		    g2int_write_icp_possibly_interned_symbol(class_qualifier_qm,
			    Nil);
		}
		else
		    g2int_write_icp_byte(G2int_unqualified_system_attribute_tag);
		g2int_write_icp_possibly_interned_symbol(base_name,Nil);
	    }
	    else {
		class_qualifier_qm = CONSP(attribute_spec_qm) ? 
			SECOND(attribute_spec_qm) : Nil;
		base_name = CONSP(attribute_spec_qm) ? 
			THIRD(attribute_spec_qm) : attribute_spec_qm;
		if (class_qualifier_qm) {
		    g2int_write_icp_byte(G2int_qualified_symbolic_attribute_tag);
		    g2int_write_icp_possibly_interned_symbol(class_qualifier_qm,
			    Nil);
		}
		else
		    g2int_write_icp_byte(G2int_unqualified_symbolic_attribute_tag);
		g2int_write_icp_possibly_interned_symbol(base_name,Nil);
	    }
	}
	else if (EQ(attribute_type,Qg2int_vector_element)) {
	    g2int_write_icp_byte(G2int_vector_element_attribute_spec_tag);
	    g2int_write_icp_fixnum(FIXNUMP(attribute_spec_qm) ? 
		    attribute_spec_qm : SECOND(attribute_spec_qm));
	}
	else if (EQ(attribute_type,Qg2int_list_element)) {
	    g2int_write_icp_byte(G2int_list_element_attribute_spec_tag);
	    g2int_write_icp_fixnum(FIXNUMP(attribute_spec_qm) ? 
		    attribute_spec_qm : SECOND(attribute_spec_qm));
	}
    }
    else
	g2int_write_icp_byte(G2int_nameless_attribute_spec_tag);
    return VALUES_1(Nil);
}

/* READ-ICP-ATTRIBUTE-SPEC? */
Object g2int_read_icp_attribute_specqm()
{
    Object tag, base_name, qualifier, index_1;

    x_note_fn_call(47,64);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_3(Qg2int_attribute,Nil,Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 12:
	    base_name = g2int_read_icp_possibly_interned_symbol();
	    return VALUES_3(Qg2int_attribute,Nil,base_name);
	  case 13:
	    qualifier = g2int_read_icp_possibly_interned_symbol();
	    base_name = g2int_read_icp_possibly_interned_symbol();
	    return VALUES_3(Qg2int_attribute,qualifier,base_name);
	  case 14:
	    base_name = g2int_read_icp_possibly_interned_symbol();
	    return VALUES_3(Qg2int_attribute,Nil,base_name);
	  case 15:
	    qualifier = g2int_read_icp_possibly_interned_symbol();
	    base_name = g2int_read_icp_possibly_interned_symbol();
	    return VALUES_3(Qg2int_attribute,qualifier,base_name);
	  case 3:
	    index_1 = g2int_read_icp_fixnum();
	    return VALUES_3(Qg2int_vector_element,Nil,index_1);
	  case 4:
	    index_1 = g2int_read_icp_fixnum();
	    return VALUES_3(Qg2int_list_element,Nil,index_1);
	  default:
	    return VALUES_3(Qg2int_attribute,Nil,Nil);
	}
}

static Object Qg2int_write_icp_list_of_attributes;  /* write-icp-list-of-attributes */

static Object string_constant_3;   /* "resumable icp synch error: ~S expected, ~S found" */

/* WRITE-ICP-LIST-OF-ATTRIBUTES */
Object g2int_write_icp_list_of_attributes(list_of_attributes)
    Object list_of_attributes;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,65);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_fixnum(FIX((SI_Long)0L));
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_attributes,top,Nil);
	}
	list_of_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_attributes;
	value = g2int_write_icp_fixnum(FIX((SI_Long)0L));
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(list_of_attributes);
	    g2int_resumable_icp_push(Qg2int_write_icp_list_of_attributes);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_attributes;  /* read-icp-list-of-attributes */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* READ-ICP-LIST-OF-ATTRIBUTES */
Object g2int_read_icp_list_of_attributes()
{
    Object length_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, tag, temp;
    Object qualifier, base_name, resumable_icp_state_1, icp_suspend_1, top;
    Object value, arg1, key, arg2;
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(47,66);
    if (G2int_disable_resumability) {
	length_1 = g2int_read_icp_fixnum();
	count_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (count_1 > ab_loop_bind_)
	    goto end_loop;
	tag = g2int_read_icp_byte();
	if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
		FIXNUM_LE(tag,FIX((SI_Long)127L))))
	    temp = Nil;
	else
	    switch (INTEGER_TO_CHAR(tag)) {
	      case 13:
		qualifier = g2int_read_icp_possibly_interned_symbol();
		base_name = g2int_read_icp_possibly_interned_symbol();
		temp = g2int_gensym_list_2(qualifier,base_name);
		break;
	      case 12:
		temp = g2int_read_icp_possibly_interned_symbol();
		break;
	      default:
		temp = Nil;
		break;
	    }
	ab_loopvar__2 = g2int_gensym_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qg2int_read_icp_list_of_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_attributes,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    length_1 = value;
	}
	count_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)1L;
	ab_loop_bind_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
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
	if (count_1 > ab_loop_bind_)
	    goto end_loop_1;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		tag = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_byte();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(ab_loopvar__2);
		    g2int_resumable_icp_push(ab_loopvar__1);
		    g2int_resumable_icp_push(ab_loopvar_);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(count_1));
		    g2int_resumable_icp_push(length_1);
		    g2int_resumable_icp_push(Qg2int_read_icp_list_of_attributes);
		    return VALUES_1(G2int_icp_suspend);
		}
		tag = value;
	    }
	    key = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : tag;
	    if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) && 
		    FIXNUM_LE(key,FIX((SI_Long)127L))))
		arg1 = Nil;
	    else
		switch (INTEGER_TO_CHAR(key)) {
		  case 13:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			qualifier = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_possibly_interned_symbol();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(tag);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(ab_loopvar__2);
			    g2int_resumable_icp_push(ab_loopvar__1);
			    g2int_resumable_icp_push(ab_loopvar_);
			    g2int_resumable_icp_push(FIX(ab_loop_bind_));
			    g2int_resumable_icp_push(FIX(count_1));
			    g2int_resumable_icp_push(length_1);
			    g2int_resumable_icp_push(Qg2int_read_icp_list_of_attributes);
			    return VALUES_1(G2int_icp_suspend);
			}
			qualifier = value;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			base_name = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_possibly_interned_symbol();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(qualifier);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(tag);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(ab_loopvar__2);
			    g2int_resumable_icp_push(ab_loopvar__1);
			    g2int_resumable_icp_push(ab_loopvar_);
			    g2int_resumable_icp_push(FIX(ab_loop_bind_));
			    g2int_resumable_icp_push(FIX(count_1));
			    g2int_resumable_icp_push(length_1);
			    g2int_resumable_icp_push(Qg2int_read_icp_list_of_attributes);
			    return VALUES_1(G2int_icp_suspend);
			}
			base_name = value;
		    }
		    arg1 = g2int_gensym_list_2(qualifier,base_name);
		    break;
		  case 12:
		    value = g2int_read_icp_possibly_interned_symbol();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(tag);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(ab_loopvar__2);
			g2int_resumable_icp_push(ab_loopvar__1);
			g2int_resumable_icp_push(ab_loopvar_);
			g2int_resumable_icp_push(FIX(ab_loop_bind_));
			g2int_resumable_icp_push(FIX(count_1));
			g2int_resumable_icp_push(length_1);
			g2int_resumable_icp_push(Qg2int_read_icp_list_of_attributes);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		    break;
		  default:
		    arg1 = Nil;
		    break;
		}
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
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_boolean;  /* read-icp-list-of-boolean */

/* READ-ICP-LIST-OF-BOOLEAN */
Object g2int_read_icp_list_of_boolean()
{
    Object length_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(47,67);
    if (G2int_disable_resumability) {
	length_1 = g2int_read_icp_fixnum();
	count_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (count_1 > ab_loop_bind_)
	    goto end_loop;
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_read_icp_boolean(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qg2int_read_icp_list_of_boolean,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_boolean,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_boolean);
		return VALUES_1(G2int_icp_suspend);
	    }
	    length_1 = value;
	}
	count_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)1L;
	ab_loop_bind_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
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
	if (count_1 > ab_loop_bind_)
	    goto end_loop_1;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(count_1));
		g2int_resumable_icp_push(length_1);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_boolean);
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
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_boolean;  /* write-icp-list-of-boolean */

/* WRITE-ICP-LIST-OF-BOOLEAN */
Object g2int_write_icp_list_of_boolean(list_of_boolean)
    Object list_of_boolean;
{
    Object value, ab_loop_list_, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, v1, v2, v3;
    Object result;

    x_note_fn_call(47,68);
    if (G2int_disable_resumability) {
	g2int_write_icp_fixnum(length(list_of_boolean));
	value = Nil;
	ab_loop_list_ = list_of_boolean;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_boolean(value);
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
	    if ( !EQ(Qg2int_write_icp_list_of_boolean,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_boolean,top,Nil);
	}
	list_of_boolean = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_boolean;
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
		    g2int_write_icp_fixnum(length(list_of_boolean)))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_boolean;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,g2int_write_icp_boolean(value))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(value);
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
	    g2int_resumable_icp_push(list_of_boolean);
	    g2int_resumable_icp_push(Qg2int_write_icp_list_of_boolean);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_lists_of_attributes;  /* write-icp-list-of-lists-of-attributes */

/* WRITE-ICP-LIST-OF-LISTS-OF-ATTRIBUTES */
Object g2int_write_icp_list_of_lists_of_attributes(list_of_lists_of_attributes)
    Object list_of_lists_of_attributes;
{
    Object list_of_attributes, ab_loop_list_, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, v1, v2, v3;
    Object result;

    x_note_fn_call(47,69);
    if (G2int_disable_resumability) {
	g2int_write_icp_fixnum(length(list_of_lists_of_attributes));
	list_of_attributes = Nil;
	ab_loop_list_ = list_of_lists_of_attributes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	list_of_attributes = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_write_icp_list_of_attributes(list_of_attributes);
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
	    if ( !EQ(Qg2int_write_icp_list_of_lists_of_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_lists_of_attributes,top,Nil);
	}
	list_of_lists_of_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_lists_of_attributes;
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
		g2int_write_icp_fixnum(length(list_of_lists_of_attributes)))) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	list_of_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loop_list_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_lists_of_attributes;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
	    goto resume;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	list_of_attributes = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
      resume:
	if (EQ(icp_suspend_1,
		g2int_write_icp_list_of_attributes(list_of_attributes))) {
	    g2int_resumable_icp_push(ab_loop_list_);
	    g2int_resumable_icp_push(list_of_attributes);
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
	    g2int_resumable_icp_push(list_of_lists_of_attributes);
	    g2int_resumable_icp_push(Qg2int_write_icp_list_of_lists_of_attributes);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_lists_of_attributes;  /* read-icp-list-of-lists-of-attributes */

/* READ-ICP-LIST-OF-LISTS-OF-ATTRIBUTES */
Object g2int_read_icp_list_of_lists_of_attributes()
{
    Object length_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value, arg1, arg2;
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(47,70);
    if (G2int_disable_resumability) {
	length_1 = g2int_read_icp_fixnum();
	count_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (count_1 > ab_loop_bind_)
	    goto end_loop;
	ab_loopvar__2 = 
		g2int_gensym_cons_1(g2int_read_icp_list_of_attributes(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
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
	    if ( !EQ(Qg2int_read_icp_list_of_lists_of_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_lists_of_attributes,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_lists_of_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    length_1 = value;
	}
	count_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)1L;
	ab_loop_bind_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
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
	if (count_1 > ab_loop_bind_)
	    goto end_loop_1;
      resume:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(count_1));
		g2int_resumable_icp_push(length_1);
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_lists_of_attributes);
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
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_included_return_attributes;  /* write-icp-list-of-included-return-attributes */

/* WRITE-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES */
Object g2int_write_icp_list_of_included_return_attributes(list_of_included_return_attributes)
    Object list_of_included_return_attributes;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,71);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L ? 
		g2int_write_icp_list_of_lists_of_attributes(list_of_included_return_attributes) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_included_return_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_included_return_attributes,
			top,Nil);
	}
	list_of_included_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_included_return_attributes;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L) {
	    value = 
		    g2int_write_icp_list_of_lists_of_attributes(list_of_included_return_attributes);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_included_return_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_included_return_attributes;  /* read-icp-list-of-included-return-attributes */

/* READ-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES */
Object g2int_read_icp_list_of_included_return_attributes()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,72);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L ? g2int_read_icp_list_of_lists_of_attributes() 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_of_included_return_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_included_return_attributes,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L) {
	    value = g2int_read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_included_return_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_excluded_return_attributes;  /* write-icp-list-of-excluded-return-attributes */

/* WRITE-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES */
Object g2int_write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes)
    Object list_of_excluded_return_attributes;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,73);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L ? 
		g2int_write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_excluded_return_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_excluded_return_attributes,
			top,Nil);
	}
	list_of_excluded_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_excluded_return_attributes;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L) {
	    value = 
		    g2int_write_icp_list_of_lists_of_attributes(list_of_excluded_return_attributes);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_excluded_return_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_excluded_return_attributes;  /* read-icp-list-of-excluded-return-attributes */

/* READ-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES */
Object g2int_read_icp_list_of_excluded_return_attributes()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,74);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L ? g2int_read_icp_list_of_lists_of_attributes() 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_of_excluded_return_attributes,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_excluded_return_attributes,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L) {
	    value = g2int_read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_excluded_return_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_included_return_system_attributes;  /* write-icp-list-of-included-return-system-attributes */

/* WRITE-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES */
Object g2int_write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes)
    Object list_of_included_return_system_attributes;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,75);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L ? 
		g2int_write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_write_icp_list_of_included_return_system_attributes,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_included_return_system_attributes,
			top,Nil);
	}
	list_of_included_return_system_attributes = (resumable_icp_state_1 
		? TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		&&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_included_return_system_attributes;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L) {
	    value = 
		    g2int_write_icp_list_of_lists_of_attributes(list_of_included_return_system_attributes);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_included_return_system_attributes);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_included_return_system_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_included_return_system_attributes;  /* read-icp-list-of-included-return-system-attributes */

/* READ-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES */
Object g2int_read_icp_list_of_included_return_system_attributes()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,76);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L ? g2int_read_icp_list_of_lists_of_attributes() 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_read_icp_list_of_included_return_system_attributes,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_included_return_system_attributes,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L) {
	    value = g2int_read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_included_return_system_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_include_all_return_system_attributes;  /* write-icp-list-of-include-all-return-system-attributes */

/* WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES */
Object g2int_write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes)
    Object list_of_include_all_return_system_attributes;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,77);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)9L ? 
		g2int_write_icp_list_of_boolean(list_of_include_all_return_system_attributes) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_write_icp_list_of_include_all_return_system_attributes,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_include_all_return_system_attributes,
			top,Nil);
	}
	list_of_include_all_return_system_attributes = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_include_all_return_system_attributes;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)9L) {
	    value = 
		    g2int_write_icp_list_of_boolean(list_of_include_all_return_system_attributes);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_include_all_return_system_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_include_all_return_system_attributes;  /* read-icp-list-of-include-all-return-system-attributes */

/* READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES */
Object g2int_read_icp_list_of_include_all_return_system_attributes()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,78);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)9L ? g2int_read_icp_list_of_boolean() : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_read_icp_list_of_include_all_return_system_attributes,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_include_all_return_system_attributes,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)9L) {
	    value = g2int_read_icp_list_of_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_include_all_return_system_attributes);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_include_all_return_system_attributes_except;  /* write-icp-list-of-include-all-return-system-attributes-except */

/* WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT */
Object g2int_write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except)
    Object list_of_include_all_return_system_attributes_except;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,79);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)25L ? 
		g2int_write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except) 
		: Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_write_icp_list_of_include_all_return_system_attributes_except,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_include_all_return_system_attributes_except,
			top,Nil);
	}
	list_of_include_all_return_system_attributes_except = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_include_all_return_system_attributes_except;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)25L) {
	    value = 
		    g2int_write_icp_list_of_lists_of_attributes(list_of_include_all_return_system_attributes_except);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes_except);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_include_all_return_system_attributes_except);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_include_all_return_system_attributes_except;  /* read-icp-list-of-include-all-return-system-attributes-except */

/* READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT */
Object g2int_read_icp_list_of_include_all_return_system_attributes_except()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,80);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)25L ? 
		g2int_read_icp_list_of_lists_of_attributes() : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_read_icp_list_of_include_all_return_system_attributes_except,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_include_all_return_system_attributes_except,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)25L) {
	    value = g2int_read_icp_list_of_lists_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_include_all_return_system_attributes_except);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_list_of_return_kinds;  /* write-icp-list-of-return-kinds */

/* WRITE-ICP-LIST-OF-RETURN-KINDS */
Object g2int_write_icp_list_of_return_kinds(list_of_return_kinds)
    Object list_of_return_kinds;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,81);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)8L ? 
		g2int_write_icp_list_of_attributes(list_of_return_kinds) : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_list_of_return_kinds,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_list_of_return_kinds,top,Nil);
	}
	list_of_return_kinds = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_return_kinds;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)8L) {
	    value = g2int_write_icp_list_of_attributes(list_of_return_kinds);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(list_of_return_kinds);
		g2int_resumable_icp_push(Qg2int_write_icp_list_of_return_kinds);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_list_of_return_kinds;  /* read-icp-list-of-return-kinds */

/* READ-ICP-LIST-OF-RETURN-KINDS */
Object g2int_read_icp_list_of_return_kinds()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,82);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)8L ? g2int_read_icp_list_of_attributes() : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_list_of_return_kinds,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_list_of_return_kinds,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)8L) {
	    value = g2int_read_icp_list_of_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_list_of_return_kinds);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_remote_procedure_varargs_p;  /* write-icp-remote-procedure-varargs-p */

/* WRITE-ICP-REMOTE-PROCEDURE-VARARGS-P */
Object g2int_write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p)
    Object remote_procedure_varargs_p;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,83);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)9L ? 
		g2int_write_icp_boolean(remote_procedure_varargs_p) : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_remote_procedure_varargs_p,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_write_icp_remote_procedure_varargs_p,top,Nil);
	}
	remote_procedure_varargs_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_varargs_p;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)9L) {
	    value = g2int_write_icp_boolean(remote_procedure_varargs_p);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(remote_procedure_varargs_p);
		g2int_resumable_icp_push(Qg2int_write_icp_remote_procedure_varargs_p);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_remote_procedure_varargs_p;  /* read-icp-remote-procedure-varargs-p */

/* READ-ICP-REMOTE-PROCEDURE-VARARGS-P */
Object g2int_read_icp_remote_procedure_varargs_p()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(47,84);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)9L ? g2int_read_icp_boolean() : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_remote_procedure_varargs_p,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_read_icp_remote_procedure_varargs_p,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)9L) {
	    value = g2int_read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_remote_procedure_varargs_p);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_attribute_value_tags = UNBOUND;

/* WRITE-ICP-EVALUATION-TRUTH-VALUE */
Object g2int_write_icp_evaluation_truth_value(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(47,85);
    return g2int_write_icp_fixnum(evaluation_truth_value);
}

/* RECLAIM-EVALUATION-TRUTH-VALUE-IF-APPROPRIATE */
Object g2int_reclaim_evaluation_truth_value_if_appropriate(maybe_evaluation_truth_value)
    Object maybe_evaluation_truth_value;
{
    x_note_fn_call(47,86);
    return VALUES_1(maybe_evaluation_truth_value);
}

/* READ-ICP-EVALUATION-TRUTH-VALUE */
Object g2int_read_icp_evaluation_truth_value()
{
    x_note_fn_call(47,87);
    return g2int_read_icp_fixnum();
}

static Object Qg2int_write_attribute_value;  /* write_attribute_value */

/* WRITE-ICP-ATTRIBUTE-VALUE */
Object g2int_write_icp_attribute_value(simple_value,corresponding_index_qm)
    Object simple_value, corresponding_index_qm;
{
    Object value_type, value, converted_value;
    char copy_string_value_p;

    x_note_fn_call(47,88);
    value_type = FIX(IFIX(ISVREF(simple_value,(SI_Long)1L)) >>  -  - 
	    (SI_Long)3L);
    value = ISVREF(simple_value,(SI_Long)2L);
    if ( !TRUEP(value))
	value_type = FIX((SI_Long)0L);
    if ( !(FIXNUMP(value_type) && FIXNUM_LE(FIX((SI_Long)-128L),
	    value_type) && FIXNUM_LE(value_type,FIX((SI_Long)127L))))
	g2int_gsi_connection_error(3,Qg2int_write_attribute_value,
		G2int_gsi_incompatible_type,value_type);
    else
	switch (INTEGER_TO_CHAR(value_type)) {
	  case 1:
	    g2int_write_icp_byte(G2int_attribute_value_integer_tag);
	    g2int_write_icp_fixnum(value);
	    break;
	  case 5:
	    g2int_write_icp_byte(G2int_attribute_value_truth_value_tag);
	    g2int_write_icp_fixnum(value);
	    break;
	  case 6:
	    g2int_write_icp_byte(G2int_attribute_value_float_tag);
	    g2int_write_icp_managed_double_float(value);
	    break;
	  case 4:
	  case 11:
	    g2int_write_icp_byte(G2int_attribute_value_text_tag);
	    converted_value = value;
	    copy_string_value_p = STRINGP(converted_value);
	    if (copy_string_value_p)
		converted_value = 
			g2int_gensym_string_to_wide_string_for_gsi(converted_value);
	    g2int_write_icp_text_string(converted_value);
	    if (copy_string_value_p)
		g2int_reclaim_wide_string(converted_value);
	    break;
	  case 3:
	    g2int_write_icp_possibly_interned_symbol(value,Nil);
	    break;
	  case 0:
	    g2int_write_icp_byte(G2int_attribute_value_null_tag);
	    break;
	  case 51:
	    g2int_write_icp_byte(G2int_attribute_value_long_tag);
	    g2int_write_icp_managed_long(value);
	    break;
	  default:
	    g2int_gsi_connection_error(3,Qg2int_write_attribute_value,
		    G2int_gsi_incompatible_type,value_type);
	    break;
	}
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-ATTRIBUTE-VALUE */
Object g2int_reclaim_icp_attribute_value(icp_attribute_value)
    Object icp_attribute_value;
{
    x_note_fn_call(47,89);
    if (g2int_text_string_p(icp_attribute_value))
	g2int_reclaim_text_or_gensym_string(icp_attribute_value);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(icp_attribute_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(icp_attribute_value)) == 
	    (SI_Long)1L)
	g2int_reclaim_managed_simple_float_array_of_length_1(icp_attribute_value);
    return VALUES_1(Nil);
}

/* READ-ICP-ATTRIBUTE-VALUE */
Object g2int_read_icp_attribute_value()
{
    Object tag, symbol_qm, symbol_index, symbol, symbol_name_1;
    Object new_index_limit_plus_one, temp;

    x_note_fn_call(47,90);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	symbol_qm = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 0:
	    symbol_index = g2int_read_icp_fixnum();
	    symbol = g2int_get_from_icp_port(G2int_current_icp_port,
		    symbol_index,Qg2int_standard_icp_object_index_space);
	    symbol_qm = symbol;
	    break;
	  case 1:
	    symbol_index = g2int_read_icp_fixnum();
	    symbol_name_1 = g2int_read_icp_text_string();
	    symbol = g2int_intern_text_string(1,symbol_name_1);
	    g2int_store_corresponding_icp_object(symbol_index,symbol);
	    symbol_qm = symbol;
	    break;
	  case 2:
	    new_index_limit_plus_one = g2int_read_icp_fixnum();
	    g2int_handler_for_enlarge_corresponding_icp_object_index_space(Qg2int_standard_icp_object_index_space,
		    new_index_limit_plus_one);
	    symbol_index = g2int_read_icp_fixnum();
	    symbol_name_1 = g2int_read_icp_text_string();
	    symbol = g2int_intern_text_string(1,symbol_name_1);
	    g2int_store_corresponding_icp_object(symbol_index,symbol);
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
	    temp = g2int_read_icp_fixnum();
	    break;
	  case 16:
	    temp = g2int_read_icp_managed_long();
	    break;
	  case 6:
	    temp = g2int_read_icp_managed_double_float();
	    break;
	  case 8:
	    temp = g2int_read_icp_text_string();
	    break;
	  case 9:
	    temp = g2int_read_icp_evaluation_truth_value();
	    break;
	  case 14:
	    temp = g2int_read_icp_evaluation_sequence();
	    break;
	  case 15:
	    temp = g2int_read_icp_evaluation_structure();
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

/* WRITE-ICP-HISTORY-TIMESTAMP */
Object g2int_write_icp_history_timestamp(history_timestamp)
    Object history_timestamp;
{
    x_note_fn_call(47,91);
    return VALUES_1(history_timestamp);
}

/* READ-ICP-HISTORY-TIMESTAMP */
Object g2int_read_icp_history_timestamp()
{
    Object tag;

    x_note_fn_call(47,92);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 5:
	    return g2int_read_icp_fixnum();
	  case 6:
	    return g2int_read_icp_managed_double_float();
	  default:
	    return VALUES_1(Nil);
	}
}

/* WRITE-ICP-ADD-ATTRIBUTE-VALUE */
Object g2int_write_icp_add_attribute_value(attribute_spec_qm,
	    attribute_value,corresponding_index_of_attribute_value_qm)
    Object attribute_spec_qm, attribute_value;
    Object corresponding_index_of_attribute_value_qm;
{
    x_note_fn_call(47,93);
    g2int_write_icp_byte(G2int_add_attribute_value_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    return g2int_write_icp_attribute_value(attribute_value,
	    corresponding_index_of_attribute_value_qm);
}

/* READ-ICP-ADD-ATTRIBUTE-VALUE */
Object g2int_read_icp_add_attribute_value()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object attribute_value, value_type, current_subobject_qm;
    Object result;

    x_note_fn_call(47,94);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    result = g2int_read_icp_attribute_value();
    MVS_2(result,attribute_value,value_type);
    current_subobject_qm = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)8L);
    return g2int_gsi_add_leaf_to_item_instance(current_subobject_qm,
	    attribute_type,attribute_qualifier_qm,attribute_name_or_index,
	    attribute_value,value_type);
}

/* WRITE-ICP-ADD-CIRCULAR-ATTRIBUTE */
Object g2int_write_icp_add_circular_attribute(attribute_spec_qm,
	    corresponding_index)
    Object attribute_spec_qm, corresponding_index;
{
    x_note_fn_call(47,95);
    g2int_write_icp_byte(G2int_add_circular_attribute_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    return g2int_write_icp_fixnum(corresponding_index);
}

/* READ-ICP-ADD-CIRCULAR-ATTRIBUTE */
Object g2int_read_icp_add_circular_attribute()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object handle, current_subobject_qm;
    Object result;

    x_note_fn_call(47,96);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    handle = g2int_read_icp_fixnum();
    current_subobject_qm = ISVREF(G2int_current_receiving_resumable_object,
	    (SI_Long)8L);
    return g2int_gsi_add_leaf_to_item_instance(current_subobject_qm,
	    attribute_type,attribute_qualifier_qm,attribute_name_or_index,
	    g2int_get_from_icp_port(G2int_current_icp_port,handle,
	    Qg2int_standard_icp_object_index_space),
	    G2int_circular_reference_tag);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT */
Object g2int_write_icp_add_attribute_object(attribute_spec_qm,class_name,
	    corresponding_index_of_class_name_qm,symbolic_attribute_count)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count;
{
    x_note_fn_call(47,97);
    g2int_write_icp_byte(G2int_add_attribute_object_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    return g2int_write_icp_fixnum(symbolic_attribute_count);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT */
Object g2int_read_icp_add_attribute_object()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count;
    Object result;

    x_note_fn_call(47,98);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    return g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    G2int_gsi_null_type_tag,FIX((SI_Long)0L),symbolic_attribute_count);
}

/* WRITE-ICP-ADD-RESUMABLE-CIRCULARITY */
Object g2int_write_icp_add_resumable_circularity(corresponding_index)
    Object corresponding_index;
{
    x_note_fn_call(47,99);
    g2int_write_icp_byte(G2int_add_resumable_circularity_for_resumable_object_portion);
    return g2int_write_icp_fixnum(corresponding_index);
}

/* READ-ICP-ADD-RESUMABLE-CIRCULARITY */
Object g2int_read_icp_add_resumable_circularity()
{
    Object corresponding_index;

    x_note_fn_call(47,100);
    corresponding_index = g2int_read_icp_fixnum();
    return g2int_gsi_add_resumable_circularity(corresponding_index);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT-VECTOR */
Object g2int_write_icp_add_attribute_object_vector(attribute_spec_qm,
	    class_name,corresponding_index_of_class_name_qm,
	    symbolic_attribute_count,resumable_vector_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, resumable_vector_length;
{
    x_note_fn_call(47,101);
    g2int_write_icp_byte(G2int_add_attribute_object_vector_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    g2int_write_icp_fixnum(symbolic_attribute_count);
    return g2int_write_icp_fixnum(resumable_vector_length);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT-VECTOR */
Object g2int_read_icp_add_attribute_object_vector()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_vector_length;
    Object result;

    x_note_fn_call(47,102);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    resumable_vector_length = g2int_read_icp_fixnum();
    return g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    G2int_gsi_item_array_type_tag,resumable_vector_length,
	    symbolic_attribute_count);
}

static Object Qg2int_long;         /* long */

static Object Qg2int_float;        /* |float| */

static Object Qg2int_text;         /* text */

static Object Qg2int_truth;        /* truth */

/* WRITE-ICP-RESUMABLE-SEQUENCE-ELEMENT-TYPE */
Object g2int_write_icp_resumable_sequence_element_type(element_type)
    Object element_type;
{
    Object temp;

    x_note_fn_call(47,103);
    if (EQ(element_type,Qinteger))
	temp = G2int_attribute_value_integer_tag;
    else if (EQ(element_type,Qg2int_long))
	temp = G2int_attribute_value_long_tag;
    else if (EQ(element_type,Qg2int_float))
	temp = G2int_attribute_value_float_tag;
    else if (EQ(element_type,Qg2int_text))
	temp = G2int_attribute_value_text_tag;
    else if (EQ(element_type,Qg2int_truth))
	temp = G2int_attribute_value_truth_value_tag;
    else if (EQ(element_type,Qsymbol))
	temp = G2int_attribute_value_symbol_tag;
    else
	temp = G2int_unknown_value_vector_element_type_tag;
    g2int_write_icp_byte(temp);
    return VALUES_1(Nil);
}

/* READ-ICP-RESUMABLE-SEQUENCE-ELEMENT-TYPE */
Object g2int_read_icp_resumable_sequence_element_type()
{
    Object tag, temp;

    x_note_fn_call(47,104);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 5:
	    temp = Qinteger;
	    break;
	  case 16:
	    temp = Qg2int_long;
	    break;
	  case 6:
	    temp = Qg2int_float;
	    break;
	  case 8:
	    temp = Qg2int_text;
	    break;
	  case 9:
	    temp = Qg2int_truth;
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
Object g2int_write_icp_add_attribute_value_vector(attribute_spec_qm,
	    class_name,corresponding_index_of_class_name_qm,
	    symbolic_attribute_count,element_type,resumable_vector_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type, resumable_vector_length;
{
    x_note_fn_call(47,105);
    g2int_write_icp_byte(G2int_add_attribute_value_vector_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    g2int_write_icp_fixnum(symbolic_attribute_count);
    g2int_write_icp_resumable_sequence_element_type(element_type);
    return g2int_write_icp_fixnum(resumable_vector_length);
}

/* READ-ICP-ADD-ATTRIBUTE-VALUE-VECTOR */
Object g2int_read_icp_add_attribute_value_vector()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_vector_length;
    Object result;

    x_note_fn_call(47,106);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    element_type = g2int_read_icp_resumable_sequence_element_type();
    resumable_vector_length = g2int_read_icp_fixnum();
    return g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    g2int_gsi_array_type_from_g2_element_type(element_type),
	    resumable_vector_length,symbolic_attribute_count);
}

/* WRITE-ICP-HISTORY-SPEC */
Object g2int_write_icp_history_spec(history_spec)
    Object history_spec;
{
    Object gensymed_symbol, datapoint_count_qm, datapoint_age_qm;
    Object granularity_qm;

    x_note_fn_call(47,107);
    gensymed_symbol = history_spec;
    gensymed_symbol = CDR(gensymed_symbol);
    datapoint_count_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    datapoint_age_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    granularity_qm = CAR(gensymed_symbol);
    if (datapoint_count_qm)
	g2int_write_icp_fixnum(datapoint_count_qm);
    else
	g2int_write_icp_fixnum(G2int_no_history_spec_value);
    if (datapoint_age_qm)
	g2int_write_icp_fixnum(datapoint_age_qm);
    else
	g2int_write_icp_fixnum(G2int_no_history_spec_value);
    if (granularity_qm)
	return g2int_write_icp_fixnum(granularity_qm);
    else
	return g2int_write_icp_fixnum(G2int_no_history_spec_value);
}

/* READ-ICP-HISTORY-SPEC */
Object g2int_read_icp_history_spec()
{
    Object datapoint_count, datapoint_age, granularity;

    x_note_fn_call(47,108);
    datapoint_count = g2int_read_icp_fixnum();
    datapoint_age = g2int_read_icp_fixnum();
    granularity = g2int_read_icp_fixnum();
    return VALUES_3(FIXNUM_EQ(G2int_no_history_spec_value,datapoint_count) 
	    ? Nil : datapoint_count,FIXNUM_EQ(G2int_no_history_spec_value,
	    datapoint_age) ? Nil : datapoint_age,
	    FIXNUM_EQ(G2int_no_history_spec_value,granularity) ? Nil : 
	    granularity);
}

/* WRITE-ICP-EVALUATION-QUANTITY-OR-NIL */
Object g2int_write_icp_evaluation_quantity_or_nil(evaluation_quantity_or_nil)
    Object evaluation_quantity_or_nil;
{
    x_note_fn_call(47,109);
    if ( !TRUEP(evaluation_quantity_or_nil))
	return g2int_write_icp_byte(G2int_attribute_value_null_tag);
    else if (FIXNUMP(evaluation_quantity_or_nil)) {
	g2int_write_icp_byte(G2int_attribute_value_integer_tag);
	return g2int_write_icp_fixnum(evaluation_quantity_or_nil);
    }
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_quantity_or_nil) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) == 
	    (SI_Long)1L) {
	g2int_write_icp_byte(G2int_attribute_value_float_tag);
	return g2int_write_icp_managed_double_float(evaluation_quantity_or_nil);
    }
    else if (INLINE_LONG_VECTOR_P(evaluation_quantity_or_nil) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_quantity_or_nil)) == 
	    (SI_Long)1L) {
	g2int_write_icp_byte(G2int_attribute_value_long_tag);
	return g2int_write_icp_managed_long(evaluation_quantity_or_nil);
    }
    else
	return VALUES_1(Qnil);
}

/* READ-ICP-EVALUATION-QUANTITY-OR-NIL */
Object g2int_read_icp_evaluation_quantity_or_nil()
{
    Object tag;

    x_note_fn_call(47,110);
    tag = g2int_read_icp_byte();
    if ( !(FIXNUMP(tag) && FIXNUM_LE(FIX((SI_Long)-128L),tag) && 
	    FIXNUM_LE(tag,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(tag)) {
	  case 13:
	    return VALUES_1(Nil);
	  case 5:
	    return g2int_read_icp_fixnum();
	  case 6:
	    return g2int_read_icp_managed_double_float();
	  case 16:
	    return g2int_read_icp_managed_long();
	  default:
	    return VALUES_1(Nil);
	}
}

/* WRITE-ICP-DYNAMIC-HISTORY-INFO */
Object g2int_write_icp_dynamic_history_info(dynamic_history_info)
    Object dynamic_history_info;
{
    Object gensymed_symbol, base_time_qm, lowest_ever_qm, highest_ever_qm;
    Object time_at_start_qm;

    x_note_fn_call(47,111);
    gensymed_symbol = dynamic_history_info;
    base_time_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lowest_ever_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    highest_ever_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    time_at_start_qm = CAR(gensymed_symbol);
    g2int_write_icp_evaluation_quantity_or_nil(base_time_qm);
    g2int_write_icp_evaluation_quantity_or_nil(lowest_ever_qm);
    g2int_write_icp_evaluation_quantity_or_nil(highest_ever_qm);
    return g2int_write_icp_evaluation_quantity_or_nil(time_at_start_qm);
}

/* READ-ICP-DYNAMIC-HISTORY-INFO */
Object g2int_read_icp_dynamic_history_info()
{
    Object base_time_qm, lowest_ever_qm, highest_ever_qm, time_at_start_qm;

    x_note_fn_call(47,112);
    base_time_qm = g2int_read_icp_evaluation_quantity_or_nil();
    lowest_ever_qm = g2int_read_icp_evaluation_quantity_or_nil();
    highest_ever_qm = g2int_read_icp_evaluation_quantity_or_nil();
    time_at_start_qm = g2int_read_icp_evaluation_quantity_or_nil();
    return VALUES_4(base_time_qm,lowest_ever_qm,highest_ever_qm,
	    time_at_start_qm);
}

/* WRITE-ICP-ADD-ATTRIBUTE-HISTORY-OBJECT */
Object g2int_write_icp_add_attribute_history_object(attribute_spec_qm,
	    class_name,corresponding_index_of_class_name_qm,
	    symbolic_attribute_count,element_type_qm,
	    resumable_history_length,resumable_history_spec,
	    dynamic_history_info,timestamps_use_float_array_p,
	    values_use_float_array_p)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type_qm, resumable_history_length;
    Object resumable_history_spec, dynamic_history_info;
    Object timestamps_use_float_array_p, values_use_float_array_p;
{
    x_note_fn_call(47,113);
    g2int_write_icp_byte(G2int_add_attribute_history_object_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    g2int_write_icp_fixnum(symbolic_attribute_count);
    g2int_write_icp_resumable_sequence_element_type(element_type_qm);
    g2int_write_icp_fixnum(resumable_history_length);
    g2int_write_icp_boolean(timestamps_use_float_array_p);
    g2int_write_icp_boolean(values_use_float_array_p);
    g2int_write_icp_history_spec(resumable_history_spec);
    return g2int_write_icp_dynamic_history_info(dynamic_history_info);
}

/* READ-ICP-ADD-ATTRIBUTE-HISTORY-OBJECT */
Object g2int_read_icp_add_attribute_history_object()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type_qm;
    Object resumable_history_length, timestamps_use_float_array_p;
    Object values_use_float_array_p, datapoint_count, datapoint_age;
    Object granularity, base_time, lowest_ever_qm, highest_ever_qm;
    Object time_at_start_qm, new_history_item, type, gsi_instance_extension;
    Object svref_new_value;
    Object result;

    x_note_fn_call(47,114);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    element_type_qm = g2int_read_icp_resumable_sequence_element_type();
    resumable_history_length = g2int_read_icp_fixnum();
    timestamps_use_float_array_p = g2int_read_icp_boolean();
    values_use_float_array_p = g2int_read_icp_boolean();
    result = g2int_read_icp_history_spec();
    MVS_3(result,datapoint_count,datapoint_age,granularity);
    result = g2int_read_icp_dynamic_history_info();
    MVS_4(result,base_time,lowest_ever_qm,highest_ever_qm,time_at_start_qm);
    if (lowest_ever_qm)
	g2int_reclaim_managed_simple_float_array_of_length_1(lowest_ever_qm);
    if (highest_ever_qm)
	g2int_reclaim_managed_simple_float_array_of_length_1(highest_ever_qm);
    if (time_at_start_qm)
	g2int_reclaim_managed_simple_float_array_of_length_1(time_at_start_qm);
    new_history_item = g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    G2int_gsi_null_type_tag,FIX((SI_Long)0L),symbolic_attribute_count);
    type = element_type_qm ? 
	    g2int_gsi_type_from_g2_element_type(element_type_qm) : 
	    G2int_gsi_value_type_tag;
    g2int_set_gsi_instance_value_type(new_history_item,type);
    gsi_instance_extension = ISVREF(new_history_item,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(new_history_item,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    svref_new_value = g2int_make_gsi_history(8,new_history_item,
	    resumable_history_length,Nil,Nil,base_time,datapoint_count,
	    datapoint_age,granularity);
    return VALUES_1(SVREF(gsi_instance_extension,FIX((SI_Long)12L)) = 
	    svref_new_value);
}

/* WRITE-ICP-ADD-ATTRIBUTE-OBJECT-LIST */
Object g2int_write_icp_add_attribute_object_list(attribute_spec_qm,
	    class_name,corresponding_index_of_class_name_qm,
	    symbolic_attribute_count,resumable_list_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, resumable_list_length;
{
    x_note_fn_call(47,115);
    g2int_write_icp_byte(G2int_add_attribute_object_list_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    g2int_write_icp_fixnum(symbolic_attribute_count);
    return g2int_write_icp_fixnum(resumable_list_length);
}

/* READ-ICP-ADD-ATTRIBUTE-OBJECT-LIST */
Object g2int_read_icp_add_attribute_object_list()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, resumable_list_length;
    Object result;

    x_note_fn_call(47,116);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    resumable_list_length = g2int_read_icp_fixnum();
    return g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    G2int_gsi_item_list_type_tag,resumable_list_length,
	    symbolic_attribute_count);
}

/* WRITE-ICP-ADD-ATTRIBUTE-VALUE-LIST */
Object g2int_write_icp_add_attribute_value_list(attribute_spec_qm,
	    class_name,corresponding_index_of_class_name_qm,
	    symbolic_attribute_count,element_type,resumable_list_length)
    Object attribute_spec_qm, class_name, corresponding_index_of_class_name_qm;
    Object symbolic_attribute_count, element_type, resumable_list_length;
{
    x_note_fn_call(47,117);
    g2int_write_icp_byte(G2int_add_attribute_value_list_for_resumable_object_portion);
    g2int_write_icp_attribute_specqm(attribute_spec_qm);
    g2int_write_icp_possibly_interned_symbol(class_name,
	    corresponding_index_of_class_name_qm);
    g2int_write_icp_fixnum(symbolic_attribute_count);
    g2int_write_icp_resumable_sequence_element_type(element_type);
    return g2int_write_icp_fixnum(resumable_list_length);
}

/* READ-ICP-ADD-ATTRIBUTE-VALUE-LIST */
Object g2int_read_icp_add_attribute_value_list()
{
    Object attribute_type, attribute_qualifier_qm, attribute_name_or_index;
    Object class_name, symbolic_attribute_count, element_type;
    Object resumable_list_length;
    Object result;

    x_note_fn_call(47,118);
    result = g2int_read_icp_attribute_specqm();
    MVS_3(result,attribute_type,attribute_qualifier_qm,
	    attribute_name_or_index);
    class_name = g2int_read_icp_possibly_interned_symbol();
    symbolic_attribute_count = g2int_read_icp_fixnum();
    element_type = g2int_read_icp_resumable_sequence_element_type();
    resumable_list_length = g2int_read_icp_fixnum();
    return g2int_gsi_build_item_instance(attribute_type,
	    attribute_qualifier_qm,attribute_name_or_index,class_name,
	    g2int_gsi_list_type_from_g2_element_type(element_type),
	    resumable_list_length,symbolic_attribute_count);
}

/* WRITE-ICP-ADD-VALUE-VECTOR-RANGE */
Object g2int_write_icp_add_value_vector_range(number_of_elements,
	    resumable_node,interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    x_note_fn_call(47,119);
    g2int_write_icp_byte(G2int_add_value_vector_range_for_resumable_object_portion);
    return VALUES_1(interning_details_qm);
}

/* READ-ICP-ADD-VALUE-VECTOR-RANGE */
Object g2int_read_icp_add_value_vector_range()
{
    Object number_of_elements, highest_index, item, item_value;
    Object ab_loop_iter_flag_, attribute_value, value_type, svref_new_value;
    Object incff_1_arg, gsi_instance_extension;
    SI_Long ab_loop_repeat_, index_1, gensymed_symbol, gensymed_symbol_1;
    SI_Long svref_new_value_1;
    Object result;

    x_note_fn_call(47,120);
    number_of_elements = g2int_read_icp_fixnum();
    highest_index = g2int_read_icp_fixnum();
    item = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L);
    item_value = ISVREF(item,(SI_Long)2L);
    ab_loop_repeat_ = IFIX(number_of_elements);
    index_1 = IFIX(FIXNUM_ADD1(highest_index));
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 - (SI_Long)1L;
    result = g2int_read_icp_attribute_value();
    MVS_2(result,attribute_value,value_type);
    svref_new_value = g2int_make_gsi_instance(2,
	    g2int_gsi_type_from_leaf_type(value_type),attribute_value);
    ISVREF(item_value,index_1) = svref_new_value;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    incff_1_arg = number_of_elements;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    gensymed_symbol = gsi_instance_extension ? 
	    IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
    gensymed_symbol_1 = IFIX(incff_1_arg);
    svref_new_value_1 = gensymed_symbol + gensymed_symbol_1;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(svref_new_value_1);
    return VALUES_1(Qnil);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object g2int_write_icp_add_homogeneous_value_vector_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    x_note_fn_call(47,121);
    g2int_write_icp_byte(G2int_add_homogeneous_value_vector_range_for_resumable_object_portion);
    return VALUES_1(interning_details_qm);
}

Object G2int_gsi_wide_api_p = UNBOUND;

/* READ-ICP-ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE */
Object g2int_read_icp_add_homogeneous_value_vector_range()
{
    Object number_of_elements, element_type, highest_index, item, item_value;
    Object temp, ab_loop_iter_flag_, svref_new_value, symbol, incff_1_arg;
    Object gsi_instance_extension;
    SI_Long ab_loop_repeat_, index_1, temp_1, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    double aref_new_value;

    x_note_fn_call(47,122);
    number_of_elements = g2int_read_icp_fixnum();
    element_type = g2int_read_icp_resumable_sequence_element_type();
    highest_index = g2int_read_icp_fixnum();
    item = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L);
    item_value = ISVREF(item,(SI_Long)2L);
    temp = g2int_gsi_type_from_g2_element_type(element_type);
    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
	    FIXNUM_LE(temp,FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	  case 5:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    temp_1 = IFIX(g2int_read_icp_fixnum());
	    BYTE_32_ISASET_1(item_value,index_1,temp_1);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:;
	    break;
	  case 6:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    aref_new_value = g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(item_value,index_1,aref_new_value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	    break;
	  case 4:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    svref_new_value = 
		    inline_extract_c_string(g2int_convert_value_to_gsi_value(g2int_read_icp_text_string()));
	    ISVREF(item_value,index_1) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_2;
	  end_loop_2:;
	    break;
	  case 3:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(highest_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 - (SI_Long)1L;
	    symbol = g2int_read_icp_possibly_interned_symbol();
	    svref_new_value = 
		    g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) ? 
		    symbol : 
		    inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
		    G2int_gsi_wide_api_p));
	    ISVREF(item_value,index_1) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:;
	    break;
	  default:
	    break;
	}
    incff_1_arg = number_of_elements;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    gensymed_symbol = gsi_instance_extension ? 
	    IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
    gensymed_symbol_1 = IFIX(incff_1_arg);
    temp_1 = gensymed_symbol + gensymed_symbol_1;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    return VALUES_1(ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(temp_1));
}

/* WRITE-ICP-ADD-HISTORY-RANGE */
Object g2int_write_icp_add_history_range(resumable_node,
	    number_of_cached_elements,cached_interning_details_qm,
	    ring_index_of_first_uncached_element,
	    number_of_uncached_elements,uncached_interning_details_qm,
	    timestamps_use_float_array_p,values_use_float_array_p)
    Object resumable_node, number_of_cached_elements;
    Object cached_interning_details_qm, ring_index_of_first_uncached_element;
    Object number_of_uncached_elements, uncached_interning_details_qm;
    Object timestamps_use_float_array_p, values_use_float_array_p;
{
    x_note_fn_call(47,123);
    g2int_write_icp_byte(G2int_add_history_range_for_resumable_object_portion);
    g2int_write_icp_boolean(timestamps_use_float_array_p);
    g2int_write_icp_boolean(values_use_float_array_p);
    g2int_write_icp_fixnum(FIXNUM_ADD(number_of_cached_elements,
	    number_of_uncached_elements));
    return VALUES_1(uncached_interning_details_qm);
}

/* READ-ICP-ADD-HISTORY-RANGE */
Object g2int_read_icp_add_history_range()
{
    Object timestamps_use_float_array_p, values_use_float_array_p;
    Object number_of_elements;

    x_note_fn_call(47,124);
    timestamps_use_float_array_p = g2int_read_icp_boolean();
    values_use_float_array_p = g2int_read_icp_boolean();
    number_of_elements = g2int_read_icp_fixnum();
    return g2int_gsi_receive_add_history_range(timestamps_use_float_array_p,
	    values_use_float_array_p,number_of_elements);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object g2int_write_icp_add_homogeneous_history_range(resumable_node,
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
    x_note_fn_call(47,125);
    g2int_write_icp_byte(G2int_add_homogeneous_history_range_for_resumable_object_portion);
    g2int_write_icp_boolean(timestamps_use_float_array_p);
    g2int_write_icp_resumable_sequence_element_type(element_type);
    g2int_write_icp_fixnum(FIXNUM_ADD(number_of_cached_elements,
	    number_of_uncached_elements));
    return VALUES_1(uncached_interning_details_qm);
}

/* READ-ICP-ADD-HOMOGENEOUS-HISTORY-RANGE */
Object g2int_read_icp_add_homogeneous_history_range()
{
    Object timestamps_use_float_array_p, element_type, number_of_elements;

    x_note_fn_call(47,126);
    timestamps_use_float_array_p = g2int_read_icp_boolean();
    element_type = g2int_read_icp_resumable_sequence_element_type();
    number_of_elements = g2int_read_icp_fixnum();
    return g2int_gsi_receive_add_homogeneous_history_range(timestamps_use_float_array_p,
	    element_type,number_of_elements);
}

/* WRITE-ICP-ADD-VALUE-LIST-RANGE */
Object g2int_write_icp_add_value_list_range(number_of_elements,
	    resumable_node,interning_details_qm)
    Object number_of_elements, resumable_node, interning_details_qm;
{
    x_note_fn_call(47,127);
    g2int_write_icp_byte(G2int_add_value_list_range_for_resumable_object_portion);
    return VALUES_1(interning_details_qm);
}

/* READ-ICP-ADD-VALUE-LIST-RANGE */
Object g2int_read_icp_add_value_list_range()
{
    Object number_of_elements, item, list_1, gsi_instance_extension;
    Object ab_loop_iter_flag_, attribute_value, value_type, svref_new_value;
    Object incff_1_arg;
    SI_Long ab_loop_repeat_, gensymed_symbol, gensymed_symbol_1, index_1;
    SI_Long svref_new_value_1;
    Object result;

    x_note_fn_call(47,128);
    number_of_elements = g2int_read_icp_fixnum();
    item = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L);
    list_1 = ISVREF(item,(SI_Long)2L);
    ab_loop_repeat_ = IFIX(number_of_elements);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    gensymed_symbol = gsi_instance_extension ? 
	    IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
    gensymed_symbol_1 = IFIX(G2int_gsi_magic_offset);
    index_1 = gensymed_symbol + gensymed_symbol_1;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    result = g2int_read_icp_attribute_value();
    MVS_2(result,attribute_value,value_type);
    svref_new_value = g2int_make_gsi_instance(2,
	    g2int_gsi_type_from_leaf_type(value_type),attribute_value);
    ISVREF(list_1,index_1) = svref_new_value;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    incff_1_arg = number_of_elements;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    gensymed_symbol = gsi_instance_extension ? 
	    IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
    gensymed_symbol_1 = IFIX(incff_1_arg);
    svref_new_value_1 = gensymed_symbol + gensymed_symbol_1;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(svref_new_value_1);
    return VALUES_1(Qnil);
}

/* WRITE-ICP-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object g2int_write_icp_add_homogeneous_value_list_range(number_of_elements,
	    element_type,resumable_node,interning_details_qm)
    Object number_of_elements, element_type, resumable_node;
    Object interning_details_qm;
{
    x_note_fn_call(47,129);
    g2int_write_icp_byte(G2int_add_homogeneous_value_list_range_for_resumable_object_portion);
    return VALUES_1(interning_details_qm);
}

/* READ-ICP-ADD-HOMOGENEOUS-VALUE-LIST-RANGE */
Object g2int_read_icp_add_homogeneous_value_list_range()
{
    Object number_of_elements, element_type, item, item_value;
    Object gsi_instance_extension, next_index, temp, ab_loop_iter_flag_;
    Object svref_new_value, symbol, incff_1_arg;
    SI_Long ab_loop_repeat_, index_1, temp_1, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    double aref_new_value;

    x_note_fn_call(47,130);
    number_of_elements = g2int_read_icp_fixnum();
    element_type = g2int_read_icp_resumable_sequence_element_type();
    item = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L);
    item_value = ISVREF(item,(SI_Long)2L);
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    next_index = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)7L) : FIX((SI_Long)0L);
    temp = g2int_gsi_type_from_g2_element_type(element_type);
    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
	    FIXNUM_LE(temp,FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 1:
	  case 5:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(next_index);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 + (SI_Long)1L;
	    temp_1 = IFIX(g2int_read_icp_fixnum());
	    BYTE_32_ISASET_1(item_value,index_1,temp_1);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:;
	    break;
	  case 6:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(next_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_1;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 + (SI_Long)1L;
	    aref_new_value = g2int_read_icp_double_float_1();
	    DFLOAT_ISASET_1(item_value,index_1,aref_new_value);
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	    break;
	  case 4:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(next_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_2:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_2;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 + (SI_Long)1L;
	    svref_new_value = 
		    inline_extract_c_string(g2int_convert_value_to_gsi_value(g2int_read_icp_text_string()));
	    ISVREF(item_value,index_1) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_2;
	  end_loop_2:;
	    break;
	  case 3:
	    ab_loop_repeat_ = IFIX(number_of_elements);
	    index_1 = IFIX(next_index);
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop_3;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index_1 = index_1 + (SI_Long)1L;
	    symbol = g2int_read_icp_possibly_interned_symbol();
	    svref_new_value = 
		    g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) ? 
		    symbol : 
		    inline_extract_c_string(g2int_gsi_string_for_symbol(symbol,
		    G2int_gsi_wide_api_p));
	    ISVREF(item_value,index_1) = svref_new_value;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:;
	    break;
	  default:
	    break;
	}
    incff_1_arg = number_of_elements;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    gensymed_symbol = gsi_instance_extension ? 
	    IFIX(ISVREF(gsi_instance_extension,(SI_Long)7L)) : (SI_Long)0L;
    gensymed_symbol_1 = IFIX(incff_1_arg);
    temp_1 = gensymed_symbol + gensymed_symbol_1;
    gsi_instance_extension = ISVREF(item,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(item,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    return VALUES_1(ISVREF(gsi_instance_extension,(SI_Long)7L) = FIX(temp_1));
}

/* WRITE-ICP-ASCEND-TO-PARENT */
Object g2int_write_icp_ascend_to_parent(ascension_count)
    Object ascension_count;
{
    x_note_fn_call(47,131);
    g2int_write_icp_byte(G2int_ascend_to_parent_for_resumable_object_portion);
    return g2int_write_icp_fixnum(ascension_count);
}

static Object Qg2int_gsi_superior_item;  /* gsi-superior-item */

/* READ-ICP-ASCEND-TO-PARENT */
Object g2int_read_icp_ascend_to_parent()
{
    Object ascension_count, ancestor, svref_arg_1;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(47,132);
    ascension_count = g2int_read_icp_fixnum();
    ab_loop_repeat_ = IFIX(ascension_count);
    ancestor = ISVREF(G2int_current_receiving_resumable_object,(SI_Long)8L);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    ancestor = g2int_get_gsi_instance_plist_value(ancestor,
	    Qg2int_gsi_superior_item);
    goto next_loop;
  end_loop:
    svref_arg_1 = G2int_current_receiving_resumable_object;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = ancestor;
    return VALUES_1(Qnil);
}

/* WRITE-ICP-SUSPEND-BUILDING-OBJECT */
Object g2int_write_icp_suspend_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(47,133);
    g2int_write_icp_byte(G2int_suspend_building_object_for_resumable_object_portion);
    return g2int_write_icp_fixnum(bandwidth_consumed);
}

static Object Qg2int_exit_from_resumable_object_portion;  /* exit-from-resumable-object-portion */

/* READ-ICP-SUSPEND-BUILDING-OBJECT */
Object g2int_read_icp_suspend_building_object()
{
    Object bandwidth_consumed, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(47,134);
    bandwidth_consumed = g2int_read_icp_fixnum();
    if (IFIX(bandwidth_consumed) > (SI_Long)0L) {
	current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	    temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		    (SI_Long)53L) : Nil;
	    if (temp);
	    else
		temp = Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(G2int_writing_icp_message_group);
			      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					&&  
					!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					    {
				    g2int_send_icp_update_object_passing_network_resources(bandwidth_consumed,
					    G2int_no_resumable_object_index,
					    Nil);
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
    }
    G2int_rpc_throw_tag = Qg2int_exit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

/* WRITE-ICP-FINISH-BUILDING-OBJECT */
Object g2int_write_icp_finish_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(47,135);
    g2int_write_icp_byte(G2int_finish_building_object_for_resumable_object_portion);
    return g2int_write_icp_fixnum(bandwidth_consumed);
}

/* READ-ICP-FINISH-BUILDING-OBJECT */
Object g2int_read_icp_finish_building_object()
{
    Object bandwidth_consumed;

    x_note_fn_call(47,136);
    bandwidth_consumed = g2int_read_icp_fixnum();
    return g2int_receive_finish_building_object(bandwidth_consumed);
}

/* WRITE-ICP-ABORT-BUILDING-OBJECT */
Object g2int_write_icp_abort_building_object(bandwidth_consumed)
    Object bandwidth_consumed;
{
    x_note_fn_call(47,137);
    g2int_write_icp_byte(G2int_abort_building_object_for_resumable_object_portion);
    return g2int_write_icp_fixnum(bandwidth_consumed);
}

/* READ-ICP-ABORT-BUILDING-OBJECT */
Object g2int_read_icp_abort_building_object()
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
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(47,138);
    bandwidth_consumed = g2int_read_icp_fixnum();
    resumable_object_index = 
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)11L);
    resumable_instance_node_indices = 
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)12L);
    current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = Nil;
	disable_resumability = temp;
	PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(G2int_writing_icp_message_group);
			  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
				    &&  
				    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					{
				g2int_send_icp_update_object_passing_network_resources(bandwidth_consumed,
					resumable_object_index,
					resumable_instance_node_indices);
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
    g2int_reclaim_receiving_resumable_object(G2int_current_receiving_resumable_object);
    G2int_rpc_throw_tag = Qg2int_exit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

/* WRITE-ICP-RESUMABLE-OBJECT-PORTION */
Object g2int_write_icp_resumable_object_portion(resumable_object_portion)
    Object resumable_object_portion;
{
    x_note_fn_call(47,139);
    return g2int_write_icp_fixnum(g2int_get_icp_object_index_for_gsi_instance(resumable_object_portion,
	    G2int_current_icp_port));
}

/* READ-ICP-RESUMABLE-OBJECT-PORTION */
Object g2int_read_icp_resumable_object_portion()
{
    x_note_fn_call(47,140);
    return g2int_read_icp_fixnum();
}

/* WRITE-ICP-RESUMABLE-NODE-INDICES */
Object g2int_write_icp_resumable_node_indices(resumable_node_indices)
    Object resumable_node_indices;
{
    Object length_1, index_1, ab_loop_list_;

    x_note_fn_call(47,141);
    length_1 = length(resumable_node_indices);
    g2int_write_icp_fixnum(length_1);
    index_1 = Nil;
    ab_loop_list_ = resumable_node_indices;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    index_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_write_icp_fixnum(index_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* READ-ICP-RESUMABLE-NODE-INDICES */
Object g2int_read_icp_resumable_node_indices()
{
    Object length_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long count_1, ab_loop_bind_;

    x_note_fn_call(47,142);
    length_1 = g2int_read_icp_fixnum();
    count_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(length_1);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (count_1 > ab_loop_bind_)
	goto end_loop;
    ab_loopvar__2 = g2int_gensym_cons_1(g2int_read_icp_fixnum(),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qg2int_item_index_space;  /* item-index-space */

static Object Qg2int_frame_serial_number;  /* frame-serial-number */

/* RECLAIM-INDEX-FOR-RESUMABLE-OBJECT */
Object g2int_reclaim_index_for_resumable_object(index_1,output_port_p)
    Object index_1, output_port_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1, old_entry;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(47,143);
    port = G2int_current_icp_port;
    if (EQ(Qg2int_standard_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(Qg2int_standard_icp_object_index_space,
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
    else if (EQ(Qg2int_standard_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(G2int_current_icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(G2int_current_icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = 
		g2int_frame_serial_number_to_item_table(G2int_current_icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	g2int_set_balanced_binary_tree_entry(SVREF(index_space,
		FIX(temp_2)),Qeq,
		G2int_fp_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry,
		T,index_1,FIX(gensymed_symbol),Nil);
    }
    else {
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    g2int_enlarge_index_space(index_space,index_1);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) 
		>>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    if (output_port_p) {
	if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	    gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	    temp_2 = gensymed_symbol % (SI_Long)67L;
	    result = g2int_delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		    index_1,SVREF(index_space,FIX(temp_2)),
		    FIX(gensymed_symbol));
	    old_entry = NTH_VALUE((SI_Long)1L, result);
	    g2int_note_item_deleted_from_frame_serial_number_table(old_entry);
	}
	else
	    g2int_deassign_index_in_index_space(index_1,index_space);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-INDEX-FOR-RESUMABLE-INSTANCE-NODE */
Object g2int_reclaim_index_for_resumable_instance_node(index_1,output_port_p)
    Object index_1, output_port_p;
{
    Object port, index_space_name, icp_socket, temp, temp_1, index_space;
    Object svref_arg_1, old_entry;
    SI_Long gensymed_symbol, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(47,144);
    port = G2int_current_icp_port;
    if (EQ(Qg2int_standard_icp_object_index_space,
	    Qg2int_standard_icp_object_index_space))
	index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(Qg2int_standard_icp_object_index_space,
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
    else if (EQ(Qg2int_standard_icp_object_index_space,
	    Qg2int_frame_serial_number))
	index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		Qg2int_item_index_space : Qg2int_frame_serial_number;
    else
	index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(G2int_current_icp_port,(SI_Long)8L);
    else if (EQ(index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(G2int_current_icp_port);
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	index_space = 
		g2int_frame_serial_number_to_item_table(G2int_current_icp_port);
    else
	index_space = Qnil;
    if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	g2int_set_balanced_binary_tree_entry(SVREF(index_space,
		FIX(temp_2)),Qeq,
		G2int_fp_mutate_frame_serial_number_to_item_table_tree_for_hash_tree_entry,
		T,index_1,FIX(gensymed_symbol),Nil);
    }
    else {
	if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
	    g2int_enlarge_index_space(index_space,index_1);
	svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),IFIX(index_1) 
		>>  -  - (SI_Long)10L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    if (output_port_p) {
	if (EQ(index_space_name,Qg2int_frame_serial_number)) {
	    gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	    temp_2 = gensymed_symbol % (SI_Long)67L;
	    result = g2int_delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		    index_1,SVREF(index_space,FIX(temp_2)),
		    FIX(gensymed_symbol));
	    old_entry = NTH_VALUE((SI_Long)1L, result);
	    g2int_note_item_deleted_from_frame_serial_number_table(old_entry);
	}
	else
	    g2int_deassign_index_in_index_space(index_1,index_space);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-INDICES-ASSOCIATED-WITH-RESUMABLE-OBJECT */
Object g2int_reclaim_indices_associated_with_resumable_object(resumable_object_index,
	    resumable_instance_node_indices,output_port_p)
    Object resumable_object_index, resumable_instance_node_indices;
    Object output_port_p;
{
    Object index_1, ab_loop_list_;

    x_note_fn_call(47,145);
    if (FIXNUM_NE(resumable_object_index,G2int_no_resumable_object_index))
	g2int_reclaim_index_for_resumable_object(resumable_object_index,
		output_port_p);
    index_1 = Nil;
    ab_loop_list_ = resumable_instance_node_indices;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    index_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2int_reclaim_index_for_resumable_instance_node(index_1,output_port_p);
    goto next_loop;
  end_loop:;
    return g2int_reclaim_gensym_list_1(resumable_instance_node_indices);
}

/* RECEIVE-FINISH-BUILDING-OBJECT */
Object g2int_receive_finish_building_object(bandwidth_consumed)
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
    Object gensymed_symbol, rpc_arglist_structure_qm;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(47,146);
    resumable_object_index = 
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)11L);
    resumable_instance_node_indices = 
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)12L);
    current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = Nil;
	disable_resumability = temp;
	PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(G2int_writing_icp_message_group);
			  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
				    &&  
				    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					{
				g2int_send_icp_update_object_passing_network_resources(bandwidth_consumed,
					resumable_object_index,
					resumable_instance_node_indices);
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
    g2int_reclaim_indices_associated_with_resumable_object(resumable_object_index,
	    resumable_instance_node_indices,Nil);
    rpc_arglist_structure_qm = 
	    ISVREF(G2int_current_receiving_resumable_object,(SI_Long)9L);
    if (rpc_arglist_structure_qm)
	g2int_gsi_check_if_all_items_are_built(rpc_arglist_structure_qm);
    else;
    G2int_rpc_throw_tag = Qg2int_exit_from_resumable_object_portion;
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_update_object_passing_network_resources;  /* send-icp-update-object-passing-network-resources */

/* SEND-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES */
Object g2int_send_icp_update_object_passing_network_resources(freed,
	    resumable_object_index,resumable_node_indices)
    Object freed, resumable_object_index, resumable_node_indices;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,147);
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
		      Qg2int_send_icp_update_object_passing_network_resources;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)321L));
	  g2int_write_icp_fixnum(freed);
	  g2int_write_icp_fixnum(resumable_object_index);
	  g2int_write_icp_resumable_node_indices(resumable_node_indices);
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
		    !EQ(Qg2int_send_icp_update_object_passing_network_resources,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_update_object_passing_network_resources,
			top,Nil);
		goto end_send_icp_update_object_passing_network_resources;
	    }
	}
	freed = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : freed;
	resumable_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : resumable_object_index;
	resumable_node_indices = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : resumable_node_indices;
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
		      Qg2int_send_icp_update_object_passing_network_resources;
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
		  g2int_start_writing_icp_message(FIX((SI_Long)321L)))) {
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
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_fixnum(freed))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_fixnum(resumable_object_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_node_indices(resumable_node_indices))) 
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
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(resumable_node_indices);
	      g2int_resumable_icp_push(resumable_object_index);
	      g2int_resumable_icp_push(freed);
	      g2int_resumable_icp_push(Qg2int_send_icp_update_object_passing_network_resources);
	      result = VALUES_1(G2int_icp_suspend);
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
Object g2int_handle_icp_update_object_passing_network_resources__body(freed,
	    resumable_object_index,resumable_node_indices)
    Object freed, resumable_object_index, resumable_node_indices;
{
    Object current_icp_port, svref_arg_1, incff_1_arg, svref_new_value;
    Declare_special(1);

    x_note_fn_call(47,148);
    current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,0);
      g2int_reclaim_indices_associated_with_resumable_object(resumable_object_index,
	      resumable_node_indices,T);
    POP_SPECIAL();
    svref_arg_1 = G2int_current_icp_socket;
    incff_1_arg = freed;
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,(SI_Long)30L),incff_1_arg);
    SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_update_object_passing_network_resources;  /* handle-icp-update-object-passing-network-resources */

/* HANDLE-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES */
Object g2int_handle_icp_update_object_passing_network_resources()
{
    Object freed, resumable_object_index, resumable_node_indices;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,149);
    if (G2int_disable_resumability) {
	freed = g2int_read_icp_fixnum();
	resumable_object_index = g2int_read_icp_fixnum();
	resumable_node_indices = g2int_read_icp_resumable_node_indices();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_update_object_passing_network_resources__body(freed,
		  resumable_object_index,resumable_node_indices);
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
		    !EQ(Qg2int_handle_icp_update_object_passing_network_resources,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_update_object_passing_network_resources,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    freed = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_update_object_passing_network_resources);
		return VALUES_1(G2int_icp_suspend);
	    }
	    freed = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    resumable_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(freed);
		g2int_resumable_icp_push(Qg2int_handle_icp_update_object_passing_network_resources);
		return VALUES_1(G2int_icp_suspend);
	    }
	    resumable_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    resumable_node_indices = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_node_indices();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(resumable_object_index);
		g2int_resumable_icp_push(freed);
		g2int_resumable_icp_push(Qg2int_handle_icp_update_object_passing_network_resources);
		return VALUES_1(G2int_icp_suspend);
	    }
	    resumable_node_indices = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_update_object_passing_network_resources__body(freed,
		  resumable_object_index,resumable_node_indices);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_toplevel_object_has_been_deleted_on_receiving_side;  /* toplevel-object-has-been-deleted-on-receiving-side */

static Object Qg2int_rpc_arg_list;  /* rpc-arg-list */

/* BODY-OF-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object g2int_body_of_continue_building_resumable_object(resumable_object_portion)
    Object resumable_object_portion;
{
    Object resumable_object_qm, current_receiving_resumable_object;
    Object do_not_initialize_g2_array_elements_p, toplevel_object_qm;
    Object rpc_throw_tag, gsi_reclaim_list_level, icp_tag;
    Declare_special(4);
    Object result;

    x_note_fn_call(47,150);
    resumable_object_qm = g2int_get_from_icp_port(G2int_current_icp_port,
	    resumable_object_portion,Qg2int_standard_icp_object_index_space);
    if (resumable_object_qm) {
	current_receiving_resumable_object = resumable_object_qm;
	do_not_initialize_g2_array_elements_p = T;
	toplevel_object_qm = ISVREF(resumable_object_qm,(SI_Long)7L);
	PUSH_SPECIAL(G2int_do_not_initialize_g2_array_elements_p,do_not_initialize_g2_array_elements_p,
		3);
	  PUSH_SPECIAL(G2int_current_receiving_resumable_object,current_receiving_resumable_object,
		  2);
	    if (toplevel_object_qm && T)
		g2int_record_object_building_problem_on_receiving_side_1(Qg2int_toplevel_object_has_been_deleted_on_receiving_side,
			Nil,Nil,Nil,Nil,Nil,Nil);
	    rpc_throw_tag = Nil;
	    PUSH_SPECIAL(G2int_rpc_throw_tag,rpc_throw_tag,1);
	    next_loop:
	      gsi_reclaim_list_level = Qg2int_rpc_arg_list;
	      icp_tag = g2int_read_icp_byte();
	      PUSH_SPECIAL(G2int_gsi_reclaim_list_level,gsi_reclaim_list_level,
		      0);
		if (! !(FIXNUMP(icp_tag) && FIXNUM_LE(FIX((SI_Long)-128L),
			icp_tag) && FIXNUM_LE(icp_tag,FIX((SI_Long)127L))))
		    switch (INTEGER_TO_CHAR(icp_tag)) {
		      case 13:
			g2int_read_icp_abort_building_object();
			break;
		      case 12:
			g2int_read_icp_finish_building_object();
			break;
		      case 11:
			g2int_read_icp_suspend_building_object();
			break;
		      case 10:
			g2int_read_icp_ascend_to_parent();
			break;
		      case 15:
			g2int_read_icp_add_homogeneous_value_list_range();
			break;
		      case 9:
			g2int_read_icp_add_value_list_range();
			break;
		      case 19:
			g2int_read_icp_add_homogeneous_history_range();
			break;
		      case 18:
			g2int_read_icp_add_history_range();
			break;
		      case 14:
			g2int_read_icp_add_homogeneous_value_vector_range();
			break;
		      case 8:
			g2int_read_icp_add_value_vector_range();
			break;
		      case 7:
			g2int_read_icp_add_attribute_value_list();
			break;
		      case 6:
			g2int_read_icp_add_attribute_object_list();
			break;
		      case 17:
			g2int_read_icp_add_attribute_history_object();
			break;
		      case 5:
			g2int_read_icp_add_attribute_value_vector();
			break;
		      case 4:
			g2int_read_icp_add_attribute_object_vector();
			break;
		      case 16:
			g2int_read_icp_add_resumable_circularity();
			break;
		      case 3:
			g2int_read_icp_add_attribute_object();
			break;
		      case 2:
			g2int_read_icp_add_circular_attribute();
			break;
		      case 1:
			g2int_read_icp_add_attribute_value();
			break;
		      default:
			break;
		    }
	      POP_SPECIAL();
	      if (G2int_rpc_throw_tag) {
		  result = VALUES_1(Nil);
		  goto end;
	      }
	      goto next_loop;
	    end_loop:
	      result = VALUES_1(Qnil);
	    end:;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_send_icp_continue_building_resumable_object;  /* send-icp-continue-building-resumable-object */

/* SEND-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object g2int_send_icp_continue_building_resumable_object(resumable_object_portion)
    Object resumable_object_portion;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,151);
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
		      Qg2int_send_icp_continue_building_resumable_object;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)320L));
	  g2int_write_icp_resumable_object_portion(resumable_object_portion);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_continue_building_resumable_object,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_continue_building_resumable_object,
			top,Nil);
		goto end_send_icp_continue_building_resumable_object;
	    }
	}
	resumable_object_portion = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : resumable_object_portion;
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
		      Qg2int_send_icp_continue_building_resumable_object;
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
		  g2int_start_writing_icp_message(FIX((SI_Long)320L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_resumable_object_portion(resumable_object_portion))) 
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
	      g2int_resumable_icp_push(resumable_object_portion);
	      g2int_resumable_icp_push(Qg2int_send_icp_continue_building_resumable_object);
	      result = VALUES_1(G2int_icp_suspend);
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
Object g2int_handle_icp_continue_building_resumable_object__body(resumable_object_portion)
    Object resumable_object_portion;
{
    x_note_fn_call(47,152);
    g2int_body_of_continue_building_resumable_object(resumable_object_portion);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_continue_building_resumable_object;  /* handle-icp-continue-building-resumable-object */

/* HANDLE-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT */
Object g2int_handle_icp_continue_building_resumable_object()
{
    Object resumable_object_portion, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,153);
    if (G2int_disable_resumability) {
	resumable_object_portion = g2int_read_icp_resumable_object_portion();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_continue_building_resumable_object,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_continue_building_resumable_object,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    resumable_object_portion = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_resumable_object_portion();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_continue_building_resumable_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    resumable_object_portion = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_continue_building_resumable_object__body(resumable_object_portion);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GSI-RECORD-RPC-NAME-IN-ALL-RECEIVING-RESUMABLE-OBJECTS */
Object g2int_gsi_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
	    item)
    Object remote_procedure_name, item;
{
    Object my_item_qm, svref_new_value;

    x_note_fn_call(47,154);
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
Object g2int_g2_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
	    rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object argument, ab_loop_list_, typical_resumable_object_qm;
    Object initial_resumable_var, typical_resumable_object_qm_1;
    Object svref_new_value;

    x_note_fn_call(47,155);
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
	goto end;
    }
    goto next_loop;
  end_loop:
    typical_resumable_object_qm = Qnil;
  end:;
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
Object g2int_twrite_gsi_rpc_backtrace_info()
{
    Object temp, index_of_top_of_backtrace_stack_new_value;

    x_note_fn_call(47,156);
    g2int_twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)7L));
    if (IFIX(G2int_index_of_top_of_backtrace_stack) < (SI_Long)0L)
	temp = Nil;
    else {
	temp = ISVREF(G2int_backtrace_stack_for_internal_error,
		IFIX(G2int_index_of_top_of_backtrace_stack));
	index_of_top_of_backtrace_stack_new_value = 
		FIXNUM_SUB1(G2int_index_of_top_of_backtrace_stack);
	G2int_index_of_top_of_backtrace_stack = 
		index_of_top_of_backtrace_stack_new_value;
    }
    g2int_twrite(temp);
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_rpc_start;  /* send-icp-rpc-start */

/* SEND-ICP-RPC-START */
Object g2int_send_icp_rpc_start(remote_procedure_name,rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,157);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_start;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)230L));
	  g2int_write_icp_corresponding_object_index(remote_procedure_name);
	  g2int_write_icp_rpc_argument_list(rpc_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_start,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_rpc_start,top,Nil);
		goto end_send_icp_rpc_start;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : rpc_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_start;
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
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)230L)))) {
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
		  g2int_write_icp_corresponding_object_index(remote_procedure_name))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_rpc_argument_list(rpc_argument_list))) {
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
	      g2int_resumable_icp_push(rpc_argument_list);
	      g2int_resumable_icp_push(remote_procedure_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_start);
	      result = VALUES_1(G2int_icp_suspend);
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

static Object Qg2int_start;        /* start */

static Object Qg2int_gsi;          /* gsi */

/* HANDLE-ICP-RPC-START--BODY */
Object g2int_handle_icp_rpc_start__body(remote_procedure_name,
	    rpc_argument_list)
    Object remote_procedure_name, rpc_argument_list;
{
    Object item_among_arguments_qm, rpc_arglist_structure, svref_new_value;

    x_note_fn_call(47,158);
    item_among_arguments_qm = g2int_get_item_from_arguments(rpc_argument_list);
    if (item_among_arguments_qm) {
	rpc_arglist_structure = ISVREF(item_among_arguments_qm,(SI_Long)9L);
	SVREF(rpc_arglist_structure,FIX((SI_Long)3L)) = remote_procedure_name;
	SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qg2int_start;
	g2int_gsi_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
		item_among_arguments_qm);
	svref_new_value = G2int_gsi_reclaim_listqm;
	SVREF(rpc_arglist_structure,FIX((SI_Long)7L)) = svref_new_value;
	G2int_gsi_reclaim_listqm = Nil;
    }
    else {
	g2int_gsi_start_or_call_local_function_or_handle_return_values(Qg2int_start,
		remote_procedure_name,Nil,rpc_argument_list);
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_start;  /* handle-icp-rpc-start */

/* HANDLE-ICP-RPC-START */
Object g2int_handle_icp_rpc_start()
{
    Object index_1, index_space, remote_procedure_name, rpc_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,159);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    remote_procedure_name = Nil;
	rpc_argument_list = g2int_read_icp_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_start__body(remote_procedure_name,
		  rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_start,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_rpc_start,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_name = g2int_resumable_icp_pop();
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
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_start);
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
		remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		remote_procedure_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    rpc_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_procedure_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_start);
		return VALUES_1(G2int_icp_suspend);
	    }
	    rpc_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_start__body(remote_procedure_name,
		  rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_call;  /* send-icp-rpc-call */

/* SEND-ICP-RPC-CALL */
Object g2int_send_icp_rpc_call(remote_procedure_name,
	    remote_procedure_identifier,rpc_argument_list)
    Object remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,160);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_call;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	  remote_procedure_name = temp_1;
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_identifier,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier);
	  remote_procedure_identifier = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)231L));
	  g2int_write_icp_corresponding_object_index(remote_procedure_name);
	  g2int_write_icp_corresponding_object_index(remote_procedure_identifier);
	  g2int_write_icp_rpc_argument_list(rpc_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_call,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_rpc_call,top,Nil);
		goto end_send_icp_rpc_call;
	    }
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_identifier;
	rpc_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : rpc_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_call;
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
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_name = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name = value_1;
	  }
	l2:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(remote_procedure_identifier,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_identifier = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_identifier = value_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)231L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l4:
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
		  g2int_write_icp_corresponding_object_index(remote_procedure_name))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(remote_procedure_identifier))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_rpc_argument_list(rpc_argument_list))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(rpc_argument_list);
	      g2int_resumable_icp_push(remote_procedure_identifier);
	      g2int_resumable_icp_push(remote_procedure_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_call);
	      result = VALUES_1(G2int_icp_suspend);
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

static Object Qg2int_call;         /* call */

/* HANDLE-ICP-RPC-CALL--BODY */
Object g2int_handle_icp_rpc_call__body(remote_procedure_name,
	    remote_procedure_identifier,rpc_argument_list)
    Object remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object item_among_arguments_qm, rpc_arglist_structure, svref_new_value;

    x_note_fn_call(47,161);
    item_among_arguments_qm = g2int_get_item_from_arguments(rpc_argument_list);
    if (item_among_arguments_qm) {
	rpc_arglist_structure = ISVREF(item_among_arguments_qm,(SI_Long)9L);
	SVREF(rpc_arglist_structure,FIX((SI_Long)3L)) = remote_procedure_name;
	SVREF(rpc_arglist_structure,FIX((SI_Long)4L)) = 
		remote_procedure_identifier;
	SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qg2int_call;
	g2int_gsi_record_rpc_name_in_all_receiving_resumable_objects(remote_procedure_name,
		item_among_arguments_qm);
	svref_new_value = G2int_gsi_reclaim_listqm;
	SVREF(rpc_arglist_structure,FIX((SI_Long)7L)) = svref_new_value;
	G2int_gsi_reclaim_listqm = Nil;
    }
    else {
	g2int_gsi_start_or_call_local_function_or_handle_return_values(Qg2int_call,
		remote_procedure_name,remote_procedure_identifier,
		rpc_argument_list);
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_call;  /* handle-icp-rpc-call */

/* HANDLE-ICP-RPC-CALL */
Object g2int_handle_icp_rpc_call()
{
    Object index_1, index_space, remote_procedure_name;
    Object remote_procedure_identifier, rpc_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,162);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    remote_procedure_name = Nil;
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_identifier = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    remote_procedure_identifier = Nil;
	rpc_argument_list = g2int_read_icp_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_call__body(remote_procedure_name,
		  remote_procedure_identifier,rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_call,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_rpc_call,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_name = g2int_resumable_icp_pop();
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
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_call);
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
		remote_procedure_name = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		remote_procedure_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_identifier = g2int_resumable_icp_pop();
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
		    g2int_resumable_icp_push(remote_procedure_name);
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_call);
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
		remote_procedure_identifier = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		remote_procedure_identifier = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    rpc_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_procedure_identifier);
		g2int_resumable_icp_push(remote_procedure_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_call);
		return VALUES_1(G2int_icp_suspend);
	    }
	    rpc_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_call__body(remote_procedure_name,
		  remote_procedure_identifier,rpc_argument_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_return_values;  /* send-icp-rpc-return-values */

/* SEND-ICP-RPC-RETURN-VALUES */
Object g2int_send_icp_rpc_return_values(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,163);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_return_values;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)237L));
	  g2int_write_icp_unsigned_integer(calling_procedure_index);
	  g2int_write_icp_rpc_argument_list(return_values_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_return_values,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_rpc_return_values,top,Nil);
		goto end_send_icp_rpc_return_values;
	    }
	}
	calling_procedure_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : calling_procedure_index;
	return_values_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : return_values_list;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_return_values;
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
		  g2int_start_writing_icp_message(FIX((SI_Long)237L)))) {
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
		  g2int_write_icp_unsigned_integer(calling_procedure_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_rpc_argument_list(return_values_list))) {
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
	      g2int_resumable_icp_push(return_values_list);
	      g2int_resumable_icp_push(calling_procedure_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_return_values);
	      result = VALUES_1(G2int_icp_suspend);
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

static Object Qg2int_rpc_return_values;  /* rpc-return-values */

/* HANDLE-ICP-RPC-RETURN-VALUES--BODY */
Object g2int_handle_icp_rpc_return_values__body(calling_procedure_index,
	    return_values_list)
    Object calling_procedure_index, return_values_list;
{
    Object item_among_arguments_qm, remote_procedure_identifier;
    Object rpc_arglist_structure, svref_new_value;

    x_note_fn_call(47,164);
    item_among_arguments_qm = 
	    g2int_get_item_from_arguments(return_values_list);
    remote_procedure_identifier = 
	    g2int_lookup_remote_procedure_identifier_from_index(calling_procedure_index);
    if (remote_procedure_identifier);
    else
	remote_procedure_identifier = g2int_gsi_connection_error(2,
		Qg2int_rpc_return_values,
		G2int_gsi_unknown_calling_procedure_index);
    if (item_among_arguments_qm) {
	rpc_arglist_structure = ISVREF(item_among_arguments_qm,(SI_Long)9L);
	SVREF(rpc_arglist_structure,FIX((SI_Long)2L)) = Qreturn;
	SVREF(rpc_arglist_structure,FIX((SI_Long)4L)) = 
		remote_procedure_identifier;
	SVREF(rpc_arglist_structure,FIX((SI_Long)5L)) = 
		calling_procedure_index;
	svref_new_value = G2int_gsi_reclaim_listqm;
	SVREF(rpc_arglist_structure,FIX((SI_Long)7L)) = svref_new_value;
	G2int_gsi_reclaim_listqm = Nil;
    }
    else {
	g2int_gsi_start_or_call_local_function_or_handle_return_values(Qreturn,
		ISVREF(ISVREF(remote_procedure_identifier,(SI_Long)3L),
		(SI_Long)2L),remote_procedure_identifier,return_values_list);
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_return_values;  /* handle-icp-rpc-return-values */

/* HANDLE-ICP-RPC-RETURN-VALUES */
Object g2int_handle_icp_rpc_return_values()
{
    Object calling_procedure_index, return_values_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,165);
    if (G2int_disable_resumability) {
	calling_procedure_index = g2int_read_icp_unsigned_integer();
	return_values_list = g2int_read_icp_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_return_values__body(calling_procedure_index,
		  return_values_list);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_return_values,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_rpc_return_values,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    calling_procedure_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_return_values);
		return VALUES_1(G2int_icp_suspend);
	    }
	    calling_procedure_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    return_values_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(calling_procedure_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_return_values);
		return VALUES_1(G2int_icp_suspend);
	    }
	    return_values_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_return_values__body(calling_procedure_index,
		  return_values_list);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_error;  /* send-icp-rpc-error */

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

/* SEND-ICP-RPC-ERROR */
Object g2int_send_icp_rpc_error(error_name,error_level,error_description,
	    error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,166);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_error;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)232L));
	  g2int_write_icp_corresponding_object_index(error_name);
	  g2int_write_icp_unsigned_integer(error_level);
	  g2int_write_icp_text_string(error_description);
	  g2int_write_icp_rpc_argument_list(error_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_error,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_rpc_error,top,Nil);
		goto end_send_icp_rpc_error;
	    }
	}
	error_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_error;
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
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      error_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)232L)))) {
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
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(error_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_unsigned_integer(error_level))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_text_string(error_description))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_rpc_argument_list(error_argument_list))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
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
	      g2int_resumable_icp_push(error_argument_list);
	      g2int_resumable_icp_push(error_description);
	      g2int_resumable_icp_push(error_level);
	      g2int_resumable_icp_push(error_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_error);
	      result = VALUES_1(G2int_icp_suspend);
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

static Object Qg2int_rpc_error_handler_1;  /* rpc_error_handler_1 */

/* HANDLE-ICP-RPC-ERROR--BODY */
Object g2int_handle_icp_rpc_error__body(error_name,error_level,
	    error_description,error_argument_list)
    Object error_name, error_level, error_description, error_argument_list;
{
    x_note_fn_call(47,167);
    g2int_gsi_warning(4,Qg2int_rpc_error_handler_1,
	    G2int_gsi_rpc_error_from_g2,error_level,error_description);
    g2int_reclaim_transformed_rpc_argument_list(error_argument_list,Nil);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_error;  /* handle-icp-rpc-error */

/* HANDLE-ICP-RPC-ERROR */
Object g2int_handle_icp_rpc_error()
{
    Object index_1, index_space, error_name, error_level, error_description;
    Object error_argument_list, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,168);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    error_name = Nil;
	error_level = g2int_read_icp_unsigned_integer();
	error_description = g2int_read_icp_text_string();
	error_argument_list = g2int_read_icp_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_error__body(error_name,error_level,
		  error_description,error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_error,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_rpc_error,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_name = g2int_resumable_icp_pop();
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
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error);
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
		error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		error_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_level = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_level = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_description = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_description = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_description);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_error__body(error_name,error_level,
		  error_description,error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_error_to_caller;  /* send-icp-rpc-error-to-caller */

/* SEND-ICP-RPC-ERROR-TO-CALLER */
Object g2int_send_icp_rpc_error_to_caller(remote_caller_index,signaller_qm,
	    error_name,error_level,error_description,error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(47,169);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_error_to_caller;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(error_name);
	  error_name = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)233L));
	  g2int_write_icp_unsigned_integer(remote_caller_index);
	  g2int_write_icp_unsigned_integer_or_nil(signaller_qm);
	  g2int_write_icp_corresponding_object_index(error_name);
	  g2int_write_icp_unsigned_integer(error_level);
	  g2int_write_icp_text_string(error_description);
	  g2int_write_icp_rpc_argument_list(error_argument_list);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_error_to_caller,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_send_icp_rpc_error_to_caller,top,Nil);
		goto end_send_icp_rpc_error_to_caller;
	    }
	}
	remote_caller_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_caller_index;
	signaller_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : signaller_qm;
	error_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_name;
	error_level = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_level;
	error_description = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_description;
	error_argument_list = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_argument_list;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_error_to_caller;
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
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(error_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      error_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(error_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      error_name = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)233L)))) {
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(remote_caller_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer_or_nil(signaller_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(error_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_unsigned_integer(error_level))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_text_string(error_description))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_rpc_argument_list(error_argument_list))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
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
	      g2int_resumable_icp_push(error_argument_list);
	      g2int_resumable_icp_push(error_description);
	      g2int_resumable_icp_push(error_level);
	      g2int_resumable_icp_push(error_name);
	      g2int_resumable_icp_push(signaller_qm);
	      g2int_resumable_icp_push(remote_caller_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_error_to_caller);
	      result = VALUES_1(G2int_icp_suspend);
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

static Object Qg2int_outstanding;  /* outstanding */

static Object Qg2int_sync_abort;   /* sync-abort */

static Object Qg2int_rpc_error_handler_2;  /* rpc_error_handler_2 */

/* HANDLE-ICP-RPC-ERROR-TO-CALLER--BODY */
Object g2int_handle_icp_rpc_error_to_caller__body(remote_caller_index,
	    signaller_qm,error_name,error_level,error_description,
	    error_argument_list)
    Object remote_caller_index, signaller_qm, error_name, error_level;
    Object error_description, error_argument_list;
{
    Object remote_procedure_identifier, gsi_remote_procedure;
    Object g2_procedure_name;

    x_note_fn_call(47,170);
    remote_procedure_identifier = (SI_Long)0L < IFIX(remote_caller_index) ?
	     
	    g2int_lookup_remote_procedure_identifier_from_index(remote_caller_index) 
	    : Nil;
    if (remote_procedure_identifier && EQ(Qg2int_outstanding,
	    ISVREF(remote_procedure_identifier,(SI_Long)6L)))
	SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = 
		Qg2int_sync_abort;
    gsi_remote_procedure = remote_procedure_identifier ? 
	    ISVREF(remote_procedure_identifier,(SI_Long)3L) : Nil;
    g2_procedure_name = ISVREF(gsi_remote_procedure,(SI_Long)1L);
    g2int_gsi_warning(5,Qg2int_rpc_error_handler_2,
	    G2int_gsi_rpc_error_from_g2_procedure,g2_procedure_name,
	    error_level,error_description);
    g2int_reclaim_transformed_rpc_argument_list(error_argument_list,Nil);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_error_to_caller;  /* handle-icp-rpc-error-to-caller */

/* HANDLE-ICP-RPC-ERROR-TO-CALLER */
Object g2int_handle_icp_rpc_error_to_caller()
{
    Object remote_caller_index, signaller_qm, index_1, index_space, error_name;
    Object error_level, error_description, error_argument_list;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(47,171);
    if (G2int_disable_resumability) {
	remote_caller_index = g2int_read_icp_unsigned_integer();
	signaller_qm = g2int_read_icp_unsigned_integer_or_nil();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    error_name = Nil;
	error_level = g2int_read_icp_unsigned_integer();
	error_description = g2int_read_icp_text_string();
	error_argument_list = g2int_read_icp_rpc_argument_list();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_error_to_caller__body(remote_caller_index,
		  signaller_qm,error_name,error_level,error_description,
		  error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_error_to_caller,top))
		return g2int_icp_error_internal(Qerror,string_constant_3,
			Qg2int_handle_icp_rpc_error_to_caller,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_caller_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_caller_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    signaller_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer_or_nil();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    signaller_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_name = g2int_resumable_icp_pop();
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
		    g2int_resumable_icp_push(signaller_qm);
		    g2int_resumable_icp_push(remote_caller_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
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
		error_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		error_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_level = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_level = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_description = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_description = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_argument_list = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_rpc_argument_list();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_description);
		g2int_resumable_icp_push(error_level);
		g2int_resumable_icp_push(error_name);
		g2int_resumable_icp_push(signaller_qm);
		g2int_resumable_icp_push(remote_caller_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_error_to_caller);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_argument_list = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_error_to_caller__body(remote_caller_index,
		  signaller_qm,error_name,error_level,error_description,
		  error_argument_list);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_description);
	temp = Nil;
    }
    return VALUES_1(temp);
}

void rpc_common2_INIT()
{
    Object temp, reclaim_structure_for_resumable_object_mixin;
    Object reclaim_structure_for_resumable_icp_object_mixin;
    Object reclaim_structure_for_resumable_node_mixin;
    Object reclaim_structure_for_resumable_icp_node_mixin;
    Object reclaim_structure_for_receiving_resumable_object;
    Object reclaim_structure_for_object_building_problem;
    Object reclaim_structure_for_receiving_rpc_arglist_structure;
    Object AB_package, list_constant_8, list_constant_7;
    Object Qg2int_abort_building_object_for_resumable_object_portion;
    Object Qg2int_finish_building_object_for_resumable_object_portion;
    Object Qg2int_suspend_building_object_for_resumable_object_portion;
    Object Qg2int_ascend_to_parent_for_resumable_object_portion;
    Object Qg2int_add_homogeneous_value_list_range_for_resumable_object_portion;
    Object Qg2int_add_value_list_range_for_resumable_object_portion;
    Object Qg2int_add_homogeneous_history_range_for_resumable_object_portion;
    Object Qg2int_add_history_range_for_resumable_object_portion;
    Object Qg2int_add_homogeneous_value_vector_range_for_resumable_object_portion;
    Object Qg2int_add_value_vector_range_for_resumable_object_portion;
    Object Qg2int_add_attribute_value_list_for_resumable_object_portion;
    Object Qg2int_add_attribute_object_list_for_resumable_object_portion;
    Object Qg2int_add_attribute_history_object_for_resumable_object_portion;
    Object Qg2int_add_attribute_value_vector_for_resumable_object_portion;
    Object Qg2int_add_attribute_object_vector_for_resumable_object_portion;
    Object Qg2int_add_resumable_circularity_for_resumable_object_portion;
    Object Qg2int_add_attribute_object_for_resumable_object_portion;
    Object Qg2int_add_circular_attribute_for_resumable_object_portion;
    Object Qg2int_add_attribute_value_for_resumable_object_portion;
    Object list_constant_6, Qg2int_attribute_value_tags;
    Object Qg2int_attribute_value_long_tag;
    Object Qg2int_attribute_value_evaluation_structure_tag;
    Object Qg2int_attribute_value_evaluation_sequence_tag;
    Object Qg2int_attribute_value_null_tag, Qg2int_circular_reference_tag;
    Object Qg2int_unknown_value_vector_element_type_tag;
    Object Qg2int_attribute_value_truth_value_tag;
    Object Qg2int_attribute_value_text_tag, Qg2int_attribute_value_symbol_tag;
    Object Qg2int_attribute_value_float_tag;
    Object Qg2int_attribute_value_integer_tag, Qg2int_current_value;
    Object Qg2int_name, list_constant_5, Qg2int_attribute_specqm_tags;
    Object Qg2int_qualified_system_attribute_tag;
    Object Qg2int_unqualified_system_attribute_tag;
    Object Qg2int_qualified_symbolic_attribute_tag;
    Object Qg2int_unqualified_symbolic_attribute_tag;
    Object Qg2int_list_element_attribute_spec_tag;
    Object Qg2int_vector_element_attribute_spec_tag;
    Object Qg2int_nameless_attribute_spec_tag, list_constant_4;
    Object Qg2int_possibly_interned_symbol_tags;
    Object Qg2int_possibly_interned_symbol_uninterned_overflow_tag;
    Object Qg2int_possibly_interned_symbol_uninterned_tag;
    Object Qg2int_possibly_interned_symbol_interned_tag;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2int_receiving_rpc_arglist_structure, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_receiving_rpc_arglist_structure_count;
    Object Qg2int_chain_of_available_receiving_rpc_arglist_structures;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_10, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object Qg2int_reclaim_icp_port_entry_for_resumable_instance_node;
    Object Qg2int_resumable_instance_node, list_constant_3;
    Object Qg2int_icp_object_map_for_resumable_instance_node;
    Object Qg2int_reclaim_icp_port_entry_for_resumable_object;
    Object Qg2int_reclaim_resumable_object, Qg2int_resumable_object;
    Object list_constant_2, Qg2int_icp_object_map_for_resumable_object;
    Object Qg2int_object_building_problem;
    Object Qg2int_object_building_problem_count;
    Object Qg2int_chain_of_available_object_building_problems;
    Object string_constant_9, Qg2int_receiving_resumable_object;
    Object Qg2int_receiving_resumable_object_count;
    Object Qg2int_chain_of_available_receiving_resumable_objects;
    Object string_constant_8, Qg2int_resumable_icp_node_mixin;
    Object Qg2int_resumable_icp_node_mixin_count;
    Object Qg2int_chain_of_available_resumable_icp_node_mixins;
    Object string_constant_7, Qg2int_resumable_node_mixin;
    Object Qg2int_resumable_node_mixin_count;
    Object Qg2int_chain_of_available_resumable_node_mixins, string_constant_6;
    Object Qg2int_resumable_icp_object_mixin;
    Object Qg2int_resumable_icp_object_mixin_count;
    Object Qg2int_chain_of_available_resumable_icp_object_mixins;
    Object string_constant_5, Qg2int_resumable_object_mixin;
    Object Qg2int_resumable_object_mixin_count;
    Object Qg2int_chain_of_available_resumable_object_mixins;
    Object string_constant_4;

    x_note_fn_call(47,172);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_class_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_resumable_object_mixin = STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN",
	    AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    Qg2int_resumable_object_mixin,
	    Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_resumable_object_mixin,
	    Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_resumable_object_mixin == UNBOUND)
	G2int_the_type_description_of_resumable_object_mixin = Nil;
    string_constant_4 = STATIC_STRING("43Dy8l83Iy1n83Iy8m8k1l8m0000000krk0k0");
    temp = G2int_the_type_description_of_resumable_object_mixin;
    G2int_the_type_description_of_resumable_object_mixin = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_4));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_object_mixin_g2_struct,
	    G2int_the_type_description_of_resumable_object_mixin,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_resumable_object_mixin,
	    G2int_the_type_description_of_resumable_object_mixin,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_resumable_object_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-OBJECT-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_resumable_object_mixins,
	    G2int_chain_of_available_resumable_object_mixins);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_resumable_object_mixins,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_resumable_object_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-OBJECT-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_resumable_object_mixin_count,
	    G2int_resumable_object_mixin_count);
    g2int_record_system_variable(Qg2int_resumable_object_mixin_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_resumable_object_mixin = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_resumable_object_mixin,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_resumable_object_mixin,
	    reclaim_structure_for_resumable_object_mixin);
    Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_resumable_icp_object_mixin = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    Qg2int_resumable_icp_object_mixin,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_resumable_icp_object_mixin,
	    Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_resumable_icp_object_mixin == UNBOUND)
	G2int_the_type_description_of_resumable_icp_object_mixin = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8l830gy1o830gy83Iy8m8k1l83Iy0000001l1m8o83Iyksk0k0");
    temp = G2int_the_type_description_of_resumable_icp_object_mixin;
    G2int_the_type_description_of_resumable_icp_object_mixin = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_object_mixin_g2_struct,
	    G2int_the_type_description_of_resumable_icp_object_mixin,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_resumable_icp_object_mixin,
	    G2int_the_type_description_of_resumable_icp_object_mixin,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_resumable_icp_object_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-ICP-OBJECT-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_resumable_icp_object_mixins,
	    G2int_chain_of_available_resumable_icp_object_mixins);
    g2int_record_system_variable(Qg2int_chain_of_available_resumable_icp_object_mixins,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_resumable_icp_object_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-ICP-OBJECT-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_resumable_icp_object_mixin_count,
	    G2int_resumable_icp_object_mixin_count);
    g2int_record_system_variable(Qg2int_resumable_icp_object_mixin_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_resumable_icp_object_mixin = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_resumable_icp_object_mixin,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_resumable_icp_object_mixin,
	    reclaim_structure_for_resumable_icp_object_mixin);
    Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_resumable_node_mixin = STATIC_SYMBOL("RESUMABLE-NODE-MIXIN",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    Qg2int_resumable_node_mixin,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_resumable_node_mixin,
	    Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_resumable_node_mixin == UNBOUND)
	G2int_the_type_description_of_resumable_node_mixin = Nil;
    string_constant_6 = STATIC_STRING("43Dy8l83Oy1n83Oy8m8k1l8m0000000knk0k0");
    temp = G2int_the_type_description_of_resumable_node_mixin;
    G2int_the_type_description_of_resumable_node_mixin = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_6));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_node_mixin_g2_struct,
	    G2int_the_type_description_of_resumable_node_mixin,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_resumable_node_mixin,
	    G2int_the_type_description_of_resumable_node_mixin,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_resumable_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_resumable_node_mixins,
	    G2int_chain_of_available_resumable_node_mixins);
    g2int_record_system_variable(Qg2int_chain_of_available_resumable_node_mixins,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_resumable_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_resumable_node_mixin_count,
	    G2int_resumable_node_mixin_count);
    g2int_record_system_variable(Qg2int_resumable_node_mixin_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_resumable_node_mixin = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_resumable_node_mixin,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_resumable_node_mixin,
	    reclaim_structure_for_resumable_node_mixin);
    Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_resumable_icp_node_mixin = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    Qg2int_resumable_icp_node_mixin,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_resumable_icp_node_mixin,
	    Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_resumable_icp_node_mixin == UNBOUND)
	G2int_the_type_description_of_resumable_icp_node_mixin = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8l830fy1o830fy83Oy8m8k1l83Oy0000001l1m8o83Oykok0k0");
    temp = G2int_the_type_description_of_resumable_icp_node_mixin;
    G2int_the_type_description_of_resumable_icp_node_mixin = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_7));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_resumable_icp_node_mixin_g2_struct,
	    G2int_the_type_description_of_resumable_icp_node_mixin,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_resumable_icp_node_mixin,
	    G2int_the_type_description_of_resumable_icp_node_mixin,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_resumable_icp_node_mixins = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RESUMABLE-ICP-NODE-MIXINS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_resumable_icp_node_mixins,
	    G2int_chain_of_available_resumable_icp_node_mixins);
    g2int_record_system_variable(Qg2int_chain_of_available_resumable_icp_node_mixins,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_resumable_icp_node_mixin_count = 
	    STATIC_SYMBOL("RESUMABLE-ICP-NODE-MIXIN-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_resumable_icp_node_mixin_count,
	    G2int_resumable_icp_node_mixin_count);
    g2int_record_system_variable(Qg2int_resumable_icp_node_mixin_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_resumable_icp_node_mixin = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_resumable_icp_node_mixin,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_resumable_icp_node_mixin,
	    reclaim_structure_for_resumable_icp_node_mixin);
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_receiving_resumable_object = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    Qg2int_receiving_resumable_object,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_receiving_resumable_object,
	    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_receiving_resumable_object == UNBOUND)
	G2int_the_type_description_of_receiving_resumable_object = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8l8305y1o8305y83Iy8m8k1l83Iy0000001n1m8o83Iy1n8n83=Cy01m8p830Mykzk0k0");
    temp = G2int_the_type_description_of_receiving_resumable_object;
    G2int_the_type_description_of_receiving_resumable_object = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_8));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct,
	    G2int_the_type_description_of_receiving_resumable_object,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_receiving_resumable_object,
	    G2int_the_type_description_of_receiving_resumable_object,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_receiving_resumable_objects = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RECEIVING-RESUMABLE-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_receiving_resumable_objects,
	    G2int_chain_of_available_receiving_resumable_objects);
    g2int_record_system_variable(Qg2int_chain_of_available_receiving_resumable_objects,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_receiving_resumable_object_count = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_receiving_resumable_object_count,
	    G2int_receiving_resumable_object_count);
    g2int_record_system_variable(Qg2int_receiving_resumable_object_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_receiving_resumable_object = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_receiving_resumable_object,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_receiving_resumable_object,
	    reclaim_structure_for_receiving_resumable_object);
    Qg2_defstruct_structure_name_object_building_problem_g2_struct = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_object_building_problem = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    Qg2int_object_building_problem,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_object_building_problem,
	    Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_object_building_problem == UNBOUND)
	G2int_the_type_description_of_object_building_problem = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8l83=ay1n83=ay8m8k1l8m0000001l1n8n83=7y1q83=gy83=by83=cy83=ey83=fy83=dykrk0k0");
    temp = G2int_the_type_description_of_object_building_problem;
    G2int_the_type_description_of_object_building_problem = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_9));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_object_building_problem_g2_struct,
	    G2int_the_type_description_of_object_building_problem,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_object_building_problem,
	    G2int_the_type_description_of_object_building_problem,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_object_building_problems = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-OBJECT-BUILDING-PROBLEMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_object_building_problems,
	    G2int_chain_of_available_object_building_problems);
    g2int_record_system_variable(Qg2int_chain_of_available_object_building_problems,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_object_building_problem_count = 
	    STATIC_SYMBOL("OBJECT-BUILDING-PROBLEM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_object_building_problem_count,
	    G2int_object_building_problem_count);
    g2int_record_system_variable(Qg2int_object_building_problem_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_object_building_problem = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_object_building_problem,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_object_building_problem,
	    reclaim_structure_for_object_building_problem);
    string_constant = STATIC_STRING("~(~A::~A~)");
    string_constant_1 = STATIC_STRING("~(~A~)");
    string_constant_2 = STATIC_STRING("top-level");
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_input = STATIC_SYMBOL("INPUT",AB_package);
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_set_access_form_for_resumable_object = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-RESUMABLE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_resumable_object,
	    STATIC_FUNCTION(g2int_set_access_form_for_resumable_object,NIL,
	    FALSE,2,2));
    Qg2int_resumable_object = STATIC_SYMBOL("RESUMABLE-OBJECT",AB_package);
    Qg2int_icp_object_map_for_resumable_object = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-RESUMABLE-OBJECT",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_resumable_object,
	    Qg2int_resumable_object);
    g2int_initialize_icp_object_type_compile(Qg2int_resumable_object,
	    Qg2int_standard_icp_object_index_space,list_constant_2);
    Qg2int_reclaim_resumable_object = 
	    STATIC_SYMBOL("RECLAIM-RESUMABLE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_resumable_object,
	    STATIC_FUNCTION(g2int_reclaim_resumable_object,NIL,FALSE,2,2));
    Qg2int_reclaim_icp_port_entry_for_resumable_object = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_resumable_object,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_resumable_object,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_resumable_object,
	    Qg2int_reclaim_resumable_object,Qnil,
	    Qg2int_reclaim_icp_port_entry_for_resumable_object);
    Qg2int_set_access_form_for_resumable_instance_node = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_resumable_instance_node,
	    STATIC_FUNCTION(g2int_set_access_form_for_resumable_instance_node,
	    NIL,FALSE,2,2));
    Qg2int_resumable_instance_node = 
	    STATIC_SYMBOL("RESUMABLE-INSTANCE-NODE",AB_package);
    Qg2int_icp_object_map_for_resumable_instance_node = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_resumable_instance_node,
	    Qg2int_resumable_instance_node);
    g2int_initialize_icp_object_type_compile(Qg2int_resumable_instance_node,
	    Qg2int_standard_icp_object_index_space,list_constant_3);
    Qg2int_reclaim_icp_port_entry_for_resumable_instance_node = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-RESUMABLE-INSTANCE-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_resumable_instance_node,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_resumable_instance_node,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_resumable_instance_node,Qnil,
	    Qnil,Qg2int_reclaim_icp_port_entry_for_resumable_instance_node);
    Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct 
	    = STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_receiving_rpc_arglist_structure = 
	    STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    Qg2int_receiving_rpc_arglist_structure,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_receiving_rpc_arglist_structure,
	    Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_receiving_rpc_arglist_structure == 
	    UNBOUND)
	G2int_the_type_description_of_receiving_rpc_arglist_structure = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8l8306y1n8306y8m8k1l8m0000000ktk0k0");
    temp = G2int_the_type_description_of_receiving_rpc_arglist_structure;
    G2int_the_type_description_of_receiving_rpc_arglist_structure = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_10));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_receiving_rpc_arglist_structure_g2_struct,
	    G2int_the_type_description_of_receiving_rpc_arglist_structure,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_receiving_rpc_arglist_structure,
	    G2int_the_type_description_of_receiving_rpc_arglist_structure,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_receiving_rpc_arglist_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RECEIVING-RPC-ARGLIST-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_receiving_rpc_arglist_structures,
	    G2int_chain_of_available_receiving_rpc_arglist_structures);
    g2int_record_system_variable(Qg2int_chain_of_available_receiving_rpc_arglist_structures,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_receiving_rpc_arglist_structure_count = 
	    STATIC_SYMBOL("RECEIVING-RPC-ARGLIST-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_receiving_rpc_arglist_structure_count,
	    G2int_receiving_rpc_arglist_structure_count);
    g2int_record_system_variable(Qg2int_receiving_rpc_arglist_structure_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_receiving_rpc_arglist_structure = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_receiving_rpc_arglist_structure,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_receiving_rpc_arglist_structure,
	    reclaim_structure_for_receiving_rpc_arglist_structure);
    Qg2int_gsi_reference_flag = STATIC_SYMBOL("GSI-REFERENCE-FLAG",AB_package);
    list_constant = STATIC_LIST((SI_Long)18L,FIX((SI_Long)17L),
	    FIX((SI_Long)19L),FIX((SI_Long)20L),FIX((SI_Long)21L),
	    FIX((SI_Long)22L),FIX((SI_Long)25L),FIX((SI_Long)26L),
	    FIX((SI_Long)23L),FIX((SI_Long)24L),FIX((SI_Long)33L),
	    FIX((SI_Long)35L),FIX((SI_Long)36L),FIX((SI_Long)37L),
	    FIX((SI_Long)38L),FIX((SI_Long)41L),FIX((SI_Long)42L),
	    FIX((SI_Long)39L),FIX((SI_Long)40L));
    Qg2int_integer_array = STATIC_SYMBOL("INTEGER-ARRAY",AB_package);
    Qg2int_symbol_array = STATIC_SYMBOL("SYMBOL-ARRAY",AB_package);
    Qg2int_text_array = STATIC_SYMBOL("TEXT-ARRAY",AB_package);
    Qg2int_truth_value_array = STATIC_SYMBOL("TRUTH-VALUE-ARRAY",AB_package);
    Qg2int_float_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qg2int_g2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qg2int_quantity_array = STATIC_SYMBOL("QUANTITY-ARRAY",AB_package);
    Qg2int_item_array = STATIC_SYMBOL("ITEM-ARRAY",AB_package);
    Qg2int_value_array = STATIC_SYMBOL("VALUE-ARRAY",AB_package);
    Qg2int_integer_list = STATIC_SYMBOL("INTEGER-LIST",AB_package);
    Qg2int_symbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    Qg2int_text_list = STATIC_SYMBOL("TEXT-LIST",AB_package);
    Qg2int_truth_value_list = STATIC_SYMBOL("TRUTH-VALUE-LIST",AB_package);
    Qg2int_float_list = STATIC_SYMBOL("FLOAT-LIST",AB_package);
    Qg2int_g2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qg2int_quantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    Qg2int_item_list = STATIC_SYMBOL("ITEM-LIST",AB_package);
    Qg2int_value_list = STATIC_SYMBOL("VALUE-LIST",AB_package);
    Qg2_defstruct_structure_name_gsi_instance_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_write_rpc_argument = STATIC_SYMBOL("WRITE_RPC_ARGUMENT",AB_package);
    Qg2int_gsi_instance_squirrelled_index = 
	    STATIC_SYMBOL("GSI-INSTANCE-SQUIRRELLED-INDEX",AB_package);
    if (G2int_rpc_throw_tag == UNBOUND)
	G2int_rpc_throw_tag = Nil;
    Qg2int_possibly_interned_symbol_interned_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-INTERNED-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_possibly_interned_symbol_interned_tag,
	    FIX((SI_Long)0L));
    Qg2int_possibly_interned_symbol_uninterned_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-UNINTERNED-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_possibly_interned_symbol_uninterned_tag,
	    FIX((SI_Long)1L));
    Qg2int_possibly_interned_symbol_uninterned_overflow_tag = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-UNINTERNED-OVERFLOW-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_possibly_interned_symbol_uninterned_overflow_tag,
	    FIX((SI_Long)2L));
    Qg2int_possibly_interned_symbol_tags = 
	    STATIC_SYMBOL("POSSIBLY-INTERNED-SYMBOL-TAGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_possibly_interned_symbol_tags,
	    G2int_possibly_interned_symbol_tags);
    list_constant_4 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)0L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L));
    SET_SYMBOL_VALUE(Qg2int_possibly_interned_symbol_tags,list_constant_4);
    Qg2int_nameless_attribute_spec_tag = 
	    STATIC_SYMBOL("NAMELESS-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_nameless_attribute_spec_tag,FIX((SI_Long)2L));
    Qg2int_vector_element_attribute_spec_tag = 
	    STATIC_SYMBOL("VECTOR-ELEMENT-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_vector_element_attribute_spec_tag,
	    FIX((SI_Long)3L));
    Qg2int_list_element_attribute_spec_tag = 
	    STATIC_SYMBOL("LIST-ELEMENT-ATTRIBUTE-SPEC-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_list_element_attribute_spec_tag,FIX((SI_Long)4L));
    Qg2int_unqualified_symbolic_attribute_tag = 
	    STATIC_SYMBOL("UNQUALIFIED-SYMBOLIC-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unqualified_symbolic_attribute_tag,
	    FIX((SI_Long)12L));
    Qg2int_qualified_symbolic_attribute_tag = 
	    STATIC_SYMBOL("QUALIFIED-SYMBOLIC-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_qualified_symbolic_attribute_tag,
	    FIX((SI_Long)13L));
    Qg2int_unqualified_system_attribute_tag = 
	    STATIC_SYMBOL("UNQUALIFIED-SYSTEM-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unqualified_system_attribute_tag,
	    FIX((SI_Long)14L));
    Qg2int_qualified_system_attribute_tag = 
	    STATIC_SYMBOL("QUALIFIED-SYSTEM-ATTRIBUTE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_qualified_system_attribute_tag,FIX((SI_Long)15L));
    Qg2int_attribute_specqm_tags = STATIC_SYMBOL("ATTRIBUTE-SPEC\?-TAGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_attribute_specqm_tags,
	    G2int_attribute_specqm_tags);
    list_constant_5 = STATIC_LIST((SI_Long)7L,FIX((SI_Long)2L),
	    FIX((SI_Long)3L),FIX((SI_Long)4L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)14L),FIX((SI_Long)15L));
    SET_SYMBOL_VALUE(Qg2int_attribute_specqm_tags,list_constant_5);
    Qg2int_vector_element = STATIC_SYMBOL("VECTOR-ELEMENT",AB_package);
    Qg2int_attribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qg2int_name = STATIC_SYMBOL("NAME",AB_package);
    Qg2int_current_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qg2int_name,
	    Qg2int_current_value);
    Qg2int_list_element = STATIC_SYMBOL("LIST-ELEMENT",AB_package);
    Qg2int_write_icp_list_of_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-ATTRIBUTES",AB_package);
    string_constant_3 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_attributes,NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-ATTRIBUTES",AB_package);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_attributes,NIL,FALSE,0,0));
    Qg2int_read_icp_list_of_boolean = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-BOOLEAN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_boolean,
	    STATIC_FUNCTION(g2int_read_icp_list_of_boolean,NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_boolean = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-BOOLEAN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_boolean,
	    STATIC_FUNCTION(g2int_write_icp_list_of_boolean,NIL,FALSE,1,1));
    Qg2int_write_icp_list_of_lists_of_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-LISTS-OF-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_lists_of_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_lists_of_attributes,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_lists_of_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-LISTS-OF-ATTRIBUTES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_lists_of_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_lists_of_attributes,NIL,
	    FALSE,0,0));
    Qg2int_write_icp_list_of_included_return_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_included_return_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_included_return_attributes,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_included_return_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_included_return_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_included_return_attributes,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_excluded_return_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_excluded_return_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_excluded_return_attributes,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_excluded_return_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-EXCLUDED-RETURN-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_excluded_return_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_excluded_return_attributes,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_included_return_system_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_included_return_system_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_included_return_system_attributes,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_included_return_system_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDED-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_included_return_system_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_included_return_system_attributes,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_include_all_return_system_attributes,
	    STATIC_FUNCTION(g2int_write_icp_list_of_include_all_return_system_attributes,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_include_all_return_system_attributes = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_include_all_return_system_attributes,
	    STATIC_FUNCTION(g2int_read_icp_list_of_include_all_return_system_attributes,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_include_all_return_system_attributes_except,
	    STATIC_FUNCTION(g2int_write_icp_list_of_include_all_return_system_attributes_except,
	    NIL,FALSE,1,1));
    Qg2int_read_icp_list_of_include_all_return_system_attributes_except = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-INCLUDE-ALL-RETURN-SYSTEM-ATTRIBUTES-EXCEPT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_include_all_return_system_attributes_except,
	    STATIC_FUNCTION(g2int_read_icp_list_of_include_all_return_system_attributes_except,
	    NIL,FALSE,0,0));
    Qg2int_write_icp_list_of_return_kinds = 
	    STATIC_SYMBOL("WRITE-ICP-LIST-OF-RETURN-KINDS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_list_of_return_kinds,
	    STATIC_FUNCTION(g2int_write_icp_list_of_return_kinds,NIL,FALSE,
	    1,1));
    Qg2int_read_icp_list_of_return_kinds = 
	    STATIC_SYMBOL("READ-ICP-LIST-OF-RETURN-KINDS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_list_of_return_kinds,
	    STATIC_FUNCTION(g2int_read_icp_list_of_return_kinds,NIL,FALSE,
	    0,0));
    Qg2int_write_icp_remote_procedure_varargs_p = 
	    STATIC_SYMBOL("WRITE-ICP-REMOTE-PROCEDURE-VARARGS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_remote_procedure_varargs_p,
	    STATIC_FUNCTION(g2int_write_icp_remote_procedure_varargs_p,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_remote_procedure_varargs_p = 
	    STATIC_SYMBOL("READ-ICP-REMOTE-PROCEDURE-VARARGS-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_remote_procedure_varargs_p,
	    STATIC_FUNCTION(g2int_read_icp_remote_procedure_varargs_p,NIL,
	    FALSE,0,0));
    Qg2int_attribute_value_integer_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-INTEGER-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_integer_tag,FIX((SI_Long)5L));
    Qg2int_attribute_value_float_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-FLOAT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_float_tag,FIX((SI_Long)6L));
    Qg2int_attribute_value_symbol_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-SYMBOL-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_symbol_tag,FIX((SI_Long)7L));
    Qg2int_attribute_value_text_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-TEXT-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_text_tag,FIX((SI_Long)8L));
    Qg2int_attribute_value_truth_value_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-TRUTH-VALUE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_truth_value_tag,FIX((SI_Long)9L));
    Qg2int_unknown_value_vector_element_type_tag = 
	    STATIC_SYMBOL("UNKNOWN-VALUE-VECTOR-ELEMENT-TYPE-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_unknown_value_vector_element_type_tag,
	    FIX((SI_Long)11L));
    Qg2int_circular_reference_tag = STATIC_SYMBOL("CIRCULAR-REFERENCE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_circular_reference_tag,FIX((SI_Long)12L));
    Qg2int_attribute_value_null_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-NULL-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_null_tag,FIX((SI_Long)13L));
    Qg2int_attribute_value_evaluation_sequence_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-EVALUATION-SEQUENCE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_evaluation_sequence_tag,
	    FIX((SI_Long)14L));
    Qg2int_attribute_value_evaluation_structure_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-EVALUATION-STRUCTURE-TAG",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_evaluation_structure_tag,
	    FIX((SI_Long)15L));
    Qg2int_attribute_value_long_tag = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-LONG-TAG",AB_package);
    SET_SYMBOL_VALUE(Qg2int_attribute_value_long_tag,FIX((SI_Long)16L));
    Qg2int_attribute_value_tags = STATIC_SYMBOL("ATTRIBUTE-VALUE-TAGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_attribute_value_tags,
	    G2int_attribute_value_tags);
    list_constant_6 = STATIC_LIST((SI_Long)11L,FIX((SI_Long)5L),
	    FIX((SI_Long)6L),FIX((SI_Long)7L),FIX((SI_Long)8L),
	    FIX((SI_Long)9L),FIX((SI_Long)11L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),FIX((SI_Long)14L),FIX((SI_Long)15L),
	    FIX((SI_Long)16L));
    SET_SYMBOL_VALUE(Qg2int_attribute_value_tags,list_constant_6);
    Qg2int_write_attribute_value = STATIC_SYMBOL("WRITE_ATTRIBUTE_VALUE",
	    AB_package);
    Qg2int_add_attribute_value_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_value_for_resumable_object_portion,
	    FIX((SI_Long)1L));
    Qg2int_add_circular_attribute_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-CIRCULAR-ATTRIBUTE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_circular_attribute_for_resumable_object_portion,
	    FIX((SI_Long)2L));
    Qg2int_add_attribute_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_object_for_resumable_object_portion,
	    FIX((SI_Long)3L));
    Qg2int_add_resumable_circularity_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-RESUMABLE-CIRCULARITY-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_resumable_circularity_for_resumable_object_portion,
	    FIX((SI_Long)16L));
    Qg2int_add_attribute_object_vector_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-VECTOR-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_object_vector_for_resumable_object_portion,
	    FIX((SI_Long)4L));
    Qg2int_long = STATIC_SYMBOL("LONG",AB_package);
    Qg2int_float = STATIC_SYMBOL("float",AB_package);
    Qg2int_text = STATIC_SYMBOL("TEXT",AB_package);
    Qg2int_truth = STATIC_SYMBOL("TRUTH",AB_package);
    Qg2int_add_attribute_value_vector_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-VECTOR-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_value_vector_for_resumable_object_portion,
	    FIX((SI_Long)5L));
    Qg2int_add_attribute_history_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-HISTORY-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_history_object_for_resumable_object_portion,
	    FIX((SI_Long)17L));
    Qg2int_add_attribute_object_list_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-OBJECT-LIST-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_object_list_for_resumable_object_portion,
	    FIX((SI_Long)6L));
    Qg2int_add_attribute_value_list_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-ATTRIBUTE-VALUE-LIST-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_attribute_value_list_for_resumable_object_portion,
	    FIX((SI_Long)7L));
    Qg2int_add_value_vector_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-VALUE-VECTOR-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_value_vector_range_for_resumable_object_portion,
	    FIX((SI_Long)8L));
    Qg2int_add_homogeneous_value_vector_range_for_resumable_object_portion 
	    = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-VALUE-VECTOR-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_homogeneous_value_vector_range_for_resumable_object_portion,
	    FIX((SI_Long)14L));
    Qg2int_add_history_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HISTORY-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_history_range_for_resumable_object_portion,
	    FIX((SI_Long)18L));
    Qg2int_add_homogeneous_history_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-HISTORY-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_homogeneous_history_range_for_resumable_object_portion,
	    FIX((SI_Long)19L));
    Qg2int_add_value_list_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-VALUE-LIST-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_value_list_range_for_resumable_object_portion,
	    FIX((SI_Long)9L));
    Qg2int_add_homogeneous_value_list_range_for_resumable_object_portion = 
	    STATIC_SYMBOL("ADD-HOMOGENEOUS-VALUE-LIST-RANGE-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_add_homogeneous_value_list_range_for_resumable_object_portion,
	    FIX((SI_Long)15L));
    Qg2int_ascend_to_parent_for_resumable_object_portion = 
	    STATIC_SYMBOL("ASCEND-TO-PARENT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_ascend_to_parent_for_resumable_object_portion,
	    FIX((SI_Long)10L));
    Qg2int_gsi_superior_item = STATIC_SYMBOL("GSI-SUPERIOR-ITEM",AB_package);
    Qg2int_suspend_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("SUSPEND-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_suspend_building_object_for_resumable_object_portion,
	    FIX((SI_Long)11L));
    Qg2int_exit_from_resumable_object_portion = 
	    STATIC_SYMBOL("EXIT-FROM-RESUMABLE-OBJECT-PORTION",AB_package);
    Qg2int_finish_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("FINISH-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_finish_building_object_for_resumable_object_portion,
	    FIX((SI_Long)12L));
    Qg2int_abort_building_object_for_resumable_object_portion = 
	    STATIC_SYMBOL("ABORT-BUILDING-OBJECT-FOR-RESUMABLE-OBJECT-PORTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_abort_building_object_for_resumable_object_portion,
	    FIX((SI_Long)13L));
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_frame_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",
	    AB_package);
    Qg2int_send_icp_update_object_passing_network_resources = 
	    STATIC_SYMBOL("SEND-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_update_object_passing_network_resources,
	    STATIC_FUNCTION(g2int_send_icp_update_object_passing_network_resources,
	    NIL,FALSE,3,3));
    Qg2int_handle_icp_update_object_passing_network_resources = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-OBJECT-PASSING-NETWORK-RESOURCES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_update_object_passing_network_resources,
	    STATIC_FUNCTION(g2int_handle_icp_update_object_passing_network_resources,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_update_object_passing_network_resources,
	    FIX((SI_Long)321L));
    Qg2int_toplevel_object_has_been_deleted_on_receiving_side = 
	    STATIC_SYMBOL("TOPLEVEL-OBJECT-HAS-BEEN-DELETED-ON-RECEIVING-SIDE",
	    AB_package);
    Qg2int_rpc_arg_list = STATIC_SYMBOL("RPC-ARG-LIST",AB_package);
    Qg2int_send_icp_continue_building_resumable_object = 
	    STATIC_SYMBOL("SEND-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_continue_building_resumable_object,
	    STATIC_FUNCTION(g2int_send_icp_continue_building_resumable_object,
	    NIL,FALSE,1,1));
    Qg2int_handle_icp_continue_building_resumable_object = 
	    STATIC_SYMBOL("HANDLE-ICP-CONTINUE-BUILDING-RESUMABLE-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_continue_building_resumable_object,
	    STATIC_FUNCTION(g2int_handle_icp_continue_building_resumable_object,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_continue_building_resumable_object,
	    FIX((SI_Long)320L));
    list_constant_7 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_8 = STATIC_CONS(Qunsigned_byte,list_constant_7);
    array_constant = STATIC_ARRAY(list_constant_8,(SI_Long)1L,
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
    Qg2int_send_icp_rpc_start = STATIC_SYMBOL("SEND-ICP-RPC-START",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_start,
	    STATIC_FUNCTION(g2int_send_icp_rpc_start,NIL,FALSE,2,2));
    Qg2int_start = STATIC_SYMBOL("START",AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_handle_icp_rpc_start = STATIC_SYMBOL("HANDLE-ICP-RPC-START",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_start,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_start,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_start,
	    FIX((SI_Long)230L));
    Qg2int_send_icp_rpc_call = STATIC_SYMBOL("SEND-ICP-RPC-CALL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_call,
	    STATIC_FUNCTION(g2int_send_icp_rpc_call,NIL,FALSE,3,3));
    Qg2int_call = STATIC_SYMBOL("CALL",AB_package);
    Qg2int_handle_icp_rpc_call = STATIC_SYMBOL("HANDLE-ICP-RPC-CALL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_call,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_call,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_call,
	    FIX((SI_Long)231L));
    Qg2int_send_icp_rpc_return_values = 
	    STATIC_SYMBOL("SEND-ICP-RPC-RETURN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_return_values,
	    STATIC_FUNCTION(g2int_send_icp_rpc_return_values,NIL,FALSE,2,2));
    Qg2int_rpc_return_values = STATIC_SYMBOL("RPC-RETURN-VALUES",AB_package);
    Qg2int_handle_icp_rpc_return_values = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-RETURN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_return_values,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_return_values,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_return_values,
	    FIX((SI_Long)237L));
    Qg2int_send_icp_rpc_error = STATIC_SYMBOL("SEND-ICP-RPC-ERROR",AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_error,
	    STATIC_FUNCTION(g2int_send_icp_rpc_error,NIL,FALSE,4,4));
    Qg2int_rpc_error_handler_1 = STATIC_SYMBOL("RPC_ERROR_HANDLER_1",
	    AB_package);
    Qg2int_handle_icp_rpc_error = STATIC_SYMBOL("HANDLE-ICP-RPC-ERROR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_error,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_error,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_error,
	    FIX((SI_Long)232L));
    Qg2int_send_icp_rpc_error_to_caller = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ERROR-TO-CALLER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_error_to_caller,
	    STATIC_FUNCTION(g2int_send_icp_rpc_error_to_caller,NIL,FALSE,6,6));
    Qg2int_outstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qg2int_sync_abort = STATIC_SYMBOL("SYNC-ABORT",AB_package);
    Qg2int_rpc_error_handler_2 = STATIC_SYMBOL("RPC_ERROR_HANDLER_2",
	    AB_package);
    Qg2int_handle_icp_rpc_error_to_caller = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ERROR-TO-CALLER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_error_to_caller,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_error_to_caller,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_error_to_caller,
	    FIX((SI_Long)233L));
}
