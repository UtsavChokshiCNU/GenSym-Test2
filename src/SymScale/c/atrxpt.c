/* atrxpt.c
 * Input file:  attr-export.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "atrxpt.h"


DEFINE_VARIABLE_WITH_SYMBOL(Current_attribute_description_class, Qcurrent_attribute_description_class);

static Object Qg2_defstruct_structure_name_virtual_attribute_g2_struct;  /* g2-defstruct-structure-name::virtual-attribute-g2-struct */

static Object Qg2_defstruct_structure_name_slot_description_g2_struct;  /* g2-defstruct-structure-name::slot-description-g2-struct */

/* DEFINING-CLASS-OF-SLOT */
Object defining_class_of_slot(slot_description_or_virtual_attribute)
    Object slot_description_or_virtual_attribute;
{
    Object class_specification_for_virtual_attribute, temp;

    x_note_fn_call(182,0);
    class_specification_for_virtual_attribute = 
	    SIMPLE_VECTOR_P(slot_description_or_virtual_attribute) && 
	    EQ(ISVREF(slot_description_or_virtual_attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct) ? 
	    ISVREF(slot_description_or_virtual_attribute,(SI_Long)2L) : Qnil;
    if (SIMPLE_VECTOR_P(slot_description_or_virtual_attribute) && 
	    EQ(ISVREF(slot_description_or_virtual_attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_slot_description_g2_struct))
	temp = ISVREF(slot_description_or_virtual_attribute,(SI_Long)3L);
    else if (class_type_specification_p(class_specification_for_virtual_attribute))
	temp = M_CAR(M_CDR(class_specification_for_virtual_attribute));
    else
	temp = 
		virtual_attribute_defined_for_class_qm(slot_description_or_virtual_attribute,
		Current_attribute_description_class);
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

static Object Qitem;               /* item */

/* DEFINING-CLASS-OF-SLOT-FOR-USER */
Object defining_class_of_slot_for_user(slot_description_or_virtual_attribute)
    Object slot_description_or_virtual_attribute;
{
    Object actual_class;

    x_note_fn_call(182,1);
    actual_class = 
	    defining_class_of_slot(slot_description_or_virtual_attribute);
    return VALUES_1(memq_function(actual_class,list_constant) ? Qitem : 
	    actual_class);
}

static Object Qsuperior_class_p;   /* superior-class-p */

static Object Qdefining_class_of_attr_pair;  /* defining-class-of-attr-pair */

/* SORT-PAIRS-ACCORDING-TO-DEFINING-CLASS */
Object sort_pairs_according_to_defining_class(class_name,slot_desc_alist)
    Object class_name, slot_desc_alist;
{
    Object current_attribute_description_class, temp;
    Declare_special(1);

    x_note_fn_call(182,2);
    current_attribute_description_class = class_name;
    PUSH_SPECIAL_WITH_SYMBOL(Current_attribute_description_class,Qcurrent_attribute_description_class,current_attribute_description_class,
	    0);
      temp = sort_list(slot_desc_alist,Qsuperior_class_p,
	      Qdefining_class_of_attr_pair);
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* SUPERIOR-CLASS-P */
Object superior_class_p(symbol,class_1)
    Object symbol, class_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(182,3);
    gensymed_symbol = lookup_global_or_kb_specific_property_value(symbol,
	    Class_description_gkbprop);
    temp =  !(gensymed_symbol ? TRUEP(memq_function(class_1,
	    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? T : Nil;
    return VALUES_1(temp);
}

/* DEFINING-CLASS-OF-ATTR-PAIR */
Object defining_class_of_attr_pair(slot_desc_dotted_pair)
    Object slot_desc_dotted_pair;
{
    Object temp;

    x_note_fn_call(182,4);
    temp = defining_class_of_slot(M_CDR(slot_desc_dotted_pair));
    return VALUES_1(temp);
}

static Object Qab_or;              /* or */

static Object Qab_class;           /* class */

/* APPLICABLE-AND-NOT-DEPRECATED-VIRTUAL-ATTRIBUTE-P */
Object applicable_and_not_deprecated_virtual_attribute_p(class_description,
	    attribute_structure,include_deprecated_p)
    Object class_description, attribute_structure, include_deprecated_p;
{
    Object inheritance_path, arg_spec, features, class_or_superclass;
    Object ab_loop_list_, temp, valid_class, ab_loop_list__1, ab_loop_it_;
    char temp_1;

    x_note_fn_call(182,5);
    inheritance_path = ISVREF(class_description,(SI_Long)2L);
    arg_spec = ISVREF(attribute_structure,(SI_Long)2L);
    features = ISVREF(attribute_structure,(SI_Long)4L);
    if (CONSP(arg_spec)) {
	class_or_superclass = Nil;
	ab_loop_list_ = inheritance_path;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_or_superclass = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(include_deprecated_p) && 
		class_is_specifically_deprecated_in_features_p(class_or_superclass,
		features)) {
	    temp = Nil;
	    goto end_1;
	}
	if (EQ(Qab_or,M_CAR(arg_spec))) {
	    valid_class = Nil;
	    ab_loop_list__1 = CDR(arg_spec);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    valid_class = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = CONSP(valid_class) && EQ(Qab_class,
		    M_CAR(valid_class)) ? (EQ(class_or_superclass,
		    CADR(valid_class)) ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	}
	else
	    temp_1 = EQ(M_CAR(arg_spec),Qab_class) ? EQ(CADR(arg_spec),
		    class_or_superclass) : TRUEP(Qnil);
	if (temp_1) {
	    temp = T;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Nil;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object Qpreviously_put_in_attribute_tables;  /* previously-put-in-attribute-tables */

/* GET-LIST-OF-ALL-USER-VISIBLE-ATTRIBUTES-SPECIFYING-DEPRECATION */
Object get_list_of_all_user_visible_attributes_specifying_deprecation(class_description,
	    include_deprecated_virtual_attributes_p)
    Object class_description, include_deprecated_virtual_attributes_p;
{
    Object class_name, virtual_attributes, attr_name, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp, virtual_attr_list;
    Object slot_description, defining_class_name, aliased_slot_name;
    Object pretty_slot_name, class_or_frame_qm, gensymed_symbol;
    Object ab_loop_list__1, slot_desc_list, list_1, name;
    Object virtual_attr_list_non_local;
    char temp_1;

    x_note_fn_call(182,6);
    class_name = ISVREF(class_description,(SI_Long)1L);
    virtual_attributes = all_virtual_attributes_for_class(2,
	    class_description,include_deprecated_virtual_attributes_p);
    attr_name = Nil;
    ab_loop_list_ = virtual_attributes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attr_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = attr_name;
    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
	    get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,
	    Nil)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
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
    if (user_visible_slot_p(slot_description) &&  
	    !TRUEP(assq_function(aliased_slot_name,virtual_attr_list))) {
	temp_1 = TRUEP(include_deprecated_virtual_attributes_p);
	if (temp_1);
	else {
	    gensymed_symbol = Nil;
	    ab_loop_list__1 = ISVREF(slot_description,(SI_Long)9L);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    gensymed_symbol = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		    Qpreviously_put_in_attribute_tables)) {
		temp_1 = TRUEP(gensymed_symbol);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    temp_1 =  !temp_1;
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
    goto end_3;
    slot_desc_list = Qnil;
  end_3:;
    if (Virtual_attributes_not_local_to_a_class) {
	list_1 = all_non_local_virtual_attributes_for_class(2,
		class_description,include_deprecated_virtual_attributes_p);
	name = Nil;
	ab_loop_list_ = list_1;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = name;
	ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
		get_property_value_function(3,
		get_symbol_properties_function(name),Qvirtual_attribute,
		Nil)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_3;
      end_loop_3:
	reclaim_eval_list_1(list_1);
	virtual_attr_list_non_local = ab_loopvar_;
	goto end_4;
	virtual_attr_list_non_local = Qnil;
      end_4:;
    }
    else
	virtual_attr_list_non_local = Nil;
    temp = sort_pairs_according_to_defining_class(class_name,
	    nconc2(slot_desc_list,nconc2(virtual_attr_list,
	    virtual_attr_list_non_local)));
    return VALUES_1(temp);
}

/* GET-LIST-OF-ALL-USER-VISIBLE-ATTRIBUTES-FOR-PANE */
Object get_list_of_all_user_visible_attributes_for_pane(class_description,
	    include_deprecated_virtual_attributes_p)
    Object class_description, include_deprecated_virtual_attributes_p;
{
    Object virtual_attributes, attr_name, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, virtual_attr_list;
    Object slot_description, defining_class_name, aliased_slot_name;
    Object pretty_slot_name, class_or_frame_qm, gensymed_symbol;
    Object ab_loop_list__1, slot_desc_list;
    char temp_1;

    x_note_fn_call(182,7);
    virtual_attributes = all_virtual_attributes_for_class(2,
	    class_description,include_deprecated_virtual_attributes_p);
    attr_name = Nil;
    ab_loop_list_ = virtual_attributes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attr_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = attr_name;
    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
	    get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,
	    Nil)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
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
    if (user_visible_slot_p(slot_description) &&  
	    !TRUEP(assq_function(aliased_slot_name,virtual_attr_list))) {
	temp_1 = TRUEP(include_deprecated_virtual_attributes_p);
	if (temp_1);
	else {
	    gensymed_symbol = Nil;
	    ab_loop_list__1 = ISVREF(slot_description,(SI_Long)9L);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    gensymed_symbol = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (gensymed_symbol && EQ(M_CAR(gensymed_symbol),
		    Qpreviously_put_in_attribute_tables)) {
		temp_1 = TRUEP(gensymed_symbol);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    temp_1 =  !temp_1;
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
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
    goto end_3;
    slot_desc_list = Qnil;
  end_3:;
    return VALUES_1(slot_desc_list);
}

/* GET-LIST-OF-ALL-VIRTUAL-ATTRIBUTES-FOR-PANE */
Object get_list_of_all_virtual_attributes_for_pane(class_description,
	    include_deprecated_virtual_attributes_p)
    Object class_description, include_deprecated_virtual_attributes_p;
{
    Object virtual_attributes, attr_name, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, virtual_attr_list, list_1, name;
    Object virtual_attr_list_non_local;

    x_note_fn_call(182,8);
    virtual_attributes = all_virtual_attributes_for_class(2,
	    class_description,include_deprecated_virtual_attributes_p);
    attr_name = Nil;
    ab_loop_list_ = virtual_attributes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attr_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = attr_name;
    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
	    get_property_value_function(3,
	    get_symbol_properties_function(attr_name),Qvirtual_attribute,
	    Nil)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(virtual_attributes);
    virtual_attr_list = ab_loopvar_;
    goto end_1;
    virtual_attr_list = Qnil;
  end_1:;
    if (Virtual_attributes_not_local_to_a_class) {
	list_1 = all_non_local_virtual_attributes_for_class(2,
		class_description,include_deprecated_virtual_attributes_p);
	name = Nil;
	ab_loop_list_ = list_1;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = name;
	ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
		get_property_value_function(3,
		get_symbol_properties_function(name),Qvirtual_attribute,
		Nil)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_list_1(list_1);
	virtual_attr_list_non_local = ab_loopvar_;
	goto end_2;
	virtual_attr_list_non_local = Qnil;
      end_2:;
    }
    else
	virtual_attr_list_non_local = Nil;
    temp = nconc2(virtual_attr_list,virtual_attr_list_non_local);
    return VALUES_1(temp);
}

/* GET-LIST-OF-ALL-USER-VISIBLE-ATTRIBUTES */
Object get_list_of_all_user_visible_attributes(class_description)
    Object class_description;
{
    Object temp;

    x_note_fn_call(182,9);
    temp = 
	    get_list_of_all_user_visible_attributes_specifying_deprecation(class_description,
	    Nil);
    return VALUES_1(temp);
}

static Object Qdo_not_put_in_attribute_tables;  /* do-not-put-in-attribute-tables */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

/* USER-VISIBLE-SLOT-P */
Object user_visible_slot_p(slot_description)
    Object slot_description;
{
    Object temp, category_qm, category_evaluator_interface;

    x_note_fn_call(182,10);
    temp = ISVREF(slot_description,(SI_Long)8L);
    if (temp)
	return VALUES_1(temp);
    else if ( !TRUEP(assq_function(Qdo_not_put_in_attribute_tables,
	    ISVREF(slot_description,(SI_Long)9L)))) {
	temp = assq_function(Qtype,ISVREF(slot_description,(SI_Long)9L));
	category_qm = SECOND(temp);
	if (category_qm) {
	    temp = Include_slots_visible_only_to_roles_p;
	    if (temp)
		return VALUES_1(temp);
	    else {
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
			Qcategory_evaluator_interface);
		if (category_evaluator_interface)
		    return VALUES_1(ISVREF(category_evaluator_interface,
			    (SI_Long)2L));
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qvirtual_attributes_local_to_class;  /* virtual-attributes-local-to-class */

static Object Qdeprecated;         /* deprecated */

/* ALL-VIRTUAL-ATTRIBUTES-FOR-CLASS */
Object all_virtual_attributes_for_class varargs_1(int, n)
{
    Object class_description;
    Object include_deprecated_p, class_1, ab_loop_list_, virtual_attributes;
    Object filtered_virtual_attributes, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, attribute, ab_loop_list__1, valid_attribute;
    Object ab_loopvar__3, ab_loopvar__4;
    Declare_varargs_nonrelocating;

    x_note_fn_call(182,11);
    INIT_ARGS_nonrelocating();
    class_description = REQUIRED_ARG_nonrelocating();
    include_deprecated_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_1 = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
    virtual_attributes = Nil;
    filtered_virtual_attributes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    virtual_attributes = get_property_value_function(3,
	    get_symbol_properties_function(class_1),
	    Qvirtual_attributes_local_to_class,Nil);
    attribute = Nil;
    ab_loop_list__1 = virtual_attributes;
    valid_attribute = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    attribute = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    valid_attribute = CONSP(attribute) && EQ(Qdeprecated,CADR(attribute)) ?
	     (include_deprecated_p ? M_CAR(attribute) : Nil) : attribute;
    if (valid_attribute) {
	ab_loopvar__4 = eval_cons_1(valid_attribute,Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
    }
    goto next_loop_1;
  end_loop_1:
    filtered_virtual_attributes = ab_loopvar__2;
    goto end_1;
    filtered_virtual_attributes = Qnil;
  end_1:;
    ab_loopvar__2 = filtered_virtual_attributes;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* ALL-NON-LOCAL-VIRTUAL-ATTRIBUTES-FOR-CLASS */
Object all_non_local_virtual_attributes_for_class varargs_1(int, n)
{
    Object class_description;
    Object include_deprecated_p, non_local_attr, ab_loop_list_;
    Object attribute_structure, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(182,12);
    INIT_ARGS_nonrelocating();
    class_description = REQUIRED_ARG_nonrelocating();
    include_deprecated_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    non_local_attr = Nil;
    ab_loop_list_ = Virtual_attributes_not_local_to_a_class;
    attribute_structure = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    non_local_attr = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_structure = get_property_value_function(3,
	    get_symbol_properties_function(non_local_attr),
	    Qvirtual_attribute,Nil);
    if (applicable_and_not_deprecated_virtual_attribute_p(class_description,
	    attribute_structure,include_deprecated_p)) {
	ab_loopvar__2 = eval_cons_1(non_local_attr,Nil);
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

static Object Qedit_attribute;     /* edit-attribute */

static Object Qnot_user_editable;  /* not-user-editable */

static Object Qattribute_name;     /* attribute-name */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qvirtual;            /* virtual */

static Object Qtext_readable;      /* text-readable */

static Object Qtext_writable;      /* text-writable */

static Object Qvalue_readable;     /* value-readable */

static Object Qvalue_writable;     /* value-writable */

static Object Qis_system_defined;  /* is-system-defined */

static Object Qdefining_class;     /* defining-class */

static Object Qab_structure;       /* structure */

static Object Kfuncall;            /* :funcall */

static Object Qcompound_slot_descriptor;  /* compound-slot-descriptor */

static Object Qtext;               /* text */

static Object Qinitial_value;      /* initial-value */

static Object Qinitial_item_class;  /* initial-item-class */

static Object Qtruth_value;        /* truth-value */

static Object Qeditor_grammar;     /* editor-grammar */

static Object Qsuperseded;         /* superseded */

static Object Qtype_specification_explicit_complex_type;  /* type-specification-explicit-complex-type */

static Object Qtype_specification_simple_expansion;  /* type-specification-simple-expansion */

static Object Qexclude_from_wildcard_denotation;  /* exclude-from-wildcard-denotation */

/* GENERATE-DESCRIPTION-OF-ATTRIBUTE */
Object generate_description_of_attribute(class_name,aliased_slot_name,
	    slot_description_or_virtual_attribute,class_description,frame,
	    user_mode,expose_internal_classes_p)
    Object class_name, aliased_slot_name;
    Object slot_description_or_virtual_attribute, class_description, frame;
    Object user_mode, expose_internal_classes_p;
{
    Object current_attribute_description_class, defining_class_name;
    Object writable_via_restrictions, slot_type, system_defined_p;
    Object slot_init_form, category_symbol_qm, category_evaluator_interface;
    Object category_getter_qm, category_setter_qm, text_readable;
    Object text_writable, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value, returned_structure, initial_value_qm, function;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, value;
    Object car_1, cdr_1, temp_2, managed_value, evaluation_value_qm;
    Object shadowed_slot, exclude_from_wildcard_denotation;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(182,13);
    current_attribute_description_class = class_name;
    PUSH_SPECIAL_WITH_SYMBOL(Current_attribute_description_class,Qcurrent_attribute_description_class,current_attribute_description_class,
	    0);
      defining_class_name = 
	      defining_class_of_slot(slot_description_or_virtual_attribute);
      writable_via_restrictions = frame ? 
	      frame_or_attribute_operation_is_allowed_for_mode_p(Qedit_attribute,
	      frame,aliased_slot_name,defining_class_name,user_mode) : T;
      if (EQ(ISVREF(slot_description_or_virtual_attribute,(SI_Long)0L),
	      Qg2_defstruct_structure_name_slot_description_g2_struct)) {
	  slot_type = assq_function(Qtype,
		  ISVREF(slot_description_or_virtual_attribute,(SI_Long)9L));
	  system_defined_p = system_defined_attribute_p(2,
		  aliased_slot_name,ISVREF(class_description,(SI_Long)1L));
	  slot_init_form = ISVREF(slot_description_or_virtual_attribute,
		  (SI_Long)6L);
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
	  if (category_symbol_qm) {
	      category_evaluator_interface = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol_qm),
		      Qcategory_evaluator_interface);
	      category_setter_qm = category_evaluator_interface ? 
		      ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	  }
	  else
	      category_setter_qm = Nil;
	  text_readable = slot_type ? ( 
		  !TRUEP(do_not_put_slot_in_attribute_tables_p(2,
		  slot_description_or_virtual_attribute,T)) ? T : Nil) : Qnil;
	  text_writable = writable_via_restrictions ? ( 
		  !TRUEP(assq_function(Qnot_user_editable,
		  ISVREF(slot_description_or_virtual_attribute,
		  (SI_Long)9L))) ? T : Nil) : Qnil;
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)16L + 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattribute_name;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qattribute_name;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = aliased_slot_name;
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
	      item_or_value = aliased_slot_name;
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
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qvirtual;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qvirtual;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = Nil ? Evaluation_true_value : 
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
	      item_or_value = Nil ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtext_readable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qtext_readable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = text_readable ? Evaluation_true_value : 
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
	      item_or_value = text_readable ? Evaluation_true_value : 
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
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qtext_writable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)7L)) = Qtext_writable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = text_writable ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = text_writable ? Evaluation_true_value : 
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
	      SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qvalue_readable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)9L)) = Qvalue_readable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = system_defined_p ? (text_readable && 
		      category_getter_qm ? Evaluation_true_value : 
		      Evaluation_false_value) : Evaluation_true_value;
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
	      item_or_value = system_defined_p ? (text_readable && 
		      category_getter_qm ? Evaluation_true_value : 
		      Evaluation_false_value) : Evaluation_true_value;
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
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qvalue_writable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)11L)) = Qvalue_writable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = system_defined_p ? (text_readable && 
		      writable_via_restrictions && category_setter_qm && 
		      system_defined_p && (frame ? 
		      TRUEP(user_writable_slot_of_instance_p(frame,
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)3L))) : 
		      TRUEP(user_writable_slot_of_class_p(ISVREF(class_description,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)3L)))) ? Evaluation_true_value : 
		      Evaluation_false_value) : Evaluation_true_value;
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
	      SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = system_defined_p ? (text_readable && 
		      writable_via_restrictions && category_setter_qm && 
		      system_defined_p && (frame ? 
		      TRUEP(user_writable_slot_of_instance_p(frame,
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)3L))) : 
		      TRUEP(user_writable_slot_of_class_p(ISVREF(class_description,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)1L),
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)3L)))) ? Evaluation_true_value : 
		      Evaluation_false_value) : Evaluation_true_value;
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
	      SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qis_system_defined;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)13L)) = Qis_system_defined;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = system_defined_p ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = system_defined_p ? Evaluation_true_value : 
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
	      SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qdefining_class;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)15L)) = Qdefining_class;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = expose_internal_classes_p ? 
		      defining_class_of_slot(slot_description_or_virtual_attribute) 
		      : 
		      defining_class_of_slot_for_user(slot_description_or_virtual_attribute);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = expose_internal_classes_p ? 
		      defining_class_of_slot(slot_description_or_virtual_attribute) 
		      : 
		      defining_class_of_slot_for_user(slot_description_or_virtual_attribute);
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
	      SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
	  }
	  returned_structure = eval_cons_1(gensymed_symbol,Qab_structure);
	  if (system_defined_p) {
	      temp_1 =  !TRUEP(category_getter_qm);
	      if (temp_1);
	      else
		  temp_1 = CONSP(slot_init_form) ? 
			  EQ(M_CAR(slot_init_form),Kfuncall) : TRUEP(Qnil);
	      if (temp_1);
	      else if (SIMPLE_VECTOR_P(slot_description_or_virtual_attribute) 
		      && EQ(ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_slot_description_g2_struct)) 
			  {
		  gensymed_symbol = 
			  ISVREF(slot_description_or_virtual_attribute,
			  (SI_Long)2L);
		  temp_1 = 
			  TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qcompound_slot_descriptor));
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (!temp_1) {
		  initial_value_qm = Nil;
		  category_evaluator_interface = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol_qm),
			  Qcategory_evaluator_interface);
		  function = category_evaluator_interface ? 
			  ISVREF(category_evaluator_interface,(SI_Long)2L) 
			  : Qnil;
		  if (function) {
		      gensymed_symbol = function;
		      gensymed_symbol_2 = memq_function(Qtext,
			      CDDR(slot_type)) && CONSP(slot_init_form) ? 
			      CAR(slot_init_form) : slot_init_form;
		      gensymed_symbol_3 = Nil;
		      gensymed_symbol_4 = 
			      slot_description_or_virtual_attribute;
		      initial_value_qm = inline_funcall_3(gensymed_symbol,
			      gensymed_symbol_2,gensymed_symbol_3,
			      gensymed_symbol_4);
		  }
		  else
		      initial_value_qm = Nil;
		  if (initial_value_qm)
		      set_evaluation_structure_slot(returned_structure,
			      Qinitial_value,initial_value_qm);
	      }
	  }
	  else if (class_type_specification_p(ISVREF(slot_description_or_virtual_attribute,
		  (SI_Long)5L)))
	      set_evaluation_structure_slot(returned_structure,
		      Qinitial_item_class,
		      M_CAR(M_CDR(ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)5L))));
	  else {
	      value = slot_init_form;
	      if (CONSP(value)) {
		  car_1 = M_CAR(value);
		  cdr_1 = M_CDR(value);
		  if (CONSP(cdr_1)) {
		      temp_2 = M_CAR(cdr_1);
		      temp_1 = SYMBOLP(temp_2);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  temp_1 = temp_1 ? slot_value_number_p(car_1) || 
			  text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1) {
		  managed_value = M_CAR(value);
		  if (EQ(convert_type_or_unit_of_measure_to_type(M_CAR(M_CDR(value))),
			  Qtruth_value)) {
		      if (FIXNUM_EQ(managed_value,Truth))
			  evaluation_value_qm = Evaluation_true_value;
		      else if (FIXNUM_EQ(managed_value,Falsity))
			  evaluation_value_qm = Evaluation_false_value;
		      else
			  evaluation_value_qm = eval_cons_1(managed_value,
				  Qtruth_value);
		  }
		  else
		      evaluation_value_qm = FIXNUMP(managed_value) || 
			      SYMBOLP(managed_value) ? managed_value : 
			      copy_evaluation_value_1(managed_value);
	      }
	      else {
		  if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      evaluation_value_qm = serve_item_p(value) ? value : Nil;
		  else if (CONSP(value) && EQ(M_CAR(value),Kfuncall))
		      evaluation_value_qm = Nil;
		  else
		      evaluation_value_qm = FIXNUMP(value) || value && 
			      SYMBOLP(value) || SIMPLE_VECTOR_P(value) ? 
			      value : copy_if_evaluation_value_1(value);
	      }
	      if (evaluation_value_qm)
		  set_evaluation_structure_slot(returned_structure,
			  Qinitial_value,evaluation_value_qm);
	  }
	  if (text_writable)
	      set_evaluation_structure_slot(returned_structure,
		      Qeditor_grammar,category_symbol_qm);
	  if (do_not_put_slot_in_attribute_tables_p(2,
		  slot_description_or_virtual_attribute,Nil))
	      set_evaluation_structure_slot(returned_structure,Qsuperseded,
		      Evaluation_true_value);
	  if (system_defined_p) {
	      if (category_getter_qm) {
		  temp_2 = get_property_value_function(3,
			  get_symbol_properties_function(category_symbol_qm),
			  Qtype_specification_explicit_complex_type,Nil);
		  if (temp_2);
		  else
		      temp_2 = get_property_value_function(3,
			      get_symbol_properties_function(category_symbol_qm),
			      Qtype_specification_simple_expansion,Nil);
		  set_evaluation_structure_slot(returned_structure,Qtype,
			  generate_type_description_of_attribute(temp_2));
	      }
	  }
	  else
	      set_evaluation_structure_slot(returned_structure,Qtype,
		      generate_type_description_of_attribute(ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)5L)));
	  result = VALUES_1(returned_structure);
      }
      else {
	  shadowed_slot = 
		  find_slot_shadowed_by_virtual_attribute(aliased_slot_name,
		  class_description);
	  text_readable = shadowed_slot ? (assq_function(Qtype,
		  ISVREF(shadowed_slot,(SI_Long)9L)) ? ( 
		  !TRUEP(do_not_put_slot_in_attribute_tables_p(2,
		  shadowed_slot,Nil)) ? T : Nil) : Qnil) : Qnil;
	  text_writable = shadowed_slot ? (writable_via_restrictions ? 
		  (frame ? user_writable_slot_of_instance_p(frame,
		  ISVREF(shadowed_slot,(SI_Long)1L),ISVREF(shadowed_slot,
		  (SI_Long)3L)) : 
		  user_writable_slot_of_class_p(ISVREF(class_description,
		  (SI_Long)1L),ISVREF(shadowed_slot,(SI_Long)1L),
		  ISVREF(shadowed_slot,(SI_Long)3L))) : Qnil) : Qnil;
	  exclude_from_wildcard_denotation = 
		  exclude_from_wildcard_denotation_p(aliased_slot_name);
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)18L + 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattribute_name;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qattribute_name;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = aliased_slot_name;
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
	      item_or_value = aliased_slot_name;
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
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qvirtual;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qvirtual;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = T ? Evaluation_true_value : 
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
	      item_or_value = T ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qtext_readable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)5L)) = Qtext_readable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = text_readable ? Evaluation_true_value : 
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
	      item_or_value = text_readable ? Evaluation_true_value : 
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
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qtext_writable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)7L)) = Qtext_writable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = text_writable ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = text_writable ? Evaluation_true_value : 
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
	      SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qvalue_readable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)9L)) = Qvalue_readable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)6L) ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)6L) ? Evaluation_true_value : 
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
	      SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qvalue_writable;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)11L)) = Qvalue_writable;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = writable_via_restrictions && 
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)7L) ? Evaluation_true_value : 
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
	      SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = writable_via_restrictions && 
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)7L) ? Evaluation_true_value : 
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
	      SVREF(temp,FIX((SI_Long)12L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)15L)) = Qinitial_value;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)13L)) = Qinitial_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      gensymed_symbol_2 = 
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)5L);
	      gensymed_symbol_3 = ISVREF(class_description,(SI_Long)1L);
	      item_or_value = inline_funcall_1(gensymed_symbol_2,
		      gensymed_symbol_3);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)16L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      gensymed_symbol_2 = 
		      ISVREF(slot_description_or_virtual_attribute,
		      (SI_Long)5L);
	      gensymed_symbol_3 = ISVREF(class_description,(SI_Long)1L);
	      item_or_value = inline_funcall_1(gensymed_symbol_2,
		      gensymed_symbol_3);
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
	      SVREF(temp,FIX((SI_Long)14L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)17L)) = Qis_system_defined;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)15L)) = Qis_system_defined;
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
	      SVREF(gensymed_symbol,FIX((SI_Long)18L)) = temp;
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
	      SVREF(temp,FIX((SI_Long)16L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)19L)) = Qdefining_class;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)17L)) = Qdefining_class;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = expose_internal_classes_p ? 
		      defining_class_of_slot(slot_description_or_virtual_attribute) 
		      : 
		      defining_class_of_slot_for_user(slot_description_or_virtual_attribute);
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
	      SVREF(gensymed_symbol,FIX((SI_Long)20L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = expose_internal_classes_p ? 
		      defining_class_of_slot(slot_description_or_virtual_attribute) 
		      : 
		      defining_class_of_slot_for_user(slot_description_or_virtual_attribute);
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
	      SVREF(temp,FIX((SI_Long)18L)) = svref_new_value;
	  }
	  returned_structure = eval_cons_1(gensymed_symbol,Qab_structure);
	  if (text_writable) {
	      temp_2 = assq_function(Qtype,ISVREF(shadowed_slot,(SI_Long)9L));
	      set_evaluation_structure_slot(returned_structure,
		      Qeditor_grammar,SECOND(temp_2));
	  }
	  if (exclude_from_wildcard_denotation)
	      set_evaluation_structure_slot(returned_structure,
		      Qexclude_from_wildcard_denotation,T ? 
		      Evaluation_true_value : Evaluation_false_value);
	  set_evaluation_structure_slot(returned_structure,Qtype,
		  generate_type_description_of_attribute(ISVREF(slot_description_or_virtual_attribute,
		  (SI_Long)3L)));
	  result = VALUES_1(returned_structure);
      }
    POP_SPECIAL();
    return result;
}

/* USER-WRITABLE-SLOT-OF-CLASS-P */
Object user_writable_slot_of_class_p(class_name,slot_name,defining_class_qm)
    Object class_name, slot_name, defining_class_qm;
{
    Object attribute_features;

    x_note_fn_call(182,14);
    attribute_features = get_attribute_features(class_name,slot_name,
	    defining_class_qm,Nil);
    if (type_slot_feature_assq_if_editable(attribute_features))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

static Object Qslot_category;      /* slot-category */

static Object Qclass_of_optional_subframe;  /* class-of-optional-subframe */

/* USER-WRITABLE-SLOT-OF-INSTANCE-P */
Object user_writable_slot_of_instance_p(frame,slot_name,defining_class_qm)
    Object frame, slot_name, defining_class_qm;
{
    Object attribute_features, type_of_slot_qm, list_1;
    char temp;

    x_note_fn_call(182,15);
    attribute_features = get_attribute_features(ISVREF(ISVREF(frame,
	    (SI_Long)1L),(SI_Long)1L),slot_name,defining_class_qm,Nil);
    type_of_slot_qm = type_slot_feature_assq_if_editable(attribute_features);
    if (user_writable_slot_of_class_p(ISVREF(ISVREF(frame,(SI_Long)1L),
	    (SI_Long)1L),slot_name,defining_class_qm) && 
	    transient_or_permanent_p(frame)) {
	list_1 = INLINE_SYMBOL_PLIST(slot_name);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qslot_category))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:;
	temp =  !(list_1 ? TRUEP(M_CAR(M_CDR(list_1))) : TRUEP(Nil));
	if (temp);
	else
	    temp = TRUEP(assq_function(Qclass_of_optional_subframe,
		    attribute_features));
	if (temp);
	else
	    temp = TRUEP(might_be_writable_slot_p(frame,slot_name,
		    type_of_slot_qm));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1( 
		!TRUEP(reason_permanent_items_attribute_is_not_editable(3,
		frame,slot_name,defining_class_qm)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* FIND-SLOT-SHADOWED-BY-VIRTUAL-ATTRIBUTE */
Object find_slot_shadowed_by_virtual_attribute(virtual_attribute_name,
	    class_description)
    Object virtual_attribute_name, class_description;
{
    Object slot_description, ab_loop_list_, aliased_slot_name;
    Object pretty_slot_name, class_or_frame_qm, temp;

    x_note_fn_call(182,16);
    slot_description = Nil;
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
    aliased_slot_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
    class_or_frame_qm = ISVREF(slot_description,(SI_Long)3L);
    temp = get_alias_for_slot_name_if_any(pretty_slot_name,class_or_frame_qm);
    if (temp);
    else
	temp = pretty_slot_name;
    aliased_slot_name = temp;
    if (EQ(aliased_slot_name,virtual_attribute_name))
	goto end_loop;
    goto next_loop;
  end_loop:
    if (EQ(aliased_slot_name,virtual_attribute_name))
	return VALUES_1(slot_description);
    else
	return VALUES_1(Nil);
    return VALUES_1(Qnil);
}

static Object Qtype_or_operator;   /* type-or-operator */

static Object Qoperands;           /* operands */

static Object Qoperand;            /* operand */

static Object Qpossible_values;    /* possible-values */

static Object Qinteger_range;      /* integer-range */

static Object Qfloat_range;        /* float-range */

static Object Qquantity_range;     /* quantity-range */

static Object Qhigh;               /* high */

static Object Qlow;                /* low */

static Object Qslots;              /* slots */

static Object Qrequired_slots;     /* required-slots */

static Object Qelement_type;       /* element-type */

static Object Qminimum_elements;   /* minimum-elements */

static Object Qmaximum_elements;   /* maximum-elements */

static Object Qab_class_name;      /* class-name */

static Object Qno_item;            /* no-item */

static Object Qnone;               /* none */

static Object Qnamed;              /* named */

/* GENERATE-TYPE-DESCRIPTION-OF-ATTRIBUTE */
Object generate_type_description_of_attribute(type_specification)
    Object type_specification;
{
    Object type_or_operator, rest_of_spec, operand, ab_loop_list_, op_list;
    Object ab_loopvar_, ab_loopvar__1, gensymed_symbol, temp, item_or_value;
    Object x2, svref_new_value, details_qm, slots_qm, minimum_contents_qm;
    Object temp_2, slot_spec, ab_loopvar__2, temp_3, elt_type_qm, low_bound_qm;
    Object high_bound_qm, type_name;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(182,17);
    if (CONSP(type_specification)) {
	type_or_operator = CAR(type_specification);
	rest_of_spec = CDR(type_specification);
	if (EQ(type_or_operator,Qab_or) || EQ(type_or_operator,Qand)) {
	    operand = Nil;
	    ab_loop_list_ = rest_of_spec;
	    op_list = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    operand = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = 
		    eval_cons_1(generate_type_description_of_attribute(operand),
		    Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		op_list = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = type_or_operator;
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
		item_or_value = type_or_operator;
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
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qoperands;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qoperands;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = allocate_evaluation_sequence(op_list);
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
		item_or_value = allocate_evaluation_sequence(op_list);
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	    return VALUES_1(Qnil);
	}
	else if (EQ(type_or_operator,Qnot)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnot;
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
		item_or_value = Qnot;
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
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qoperand;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qoperand;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			generate_type_description_of_attribute(FIRST(rest_of_spec));
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
		item_or_value = 
			generate_type_description_of_attribute(FIRST(rest_of_spec));
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(type_or_operator,Qmember)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qmember;
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
		item_or_value = Qmember;
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
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qpossible_values;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qpossible_values;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			allocate_evaluation_sequence(copy_list_using_eval_conses_1(rest_of_spec));
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
		item_or_value = 
			allocate_evaluation_sequence(copy_list_using_eval_conses_1(rest_of_spec));
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(type_or_operator,Qinteger_range) || 
		EQ(type_or_operator,Qfloat_range) || EQ(type_or_operator,
		Qquantity_range)) {
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = type_or_operator;
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
		item_or_value = type_or_operator;
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
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhigh;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qhigh;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnil;
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
		item_or_value = Qnil;
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
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qlow;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)5L)) = Qlow;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnil;
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
		item_or_value = Qnil;
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(type_or_operator,Qab_structure)) {
	    details_qm = M_CDR(type_specification);
	    slots_qm = details_qm ? M_CAR(M_CDR(type_specification)) : Qnil;
	    minimum_contents_qm = details_qm ? CADDR(type_specification) : 
		    Qnil;
	    temp_2 = eval_list_2(Qtype_or_operator,Qab_structure);
	    if (slots_qm) {
		slot_spec = Nil;
		ab_loop_list_ = slots_qm;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		slot_spec = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
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
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattribute_name;
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)1L)) = Qattribute_name;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = FIRST(slot_spec);
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
		    item_or_value = FIRST(slot_spec);
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
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qtype;
		else {
		    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp,FIX((SI_Long)3L)) = Qtype;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    generate_type_description_of_attribute(SECOND(slot_spec));
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
			    generate_type_description_of_attribute(SECOND(slot_spec));
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
		ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,
			Qab_structure),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_1;
	      end_loop_1:
		temp_3 = ab_loopvar_;
		goto end_1;
		temp_3 = Qnil;
	      end_1:;
		temp_3 = eval_list_2(Qslots,
			allocate_evaluation_sequence(temp_3));
	    }
	    else
		temp_3 = Nil;
	    return allocate_evaluation_structure(nconc2(temp_2,
		    nconc2(temp_3,minimum_contents_qm ? 
		    eval_list_2(Qrequired_slots,
		    generate_structure_required_attributes_sequences(minimum_contents_qm)) 
		    : Nil)));
	}
	else if (EQ(type_or_operator,Qsequence)) {
	    elt_type_qm = CADR(type_specification);
	    low_bound_qm = CADDR(type_specification);
	    high_bound_qm = CADDDR(type_specification);
	    temp_3 = eval_list_2(Qtype_or_operator,Qsequence);
	    temp_2 = elt_type_qm ? eval_list_2(Qelement_type,
		    generate_type_description_of_attribute(elt_type_qm)) : Nil;
	    return allocate_evaluation_structure(nconc2(temp_3,
		    nconc2(temp_2,nconc2(low_bound_qm ? 
		    eval_list_2(Qminimum_elements,low_bound_qm) : Nil,
		    high_bound_qm ? eval_list_2(Qmaximum_elements,
		    high_bound_qm) : Nil))));
	}
	else if (EQ(type_or_operator,Qab_class)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qab_class;
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
		item_or_value = Qab_class;
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
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qab_class_name;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)3L)) = Qab_class_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = M_CAR(M_CDR(type_specification));
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
		item_or_value = M_CAR(M_CDR(type_specification));
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(type_or_operator,Qno_item)) {
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
		temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnone;
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
		item_or_value = Qnone;
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else if (EQ(type_or_operator,Qnamed)) {
	    type_name = FIRST(rest_of_spec);
	    temp_2 = get_property_value_function(3,
		    get_symbol_properties_function(type_name),
		    Qtype_specification_explicit_complex_type,Nil);
	    if (temp_2);
	    else
		temp_2 = get_property_value_function(3,
			get_symbol_properties_function(type_name),
			Qtype_specification_simple_expansion,Nil);
	    return generate_type_description_of_attribute(temp_2);
	}
	else if ( !TRUEP(rest_of_spec) && 
		user_type_for_type_specification(type_or_operator)) {
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
		temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = 
			user_type_for_type_specification(type_or_operator);
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
		item_or_value = 
			user_type_for_type_specification(type_or_operator);
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
	    return eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else
	    return VALUES_1(Nil);
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
	    temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype_or_operator;
	else {
	    temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qtype_or_operator;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = 
		    user_type_for_type_specification(type_specification);
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
	    item_or_value = 
		    user_type_for_type_specification(type_specification);
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
	return eval_cons_1(gensymed_symbol,Qab_structure);
    }
}

/* GENERATE-STRUCTURE-REQUIRED-ATTRIBUTES-SEQUENCES */
Object generate_structure_required_attributes_sequences(boolean_combo)
    Object boolean_combo;
{
    Object temp, elt_1, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(182,18);
    if ( !TRUEP(boolean_combo))
	temp = error((SI_Long)1L,
		"Can\'t make sequence showing a null required set of attributes");
    else if (SYMBOLP(boolean_combo))
	temp = boolean_combo;
    else {
	elt_1 = Nil;
	ab_loop_list_ = boolean_combo;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		eval_cons_1(generate_structure_required_attributes_sequences(elt_1),
		Nil);
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
    return VALUES_1(temp);
}

static Object string_constant;     /* "bogus slot name ~a" */

static Object string_constant_1;   /* "malformed component:  ~a" */

static Object string_constant_2;   /* "bad component contents:  ~a" */

/* G2-TEST-CONCLUDE-COMPONENT */
Object g2_test_conclude_component(frame,slot_name_ev,
	    class_if_specific_or_false,evaluation_value)
    Object frame, slot_name_ev, class_if_specific_or_false, evaluation_value;
{
    Object class_if_specific_qm, temp, slot_name, unaliased_slot_name;
    Object slot_description, slot_type_qm, top_of_stack, message_1, category;
    Object text_slot_p, category_evaluator_interface, parse_result_maker_qm;
    Object current_edit_state, svref_arg_1, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm, commit_error_string_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(182,19);
    class_if_specific_qm = class_if_specific_or_false && 
	    SYMBOLP(class_if_specific_or_false) ? 
	    class_if_specific_or_false : Qnil;
    temp = slot_name_ev;
    reclaim_evaluation_value(slot_name_ev);
    slot_name = temp;
    if ( !(FIXNUMP(class_if_specific_or_false) || 
	    SYMBOLP(class_if_specific_or_false) || 
	    SIMPLE_VECTOR_P(class_if_specific_or_false)))
	reclaim_if_evaluation_value_1(class_if_specific_or_false);
    reclaim_evaluation_value(slot_name_ev);
    unaliased_slot_name = get_slot_name_for_alias_if_any(slot_name,frame);
    if (unaliased_slot_name);
    else
	unaliased_slot_name = slot_name;
    slot_description = 
	    get_slot_description_of_class_description_function(unaliased_slot_name,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    slot_type_qm = slot_description ? assq_function(Qtype,
	    ISVREF(slot_description,(SI_Long)9L)) : Qnil;
    if ( !TRUEP(slot_description)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant,
		slot_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (slot_type_qm) {
	category = SECOND(slot_type_qm);
	text_slot_p = memq_function(Qtext,CDDR(slot_type_qm));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(category),
		Qcategory_evaluator_interface);
	parse_result_maker_qm = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (parse_result_maker_qm) {
	    current_edit_state = make_edit_state_1();
	    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		    0);
	      svref_arg_1 = Current_edit_state;
	      SVREF(svref_arg_1,FIX((SI_Long)3L)) = frame;
	      gensymed_symbol = parse_result_maker_qm;
	      gensymed_symbol_1 = evaluation_value;
	      gensymed_symbol_2 = frame;
	      gensymed_symbol_3 = slot_description;
	      gensymed_symbol_4 = Nil;
	      result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	      MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	      if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		  top_of_stack = Cached_top_of_stack;
		  message_1 = tformat_stack_error_text_string(2,
			  string_constant_1,error_string_qm);
		  temp = raw_stack_error_named_error(top_of_stack,message_1);
	      }
	      else {
		  commit_error_string_qm = 
			  simple_commit_parse_result(frame,
			  unaliased_slot_name,class_if_specific_qm,
			  slot_description,Nil,Nil,category,text_slot_p,
			  parse_result_or_bad_phrase,Nil,evaluation_value);
		  if (commit_error_string_qm) {
		      top_of_stack = Cached_top_of_stack;
		      message_1 = tformat_stack_error_text_string(2,
			      string_constant_2,commit_error_string_qm);
		      temp = raw_stack_error_named_error(top_of_stack,
			      message_1);
		  }
		  else
		      temp = Nil;
	      }
	      goto end_attribute_export_conclude_context;
	    end_attribute_export_conclude_context:
	      reclaim_edit_state_1(Current_edit_state);
	      result = VALUES_1(temp);
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-TEST-GET-COMPONENT */
Object g2_test_get_component(frame,slot_name_ev,class_if_specific_or_false)
    Object frame, slot_name_ev, class_if_specific_or_false;
{
    Object class_if_specific_qm, temp, slot_name, slot_description;
    Object slot_type_qm, top_of_stack, message_1, evaluator_info, getter_qm;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object extracted_value, reclaim_p, gensymed_symbol_3;
    Object result;

    x_note_fn_call(182,20);
    class_if_specific_qm = class_if_specific_or_false && 
	    SYMBOLP(class_if_specific_or_false) ? 
	    class_if_specific_or_false : Qnil;
    temp = slot_name_ev;
    reclaim_evaluation_value(slot_name_ev);
    slot_name = temp;
    if ( !(FIXNUMP(class_if_specific_or_false) || 
	    SYMBOLP(class_if_specific_or_false) || 
	    SIMPLE_VECTOR_P(class_if_specific_or_false)))
	reclaim_if_evaluation_value_1(class_if_specific_or_false);
    reclaim_evaluation_value(slot_name_ev);
    temp = get_slot_name_for_alias_if_any(slot_name,frame);
    if (temp);
    else
	temp = slot_name;
    slot_description = 
	    get_slot_description_of_class_description_function(temp,
	    ISVREF(frame,(SI_Long)1L),class_if_specific_qm);
    slot_type_qm = slot_description ? assq_function(Qtype,
	    ISVREF(slot_description,(SI_Long)9L)) : Qnil;
    if ( !TRUEP(slot_description)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant,
		slot_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (slot_type_qm) {
	evaluator_info = ISVREF(slot_description,(SI_Long)10L);
	if (evaluator_info);
	else
	    evaluator_info = cache_evaluator_slot_info(slot_description);
	getter_qm = ISVREF(evaluator_info,(SI_Long)3L);
	if (getter_qm) {
	    gensymed_symbol = ISVREF(evaluator_info,(SI_Long)5L);
	    gensymed_symbol_1 = get_slot_description_value(frame,
		    slot_description);
	    gensymed_symbol_2 = evaluator_info;
	    result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    MVS_2(result,extracted_value,reclaim_p);
	    gensymed_symbol = getter_qm;
	    gensymed_symbol_1 = extracted_value;
	    gensymed_symbol_2 = frame;
	    gensymed_symbol_3 = slot_description;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    if (reclaim_p)
		reclaim_slot_value(extracted_value);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_3;   /* "Cannot edit ~NF, because ~A.  See the saving-parameters." */

static Object Qslot_value_compiler;  /* slot-value-compiler */

static Object Qtwrite_edit_backtrace_info;  /* twrite-edit-backtrace-info */

/* SIMPLE-COMMIT-PARSE-RESULT */
Object simple_commit_parse_result(frame,slot_name,defining_class_qm,
	    slot_description,slot_component_name_qm,
	    slot_component_indicator_qm,category_qm,text_type_slot_p,
	    parse_result,editing_for_runtime_change_p,evaluation_value)
    Object frame, slot_name, defining_class_qm, slot_description;
    Object slot_component_name_qm, slot_component_indicator_qm, category_qm;
    Object text_type_slot_p, parse_result, editing_for_runtime_change_p;
    Object evaluation_value;
{
    Object reason_not_editable_qm, slot_value_compiler_qm;
    Object index_of_top_of_backtrace_stack, old_top_of_stack;
    Object elements_to_push_qm, temp, stored_elements_to_push, index_1;
    Object elements_to_push_qm_old_value, temp_1, info_symbol;
    Object twrite_function_qm, number_of_args, svref_arg_2;
    Object new_value_or_bad_phrase, explanatory_text_string_if_bad_phrase_qm;
    Object evaluator_info, new_value, do_not_note_permanent_changes_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(182,21);
    reason_not_editable_qm = 
	    reason_permanent_items_attribute_is_not_editable(4,frame,
	    slot_name,defining_class_qm,slot_description);
    if (reason_not_editable_qm)
	return tformat_text_string(3,string_constant_3,frame,
		reason_not_editable_qm);
    slot_value_compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
	    Qslot_value_compiler);
    if ( !TRUEP(slot_value_compiler_qm) || EQ(parse_result,Bad_phrase))
	result = VALUES_1(parse_result);
    else {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      old_top_of_stack = Index_of_top_of_backtrace_stack;
	      elements_to_push_qm = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      elements_to_push_qm = backtrace_cons_1(slot_name,
		      elements_to_push_qm);
	      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		      Size_of_basic_backtrace_information),
		      Maximum_index_in_backtrace_stack_for_internal_error)) {
		  stored_elements_to_push = elements_to_push_qm;
		  index_1 = Index_of_top_of_backtrace_stack;
		next_loop:
		  if ( !TRUEP(elements_to_push_qm))
		      goto end_loop;
		  temp = Backtrace_stack_for_internal_error;
		  elements_to_push_qm_old_value = elements_to_push_qm;
		  temp_1 = FIRST(elements_to_push_qm_old_value);
		  elements_to_push_qm = REST(elements_to_push_qm_old_value);
		  SVREF(temp,index_1) = temp_1;
		  index_1 = FIXNUM_SUB1(index_1);
		  goto next_loop;
		end_loop:;
		  reclaim_backtrace_list_1(stored_elements_to_push);
		  info_symbol = Qcompile;
		  twrite_function_qm = Qtwrite_edit_backtrace_info;
		  number_of_args = 
			  FIXNUM_MINUS(Index_of_top_of_backtrace_stack,
			  old_top_of_stack);
		  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
		  temp = Backtrace_stack_for_internal_error;
		  svref_arg_2 = Index_of_top_of_backtrace_stack;
		  SVREF(temp,svref_arg_2) = number_of_args;
		  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
		  temp = Backtrace_stack_for_internal_error;
		  svref_arg_2 = Index_of_top_of_backtrace_stack;
		  SVREF(temp,svref_arg_2) = twrite_function_qm;
		  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
		  Index_of_top_of_backtrace_stack = temp;
		  temp = Backtrace_stack_for_internal_error;
		  svref_arg_2 = Index_of_top_of_backtrace_stack;
		  SVREF(temp,svref_arg_2) = info_symbol;
	      }
	      else {
		  Index_of_top_of_backtrace_stack = old_top_of_stack;
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
		  SVREF(temp,svref_arg_2) = Qcompile;
	      }
	  }
	  result = funcall(7,slot_value_compiler_qm,parse_result,frame,
		  slot_name,defining_class_qm,slot_component_name_qm,
		  slot_component_name_qm ? get_slot_component_group(3,
		  frame,slot_name,slot_component_indicator_qm) : Qnil);
	POP_SPECIAL();
    }
    MVS_2(result,new_value_or_bad_phrase,
	    explanatory_text_string_if_bad_phrase_qm);
    if (EQ(new_value_or_bad_phrase,Bad_phrase))
	return VALUES_1(explanatory_text_string_if_bad_phrase_qm);
    else {
	evaluator_info = ISVREF(slot_description,(SI_Long)10L);
	if (evaluator_info);
	else
	    evaluator_info = cache_evaluator_slot_info(slot_description);
	temp_1 = ISVREF(evaluator_info,(SI_Long)4L);
	new_value = FUNCALL_3(temp_1,
		copy_for_slot_value(new_value_or_bad_phrase),
		evaluation_value,evaluator_info);
	temp_1 = Do_not_note_permanent_changes_p;
	if (temp_1);
	else
	    temp_1 = editing_for_runtime_change_p;
	do_not_note_permanent_changes_p = temp_1;
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
		0);
	  if (editing_for_runtime_change_p)
	      note_kb_state_change_to_slot_by_saving_text(frame,
		      slot_description);
	  change_slot_description_value_function(frame,slot_description,
		  new_value,slot_component_name_qm,
		  slot_component_indicator_qm);
	  result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
}

/* TEXT-SLOT-VALUE-TO-EVALUATION-TEXT */
Object text_slot_value_to_evaluation_text(frame,slot_value,type_of_slot)
    Object frame, slot_value, type_of_slot;
{
    Object text, evaluation_text;

    x_note_fn_call(182,22);
    text = make_text_representation_for_slot_value_itself(frame,slot_value,
	    type_of_slot);
    evaluation_text = convert_text_to_text_string(1,text);
    reclaim_text(text);
    return VALUES_1(evaluation_text);
}

static Object string_constant_4;   /* "~a " */

static Object Qparsing_context_complete_status;  /* parsing-context-complete-status */

static Object array_constant;      /* # */

static Object string_constant_5;   /* "ambiguous-phrase" */

/* PARSE-TEXT-STRING */
Object parse_text_string varargs_1(int, n)
{
    Object text_string, category;
    Object frame_being_edited_qm, previous_edit_state, type_of_slot;
    Object string_to_parse, parsing_context, parse_result;
    Object parse_result_error_string_qm;
    Object keep_edit_workspace_hidden_no_matter_what_qm, parse_status;
    Object error_string_qm, current_edit_state, incomplete_phrase;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object parse_trees;
    Declare_varargs_nonrelocating;
    Declare_special(3);
    Object result;

    x_note_fn_call(182,23);
    INIT_ARGS_nonrelocating();
    text_string = REQUIRED_ARG_nonrelocating();
    category = REQUIRED_ARG_nonrelocating();
    frame_being_edited_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    previous_edit_state = Current_edit_state;
    type_of_slot = gensym_list_2(Qtype,category);
    string_to_parse = tformat_text_string(2,string_constant_4,text_string);
    parsing_context = create_parsing_context(3,Nil,Nil,type_of_slot);
    parse_result = Bad_phrase;
    parse_result_error_string_qm = Nil;
    keep_edit_workspace_hidden_no_matter_what_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Keep_edit_workspace_hidden_no_matter_what_qm,Qkeep_edit_workspace_hidden_no_matter_what_qm,keep_edit_workspace_hidden_no_matter_what_qm,
	    2);
      SVREF(parsing_context,FIX((SI_Long)3L)) = frame_being_edited_qm;
      result = advance_parsing_context(parsing_context,string_to_parse);
      MVS_2(result,parse_status,error_string_qm);
      if (EQ(parse_status,Qparsing_context_complete_status)) {
	  current_edit_state = parsing_context;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		  1);
	    incomplete_phrase = Nil;
	    ab_loop_list_ = ISVREF(ISVREF(ISVREF(parsing_context,
		    (SI_Long)105L),(SI_Long)2L),(SI_Long)6L);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    incomplete_phrase = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(incomplete_phrase,(SI_Long)1L),
		    ISVREF(parsing_context,(SI_Long)30L))) {
		temp = ISVREF(incomplete_phrase,(SI_Long)2L);
		ab_loopvar__2 = phrase_cons(CAR(temp),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop;
	  end_loop:
	    parse_trees = ab_loopvar_;
	    goto end_1;
	    parse_trees = Qnil;
	  end_1:;
	    if ( !TRUEP(parse_trees))
		parse_result_error_string_qm = 
			copy_constant_wide_string_given_length(array_constant,
			FIX((SI_Long)17L));
	    else if ( !TRUEP(CDR(parse_trees))) {
		current_edit_state = previous_edit_state;
		PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
			0);
		  parse_result = copy_for_phrase(CAR(parse_trees));
		POP_SPECIAL();
	    }
	    else
		parse_result_error_string_qm = string_constant_5;
	  POP_SPECIAL();
      }
      else if ( !TRUEP(error_string_qm))
	  parse_result_error_string_qm = 
		  copy_constant_wide_string_given_length(array_constant,
		  FIX((SI_Long)17L));
      else
	  parse_result_error_string_qm = error_string_qm;
      delete_parsing_context(parsing_context);
      reclaim_gensym_list_1(type_of_slot);
      reclaim_text_string(string_to_parse);
      result = VALUES_2(parse_result,parse_result_error_string_qm);
    POP_SPECIAL();
    return result;
}

static Object string_constant_6;   /* "There is no class named ~a." */

static Object list_constant_1;     /* # */

static Object string_constant_7;   /* "Specific Attributes must be a sequence of symbols" */

static Object Qadministrator;      /* administrator */

/* G2-GET-ATTRIBUTE-DESCRIPTIONS-OF-CLASS */
Object g2_get_attribute_descriptions_of_class(class_name,specific_attributes)
    Object class_name, specific_attributes;
{
    Object top_of_stack, message_1, name_and_description_alist, name, slot;
    Object ab_loop_list_, struct_list, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, gensymed_symbol, held_vector, value, ab_loop_it_;
    Object elt_1, validated_elt;
    SI_Long next_index, length_1;
    char all_attributes_p, temp;

    x_note_fn_call(182,24);
    if ( !TRUEP(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_6,
		class_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(type_specification_type_p(specific_attributes,
	    list_constant_1))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_7);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    all_attributes_p = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(specific_attributes),
	    (SI_Long)1L))) == (SI_Long)0L;
    name_and_description_alist = 
	    get_list_of_all_user_visible_attributes(lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop));
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
    temp = all_attributes_p;
    if (temp);
    else {
	gensymed_symbol = specific_attributes;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	value = Nil;
	ab_loop_it_ = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	value = validated_elt;
	ab_loop_it_ = evaluation_value_equal_p(name,value);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
    }
    if (temp) {
	ab_loopvar__1 = 
		eval_cons_1(generate_description_of_attribute(class_name,
		name,slot,
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop),Nil,Qadministrator,Nil),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    struct_list = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    reclaim_evaluation_value(specific_attributes);
    return allocate_evaluation_sequence(struct_list);
    return VALUES_1(Qnil);
}

static Object Kstack_error;        /* :stack-error */

/* G2-GET-ATTRIBUTE-DESCRIPTIONS-OF-CLASS-SYSTEM-RPC-INTERNAL */
Object g2_get_attribute_descriptions_of_class_system_rpc_internal(gensymed_symbol,
	    class_1,specific_attributes)
    Object gensymed_symbol, class_1, specific_attributes;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(182,25);
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
	    result = g2_get_attribute_descriptions_of_class(class_1,
		    specific_attributes);
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

/* G2-GET-ATTRIBUTE-VALUES-OF-ITEM */
Object g2_get_attribute_values_of_item(frame,specific_attributes)
    Object frame, specific_attributes;
{
    Object class_description, name_and_description_alist, top_of_stack;
    Object message_1, name, slot_description_or_virtual_attribute;
    Object ab_loop_list_, want_attribute_p, attribute_value_qm;
    Object attribute_names_and_values, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, temp, gensymed_symbol, held_vector, value;
    Object ab_loop_it_, elt_1, validated_elt;
    SI_Long next_index, length_1;
    char all_attributes_p;

    x_note_fn_call(182,26);
    class_description = ISVREF(frame,(SI_Long)1L);
    name_and_description_alist = 
	    get_list_of_all_user_visible_attributes(class_description);
    if ( !TRUEP(type_specification_type_p(specific_attributes,
	    list_constant_1))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_7);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = name_and_description_alist;
    all_attributes_p = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(specific_attributes),
	    (SI_Long)1L))) == (SI_Long)0L;
    want_attribute_p = Nil;
    attribute_value_qm = Nil;
    attribute_names_and_values = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = all_attributes_p ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = specific_attributes;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	value = Nil;
	ab_loop_it_ = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	value = validated_elt;
	ab_loop_it_ = evaluation_value_equal_p(name,value);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
    }
    want_attribute_p = temp;
    attribute_value_qm = want_attribute_p ? 
	    get_attribute_description_evaluation_value(frame,
	    slot_description_or_virtual_attribute) : Qnil;
    if (attribute_value_qm) {
	ab_loopvar__1 = eval_cons_1(name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	ab_loopvar__1 = eval_cons_1(attribute_value_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    reclaim_evaluation_value(specific_attributes);
    return allocate_evaluation_structure(attribute_names_and_values);
    return VALUES_1(Qnil);
}

/* G2-GET-ATTRIBUTE-VALUES-OF-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_get_attribute_values_of_item_system_rpc_internal(gensymed_symbol,
	    item,specific_attributes)
    Object gensymed_symbol, item, specific_attributes;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(182,27);
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
	    result = g2_get_attribute_values_of_item(item,specific_attributes);
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

/* G2-GET-ATTRIBUTE-TEXTS-OF-ITEM */
Object g2_get_attribute_texts_of_item(frame,specific_attributes)
    Object frame, specific_attributes;
{
    Object class_description, name_and_description_alist, top_of_stack;
    Object message_1, name, slot_description_or_virtual_attribute;
    Object ab_loop_list_, want_attribute_p, attribute_text_value_qm;
    Object attribute_names_and_values, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, temp, gensymed_symbol, held_vector, value;
    Object ab_loop_it_, elt_1, validated_elt;
    SI_Long next_index, length_1;
    char all_attributes_p;

    x_note_fn_call(182,28);
    class_description = ISVREF(frame,(SI_Long)1L);
    name_and_description_alist = 
	    get_list_of_all_user_visible_attributes(class_description);
    if ( !TRUEP(type_specification_type_p(specific_attributes,
	    list_constant_1))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_7);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = name_and_description_alist;
    all_attributes_p = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(specific_attributes),
	    (SI_Long)1L))) == (SI_Long)0L;
    want_attribute_p = Nil;
    attribute_text_value_qm = Nil;
    attribute_names_and_values = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = all_attributes_p ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = specific_attributes;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	value = Nil;
	ab_loop_it_ = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	value = validated_elt;
	ab_loop_it_ = evaluation_value_equal_p(name,value);
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
    }
    want_attribute_p = temp;
    attribute_text_value_qm = want_attribute_p ? 
	    serve_text_of_attribute(frame,name,Nil) : Qnil;
    if (attribute_text_value_qm) {
	ab_loopvar__1 = eval_cons_1(name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	ab_loopvar__1 = eval_cons_1(attribute_text_value_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    reclaim_evaluation_value(specific_attributes);
    return allocate_evaluation_structure(attribute_names_and_values);
    return VALUES_1(Qnil);
}

/* G2-GET-ATTRIBUTE-TEXTS-OF-ITEM-SYSTEM-RPC-INTERNAL */
Object g2_get_attribute_texts_of_item_system_rpc_internal(gensymed_symbol,
	    item,specific_attributes)
    Object gensymed_symbol, item, specific_attributes;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(182,29);
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
	    result = g2_get_attribute_texts_of_item(item,specific_attributes);
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

static Object Qname;               /* name */

static Object Qclass_qualifier;    /* class-qualifier */

/* G2-GET-DENOTED-ATTRIBUTE-TEXTS */
Object g2_get_denoted_attribute_texts(frame,denoted_attributes_sequence)
    Object frame, denoted_attributes_sequence;
{
    Object gensymed_symbol, held_vector, denoted_attribute, name;
    Object class_qualifier_qm, texts, ab_loopvar_, ab_loopvar__1, elt_1;
    Object validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(182,30);
    gensymed_symbol = denoted_attributes_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    denoted_attribute = Nil;
    name = Nil;
    class_qualifier_qm = Nil;
    texts = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
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
    denoted_attribute = validated_elt;
    name = estructure_slot(denoted_attribute,Qname,Nil);
    class_qualifier_qm = estructure_slot(denoted_attribute,
	    Qclass_qualifier,Nil);
    ab_loopvar__1 = eval_cons_1(serve_text_of_attribute(frame,name,
	    class_qualifier_qm),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	texts = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    reclaim_evaluation_value(denoted_attributes_sequence);
    return allocate_evaluation_sequence(texts);
    return VALUES_1(Qnil);
}

/* G2-GET-DENOTED-ATTRIBUTE-TEXTS-SYSTEM-RPC-INTERNAL */
Object g2_get_denoted_attribute_texts_system_rpc_internal(gensymed_symbol,
	    item,denoted_attributes_sequence)
    Object gensymed_symbol, item, denoted_attributes_sequence;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(182,31);
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
	    result = g2_get_denoted_attribute_texts(item,
		    denoted_attributes_sequence);
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

static Object string_constant_8;   /* "The first argument to g2-get-attributes-visible-in-mode must be a symbol or an item." */

static Object Quuid;               /* uuid */

static Object Qshow_uuids_in_attribute_tables;  /* show-uuids-in-attribute-tables */

/* G2-GET-ATTRIBUTES-VISIBLE-IN-MODE */
Object g2_get_attributes_visible_in_mode(class_or_item,user_mode)
    Object class_or_item, user_mode;
{
    Object x2, top_of_stack, message_1, class_description;
    Object name_and_description_alist, name;
    Object slot_description_or_virtual_attribute, ab_loop_list_;
    Object attribute_names, ab_loopvar_, ab_loopvar__1, ab_loop_desetq_, frame;
    Object slot_description, defining_class_name, temp_1, aliased_slot_name;
    Object pretty_slot_name, class_or_frame_qm;
    char temp;

    x_note_fn_call(182,32);
    temp = SYMBOLP(class_or_item);
    if (temp);
    else if (SIMPLE_VECTOR_P(class_or_item) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(class_or_item)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(class_or_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(class_or_item,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_8);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    class_description = SYMBOLP(class_or_item) ? 
	    lookup_global_or_kb_specific_property_value(class_or_item,
	    Class_description_gkbprop) : ISVREF(class_or_item,(SI_Long)1L);
    if ( !TRUEP(class_description)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_6,
		class_or_item);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    name_and_description_alist = 
	    get_list_of_all_user_visible_attributes(class_description);
    name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = name_and_description_alist;
    attribute_names = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = SIMPLE_VECTOR_P(slot_description_or_virtual_attribute) ? 
	    EQ(ISVREF(slot_description_or_virtual_attribute,(SI_Long)0L),
	    Qg2_defstruct_structure_name_virtual_attribute_g2_struct) : 
	    TRUEP(Qnil);
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(class_or_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(class_or_item)) > 
		(SI_Long)2L &&  !EQ(ISVREF(class_or_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(class_or_item,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    frame = class_or_item;
	    slot_description = slot_description_or_virtual_attribute;
	    defining_class_name = ISVREF(slot_description,(SI_Long)3L);
	    if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
		temp_1 = ISVREF(slot_description,(SI_Long)3L);
		temp =  !EQ(temp_1,
			ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
			(SI_Long)2L),class_description,Nil),(SI_Long)3L));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		aliased_slot_name = ISVREF(slot_description,(SI_Long)1L);
	    else {
		pretty_slot_name = ISVREF(slot_description,(SI_Long)2L);
		class_or_frame_qm = defining_class_name;
		aliased_slot_name = 
			get_alias_for_slot_name_if_any(pretty_slot_name,
			class_or_frame_qm);
		if (aliased_slot_name);
		else
		    aliased_slot_name = pretty_slot_name;
	    }
	    temp = TRUEP(include_slot_in_attribute_table_for_mode_p(frame,
		    aliased_slot_name,defining_class_name,user_mode));
	}
	else
	    temp = TRUEP(T);
    }
    if ((temp ?  !TRUEP(memq_function(name,attribute_names)) : TRUEP(Nil)) 
	    ?  !EQ(name,Quuid) || BOUNDP(Qmiscellaneous_parameters) && 
	    Miscellaneous_parameters && 
	    get_slot_value_function(Miscellaneous_parameters,
	    Qshow_uuids_in_attribute_tables,Nil) : TRUEP(Nil)) {
	ab_loopvar__1 = eval_cons_1(name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    return allocate_evaluation_sequence(attribute_names);
    return VALUES_1(Qnil);
}

/* G2-GET-ATTRIBUTES-VISIBLE-IN-MODE-SYSTEM-RPC-INTERNAL */
Object g2_get_attributes_visible_in_mode_system_rpc_internal(gensymed_symbol,
	    class_or_item,user_mode)
    Object gensymed_symbol, class_or_item, user_mode;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(182,33);
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
	    result = g2_get_attributes_visible_in_mode(class_or_item,
		    user_mode);
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

/* G2-GET-FILTERED-ATTRIBUTES */
Object g2_get_filtered_attributes(frame,filter_flags)
    Object frame, filter_flags;
{
    Object class_description, filter, attributes_alist, name;
    Object slot_description_or_virtual_attribute, ab_loop_list_;
    Object attribute_value, attribute_names, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_;

    x_note_fn_call(182,34);
    class_description = ISVREF(frame,(SI_Long)1L);
    filter = filter_flags;
    attributes_alist = 
	    get_list_of_all_user_visible_attributes(class_description);
    name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = attributes_alist;
    attribute_value = Nil;
    attribute_names = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (slot_passes_filter_p(slot_description_or_virtual_attribute,filter))
	attribute_value = get_attribute_description_evaluation_value(frame,
		slot_description_or_virtual_attribute);
    if (attribute_value) {
	ab_loopvar__1 = eval_cons_1(name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(attributes_alist);
    return allocate_evaluation_sequence(attribute_names);
    return VALUES_1(Qnil);
}

/* SLOT-PASSES-FILTER-P */
Object slot_passes_filter_p(slot_description,filter)
    Object slot_description, filter;
{
    x_note_fn_call(182,35);
    return VALUES_1(T);
}

void attr_export_INIT()
{
    Object gensymed_symbol, system_defined_rpcs_new_value;
    Object Qg2_get_filtered_attributes;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_get_attributes_visible_in_mode_system_rpc_internal;
    Object Qg2_get_attributes_visible_in_mode, Qsystem_defined_rpc;
    Object list_constant_5, list_constant_21, list_constant_20;
    Object list_constant_19, list_constant_18, Quser_mode, list_constant_3;
    Object Qitem_or_datum, Qclass_or_item;
    Object Qg2_get_denoted_attribute_texts_system_rpc_internal;
    Object Qg2_get_denoted_attribute_texts, list_constant_17, list_constant_16;
    Object list_constant_10, list_constant_15, Qdenoted_attributes_sequence;
    Object Qg2_get_attribute_texts_of_item_system_rpc_internal;
    Object Qg2_get_attribute_texts_of_item, list_constant_14, list_constant_13;
    Object Qg2_get_attribute_values_of_item_system_rpc_internal;
    Object Qg2_get_attribute_values_of_item, list_constant_12;
    Object list_constant_11, Qdatum, Qspecific_attributes, list_constant_9;
    Object Qg2_get_attribute_descriptions_of_class_system_rpc_internal;
    Object Qg2_get_attribute_descriptions_of_class, list_constant_8;
    Object list_constant_7, list_constant_6, list_constant_4, list_constant_2;
    Object Qg2_test_get_component, Qg2_test_conclude_component;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qroot, Qsystem_item;
    Object Qproto_block, Qkb_frame, Qentity;

    x_note_fn_call(182,36);
    SET_PACKAGE("AB");
    if (Current_attribute_description_class == UNBOUND)
	Current_attribute_description_class = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_virtual_attribute_g2_struct = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_slot_description_g2_struct = 
	    STATIC_SYMBOL("SLOT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    Qkb_frame = STATIC_SYMBOL("KB-FRAME",AB_package);
    Qproto_block = STATIC_SYMBOL("PROTO-BLOCK",AB_package);
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    list_constant = STATIC_LIST((SI_Long)6L,Qentity,Qblock,Qkb_frame,
	    Qproto_block,Qsystem_item,Qroot);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qsuperior_class_p = STATIC_SYMBOL("SUPERIOR-CLASS-P",AB_package);
    Qdefining_class_of_attr_pair = 
	    STATIC_SYMBOL("DEFINING-CLASS-OF-ATTR-PAIR",AB_package);
    SET_SYMBOL_FUNCTION(Qsuperior_class_p,STATIC_FUNCTION(superior_class_p,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qdefining_class_of_attr_pair,
	    STATIC_FUNCTION(defining_class_of_attr_pair,NIL,FALSE,1,1));
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    Qpreviously_put_in_attribute_tables = 
	    STATIC_SYMBOL("PREVIOUSLY-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    if (Include_slots_visible_only_to_roles_p == UNBOUND)
	Include_slots_visible_only_to_roles_p = T;
    Qdo_not_put_in_attribute_tables = 
	    STATIC_SYMBOL("DO-NOT-PUT-IN-ATTRIBUTE-TABLES",AB_package);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    Qdeprecated = STATIC_SYMBOL("DEPRECATED",AB_package);
    Qedit_attribute = STATIC_SYMBOL("EDIT-ATTRIBUTE",AB_package);
    Qnot_user_editable = STATIC_SYMBOL("NOT-USER-EDITABLE",AB_package);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvirtual = STATIC_SYMBOL("VIRTUAL",AB_package);
    Qtext_readable = STATIC_SYMBOL("TEXT-READABLE",AB_package);
    Qtext_writable = STATIC_SYMBOL("TEXT-WRITABLE",AB_package);
    Qvalue_readable = STATIC_SYMBOL("VALUE-READABLE",AB_package);
    Qvalue_writable = STATIC_SYMBOL("VALUE-WRITABLE",AB_package);
    Qis_system_defined = STATIC_SYMBOL("IS-SYSTEM-DEFINED",AB_package);
    Qdefining_class = STATIC_SYMBOL("DEFINING-CLASS",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qcompound_slot_descriptor = STATIC_SYMBOL("COMPOUND-SLOT-DESCRIPTOR",
	    AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qinitial_item_class = STATIC_SYMBOL("INITIAL-ITEM-CLASS",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qeditor_grammar = STATIC_SYMBOL("EDITOR-GRAMMAR",AB_package);
    Qsuperseded = STATIC_SYMBOL("SUPERSEDED",AB_package);
    Qtype_specification_explicit_complex_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-EXPLICIT-COMPLEX-TYPE",
	    AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qexclude_from_wildcard_denotation = 
	    STATIC_SYMBOL("EXCLUDE-FROM-WILDCARD-DENOTATION",AB_package);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Qclass_of_optional_subframe = 
	    STATIC_SYMBOL("CLASS-OF-OPTIONAL-SUBFRAME",AB_package);
    Qtype_or_operator = STATIC_SYMBOL("TYPE-OR-OPERATOR",AB_package);
    Qoperands = STATIC_SYMBOL("OPERANDS",AB_package);
    Qoperand = STATIC_SYMBOL("OPERAND",AB_package);
    Qpossible_values = STATIC_SYMBOL("POSSIBLE-VALUES",AB_package);
    Qinteger_range = STATIC_SYMBOL("INTEGER-RANGE",AB_package);
    Qfloat_range = STATIC_SYMBOL("FLOAT-RANGE",AB_package);
    Qquantity_range = STATIC_SYMBOL("QUANTITY-RANGE",AB_package);
    Qhigh = STATIC_SYMBOL("HIGH",AB_package);
    Qlow = STATIC_SYMBOL("LOW",AB_package);
    Qslots = STATIC_SYMBOL("SLOTS",AB_package);
    Qrequired_slots = STATIC_SYMBOL("REQUIRED-SLOTS",AB_package);
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    Qminimum_elements = STATIC_SYMBOL("MINIMUM-ELEMENTS",AB_package);
    Qmaximum_elements = STATIC_SYMBOL("MAXIMUM-ELEMENTS",AB_package);
    Qab_class_name = STATIC_SYMBOL("CLASS-NAME",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qg2_test_conclude_component = 
	    STATIC_SYMBOL("G2-TEST-CONCLUDE-COMPONENT",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_test_conclude_component,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant = STATIC_STRING("bogus slot name ~a");
    string_constant_1 = STATIC_STRING("malformed component:  ~a");
    string_constant_2 = STATIC_STRING("bad component contents:  ~a");
    SET_SYMBOL_FUNCTION(Qg2_test_conclude_component,
	    STATIC_FUNCTION(g2_test_conclude_component,NIL,FALSE,4,4));
    Qg2_test_get_component = STATIC_SYMBOL("G2-TEST-GET-COMPONENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_test_get_component,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_test_get_component,
	    STATIC_FUNCTION(g2_test_get_component,NIL,FALSE,3,3));
    string_constant_3 = 
	    STATIC_STRING("Cannot edit ~NF, because ~A.  See the saving-parameters.");
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    Qtwrite_edit_backtrace_info = 
	    STATIC_SYMBOL("TWRITE-EDIT-BACKTRACE-INFO",AB_package);
    string_constant_4 = STATIC_STRING("~a ");
    Qparsing_context_complete_status = 
	    STATIC_SYMBOL("PARSING-CONTEXT-COMPLETE-STATUS",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    string_constant_5 = STATIC_STRING("ambiguous-phrase");
    Qg2_get_attribute_descriptions_of_class = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-DESCRIPTIONS-OF-CLASS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_attribute_descriptions_of_class,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_6 = STATIC_STRING("There is no class named ~a.");
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qsequence,Qsymbol);
    string_constant_7 = 
	    STATIC_STRING("Specific Attributes must be a sequence of symbols");
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_descriptions_of_class,
	    STATIC_FUNCTION(g2_get_attribute_descriptions_of_class,NIL,
	    FALSE,2,2));
    Qg2_get_attribute_descriptions_of_class_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-DESCRIPTIONS-OF-CLASS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_3 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_6 = STATIC_LIST_STAR((SI_Long)3L,Qab_class,Ktype,
	    list_constant_3);
    Qspecific_attributes = STATIC_SYMBOL("SPECIFIC-ATTRIBUTES",AB_package);
    list_constant_4 = STATIC_CONS(Qsequence,Qnil);
    list_constant_5 = STATIC_CONS(list_constant_4,Qnil);
    list_constant_7 = STATIC_LIST_STAR((SI_Long)3L,Qspecific_attributes,
	    Ktype,list_constant_5);
    list_constant_8 = STATIC_LIST((SI_Long)2L,list_constant_6,list_constant_7);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_get_attribute_descriptions_of_class,
	    make_system_rpc_1(Qg2_get_attribute_descriptions_of_class_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_8,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,
	    Qg2_get_attribute_descriptions_of_class,System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_descriptions_of_class_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attribute_descriptions_of_class_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_attribute_values_of_item = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-VALUES-OF-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_attribute_values_of_item,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_values_of_item,
	    STATIC_FUNCTION(g2_get_attribute_values_of_item,NIL,FALSE,2,2));
    Qg2_get_attribute_values_of_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-VALUES-OF-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qitem,Ktype,list_constant_9);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qspecific_attributes,Ktype,
	    Qdatum);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_10,
	    list_constant_11);
    list_constant_12 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_14 = STATIC_CONS(list_constant_12,Qnil);
    mutate_global_property(Qg2_get_attribute_values_of_item,
	    make_system_rpc_1(Qg2_get_attribute_values_of_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_13,
	    Nil,T),list_constant_14),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,
	    Qg2_get_attribute_values_of_item,System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_values_of_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attribute_values_of_item_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_attribute_texts_of_item = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-TEXTS-OF-ITEM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_attribute_texts_of_item,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_texts_of_item,
	    STATIC_FUNCTION(g2_get_attribute_texts_of_item,NIL,FALSE,2,2));
    Qg2_get_attribute_texts_of_item_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTE-TEXTS-OF-ITEM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_get_attribute_texts_of_item,
	    make_system_rpc_1(Qg2_get_attribute_texts_of_item_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_13,
	    Nil,T),list_constant_14),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,
	    Qg2_get_attribute_texts_of_item,System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_get_attribute_texts_of_item_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attribute_texts_of_item_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_denoted_attribute_texts = 
	    STATIC_SYMBOL("G2-GET-DENOTED-ATTRIBUTE-TEXTS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_denoted_attribute_texts,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qclass_qualifier = STATIC_SYMBOL("CLASS-QUALIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_denoted_attribute_texts,
	    STATIC_FUNCTION(g2_get_denoted_attribute_texts,NIL,FALSE,2,2));
    Qg2_get_denoted_attribute_texts_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-DENOTED-ATTRIBUTE-TEXTS-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qdenoted_attributes_sequence = 
	    STATIC_SYMBOL("DENOTED-ATTRIBUTES-SEQUENCE",AB_package);
    list_constant_15 = STATIC_CONS(Ktype,list_constant_5);
    list_constant_16 = STATIC_CONS(Qdenoted_attributes_sequence,
	    list_constant_15);
    list_constant_17 = STATIC_LIST((SI_Long)2L,list_constant_10,
	    list_constant_16);
    mutate_global_property(Qg2_get_denoted_attribute_texts,
	    make_system_rpc_1(Qg2_get_denoted_attribute_texts_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_17,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,
	    Qg2_get_denoted_attribute_texts,System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_get_denoted_attribute_texts_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_denoted_attribute_texts_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_attributes_visible_in_mode = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTES-VISIBLE-IN-MODE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_attributes_visible_in_mode,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_8 = 
	    STATIC_STRING("The first argument to g2-get-attributes-visible-in-mode must be a symbol or an item.");
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qmiscellaneous_parameters = STATIC_SYMBOL("MISCELLANEOUS-PARAMETERS",
	    AB_package);
    Qshow_uuids_in_attribute_tables = 
	    STATIC_SYMBOL("SHOW-UUIDS-IN-ATTRIBUTE-TABLES",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_attributes_visible_in_mode,
	    STATIC_FUNCTION(g2_get_attributes_visible_in_mode,NIL,FALSE,2,2));
    Qg2_get_attributes_visible_in_mode_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTES-VISIBLE-IN-MODE-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qclass_or_item = STATIC_SYMBOL("CLASS-OR-ITEM",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qclass_or_item,Ktype,
	    Qitem_or_datum);
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    list_constant_18 = STATIC_CONS(Ktype,list_constant_3);
    list_constant_20 = STATIC_CONS(Quser_mode,list_constant_18);
    list_constant_21 = STATIC_LIST((SI_Long)2L,list_constant_19,
	    list_constant_20);
    mutate_global_property(Qg2_get_attributes_visible_in_mode,
	    make_system_rpc_1(Qg2_get_attributes_visible_in_mode_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_21,
	    Nil,T),list_constant_5),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,
	    Qg2_get_attributes_visible_in_mode,System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_get_attributes_visible_in_mode_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_attributes_visible_in_mode_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_get_filtered_attributes = 
	    STATIC_SYMBOL("G2-GET-FILTERED-ATTRIBUTES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_filtered_attributes,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_filtered_attributes,
	    STATIC_FUNCTION(g2_get_filtered_attributes,NIL,FALSE,2,2));
}
