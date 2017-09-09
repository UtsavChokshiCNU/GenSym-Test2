/* rsrcs.c
 * Input file:  resources.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rsrcs.h"


Object The_type_description_of_compiled_resource = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_compiled_resources, Qchain_of_available_compiled_resources);

DEFINE_VARIABLE_WITH_SYMBOL(Compiled_resource_count, Qcompiled_resource_count);

Object Chain_of_available_compiled_resources_vector = UNBOUND;

/* COMPILED-RESOURCE-STRUCTURE-MEMORY-USAGE */
Object compiled_resource_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(246,0);
    temp = Compiled_resource_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-COMPILED-RESOURCE-COUNT */
Object outstanding_compiled_resource_count()
{
    Object def_structure_compiled_resource_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(246,1);
    gensymed_symbol = IFIX(Compiled_resource_count);
    def_structure_compiled_resource_variable = 
	    Chain_of_available_compiled_resources;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_compiled_resource_variable))
	goto end_loop;
    def_structure_compiled_resource_variable = 
	    ISVREF(def_structure_compiled_resource_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-COMPILED-RESOURCE-1 */
Object reclaim_compiled_resource_1(compiled_resource)
    Object compiled_resource;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(246,2);
    inline_note_reclaim_cons(compiled_resource,Nil);
    structure_being_reclaimed = compiled_resource;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_compiled_resource_slot(ISVREF(compiled_resource,(SI_Long)6L));
      SVREF(compiled_resource,FIX((SI_Long)6L)) = Nil;
      reclaim_compiled_resource_slot(ISVREF(compiled_resource,(SI_Long)7L));
      SVREF(compiled_resource,FIX((SI_Long)7L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_compiled_resources_vector,
	    IFIX(Current_thread_index));
    SVREF(compiled_resource,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_compiled_resources_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = compiled_resource;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-COMPILED-RESOURCE */
Object reclaim_structure_for_compiled_resource(compiled_resource)
    Object compiled_resource;
{
    x_note_fn_call(246,3);
    return reclaim_compiled_resource_1(compiled_resource);
}

static Object Qg2_defstruct_structure_name_compiled_resource_g2_struct;  /* g2-defstruct-structure-name::compiled-resource-g2-struct */

/* MAKE-PERMANENT-COMPILED-RESOURCE-STRUCTURE-INTERNAL */
Object make_permanent_compiled_resource_structure_internal()
{
    Object def_structure_compiled_resource_variable;
    Object defstruct_g2_compiled_resource_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(246,4);
    def_structure_compiled_resource_variable = Nil;
    atomic_incff_symval(Qcompiled_resource_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_compiled_resource_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_compiled_resource_variable = the_array;
	SVREF(defstruct_g2_compiled_resource_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compiled_resource_g2_struct;
	def_structure_compiled_resource_variable = 
		defstruct_g2_compiled_resource_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_compiled_resource_variable);
}

/* MAKE-COMPILED-RESOURCE-1 */
Object make_compiled_resource_1(compiled_resource_native_p,
	    compiled_resource_type,compiled_resource_id,
	    compiled_resource_language)
    Object compiled_resource_native_p, compiled_resource_type;
    Object compiled_resource_id, compiled_resource_language;
{
    Object def_structure_compiled_resource_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(246,5);
    def_structure_compiled_resource_variable = 
	    ISVREF(Chain_of_available_compiled_resources_vector,
	    IFIX(Current_thread_index));
    if (def_structure_compiled_resource_variable) {
	svref_arg_1 = Chain_of_available_compiled_resources_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_compiled_resource_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_compiled_resource_g2_struct;
    }
    else
	def_structure_compiled_resource_variable = 
		make_permanent_compiled_resource_structure_internal();
    inline_note_allocate_cons(def_structure_compiled_resource_variable,Nil);
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)1L)) = 
	    compiled_resource_native_p;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)2L)) = 
	    compiled_resource_type;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)3L)) = 
	    compiled_resource_id;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)4L)) = 
	    compiled_resource_language;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_compiled_resource_variable,FIX((SI_Long)7L)) = Nil;
    return VALUES_1(def_structure_compiled_resource_variable);
}

/* RECLAIM-COMPILED-RESOURCE-SLOT */
Object reclaim_compiled_resource_slot(slot_value)
    Object slot_value;
{
    x_note_fn_call(246,6);
    return reclaim_slot_value(slot_value);
}

/* COMPILED-RESOURCE-P-FUNCTION */
Object compiled_resource_p_function(thing)
    Object thing;
{
    x_note_fn_call(246,7);
    if (SIMPLE_VECTOR_P(thing))
	return VALUES_1(EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_compiled_resource_g2_struct) ?
		 T : Nil);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-COMPILED-RESOURCE-FUNCTION */
Object reclaim_compiled_resource_function(compiled_resource)
    Object compiled_resource;
{
    x_note_fn_call(246,8);
    return reclaim_compiled_resource_1(compiled_resource);
}

/* ENCODE-RESOURCE-AS-LIST */
Object encode_resource_as_list(compiled_resource)
    Object compiled_resource;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value;

    x_note_fn_call(246,9);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)7L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = ISVREF(compiled_resource,(SI_Long)1L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)2L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)3L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)4L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)5L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)6L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(compiled_resource,(SI_Long)7L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    return VALUES_1(gensymed_symbol);
}

static Object Qab_gensym;          /* gensym */

/* DECODE-RESOURCE-FROM-LIST */
Object decode_resource_from_list(list_1)
    Object list_1;
{
    Object gensym_pop_store, cons_1, next_cons, temp, svref_arg_2, temp_1;
    Object temp_2, temp_3, compiled_resource;

    x_note_fn_call(246,10);
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    temp_1 = gensym_pop_store;
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    temp_2 = gensym_pop_store;
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    temp_3 = gensym_pop_store;
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    compiled_resource = make_compiled_resource_1(temp_1,temp_2,temp_3,
	    gensym_pop_store);
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    SVREF(compiled_resource,FIX((SI_Long)5L)) = gensym_pop_store;
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    SVREF(compiled_resource,FIX((SI_Long)6L)) = gensym_pop_store;
    gensym_pop_store = Nil;
    cons_1 = list_1;
    if (cons_1) {
	gensym_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    list_1 = next_cons;
    SVREF(compiled_resource,FIX((SI_Long)7L)) = gensym_pop_store;
    return VALUES_1(compiled_resource);
}

/* SAFE-AND-STUPID-GETF */
Object safe_and_stupid_getf(plist,indicator)
    Object plist, indicator;
{
    x_note_fn_call(246,11);
    if (FIXNUM_ODDP(length(plist)))
	return VALUES_1(Nil);
    else
	return getf(plist,indicator,_);
}

static Object Qis_native;          /* is-native */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qtop_level_type;     /* top-level-type */

static Object Qid;                 /* id */

static Object Qfloat_array;        /* float-array */

static Object Qtruth_value;        /* truth-value */

static Object Qlanguage;           /* language */

static Object Qload_option;        /* load-option */

static Object Qab_structure;       /* structure */

static Object Qmemory_options;     /* memory-options */

/* COMPILED-RESOURCE-TO-COMPONENT */
Object compiled_resource_to_component(compiled_resource)
    Object compiled_resource;
{
    Object gensymed_symbol, temp, item_or_value, x2, temp_2, value;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    Object gensymed_symbol_2, temp_3, new_structure, memory_options_qm, option;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, temp_4, name, value_1;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    double aref_new_value;

    x_note_fn_call(246,12);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qis_native;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qis_native;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(compiled_resource,(SI_Long)1L) ? 
		Evaluation_true_value : Evaluation_false_value;
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(compiled_resource,(SI_Long)1L) ? 
		Evaluation_true_value : Evaluation_false_value;
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
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtop_level_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qtop_level_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(compiled_resource,(SI_Long)2L);
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(compiled_resource,(SI_Long)2L);
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
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qid;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qid;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	value = ISVREF(compiled_resource,(SI_Long)3L);
	if (FIXNUMP(value))
	    item_or_value = value;
	else if ( !TRUEP(value))
	    item_or_value = Evaluation_false_value;
	else if (EQ(value,T))
	    item_or_value = Evaluation_true_value;
	else if (SYMBOLP(value))
	    item_or_value = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    item_or_value = copy_managed_float(value);
	else if (FLOATP(value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp,temp_2) = amf_available_array_cons_qm;
		    temp = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp,temp_2) = amf_available_array_cons_qm;
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
	    item_or_value = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    item_or_value = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    item_or_value = make_evaluation_long(value);
	else if (text_string_p(value))
	    item_or_value = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol_2 = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		item_or_value = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		item_or_value = Evaluation_false_value;
	    else
		item_or_value = eval_cons_1(gensymed_symbol_2,Qtruth_value);
	}
	else
	    item_or_value = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	value = ISVREF(compiled_resource,(SI_Long)3L);
	if (FIXNUMP(value))
	    item_or_value = value;
	else if ( !TRUEP(value))
	    item_or_value = Evaluation_false_value;
	else if (EQ(value,T))
	    item_or_value = Evaluation_true_value;
	else if (SYMBOLP(value))
	    item_or_value = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    item_or_value = copy_managed_float(value);
	else if (FLOATP(value)) {
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
	    item_or_value = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    item_or_value = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    item_or_value = make_evaluation_long(value);
	else if (text_string_p(value))
	    item_or_value = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol_2 = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol_2,Truth))
		item_or_value = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol_2,Falsity))
		item_or_value = Evaluation_false_value;
	    else
		item_or_value = eval_cons_1(gensymed_symbol_2,Qtruth_value);
	}
	else
	    item_or_value = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
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
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qlanguage;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qlanguage;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(compiled_resource,(SI_Long)4L);
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(compiled_resource,(SI_Long)4L);
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
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qload_option;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qload_option;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(compiled_resource,(SI_Long)5L);
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
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = ISVREF(compiled_resource,(SI_Long)5L);
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
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)10L)) = temp_2;
    }
    new_structure = eval_cons_1(gensymed_symbol,Qab_structure);
    memory_options_qm = ISVREF(compiled_resource,(SI_Long)6L);
    if (memory_options_qm) {
	option = Nil;
	ab_loop_list_ = memory_options_qm;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	option = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(option,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp_4 = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp_4 = Qnil;
      end_1:;
	set_evaluation_structure_slot(new_structure,Qmemory_options,temp_4);
    }
    name = Nil;
    value_1 = Nil;
    ab_loop_list_ = ISVREF(compiled_resource,(SI_Long)7L);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
  next_loop_1:
    name = CAR(ab_loop_list_);
    temp_4 = CDR(ab_loop_list_);
    value_1 = CAR(temp_4);
    add_resource_property_to_structure(new_structure,
	    ISVREF(compiled_resource,(SI_Long)2L),name,value_1);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(new_structure);
}

static Object Qtext;               /* text */

static Object Qcontrol_text;       /* control-text */

static Object Qstyle;              /* style */

static Object Qoptions;            /* options */

static Object Qattributes;         /* attributes */

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

static Object Qcontents;           /* contents */

static Object Qwin32;              /* win32 */

/* ADD-RESOURCE-PROPERTY-TO-STRUCTURE */
Object add_resource_property_to_structure(structure,type,name,value)
    Object structure, type, name, value;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float, gensymed_symbol, attr_structure, attr_name;
    Object attr_value, ab_loop_list_, temp_3, control, ab_loopvar_;
    Object ab_loopvar__1, gensymed_symbol_2, native_p, control_type, id;
    Object properties, item_or_value, x2, control_structure, prop_name;
    Object prop_value, ab_loop_list__1;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_4;
    double aref_new_value;

    x_note_fn_call(246,13);
    if (EQ(name,Qtext)) {
	if (FIXNUMP(value))
	    temp = value;
	else if ( !TRUEP(value))
	    temp = Evaluation_false_value;
	else if (EQ(value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(value))
	    temp = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_float(value);
	else if (FLOATP(value)) {
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
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    temp = make_evaluation_long(value);
	else if (text_string_p(value))
	    temp = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
	return set_evaluation_structure_slot(structure,Qcontrol_text,temp);
    }
    else if (SYMBOLP(value) || FIXNUMP(value) || text_string_p(value)) {
	if (FIXNUMP(value))
	    temp = value;
	else if ( !TRUEP(value))
	    temp = Evaluation_false_value;
	else if (EQ(value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(value))
	    temp = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_float(value);
	else if (FLOATP(value)) {
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
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    temp = make_evaluation_long(value);
	else if (text_string_p(value))
	    temp = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
	return set_evaluation_structure_slot(structure,name,temp);
    }
    else if (EQ(name,Qstyle))
	return set_evaluation_structure_slot(structure,name,
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(value)));
    else if (EQ(name,Qoptions))
	return set_evaluation_structure_slot(structure,name,
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(value)));
    else if (EQ(name,Qattributes)) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	attr_structure = eval_cons_1(gensymed_symbol,Qab_structure);
	attr_name = Nil;
	attr_value = Nil;
	ab_loop_list_ = value;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	attr_name = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	attr_value = CAR(temp);
	temp = attr_name;
	if (EQ(attr_value,Qtrue))
	    temp_3 = Evaluation_true_value;
	else if (EQ(attr_value,Qfalse))
	    temp_3 = Evaluation_false_value;
	else if (LISTP(attr_value))
	    temp_3 = 
		    allocate_evaluation_sequence(copy_list_using_eval_conses_1(attr_value));
	else
	    temp_3 = FIXNUMP(attr_value) || attr_value && 
		    SYMBOLP(attr_value) || SIMPLE_VECTOR_P(attr_value) ? 
		    attr_value : copy_if_evaluation_value_1(attr_value);
	set_evaluation_structure_slot(attr_structure,temp,temp_3);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:;
	return set_evaluation_structure_slot(structure,name,attr_structure);
    }
    else if (EQ(name,Qcontents)) {
	control = Nil;
	ab_loop_list_ = value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	control = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_2 = control;
	native_p = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	control_type = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	id = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	properties = CAR(gensymed_symbol_2);
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)6L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qis_native;
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qis_native;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = EQ(native_p,Qwin32) ? T : Nil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_1 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = EQ(native_p,Qwin32) ? T : Nil;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_2 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qtype;
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qtype;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = control_type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_1 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = control_type;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_2 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)7L)) = Qid;
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qid;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = id;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_1 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = id;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    temp_2 = temp_4 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = temp_2;
	}
	control_structure = eval_cons_1(gensymed_symbol_2,Qab_structure);
	prop_name = Nil;
	prop_value = Nil;
	ab_loop_list__1 = properties;
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
      next_loop_2:
	prop_name = CAR(ab_loop_list__1);
	temp = CDR(ab_loop_list__1);
	prop_value = CAR(temp);
	add_resource_property_to_structure(control_structure,control_type,
		prop_name,prop_value);
	ab_loop_list__1 = CDDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	goto next_loop_2;
      end_loop_2:;
	ab_loopvar__1 = eval_cons_1(control_structure,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_1;
      end_loop_1:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
	return set_evaluation_structure_slot(structure,name,temp);
    }
    else
	return VALUES_1(Qnil);
}

void resources_INIT()
{
    Object temp, reclaim_structure_for_compiled_resource_1;
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qcompiled_resource;
    Object Qreclaim_structure, Qoutstanding_compiled_resource_count;
    Object Qcompiled_resource_structure_memory_usage, Qutilities2;
    Object string_constant_1, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;

    x_note_fn_call(246,14);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_compiled_resource_g2_struct = 
	    STATIC_SYMBOL("COMPILED-RESOURCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qcompiled_resource = STATIC_SYMBOL("COMPILED-RESOURCE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_compiled_resource_g2_struct,
	    Qcompiled_resource,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qcompiled_resource,
	    Qg2_defstruct_structure_name_compiled_resource_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_compiled_resource == UNBOUND)
	The_type_description_of_compiled_resource = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m83g2y1n83g2y8n8k1l8n0000001l1n8y83-3Ey1o83sQy83sRy83sOy83sPyksk0k0");
    temp = The_type_description_of_compiled_resource;
    The_type_description_of_compiled_resource = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_compiled_resource_g2_struct,
	    The_type_description_of_compiled_resource,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qcompiled_resource,
	    The_type_description_of_compiled_resource,
	    Qtype_description_of_type);
    Qoutstanding_compiled_resource_count = 
	    STATIC_SYMBOL("OUTSTANDING-COMPILED-RESOURCE-COUNT",AB_package);
    Qcompiled_resource_structure_memory_usage = 
	    STATIC_SYMBOL("COMPILED-RESOURCE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q83g2y8s83-NQy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_compiled_resource_count);
    push_optimized_constant(Qcompiled_resource_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_compiled_resources = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-COMPILED-RESOURCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_compiled_resources,
	    Chain_of_available_compiled_resources);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_compiled_resources,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcompiled_resource_count = STATIC_SYMBOL("COMPILED-RESOURCE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcompiled_resource_count,
	    Compiled_resource_count);
    record_system_variable(Qcompiled_resource_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_compiled_resources_vector == UNBOUND)
	Chain_of_available_compiled_resources_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcompiled_resource_structure_memory_usage,
	    STATIC_FUNCTION(compiled_resource_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_compiled_resource_count,
	    STATIC_FUNCTION(outstanding_compiled_resource_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_compiled_resource_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_compiled_resource,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qcompiled_resource,
	    reclaim_structure_for_compiled_resource_1);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qis_native = STATIC_SYMBOL("IS-NATIVE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtop_level_type = STATIC_SYMBOL("TOP-LEVEL-TYPE",AB_package);
    Qid = STATIC_SYMBOL("ID",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Qload_option = STATIC_SYMBOL("LOAD-OPTION",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qmemory_options = STATIC_SYMBOL("MEMORY-OPTIONS",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qcontrol_text = STATIC_SYMBOL("CONTROL-TEXT",AB_package);
    Qstyle = STATIC_SYMBOL("STYLE",AB_package);
    Qoptions = STATIC_SYMBOL("OPTIONS",AB_package);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    Qcontents = STATIC_SYMBOL("CONTENTS",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
}
