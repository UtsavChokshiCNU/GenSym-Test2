/* utlts2.c
 * Input file:  utilities2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts2.h"


Object Def_structure_slot_descriptions_prop = UNBOUND;

Object Ab_name_of_unique_structure_type_prop = UNBOUND;

Object Unique_structure_type_of_ab_name_qm_prop = UNBOUND;

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* FIND-STRUCTURE-METHOD */
Object find_structure_method(method_name,structure)
    Object method_name, structure;
{
    Object temp, method_id_qm, gensymed_symbol;
    SI_Long id, ab_loop_bind_;

    x_note_fn_call(24,0);
    id = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Maximum_number_of_structure_methods);
  next_loop:
    if (id >= ab_loop_bind_)
	goto end_loop;
    temp = ISVREF(Table_to_map_structure_id_to_method_name,id);
    if (EQL(temp,method_name)) {
	method_id_qm = FIX(id);
	goto end_1;
    }
    id = id + (SI_Long)1L;
    goto next_loop;
  end_loop:
    method_id_qm = Qnil;
  end_1:;
    if (method_id_qm) {
	gensymed_symbol = ISVREF(structure,(SI_Long)0L);
	return VALUES_1(ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),IFIX(method_id_qm)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qtype_description_of_type;  /* type-description-of-type */

/* RECORD-DIRECT-STRUCTURE-METHOD */
Object record_direct_structure_method(method_name,structure_ab_type,
	    method_function)
    Object method_name, structure_ab_type, method_function;
{
    Object type_description, direct_methods, existing_entry_qm, push_arg, temp;
    SI_Long id, ab_loop_bind_;

    x_note_fn_call(24,1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qtype_description_of_type);
    direct_methods = ISVREF(type_description,(SI_Long)8L);
    existing_entry_qm = assq_function(method_name,direct_methods);
    if (existing_entry_qm)
	M_SECOND(existing_entry_qm) = method_function;
    else {
	push_arg = LIST_2(method_name,method_function);
	direct_methods = CONS(push_arg,direct_methods);
    }
    SVREF(type_description,FIX((SI_Long)8L)) = direct_methods;
    id = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Maximum_number_of_structure_methods);
  next_loop:
    if (id >= ab_loop_bind_)
	goto end_loop;
    temp = ISVREF(Table_to_map_structure_id_to_method_name,id);
    if (EQL(temp,method_name)) {
	temp = FIX(id);
	goto end_1;
    }
    id = id + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return set_structure_method_and_propogate(structure_ab_type,
	    method_name,temp,method_function);
}

/* DIRECT-STRUCTURE-METHOD */
Object direct_structure_method(method_name,structure_ab_type)
    Object method_name, structure_ab_type;
{
    Object type_description, direct_methods, temp;

    x_note_fn_call(24,2);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qtype_description_of_type);
    direct_methods = ISVREF(type_description,(SI_Long)8L);
    temp = assq_function(method_name,direct_methods);
    return VALUES_1(SECOND(temp));
}

/* SET-STRUCTURE-METHOD-AND-PROPOGATE */
Object set_structure_method_and_propogate(structure_ab_type,method_name,
	    method_id,method_function)
    Object structure_ab_type, method_name, method_id, method_function;
{
    Object type_description, dispatch_table_of_this_structure_type, subtype;
    Object ab_loop_list_;

    x_note_fn_call(24,3);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qtype_description_of_type);
    dispatch_table_of_this_structure_type = ISVREF(type_description,
	    (SI_Long)9L);
    SVREF(dispatch_table_of_this_structure_type,method_id) = method_function;
    subtype = Nil;
    ab_loop_list_ = ISVREF(type_description,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    subtype = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !( !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(subtype),
	    Qtype_description_of_type)) || assq_function(method_name,
	    ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(subtype),
	    Qtype_description_of_type),(SI_Long)8L))))
	set_structure_method_and_propogate(subtype,method_name,method_id,
		method_function);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Structure_method_arglist_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Structure_being_reclaimed, Qstructure_being_reclaimed);

/* RESET-STRUCTURE-BEING-RECLAIMED-AFTER-BOMBOUT */
Object reset_structure_being_reclaimed_after_bombout()
{
    x_note_fn_call(24,4);
    Structure_being_reclaimed = Nil;
    return VALUES_1(Structure_being_reclaimed);
}

static Object Qab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

/* TYPE-OF-NAMED-STRUCTURE */
Object type_of_named_structure(named_structure_instance)
    Object named_structure_instance;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(24,5);
    gensymed_symbol = SIMPLE_VECTOR_P(named_structure_instance) ? 
	    ISVREF(named_structure_instance,(SI_Long)0L) : 
	    CAR(named_structure_instance);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qab_name_of_unique_structure_type);
    return VALUES_1(temp);
}

/* LOAD-AND-INITIALIZE-TYPE-DESCRIPTION */
Object load_and_initialize_type_description(old_type_description_qm,
	    new_type_description)
    Object old_type_description_qm, new_type_description;
{
    Object temp, new_superior_type, new_superior_type_qm;
    Object new_superior_type_description_qm, new_dispatch_table;
    Object svref_new_value, pushnew_arg;
    SI_Long i, ab_loop_bind_;
    char temp_1;

    x_note_fn_call(24,6);
    temp = ISVREF(new_type_description,(SI_Long)2L);
    new_superior_type = SECOND(temp);
    new_superior_type_qm = EQ(T,new_superior_type) ? Nil : new_superior_type;
    new_superior_type_description_qm = new_superior_type_qm ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(new_superior_type),
	    Qtype_description_of_type) : Nil;
    if (old_type_description_qm) {
	temp = ISVREF(old_type_description_qm,(SI_Long)2L);
	temp_1 = EQ(new_superior_type_qm,SECOND(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	new_dispatch_table = ISVREF(old_type_description_qm,(SI_Long)9L);
    else if (new_superior_type_qm)
	new_dispatch_table = 
		make_structure_method_table(ISVREF(new_superior_type_description_qm,
		(SI_Long)9L));
    else
	new_dispatch_table = make_structure_method_table(Nil);
    svref_new_value = 
	    ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(new_superior_type),
	    Qtype_description_of_type),(SI_Long)9L);
    SVREF(new_dispatch_table,FIX((SI_Long)0L)) = svref_new_value;
    SVREF(new_type_description,FIX((SI_Long)9L)) = new_dispatch_table;
    if (new_superior_type_description_qm) {
	pushnew_arg = ISVREF(new_type_description,(SI_Long)1L);
	svref_new_value = adjoin(2,pushnew_arg,
		ISVREF(new_superior_type_description_qm,(SI_Long)4L));
	SVREF(new_superior_type_description_qm,FIX((SI_Long)4L)) = 
		svref_new_value;
    }
    if (old_type_description_qm) {
	svref_new_value = ISVREF(old_type_description_qm,(SI_Long)4L);
	SVREF(new_type_description,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (old_type_description_qm) {
	i = (SI_Long)1L;
	ab_loop_bind_ = 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_type_description_qm));
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	svref_new_value = ISVREF(new_type_description,i);
	ISVREF(old_type_description_qm,i) = svref_new_value;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	return VALUES_1(old_type_description_qm);
    }
    else
	return VALUES_1(new_type_description);
}

/* RECLAIM-STRUCTURE-FUNCTION */
Object reclaim_structure_function(named_gensym_structure)
    Object named_gensym_structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,7);
    gensymed_symbol = ISVREF(named_gensym_structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = named_gensym_structure;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-STRUCTURE-IF-ANY */
Object reclaim_structure_if_any(structure_qm)
    Object structure_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,8);
    if (structure_qm) {
	gensymed_symbol = ISVREF(structure_qm,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = structure_qm;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-IF-STRUCTURE */
Object reclaim_if_structure(thing_qm)
    Object thing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,9);
    if (allocated_named_gensym_structure_p(thing_qm)) {
	gensymed_symbol = ISVREF(thing_qm,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = thing_qm;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(Nil);
}

/* CLEAN-UP-STRUCTURE-FUNCTION */
Object clean_up_structure_function(named_gensym_structure)
    Object named_gensym_structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,10);
    gensymed_symbol = ISVREF(named_gensym_structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)9L);
    gensymed_symbol_1 = named_gensym_structure;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* CLEAN-UP-AND-RECLAIM-STRUCTURE */
Object clean_up_and_reclaim_structure(structure)
    Object structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,11);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)9L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

Object The_type_description_of_named_gensym_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_named_gensym_structures, Qchain_of_available_named_gensym_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Named_gensym_structure_count, Qnamed_gensym_structure_count);

Object Chain_of_available_named_gensym_structures_vector = UNBOUND;

/* NAMED-GENSYM-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object named_gensym_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,12);
    temp = Named_gensym_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)1L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-NAMED-GENSYM-STRUCTURE-COUNT */
Object outstanding_named_gensym_structure_count()
{
    Object def_structure_named_gensym_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,13);
    gensymed_symbol = IFIX(Named_gensym_structure_count);
    def_structure_named_gensym_structure_variable = 
	    Chain_of_available_named_gensym_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_named_gensym_structure_variable))
	goto end_loop;
    def_structure_named_gensym_structure_variable = 
	    ISVREF(def_structure_named_gensym_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-NAMED-GENSYM-STRUCTURE-1 */
Object reclaim_named_gensym_structure_1(named_gensym_structure)
    Object named_gensym_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,14);
    inline_note_reclaim_cons(named_gensym_structure,Nil);
    temp = ISVREF(Chain_of_available_named_gensym_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(named_gensym_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_named_gensym_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = named_gensym_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NAMED-GENSYM-STRUCTURE */
Object reclaim_structure_for_named_gensym_structure(named_gensym_structure)
    Object named_gensym_structure;
{
    x_note_fn_call(24,15);
    return reclaim_named_gensym_structure_1(named_gensym_structure);
}

static Object Qg2_defstruct_structure_name_named_gensym_structure_g2_struct;  /* g2-defstruct-structure-name::named-gensym-structure-g2-struct */

/* MAKE-PERMANENT-NAMED-GENSYM-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_named_gensym_structure_structure_internal()
{
    Object def_structure_named_gensym_structure_variable;
    Object defstruct_g2_named_gensym_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,16);
    def_structure_named_gensym_structure_variable = Nil;
    atomic_incff_symval(Qnamed_gensym_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_named_gensym_structure_variable = Nil;
	gensymed_symbol = (SI_Long)1L;
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
	defstruct_g2_named_gensym_structure_variable = the_array;
	SVREF(defstruct_g2_named_gensym_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_named_gensym_structure_g2_struct;
	def_structure_named_gensym_structure_variable = 
		defstruct_g2_named_gensym_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_named_gensym_structure_variable);
}

/* MAKE-NAMED-GENSYM-STRUCTURE-1 */
Object make_named_gensym_structure_1()
{
    Object def_structure_named_gensym_structure_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(24,17);
    def_structure_named_gensym_structure_variable = 
	    ISVREF(Chain_of_available_named_gensym_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_named_gensym_structure_variable) {
	svref_arg_1 = Chain_of_available_named_gensym_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_named_gensym_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_named_gensym_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_named_gensym_structure_g2_struct;
    }
    else
	def_structure_named_gensym_structure_variable = 
		make_permanent_named_gensym_structure_structure_internal();
    inline_note_allocate_cons(def_structure_named_gensym_structure_variable,
	    Nil);
    return VALUES_1(def_structure_named_gensym_structure_variable);
}

Object The_type_description_of_type_description = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_type_descriptions, Qchain_of_available_type_descriptions);

DEFINE_VARIABLE_WITH_SYMBOL(Type_description_count, Qtype_description_count);

Object Chain_of_available_type_descriptions_vector = UNBOUND;

/* TYPE-DESCRIPTION-STRUCTURE-MEMORY-USAGE */
Object type_description_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,18);
    temp = Type_description_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)17L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TYPE-DESCRIPTION-COUNT */
Object outstanding_type_description_count()
{
    Object def_structure_type_description_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,19);
    gensymed_symbol = IFIX(Type_description_count);
    def_structure_type_description_variable = 
	    Chain_of_available_type_descriptions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_type_description_variable))
	goto end_loop;
    def_structure_type_description_variable = 
	    ISVREF(def_structure_type_description_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TYPE-DESCRIPTION-1 */
Object reclaim_type_description_1(type_description)
    Object type_description;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,20);
    inline_note_reclaim_cons(type_description,Nil);
    temp = ISVREF(Chain_of_available_type_descriptions_vector,
	    IFIX(Current_thread_index));
    SVREF(type_description,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_type_descriptions_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = type_description;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TYPE-DESCRIPTION */
Object reclaim_structure_for_type_description(type_description)
    Object type_description;
{
    x_note_fn_call(24,21);
    return reclaim_type_description_1(type_description);
}

static Object Qg2_defstruct_structure_name_type_description_g2_struct;  /* g2-defstruct-structure-name::type-description-g2-struct */

/* MAKE-PERMANENT-TYPE-DESCRIPTION-STRUCTURE-INTERNAL */
Object make_permanent_type_description_structure_internal()
{
    Object def_structure_type_description_variable;
    Object defstruct_g2_type_description_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,22);
    def_structure_type_description_variable = Nil;
    atomic_incff_symval(Qtype_description_count,FIX((SI_Long)20L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_type_description_variable = Nil;
	gensymed_symbol_1 = (SI_Long)17L;
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
	defstruct_g2_type_description_variable = the_array;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_type_description_g2_struct;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_type_description_variable,FIX((SI_Long)16L)) = Nil;
	def_structure_type_description_variable = 
		defstruct_g2_type_description_variable;
	if (gensymed_symbol >= (SI_Long)20L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_type_descriptions_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_type_description_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_type_descriptions_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_type_description_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_type_description_variable);
}

/* MAKE-TYPE-DESCRIPTION-1 */
Object make_type_description_1()
{
    Object def_structure_type_description_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,23);
    def_structure_type_description_variable = 
	    ISVREF(Chain_of_available_type_descriptions_vector,
	    IFIX(Current_thread_index));
    if (def_structure_type_description_variable) {
	temp = Chain_of_available_type_descriptions_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_type_description_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_type_description_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_type_description_g2_struct;
    }
    else
	def_structure_type_description_variable = 
		make_permanent_type_description_structure_internal();
    inline_note_allocate_cons(def_structure_type_description_variable,Nil);
    SVREF(def_structure_type_description_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)8L)) = Nil;
    temp = make_array(1,FIX((SI_Long)10L));
    SVREF(def_structure_type_description_variable,FIX((SI_Long)9L)) = temp;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_type_description_variable,FIX((SI_Long)11L)) = Nil;
    ISVREF(def_structure_type_description_variable,(SI_Long)12L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_type_description_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_type_description_variable,(SI_Long)14L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_type_description_variable,(SI_Long)15L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_type_description_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_type_description_variable);
}

/* PRINT-TYPE-DESCRIPTION */
Object print_type_description(type_description,stream,depth)
    Object type_description, stream, depth;
{
    Object dot_object_dot, dot_stream_dot, temp;

    x_note_fn_call(24,24);
    dot_object_dot = type_description;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    temp = ISVREF(type_description_of(type_description),(SI_Long)1L);
    format((SI_Long)4L,stream,"~a ~a",temp,ISVREF(type_description,
	    (SI_Long)1L));
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

/* TYPE-NAME-OF */
Object type_name_of(thing)
    Object thing;
{
    Object description_qm;

    x_note_fn_call(24,25);
    description_qm = type_description_of(thing);
    if (description_qm)
	return VALUES_1(ISVREF(description_qm,(SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* STRUCTURE-TYPE-P */
Object structure_type_p(named_gensym_structure,type)
    Object named_gensym_structure, type;
{
    Object type_description_of_type, type_description_of_instance, temp;

    x_note_fn_call(24,26);
    type_description_of_type = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
	    Qtype_description_of_type);
    type_description_of_instance = type_description_of(named_gensym_structure);
    temp = EQL(type_description_of_instance,type_description_of_type) ? T :
	     Nil;
    if (temp);
    else
	temp = 
		subtype_p_using_type_descriptions(type_description_of_instance,
		type_description_of_type);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_vector_pool_conses, Qavailable_vector_pool_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_vector_pool_conses_tail, Qavailable_vector_pool_conses_tail);

Object Available_vector_pool_conses_vector = UNBOUND;

Object Available_vector_pool_conses_tail_vector = UNBOUND;

Object Vector_pool_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Vector_pool_cons_counter, Qvector_pool_cons_counter);

/* OUTSTANDING-VECTOR-POOL-CONSES */
Object outstanding_vector_pool_conses()
{
    Object temp;

    x_note_fn_call(24,27);
    temp = FIXNUM_MINUS(Vector_pool_cons_counter,
	    length(Available_vector_pool_conses));
    return VALUES_1(temp);
}

/* VECTOR-POOL-CONS-MEMORY-USAGE */
Object vector_pool_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(24,28);
    temp = FIXNUM_TIMES(Vector_pool_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-VECTOR-POOL-CONS-POOL */
Object replenish_vector_pool_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(24,29);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qvector_pool_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Vector_pool_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qvector_pool;        /* vector-pool */

/* VECTOR-POOL-CONS-1 */
Object vector_pool_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(24,30);
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-VECTOR-POOL-LIST-POOL */
Object replenish_vector_pool_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(24,31);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qvector_pool_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-VECTOR-POOL-LIST-1 */
Object make_vector_pool_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(24,32);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_vector_pool_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_vector_pool_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* VECTOR-POOL-LIST-2 */
Object vector_pool_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,33);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_vector_pool_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qvector_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_vector_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* VECTOR-POOL-LIST-3 */
Object vector_pool_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,34);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_vector_pool_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qvector_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_vector_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* VECTOR-POOL-LIST-4 */
Object vector_pool_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,35);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_vector_pool_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qvector_pool);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_vector_pool_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* VECTOR-POOL-LIST-TRACE-HOOK */
Object vector_pool_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(24,36);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-VECTOR-POOL-CONSES-1 */
Object copy_tree_using_vector_pool_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,37);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_vector_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_vector_pool_cons_pool();
	temp_1 = copy_tree_using_vector_pool_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_vector_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_vector_pool_cons_pool();
	temp_1 = 
		copy_tree_using_vector_pool_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-VECTOR-POOL-CONSES-1 */
Object copy_list_using_vector_pool_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,38);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_vector_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_vector_pool_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_vector_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_vector_pool_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-VECTOR-POOL-CONS-1 */
Object reclaim_vector_pool_cons_1(vector_pool_cons)
    Object vector_pool_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,39);
    inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
    if (ISVREF(Available_vector_pool_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = vector_pool_cons;
	temp = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = vector_pool_cons;
    }
    else {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = vector_pool_cons;
	temp = Available_vector_pool_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = vector_pool_cons;
    }
    M_CDR(vector_pool_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-VECTOR-POOL-LIST-1 */
Object reclaim_vector_pool_list_1(vector_pool_list)
    Object vector_pool_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,40);
    if (vector_pool_list) {
	last_1 = vector_pool_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qvector_pool);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = vector_pool_list;
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_vector_pool_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = vector_pool_list;
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-VECTOR-POOL-LIST*-1 */
Object reclaim_vector_pool_list_star_1(vector_pool_list)
    Object vector_pool_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(24,41);
    if (CONSP(vector_pool_list)) {
	temp = last(vector_pool_list,_);
	M_CDR(temp) = Nil;
	if (vector_pool_list) {
	    last_1 = vector_pool_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qvector_pool);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qvector_pool);
	    if (ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_vector_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = vector_pool_list;
		temp = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_vector_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = vector_pool_list;
		temp = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-VECTOR-POOL-TREE-1 */
Object reclaim_vector_pool_tree_1(tree)
    Object tree;
{
    Object e, e2, vector_pool_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,42);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_vector_pool_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		vector_pool_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
		if (EQ(vector_pool_cons,e))
		    goto end_1;
		else if ( !TRUEP(vector_pool_cons))
		    goto end_1;
		else
		    vector_pool_cons = CDR(vector_pool_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_vector_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_vector_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-VECTOR-POOL-ELEMENT-1 */
Object delete_vector_pool_element_1(element,vector_pool_list)
    Object element, vector_pool_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(24,43);
    if (vector_pool_list) {
	if (EQ(element,M_CAR(vector_pool_list))) {
	    temp = CDR(vector_pool_list);
	    inline_note_reclaim_cons(vector_pool_list,Qvector_pool);
	    if (ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_vector_pool_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = vector_pool_list;
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = vector_pool_list;
	    }
	    else {
		temp_1 = Available_vector_pool_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = vector_pool_list;
		temp_1 = Available_vector_pool_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = vector_pool_list;
	    }
	    M_CDR(vector_pool_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = vector_pool_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qvector_pool);
		if (ISVREF(Available_vector_pool_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_vector_pool_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_vector_pool_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_vector_pool_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_vector_pool_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = vector_pool_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-VECTOR-POOL-CONS-1 */
Object delete_vector_pool_cons_1(vector_pool_cons,vector_pool_list)
    Object vector_pool_cons, vector_pool_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(24,44);
    if (EQ(vector_pool_cons,vector_pool_list))
	temp = CDR(vector_pool_list);
    else {
	l_trailer_qm = Nil;
	l = vector_pool_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,vector_pool_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = vector_pool_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_vector_pool_cons_1(vector_pool_cons);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_lookup_conses, Qavailable_lookup_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_lookup_conses_tail, Qavailable_lookup_conses_tail);

Object Available_lookup_conses_vector = UNBOUND;

Object Available_lookup_conses_tail_vector = UNBOUND;

Object Lookup_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Lookup_cons_counter, Qlookup_cons_counter);

/* OUTSTANDING-LOOKUP-CONSES */
Object outstanding_lookup_conses()
{
    Object temp;

    x_note_fn_call(24,45);
    temp = FIXNUM_MINUS(Lookup_cons_counter,length(Available_lookup_conses));
    return VALUES_1(temp);
}

/* LOOKUP-CONS-MEMORY-USAGE */
Object lookup_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(24,46);
    temp = FIXNUM_TIMES(Lookup_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-LOOKUP-CONS-POOL */
Object replenish_lookup_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(24,47);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qlookup_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Lookup_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qlookup;             /* lookup */

/* LOOKUP-CONS-1 */
Object lookup_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(24,48);
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
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-LOOKUP-LIST-POOL */
Object replenish_lookup_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(24,49);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index))) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qlookup_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-LOOKUP-LIST-1 */
Object make_lookup_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(24,50);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_lookup_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qlookup);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* LOOKUP-LIST-2 */
Object lookup_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,51);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_lookup_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_lookup_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* LOOKUP-LIST-3 */
Object lookup_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,52);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_lookup_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_lookup_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* LOOKUP-LIST-4 */
Object lookup_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,53);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_lookup_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_lookup_conses_vector,IFIX(Current_thread_index));
    svref_arg_1 = Available_lookup_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* LOOKUP-LIST-TRACE-HOOK */
Object lookup_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(24,54);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-LOOKUP-CONSES-1 */
Object copy_tree_using_lookup_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,55);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	temp_1 = copy_tree_using_lookup_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	temp_1 = copy_tree_using_lookup_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-LOOKUP-CONSES-1 */
Object copy_list_using_lookup_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,56);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-LOOKUP-CONS-1 */
Object reclaim_lookup_cons_1(lookup_cons)
    Object lookup_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,57);
    inline_note_reclaim_cons(lookup_cons,Qlookup);
    if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	temp = ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = lookup_cons;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = lookup_cons;
    }
    else {
	temp = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = lookup_cons;
	temp = Available_lookup_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = lookup_cons;
    }
    M_CDR(lookup_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-LOOKUP-LIST-1 */
Object reclaim_lookup_list_1(lookup_list)
    Object lookup_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,58);
    if (lookup_list) {
	last_1 = lookup_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = lookup_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = lookup_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-LOOKUP-LIST*-1 */
Object reclaim_lookup_list_star_1(lookup_list)
    Object lookup_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(24,59);
    if (CONSP(lookup_list)) {
	temp = last(lookup_list,_);
	M_CDR(temp) = Nil;
	if (lookup_list) {
	    last_1 = lookup_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qlookup);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = lookup_list;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = lookup_list;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-LOOKUP-TREE-1 */
Object reclaim_lookup_tree_1(tree)
    Object tree;
{
    Object e, e2, lookup_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,60);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_lookup_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		lookup_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(lookup_cons,Qlookup);
		if (EQ(lookup_cons,e))
		    goto end_1;
		else if ( !TRUEP(lookup_cons))
		    goto end_1;
		else
		    lookup_cons = CDR(lookup_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-LOOKUP-ELEMENT-1 */
Object delete_lookup_element_1(element,lookup_list)
    Object element, lookup_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(24,61);
    if (lookup_list) {
	if (EQ(element,M_CAR(lookup_list))) {
	    temp = CDR(lookup_list);
	    inline_note_reclaim_cons(lookup_list,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = lookup_list;
		temp_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = lookup_list;
	    }
	    else {
		temp_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = lookup_list;
		temp_1 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = lookup_list;
	    }
	    M_CDR(lookup_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = lookup_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qlookup);
		if (ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = lookup_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-LOOKUP-CONS-1 */
Object delete_lookup_cons_1(lookup_cons,lookup_list)
    Object lookup_cons, lookup_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(24,62);
    if (EQ(lookup_cons,lookup_list))
	temp = CDR(lookup_list);
    else {
	l_trailer_qm = Nil;
	l = lookup_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,lookup_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = lookup_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_lookup_cons_1(lookup_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_binary_tree_element = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_binary_tree_elements, Qchain_of_available_binary_tree_elements);

DEFINE_VARIABLE_WITH_SYMBOL(Binary_tree_element_count, Qbinary_tree_element_count);

Object Chain_of_available_binary_tree_elements_vector = UNBOUND;

/* BINARY-TREE-ELEMENT-STRUCTURE-MEMORY-USAGE */
Object binary_tree_element_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,63);
    temp = Binary_tree_element_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BINARY-TREE-ELEMENT-COUNT */
Object outstanding_binary_tree_element_count()
{
    Object def_structure_binary_tree_element_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,64);
    gensymed_symbol = IFIX(Binary_tree_element_count);
    def_structure_binary_tree_element_variable = 
	    Chain_of_available_binary_tree_elements;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_binary_tree_element_variable))
	goto end_loop;
    def_structure_binary_tree_element_variable = 
	    ISVREF(def_structure_binary_tree_element_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BINARY-TREE-ELEMENT-1 */
Object reclaim_binary_tree_element_1(binary_tree_element)
    Object binary_tree_element;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,65);
    inline_note_reclaim_cons(binary_tree_element,Nil);
    temp = ISVREF(Chain_of_available_binary_tree_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(binary_tree_element,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_binary_tree_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = binary_tree_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BINARY-TREE-ELEMENT */
Object reclaim_structure_for_binary_tree_element(binary_tree_element)
    Object binary_tree_element;
{
    x_note_fn_call(24,66);
    return reclaim_binary_tree_element_1(binary_tree_element);
}

/* MAKE-PERMANENT-BINARY-TREE-ELEMENT-STRUCTURE-INTERNAL */
Object make_permanent_binary_tree_element_structure_internal()
{
    Object def_structure_binary_tree_element_variable, the_array;
    Object defstruct_g2_binary_tree_element_variable, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,67);
    def_structure_binary_tree_element_variable = Nil;
    atomic_incff_symval(Qbinary_tree_element_count,FIX((SI_Long)100L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)5L;
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
	defstruct_g2_binary_tree_element_variable = the_array;
	def_structure_binary_tree_element_variable = 
		defstruct_g2_binary_tree_element_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_binary_tree_elements_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_binary_tree_elements_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_binary_tree_element_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_binary_tree_element_variable);
}

/* MAKE-BINARY-TREE-ELEMENT-1 */
Object make_binary_tree_element_1(binary_element_hash_number,
	    less_than_branch,greater_than_branch,binary_element_alist,
	    balance_factor)
    Object binary_element_hash_number, less_than_branch, greater_than_branch;
    Object binary_element_alist, balance_factor;
{
    Object def_structure_binary_tree_element_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(24,68);
    def_structure_binary_tree_element_variable = 
	    ISVREF(Chain_of_available_binary_tree_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_binary_tree_element_variable) {
	svref_arg_1 = Chain_of_available_binary_tree_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_binary_tree_element_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_binary_tree_element_variable = 
		make_permanent_binary_tree_element_structure_internal();
    inline_note_allocate_cons(def_structure_binary_tree_element_variable,Nil);
    SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)0L)) = 
	    binary_element_hash_number;
    SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)1L)) = 
	    less_than_branch;
    SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)2L)) = 
	    greater_than_branch;
    SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)3L)) = 
	    binary_element_alist;
    SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)4L)) = 
	    balance_factor;
    return VALUES_1(def_structure_binary_tree_element_variable);
}

/* FLATTEN-BINARY-TREE */
Object flatten_binary_tree(tree)
    Object tree;
{
    x_note_fn_call(24,69);
    if (tree)
	return flatten_binary_tree_1(tree,Nil);
    else
	return VALUES_1(Nil);
}

/* FLATTEN-BINARY-TREE-1 */
Object flatten_binary_tree_1(tree,pairs)
    Object tree, pairs;
{
    Object pair, ab_loop_list_, subtree1, subtree2;

    x_note_fn_call(24,70);
    pair = Nil;
    ab_loop_list_ = ISVREF(tree,(SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pairs = gensym_cons_1(CAR(pair),gensym_cons_1(CDR(pair),pairs));
    goto next_loop;
  end_loop:;
    subtree1 = ISVREF(tree,(SI_Long)1L);
    subtree2 = ISVREF(tree,(SI_Long)2L);
    if (subtree1)
	pairs = flatten_binary_tree_1(subtree1,pairs);
    if (subtree2)
	pairs = flatten_binary_tree_1(subtree2,pairs);
    return VALUES_1(pairs);
}

static Object Qequal_rule_context;  /* equal-rule-context */

/* LOOKUP-BINARY-TREE-ENTRY */
Object lookup_binary_tree_entry(tree_element,key_comparitor,key,key_hash_init)
    Object tree_element, key_comparitor, key, key_hash_init;
{
    Object entry_cons, entry_key, temp;
    SI_Long key_hash, key_hash_local, element_hash;

    x_note_fn_call(24,71);
    key_hash = IFIX(key_hash_init);
    key_hash_local = key_hash;
    element_hash = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(tree_element))
	goto end_loop;
    element_hash = IFIX(ISVREF(tree_element,(SI_Long)0L));
    if (key_hash_local < element_hash)
	tree_element = ISVREF(tree_element,(SI_Long)1L);
    else if (key_hash_local > element_hash)
	tree_element = ISVREF(tree_element,(SI_Long)2L);
    else {
	entry_cons = ISVREF(tree_element,(SI_Long)3L);
	entry_key = Nil;
      next_loop_1:
	if ( !TRUEP(entry_cons))
	    goto end_loop_1;
	entry_key = M_CAR(M_CAR(entry_cons));
	if (EQ(key_comparitor,Qequal))
	    temp = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qequal_rule_context))
	    temp = equal_rule_context(key,entry_key);
	else
	    temp = FUNCALL_2(key_comparitor,key,entry_key);
	if (temp) {
	    temp = M_CDR(M_CAR(entry_cons));
	    goto end_1;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* LOOKUP-EQ-BINARY-TREE-ENTRY */
Object lookup_eq_binary_tree_entry(tree_element,key,key_hash_init)
    Object tree_element, key, key_hash_init;
{
    Object entry_cons, temp;
    SI_Long key_hash, key_hash_local, element_hash;

    x_note_fn_call(24,72);
    key_hash = IFIX(key_hash_init);
    key_hash_local = key_hash;
    element_hash = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(tree_element))
	goto end_loop;
    element_hash = IFIX(ISVREF(tree_element,(SI_Long)0L));
    if (key_hash_local < element_hash)
	tree_element = ISVREF(tree_element,(SI_Long)1L);
    else if (key_hash_local > element_hash)
	tree_element = ISVREF(tree_element,(SI_Long)2L);
    else {
	entry_cons = ISVREF(tree_element,(SI_Long)3L);
      next_loop_1:
	if ( !TRUEP(entry_cons))
	    goto end_loop_1;
	if (EQ(key,M_CAR(M_CAR(entry_cons)))) {
	    temp = M_CDR(M_CAR(entry_cons));
	    goto end_1;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

Object Binary_tree_ancestor = UNBOUND;

Object Binary_tree_branch = UNBOUND;

static Object Kless_than;          /* :less-than */

static Object Kgreater_than;       /* :greater-than */

/* SET-BALANCED-BINARY-TREE-ENTRY */
Object set_balanced_binary_tree_entry(binary_tree,key_comparitor,
	    mutator_function_qm,mutate_old_entry_qm,key,key_hash_init,entry)
    Object binary_tree, key_comparitor, mutator_function_qm;
    Object mutate_old_entry_qm, key, key_hash_init, entry;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object gensymed_symbol_1, insertion_point, alist, entry_cons, entry_key;
    Object temp_1, alist_entry_qm, new_node, heavy_ancestor, balance;
    SI_Long key_hash, insertion_depth, heavy_ancestor_depth;
    SI_Long insertion_point_hash, depth_of_insertion_parent, adjust_point;
    SI_Long ab_loop_bind_, svref_new_value_1;

    x_note_fn_call(24,73);
    key_hash = IFIX(key_hash_init);
    if ( !TRUEP(CDR(binary_tree))) {
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
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
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
	M_CAR(gensymed_symbol_1) = key;
	M_CDR(gensymed_symbol_1) = entry;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	temp = make_binary_tree_element_1(FIX(key_hash),Nil,Nil,
		gensymed_symbol,FIX((SI_Long)0L));
	M_CDR(binary_tree) = temp;
	return VALUES_1(entry);
    }
    insertion_point = CDR(binary_tree);
    insertion_depth = (SI_Long)0L;
    heavy_ancestor_depth = (SI_Long)0L;
    insertion_point_hash = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(insertion_point))
	goto end_loop;
    insertion_point_hash = IFIX(ISVREF(insertion_point,(SI_Long)0L));
    if (IFIX(ISVREF(insertion_point,(SI_Long)4L)) != (SI_Long)0L)
	heavy_ancestor_depth = insertion_depth;
    if (key_hash < insertion_point_hash) {
	temp = Binary_tree_ancestor;
	ISVREF(temp,insertion_depth) = insertion_point;
	temp = Binary_tree_branch;
	ISVREF(temp,insertion_depth) = Kless_than;
	insertion_depth = insertion_depth + (SI_Long)1L;
	insertion_point = ISVREF(insertion_point,(SI_Long)1L);
    }
    else if (key_hash > insertion_point_hash) {
	temp = Binary_tree_ancestor;
	ISVREF(temp,insertion_depth) = insertion_point;
	temp = Binary_tree_branch;
	ISVREF(temp,insertion_depth) = Kgreater_than;
	insertion_depth = insertion_depth + (SI_Long)1L;
	insertion_point = ISVREF(insertion_point,(SI_Long)2L);
    }
    else {
	alist = ISVREF(insertion_point,(SI_Long)3L);
	entry_cons = alist;
	entry_key = Nil;
      next_loop_1:
	if ( !TRUEP(entry_cons))
	    goto end_loop_1;
	entry_key = M_CAR(M_CAR(entry_cons));
	if (EQ(key_comparitor,Qequal_rule_context))
	    temp_1 = equal_rule_context(key,entry_key);
	else if (EQ(key_comparitor,Qeq))
	    temp_1 = EQ(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	if (temp_1) {
	    alist_entry_qm = M_CAR(entry_cons);
	    goto end_1;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	alist_entry_qm = Qnil;
      end_1:;
	if (alist_entry_qm) {
	    if (mutate_old_entry_qm) {
		if (mutator_function_qm)
		    inline_funcall_3(mutator_function_qm,alist_entry_qm,
			    key,entry);
		else
		    M_CDR(alist_entry_qm) = entry;
	    }
	    else
		entry = M_CDR(alist_entry_qm);
	}
	else {
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
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_lookup_cons_pool();
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
	    M_CAR(gensymed_symbol_1) = key;
	    M_CDR(gensymed_symbol_1) = entry;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol) = alist;
	    inline_note_allocate_cons(gensymed_symbol,Qlookup);
	    SVREF(insertion_point,FIX((SI_Long)3L)) = gensymed_symbol;
	}
	return VALUES_1(entry);
    }
    goto next_loop;
  end_loop:;
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
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
    M_CAR(gensymed_symbol_1) = key;
    M_CDR(gensymed_symbol_1) = entry;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    new_node = make_binary_tree_element_1(FIX(key_hash),Nil,Nil,
	    gensymed_symbol,FIX((SI_Long)0L));
    depth_of_insertion_parent = insertion_depth - (SI_Long)1L;
    heavy_ancestor = ISVREF(Binary_tree_ancestor,heavy_ancestor_depth);
    if (EQ(ISVREF(Binary_tree_branch,depth_of_insertion_parent),Kless_than)) {
	temp = ISVREF(Binary_tree_ancestor,depth_of_insertion_parent);
	SVREF(temp,FIX((SI_Long)1L)) = new_node;
    }
    else {
	temp = ISVREF(Binary_tree_ancestor,depth_of_insertion_parent);
	SVREF(temp,FIX((SI_Long)2L)) = new_node;
    }
    adjust_point = heavy_ancestor_depth + (SI_Long)1L;
    ab_loop_bind_ = depth_of_insertion_parent;
    if (EQ(ISVREF(Binary_tree_branch,heavy_ancestor_depth),Kless_than)) {
	temp = FIXNUM_ADD1(ISVREF(heavy_ancestor,(SI_Long)4L));
	SVREF(heavy_ancestor,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = FIXNUM_SUB1(ISVREF(heavy_ancestor,(SI_Long)4L));
	SVREF(heavy_ancestor,FIX((SI_Long)4L)) = temp;
    }
  next_loop_2:
    if (adjust_point > ab_loop_bind_)
	goto end_loop_2;
    temp = ISVREF(Binary_tree_ancestor,adjust_point);
    svref_new_value_1 = EQ(ISVREF(Binary_tree_branch,adjust_point),
	    Kless_than) ? (SI_Long)1L : (SI_Long)-1L;
    ISVREF(temp,(SI_Long)4L) = FIX(svref_new_value_1);
    adjust_point = adjust_point + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    balance = ISVREF(heavy_ancestor,(SI_Long)4L);
    if (IFIX(balance) > (SI_Long)1L || IFIX(balance) < (SI_Long)-1L)
	rebalance_tree(binary_tree,heavy_ancestor_depth == (SI_Long)0L ? 
		Nil : ISVREF(Binary_tree_ancestor,heavy_ancestor_depth - 
		(SI_Long)1L),heavy_ancestor);
    return VALUES_1(entry);
}

/* REBALANCE-TREE */
Object rebalance_tree(binary_tree,heavy_parent,heavy_ancestor)
    Object binary_tree, heavy_parent, heavy_ancestor;
{
    Object heavy_child, svref_new_value, heavy_grandchild;
    Object greater_than_heavy_great_grandchild;
    Object less_than_heavy_great_grandchild;
    SI_Long imbalance_direction, heavy_child_balance_factor, depth_change;

    x_note_fn_call(24,74);
    imbalance_direction = IFIX(ISVREF(heavy_ancestor,(SI_Long)4L));
    heavy_child = imbalance_direction == (SI_Long)2L ? 
	    ISVREF(heavy_ancestor,(SI_Long)1L) : ISVREF(heavy_ancestor,
	    (SI_Long)2L);
    heavy_child_balance_factor = IFIX(ISVREF(heavy_child,(SI_Long)4L));
    depth_change = (SI_Long)0L;
    if (imbalance_direction == (SI_Long)2L) {
	if (heavy_child_balance_factor == (SI_Long)1L) {
	    svref_new_value = ISVREF(heavy_child,(SI_Long)2L);
	    SVREF(heavy_ancestor,FIX((SI_Long)1L)) = svref_new_value;
	    SVREF(heavy_child,FIX((SI_Long)2L)) = heavy_ancestor;
	    ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
	    ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    depth_change = (SI_Long)-1L;
	}
	else if (heavy_child_balance_factor == (SI_Long)0L) {
	    svref_new_value = ISVREF(heavy_child,(SI_Long)2L);
	    SVREF(heavy_ancestor,FIX((SI_Long)1L)) = svref_new_value;
	    SVREF(heavy_child,FIX((SI_Long)2L)) = heavy_ancestor;
	    ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)1L);
	    ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)-1L);
	    depth_change = (SI_Long)0L;
	}
	else {
	    heavy_grandchild = ISVREF(heavy_child,(SI_Long)2L);
	    greater_than_heavy_great_grandchild = ISVREF(heavy_grandchild,
		    (SI_Long)2L);
	    less_than_heavy_great_grandchild = ISVREF(heavy_grandchild,
		    (SI_Long)1L);
	    SVREF(heavy_child,FIX((SI_Long)2L)) = 
		    less_than_heavy_great_grandchild;
	    SVREF(heavy_ancestor,FIX((SI_Long)1L)) = 
		    greater_than_heavy_great_grandchild;
	    SVREF(heavy_grandchild,FIX((SI_Long)1L)) = heavy_child;
	    SVREF(heavy_grandchild,FIX((SI_Long)2L)) = heavy_ancestor;
	    if (IFIX(ISVREF(heavy_grandchild,(SI_Long)4L)) == (SI_Long)1L) {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)-1L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    }
	    else if (IFIX(ISVREF(heavy_grandchild,(SI_Long)4L)) == 
		    (SI_Long)-1L) {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)1L);
	    }
	    else {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    }
	    ISVREF(heavy_grandchild,(SI_Long)4L) = FIX((SI_Long)0L);
	    depth_change = (SI_Long)-1L;
	    heavy_child = heavy_grandchild;
	}
    }
    else if (imbalance_direction == (SI_Long)-2L) {
	if (heavy_child_balance_factor == (SI_Long)-1L) {
	    svref_new_value = ISVREF(heavy_child,(SI_Long)1L);
	    SVREF(heavy_ancestor,FIX((SI_Long)2L)) = svref_new_value;
	    SVREF(heavy_child,FIX((SI_Long)1L)) = heavy_ancestor;
	    ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
	    ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    depth_change = (SI_Long)-1L;
	}
	else if (heavy_child_balance_factor == (SI_Long)0L) {
	    svref_new_value = ISVREF(heavy_child,(SI_Long)1L);
	    SVREF(heavy_ancestor,FIX((SI_Long)2L)) = svref_new_value;
	    SVREF(heavy_child,FIX((SI_Long)1L)) = heavy_ancestor;
	    ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)-1L);
	    ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)1L);
	    depth_change = (SI_Long)0L;
	}
	else {
	    heavy_grandchild = ISVREF(heavy_child,(SI_Long)1L);
	    less_than_heavy_great_grandchild = ISVREF(heavy_grandchild,
		    (SI_Long)1L);
	    greater_than_heavy_great_grandchild = ISVREF(heavy_grandchild,
		    (SI_Long)2L);
	    SVREF(heavy_child,FIX((SI_Long)1L)) = 
		    greater_than_heavy_great_grandchild;
	    SVREF(heavy_ancestor,FIX((SI_Long)2L)) = 
		    less_than_heavy_great_grandchild;
	    SVREF(heavy_grandchild,FIX((SI_Long)2L)) = heavy_child;
	    SVREF(heavy_grandchild,FIX((SI_Long)1L)) = heavy_ancestor;
	    if (IFIX(ISVREF(heavy_grandchild,(SI_Long)4L)) == (SI_Long)-1L) {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)1L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    }
	    else if (IFIX(ISVREF(heavy_grandchild,(SI_Long)4L)) == 
			(SI_Long)1L) {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)-1L);
	    }
	    else {
		ISVREF(heavy_ancestor,(SI_Long)4L) = FIX((SI_Long)0L);
		ISVREF(heavy_child,(SI_Long)4L) = FIX((SI_Long)0L);
	    }
	    ISVREF(heavy_grandchild,(SI_Long)4L) = FIX((SI_Long)0L);
	    depth_change = (SI_Long)-1L;
	    heavy_child = heavy_grandchild;
	}
    }
    else
	return VALUES_1(FIX((SI_Long)0L));
    if ( !TRUEP(heavy_parent))
	M_CDR(binary_tree) = heavy_child;
    else if (EQ(ISVREF(heavy_parent,(SI_Long)1L),heavy_ancestor))
	SVREF(heavy_parent,FIX((SI_Long)1L)) = heavy_child;
    else
	SVREF(heavy_parent,FIX((SI_Long)2L)) = heavy_child;
    return VALUES_1(FIX(depth_change));
}

/* DELETE-BALANCED-BINARY-TREE-ENTRY */
Object delete_balanced_binary_tree_entry(comparitor,key,binary_tree,
	    key_hash_init)
    Object comparitor, key, binary_tree, key_hash_init;
{
    Object deletion_point, old_key, old_entry, temp, alist, parent_cons;
    Object entry_cons, entry_cons_qm, parent_cons_qm, old_alist_cons;
    Object svref_arg_2, less_branch, greater_branch, branch_to_promote;
    Object successor_parent, successor_node, successor_less_branch;
    Object depth_reduced_qm, ancestor, temp_1;
    SI_Long key_hash, deletion_depth, deletion_point_hash, rebalance_depth;
    SI_Long deletion_parent_depth, balance, rebalance_point;
    Object result;

    x_note_fn_call(24,75);
    key_hash = IFIX(key_hash_init);
    deletion_point = CDR(binary_tree);
    deletion_depth = (SI_Long)0L;
    old_key = Nil;
    old_entry = Nil;
    if ( !TRUEP(deletion_point))
	return VALUES_2(Nil,Nil);
    deletion_point_hash = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(deletion_point))
	goto end_loop;
    deletion_point_hash = IFIX(ISVREF(deletion_point,(SI_Long)0L));
    if (key_hash < deletion_point_hash) {
	temp = Binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = deletion_point;
	temp = Binary_tree_branch;
	ISVREF(temp,deletion_depth) = Kless_than;
	deletion_depth = deletion_depth + (SI_Long)1L;
	deletion_point = ISVREF(deletion_point,(SI_Long)1L);
    }
    else if (key_hash > deletion_point_hash) {
	temp = Binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = deletion_point;
	temp = Binary_tree_branch;
	ISVREF(temp,deletion_depth) = Kgreater_than;
	deletion_depth = deletion_depth + (SI_Long)1L;
	deletion_point = ISVREF(deletion_point,(SI_Long)2L);
    }
    else {
	alist = ISVREF(deletion_point,(SI_Long)3L);
	if ( !TRUEP(alist) || FUNCALL_2(comparitor,key,CAAR(alist)))
	    result = VALUES_2(alist,Nil);
	else {
	    parent_cons = alist;
	    entry_cons = CDR(alist);
	  next_loop_1:
	    if ( !TRUEP(entry_cons))
		goto end_loop_1;
	    if (FUNCALL_2(comparitor,key,CAAR(entry_cons))) {
		result = VALUES_2(entry_cons,parent_cons);
		goto end_1;
	    }
	    parent_cons = entry_cons;
	    entry_cons = CDR(entry_cons);
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_2(Nil,Nil);
	    goto end_1;
	    result = VALUES_1(Qnil);
	  end_1:;
	}
	MVS_2(result,entry_cons_qm,parent_cons_qm);
	if ( !TRUEP(entry_cons_qm))
	    deletion_point = Nil;
	else {
	    old_alist_cons = M_CAR(entry_cons_qm);
	    old_key = M_CAR(old_alist_cons);
	    old_entry = M_CDR(old_alist_cons);
	    if (parent_cons_qm) {
		temp = M_CDR(entry_cons_qm);
		M_CDR(parent_cons_qm) = temp;
		deletion_point = Nil;
	    }
	    else if (M_CDR(entry_cons_qm)) {
		temp = M_CDR(entry_cons_qm);
		SVREF(deletion_point,FIX((SI_Long)3L)) = temp;
		deletion_point = Nil;
	    }
	    inline_note_reclaim_cons(old_alist_cons,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = old_alist_cons;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old_alist_cons;
	    }
	    else {
		temp = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old_alist_cons;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old_alist_cons;
	    }
	    M_CDR(old_alist_cons) = Nil;
	    inline_note_reclaim_cons(entry_cons_qm,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = entry_cons_qm;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = entry_cons_qm;
	    }
	    else {
		temp = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = entry_cons_qm;
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = entry_cons_qm;
	    }
	    M_CDR(entry_cons_qm) = Nil;
	}
	goto end_2;
    }
    goto next_loop;
  end_loop:
  end_2:;
    if ( !TRUEP(deletion_point))
	return VALUES_2(old_key,old_entry);
    less_branch = ISVREF(deletion_point,(SI_Long)1L);
    greater_branch = ISVREF(deletion_point,(SI_Long)2L);
    rebalance_depth = deletion_depth;
    deletion_parent_depth = deletion_depth - (SI_Long)1L;
    if ( !TRUEP(less_branch))
	branch_to_promote = greater_branch;
    else if ( !TRUEP(greater_branch))
	branch_to_promote = less_branch;
    else if ( !TRUEP(ISVREF(greater_branch,(SI_Long)1L))) {
	SVREF(greater_branch,FIX((SI_Long)1L)) = less_branch;
	temp = ISVREF(deletion_point,(SI_Long)4L);
	SVREF(greater_branch,FIX((SI_Long)4L)) = temp;
	temp = Binary_tree_ancestor;
	ISVREF(temp,rebalance_depth) = greater_branch;
	temp = Binary_tree_branch;
	ISVREF(temp,rebalance_depth) = Kgreater_than;
	rebalance_depth = rebalance_depth + (SI_Long)1L;
	branch_to_promote = greater_branch;
    }
    else {
	successor_parent = greater_branch;
	successor_node = ISVREF(greater_branch,(SI_Long)1L);
	successor_less_branch = Nil;
      next_loop_2:
	successor_less_branch = ISVREF(successor_node,(SI_Long)1L);
	rebalance_depth = rebalance_depth + (SI_Long)1L;
	temp = Binary_tree_ancestor;
	ISVREF(temp,rebalance_depth) = successor_parent;
	temp = Binary_tree_branch;
	ISVREF(temp,rebalance_depth) = Kless_than;
	if ( !TRUEP(successor_less_branch))
	    goto end_loop_2;
	successor_parent = successor_node;
	successor_node = successor_less_branch;
	goto next_loop_2;
      end_loop_2:
	temp = ISVREF(successor_node,(SI_Long)2L);
	SVREF(successor_parent,FIX((SI_Long)1L)) = temp;
	SVREF(successor_node,FIX((SI_Long)1L)) = less_branch;
	SVREF(successor_node,FIX((SI_Long)2L)) = greater_branch;
	temp = ISVREF(deletion_point,(SI_Long)4L);
	SVREF(successor_node,FIX((SI_Long)4L)) = temp;
	temp = Binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = successor_node;
	temp = Binary_tree_branch;
	ISVREF(temp,deletion_depth) = Kgreater_than;
	rebalance_depth = rebalance_depth + (SI_Long)1L;
	branch_to_promote = successor_node;
	goto end_3;
	branch_to_promote = Qnil;
      end_3:;
    }
    reclaim_binary_tree_element_1(deletion_point);
    if (deletion_parent_depth == (SI_Long)-1L)
	M_CDR(binary_tree) = branch_to_promote;
    else if (EQ(ISVREF(Binary_tree_branch,deletion_parent_depth),Kless_than)) {
	temp = ISVREF(Binary_tree_ancestor,deletion_parent_depth);
	SVREF(temp,FIX((SI_Long)1L)) = branch_to_promote;
    }
    else {
	temp = ISVREF(Binary_tree_ancestor,deletion_parent_depth);
	SVREF(temp,FIX((SI_Long)2L)) = branch_to_promote;
    }
    depth_reduced_qm = T;
    balance = (SI_Long)0L;
    rebalance_point = rebalance_depth - (SI_Long)1L;
    ancestor = Nil;
  next_loop_3:
    if (rebalance_point < (SI_Long)0L)
	goto end_loop_3;
    if ( !TRUEP(depth_reduced_qm))
	goto end_loop_3;
    ancestor = ISVREF(Binary_tree_ancestor,rebalance_point);
    temp_1 = ISVREF(Binary_tree_branch,rebalance_point);
    if (EQ(temp_1,Kless_than)) {
	temp = FIXNUM_SUB1(ISVREF(ancestor,(SI_Long)4L));
	balance = IFIX(SVREF(ancestor,FIX((SI_Long)4L)) = temp);
	if (balance == (SI_Long)-1L)
	    depth_reduced_qm = Nil;
	else if (balance == (SI_Long)-2L) {
	    if (IFIX(rebalance_tree(binary_tree,rebalance_point != 
		    (SI_Long)0L ? ISVREF(Binary_tree_ancestor,
		    rebalance_point - (SI_Long)1L) : Nil,ancestor)) == 
		    (SI_Long)0L)
		depth_reduced_qm = Nil;
	}
    }
    else if (EQ(temp_1,Kgreater_than)) {
	temp = FIXNUM_ADD1(ISVREF(ancestor,(SI_Long)4L));
	balance = IFIX(SVREF(ancestor,FIX((SI_Long)4L)) = temp);
	if (balance == (SI_Long)1L)
	    depth_reduced_qm = Nil;
	else if (balance == (SI_Long)2L) {
	    if (IFIX(rebalance_tree(binary_tree,rebalance_point != 
		    (SI_Long)0L ? ISVREF(Binary_tree_ancestor,
		    rebalance_point - (SI_Long)1L) : Nil,ancestor)) == 
		    (SI_Long)0L)
		depth_reduced_qm = Nil;
	}
    }
    rebalance_point = rebalance_point - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    return VALUES_2(old_key,old_entry);
}

Object The_type_description_of_skip_list_element = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_skip_list_elements, Qchain_of_available_skip_list_elements);

DEFINE_VARIABLE_WITH_SYMBOL(Skip_list_element_count, Qskip_list_element_count);

Object Chain_of_available_skip_list_elements_vector = UNBOUND;

/* SKIP-LIST-ELEMENT-STRUCTURE-MEMORY-USAGE */
Object skip_list_element_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,76);
    temp = Skip_list_element_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SKIP-LIST-ELEMENT-COUNT */
Object outstanding_skip_list_element_count()
{
    Object def_structure_skip_list_element_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,77);
    gensymed_symbol = IFIX(Skip_list_element_count);
    def_structure_skip_list_element_variable = 
	    Chain_of_available_skip_list_elements;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_skip_list_element_variable))
	goto end_loop;
    def_structure_skip_list_element_variable = 
	    ISVREF(def_structure_skip_list_element_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SKIP-LIST-ELEMENT-INTERNAL-1 */
Object reclaim_skip_list_element_internal_1(skip_list_element)
    Object skip_list_element;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,78);
    inline_note_reclaim_cons(skip_list_element,Nil);
    temp = ISVREF(Chain_of_available_skip_list_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(skip_list_element,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_skip_list_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = skip_list_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SKIP-LIST-ELEMENT */
Object reclaim_structure_for_skip_list_element(skip_list_element)
    Object skip_list_element;
{
    x_note_fn_call(24,79);
    return reclaim_skip_list_element_internal_1(skip_list_element);
}

/* MAKE-PERMANENT-SKIP-LIST-ELEMENT-STRUCTURE-INTERNAL */
Object make_permanent_skip_list_element_structure_internal()
{
    Object def_structure_skip_list_element_variable, the_array;
    Object defstruct_g2_skip_list_element_variable, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,80);
    def_structure_skip_list_element_variable = Nil;
    atomic_incff_symval(Qskip_list_element_count,FIX((SI_Long)100L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)5L;
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
	defstruct_g2_skip_list_element_variable = the_array;
	def_structure_skip_list_element_variable = 
		defstruct_g2_skip_list_element_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_skip_list_elements_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)0L)) = 
		temp;
	temp = Chain_of_available_skip_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_skip_list_element_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_skip_list_element_variable);
}

/* MAKE-SKIP-LIST-ELEMENT-1 */
Object make_skip_list_element_1(skip_list_element_hash_number,
	    skip_list_element_key,skip_list_element_entry,
	    skip_list_element_top_level)
    Object skip_list_element_hash_number, skip_list_element_key;
    Object skip_list_element_entry, skip_list_element_top_level;
{
    Object def_structure_skip_list_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,81);
    def_structure_skip_list_element_variable = 
	    ISVREF(Chain_of_available_skip_list_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_skip_list_element_variable) {
	svref_arg_1 = Chain_of_available_skip_list_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_skip_list_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_skip_list_element_variable = 
		make_permanent_skip_list_element_structure_internal();
    inline_note_allocate_cons(def_structure_skip_list_element_variable,Nil);
    SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)1L)) = 
	    skip_list_element_hash_number;
    SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)2L)) = 
	    skip_list_element_key;
    SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)3L)) = 
	    skip_list_element_entry;
    SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)4L)) = 
	    skip_list_element_top_level;
    return VALUES_1(def_structure_skip_list_element_variable);
}

/* RECLAIM-SKIP-LIST-ELEMENT */
Object reclaim_skip_list_element(element)
    Object element;
{
    Object temp;

    x_note_fn_call(24,82);
    reclaim_managed_simple_vector_for_skip_list(ISVREF(element,(SI_Long)0L));
    SVREF(element,FIX((SI_Long)0L)) = Nil;
    temp = reclaim_skip_list_element_internal_1(element);
    return VALUES_1(temp);
}

/* FLATTEN-SKIP-LIST */
Object flatten_skip_list(skip_list)
    Object skip_list;
{
    Object gensymed_symbol, head, tail, node, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(24,83);
    gensymed_symbol = skip_list;
    head = CAR(gensymed_symbol);
    tail = CDR(gensymed_symbol);
    node = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),(SI_Long)0L));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (EQ(node,tail))
	goto end_loop;
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(ISVREF(node,(SI_Long)2L),
	    ISVREF(node,(SI_Long)3L)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    node = ATOMIC_REF_OBJECT(ISVREF(ISVREF(node,(SI_Long)0L),(SI_Long)0L));
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* LOOKUP-SKIP-LIST-ENTRY */
Object lookup_skip_list_entry(skip_list_element,max_level_init,
	    key_comparitor,key,key_hash_init)
    Object skip_list_element, max_level_init, key_comparitor, key;
    Object key_hash_init;
{
    Object marked, pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object entry_key;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(24,84);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list_element);
    curr = Nil;
    succ = Nil;
    level = max_level;
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
    temp_2 = IFIX(entry_hash) < key_hash;
    if (temp_2);
    else if (IFIX(entry_hash) == key_hash) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qequal_rule_context))
	    temp_1 = equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp_2 =  !TRUEP(temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
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
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qequal_rule_context))
	    temp_1 = equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp_1 = temp_1 ? ISVREF(curr,(SI_Long)3L) : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

Object Half_of_most_positive_fixnum = UNBOUND;

/* RANDOM-LEVEL */
Object random_level(max_level_init)
    Object max_level_init;
{
    Object level, temp;
    SI_Long max_level;

    x_note_fn_call(24,85);
    max_level = IFIX(max_level_init);
    level = FIX((SI_Long)0L);
  next_loop:
    if ( !((SI_Long)2L * IFIX(g2_random(Half_of_most_positive_fixnum)) < 
	    IFIX(Half_of_most_positive_fixnum) && IFIX(level) < max_level))
	goto end_loop;
    level = FIXNUM_ADD1(level);
    goto next_loop;
  end_loop:
    temp = level;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Skip_list_find_preds, Qskip_list_find_preds);

DEFINE_VARIABLE_WITH_SYMBOL(Skip_list_find_succs, Qskip_list_find_succs);

/* SKIP-LIST-FIND */
Object skip_list_find(skip_list,max_level,key_comparitor,key,hash,preds,succs)
    Object skip_list, max_level, key_comparitor, key, hash, preds, succs;
{
    Object marked, snip, pred, curr, succ, next, reference, temp, temp_1;
    Object entry_hash, entry_key;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp_3;
    int temp_2;
    Object result;

    x_note_fn_call(24,86);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    snip = Nil;
    pred = Nil;
    curr = Nil;
    succ = Nil;
  retry:
  next_loop:
    pred = skip_list;
    level = IFIX(max_level);
    ab_loop_bind_ = bottom_level;
  next_loop_1:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next = Nil;
  next_loop_2:
    next = ISVREF(curr,(SI_Long)0L);
    reference = ISVREF(next,level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_3:
    if ( !TRUEP(marked))
	goto end_loop_1;
    temp = ISVREF(pred,(SI_Long)0L);
    temp_2 = level;
    temp_1 = MAKE_ATOMIC_REF(curr,(SI_Long)0L);
    snip = CAS_SVREF(temp,temp_2,temp_1,MAKE_ATOMIC_REF(succ,(SI_Long)0L));
    if ( !TRUEP(snip))
	goto retry;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_3;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    temp_3 = FIXNUM_LT(entry_hash,hash);
    if (temp_3);
    else if (FIXNUM_EQ(entry_hash,hash)) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qequal_rule_context))
	    temp_1 = equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp_3 =  !TRUEP(temp_1);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_1;
    goto next_loop_2;
  end_loop_2:
  end_1:;
    ISVREF(preds,level) = pred;
    ISVREF(succs,level) = curr;
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    if (FIXNUM_EQ(ISVREF(curr,(SI_Long)1L),hash)) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_3 = EQUAL(key,entry_key);
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_3 = TRUEP(string_eq(2,key,entry_key));
	else if (EQ(key_comparitor,Qequal_rule_context))
	    temp_3 = TRUEP(equal_rule_context(key,entry_key));
	else
	    temp_3 = TRUEP(FUNCALL_2(key_comparitor,key,entry_key));
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3)
	return VALUES_1(curr);
    else
	return VALUES_1(Nil);
    goto next_loop;
  end_loop_3:;
    return VALUES_1(Qnil);
}

/* SET-SKIP-LIST-ENTRY */
Object set_skip_list_entry(skip_list,max_level_init,key_comparitor,
	    mutator_function_qm,mutate_old_entry_qm,key,key_hash_init,entry)
    Object skip_list, max_level_init, key_comparitor, mutator_function_qm;
    Object mutate_old_entry_qm, key, key_hash_init, entry;
{
    Object head, preds, succs, insertion_point, pred, top_level, node, next;
    Object new_node, svref_arg_1, svref_new_value, succ, temp, temp_1;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;
    int temp_2;

    x_note_fn_call(24,87);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    head = M_CAR(M_CDR(skip_list));
    preds = Skip_list_find_preds;
    succs = Skip_list_find_succs;
    insertion_point = Nil;
  next_loop:
    insertion_point = skip_list_find(head,FIX(max_level),key_comparitor,
	    key,FIX(key_hash),preds,succs);
    if (insertion_point) {
	if (mutate_old_entry_qm) {
	    if (mutator_function_qm)
		inline_funcall_3(mutator_function_qm,insertion_point,key,
			entry);
	    else {
		SVREF(insertion_point,FIX((SI_Long)2L)) = key;
		SVREF(insertion_point,FIX((SI_Long)3L)) = entry;
	    }
	}
	else
	    entry = ISVREF(insertion_point,(SI_Long)3L);
	return VALUES_1(entry);
    }
    pred = ISVREF(preds,bottom_level);
    top_level = IFIX(ISVREF(pred,(SI_Long)1L)) == key_hash ? ISVREF(pred,
	    (SI_Long)4L) : random_level(FIX(max_level));
    node = make_skip_list_element_1(FIX(key_hash),key,entry,top_level);
    next = 
	    allocate_managed_simple_vector_for_skip_list(FIXNUM_ADD1(top_level));
    SVREF(node,FIX((SI_Long)0L)) = next;
    new_node = node;
    level = bottom_level;
    ab_loop_bind_ = IFIX(top_level);
  next_loop_1:
    if (level > ab_loop_bind_)
	goto end_loop;
    svref_arg_1 = ISVREF(new_node,(SI_Long)0L);
    svref_new_value = MAKE_ATOMIC_REF(ISVREF(succs,level),(SI_Long)0L);
    ISVREF(svref_arg_1,level) = svref_new_value;
    level = level + (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    succ = ISVREF(succs,bottom_level);
    temp = ISVREF(pred,(SI_Long)0L);
    temp_1 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
    if (CAS_SVREF(temp,bottom_level,temp_1,MAKE_ATOMIC_REF(new_node,
	    (SI_Long)0L))) {
	level = bottom_level + (SI_Long)1L;
	ab_loop_bind_ = IFIX(top_level);
      next_loop_2:
	if (level > ab_loop_bind_)
	    goto end_loop_1;
      next_loop_3:
	pred = ISVREF(preds,level);
	succ = ISVREF(succs,level);
	temp = ISVREF(pred,(SI_Long)0L);
	temp_2 = level;
	temp_1 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
	if (CAS_SVREF(temp,temp_2,temp_1,MAKE_ATOMIC_REF(new_node,
		(SI_Long)0L)))
	    goto end_1;
	skip_list_find(head,FIX(max_level),key_comparitor,key,
		FIX(key_hash),preds,succs);
	goto next_loop_3;
      end_loop_2:
      end_1:
	level = level + (SI_Long)1L;
	goto next_loop_2;
      end_loop_1:;
	return VALUES_1(entry);
    }
    else
	reclaim_skip_list_element(new_node);
    goto next_loop;
  end_loop_3:;
    return VALUES_1(Qnil);
}

/* DELETE-SKIP-LIST-ENTRY */
Object delete_skip_list_entry(comparitor,key,skip_list,max_level_init,
	    key_hash_init)
    Object comparitor, key, skip_list, max_level_init, key_hash_init;
{
    Object head, preds, succs, deletion_point, node_to_remove, old_key;
    Object old_entry, succ, marked, reference, temp, temp_1, i_marked_it;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;
    int temp_2;
    Object result;

    x_note_fn_call(24,88);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    head = M_CAR(M_CDR(skip_list));
    preds = Skip_list_find_preds;
    succs = Skip_list_find_succs;
    deletion_point = Nil;
  next_loop:
    deletion_point = skip_list_find(head,FIX(max_level),comparitor,key,
	    FIX(key_hash),preds,succs);
    if ( !TRUEP(deletion_point))
	return VALUES_2(Nil,Nil);
    node_to_remove = ISVREF(succs,bottom_level);
    old_key = ISVREF(deletion_point,(SI_Long)2L);
    old_entry = ISVREF(deletion_point,(SI_Long)3L);
    succ = Nil;
    marked = Nil;
    level = IFIX(ISVREF(node_to_remove,(SI_Long)4L));
    ab_loop_bind_ = bottom_level + (SI_Long)1L;
  next_loop_1:
    if (level < ab_loop_bind_)
	goto end_loop;
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( ! !TRUEP(marked))
	goto end_loop_1;
    temp_1 = ISVREF(node_to_remove,(SI_Long)0L);
    temp_2 = level;
    temp = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
    CAS_SVREF(temp_1,temp_2,temp,MAKE_ATOMIC_REF(succ,(SI_Long)355L));
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),bottom_level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    i_marked_it = Nil;
  next_loop_3:
    temp = ISVREF(node_to_remove,(SI_Long)0L);
    temp_1 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
    i_marked_it = CAS_SVREF(temp,bottom_level,temp_1,MAKE_ATOMIC_REF(succ,
	    (SI_Long)355L));
    reference = ISVREF(ISVREF(ISVREF(succs,bottom_level),(SI_Long)0L),
	    bottom_level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    if (i_marked_it) {
	skip_list_find(head,FIX(max_level),comparitor,key,FIX(key_hash),
		preds,succs);
	return VALUES_2(old_key,old_entry);
    }
    else if (marked)
	return VALUES_2(old_key,old_entry);
    goto next_loop_3;
  end_loop_2:;
    goto next_loop;
  end_loop_3:
    return VALUES_1(Qnil);
}

Object The_type_description_of_sparse_array = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_sparse_arrays, Qchain_of_available_sparse_arrays);

DEFINE_VARIABLE_WITH_SYMBOL(Sparse_array_count, Qsparse_array_count);

Object Chain_of_available_sparse_arrays_vector = UNBOUND;

/* SPARSE-ARRAY-STRUCTURE-MEMORY-USAGE */
Object sparse_array_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,89);
    temp = Sparse_array_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SPARSE-ARRAY-COUNT */
Object outstanding_sparse_array_count()
{
    Object def_structure_sparse_array_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,90);
    gensymed_symbol = IFIX(Sparse_array_count);
    def_structure_sparse_array_variable = Chain_of_available_sparse_arrays;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_sparse_array_variable))
	goto end_loop;
    def_structure_sparse_array_variable = 
	    ISVREF(def_structure_sparse_array_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SPARSE-ARRAY-1-1 */
Object reclaim_sparse_array_1_1(sparse_array)
    Object sparse_array;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,91);
    inline_note_reclaim_cons(sparse_array,Nil);
    temp = ISVREF(Chain_of_available_sparse_arrays_vector,
	    IFIX(Current_thread_index));
    SVREF(sparse_array,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_sparse_arrays_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = sparse_array;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SPARSE-ARRAY */
Object reclaim_structure_for_sparse_array(sparse_array)
    Object sparse_array;
{
    x_note_fn_call(24,92);
    return reclaim_sparse_array_1_1(sparse_array);
}

static Object Qg2_defstruct_structure_name_sparse_array_g2_struct;  /* g2-defstruct-structure-name::sparse-array-g2-struct */

/* MAKE-PERMANENT-SPARSE-ARRAY-STRUCTURE-INTERNAL */
Object make_permanent_sparse_array_structure_internal()
{
    Object def_structure_sparse_array_variable;
    Object defstruct_g2_sparse_array_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,93);
    def_structure_sparse_array_variable = Nil;
    atomic_incff_symval(Qsparse_array_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_sparse_array_variable = Nil;
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
	defstruct_g2_sparse_array_variable = the_array;
	SVREF(defstruct_g2_sparse_array_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sparse_array_g2_struct;
	def_structure_sparse_array_variable = 
		defstruct_g2_sparse_array_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_sparse_array_variable);
}

/* ALLOCATE-SPARSE-ARRAY-1 */
Object allocate_sparse_array_1()
{
    Object def_structure_sparse_array_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,94);
    def_structure_sparse_array_variable = 
	    ISVREF(Chain_of_available_sparse_arrays_vector,
	    IFIX(Current_thread_index));
    if (def_structure_sparse_array_variable) {
	svref_arg_1 = Chain_of_available_sparse_arrays_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_sparse_array_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_sparse_array_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_sparse_array_g2_struct;
    }
    else
	def_structure_sparse_array_variable = 
		make_permanent_sparse_array_structure_internal();
    inline_note_allocate_cons(def_structure_sparse_array_variable,Nil);
    ISVREF(def_structure_sparse_array_variable,(SI_Long)1L) = FIX((SI_Long)0L);
    ISVREF(def_structure_sparse_array_variable,(SI_Long)2L) = 
	    FIX((SI_Long)-1L);
    SVREF(def_structure_sparse_array_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_sparse_array_variable);
}

/* RECLAIM-SPARSE-ARRAY */
Object reclaim_sparse_array(sparse_array)
    Object sparse_array;
{
    Object depth;

    x_note_fn_call(24,95);
    depth = ISVREF(sparse_array,(SI_Long)2L);
    if (IFIX(depth) >= (SI_Long)0L)
	reclaim_sparse_array_vectors(ISVREF(sparse_array,(SI_Long)3L),depth);
    reclaim_sparse_array_1_1(sparse_array);
    return VALUES_1(Nil);
}

/* RECLAIM-SPARSE-ARRAY-VECTORS */
Object reclaim_sparse_array_vectors(vector_1,depth)
    Object vector_1, depth;
{
    Object subdepth, subvector_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(24,96);
    if (IFIX(depth) > (SI_Long)0L) {
	subdepth = FIXNUM_SUB1(depth);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)32L;
	subvector_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	subvector_qm = ISVREF(vector_1,index_1);
	if (subvector_qm)
	    reclaim_sparse_array_vectors(subvector_qm,subdepth);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    reclaim_managed_simple_vector(vector_1);
    return VALUES_1(Nil);
}

/* AREF-SPARSE-ARRAY */
Object aref_sparse_array(sparse_array,index_init)
    Object sparse_array, index_init;
{
    Object buffer, temp;
    SI_Long index_1, base, depth, shift_amount;

    x_note_fn_call(24,97);
    index_1 = IFIX(index_init);
    base = index_1 - IFIX(ISVREF(sparse_array,(SI_Long)1L));
    depth = IFIX(ISVREF(sparse_array,(SI_Long)2L));
    shift_amount = depth * IFIX(Sparse_array_layer_order);
    if (depth >= (SI_Long)0L && base >= (SI_Long)0L && (depth == 
	    IFIX(Sparse_array_max_depth) || base < (SI_Long)1L << 
	    shift_amount + IFIX(Sparse_array_layer_order))) {
	buffer = ISVREF(sparse_array,(SI_Long)3L);
      next_loop:
	if ( !TRUEP(buffer))
	    goto end_loop;
	if (shift_amount == (SI_Long)0L) {
	    temp = ISVREF(buffer,base);
	    goto end_1;
	}
	else {
	    buffer = ISVREF(buffer,base >>  -  - shift_amount);
	    base = base & ((SI_Long)1L << shift_amount) - (SI_Long)1L;
	    shift_amount = shift_amount - IFIX(Sparse_array_layer_order);
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* ASET-SPARSE-ARRAY */
Object aset_sparse_array(sparse_array,index_init,value)
    Object sparse_array, index_init, value;
{
    Object new_buffer, svref_new_value, buffer, next_buffer_qm;
    SI_Long index_1, lowest_index, current_depth, shift_amount, buffer_length;
    SI_Long buffer_mask, init_index, ab_loop_bind_, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, buffer_index;

    x_note_fn_call(24,98);
    index_1 = IFIX(index_init);
    lowest_index = IFIX(ISVREF(sparse_array,(SI_Long)1L));
    current_depth = IFIX(ISVREF(sparse_array,(SI_Long)2L));
    shift_amount = current_depth * IFIX(Sparse_array_layer_order);
    buffer_length = (SI_Long)32L;
    buffer_mask = buffer_length - (SI_Long)1L;
    new_buffer = Nil;
  next_loop:
    if ( !(index_1 < lowest_index || current_depth < 
	    IFIX(Sparse_array_max_depth) && index_1 >= lowest_index + 
	    ((SI_Long)1L << shift_amount + IFIX(Sparse_array_layer_order))))
	goto end_loop;
    new_buffer = allocate_managed_simple_vector(FIX(buffer_length));
    init_index = (SI_Long)0L;
    ab_loop_bind_ = buffer_length;
  next_loop_1:
    if (init_index >= ab_loop_bind_)
	goto end_loop_1;
    ISVREF(new_buffer,init_index) = Nil;
    init_index = init_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    if (current_depth == (SI_Long)-1L) {
	current_depth = (SI_Long)0L;
	shift_amount = (SI_Long)0L;
	lowest_index = index_1 &  - buffer_length;
    }
    else {
	current_depth = current_depth + (SI_Long)1L;
	shift_amount = shift_amount + IFIX(Sparse_array_layer_order);
	svref_arg_2 = lowest_index >>  -  - shift_amount & buffer_mask;
	svref_new_value = ISVREF(sparse_array,(SI_Long)3L);
	ISVREF(new_buffer,svref_arg_2) = svref_new_value;
	gensymed_symbol = lowest_index;
	gensymed_symbol_1 = current_depth == IFIX(Sparse_array_max_depth) ?
		 (SI_Long)-1L :  - ((SI_Long)1L << shift_amount + 
		IFIX(Sparse_array_layer_order));
	lowest_index = gensymed_symbol & gensymed_symbol_1;
    }
    ISVREF(sparse_array,(SI_Long)1L) = FIX(lowest_index);
    ISVREF(sparse_array,(SI_Long)2L) = FIX(current_depth);
    SVREF(sparse_array,FIX((SI_Long)3L)) = new_buffer;
    goto next_loop;
  end_loop:;
    buffer = ISVREF(sparse_array,(SI_Long)3L);
    buffer_index = (SI_Long)0L;
    next_buffer_qm = Nil;
  next_loop_2:
    buffer_index = index_1 >>  -  - shift_amount & buffer_mask;
    if (shift_amount == (SI_Long)0L)
	goto end_loop_2;
    next_buffer_qm = ISVREF(buffer,buffer_index);
    if ( !TRUEP(next_buffer_qm)) {
	next_buffer_qm = allocate_managed_simple_vector(FIX(buffer_length));
	init_index = (SI_Long)0L;
	ab_loop_bind_ = buffer_length;
      next_loop_3:
	if (init_index >= ab_loop_bind_)
	    goto end_loop_3;
	ISVREF(next_buffer_qm,init_index) = Nil;
	init_index = init_index + (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	ISVREF(buffer,buffer_index) = next_buffer_qm;
    }
    shift_amount = shift_amount - IFIX(Sparse_array_layer_order);
    buffer = next_buffer_qm;
    goto next_loop_2;
  end_loop_2:
    ISVREF(buffer,buffer_index) = value;
    return VALUES_1(value);
}

/* COLLECT-LEAF-VECTORS */
Object collect_leaf_vectors(vector_1,depth)
    Object vector_1, depth;
{
    Object temp, element_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object subvector_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(24,99);
    if (IFIX(depth) < (SI_Long)0L)
	temp = Nil;
    else if (IFIX(depth) == (SI_Long)0L)
	temp = scope_cons(vector_1,Nil);
    else if (IFIX(depth) == (SI_Long)1L) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
	element_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	element_qm = ISVREF(vector_1,index_1);
	if (element_qm) {
	    ab_loopvar__2 = scope_cons(element_qm,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1));
	subvector_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	subvector_qm = ISVREF(vector_1,index_1);
	if (subvector_qm) {
	    ab_loopvar__2 = collect_leaf_vectors(subvector_qm,
		    FIXNUM_SUB1(depth));
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

/* MAKE-INDEX-SPACE-VECTOR */
Object make_index_space_vector()
{
    Object new_vector, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_1, index_1, ab_loop_bind_;

    x_note_fn_call(24,100);
    new_vector = allocate_managed_simple_vector(FIX((SI_Long)1024L));
    gensymed_symbol = new_vector;
    gensymed_symbol_1 = (SI_Long)1024L;
    gensymed_symbol_2 = Nil;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = gensymed_symbol_1;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    ISVREF(gensymed_symbol,index_1) = gensymed_symbol_2;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(new_vector);
}

Object The_type_description_of_index_space = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_index_spaces, Qchain_of_available_index_spaces);

DEFINE_VARIABLE_WITH_SYMBOL(Index_space_count, Qindex_space_count);

Object Chain_of_available_index_spaces_vector = UNBOUND;

/* INDEX-SPACE-STRUCTURE-MEMORY-USAGE */
Object index_space_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,101);
    temp = Index_space_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INDEX-SPACE-COUNT */
Object outstanding_index_space_count()
{
    Object def_structure_index_space_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,102);
    gensymed_symbol = IFIX(Index_space_count);
    def_structure_index_space_variable = Chain_of_available_index_spaces;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_index_space_variable))
	goto end_loop;
    def_structure_index_space_variable = 
	    ISVREF(def_structure_index_space_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INDEX-SPACE-1 */
Object reclaim_index_space_1(index_space)
    Object index_space;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(24,103);
    inline_note_reclaim_cons(index_space,Nil);
    structure_being_reclaimed = index_space;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_vector_of_index_subspace_vectors(ISVREF(index_space,
	      (SI_Long)2L));
      SVREF(index_space,FIX((SI_Long)2L)) = Nil;
      reclaim_gensym_list_1(ISVREF(index_space,(SI_Long)5L));
      SVREF(index_space,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_index_spaces_vector,
	    IFIX(Current_thread_index));
    SVREF(index_space,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_index_spaces_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = index_space;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INDEX-SPACE */
Object reclaim_structure_for_index_space(index_space)
    Object index_space;
{
    x_note_fn_call(24,104);
    return reclaim_index_space_1(index_space);
}

static Object Qg2_defstruct_structure_name_index_space_g2_struct;  /* g2-defstruct-structure-name::index-space-g2-struct */

/* MAKE-PERMANENT-INDEX-SPACE-STRUCTURE-INTERNAL */
Object make_permanent_index_space_structure_internal()
{
    Object def_structure_index_space_variable;
    Object defstruct_g2_index_space_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,105);
    def_structure_index_space_variable = Nil;
    atomic_incff_symval(Qindex_space_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_index_space_variable = Nil;
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
	defstruct_g2_index_space_variable = the_array;
	SVREF(defstruct_g2_index_space_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_index_space_g2_struct;
	def_structure_index_space_variable = defstruct_g2_index_space_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_index_space_variable);
}

/* MAKE-INDEX-SPACE-1 */
Object make_index_space_1(index_space_name,index_space_object_reclaimer_qm)
    Object index_space_name, index_space_object_reclaimer_qm;
{
    Object def_structure_index_space_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,106);
    def_structure_index_space_variable = 
	    ISVREF(Chain_of_available_index_spaces_vector,
	    IFIX(Current_thread_index));
    if (def_structure_index_space_variable) {
	temp = Chain_of_available_index_spaces_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_index_space_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_index_space_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_index_space_g2_struct;
    }
    else
	def_structure_index_space_variable = 
		make_permanent_index_space_structure_internal();
    inline_note_allocate_cons(def_structure_index_space_variable,Nil);
    SVREF(def_structure_index_space_variable,FIX((SI_Long)1L)) = 
	    index_space_name;
    SVREF(def_structure_index_space_variable,FIX((SI_Long)6L)) = 
	    index_space_object_reclaimer_qm;
    temp = make_index_space_vector();
    SVREF(def_structure_index_space_variable,FIX((SI_Long)2L)) = temp;
    ISVREF(def_structure_index_space_variable,(SI_Long)3L) = FIX((SI_Long)-1L);
    ISVREF(def_structure_index_space_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    SVREF(def_structure_index_space_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_index_space_variable);
}

/* RECLAIM-IF-INDEX-SPACE */
Object reclaim_if_index_space(index_space_qm)
    Object index_space_qm;
{
    x_note_fn_call(24,107);
    if (index_space_qm)
	reclaim_index_space_1(index_space_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-VECTOR-OF-INDEX-SUBSPACE-VECTORS */
Object reclaim_vector_of_index_subspace_vectors(vector_of_index_subspace_vectors)
    Object vector_of_index_subspace_vectors;
{
    Object index_space_name, index_space_object_reclaimer_qm;
    Object nil_unreclaimed_as_yet_p, index_subspace_vector_qm, fn, object_qm;
    SI_Long i, ab_loop_bind_, j;

    x_note_fn_call(24,108);
    index_space_name = ISVREF(Structure_being_reclaimed,(SI_Long)1L);
    index_space_object_reclaimer_qm = ISVREF(Structure_being_reclaimed,
	    (SI_Long)6L);
    nil_unreclaimed_as_yet_p = T;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(vector_of_index_subspace_vectors));
    index_subspace_vector_qm = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    index_subspace_vector_qm = ISVREF(vector_of_index_subspace_vectors,i);
    if ( !TRUEP(index_subspace_vector_qm))
	goto end_loop;
    if (index_space_object_reclaimer_qm) {
	fn = SYMBOL_FUNCTION(index_space_object_reclaimer_qm);
	j = (SI_Long)0L;
	object_qm = Nil;
      next_loop_1:
	if (j >= (SI_Long)1024L)
	    goto end_loop_1;
	object_qm = ISVREF(index_subspace_vector_qm,j);
	if (object_qm || nil_unreclaimed_as_yet_p) {
	    inline_funcall_3(fn,object_qm,index_space_name,T);
	    if ( !TRUEP(object_qm))
		nil_unreclaimed_as_yet_p = Nil;
	}
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    reclaim_managed_simple_vector(index_subspace_vector_qm);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return reclaim_managed_simple_vector(vector_of_index_subspace_vectors);
}

static Object Qab_gensym;          /* gensym */

/* ASSIGN-INDEX-IN-INDEX-SPACE */
Object assign_index_in_index_space(index_space)
    Object index_space;
{
    Object gensym_pop_store, cons_1, next_cons, temp, svref_arg_2, index_1;
    Object temp_1;

    x_note_fn_call(24,109);
    if (ISVREF(index_space,(SI_Long)5L)) {
	gensym_pop_store = Nil;
	cons_1 = ISVREF(index_space,(SI_Long)5L);
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
	SVREF(index_space,FIX((SI_Long)5L)) = next_cons;
	return VALUES_1(gensym_pop_store);
    }
    else {
	index_1 = FIXNUM_ADD1(ISVREF(index_space,(SI_Long)3L));
	SVREF(index_space,FIX((SI_Long)3L)) = index_1;
	if (FIXNUM_EQ(index_1,ISVREF(index_space,(SI_Long)4L))) {
	    enlarge_index_space(index_space,Nil);
	    temp_1 = ISVREF(index_space,(SI_Long)4L);
	    return VALUES_2(index_1,temp_1);
	}
	else
	    return VALUES_1(index_1);
    }
}

/* DEASSIGN-INDEX-IN-INDEX-SPACE */
Object deassign_index_in_index_space(index_1,index_space)
    Object index_1, index_space;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(24,110);
    gensym_push_modify_macro_arg = index_1;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(index_space,(SI_Long)5L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    return VALUES_1(SVREF(index_space,FIX((SI_Long)5L)) = svref_new_value);
}

Object Enlarge_index_space_error_message = UNBOUND;

/* ENLARGE-INDEX-SPACE */
Object enlarge_index_space(index_space,minimum_new_index_limit_qm)
    Object index_space, minimum_new_index_limit_qm;
{
    Object spine_vector, spine_vector_length, new_index_subspace_index;
    Object new_spine_vector, temp, svref_new_value;
    SI_Long new_spine_vector_length, i, ab_loop_bind_, svref_new_value_1;

    x_note_fn_call(24,111);
    if (minimum_new_index_limit_qm) {
	if (FIXNUM_GT(ISVREF(index_space,(SI_Long)4L),
		minimum_new_index_limit_qm))
	    return VALUES_1(Nil);
    }
    else
	minimum_new_index_limit_qm = ISVREF(index_space,(SI_Long)4L);
    spine_vector = ISVREF(index_space,(SI_Long)2L);
    spine_vector_length = length(spine_vector);
    new_index_subspace_index = Nil;
  next_loop:
    new_index_subspace_index = FIX(IFIX(ISVREF(index_space,(SI_Long)4L)) 
	    >>  -  - (SI_Long)10L);
    if (FIXNUM_EQ(new_index_subspace_index,spine_vector_length)) {
	new_spine_vector_length = IFIX(spine_vector_length) << (SI_Long)1L;
	new_spine_vector = 
		allocate_managed_simple_vector(FIX(new_spine_vector_length));
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(spine_vector_length);
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	temp = ISVREF(spine_vector,i);
	ISVREF(new_spine_vector,i) = temp;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	i = IFIX(spine_vector_length);
	ab_loop_bind_ = new_spine_vector_length;
      next_loop_2:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(new_spine_vector,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_1:;
	reclaim_managed_simple_vector(spine_vector);
	SVREF(index_space,FIX((SI_Long)2L)) = new_spine_vector;
	spine_vector = new_spine_vector;
	spine_vector_length = FIX(new_spine_vector_length);
    }
    temp = ISVREF(index_space,(SI_Long)2L);
    svref_new_value = make_index_space_vector();
    SVREF(temp,new_index_subspace_index) = svref_new_value;
    svref_new_value_1 = IFIX(ISVREF(index_space,(SI_Long)4L)) + (SI_Long)1024L;
    ISVREF(index_space,(SI_Long)4L) = FIX(svref_new_value_1);
    if (FIXNUM_GT(ISVREF(index_space,(SI_Long)4L),minimum_new_index_limit_qm))
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

Object The_type_description_of_queue_element = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_queue_elements, Qchain_of_available_queue_elements);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_element_count, Qqueue_element_count);

Object Chain_of_available_queue_elements_vector = UNBOUND;

/* QUEUE-ELEMENT-STRUCTURE-MEMORY-USAGE */
Object queue_element_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,112);
    temp = Queue_element_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-QUEUE-ELEMENT-COUNT */
Object outstanding_queue_element_count()
{
    Object def_structure_queue_element_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,113);
    gensymed_symbol = IFIX(Queue_element_count);
    def_structure_queue_element_variable = Chain_of_available_queue_elements;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_queue_element_variable))
	goto end_loop;
    def_structure_queue_element_variable = 
	    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-QUEUE-ELEMENT-1 */
Object reclaim_queue_element_1(queue_element)
    Object queue_element;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,114);
    inline_note_reclaim_cons(queue_element,Nil);
    temp = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(queue_element,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = queue_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-QUEUE-ELEMENT */
Object reclaim_structure_for_queue_element(queue_element)
    Object queue_element;
{
    x_note_fn_call(24,115);
    return reclaim_queue_element_1(queue_element);
}

/* MAKE-PERMANENT-QUEUE-ELEMENT-STRUCTURE-INTERNAL */
Object make_permanent_queue_element_structure_internal()
{
    Object def_structure_queue_element_variable, the_array;
    Object defstruct_g2_queue_element_variable;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,116);
    def_structure_queue_element_variable = Nil;
    atomic_incff_symval(Qqueue_element_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
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
	defstruct_g2_queue_element_variable = the_array;
	def_structure_queue_element_variable = 
		defstruct_g2_queue_element_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_queue_element_variable);
}

/* MAKE-QUEUE-ELEMENT-1 */
Object make_queue_element_1(queue_next_element,queue_previous_element,
	    queue_datum)
    Object queue_next_element, queue_previous_element, queue_datum;
{
    Object def_structure_queue_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,117);
    def_structure_queue_element_variable = 
	    ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_element_variable) {
	svref_arg_1 = Chain_of_available_queue_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = 
	    queue_next_element;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)3L)) = 
	    queue_previous_element;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)4L)) = queue_datum;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_queue_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    return VALUES_1(def_structure_queue_element_variable);
}

Object Constant_queue_marker = UNBOUND;

/* READ-QUEUE-NODE */
Object read_queue_node(reference)
    Object reference;
{
    Object reference_1, temp, temp_1, node, mark, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    Object result;

    x_note_fn_call(24,118);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference_1) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,node,mark);
    if ( !TRUEP(mark)) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = node;
	if ( !TRUEP(gensymed_symbol)) {
	    temp_1 = Nil;
	    goto end_1;
	}
      next_loop_1:
	gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	    goto end_2;
	goto next_loop_1;
      end_loop:
      end_2:
	if (EQ(gensymed_symbol,node)) {
	    temp_1 = gensymed_symbol;
	    goto end_1;
	}
	else
	    release_queue_node(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
      end_1:;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CREATE-QUEUE-ELEMENT */
Object create_queue_element(thing)
    Object thing;
{
    Object def_structure_queue_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value, node, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2;

    x_note_fn_call(24,119);
    def_structure_queue_element_variable = 
	    ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_element_variable) {
	svref_arg_1 = Chain_of_available_queue_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_queue_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    node = def_structure_queue_element_variable;
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol)) {
	node = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,node)) {
	node = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    node = Qnil;
  end_1:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_2:
    gensymed_symbol = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    SVREF(node,FIX((SI_Long)4L)) = thing;
    return VALUES_1(node);
}

/* RELEASE-QUEUE-NODE */
Object release_queue_node(node)
    Object node;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, temp_1, temp_2;
    Object svref_arg_2;

    x_note_fn_call(24,120);
    if ( !TRUEP(node))
	return VALUES_1(Nil);
    temp = FIX((SI_Long)0L);
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop:
    gensymed_symbol = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_1 = FIX(IFIX(gensymed_symbol) - (SI_Long)2L);
    if ((SI_Long)0L == IFIX(gensymed_symbol_1))
	gensymed_symbol_1 = FIX((SI_Long)1L);
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp_1 = FIX(IFIX(FIXNUM_MINUS(gensymed_symbol,gensymed_symbol_1)) & 
	    (SI_Long)1L);
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    if (NUM_EQ(temp,temp_1))
	return VALUES_1(Nil);
    release_reference(node);
    inline_note_reclaim_cons(node,Nil);
    temp_2 = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(node,FIX((SI_Long)0L)) = temp_2;
    temp_2 = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_2,svref_arg_2) = node;
    return VALUES_1(Nil);
}

Object Constant_queue_head_marker = UNBOUND;

Object Constant_queue_tail_marker = UNBOUND;

/* RELEASE-REFERENCE */
Object release_reference(node)
    Object node;
{
    x_note_fn_call(24,121);
    release_queue_node(ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)3L)));
    return release_queue_node(ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)2L)));
}

/* MAKE-EMPTY-CONSTANT-QUEUE */
Object make_empty_constant_queue()
{
    Object def_structure_queue_element_variable, temp, svref_arg_2;
    Object svref_new_value, new_queue, head, tail, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(24,122);
    def_structure_queue_element_variable = 
	    ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_element_variable) {
	temp = Chain_of_available_queue_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_element_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)4L)) = 
	    Constant_queue_marker;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_queue_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    new_queue = def_structure_queue_element_variable;
    def_structure_queue_element_variable = 
	    ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_element_variable) {
	temp = Chain_of_available_queue_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_element_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = Nil;
    temp = MAKE_ATOMIC_REF(Nil,(SI_Long)0L);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)3L)) = temp;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)4L)) = 
	    Constant_queue_head_marker;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_queue_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    head = def_structure_queue_element_variable;
    def_structure_queue_element_variable = 
	    ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_element_variable) {
	temp = Chain_of_available_queue_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_element_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_queue_element_variable = 
		make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    temp = MAKE_ATOMIC_REF(Nil,(SI_Long)0L);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)4L)) = 
	    Constant_queue_tail_marker;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    ISVREF(def_structure_queue_element_variable,(SI_Long)1L) = 
	    FIX((SI_Long)1L);
    tail = def_structure_queue_element_variable;
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = head;
    if ( !TRUEP(gensymed_symbol)) {
	head = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(head,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(head,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,head)) {
	head = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    head = Qnil;
  end_1:;
    gensymed_symbol = Nil;
  next_loop_2:
    gensymed_symbol = tail;
    if ( !TRUEP(gensymed_symbol)) {
	tail = Nil;
	goto end_3;
    }
  next_loop_3:
    gensymed_symbol_1 = ISVREF(tail,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(tail,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_4;
    goto next_loop_3;
  end_loop_2:
  end_4:
    if (EQ(gensymed_symbol,tail)) {
	tail = gensymed_symbol;
	goto end_3;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop_2;
  end_loop_3:
    tail = Qnil;
  end_3:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_4:
    gensymed_symbol = ISVREF(head,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(head,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_4;
    goto next_loop_4;
  end_loop_4:;
    gensymed_symbol = Nil;
    gensymed_symbol_1 = Nil;
  next_loop_5:
    gensymed_symbol = ISVREF(tail,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(gensymed_symbol);
    if (CAS_SVREF(tail,(SI_Long)1L,gensymed_symbol,gensymed_symbol_1))
	goto end_loop_5;
    goto next_loop_5;
  end_loop_5:;
    temp = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    SVREF(head,FIX((SI_Long)2L)) = temp;
    temp = MAKE_ATOMIC_REF(head,(SI_Long)0L);
    SVREF(tail,FIX((SI_Long)3L)) = temp;
    SVREF(new_queue,FIX((SI_Long)2L)) = head;
    SVREF(new_queue,FIX((SI_Long)3L)) = tail;
    return VALUES_1(new_queue);
}

/* CONSTANT-QUEUE-NEXT */
Object constant_queue_next(cursor,constant_queue)
    Object cursor, constant_queue;
{
    Object tail, temp, reference, reference_1, node, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, next;
    char d, temp_1;

    x_note_fn_call(24,123);
    tail = ISVREF(constant_queue,(SI_Long)3L);
  next_loop:
    if (EQ(cursor,tail)) {
	temp = Nil;
	goto end_1;
    }
    reference = ISVREF(cursor,(SI_Long)2L);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node = temp;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol))
	goto end_2;
  next_loop_2:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_3;
    goto next_loop_2;
  end_loop:
  end_3:
    if (EQ(gensymed_symbol,node))
	goto end_2;
    else
	release_queue_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
  end_2:;
    next = node;
    d = (SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L));
    if (d) {
	temp = ISVREF(cursor,(SI_Long)2L);
	temp_1 =  !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)355L));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if (EQ(next,ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)2L))))
	    help_delete_queue_node(next);
	release_queue_node(next);
    }
    else {
	release_queue_node(next);
	cursor = next;
	if ( !d &&  !EQ(next,tail)) {
	    temp = cursor;
	    goto end_1;
	}
    }
    goto next_loop;
  end_loop_2:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-PREVIOUS */
Object constant_queue_previous(cursor,constant_queue)
    Object cursor, constant_queue;
{
    Object head, reference, reference_1, temp, node, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, prev;

    x_note_fn_call(24,124);
    head = ISVREF(constant_queue,(SI_Long)2L);
  next_loop:
    if (EQ(cursor,head))
	return VALUES_1(Nil);
    reference = ISVREF(cursor,(SI_Long)3L);
    reference_1 = reference;
    temp = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node = temp;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = node;
    if ( !TRUEP(gensymed_symbol))
	goto end_1;
  next_loop_2:
    gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_2;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,node))
	goto end_1;
    else
	release_queue_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    prev = node;
    temp = ISVREF(prev,(SI_Long)2L);
    if (EQ(temp,MAKE_ATOMIC_REF(cursor,(SI_Long)0L)) &&  !((SI_Long)355L 
	    == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))) {
	release_queue_node(prev);
	cursor = prev;
	if ( !EQ(prev,head))
	    return VALUES_1(cursor);
    }
    else if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))
	cursor = constant_queue_next(cursor,constant_queue);
    else {
	prev = help_insert_queue_node(prev,cursor);
	release_queue_node(prev);
    }
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* CONSTANT-QUEUE-READ */
Object constant_queue_read varargs_1(int, n)
{
    Object cursor;
    Object constant_queue, value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,125);
    INIT_ARGS_nonrelocating();
    cursor = REQUIRED_ARG_nonrelocating();
    constant_queue = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(cursor,constant_queue ? ISVREF(constant_queue,(SI_Long)2L) : 
	    Nil) || EQ(cursor,constant_queue ? ISVREF(constant_queue,
	    (SI_Long)3L) : Nil))
	return VALUES_1(Nil);
    else {
	value = ISVREF(cursor,(SI_Long)4L);
	if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(value);
    }
}

/* CLEAR-CONSTANT-QUEUE */
Object clear_constant_queue(constant_queue)
    Object constant_queue;
{
    Object head, tail, next_element_structure, element_structure, temp;
    Object svref_arg_2;

    x_note_fn_call(24,126);
    head = ISVREF(constant_queue,(SI_Long)2L);
    tail = ISVREF(constant_queue,(SI_Long)3L);
    next_element_structure = Nil;
    element_structure = ATOMIC_REF_OBJECT(ISVREF(head,(SI_Long)2L));
  next_loop:
    if (EQ(element_structure,tail))
	goto end_loop;
    next_element_structure = ATOMIC_REF_OBJECT(ISVREF(element_structure,
	    (SI_Long)2L));
    inline_note_reclaim_cons(element_structure,Nil);
    temp = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(element_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = element_structure;
    element_structure = next_element_structure;
    goto next_loop;
  end_loop:;
    temp = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    SVREF(head,FIX((SI_Long)2L)) = temp;
    temp = MAKE_ATOMIC_REF(head,(SI_Long)0L);
    SVREF(tail,FIX((SI_Long)3L)) = temp;
    return VALUES_1(constant_queue);
}

/* RECLAIM-CONSTANT-QUEUE */
Object reclaim_constant_queue(constant_queue)
    Object constant_queue;
{
    Object head, tail, element, temp, temp_1, svref_arg_2;

    x_note_fn_call(24,127);
    head = ISVREF(constant_queue,(SI_Long)2L);
    tail = ISVREF(constant_queue,(SI_Long)3L);
    element = head;
  next_loop:
    if (EQ(element,tail))
	goto end_loop;
    temp = ATOMIC_REF_OBJECT(ISVREF(element,(SI_Long)2L));
    inline_note_reclaim_cons(element,Nil);
    temp_1 = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(element,FIX((SI_Long)0L)) = temp_1;
    temp_1 = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_1,svref_arg_2) = element;
    element = temp;
    goto next_loop;
  end_loop:
    inline_note_reclaim_cons(element,Nil);
    temp_1 = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(element,FIX((SI_Long)0L)) = temp_1;
    temp_1 = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_1,svref_arg_2) = element;
    SVREF(constant_queue,FIX((SI_Long)4L)) = Nil;
    inline_note_reclaim_cons(constant_queue,Nil);
    temp_1 = ISVREF(Chain_of_available_queue_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(constant_queue,FIX((SI_Long)0L)) = temp_1;
    temp_1 = Chain_of_available_queue_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_1,svref_arg_2) = constant_queue;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-PUSH-COMMON */
Object constant_queue_push_common(node,next)
    Object node, next;
{
    Object backoff_limit, link1, temp_1, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, prev2;
    char temp;
    Declare_special(1);

    x_note_fn_call(24,128);
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
      link1 = Nil;
    next_loop:
      link1 = ISVREF(next,(SI_Long)3L);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(link1);
      if (temp);
      else {
	  temp_1 = ISVREF(node,(SI_Long)2L);
	  temp =  !EQ(temp_1,MAKE_ATOMIC_REF(next,(SI_Long)0L));
      }
      if (temp)
	  goto end_loop;
      temp_1 = link1;
      if (CAS_SVREF(next,(SI_Long)3L,temp_1,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_1:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_1;
	next_loop_2:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_2;
	  goto next_loop_2;
	end_loop_1:
	end_2:
	  if (EQ(gensymed_symbol,node))
	      goto end_1;
	  else
	      release_queue_node(gensymed_symbol);
	  goto next_loop_1;
	end_loop_2:
	end_1:;
	  release_queue_node(ATOMIC_REF_OBJECT(link1));
	  if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(node,(SI_Long)3L))) {
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node;
	      if ( !TRUEP(gensymed_symbol)) {
		  prev2 = Nil;
		  goto end_3;
	      }
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_3:
	    end_4:
	      if (EQ(gensymed_symbol,node)) {
		  prev2 = gensymed_symbol;
		  goto end_3;
	      }
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_4:
	      prev2 = Qnil;
	    end_3:;
	      prev2 = help_insert_queue_node(prev2,next);
	      release_queue_node(prev2);
	  }
	  goto end_loop;
      }
      back_off();
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    release_queue_node(next);
    release_queue_node(node);
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-PUSH-RIGHT */
Object constant_queue_push_right(constant_queue,thing)
    Object constant_queue, thing;
{
    Object node, gensymed_symbol, next, gensymed_symbol_1, gensymed_symbol_2;
    Object prev, backoff_limit, temp, svref_new_value, temp_1;
    Declare_special(1);

    x_note_fn_call(24,129);
    node = create_queue_element(thing);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(constant_queue,(SI_Long)3L);
    if ( !TRUEP(gensymed_symbol)) {
	next = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(constant_queue,(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(constant_queue,(SI_Long)3L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(constant_queue,(SI_Long)3L))) {
	next = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    next = Qnil;
  end_1:;
    prev = read_queue_node(ISVREF(next,(SI_Long)3L));
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)0L)))
	  prev = help_insert_queue_node(prev,next);
      else {
	  svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	  svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	  temp = prev;
	  temp_1 = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  if (CAS_SVREF(temp,(SI_Long)2L,temp_1,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_3;
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_2:
	    end_4:
	      if (EQ(gensymed_symbol,node))
		  goto end_3;
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_3:
	    end_3:;
	      goto end_loop_4;
	  }
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      constant_queue_push_common(node,next);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-PUSH-LEFT */
Object constant_queue_push_left(constant_queue,thing)
    Object constant_queue, thing;
{
    Object node, gensymed_symbol, prev, gensymed_symbol_1, gensymed_symbol_2;
    Object next, backoff_limit, temp, svref_new_value;
    Declare_special(1);

    x_note_fn_call(24,130);
    node = create_queue_element(thing);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(constant_queue,(SI_Long)2L);
    if ( !TRUEP(gensymed_symbol)) {
	prev = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(constant_queue,(SI_Long)2L),(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(constant_queue,(SI_Long)2L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(constant_queue,(SI_Long)2L))) {
	prev = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    prev = Qnil;
  end_1:;
    next = read_queue_node(ISVREF(prev,(SI_Long)2L));
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)0L))) {
	  release_queue_node(next);
	  next = read_queue_node(ISVREF(prev,(SI_Long)2L));
      }
      else {
	  svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	  svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	  temp = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  if (CAS_SVREF(prev,(SI_Long)2L,temp,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_3;
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_2:
	    end_4:
	      if (EQ(gensymed_symbol,node))
		  goto end_3;
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_3:
	    end_3:;
	      goto end_loop_4;
	  }
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      constant_queue_push_common(node,next);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-POP-LEFT */
Object constant_queue_pop_left varargs_1(int, n)
{
    Object constant_queue;
    Object default_value, gensymed_symbol, prev, gensymed_symbol_1;
    Object gensymed_symbol_2, tail, node, return_value, backoff_limit, link1;
    Object temp, reference, reference_1, node_1, next, prev2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(24,131);
    INIT_ARGS_nonrelocating();
    constant_queue = REQUIRED_ARG_nonrelocating();
    default_value = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(constant_queue,(SI_Long)2L);
    if ( !TRUEP(gensymed_symbol)) {
	prev = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(constant_queue,(SI_Long)2L),(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(constant_queue,(SI_Long)2L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(constant_queue,(SI_Long)2L))) {
	prev = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    prev = Qnil;
  end_1:;
    tail = ISVREF(constant_queue,(SI_Long)3L);
    node = Nil;
    return_value = default_value;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      node = read_queue_node(ISVREF(prev,(SI_Long)2L));
      if (EQ(node,tail)) {
	  release_queue_node(node);
	  release_queue_node(prev);
	  result = VALUES_2(default_value,Nil);
	  POP_SPECIAL();
	  goto end_constant_queue_pop_left;
      }
      link1 = ISVREF(node,(SI_Long)2L);
      if ((SI_Long)355L == ATOMIC_REF_STAMP(link1)) {
	  help_delete_queue_node(node);
	  release_queue_node(node);
      }
      else {
	  temp = node;
	  if (CAS_SVREF(temp,(SI_Long)2L,link1,
		  MAKE_ATOMIC_REF(ATOMIC_REF_OBJECT(link1),(SI_Long)355L))) {
	      help_delete_queue_node(node);
	      reference = ISVREF(node,(SI_Long)2L);
	      reference_1 = reference;
	      temp = ATOMIC_REF_OBJECT(reference_1);
	      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	      node_1 = temp;
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node_1;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_3;
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_2:
	    end_4:
	      if (EQ(gensymed_symbol,node_1))
		  goto end_3;
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_3:
	    end_3:;
	      next = node_1;
	      prev2 = help_insert_queue_node(prev,next);
	      release_queue_node(prev2);
	      release_queue_node(next);
	      return_value = ISVREF(node,(SI_Long)4L);
	      goto end_loop_4;
	  }
	  release_queue_node(node);
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      remove_queue_cross_reference(node);
      release_queue_node(node);
      result = VALUES_2(return_value,T);
    POP_SPECIAL();
  end_constant_queue_pop_left:
    return result;
}

/* CONSTANT-QUEUE-POP-RIGHT */
Object constant_queue_pop_right varargs_1(int, n)
{
    Object constant_queue;
    Object default_value, gensymed_symbol, next, gensymed_symbol_1;
    Object gensymed_symbol_2, node, return_value, backoff_limit, temp, temp_1;
    Object reference, reference_1, node_1, prev, prev2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(24,132);
    INIT_ARGS_nonrelocating();
    constant_queue = REQUIRED_ARG_nonrelocating();
    default_value = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(constant_queue,(SI_Long)3L);
    if ( !TRUEP(gensymed_symbol)) {
	next = Nil;
	goto end_1;
    }
  next_loop_1:
    gensymed_symbol_1 = ISVREF(ISVREF(constant_queue,(SI_Long)3L),(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(ISVREF(constant_queue,(SI_Long)3L),(SI_Long)1L,
	    gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_1;
  end_loop:
  end_2:
    if (EQ(gensymed_symbol,ISVREF(constant_queue,(SI_Long)3L))) {
	next = gensymed_symbol;
	goto end_1;
    }
    else
	release_queue_node(gensymed_symbol);
    goto next_loop;
  end_loop_1:
    next = Qnil;
  end_1:;
    node = read_queue_node(ISVREF(next,(SI_Long)3L));
    return_value = default_value;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_2:
      temp = ISVREF(node,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(next,(SI_Long)0L)))
	  node = help_insert_queue_node(node,next);
      else {
	  if (EQ(node,ISVREF(constant_queue,(SI_Long)2L))) {
	      release_queue_node(node);
	      release_queue_node(next);
	      result = VALUES_2(default_value,Nil);
	      POP_SPECIAL();
	      goto end_constant_queue_pop_right;
	  }
	  temp = node;
	  temp_1 = MAKE_ATOMIC_REF(next,(SI_Long)0L);
	  if (CAS_SVREF(temp,(SI_Long)2L,temp_1,MAKE_ATOMIC_REF(next,
		  (SI_Long)355L))) {
	      help_delete_queue_node(node);
	      reference = ISVREF(node,(SI_Long)3L);
	      reference_1 = reference;
	      temp = ATOMIC_REF_OBJECT(reference_1);
	      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	      node_1 = temp;
	      gensymed_symbol = Nil;
	    next_loop_3:
	      gensymed_symbol = node_1;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_3;
	    next_loop_4:
	      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_4;
	      goto next_loop_4;
	    end_loop_2:
	    end_4:
	      if (EQ(gensymed_symbol,node_1))
		  goto end_3;
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_3;
	    end_loop_3:
	    end_3:;
	      prev = node_1;
	      prev2 = help_insert_queue_node(prev,next);
	      release_queue_node(prev2);
	      release_queue_node(next);
	      return_value = ISVREF(node,(SI_Long)4L);
	      goto end_loop_4;
	  }
	  back_off();
      }
      goto next_loop_2;
    end_loop_4:
      remove_queue_cross_reference(node);
      release_queue_node(node);
      result = VALUES_2(return_value,T);
    POP_SPECIAL();
  end_constant_queue_pop_right:
    return result;
}

/* HELP-DELETE-QUEUE-NODE */
Object help_delete_queue_node(node)
    Object node;
{
    Object link1, temp_1, lastlink_deleted_qm, reference, reference_1, node_1;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, prev, next;
    Object backoff_limit, next2, prev2, temp_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(24,133);
    link1 = Nil;
  next_loop:
    link1 = ISVREF(node,(SI_Long)3L);
    temp = (SI_Long)355L == ATOMIC_REF_STAMP(link1);
    if (temp);
    else {
	temp_1 = link1;
	temp = TRUEP(CAS_SVREF(node,(SI_Long)3L,temp_1,
		MAKE_ATOMIC_REF(ATOMIC_REF_OBJECT(link1),(SI_Long)355L)));
    }
    if (temp)
	goto end_loop;
    goto next_loop;
  end_loop:;
    lastlink_deleted_qm = T;
    reference = ISVREF(node,(SI_Long)3L);
    reference_1 = reference;
    temp_1 = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node_1 = temp_1;
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = node_1;
    if ( !TRUEP(gensymed_symbol))
	goto end_1;
  next_loop_2:
    gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_2;
    goto next_loop_2;
  end_loop_1:
  end_2:
    if (EQ(gensymed_symbol,node_1))
	goto end_1;
    else
	release_queue_node(gensymed_symbol);
    goto next_loop_1;
  end_loop_2:
  end_1:;
    prev = node_1;
    reference = ISVREF(node,(SI_Long)2L);
    reference_1 = reference;
    temp_1 = ATOMIC_REF_OBJECT(reference_1);
    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
    node_1 = temp_1;
    gensymed_symbol = Nil;
  next_loop_3:
    gensymed_symbol = node_1;
    if ( !TRUEP(gensymed_symbol))
	goto end_3;
  next_loop_4:
    gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
    if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	goto end_4;
    goto next_loop_4;
  end_loop_3:
  end_4:
    if (EQ(gensymed_symbol,node_1))
	goto end_3;
    else
	release_queue_node(gensymed_symbol);
    goto next_loop_3;
  end_loop_4:
  end_3:;
    next = node_1;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop_5:
      if (EQ(prev,next))
	  goto end_loop_5;
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L))) {
	  reference = ISVREF(next,(SI_Long)2L);
	  reference_1 = reference;
	  temp_1 = ATOMIC_REF_OBJECT(reference_1);
	  (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	  node_1 = temp_1;
	  gensymed_symbol = Nil;
	next_loop_6:
	  gensymed_symbol = node_1;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_5;
	next_loop_7:
	  gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		  gensymed_symbol_2))
	      goto end_6;
	  goto next_loop_7;
	end_loop_6:
	end_6:
	  if (EQ(gensymed_symbol,node_1))
	      goto end_5;
	  else
	      release_queue_node(gensymed_symbol);
	  goto next_loop_6;
	end_loop_7:
	end_5:;
	  next2 = node_1;
	  release_queue_node(next);
	  next = next2;
      }
      else {
	  prev2 = read_queue_node(ISVREF(prev,(SI_Long)2L));
	  if ( !TRUEP(prev2)) {
	      if ( !TRUEP(lastlink_deleted_qm)) {
		  help_delete_queue_node(prev);
		  lastlink_deleted_qm = T;
	      }
	      reference = ISVREF(prev,(SI_Long)3L);
	      reference_1 = reference;
	      temp_1 = ATOMIC_REF_OBJECT(reference_1);
	      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	      node_1 = temp_1;
	      gensymed_symbol = Nil;
	    next_loop_8:
	      gensymed_symbol = node_1;
	      if ( !TRUEP(gensymed_symbol))
		  goto end_7;
	    next_loop_9:
	      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		      gensymed_symbol_2))
		  goto end_8;
	      goto next_loop_9;
	    end_loop_8:
	    end_8:
	      if (EQ(gensymed_symbol,node_1))
		  goto end_7;
	      else
		  release_queue_node(gensymed_symbol);
	      goto next_loop_8;
	    end_loop_9:
	    end_7:;
	      prev2 = node_1;
	      release_queue_node(prev);
	      prev = prev2;
	  }
	  else if ( !EQ(prev2,node)) {
	      lastlink_deleted_qm = Nil;
	      release_queue_node(prev);
	      prev = prev2;
	  }
	  else {
	      release_queue_node(prev2);
	      temp_1 = prev;
	      temp_2 = MAKE_ATOMIC_REF(node,(SI_Long)0L);
	      if (CAS_SVREF(temp_1,(SI_Long)2L,temp_2,MAKE_ATOMIC_REF(next,
		      (SI_Long)0L))) {
		  gensymed_symbol = Nil;
		next_loop_10:
		  gensymed_symbol = next;
		  if ( !TRUEP(gensymed_symbol))
		      goto end_9;
		next_loop_11:
		  gensymed_symbol_1 = ISVREF(next,(SI_Long)1L);
		  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
		  if (CAS_SVREF(next,(SI_Long)1L,gensymed_symbol_1,
			  gensymed_symbol_2))
		      goto end_10;
		  goto next_loop_11;
		end_loop_10:
		end_10:
		  if (EQ(gensymed_symbol,next))
		      goto end_9;
		  else
		      release_queue_node(gensymed_symbol);
		  goto next_loop_10;
		end_loop_11:
		end_9:;
		  release_queue_node(node);
		  goto end_loop_5;
	      }
	      back_off();
	  }
      }
      goto next_loop_5;
    end_loop_5:
      release_queue_node(prev);
      release_queue_node(next);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HELP-INSERT-QUEUE-NODE */
Object help_insert_queue_node(prev,node)
    Object prev, node;
{
    Object backoff_limit, lastlink_deleted_qm, prev2, reference, reference_1;
    Object temp, node_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object link1;
    Declare_special(1);

    x_note_fn_call(24,134);
    backoff_limit = Backoff_min_delay;
    lastlink_deleted_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
      prev2 = Nil;
    next_loop:
      prev2 = read_queue_node(ISVREF(prev,(SI_Long)2L));
      if ( !TRUEP(prev2)) {
	  if ( !TRUEP(lastlink_deleted_qm)) {
	      help_delete_queue_node(prev);
	      lastlink_deleted_qm = T;
	  }
	  reference = ISVREF(prev,(SI_Long)3L);
	  reference_1 = reference;
	  temp = ATOMIC_REF_OBJECT(reference_1);
	  (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	  node_1 = temp;
	  gensymed_symbol = Nil;
	next_loop_1:
	  gensymed_symbol = node_1;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_1;
	next_loop_2:
	  gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		  gensymed_symbol_2))
	      goto end_2;
	  goto next_loop_2;
	end_loop:
	end_2:
	  if (EQ(gensymed_symbol,node_1))
	      goto end_1;
	  else
	      release_queue_node(gensymed_symbol);
	  goto next_loop_1;
	end_loop_1:
	end_1:;
	  prev2 = node_1;
	  release_queue_node(prev);
	  prev = prev2;
      }
      else {
	  link1 = ISVREF(node,(SI_Long)3L);
	  if ((SI_Long)355L == ATOMIC_REF_STAMP(link1)) {
	      release_queue_node(prev2);
	      temp = prev;
	      goto end_3;
	  }
	  if ( !EQ(prev2,node)) {
	      lastlink_deleted_qm = Nil;
	      release_queue_node(prev);
	      prev = prev2;
	  }
	  else {
	      release_queue_node(prev2);
	      if (CAS_SVREF(node,(SI_Long)3L,link1,MAKE_ATOMIC_REF(prev,
		      (SI_Long)0L))) {
		  gensymed_symbol = Nil;
		next_loop_3:
		  gensymed_symbol = prev;
		  if ( !TRUEP(gensymed_symbol))
		      goto end_4;
		next_loop_4:
		  gensymed_symbol_1 = ISVREF(prev,(SI_Long)1L);
		  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
		  if (CAS_SVREF(prev,(SI_Long)1L,gensymed_symbol_1,
			  gensymed_symbol_2))
		      goto end_5;
		  goto next_loop_4;
		end_loop_2:
		end_5:
		  if (EQ(gensymed_symbol,prev))
		      goto end_4;
		  else
		      release_queue_node(gensymed_symbol);
		  goto next_loop_3;
		end_loop_3:
		end_4:;
		  release_queue_node(ATOMIC_REF_OBJECT(link1));
		  if ( !((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(prev,
			  (SI_Long)3L)))) {
		      temp = prev;
		      goto end_3;
		  }
	      }
	      back_off();
	  }
      }
      goto next_loop;
    end_loop_4:
      temp = Qnil;
    end_3:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* REMOVE-QUEUE-CROSS-REFERENCE */
Object remove_queue_cross_reference(node)
    Object node;
{
    Object prev, reference, reference_1, temp, node_1, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, prev2, svref_new_value, next;
    Object next2;

    x_note_fn_call(24,135);
    prev = Nil;
  next_loop:
    prev = ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)3L));
    if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(prev,(SI_Long)2L))) {
	reference = ISVREF(prev,(SI_Long)3L);
	reference_1 = reference;
	temp = ATOMIC_REF_OBJECT(reference_1);
	(SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	node_1 = temp;
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = node_1;
	if ( !TRUEP(gensymed_symbol))
	    goto end_1;
      next_loop_2:
	gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	    goto end_2;
	goto next_loop_2;
      end_loop:
      end_2:
	if (EQ(gensymed_symbol,node_1))
	    goto end_1;
	else
	    release_queue_node(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
      end_1:;
	prev2 = node_1;
	svref_new_value = MAKE_ATOMIC_REF(prev2,(SI_Long)355L);
	SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
	release_queue_node(prev);
    }
    else {
	next = ATOMIC_REF_OBJECT(ISVREF(node,(SI_Long)2L));
	if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(next,(SI_Long)2L))) {
	    reference = ISVREF(next,(SI_Long)2L);
	    reference_1 = reference;
	    temp = ATOMIC_REF_OBJECT(reference_1);
	    (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
	    node_1 = temp;
	    gensymed_symbol = Nil;
	  next_loop_3:
	    gensymed_symbol = node_1;
	    if ( !TRUEP(gensymed_symbol))
		goto end_3;
	  next_loop_4:
	    gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
	    gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	    if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,
		    gensymed_symbol_2))
		goto end_4;
	    goto next_loop_4;
	  end_loop_2:
	  end_4:
	    if (EQ(gensymed_symbol,node_1))
		goto end_3;
	    else
		release_queue_node(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_3:
	  end_3:;
	    next2 = node_1;
	    svref_new_value = MAKE_ATOMIC_REF(next2,(SI_Long)355L);
	    SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
	    release_queue_node(next);
	}
	else
	    goto end_loop_4;
    }
    goto next_loop;
  end_loop_4:;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-INSERT-BEFORE */
Object constant_queue_insert_before(constant_queue,cursor,thing)
    Object constant_queue, cursor, thing;
{
    Object node, backoff_limit, reference, reference_1, temp, node_1;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, prev;
    Object svref_new_value, temp_1, next;
    Declare_special(1);

    x_note_fn_call(24,136);
    if (EQ(cursor,ISVREF(constant_queue,(SI_Long)2L)))
	return constant_queue_insert_after(constant_queue,cursor,thing);
    node = create_queue_element(thing);
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop:
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L)))
	  cursor = constant_queue_next(cursor,constant_queue);
      reference = ISVREF(cursor,(SI_Long)3L);
      reference_1 = reference;
      temp = ATOMIC_REF_OBJECT(reference_1);
      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
      node_1 = temp;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = node_1;
      if ( !TRUEP(gensymed_symbol))
	  goto end_1;
    next_loop_2:
      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_2;
      goto next_loop_2;
    end_loop:
    end_2:
      if (EQ(gensymed_symbol,node_1))
	  goto end_1;
      else
	  release_queue_node(gensymed_symbol);
      goto next_loop_1;
    end_loop_1:
    end_1:;
      prev = node_1;
      svref_new_value = MAKE_ATOMIC_REF(prev,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
      temp = prev;
      temp_1 = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      if (CAS_SVREF(temp,(SI_Long)2L,temp_1,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_3:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_3;
	next_loop_4:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_4;
	  goto next_loop_4;
	end_loop_2:
	end_4:
	  if (EQ(gensymed_symbol,node))
	      goto end_3;
	  else
	      release_queue_node(gensymed_symbol);
	  goto next_loop_3;
	end_loop_3:
	end_3:;
	  goto end_loop_4;
      }
      temp = ISVREF(prev,(SI_Long)2L);
      if ( !EQ(temp,MAKE_ATOMIC_REF(cursor,(SI_Long)0L)))
	  prev = help_insert_queue_node(prev,cursor);
      release_queue_node(prev);
      back_off();
      goto next_loop;
    end_loop_4:
      next = cursor;
      node = help_insert_queue_node(node,next);
      release_queue_node(node);
      temp = node;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-INSERT-AFTER */
Object constant_queue_insert_after(constant_queue,cursor,thing)
    Object constant_queue, cursor, thing;
{
    Object node, next, backoff_limit, reference, reference_1, temp, node_1;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(24,137);
    if (EQ(cursor,ISVREF(constant_queue,(SI_Long)3L))) {
	result = constant_queue_insert_before(constant_queue,cursor,thing);
	goto end_constant_queue_insert_after;
    }
    node = create_queue_element(thing);
    next = Nil;
    backoff_limit = Backoff_min_delay;
    PUSH_SPECIAL_WITH_SYMBOL(Backoff_limit,Qbackoff_limit,backoff_limit,0);
    next_loop:
      reference = ISVREF(cursor,(SI_Long)2L);
      reference_1 = reference;
      temp = ATOMIC_REF_OBJECT(reference_1);
      (SI_Long)355L == ATOMIC_REF_STAMP(reference_1);
      node_1 = temp;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = node_1;
      if ( !TRUEP(gensymed_symbol))
	  goto end_1;
    next_loop_2:
      gensymed_symbol_1 = ISVREF(node_1,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(node_1,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_2;
      goto next_loop_2;
    end_loop:
    end_2:
      if (EQ(gensymed_symbol,node_1))
	  goto end_1;
      else
	  release_queue_node(gensymed_symbol);
      goto next_loop_1;
    end_loop_1:
    end_1:;
      next = node_1;
      svref_new_value = MAKE_ATOMIC_REF(cursor,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)3L)) = svref_new_value;
      svref_new_value = MAKE_ATOMIC_REF(next,(SI_Long)0L);
      SVREF(node,FIX((SI_Long)2L)) = svref_new_value;
      temp = MAKE_ATOMIC_REF(next,(SI_Long)0L);
      if (CAS_SVREF(cursor,(SI_Long)2L,temp,MAKE_ATOMIC_REF(node,
		  (SI_Long)0L))) {
	  gensymed_symbol = Nil;
	next_loop_3:
	  gensymed_symbol = node;
	  if ( !TRUEP(gensymed_symbol))
	      goto end_3;
	next_loop_4:
	  gensymed_symbol_1 = ISVREF(node,(SI_Long)1L);
	  gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	  if (CAS_SVREF(node,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	      goto end_4;
	  goto next_loop_4;
	end_loop_2:
	end_4:
	  if (EQ(gensymed_symbol,node))
	      goto end_3;
	  else
	      release_queue_node(gensymed_symbol);
	  goto next_loop_3;
	end_loop_3:
	end_3:;
	  goto end_loop_4;
      }
      release_queue_node(next);
      if ((SI_Long)355L == ATOMIC_REF_STAMP(ISVREF(cursor,(SI_Long)2L))) {
	  release_queue_node(node);
	  result = constant_queue_insert_before(constant_queue,cursor,thing);
	  POP_SPECIAL();
	  goto end_constant_queue_insert_after;
      }
      back_off();
      goto next_loop;
    end_loop_4:
      gensymed_symbol = Nil;
    next_loop_5:
      gensymed_symbol = cursor;
      if ( !TRUEP(gensymed_symbol))
	  goto end_5;
    next_loop_6:
      gensymed_symbol_1 = ISVREF(cursor,(SI_Long)1L);
      gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
      if (CAS_SVREF(cursor,(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	  goto end_6;
      goto next_loop_6;
    end_loop_5:
    end_6:
      if (EQ(gensymed_symbol,cursor))
	  goto end_5;
      else
	  release_queue_node(gensymed_symbol);
      goto next_loop_5;
    end_loop_6:
    end_5:;
      node = help_insert_queue_node(node,next);
      release_queue_node(node);
      release_queue_node(next);
      temp = node;
    POP_SPECIAL();
    result = VALUES_1(temp);
  end_constant_queue_insert_after:
    return result;
}

/* CONSTANT-QUEUE-DELETE */
Object constant_queue_delete varargs_1(int, n)
{
    Object cursor;
    Object constant_queue, link1, temp, gensymed_symbol, prev;
    Object gensymed_symbol_1, gensymed_symbol_2, value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(24,138);
    INIT_ARGS_nonrelocating();
    cursor = REQUIRED_ARG_nonrelocating();
    constant_queue = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (constant_queue && (EQ(cursor,ISVREF(constant_queue,(SI_Long)2L)) 
	    || EQ(cursor,ISVREF(constant_queue,(SI_Long)3L))))
	return VALUES_2(Nil,Nil);
    link1 = Nil;
  next_loop:
    link1 = ISVREF(cursor,(SI_Long)2L);
    if ((SI_Long)355L == ATOMIC_REF_STAMP(link1))
	return VALUES_2(Nil,Nil);
    temp = link1;
    if (CAS_SVREF(cursor,(SI_Long)2L,temp,
	    MAKE_ATOMIC_REF(ATOMIC_REF_OBJECT(link1),(SI_Long)355L))) {
	help_delete_queue_node(cursor);
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L));
	if ( !TRUEP(gensymed_symbol)) {
	    prev = Nil;
	    goto end_1;
	}
      next_loop_2:
	gensymed_symbol_1 = ISVREF(ATOMIC_REF_OBJECT(ISVREF(cursor,
		(SI_Long)3L)),(SI_Long)1L);
	gensymed_symbol_2 = add(gensymed_symbol_1,FIX((SI_Long)2L));
	if (CAS_SVREF(ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L)),
		(SI_Long)1L,gensymed_symbol_1,gensymed_symbol_2))
	    goto end_2;
	goto next_loop_2;
      end_loop:
      end_2:
	temp = gensymed_symbol;
	if (EQ(temp,ATOMIC_REF_OBJECT(ISVREF(cursor,(SI_Long)3L)))) {
	    prev = gensymed_symbol;
	    goto end_1;
	}
	else
	    release_queue_node(gensymed_symbol);
	goto next_loop_1;
      end_loop_1:
	prev = Qnil;
      end_1:;
	temp = prev;
	prev = help_insert_queue_node(temp,ATOMIC_REF_OBJECT(link1));
	release_queue_node(prev);
	value = ISVREF(cursor,(SI_Long)4L);
	remove_queue_cross_reference(cursor);
	return VALUES_2(value,T);
    }
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* CONSTANT-QUEUE-SEARCH-AND-DELETE */
Object constant_queue_search_and_delete(constant_queue,datum)
    Object constant_queue, datum;
{
    Object head, queue_element;

    x_note_fn_call(24,139);
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = constant_queue_next(head,constant_queue);
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    if (EQ(datum,ISVREF(queue_element,(SI_Long)4L))) {
	constant_queue_delete(2,queue_element,constant_queue);
	goto end_loop;
    }
    queue_element = constant_queue_next(queue_element,constant_queue);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-SEARCH-AND-DELETE-ALL */
Object constant_queue_search_and_delete_all(constant_queue,datum)
    Object constant_queue, datum;
{
    Object head, queue_element, next_queue_element;

    x_note_fn_call(24,140);
    head = ISVREF(constant_queue,(SI_Long)2L);
    queue_element = constant_queue_next(head,constant_queue);
    next_queue_element = Nil;
  next_loop:
    if ( !TRUEP(queue_element))
	goto end_loop;
    next_queue_element = constant_queue_next(queue_element,constant_queue);
    if (EQ(datum,ISVREF(queue_element,(SI_Long)4L)))
	constant_queue_delete(2,queue_element,constant_queue);
    queue_element = next_queue_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REQUEUE-QUEUE-ELEMENT */
Object requeue_queue_element(constant_queue,queue_element,element_queue)
    Object constant_queue, queue_element, element_queue;
{
    Object value;

    x_note_fn_call(24,141);
    value = ISVREF(queue_element,(SI_Long)4L);
    constant_queue_delete(2,queue_element,element_queue);
    constant_queue_push_right(constant_queue,value);
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-LENGTH */
Object constant_queue_length(constant_queue)
    Object constant_queue;
{
    Object queue, next_queue_element, element;
    SI_Long ab_loopvar_;

    x_note_fn_call(24,142);
    if ( !TRUEP(constant_queue))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	queue = constant_queue;
	next_queue_element = Nil;
	element = Nil;
	ab_loopvar_ = (SI_Long)0L;
	next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),
		queue);
      next_loop:
	if ( !TRUEP(next_queue_element))
	    goto end_loop;
	element = ISVREF(next_queue_element,(SI_Long)4L);
	next_queue_element = constant_queue_next(next_queue_element,queue);
	if (element)
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(FIX(ab_loopvar_));
	return VALUES_1(Qnil);
    }
}

/* CONSTANT-QUEUE-NREVERSE */
Object constant_queue_nreverse(constant_queue)
    Object constant_queue;
{
    Object new_constant_queue, queue, next_queue_element, block, temp;

    x_note_fn_call(24,143);
    new_constant_queue = make_empty_constant_queue();
    queue = constant_queue;
    next_queue_element = Nil;
    block = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    block = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
    constant_queue_push_left(new_constant_queue,block);
    goto next_loop;
  end_loop:
    reclaim_constant_queue(constant_queue);
    temp = new_constant_queue;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-NTH */
Object constant_queue_nth(n_1,constant_queue)
    Object n_1, constant_queue;
{
    Object queue, next_queue_element, block, temp;
    SI_Long count_1;

    x_note_fn_call(24,144);
    count_1 = (SI_Long)0L;
    queue = constant_queue;
    next_queue_element = Nil;
    block = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    block = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
    if (count_1 == IFIX(n_1)) {
	temp = block;
	goto end_1;
    }
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object The_type_description_of_lru_element = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_lru_elements, Qchain_of_available_lru_elements);

DEFINE_VARIABLE_WITH_SYMBOL(Lru_element_count, Qlru_element_count);

Object Chain_of_available_lru_elements_vector = UNBOUND;

/* LRU-ELEMENT-STRUCTURE-MEMORY-USAGE */
Object lru_element_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,145);
    temp = Lru_element_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LRU-ELEMENT-COUNT */
Object outstanding_lru_element_count()
{
    Object def_structure_lru_element_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,146);
    gensymed_symbol = IFIX(Lru_element_count);
    def_structure_lru_element_variable = Chain_of_available_lru_elements;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_lru_element_variable))
	goto end_loop;
    def_structure_lru_element_variable = 
	    ISVREF(def_structure_lru_element_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LRU-ELEMENT-1 */
Object reclaim_lru_element_1(lru_element)
    Object lru_element;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(24,147);
    inline_note_reclaim_cons(lru_element,Nil);
    structure_being_reclaimed = lru_element;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      remove_lru_element(ISVREF(lru_element,(SI_Long)1L));
      SVREF(lru_element,FIX((SI_Long)1L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_lru_elements_vector,
	    IFIX(Current_thread_index));
    SVREF(lru_element,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_lru_elements_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = lru_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LRU-ELEMENT */
Object reclaim_structure_for_lru_element(lru_element)
    Object lru_element;
{
    x_note_fn_call(24,148);
    return reclaim_lru_element_1(lru_element);
}

static Object Qg2_defstruct_structure_name_lru_element_g2_struct;  /* g2-defstruct-structure-name::lru-element-g2-struct */

/* MAKE-PERMANENT-LRU-ELEMENT-STRUCTURE-INTERNAL */
Object make_permanent_lru_element_structure_internal()
{
    Object def_structure_lru_element_variable;
    Object defstruct_g2_lru_element_variable, the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,149);
    def_structure_lru_element_variable = Nil;
    atomic_incff_symval(Qlru_element_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_lru_element_variable = Nil;
	gensymed_symbol_1 = (SI_Long)3L;
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
	defstruct_g2_lru_element_variable = the_array;
	SVREF(defstruct_g2_lru_element_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_lru_element_g2_struct;
	def_structure_lru_element_variable = defstruct_g2_lru_element_variable;
	SVREF(def_structure_lru_element_variable,FIX((SI_Long)1L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_lru_elements_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_lru_element_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_lru_elements_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_lru_element_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_lru_element_variable);
}

/* MAKE-LRU-ELEMENT-1 */
Object make_lru_element_1()
{
    Object def_structure_lru_element_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,150);
    def_structure_lru_element_variable = 
	    ISVREF(Chain_of_available_lru_elements_vector,
	    IFIX(Current_thread_index));
    if (def_structure_lru_element_variable) {
	svref_arg_1 = Chain_of_available_lru_elements_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_lru_element_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_lru_element_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_lru_element_g2_struct;
    }
    else
	def_structure_lru_element_variable = 
		make_permanent_lru_element_structure_internal();
    inline_note_allocate_cons(def_structure_lru_element_variable,Nil);
    return VALUES_1(def_structure_lru_element_variable);
}

/* REMOVE-LRU-ELEMENT */
Object remove_lru_element(next_element)
    Object next_element;
{
    Object previous_element;

    x_note_fn_call(24,151);
    if ( !(SIMPLE_VECTOR_P(Structure_being_reclaimed) && 
	    EQ(ISVREF(Structure_being_reclaimed,(SI_Long)0L),
	    Qg2_defstruct_structure_name_lru_element_g2_struct))) {
	next_element = ISVREF(Structure_being_reclaimed,(SI_Long)1L);
	previous_element = ISVREF(Structure_being_reclaimed,(SI_Long)2L);
	SVREF(previous_element,FIX((SI_Long)1L)) = next_element;
	SVREF(next_element,FIX((SI_Long)2L)) = previous_element;
    }
    return VALUES_1(Nil);
}

/* MAKE-LRU-QUEUE */
Object make_lru_queue()
{
    Object new_queue;

    x_note_fn_call(24,152);
    new_queue = make_lru_element_1();
    SVREF(new_queue,FIX((SI_Long)1L)) = new_queue;
    SVREF(new_queue,FIX((SI_Long)2L)) = new_queue;
    return VALUES_1(new_queue);
}

/* INSTALL-LRU-ELEMENT-IN-QUEUE */
Object install_lru_element_in_queue(lru_element,lru_queue)
    Object lru_element, lru_queue;
{
    Object previous_tail;

    x_note_fn_call(24,153);
    previous_tail = ISVREF(lru_queue,(SI_Long)2L);
    SVREF(previous_tail,FIX((SI_Long)1L)) = lru_element;
    SVREF(lru_queue,FIX((SI_Long)2L)) = lru_element;
    SVREF(lru_element,FIX((SI_Long)1L)) = lru_queue;
    SVREF(lru_element,FIX((SI_Long)2L)) = previous_tail;
    return VALUES_1(lru_element);
}

DEFINE_VARIABLE_WITH_SYMBOL(Memory_limit_variable_names_for_decacheable_structures, Qmemory_limit_variable_names_for_decacheable_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Names_and_sizes_for_decacheable_structures, Qnames_and_sizes_for_decacheable_structures);

Object Default_decacheable_structure_allocation_limit = UNBOUND;

Object Minimum_decacheable_structure_allocation_limit = UNBOUND;

Object The_type_description_of_memory_limit_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_memory_limit_infos, Qchain_of_available_memory_limit_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Memory_limit_info_count, Qmemory_limit_info_count);

Object Chain_of_available_memory_limit_infos_vector = UNBOUND;

/* MEMORY-LIMIT-INFO-STRUCTURE-MEMORY-USAGE */
Object memory_limit_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,154);
    temp = Memory_limit_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)9L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-MEMORY-LIMIT-INFO-COUNT */
Object outstanding_memory_limit_info_count()
{
    Object def_structure_memory_limit_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,155);
    gensymed_symbol = IFIX(Memory_limit_info_count);
    def_structure_memory_limit_info_variable = 
	    Chain_of_available_memory_limit_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_memory_limit_info_variable))
	goto end_loop;
    def_structure_memory_limit_info_variable = 
	    ISVREF(def_structure_memory_limit_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-MEMORY-LIMIT-INFO-1 */
Object reclaim_memory_limit_info_1(memory_limit_info)
    Object memory_limit_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,156);
    inline_note_reclaim_cons(memory_limit_info,Nil);
    temp = ISVREF(Chain_of_available_memory_limit_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(memory_limit_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_memory_limit_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = memory_limit_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-MEMORY-LIMIT-INFO */
Object reclaim_structure_for_memory_limit_info(memory_limit_info)
    Object memory_limit_info;
{
    x_note_fn_call(24,157);
    return reclaim_memory_limit_info_1(memory_limit_info);
}

static Object Qg2_defstruct_structure_name_memory_limit_info_g2_struct;  /* g2-defstruct-structure-name::memory-limit-info-g2-struct */

/* MAKE-PERMANENT-MEMORY-LIMIT-INFO-STRUCTURE-INTERNAL */
Object make_permanent_memory_limit_info_structure_internal()
{
    Object def_structure_memory_limit_info_variable;
    Object defstruct_g2_memory_limit_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,158);
    def_structure_memory_limit_info_variable = Nil;
    atomic_incff_symval(Qmemory_limit_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_memory_limit_info_variable = Nil;
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
	defstruct_g2_memory_limit_info_variable = the_array;
	SVREF(defstruct_g2_memory_limit_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_memory_limit_info_g2_struct;
	def_structure_memory_limit_info_variable = 
		defstruct_g2_memory_limit_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_memory_limit_info_variable);
}

/* MAKE-MEMORY-LIMIT-INFO-1 */
Object make_memory_limit_info_1()
{
    Object def_structure_memory_limit_info_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,159);
    def_structure_memory_limit_info_variable = 
	    ISVREF(Chain_of_available_memory_limit_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_memory_limit_info_variable) {
	temp = Chain_of_available_memory_limit_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_memory_limit_info_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_memory_limit_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_memory_limit_info_g2_struct;
    }
    else
	def_structure_memory_limit_info_variable = 
		make_permanent_memory_limit_info_structure_internal();
    inline_note_allocate_cons(def_structure_memory_limit_info_variable,Nil);
    ISVREF(def_structure_memory_limit_info_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    temp = Default_decacheable_structure_allocation_limit;
    SVREF(def_structure_memory_limit_info_variable,FIX((SI_Long)2L)) = temp;
    ISVREF(def_structure_memory_limit_info_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_memory_limit_info_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_memory_limit_info_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_memory_limit_info_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_memory_limit_info_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_memory_limit_info_variable,FIX((SI_Long)8L)) = Nil;
    return VALUES_1(def_structure_memory_limit_info_variable);
}

/* INITIALIZE-MEMORY-LIMIT-INFO */
Object initialize_memory_limit_info(sizes_qm,name)
    Object sizes_qm, name;
{
    Object size, ab_loop_list_, memory_limit_info, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(24,160);
    if (sizes_qm) {
	size = Nil;
	ab_loop_list_ = sizes_qm;
	memory_limit_info = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	size = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	memory_limit_info = make_memory_limit_info_1();
	SVREF(memory_limit_info,FIX((SI_Long)7L)) = size;
	SVREF(memory_limit_info,FIX((SI_Long)8L)) = name;
	ab_loopvar__2 = LIST_1(memory_limit_info);
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
    else
	return make_memory_limit_info_1();
}

/* GET-MEMORY-LIMIT-INFO-GIVEN-SIZE */
Object get_memory_limit_info_given_size(memory_limit_variable,size)
    Object memory_limit_variable, size;
{
    Object limit_info, ab_loop_list_, decacheable_structure_size;

    x_note_fn_call(24,161);
    limit_info = Nil;
    ab_loop_list_ = memory_limit_variable;
    decacheable_structure_size = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    limit_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    decacheable_structure_size = ISVREF(limit_info,(SI_Long)7L);
    if (FIXNUM_LE(size,decacheable_structure_size))
	return VALUES_1(limit_info);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-BRACKETING-SIZES */
Object get_bracketing_sizes(size,sizes)
    Object size, sizes;
{
    Object min_size, max_size, ab_loop_list_;

    x_note_fn_call(24,162);
    min_size = FIX((SI_Long)0L);
    max_size = Nil;
    ab_loop_list_ = sizes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    max_size = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_GT(size,min_size) && FIXNUM_LE(size,max_size))
	return VALUES_2(min_size,max_size);
    min_size = max_size;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Decache_occurred_since_last_update_qm, Qdecache_occurred_since_last_update_qm);

/* ACCUMULATE-THRASHING-COST-AND-DECACHE */
Object accumulate_thrashing_cost_and_decache(structure_to_decache_qm,
	    limit_info,cost_function_name,decaching_function_name)
    Object structure_to_decache_qm, limit_info, cost_function_name;
    Object decaching_function_name;
{
    Object temp, svref_new_value;

    x_note_fn_call(24,163);
    temp = FUNCALL_1(cost_function_name,structure_to_decache_qm);
    svref_new_value = add(temp,ISVREF(limit_info,(SI_Long)3L));
    SVREF(limit_info,FIX((SI_Long)3L)) = svref_new_value;
    return FUNCALL_1(decaching_function_name,structure_to_decache_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_desired_thrashing_setpoint, Qglobal_desired_thrashing_setpoint);

DEFINE_VARIABLE_WITH_SYMBOL(Time_of_last_thrashing_cost_update, Qtime_of_last_thrashing_cost_update);

DEFINE_VARIABLE_WITH_SYMBOL(Thrashing_cost_update_interval, Qthrashing_cost_update_interval);

DEFINE_VARIABLE_WITH_SYMBOL(Long_thrashing_cost_update_interval, Qlong_thrashing_cost_update_interval);

/* UPDATE-MEMORY-LIMITS-NOW */
Object update_memory_limits_now(fixnum_time_now)
    Object fixnum_time_now;
{
    Object memory_limit_variable_name, ab_loop_list_, memory_limit_info;
    Object limit_info_for_size, ab_loop_list__1;
    SI_Long time_since_last_update, gensymed_symbol;

    x_note_fn_call(24,164);
    if (FIXNUM_GE(fixnum_time_now,Time_of_last_thrashing_cost_update))
	time_since_last_update = IFIX(FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update));
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	time_since_last_update = gensymed_symbol + (SI_Long)1L;
    }
    memory_limit_variable_name = Nil;
    ab_loop_list_ = Memory_limit_variable_names_for_decacheable_structures;
    memory_limit_info = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    memory_limit_variable_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    memory_limit_info = SYMBOL_VALUE(memory_limit_variable_name);
    if (ATOM(memory_limit_info))
	apply_memory_limit_control_law(memory_limit_info,
		FIX(time_since_last_update));
    else {
	limit_info_for_size = Nil;
	ab_loop_list__1 = memory_limit_info;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	limit_info_for_size = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	apply_memory_limit_control_law(limit_info_for_size,
		FIX(time_since_last_update));
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    Time_of_last_thrashing_cost_update = fixnum_time_now;
    Decache_occurred_since_last_update_qm = Nil;
    return VALUES_1(Nil);
}

/* UPDATE-MEMORY-LIMITS */
Object update_memory_limits(fixnum_time_now)
    Object fixnum_time_now;
{
    Object temp;
    SI_Long gensymed_symbol;

    x_note_fn_call(24,165);
    if (FIXNUM_GE(fixnum_time_now,Time_of_last_thrashing_cost_update))
	temp = FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(fixnum_time_now,
		Time_of_last_thrashing_cost_update));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GT(temp,Decache_occurred_since_last_update_qm ? 
	    Thrashing_cost_update_interval : 
	    Long_thrashing_cost_update_interval))
	return update_memory_limits_now(fixnum_time_now);
    else
	return VALUES_1(Nil);
}

Object Positive_thrashing_error_gain = UNBOUND;

Object Negative_thrashing_error_gain = UNBOUND;

/* APPLY-MEMORY-LIMIT-CONTROL-LAW */
Object apply_memory_limit_control_law(memory_limit_info,time_since_last_update)
    Object memory_limit_info, time_since_last_update;
{
    Object newest_thrashing_ratio, filtered_thrashing_ratio, limit;
    Object thrashing_error, temp, svref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(24,166);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = compute_newest_thrashing_ratio(memory_limit_info,
		time_since_last_update);
	MVS_2(result,newest_thrashing_ratio,filtered_thrashing_ratio);
	limit = ISVREF(memory_limit_info,(SI_Long)2L);
	thrashing_error = minus(filtered_thrashing_ratio,
		Global_desired_thrashing_setpoint);
	temp = FIX((SI_Long)0L);
	if (NUM_GT(thrashing_error,temp)) {
	    svref_new_value = FIXNUM_ADD(limit,
		    l_round(ltimes(thrashing_error,
		    Positive_thrashing_error_gain),_));
	    SVREF(memory_limit_info,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp = FIX((SI_Long)0L);
	if (NUM_LT(thrashing_error,temp)) {
	    temp = FIXNUM_ADD(limit,l_round(ltimes(thrashing_error,
		    Negative_thrashing_error_gain),_));
	    svref_new_value = 
		    FIXNUM_MAX(Minimum_decacheable_structure_allocation_limit,
		    temp);
	    result = VALUES_1(SVREF(memory_limit_info,FIX((SI_Long)2L)) = 
		    svref_new_value);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_no_value, Qsimulation_no_value);

DEFINE_VARIABLE_WITH_SYMBOL(Combiners_for_defun_incremental, Qcombiners_for_defun_incremental);

DEFINE_VARIABLE_WITH_SYMBOL(Defun_incremental_compile_time_registry, Qdefun_incremental_compile_time_registry);

DEFINE_VARIABLE_WITH_SYMBOL(Defun_incremental_runtime_registry, Qdefun_incremental_runtime_registry);

DEFINE_VARIABLE_WITH_SYMBOL(Available_queue_item_conses, Qavailable_queue_item_conses);

DEFINE_VARIABLE_WITH_SYMBOL(Available_queue_item_conses_tail, Qavailable_queue_item_conses_tail);

Object Available_queue_item_conses_vector = UNBOUND;

Object Available_queue_item_conses_tail_vector = UNBOUND;

Object Queue_item_cons_counter_vector = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Queue_item_cons_counter, Qqueue_item_cons_counter);

/* OUTSTANDING-QUEUE-ITEM-CONSES */
Object outstanding_queue_item_conses()
{
    Object temp;

    x_note_fn_call(24,167);
    temp = FIXNUM_MINUS(Queue_item_cons_counter,
	    length(Available_queue_item_conses));
    return VALUES_1(temp);
}

/* QUEUE-ITEM-CONS-MEMORY-USAGE */
Object queue_item_cons_memory_usage()
{
    Object temp;

    x_note_fn_call(24,168);
    temp = FIXNUM_TIMES(Queue_item_cons_counter,ltimes(FIX((SI_Long)2L),
	    Bytes_per_rtl_ptr));
    return VALUES_1(temp);
}

/* REPLENISH-QUEUE-ITEM-CONS-POOL */
Object replenish_queue_item_cons_pool()
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value, incff_1_arg;
    XDeclare_area(1);

    x_note_fn_call(24,169);
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,Cons_pool_conses_to_make_at_a_time);
    POP_AREA(0);
    new_conses = gensymed_symbol;
    atomic_incff_symval(Qqueue_item_cons_counter,
	    Cons_pool_conses_to_make_at_a_time);
    if (ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(CDR(new_conses),
		ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(new_conses);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	svref_arg_1 = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    svref_arg_1 = Queue_item_cons_counter_vector;
    svref_arg_2 = Current_thread_index;
    incff_1_arg = FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time);
    svref_new_value = FIXNUM_ADD(ISVREF(svref_arg_1,IFIX(svref_arg_2)),
	    incff_1_arg);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    return VALUES_1(new_conses);
}

static Object Qqueue_item;         /* queue-item */

/* QUEUE-ITEM-CONS-1 */
Object queue_item_cons_1(car_1,cdr_1)
    Object car_1, cdr_1;
{
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(24,170);
    new_cons = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_queue_item_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_queue_item_cons_pool();
    M_CAR(gensymed_symbol) = car_1;
    M_CDR(gensymed_symbol) = cdr_1;
    inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
    return VALUES_1(gensymed_symbol);
}

/* REPLENISH-QUEUE-ITEM-LIST-POOL */
Object replenish_queue_item_list_pool(conses_needed_minus_one)
    Object conses_needed_minus_one;
{
    Object gensymed_symbol, new_conses, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long conses_needed, temp, new_conses_count;
    XDeclare_area(1);

    x_note_fn_call(24,171);
    conses_needed = IFIX(FIXNUM_ADD1(conses_needed_minus_one));
    temp = (conses_needed + 
	    IFIX(FIXNUM_SUB1(Cons_pool_conses_to_make_at_a_time))) / 
	    IFIX(Cons_pool_conses_to_make_at_a_time);
    new_conses_count = temp;
    gensymed_symbol = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	gensymed_symbol = make_list(1,FIX(new_conses_count));
    POP_AREA(0);
    new_conses = gensymed_symbol;
    if (ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index))) {
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = nconc2(new_conses,
		ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index)));
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else {
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = new_conses;
	svref_arg_1 = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = last(new_conses,_);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    atomic_incff_symval(Qqueue_item_cons_counter,FIX(new_conses_count));
    return VALUES_1(Nil);
}

/* MAKE-QUEUE-ITEM-LIST-1 */
Object make_queue_item_list_1(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, svref_arg_1, svref_arg_2;
    Object svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(24,172);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_queue_item_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = ISVREF(Available_queue_item_conses_vector,
		    IFIX(Current_thread_index));
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
	svref_arg_1 = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = CDR(gensymed_symbol_1);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_queue_item_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	M_CDR(gensymed_symbol_1) = Nil;
	goto end_2;
	temp = Qnil;
      end_2:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* QUEUE-ITEM-LIST-2 */
Object queue_item_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,173);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_queue_item_list_pool(FIX((SI_Long)1L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qqueue_item);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_queue_item_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* QUEUE-ITEM-LIST-3 */
Object queue_item_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,174);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_queue_item_list_pool(FIX((SI_Long)2L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qqueue_item);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_queue_item_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* QUEUE-ITEM-LIST-4 */
Object queue_item_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, temp, gensymed_symbol_1, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,175);
    gensymed_symbol = Nil;
  next_loop:
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    temp = CDR(temp);
    temp = CDR(temp);
    gensymed_symbol = CDR(temp);
    if (gensymed_symbol)
	goto end_loop;
    replenish_queue_item_list_pool(FIX((SI_Long)3L));
    goto next_loop;
  end_loop:
    if ( !((SI_Long)0L == inline_debugging_consing())) {
	gensymed_symbol_1 = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
      next_loop_1:
	inline_note_allocate_cons(gensymed_symbol_1,Qqueue_item);
	if (EQ(gensymed_symbol_1,gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:;
    }
    temp = ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index));
    svref_arg_1 = Available_queue_item_conses_vector;
    svref_arg_2 = Current_thread_index;
    svref_new_value = CDR(gensymed_symbol);
    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
	    IFIX(Current_thread_index)))) {
	svref_arg_1 = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    M_CDR(gensymed_symbol) = Nil;
    gensymed_symbol = temp;
    goto end_1;
    gensymed_symbol = Qnil;
  end_1:;
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* QUEUE-ITEM-LIST-TRACE-HOOK */
Object queue_item_list_trace_hook(a_list)
    Object a_list;
{
    x_note_fn_call(24,176);
    return VALUES_1(a_list);
}

/* COPY-TREE-USING-QUEUE-ITEM-CONSES-1 */
Object copy_tree_using_queue_item_conses_1(tree_qm)
    Object tree_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,177);
    if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	new_cons = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_queue_item_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_queue_item_cons_pool();
	temp_1 = copy_tree_using_queue_item_conses_1(CAR(tree_qm));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(tree_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_queue_item_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_queue_item_cons_pool();
	temp_1 = 
		copy_tree_using_queue_item_conses_1(CAR(current_copy_position));
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* COPY-LIST-USING-QUEUE-ITEM-CONSES-1 */
Object copy_list_using_queue_item_conses_1(list_qm)
    Object list_qm;
{
    Object temp, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol, new_list, last_new_cons, current_copy_position;

    x_note_fn_call(24,178);
    if (ATOM(list_qm))
	temp = list_qm;
    else {
	new_cons = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_queue_item_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_queue_item_cons_pool();
	temp_1 = CAR(list_qm);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(list_qm);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
	new_list = gensymed_symbol;
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	new_cons = ISVREF(Available_queue_item_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_queue_item_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_queue_item_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_queue_item_cons_pool();
	temp_1 = CAR(current_copy_position);
	M_CAR(gensymed_symbol) = temp_1;
	temp_1 = CDR(current_copy_position);
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qqueue_item);
	M_CDR(last_new_cons) = gensymed_symbol;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* RECLAIM-QUEUE-ITEM-CONS-1 */
Object reclaim_queue_item_cons_1(queue_item_cons)
    Object queue_item_cons;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,179);
    inline_note_reclaim_cons(queue_item_cons,Qqueue_item);
    if (ISVREF(Available_queue_item_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_queue_item_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = queue_item_cons;
	temp = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = queue_item_cons;
    }
    else {
	temp = Available_queue_item_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = queue_item_cons;
	temp = Available_queue_item_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = queue_item_cons;
    }
    M_CDR(queue_item_cons) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-QUEUE-ITEM-LIST-1 */
Object reclaim_queue_item_list_1(queue_item_list)
    Object queue_item_list;
{
    Object last_1, next_qm, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,180);
    if (queue_item_list) {
	last_1 = queue_item_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qqueue_item);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qqueue_item);
	if (ISVREF(Available_queue_item_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_queue_item_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = queue_item_list;
	    temp = Available_queue_item_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_queue_item_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = queue_item_list;
	    temp = Available_queue_item_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-QUEUE-ITEM-LIST*-1 */
Object reclaim_queue_item_list_star_1(queue_item_list)
    Object queue_item_list;
{
    Object temp, last_1, next_qm, svref_arg_2, temp_1;

    x_note_fn_call(24,181);
    if (CONSP(queue_item_list)) {
	temp = last(queue_item_list,_);
	M_CDR(temp) = Nil;
	if (queue_item_list) {
	    last_1 = queue_item_list;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qqueue_item);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qqueue_item);
	    if (ISVREF(Available_queue_item_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_queue_item_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = queue_item_list;
		temp = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_queue_item_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = queue_item_list;
		temp = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-QUEUE-ITEM-TREE-1 */
Object reclaim_queue_item_tree_1(tree)
    Object tree;
{
    Object e, e2, queue_item_cons, temp, svref_arg_2, temp_1;

    x_note_fn_call(24,182);
    if (CONSP(tree)) {
	e = tree;
      next_loop:
	reclaim_queue_item_tree_1(M_CAR(e));
	e2 = M_CDR(e);
	if (CONSP(e2))
	    e = e2;
	else {
	    if (tree &&  !((SI_Long)0L == inline_debugging_consing())) {
		queue_item_cons = tree;
	      next_loop_1:
		inline_note_reclaim_cons(queue_item_cons,Qqueue_item);
		if (EQ(queue_item_cons,e))
		    goto end_1;
		else if ( !TRUEP(queue_item_cons))
		    goto end_1;
		else
		    queue_item_cons = CDR(queue_item_cons);
		goto next_loop_1;
	      end_loop:
	      end_1:;
	    }
	    if (ISVREF(Available_queue_item_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_queue_item_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = tree;
		temp = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    else {
		temp = Available_queue_item_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = tree;
		temp = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = e;
	    }
	    M_CDR(e) = Nil;
	    goto end_loop_1;
	}
	goto next_loop;
      end_loop_1:
	temp_1 = Qnil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* DELETE-QUEUE-ITEM-ELEMENT-1 */
Object delete_queue_item_element_1(element,queue_item_list)
    Object element, queue_item_list;
{
    Object temp, temp_1, svref_arg_2, l_trailer_qm, l;

    x_note_fn_call(24,183);
    if (queue_item_list) {
	if (EQ(element,M_CAR(queue_item_list))) {
	    temp = CDR(queue_item_list);
	    inline_note_reclaim_cons(queue_item_list,Qqueue_item);
	    if (ISVREF(Available_queue_item_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_queue_item_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = queue_item_list;
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = queue_item_list;
	    }
	    else {
		temp_1 = Available_queue_item_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = queue_item_list;
		temp_1 = Available_queue_item_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = queue_item_list;
	    }
	    M_CDR(queue_item_list) = Nil;
	}
	else {
	    l_trailer_qm = Nil;
	    l = queue_item_list;
	  next_loop:
	    if ( !TRUEP(l))
		goto end_loop;
	    if (EQ(element,M_CAR(l))) {
		temp_1 = M_CDR(l);
		M_CDR(l_trailer_qm) = temp_1;
		inline_note_reclaim_cons(l,Qqueue_item);
		if (ISVREF(Available_queue_item_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_queue_item_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = l;
		    temp_1 = Available_queue_item_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		else {
		    temp_1 = Available_queue_item_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		    temp_1 = Available_queue_item_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = l;
		}
		M_CDR(l) = Nil;
		goto end_loop;
	    }
	    l_trailer_qm = l;
	    l = M_CDR(l);
	    goto next_loop;
	  end_loop:
	    temp = queue_item_list;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DELETE-QUEUE-ITEM-CONS-1 */
Object delete_queue_item_cons_1(queue_item_cons,queue_item_list)
    Object queue_item_cons, queue_item_list;
{
    Object temp, l_trailer_qm, l, cdr_new_value;

    x_note_fn_call(24,184);
    if (EQ(queue_item_cons,queue_item_list))
	temp = CDR(queue_item_list);
    else {
	l_trailer_qm = Nil;
	l = queue_item_list;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if (EQ(l,queue_item_cons)) {
	    cdr_new_value = CDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	    temp = queue_item_list;
	    goto end_1;
	}
	l_trailer_qm = l;
	l = M_CDR(l);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    reclaim_queue_item_cons_1(queue_item_cons);
    return VALUES_1(temp);
}

Object The_type_description_of_queue = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_queues, Qchain_of_available_queues);

DEFINE_VARIABLE_WITH_SYMBOL(Queue_count, Qqueue_count);

Object Chain_of_available_queues_vector = UNBOUND;

/* QUEUE-STRUCTURE-MEMORY-USAGE */
Object queue_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(24,185);
    temp = Queue_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-QUEUE-COUNT */
Object outstanding_queue_count()
{
    Object def_structure_queue_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(24,186);
    gensymed_symbol = IFIX(Queue_count);
    def_structure_queue_variable = Chain_of_available_queues;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_queue_variable))
	goto end_loop;
    def_structure_queue_variable = ISVREF(def_structure_queue_variable,
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

/* RECLAIM-QUEUE-INTERNAL-1 */
Object reclaim_queue_internal_1(queue)
    Object queue;
{
    Object temp, svref_arg_2;

    x_note_fn_call(24,187);
    inline_note_reclaim_cons(queue,Nil);
    temp = ISVREF(Chain_of_available_queues_vector,IFIX(Current_thread_index));
    SVREF(queue,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_queues_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = queue;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-QUEUE */
Object reclaim_structure_for_queue(queue)
    Object queue;
{
    x_note_fn_call(24,188);
    return reclaim_queue_internal_1(queue);
}

static Object Qg2_defstruct_structure_name_queue_g2_struct;  /* g2-defstruct-structure-name::queue-g2-struct */

/* MAKE-PERMANENT-QUEUE-STRUCTURE-INTERNAL */
Object make_permanent_queue_structure_internal()
{
    Object def_structure_queue_variable, defstruct_g2_queue_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(24,189);
    def_structure_queue_variable = Nil;
    atomic_incff_symval(Qqueue_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_queue_variable = Nil;
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
	defstruct_g2_queue_variable = the_array;
	SVREF(defstruct_g2_queue_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_queue_g2_struct;
	def_structure_queue_variable = defstruct_g2_queue_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_queue_variable);
}

/* MAKE-QUEUE-INTERNAL-1 */
Object make_queue_internal_1(queue_head_internal,queue_tail_internal)
    Object queue_head_internal, queue_tail_internal;
{
    Object def_structure_queue_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(24,190);
    def_structure_queue_variable = ISVREF(Chain_of_available_queues_vector,
	    IFIX(Current_thread_index));
    if (def_structure_queue_variable) {
	svref_arg_1 = Chain_of_available_queues_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_queue_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_queue_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_queue_g2_struct;
    }
    else
	def_structure_queue_variable = 
		make_permanent_queue_structure_internal();
    inline_note_allocate_cons(def_structure_queue_variable,Nil);
    SVREF(def_structure_queue_variable,FIX((SI_Long)1L)) = queue_head_internal;
    SVREF(def_structure_queue_variable,FIX((SI_Long)2L)) = queue_tail_internal;
    return VALUES_1(def_structure_queue_variable);
}

/* MAKE-QUEUE */
Object make_queue()
{
    x_note_fn_call(24,191);
    return make_queue_internal_1(Nil,Nil);
}

/* RECLAIM-QUEUE */
Object reclaim_queue(queue)
    Object queue;
{
    x_note_fn_call(24,192);
    clear_queue(queue);
    return reclaim_queue_internal_1(queue);
}

/* QUEUE-EMPTY-P */
Object queue_empty_p(queue)
    Object queue;
{
    x_note_fn_call(24,193);
    return VALUES_1( !TRUEP(ISVREF(queue,(SI_Long)1L)) ? T : Nil);
}

/* QUEUE-NON-EMPTY-P */
Object queue_non_empty_p(queue)
    Object queue;
{
    x_note_fn_call(24,194);
    return VALUES_1(ISVREF(queue,(SI_Long)1L));
}

/* CLEAR-QUEUE */
Object clear_queue(queue)
    Object queue;
{
    x_note_fn_call(24,195);
    if (ISVREF(queue,(SI_Long)1L))
	reclaim_queue_item_list_1(ISVREF(queue,(SI_Long)1L));
    SVREF(queue,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(SVREF(queue,FIX((SI_Long)2L)) = Nil);
}

/* QUEUE-INSERT */
Object queue_insert(queue,element)
    Object queue, element;
{
    Object gensymed_symbol, first_1, last_1, temp, next;

    x_note_fn_call(24,196);
    gensymed_symbol = element;
    gensymed_symbol = queue_item_cons_1(gensymed_symbol,Nil);
  next_loop:
    first_1 = ISVREF(queue,(SI_Long)1L);
    last_1 = ISVREF(queue,(SI_Long)2L);
    temp = ISVREF(queue,(SI_Long)2L);
    next = CDR(temp);
    if ( !TRUEP(first_1)) {
	if (CAS_SVREF(queue,(SI_Long)1L,first_1,gensymed_symbol)) {
	    CAS_SVREF(queue,(SI_Long)2L,last_1,gensymed_symbol);
	    return VALUES_1(gensymed_symbol);
	}
    }
    else if (EQ(last_1,ISVREF(queue,(SI_Long)2L))) {
	if ( !TRUEP(next)) {
	    if (CAS_CDR(last_1,next,gensymed_symbol)) {
		CAS_SVREF(queue,(SI_Long)2L,last_1,gensymed_symbol);
		return VALUES_1(gensymed_symbol);
	    }
	}
	else
	    CAS_SVREF(queue,(SI_Long)2L,last_1,next);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* QUEUE-PUSH */
Object queue_push(queue,element)
    Object queue, element;
{
    Object queue_item_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object gensymed_symbol, first_1, last_1, temp, next;

    x_note_fn_call(24,197);
    if (ISVREF(queue,(SI_Long)1L)) {
	queue_item_push_modify_macro_arg = element;
	car_1 = queue_item_push_modify_macro_arg;
	cdr_1 = ISVREF(queue,(SI_Long)1L);
	svref_new_value = queue_item_cons_1(car_1,cdr_1);
	SVREF(queue,FIX((SI_Long)1L)) = svref_new_value;
    }
    else {
	gensymed_symbol = element;
	gensymed_symbol = queue_item_cons_1(gensymed_symbol,Nil);
      next_loop:
	first_1 = ISVREF(queue,(SI_Long)1L);
	last_1 = ISVREF(queue,(SI_Long)2L);
	temp = ISVREF(queue,(SI_Long)2L);
	next = CDR(temp);
	if ( !TRUEP(first_1)) {
	    if (CAS_SVREF(queue,(SI_Long)1L,first_1,gensymed_symbol)) {
		CAS_SVREF(queue,(SI_Long)2L,last_1,gensymed_symbol);
		goto end_1;
	    }
	}
	else if (EQ(last_1,ISVREF(queue,(SI_Long)2L))) {
	    if ( !TRUEP(next)) {
		if (CAS_CDR(last_1,next,gensymed_symbol)) {
		    CAS_SVREF(queue,(SI_Long)2L,last_1,gensymed_symbol);
		    goto end_1;
		}
	    }
	    else
		CAS_SVREF(queue,(SI_Long)2L,last_1,next);
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(element);
}

/* QUEUE-POP */
Object queue_pop(queue)
    Object queue;
{
    Object first_1, last_1, next, gensymed_symbol;

    x_note_fn_call(24,198);
  next_loop:
    first_1 = ISVREF(queue,(SI_Long)1L);
    last_1 = ISVREF(queue,(SI_Long)2L);
    next = CDR(first_1);
    if ( !TRUEP(first_1))
	return VALUES_1(Nil);
    else if (EQ(first_1,ISVREF(queue,(SI_Long)1L))) {
	if (EQ(first_1,last_1))
	    CAS_SVREF(queue,(SI_Long)2L,last_1,next);
	else {
	    gensymed_symbol = CAR(first_1);
	    if (CAS_SVREF(queue,(SI_Long)1L,first_1,next)) {
		reclaim_queue_item_cons_1(first_1);
		return VALUES_1(gensymed_symbol);
	    }
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* QUEUE-PEEK */
Object queue_peek(queue)
    Object queue;
{
    Object temp;

    x_note_fn_call(24,199);
    temp = ISVREF(queue,(SI_Long)1L);
    return VALUES_1(CAR(temp));
}

/* QUEUE-LENGTH */
Object queue_length(queue)
    Object queue;
{
    Object length_1, sublist, element;

    x_note_fn_call(24,200);
    length_1 = FIX((SI_Long)0L);
    sublist = ISVREF(queue,(SI_Long)1L);
    element = Nil;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    element = M_CAR(sublist);
    length_1 = FIXNUM_ADD1(length_1);
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:;
    return VALUES_1(length_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_flags, Qcurrent_computation_flags);

Object Special_setf_method_prop = UNBOUND;

void utilities2_INIT()
{
    Object temp, reclaim_structure_for_named_gensym_structure_1;
    Object reclaim_structure_for_type_description_1;
    Object reclaim_structure_for_binary_tree_element_1;
    Object reclaim_structure_for_skip_list_element_1;
    Object reclaim_structure_for_sparse_array_1;
    Object reclaim_structure_for_index_space_1;
    Object reclaim_structure_for_queue_element_1;
    Object reclaim_structure_for_lru_element_1;
    Object reclaim_structure_for_memory_limit_info_1;
    Object reclaim_structure_for_queue_1;
    Object Qspecial_setf_method, Qset_serve_loose_ends_p, Qserve_loose_ends_p;
    Object AB_package, Qset_serve_only_permanent_items_p;
    Object Qserve_only_permanent_items_p;
    Object Qset_within_dynamic_extent_of_traced_rule_p;
    Object Qwithin_dynamic_extent_of_traced_rule_p;
    Object Qset_dont_forward_chain_from_rule, Qdont_forward_chain_from_rule;
    Object Qset_dont_compute_new_variable_values;
    Object Qdont_compute_new_variable_values;
    Object Qset_default_dont_compute_new_variable_values;
    Object Qdefault_dont_compute_new_variable_values;
    Object Qset_attempting_network_read_access_p;
    Object Qattempting_network_read_access_p;
    Object Qset_attempting_network_write_access_p;
    Object Qattempting_network_write_access_p;
    Object Qset_role_serve_inactive_objects_qm;
    Object Qrole_serve_inactive_objects_qm;
    Object Qset_no_wake_ups_during_role_serving;
    Object Qno_wake_ups_during_role_serving, Qset_force_new_request_for_value;
    Object Qforce_new_request_for_value, Qset_final_evaluation_attempt_qm;
    Object Qfinal_evaluation_attempt_qm, Qset_cache_explanation_variables_qm;
    Object Qcache_explanation_variables_qm, Qutilities2, Qqueue;
    Object Qreclaim_structure, Qoutstanding_queue_count;
    Object Qqueue_structure_memory_usage, string_constant_24;
    Object string_constant_23, Qunique_structure_type_of_ab_name_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_22;
    Object Qqueue_item_cons_memory_usage, Qoutstanding_queue_item_conses;
    Object Qutilities1, list_constant_1, Qqueue_item_cons_counter_vector;
    Object list_constant, Qavailable_queue_item_conses_tail_vector;
    Object Qavailable_queue_item_conses_vector, list_constant_9;
    Object string_constant_21, Kfuncall, list_constant_8;
    Object Qfixnum_time_interval, list_constant_7, list_constant_6;
    Object Qget_fixnum_time_function, Qmemory_limit_info;
    Object Qoutstanding_memory_limit_info_count;
    Object Qmemory_limit_info_structure_memory_usage, string_constant_20;
    Object string_constant_19, Qlru_element, Qoutstanding_lru_element_count;
    Object Qlru_element_structure_memory_usage, string_constant_18;
    Object string_constant_17, list_constant_5, Qconstant_queue_tail_marker;
    Object list_constant_4, Qconstant_queue_head_marker, list_constant_3;
    Object Qconstant_queue_marker, Qqueue_element;
    Object Qoutstanding_queue_element_count;
    Object Qqueue_element_structure_memory_usage, string_constant_16;
    Object Qg2_defstruct_structure_name_queue_element_g2_struct;
    Object string_constant_15, string_constant_14;
    Object Qenlarge_index_space_error_message, Qindex_space;
    Object Qoutstanding_index_space_count, Qindex_space_structure_memory_usage;
    Object string_constant_13, string_constant_12, Qsparse_array;
    Object Qoutstanding_sparse_array_count;
    Object Qsparse_array_structure_memory_usage, string_constant_11;
    Object string_constant_10, Qskip_list_global_max_level;
    Object Qhalf_of_most_positive_fixnum, Qskip_list_element;
    Object Qoutstanding_skip_list_element_count;
    Object Qskip_list_element_structure_memory_usage, string_constant_9;
    Object Qg2_defstruct_structure_name_skip_list_element_g2_struct;
    Object string_constant_8, list_constant_2, Qbinary_tree_branch;
    Object Qbinary_tree_ancestor, Qbinary_tree_element;
    Object Qoutstanding_binary_tree_element_count;
    Object Qbinary_tree_element_structure_memory_usage, string_constant_7;
    Object Qg2_defstruct_structure_name_binary_tree_element_g2_struct;
    Object string_constant_6, string_constant_5, Qlookup_cons_memory_usage;
    Object Qoutstanding_lookup_conses, Qlookup_cons_counter_vector;
    Object Qavailable_lookup_conses_tail_vector;
    Object Qavailable_lookup_conses_vector, string_constant_4;
    Object Qvector_pool_cons_memory_usage, Qoutstanding_vector_pool_conses;
    Object Qvector_pool_cons_counter_vector, Qmake_thread_array;
    Object Qavailable_vector_pool_conses_tail_vector;
    Object Qavailable_vector_pool_conses_vector, Qprint_type_description;
    Object Qtype_description, Qoutstanding_type_description_count;
    Object Qtype_description_structure_memory_usage, string_constant_3;
    Object string_constant_2, Qnamed_gensym_structure;
    Object Qoutstanding_named_gensym_structure_count;
    Object Qnamed_gensym_structure_structure_memory_usage, string_constant_1;
    Object string_constant, Qstructure_method_arglist;
    Object Qdef_structure_slot_descriptions;

    x_note_fn_call(24,201);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdef_structure_slot_descriptions = 
	    STATIC_SYMBOL("DEF-STRUCTURE-SLOT-DESCRIPTIONS",AB_package);
    Def_structure_slot_descriptions_prop = Qdef_structure_slot_descriptions;
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    Ab_name_of_unique_structure_type_prop = Qab_name_of_unique_structure_type;
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    Unique_structure_type_of_ab_name_qm_prop = 
	    Qunique_structure_type_of_ab_name_qm;
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    Qstructure_method_arglist = STATIC_SYMBOL("STRUCTURE-METHOD-ARGLIST",
	    AB_package);
    Structure_method_arglist_prop = Qstructure_method_arglist;
    Qstructure_being_reclaimed = STATIC_SYMBOL("STRUCTURE-BEING-RECLAIMED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstructure_being_reclaimed,
	    Structure_being_reclaimed);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qstructure_being_reclaimed,Qutilities2,Nil,Qnil,
	    Qt,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_named_gensym_structure_g2_struct = 
	    STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnamed_gensym_structure = STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    Qnamed_gensym_structure,Qab_name_of_unique_structure_type);
    mutate_global_property(Qnamed_gensym_structure,
	    Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_named_gensym_structure == UNBOUND)
	The_type_description_of_named_gensym_structure = Nil;
    string_constant = STATIC_STRING("43Dy8m8n1m8n8k1l8k0000001l1m8x0klk0k0");
    temp = The_type_description_of_named_gensym_structure;
    The_type_description_of_named_gensym_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    mutate_global_property(Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    The_type_description_of_named_gensym_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qnamed_gensym_structure,
	    The_type_description_of_named_gensym_structure,
	    Qtype_description_of_type);
    Qoutstanding_named_gensym_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-NAMED-GENSYM-STRUCTURE-COUNT",
	    AB_package);
    Qnamed_gensym_structure_structure_memory_usage = 
	    STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_1 = STATIC_STRING("1q8n8s83-g1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_named_gensym_structure_count);
    push_optimized_constant(Qnamed_gensym_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_named_gensym_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NAMED-GENSYM-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_named_gensym_structures,
	    Chain_of_available_named_gensym_structures);
    record_system_variable(Qchain_of_available_named_gensym_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qnamed_gensym_structure_count = 
	    STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnamed_gensym_structure_count,
	    Named_gensym_structure_count);
    record_system_variable(Qnamed_gensym_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_named_gensym_structures_vector == UNBOUND)
	Chain_of_available_named_gensym_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qnamed_gensym_structure_structure_memory_usage,
	    STATIC_FUNCTION(named_gensym_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_named_gensym_structure_count,
	    STATIC_FUNCTION(outstanding_named_gensym_structure_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_named_gensym_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_named_gensym_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qnamed_gensym_structure,
	    reclaim_structure_for_named_gensym_structure_1);
    Qg2_defstruct_structure_name_type_description_g2_struct = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtype_description = STATIC_SYMBOL("TYPE-DESCRIPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_type_description_g2_struct,
	    Qtype_description,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtype_description,
	    Qg2_defstruct_structure_name_type_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_type_description == UNBOUND)
	The_type_description_of_type_description = Nil;
    Qprint_type_description = STATIC_SYMBOL("PRINT-TYPE-DESCRIPTION",
	    AB_package);
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83o4y1n83o4y8n8k1l8n0000001n1m83=0y9k1m83=ey3Gy1m831uy831Jyk3Dyk0k0");
    temp = The_type_description_of_type_description;
    clear_optimized_constants();
    push_optimized_constant(Qprint_type_description);
    The_type_description_of_type_description = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    mutate_global_property(Qg2_defstruct_structure_name_type_description_g2_struct,
	    The_type_description_of_type_description,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtype_description,
	    The_type_description_of_type_description,
	    Qtype_description_of_type);
    Qoutstanding_type_description_count = 
	    STATIC_SYMBOL("OUTSTANDING-TYPE-DESCRIPTION-COUNT",AB_package);
    Qtype_description_structure_memory_usage = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_3 = STATIC_STRING("1q83o4y8s83-uay09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_type_description_count);
    push_optimized_constant(Qtype_description_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_type_descriptions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TYPE-DESCRIPTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_type_descriptions,
	    Chain_of_available_type_descriptions);
    record_system_variable(Qchain_of_available_type_descriptions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qtype_description_count = STATIC_SYMBOL("TYPE-DESCRIPTION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtype_description_count,Type_description_count);
    record_system_variable(Qtype_description_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_type_descriptions_vector == UNBOUND)
	Chain_of_available_type_descriptions_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtype_description_structure_memory_usage,
	    STATIC_FUNCTION(type_description_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_type_description_count,
	    STATIC_FUNCTION(outstanding_type_description_count,NIL,FALSE,0,0));
    reclaim_structure_for_type_description_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_type_description,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtype_description,
	    reclaim_structure_for_type_description_1);
    SET_SYMBOL_FUNCTION(Qprint_type_description,
	    STATIC_FUNCTION(print_type_description,NIL,FALSE,3,3));
    Qavailable_vector_pool_conses = 
	    STATIC_SYMBOL("AVAILABLE-VECTOR-POOL-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_vector_pool_conses,
	    Available_vector_pool_conses);
    record_system_variable(Qavailable_vector_pool_conses,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_vector_pool_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-VECTOR-POOL-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_vector_pool_conses_tail,
	    Available_vector_pool_conses_tail);
    record_system_variable(Qavailable_vector_pool_conses_tail,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_vector_pool_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-VECTOR-POOL-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_vector_pool_conses_vector,
	    Available_vector_pool_conses_vector);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qmake_thread_array = STATIC_SYMBOL("MAKE-THREAD-ARRAY",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,Qnil);
    record_system_variable(Qavailable_vector_pool_conses_vector,
	    Qutilities2,list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_vector_pool_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-VECTOR-POOL-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_vector_pool_conses_tail_vector,
	    Available_vector_pool_conses_tail_vector);
    record_system_variable(Qavailable_vector_pool_conses_tail_vector,
	    Qutilities2,list_constant,Qnil,Qt,Qnil,Qnil);
    Qvector_pool_cons_counter_vector = 
	    STATIC_SYMBOL("VECTOR-POOL-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_pool_cons_counter_vector,
	    Vector_pool_cons_counter_vector);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_thread_array,
	    FIX((SI_Long)0L));
    record_system_variable(Qvector_pool_cons_counter_vector,Qutilities2,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qvector_pool_cons_counter = STATIC_SYMBOL("VECTOR-POOL-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvector_pool_cons_counter,
	    Vector_pool_cons_counter);
    record_system_variable(Qvector_pool_cons_counter,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_vector_pool_conses = 
	    STATIC_SYMBOL("OUTSTANDING-VECTOR-POOL-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_vector_pool_conses,
	    STATIC_FUNCTION(outstanding_vector_pool_conses,NIL,FALSE,0,0));
    Qvector_pool_cons_memory_usage = 
	    STATIC_SYMBOL("VECTOR-POOL-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qvector_pool_cons_memory_usage,
	    STATIC_FUNCTION(vector_pool_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_4 = STATIC_STRING("1q83-wRy9k83-wQy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_vector_pool_conses);
    push_optimized_constant(Qvector_pool_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_4));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qavailable_lookup_conses = STATIC_SYMBOL("AVAILABLE-LOOKUP-CONSES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_lookup_conses,
	    Available_lookup_conses);
    Qutilities1 = STATIC_SYMBOL("UTILITIES1",AB_package);
    record_system_variable(Qavailable_lookup_conses,Qutilities1,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qavailable_lookup_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-LOOKUP-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_lookup_conses_tail,
	    Available_lookup_conses_tail);
    record_system_variable(Qavailable_lookup_conses_tail,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_lookup_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-LOOKUP-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_lookup_conses_vector,
	    Available_lookup_conses_vector);
    record_system_variable(Qavailable_lookup_conses_vector,Qutilities1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_lookup_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-LOOKUP-CONSES-TAIL-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_lookup_conses_tail_vector,
	    Available_lookup_conses_tail_vector);
    record_system_variable(Qavailable_lookup_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qlookup_cons_counter_vector = 
	    STATIC_SYMBOL("LOOKUP-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlookup_cons_counter_vector,
	    Lookup_cons_counter_vector);
    record_system_variable(Qlookup_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qlookup_cons_counter = STATIC_SYMBOL("LOOKUP-CONS-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlookup_cons_counter,Lookup_cons_counter);
    record_system_variable(Qlookup_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_lookup_conses = STATIC_SYMBOL("OUTSTANDING-LOOKUP-CONSES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_lookup_conses,
	    STATIC_FUNCTION(outstanding_lookup_conses,NIL,FALSE,0,0));
    Qlookup_cons_memory_usage = STATIC_SYMBOL("LOOKUP-CONS-MEMORY-USAGE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qlookup_cons_memory_usage,
	    STATIC_FUNCTION(lookup_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_5 = STATIC_STRING("1q83-dKy9k83-dJy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_lookup_conses);
    push_optimized_constant(Qlookup_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    if (The_type_description_of_binary_tree_element == UNBOUND)
	The_type_description_of_binary_tree_element = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83fLy1m83fLy8k1l8k0000001n1m83*gy9k1m83=ey3-Wy1n8y83-2qy1p83qYy83-2-y83--Yy83qXy83qKykpk0k0");
    temp = The_type_description_of_binary_tree_element;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_binary_tree_element = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    Qg2_defstruct_structure_name_binary_tree_element_g2_struct = 
	    STATIC_SYMBOL("BINARY-TREE-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_binary_tree_element_g2_struct,
	    The_type_description_of_binary_tree_element,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qbinary_tree_element = STATIC_SYMBOL("BINARY-TREE-ELEMENT",AB_package);
    mutate_global_property(Qbinary_tree_element,
	    The_type_description_of_binary_tree_element,
	    Qtype_description_of_type);
    Qoutstanding_binary_tree_element_count = 
	    STATIC_SYMBOL("OUTSTANDING-BINARY-TREE-ELEMENT-COUNT",AB_package);
    Qbinary_tree_element_structure_memory_usage = 
	    STATIC_SYMBOL("BINARY-TREE-ELEMENT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_7 = STATIC_STRING("1q83fLy8s83-Kmy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_binary_tree_element_count);
    push_optimized_constant(Qbinary_tree_element_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_binary_tree_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BINARY-TREE-ELEMENTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_binary_tree_elements,
	    Chain_of_available_binary_tree_elements);
    record_system_variable(Qchain_of_available_binary_tree_elements,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qbinary_tree_element_count = STATIC_SYMBOL("BINARY-TREE-ELEMENT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbinary_tree_element_count,
	    Binary_tree_element_count);
    record_system_variable(Qbinary_tree_element_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_binary_tree_elements_vector == UNBOUND)
	Chain_of_available_binary_tree_elements_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qbinary_tree_element_structure_memory_usage,
	    STATIC_FUNCTION(binary_tree_element_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_binary_tree_element_count,
	    STATIC_FUNCTION(outstanding_binary_tree_element_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_binary_tree_element_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_binary_tree_element,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qbinary_tree_element,
	    reclaim_structure_for_binary_tree_element_1);
    Qequal_rule_context = STATIC_SYMBOL("EQUAL-RULE-CONTEXT",AB_package);
    Qbinary_tree_ancestor = STATIC_SYMBOL("BINARY-TREE-ANCESTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbinary_tree_ancestor,Binary_tree_ancestor);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_array,
	    FIX((SI_Long)50L));
    record_system_variable(Qbinary_tree_ancestor,Qutilities2,
	    list_constant_2,Qnil,Qt,Qnil,Qnil);
    Qbinary_tree_branch = STATIC_SYMBOL("BINARY-TREE-BRANCH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbinary_tree_branch,Binary_tree_branch);
    record_system_variable(Qbinary_tree_branch,Qutilities2,list_constant_2,
	    Qnil,Qt,Qnil,Qnil);
    Kless_than = STATIC_SYMBOL("LESS-THAN",Pkeyword);
    Kgreater_than = STATIC_SYMBOL("GREATER-THAN",Pkeyword);
    if (The_type_description_of_skip_list_element == UNBOUND)
	The_type_description_of_skip_list_element = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83nCy1m83nCy8k1l8k0000001o1m83*gy9k1m83=ey3-Wy1n8y83-5qy1o83-D2y83-D3y83-D1y83-D4y1m83My83-B3ykpk0k0");
    temp = The_type_description_of_skip_list_element;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_skip_list_element = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    Qg2_defstruct_structure_name_skip_list_element_g2_struct = 
	    STATIC_SYMBOL("SKIP-LIST-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_skip_list_element_g2_struct,
	    The_type_description_of_skip_list_element,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qskip_list_element = STATIC_SYMBOL("SKIP-LIST-ELEMENT",AB_package);
    mutate_global_property(Qskip_list_element,
	    The_type_description_of_skip_list_element,
	    Qtype_description_of_type);
    Qoutstanding_skip_list_element_count = 
	    STATIC_SYMBOL("OUTSTANDING-SKIP-LIST-ELEMENT-COUNT",AB_package);
    Qskip_list_element_structure_memory_usage = 
	    STATIC_SYMBOL("SKIP-LIST-ELEMENT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q83nCy8s83-q0y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_skip_list_element_count);
    push_optimized_constant(Qskip_list_element_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_skip_list_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SKIP-LIST-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_skip_list_elements,
	    Chain_of_available_skip_list_elements);
    record_system_variable(Qchain_of_available_skip_list_elements,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qskip_list_element_count = STATIC_SYMBOL("SKIP-LIST-ELEMENT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qskip_list_element_count,
	    Skip_list_element_count);
    record_system_variable(Qskip_list_element_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_skip_list_elements_vector == UNBOUND)
	Chain_of_available_skip_list_elements_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qskip_list_element_structure_memory_usage,
	    STATIC_FUNCTION(skip_list_element_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_skip_list_element_count,
	    STATIC_FUNCTION(outstanding_skip_list_element_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_skip_list_element_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_skip_list_element,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qskip_list_element,
	    reclaim_structure_for_skip_list_element_1);
    Qhalf_of_most_positive_fixnum = 
	    STATIC_SYMBOL("HALF-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhalf_of_most_positive_fixnum,
	    Half_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qhalf_of_most_positive_fixnum,
	    chestnut_floorf_function(Most_positive_fixnum,FIX((SI_Long)2L)));
    Qskip_list_global_max_level = 
	    STATIC_SYMBOL("SKIP-LIST-GLOBAL-MAX-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qskip_list_global_max_level,FIX((SI_Long)32L));
    if (Skip_list_find_preds == UNBOUND)
	Skip_list_find_preds = make_array(1,Skip_list_global_max_level);
    if (Skip_list_find_succs == UNBOUND)
	Skip_list_find_succs = make_array(1,Skip_list_global_max_level);
    Qg2_defstruct_structure_name_sparse_array_g2_struct = 
	    STATIC_SYMBOL("SPARSE-ARRAY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsparse_array = STATIC_SYMBOL("SPARSE-ARRAY",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_sparse_array_g2_struct,
	    Qsparse_array,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsparse_array,
	    Qg2_defstruct_structure_name_sparse_array_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_sparse_array == UNBOUND)
	The_type_description_of_sparse_array = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83nKy1n83nKy8n8k1l8n0000001n1n8y83pdy01m83My83-B5y1m831uy831Jykok0k0");
    temp = The_type_description_of_sparse_array;
    The_type_description_of_sparse_array = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_sparse_array_g2_struct,
	    The_type_description_of_sparse_array,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsparse_array,
	    The_type_description_of_sparse_array,Qtype_description_of_type);
    Qoutstanding_sparse_array_count = 
	    STATIC_SYMBOL("OUTSTANDING-SPARSE-ARRAY-COUNT",AB_package);
    Qsparse_array_structure_memory_usage = 
	    STATIC_SYMBOL("SPARSE-ARRAY-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q83nKy8s83-qOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_sparse_array_count);
    push_optimized_constant(Qsparse_array_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_sparse_arrays = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SPARSE-ARRAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_sparse_arrays,
	    Chain_of_available_sparse_arrays);
    record_system_variable(Qchain_of_available_sparse_arrays,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qsparse_array_count = STATIC_SYMBOL("SPARSE-ARRAY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsparse_array_count,Sparse_array_count);
    record_system_variable(Qsparse_array_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_sparse_arrays_vector == UNBOUND)
	Chain_of_available_sparse_arrays_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsparse_array_structure_memory_usage,
	    STATIC_FUNCTION(sparse_array_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_sparse_array_count,
	    STATIC_FUNCTION(outstanding_sparse_array_count,NIL,FALSE,0,0));
    reclaim_structure_for_sparse_array_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_sparse_array,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsparse_array,
	    reclaim_structure_for_sparse_array_1);
    Qg2_defstruct_structure_name_index_space_g2_struct = 
	    STATIC_SYMBOL("INDEX-SPACE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qindex_space = STATIC_SYMBOL("INDEX-SPACE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_index_space_g2_struct,
	    Qindex_space,Qab_name_of_unique_structure_type);
    mutate_global_property(Qindex_space,
	    Qg2_defstruct_structure_name_index_space_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_index_space == UNBOUND)
	The_type_description_of_index_space = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83j-y1n83j-y8n8k1l8n0000001l1n8y83-4ay1m83-=Py83-=Qykrk0k0");
    temp = The_type_description_of_index_space;
    The_type_description_of_index_space = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    mutate_global_property(Qg2_defstruct_structure_name_index_space_g2_struct,
	    The_type_description_of_index_space,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qindex_space,
	    The_type_description_of_index_space,Qtype_description_of_type);
    Qoutstanding_index_space_count = 
	    STATIC_SYMBOL("OUTSTANDING-INDEX-SPACE-COUNT",AB_package);
    Qindex_space_structure_memory_usage = 
	    STATIC_SYMBOL("INDEX-SPACE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_13 = STATIC_STRING("1q83j-y8s83-Zgy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_index_space_count);
    push_optimized_constant(Qindex_space_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_index_spaces = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INDEX-SPACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_index_spaces,
	    Chain_of_available_index_spaces);
    record_system_variable(Qchain_of_available_index_spaces,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qindex_space_count = STATIC_SYMBOL("INDEX-SPACE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qindex_space_count,Index_space_count);
    record_system_variable(Qindex_space_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_index_spaces_vector == UNBOUND)
	Chain_of_available_index_spaces_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qindex_space_structure_memory_usage,
	    STATIC_FUNCTION(index_space_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_index_space_count,
	    STATIC_FUNCTION(outstanding_index_space_count,NIL,FALSE,0,0));
    reclaim_structure_for_index_space_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_index_space,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qindex_space,
	    reclaim_structure_for_index_space_1);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qenlarge_index_space_error_message = 
	    STATIC_SYMBOL("ENLARGE-INDEX-SPACE-ERROR-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qenlarge_index_space_error_message,
	    Enlarge_index_space_error_message);
    string_constant_14 = STATIC_STRING("Index space full!");
    SET_SYMBOL_VALUE(Qenlarge_index_space_error_message,string_constant_14);
    if (The_type_description_of_queue_element == UNBOUND)
	The_type_description_of_queue_element = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8m83m=y1m83m=y8k1l8k0000001m1m83*gy9k1n8y83-5Ey1n83-9qy83-9ry83-9oykpk0k0");
    temp = The_type_description_of_queue_element;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_queue_element = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_15));
    Qg2_defstruct_structure_name_queue_element_g2_struct = 
	    STATIC_SYMBOL("QUEUE-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_queue_element_g2_struct,
	    The_type_description_of_queue_element,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qqueue_element = STATIC_SYMBOL("QUEUE-ELEMENT",AB_package);
    mutate_global_property(Qqueue_element,
	    The_type_description_of_queue_element,Qtype_description_of_type);
    Qoutstanding_queue_element_count = 
	    STATIC_SYMBOL("OUTSTANDING-QUEUE-ELEMENT-COUNT",AB_package);
    Qqueue_element_structure_memory_usage = 
	    STATIC_SYMBOL("QUEUE-ELEMENT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_16 = STATIC_STRING("1q83m=y8s83-l2y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_queue_element_count);
    push_optimized_constant(Qqueue_element_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_16));
    Qchain_of_available_queue_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-QUEUE-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_queue_elements,
	    Chain_of_available_queue_elements);
    record_system_variable(Qchain_of_available_queue_elements,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qqueue_element_count = STATIC_SYMBOL("QUEUE-ELEMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_element_count,Queue_element_count);
    record_system_variable(Qqueue_element_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_queue_elements_vector == UNBOUND)
	Chain_of_available_queue_elements_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qqueue_element_structure_memory_usage,
	    STATIC_FUNCTION(queue_element_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_queue_element_count,
	    STATIC_FUNCTION(outstanding_queue_element_count,NIL,FALSE,0,0));
    reclaim_structure_for_queue_element_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_queue_element,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qqueue_element,
	    reclaim_structure_for_queue_element_1);
    Qconstant_queue_marker = STATIC_SYMBOL("CONSTANT-QUEUE-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconstant_queue_marker,Constant_queue_marker);
    list_constant_3 = STATIC_CONS(Qconstant_queue_marker,Qnil);
    SET_SYMBOL_VALUE(Qconstant_queue_marker,list_constant_3);
    Qconstant_queue_head_marker = 
	    STATIC_SYMBOL("CONSTANT-QUEUE-HEAD-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconstant_queue_head_marker,
	    Constant_queue_head_marker);
    list_constant_4 = STATIC_CONS(Qconstant_queue_head_marker,Qnil);
    SET_SYMBOL_VALUE(Qconstant_queue_head_marker,list_constant_4);
    Qconstant_queue_tail_marker = 
	    STATIC_SYMBOL("CONSTANT-QUEUE-TAIL-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconstant_queue_tail_marker,
	    Constant_queue_tail_marker);
    list_constant_5 = STATIC_CONS(Qconstant_queue_tail_marker,Qnil);
    SET_SYMBOL_VALUE(Qconstant_queue_tail_marker,list_constant_5);
    Qg2_defstruct_structure_name_lru_element_g2_struct = 
	    STATIC_SYMBOL("LRU-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlru_element = STATIC_SYMBOL("LRU-ELEMENT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_lru_element_g2_struct,
	    Qlru_element,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlru_element,
	    Qg2_defstruct_structure_name_lru_element_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_lru_element == UNBOUND)
	The_type_description_of_lru_element = Nil;
    string_constant_17 = 
	    STATIC_STRING("43Dy8m831gy1n831gy8n8k1l8n0000001l1m831uy831Jyknk0k0");
    temp = The_type_description_of_lru_element;
    The_type_description_of_lru_element = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_17));
    mutate_global_property(Qg2_defstruct_structure_name_lru_element_g2_struct,
	    The_type_description_of_lru_element,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlru_element,
	    The_type_description_of_lru_element,Qtype_description_of_type);
    Qoutstanding_lru_element_count = 
	    STATIC_SYMBOL("OUTSTANDING-LRU-ELEMENT-COUNT",AB_package);
    Qlru_element_structure_memory_usage = 
	    STATIC_SYMBOL("LRU-ELEMENT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_18 = STATIC_STRING("1q831gy8s83-dOy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_lru_element_count);
    push_optimized_constant(Qlru_element_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_18));
    Qchain_of_available_lru_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LRU-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_lru_elements,
	    Chain_of_available_lru_elements);
    record_system_variable(Qchain_of_available_lru_elements,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlru_element_count = STATIC_SYMBOL("LRU-ELEMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlru_element_count,Lru_element_count);
    record_system_variable(Qlru_element_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_lru_elements_vector == UNBOUND)
	Chain_of_available_lru_elements_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlru_element_structure_memory_usage,
	    STATIC_FUNCTION(lru_element_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_lru_element_count,
	    STATIC_FUNCTION(outstanding_lru_element_count,NIL,FALSE,0,0));
    reclaim_structure_for_lru_element_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_lru_element,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlru_element,
	    reclaim_structure_for_lru_element_1);
    if (Memory_limit_variable_names_for_decacheable_structures == UNBOUND)
	Memory_limit_variable_names_for_decacheable_structures = Nil;
    if (Names_and_sizes_for_decacheable_structures == UNBOUND)
	Names_and_sizes_for_decacheable_structures = Nil;
    Default_decacheable_structure_allocation_limit = FIX((SI_Long)5L);
    Minimum_decacheable_structure_allocation_limit = FIX((SI_Long)1L);
    Qg2_defstruct_structure_name_memory_limit_info_g2_struct = 
	    STATIC_SYMBOL("MEMORY-LIMIT-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmemory_limit_info = STATIC_SYMBOL("MEMORY-LIMIT-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_memory_limit_info_g2_struct,
	    Qmemory_limit_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmemory_limit_info,
	    Qg2_defstruct_structure_name_memory_limit_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_memory_limit_info == UNBOUND)
	The_type_description_of_memory_limit_info = Nil;
    string_constant_19 = 
	    STATIC_STRING("43Dy8m83kfy1n83kfy8n8k1l8n0000001l1m831uy831Jyktk0k0");
    temp = The_type_description_of_memory_limit_info;
    The_type_description_of_memory_limit_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_19));
    mutate_global_property(Qg2_defstruct_structure_name_memory_limit_info_g2_struct,
	    The_type_description_of_memory_limit_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qmemory_limit_info,
	    The_type_description_of_memory_limit_info,
	    Qtype_description_of_type);
    Qoutstanding_memory_limit_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-MEMORY-LIMIT-INFO-COUNT",AB_package);
    Qmemory_limit_info_structure_memory_usage = 
	    STATIC_SYMBOL("MEMORY-LIMIT-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_20 = STATIC_STRING("1q83kfy8s83-eCy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_memory_limit_info_count);
    push_optimized_constant(Qmemory_limit_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    Qchain_of_available_memory_limit_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-MEMORY-LIMIT-INFOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_memory_limit_infos,
	    Chain_of_available_memory_limit_infos);
    record_system_variable(Qchain_of_available_memory_limit_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qmemory_limit_info_count = STATIC_SYMBOL("MEMORY-LIMIT-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmemory_limit_info_count,
	    Memory_limit_info_count);
    record_system_variable(Qmemory_limit_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_memory_limit_infos_vector == UNBOUND)
	Chain_of_available_memory_limit_infos_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qmemory_limit_info_structure_memory_usage,
	    STATIC_FUNCTION(memory_limit_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_memory_limit_info_count,
	    STATIC_FUNCTION(outstanding_memory_limit_info_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_memory_limit_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_memory_limit_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qmemory_limit_info,
	    reclaim_structure_for_memory_limit_info_1);
    Qdecache_occurred_since_last_update_qm = 
	    STATIC_SYMBOL("DECACHE-OCCURRED-SINCE-LAST-UPDATE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdecache_occurred_since_last_update_qm,
	    Decache_occurred_since_last_update_qm);
    record_system_variable(Qdecache_occurred_since_last_update_qm,
	    Qutilities2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qglobal_desired_thrashing_setpoint = 
	    STATIC_SYMBOL("GLOBAL-DESIRED-THRASHING-SETPOINT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_desired_thrashing_setpoint,
	    Global_desired_thrashing_setpoint);
    record_system_variable(Qglobal_desired_thrashing_setpoint,Qutilities2,
	    FIX((SI_Long)50L),Qnil,Qnil,Qnil,Qnil);
    Qtime_of_last_thrashing_cost_update = 
	    STATIC_SYMBOL("TIME-OF-LAST-THRASHING-COST-UPDATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtime_of_last_thrashing_cost_update,
	    Time_of_last_thrashing_cost_update);
    Qget_fixnum_time_function = STATIC_SYMBOL("GET-FIXNUM-TIME-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_fixnum_time_function,
	    STATIC_FUNCTION(get_fixnum_time_function,NIL,FALSE,0,0));
    list_constant_6 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_fixnum_time_function);
    record_system_variable(Qtime_of_last_thrashing_cost_update,Qutilities2,
	    list_constant_6,Qnil,Qnil,Qnil,Qnil);
    Qthrashing_cost_update_interval = 
	    STATIC_SYMBOL("THRASHING-COST-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthrashing_cost_update_interval,
	    Thrashing_cost_update_interval);
    Qfixnum_time_interval = STATIC_SYMBOL("FIXNUM-TIME-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qfixnum_time_interval,
	    STATIC_FUNCTION(fixnum_time_interval,NIL,FALSE,1,1));
    list_constant_7 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qfixnum_time_interval,FIX((SI_Long)1000L));
    record_system_variable(Qthrashing_cost_update_interval,Qutilities2,
	    list_constant_7,Qnil,Qnil,Qnil,Qnil);
    Qlong_thrashing_cost_update_interval = 
	    STATIC_SYMBOL("LONG-THRASHING-COST-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlong_thrashing_cost_update_interval,
	    Long_thrashing_cost_update_interval);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qfixnum_time_interval,FIX((SI_Long)5000L));
    record_system_variable(Qlong_thrashing_cost_update_interval,
	    Qutilities2,list_constant_8,Qnil,Qnil,Qnil,Qnil);
    Positive_thrashing_error_gain = FIX((SI_Long)1L);
    Negative_thrashing_error_gain = FIX((SI_Long)1L);
    Qsimulation_no_value = STATIC_SYMBOL("SIMULATION-NO-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_no_value,Simulation_no_value);
    string_constant_21 = STATIC_STRING("simulation-no-value-");
    list_constant_9 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_21);
    record_system_variable(Qsimulation_no_value,Qutilities2,
	    list_constant_9,Qnil,Qnil,Qnil,Qnil);
    if (Combiners_for_defun_incremental == UNBOUND)
	Combiners_for_defun_incremental = Nil;
    if (Defun_incremental_compile_time_registry == UNBOUND)
	Defun_incremental_compile_time_registry = Nil;
    if (Defun_incremental_runtime_registry == UNBOUND)
	Defun_incremental_runtime_registry = Nil;
    Qavailable_queue_item_conses = 
	    STATIC_SYMBOL("AVAILABLE-QUEUE-ITEM-CONSES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_queue_item_conses,
	    Available_queue_item_conses);
    record_system_variable(Qavailable_queue_item_conses,Qutilities1,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qavailable_queue_item_conses_tail = 
	    STATIC_SYMBOL("AVAILABLE-QUEUE-ITEM-CONSES-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_queue_item_conses_tail,
	    Available_queue_item_conses_tail);
    record_system_variable(Qavailable_queue_item_conses_tail,Qutilities1,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qavailable_queue_item_conses_vector = 
	    STATIC_SYMBOL("AVAILABLE-QUEUE-ITEM-CONSES-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_queue_item_conses_vector,
	    Available_queue_item_conses_vector);
    record_system_variable(Qavailable_queue_item_conses_vector,Qutilities1,
	    list_constant,Qnil,Qt,Qnil,Qnil);
    Qavailable_queue_item_conses_tail_vector = 
	    STATIC_SYMBOL("AVAILABLE-QUEUE-ITEM-CONSES-TAIL-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_queue_item_conses_tail_vector,
	    Available_queue_item_conses_tail_vector);
    record_system_variable(Qavailable_queue_item_conses_tail_vector,
	    Qutilities1,list_constant,Qnil,Qt,Qnil,Qnil);
    Qqueue_item_cons_counter_vector = 
	    STATIC_SYMBOL("QUEUE-ITEM-CONS-COUNTER-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_item_cons_counter_vector,
	    Queue_item_cons_counter_vector);
    record_system_variable(Qqueue_item_cons_counter_vector,Qutilities1,
	    list_constant_1,Qnil,Qt,Qnil,Qnil);
    Qqueue_item_cons_counter = STATIC_SYMBOL("QUEUE-ITEM-CONS-COUNTER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_item_cons_counter,
	    Queue_item_cons_counter);
    record_system_variable(Qqueue_item_cons_counter,Qutilities1,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qoutstanding_queue_item_conses = 
	    STATIC_SYMBOL("OUTSTANDING-QUEUE-ITEM-CONSES",AB_package);
    SET_SYMBOL_FUNCTION(Qoutstanding_queue_item_conses,
	    STATIC_FUNCTION(outstanding_queue_item_conses,NIL,FALSE,0,0));
    Qqueue_item_cons_memory_usage = 
	    STATIC_SYMBOL("QUEUE-ITEM-CONS-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qqueue_item_cons_memory_usage,
	    STATIC_FUNCTION(queue_item_cons_memory_usage,NIL,FALSE,0,0));
    string_constant_22 = STATIC_STRING("1q83-l4y9k83-l3y09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qcons);
    push_optimized_constant(Qoutstanding_queue_item_conses);
    push_optimized_constant(Qqueue_item_cons_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_22));
    Qqueue_item = STATIC_SYMBOL("QUEUE-ITEM",AB_package);
    Qg2_defstruct_structure_name_queue_g2_struct = 
	    STATIC_SYMBOL("QUEUE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qqueue = STATIC_SYMBOL("QUEUE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_queue_g2_struct,
	    Qqueue,Qab_name_of_unique_structure_type);
    mutate_global_property(Qqueue,
	    Qg2_defstruct_structure_name_queue_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_queue == UNBOUND)
	The_type_description_of_queue = Nil;
    string_constant_23 = 
	    STATIC_STRING("43Dy8m83m*y1n83m*y8n8k1l8n0000001o1m83=0y83-9Dy1m83My83-Apy1n8y83-5Fy1m83-9py83-9sy1m831uy83--gyknk0k0");
    temp = The_type_description_of_queue;
    The_type_description_of_queue = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_23));
    mutate_global_property(Qg2_defstruct_structure_name_queue_g2_struct,
	    The_type_description_of_queue,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qqueue,The_type_description_of_queue,
	    Qtype_description_of_type);
    Qoutstanding_queue_count = STATIC_SYMBOL("OUTSTANDING-QUEUE-COUNT",
	    AB_package);
    Qqueue_structure_memory_usage = 
	    STATIC_SYMBOL("QUEUE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_24 = STATIC_STRING("1q83m*y8s83-l1y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_queue_count);
    push_optimized_constant(Qqueue_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_24));
    Qchain_of_available_queues = STATIC_SYMBOL("CHAIN-OF-AVAILABLE-QUEUES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_queues,
	    Chain_of_available_queues);
    record_system_variable(Qchain_of_available_queues,Qutilities2,Nil,Qnil,
	    Qt,Qnil,Qnil);
    Qqueue_count = STATIC_SYMBOL("QUEUE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qqueue_count,Queue_count);
    record_system_variable(Qqueue_count,Qutilities2,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    if (Chain_of_available_queues_vector == UNBOUND)
	Chain_of_available_queues_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qqueue_structure_memory_usage,
	    STATIC_FUNCTION(queue_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_queue_count,
	    STATIC_FUNCTION(outstanding_queue_count,NIL,FALSE,0,0));
    reclaim_structure_for_queue_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_queue,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qqueue,
	    reclaim_structure_for_queue_1);
    Qcurrent_computation_flags = STATIC_SYMBOL("CURRENT-COMPUTATION-FLAGS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_computation_flags,
	    Current_computation_flags);
    record_system_variable(Qcurrent_computation_flags,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qspecial_setf_method = STATIC_SYMBOL("SPECIAL-SETF-METHOD",AB_package);
    Special_setf_method_prop = Qspecial_setf_method;
    Qcache_explanation_variables_qm = 
	    STATIC_SYMBOL("CACHE-EXPLANATION-VARIABLES\?",AB_package);
    Qset_cache_explanation_variables_qm = 
	    STATIC_SYMBOL("SET-CACHE-EXPLANATION-VARIABLES\?",AB_package);
    mutate_global_property(Qcache_explanation_variables_qm,
	    Qset_cache_explanation_variables_qm,Qspecial_setf_method);
    Qfinal_evaluation_attempt_qm = 
	    STATIC_SYMBOL("FINAL-EVALUATION-ATTEMPT\?",AB_package);
    Qset_final_evaluation_attempt_qm = 
	    STATIC_SYMBOL("SET-FINAL-EVALUATION-ATTEMPT\?",AB_package);
    mutate_global_property(Qfinal_evaluation_attempt_qm,
	    Qset_final_evaluation_attempt_qm,Qspecial_setf_method);
    Qforce_new_request_for_value = 
	    STATIC_SYMBOL("FORCE-NEW-REQUEST-FOR-VALUE",AB_package);
    Qset_force_new_request_for_value = 
	    STATIC_SYMBOL("SET-FORCE-NEW-REQUEST-FOR-VALUE",AB_package);
    mutate_global_property(Qforce_new_request_for_value,
	    Qset_force_new_request_for_value,Qspecial_setf_method);
    Qno_wake_ups_during_role_serving = 
	    STATIC_SYMBOL("NO-WAKE-UPS-DURING-ROLE-SERVING",AB_package);
    Qset_no_wake_ups_during_role_serving = 
	    STATIC_SYMBOL("SET-NO-WAKE-UPS-DURING-ROLE-SERVING",AB_package);
    mutate_global_property(Qno_wake_ups_during_role_serving,
	    Qset_no_wake_ups_during_role_serving,Qspecial_setf_method);
    Qrole_serve_inactive_objects_qm = 
	    STATIC_SYMBOL("ROLE-SERVE-INACTIVE-OBJECTS\?",AB_package);
    Qset_role_serve_inactive_objects_qm = 
	    STATIC_SYMBOL("SET-ROLE-SERVE-INACTIVE-OBJECTS\?",AB_package);
    mutate_global_property(Qrole_serve_inactive_objects_qm,
	    Qset_role_serve_inactive_objects_qm,Qspecial_setf_method);
    Qattempting_network_write_access_p = 
	    STATIC_SYMBOL("ATTEMPTING-NETWORK-WRITE-ACCESS-P",AB_package);
    Qset_attempting_network_write_access_p = 
	    STATIC_SYMBOL("SET-ATTEMPTING-NETWORK-WRITE-ACCESS-P",AB_package);
    mutate_global_property(Qattempting_network_write_access_p,
	    Qset_attempting_network_write_access_p,Qspecial_setf_method);
    Qattempting_network_read_access_p = 
	    STATIC_SYMBOL("ATTEMPTING-NETWORK-READ-ACCESS-P",AB_package);
    Qset_attempting_network_read_access_p = 
	    STATIC_SYMBOL("SET-ATTEMPTING-NETWORK-READ-ACCESS-P",AB_package);
    mutate_global_property(Qattempting_network_read_access_p,
	    Qset_attempting_network_read_access_p,Qspecial_setf_method);
    Qdefault_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("DEFAULT-DONT-COMPUTE-NEW-VARIABLE-VALUES",
	    AB_package);
    Qset_default_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("SET-DEFAULT-DONT-COMPUTE-NEW-VARIABLE-VALUES",
	    AB_package);
    mutate_global_property(Qdefault_dont_compute_new_variable_values,
	    Qset_default_dont_compute_new_variable_values,
	    Qspecial_setf_method);
    Qdont_compute_new_variable_values = 
	    STATIC_SYMBOL("DONT-COMPUTE-NEW-VARIABLE-VALUES",AB_package);
    Qset_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("SET-DONT-COMPUTE-NEW-VARIABLE-VALUES",AB_package);
    mutate_global_property(Qdont_compute_new_variable_values,
	    Qset_dont_compute_new_variable_values,Qspecial_setf_method);
    Qdont_forward_chain_from_rule = 
	    STATIC_SYMBOL("DONT-FORWARD-CHAIN-FROM-RULE",AB_package);
    Qset_dont_forward_chain_from_rule = 
	    STATIC_SYMBOL("SET-DONT-FORWARD-CHAIN-FROM-RULE",AB_package);
    mutate_global_property(Qdont_forward_chain_from_rule,
	    Qset_dont_forward_chain_from_rule,Qspecial_setf_method);
    Qwithin_dynamic_extent_of_traced_rule_p = 
	    STATIC_SYMBOL("WITHIN-DYNAMIC-EXTENT-OF-TRACED-RULE-P",AB_package);
    Qset_within_dynamic_extent_of_traced_rule_p = 
	    STATIC_SYMBOL("SET-WITHIN-DYNAMIC-EXTENT-OF-TRACED-RULE-P",
	    AB_package);
    mutate_global_property(Qwithin_dynamic_extent_of_traced_rule_p,
	    Qset_within_dynamic_extent_of_traced_rule_p,Qspecial_setf_method);
    Qserve_only_permanent_items_p = 
	    STATIC_SYMBOL("SERVE-ONLY-PERMANENT-ITEMS-P",AB_package);
    Qset_serve_only_permanent_items_p = 
	    STATIC_SYMBOL("SET-SERVE-ONLY-PERMANENT-ITEMS-P",AB_package);
    mutate_global_property(Qserve_only_permanent_items_p,
	    Qset_serve_only_permanent_items_p,Qspecial_setf_method);
    Qserve_loose_ends_p = STATIC_SYMBOL("SERVE-LOOSE-ENDS-P",AB_package);
    Qset_serve_loose_ends_p = STATIC_SYMBOL("SET-SERVE-LOOSE-ENDS-P",
	    AB_package);
    mutate_global_property(Qserve_loose_ends_p,Qset_serve_loose_ends_p,
	    Qspecial_setf_method);
}
