/* prmtvs.c
 * Input file:  primitives.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "prmtvs.h"


DEFINE_VARIABLE_WITH_SYMBOL(One_integer, Qone_integer);

DEFINE_VARIABLE_WITH_SYMBOL(Minus_one_integer, Qminus_one_integer);

/* MAKE-PERMANENT-INTEGER */
Object make_permanent_integer(integer)
    Object integer;
{
    Object one_less;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,0);
    if (FIXNUMP(integer))
	return VALUES_1(integer);
    else {
	one_less = add(integer,Minus_one_integer);
	if (PUSH_AREA(Dynamic_area,0))
	    result = add(one_less,One_integer);
	POP_AREA(0);
	return result;
    }
}

/* MAKE-PERMANENT-LIST */
Object make_permanent_list(length_1)
    Object length_1;
{
    Object new_list;
    XDeclare_area(1);

    x_note_fn_call(13,1);
    new_list = Nil;
    if (PUSH_AREA(Dynamic_area,0))
	new_list = make_list(1,length_1);
    POP_AREA(0);
    return VALUES_1(new_list);
}

/* MAKE-DYNAMIC-LIST */
Object make_dynamic_list(length_1)
    Object length_1;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,2);
    if (PUSH_AREA(Dynamic_area,0))
	result = make_list(1,length_1);
    POP_AREA(0);
    return result;
}

Object Global_property_conses = UNBOUND;

/* MUTATE-GLOBAL-PROPERTY */
Object mutate_global_property(symbol_1,value,property_1)
    Object symbol_1, value, property_1;
{
    Object original_plist, property_cons, property_value_cons;
    Object new_property_cons, new_value_cons;

    x_note_fn_call(13,3);
    original_plist = SYMBOL_PLIST(symbol_1);
    property_cons = original_plist;
  next_loop:
    if ( !TRUEP(property_cons))
	goto end_loop;
    if (EQ(property_1,M_CAR(property_cons))) {
	property_cons = M_CDR(property_cons);
	property_value_cons = property_cons;
	goto end_1;
    }
    property_cons = M_CDR(M_CDR(property_cons));
    goto next_loop;
  end_loop:
    property_value_cons = Qnil;
  end_1:;
    if (property_value_cons)
	M_CAR(property_value_cons) = value;
    else {
	new_property_cons = Global_property_conses;
	if ( !TRUEP(new_property_cons))
	    new_property_cons = make_permanent_list(FIX((SI_Long)200L));
	new_value_cons = M_CDR(new_property_cons);
	Global_property_conses = M_CDR(new_value_cons);
	M_CAR(new_property_cons) = property_1;
	M_CAR(new_value_cons) = value;
	M_CDR(new_value_cons) = original_plist;
	SET_SYMBOL_PLIST(symbol_1,new_property_cons);
    }
    return VALUES_1(value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Object_pool_meters, Qobject_pool_meters);

/* UPDATE-OBJECT-POOL-METERS-LIST */
Object update_object_pool_meters_list(new_entry)
    Object new_entry;
{
    Object entry_cons, temp;
    XDeclare_area(1);

    x_note_fn_call(13,4);
    entry_cons = Object_pool_meters;
  next_loop:
    if ( !TRUEP(entry_cons))
	goto end_loop;
    if (EQ(CAAR(entry_cons),CAR(new_entry))) {
	temp = CAR(entry_cons);
	if ( !EQUAL(temp,new_entry))
	    M_CAR(entry_cons) = new_entry;
	goto end_1;
    }
    entry_cons = M_CDR(entry_cons);
    goto next_loop;
  end_loop:
    if (PUSH_AREA(Dynamic_area,0))
	Object_pool_meters = nconc2(Object_pool_meters,CONS(new_entry,Nil));
    POP_AREA(0);
  end_1:;
    return VALUES_1(CAR(new_entry));
}

/* POOL-ENTRY-NAME */
Object pool_entry_name(pool_entry)
    Object pool_entry;
{
    x_note_fn_call(13,5);
    return VALUES_1(FIRST(pool_entry));
}

/* POOL-ENTRY-DATA-TYPE */
Object pool_entry_data_type(pool_entry)
    Object pool_entry;
{
    x_note_fn_call(13,6);
    return VALUES_1(SECOND(pool_entry));
}

/* POOL-ENTRY-OBJECT-COUNT */
Object pool_entry_object_count(pool_entry)
    Object pool_entry;
{
    Object gensymed_symbol;

    x_note_fn_call(13,7);
    gensymed_symbol = THIRD(pool_entry);
    if (BOUNDP(gensymed_symbol))
	return VALUES_1(SYMBOL_VALUE(gensymed_symbol));
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* POOL-ENTRY-OUTSTANDING-OBJECT-COUNT */
Object pool_entry_outstanding_object_count(pool_entry)
    Object pool_entry;
{
    Object outstanding_counter_variable_qm, outstanding_counter_function_qm;

    x_note_fn_call(13,8);
    outstanding_counter_variable_qm = FOURTH(pool_entry);
    if (outstanding_counter_variable_qm) {
	if (BOUNDP(outstanding_counter_variable_qm))
	    return VALUES_1(SYMBOL_VALUE(outstanding_counter_variable_qm));
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
    else {
	outstanding_counter_function_qm = FIFTH(pool_entry);
	if (outstanding_counter_function_qm) {
	    if (fboundp(outstanding_counter_function_qm))
		return FUNCALL_0(SYMBOL_FUNCTION(outstanding_counter_function_qm));
	    else
		return VALUES_1(FIX((SI_Long)0L));
	}
	else
	    return VALUES_1(FIX((SI_Long)0L));
    }
}

/* POOL-ENTRY-MEMORY-USAGE-IN-BYTES */
Object pool_entry_memory_usage_in_bytes(pool_entry)
    Object pool_entry;
{
    Object gensymed_symbol;

    x_note_fn_call(13,9);
    gensymed_symbol = SIXTH(pool_entry);
    if (fboundp(gensymed_symbol))
	return FUNCALL_0(SYMBOL_FUNCTION(gensymed_symbol));
    else
	return VALUES_1(FIX((SI_Long)0L));
}

/* TOTAL-POOL-OUTSTANDING-OBJECT-COUNT */
Object total_pool_outstanding_object_count()
{
    Object accumulator, pool_entry, ab_loop_list_;
    Object outstanding_counter_variable_qm, outstanding_counter_function_qm;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(13,10);
    accumulator = FIX((SI_Long)0L);
    pool_entry = Nil;
    ab_loop_list_ = Object_pool_meters;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pool_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = IFIX(accumulator);
    outstanding_counter_variable_qm = FOURTH(pool_entry);
    if (outstanding_counter_variable_qm)
	gensymed_symbol_1 = BOUNDP(outstanding_counter_variable_qm) ? 
		IFIX(SYMBOL_VALUE(outstanding_counter_variable_qm)) : 
		(SI_Long)0L;
    else {
	outstanding_counter_function_qm = FIFTH(pool_entry);
	gensymed_symbol_1 = outstanding_counter_function_qm ? 
		(fboundp(outstanding_counter_function_qm) ? 
		IFIX(FUNCALL_0(SYMBOL_FUNCTION(outstanding_counter_function_qm))) 
		: (SI_Long)0L) : (SI_Long)0L;
    }
    accumulator = FIX(gensymed_symbol + gensymed_symbol_1);
    goto next_loop;
  end_loop:
    return VALUES_1(accumulator);
    return VALUES_1(Qnil);
}

/* TOTAL-POOL-OBJECT-COUNT */
Object total_pool_object_count()
{
    Object accumulator, pool_entry, ab_loop_list_, gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2;

    x_note_fn_call(13,11);
    accumulator = FIX((SI_Long)0L);
    pool_entry = Nil;
    ab_loop_list_ = Object_pool_meters;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pool_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = IFIX(accumulator);
    gensymed_symbol_1 = THIRD(pool_entry);
    gensymed_symbol_2 = BOUNDP(gensymed_symbol_1) ? 
	    IFIX(SYMBOL_VALUE(gensymed_symbol_1)) : (SI_Long)0L;
    accumulator = FIX(gensymed_symbol + gensymed_symbol_2);
    goto next_loop;
  end_loop:
    return VALUES_1(accumulator);
    return VALUES_1(Qnil);
}

/* TOTAL-POOL-MEMORY-USAGE */
Object total_pool_memory_usage()
{
    Object accumulator, pool_entry, ab_loop_list_, gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2;

    x_note_fn_call(13,12);
    accumulator = FIX((SI_Long)0L);
    pool_entry = Nil;
    ab_loop_list_ = Object_pool_meters;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pool_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = IFIX(accumulator);
    gensymed_symbol_1 = SIXTH(pool_entry);
    gensymed_symbol_2 = fboundp(gensymed_symbol_1) ? 
	    IFIX(FUNCALL_0(SYMBOL_FUNCTION(gensymed_symbol_1))) : (SI_Long)0L;
    accumulator = FIX(gensymed_symbol + gensymed_symbol_2);
    goto next_loop;
  end_loop:
    return VALUES_1(accumulator);
    return VALUES_1(Qnil);
}

Object Names_of_interesting_system_object_pools = UNBOUND;

/* PM-ELT */
Object pm_elt(object,index_1)
    Object object, index_1;
{
    x_note_fn_call(13,13);
    if (CONSP(object))
	return nth(index_1,object);
    else if (ARRAYP(object))
	return aref1(object,index_1);
    else
	return VALUES_1(FIX((SI_Long)-1234567L));
}

/* PM-NTHCDR */
Object pm_nthcdr(object,index_1)
    Object object, index_1;
{
    x_note_fn_call(13,14);
    if (CONSP(object))
	return nthcdr(index_1,object);
    else
	return VALUES_1(FIX((SI_Long)-1234567L));
}

/* PM-TYPE-OF */
Object pm_type_of(object)
    Object object;
{
    x_note_fn_call(13,15);
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

static Object Qcomposite_object;   /* composite-object */

/* PM-COMPOSITE-TYPE-OF */
Object pm_composite_type_of(object)
    Object object;
{
    Object temp, element, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(13,16);
    if (ARRAYP(object) || CONSP(object)) {
	temp = pm_type_of(object);
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
	ab_loopvar__2 = LIST_1(pm_type_of(element));
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	return list_star(3,Qcomposite_object,temp,temp_1);
    }
    else
	return pm_type_of(object);
}

DEFINE_VARIABLE_WITH_SYMBOL(Single_element_string, Qsingle_element_string);

static Object string_constant;     /* "#w\"" */

static Object string_constant_1;   /* " " */

static Object string_constant_2;   /* "\"" */

/* PM-PRINT-WIDE-STRING */
Object pm_print_wide_string(thing)
    Object thing;
{
    Object elt_1, elt_arg_1, elt_new_value;
    SI_Long i;

    x_note_fn_call(13,17);
    princ(string_constant,_);
    i = (SI_Long)0L;
    elt_1 = Nil;
  next_loop:
    elt_1 = aref1(thing,FIX(i));
    if (IFIX(elt_1) == (SI_Long)0L)
	goto end_loop;
    if (newline_p(elt_1))
	terpri(_);
    else if (IFIX(elt_1) == (SI_Long)32L)
	princ(string_constant_1,_);
    else {
	elt_arg_1 = Single_element_string;
	elt_new_value = CODE_CHAR(elt_1);
	set_elt(elt_arg_1,FIX((SI_Long)0L),elt_new_value);
	princ(Single_element_string,_);
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    princ(string_constant_2,_);
    return VALUES_1(Qnil);
}

/* PM-PRINT-SUBSTRUCTURE */
Object pm_print_substructure(object,max_depth,depth)
    Object object, max_depth, depth;
{
    Object element;
    SI_Long i, ab_loop_bind_, j, ab_loop_bind__1;

    x_note_fn_call(13,18);
    if (FIXNUMP(max_depth) && FIXNUM_GT(depth,max_depth))
	format((SI_Long)3L,T,"~s~%",object);
    else if (STRINGP(object))
	format((SI_Long)3L,T,"~s~%",object);
    else if (text_string_p(object)) {
	pm_print_wide_string(object);
	terpri(_);
    }
    else if (ARRAYP(object) || CONSP(object)) {
	format((SI_Long)3L,T,"~(~s~):~%",pm_type_of(object));
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
	pm_print_substructure(element,max_depth,FIXNUM_ADD1(depth));
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    else
	format((SI_Long)3L,T,"~s~%",object);
    return VALUES_1(Nil);
}

/* PM-PRINT-STRUCTURE */
Object pm_print_structure(object,max_depth)
    Object object, max_depth;
{
    x_note_fn_call(13,19);
    pm_print_substructure(object,max_depth,FIX((SI_Long)0L));
    return VALUES_1(object);
}

static Object string_constant_3;   /* "-G2-STRUCT" */

/* PM-STRUCTURE-TYPE */
Object pm_structure_type(thing)
    Object thing;
{
    Object raw_type_name, string_1, suffix, n_1, tail, temp;

    x_note_fn_call(13,20);
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
			Ab_package_1);
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

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* PM-FRAME-TYPE */
Object pm_frame_type(thing)
    Object thing;
{
    Object x;

    x_note_fn_call(13,21);
    if (SIMPLE_VECTOR_P(thing) && IFIX(length(thing)) > (SI_Long)2L) {
	x = ISVREF(thing,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(x))
	    return VALUES_1(ISVREF(x,(SI_Long)1L));
	else if (EQ(x,Qavailable_frame_vector))
	    return VALUES_1(Qavailable_frame_vector);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmanaged_float;      /* managed-float */

/* PM-GENSYM-TYPE-OF */
Object pm_gensym_type_of(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(13,22);
    temp = pm_frame_type(thing);
    if (temp);
    else
	temp = pm_structure_type(thing);
    if (temp);
    else
	temp = managed_float_p_function(thing) ? Qmanaged_float : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return type_of(thing);
}

Object Pm_file_names = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Pm_slot_names, Qpm_slot_names);

/* PM-SLOT-NAMES */
Object pm_slot_names(vector_1)
    Object vector_1;
{
    Object filename, ab_loop_list_, filename_qm, stream, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(13,23);
    SAVE_STACK();
    if ( !TRUEP(Pm_slot_names)) {
	filename = Nil;
	ab_loop_list_ = Pm_file_names;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	filename = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (gensym_probe_file(filename)) {
	    filename_qm = filename;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	filename_qm = Qnil;
      end_1:;
	if (filename_qm) {
	    format((SI_Long)3L,T,"[Reading slotnames from ~s]~%",filename_qm);
	    stream = lopen(1,filename_qm);
	    if (PUSH_UNWIND_PROTECT(0))
		Pm_slot_names = lread(stream,Nil,_,_);
	    POP_UNWIND_PROTECT(0);
	    if (STREAMP(stream))
		lclose(1,stream);
	    CONTINUE_UNWINDING(0);
	}
    }
    temp = pm_structure_type(vector_1);
    if (temp);
    else
	temp = pm_frame_type(vector_1);
    temp = assq_function(temp,Pm_slot_names);
    RESTORE_STACK();
    return VALUES_1(CDR(temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Pm_max_length, Qpm_max_length);

static Object string_constant_4;   /* " is a " */

static Object string_constant_5;   /* " aka " */

static Object list_constant;       /* # */

static Object string_constant_6;   /* "  " */

static Object string_constant_7;   /* "CDR" */

/* PM-DESCRIBE */
Object pm_describe(thing)
    Object thing;
{
    Object max_length, temp, names, elt_1, name, names_old_value, sublist;
    Object ab_loop_iter_flag_;
    SI_Long ab_loop_bind_, i;
    char temp_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,24);
    if (PUSH_AREA(Dynamic_area,0)) {
	max_length = Pm_max_length;
	pm_prin1(thing);
	princ(string_constant_4,_);
	prin1(pm_gensym_type_of(thing),_);
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
	    pm_print_wide_string(thing);
	    terpri(_);
	}
	else if (VECTORP(thing)) {
	    names = pm_slot_names(thing);
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
	    pm_print_object_id(elt_1);
	    princ(string_constant_6,_);
	    pm_print(elt_1);
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
	    pm_print_object_id(elt_1);
	    princ(string_constant_6,_);
	    pm_print(elt_1);
	    temp = CDR(sublist);
	    if (ATOM(temp) && CDR(sublist)) {
		format((SI_Long)3L,T,"[~2d] ",string_constant_7);
		if (Nil)
		    format((SI_Long)3L,T," ~50a ",Nil);
		pm_print_object_id(CDR(sublist));
		princ(string_constant_6,_);
		pm_print(CDR(sublist));
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

DEFINE_VARIABLE_WITH_SYMBOL(Pm_temp_string, Qpm_temp_string);

static Object string_constant_8;   /* "0123456789abcdef" */

/* PM-OBJECT-ID */
Object pm_object_id(object)
    Object object;
{
    Object addr_1, char_arg_1, temp;
    SI_Long i;
    char char_new_value;

    x_note_fn_call(13,25);
    addr_1 = pct_pointer(object);
    i = (SI_Long)9L;
  next_loop:
    if (i < (SI_Long)2L)
	goto end_loop;
    char_arg_1 = Pm_temp_string;
    char_new_value = ICHAR(string_constant_8,IFIX(addr_1) & (SI_Long)15L);
    SET_ICHAR(char_arg_1,i,char_new_value);
    addr_1 = FIX(IFIX(addr_1) >>  -  - (SI_Long)4L);
    i = i - (SI_Long)1L;
    goto next_loop;
  end_loop:;
    char_arg_1 = Pm_temp_string;
    temp = CHR('0');
    SET_CHAR(char_arg_1,FIX((SI_Long)0L),temp);
    char_arg_1 = Pm_temp_string;
    temp = CHR('x');
    SET_CHAR(char_arg_1,FIX((SI_Long)1L),temp);
    return VALUES_1(Pm_temp_string);
}

/* PM-PRINT-OBJECT-ID */
Object pm_print_object_id(object)
    Object object;
{
    x_note_fn_call(13,26);
    return pm_prin1(pm_object_id(object));
}

/* PM-PRINT */
Object pm_print(thing)
    Object thing;
{
    x_note_fn_call(13,27);
    pm_prin1(thing);
    terpri(_);
    return VALUES_1(thing);
}

/* PM-PRINC */
Object pm_princ(thing)
    Object thing;
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(13,28);
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
Object pm_prin1(thing)
    Object thing;
{
    Object print_circle, wide_string, gensym_string, car_1, rest_1;
    Object ab_loop_list_;
    Declare_special(1);
    XDeclare_area(1);

    x_note_fn_call(13,29);
    if (PUSH_AREA(Dynamic_area,0)) {
	print_circle = T;
	PUSH_SPECIAL_WITH_SYMBOL(Print_circle,Qprint_circle,print_circle,0);
	  if (text_string_p(thing))
	      pm_print_wide_string(thing);
	  else if (managed_float_p_function(thing)) {
	      wide_string = tformat_text_string(2,string_constant_9,thing);
	      gensym_string = wide_string_to_gensym_string(wide_string);
	      princ(string_constant_10,_);
	      princ(gensym_string,_);
	      princ(string_constant_1,_);
	      pm_print_object_id(thing);
	      princ(string_constant_11,_);
	      reclaim_text_string(wide_string);
	      reclaim_gensym_string(gensym_string);
	  }
	  else if (pm_structure_type(thing)) {
	      princ(string_constant_12,_);
	      princ(pm_structure_type(thing),_);
	      princ(string_constant_1,_);
	      princ(pm_object_id(thing),_);
	      princ(string_constant_11,_);
	  }
	  else if (pm_frame_type(thing)) {
	      princ(string_constant_12,_);
	      princ(pm_frame_type(thing),_);
	      princ(string_constant_1,_);
	      pm_print_object_id(thing);
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
	      pm_prin1(car_1);
	      if ( !TRUEP(rest_1));
	      else if (CONSP(rest_1))
		  princ(string_constant_1,_);
	      else {
		  princ(string_constant_14,_);
		  pm_prin1(rest_1);
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

Object System_variable_descriptions_prop = UNBOUND;

static Object Qsystem_variable_descriptions;  /* system-variable-descriptions */

/* RECORD-SYSTEM-VARIABLE */
Object record_system_variable(system_variable_name,module_name,
	    initialization,re_evaluate_initialization_on_rebinding_qm,
	    also_bind_globally_qm,value_reclaimer_qm,kb_specific_qm)
    Object system_variable_name, module_name, initialization;
    Object re_evaluate_initialization_on_rebinding_qm, also_bind_globally_qm;
    Object value_reclaimer_qm, kb_specific_qm;
{
    Object system_variable_descriptions, system_variable_description_qm;
    Object cdr_new_value;

    x_note_fn_call(13,30);
    system_variable_descriptions = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qsystem_variable_descriptions);
    system_variable_description_qm = assoc_eql(system_variable_name,
	    system_variable_descriptions);
    if (system_variable_description_qm) {
	cdr_new_value = LIST_4(initialization,
		re_evaluate_initialization_on_rebinding_qm,kb_specific_qm,
		value_reclaimer_qm);
	M_CDR(system_variable_description_qm) = cdr_new_value;
    }
    else
	mutate_global_property(module_name,
		nconc2(system_variable_descriptions,
		LIST_1(LIST_5(system_variable_name,initialization,
		re_evaluate_initialization_on_rebinding_qm,kb_specific_qm,
		value_reclaimer_qm))),Qsystem_variable_descriptions);
    if (also_bind_globally_qm)
	return set_system_variable_as_appropriate(system_variable_name,
		initialization);
    else
	return VALUES_1(Nil);
}

static Object Qlisp_modules_to_be_loaded;  /* lisp-modules-to-be-loaded */

/* COMPUTE-SYSTEM-VARIABLES */
Object compute_system_variables(system_name)
    Object system_name;
{
    Object module_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, system_variable_name, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4, ab_loop_desetq_;

    x_note_fn_call(13,31);
    module_name = Nil;
    ab_loop_list_ = get(system_name,Qlisp_modules_to_be_loaded,_);
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
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qsystem_variable_descriptions);
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
    goto end_1;
    ab_loopvar__2 = Qnil;
  end_1:;
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

DEFINE_VARIABLE_WITH_SYMBOL(Process_initializations_alist, Qprocess_initializations_alist);

DEFINE_VARIABLE_WITH_SYMBOL(No_saved_initial_value, Qno_saved_initial_value);

/* INITIALIZE-SYSTEM-VARIABLES */
Object initialize_system_variables(system_name,process_handle)
    Object system_name, process_handle;
{
    Object process_initializations_entry, push_arg, temp, module_name;
    Object ab_loop_list_, system_variable_name, initialization;
    Object re_evaluate_initialization_on_rebinding_qm, kb_specific_qm;
    Object ab_loop_list__1, saved_initial_value_if_any, ab_loop_desetq_;
    Object temp_1, new_value;

    x_note_fn_call(13,32);
    process_initializations_entry = assq_function(process_handle,
	    Process_initializations_alist);
    if (process_initializations_entry);
    else {
	push_arg = LIST_1(process_handle);
	temp = CONS(push_arg,Process_initializations_alist);
	Process_initializations_alist = temp;
	process_initializations_entry = FIRST(Process_initializations_alist);
    }
    module_name = Nil;
    ab_loop_list_ = get(system_name,Qlisp_modules_to_be_loaded,_);
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
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(module_name),
	    Qsystem_variable_descriptions);
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
	    getfq_function(CDR(process_initializations_entry),
	    system_variable_name,No_saved_initial_value);
    if (EQ(saved_initial_value_if_any,No_saved_initial_value) || 
	    re_evaluate_initialization_on_rebinding_qm) {
	new_value = 
		set_system_variable_as_appropriate(system_variable_name, 
		!TRUEP(kb_specific_qm) ? initialization : Nil);
	temp = set_getf(CDR(process_initializations_entry),
		system_variable_name,new_value);
	M_CDR(process_initializations_entry) = temp;
    }
    else if ( !EQ(saved_initial_value_if_any,No_saved_initial_value))
	set(system_variable_name,saved_initial_value_if_any);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(In_clear_kb_p, Qin_clear_kb_p);

static Object Kno_initial_value;   /* :no-initial-value */

static Object Qno_initial_value;   /* no-initial-value */

static Object Ksystem_frame;       /* :system-frame */

static Object Ksymbol_value;       /* :symbol-value */

static Object Kfuncall;            /* :funcall */

/* SET-SYSTEM-VARIABLE-AS-APPROPRIATE */
Object set_system_variable_as_appropriate(system_variable_name,initialization)
    Object system_variable_name, initialization;
{
    Object in_clear_kb_p, temp;
    Declare_special(1);

    x_note_fn_call(13,33);
    if (EQ(initialization,Kno_initial_value) || CONSP(initialization) && 
	    EQ(M_CAR(initialization),Qno_initial_value))
	return set(system_variable_name,No_saved_initial_value);
    else if (EQ(initialization,Ksystem_frame)) {
	in_clear_kb_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(In_clear_kb_p,Qin_clear_kb_p,in_clear_kb_p,0);
	  temp = make_system_frame(system_variable_name);
	POP_SPECIAL();
	return install_system_table(temp);
    }
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

Object Named_dynamic_extent_description_prop = UNBOUND;

/* MAKE-NAMED-DYNAMIC-EXTENT-DESCRIPTION */
Object make_named_dynamic_extent_description(name,module,
	    variables_of_dynamic_extent,
	    dynamic_superiors_list_of_dynamic_extent,
	    shadowing_list_of_dynamic_extent,
	    included_list_of_dynamic_extent,named_dynamic_extent_plist)
    Object name, module, variables_of_dynamic_extent;
    Object dynamic_superiors_list_of_dynamic_extent;
    Object shadowing_list_of_dynamic_extent, included_list_of_dynamic_extent;
    Object named_dynamic_extent_plist;
{
    x_note_fn_call(13,34);
    return list_star(7,name,module,variables_of_dynamic_extent,
	    dynamic_superiors_list_of_dynamic_extent,
	    shadowing_list_of_dynamic_extent,
	    included_list_of_dynamic_extent,named_dynamic_extent_plist);
}

static Object Qgsi_api_symbol;     /* gsi-api-symbol */

/* DECLARE-GSI-API-SYMBOL-1 */
Object declare_gsi_api_symbol_1(name)
    Object name;
{
    x_note_fn_call(13,35);
    return set_get(name,Qgsi_api_symbol,T);
}

/* G2INT-X-ERROR */
int g2int_x_error(error_code)
    int error_code;
{
    int result_1;

    x_note_fn_call(13,36);
    result_1 = error_code;
    return result_1;
}

/* G2INT-NETWORK-EVENT-HANDLER */
SI_Long g2int_network_event_handler(event_code,event_socket_handle,
	    event_status_code)
    SI_Long event_code, event_socket_handle, event_status_code;
{
    SI_Long result_1;

    x_note_fn_call(13,37);
    result_1 = IFIX(handle_event_internal(FIX(event_code),
	    FIX(event_socket_handle),FIX(event_status_code)));
    return result_1;
}

/* G2INT-OPEN-FD-CALLBACK */
SI_Long g2int_open_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,38);
    result_1 = fd;
    return result_1;
}

/* G2INT-CLOSE-FD-CALLBACK */
SI_Long g2int_close_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,39);
    result_1 = fd;
    return result_1;
}

/* G2INT-WRITING-FD-CALLBACK */
SI_Long g2int_writing_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,40);
    result_1 = fd;
    return result_1;
}

/* G2INT-NOT-WRITING-FD-CALLBACK */
SI_Long g2int_not_writing_fd_callback(fd)
    SI_Long fd;
{
    SI_Long result_1;

    x_note_fn_call(13,41);
    result_1 = fd;
    return result_1;
}

/* MAKE-SYMBOL-NAME-FROM-C-NAME */
Object make_symbol_name_from_c_name(length_1,buffer)
    Object length_1, buffer;
{
    Object string_1, buffer_char, char_1, temp;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(13,42);
    string_1 = obtain_simple_gensym_string(length_1);
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
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-NAME-FOR-FUNCTION */
Object get_name_for_function(fn)
    Object fn;
{
    Object temp_1;
    char *temp;

    x_note_fn_call(13,43);
    if (SYMBOLP(fn))
	return gensym_symbol_name(fn);
    temp = ISTRING(Gensym_environment_variable_buffer);
    temp_1 = FIX(g2ext_get_name_for_function(temp,
	    inline_get_function_address(fn)));
    return make_symbol_name_from_c_name(temp_1,
	    Gensym_environment_variable_buffer);
}

/* C-GET-TRACE-FUNCTION-NAME */
Object c_get_trace_function_name(buffer)
    Object buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,44);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_get_trace_function_name(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object Trace_function_p_prop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Running_trace_function_p, Qrunning_trace_function_p);

static Object Qtrace_function_p;   /* trace-function-p */

/* G2INT-RUN-TRACE-FUNCTION */
SI_Long g2int_run_trace_function()
{
    Object length_1, temp, function_name, running_trace_function_p;
    SI_Long result_1;
    Declare_special(1);

    x_note_fn_call(13,45);
    length_1 = c_get_trace_function_name(Gensym_environment_variable_buffer);
    temp = FIX((SI_Long)0L);
    function_name = NUM_LE(temp,length_1) ? intern_gensym_string(1,
	    make_symbol_name_from_c_name(length_1,
	    Gensym_environment_variable_buffer)) : Nil;
    if (getfq_function_no_default(INLINE_SYMBOL_PLIST(function_name),
	    Qtrace_function_p) && fboundp(function_name)) {
	running_trace_function_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Running_trace_function_p,Qrunning_trace_function_p,running_trace_function_p,
		0);
	  FUNCALL_0(function_name);
	POP_SPECIAL();
	result_1 = (SI_Long)1L;
    }
    else
	result_1 = (SI_Long)0L;
    return result_1;
}

DEFINE_VARIABLE_WITH_SYMBOL(Unix_command_callback_function, Qunix_command_callback_function);

/* G2INT-UNIX-COMMAND-CALLBACK */
SI_Long g2int_unix_command_callback()
{
    SI_Long result_1;

    x_note_fn_call(13,46);
    result_1 = Unix_command_callback_function ? 
	    IFIX(FUNCALL_0(Unix_command_callback_function)) : (SI_Long)0L;
    return result_1;
}

DEFINE_VARIABLE_WITH_SYMBOL(Cached_fixnum_time_qm, Qcached_fixnum_time_qm);

/* C-NATIVE-CLOCK-TICKS-OR-CACHE */
Object c_native_clock_ticks_or_cache(as_accurately_as_possible_qm,
	    disable_caching_fixnum_time_qm)
    Object as_accurately_as_possible_qm, disable_caching_fixnum_time_qm;
{
    Object temp;

    x_note_fn_call(13,47);
    temp = FIX(g2ext_g2_clock_ticks(IFIX(Most_positive_fixnum)));
    return VALUES_1(temp);
}

/* CLEAR-FIXNUM-TIME-ALARM */
Object clear_fixnum_time_alarm()
{
    x_note_fn_call(13,48);
    if (Cached_fixnum_time_qm) {
	if (g2ext_cancel_future_alarm_signal() != (SI_Long)0L)
	    format((SI_Long)2L,T,
		    "~%Failure reported when clearing sigalarm, continuing.");
	Cached_fixnum_time_qm = Nil;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Check_time_on_next_uuid, Qcheck_time_on_next_uuid);

DEFINE_VARIABLE_WITH_SYMBOL(Time_to_check_network_events, Qtime_to_check_network_events);

/* G2INT-SERVICE-SIGALRM-SIGNAL */
Object g2int_service_sigalrm_signal()
{
    x_note_fn_call(13,49);
    Cached_fixnum_time_qm = Nil;
    Check_time_on_next_uuid = T;
    Time_to_check_network_events = T;
    return VALUES_1(Nil);
}

/* GET-FIXNUM-TIME-FUNCTION */
Object get_fixnum_time_function()
{
    Object temp;

    x_note_fn_call(13,50);
    temp = c_native_clock_ticks_or_cache(Nil,Nil);
    return VALUES_1(temp);
}

Object Fixnum_time_units_per_second = UNBOUND;

Object Fixnum_time_bignum_worries_limit = UNBOUND;

/* FIXNUM-TIME-INTERVAL-PROTECTED */
Object fixnum_time_interval_protected(milliseconds)
    Object milliseconds;
{
    Object result_fixnum;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(13,51);
    result_fixnum = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result_fixnum = ceiling(ltimes(milliseconds,
		Fixnum_time_units_per_second),FIX((SI_Long)1000L));
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(result_fixnum);
}

/* FIXNUM-TIME-INTERVAL */
Object fixnum_time_interval(milliseconds)
    Object milliseconds;
{
    Object temp;
    SI_Long local_time_units_per_second;

    x_note_fn_call(13,52);
    local_time_units_per_second = IFIX(Fixnum_time_units_per_second);
    if (local_time_units_per_second == (SI_Long)1000L)
	temp = milliseconds;
    else if (FIXNUM_LT(milliseconds,Fixnum_time_bignum_worries_limit))
	temp = FIX((IFIX(milliseconds) * local_time_units_per_second + 
		((SI_Long)1000L - (SI_Long)1L)) / (SI_Long)1000L);
    else
	temp = fixnum_time_interval_protected(milliseconds);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_time_interval_for_one_second, Qfixnum_time_interval_for_one_second);

/* FIXNUM-TIME-DIFFERENCE-IN-SECONDS */
Object fixnum_time_difference_in_seconds(later_fixnum_time,earlier_fixnum_time)
    Object later_fixnum_time, earlier_fixnum_time;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(13,53);
    if (FIXNUM_GE(later_fixnum_time,earlier_fixnum_time))
	gensymed_symbol = IFIX(FIXNUM_MINUS(later_fixnum_time,
		earlier_fixnum_time));
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(later_fixnum_time,
		earlier_fixnum_time));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
    }
    gensymed_symbol_1 = IFIX(Fixnum_time_units_per_second);
    return VALUES_1(FIX(gensymed_symbol / gensymed_symbol_1));
}

/* C-SET-FILE-OPERATION-TIMEOUT */
Object c_set_file_operation_timeout(timeout)
    Object timeout;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,54);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(timeout);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = timeout;
    temp = FIX(g2ext_set_file_operation_retry_timeout(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-UNIX_COMMAND_WITH_STRING_OUTPUT */
Object c_unix_command_with_string_output(command,buff,max_bytes)
    Object command, buff, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,55);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(buff);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* UNIX-COMMAND-OUTPUT-AS-STRING */
Object unix_command_output_as_string(command_string)
    Object command_string;
{
    Object result_code;

    x_note_fn_call(13,56);
    result_code = c_unix_command_with_string_output(command_string,
	    Gensym_environment_variable_buffer,
	    Maximum_gensym_environment_variable_length);
    if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(result_code)) {
	  case 0:
	    return copy_null_terminated_string_as_text_string(Gensym_environment_variable_buffer);
	  case -1:
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

/* C-UNIX_COMMAND_WITH_STRING_OUTPUT_AND_TIMEOUT */
Object c_unix_command_with_string_output_and_timeout(command,dir,buff,
	    timeout_in_ms,max_bytes)
    Object command, dir, buff, timeout_in_ms, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,57);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(dir);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(buff);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* UNIX-COMMAND-OUTPUT-AS-STRING-WITH-TIMEOUT-CALLBACK */
Object unix_command_output_as_string_with_timeout_callback(command_string,
	    directory_1,initial_timeout_qm,callback_qm)
    Object command_string, directory_1, initial_timeout_qm, callback_qm;
{
    Object unix_command_callback_function, temp, temp_1, result_code;
    Declare_special(1);
    Object result;

    x_note_fn_call(13,58);
    unix_command_callback_function = callback_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Unix_command_callback_function,Qunix_command_callback_function,unix_command_callback_function,
	    0);
      temp = Gensym_environment_variable_buffer;
      temp_1 = initial_timeout_qm;
      if (temp_1);
      else
	  temp_1 = Most_positive_fixnum;
      result_code = 
	      c_unix_command_with_string_output_and_timeout(command_string,
	      directory_1,temp,temp_1,
	      Maximum_gensym_environment_variable_length);
      if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	      result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	  result = VALUES_1(Nil);
      else
	  switch (INTEGER_TO_CHAR(result_code)) {
	    case 0:
	      result = copy_null_terminated_string_as_text_string(Gensym_environment_variable_buffer);
	      break;
	    case -1:
	      result = VALUES_1(Nil);
	      break;
	    default:
	      result = VALUES_1(Nil);
	      break;
	  }
    POP_SPECIAL();
    return result;
}

/* C-RUN_PROGRAM_WITH_STRING_OUTPUT_AND_TIMEOUT */
Object c_run_program_with_string_output_and_timeout(command,dir,buff,
	    timeout_in_ms,max_bytes)
    Object command, dir, buff, timeout_in_ms, max_bytes;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,59);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(dir);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(buff);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-DIRECTORY_CONTAINS_DIRECTORY */
Object c_directory_contains_directory(containing_directory,contained_directory)
    Object containing_directory, contained_directory;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,60);
    gensymed_symbol = 
	    copy_foreign_string_arg_if_appropriate(containing_directory);
    gensymed_symbol_1 = 
	    copy_foreign_string_arg_if_appropriate(contained_directory);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-WRITE-STRING-TO-CONSOLE */
Object c_write_string_to_console(string_1,write_console_p)
    Object string_1, write_console_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,61);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = FIX(g2ext_write_string_to_console_1(ISTRING(temp),
	    IFIX(write_console_p)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Known_process_ids_qm, Qknown_process_ids_qm);

DEFINE_VARIABLE_WITH_SYMBOL(All_foreign_function_images_qm, Qall_foreign_function_images_qm);

DEFINE_VARIABLE_WITH_SYMBOL(All_external_foreign_function_images_qm, Qall_external_foreign_function_images_qm);

/* KILL-FOREIGN-IMAGES */
Object kill_foreign_images(list_of_foreign_images_qm)
    Object list_of_foreign_images_qm;
{
    Object copy_of_list_of_foreign_images, foreign_image_info, ab_loop_list_;

    x_note_fn_call(13,62);
    if (list_of_foreign_images_qm) {
	copy_of_list_of_foreign_images = 
		copy_list_using_icp_conses_function(list_of_foreign_images_qm);
	foreign_image_info = Nil;
	ab_loop_list_ = copy_of_list_of_foreign_images;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	foreign_image_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	kill_foreign_image_unconditionally(foreign_image_info);
	goto next_loop;
      end_loop:
	reclaim_icp_list_function(copy_of_list_of_foreign_images);
    }
    return VALUES_1(Nil);
}

/* SHUTDOWN-SYSTEM-FOR-EXIT */
Object shutdown_system_for_exit()
{
    Object process_id, ab_loop_list_, temp;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(13,63);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	kill_foreign_images(All_foreign_function_images_qm);
	kill_foreign_images(All_external_foreign_function_images_qm);
	if (Known_process_ids_qm) {
	    process_id = Nil;
	    ab_loop_list_ = Known_process_ids_qm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    process_id = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    kill_possibly_leftover_spawned_process(process_id);
	    goto next_loop;
	  end_loop:
	    reclaim_sysproc_list_function(Known_process_ids_qm);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    g2ext_shift_rule_ordering();
    close_and_disconnect_all_sockets();
    temp = close_native_window();
    return VALUES_1(temp);
}

Object Isqrt_of_most_positive_fixnum = UNBOUND;

Object Minus_of_isqrt_of_most_positive_fixnum = UNBOUND;

/* SCALEF-FUNCTION */
Object scalef_function(scale,value)
    Object scale, value;
{
    Object temp;

    x_note_fn_call(13,64);
    temp = LONG_TO_FIXNUM(inline_floor_1(0.5 + (double)IFIX(scale) * 
	    (double)IFIX(value) / (double)(SI_Long)4096L));
    return VALUES_1(temp);
}

/* INVERSE-SCALEF-FUNCTION */
Object inverse_scalef_function(scale,value)
    Object scale, value;
{
    Object temp;

    x_note_fn_call(13,65);
    temp = LONG_TO_FIXNUM(inline_floor_1(0.5 + (double)IFIX(value) * 
	    (double)(SI_Long)4096L / (double)IFIX(scale)));
    return VALUES_1(temp);
}

/* FLOAT-DELTA-X-IN-WINDOW */
Object float_delta_x_in_window(delta_x_in_workspace,x_scale)
    Object delta_x_in_workspace, x_scale;
{
    x_note_fn_call(13,66);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(x_scale) * 
	    (double)IFIX(delta_x_in_workspace) / (double)(SI_Long)4096L));
}

/* FLOAT-DELTA-Y-IN-WINDOW */
Object float_delta_y_in_window(delta_y_in_workspace,y_scale)
    Object delta_y_in_workspace, y_scale;
{
    x_note_fn_call(13,67);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(y_scale) * 
	    (double)IFIX(delta_y_in_workspace) / (double)(SI_Long)4096L));
}

/* SCALE-SCALE */
Object scale_scale(scale,numerator_1,denominator_1)
    Object scale, numerator_1, denominator_1;
{
    x_note_fn_call(13,68);
    return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(0.5 + 
	    (double)IFIX(scale) * (double)IFIX(numerator_1) / 
	    (double)IFIX(denominator_1))));
}

/* CONVERT-TO-MAGNIFICATION */
Object convert_to_magnification(factor)
    Object factor;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(13,69);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = lmin(lmax(l_round(ltimes(factor,FIX((SI_Long)256L)),_),
		Least_magnification),Greatest_magnification);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* CONVERT-TO-MAGNIFICATION-AT-COMPILE-TIME */
Object convert_to_magnification_at_compile_time(factor)
    Object factor;
{
    x_note_fn_call(13,70);
    return lmin(lmax(l_round(ltimes(factor,FIX((SI_Long)256L)),_),
	    Least_magnification),Greatest_magnification);
}

static Object float_constant;      /* 0.0 */

/* CONVERT-MAGNIFICATION-TO-FACTOR */
Object convert_magnification_to_factor(magnification)
    Object magnification;
{
    Object temp;
    double temp_1;

    x_note_fn_call(13,71);
    temp = lfloat(magnification,float_constant);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 / 256.0));
}

/* INVERSE-MAGNIFY */
Object inverse_magnify(delta_in_workspace,magnification)
    Object delta_in_workspace, magnification;
{
    Object temp;
    double temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(13,72);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = lfloat(magnification,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = 
		l_round(DOUBLE_TO_DOUBLE_FLOAT((double)((float)
		(IFIX(delta_in_workspace) << (SI_Long)8L)) / temp_1),_);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* CONVERT-ANY-NUMBER-TO-TEXT-WIDTH-AT-COMPILE-TIME */
Object convert_any_number_to_text_width_at_compile_time(number)
    Object number;
{
    x_note_fn_call(13,73);
    return l_round(ltimes(number,FIX((SI_Long)256L)),_);
}

/* CONVERT-ANY-NUMBER-TO-TEXT-WIDTH */
Object convert_any_number_to_text_width(number)
    Object number;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(13,74);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = l_round(ltimes(number,FIX((SI_Long)256L)),_);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

Object Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation = UNBOUND;

/* EXIT-LISP-PROCESS */
Object exit_lisp_process varargs_1(int, n)
{
    Object status_qm, status;
    Declare_varargs_nonrelocating;

    x_note_fn_call(13,75);
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

DEFINE_VARIABLE_WITH_SYMBOL(Inner_abort_level_tag, Qinner_abort_level_tag);

DEFINE_VARIABLE_WITH_SYMBOL(Abort_level_0_tag, Qabort_level_0_tag);

static Object list_constant_1;     /* # */

static Object Qabort_level_0;      /* abort-level-0 */

/* ABORT */
Object abort_g2 varargs_1(int, n)
{
    Object abort_level_qm, tag;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(13,76);
    INIT_ARGS_nonrelocating();
    abort_level_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tag = abort_level_qm ? nth(abort_level_qm,list_constant_1) : 
	    Inner_abort_level_tag;
    if (EQ(tag,Qabort_level_0) && Abort_level_0_tag)
	tag = Abort_level_0_tag;
    result = VALUES_1(Nil);
    THROW(tag,result);
}

/* C-SPAWN_COMMAND_LINE_PROCESS */
Object c_spawn_command_line_process(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,77);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = 
	    DOUBLE_TO_DOUBLE_FLOAT(g2ext_spawn_command_line_process(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-SPAWN_EXECUTABLE_PROCESS */
Object c_spawn_executable_process(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,78);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = DOUBLE_TO_DOUBLE_FLOAT(g2ext_spawn_command_directly(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-LOAD_LIBRARY */
Object c_load_library(name,init_function_name,init_function_arg)
    Object name, init_function_name, init_function_arg;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(13,79);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = 
	    copy_foreign_string_arg_if_appropriate(init_function_name);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-PRODUCE_SHARED_OBJECT */
Object c_produce_shared_object(kb_filename,nfiles,obj_suffix,dll_name)
    Object kb_filename, nfiles, obj_suffix, dll_name;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(13,80);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(kb_filename);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(obj_suffix);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(dll_name);
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
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(temp);
}

/* C-SET-INCLUDE-DIRECTORY */
Object c_set_include_directory(directory_1)
    Object directory_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,81);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(directory_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = directory_1;
    temp = FIX(g2ext_set_include_directory(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* LOAD-LIBRARY */
Object load_library(name,init_function_name,init_function_arg)
    Object name, init_function_name, init_function_arg;
{
    Object temp;

    x_note_fn_call(13,82);
    temp = T ? ((SI_Long)0L == IFIX(c_load_library(name,init_function_name,
	    init_function_arg)) ? T : Nil) : Nil;
    return VALUES_1(temp);
}

/* C-SUBSTATUS_RUN_COMMAND_LINE */
Object c_substatus_run_command_line(command_string)
    Object command_string;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,83);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command_string;
    temp = FIX(g2ext_substatus_run_command_line(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-UUID-CREATE */
Object c_uuid_create(buffer)
    Object buffer;
{
    Object temp;

    x_note_fn_call(13,84);
    temp = FIX(g2ext_uuid_create(UBYTE_16_SARRAY_TO_USHORT_PTR(buffer)));
    return VALUES_1(temp);
}

Object Rpc_s_uuid_local_only_message = UNBOUND;

Object Rpc_s_uuid_no_address_message = UNBOUND;

/* NO-OPERATION-FUNCTION */
Object no_operation_function()
{
    x_note_fn_call(13,85);
    return VALUES_1(Nil);
}

static Object float_constant_1;    /* 4195835.0 */

static Object float_constant_2;    /* 3145727.0 */

/* INTEL-INSIDE-P */
Object intel_inside_p()
{
    Object a, b, temp_4, temp_5;
    double temp, temp_1, temp_2, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(13,86);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	a = float_constant_1;
	b = float_constant_2;
	temp = DOUBLE_FLOAT_TO_DOUBLE(a);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(b);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(a);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(b);
	temp_4 = DOUBLE_TO_DOUBLE_FLOAT(temp - temp_1 * (temp_2 / temp_3));
	temp_5 = FIX((SI_Long)100L);
	result = VALUES_1(NUM_GT(temp_4,temp_5) ? T : Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* C-G2_PROBE_FILE */
Object c_g2_probe_file(namestring_1)
    Object namestring_1;
{
    Object temp;

    x_note_fn_call(13,87);
    temp = 
	    LONG_TO_FIXNUM(g2ext_g2_probe_file(UBYTE_16_SARRAY_TO_USHORT_PTR(namestring_1)));
    return VALUES_1(temp);
}

/* C-G2_STREAM_OPEN */
Object c_g2_stream_open(namestring_1,open_mode)
    Object namestring_1, open_mode;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,88);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(namestring_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = namestring_1;
    temp = LONG_TO_FIXNUM(g2ext_g2_stream_open(ISTRING(temp),IFIX(open_mode)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-G2_STREAM_WRITE_STRING */
Object c_g2_stream_write_string(output_string,g2_output_stream,write_newline_p)
    Object output_string, g2_output_stream, write_newline_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,89);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(output_string);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = output_string;
    temp = FIX(g2ext_str_write_string(ISTRING(temp),IFIX(g2_output_stream),
	    IFIX(write_newline_p)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-RUN-TRACE */
Object c_run_trace(command,length_1,wide_p)
    Object command, length_1, wide_p;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(13,90);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(command);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = command;
    temp = FIX(g2ext_run_trace(ISTRING(temp),IFIX(length_1),IFIX(wide_p)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* RUN-TRACE */
Object run_trace(string_1)
    Object string_1;
{
    Object temp, temp_1;

    x_note_fn_call(13,91);
    temp = FIX((SI_Long)0L);
    if (text_string_p(string_1))
	temp_1 = 
		FIX(g2ext_run_trace(UBYTE_16_SARRAY_TO_USHORT_PTR(string_1),
		IFIX(lengthw(string_1)),(SI_Long)1L));
    else if (STRINGP(string_1))
	temp_1 = c_run_trace(string_1,length(string_1),FIX((SI_Long)0L));
    else
	temp_1 = FIX((SI_Long)0L);
    temp = NUM_NE(temp,temp_1) ? T : Nil;
    return VALUES_1(temp);
}

/* VISIBLE-WINDOW-IS-PRESENT-P */
Object visible_window_is_present_p()
{
    Object temp;

    x_note_fn_call(13,92);
    temp = (SI_Long)0L != g2ext_visible_window_is_present() ? T : Nil;
    return VALUES_1(temp);
}

/* WINDOW-IS-PRESENT-P */
Object window_is_present_p()
{
    Object temp;

    x_note_fn_call(13,93);
    temp = (SI_Long)0L != g2ext_window_is_present() ? T : Nil;
    return VALUES_1(temp);
}

Object G2_max_threads = UNBOUND;

Object Max_number_of_cores = UNBOUND;

Object Number_of_all_threads = UNBOUND;

/* MAKE-THREAD-ARRAY */
Object make_thread_array(object)
    Object object;
{
    Object thread_array;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(13,94);
    thread_array = make_array(1,Number_of_all_threads);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Number_of_all_threads);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    ISVREF(thread_array,index_1) = object;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(thread_array);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_thread_index, Qcurrent_thread_index);

Object Backoff_min_delay = UNBOUND;

Object Backoff_max_delay = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Backoff_limit, Qbackoff_limit);

/* BACK-OFF */
Object back_off()
{
    Object temp_2;
    SI_Long delay, temp, temp_1;
    double temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(13,95);
    delay = IFIX(g2_random(Backoff_limit));
    temp = IFIX(Backoff_max_delay);
    temp_1 = (SI_Long)2L * IFIX(Backoff_limit);
    Backoff_limit = FIX(MIN(temp,temp_1));
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp_2 = coerce(FIX(delay),Qdouble_float);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	lsleep(DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 1000.0));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

void primitives_INIT()
{
    Object temp;
    Object Qg2_stream_foreign_file_op_failure, AB_package;
    Object Qg2_stream_foreign_file_op_success;
    Object Qg2_stream_open_mode_for_binary_update;
    Object Qg2_stream_open_mode_for_binary_appending;
    Object Qg2_stream_open_mode_for_binary_output;
    Object Qg2_stream_open_mode_for_binary_input;
    Object Qg2_stream_open_mode_for_update, Qg2_stream_open_mode_for_appending;
    Object Qg2_stream_open_mode_for_output, Qg2_stream_open_mode_for_input;
    Object Qwide_character_code_offset, string_constant_19;
    Object Qrpc_s_uuid_no_address_message, string_constant_18;
    Object Qrpc_s_uuid_local_only_message, Qrpc_s_uuid_no_address;
    Object Qrpc_s_uuid_local_only, Qabort_level_4, Qabort_level_3;
    Object Qabort_level_2, Qabort_level_1, Qmost_positive_workspace_coordinate;
    Object Qmost_negative_workspace_coordinate;
    Object Qscaling_factor_for_text_widths;
    Object Qnumber_of_fraction_bits_for_text_widths, Qgreatest_magnification;
    Object Qleast_magnification, Qminus_of_isqrt_of_most_positive_fixnum;
    Object Qisqrt_of_most_positive_fixnum, Qprimitives;
    Object Qg2int_run_trace_function, Qnamed_dynamic_extent_description;
    Object list_constant_3, string_constant_17, string_constant_16;
    Object Qpm_print_structure, Qpm_composite_type_of, Qpm_type_of, Qpm_nthcdr;
    Object Qpm_elt, list_constant_2, Qframe_vector_pool, Qbyte_vector_16_pool;
    Object Qtoken_conses, Qgraphics_conses, Qslot_value_conses, Qgensym_conses;

    x_note_fn_call(13,96);
    SET_PACKAGE("AB");
    if (One_integer == UNBOUND)
	One_integer = FIX((SI_Long)1L);
    if (Minus_one_integer == UNBOUND)
	Minus_one_integer = FIX((SI_Long)-1L);
    if (Global_property_conses == UNBOUND)
	Global_property_conses = Nil;
    if (Object_pool_meters == UNBOUND)
	Object_pool_meters = Nil;
    AB_package = STATIC_PACKAGE("AB");
    Qgensym_conses = STATIC_SYMBOL("GENSYM-CONSES",AB_package);
    Qslot_value_conses = STATIC_SYMBOL("SLOT-VALUE-CONSES",AB_package);
    Qgraphics_conses = STATIC_SYMBOL("GRAPHICS-CONSES",AB_package);
    Qtoken_conses = STATIC_SYMBOL("TOKEN-CONSES",AB_package);
    Qbyte_vector_16_pool = STATIC_SYMBOL("BYTE-VECTOR-16-POOL",AB_package);
    Qframe_vector_pool = STATIC_SYMBOL("FRAME-VECTOR-POOL",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)6L,Qgensym_conses,
	    Qslot_value_conses,Qgraphics_conses,Qtoken_conses,
	    Qbyte_vector_16_pool,Qframe_vector_pool);
    Names_of_interesting_system_object_pools = list_constant_2;
    Qpm_elt = STATIC_SYMBOL("PM-ELT",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_elt,STATIC_FUNCTION(pm_elt,NIL,FALSE,2,2));
    Qpm_nthcdr = STATIC_SYMBOL("PM-NTHCDR",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_nthcdr,STATIC_FUNCTION(pm_nthcdr,NIL,FALSE,2,2));
    Qpm_type_of = STATIC_SYMBOL("PM-TYPE-OF",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_type_of,STATIC_FUNCTION(pm_type_of,NIL,FALSE,1,1));
    Qcomposite_object = STATIC_SYMBOL("COMPOSITE-OBJECT",AB_package);
    Qpm_composite_type_of = STATIC_SYMBOL("PM-COMPOSITE-TYPE-OF",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_composite_type_of,
	    STATIC_FUNCTION(pm_composite_type_of,NIL,FALSE,1,1));
    if (Single_element_string == UNBOUND)
	Single_element_string = make_string(1,FIX((SI_Long)1L));
    string_constant = STATIC_STRING("#w\"");
    string_constant_1 = STATIC_STRING(" ");
    string_constant_2 = STATIC_STRING("\"");
    Qpm_print_structure = STATIC_SYMBOL("PM-PRINT-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qpm_print_structure,
	    STATIC_FUNCTION(pm_print_structure,NIL,FALSE,2,2));
    string_constant_3 = STATIC_STRING("-G2-STRUCT");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qmanaged_float = STATIC_SYMBOL("MANAGED-FLOAT",AB_package);
    string_constant_16 = STATIC_STRING("slotnames.70");
    string_constant_17 = STATIC_STRING("/home/ab/g2/slotnames.70");
    list_constant_3 = STATIC_LIST((SI_Long)2L,string_constant_16,
	    string_constant_17);
    Pm_file_names = list_constant_3;
    if (Pm_slot_names == UNBOUND)
	Pm_slot_names = Nil;
    if (Pm_max_length == UNBOUND)
	Pm_max_length = FIX((SI_Long)100L);
    string_constant_4 = STATIC_STRING(" is a ");
    string_constant_5 = STATIC_STRING(" aka ");
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    string_constant_6 = STATIC_STRING("  ");
    string_constant_7 = STATIC_STRING("CDR");
    if (Pm_temp_string == UNBOUND)
	Pm_temp_string = make_string(1,FIX((SI_Long)10L));
    string_constant_8 = STATIC_STRING("0123456789abcdef");
    string_constant_9 = STATIC_STRING("~A");
    string_constant_10 = STATIC_STRING("#<Managed-Float ");
    string_constant_11 = STATIC_STRING(">");
    string_constant_12 = STATIC_STRING("#<");
    string_constant_13 = STATIC_STRING("(");
    string_constant_14 = STATIC_STRING(" . ");
    string_constant_15 = STATIC_STRING(")");
    Qsystem_variable_descriptions = 
	    STATIC_SYMBOL("SYSTEM-VARIABLE-DESCRIPTIONS",AB_package);
    System_variable_descriptions_prop = Qsystem_variable_descriptions;
    Qlisp_modules_to_be_loaded = STATIC_SYMBOL("LISP-MODULES-TO-BE-LOADED",
	    AB_package);
    if (Process_initializations_alist == UNBOUND)
	Process_initializations_alist = Nil;
    Qno_saved_initial_value = STATIC_SYMBOL("NO-SAVED-INITIAL-VALUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qno_saved_initial_value,No_saved_initial_value);
    if (No_saved_initial_value == UNBOUND)
	No_saved_initial_value = LIST_1(Qno_saved_initial_value);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    Qno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    Ksymbol_value = STATIC_SYMBOL("SYMBOL-VALUE",Pkeyword);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    Named_dynamic_extent_description_prop = Qnamed_dynamic_extent_description;
    Qgsi_api_symbol = STATIC_SYMBOL("GSI-API-SYMBOL",AB_package);
    Qtrace_function_p = STATIC_SYMBOL("TRACE-FUNCTION-P",AB_package);
    Trace_function_p_prop = Qtrace_function_p;
    if (Running_trace_function_p == UNBOUND)
	Running_trace_function_p = Nil;
    Qg2int_run_trace_function = STATIC_SYMBOL("G2INT-RUN-TRACE-FUNCTION",
	    AB_package);
    set_get(Qg2int_run_trace_function,Qgsi_api_symbol,T);
    if (Unix_command_callback_function == UNBOUND)
	Unix_command_callback_function = Nil;
    if (Cached_fixnum_time_qm == UNBOUND)
	Cached_fixnum_time_qm = Nil;
    if (Check_time_on_next_uuid == UNBOUND)
	Check_time_on_next_uuid = Nil;
    if (Time_to_check_network_events == UNBOUND)
	Time_to_check_network_events = Nil;
    Fixnum_time_units_per_second = FIX(g2ext_g2_clock_ticks_per_second());
    temp = FIX(IFIX(Most_positive_fixnum) / 
	    IFIX(Fixnum_time_units_per_second));
    Fixnum_time_bignum_worries_limit = temp;
    if (Fixnum_time_interval_for_one_second == UNBOUND)
	Fixnum_time_interval_for_one_second = 
		fixnum_time_interval(FIX((SI_Long)1000L));
    Qknown_process_ids_qm = STATIC_SYMBOL("KNOWN-PROCESS-IDS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qknown_process_ids_qm,Known_process_ids_qm);
    Qprimitives = STATIC_SYMBOL("PRIMITIVES",AB_package);
    record_system_variable(Qknown_process_ids_qm,Qprimitives,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qall_foreign_function_images_qm = 
	    STATIC_SYMBOL("ALL-FOREIGN-FUNCTION-IMAGES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_foreign_function_images_qm,
	    All_foreign_function_images_qm);
    record_system_variable(Qall_foreign_function_images_qm,Qprimitives,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qall_external_foreign_function_images_qm = 
	    STATIC_SYMBOL("ALL-EXTERNAL-FOREIGN-FUNCTION-IMAGES\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_external_foreign_function_images_qm,
	    All_external_foreign_function_images_qm);
    record_system_variable(Qall_external_foreign_function_images_qm,
	    Qprimitives,Nil,Qnil,Qnil,Qnil,Qnil);
    Qisqrt_of_most_positive_fixnum = 
	    STATIC_SYMBOL("ISQRT-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qisqrt_of_most_positive_fixnum,
	    Isqrt_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qisqrt_of_most_positive_fixnum,
	    isqrt(Most_positive_fixnum));
    Qminus_of_isqrt_of_most_positive_fixnum = 
	    STATIC_SYMBOL("MINUS-OF-ISQRT-OF-MOST-POSITIVE-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminus_of_isqrt_of_most_positive_fixnum,
	    Minus_of_isqrt_of_most_positive_fixnum);
    SET_SYMBOL_VALUE(Qminus_of_isqrt_of_most_positive_fixnum,
	    FIXNUM_NEGATE(Isqrt_of_most_positive_fixnum));
    Qleast_magnification = STATIC_SYMBOL("LEAST-MAGNIFICATION",AB_package);
    SET_SYMBOL_VALUE(Qleast_magnification,FIX((SI_Long)16L));
    Qgreatest_magnification = STATIC_SYMBOL("GREATEST-MAGNIFICATION",
	    AB_package);
    SET_SYMBOL_VALUE(Qgreatest_magnification,FIX((SI_Long)4096L));
    float_constant = STATIC_FLOAT(0.0);
    Qnumber_of_fraction_bits_for_text_widths = 
	    STATIC_SYMBOL("NUMBER-OF-FRACTION-BITS-FOR-TEXT-WIDTHS",
	    AB_package);
    SET_SYMBOL_VALUE(Qnumber_of_fraction_bits_for_text_widths,
	    FIX((SI_Long)8L));
    Qscaling_factor_for_text_widths = 
	    STATIC_SYMBOL("SCALING-FACTOR-FOR-TEXT-WIDTHS",AB_package);
    SET_SYMBOL_VALUE(Qscaling_factor_for_text_widths,FIX((SI_Long)256L));
    Qmost_negative_workspace_coordinate = 
	    STATIC_SYMBOL("MOST-NEGATIVE-WORKSPACE-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qmost_negative_workspace_coordinate,
	    FIX((SI_Long)-16777216L));
    Qmost_positive_workspace_coordinate = 
	    STATIC_SYMBOL("MOST-POSITIVE-WORKSPACE-COORDINATE",AB_package);
    SET_SYMBOL_VALUE(Qmost_positive_workspace_coordinate,
	    FIX((SI_Long)16777215L));
    Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation 
	    = 
	    lfloor(DOUBLE_TO_DOUBLE_FLOAT(sqrt((double)
	    (IFIX(Most_positive_fixnum) >>  -  - (SI_Long)1L))),_);
    if (Abort_level_0_tag == UNBOUND)
	Abort_level_0_tag = Nil;
    Qabort_level_0 = STATIC_SYMBOL("ABORT-LEVEL-0",AB_package);
    Qabort_level_1 = STATIC_SYMBOL("ABORT-LEVEL-1",AB_package);
    Qabort_level_2 = STATIC_SYMBOL("ABORT-LEVEL-2",AB_package);
    Qabort_level_3 = STATIC_SYMBOL("ABORT-LEVEL-3",AB_package);
    Qabort_level_4 = STATIC_SYMBOL("ABORT-LEVEL-4",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qabort_level_0,
	    Qabort_level_1,Qabort_level_2,Qabort_level_3,Qabort_level_4);
    Qrpc_s_uuid_local_only = STATIC_SYMBOL("RPC_S_UUID_LOCAL_ONLY",AB_package);
    SET_SYMBOL_VALUE(Qrpc_s_uuid_local_only,FIX((SI_Long)1824L));
    Qrpc_s_uuid_no_address = STATIC_SYMBOL("RPC_S_UUID_NO_ADDRESS",AB_package);
    SET_SYMBOL_VALUE(Qrpc_s_uuid_no_address,FIX((SI_Long)1739L));
    Qrpc_s_uuid_local_only_message = 
	    STATIC_SYMBOL("RPC_S_UUID_LOCAL_ONLY-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrpc_s_uuid_local_only_message,
	    Rpc_s_uuid_local_only_message);
    string_constant_18 = 
	    STATIC_STRING("A UUID that is valid only on this computer has been allocated.");
    SET_SYMBOL_VALUE(Qrpc_s_uuid_local_only_message,string_constant_18);
    Qrpc_s_uuid_no_address_message = 
	    STATIC_SYMBOL("RPC_S_UUID_NO_ADDRESS-MESSAGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrpc_s_uuid_no_address_message,
	    Rpc_s_uuid_no_address_message);
    string_constant_19 = 
	    STATIC_STRING("No network address is available to use to construct a universal unique identifier (UUID).");
    SET_SYMBOL_VALUE(Qrpc_s_uuid_no_address_message,string_constant_19);
    Qwide_character_code_offset = 
	    STATIC_SYMBOL("WIDE-CHARACTER-CODE-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qwide_character_code_offset,FIX((SI_Long)1000000L));
    float_constant_1 = STATIC_FLOAT(4195835.0);
    float_constant_2 = STATIC_FLOAT(3145727.0);
    Qg2_stream_open_mode_for_input = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-INPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_input,FIX((SI_Long)0L));
    Qg2_stream_open_mode_for_output = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_output,FIX((SI_Long)1L));
    Qg2_stream_open_mode_for_appending = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-APPENDING",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_appending,FIX((SI_Long)2L));
    Qg2_stream_open_mode_for_update = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_update,FIX((SI_Long)3L));
    Qg2_stream_open_mode_for_binary_input = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-INPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_binary_input,FIX((SI_Long)4L));
    Qg2_stream_open_mode_for_binary_output = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-OUTPUT",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_binary_output,FIX((SI_Long)5L));
    Qg2_stream_open_mode_for_binary_appending = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-APPENDING",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_binary_appending,
	    FIX((SI_Long)6L));
    Qg2_stream_open_mode_for_binary_update = 
	    STATIC_SYMBOL("G2-STREAM-OPEN-MODE-FOR-BINARY-UPDATE",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_open_mode_for_binary_update,FIX((SI_Long)7L));
    Qg2_stream_foreign_file_op_success = 
	    STATIC_SYMBOL("G2-STREAM-FOREIGN-FILE-OP-SUCCESS",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_foreign_file_op_success,FIX((SI_Long)0L));
    Qg2_stream_foreign_file_op_failure = 
	    STATIC_SYMBOL("G2-STREAM-FOREIGN-FILE-OP-FAILURE",AB_package);
    SET_SYMBOL_VALUE(Qg2_stream_foreign_file_op_failure,FIX((SI_Long)-1L));
    G2_max_threads = FIX(g2ext_max_threads());
    Max_number_of_cores = FIX(g2ext_number_of_cores());
    Number_of_all_threads = G2_max_threads;
    if (Current_thread_index == UNBOUND)
	Current_thread_index = FIX((SI_Long)0L);
    Backoff_min_delay = FIX((SI_Long)1L);
    Backoff_max_delay = FIX((SI_Long)1024L);
    if (Backoff_limit == UNBOUND)
	Backoff_limit = Backoff_min_delay;
}
