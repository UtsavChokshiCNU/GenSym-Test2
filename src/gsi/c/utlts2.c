/* utlts2.c
 * Input file:  utilities2.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "utlts2.h"


Object G2int_def_structure_slot_descriptions_prop = UNBOUND;

Object G2int_ab_name_of_unique_structure_type_prop = UNBOUND;

Object G2int_unique_structure_type_of_ab_nameqm_prop = UNBOUND;

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* FIND-STRUCTURE-METHOD */
Object g2int_find_structure_method(method_name,structure)
    Object method_name, structure;
{
    Object temp, method_id_qm, gensymed_symbol;
    SI_Long id, ab_loop_bind_;

    x_note_fn_call(22,0);
    id = (SI_Long)0L;
    ab_loop_bind_ = IFIX(G2int_maximum_number_of_structure_methods);
  next_loop:
    if (id >= ab_loop_bind_)
	goto end_loop;
    temp = ISVREF(G2int_table_to_map_structure_id_to_method_name,id);
    if (EQL(temp,method_name)) {
	method_id_qm = FIX(id);
	goto end;
    }
    id = id + (SI_Long)1L;
    goto next_loop;
  end_loop:
    method_id_qm = Qnil;
  end:;
    if (method_id_qm) {
	gensymed_symbol = ISVREF(structure,(SI_Long)0L);
	return VALUES_1(ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),IFIX(method_id_qm)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_type_description_of_type;  /* type-description-of-type */

/* RECORD-DIRECT-STRUCTURE-METHOD */
Object g2int_record_direct_structure_method(method_name,structure_ab_type,
	    method_function)
    Object method_name, structure_ab_type, method_function;
{
    Object type_description, direct_methods, existing_entry_qm, push_arg, temp;
    SI_Long id, ab_loop_bind_;

    x_note_fn_call(22,1);
    type_description = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qg2int_type_description_of_type);
    direct_methods = ISVREF(type_description,(SI_Long)8L);
    existing_entry_qm = g2int_assq_function(method_name,direct_methods);
    if (existing_entry_qm)
	M_SECOND(existing_entry_qm) = method_function;
    else {
	push_arg = LIST_2(method_name,method_function);
	direct_methods = CONS(push_arg,direct_methods);
    }
    SVREF(type_description,FIX((SI_Long)8L)) = direct_methods;
    id = (SI_Long)0L;
    ab_loop_bind_ = IFIX(G2int_maximum_number_of_structure_methods);
  next_loop:
    if (id >= ab_loop_bind_)
	goto end_loop;
    temp = ISVREF(G2int_table_to_map_structure_id_to_method_name,id);
    if (EQL(temp,method_name)) {
	temp = FIX(id);
	goto end;
    }
    id = id + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return g2int_set_structure_method_and_propogate(structure_ab_type,
	    method_name,temp,method_function);
}

/* DIRECT-STRUCTURE-METHOD */
Object g2int_direct_structure_method(method_name,structure_ab_type)
    Object method_name, structure_ab_type;
{
    Object type_description, direct_methods, temp;

    x_note_fn_call(22,2);
    type_description = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qg2int_type_description_of_type);
    direct_methods = ISVREF(type_description,(SI_Long)8L);
    temp = g2int_assq_function(method_name,direct_methods);
    return VALUES_1(SECOND(temp));
}

/* SET-STRUCTURE-METHOD-AND-PROPOGATE */
Object g2int_set_structure_method_and_propogate(structure_ab_type,
	    method_name,method_id,method_function)
    Object structure_ab_type, method_name, method_id, method_function;
{
    Object type_description, dispatch_table_of_this_structure_type, subtype;
    Object ab_loop_list_;

    x_note_fn_call(22,3);
    type_description = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(structure_ab_type),
	    Qg2int_type_description_of_type);
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
    if ( !( 
	    !TRUEP(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(subtype),
	    Qg2int_type_description_of_type)) || 
	    g2int_assq_function(method_name,
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(subtype),
	    Qg2int_type_description_of_type),(SI_Long)8L))))
	g2int_set_structure_method_and_propogate(subtype,method_name,
		method_id,method_function);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_structure_method_arglist_prop = UNBOUND;

Object G2int_structure_being_reclaimed = UNBOUND;

/* RESET-STRUCTURE-BEING-RECLAIMED-AFTER-BOMBOUT */
Object g2int_reset_structure_being_reclaimed_after_bombout()
{
    x_note_fn_call(22,4);
    G2int_structure_being_reclaimed = Nil;
    return VALUES_1(G2int_structure_being_reclaimed);
}

static Object Qg2int_ab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

/* TYPE-OF-NAMED-STRUCTURE */
Object g2int_type_of_named_structure(named_structure_instance)
    Object named_structure_instance;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(22,5);
    gensymed_symbol = SIMPLE_VECTOR_P(named_structure_instance) ? 
	    ISVREF(named_structure_instance,(SI_Long)0L) : 
	    CAR(named_structure_instance);
    temp = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_ab_name_of_unique_structure_type);
    return VALUES_1(temp);
}

/* LOAD-AND-INITIALIZE-TYPE-DESCRIPTION */
Object g2int_load_and_initialize_type_description(old_type_description_qm,
	    new_type_description)
    Object old_type_description_qm, new_type_description;
{
    Object temp, new_superior_type, new_superior_type_qm;
    Object new_superior_type_description_qm, new_dispatch_table;
    Object svref_new_value, pushnew_arg;
    SI_Long i, ab_loop_bind_;
    char temp_1;

    x_note_fn_call(22,6);
    temp = ISVREF(new_type_description,(SI_Long)2L);
    new_superior_type = SECOND(temp);
    new_superior_type_qm = EQ(T,new_superior_type) ? Nil : new_superior_type;
    new_superior_type_description_qm = new_superior_type_qm ? 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(new_superior_type),
	    Qg2int_type_description_of_type) : Nil;
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
		g2int_make_structure_method_table(ISVREF(new_superior_type_description_qm,
		(SI_Long)9L));
    else
	new_dispatch_table = g2int_make_structure_method_table(Nil);
    svref_new_value = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(new_superior_type),
	    Qg2int_type_description_of_type),(SI_Long)9L);
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
Object g2int_reclaim_structure_function(named_gensym_structure)
    Object named_gensym_structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(22,7);
    gensymed_symbol = ISVREF(named_gensym_structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = named_gensym_structure;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-STRUCTURE-IF-ANY */
Object g2int_reclaim_structure_if_any(structure_qm)
    Object structure_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(22,8);
    if (structure_qm) {
	gensymed_symbol = ISVREF(structure_qm,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = structure_qm;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-IF-STRUCTURE */
Object g2int_reclaim_if_structure(thing_qm)
    Object thing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(22,9);
    if (g2int_allocated_named_gensym_structure_p(thing_qm)) {
	gensymed_symbol = ISVREF(thing_qm,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = thing_qm;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(Nil);
}

/* CLEAN-UP-STRUCTURE-FUNCTION */
Object g2int_clean_up_structure_function(named_gensym_structure)
    Object named_gensym_structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(22,10);
    gensymed_symbol = ISVREF(named_gensym_structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)9L);
    gensymed_symbol_1 = named_gensym_structure;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* CLEAN-UP-AND-RECLAIM-STRUCTURE */
Object g2int_clean_up_and_reclaim_structure(structure)
    Object structure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(22,11);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)9L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol = ISVREF(structure,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = structure;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_named_gensym_structure = UNBOUND;

Object G2int_chain_of_available_named_gensym_structures = UNBOUND;

Object G2int_named_gensym_structure_count = UNBOUND;

/* RECLAIM-NAMED-GENSYM-STRUCTURE-1 */
Object g2int_reclaim_named_gensym_structure_1(named_gensym_structure)
    Object named_gensym_structure;
{
    Object svref_new_value;

    x_note_fn_call(22,12);
    inline_note_reclaim_cons(named_gensym_structure,Nil);
    svref_new_value = G2int_chain_of_available_named_gensym_structures;
    SVREF(named_gensym_structure,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_named_gensym_structures = named_gensym_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-NAMED-GENSYM-STRUCTURE */
Object g2int_reclaim_structure_for_named_gensym_structure(named_gensym_structure)
    Object named_gensym_structure;
{
    x_note_fn_call(22,13);
    return g2int_reclaim_named_gensym_structure_1(named_gensym_structure);
}

static Object Qg2_defstruct_structure_name_named_gensym_structure_g2_struct;  /* g2-defstruct-structure-name::named-gensym-structure-g2-struct */

/* MAKE-PERMANENT-NAMED-GENSYM-STRUCTURE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_named_gensym_structure_structure_internal()
{
    Object def_structure_named_gensym_structure_variable;
    Object named_gensym_structure_count_new_value;
    Object defstruct_g2_named_gensym_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,14);
    def_structure_named_gensym_structure_variable = Nil;
    named_gensym_structure_count_new_value = 
	    FIXNUM_ADD1(G2int_named_gensym_structure_count);
    G2int_named_gensym_structure_count = 
	    named_gensym_structure_count_new_value;
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
Object g2int_make_named_gensym_structure_1()
{
    Object def_structure_named_gensym_structure_variable;

    x_note_fn_call(22,15);
    def_structure_named_gensym_structure_variable = 
	    G2int_chain_of_available_named_gensym_structures;
    if (def_structure_named_gensym_structure_variable) {
	G2int_chain_of_available_named_gensym_structures = 
		ISVREF(def_structure_named_gensym_structure_variable,
		(SI_Long)0L);
	SVREF(def_structure_named_gensym_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_named_gensym_structure_g2_struct;
    }
    else
	def_structure_named_gensym_structure_variable = 
		g2int_make_permanent_named_gensym_structure_structure_internal();
    inline_note_allocate_cons(def_structure_named_gensym_structure_variable,
	    Nil);
    return VALUES_1(def_structure_named_gensym_structure_variable);
}

/* TYPE-NAME-OF */
Object g2int_type_name_of(thing)
    Object thing;
{
    Object description_qm;

    x_note_fn_call(22,16);
    description_qm = g2int_type_description_of(thing);
    if (description_qm)
	return VALUES_1(ISVREF(description_qm,(SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* STRUCTURE-TYPE-P */
Object g2int_structure_type_p(named_gensym_structure,type)
    Object named_gensym_structure, type;
{
    Object type_description_of_type, type_description_of_instance, temp;

    x_note_fn_call(22,17);
    type_description_of_type = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
	    Qg2int_type_description_of_type);
    type_description_of_instance = 
	    g2int_type_description_of(named_gensym_structure);
    temp = EQL(type_description_of_instance,type_description_of_type) ? T :
	     Nil;
    if (temp);
    else
	temp = 
		g2int_subtype_p_using_type_descriptions(type_description_of_instance,
		type_description_of_type);
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_binary_tree_element = UNBOUND;

Object G2int_chain_of_available_binary_tree_elements = UNBOUND;

Object G2int_binary_tree_element_count = UNBOUND;

/* RECLAIM-BINARY-TREE-ELEMENT-1 */
Object g2int_reclaim_binary_tree_element_1(binary_tree_element)
    Object binary_tree_element;
{
    Object svref_new_value;

    x_note_fn_call(22,18);
    inline_note_reclaim_cons(binary_tree_element,Nil);
    svref_new_value = G2int_chain_of_available_binary_tree_elements;
    SVREF(binary_tree_element,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_binary_tree_elements = binary_tree_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BINARY-TREE-ELEMENT */
Object g2int_reclaim_structure_for_binary_tree_element(binary_tree_element)
    Object binary_tree_element;
{
    x_note_fn_call(22,19);
    return g2int_reclaim_binary_tree_element_1(binary_tree_element);
}

/* MAKE-PERMANENT-BINARY-TREE-ELEMENT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_binary_tree_element_structure_internal()
{
    Object def_structure_binary_tree_element_variable, the_array;
    Object defstruct_g2_binary_tree_element_variable, svref_new_value;
    SI_Long binary_tree_element_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,20);
    def_structure_binary_tree_element_variable = Nil;
    binary_tree_element_count_new_value = 
	    IFIX(G2int_binary_tree_element_count) + (SI_Long)100L;
    G2int_binary_tree_element_count = FIX(binary_tree_element_count_new_value);
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
	svref_new_value = G2int_chain_of_available_binary_tree_elements;
	SVREF(def_structure_binary_tree_element_variable,FIX((SI_Long)0L)) 
		= svref_new_value;
	G2int_chain_of_available_binary_tree_elements = 
		def_structure_binary_tree_element_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_binary_tree_element_variable);
}

/* MAKE-BINARY-TREE-ELEMENT-1 */
Object g2int_make_binary_tree_element_1(binary_element_hash_number,
	    less_than_branch,greater_than_branch,binary_element_alist,
	    balance_factor)
    Object binary_element_hash_number, less_than_branch, greater_than_branch;
    Object binary_element_alist, balance_factor;
{
    Object def_structure_binary_tree_element_variable;

    x_note_fn_call(22,21);
    def_structure_binary_tree_element_variable = 
	    G2int_chain_of_available_binary_tree_elements;
    if (def_structure_binary_tree_element_variable)
	G2int_chain_of_available_binary_tree_elements = 
		ISVREF(def_structure_binary_tree_element_variable,(SI_Long)0L);
    else
	def_structure_binary_tree_element_variable = 
		g2int_make_permanent_binary_tree_element_structure_internal();
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
Object g2int_flatten_binary_tree(tree)
    Object tree;
{
    x_note_fn_call(22,22);
    if (tree)
	return g2int_flatten_binary_tree_1(tree,Nil);
    else
	return VALUES_1(Nil);
}

/* FLATTEN-BINARY-TREE-1 */
Object g2int_flatten_binary_tree_1(tree,pairs)
    Object tree, pairs;
{
    Object pair, ab_loop_list_, subtree1, subtree2;

    x_note_fn_call(22,23);
    pair = Nil;
    ab_loop_list_ = ISVREF(tree,(SI_Long)3L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pairs = g2int_gensym_cons_1(CAR(pair),g2int_gensym_cons_1(CDR(pair),
	    pairs));
    goto next_loop;
  end_loop:;
    subtree1 = ISVREF(tree,(SI_Long)1L);
    subtree2 = ISVREF(tree,(SI_Long)2L);
    if (subtree1)
	pairs = g2int_flatten_binary_tree_1(subtree1,pairs);
    if (subtree2)
	pairs = g2int_flatten_binary_tree_1(subtree2,pairs);
    return VALUES_1(pairs);
}

static Object Qg2int_equal_rule_context;  /* equal-rule-context */

/* LOOKUP-BINARY-TREE-ENTRY */
Object g2int_lookup_binary_tree_entry(tree_element,key_comparitor,key,
	    key_hash_init)
    Object tree_element, key_comparitor, key, key_hash_init;
{
    Object entry_cons, entry_key, temp;
    SI_Long key_hash, key_hash_local, element_hash;

    x_note_fn_call(22,24);
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
	else if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp = g2int_equal_rule_context(key,entry_key);
	else
	    temp = FUNCALL_2(key_comparitor,key,entry_key);
	if (temp) {
	    temp = M_CDR(M_CAR(entry_cons));
	    goto end;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end:;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* LOOKUP-EQ-BINARY-TREE-ENTRY */
Object g2int_lookup_eq_binary_tree_entry(tree_element,key,key_hash_init)
    Object tree_element, key, key_hash_init;
{
    Object entry_cons, temp;
    SI_Long key_hash, key_hash_local, element_hash;

    x_note_fn_call(22,25);
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
	    goto end;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end:;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object G2int_binary_tree_ancestor = UNBOUND;

Object G2int_binary_tree_branch = UNBOUND;

static Object Qg2int_gensym;       /* gensym */

static Object Kless_than;          /* :less-than */

static Object Kgreater_than;       /* :greater-than */

/* SET-BALANCED-BINARY-TREE-ENTRY */
Object g2int_set_balanced_binary_tree_entry(binary_tree,key_comparitor,
	    mutator_function_qm,mutate_old_entry_qm,key,key_hash_init,entry)
    Object binary_tree, key_comparitor, mutator_function_qm;
    Object mutate_old_entry_qm, key, key_hash_init, entry;
{
    Object new_cons, gensymed_symbol, gensymed_symbol_1, temp, insertion_point;
    Object alist, entry_cons, entry_key, temp_1, alist_entry_qm, new_node;
    Object heavy_ancestor, balance;
    SI_Long key_hash, insertion_depth, heavy_ancestor_depth;
    SI_Long insertion_point_hash, depth_of_insertion_parent, adjust_point;
    SI_Long ab_loop_bind_, svref_new_value;

    x_note_fn_call(22,26);
    key_hash = IFIX(key_hash_init);
    if ( !TRUEP(CDR(binary_tree))) {
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = g2int_replenish_gensym_cons_pool();
	new_cons = G2int_available_gensym_conses;
	if (new_cons) {
	    G2int_available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = g2int_replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = key;
	M_CDR(gensymed_symbol_1) = entry;
	inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	temp = g2int_make_binary_tree_element_1(FIX(key_hash),Nil,Nil,
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
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,insertion_depth) = insertion_point;
	temp = G2int_binary_tree_branch;
	ISVREF(temp,insertion_depth) = Kless_than;
	insertion_depth = insertion_depth + (SI_Long)1L;
	insertion_point = ISVREF(insertion_point,(SI_Long)1L);
    }
    else if (key_hash > insertion_point_hash) {
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,insertion_depth) = insertion_point;
	temp = G2int_binary_tree_branch;
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
	if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp_1 = g2int_equal_rule_context(key,entry_key);
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
	    goto end;
	}
	entry_cons = M_CDR(entry_cons);
	goto next_loop_1;
      end_loop_1:
	alist_entry_qm = Qnil;
      end:;
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
	    new_cons = G2int_available_gensym_conses;
	    if (new_cons) {
		G2int_available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = g2int_replenish_gensym_cons_pool();
	    new_cons = G2int_available_gensym_conses;
	    if (new_cons) {
		G2int_available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = g2int_replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_1) = key;
	    M_CDR(gensymed_symbol_1) = entry;
	    inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol) = alist;
	    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
	    SVREF(insertion_point,FIX((SI_Long)3L)) = gensymed_symbol;
	}
	return VALUES_1(entry);
    }
    goto next_loop;
  end_loop:;
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = g2int_replenish_gensym_cons_pool();
    new_cons = G2int_available_gensym_conses;
    if (new_cons) {
	G2int_available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = g2int_replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol_1) = key;
    M_CDR(gensymed_symbol_1) = entry;
    inline_note_allocate_cons(gensymed_symbol_1,Qg2int_gensym);
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qg2int_gensym);
    new_node = g2int_make_binary_tree_element_1(FIX(key_hash),Nil,Nil,
	    gensymed_symbol,FIX((SI_Long)0L));
    depth_of_insertion_parent = insertion_depth - (SI_Long)1L;
    heavy_ancestor = ISVREF(G2int_binary_tree_ancestor,heavy_ancestor_depth);
    if (EQ(ISVREF(G2int_binary_tree_branch,depth_of_insertion_parent),
	    Kless_than)) {
	temp = ISVREF(G2int_binary_tree_ancestor,depth_of_insertion_parent);
	SVREF(temp,FIX((SI_Long)1L)) = new_node;
    }
    else {
	temp = ISVREF(G2int_binary_tree_ancestor,depth_of_insertion_parent);
	SVREF(temp,FIX((SI_Long)2L)) = new_node;
    }
    adjust_point = heavy_ancestor_depth + (SI_Long)1L;
    ab_loop_bind_ = depth_of_insertion_parent;
    if (EQ(ISVREF(G2int_binary_tree_branch,heavy_ancestor_depth),Kless_than)) {
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
    temp = ISVREF(G2int_binary_tree_ancestor,adjust_point);
    svref_new_value = EQ(ISVREF(G2int_binary_tree_branch,adjust_point),
	    Kless_than) ? (SI_Long)1L : (SI_Long)-1L;
    ISVREF(temp,(SI_Long)4L) = FIX(svref_new_value);
    adjust_point = adjust_point + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    balance = ISVREF(heavy_ancestor,(SI_Long)4L);
    if (IFIX(balance) > (SI_Long)1L || IFIX(balance) < (SI_Long)-1L)
	g2int_rebalance_tree(binary_tree,heavy_ancestor_depth == 
		(SI_Long)0L ? Nil : ISVREF(G2int_binary_tree_ancestor,
		heavy_ancestor_depth - (SI_Long)1L),heavy_ancestor);
    return VALUES_1(entry);
}

/* REBALANCE-TREE */
Object g2int_rebalance_tree(binary_tree,heavy_parent,heavy_ancestor)
    Object binary_tree, heavy_parent, heavy_ancestor;
{
    Object heavy_child, svref_new_value, heavy_grandchild;
    Object greater_than_heavy_great_grandchild;
    Object less_than_heavy_great_grandchild;
    SI_Long imbalance_direction, heavy_child_balance_factor, depth_change;

    x_note_fn_call(22,27);
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
Object g2int_delete_balanced_binary_tree_entry(comparitor,key,binary_tree,
	    key_hash_init)
    Object comparitor, key, binary_tree, key_hash_init;
{
    Object deletion_point, old_key, old_entry, temp, alist, parent_cons;
    Object entry_cons, entry_cons_qm, parent_cons_qm, old_alist_cons;
    Object less_branch, greater_branch, branch_to_promote, successor_parent;
    Object successor_node, successor_less_branch, depth_reduced_qm, ancestor;
    Object temp_1;
    SI_Long key_hash, deletion_depth, deletion_point_hash, rebalance_depth;
    SI_Long deletion_parent_depth, balance, rebalance_point;
    Object result;

    x_note_fn_call(22,28);
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
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = deletion_point;
	temp = G2int_binary_tree_branch;
	ISVREF(temp,deletion_depth) = Kless_than;
	deletion_depth = deletion_depth + (SI_Long)1L;
	deletion_point = ISVREF(deletion_point,(SI_Long)1L);
    }
    else if (key_hash > deletion_point_hash) {
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = deletion_point;
	temp = G2int_binary_tree_branch;
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
		goto end;
	    }
	    parent_cons = entry_cons;
	    entry_cons = CDR(entry_cons);
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_2(Nil,Nil);
	    goto end;
	    result = VALUES_1(Qnil);
	  end:;
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
	    inline_note_reclaim_cons(old_alist_cons,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(old_alist_cons) = temp;
	    G2int_available_gensym_conses = old_alist_cons;
	    inline_note_reclaim_cons(entry_cons_qm,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(entry_cons_qm) = temp;
	    G2int_available_gensym_conses = entry_cons_qm;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
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
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,rebalance_depth) = greater_branch;
	temp = G2int_binary_tree_branch;
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
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,rebalance_depth) = successor_parent;
	temp = G2int_binary_tree_branch;
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
	temp = G2int_binary_tree_ancestor;
	ISVREF(temp,deletion_depth) = successor_node;
	temp = G2int_binary_tree_branch;
	ISVREF(temp,deletion_depth) = Kgreater_than;
	rebalance_depth = rebalance_depth + (SI_Long)1L;
	branch_to_promote = successor_node;
	goto end_2;
	branch_to_promote = Qnil;
      end_2:;
    }
    g2int_reclaim_binary_tree_element_1(deletion_point);
    if (deletion_parent_depth == (SI_Long)-1L)
	M_CDR(binary_tree) = branch_to_promote;
    else if (EQ(ISVREF(G2int_binary_tree_branch,deletion_parent_depth),
	    Kless_than)) {
	temp = ISVREF(G2int_binary_tree_ancestor,deletion_parent_depth);
	SVREF(temp,FIX((SI_Long)1L)) = branch_to_promote;
    }
    else {
	temp = ISVREF(G2int_binary_tree_ancestor,deletion_parent_depth);
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
    ancestor = ISVREF(G2int_binary_tree_ancestor,rebalance_point);
    temp_1 = ISVREF(G2int_binary_tree_branch,rebalance_point);
    if (EQ(temp_1,Kless_than)) {
	temp = FIXNUM_SUB1(ISVREF(ancestor,(SI_Long)4L));
	balance = IFIX(SVREF(ancestor,FIX((SI_Long)4L)) = temp);
	if (balance == (SI_Long)-1L)
	    depth_reduced_qm = Nil;
	else if (balance == (SI_Long)-2L) {
	    if (IFIX(g2int_rebalance_tree(binary_tree,rebalance_point != 
		    (SI_Long)0L ? ISVREF(G2int_binary_tree_ancestor,
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
	    if (IFIX(g2int_rebalance_tree(binary_tree,rebalance_point != 
		    (SI_Long)0L ? ISVREF(G2int_binary_tree_ancestor,
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

Object G2int_the_type_description_of_skip_list_element = UNBOUND;

Object G2int_chain_of_available_skip_list_elements = UNBOUND;

Object G2int_skip_list_element_count = UNBOUND;

/* RECLAIM-SKIP-LIST-ELEMENT-INTERNAL-1 */
Object g2int_reclaim_skip_list_element_internal_1(skip_list_element)
    Object skip_list_element;
{
    Object svref_new_value;

    x_note_fn_call(22,29);
    inline_note_reclaim_cons(skip_list_element,Nil);
    svref_new_value = G2int_chain_of_available_skip_list_elements;
    SVREF(skip_list_element,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_skip_list_elements = skip_list_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SKIP-LIST-ELEMENT */
Object g2int_reclaim_structure_for_skip_list_element(skip_list_element)
    Object skip_list_element;
{
    x_note_fn_call(22,30);
    return g2int_reclaim_skip_list_element_internal_1(skip_list_element);
}

/* MAKE-PERMANENT-SKIP-LIST-ELEMENT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_skip_list_element_structure_internal()
{
    Object def_structure_skip_list_element_variable, the_array;
    Object defstruct_g2_skip_list_element_variable, svref_new_value;
    SI_Long skip_list_element_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,31);
    def_structure_skip_list_element_variable = Nil;
    skip_list_element_count_new_value = 
	    IFIX(G2int_skip_list_element_count) + (SI_Long)100L;
    G2int_skip_list_element_count = FIX(skip_list_element_count_new_value);
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
	svref_new_value = G2int_chain_of_available_skip_list_elements;
	SVREF(def_structure_skip_list_element_variable,FIX((SI_Long)0L)) = 
		svref_new_value;
	G2int_chain_of_available_skip_list_elements = 
		def_structure_skip_list_element_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_skip_list_element_variable);
}

/* MAKE-SKIP-LIST-ELEMENT-1 */
Object g2int_make_skip_list_element_1(skip_list_element_hash_number,
	    skip_list_element_key,skip_list_element_entry,
	    skip_list_element_top_level)
    Object skip_list_element_hash_number, skip_list_element_key;
    Object skip_list_element_entry, skip_list_element_top_level;
{
    Object def_structure_skip_list_element_variable;

    x_note_fn_call(22,32);
    def_structure_skip_list_element_variable = 
	    G2int_chain_of_available_skip_list_elements;
    if (def_structure_skip_list_element_variable)
	G2int_chain_of_available_skip_list_elements = 
		ISVREF(def_structure_skip_list_element_variable,(SI_Long)0L);
    else
	def_structure_skip_list_element_variable = 
		g2int_make_permanent_skip_list_element_structure_internal();
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
Object g2int_reclaim_skip_list_element(element)
    Object element;
{
    Object temp;

    x_note_fn_call(22,33);
    g2int_reclaim_managed_simple_vector_for_skip_list(ISVREF(element,
	    (SI_Long)0L));
    SVREF(element,FIX((SI_Long)0L)) = Nil;
    temp = g2int_reclaim_skip_list_element_internal_1(element);
    return VALUES_1(temp);
}

/* FLATTEN-SKIP-LIST */
Object g2int_flatten_skip_list(skip_list)
    Object skip_list;
{
    Object gensymed_symbol, head, tail, node, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(22,34);
    gensymed_symbol = skip_list;
    head = CAR(gensymed_symbol);
    tail = CDR(gensymed_symbol);
    node = ISVREF(ISVREF(head,(SI_Long)0L),(SI_Long)0L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (EQ(node,tail))
	goto end_loop;
    ab_loopvar__2 = g2int_gensym_cons_1(g2int_gensym_cons_1(ISVREF(node,
	    (SI_Long)2L),ISVREF(node,(SI_Long)3L)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    node = ISVREF(ISVREF(node,(SI_Long)0L),(SI_Long)0L);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* LOOKUP-SKIP-LIST-ENTRY */
Object g2int_lookup_skip_list_entry(skip_list_element,max_level_init,
	    key_comparitor,key,key_hash_init)
    Object skip_list_element, max_level_init, key_comparitor, key;
    Object key_hash_init;
{
    Object pred, curr, entry_hash, entry_key, temp_1;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;
    char temp;

    x_note_fn_call(22,35);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    pred = M_CAR(skip_list_element);
    curr = Nil;
    level = max_level;
    ab_loop_bind_ = bottom_level;
  next_loop:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ISVREF(ISVREF(pred,(SI_Long)0L),level);
    entry_hash = Nil;
  next_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    temp = IFIX(entry_hash) < key_hash;
    if (temp);
    else if (IFIX(entry_hash) == key_hash) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp_1 = g2int_equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp =  !TRUEP(temp_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	pred = curr;
	curr = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    }
    else
	goto end;
    goto next_loop_1;
  end_loop_1:
  end:;
    level = level - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp_1 = g2int_equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp_1 = temp_1 ? ISVREF(curr,(SI_Long)3L) : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

Object G2int_half_of_most_positive_fixnum = UNBOUND;

/* RANDOM-LEVEL */
Object g2int_random_level(max_level_init)
    Object max_level_init;
{
    Object level, temp;
    SI_Long max_level;

    x_note_fn_call(22,36);
    max_level = IFIX(max_level_init);
    level = FIX((SI_Long)0L);
  next_loop:
    if ( !((SI_Long)2L * IFIX(l_random(G2int_half_of_most_positive_fixnum,
	    _)) < IFIX(G2int_half_of_most_positive_fixnum) && IFIX(level) 
	    < max_level))
	goto end_loop;
    level = FIXNUM_ADD1(level);
    goto next_loop;
  end_loop:
    temp = level;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

Object G2int_skip_list_find_preds = UNBOUND;

Object G2int_skip_list_find_succs = UNBOUND;

/* SKIP-LIST-FIND */
Object g2int_skip_list_find(skip_list,max_level,key_comparitor,key,hash,
	    preds,succs)
    Object skip_list, max_level, key_comparitor, key, hash, preds, succs;
{
    Object pred, curr, entry_hash, entry_key, temp_1;
    SI_Long bottom_level, level, ab_loop_bind_;
    char temp;

    x_note_fn_call(22,37);
    bottom_level = (SI_Long)0L;
    pred = skip_list;
    curr = Nil;
    level = IFIX(max_level);
    ab_loop_bind_ = bottom_level;
  next_loop:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ISVREF(ISVREF(pred,(SI_Long)0L),level);
    entry_hash = Nil;
  next_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    temp = FIXNUM_LT(entry_hash,hash);
    if (temp);
    else if (FIXNUM_EQ(entry_hash,hash)) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp_1 = EQUAL(key,entry_key) ? T : Nil;
	else if (EQ(key_comparitor,Qstring_eq))
	    temp_1 = string_eq(2,key,entry_key);
	else if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp_1 = g2int_equal_rule_context(key,entry_key);
	else
	    temp_1 = FUNCALL_2(key_comparitor,key,entry_key);
	temp =  !TRUEP(temp_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	pred = curr;
	curr = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    }
    else
	goto end;
    goto next_loop_1;
  end_loop_1:
  end:;
    ISVREF(preds,level) = pred;
    ISVREF(succs,level) = curr;
    level = level - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (FIXNUM_EQ(ISVREF(curr,(SI_Long)1L),hash)) {
	entry_key = ISVREF(curr,(SI_Long)2L);
	if (EQ(key_comparitor,Qequal))
	    temp = EQUAL(key,entry_key);
	else if (EQ(key_comparitor,Qstring_eq))
	    temp = TRUEP(string_eq(2,key,entry_key));
	else if (EQ(key_comparitor,Qg2int_equal_rule_context))
	    temp = TRUEP(g2int_equal_rule_context(key,entry_key));
	else
	    temp = TRUEP(FUNCALL_2(key_comparitor,key,entry_key));
    }
    else
	temp = TRUEP(Nil);
    return VALUES_1(temp ? curr : Nil);
}

/* SET-SKIP-LIST-ENTRY */
Object g2int_set_skip_list_entry(skip_list,max_level_init,key_comparitor,
	    mutator_function_qm,mutate_old_entry_qm,key,key_hash_init,entry)
    Object skip_list, max_level_init, key_comparitor, mutator_function_qm;
    Object mutate_old_entry_qm, key, key_hash_init, entry;
{
    Object head, preds, succs, insertion_point, pred_0, top_level, node, next;
    Object new_node, succ, pred, svref_arg_1;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;

    x_note_fn_call(22,38);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    head = M_CAR(M_CDR(skip_list));
    preds = G2int_skip_list_find_preds;
    succs = G2int_skip_list_find_succs;
    insertion_point = g2int_skip_list_find(head,FIX(max_level),
	    key_comparitor,key,FIX(key_hash),preds,succs);
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
    }
    else {
	pred_0 = ISVREF(preds,bottom_level);
	top_level = IFIX(ISVREF(pred_0,(SI_Long)1L)) == key_hash ? 
		ISVREF(pred_0,(SI_Long)4L) : 
		g2int_random_level(FIX(max_level));
	node = g2int_make_skip_list_element_1(FIX(key_hash),key,entry,
		top_level);
	next = 
		g2int_allocate_managed_simple_vector_for_skip_list(FIXNUM_ADD1(top_level));
	SVREF(node,FIX((SI_Long)0L)) = next;
	new_node = node;
	level = bottom_level;
	ab_loop_bind_ = IFIX(top_level);
	succ = Nil;
	pred = Nil;
      next_loop:
	if (level > ab_loop_bind_)
	    goto end_loop;
	succ = ISVREF(succs,level);
	pred = ISVREF(preds,level);
	svref_arg_1 = ISVREF(new_node,(SI_Long)0L);
	ISVREF(svref_arg_1,level) = succ;
	svref_arg_1 = ISVREF(pred,(SI_Long)0L);
	ISVREF(svref_arg_1,level) = new_node;
	level = level + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(entry);
}

/* DELETE-SKIP-LIST-ENTRY */
Object g2int_delete_skip_list_entry(comparitor,key,skip_list,
	    max_level_init,key_hash_init)
    Object comparitor, key, skip_list, max_level_init, key_hash_init;
{
    Object head, preds, succs, deletion_point, node_to_remove, old_key;
    Object old_entry, pred, svref_arg_1, svref_new_value;
    SI_Long max_level, key_hash, bottom_level, level, ab_loop_bind_;

    x_note_fn_call(22,39);
    max_level = IFIX(max_level_init);
    key_hash = IFIX(key_hash_init);
    bottom_level = (SI_Long)0L;
    head = M_CAR(M_CDR(skip_list));
    preds = G2int_skip_list_find_preds;
    succs = G2int_skip_list_find_succs;
    deletion_point = g2int_skip_list_find(head,FIX(max_level),comparitor,
	    key,FIX(key_hash),preds,succs);
    if ( !TRUEP(deletion_point))
	return VALUES_2(Nil,Nil);
    node_to_remove = deletion_point;
    old_key = ISVREF(deletion_point,(SI_Long)2L);
    old_entry = ISVREF(deletion_point,(SI_Long)3L);
    level = IFIX(ISVREF(node_to_remove,(SI_Long)4L));
    ab_loop_bind_ = bottom_level;
    pred = Nil;
  next_loop:
    if (level < ab_loop_bind_)
	goto end_loop;
    pred = ISVREF(preds,level);
    if (EQ(ISVREF(ISVREF(pred,(SI_Long)0L),level),node_to_remove)) {
	svref_arg_1 = ISVREF(pred,(SI_Long)0L);
	svref_new_value = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),level);
	ISVREF(svref_arg_1,level) = svref_new_value;
    }
    level = level - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    g2int_reclaim_skip_list_element(node_to_remove);
    return VALUES_2(old_key,old_entry);
}

/* MAKE-INDEX-SPACE-VECTOR */
Object g2int_make_index_space_vector()
{
    Object new_vector, gensymed_symbol, gensymed_symbol_2;
    SI_Long gensymed_symbol_1, index_1, ab_loop_bind_;

    x_note_fn_call(22,40);
    new_vector = g2int_allocate_managed_simple_vector(FIX((SI_Long)1024L));
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

Object G2int_the_type_description_of_index_space = UNBOUND;

Object G2int_chain_of_available_index_spaces = UNBOUND;

Object G2int_index_space_count = UNBOUND;

/* RECLAIM-INDEX-SPACE-1 */
Object g2int_reclaim_index_space_1(index_space)
    Object index_space;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(22,41);
    inline_note_reclaim_cons(index_space,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = index_space;
    g2int_reclaim_vector_of_index_subspace_vectors(ISVREF(index_space,
	    (SI_Long)2L));
    SVREF(index_space,FIX((SI_Long)2L)) = Nil;
    g2int_reclaim_gensym_list_1(ISVREF(index_space,(SI_Long)5L));
    SVREF(index_space,FIX((SI_Long)5L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_index_spaces;
    SVREF(index_space,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_index_spaces = index_space;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INDEX-SPACE */
Object g2int_reclaim_structure_for_index_space(index_space)
    Object index_space;
{
    x_note_fn_call(22,42);
    return g2int_reclaim_index_space_1(index_space);
}

static Object Qg2_defstruct_structure_name_index_space_g2_struct;  /* g2-defstruct-structure-name::index-space-g2-struct */

/* MAKE-PERMANENT-INDEX-SPACE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_index_space_structure_internal()
{
    Object def_structure_index_space_variable, index_space_count_new_value;
    Object defstruct_g2_index_space_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,43);
    def_structure_index_space_variable = Nil;
    index_space_count_new_value = FIXNUM_ADD1(G2int_index_space_count);
    G2int_index_space_count = index_space_count_new_value;
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
Object g2int_make_index_space_1(index_space_name,
	    index_space_object_reclaimer_qm)
    Object index_space_name, index_space_object_reclaimer_qm;
{
    Object def_structure_index_space_variable, svref_new_value;

    x_note_fn_call(22,44);
    def_structure_index_space_variable = G2int_chain_of_available_index_spaces;
    if (def_structure_index_space_variable) {
	G2int_chain_of_available_index_spaces = 
		ISVREF(def_structure_index_space_variable,(SI_Long)0L);
	SVREF(def_structure_index_space_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_index_space_g2_struct;
    }
    else
	def_structure_index_space_variable = 
		g2int_make_permanent_index_space_structure_internal();
    inline_note_allocate_cons(def_structure_index_space_variable,Nil);
    SVREF(def_structure_index_space_variable,FIX((SI_Long)1L)) = 
	    index_space_name;
    SVREF(def_structure_index_space_variable,FIX((SI_Long)6L)) = 
	    index_space_object_reclaimer_qm;
    svref_new_value = g2int_make_index_space_vector();
    SVREF(def_structure_index_space_variable,FIX((SI_Long)2L)) = 
	    svref_new_value;
    ISVREF(def_structure_index_space_variable,(SI_Long)3L) = FIX((SI_Long)-1L);
    ISVREF(def_structure_index_space_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    SVREF(def_structure_index_space_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_index_space_variable);
}

/* RECLAIM-IF-INDEX-SPACE */
Object g2int_reclaim_if_index_space(index_space_qm)
    Object index_space_qm;
{
    x_note_fn_call(22,45);
    if (index_space_qm)
	g2int_reclaim_index_space_1(index_space_qm);
    return VALUES_1(Nil);
}

/* RECLAIM-VECTOR-OF-INDEX-SUBSPACE-VECTORS */
Object g2int_reclaim_vector_of_index_subspace_vectors(vector_of_index_subspace_vectors)
    Object vector_of_index_subspace_vectors;
{
    Object index_space_name, index_space_object_reclaimer_qm;
    Object nil_unreclaimed_as_yet_p, index_subspace_vector_qm, fn, object_qm;
    SI_Long i, ab_loop_bind_, j;

    x_note_fn_call(22,46);
    index_space_name = ISVREF(G2int_structure_being_reclaimed,(SI_Long)1L);
    index_space_object_reclaimer_qm = 
	    ISVREF(G2int_structure_being_reclaimed,(SI_Long)6L);
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
    g2int_reclaim_managed_simple_vector(index_subspace_vector_qm);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return g2int_reclaim_managed_simple_vector(vector_of_index_subspace_vectors);
}

/* ASSIGN-INDEX-IN-INDEX-SPACE */
Object g2int_assign_index_in_index_space(index_space)
    Object index_space;
{
    Object gensym_pop_store, cons_1, next_cons, cdr_new_value, index_1, temp;

    x_note_fn_call(22,47);
    if (ISVREF(index_space,(SI_Long)5L)) {
	gensym_pop_store = Nil;
	cons_1 = ISVREF(index_space,(SI_Long)5L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    cdr_new_value = G2int_available_gensym_conses;
	    M_CDR(cons_1) = cdr_new_value;
	    G2int_available_gensym_conses = cons_1;
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
	    g2int_enlarge_index_space(index_space,Nil);
	    temp = ISVREF(index_space,(SI_Long)4L);
	    return VALUES_2(index_1,temp);
	}
	else
	    return VALUES_1(index_1);
    }
}

/* DEASSIGN-INDEX-IN-INDEX-SPACE */
Object g2int_deassign_index_in_index_space(index_1,index_space)
    Object index_1, index_space;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(22,48);
    gensym_push_modify_macro_arg = index_1;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(index_space,(SI_Long)5L);
    svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
    return VALUES_1(SVREF(index_space,FIX((SI_Long)5L)) = svref_new_value);
}

Object G2int_enlarge_index_space_error_message = UNBOUND;

/* ENLARGE-INDEX-SPACE */
Object g2int_enlarge_index_space(index_space,minimum_new_index_limit_qm)
    Object index_space, minimum_new_index_limit_qm;
{
    Object spine_vector, spine_vector_length, new_index_subspace_index;
    Object new_spine_vector, temp, svref_new_value;
    SI_Long new_spine_vector_length, i, ab_loop_bind_, svref_new_value_1;

    x_note_fn_call(22,49);
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
		g2int_allocate_managed_simple_vector(FIX(new_spine_vector_length));
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
	g2int_reclaim_managed_simple_vector(spine_vector);
	SVREF(index_space,FIX((SI_Long)2L)) = new_spine_vector;
	spine_vector = new_spine_vector;
	spine_vector_length = FIX(new_spine_vector_length);
    }
    temp = ISVREF(index_space,(SI_Long)2L);
    svref_new_value = g2int_make_index_space_vector();
    SVREF(temp,new_index_subspace_index) = svref_new_value;
    svref_new_value_1 = IFIX(ISVREF(index_space,(SI_Long)4L)) + (SI_Long)1024L;
    ISVREF(index_space,(SI_Long)4L) = FIX(svref_new_value_1);
    if (FIXNUM_GT(ISVREF(index_space,(SI_Long)4L),minimum_new_index_limit_qm))
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

Object G2int_the_type_description_of_queue_element = UNBOUND;

Object G2int_chain_of_available_queue_elements = UNBOUND;

Object G2int_queue_element_count = UNBOUND;

/* RECLAIM-QUEUE-ELEMENT-1 */
Object g2int_reclaim_queue_element_1(queue_element)
    Object queue_element;
{
    Object svref_new_value;

    x_note_fn_call(22,50);
    inline_note_reclaim_cons(queue_element,Nil);
    svref_new_value = G2int_chain_of_available_queue_elements;
    SVREF(queue_element,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_queue_elements = queue_element;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-QUEUE-ELEMENT */
Object g2int_reclaim_structure_for_queue_element(queue_element)
    Object queue_element;
{
    x_note_fn_call(22,51);
    return g2int_reclaim_queue_element_1(queue_element);
}

/* MAKE-PERMANENT-QUEUE-ELEMENT-STRUCTURE-INTERNAL */
Object g2int_make_permanent_queue_element_structure_internal()
{
    Object def_structure_queue_element_variable, queue_element_count_new_value;
    Object the_array, defstruct_g2_queue_element_variable;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,52);
    def_structure_queue_element_variable = Nil;
    queue_element_count_new_value = FIXNUM_ADD1(G2int_queue_element_count);
    G2int_queue_element_count = queue_element_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
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
	defstruct_g2_queue_element_variable = the_array;
	def_structure_queue_element_variable = 
		defstruct_g2_queue_element_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_queue_element_variable);
}

/* MAKE-QUEUE-ELEMENT-1 */
Object g2int_make_queue_element_1(queue_next_element,
	    queue_previous_element,queue_datum)
    Object queue_next_element, queue_previous_element, queue_datum;
{
    Object def_structure_queue_element_variable;

    x_note_fn_call(22,53);
    def_structure_queue_element_variable = 
	    G2int_chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	G2int_chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		g2int_make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = 
	    queue_next_element;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
	    queue_previous_element;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = queue_datum;
    return VALUES_1(def_structure_queue_element_variable);
}

Object G2int_constant_queue_marker = UNBOUND;

/* RELEASE-QUEUE-NODE */
Object g2int_release_queue_node(node)
    Object node;
{
    Object svref_new_value;

    x_note_fn_call(22,54);
    if ( !TRUEP(node))
	return VALUES_1(Nil);
    inline_note_reclaim_cons(node,Nil);
    svref_new_value = G2int_chain_of_available_queue_elements;
    SVREF(node,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_queue_elements = node;
    return VALUES_1(Nil);
}

/* MAKE-EMPTY-CONSTANT-QUEUE */
Object g2int_make_empty_constant_queue()
{
    Object def_structure_queue_element_variable, new_queue;

    x_note_fn_call(22,55);
    def_structure_queue_element_variable = 
	    G2int_chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	G2int_chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		g2int_make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = 
	    G2int_constant_queue_marker;
    new_queue = def_structure_queue_element_variable;
    SVREF(new_queue,FIX((SI_Long)0L)) = new_queue;
    SVREF(new_queue,FIX((SI_Long)1L)) = new_queue;
    return VALUES_1(new_queue);
}

/* CONSTANT-QUEUE-READ */
Object g2int_constant_queue_read varargs_1(int, n)
{
    Object cursor;
    Object value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(22,56);
    INIT_ARGS_nonrelocating();
    cursor = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    value = ISVREF(cursor,(SI_Long)2L);
    return VALUES_1(value);
}

/* RECLAIM-CONSTANT-QUEUE */
Object g2int_reclaim_constant_queue(constant_queue)
    Object constant_queue;
{
    Object element, temp, svref_new_value;

    x_note_fn_call(22,57);
    element = ISVREF(constant_queue,(SI_Long)0L);
  next_loop:
    if (EQ(element,constant_queue))
	goto end_loop;
    temp = ISVREF(element,(SI_Long)0L);
    inline_note_reclaim_cons(element,Nil);
    svref_new_value = G2int_chain_of_available_queue_elements;
    SVREF(element,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_queue_elements = element;
    element = temp;
    goto next_loop;
  end_loop:;
    SVREF(constant_queue,FIX((SI_Long)2L)) = Nil;
    inline_note_reclaim_cons(constant_queue,Nil);
    svref_new_value = G2int_chain_of_available_queue_elements;
    SVREF(constant_queue,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_queue_elements = constant_queue;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-SEARCH-AND-DELETE */
Object g2int_constant_queue_search_and_delete(constant_queue,datum)
    Object constant_queue, datum;
{
    Object head, queue_element, gensymed_symbol, gensymed_symbol_1;
    Object svref_new_value;

    x_note_fn_call(22,58);
    head = ISVREF(constant_queue,(SI_Long)0L);
    queue_element = head;
  next_loop:
    if (EQ(queue_element,constant_queue))
	goto end_loop;
    if (EQ(datum,ISVREF(queue_element,(SI_Long)2L))) {
	gensymed_symbol = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol_1 = ISVREF(queue_element,(SI_Long)1L);
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = gensymed_symbol;
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	inline_note_reclaim_cons(queue_element,Nil);
	svref_new_value = G2int_chain_of_available_queue_elements;
	SVREF(queue_element,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_queue_elements = queue_element;
	goto end_loop;
    }
    queue_element = ISVREF(queue_element,(SI_Long)0L);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-SEARCH-AND-DELETE-ALL */
Object g2int_constant_queue_search_and_delete_all(constant_queue,datum)
    Object constant_queue, datum;
{
    Object head, queue_element, next_queue_element, gensymed_symbol;
    Object gensymed_symbol_1, svref_new_value;

    x_note_fn_call(22,59);
    head = ISVREF(constant_queue,(SI_Long)0L);
    queue_element = head;
    next_queue_element = Nil;
  next_loop:
    if (EQ(queue_element,constant_queue))
	goto end_loop;
    next_queue_element = ISVREF(queue_element,(SI_Long)0L);
    if (EQ(datum,ISVREF(queue_element,(SI_Long)2L))) {
	gensymed_symbol = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol_1 = ISVREF(queue_element,(SI_Long)1L);
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = gensymed_symbol;
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	inline_note_reclaim_cons(queue_element,Nil);
	svref_new_value = G2int_chain_of_available_queue_elements;
	SVREF(queue_element,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_queue_elements = queue_element;
    }
    queue_element = next_queue_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CONSTANT-QUEUE-LENGTH */
Object g2int_constant_queue_length(constant_queue)
    Object constant_queue;
{
    Object queue, next_queue_element, element;
    SI_Long ab_loopvar_;

    x_note_fn_call(22,60);
    if ( !TRUEP(constant_queue))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	queue = constant_queue;
	next_queue_element = Nil;
	element = Nil;
	ab_loopvar_ = (SI_Long)0L;
	next_queue_element = ISVREF(queue,(SI_Long)0L);
      next_loop:
	if (EQ(next_queue_element,queue))
	    goto end_loop;
	element = ISVREF(next_queue_element,(SI_Long)2L);
	next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
	if (element)
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(FIX(ab_loopvar_));
	return VALUES_1(Qnil);
    }
}

/* CONSTANT-QUEUE-NREVERSE */
Object g2int_constant_queue_nreverse(constant_queue)
    Object constant_queue;
{
    Object new_constant_queue, queue, next_queue_element, block;
    Object gensymed_symbol, def_structure_queue_element_variable;
    Object gensymed_symbol_1, temp;

    x_note_fn_call(22,61);
    new_constant_queue = g2int_make_empty_constant_queue();
    queue = constant_queue;
    next_queue_element = Nil;
    block = Nil;
    next_queue_element = ISVREF(queue,(SI_Long)0L);
  next_loop:
    if (EQ(next_queue_element,queue))
	goto end_loop;
    block = ISVREF(next_queue_element,(SI_Long)2L);
    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
    gensymed_symbol = ISVREF(new_constant_queue,(SI_Long)0L);
    def_structure_queue_element_variable = 
	    G2int_chain_of_available_queue_elements;
    if (def_structure_queue_element_variable)
	G2int_chain_of_available_queue_elements = 
		ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
    else
	def_structure_queue_element_variable = 
		g2int_make_permanent_queue_element_structure_internal();
    inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = 
	    gensymed_symbol;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
	    new_constant_queue;
    SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = block;
    gensymed_symbol_1 = def_structure_queue_element_variable;
    SVREF(new_constant_queue,FIX((SI_Long)0L)) = gensymed_symbol_1;
    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
    goto next_loop;
  end_loop:
    g2int_reclaim_constant_queue(constant_queue);
    temp = new_constant_queue;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* CONSTANT-QUEUE-NTH */
Object g2int_constant_queue_nth(n_1,constant_queue)
    Object n_1, constant_queue;
{
    Object queue, next_queue_element, block, temp;
    SI_Long count_1;

    x_note_fn_call(22,62);
    count_1 = (SI_Long)0L;
    queue = constant_queue;
    next_queue_element = Nil;
    block = Nil;
    next_queue_element = ISVREF(queue,(SI_Long)0L);
  next_loop:
    if (EQ(next_queue_element,queue))
	goto end_loop;
    block = ISVREF(next_queue_element,(SI_Long)2L);
    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
    if (count_1 == IFIX(n_1)) {
	temp = block;
	goto end;
    }
    count_1 = count_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

Object G2int_memory_limit_variable_names_for_decacheable_structures = UNBOUND;

Object G2int_names_and_sizes_for_decacheable_structures = UNBOUND;

Object G2int_default_decacheable_structure_allocation_limit = UNBOUND;

Object G2int_minimum_decacheable_structure_allocation_limit = UNBOUND;

Object G2int_decache_occurred_since_last_updateqm = UNBOUND;

Object G2int_global_desired_thrashing_setpoint = UNBOUND;

Object G2int_time_of_last_thrashing_cost_update = UNBOUND;

Object G2int_thrashing_cost_update_interval = UNBOUND;

Object G2int_long_thrashing_cost_update_interval = UNBOUND;

Object G2int_positive_thrashing_error_gain = UNBOUND;

Object G2int_negative_thrashing_error_gain = UNBOUND;

Object G2int_simulation_no_value = UNBOUND;

Object G2int_combiners_for_defun_incremental = UNBOUND;

Object G2int_defun_incremental_compile_time_registry = UNBOUND;

Object G2int_defun_incremental_runtime_registry = UNBOUND;

Object G2int_the_type_description_of_queue = UNBOUND;

Object G2int_chain_of_available_queues = UNBOUND;

Object G2int_queue_count = UNBOUND;

/* RECLAIM-QUEUE-INTERNAL-1 */
Object g2int_reclaim_queue_internal_1(queue)
    Object queue;
{
    Object svref_new_value;

    x_note_fn_call(22,63);
    inline_note_reclaim_cons(queue,Nil);
    svref_new_value = G2int_chain_of_available_queues;
    SVREF(queue,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_queues = queue;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-QUEUE */
Object g2int_reclaim_structure_for_queue(queue)
    Object queue;
{
    x_note_fn_call(22,64);
    return g2int_reclaim_queue_internal_1(queue);
}

static Object Qg2_defstruct_structure_name_queue_g2_struct;  /* g2-defstruct-structure-name::queue-g2-struct */

/* MAKE-PERMANENT-QUEUE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_queue_structure_internal()
{
    Object def_structure_queue_variable, queue_count_new_value;
    Object defstruct_g2_queue_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(22,65);
    def_structure_queue_variable = Nil;
    queue_count_new_value = FIXNUM_ADD1(G2int_queue_count);
    G2int_queue_count = queue_count_new_value;
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
Object g2int_make_queue_internal_1(queue_head_internal,queue_tail_internal)
    Object queue_head_internal, queue_tail_internal;
{
    Object def_structure_queue_variable;

    x_note_fn_call(22,66);
    def_structure_queue_variable = G2int_chain_of_available_queues;
    if (def_structure_queue_variable) {
	G2int_chain_of_available_queues = 
		ISVREF(def_structure_queue_variable,(SI_Long)0L);
	SVREF(def_structure_queue_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_queue_g2_struct;
    }
    else
	def_structure_queue_variable = 
		g2int_make_permanent_queue_structure_internal();
    inline_note_allocate_cons(def_structure_queue_variable,Nil);
    SVREF(def_structure_queue_variable,FIX((SI_Long)1L)) = queue_head_internal;
    SVREF(def_structure_queue_variable,FIX((SI_Long)2L)) = queue_tail_internal;
    return VALUES_1(def_structure_queue_variable);
}

Object G2int_current_computation_flags = UNBOUND;

Object G2int_special_setf_method_prop = UNBOUND;

void utilities2_INIT()
{
    Object temp, reclaim_structure_for_named_gensym_structure;
    Object reclaim_structure_for_binary_tree_element;
    Object reclaim_structure_for_skip_list_element;
    Object reclaim_structure_for_index_space;
    Object reclaim_structure_for_queue_element, reclaim_structure_for_queue;
    Object Qg2int_special_setf_method, Qg2int_set_serve_loose_ends_p;
    Object Qg2int_serve_loose_ends_p, AB_package;
    Object Qg2int_set_serve_only_permanent_items_p;
    Object Qg2int_serve_only_permanent_items_p;
    Object Qg2int_set_within_dynamic_extent_of_traced_rule_p;
    Object Qg2int_within_dynamic_extent_of_traced_rule_p;
    Object Qg2int_set_dont_forward_chain_from_rule;
    Object Qg2int_dont_forward_chain_from_rule;
    Object Qg2int_set_dont_compute_new_variable_values;
    Object Qg2int_dont_compute_new_variable_values;
    Object Qg2int_set_default_dont_compute_new_variable_values;
    Object Qg2int_default_dont_compute_new_variable_values;
    Object Qg2int_set_attempting_network_read_access_p;
    Object Qg2int_attempting_network_read_access_p;
    Object Qg2int_set_attempting_network_write_access_p;
    Object Qg2int_attempting_network_write_access_p;
    Object Qg2int_set_role_serve_inactive_objectsqm;
    Object Qg2int_role_serve_inactive_objectsqm;
    Object Qg2int_set_no_wake_ups_during_role_serving;
    Object Qg2int_no_wake_ups_during_role_serving;
    Object Qg2int_set_force_new_request_for_value;
    Object Qg2int_force_new_request_for_value;
    Object Qg2int_set_final_evaluation_attemptqm;
    Object Qg2int_final_evaluation_attemptqm;
    Object Qg2int_set_cache_explanation_variablesqm;
    Object Qg2int_cache_explanation_variablesqm, Qg2int_utilities2;
    Object Qg2int_current_computation_flags, Qg2int_queue;
    Object Qg2int_reclaim_structure, Qg2int_queue_count;
    Object Qg2int_chain_of_available_queues, string_constant_7;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_4;
    Object Qg2int_simulation_no_value, string_constant_6, Kfuncall;
    Object list_constant_3, Qg2int_long_thrashing_cost_update_interval;
    Object Qg2int_fixnum_time_interval, list_constant_2;
    Object Qg2int_thrashing_cost_update_interval, list_constant_1;
    Object Qg2int_time_of_last_thrashing_cost_update;
    Object Qg2int_get_fixnum_time_function;
    Object Qg2int_global_desired_thrashing_setpoint;
    Object Qg2int_decache_occurred_since_last_updateqm, Kconstant_queue_marker;
    Object Qg2int_constant_queue_marker, Qg2int_queue_element;
    Object Qg2int_queue_element_count;
    Object Qg2int_chain_of_available_queue_elements;
    Object Qg2_defstruct_structure_name_queue_element_g2_struct;
    Object string_constant_5, string_constant_4;
    Object Qg2int_enlarge_index_space_error_message, Qg2int_index_space;
    Object Qg2int_index_space_count, Qg2int_chain_of_available_index_spaces;
    Object string_constant_3, Qg2int_skip_list_global_max_level;
    Object Qg2int_half_of_most_positive_fixnum, Qg2int_skip_list_element;
    Object Qg2int_skip_list_element_count;
    Object Qg2int_chain_of_available_skip_list_elements;
    Object Qg2_defstruct_structure_name_skip_list_element_g2_struct;
    Object string_constant_2, list_constant, Qg2int_binary_tree_branch;
    Object Qg2int_binary_tree_ancestor, Qg2int_binary_tree_element;
    Object Qg2int_binary_tree_element_count;
    Object Qg2int_chain_of_available_binary_tree_elements;
    Object Qg2_defstruct_structure_name_binary_tree_element_g2_struct;
    Object string_constant_1, Qg2int_named_gensym_structure;
    Object Qg2int_named_gensym_structure_count;
    Object Qg2int_chain_of_available_named_gensym_structures, string_constant;
    Object Qg2int_structure_being_reclaimed, Qg2int_structure_method_arglist;
    Object Qg2int_def_structure_slot_descriptions;

    x_note_fn_call(22,67);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_def_structure_slot_descriptions = 
	    STATIC_SYMBOL("DEF-STRUCTURE-SLOT-DESCRIPTIONS",AB_package);
    G2int_def_structure_slot_descriptions_prop = 
	    Qg2int_def_structure_slot_descriptions;
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    G2int_ab_name_of_unique_structure_type_prop = 
	    Qg2int_ab_name_of_unique_structure_type;
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    G2int_unique_structure_type_of_ab_nameqm_prop = 
	    Qg2int_unique_structure_type_of_ab_nameqm;
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    Qg2int_structure_method_arglist = 
	    STATIC_SYMBOL("STRUCTURE-METHOD-ARGLIST",AB_package);
    G2int_structure_method_arglist_prop = Qg2int_structure_method_arglist;
    Qg2int_structure_being_reclaimed = 
	    STATIC_SYMBOL("STRUCTURE-BEING-RECLAIMED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_structure_being_reclaimed,
	    G2int_structure_being_reclaimed);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_structure_being_reclaimed,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_named_gensym_structure_g2_struct = 
	    STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_named_gensym_structure = STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    Qg2int_named_gensym_structure,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_named_gensym_structure,
	    Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_named_gensym_structure == UNBOUND)
	G2int_the_type_description_of_named_gensym_structure = Nil;
    string_constant = STATIC_STRING("43Dy8l8m1m8m8k1l8k0000001l1m8o0klk0k0");
    temp = G2int_the_type_description_of_named_gensym_structure;
    G2int_the_type_description_of_named_gensym_structure = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_named_gensym_structure_g2_struct,
	    G2int_the_type_description_of_named_gensym_structure,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_named_gensym_structure,
	    G2int_the_type_description_of_named_gensym_structure,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_named_gensym_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-NAMED-GENSYM-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_named_gensym_structures,
	    G2int_chain_of_available_named_gensym_structures);
    g2int_record_system_variable(Qg2int_chain_of_available_named_gensym_structures,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_named_gensym_structure_count = 
	    STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_named_gensym_structure_count,
	    G2int_named_gensym_structure_count);
    g2int_record_system_variable(Qg2int_named_gensym_structure_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_named_gensym_structure = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_named_gensym_structure,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_named_gensym_structure,
	    reclaim_structure_for_named_gensym_structure);
    if (G2int_the_type_description_of_binary_tree_element == UNBOUND)
	G2int_the_type_description_of_binary_tree_element = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8l83Zy1m83Zy8k1l8k0000001n1m83Dy9k1m83Cy3-Wy1n8n83*Qy1p83Yy83*Oy83-0y83Xy83Wykpk0k0");
    temp = G2int_the_type_description_of_binary_tree_element;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qvector);
    G2int_the_type_description_of_binary_tree_element = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_1));
    Qg2_defstruct_structure_name_binary_tree_element_g2_struct = 
	    STATIC_SYMBOL("BINARY-TREE-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_binary_tree_element_g2_struct,
	    G2int_the_type_description_of_binary_tree_element,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_binary_tree_element = STATIC_SYMBOL("BINARY-TREE-ELEMENT",
	    AB_package);
    g2int_mutate_global_property(Qg2int_binary_tree_element,
	    G2int_the_type_description_of_binary_tree_element,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_binary_tree_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BINARY-TREE-ELEMENTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_binary_tree_elements,
	    G2int_chain_of_available_binary_tree_elements);
    g2int_record_system_variable(Qg2int_chain_of_available_binary_tree_elements,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_binary_tree_element_count = 
	    STATIC_SYMBOL("BINARY-TREE-ELEMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_binary_tree_element_count,
	    G2int_binary_tree_element_count);
    g2int_record_system_variable(Qg2int_binary_tree_element_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_binary_tree_element = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_binary_tree_element,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_binary_tree_element,
	    reclaim_structure_for_binary_tree_element);
    Qg2int_equal_rule_context = STATIC_SYMBOL("EQUAL-RULE-CONTEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_equal_rule_context,
	    STATIC_FUNCTION(g2int_equal_rule_context,NIL,FALSE,2,2));
    Qg2int_binary_tree_ancestor = STATIC_SYMBOL("BINARY-TREE-ANCESTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_binary_tree_ancestor,
	    G2int_binary_tree_ancestor);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    list_constant = STATIC_LIST((SI_Long)3L,Kfuncall,Qmake_array,
	    FIX((SI_Long)50L));
    g2int_record_system_variable(Qg2int_binary_tree_ancestor,
	    Qg2int_utilities2,list_constant,Qnil,Qt,Qnil,Qnil);
    Qg2int_binary_tree_branch = STATIC_SYMBOL("BINARY-TREE-BRANCH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_binary_tree_branch,
	    G2int_binary_tree_branch);
    g2int_record_system_variable(Qg2int_binary_tree_branch,
	    Qg2int_utilities2,list_constant,Qnil,Qt,Qnil,Qnil);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Kless_than = STATIC_SYMBOL("LESS-THAN",Pkeyword);
    Kgreater_than = STATIC_SYMBOL("GREATER-THAN",Pkeyword);
    if (G2int_the_type_description_of_skip_list_element == UNBOUND)
	G2int_the_type_description_of_skip_list_element = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8l83=xy1m83=xy8k1l8k0000001o1m83Dy9k1m83Cy3-Wy1n8n83*vy1o830-y830*y830+y830=y1m8p83=kykpk0k0");
    temp = G2int_the_type_description_of_skip_list_element;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qvector);
    G2int_the_type_description_of_skip_list_element = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_2));
    Qg2_defstruct_structure_name_skip_list_element_g2_struct = 
	    STATIC_SYMBOL("SKIP-LIST-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_skip_list_element_g2_struct,
	    G2int_the_type_description_of_skip_list_element,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_skip_list_element = STATIC_SYMBOL("SKIP-LIST-ELEMENT",AB_package);
    g2int_mutate_global_property(Qg2int_skip_list_element,
	    G2int_the_type_description_of_skip_list_element,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_skip_list_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SKIP-LIST-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_skip_list_elements,
	    G2int_chain_of_available_skip_list_elements);
    g2int_record_system_variable(Qg2int_chain_of_available_skip_list_elements,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_skip_list_element_count = 
	    STATIC_SYMBOL("SKIP-LIST-ELEMENT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_skip_list_element_count,
	    G2int_skip_list_element_count);
    g2int_record_system_variable(Qg2int_skip_list_element_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_skip_list_element = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_skip_list_element,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_skip_list_element,reclaim_structure_for_skip_list_element);
    Qg2int_half_of_most_positive_fixnum = 
	    STATIC_SYMBOL("HALF-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_half_of_most_positive_fixnum,
	    G2int_half_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qg2int_half_of_most_positive_fixnum,
	    g2int_chestnut_floorf_function(Most_positive_fixnum,
	    FIX((SI_Long)2L)));
    Qg2int_skip_list_global_max_level = 
	    STATIC_SYMBOL("SKIP-LIST-GLOBAL-MAX-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_skip_list_global_max_level,FIX((SI_Long)32L));
    if (G2int_skip_list_find_preds == UNBOUND)
	G2int_skip_list_find_preds = make_array(1,
		G2int_skip_list_global_max_level);
    if (G2int_skip_list_find_succs == UNBOUND)
	G2int_skip_list_find_succs = make_array(1,
		G2int_skip_list_global_max_level);
    Qg2_defstruct_structure_name_index_space_g2_struct = 
	    STATIC_SYMBOL("INDEX-SPACE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_index_space = STATIC_SYMBOL("INDEX-SPACE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_index_space_g2_struct,
	    Qg2int_index_space,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_index_space,
	    Qg2_defstruct_structure_name_index_space_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_index_space == UNBOUND)
	G2int_the_type_description_of_index_space = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8l83-ky1n83-ky8m8k1l8m0000001l1n8n83*iy1m83-ly83-mykrk0k0");
    temp = G2int_the_type_description_of_index_space;
    G2int_the_type_description_of_index_space = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_3));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_index_space_g2_struct,
	    G2int_the_type_description_of_index_space,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_index_space,
	    G2int_the_type_description_of_index_space,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_index_spaces = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INDEX-SPACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_index_spaces,
	    G2int_chain_of_available_index_spaces);
    g2int_record_system_variable(Qg2int_chain_of_available_index_spaces,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_index_space_count = STATIC_SYMBOL("INDEX-SPACE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_index_space_count,
	    G2int_index_space_count);
    g2int_record_system_variable(Qg2int_index_space_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_index_space = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_index_space,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_index_space,reclaim_structure_for_index_space);
    Qg2int_enlarge_index_space_error_message = 
	    STATIC_SYMBOL("ENLARGE-INDEX-SPACE-ERROR-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_enlarge_index_space_error_message,
	    G2int_enlarge_index_space_error_message);
    string_constant_4 = STATIC_STRING("Index space full!");
    SET_SYMBOL_VALUE(Qg2int_enlarge_index_space_error_message,
	    string_constant_4);
    if (G2int_the_type_description_of_queue_element == UNBOUND)
	G2int_the_type_description_of_queue_element = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8l83=Ly1m83=Ly8k1l8k0000001m1m83Dy9k1n8n83*oy1n83=Ny83=Oy83=Kyknk0k0");
    temp = G2int_the_type_description_of_queue_element;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qvector);
    G2int_the_type_description_of_queue_element = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    Qg2_defstruct_structure_name_queue_element_g2_struct = 
	    STATIC_SYMBOL("QUEUE-ELEMENT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_queue_element_g2_struct,
	    G2int_the_type_description_of_queue_element,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_queue_element = STATIC_SYMBOL("QUEUE-ELEMENT",AB_package);
    g2int_mutate_global_property(Qg2int_queue_element,
	    G2int_the_type_description_of_queue_element,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_queue_elements = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-QUEUE-ELEMENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_queue_elements,
	    G2int_chain_of_available_queue_elements);
    g2int_record_system_variable(Qg2int_chain_of_available_queue_elements,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_queue_element_count = STATIC_SYMBOL("QUEUE-ELEMENT-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_queue_element_count,
	    G2int_queue_element_count);
    g2int_record_system_variable(Qg2int_queue_element_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_queue_element = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_queue_element,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_queue_element,reclaim_structure_for_queue_element);
    Qg2int_constant_queue_marker = STATIC_SYMBOL("CONSTANT-QUEUE-MARKER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_constant_queue_marker,
	    G2int_constant_queue_marker);
    Kconstant_queue_marker = STATIC_SYMBOL("CONSTANT-QUEUE-MARKER",Pkeyword);
    SET_SYMBOL_VALUE(Qg2int_constant_queue_marker,Kconstant_queue_marker);
    if (G2int_memory_limit_variable_names_for_decacheable_structures == 
	    UNBOUND)
	G2int_memory_limit_variable_names_for_decacheable_structures = Nil;
    if (G2int_names_and_sizes_for_decacheable_structures == UNBOUND)
	G2int_names_and_sizes_for_decacheable_structures = Nil;
    G2int_default_decacheable_structure_allocation_limit = FIX((SI_Long)5L);
    G2int_minimum_decacheable_structure_allocation_limit = FIX((SI_Long)1L);
    Qg2int_decache_occurred_since_last_updateqm = 
	    STATIC_SYMBOL("DECACHE-OCCURRED-SINCE-LAST-UPDATE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_decache_occurred_since_last_updateqm,
	    G2int_decache_occurred_since_last_updateqm);
    g2int_record_system_variable(Qg2int_decache_occurred_since_last_updateqm,
	    Qg2int_utilities2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_global_desired_thrashing_setpoint = 
	    STATIC_SYMBOL("GLOBAL-DESIRED-THRASHING-SETPOINT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_global_desired_thrashing_setpoint,
	    G2int_global_desired_thrashing_setpoint);
    g2int_record_system_variable(Qg2int_global_desired_thrashing_setpoint,
	    Qg2int_utilities2,FIX((SI_Long)50L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_time_of_last_thrashing_cost_update = 
	    STATIC_SYMBOL("TIME-OF-LAST-THRASHING-COST-UPDATE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_time_of_last_thrashing_cost_update,
	    G2int_time_of_last_thrashing_cost_update);
    Qg2int_get_fixnum_time_function = 
	    STATIC_SYMBOL("GET-FIXNUM-TIME-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_fixnum_time_function,
	    STATIC_FUNCTION(g2int_get_fixnum_time_function,NIL,FALSE,0,0));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_get_fixnum_time_function);
    g2int_record_system_variable(Qg2int_time_of_last_thrashing_cost_update,
	    Qg2int_utilities2,list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_thrashing_cost_update_interval = 
	    STATIC_SYMBOL("THRASHING-COST-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_thrashing_cost_update_interval,
	    G2int_thrashing_cost_update_interval);
    Qg2int_fixnum_time_interval = STATIC_SYMBOL("FIXNUM-TIME-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_fixnum_time_interval,
	    STATIC_FUNCTION(g2int_fixnum_time_interval,NIL,FALSE,1,1));
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_fixnum_time_interval,FIX((SI_Long)1000L));
    g2int_record_system_variable(Qg2int_thrashing_cost_update_interval,
	    Qg2int_utilities2,list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qg2int_long_thrashing_cost_update_interval = 
	    STATIC_SYMBOL("LONG-THRASHING-COST-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_long_thrashing_cost_update_interval,
	    G2int_long_thrashing_cost_update_interval);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_fixnum_time_interval,FIX((SI_Long)5000L));
    g2int_record_system_variable(Qg2int_long_thrashing_cost_update_interval,
	    Qg2int_utilities2,list_constant_3,Qnil,Qnil,Qnil,Qnil);
    G2int_positive_thrashing_error_gain = FIX((SI_Long)1L);
    G2int_negative_thrashing_error_gain = FIX((SI_Long)1L);
    Qg2int_simulation_no_value = STATIC_SYMBOL("SIMULATION-NO-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_simulation_no_value,
	    G2int_simulation_no_value);
    string_constant_6 = STATIC_STRING("simulation-no-value-");
    list_constant_4 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_6);
    g2int_record_system_variable(Qg2int_simulation_no_value,
	    Qg2int_utilities2,list_constant_4,Qnil,Qnil,Qnil,Qnil);
    if (G2int_combiners_for_defun_incremental == UNBOUND)
	G2int_combiners_for_defun_incremental = Nil;
    if (G2int_defun_incremental_compile_time_registry == UNBOUND)
	G2int_defun_incremental_compile_time_registry = Nil;
    if (G2int_defun_incremental_runtime_registry == UNBOUND)
	G2int_defun_incremental_runtime_registry = Nil;
    Qg2_defstruct_structure_name_queue_g2_struct = 
	    STATIC_SYMBOL("QUEUE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_queue = STATIC_SYMBOL("QUEUE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_queue_g2_struct,
	    Qg2int_queue,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_queue,
	    Qg2_defstruct_structure_name_queue_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_queue == UNBOUND)
	G2int_the_type_description_of_queue = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8l83=Jy1n83=Jy8m8k1l8m0000001o1m83=Hy83=Iy1m8p83=gy1n8n83*py1m83=My83=Py1m83ey83-1yknk0k0");
    temp = G2int_the_type_description_of_queue;
    G2int_the_type_description_of_queue = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_7));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_queue_g2_struct,
	    G2int_the_type_description_of_queue,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_queue,
	    G2int_the_type_description_of_queue,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_queues = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-QUEUES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_queues,
	    G2int_chain_of_available_queues);
    g2int_record_system_variable(Qg2int_chain_of_available_queues,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_queue_count = STATIC_SYMBOL("QUEUE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_queue_count,G2int_queue_count);
    g2int_record_system_variable(Qg2int_queue_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_queue = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_queue,NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_queue,reclaim_structure_for_queue);
    Qg2int_current_computation_flags = 
	    STATIC_SYMBOL("CURRENT-COMPUTATION-FLAGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_computation_flags,
	    G2int_current_computation_flags);
    g2int_record_system_variable(Qg2int_current_computation_flags,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_special_setf_method = STATIC_SYMBOL("SPECIAL-SETF-METHOD",
	    AB_package);
    G2int_special_setf_method_prop = Qg2int_special_setf_method;
    Qg2int_cache_explanation_variablesqm = 
	    STATIC_SYMBOL("CACHE-EXPLANATION-VARIABLES\?",AB_package);
    Qg2int_set_cache_explanation_variablesqm = 
	    STATIC_SYMBOL("SET-CACHE-EXPLANATION-VARIABLES\?",AB_package);
    g2int_mutate_global_property(Qg2int_cache_explanation_variablesqm,
	    Qg2int_set_cache_explanation_variablesqm,
	    Qg2int_special_setf_method);
    Qg2int_final_evaluation_attemptqm = 
	    STATIC_SYMBOL("FINAL-EVALUATION-ATTEMPT\?",AB_package);
    Qg2int_set_final_evaluation_attemptqm = 
	    STATIC_SYMBOL("SET-FINAL-EVALUATION-ATTEMPT\?",AB_package);
    g2int_mutate_global_property(Qg2int_final_evaluation_attemptqm,
	    Qg2int_set_final_evaluation_attemptqm,Qg2int_special_setf_method);
    Qg2int_force_new_request_for_value = 
	    STATIC_SYMBOL("FORCE-NEW-REQUEST-FOR-VALUE",AB_package);
    Qg2int_set_force_new_request_for_value = 
	    STATIC_SYMBOL("SET-FORCE-NEW-REQUEST-FOR-VALUE",AB_package);
    g2int_mutate_global_property(Qg2int_force_new_request_for_value,
	    Qg2int_set_force_new_request_for_value,Qg2int_special_setf_method);
    Qg2int_no_wake_ups_during_role_serving = 
	    STATIC_SYMBOL("NO-WAKE-UPS-DURING-ROLE-SERVING",AB_package);
    Qg2int_set_no_wake_ups_during_role_serving = 
	    STATIC_SYMBOL("SET-NO-WAKE-UPS-DURING-ROLE-SERVING",AB_package);
    g2int_mutate_global_property(Qg2int_no_wake_ups_during_role_serving,
	    Qg2int_set_no_wake_ups_during_role_serving,
	    Qg2int_special_setf_method);
    Qg2int_role_serve_inactive_objectsqm = 
	    STATIC_SYMBOL("ROLE-SERVE-INACTIVE-OBJECTS\?",AB_package);
    Qg2int_set_role_serve_inactive_objectsqm = 
	    STATIC_SYMBOL("SET-ROLE-SERVE-INACTIVE-OBJECTS\?",AB_package);
    g2int_mutate_global_property(Qg2int_role_serve_inactive_objectsqm,
	    Qg2int_set_role_serve_inactive_objectsqm,
	    Qg2int_special_setf_method);
    Qg2int_attempting_network_write_access_p = 
	    STATIC_SYMBOL("ATTEMPTING-NETWORK-WRITE-ACCESS-P",AB_package);
    Qg2int_set_attempting_network_write_access_p = 
	    STATIC_SYMBOL("SET-ATTEMPTING-NETWORK-WRITE-ACCESS-P",AB_package);
    g2int_mutate_global_property(Qg2int_attempting_network_write_access_p,
	    Qg2int_set_attempting_network_write_access_p,
	    Qg2int_special_setf_method);
    Qg2int_attempting_network_read_access_p = 
	    STATIC_SYMBOL("ATTEMPTING-NETWORK-READ-ACCESS-P",AB_package);
    Qg2int_set_attempting_network_read_access_p = 
	    STATIC_SYMBOL("SET-ATTEMPTING-NETWORK-READ-ACCESS-P",AB_package);
    g2int_mutate_global_property(Qg2int_attempting_network_read_access_p,
	    Qg2int_set_attempting_network_read_access_p,
	    Qg2int_special_setf_method);
    Qg2int_default_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("DEFAULT-DONT-COMPUTE-NEW-VARIABLE-VALUES",
	    AB_package);
    Qg2int_set_default_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("SET-DEFAULT-DONT-COMPUTE-NEW-VARIABLE-VALUES",
	    AB_package);
    g2int_mutate_global_property(Qg2int_default_dont_compute_new_variable_values,
	    Qg2int_set_default_dont_compute_new_variable_values,
	    Qg2int_special_setf_method);
    Qg2int_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("DONT-COMPUTE-NEW-VARIABLE-VALUES",AB_package);
    Qg2int_set_dont_compute_new_variable_values = 
	    STATIC_SYMBOL("SET-DONT-COMPUTE-NEW-VARIABLE-VALUES",AB_package);
    g2int_mutate_global_property(Qg2int_dont_compute_new_variable_values,
	    Qg2int_set_dont_compute_new_variable_values,
	    Qg2int_special_setf_method);
    Qg2int_dont_forward_chain_from_rule = 
	    STATIC_SYMBOL("DONT-FORWARD-CHAIN-FROM-RULE",AB_package);
    Qg2int_set_dont_forward_chain_from_rule = 
	    STATIC_SYMBOL("SET-DONT-FORWARD-CHAIN-FROM-RULE",AB_package);
    g2int_mutate_global_property(Qg2int_dont_forward_chain_from_rule,
	    Qg2int_set_dont_forward_chain_from_rule,
	    Qg2int_special_setf_method);
    Qg2int_within_dynamic_extent_of_traced_rule_p = 
	    STATIC_SYMBOL("WITHIN-DYNAMIC-EXTENT-OF-TRACED-RULE-P",AB_package);
    Qg2int_set_within_dynamic_extent_of_traced_rule_p = 
	    STATIC_SYMBOL("SET-WITHIN-DYNAMIC-EXTENT-OF-TRACED-RULE-P",
	    AB_package);
    g2int_mutate_global_property(Qg2int_within_dynamic_extent_of_traced_rule_p,
	    Qg2int_set_within_dynamic_extent_of_traced_rule_p,
	    Qg2int_special_setf_method);
    Qg2int_serve_only_permanent_items_p = 
	    STATIC_SYMBOL("SERVE-ONLY-PERMANENT-ITEMS-P",AB_package);
    Qg2int_set_serve_only_permanent_items_p = 
	    STATIC_SYMBOL("SET-SERVE-ONLY-PERMANENT-ITEMS-P",AB_package);
    g2int_mutate_global_property(Qg2int_serve_only_permanent_items_p,
	    Qg2int_set_serve_only_permanent_items_p,
	    Qg2int_special_setf_method);
    Qg2int_serve_loose_ends_p = STATIC_SYMBOL("SERVE-LOOSE-ENDS-P",AB_package);
    Qg2int_set_serve_loose_ends_p = STATIC_SYMBOL("SET-SERVE-LOOSE-ENDS-P",
	    AB_package);
    g2int_mutate_global_property(Qg2int_serve_loose_ends_p,
	    Qg2int_set_serve_loose_ends_p,Qg2int_special_setf_method);
}
