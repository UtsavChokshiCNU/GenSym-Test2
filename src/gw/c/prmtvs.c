/* prmtvs.c
 * Input file:  primitives.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "prmtvs.h"


Object G2int_one_integer = UNBOUND;

Object G2int_minus_one_integer = UNBOUND;

/* MAKE-PERMANENT-LIST */
Object g2int_make_permanent_list(length_1)
    Object length_1;
{
    Object new_list;
    XDeclare_area(1);

    x_note_fn_call(13,0);
    new_list = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	new_list = make_list(1,length_1);
    POP_AREA(0);
    return VALUES_1(new_list);
}

Object G2int_global_property_conses = UNBOUND;

/* MUTATE-GLOBAL-PROPERTY */
Object g2int_mutate_global_property(symbol_1,value,property_1)
    Object symbol_1, value, property_1;
{
    Object original_plist, property_cons, property_value_cons;
    Object new_property_cons, new_value_cons;

    x_note_fn_call(13,1);
    original_plist = SYMBOL_PLIST(symbol_1);
    property_cons = original_plist;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(property_1,M_CAR(property_cons))) {
	property_cons = M_CDR(property_cons);
	property_value_cons = property_cons;
	goto end;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    property_value_cons = Qnil;
  end:;
    if (property_value_cons)
	M_CAR(property_value_cons) = value;
    else {
	new_property_cons = G2int_global_property_conses;
	if ( !TRUEP(new_property_cons))
	    new_property_cons = g2int_make_permanent_list(FIX((SI_Long)200L));
	new_value_cons = M_CDR(new_property_cons);
	G2int_global_property_conses = M_CDR(new_value_cons);
	M_CAR(new_property_cons) = property_1;
	M_CAR(new_value_cons) = value;
	M_CDR(new_value_cons) = original_plist;
	SET_SYMBOL_PLIST(symbol_1,new_property_cons);
    }
    return VALUES_1(value);
}

Object G2int_object_pool_meters = UNBOUND;

Object G2int_names_of_interesting_system_object_pools = UNBOUND;

/* PM-ELT */
Object g2int_pm_elt(object,index_1)
    Object object, index_1;
{
    x_note_fn_call(13,2);
    if (CONSP(object))
	return nth(index_1,object);
    else if (ARRAYP(object))
	return aref1(object,index_1);
    else
	return VALUES_1(FIX((SI_Long)-1234567L));
}

/* PM-NTHCDR */
Object g2int_pm_nthcdr(object,index_1)
    Object object, index_1;
{
    x_note_fn_call(13,3);
    if (CONSP(object))
	return nthcdr(index_1,object);
    else
	return VALUES_1(FIX((SI_Long)-1234567L));
}

/* PM-TYPE-OF */
Object g2int_pm_type_of(object)
    Object object;
{
    x_note_fn_call(13,4);
    if ( !TRUEP(object))
	return VALUES_1(Qnull);
    else if (SYMBOLP(object) || STRINGP(object) || NUMBERP(object))
	return VALUES_1(LIST_2(Qmember,object));
    else if (CONSP(object))
	return VALUES_1(Qcons);
    else if (ARRAYP(object))
	return VALUES_1(LIST_3(Qarray,array_element_type(object),
		length(object)));
    else
	return VALUES_1(Qnil);
}

static Object Qg2int_composite_object;  /* composite-object */

/* PM-COMPOSITE-TYPE-OF */
Object g2int_pm_composite_type_of(object)
    Object object;
{
    Object temp, element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(13,5);
    if (ARRAYP(object) || CONSP(object)) {
	temp = g2int_pm_type_of(object);
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(object));
	element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	element = elt(object,FIX(i));
	ab_loopvar__2 = LIST_1(g2int_pm_type_of(element));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end;
	temp_1 = Qnil;
      end:;
	return list_star(3,Qg2int_composite_object,temp,temp_1);
    }
    else
	return g2int_pm_type_of(object);
}

Object G2int_single_element_string = UNBOUND;

static Object string_constant;     /* "#w\"" */

static Object string_constant_1;   /* " " */

static Object string_constant_2;   /* "\"" */

/* PM-PRINT-WIDE-STRING */
Object g2int_pm_print_wide_string(thing)
    Object thing;
{
    Object elt_1, elt_arg_1, elt_new_value;
    SI_Long i;

    x_note_fn_call(13,6);
    princ(string_constant,_);
    i = (SI_Long)0L;
    elt_1 = Nil;
  next_loop:
    elt_1 = aref1(thing,FIX(i));
    if (IFIX(elt_1) == (SI_Long)0L)
	goto end_loop;
    if (g2int_newline_p(elt_1))
	terpri(_);
    else if (IFIX(elt_1) == (SI_Long)32L)
	princ(string_constant_1,_);
    else {
	elt_arg_1 = G2int_single_element_string;
	elt_new_value = CODE_CHAR(elt_1);
	set_elt(elt_arg_1,FIX((SI_Long)0L),elt_new_value);
	princ(G2int_single_element_string,_);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    princ(string_constant_2,_);
    return VALUES_1(Qnil);
}

/* PM-PRINT-SUBSTRUCTURE */
Object g2int_pm_print_substructure(object,max_depth,depth)
    Object object, max_depth, depth;
{
    Object element;
    SI_Long i, ab_loop_bind_, j, ab_loop_bind__1;

    x_note_fn_call(13,7);
    if (FIXNUMP(max_depth) && FIXNUM_GT(depth,max_depth))
	format((SI_Long)3L,T,"~s~%",object);
    else if (STRINGP(object))
	format((SI_Long)3L,T,"~s~%",object);
    else if (g2int_text_string_p(object)) {
	g2int_pm_print_wide_string(object);
	terpri(_);
    }
    else if (ARRAYP(object) || CONSP(object)) {
	format((SI_Long)3L,T,"~s:~%",g2int_pm_type_of(object));
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(object));
	element = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	element = elt(object,FIX(i));
	j = (SI_Long)0L;
	ab_loop_bind__1 = IFIX(depth) * (SI_Long)2L;
      next_loop_1:
	if (j > ab_loop_bind__1)
	    goto end_loop_1;
	format((SI_Long)2L,T," ");
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	format((SI_Long)3L,T,"[~d] ",FIX(i));
	g2int_pm_print_substructure(element,max_depth,FIXNUM_ADD1(depth));
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else
	format((SI_Long)3L,T,"~s~%",object);
    return VALUES_1(Nil);
}

/* PM-PRINT-STRUCTURE */
Object g2int_pm_print_structure(object,max_depth)
    Object object, max_depth;
{
    x_note_fn_call(13,8);
    g2int_pm_print_substructure(object,max_depth,FIX((SI_Long)0L));
    return VALUES_1(object);
}

static Object string_constant_3;   /* "-G2-STRUCT" */

/* PM-STRUCTURE-TYPE */
Object g2int_pm_structure_type(thing)
    Object thing;
{
    Object raw_type_name, string_1, suffix, n_1, tail, temp;

    x_note_fn_call(13,9);
    if (SIMPLE_VECTOR_P(thing) && IFIX(length(thing)) > (SI_Long)1L) {
	raw_type_name = aref1(thing,FIX((SI_Long)0L));
	if (SYMBOLP(raw_type_name)) {
	    string_1 = SYMBOL_NAME(raw_type_name);
	    suffix = string_constant_3;
	    n_1 = SIMPLE_ARRAY_ANY_1_LENGTH(suffix);
	    tail = FIXNUM_MINUS(length(string_1),n_1);
	    if (IFIX(tail) > (SI_Long)0L && string_eq(4,string_1,suffix,
		    Kstart1,tail)) {
		temp = intern(subseq(string_1,FIX((SI_Long)0L),tail),
			G2int_ab_package_1);
		return VALUES_1(temp);
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

static Object Qg2int_available_frame_vector;  /* available-frame-vector */

/* PM-FRAME-TYPE */
Object g2int_pm_frame_type(thing)
    Object thing;
{
    Object x;

    x_note_fn_call(13,10);
    if (SIMPLE_VECTOR_P(thing) && IFIX(length(thing)) > (SI_Long)2L) {
	x = ISVREF(thing,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(x))
	    return VALUES_1(ISVREF(x,(SI_Long)1L));
	else if (EQ(x,Qg2int_available_frame_vector))
	    return VALUES_1(Qg2int_available_frame_vector);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_managed_float;  /* managed-float */

/* PM-GENSYM-TYPE-OF */
Object g2int_pm_gensym_type_of(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(13,11);
    temp = g2int_pm_frame_type(thing);
    if (temp);
    else
	temp = g2int_pm_structure_type(thing);
    if (temp);
    else
	temp = g2int_managed_float_p_function(thing) ? 
		Qg2int_managed_float : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return type_of(thing);
}

Object G2int_pm_file_names = UNBOUND;

Object G2int_pm_slot_names = UNBOUND;

/* PM-SLOT-NAMES */
Object g2int_pm_slot_names(vector_1)
    Object vector_1;
{
    Object filename, ab_loop_list_, filename_qm, stream, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(13,12);
    SAVE_STACK();
    if ( !TRUEP(G2int_pm_slot_names)) {
	filename = Nil;
	ab_loop_list_ = G2int_pm_file_names;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	filename = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (g2int_gensym_probe_file(filename)) {
	    filename_qm = filename;
	    goto end;
	}
	goto next_loop;
      end_loop:
	filename_qm = Qnil;
      end:;
	if (filename_qm) {
	    format((SI_Long)3L,T,"[Reading slotnames from ~s]~%",filename_qm);
	    stream = lopen(1,filename_qm);
	    if (PUSH_UNWIND_PROTECT(0))
		G2int_pm_slot_names = lread(stream,Nil,_,_);
	    POP_UNWIND_PROTECT(0);
	    if (STREAMP(stream))
		lclose(1,stream);
	    CONTINUE_UNWINDING(0);
	}
    }
    temp = g2int_pm_structure_type(vector_1);
    if (temp);
    else
	temp = g2int_pm_frame_type(vector_1);
    temp = g2int_assq_function(temp,G2int_pm_slot_names);
    RESTORE_STACK();
    return VALUES_1(CDR(temp));
}

Object G2int_pm_max_length = UNBOUND;

static Object string_constant_4;   /* " is a " */

static Object string_constant_5;   /* " aka " */

static Object list_constant;       /* # */

static Object string_constant_6;   /* "  " */

static Object string_constant_7;   /* "CDR" */

/* PM-DESCRIBE */
Object g2int_pm_describe(thing)
    Object thing;
{
    Object max_length, temp, names, elt_1, name, names_old_value, sublist;
    Object ab_loop_iter_flag_;
    SI_Long ab_loop_bind_, i;
    char temp_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,13);
    if (PUSH_AREA(Dynamic_area,0)) {
	max_length = G2int_pm_max_length;
	g2int_pm_prin1(thing);
	princ(string_constant_4,_);
	prin1(g2int_pm_gensym_type_of(thing),_);
	princ(string_constant_5,_);
	prin1(type_of(thing),_);
	terpri(_);
	if (ARRAYP(thing)) {
	    temp = array_element_type(thing);
	    temp_1 = EQUAL(list_constant,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? FIXNUM_EQ(FIX((SI_Long)1L),ARRAY_RANK(thing)) : 
		TRUEP(Nil)) {
	    g2int_pm_print_wide_string(thing);
	    terpri(_);
	}
	else if (VECTORP(thing)) {
	    names = g2int_pm_slot_names(thing);
	    temp = length(thing);
	    ab_loop_bind_ = IFIX(FIXNUM_MIN(temp,max_length));
	    i = (SI_Long)0L;
	    elt_1 = Nil;
	    name = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    elt_1 = aref1(thing,FIX(i));
	    names_old_value = names;
	    temp = FIRST(names_old_value);
	    names = REST(names_old_value);
	    name = temp;
	    format((SI_Long)3L,T,"[~2d] ",FIX(i));
	    if (name)
		format((SI_Long)3L,T," ~50a ",name);
	    g2int_pm_print_object_id(elt_1);
	    princ(string_constant_6,_);
	    g2int_pm_print(elt_1);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else if (CONSP(thing)) {
	    sublist = thing;
	    temp = length(thing);
	    ab_loop_bind_ = IFIX(FIXNUM_MIN(temp,max_length));
	    i = (SI_Long)0L;
	    elt_1 = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(sublist))
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_iter_flag_))
		i = i + (SI_Long)1L;
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    elt_1 = CAR(sublist);
	    format((SI_Long)3L,T,"[~2d] ",FIX(i));
	    if (Nil)
		format((SI_Long)3L,T," ~50a ",Nil);
	    g2int_pm_print_object_id(elt_1);
	    princ(string_constant_6,_);
	    g2int_pm_print(elt_1);
	    temp = CDR(sublist);
	    if (ATOM(temp) && CDR(sublist)) {
		format((SI_Long)3L,T,"[~2d] ",string_constant_7);
		if (Nil)
		    format((SI_Long)3L,T," ~50a ",Nil);
		g2int_pm_print_object_id(CDR(sublist));
		princ(string_constant_6,_);
		g2int_pm_print(CDR(sublist));
	    }
	    ab_loop_iter_flag_ = Nil;
	    sublist = M_CDR(sublist);
	    goto next_loop_1;
	  end_loop_1:;
	}
	result = VALUES_1(thing);
    }
    POP_AREA(0);
    return result;
}

Object G2int_pm_temp_string = UNBOUND;

static Object string_constant_8;   /* "0123456789abcdef" */

/* PM-OBJECT-ID */
Object g2int_pm_object_id(object)
    Object object;
{
    Object addr_1, char_arg_1, temp;
    SI_Long i;
    char char_new_value;

    x_note_fn_call(13,14);
    addr_1 = g2int_pctpointer(object);
    i = (SI_Long)9L;
  next_loop:
    if (i < (SI_Long)2L)
	goto end_loop;
    char_arg_1 = G2int_pm_temp_string;
    char_new_value = ICHAR(string_constant_8,IFIX(addr_1) & (SI_Long)15L);
    SET_ICHAR(char_arg_1,i,char_new_value);
    addr_1 = FIX(IFIX(addr_1) >>  -  - (SI_Long)4L);
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    char_arg_1 = G2int_pm_temp_string;
    temp = CHR('0');
    SET_CHAR(char_arg_1,FIX((SI_Long)0L),temp);
    char_arg_1 = G2int_pm_temp_string;
    temp = CHR('x');
    SET_CHAR(char_arg_1,FIX((SI_Long)1L),temp);
    return VALUES_1(G2int_pm_temp_string);
}

/* PM-PRINT-OBJECT-ID */
Object g2int_pm_print_object_id(object)
    Object object;
{
    x_note_fn_call(13,15);
    return g2int_pm_prin1(g2int_pm_object_id(object));
}

/* PM-PRINT */
Object g2int_pm_print(thing)
    Object thing;
{
    x_note_fn_call(13,16);
    g2int_pm_prin1(thing);
    terpri(_);
    return VALUES_1(thing);
}

/* PM-PRINC */
Object g2int_pm_princ(thing)
    Object thing;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,17);
    if (PUSH_AREA(Dynamic_area,0))
	result = princ(thing,_);
    POP_AREA(0);
    return result;
}

static Object string_constant_9;   /* "~A" */

static Object string_constant_10;  /* "#<Managed-Float " */

static Object string_constant_11;  /* ">" */

static Object string_constant_12;  /* "#<" */

static Object string_constant_13;  /* "(" */

static Object string_constant_14;  /* " . " */

static Object string_constant_15;  /* ")" */

/* PM-PRIN1 */
Object g2int_pm_prin1(thing)
    Object thing;
{
    Object print_circle, wide_string, gensym_string, car_1, rest_1;
    Object ab_loop_list_;
    Declare_special(1);
    XDeclare_area(1);

    x_note_fn_call(13,18);
    if (PUSH_AREA(Dynamic_area,0)) {
	print_circle = T;
	PUSH_SPECIAL(Print_circle,print_circle,0);
	  if (g2int_text_string_p(thing))
	      g2int_pm_print_wide_string(thing);
	  else if (g2int_managed_float_p_function(thing)) {
	      wide_string = g2int_tformat_text_string(2,string_constant_9,
		      thing);
	      gensym_string = g2int_wide_string_to_gensym_string(wide_string);
	      princ(string_constant_10,_);
	      princ(gensym_string,_);
	      princ(string_constant_1,_);
	      g2int_pm_print_object_id(thing);
	      princ(string_constant_11,_);
	      g2int_reclaim_text_string(wide_string);
	      g2int_reclaim_gensym_string(gensym_string);
	  }
	  else if (g2int_pm_structure_type(thing)) {
	      princ(string_constant_12,_);
	      princ(g2int_pm_structure_type(thing),_);
	      princ(string_constant_1,_);
	      princ(g2int_pm_object_id(thing),_);
	      princ(string_constant_11,_);
	  }
	  else if (g2int_pm_frame_type(thing)) {
	      princ(string_constant_12,_);
	      princ(g2int_pm_frame_type(thing),_);
	      princ(string_constant_1,_);
	      g2int_pm_print_object_id(thing);
	      princ(string_constant_11,_);
	  }
	  else if (CONSP(thing)) {
	      princ(string_constant_13,_);
	      car_1 = Nil;
	      rest_1 = Nil;
	      ab_loop_list_ = thing;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      car_1 = CAR(ab_loop_list_);
	      rest_1 = CDR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      g2int_pm_prin1(car_1);
	      if ( !TRUEP(rest_1));
	      else if (CONSP(rest_1))
		  princ(string_constant_1,_);
	      else {
		  princ(string_constant_14,_);
		  g2int_pm_prin1(rest_1);
		  goto end_loop;
	      }
	      goto next_loop;
	    end_loop:;
	      princ(string_constant_15,_);
	  }
	  else
	      prin1(thing,_);
	POP_SPECIAL();
    }
    POP_AREA(0);
    return VALUES_1(thing);
}

Object G2int_system_variable_descriptions_prop = UNBOUND;

static Object Qg2int_system_variable_descriptions;  /* system-variable-descriptions */

/* RECORD-SYSTEM-VARIABLE */
Object g2int_record_system_variable(system_variable_name,module_name,
	    initialization,re_evaluate_initialization_on_rebinding_qm,
	    also_bind_globally_qm,value_reclaimer_qm,kb_specific_qm)
    Object system_variable_name, module_name, initialization;
    Object re_evaluate_initialization_on_rebinding_qm, also_bind_globally_qm;
    Object value_reclaimer_qm, kb_specific_qm;
{
    Object system_variable_descriptions, system_variable_description_qm;
    Object cdr_new_value;

    x_note_fn_call(13,19);
    system_variable_descriptions = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qg2int_system_variable_descriptions);
    system_variable_description_qm = assoc_eql(system_variable_name,
	    system_variable_descriptions);
    if (system_variable_description_qm) {
	cdr_new_value = LIST_4(initialization,
		re_evaluate_initialization_on_rebinding_qm,kb_specific_qm,
		value_reclaimer_qm);
	M_CDR(system_variable_description_qm) = cdr_new_value;
    }
    else
	g2int_mutate_global_property(module_name,
		nconc2(system_variable_descriptions,
		LIST_1(LIST_5(system_variable_name,initialization,
		re_evaluate_initialization_on_rebinding_qm,kb_specific_qm,
		value_reclaimer_qm))),Qg2int_system_variable_descriptions);
    if (also_bind_globally_qm)
	return g2int_set_system_variable_as_appropriate(system_variable_name,
		initialization);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_lisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

/* COMPUTE-SYSTEM-VARIABLES */
Object g2int_compute_system_variables(system_name)
    Object system_name;
{
    Object module_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, system_variable_name, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4, ab_loop_desetq_;

    x_note_fn_call(13,20);
    module_name = Nil;
    ab_loop_list_ = get(system_name,Qg2int_lisp_modules_to_be_loaded,_);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    system_variable_name = Nil;
    ab_loop_list__1 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qg2int_system_variable_descriptions);
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    system_variable_name = CAR(ab_loop_desetq_);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__4 = LIST_1(system_variable_name);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop_1;
  end_loop_1:
    goto end;
    ab_loopvar__2 = Qnil;
  end:;
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

Object G2int_process_initializations_alist = UNBOUND;

Object G2int_no_saved_initial_value = UNBOUND;

/* INITIALIZE-SYSTEM-VARIABLES */
Object g2int_initialize_system_variables(system_name,process_handle)
    Object system_name, process_handle;
{
    Object process_initializations_entry, push_arg, temp, module_name;
    Object ab_loop_list_, system_variable_name, initialization;
    Object re_evaluate_initialization_on_rebinding_qm, kb_specific_qm;
    Object ab_loop_list__1, saved_initial_value_if_any, ab_loop_desetq_;
    Object temp_1, new_value;

    x_note_fn_call(13,21);
    process_initializations_entry = g2int_assq_function(process_handle,
	    G2int_process_initializations_alist);
    if (process_initializations_entry);
    else {
	push_arg = LIST_1(process_handle);
	temp = CONS(push_arg,G2int_process_initializations_alist);
	G2int_process_initializations_alist = temp;
	process_initializations_entry = 
		FIRST(G2int_process_initializations_alist);
    }
    module_name = Nil;
    ab_loop_list_ = get(system_name,Qg2int_lisp_modules_to_be_loaded,_);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    system_variable_name = Nil;
    initialization = Nil;
    re_evaluate_initialization_on_rebinding_qm = Nil;
    kb_specific_qm = Nil;
    ab_loop_list__1 = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qg2int_system_variable_descriptions);
    saved_initial_value_if_any = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    system_variable_name = CAR(ab_loop_desetq_);
    temp_1 = CDR(ab_loop_desetq_);
    initialization = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    re_evaluate_initialization_on_rebinding_qm = CAR(temp_1);
    temp_1 = CDR(ab_loop_desetq_);
    temp_1 = CDR(temp_1);
    temp_1 = CDR(temp_1);
    kb_specific_qm = CAR(temp_1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    saved_initial_value_if_any = 
	    g2int_getfq_function(CDR(process_initializations_entry),
	    system_variable_name,G2int_no_saved_initial_value);
    if (EQ(saved_initial_value_if_any,G2int_no_saved_initial_value) || 
	    re_evaluate_initialization_on_rebinding_qm) {
	new_value = 
		g2int_set_system_variable_as_appropriate(system_variable_name,
		 !TRUEP(kb_specific_qm) ? initialization : Nil);
	temp = set_getf(CDR(process_initializations_entry),
		system_variable_name,new_value);
	M_CDR(process_initializations_entry) = temp;
    }
    else if ( !EQ(saved_initial_value_if_any,G2int_no_saved_initial_value))
	set(system_variable_name,saved_initial_value_if_any);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Kno_initial_value;   /* :no-initial-value */

static Object Qg2int_no_initial_value;  /* no-initial-value */

static Object Ksystem_frame;       /* :system-frame */

static Object Ksymbol_value;       /* :symbol-value */

static Object Kfuncall;            /* :funcall */

/* SET-SYSTEM-VARIABLE-AS-APPROPRIATE */
Object g2int_set_system_variable_as_appropriate(system_variable_name,
	    initialization)
    Object system_variable_name, initialization;
{
    Object temp;

    x_note_fn_call(13,22);
    if (EQ(initialization,Kno_initial_value) || CONSP(initialization) && 
	    EQ(M_CAR(initialization),Qg2int_no_initial_value))
	return set(system_variable_name,G2int_no_saved_initial_value);
    else if (EQ(initialization,Ksystem_frame))
	return VALUES_1(Nil);
    else {
	if (ATOM(initialization))
	    temp = initialization;
	else {
	    temp = FIRST(initialization);
	    if (EQ(temp,Qquote))
		temp = SECOND(initialization);
	    else if (EQ(temp,Ksymbol_value))
		temp = SYMBOL_VALUE(SECOND(initialization));
	    else if (EQ(temp,Kfuncall)) {
		temp = SECOND(initialization);
		temp = APPLY_1(temp,CDDR(initialization));
	    }
	    else
		temp = initialization;
	}
	return set(system_variable_name,temp);
    }
}

Object G2int_named_dynamic_extent_description_prop = UNBOUND;

/* MAKE-NAMED-DYNAMIC-EXTENT-DESCRIPTION */
Object g2int_make_named_dynamic_extent_description(name,module,
	    variables_of_dynamic_extent,
	    dynamic_superiors_list_of_dynamic_extent,
	    shadowing_list_of_dynamic_extent,
	    included_list_of_dynamic_extent,named_dynamic_extent_plist)
    Object name, module, variables_of_dynamic_extent;
    Object dynamic_superiors_list_of_dynamic_extent;
    Object shadowing_list_of_dynamic_extent, included_list_of_dynamic_extent;
    Object named_dynamic_extent_plist;
{
    x_note_fn_call(13,23);
    return list_star(7,name,module,variables_of_dynamic_extent,
	    dynamic_superiors_list_of_dynamic_extent,
	    shadowing_list_of_dynamic_extent,
	    included_list_of_dynamic_extent,named_dynamic_extent_plist);
}

static Object Qg2int_gsi_api_symbol;  /* gsi-api-symbol */

/* DECLARE-GSI-API-SYMBOL-1 */
Object g2int_declare_gsi_api_symbol_1(name)
    Object name;
{
    x_note_fn_call(13,24);
    return set_get(name,Qg2int_gsi_api_symbol,T);
}

/* G2INT-X-ERROR */
int g2int_g2int_x_error(error_code)
    int error_code;
{
    int result_1;

    x_note_fn_call(13,25);
    result_1 = error_code;
    return result_1;
}

/* G2INT-NETWORK-EVENT-HANDLER */
SI_Long g2int_network_event_handler(event_code,event_socket_handle,
	    event_status_code)
    SI_Long event_code, event_socket_handle, event_status_code;
{
    SI_Long result_1;

    x_note_fn_call(13,26);
    result_1 = IFIX(g2int_handle_event_internal(FIX(event_code),
	    FIX(event_socket_handle),FIX(event_status_code)));
    return result_1;
}

/* G2INT-OPEN-FD-CALLBACK */
SI_Long g2int_open_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,27);
    result_1 = IFIX(g2int_call_gsi_open_fd_callback(FIX(fd)));
    return result_1;
}

/* G2INT-CLOSE-FD-CALLBACK */
SI_Long g2int_close_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,28);
    result_1 = IFIX(g2int_call_gsi_close_fd_callback(FIX(fd)));
    return result_1;
}

/* G2INT-WRITING-FD-CALLBACK */
SI_Long g2int_writing_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,29);
    result_1 = IFIX(g2int_call_gsi_writing_fd_callback(FIX(fd)));
    return result_1;
}

/* G2INT-NOT-WRITING-FD-CALLBACK */
SI_Long g2int_not_writing_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,30);
    result_1 = IFIX(g2int_call_gsi_not_writing_fd_callback(FIX(fd)));
    return result_1;
}

/* MAKE-SYMBOL-NAME-FROM-C-NAME */
Object g2int_make_symbol_name_from_c_name(length_1,buffer)
    Object length_1, buffer;
{
    Object string_1, buffer_char, char_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(13,31);
    string_1 = g2int_obtain_simple_gensym_string(length_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    buffer_char = Nil;
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    buffer_char = CHR(ISCHAR(buffer,i));
    char_1 = CHAR_EQ(buffer_char,CHR('_')) ? CHR('-') : 
	    CHAR_UPCASE(buffer_char);
    SET_ISCHAR(string_1,i,ICHAR_CODE(char_1));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = string_1;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* GET-NAME-FOR-FUNCTION */
Object g2int_get_name_for_function(fn)
    Object fn;
{
    Object temp_1;
    char *temp;

    x_note_fn_call(13,32);
    if (SYMBOLP(fn))
	return g2int_gensym_symbol_name(fn);
    temp = ISTRING(G2int_gensym_environment_variable_buffer);
    temp_1 = FIX(g2ext_get_name_for_function(temp,
	    inline_get_function_address(fn)));
    return g2int_make_symbol_name_from_c_name(temp_1,
	    G2int_gensym_environment_variable_buffer);
}

/* C-GET-TRACE-FUNCTION-NAME */
Object g2int_c_get_trace_function_name(buffer)
    Object buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,33);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_trace_function_name(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object G2int_trace_function_p_prop = UNBOUND;

Object G2int_running_trace_function_p = UNBOUND;

static Object Qg2int_trace_function_p;  /* trace-function-p */

/* G2INT-RUN-TRACE-FUNCTION */
SI_Long g2int_run_trace_function()
{
    Object length_1, temp, function_name, running_trace_function_p;
    SI_Long result_1;
    Declare_special(1);

    x_note_fn_call(13,34);
    length_1 = 
	    g2int_c_get_trace_function_name(G2int_gensym_environment_variable_buffer);
    temp = FIX((SI_Long)0L);
    function_name = NUM_LE(temp,length_1) ? g2int_intern_gensym_string(1,
	    g2int_make_symbol_name_from_c_name(length_1,
	    G2int_gensym_environment_variable_buffer)) : Nil;
    if (g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(function_name),
	    Qg2int_trace_function_p) && fboundp(function_name)) {
	running_trace_function_p = T;
	PUSH_SPECIAL(G2int_running_trace_function_p,running_trace_function_p,
		0);
	  FUNCALL_0(function_name);
	POP_SPECIAL();
	result_1 = (SI_Long)1L;
    }
    else
	result_1 = (SI_Long)0L;
    return result_1;
}

Object G2int_unix_command_callback_function = UNBOUND;

/* G2INT-UNIX-COMMAND-CALLBACK */
SI_Long g2int_unix_command_callback()
{
    SI_Long result_1;

    x_note_fn_call(13,35);
    result_1 = G2int_unix_command_callback_function ? 
	    IFIX(FUNCALL_0(G2int_unix_command_callback_function)) : 
	    (SI_Long)0L;
    return result_1;
}

Object G2int_cached_fixnum_timeqm = UNBOUND;

/* C-NATIVE-CLOCK-TICKS-OR-CACHE */
Object g2int_c_native_clock_ticks_or_cache(as_accurately_as_possible_qm,
	    disable_caching_fixnum_time_qm)
    Object as_accurately_as_possible_qm, disable_caching_fixnum_time_qm;
{
    Object temp;

    x_note_fn_call(13,36);
    temp = FIX(g2ext_g2_clock_ticks(IFIX(Most_positive_fixnum)));
    return VALUES_1(temp);
}

/* CLEAR-FIXNUM-TIME-ALARM */
Object g2int_clear_fixnum_time_alarm()
{
    x_note_fn_call(13,37);
    if (G2int_cached_fixnum_timeqm) {
	if (g2ext_cancel_future_alarm_signal() != (SI_Long)0L)
	    format((SI_Long)2L,T,
		    "~%Failure reported when clearing sigalarm, continuing.");
	G2int_cached_fixnum_timeqm = Nil;
    }
    return VALUES_1(Nil);
}

Object G2int_check_time_on_next_uuid = UNBOUND;

Object G2int_time_to_check_network_events = UNBOUND;

/* G2INT-SERVICE-SIGALRM-SIGNAL */
Object g2int_service_sigalrm_signal()
{
    x_note_fn_call(13,38);
    G2int_cached_fixnum_timeqm = Nil;
    G2int_check_time_on_next_uuid = T;
    G2int_time_to_check_network_events = T;
    return VALUES_1(Nil);
}

/* GET-FIXNUM-TIME-FUNCTION */
Object g2int_get_fixnum_time_function()
{
    Object temp;

    x_note_fn_call(13,39);
    temp = g2int_c_native_clock_ticks_or_cache(Nil,Nil);
    return VALUES_1(temp);
}

Object G2int_fixnum_time_units_per_second = UNBOUND;

Object G2int_fixnum_time_bignum_worries_limit = UNBOUND;

/* FIXNUM-TIME-INTERVAL-PROTECTED */
Object g2int_fixnum_time_interval_protected(milliseconds)
    Object milliseconds;
{
    SI_Long result_fixnum, temp;

    x_note_fn_call(13,40);
    format((SI_Long)2L,T,"Memory inconsistency (type 3, case 2) detected.");
    result_fixnum = (SI_Long)0L;
    temp = (IFIX(FIXNUM_TIMES(milliseconds,
	    G2int_fixnum_time_units_per_second)) + ((SI_Long)1000L - 
	    (SI_Long)1L)) / (SI_Long)1000L;
    result_fixnum = temp;
    return VALUES_1(FIX(result_fixnum));
}

/* FIXNUM-TIME-INTERVAL */
Object g2int_fixnum_time_interval(milliseconds)
    Object milliseconds;
{
    Object temp;
    SI_Long local_time_units_per_second;

    x_note_fn_call(13,41);
    local_time_units_per_second = IFIX(G2int_fixnum_time_units_per_second);
    if (local_time_units_per_second == (SI_Long)1000L)
	temp = milliseconds;
    else if (FIXNUM_LT(milliseconds,G2int_fixnum_time_bignum_worries_limit))
	temp = FIX((IFIX(milliseconds) * local_time_units_per_second + 
		((SI_Long)1000L - (SI_Long)1L)) / (SI_Long)1000L);
    else
	temp = g2int_fixnum_time_interval_protected(milliseconds);
    return VALUES_1(temp);
}

Object G2int_fixnum_time_interval_for_one_second = UNBOUND;

/* FIXNUM-TIME-DIFFERENCE-IN-SECONDS */
Object g2int_fixnum_time_difference_in_seconds(later_fixnum_time,
	    earlier_fixnum_time)
    Object later_fixnum_time, earlier_fixnum_time;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(13,42);
    if (FIXNUM_GE(later_fixnum_time,earlier_fixnum_time))
	gensymed_symbol = IFIX(FIXNUM_MINUS(later_fixnum_time,
		earlier_fixnum_time));
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(later_fixnum_time,
		earlier_fixnum_time));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
    }
    gensymed_symbol_1 = IFIX(G2int_fixnum_time_units_per_second);
    return VALUES_1(FIX(gensymed_symbol / gensymed_symbol_1));
}

/* C-SET-FILE-OPERATION-TIMEOUT */
Object g2int_c_set_file_operation_timeout(timeout)
    Object timeout;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,43);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(timeout);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = timeout;
    temp = FIX(g2ext_set_file_operation_retry_timeout(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-UNIX_COMMAND_WITH_STRING_OUTPUT */
Object g2int_c_unix_command_with_string_output(command,buff,max_bytes)
    Object command, buff, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,44);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_unix_cmd_with_string_output_mx(temp_1,ISTRING(temp),
	    IFIX(max_bytes)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-UNIX_COMMAND_WITH_STRING_OUTPUT_AND_TIMEOUT */
Object g2int_c_unix_command_with_string_output_and_timeout(command,dir,
	    buff,timeout_in_ms,max_bytes)
    Object command, dir, buff, timeout_in_ms, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,45);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = g2int_copy_foreign_string_arg_if_appropriate(dir);
    gensymed_symbol_2 = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = dir;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_unix_cmd_with_string_output_and_timeout_mx(temp_1,
	    temp_2,ISTRING(temp),IFIX(timeout_in_ms),IFIX(max_bytes)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	g2int_reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-RUN_PROGRAM_WITH_STRING_OUTPUT_AND_TIMEOUT */
Object g2int_c_run_program_with_string_output_and_timeout(command,dir,buff,
	    timeout_in_ms,max_bytes)
    Object command, dir, buff, timeout_in_ms, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,46);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = g2int_copy_foreign_string_arg_if_appropriate(dir);
    gensymed_symbol_2 = g2int_copy_foreign_string_arg_if_appropriate(buff);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = dir;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = buff;
    temp = FIX(g2ext_run_program_with_string_output_and_timeout_mx(temp_1,
	    temp_2,ISTRING(temp),IFIX(timeout_in_ms),IFIX(max_bytes)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	g2int_reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-DIRECTORY_CONTAINS_DIRECTORY */
Object g2int_c_directory_contains_directory(containing_directory,
	    contained_directory)
    Object containing_directory, contained_directory;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,47);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(containing_directory);
    gensymed_symbol_1 = 
	    g2int_copy_foreign_string_arg_if_appropriate(contained_directory);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = containing_directory;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = contained_directory;
    temp = FIX(g2ext_directory_contains_directory(temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-WRITE-STRING-TO-CONSOLE */
Object g2int_c_write_string_to_console(string_1,write_console_p)
    Object string_1, write_console_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,48);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = FIX(g2ext_write_string_to_console_1(ISTRING(temp),
	    IFIX(write_console_p)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object G2int_known_process_idsqm = UNBOUND;

Object G2int_all_foreign_function_imagesqm = UNBOUND;

Object G2int_all_external_foreign_function_imagesqm = UNBOUND;

/* KILL-FOREIGN-IMAGES */
Object g2int_kill_foreign_images(list_of_foreign_images_qm)
    Object list_of_foreign_images_qm;
{
    Object copy_of_list_of_foreign_images, foreign_image_info, ab_loop_list_;

    x_note_fn_call(13,49);
    if (list_of_foreign_images_qm) {
	copy_of_list_of_foreign_images = 
		g2int_copy_list_using_icp_conses_function(list_of_foreign_images_qm);
	foreign_image_info = Nil;
	ab_loop_list_ = copy_of_list_of_foreign_images;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	foreign_image_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_kill_foreign_image_unconditionally(foreign_image_info);
	goto next_loop;
      end_loop:
	g2int_reclaim_icp_list_function(copy_of_list_of_foreign_images);
    }
    return VALUES_1(Nil);
}

/* SHUTDOWN-SYSTEM-FOR-EXIT */
Object g2int_shutdown_system_for_exit()
{
    Object process_id, ab_loop_list_;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(13,50);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	g2int_kill_foreign_images(G2int_all_foreign_function_imagesqm);
	g2int_kill_foreign_images(G2int_all_external_foreign_function_imagesqm);
	if (G2int_known_process_idsqm) {
	    process_id = Nil;
	    ab_loop_list_ = G2int_known_process_idsqm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    process_id = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    g2int_kill_possibly_leftover_spawned_process(process_id);
	    goto next_loop;
	  end_loop:
	    g2int_reclaim_sysproc_list_function(G2int_known_process_idsqm);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    g2int_shift_rule_ordering_heuristics();
    g2int_close_and_disconnect_all_sockets();
    return VALUES_1(Nil);
}

Object G2int_isqrt_of_most_positive_fixnum = UNBOUND;

Object G2int_minus_of_isqrt_of_most_positive_fixnum = UNBOUND;

/* SCALEF-FUNCTION */
Object g2int_scalef_function(scale,value)
    Object scale, value;
{
    x_note_fn_call(13,51);
    return VALUES_1(Nil);
}

/* INVERSE-SCALEF-FUNCTION */
Object g2int_inverse_scalef_function(scale,value)
    Object scale, value;
{
    x_note_fn_call(13,52);
    return VALUES_1(Nil);
}

/* FLOAT-DELTA-X-IN-WINDOW */
Object g2int_float_delta_x_in_window(delta_x_in_workspace,x_scale)
    Object delta_x_in_workspace, x_scale;
{
    x_note_fn_call(13,53);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(x_scale) * 
	    (double)IFIX(delta_x_in_workspace) / (double)(SI_Long)4096L));
}

/* FLOAT-DELTA-Y-IN-WINDOW */
Object g2int_float_delta_y_in_window(delta_y_in_workspace,y_scale)
    Object delta_y_in_workspace, y_scale;
{
    x_note_fn_call(13,54);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(y_scale) * 
	    (double)IFIX(delta_y_in_workspace) / (double)(SI_Long)4096L));
}

Object G2int_maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation = UNBOUND;

/* EXIT-LISP-PROCESS */
Object g2int_exit_lisp_process varargs_1(int, n)
{
    Object status_qm, status;
    Declare_varargs_nonrelocating;

    x_note_fn_call(13,55);
    INIT_ARGS_nonrelocating();
    status_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    status = status_qm;
    if (status);
    else
	status = FIX((SI_Long)0L);
    g2ext_exit_from_lisp(IFIX(status));
    return VALUES_1(status_qm);
}

Object G2int_inner_abort_level_tag = UNBOUND;

Object G2int_abort_level_0_tag = UNBOUND;

static Object list_constant_1;     /* # */

static Object Qg2int_abort_level_0;  /* abort-level-0 */

/* ABORT */
Object g2int_abort varargs_1(int, n)
{
    Object abort_level_qm, tag;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(13,56);
    INIT_ARGS_nonrelocating();
    abort_level_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tag = abort_level_qm ? nth(abort_level_qm,list_constant_1) : 
	    G2int_inner_abort_level_tag;
    if (EQ(tag,Qg2int_abort_level_0) && G2int_abort_level_0_tag)
	tag = G2int_abort_level_0_tag;
    result = VALUES_1(Nil);
    THROW(tag,result);
}

/* C-SPAWN_COMMAND_LINE_PROCESS */
Object g2int_c_spawn_command_line_process(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,57);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = 
	    DOUBLE_TO_DOUBLE_FLOAT(g2ext_spawn_command_line_process(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-SPAWN_EXECUTABLE_PROCESS */
Object g2int_c_spawn_executable_process(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,58);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = DOUBLE_TO_DOUBLE_FLOAT(g2ext_spawn_command_directly(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-LOAD_LIBRARY */
Object g2int_c_load_library(name,init_function_name,init_function_arg)
    Object name, init_function_name, init_function_arg;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,59);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = 
	    g2int_copy_foreign_string_arg_if_appropriate(init_function_name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = init_function_name;
    temp = FIX(g2ext_load_library(temp_1,ISTRING(temp),init_function_arg));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-PRODUCE_SHARED_OBJECT */
Object g2int_c_produce_shared_object(kb_filename,nfiles,obj_suffix,dll_name)
    Object kb_filename, nfiles, obj_suffix, dll_name;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,60);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(kb_filename);
    gensymed_symbol_1 = 
	    g2int_copy_foreign_string_arg_if_appropriate(obj_suffix);
    gensymed_symbol_2 = g2int_copy_foreign_string_arg_if_appropriate(dll_name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = kb_filename;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = obj_suffix;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = dll_name;
    temp = FIX(g2ext_produce_shared_object(temp_1,IFIX(nfiles),temp_2,
	    ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	g2int_reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	g2int_reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-SET-INCLUDE-DIRECTORY */
Object g2int_c_set_include_directory(directory_1)
    Object directory_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,61);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(directory_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = directory_1;
    temp = FIX(g2ext_set_include_directory(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* LOAD-LIBRARY */
Object g2int_load_library(name,init_function_name,init_function_arg)
    Object name, init_function_name, init_function_arg;
{
    Object temp;

    x_note_fn_call(13,62);
    temp = T ? ((SI_Long)0L == IFIX(g2int_c_load_library(name,
	    init_function_name,init_function_arg)) ? T : Nil) : Nil;
    return VALUES_1(temp);
}

/* C-SUBSTATUS_RUN_COMMAND_LINE */
Object g2int_c_substatus_run_command_line(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,63);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = FIX(g2ext_substatus_run_command_line(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-UUID-CREATE */
Object g2int_c_uuid_create(buffer)
    Object buffer;
{
    Object temp;

    x_note_fn_call(13,64);
    temp = FIX(g2ext_uuid_create(UBYTE_16_SARRAY_TO_USHORT_PTR(buffer)));
    return VALUES_1(temp);
}

Object G2int_rpc_s_uuid_local_only_message = UNBOUND;

Object G2int_rpc_s_uuid_no_address_message = UNBOUND;

/* NO-OPERATION-FUNCTION */
Object g2int_no_operation_function()
{
    x_note_fn_call(13,65);
    return VALUES_1(Nil);
}

/* C-G2_PROBE_FILE */
Object g2int_c_g2_probe_file(namestring_1)
    Object namestring_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,66);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(namestring_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = namestring_1;
    temp = LONG_TO_FIXNUM(g2ext_g2_probe_file(ISTRING(temp)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-G2_PROBE_FILE_WIDE */
Object g2int_c_g2_probe_file_wide(namestring_1)
    Object namestring_1;
{
    Object temp;

    x_note_fn_call(13,67);
    temp = 
	    LONG_TO_FIXNUM(g2ext_g2_probe_file_s16(UBYTE_16_SARRAY_TO_USHORT_PTR(namestring_1)));
    return VALUES_1(temp);
}

/* C-G2_STREAM_OPEN */
Object g2int_c_g2_stream_open(namestring_1,open_mode)
    Object namestring_1, open_mode;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,68);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(namestring_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = namestring_1;
    temp = LONG_TO_FIXNUM(g2ext_g2_stream_open(ISTRING(temp),IFIX(open_mode)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-G2_STREAM_OPEN_WIDE */
Object g2int_c_g2_stream_open_wide(namestring_1,open_mode)
    Object namestring_1, open_mode;
{
    Object temp;

    x_note_fn_call(13,69);
    temp = 
	    LONG_TO_FIXNUM(g2ext_g2_stream_open_s16(UBYTE_16_SARRAY_TO_USHORT_PTR(namestring_1),
	    IFIX(open_mode)));
    return VALUES_1(temp);
}

/* C-G2_STREAM_WRITE_STRING */
Object g2int_c_g2_stream_write_string(output_string,g2_output_stream,
	    write_newline_p)
    Object output_string, g2_output_stream, write_newline_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,70);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(output_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = output_string;
    temp = FIX(g2ext_str_write_string(ISTRING(temp),IFIX(g2_output_stream),
	    IFIX(write_newline_p)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-RUN-TRACE */
Object g2int_c_run_trace(command,length_1,wide_p)
    Object command, length_1, wide_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,71);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(command);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command;
    temp = FIX(g2ext_run_trace(ISTRING(temp),IFIX(length_1),IFIX(wide_p)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* RUN-TRACE */
Object g2int_run_trace(string_1)
    Object string_1;
{
    Object temp, temp_1;

    x_note_fn_call(13,72);
    temp = FIX((SI_Long)0L);
    if (g2int_text_string_p(string_1))
	temp_1 = 
		FIX(g2ext_run_trace(UBYTE_16_SARRAY_TO_USHORT_PTR(string_1),
		IFIX(g2int_lengthw(string_1)),(SI_Long)1L));
    else if (STRINGP(string_1))
	temp_1 = g2int_c_run_trace(string_1,length(string_1),FIX((SI_Long)0L));
    else
	temp_1 = FIX((SI_Long)0L);
    temp = NUM_NE(temp,temp_1) ? T : Nil;
    return VALUES_1(temp);
}

/* VISIBLE-WINDOW-IS-PRESENT-P */
Object g2int_visible_window_is_present_p()
{
    Object temp;

    x_note_fn_call(13,73);
    temp = (SI_Long)0L != g2ext_visible_window_is_present() ? T : Nil;
    return VALUES_1(temp);
}

/* WINDOW-IS-PRESENT-P */
Object g2int_window_is_present_p()
{
    Object temp;

    x_note_fn_call(13,74);
    temp = (SI_Long)0L != g2ext_window_is_present() ? T : Nil;
    return VALUES_1(temp);
}

void primitives_INIT()
{
    Object temp;
    Object Qg2int_g2_stream_foreign_file_op_failure, AB_package;
    Object Qg2int_g2_stream_foreign_file_op_success;
    Object Qg2int_g2_stream_open_mode_for_binary_update;
    Object Qg2int_g2_stream_open_mode_for_binary_appending;
    Object Qg2int_g2_stream_open_mode_for_binary_output;
    Object Qg2int_g2_stream_open_mode_for_binary_input;
    Object Qg2int_g2_stream_open_mode_for_update;
    Object Qg2int_g2_stream_open_mode_for_appending;
    Object Qg2int_g2_stream_open_mode_for_output;
    Object Qg2int_g2_stream_open_mode_for_input;
    Object Qg2int_wide_character_code_offset, string_constant_19;
    Object Qg2int_rpc_s_uuid_no_address_message, string_constant_18;
    Object Qg2int_rpc_s_uuid_local_only_message, Qg2int_rpc_s_uuid_no_address;
    Object Qg2int_rpc_s_uuid_local_only, Qg2int_abort_level_4;
    Object Qg2int_abort_level_3, Qg2int_abort_level_2, Qg2int_abort_level_1;
    Object Qg2int_most_positive_workspace_coordinate;
    Object Qg2int_most_negative_workspace_coordinate;
    Object Qg2int_scaling_factor_for_text_widths;
    Object Qg2int_number_of_fraction_bits_for_text_widths;
    Object Qg2int_greatest_magnification, Qg2int_least_magnification;
    Object Qg2int_minus_of_isqrt_of_most_positive_fixnum;
    Object Qg2int_isqrt_of_most_positive_fixnum, Qg2int_primitives;
    Object Qg2int_all_external_foreign_function_imagesqm;
    Object Qg2int_all_foreign_function_imagesqm, Qg2int_known_process_idsqm;
    Object Qg2int_run_trace_function, Qg2int_named_dynamic_extent_description;
    Object Qg2int_no_saved_initial_value, list_constant_2, string_constant_17;
    Object string_constant_16, Qg2int_pm_print_structure;
    Object Qg2int_pm_composite_type_of, Qg2int_pm_type_of, Qg2int_pm_nthcdr;
    Object Qg2int_pm_elt;

    x_note_fn_call(13,75);
    SET_PACKAGE("AB");
    if (G2int_one_integer == UNBOUND)
	G2int_one_integer = FIX((SI_Long)1L);
    if (G2int_minus_one_integer == UNBOUND)
	G2int_minus_one_integer = FIX((SI_Long)-1L);
    if (G2int_global_property_conses == UNBOUND)
	G2int_global_property_conses = Nil;
    if (G2int_object_pool_meters == UNBOUND)
	G2int_object_pool_meters = Nil;
    G2int_names_of_interesting_system_object_pools = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_pm_elt = STATIC_SYMBOL("PM-ELT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_pm_elt,STATIC_FUNCTION(g2int_pm_elt,NIL,
	    FALSE,2,2));
    Qg2int_pm_nthcdr = STATIC_SYMBOL("PM-NTHCDR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_pm_nthcdr,STATIC_FUNCTION(g2int_pm_nthcdr,
	    NIL,FALSE,2,2));
    Qg2int_pm_type_of = STATIC_SYMBOL("PM-TYPE-OF",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_pm_type_of,STATIC_FUNCTION(g2int_pm_type_of,
	    NIL,FALSE,1,1));
    Qg2int_composite_object = STATIC_SYMBOL("COMPOSITE-OBJECT",AB_package);
    Qg2int_pm_composite_type_of = STATIC_SYMBOL("PM-COMPOSITE-TYPE-OF",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_pm_composite_type_of,
	    STATIC_FUNCTION(g2int_pm_composite_type_of,NIL,FALSE,1,1));
    if (G2int_single_element_string == UNBOUND)
	G2int_single_element_string = make_string(1,FIX((SI_Long)1L));
    string_constant = STATIC_STRING("#w\"");
    string_constant_1 = STATIC_STRING(" ");
    string_constant_2 = STATIC_STRING("\"");
    Qg2int_pm_print_structure = STATIC_SYMBOL("PM-PRINT-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_pm_print_structure,
	    STATIC_FUNCTION(g2int_pm_print_structure,NIL,FALSE,2,2));
    string_constant_3 = STATIC_STRING("-G2-STRUCT");
    Qg2int_available_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2int_managed_float = STATIC_SYMBOL("MANAGED-FLOAT",AB_package);
    string_constant_16 = STATIC_STRING("slotnames.70");
    string_constant_17 = STATIC_STRING("/home/ab/g2/slotnames.70");
    list_constant_2 = STATIC_LIST((SI_Long)2L,string_constant_16,
	    string_constant_17);
    G2int_pm_file_names = list_constant_2;
    if (G2int_pm_slot_names == UNBOUND)
	G2int_pm_slot_names = Nil;
    if (G2int_pm_max_length == UNBOUND)
	G2int_pm_max_length = FIX((SI_Long)100L);
    string_constant_4 = STATIC_STRING(" is a ");
    string_constant_5 = STATIC_STRING(" aka ");
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    string_constant_6 = STATIC_STRING("  ");
    string_constant_7 = STATIC_STRING("CDR");
    if (G2int_pm_temp_string == UNBOUND)
	G2int_pm_temp_string = make_string(1,FIX((SI_Long)10L));
    string_constant_8 = STATIC_STRING("0123456789abcdef");
    string_constant_9 = STATIC_STRING("~A");
    string_constant_10 = STATIC_STRING("#<Managed-Float ");
    string_constant_11 = STATIC_STRING(">");
    string_constant_12 = STATIC_STRING("#<");
    string_constant_13 = STATIC_STRING("(");
    string_constant_14 = STATIC_STRING(" . ");
    string_constant_15 = STATIC_STRING(")");
    Qg2int_system_variable_descriptions = 
	    STATIC_SYMBOL("SYSTEM-VARIABLE-DESCRIPTIONS",AB_package);
    G2int_system_variable_descriptions_prop = 
	    Qg2int_system_variable_descriptions;
    Qg2int_lisp_modules_to_be_loaded = 
	    STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",AB_package);
    if (G2int_process_initializations_alist == UNBOUND)
	G2int_process_initializations_alist = Nil;
    Qg2int_no_saved_initial_value = STATIC_SYMBOL("NO-SAVED-INITIAL-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_no_saved_initial_value,
	    G2int_no_saved_initial_value);
    if (G2int_no_saved_initial_value == UNBOUND)
	G2int_no_saved_initial_value = LIST_1(Qg2int_no_saved_initial_value);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    Qg2int_no_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    Ksymbol_value = STATIC_SYMBOL("SYMBOL-VALUE",Pkeyword);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_named_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    G2int_named_dynamic_extent_description_prop = 
	    Qg2int_named_dynamic_extent_description;
    Qg2int_gsi_api_symbol = STATIC_SYMBOL("GSI-API-SYMBOL",AB_package);
    Qg2int_trace_function_p = STATIC_SYMBOL("TRACE-FUNCTION-P",AB_package);
    G2int_trace_function_p_prop = Qg2int_trace_function_p;
    if (G2int_running_trace_function_p == UNBOUND)
	G2int_running_trace_function_p = Nil;
    Qg2int_run_trace_function = STATIC_SYMBOL("G2INT-RUN-TRACE-FUNCTION",
	    AB_package);
    set_get(Qg2int_run_trace_function,Qg2int_gsi_api_symbol,T);
    if (G2int_unix_command_callback_function == UNBOUND)
	G2int_unix_command_callback_function = Nil;
    if (G2int_cached_fixnum_timeqm == UNBOUND)
	G2int_cached_fixnum_timeqm = Nil;
    if (G2int_check_time_on_next_uuid == UNBOUND)
	G2int_check_time_on_next_uuid = Nil;
    if (G2int_time_to_check_network_events == UNBOUND)
	G2int_time_to_check_network_events = Nil;
    G2int_fixnum_time_units_per_second = 
	    FIX(g2ext_g2_clock_ticks_per_second());
    temp = FIX(IFIX(Most_positive_fixnum) / 
	    IFIX(G2int_fixnum_time_units_per_second));
    G2int_fixnum_time_bignum_worries_limit = temp;
    if (G2int_fixnum_time_interval_for_one_second == UNBOUND)
	G2int_fixnum_time_interval_for_one_second = 
		g2int_fixnum_time_interval(FIX((SI_Long)1000L));
    Qg2int_known_process_idsqm = STATIC_SYMBOL("KNOWN-PROCESS-IDS\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_known_process_idsqm,
	    G2int_known_process_idsqm);
    Qg2int_primitives = STATIC_SYMBOL("PRIMITIVES",AB_package);
    g2int_record_system_variable(Qg2int_known_process_idsqm,
	    Qg2int_primitives,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_all_foreign_function_imagesqm = 
	    STATIC_SYMBOL("ALL-FOREIGN-FUNCTION-IMAGES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_all_foreign_function_imagesqm,
	    G2int_all_foreign_function_imagesqm);
    g2int_record_system_variable(Qg2int_all_foreign_function_imagesqm,
	    Qg2int_primitives,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_all_external_foreign_function_imagesqm = 
	    STATIC_SYMBOL("ALL-EXTERNAL-FOREIGN-FUNCTION-IMAGES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_all_external_foreign_function_imagesqm,
	    G2int_all_external_foreign_function_imagesqm);
    g2int_record_system_variable(Qg2int_all_external_foreign_function_imagesqm,
	    Qg2int_primitives,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_isqrt_of_most_positive_fixnum = 
	    STATIC_SYMBOL("ISQRT-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_isqrt_of_most_positive_fixnum,
	    G2int_isqrt_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qg2int_isqrt_of_most_positive_fixnum,
	    isqrt(Most_positive_fixnum));
    Qg2int_minus_of_isqrt_of_most_positive_fixnum = 
	    STATIC_SYMBOL("MINUS-OF-ISQRT-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_minus_of_isqrt_of_most_positive_fixnum,
	    G2int_minus_of_isqrt_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qg2int_minus_of_isqrt_of_most_positive_fixnum,
	    FIXNUM_NEGATE(G2int_isqrt_of_most_positive_fixnum));
    Qg2int_least_magnification = STATIC_SYMBOL("LEAST-MAGNIFICATION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_least_magnification,FIX((SI_Long)16L));
    Qg2int_greatest_magnification = STATIC_SYMBOL("GREATEST-MAGNIFICATION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_greatest_magnification,FIX((SI_Long)4096L));
    Qg2int_number_of_fraction_bits_for_text_widths = 
	    STATIC_SYMBOL("NUMBER-OF-FRACTION-BITS-FOR-TEXT-WIDTHS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_number_of_fraction_bits_for_text_widths,
	    FIX((SI_Long)8L));
    Qg2int_scaling_factor_for_text_widths = 
	    STATIC_SYMBOL("SCALING-FACTOR-FOR-TEXT-WIDTHS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_scaling_factor_for_text_widths,FIX((SI_Long)256L));
    Qg2int_most_negative_workspace_coordinate = 
	    STATIC_SYMBOL("MOST-NEGATIVE-WORKSPACE-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_negative_workspace_coordinate,
	    FIX((SI_Long)-16777216L));
    Qg2int_most_positive_workspace_coordinate = 
	    STATIC_SYMBOL("MOST-POSITIVE-WORKSPACE-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_most_positive_workspace_coordinate,
	    FIX((SI_Long)16777215L));
    G2int_maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation 
	    = Nil;
    if (G2int_abort_level_0_tag == UNBOUND)
	G2int_abort_level_0_tag = Nil;
    Qg2int_abort_level_0 = STATIC_SYMBOL("ABORT-LEVEL-0",AB_package);
    Qg2int_abort_level_1 = STATIC_SYMBOL("ABORT-LEVEL-1",AB_package);
    Qg2int_abort_level_2 = STATIC_SYMBOL("ABORT-LEVEL-2",AB_package);
    Qg2int_abort_level_3 = STATIC_SYMBOL("ABORT-LEVEL-3",AB_package);
    Qg2int_abort_level_4 = STATIC_SYMBOL("ABORT-LEVEL-4",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qg2int_abort_level_0,
	    Qg2int_abort_level_1,Qg2int_abort_level_2,Qg2int_abort_level_3,
	    Qg2int_abort_level_4);
    Qg2int_rpc_s_uuid_local_only = STATIC_SYMBOL("RPC_S_UUID_LOCAL_ONLY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_s_uuid_local_only,FIX((SI_Long)1824L));
    Qg2int_rpc_s_uuid_no_address = STATIC_SYMBOL("RPC_S_UUID_NO_ADDRESS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_rpc_s_uuid_no_address,FIX((SI_Long)1739L));
    Qg2int_rpc_s_uuid_local_only_message = 
	    STATIC_SYMBOL("RPC_S_UUID_LOCAL_ONLY-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rpc_s_uuid_local_only_message,
	    G2int_rpc_s_uuid_local_only_message);
    string_constant_18 = 
	    STATIC_STRING("A UUID that is valid only on this computer has been allocated.");
    SET_SYMBOL_VALUE(Qg2int_rpc_s_uuid_local_only_message,string_constant_18);
    Qg2int_rpc_s_uuid_no_address_message = 
	    STATIC_SYMBOL("RPC_S_UUID_NO_ADDRESS-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rpc_s_uuid_no_address_message,
	    G2int_rpc_s_uuid_no_address_message);
    string_constant_19 = 
	    STATIC_STRING("No network address is available to use to construct a universal unique identifier (UUID).");
    SET_SYMBOL_VALUE(Qg2int_rpc_s_uuid_no_address_message,string_constant_19);
    Qg2int_wide_character_code_offset = 
	    STATIC_SYMBOL("WIDE-CHARACTER-CODE-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_wide_character_code_offset,FIX((SI_Long)1000000L));
    Qg2int_g2_stream_open_mode_for_input = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-INPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_input,FIX((SI_Long)0L));
    Qg2int_g2_stream_open_mode_for_output = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_output,FIX((SI_Long)1L));
    Qg2int_g2_stream_open_mode_for_appending = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-APPENDING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_appending,
	    FIX((SI_Long)2L));
    Qg2int_g2_stream_open_mode_for_update = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_update,FIX((SI_Long)3L));
    Qg2int_g2_stream_open_mode_for_binary_input = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-INPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_binary_input,
	    FIX((SI_Long)4L));
    Qg2int_g2_stream_open_mode_for_binary_output = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_binary_output,
	    FIX((SI_Long)5L));
    Qg2int_g2_stream_open_mode_for_binary_appending = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-APPENDING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_binary_appending,
	    FIX((SI_Long)6L));
    Qg2int_g2_stream_open_mode_for_binary_update = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_open_mode_for_binary_update,
	    FIX((SI_Long)7L));
    Qg2int_g2_stream_foreign_file_op_success = 
	    STATIC_SYMBOL("G2-STREAM-FOREIGN-FILE-OP-SUCCESS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_foreign_file_op_success,
	    FIX((SI_Long)0L));
    Qg2int_g2_stream_foreign_file_op_failure = 
	    STATIC_SYMBOL("G2-STREAM-FOREIGN-FILE-OP-FAILURE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_g2_stream_foreign_file_op_failure,
	    FIX((SI_Long)-1L));
}
