/* evt-g2.c
 * Input file:  events-g2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "evt-g2.h"


static Object Qno_slot_description_error;  /* no-slot-description-error */

/* GET-TEXT-OF-ATTRIBUTE */
Object get_text_of_attribute(item,pretty_slot_name,class_if_specific)
    Object item, pretty_slot_name, class_if_specific;
{
    Object real_slot_name, slot_description_qm, temp;

    x_note_fn_call(248,0);
    if ( !SYMBOLP(class_if_specific))
	class_if_specific = Nil;
    real_slot_name = get_slot_name_for_alias_if_any(pretty_slot_name,item);
    if (real_slot_name);
    else
	real_slot_name = pretty_slot_name;
    slot_description_qm = 
	    get_slot_description_of_class_description_function(real_slot_name,
	    ISVREF(item,(SI_Long)1L),class_if_specific);
    if (slot_description_qm) {
	temp = get_slot_description_value(item,slot_description_qm);
	return make_text_string_representation_for_slot_value_itself(item,
		temp,get_type_of_slot_if_any(3,item,real_slot_name,
		class_if_specific));
    }
    else
	return VALUES_1(Qno_slot_description_error);
}

static Object Qundefined_attribute_for_class;  /* undefined-attribute-for-class */

static Object string_constant;     /* "attribute not defined ~NQ" */

/* G2-GET-TEXT-OF-ATTRIBUTE-SYSTEM-RPC-INTERNAL */
Object g2_get_text_of_attribute_system_rpc_internal(rpc_instance,item,
	    pretty_slot_name,class_if_specific)
    Object rpc_instance, item, pretty_slot_name, class_if_specific;
{
    Object text_or_error;

    x_note_fn_call(248,1);
    text_or_error = get_text_of_attribute(item,pretty_slot_name,
	    class_if_specific);
    if (EQ(text_or_error,Qno_slot_description_error))
	system_rpc_error(rpc_instance,Qundefined_attribute_for_class,
		tformat_text_string(3,string_constant,pretty_slot_name,
		class_if_specific));
    else
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(text_or_error,Nil));
    return VALUES_1(Nil);
}

/* SYSTEM-RPC-ACCESS-ERROR */
Object system_rpc_access_error(rpc_instance,access_error)
    Object rpc_instance, access_error;
{
    Object temp;

    x_note_fn_call(248,2);
    temp = ISVREF(access_error,(SI_Long)1L);
    return system_rpc_error(rpc_instance,temp,
	    make_default_text_string_for_access_error(access_error));
}

static Object Qicon_description_qm;  /* icon-description? */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qicon_description;   /* icon-description */

/* JV-GET-ICON-DESCRIPTION-DEFINED-BY-CLASS */
Object jv_get_icon_description_defined_by_class(class_description)
    Object class_description;
{
    Object category_evaluator_interface, gensymed_symbol, slot_description;
    Object slot_init_form, line_drawing_description, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(248,3);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_description_qm),
	    Qcategory_evaluator_interface);
    gensymed_symbol = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (class_description && (memq_function(Qicon_description,
	    ISVREF(class_description,(SI_Long)7L)) || 
	    memq_function(Qicon_description,ISVREF(class_description,
	    (SI_Long)8L)))) {
	slot_description = 
		get_slot_description_of_class_description_function(Qicon_description,
		class_description,Nil);
	slot_init_form = slot_description ? ISVREF(slot_description,
		(SI_Long)6L) : Qnil;
    }
    else
	slot_init_form = Nil;
    if (slot_init_form) {
	line_drawing_description = 
		copy_tree_using_gensym_conses_1(ISVREF(slot_init_form,
		(SI_Long)8L));
	line_drawing_description = gensym_cons_1(ISVREF(slot_init_form,
		(SI_Long)2L),line_drawing_description);
	line_drawing_description = gensym_cons_1(ISVREF(slot_init_form,
		(SI_Long)1L),line_drawing_description);
	gensymed_symbol_1 = line_drawing_description;
    }
    else
	gensymed_symbol_1 = Nil;
    gensymed_symbol_2 = Nil;
    gensymed_symbol_3 = Nil;
    return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3));
}

Object The_type_description_of_pseudo_attribute = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_pseudo_attributes, Qchain_of_available_pseudo_attributes);

DEFINE_VARIABLE_WITH_SYMBOL(Pseudo_attribute_count, Qpseudo_attribute_count);

Object Chain_of_available_pseudo_attributes_vector = UNBOUND;

/* PSEUDO-ATTRIBUTE-STRUCTURE-MEMORY-USAGE */
Object pseudo_attribute_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(248,4);
    temp = Pseudo_attribute_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PSEUDO-ATTRIBUTE-COUNT */
Object outstanding_pseudo_attribute_count()
{
    Object def_structure_pseudo_attribute_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(248,5);
    gensymed_symbol = IFIX(Pseudo_attribute_count);
    def_structure_pseudo_attribute_variable = 
	    Chain_of_available_pseudo_attributes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_pseudo_attribute_variable))
	goto end_loop;
    def_structure_pseudo_attribute_variable = 
	    ISVREF(def_structure_pseudo_attribute_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PSEUDO-ATTRIBUTE-1 */
Object reclaim_pseudo_attribute_1(pseudo_attribute)
    Object pseudo_attribute;
{
    Object temp, svref_arg_2;

    x_note_fn_call(248,6);
    inline_note_reclaim_cons(pseudo_attribute,Nil);
    temp = ISVREF(Chain_of_available_pseudo_attributes_vector,
	    IFIX(Current_thread_index));
    SVREF(pseudo_attribute,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_pseudo_attributes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = pseudo_attribute;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PSEUDO-ATTRIBUTE */
Object reclaim_structure_for_pseudo_attribute(pseudo_attribute)
    Object pseudo_attribute;
{
    x_note_fn_call(248,7);
    return reclaim_pseudo_attribute_1(pseudo_attribute);
}

static Object Qg2_defstruct_structure_name_pseudo_attribute_g2_struct;  /* g2-defstruct-structure-name::pseudo-attribute-g2-struct */

/* MAKE-PERMANENT-PSEUDO-ATTRIBUTE-STRUCTURE-INTERNAL */
Object make_permanent_pseudo_attribute_structure_internal()
{
    Object def_structure_pseudo_attribute_variable;
    Object defstruct_g2_pseudo_attribute_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(248,8);
    def_structure_pseudo_attribute_variable = Nil;
    atomic_incff_symval(Qpseudo_attribute_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_pseudo_attribute_variable = Nil;
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
	defstruct_g2_pseudo_attribute_variable = the_array;
	SVREF(defstruct_g2_pseudo_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_attribute_g2_struct;
	def_structure_pseudo_attribute_variable = 
		defstruct_g2_pseudo_attribute_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_pseudo_attribute_variable);
}

/* MAKE-PSEUDO-ATTRIBUTE-1 */
Object make_pseudo_attribute_1(pseudo_attribute_name)
    Object pseudo_attribute_name;
{
    Object def_structure_pseudo_attribute_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(248,9);
    def_structure_pseudo_attribute_variable = 
	    ISVREF(Chain_of_available_pseudo_attributes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_pseudo_attribute_variable) {
	svref_arg_1 = Chain_of_available_pseudo_attributes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_pseudo_attribute_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_pseudo_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_pseudo_attribute_g2_struct;
    }
    else
	def_structure_pseudo_attribute_variable = 
		make_permanent_pseudo_attribute_structure_internal();
    inline_note_allocate_cons(def_structure_pseudo_attribute_variable,Nil);
    SVREF(def_structure_pseudo_attribute_variable,FIX((SI_Long)1L)) = 
	    pseudo_attribute_name;
    SVREF(def_structure_pseudo_attribute_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_pseudo_attribute_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_pseudo_attribute_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_pseudo_attribute_variable);
}

Object Pseudo_attribute_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Static_attributes, Qstatic_attributes);

DEFINE_VARIABLE_WITH_SYMBOL(Class_info_attributes, Qclass_info_attributes);

Object Class_info_key = UNBOUND;

static Object list_constant;       /* # */

static Object Qtype_specification_explicit_complex_type;  /* type-specification-explicit-complex-type */

static Object Qpseudo_attribute;   /* pseudo-attribute */

/* ADD-PSEUDO-ATTRIBUTE */
Object add_pseudo_attribute(attribute_name,defining_class,getter_name,
	    category_name_or_type_description)
    Object attribute_name, defining_class, getter_name;
    Object category_name_or_type_description;
{
    Object pseudo_attribute_structure, gensym_modify_macro_using_test_arg_1;
    Object car_1, cdr_1, key_result, x_element, ab_loop_list_, ab_loop_it_;
    Object temp_1;
    char temp;

    x_note_fn_call(248,10);
    pseudo_attribute_structure = make_pseudo_attribute_1(attribute_name);
    if (memq_function(defining_class,list_constant) && EQ(defining_class,
	    Class_info_key)) {
	gensym_modify_macro_using_test_arg_1 = attribute_name;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = Class_info_attributes;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list_ = cdr_1;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	x_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	temp_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	Class_info_attributes = temp_1;
    }
    else {
	gensym_modify_macro_using_test_arg_1 = attribute_name;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = Static_attributes;
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
	    temp = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_2:;
	temp_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	Static_attributes = temp_1;
    }
    SVREF(pseudo_attribute_structure,FIX((SI_Long)4L)) = getter_name;
    if (SYMBOLP(category_name_or_type_description)) {
	temp_1 = get_property_value_function(3,
		get_symbol_properties_function(category_name_or_type_description),
		Qtype_specification_explicit_complex_type,Nil);
	SVREF(pseudo_attribute_structure,FIX((SI_Long)2L)) = temp_1;
    }
    else
	SVREF(pseudo_attribute_structure,FIX((SI_Long)2L)) = 
		category_name_or_type_description;
    SVREF(pseudo_attribute_structure,FIX((SI_Long)3L)) = defining_class;
    return mutate_global_property(attribute_name,
	    pseudo_attribute_structure,Qpseudo_attribute);
}

/* CLASS-NAME-PSEUDO-ATTRIBUTE-GETTER */
Object class_name_pseudo_attribute_getter(class_name)
    Object class_name;
{
    x_note_fn_call(248,11);
    return VALUES_1(class_name);
}

static Object Qtruth_value;        /* truth-value */

/* IS-SYSTEM-DEFINED-PSEUDO-ATTRIBUTE-GETTER */
Object is_system_defined_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object temp, evaluation_value;
    char temp_1;

    x_note_fn_call(248,12);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    evaluation_value = temp_1 ? Evaluation_true_value : Evaluation_false_value;
    if (EQ(evaluation_value,Evaluation_true_value) || EQ(evaluation_value,
	    Evaluation_false_value))
	return VALUES_1(evaluation_value);
    else
	return eval_cons_1(M_CAR(evaluation_value),Qtruth_value);
}

/* DIRECT-SUPERIOR-CLASSES-PSEUDO-ATTRIBUTE-GETTER */
Object direct_superior_classes_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object class_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(248,13);
    class_1 = Nil;
    ab_loop_list_ = lookup_global_or_kb_specific_property_value(class_name,
	    Direct_superior_classes_gkbprop);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(Reference_class_info_p ? 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop) : class_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp);
}

/* CLASS-INHERITANCE-PATH-PSEUDO-ATTRIBUTE-GETTER */
Object class_inheritance_path_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object class_1, class_description, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(248,14);
    class_1 = Nil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = eval_cons_1(Reference_class_info_p ? 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop) : class_1,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp);
}

static Object Qnot_user_instantiable;  /* not-user-instantiable */

static Object Qnot_solely_instantiable;  /* not-solely-instantiable */

/* INSTANTIATE-PSEUDO-ATTRIBUTE-GETTER */
Object instantiate_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object class_description, class_features, gensymed_symbol, ab_loop_list_;
    char temp;

    x_note_fn_call(248,15);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    class_features = ISVREF(class_description,(SI_Long)12L);
    if (ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)16L)) {
	gensymed_symbol = Nil;
	ab_loop_list_ = class_features;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qnot_user_instantiable)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = Nil;
	ab_loop_list_ = class_features;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qnot_solely_instantiable)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_2:;
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* INCLUDE-IN-MENUS-PSEUDO-ATTRIBUTE-GETTER */
Object include_in_menus_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object class_description, class_features, gensymed_symbol, ab_loop_list_;
    char temp;

    x_note_fn_call(248,16);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    class_features = ISVREF(class_description,(SI_Long)12L);
    if (ISVREF(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),(SI_Long)16L)) {
	gensymed_symbol = Nil;
	ab_loop_list_ = class_features;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		Qnot_user_instantiable)) {
	    temp = TRUEP(gensymed_symbol);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* ICON-DESCRIPTION-PSEUDO-ATTRIBUTE-GETTER */
Object icon_description_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object line_drawing_description, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,17);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_description_qm),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qicon_description,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	line_drawing_description = ISVREF(slot_init_form_qm,(SI_Long)8L);
	line_drawing_description = gensym_cons_1(ISVREF(slot_init_form_qm,
		(SI_Long)2L),line_drawing_description);
	line_drawing_description = gensym_cons_1(ISVREF(slot_init_form_qm,
		(SI_Long)1L),line_drawing_description);
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = line_drawing_description;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp_1 = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
	reclaim_gensym_cons_1(CDR(line_drawing_description));
	reclaim_gensym_cons_1(line_drawing_description);
	return VALUES_1(temp_1);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qcross_section_pattern;  /* cross-section-pattern */

/* CROSS-SECTION-PATTERN-PSEUDO-ATTRIBUTE-GETTER */
Object cross_section_pattern_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object cross_section_pattern, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,18);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcross_section_pattern),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qcross_section_pattern,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	cross_section_pattern = slot_init_form_qm;
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = cross_section_pattern;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qstub_length;        /* stub-length */

/* STUB-LENGTH-PSEUDO-ATTRIBUTE-GETTER */
Object stub_length_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,19);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstub_length),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qstub_length,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qjunction_class;     /* junction-class */

static Object Qjunction_block_class;  /* junction-block-class */

/* JUNCTION-BLOCK-CLASS-PSEUDO-ATTRIBUTE-GETTER */
Object junction_block_class_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,20);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qjunction_class),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qjunction_block_class,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qmessage_properties;  /* message-properties */

static Object Qdefault_message_properties_for_class;  /* default-message-properties-for-class */

/* DEFAULT-MESSAGE-PROPERTIES-PSEUDO-ATTRIBUTE-GETTER */
Object default_message_properties_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,21);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmessage_properties),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qdefault_message_properties_for_class,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qpositive_integer;   /* positive-integer */

static Object Qkb_workspace_initial_width;  /* kb-workspace-initial-width */

/* KB-WORKSPACE-INITIAL-WIDTH-PSEUDO-ATTRIBUTE-GETTER */
Object kb_workspace_initial_width_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,22);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qkb_workspace_initial_width,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qkb_workspace_initial_height;  /* kb-workspace-initial-height */

/* KB-WORKSPACE-INITIAL-HEIGHT-PSEUDO-ATTRIBUTE-GETTER */
Object kb_workspace_initial_height_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,23);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpositive_integer),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qkb_workspace_initial_height,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qdefault_text_box_format_name;  /* default-text-box-format-name */

/* DEFAULT-TEXT-BOX-FORMAT-NAME-PSEUDO-ATTRIBUTE-GETTER */
Object default_text_box_format_name_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,24);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsymbol),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qdefault_text_box_format_name,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

static Object Qdefault_readout_table_format_name;  /* default-readout-table-format-name */

/* DEFAULT-READOUT-TABLE-FORMAT-NAME-PSEUDO-ATTRIBUTE-GETTER */
Object default_readout_table_format_name_pseudo_attribute_getter(class_name)
    Object class_name;
{
    Object category_evaluator_interface, evaluation_value_function, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, slot_description_qm, slot_init_form_qm;
    Object gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Object result;

    x_note_fn_call(248,25);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsymbol),
	    Qcategory_evaluator_interface);
    evaluation_value_function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
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
    slot_description_qm = 
	    get_slot_description_of_class_description_function(Qdefault_readout_table_format_name,
	    gensymed_symbol,Nil);
    slot_init_form_qm = slot_description_qm ? ISVREF(slot_description_qm,
	    (SI_Long)6L) : Nil;
    if (slot_init_form_qm) {
	gensymed_symbol = evaluation_value_function;
	gensymed_symbol_1 = slot_init_form_qm;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3));
    }
    else
	return VALUES_1(Nil);
}

/* SYSTEM-MENU-CHOICES-PSEUDO-ATTRIBUTE-GETTER */
Object system_menu_choices_pseudo_attribute_getter(class_name)
    Object class_name;
{
    x_note_fn_call(248,26);
    return system_menu_choices_for_class(class_name);
}

/* CLASS-DEFINES-PSEUDO-ATTRIBUTE-P */
Object class_defines_pseudo_attribute_p(class_name,attribute_name)
    Object class_name, attribute_name;
{
    Object pseudo_attribute;

    x_note_fn_call(248,27);
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
	    Qpseudo_attribute)) {
	pseudo_attribute = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		Qpseudo_attribute);
	return VALUES_1(EQ(pseudo_attribute ? ISVREF(pseudo_attribute,
		(SI_Long)3L) : Nil,class_name) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qattribute_name;     /* attribute-name */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qtext_readable;      /* text-readable */

static Object Qtext_writable;      /* text-writable */

static Object Qvalue_readable;     /* value-readable */

static Object Qvalue_writable;     /* value-writable */

static Object Qis_system_defined;  /* is-system-defined */

static Object Qdefining_class;     /* defining-class */

static Object Qinitial_value;      /* initial-value */

static Object Qab_structure;       /* structure */

/* GENERATE-DESCRIPTION-OF-PSEUDO-ATTRIBUTE */
Object generate_description_of_pseudo_attribute(attribute_name,
	    initial_value_for_specific_class)
    Object attribute_name, initial_value_for_specific_class;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    Object pseudo_attribute, thing;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,28);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)18L + 
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattribute_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qattribute_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = FIXNUMP(attribute_name) || attribute_name && 
		SYMBOLP(attribute_name) ? attribute_name : 
		copy_evaluation_value_1(attribute_name);
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
	item_or_value = FIXNUMP(attribute_name) || attribute_name && 
		SYMBOLP(attribute_name) ? attribute_name : 
		copy_evaluation_value_1(attribute_name);
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtext_readable;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qtext_readable;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	item_or_value = Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtext_writable;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qtext_writable;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	item_or_value = Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qvalue_readable;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qvalue_readable;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	item_or_value = Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qvalue_writable;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qvalue_writable;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	item_or_value = Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qis_system_defined;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)11L)) = Qis_system_defined;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_true_value;
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
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Evaluation_true_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qdefining_class;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)13L)) = Qdefining_class;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	pseudo_attribute = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		Qpseudo_attribute);
	thing = pseudo_attribute ? ISVREF(pseudo_attribute,(SI_Long)3L) : Nil;
	item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
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
	SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	pseudo_attribute = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		Qpseudo_attribute);
	thing = pseudo_attribute ? ISVREF(pseudo_attribute,(SI_Long)3L) : Nil;
	item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qinitial_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)15L)) = Qinitial_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = initial_value_for_specific_class;
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
	SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = initial_value_for_specific_class;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)19L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)17L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		generate_type_description_of_attribute(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		Qpseudo_attribute),(SI_Long)2L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)20L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		generate_type_description_of_attribute(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		Qpseudo_attribute),(SI_Long)2L));
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)18L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qvirtual_attributes_local_to_class;  /* virtual-attributes-local-to-class */

static Object Qdeprecated;         /* deprecated */

/* FILTERED-VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS */
Object filtered_virtual_attributes_local_to_class(class_name)
    Object class_name;
{
    Object virtual_attributes, attribute, ab_loop_list_, valid_attribute;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(248,29);
    virtual_attributes = get_property_value_function(3,
	    get_symbol_properties_function(class_name),
	    Qvirtual_attributes_local_to_class,Nil);
    attribute = Nil;
    ab_loop_list_ = virtual_attributes;
    valid_attribute = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    valid_attribute = CONSP(attribute) ? (EQ(Qdeprecated,CADR(attribute)) ?
	     Nil : M_CAR(attribute)) : attribute;
    if (valid_attribute) {
	ab_loopvar__2 = eval_cons_1(valid_attribute,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CLASSES-OF-CLASS-P */
Object classes_of_class_p(classes,class_1)
    Object classes, class_1;
{
    Object each_class, ab_loop_list_, class_description, ab_loop_it_;
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(248,30);
    each_class = Nil;
    ab_loop_list_ = classes;
    class_description = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    each_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_description = 
	    lookup_global_or_kb_specific_property_value(each_class,
	    Class_description_gkbprop);
    if (class_description) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qvirtual_attribute;  /* virtual-attribute */

/* GET-LIST-OF-INSTANCE-ATTRIBUTES */
Object get_list_of_instance_attributes(class_description,
	    include_inherited_attributes_p,stop_classes)
    Object class_description, include_inherited_attributes_p, stop_classes;
{
    Object class_name, virtual_attributes, attr_name, ab_loop_list_;
    Object attribute_structure, defining_class, include_attribute_p;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, virtual_attr_list;
    Object slot_description, defining_class_name, aliased_slot_name, temp;
    Object pretty_slot_name, class_or_frame_qm, slot_desc_list, non_local_attr;
    Object virtual_attr_list_non_local;
    char temp_1;

    x_note_fn_call(248,31);
    class_name = ISVREF(class_description,(SI_Long)1L);
    virtual_attributes = include_inherited_attributes_p ? 
	    all_virtual_attributes_for_class(2,class_description,Nil) : 
	    filtered_virtual_attributes_local_to_class(class_name);
    attr_name = Nil;
    ab_loop_list_ = virtual_attributes;
    attribute_structure = Nil;
    defining_class = Nil;
    include_attribute_p = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attr_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_structure = get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,Nil);
    defining_class = 
	    virtual_attribute_defined_for_class_qm(attribute_structure,
	    class_name);
    include_attribute_p =  !TRUEP(classes_of_class_p(stop_classes,
	    defining_class)) ? T : Nil;
    if (include_attribute_p) {
	ab_loopvar__2 = eval_cons_1(eval_cons_1(attr_name,
		attribute_structure),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(virtual_attributes);
    virtual_attr_list = ab_loopvar_;
    goto end_1;
    virtual_attr_list = Qnil;
  end_1:;
    slot_description = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    defining_class_name = Nil;
    aliased_slot_name = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    defining_class_name = ISVREF(slot_description,(SI_Long)3L);
    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	temp = ISVREF(slot_description,(SI_Long)3L);
	temp_1 =  !EQ(temp,
		ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		(SI_Long)2L),class_description,Nil),(SI_Long)3L));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	aliased_slot_name = ISVREF(slot_description,(SI_Long)1L);
    else {
	pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
	class_or_frame_qm = defining_class_name;
	temp = get_alias_for_slot_name_if_any(pretty_slot_name,
		class_or_frame_qm);
	if (temp);
	else
	    temp = pretty_slot_name;
	aliased_slot_name = temp;
    }
    if ((include_inherited_attributes_p || EQ(defining_class_name,
	    class_name)) &&  !TRUEP(classes_of_class_p(stop_classes,
	    defining_class_name)) && user_visible_slot_p(slot_description) 
	    &&  !TRUEP(assq_function(aliased_slot_name,virtual_attr_list))) {
	ab_loopvar__2 = eval_cons_1(eval_cons_1(aliased_slot_name,
		slot_description),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    slot_desc_list = ab_loopvar_;
    goto end_2;
    slot_desc_list = Qnil;
  end_2:;
    if (Virtual_attributes_not_local_to_a_class) {
	non_local_attr = Nil;
	ab_loop_list_ = Virtual_attributes_not_local_to_a_class;
	attribute_structure = Nil;
	defining_class = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	non_local_attr = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_structure = get_property_value_function(3,
		get_symbol_properties_function(non_local_attr),
		Qvirtual_attribute,Nil);
	defining_class = 
		virtual_attribute_defined_for_class_qm(attribute_structure,
		class_name);
	if (include_inherited_attributes_p ?  
		!TRUEP(classes_of_class_p(stop_classes,defining_class)) && 
		applicable_and_not_deprecated_virtual_attribute_p(class_description,
		attribute_structure,Nil) : EQ(defining_class,class_name)) {
	    ab_loopvar__2 = eval_cons_1(eval_cons_1(non_local_attr,
		    attribute_structure),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_2;
      end_loop_2:
	virtual_attr_list_non_local = ab_loopvar_;
	goto end_3;
	virtual_attr_list_non_local = Qnil;
      end_3:;
    }
    else
	virtual_attr_list_non_local = Nil;
    temp = sort_pairs_according_to_defining_class(class_name,
	    nconc2(slot_desc_list,nconc2(virtual_attr_list,
	    virtual_attr_list_non_local)));
    return VALUES_1(temp);
}

static Object list_constant_1;     /* # */

static Object Qno_such_class_error;  /* no-such-class-error */

/* GET-STATIC-ATTRIBUTE-DESCRIPTIONS-OF-CLASS */
Object get_static_attribute_descriptions_of_class varargs_1(int, n)
{
    Object class_name;
    Object include_inherited_attributes_p, temp, result_1, attribute_name;
    Object ab_loop_list_, class_defines_attribute_p, pseudo_attribute;
    Object gensymed_symbol, sub_class_bit_vector, class_description_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(248,32);
    INIT_ARGS_nonrelocating();
    class_name = REQUIRED_ARG_nonrelocating();
    include_inherited_attributes_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(class_name,
		Class_definition_gkbprop);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	result_1 = Nil;
	attribute_name = Nil;
	ab_loop_list_ = Static_attributes;
	class_defines_attribute_p = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_defines_attribute_p = 
		class_defines_pseudo_attribute_p(class_name,attribute_name);
	temp_1 = TRUEP(class_defines_attribute_p);
	if (temp_1);
	else if (include_inherited_attributes_p) {
	    pseudo_attribute = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute_name),
		    Qpseudo_attribute);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(pseudo_attribute 
		    ? ISVREF(pseudo_attribute,(SI_Long)3L) : Nil,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = 
			ISVREF(lookup_global_or_kb_specific_property_value(class_name,
			Class_description_gkbprop),(SI_Long)19L);
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
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
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
	if (temp_1) {
	    temp = attribute_name;
	    temp = generate_description_of_pseudo_attribute(temp,
		    get_attribute_from_class(class_name,attribute_name));
	    result_1 = eval_cons_1(temp,result_1);
	}
	goto next_loop;
      end_loop:
	return allocate_evaluation_sequence(result_1);
	return VALUES_1(Qnil);
    }
    else {
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L)))
	    return get_instance_attribute_descriptions_of_class(3,
		    ISVREF(ISVREF(lookup_global_or_kb_specific_property_value(class_name,
		    Class_definition_gkbprop),(SI_Long)1L),(SI_Long)1L),T,
		    list_constant_1);
	else
	    return VALUES_1(Qno_such_class_error);
    }
}

static Object Qadministrator;      /* administrator */

/* GET-INSTANCE-ATTRIBUTE-DESCRIPTIONS-OF-CLASS */
Object get_instance_attribute_descriptions_of_class varargs_1(int, n)
{
    Object class_name;
    Object include_inherited_attributes_p, stop_classes;
    Object name_and_description_alist, name, slot, ab_loop_list_, struct_list;
    Object ab_loopvar_, ab_loopvar__1, ab_loop_desetq_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(248,33);
    INIT_ARGS_nonrelocating();
    class_name = REQUIRED_ARG_nonrelocating();
    include_inherited_attributes_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    stop_classes = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	name_and_description_alist = 
		get_list_of_instance_attributes(lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop),include_inherited_attributes_p,
		stop_classes);
	name = Nil;
	slot = Nil;
	ab_loop_list_ = name_and_description_alist;
	struct_list = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	name = CAR(ab_loop_desetq_);
	slot = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = 
		eval_cons_1(generate_description_of_attribute(class_name,
		name,slot,
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop),Nil,Qadministrator,T),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    struct_list = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	reclaim_eval_alist(name_and_description_alist);
	return allocate_evaluation_sequence(struct_list);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qno_such_class_error);
}

/* GET-GLOBAL-CLASS-INFO-ATTRIBUTE-NAMES-AND-VALUES */
Object get_global_class_info_attribute_names_and_values(class_name)
    Object class_name;
{
    Object result_1, attribute_name, ab_loop_list_, attribute_value;

    x_note_fn_call(248,34);
    result_1 = Nil;
    attribute_name = Nil;
    ab_loop_list_ = Class_info_attributes;
    attribute_value = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_value = get_attribute_from_class(class_name,attribute_name);
    result_1 = eval_cons_1(attribute_value,result_1);
    result_1 = eval_cons_1(attribute_name,result_1);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* GET-ATTRIBUTE-FROM-CLASS */
Object get_attribute_from_class(classname,attribute)
    Object classname, attribute;
{
    Object temp, pseudo_attribute, pseudo_attribute_getter;
    Object class_description_qm, item, denotation, evaluation_value_or_error;
    Object x2;
    char temp_1;

    x_note_fn_call(248,35);
    if (lookup_global_or_kb_specific_property_value(classname,
	    Class_description_gkbprop)) {
	temp = lookup_global_or_kb_specific_property_value(classname,
		Class_definition_gkbprop);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else
	temp_1 = lookup_global_or_kb_specific_property_value(classname,
		Class_description_gkbprop) ? 
		TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute),
		Qpseudo_attribute)) : TRUEP(Qnil);
    if (temp_1) {
	pseudo_attribute = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(attribute),
		Qpseudo_attribute);
	pseudo_attribute_getter = pseudo_attribute ? 
		ISVREF(pseudo_attribute,(SI_Long)4L) : Qnil;
	if (pseudo_attribute_getter)
	    return FUNCALL_1(pseudo_attribute_getter,classname);
	else
	    return VALUES_1(Nil);
    }
    else {
	class_description_qm = 
		lookup_global_or_kb_specific_property_value(classname,
		Class_description_gkbprop);
	if (class_description_qm &&  !TRUEP(ISVREF(class_description_qm,
		(SI_Long)20L))) {
	    item = lookup_global_or_kb_specific_property_value(classname,
		    Class_definition_gkbprop);
	    denotation = make_attribute_denotation(attribute,Nil,T);
	    evaluation_value_or_error = Nil;
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? attribute && SYMBOLP(attribute) : TRUEP(Nil)) {
		evaluation_value_or_error = 
			get_denoted_evaluation_value(item,denotation);
		return VALUES_1(evaluation_value_or_error);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qno_such_class_error);
    }
}

static Object Qclass_attributes;   /* class-attributes */

static Object Qinstance_attributes;  /* instance-attributes */

/* GET-CLASS-INFO */
Object get_class_info(class_name,include_inherited_attributes_p,structure_p)
    Object class_name, include_inherited_attributes_p, structure_p;
{
    Object class_info_attributes, class_attributes, instance_attributes;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,36);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	class_info_attributes = 
		nreverse(get_global_class_info_attribute_names_and_values(class_name));
	class_attributes = get_static_attribute_descriptions_of_class(2,
		class_name,include_inherited_attributes_p);
	instance_attributes = 
		get_instance_attribute_descriptions_of_class(2,class_name,
		include_inherited_attributes_p);
	PUSH_SPECIAL_WITH_SYMBOL(Class_info_attributes,Qclass_info_attributes,class_info_attributes,
		0);
	  Class_info_attributes = eval_cons_1(Qclass_attributes,
		  Class_info_attributes);
	  Class_info_attributes = eval_cons_1(class_attributes,
		  Class_info_attributes);
	  Class_info_attributes = eval_cons_1(Qinstance_attributes,
		  Class_info_attributes);
	  Class_info_attributes = eval_cons_1(instance_attributes,
		  Class_info_attributes);
	  Class_info_attributes = 
		  add_class_export_info_attributes(class_name,
		  Class_info_attributes);
	  Class_info_attributes = nreverse(Class_info_attributes);
	  if (structure_p)
	      result = allocate_evaluation_structure(Class_info_attributes);
	  else
	      result = VALUES_1(Class_info_attributes);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Qno_such_class_error);
}

/* G2-GET-CLASS-INFO-SYSTEM-RPC-INTERNAL */
Object g2_get_class_info_system_rpc_internal(rpc_instance,class_name,
	    include_inherited_attributes_p)
    Object rpc_instance, class_name, include_inherited_attributes_p;
{
    Object current_system_rpc_icp_socket_qm, info_or_error;
    Declare_special(1);

    x_note_fn_call(248,37);
    current_system_rpc_icp_socket_qm = ISVREF(rpc_instance,(SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
	    0);
      info_or_error = get_class_info(class_name,
	      evaluation_truth_value_is_true_p(include_inherited_attributes_p),
	      T);
      if (EQ(info_or_error,Qno_such_class_error))
	  system_rpc_access_error(rpc_instance,
		  make_no_such_class_error_message(class_name));
      else
	  return_from_system_defined_rpc(rpc_instance,
		  eval_cons_1(info_or_error,Nil));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qinclude_method_text_in_class_export;  /* include-method-text-in-class-export */

/* G2-INCLUDE-METHOD-TEXT-IN-EXPORT */
Object g2_include_method_text_in_export(include_method_text)
    Object include_method_text;
{
    Object include_text_p, enclosing_gsi_interface_frame_qm, x2;
    Object gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(248,38);
    include_text_p = evaluation_truth_value_is_true_p(include_method_text);
    enclosing_gsi_interface_frame_qm = Current_system_rpc_icp_socket_qm ? 
	    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : Nil;
    if (SIMPLE_VECTOR_P(enclosing_gsi_interface_frame_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(enclosing_gsi_interface_frame_qm)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(enclosing_gsi_interface_frame_qm,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(enclosing_gsi_interface_frame_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(enclosing_gsi_interface_frame_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(enclosing_gsi_interface_frame_qm) ? 
		EQ(ISVREF(enclosing_gsi_interface_frame_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)6L);
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
    else
	temp = TRUEP(Nil);
    if (temp)
	set_non_savable_lookup_slot_value(enclosing_gsi_interface_frame_qm,
		Qinclude_method_text_in_class_export,include_text_p);
    return VALUES_1(Nil);
}

static Object Kstack_error;        /* :stack-error */

/* G2-INCLUDE-METHOD-TEXT-IN-EXPORT-SYSTEM-RPC-INTERNAL */
Object g2_include_method_text_in_export_system_rpc_internal(gensymed_symbol,
	    include_method_text)
    Object gensymed_symbol, include_method_text;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,39);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    g2_include_method_text_in_export(include_method_text);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* GET-CLASS-INHERITANCE-PATH */
Object get_class_inheritance_path(class_name)
    Object class_name;
{
    Object class_description, class_in_hierarchy, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(248,40);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description) {
	class_in_hierarchy = Nil;
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_in_hierarchy = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = eval_cons_1(class_in_hierarchy,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = allocate_evaluation_sequence(temp);
    }
    else
	temp = Qno_such_class_error;
    return VALUES_1(temp);
}

/* G2-GET-CLASS-INHERITANCE-PATH-SYSTEM-RPC-INTERNAL */
Object g2_get_class_inheritance_path_system_rpc_internal(rpc_instance,
	    class_name)
    Object rpc_instance, class_name;
{
    Object info_or_error;

    x_note_fn_call(248,41);
    info_or_error = get_class_inheritance_path(class_name);
    if (EQ(info_or_error,Qno_such_class_error))
	system_rpc_access_error(rpc_instance,
		make_no_such_class_error_message(class_name));
    else
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(info_or_error,Nil));
    return VALUES_1(Nil);
}

static Object Qdefinition;         /* definition */

/* G2-GET-SHORT-CLASS-INFO */
Object g2_get_short_class_info(class_name)
    Object class_name;
{
    Object class_description, definition, class_in_hierarchy, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object class_inheritance_path;

    x_note_fn_call(248,42);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description) {
	definition = get_instance_with_name_if_any(Qdefinition,class_name);
	class_in_hierarchy = Nil;
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_in_hierarchy = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = eval_cons_1(class_in_hierarchy,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	class_inheritance_path = allocate_evaluation_sequence(temp);
	temp = definition ? 
		allocate_evaluation_sequence(eval_list_3(class_inheritance_path,
		definition,get_module_block_is_in(definition))) : 
		class_inheritance_path;
    }
    else
	temp = Qno_such_class_error;
    return VALUES_1(temp);
}

/* G2-GET-SHORT-CLASS-INFO-SYSTEM-RPC-INTERNAL */
Object g2_get_short_class_info_system_rpc_internal(rpc_instance,class_name)
    Object rpc_instance, class_name;
{
    Object info_or_error;

    x_note_fn_call(248,43);
    info_or_error = g2_get_short_class_info(class_name);
    if (EQ(info_or_error,Qno_such_class_error))
	system_rpc_access_error(rpc_instance,
		make_no_such_class_error_message(class_name));
    else
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(info_or_error,Nil));
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_access_error_g2_struct;  /* g2-defstruct-structure-name::access-error-g2-struct */

/* G2-GET-ATTRIBUTE-FROM-CLASS-SYSTEM-RPC-INTERNAL */
Object g2_get_attribute_from_class_system_rpc_internal(rpc_instance,
	    classname,attribute)
    Object rpc_instance, classname, attribute;
{
    Object evaluation_value_or_error;

    x_note_fn_call(248,44);
    evaluation_value_or_error = get_attribute_from_class(classname,attribute);
    if (SIMPLE_VECTOR_P(evaluation_value_or_error) && 
	    EQ(ISVREF(evaluation_value_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	system_rpc_access_error(rpc_instance,evaluation_value_or_error);
    else
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(evaluation_value_or_error,Nil));
    return VALUES_1(Nil);
}

/* G2-GET-ATTRIBUTES-FROM-CLASS-SYSTEM-RPC-INTERNAL */
Object g2_get_attributes_from_class_system_rpc_internal(rpc_instance,
	    classname,attributes)
    Object rpc_instance, classname, attributes;
{
    Object attribute_values, gensymed_symbol, held_vector, attribute_name;
    Object attribute_value_or_error, elt_1, validated_elt, value;
    Object ab_loop_list_, evaluation_value_or_error;
    SI_Long next_index, length_1;

    x_note_fn_call(248,45);
    attribute_values = Qnil;
    gensymed_symbol = attributes;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    attribute_name = Nil;
    attribute_value_or_error = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    attribute_name = validated_elt;
    attribute_value_or_error = get_attribute_from_class(classname,
	    attribute_name);
    if (SIMPLE_VECTOR_P(attribute_value_or_error) && 
	    EQ(ISVREF(attribute_value_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct)) {
	value = Nil;
	ab_loop_list_ = attribute_values;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	    reclaim_if_evaluation_value_1(value);
	goto next_loop_1;
      end_loop_1:;
	reclaim_eval_list_1(attribute_values);
	evaluation_value_or_error = attribute_value_or_error;
	goto end_1;
    }
    else {
	attribute_values = eval_cons_1(attribute_value_or_error,
		attribute_values);
	attribute_values = eval_cons_1(attribute_name,attribute_values);
    }
    goto next_loop;
  end_loop:
    evaluation_value_or_error = 
	    allocate_evaluation_structure(attribute_values);
    goto end_1;
    evaluation_value_or_error = Qnil;
  end_1:;
    if (SIMPLE_VECTOR_P(evaluation_value_or_error) && 
	    EQ(ISVREF(evaluation_value_or_error,(SI_Long)0L),
	    Qg2_defstruct_structure_name_access_error_g2_struct))
	system_rpc_access_error(rpc_instance,evaluation_value_or_error);
    else
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(evaluation_value_or_error,Nil));
    return VALUES_1(Nil);
}

/* G2-GET-MULTIPLE-CLASS-ATTRIBUTE-VALUES-SYSTEM-RPC-INTERNAL */
Object g2_get_multiple_class_attribute_values_system_rpc_internal(rpc_instance,
	    class_names)
    Object rpc_instance, class_names;
{
    x_note_fn_call(248,46);
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(g2_get_multiple_class_attribute_values(class_names),
	    Nil));
    return VALUES_1(Nil);
}

/* G2-GET-MULTIPLE-CLASS-ATTRIBUTE-VALUES */
Object g2_get_multiple_class_attribute_values(class_names)
    Object class_names;
{
    Object classes_to_collect, class_attribute_values_list, gensymed_symbol;
    Object held_vector, class_name, elt_1, validated_elt, class_description;
    Object class_inheritance_path, class_in_path, ab_loop_list_;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_, class_to_collect, temp_1;
    SI_Long next_index, length_1;
    char temp;

    x_note_fn_call(248,47);
    classes_to_collect = Nil;
    class_attribute_values_list = Nil;
    gensymed_symbol = class_names;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    class_name = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    class_name = validated_elt;
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	class_description = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
	class_in_path = Nil;
	ab_loop_list_ = class_inheritance_path;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	class_in_path = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensym_modify_macro_using_test_arg_1 = class_in_path;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = classes_to_collect;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_2;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(Qnil);
      end_1:;
	classes_to_collect = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    class_to_collect = Nil;
    ab_loop_list_ = classes_to_collect;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    class_to_collect = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = get_class_attribute_values_or_definition(class_to_collect);
    class_attribute_values_list = eval_cons_1(temp_1,
	    class_attribute_values_list);
    class_attribute_values_list = eval_cons_1(class_to_collect,
	    class_attribute_values_list);
    goto next_loop_3;
  end_loop_3:;
    reclaim_gensym_list_1(classes_to_collect);
    temp_1 = allocate_evaluation_structure(class_attribute_values_list);
    return VALUES_1(temp_1);
}

/* GET-CLASS-ATTRIBUTE-VALUES-OR-DEFINITION */
Object get_class_attribute_values_or_definition(class_name)
    Object class_name;
{
    Object temp;

    x_note_fn_call(248,48);
    temp = system_class_p(class_name) ? 
	    get_system_class_attribute_values(class_name) : 
	    get_instance_with_name_if_any(Qdefinition,class_name);
    return VALUES_1(temp);
}

/* GET-SYSTEM-CLASS-ATTRIBUTE-VALUES */
Object get_system_class_attribute_values(class_name)
    Object class_name;
{
    Object class_attribute_values, pseudo_attribute_name, ab_loop_list_;
    Object pseudo_attribute, defining_class, gensymed_symbol, temp;

    x_note_fn_call(248,49);
    class_attribute_values = Nil;
    pseudo_attribute_name = Nil;
    ab_loop_list_ = Static_attributes;
    pseudo_attribute = Nil;
    defining_class = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pseudo_attribute_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pseudo_attribute = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(pseudo_attribute_name),
	    Qpseudo_attribute);
    defining_class = ISVREF(pseudo_attribute,(SI_Long)3L);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol ? TRUEP(memq_function(defining_class,
	    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
	temp = get_attribute_from_class(class_name,pseudo_attribute_name);
	class_attribute_values = eval_cons_1(temp,class_attribute_values);
	class_attribute_values = eval_cons_1(pseudo_attribute_name,
		class_attribute_values);
    }
    goto next_loop;
  end_loop:;
    temp = allocate_evaluation_structure(class_attribute_values);
    return VALUES_1(temp);
}

static Object Qformat_description;  /* format-description */

static Object Qno_such_format_error;  /* no-such-format-error */

static Object Qformat_name;        /* format-name */

/* G2-GET-FORMAT-INFO-SYSTEM-RPC-INTERNAL */
Object g2_get_format_info_system_rpc_internal(rpc_instance,format_name)
    Object rpc_instance, format_name;
{
    Object format_description_qm;

    x_note_fn_call(248,50);
    format_description_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(format_name),
	    Qformat_description);
    if (format_description_qm)
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(export_format_description(format_description_qm),
		Nil));
    else
	system_rpc_access_error(rpc_instance,
		make_access_error_1(Qno_such_format_error,
		gensym_list_2(Qformat_name,format_name)));
    return VALUES_1(Nil);
}

/* EXPORT-FORMAT-DESCRIPTION */
Object export_format_description(format_description)
    Object format_description;
{
    Object name_value_plist, class_name, overrides_plist;
    Object name_and_description_alist, name, slot, ab_loop_list_, slot_type;
    Object slot_init_form_qm, override_qm, value_qm, exported_value_qm;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(248,51);
    name_value_plist = Nil;
    class_name = CAR(format_description);
    overrides_plist = CDR(format_description);
    name_and_description_alist = 
	    get_list_of_instance_attributes(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),T,list_constant_1);
    name = Nil;
    slot = Nil;
    ab_loop_list_ = name_and_description_alist;
    slot_type = Nil;
    slot_init_form_qm = Nil;
    override_qm = Nil;
    value_qm = Nil;
    exported_value_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_type = assq_function(Qtype,ISVREF(slot,(SI_Long)9L));
    slot_init_form_qm = ISVREF(slot,(SI_Long)6L);
    override_qm = getfq_function_no_default(overrides_plist,name);
    temp = override_qm;
    if (temp);
    else
	temp = slot_init_form_qm;
    value_qm = temp;
    exported_value_qm = value_qm ? export_format_value(value_qm,slot_type) 
	    : Qnil;
    if (exported_value_qm) {
	name_value_plist = eval_cons_1(name,name_value_plist);
	name_value_plist = eval_cons_1(exported_value_qm,name_value_plist);
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    if (name_value_plist)
	return allocate_evaluation_structure(nreverse(name_value_plist));
    return VALUES_1(Qnil);
}

static Object Qab_font;            /* ab-font */

static Object Qfixed14;            /* fixed14 */

static Object Qfloat_array;        /* float-array */

/* EXPORT-FORMAT-VALUE */
Object export_format_value(value,slot_type)
    Object value, slot_type;
{
    Object category_symbol_qm, category_evaluator_interface;
    Object category_getter_qm, font_name_qm, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(248,52);
    category_symbol_qm = slot_type ? SECOND(slot_type) : Nil;
    if (category_symbol_qm) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol_qm),
		Qcategory_evaluator_interface);
	category_getter_qm = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    }
    else
	category_getter_qm = Nil;
    if (CONSP(value)) {
	font_name_qm = M_CAR(value);
	if ((getfq_function_no_default(INLINE_SYMBOL_PLIST(font_name_qm),
		Qab_font) || EQ(font_name_qm,Qfixed14)) &&  !TRUEP(CDR(value)))
	    return VALUES_1(font_name_qm);
	else
	    return VALUES_1(Nil);
    }
    else if (FIXNUMP(value))
	return VALUES_1(value);
    else if ( !TRUEP(value))
	return VALUES_1(Evaluation_false_value);
    else if (EQ(value,T))
	return VALUES_1(Evaluation_true_value);
    else if (SYMBOLP(value))
	return VALUES_1(value);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	return copy_managed_float(value);
    else if (FLOATP(value)) {
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return VALUES_1(new_float);
    }
    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	return copy_managed_long(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L)
	return make_evaluation_long(value);
    else if (text_string_p(value))
	return copy_as_wide_string(value);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	gensymed_symbol = M_CAR(value);
	if (FIXNUM_EQ(gensymed_symbol,Truth))
	    return VALUES_1(Evaluation_true_value);
	else if (FIXNUM_EQ(gensymed_symbol,Falsity))
	    return VALUES_1(Evaluation_false_value);
	else
	    return eval_cons_1(gensymed_symbol,Qtruth_value);
    }
    else
	return error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value));
}

static Object string_constant_1;   /* "~A does not name a class" */

/* G2-GET-CLASS-HASH */
Object g2_get_class_hash(class_name)
    Object class_name;
{
    Object class_description_qm, indent_sequences_and_structures_p, class_info;
    Object temp, top_of_stack, message_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,53);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (class_description_qm) {
	Leave_text_representation_as_a_single_line_qm = T;
	indent_sequences_and_structures_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Indent_sequences_and_structures_p,Qindent_sequences_and_structures_p,indent_sequences_and_structures_p,
		0);
	  class_info = get_class_info(class_name,Nil,T);
	  temp = evaluation_value_hash(class_info);
	  reclaim_evaluation_value(class_info);
	  result = VALUES_1(temp);
	POP_SPECIAL();
	return result;
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_1,
		class_name);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* G2-GET-CLASS-HASH-SYSTEM-RPC-INTERNAL */
Object g2_get_class_hash_system_rpc_internal(gensymed_symbol,class_name)
    Object gensymed_symbol, class_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, result_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,54);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result_1 = g2_get_class_hash(class_name);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(result_1) != (SI_Long)0L)
		result = maybe_make_evaluation_unsigned_vector_16(result_1);
	    else
		result = VALUES_1(result_1);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qkb_workspace;       /* kb-workspace */

/* G2-GET-LIST-OF-WORKSPACES-SYSTEM-RPC-INTERNAL */
Object g2_get_list_of_workspaces_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    Object ws_info, ws_info_list, scope_conses, ab_loopvar_, ab_loopvar__1, ws;
    Object name_qm, gensymed_symbol;
    char temp;
    Declare_special(1);

    x_note_fn_call(248,55);
    ws_info = Nil;
    ws_info_list = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ws = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      name_qm = Nil;
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
      ws = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      name_qm = get_primary_name_for_frame_if_any(ws);
      gensymed_symbol = ACCESS_ONCE(ISVREF(ws,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
      temp = TRUEP(gensymed_symbol);
      if (temp);
      else
	  temp =  !TRUEP(name_qm);
      if ( !temp)
	  ws_info_list = eval_cons_1(name_qm,ws_info_list);
      goto next_loop;
    end_loop_1:
      ws_info = allocate_evaluation_sequence(ws_info_list);
      return_from_system_defined_rpc(rpc_instance,eval_cons_1(ws_info,Nil));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

/* CREATE-BOUNDS-STRUCTURE-FROM-BLOCK-EDGES */
Object create_bounds_structure_from_block_edges(block)
    Object block;
{
    Object gensymed_symbol, temp, gensymed_symbol_2, item_or_value, x2;
    Object svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,56);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qleft;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qleft;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)0L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)0L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtop;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qtop;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)1L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qright;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qright;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)2L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)2L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qbottom;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qbottom;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)3L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	gensymed_symbol_2 = ISVREF(block,(SI_Long)14L);
	gensymed_symbol_2 = gensymed_symbol_2 ? ISVREF(gensymed_symbol_2,
		(SI_Long)3L) : FIX((SI_Long)0L);
	item_or_value = gensymed_symbol_2;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* GET-GENSYM-WINDOW-FROM-SYSTEM-RPC-INSTANCE-ICP-SOCKET */
Object get_gensym_window_from_system_rpc_instance_icp_socket(system_rpc_instance_icp_socket)
    Object system_rpc_instance_icp_socket;
{
    Object workstation, ab_loop_list_, window, icp_output_port;
    Object parent_icp_socket, ab_loop_it_;

    x_note_fn_call(248,57);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    window = Nil;
    icp_output_port = Nil;
    parent_icp_socket = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    window = ISVREF(workstation,(SI_Long)1L);
    icp_output_port = ISVREF(window,(SI_Long)12L);
    parent_icp_socket = icp_output_port ? ISVREF(icp_output_port,
	    (SI_Long)2L) : Qnil;
    ab_loop_it_ = EQ(system_rpc_instance_icp_socket,parent_icp_socket) ? 
	    window : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-SET-V5-MODE-SYSTEM-RPC-INTERNAL */
Object g2_set_v5_mode_system_rpc_internal(rpc_instance,state_1)
    Object rpc_instance, state_1;
{
    x_note_fn_call(248,58);
    set_v5_mode_state(evaluation_truth_value_true_p(state_1));
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(G2_has_v5_mode_windows_p ? Evaluation_true_value : 
	    Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ws_representation_slots_to_update, Qws_representation_slots_to_update);

static Object Qg2_get_updated_workspace_information;  /* g2-get-updated-workspace-information */

/* G2-GET-UPDATED-WORKSPACE-INFORMATION-SYSTEM-RPC-INTERNAL */
Object g2_get_updated_workspace_information_system_rpc_internal(rpc_instance,
	    session,workspace,attributes)
    Object rpc_instance, session, workspace, attributes;
{
    Object gensymed_symbol, held_vector, attr, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, interim_attr_list, attr_list;
    Object result_1;
    SI_Long next_index, length_1;

    x_note_fn_call(248,59);
    if (ui_client_session_ok_for_defun_system_rpc_qm(session,rpc_instance,
	    Qg2_get_updated_workspace_information)) {
	if (attributes) {
	    gensymed_symbol = attributes;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    attr = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
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
	    attr = validated_elt;
	    ab_loopvar__2 = eval_cons_1(attr,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    interim_attr_list = ab_loopvar_;
	    goto end_1;
	    interim_attr_list = Qnil;
	  end_1:;
	}
	else
	    interim_attr_list = Nil;
	attr_list = interim_attr_list;
	if (attr_list);
	else
	    attr_list = Ws_representation_slots_to_update;
	result_1 = 
		eval_cons_1(create_ws_representation_updated_state(workspace,
		attr_list),Nil);
	if (interim_attr_list)
	    reclaim_eval_list_1(interim_attr_list);
	if (attributes)
	    reclaim_evaluation_sequence(attributes);
	return_from_system_defined_rpc(rpc_instance,result_1);
    }
    return VALUES_1(Nil);
}

static Object Qg2_represent_workspace;  /* g2-represent-workspace */

static Object Qws_representation;  /* ws-representation */

static Object Qreturn_type;        /* return-type */

static Object Qsession_association_confirmation;  /* session-association-confirmation */

static Object Qsubscription_handle;  /* subscription-handle */

static Object Qsession_already_associated;  /* session-already-associated */

static Object string_constant_2;   /* "session already associated with workspace" */

static Object Qinitial_subscription_data;  /* initial-subscription-data */

static Object Qworkspace_initial_data;  /* workspace-initial-data */

/* G2-REPRESENT-WORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_represent_workspace_system_rpc_internal(rpc_instance,session,
	    workspace,callback_procedure)
    Object rpc_instance, session, workspace, callback_procedure;
{
    Object existing_representation_for_session_qm, gensymed_symbol, temp;
    Object item_or_value, x2, svref_new_value, icp_socket, ws_initial_data;
    Object representation, subscription_handle;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,60);
    if (ui_client_session_ok_for_defun_system_rpc_qm(session,rpc_instance,
	    Qg2_represent_workspace)) {
	existing_representation_for_session_qm = 
		find_frame_representation_for_this_session(session,
		workspace,Qws_representation);
	if (existing_representation_for_session_qm) {
	    if (associate_workspace_with_ui_session(session,workspace)) {
		gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L 
			+ (SI_Long)1L));
		gensymed_symbol_1 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qreturn_type;
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)1L)) = Qreturn_type;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = Qsession_association_confirmation;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
		}
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = Qsession_association_confirmation;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
			    Qsubscription_handle;
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)3L)) = Qsubscription_handle;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    ISVREF(existing_representation_for_session_qm,
			    (SI_Long)12L);
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp = temp_1 ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
		}
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = 
			    ISVREF(existing_representation_for_session_qm,
			    (SI_Long)12L);
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    svref_new_value = temp_1 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
		}
		return_from_system_defined_rpc(rpc_instance,
			eval_cons_1(eval_cons_1(gensymed_symbol,
			Qab_structure),Nil));
	    }
	    else
		system_rpc_error(rpc_instance,Qsession_already_associated,
			tformat_text_string(1,string_constant_2));
	}
	else {
	    icp_socket = ISVREF(rpc_instance,(SI_Long)2L);
	    ws_initial_data = 
		    create_ws_representation_initial_state(workspace);
	    representation = represent_ws(workspace,icp_socket,
		    callback_procedure);
	    subscription_handle = ISVREF(representation,(SI_Long)12L);
	    associate_workspace_with_ui_session(session,workspace);
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qreturn_type;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qreturn_type;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qinitial_subscription_data;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qinitial_subscription_data;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
			Qworkspace_initial_data;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qworkspace_initial_data;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = ws_initial_data;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = ws_initial_data;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsubscription_handle;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qsubscription_handle;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = subscription_handle;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp = temp_1 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = subscription_handle;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_1 = TRUEP(Nil);
		svref_new_value = temp_1 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    return_from_system_defined_rpc(rpc_instance,
		    eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
		    Nil));
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2_represent_trend_chart;  /* g2-represent-trend-chart */

static Object Qui_client_interface;  /* ui-client-interface */

static Object Qitem_initial_data;  /* item-initial-data */

/* G2-REPRESENT-TREND-CHART-SYSTEM-RPC-INTERNAL */
Object g2_represent_trend_chart_system_rpc_internal(rpc_instance,item,
	    callback_procedure)
    Object rpc_instance, item, callback_procedure;
{
    Object icp_socket, item_initial_data, representation, subscription_handle;
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,61);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_represent_trend_chart,
	    Qui_client_interface)) {
	icp_socket = ISVREF(rpc_instance,(SI_Long)2L);
	item_initial_data = trend_chart_property_getter(item);
	representation = represent_trend_chart(item,icp_socket,
		callback_procedure);
	subscription_handle = ISVREF(representation,(SI_Long)12L);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qitem_initial_data;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qitem_initial_data;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = item_initial_data;
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = item_initial_data;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qsubscription_handle;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qsubscription_handle;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = subscription_handle;
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = subscription_handle;
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	}
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),Nil));
    }
    return VALUES_1(Nil);
}

static Object Qsession_and_workspace_not_associated;  /* session-and-workspace-not-associated */

static Object string_constant_3;   /* "session and workspace not associated" */

/* G2-UNREPRESENT-WORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_unrepresent_workspace_system_rpc_internal(rpc_instance,session,
	    subscription_handle)
    Object rpc_instance, session, subscription_handle;
{
    Object representation_qm, session_ok_qm, frame;

    x_note_fn_call(248,62);
    representation_qm = representation_handle_gethash(subscription_handle);
    session_ok_qm = ui_client_session_ok_for_defun_system_rpc_qm(session,
	    rpc_instance,Qg2_represent_workspace);
    if ( !TRUEP(session_ok_qm));
    else if ( !TRUEP(representation_qm))
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(Evaluation_false_value,Nil));
    else {
	frame = ISVREF(representation_qm,(SI_Long)9L);
	if (disassociate_workspace_from_ui_session(session,frame)) {
	    if ( !TRUEP(any_session_ws_associations_remaining_p(frame,
		    ISVREF(session,(SI_Long)26L))))
		delete_representation(1,representation_qm);
	    return_from_system_defined_rpc(rpc_instance,
		    eval_cons_1(Evaluation_true_value,Nil));
	}
	else
	    system_rpc_error(rpc_instance,
		    Qsession_and_workspace_not_associated,
		    tformat_text_string(1,string_constant_3));
    }
    return VALUES_1(Nil);
}

static Object Qis_moved_by_the_user;  /* is-moved-by-the-user */

/* G2-MOVE-WS-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_move_ws_item_system_rpc_internal(rpc_instance,item,xpos,ypos,
	    enlarge_workspace_if_necessary_p_ev,transient_change_p_ev)
    Object rpc_instance, item, xpos, ypos, enlarge_workspace_if_necessary_p_ev;
    Object transient_change_p_ev;
{
    Object temp, enlarge_workspace_if_necessary_p, transient_change_p, deltax;
    Object deltay, gensymed_symbol, temp_1, temp_2, temp_3;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(248,63);
    temp = 
	    evaluation_truth_value_is_true_p(enlarge_workspace_if_necessary_p_ev);
    if ( !(EQ(enlarge_workspace_if_necessary_p_ev,Evaluation_true_value) 
	    || EQ(enlarge_workspace_if_necessary_p_ev,Evaluation_false_value)))
	reclaim_eval_cons_1(enlarge_workspace_if_necessary_p_ev);
    enlarge_workspace_if_necessary_p = temp;
    temp = evaluation_truth_value_is_true_p(transient_change_p_ev);
    if ( !(EQ(transient_change_p_ev,Evaluation_true_value) || 
	    EQ(transient_change_p_ev,Evaluation_false_value)))
	reclaim_eval_cons_1(transient_change_p_ev);
    transient_change_p = temp;
    if (item) {
	deltax = FIXNUM_MINUS(xpos,item_x_position(item));
	deltay = FIXNUM_MINUS(ypos,item_y_position(item));
	if (enlarge_workspace_if_necessary_p) {
	    temp = get_workspace_if_any(item);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(deltax);
	    temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(FIXNUM_NEGATE(deltay));
	    temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(deltax);
	    temp_3 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(FIXNUM_NEGATE(deltay));
	    enlarge_workspace_if_necessary(5,temp,temp_1,temp_2,temp_3,
		    FIX(gensymed_symbol_1 + gensymed_symbol_2));
	}
	move_item_by(4,item,deltax,deltay,transient_change_p);
	invoke_rules_for_movement_chaining(2,item,Qis_moved_by_the_user);
    }
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(item ? 
	    Evaluation_true_value : Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-SHUTDOWN-G2-PROCESS-SYSTEM-RPC-INTERNAL */
Object g2_shutdown_g2_process_system_rpc_internal(gensymed_symbol,status)
    Object gensymed_symbol, status;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,64);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    shut_down_ab_process(1,status);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CLEAR-KB-SYSTEM-RPC-INTERNAL */
Object g2_clear_kb_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,65);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    if (( !TRUEP(System_is_running) || System_has_paused) &&  
		    !TRUEP(Inside_breakpoint_p))
		clear_kb(0);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-SET-PACKAGE-PREPARATION-MODE-SYSTEM-RPC-INTERNAL */
Object g2_set_package_preparation_mode_system_rpc_internal(rpc_instance,
	    new_state)
    Object rpc_instance, new_state;
{
    x_note_fn_call(248,66);
    set_package_preparation_mode(evaluation_truth_value_is_true_p(new_state));
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Package_preparation_mode ? Evaluation_true_value : 
	    Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-GET-PACKAGE-PREPARATION-MODE-SYSTEM-RPC-INTERNAL */
Object g2_get_package_preparation_mode_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    x_note_fn_call(248,67);
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Package_preparation_mode ? Evaluation_true_value : 
	    Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-SET-SIMULATE-PROPRIETARY-MODE-SYSTEM-RPC-INTERNAL */
Object g2_set_simulate_proprietary_mode_system_rpc_internal(rpc_instance,
	    new_state)
    Object rpc_instance, new_state;
{
    x_note_fn_call(248,68);
    set_simulate_proprietary_mode(evaluation_truth_value_is_true_p(new_state));
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Simulate_proprietary_qm ? Evaluation_true_value : 
	    Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-GET-SIMULATE-PROPRIETARY-MODE-SYSTEM-RPC-INTERNAL */
Object g2_get_simulate_proprietary_mode_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    x_note_fn_call(248,69);
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Simulate_proprietary_qm ? Evaluation_true_value : 
	    Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-STRIP-ALL-TEXTS-SYSTEM-RPC-INTERNAL */
Object g2_strip_all_texts_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    x_note_fn_call(248,70);
    strip_all_texts();
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Evaluation_true_value,Nil));
    return VALUES_1(Nil);
}

/* G2-MAKE-KB-PROPRIETARY-SYSTEM-RPC-INTERNAL */
Object g2_make_kb_proprietary_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    x_note_fn_call(248,71);
    make_proprietary_now();
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Evaluation_true_value,Nil));
    return VALUES_1(Nil);
}

/* G2-FLUSH-ALL-CHANGE-LOGS-SYSTEM-RPC-INTERNAL */
Object g2_flush_all_change_logs_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    x_note_fn_call(248,72);
    flush_change_log_for_entire_kb_now();
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Evaluation_true_value,Nil));
    return VALUES_1(Nil);
}

/* G2-ENABLE-ALL-ITEMS-SYSTEM-RPC-INTERNAL */
Object g2_enable_all_items_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame, gensymed_symbol;
    Object gensymed_symbol_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(248,73);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & (SI_Long)8192L)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)48L),(SI_Long)1L);
	  gensymed_symbol_1 = frame;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(Evaluation_true_value,Nil));
    return VALUES_1(Nil);
}

/* G2-MOVE-WS-ITEM-BY-SYSTEM-RPC-INTERNAL */
Object g2_move_ws_item_by_system_rpc_internal(rpc_instance,item,deltax,
	    deltay,enlarge_workspace_if_necessary_p_ev,transient_change_p_ev)
    Object rpc_instance, item, deltax, deltay;
    Object enlarge_workspace_if_necessary_p_ev, transient_change_p_ev;
{
    Object temp, enlarge_workspace_if_necessary_p, transient_change_p;
    Object workspace_qm, extreme_left_edge, extreme_top_edge;
    Object extreme_right_edge, extreme_bottom_edge;
    Object result;

    x_note_fn_call(248,74);
    temp = 
	    evaluation_truth_value_is_true_p(enlarge_workspace_if_necessary_p_ev);
    if ( !(EQ(enlarge_workspace_if_necessary_p_ev,Evaluation_true_value) 
	    || EQ(enlarge_workspace_if_necessary_p_ev,Evaluation_false_value)))
	reclaim_eval_cons_1(enlarge_workspace_if_necessary_p_ev);
    enlarge_workspace_if_necessary_p = temp;
    temp = evaluation_truth_value_is_true_p(transient_change_p_ev);
    if ( !(EQ(transient_change_p_ev,Evaluation_true_value) || 
	    EQ(transient_change_p_ev,Evaluation_false_value)))
	reclaim_eval_cons_1(transient_change_p_ev);
    transient_change_p = temp;
    if (item) {
	workspace_qm = get_workspace_if_any(item);
	if (workspace_qm && enlarge_workspace_if_necessary_p) {
	    result = determine_extreme_edges_for_item_being_moved(item);
	    MVS_4(result,extreme_left_edge,extreme_top_edge,
		    extreme_right_edge,extreme_bottom_edge);
	    enlarge_workspace_if_necessary(5,workspace_qm,
		    FIXNUM_ADD(extreme_left_edge,deltax),
		    FIXNUM_ADD(extreme_top_edge,deltay),
		    FIXNUM_ADD(extreme_right_edge,deltax),
		    FIXNUM_ADD(extreme_bottom_edge,deltay));
	}
	move_item_by(4,item,deltax,FIXNUM_NEGATE(deltay),transient_change_p);
	invoke_rules_for_movement_chaining(2,item,Qis_moved_by_the_user);
    }
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(item ? 
	    Evaluation_true_value : Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

static Object Qis_moved_by_g2;     /* is-moved-by-g2 */

static Object Qsocket;             /* socket */

/* G2-MOVE-ITEMS-ALONG-PATHS */
Object g2_move_items_along_paths(items,paths,interval,return_rpc_name,id)
    Object items, paths, interval, return_rpc_name, id;
{
    Object sessions, enlarge_workspace_if_necessary_p, transient_change_p;
    Object gensymed_symbol, held_vector, item, gensymed_symbol_1;
    Object held_vector_1, path, length_3, xpos, ypos, deltax, deltay;
    Object workspace_qm, elt_1, validated_elt, temp, extreme_left_edge;
    Object extreme_top_edge, extreme_right_edge, extreme_bottom_edge;
    Object notification_data_version_map, any_body_evaluated_p, frame_list;
    Object class_name, new_list, frame, ab_loop_list_, sub_class_bit_vector;
    Object representations, current_frame_serial_number_on_entry;
    Object representation, xa, ya, version_for_current, evaluatedp, address;
    Object socket_1, representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send, reps;
    Object current_frame_serial_number_on_entry_1, rep, session;
    SI_Long next_index, length_1, next_index_1, length_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,75);
    SAVE_STACK();
    sessions = Qnil;
    enlarge_workspace_if_necessary_p = T;
    transient_change_p = Nil;
    gensymed_symbol = items;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    item = Nil;
    gensymed_symbol_1 = paths;
    held_vector_1 = Nil;
    next_index_1 = (SI_Long)1L;
    length_2 = (SI_Long)0L;
    path = Nil;
    length_3 = Nil;
    xpos = Nil;
    ypos = Nil;
    deltax = Nil;
    deltay = Nil;
    workspace_qm = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
    held_vector_1 = M_CAR(gensymed_symbol_1);
    length_2 = IFIX(ISVREF(held_vector_1,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    item = validated_elt;
    if (next_index_1 >= length_2)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector_1,
	    next_index_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector_1,(next_index_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),next_index_1 & (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index_1 = next_index_1 + (SI_Long)1L;
    path = validated_elt;
    length_3 = FIXNUM_SUB1(ISVREF(M_CAR(path),(SI_Long)1L));
    xpos = evaluation_sequence_aref(path,FIX(IFIX(length_3) - (SI_Long)2L));
    ypos = evaluation_sequence_aref(path,FIXNUM_SUB1(length_3));
    temp = xpos;
    deltax = FIXNUM_MINUS(temp,item_x_position(item));
    temp = ypos;
    deltay = FIXNUM_MINUS(temp,item_y_position(item));
    workspace_qm = get_workspace_if_any(item);
    if (workspace_qm && enlarge_workspace_if_necessary_p) {
	result = determine_extreme_edges_for_item_being_moved(item);
	MVS_4(result,extreme_left_edge,extreme_top_edge,extreme_right_edge,
		extreme_bottom_edge);
	enlarge_workspace_if_necessary(5,workspace_qm,
		FIXNUM_ADD(extreme_left_edge,deltax),
		FIXNUM_ADD(extreme_top_edge,deltay),
		FIXNUM_ADD(extreme_right_edge,deltax),
		FIXNUM_ADD(extreme_bottom_edge,deltay));
    }
    move_item_by(4,item,deltax,deltay,transient_change_p);
    invoke_rules_for_movement_chaining(3,item,Qis_moved_by_g2,T);
    if (G2_has_v5_mode_windows_p && workspace_qm) {
	LOCK(Javalink_notification_versions);
	if (PUSH_UNWIND_PROTECT(1)) {
	    notification_data_version_map = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		    1);
	      if (workspace_qm && v5_tw_item_like_p(workspace_qm)) {
		  any_body_evaluated_p = Nil;
		  frame_list = ISVREF(workspace_qm,(SI_Long)9L);
		  class_name = Qws_representation;
		  new_list = Qnil;
		  frame = Nil;
		  ab_loop_list_ = frame_list;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  frame = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol = 
			  lookup_global_or_kb_specific_property_value(class_name,
			  Class_description_gkbprop);
		  if (gensymed_symbol) {
		      sub_class_bit_vector = ISVREF(ISVREF(frame,
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
			  temp_1 = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      new_list = gensym_cons_1(frame,new_list);
		  goto next_loop_1;
		end_loop_1:
		  representations = new_list;
		  goto end_1;
		  representations = Qnil;
		end_1:;
		  current_frame_serial_number_on_entry = 
			  copy_frame_serial_number(Current_frame_serial_number);
		  representation = Nil;
		  ab_loop_list_ = representations;
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  representation = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol = ISVREF(representation,(SI_Long)3L);
		  temp_1 = SIMPLE_VECTOR_P(representation) ? 
			  EQ(ISVREF(representation,(SI_Long)1L),
			  Qavailable_frame_vector) : TRUEP(Qnil);
		  if (temp_1);
		  else
		      temp_1 = FIXNUMP(gensymed_symbol) ? 
			      IFIX(gensymed_symbol) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  if (temp_1);
		  else if (FIXNUMP(current_frame_serial_number_on_entry))
		      temp_1 = FIXNUMP(gensymed_symbol) ? 
			      FIXNUM_LT(current_frame_serial_number_on_entry,
			      gensymed_symbol) : TRUEP(T);
		  else if (FIXNUMP(gensymed_symbol))
		      temp_1 = TRUEP(Nil);
		  else {
		      xa = M_CAR(current_frame_serial_number_on_entry);
		      ya = M_CAR(gensymed_symbol);
		      temp_1 = FIXNUM_LT(xa,ya);
		      if (temp_1);
		      else
			  temp_1 = FIXNUM_EQ(xa,ya) ? 
				  FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
				  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		  }
		  if ( !temp_1 ? 
			  TRUEP(representation_address_valid_p(representation)) 
			  : TRUEP(Nil)) {
		      if ( !TRUEP(Notification_data_version_map))
			  Notification_data_version_map = gensym_cons_1(T,Nil);
		      version_for_current = Nil;
		      evaluatedp = Nil;
		      address = ISVREF(representation,(SI_Long)8L);
		      socket_1 = getf(address,Qsocket,_);
		      representation_version = 
			      remote_icp_protocol_version(socket_1);
		      subscription_handle = ISVREF(representation,
			      (SI_Long)12L);
		      current_list = Notification_data_version_map;
		      version_or_data = Nil;
		    next_loop_3:
		      version_or_data = CAR(current_list);
		      if ( !TRUEP(version_or_data))
			  goto end_2;
		      version_for_current = 
			      javalink_versioned_call_data_get_version(version_or_data);
		      evaluatedp = 
			      javalink_versioned_call_data_evaluated_p(version_or_data);
		      if (EQ(version_for_current,T) || 
			      FIXNUM_GE(representation_version,
			      version_for_current)) {
			  if ( !TRUEP(evaluatedp)) {
			      LOCK(Javalink_notification_versions);
			      if (PUSH_UNWIND_PROTECT(0)) {
				  current_lookup_data = 
					  make_javalink_versioned_data(version_or_data);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
					  0);
				    send_ws_representations_item_moved_aux(item,
					    path,FIX((SI_Long)0L),
					    FIX((SI_Long)0L),interval,
					    return_rpc_name,id);
				    temp = Current_lookup_data;
				  POP_SPECIAL();
				  SAVE_VALUES(VALUES_1(temp));
			      }
			      POP_UNWIND_PROTECT(0);
			      UNLOCK(Javalink_notification_versions);
			      CONTINUE_UNWINDING(0);
			      result = RESTORE_VALUES();
			      version_or_data = result;
			      M_CAR(current_list) = version_or_data;
			  }
			  if (javalink_versioned_call_data_sendp(version_or_data)) 
				      {
			      arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			      arg_list = Nil;
			      ab_loop_list__1 = arg_lists;
			      arg_list_to_send = Nil;
			    next_loop_4:
			      if ( !TRUEP(ab_loop_list__1))
				  goto end_loop_3;
			      arg_list = M_CAR(ab_loop_list__1);
			      ab_loop_list__1 = M_CDR(ab_loop_list__1);
			      arg_list_to_send = 
				      javalink_versioning_make_arg_list_copy(arg_list,
				      subscription_handle);
			      callback_representation_fire_callback(representation,
				      socket_1,arg_list_to_send);
			      goto next_loop_4;
			    end_loop_3:;
			  }
			  goto end_2;
		      }
		      current_list = CDR(current_list);
		      goto next_loop_3;
		    end_loop_4:
		    end_2:;
		  }
		  goto next_loop_2;
		end_loop_2:
		  reclaim_gensym_list_1(representations);
		  reclaim_frame_serial_number(current_frame_serial_number_on_entry);
		  javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
		  goto end_3;
		end_3:;
	      }
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Javalink_notification_versions);
	CONTINUE_UNWINDING(1);
	reps = ISVREF(workspace_qm,(SI_Long)9L);
	current_frame_serial_number_on_entry_1 = 
		copy_frame_serial_number(Current_frame_serial_number);
	rep = Nil;
	ab_loop_list_ = reps;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	rep = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qws_representation,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(rep,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(rep,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(rep) ? EQ(ISVREF(rep,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(current_frame_serial_number_on_entry_1))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(current_frame_serial_number_on_entry_1,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(current_frame_serial_number_on_entry_1);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry_1),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? TRUEP(representation_address_valid_p(rep)) : TRUEP(Nil)) {
	    session = Nil;
	    ab_loop_list__1 = 
		    ISVREF(get_interface_from_representation(rep),
		    (SI_Long)26L);
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_6;
	    session = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (workspace_is_showing_in_ui_client_item(workspace_qm,session))
		sessions = eval_cons_1(session,sessions);
	    goto next_loop_6;
	  end_loop_6:;
	}
	goto next_loop_5;
      end_loop_5:
	reclaim_frame_serial_number(current_frame_serial_number_on_entry_1);
    }
    goto next_loop;
  end_loop:
    reclaim_evaluation_sequence(items);
    reclaim_evaluation_sequence(paths);
    result = allocate_evaluation_sequence(sessions);
    RESTORE_STACK();
    return result;
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* G2-CREATE-ITEM */
Object g2_create_item(class_name)
    Object class_name;
{
    x_note_fn_call(248,76);
    return create_action_internal(class_name,Cached_top_of_stack);
}

/* G2-CREATE-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_create_item_system_rpc_internal(gensymed_symbol,class_name)
    Object gensymed_symbol, class_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,77);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_create_item(class_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CLONE-ITEM */
Object g2_clone_item(item)
    Object item;
{
    x_note_fn_call(248,78);
    return create_by_cloning_action_internal(ISVREF(ISVREF(item,
	    (SI_Long)1L),(SI_Long)1L),item,Cached_top_of_stack,Nil);
}

/* G2-CLONE-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_clone_item_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,79);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_clone_item(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qattribute;          /* attribute */

/* G2-TRANSFER-ITEM */
Object g2_transfer_item(item,target_item,ypos,xpos,attribute_name_or_false,
	    class_qualifier_or_false)
    Object item, target_item, ypos, xpos, attribute_name_or_false;
    Object class_qualifier_or_false;
{
    Object x2, sub_class_bit_vector, place_reference;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,80);
    if (item && target_item) {
	if (SIMPLE_VECTOR_P(target_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(target_item)) > (SI_Long)2L 
		&&  !EQ(ISVREF(target_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(target_item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(target_item,(SI_Long)1L),
		    (SI_Long)19L);
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
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ?  !SYMBOLP(attribute_name_or_false) : TRUEP(Nil)) {
	    transfer_action_internal(item,target_item,xpos,ypos,
		    Cached_top_of_stack,Nil);
	    return VALUES_1(Evaluation_true_value);
	}
	else {
	    if (SIMPLE_VECTOR_P(target_item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(target_item)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(target_item,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(target_item,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? SYMBOLP(attribute_name_or_false) : TRUEP(Nil)) {
		place_reference = 
			make_evaluation_place_reference_to_place(slot_value_list_4(Qattribute,
			attribute_name_or_false,
			SYMBOLP(class_qualifier_or_false) ? 
			class_qualifier_or_false : Qnil,
			Qcurrent_computation_frame),target_item);
		transfer_action_internal(item,place_reference,xpos,ypos,
			Cached_top_of_stack,Nil);
		return VALUES_1(Evaluation_true_value);
	    }
	    else {
		if (SIMPLE_VECTOR_P(target_item) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(target_item)) > 
			(SI_Long)2L &&  !EQ(ISVREF(target_item,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(target_item,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp) {
		    transfer_action_internal(item,Nil,xpos,ypos,
			    Cached_top_of_stack,Nil);
		    return VALUES_1(Evaluation_true_value);
		}
		else
		    return VALUES_1(Evaluation_false_value);
	    }
	}
    }
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-TRANSFER-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_transfer_item_system_rpc_internal(gensymed_symbol,item,
	    target_item,xpos,ypos,attribute_name_or_false,
	    class_qualifier_or_false)
    Object gensymed_symbol, item, target_item, xpos, ypos;
    Object attribute_name_or_false, class_qualifier_or_false;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object current_computation_frame, current_computation_instance;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(248,81);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  2);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    current_computation_frame = 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
	    current_computation_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		result = g2_transfer_item(item,target_item,ypos,xpos,
			attribute_name_or_false,class_qualifier_or_false);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DELETE-ITEM */
Object g2_delete_item(item,without_permanence_checks_p,without_leaving_stubs_p)
    Object item, without_permanence_checks_p, without_leaving_stubs_p;
{
    Object temp, temp_1;

    x_note_fn_call(248,82);
    temp = evaluation_truth_value_is_true_p(without_permanence_checks_p);
    if ( !(EQ(without_permanence_checks_p,Evaluation_true_value) || 
	    EQ(without_permanence_checks_p,Evaluation_false_value)))
	reclaim_eval_cons_1(without_permanence_checks_p);
    temp_1 = evaluation_truth_value_is_true_p(without_leaving_stubs_p);
    if ( !(EQ(without_leaving_stubs_p,Evaluation_true_value) || 
	    EQ(without_leaving_stubs_p,Evaluation_false_value)))
	reclaim_eval_cons_1(without_leaving_stubs_p);
    delete_action_internal(item,temp,temp_1,Cached_top_of_stack,Nil);
    return VALUES_1(Nil);
}

/* G2-DELETE-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_delete_item_system_rpc_internal(gensymed_symbol,item,
	    without_permanence_checks_p,without_leaving_stubs_p)
    Object gensymed_symbol, item, without_permanence_checks_p;
    Object without_leaving_stubs_p;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, current_computation_frame;
    Object current_computation_instance, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(248,83);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  2);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    current_computation_frame = 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
	    current_computation_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      0);
		gensymed_symbol_1 = g2_delete_item(item,
			without_permanence_checks_p,without_leaving_stubs_p);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* INITIAL-PERMANENT */
Object initial_permanent(class_1)
    Object class_1;
{
    x_note_fn_call(248,84);
    return VALUES_1(Nil);
}

/* GET-PERMANENT */
Object get_permanent(item)
    Object item;
{
    x_note_fn_call(248,85);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)1L) ? Evaluation_true_value : Evaluation_false_value);
}

/* INITIAL-MANUALLY-DISABLED? */
Object initial_manually_disabled_qm(class_1)
    Object class_1;
{
    x_note_fn_call(248,86);
    return VALUES_1(Nil);
}

/* GET-MANUALLY-DISABLED? */
Object get_manually_disabled_qm(item)
    Object item;
{
    x_note_fn_call(248,87);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)8192L) ? Evaluation_true_value : Evaluation_false_value);
}

static Object string_constant_4;   /* "~NF may not be enabled or disabled" */

static Object string_constant_5;   /* "~NF can not be disabled because it is currently running" */

/* SET-MANUALLY-DISABLED? */
Object set_manually_disabled_qm(item,new_value)
    Object item, new_value;
{
    Object temp, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(248,88);
    if ( !TRUEP(frame_may_be_enabled_or_disabled_p(1,item)))
	temp = tformat_text_string(2,string_constant_4,item);
    else if (evaluation_truth_value_true_p(new_value) && 
	    Current_computation_frame && Current_computation_instance && 
	    existence_depends_on_p(Current_computation_frame,item))
	temp = tformat_text_string(2,string_constant_5,item);
    else {
	if (evaluation_truth_value_true_p(new_value)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
		    (SI_Long)8192L))) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)47L),(SI_Long)1L);
		gensymed_symbol_1 = item;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	}
	else if ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
		(SI_Long)8192L)) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)48L),(SI_Long)1L);
	    gensymed_symbol_1 = item;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* G2-MAKE-PERMANENT */
Object g2_make_permanent(item)
    Object item;
{
    x_note_fn_call(248,89);
    return make_permanent_action_internal(item,Cached_top_of_stack);
}

/* G2-MAKE-PERMANENT-SYSTEM-RPC-INTERNAL */
Object g2_make_permanent_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,90);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    g2_make_permanent(item);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* INITIAL-TRANSIENT */
Object initial_transient(class_1)
    Object class_1;
{
    x_note_fn_call(248,91);
    return VALUES_1(Nil);
}

/* GET-TRANSIENT */
Object get_transient(item)
    Object item;
{
    x_note_fn_call(248,92);
    return VALUES_1((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	    (SI_Long)262144L) ? Evaluation_true_value : 
	    Evaluation_false_value);
}

/* G2-MAKE-TRANSIENT */
Object g2_make_transient(item)
    Object item;
{
    x_note_fn_call(248,93);
    return make_transient_action_internal(item,Cached_top_of_stack);
}

/* G2-MAKE-TRANSIENT-SYSTEM-RPC-INTERNAL */
Object g2_make_transient_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,94);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_make_transient(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-SUBWORKSPACE */
Object g2_get_subworkspace(item)
    Object item;
{
    Object temp;

    x_note_fn_call(248,95);
    temp = ISVREF(item,(SI_Long)18L);
    return VALUES_1(CAR(temp));
}

/* G2-GET-SUBWORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_get_subworkspace_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,96);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_subworkspace(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-REFERENCED-ITEMS */
Object g2_get_referenced_items(message_1)
    Object message_1;
{
    Object snapshots, snapshot, ab_loop_list_, block, lst, ab_loopvar_;
    Object ab_loopvar__1;

    x_note_fn_call(248,97);
    snapshots = snapshots_of_valid_blocks_related_to_message(message_1);
    snapshot = Nil;
    ab_loop_list_ = snapshots;
    block = Nil;
    lst = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    snapshot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    block = ISVREF(snapshot,(SI_Long)1L);
    if (allow_go_to_referenced_item_p(block)) {
	ab_loopvar__1 = eval_cons_1(block,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    lst = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if (lst)
	return allocate_evaluation_sequence(lst);
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

/* G2-GET-REFERENCED-ITEMS-SYSTEM-RPC-INTERNAL */
Object g2_get_referenced_items_system_rpc_internal(gensymed_symbol,message_1)
    Object gensymed_symbol, message_1;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,98);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_referenced_items(message_1);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-NAME-FOR-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_name_for_item_system_rpc_internal(gensymed_symbol,frame)
    Object gensymed_symbol, frame;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,99);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_user_name_for_frame(frame);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-ORIGIN-OF-MESSAGE */
Object g2_get_origin_of_message(text_box)
    Object text_box;
{
    Object originating_frame_qm, temp;

    x_note_fn_call(248,100);
    originating_frame_qm = get_origin_of_message_if_appropriate(text_box);
    temp = originating_frame_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-GET-ORIGIN-OF-MESSAGE-SYSTEM-RPC-INTERNAL */
Object g2_get_origin_of_message_system_rpc_internal(gensymed_symbol,text_box)
    Object gensymed_symbol, text_box;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object origin_or_falsity, x2, passed_top_of_stack, error_1, error_text;
    Object supress_debugging_info_qm, temp_1, error_text_string;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,101);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    origin_or_falsity = g2_get_origin_of_message(text_box);
	    if (SIMPLE_VECTOR_P(origin_or_falsity) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(origin_or_falsity)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(origin_or_falsity,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(origin_or_falsity,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = VALUES_1(origin_or_falsity);
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MAKE-SUBWORKSPACE */
Object g2_make_subworkspace(kb_workspace,target_item)
    Object kb_workspace, target_item;
{
    x_note_fn_call(248,102);
    make_subworkspace_action_internal(kb_workspace,target_item,
	    Cached_top_of_stack);
    return VALUES_1(Nil);
}

/* G2-MAKE-SUBWORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_make_subworkspace_system_rpc_internal(gensymed_symbol,
	    kb_workspace,target_item)
    Object gensymed_symbol, kb_workspace, target_item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,103);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_make_subworkspace(kb_workspace,target_item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-CONTAINMENT-HIERARCHY */
Object g2_get_containment_hierarchy(item)
    Object item;
{
    Object containment_list, current_item, superior_frame_1;

    x_note_fn_call(248,104);
    containment_list = Nil;
    current_item = item;
    superior_frame_1 = Nil;
  next_loop:
    superior_frame_1 = superior_frame(current_item);
    if ( !TRUEP(superior_frame_1))
	goto end_loop;
    containment_list = eval_cons_1(superior_frame_1,containment_list);
    current_item = superior_frame_1;
    goto next_loop;
  end_loop:
    return allocate_evaluation_sequence(nreverse(containment_list));
    return VALUES_1(Qnil);
}

static Object string_constant_6;   /* "Call to ~A not available to interface ~NF" */

static Object Qg2_get_containment_hierarchy;  /* g2-get-containment-hierarchy */

/* G2-GET-CONTAINMENT-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_containment_hierarchy_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,105);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_get_containment_hierarchy,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_get_containment_hierarchy(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* EXPORTED-USER-MENU-CHOICE-P */
Object exported_user_menu_choice_p(user_menu_choice,frame,restrictions,
	    permitted_qm)
    Object user_menu_choice, frame, restrictions, permitted_qm;
{
    Object choice_name;

    x_note_fn_call(248,106);
    choice_name = ISVREF(user_menu_choice,(SI_Long)20L);
    return VALUES_1(choice_name &&  !TRUEP(built_in_menu_choice_p(1,
	    choice_name)) && ISVREF(user_menu_choice,(SI_Long)23L) && 
	    evaluate_user_menu_choice_condition(user_menu_choice,frame) ? 
	    (memq_function(choice_name,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil) : Qnil);
}

static Object list_constant_2;     /* # */

static Object Qg2_user_mode;       /* g2-user-mode */

/* G2-GET-CURRENT-USER-MENU-CHOICES */
Object g2_get_current_user_menu_choices(item,user_mode_or_g2_window)
    Object item, user_mode_or_g2_window;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, gensym_window;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(248,107);
    SAVE_STACK();
    check_type_or_stack_error(2,user_mode_or_g2_window,list_constant_2);
    if (SYMBOLP(user_mode_or_g2_window)) {
	result = g2_get_current_user_menu_choices_internal(item,
		user_mode_or_g2_window);
	RESTORE_STACK();
	return result;
    }
    else {
	if (SIMPLE_VECTOR_P(user_mode_or_g2_window) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(user_mode_or_g2_window)) > 
		(SI_Long)2L &&  !EQ(ISVREF(user_mode_or_g2_window,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(user_mode_or_g2_window,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	if (temp) {
	    gensym_window = 
		    map_to_gensym_window_or_stack_error(user_mode_or_g2_window);
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = ISVREF(gensym_window,(SI_Long)2L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			11);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  10);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    9);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      8);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				7);
			  temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  6);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    5);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
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
					SAVE_VALUES(g2_get_current_user_menu_choices_internal(item,
						get_lookup_slot_value_given_default(user_mode_or_g2_window,
						Qg2_user_mode,Nil)));
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
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Qnil);
	}
    }
}

/* G2-GET-CURRENT-USER-MENU-CHOICES-INTERNAL */
Object g2_get_current_user_menu_choices_internal(item,user_mode)
    Object item, user_mode;
{
    Object class_1, exported_user_menu_choices, current_g2_user_mode_qm;
    Object restrictions, permitted, superior_class, class_description;
    Object ab_loop_list_, current_user_menu_choice, ab_loop_list__1;
    Object exported_user_menu_choice, ab_loop_list__2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,108);
    class_1 = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    exported_user_menu_choices = Nil;
    current_g2_user_mode_qm = user_mode;
    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
	    0);
      restrictions = Nil;
      permitted = Nil;
      superior_class = Nil;
      class_description = 
	      lookup_global_or_kb_specific_property_value(class_1,
	      Class_description_gkbprop);
      ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
      result = compute_menu_restrictions_for_workspace(item);
      MVS_2(result,restrictions,permitted);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      superior_class = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      current_user_menu_choice = Nil;
      ab_loop_list__1 = lookup_kb_specific_property_value(superior_class,
	      User_menu_choices_for_this_class_kbprop);
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      current_user_menu_choice = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (exported_user_menu_choice_p(current_user_menu_choice,item,
	      restrictions,permitted)) {
	  exported_user_menu_choice = Nil;
	  ab_loop_list__2 = exported_user_menu_choices;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list__2))
	      goto end_loop_2;
	  exported_user_menu_choice = M_CAR(ab_loop_list__2);
	  ab_loop_list__2 = M_CDR(ab_loop_list__2);
	  if (EQ(ISVREF(current_user_menu_choice,(SI_Long)20L),
		  ISVREF(exported_user_menu_choice,(SI_Long)20L))) {
	      temp = TRUEP(Nil);
	      goto end_1;
	  }
	  goto next_loop_2;
	end_loop_2:
	  temp = TRUEP(T);
	  goto end_1;
	  temp = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  exported_user_menu_choices = 
		  eval_cons_1(current_user_menu_choice,
		  exported_user_menu_choices);
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:
      result = allocate_evaluation_sequence(exported_user_menu_choices);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object Qg2_get_current_user_menu_choices;  /* g2-get-current-user-menu-choices */

/* G2-GET-CURRENT-USER-MENU-CHOICES-SYSTEM-RPC-INTERNAL */
Object g2_get_current_user_menu_choices_system_rpc_internal(gensymed_symbol,
	    item,user_mode)
    Object gensymed_symbol, item, user_mode;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,109);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,
			Qg2_get_current_user_menu_choices,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_get_current_user_menu_choices_internal(item,user_mode);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_get_current_user_menu_choices_for_session;  /* g2-get-current-user-menu-choices-for-session */

/* G2-GET-CURRENT-USER-MENU-CHOICES-FOR-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_get_current_user_menu_choices_for_session_system_rpc_internal(gensymed_symbol,
	    item,session)
    Object gensymed_symbol, item, session;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object user_mode, current_ui_client_session, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(248,110);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  1);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,
			Qg2_get_current_user_menu_choices_for_session,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    user_mode = ISVREF(session,(SI_Long)20L);
	    current_ui_client_session = session;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_ui_client_session,Qcurrent_ui_client_session,current_ui_client_session,
		    0);
	      result = g2_get_current_user_menu_choices_internal(item,
		      user_mode);
	    POP_SPECIAL();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-USER-MENU-CHOICE */
Object g2_get_user_menu_choice(label,applicable_class)
    Object label, applicable_class;
{
    Object class_description, superior_class, ab_loop_list_, ab_loop_it_, umc;
    Object ab_loop_list__1;

    x_note_fn_call(248,111);
    class_description = 
	    lookup_global_or_kb_specific_property_value(applicable_class,
	    Class_description_gkbprop);
    if (class_description) {
	superior_class = Nil;
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	umc = Nil;
	ab_loop_list__1 = lookup_kb_specific_property_value(superior_class,
		User_menu_choices_for_this_class_kbprop);
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	umc = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQ(ISVREF(umc,(SI_Long)20L),label) ? umc : Nil;
	if (ab_loop_it_)
	    goto end_1;
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
    else
	return VALUES_1(Nil);
}

static Object Qg2_get_user_menu_choice;  /* g2-get-user-menu-choice */

/* G2-GET-USER-MENU-CHOICE-SYSTEM-RPC-INTERNAL */
Object g2_get_user_menu_choice_system_rpc_internal(gensymed_symbol,label,
	    applicable_class_qm)
    Object gensymed_symbol, label, applicable_class_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,112);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_get_user_menu_choice,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_get_user_menu_choice(label,applicable_class_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-STRICT-INSTANCES-OF-CLASS */
Object g2_get_strict_instances_of_class(class_name)
    Object class_name;
{
    Object ab_loopvar_, sci, scis, ab_loopvar__1, ab_loopvar__2, top_of_stack;
    Object message_1;

    x_note_fn_call(248,113);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	ab_loopvar_ = lookup_kb_specific_property_value(class_name,
		Instances_specific_to_this_class_kbprop);
	sci = Nil;
	scis = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loopvar_))
	    goto end_loop;
	sci = ab_loopvar_;
	ab_loopvar_ = ISVREF(ab_loopvar_,(SI_Long)6L);
	ab_loopvar__2 = eval_cons_1(sci,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    scis = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	return allocate_evaluation_sequence(scis);
	return VALUES_1(Qnil);
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_1,
		class_name);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* G2-GET-STRICT-INSTANCES-OF-CLASS-SYSTEM-RPC-INTERNAL */
Object g2_get_strict_instances_of_class_system_rpc_internal(gensymed_symbol,
	    class_name)
    Object gensymed_symbol, class_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,114);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_strict_instances_of_class(class_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-DIRECT-SUBCLASSES */
Object g2_get_direct_subclasses(class_name)
    Object class_name;
{
    Object top_of_stack, message_1;

    x_note_fn_call(248,115);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop))
	return allocate_evaluation_sequence(copy_list_using_eval_conses_1(lookup_global_or_kb_specific_property_value(class_name,
		Inferior_classes_gkbprop)));
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_1,
		class_name);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* G2-GET-DIRECT-SUBCLASSES-SYSTEM-RPC-INTERNAL */
Object g2_get_direct_subclasses_system_rpc_internal(gensymed_symbol,class_name)
    Object gensymed_symbol, class_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,116);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_direct_subclasses(class_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-ENABLE-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_enable_item_system_rpc_internal(rpc_instance,item)
    Object rpc_instance, item;
{
    Object ok_qm, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(248,117);
    ok_qm = item && (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)8192L) ? frame_may_be_enabled_or_disabled_p(1,item) : 
	    Qnil;
    if (ok_qm) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)48L),(SI_Long)1L);
	gensymed_symbol_1 = item;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(ok_qm ? 
	    Evaluation_true_value : Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-DISABLE-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_disable_item_system_rpc_internal(rpc_instance,item)
    Object rpc_instance, item;
{
    Object ok_qm, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(248,118);
    ok_qm = item &&  !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)8192L)) ? frame_may_be_enabled_or_disabled_p(1,item) :
	     Qnil;
    if (ok_qm) {
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)47L),(SI_Long)1L);
	gensymed_symbol_1 = item;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(ok_qm ? 
	    Evaluation_true_value : Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-ITEM-IS-DISABLED-SYSTEM-RPC-INTERNAL */
Object g2_item_is_disabled_system_rpc_internal(rpc_instance,item)
    Object rpc_instance, item;
{
    char disabled_qm;

    x_note_fn_call(248,119);
    disabled_qm = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	    (SI_Long)8192L);
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(disabled_qm ? 
	    Evaluation_true_value : Evaluation_false_value,Nil));
    return VALUES_1(Nil);
}

/* G2-CHANGE-MODE-FOR-WINDOW */
Object g2_change_mode_for_window(client_item,new_mode)
    Object client_item, new_mode;
{
    Object error_string_qm;
    Object result;

    x_note_fn_call(248,120);
    result = check_and_install_new_g2_user_mode_for_login(new_mode,
	    client_item);
    error_string_qm = NTH_VALUE((SI_Long)1L, result);
    if ( !TRUEP(error_string_qm))
	return VALUES_1(Evaluation_true_value);
    else {
	reclaim_text_string(error_string_qm);
	return VALUES_1(Evaluation_false_value);
    }
}

static Object Qg2_change_mode_for_window;  /* g2-change-mode-for-window */

/* G2-CHANGE-MODE-FOR-WINDOW-SYSTEM-RPC-INTERNAL */
Object g2_change_mode_for_window_system_rpc_internal(gensymed_symbol,
	    client_item,new_mode)
    Object gensymed_symbol, client_item, new_mode;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,121);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_change_mode_for_window,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_change_mode_for_window(client_item,new_mode);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-LIST-MEMBERSHIPS */
Object g2_get_list_memberships(item)
    Object item;
{
    Object lists, element, ab_loop_list_;

    x_note_fn_call(248,122);
    lists = Nil;
    element = Nil;
    ab_loop_list_ = ISVREF(item,(SI_Long)13L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    lists = eval_cons_1(ISVREF(element,(SI_Long)5L),lists);
    goto next_loop;
  end_loop:
    return allocate_evaluation_sequence(lists);
    return VALUES_1(Qnil);
}

/* G2-GET-LIST-MEMBERSHIPS-SYSTEM-RPC-INTERNAL */
Object g2_get_list_memberships_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,123);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_list_memberships(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-METHODS-DEFINED-FOR-CLASS */
Object g2_get_methods_defined_for_class(class_name)
    Object class_name;
{
    Object methods, method_information, ab_loop_list_, method, ab_loop_list__1;

    x_note_fn_call(248,124);
    methods = Nil;
    method_information = Nil;
    ab_loop_list_ = lookup_kb_specific_property_value(class_name,
	    Procedure_methods_of_class_kbprop);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    method_information = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    method = Nil;
    ab_loop_list__1 = CDR(method_information);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    method = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    methods = eval_cons_1(method,methods);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return allocate_evaluation_sequence(nreverse(methods));
    return VALUES_1(Qnil);
}

/* G2-GET-METHODS-DEFINED-FOR-CLASS-SYSTEM-RPC-INTERNAL */
Object g2_get_methods_defined_for_class_system_rpc_internal(gensymed_symbol,
	    class_name)
    Object gensymed_symbol, class_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,125);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_methods_defined_for_class(class_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-METHODS-OF-NAME */
Object g2_get_methods_of_name(method_name)
    Object method_name;
{
    Object methods_found, classes_of_procedure_method_qm, class_1;
    Object ab_loop_list_, class_methods_qm, ab_loop_desetq_, specific_method;
    Object ab_loop_list__1;

    x_note_fn_call(248,126);
    methods_found = Nil;
    classes_of_procedure_method_qm = SYMBOLP(method_name) ? 
	    lookup_kb_specific_property_value(method_name,
	    Classes_of_procedure_method_kbprop) : Qnil;
    class_1 = Nil;
    ab_loop_list_ = classes_of_procedure_method_qm;
    class_methods_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_methods_qm = get_named_procedure_methods_for_class(method_name,
	    class_1);
    if (class_methods_qm) {
	specific_method = Nil;
	ab_loop_list__1 = CDR(class_methods_qm);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	specific_method = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	methods_found = eval_cons_1(specific_method,methods_found);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return allocate_evaluation_sequence(nreverse(methods_found));
    return VALUES_1(Qnil);
}

/* G2-GET-METHODS-OF-NAME-SYSTEM-RPC-INTERNAL */
Object g2_get_methods_of_name_system_rpc_internal(gensymed_symbol,method_name)
    Object gensymed_symbol, method_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,127);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_methods_of_name(method_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qreset;              /* reset */

static Object Qpaused;             /* paused */

static Object Qrunning;            /* running */

static Object Qg2_set_g2_state;    /* g2-set-g2-state */

/* G2-SET-G2-STATE-SYSTEM-RPC-INTERNAL */
Object g2_set_g2_state_system_rpc_internal(rpc_instance,desired_state)
    Object rpc_instance, desired_state;
{
    x_note_fn_call(248,128);
    if (EQ(desired_state,Qreset)) {
	if ((System_has_paused || System_is_running) &&  
		!TRUEP(Inside_breakpoint_p))
	    system_reset();
    }
    else if (EQ(desired_state,Qpaused)) {
	if (System_is_running)
	    system_pause(0);
    }
    else if (EQ(desired_state,Qrunning)) {
	if (Inside_breakpoint_p)
	    return_from_breakpoint(1,eval_cons_1(Qg2_set_g2_state,
		    rpc_instance));
	else if (System_has_paused)
	    system_resume();
	else if ( !TRUEP(System_is_running))
	    system_start();
    }
    if ( !(EQ(desired_state,Qrunning) && Inside_breakpoint_p))
	return_from_g2_set_g2_state(rpc_instance);
    return VALUES_1(Nil);
}

/* RETURN-FROM-G2-SET-G2-STATE */
Object return_from_g2_set_g2_state(rpc_instance)
    Object rpc_instance;
{
    Object new_state;

    x_note_fn_call(248,129);
    if (System_is_running)
	new_state = Qrunning;
    else if (System_has_paused)
	new_state = Qpaused;
    else
	new_state = Qreset;
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(new_state,Nil));
    return VALUES_1(Nil);
}

/* G2-GET-G2-STATE-SYSTEM-RPC-INTERNAL */
Object g2_get_g2_state_system_rpc_internal(rpc_instance)
    Object rpc_instance;
{
    Object new_state;

    x_note_fn_call(248,130);
    if (System_is_running)
	new_state = Qrunning;
    else if (System_has_paused)
	new_state = Qpaused;
    else
	new_state = Qreset;
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(new_state,Nil));
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* "Invalid G2-Window ~NF" */

static Object Qui_client_session;  /* ui-client-session */

static Object string_constant_8;   /* "G2-FIRE-ACTION-BUTTON called with invalid client ~NF" */

static Object string_constant_9;   /* "G2-FIRE-ACTION-BUTTON called with no client" */

/* NORMALIZE-SPECIFIC-CLIENT */
Object normalize_specific_client(item)
    Object item;
{
    Object sub_class_bit_vector, workstation_for_g2_window_qm;
    Object gensym_window_qm, temp_1, top_of_stack, message_1;
    Object gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,131);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_window_class_description,
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
	workstation_for_g2_window_qm = ISVREF(item,(SI_Long)20L);
	gensym_window_qm = workstation_for_g2_window_qm ? 
		ISVREF(workstation_for_g2_window_qm,(SI_Long)1L) : Qnil;
	temp_1 = gensym_window_qm;
	if (temp_1);
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_7,item);
	    temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qui_client_session,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
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
	if (temp)
	    temp_1 = ui_client_session_valid_p(item) ? item : Qnil;
	else if (item) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_8,item);
	    temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_9,Nil);
	    temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    return VALUES_1(temp_1);
}

/* G2-FIRE-ACTION-BUTTON */
Object g2_fire_action_button(item,specific_client)
    Object item, specific_client;
{
    Object client_item, current_workstation_window, temp, sub_class_bit_vector;
    Object click_result_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,132);
    client_item = normalize_specific_client(specific_client);
    current_workstation_window = System_window;
    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
	    0);
      temp = ISVREF(item,(SI_Long)8L);
      if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(item,
	      (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	      && (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
	      (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(item,
	      (SI_Long)4L)) & (SI_Long)8192L)))) {
	  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
      }
      else
	  temp_1 = TRUEP(Nil);
      click_result_qm = (temp_1 ? TRUEP(System_is_running) : TRUEP(Nil)) ? 
	      fire_action_button(item,client_item) : Nil;
      if (FIXNUMP(click_result_qm) && IFIX(click_result_qm) >= (SI_Long)1L)
	  result = VALUES_1(Evaluation_true_value);
      else
	  result = VALUES_1(Evaluation_false_value);
    POP_SPECIAL();
    return result;
}

static Object Qg2_fire_action_button;  /* g2-fire-action-button */

/* G2-FIRE-ACTION-BUTTON-SYSTEM-RPC-INTERNAL */
Object g2_fire_action_button_system_rpc_internal(gensymed_symbol,
	    action_button,specific_client)
    Object gensymed_symbol, action_button, specific_client;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,133);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_fire_action_button,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    check_ui_client_session_for_rpc_access(specific_client);
	    result = g2_fire_action_button(action_button,specific_client);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-FIRE-USER-MENU-CHOICE */
Object g2_fire_user_menu_choice(user_menu_choice,item,specific_client)
    Object user_menu_choice, item, specific_client;
{
    Object client_item, sub_class_bit_vector, temp_1, rules_scheduled_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,134);
    client_item = normalize_specific_client(specific_client);
    sub_class_bit_vector = ISVREF(ISVREF(user_menu_choice,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(User_menu_choice_class_description,(SI_Long)18L));
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
    if (temp ? TRUEP(System_is_running) : TRUEP(Nil)) {
	temp_1 = ISVREF(user_menu_choice,(SI_Long)8L);
	temp =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != 
		(IFIX(ISVREF(user_menu_choice,(SI_Long)5L)) & (SI_Long)1L) 
		||  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
		(SI_Long)16777216L) &&  !((SI_Long)0L != 
		(IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) & 
		(SI_Long)8192L)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = client_item;
	if (temp_1);
	else
	    temp_1 = System_window;
	rules_scheduled_qm = execute_user_menu_choice(user_menu_choice,
		item,temp_1);
	if (FIXNUMP(rules_scheduled_qm) && IFIX(rules_scheduled_qm) >= 
		(SI_Long)1L)
	    return VALUES_1(Evaluation_true_value);
	else
	    return VALUES_1(Evaluation_false_value);
    }
    else
	return VALUES_1(Evaluation_false_value);
}

static Object Qg2_fire_user_menu_choice;  /* g2-fire-user-menu-choice */

/* G2-FIRE-USER-MENU-CHOICE-SYSTEM-RPC-INTERNAL */
Object g2_fire_user_menu_choice_system_rpc_internal(gensymed_symbol,
	    user_menu_choice,item,specific_client)
    Object gensymed_symbol, user_menu_choice, item, specific_client;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,135);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_fire_user_menu_choice,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    check_ui_client_session_for_rpc_access(specific_client);
	    result = g2_fire_user_menu_choice(user_menu_choice,item,
		    specific_client);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_show_workspace;  /* g2-show-workspace */

static Object Qitem;               /* item */

static Object Qgo_to_item;         /* go-to-item */

static Object Qsymbolic_x_scale;   /* symbolic-x-scale */

static Object Qsymbolic_y_scale;   /* symbolic-y-scale */

static Object Qsymbolic_x_in_workspace;  /* symbolic-x-in-workspace */

static Object Qsymbolic_y_in_workspace;  /* symbolic-y-in-workspace */

static Object Qsymbolic_x_in_window;  /* symbolic-x-in-window */

static Object Qsymbolic_y_in_window;  /* symbolic-y-in-window */

static Object Qx_offset_units;     /* x-offset-units */

static Object Qsymbolic_x_offset_direction;  /* symbolic-x-offset-direction */

static Object Qy_offset_units;     /* y-offset-units */

static Object Qsymbolic_y_offset_direction;  /* symbolic-y-offset-direction */

static Object Qx_magnification;    /* x-magnification */

static Object Qy_magnification;    /* y-magnification */

static Object Qx_in_workspace;     /* x-in-workspace */

static Object Qy_in_workspace;     /* y-in-workspace */

static Object Qx_in_window;        /* x-in-window */

static Object Qy_in_window;        /* y-in-window */

/* G2-SHOW-WORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_show_workspace_system_rpc_internal(gensymed_symbol,workspace,
	    show_details_qm,specific_client)
    Object gensymed_symbol, workspace, show_details_qm, specific_client;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, temp_1, temp_2;
    Object temp_3, temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10;
    Object temp_11, temp_12, temp_13, temp_14, temp_15, temp_16, temp_17;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,136);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
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
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_show_workspace,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    temp_1 = estructure_slot(show_details_qm,Qitem,Nil);
	    if (temp_1);
	    else
		temp_1 = workspace;
	    temp_2 = estructure_slot(show_details_qm,Qgo_to_item,Nil);
	    temp_3 = estructure_slot(show_details_qm,Qsymbolic_x_scale,Nil);
	    temp_4 = estructure_slot(show_details_qm,Qsymbolic_y_scale,Nil);
	    temp_5 = estructure_slot(show_details_qm,
		    Qsymbolic_x_in_workspace,Nil);
	    temp_6 = estructure_slot(show_details_qm,
		    Qsymbolic_y_in_workspace,Nil);
	    temp_7 = estructure_slot(show_details_qm,Qsymbolic_x_in_window,
		    Nil);
	    temp_8 = estructure_slot(show_details_qm,Qsymbolic_y_in_window,
		    Nil);
	    temp_9 = estructure_slot(show_details_qm,Qx_offset_units,Nil);
	    temp_10 = estructure_slot(show_details_qm,
		    Qsymbolic_x_offset_direction,Nil);
	    temp_11 = estructure_slot(show_details_qm,Qy_offset_units,Nil);
	    temp_12 = estructure_slot(show_details_qm,
		    Qsymbolic_y_offset_direction,Nil);
	    temp_13 = estructure_slot(show_details_qm,Qx_magnification,Nil);
	    temp_14 = estructure_slot(show_details_qm,Qy_magnification,Nil);
	    temp_15 = estructure_slot(show_details_qm,Qx_in_workspace,Nil);
	    temp_16 = estructure_slot(show_details_qm,Qy_in_workspace,Nil);
	    temp_17 = estructure_slot(show_details_qm,Qx_in_window,Nil);
	    show_workspace(21,temp_1,specific_client,temp_2,temp_3,temp_4,
		    temp_5,temp_6,temp_7,temp_8,temp_9,temp_10,temp_11,
		    temp_12,temp_13,temp_14,temp_15,temp_16,temp_17,
		    estructure_slot(show_details_qm,Qy_in_window,Nil),T,T);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_hide_workspace;  /* g2-hide-workspace */

/* G2-HIDE-WORKSPACE-SYSTEM-RPC-INTERNAL */
Object g2_hide_workspace_system_rpc_internal(gensymed_symbol,workspace,
	    specific_client)
    Object gensymed_symbol, workspace, specific_client;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, interface_qm, frame, symbol;
    Object sub_class_bit_vector, top_of_stack, message_1, passed_top_of_stack;
    Object error_1, error_text, supress_debugging_info_qm, temp_1;
    Object error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,137);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
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
			temp = (SI_Long)0L < gensymed_symbol_2;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_hide_workspace,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    show_or_hide(5,workspace,Nil,Nil,specific_client,Nil);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* LOOSE-END-CONNECTION-FRAME-P */
Object loose_end_connection_frame_p(connection_frame_1)
    Object connection_frame_1;
{
    Object temp;

    x_note_fn_call(248,138);
    temp = loose_end_connection_p(ISVREF(connection_frame_1,(SI_Long)21L));
    return VALUES_1(temp);
}

/* GET-LOOSE-END-FOR-LOOSE-END-CONNECTION-FRAME */
Object get_loose_end_for_loose_end_connection_frame(connection_frame_1)
    Object connection_frame_1;
{
    Object connection, connection_input, connection_output;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,139);
    connection = ISVREF(connection_frame_1,(SI_Long)21L);
    connection_input = ISVREF(connection,(SI_Long)3L);
    connection_output = ISVREF(connection,(SI_Long)2L);
    sub_class_bit_vector = ISVREF(ISVREF(connection_input,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
    return VALUES_1(temp ? connection_input : connection_output);
}

static Object Qorthogonal;         /* orthogonal */

static Object string_constant_10;  /* "vertex (~NV, ~NV) does not match connection origin" */

static Object string_constant_11;  /* "non-orthogonal vertices specified" */

/* MOVE-LOOSE-END-AND-SET-CONNECTION-VERTICES */
Object move_loose_end_and_set_connection_vertices(loose_end,connection,
	    vertex_list_arg,connection_mode)
    Object loose_end, connection, vertex_list_arg, connection_mode;
{
    Object input, output, block, input_end_position, output_end_position;
    Object vertex_list, block_x, block_y, vertex_list_start_x;
    Object vertex_list_start_y, top_of_stack, message_1, start_x, start_y;
    Object deltas, initial_horizontal_p, prev_x, prev_y, x, y, ab_loop_list_;
    Object horizontal_p, ab_loop_iter_flag_, ab_loop_desetq_, gensymed_symbol;
    Object workspace_qm, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp_1;
    Object result;

    x_note_fn_call(248,140);
    input = ISVREF(connection,(SI_Long)3L);
    output = ISVREF(connection,(SI_Long)2L);
    block = EQ(input,loose_end) ? output : input;
    input_end_position = ISVREF(connection,(SI_Long)5L);
    output_end_position = ISVREF(connection,(SI_Long)4L);
    vertex_list = Nil;
    if (EQ(connection_mode,Qorthogonal)) {
	result = determine_connection_terminal_coordinate(block,EQ(block,
		input) ? input_end_position : output_end_position);
	MVS_2(result,block_x,block_y);
	vertex_list_start_x = CAAR(vertex_list_arg);
	vertex_list_start_y = CDAR(vertex_list_arg);
	if ( !(FIXNUM_EQ(block_x,vertex_list_start_x) && FIXNUM_EQ(block_y,
		vertex_list_start_y))) {
	    reclaim_gensym_tree_1(vertex_list_arg);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_10,vertex_list_start_x,
		    vertex_list_start_y);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if (EQ(block,output))
	    vertex_list = nreverse(vertex_list_arg);
	else
	    vertex_list = vertex_list_arg;
	start_x = CAAR(vertex_list);
	start_y = CDAR(vertex_list);
	deltas = Qnil;
	initial_horizontal_p = EQ(block,input) ? ((SI_Long)1L == 
		(IFIX(input_end_position) & (SI_Long)1L) ? T : Nil) : 
		FIXNUM_EQ(start_y,CDADR(vertex_list)) ? T : Nil;
	prev_x = start_x;
	prev_y = start_y;
	x = Nil;
	y = Nil;
	ab_loop_list_ = CDR(vertex_list);
	horizontal_p = initial_horizontal_p;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	x = CAR(ab_loop_desetq_);
	y = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	if ( !(horizontal_p ? FIXNUM_EQ(prev_y,y) : FIXNUM_EQ(prev_x,x))) {
	    reclaim_gensym_tree_1(vertex_list);
	    reclaim_slot_value_list_1(deltas);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_11);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	deltas = slot_value_cons_1(horizontal_p ? FIXNUM_MINUS(x,prev_x) : 
		FIXNUM_MINUS(y,prev_y),deltas);
	ab_loop_iter_flag_ = Nil;
	prev_x = x;
	prev_y = y;
	goto next_loop;
      end_loop:
	reclaim_gensym_tree_1(vertex_list);
	deltas = nreverse(deltas);
	gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	workspace_qm = gensymed_symbol;
	update_connection_images(T,workspace_qm,connection);
	update_images_of_block(loose_end,T,Nil);
	if (EQ(input,loose_end)) {
	    gensymed_symbol_1 = IFIX(start_x);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(start_y);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    shift_block(loose_end,temp,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    temp_1 = TRUEP(Noting_changes_to_kb_p);
	    if (temp_1);
	    else {
		gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp_1)
		note_change_to_connection_1(connection);
	    svref_new_value = initial_horizontal_p ? (SI_Long)1L : (SI_Long)0L;
	    ISVREF(connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    gensymed_symbol_1 = IFIX(x);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(y);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    shift_block(loose_end,temp,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    temp_1 = TRUEP(Noting_changes_to_kb_p);
	    if (temp_1);
	    else {
		gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp_1)
		note_change_to_connection_1(connection);
	    svref_new_value = horizontal_p ? (SI_Long)1L : (SI_Long)0L;
	    ISVREF(connection,(SI_Long)4L) = FIX(svref_new_value);
	}
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = deltas;
	remove_redundant_deltas_from_connection(connection);
	update_images_of_block(loose_end,Nil,Nil);
	update_connection_images(Nil,workspace_qm,connection);
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else {
	result = determine_connection_terminal_coordinate(block,EQ(block,
		input) ? input_end_position : output_end_position);
	MVS_2(result,block_x,block_y);
	vertex_list_start_x = CAAR(vertex_list_arg);
	vertex_list_start_y = CDAR(vertex_list_arg);
	if ( !(FIXNUM_EQ(block_x,vertex_list_start_x) && FIXNUM_EQ(block_y,
		vertex_list_start_y))) {
	    reclaim_gensym_tree_1(vertex_list_arg);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_10,vertex_list_start_x,
		    vertex_list_start_y);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	if (EQ(block,output))
	    vertex_list = nreverse(vertex_list_arg);
	else
	    vertex_list = vertex_list_arg;
	start_x = CAAR(vertex_list);
	start_y = CDAR(vertex_list);
	deltas = Qnil;
	initial_horizontal_p = EQ(block,input) ? ((SI_Long)1L == 
		(IFIX(input_end_position) & (SI_Long)1L) ? T : Nil) : 
		(SI_Long)1L == (IFIX(output_end_position) & (SI_Long)1L) ? 
		T : Nil;
	prev_x = start_x;
	prev_y = start_y;
	x = Nil;
	y = Nil;
	ab_loop_list_ = CDR(vertex_list);
	horizontal_p = initial_horizontal_p;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	x = CAR(ab_loop_desetq_);
	y = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
	deltas = slot_value_cons_1(initial_horizontal_p ? FIXNUM_MINUS(x,
		prev_x) : FIXNUM_MINUS(y,prev_y),deltas);
	deltas = slot_value_cons_1( !TRUEP(initial_horizontal_p) ? 
		FIXNUM_MINUS(x,prev_x) : FIXNUM_MINUS(y,prev_y),deltas);
	ab_loop_iter_flag_ = Nil;
	prev_x = x;
	prev_y = y;
	goto next_loop_1;
      end_loop_1:
	reclaim_gensym_tree_1(vertex_list);
	deltas = nreverse(deltas);
	gensymed_symbol = ACCESS_ONCE(ISVREF(loose_end,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	workspace_qm = gensymed_symbol;
	update_connection_images(T,workspace_qm,connection);
	update_images_of_block(loose_end,T,Nil);
	if (EQ(input,loose_end)) {
	    gensymed_symbol_1 = IFIX(start_x);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(start_y);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    shift_block(loose_end,temp,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    temp_1 = TRUEP(Noting_changes_to_kb_p);
	    if (temp_1);
	    else {
		gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp_1)
		note_change_to_connection_1(connection);
	    svref_new_value = initial_horizontal_p ? (SI_Long)1L : (SI_Long)0L;
	    ISVREF(connection,(SI_Long)5L) = FIX(svref_new_value);
	}
	else {
	    gensymed_symbol_1 = IFIX(x);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    temp = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    gensymed_symbol_1 = IFIX(y);
	    gensymed_symbol = ISVREF(loose_end,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    shift_block(loose_end,temp,FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2));
	    temp_1 = TRUEP(Noting_changes_to_kb_p);
	    if (temp_1);
	    else {
		gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
			(SI_Long)128L;
		temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
			!TRUEP(Geometric_change_to_connection_is_temporary_p) 
			: TRUEP(Nil);
	    }
	    if (temp_1)
		note_change_to_connection_1(connection);
	    svref_new_value = horizontal_p ? (SI_Long)1L : (SI_Long)0L;
	    ISVREF(connection,(SI_Long)4L) = FIX(svref_new_value);
	}
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol_1 = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol_1) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = deltas;
	remove_redundant_deltas_from_connection(connection);
	update_images_of_block(loose_end,Nil,Nil);
	update_connection_images(Nil,workspace_qm,connection);
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

/* DECODE-CONNECTION-POSITION-SEQUENCE */
Object decode_connection_position_sequence(sequence)
    Object sequence;
{
    Object x, res, gensymed_symbol, held_vector, coordinate, horizontal_p;
    Object ab_loop_iter_flag_, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(248,141);
    x = FIX((SI_Long)0L);
    res = Qnil;
    gensymed_symbol = sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    coordinate = Nil;
    horizontal_p = T;
    ab_loop_iter_flag_ = T;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    coordinate = validated_elt;
    if ( !TRUEP(ab_loop_iter_flag_))
	horizontal_p =  !TRUEP(horizontal_p) ? T : Nil;
    if (horizontal_p)
	x = coordinate;
    else
	res = gensym_cons_1(gensym_cons_1(x,FIXNUM_NEGATE(coordinate)),res);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    temp = nreverse(res);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object string_constant_12;  /* "must supply window/ui-client-interface" */

static Object Qconnection_style;   /* connection-style */

static Object Qmoving_loose_end;   /* moving-loose-end */

static Object string_constant_13;  /* "~NV must be an item" */

static Object string_constant_14;  /* "~NF is not a loose-end connection" */

static Object Qjoining_loose_ends;  /* joining-loose-ends */

static Object Qjoined_connections;  /* joined-connections */

static Object string_constant_15;  /* "other item ~NF must be a loose end for ~A" */

static Object string_constant_16;  /* "Incompatible directions or cross-sections joining ~NF to ~NF" */

static Object Qdragging_loose_end_into_item;  /* dragging-loose-end-into-item */

static Object Qadded_connection_to_block;  /* added-connection-to-block */

static Object string_constant_17;  /* "~NF is not an item that accepts connections" */

static Object Qmaking_new_junction_block;  /* making-new-junction-block */

static Object Qmade_junction;      /* made-junction */

static Object string_constant_18;  /* "~NF is not a connection" */

static Object string_constant_19;  /* "unknown mode ~A" */

static Object Qmoved_loose_end;    /* moved-loose-end */

static Object Qdeleted_stub;       /* deleted-stub */

/* G2-MAKE-CONNECTION-FOR-USER */
Object g2_make_connection_for_user(loose_end_connection,other_item,mode_ev,
	    connection_position_sequence,specific_client_or_false)
    Object loose_end_connection, other_item, mode_ev;
    Object connection_position_sequence, specific_client_or_false;
{
    Object connection, x2, gensymed_symbol, sub_class_bit_vector;
    Object specific_client_qm, top_of_stack, message_1, connection_style;
    Object temp_1, mode, loose_end, vertex_list, end_dragging_p;
    Object connection_type, connection_was_not_made_p, joined_connection;
    Object original_x_position, original_y_position, other_loose_end;
    Object other_connection;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Object result;

    x_note_fn_call(248,142);
    connection = ISVREF(loose_end_connection,(SI_Long)21L);
    if (SIMPLE_VECTOR_P(specific_client_or_false) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(specific_client_or_false)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(specific_client_or_false,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(specific_client_or_false,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
	specific_client_qm = specific_client_or_false;
    else if (Current_system_rpc_icp_socket_qm)
	specific_client_qm = ISVREF(Current_system_rpc_icp_socket_qm,
		(SI_Long)5L);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_12);
	specific_client_qm = raw_stack_error_named_error(top_of_stack,
		message_1);
    }
    connection_style = get_lookup_slot_value(loose_end_connection,
	    Qconnection_style);
    temp_1 = mode_ev;
    mode = temp_1;
    loose_end = Nil;
    vertex_list = Nil;
    end_dragging_p = Nil;
    connection_type = Nil;
    connection_was_not_made_p = Nil;
    joined_connection = Nil;
    original_x_position = Nil;
    original_y_position = Nil;
    if ( !EQ(mode,Qmoving_loose_end)) {
	if (SIMPLE_VECTOR_P(other_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(other_item)) > (SI_Long)2L 
		&&  !EQ(ISVREF(other_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(other_item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_13);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (loose_end_connection_frame_p(loose_end_connection)) {
	loose_end = 
		get_loose_end_for_loose_end_connection_frame(loose_end_connection);
	vertex_list = 
		decode_connection_position_sequence(connection_position_sequence);
	original_x_position = item_x_position(loose_end);
	original_y_position = item_y_position(loose_end);
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_14,
		loose_end_connection);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (EQ(mode,Qjoining_loose_ends)) {
	connection_type = Qjoined_connections;
	if ( !TRUEP(loose_end_connection_frame_p(other_item))) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_15,other_item,mode);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	move_loose_end_and_set_connection_vertices(loose_end,connection,
		vertex_list,connection_style);
	other_loose_end = 
		get_loose_end_for_loose_end_connection_frame(other_item);
	result = join_two_connections(loose_end,other_loose_end);
	MVS_2(result,end_dragging_p,joined_connection);
	if ( !TRUEP(end_dragging_p)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_16,loose_end_connection,other_item);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    else if (EQ(mode,Qdragging_loose_end_into_item)) {
	connection_type = Qadded_connection_to_block;
	sub_class_bit_vector = ISVREF(ISVREF(other_item,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	    sub_class_bit_vector = ISVREF(ISVREF(other_item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	if (temp);
	else
	    temp = TRUEP(no_manual_connections_p(other_item));
	if (temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_17,other_item);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	move_loose_end_and_set_connection_vertices(loose_end,connection,
		vertex_list,connection_style);
	result = add_new_connection_to_block(2,loose_end,other_item);
	MVS_2(result,end_dragging_p,connection_was_not_made_p);
	if (G2_has_v5_mode_windows_p &&  !TRUEP(connection_was_not_made_p))
	    send_ws_representations_connection_moved(connection);
    }
    else if (EQ(mode,Qmaking_new_junction_block)) {
	connection_type = Qmade_junction;
	sub_class_bit_vector = ISVREF(ISVREF(other_item,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_18,other_item);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	move_loose_end_and_set_connection_vertices(loose_end,connection,
		vertex_list,connection_style);
	other_connection = ISVREF(other_item,(SI_Long)21L);
	end_dragging_p = make_junction(other_connection,loose_end);
	if (G2_has_v5_mode_windows_p) {
	    send_ws_representations_connection_moved(connection);
	    send_ws_representations_connection_moved(other_connection);
	}
    }
    else if (EQ(mode,Qmoving_loose_end)) {
	connection_was_not_made_p = T;
	move_loose_end_and_set_connection_vertices(loose_end,connection,
		vertex_list,connection_style);
	if (G2_has_v5_mode_windows_p)
	    send_ws_representations_connection_moved(connection);
    }
    else {
	reclaim_gensym_tree_1(vertex_list);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_19,mode);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (connection_was_not_made_p)
	connection_type = EQ(mode,Qmoving_loose_end) ? Qmoved_loose_end : 
		Qdeleted_stub;
    if (end_dragging_p) {
	invoke_connection_handler_if_any(connection_was_not_made_p ? 
		other_item : connection,specific_client_qm,connection_type,
		 !TRUEP(connection_was_not_made_p) && EQ(connection_type,
		Qadded_connection_to_block) ? other_item : Qnil);
	if ( !TRUEP(connection_was_not_made_p)) {
	    if (EQ(connection_type,Qadded_connection_to_block)) {
		invoke_rules_for_direct_connection_chaining(connection,Nil);
		return invoke_rules_for_indirect_connection_chaining(connection,
			Nil);
	    }
	    else if (EQ(connection_type,Qjoined_connections)) {
		invoke_rules_for_direct_connection_chaining(joined_connection,
			Nil);
		return invoke_rules_for_indirect_connection_chaining(joined_connection,
			Nil);
	    }
	    else if (EQ(connection_type,Qmade_junction))
		return invoke_rules_for_indirect_connection_chaining(connection,
			Nil);
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-MAKE-CONNECTION-FOR-USER-SYSTEM-RPC-INTERNAL */
Object g2_make_connection_for_user_system_rpc_internal(gensymed_symbol,
	    loose_end_connection,other_item,mode,position_sequence,
	    specific_client_or_false)
    Object gensymed_symbol, loose_end_connection, other_item, mode;
    Object position_sequence, specific_client_or_false;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,143);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = 
		    g2_make_connection_for_user(loose_end_connection,
		    other_item,mode,position_sequence,
		    specific_client_or_false);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-CONNECTION-INPUT-AND-OUTPUT-SYSTEM-RPC-INTERNAL */
Object g2_get_connection_input_and_output_system_rpc_internal(gensymed_symbol,
	    connection)
    Object gensymed_symbol, connection;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, input, output;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,144);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_connection_input_and_output(connection);
	    MVS_2(result,input,output);
	    result = allocate_evaluation_sequence(eval_list_2(input,output));
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qwindow;             /* window */

static Object Qpopup;              /* popup */

static Object Qradio;              /* radio */

/* G2-CONFIRM-AVAILABLE-HANDLES-BY-TYPE-SYSTEM-RPC-INTERNAL */
Object g2_confirm_available_handles_by_type_system_rpc_internal(rpc_instance,
	    type)
    Object rpc_instance, type;
{
    Object code, value;

    x_note_fn_call(248,145);
    if (EQ(type,Qwindow)) {
	code = M_CAR(M_CDR(Index_of_open_windows));
	value = FIXNUMP(code) && (IFIX(code) & (SI_Long)8192L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_jl_semantics_graph)) : Nil;
    }
    else if (EQ(type,Qpopup)) {
	code = M_CAR(M_CDR(Popup_frames_available));
	value = FIXNUMP(code) && (IFIX(code) & (SI_Long)16384L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_jp_semantics_graph)) : Nil;
    }
    else if (EQ(type,Qradio)) {
	code = M_CAR(M_CDR(Radio_button_status_flags));
	value = FIXNUMP(code) && (IFIX(code) & (SI_Long)32768L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_al_semantics_graph)) : Nil;
    }
    else
	value = Nil;
    if ( !TRUEP(value))
	value = FIX((SI_Long)0L);
    return_from_system_defined_rpc(rpc_instance,eval_cons_1(value,Nil));
    return VALUES_1(Nil);
}

/* ITEM-HAS-REMOTE-REPRESENTATION-P */
Object item_has_remote_representation_p(item,representation_class_name)
    Object item, representation_class_name;
{
    Object representation, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(248,146);
    representation = Nil;
    ab_loop_list_ = ISVREF(item,(SI_Long)9L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(representation_class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(representation,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
    if (temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	temp_1 = representation;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

/* MAKE-NESTED-EVALUATION-VALUE-BASED-ON-TYPE */
Object make_nested_evaluation_value_based_on_type(tree)
    Object tree;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float, gensymed_symbol, element, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, list_of_sequences;
    double aref_new_value;

    x_note_fn_call(248,147);
    if ( !LISTP(tree)) {
	if (FIXNUMP(tree))
	    temp = tree;
	else if ( !TRUEP(tree))
	    temp = Evaluation_false_value;
	else if (EQ(tree,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(tree))
	    temp = tree;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tree) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree)) == (SI_Long)1L)
	    temp = copy_managed_float(tree);
	else if (FLOATP(tree)) {
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(tree);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(tree) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree)) == (SI_Long)1L)
	    temp = copy_managed_long(tree);
	else if (INLINE_LONG_P(tree) != (SI_Long)0L)
	    temp = make_evaluation_long(tree);
	else if (text_string_p(tree))
	    temp = copy_as_wide_string(tree);
	else if (CONSP(tree) && EQ(M_CDR(tree),Qtruth_value)) {
	    gensymed_symbol = M_CAR(tree);
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
		    type_of(tree));
    }
    else {
	element = Nil;
	ab_loop_list_ = tree;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		eval_cons_1(make_nested_evaluation_value_based_on_type(element),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	list_of_sequences = ab_loopvar_;
	goto end_1;
	list_of_sequences = Qnil;
      end_1:;
	temp = allocate_evaluation_sequence(list_of_sequences);
    }
    return VALUES_1(temp);
}

static Object Qtc_representation;  /* tc-representation */

static Object Qgeneral_update;     /* general-update */

/* SEND-NEW-TREND-CHART-DATA */
Object send_new_trend_chart_data(trend_chart,trend_chart_data)
    Object trend_chart, trend_chart_data;
{
    Object body_evaluated_p, notification_body, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object address, subscription_handle, socket_1, argument_list;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(248,148);
    body_evaluated_p = Nil;
    notification_body = Nil;
    frame_list = ISVREF(trend_chart,(SI_Long)9L);
    class_name = Qtc_representation;
    new_list = Qnil;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	new_list = gensym_cons_1(frame,new_list);
    goto next_loop;
  end_loop:
    representations = new_list;
    goto end_1;
    representations = Qnil;
  end_1:;
    current_frame_serial_number_on_entry = 
	    copy_frame_serial_number(Current_frame_serial_number);
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(current_frame_serial_number_on_entry))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(current_frame_serial_number_on_entry,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(current_frame_serial_number_on_entry);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	if ( !TRUEP(body_evaluated_p)) {
	    notification_body = trend_chart_data;
	    body_evaluated_p = T;
	}
	address = ISVREF(representation,(SI_Long)8L);
	subscription_handle = ISVREF(representation,(SI_Long)12L);
	socket_1 = getf(address,Qsocket,_);
	argument_list = eval_list_4(subscription_handle,trend_chart,
		Qgeneral_update,FIXNUMP(notification_body) || 
		notification_body && SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body) ? notification_body : 
		copy_if_evaluation_value_1(notification_body));
	callback_representation_fire_callback(representation,socket_1,
		argument_list);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(current_frame_serial_number_on_entry);
    reclaim_gensym_list_1(representations);
    if (body_evaluated_p) {
	if ( !(FIXNUMP(notification_body) || SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body)))
	    reclaim_if_evaluation_value_1(notification_body);
    }
    return VALUES_1(body_evaluated_p);
    return VALUES_1(Qnil);
}

static Object Qactivation_value;   /* activation-value */

static Object Qactivation;         /* activation */

/* SEND-TREND-CHART-ACTIVATION-DEACTIVATION */
Object send_trend_chart_activation_deactivation(trend_chart,is_activation)
    Object trend_chart, is_activation;
{
    Object body_evaluated_p, notification_body, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object temp_1, item_or_value, x2, svref_new_value, address;
    Object subscription_handle, socket_1, argument_list;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;

    x_note_fn_call(248,149);
    body_evaluated_p = Nil;
    notification_body = Nil;
    frame_list = ISVREF(trend_chart,(SI_Long)9L);
    class_name = Qtc_representation;
    new_list = Qnil;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	new_list = gensym_cons_1(frame,new_list);
    goto next_loop;
  end_loop:
    representations = new_list;
    goto end_1;
    representations = Qnil;
  end_1:;
    current_frame_serial_number_on_entry = 
	    copy_frame_serial_number(Current_frame_serial_number);
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(current_frame_serial_number_on_entry))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(current_frame_serial_number_on_entry,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(current_frame_serial_number_on_entry);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	if ( !TRUEP(body_evaluated_p)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qactivation_value;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qactivation_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = is_activation ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = is_activation ? Evaluation_true_value : 
			Evaluation_false_value;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		svref_new_value = temp ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    notification_body = eval_cons_1(gensymed_symbol,Qab_structure);
	    body_evaluated_p = T;
	}
	address = ISVREF(representation,(SI_Long)8L);
	subscription_handle = ISVREF(representation,(SI_Long)12L);
	socket_1 = getf(address,Qsocket,_);
	argument_list = eval_list_4(subscription_handle,trend_chart,
		Qactivation,FIXNUMP(notification_body) || 
		notification_body && SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body) ? notification_body : 
		copy_if_evaluation_value_1(notification_body));
	callback_representation_fire_callback(representation,socket_1,
		argument_list);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(current_frame_serial_number_on_entry);
    reclaim_gensym_list_1(representations);
    if (body_evaluated_p) {
	if ( !(FIXNUMP(notification_body) || SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body)))
	    reclaim_if_evaluation_value_1(notification_body);
    }
    return VALUES_1(body_evaluated_p);
    return VALUES_1(Qnil);
}

static Object Qtimespan_info;      /* timespan-info */

static Object Qinitial_plot_data;  /* initial-plot-data */

static Object Qtime_delta;         /* time-delta */

static Object Qclock_discontinuity;  /* clock-discontinuity */

/* SEND-TREND-CHART-UPDATE-FOR-CLOCK-DISCONTINUITY */
Object send_trend_chart_update_for_clock_discontinuity(trend_chart,delta)
    Object trend_chart, delta;
{
    Object body_evaluated_p, notification_body, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object temp_1, item_or_value, x2, temp_2, amf_available_array_cons_qm;
    Object amf_array, amf_result, new_float, gensymed_symbol_4, temp_3;
    Object address, subscription_handle, socket_1, argument_list;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;
    double aref_new_value;

    x_note_fn_call(248,150);
    body_evaluated_p = Nil;
    notification_body = Nil;
    frame_list = ISVREF(trend_chart,(SI_Long)9L);
    class_name = Qtc_representation;
    new_list = Qnil;
    frame = Nil;
    ab_loop_list_ = frame_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	new_list = gensym_cons_1(frame,new_list);
    goto next_loop;
  end_loop:
    representations = new_list;
    goto end_1;
    representations = Qnil;
  end_1:;
    current_frame_serial_number_on_entry = 
	    copy_frame_serial_number(Current_frame_serial_number);
    representation = Nil;
    ab_loop_list_ = representations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    representation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(representation,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(current_frame_serial_number_on_entry))
	temp = FIXNUMP(gensymed_symbol) ? 
		FIXNUM_LT(current_frame_serial_number_on_entry,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(current_frame_serial_number_on_entry);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp ? TRUEP(representation_address_valid_p(representation)) : 
	    TRUEP(Nil)) {
	if ( !TRUEP(body_evaluated_p)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtimespan_info;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qtimespan_info;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = collect_time_bounds(trend_chart,Nil,T);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = collect_time_bounds(trend_chart,Nil,T);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_2 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qinitial_plot_data;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qinitial_plot_data;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = get_current_plot_data(trend_chart,Nil,T);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = get_current_plot_data(trend_chart,Nil,T);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_2 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtime_delta;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)5L)) = Qtime_delta;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		if (FIXNUMP(delta))
		    item_or_value = delta;
		else if ( !TRUEP(delta))
		    item_or_value = Evaluation_false_value;
		else if (EQ(delta,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(delta))
		    item_or_value = delta;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(delta) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(delta)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(delta);
		else if (FLOATP(delta)) {
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(delta);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(delta) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(delta)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(delta);
		else if (INLINE_LONG_P(delta) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(delta);
		else if (text_string_p(delta))
		    item_or_value = copy_as_wide_string(delta);
		else if (CONSP(delta) && EQ(M_CDR(delta),Qtruth_value)) {
		    gensymed_symbol_4 = M_CAR(delta);
		    if (FIXNUM_EQ(gensymed_symbol_4,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_4,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_4,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(delta));
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		if (FIXNUMP(delta))
		    item_or_value = delta;
		else if ( !TRUEP(delta))
		    item_or_value = Evaluation_false_value;
		else if (EQ(delta,T))
		    item_or_value = Evaluation_true_value;
		else if (SYMBOLP(delta))
		    item_or_value = delta;
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(delta) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(delta)) == (SI_Long)1L)
		    item_or_value = copy_managed_float(delta);
		else if (FLOATP(delta)) {
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
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(delta);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    item_or_value = new_float;
		}
		else if (INLINE_LONG_VECTOR_P(delta) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(delta)) == (SI_Long)1L)
		    item_or_value = copy_managed_long(delta);
		else if (INLINE_LONG_P(delta) != (SI_Long)0L)
		    item_or_value = make_evaluation_long(delta);
		else if (text_string_p(delta))
		    item_or_value = copy_as_wide_string(delta);
		else if (CONSP(delta) && EQ(M_CDR(delta),Qtruth_value)) {
		    gensymed_symbol_4 = M_CAR(delta);
		    if (FIXNUM_EQ(gensymed_symbol_4,Truth))
			item_or_value = Evaluation_true_value;
		    else if (FIXNUM_EQ(gensymed_symbol_4,Falsity))
			item_or_value = Evaluation_false_value;
		    else
			item_or_value = eval_cons_1(gensymed_symbol_4,
				Qtruth_value);
		}
		else
		    item_or_value = error((SI_Long)2L,
			    "Bad type ~a for make-evaluation-value-based-on-type.",
			    type_of(delta));
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_2 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(temp_1,FIX((SI_Long)6L)) = temp_2;
	    }
	    notification_body = eval_cons_1(gensymed_symbol,Qab_structure);
	    body_evaluated_p = T;
	}
	address = ISVREF(representation,(SI_Long)8L);
	subscription_handle = ISVREF(representation,(SI_Long)12L);
	socket_1 = getf(address,Qsocket,_);
	argument_list = eval_list_4(subscription_handle,trend_chart,
		Qclock_discontinuity,FIXNUMP(notification_body) || 
		notification_body && SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body) ? notification_body : 
		copy_if_evaluation_value_1(notification_body));
	callback_representation_fire_callback(representation,socket_1,
		argument_list);
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_frame_serial_number(current_frame_serial_number_on_entry);
    reclaim_gensym_list_1(representations);
    if (body_evaluated_p) {
	if ( !(FIXNUMP(notification_body) || SYMBOLP(notification_body) || 
		SIMPLE_VECTOR_P(notification_body)))
	    reclaim_if_evaluation_value_1(notification_body);
    }
    return VALUES_1(body_evaluated_p);
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

static Object Qitem_icon_variables_change;  /* item-icon-variables-change */

/* SEND-WS-REPRESENTATIONS-ITEM-ICON-VARIABLES-CHANGE */
Object send_ws_representations_item_icon_variables_change(item,new_variables)
    Object item, new_variables;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,151);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(item) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L &&  
		  !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(item,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(item,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(item);
	  }
	  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(item);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				send_versioned_ws_notification_internal(Qitem_icon_variables_change,
					item,FIXNUMP(new_variables) || 
					new_variables && 
					SYMBOLP(new_variables) || 
					SIMPLE_VECTOR_P(new_variables) ? 
					new_variables : 
					copy_if_evaluation_value_1(new_variables));
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qpath;               /* path */

static Object Qx_offset;           /* x-offset */

static Object Qy_offset;           /* y-offset */

static Object Qinterval;           /* interval */

static Object Qid;                 /* id */

static Object Qreturn_rpc_name;    /* return-rpc-name */

static Object Qitem_move;          /* item-move */

/* SEND-WS-REPRESENTATIONS-ITEM-MOVED-INTERNAL */
Object send_ws_representations_item_moved_internal(item,path_qm,x_offset,
	    y_offset,interval_qm,return_rpc_name_qm,id_qm)
    Object item, path_qm, x_offset, y_offset, interval_qm, return_rpc_name_qm;
    Object id_qm;
{
    Object bounds, gensymed_symbol, svref_arg_1, gensymed_symbol_2;
    Object gensymed_symbol_3, item_or_value, x2, gensymed_symbol_4, temp_1;
    SI_Long gensymed_symbol_1, svref_arg_2, gensymed_symbol_5, ab_loop_bind_;
    SI_Long value_index;
    char temp;

    x_note_fn_call(248,152);
    bounds = get_bounds_of_thing(item);
    if (bounds);
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)0L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
		    - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX((SI_Long)1L);
	}
	bounds = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    if (path_qm) {
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qpath;
	item_or_value = FIXNUMP(path_qm) || path_qm && SYMBOLP(path_qm) || 
		SIMPLE_VECTOR_P(path_qm) ? path_qm : 
		copy_if_evaluation_value_1(path_qm);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_1;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_1;
      end_1:;
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qx_offset;
	item_or_value = FIXNUMP(x_offset) || x_offset && SYMBOLP(x_offset) 
		|| SIMPLE_VECTOR_P(x_offset) ? x_offset : 
		copy_if_evaluation_value_1(x_offset);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop_1;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_2;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop_1;
      end_loop_1:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_2;
      end_2:;
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qy_offset;
	item_or_value = FIXNUMP(y_offset) || y_offset && SYMBOLP(y_offset) 
		|| SIMPLE_VECTOR_P(y_offset) ? y_offset : 
		copy_if_evaluation_value_1(y_offset);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_2:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop_2;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_3;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop_2;
      end_loop_2:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_3;
      end_3:;
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qinterval;
	item_or_value = FIXNUMP(interval_qm) || interval_qm && 
		SYMBOLP(interval_qm) || SIMPLE_VECTOR_P(interval_qm) ? 
		interval_qm : copy_if_evaluation_value_1(interval_qm);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_3:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop_3;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_4;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop_3;
      end_loop_3:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_4;
      end_4:;
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qid;
	item_or_value = FIXNUMP(id_qm) || id_qm && SYMBOLP(id_qm) || 
		SIMPLE_VECTOR_P(id_qm) ? id_qm : 
		copy_if_evaluation_value_1(id_qm);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_4:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop_4;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_5;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop_4;
      end_loop_4:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_5;
      end_5:;
	gensymed_symbol = bounds;
	gensymed_symbol_2 = M_CAR(gensymed_symbol);
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)1L));
	gensymed_symbol_3 = Qreturn_rpc_name;
	item_or_value = return_rpc_name_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	gensymed_symbol_4 = temp ? get_reference_to_item(item_or_value) : 
		item_or_value;
	gensymed_symbol_5 = (SI_Long)1L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_5:
	if (gensymed_symbol_5 >= ab_loop_bind_)
	    goto end_loop_5;
	if (EQ(FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(gensymed_symbol_2,
		gensymed_symbol_5 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol_2,(gensymed_symbol_5 >>  -  
		- (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_5 & 
		(SI_Long)1023L),gensymed_symbol_3)) {
	    value_index = gensymed_symbol_5 + (SI_Long)1L;
	    reclaim_if_evaluation_value_function(FIXNUM_LE(ISVREF(gensymed_symbol_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(gensymed_symbol_2,value_index + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(gensymed_symbol_2,(value_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),value_index & 
		    (SI_Long)1023L));
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = value_index + IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	    }
	    else {
		svref_arg_1 = ISVREF(gensymed_symbol_2,(value_index >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = value_index & (SI_Long)1023L;
		ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	    }
	    goto end_6;
	}
	gensymed_symbol_5 = gensymed_symbol_5 + (SI_Long)2L;
	goto next_loop_5;
      end_loop_5:
	gensymed_symbol_2 = adjust_managed_array(2,gensymed_symbol_2,
		FIX(gensymed_symbol_1 + (SI_Long)2L));
	M_CAR(gensymed_symbol) = gensymed_symbol_2;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_3;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_3;
	}
	gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)1L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = gensymed_symbol_4;
	}
	else {
	    svref_arg_1 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(svref_arg_1,svref_arg_2) = gensymed_symbol_4;
	}
	goto end_6;
      end_6:;
    }
    temp_1 = send_versioned_ws_notification_internal(Qitem_move,item,bounds);
    return VALUES_1(temp_1);
}

/* SEND-WS-REPRESENTATIONS-ITEM-MOVED-AUX */
Object send_ws_representations_item_moved_aux(item,path_qm,x_offset,
	    y_offset,interval_qm,return_rpc_name_qm,id_qm)
    Object item, path_qm, x_offset, y_offset, interval_qm, return_rpc_name_qm;
    Object id_qm;
{
    Object connections, connection, ab_loop_list_, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock, x_offset_sub;
    Object y_offset_sub, sub_class_bit_vector;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    char temp;

    x_note_fn_call(248,153);
    send_ws_representations_item_moved_internal(item,path_qm,x_offset,
	    y_offset,interval_qm,return_rpc_name_qm,id_qm);
    connections = connections_moved_for_blocks_moved(item);
    connection = Nil;
    ab_loop_list_ = connections;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !SYMBOLP(connection))
	send_ws_representations_connection_moved_internal(connection,Nil,
		Nil,Nil,Nil);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(connections);
    if ( !TRUEP(Ws_protocol_handle_moves_from_edge_change_p)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	x_offset_sub = Nil;
	y_offset_sub = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (path_qm) {
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    x_offset_sub = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    x_offset_sub = FIX((SI_Long)0L);
	if (path_qm) {
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(item,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol_2 = (SI_Long)1L;
	    gensymed_symbol_1 = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = gensymed_symbol_2 + gensymed_symbol_3;
	    gensymed_symbol_3 = (SI_Long)1L;
	    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
	    y_offset_sub = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	}
	else
	    y_offset_sub = FIX((SI_Long)0L);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
	if (temp)
	    send_ws_representations_item_moved_aux(subblock,path_qm,
		    FIXNUM_ADD(x_offset,x_offset_sub),FIXNUM_ADD(y_offset,
		    y_offset_sub),interval_qm,Nil,Nil);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* SEND-WS-REPRESENTATIONS-ITEM-MOVED */
Object send_ws_representations_item_moved(item,delta_x,delta_y)
    Object item, delta_x, delta_y;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,154);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(item) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L &&  
		  !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(item,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(item,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(item);
	  }
	  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(item);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				send_ws_representations_item_moved_aux(item,
					Nil,FIX((SI_Long)0L),
					FIX((SI_Long)0L),Nil,Nil,Nil);
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qtw_workspace_item_position;  /* tw-workspace-item-position */

/* SEND-WS-REPRESENTATIONS-CONNECTION-MOVED-INTERNAL */
Object send_ws_representations_connection_moved_internal(connection,
	    path_qm,interval_qm,return_rpc_name_qm,id_qm)
    Object connection, path_qm, interval_qm, return_rpc_name_qm, id_qm;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    Object temp_3;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(248,155);
    temp = SIMPLE_VECTOR_P(connection) && EQ(ISVREF(connection,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct) ? 
	    get_or_make_connection_frame_and_activate_if_appropriate(connection) 
	    : connection;
    if (path_qm) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
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
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		    Qtw_workspace_item_position;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtw_workspace_item_position;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = get_position_of_thing(connection);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = get_position_of_thing(connection);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qpath;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Qpath;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = FIXNUMP(path_qm) || path_qm && 
		    SYMBOLP(path_qm) || SIMPLE_VECTOR_P(path_qm) ? path_qm 
		    : copy_if_evaluation_value_1(path_qm);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = FIXNUMP(path_qm) || path_qm && 
		    SYMBOLP(path_qm) || SIMPLE_VECTOR_P(path_qm) ? path_qm 
		    : copy_if_evaluation_value_1(path_qm);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qinterval;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qinterval;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = FIXNUMP(interval_qm) || interval_qm && 
		    SYMBOLP(interval_qm) || SIMPLE_VECTOR_P(interval_qm) ? 
		    interval_qm : copy_if_evaluation_value_1(interval_qm);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = FIXNUMP(interval_qm) || interval_qm && 
		    SYMBOLP(interval_qm) || SIMPLE_VECTOR_P(interval_qm) ? 
		    interval_qm : copy_if_evaluation_value_1(interval_qm);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qid;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)7L)) = Qid;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = id_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = id_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)8L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qreturn_rpc_name;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)9L)) = Qreturn_rpc_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = return_rpc_name_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = return_rpc_name_qm;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)10L)) = svref_new_value;
	}
	temp_3 = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
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
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		    Qtw_workspace_item_position;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qtw_workspace_item_position;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = get_position_of_thing(connection);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = get_position_of_thing(connection);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	temp_3 = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    temp_3 = send_versioned_ws_notification_internal(Qitem_move,temp,temp_3);
    return VALUES_1(temp_3);
}

/* SEND-WS-REPRESENTATIONS-CONNECTION-MOVED */
Object send_ws_representations_connection_moved(connection)
    Object connection;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,156);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(connection) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(connection,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(connection,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(connection,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(connection);
	  }
	  else if (SIMPLE_VECTOR_P(connection) && EQ(ISVREF(connection,
		  (SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(connection);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(connection) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(connection,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(connection,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(connection);
	      }
	      else if (SIMPLE_VECTOR_P(connection) && EQ(ISVREF(connection,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(connection);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(connection) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(connection,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(connection,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(connection,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(connection,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(connection);
	      }
	      else if (SIMPLE_VECTOR_P(connection) && EQ(ISVREF(connection,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(connection);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				send_ws_representations_connection_moved_internal(connection,
					Nil,Nil,Nil,Nil);
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qitem_resize;        /* item-resize */

/* SEND-WS-REPRESENTATIONS-ITEM-RESIZED */
Object send_ws_representations_item_resized(item,new_left,new_top,
	    new_right,new_bottom)
    Object item, new_left, new_top, new_right, new_bottom;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_2, item_or_value;
    Object svref_new_value, arg_lists, arg_list, ab_loop_list__1;
    Object arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,157);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(item) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L &&  
		  !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(item,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(item,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(item);
	  }
	  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(item);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				gensymed_symbol_3 = 
					allocate_managed_array(1,
					FIX((SI_Long)8L + (SI_Long)1L));
				gensymed_symbol = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol_3,svref_arg_2) 
					    = FIX((SI_Long)1L);
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (gensymed_symbol >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol & 
					    (SI_Long)1023L;
				    ISVREF(temp_2,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)3L)) = Qleft;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)1L)) = Qleft;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = new_left;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)4L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = new_left;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)2L)) = 
					    svref_new_value;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)5L)) = Qtop;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)3L)) = Qtop;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = FIXNUM_NEGATE(new_top);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)6L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = FIXNUM_NEGATE(new_top);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)4L)) = 
					    svref_new_value;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)7L)) = Qright;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)5L)) = Qright;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = new_right;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)8L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = new_right;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)6L)) = 
					    svref_new_value;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)9L)) = Qbottom;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)7L)) = Qbottom;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = FIXNUM_NEGATE(new_bottom);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)10L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = FIXNUM_NEGATE(new_bottom);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)8L)) = 
					    svref_new_value;
				}
				send_versioned_ws_notification_internal(Qitem_resize,
					item,eval_cons_1(gensymed_symbol_3,
					Qab_structure));
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qnew_rotation;       /* new-rotation */

static Object Qnormal;             /* normal */

static Object Qitem_rotate;        /* item-rotate */

/* SEND-WS-REPRESENTATIONS-ITEM-ROTATED */
Object send_ws_representations_item_rotated(item,new_rotation)
    Object item, new_rotation;
{
    Object sub_class_bit_vector, notification_data_version_map, x2;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_2, item_or_value;
    Object svref_new_value, arg_lists, arg_list, ab_loop_list__1;
    Object arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,158);
    SAVE_STACK();
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
    if ( !temp) {
	LOCK(Javalink_notification_versions);
	if (PUSH_UNWIND_PROTECT(1)) {
	    notification_data_version_map = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		    1);
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      if (temp_1) {
		  if (SIMPLE_VECTOR_P(item) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(item,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_class_bit_vector = ISVREF(ISVREF(item,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
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
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  connection_qm = ISVREF(item,(SI_Long)21L);
			  temp_1 = workspace_of_connection_qm(connection_qm);
		      }
		      else
			  temp_1 = get_workspace_if_any(item);
		  }
		  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_connection_g2_struct))
		      temp_1 = workspace_of_connection_qm(item);
		  else
		      temp_1 = Qnil;
		  temp = TRUEP(v5_tw_item_like_p(temp_1));
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  any_body_evaluated_p = Nil;
		  if (SIMPLE_VECTOR_P(item) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(item,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_class_bit_vector = ISVREF(ISVREF(item,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
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
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  connection_qm = ISVREF(item,(SI_Long)21L);
			  temp_1 = workspace_of_connection_qm(connection_qm);
		      }
		      else
			  temp_1 = get_workspace_if_any(item);
		  }
		  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_connection_g2_struct))
		      temp_1 = workspace_of_connection_qm(item);
		  else
		      temp_1 = Qnil;
		  frame_list = ISVREF(temp_1,(SI_Long)9L);
		  class_name = Qws_representation;
		  new_list = Qnil;
		  frame = Nil;
		  ab_loop_list_ = frame_list;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  frame = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol_3 = 
			  lookup_global_or_kb_specific_property_value(class_name,
			  Class_description_gkbprop);
		  if (gensymed_symbol_3) {
		      sub_class_bit_vector = ISVREF(ISVREF(frame,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      new_list = gensym_cons_1(frame,new_list);
		  goto next_loop;
		end_loop:
		  representations = new_list;
		  goto end_1;
		  representations = Qnil;
		end_1:;
		  current_frame_serial_number_on_entry = 
			  copy_frame_serial_number(Current_frame_serial_number);
		  representation = Nil;
		  ab_loop_list_ = representations;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  representation = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
		  temp = SIMPLE_VECTOR_P(representation) ? 
			  EQ(ISVREF(representation,(SI_Long)1L),
			  Qavailable_frame_vector) : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = FIXNUMP(gensymed_symbol_3) ? 
			      IFIX(gensymed_symbol_3) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  if (temp);
		  else if (FIXNUMP(current_frame_serial_number_on_entry))
		      temp = FIXNUMP(gensymed_symbol_3) ? 
			      FIXNUM_LT(current_frame_serial_number_on_entry,
			      gensymed_symbol_3) : TRUEP(T);
		  else if (FIXNUMP(gensymed_symbol_3))
		      temp = TRUEP(Nil);
		  else {
		      xa = M_CAR(current_frame_serial_number_on_entry);
		      ya = M_CAR(gensymed_symbol_3);
		      temp = FIXNUM_LT(xa,ya);
		      if (temp);
		      else
			  temp = FIXNUM_EQ(xa,ya) ? 
				  FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
				  M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
		  }
		  if ( !temp ? 
			  TRUEP(representation_address_valid_p(representation)) 
			  : TRUEP(Nil)) {
		      if ( !TRUEP(Notification_data_version_map))
			  Notification_data_version_map = gensym_cons_1(T,Nil);
		      version_for_current = Nil;
		      evaluatedp = Nil;
		      address = ISVREF(representation,(SI_Long)8L);
		      socket_1 = getf(address,Qsocket,_);
		      representation_version = 
			      remote_icp_protocol_version(socket_1);
		      subscription_handle = ISVREF(representation,
			      (SI_Long)12L);
		      current_list = Notification_data_version_map;
		      version_or_data = Nil;
		    next_loop_2:
		      version_or_data = CAR(current_list);
		      if ( !TRUEP(version_or_data))
			  goto end_2;
		      version_for_current = 
			      javalink_versioned_call_data_get_version(version_or_data);
		      evaluatedp = 
			      javalink_versioned_call_data_evaluated_p(version_or_data);
		      if (EQ(version_for_current,T) || 
			      FIXNUM_GE(representation_version,
			      version_for_current)) {
			  if ( !TRUEP(evaluatedp)) {
			      LOCK(Javalink_notification_versions);
			      if (PUSH_UNWIND_PROTECT(0)) {
				  current_lookup_data = 
					  make_javalink_versioned_data(version_or_data);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
					  0);
				    gensymed_symbol_3 = 
					    allocate_managed_array(1,
					    FIX((SI_Long)2L + (SI_Long)1L));
				    gensymed_symbol = (SI_Long)0L;
				    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					svref_arg_2 = gensymed_symbol + 
						IFIX(Managed_array_index_offset);
					ISVREF(gensymed_symbol_3,
						svref_arg_2) = 
						FIX((SI_Long)1L);
				    }
				    else {
					temp_2 = ISVREF(gensymed_symbol_3,
						(gensymed_symbol >>  -  - 
						(SI_Long)10L) + (SI_Long)2L);
					svref_arg_2 = gensymed_symbol & 
						(SI_Long)1023L;
					ISVREF(temp_2,svref_arg_2) = 
						FIX((SI_Long)1L);
				    }
				    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					    (SI_Long)1L),
					    Maximum_in_place_array_size))
					SVREF(gensymed_symbol_3,
						FIX((SI_Long)3L)) = 
						Qnew_rotation;
				    else {
					temp_2 = ISVREF(gensymed_symbol_3,
						(SI_Long)2L);
					SVREF(temp_2,FIX((SI_Long)1L)) = 
						Qnew_rotation;
				    }
				    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					item_or_value = new_rotation;
					if (item_or_value);
					else
					    item_or_value = Qnormal;
					if (SIMPLE_VECTOR_P(item_or_value) 
						&& 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						> (SI_Long)2L &&  
						!EQ(ISVREF(item_or_value,
						(SI_Long)1L),
						Qavailable_frame_vector)) {
					    x2 = ISVREF(item_or_value,
						    (SI_Long)1L);
					    temp = SIMPLE_VECTOR_P(x2) && 
						    EQ(ISVREF(x2,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_class_description_g2_struct) 
						    ? TRUEP(x2) : TRUEP(Qnil);
					}
					else
					    temp = TRUEP(Nil);
					temp_2 = temp ? 
						get_reference_to_item(item_or_value) 
						: item_or_value;
					SVREF(gensymed_symbol_3,
						FIX((SI_Long)4L)) = temp_2;
				    }
				    else {
					temp_2 = ISVREF(gensymed_symbol_3,
						(SI_Long)2L);
					item_or_value = new_rotation;
					if (item_or_value);
					else
					    item_or_value = Qnormal;
					if (SIMPLE_VECTOR_P(item_or_value) 
						&& 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						> (SI_Long)2L &&  
						!EQ(ISVREF(item_or_value,
						(SI_Long)1L),
						Qavailable_frame_vector)) {
					    x2 = ISVREF(item_or_value,
						    (SI_Long)1L);
					    temp = SIMPLE_VECTOR_P(x2) && 
						    EQ(ISVREF(x2,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_class_description_g2_struct) 
						    ? TRUEP(x2) : TRUEP(Qnil);
					}
					else
					    temp = TRUEP(Nil);
					svref_new_value = temp ? 
						get_reference_to_item(item_or_value) 
						: item_or_value;
					SVREF(temp_2,FIX((SI_Long)2L)) = 
						svref_new_value;
				    }
				    send_versioned_ws_notification_internal(Qitem_rotate,
					    item,
					    eval_cons_1(gensymed_symbol_3,
					    Qab_structure));
				    temp_1 = Current_lookup_data;
				  POP_SPECIAL();
				  SAVE_VALUES(VALUES_1(temp_1));
			      }
			      POP_UNWIND_PROTECT(0);
			      UNLOCK(Javalink_notification_versions);
			      CONTINUE_UNWINDING(0);
			      result = RESTORE_VALUES();
			      version_or_data = result;
			      M_CAR(current_list) = version_or_data;
			  }
			  if (javalink_versioned_call_data_sendp(version_or_data)) 
				      {
			      arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			      arg_list = Nil;
			      ab_loop_list__1 = arg_lists;
			      arg_list_to_send = Nil;
			    next_loop_3:
			      if ( !TRUEP(ab_loop_list__1))
				  goto end_loop_2;
			      arg_list = M_CAR(ab_loop_list__1);
			      ab_loop_list__1 = M_CDR(ab_loop_list__1);
			      arg_list_to_send = 
				      javalink_versioning_make_arg_list_copy(arg_list,
				      subscription_handle);
			      callback_representation_fire_callback(representation,
				      socket_1,arg_list_to_send);
			      goto next_loop_3;
			    end_loop_2:;
			  }
			  goto end_2;
		      }
		      current_list = CDR(current_list);
		      goto next_loop_2;
		    end_loop_3:
		    end_2:;
		  }
		  goto next_loop_1;
		end_loop_1:
		  reclaim_gensym_list_1(representations);
		  reclaim_frame_serial_number(current_frame_serial_number_on_entry);
		  javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
		  SAVE_VALUES(VALUES_1(any_body_evaluated_p));
		  goto end_3;
		  SAVE_VALUES(VALUES_1(Qnil));
		end_3:;
	      }
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Javalink_notification_versions);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qcolor_pattern_changes;  /* color-pattern-changes */

static Object Qitem_color_pattern_change;  /* item-color-pattern-change */

/* SEND-WS-REPRESENTATIONS-ITEM-COLOR-PATTERN-CHANGE */
Object send_ws_representations_item_color_pattern_change(item,
	    specific_region_qm,color_or_pattern)
    Object item, specific_region_qm, color_or_pattern;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_2, gensymed_symbol_4;
    Object item_or_value, temp_3, svref_new_value, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,159);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(item) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L &&  
		  !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(item,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(item,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(item);
	  }
	  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(item);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				gensymed_symbol_3 = 
					allocate_managed_array(1,
					FIX((SI_Long)2L + (SI_Long)1L));
				gensymed_symbol = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol_3,svref_arg_2) 
					    = FIX((SI_Long)1L);
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (gensymed_symbol >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol & 
					    (SI_Long)1023L;
				    ISVREF(temp_2,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)3L)) = 
					    Qcolor_pattern_changes;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)1L)) = 
					    Qcolor_pattern_changes;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    if (SYMBOLP(color_or_pattern)) {
					gensymed_symbol_4 = 
						allocate_managed_array(1,
						FIX((SI_Long)2L + 
						(SI_Long)1L));
					gensymed_symbol = (SI_Long)0L;
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    svref_arg_2 = gensymed_symbol 
						    + 
						    IFIX(Managed_array_index_offset);
					    ISVREF(gensymed_symbol_4,
						    svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol_4,
						    (gensymed_symbol >>  - 
						     - (SI_Long)10L) + 
						    (SI_Long)2L);
					    svref_arg_2 = gensymed_symbol 
						    & (SI_Long)1023L;
					    ISVREF(temp_2,svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size))
					    SVREF(gensymed_symbol_4,
						    FIX((SI_Long)3L)) = 
						    specific_region_qm;
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol_4,
						    (SI_Long)2L);
					    SVREF(temp_2,FIX((SI_Long)1L)) 
						    = specific_region_qm;
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    item_or_value = color_or_pattern;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    temp_2 = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(gensymed_symbol_4,
						    FIX((SI_Long)4L)) = temp_2;
					}
					else {
					    temp_2 = 
						    ISVREF(gensymed_symbol_4,
						    (SI_Long)2L);
					    item_or_value = color_or_pattern;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    temp_3 = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(temp_2,FIX((SI_Long)2L)) 
						    = temp_3;
					}
					item_or_value = 
						eval_cons_1(gensymed_symbol_4,
						Qab_structure);
				    }
				    else
					item_or_value = 
						export_color_pattern(color_or_pattern);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)4L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    if (SYMBOLP(color_or_pattern)) {
					gensymed_symbol_4 = 
						allocate_managed_array(1,
						FIX((SI_Long)2L + 
						(SI_Long)1L));
					gensymed_symbol = (SI_Long)0L;
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    svref_arg_2 = gensymed_symbol 
						    + 
						    IFIX(Managed_array_index_offset);
					    ISVREF(gensymed_symbol_4,
						    svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					else {
					    temp_3 = 
						    ISVREF(gensymed_symbol_4,
						    (gensymed_symbol >>  - 
						     - (SI_Long)10L) + 
						    (SI_Long)2L);
					    svref_arg_2 = gensymed_symbol 
						    & (SI_Long)1023L;
					    ISVREF(temp_3,svref_arg_2) = 
						    FIX((SI_Long)1L);
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size))
					    SVREF(gensymed_symbol_4,
						    FIX((SI_Long)3L)) = 
						    specific_region_qm;
					else {
					    temp_3 = 
						    ISVREF(gensymed_symbol_4,
						    (SI_Long)2L);
					    SVREF(temp_3,FIX((SI_Long)1L)) 
						    = specific_region_qm;
					}
					if (FIXNUM_LE(ISVREF(gensymed_symbol_4,
						(SI_Long)1L),
						Maximum_in_place_array_size)) {
					    item_or_value = color_or_pattern;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    temp_3 = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(gensymed_symbol_4,
						    FIX((SI_Long)4L)) = temp_3;
					}
					else {
					    temp_3 = 
						    ISVREF(gensymed_symbol_4,
						    (SI_Long)2L);
					    item_or_value = color_or_pattern;
					    if (SIMPLE_VECTOR_P(item_or_value) 
						    && 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						    > (SI_Long)2L &&  
						    !EQ(ISVREF(item_or_value,
						    (SI_Long)1L),
						    Qavailable_frame_vector)) {
						x2 = ISVREF(item_or_value,
							(SI_Long)1L);
						temp = SIMPLE_VECTOR_P(x2) 
							&& EQ(ISVREF(x2,
							(SI_Long)0L),
							Qg2_defstruct_structure_name_class_description_g2_struct) 
							? TRUEP(x2) : 
							TRUEP(Qnil);
					    }
					    else
						temp = TRUEP(Nil);
					    svref_new_value = temp ? 
						    get_reference_to_item(item_or_value) 
						    : item_or_value;
					    SVREF(temp_3,FIX((SI_Long)2L)) 
						    = svref_new_value;
					}
					item_or_value = 
						eval_cons_1(gensymed_symbol_4,
						Qab_structure);
				    }
				    else
					item_or_value = 
						export_color_pattern(color_or_pattern);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_3 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)2L)) = temp_3;
				}
				send_versioned_ws_notification_internal(Qitem_color_pattern_change,
					item,eval_cons_1(gensymed_symbol_3,
					Qab_structure));
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* ITEM-OR-CONNECTION-BEING-DELETED-P */
Object item_or_connection_being_deleted_p(thing)
    Object thing;
{
    Object x2, temp_1, sub_class_bit_vector, connection;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,160);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = (SI_Long)0L != (IFIX(ISVREF(thing,(SI_Long)5L)) & 
		(SI_Long)512L) ? T : Nil;
	if (temp_1);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		connection = ISVREF(thing,(SI_Long)21L);
		temp_1 = (SI_Long)0L != (IFIX(ISVREF(connection,
			(SI_Long)7L)) & (SI_Long)256L) ? T : Nil;
	    }
	    else
		temp_1 = Nil;
	}
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	temp_1 = (SI_Long)0L != (IFIX(ISVREF(thing,(SI_Long)7L)) & 
		(SI_Long)256L) ? T : Nil;
    else
	temp_1 = Qnil;
    return VALUES_1(temp_1);
}

/* SEND-WS-REPRESENTATIONS-ITEM-LAYER-CHANGE */
Object send_ws_representations_item_layer_change(thing,parent_of_thing_qm,
	    position_or_next_lower_thing)
    Object thing, parent_of_thing_qm, position_or_next_lower_thing;
{
    Object x2, sub_class_bit_vector, connection_qm, should_be_wksp_thing;
    Object useable_position_or_next_lower_thing, notification_data_version_map;
    Object any_body_evaluated_p, frame_list, class_name, new_list, frame;
    Object ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_1, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,161);
    SAVE_STACK();
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	    connection_qm = ISVREF(thing,(SI_Long)21L);
	    should_be_wksp_thing = workspace_of_connection_qm(connection_qm);
	}
	else
	    should_be_wksp_thing = get_workspace_if_any(thing);
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct))
	should_be_wksp_thing = workspace_of_connection_qm(thing);
    else
	should_be_wksp_thing = Qnil;
    if (should_be_wksp_thing);
    else
	should_be_wksp_thing = parent_of_thing_qm;
    useable_position_or_next_lower_thing = 
	    find_non_loose_end_below_thing(thing,should_be_wksp_thing,
	    position_or_next_lower_thing);
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (should_be_wksp_thing && 
		      v5_tw_item_like_p(should_be_wksp_thing)) {
	      any_body_evaluated_p = Nil;
	      frame_list = ISVREF(should_be_wksp_thing,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = 
			      gensym_list_2(T2_supports_item_layer_change,T);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				if (FIXNUMP(version_or_data) && 
					IFIX(version_or_data) <= (SI_Long)20L)
				    send_ws_representations_item_insert_or_change_layer_aux(thing,
					    useable_position_or_next_lower_thing,
					    Nil);
				else {
				    send_ws_representations_item_remove_as_subblock_aux(thing);
				    send_ws_representations_item_insert_or_change_layer_aux(thing,
					    useable_position_or_next_lower_thing,
					    T);
				}
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* FIND-NON-LOOSE-END-BELOW-THING */
Object find_non_loose_end_below_thing(thing,parent_of_thing_qm,
	    position_or_next_lower_thing)
    Object thing, parent_of_thing_qm, position_or_next_lower_thing;
{
    Object x2, sub_class_bit_vector, connection_qm, temp_1, gensymed_symbol_3;
    Object subblocks, queue, next_queue_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, subblocks_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,162);
    if (SIMPLE_VECTOR_P(position_or_next_lower_thing) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(position_or_next_lower_thing)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(position_or_next_lower_thing,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(position_or_next_lower_thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(position_or_next_lower_thing,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	if (SIMPLE_VECTOR_P(thing) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L &&  
		!EQ(ISVREF(thing,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		connection_qm = ISVREF(thing,(SI_Long)21L);
		temp_1 = workspace_of_connection_qm(connection_qm);
	    }
	    else
		temp_1 = get_workspace_if_any(thing);
	}
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))
	    temp_1 = workspace_of_connection_qm(thing);
	else
	    temp_1 = Qnil;
	if (temp_1);
	else
	    temp_1 = parent_of_thing_qm;
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(temp_1,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol_3;
	if (subblocks) {
	    queue = subblocks;
	    next_queue_element = Nil;
	    gensymed_symbol_3 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    next_queue_element = constant_queue_next(ISVREF(queue,
		    (SI_Long)2L),queue);
	  next_loop:
	    if ( !TRUEP(next_queue_element))
		goto end_loop;
	    gensymed_symbol_3 = ISVREF(next_queue_element,(SI_Long)4L);
	    next_queue_element = constant_queue_next(next_queue_element,queue);
	    ab_loopvar__2 = slot_value_cons_1(gensymed_symbol_3,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	}
	else
	    temp_1 = Nil;
	subblocks_1 = nreverse(temp_1);
	position_or_next_lower_thing = 
		find_next_non_loose_end(memq_function(position_or_next_lower_thing,
		subblocks_1));
	reclaim_slot_value_list_1(subblocks_1);
    }
    return VALUES_1(position_or_next_lower_thing);
}

static Object Qitem_remove;        /* item-remove */

/* SEND-ITEM-REMOVE-AS-SUBBLOCK-INTERNAL */
Object send_item_remove_as_subblock_internal(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(248,163);
    temp = send_versioned_ws_notification_internal(Qitem_remove,thing,Nil);
    return VALUES_1(temp);
}

static Object Qposition_or_next_lower_item;  /* position-or-next-lower-item */

static Object Qitem_layer_change;  /* item-layer-change */

/* SEND-LAYER-CHANGE-FOR-ITEM-INTERNAL */
Object send_layer_change_for_item_internal(thing,position_or_next_lower_thing)
    Object thing, position_or_next_lower_thing;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,164);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qposition_or_next_lower_item;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qposition_or_next_lower_item;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = position_or_next_lower_thing;
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
	item_or_value = position_or_next_lower_thing;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    temp_2 = send_versioned_ws_notification_internal(Qitem_layer_change,
	    thing,eval_cons_1(gensymed_symbol,Qab_structure));
    return VALUES_1(temp_2);
}

static Object Qitem_insert;        /* item-insert */

/* SEND-INSERT-FOR-ITEM-INTERNAL */
Object send_insert_for_item_internal(thing,position_or_next_lower_thing)
    Object thing, position_or_next_lower_thing;
{
    Object info, temp;

    x_note_fn_call(248,165);
    info = get_thing_initial_info(thing);
    set_evaluation_structure_slot(info,Qposition_or_next_lower_item,
	    position_or_next_lower_thing);
    temp = send_versioned_ws_notification_internal(Qitem_insert,thing,info);
    return VALUES_1(temp);
}

/* SEND-WS-REPRESENTATIONS-ITEM-INSERT-OR-CHANGE-LAYER-AUX */
Object send_ws_representations_item_insert_or_change_layer_aux(thing,
	    position_or_next_lower_thing,for_insert_p)
    Object thing, position_or_next_lower_thing, for_insert_p;
{
    Object children, item_like_children_1, first_child, x2;
    Object sub_class_bit_vector, first_lower_item_or_position;
    Object last_non_loose_end, child1, child2, ab_loop_list_, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(248,166);
    if (for_insert_p)
	send_insert_for_item_internal(thing,position_or_next_lower_thing);
    else
	send_layer_change_for_item_internal(thing,
		position_or_next_lower_thing);
    children = children_of_thing(2,thing,T);
    item_like_children_1 = item_like_children(children);
    first_child = CAR(item_like_children_1);
    if (SIMPLE_VECTOR_P(thing) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(thing,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    first_lower_item_or_position = temp ? position_or_next_lower_thing : thing;
    if (first_child)
	send_ws_representations_item_insert_or_change_layer_aux(first_child,
		first_lower_item_or_position,for_insert_p);
    last_non_loose_end = first_lower_item_or_position;
    child1 = Nil;
    child2 = Nil;
    ab_loop_list_ = item_like_children_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child1 = CAR(ab_loop_list_);
    temp_1 = CDR(ab_loop_list_);
    child2 = CAR(temp_1);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(child1) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(child1)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(child1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(child1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(child1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
    if ( !temp)
	last_non_loose_end = child1;
    if (child2)
	send_ws_representations_item_insert_or_change_layer_aux(child2,
		last_non_loose_end,for_insert_p);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(children);
    return reclaim_gensym_list_1(item_like_children_1);
}

/* SEND-WS-REPRESENTATIONS-ITEM-INSERT-AS-SUBBLOCK */
Object send_ws_representations_item_insert_as_subblock(thing,
	    parent_of_thing_qm,position_or_next_lower_thing)
    Object thing, parent_of_thing_qm, position_or_next_lower_thing;
{
    Object x2, sub_class_bit_vector, connection_qm, should_be_wksp_thing;
    Object useable_position_or_next_lower_thing, notification_data_version_map;
    Object any_body_evaluated_p, frame_list, class_name, new_list, frame;
    Object ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, temp_1, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,167);
    SAVE_STACK();
    if (Transfer_in_progress) {
	Saved_position_or_next_lower_thing = position_or_next_lower_thing;
	RESTORE_STACK();
	return VALUES_1(Saved_position_or_next_lower_thing);
    }
    else {
	if (SIMPLE_VECTOR_P(thing) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L &&  
		!EQ(ISVREF(thing,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(thing,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		connection_qm = ISVREF(thing,(SI_Long)21L);
		should_be_wksp_thing = 
			workspace_of_connection_qm(connection_qm);
	    }
	    else
		should_be_wksp_thing = get_workspace_if_any(thing);
	}
	else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct))
	    should_be_wksp_thing = workspace_of_connection_qm(thing);
	else
	    should_be_wksp_thing = Qnil;
	if (should_be_wksp_thing);
	else
	    should_be_wksp_thing = parent_of_thing_qm;
	useable_position_or_next_lower_thing = 
		find_non_loose_end_below_thing(thing,should_be_wksp_thing,
		position_or_next_lower_thing);
	LOCK(Javalink_notification_versions);
	if (PUSH_UNWIND_PROTECT(1)) {
	    notification_data_version_map = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		    1);
	      if (should_be_wksp_thing && 
		      v5_tw_item_like_p(should_be_wksp_thing)) {
		  any_body_evaluated_p = Nil;
		  frame_list = ISVREF(should_be_wksp_thing,(SI_Long)9L);
		  class_name = Qws_representation;
		  new_list = Qnil;
		  frame = Nil;
		  ab_loop_list_ = frame_list;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  frame = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol_3 = 
			  lookup_global_or_kb_specific_property_value(class_name,
			  Class_description_gkbprop);
		  if (gensymed_symbol_3) {
		      sub_class_bit_vector = ISVREF(ISVREF(frame,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      new_list = gensym_cons_1(frame,new_list);
		  goto next_loop;
		end_loop:
		  representations = new_list;
		  goto end_1;
		  representations = Qnil;
		end_1:;
		  current_frame_serial_number_on_entry = 
			  copy_frame_serial_number(Current_frame_serial_number);
		  representation = Nil;
		  ab_loop_list_ = representations;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  representation = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
		  temp = SIMPLE_VECTOR_P(representation) ? 
			  EQ(ISVREF(representation,(SI_Long)1L),
			  Qavailable_frame_vector) : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = FIXNUMP(gensymed_symbol_3) ? 
			      IFIX(gensymed_symbol_3) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  if (temp);
		  else if (FIXNUMP(current_frame_serial_number_on_entry))
		      temp = FIXNUMP(gensymed_symbol_3) ? 
			      FIXNUM_LT(current_frame_serial_number_on_entry,
			      gensymed_symbol_3) : TRUEP(T);
		  else if (FIXNUMP(gensymed_symbol_3))
		      temp = TRUEP(Nil);
		  else {
		      xa = M_CAR(current_frame_serial_number_on_entry);
		      ya = M_CAR(gensymed_symbol_3);
		      temp = FIXNUM_LT(xa,ya);
		      if (temp);
		      else
			  temp = FIXNUM_EQ(xa,ya) ? 
				  FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
				  M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
		  }
		  if ( !temp ? 
			  TRUEP(representation_address_valid_p(representation)) 
			  : TRUEP(Nil)) {
		      if ( !TRUEP(Notification_data_version_map))
			  Notification_data_version_map = gensym_cons_1(T,Nil);
		      version_for_current = Nil;
		      evaluatedp = Nil;
		      address = ISVREF(representation,(SI_Long)8L);
		      socket_1 = getf(address,Qsocket,_);
		      representation_version = 
			      remote_icp_protocol_version(socket_1);
		      subscription_handle = ISVREF(representation,
			      (SI_Long)12L);
		      current_list = Notification_data_version_map;
		      version_or_data = Nil;
		    next_loop_2:
		      version_or_data = CAR(current_list);
		      if ( !TRUEP(version_or_data))
			  goto end_2;
		      version_for_current = 
			      javalink_versioned_call_data_get_version(version_or_data);
		      evaluatedp = 
			      javalink_versioned_call_data_evaluated_p(version_or_data);
		      if (EQ(version_for_current,T) || 
			      FIXNUM_GE(representation_version,
			      version_for_current)) {
			  if ( !TRUEP(evaluatedp)) {
			      LOCK(Javalink_notification_versions);
			      if (PUSH_UNWIND_PROTECT(0)) {
				  current_lookup_data = 
					  make_javalink_versioned_data(version_or_data);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
					  0);
				    send_ws_representations_item_insert_or_change_layer_aux(thing,
					    useable_position_or_next_lower_thing,
					    T);
				    temp_1 = Current_lookup_data;
				  POP_SPECIAL();
				  SAVE_VALUES(VALUES_1(temp_1));
			      }
			      POP_UNWIND_PROTECT(0);
			      UNLOCK(Javalink_notification_versions);
			      CONTINUE_UNWINDING(0);
			      result = RESTORE_VALUES();
			      version_or_data = result;
			      M_CAR(current_list) = version_or_data;
			  }
			  if (javalink_versioned_call_data_sendp(version_or_data)) 
				      {
			      arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			      arg_list = Nil;
			      ab_loop_list__1 = arg_lists;
			      arg_list_to_send = Nil;
			    next_loop_3:
			      if ( !TRUEP(ab_loop_list__1))
				  goto end_loop_2;
			      arg_list = M_CAR(ab_loop_list__1);
			      ab_loop_list__1 = M_CDR(ab_loop_list__1);
			      arg_list_to_send = 
				      javalink_versioning_make_arg_list_copy(arg_list,
				      subscription_handle);
			      callback_representation_fire_callback(representation,
				      socket_1,arg_list_to_send);
			      goto next_loop_3;
			    end_loop_2:;
			  }
			  goto end_2;
		      }
		      current_list = CDR(current_list);
		      goto next_loop_2;
		    end_loop_3:
		    end_2:;
		  }
		  goto next_loop_1;
		end_loop_1:
		  reclaim_gensym_list_1(representations);
		  reclaim_frame_serial_number(current_frame_serial_number_on_entry);
		  javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
		  SAVE_VALUES(VALUES_1(any_body_evaluated_p));
		  goto end_3;
		  SAVE_VALUES(VALUES_1(Qnil));
		end_3:;
	      }
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Javalink_notification_versions);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

/* SEND-WS-REPRESENTATIONS-REMOVE-CONNECTIONS-OF-BLOCK */
Object send_ws_representations_remove_connections_of_block(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,168);
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
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
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      send_ws_representations_item_remove_as_subblock(connection,block);
      goto next_loop;
    end_loop_2:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SEND-WS-REPRESENTATIONS-ITEM-REMOVE-AS-SUBBLOCK-AUX */
Object send_ws_representations_item_remove_as_subblock_aux(thing)
    Object thing;
{
    Object children, item_like_children_1, child, ab_loop_list_;

    x_note_fn_call(248,169);
    send_versioned_ws_notification_internal(Qitem_remove,thing,Nil);
    children = children_of_thing(2,thing,T);
    item_like_children_1 = item_like_children(children);
    child = Nil;
    ab_loop_list_ = item_like_children_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    child = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    send_ws_representations_item_remove_as_subblock_aux(child);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(children);
    reclaim_gensym_list_1(item_like_children_1);
    return VALUES_1(Qnil);
}

/* SEND-WS-REPRESENTATIONS-ITEM-REMOVE-AS-SUBBLOCK */
Object send_ws_representations_item_remove_as_subblock(thing,
	    parent_of_thing_qm)
    Object thing, parent_of_thing_qm;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, arg_lists, arg_list;
    Object ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,170);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  temp = TRUEP(parent_of_thing_qm);
	  if (temp);
	  else {
	      if (SIMPLE_VECTOR_P(thing) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(thing,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(thing,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(thing,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(thing,(SI_Long)21L);
		      temp = TRUEP(workspace_of_connection_qm(connection_qm));
		  }
		  else
		      temp = TRUEP(get_workspace_if_any(thing));
	      }
	      else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp = TRUEP(workspace_of_connection_qm(thing));
	      else
		  temp = TRUEP(Qnil);
	  }
	  if (temp) {
	      temp_1 = parent_of_thing_qm;
	      if (temp_1);
	      else {
		  if (SIMPLE_VECTOR_P(thing) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(thing,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_class_bit_vector = ISVREF(ISVREF(thing,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
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
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  connection_qm = ISVREF(thing,(SI_Long)21L);
			  temp_1 = workspace_of_connection_qm(connection_qm);
		      }
		      else
			  temp_1 = get_workspace_if_any(thing);
		  }
		  else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_connection_g2_struct))
		      temp_1 = workspace_of_connection_qm(thing);
		  else
		      temp_1 = Qnil;
	      }
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      temp_1 = parent_of_thing_qm;
	      if (temp_1);
	      else {
		  if (SIMPLE_VECTOR_P(thing) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(thing,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      sub_class_bit_vector = ISVREF(ISVREF(thing,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
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
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  connection_qm = ISVREF(thing,(SI_Long)21L);
			  temp_1 = workspace_of_connection_qm(connection_qm);
		      }
		      else
			  temp_1 = get_workspace_if_any(thing);
		  }
		  else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_connection_g2_struct))
		      temp_1 = workspace_of_connection_qm(thing);
		  else
		      temp_1 = Qnil;
	      }
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				send_ws_representations_item_remove_as_subblock_aux(thing);
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qnew_value;          /* new-value */

static Object Qitem_change;        /* item-change */

/* SEND-WS-REPRESENTATIONS-ITEM-VIRTUAL-ATTRIBUTE-CHANGE */
Object send_ws_representations_item_virtual_attribute_change(item,
	    virtual_attribute,sub_denotation_qm)
    Object item, virtual_attribute, sub_denotation_qm;
{
    Object notification_data_version_map, x2, sub_class_bit_vector;
    Object connection_qm, temp_1, any_body_evaluated_p, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol_3, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object version_for_current, evaluatedp, address, socket_1;
    Object representation_version, subscription_handle, current_list;
    Object version_or_data, current_lookup_data, getter_qm, new_value;
    Object attribute_name, temp_2, item_or_value, svref_new_value, update_info;
    Object arg_lists, arg_list, ab_loop_list__1, arg_list_to_send;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,171);
    SAVE_STACK();
    LOCK(Javalink_notification_versions);
    if (PUSH_UNWIND_PROTECT(1)) {
	notification_data_version_map = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Notification_data_version_map,Qnotification_data_version_map,notification_data_version_map,
		1);
	  if (SIMPLE_VECTOR_P(item) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L &&  
		  !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(item,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
		  connection_qm = ISVREF(item,(SI_Long)21L);
		  temp_1 = workspace_of_connection_qm(connection_qm);
	      }
	      else
		  temp_1 = get_workspace_if_any(item);
	  }
	  else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		  Qg2_defstruct_structure_name_connection_g2_struct))
	      temp_1 = workspace_of_connection_qm(item);
	  else
	      temp_1 = Qnil;
	  if (temp_1) {
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      temp = TRUEP(v5_tw_item_like_p(temp_1));
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      any_body_evaluated_p = Nil;
	      if (SIMPLE_VECTOR_P(item) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(item,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Connection_class_description,
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      connection_qm = ISVREF(item,(SI_Long)21L);
		      temp_1 = workspace_of_connection_qm(connection_qm);
		  }
		  else
		      temp_1 = get_workspace_if_any(item);
	      }
	      else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_connection_g2_struct))
		  temp_1 = workspace_of_connection_qm(item);
	      else
		  temp_1 = Qnil;
	      frame_list = ISVREF(temp_1,(SI_Long)9L);
	      class_name = Qws_representation;
	      new_list = Qnil;
	      frame = Nil;
	      ab_loop_list_ = frame_list;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = 
		      lookup_global_or_kb_specific_property_value(class_name,
		      Class_description_gkbprop);
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
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
	      if (temp)
		  new_list = gensym_cons_1(frame,new_list);
	      goto next_loop;
	    end_loop:
	      representations = new_list;
	      goto end_1;
	      representations = Qnil;
	    end_1:;
	      current_frame_serial_number_on_entry = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      representation = Nil;
	      ab_loop_list_ = representations;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_3 = ISVREF(representation,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(representation) ? 
		      EQ(ISVREF(representation,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  IFIX(gensymed_symbol_3) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else if (FIXNUMP(current_frame_serial_number_on_entry))
		  temp = FIXNUMP(gensymed_symbol_3) ? 
			  FIXNUM_LT(current_frame_serial_number_on_entry,
			  gensymed_symbol_3) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol_3))
		  temp = TRUEP(Nil);
	      else {
		  xa = M_CAR(current_frame_serial_number_on_entry);
		  ya = M_CAR(gensymed_symbol_3);
		  temp = FIXNUM_LT(xa,ya);
		  if (temp);
		  else
		      temp = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			      M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
	      }
	      if ( !temp ? 
		      TRUEP(representation_address_valid_p(representation)) 
		      : TRUEP(Nil)) {
		  if ( !TRUEP(Notification_data_version_map))
		      Notification_data_version_map = gensym_cons_1(T,Nil);
		  version_for_current = Nil;
		  evaluatedp = Nil;
		  address = ISVREF(representation,(SI_Long)8L);
		  socket_1 = getf(address,Qsocket,_);
		  representation_version = 
			  remote_icp_protocol_version(socket_1);
		  subscription_handle = ISVREF(representation,(SI_Long)12L);
		  current_list = Notification_data_version_map;
		  version_or_data = Nil;
		next_loop_2:
		  version_or_data = CAR(current_list);
		  if ( !TRUEP(version_or_data))
		      goto end_2;
		  version_for_current = 
			  javalink_versioned_call_data_get_version(version_or_data);
		  evaluatedp = 
			  javalink_versioned_call_data_evaluated_p(version_or_data);
		  if (EQ(version_for_current,T) || 
			  FIXNUM_GE(representation_version,
			  version_for_current)) {
		      if ( !TRUEP(evaluatedp)) {
			  LOCK(Javalink_notification_versions);
			  if (PUSH_UNWIND_PROTECT(0)) {
			      current_lookup_data = 
				      make_javalink_versioned_data(version_or_data);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_lookup_data,Qcurrent_lookup_data,current_lookup_data,
				      0);
				getter_qm = ISVREF(virtual_attribute,
					(SI_Long)6L);
				new_value = getter_qm ? 
					inline_funcall_1(getter_qm,item) : 
					No_component_value;
				attribute_name = ISVREF(virtual_attribute,
					(SI_Long)1L);
				gensymed_symbol_3 = 
					allocate_managed_array(1,
					FIX((SI_Long)4L + (SI_Long)1L));
				gensymed_symbol = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol_3,svref_arg_2) 
					    = FIX((SI_Long)1L);
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (gensymed_symbol >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol & 
					    (SI_Long)1023L;
				    ISVREF(temp_2,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)3L)) = 
					    Qattribute_name;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)1L)) = 
					    Qattribute_name;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = attribute_name;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)4L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = attribute_name;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)2L)) = 
					    svref_new_value;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)5L)) = Qnew_value;
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    SVREF(temp_2,FIX((SI_Long)3L)) = 
					    Qnew_value;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol_3,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = new_value;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    temp_2 = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol_3,
					    FIX((SI_Long)6L)) = temp_2;
				}
				else {
				    temp_2 = ISVREF(gensymed_symbol_3,
					    (SI_Long)2L);
				    item_or_value = new_value;
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp = TRUEP(Nil);
				    svref_new_value = temp ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_2,FIX((SI_Long)4L)) = 
					    svref_new_value;
				}
				update_info = 
					eval_cons_1(gensymed_symbol_3,
					Qab_structure);
				send_versioned_ws_notification_internal(Qitem_change,
					item,update_info);
				temp_1 = Current_lookup_data;
			      POP_SPECIAL();
			      SAVE_VALUES(VALUES_1(temp_1));
			  }
			  POP_UNWIND_PROTECT(0);
			  UNLOCK(Javalink_notification_versions);
			  CONTINUE_UNWINDING(0);
			  result = RESTORE_VALUES();
			  version_or_data = result;
			  M_CAR(current_list) = version_or_data;
		      }
		      if (javalink_versioned_call_data_sendp(version_or_data)) 
				  {
			  arg_lists = ISVREF(version_or_data,(SI_Long)2L);
			  arg_list = Nil;
			  ab_loop_list__1 = arg_lists;
			  arg_list_to_send = Nil;
			next_loop_3:
			  if ( !TRUEP(ab_loop_list__1))
			      goto end_loop_2;
			  arg_list = M_CAR(ab_loop_list__1);
			  ab_loop_list__1 = M_CDR(ab_loop_list__1);
			  arg_list_to_send = 
				  javalink_versioning_make_arg_list_copy(arg_list,
				  subscription_handle);
			  callback_representation_fire_callback(representation,
				  socket_1,arg_list_to_send);
			  goto next_loop_3;
			end_loop_2:;
		      }
		      goto end_2;
		  }
		  current_list = CDR(current_list);
		  goto next_loop_2;
		end_loop_3:
		end_2:;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      reclaim_gensym_list_1(representations);
	      reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	      javalink_versioning_reclaim_evaluated_version_bodies(Notification_data_version_map);
	      SAVE_VALUES(VALUES_1(any_body_evaluated_p));
	      goto end_3;
	      SAVE_VALUES(VALUES_1(Qnil));
	    end_3:;
	  }
	  else
	      SAVE_VALUES(VALUES_1(Nil));
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(1);
    UNLOCK(Javalink_notification_versions);
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Highest_parsing_context_handle, Qhighest_parsing_context_handle);

DEFINE_VARIABLE_WITH_SYMBOL(Current_parsing_contexts, Qcurrent_parsing_contexts);

static Object Qg2_defstruct_structure_name_parsing_context_g2_struct;  /* g2-defstruct-structure-name::parsing-context-g2-struct */

/* GET-PARSING-CONTEXT */
Object get_parsing_context(handle)
    Object handle;
{
    Object temp;

    x_note_fn_call(248,172);
    if (FIXNUMP(handle)) {
	temp = assq_function(handle,Current_parsing_contexts);
	return VALUES_1(CDR(temp));
    }
    else if (SIMPLE_VECTOR_P(handle) && EQ(ISVREF(handle,(SI_Long)0L),
	    Qg2_defstruct_structure_name_parsing_context_g2_struct))
	return VALUES_1(handle);
    else
	return VALUES_1(Nil);
}

/* REMOVE-PARSING-CONTEXT */
Object remove_parsing_context(handle_or_pc)
    Object handle_or_pc;
{
    Object parsing_context_pair_qm, pc;

    x_note_fn_call(248,173);
    if (FIXNUMP(handle_or_pc)) {
	parsing_context_pair_qm = assq_function(handle_or_pc,
		Current_parsing_contexts);
	if (parsing_context_pair_qm) {
	    pc = CDR(parsing_context_pair_qm);
	    Current_parsing_contexts = 
		    delete_gensym_element_1(parsing_context_pair_qm,
		    Current_parsing_contexts);
	    reclaim_gensym_cons_1(parsing_context_pair_qm);
	    return reclaim_parsing_context(pc);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return reclaim_parsing_context(handle_or_pc);
}

DEFINE_VARIABLE_WITH_SYMBOL(Testing_parsing_context_locally_p, Qtesting_parsing_context_locally_p);

/* MAYBE-RETURN-FROM-SYSTEM-DEFINED-RPC */
Object maybe_return_from_system_defined_rpc(rpc_instance,eval_list)
    Object rpc_instance, eval_list;
{
    x_note_fn_call(248,174);
    if (Testing_parsing_context_locally_p)
	return VALUES_1(Nil);
    else
	return return_from_system_defined_rpc(rpc_instance,eval_list);
}

static Object Qg2_create_parsing_context;  /* g2-create-parsing-context */

/* G2-CREATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL */
Object g2_create_parsing_context_system_rpc_internal(rpc_instance,
	    grammar_category_qm,class_name_qm,attribute_name_qm,
	    slot_component_name_qm,slot_component_indicator_qm)
    Object rpc_instance, grammar_category_qm, class_name_qm, attribute_name_qm;
    Object slot_component_name_qm, slot_component_indicator_qm;
{
    Object pretty_slot_name_qm, slot_description_qm, type_when_editable_qm, pc;
    Object type_to_use, construct_the_type_qm;
    Object highest_parsing_context_handle_new_value, index_1;

    x_note_fn_call(248,175);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_create_parsing_context,
	    Qui_client_interface)) {
	if ( !SYMBOLP(grammar_category_qm)) {
	    reclaim_evaluation_value(grammar_category_qm);
	    grammar_category_qm = Nil;
	}
	if ( !SYMBOLP(class_name_qm)) {
	    reclaim_evaluation_value(class_name_qm);
	    class_name_qm = Nil;
	}
	if ( !SYMBOLP(attribute_name_qm)) {
	    reclaim_evaluation_value(attribute_name_qm);
	    attribute_name_qm = Nil;
	}
	if ( !SYMBOLP(slot_component_name_qm)) {
	    reclaim_evaluation_value(slot_component_name_qm);
	    slot_component_name_qm = Nil;
	}
	if ( !SYMBOLP(slot_component_indicator_qm)) {
	    reclaim_evaluation_value(slot_component_indicator_qm);
	    slot_component_indicator_qm = Nil;
	}
	if (attribute_name_qm && class_name_qm) {
	    pretty_slot_name_qm = 
		    get_slot_name_for_alias_if_any(attribute_name_qm,
		    class_name_qm);
	    if (pretty_slot_name_qm);
	    else
		pretty_slot_name_qm = attribute_name_qm;
	}
	else
	    pretty_slot_name_qm = Nil;
	slot_description_qm = attribute_name_qm && class_name_qm ? 
		get_slot_description_of_class_description_function(pretty_slot_name_qm,
		lookup_global_or_kb_specific_property_value(class_name_qm,
		Class_description_gkbprop),Nil) : Nil;
	type_when_editable_qm = slot_description_qm ? 
		type_slot_feature_assq_if_editable(ISVREF(slot_description_qm,
		(SI_Long)9L)) : Nil;
	if ( !(grammar_category_qm || class_name_qm && attribute_name_qm))
	    maybe_return_from_system_defined_rpc(rpc_instance,
		    eval_cons_1(Evaluation_false_value,Nil));
	else if ( !TRUEP(grammar_category_qm) &&  !TRUEP(slot_description_qm))
	    maybe_return_from_system_defined_rpc(rpc_instance,
		    eval_cons_1(Evaluation_false_value,Nil));
	else if ( !TRUEP(grammar_category_qm) && slot_description_qm &&  
		!TRUEP(type_when_editable_qm))
	    maybe_return_from_system_defined_rpc(rpc_instance,
		    eval_cons_1(Evaluation_false_value,Nil));
	else {
	    pc = Nil;
	    type_to_use = Nil;
	    construct_the_type_qm = Nil;
	    highest_parsing_context_handle_new_value = 
		    FIXNUM_ADD1(Highest_parsing_context_handle);
	    Highest_parsing_context_handle = 
		    highest_parsing_context_handle_new_value;
	    index_1 = Highest_parsing_context_handle;
	    if (grammar_category_qm &&  !TRUEP(class_name_qm)) {
		construct_the_type_qm = T;
		type_to_use = gensym_list_2(Qtype,grammar_category_qm);
		pc = create_parsing_context(5,Nil,Nil,type_to_use,Nil,Nil);
	    }
	    else {
		if (grammar_category_qm && type_when_editable_qm) {
		    construct_the_type_qm = EQ(grammar_category_qm,
			    SECOND(type_when_editable_qm)) ? T : Nil;
		    type_to_use = construct_the_type_qm ? 
			    type_when_editable_qm : gensym_list_2(Qtype,
			    grammar_category_qm);
		}
		pc = create_parsing_context(5,class_name_qm,
			pretty_slot_name_qm,type_to_use,
			slot_component_name_qm,slot_component_indicator_qm);
	    }
	    Current_parsing_contexts = gensym_cons_1(gensym_cons_1(index_1,
		    pc),Current_parsing_contexts);
	    return_from_parsing_context_creation(pc,index_1,rpc_instance);
	}
    }
    return VALUES_1(Nil);
}

static Object Qparsing_context_handle;  /* parsing-context-handle */

static Object Qendable_p;          /* endable-p */

static Object Qlongest_common_completion;  /* longest-common-completion */

static Object Qcompletion_choices;  /* completion-choices */

static Object Qcategory_choices;   /* category-choices */

/* RETURN-FROM-PARSING-CONTEXT-CREATION */
Object return_from_parsing_context_creation(current_parsing_context_qm,
	    index_1,rpc_instance)
    Object current_parsing_context_qm, index_1, rpc_instance;
{
    Object start_token, current_edit_state, category_choices;
    Object completion_choices, longest_common_completion_qm, can_end_qm;
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(248,176);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    1);
      if ( !TRUEP(ISVREF(Current_parsing_context_qm,(SI_Long)11L))) {
	  start_token = ISVREF(Current_parsing_context_qm,(SI_Long)103L);
	  current_edit_state = Current_parsing_context_qm;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		  0);
	    update_parsing_context_completions_as_appropriate(3,
		    start_token,Nil,Nil);
	  POP_SPECIAL();
	  result = compute_parsing_context_prompts(start_token);
	  MVS_4(result,category_choices,completion_choices,
		  longest_common_completion_qm,can_end_qm);
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		      Qparsing_context_handle;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qparsing_context_handle;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = index_1;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = index_1;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qendable_p;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qendable_p;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = can_end_qm ? Evaluation_true_value : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = can_end_qm ? Evaluation_true_value : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
		      Qlongest_common_completion;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qlongest_common_completion;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = longest_common_completion_qm;
	      if (item_or_value);
	      else
		  item_or_value = Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = longest_common_completion_qm;
	      if (item_or_value);
	      else
		  item_or_value = Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qcompletion_choices;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)7L)) = Qcompletion_choices;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = 
		      allocate_evaluation_sequence(copy_list_using_eval_conses_1(completion_choices));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = 
		      allocate_evaluation_sequence(copy_list_using_eval_conses_1(completion_choices));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qcategory_choices;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)9L)) = Qcategory_choices;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = 
		      allocate_evaluation_sequence(copy_list_using_eval_conses_1(category_choices));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = 
		      allocate_evaluation_sequence(copy_list_using_eval_conses_1(category_choices));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	  }
	  result = maybe_return_from_system_defined_rpc(rpc_instance,
		  eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),Nil));
      }
      else {
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
		      Qparsing_context_handle;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qparsing_context_handle;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = index_1;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = index_1;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qendable_p;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qendable_p;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = Evaluation_true_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = Evaluation_true_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
		      Qlongest_common_completion;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qlongest_common_completion;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qcompletion_choices;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)7L)) = Qcompletion_choices;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = allocate_evaluation_sequence(Nil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = allocate_evaluation_sequence(Nil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qcategory_choices;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)9L)) = Qcategory_choices;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = allocate_evaluation_sequence(Nil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = allocate_evaluation_sequence(Nil);
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	  }
	  result = maybe_return_from_system_defined_rpc(rpc_instance,
		  eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),Nil));
      }
    POP_SPECIAL();
    return result;
}

/* G2-SIMPLE-CREATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL */
Object g2_simple_create_parsing_context_system_rpc_internal(rpc_instance,
	    item,attribute_name)
    Object rpc_instance, item, attribute_name;
{
    x_note_fn_call(248,177);
    maybe_return_from_system_defined_rpc(rpc_instance,
	    eval_cons_1(g2_simple_create_parsing_context(item,
	    attribute_name),Nil));
    return VALUES_1(Nil);
}

/* G2-SIMPLE-CREATE-PARSING-CONTEXT */
Object g2_simple_create_parsing_context(item_as_evaluation_value,
	    attribute_name_as_evaluation_value)
    Object item_as_evaluation_value, attribute_name_as_evaluation_value;
{
    Object item, attribute_name, value_1, pc;
    Object highest_parsing_context_handle_new_value, index_1;

    x_note_fn_call(248,178);
    item = IDENTITY(item_as_evaluation_value);
    attribute_name = attribute_name_as_evaluation_value;
    value_1 = Nil;
    pc = simple_create_parsing_context(item,attribute_name);
    highest_parsing_context_handle_new_value = 
	    FIXNUM_ADD1(Highest_parsing_context_handle);
    Highest_parsing_context_handle = highest_parsing_context_handle_new_value;
    index_1 = Highest_parsing_context_handle;
    Current_parsing_contexts = gensym_cons_1(gensym_cons_1(index_1,pc),
	    Current_parsing_contexts);
    value_1 = index_1;
    IDENTITY(item_as_evaluation_value);
    return VALUES_1(value_1);
}

static Object string_constant_20;  /* "Cannot create parsing context for item ~NF, attribute ~a" */

/* SIMPLE-CREATE-PARSING-CONTEXT */
Object simple_create_parsing_context(item,attribute_name)
    Object item, attribute_name;
{
    Object class_name, pretty_slot_name, slot_description_qm;
    Object type_when_editable, pc, top_of_stack, message_1;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;

    x_note_fn_call(248,179);
    class_name = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    pretty_slot_name = get_slot_name_for_alias_if_any(attribute_name,
	    class_name);
    if (pretty_slot_name);
    else
	pretty_slot_name = attribute_name;
    slot_description_qm = 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),Nil);
    type_when_editable = slot_description_qm ? 
	    type_slot_feature_assq_if_editable(ISVREF(slot_description_qm,
	    (SI_Long)9L)) : Nil;
    pc = Nil;
    if ( !TRUEP(slot_description_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_20,
		item,attribute_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    pc = create_parsing_context(5,class_name,pretty_slot_name,
	    type_when_editable,Nil,Nil);
    SVREF(pc,FIX((SI_Long)3L)) = item;
    frame_serial_number_setf_arg = ISVREF(item,(SI_Long)3L);
    old = ISVREF(pc,(SI_Long)4L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(pc,FIX((SI_Long)4L)) = svref_new_value;
    svref_new_value = get_text_of_attribute(item,pretty_slot_name,class_name);
    SVREF(pc,FIX((SI_Long)110L)) = svref_new_value;
    return VALUES_1(pc);
}

static Object string_constant_21;  /* "Class name ~a not valid for g2-validate-parsing-text" */

static Object string_constant_22;  /* "Class name ~a or attribute name ~a not valid for g2-validate-parsing-text" */

/* G2-VALIDATE-PARSING-TEXT */
Object g2_validate_parsing_text(class_name_as_evaluation_value,
	    attribute_name_as_evaluation_value,the_text_as_evaluation_value)
    Object class_name_as_evaluation_value, attribute_name_as_evaluation_value;
    Object the_text_as_evaluation_value;
{
    Object class_name, attribute_name, the_text, value_1, pretty_slot_name;
    Object class_description_qm, slot_description_qm, type_when_editable;
    Object top_of_stack, message_1, current_parsing_context_qm, svref_arg_1;
    Object svref_new_value, temp, ok, endable_p, longest_common_completion_qm;
    Object category_choices, completion_choices, token_complete_p, token_data;
    Object copy_of_gripe;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,180);
    class_name = class_name_as_evaluation_value;
    attribute_name = attribute_name_as_evaluation_value;
    the_text = the_text_as_evaluation_value;
    value_1 = Nil;
    pretty_slot_name = get_slot_name_for_alias_if_any(attribute_name,
	    class_name);
    if (pretty_slot_name);
    else
	pretty_slot_name = attribute_name;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    slot_description_qm = class_description_qm ? 
	    get_slot_description_of_class_description_function(pretty_slot_name,
	    class_description_qm,Nil) : Qnil;
    type_when_editable = slot_description_qm ? 
	    type_slot_feature_assq_if_editable(ISVREF(slot_description_qm,
	    (SI_Long)9L)) : Nil;
    if ( !TRUEP(class_description_qm)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_21,
		class_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(type_when_editable)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_22,
		class_name,attribute_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    current_parsing_context_qm = create_parsing_context(5,class_name,
	    pretty_slot_name,type_when_editable,Nil,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      svref_arg_1 = Current_parsing_context_qm;
      SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
      svref_arg_1 = Current_parsing_context_qm;
      svref_new_value = copy_wide_string(the_text);
      SVREF(svref_arg_1,FIX((SI_Long)110L)) = svref_new_value;
      temp = Current_parsing_context_qm;
      result = parsing_context_adjust_cursor_position(temp,
	      lengthw(ISVREF(Current_parsing_context_qm,(SI_Long)110L)));
      MVS_8(result,ok,endable_p,longest_common_completion_qm,
	      category_choices,completion_choices,token_complete_p,
	      token_data,copy_of_gripe);
      temp = package_return_values_from_parsing_rpc(ok,endable_p,
	      longest_common_completion_qm,category_choices,
	      completion_choices,token_complete_p,token_data,copy_of_gripe);
      clear_parsing_context(Current_parsing_context_qm);
      remove_parsing_context(Current_parsing_context_qm);
      value_1 = temp;
    POP_SPECIAL();
    reclaim_text_string(the_text_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

static Object Qg2_parsing_context_get_text;  /* g2-parsing-context-get-text */

/* G2-PARSING-CONTEXT-GET-TEXT-SYSTEM-RPC-INTERNAL */
Object g2_parsing_context_get_text_system_rpc_internal(gensymed_symbol,
	    parsing_context_handle)
    Object gensymed_symbol, parsing_context_handle;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, interface_qm;
    Object frame, symbol, sub_class_bit_vector, top_of_stack, message_1;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp_1, error_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,181);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    interface_qm = Current_system_rpc_icp_socket_qm ? 
		    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : 
		    Qnil;
	    temp =  !TRUEP(interface_qm);
	    if (temp);
	    else {
		frame = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L);
		symbol = Qui_client_interface;
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(symbol,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
			temp = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		temp =  !temp;
	    }
	    if (temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(3,
			string_constant_6,Qg2_parsing_context_get_text,
			ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L));
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    result = g2_parsing_context_get_text(parsing_context_handle);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp_1;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_23;  /* "There is no parsing-context for handle ~d." */

/* G2-PARSING-CONTEXT-GET-TEXT */
Object g2_parsing_context_get_text(parsing_context_handle_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
{
    Object parsing_context_handle, value_1, current_parsing_context_qm;
    Object top_of_stack, message_1, temp;
    Declare_special(1);

    x_note_fn_call(248,182);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if ( !TRUEP(Current_parsing_context_qm)) {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_23,
		  parsing_context_handle);
	  value_1 = raw_stack_error_named_error(top_of_stack,message_1);
      }
      else
	  value_1 = ISVREF(Current_parsing_context_qm,(SI_Long)110L);
    POP_SPECIAL();
    temp = copy_as_wide_string(value_1);
    return VALUES_1(temp);
}

static Object Qg2_clear_parsing_context;  /* g2-clear-parsing-context */

/* G2-SET-EDITING-CONTEXT-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_set_editing_context_item_system_rpc_internal(rpc_instance,
	    parsing_context_handle,item)
    Object rpc_instance, parsing_context_handle, item;
{
    Object current_parsing_context_qm, svref_arg_1;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Declare_special(1);

    x_note_fn_call(248,183);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_clear_parsing_context,
	    Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if ( !TRUEP(Current_parsing_context_qm))
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	  svref_arg_1 = Current_parsing_context_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)3L)) = item;
	  svref_arg_1 = Current_parsing_context_qm;
	  frame_serial_number_setf_arg = ISVREF(item,(SI_Long)3L);
	  old = ISVREF(svref_arg_1,(SI_Long)4L);
	  new_1 = frame_serial_number_setf_arg;
	  svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		  (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		  frame_serial_number_setf_helper_1(old,new_1);
	  SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
	  return_from_system_defined_rpc(rpc_instance,
		  eval_cons_1(Evaluation_true_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* G2-CLEAR-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL */
Object g2_clear_parsing_context_system_rpc_internal(rpc_instance,
	    parsing_context_handle)
    Object rpc_instance, parsing_context_handle;
{
    Object current_parsing_context_qm;
    Declare_special(1);

    x_note_fn_call(248,184);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_clear_parsing_context,
	    Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if (Current_parsing_context_qm) {
	      clear_parsing_context(Current_parsing_context_qm);
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_true_value,Nil));
	  }
	  else
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* G2-CLEAR-PARSING-CONTEXT */
Object g2_clear_parsing_context(parsing_context_handle_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
{
    Object parsing_context_handle, value_1, current_parsing_context_qm, temp;
    Declare_special(1);

    x_note_fn_call(248,185);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  clear_parsing_context(Current_parsing_context_qm);
	  value_1 = Truth;
      }
      else
	  value_1 = Falsity;
    POP_SPECIAL();
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

static Object Qg2_delete_parsing_context;  /* g2-delete-parsing-context */

/* G2-DELETE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL */
Object g2_delete_parsing_context_system_rpc_internal(rpc_instance,
	    parsing_context_handle)
    Object rpc_instance, parsing_context_handle;
{
    x_note_fn_call(248,186);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_delete_parsing_context,
	    Qui_client_interface))
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(g2_delete_parsing_context(parsing_context_handle),
		Nil));
    return VALUES_1(Nil);
}

/* G2-DELETE-PARSING-CONTEXT */
Object g2_delete_parsing_context(parsing_context_handle_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
{
    Object parsing_context_handle, value_1, current_parsing_context_qm, temp;
    Declare_special(1);

    x_note_fn_call(248,187);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  remove_parsing_context(parsing_context_handle);
	  value_1 = Truth;
      }
      else
	  value_1 = Falsity;
    POP_SPECIAL();
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

static Object Qg2_commit_parse_result;  /* g2-commit-parse-result */

/* G2-COMMIT-PARSE-RESULT-SYSTEM-RPC-INTERNAL */
Object g2_commit_parse_result_system_rpc_internal(rpc_instance,
	    parsing_context_handle,item,editing_for_runtime_change_p)
    Object rpc_instance, parsing_context_handle, item;
    Object editing_for_runtime_change_p;
{
    Object current_parsing_context_qm, svref_arg_1;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Object structure_to_return, top_of_stack, message_1;
    Declare_special(1);

    x_note_fn_call(248,188);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_commit_parse_result,
	    Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if (Current_parsing_context_qm) {
	      svref_arg_1 = Current_parsing_context_qm;
	      SVREF(svref_arg_1,FIX((SI_Long)3L)) = item;
	      svref_arg_1 = Current_parsing_context_qm;
	      frame_serial_number_setf_arg = ISVREF(item,(SI_Long)3L);
	      old = ISVREF(svref_arg_1,(SI_Long)4L);
	      new_1 = frame_serial_number_setf_arg;
	      svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		      (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		      frame_serial_number_setf_helper_1(old,new_1);
	      SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
	      structure_to_return = 
		      g2_compile_parse_result(parsing_context_handle,
		      editing_for_runtime_change_p);
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(structure_to_return,Nil));
	  }
	  else {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(2,
		      string_constant_23,parsing_context_handle);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qg2_compile_parse_result;  /* g2-compile-parse-result */

/* G2-COMPILE-PARSE-RESULT-SYSTEM-RPC-INTERNAL */
Object g2_compile_parse_result_system_rpc_internal(rpc_instance,
	    parsing_context_handle,editing_for_runtime_change_p)
    Object rpc_instance, parsing_context_handle, editing_for_runtime_change_p;
{
    Object structure_to_return;

    x_note_fn_call(248,189);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_compile_parse_result,
	    Qui_client_interface)) {
	structure_to_return = 
		g2_compile_parse_result(parsing_context_handle,
		editing_for_runtime_change_p);
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(structure_to_return,Nil));
    }
    return VALUES_1(Nil);
}

static Object Qok;                 /* ok */

static Object Qdescription;        /* description */

static Object Qerror_index;        /* error-index */

/* G2-COMPILE-PARSE-RESULT */
Object g2_compile_parse_result(parsing_context_handle_as_evaluation_value,
	    editing_for_runtime_change_p_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
    Object editing_for_runtime_change_p_as_evaluation_value;
{
    Object parsing_context_handle, editing_for_runtime_change_p, value_1;
    Object current_parsing_context_qm, ok, error_text, error_index;
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    Object top_of_stack, message_1, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,190);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    editing_for_runtime_change_p = 
	    M_CAR(editing_for_runtime_change_p_as_evaluation_value);
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  if (EQ(editing_for_runtime_change_p,Truth))
	      editing_for_runtime_change_p = T;
	  else if (EQ(editing_for_runtime_change_p,Falsity))
	      editing_for_runtime_change_p = Nil;
	  result = commit_parse_result(Current_parsing_context_qm,
		  editing_for_runtime_change_p);
	  MVS_3(result,ok,error_text,error_index);
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qok;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qok;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = ok ? Evaluation_true_value : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = ok ? Evaluation_true_value : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qdescription;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qdescription;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = error_text;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = error_text;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qerror_index;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qerror_index;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = error_index ? error_index : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = error_index ? error_index : 
		      Evaluation_false_value;
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	  }
	  value_1 = eval_cons_1(gensymed_symbol,Qab_structure);
      }
      else {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_23,
		  parsing_context_handle);
	  value_1 = raw_stack_error_named_error(top_of_stack,message_1);
      }
    POP_SPECIAL();
    if ( !(EQ(editing_for_runtime_change_p_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(editing_for_runtime_change_p_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(editing_for_runtime_change_p_as_evaluation_value);
    temp_2 = IDENTITY(value_1);
    return VALUES_1(temp_2);
}

static Object Qframe_is_null_or_reprocessed;  /* frame-is-null-or-reprocessed */

static Object array_constant;      /* # */

static Object Qparse_is_bad;       /* parse-is-bad */

static Object array_constant_1;    /* # */

static Object Qparse_is_incomplete;  /* parse-is-incomplete */

static Object array_constant_2;    /* # */

static Object Qparse_is_ambiguous;  /* parse-is-ambiguous */

static Object array_constant_3;    /* # */

/* COMMIT-PARSE-RESULT */
Object commit_parse_result(current_parsing_context_qm,
	    editing_for_runtime_change_p)
    Object current_parsing_context_qm, editing_for_runtime_change_p;
{
    Object item, flag_or_error_text_or_nil, gensymed_symbol, x, y, xa, ya;
    Object error_text, temp_1, temp_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,191);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      item = Nil;
      flag_or_error_text_or_nil = Nil;
      if ( !TRUEP(Current_parsing_context_qm))
	  flag_or_error_text_or_nil = Qframe_is_null_or_reprocessed;
      else {
	  item = ISVREF(Current_parsing_context_qm,(SI_Long)3L);
	  temp =  !TRUEP(item);
	  if (temp);
	  else {
	      gensymed_symbol = ISVREF(item,(SI_Long)3L);
	      temp = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			  == (SI_Long)-1L : TRUEP(Nil);
	      if (temp);
	      else {
		  x = gensymed_symbol;
		  y = ISVREF(Current_parsing_context_qm,(SI_Long)4L);
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
			  temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				  M_CDR(x)) : TRUEP(Qnil);
		  }
	      }
	  }
	  if (temp)
	      flag_or_error_text_or_nil = Qframe_is_null_or_reprocessed;
	  else {
	      complete_and_extend_final_token_if_necessary(Current_parsing_context_qm);
	      flag_or_error_text_or_nil = 
		      end_editorless_parsing(Current_parsing_context_qm,
		      item,editing_for_runtime_change_p);
	  }
      }
      if (flag_or_error_text_or_nil) {
	  if (SYMBOLP(flag_or_error_text_or_nil)) {
	      if (EQ(flag_or_error_text_or_nil,Qframe_is_null_or_reprocessed))
		  error_text = array_constant;
	      else if (EQ(flag_or_error_text_or_nil,Qparse_is_bad))
		  error_text = array_constant_1;
	      else if (EQ(flag_or_error_text_or_nil,Qparse_is_incomplete))
		  error_text = array_constant_2;
	      else if (EQ(flag_or_error_text_or_nil,Qparse_is_ambiguous))
		  error_text = array_constant_3;
	      else
		  error_text = Qnil;
	      temp_1 = copy_text_string(error_text);
	      temp_2 = ISVREF(Current_parsing_context_qm,(SI_Long)107L);
	      result = VALUES_3(Nil,temp_1,temp_2);
	  }
	  else {
	      temp_1 = copy_text_string(flag_or_error_text_or_nil);
	      temp_2 = ISVREF(Current_parsing_context_qm,(SI_Long)107L);
	      result = VALUES_3(Nil,temp_1,temp_2);
	  }
      }
      else
	  result = VALUES_3(T,Nil,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_update_parsing_context;  /* g2-update-parsing-context */

static Object array_constant_4;    /* # */

/* G2-UPDATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL */
Object g2_update_parsing_context_system_rpc_internal(rpc_instance,
	    parsing_context_handle,backup_index_qm,advance_index_qm,the_text)
    Object rpc_instance, parsing_context_handle, backup_index_qm;
    Object advance_index_qm, the_text;
{
    Object current_parsing_context_qm, copy_of_gripe, parse_status;
    Object svref_arg_1, temp, current_edit_state, start_index, advance_string;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(248,192);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_update_parsing_context,
	    Qui_client_interface)) {
	if ( !FIXNUMP(backup_index_qm))
	    backup_index_qm = Nil;
	if ( !FIXNUMP(advance_index_qm))
	    advance_index_qm = Nil;
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	copy_of_gripe = Nil;
	parse_status = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		1);
	  if ( !TRUEP(string_equalw(ISVREF(Current_parsing_context_qm,
		  (SI_Long)110L),array_constant_4)))
	      reclaim_text_string(ISVREF(Current_parsing_context_qm,
		      (SI_Long)110L));
	  svref_arg_1 = Current_parsing_context_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)110L)) = the_text;
	  if (advance_index_qm) {
	      temp = advance_index_qm;
	      temp_1 = FIXNUM_GT(temp,lengthw(the_text));
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      advance_index_qm = lengthw(the_text);
	  if (Current_parsing_context_qm) {
	      if (ISVREF(Current_parsing_context_qm,(SI_Long)11L))
		  return_from_parsing_rpc_with_cursor_relative_prompt_and_status_data(rpc_instance,
			  Current_parsing_context_qm,Nil,Nil);
	      else {
		  current_edit_state = Current_parsing_context_qm;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			  0);
		    start_index = ISVREF(Current_parsing_context_qm,
			    (SI_Long)108L);
		    if (backup_index_qm) {
			result = retreat_parsing_context(Current_parsing_context_qm,
				backup_index_qm);
			MVS_2(result,parse_status,copy_of_gripe);
			if (copy_of_gripe)
			    copy_of_gripe = copy_text_string(copy_of_gripe);
		    }
		    else if (advance_index_qm) {
			if (FIXNUM_GT(advance_index_qm,start_index)) {
			    advance_string = 
				    copy_text_string_portion(the_text,
				    start_index,advance_index_qm);
			    result = advance_parsing_context(Current_parsing_context_qm,
				    advance_string);
			    MVS_2(result,parse_status,copy_of_gripe);
			    if (copy_of_gripe)
				copy_of_gripe = 
					copy_text_string(copy_of_gripe);
			}
			else if (FIXNUM_EQ(advance_index_qm,start_index));
			else if (FIXNUM_LT(advance_index_qm,start_index)) {
			    svref_arg_1 = Current_parsing_context_qm;
			    SVREF(svref_arg_1,FIX((SI_Long)110L)) = 
				    array_constant_4;
			    clear_parsing_context(Current_parsing_context_qm);
			    advance_string = 
				    copy_text_string_portion(the_text,
				    FIX((SI_Long)0L),advance_index_qm);
			    result = advance_parsing_context(Current_parsing_context_qm,
				    advance_string);
			    MVS_2(result,parse_status,copy_of_gripe);
			    if (copy_of_gripe)
				copy_of_gripe = 
					copy_text_string(copy_of_gripe);
			}
		    }
		    return_from_parsing_rpc_with_cursor_relative_prompt_and_status_data(rpc_instance,
			    Current_parsing_context_qm,parse_status,
			    copy_of_gripe);
		  POP_SPECIAL();
	      }
	  }
	  else
	      maybe_return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object list_constant_3;     /* # */

/* RETURN-VALUES-WITH-CURSOR-RELATIVE-PROMPT-AND-STATUS-DATA */
Object return_values_with_cursor_relative_prompt_and_status_data varargs_1(int, n)
{
    Object current_parsing_context_qm;
    Object copy_of_gripe, cursor_token, token_data;
    Object got_prompts_from_prior_token_qm, temp, category_choices;
    Object completion_choices, longest_common_completion_qm, can_end_qm;
    Object temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,193);
    INIT_ARGS_nonrelocating();
    current_parsing_context_qm = REQUIRED_ARG_nonrelocating();
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      copy_of_gripe = OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      END_ARGS_nonrelocating();
      if (ISVREF(Current_parsing_context_qm,(SI_Long)11L))
	  result = VALUES_7(T,T,Nil,Nil,Nil,Nil,list_constant_3);
      else {
	  cursor_token = ISVREF(Current_parsing_context_qm,(SI_Long)105L);
	  token_data = phrase_list_3(ISVREF(cursor_token,(SI_Long)12L),
		  ISVREF(cursor_token,(SI_Long)7L),ISVREF(cursor_token,
		  (SI_Long)8L));
	  got_prompts_from_prior_token_qm = Nil;
	  if ( !TRUEP(ISVREF(Current_parsing_context_qm,(SI_Long)107L))) {
	      if (( !TRUEP(ISVREF(cursor_token,(SI_Long)4L)) || 
		      comment_token_p(cursor_token)) && 
		      ISVREF(cursor_token,(SI_Long)2L)) {
		  got_prompts_from_prior_token_qm = T;
		  temp = maybe_skip_comment_tokens(ISVREF(cursor_token,
			  (SI_Long)2L));
	      }
	      else
		  temp = cursor_token;
	      result = compute_parsing_context_prompts(temp);
	  }
	  else
	      result = VALUES_1(Nil);
	  MVS_4(result,category_choices,completion_choices,
		  longest_common_completion_qm,can_end_qm);
	  temp_1 =  !TRUEP(ISVREF(Current_parsing_context_qm,
		  (SI_Long)107L)) ? T : Nil;
	  temp =  !TRUEP(parsing_token_incomplete_p(cursor_token)) ? T : Nil;
	  result = VALUES_8(temp_1,can_end_qm,longest_common_completion_qm,
		  category_choices,completion_choices,temp,token_data,
		  copy_of_gripe);
      }
    POP_SPECIAL();
    return result;
}

/* RETURN-FROM-PARSING-RPC-WITH-CURSOR-RELATIVE-PROMPT-AND-STATUS-DATA */
Object return_from_parsing_rpc_with_cursor_relative_prompt_and_status_data(rpc_instance,
	    current_parsing_context_qm,parse_status,copy_of_gripe)
    Object rpc_instance, current_parsing_context_qm, parse_status;
    Object copy_of_gripe;
{
    Object ok, endable_p, longest_common_completion_qm, category_choices;
    Object completion_choices, token_complete_p, token_data;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,194);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      result = return_values_with_cursor_relative_prompt_and_status_data(1,
	      Current_parsing_context_qm);
      MVS_7(result,ok,endable_p,longest_common_completion_qm,
	      category_choices,completion_choices,token_complete_p,token_data);
      result = maybe_return_from_system_defined_rpc(rpc_instance,
	      eval_cons_1(package_return_values_from_parsing_rpc(ok,
	      endable_p,longest_common_completion_qm,category_choices,
	      completion_choices,token_complete_p,token_data,
	      copy_of_gripe),Nil));
    POP_SPECIAL();
    return result;
}

static Object Qtoken_complete_p;   /* token-complete-p */

static Object Qtoken_data;         /* token-data */

/* PACKAGE-RETURN-VALUES-FROM-PARSING-RPC */
Object package_return_values_from_parsing_rpc(ok,endable_p,
	    longest_common_completion_qm,category_choices,
	    completion_choices,token_complete_p,token_data,copy_of_gripe)
    Object ok, endable_p, longest_common_completion_qm, category_choices;
    Object completion_choices, token_complete_p, token_data, copy_of_gripe;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(248,195);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)18L + 
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qok;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qok;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ok ? Evaluation_true_value : Evaluation_false_value;
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
	item_or_value = ok ? Evaluation_true_value : Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qendable_p;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qendable_p;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = endable_p ? Evaluation_true_value : 
		Evaluation_false_value;
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
	item_or_value = endable_p ? Evaluation_true_value : 
		Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qdescription;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qdescription;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = copy_of_gripe ? copy_of_gripe : Evaluation_false_value;
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
	item_or_value = copy_of_gripe ? copy_of_gripe : Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qerror_index;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qerror_index;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = ISVREF(Current_parsing_context_qm,(SI_Long)107L) ? 
		ISVREF(Current_parsing_context_qm,(SI_Long)107L) : 
		Evaluation_false_value;
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
	item_or_value = ISVREF(Current_parsing_context_qm,(SI_Long)107L) ? 
		ISVREF(Current_parsing_context_qm,(SI_Long)107L) : 
		Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qlongest_common_completion;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qlongest_common_completion;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = longest_common_completion_qm;
	if (item_or_value);
	else
	    item_or_value = Evaluation_false_value;
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
	item_or_value = longest_common_completion_qm;
	if (item_or_value);
	else
	    item_or_value = Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qcategory_choices;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)11L)) = Qcategory_choices;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(category_choices));
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
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(category_choices));
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qcompletion_choices;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)13L)) = Qcompletion_choices;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(completion_choices));
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
	SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(completion_choices));
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qtoken_complete_p;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)15L)) = Qtoken_complete_p;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = token_complete_p ? Evaluation_true_value : 
		Evaluation_false_value;
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
	SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = token_complete_p ? Evaluation_true_value : 
		Evaluation_false_value;
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)19L)) = Qtoken_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)17L)) = Qtoken_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(token_data));
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
	SVREF(gensymed_symbol,FIX((SI_Long)20L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(token_data));
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
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)18L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qg2_shift_cursor_position;  /* g2-shift-cursor-position */

/* G2-SHIFT-CURSOR-POSITION-SYSTEM-RPC-INTERNAL */
Object g2_shift_cursor_position_system_rpc_internal(rpc_instance,
	    parsing_context_handle,new_position,the_text)
    Object rpc_instance, parsing_context_handle, new_position, the_text;
{
    Object current_parsing_context_qm, svref_arg_1;
    Declare_special(1);

    x_note_fn_call(248,196);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_shift_cursor_position,
	    Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if (Current_parsing_context_qm) {
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(the_text) != (SI_Long)0L) {
		  if ( 
			  !TRUEP(string_equalw(ISVREF(Current_parsing_context_qm,
			  (SI_Long)110L),array_constant_4)))
		      reclaim_text_string(ISVREF(Current_parsing_context_qm,
			      (SI_Long)110L));
		  svref_arg_1 = Current_parsing_context_qm;
		  SVREF(svref_arg_1,FIX((SI_Long)110L)) = the_text;
	      }
	      maybe_return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(g2_adjust_cursor_position(parsing_context_handle,
		      FIXNUM_ADD1(new_position)),Nil));
	  }
	  else
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qg2_adjust_cursor_position;  /* g2-adjust-cursor-position */

/* G2-ADJUST-CURSOR-POSITION-SYSTEM-RPC-INTERNAL */
Object g2_adjust_cursor_position_system_rpc_internal(rpc_instance,
	    parsing_context_handle,new_position)
    Object rpc_instance, parsing_context_handle, new_position;
{
    Object current_parsing_context_qm;
    Declare_special(1);

    x_note_fn_call(248,197);
    if (rpc_interface_class_ok_qm(rpc_instance,Qg2_adjust_cursor_position,
	    Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if (Current_parsing_context_qm)
	      maybe_return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(g2_adjust_cursor_position(parsing_context_handle,
		      new_position),Nil));
	  else
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object string_constant_24;  /* "Position ~a invalid for g2-adjust-cursor-position" */

/* G2-ADJUST-CURSOR-POSITION */
Object g2_adjust_cursor_position(parsing_context_handle_as_evaluation_value,
	    new_position_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
    Object new_position_as_evaluation_value;
{
    Object parsing_context_handle, new_position, value_1;
    Object current_parsing_context_qm, temp, top_of_stack, message_1, ok;
    Object endable_p, longest_common_completion_qm, category_choices;
    Object completion_choices, token_complete_p, token_data, copy_of_gripe;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,198);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    new_position = new_position_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  temp = add1(lengthw(ISVREF(Current_parsing_context_qm,
		  (SI_Long)110L)));
	  if (NUM_GT(new_position,temp)) {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(2,
		      string_constant_24,new_position);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  result = parsing_context_adjust_cursor_position(Current_parsing_context_qm,
		  FIXNUM_SUB1(new_position));
	  MVS_8(result,ok,endable_p,longest_common_completion_qm,
		  category_choices,completion_choices,token_complete_p,
		  token_data,copy_of_gripe);
	  value_1 = package_return_values_from_parsing_rpc(ok,endable_p,
		  longest_common_completion_qm,category_choices,
		  completion_choices,token_complete_p,token_data,
		  copy_of_gripe);
      }
      else {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_23,
		  parsing_context_handle);
	  value_1 = raw_stack_error_named_error(top_of_stack,message_1);
      }
    POP_SPECIAL();
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* PARSING-CONTEXT-ADJUST-CURSOR-POSITION */
Object parsing_context_adjust_cursor_position(current_parsing_context_qm,
	    new_position)
    Object current_parsing_context_qm, new_position;
{
    Object current_edit_state, copy_of_gripe;
    Declare_special(2);
    Object result;

    x_note_fn_call(248,199);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    1);
      if (ISVREF(Current_parsing_context_qm,(SI_Long)11L))
	  result = return_values_with_cursor_relative_prompt_and_status_data(1,
		  Current_parsing_context_qm);
      else {
	  if (IFIX(new_position) < (SI_Long)0L)
	      new_position = lengthw(ISVREF(Current_parsing_context_qm,
		      (SI_Long)110L));
	  current_edit_state = Current_parsing_context_qm;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		  0);
	    result = shift_cursor_token(Current_parsing_context_qm,
		    new_position);
	    copy_of_gripe = NTH_VALUE((SI_Long)1L, result);
	    result = return_values_with_cursor_relative_prompt_and_status_data(2,
		    Current_parsing_context_qm,copy_of_gripe);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

/* PARSING-CONTEXT-SET-TEXT */
Object parsing_context_set_text(current_parsing_context_qm,the_text,
	    new_position)
    Object current_parsing_context_qm, the_text, new_position;
{
    Object new_text, common_position, svref_arg_1, ok, endable_p;
    Object longest_common_completion_qm, category_choices, completion_choices;
    Object token_complete_p, token_data, copy_of_gripe;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,200);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(the_text) != (SI_Long)0L) {
	  new_text = copy_wide_string(the_text);
	  common_position = mismatch(4,new_text,
		  ISVREF(Current_parsing_context_qm,(SI_Long)110L),Kend2,
		  ISVREF(Current_parsing_context_qm,(SI_Long)108L));
	  if ( !TRUEP(string_equalw(ISVREF(Current_parsing_context_qm,
		  (SI_Long)110L),array_constant_4)))
	      reclaim_text_string(ISVREF(Current_parsing_context_qm,
		      (SI_Long)110L));
	  svref_arg_1 = Current_parsing_context_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)110L)) = new_text;
	  if (ISVREF(Current_parsing_context_qm,(SI_Long)107L)) {
	      svref_arg_1 = Current_parsing_context_qm;
	      SVREF(svref_arg_1,FIX((SI_Long)107L)) = Nil;
	  }
	  if ( !TRUEP(ISVREF(Current_parsing_context_qm,(SI_Long)107L)) && 
		  ( !TRUEP(common_position) || FIXNUM_EQ(common_position,
		  ISVREF(Current_parsing_context_qm,(SI_Long)108L))))
	      result = parsing_context_adjust_cursor_position(Current_parsing_context_qm,
		      new_position);
	  else {
	      result = parsing_context_adjust_cursor_position(Current_parsing_context_qm,
		      common_position);
	      MVS_8(result,ok,endable_p,longest_common_completion_qm,
		      category_choices,completion_choices,token_complete_p,
		      token_data,copy_of_gripe);
	      if (ok ||  !TRUEP(token_complete_p))
		  result = parsing_context_adjust_cursor_position(Current_parsing_context_qm,
			  new_position);
	      else
		  result = VALUES_8(ok,endable_p,
			  longest_common_completion_qm,category_choices,
			  completion_choices,token_complete_p,token_data,
			  copy_of_gripe);
	  }
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_parsing_context_delete_characters;  /* g2-parsing-context-delete-characters */

/* G2-PARSING-CONTEXT-DELETE-CHARACTERS-SYSTEM-RPC-INTERNAL */
Object g2_parsing_context_delete_characters_system_rpc_internal(rpc_instance,
	    parsing_context_handle,position_1,number_of_chars)
    Object rpc_instance, parsing_context_handle, position_1, number_of_chars;
{
    x_note_fn_call(248,201);
    if (rpc_interface_class_ok_qm(rpc_instance,
	    Qg2_parsing_context_delete_characters,Qui_client_interface))
	maybe_return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(g2_parsing_context_delete_characters(parsing_context_handle,
		position_1,number_of_chars),Nil));
    return VALUES_1(Nil);
}

static Object string_constant_25;  /* "Error while deleting ~a characters from position ~a:  Bad string index?" */

/* G2-PARSING-CONTEXT-DELETE-CHARACTERS */
Object g2_parsing_context_delete_characters(parsing_context_handle_as_evaluation_value,
	    position_as_evaluation_value,number_of_chars_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
    Object position_as_evaluation_value, number_of_chars_as_evaluation_value;
{
    Object parsing_context_handle, position_1, number_of_chars, value_1;
    Object current_parsing_context_qm, ok, endable_p;
    Object longest_common_completion_qm, category_choices, completion_choices;
    Object token_complete_p, token_data, copy_of_gripe, top_of_stack;
    Object message_1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,202);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    position_1 = position_as_evaluation_value;
    number_of_chars = number_of_chars_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  result = parsing_context_delete_characters(Current_parsing_context_qm,
		  FIXNUM_SUB1(position_1),number_of_chars);
	  MVS_8(result,ok,endable_p,longest_common_completion_qm,
		  category_choices,completion_choices,token_complete_p,
		  token_data,copy_of_gripe);
	  if ( !TRUEP(token_data) && copy_of_gripe) {
	      reclaim_text_string(copy_of_gripe);
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(3,
		      string_constant_25,number_of_chars,position_1);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  value_1 = package_return_values_from_parsing_rpc(ok,endable_p,
		  longest_common_completion_qm,category_choices,
		  completion_choices,token_complete_p,token_data,
		  copy_of_gripe);
      }
      else {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_23,
		  parsing_context_handle);
	  value_1 = raw_stack_error_named_error(top_of_stack,message_1);
      }
    POP_SPECIAL();
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* PARSING-CONTEXT-DELETE-CHARACTERS */
Object parsing_context_delete_characters(current_parsing_context_qm,
	    position_1,number_of_chars)
    Object current_parsing_context_qm, position_1, number_of_chars;
{
    Object temp, g2_position, new_string_qm, svref_arg_1, gensymed_symbol;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,203);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      temp = ISVREF(Current_parsing_context_qm,(SI_Long)108L);
      if (NUM_LT(position_1,temp))
	  retreat_parsing_context(Current_parsing_context_qm,position_1);
      g2_position = FIXNUM_ADD1(position_1);
      new_string_qm = omit_from_g2_text(ISVREF(Current_parsing_context_qm,
	      (SI_Long)110L),g2_position,add(g2_position,
	      FIXNUM_SUB1(number_of_chars)));
      if (new_string_qm) {
	  if ( !TRUEP(string_equalw(ISVREF(Current_parsing_context_qm,
		  (SI_Long)110L),array_constant_4)))
	      reclaim_text_string(ISVREF(Current_parsing_context_qm,
		      (SI_Long)110L));
	  svref_arg_1 = Current_parsing_context_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)110L)) = new_string_qm;
	  result = adjust_after_insert_sl_delete(Current_parsing_context_qm,
		  position_1);
      }
      else {
	  gensymed_symbol = tformat_text_string(3,string_constant_25,
		  number_of_chars,position_1);
	  result = VALUES_8(Nil,Nil,Nil,Nil,Nil,Nil,Nil,gensymed_symbol);
      }
    POP_SPECIAL();
    return result;
}

static Object Qg2_parsing_context_insert_characters;  /* g2-parsing-context-insert-characters */

/* G2-PARSING-CONTEXT-INSERT-CHARACTERS-SYSTEM-RPC-INTERNAL */
Object g2_parsing_context_insert_characters_system_rpc_internal(rpc_instance,
	    parsing_context_handle,position_1,addition)
    Object rpc_instance, parsing_context_handle, position_1, addition;
{
    x_note_fn_call(248,204);
    if (rpc_interface_class_ok_qm(rpc_instance,
	    Qg2_parsing_context_insert_characters,Qui_client_interface))
	return_from_system_defined_rpc(rpc_instance,
		eval_cons_1(g2_parsing_context_insert_characters(parsing_context_handle,
		position_1,addition),Nil));
    return VALUES_1(Nil);
}

static Object string_constant_26;  /* "Error while inserting characters:  Bad string index ~a or invalid string." */

/* G2-PARSING-CONTEXT-INSERT-CHARACTERS */
Object g2_parsing_context_insert_characters(parsing_context_handle_as_evaluation_value,
	    position_as_evaluation_value,addition_as_evaluation_value)
    Object parsing_context_handle_as_evaluation_value;
    Object position_as_evaluation_value, addition_as_evaluation_value;
{
    Object parsing_context_handle, position_1, addition, value_1;
    Object current_parsing_context_qm, ok, endable_p;
    Object longest_common_completion_qm, category_choices, completion_choices;
    Object token_complete_p, token_data, copy_of_gripe, top_of_stack;
    Object message_1, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,205);
    parsing_context_handle = parsing_context_handle_as_evaluation_value;
    position_1 = position_as_evaluation_value;
    addition = addition_as_evaluation_value;
    value_1 = Nil;
    current_parsing_context_qm = get_parsing_context(parsing_context_handle);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      if (Current_parsing_context_qm) {
	  result = parsing_context_insert_characters(Current_parsing_context_qm,
		  FIXNUM_SUB1(position_1),addition);
	  MVS_8(result,ok,endable_p,longest_common_completion_qm,
		  category_choices,completion_choices,token_complete_p,
		  token_data,copy_of_gripe);
	  if ( !TRUEP(token_data) && copy_of_gripe) {
	      reclaim_text_string(copy_of_gripe);
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(2,
		      string_constant_26,position_1);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  value_1 = package_return_values_from_parsing_rpc(ok,endable_p,
		  longest_common_completion_qm,category_choices,
		  completion_choices,token_complete_p,token_data,
		  copy_of_gripe);
      }
      else {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_23,
		  parsing_context_handle);
	  value_1 = raw_stack_error_named_error(top_of_stack,message_1);
      }
    POP_SPECIAL();
    reclaim_text_string(addition_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* PARSING-CONTEXT-INSERT-CHARACTERS */
Object parsing_context_insert_characters(current_parsing_context_qm,
	    position_1,addition)
    Object current_parsing_context_qm, position_1, addition;
{
    Object temp, g2_position, new_string_qm, svref_arg_1, gensymed_symbol;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,206);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    0);
      temp = ISVREF(Current_parsing_context_qm,(SI_Long)108L);
      if (NUM_LT(position_1,temp))
	  retreat_parsing_context(Current_parsing_context_qm,position_1);
      g2_position = FIXNUM_ADD1(position_1);
      new_string_qm = insert_in_g2_text(addition,
	      ISVREF(Current_parsing_context_qm,(SI_Long)110L),g2_position);
      if (new_string_qm) {
	  if ( !TRUEP(string_equalw(ISVREF(Current_parsing_context_qm,
		  (SI_Long)110L),array_constant_4)))
	      reclaim_text_string(ISVREF(Current_parsing_context_qm,
		      (SI_Long)110L));
	  svref_arg_1 = Current_parsing_context_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)110L)) = new_string_qm;
	  temp = Current_parsing_context_qm;
	  result = adjust_after_insert_sl_delete(temp,add(position_1,
		  lengthw(addition)));
      }
      else {
	  gensymed_symbol = tformat_text_string(2,string_constant_26,
		  position_1);
	  result = VALUES_8(Nil,Nil,Nil,Nil,Nil,Nil,Nil,gensymed_symbol);
      }
    POP_SPECIAL();
    return result;
}

/* ADJUST-AFTER-INSERT/DELETE */
Object adjust_after_insert_sl_delete(current_parsing_context_qm,position_1)
    Object current_parsing_context_qm, position_1;
{
    Object current_edit_state, copy_of_gripe;
    Declare_special(2);
    Object result;

    x_note_fn_call(248,207);
    PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
	    1);
      if (ISVREF(Current_parsing_context_qm,(SI_Long)11L))
	  result = return_values_with_cursor_relative_prompt_and_status_data(1,
		  Current_parsing_context_qm);
      else {
	  current_edit_state = Current_parsing_context_qm;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		  0);
	    result = shift_cursor_token(Current_parsing_context_qm,position_1);
	    copy_of_gripe = NTH_VALUE((SI_Long)1L, result);
	    result = return_values_with_cursor_relative_prompt_and_status_data(2,
		    Current_parsing_context_qm,copy_of_gripe);
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    return result;
}

static Object Qg2_menu_of_names_for_category;  /* g2-menu-of-names-for-category */

static Object Qtoken_prompts_for_category;  /* token-prompts-for-category */

/* G2-MENU-OF-NAMES-FOR-CATEGORY-SYSTEM-RPC-INTERNAL */
Object g2_menu_of_names_for_category_system_rpc_internal(rpc_instance,
	    category_symbol,parsing_context_handle)
    Object rpc_instance, category_symbol, parsing_context_handle;
{
    Object current_parsing_context_qm, cursor_token, prefix_string_qm, list_1;
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(248,208);
    if (rpc_interface_class_ok_qm(rpc_instance,
	    Qg2_menu_of_names_for_category,Qui_client_interface)) {
	current_parsing_context_qm = 
		get_parsing_context(parsing_context_handle);
	PUSH_SPECIAL_WITH_SYMBOL(Current_parsing_context_qm,Qcurrent_parsing_context_qm,current_parsing_context_qm,
		0);
	  if (Current_parsing_context_qm) {
	      cursor_token = ISVREF(Current_parsing_context_qm,(SI_Long)105L);
	      prefix_string_qm = parsing_token_incomplete_p(cursor_token) ?
		       ISVREF(cursor_token,(SI_Long)9L) : Nil;
	      list_1 = make_menu_of_names_from_directory(category_symbol,
		      prefix_string_qm);
	      if (Trace_parsing_context_p)
		  format((SI_Long)5L,T,
			  "~%~%~%>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>~%Menu of names for ~a with prefix \"~a\" =~%~a",
			  category_symbol,prefix_string_qm,list_1);
	      if (list_1) {
		  gensymed_symbol = allocate_managed_array(1,
			  FIX((SI_Long)2L + (SI_Long)1L));
		  gensymed_symbol_1 = (SI_Long)0L;
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = gensymed_symbol_1 + 
			      IFIX(Managed_array_index_offset);
		      ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		  }
		  else {
		      temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  
			      -  - (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		      ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size))
		      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
			      Qtoken_prompts_for_category;
		  else {
		      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		      SVREF(temp,FIX((SI_Long)1L)) = 
			      Qtoken_prompts_for_category;
		  }
		  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      item_or_value = 
			      allocate_evaluation_sequence(copy_list_using_eval_conses_1(list_1));
		      if (SIMPLE_VECTOR_P(item_or_value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value,(SI_Long)1L);
			  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      temp = temp_1 ? get_reference_to_item(item_or_value) 
			      : item_or_value;
		      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
		  }
		  else {
		      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		      item_or_value = 
			      allocate_evaluation_sequence(copy_list_using_eval_conses_1(list_1));
		      if (SIMPLE_VECTOR_P(item_or_value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			      > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(item_or_value,(SI_Long)1L);
			  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      svref_new_value = temp_1 ? 
			      get_reference_to_item(item_or_value) : 
			      item_or_value;
		      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
		  }
		  return_from_system_defined_rpc(rpc_instance,
			  eval_cons_1(eval_cons_1(gensymed_symbol,
			  Qab_structure),Nil));
	      }
	      else
		  return_from_system_defined_rpc(rpc_instance,
			  eval_cons_1(Evaluation_false_value,Nil));
	  }
	  else
	      return_from_system_defined_rpc(rpc_instance,
		      eval_cons_1(Evaluation_false_value,Nil));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* BLANK-TEXT-STRING-P */
Object blank_text_string_p(text_string)
    Object text_string;
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(248,209);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(text_string_length(text_string));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !(UBYTE_16_ISAREF_1(text_string,i) == (SI_Long)32L))
	return VALUES_1(Nil);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

static Object Qname_or_names;      /* name-or-names */

static Object Qtext;               /* text */

/* CONVERT-INTERNAL-SLOT-VALUE */
Object convert_internal_slot_value(category_qm,category_function_qm,
	    slot_features,frame,value)
    Object category_qm, category_function_qm, slot_features, frame, value;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, converted_value_qm, temp, type_of_slot_component;

    x_note_fn_call(248,210);
    if (category_function_qm) {
	gensymed_symbol = category_function_qm;
	gensymed_symbol_1 = value;
	gensymed_symbol_2 = frame;
	gensymed_symbol_3 = Nil;
	converted_value_qm = inline_funcall_3(gensymed_symbol,
		gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	converted_value_qm = Nil;
    if (converted_value_qm)
	temp = converted_value_qm;
    else if (EQ(category_qm,Qname_or_names)) {
	if ( !TRUEP(value))
	    temp = Nil;
	else if (LISTP(value))
	    temp = 
		    allocate_evaluation_sequence(copy_list_using_eval_conses_1(value));
	else if (SYMBOLP(value))
	    temp = value;
	else
	    temp = Qt;
    }
    else if (category_function_qm &&  !TRUEP(converted_value_qm))
	temp = Nil;
    else {
	type_of_slot_component = assq_function(Qtype,slot_features);
	temp = memq_function(Qtext,CDDR(type_of_slot_component)) ? 
		text_slot_value_to_evaluation_text(frame,value,
		type_of_slot_component) : Nil;
    }
    return VALUES_1(temp);
}

static Object Qtrend_chart;        /* trend-chart */

static Object Qslot_name;          /* slot-name */

static Object Qslot_component_name;  /* slot-component-name */

static Object Qslot_component_alias;  /* slot-component-alias */

static Object Qchart_element_uid;  /* chart-element-uid */

static Object Qslot_change;        /* slot-change */

/* SEND-TREND-CHART-SLOT-CHANGE */
Object send_trend_chart_slot_change(trend_chart,slot_name,
	    slot_component_name,new_value,old_value,
	    slot_component_indicator_qm)
    Object trend_chart, slot_name, slot_component_name, new_value, old_value;
    Object slot_component_indicator_qm;
{
    Object body_evaluated_p, notification_body, frame_list, class_name;
    Object new_list, frame, ab_loop_list_, gensymed_symbol;
    Object sub_class_bit_vector, representations;
    Object current_frame_serial_number_on_entry, representation, xa, ya;
    Object slot_features, category_spec_qm, category_qm;
    Object category_evaluator_interface, category_function_qm;
    Object exported_new_value, temp_1, item_or_value, x2, temp_2;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    Object gensymed_symbol_4, temp_3, address, subscription_handle, socket_1;
    Object argument_list;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp;
    double aref_new_value;

    x_note_fn_call(248,211);
    if ( !EQUAL(new_value,old_value)) {
	body_evaluated_p = Nil;
	notification_body = Nil;
	frame_list = ISVREF(trend_chart,(SI_Long)9L);
	class_name = Qtc_representation;
	new_list = Qnil;
	frame = Nil;
	ab_loop_list_ = frame_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	    new_list = gensym_cons_1(frame,new_list);
	goto next_loop;
      end_loop:
	representations = new_list;
	goto end_1;
	representations = Qnil;
      end_1:;
	current_frame_serial_number_on_entry = 
		copy_frame_serial_number(Current_frame_serial_number);
	representation = Nil;
	ab_loop_list_ = representations;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	representation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(representation,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(representation) ? EQ(ISVREF(representation,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(current_frame_serial_number_on_entry))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(current_frame_serial_number_on_entry,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(current_frame_serial_number_on_entry);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(current_frame_serial_number_on_entry),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp ? TRUEP(representation_address_valid_p(representation)) 
		: TRUEP(Nil)) {
	    if ( !TRUEP(body_evaluated_p)) {
		slot_features = get_slot_component_features(slot_name,
			lookup_global_or_kb_specific_property_value(Qtrend_chart,
			Class_description_gkbprop),slot_component_name);
		category_spec_qm = assq_function(Qtype,slot_features);
		category_qm = category_spec_qm ? CADR(category_spec_qm) : Qnil;
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			Qcategory_evaluator_interface);
		category_function_qm = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		exported_new_value = 
			convert_internal_slot_value(category_qm,
			category_function_qm,slot_features,trend_chart,
			new_value);
		gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L 
			+ (SI_Long)1L));
		gensymed_symbol_1 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_1 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qslot_name;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)1L)) = Qslot_name;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    get_alias_for_slot_name_if_any(slot_name,
			    trend_chart);
		    if (item_or_value);
		    else
			item_or_value = slot_name;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = 
			    get_alias_for_slot_name_if_any(slot_name,
			    trend_chart);
		    if (item_or_value);
		    else
			item_or_value = slot_name;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_2 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)2L)) = temp_2;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
			    Qslot_component_name;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)3L)) = Qslot_component_name;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_component_name),
			    Qslot_component_alias);
		    if (item_or_value);
		    else
			item_or_value = slot_component_name;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(slot_component_name),
			    Qslot_component_alias);
		    if (item_or_value);
		    else
			item_or_value = slot_component_name;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_2 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)4L)) = temp_2;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
			    Qchart_element_uid;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)5L)) = Qchart_element_uid;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    if (FIXNUMP(slot_component_indicator_qm))
			item_or_value = slot_component_indicator_qm;
		    else if ( !TRUEP(slot_component_indicator_qm))
			item_or_value = Evaluation_false_value;
		    else if (EQ(slot_component_indicator_qm,T))
			item_or_value = Evaluation_true_value;
		    else if (SYMBOLP(slot_component_indicator_qm))
			item_or_value = slot_component_indicator_qm;
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_component_indicator_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_component_indicator_qm)) 
			    == (SI_Long)1L)
			item_or_value = 
				copy_managed_float(slot_component_indicator_qm);
		    else if (FLOATP(slot_component_indicator_qm)) {
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
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_1 = Available_float_array_conses_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
				temp_1 = 
					Available_float_array_conses_tail_vector;
				temp_2 = Current_thread_index;
				SVREF(temp_1,temp_2) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				DOUBLE_FLOAT_TO_DOUBLE(slot_component_indicator_qm);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			item_or_value = new_float;
		    }
		    else if (INLINE_LONG_VECTOR_P(slot_component_indicator_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_component_indicator_qm)) 
			    == (SI_Long)1L)
			item_or_value = 
				copy_managed_long(slot_component_indicator_qm);
		    else if (INLINE_LONG_P(slot_component_indicator_qm) != 
			    (SI_Long)0L)
			item_or_value = 
				make_evaluation_long(slot_component_indicator_qm);
		    else if (text_string_p(slot_component_indicator_qm))
			item_or_value = 
				copy_as_wide_string(slot_component_indicator_qm);
		    else if (CONSP(slot_component_indicator_qm) && 
			    EQ(M_CDR(slot_component_indicator_qm),
			    Qtruth_value)) {
			gensymed_symbol_4 = M_CAR(slot_component_indicator_qm);
			if (FIXNUM_EQ(gensymed_symbol_4,Truth))
			    item_or_value = Evaluation_true_value;
			else if (FIXNUM_EQ(gensymed_symbol_4,Falsity))
			    item_or_value = Evaluation_false_value;
			else
			    item_or_value = eval_cons_1(gensymed_symbol_4,
				    Qtruth_value);
		    }
		    else
			item_or_value = error((SI_Long)2L,
				"Bad type ~a for make-evaluation-value-based-on-type.",
				type_of(slot_component_indicator_qm));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    if (FIXNUMP(slot_component_indicator_qm))
			item_or_value = slot_component_indicator_qm;
		    else if ( !TRUEP(slot_component_indicator_qm))
			item_or_value = Evaluation_false_value;
		    else if (EQ(slot_component_indicator_qm,T))
			item_or_value = Evaluation_true_value;
		    else if (SYMBOLP(slot_component_indicator_qm))
			item_or_value = slot_component_indicator_qm;
		    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_component_indicator_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_component_indicator_qm)) 
			    == (SI_Long)1L)
			item_or_value = 
				copy_managed_float(slot_component_indicator_qm);
		    else if (FLOATP(slot_component_indicator_qm)) {
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
				temp_2 = 
					Available_float_array_conses_tail_vector;
				temp_3 = Current_thread_index;
				SVREF(temp_2,temp_3) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_2 = Available_float_array_conses_vector;
				temp_3 = Current_thread_index;
				SVREF(temp_2,temp_3) = 
					amf_available_array_cons_qm;
				temp_2 = 
					Available_float_array_conses_tail_vector;
				temp_3 = Current_thread_index;
				SVREF(temp_2,temp_3) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				DOUBLE_FLOAT_TO_DOUBLE(slot_component_indicator_qm);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			item_or_value = new_float;
		    }
		    else if (INLINE_LONG_VECTOR_P(slot_component_indicator_qm) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_component_indicator_qm)) 
			    == (SI_Long)1L)
			item_or_value = 
				copy_managed_long(slot_component_indicator_qm);
		    else if (INLINE_LONG_P(slot_component_indicator_qm) != 
			    (SI_Long)0L)
			item_or_value = 
				make_evaluation_long(slot_component_indicator_qm);
		    else if (text_string_p(slot_component_indicator_qm))
			item_or_value = 
				copy_as_wide_string(slot_component_indicator_qm);
		    else if (CONSP(slot_component_indicator_qm) && 
			    EQ(M_CDR(slot_component_indicator_qm),
			    Qtruth_value)) {
			gensymed_symbol_4 = M_CAR(slot_component_indicator_qm);
			if (FIXNUM_EQ(gensymed_symbol_4,Truth))
			    item_or_value = Evaluation_true_value;
			else if (FIXNUM_EQ(gensymed_symbol_4,Falsity))
			    item_or_value = Evaluation_false_value;
			else
			    item_or_value = eval_cons_1(gensymed_symbol_4,
				    Qtruth_value);
		    }
		    else
			item_or_value = error((SI_Long)2L,
				"Bad type ~a for make-evaluation-value-based-on-type.",
				type_of(slot_component_indicator_qm));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_2 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)6L)) = temp_2;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qnew_value;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)7L)) = Qnew_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = exported_new_value;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_1 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = exported_new_value;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    temp_2 = temp ? get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)8L)) = temp_2;
		}
		notification_body = eval_cons_1(gensymed_symbol,Qab_structure);
		body_evaluated_p = T;
	    }
	    address = ISVREF(representation,(SI_Long)8L);
	    subscription_handle = ISVREF(representation,(SI_Long)12L);
	    socket_1 = getf(address,Qsocket,_);
	    argument_list = eval_list_4(subscription_handle,trend_chart,
		    Qslot_change,FIXNUMP(notification_body) || 
		    notification_body && SYMBOLP(notification_body) || 
		    SIMPLE_VECTOR_P(notification_body) ? notification_body 
		    : copy_if_evaluation_value_1(notification_body));
	    callback_representation_fire_callback(representation,socket_1,
		    argument_list);
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_frame_serial_number(current_frame_serial_number_on_entry);
	reclaim_gensym_list_1(representations);
	if (body_evaluated_p) {
	    if ( !(FIXNUMP(notification_body) || 
		    SYMBOLP(notification_body) || 
		    SIMPLE_VECTOR_P(notification_body)))
		reclaim_if_evaluation_value_1(notification_body);
	}
	return VALUES_1(body_evaluated_p);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-TRANSFER-ITEMS-SYSTEM-RPC-INTERNAL */
Object g2_transfer_items_system_rpc_internal(gensymed_symbol,
	    sequence_of_items,kb_workspace,delta_x,delta_y)
    Object gensymed_symbol, sequence_of_items, kb_workspace, delta_x, delta_y;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,212);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    g2_transfer_list_contents(5,sequence_of_items,kb_workspace,
		    delta_x,delta_y,Evaluation_true_value);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-MOVE-ITEMS-ENLARGING-WORKSPACE-IF-NECESSARY-SYSTEM-RPC-INTERNAL */
Object g2_move_items_enlarging_workspace_if_necessary_system_rpc_internal(gensymed_symbol,
	    sequence_of_items,delta_x,delta_y,enlarge_workspace_if_necessary_1)
    Object gensymed_symbol, sequence_of_items, delta_x, delta_y;
    Object enlarge_workspace_if_necessary_1;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, objects_being_moved, from_workspace;
    Object left, top, right, bottom, margin, block, ab_loop_list_;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, leftmost_point, biggest_move;
    SI_Long rightmost_point, topmost_point, bottommost_point;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,213);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    delta_y = FIXNUM_NEGATE(delta_y);
	    result = get_blocks_valid_for_group_operation(sequence_of_items);
	    MVS_2(result,objects_being_moved,from_workspace);
	    if ( 
		    !TRUEP(evaluation_truth_value_is_true_p(enlarge_workspace_if_necessary_1))) 
			{
		result = determine_extreme_edges_of_group(objects_being_moved);
		MVS_4(result,left,top,right,bottom);
		margin = ISVREF(from_workspace,(SI_Long)17L);
		if (IFIX(delta_x) < (SI_Long)0L) {
		    gensymed_symbol_1 = ISVREF(from_workspace,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		    gensymed_symbol_3 = IFIX(margin);
		    leftmost_point = gensymed_symbol_2 + gensymed_symbol_3;
		    biggest_move = leftmost_point - IFIX(left);
		    if (IFIX(delta_x) < biggest_move)
			delta_x = FIX(biggest_move);
		}
		else {
		    gensymed_symbol_1 = ISVREF(from_workspace,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		    gensymed_symbol_3 = IFIX(margin);
		    rightmost_point = gensymed_symbol_2 - gensymed_symbol_3;
		    biggest_move = rightmost_point - IFIX(right);
		    if (IFIX(delta_x) > biggest_move)
			delta_x = FIX(biggest_move);
		}
		if (IFIX(delta_y) < (SI_Long)0L) {
		    gensymed_symbol_1 = ISVREF(from_workspace,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		    gensymed_symbol_3 = IFIX(margin);
		    topmost_point = gensymed_symbol_2 + gensymed_symbol_3;
		    biggest_move = topmost_point - IFIX(top);
		    if (IFIX(delta_y) < biggest_move)
			delta_y = FIX(biggest_move);
		}
		else {
		    gensymed_symbol_1 = ISVREF(from_workspace,(SI_Long)14L);
		    gensymed_symbol_1 = gensymed_symbol_1 ? 
			    ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		    gensymed_symbol_3 = IFIX(margin);
		    bottommost_point = gensymed_symbol_2 - gensymed_symbol_3;
		    biggest_move = bottommost_point - IFIX(bottom);
		    if (IFIX(delta_y) > biggest_move)
			delta_y = FIX(biggest_move);
		}
	    }
	    move_blocks_with_their_external_connections(objects_being_moved,
		    from_workspace,delta_x,delta_y);
	    if (G2_has_v5_mode_windows_p) {
		block = Nil;
		ab_loop_list_ = objects_being_moved;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		block = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		send_ws_representations_item_moved(block,delta_x,delta_y);
		goto next_loop;
	      end_loop:;
	    }
	    reclaim_dragging_list_1(objects_being_moved);
	    if ( !(EQ(enlarge_workspace_if_necessary_1,
		    Evaluation_true_value) || 
		    EQ(enlarge_workspace_if_necessary_1,
		    Evaluation_false_value)))
		reclaim_eval_cons_1(enlarge_workspace_if_necessary_1);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* DETERMINE-EXTREME-EDGES-OF-GROUP */
Object determine_extreme_edges_of_group(group_of_blocks)
    Object group_of_blocks;
{
    Object current_leftmost, current_rightmost, current_topmost;
    Object current_bottommost, block, ab_loop_list_, left, top, right, bottom;
    Object result;

    x_note_fn_call(248,214);
    current_leftmost = Most_positive_fixnum;
    current_rightmost = Most_negative_fixnum;
    current_topmost = Most_positive_fixnum;
    current_bottommost = Most_negative_fixnum;
    block = Nil;
    ab_loop_list_ = group_of_blocks;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    block = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = determine_extreme_edges_of_block(block);
    MVS_4(result,left,top,right,bottom);
    if (FIXNUM_LT(left,current_leftmost))
	current_leftmost = left;
    if (FIXNUM_GT(right,current_rightmost))
	current_rightmost = right;
    if (FIXNUM_LT(top,current_topmost))
	current_topmost = top;
    if (FIXNUM_GT(bottom,current_bottommost))
	current_bottommost = bottom;
    goto next_loop;
  end_loop:
    return VALUES_4(current_leftmost,current_topmost,current_rightmost,
	    current_bottommost);
    return VALUES_1(Qnil);
}

/* G2-MOVE-ITEMS-SYSTEM-RPC-INTERNAL */
Object g2_move_items_system_rpc_internal(gensymed_symbol,sequence_of_items,
	    delta_x,delta_y)
    Object gensymed_symbol, sequence_of_items, delta_x, delta_y;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,215);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    g2_move_list_contents(3,sequence_of_items,delta_x,delta_y);
	    gensymed_symbol_1 = Nil;
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-CLONE-AND-TRANSFER-ITEMS-SYSTEM-RPC-INTERNAL */
Object g2_clone_and_transfer_items_system_rpc_internal(gensymed_symbol,
	    sequence_of_items,kb_workspace,delta_x,delta_y)
    Object gensymed_symbol, sequence_of_items, kb_workspace, delta_x, delta_y;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list, item_list, temp;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,216);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    item_list = g2_clone_list_contents(sequence_of_items,
		    kb_workspace,delta_x,delta_y);
	    temp = get_list_contents_as_sequence(item_list);
	    delete_frame(item_list);
	    result = VALUES_1(temp);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-INVOKE-GENERIC-EVENT-RULES-SYSTEM-RPC-INTERNAL */
Object g2_invoke_generic_event_rules_system_rpc_internal(gensymed_symbol,
	    event_name,item,event_object)
    Object gensymed_symbol, event_name, item, event_object;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,217);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_invoke_generic_event_rules(event_name,
		    item,event_object);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_27;  /* "Description of ~(~NF.~)" */

static Object Qtable_item;         /* table-item */

/* G2-GET-DESCRIPTION-OF-ITEM */
Object g2_get_description_of_item(item)
    Object item;
{
    Object current_computation_frame, gensymed_symbol, gensymed_symbol_1;
    Object display_description, main_header, descriptions, display_statement;
    Object ab_loop_list_, description, temp, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(248,218);
    current_computation_frame = item;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)15L),(SI_Long)1L);
      gensymed_symbol_1 = item;
      display_description = inline_funcall_1(gensymed_symbol,
	      gensymed_symbol_1);
      main_header = tformat_text_string(2,string_constant_27,item);
      descriptions = Qnil;
      display_statement = Nil;
      ab_loop_list_ = display_description;
      description = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      display_statement = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      description = Nil;
      if (ATOM(display_statement)) {
	  if ( !TRUEP(display_statement))
	      description = Nil;
	  else if (text_string_p(display_statement))
	      description = display_statement;
	  else if (CONSP(display_statement)) {
	      temp = convert_text_to_text_string(1,display_statement);
	      reclaim_text(display_statement);
	      description = temp;
	  }
	  else {
	      if (SIMPLE_VECTOR_P(display_statement) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(display_statement)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(display_statement,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(display_statement,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  gensymed_symbol = ISVREF(display_statement,(SI_Long)1L);
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Text_box_class_description,
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
		      temp_1 = (SI_Long)0L < gensymed_symbol_2;
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      temp = convert_text_to_text_string(1,
			      ISVREF(display_statement,(SI_Long)16L));
		  else {
		      gensymed_symbol_1 = 
			      lookup_global_or_kb_specific_property_value(Qtable_item,
			      Class_description_gkbprop);
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
		      if (temp_1)
			  temp = get_represented_item(display_statement);
		      else
			  temp = Qnil;
		  }
		  delete_frame(display_statement);
		  description = temp;
	      }
	      else
		  description = Nil;
	  }
      }
      else
	  description = Nil;
      if (description)
	  descriptions = eval_cons_1(description,descriptions);
      goto next_loop;
    end_loop:
      reclaim_eval_list_1(display_description);
      descriptions = eval_cons_1(main_header,descriptions);
      result = allocate_evaluation_sequence(descriptions);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* G2-GET-DESCRIPTION-OF-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_get_description_of_item_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,219);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_description_of_item(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qitem_or_name;       /* item-or-name */

/* EXPORT-NODE */
Object export_node(node)
    Object node;
{
    Object node_item, exported_item, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(248,220);
    node_item = estructure_slot(node,Qitem_or_name,Nil);
    exported_item = Nil;
    gensymed_symbol = ISVREF(node_item,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qtable_item,
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
    if (temp)
	exported_item = get_represented_item(node_item);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	if (temp)
	    exported_item = convert_text_to_text_string(1,ISVREF(node_item,
		    (SI_Long)16L));
	else
	    exported_item = Qnil;
    }
    temp_1 = set_evaluation_structure_slot(node,Qitem_or_name,exported_item);
    return VALUES_1(temp_1);
}

/* SIBLING-NODES */
Object sibling_nodes(default_junction,excluded_node)
    Object default_junction, excluded_node;
{
    Object siblings, scope_conses, ab_node_stack_, ab_current_node_;
    Object gensymed_symbol, ab_skip_list_form_, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, sibling_node, temp;
    Object ab_less_than_branch_qm_, sub_class_bit_vector, temp_2;
    Object item_or_value, x2, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_arg_2;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(248,221);
    siblings = Qnil;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(default_junction,(SI_Long)14L));
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
      sibling_node = Nil;
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
    next_loop:
    next_loop_1:
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
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
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
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      sibling_node = get_block_at_other_end_of_connection(connection,
	      default_junction);
      if ( !EQ(sibling_node,excluded_node)) {
	  sub_class_bit_vector = ISVREF(ISVREF(sibling_node,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Default_junction_class_description,
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
	      temp = siblings;
	      siblings = nconc2(temp,sibling_nodes(sibling_node,
		      default_junction));
	  }
	  else {
	      gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		      (SI_Long)1L));
	      gensymed_symbol_1 = (SI_Long)0L;
	      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  svref_arg_2 = gensymed_symbol_1 + 
			  IFIX(Managed_array_index_offset);
		  ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	      }
	      else {
		  temp_2 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  - 
			   - (SI_Long)10L) + (SI_Long)2L);
		  svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		  ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	      }
	      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		      Maximum_in_place_array_size))
		  SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qitem_or_name;
	      else {
		  temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
		  SVREF(temp_2,FIX((SI_Long)1L)) = Qitem_or_name;
	      }
	      if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		      Maximum_in_place_array_size)) {
		  item_or_value = sibling_node;
		  if (SIMPLE_VECTOR_P(item_or_value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(item_or_value,(SI_Long)1L);
		      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
			  item_or_value;
		  SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_2;
	      }
	      else {
		  temp_2 = ISVREF(gensymed_symbol,(SI_Long)2L);
		  item_or_value = sibling_node;
		  if (SIMPLE_VECTOR_P(item_or_value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(item_or_value,(SI_Long)1L);
		      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  svref_new_value = temp_1 ? 
			  get_reference_to_item(item_or_value) : item_or_value;
		  SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	      }
	      siblings = eval_cons_1(eval_cons_1(gensymed_symbol,
		      Qab_structure),siblings);
	  }
      }
      goto next_loop;
    end_loop_2:
      temp = siblings;
      goto end_2;
      temp = Qnil;
    end_2:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qchildren;           /* children */

/* GATHER-CHILDREN-NODES */
Object gather_children_nodes(item_node)
    Object item_node;
{
    Object item, child_connection_qm, child_block_qm, child_nodes;
    Object sub_class_bit_vector, gensymed_symbol_3, temp_1, item_or_value, x2;
    Object svref_new_value, node, ab_loop_list_, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    char temp;

    x_note_fn_call(248,222);
    item = estructure_slot(item_node,Qitem_or_name,Nil);
    child_connection_qm = sub_nodes_connection(1,item);
    child_block_qm = child_connection_qm ? 
	    get_block_at_other_end_of_connection(child_connection_qm,item) 
	    : Qnil;
    child_nodes = Nil;
    if (child_block_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(child_block_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Default_junction_class_description,(SI_Long)18L));
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
	    child_nodes = sibling_nodes(child_block_qm,item);
	else {
	    gensymed_symbol_3 = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol_3,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_3,(gensymed_symbol >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol_3,FIX((SI_Long)3L)) = Qitem_or_name;
	    else {
		temp_1 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qitem_or_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol_3,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = child_block_qm;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		temp_1 = temp ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol_3,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
		item_or_value = child_block_qm;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		svref_new_value = temp ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    child_nodes = eval_cons_1(eval_cons_1(gensymed_symbol_3,
		    Qab_structure),Nil);
	}
	node = Nil;
	ab_loop_list_ = child_nodes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	node = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gather_children_nodes(node);
	export_node(node);
	goto next_loop;
      end_loop:;
	temp_2 = child_nodes ? set_evaluation_structure_slot(item_node,
		Qchildren,allocate_evaluation_sequence(child_nodes)) : Nil;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* GET-TREE-STRUCTURE-FOR-INSPECT-COMMAND */
Object get_tree_structure_for_inspect_command varargs_1(int, n)
{
    Object inspect_command_string;
    Object force_workspace_creation_p, root_node_index, inspect_command;
    Object gensymed_symbol, current_workstation_1, current_workstation_window;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm, workspace_qm, subblocks, block_count;
    Object root, temp_1, item_or_value, x2, svref_new_value, root_node;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(10);
    Object result;

    x_note_fn_call(248,223);
    INIT_ARGS_nonrelocating();
    inspect_command_string = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    force_workspace_creation_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    root_node_index = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)2L);
    END_ARGS_nonrelocating();
    inspect_command = 
	    make_inspect_command_or_signal_error(inspect_command_string);
    gensymed_symbol = get_or_make_dummy_workstation();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		9);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  8);
	    type_of_current_workstation_window = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		    7);
	      current_workstation_native_window_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
		      6);
		temp = ISVREF(Current_workstation,(SI_Long)17L);
		current_workstation_context = CAR(temp);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			5);
		  type_of_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			  4);
		    specific_structure_for_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)2L);
		    PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			    3);
		      current_workstation_detail_pane = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
			      2);
			current_g2_user_mode_qm = Qadministrator;
			PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				1);
			  servicing_workstation_qm = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				  0);
			    if (force_workspace_creation_p)
				make_inspect_workspace(1,inspect_command);
			    execute_inspect_command(inspect_command);
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
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    gensymed_symbol = ACCESS_ONCE(ISVREF(inspect_command,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    workspace_qm = gensymed_symbol;
    if (workspace_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
    }
    else
	subblocks = Nil;
    block_count = constant_queue_length(subblocks);
    root = FIXNUM_GT(block_count,FIXNUM_SUB1(root_node_index)) ? 
	    (subblocks ? constant_queue_nth(FIXNUM_MINUS(block_count,
	    root_node_index),subblocks) : Nil) : Qnil;
    if (root) {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
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
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qitem_or_name;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qitem_or_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = root;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = root;
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	root_node = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    else
	root_node = Nil;
    if (root_node) {
	gather_children_nodes(root_node);
	export_node(root_node);
    }
    if (workspace_qm)
	delete_frame(workspace_qm);
    else
	delete_frame(inspect_command);
    RESTORE_STACK();
    return VALUES_1(root_node);
}

static Object string_constant_28;  /* "show on a workspace the method inheritance path for ~s and the method ~s" */

static Object string_constant_29;  /* "show on a workspace the method inheritance path for ~s" */

/* G2-GET-METHOD-INHERITANCE-PATH */
Object g2_get_method_inheritance_path(class_name,method_name_qm)
    Object class_name, method_name_qm;
{
    x_note_fn_call(248,224);
    return get_tree_structure_for_inspect_command(1,method_name_qm ? 
	    tformat_text_string(3,string_constant_28,class_name,
	    method_name_qm) : tformat_text_string(2,string_constant_29,
	    class_name));
}

/* G2-GET-METHOD-INHERITANCE-PATH-SYSTEM-RPC-INTERNAL */
Object g2_get_method_inheritance_path_system_rpc_internal(gensymed_symbol,
	    class_name,method_name_qm)
    Object gensymed_symbol, class_name, method_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,225);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_method_inheritance_path(class_name,method_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_30;  /* "show on a workspace the method hierarchy of ~s" */

/* G2-GET-METHOD-HIERARCHY */
Object g2_get_method_hierarchy(method_name)
    Object method_name;
{
    x_note_fn_call(248,226);
    return get_tree_structure_for_inspect_command(1,tformat_text_string(2,
	    string_constant_30,method_name));
}

/* G2-GET-METHOD-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_method_hierarchy_system_rpc_internal(gensymed_symbol,method_name)
    Object gensymed_symbol, method_name;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,227);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_method_hierarchy(method_name);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_31;  /* "show on a workspace the procedure invocation hierarchy" */

/* G2-GET-PROCEDURE-INVOCATION-HIERARCHY */
Object g2_get_procedure_invocation_hierarchy()
{
    x_note_fn_call(248,228);
    return get_tree_structure_for_inspect_command(2,tformat_text_string(1,
	    string_constant_31),T);
}

/* G2-GET-PROCEDURE-INVOCATION-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_procedure_invocation_hierarchy_system_rpc_internal(gensymed_symbol)
    Object gensymed_symbol;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,229);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_procedure_invocation_hierarchy();
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_32;  /* "show on a workspace the procedure calling hierarchy of ~s" */

/* G2-GET-PROCEDURE-CALLING-HIERARCHY */
Object g2_get_procedure_calling_hierarchy(procedure_name_qm)
    Object procedure_name_qm;
{
    Object temp;

    x_note_fn_call(248,230);
    temp = procedure_name_qm;
    if (temp);
    else
	temp = Qitem;
    return get_tree_structure_for_inspect_command(1,tformat_text_string(2,
	    string_constant_32,temp));
}

/* G2-GET-PROCEDURE-CALLING-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_procedure_calling_hierarchy_system_rpc_internal(gensymed_symbol,
	    procedure_name_qm)
    Object gensymed_symbol, procedure_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,231);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_procedure_calling_hierarchy(procedure_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_33;  /* "show on a workspace the procedure caller hierarchy of ~s" */

/* G2-GET-PROCEDURE-CALLER-HIERARCHY */
Object g2_get_procedure_caller_hierarchy(procedure_name_qm)
    Object procedure_name_qm;
{
    Object temp;

    x_note_fn_call(248,232);
    temp = procedure_name_qm;
    if (temp);
    else
	temp = Qitem;
    return get_tree_structure_for_inspect_command(1,tformat_text_string(2,
	    string_constant_33,temp));
}

/* G2-GET-PROCEDURE-CALLER-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_procedure_caller_hierarchy_system_rpc_internal(gensymed_symbol,
	    procedure_name_qm)
    Object gensymed_symbol, procedure_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,233);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_procedure_caller_hierarchy(procedure_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_34;  /* "show on a workspace the class hierarchy of ~s" */

static Object string_constant_35;  /* "show on a workspace the class hierarchy" */

/* G2-GET-CLASS-HIERARCHY */
Object g2_get_class_hierarchy(class_name_qm)
    Object class_name_qm;
{
    x_note_fn_call(248,234);
    return get_tree_structure_for_inspect_command(1,class_name_qm ? 
	    tformat_text_string(2,string_constant_34,class_name_qm) : 
	    tformat_text_string(1,string_constant_35));
}

/* G2-GET-CLASS-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_class_hierarchy_system_rpc_internal(gensymed_symbol,
	    class_name_qm)
    Object gensymed_symbol, class_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,235);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_class_hierarchy(class_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object string_constant_36;  /* "show on a workspace the workspace hierarchy of ~s" */

static Object string_constant_37;  /* "show on a workspace the workspace hierarchy" */

/* G2-GET-WORKSPACE-HIERARCHY */
Object g2_get_workspace_hierarchy(workspace_name_qm)
    Object workspace_name_qm;
{
    x_note_fn_call(248,236);
    return get_tree_structure_for_inspect_command(1,workspace_name_qm ? 
	    tformat_text_string(2,string_constant_36,workspace_name_qm) : 
	    tformat_text_string(1,string_constant_37));
}

/* G2-GET-WORKSPACE-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_workspace_hierarchy_system_rpc_internal(gensymed_symbol,
	    workspace_name_qm)
    Object gensymed_symbol, workspace_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,237);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_workspace_hierarchy(workspace_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-MODULE-HIERARCHY */
Object g2_get_module_hierarchy(module_name_qm)
    Object module_name_qm;
{
    x_note_fn_call(248,238);
    return export_module_hierarchy(module_name_qm);
}

/* G2-GET-MODULE-HIERARCHY-SYSTEM-RPC-INTERNAL */
Object g2_get_module_hierarchy_system_rpc_internal(gensymed_symbol,
	    module_name_qm)
    Object gensymed_symbol, module_name_qm;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,239);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_module_hierarchy(module_name_qm);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* EXPORT-GRAPH-NODE */
Object export_graph_node varargs_1(int, n)
{
    Object graph_node;
    Object item_node_creation_function_qm, add_children_to_all_nodes_p;
    Object root_node, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value, children_qm, child_nodes_qm, child, ab_loop_list_;
    Object temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(248,240);
    INIT_ARGS_nonrelocating();
    graph_node = REQUIRED_ARG_nonrelocating();
    item_node_creation_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    add_children_to_all_nodes_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (item_node_creation_function_qm)
	root_node = FUNCALL_1(item_node_creation_function_qm,
		ISVREF(graph_node,(SI_Long)2L));
    else {
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qitem_or_name;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qitem_or_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = ISVREF(graph_node,(SI_Long)2L);
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
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = ISVREF(graph_node,(SI_Long)2L);
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
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	}
	root_node = eval_cons_1(gensymed_symbol,Qab_structure);
    }
    children_qm = ISVREF(graph_node,(SI_Long)5L);
    if ( !TRUEP(children_qm)) {
	if (add_children_to_all_nodes_p)
	    set_evaluation_structure_slot(root_node,Qchildren,
		    allocate_evaluation_sequence(Nil));
    }
    else if (CONSP(children_qm)) {
	child_nodes_qm = Qnil;
	child = Nil;
	ab_loop_list_ = children_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	child = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_2 = export_graph_node(3,child,item_node_creation_function_qm,
		add_children_to_all_nodes_p);
	child_nodes_qm = eval_cons_1(temp_2,child_nodes_qm);
	goto next_loop;
      end_loop:
	if (child_nodes_qm)
	    set_evaluation_structure_slot(root_node,Qchildren,
		    allocate_evaluation_sequence(nreverse(child_nodes_qm)));
    }
    else
	set_evaluation_structure_slot(root_node,Qchildren,
		allocate_evaluation_sequence(eval_cons_1(export_graph_node(3,
		children_qm,item_node_creation_function_qm,
		add_children_to_all_nodes_p),Nil)));
    return VALUES_1(root_node);
}

static Object Qhash_symbol_or_frame;  /* hash-symbol-or-frame */

static Object Qsxhashw;            /* sxhashw */

static Object Qvertical;           /* vertical */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qget_directly_required_module_information_system_tables;  /* get-directly-required-module-information-system-tables */

static Object Qmake_attributes_table_for_module_information_in_hierarchy;  /* make-attributes-table-for-module-information-in-hierarchy */

static Object array_constant_5;    /* # */

static Object string_constant_38;  /* "" */

static Object string_constant_39;  /* "No module hierarchy ~a~a" */

static Object string_constant_40;  /* "can be shown for " */

static Object string_constant_41;  /* "exists, because the top-level module is unnamed." */

static Object array_constant_6;    /* # */

static Object array_constant_7;    /* # */

/* EXPORT-MODULE-HIERARCHY */
Object export_module_hierarchy(module_to_start_with_qm)
    Object module_to_start_with_qm;
{
    Object gensymed_symbol, current_workstation_1, current_workstation_window;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm, required_modules_node;
    Object unrequired_modules_node_qm, ultimate_top_level_module_qm;
    Object system_table_for_top_module_qm, temp_1, temp_2, temp_3, temp_4;
    Object graph, temp_5, item_or_value, x2, svref_new_value;
    Object unrequired_modules_qm, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object module_information_instance, parent_module_qm, instance_qm;
    Object root_node;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_6;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(11);
    Object result;

    x_note_fn_call(248,241);
    SAVE_STACK();
    gensymed_symbol = get_or_make_dummy_workstation();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		10);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  9);
	    type_of_current_workstation_window = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		    8);
	      current_workstation_native_window_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
		      7);
		temp = ISVREF(Current_workstation,(SI_Long)17L);
		current_workstation_context = CAR(temp);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			6);
		  type_of_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			  5);
		    specific_structure_for_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)2L);
		    PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			    4);
		      current_workstation_detail_pane = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
			      3);
			current_g2_user_mode_qm = Qadministrator;
			PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				2);
			  servicing_workstation_qm = T;
			  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				  1);
			    required_modules_node = Nil;
			    unrequired_modules_node_qm = Nil;
			    ultimate_top_level_module_qm = 
				    ISVREF(Module_information,(SI_Long)23L);
			    system_table_for_top_module_qm = 
				    module_to_start_with_qm ? 
				    lookup_kb_specific_property_value(module_to_start_with_qm,
				    Module_information_instance_for_module_qm_kbprop) 
				    : Module_information;
			    if (system_table_for_top_module_qm && 
				    ISVREF(system_table_for_top_module_qm,
				    (SI_Long)23L)) {
				temp_1 = IDENTITY(Qhash_symbol_or_frame);
				if (temp_1);
				else
				    temp_1 = Qsxhashw;
				temp_2 = IDENTITY(Qvertical);
				if (temp_2);
				else
				    temp_2 = Qvertical;
				temp_3 = IDENTITY(FIX((SI_Long)50L));
				if (temp_3);
				else
				    temp_3 = FIX((SI_Long)50L);
				temp_4 = IDENTITY(FIX((SI_Long)5L));
				if (temp_4);
				else
				    temp_4 = FIX((SI_Long)50L);
				temp = IDENTITY(Nil);
				if (temp);
				else
				    temp = Qtemporary_workspace;
				graph = 
					graph_frame_hierarchy_function(system_table_for_top_module_qm,
					Qget_directly_required_module_information_system_tables,
					Nil,
					Qmake_attributes_table_for_module_information_in_hierarchy,
					temp_1,temp_2,temp_3,temp_4,Nil,
					temp,Nil,FIX((SI_Long)0L),
					FIX((SI_Long)0L));
				gensymed_symbol = allocate_managed_array(1,
					FIX((SI_Long)2L + (SI_Long)1L));
				gensymed_symbol_1 = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol_1 + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (gensymed_symbol_1 >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol_1 & 
					    (SI_Long)1023L;
				    ISVREF(temp_5,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)3L)) = Qitem_or_name;
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    SVREF(temp_5,FIX((SI_Long)1L)) = 
					    Qitem_or_name;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = 
					    copy_constant_wide_string_given_length(array_constant_5,
					    FIX((SI_Long)27L));
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    temp_5 = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)4L)) = temp_5;
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    item_or_value = 
					    copy_constant_wide_string_given_length(array_constant_5,
					    FIX((SI_Long)27L));
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    svref_new_value = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_5,FIX((SI_Long)2L)) = 
					    svref_new_value;
				}
				required_modules_node = 
					eval_cons_1(gensymed_symbol,
					Qab_structure);
				temp = required_modules_node;
				set_evaluation_structure_slot(temp,
					Qchildren,
					allocate_evaluation_sequence(eval_cons_1(export_graph_node(1,
					ISVREF(graph,(SI_Long)3L)),Nil)));
				reclaim_graph_display_1(graph);
			    }
			    else {
				gensymed_symbol = allocate_managed_array(1,
					FIX((SI_Long)2L + (SI_Long)1L));
				gensymed_symbol_1 = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol_1 + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (gensymed_symbol_1 >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol_1 & 
					    (SI_Long)1023L;
				    ISVREF(temp_5,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)3L)) = Qitem_or_name;
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    SVREF(temp_5,FIX((SI_Long)1L)) = 
					    Qitem_or_name;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    temp = module_to_start_with_qm;
				    if (temp);
				    else
					temp = string_constant_38;
				    item_or_value = tformat_text_string(3,
					    string_constant_39,
					    module_to_start_with_qm ? 
					    string_constant_40 : 
					    string_constant_41,temp);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    temp_5 = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)4L)) = temp_5;
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    temp = module_to_start_with_qm;
				    if (temp);
				    else
					temp = string_constant_38;
				    item_or_value = tformat_text_string(3,
					    string_constant_39,
					    module_to_start_with_qm ? 
					    string_constant_40 : 
					    string_constant_41,temp);
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    svref_new_value = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_5,FIX((SI_Long)2L)) = 
					    svref_new_value;
				}
				required_modules_node = 
					eval_cons_1(gensymed_symbol,
					Qab_structure);
				if ( !TRUEP(module_to_start_with_qm)) {
				    temp = required_modules_node;
				    gensymed_symbol = 
					    allocate_managed_array(1,
					    FIX((SI_Long)2L + (SI_Long)1L));
				    gensymed_symbol_1 = (SI_Long)0L;
				    if (FIXNUM_LE(ISVREF(gensymed_symbol,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					svref_arg_2 = gensymed_symbol_1 + 
						IFIX(Managed_array_index_offset);
					ISVREF(gensymed_symbol,
						svref_arg_2) = 
						FIX((SI_Long)1L);
				    }
				    else {
					temp_5 = ISVREF(gensymed_symbol,
						(gensymed_symbol_1 >>  -  
						- (SI_Long)10L) + (SI_Long)2L);
					svref_arg_2 = gensymed_symbol_1 & 
						(SI_Long)1023L;
					ISVREF(temp_5,svref_arg_2) = 
						FIX((SI_Long)1L);
				    }
				    if (FIXNUM_LE(ISVREF(gensymed_symbol,
					    (SI_Long)1L),
					    Maximum_in_place_array_size))
					SVREF(gensymed_symbol,
						FIX((SI_Long)3L)) = 
						Qitem_or_name;
				    else {
					temp_5 = ISVREF(gensymed_symbol,
						(SI_Long)2L);
					SVREF(temp_5,FIX((SI_Long)1L)) = 
						Qitem_or_name;
				    }
				    if (FIXNUM_LE(ISVREF(gensymed_symbol,
					    (SI_Long)1L),
					    Maximum_in_place_array_size)) {
					item_or_value = Module_information;
					if (SIMPLE_VECTOR_P(item_or_value) 
						&& 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						> (SI_Long)2L &&  
						!EQ(ISVREF(item_or_value,
						(SI_Long)1L),
						Qavailable_frame_vector)) {
					    x2 = ISVREF(item_or_value,
						    (SI_Long)1L);
					    temp_6 = SIMPLE_VECTOR_P(x2) 
						    && EQ(ISVREF(x2,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_class_description_g2_struct) 
						    ? TRUEP(x2) : TRUEP(Qnil);
					}
					else
					    temp_6 = TRUEP(Nil);
					temp_5 = temp_6 ? 
						get_reference_to_item(item_or_value) 
						: item_or_value;
					SVREF(gensymed_symbol,
						FIX((SI_Long)4L)) = temp_5;
				    }
				    else {
					temp_5 = ISVREF(gensymed_symbol,
						(SI_Long)2L);
					item_or_value = Module_information;
					if (SIMPLE_VECTOR_P(item_or_value) 
						&& 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
						> (SI_Long)2L &&  
						!EQ(ISVREF(item_or_value,
						(SI_Long)1L),
						Qavailable_frame_vector)) {
					    x2 = ISVREF(item_or_value,
						    (SI_Long)1L);
					    temp_6 = SIMPLE_VECTOR_P(x2) 
						    && EQ(ISVREF(x2,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_class_description_g2_struct) 
						    ? TRUEP(x2) : TRUEP(Qnil);
					}
					else
					    temp_6 = TRUEP(Nil);
					svref_new_value = temp_6 ? 
						get_reference_to_item(item_or_value) 
						: item_or_value;
					SVREF(temp_5,FIX((SI_Long)2L)) = 
						svref_new_value;
				    }
				    set_evaluation_structure_slot(temp,
					    Qchildren,
					    allocate_evaluation_sequence(eval_cons_1(eval_cons_1(gensymed_symbol,
					    Qab_structure),Nil)));
				}
			    }
			    unrequired_modules_qm = Qnil;
			    scope_conses = Scope_conses;
			    ab_loopvar_ = Nil;
			    ab_loopvar__1 = Nil;
			    module_information_instance = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				    0);
			      parent_module_qm = Nil;
			      ab_loopvar_ = 
				      collect_subclasses(Qmodule_information);
			      propagate_kb_requires_module_p_to_all_modules();
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
				  temp_6 =  !TRUEP(ab_loopvar__1);
			      }
			      else
				  temp_6 = TRUEP(Nil);
			      if (temp_6)
				  goto end_loop_1;
			      module_information_instance = ab_loopvar__1;
			      ab_loopvar__1 = ISVREF(ab_loopvar__1,
				      (SI_Long)6L);
			      parent_module_qm = 
				      ISVREF(module_information_instance,
				      (SI_Long)23L);
			      if ( !EQ(module_information_instance,
				      Module_information)) {
				  temp_6 =  !TRUEP(parent_module_qm);
				  if (temp_6);
				  else
				      temp_6 =  
					      !TRUEP(ultimate_top_level_module_qm);
				  if (temp_6);
				  else {
				      instance_qm = 
					      lookup_kb_specific_property_value(parent_module_qm,
					      Module_information_instance_for_module_qm_kbprop);
				      temp_6 =  !(instance_qm && 
					      ISVREF(instance_qm,
					      (SI_Long)25L));
				  }
			      }
			      else
				  temp_6 = TRUEP(Nil);
			      if (temp_6) {
				  gensymed_symbol = 
					  allocate_managed_array(1,
					  FIX((SI_Long)2L + (SI_Long)1L));
				  gensymed_symbol_1 = (SI_Long)0L;
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size)) {
				      svref_arg_2 = gensymed_symbol_1 + 
					      IFIX(Managed_array_index_offset);
				      ISVREF(gensymed_symbol,svref_arg_2) 
					      = FIX((SI_Long)1L);
				  }
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (gensymed_symbol_1 >>  -  - 
					      (SI_Long)10L) + (SI_Long)2L);
				      svref_arg_2 = gensymed_symbol_1 & 
					      (SI_Long)1023L;
				      ISVREF(temp_5,svref_arg_2) = 
					      FIX((SI_Long)1L);
				  }
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size))
				      SVREF(gensymed_symbol,
					      FIX((SI_Long)3L)) = 
					      Qitem_or_name;
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (SI_Long)2L);
				      SVREF(temp_5,FIX((SI_Long)1L)) = 
					      Qitem_or_name;
				  }
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size)) {
				      item_or_value = 
					      module_information_instance;
				      if (SIMPLE_VECTOR_P(item_or_value) 
					      && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					      > (SI_Long)2L &&  
					      !EQ(ISVREF(item_or_value,
					      (SI_Long)1L),
					      Qavailable_frame_vector)) {
					  x2 = ISVREF(item_or_value,
						  (SI_Long)1L);
					  temp_6 = SIMPLE_VECTOR_P(x2) && 
						  EQ(ISVREF(x2,
						  (SI_Long)0L),
						  Qg2_defstruct_structure_name_class_description_g2_struct) 
						  ? TRUEP(x2) : TRUEP(Qnil);
				      }
				      else
					  temp_6 = TRUEP(Nil);
				      temp_5 = temp_6 ? 
					      get_reference_to_item(item_or_value) 
					      : item_or_value;
				      SVREF(gensymed_symbol,
					      FIX((SI_Long)4L)) = temp_5;
				  }
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (SI_Long)2L);
				      item_or_value = 
					      module_information_instance;
				      if (SIMPLE_VECTOR_P(item_or_value) 
					      && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					      > (SI_Long)2L &&  
					      !EQ(ISVREF(item_or_value,
					      (SI_Long)1L),
					      Qavailable_frame_vector)) {
					  x2 = ISVREF(item_or_value,
						  (SI_Long)1L);
					  temp_6 = SIMPLE_VECTOR_P(x2) && 
						  EQ(ISVREF(x2,
						  (SI_Long)0L),
						  Qg2_defstruct_structure_name_class_description_g2_struct) 
						  ? TRUEP(x2) : TRUEP(Qnil);
				      }
				      else
					  temp_6 = TRUEP(Nil);
				      svref_new_value = temp_6 ? 
					      get_reference_to_item(item_or_value) 
					      : item_or_value;
				      SVREF(temp_5,FIX((SI_Long)2L)) = 
					      svref_new_value;
				  }
				  unrequired_modules_qm = 
					  eval_cons_1(eval_cons_1(gensymed_symbol,
					  Qab_structure),
					  unrequired_modules_qm);
			      }
			      goto next_loop;
			    end_loop_1:
			      if (unrequired_modules_qm) {
				  gensymed_symbol = 
					  allocate_managed_array(1,
					  FIX((SI_Long)2L + (SI_Long)1L));
				  gensymed_symbol_1 = (SI_Long)0L;
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size)) {
				      svref_arg_2 = gensymed_symbol_1 + 
					      IFIX(Managed_array_index_offset);
				      ISVREF(gensymed_symbol,svref_arg_2) 
					      = FIX((SI_Long)1L);
				  }
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (gensymed_symbol_1 >>  -  - 
					      (SI_Long)10L) + (SI_Long)2L);
				      svref_arg_2 = gensymed_symbol_1 & 
					      (SI_Long)1023L;
				      ISVREF(temp_5,svref_arg_2) = 
					      FIX((SI_Long)1L);
				  }
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size))
				      SVREF(gensymed_symbol,
					      FIX((SI_Long)3L)) = 
					      Qitem_or_name;
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (SI_Long)2L);
				      SVREF(temp_5,FIX((SI_Long)1L)) = 
					      Qitem_or_name;
				  }
				  if (FIXNUM_LE(ISVREF(gensymed_symbol,
					  (SI_Long)1L),
					  Maximum_in_place_array_size)) {
				      item_or_value = 
					      copy_constant_wide_string_given_length(array_constant_6,
					      FIX((SI_Long)31L));
				      if (SIMPLE_VECTOR_P(item_or_value) 
					      && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					      > (SI_Long)2L &&  
					      !EQ(ISVREF(item_or_value,
					      (SI_Long)1L),
					      Qavailable_frame_vector)) {
					  x2 = ISVREF(item_or_value,
						  (SI_Long)1L);
					  temp_6 = SIMPLE_VECTOR_P(x2) && 
						  EQ(ISVREF(x2,
						  (SI_Long)0L),
						  Qg2_defstruct_structure_name_class_description_g2_struct) 
						  ? TRUEP(x2) : TRUEP(Qnil);
				      }
				      else
					  temp_6 = TRUEP(Nil);
				      temp_5 = temp_6 ? 
					      get_reference_to_item(item_or_value) 
					      : item_or_value;
				      SVREF(gensymed_symbol,
					      FIX((SI_Long)4L)) = temp_5;
				  }
				  else {
				      temp_5 = ISVREF(gensymed_symbol,
					      (SI_Long)2L);
				      item_or_value = 
					      copy_constant_wide_string_given_length(array_constant_6,
					      FIX((SI_Long)31L));
				      if (SIMPLE_VECTOR_P(item_or_value) 
					      && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					      > (SI_Long)2L &&  
					      !EQ(ISVREF(item_or_value,
					      (SI_Long)1L),
					      Qavailable_frame_vector)) {
					  x2 = ISVREF(item_or_value,
						  (SI_Long)1L);
					  temp_6 = SIMPLE_VECTOR_P(x2) && 
						  EQ(ISVREF(x2,
						  (SI_Long)0L),
						  Qg2_defstruct_structure_name_class_description_g2_struct) 
						  ? TRUEP(x2) : TRUEP(Qnil);
				      }
				      else
					  temp_6 = TRUEP(Nil);
				      svref_new_value = temp_6 ? 
					      get_reference_to_item(item_or_value) 
					      : item_or_value;
				      SVREF(temp_5,FIX((SI_Long)2L)) = 
					      svref_new_value;
				  }
				  unrequired_modules_node_qm = 
					  eval_cons_1(gensymed_symbol,
					  Qab_structure);
				  unrequired_modules_qm = 
					  nreverse(unrequired_modules_qm);
				  temp = unrequired_modules_node_qm;
				  set_evaluation_structure_slot(temp,
					  Qchildren,
					  allocate_evaluation_sequence(unrequired_modules_qm));
			      }
			    POP_SPECIAL();
			    if (unrequired_modules_node_qm) {
				gensymed_symbol = allocate_managed_array(1,
					FIX((SI_Long)2L + (SI_Long)1L));
				gensymed_symbol_1 = (SI_Long)0L;
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    svref_arg_2 = gensymed_symbol_1 + 
					    IFIX(Managed_array_index_offset);
				    ISVREF(gensymed_symbol,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (gensymed_symbol_1 >>  -  - 
					    (SI_Long)10L) + (SI_Long)2L);
				    svref_arg_2 = gensymed_symbol_1 & 
					    (SI_Long)1023L;
				    ISVREF(temp_5,svref_arg_2) = 
					    FIX((SI_Long)1L);
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size))
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)3L)) = Qitem_or_name;
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    SVREF(temp_5,FIX((SI_Long)1L)) = 
					    Qitem_or_name;
				}
				if (FIXNUM_LE(ISVREF(gensymed_symbol,
					(SI_Long)1L),
					Maximum_in_place_array_size)) {
				    item_or_value = 
					    copy_constant_wide_string_given_length(array_constant_7,
					    FIX((SI_Long)14L));
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    temp_5 = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)4L)) = temp_5;
				}
				else {
				    temp_5 = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    item_or_value = 
					    copy_constant_wide_string_given_length(array_constant_7,
					    FIX((SI_Long)14L));
				    if (SIMPLE_VECTOR_P(item_or_value) && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					    > (SI_Long)2L &&  
					    !EQ(ISVREF(item_or_value,
					    (SI_Long)1L),
					    Qavailable_frame_vector)) {
					x2 = ISVREF(item_or_value,(SI_Long)1L);
					temp_6 = SIMPLE_VECTOR_P(x2) && 
						EQ(ISVREF(x2,(SI_Long)0L),
						Qg2_defstruct_structure_name_class_description_g2_struct) 
						? TRUEP(x2) : TRUEP(Qnil);
				    }
				    else
					temp_6 = TRUEP(Nil);
				    svref_new_value = temp_6 ? 
					    get_reference_to_item(item_or_value) 
					    : item_or_value;
				    SVREF(temp_5,FIX((SI_Long)2L)) = 
					    svref_new_value;
				}
				root_node = eval_cons_1(gensymed_symbol,
					Qab_structure);
				set_evaluation_structure_slot(root_node,
					Qchildren,
					allocate_evaluation_sequence(eval_list_2(required_modules_node,
					unrequired_modules_node_qm)));
				SAVE_VALUES(VALUES_1(root_node));
			    }
			    else
				SAVE_VALUES(VALUES_1(required_modules_node));
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
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-GET-INSPECT-GRAPH */
Object g2_get_inspect_graph(inspect_command_string)
    Object inspect_command_string;
{
    x_note_fn_call(248,242);
    return get_tree_structure_for_inspect_command(1,inspect_command_string);
}

/* G2-GET-INSPECT-GRAPH-SYSTEM-RPC-INTERNAL */
Object g2_get_inspect_graph_system_rpc_internal(gensymed_symbol,
	    inspect_command_string)
    Object gensymed_symbol, inspect_command_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(248,243);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_inspect_graph(inspect_command_string);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

void events_g2_INIT()
{
    Object temp, temp_1, reclaim_structure_for_pseudo_attribute_1;
    Object gensymed_symbol;
    Object Qg2_get_inspect_graph_system_rpc_internal, Qg2_get_inspect_graph;
    Object Qsystem_defined_rpc, list_constant_190, list_constant_201;
    Object list_constant_200, list_constant_170, Qinspect_command_string;
    Object AB_package, Qfunction_keeps_procedure_environment_valid_qm;
    Object list_constant_157, Qg2_get_module_hierarchy_system_rpc_internal;
    Object Qg2_get_module_hierarchy, list_constant_199, list_constant_198;
    Object list_constant_191, Qmodule_name_qm;
    Object Qg2_get_workspace_hierarchy_system_rpc_internal;
    Object Qg2_get_workspace_hierarchy, list_constant_197, list_constant_196;
    Object Qworkspace_name_qm, Qg2_get_class_hierarchy_system_rpc_internal;
    Object Qg2_get_class_hierarchy, list_constant_195, list_constant_194;
    Object Qclass_name_qm;
    Object Qg2_get_procedure_caller_hierarchy_system_rpc_internal;
    Object Qg2_get_procedure_caller_hierarchy, list_constant_193;
    Object Qg2_get_procedure_calling_hierarchy_system_rpc_internal;
    Object Qg2_get_procedure_calling_hierarchy, list_constant_192;
    Object Qprocedure_name_qm, list_constant_186;
    Object Qg2_get_procedure_invocation_hierarchy_system_rpc_internal;
    Object Qg2_get_procedure_invocation_hierarchy;
    Object Qg2_get_method_hierarchy_system_rpc_internal;
    Object Qg2_get_method_hierarchy, list_constant_112;
    Object Qg2_get_method_inheritance_path_system_rpc_internal;
    Object Qg2_get_method_inheritance_path, list_constant_189;
    Object list_constant_188, list_constant_35, list_constant_25, Qab_or;
    Object list_constant_187, list_constant_14, Qmethod_name_qm;
    Object list_constant_10, Qg2_get_description_of_item_system_rpc_internal;
    Object Qg2_get_description_of_item, list_constant_22, list_constant_72;
    Object Qg2_invoke_generic_event_rules_system_rpc_internal;
    Object Qg2_invoke_generic_event_rules, list_constant_185;
    Object list_constant_184, list_constant_6, list_constant_183;
    Object list_constant_96, Qevent_object, list_constant_13, Qevent_name;
    Object Qg2_clone_and_transfer_items_system_rpc_internal;
    Object Qg2_clone_and_transfer_items, list_constant_178;
    Object Qg2_move_items_system_rpc_internal, Qg2_move_items;
    Object list_constant_182, list_constant_181, list_constant_175;
    Object list_constant_177, list_constant_176;
    Object Qg2_move_items_enlarging_workspace_if_necessary_system_rpc_internal;
    Object Qg2_move_items_enlarging_workspace_if_necessary, list_constant_180;
    Object list_constant_179, list_constant_17;
    Object Qenlarge_workspace_if_necessary;
    Object Qg2_transfer_items_system_rpc_internal, Qg2_transfer_items;
    Object list_constant_97, list_constant_57, Qdelta_y, Qdelta_x;
    Object list_constant_31, Qsequence_of_items;
    Object Qg2_menu_of_names_for_category_system_rpc_internal, list_constant_5;
    Object list_constant_174, list_constant_150, list_constant_173;
    Object Qcategory_symbol;
    Object Qg2_parsing_context_insert_characters_system_rpc_internal;
    Object list_constant_172, list_constant_171, list_constant_167;
    Object list_constant_149, Qaddition, list_constant_151;
    Object Qg2_parsing_context_delete_characters_system_rpc_internal;
    Object list_constant_169, list_constant_168, Qnumber_of_chars;
    Object Qg2_adjust_cursor_position_system_rpc_internal, list_constant_166;
    Object list_constant_163, Qg2_shift_cursor_position_system_rpc_internal;
    Object list_constant_165, list_constant_164, list_constant_160;
    Object Qnew_position, list_constant_162;
    Object Qg2_update_parsing_context_system_rpc_internal, list_constant_161;
    Object list_constant_159, list_constant_158, Qthe_text, list_constant_73;
    Object Qadvance_index_qm, Qbackup_index_qm;
    Object Qg2_compile_parse_result_system_rpc_internal, list_constant_156;
    Object list_constant_155, list_constant_153;
    Object Qg2_commit_parse_result_system_rpc_internal, list_constant_154;
    Object Qediting_for_runtime_change_p;
    Object Qg2_delete_parsing_context_system_rpc_internal;
    Object Qg2_clear_parsing_context_system_rpc_internal;
    Object Qg2_set_editing_context_item_system_rpc_internal;
    Object Qg2_set_editing_context_item, list_constant_152;
    Object Qg2_parsing_context_get_text_system_rpc_internal;
    Object Qg2_validate_parsing_text, Qg2_simple_create_parsing_context;
    Object Qg2_simple_create_parsing_context_system_rpc_internal;
    Object list_constant_148, list_constant_147;
    Object Qg2_create_parsing_context_system_rpc_internal, list_constant_146;
    Object list_constant_145, list_constant_144, list_constant_143;
    Object list_constant_142, list_constant_141, Qslot_component_indicator_qm;
    Object Qslot_component_name_qm, Qattribute_name_qm, Qgrammar_category_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_confirm_available_handles_by_type_system_rpc_internal;
    Object Qg2_confirm_available_handles_by_type, list_constant_140;
    Object list_constant_139, list_constant_138;
    Object Qg2_get_connection_input_and_output_system_rpc_internal;
    Object Qg2_get_connection_input_and_output, list_constant_137;
    Object list_constant_136, list_constant_135, Qconnection;
    Object list_constant_127, Qg2_make_connection_for_user_system_rpc_internal;
    Object Qg2_make_connection_for_user, list_constant_134, list_constant_133;
    Object list_constant_132, list_constant_131, list_constant_130;
    Object list_constant_129, list_constant_128, Qspecific_client_or_false;
    Object Qposition_sequence, Qmode, Qother_item, Qitem_or_datum;
    Object Qloose_end_connection, Qab_class;
    Object Qg2_hide_workspace_system_rpc_internal, list_constant_126;
    Object list_constant_122, list_constant_48;
    Object Qg2_show_workspace_system_rpc_internal, list_constant_125;
    Object list_constant_124, Qshow_details_qm;
    Object Qg2_fire_user_menu_choice_system_rpc_internal, list_constant_42;
    Object list_constant_123, list_constant_121, list_constant_118;
    Object list_constant_120, Quser_menu_choice;
    Object Qg2_fire_action_button_system_rpc_internal, list_constant_119;
    Object list_constant_117, list_constant_116, Qspecific_client;
    Object list_constant_44, list_constant_115, Qaction_button;
    Object Qg2_get_g2_state_system_rpc_internal, Qg2_get_g2_state;
    Object Qg2_set_g2_state_system_rpc_internal, list_constant_114;
    Object list_constant_113, Qdesired_state;
    Object Qg2_get_methods_of_name_system_rpc_internal;
    Object Qg2_get_methods_of_name, list_constant_111, Qmethod_name;
    Object Qg2_get_methods_defined_for_class_system_rpc_internal;
    Object Qg2_get_methods_defined_for_class, list_constant_21;
    Object Qg2_get_list_memberships_system_rpc_internal;
    Object Qg2_get_list_memberships;
    Object Qg2_change_mode_for_window_system_rpc_internal, list_constant_110;
    Object list_constant_109, list_constant_108, Qnew_mode, list_constant_107;
    Object Qclient_item, Qui_client_item;
    Object Qg2_item_is_disabled_system_rpc_internal, Qg2_item_is_disabled;
    Object Qg2_disable_item_system_rpc_internal, Qg2_disable_item;
    Object Qg2_enable_item_system_rpc_internal, Qg2_enable_item;
    Object Qg2_get_direct_subclasses_system_rpc_internal;
    Object Qg2_get_direct_subclasses;
    Object Qg2_get_strict_instances_of_class_system_rpc_internal;
    Object Qg2_get_strict_instances_of_class;
    Object Qg2_get_user_menu_choice_system_rpc_internal, list_constant_82;
    Object list_constant_106, list_constant_105, list_constant_104;
    Object Qapplicable_class_qm, Qlabel;
    Object Qg2_get_current_user_menu_choices_for_session_system_rpc_internal;
    Object list_constant_103, list_constant_47;
    Object Qg2_get_current_user_menu_choices_system_rpc_internal;
    Object list_constant_102, list_constant_101, Quser_mode, list_constant_100;
    Object Qg2_window, Qg2_get_containment_hierarchy_system_rpc_internal;
    Object Qg2_make_subworkspace_system_rpc_internal, Qg2_make_subworkspace;
    Object list_constant_99, list_constant_98, Qtarget_item, list_constant_71;
    Object list_constant_95, list_constant_45;
    Object Qg2_get_origin_of_message_system_rpc_internal;
    Object Qg2_get_origin_of_message, list_constant_94, list_constant_93;
    Object list_constant_92, Qtext_box, Qg2_name_for_item_system_rpc_internal;
    Object Qg2_name_for_item, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_88, list_constant_87, Qframe;
    Object Qg2_get_referenced_items_system_rpc_internal;
    Object Qg2_get_referenced_items, list_constant_86, list_constant_85;
    Object list_constant_46, list_constant_84, list_constant_83, Qmessage;
    Object Qg2_get_subworkspace_system_rpc_internal, Qg2_get_subworkspace;
    Object list_constant_81, Qg2_make_transient_system_rpc_internal;
    Object Qg2_make_transient, Qget_transient, Qinitial_transient;
    Object list_constant_4, Qtransient, Qg2_make_permanent_system_rpc_internal;
    Object Qg2_make_permanent, Qset_manually_disabled_qm;
    Object Qget_manually_disabled_qm, Qinitial_manually_disabled_qm;
    Object Qmanually_disabled_qm, Qget_permanent, Qinitial_permanent;
    Object Qpermanent, Qg2_delete_item_system_rpc_internal, Qg2_delete_item;
    Object list_constant_80, list_constant_79, list_constant_78;
    Object Qwithout_leaving_stubs_p, Qwithout_permanence_checks_p;
    Object Qg2_transfer_item_system_rpc_internal, Qg2_transfer_item;
    Object list_constant_77, list_constant_76, list_constant_75;
    Object list_constant_59, list_constant_58, list_constant_74;
    Object Qclass_qualifier_or_false, Qattribute_name_or_false;
    Object Qg2_clone_item_system_rpc_internal, Qg2_clone_item;
    Object Qg2_create_item_system_rpc_internal, Qg2_create_item;
    Object Qg2_move_items_along_paths, Qg2_move_ws_item_by_system_rpc_internal;
    Object Qg2_move_ws_item_by, list_constant_70, list_constant_69;
    Object list_constant_68, list_constant_67, list_constant_61;
    Object list_constant_60, Qdeltay, Qdeltax;
    Object Qg2_enable_all_items_system_rpc_internal, Qg2_enable_all_items;
    Object Qg2_flush_all_change_logs_system_rpc_internal;
    Object Qg2_flush_all_change_logs;
    Object Qg2_make_kb_proprietary_system_rpc_internal;
    Object Qg2_make_kb_proprietary, Qg2_strip_all_texts_system_rpc_internal;
    Object Qg2_strip_all_texts;
    Object Qg2_get_simulate_proprietary_mode_system_rpc_internal;
    Object Qg2_get_simulate_proprietary_mode;
    Object Qg2_set_simulate_proprietary_mode_system_rpc_internal;
    Object Qg2_set_simulate_proprietary_mode, list_constant_66;
    Object Qg2_get_package_preparation_mode_system_rpc_internal;
    Object Qg2_get_package_preparation_mode;
    Object Qg2_set_package_preparation_mode_system_rpc_internal;
    Object Qg2_set_package_preparation_mode, list_constant_65, Qnew_state;
    Object Qg2_clear_kb_system_rpc_internal, Qg2_clear_kb;
    Object Qg2_shutdown_g2_process_system_rpc_internal;
    Object Qg2_shutdown_g2_process, list_constant_64, list_constant_63;
    Object Qstatus, Qg2_move_ws_item_system_rpc_internal, Qg2_move_ws_item;
    Object list_constant_62, Qtransient_change_p_ev;
    Object Qenlarge_workspace_if_necessary_p_ev, Qypos, Qxpos;
    Object Qg2_unrepresent_workspace_system_rpc_internal;
    Object Qg2_unrepresent_workspace, list_constant_56, list_constant_55;
    Object Qg2_represent_trend_chart_system_rpc_internal, list_constant_54;
    Object list_constant_53, list_constant_51;
    Object Qg2_represent_workspace_system_rpc_internal, list_constant_52;
    Object Qcallback_procedure;
    Object Qg2_get_updated_workspace_information_system_rpc_internal;
    Object list_constant_50, list_constant_49, Qattributes, Qworkspace;
    Object Qsession, list_constant_43, Qitem_configuration;
    Object Qg2_set_v5_mode_system_rpc_internal, Qg2_set_v5_mode;
    Object list_constant_41, list_constant_40, Qstate;
    Object Qg2_get_list_of_workspaces_system_rpc_internal;
    Object Qg2_get_list_of_workspaces, Qg2_get_class_hash_system_rpc_internal;
    Object Qg2_get_class_hash, list_constant_39, list_constant_38;
    Object Qunsigned_vector_16, Qg2_get_format_info_system_rpc_internal;
    Object Qg2_get_format_info, list_constant_37, list_constant_36;
    Object Qg2_get_multiple_class_attribute_values;
    Object Qg2_get_multiple_class_attribute_values_system_rpc_internal;
    Object list_constant_34, list_constant_33, list_constant_32, Qclass_names;
    Object Qg2_get_attributes_from_class_system_rpc_internal;
    Object Qg2_get_attributes_from_class, list_constant_28, list_constant_30;
    Object list_constant_29, list_constant_23;
    Object Qg2_get_attribute_from_class_system_rpc_internal;
    Object Qg2_get_attribute_from_class, list_constant_27, list_constant_26;
    Object Qno_item, list_constant_24, Qclassname;
    Object Qg2_get_short_class_info_system_rpc_internal;
    Object Qg2_get_short_class_info;
    Object Qg2_get_class_inheritance_path_system_rpc_internal;
    Object Qg2_get_class_inheritance_path, list_constant_20;
    Object Qg2_include_method_text_in_export_system_rpc_internal;
    Object Qg2_include_method_text_in_export, list_constant_19;
    Object list_constant_18, Qinclude_method_text;
    Object Qg2_get_class_info_system_rpc_internal, Qg2_get_class_info;
    Object list_constant_16, list_constant_15, Qinclude_inherited_attributes_p;
    Object Qab_class_name, Qentity, list_constant_12;
    Object Qsystem_menu_choices_pseudo_attribute_getter, Qsystem_menu_choices;
    Object list_constant_11;
    Object Qdefault_readout_table_format_name_pseudo_attribute_getter;
    Object Qreadout_table;
    Object Qdefault_text_box_format_name_pseudo_attribute_getter;
    Object Qkb_workspace_initial_height_pseudo_attribute_getter;
    Object Qkb_workspace_initial_width_pseudo_attribute_getter;
    Object Qdefault_message_properties_pseudo_attribute_getter;
    Object Qdefault_message_properties;
    Object Qjunction_block_class_pseudo_attribute_getter;
    Object Qstub_length_pseudo_attribute_getter;
    Object Qcross_section_pattern_pseudo_attribute_getter;
    Object Qicon_description_pseudo_attribute_getter;
    Object Qinclude_in_menus_pseudo_attribute_getter, Qinclude_in_menus;
    Object Qinstantiate_pseudo_attribute_getter, Qinstantiate;
    Object Qclass_inheritance_path_pseudo_attribute_getter;
    Object Qpart_of_class_info, Qclass_inheritance_path;
    Object Qdirect_superior_classes_pseudo_attribute_getter;
    Object Qdirect_superior_classes;
    Object Qis_system_defined_pseudo_attribute_getter;
    Object Qclass_name_pseudo_attribute_getter, Qclass_info_key;
    Object Qreclaim_structure, Qoutstanding_pseudo_attribute_count;
    Object Qpseudo_attribute_structure_memory_usage, Qutilities2;
    Object string_constant_43, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_42, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qg2_get_text_of_attribute_system_rpc_internal;
    Object Qg2_get_text_of_attribute, list_constant_9, list_constant_8;
    Object list_constant_7, Qclass_if_specific, Qdatum, Qpretty_slot_name;

    x_note_fn_call(248,244);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qno_slot_description_error = STATIC_SYMBOL("NO-SLOT-DESCRIPTION-ERROR",
	    AB_package);
    Qg2_get_text_of_attribute = STATIC_SYMBOL("G2-GET-TEXT-OF-ATTRIBUTE",
	    AB_package);
    Qg2_get_text_of_attribute_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-TEXT-OF-ATTRIBUTE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qitem,Ktype,list_constant_4);
    Qpretty_slot_name = STATIC_SYMBOL("PRETTY-SLOT-NAME",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qpretty_slot_name,Ktype,Qsymbol);
    Qclass_if_specific = STATIC_SYMBOL("CLASS-IF-SPECIFIC",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_5 = STATIC_CONS(Qdatum,Qnil);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)3L,Qclass_if_specific,
	    Ktype,list_constant_5);
    list_constant_9 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_7,list_constant_8);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_get_text_of_attribute,
	    make_system_rpc_1(Qg2_get_text_of_attribute_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_9,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_text_of_attribute,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qundefined_attribute_for_class = 
	    STATIC_SYMBOL("UNDEFINED-ATTRIBUTE-FOR-CLASS",AB_package);
    string_constant = STATIC_STRING("attribute not defined ~NQ");
    SET_SYMBOL_FUNCTION(Qg2_get_text_of_attribute_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_text_of_attribute_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qicon_description_qm = STATIC_SYMBOL("ICON-DESCRIPTION\?",AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_pseudo_attribute_g2_struct = 
	    STATIC_SYMBOL("PSEUDO-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpseudo_attribute = STATIC_SYMBOL("PSEUDO-ATTRIBUTE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_attribute_g2_struct,
	    Qpseudo_attribute,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qpseudo_attribute,
	    Qg2_defstruct_structure_name_pseudo_attribute_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_pseudo_attribute == UNBOUND)
	The_type_description_of_pseudo_attribute = Nil;
    string_constant_42 = 
	    STATIC_STRING("43Dy8m83loy1n83loy8n8k1l8n0000001l1n8y83-5By1l83-9Yykpk0k0");
    temp_1 = The_type_description_of_pseudo_attribute;
    The_type_description_of_pseudo_attribute = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_42));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_pseudo_attribute_g2_struct,
	    The_type_description_of_pseudo_attribute,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qpseudo_attribute,
	    The_type_description_of_pseudo_attribute,
	    Qtype_description_of_type);
    Qoutstanding_pseudo_attribute_count = 
	    STATIC_SYMBOL("OUTSTANDING-PSEUDO-ATTRIBUTE-COUNT",AB_package);
    Qpseudo_attribute_structure_memory_usage = 
	    STATIC_SYMBOL("PSEUDO-ATTRIBUTE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_43 = STATIC_STRING("1q83loy8s83-key09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_pseudo_attribute_count);
    push_optimized_constant(Qpseudo_attribute_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_43));
    Qchain_of_available_pseudo_attributes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PSEUDO-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_pseudo_attributes,
	    Chain_of_available_pseudo_attributes);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_pseudo_attributes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qpseudo_attribute_count = STATIC_SYMBOL("PSEUDO-ATTRIBUTE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpseudo_attribute_count,Pseudo_attribute_count);
    record_system_variable(Qpseudo_attribute_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_pseudo_attributes_vector == UNBOUND)
	Chain_of_available_pseudo_attributes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpseudo_attribute_structure_memory_usage,
	    STATIC_FUNCTION(pseudo_attribute_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_pseudo_attribute_count,
	    STATIC_FUNCTION(outstanding_pseudo_attribute_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_pseudo_attribute_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_pseudo_attribute,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpseudo_attribute,
	    reclaim_structure_for_pseudo_attribute_1);
    Pseudo_attribute_prop = Qpseudo_attribute;
    if (Static_attributes == UNBOUND)
	Static_attributes = Nil;
    if (Class_info_attributes == UNBOUND)
	Class_info_attributes = Nil;
    Qclass_info_key = STATIC_SYMBOL("CLASS-INFO-KEY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclass_info_key,Class_info_key);
    Qpart_of_class_info = STATIC_SYMBOL("PART-OF-CLASS-INFO",AB_package);
    SET_SYMBOL_VALUE(Qclass_info_key,Qpart_of_class_info);
    list_constant = STATIC_CONS(Qpart_of_class_info,Qnil);
    Qtype_specification_explicit_complex_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-EXPLICIT-COMPLEX-TYPE",
	    AB_package);
    Qclass_name_pseudo_attribute_getter = 
	    STATIC_SYMBOL("CLASS-NAME-PSEUDO-ATTRIBUTE-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qclass_name_pseudo_attribute_getter,
	    STATIC_FUNCTION(class_name_pseudo_attribute_getter,NIL,FALSE,1,1));
    Qab_class_name = STATIC_SYMBOL("CLASS-NAME",AB_package);
    add_pseudo_attribute(Qab_class_name,Qpart_of_class_info,
	    Qclass_name_pseudo_attribute_getter,Qsymbol);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qis_system_defined_pseudo_attribute_getter = 
	    STATIC_SYMBOL("IS-SYSTEM-DEFINED-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qis_system_defined_pseudo_attribute_getter,
	    STATIC_FUNCTION(is_system_defined_pseudo_attribute_getter,NIL,
	    FALSE,1,1));
    Qis_system_defined = STATIC_SYMBOL("IS-SYSTEM-DEFINED",AB_package);
    add_pseudo_attribute(Qis_system_defined,Qpart_of_class_info,
	    Qis_system_defined_pseudo_attribute_getter,Qsymbol);
    Qdirect_superior_classes_pseudo_attribute_getter = 
	    STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdirect_superior_classes_pseudo_attribute_getter,
	    STATIC_FUNCTION(direct_superior_classes_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qdirect_superior_classes = STATIC_SYMBOL("DIRECT-SUPERIOR-CLASSES",
	    AB_package);
    list_constant_10 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_10,
	    FIX((SI_Long)0L));
    add_pseudo_attribute(Qdirect_superior_classes,Qpart_of_class_info,
	    Qdirect_superior_classes_pseudo_attribute_getter,list_constant_11);
    Qclass_inheritance_path_pseudo_attribute_getter = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qclass_inheritance_path_pseudo_attribute_getter,
	    STATIC_FUNCTION(class_inheritance_path_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qclass_inheritance_path = STATIC_SYMBOL("CLASS-INHERITANCE-PATH",
	    AB_package);
    add_pseudo_attribute(Qclass_inheritance_path,Qpart_of_class_info,
	    Qclass_inheritance_path_pseudo_attribute_getter,list_constant_11);
    Qnot_user_instantiable = STATIC_SYMBOL("NOT-USER-INSTANTIABLE",AB_package);
    Qnot_solely_instantiable = STATIC_SYMBOL("NOT-SOLELY-INSTANTIABLE",
	    AB_package);
    Qinstantiate_pseudo_attribute_getter = 
	    STATIC_SYMBOL("INSTANTIATE-PSEUDO-ATTRIBUTE-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qinstantiate_pseudo_attribute_getter,
	    STATIC_FUNCTION(instantiate_pseudo_attribute_getter,NIL,FALSE,
	    1,1));
    Qinstantiate = STATIC_SYMBOL("INSTANTIATE",AB_package);
    add_pseudo_attribute(Qinstantiate,Qblock,
	    Qinstantiate_pseudo_attribute_getter,Qtruth_value);
    Qinclude_in_menus_pseudo_attribute_getter = 
	    STATIC_SYMBOL("INCLUDE-IN-MENUS-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinclude_in_menus_pseudo_attribute_getter,
	    STATIC_FUNCTION(include_in_menus_pseudo_attribute_getter,NIL,
	    FALSE,1,1));
    Qinclude_in_menus = STATIC_SYMBOL("INCLUDE-IN-MENUS",AB_package);
    add_pseudo_attribute(Qinclude_in_menus,Qblock,
	    Qinclude_in_menus_pseudo_attribute_getter,Qtruth_value);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qicon_description_pseudo_attribute_getter = 
	    STATIC_SYMBOL("ICON-DESCRIPTION-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qicon_description_pseudo_attribute_getter,
	    STATIC_FUNCTION(icon_description_pseudo_attribute_getter,NIL,
	    FALSE,1,1));
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    add_pseudo_attribute(Qicon_description,Qentity,
	    Qicon_description_pseudo_attribute_getter,Qicon_description_qm);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qcross_section_pattern_pseudo_attribute_getter = 
	    STATIC_SYMBOL("CROSS-SECTION-PATTERN-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcross_section_pattern_pseudo_attribute_getter,
	    STATIC_FUNCTION(cross_section_pattern_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    add_pseudo_attribute(Qcross_section_pattern,Qconnection,
	    Qcross_section_pattern_pseudo_attribute_getter,
	    Qcross_section_pattern);
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qstub_length_pseudo_attribute_getter = 
	    STATIC_SYMBOL("STUB-LENGTH-PSEUDO-ATTRIBUTE-GETTER",AB_package);
    SET_SYMBOL_FUNCTION(Qstub_length_pseudo_attribute_getter,
	    STATIC_FUNCTION(stub_length_pseudo_attribute_getter,NIL,FALSE,
	    1,1));
    add_pseudo_attribute(Qstub_length,Qconnection,
	    Qstub_length_pseudo_attribute_getter,Qstub_length);
    Qjunction_class = STATIC_SYMBOL("JUNCTION-CLASS",AB_package);
    Qjunction_block_class = STATIC_SYMBOL("JUNCTION-BLOCK-CLASS",AB_package);
    Qjunction_block_class_pseudo_attribute_getter = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-CLASS-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qjunction_block_class_pseudo_attribute_getter,
	    STATIC_FUNCTION(junction_block_class_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    add_pseudo_attribute(Qjunction_block_class,Qconnection,
	    Qjunction_block_class_pseudo_attribute_getter,Qjunction_class);
    Qmessage_properties = STATIC_SYMBOL("MESSAGE-PROPERTIES",AB_package);
    Qdefault_message_properties_for_class = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES-FOR-CLASS",AB_package);
    Qdefault_message_properties_pseudo_attribute_getter = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdefault_message_properties_pseudo_attribute_getter,
	    STATIC_FUNCTION(default_message_properties_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qdefault_message_properties = 
	    STATIC_SYMBOL("DEFAULT-MESSAGE-PROPERTIES",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    add_pseudo_attribute(Qdefault_message_properties,Qmessage,
	    Qdefault_message_properties_pseudo_attribute_getter,
	    Qmessage_properties);
    Qpositive_integer = STATIC_SYMBOL("POSITIVE-INTEGER",AB_package);
    Qkb_workspace_initial_width = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH",AB_package);
    Qkb_workspace_initial_width_pseudo_attribute_getter = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qkb_workspace_initial_width_pseudo_attribute_getter,
	    STATIC_FUNCTION(kb_workspace_initial_width_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    add_pseudo_attribute(Qkb_workspace_initial_width,Qkb_workspace,
	    Qkb_workspace_initial_width_pseudo_attribute_getter,
	    Qpositive_integer);
    Qkb_workspace_initial_height = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT",AB_package);
    Qkb_workspace_initial_height_pseudo_attribute_getter = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qkb_workspace_initial_height_pseudo_attribute_getter,
	    STATIC_FUNCTION(kb_workspace_initial_height_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    add_pseudo_attribute(Qkb_workspace_initial_height,Qkb_workspace,
	    Qkb_workspace_initial_height_pseudo_attribute_getter,
	    Qpositive_integer);
    Qdefault_text_box_format_name = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME",AB_package);
    Qdefault_text_box_format_name_pseudo_attribute_getter = 
	    STATIC_SYMBOL("DEFAULT-TEXT-BOX-FORMAT-NAME-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdefault_text_box_format_name_pseudo_attribute_getter,
	    STATIC_FUNCTION(default_text_box_format_name_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    add_pseudo_attribute(Qdefault_text_box_format_name,Qtext_box,
	    Qdefault_text_box_format_name_pseudo_attribute_getter,Qsymbol);
    Qdefault_readout_table_format_name = 
	    STATIC_SYMBOL("DEFAULT-READOUT-TABLE-FORMAT-NAME",AB_package);
    Qdefault_readout_table_format_name_pseudo_attribute_getter = 
	    STATIC_SYMBOL("DEFAULT-READOUT-TABLE-FORMAT-NAME-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdefault_readout_table_format_name_pseudo_attribute_getter,
	    STATIC_FUNCTION(default_readout_table_format_name_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    add_pseudo_attribute(Qdefault_readout_table_format_name,Qreadout_table,
	    Qdefault_readout_table_format_name_pseudo_attribute_getter,
	    Qsymbol);
    Qsystem_menu_choices_pseudo_attribute_getter = 
	    STATIC_SYMBOL("SYSTEM-MENU-CHOICES-PSEUDO-ATTRIBUTE-GETTER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_menu_choices_pseudo_attribute_getter,
	    STATIC_FUNCTION(system_menu_choices_pseudo_attribute_getter,
	    NIL,FALSE,1,1));
    Qsystem_menu_choices = STATIC_SYMBOL("SYSTEM-MENU-CHOICES",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_11,
	    Qno_item);
    add_pseudo_attribute(Qsystem_menu_choices,Qblock,
	    Qsystem_menu_choices_pseudo_attribute_getter,list_constant_12);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_readable = STATIC_SYMBOL("TEXT-READABLE",AB_package);
    Qtext_writable = STATIC_SYMBOL("TEXT-WRITABLE",AB_package);
    Qvalue_readable = STATIC_SYMBOL("VALUE-READABLE",AB_package);
    Qvalue_writable = STATIC_SYMBOL("VALUE-WRITABLE",AB_package);
    Qdefining_class = STATIC_SYMBOL("DEFINING-CLASS",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    Qdeprecated = STATIC_SYMBOL("DEPRECATED",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    Qno_such_class_error = STATIC_SYMBOL("NO-SUCH-CLASS-ERROR",AB_package);
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    Qclass_attributes = STATIC_SYMBOL("CLASS-ATTRIBUTES",AB_package);
    Qinstance_attributes = STATIC_SYMBOL("INSTANCE-ATTRIBUTES",AB_package);
    Qg2_get_class_info = STATIC_SYMBOL("G2-GET-CLASS-INFO",AB_package);
    Qg2_get_class_info_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CLASS-INFO-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_13 = STATIC_CONS(Ktype,list_constant_10);
    list_constant_14 = STATIC_CONS(Qab_class_name,list_constant_13);
    Qinclude_inherited_attributes_p = 
	    STATIC_SYMBOL("INCLUDE-INHERITED-ATTRIBUTES-P",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,
	    Qinclude_inherited_attributes_p,Ktype,Qtruth_value);
    list_constant_16 = STATIC_LIST((SI_Long)2L,list_constant_14,
	    list_constant_15);
    mutate_global_property(Qg2_get_class_info,
	    make_system_rpc_1(Qg2_get_class_info_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_16,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_class_info,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_class_info_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_class_info_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qinclude_method_text_in_class_export = 
	    STATIC_SYMBOL("INCLUDE-METHOD-TEXT-IN-CLASS-EXPORT",AB_package);
    Qg2_include_method_text_in_export = 
	    STATIC_SYMBOL("G2-INCLUDE-METHOD-TEXT-IN-EXPORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_include_method_text_in_export,
	    STATIC_FUNCTION(g2_include_method_text_in_export,NIL,FALSE,1,1));
    Qg2_include_method_text_in_export_system_rpc_internal = 
	    STATIC_SYMBOL("G2-INCLUDE-METHOD-TEXT-IN-EXPORT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qinclude_method_text = STATIC_SYMBOL("INCLUDE-METHOD-TEXT",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Ktype,Qtruth_value);
    list_constant_18 = STATIC_CONS(Qinclude_method_text,list_constant_17);
    list_constant_19 = STATIC_CONS(list_constant_18,Qnil);
    mutate_global_property(Qg2_include_method_text_in_export,
	    make_system_rpc_1(Qg2_include_method_text_in_export_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_19,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_include_method_text_in_export,System_defined_rpcs);
    System_defined_rpcs = temp;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_include_method_text_in_export_system_rpc_internal,
	    STATIC_FUNCTION(g2_include_method_text_in_export_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_class_inheritance_path = 
	    STATIC_SYMBOL("G2-GET-CLASS-INHERITANCE-PATH",AB_package);
    Qg2_get_class_inheritance_path_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CLASS-INHERITANCE-PATH-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_21 = STATIC_CONS(list_constant_14,Qnil);
    list_constant_20 = STATIC_CONS(Qsequence,Qnil);
    list_constant_22 = STATIC_CONS(list_constant_20,Qnil);
    mutate_global_property(Qg2_get_class_inheritance_path,
	    make_system_rpc_1(Qg2_get_class_inheritance_path_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_class_inheritance_path,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_class_inheritance_path_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_class_inheritance_path_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qdefinition = STATIC_SYMBOL("DEFINITION",AB_package);
    Qg2_get_short_class_info = STATIC_SYMBOL("G2-GET-SHORT-CLASS-INFO",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_short_class_info,
	    STATIC_FUNCTION(g2_get_short_class_info,NIL,FALSE,1,1));
    Qg2_get_short_class_info_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-SHORT-CLASS-INFO-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_short_class_info,
	    make_system_rpc_1(Qg2_get_short_class_info_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_short_class_info,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_short_class_info_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_short_class_info_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_attribute_from_class = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-FROM-CLASS",AB_package);
    Qg2_get_attribute_from_class_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-FROM-CLASS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclassname = STATIC_SYMBOL("CLASSNAME",AB_package);
    list_constant_23 = STATIC_CONS(Qclassname,list_constant_13);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_24 = STATIC_CONS(Qattribute,list_constant_13);
    list_constant_27 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_24);
    list_constant_25 = STATIC_CONS(Qno_item,Qnil);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_25,list_constant_5);
    list_constant_28 = STATIC_CONS(list_constant_26,Qnil);
    mutate_global_property(Qg2_get_attribute_from_class,
	    make_system_rpc_1(Qg2_get_attribute_from_class_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_27,
	    Nil,T),list_constant_28),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_attribute_from_class,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qg2_defstruct_structure_name_access_error_g2_struct = 
	    STATIC_SYMBOL("ACCESS-ERROR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_from_class_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attribute_from_class_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_attributes_from_class = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTES-FROM-CLASS",AB_package);
    Qg2_get_attributes_from_class_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTES-FROM-CLASS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,Qattributes,Ktype,
	    list_constant_22);
    list_constant_30 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_29);
    mutate_global_property(Qg2_get_attributes_from_class,
	    make_system_rpc_1(Qg2_get_attributes_from_class_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_30,
	    Nil,T),list_constant_28),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_attributes_from_class,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_attributes_from_class_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attributes_from_class_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_multiple_class_attribute_values = 
	    STATIC_SYMBOL("G2-GET-MULTIPLE-CLASS-ATTRIBUTE-VALUES",AB_package);
    Qg2_get_multiple_class_attribute_values_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-MULTIPLE-CLASS-ATTRIBUTE-VALUES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclass_names = STATIC_SYMBOL("CLASS-NAMES",AB_package);
    list_constant_31 = STATIC_CONS(Ktype,list_constant_22);
    list_constant_32 = STATIC_CONS(Qclass_names,list_constant_31);
    list_constant_34 = STATIC_CONS(list_constant_32,Qnil);
    list_constant_33 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_35 = STATIC_CONS(list_constant_33,Qnil);
    mutate_global_property(Qg2_get_multiple_class_attribute_values,
	    make_system_rpc_1(Qg2_get_multiple_class_attribute_values_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_34,
	    Nil,T),list_constant_35),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_multiple_class_attribute_values,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_multiple_class_attribute_values_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_multiple_class_attribute_values_system_rpc_internal,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qg2_get_multiple_class_attribute_values,
	    STATIC_FUNCTION(g2_get_multiple_class_attribute_values,NIL,
	    FALSE,1,1));
    Qg2_get_format_info = STATIC_SYMBOL("G2-GET-FORMAT-INFO",AB_package);
    Qg2_get_format_info_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-FORMAT-INFO-SYSTEM-RPC-INTERNAL",AB_package);
    Qformat_name = STATIC_SYMBOL("FORMAT-NAME",AB_package);
    list_constant_36 = STATIC_CONS(Qformat_name,list_constant_13);
    list_constant_37 = STATIC_CONS(list_constant_36,Qnil);
    mutate_global_property(Qg2_get_format_info,
	    make_system_rpc_1(Qg2_get_format_info_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_37,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_format_info,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    Qno_such_format_error = STATIC_SYMBOL("NO-SUCH-FORMAT-ERROR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_format_info_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_format_info_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qab_font = STATIC_SYMBOL("AB-FONT",AB_package);
    Qfixed14 = STATIC_SYMBOL("FIXED14",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qg2_get_class_hash = STATIC_SYMBOL("G2-GET-CLASS-HASH",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_class_hash,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_1 = STATIC_STRING("~A does not name a class");
    SET_SYMBOL_FUNCTION(Qg2_get_class_hash,
	    STATIC_FUNCTION(g2_get_class_hash,NIL,FALSE,1,1));
    Qg2_get_class_hash_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CLASS-HASH-SYSTEM-RPC-INTERNAL",AB_package);
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    list_constant_38 = STATIC_CONS(Qunsigned_vector_16,Qnil);
    list_constant_39 = STATIC_CONS(list_constant_38,Qnil);
    mutate_global_property(Qg2_get_class_hash,
	    make_system_rpc_1(Qg2_get_class_hash_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_39),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_class_hash,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_class_hash_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_class_hash_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_get_list_of_workspaces = STATIC_SYMBOL("G2-GET-LIST-OF-WORKSPACES",
	    AB_package);
    Qg2_get_list_of_workspaces_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-LIST-OF-WORKSPACES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_list_of_workspaces,
	    make_system_rpc_1(Qg2_get_list_of_workspaces_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_list_of_workspaces,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_list_of_workspaces_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_list_of_workspaces_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qg2_set_v5_mode = STATIC_SYMBOL("G2-SET-V5-MODE",AB_package);
    Qg2_set_v5_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-V5-MODE-SYSTEM-RPC-INTERNAL",AB_package);
    Qstate = STATIC_SYMBOL("STATE",AB_package);
    list_constant_40 = STATIC_CONS(Qstate,list_constant_17);
    list_constant_41 = STATIC_CONS(list_constant_40,Qnil);
    list_constant_42 = STATIC_CONS(Qtruth_value,Qnil);
    mutate_global_property(Qg2_set_v5_mode,
	    make_system_rpc_1(Qg2_set_v5_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_41,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_v5_mode,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_v5_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_v5_mode_system_rpc_internal,NIL,FALSE,2,2));
    Qitem_configuration = STATIC_SYMBOL("ITEM-CONFIGURATION",AB_package);
    list_constant_43 = STATIC_CONS(Qitem_configuration,Qnil);
    if (Ws_representation_slots_to_update == UNBOUND)
	Ws_representation_slots_to_update = list_constant_43;
    Qg2_get_updated_workspace_information = 
	    STATIC_SYMBOL("G2-GET-UPDATED-WORKSPACE-INFORMATION",AB_package);
    Qg2_get_updated_workspace_information_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-UPDATED-WORKSPACE-INFORMATION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qsession = STATIC_SYMBOL("SESSION",AB_package);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qab_class,Qui_client_session);
    list_constant_47 = STATIC_LIST((SI_Long)3L,Qsession,Ktype,
	    list_constant_44);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qab_class,Qkb_workspace);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qworkspace,Ktype,
	    list_constant_45);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_25,list_constant_22);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qattributes,Ktype,
	    list_constant_46);
    list_constant_50 = STATIC_LIST((SI_Long)3L,list_constant_47,
	    list_constant_48,list_constant_49);
    mutate_global_property(Qg2_get_updated_workspace_information,
	    make_system_rpc_1(Qg2_get_updated_workspace_information_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_50,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_updated_workspace_information,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_updated_workspace_information_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_updated_workspace_information_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_represent_workspace = STATIC_SYMBOL("G2-REPRESENT-WORKSPACE",
	    AB_package);
    Qg2_represent_workspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-REPRESENT-WORKSPACE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qcallback_procedure = STATIC_SYMBOL("CALLBACK-PROCEDURE",AB_package);
    list_constant_51 = STATIC_CONS(Qcallback_procedure,list_constant_13);
    list_constant_52 = STATIC_LIST((SI_Long)3L,list_constant_47,
	    list_constant_48,list_constant_51);
    mutate_global_property(Qg2_represent_workspace,
	    make_system_rpc_1(Qg2_represent_workspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_52,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_represent_workspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qws_representation = STATIC_SYMBOL("WS-REPRESENTATION",AB_package);
    Qreturn_type = STATIC_SYMBOL("RETURN-TYPE",AB_package);
    Qsession_association_confirmation = 
	    STATIC_SYMBOL("SESSION-ASSOCIATION-CONFIRMATION",AB_package);
    Qsubscription_handle = STATIC_SYMBOL("SUBSCRIPTION-HANDLE",AB_package);
    Qsession_already_associated = 
	    STATIC_SYMBOL("SESSION-ALREADY-ASSOCIATED",AB_package);
    string_constant_2 = 
	    STATIC_STRING("session already associated with workspace");
    Qinitial_subscription_data = STATIC_SYMBOL("INITIAL-SUBSCRIPTION-DATA",
	    AB_package);
    Qworkspace_initial_data = STATIC_SYMBOL("WORKSPACE-INITIAL-DATA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_represent_workspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_represent_workspace_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_represent_trend_chart = STATIC_SYMBOL("G2-REPRESENT-TREND-CHART",
	    AB_package);
    Qg2_represent_trend_chart_system_rpc_internal = 
	    STATIC_SYMBOL("G2-REPRESENT-TREND-CHART-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_53 = STATIC_CONS(list_constant_51,Qnil);
    list_constant_54 = STATIC_CONS(list_constant_6,list_constant_53);
    mutate_global_property(Qg2_represent_trend_chart,
	    make_system_rpc_1(Qg2_represent_trend_chart_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_54,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_represent_trend_chart,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    Qitem_initial_data = STATIC_SYMBOL("ITEM-INITIAL-DATA",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_represent_trend_chart_system_rpc_internal,
	    STATIC_FUNCTION(g2_represent_trend_chart_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_unrepresent_workspace = STATIC_SYMBOL("G2-UNREPRESENT-WORKSPACE",
	    AB_package);
    Qg2_unrepresent_workspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UNREPRESENT-WORKSPACE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qsubscription_handle,Ktype,
	    Qinteger);
    list_constant_56 = STATIC_LIST((SI_Long)2L,list_constant_47,
	    list_constant_55);
    mutate_global_property(Qg2_unrepresent_workspace,
	    make_system_rpc_1(Qg2_unrepresent_workspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_56,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_unrepresent_workspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qsession_and_workspace_not_associated = 
	    STATIC_SYMBOL("SESSION-AND-WORKSPACE-NOT-ASSOCIATED",AB_package);
    string_constant_3 = STATIC_STRING("session and workspace not associated");
    SET_SYMBOL_FUNCTION(Qg2_unrepresent_workspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_unrepresent_workspace_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_move_ws_item = STATIC_SYMBOL("G2-MOVE-WS-ITEM",AB_package);
    Qg2_move_ws_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MOVE-WS-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    Qxpos = STATIC_SYMBOL("XPOS",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Ktype,Qinteger);
    list_constant_58 = STATIC_CONS(Qxpos,list_constant_57);
    Qypos = STATIC_SYMBOL("YPOS",AB_package);
    list_constant_59 = STATIC_CONS(Qypos,list_constant_57);
    Qenlarge_workspace_if_necessary_p_ev = 
	    STATIC_SYMBOL("ENLARGE-WORKSPACE-IF-NECESSARY-P-EV",AB_package);
    list_constant_60 = STATIC_CONS(Qenlarge_workspace_if_necessary_p_ev,
	    list_constant_17);
    Qtransient_change_p_ev = STATIC_SYMBOL("TRANSIENT-CHANGE-P-EV",AB_package);
    list_constant_61 = STATIC_CONS(Qtransient_change_p_ev,list_constant_17);
    list_constant_62 = STATIC_LIST((SI_Long)5L,list_constant_6,
	    list_constant_58,list_constant_59,list_constant_60,
	    list_constant_61);
    mutate_global_property(Qg2_move_ws_item,
	    make_system_rpc_1(Qg2_move_ws_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_62,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_move_ws_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qis_moved_by_the_user = STATIC_SYMBOL("IS-MOVED-BY-THE-USER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_move_ws_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_move_ws_item_system_rpc_internal,NIL,FALSE,
	    6,6));
    Qg2_shutdown_g2_process = STATIC_SYMBOL("G2-SHUTDOWN-G2-PROCESS",
	    AB_package);
    Qg2_shutdown_g2_process_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SHUTDOWN-G2-PROCESS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    list_constant_63 = STATIC_CONS(Qstatus,list_constant_13);
    list_constant_64 = STATIC_CONS(list_constant_63,Qnil);
    mutate_global_property(Qg2_shutdown_g2_process,
	    make_system_rpc_1(Qg2_shutdown_g2_process_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_64,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_shutdown_g2_process,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_shutdown_g2_process_system_rpc_internal,
	    STATIC_FUNCTION(g2_shutdown_g2_process_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_clear_kb = STATIC_SYMBOL("G2-CLEAR-KB",AB_package);
    Qg2_clear_kb_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CLEAR-KB-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_clear_kb,
	    make_system_rpc_1(Qg2_clear_kb_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),Qnil),
	    Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_clear_kb,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_clear_kb_system_rpc_internal,
	    STATIC_FUNCTION(g2_clear_kb_system_rpc_internal,NIL,FALSE,1,1));
    Qg2_set_package_preparation_mode = 
	    STATIC_SYMBOL("G2-SET-PACKAGE-PREPARATION-MODE",AB_package);
    Qg2_set_package_preparation_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-PACKAGE-PREPARATION-MODE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qnew_state = STATIC_SYMBOL("NEW-STATE",AB_package);
    list_constant_65 = STATIC_CONS(Qnew_state,list_constant_17);
    list_constant_66 = STATIC_CONS(list_constant_65,Qnil);
    mutate_global_property(Qg2_set_package_preparation_mode,
	    make_system_rpc_1(Qg2_set_package_preparation_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_66,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_package_preparation_mode,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_package_preparation_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_package_preparation_mode_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_package_preparation_mode = 
	    STATIC_SYMBOL("G2-GET-PACKAGE-PREPARATION-MODE",AB_package);
    Qg2_get_package_preparation_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PACKAGE-PREPARATION-MODE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_package_preparation_mode,
	    make_system_rpc_1(Qg2_get_package_preparation_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_package_preparation_mode,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_package_preparation_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_package_preparation_mode_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_set_simulate_proprietary_mode = 
	    STATIC_SYMBOL("G2-SET-SIMULATE-PROPRIETARY-MODE",AB_package);
    Qg2_set_simulate_proprietary_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-SIMULATE-PROPRIETARY-MODE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_set_simulate_proprietary_mode,
	    make_system_rpc_1(Qg2_set_simulate_proprietary_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_66,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_simulate_proprietary_mode,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_set_simulate_proprietary_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_simulate_proprietary_mode_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_simulate_proprietary_mode = 
	    STATIC_SYMBOL("G2-GET-SIMULATE-PROPRIETARY-MODE",AB_package);
    Qg2_get_simulate_proprietary_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-SIMULATE-PROPRIETARY-MODE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_simulate_proprietary_mode,
	    make_system_rpc_1(Qg2_get_simulate_proprietary_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_simulate_proprietary_mode,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_simulate_proprietary_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_simulate_proprietary_mode_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_strip_all_texts = STATIC_SYMBOL("G2-STRIP-ALL-TEXTS",AB_package);
    Qg2_strip_all_texts_system_rpc_internal = 
	    STATIC_SYMBOL("G2-STRIP-ALL-TEXTS-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_strip_all_texts,
	    make_system_rpc_1(Qg2_strip_all_texts_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_strip_all_texts,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_strip_all_texts_system_rpc_internal,
	    STATIC_FUNCTION(g2_strip_all_texts_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_make_kb_proprietary = STATIC_SYMBOL("G2-MAKE-KB-PROPRIETARY",
	    AB_package);
    Qg2_make_kb_proprietary_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-KB-PROPRIETARY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_make_kb_proprietary,
	    make_system_rpc_1(Qg2_make_kb_proprietary_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_kb_proprietary,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_make_kb_proprietary_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_kb_proprietary_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_flush_all_change_logs = STATIC_SYMBOL("G2-FLUSH-ALL-CHANGE-LOGS",
	    AB_package);
    Qg2_flush_all_change_logs_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FLUSH-ALL-CHANGE-LOGS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_flush_all_change_logs,
	    make_system_rpc_1(Qg2_flush_all_change_logs_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_flush_all_change_logs,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_flush_all_change_logs_system_rpc_internal,
	    STATIC_FUNCTION(g2_flush_all_change_logs_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_enable_all_items = STATIC_SYMBOL("G2-ENABLE-ALL-ITEMS",AB_package);
    Qg2_enable_all_items_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ENABLE-ALL-ITEMS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_enable_all_items,
	    make_system_rpc_1(Qg2_enable_all_items_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_enable_all_items,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_enable_all_items_system_rpc_internal,
	    STATIC_FUNCTION(g2_enable_all_items_system_rpc_internal,NIL,
	    FALSE,1,1));
    Qg2_move_ws_item_by = STATIC_SYMBOL("G2-MOVE-WS-ITEM-BY",AB_package);
    Qg2_move_ws_item_by_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MOVE-WS-ITEM-BY-SYSTEM-RPC-INTERNAL",AB_package);
    Qdeltax = STATIC_SYMBOL("DELTAX",AB_package);
    list_constant_67 = STATIC_CONS(Qdeltax,list_constant_57);
    Qdeltay = STATIC_SYMBOL("DELTAY",AB_package);
    list_constant_68 = STATIC_CONS(Qdeltay,list_constant_57);
    list_constant_69 = STATIC_LIST((SI_Long)2L,list_constant_60,
	    list_constant_61);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)4L,list_constant_6,
	    list_constant_67,list_constant_68,list_constant_69);
    mutate_global_property(Qg2_move_ws_item_by,
	    make_system_rpc_1(Qg2_move_ws_item_by_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_70,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_move_ws_item_by,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_move_ws_item_by_system_rpc_internal,
	    STATIC_FUNCTION(g2_move_ws_item_by_system_rpc_internal,NIL,
	    FALSE,6,6));
    Qg2_move_items_along_paths = STATIC_SYMBOL("G2-MOVE-ITEMS-ALONG-PATHS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_move_items_along_paths,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qis_moved_by_g2 = STATIC_SYMBOL("IS-MOVED-BY-G2",AB_package);
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_move_items_along_paths,
	    STATIC_FUNCTION(g2_move_items_along_paths,NIL,FALSE,5,5));
    Qg2_create_item = STATIC_SYMBOL("G2-CREATE-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_create_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_create_item,STATIC_FUNCTION(g2_create_item,NIL,
	    FALSE,1,1));
    Qg2_create_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CREATE-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_71 = STATIC_CONS(list_constant_4,Qnil);
    mutate_global_property(Qg2_create_item,
	    make_system_rpc_1(Qg2_create_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_71),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_create_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_create_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_create_item_system_rpc_internal,NIL,FALSE,2,2));
    Qg2_clone_item = STATIC_SYMBOL("G2-CLONE-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_clone_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clone_item,STATIC_FUNCTION(g2_clone_item,NIL,
	    FALSE,1,1));
    Qg2_clone_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CLONE-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_72 = STATIC_CONS(list_constant_6,Qnil);
    mutate_global_property(Qg2_clone_item,
	    make_system_rpc_1(Qg2_clone_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_71),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_clone_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_clone_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_clone_item_system_rpc_internal,NIL,FALSE,2,2));
    Qg2_transfer_item = STATIC_SYMBOL("G2-TRANSFER-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_transfer_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_transfer_item,STATIC_FUNCTION(g2_transfer_item,
	    NIL,FALSE,6,6));
    Qg2_transfer_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-TRANSFER-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    Qtarget_item = STATIC_SYMBOL("TARGET-ITEM",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_74 = STATIC_LIST((SI_Long)3L,Qtarget_item,Ktype,
	    Qitem_or_datum);
    Qattribute_name_or_false = STATIC_SYMBOL("ATTRIBUTE-NAME-OR-FALSE",
	    AB_package);
    list_constant_73 = STATIC_CONS(Ktype,list_constant_5);
    list_constant_75 = STATIC_CONS(Qattribute_name_or_false,list_constant_73);
    Qclass_qualifier_or_false = STATIC_SYMBOL("CLASS-QUALIFIER-OR-FALSE",
	    AB_package);
    list_constant_76 = STATIC_CONS(Qclass_qualifier_or_false,list_constant_73);
    list_constant_77 = STATIC_LIST((SI_Long)6L,list_constant_6,
	    list_constant_74,list_constant_58,list_constant_59,
	    list_constant_75,list_constant_76);
    mutate_global_property(Qg2_transfer_item,
	    make_system_rpc_1(Qg2_transfer_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_77,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_transfer_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_transfer_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_transfer_item_system_rpc_internal,NIL,FALSE,
	    7,7));
    Qg2_delete_item = STATIC_SYMBOL("G2-DELETE-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_delete_item,STATIC_FUNCTION(g2_delete_item,NIL,
	    FALSE,3,3));
    Qg2_delete_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DELETE-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    Qwithout_permanence_checks_p = 
	    STATIC_SYMBOL("WITHOUT-PERMANENCE-CHECKS-P",AB_package);
    list_constant_78 = STATIC_CONS(Qwithout_permanence_checks_p,
	    list_constant_17);
    Qwithout_leaving_stubs_p = STATIC_SYMBOL("WITHOUT-LEAVING-STUBS-P",
	    AB_package);
    list_constant_79 = STATIC_CONS(Qwithout_leaving_stubs_p,list_constant_17);
    list_constant_80 = STATIC_LIST((SI_Long)3L,list_constant_6,
	    list_constant_78,list_constant_79);
    mutate_global_property(Qg2_delete_item,
	    make_system_rpc_1(Qg2_delete_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_80,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_delete_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_delete_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_delete_item_system_rpc_internal,NIL,FALSE,4,4));
    Qpermanent = STATIC_SYMBOL("PERMANENT",AB_package);
    temp = CONS(Qpermanent,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qpermanent,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_permanent = STATIC_SYMBOL("INITIAL-PERMANENT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_permanent,
	    STATIC_FUNCTION(initial_permanent,NIL,FALSE,1,1));
    Qget_permanent = STATIC_SYMBOL("GET-PERMANENT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_permanent,STATIC_FUNCTION(get_permanent,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qpermanent,list_constant_4,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qinitial_permanent),
	    SYMBOL_FUNCTION(Qget_permanent),Nil);
    Qmanually_disabled_qm = STATIC_SYMBOL("MANUALLY-DISABLED\?",AB_package);
    temp = CONS(Qmanually_disabled_qm,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qmanually_disabled_qm,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    string_constant_4 = STATIC_STRING("~NF may not be enabled or disabled");
    string_constant_5 = 
	    STATIC_STRING("~NF can not be disabled because it is currently running");
    Qinitial_manually_disabled_qm = 
	    STATIC_SYMBOL("INITIAL-MANUALLY-DISABLED\?",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_manually_disabled_qm,
	    STATIC_FUNCTION(initial_manually_disabled_qm,NIL,FALSE,1,1));
    Qget_manually_disabled_qm = STATIC_SYMBOL("GET-MANUALLY-DISABLED\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_manually_disabled_qm,
	    STATIC_FUNCTION(get_manually_disabled_qm,NIL,FALSE,1,1));
    Qset_manually_disabled_qm = STATIC_SYMBOL("SET-MANUALLY-DISABLED\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_manually_disabled_qm,
	    STATIC_FUNCTION(set_manually_disabled_qm,NIL,FALSE,2,2));
    add_virtual_attribute(Qmanually_disabled_qm,list_constant_4,
	    Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qinitial_manually_disabled_qm),
	    SYMBOL_FUNCTION(Qget_manually_disabled_qm),
	    SYMBOL_FUNCTION(Qset_manually_disabled_qm));
    Qg2_make_permanent = STATIC_SYMBOL("G2-MAKE-PERMANENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_permanent,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_make_permanent,
	    STATIC_FUNCTION(g2_make_permanent,NIL,FALSE,1,1));
    Qg2_make_permanent_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-PERMANENT-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_make_permanent,
	    make_system_rpc_1(Qg2_make_permanent_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_permanent,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_make_permanent_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_permanent_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qtransient = STATIC_SYMBOL("TRANSIENT",AB_package);
    temp = CONS(Qtransient,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qtransient,temp_1);
    set_property_value_function(get_symbol_properties_function(Qitem),
	    Qvirtual_attributes_local_to_class,temp);
    Qinitial_transient = STATIC_SYMBOL("INITIAL-TRANSIENT",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_transient,
	    STATIC_FUNCTION(initial_transient,NIL,FALSE,1,1));
    Qget_transient = STATIC_SYMBOL("GET-TRANSIENT",AB_package);
    SET_SYMBOL_FUNCTION(Qget_transient,STATIC_FUNCTION(get_transient,NIL,
	    FALSE,1,1));
    add_virtual_attribute(Qtransient,list_constant_4,Qtruth_value,Qnil,
	    SYMBOL_FUNCTION(Qinitial_transient),
	    SYMBOL_FUNCTION(Qget_transient),Nil);
    Qg2_make_transient = STATIC_SYMBOL("G2-MAKE-TRANSIENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_transient,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_make_transient,
	    STATIC_FUNCTION(g2_make_transient,NIL,FALSE,1,1));
    Qg2_make_transient_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-TRANSIENT-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_make_transient,
	    make_system_rpc_1(Qg2_make_transient_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_transient,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_make_transient_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_transient_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_get_subworkspace = STATIC_SYMBOL("G2-GET-SUBWORKSPACE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_subworkspace,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_subworkspace,
	    STATIC_FUNCTION(g2_get_subworkspace,NIL,FALSE,1,1));
    Qg2_get_subworkspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-SUBWORKSPACE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_25,list_constant_71);
    list_constant_82 = STATIC_CONS(list_constant_81,Qnil);
    mutate_global_property(Qg2_get_subworkspace,
	    make_system_rpc_1(Qg2_get_subworkspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_82),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_subworkspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_subworkspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_subworkspace_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_get_referenced_items = STATIC_SYMBOL("G2-GET-REFERENCED-ITEMS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_referenced_items,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_referenced_items,
	    STATIC_FUNCTION(g2_get_referenced_items,NIL,FALSE,1,1));
    Qg2_get_referenced_items_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-REFERENCED-ITEMS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qab_class,Qmessage);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qmessage,Ktype,
	    list_constant_83);
    list_constant_85 = STATIC_CONS(list_constant_84,Qnil);
    list_constant_86 = STATIC_CONS(list_constant_46,Qnil);
    mutate_global_property(Qg2_get_referenced_items,
	    make_system_rpc_1(Qg2_get_referenced_items_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_85,
	    Nil,T),list_constant_86),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_referenced_items,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_referenced_items_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_referenced_items_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_name_for_item = STATIC_SYMBOL("G2-NAME-FOR-ITEM",AB_package);
    Qg2_name_for_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-NAME-FOR-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qab_class,Qblock);
    list_constant_88 = STATIC_LIST((SI_Long)3L,Qframe,Ktype,list_constant_87);
    list_constant_90 = STATIC_CONS(list_constant_88,Qnil);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_89 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_10);
    list_constant_91 = STATIC_CONS(list_constant_89,Qnil);
    mutate_global_property(Qg2_name_for_item,
	    make_system_rpc_1(Qg2_name_for_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_90,
	    Nil,T),list_constant_91),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_name_for_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_name_for_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_name_for_item_system_rpc_internal,NIL,FALSE,
	    2,2));
    Qg2_get_origin_of_message = STATIC_SYMBOL("G2-GET-ORIGIN-OF-MESSAGE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_origin_of_message,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_origin_of_message,
	    STATIC_FUNCTION(g2_get_origin_of_message,NIL,FALSE,1,1));
    Qg2_get_origin_of_message_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ORIGIN-OF-MESSAGE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_92 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_box);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qtext_box,Ktype,
	    list_constant_92);
    list_constant_94 = STATIC_CONS(list_constant_93,Qnil);
    mutate_global_property(Qg2_get_origin_of_message,
	    make_system_rpc_1(Qg2_get_origin_of_message_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_94,
	    Nil,T),list_constant_82),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_origin_of_message,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_origin_of_message_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_origin_of_message_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_make_subworkspace = STATIC_SYMBOL("G2-MAKE-SUBWORKSPACE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_subworkspace,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_make_subworkspace,
	    STATIC_FUNCTION(g2_make_subworkspace,NIL,FALSE,2,2));
    Qg2_make_subworkspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-SUBWORKSPACE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_95 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_45);
    list_constant_97 = STATIC_CONS(Qkb_workspace,list_constant_95);
    list_constant_96 = STATIC_CONS(Ktype,list_constant_71);
    list_constant_98 = STATIC_CONS(Qtarget_item,list_constant_96);
    list_constant_99 = STATIC_LIST((SI_Long)2L,list_constant_97,
	    list_constant_98);
    mutate_global_property(Qg2_make_subworkspace,
	    make_system_rpc_1(Qg2_make_subworkspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_99,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_subworkspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_make_subworkspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_subworkspace_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qg2_get_containment_hierarchy = 
	    STATIC_SYMBOL("G2-GET-CONTAINMENT-HIERARCHY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_containment_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_containment_hierarchy,
	    STATIC_FUNCTION(g2_get_containment_hierarchy,NIL,FALSE,1,1));
    Qg2_get_containment_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CONTAINMENT-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_containment_hierarchy,
	    make_system_rpc_1(Qg2_get_containment_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_containment_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    string_constant_6 = 
	    STATIC_STRING("Call to ~A not available to interface ~NF");
    SET_SYMBOL_FUNCTION(Qg2_get_containment_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_containment_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_current_user_menu_choices = 
	    STATIC_SYMBOL("G2-GET-CURRENT-USER-MENU-CHOICES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_current_user_menu_choices,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_window);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_100);
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_current_user_menu_choices,
	    STATIC_FUNCTION(g2_get_current_user_menu_choices,NIL,FALSE,2,2));
    Qg2_get_current_user_menu_choices_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CURRENT-USER-MENU-CHOICES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    list_constant_101 = STATIC_CONS(Quser_mode,list_constant_13);
    list_constant_102 = STATIC_LIST((SI_Long)2L,list_constant_6,
	    list_constant_101);
    mutate_global_property(Qg2_get_current_user_menu_choices,
	    make_system_rpc_1(Qg2_get_current_user_menu_choices_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_102,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_current_user_menu_choices,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_current_user_menu_choices_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_current_user_menu_choices_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_current_user_menu_choices_for_session = 
	    STATIC_SYMBOL("G2-GET-CURRENT-USER-MENU-CHOICES-FOR-SESSION",
	    AB_package);
    Qg2_get_current_user_menu_choices_for_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CURRENT-USER-MENU-CHOICES-FOR-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_103 = STATIC_LIST((SI_Long)2L,list_constant_6,
	    list_constant_47);
    mutate_global_property(Qg2_get_current_user_menu_choices_for_session,
	    make_system_rpc_1(Qg2_get_current_user_menu_choices_for_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_103,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_current_user_menu_choices_for_session,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_current_user_menu_choices_for_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_current_user_menu_choices_for_session_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_user_menu_choice = STATIC_SYMBOL("G2-GET-USER-MENU-CHOICE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_user_menu_choice,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_user_menu_choice,
	    STATIC_FUNCTION(g2_get_user_menu_choice,NIL,FALSE,2,2));
    Qg2_get_user_menu_choice_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-USER-MENU-CHOICE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    list_constant_104 = STATIC_CONS(Qlabel,list_constant_13);
    Qapplicable_class_qm = STATIC_SYMBOL("APPLICABLE-CLASS\?",AB_package);
    list_constant_105 = STATIC_CONS(Qapplicable_class_qm,list_constant_13);
    list_constant_106 = STATIC_LIST((SI_Long)2L,list_constant_104,
	    list_constant_105);
    mutate_global_property(Qg2_get_user_menu_choice,
	    make_system_rpc_1(Qg2_get_user_menu_choice_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_106,
	    Nil,T),list_constant_82),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_user_menu_choice,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_user_menu_choice_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_user_menu_choice_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_strict_instances_of_class = 
	    STATIC_SYMBOL("G2-GET-STRICT-INSTANCES-OF-CLASS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_strict_instances_of_class,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_strict_instances_of_class,
	    STATIC_FUNCTION(g2_get_strict_instances_of_class,NIL,FALSE,1,1));
    Qg2_get_strict_instances_of_class_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-STRICT-INSTANCES-OF-CLASS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_strict_instances_of_class,
	    make_system_rpc_1(Qg2_get_strict_instances_of_class_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_strict_instances_of_class,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_strict_instances_of_class_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_strict_instances_of_class_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_direct_subclasses = STATIC_SYMBOL("G2-GET-DIRECT-SUBCLASSES",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_direct_subclasses,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_direct_subclasses,
	    STATIC_FUNCTION(g2_get_direct_subclasses,NIL,FALSE,1,1));
    Qg2_get_direct_subclasses_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-DIRECT-SUBCLASSES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_direct_subclasses,
	    make_system_rpc_1(Qg2_get_direct_subclasses_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_direct_subclasses,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_direct_subclasses_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_direct_subclasses_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_enable_item = STATIC_SYMBOL("G2-ENABLE-ITEM",AB_package);
    Qg2_enable_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ENABLE-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_enable_item,
	    make_system_rpc_1(Qg2_enable_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_enable_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_enable_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_enable_item_system_rpc_internal,NIL,FALSE,2,2));
    Qg2_disable_item = STATIC_SYMBOL("G2-DISABLE-ITEM",AB_package);
    Qg2_disable_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DISABLE-ITEM-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_disable_item,
	    make_system_rpc_1(Qg2_disable_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_disable_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_disable_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_disable_item_system_rpc_internal,NIL,FALSE,
	    2,2));
    Qg2_item_is_disabled = STATIC_SYMBOL("G2-ITEM-IS-DISABLED",AB_package);
    Qg2_item_is_disabled_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ITEM-IS-DISABLED-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_item_is_disabled,
	    make_system_rpc_1(Qg2_item_is_disabled_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_item_is_disabled,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_item_is_disabled_system_rpc_internal,
	    STATIC_FUNCTION(g2_item_is_disabled_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_change_mode_for_window = STATIC_SYMBOL("G2-CHANGE-MODE-FOR-WINDOW",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_change_mode_for_window,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_change_mode_for_window,
	    STATIC_FUNCTION(g2_change_mode_for_window,NIL,FALSE,2,2));
    Qg2_change_mode_for_window_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CHANGE-MODE-FOR-WINDOW-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclient_item = STATIC_SYMBOL("CLIENT-ITEM",AB_package);
    Qui_client_item = STATIC_SYMBOL("UI-CLIENT-ITEM",AB_package);
    list_constant_107 = STATIC_LIST((SI_Long)2L,Qab_class,Qui_client_item);
    list_constant_108 = STATIC_LIST((SI_Long)3L,Qclient_item,Ktype,
	    list_constant_107);
    Qnew_mode = STATIC_SYMBOL("NEW-MODE",AB_package);
    list_constant_109 = STATIC_CONS(Qnew_mode,list_constant_13);
    list_constant_110 = STATIC_LIST((SI_Long)2L,list_constant_108,
	    list_constant_109);
    mutate_global_property(Qg2_change_mode_for_window,
	    make_system_rpc_1(Qg2_change_mode_for_window_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_110,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_change_mode_for_window,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_change_mode_for_window_system_rpc_internal,
	    STATIC_FUNCTION(g2_change_mode_for_window_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_list_memberships = STATIC_SYMBOL("G2-GET-LIST-MEMBERSHIPS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_list_memberships,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_list_memberships,
	    STATIC_FUNCTION(g2_get_list_memberships,NIL,FALSE,1,1));
    Qg2_get_list_memberships_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-LIST-MEMBERSHIPS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_list_memberships,
	    make_system_rpc_1(Qg2_get_list_memberships_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_list_memberships,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_list_memberships_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_list_memberships_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_methods_defined_for_class = 
	    STATIC_SYMBOL("G2-GET-METHODS-DEFINED-FOR-CLASS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_methods_defined_for_class,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_methods_defined_for_class,
	    STATIC_FUNCTION(g2_get_methods_defined_for_class,NIL,FALSE,1,1));
    Qg2_get_methods_defined_for_class_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-METHODS-DEFINED-FOR-CLASS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_methods_defined_for_class,
	    make_system_rpc_1(Qg2_get_methods_defined_for_class_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_methods_defined_for_class,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_methods_defined_for_class_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_methods_defined_for_class_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_methods_of_name = STATIC_SYMBOL("G2-GET-METHODS-OF-NAME",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_methods_of_name,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_methods_of_name,
	    STATIC_FUNCTION(g2_get_methods_of_name,NIL,FALSE,1,1));
    Qg2_get_methods_of_name_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-METHODS-OF-NAME-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qmethod_name = STATIC_SYMBOL("METHOD-NAME",AB_package);
    list_constant_111 = STATIC_CONS(Qmethod_name,list_constant_13);
    list_constant_112 = STATIC_CONS(list_constant_111,Qnil);
    mutate_global_property(Qg2_get_methods_of_name,
	    make_system_rpc_1(Qg2_get_methods_of_name_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_112,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_methods_of_name,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_methods_of_name_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_methods_of_name_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_set_g2_state = STATIC_SYMBOL("G2-SET-G2-STATE",AB_package);
    Qg2_set_g2_state_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-G2-STATE-SYSTEM-RPC-INTERNAL",AB_package);
    Qdesired_state = STATIC_SYMBOL("DESIRED-STATE",AB_package);
    list_constant_113 = STATIC_CONS(Qdesired_state,list_constant_13);
    list_constant_114 = STATIC_CONS(list_constant_113,Qnil);
    mutate_global_property(Qg2_set_g2_state,
	    make_system_rpc_1(Qg2_set_g2_state_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_114,
	    Nil,T),list_constant_10),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_g2_state,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_set_g2_state_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_g2_state_system_rpc_internal,NIL,FALSE,
	    2,2));
    Qg2_get_g2_state = STATIC_SYMBOL("G2-GET-G2-STATE",AB_package);
    Qg2_get_g2_state_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-G2-STATE-SYSTEM-RPC-INTERNAL",AB_package);
    mutate_global_property(Qg2_get_g2_state,
	    make_system_rpc_1(Qg2_get_g2_state_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_10),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_g2_state,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_g2_state_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_g2_state_system_rpc_internal,NIL,FALSE,
	    1,1));
    string_constant_7 = STATIC_STRING("Invalid G2-Window ~NF");
    string_constant_8 = 
	    STATIC_STRING("G2-FIRE-ACTION-BUTTON called with invalid client ~NF");
    string_constant_9 = 
	    STATIC_STRING("G2-FIRE-ACTION-BUTTON called with no client");
    Qg2_fire_action_button = STATIC_SYMBOL("G2-FIRE-ACTION-BUTTON",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_fire_action_button,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_fire_action_button,
	    STATIC_FUNCTION(g2_fire_action_button,NIL,FALSE,2,2));
    Qg2_fire_action_button_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FIRE-ACTION-BUTTON-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    list_constant_115 = STATIC_LIST((SI_Long)2L,Qab_class,Qaction_button);
    list_constant_117 = STATIC_LIST((SI_Long)3L,Qaction_button,Ktype,
	    list_constant_115);
    Qspecific_client = STATIC_SYMBOL("SPECIFIC-CLIENT",AB_package);
    list_constant_116 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_44);
    list_constant_118 = STATIC_CONS(Qspecific_client,list_constant_116);
    list_constant_119 = STATIC_LIST((SI_Long)2L,list_constant_117,
	    list_constant_118);
    mutate_global_property(Qg2_fire_action_button,
	    make_system_rpc_1(Qg2_fire_action_button_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_119,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_fire_action_button,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_fire_action_button_system_rpc_internal,
	    STATIC_FUNCTION(g2_fire_action_button_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qg2_fire_user_menu_choice = STATIC_SYMBOL("G2-FIRE-USER-MENU-CHOICE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_fire_user_menu_choice,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_fire_user_menu_choice,
	    STATIC_FUNCTION(g2_fire_user_menu_choice,NIL,FALSE,3,3));
    Qg2_fire_user_menu_choice_system_rpc_internal = 
	    STATIC_SYMBOL("G2-FIRE-USER-MENU-CHOICE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qab_class,Quser_menu_choice);
    list_constant_121 = STATIC_LIST((SI_Long)3L,Quser_menu_choice,Ktype,
	    list_constant_120);
    list_constant_122 = STATIC_CONS(list_constant_118,Qnil);
    list_constant_123 = STATIC_LIST_STAR((SI_Long)3L,list_constant_121,
	    list_constant_6,list_constant_122);
    mutate_global_property(Qg2_fire_user_menu_choice,
	    make_system_rpc_1(Qg2_fire_user_menu_choice_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_123,
	    Nil,T),list_constant_42),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_fire_user_menu_choice,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_fire_user_menu_choice_system_rpc_internal,
	    STATIC_FUNCTION(g2_fire_user_menu_choice_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_show_workspace = STATIC_SYMBOL("G2-SHOW-WORKSPACE",AB_package);
    Qg2_show_workspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SHOW-WORKSPACE-SYSTEM-RPC-INTERNAL",AB_package);
    Qshow_details_qm = STATIC_SYMBOL("SHOW-DETAILS\?",AB_package);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)3L,Qshow_details_qm,
	    Ktype,list_constant_35);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)3L,list_constant_48,
	    list_constant_124,list_constant_122);
    mutate_global_property(Qg2_show_workspace,
	    make_system_rpc_1(Qg2_show_workspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_125,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_show_workspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qgo_to_item = STATIC_SYMBOL("GO-TO-ITEM",AB_package);
    Qsymbolic_x_scale = STATIC_SYMBOL("SYMBOLIC-X-SCALE",AB_package);
    Qsymbolic_y_scale = STATIC_SYMBOL("SYMBOLIC-Y-SCALE",AB_package);
    Qsymbolic_x_in_workspace = STATIC_SYMBOL("SYMBOLIC-X-IN-WORKSPACE",
	    AB_package);
    Qsymbolic_y_in_workspace = STATIC_SYMBOL("SYMBOLIC-Y-IN-WORKSPACE",
	    AB_package);
    Qsymbolic_x_in_window = STATIC_SYMBOL("SYMBOLIC-X-IN-WINDOW",AB_package);
    Qsymbolic_y_in_window = STATIC_SYMBOL("SYMBOLIC-Y-IN-WINDOW",AB_package);
    Qx_offset_units = STATIC_SYMBOL("X-OFFSET-UNITS",AB_package);
    Qsymbolic_x_offset_direction = 
	    STATIC_SYMBOL("SYMBOLIC-X-OFFSET-DIRECTION",AB_package);
    Qy_offset_units = STATIC_SYMBOL("Y-OFFSET-UNITS",AB_package);
    Qsymbolic_y_offset_direction = 
	    STATIC_SYMBOL("SYMBOLIC-Y-OFFSET-DIRECTION",AB_package);
    Qx_magnification = STATIC_SYMBOL("X-MAGNIFICATION",AB_package);
    Qy_magnification = STATIC_SYMBOL("Y-MAGNIFICATION",AB_package);
    Qx_in_workspace = STATIC_SYMBOL("X-IN-WORKSPACE",AB_package);
    Qy_in_workspace = STATIC_SYMBOL("Y-IN-WORKSPACE",AB_package);
    Qx_in_window = STATIC_SYMBOL("X-IN-WINDOW",AB_package);
    Qy_in_window = STATIC_SYMBOL("Y-IN-WINDOW",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_show_workspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_show_workspace_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_hide_workspace = STATIC_SYMBOL("G2-HIDE-WORKSPACE",AB_package);
    Qg2_hide_workspace_system_rpc_internal = 
	    STATIC_SYMBOL("G2-HIDE-WORKSPACE-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_126 = STATIC_CONS(list_constant_48,list_constant_122);
    mutate_global_property(Qg2_hide_workspace,
	    make_system_rpc_1(Qg2_hide_workspace_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_126,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_hide_workspace,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_hide_workspace_system_rpc_internal,
	    STATIC_FUNCTION(g2_hide_workspace_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    string_constant_10 = 
	    STATIC_STRING("vertex (~NV, ~NV) does not match connection origin");
    string_constant_11 = STATIC_STRING("non-orthogonal vertices specified");
    Qg2_make_connection_for_user = 
	    STATIC_SYMBOL("G2-MAKE-CONNECTION-FOR-USER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_make_connection_for_user,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_12 = 
	    STATIC_STRING("must supply window/ui-client-interface");
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qmoving_loose_end = STATIC_SYMBOL("MOVING-LOOSE-END",AB_package);
    string_constant_13 = STATIC_STRING("~NV must be an item");
    string_constant_14 = STATIC_STRING("~NF is not a loose-end connection");
    Qjoining_loose_ends = STATIC_SYMBOL("JOINING-LOOSE-ENDS",AB_package);
    Qjoined_connections = STATIC_SYMBOL("JOINED-CONNECTIONS",AB_package);
    string_constant_15 = 
	    STATIC_STRING("other item ~NF must be a loose end for ~A");
    string_constant_16 = 
	    STATIC_STRING("Incompatible directions or cross-sections joining ~NF to ~NF");
    Qdragging_loose_end_into_item = 
	    STATIC_SYMBOL("DRAGGING-LOOSE-END-INTO-ITEM",AB_package);
    Qadded_connection_to_block = STATIC_SYMBOL("ADDED-CONNECTION-TO-BLOCK",
	    AB_package);
    string_constant_17 = 
	    STATIC_STRING("~NF is not an item that accepts connections");
    Qmaking_new_junction_block = STATIC_SYMBOL("MAKING-NEW-JUNCTION-BLOCK",
	    AB_package);
    Qmade_junction = STATIC_SYMBOL("MADE-JUNCTION",AB_package);
    string_constant_18 = STATIC_STRING("~NF is not a connection");
    string_constant_19 = STATIC_STRING("unknown mode ~A");
    Qmoved_loose_end = STATIC_SYMBOL("MOVED-LOOSE-END",AB_package);
    Qdeleted_stub = STATIC_SYMBOL("DELETED-STUB",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_make_connection_for_user,
	    STATIC_FUNCTION(g2_make_connection_for_user,NIL,FALSE,5,5));
    Qg2_make_connection_for_user_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MAKE-CONNECTION-FOR-USER-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qloose_end_connection = STATIC_SYMBOL("LOOSE-END-CONNECTION",AB_package);
    list_constant_127 = STATIC_LIST((SI_Long)2L,Qab_class,Qconnection);
    list_constant_129 = STATIC_LIST((SI_Long)3L,Qloose_end_connection,
	    Ktype,list_constant_127);
    Qother_item = STATIC_SYMBOL("OTHER-ITEM",AB_package);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Ktype,Qitem_or_datum);
    list_constant_130 = STATIC_CONS(Qother_item,list_constant_128);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    list_constant_131 = STATIC_CONS(Qmode,list_constant_13);
    Qposition_sequence = STATIC_SYMBOL("POSITION-SEQUENCE",AB_package);
    list_constant_132 = STATIC_CONS(Qposition_sequence,list_constant_31);
    Qspecific_client_or_false = STATIC_SYMBOL("SPECIFIC-CLIENT-OR-FALSE",
	    AB_package);
    list_constant_133 = STATIC_CONS(Qspecific_client_or_false,
	    list_constant_128);
    list_constant_134 = STATIC_LIST((SI_Long)5L,list_constant_129,
	    list_constant_130,list_constant_131,list_constant_132,
	    list_constant_133);
    mutate_global_property(Qg2_make_connection_for_user,
	    make_system_rpc_1(Qg2_make_connection_for_user_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_134,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_make_connection_for_user,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_make_connection_for_user_system_rpc_internal,
	    STATIC_FUNCTION(g2_make_connection_for_user_system_rpc_internal,
	    NIL,FALSE,6,6));
    Qg2_get_connection_input_and_output = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-INPUT-AND-OUTPUT",AB_package);
    Qg2_get_connection_input_and_output_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-INPUT-AND-OUTPUT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_135 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_127);
    list_constant_136 = STATIC_CONS(Qconnection,list_constant_135);
    list_constant_137 = STATIC_CONS(list_constant_136,Qnil);
    mutate_global_property(Qg2_get_connection_input_and_output,
	    make_system_rpc_1(Qg2_get_connection_input_and_output_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_137,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_connection_input_and_output,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_connection_input_and_output_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_connection_input_and_output_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_confirm_available_handles_by_type = 
	    STATIC_SYMBOL("G2-CONFIRM-AVAILABLE-HANDLES-BY-TYPE",AB_package);
    Qg2_confirm_available_handles_by_type_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CONFIRM-AVAILABLE-HANDLES-BY-TYPE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_138 = STATIC_CONS(Qtype,list_constant_13);
    list_constant_139 = STATIC_CONS(list_constant_138,Qnil);
    list_constant_140 = STATIC_CONS(Qinteger,Qnil);
    mutate_global_property(Qg2_confirm_available_handles_by_type,
	    make_system_rpc_1(Qg2_confirm_available_handles_by_type_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_139,
	    Nil,T),list_constant_140),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_confirm_available_handles_by_type,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qpopup = STATIC_SYMBOL("POPUP",AB_package);
    Qradio = STATIC_SYMBOL("RADIO",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_confirm_available_handles_by_type_system_rpc_internal,
	    STATIC_FUNCTION(g2_confirm_available_handles_by_type_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qtc_representation = STATIC_SYMBOL("TC-REPRESENTATION",AB_package);
    Qgeneral_update = STATIC_SYMBOL("GENERAL-UPDATE",AB_package);
    Qactivation_value = STATIC_SYMBOL("ACTIVATION-VALUE",AB_package);
    Qactivation = STATIC_SYMBOL("ACTIVATION",AB_package);
    Qtimespan_info = STATIC_SYMBOL("TIMESPAN-INFO",AB_package);
    Qinitial_plot_data = STATIC_SYMBOL("INITIAL-PLOT-DATA",AB_package);
    Qtime_delta = STATIC_SYMBOL("TIME-DELTA",AB_package);
    Qclock_discontinuity = STATIC_SYMBOL("CLOCK-DISCONTINUITY",AB_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qitem_icon_variables_change = 
	    STATIC_SYMBOL("ITEM-ICON-VARIABLES-CHANGE",AB_package);
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    Qx_offset = STATIC_SYMBOL("X-OFFSET",AB_package);
    Qy_offset = STATIC_SYMBOL("Y-OFFSET",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    Qid = STATIC_SYMBOL("ID",AB_package);
    Qreturn_rpc_name = STATIC_SYMBOL("RETURN-RPC-NAME",AB_package);
    Qitem_move = STATIC_SYMBOL("ITEM-MOVE",AB_package);
    Qtw_workspace_item_position = 
	    STATIC_SYMBOL("TW-WORKSPACE-ITEM-POSITION",AB_package);
    Qitem_resize = STATIC_SYMBOL("ITEM-RESIZE",AB_package);
    Qnew_rotation = STATIC_SYMBOL("NEW-ROTATION",AB_package);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qitem_rotate = STATIC_SYMBOL("ITEM-ROTATE",AB_package);
    Qcolor_pattern_changes = STATIC_SYMBOL("COLOR-PATTERN-CHANGES",AB_package);
    Qitem_color_pattern_change = STATIC_SYMBOL("ITEM-COLOR-PATTERN-CHANGE",
	    AB_package);
    Qitem_remove = STATIC_SYMBOL("ITEM-REMOVE",AB_package);
    Qposition_or_next_lower_item = 
	    STATIC_SYMBOL("POSITION-OR-NEXT-LOWER-ITEM",AB_package);
    Qitem_layer_change = STATIC_SYMBOL("ITEM-LAYER-CHANGE",AB_package);
    Qitem_insert = STATIC_SYMBOL("ITEM-INSERT",AB_package);
    Qnew_value = STATIC_SYMBOL("NEW-VALUE",AB_package);
    Qitem_change = STATIC_SYMBOL("ITEM-CHANGE",AB_package);
    if (Highest_parsing_context_handle == UNBOUND)
	Highest_parsing_context_handle = FIX((SI_Long)0L);
    if (Current_parsing_contexts == UNBOUND)
	Current_parsing_contexts = Nil;
    Qg2_defstruct_structure_name_parsing_context_g2_struct = 
	    STATIC_SYMBOL("PARSING-CONTEXT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Current_parsing_context_qm == UNBOUND)
	Current_parsing_context_qm = Nil;
    if (Testing_parsing_context_locally_p == UNBOUND)
	Testing_parsing_context_locally_p = Nil;
    Qg2_create_parsing_context = STATIC_SYMBOL("G2-CREATE-PARSING-CONTEXT",
	    AB_package);
    Qg2_create_parsing_context_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CREATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qgrammar_category_qm = STATIC_SYMBOL("GRAMMAR-CATEGORY\?",AB_package);
    list_constant_141 = STATIC_CONS(Qgrammar_category_qm,list_constant_73);
    Qclass_name_qm = STATIC_SYMBOL("CLASS-NAME\?",AB_package);
    list_constant_142 = STATIC_CONS(Qclass_name_qm,list_constant_73);
    Qattribute_name_qm = STATIC_SYMBOL("ATTRIBUTE-NAME\?",AB_package);
    list_constant_143 = STATIC_CONS(Qattribute_name_qm,list_constant_73);
    Qslot_component_name_qm = STATIC_SYMBOL("SLOT-COMPONENT-NAME\?",
	    AB_package);
    list_constant_144 = STATIC_CONS(Qslot_component_name_qm,list_constant_73);
    Qslot_component_indicator_qm = 
	    STATIC_SYMBOL("SLOT-COMPONENT-INDICATOR\?",AB_package);
    list_constant_145 = STATIC_CONS(Qslot_component_indicator_qm,
	    list_constant_73);
    list_constant_146 = STATIC_LIST((SI_Long)5L,list_constant_141,
	    list_constant_142,list_constant_143,list_constant_144,
	    list_constant_145);
    mutate_global_property(Qg2_create_parsing_context,
	    make_system_rpc_1(Qg2_create_parsing_context_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_146,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_create_parsing_context,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_create_parsing_context_system_rpc_internal,
	    STATIC_FUNCTION(g2_create_parsing_context_system_rpc_internal,
	    NIL,FALSE,6,6));
    Qparsing_context_handle = STATIC_SYMBOL("PARSING-CONTEXT-HANDLE",
	    AB_package);
    Qendable_p = STATIC_SYMBOL("ENDABLE-P",AB_package);
    Qlongest_common_completion = STATIC_SYMBOL("LONGEST-COMMON-COMPLETION",
	    AB_package);
    Qcompletion_choices = STATIC_SYMBOL("COMPLETION-CHOICES",AB_package);
    Qcategory_choices = STATIC_SYMBOL("CATEGORY-CHOICES",AB_package);
    Qg2_simple_create_parsing_context = 
	    STATIC_SYMBOL("G2-SIMPLE-CREATE-PARSING-CONTEXT",AB_package);
    Qg2_simple_create_parsing_context_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SIMPLE-CREATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_147 = STATIC_CONS(Qattribute_name,list_constant_73);
    list_constant_148 = STATIC_LIST((SI_Long)2L,list_constant_6,
	    list_constant_147);
    mutate_global_property(Qg2_simple_create_parsing_context,
	    make_system_rpc_1(Qg2_simple_create_parsing_context_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_148,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_simple_create_parsing_context,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_simple_create_parsing_context_system_rpc_internal,
	    STATIC_FUNCTION(g2_simple_create_parsing_context_system_rpc_internal,
	    NIL,FALSE,3,3));
    gensymed_symbol = T;
    mutate_global_property(Qg2_simple_create_parsing_context,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_simple_create_parsing_context,
	    STATIC_FUNCTION(g2_simple_create_parsing_context,NIL,FALSE,2,2));
    string_constant_20 = 
	    STATIC_STRING("Cannot create parsing context for item ~NF, attribute ~a");
    Qg2_validate_parsing_text = STATIC_SYMBOL("G2-VALIDATE-PARSING-TEXT",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_validate_parsing_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_21 = 
	    STATIC_STRING("Class name ~a not valid for g2-validate-parsing-text");
    string_constant_22 = 
	    STATIC_STRING("Class name ~a or attribute name ~a not valid for g2-validate-parsing-text");
    SET_SYMBOL_FUNCTION(Qg2_validate_parsing_text,
	    STATIC_FUNCTION(g2_validate_parsing_text,NIL,FALSE,3,3));
    Qg2_parsing_context_get_text = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-GET-TEXT",AB_package);
    Qg2_parsing_context_get_text_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-GET-TEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_149 = STATIC_CONS(Qparsing_context_handle,list_constant_57);
    list_constant_150 = STATIC_CONS(list_constant_149,Qnil);
    list_constant_151 = STATIC_CONS(Qtext,Qnil);
    mutate_global_property(Qg2_parsing_context_get_text,
	    make_system_rpc_1(Qg2_parsing_context_get_text_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_150,
	    Nil,T),list_constant_151),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_parsing_context_get_text,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_get_text_system_rpc_internal,
	    STATIC_FUNCTION(g2_parsing_context_get_text_system_rpc_internal,
	    NIL,FALSE,2,2));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parsing_context_get_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_23 = 
	    STATIC_STRING("There is no parsing-context for handle ~d.");
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_get_text,
	    STATIC_FUNCTION(g2_parsing_context_get_text,NIL,FALSE,1,1));
    Qg2_set_editing_context_item = 
	    STATIC_SYMBOL("G2-SET-EDITING-CONTEXT-ITEM",AB_package);
    Qg2_set_editing_context_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SET-EDITING-CONTEXT-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_152 = STATIC_CONS(list_constant_149,list_constant_72);
    mutate_global_property(Qg2_set_editing_context_item,
	    make_system_rpc_1(Qg2_set_editing_context_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_152,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_set_editing_context_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qg2_clear_parsing_context = STATIC_SYMBOL("G2-CLEAR-PARSING-CONTEXT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_set_editing_context_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_set_editing_context_item_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_clear_parsing_context_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CLEAR-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_clear_parsing_context,
	    make_system_rpc_1(Qg2_clear_parsing_context_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_150,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_clear_parsing_context,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_clear_parsing_context_system_rpc_internal,
	    STATIC_FUNCTION(g2_clear_parsing_context_system_rpc_internal,
	    NIL,FALSE,2,2));
    gensymed_symbol = T;
    mutate_global_property(Qg2_clear_parsing_context,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clear_parsing_context,
	    STATIC_FUNCTION(g2_clear_parsing_context,NIL,FALSE,1,1));
    Qg2_delete_parsing_context = STATIC_SYMBOL("G2-DELETE-PARSING-CONTEXT",
	    AB_package);
    Qg2_delete_parsing_context_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DELETE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_delete_parsing_context,
	    make_system_rpc_1(Qg2_delete_parsing_context_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_150,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_delete_parsing_context,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_delete_parsing_context_system_rpc_internal,
	    STATIC_FUNCTION(g2_delete_parsing_context_system_rpc_internal,
	    NIL,FALSE,2,2));
    gensymed_symbol = T;
    mutate_global_property(Qg2_delete_parsing_context,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_delete_parsing_context,
	    STATIC_FUNCTION(g2_delete_parsing_context,NIL,FALSE,1,1));
    Qg2_commit_parse_result = STATIC_SYMBOL("G2-COMMIT-PARSE-RESULT",
	    AB_package);
    Qg2_commit_parse_result_system_rpc_internal = 
	    STATIC_SYMBOL("G2-COMMIT-PARSE-RESULT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qediting_for_runtime_change_p = 
	    STATIC_SYMBOL("EDITING-FOR-RUNTIME-CHANGE-P",AB_package);
    list_constant_153 = STATIC_CONS(Qediting_for_runtime_change_p,
	    list_constant_17);
    list_constant_154 = STATIC_LIST((SI_Long)3L,list_constant_149,
	    list_constant_6,list_constant_153);
    mutate_global_property(Qg2_commit_parse_result,
	    make_system_rpc_1(Qg2_commit_parse_result_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_154,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_commit_parse_result,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_commit_parse_result_system_rpc_internal,
	    STATIC_FUNCTION(g2_commit_parse_result_system_rpc_internal,NIL,
	    FALSE,4,4));
    Qg2_compile_parse_result = STATIC_SYMBOL("G2-COMPILE-PARSE-RESULT",
	    AB_package);
    Qg2_compile_parse_result_system_rpc_internal = 
	    STATIC_SYMBOL("G2-COMPILE-PARSE-RESULT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_155 = STATIC_CONS(list_constant_153,Qnil);
    list_constant_156 = STATIC_CONS(list_constant_149,list_constant_155);
    mutate_global_property(Qg2_compile_parse_result,
	    make_system_rpc_1(Qg2_compile_parse_result_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_156,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_compile_parse_result,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_compile_parse_result_system_rpc_internal,
	    STATIC_FUNCTION(g2_compile_parse_result_system_rpc_internal,
	    NIL,FALSE,3,3));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_compile_parse_result,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qdescription = STATIC_SYMBOL("DESCRIPTION",AB_package);
    Qerror_index = STATIC_SYMBOL("ERROR-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_compile_parse_result,
	    STATIC_FUNCTION(g2_compile_parse_result,NIL,FALSE,2,2));
    Qframe_is_null_or_reprocessed = 
	    STATIC_SYMBOL("FRAME-IS-NULL-OR-REPROCESSED",AB_package);
    list_constant_157 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    Qparse_is_bad = STATIC_SYMBOL("PARSE-IS-BAD",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qparse_is_incomplete = STATIC_SYMBOL("PARSE-IS-INCOMPLETE",AB_package);
    array_constant_2 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    Qparse_is_ambiguous = STATIC_SYMBOL("PARSE-IS-AMBIGUOUS",AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    Qg2_update_parsing_context = STATIC_SYMBOL("G2-UPDATE-PARSING-CONTEXT",
	    AB_package);
    Qg2_update_parsing_context_system_rpc_internal = 
	    STATIC_SYMBOL("G2-UPDATE-PARSING-CONTEXT-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qbackup_index_qm = STATIC_SYMBOL("BACKUP-INDEX\?",AB_package);
    list_constant_158 = STATIC_CONS(Qbackup_index_qm,list_constant_73);
    Qadvance_index_qm = STATIC_SYMBOL("ADVANCE-INDEX\?",AB_package);
    list_constant_159 = STATIC_CONS(Qadvance_index_qm,list_constant_73);
    Qthe_text = STATIC_SYMBOL("THE-TEXT",AB_package);
    list_constant_160 = STATIC_LIST_STAR((SI_Long)3L,Qthe_text,Ktype,
	    list_constant_151);
    list_constant_161 = STATIC_LIST((SI_Long)4L,list_constant_149,
	    list_constant_158,list_constant_159,list_constant_160);
    mutate_global_property(Qg2_update_parsing_context,
	    make_system_rpc_1(Qg2_update_parsing_context_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_161,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_update_parsing_context,System_defined_rpcs);
    System_defined_rpcs = temp;
    array_constant_4 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_update_parsing_context_system_rpc_internal,
	    STATIC_FUNCTION(g2_update_parsing_context_system_rpc_internal,
	    NIL,FALSE,5,5));
    list_constant_162 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_3 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)0L),
	    FIX((SI_Long)0L),list_constant_162);
    Qtoken_complete_p = STATIC_SYMBOL("TOKEN-COMPLETE-P",AB_package);
    Qtoken_data = STATIC_SYMBOL("TOKEN-DATA",AB_package);
    Qg2_shift_cursor_position = STATIC_SYMBOL("G2-SHIFT-CURSOR-POSITION",
	    AB_package);
    Qg2_shift_cursor_position_system_rpc_internal = 
	    STATIC_SYMBOL("G2-SHIFT-CURSOR-POSITION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qnew_position = STATIC_SYMBOL("NEW-POSITION",AB_package);
    list_constant_163 = STATIC_CONS(Qnew_position,list_constant_57);
    list_constant_164 = STATIC_CONS(list_constant_160,Qnil);
    list_constant_165 = STATIC_LIST_STAR((SI_Long)3L,list_constant_149,
	    list_constant_163,list_constant_164);
    mutate_global_property(Qg2_shift_cursor_position,
	    make_system_rpc_1(Qg2_shift_cursor_position_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_165,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_shift_cursor_position,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_shift_cursor_position_system_rpc_internal,
	    STATIC_FUNCTION(g2_shift_cursor_position_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_adjust_cursor_position = STATIC_SYMBOL("G2-ADJUST-CURSOR-POSITION",
	    AB_package);
    Qg2_adjust_cursor_position_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ADJUST-CURSOR-POSITION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_166 = STATIC_LIST((SI_Long)2L,list_constant_149,
	    list_constant_163);
    mutate_global_property(Qg2_adjust_cursor_position,
	    make_system_rpc_1(Qg2_adjust_cursor_position_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_166,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_adjust_cursor_position,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_adjust_cursor_position_system_rpc_internal,
	    STATIC_FUNCTION(g2_adjust_cursor_position_system_rpc_internal,
	    NIL,FALSE,3,3));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_adjust_cursor_position,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_24 = 
	    STATIC_STRING("Position ~a invalid for g2-adjust-cursor-position");
    SET_SYMBOL_FUNCTION(Qg2_adjust_cursor_position,
	    STATIC_FUNCTION(g2_adjust_cursor_position,NIL,FALSE,2,2));
    Qg2_parsing_context_delete_characters = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-DELETE-CHARACTERS",AB_package);
    Qg2_parsing_context_delete_characters_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-DELETE-CHARACTERS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_167 = STATIC_CONS(Qposition,list_constant_57);
    Qnumber_of_chars = STATIC_SYMBOL("NUMBER-OF-CHARS",AB_package);
    list_constant_168 = STATIC_CONS(Qnumber_of_chars,list_constant_57);
    list_constant_169 = STATIC_LIST((SI_Long)3L,list_constant_149,
	    list_constant_167,list_constant_168);
    mutate_global_property(Qg2_parsing_context_delete_characters,
	    make_system_rpc_1(Qg2_parsing_context_delete_characters_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_169,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_parsing_context_delete_characters,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_delete_characters_system_rpc_internal,
	    STATIC_FUNCTION(g2_parsing_context_delete_characters_system_rpc_internal,
	    NIL,FALSE,4,4));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parsing_context_delete_characters,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_25 = 
	    STATIC_STRING("Error while deleting ~a characters from position ~a:  Bad string index\?");
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_delete_characters,
	    STATIC_FUNCTION(g2_parsing_context_delete_characters,NIL,FALSE,
	    3,3));
    Qg2_parsing_context_insert_characters = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-INSERT-CHARACTERS",AB_package);
    Qg2_parsing_context_insert_characters_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PARSING-CONTEXT-INSERT-CHARACTERS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qaddition = STATIC_SYMBOL("ADDITION",AB_package);
    list_constant_170 = STATIC_CONS(Ktype,list_constant_151);
    list_constant_171 = STATIC_CONS(Qaddition,list_constant_170);
    list_constant_172 = STATIC_LIST((SI_Long)3L,list_constant_149,
	    list_constant_167,list_constant_171);
    mutate_global_property(Qg2_parsing_context_insert_characters,
	    make_system_rpc_1(Qg2_parsing_context_insert_characters_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_172,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_parsing_context_insert_characters,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_insert_characters_system_rpc_internal,
	    STATIC_FUNCTION(g2_parsing_context_insert_characters_system_rpc_internal,
	    NIL,FALSE,4,4));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_parsing_context_insert_characters,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_26 = 
	    STATIC_STRING("Error while inserting characters:  Bad string index ~a or invalid string.");
    SET_SYMBOL_FUNCTION(Qg2_parsing_context_insert_characters,
	    STATIC_FUNCTION(g2_parsing_context_insert_characters,NIL,FALSE,
	    3,3));
    Qg2_menu_of_names_for_category = 
	    STATIC_SYMBOL("G2-MENU-OF-NAMES-FOR-CATEGORY",AB_package);
    Qg2_menu_of_names_for_category_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MENU-OF-NAMES-FOR-CATEGORY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qcategory_symbol = STATIC_SYMBOL("CATEGORY-SYMBOL",AB_package);
    list_constant_173 = STATIC_CONS(Qcategory_symbol,list_constant_13);
    list_constant_174 = STATIC_CONS(list_constant_173,list_constant_150);
    mutate_global_property(Qg2_menu_of_names_for_category,
	    make_system_rpc_1(Qg2_menu_of_names_for_category_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_174,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_menu_of_names_for_category,System_defined_rpcs);
    System_defined_rpcs = temp;
    Qtoken_prompts_for_category = 
	    STATIC_SYMBOL("TOKEN-PROMPTS-FOR-CATEGORY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_menu_of_names_for_category_system_rpc_internal,
	    STATIC_FUNCTION(g2_menu_of_names_for_category_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qname_or_names = STATIC_SYMBOL("NAME-OR-NAMES",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qslot_name = STATIC_SYMBOL("SLOT-NAME",AB_package);
    Qslot_component_name = STATIC_SYMBOL("SLOT-COMPONENT-NAME",AB_package);
    Qslot_component_alias = STATIC_SYMBOL("SLOT-COMPONENT-ALIAS",AB_package);
    Qchart_element_uid = STATIC_SYMBOL("CHART-ELEMENT-UID",AB_package);
    Qslot_change = STATIC_SYMBOL("SLOT-CHANGE",AB_package);
    Qg2_transfer_items = STATIC_SYMBOL("G2-TRANSFER-ITEMS",AB_package);
    Qg2_transfer_items_system_rpc_internal = 
	    STATIC_SYMBOL("G2-TRANSFER-ITEMS-SYSTEM-RPC-INTERNAL",AB_package);
    Qsequence_of_items = STATIC_SYMBOL("SEQUENCE-OF-ITEMS",AB_package);
    list_constant_175 = STATIC_CONS(Qsequence_of_items,list_constant_31);
    Qdelta_x = STATIC_SYMBOL("DELTA-X",AB_package);
    list_constant_176 = STATIC_CONS(Qdelta_x,list_constant_57);
    Qdelta_y = STATIC_SYMBOL("DELTA-Y",AB_package);
    list_constant_177 = STATIC_CONS(Qdelta_y,list_constant_57);
    list_constant_178 = STATIC_LIST((SI_Long)4L,list_constant_175,
	    list_constant_97,list_constant_176,list_constant_177);
    mutate_global_property(Qg2_transfer_items,
	    make_system_rpc_1(Qg2_transfer_items_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_178,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_transfer_items,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_transfer_items_system_rpc_internal,
	    STATIC_FUNCTION(g2_transfer_items_system_rpc_internal,NIL,
	    FALSE,5,5));
    Qg2_move_items_enlarging_workspace_if_necessary = 
	    STATIC_SYMBOL("G2-MOVE-ITEMS-ENLARGING-WORKSPACE-IF-NECESSARY",
	    AB_package);
    Qg2_move_items_enlarging_workspace_if_necessary_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MOVE-ITEMS-ENLARGING-WORKSPACE-IF-NECESSARY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qenlarge_workspace_if_necessary = 
	    STATIC_SYMBOL("ENLARGE-WORKSPACE-IF-NECESSARY",AB_package);
    SET_SYMBOL_FUNCTION(Qenlarge_workspace_if_necessary,
	    STATIC_FUNCTION(enlarge_workspace_if_necessary,NIL,TRUE,5,6));
    list_constant_179 = STATIC_CONS(Qenlarge_workspace_if_necessary,
	    list_constant_17);
    list_constant_180 = STATIC_LIST((SI_Long)4L,list_constant_175,
	    list_constant_176,list_constant_177,list_constant_179);
    mutate_global_property(Qg2_move_items_enlarging_workspace_if_necessary,
	    make_system_rpc_1(Qg2_move_items_enlarging_workspace_if_necessary_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_180,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_move_items_enlarging_workspace_if_necessary,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_move_items_enlarging_workspace_if_necessary_system_rpc_internal,
	    STATIC_FUNCTION(g2_move_items_enlarging_workspace_if_necessary_system_rpc_internal,
	    NIL,FALSE,5,5));
    Qg2_move_items = STATIC_SYMBOL("G2-MOVE-ITEMS",AB_package);
    Qg2_move_items_system_rpc_internal = 
	    STATIC_SYMBOL("G2-MOVE-ITEMS-SYSTEM-RPC-INTERNAL",AB_package);
    list_constant_181 = STATIC_LIST((SI_Long)2L,list_constant_176,
	    list_constant_177);
    list_constant_182 = STATIC_CONS(list_constant_175,list_constant_181);
    mutate_global_property(Qg2_move_items,
	    make_system_rpc_1(Qg2_move_items_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_182,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_move_items,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_move_items_system_rpc_internal,
	    STATIC_FUNCTION(g2_move_items_system_rpc_internal,NIL,FALSE,4,4));
    Qg2_clone_and_transfer_items = 
	    STATIC_SYMBOL("G2-CLONE-AND-TRANSFER-ITEMS",AB_package);
    Qg2_clone_and_transfer_items_system_rpc_internal = 
	    STATIC_SYMBOL("G2-CLONE-AND-TRANSFER-ITEMS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_clone_and_transfer_items,
	    make_system_rpc_1(Qg2_clone_and_transfer_items_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_178,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_clone_and_transfer_items,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_clone_and_transfer_items_system_rpc_internal,
	    STATIC_FUNCTION(g2_clone_and_transfer_items_system_rpc_internal,
	    NIL,FALSE,5,5));
    Qg2_invoke_generic_event_rules = 
	    STATIC_SYMBOL("G2-INVOKE-GENERIC-EVENT-RULES",AB_package);
    Qg2_invoke_generic_event_rules_system_rpc_internal = 
	    STATIC_SYMBOL("G2-INVOKE-GENERIC-EVENT-RULES-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qevent_name = STATIC_SYMBOL("EVENT-NAME",AB_package);
    list_constant_183 = STATIC_CONS(Qevent_name,list_constant_13);
    Qevent_object = STATIC_SYMBOL("EVENT-OBJECT",AB_package);
    list_constant_184 = STATIC_CONS(Qevent_object,list_constant_96);
    list_constant_185 = STATIC_LIST((SI_Long)3L,list_constant_183,
	    list_constant_6,list_constant_184);
    mutate_global_property(Qg2_invoke_generic_event_rules,
	    make_system_rpc_1(Qg2_invoke_generic_event_rules_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_185,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_invoke_generic_event_rules,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_invoke_generic_event_rules_system_rpc_internal,
	    STATIC_FUNCTION(g2_invoke_generic_event_rules_system_rpc_internal,
	    NIL,FALSE,4,4));
    Qg2_get_description_of_item = 
	    STATIC_SYMBOL("G2-GET-DESCRIPTION-OF-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_description_of_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_27 = STATIC_STRING("Description of ~(~NF.~)");
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_description_of_item,
	    STATIC_FUNCTION(g2_get_description_of_item,NIL,FALSE,1,1));
    Qg2_get_description_of_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-DESCRIPTION-OF-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_description_of_item,
	    make_system_rpc_1(Qg2_get_description_of_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_72,
	    Nil,T),list_constant_22),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_description_of_item,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_description_of_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_description_of_item_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qitem_or_name = STATIC_SYMBOL("ITEM-OR-NAME",AB_package);
    Qchildren = STATIC_SYMBOL("CHILDREN",AB_package);
    Qg2_get_method_inheritance_path = 
	    STATIC_SYMBOL("G2-GET-METHOD-INHERITANCE-PATH",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_method_inheritance_path,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_28 = 
	    STATIC_STRING("show on a workspace the method inheritance path for ~s and the method ~s");
    string_constant_29 = 
	    STATIC_STRING("show on a workspace the method inheritance path for ~s");
    SET_SYMBOL_FUNCTION(Qg2_get_method_inheritance_path,
	    STATIC_FUNCTION(g2_get_method_inheritance_path,NIL,FALSE,2,2));
    Qg2_get_method_inheritance_path_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-METHOD-INHERITANCE-PATH-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qmethod_name_qm = STATIC_SYMBOL("METHOD-NAME\?",AB_package);
    list_constant_186 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_25,list_constant_10);
    list_constant_187 = STATIC_LIST((SI_Long)3L,Qmethod_name_qm,Ktype,
	    list_constant_186);
    list_constant_189 = STATIC_LIST((SI_Long)2L,list_constant_14,
	    list_constant_187);
    list_constant_188 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_25,list_constant_35);
    list_constant_190 = STATIC_CONS(list_constant_188,Qnil);
    mutate_global_property(Qg2_get_method_inheritance_path,
	    make_system_rpc_1(Qg2_get_method_inheritance_path_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_189,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_method_inheritance_path,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_method_inheritance_path_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_method_inheritance_path_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_method_hierarchy = STATIC_SYMBOL("G2-GET-METHOD-HIERARCHY",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_method_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_30 = 
	    STATIC_STRING("show on a workspace the method hierarchy of ~s");
    SET_SYMBOL_FUNCTION(Qg2_get_method_hierarchy,
	    STATIC_FUNCTION(g2_get_method_hierarchy,NIL,FALSE,1,1));
    Qg2_get_method_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-METHOD-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_method_hierarchy,
	    make_system_rpc_1(Qg2_get_method_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_112,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_method_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_method_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_method_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_procedure_invocation_hierarchy = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-INVOCATION-HIERARCHY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_procedure_invocation_hierarchy,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_31 = 
	    STATIC_STRING("show on a workspace the procedure invocation hierarchy");
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_invocation_hierarchy,
	    STATIC_FUNCTION(g2_get_procedure_invocation_hierarchy,NIL,
	    FALSE,0,0));
    Qg2_get_procedure_invocation_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-INVOCATION-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_procedure_invocation_hierarchy,
	    make_system_rpc_1(Qg2_get_procedure_invocation_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,Qnil,Nil,T),
	    list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_procedure_invocation_hierarchy,
	    System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_invocation_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_procedure_invocation_hierarchy_system_rpc_internal,
	    NIL,FALSE,1,1));
    Qg2_get_procedure_calling_hierarchy = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-CALLING-HIERARCHY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_procedure_calling_hierarchy,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_32 = 
	    STATIC_STRING("show on a workspace the procedure calling hierarchy of ~s");
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_calling_hierarchy,
	    STATIC_FUNCTION(g2_get_procedure_calling_hierarchy,NIL,FALSE,1,1));
    Qg2_get_procedure_calling_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-CALLING-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qprocedure_name_qm = STATIC_SYMBOL("PROCEDURE-NAME\?",AB_package);
    list_constant_191 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_186);
    list_constant_192 = STATIC_CONS(Qprocedure_name_qm,list_constant_191);
    list_constant_193 = STATIC_CONS(list_constant_192,Qnil);
    mutate_global_property(Qg2_get_procedure_calling_hierarchy,
	    make_system_rpc_1(Qg2_get_procedure_calling_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_193,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_procedure_calling_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_calling_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_procedure_calling_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_procedure_caller_hierarchy = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-CALLER-HIERARCHY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_procedure_caller_hierarchy,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_33 = 
	    STATIC_STRING("show on a workspace the procedure caller hierarchy of ~s");
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_caller_hierarchy,
	    STATIC_FUNCTION(g2_get_procedure_caller_hierarchy,NIL,FALSE,1,1));
    Qg2_get_procedure_caller_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-PROCEDURE-CALLER-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_procedure_caller_hierarchy,
	    make_system_rpc_1(Qg2_get_procedure_caller_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_193,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_procedure_caller_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_procedure_caller_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_procedure_caller_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_class_hierarchy = STATIC_SYMBOL("G2-GET-CLASS-HIERARCHY",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_class_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_34 = 
	    STATIC_STRING("show on a workspace the class hierarchy of ~s");
    string_constant_35 = 
	    STATIC_STRING("show on a workspace the class hierarchy");
    SET_SYMBOL_FUNCTION(Qg2_get_class_hierarchy,
	    STATIC_FUNCTION(g2_get_class_hierarchy,NIL,FALSE,1,1));
    Qg2_get_class_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-CLASS-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_194 = STATIC_CONS(Qclass_name_qm,list_constant_191);
    list_constant_195 = STATIC_CONS(list_constant_194,Qnil);
    mutate_global_property(Qg2_get_class_hierarchy,
	    make_system_rpc_1(Qg2_get_class_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_195,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_class_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_class_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_class_hierarchy_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_get_workspace_hierarchy = 
	    STATIC_SYMBOL("G2-GET-WORKSPACE-HIERARCHY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_workspace_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_36 = 
	    STATIC_STRING("show on a workspace the workspace hierarchy of ~s");
    string_constant_37 = 
	    STATIC_STRING("show on a workspace the workspace hierarchy");
    SET_SYMBOL_FUNCTION(Qg2_get_workspace_hierarchy,
	    STATIC_FUNCTION(g2_get_workspace_hierarchy,NIL,FALSE,1,1));
    Qg2_get_workspace_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-WORKSPACE-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qworkspace_name_qm = STATIC_SYMBOL("WORKSPACE-NAME\?",AB_package);
    list_constant_196 = STATIC_CONS(Qworkspace_name_qm,list_constant_191);
    list_constant_197 = STATIC_CONS(list_constant_196,Qnil);
    mutate_global_property(Qg2_get_workspace_hierarchy,
	    make_system_rpc_1(Qg2_get_workspace_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_197,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_workspace_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_workspace_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_workspace_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_get_module_hierarchy = STATIC_SYMBOL("G2-GET-MODULE-HIERARCHY",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_module_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_module_hierarchy,
	    STATIC_FUNCTION(g2_get_module_hierarchy,NIL,FALSE,1,1));
    Qg2_get_module_hierarchy_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-MODULE-HIERARCHY-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qmodule_name_qm = STATIC_SYMBOL("MODULE-NAME\?",AB_package);
    list_constant_198 = STATIC_CONS(Qmodule_name_qm,list_constant_191);
    list_constant_199 = STATIC_CONS(list_constant_198,Qnil);
    mutate_global_property(Qg2_get_module_hierarchy,
	    make_system_rpc_1(Qg2_get_module_hierarchy_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_199,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_module_hierarchy,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_module_hierarchy_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_module_hierarchy_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qhash_symbol_or_frame = STATIC_SYMBOL("HASH-SYMBOL-OR-FRAME",AB_package);
    Qsxhashw = STATIC_SYMBOL("SXHASHW",AB_package);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qget_directly_required_module_information_system_tables = 
	    STATIC_SYMBOL("GET-DIRECTLY-REQUIRED-MODULE-INFORMATION-SYSTEM-TABLES",
	    AB_package);
    Qmake_attributes_table_for_module_information_in_hierarchy = 
	    STATIC_SYMBOL("MAKE-ATTRIBUTES-TABLE-FOR-MODULE-INFORMATION-IN-HIERARCHY",
	    AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    string_constant_38 = STATIC_STRING("");
    string_constant_39 = STATIC_STRING("No module hierarchy ~a~a");
    string_constant_40 = STATIC_STRING("can be shown for ");
    string_constant_41 = 
	    STATIC_STRING("exists, because the top-level module is unnamed.");
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    array_constant_7 = STATIC_ARRAY(list_constant_157,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    Qg2_get_inspect_graph = STATIC_SYMBOL("G2-GET-INSPECT-GRAPH",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_inspect_graph,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_inspect_graph,
	    STATIC_FUNCTION(g2_get_inspect_graph,NIL,FALSE,1,1));
    Qg2_get_inspect_graph_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-INSPECT-GRAPH-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qinspect_command_string = STATIC_SYMBOL("INSPECT-COMMAND-STRING",
	    AB_package);
    list_constant_200 = STATIC_CONS(Qinspect_command_string,list_constant_170);
    list_constant_201 = STATIC_CONS(list_constant_200,Qnil);
    mutate_global_property(Qg2_get_inspect_graph,
	    make_system_rpc_1(Qg2_get_inspect_graph_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_201,
	    Nil,T),list_constant_190),Qsystem_defined_rpc);
    temp = adjoin(2,Qg2_get_inspect_graph,System_defined_rpcs);
    System_defined_rpcs = temp;
    SET_SYMBOL_FUNCTION(Qg2_get_inspect_graph_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_inspect_graph_system_rpc_internal,NIL,
	    FALSE,2,2));
}
