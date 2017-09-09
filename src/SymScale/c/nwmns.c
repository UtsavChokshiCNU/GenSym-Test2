/* nwmns.c
 * Input file:  new-menus.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "nwmns.h"


Object Presentation_type_named_prop = UNBOUND;

static Object Qg2_defstruct_structure_name_presentation_type_g2_struct;  /* g2-defstruct-structure-name::presentation-type-g2-struct */

static Object Qpresentation_type_named;  /* presentation-type-named */

/* MAKE-PRESENTATION-TYPE */
Object make_presentation_type(name,menu_1,dialog,available_p,predicate,
	    blackboard,immediate_value,parameters)
    Object name, menu_1, dialog, available_p, predicate, blackboard;
    Object immediate_value, parameters;
{
    Object defstruct_g2_presentation_type_variable, the_array, ptype;
    SI_Long gensymed_symbol, i, ab_loop_bind_;

    x_note_fn_call(118,0);
    defstruct_g2_presentation_type_variable = Nil;
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
    defstruct_g2_presentation_type_variable = the_array;
    SVREF(defstruct_g2_presentation_type_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_presentation_type_g2_struct;
    ptype = defstruct_g2_presentation_type_variable;
    SVREF(ptype,FIX((SI_Long)1L)) = name;
    SVREF(ptype,FIX((SI_Long)2L)) = menu_1;
    SVREF(ptype,FIX((SI_Long)3L)) = dialog;
    SVREF(ptype,FIX((SI_Long)4L)) = available_p;
    SVREF(ptype,FIX((SI_Long)5L)) = predicate;
    SVREF(ptype,FIX((SI_Long)6L)) = blackboard;
    SVREF(ptype,FIX((SI_Long)8L)) = immediate_value;
    SVREF(ptype,FIX((SI_Long)7L)) = parameters;
    mutate_global_property(name,ptype,Qpresentation_type_named);
    return VALUES_1(ptype);
}

/* FIND-PRESENTATION-TYPE */
Object find_presentation_type varargs_1(int, n)
{
    Object presentation_type_or_name;
    Object warn_p, temp, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,1);
    INIT_ARGS_nonrelocating();
    presentation_type_or_name = REQUIRED_ARG_nonrelocating();
    warn_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(presentation_type_or_name) && 
	    EQ(ISVREF(presentation_type_or_name,(SI_Long)0L),
	    Qg2_defstruct_structure_name_presentation_type_g2_struct))
	return VALUES_1(presentation_type_or_name);
    else if (SYMBOLP(presentation_type_or_name))
	return getfq_function_no_default(INLINE_SYMBOL_PLIST(presentation_type_or_name),
		Qpresentation_type_named);
    else if (CONSP(presentation_type_or_name)) {
	temp = CAR(presentation_type_or_name);
	if (CONSP(temp)) {
	    gensymed_symbol = CAAR(presentation_type_or_name);
	    return getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qpresentation_type_named);
	}
	else {
	    gensymed_symbol = CAR(presentation_type_or_name);
	    return getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qpresentation_type_named);
	}
    }
    else if (warn_p)
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

/* PRESENTATION-TYPE-PARAMETERS */
Object presentation_type_parameters(presentation_type_or_name)
    Object presentation_type_or_name;
{
    Object temp;

    x_note_fn_call(118,2);
    if (ATOM(presentation_type_or_name))
	return VALUES_1(Nil);
    else {
	temp = CAR(presentation_type_or_name);
	if (ATOM(temp))
	    return VALUES_1(CDR(presentation_type_or_name));
	else {
	    temp = CAR(presentation_type_or_name);
	    return VALUES_1(CDR(temp));
	}
    }
}

/* PRESENTATION-TYPE-OPTIONS */
Object presentation_type_options(presentation_type_or_name)
    Object presentation_type_or_name;
{
    Object temp;

    x_note_fn_call(118,3);
    if (ATOM(presentation_type_or_name))
	return VALUES_1(Nil);
    else {
	temp = CAR(presentation_type_or_name);
	if (ATOM(temp))
	    return VALUES_1(Nil);
	else
	    return VALUES_1(CDR(presentation_type_or_name));
    }
}

/* PARSE-PRESENTATION-TYPE */
Object parse_presentation_type(presentation_type_or_name)
    Object presentation_type_or_name;
{
    Object ptype_qm, parameters, options;

    x_note_fn_call(118,4);
    ptype_qm = find_presentation_type(2,presentation_type_or_name,T);
    parameters = presentation_type_parameters(presentation_type_or_name);
    options = presentation_type_options(presentation_type_or_name);
    return VALUES_3(ptype_qm,parameters,options);
}

/* PRESENTATION-TYPE-ADMITS-MENU-P */
Object presentation_type_admits_menu_p(ptype)
    Object ptype;
{
    Object ptype_qm;

    x_note_fn_call(118,5);
    ptype_qm = find_presentation_type(1,ptype);
    if (ptype_qm)
	return VALUES_1(ISVREF(ptype_qm,(SI_Long)2L));
    else
	return VALUES_1(Nil);
}

/* PRESENTATION-TYPE-ADMITS-DIALOG-P */
Object presentation_type_admits_dialog_p(ptype)
    Object ptype;
{
    Object ptype_qm;

    x_note_fn_call(118,6);
    ptype_qm = find_presentation_type(1,ptype);
    if (ptype_qm)
	return VALUES_1(ISVREF(ptype_qm,(SI_Long)3L));
    else
	return VALUES_1(Nil);
}

Object Magic_argument_fetcher_prop = UNBOUND;

static Object Qmagic_argument_fetcher;  /* magic-argument-fetcher */

/* BLACKBOARD-ARGUMENT-OF-MOUSE-POINTER */
Object blackboard_argument_of_mouse_pointer(mouse_pointer,magic_argument_name)
    Object mouse_pointer, magic_argument_name;
{
    Object temp;

    x_note_fn_call(118,7);
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(magic_argument_name),
	    Qmagic_argument_fetcher)) {
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(magic_argument_name),
		Qmagic_argument_fetcher);
	return FUNCALL_1(temp,mouse_pointer);
    }
    else
	return VALUES_1(Nil);
}

/* BLACKBOARD-ARGUMENT-TYPE-P */
Object blackboard_argument_type_p(type)
    Object type;
{
    Object ptype_qm;

    x_note_fn_call(118,8);
    ptype_qm = find_presentation_type(1,type);
    if (ptype_qm)
	return VALUES_1(ISVREF(ptype_qm,(SI_Long)6L));
    else if (SYMBOLP(type))
	return lookup_global_or_kb_specific_property_value(type,
		Class_description_gkbprop);
    else
	return VALUES_1(Qnil);
}

/* GET-MAGIC-ARGUMENT */
Object get_magic_argument(type,mouse_pointer)
    Object type, mouse_pointer;
{
    Object fetcher_qm, gensymed_symbol, temp;

    x_note_fn_call(118,9);
    fetcher_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
	    Qmagic_argument_fetcher);
    if (fetcher_qm) {
	gensymed_symbol = fetcher_qm;
	temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) 
		: gensymed_symbol;
	return FUNCALL_1(temp,mouse_pointer);
    }
    else if (lookup_global_or_kb_specific_property_value(type,
	    Class_description_gkbprop))
	return find_frame_of_class_in_mouse_pointer(mouse_pointer,type);
    else
	return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct;  /* g2-defstruct-structure-name::entire-g2-window-spot-g2-struct */

/* FIND-FRAME-OF-CLASS-IN-MOUSE-POINTER */
Object find_frame_of_class_in_mouse_pointer(mouse_pointer,class_1)
    Object mouse_pointer, class_1;
{
    Object spot, frame, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(118,10);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(frame);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object New_style_event_handler_prop = UNBOUND;

Object Event_handler_pretty_name_qm_prop = UNBOUND;

static Object Qevent_handler_pretty_name_qm;  /* event-handler-pretty-name? */

/* EVENT-HANDLER-PRETTY-NAME */
Object event_handler_pretty_name(event_handler_name)
    Object event_handler_name;
{
    Object temp;

    x_note_fn_call(118,11);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(event_handler_name),
	    Qevent_handler_pretty_name_qm);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(event_handler_name);
}

Object Event_handler_condition_prop = UNBOUND;

Object Keymap_named_prop = UNBOUND;

static Object Qg2_defstruct_structure_name_keymap_g2_struct;  /* g2-defstruct-structure-name::keymap-g2-struct */

static Object Qinternal;           /* internal */

static Object Qkeymap_named;       /* keymap-named */

/* MAKE-KEYMAP */
Object make_keymap(name,pretty_name,bindings,namespace,condition,filter,
	    lookup_method,describe_method)
    Object name, pretty_name, bindings, namespace, condition, filter;
    Object lookup_method, describe_method;
{
    Object defstruct_g2_keymap_variable, the_array, keymap, svref_new_value;
    Object key_pattern, class_1, handler, options, ab_loop_list_;
    Object ab_loop_desetq_, temp;
    SI_Long gensymed_symbol, i, ab_loop_bind_;

    x_note_fn_call(118,12);
    defstruct_g2_keymap_variable = Nil;
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
    defstruct_g2_keymap_variable = the_array;
    SVREF(defstruct_g2_keymap_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_keymap_g2_struct;
    keymap = defstruct_g2_keymap_variable;
    SVREF(keymap,FIX((SI_Long)1L)) = name;
    SVREF(keymap,FIX((SI_Long)2L)) = pretty_name;
    svref_new_value = namespace;
    if (svref_new_value);
    else
	svref_new_value = Qinternal;
    SVREF(keymap,FIX((SI_Long)4L)) = svref_new_value;
    SVREF(keymap,FIX((SI_Long)5L)) = condition;
    SVREF(keymap,FIX((SI_Long)6L)) = filter;
    SVREF(keymap,FIX((SI_Long)7L)) = lookup_method;
    SVREF(keymap,FIX((SI_Long)8L)) = describe_method;
    key_pattern = Nil;
    class_1 = Nil;
    handler = Nil;
    options = Nil;
    ab_loop_list_ = bindings;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key_pattern = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    class_1 = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    handler = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    options = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    bind_key_in_keymap(keymap,key_pattern,class_1,handler,options);
    goto next_loop_1;
  end_loop_1:;
    mutate_global_property(name,keymap,Qkeymap_named);
    return VALUES_1(keymap);
}

/* KEYMAP-ENABLED-P */
Object keymap_enabled_p(keymap)
    Object keymap;
{
    Object temp, gensymed_symbol;

    x_note_fn_call(118,13);
    temp =  !TRUEP(ISVREF(keymap,(SI_Long)5L)) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	gensymed_symbol = ISVREF(keymap,(SI_Long)5L);
	return FUNCALL_0(SYMBOLP(gensymed_symbol) ? 
		SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol);
    }
}

/* KEYMAP-PRIVATE-P */
Object keymap_private_p(keymap)
    Object keymap;
{
    x_note_fn_call(118,14);
    return VALUES_1( !TRUEP(ISVREF(keymap,(SI_Long)2L)) ? T : Nil);
}

/* BIND-KEY-IN-KEYMAP */
Object bind_key_in_keymap(keymap,key_pattern,class_1,handler_qm,options)
    Object keymap, key_pattern, class_1, handler_qm, options;
{
    Object buckets, bucket_qm, sublist, class_1_1, handler, options_1, temp;
    Object place_qm, old_entry_qm, new_entry, previous_cons, temp_1;

    x_note_fn_call(118,15);
    buckets = ISVREF(keymap,(SI_Long)3L);
    bucket_qm = ab_assoc_equal(key_pattern,ISVREF(keymap,(SI_Long)3L));
    if (bucket_qm) {
	sublist = CDR(bucket_qm);
	class_1_1 = Nil;
	handler = Nil;
	options_1 = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	temp = CAR(sublist);
	class_1_1 = CAR(temp);
	temp = CAR(sublist);
	temp = CDR(temp);
	handler = CAR(temp);
	temp = CAR(sublist);
	temp = CDR(temp);
	options_1 = CDR(temp);
	if (EQ(class_1,class_1_1)) {
	    place_qm = sublist;
	    goto end_1;
	}
	sublist = M_CDR(sublist);
	goto next_loop;
      end_loop:
	place_qm = Qnil;
      end_1:;
    }
    else
	place_qm = Nil;
    old_entry_qm = CAR(place_qm);
    if ( !TRUEP(handler_qm)) {
	if (old_entry_qm)
	    M_SECOND(old_entry_qm) = Nil;
    }
    else if (old_entry_qm) {
	M_SECOND(old_entry_qm) = handler_qm;
	M_CDDR(old_entry_qm) = options;
    }
    else if (bucket_qm) {
	new_entry = list_star(3,class_1,handler_qm,options);
	previous_cons = bucket_qm;
	sublist = CDR(bucket_qm);
	class_1_1 = Nil;
	handler = Nil;
	options = Nil;
      next_loop_1:
	if ( !TRUEP(sublist))
	    goto end_loop_1;
	temp = CAR(sublist);
	class_1_1 = CAR(temp);
	temp = CAR(sublist);
	temp = CDR(temp);
	handler = CAR(temp);
	temp = CAR(sublist);
	temp = CDR(temp);
	options = CDR(temp);
	if (ab_subtypep(class_1,class_1_1)) {
	    temp_1 = CONS(new_entry,sublist);
	    M_CDR(previous_cons) = temp_1;
	    goto end_2;
	}
	previous_cons = CDR(sublist);
	sublist = M_CDR(sublist);
	goto next_loop_1;
      end_loop_1:
	bucket_qm = nconc2(bucket_qm,LIST_1(new_entry));
      end_2:;
    }
    else {
	temp = CONS(handler_qm,options);
	temp = CONS(class_1,temp);
	temp = CONS(temp,Nil);
	bucket_qm = CONS(key_pattern,temp);
	temp_1 = nconc2(buckets,LIST_1(bucket_qm));
	SVREF(keymap,FIX((SI_Long)3L)) = temp_1;
    }
    if ( !TRUEP(bucket_qm) ||  !TRUEP(CDR(bucket_qm))) {
	temp_1 = lremove(2,bucket_qm,ISVREF(keymap,(SI_Long)3L));
	SVREF(keymap,FIX((SI_Long)3L)) = temp_1;
    }
    return VALUES_1(keymap);
}

/* STRUCTURE-CLASS */
Object structure_class(structure)
    Object structure;
{
    x_note_fn_call(118,16);
    return VALUES_1(ISVREF(type_description_of(structure),(SI_Long)1L));
}

Object Spot_class_set_prop = UNBOUND;

/* FIND-FRAME-IN-SPOT */
Object find_frame_in_spot(leaf_spot)
    Object leaf_spot;
{
    Object spot, ab_loop_it_;

    x_note_fn_call(118,17);
    spot = leaf_spot;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    ab_loop_it_ = ISVREF(spot,(SI_Long)4L);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qexact;              /* exact */

static Object Qspot_class_set;     /* spot-class-set */

/* LOOKUP-KEY-IN-BUCKET */
Object lookup_key_in_bucket(bucket,spot)
    Object bucket, spot;
{
    Object class_1, handler, options, ab_loop_list_, ab_loop_desetq_, temp;
    Object frame_qm, spot_1, spot_class, frame, spot_class_set, ab_loop_it_;

    x_note_fn_call(118,18);
    class_1 = Nil;
    handler = Nil;
    options = Nil;
    ab_loop_list_ = CDR(bucket);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    handler = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    options = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(class_1,T))
	temp = T;
    else if (memq_function(Qexact,options)) {
	frame_qm = find_frame_in_spot(spot);
	temp = class_1;
	temp = EQ(temp,structure_class(spot)) ? T : Nil;
	if (temp);
	else
	    temp = frame_qm ? (EQ(class_1,ISVREF(ISVREF(frame_qm,
		    (SI_Long)1L),(SI_Long)1L)) ? T : Nil) : Qnil;
    }
    else {
	spot_1 = spot;
	spot_class = Nil;
	frame = Nil;
	spot_class_set = Nil;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(spot_1))
	    goto end_loop_1;
	spot_class = structure_class(spot_1);
	frame = ISVREF(spot_1,(SI_Long)4L);
	spot_class_set = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
		Qspot_class_set);
	temp = memq_function(spot_class,spot_class_set);
	if (temp);
	else
	    temp = ab_typep_function(spot_1,class_1);
	if (temp);
	else
	    temp = frame ? ab_typep_function(frame,class_1) : Qnil;
	ab_loop_it_ = temp;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	spot_1 = ISVREF(spot_1,(SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
    }
    if (temp)
	return VALUES_1(handler);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qkey_pattern_named;  /* key-pattern-named */

static Object Qab_or;              /* or */

/* LOOKUP-KEY-IN-KEYMAP */
Object lookup_key_in_keymap(keymap,keycode,spot)
    Object keymap, keycode, spot;
{
    Object gensymed_symbol, temp, bucket, ab_loop_list_, key_pattern;
    Object gensymed_symbol_1, disjunct, ab_loop_list__1, ab_loop_it_;
    Object handler_qm, filter_qm;
    char temp_1;

    x_note_fn_call(118,19);
    if (ISVREF(keymap,(SI_Long)7L)) {
	gensymed_symbol = ISVREF(keymap,(SI_Long)7L);
	temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) 
		: gensymed_symbol;
	return FUNCALL_3(temp,keymap,keycode,spot);
    }
    else {
	bucket = Nil;
	ab_loop_list_ = ISVREF(keymap,(SI_Long)3L);
	key_pattern = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	bucket = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	key_pattern = FIRST(bucket);
	if (FIXNUMP(key_pattern))
	    temp = FIXNUM_EQ(key_pattern,keycode) ? T : Nil;
	else if (SYMBOLP(key_pattern)) {
	    gensymed_symbol = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(key_pattern),
		    Qkey_pattern_named);
	    gensymed_symbol_1 = keycode;
	    temp = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	}
	else if (CONSP(key_pattern) && FIXNUMP(CAR(key_pattern)))
	    temp = FIXNUM_EQ(FIXNUM_LOGAND(keycode,CDR(key_pattern)),
		    CAR(key_pattern)) ? T : Nil;
	else if (CONSP(key_pattern) && EQ(FIRST(key_pattern),Qab_or)) {
	    disjunct = Nil;
	    ab_loop_list__1 = REST(key_pattern);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    disjunct = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = key_code_matches_key_pattern_p_function(keycode,
		    disjunct);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Qnil;
	if (temp) {
	    handler_qm = lookup_key_in_bucket(bucket,spot);
	    filter_qm = ISVREF(keymap,(SI_Long)6L);
	    if (handler_qm) {
		temp_1 =  !TRUEP(filter_qm);
		if (temp_1);
		else {
		    gensymed_symbol = filter_qm;
		    temp = SYMBOLP(gensymed_symbol) ? 
			    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
		    temp_1 = TRUEP(FUNCALL_2(temp,keymap,handler_qm));
		}
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return make_event_interpretation(ISVREF(keymap,
			(SI_Long)4L),handler_qm,Nil);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object Qkey_pattern_abbreviation;  /* key-pattern-abbreviation */

/* LOOKUP-COMMAND-IN-KEYMAP */
Object lookup_command_in_keymap(keymap,command_name)
    Object keymap, command_name;
{
    Object bucket, ab_loop_list_, key_pattern, abbrev_qm, alternate_key_qm;
    Object key_code, temp, unicode, gensymed_symbol, class_1, handler;
    Object ab_loop_list__1, ab_loop_desetq_;
    SI_Long arg, arg_1, arg_2;
    char temp_1;

    x_note_fn_call(118,20);
    bucket = Nil;
    ab_loop_list_ = ISVREF(keymap,(SI_Long)3L);
    key_pattern = Nil;
    abbrev_qm = Nil;
    alternate_key_qm = Nil;
    key_code = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    bucket = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    key_pattern = FIRST(bucket);
    abbrev_qm = SYMBOLP(key_pattern) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(key_pattern),
	    Qkey_pattern_abbreviation) : Qnil;
    alternate_key_qm = abbrev_qm && CONSP(abbrev_qm) && EQ(CAR(abbrev_qm),
	    Qab_or) ? CADR(abbrev_qm) : Qnil;
    temp = alternate_key_qm;
    if (temp);
    else
	temp = key_pattern;
    key_code = temp;
    if (FIXNUMP(key_code)) {
	arg = (SI_Long)769L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)779L;
	temp_1 = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	if (temp_1);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp_1 = IFIX(gensymed_symbol) == (SI_Long)779L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)812L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)813L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)814L;
	}
	if (temp_1);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp_1 = IFIX(gensymed_symbol) == (SI_Long)778L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)815L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)816L;
	    if (temp_1);
	    else
		temp_1 = IFIX(gensymed_symbol) == (SI_Long)817L;
	}
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	class_1 = Nil;
	handler = Nil;
	ab_loop_list__1 = CDR(bucket);
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	class_1 = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	handler = CAR(temp);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(handler,command_name))
	    return VALUES_1(key_code);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant;     /* "~a" */

/* DESCRIBE-KEYMAP */
Object describe_keymap(keymap,frame_qm)
    Object keymap, frame_qm;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(118,21);
    if (ISVREF(keymap,(SI_Long)8L)) {
	gensymed_symbol = ISVREF(keymap,(SI_Long)8L);
	temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) 
		: gensymed_symbol;
	return FUNCALL_2(temp,keymap,frame_qm);
    }
    else {
	temp = tformat_text_string(2,string_constant,ISVREF(keymap,
		(SI_Long)2L));
	return describe_keymap_into_table_rows(temp,ISVREF(keymap,
		(SI_Long)3L));
    }
}

Object Ui_command_named_prop = UNBOUND;

Object Ui_commands_with_menu_name_prop = UNBOUND;

Object Ui_command_command_posts_dialog_p_prop = UNBOUND;

Object Plus_missing_argument_plus = UNBOUND;

Object Plus_abort_menu_choice_plus = UNBOUND;

Object List_of_all_ui_commands = UNBOUND;

static Object Qg2_defstruct_structure_name_ui_command_g2_struct;  /* g2-defstruct-structure-name::ui-command-g2-struct */

static Object Qui_command_named;   /* ui-command-named */

/* FIND-UI-COMMAND */
Object find_ui_command varargs_1(int, n)
{
    Object command_or_name;
    Object warn_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,22);
    INIT_ARGS_nonrelocating();
    command_or_name = REQUIRED_ARG_nonrelocating();
    warn_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    temp = SIMPLE_VECTOR_P(command_or_name) && EQ(ISVREF(command_or_name,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_ui_command_g2_struct) ? 
	    command_or_name : Nil;
    if (temp);
    else
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(command_or_name),
		Qui_command_named);
    if (temp)
	return VALUES_1(temp);
    else if (warn_p)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* GENERIC-NAME-OF-EXPORTED-UI-COMMAND? */
Object generic_name_of_exported_ui_command_qm(name)
    Object name;
{
    x_note_fn_call(118,23);
    return built_in_menu_choice_p(1,name);
}

static Object Qui_commands_with_menu_name;  /* ui-commands-with-menu-name */

/* MAKE-UI-COMMAND */
Object make_ui_command varargs_1(int, n)
{
    Object name, lambda_list;
    Object documentation, menu_name, id, defstruct_g2_ui_command_variable;
    Object the_array, cmd, svref_new_value, sublist, key, temp;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,24);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    lambda_list = REQUIRED_ARG_nonrelocating();
    documentation = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    menu_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : name;
    id = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    defstruct_g2_ui_command_variable = Nil;
    gensymed_symbol = (SI_Long)11L;
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
    defstruct_g2_ui_command_variable = the_array;
    SVREF(defstruct_g2_ui_command_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_ui_command_g2_struct;
    cmd = defstruct_g2_ui_command_variable;
    SVREF(cmd,FIX((SI_Long)1L)) = name;
    SVREF(cmd,FIX((SI_Long)8L)) = lambda_list;
    SVREF(cmd,FIX((SI_Long)7L)) = documentation;
    svref_new_value = menu_name;
    if (svref_new_value);
    else
	svref_new_value = name;
    SVREF(cmd,FIX((SI_Long)2L)) = svref_new_value;
    SVREF(cmd,FIX((SI_Long)9L)) = id;
    sublist = List_of_all_ui_commands;
    key = Nil;
  next_loop_1:
    if ( !TRUEP(sublist))
	goto end_loop_1;
    key = ISVREF(CAR(sublist),(SI_Long)1L);
    if (EQ(key,ISVREF(cmd,(SI_Long)1L))) {
	M_CAR(sublist) = cmd;
	goto end_1;
    }
    sublist = M_CDR(sublist);
    goto next_loop_1;
  end_loop_1:
    List_of_all_ui_commands = CONS(cmd,List_of_all_ui_commands);
  end_1:;
    sublist = getfq_function_no_default(INLINE_SYMBOL_PLIST(menu_name),
	    Qui_commands_with_menu_name);
    key = Nil;
  next_loop_2:
    if ( !TRUEP(sublist))
	goto end_loop_2;
    key = ISVREF(CAR(sublist),(SI_Long)1L);
    if (EQ(key,ISVREF(cmd,(SI_Long)1L))) {
	M_CAR(sublist) = cmd;
	goto end_2;
    }
    sublist = M_CDR(sublist);
    goto next_loop_2;
  end_loop_2:
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(menu_name),
	    Qui_commands_with_menu_name);
    mutate_global_property(menu_name,CONS(cmd,temp),
	    Qui_commands_with_menu_name);
  end_2:;
    mutate_global_property(name,cmd,Qui_command_named);
    return VALUES_1(cmd);
}

/* EMPTY-COMMAND-PURSUER */
Object empty_command_pursuer(partial_command)
    Object partial_command;
{
    x_note_fn_call(118,25);
    return VALUES_1(Nil);
}

/* GET-UI-COMMAND-FUNCTION */
Object get_ui_command_function(command_name)
    Object command_name;
{
    x_note_fn_call(118,26);
    return VALUES_1(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named),(SI_Long)4L));
}

/* GET-UI-COMMAND-LABELER */
Object get_ui_command_labeler(command_name)
    Object command_name;
{
    x_note_fn_call(118,27);
    return VALUES_1(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named),(SI_Long)10L));
}

/* GET-UI-COMMAND-TRANSLATOR */
Object get_ui_command_translator(command_name)
    Object command_name;
{
    x_note_fn_call(118,28);
    return VALUES_1(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named),(SI_Long)5L));
}

/* GET-UI-COMMAND-PURSUER */
Object get_ui_command_pursuer(command_name)
    Object command_name;
{
    x_note_fn_call(118,29);
    return VALUES_1(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named),(SI_Long)6L));
}

/* SET-UI-COMMAND-FUNCTION */
Object set_ui_command_function(command_name,function)
    Object command_name, function;
{
    Object svref_arg_1;

    x_note_fn_call(118,30);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)4L)) = function);
}

/* SET-UI-COMMAND-LABELER */
Object set_ui_command_labeler(command_name,function)
    Object command_name, function;
{
    Object svref_arg_1;

    x_note_fn_call(118,31);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)10L)) = function);
}

/* SET-UI-COMMAND-TRANSLATOR */
Object set_ui_command_translator(command_name,function)
    Object command_name, function;
{
    Object svref_arg_1;

    x_note_fn_call(118,32);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)5L)) = function);
}

/* SET-UI-COMMAND-PURSUER */
Object set_ui_command_pursuer(command_name,function)
    Object command_name, function;
{
    Object svref_arg_1;

    x_note_fn_call(118,33);
    svref_arg_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)6L)) = function);
}

/* LAMBDA-LIST-OF-UI-COMMAND-NAMED */
Object lambda_list_of_ui_command_named varargs_1(int, n)
{
    Object user_menu_choice_symbol_qm;
    Object default_1, command_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,34);
    INIT_ARGS_nonrelocating();
    user_menu_choice_symbol_qm = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    command_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(user_menu_choice_symbol_qm),
	    Qui_command_named);
    if (command_qm)
	return VALUES_1(ISVREF(command_qm,(SI_Long)8L));
    else
	return VALUES_1(default_1);
}

Object The_type_description_of_partial_command = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_partial_commands, Qchain_of_available_partial_commands);

DEFINE_VARIABLE_WITH_SYMBOL(Partial_command_count, Qpartial_command_count);

Object Chain_of_available_partial_commands_vector = UNBOUND;

/* PARTIAL-COMMAND-STRUCTURE-MEMORY-USAGE */
Object partial_command_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(118,35);
    temp = Partial_command_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PARTIAL-COMMAND-COUNT */
Object outstanding_partial_command_count()
{
    Object def_structure_partial_command_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(118,36);
    gensymed_symbol = IFIX(Partial_command_count);
    def_structure_partial_command_variable = 
	    Chain_of_available_partial_commands;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_partial_command_variable))
	goto end_loop;
    def_structure_partial_command_variable = 
	    ISVREF(def_structure_partial_command_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PARTIAL-COMMAND-1-1 */
Object reclaim_partial_command_1_1(partial_command)
    Object partial_command;
{
    Object temp, svref_arg_2;

    x_note_fn_call(118,37);
    inline_note_reclaim_cons(partial_command,Nil);
    temp = ISVREF(Chain_of_available_partial_commands_vector,
	    IFIX(Current_thread_index));
    SVREF(partial_command,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_partial_commands_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = partial_command;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PARTIAL-COMMAND */
Object reclaim_structure_for_partial_command(partial_command)
    Object partial_command;
{
    x_note_fn_call(118,38);
    return reclaim_partial_command_1_1(partial_command);
}

static Object Qg2_defstruct_structure_name_partial_command_g2_struct;  /* g2-defstruct-structure-name::partial-command-g2-struct */

/* MAKE-PERMANENT-PARTIAL-COMMAND-STRUCTURE-INTERNAL */
Object make_permanent_partial_command_structure_internal()
{
    Object def_structure_partial_command_variable;
    Object defstruct_g2_partial_command_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(118,39);
    def_structure_partial_command_variable = Nil;
    atomic_incff_symval(Qpartial_command_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_partial_command_variable = Nil;
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
	defstruct_g2_partial_command_variable = the_array;
	SVREF(defstruct_g2_partial_command_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_partial_command_g2_struct;
	def_structure_partial_command_variable = 
		defstruct_g2_partial_command_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_partial_command_variable);
}

/* MAKE-PARTIAL-COMMAND-1-1 */
Object make_partial_command_1_1()
{
    Object def_structure_partial_command_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(118,40);
    def_structure_partial_command_variable = 
	    ISVREF(Chain_of_available_partial_commands_vector,
	    IFIX(Current_thread_index));
    if (def_structure_partial_command_variable) {
	svref_arg_1 = Chain_of_available_partial_commands_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_partial_command_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_partial_command_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_partial_command_g2_struct;
    }
    else
	def_structure_partial_command_variable = 
		make_permanent_partial_command_structure_internal();
    inline_note_allocate_cons(def_structure_partial_command_variable,Nil);
    return VALUES_1(def_structure_partial_command_variable);
}

/* PARTIAL-COMMAND-P-FUNCTION */
Object partial_command_p_function(thing)
    Object thing;
{
    x_note_fn_call(118,41);
    if (SIMPLE_VECTOR_P(thing))
	return VALUES_1(EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_partial_command_g2_struct) ? 
		T : Nil);
    else
	return VALUES_1(Nil);
}

/* MAKE-PARTIAL-COMMAND */
Object make_partial_command(command_name,command_arguments)
    Object command_name, command_arguments;
{
    Object pc;

    x_note_fn_call(118,42);
    pc = make_partial_command_1_1();
    SVREF(pc,FIX((SI_Long)1L)) = command_name;
    SVREF(pc,FIX((SI_Long)2L)) = command_arguments;
    return VALUES_1(pc);
}

/* RECLAIM-PARTIAL-COMMAND */
Object reclaim_partial_command(partial_command)
    Object partial_command;
{
    Object arguments, argument, ab_loop_list_;

    x_note_fn_call(118,43);
    arguments = ISVREF(partial_command,(SI_Long)2L);
    argument = Nil;
    ab_loop_list_ = arguments;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_partial_command_argument(argument);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(arguments);
    return reclaim_partial_command_1_1(partial_command);
}

static Object Qg2_defstruct_structure_name_snapshot_of_block_g2_struct;  /* g2-defstruct-structure-name::snapshot-of-block-g2-struct */

/* COPY-PARTIAL-COMMAND */
Object copy_partial_command(partial_command)
    Object partial_command;
{
    Object name, arguments, sublist, argument, first_new_value;

    x_note_fn_call(118,44);
    name = ISVREF(partial_command,(SI_Long)1L);
    arguments = copy_list_using_slot_value_conses_1(ISVREF(partial_command,
	    (SI_Long)2L));
    sublist = arguments;
    argument = Nil;
  next_loop:
    if ( !TRUEP(sublist))
	goto end_loop;
    argument = FIRST(sublist);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct)) {
	first_new_value = copy_snapshot_of_block(argument);
	M_FIRST(sublist) = first_new_value;
    }
    sublist = M_CDR(sublist);
    goto next_loop;
  end_loop:;
    return make_partial_command(name,arguments);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* SNAPSHOT-COMMAND-ARGUMENT */
Object snapshot_command_argument(value)
    Object value;
{
    Object x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,45);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(value,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	return make_snapshot_of_block(value);
    else
	return VALUES_1(value);
}

/* COMMAND-ARGUMENT-VALUE */
Object command_argument_value(argument)
    Object argument;
{
    x_note_fn_call(118,46);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct)) {
	snapshot_of_block_valid_p(argument);
	return VALUES_1(ISVREF(argument,(SI_Long)1L));
    }
    else
	return VALUES_1(argument);
}

/* COMMAND-ARGUMENT-VALID-P */
Object command_argument_valid_p(argument)
    Object argument;
{
    x_note_fn_call(118,47);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct))
	return snapshot_of_block_valid_p(argument);
    else
	return VALUES_1(T);
}

/* RECLAIM-PARTIAL-COMMAND-ARGUMENT */
Object reclaim_partial_command_argument(argument)
    Object argument;
{
    x_note_fn_call(118,48);
    if (SIMPLE_VECTOR_P(argument) && EQ(ISVREF(argument,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct))
	return reclaim_snapshot_of_block_1(argument);
    else
	return VALUES_1(Nil);
}

/* PARTIAL-COMMAND-VALID-P */
Object partial_command_valid_p(partial_command)
    Object partial_command;
{
    Object argument, ab_loop_list_;

    x_note_fn_call(118,49);
    argument = Nil;
    ab_loop_list_ = ISVREF(partial_command,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(command_argument_valid_p(argument)))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* MAKE-INITIAL-PARTIAL-COMMAND */
Object make_initial_partial_command(command_or_partial_command,mouse_pointer)
    Object command_or_partial_command, mouse_pointer;
{
    Object command_qm, gensymed_symbol, temp, partial_command_qm;

    x_note_fn_call(118,50);
    if ( !TRUEP(command_or_partial_command))
	return VALUES_1(Nil);
    else if (SIMPLE_VECTOR_P(command_or_partial_command) && 
	    EQ(ISVREF(command_or_partial_command,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	return copy_partial_command(command_or_partial_command);
    else {
	command_qm = find_ui_command(2,command_or_partial_command,T);
	if (command_qm) {
	    gensymed_symbol = ISVREF(command_qm,(SI_Long)5L);
	    temp = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    partial_command_qm = FUNCALL_1(temp,mouse_pointer);
	}
	else
	    partial_command_qm = Nil;
	if (partial_command_qm) {
	    fill_in_immediate_arguments(partial_command_qm);
	    return VALUES_1(partial_command_qm);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* FILL-IN-MOUSE-POINTER-ARGUMENTS */
Object fill_in_mouse_pointer_arguments(partial_command,mouse_pointer)
    Object partial_command, mouse_pointer;
{
    x_note_fn_call(118,51);
  next_loop:
    if ( !TRUEP(fill_in_next_mouse_pointer_argument(partial_command,
	    mouse_pointer)))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-IN-NEXT-MOUSE-POINTER-ARGUMENT */
Object fill_in_next_mouse_pointer_argument(partial_command,mouse_pointer)
    Object partial_command, mouse_pointer;
{
    Object temp, type_qm, place, value_qm;
    Object result;

    x_note_fn_call(118,52);
    result = partial_command_next_argument(partial_command);
    MVS_3(result,temp,type_qm,place);
    if (blackboard_argument_type_p(type_qm)) {
	value_qm = get_magic_argument(type_qm,mouse_pointer);
	if (value_qm) {
	    bind_partial_command_argument(partial_command,place,
		    snapshot_command_argument(value_qm));
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* FILL-IN-IMMEDIATE-ARGUMENTS */
Object fill_in_immediate_arguments(partial_command)
    Object partial_command;
{
    x_note_fn_call(118,53);
  next_loop:
    if ( !TRUEP(fill_in_next_immediate_argument(partial_command)))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FILL-IN-NEXT-IMMEDIATE-ARGUMENT */
Object fill_in_next_immediate_argument(partial_command)
    Object partial_command;
{
    Object temp, type_qm, place, ptype, parameters, value_qm;
    Object result;

    x_note_fn_call(118,54);
    result = partial_command_next_argument(partial_command);
    MVS_3(result,temp,type_qm,place);
    if (type_qm) {
	result = parse_presentation_type(type_qm);
	MVS_2(result,ptype,parameters);
	if (ptype) {
	    if (ISVREF(ptype,(SI_Long)8L)) {
		temp = ISVREF(ptype,(SI_Long)8L);
		value_qm = APPLY_1(temp,parameters);
		if (value_qm) {
		    bind_partial_command_argument(partial_command,place,
			    value_qm);
		    temp = value_qm;
		}
		else
		    temp = Nil;
	    }
	    else
		temp = Nil;
	    reclaim_presentation_type(type_qm);
	    return VALUES_1(temp);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PARTIAL-COMMAND-COMMAND */
Object partial_command_command(partial_command)
    Object partial_command;
{
    x_note_fn_call(118,55);
    return find_ui_command(1,ISVREF(partial_command,(SI_Long)1L));
}

/* PARTIAL-COMMAND-NEXT-ARGUMENT */
Object partial_command_next_argument(partial_command)
    Object partial_command;
{
    Object command, gensymed_symbol, temp;

    x_note_fn_call(118,56);
    command = partial_command_command(partial_command);
    gensymed_symbol = ISVREF(command,(SI_Long)6L);
    temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) : 
	    gensymed_symbol;
    return FUNCALL_1(temp,partial_command);
}

/* MAKE-EMPTY-PARTIAL-COMMAND */
Object make_empty_partial_command(command_or_command_name)
    Object command_or_command_name;
{
    Object command_qm, argument, ab_loop_list_, number_of_arguments, arguments;
    Object place, car_new_value;
    SI_Long ab_loopvar_;

    x_note_fn_call(118,57);
    command_qm = find_ui_command(1,command_or_command_name);
    if (command_qm) {
	argument = Nil;
	ab_loop_list_ = ISVREF(command_qm,(SI_Long)8L);
	ab_loopvar_ = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(memq_function(argument,Lambda_list_keywords)))
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	goto next_loop;
      end_loop:
	number_of_arguments = FIX(ab_loopvar_);
	goto end_1;
	number_of_arguments = Qnil;
      end_1:;
	arguments = make_slot_value_list_1(number_of_arguments);
	place = arguments;
      next_loop_1:
	if ( !TRUEP(place))
	    goto end_loop_1;
	car_new_value = Plus_missing_argument_plus;
	M_CAR(place) = car_new_value;
	place = M_CDR(place);
	goto next_loop_1;
      end_loop_1:;
	return make_partial_command(ISVREF(command_qm,(SI_Long)1L),arguments);
    }
    else
	return VALUES_1(Nil);
}

/* COMMAND-OR-PARTIAL-COMMAND-NEXT-ARGUMENT-TYPE */
Object command_or_partial_command_next_argument_type(command_or_partial_command)
    Object command_or_partial_command;
{
    Object partial_command_qm, argument_type;
    Object result;

    x_note_fn_call(118,58);
    partial_command_qm = SYMBOLP(command_or_partial_command) ? 
	    make_empty_partial_command(command_or_partial_command) : 
	    command_or_partial_command;
    if (partial_command_qm) {
	result = partial_command_next_argument(partial_command_qm);
	argument_type = NTH_VALUE((SI_Long)1L, result);
	if (SYMBOLP(command_or_partial_command))
	    reclaim_partial_command(partial_command_qm);
	return VALUES_1(argument_type);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PRESENTATION-TYPE */
Object reclaim_presentation_type(presentation_type)
    Object presentation_type;
{
    Object temp;

    x_note_fn_call(118,59);
    if (CONSP(presentation_type)) {
	temp = CAR(presentation_type);
	if (CONSP(temp))
	    reclaim_slot_value_list_1(CAR(presentation_type));
	return reclaim_slot_value_list_1(presentation_type);
    }
    else
	return VALUES_1(Nil);
}

/* PRESENTATION-TYPE-WANTS-MENU */
Object presentation_type_wants_menu(ptype_qm)
    Object ptype_qm;
{
    Object ptype, arguments, temp;
    Object result;

    x_note_fn_call(118,60);
    if (ptype_qm) {
	result = parse_presentation_type(ptype_qm);
	MVS_2(result,ptype,arguments);
	presentation_type_admits_menu_p(ptype);
	if (ISVREF(ptype,(SI_Long)4L)) {
	    temp = ISVREF(ptype,(SI_Long)4L);
	    return APPLY_1(temp,arguments);
	}
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* PARTIAL-COMMAND-NEXT-ARGUMENT-WANTS-MENU */
Object partial_command_next_argument_wants_menu(command_or_partial_command)
    Object command_or_partial_command;
{
    Object ptype, wants_menu_qm;

    x_note_fn_call(118,61);
    ptype = 
	    command_or_partial_command_next_argument_type(command_or_partial_command);
    wants_menu_qm = presentation_type_wants_menu(ptype);
    reclaim_presentation_type(ptype);
    return VALUES_1(wants_menu_qm);
}

static Object Qui_command_command_posts_dialog_p;  /* ui-command-command-posts-dialog-p */

/* PARTIAL-COMMAND-NEXT-ARGUMENT-WANTS-DIALOG */
Object partial_command_next_argument_wants_dialog(command_or_partial_command)
    Object command_or_partial_command;
{
    Object command_name_qm, ptype, wants_dialog_qm;

    x_note_fn_call(118,62);
    if (SYMBOLP(command_or_partial_command))
	command_name_qm = command_or_partial_command;
    else if (SIMPLE_VECTOR_P(command_or_partial_command) && 
	    EQ(ISVREF(command_or_partial_command,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	command_name_qm = ISVREF(command_or_partial_command,(SI_Long)1L);
    else
	command_name_qm = Qnil;
    ptype = 
	    command_or_partial_command_next_argument_type(command_or_partial_command);
    wants_dialog_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name_qm),
	    Qui_command_command_posts_dialog_p);
    if (wants_dialog_qm);
    else
	wants_dialog_qm = presentation_type_admits_dialog_p(ptype);
    reclaim_presentation_type(ptype);
    return VALUES_1(wants_dialog_qm);
}

/* PARTIAL-COMMAND-IS-COMPLETE-P */
Object partial_command_is_complete_p(partial_command)
    Object partial_command;
{
    Object argument, ab_loop_list_;

    x_note_fn_call(118,63);
    argument = Nil;
    ab_loop_list_ = ISVREF(partial_command,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(argument,Plus_missing_argument_plus))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* RECORD-COMMAND-IN-JOURNAL */
Object record_command_in_journal(command_name,command_arguments)
    Object command_name, command_arguments;
{
    x_note_fn_call(118,64);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ui_command_context, Qui_command_context);

/* COMMAND-AVAILABLE-P */
Object command_available_p(command,mouse_pointer)
    Object command, mouse_pointer;
{
    Object frame_qm, command_qm, gensymed_symbol, temp, partial_command_qm;

    x_note_fn_call(118,65);
    if (mouse_pointer_is_multi_p(mouse_pointer) &&  
	    !TRUEP(command_runs_on_multi_selection_p(command)))
	return VALUES_1(Nil);
    else if (CONSP(command)) {
	frame_qm = compute_frame_for_selection(mouse_pointer);
	if (frame_qm)
	    return VALUES_1( ! 
		    !TRUEP(get_user_menu_choice_or_choice_symbols(2,
		    frame_qm,SECOND(command))) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else {
	command_qm = find_ui_command(2,command,T);
	if (command_qm) {
	    gensymed_symbol = ISVREF(command_qm,(SI_Long)5L);
	    temp = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    partial_command_qm = FUNCALL_1(temp,mouse_pointer);
	}
	else
	    partial_command_qm = Nil;
	if (partial_command_qm) {
	    reclaim_partial_command(partial_command_qm);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* START-UI-COMMAND */
Object start_ui_command varargs_1(int, n)
{
    Object command_or_name, mouse_pointer;
    Object warn_p, command_qm, gensymed_symbol, temp, partial_command_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,66);
    INIT_ARGS_nonrelocating();
    command_or_name = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    warn_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    command_qm = find_ui_command(2,command_or_name,T);
    if (command_qm) {
	gensymed_symbol = ISVREF(command_qm,(SI_Long)5L);
	temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) 
		: gensymed_symbol;
	partial_command_qm = FUNCALL_1(temp,mouse_pointer);
	if (partial_command_qm)
	    return pursue_partial_command(2,partial_command_qm,mouse_pointer);
	else if (warn_p)
	    return VALUES_1(Nil);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* EXECUTE-UI-COMMAND */
Object execute_ui_command(command_name,command_arguments)
    Object command_name, command_arguments;
{
    Object ui_command_qm, temp;

    x_note_fn_call(118,67);
    ui_command_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
	    Qui_command_named);
    if (ui_command_qm) {
	record_command_in_journal(command_name,command_arguments);
	temp = ISVREF(ui_command_qm,(SI_Long)4L);
	return APPLY_1(temp,command_arguments);
    }
    else
	return VALUES_1(Nil);
}

/* EXECUTE-PARTIAL-COMMAND */
Object execute_partial_command(partial_command)
    Object partial_command;
{
    Object command_name, argument, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, command_arguments, temp;

    x_note_fn_call(118,68);
    if ( !(SIMPLE_VECTOR_P(partial_command) && EQ(ISVREF(partial_command,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct)))
	return VALUES_1(Nil);
    else if ( !TRUEP(partial_command_valid_p(partial_command)))
	return VALUES_1(Nil);
    else {
	command_name = ISVREF(partial_command,(SI_Long)1L);
	argument = Nil;
	ab_loop_list_ = ISVREF(partial_command,(SI_Long)2L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = slot_value_cons_1(command_argument_value(argument),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	command_arguments = ab_loopvar_;
	goto end_1;
	command_arguments = Qnil;
      end_1:;
	temp = execute_ui_command(command_name,command_arguments);
	reclaim_slot_value_list_1(command_arguments);
	reclaim_partial_command(partial_command);
	return VALUES_1(temp);
    }
}

/* PURSUE-PARTIAL-COMMAND */
Object pursue_partial_command varargs_1(int, n)
{
    Object partial_command, mouse_pointer;
    Object mode, command, pursuer, gensymed_symbol, temp, argument_type;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(118,69);
    INIT_ARGS_nonrelocating();
    partial_command = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    mode = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    command = partial_command_command(partial_command);
    pursuer = ISVREF(command,(SI_Long)6L);
    fill_in_mouse_pointer_arguments(partial_command,mouse_pointer);
    fill_in_immediate_arguments(partial_command);
    gensymed_symbol = pursuer;
    temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) : 
	    gensymed_symbol;
    result = FUNCALL_1(temp,partial_command);
    argument_type = NTH_VALUE((SI_Long)1L, result);
    if ( !TRUEP(argument_type))
	return execute_partial_command(partial_command);
    else
	return collect_next_argument_for_partial_command(partial_command,
		argument_type,mouse_pointer,mode);
}

DEFINE_VARIABLE_WITH_SYMBOL(Presentation_mode, Qpresentation_mode);

/* COLLECT-NEXT-ARGUMENT-FOR-PARTIAL-COMMAND */
Object collect_next_argument_for_partial_command(partial_command,
	    argument_type,mouse_pointer,mode)
    Object partial_command, argument_type, mouse_pointer, mode;
{
    Object ptype_qm, presentation_mode, menu_qm, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,70);
    ptype_qm = find_presentation_type(2,argument_type,T);
    presentation_mode = mode;
    PUSH_SPECIAL_WITH_SYMBOL(Presentation_mode,Qpresentation_mode,presentation_mode,
	    0);
      if (ptype_qm) {
	  menu_qm = make_parameter_submenu_for_partial_command(2,
		  partial_command,mouse_pointer);
	  temp = menu_qm ? expose_menu(3,menu_qm,ISVREF(mouse_pointer,
		  (SI_Long)2L),ISVREF(mouse_pointer,(SI_Long)3L)) : Nil;
	  reclaim_presentation_type(argument_type);
	  result = VALUES_1(temp);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* MORE-MISSING-ARGUMENTS-P */
Object more_missing_arguments_p(partial_command,argument_place)
    Object partial_command, argument_place;
{
    Object argument, temp, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(118,71);
    argument = Nil;
    temp = nthcdr(argument_place,ISVREF(partial_command,(SI_Long)2L));
    ab_loop_list_ = CDR(temp);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(argument,Plus_missing_argument_plus) ? T : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PARTIAL-COMMAND-REQUIRES-SUBMENU-AFTER-THIS-CHOICE */
Object partial_command_requires_submenu_after_this_choice(partial_command,
	    which_argument,value)
    Object partial_command, which_argument, value;
{
    Object new_partial_command;

    x_note_fn_call(118,72);
    new_partial_command = copy_partial_command(partial_command);
    bind_partial_command_argument(new_partial_command,which_argument,value);
    fill_in_immediate_arguments(new_partial_command);
    if ( !TRUEP(partial_command_is_complete_p(new_partial_command)))
	return VALUES_1(new_partial_command);
    else {
	reclaim_partial_command(new_partial_command);
	return VALUES_1(Nil);
    }
}

/* PARAMETER-MENU-ITEM-SUBMENU-P */
Object parameter_menu_item_submenu_p(menu_description,menu_item,
	    partial_command,argument_place,arg_3)
    Object menu_description, menu_item, partial_command, argument_place, arg_3;
{
    Object temp, new_partial_command_qm;

    x_note_fn_call(118,73);
    temp = menu_item_submenu_p(menu_description,menu_item);
    if (temp)
	return VALUES_1(temp);
    else if (more_missing_arguments_p(partial_command,argument_place)) {
	new_partial_command_qm = 
		partial_command_requires_submenu_after_this_choice(partial_command,
		argument_place,
		transform_menu_item_after_choice(menu_description,menu_item));
	if (new_partial_command_qm) {
	    reclaim_partial_command(new_partial_command_qm);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qparameter_menu_item_submenu_p;  /* parameter-menu-item-submenu-p */

/* MAKE-PARAMETER-SUBMENU-FOR-PARTIAL-COMMAND */
Object make_parameter_submenu_for_partial_command varargs_1(int, n)
{
    Object partial_command, mouse_pointer;
    Object adjustment, command, pursuer, gensymed_symbol, temp, argument_type;
    Object argument_place, ptype_qm, parameters, options, menu_name_qm;
    Object menu_description_qm;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(118,74);
    INIT_ARGS_nonrelocating();
    partial_command = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    adjustment = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    command = partial_command_command(partial_command);
    pursuer = ISVREF(command,(SI_Long)6L);
    gensymed_symbol = pursuer;
    temp = SYMBOLP(gensymed_symbol) ? SYMBOL_FUNCTION(gensymed_symbol) : 
	    gensymed_symbol;
    result = FUNCALL_1(temp,partial_command);
    MVS_3(result,temp,argument_type,argument_place);
    result = parse_presentation_type(argument_type);
    MVS_3(result,ptype_qm,parameters,options);
    if (ptype_qm) {
	menu_name_qm = ISVREF(ptype_qm,(SI_Long)2L);
	menu_description_qm = menu_name_qm ? 
		menu_description_named(menu_name_qm) : Qnil;
	temp = menu_description_qm ? make_parameter_menu(12,menu_name_qm,
		partial_command,argument_place,mouse_pointer,adjustment,
		parameters,options,Nil,Nil,
		SYMBOL_FUNCTION(Qparameter_menu_item_submenu_p),
		partial_command,argument_place) : Nil;
	reclaim_presentation_type(argument_type);
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

/* BIND-PARTIAL-COMMAND-ARGUMENT */
Object bind_partial_command_argument(partial_command,which_argument,value)
    Object partial_command, which_argument, value;
{
    Object nth_arg_2, nth_new_value;

    x_note_fn_call(118,75);
    nth_arg_2 = ISVREF(partial_command,(SI_Long)2L);
    nth_new_value = snapshot_command_argument(value);
    return VALUES_1(M_NTH(which_argument,nth_arg_2) = nth_new_value);
}

/* UNBIND-PARTIAL-COMMAND-ARGUMENT */
Object unbind_partial_command_argument(partial_command,which_argument)
    Object partial_command, which_argument;
{
    Object arguments, old_argument, nth_new_value;

    x_note_fn_call(118,76);
    arguments = ISVREF(partial_command,(SI_Long)2L);
    old_argument = nth(which_argument,arguments);
    reclaim_partial_command_argument(old_argument);
    nth_new_value = Plus_missing_argument_plus;
    return VALUES_1(M_NTH(which_argument,arguments) = nth_new_value);
}

Object Find_menu_description_prop = UNBOUND;

static Object Qfind_menu_description;  /* find-menu-description */

/* MENU-DESCRIPTION-NAMED */
Object menu_description_named(name_qm)
    Object name_qm;
{
    x_note_fn_call(118,77);
    if (name_qm)
	return getfq_function_no_default(INLINE_SYMBOL_PLIST(name_qm),
		Qfind_menu_description);
    else
	return VALUES_1(Nil);
}

Object Menu_descriptions_for_class_prop = UNBOUND;

static Object Qg2_defstruct_structure_name_menu_description_g2_struct;  /* g2-defstruct-structure-name::menu-description-g2-struct */

static Object Qparameter_menu;     /* parameter-menu */

static Object Qparameter_menu_choice_function;  /* parameter-menu-choice-function */

static Object Qcommand_menu;       /* command-menu */

static Object Qcommand_menu_choice_function;  /* command-menu-choice-function */

static Object Qmenu_descriptions_for_class;  /* menu-descriptions-for-class */

/* MAKE-MENU-DESCRIPTION */
Object make_menu_description(name,doc,classes,title,condition,
	    make_text_cell_1,single_lines,capitalize,strip_hyphens,
	    choice_function,no_choice_function,restriction_type,
	    choice_transformer,submenu_choices,menu_type,choices)
    Object name, doc, classes, title, condition, make_text_cell_1;
    Object single_lines, capitalize, strip_hyphens, choice_function;
    Object no_choice_function, restriction_type, choice_transformer;
    Object submenu_choices, menu_type, choices;
{
    Object defstruct_g2_menu_description_variable, the_array, menu_1;
    Object svref_new_value, class_1, ab_loop_list_, sublist, key, temp, temp_1;
    SI_Long gensymed_symbol, i, ab_loop_bind_;

    x_note_fn_call(118,78);
    defstruct_g2_menu_description_variable = Nil;
    gensymed_symbol = (SI_Long)17L;
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
    defstruct_g2_menu_description_variable = the_array;
    SVREF(defstruct_g2_menu_description_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_menu_description_g2_struct;
    menu_1 = defstruct_g2_menu_description_variable;
    SVREF(menu_1,FIX((SI_Long)1L)) = name;
    SVREF(menu_1,FIX((SI_Long)3L)) = doc;
    svref_new_value = title;
    if (svref_new_value);
    else
	svref_new_value = name;
    SVREF(menu_1,FIX((SI_Long)2L)) = svref_new_value;
    SVREF(menu_1,FIX((SI_Long)4L)) = classes;
    SVREF(menu_1,FIX((SI_Long)11L)) = make_text_cell_1;
    SVREF(menu_1,FIX((SI_Long)8L)) = condition;
    SVREF(menu_1,FIX((SI_Long)7L)) = restriction_type;
    SVREF(menu_1,FIX((SI_Long)9L)) = choice_transformer;
    SVREF(menu_1,FIX((SI_Long)10L)) = submenu_choices;
    SVREF(menu_1,FIX((SI_Long)15L)) = menu_type;
    SVREF(menu_1,FIX((SI_Long)12L)) = single_lines;
    SVREF(menu_1,FIX((SI_Long)13L)) = capitalize;
    SVREF(menu_1,FIX((SI_Long)14L)) = strip_hyphens;
    SVREF(menu_1,FIX((SI_Long)6L)) = no_choice_function;
    svref_new_value = choice_function;
    if (svref_new_value);
    else if (EQ(menu_type,Qparameter_menu))
	svref_new_value = SYMBOL_FUNCTION(Qparameter_menu_choice_function);
    else if (EQ(menu_type,Qcommand_menu))
	svref_new_value = SYMBOL_FUNCTION(Qcommand_menu_choice_function);
    else
	svref_new_value = Qnil;
    SVREF(menu_1,FIX((SI_Long)5L)) = svref_new_value;
    SVREF(menu_1,FIX((SI_Long)16L)) = choices;
    class_1 = Nil;
    ab_loop_list_ = classes;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sublist = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qmenu_descriptions_for_class);
    key = Nil;
  next_loop_2:
    if ( !TRUEP(sublist))
	goto end_loop_2;
    key = ISVREF(CAR(sublist),(SI_Long)1L);
    if (EQ(key,ISVREF(menu_1,(SI_Long)1L))) {
	M_CAR(sublist) = menu_1;
	goto end_1;
    }
    sublist = M_CDR(sublist);
    goto next_loop_2;
  end_loop_2:
    temp = class_1;
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(class_1),
	    Qmenu_descriptions_for_class);
    mutate_global_property(temp,CONS(menu_1,temp_1),
	    Qmenu_descriptions_for_class);
  end_1:;
    goto next_loop_1;
  end_loop_1:;
    return mutate_global_property(name,menu_1,Qfind_menu_description);
}

/* MENU-AVAILABLE-P */
Object menu_available_p(menu_description,mouse_pointer)
    Object menu_description, mouse_pointer;
{
    Object condition, temp;

    x_note_fn_call(118,79);
    condition = ISVREF(menu_description,(SI_Long)8L);
    temp =  !TRUEP(condition) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return FUNCALL_1(condition,mouse_pointer);
}

/* MENU-OBTAINS-P */
Object menu_obtains_p(name_of_menu,mouse_pointer)
    Object name_of_menu, mouse_pointer;
{
    Object menu_description_qm;

    x_note_fn_call(118,80);
    menu_description_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_menu),
	    Qfind_menu_description);
    if (menu_description_qm)
	return VALUES_1(EQ(menu_description_qm,
		find_menu_for_spot(ISVREF(mouse_pointer,(SI_Long)5L))) ? T 
		: Nil);
    else
	return VALUES_1(Nil);
}

static Object Qnamed_gensym_structure;  /* named-gensym-structure */

/* FIND-MENU-FOR-SPOT */
Object find_menu_for_spot(spot)
    Object spot;
{
    Object mouse_pointer, class_name, ab_loop_list_, menu_descriptions, desc;
    Object ab_loop_list__1;

    x_note_fn_call(118,81);
    mouse_pointer = ISVREF(spot,(SI_Long)1L);
    class_name = Nil;
    ab_loop_list_ = ISVREF(type_description_of(spot),(SI_Long)2L);
    menu_descriptions = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(class_name,Qnamed_gensym_structure))
	goto end_loop;
    menu_descriptions = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_name),
	    Qmenu_descriptions_for_class);
    desc = Nil;
    ab_loop_list__1 = menu_descriptions;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    desc = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (menu_available_p(desc,mouse_pointer))
	return VALUES_1(desc);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* WITHIN-SPOT-OF-TYPE-P */
Object within_spot_of_type_p(mouse_pointer,spot_type_or_frame_class)
    Object mouse_pointer, spot_type_or_frame_class;
{
    Object spot, frame, ab_loop_it_, temp;

    x_note_fn_call(118,82);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    temp = ab_typep_function(spot,spot_type_or_frame_class);
    if (temp);
    else
	temp = frame ? ab_typep_function(frame,spot_type_or_frame_class) : 
		Qnil;
    ab_loop_it_ = temp;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PRESENTATION-TYPE-CHOICE-TRANSFORMER */
Object presentation_type_choice_transformer(presentation_type_or_name)
    Object presentation_type_or_name;
{
    Object ptype_qm, menu_name_qm, menu_descriiption_qm;

    x_note_fn_call(118,83);
    ptype_qm = find_presentation_type(1,presentation_type_or_name);
    if (ptype_qm) {
	menu_name_qm = ISVREF(ptype_qm,(SI_Long)2L);
	if (menu_name_qm) {
	    menu_descriiption_qm = menu_description_named(menu_name_qm);
	    if (menu_descriiption_qm)
		return VALUES_1(ISVREF(menu_descriiption_qm,(SI_Long)9L));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Exported_menu_description_for_class_prop = UNBOUND;

/* SYSTEM-MENU-CHOICES-FOR-CLASS */
Object system_menu_choices_for_class(class_name)
    Object class_name;
{
    Object menu_description;

    x_note_fn_call(118,84);
    menu_description = menu_description_for_class(class_name);
    if (menu_description)
	return allocate_evaluation_sequence(menu_description_choice_names(menu_description));
    else
	return VALUES_1(Nil);
}

/* MENU-DESCRIPTION-FOR-CLASS */
Object menu_description_for_class(class_name)
    Object class_name;
{
    Object class_description, class_inheritance_path, super_class;
    Object ab_loop_list_, ab_loop_it_;

    x_note_fn_call(118,85);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
    super_class = Nil;
    ab_loop_list_ = class_inheritance_path;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    super_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = menu_description_local_to_class_if_any(super_class);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qexported_menu_description_for_class;  /* exported-menu-description-for-class */

/* MENU-DESCRIPTION-LOCAL-TO-CLASS-IF-ANY */
Object menu_description_local_to_class_if_any(class_name)
    Object class_name;
{
    Object menu_description_name_qm;

    x_note_fn_call(118,86);
    menu_description_name_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(class_name),
	    Qexported_menu_description_for_class);
    if (menu_description_name_qm)
	return menu_description_named(menu_description_name_qm);
    else
	return VALUES_1(Nil);
}

/* MENU-DESCRIPTION-CHOICE-NAMES */
Object menu_description_choice_names(menu_description)
    Object menu_description;
{
    Object result_1, list_or_function, symbol_or_list, ab_loop_list_;
    Object command_structure_qm, eval_modify_macro_using_test_arg_1, car_1;
    Object cdr_1, key_result, x_element, ab_loop_list__1, ab_loop_it_;
    Object included_menu_name, included_menu_description_qm, temp_1;
    char temp;

    x_note_fn_call(118,87);
    result_1 = Nil;
    list_or_function = ISVREF(menu_description,(SI_Long)16L);
    if (ATOM(list_or_function));
    else {
	symbol_or_list = Nil;
	ab_loop_list_ = list_or_function;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	symbol_or_list = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ATOM(symbol_or_list)) {
	    command_structure_qm = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol_or_list),
		    Qui_command_named);
	    eval_modify_macro_using_test_arg_1 = command_structure_qm ? 
		    ISVREF(command_structure_qm,(SI_Long)2L) : symbol_or_list;
	    car_1 = eval_modify_macro_using_test_arg_1;
	    cdr_1 = result_1;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list__1 = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    x_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_1:;
	    result_1 = temp ? cdr_1 : eval_cons_1(car_1,cdr_1);
	}
	else {
	    included_menu_name = CADR(symbol_or_list);
	    included_menu_description_qm = 
		    menu_description_named(included_menu_name);
	    if (included_menu_description_qm) {
		temp_1 = 
			menu_description_choice_names(included_menu_description_qm);
		result_1 = nconc2(temp_1,result_1);
	    }
	}
	goto next_loop;
      end_loop:;
    }
    return nreverse(result_1);
}

/* COPY-MENU-ITEM */
Object copy_menu_item(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,88);
    return copy_for_slot_value(menu_item);
}

/* RECLAIM-MENU-ITEM */
Object reclaim_menu_item(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,89);
    if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct)) {
	if (snapshot_of_block_valid_p(menu_item))
	    delete_menu(ISVREF(menu_item,(SI_Long)1L));
	return reclaim_snapshot_of_block_1(menu_item);
    }
    else if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	return reclaim_partial_command(menu_item);
    else if (CONSP(menu_item))
	return reclaim_slot_value(menu_item);
    else
	return VALUES_1(Qnil);
}

/* MENU-ITEM-NCOLUMNS */
Object menu_item_ncolumns(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,90);
    if (CONSP(menu_item) && EQ(CAR(menu_item),Qrow))
	return length(CDR(menu_item));
    else
	return VALUES_1(FIX((SI_Long)1L));
}

static Object Qchoice;             /* choice */

/* MENU-ITEM-PLIST */
Object menu_item_plist(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,91);
    if (CONSP(menu_item) && EQ(CAR(menu_item),Qchoice))
	return VALUES_1(CDDDR(menu_item));
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* MENU-ITEM-SPECIAL-P */
Object menu_item_special_p(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,92);
    if (CONSP(menu_item))
	return memq_function(CAR(menu_item),list_constant);
    else
	return VALUES_1(Nil);
}

static Object Qsubmenu;            /* submenu */

/* MENU-ITEM-EXPLICIT-SUBMENU */
Object menu_item_explicit_submenu(menu_description,menu_item)
    Object menu_description, menu_item;
{
    x_note_fn_call(118,93);
    if (CONSP(menu_item) && EQ(CAR(menu_item),Qsubmenu))
	return VALUES_1(CADR(menu_item));
    else
	return VALUES_1(Nil);
}

static Object Qdialog;             /* dialog */

/* MENU-ITEM-DIALOG */
Object menu_item_dialog(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,94);
    if (CONSP(menu_item) && EQ(CAR(menu_item),Qdialog))
	return VALUES_1(THIRD(menu_item));
    else
	return VALUES_1(Nil);
}

static Object Qcommand;            /* command */

/* MENU-ITEM-IS-COMMAND-P */
Object menu_item_is_command_p(menu_item)
    Object menu_item;
{
    Object temp;

    x_note_fn_call(118,95);
    temp = SYMBOLP(menu_item) ? T : Nil;
    if (temp);
    else
	temp = CONSP(menu_item) ? (EQ(CAR(menu_item),Qcommand) ? T : Nil) :
		 Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (SIMPLE_VECTOR_P(menu_item))
	return VALUES_1(EQ(ISVREF(menu_item,(SI_Long)0L),
		Qg2_defstruct_structure_name_partial_command_g2_struct) ? 
		T : Nil);
    else
	return VALUES_1(Nil);
}

/* MENU-ITEM-COMMAND-NAME */
Object menu_item_command_name(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,96);
    if (SYMBOLP(menu_item))
	return VALUES_1(menu_item);
    else if (CONSP(menu_item) && EQ(CAR(menu_item),Qcommand))
	return VALUES_1(THIRD(menu_item));
    else
	return VALUES_1(Qnil);
}

/* MENU-ITEM-COMMAND */
Object menu_item_command(menu_item)
    Object menu_item;
{
    Object temp;

    x_note_fn_call(118,97);
    temp = menu_item_command_name(menu_item);
    if (temp)
	return VALUES_1(temp);
    else if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	return VALUES_1(menu_item);
    else
	return VALUES_1(Nil);
}

static Object Q_SPACER_;           /* |-spacer-| */

/* MENU-ITEM-SUBMENU-P */
Object menu_item_submenu_p(menu_description,menu_item)
    Object menu_description, menu_item;
{
    Object temp, name, char_1;
    SI_Long ab_loop_bind_, i;
    char temp_1;

    x_note_fn_call(118,98);
    temp = menu_item_explicit_submenu(menu_description,menu_item);
    if (temp)
	return VALUES_1(temp);
    else {
	if (SYMBOLP(menu_item)) {
	    temp_1 = EQ(menu_item,Q_SPACER_);
	    if (temp_1);
	    else {
		name = symbol_name_text_string(menu_item);
		ab_loop_bind_ = IFIX(text_string_length(name));
		i = (SI_Long)0L;
		char_1 = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
		if ( !(IFIX(char_1) == (SI_Long)45L)) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(Nil);
	else if (EQ(ISVREF(menu_description,(SI_Long)15L),Qparameter_menu))
	    return VALUES_1(Nil);
	else if (menu_item_is_command_p(menu_item))
	    return partial_command_next_argument_wants_menu(menu_item_command(menu_item));
	else
	    return VALUES_1(Qnil);
    }
}

/* MENU-ITEM-NAME */
Object menu_item_name(menu_item)
    Object menu_item;
{
    x_note_fn_call(118,99);
    if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	return VALUES_1(ISVREF(partial_command_command(menu_item),
		(SI_Long)2L));
    else if (CONSP(menu_item) && EQ(FIRST(menu_item),Qcommand))
	return VALUES_1(SECOND(menu_item));
    else
	return menu_item_value(menu_item);
}

static Object Quser_menu_choice;   /* user-menu-choice */

/* MENU-ITEM-VALUE */
Object menu_item_value(menu_item)
    Object menu_item;
{
    Object temp, name, char_1;
    SI_Long ab_loop_bind_, i;
    char temp_1;

    x_note_fn_call(118,100);
    if (CONSP(menu_item)) {
	temp = CAR(menu_item);
	if (EQ(temp,Qchoice) || EQ(temp,Qcommand))
	    return VALUES_1(THIRD(menu_item));
	else if (EQ(temp,Quser_menu_choice))
	    return VALUES_1(SECOND(menu_item));
	else if (EQ(temp,Qsubmenu)) {
	    temp = THIRD(menu_item);
	    if (temp)
		return VALUES_1(temp);
	    else
		return VALUES_1(SECOND(menu_item));
	}
	else
	    return VALUES_1(menu_item);
    }
    else {
	if (SYMBOLP(menu_item)) {
	    temp_1 = EQ(menu_item,Q_SPACER_);
	    if (temp_1);
	    else {
		name = symbol_name_text_string(menu_item);
		ab_loop_bind_ = IFIX(text_string_length(name));
		i = (SI_Long)0L;
		char_1 = Nil;
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
		if ( !(IFIX(char_1) == (SI_Long)45L)) {
		    temp_1 = TRUEP(Nil);
		    goto end_1;
		}
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		temp_1 = TRUEP(T);
		goto end_1;
		temp_1 = TRUEP(Qnil);
	      end_1:;
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(Nil);
	else
	    return VALUES_1(menu_item);
    }
}

static Object Qmenu_string;        /* menu-string */

static Object Kfirst_of_each_word;  /* :first-of-each-word */

static Object Knone;               /* :none */

/* TRANSLATED-STRING-FOR-SYMBOL */
Object translated_string_for_symbol varargs_1(int, n)
{
    Object symbol;
    Object capitalize_qm, strip_hyphens_qm, translation_qm, default_1;
    Object menu_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,101);
    INIT_ARGS_nonrelocating();
    symbol = REQUIRED_ARG_nonrelocating();
    capitalize_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    strip_hyphens_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    translation_qm = SYMBOLP(symbol) ? translation_for_symbol_qm(1,symbol) 
	    : Qnil;
    default_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
	    Qmenu_string);
    if (default_1);
    else
	default_1 = symbol;
    menu_name = translation_qm;
    if (menu_name);
    else
	menu_name = default_1;
    if (SYMBOLP(menu_name))
	return copy_symbol_name(5,menu_name,EQ(capitalize_qm,T) ? 
		Kfirst_of_each_word : capitalize_qm,strip_hyphens_qm,Nil,
		Known_gensym_acronyms);
    else if (text_string_p(menu_name)) {
	if (translation_qm || capitalize_qm)
	    return copy_text_string(menu_name);
	else
	    return copy_text_string_with_case_conversion(menu_name,Knone);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_1;   /* "~a..." */

/* COMPUTE-MODIFIED-MENU-ITEM-STRING */
Object compute_modified_menu_item_string(menu_item,string_1)
    Object menu_item, string_1;
{
    Object native_qm, temp;

    x_note_fn_call(118,102);
    native_qm = current_window() ? native_pop_up_menus_p(current_window()) 
	    : Qnil;
    if ( !TRUEP(native_qm)) {
	temp = remove_character_from_wide_string(FIX((SI_Long)38L),string_1);
	reclaim_text_string(string_1);
	string_1 = temp;
    }
    if (native_qm && partial_command_next_argument_wants_dialog(menu_item)) {
	temp = tformat_text_string(2,string_constant_1,string_1);
	reclaim_text_string(string_1);
	string_1 = temp;
    }
    return VALUES_1(string_1);
}

static Object Qmenu_item;          /* menu-item */

static Object string_constant_2;   /* "<<Missing submenu ~s>>" */

/* MENU-ITEM-STRING */
Object menu_item_string varargs_1(int, n)
{
    Object menu_description, menu_item;
    Object capitalize_qm, strip_hyphens_qm, parameters, temp;
    Object current_localization_purpose_qm, name, char_1, string_1, command;
    Object gensymed_symbol, submenu_name, submenu_title, submenu_desc;
    SI_Long ab_loop_bind_, i;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(118,103);
    INIT_ARGS_nonrelocating();
    menu_description = REQUIRED_ARG_nonrelocating();
    menu_item = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    capitalize_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    strip_hyphens_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = Current_localization_purpose_qm;
	if (temp);
	else
	    temp = Qmenu_item;
	current_localization_purpose_qm = temp;
	PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
		0);
	  if ( !TRUEP(menu_item))
	      SAVE_VALUES(VALUES_1(Nil));
	  else {
	      if (SYMBOLP(menu_item)) {
		  temp_1 = EQ(menu_item,Q_SPACER_);
		  if (temp_1);
		  else {
		      name = symbol_name_text_string(menu_item);
		      ab_loop_bind_ = IFIX(text_string_length(name));
		      i = (SI_Long)0L;
		      char_1 = Nil;
		    next_loop:
		      if (i >= ab_loop_bind_)
			  goto end_loop;
		      char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
		      if ( !(IFIX(char_1) == (SI_Long)45L)) {
			  temp_1 = TRUEP(Nil);
			  goto end_1;
		      }
		      i = i + (SI_Long)1L;
		      goto next_loop;
		    end_loop:
		      temp_1 = TRUEP(T);
		      goto end_1;
		      temp_1 = TRUEP(Qnil);
		    end_1:;
		  }
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  SAVE_VALUES(VALUES_1(Nil));
	      else if (STRINGP(menu_item) || text_string_p(menu_item))
		  SAVE_VALUES(copy_text_string(menu_item));
	      else if (SYMBOLP(menu_item)) {
		  string_1 = translated_string_for_symbol(3,menu_item,
			  capitalize_qm,strip_hyphens_qm);
		  SAVE_VALUES(compute_modified_menu_item_string(menu_item,
			  string_1));
	      }
	      else if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_partial_command_g2_struct)) 
			  {
		  command = partial_command_command(menu_item);
		  string_1 = translated_string_for_symbol(3,ISVREF(command,
			  (SI_Long)2L),capitalize_qm,strip_hyphens_qm);
		  if (ISVREF(command,(SI_Long)10L) && 
			  partial_command_is_complete_p(menu_item)) {
		      gensymed_symbol = ISVREF(command,(SI_Long)10L);
		      temp = SYMBOLP(gensymed_symbol) ? 
			      SYMBOL_FUNCTION(gensymed_symbol) : 
			      gensymed_symbol;
		      temp = FUNCALL_2(temp,menu_item,string_1);
		      reclaim_wide_string(string_1);
		      string_1 = temp;
		  }
		  SAVE_VALUES(compute_modified_menu_item_string(menu_item,
			  string_1));
	      }
	      else if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_ui_command_g2_struct)) {
		  string_1 = translated_string_for_symbol(3,
			  ISVREF(menu_item,(SI_Long)2L),capitalize_qm,
			  strip_hyphens_qm);
		  SAVE_VALUES(compute_modified_menu_item_string(ISVREF(menu_item,
			  (SI_Long)1L),string_1));
	      }
	      else if (CONSP(menu_item)) {
		  temp = CAR(menu_item);
		  if (EQ(temp,Qsubmenu)) {
		      submenu_name = SECOND(menu_item);
		      submenu_title = THIRD(menu_item);
		      submenu_desc = 
			      getfq_function_no_default(INLINE_SYMBOL_PLIST(submenu_name),
			      Qfind_menu_description);
		      if (ISVREF(menu_description,(SI_Long)10L)) {
			  temp = submenu_title;
			  if (temp);
			  else
			      temp = submenu_name;
			  SAVE_VALUES(menu_item_string(5,menu_description,
				  temp,capitalize_qm,strip_hyphens_qm,
				  parameters));
		      }
		      else if (submenu_desc) {
			  temp = submenu_title;
			  if (temp);
			  else
			      temp = ISVREF(submenu_desc,(SI_Long)2L);
			  SAVE_VALUES(menu_item_string(5,submenu_desc,temp,
				  capitalize_qm,strip_hyphens_qm,parameters));
		      }
		      else
			  SAVE_VALUES(tformat_text_string(2,
				  string_constant_2,submenu_name));
		  }
		  else if (EQ(temp,Qchoice) || EQ(temp,Qcommand) || 
			  EQ(temp,Qdialog) || EQ(temp,Quser_menu_choice))
		      SAVE_VALUES(menu_item_string(5,menu_description,
			      SECOND(menu_item),capitalize_qm,
			      strip_hyphens_qm,parameters));
		  else
		      SAVE_VALUES(VALUES_1(Nil));
	      }
	      else
		  SAVE_VALUES(VALUES_1(Nil));
	  }
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object list_constant_1;     /* # */

/* MENU-ITEM-CAUSES-MOVEMENT-P */
Object menu_item_causes_movement_p(choice)
    Object choice;
{
    x_note_fn_call(118,104);
    return memq_function(choice,list_constant_1);
}

Object Refreshes_image_plane_p_prop = UNBOUND;

static Object Qrefreshes_image_plane_p;  /* refreshes-image-plane-p */

/* EVENT-HANDLER-REFRESHES-IMAGE-PLANE-P */
Object event_handler_refreshes_image_plane_p(event_handler_qm)
    Object event_handler_qm;
{
    x_note_fn_call(118,105);
    if (event_handler_qm && SYMBOLP(event_handler_qm))
	return getfq_function_no_default(INLINE_SYMBOL_PLIST(event_handler_qm),
		Qrefreshes_image_plane_p);
    else
	return VALUES_1(Nil);
}

/* TRANSFORM-MENU-ITEM */
Object transform_menu_item varargs_1(int, n)
{
    Object menu_description, menu_item, mouse_pointer;
    Object recyclable_lists_qm, name, char_1, submenu_name, desc, command_name;
    Object command_qm, partial_command_qm, new_menu_item;
    SI_Long ab_loop_bind_, i;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,106);
    INIT_ARGS_nonrelocating();
    menu_description = REQUIRED_ARG_nonrelocating();
    menu_item = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    recyclable_lists_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(menu_item)) {
	temp = EQ(menu_item,Q_SPACER_);
	if (temp);
	else {
	    name = symbol_name_text_string(menu_item);
	    ab_loop_bind_ = IFIX(text_string_length(name));
	    i = (SI_Long)0L;
	    char_1 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    char_1 = FIX(UBYTE_16_ISAREF_1(name,i));
	    if ( !(IFIX(char_1) == (SI_Long)45L)) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(menu_item);
    else if (menu_item_explicit_submenu(menu_description,menu_item)) {
	temp = TRUEP(ISVREF(menu_description,(SI_Long)10L));
	if (temp);
	else {
	    submenu_name = menu_item_explicit_submenu(menu_description,
		    menu_item);
	    desc = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(submenu_name),
		    Qfind_menu_description);
	    temp = desc ? TRUEP(menu_available_p(desc,mouse_pointer)) : 
		    TRUEP(Qnil);
	}
	if (temp)
	    return copy_for_slot_value(menu_item);
	else
	    return VALUES_1(Nil);
    }
    else if (menu_item_command_name(menu_item) && 
	    EQ(ISVREF(menu_description,(SI_Long)15L),Qcommand_menu)) {
	command_name = menu_item_command_name(menu_item);
	command_qm = find_ui_command(2,command_name,T);
	partial_command_qm = make_initial_partial_command(command_qm,
		mouse_pointer);
	if ( !TRUEP(partial_command_qm))
	    return VALUES_1(Nil);
	else if (SYMBOLP(menu_item))
	    return VALUES_1(partial_command_qm);
	else if (CONSP(menu_item)) {
	    new_menu_item = copy_list_using_slot_value_conses_1(menu_item);
	    M_THIRD(new_menu_item) = partial_command_qm;
	    if (recyclable_lists_qm)
		reclaim_slot_value_list_1(menu_item);
	    return VALUES_1(new_menu_item);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return copy_for_slot_value(menu_item);
}

/* FILTER-CHOICES-BY-RESTRICTIONS */
Object filter_choices_by_restrictions(choices,restrictions,permitted_qm)
    Object choices, restrictions, permitted_qm;
{
    Object choice, ab_loop_list_, choice_name, allowed_p, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, restricted_choices;

    x_note_fn_call(118,107);
    choice = Nil;
    ab_loop_list_ = choices;
    choice_name = Nil;
    allowed_p = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    choice_name = menu_item_name(choice);
    allowed_p = memq_function(choice_name,restrictions) ? permitted_qm :  
	    !TRUEP(permitted_qm) ? T : Nil;
    if (allowed_p) {
	ab_loopvar__2 = slot_value_cons_1(choice,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else if (SIMPLE_VECTOR_P(choice) && EQ(ISVREF(choice,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	reclaim_partial_command(choice);
    else if (CONSP(choice))
	reclaim_slot_value(choice);
    goto next_loop;
  end_loop:
    restricted_choices = ab_loopvar_;
    goto end_1;
    restricted_choices = Qnil;
  end_1:;
    reclaim_slot_value_list_1(choices);
    reclaim_filter_list_function(restrictions);
    return VALUES_1(restricted_choices);
}

static Object Qinclude;            /* include */

/* MAP-OVER-MENU-ITEMS */
Object map_over_menu_items varargs_1(int, n)
{
    Object menu_description, function, mouse_pointer, parameters;
    Object descend_into_submenus_qm, choice_list, choice_list_is_computed_p;
    Object choices, transformed_menu_item, return_value, choice, ab_loop_list_;
    Object menu_type, gensymed_symbol, included_menu_qm;
    Object parameters_for_submenu, available_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,108);
    INIT_ARGS_nonrelocating();
    menu_description = REQUIRED_ARG_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    parameters = REQUIRED_ARG_nonrelocating();
    descend_into_submenus_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    choice_list = ISVREF(menu_description,(SI_Long)16L);
    choice_list_is_computed_p = choice_list ? (ATOM(choice_list) ? T : 
	    Nil) : Qnil;
    choices = choice_list_is_computed_p ? APPLY_2(choice_list,
	    mouse_pointer,parameters) : choice_list;
    transformed_menu_item = Nil;
    return_value = Nil;
    choice = Nil;
    ab_loop_list_ = choices;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(choice) && (EQ(CAR(choice),Qinclude) || 
	    descend_into_submenus_qm && EQ(CAR(choice),Qsubmenu))) {
	menu_type = FIRST(choice);
	gensymed_symbol = SECOND(choice);
	included_menu_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qfind_menu_description);
	parameters_for_submenu = EQ(menu_type,Qinclude) ? 
		(IFIX(length(choice)) >= (SI_Long)3L ? THIRD(choice) : 
		parameters) : parameters;
	available_qm = included_menu_qm ? 
		menu_available_p(included_menu_qm,mouse_pointer) : Qnil;
	if (available_qm)
	    return_value = map_over_menu_items(4,included_menu_qm,function,
		    mouse_pointer,parameters_for_submenu);
    }
    else {
	transformed_menu_item = transform_menu_item(4,menu_description,
		choice,mouse_pointer,choice_list_is_computed_p);
	if (transformed_menu_item)
	    return_value = FUNCALL_3(function,menu_description,
		    transformed_menu_item,mouse_pointer);
    }
    if (return_value)
	goto end_search;
    goto next_loop;
  end_loop:;
  end_search:
    if (choice_list_is_computed_p)
	reclaim_slot_value(choices);
    return VALUES_1(return_value);
}

static Object Qmenu;               /* menu */

/* OLD-STYLE-MENU-P */
Object old_style_menu_p(menu_1)
    Object menu_1;
{
    Object x2;
    char temp;

    x_note_fn_call(118,109);
    if (SIMPLE_VECTOR_P(menu_1) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(menu_1)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(menu_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(menu_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(EQ(ISVREF(ISVREF(menu_1,(SI_Long)1L),(SI_Long)1L),
		Qmenu) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qnew_menu;           /* new-menu */

/* NEW-STYLE-MENU-P */
Object new_style_menu_p(menu_1)
    Object menu_1;
{
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(118,110);
    if (SIMPLE_VECTOR_P(menu_1) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(menu_1)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(menu_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(menu_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (SIMPLE_VECTOR_P(menu_1) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(menu_1)) > (SI_Long)2L &&  
		!EQ(ISVREF(menu_1,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(menu_1,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qnew_menu,
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
		    return VALUES_1((SI_Long)0L < gensymed_symbol_2 ? T : Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-NEW-MENU-OTHER-THINGS-TO-RECLAIM-VALUE */
Object reclaim_new_menu_other_things_to_reclaim_value(things,gensymed_symbol)
    Object things, gensymed_symbol;
{
    x_note_fn_call(118,111);
    reclaim_menu_items(things);
    return VALUES_1(Nil);
}

static Object Qmenu_no_choice_function;  /* menu-no-choice-function */

/* CLEANUP-FOR-NEW-MENU */
Object cleanup_for_new_menu(new_menu)
    Object new_menu;
{
    Object frame, sub_vector_qm, method_function_qm, no_choice_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(118,112);
    frame = new_menu;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qnew_menu)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    no_choice_function_qm = get_lookup_slot_value_given_default(new_menu,
	    Qmenu_no_choice_function,Nil);
    if (no_choice_function_qm)
	return APPLY_4(no_choice_function_qm,new_menu,Nil,Nil,
		ISVREF(new_menu,(SI_Long)22L));
    else
	return VALUES_1(Nil);
}

/* NOTICE-CHOICE-MADE-ON-MENU */
Object notice_choice_made_on_menu(menu_1,choice)
    Object menu_1, choice;
{
    x_note_fn_call(118,113);
    if (new_style_menu_p(menu_1))
	return set_non_savable_lookup_slot_value(menu_1,
		Qmenu_no_choice_function,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qnew_menu_other_things_to_reclaim;  /* new-menu-other-things-to-reclaim */

/* ENSURE-THAT-MENU-ITEM-WILL-BE-RECLAIMED */
Object ensure_that_menu_item_will_be_reclaimed(menu_1,menu_item)
    Object menu_1, menu_item;
{
    Object x2, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object new_menu_other_things_to_reclaim_new_value, thing;
    char temp;

    x_note_fn_call(118,114);
    if (SIMPLE_VECTOR_P(menu_item) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(menu_item)) > (SI_Long)2L &&  
	    !EQ(ISVREF(menu_item,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(menu_item,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	slot_value_push_modify_macro_arg = make_snapshot_of_block(menu_item);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value_given_default(menu_1,
		Qnew_menu_other_things_to_reclaim,Nil);
	new_menu_other_things_to_reclaim_new_value = 
		slot_value_cons_1(car_1,cdr_1);
	return set_non_savable_lookup_slot_value(menu_1,
		Qnew_menu_other_things_to_reclaim,
		new_menu_other_things_to_reclaim_new_value);
    }
    else if (SIMPLE_VECTOR_P(menu_item) && EQ(ISVREF(menu_item,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct)) {
	slot_value_push_modify_macro_arg = menu_item;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value_given_default(menu_1,
		Qnew_menu_other_things_to_reclaim,Nil);
	new_menu_other_things_to_reclaim_new_value = 
		slot_value_cons_1(car_1,cdr_1);
	return set_non_savable_lookup_slot_value(menu_1,
		Qnew_menu_other_things_to_reclaim,
		new_menu_other_things_to_reclaim_new_value);
    }
    else {
	if (menu_item_is_command_p(menu_item)) {
	    thing = menu_item_command(menu_item);
	    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_partial_command_g2_struct) 
		    : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    slot_value_push_modify_macro_arg = menu_item_command(menu_item);
	    car_1 = slot_value_push_modify_macro_arg;
	    cdr_1 = get_lookup_slot_value_given_default(menu_1,
		    Qnew_menu_other_things_to_reclaim,Nil);
	    new_menu_other_things_to_reclaim_new_value = 
		    slot_value_cons_1(car_1,cdr_1);
	    return set_non_savable_lookup_slot_value(menu_1,
		    Qnew_menu_other_things_to_reclaim,
		    new_menu_other_things_to_reclaim_new_value);
	}
	else
	    return VALUES_1(Qnil);
    }
}

/* TRANSFORM-MENU-ITEM-AFTER-CHOICE */
Object transform_menu_item_after_choice(menu_description_qm,menu_item)
    Object menu_description_qm, menu_item;
{
    Object value, transformer_qm;
    char temp;

    x_note_fn_call(118,115);
    value = menu_item_value(menu_item);
    transformer_qm = Nil;
    temp =  !TRUEP(menu_description_qm);
    if (temp);
    else {
	transformer_qm = ISVREF(menu_description_qm,(SI_Long)9L);
	temp =  !TRUEP(transformer_qm);
    }
    if (temp)
	return VALUES_1(value);
    else
	return FUNCALL_1(transformer_qm,value);
}

static Object Kfuncall;            /* :funcall */

/* COMPUTE-MENU-TITLE */
Object compute_menu_title(menu_description,parameters)
    Object menu_description, parameters;
{
    Object title_spec, temp;

    x_note_fn_call(118,116);
    title_spec = ISVREF(menu_description,(SI_Long)2L);
    if (ATOM(title_spec))
	return VALUES_1(title_spec);
    else if (EQ(FIRST(title_spec),Kfuncall)) {
	temp = SECOND(title_spec);
	return APPLY_1(temp,parameters);
    }
    else
	return VALUES_1(Qnil);
}

static Object Ktitle;              /* :title */

static Object Qcascade_menu_item_format;  /* cascade-menu-item-format */

static Object Qformat_frame;       /* format-frame */

static Object Qmenu_item_format;   /* menu-item-format */

static Object list_constant_2;     /* # */

static Object Qmenu_table_format;  /* menu-table-format */

static Object Qmenu_table_format_for_new_g2_classic_ui;  /* menu-table-format-for-new-g2-classic-ui */

static Object Qmenu_description_of_menu;  /* menu-description-of-menu */

static Object Qmenu_choice_transformer;  /* menu-choice-transformer */

static Object Qmenu_mouse_pointer;  /* menu-mouse-pointer */

/* MAKE-MENU-FROM-DESCRIPTION */
Object make_menu_from_description varargs_1(int, n)
{
    Object menu_description, mouse_pointer;
    Object adjustment, menu_class, parameters, options, the_menu_items;
    Object the_title, item_submenu_function_qm, arg_1, arg_2, arg_3;
    Object menu_items, title_qm, single_lines_qm, capitalize_qm;
    Object strip_hyphens_qm, temp, menu_item, ab_loop_list_, ab_loop_it_;
    Object markers_exist_qm, ab_loopvar_, ab_loopvar__1, ab_loop_maxmin_fl_;
    Object number_of_columns, format_name, cascade_format, default_format;
    Object title_cells, format_1, ab_loopvar__2, item_cells, menu_1;
    Object svref_new_value;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(118,117);
    INIT_ARGS_nonrelocating();
    menu_description = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    adjustment = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    menu_class = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    options = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    the_menu_items = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    the_title = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    item_submenu_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    arg_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    arg_2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    arg_3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    LOCK(Localization_context);
    if (PUSH_UNWIND_PROTECT(0)) {
	push_item_to_end_of_current_localization_domains(Qmenu);
	menu_items = the_menu_items;
	if (menu_items);
	else
	    menu_items = compute_menu_items(menu_description,mouse_pointer,
		    parameters);
	if (menu_items) {
	    title_qm = the_title;
	    if (title_qm);
	    else
		title_qm = getf(options,Ktitle,_);
	    if (title_qm);
	    else
		title_qm = compute_menu_title(menu_description,parameters);
	    single_lines_qm = ISVREF(menu_description,(SI_Long)12L);
	    capitalize_qm = ISVREF(menu_description,(SI_Long)13L);
	    strip_hyphens_qm = ISVREF(menu_description,(SI_Long)14L);
	    temp = menu_class;
	    if (temp);
	    else
		temp = ISVREF(menu_description,(SI_Long)15L);
	    if (temp);
	    else
		temp = Qnew_menu;
	    menu_class = temp;
	    menu_item = Nil;
	    ab_loop_list_ = menu_items;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    menu_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = item_submenu_function_qm ? 
		    inline_funcall_5(item_submenu_function_qm,
		    menu_description,menu_item,arg_1,arg_2,arg_3) : 
		    menu_item_submenu_p(menu_description,menu_item);
	    if (ab_loop_it_) {
		markers_exist_qm = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    markers_exist_qm = Qnil;
	  end_1:;
	    menu_item = Nil;
	    ab_loop_list_ = menu_items;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    ab_loopvar__1 = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl_ = T;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    menu_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = menu_item_ncolumns(menu_item);
	    if (ab_loop_maxmin_fl_) {
		ab_loop_maxmin_fl_ = Nil;
		ab_loopvar_ = ab_loopvar__1;
	    }
	    else
		ab_loopvar_ = FIXNUM_MAX(ab_loopvar_,ab_loopvar__1);
	    goto next_loop_1;
	  end_loop_1:
	    number_of_columns = ab_loopvar_;
	    goto end_2;
	    number_of_columns = Qnil;
	  end_2:;
	    format_name = New_g2_classic_ui_p ? get_ui_parameter(2,
		    Qcascade_menu_item_format,adjustment) : 
		    choose_cascade_menu_item_format_per_menu_parameters();
	    cascade_format = get_instance_with_name_if_any(Qformat_frame,
		    format_name);
	    if (cascade_format);
	    else
		cascade_format = make_format_frame(format_name);
	    format_name = New_g2_classic_ui_p ? get_ui_parameter(2,
		    Qmenu_item_format,adjustment) : 
		    choose_menu_item_format_per_menu_parameters(markers_exist_qm);
	    default_format = get_instance_with_name_if_any(Qformat_frame,
		    format_name);
	    if (default_format);
	    else
		default_format = make_format_frame(format_name);
	    if (title_qm) {
		temp = slot_value_cons_1(menu_item_string(5,
			menu_description,title_qm,capitalize_qm,
			strip_hyphens_qm,parameters),Nil);
		title_cells = slot_value_cons_1(make_table_spanning_row(2,
			make_text_cell(2,temp,
			choose_menu_heading_format_per_menu_parameters(1,
			markers_exist_qm)),number_of_columns),Nil);
	    }
	    else
		title_cells = Nil;
	    menu_item = Nil;
	    ab_loop_list_ = menu_items;
	    format_1 = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    menu_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    format_1 = (item_submenu_function_qm ? 
		    TRUEP(inline_funcall_5(item_submenu_function_qm,
		    menu_description,menu_item,arg_1,arg_2,arg_3)) : 
		    TRUEP(menu_item_submenu_p(menu_description,
		    menu_item))) ? cascade_format : default_format;
	    ab_loopvar__2 = make_table_rows_for_menu_item(5,
		    menu_description,menu_item,format_1,number_of_columns,
		    parameters);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    goto next_loop_2;
	  end_loop_2:
	    item_cells = ab_loopvar_;
	    goto end_3;
	    item_cells = Qnil;
	  end_3:;
	    temp = nconc2(title_cells,item_cells);
	    menu_1 = make_or_reformat_table(5,temp,New_g2_classic_ui_p ? 
		    (memq_function(ISVREF(menu_description,(SI_Long)1L),
		    list_constant_2) ? Qmenu_table_format : 
		    Qmenu_table_format_for_new_g2_classic_ui) : 
		    Qmenu_table_format,Nil,menu_class,single_lines_qm);
	    menu_item = Nil;
	    ab_loop_list_ = menu_items;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    menu_item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ensure_that_menu_item_will_be_reclaimed(menu_1,menu_item);
	    goto next_loop_3;
	  end_loop_3:;
	    set_non_savable_lookup_slot_value(menu_1,
		    Qmenu_description_of_menu,menu_description);
	    svref_new_value = ISVREF(menu_description,(SI_Long)5L);
	    ISVREF(menu_1,(SI_Long)21L) = svref_new_value;
	    set_non_savable_lookup_slot_value(menu_1,
		    Qmenu_no_choice_function,ISVREF(menu_description,
		    (SI_Long)6L));
	    ISVREF(menu_1,(SI_Long)22L) = Nil;
	    set_non_savable_lookup_slot_value(menu_1,
		    Qmenu_choice_transformer,ISVREF(menu_description,
		    (SI_Long)9L));
	    set_non_savable_lookup_slot_value(menu_1,Qmenu_mouse_pointer,
		    reference_mouse_pointer(mouse_pointer));
	    if ( !TRUEP(the_menu_items))
		reclaim_slot_value(menu_items);
	    temp = menu_1;
	}
	else
	    temp = Nil;
	SAVE_VALUES(VALUES_1(temp));
	remove_last_item_in_current_localization_domains();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Localization_context);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qleft_aligned_cascade_menu_item_format_new_large;  /* left-aligned-cascade-menu-item-format-new-large */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_large;  /* left-arrow-left-aligned-cascade-menu-item-format-new-large */

static Object Qleft_aligned_cascade_menu_item_format_new_small;  /* left-aligned-cascade-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format_new_small;  /* left-arrow-left-aligned-cascade-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_cascade_menu_item_format;  /* left-arrow-left-aligned-cascade-menu-item-format */

static Object Qleft_aligned_cascade_menu_item_format;  /* left-aligned-cascade-menu-item-format */

static Object Qleft_aligned_menu_item_format_new_large;  /* left-aligned-menu-item-format-new-large */

static Object Qleft_arrow_left_aligned_menu_item_format_new_large;  /* left-arrow-left-aligned-menu-item-format-new-large */

static Object Qleft_aligned_menu_item_format_new_small;  /* left-aligned-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_menu_item_format_new_small;  /* left-arrow-left-aligned-menu-item-format-new-small */

static Object Qleft_arrow_left_aligned_menu_item_format;  /* left-arrow-left-aligned-menu-item-format */

static Object Qleft_aligned_menu_item_format;  /* left-aligned-menu-item-format */

/* CHANGE-ADJUSTMENT-OF-MENU */
Object change_adjustment_of_menu(menu_1,adjustment)
    Object menu_1, adjustment;
{
    Object row, ab_loop_list_, cell, ab_loop_list__1, format_name;
    Object new_format_name, new_format, x, x2, temp_1, car_arg;
    Object gensymed_symbol;
    char temp;
    Declare_special(2);

    x_note_fn_call(118,118);
    update_images_of_block(menu_1,T,T);
    row = Nil;
    ab_loop_list_ = ISVREF(menu_1,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,1);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      cell = Nil;
      ab_loop_list__1 = Row;
      PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
	format_name = Nil;
	new_format_name = Nil;
	new_format = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	Cell = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (CONSP(Cell)) {
	    x = CAR(Cell);
	    if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(x,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	format_name = temp ? get_lookup_slot_value_given_default(CAR(Cell),
		Qname_or_names_for_frame,Nil) : Nil;
	if (EQ(format_name,Qleft_aligned_cascade_menu_item_format_new_large))
	    new_format_name = 
		    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large;
	else if (EQ(format_name,
		Qleft_aligned_cascade_menu_item_format_new_small))
	    new_format_name = 
		    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small;
	else if (EQ(format_name,
		Qleft_arrow_left_aligned_cascade_menu_item_format_new_large))
	    new_format_name = Qleft_aligned_cascade_menu_item_format_new_large;
	else if (EQ(format_name,
		Qleft_arrow_left_aligned_cascade_menu_item_format_new_small))
	    new_format_name = Qleft_aligned_cascade_menu_item_format_new_small;
	else if (EQ(format_name,
		Qleft_arrow_left_aligned_cascade_menu_item_format))
	    new_format_name = Qleft_aligned_cascade_menu_item_format;
	else if (EQ(format_name,Qleft_aligned_cascade_menu_item_format))
	    new_format_name = Qleft_aligned_cascade_menu_item_format;
	else if (EQ(format_name,Qleft_aligned_menu_item_format_new_large))
	    new_format_name = 
		    Qleft_arrow_left_aligned_menu_item_format_new_large;
	else if (EQ(format_name,Qleft_aligned_menu_item_format_new_small))
	    new_format_name = 
		    Qleft_arrow_left_aligned_menu_item_format_new_small;
	else if (EQ(format_name,
		Qleft_arrow_left_aligned_menu_item_format_new_large))
	    new_format_name = Qleft_aligned_menu_item_format_new_large;
	else if (EQ(format_name,
		Qleft_arrow_left_aligned_menu_item_format_new_small))
	    new_format_name = Qleft_aligned_menu_item_format_new_small;
	else if (EQ(format_name,Qleft_arrow_left_aligned_menu_item_format))
	    new_format_name = Qleft_aligned_menu_item_format;
	else if (EQ(format_name,Qleft_aligned_menu_item_format))
	    new_format_name = Qleft_aligned_menu_item_format;
	else
	    new_format_name = Qnil;
	if (new_format_name) {
	    temp_1 = get_instance_with_name_if_any(Qformat_frame,
		    new_format_name);
	    if (temp_1);
	    else
		temp_1 = make_format_frame(new_format_name);
	    new_format = temp_1;
	}
	else
	    new_format = Nil;
	if (new_format) {
	    car_arg = Cell;
	    M_CAR(car_arg) = new_format;
	}
	goto next_loop_1;
      end_loop_1:;
      POP_SPECIAL();
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    gensymed_symbol = ISVREF(menu_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(menu_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    reformat_table_in_place(3,menu_1,T,minus(temp_1,gensymed_symbol));
    update_images_of_block(menu_1,Nil,T);
    return VALUES_1(Nil);
}

/* MAKE-TABLE-ROWS-FOR-MENU-ITEM */
Object make_table_rows_for_menu_item varargs_1(int, n)
{
    Object menu_description, menu_item, format_1, number_of_columns;
    Object parameters, item, ab_loop_list_, text_cell_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,119);
    INIT_ARGS_nonrelocating();
    menu_description = REQUIRED_ARG_nonrelocating();
    menu_item = REQUIRED_ARG_nonrelocating();
    format_1 = REQUIRED_ARG_nonrelocating();
    number_of_columns = REQUIRED_ARG_nonrelocating();
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (CONSP(menu_item) && EQ(CAR(menu_item),Qrow)) {
	item = Nil;
	ab_loop_list_ = CDR(menu_item);
	text_cell_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	text_cell_qm = menu_item_make_text_cell(menu_description,item,
		format_1,parameters);
	if (text_cell_qm ||  !TRUEP(item)) {
	    ab_loopvar__2 = slot_value_cons_1(text_cell_qm,Nil);
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
	return slot_value_cons_1(temp,Nil);
    }
    else {
	text_cell_qm = menu_item_make_text_cell(menu_description,menu_item,
		format_1,parameters);
	if (text_cell_qm)
	    return slot_value_cons_1(make_table_spanning_row(2,
		    text_cell_qm,number_of_columns),Nil);
	else
	    return make_table_spacer_cells(2,FIX((SI_Long)3L),
		    number_of_columns);
    }
}

/* MENU-ITEM-MAKE-TEXT-CELL */
Object menu_item_make_text_cell(menu_description,menu_item,format_1,parameters)
    Object menu_description, menu_item, format_1, parameters;
{
    Object capitalize_qm, strip_hyphens_qm, function_qm, string_qm, text_cell;
    Object plist, property_1, value, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(118,120);
    capitalize_qm = ISVREF(menu_description,(SI_Long)13L);
    strip_hyphens_qm = ISVREF(menu_description,(SI_Long)14L);
    function_qm = ISVREF(menu_description,(SI_Long)11L);
    string_qm = Nil;
    if ( !TRUEP(menu_item))
	return VALUES_1(Nil);
    else if (function_qm)
	return APPLY_4(function_qm,menu_description,menu_item,format_1,
		parameters);
    else {
	string_qm = menu_item_string(5,menu_description,menu_item,
		capitalize_qm,strip_hyphens_qm,parameters);
	if (string_qm) {
	    text_cell = make_text_cell(2,slot_value_cons_1(string_qm,Nil),
		    format_1);
	    plist = menu_item_plist(menu_item);
	    change_text_cell_property(text_cell,Qchoice,
		    copy_menu_item(menu_item));
	    property_1 = Nil;
	    value = Nil;
	    ab_loop_list_ = plist;
	    ab_loop_desetq_ = Nil;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    property_1 = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    value = CAR(temp);
	    change_text_cell_property(text_cell,property_1,
		    copy_for_slot_value(value));
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:;
	    return VALUES_1(text_cell);
	}
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qmenus_for_this;     /* menus-for-this */

static Object Qwhat_this_is_a_menu_for_qm;  /* what-this-is-a-menu-for? */

/* FINALIZE-MENU */
Object finalize_menu varargs_1(int, n)
{
    Object menu_1;
    Object thing, temp, slot_value_push_modify_macro_arg, car_1, cdr_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,121);
    INIT_ARGS_nonrelocating();
    menu_1 = REQUIRED_ARG_nonrelocating();
    thing = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(get_lookup_slot_value_given_default(menu_1,
	    Qmenu_mouse_pointer,Nil),(SI_Long)2L);
    ISVREF(menu_1,(SI_Long)23L) = temp;
    temp = ISVREF(get_lookup_slot_value_given_default(menu_1,
	    Qmenu_mouse_pointer,Nil),(SI_Long)3L);
    ISVREF(menu_1,(SI_Long)24L) = temp;
    if (is_block_p(thing)) {
	slot_value_push_modify_macro_arg = menu_1;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value_given_default(thing,Qmenus_for_this,Nil);
	temp = slot_value_cons_1(car_1,cdr_1);
	set_non_savable_lookup_slot_value(thing,Qmenus_for_this,temp);
	set_non_savable_lookup_slot_value(menu_1,
		Qwhat_this_is_a_menu_for_qm,thing);
    }
    return VALUES_1(menu_1);
}

/* MAKE-MENU-NAMED-FUNCTION */
Object make_menu_named_function(menu_name_or_description,mouse_pointer,
	    adjustment,class_1,parameters,options,items,title,
	    item_submenu_function_qm,arg_1,arg_2,arg_3)
    Object menu_name_or_description, mouse_pointer, adjustment, class_1;
    Object parameters, options, items, title, item_submenu_function_qm, arg_1;
    Object arg_2, arg_3;
{
    Object temp, desc_qm;

    x_note_fn_call(118,122);
    temp = mouse_pointer;
    if (temp);
    else
	temp = ISVREF(Current_workstation,(SI_Long)11L);
    mouse_pointer = temp;
    desc_qm = SYMBOLP(menu_name_or_description) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(menu_name_or_description),
	    Qfind_menu_description) : menu_name_or_description;
    if (desc_qm)
	return make_menu_from_description(12,desc_qm,mouse_pointer,
		adjustment,class_1,parameters,options,items,title,
		item_submenu_function_qm,arg_1,arg_2,arg_3);
    else
	return VALUES_1(Nil);
}

/* POST-MENU-FUNCTION */
Object post_menu_function(menu_1,choice_function,choice_function_arguments,
	    no_choice_function,what_this_is_a_menu_for,x_in_window,y_in_window)
    Object menu_1, choice_function, choice_function_arguments;
    Object no_choice_function, what_this_is_a_menu_for, x_in_window;
    Object y_in_window;
{
    Object mouse_pointer, temp, temp_1;
    Object result;

    x_note_fn_call(118,123);
    if (choice_function) {
	ISVREF(menu_1,(SI_Long)21L) = choice_function;
	ISVREF(menu_1,(SI_Long)22L) = choice_function_arguments;
    }
    if (no_choice_function)
	set_non_savable_lookup_slot_value(menu_1,Qmenu_no_choice_function,
		no_choice_function);
    finalize_menu(2,menu_1,what_this_is_a_menu_for);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)11L);
    temp = x_in_window;
    if (temp);
    else
	temp = ISVREF(mouse_pointer,(SI_Long)2L);
    temp_1 = y_in_window;
    if (temp_1);
    else
	temp_1 = ISVREF(mouse_pointer,(SI_Long)3L);
    result = VALUES_2(temp,temp_1);
    MVS_2(result,x_in_window,y_in_window);
    return expose_menu(3,menu_1,x_in_window,y_in_window);
}

/* POST-MENU-NAMED-FUNCTION */
Object post_menu_named_function(menu_name,mouse_pointer,x_in_window,
	    y_in_window,what_this_is_a_menu_for,title,choice_function,
	    choice_function_arguments)
    Object menu_name, mouse_pointer, x_in_window, y_in_window;
    Object what_this_is_a_menu_for, title, choice_function;
    Object choice_function_arguments;
{
    Object menu_qm;

    x_note_fn_call(118,124);
    menu_qm = make_menu_named_function(menu_name,mouse_pointer,Nil,Nil,Nil,
	    Nil,Nil,title,Nil,Nil,Nil,Nil);
    if (menu_qm)
	return post_menu_function(menu_qm,choice_function,
		choice_function_arguments,Nil,what_this_is_a_menu_for,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* MAKE-COMMAND-MENU */
Object make_command_menu varargs_1(int, n)
{
    Object menu_name, mouse_pointer;
    Object parameters, options, menu_items, title, menu_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,125);
    INIT_ARGS_nonrelocating();
    menu_name = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    options = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    menu_items = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    title = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    menu_qm = make_menu_named_function(menu_name,mouse_pointer,Nil,
	    Qcommand_menu,parameters,options,menu_items,title,Nil,Nil,Nil,Nil);
    if (menu_qm) {
	ISVREF(menu_qm,(SI_Long)21L) = Qcommand_menu_choice_function;
	return VALUES_1(menu_qm);
    }
    else
	return VALUES_1(Nil);
}

/* POST-COMMAND-MENU */
Object post_command_menu varargs_1(int, n)
{
    Object menu_name_or_description;
    Object mouse_pointer, x, y, thing, parameters, options, title, desc_qm;
    Object menu_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,126);
    INIT_ARGS_nonrelocating();
    menu_name_or_description = REQUIRED_ARG_nonrelocating();
    mouse_pointer = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    y = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    thing = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    options = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    title = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(mouse_pointer))
	mouse_pointer = ISVREF(Current_workstation,(SI_Long)11L);
    if ( !TRUEP(x))
	x = ISVREF(mouse_pointer,(SI_Long)2L);
    if ( !TRUEP(y))
	y = ISVREF(mouse_pointer,(SI_Long)3L);
    desc_qm = SYMBOLP(menu_name_or_description) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(menu_name_or_description),
	    Qfind_menu_description) : menu_name_or_description;
    if (desc_qm) {
	menu_qm = make_command_menu(6,desc_qm,mouse_pointer,parameters,
		options,Nil,title);
	if (menu_qm) {
	    finalize_menu(2,menu_qm,thing);
	    return expose_menu(3,menu_qm,x,y);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COMMAND-MENU-CHOICE-FUNCTION */
Object command_menu_choice_function(menu_1,menu_item,choice)
    Object menu_1, menu_item, choice;
{
    Object temp, command_qm, user_menu_choice_qm;

    x_note_fn_call(118,127);
    temp =  !TRUEP(choice) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (SYMBOLP(choice)) {
	command_qm = find_ui_command(1,choice);
	user_menu_choice_qm = CONSP(menu_item) ? (EQ(CAR(menu_item),
		Quser_menu_choice) ? T : Nil) : Qnil;
	if (user_menu_choice_qm)
	    return execute_user_menu_choice_if_possible(choice,
		    get_lookup_slot_value_given_default(menu_1,
		    Qwhat_this_is_a_menu_for_qm,Nil));
	else if (command_qm)
	    return start_ui_command(2,command_qm,
		    get_lookup_slot_value_given_default(menu_1,
		    Qmenu_mouse_pointer,Nil));
	else
	    return VALUES_1(Qnil);
    }
    else if (SIMPLE_VECTOR_P(choice) && EQ(ISVREF(choice,(SI_Long)0L),
	    Qg2_defstruct_structure_name_ui_command_g2_struct))
	return start_ui_command(2,choice,
		get_lookup_slot_value_given_default(menu_1,
		Qmenu_mouse_pointer,Nil));
    else if (SIMPLE_VECTOR_P(choice) && EQ(ISVREF(choice,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct)) {
	if (partial_command_valid_p(choice)) {
	    temp = copy_partial_command(choice);
	    return pursue_partial_command(3,temp,
		    get_lookup_slot_value_given_default(menu_1,
		    Qmenu_mouse_pointer,Nil),Qmenu);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-PARAMETER-MENU-PARTIAL-COMMAND-VALUE */
Object reclaim_parameter_menu_partial_command_value(partial_command_qm,
	    gensymed_symbol)
    Object partial_command_qm, gensymed_symbol;
{
    x_note_fn_call(118,128);
    if (partial_command_qm)
	reclaim_partial_command(partial_command_qm);
    return VALUES_1(Nil);
}

static Object Qparameter_menu_partial_command;  /* parameter-menu-partial-command */

static Object Qparameter_menu_which_argument;  /* parameter-menu-which-argument */

/* MAKE-PARAMETER-MENU */
Object make_parameter_menu varargs_1(int, n)
{
    Object menu_name, partial_command, which_argument, mouse_pointer;
    Object adjustment, parameters, options, menu_items, title;
    Object item_submenu_function_qm, arg_1, arg_2, arg_3, menu_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,129);
    INIT_ARGS_nonrelocating();
    menu_name = REQUIRED_ARG_nonrelocating();
    partial_command = REQUIRED_ARG_nonrelocating();
    which_argument = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    adjustment = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    parameters = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    options = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    menu_items = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    title = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    item_submenu_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    arg_1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    arg_2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    arg_3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    menu_qm = make_menu_named_function(menu_name,mouse_pointer,adjustment,
	    Qparameter_menu,parameters,options,menu_items,title,
	    item_submenu_function_qm,arg_1,arg_2,arg_3);
    if (menu_qm) {
	ISVREF(menu_qm,(SI_Long)21L) = Qparameter_menu_choice_function;
	set_non_savable_lookup_slot_value(menu_qm,
		Qparameter_menu_partial_command,partial_command);
	set_non_savable_lookup_slot_value(menu_qm,
		Qparameter_menu_which_argument,which_argument);
	return VALUES_1(menu_qm);
    }
    else
	return VALUES_1(Nil);
}

/* PARAMETER-MENU-CHOICE-FUNCTION */
Object parameter_menu_choice_function(menu_1,menu_item,value)
    Object menu_1, menu_item, value;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(118,130);
    temp = copy_partial_command(get_lookup_slot_value_given_default(menu_1,
	    Qparameter_menu_partial_command,Nil));
    temp_1 = menu_item_dialog(menu_item);
    temp_2 = get_lookup_slot_value_given_default(menu_1,
	    Qparameter_menu_which_argument,Nil);
    return parameter_menu_choice_function_1(temp,temp_1,temp_2,value,
	    get_lookup_slot_value_given_default(menu_1,Qmenu_mouse_pointer,
	    Nil));
}

/* PARAMETER-MENU-CHOICE-FUNCTION-1 */
Object parameter_menu_choice_function_1(partial_command,dialog_qm,
	    which_argument,value,mouse_pointer)
    Object partial_command, dialog_qm, which_argument, value, mouse_pointer;
{
    x_note_fn_call(118,131);
    if (dialog_qm) {
	FUNCALL_4(dialog_qm,partial_command,which_argument,value,
		mouse_pointer);
	return reclaim_partial_command(partial_command);
    }
    else {
	bind_partial_command_argument(partial_command,which_argument,value);
	return pursue_partial_command(3,partial_command,mouse_pointer,Qmenu);
    }
}

/* CREATE-SUBMENU */
Object create_submenu varargs_1(int, n)
{
    Object parent_menu, menu_item, mouse_pointer;
    Object adjustment, menu_description, value, explicit_submenu_qm;
    Object implicit_submenu_qm, submenu_choices, original_mouse_pointer;
    Object submenu_choice_list, submenu_name, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, menu_qm, pc, temp_1;
    Object temp_2, this_partial_command, this_argument, this_value;
    Object next_partial_command_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,132);
    INIT_ARGS_nonrelocating();
    parent_menu = REQUIRED_ARG_nonrelocating();
    menu_item = REQUIRED_ARG_nonrelocating();
    mouse_pointer = REQUIRED_ARG_nonrelocating();
    adjustment = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(old_style_menu_p(parent_menu))) {
	menu_description = get_lookup_slot_value_given_default(parent_menu,
		Qmenu_description_of_menu,Nil);
	value = menu_item_value(menu_item);
	explicit_submenu_qm = menu_item_explicit_submenu(menu_description,
		menu_item);
	implicit_submenu_qm = menu_item_submenu_p(menu_description,menu_item);
	submenu_choices = ISVREF(menu_description,(SI_Long)10L);
	original_mouse_pointer = 
		get_lookup_slot_value_given_default(parent_menu,
		Qmenu_mouse_pointer,Nil);
	submenu_choice_list = Nil;
	submenu_name = submenu_choices ? menu_description : 
		explicit_submenu_qm;
	gensymed_symbol = ISVREF(parent_menu,(SI_Long)1L);
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qcommand_menu,
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
	if (temp) {
	    submenu_choice_list = submenu_choices ? 
		    FUNCALL_3(submenu_choices,menu_description,
		    explicit_submenu_qm,original_mouse_pointer) : Nil;
	    if (explicit_submenu_qm)
		menu_qm = make_command_menu(4,submenu_name,
			original_mouse_pointer,Nil,submenu_choice_list);
	    else if (implicit_submenu_qm) {
		pc = make_initial_partial_command(value,mouse_pointer);
		menu_qm = make_parameter_submenu_for_partial_command(3,pc,
			mouse_pointer,adjustment);
	    }
	    else
		menu_qm = Qnil;
	}
	else {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qparameter_menu,
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
	    if (temp) {
		if (explicit_submenu_qm) {
		    submenu_choice_list = submenu_choices ? 
			    FUNCALL_3(submenu_choices,menu_description,
			    explicit_submenu_qm,original_mouse_pointer) : Nil;
		    temp_1 = 
			    copy_partial_command(get_lookup_slot_value_given_default(parent_menu,
			    Qparameter_menu_partial_command,Nil));
		    temp_2 = 
			    get_lookup_slot_value_given_default(parent_menu,
			    Qparameter_menu_which_argument,Nil);
		    menu_qm = make_parameter_menu(8,submenu_name,temp_1,
			    temp_2,original_mouse_pointer,adjustment,Nil,
			    Nil,submenu_choice_list);
		}
		else {
		    this_partial_command = 
			    get_lookup_slot_value_given_default(parent_menu,
			    Qparameter_menu_partial_command,Nil);
		    this_argument = 
			    get_lookup_slot_value_given_default(parent_menu,
			    Qparameter_menu_which_argument,Nil);
		    this_value = 
			    transform_menu_item_after_choice(menu_description,
			    menu_item);
		    next_partial_command_qm = 
			    partial_command_requires_submenu_after_this_choice(this_partial_command,
			    this_argument,this_value);
		    menu_qm = next_partial_command_qm ? 
			    make_parameter_submenu_for_partial_command(3,
			    next_partial_command_qm,original_mouse_pointer,
			    adjustment) : Nil;
		}
	    }
	    else
		menu_qm = Qnil;
	}
	if (submenu_choice_list)
	    reclaim_slot_value_list_1(submenu_choice_list);
	if (menu_qm) {
	    finalize_menu(2,menu_qm,
		    get_lookup_slot_value_given_default(parent_menu,
		    Qwhat_this_is_a_menu_for_qm,Nil));
	    return VALUES_1(menu_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtelewindows;        /* telewindows */

/* EXPOSE-MENU */
Object expose_menu varargs_1(int, n)
{
    Object menu_1, x_in_window_qm, y_in_window;
    Object default_x_scale_qm, default_y_scale_qm, x_for_left_adjusting_qm;
    Object x_for_right_adjusting_qm, walking_submenu_p, window;
    Object icp_output_port_qm, current_icp_port, current_icp_socket, temp;
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
    Declare_varargs_nonrelocating;
    Declare_special(12);
    Object result;

    x_note_fn_call(118,133);
    INIT_ARGS_nonrelocating();
    menu_1 = REQUIRED_ARG_nonrelocating();
    x_in_window_qm = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    default_x_scale_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    default_y_scale_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_for_left_adjusting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    x_for_right_adjusting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    walking_submenu_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    window = ISVREF(Current_workstation,(SI_Long)1L);
    if (native_pop_up_menus_p(window) && menu_works_natively_p(menu_1)) {
	icp_output_port_qm = ISVREF(window,(SI_Long)12L);
	if (icp_output_port_qm && 
		icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
	    current_icp_port = icp_output_port_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    11);
	      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		      10);
		temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)17L ? ISVREF(Current_icp_socket,
			(SI_Long)53L) : Nil;
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
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,gensymed_symbol_2);
				    }
				    if (icp_connection_open_p(Current_icp_socket) 
					    &&  
					    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						{
					temp = x_in_window_qm;
					if (temp);
					else
					    temp = x_for_left_adjusting_qm;
					if (temp);
					else
					    temp = x_for_right_adjusting_qm;
					if (temp);
					else
					    temp = FIX((SI_Long)100L);
					temp = expose_menu_remotely(window,
						menu_1,temp,y_in_window);
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
					gensymed_symbol_5 = 
						gensymed_symbol_3 - 
						gensymed_symbol_4;
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)6L);
					aref_new_value = gensymed_symbol_5 
						+ 
						DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						(SI_Long)6L),(SI_Long)0L);
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
					aref_arg_1 = 
						ISVREF(Profiling_enabled_qm,
						(SI_Long)2L);
					aref_new_value = gensymed_symbol ? 
						gensymed_symbol_1 + 
						gensymed_symbol_5 + 
						(gensymed_symbol_4 - 
						gensymed_symbol_2) : 
						gensymed_symbol_3;
					DFLOAT_ISASET_1(aref_arg_1,
						(SI_Long)0L,aref_new_value);
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
	else
	    return VALUES_1(Nil);
    }
    else
	return expose_menu_locally(menu_1,x_in_window_qm,y_in_window,
		default_x_scale_qm,default_y_scale_qm,
		x_for_left_adjusting_qm,x_for_right_adjusting_qm,
		walking_submenu_p);
}

static Object list_constant_3;     /* # */

/* MENU-WORKS-NATIVELY-P */
Object menu_works_natively_p(menu_1)
    Object menu_1;
{
    Object desc;

    x_note_fn_call(118,134);
    desc = get_lookup_slot_value_given_default(menu_1,
	    Qmenu_description_of_menu,Nil);
    return VALUES_1( !TRUEP(memq_function(ISVREF(desc,(SI_Long)1L),
	    list_constant_3)) ? T : Nil);
}

static Object Qmenu_workspace;     /* menu-workspace */

/* MAKE-MENU-WORKSPACE */
Object make_menu_workspace(menu_1)
    Object menu_1;
{
    Object workspace;

    x_note_fn_call(118,135);
    workspace = make_workspace(4,Qmenu_workspace,Nil,menu_1,FIX((SI_Long)0L));
    make_workspace_unselectable(workspace);
    return VALUES_1(workspace);
}

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qab_slot_value;      /* slot-value */

static Object Qtable_rows;         /* table-rows */

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qclose_box_x_offset;  /* close-box-x-offset */

static Object Qclose_box_y_offset;  /* close-box-y-offset */

/* EXPOSE-MENU-LOCALLY */
Object expose_menu_locally(menu_1,x_in_window_qm,y_in_window,
	    default_x_scale_qm,default_y_scale_qm,x_for_left_adjusting_qm,
	    x_for_right_adjusting_qm,walking_submenu_p)
    Object menu_1, x_in_window_qm, y_in_window, default_x_scale_qm;
    Object default_y_scale_qm, x_for_left_adjusting_qm;
    Object x_for_right_adjusting_qm, walking_submenu_p;
{
    Object menu_workspace, temp, first_row, cell_qm, ab_loop_list_;
    Object title_text_qm, ab_loop_it_, slot_value_pop_store, cons_1, next_cons;
    Object temp_2, svref_arg_2;
    char temp_1;

    x_note_fn_call(118,136);
    menu_workspace = make_menu_workspace(menu_1);
    if (walking_submenu_p)
	ISVREF(menu_workspace,(SI_Long)28L) = T;
    if (New_g2_classic_ui_p) {
	change_slot_value(3,menu_workspace,Qworkspace_background_color_qm,
		get_ui_parameter(1,Qsystem_workspace_background_color));
	temp = ISVREF(menu_1,(SI_Long)19L);
	first_row = FIRST(temp);
	cell_qm = Nil;
	ab_loop_list_ = first_row;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	cell_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (cell_qm && CONSP(cell_qm)) {
	    title_text_qm = copy_text(CDDDR(cell_qm));
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	title_text_qm = Qnil;
      end_1:;
	if (title_text_qm) {
	    temp = ISVREF(menu_1,(SI_Long)19L);
	    temp_1 = TRUEP(CDR(temp));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cell_qm = Nil;
	    ab_loop_list_ = first_row;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    cell_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = cell_qm ? (ATOM(cell_qm) ? T : Nil) : Qnil;
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    slot_value_pop_store = Nil;
	    cons_1 = ISVREF(menu_1,(SI_Long)19L);
	    if (cons_1) {
		slot_value_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = 
			    ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = cons_1;
		    temp_2 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		else {
		    temp_2 = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		    temp_2 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(menu_1,Qtable_rows);
	    SVREF(menu_1,FIX((SI_Long)19L)) = next_cons;
	    reclaim_slot_value(first_row);
	    reformat_table_in_place(3,menu_1,T,
		    FIX(IFIX(get_total_title_bar_text_width(title_text_qm)) 
		    + (SI_Long)33L));
	    change_slot_value(3,menu_workspace,Qtitle_bar_caption_text,
		    title_text_qm);
	    shrink_wrap_workspace(menu_workspace);
	}
	else if (title_text_qm)
	    reclaim_text(title_text_qm);
	temp = x_for_left_adjusting_qm || x_for_right_adjusting_qm ? 
		x_in_window_qm : FIXNUM_ADD(x_in_window_qm,
		get_ui_parameter(1,Qclose_box_x_offset));
	return post_menu_workspace(9,menu_workspace,temp,
		x_for_left_adjusting_qm || x_for_right_adjusting_qm ? 
		y_in_window : FIXNUM_ADD(y_in_window,get_ui_parameter(1,
		Qclose_box_y_offset)),Nil,default_x_scale_qm,
		default_y_scale_qm,x_for_left_adjusting_qm,
		x_for_right_adjusting_qm,walking_submenu_p);
    }
    else
	return post_menu_workspace(9,menu_workspace,x_in_window_qm,
		y_in_window,Nil,default_x_scale_qm,default_y_scale_qm,
		x_for_left_adjusting_qm,x_for_right_adjusting_qm,
		walking_submenu_p);
}

Object List_of_all_workstation_contexts = UNBOUND;

Object Context_description_named_prop = UNBOUND;

static Object Qg2_defstruct_structure_name_context_description_g2_struct;  /* g2-defstruct-structure-name::context-description-g2-struct */

static Object Qcontext_description_named;  /* context-description-named */

/* MAKE-CONTEXT-DESCRIPTION */
Object make_context_description(name,parent_1,modal,keymaps)
    Object name, parent_1, modal, keymaps;
{
    Object old_context, defstruct_g2_context_description_variable, the_array;
    Object context, sublist, key;
    SI_Long gensymed_symbol, i, ab_loop_bind_;

    x_note_fn_call(118,137);
    old_context = find_workstation_context(1,name);
    defstruct_g2_context_description_variable = Nil;
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
    defstruct_g2_context_description_variable = the_array;
    SVREF(defstruct_g2_context_description_variable,FIX((SI_Long)0L)) = 
	    Qg2_defstruct_structure_name_context_description_g2_struct;
    context = defstruct_g2_context_description_variable;
    SVREF(context,FIX((SI_Long)1L)) = name;
    SVREF(context,FIX((SI_Long)2L)) = parent_1;
    SVREF(context,FIX((SI_Long)3L)) = modal;
    SVREF(context,FIX((SI_Long)4L)) = keymaps;
    sublist = List_of_all_workstation_contexts;
    key = Nil;
  next_loop_1:
    if ( !TRUEP(sublist))
	goto end_loop_1;
    key = ISVREF(CAR(sublist),(SI_Long)1L);
    if (EQ(key,ISVREF(context,(SI_Long)1L))) {
	M_CAR(sublist) = context;
	goto end_1;
    }
    sublist = M_CDR(sublist);
    goto next_loop_1;
  end_loop_1:
    List_of_all_workstation_contexts = CONS(context,
	    List_of_all_workstation_contexts);
  end_1:;
    return mutate_global_property(name,context,Qcontext_description_named);
}

/* ADD-KEYMAP-TO-WORKSTATION-CONTEXT */
Object add_keymap_to_workstation_context(keymap_name,context_name)
    Object keymap_name, context_name;
{
    Object context_qm, svref_new_value;

    x_note_fn_call(118,138);
    context_qm = find_workstation_context(2,context_name,T);
    if (context_qm) {
	if ( !TRUEP(memq_function(keymap_name,ISVREF(context_qm,
		    (SI_Long)4L)))) {
	    svref_new_value = nconc2(ISVREF(context_qm,(SI_Long)4L),
		    LIST_1(keymap_name));
	    SVREF(context_qm,FIX((SI_Long)4L)) = svref_new_value;
	}
    }
    return VALUES_1(context_qm);
}

/* DELETE-KEYMAP-FROM-WORKSTATION-CONTEXT */
Object delete_keymap_from_workstation_context(keymap_name,context_name)
    Object keymap_name, context_name;
{
    Object context_qm, svref_new_value;

    x_note_fn_call(118,139);
    context_qm = find_workstation_context(2,context_name,T);
    if (context_qm) {
	svref_new_value = delete_eql(keymap_name,ISVREF(context_qm,
		(SI_Long)4L));
	SVREF(context_qm,FIX((SI_Long)4L)) = svref_new_value;
    }
    return VALUES_1(context_qm);
}

/* FIND-WORKSTATION-CONTEXT */
Object find_workstation_context varargs_1(int, n)
{
    Object context_or_name;
    Object warn_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(118,140);
    INIT_ARGS_nonrelocating();
    context_or_name = REQUIRED_ARG_nonrelocating();
    warn_p = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    temp =  !SYMBOLP(context_or_name) ? context_or_name : Nil;
    if (temp);
    else
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(context_or_name),
		Qcontext_description_named);
    if (temp)
	return VALUES_1(temp);
    else if (warn_p)
	return VALUES_1(Nil);
    else
	return VALUES_1(Nil);
}

/* CONTEXT-DESCRIPTION-PARENT-CONTEXT */
Object context_description_parent_context(context)
    Object context;
{
    x_note_fn_call(118,141);
    return find_workstation_context(1,ISVREF(context,(SI_Long)2L));
}

/* LOOKUP-KEY-IN-CONTEXT */
Object lookup_key_in_context(context,keycode,spot)
    Object context, keycode, spot;
{
    Object keymap_name, ab_loop_list_, keymap_qm, handler_qm, ab_loop_it_;
    Object temp;

    x_note_fn_call(118,142);
    keymap_name = Nil;
    ab_loop_list_ = ISVREF(context,(SI_Long)4L);
    keymap_qm = Nil;
    handler_qm = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    keymap_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(keymap_name),
	    Qkeymap_named);
    if (temp);
    else
	temp = T ? Nil : Qnil;
    keymap_qm = temp;
    handler_qm = keymap_qm && keymap_enabled_p(keymap_qm) ? 
	    lookup_key_in_keymap(keymap_qm,keycode,spot) : Qnil;
    ab_loop_it_ = handler_qm;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qfind_event_interpretation;  /* find-event-interpretation */

static Object Qtop_level;          /* top-level */

/* LOOKUP-KEY-IN-CONTEXT-STACK */
Object lookup_key_in_context_stack(workstation,key_code,spot)
    Object workstation, key_code, spot;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object context_name, new_style_context_qm, handler_qm, context, handler;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,143);
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
	  SVREF(temp,svref_arg_2) = Qfind_event_interpretation;
      }
      temp_1 = ISVREF(workstation,(SI_Long)17L);
      context_name = ISVREF(FIRST(temp_1),(SI_Long)1L);
      new_style_context_qm = find_workstation_context(1,context_name);
      handler_qm = Nil;
      if (new_style_context_qm) {
	  context = new_style_context_qm;
	  handler = Nil;
	next_loop:
	  if ( !TRUEP(context))
	      goto end_loop;
	  handler = lookup_key_in_context(context,key_code,spot);
	  if (handler) {
	      temp_1 = ISVREF(context,(SI_Long)1L);
	      result = VALUES_2(handler,temp_1);
	      goto end_1;
	  }
	  context = context_description_parent_context(context);
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	end_1:;
      }
      else {
	  handler_qm = lookup_key_in_context(find_workstation_context(1,
		  Qtop_level),key_code,spot);
	  if (handler_qm)
	      result = VALUES_2(handler_qm,Qtop_level);
	  else
	      result = VALUES_1(Qnil);
      }
    POP_SPECIAL();
    return result;
}

/* LOOKUP-COMMAND-IN-CONTEXT */
Object lookup_command_in_context(context,command_name)
    Object context, command_name;
{
    Object keymap_name, ab_loop_list_, keymap_qm, ab_loop_it_;

    x_note_fn_call(118,144);
    keymap_name = Nil;
    ab_loop_list_ = ISVREF(context,(SI_Long)4L);
    keymap_qm = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    keymap_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    keymap_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(keymap_name),
	    Qkeymap_named);
    ab_loop_it_ = keymap_qm && keymap_enabled_p(keymap_qm) ? 
	    lookup_command_in_keymap(keymap_qm,command_name) : Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* LOOKUP-COMMAND-IN-CONTEXT-STACK */
Object lookup_command_in_context_stack(command_name)
    Object command_name;
{
    Object temp, context_name, context_qm, context, key_pattern_qm;
    Object ab_loop_it_;

    x_note_fn_call(118,145);
    temp = ISVREF(Current_workstation,(SI_Long)17L);
    context_name = ISVREF(FIRST(temp),(SI_Long)1L);
    context_qm = find_workstation_context(1,context_name);
    if (context_qm) {
	context = context_qm;
	key_pattern_qm = Nil;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(context))
	    goto end_loop;
	key_pattern_qm = lookup_command_in_context(context,command_name);
	ab_loop_it_ = key_pattern_qm;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	context = context_description_parent_context(context);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FIND-EVENT-INTERPRETATION */
Object find_event_interpretation(event,workstation)
    Object event, workstation;
{
    Object mouse_pointer;

    x_note_fn_call(118,146);
    mouse_pointer = ISVREF(workstation,(SI_Long)11L);
    return lookup_key_in_context_stack(workstation,ISVREF(mouse_pointer,
	    (SI_Long)8L),ISVREF(mouse_pointer,(SI_Long)5L));
}

/* DEFINE-KEY */
Object define_key(context_name,parsed_key_pattern,object_class,handler)
    Object context_name, parsed_key_pattern, object_class, handler;
{
    Object context_qm, temp, gensymed_symbol, keymap_qm;

    x_note_fn_call(118,147);
    context_qm = find_workstation_context(2,context_name,T);
    temp = ISVREF(context_qm,(SI_Long)4L);
    gensymed_symbol = FIRST(temp);
    keymap_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qkeymap_named);
    if (keymap_qm)
	return bind_key_in_keymap(keymap_qm,parsed_key_pattern,
		object_class,handler,Nil);
    else
	return VALUES_1(Nil);
}

/* EVENT-BLACKBOARD-FUNCTION */
Object event_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,148);
    if (BOUNDP(Qcurrent_workstation_event))
	return VALUES_1(Current_workstation_event);
    else
	return VALUES_1(Nil);
}

/* EVENT-PLIST-BLACKBOARD-FUNCTION */
Object event_plist_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,149);
    if (BOUNDP(Qcurrent_workstation_event))
	return VALUES_1(ISVREF(Current_workstation_event,(SI_Long)10L));
    else
	return VALUES_1(Nil);
}

/* KEY-CODE-BLACKBOARD-FUNCTION */
Object key_code_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,150);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)8L));
}

/* TIMESTAMP-BLACKBOARD-FUNCTION */
Object timestamp_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,151);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)7L));
}

/* MOUSE-POINTER-BLACKBOARD-FUNCTION */
Object mouse_pointer_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,152);
    return VALUES_1(mouse_pointer);
}

/* MOUSE-DOWN-POINTER-BLACKBOARD-FUNCTION */
Object mouse_down_pointer_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,153);
    return VALUES_1(ISVREF(Current_workstation,(SI_Long)13L));
}

/* WORKSTATION-BLACKBOARD-FUNCTION */
Object workstation_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,154);
    return VALUES_1(Current_workstation);
}

/* WINDOW-BLACKBOARD-FUNCTION */
Object window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,155);
    return VALUES_1(ISVREF(Current_workstation,(SI_Long)1L));
}

/* G2-WINDOW-BLACKBOARD-FUNCTION */
Object g2_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,156);
    return VALUES_1(ISVREF(Current_workstation,(SI_Long)25L));
}

/* WORKSTATION-CONTEXT-BLACKBOARD-FUNCTION */
Object workstation_context_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object temp;

    x_note_fn_call(118,157);
    temp = ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),(SI_Long)17L);
    return VALUES_1(FIRST(temp));
}

/* WORKSTATION-CONTEXT-SPECIFICS-BLACKBOARD-FUNCTION */
Object workstation_context_specifics_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object temp, ws;

    x_note_fn_call(118,158);
    temp = ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),(SI_Long)17L);
    ws = FIRST(temp);
    return VALUES_1(ISVREF(ws,(SI_Long)2L));
}

/* SPOT-BLACKBOARD-FUNCTION */
Object spot_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,159);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)5L));
}

/* INNERMOST-SPOT-BLACKBOARD-FUNCTION */
Object innermost_spot_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,160);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)5L));
}

static Object Qpane_spot;          /* pane-spot */

static Object Qtype_description_of_type;  /* type-description-of-type */

/* PANE-BLACKBOARD-FUNCTION */
Object pane_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object pane_spot, spot;

    x_note_fn_call(118,161);
    pane_spot = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpane_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),pane_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)6L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* DETAIL-PANE-BLACKBOARD-FUNCTION */
Object detail_pane_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,162);
    return detail_pane(ISVREF(Current_workstation,(SI_Long)1L));
}

static Object Qimage_plane_spot;   /* image-plane-spot */

/* IMAGE-PLANE-BLACKBOARD-FUNCTION */
Object image_plane_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_spot, spot;

    x_note_fn_call(118,163);
    image_plane_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qimage_plane_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    image_plane_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)6L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* IMAGE-PLANE-SHOWING-BLOCK-BLACKBOARD-FUNCTION */
Object image_plane_showing_block_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_spot, spot;

    x_note_fn_call(118,164);
    image_plane_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qimage_plane_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    image_plane_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)6L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qevent_plist;        /* event-plist */

static Object Qwindow;             /* window */

/* NATIVE-WINDOW-BLACKBOARD-FUNCTION */
Object native_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object event_plist, handle_qm;

    x_note_fn_call(118,165);
    event_plist = get_magic_argument(Qevent_plist,mouse_pointer);
    handle_qm = getf(event_plist,Qwindow,_);
    if (handle_qm)
	return find_native_window(2,ISVREF(Current_workstation,
		(SI_Long)1L),handle_qm);
    else
	return VALUES_1(Nil);
}

/* NATIVE-IMAGE-PLANE-BLACKBOARD-FUNCTION */
Object native_image_plane_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object event_plist, handle_qm;

    x_note_fn_call(118,166);
    event_plist = get_magic_argument(Qevent_plist,mouse_pointer);
    handle_qm = getf(event_plist,Qwindow,_);
    if (handle_qm)
	return find_native_image_plane(ISVREF(Current_workstation,
		(SI_Long)1L),handle_qm);
    else
	return VALUES_1(Nil);
}

/* CURRENT-SELECTION-BLACKBOARD-FUNCTION */
Object current_selection_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,167);
    return current_selection(0);
}

/* X-IN-WINDOW-BLACKBOARD-FUNCTION */
Object x_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,168);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)2L));
}

/* Y-IN-WINDOW-BLACKBOARD-FUNCTION */
Object y_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,169);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)3L));
}

/* X-IN-WORKSPACE-BLACKBOARD-FUNCTION */
Object x_in_workspace_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_spot, spot;

    x_note_fn_call(118,170);
    image_plane_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qimage_plane_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    image_plane_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)8L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* Y-IN-WORKSPACE-BLACKBOARD-FUNCTION */
Object y_in_workspace_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_spot, spot;

    x_note_fn_call(118,171);
    image_plane_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qimage_plane_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    image_plane_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)9L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* X-IN-WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION */
Object x_in_workspace_of_selection_focus_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,172);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)9L));
}

/* Y-IN-WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION */
Object y_in_workspace_of_selection_focus_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,173);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)10L));
}

/* IMAGE-PLANE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION */
Object image_plane_of_selection_focus_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,174);
    return VALUES_1(ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),(SI_Long)7L));
}

/* BLOCK-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION */
Object block_of_selection_focus_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,175);
    return VALUES_1(ISVREF(mouse_pointer,(SI_Long)11L));
}

/* WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION */
Object workspace_of_selection_focus_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_qm;

    x_note_fn_call(118,176);
    image_plane_qm = ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),(SI_Long)7L);
    if (image_plane_qm)
	return VALUES_1(ISVREF(image_plane_qm,(SI_Long)5L));
    else
	return VALUES_1(Nil);
}

/* LATEST-X-IN-WINDOW-BLACKBOARD-FUNCTION */
Object latest_x_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,177);
    return VALUES_1(ISVREF(ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)2L));
}

/* LATEST-Y-IN-WINDOW-BLACKBOARD-FUNCTION */
Object latest_y_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,178);
    return VALUES_1(ISVREF(ISVREF(ISVREF(mouse_pointer,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)3L));
}

/* ORIGINAL-MOUSE-POINTER-BLACKBOARD-FUNCTION */
Object original_mouse_pointer_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame, sub_class_bit_vector, menu_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,179);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Menu_class_description,
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
	menu_qm = frame;
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    menu_qm = Qnil;
  end_1:;
    if (menu_qm)
	return get_lookup_slot_value_given_default(menu_qm,
		Qmenu_mouse_pointer,Nil);
    else
	return VALUES_1(mouse_pointer);
}

/* ORIGINAL-X-IN-WINDOW-BLACKBOARD-FUNCTION */
Object original_x_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame, sub_class_bit_vector, menu_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,180);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Menu_class_description,
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
	menu_qm = frame;
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    menu_qm = Qnil;
  end_1:;
    if (menu_qm)
	return VALUES_1(ISVREF(menu_qm,(SI_Long)23L));
    else
	return VALUES_1(ISVREF(mouse_pointer,(SI_Long)2L));
}

/* ORIGINAL-Y-IN-WINDOW-BLACKBOARD-FUNCTION */
Object original_y_in_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame, sub_class_bit_vector, menu_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,181);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Menu_class_description,
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
	menu_qm = frame;
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    menu_qm = Qnil;
  end_1:;
    if (menu_qm)
	return VALUES_1(ISVREF(menu_qm,(SI_Long)24L));
    else
	return VALUES_1(ISVREF(mouse_pointer,(SI_Long)3L));
}

/* FRAME-BLACKBOARD-FUNCTION */
Object frame_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame, x2;
    char temp;

    x_note_fn_call(118,182);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(frame);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-SUBFRAME */
Object get_subframe(frame,slot_name,defining_class_qm)
    Object frame, slot_name, defining_class_qm;
{
    Object slot_value, x2;
    char temp;

    x_note_fn_call(118,183);
    slot_value = get_slot_value_if_any_function(frame,slot_name,
	    defining_class_qm);
    if (slot_value) {
	if (SIMPLE_VECTOR_P(slot_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(slot_value);
    else
	return VALUES_1(Nil);
}

static Object Qreadout_table_spot;  /* readout-table-spot */

static Object Qattribute_name_represented_by_table_spot;  /* attribute-name-represented-by-table-spot */

static Object Qattribute_value_represented_by_table_spot;  /* attribute-value-represented-by-table-spot */

/* FRAME-OR-SUBFRAME-BLACKBOARD-FUNCTION */
Object frame_or_subframe_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, readout_table_spot, spot_1, readout_table_qm, slot_name;
    Object defining_class, frame, x2;
    char temp;

    x_note_fn_call(118,184);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    readout_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qreadout_table_spot),
	    Qtype_description_of_type);
    spot_1 = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot_1))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot_1),
	    readout_table_spot)) {
	readout_table_qm = ISVREF(spot_1,(SI_Long)4L);
	goto end_1;
    }
    spot_1 = ISVREF(spot_1,(SI_Long)2L);
    goto next_loop;
  end_loop:
    readout_table_qm = Qnil;
  end_1:;
    if (readout_table_qm)
	return VALUES_1(readout_table_qm);
    else if (ab_typep_function(spot,
	    Qattribute_name_represented_by_table_spot) || 
	    ab_typep_function(spot,
		Qattribute_value_represented_by_table_spot)) {
	slot_name = ISVREF(spot,(SI_Long)6L);
	defining_class = ISVREF(spot,(SI_Long)7L);
	frame = ISVREF(ISVREF(spot,(SI_Long)2L),(SI_Long)4L);
	return get_subframe(frame,slot_name,defining_class);
    }
    else {
	spot = ISVREF(mouse_pointer,(SI_Long)5L);
	frame = Nil;
      next_loop_1:
	if ( !TRUEP(spot))
	    goto end_loop_1;
	if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
		Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	    goto end_loop_1;
	frame = ISVREF(spot,(SI_Long)4L);
	if (frame) {
	    if (SIMPLE_VECTOR_P(frame) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(frame,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(frame,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(frame);
	spot = ISVREF(spot,(SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* SUBFRAME-BLACKBOARD-FUNCTION */
Object subframe_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, expr, slot_name, defining_class, frame;

    x_note_fn_call(118,185);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    expr = spot;
    if (ab_typep_function(expr,Qattribute_name_represented_by_table_spot) 
	    || ab_typep_function(expr,
	    Qattribute_value_represented_by_table_spot)) {
	slot_name = ISVREF(spot,(SI_Long)6L);
	defining_class = ISVREF(spot,(SI_Long)7L);
	frame = ISVREF(ISVREF(spot,(SI_Long)2L),(SI_Long)4L);
	return get_subframe(frame,slot_name,defining_class);
    }
    else
	return VALUES_1(Nil);
}

/* TABLE-BLACKBOARD-FUNCTION */
Object table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,186);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
	return VALUES_1(frame);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TABLE-BUT-NOT-KB-ITEM-BLACKBOARD-FUNCTION */
Object table_but_not_kb_item_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, frame;

    x_note_fn_call(118,187);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    if (frame && table_but_not_kb_item_p(frame))
	return VALUES_1(frame);
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TABLE-BUT-NOT-KB-ITEM-P */
Object table_but_not_kb_item_p(block)
    Object block;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,188);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
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
    if (temp)
	return VALUES_1( !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) 
		& (SI_Long)262144L) || (SI_Long)0L != (IFIX(ISVREF(block,
		(SI_Long)4L)) & (SI_Long)1L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qattribute_table_spot;  /* attribute-table-spot */

static Object Qattribute_display_spot;  /* attribute-display-spot */

static Object Qtable_header_spot;  /* table-header-spot */

static Object Qsearch_state_table_spot;  /* search-state-table-spot */

static Object Qgraph_table_spot;   /* graph-table-spot */

/* ATTRIBUTE-TABLE-BLACKBOARD-FUNCTION */
Object attribute_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_table_spot, attribute_display_spot, table_header_spot;
    Object search_state_table_spot, graph_table_spot, spot;

    x_note_fn_call(118,189);
    attribute_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_table_spot),
	    Qtype_description_of_type);
    attribute_display_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_display_spot),
	    Qtype_description_of_type);
    table_header_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_header_spot),
	    Qtype_description_of_type);
    search_state_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qsearch_state_table_spot),
	    Qtype_description_of_type);
    graph_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgraph_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_table_spot) || 
	    subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_display_spot) || 
	    subtype_p_using_type_descriptions(type_description_of(spot),
	    table_header_spot) || 
	    subtype_p_using_type_descriptions(type_description_of(spot),
	    search_state_table_spot) || 
	    subtype_p_using_type_descriptions(type_description_of(spot),
	    graph_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qshort_representation_table_spot;  /* short-representation-table-spot */

static Object Qmultiframe_table_spot;  /* multiframe-table-spot */

/* SHORT-REPRESENTATION-TABLE-BLACKBOARD-FUNCTION */
Object short_representation_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object short_representation_table_spot, multiframe_table_spot, spot;

    x_note_fn_call(118,190);
    short_representation_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qshort_representation_table_spot),
	    Qtype_description_of_type);
    multiframe_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmultiframe_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    short_representation_table_spot) || 
	    subtype_p_using_type_descriptions(type_description_of(spot),
	    multiframe_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qtable_spot;         /* table-spot */

/* TEXT-CELL-OF-TABLE-BLACKBOARD-FUNCTION */
Object text_cell_of_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object table_spot, spot, table_cell;

    x_note_fn_call(118,191);
    table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    table_spot)) {
	table_cell = ISVREF(spot,(SI_Long)18L);
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    table_cell = Qnil;
  end_1:;
    if (CONSP(table_cell))
	return VALUES_1(table_cell);
    else
	return VALUES_1(Nil);
}

/* CELL-OF-TABLE-BLACKBOARD-FUNCTION */
Object cell_of_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object table_spot, spot;

    x_note_fn_call(118,192);
    table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtable_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)18L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qattribute_represented_by_table_spot;  /* attribute-represented-by-table-spot */

static Object Qtext_box_spot;      /* text-box-spot */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* SLOT-NAME-BLACKBOARD-FUNCTION */
Object slot_name_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_represented_by_table_spot, spot, temp, text_box_spot;
    Object text_box_spot_qm, text_box, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(118,193);
    attribute_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_represented_by_table_spot)) {
	temp = ISVREF(spot,(SI_Long)6L);
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	text_box_spot = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_box_spot),
		Qtype_description_of_type);
	spot = ISVREF(mouse_pointer,(SI_Long)5L);
      next_loop_1:
	if ( !TRUEP(spot))
	    goto end_loop_1;
	if (subtype_p_using_type_descriptions(type_description_of(spot),
		text_box_spot)) {
	    text_box_spot_qm = spot;
	    goto end_2;
	}
	spot = ISVREF(spot,(SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	text_box_spot_qm = Qnil;
      end_2:;
	if (text_box_spot_qm) {
	    text_box = ISVREF(text_box_spot_qm,(SI_Long)4L);
	    gensymed_symbol = ISVREF(text_box,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
	    if (temp_1)
		return VALUES_1(Qname_or_names_for_frame);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Edit_box_class_description,(SI_Long)18L));
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
		if (temp_1)
		    return VALUES_1(Nil);
		else
		    return VALUES_1(Qbox_translation_and_text);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qtext_box;           /* text-box */

/* DEFINING-CLASS-BLACKBOARD-FUNCTION */
Object defining_class_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_represented_by_table_spot, spot, temp, text_box_spot;
    Object text_box_spot_qm, text_box, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(118,194);
    attribute_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_represented_by_table_spot)) {
	temp = ISVREF(spot,(SI_Long)7L);
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	text_box_spot = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_box_spot),
		Qtype_description_of_type);
	spot = ISVREF(mouse_pointer,(SI_Long)5L);
      next_loop_1:
	if ( !TRUEP(spot))
	    goto end_loop_1;
	if (subtype_p_using_type_descriptions(type_description_of(spot),
		text_box_spot)) {
	    text_box_spot_qm = spot;
	    goto end_2;
	}
	spot = ISVREF(spot,(SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	text_box_spot_qm = Qnil;
      end_2:;
	if (text_box_spot_qm) {
	    text_box = ISVREF(text_box_spot_qm,(SI_Long)4L);
	    gensymed_symbol = ISVREF(text_box,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
	    if (temp_1)
		return VALUES_1(Qblock);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Edit_box_class_description,(SI_Long)18L));
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
		if (temp_1)
		    return VALUES_1(Nil);
		else
		    return VALUES_1(Qtext_box);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

/* SLOT-COMPONENT-NAME?-BLACKBOARD-FUNCTION */
Object slot_component_name_qm_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_represented_by_table_spot, spot;

    x_note_fn_call(118,195);
    attribute_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_represented_by_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)8L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SLOT-COMPONENT-INDICATOR?-BLACKBOARD-FUNCTION */
Object slot_component_indicator_qm_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_represented_by_table_spot, spot;

    x_note_fn_call(118,196);
    attribute_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_represented_by_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)9L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qitem_represented_by_table_spot;  /* item-represented-by-table-spot */

/* FRAME-REPRESENTED-BY-TABLE-BLACKBOARD-FUNCTION */
Object frame_represented_by_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object item_represented_by_table_spot, spot;

    x_note_fn_call(118,197);
    item_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    item_represented_by_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qtext_spot;          /* text-spot */

/* BLOCK-SHOWING-REPRESENTATION-BLACKBOARD-FUNCTION */
Object block_showing_representation_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object text_spot, spot;

    x_note_fn_call(118,198);
    text_spot = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),text_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* BLOCK-BEING-REPRESENTED-BLACKBOARD-FUNCTION */
Object block_being_represented_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object item_represented_by_table_spot, spot, temp;
    Object type_description_of_desired_type, text_box_spot_qm;
    Object frame_represented_qm, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(118,199);
    item_represented_by_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qitem_represented_by_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    item_represented_by_table_spot)) {
	temp = ISVREF(spot,(SI_Long)4L);
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    if (temp)
	return VALUES_1(temp);
    else {
	type_description_of_desired_type = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_box_spot),
		Qtype_description_of_type);
	spot = ISVREF(mouse_pointer,(SI_Long)5L);
      next_loop_1:
	if ( !TRUEP(spot))
	    goto end_loop_1;
	if (subtype_p_using_type_descriptions(type_description_of(spot),
		type_description_of_desired_type)) {
	    text_box_spot_qm = spot;
	    goto end_2;
	}
	spot = ISVREF(spot,(SI_Long)2L);
	goto next_loop_1;
      end_loop_1:
	text_box_spot_qm = Qnil;
      end_2:;
	if (text_box_spot_qm) {
	    frame_represented_qm = ISVREF(text_box_spot_qm,(SI_Long)4L);
	    gensymed_symbol = ISVREF(frame_represented_qm,(SI_Long)1L);
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
		gensymed_symbol = ACCESS_ONCE(ISVREF(frame_represented_qm,
			(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		return VALUES_1(gensymed_symbol);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Text_box_class_description,(SI_Long)18L));
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
		if (temp_1)
		    return VALUES_1(frame_represented_qm);
		else
		    return VALUES_1(Qnil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
}

/* ATTRIBUTE-DISPLAY-BLACKBOARD-FUNCTION */
Object attribute_display_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_display_spot, spot;

    x_note_fn_call(118,200);
    attribute_display_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_display_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_display_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ATTRIBUTE-DISPLAY-TEXT-CELL-BLACKBOARD-FUNCTION */
Object attribute_display_text_cell_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object attribute_display_spot, spot;

    x_note_fn_call(118,201);
    attribute_display_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_display_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    attribute_display_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)18L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GRAPH-TABLE-BLACKBOARD-FUNCTION */
Object graph_table_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object graph_table_spot, spot;

    x_note_fn_call(118,202);
    graph_table_spot = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgraph_table_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    graph_table_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)4L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* LINE-INDEX-BLACKBOARD-FUNCTION */
Object line_index_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object text_spot, spot;

    x_note_fn_call(118,203);
    text_spot = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),text_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)9L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHARACTER-INDEX-BLACKBOARD-FUNCTION */
Object character_index_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object text_spot, spot;

    x_note_fn_call(118,204);
    text_spot = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),text_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)10L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TEXT-PLIST-BLACKBOARD-FUNCTION */
Object text_plist_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object text_spot, spot;

    x_note_fn_call(118,205);
    text_spot = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),text_spot))
	return VALUES_1(ISVREF(spot,(SI_Long)15L));
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Kunknown;            /* :unknown */

/* EDITABLE-TEXT-SPOT-P-BLACKBOARD-FUNCTION */
Object editable_text_spot_p_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object text_spot, type_description_of_desired_type, spot, image_plane;
    Object block_being_represented, block_showing_representation, slot_name;
    Object defining_class;
    char temp;

    x_note_fn_call(118,206);
    text_spot = Nil;
    type_description_of_desired_type = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_spot),
	    Qtype_description_of_type);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (subtype_p_using_type_descriptions(type_description_of(spot),
	    type_description_of_desired_type)) {
	text_spot = spot;
	goto end_1;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    text_spot = Qnil;
  end_1:;
    if (text_spot) {
	if (EQ(Kunknown,ISVREF(text_spot,(SI_Long)8L))) {
	    SVREF(text_spot,FIX((SI_Long)8L)) = Nil;
	    type_description_of_desired_type = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qattribute_value_represented_by_table_spot),
		    Qtype_description_of_type);
	    spot = ISVREF(mouse_pointer,(SI_Long)5L);
	  next_loop_1:
	    if ( !TRUEP(spot))
		goto end_loop_1;
	    if (subtype_p_using_type_descriptions(type_description_of(spot),
		    type_description_of_desired_type)) {
		temp = TRUEP(spot);
		goto end_2;
	    }
	    spot = ISVREF(spot,(SI_Long)2L);
	    goto next_loop_1;
	  end_loop_1:
	    temp = TRUEP(Qnil);
	  end_2:;
	    if (temp);
	    else {
		type_description_of_desired_type = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtext_box_spot),
			Qtype_description_of_type);
		spot = ISVREF(mouse_pointer,(SI_Long)5L);
	      next_loop_2:
		if ( !TRUEP(spot))
		    goto end_loop_2;
		if (subtype_p_using_type_descriptions(type_description_of(spot),
			type_description_of_desired_type)) {
		    temp = TRUEP(spot);
		    goto end_3;
		}
		spot = ISVREF(spot,(SI_Long)2L);
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(Qnil);
	      end_3:;
	    }
	    if (temp) {
		image_plane = image_plane_blackboard_function(mouse_pointer);
		block_being_represented = 
			block_being_represented_blackboard_function(mouse_pointer);
		block_showing_representation = 
			block_showing_representation_blackboard_function(mouse_pointer);
		slot_name = slot_name_blackboard_function(mouse_pointer);
		defining_class = 
			defining_class_blackboard_function(mouse_pointer);
		if (image_plane && block_being_represented && 
			block_showing_representation && slot_name ? 
			(slot_editable_p(block_being_represented,slot_name,
			defining_class) || editable_virtual_attribute_p(3,
			block_being_represented,slot_name,defining_class)) 
			&& text_visible_p(ISVREF(text_spot,(SI_Long)14L),
			ISVREF(text_spot,(SI_Long)15L),ISVREF(image_plane,
			(SI_Long)11L),ISVREF(image_plane,(SI_Long)12L)) : 
			TRUEP(Nil))
		    SVREF(text_spot,FIX((SI_Long)8L)) = text_spot;
	    }
	}
	return VALUES_1(ISVREF(text_spot,(SI_Long)8L));
    }
    else
	return VALUES_1(Nil);
}

/* IMAGE-PLANE-OF-MOUSE-POINTER */
Object image_plane_of_mouse_pointer(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane_qm;

    x_note_fn_call(118,207);
    image_plane_qm = image_plane_blackboard_function(mouse_pointer);
    return VALUES_1(image_plane_qm);
}

/* FRAME-FOR-SELECTION-BLACKBOARD-FUNCTION */
Object frame_for_selection_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,208);
    return compute_frame_for_selection(mouse_pointer);
}

static Object Qworkspace;          /* workspace */

static Object Qedit_workspace;     /* edit-workspace */

/* COMPUTE-FRAME-FOR-SELECTION */
Object compute_frame_for_selection(mouse_pointer)
    Object mouse_pointer;
{
    Object graph_table_qm, short_representation_table_qm, attribute_display_qm;
    Object attribute_table_qm, frame_qm, workspace_qm, temp, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(118,209);
    graph_table_qm = graph_table_blackboard_function(mouse_pointer);
    short_representation_table_qm = 
	    short_representation_table_blackboard_function(mouse_pointer);
    attribute_display_qm = 
	    attribute_display_blackboard_function(mouse_pointer);
    attribute_table_qm = attribute_table_blackboard_function(mouse_pointer);
    frame_qm = frame_blackboard_function(mouse_pointer);
    workspace_qm = find_frame_of_class_in_mouse_pointer(mouse_pointer,
	    Qworkspace);
    temp = graph_table_qm;
    if (temp);
    else
	temp = short_representation_table_qm;
    if (temp);
    else
	temp = attribute_display_qm;
    if (temp);
    else
	temp = attribute_table_qm;
    if (temp)
	return VALUES_1(temp);
    else {
	if (workspace_qm) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qedit_workspace,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
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
	if (temp_1)
	    return VALUES_1(workspace_qm);
	else
	    return VALUES_1(frame_qm);
    }
}

/* MOST-INTERESTING-FRAME-BLACKBOARD-FUNCTION */
Object most_interesting_frame_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,210);
    return most_interesting_frame(mouse_pointer);
}

/* MOST-INTERESTING-FRAME-IN-SPOT */
Object most_interesting_frame_in_spot(spot)
    Object spot;
{
    Object frame_star, frame, expr, temp;

    x_note_fn_call(118,211);
    frame_star = Nil;
    frame = Nil;
  next_loop:
    if ( !TRUEP(spot))
	goto end_loop;
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct))
	goto end_loop;
    frame = ISVREF(spot,(SI_Long)4L);
    expr = spot;
    if (ab_typep_function(expr,Qshort_representation_table_spot) || 
	    ab_typep_function(expr,Qmultiframe_table_spot) || 
	    ab_typep_function(expr,Qattribute_display_spot) || 
	    ab_typep_function(expr,Qattribute_table_spot))
	return VALUES_1(frame);
    else {
	temp = frame_star;
	if (temp);
	else
	    temp = frame;
	frame_star = temp;
    }
    spot = ISVREF(spot,(SI_Long)2L);
    goto next_loop;
  end_loop:
    return VALUES_1(frame_star);
    return VALUES_1(Qnil);
}

/* MOST-INTERESTING-FRAME */
Object most_interesting_frame(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(118,212);
    return most_interesting_frame_in_spot(ISVREF(mouse_pointer,(SI_Long)5L));
}

/* THING-TO-SELECT-BLACKBOARD-FUNCTION */
Object thing_to_select_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, block, attribute_table_qm, table_qm, cell_of_table_qm;
    Object short_representation_table_qm, the_table_qm, x2;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,213);
    spot = spot_blackboard_function(mouse_pointer);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    attribute_table_qm = attribute_table_blackboard_function(mouse_pointer);
    table_qm = table_blackboard_function(mouse_pointer);
    cell_of_table_qm = cell_of_table_blackboard_function(mouse_pointer);
    short_representation_table_qm = 
	    short_representation_table_blackboard_function(mouse_pointer);
    if (spot && block) {
	the_table_qm = short_representation_table_qm;
	if (the_table_qm);
	else
	    the_table_qm = attribute_table_qm;
	if (the_table_qm);
	else
	    the_table_qm = table_qm;
	if (EQ(structure_class(spot),
		Qattribute_name_represented_by_table_spot) && the_table_qm)
	    return VALUES_1(the_table_qm);
	else if (EQ(structure_class(spot),
		Qattribute_value_represented_by_table_spot)) {
	    if (selectable_table_cell_p(the_table_qm,cell_of_table_qm))
		return prepare_table_cell(cell_of_table_qm,the_table_qm);
	    else
		return VALUES_1(the_table_qm);
	}
	else {
	    if (SIMPLE_VECTOR_P(block) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(block,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(block,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
		return VALUES_1(ISVREF(block,(SI_Long)21L));
	    else {
		temp_1 = the_table_qm;
		if (temp_1)
		    return VALUES_1(temp_1);
		else
		    return VALUES_1(block);
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

/* PREPARE-TABLE-CELL */
Object prepare_table_cell(cell_qm,table)
    Object cell_qm, table;
{
    x_note_fn_call(118,214);
    if (cell_qm)
	return VALUES_1(cell_qm);
    else
	return VALUES_1(Nil);
}

/* GET-TABLE-FOR-CELL */
Object get_table_for_cell(cell)
    Object cell;
{
    Object frame_qm, representation, ab_loop_list_, ab_loop_it_;
    Object sub_class_bit_vector, row, ab_loop_list__1, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(118,215);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,1);
      if (CONSP(Cell)) {
	  frame_qm = get_slot_represented_by_text_cell_if_any(Cell);
	  if (frame_qm) {
	      representation = Nil;
	      ab_loop_list_ = ISVREF(frame_qm,(SI_Long)9L);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      representation = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      sub_class_bit_vector = ISVREF(ISVREF(representation,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
		  row = Nil;
		  ab_loop_list__1 = ISVREF(representation,(SI_Long)19L);
		  PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
		    ab_loop_it_ = Nil;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_1;
		    Row = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    ab_loop_it_ = memq_function(Cell,Row);
		    if (ab_loop_it_) {
			temp = TRUEP(ab_loop_it_);
			goto end_1;
		    }
		    goto next_loop_1;
		  end_loop_1:
		    temp = TRUEP(Qnil);
		  end_1:;
		  POP_SPECIAL();
	      }
	      else
		  temp = TRUEP(Nil);
	      ab_loop_it_ = temp ? representation : Nil;
	      if (ab_loop_it_) {
		  result = VALUES_1(ab_loop_it_);
		  goto end_2;
	      }
	      goto next_loop;
	    end_loop:
	      result = VALUES_1(Qnil);
	    end_2:;
	  }
	  else
	      result = VALUES_1(Nil);
      }
      else {
	  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(Cell,(SI_Long)14L));
	  gensymed_symbol_3 = gensymed_symbol_3 ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	  result = VALUES_1(gensymed_symbol_3);
      }
    POP_SPECIAL();
    return result;
}

/* CELL-IN-TABLE-P */
Object cell_in_table_p(cell,table)
    Object cell, table;
{
    Object row, ab_loop_list_, ab_loop_it_, element, ab_loop_list__1;
    Declare_special(2);
    Object result;

    x_note_fn_call(118,216);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,1);
      row = Nil;
      ab_loop_list_ = ISVREF(table,(SI_Long)19L);
      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	Row = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	element = Nil;
	ab_loop_list__1 = Row;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQ(Cell,element) ? T : Nil;
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
    POP_SPECIAL();
    return result;
}

/* SELECTED-IMAGE-PLANE-BLACKBOARD-FUNCTION */
Object selected_image_plane_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object workstation;

    x_note_fn_call(118,217);
    workstation = workstation_blackboard_function(mouse_pointer);
    if (workstation)
	return VALUES_1(ISVREF(workstation,(SI_Long)51L));
    else
	return VALUES_1(Nil);
}

/* SELECTED-WORKSPACE-BLACKBOARD-FUNCTION */
Object selected_workspace_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object workstation;

    x_note_fn_call(118,218);
    workstation = workstation_blackboard_function(mouse_pointer);
    if (workstation)
	return selected_workspace(1,workstation);
    else
	return VALUES_1(Nil);
}

/* SELECTED-NATIVE-WINDOW-BLACKBOARD-FUNCTION */
Object selected_native_window_blackboard_function(mouse_pointer)
    Object mouse_pointer;
{
    Object workstation;

    x_note_fn_call(118,219);
    workstation = workstation_blackboard_function(mouse_pointer);
    if (workstation)
	return selected_native_window_qm(workstation);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Compute_menu_items_list, Qcompute_menu_items_list);

/* COLLECT-MENU-ITEM */
Object collect_menu_item(menu_description,menu_item,mouse_pointer)
    Object menu_description, menu_item, mouse_pointer;
{
    x_note_fn_call(118,220);
    Compute_menu_items_list = slot_value_cons_1(menu_item,
	    Compute_menu_items_list);
    return VALUES_1(Nil);
}

static Object Qcollect_menu_item;  /* collect-menu-item */

/* COMPUTE-MENU-ITEMS */
Object compute_menu_items(menu_description,mouse_pointer,parameters)
    Object menu_description, mouse_pointer, parameters;
{
    Object compute_menu_items_list, available_choices, restriction_type;
    Object choice_restrictions, permitted_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,221);
    compute_menu_items_list = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Compute_menu_items_list,Qcompute_menu_items_list,compute_menu_items_list,
	    0);
      map_over_menu_items(4,menu_description,
	      SYMBOL_FUNCTION(Qcollect_menu_item),mouse_pointer,parameters);
      available_choices = nreverse(Compute_menu_items_list);
      restriction_type = ISVREF(menu_description,(SI_Long)7L);
      result = compute_restrictions(restriction_type,mouse_pointer);
      MVS_2(result,choice_restrictions,permitted_qm);
      result = filter_choices_by_restrictions(available_choices,
	      choice_restrictions,permitted_qm);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_restrictions_alist, Qcached_restrictions_alist);

Object Main_menu_restriction_type_exceptions = UNBOUND;

Object Workspace_menu_restriction_type_exceptions = UNBOUND;

static Object Qmain_menu;          /* main-menu */

static Object Qworkspace_menu;     /* workspace-menu */

/* GET-MENU-CHOICE-LIST */
Object get_menu_choice_list(menu_description)
    Object menu_description;
{
    Object choice_list, choices, choice, ab_loop_list_, include_clause_qm;
    Object included_choices, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object default_restriction_type_qm, cmd_qm, restriction_type, restrictions;
    Object choice_name, allowed_p, command_qm, temp;

    x_note_fn_call(118,222);
    choice_list = ISVREF(menu_description,(SI_Long)16L);
    if (ATOM(choice_list))
	choices = Nil;
    else {
	choice = Nil;
	ab_loop_list_ = choice_list;
	include_clause_qm = Nil;
	included_choices = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	choice = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	include_clause_qm = CONSP(choice) ? (EQ(FIRST(choice),Qinclude) ? 
		T : Nil) : Qnil;
	included_choices = include_clause_qm && 
		menu_description_named(SECOND(choice)) ? 
		get_menu_choice_list(menu_description_named(SECOND(choice))) 
		: Nil;
	if (include_clause_qm) {
	    ab_loopvar__2 = included_choices;
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	}
	else {
	    ab_loopvar__2 = slot_value_cons_1(copy_menu_item(choice),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	choices = ab_loopvar_;
	goto end_1;
	choices = Qnil;
      end_1:;
    }
    default_restriction_type_qm = ISVREF(menu_description,(SI_Long)7L);
    choice = Nil;
    ab_loop_list_ = choices;
    cmd_qm = Nil;
    restriction_type = Nil;
    restrictions = Nil;
    choice_name = Nil;
    allowed_p = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    choice = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    cmd_qm = ATOM(choice) ? 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(choice),
	    Qui_command_named) : Qnil;
    if ( !TRUEP(cmd_qm))
	command_qm = Nil;
    else if (SIMPLE_VECTOR_P(cmd_qm) && EQ(ISVREF(cmd_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_partial_command_g2_struct))
	command_qm = find_ui_command(1,ISVREF(cmd_qm,(SI_Long)1L));
    else if (SYMBOLP(cmd_qm))
	command_qm = find_ui_command(1,cmd_qm);
    else if (SIMPLE_VECTOR_P(cmd_qm) && EQ(ISVREF(cmd_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_ui_command_g2_struct))
	command_qm = cmd_qm;
    else
	command_qm = Qnil;
    if (command_qm && memq_function(ISVREF(command_qm,(SI_Long)1L),
	    Main_menu_restriction_type_exceptions))
	restriction_type = Qmain_menu;
    else if (command_qm && memq_function(ISVREF(command_qm,(SI_Long)1L),
	    Workspace_menu_restriction_type_exceptions))
	restriction_type = Qworkspace_menu;
    else
	restriction_type = default_restriction_type_qm;
    temp = assq_function(restriction_type,Cached_restrictions_alist);
    restrictions = CDR(temp);
    choice_name = cmd_qm ? ISVREF(cmd_qm,(SI_Long)2L) : menu_item_name(choice);
    allowed_p = memq_function(choice_name,CDR(restrictions)) ? 
	    CAR(restrictions) :  !TRUEP(CAR(restrictions)) ? T : Nil;
    if (allowed_p) {
	ab_loopvar__2 = slot_value_cons_1(copy_menu_item(choice),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    reclaim_menu_items(choices);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Name_for_find_menu_item, Qname_for_find_menu_item);

/* FIND-MENU-ITEM-INTERNAL */
Object find_menu_item_internal(menu_description,menu_item,mouse_pointer)
    Object menu_description, menu_item, mouse_pointer;
{
    Object temp;

    x_note_fn_call(118,223);
    temp = Name_for_find_menu_item;
    if (EQ(temp,menu_item_name(menu_item)))
	return VALUES_1(menu_item);
    else {
	reclaim_menu_item(menu_item);
	return VALUES_1(Nil);
    }
}

static Object Qfind_menu_item_internal;  /* find-menu-item-internal */

/* FIND-MENU-ITEM */
Object find_menu_item(menu_name,menu_description,mouse_pointer,parameters)
    Object menu_name, menu_description, mouse_pointer, parameters;
{
    Object name_for_find_menu_item;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,224);
    name_for_find_menu_item = menu_name;
    PUSH_SPECIAL_WITH_SYMBOL(Name_for_find_menu_item,Qname_for_find_menu_item,name_for_find_menu_item,
	    0);
      result = map_over_menu_items(5,menu_description,
	      SYMBOL_FUNCTION(Qfind_menu_item_internal),mouse_pointer,
	      parameters,T);
    POP_SPECIAL();
    return result;
}

/* COMMAND-PERMITTED-P */
Object command_permitted_p(command_name,frame_qm)
    Object command_name, frame_qm;
{
    x_note_fn_call(118,225);
    return VALUES_1( !TRUEP(command_is_excluded_absolutely_p(2,
	    command_name,frame_qm)) ? T : Nil);
}

static Object Qitem_menu;          /* item-menu */

static Object Qtable_menu;         /* table-menu */

/* COMPUTE-RESTRICTIONS */
Object compute_restrictions(restriction_type,mouse_pointer)
    Object restriction_type, mouse_pointer;
{
    Object frame_qm, slot_name_qm, temp;

    x_note_fn_call(118,226);
    frame_qm = frame_blackboard_function(mouse_pointer);
    slot_name_qm = slot_name_blackboard_function(mouse_pointer);
    if (EQ(restriction_type,Qmain_menu))
	return compute_main_menu_restrictions();
    else if (EQ(restriction_type,Qworkspace_menu) || EQ(restriction_type,
	    Qitem_menu))
	return compute_menu_restrictions_for_workspace(frame_qm);
    else if (EQ(restriction_type,Qtable_menu)) {
	if (display_table_p(frame_qm))
	    return compute_menu_restrictions_for_workspace(frame_qm);
	else if (frame_qm) {
	    temp = get_alias_for_slot_name_if_any(slot_name_qm,frame_qm);
	    if (temp);
	    else
		temp = slot_name_qm;
	    return compute_menu_restrictions_for_click_on_table(frame_qm,
		    temp,Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* RECLAIM-MENU-ITEMS */
Object reclaim_menu_items(menu_items)
    Object menu_items;
{
    Object menu_item, ab_loop_list_;

    x_note_fn_call(118,227);
    menu_item = Nil;
    ab_loop_list_ = menu_items;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    menu_item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_menu_item(menu_item);
    goto next_loop;
  end_loop:;
    return reclaim_slot_value_list_1(menu_items);
}

/* NAME-OF-USER-MENU-CHOICE? */
Object name_of_user_menu_choice_qm(name,frame)
    Object name, frame;
{
    Object superior_class, class_description, ab_loop_list_, ab_loop_it_;
    Object user_menu_choice, ab_loop_list__1, symbol_qm;

    x_note_fn_call(118,228);
    if (ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)16L)) {
	superior_class = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(frame,
		(SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	user_menu_choice = Nil;
	ab_loop_list__1 = lookup_kb_specific_property_value(superior_class,
		User_menu_choices_for_this_class_kbprop);
	symbol_qm = Nil;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	user_menu_choice = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	symbol_qm = ISVREF(user_menu_choice,(SI_Long)20L);
	ab_loop_it_ = EQ(symbol_qm,name) ? T : Nil;
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

/* USER-MENU-CHOICE-POTENTIALLY-RUNNABLE-P */
Object user_menu_choice_potentially_runnable_p(name,frame)
    Object name, frame;
{
    Object user_menu_choice_qm;

    x_note_fn_call(118,229);
    user_menu_choice_qm = get_user_menu_choice_or_choice_symbols(2,frame,name);
    if (user_menu_choice_qm)
	return VALUES_1(ISVREF(user_menu_choice_qm,(SI_Long)24L));
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_hot_spot_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_hot_spot_states, Qchain_of_available_hot_spot_states);

DEFINE_VARIABLE_WITH_SYMBOL(Hot_spot_state_count, Qhot_spot_state_count);

Object Chain_of_available_hot_spot_states_vector = UNBOUND;

/* HOT-SPOT-STATE-STRUCTURE-MEMORY-USAGE */
Object hot_spot_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(118,230);
    temp = Hot_spot_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)18L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-HOT-SPOT-STATE-COUNT */
Object outstanding_hot_spot_state_count()
{
    Object def_structure_hot_spot_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(118,231);
    gensymed_symbol = IFIX(Hot_spot_state_count);
    def_structure_hot_spot_state_variable = Chain_of_available_hot_spot_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_hot_spot_state_variable))
	goto end_loop;
    def_structure_hot_spot_state_variable = 
	    ISVREF(def_structure_hot_spot_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-HOT-SPOT-STATE-1 */
Object reclaim_hot_spot_state_1(hot_spot_state)
    Object hot_spot_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(118,232);
    inline_note_reclaim_cons(hot_spot_state,Nil);
    structure_being_reclaimed = hot_spot_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(hot_spot_state,(SI_Long)1L));
      SVREF(hot_spot_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(hot_spot_state,(SI_Long)2L));
      SVREF(hot_spot_state,FIX((SI_Long)2L)) = Nil;
      cancel_identified_drawing_activity_if_any(ISVREF(hot_spot_state,
	      (SI_Long)13L));
      SVREF(hot_spot_state,FIX((SI_Long)13L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_hot_spot_states_vector,
	    IFIX(Current_thread_index));
    SVREF(hot_spot_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_hot_spot_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = hot_spot_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-HOT-SPOT-STATE */
Object reclaim_structure_for_hot_spot_state(hot_spot_state)
    Object hot_spot_state;
{
    x_note_fn_call(118,233);
    return reclaim_hot_spot_state_1(hot_spot_state);
}

static Object Qg2_defstruct_structure_name_hot_spot_state_g2_struct;  /* g2-defstruct-structure-name::hot-spot-state-g2-struct */

/* MAKE-PERMANENT-HOT-SPOT-STATE-STRUCTURE-INTERNAL */
Object make_permanent_hot_spot_state_structure_internal()
{
    Object def_structure_hot_spot_state_variable;
    Object defstruct_g2_hot_spot_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(118,234);
    def_structure_hot_spot_state_variable = Nil;
    atomic_incff_symval(Qhot_spot_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_hot_spot_state_variable = Nil;
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
	defstruct_g2_hot_spot_state_variable = the_array;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_hot_spot_state_g2_struct;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_hot_spot_state_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_hot_spot_state_variable = 
		defstruct_g2_hot_spot_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_hot_spot_state_variable);
}

/* MAKE-HOT-SPOT-STATE-1 */
Object make_hot_spot_state_1(block_with_selection_focus_of_workstation_context,
	    image_plane_with_selection_focus_of_workstation_context,
	    reference_number_of_image_plane,method_function_of_hot_spot,
	    info_of_hot_spot,left_edge_in_focus_of_hot_spot,
	    top_edge_in_focus_of_hot_spot,right_edge_in_focus_of_hot_spot,
	    bottom_edge_in_focus_of_hot_spot)
    Object block_with_selection_focus_of_workstation_context;
    Object image_plane_with_selection_focus_of_workstation_context;
    Object reference_number_of_image_plane, method_function_of_hot_spot;
    Object info_of_hot_spot, left_edge_in_focus_of_hot_spot;
    Object top_edge_in_focus_of_hot_spot, right_edge_in_focus_of_hot_spot;
    Object bottom_edge_in_focus_of_hot_spot;
{
    Object def_structure_hot_spot_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(118,235);
    def_structure_hot_spot_state_variable = 
	    ISVREF(Chain_of_available_hot_spot_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_hot_spot_state_variable) {
	temp = Chain_of_available_hot_spot_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_hot_spot_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_hot_spot_state_g2_struct;
    }
    else
	def_structure_hot_spot_state_variable = 
		make_permanent_hot_spot_state_structure_internal();
    inline_note_allocate_cons(def_structure_hot_spot_state_variable,Nil);
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)3L)) = 
	    block_with_selection_focus_of_workstation_context;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)4L)) = 
	    image_plane_with_selection_focus_of_workstation_context;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)5L)) = 
	    reference_number_of_image_plane;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)6L)) = 
	    method_function_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)7L)) = 
	    info_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)8L)) = 
	    left_edge_in_focus_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)9L)) = 
	    top_edge_in_focus_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)10L)) = 
	    right_edge_in_focus_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)11L)) = 
	    bottom_edge_in_focus_of_hot_spot;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)2L)) = temp;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)13L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)14L)) = temp;
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)15L)) = T;
    temp = ISVREF(image_plane_with_selection_focus_of_workstation_context,
	    (SI_Long)5L);
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)16L)) = temp;
    temp = ISVREF(ISVREF(Current_workstation,(SI_Long)11L),(SI_Long)7L);
    SVREF(def_structure_hot_spot_state_variable,FIX((SI_Long)17L)) = temp;
    return VALUES_1(def_structure_hot_spot_state_variable);
}

/* CALL-HOT-SPOT-METHOD */
Object call_hot_spot_method(method_name,inside_p)
    Object method_name, inside_p;
{
    Object hot_spot_state, temp, svref_new_value;

    x_note_fn_call(118,236);
    hot_spot_state = Specific_structure_for_current_workstation_context;
    temp = SYMBOL_FUNCTION(ISVREF(hot_spot_state,(SI_Long)6L));
    FUNCALL_2(temp,method_name,inside_p);
    svref_new_value = inside_p ? T : Nil;
    return VALUES_1(SVREF(hot_spot_state,FIX((SI_Long)15L)) = svref_new_value);
}

static Object Kexit_hot_spot;      /* :exit-hot-spot */

static Object Kenter_hot_spot;     /* :enter-hot-spot */

static Object Kidle;               /* :idle */

/* MOUSE-MOTION-IN-HOT-SPOT */
Object mouse_motion_in_hot_spot(mouse_pointer)
    Object mouse_pointer;
{
    Object hot_spot_state, mouse_pointer_1, x_in_workspace_of_selection_focus;
    Object y_in_workspace_of_selection_focus, recently_inside_of_hot_spot_p;
    Object left, top, right, bottom, now_inside_hot_spot_p;

    x_note_fn_call(118,237);
    hot_spot_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    x_in_workspace_of_selection_focus = 
	    x_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    y_in_workspace_of_selection_focus = 
	    y_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    if (hot_spot_state && mouse_pointer_1 && 
	    x_in_workspace_of_selection_focus && 
	    y_in_workspace_of_selection_focus) {
	recently_inside_of_hot_spot_p = ISVREF(hot_spot_state,(SI_Long)15L);
	left = ISVREF(hot_spot_state,(SI_Long)8L);
	top = ISVREF(hot_spot_state,(SI_Long)9L);
	right = ISVREF(hot_spot_state,(SI_Long)10L);
	bottom = ISVREF(hot_spot_state,(SI_Long)11L);
	now_inside_hot_spot_p = FIXNUM_LE(left,
		x_in_workspace_of_selection_focus) && 
		FIXNUM_LT(x_in_workspace_of_selection_focus,right) && 
		FIXNUM_LE(top,y_in_workspace_of_selection_focus) ? 
		(FIXNUM_LT(y_in_workspace_of_selection_focus,bottom) ? T : 
		Nil) : Qnil;
	if (recently_inside_of_hot_spot_p &&  !TRUEP(now_inside_hot_spot_p))
	    return call_hot_spot_method(Kexit_hot_spot,now_inside_hot_spot_p);
	else if ( !TRUEP(recently_inside_of_hot_spot_p) && 
		now_inside_hot_spot_p)
	    return call_hot_spot_method(Kenter_hot_spot,now_inside_hot_spot_p);
	else
	    return call_hot_spot_method(Kidle,now_inside_hot_spot_p);
    }
    else
	return VALUES_1(Nil);
}

static Object Kmouse_up;           /* :mouse-up */

static Object Kunwind;             /* :unwind */

static Object Qhot_spot;           /* hot-spot */

/* MOUSE-UP-IN-HOT-SPOT */
Object mouse_up_in_hot_spot(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, hot_spot_state;

    x_note_fn_call(118,238);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    hot_spot_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && hot_spot_state) {
	mouse_motion_in_hot_spot(mouse_pointer_1);
	call_hot_spot_method(Kmouse_up,ISVREF(hot_spot_state,(SI_Long)15L));
	call_hot_spot_method(Kunwind,ISVREF(hot_spot_state,(SI_Long)15L));
	return return_from_current_workstation_context(1,Qhot_spot);
    }
    else
	return VALUES_1(Nil);
}

static Object Kaborted;            /* :aborted */

/* ABORT-HOT-SPOT */
Object abort_hot_spot(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, hot_spot_state;

    x_note_fn_call(118,239);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    hot_spot_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && hot_spot_state) {
	call_hot_spot_method(Kabort,ISVREF(hot_spot_state,(SI_Long)15L));
	SVREF(hot_spot_state,FIX((SI_Long)7L)) = Kaborted;
	call_hot_spot_method(Kunwind,ISVREF(hot_spot_state,(SI_Long)15L));
	return abort_current_workstation_context(Qhot_spot);
    }
    else
	return VALUES_1(Nil);
}

Object Scrolling_autorepeat_interval = UNBOUND;

/* SCROLLING-HEARTBEAT */
Object scrolling_heartbeat(workstation)
    Object workstation;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, mouse_pointer;
    Object hot_spot_state;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(118,240);
    SAVE_STACK();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
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
			ISVREF(Current_workstation_window,(SI_Long)17L);
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
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				mouse_pointer = ISVREF(Current_workstation,
					(SI_Long)13L);
				hot_spot_state = 
					workstation_context_specifics_blackboard_function(mouse_pointer);
				if (hot_spot_state) {
				    SVREF(hot_spot_state,
					    FIX((SI_Long)12L)) = T;
				    if ( !TRUEP(ISVREF(hot_spot_state,
					    (SI_Long)13L)))
					SAVE_VALUES(push_back_mouse_motion_event());
				    else
					SAVE_VALUES(VALUES_1(Nil));
				}
				else
				    SAVE_VALUES(VALUES_1(Nil));
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

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qscrolling_heartbeat;  /* scrolling-heartbeat */

/* START-OR-RESTART-SCROLLING-HEARTBEAT */
Object start_or_restart_scrolling_heartbeat()
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object mouse_pointer, hot_spot_state, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value, task;
    char svref_new_value_1;
    double realtime_interval_of_heartbeat, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(118,241);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(Current_workstation,(SI_Long)36L);
    if (CAS_SVREF(Current_workstation,(SI_Long)36L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    hot_spot_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (hot_spot_state)
	SVREF(hot_spot_state,FIX((SI_Long)12L)) = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	realtime_interval_of_heartbeat = 
		DOUBLE_FLOAT_TO_DOUBLE(Scrolling_autorepeat_interval);
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(Current_workstation,(SI_Long)36L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = g2ext_unix_time_as_float() + 
		realtime_interval_of_heartbeat;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qscrolling_heartbeat;
	temp = SYMBOL_FUNCTION(Qscrolling_heartbeat);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	temp = Current_workstation;
	SVREF(task,FIX((SI_Long)13L)) = temp;
	new_1 = task;
	if (CAS_SVREF(Current_workstation,(SI_Long)36L,old,new_1)) {
	    if (old) {
		if (EQ(old,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(old,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(old);
		inline_note_reclaim_cons(old,Nil);
		structure_being_reclaimed = old;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(old,(SI_Long)9L));
		  SVREF(old,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = old;
	    }
	    future_task_schedule_2(new_1);
	    result = VALUES_1(new_1);
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
	goto next_loop_1;
      end_loop_1:
	result = VALUES_1(Qnil);
      end_2:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Kmouse_down;         /* :mouse-down */

static Object Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct;  /* g2-defstruct-structure-name::stepper-of-scroll-bar-spot-g2-struct */

static Object Qdo_scrolling;       /* do-scrolling */

/* SCROLL-BAR-HOT-SPOT-METHOD */
Object scroll_bar_hot_spot_method(method,inside_qm)
    Object method, inside_qm;
{
    Object mouse_pointer, hot_spot_state, spot, block, workspace;
    Object gensym_window, image_plane, gensymed_symbol;
    Object structure_being_reclaimed, temp, svref_arg_2, ui_command, temp_1;
    Declare_special(1);

    x_note_fn_call(118,242);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    hot_spot_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    spot = spot_blackboard_function(mouse_pointer);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    gensym_window = window_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (hot_spot_state && spot && block && workspace && gensym_window && 
	    image_plane) {
	if (EQ(method,Kunwind)) {
	    gensymed_symbol = Nil;
	  next_loop:
	    gensymed_symbol = ISVREF(Current_workstation,(SI_Long)36L);
	    if (CAS_SVREF(Current_workstation,(SI_Long)36L,gensymed_symbol,
		    Nil)) {
		if (gensymed_symbol) {
		    if (EQ(gensymed_symbol,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(gensymed_symbol,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
		    inline_note_reclaim_cons(gensymed_symbol,Nil);
		    structure_being_reclaimed = gensymed_symbol;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(gensymed_symbol,
			      (SI_Long)9L));
		      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol;
		}
		return VALUES_1(T);
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (EQ(method,Kmouse_down) || EQ(method,Kenter_hot_spot)) {
	    if (inside_qm) {
		highlight_color_of_frame_spot(spot,image_plane,T);
		if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
			Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct)) 
			    {
		    ui_command = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdo_scrolling),
			    Qui_command_named);
		    if (ui_command) {
			gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			temp_1 = SYMBOLP(gensymed_symbol) ? 
				SYMBOL_FUNCTION(gensymed_symbol) : 
				gensymed_symbol;
			FUNCALL_3(temp_1,spot,block,image_plane);
		    }
		    suppress_autorepeat_until_drawing_is_done(gensym_window,
			    workspace,hot_spot_state);
		    temp = ISVREF(ISVREF(Current_workstation,(SI_Long)11L),
			    (SI_Long)7L);
		    SVREF(hot_spot_state,FIX((SI_Long)17L)) = temp;
		    return start_or_restart_scrolling_heartbeat();
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(method,Kidle)) {
	    if (ISVREF(hot_spot_state,(SI_Long)12L) && mouse_still_down_p()) {
		if ( !TRUEP(ISVREF(hot_spot_state,(SI_Long)13L))) {
		    ui_command = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdo_scrolling),
			    Qui_command_named);
		    if (ui_command) {
			gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			temp_1 = SYMBOLP(gensymed_symbol) ? 
				SYMBOL_FUNCTION(gensymed_symbol) : 
				gensymed_symbol;
			FUNCALL_3(temp_1,spot,block,image_plane);
		    }
		    suppress_autorepeat_until_drawing_is_done(gensym_window,
			    workspace,hot_spot_state);
		    return start_or_restart_scrolling_heartbeat();
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(method,Kabort) || EQ(method,Kmouse_up) || EQ(method,
		Kexit_hot_spot)) {
	    if (EQ(method,Kexit_hot_spot) || inside_qm)
		return highlight_color_of_frame_spot(spot,image_plane,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Kfinished;           /* :finished */

static Object Kcanceled;           /* :canceled */

/* ENABLE-AUTOREPEAT-AFTER-DRAWING */
Object enable_autorepeat_after_drawing(identified_drawing_activity,
	    kind_of_continuation)
    Object identified_drawing_activity, kind_of_continuation;
{
    Object hot_spot_state, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(118,243);
    SAVE_STACK();
    if (EQ(kind_of_continuation,Kfinished)) {
	hot_spot_state = ISVREF(identified_drawing_activity,(SI_Long)8L);
	SVREF(hot_spot_state,FIX((SI_Long)13L)) = Nil;
	if (ISVREF(hot_spot_state,(SI_Long)12L)) {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = 
			ISVREF(ISVREF(identified_drawing_activity,
			(SI_Long)6L),(SI_Long)2L);
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
					push_back_mouse_motion_event();
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
	}
    }
    else if (EQ(kind_of_continuation,Kcanceled));
    result = remove_identified_drawing_activity(identified_drawing_activity,
	    kind_of_continuation);
    RESTORE_STACK();
    return result;
}

static Object Qenable_autorepeat_after_drawing;  /* enable-autorepeat-after-drawing */

/* SUPPRESS-AUTOREPEAT-UNTIL-DRAWING-IS-DONE */
Object suppress_autorepeat_until_drawing_is_done(gensym_window,workspace,
	    hot_spot_state)
    Object gensym_window, workspace, hot_spot_state;
{
    Object svref_new_value;

    x_note_fn_call(118,244);
    svref_new_value = start_identified_drawing_activity(4,gensym_window,
	    Nil,SYMBOL_FUNCTION(Qenable_autorepeat_after_drawing),
	    hot_spot_state);
    SVREF(hot_spot_state,FIX((SI_Long)13L)) = svref_new_value;
    return ping_workspace_drawing(workspace,ISVREF(hot_spot_state,
	    (SI_Long)13L));
}

static Object Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct;  /* g2-defstruct-structure-name::elevator-of-scroll-bar-spot-g2-struct */

static Object Qline;               /* line */

static Object Qgensym_scroll_bar_elevator_frame_component;  /* gensym-scroll-bar-elevator-frame-component */

static Object Qleft;               /* left */

static Object Qgensym_left_scroll_arrow_frame_component;  /* gensym-left-scroll-arrow-frame-component */

static Object Qup;                 /* up */

static Object Qgensym_up_scroll_arrow_frame_component;  /* gensym-up-scroll-arrow-frame-component */

static Object Qright;              /* right */

static Object Qgensym_right_scroll_arrow_frame_component;  /* gensym-right-scroll-arrow-frame-component */

static Object Qdown;               /* down */

static Object Qgensym_down_scroll_arrow_frame_component;  /* gensym-down-scroll-arrow-frame-component */

static Object Qdark_grey;          /* dark-grey */

static Object Qlight_grey;         /* light-grey */

static Object Qface_color;         /* face-color */

/* HIGHLIGHT-COLOR-OF-FRAME-SPOT */
Object highlight_color_of_frame_spot(spot,image_plane,highlight_on_qm)
    Object spot, image_plane, highlight_on_qm;
{
    Object orientation, frame_widget_name, temp, entity_used_for_rubber_stamp;
    Object from_color, to_color;

    x_note_fn_call(118,245);
    if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
	    Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct) 
	    || EQ(Qline,ISVREF(spot,(SI_Long)11L))) {
	orientation = Nil;
	if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
		Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct))
	    frame_widget_name = Qgensym_scroll_bar_elevator_frame_component;
	else {
	    temp = ISVREF(spot,(SI_Long)10L);
	    if (EQ(temp,Qleft))
		frame_widget_name = Qgensym_left_scroll_arrow_frame_component;
	    else if (EQ(temp,Qup))
		frame_widget_name = Qgensym_up_scroll_arrow_frame_component;
	    else if (EQ(temp,Qright))
		frame_widget_name = Qgensym_right_scroll_arrow_frame_component;
	    else if (EQ(temp,Qdown))
		frame_widget_name = Qgensym_down_scroll_arrow_frame_component;
	    else
		frame_widget_name = Qnil;
	}
	entity_used_for_rubber_stamp = 
		getf(lookup_rubber_stamp_set_of_frame_widget(frame_widget_name),
		orientation,_);
	if (entity_used_for_rubber_stamp);
	else
	    entity_used_for_rubber_stamp = 
		    SECOND(Resize_box_rubber_stamp_widget);
	from_color = Qdark_grey;
	to_color = Qlight_grey;
	if (highlight_on_qm) {
	    from_color = Qlight_grey;
	    to_color = Qdark_grey;
	}
	return change_color_in_rubber_stamp(ISVREF(image_plane,
		(SI_Long)5L),entity_used_for_rubber_stamp,ISVREF(spot,
		(SI_Long)6L),ISVREF(spot,(SI_Long)7L),ISVREF(spot,
		(SI_Long)8L),ISVREF(spot,(SI_Long)9L),Qface_color,
		from_color,to_color);
    }
    else
	return VALUES_1(Nil);
}

static Object Qscroll_bar_hot_spot_method;  /* scroll-bar-hot-spot-method */

/* ENTER-HOT-SPOT-STATE-UPON-FRAME-COMPONENT */
Object enter_hot_spot_state_upon_frame_component(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, frame_component_spot, block, image_plane;
    Object hot_spot_state;

    x_note_fn_call(118,246);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    frame_component_spot = innermost_spot_blackboard_function(mouse_pointer);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && frame_component_spot && block && image_plane) {
	hot_spot_state = make_hot_spot_state_1(block,image_plane,
		ISVREF(image_plane,(SI_Long)1L),
		Qscroll_bar_hot_spot_method,Nil,
		ISVREF(frame_component_spot,(SI_Long)6L),
		ISVREF(frame_component_spot,(SI_Long)7L),
		ISVREF(frame_component_spot,(SI_Long)8L),
		ISVREF(frame_component_spot,(SI_Long)9L));
	enter_context_in_current_workstation(3,Qhot_spot,hot_spot_state,T);
	call_hot_spot_method(Kmouse_down,T);
	return VALUES_1(hot_spot_state);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_elevator_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_elevator_states, Qchain_of_available_elevator_states);

DEFINE_VARIABLE_WITH_SYMBOL(Elevator_state_count, Qelevator_state_count);

Object Chain_of_available_elevator_states_vector = UNBOUND;

/* ELEVATOR-STATE-STRUCTURE-MEMORY-USAGE */
Object elevator_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(118,247);
    temp = Elevator_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ELEVATOR-STATE-COUNT */
Object outstanding_elevator_state_count()
{
    Object def_structure_elevator_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(118,248);
    gensymed_symbol = IFIX(Elevator_state_count);
    def_structure_elevator_state_variable = Chain_of_available_elevator_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_elevator_state_variable))
	goto end_loop;
    def_structure_elevator_state_variable = 
	    ISVREF(def_structure_elevator_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ELEVATOR-STATE-1 */
Object reclaim_elevator_state_1(elevator_state)
    Object elevator_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(118,249);
    inline_note_reclaim_cons(elevator_state,Nil);
    structure_being_reclaimed = elevator_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(elevator_state,(SI_Long)1L));
      SVREF(elevator_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(elevator_state,(SI_Long)2L));
      SVREF(elevator_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_elevator_states_vector,
	    IFIX(Current_thread_index));
    SVREF(elevator_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_elevator_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = elevator_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ELEVATOR-STATE */
Object reclaim_structure_for_elevator_state(elevator_state)
    Object elevator_state;
{
    x_note_fn_call(118,250);
    return reclaim_elevator_state_1(elevator_state);
}

static Object Qg2_defstruct_structure_name_elevator_state_g2_struct;  /* g2-defstruct-structure-name::elevator-state-g2-struct */

/* MAKE-PERMANENT-ELEVATOR-STATE-STRUCTURE-INTERNAL */
Object make_permanent_elevator_state_structure_internal()
{
    Object def_structure_elevator_state_variable;
    Object defstruct_g2_elevator_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(118,251);
    def_structure_elevator_state_variable = Nil;
    atomic_incff_symval(Qelevator_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_elevator_state_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_elevator_state_variable = the_array;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_elevator_state_g2_struct;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_elevator_state_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_elevator_state_variable = 
		defstruct_g2_elevator_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_elevator_state_variable);
}

/* MAKE-ELEVATOR-STATE-1 */
Object make_elevator_state_1(block_with_selection_focus_of_workstation_context,
	    image_plane_with_selection_focus_of_workstation_context,
	    reference_number_of_image_plane)
    Object block_with_selection_focus_of_workstation_context;
    Object image_plane_with_selection_focus_of_workstation_context;
    Object reference_number_of_image_plane;
{
    Object def_structure_elevator_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(118,252);
    def_structure_elevator_state_variable = 
	    ISVREF(Chain_of_available_elevator_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_elevator_state_variable) {
	temp = Chain_of_available_elevator_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_elevator_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_elevator_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_elevator_state_g2_struct;
    }
    else
	def_structure_elevator_state_variable = 
		make_permanent_elevator_state_structure_internal();
    inline_note_allocate_cons(def_structure_elevator_state_variable,Nil);
    SVREF(def_structure_elevator_state_variable,FIX((SI_Long)3L)) = 
	    block_with_selection_focus_of_workstation_context;
    SVREF(def_structure_elevator_state_variable,FIX((SI_Long)4L)) = 
	    image_plane_with_selection_focus_of_workstation_context;
    SVREF(def_structure_elevator_state_variable,FIX((SI_Long)5L)) = 
	    reference_number_of_image_plane;
    SVREF(def_structure_elevator_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_elevator_state_variable,FIX((SI_Long)2L)) = temp;
    ISVREF(def_structure_elevator_state_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)8L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)10L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)11L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)12L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_elevator_state_variable,(SI_Long)14L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_elevator_state_variable);
}

static Object Qelevator;           /* elevator */

/* ENTER-ELEVATOR-STATE */
Object enter_elevator_state(mouse_pointer)
    Object mouse_pointer;
{
    Object elevator_spot, block, image_plane, x_in_workspace, y_in_workspace;
    Object elevator_state, svref_new_value;

    x_note_fn_call(118,253);
    elevator_spot = innermost_spot_blackboard_function(mouse_pointer);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    if (elevator_spot && block && image_plane && x_in_workspace && 
	    y_in_workspace) {
	elevator_state = make_elevator_state_1(block,image_plane,
		ISVREF(image_plane,(SI_Long)1L));
	svref_new_value = FIXNUM_MINUS(x_in_workspace,ISVREF(elevator_spot,
		(SI_Long)6L));
	SVREF(elevator_state,FIX((SI_Long)6L)) = svref_new_value;
	svref_new_value = FIXNUM_MINUS(y_in_workspace,ISVREF(elevator_spot,
		(SI_Long)7L));
	SVREF(elevator_state,FIX((SI_Long)7L)) = svref_new_value;
	enter_context_in_current_workstation(3,Qelevator,elevator_state,T);
	highlight_color_of_frame_spot(elevator_spot,image_plane,T);
	revisit_traveling_elevator(T,Nil,x_in_workspace,y_in_workspace);
	svref_new_value = ISVREF(elevator_state,(SI_Long)11L);
	SVREF(elevator_state,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = ISVREF(elevator_state,(SI_Long)12L);
	SVREF(elevator_state,FIX((SI_Long)10L)) = svref_new_value;
	return VALUES_1(elevator_state);
    }
    else
	return VALUES_1(Nil);
}

/* ABORT-ELEVATOR-STATE */
Object abort_elevator_state(mouse_pointer)
    Object mouse_pointer;
{
    Object x_in_workspace, y_in_workspace, spot, image_plane;

    x_note_fn_call(118,254);
    x_in_workspace = 
	    x_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    y_in_workspace = 
	    y_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    if (x_in_workspace && y_in_workspace) {
	revisit_traveling_elevator(Nil,T,x_in_workspace,y_in_workspace);
	mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
	spot = spot_blackboard_function(mouse_pointer);
	image_plane = image_plane_blackboard_function(mouse_pointer);
	if (spot && image_plane)
	    highlight_color_of_frame_spot(spot,image_plane,Nil);
	return abort_current_workstation_context(Qelevator);
    }
    else
	return VALUES_1(Nil);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object Qvertical;           /* vertical */

static Object Qposition_of_horizontal_elevator;  /* position-of-horizontal-elevator */

static Object Qposition_of_vertical_elevator;  /* position-of-vertical-elevator */

static Object Kdraw_as_soon_as_possible;  /* :draw-as-soon-as-possible */

/* MOUSE-UP-IN-ELEVATOR-STATE */
Object mouse_up_in_elevator_state(mouse_pointer)
    Object mouse_pointer;
{
    Object x_in_workspace, y_in_workspace, elevator_state, elevator_spot;
    Object block, image_plane, workspace, current_drawing_priority;
    Object elevator_shaft_spot, old_horizontal_position_of_block;
    Object old_vertical_position_of_block, new_horizontal_position_of_block;
    Object new_vertical_position_of_block;
    char vertical_qm;
    Declare_special(1);

    x_note_fn_call(118,255);
    x_in_workspace = 
	    x_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    y_in_workspace = 
	    y_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    if (x_in_workspace && y_in_workspace) {
	mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
	elevator_state = 
		workstation_context_specifics_blackboard_function(mouse_pointer);
	elevator_spot = spot_blackboard_function(mouse_pointer);
	block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
	image_plane = image_plane_blackboard_function(mouse_pointer);
	workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,
		Qworkspace);
	if (elevator_state && elevator_spot && block && image_plane && 
		workspace) {
	    current_drawing_priority = Kdraw_as_late_as_possible;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_priority,Qcurrent_drawing_priority,current_drawing_priority,
		    0);
	      revisit_traveling_elevator(Nil,T,x_in_workspace,y_in_workspace);
	      highlight_color_of_frame_spot(elevator_spot,image_plane,Nil);
	      elevator_shaft_spot = ISVREF(elevator_spot,(SI_Long)2L);
	      vertical_qm = EQ(Qvertical,ISVREF(elevator_shaft_spot,
		      (SI_Long)10L));
	      old_horizontal_position_of_block = 
		      get_lookup_slot_value_given_default(block,
		      Qposition_of_horizontal_elevator,FIX((SI_Long)0L));
	      old_vertical_position_of_block = 
		      get_lookup_slot_value_given_default(block,
		      Qposition_of_vertical_elevator,FIX((SI_Long)0L));
	      new_horizontal_position_of_block = vertical_qm ? 
		      old_horizontal_position_of_block : 
		      ISVREF(elevator_state,(SI_Long)8L);
	      new_vertical_position_of_block = vertical_qm ? 
		      ISVREF(elevator_state,(SI_Long)8L) : 
		      old_vertical_position_of_block;
	      if ( !(FIXNUM_EQ(ISVREF(elevator_state,(SI_Long)9L),
		      ISVREF(elevator_state,(SI_Long)11L)) && 
		      FIXNUM_EQ(ISVREF(elevator_state,(SI_Long)10L),
		      ISVREF(elevator_state,(SI_Long)12L)) || 
		      FIXNUM_EQ(new_horizontal_position_of_block,
		      old_horizontal_position_of_block) && 
		      FIXNUM_EQ(new_vertical_position_of_block,
		      old_vertical_position_of_block))) {
		  move_elevator(block,new_horizontal_position_of_block,
			  new_vertical_position_of_block);
		  delta_position_of_block_scroll(block,image_plane,
			  FIXNUM_MINUS(new_horizontal_position_of_block,
			  old_horizontal_position_of_block),
			  FIXNUM_MINUS(new_vertical_position_of_block,
			  old_vertical_position_of_block));
	      }
	    POP_SPECIAL();
	    if (EQ(Current_drawing_priority,Kdraw_as_soon_as_possible))
		force_process_drawing();
	    return return_from_current_workstation_context(1,Qelevator);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-MOTION-IN-ELEVATOR-STATE */
Object mouse_motion_in_elevator_state(mouse_pointer)
    Object mouse_pointer;
{
    Object x_in_workspace, y_in_workspace;

    x_note_fn_call(118,256);
    x_in_workspace = 
	    x_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    y_in_workspace = 
	    y_in_workspace_of_selection_focus_blackboard_function(mouse_pointer);
    if (x_in_workspace && y_in_workspace)
	return revisit_traveling_elevator(Nil,Nil,x_in_workspace,
		y_in_workspace);
    else
	return VALUES_1(Nil);
}

static Object Qblack;              /* black */

static Object Qlight_gray;         /* light-gray */

/* REVISIT-TRAVELING-ELEVATOR */
Object revisit_traveling_elevator(first_call_qm,last_call_qm,
	    new_x_in_workspace,new_y_in_workspace)
    Object first_call_qm, last_call_qm, new_x_in_workspace, new_y_in_workspace;
{
    Object mouse_pointer, elevator_state, elevator_spot, image_plane;
    Object last_elevator_position, new_elevator_position, move_it_qm;
    Object erase_it_qm, draw_it_qm, left_edge_of_ghost, top_edge_of_ghost;
    Object right_edge_of_ghost, bottom_edge_of_ghost;
    Object result;

    x_note_fn_call(118,257);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    elevator_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    elevator_spot = innermost_spot_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (elevator_state && elevator_spot && image_plane) {
	last_elevator_position = ISVREF(elevator_state,(SI_Long)8L);
	new_elevator_position = 
		elevator_position_given_workspace_point(new_x_in_workspace,
		new_y_in_workspace);
	move_it_qm =  !FIXNUM_EQ(last_elevator_position,
		new_elevator_position) ? T : Nil;
	if (move_it_qm);
	else
	    move_it_qm = first_call_qm;
	if (move_it_qm);
	else
	    move_it_qm = last_call_qm;
	if (first_call_qm)
	    erase_it_qm = Nil;
	else if (last_call_qm)
	    erase_it_qm = T;
	else
	    erase_it_qm = move_it_qm;
	draw_it_qm = last_call_qm ? Nil : move_it_qm;
	if (erase_it_qm)
	    update_ghost_elevator(Qblack,Qlight_gray);
	if (move_it_qm) {
	    SVREF(elevator_state,FIX((SI_Long)8L)) = new_elevator_position;
	    result = edges_of_dragged_elevator();
	    MVS_4(result,left_edge_of_ghost,top_edge_of_ghost,
		    right_edge_of_ghost,bottom_edge_of_ghost);
	    SVREF(elevator_state,FIX((SI_Long)11L)) = left_edge_of_ghost;
	    SVREF(elevator_state,FIX((SI_Long)12L)) = top_edge_of_ghost;
	    SVREF(elevator_state,FIX((SI_Long)13L)) = right_edge_of_ghost;
	    SVREF(elevator_state,FIX((SI_Long)14L)) = bottom_edge_of_ghost;
	}
	if (draw_it_qm)
	    return update_ghost_elevator(Qlight_gray,Qblack);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-GHOST-ELEVATOR */
Object update_ghost_elevator(from_color,to_color)
    Object from_color, to_color;
{
    Object mouse_pointer, image_plane, elevator_state, temp, temp_1;

    x_note_fn_call(118,258);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    elevator_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (image_plane && elevator_state) {
	temp = ISVREF(image_plane,(SI_Long)5L);
	temp_1 = 
		lookup_rubber_stamp_set_of_frame_widget(Qgensym_scroll_bar_elevator_frame_component);
	return change_color_in_rubber_stamp(temp,SECOND(temp_1),
		ISVREF(elevator_state,(SI_Long)11L),ISVREF(elevator_state,
		(SI_Long)12L),ISVREF(elevator_state,(SI_Long)13L),
		ISVREF(elevator_state,(SI_Long)14L),Qface_color,from_color,
		to_color);
    }
    else
	return VALUES_1(Nil);
}

/* EDGES-OF-DRAGGED-ELEVATOR */
Object edges_of_dragged_elevator()
{
    Object mouse_pointer, elevator_state, elevator_spot, elevator_shaft_spot;

    x_note_fn_call(118,259);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    elevator_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    elevator_spot = innermost_spot_blackboard_function(mouse_pointer);
    if (elevator_state && elevator_spot) {
	elevator_shaft_spot = ISVREF(elevator_spot,(SI_Long)2L);
	return edges_of_elevator(ISVREF(elevator_shaft_spot,(SI_Long)10L),
		ISVREF(elevator_shaft_spot,(SI_Long)6L),
		ISVREF(elevator_shaft_spot,(SI_Long)7L),
		ISVREF(elevator_shaft_spot,(SI_Long)8L),
		ISVREF(elevator_shaft_spot,(SI_Long)9L),
		ISVREF(elevator_state,(SI_Long)8L));
    }
    else
	return VALUES_1(Nil);
}

/* ELEVATOR-POSITION-GIVEN-WORKSPACE-POINT */
Object elevator_position_given_workspace_point(x_in_workspace,y_in_workspace)
    Object x_in_workspace, y_in_workspace;
{
    Object mouse_pointer, elevator_state, elevator_spot, elevator_shaft_spot;
    SI_Long height, width, shaft_width, shaft_height, temp, temp_1, pin_y;
    SI_Long pinned_offset, pin_x;
    char vertical_qm;

    x_note_fn_call(118,260);
    mouse_pointer = ISVREF(Current_workstation,(SI_Long)13L);
    elevator_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    elevator_spot = innermost_spot_blackboard_function(mouse_pointer);
    if (elevator_state && elevator_spot) {
	elevator_shaft_spot = ISVREF(elevator_spot,(SI_Long)2L);
	vertical_qm = EQ(Qvertical,ISVREF(elevator_shaft_spot,(SI_Long)10L));
	height = IFIX(FIXNUM_MINUS(ISVREF(elevator_shaft_spot,(SI_Long)9L),
		ISVREF(elevator_shaft_spot,(SI_Long)7L))) - (SI_Long)2L;
	width = IFIX(FIXNUM_MINUS(ISVREF(elevator_shaft_spot,(SI_Long)8L),
		ISVREF(elevator_shaft_spot,(SI_Long)6L))) - (SI_Long)2L;
	shaft_width = vertical_qm ? width : height;
	shaft_height = vertical_qm ? height : width;
	x_in_workspace = FIXNUM_MINUS(x_in_workspace,ISVREF(elevator_state,
		(SI_Long)6L));
	y_in_workspace = FIXNUM_MINUS(y_in_workspace,ISVREF(elevator_state,
		(SI_Long)7L));
	if (vertical_qm) {
	    temp = IFIX(ISVREF(elevator_shaft_spot,(SI_Long)7L));
	    temp_1 = IFIX(ISVREF(elevator_shaft_spot,(SI_Long)9L)) - 
		    shaft_width;
	    temp_1 = MIN(IFIX(y_in_workspace),temp_1);
	    pin_y = MAX(temp,temp_1);
	    pinned_offset = pin_y - IFIX(ISVREF(elevator_shaft_spot,
		    (SI_Long)7L));
	}
	else {
	    temp = IFIX(ISVREF(elevator_shaft_spot,(SI_Long)6L));
	    temp_1 = IFIX(ISVREF(elevator_shaft_spot,(SI_Long)8L)) - 
		    shaft_width;
	    temp_1 = MIN(IFIX(x_in_workspace),temp_1);
	    pin_x = MAX(temp,temp_1);
	    pinned_offset = pin_x - IFIX(ISVREF(elevator_shaft_spot,
		    (SI_Long)6L));
	}
	return position_of_elevator_as_scale_given_offset(FIX(pinned_offset),
		FIX(shaft_width),FIX(shaft_height));
    }
    else
	return VALUES_1(Nil);
}

/* DISTANCE-FROM-POINT-TO-TABLE */
Object distance_from_point_to_table(x,y,table,image_plane)
    Object x, y, table, image_plane;
{
    Object gensymed_symbol, scale;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, x_in_workspace, value;
    SI_Long unshifted_result, temp, temp_1, y_in_workspace;

    x_note_fn_call(118,261);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(table,(SI_Long)16L),(SI_Long)24L));
    x_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
    scale = ISVREF(image_plane,(SI_Long)11L);
    value = x_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    temp = IFIX(minus(FIX(gensymed_symbol_1 + gensymed_symbol_2),x));
    temp_1 = MAX((SI_Long)0L,temp);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(table,(SI_Long)16L),(SI_Long)25L));
    y_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
    scale = ISVREF(image_plane,(SI_Long)12L);
    value = y_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    temp = IFIX(minus(FIX(gensymed_symbol_1 + gensymed_symbol_2),y));
    temp_1 = MAX(temp_1,temp);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(table,(SI_Long)16L),(SI_Long)26L));
    x_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
    scale = ISVREF(image_plane,(SI_Long)11L);
    value = x_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    temp = IFIX(minus(x,FIX(gensymed_symbol_1 + gensymed_symbol_2)));
    temp_1 = MAX(temp_1,temp);
    gensymed_symbol = ISVREF(table,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(table,(SI_Long)16L),(SI_Long)27L));
    y_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
    scale = ISVREF(image_plane,(SI_Long)12L);
    value = y_in_workspace;
    if (IFIX(scale) == (SI_Long)4096L)
	gensymed_symbol_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && value 
	    < IFIX(Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
    temp = IFIX(minus(y,FIX(gensymed_symbol_1 + gensymed_symbol_2)));
    return VALUES_1(FIX(MAX(temp_1,temp)));
}

Object Minimum_distance_to_move_mouse_to_be_dragging = UNBOUND;

Object Minimum_time_that_must_pass_to_be_dragging = UNBOUND;

Object Overshoot_distance_around_menus_before_beginning_dragging = UNBOUND;

static Object Qg2_defstruct_structure_name_loose_end_spot_g2_struct;  /* g2-defstruct-structure-name::loose-end-spot-g2-struct */

/* MOUSE-WAS-DRAGGED-P */
Object mouse_was_dragged_p(spot,motion_event,original_x,original_y,
	    original_timestamp)
    Object spot, motion_event, original_x, original_y, original_timestamp;
{
    Object cursor_x, cursor_y, timestamp, minimum_distance, temp;

    x_note_fn_call(118,262);
    cursor_x = ISVREF(motion_event,(SI_Long)3L);
    cursor_y = ISVREF(motion_event,(SI_Long)4L);
    timestamp = ISVREF(motion_event,(SI_Long)2L);
    minimum_distance = SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_loose_end_spot_g2_struct) ? 
	    FIX((SI_Long)0L) : Minimum_distance_to_move_mouse_to_be_dragging;
    temp = event_time_difference(timestamp,original_timestamp);
    temp = FIXNUM_GT(temp,Minimum_time_that_must_pass_to_be_dragging) ? T :
	     Nil;
    if (temp);
    else {
	temp = FIXNUM_MINUS(cursor_x,original_x);
	temp = FIXNUM_GT(FIXNUM_ABS(temp),minimum_distance) ? T : Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	temp = FIXNUM_MINUS(cursor_y,original_y);
	return VALUES_1(FIXNUM_GT(FIXNUM_ABS(temp),minimum_distance) ? T : 
		Nil);
    }
}

/* MENU-CHOICE-CELL-P */
Object menu_choice_cell_p(cell_qm)
    Object cell_qm;
{
    x_note_fn_call(118,263);
    if (cell_qm && CONSP(cell_qm))
	return getf(CADR(cell_qm),Qchoice,_);
    else
	return VALUES_1(Nil);
}

static Object Qhighlight_color;    /* highlight-color */

static Object Qtoken_menu;         /* token-menu */

static Object Qreplace_fragments_on_sides_qm;  /* replace-fragments-on-sides? */

static Object Qreplace_entire_text_qm;  /* replace-entire-text? */

static Object Qpathname_component_token_menu;  /* pathname-component-token-menu */

static Object Qpathname_component_conversion;  /* pathname-component-conversion */

/* AUTO-INSERT-TEXT-FROM-BLOCK */
Object auto_insert_text_from_block(text,block)
    Object text, block;
{
    Object sub_class_bit_vector, flash_qm, gensymed_symbol_3;
    Object gensymed_symbol_4, replace_fragments_on_sides_qm;
    Object handle_spaces_intelligently_qm, replace_entire_text_qm;
    Object block_reference_serial_number, xa, ya;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(118,264);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
    flash_qm = temp ? ( !TRUEP(getf(ISVREF(block,(SI_Long)18L),
	    Qhighlight_color,_)) ? T : Nil) : Nil;
    gensymed_symbol_3 = ISVREF(block,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
    if (temp);
    else {
	gensymed_symbol_4 = 
		lookup_global_or_kb_specific_property_value(Qtoken_menu,
		Class_description_gkbprop);
	if (gensymed_symbol_4) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
    }
    if (temp)
	replace_fragments_on_sides_qm = get_slot_value_function(block,
		Qreplace_fragments_on_sides_qm,Nil);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
	    replace_fragments_on_sides_qm = T;
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Table_class_description,(SI_Long)18L));
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
		replace_fragments_on_sides_qm = T;
	    else
		replace_fragments_on_sides_qm = Qnil;
	}
    }
    handle_spaces_intelligently_qm = handle_spaces_intelligently_p(block);
    gensymed_symbol_3 = ISVREF(block,(SI_Long)1L);
    gensymed_symbol_4 = 
	    lookup_global_or_kb_specific_property_value(Qtoken_menu,
	    Class_description_gkbprop);
    if (gensymed_symbol_4) {
	sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
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
    replace_entire_text_qm = temp ? get_slot_value_function(block,
	    Qreplace_entire_text_qm,Nil) : Nil;
    block_reference_serial_number = copy_frame_serial_number(ISVREF(block,
	    (SI_Long)3L));
    if (flash_qm)
	highlight_or_unhighlight_text_box(3,block,Nil,Nil);
    gensymed_symbol_3 = ISVREF(block,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Kfep_conversion_choice_menu_class_description,
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
	do_kfep_conversion_edit_from_outside(text);
    else {
	gensymed_symbol_4 = 
		lookup_global_or_kb_specific_property_value(Qpathname_component_token_menu,
		Class_description_gkbprop);
	if (gensymed_symbol_4) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	    insert_text_string_at_cursor_from_outside(5,text,
		    replace_fragments_on_sides_qm,
		    handle_spaces_intelligently_qm,replace_entire_text_qm,
		    Qpathname_component_conversion);
	else
	    insert_text_string_at_cursor_from_outside(4,text,
		    replace_fragments_on_sides_qm,
		    handle_spaces_intelligently_qm,replace_entire_text_qm);
    }
    reclaim_text_string(text);
    gensymed_symbol_3 = ISVREF(block,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol_3) ? IFIX(gensymed_symbol_3) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(block_reference_serial_number))
	temp = FIXNUMP(gensymed_symbol_3) ? 
		FIXNUM_LT(block_reference_serial_number,gensymed_symbol_3) 
		: TRUEP(T);
    else if (FIXNUMP(gensymed_symbol_3))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(block_reference_serial_number);
	ya = M_CAR(gensymed_symbol_3);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? 
		    FIXNUM_LT(M_CDR(block_reference_serial_number),
		    M_CDR(gensymed_symbol_3)) : TRUEP(Qnil);
    }
    if ( !temp) {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qtoken_menu,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
	if (temp) {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    temp = TRUEP(has_only_one_subblock_p(gensymed_symbol_3));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    flash_qm = Nil;
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) : Nil;
	    delete_frame(gensymed_symbol_3);
	}
	if (flash_qm)
	    highlight_or_unhighlight_text_box(3,block,Nil,T);
    }
    return reclaim_frame_serial_number(block_reference_serial_number);
}

/* ALLOCATE-MENU-HANDLE */
Object allocate_menu_handle(gensym_window,menu_1,top_level_menu_handle_qm)
    Object gensym_window, menu_1, top_level_menu_handle_qm;
{
    Object native_menu_table, entry_qm, menu_snap, top_handle, entry;
    Object svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,265);
    native_menu_table = ISVREF(gensym_window,(SI_Long)50L);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      i = (SI_Long)1L;
      ab_loop_bind_ = IFIX(ISVREF(Native_menu_table,(SI_Long)1L));
      entry_qm = Nil;
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      entry_qm = FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Native_menu_table,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(Native_menu_table,(i >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),i & (SI_Long)1023L);
      if ( !TRUEP(entry_qm)) {
	  menu_snap = make_snapshot_of_block(menu_1);
	  top_handle = top_level_menu_handle_qm;
	  if (top_handle);
	  else
	      top_handle = FIX(i);
	  entry = slot_value_list_2(menu_snap,top_handle);
	  if (FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_1 = Native_menu_table;
	      svref_arg_2 = i + IFIX(Managed_array_index_offset);
	      ISVREF(svref_arg_1,svref_arg_2) = entry;
	  }
	  else {
	      svref_arg_1 = ISVREF(Native_menu_table,(i >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = i & (SI_Long)1023L;
	      ISVREF(svref_arg_1,svref_arg_2) = entry;
	  }
	  result = VALUES_1(FIX(i));
	  goto end_1;
      }
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* SET-MENU-HANDLE-INFO */
Object set_menu_handle_info(gensym_window,handle,info)
    Object gensym_window, handle, info;
{
    Object native_menu_table, entry_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,266);
    native_menu_table = ISVREF(gensym_window,(SI_Long)50L);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      entry_qm = FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Native_menu_table,
	      IFIX(FIXNUM_ADD(handle,Managed_array_index_offset))) : 
	      ISVREF(ISVREF(Native_menu_table,(IFIX(handle) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(handle) & (SI_Long)1023L);
      if (entry_qm)
	  nconc2(entry_qm,slot_value_cons_1(info,Nil));
      result = VALUES_1(entry_qm);
    POP_SPECIAL();
    return result;
}

/* LOOKUP-MENU-HANDLE */
Object lookup_menu_handle(gensym_window,handle)
    Object gensym_window, handle;
{
    Object native_menu_table, entry_qm, menu_snap, top_handle, items, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,267);
    native_menu_table = ISVREF(gensym_window,(SI_Long)50L);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      entry_qm = FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Native_menu_table,
	      IFIX(FIXNUM_ADD(handle,Managed_array_index_offset))) : 
	      ISVREF(ISVREF(Native_menu_table,(IFIX(handle) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(handle) & (SI_Long)1023L);
      if (entry_qm) {
	  menu_snap = FIRST(entry_qm);
	  top_handle = SECOND(entry_qm);
	  items = THIRD(entry_qm);
	  temp = snapshot_of_block_valid_p(menu_snap) ? ISVREF(menu_snap,
		  (SI_Long)1L) : Qnil;
	  result = VALUES_3(temp,top_handle,items);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-MENU-HANDLE */
Object reclaim_menu_handle(gensym_window,handle)
    Object gensym_window, handle;
{
    x_note_fn_call(118,268);
    return reclaim_menu_handle_1(ISVREF(gensym_window,(SI_Long)50L),handle);
}

/* RECLAIM-MENU-HANDLE-1 */
Object reclaim_menu_handle_1(native_menu_table,handle)
    Object native_menu_table, handle;
{
    Object entry_qm, menu_snap, top_handle, items, svref_arg_1, svref_arg_2;
    SI_Long svref_arg_2_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,269);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      entry_qm = FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(Native_menu_table,
	      IFIX(FIXNUM_ADD(handle,Managed_array_index_offset))) : 
	      ISVREF(ISVREF(Native_menu_table,(IFIX(handle) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(handle) & (SI_Long)1023L);
      if (entry_qm) {
	  menu_snap = FIRST(entry_qm);
	  top_handle = SECOND(entry_qm);
	  items = THIRD(entry_qm);
	  if (snapshot_of_block_valid_p(menu_snap))
	      delete_menu(ISVREF(menu_snap,(SI_Long)1L));
	  reclaim_snapshot_of_block_1(menu_snap);
	  reclaim_slot_value_list_1(entry_qm);
	  if (EQL(handle,top_handle))
	      reclaim_gensym_tree_1(items);
	  if (FIXNUM_LE(ISVREF(Native_menu_table,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_1 = Native_menu_table;
	      svref_arg_2 = FIXNUM_ADD(handle,Managed_array_index_offset);
	      result = VALUES_1(SVREF(svref_arg_1,svref_arg_2) = Nil);
	  }
	  else {
	      svref_arg_1 = ISVREF(Native_menu_table,(IFIX(handle) >>  -  
		      - (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2_1 = IFIX(handle) & (SI_Long)1023L;
	      result = VALUES_1(ISVREF(svref_arg_1,svref_arg_2_1) = Nil);
	  }
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-CONTENTS-OF-NATIVE-MENU-TABLE */
Object reclaim_contents_of_native_menu_table(native_menu_table)
    Object native_menu_table;
{
    SI_Long i, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,270);
    PUSH_SPECIAL_WITH_SYMBOL(Native_menu_table,Qnative_menu_table,native_menu_table,
	    0);
      i = (SI_Long)1L;
      ab_loop_bind_ = IFIX(ISVREF(Native_menu_table,(SI_Long)1L));
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      reclaim_menu_handle_1(Native_menu_table,FIX(i));
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

Object Standard_remote_submenu_depth = UNBOUND;

/* EXPOSE-MENU-REMOTELY */
Object expose_menu_remotely(gensym_window,menu_1,x,y)
    Object gensym_window, menu_1, x, y;
{
    Object handle, items;

    x_note_fn_call(118,271);
    handle = allocate_menu_handle(gensym_window,menu_1,Nil);
    items = extract_menu_item_list_from_menu(4,gensym_window,handle,menu_1,
	    Standard_remote_submenu_depth);
    set_menu_handle_info(gensym_window,handle,items);
    return send_icp_post_native_menu(Current_workstation_window,handle,x,y,
	    items);
}

/* LENGTH-OF-LONGEST-ROW */
Object length_of_longest_row(table)
    Object table;
{
    Object row, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loop_maxmin_fl_;
    Declare_special(1);
    Object result;

    x_note_fn_call(118,272);
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      ab_loopvar_ = FIX((SI_Long)0L);
      ab_loopvar__1 = FIX((SI_Long)0L);
      ab_loop_maxmin_fl_ = T;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      ab_loopvar__1 = length(Row);
      if (ab_loop_maxmin_fl_) {
	  ab_loop_maxmin_fl_ = Nil;
	  ab_loopvar_ = ab_loopvar__1;
      }
      else
	  ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar_);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qline_color;         /* line-color */

static Object Qbackground_color;   /* background-color */

static Object Qcolor;              /* color */

/* EXTRACT-MENU-ITEM-LIST-FROM-MENU */
Object extract_menu_item_list_from_menu varargs_1(int, n)
{
    Object gensym_window, top_level_menu_handle, menu_1;
    Object max_depth, column, column_items, items, ab_loopvar_, ab_loopvar__1;
    Object row, ab_loop_list_, cell_qm, string_qm, item_qm, ab_loop_it_;
    Object ab_loopvar__2, ab_loopvar__3, piece, ab_loop_list__1, fmt, plist;
    Object fg, bg, submenu_qm, choice, submenu_handle, temp;
    SI_Long ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(118,273);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    top_level_menu_handle = REQUIRED_ARG_nonrelocating();
    menu_1 = REQUIRED_ARG_nonrelocating();
    max_depth = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : FIX((SI_Long)0L);
    END_ARGS_nonrelocating();
    column = FIX((SI_Long)0L);
    ab_loop_bind_ = IFIX(length_of_longest_row(menu_1));
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,1);
      column_items = Nil;
      items = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
    next_loop:
      if (IFIX(Column) >= ab_loop_bind_)
	  goto end_loop;
      row = Nil;
      ab_loop_list_ = ISVREF(menu_1,(SI_Long)19L);
      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	cell_qm = Nil;
	string_qm = Nil;
	item_qm = Nil;
	ab_loop_it_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__3 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	Row = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cell_qm = nth(Column,Row);
	if (CONSP(cell_qm)) {
	    piece = Nil;
	    ab_loop_list__1 = CDDDR(cell_qm);
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    piece = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (text_string_p(piece)) {
		string_qm = piece;
		goto end_1;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    string_qm = Qnil;
	  end_1:;
	}
	else
	    string_qm = Nil;
	if (string_qm && menu_choice_cell_p(cell_qm)) {
	    fmt = CAR(cell_qm);
	    plist = CADR(cell_qm);
	    fg = getf(plist,Qline_color,_);
	    bg = getf(plist,Qbackground_color,_);
	    submenu_qm = Nil;
	    choice = menu_cell_menu_choice(cell_qm);
	    if (menu_item_format_is_cascade_p(fmt)) {
		if (IFIX(max_depth) <= (SI_Long)0L)
		    item_qm = gensym_list_2(Qsubmenu,string_qm);
		else {
		    submenu_qm = create_submenu(3,menu_1,choice,
			    get_lookup_slot_value_given_default(menu_1,
			    Qmenu_mouse_pointer,Nil));
		    if ( !TRUEP(submenu_qm))
			item_qm = gensym_list_2(Qsubmenu,string_qm);
		    else {
			submenu_handle = 
				allocate_menu_handle(gensym_window,
				submenu_qm,top_level_menu_handle);
			ensure_that_menu_item_will_be_reclaimed(menu_1,
				submenu_qm);
			temp = gensym_list_3(Qsubmenu,string_qm,
				submenu_handle);
			item_qm = nconc2(temp,
				extract_menu_item_list_from_menu(4,
				gensym_window,top_level_menu_handle,
				submenu_qm,FIXNUM_SUB1(max_depth)));
		    }
		}
	    }
	    else if (fg || bg)
		item_qm = gensym_list_4(Qcolor,string_qm,fg,bg);
	    else
		item_qm = string_qm;
	}
	else
	    item_qm = Nil;
	ab_loop_it_ = item_qm;
	if (ab_loop_it_) {
	    ab_loopvar__3 = gensym_cons_1(ab_loop_it_,Nil);
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__3;
	    else
		ab_loopvar__1 = ab_loopvar__3;
	    ab_loopvar__2 = ab_loopvar__3;
	}
	goto next_loop_1;
      end_loop_1:
	column_items = ab_loopvar__1;
	goto end_2;
	column_items = Qnil;
      end_2:;
      POP_SPECIAL();
      if (items && column_items) {
	  ab_loopvar__1 = gensym_cons_1(Menu_break_marker,Nil);
	  if (ab_loopvar_)
	      M_CDR(ab_loopvar_) = ab_loopvar__1;
	  else
	      items = ab_loopvar__1;
	  ab_loopvar_ = ab_loopvar__1;
      }
      ab_loopvar__1 = column_items;
      if (ab_loopvar__1) {
	  if (ab_loopvar_)
	      M_CDR(ab_loopvar_) = ab_loopvar__1;
	  else
	      items = ab_loopvar__1;
	  ab_loopvar_ = last(ab_loopvar__1,_);
      }
      Column = FIXNUM_ADD1(Column);
      goto next_loop;
    end_loop:
      result = VALUES_1(items);
      goto end_3;
      result = VALUES_1(Qnil);
    end_3:;
    POP_SPECIAL();
    return result;
}

/* RECLAIM-MENU-HANDLES-IN-ITEM-TREE */
Object reclaim_menu_handles_in_item_tree(gensym_window,items)
    Object gensym_window, items;
{
    Object item, ab_loop_list_, submenu_handle_qm;

    x_note_fn_call(118,274);
    item = Nil;
    ab_loop_list_ = items;
    submenu_handle_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    submenu_handle_qm = CONSP(item) && EQ(FIRST(item),Qsubmenu) ? 
	    THIRD(item) : Qnil;
    if (submenu_handle_qm) {
	reclaim_menu_handle(gensym_window,submenu_handle_qm);
	reclaim_menu_handles_in_item_tree(gensym_window,CDDDR(item));
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant_4;     /* # */

/* MENU-ITEM-FORMAT-IS-CASCADE-P */
Object menu_item_format_is_cascade_p(menu_item_format)
    Object menu_item_format;
{
    Object name;

    x_note_fn_call(118,275);
    name = 
	    car_or_atom(get_lookup_slot_value_given_default(menu_item_format,
	    Qname_or_names_for_frame,Nil));
    return memq_function(name,list_constant_4);
}

static Object Qmenu_handle;        /* menu-handle */

static Object Qitem_number;        /* item-number */

/* EXECUTE-NATIVE-MENU-CHOICE */
Object execute_native_menu_choice(mouse_pointer)
    Object mouse_pointer;
{
    Object gensym_window, key_code, x_in_window, y_in_window, event_plist;
    Object menu_handle, item_number, menu_qm, top_level_menu_handle, cell_qm;
    Object top_level_items;
    Object result;

    x_note_fn_call(118,276);
    gensym_window = window_blackboard_function(mouse_pointer);
    key_code = key_code_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    event_plist = event_plist_blackboard_function(mouse_pointer);
    if (gensym_window && key_code && x_in_window && y_in_window) {
	menu_handle = getf(event_plist,Qmenu_handle,_);
	if (menu_handle);
	else
	    menu_handle = FIX(IFIX(key_code) >>  -  - (SI_Long)10L & 
		    (SI_Long)1023L);
	item_number = getf(event_plist,Qitem_number,_);
	if (item_number);
	else
	    item_number = FIX(IFIX(key_code) & (SI_Long)1023L);
	result = lookup_menu_handle(gensym_window,menu_handle);
	MVS_2(result,menu_qm,top_level_menu_handle);
	if (menu_qm) {
	    if (IFIX(item_number) > (SI_Long)0L) {
		cell_qm = menu_choice_text_cell_for_item_number(menu_qm,
			item_number);
		if (cell_qm)
		    execute_menu_choice_1(5,menu_qm,cell_qm,x_in_window,
			    y_in_window,T);
	    }
	    result = lookup_menu_handle(gensym_window,top_level_menu_handle);
	    top_level_items = NTH_VALUE((SI_Long)2L, result);
	    reclaim_menu_handles_in_item_tree(gensym_window,top_level_items);
	    return reclaim_menu_handle(gensym_window,top_level_menu_handle);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MENU-CHOICE-TEXT-CELL-FOR-ITEM-NUMBER */
Object menu_choice_text_cell_for_item_number(menu_1,item_number)
    Object menu_1, item_number;
{
    Object index_1, column, row, ab_loop_list_, cell_qm;
    SI_Long ab_loop_bind_;
    Declare_special(2);
    Object result;

    x_note_fn_call(118,277);
    index_1 = FIX((SI_Long)1L);
    column = FIX((SI_Long)0L);
    ab_loop_bind_ = IFIX(length_of_longest_row(menu_1));
    PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,1);
    next_loop:
      if (IFIX(Column) >= ab_loop_bind_)
	  goto end_loop;
      row = Nil;
      ab_loop_list_ = ISVREF(menu_1,(SI_Long)19L);
      PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	cell_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	Row = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cell_qm = nth(Column,Row);
	if (menu_choice_cell_p(cell_qm)) {
	    if (FIXNUM_EQ(item_number,index_1)) {
		result = VALUES_1(cell_qm);
		POP_SPECIAL();
		POP_SPECIAL();
		goto end_search;
	    }
	    index_1 = FIXNUM_ADD1(index_1);
	}
	goto next_loop_1;
      end_loop_1:;
      POP_SPECIAL();
      Column = FIXNUM_ADD1(Column);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
  end_search:
    return result;
}

void new_menus_INIT()
{
    Object temp, reclaim_structure_for_partial_command_1, temp_1, temp_2;
    Object reclaim_structure_for_hot_spot_state_1;
    Object reclaim_structure_for_elevator_state_1;
    Object Qexecute_native_menu_choice, AB_package, Qnew_style_event_handler;
    Object Qright_aligned_cascade_menu_item_format_new_small;
    Object Qcenter_aligned_cascade_menu_item_format_new_small;
    Object Qright_aligned_cascade_menu_item_format_new_large;
    Object Qcenter_aligned_cascade_menu_item_format_new_large;
    Object Qright_aligned_cascade_menu_item_format;
    Object Qcenter_aligned_cascade_menu_item_format;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmouse_motion_in_elevator_state, Qmouse_up_in_elevator_state;
    Object Qabort_elevator_state, Qenter_elevator_state, string_constant_18;
    Object Qselection_style_of_workstation_context_type;
    Object Qtop_level_with_selection_focus_is_selection_style, Qelevator_state;
    Object Qreclaim_structure, Qoutstanding_elevator_state_count;
    Object Qelevator_state_structure_memory_usage, Qutilities2;
    Object string_constant_20;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_19, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qenter_hot_spot_state_upon_frame_component, float_constant;
    Object Qabort_hot_spot, Qmouse_up_in_hot_spot, Qmouse_motion_in_hot_spot;
    Object Qhot_spot_gestures, list_constant_9, Qglobal_development;
    Object Qhot_spot_state, Qoutstanding_hot_spot_state_count;
    Object Qhot_spot_state_structure_memory_usage, string_constant_17;
    Object string_constant_16, list_constant_8, Qprint_to_client;
    Object Qprint_to_server, list_constant_7, Qstatusbar, Qget_workspace;
    Object Qnew_workspace, Qselected_native_window_blackboard_function;
    Object Qselected_native_window, Qselected_workspace_blackboard_function;
    Object Qselected_workspace, Qselected_image_plane_blackboard_function;
    Object Qselected_image_plane, Qthing_to_select_blackboard_function;
    Object Qthing_to_select, Qmost_interesting_frame;
    Object Qmost_interesting_frame_blackboard_function;
    Object Qframe_for_selection_blackboard_function, Qframe_for_selection;
    Object Qeditable_text_spot_p_blackboard_function, Qeditable_text_spot_p;
    Object Qtext_plist_blackboard_function, Qtext_plist;
    Object Qcharacter_index_blackboard_function, Qcharacter_index;
    Object Qline_index_blackboard_function, Qline_index;
    Object Qgraph_table_blackboard_function, Qgraph_table;
    Object Qattribute_display_text_cell_blackboard_function;
    Object Qattribute_display_text_cell;
    Object Qattribute_display_blackboard_function, Qattribute_display;
    Object Qblock_being_represented_blackboard_function;
    Object Qblock_being_represented;
    Object Qblock_showing_representation_blackboard_function;
    Object Qblock_showing_representation;
    Object Qframe_represented_by_table_blackboard_function;
    Object Qframe_represented_by_table;
    Object Qslot_component_indicator_qm_blackboard_function;
    Object Qslot_component_indicator_qm;
    Object Qslot_component_name_qm_blackboard_function;
    Object Qslot_component_name_qm, Qdefining_class_blackboard_function;
    Object Qdefining_class, Qslot_name_blackboard_function, Qslot_name;
    Object Qcell_of_table_blackboard_function, Qcell_of_table;
    Object Qtext_cell_of_table_blackboard_function, Qtext_cell_of_table;
    Object Qshort_representation_table_blackboard_function;
    Object Qshort_representation_table, Qattribute_table_blackboard_function;
    Object Qattribute_table, Qtable_but_not_kb_item_blackboard_function;
    Object Qtable_but_not_kb_item, Qtable_blackboard_function, Qtable;
    Object Qsubframe_blackboard_function, Qsubframe;
    Object Qframe_or_subframe_blackboard_function, Qframe_or_subframe;
    Object Qframe_blackboard_function, Qframe;
    Object Qoriginal_y_in_window_blackboard_function, Qoriginal_y_in_window;
    Object Qoriginal_x_in_window_blackboard_function, Qoriginal_x_in_window;
    Object Qoriginal_mouse_pointer_blackboard_function;
    Object Qoriginal_mouse_pointer, Qlatest_y_in_window_blackboard_function;
    Object Qlatest_y_in_window, Qlatest_x_in_window_blackboard_function;
    Object Qlatest_x_in_window;
    Object Qworkspace_of_selection_focus_blackboard_function;
    Object Qworkspace_of_selection_focus;
    Object Qblock_of_selection_focus_blackboard_function;
    Object Qblock_of_selection_focus;
    Object Qimage_plane_of_selection_focus_blackboard_function;
    Object Qimage_plane_of_selection_focus;
    Object Qy_in_workspace_of_selection_focus_blackboard_function;
    Object Qy_in_workspace_of_selection_focus;
    Object Qx_in_workspace_of_selection_focus_blackboard_function;
    Object Qx_in_workspace_of_selection_focus;
    Object Qy_in_workspace_blackboard_function, Qy_in_workspace;
    Object Qx_in_workspace_blackboard_function, Qx_in_workspace;
    Object Qy_in_window_blackboard_function, Qy_in_window;
    Object Qx_in_window_blackboard_function, Qx_in_window;
    Object Qcurrent_selection_blackboard_function, Qcurrent_selection;
    Object Qnative_image_plane_blackboard_function, Qnative_image_plane;
    Object Qnative_window_blackboard_function, Qnative_window;
    Object Qimage_plane_showing_block_blackboard_function;
    Object Qimage_plane_showing_block, Qimage_plane_blackboard_function;
    Object Qimage_plane, Qdetail_pane_blackboard_function, Qdetail_pane;
    Object Qpane_blackboard_function, Qpane;
    Object Qinnermost_spot_blackboard_function, Qinnermost_spot;
    Object Qspot_blackboard_function, Qspot;
    Object Qworkstation_context_specifics_blackboard_function;
    Object Qworkstation_context_specifics;
    Object Qworkstation_context_blackboard_function, Qworkstation_context;
    Object Qg2_window_blackboard_function, Qg2_window;
    Object Qwindow_blackboard_function, Qworkstation_blackboard_function;
    Object Qworkstation, Qmouse_down_pointer_blackboard_function;
    Object Qmouse_down_pointer, Qmouse_pointer_blackboard_function;
    Object Qmouse_pointer, Qtimestamp_blackboard_function, Qtimestamp;
    Object Qkey_code_blackboard_function, Qkey_code;
    Object Qevent_plist_blackboard_function, Qevent_blackboard_function;
    Object Qevent, Qcontext_description, Qeditor_text_marking_menu;
    Object Qslot_value_reclaimer;
    Object Qreclaim_parameter_menu_partial_command_value, string_constant_15;
    Object list_constant_6, string_constant_14, string_constant_13;
    Object string_constant_7, string_constant_12, string_constant_11;
    Object Qcolor_menu, Qfull_color_menu, Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_new_menu;
    Object Qreclaim_new_menu_other_things_to_reclaim_value, string_constant_10;
    Object list_constant_5, string_constant_9, string_constant_8;
    Object Qmove_workspace, Qmove, Qtransfer, Qmenu_description, Qnew_menus;
    Object Qpartial_command, Qoutstanding_partial_command_count;
    Object Qpartial_command_structure_memory_usage, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object Qui_command, Qkeymap, Qevent_handler_condition, Qpresentation_type;

    x_note_fn_call(118,278);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qpresentation_type_named = STATIC_SYMBOL("PRESENTATION-TYPE-NAMED",
	    AB_package);
    Presentation_type_named_prop = Qpresentation_type_named;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_presentation_type_g2_struct = 
	    STATIC_SYMBOL("PRESENTATION-TYPE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpresentation_type = STATIC_SYMBOL("PRESENTATION-TYPE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_presentation_type_g2_struct,
	    Qpresentation_type,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qpresentation_type,
	    Qg2_defstruct_structure_name_presentation_type_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qmagic_argument_fetcher = STATIC_SYMBOL("MAGIC-ARGUMENT-FETCHER",
	    AB_package);
    Magic_argument_fetcher_prop = Qmagic_argument_fetcher;
    Qg2_defstruct_structure_name_entire_g2_window_spot_g2_struct = 
	    STATIC_SYMBOL("ENTIRE-G2-WINDOW-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    New_style_event_handler_prop = Qnew_style_event_handler;
    Qevent_handler_pretty_name_qm = 
	    STATIC_SYMBOL("EVENT-HANDLER-PRETTY-NAME\?",AB_package);
    Event_handler_pretty_name_qm_prop = Qevent_handler_pretty_name_qm;
    Qevent_handler_condition = STATIC_SYMBOL("EVENT-HANDLER-CONDITION",
	    AB_package);
    Event_handler_condition_prop = Qevent_handler_condition;
    Qkeymap_named = STATIC_SYMBOL("KEYMAP-NAMED",AB_package);
    Keymap_named_prop = Qkeymap_named;
    Qg2_defstruct_structure_name_keymap_g2_struct = 
	    STATIC_SYMBOL("KEYMAP-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qkeymap = STATIC_SYMBOL("KEYMAP",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_keymap_g2_struct,
	    Qkeymap,Qab_name_of_unique_structure_type);
    mutate_global_property(Qkeymap,
	    Qg2_defstruct_structure_name_keymap_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    Qspot_class_set = STATIC_SYMBOL("SPOT-CLASS-SET",AB_package);
    Spot_class_set_prop = Qspot_class_set;
    Qexact = STATIC_SYMBOL("EXACT",AB_package);
    Qkey_pattern_named = STATIC_SYMBOL("KEY-PATTERN-NAMED",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qkey_pattern_abbreviation = STATIC_SYMBOL("KEY-PATTERN-ABBREVIATION",
	    AB_package);
    string_constant = STATIC_STRING("~a");
    Qg2_defstruct_structure_name_ui_command_g2_struct = 
	    STATIC_SYMBOL("UI-COMMAND-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qui_command = STATIC_SYMBOL("UI-COMMAND",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ui_command_g2_struct,
	    Qui_command,Qab_name_of_unique_structure_type);
    mutate_global_property(Qui_command,
	    Qg2_defstruct_structure_name_ui_command_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qui_command_named = STATIC_SYMBOL("UI-COMMAND-NAMED",AB_package);
    Ui_command_named_prop = Qui_command_named;
    Qui_commands_with_menu_name = 
	    STATIC_SYMBOL("UI-COMMANDS-WITH-MENU-NAME",AB_package);
    Ui_commands_with_menu_name_prop = Qui_commands_with_menu_name;
    Qui_command_command_posts_dialog_p = 
	    STATIC_SYMBOL("UI-COMMAND-COMMAND-POSTS-DIALOG-P",AB_package);
    Ui_command_command_posts_dialog_p_prop = 
	    Qui_command_command_posts_dialog_p;
    string_constant_3 = STATIC_STRING("MISSING-ARGUMENT");
    if (Plus_missing_argument_plus == UNBOUND)
	Plus_missing_argument_plus = make_symbol(string_constant_3);
    string_constant_4 = STATIC_STRING("ABORT-MENU-CHOICE");
    if (Plus_abort_menu_choice_plus == UNBOUND)
	Plus_abort_menu_choice_plus = make_symbol(string_constant_4);
    if (List_of_all_ui_commands == UNBOUND)
	List_of_all_ui_commands = Nil;
    Qg2_defstruct_structure_name_partial_command_g2_struct = 
	    STATIC_SYMBOL("PARTIAL-COMMAND-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpartial_command = STATIC_SYMBOL("PARTIAL-COMMAND",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_partial_command_g2_struct,
	    Qpartial_command,Qab_name_of_unique_structure_type);
    mutate_global_property(Qpartial_command,
	    Qg2_defstruct_structure_name_partial_command_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_partial_command == UNBOUND)
	The_type_description_of_partial_command = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m83lRy1n83lRy8n8k1l8n0000001m1n8y83-51y01m83My83-Ajyknk0k0");
    temp = The_type_description_of_partial_command;
    The_type_description_of_partial_command = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_partial_command_g2_struct,
	    The_type_description_of_partial_command,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qpartial_command,
	    The_type_description_of_partial_command,Qtype_description_of_type);
    Qoutstanding_partial_command_count = 
	    STATIC_SYMBOL("OUTSTANDING-PARTIAL-COMMAND-COUNT",AB_package);
    Qpartial_command_structure_memory_usage = 
	    STATIC_SYMBOL("PARTIAL-COMMAND-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_6 = STATIC_STRING("1q83lRy8s83-iSy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_partial_command_count);
    push_optimized_constant(Qpartial_command_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_partial_commands = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PARTIAL-COMMANDS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_partial_commands,
	    Chain_of_available_partial_commands);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_partial_commands,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qpartial_command_count = STATIC_SYMBOL("PARTIAL-COMMAND-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpartial_command_count,Partial_command_count);
    record_system_variable(Qpartial_command_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_partial_commands_vector == UNBOUND)
	Chain_of_available_partial_commands_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qpartial_command_structure_memory_usage,
	    STATIC_FUNCTION(partial_command_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_partial_command_count,
	    STATIC_FUNCTION(outstanding_partial_command_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_partial_command_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_partial_command,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qpartial_command,
	    reclaim_structure_for_partial_command_1);
    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct = 
	    STATIC_SYMBOL("SNAPSHOT-OF-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qui_command_context = STATIC_SYMBOL("UI-COMMAND-CONTEXT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qui_command_context,Ui_command_context);
    Qnew_menus = STATIC_SYMBOL("NEW-MENUS",AB_package);
    record_system_variable(Qui_command_context,Qnew_menus,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    if (Presentation_mode == UNBOUND)
	Presentation_mode = Nil;
    Qparameter_menu_item_submenu_p = 
	    STATIC_SYMBOL("PARAMETER-MENU-ITEM-SUBMENU-P",AB_package);
    SET_SYMBOL_FUNCTION(Qparameter_menu_item_submenu_p,
	    STATIC_FUNCTION(parameter_menu_item_submenu_p,NIL,FALSE,5,5));
    Qfind_menu_description = STATIC_SYMBOL("FIND-MENU-DESCRIPTION",AB_package);
    Find_menu_description_prop = Qfind_menu_description;
    Qmenu_descriptions_for_class = 
	    STATIC_SYMBOL("MENU-DESCRIPTIONS-FOR-CLASS",AB_package);
    Menu_descriptions_for_class_prop = Qmenu_descriptions_for_class;
    Qg2_defstruct_structure_name_menu_description_g2_struct = 
	    STATIC_SYMBOL("MENU-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qmenu_description = STATIC_SYMBOL("MENU-DESCRIPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_menu_description_g2_struct,
	    Qmenu_description,Qab_name_of_unique_structure_type);
    mutate_global_property(Qmenu_description,
	    Qg2_defstruct_structure_name_menu_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qparameter_menu = STATIC_SYMBOL("PARAMETER-MENU",AB_package);
    Qparameter_menu_choice_function = 
	    STATIC_SYMBOL("PARAMETER-MENU-CHOICE-FUNCTION",AB_package);
    Qcommand_menu = STATIC_SYMBOL("COMMAND-MENU",AB_package);
    Qcommand_menu_choice_function = 
	    STATIC_SYMBOL("COMMAND-MENU-CHOICE-FUNCTION",AB_package);
    Qnamed_gensym_structure = STATIC_SYMBOL("NAMED-GENSYM-STRUCTURE",
	    AB_package);
    Qexported_menu_description_for_class = 
	    STATIC_SYMBOL("EXPORTED-MENU-DESCRIPTION-FOR-CLASS",AB_package);
    Exported_menu_description_for_class_prop = 
	    Qexported_menu_description_for_class;
    Qrow = STATIC_SYMBOL("ROW",AB_package);
    Qchoice = STATIC_SYMBOL("CHOICE",AB_package);
    Qinclude = STATIC_SYMBOL("INCLUDE",AB_package);
    Qsubmenu = STATIC_SYMBOL("SUBMENU",AB_package);
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    list_constant = STATIC_LIST((SI_Long)6L,Qinclude,Qsubmenu,Qchoice,
	    Qcommand,Quser_menu_choice,Qrow);
    Qdialog = STATIC_SYMBOL("DIALOG",AB_package);
    Q_SPACER_ = STATIC_SYMBOL("-spacer-",AB_package);
    Qmenu_string = STATIC_SYMBOL("MENU-STRING",AB_package);
    Kfirst_of_each_word = STATIC_SYMBOL("FIRST-OF-EACH-WORD",Pkeyword);
    Knone = STATIC_SYMBOL("NONE",Pkeyword);
    string_constant_1 = STATIC_STRING("~a...");
    Qmenu_item = STATIC_SYMBOL("MENU-ITEM",AB_package);
    string_constant_2 = STATIC_STRING("<<Missing submenu ~s>>");
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qmove_workspace = STATIC_SYMBOL("MOVE-WORKSPACE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qtransfer,Qmove,Qmove_workspace);
    Qrefreshes_image_plane_p = STATIC_SYMBOL("REFRESHES-IMAGE-PLANE-P",
	    AB_package);
    Refreshes_image_plane_p_prop = Qrefreshes_image_plane_p;
    Qnew_menu = STATIC_SYMBOL("NEW-MENU",AB_package);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    list_constant_5 = STATIC_CONS(Qmenu,Qnil);
    check_if_superior_classes_are_defined(Qnew_menu,list_constant_5);
    string_constant_7 = STATIC_STRING("1l1l8t");
    string_constant_8 = 
	    STATIC_STRING("1o4z8r83VEy83VEy835qy835qy00001m1l83Ey1l8l000004z8r83VDy83VDy835qy835qy00001m1l83Ey1l8l000004z8r83WRy83WRy835qy835qy00001m1l83Ey");
    string_constant_9 = 
	    STATIC_STRING("1l8l000004z8r83VGy83VGy835qy835qy00001m1l83Ey1l8l00000");
    string_constant_10 = 
	    STATIC_STRING("1q8q1n835qy1l9k8t1o83VEy083Ey8l1o83VDy083Ey8l1o83WRy083Ey8l1o83VGy083Ey8l");
    temp = regenerate_optimized_constant(string_constant_7);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_8,
	    string_constant_9));
    clear_optimized_constants();
    push_optimized_constant(Qmenu);
    add_class_to_environment(9,Qnew_menu,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_10),Nil);
    Qnew_menu_other_things_to_reclaim = 
	    STATIC_SYMBOL("NEW-MENU-OTHER-THINGS-TO-RECLAIM",AB_package);
    Qreclaim_new_menu_other_things_to_reclaim_value = 
	    STATIC_SYMBOL("RECLAIM-NEW-MENU-OTHER-THINGS-TO-RECLAIM-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_new_menu_other_things_to_reclaim_value,
	    STATIC_FUNCTION(reclaim_new_menu_other_things_to_reclaim_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qnew_menu_other_things_to_reclaim,
	    SYMBOL_FUNCTION(Qreclaim_new_menu_other_things_to_reclaim_value),
	    Qslot_value_reclaimer);
    Qmenu_no_choice_function = STATIC_SYMBOL("MENU-NO-CHOICE-FUNCTION",
	    AB_package);
    Qcleanup_for_new_menu = STATIC_SYMBOL("CLEANUP-FOR-NEW-MENU",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_new_menu,
	    STATIC_FUNCTION(cleanup_for_new_menu,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_new_menu);
    set_get(Qnew_menu,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qnew_menu,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Ktitle = STATIC_SYMBOL("TITLE",Pkeyword);
    Qcascade_menu_item_format = STATIC_SYMBOL("CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qmenu_item_format = STATIC_SYMBOL("MENU-ITEM-FORMAT",AB_package);
    Qfull_color_menu = STATIC_SYMBOL("FULL-COLOR-MENU",AB_package);
    Qcolor_menu = STATIC_SYMBOL("COLOR-MENU",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qfull_color_menu,Qcolor_menu);
    Qmenu_table_format = STATIC_SYMBOL("MENU-TABLE-FORMAT",AB_package);
    Qmenu_table_format_for_new_g2_classic_ui = 
	    STATIC_SYMBOL("MENU-TABLE-FORMAT-FOR-NEW-G2-CLASSIC-UI",
	    AB_package);
    Qmenu_description_of_menu = STATIC_SYMBOL("MENU-DESCRIPTION-OF-MENU",
	    AB_package);
    Qmenu_choice_transformer = STATIC_SYMBOL("MENU-CHOICE-TRANSFORMER",
	    AB_package);
    Qmenu_mouse_pointer = STATIC_SYMBOL("MENU-MOUSE-POINTER",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qleft_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",AB_package);
    Qleft_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_arrow_left_aligned_menu_item_format_new_large = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qleft_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_menu_item_format_new_small = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qleft_arrow_left_aligned_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ARROW-LEFT-ALIGNED-MENU-ITEM-FORMAT",
	    AB_package);
    Qleft_aligned_menu_item_format = 
	    STATIC_SYMBOL("LEFT-ALIGNED-MENU-ITEM-FORMAT",AB_package);
    Qmenus_for_this = STATIC_SYMBOL("MENUS-FOR-THIS",AB_package);
    Qwhat_this_is_a_menu_for_qm = 
	    STATIC_SYMBOL("WHAT-THIS-IS-A-MENU-FOR\?",AB_package);
    list_constant_6 = STATIC_CONS(Qnew_menu,Qnil);
    check_if_superior_classes_are_defined(Qcommand_menu,list_constant_6);
    string_constant_11 = 
	    STATIC_STRING("1l4z8r8325y8325y83ILy83ILy09k001m1l8o1l8l00000");
    string_constant_12 = STATIC_STRING("1n8q1n83ILy1l835qy8t1o8325y9k8o8l");
    temp = regenerate_optimized_constant(string_constant_7);
    clear_optimized_constants();
    push_optimized_constant(Qcommand_menu_choice_function);
    temp_1 = regenerate_optimized_constant(string_constant_11);
    clear_optimized_constants();
    push_optimized_constant(Qcommand_menu_choice_function);
    add_class_to_environment(9,Qcommand_menu,list_constant_6,Nil,temp,Nil,
	    temp_1,list_constant_6,
	    regenerate_optimized_constant(string_constant_12),Nil);
    SET_SYMBOL_FUNCTION(Qcommand_menu_choice_function,
	    STATIC_FUNCTION(command_menu_choice_function,NIL,FALSE,3,3));
    check_if_superior_classes_are_defined(Qparameter_menu,list_constant_6);
    string_constant_13 = 
	    STATIC_STRING("1n4z8r8325y8325y83XWy83XWy09k001m1l8o1l8l000004z8r83XXy83XXy83XWy83XWy00001m1l83Ey1l8l000004z8r83XYy83XYy83XWy83XWy00001m1l83Ey1");
    string_constant_14 = STATIC_STRING("l8l00000");
    string_constant_15 = 
	    STATIC_STRING("1p8q1n83XWy1l835qy8t1o8325y9k8o8l1o83XXy083Ey8l1o83XYy083Ey8l");
    temp = regenerate_optimized_constant(string_constant_7);
    clear_optimized_constants();
    push_optimized_constant(Qparameter_menu_choice_function);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_13,
	    string_constant_14));
    clear_optimized_constants();
    push_optimized_constant(Qparameter_menu_choice_function);
    add_class_to_environment(9,Qparameter_menu,list_constant_6,Nil,temp,
	    Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(string_constant_15),Nil);
    Qparameter_menu_partial_command = 
	    STATIC_SYMBOL("PARAMETER-MENU-PARTIAL-COMMAND",AB_package);
    Qreclaim_parameter_menu_partial_command_value = 
	    STATIC_SYMBOL("RECLAIM-PARAMETER-MENU-PARTIAL-COMMAND-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_parameter_menu_partial_command_value,
	    STATIC_FUNCTION(reclaim_parameter_menu_partial_command_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qparameter_menu_partial_command,
	    SYMBOL_FUNCTION(Qreclaim_parameter_menu_partial_command_value),
	    Qslot_value_reclaimer);
    Qparameter_menu_which_argument = 
	    STATIC_SYMBOL("PARAMETER-MENU-WHICH-ARGUMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qparameter_menu_choice_function,
	    STATIC_FUNCTION(parameter_menu_choice_function,NIL,FALSE,3,3));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qeditor_text_marking_menu = STATIC_SYMBOL("EDITOR-TEXT-MARKING-MENU",
	    AB_package);
    list_constant_3 = STATIC_CONS(Qeditor_text_marking_menu,Qnil);
    Qmenu_workspace = STATIC_SYMBOL("MENU-WORKSPACE",AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qclose_box_x_offset = STATIC_SYMBOL("CLOSE-BOX-X-OFFSET",AB_package);
    Qclose_box_y_offset = STATIC_SYMBOL("CLOSE-BOX-Y-OFFSET",AB_package);
    if (List_of_all_workstation_contexts == UNBOUND)
	List_of_all_workstation_contexts = Nil;
    Qcontext_description_named = STATIC_SYMBOL("CONTEXT-DESCRIPTION-NAMED",
	    AB_package);
    Context_description_named_prop = Qcontext_description_named;
    Qg2_defstruct_structure_name_context_description_g2_struct = 
	    STATIC_SYMBOL("CONTEXT-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcontext_description = STATIC_SYMBOL("CONTEXT-DESCRIPTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_context_description_g2_struct,
	    Qcontext_description,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcontext_description,
	    Qg2_defstruct_structure_name_context_description_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    Qfind_event_interpretation = STATIC_SYMBOL("FIND-EVENT-INTERPRETATION",
	    AB_package);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qfind_event_interpretation,
	    STATIC_FUNCTION(find_event_interpretation,NIL,FALSE,2,2));
    Qcurrent_workstation_event = STATIC_SYMBOL("CURRENT-WORKSTATION-EVENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_workstation_event,
	    Current_workstation_event);
    Qevent = STATIC_SYMBOL("EVENT",AB_package);
    Qevent_blackboard_function = STATIC_SYMBOL("EVENT-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevent_blackboard_function,
	    STATIC_FUNCTION(event_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qevent,Qevent_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qevent,Qnil,Qnil,Qnil,Qnil,
	    Qevent_blackboard_function,Qnil,Qnil);
    Qevent_plist = STATIC_SYMBOL("EVENT-PLIST",AB_package);
    Qevent_plist_blackboard_function = 
	    STATIC_SYMBOL("EVENT-PLIST-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qevent_plist_blackboard_function,
	    STATIC_FUNCTION(event_plist_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qevent_plist,Qevent_plist_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qevent_plist,Qnil,Qnil,Qnil,Qnil,
	    Qevent_plist_blackboard_function,Qnil,Qnil);
    Qkey_code = STATIC_SYMBOL("KEY-CODE",AB_package);
    Qkey_code_blackboard_function = 
	    STATIC_SYMBOL("KEY-CODE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qkey_code_blackboard_function,
	    STATIC_FUNCTION(key_code_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qkey_code,Qkey_code_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qkey_code,Qnil,Qnil,Qnil,Qnil,
	    Qkey_code_blackboard_function,Qnil,Qnil);
    Qtimestamp = STATIC_SYMBOL("TIMESTAMP",AB_package);
    Qtimestamp_blackboard_function = 
	    STATIC_SYMBOL("TIMESTAMP-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qtimestamp_blackboard_function,
	    STATIC_FUNCTION(timestamp_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qtimestamp,Qtimestamp_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qtimestamp,Qnil,Qnil,Qnil,Qnil,
	    Qtimestamp_blackboard_function,Qnil,Qnil);
    Qmouse_pointer = STATIC_SYMBOL("MOUSE-POINTER",AB_package);
    Qmouse_pointer_blackboard_function = 
	    STATIC_SYMBOL("MOUSE-POINTER-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_pointer_blackboard_function,
	    STATIC_FUNCTION(mouse_pointer_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_pointer,
	    Qmouse_pointer_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qmouse_pointer,Qnil,Qnil,Qnil,Qnil,
	    Qmouse_pointer_blackboard_function,Qnil,Qnil);
    Qmouse_down_pointer = STATIC_SYMBOL("MOUSE-DOWN-POINTER",AB_package);
    Qmouse_down_pointer_blackboard_function = 
	    STATIC_SYMBOL("MOUSE-DOWN-POINTER-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_down_pointer_blackboard_function,
	    STATIC_FUNCTION(mouse_down_pointer_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qmouse_down_pointer,
	    Qmouse_down_pointer_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qmouse_down_pointer,Qnil,Qnil,Qnil,Qnil,
	    Qmouse_down_pointer_blackboard_function,Qnil,Qnil);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    Qworkstation_blackboard_function = 
	    STATIC_SYMBOL("WORKSTATION-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qworkstation_blackboard_function,
	    STATIC_FUNCTION(workstation_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qworkstation,Qworkstation_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qworkstation,Qnil,Qnil,Qnil,Qnil,
	    Qworkstation_blackboard_function,Qnil,Qnil);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qwindow_blackboard_function = 
	    STATIC_SYMBOL("WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qwindow_blackboard_function,
	    STATIC_FUNCTION(window_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qwindow,Qwindow_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qwindow,Qnil,Qnil,Qnil,Qnil,
	    Qwindow_blackboard_function,Qnil,Qnil);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qg2_window_blackboard_function = 
	    STATIC_SYMBOL("G2-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_window_blackboard_function,
	    STATIC_FUNCTION(g2_window_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qg2_window,Qg2_window_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qg2_window,Qnil,Qnil,Qnil,Qnil,
	    Qg2_window_blackboard_function,Qnil,Qnil);
    Qworkstation_context = STATIC_SYMBOL("WORKSTATION-CONTEXT",AB_package);
    Qworkstation_context_blackboard_function = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qworkstation_context_blackboard_function,
	    STATIC_FUNCTION(workstation_context_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qworkstation_context,
	    Qworkstation_context_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qworkstation_context,Qnil,Qnil,Qnil,Qnil,
	    Qworkstation_context_blackboard_function,Qnil,Qnil);
    Qworkstation_context_specifics = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-SPECIFICS",AB_package);
    Qworkstation_context_specifics_blackboard_function = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-SPECIFICS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qworkstation_context_specifics_blackboard_function,
	    STATIC_FUNCTION(workstation_context_specifics_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qworkstation_context_specifics,
	    Qworkstation_context_specifics_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qworkstation_context_specifics,Qnil,Qnil,Qnil,
	    Qnil,Qworkstation_context_specifics_blackboard_function,Qnil,Qnil);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    Qspot_blackboard_function = STATIC_SYMBOL("SPOT-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qspot_blackboard_function,
	    STATIC_FUNCTION(spot_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qspot,Qspot_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qspot,Qnil,Qnil,Qnil,Qnil,
	    Qspot_blackboard_function,Qnil,Qnil);
    Qinnermost_spot = STATIC_SYMBOL("INNERMOST-SPOT",AB_package);
    Qinnermost_spot_blackboard_function = 
	    STATIC_SYMBOL("INNERMOST-SPOT-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qinnermost_spot_blackboard_function,
	    STATIC_FUNCTION(innermost_spot_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qinnermost_spot,
	    Qinnermost_spot_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qinnermost_spot,Qnil,Qnil,Qnil,Qnil,
	    Qinnermost_spot_blackboard_function,Qnil,Qnil);
    Qpane_spot = STATIC_SYMBOL("PANE-SPOT",AB_package);
    Qpane = STATIC_SYMBOL("PANE",AB_package);
    Qpane_blackboard_function = STATIC_SYMBOL("PANE-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qpane_blackboard_function,
	    STATIC_FUNCTION(pane_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qpane,Qpane_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qpane,Qnil,Qnil,Qnil,Qnil,
	    Qpane_blackboard_function,Qnil,Qnil);
    Qdetail_pane = STATIC_SYMBOL("DETAIL-PANE",AB_package);
    Qdetail_pane_blackboard_function = 
	    STATIC_SYMBOL("DETAIL-PANE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qdetail_pane_blackboard_function,
	    STATIC_FUNCTION(detail_pane_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qdetail_pane,Qdetail_pane_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qdetail_pane,Qnil,Qnil,Qnil,Qnil,
	    Qdetail_pane_blackboard_function,Qnil,Qnil);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qimage_plane = STATIC_SYMBOL("IMAGE-PLANE",AB_package);
    Qimage_plane_blackboard_function = 
	    STATIC_SYMBOL("IMAGE-PLANE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qimage_plane_blackboard_function,
	    STATIC_FUNCTION(image_plane_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qimage_plane,Qimage_plane_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qimage_plane,Qnil,Qnil,Qnil,Qnil,
	    Qimage_plane_blackboard_function,Qnil,Qnil);
    Qimage_plane_showing_block = STATIC_SYMBOL("IMAGE-PLANE-SHOWING-BLOCK",
	    AB_package);
    Qimage_plane_showing_block_blackboard_function = 
	    STATIC_SYMBOL("IMAGE-PLANE-SHOWING-BLOCK-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qimage_plane_showing_block_blackboard_function,
	    STATIC_FUNCTION(image_plane_showing_block_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qimage_plane_showing_block,
	    Qimage_plane_showing_block_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qimage_plane_showing_block,Qnil,Qnil,Qnil,Qnil,
	    Qimage_plane_showing_block_blackboard_function,Qnil,Qnil);
    Qnative_window = STATIC_SYMBOL("NATIVE-WINDOW",AB_package);
    Qnative_window_blackboard_function = 
	    STATIC_SYMBOL("NATIVE-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qnative_window_blackboard_function,
	    STATIC_FUNCTION(native_window_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qnative_window,
	    Qnative_window_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qnative_window,Qnil,Qnil,Qnil,Qnil,
	    Qnative_window_blackboard_function,Qnil,Qnil);
    Qnative_image_plane = STATIC_SYMBOL("NATIVE-IMAGE-PLANE",AB_package);
    Qnative_image_plane_blackboard_function = 
	    STATIC_SYMBOL("NATIVE-IMAGE-PLANE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qnative_image_plane_blackboard_function,
	    STATIC_FUNCTION(native_image_plane_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qnative_image_plane,
	    Qnative_image_plane_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qnative_image_plane,Qnil,Qnil,Qnil,Qnil,
	    Qnative_image_plane_blackboard_function,Qnil,Qnil);
    Qcurrent_selection = STATIC_SYMBOL("CURRENT-SELECTION",AB_package);
    Qcurrent_selection_blackboard_function = 
	    STATIC_SYMBOL("CURRENT-SELECTION-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qcurrent_selection_blackboard_function,
	    STATIC_FUNCTION(current_selection_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qcurrent_selection,
	    Qcurrent_selection_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qcurrent_selection,Qnil,Qnil,Qnil,Qnil,
	    Qcurrent_selection_blackboard_function,Qnil,Qnil);
    Qx_in_window = STATIC_SYMBOL("X-IN-WINDOW",AB_package);
    Qx_in_window_blackboard_function = 
	    STATIC_SYMBOL("X-IN-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qx_in_window_blackboard_function,
	    STATIC_FUNCTION(x_in_window_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qx_in_window,Qx_in_window_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qx_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qx_in_window_blackboard_function,Qnil,Qnil);
    Qy_in_window = STATIC_SYMBOL("Y-IN-WINDOW",AB_package);
    Qy_in_window_blackboard_function = 
	    STATIC_SYMBOL("Y-IN-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qy_in_window_blackboard_function,
	    STATIC_FUNCTION(y_in_window_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qy_in_window,Qy_in_window_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qy_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qy_in_window_blackboard_function,Qnil,Qnil);
    Qx_in_workspace = STATIC_SYMBOL("X-IN-WORKSPACE",AB_package);
    Qx_in_workspace_blackboard_function = 
	    STATIC_SYMBOL("X-IN-WORKSPACE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qx_in_workspace_blackboard_function,
	    STATIC_FUNCTION(x_in_workspace_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qx_in_workspace,
	    Qx_in_workspace_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qx_in_workspace,Qnil,Qnil,Qnil,Qnil,
	    Qx_in_workspace_blackboard_function,Qnil,Qnil);
    Qy_in_workspace = STATIC_SYMBOL("Y-IN-WORKSPACE",AB_package);
    Qy_in_workspace_blackboard_function = 
	    STATIC_SYMBOL("Y-IN-WORKSPACE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qy_in_workspace_blackboard_function,
	    STATIC_FUNCTION(y_in_workspace_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qy_in_workspace,
	    Qy_in_workspace_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qy_in_workspace,Qnil,Qnil,Qnil,Qnil,
	    Qy_in_workspace_blackboard_function,Qnil,Qnil);
    Qx_in_workspace_of_selection_focus = 
	    STATIC_SYMBOL("X-IN-WORKSPACE-OF-SELECTION-FOCUS",AB_package);
    Qx_in_workspace_of_selection_focus_blackboard_function = 
	    STATIC_SYMBOL("X-IN-WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qx_in_workspace_of_selection_focus_blackboard_function,
	    STATIC_FUNCTION(x_in_workspace_of_selection_focus_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qx_in_workspace_of_selection_focus,
	    Qx_in_workspace_of_selection_focus_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qx_in_workspace_of_selection_focus,Qnil,Qnil,
	    Qnil,Qnil,
	    Qx_in_workspace_of_selection_focus_blackboard_function,Qnil,Qnil);
    Qy_in_workspace_of_selection_focus = 
	    STATIC_SYMBOL("Y-IN-WORKSPACE-OF-SELECTION-FOCUS",AB_package);
    Qy_in_workspace_of_selection_focus_blackboard_function = 
	    STATIC_SYMBOL("Y-IN-WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qy_in_workspace_of_selection_focus_blackboard_function,
	    STATIC_FUNCTION(y_in_workspace_of_selection_focus_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qy_in_workspace_of_selection_focus,
	    Qy_in_workspace_of_selection_focus_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qy_in_workspace_of_selection_focus,Qnil,Qnil,
	    Qnil,Qnil,
	    Qy_in_workspace_of_selection_focus_blackboard_function,Qnil,Qnil);
    Qimage_plane_of_selection_focus = 
	    STATIC_SYMBOL("IMAGE-PLANE-OF-SELECTION-FOCUS",AB_package);
    Qimage_plane_of_selection_focus_blackboard_function = 
	    STATIC_SYMBOL("IMAGE-PLANE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qimage_plane_of_selection_focus_blackboard_function,
	    STATIC_FUNCTION(image_plane_of_selection_focus_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qimage_plane_of_selection_focus,
	    Qimage_plane_of_selection_focus_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qimage_plane_of_selection_focus,Qnil,Qnil,Qnil,
	    Qnil,Qimage_plane_of_selection_focus_blackboard_function,Qnil,
	    Qnil);
    Qblock_of_selection_focus = STATIC_SYMBOL("BLOCK-OF-SELECTION-FOCUS",
	    AB_package);
    Qblock_of_selection_focus_blackboard_function = 
	    STATIC_SYMBOL("BLOCK-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qblock_of_selection_focus_blackboard_function,
	    STATIC_FUNCTION(block_of_selection_focus_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qblock_of_selection_focus,
	    Qblock_of_selection_focus_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qblock_of_selection_focus,Qnil,Qnil,Qnil,Qnil,
	    Qblock_of_selection_focus_blackboard_function,Qnil,Qnil);
    Qworkspace_of_selection_focus = 
	    STATIC_SYMBOL("WORKSPACE-OF-SELECTION-FOCUS",AB_package);
    Qworkspace_of_selection_focus_blackboard_function = 
	    STATIC_SYMBOL("WORKSPACE-OF-SELECTION-FOCUS-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qworkspace_of_selection_focus_blackboard_function,
	    STATIC_FUNCTION(workspace_of_selection_focus_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qworkspace_of_selection_focus,
	    Qworkspace_of_selection_focus_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qworkspace_of_selection_focus,Qnil,Qnil,Qnil,
	    Qnil,Qworkspace_of_selection_focus_blackboard_function,Qnil,Qnil);
    Qlatest_x_in_window = STATIC_SYMBOL("LATEST-X-IN-WINDOW",AB_package);
    Qlatest_x_in_window_blackboard_function = 
	    STATIC_SYMBOL("LATEST-X-IN-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qlatest_x_in_window_blackboard_function,
	    STATIC_FUNCTION(latest_x_in_window_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlatest_x_in_window,
	    Qlatest_x_in_window_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qlatest_x_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qlatest_x_in_window_blackboard_function,Qnil,Qnil);
    Qlatest_y_in_window = STATIC_SYMBOL("LATEST-Y-IN-WINDOW",AB_package);
    Qlatest_y_in_window_blackboard_function = 
	    STATIC_SYMBOL("LATEST-Y-IN-WINDOW-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qlatest_y_in_window_blackboard_function,
	    STATIC_FUNCTION(latest_y_in_window_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qlatest_y_in_window,
	    Qlatest_y_in_window_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qlatest_y_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qlatest_y_in_window_blackboard_function,Qnil,Qnil);
    Qoriginal_mouse_pointer = STATIC_SYMBOL("ORIGINAL-MOUSE-POINTER",
	    AB_package);
    Qoriginal_mouse_pointer_blackboard_function = 
	    STATIC_SYMBOL("ORIGINAL-MOUSE-POINTER-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoriginal_mouse_pointer_blackboard_function,
	    STATIC_FUNCTION(original_mouse_pointer_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qoriginal_mouse_pointer,
	    Qoriginal_mouse_pointer_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qoriginal_mouse_pointer,Qnil,Qnil,Qnil,Qnil,
	    Qoriginal_mouse_pointer_blackboard_function,Qnil,Qnil);
    Qoriginal_x_in_window = STATIC_SYMBOL("ORIGINAL-X-IN-WINDOW",AB_package);
    Qoriginal_x_in_window_blackboard_function = 
	    STATIC_SYMBOL("ORIGINAL-X-IN-WINDOW-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoriginal_x_in_window_blackboard_function,
	    STATIC_FUNCTION(original_x_in_window_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qoriginal_x_in_window,
	    Qoriginal_x_in_window_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qoriginal_x_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qoriginal_x_in_window_blackboard_function,Qnil,Qnil);
    Qoriginal_y_in_window = STATIC_SYMBOL("ORIGINAL-Y-IN-WINDOW",AB_package);
    Qoriginal_y_in_window_blackboard_function = 
	    STATIC_SYMBOL("ORIGINAL-Y-IN-WINDOW-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qoriginal_y_in_window_blackboard_function,
	    STATIC_FUNCTION(original_y_in_window_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qoriginal_y_in_window,
	    Qoriginal_y_in_window_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qoriginal_y_in_window,Qnil,Qnil,Qnil,Qnil,
	    Qoriginal_y_in_window_blackboard_function,Qnil,Qnil);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    Qframe_blackboard_function = STATIC_SYMBOL("FRAME-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qframe_blackboard_function,
	    STATIC_FUNCTION(frame_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qframe,Qframe_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qframe,Qnil,Qnil,Qnil,Qnil,
	    Qframe_blackboard_function,Qnil,Qnil);
    Qreadout_table_spot = STATIC_SYMBOL("READOUT-TABLE-SPOT",AB_package);
    Qattribute_name_represented_by_table_spot = 
	    STATIC_SYMBOL("ATTRIBUTE-NAME-REPRESENTED-BY-TABLE-SPOT",
	    AB_package);
    Qattribute_value_represented_by_table_spot = 
	    STATIC_SYMBOL("ATTRIBUTE-VALUE-REPRESENTED-BY-TABLE-SPOT",
	    AB_package);
    Qframe_or_subframe = STATIC_SYMBOL("FRAME-OR-SUBFRAME",AB_package);
    Qframe_or_subframe_blackboard_function = 
	    STATIC_SYMBOL("FRAME-OR-SUBFRAME-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qframe_or_subframe_blackboard_function,
	    STATIC_FUNCTION(frame_or_subframe_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qframe_or_subframe,
	    Qframe_or_subframe_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qframe_or_subframe,Qnil,Qnil,Qnil,Qnil,
	    Qframe_or_subframe_blackboard_function,Qnil,Qnil);
    Qsubframe = STATIC_SYMBOL("SUBFRAME",AB_package);
    Qsubframe_blackboard_function = 
	    STATIC_SYMBOL("SUBFRAME-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qsubframe_blackboard_function,
	    STATIC_FUNCTION(subframe_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qsubframe,Qsubframe_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qsubframe,Qnil,Qnil,Qnil,Qnil,
	    Qsubframe_blackboard_function,Qnil,Qnil);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qtable_blackboard_function = STATIC_SYMBOL("TABLE-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtable_blackboard_function,
	    STATIC_FUNCTION(table_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qtable,Qtable_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qtable,Qnil,Qnil,Qnil,Qnil,
	    Qtable_blackboard_function,Qnil,Qnil);
    Qtable_but_not_kb_item = STATIC_SYMBOL("TABLE-BUT-NOT-KB-ITEM",AB_package);
    Qtable_but_not_kb_item_blackboard_function = 
	    STATIC_SYMBOL("TABLE-BUT-NOT-KB-ITEM-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qtable_but_not_kb_item_blackboard_function,
	    STATIC_FUNCTION(table_but_not_kb_item_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qtable_but_not_kb_item,
	    Qtable_but_not_kb_item_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qtable_but_not_kb_item,Qnil,Qnil,Qnil,Qnil,
	    Qtable_but_not_kb_item_blackboard_function,Qnil,Qnil);
    Qattribute_table_spot = STATIC_SYMBOL("ATTRIBUTE-TABLE-SPOT",AB_package);
    Qattribute_display_spot = STATIC_SYMBOL("ATTRIBUTE-DISPLAY-SPOT",
	    AB_package);
    Qtable_header_spot = STATIC_SYMBOL("TABLE-HEADER-SPOT",AB_package);
    Qsearch_state_table_spot = STATIC_SYMBOL("SEARCH-STATE-TABLE-SPOT",
	    AB_package);
    Qgraph_table_spot = STATIC_SYMBOL("GRAPH-TABLE-SPOT",AB_package);
    Qattribute_table = STATIC_SYMBOL("ATTRIBUTE-TABLE",AB_package);
    Qattribute_table_blackboard_function = 
	    STATIC_SYMBOL("ATTRIBUTE-TABLE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_table_blackboard_function,
	    STATIC_FUNCTION(attribute_table_blackboard_function,NIL,FALSE,
	    1,1));
    mutate_global_property(Qattribute_table,
	    Qattribute_table_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qattribute_table,Qnil,Qnil,Qnil,Qnil,
	    Qattribute_table_blackboard_function,Qnil,Qnil);
    Qshort_representation_table_spot = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-TABLE-SPOT",AB_package);
    Qmultiframe_table_spot = STATIC_SYMBOL("MULTIFRAME-TABLE-SPOT",AB_package);
    Qshort_representation_table = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-TABLE",AB_package);
    Qshort_representation_table_blackboard_function = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-TABLE-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qshort_representation_table_blackboard_function,
	    STATIC_FUNCTION(short_representation_table_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qshort_representation_table,
	    Qshort_representation_table_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qshort_representation_table,Qnil,Qnil,Qnil,Qnil,
	    Qshort_representation_table_blackboard_function,Qnil,Qnil);
    Qtable_spot = STATIC_SYMBOL("TABLE-SPOT",AB_package);
    Qtext_cell_of_table = STATIC_SYMBOL("TEXT-CELL-OF-TABLE",AB_package);
    Qtext_cell_of_table_blackboard_function = 
	    STATIC_SYMBOL("TEXT-CELL-OF-TABLE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_cell_of_table_blackboard_function,
	    STATIC_FUNCTION(text_cell_of_table_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qtext_cell_of_table,
	    Qtext_cell_of_table_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qtext_cell_of_table,Qnil,Qnil,Qnil,Qnil,
	    Qtext_cell_of_table_blackboard_function,Qnil,Qnil);
    Qcell_of_table = STATIC_SYMBOL("CELL-OF-TABLE",AB_package);
    Qcell_of_table_blackboard_function = 
	    STATIC_SYMBOL("CELL-OF-TABLE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qcell_of_table_blackboard_function,
	    STATIC_FUNCTION(cell_of_table_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qcell_of_table,
	    Qcell_of_table_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qcell_of_table,Qnil,Qnil,Qnil,Qnil,
	    Qcell_of_table_blackboard_function,Qnil,Qnil);
    Qattribute_represented_by_table_spot = 
	    STATIC_SYMBOL("ATTRIBUTE-REPRESENTED-BY-TABLE-SPOT",AB_package);
    Qtext_box_spot = STATIC_SYMBOL("TEXT-BOX-SPOT",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qslot_name = STATIC_SYMBOL("SLOT-NAME",AB_package);
    Qslot_name_blackboard_function = 
	    STATIC_SYMBOL("SLOT-NAME-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qslot_name_blackboard_function,
	    STATIC_FUNCTION(slot_name_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qslot_name,Qslot_name_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qslot_name,Qnil,Qnil,Qnil,Qnil,
	    Qslot_name_blackboard_function,Qnil,Qnil);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qdefining_class = STATIC_SYMBOL("DEFINING-CLASS",AB_package);
    Qdefining_class_blackboard_function = 
	    STATIC_SYMBOL("DEFINING-CLASS-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qdefining_class_blackboard_function,
	    STATIC_FUNCTION(defining_class_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qdefining_class,
	    Qdefining_class_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qdefining_class,Qnil,Qnil,Qnil,Qnil,
	    Qdefining_class_blackboard_function,Qnil,Qnil);
    Qslot_component_name_qm = STATIC_SYMBOL("SLOT-COMPONENT-NAME\?",
	    AB_package);
    Qslot_component_name_qm_blackboard_function = 
	    STATIC_SYMBOL("SLOT-COMPONENT-NAME\?-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qslot_component_name_qm_blackboard_function,
	    STATIC_FUNCTION(slot_component_name_qm_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qslot_component_name_qm,
	    Qslot_component_name_qm_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qslot_component_name_qm,Qnil,Qnil,Qnil,Qnil,
	    Qslot_component_name_qm_blackboard_function,Qnil,Qnil);
    Qslot_component_indicator_qm = 
	    STATIC_SYMBOL("SLOT-COMPONENT-INDICATOR\?",AB_package);
    Qslot_component_indicator_qm_blackboard_function = 
	    STATIC_SYMBOL("SLOT-COMPONENT-INDICATOR\?-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qslot_component_indicator_qm_blackboard_function,
	    STATIC_FUNCTION(slot_component_indicator_qm_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qslot_component_indicator_qm,
	    Qslot_component_indicator_qm_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qslot_component_indicator_qm,Qnil,Qnil,Qnil,
	    Qnil,Qslot_component_indicator_qm_blackboard_function,Qnil,Qnil);
    Qitem_represented_by_table_spot = 
	    STATIC_SYMBOL("ITEM-REPRESENTED-BY-TABLE-SPOT",AB_package);
    Qframe_represented_by_table = 
	    STATIC_SYMBOL("FRAME-REPRESENTED-BY-TABLE",AB_package);
    Qframe_represented_by_table_blackboard_function = 
	    STATIC_SYMBOL("FRAME-REPRESENTED-BY-TABLE-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qframe_represented_by_table_blackboard_function,
	    STATIC_FUNCTION(frame_represented_by_table_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qframe_represented_by_table,
	    Qframe_represented_by_table_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qframe_represented_by_table,Qnil,Qnil,Qnil,Qnil,
	    Qframe_represented_by_table_blackboard_function,Qnil,Qnil);
    Qtext_spot = STATIC_SYMBOL("TEXT-SPOT",AB_package);
    Qblock_showing_representation = 
	    STATIC_SYMBOL("BLOCK-SHOWING-REPRESENTATION",AB_package);
    Qblock_showing_representation_blackboard_function = 
	    STATIC_SYMBOL("BLOCK-SHOWING-REPRESENTATION-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qblock_showing_representation_blackboard_function,
	    STATIC_FUNCTION(block_showing_representation_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qblock_showing_representation,
	    Qblock_showing_representation_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qblock_showing_representation,Qnil,Qnil,Qnil,
	    Qnil,Qblock_showing_representation_blackboard_function,Qnil,Qnil);
    Qblock_being_represented = STATIC_SYMBOL("BLOCK-BEING-REPRESENTED",
	    AB_package);
    Qblock_being_represented_blackboard_function = 
	    STATIC_SYMBOL("BLOCK-BEING-REPRESENTED-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qblock_being_represented_blackboard_function,
	    STATIC_FUNCTION(block_being_represented_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qblock_being_represented,
	    Qblock_being_represented_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qblock_being_represented,Qnil,Qnil,Qnil,Qnil,
	    Qblock_being_represented_blackboard_function,Qnil,Qnil);
    Qattribute_display = STATIC_SYMBOL("ATTRIBUTE-DISPLAY",AB_package);
    Qattribute_display_blackboard_function = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAY-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_display_blackboard_function,
	    STATIC_FUNCTION(attribute_display_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qattribute_display,
	    Qattribute_display_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qattribute_display,Qnil,Qnil,Qnil,Qnil,
	    Qattribute_display_blackboard_function,Qnil,Qnil);
    Qattribute_display_text_cell = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAY-TEXT-CELL",AB_package);
    Qattribute_display_text_cell_blackboard_function = 
	    STATIC_SYMBOL("ATTRIBUTE-DISPLAY-TEXT-CELL-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qattribute_display_text_cell_blackboard_function,
	    STATIC_FUNCTION(attribute_display_text_cell_blackboard_function,
	    NIL,FALSE,1,1));
    mutate_global_property(Qattribute_display_text_cell,
	    Qattribute_display_text_cell_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qattribute_display_text_cell,Qnil,Qnil,Qnil,
	    Qnil,Qattribute_display_text_cell_blackboard_function,Qnil,Qnil);
    Qgraph_table = STATIC_SYMBOL("GRAPH-TABLE",AB_package);
    Qgraph_table_blackboard_function = 
	    STATIC_SYMBOL("GRAPH-TABLE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qgraph_table_blackboard_function,
	    STATIC_FUNCTION(graph_table_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qgraph_table,Qgraph_table_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qgraph_table,Qnil,Qnil,Qnil,Qnil,
	    Qgraph_table_blackboard_function,Qnil,Qnil);
    Qline_index = STATIC_SYMBOL("LINE-INDEX",AB_package);
    Qline_index_blackboard_function = 
	    STATIC_SYMBOL("LINE-INDEX-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qline_index_blackboard_function,
	    STATIC_FUNCTION(line_index_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qline_index,Qline_index_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qline_index,Qnil,Qnil,Qnil,Qnil,
	    Qline_index_blackboard_function,Qnil,Qnil);
    Qcharacter_index = STATIC_SYMBOL("CHARACTER-INDEX",AB_package);
    Qcharacter_index_blackboard_function = 
	    STATIC_SYMBOL("CHARACTER-INDEX-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qcharacter_index_blackboard_function,
	    STATIC_FUNCTION(character_index_blackboard_function,NIL,FALSE,
	    1,1));
    mutate_global_property(Qcharacter_index,
	    Qcharacter_index_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qcharacter_index,Qnil,Qnil,Qnil,Qnil,
	    Qcharacter_index_blackboard_function,Qnil,Qnil);
    Qtext_plist = STATIC_SYMBOL("TEXT-PLIST",AB_package);
    Qtext_plist_blackboard_function = 
	    STATIC_SYMBOL("TEXT-PLIST-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qtext_plist_blackboard_function,
	    STATIC_FUNCTION(text_plist_blackboard_function,NIL,FALSE,1,1));
    mutate_global_property(Qtext_plist,Qtext_plist_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qtext_plist,Qnil,Qnil,Qnil,Qnil,
	    Qtext_plist_blackboard_function,Qnil,Qnil);
    Kunknown = STATIC_SYMBOL("UNKNOWN",Pkeyword);
    Qeditable_text_spot_p = STATIC_SYMBOL("EDITABLE-TEXT-SPOT-P",AB_package);
    Qeditable_text_spot_p_blackboard_function = 
	    STATIC_SYMBOL("EDITABLE-TEXT-SPOT-P-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qeditable_text_spot_p_blackboard_function,
	    STATIC_FUNCTION(editable_text_spot_p_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qeditable_text_spot_p,
	    Qeditable_text_spot_p_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qeditable_text_spot_p,Qnil,Qnil,Qnil,Qnil,
	    Qeditable_text_spot_p_blackboard_function,Qnil,Qnil);
    Qframe_for_selection = STATIC_SYMBOL("FRAME-FOR-SELECTION",AB_package);
    Qframe_for_selection_blackboard_function = 
	    STATIC_SYMBOL("FRAME-FOR-SELECTION-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qframe_for_selection_blackboard_function,
	    STATIC_FUNCTION(frame_for_selection_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qframe_for_selection,
	    Qframe_for_selection_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qframe_for_selection,Qnil,Qnil,Qnil,Qnil,
	    Qframe_for_selection_blackboard_function,Qnil,Qnil);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qedit_workspace = STATIC_SYMBOL("EDIT-WORKSPACE",AB_package);
    Qmost_interesting_frame = STATIC_SYMBOL("MOST-INTERESTING-FRAME",
	    AB_package);
    Qmost_interesting_frame_blackboard_function = 
	    STATIC_SYMBOL("MOST-INTERESTING-FRAME-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmost_interesting_frame_blackboard_function,
	    STATIC_FUNCTION(most_interesting_frame_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qmost_interesting_frame,
	    Qmost_interesting_frame_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qmost_interesting_frame,Qnil,Qnil,Qnil,Qnil,
	    Qmost_interesting_frame_blackboard_function,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qmost_interesting_frame,
	    STATIC_FUNCTION(most_interesting_frame,NIL,FALSE,1,1));
    Qthing_to_select = STATIC_SYMBOL("THING-TO-SELECT",AB_package);
    Qthing_to_select_blackboard_function = 
	    STATIC_SYMBOL("THING-TO-SELECT-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qthing_to_select_blackboard_function,
	    STATIC_FUNCTION(thing_to_select_blackboard_function,NIL,FALSE,
	    1,1));
    mutate_global_property(Qthing_to_select,
	    Qthing_to_select_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qthing_to_select,Qnil,Qnil,Qnil,Qnil,
	    Qthing_to_select_blackboard_function,Qnil,Qnil);
    Qselected_image_plane = STATIC_SYMBOL("SELECTED-IMAGE-PLANE",AB_package);
    Qselected_image_plane_blackboard_function = 
	    STATIC_SYMBOL("SELECTED-IMAGE-PLANE-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qselected_image_plane_blackboard_function,
	    STATIC_FUNCTION(selected_image_plane_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qselected_image_plane,
	    Qselected_image_plane_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qselected_image_plane,Qnil,Qnil,Qnil,Qnil,
	    Qselected_image_plane_blackboard_function,Qnil,Qnil);
    Qselected_workspace = STATIC_SYMBOL("SELECTED-WORKSPACE",AB_package);
    Qselected_workspace_blackboard_function = 
	    STATIC_SYMBOL("SELECTED-WORKSPACE-BLACKBOARD-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qselected_workspace_blackboard_function,
	    STATIC_FUNCTION(selected_workspace_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qselected_workspace,
	    Qselected_workspace_blackboard_function,Qmagic_argument_fetcher);
    make_presentation_type(Qselected_workspace,Qnil,Qnil,Qnil,Qnil,
	    Qselected_workspace_blackboard_function,Qnil,Qnil);
    Qselected_native_window = STATIC_SYMBOL("SELECTED-NATIVE-WINDOW",
	    AB_package);
    Qselected_native_window_blackboard_function = 
	    STATIC_SYMBOL("SELECTED-NATIVE-WINDOW-BLACKBOARD-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qselected_native_window_blackboard_function,
	    STATIC_FUNCTION(selected_native_window_blackboard_function,NIL,
	    FALSE,1,1));
    mutate_global_property(Qselected_native_window,
	    Qselected_native_window_blackboard_function,
	    Qmagic_argument_fetcher);
    make_presentation_type(Qselected_native_window,Qnil,Qnil,Qnil,Qnil,
	    Qselected_native_window_blackboard_function,Qnil,Qnil);
    Qcollect_menu_item = STATIC_SYMBOL("COLLECT-MENU-ITEM",AB_package);
    SET_SYMBOL_FUNCTION(Qcollect_menu_item,
	    STATIC_FUNCTION(collect_menu_item,NIL,FALSE,3,3));
    Qnew_workspace = STATIC_SYMBOL("NEW-WORKSPACE",AB_package);
    Qget_workspace = STATIC_SYMBOL("GET-WORKSPACE",AB_package);
    Qstatusbar = STATIC_SYMBOL("STATUSBAR",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qnew_workspace,
	    Qget_workspace,Qstatusbar);
    Main_menu_restriction_type_exceptions = list_constant_7;
    Qprint_to_server = STATIC_SYMBOL("PRINT-TO-SERVER",AB_package);
    Qprint_to_client = STATIC_SYMBOL("PRINT-TO-CLIENT",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qprint_to_server,
	    Qprint_to_client);
    Workspace_menu_restriction_type_exceptions = list_constant_8;
    Qmain_menu = STATIC_SYMBOL("MAIN-MENU",AB_package);
    Qworkspace_menu = STATIC_SYMBOL("WORKSPACE-MENU",AB_package);
    Qfind_menu_item_internal = STATIC_SYMBOL("FIND-MENU-ITEM-INTERNAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfind_menu_item_internal,
	    STATIC_FUNCTION(find_menu_item_internal,NIL,FALSE,3,3));
    Qitem_menu = STATIC_SYMBOL("ITEM-MENU",AB_package);
    Qtable_menu = STATIC_SYMBOL("TABLE-MENU",AB_package);
    Qg2_defstruct_structure_name_hot_spot_state_g2_struct = 
	    STATIC_SYMBOL("HOT-SPOT-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhot_spot_state = STATIC_SYMBOL("HOT-SPOT-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_hot_spot_state_g2_struct,
	    Qhot_spot_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qhot_spot_state,
	    Qg2_defstruct_structure_name_hot_spot_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_hot_spot_state == UNBOUND)
	The_type_description_of_hot_spot_state = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83iWy1p83iWy830Vy83-Sy8n8k1l830Vy0000001m1n8y83-4Dy1t831Cy831Ky831Oy83-6jy83-=Vy83-1xy83-F7y83-C0y83qiy1m8x830Vyk3Eyk0k0");
    temp = The_type_description_of_hot_spot_state;
    The_type_description_of_hot_spot_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_hot_spot_state_g2_struct,
	    The_type_description_of_hot_spot_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qhot_spot_state,
	    The_type_description_of_hot_spot_state,Qtype_description_of_type);
    Qoutstanding_hot_spot_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-HOT-SPOT-STATE-COUNT",AB_package);
    Qhot_spot_state_structure_memory_usage = 
	    STATIC_SYMBOL("HOT-SPOT-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_17 = STATIC_STRING("1q83iWy8s83-YEy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_hot_spot_state_count);
    push_optimized_constant(Qhot_spot_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_hot_spot_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-HOT-SPOT-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_hot_spot_states,
	    Chain_of_available_hot_spot_states);
    record_system_variable(Qchain_of_available_hot_spot_states,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qhot_spot_state_count = STATIC_SYMBOL("HOT-SPOT-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhot_spot_state_count,Hot_spot_state_count);
    record_system_variable(Qhot_spot_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_hot_spot_states_vector == UNBOUND)
	Chain_of_available_hot_spot_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qhot_spot_state_structure_memory_usage,
	    STATIC_FUNCTION(hot_spot_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_hot_spot_state_count,
	    STATIC_FUNCTION(outstanding_hot_spot_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_hot_spot_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_hot_spot_state,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qhot_spot_state,
	    reclaim_structure_for_hot_spot_state_1);
    Qtop_level_with_selection_focus_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-WITH-SELECTION-FOCUS-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qhot_spot_state,
	    Qtop_level_with_selection_focus_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qhot_spot = STATIC_SYMBOL("HOT-SPOT",AB_package);
    Qglobal_development = STATIC_SYMBOL("GLOBAL-DEVELOPMENT",AB_package);
    Qhot_spot_gestures = STATIC_SYMBOL("HOT-SPOT-GESTURES",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qglobal_development,
	    Qhot_spot_gestures);
    make_context_description(Qhot_spot,Qnil,Qt,list_constant_9);
    Qmouse_up_in_hot_spot = STATIC_SYMBOL("MOUSE-UP-IN-HOT-SPOT",AB_package);
    Qmouse_motion_in_hot_spot = STATIC_SYMBOL("MOUSE-MOTION-IN-HOT-SPOT",
	    AB_package);
    Qabort_hot_spot = STATIC_SYMBOL("ABORT-HOT-SPOT",AB_package);
    string_constant_18 = STATIC_STRING("1n1n830-y8k9k1n830+y8k9l1n831-y8k9m");
    clear_optimized_constants();
    push_optimized_constant(Qmouse_up_in_hot_spot);
    push_optimized_constant(Qmouse_motion_in_hot_spot);
    push_optimized_constant(Qabort_hot_spot);
    make_keymap(Qhot_spot_gestures,Qhot_spot_gestures,
	    regenerate_optimized_constant(string_constant_18),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    mutate_global_property(Qmouse_motion_in_hot_spot,
	    Qmouse_motion_in_hot_spot,Qnew_style_event_handler);
    Kexit_hot_spot = STATIC_SYMBOL("EXIT-HOT-SPOT",Pkeyword);
    Kenter_hot_spot = STATIC_SYMBOL("ENTER-HOT-SPOT",Pkeyword);
    Kidle = STATIC_SYMBOL("IDLE",Pkeyword);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_hot_spot,
	    STATIC_FUNCTION(mouse_motion_in_hot_spot,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_up_in_hot_spot,Qmouse_up_in_hot_spot,
	    Qnew_style_event_handler);
    Kmouse_up = STATIC_SYMBOL("MOUSE-UP",Pkeyword);
    Kunwind = STATIC_SYMBOL("UNWIND",Pkeyword);
    SET_SYMBOL_FUNCTION(Qmouse_up_in_hot_spot,
	    STATIC_FUNCTION(mouse_up_in_hot_spot,NIL,FALSE,1,1));
    mutate_global_property(Qabort_hot_spot,Qabort_hot_spot,
	    Qnew_style_event_handler);
    Kaborted = STATIC_SYMBOL("ABORTED",Pkeyword);
    SET_SYMBOL_FUNCTION(Qabort_hot_spot,STATIC_FUNCTION(abort_hot_spot,NIL,
	    FALSE,1,1));
    float_constant = STATIC_FLOAT(0.3);
    Scrolling_autorepeat_interval = float_constant;
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qscrolling_heartbeat = STATIC_SYMBOL("SCROLLING-HEARTBEAT",AB_package);
    SET_SYMBOL_FUNCTION(Qscrolling_heartbeat,
	    STATIC_FUNCTION(scrolling_heartbeat,NIL,FALSE,1,1));
    Kmouse_down = STATIC_SYMBOL("MOUSE-DOWN",Pkeyword);
    Qg2_defstruct_structure_name_stepper_of_scroll_bar_spot_g2_struct = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdo_scrolling = STATIC_SYMBOL("DO-SCROLLING",AB_package);
    Kfinished = STATIC_SYMBOL("FINISHED",Pkeyword);
    Kcanceled = STATIC_SYMBOL("CANCELED",Pkeyword);
    Qenable_autorepeat_after_drawing = 
	    STATIC_SYMBOL("ENABLE-AUTOREPEAT-AFTER-DRAWING",AB_package);
    SET_SYMBOL_FUNCTION(Qenable_autorepeat_after_drawing,
	    STATIC_FUNCTION(enable_autorepeat_after_drawing,NIL,FALSE,2,2));
    Qg2_defstruct_structure_name_elevator_of_scroll_bar_spot_g2_struct = 
	    STATIC_SYMBOL("ELEVATOR-OF-SCROLL-BAR-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    Qgensym_scroll_bar_elevator_frame_component = 
	    STATIC_SYMBOL("GENSYM-SCROLL-BAR-ELEVATOR-FRAME-COMPONENT",
	    AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qgensym_left_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-LEFT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qup = STATIC_SYMBOL("UP",AB_package);
    Qgensym_up_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-UP-SCROLL-ARROW-FRAME-COMPONENT",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qgensym_right_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-RIGHT-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qdown = STATIC_SYMBOL("DOWN",AB_package);
    Qgensym_down_scroll_arrow_frame_component = 
	    STATIC_SYMBOL("GENSYM-DOWN-SCROLL-ARROW-FRAME-COMPONENT",
	    AB_package);
    Qdark_grey = STATIC_SYMBOL("DARK-GREY",AB_package);
    Qlight_grey = STATIC_SYMBOL("LIGHT-GREY",AB_package);
    Qface_color = STATIC_SYMBOL("FACE-COLOR",AB_package);
    Qenter_hot_spot_state_upon_frame_component = 
	    STATIC_SYMBOL("ENTER-HOT-SPOT-STATE-UPON-FRAME-COMPONENT",
	    AB_package);
    mutate_global_property(Qenter_hot_spot_state_upon_frame_component,
	    Qenter_hot_spot_state_upon_frame_component,
	    Qnew_style_event_handler);
    Qscroll_bar_hot_spot_method = 
	    STATIC_SYMBOL("SCROLL-BAR-HOT-SPOT-METHOD",AB_package);
    SET_SYMBOL_FUNCTION(Qscroll_bar_hot_spot_method,
	    STATIC_FUNCTION(scroll_bar_hot_spot_method,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qenter_hot_spot_state_upon_frame_component,
	    STATIC_FUNCTION(enter_hot_spot_state_upon_frame_component,NIL,
	    FALSE,1,1));
    Qg2_defstruct_structure_name_elevator_state_g2_struct = 
	    STATIC_SYMBOL("ELEVATOR-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qelevator_state = STATIC_SYMBOL("ELEVATOR-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_elevator_state_g2_struct,
	    Qelevator_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qelevator_state,
	    Qg2_defstruct_structure_name_elevator_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_elevator_state == UNBOUND)
	The_type_description_of_elevator_state = Nil;
    string_constant_19 = 
	    STATIC_STRING("43Dy8m83h=y1p83h=y830Vy83-Sy8n8k1l830Vy0000001m1n8y83-3Wy1n831Cy831Ky831Oy1m8x830Vykzk0k0");
    temp = The_type_description_of_elevator_state;
    The_type_description_of_elevator_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_19));
    mutate_global_property(Qg2_defstruct_structure_name_elevator_state_g2_struct,
	    The_type_description_of_elevator_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qelevator_state,
	    The_type_description_of_elevator_state,Qtype_description_of_type);
    Qoutstanding_elevator_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-ELEVATOR-STATE-COUNT",AB_package);
    Qelevator_state_structure_memory_usage = 
	    STATIC_SYMBOL("ELEVATOR-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_20 = STATIC_STRING("1q83h=y8s83-SWy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_elevator_state_count);
    push_optimized_constant(Qelevator_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_20));
    Qchain_of_available_elevator_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ELEVATOR-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_elevator_states,
	    Chain_of_available_elevator_states);
    record_system_variable(Qchain_of_available_elevator_states,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qelevator_state_count = STATIC_SYMBOL("ELEVATOR-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qelevator_state_count,Elevator_state_count);
    record_system_variable(Qelevator_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_elevator_states_vector == UNBOUND)
	Chain_of_available_elevator_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qelevator_state_structure_memory_usage,
	    STATIC_FUNCTION(elevator_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_elevator_state_count,
	    STATIC_FUNCTION(outstanding_elevator_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_elevator_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_elevator_state,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qelevator_state,
	    reclaim_structure_for_elevator_state_1);
    mutate_global_property(Qelevator_state,
	    Qtop_level_with_selection_focus_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qelevator = STATIC_SYMBOL("ELEVATOR",AB_package);
    make_context_description(Qelevator,Qnil,Qt,Qnil);
    Qmouse_up_in_elevator_state = 
	    STATIC_SYMBOL("MOUSE-UP-IN-ELEVATOR-STATE",AB_package);
    Qmouse_motion_in_elevator_state = 
	    STATIC_SYMBOL("MOUSE-MOTION-IN-ELEVATOR-STATE",AB_package);
    Qabort_elevator_state = STATIC_SYMBOL("ABORT-ELEVATOR-STATE",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qmouse_up_in_elevator_state);
    push_optimized_constant(Qmouse_motion_in_elevator_state);
    push_optimized_constant(Qabort_elevator_state);
    make_keymap(Qelevator,Qelevator,
	    regenerate_optimized_constant(string_constant_18),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qelevator,Qelevator);
    Qenter_elevator_state = STATIC_SYMBOL("ENTER-ELEVATOR-STATE",AB_package);
    mutate_global_property(Qenter_elevator_state,Qenter_elevator_state,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qenter_elevator_state,
	    STATIC_FUNCTION(enter_elevator_state,NIL,FALSE,1,1));
    mutate_global_property(Qabort_elevator_state,Qabort_elevator_state,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qabort_elevator_state,
	    STATIC_FUNCTION(abort_elevator_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_up_in_elevator_state,
	    Qmouse_up_in_elevator_state,Qnew_style_event_handler);
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Qposition_of_horizontal_elevator = 
	    STATIC_SYMBOL("POSITION-OF-HORIZONTAL-ELEVATOR",AB_package);
    Qposition_of_vertical_elevator = 
	    STATIC_SYMBOL("POSITION-OF-VERTICAL-ELEVATOR",AB_package);
    Kdraw_as_soon_as_possible = STATIC_SYMBOL("DRAW-AS-SOON-AS-POSSIBLE",
	    Pkeyword);
    SET_SYMBOL_FUNCTION(Qmouse_up_in_elevator_state,
	    STATIC_FUNCTION(mouse_up_in_elevator_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_motion_in_elevator_state,
	    Qmouse_motion_in_elevator_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_motion_in_elevator_state,
	    STATIC_FUNCTION(mouse_motion_in_elevator_state,NIL,FALSE,1,1));
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Minimum_distance_to_move_mouse_to_be_dragging = FIX((SI_Long)3L);
    Minimum_time_that_must_pass_to_be_dragging = FIX((SI_Long)1000L);
    Overshoot_distance_around_menus_before_beginning_dragging = 
	    FIX((SI_Long)50L);
    Qg2_defstruct_structure_name_loose_end_spot_g2_struct = 
	    STATIC_SYMBOL("LOOSE-END-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhighlight_color = STATIC_SYMBOL("HIGHLIGHT-COLOR",AB_package);
    Qtoken_menu = STATIC_SYMBOL("TOKEN-MENU",AB_package);
    Qreplace_fragments_on_sides_qm = 
	    STATIC_SYMBOL("REPLACE-FRAGMENTS-ON-SIDES\?",AB_package);
    Qreplace_entire_text_qm = STATIC_SYMBOL("REPLACE-ENTIRE-TEXT\?",
	    AB_package);
    Qpathname_component_token_menu = 
	    STATIC_SYMBOL("PATHNAME-COMPONENT-TOKEN-MENU",AB_package);
    Qpathname_component_conversion = 
	    STATIC_SYMBOL("PATHNAME-COMPONENT-CONVERSION",AB_package);
    Standard_remote_submenu_depth = FIX((SI_Long)5L);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qcenter_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("CENTER-ALIGNED-CASCADE-MENU-ITEM-FORMAT",
	    AB_package);
    Qright_aligned_cascade_menu_item_format = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-CASCADE-MENU-ITEM-FORMAT",AB_package);
    Qcenter_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("CENTER-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qright_aligned_cascade_menu_item_format_new_large = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-LARGE",
	    AB_package);
    Qcenter_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("CENTER-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    Qright_aligned_cascade_menu_item_format_new_small = 
	    STATIC_SYMBOL("RIGHT-ALIGNED-CASCADE-MENU-ITEM-FORMAT-NEW-SMALL",
	    AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)9L,
	    Qleft_aligned_cascade_menu_item_format,
	    Qcenter_aligned_cascade_menu_item_format,
	    Qright_aligned_cascade_menu_item_format,
	    Qleft_aligned_cascade_menu_item_format_new_large,
	    Qcenter_aligned_cascade_menu_item_format_new_large,
	    Qright_aligned_cascade_menu_item_format_new_large,
	    Qleft_aligned_cascade_menu_item_format_new_small,
	    Qcenter_aligned_cascade_menu_item_format_new_small,
	    Qright_aligned_cascade_menu_item_format_new_small);
    Qexecute_native_menu_choice = 
	    STATIC_SYMBOL("EXECUTE-NATIVE-MENU-CHOICE",AB_package);
    mutate_global_property(Qexecute_native_menu_choice,
	    Qexecute_native_menu_choice,Qnew_style_event_handler);
    Qmenu_handle = STATIC_SYMBOL("MENU-HANDLE",AB_package);
    Qitem_number = STATIC_SYMBOL("ITEM-NUMBER",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_native_menu_choice,
	    STATIC_FUNCTION(execute_native_menu_choice,NIL,FALSE,1,1));
}
